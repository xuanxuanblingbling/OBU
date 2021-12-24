#include "socket_ipc.h"

#if defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64
#pragma comment(lib, "Ws2_32.lib")
#include <io.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#if 1 // prevent c-format change order
#include <windows.h>
#endif
#include <afunix.h>

typedef SOCKET socket_t;
#define _errno_ WSAGetLastError()
#define SHUT_RD SD_RECEIVE
#define SHUT_WR SD_SEND
#define SHUT_RDWR SD_BOTH
#define IGNORE_ERROR (_errno_ == WSAEINTR) || (_errno_ == WSAEWOULDBLOCK)
#define CONNECT_SUCCESS (_errno_ == WSAEISCONN)
#define MSG_NOSIGNAL 0
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#define closesocket close
typedef int socket_t;
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#define _errno_ errno
#define IGNORE_ERROR (_errno_ == EINTR) || (_errno_ == EWOULDBLOCK) || (_errno_ == EAGAIN) || (_errno_ == EINPROGRESS)
#define CONNECT_SUCCESS (_errno_ == EISCONN)
#define WSAEISCONN EISCONN
#endif

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <list>
#include <mutex>
#include <set>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <unordered_map>

// 帧头  4    0x1A2B3C4D
// 帧序号 4
// 帧类型 8
// client id
// 帧长度 4
// 内容校验位
// 当前帧校验位
// 内容
#define SOCKETIPC_HEADID 0x1A2B3C4D
#define SOCKETIPC_HEADLEN 32
#define RESET_HEADNUM 5
#define SEND_MASK_PEROID 1000

typedef struct _Client_Info {
    std::string path;
    socket_t fd = INVALID_SOCKET;
    uint64_t get_mask = 0;
    uint64_t set_mask = 0;
    uint32_t head_len = 0;
    uint32_t recv_len = 0;
    uint32_t client_id = 0;
    std::vector<uint8_t> content;
    void *user_dat = nullptr;
    ipcfunc_type func = nullptr;
    bool valid = false; // 表示当前socket的连接状态
    bool del = false;   // 表示当前socket的连接状态
    uint8_t header[SOCKETIPC_HEADLEN] = {0};
    uint16_t head_num = 0;
} Client_Info;

typedef struct _Connect_Info {
    socket_t fd = INVALID_SOCKET;
    uint64_t mask = 0;
    uint32_t send_len = 0;
    bool valid = false;
    uint32_t client_id;
} Connect_Info;

typedef struct _SendData_Info {
    std::vector<uint8_t> data;
    uint64_t mask = 0;
    uint32_t id = 0;
} SendData_Info;

namespace socket_ipc {
#if defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64
class WSInit {
public:
    WSInit() {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }
    ~WSInit() { WSACleanup(); }
};
#endif

void set_nonblocking(socket_t sock, bool nonblocking) {
#if defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64
    auto flags = nonblocking ? 1UL : 0UL;
    ioctlsocket(sock, FIONBIO, &flags);
#else
    int flags = fcntl(sock, F_GETFL);
    fcntl(sock, F_SETFL, nonblocking ? (flags | O_NONBLOCK) : (flags & (~O_NONBLOCK)));
#endif
}

int make_socketaddr(const std::string &name, struct sockaddr_un *addr, int *len) {
    int name_len = name.size();
    if (name_len >= (int)sizeof(addr->sun_path) - 1) /* too long */
        return -1;
#if defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64
    memcpy(addr->sun_path, name.c_str(), name_len);
    *len = sizeof(struct sockaddr_un);
#else
    addr->sun_path[0] = '\0'; /* abstract namespace */
    memcpy(addr->sun_path + 1, name.c_str(), name_len);
    *len = 1 + name_len + offsetof(struct sockaddr_un, sun_path);
#endif
    addr->sun_family = AF_UNIX;
    return 0;
}

uint32_t bcc_check(uint8_t *buf, uint32_t buf_len) {
    uint32_t *l_dat = (uint32_t *)buf;
    uint32_t l_bcc = 0xAABBCCDD, remain_dat = 0;
    for (uint32_t idx = 0; idx < (buf_len >> 2); ++idx)
        l_bcc ^= l_dat[idx];
    if (buf_len & 0x03) {
        memcpy(&remain_dat, &l_dat[(buf_len >> 2)], buf_len & 0x03);
        l_bcc ^= remain_dat;
    }
    return l_bcc;
}

socket_t creat_socket() {
    socket_t fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd != INVALID_SOCKET)
        socket_ipc::set_nonblocking(fd, true);
    return fd;
}

bool bind_listen(socket_t fd, const std::string &path) {
    struct sockaddr_un server_addr = {0};
    int addr_len = 0;
    if (socket_ipc::make_socketaddr(path, &server_addr, &addr_len) < 0)
        return false;
    if (bind(fd, (struct sockaddr *)&server_addr, addr_len) == SOCKET_ERROR)
        return false;
    if (listen(fd, SOMAXCONN) == SOCKET_ERROR)
        return false;
    return true;
}

int connect_server(socket_t fd, const std::string &path) {
    struct sockaddr_un server_addr = {0};
    int addr_len = 0;
    if (socket_ipc::make_socketaddr(path, &server_addr, &addr_len) < 0) {
        return -1;
    }
    if (connect(fd, (struct sockaddr *)&server_addr, addr_len) == SOCKET_ERROR) {
        if (CONNECT_SUCCESS)
            return 0;
        if (IGNORE_ERROR) // WSAEWOULDBLOCK
            return 1;
        return -1;
    }

    return 0;
}
} // namespace socket_ipc

class SocketIpc::impl {
public:
    impl(){};
    ~impl() { socketipc_stop(); };

public:
    bool socket_ipc_init(const std::string &path, uint8_t mode);
    void socketipc_stop();
    std::string get_path() { return server_path; }
    bool get_status() { return socket_ipc_status.load(); }
    size_t get_connect_num() { return connect_list.size(); }
    size_t get_client_num() { return client_list.size(); }

public:
    bool send_data(const uint8_t *dat, size_t len, uint64_t mask, const std::string &dest, uint8_t flag);
    void clear_queue() {
        std::lock_guard<std::mutex> lck(send_data_mux);
        send_data_list.clear();
    }

public:
    bool add_client(const std::string &path, uint64_t mask, const ipcfunc_type &func, void *user_dat);
    bool set_client(const std::string &path, uint64_t mask, const ipcfunc_type &func, void *user_dat) {
        return set_client(path, mask, func, user_dat, 0x03);
    }
    bool set_client(const std::string &path, const ipcfunc_type &func, void *user_dat) {
        return set_client(path, 0, func, user_dat, 0x01);
    }
    bool set_client(const std::string &path, uint64_t mask) { return set_client(path, mask, nullptr, nullptr, 0x02); }

    void del_client(const std::string &path) {
        std::lock_guard<std::mutex> lck(client_list_mux);
        auto dat_itra = client_map.find(path);
        if (dat_itra != client_map.end()) {
            closesocket((dat_itra->second)->fd);
            (dat_itra->second)->fd = INVALID_SOCKET;
            (dat_itra->second)->del = true;
            client_change_flag++;
        }
    }

    bool get_client_status(const std::string &path) {
        std::lock_guard<std::mutex> lck(client_list_mux);
        auto dat_itra = client_map.find(path);
        if (dat_itra == client_map.end())
            return false;
        return (dat_itra->second)->valid;
    }
    std::vector<std::string> get_client_path() {
        std::vector<std::string> cli_path;
        if (client_list.empty())
            return cli_path;
        cli_path.resize(client_list.size());
        size_t idx = 0;
        for (auto &cli_data : client_list) {
            cli_path[idx++] = cli_data.path;
        }
        return cli_path;
    }

public:
    void set_send_queue_size(uint32_t num) { send_queue_size = (num > 2) ? num : send_queue_size; }
    void set_send_pack_size(uint32_t num) { send_pack_size = (num >= 512 && num <= 10485760) ? num : send_pack_size; }
    void set_recv_pack_size(uint32_t num) { recv_packsize = (num >= 1024 && num <= 10485760) ? num : recv_packsize; }
    uint32_t get_send_queue_size() { return send_queue_size; }
    uint32_t get_send_pack_size() { return send_pack_size; }
    uint32_t get_recv_pack_size() { return recv_packsize; }
    uint64_t get_send_mask() { return send_mask; }

private:
    FILE *fid = NULL;
    uint8_t ipc_mode = IPC_BOTH_MODE;
    socket_t server_fd = INVALID_SOCKET;
    uint32_t server_id = 0;
    std::list<Connect_Info> connect_list;
    uint64_t send_mask = 0;
    std::set<uint32_t> connect_id_set;
    uint64_t connect_change_flag = 0;
    std::string server_path = "socket.path";
    std::mutex connect_mux;

private: // 发送数据相关的变量
    std::list<SendData_Info> send_data_list;
    uint32_t send_pack_size = 32000;
    uint32_t send_queue_size = 32;
    std::mutex send_data_mux;
    std::mutex send_cv_mtx;
    std::condition_variable send_dat_cv;
    std::mutex wait_cv_mtx;
    std::condition_variable wait_dat_cv;

private:
    std::unordered_map<std::string, std::list<Client_Info>::iterator> client_map;
    std::list<Client_Info> client_list;
    std::mutex client_list_mux;
    uint32_t recv_packsize = 64000U;
    uint64_t client_change_flag = 0;
    uint64_t send_mask_flag = 0;

private:
    std::atomic_bool server_send_status{false};
    std::atomic_bool listen_connect_status{false};
    std::atomic_bool client_recv_status{false};
    std::atomic_bool socket_ipc_status{false};
    std::atomic_bool id_set_status{true};

private:
    void client_recv_thread();
    bool send_client_mask();
    void maintain_client_list();
    uint64_t get_current_ms() {
        return (std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()))
            .count();
    }

private:
    void connect_listen_thread();
    void server_send_thread();
    void maintain_connect_list();

private:
    void client_close_all();
    bool set_client(const std::string &path, uint64_t mask, const ipcfunc_type &func, void *user_dat, uint8_t flag);
    void server_close_all();
    bool server_init(const std::string &path);

#if defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64
    socket_ipc::WSInit wsinit_;
#endif
};

bool SocketIpc::impl::socket_ipc_init(const std::string &path, uint8_t mode) {
    if (path.empty() || mode == 0 || mode > 3)
        return false;

    if (socket_ipc_status.load() && path == server_path && mode == ipc_mode)
        return true;

#if !(defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64)
    signal(SIGPIPE, SIG_IGN);
#endif
    ipc_mode = mode;
    server_path = path;
    std::hash<std::string> l_strHash;
    server_id = l_strHash(server_path);

    socket_ipc_status.store(false);
    if (listen_connect_status.load() || server_send_status.load() || client_recv_status.load())
        std::this_thread::yield();
    server_close_all();
    connect_list.clear();
    connect_id_set.clear();
    send_mask = 0;
    if (mode & IPC_SERVER_MODE) {
        if (server_init(path) == false)
            return false;
    }

    client_close_all();
    socket_ipc_status.store(true);

    if (mode & IPC_SERVER_MODE)
        server_send_thread();

    if (mode & IPC_CLIENT_MODE)
        client_recv_thread();
    connect_listen_thread();
    return true;
}

inline void SocketIpc::impl::server_close_all() {
    if (server_fd != INVALID_SOCKET) {
        closesocket(server_fd);
        server_fd = INVALID_SOCKET;
#if defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64
        std::string fname = server_path + ".lck";
        if (fid != NULL)
            fclose(fid);
        fid = NULL;
        _unlink(server_path.c_str());
        _unlink(fname.c_str());
#endif
    }

    std::lock_guard<std::mutex> recv_lck(connect_mux);
    for (auto &cli_fd : connect_list) {
        if (cli_fd.fd != INVALID_SOCKET) {
            cli_fd.valid = false;
            closesocket(cli_fd.fd);
            cli_fd.fd = INVALID_SOCKET;
        }
    }
}

inline void SocketIpc::impl::socketipc_stop() {
    socket_ipc_status.store(false);
    if (listen_connect_status.load() || server_send_status.load() || client_recv_status.load())
        std::this_thread::yield();
    server_close_all();
    client_close_all();
}

inline bool SocketIpc::impl::send_data(const uint8_t *dat, size_t len, uint64_t mask, const std::string &dest,
                                       uint8_t flag) {
    if (len == 0 || socket_ipc_status.load() == false)
        return false;

    std::hash<std::string> l_strHash;
    uint32_t id = l_strHash(dest);
    if (id_set_status.load()) { // 防止更新connect_id_set计算count
        if ((!(mask & send_mask) && connect_id_set.count(id) == 0))
            return false;
    } else
        return false;

    uint32_t *dat_ptr = NULL;
    bool ret = false;
    SendData_Info dat_info;
    dat_info.data.resize(SOCKETIPC_HEADLEN + len);
    dat_info.id = id;
    dat_info.mask = mask;
    memcpy(&(dat_info.data[SOCKETIPC_HEADLEN]), &dat[0], len);
    dat_ptr = (uint32_t *)&dat_info.data[0];
    dat_ptr[6] = socket_ipc::bcc_check(&(dat_info.data[SOCKETIPC_HEADLEN]), len);
    size_t num = 0;
    do {
        num = send_data_list.size();
        if (num < send_queue_size) {
            std::lock_guard<std::mutex> lck(send_data_mux);
            send_data_list.emplace_back(std::move(dat_info));
            send_dat_cv.notify_one();
            ret = true;
            break;
        } else {
            if (flag || (!socket_ipc_status.load()))
                return false;
            std::unique_lock<std::mutex> lck(wait_cv_mtx);
            wait_dat_cv.wait_for(lck, std::chrono::milliseconds(100));
        }
    } while (socket_ipc_status.load());
    return ret;
}

inline void SocketIpc::impl::maintain_connect_list() {
    uint64_t s_mask = 0;
    std::set<uint32_t> id_set;
    std::lock_guard<std::mutex> recv_lck(connect_mux);
    for (auto list_itra = connect_list.begin(); list_itra != connect_list.end();) {
        if (list_itra->valid == false) {
            connect_list.erase(list_itra++);
        } else {
            id_set.insert(list_itra->client_id);
            s_mask |= (list_itra->mask);
            list_itra++;
        }
    }
    id_set_status.store(false);
    connect_id_set = id_set;
    send_mask = s_mask;
    id_set_status.store(true);
}

void SocketIpc::impl::connect_listen_thread() {
    auto listen_thread = [&]() {
        uint64_t connect_change = 0;
        uint64_t client_change = 0;
        uint64_t mask_send_cnt = 0;
        uint8_t recv_buff[1024] = {0};
        uint32_t *header = (uint32_t *)recv_buff;
        fd_set fdsr, fdsw;
        struct timeval tv;
        socket_t max_fd = 0;
        int select_ret = 0, recv_ret = 0, conn_ret = 0;
        uint64_t now_time = 0, mask_time = 0;
        while (1) {
            uint32_t fream_head[8] = {0};
            fream_head[0] = SOCKETIPC_HEADID;
            now_time = get_current_ms();
            tv.tv_sec = 0;
            tv.tv_usec = 500000;
            if (!socket_ipc_status.load())
                break;
            FD_ZERO(&fdsr);
            FD_ZERO(&fdsw);
            max_fd = 0;
            if (ipc_mode & IPC_SERVER_MODE) // listen the server the the client connect server
            {
                int opt_val = 0;
                socklen_t val_len = sizeof(opt_val);
                getsockopt(server_fd, SOL_SOCKET, SO_ERROR, (char *)&opt_val, &val_len);
                FD_SET((server_fd), &fdsr);
                max_fd = server_fd;
                for (const auto &cli_fd : connect_list) {
                    if (cli_fd.valid) {
                        max_fd = (max_fd < cli_fd.fd) ? cli_fd.fd : max_fd;
                        FD_SET((cli_fd.fd), &fdsr);
                    }
                }
            }

            if (ipc_mode & IPC_CLIENT_MODE) // connect the client to the server
            {
                for (Client_Info &cli_fd : client_list) {
                    if (cli_fd.fd == INVALID_SOCKET || cli_fd.valid == false) {
                        if (cli_fd.fd == INVALID_SOCKET)
                            cli_fd.fd = socket_ipc::creat_socket();
                        conn_ret = socket_ipc::connect_server(cli_fd.fd, cli_fd.path);
                        if (conn_ret == 1) {
                            FD_SET(cli_fd.fd, &fdsr);
                            FD_SET(cli_fd.fd, &fdsw);
                            max_fd = (max_fd > cli_fd.fd) ? max_fd : cli_fd.fd;
                        } else if (conn_ret == 0) {
                            cli_fd.valid = true;
                            send_client_mask();
                            send_mask_flag++;
                        }
                    }
                }
            }
            select_ret = 0;
            if (max_fd)
                select_ret = select(max_fd + 1, &fdsr, &fdsw, NULL, &tv);
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            if (select_ret < 0) {
                for (auto &cli_fd : connect_list) {
                    int opt_val = 0;
                    socklen_t val_len = sizeof(opt_val);
                    if (getsockopt(cli_fd.fd, SOL_SOCKET, SO_ERROR, (char *)&opt_val, &val_len) < 0 || opt_val) {
                        closesocket(cli_fd.fd);
                        cli_fd.fd = INVALID_SOCKET;
                        cli_fd.valid = false;
                        connect_change_flag++;
                    }
                }
            }
            if (select_ret > 0) {
                if (ipc_mode & IPC_SERVER_MODE) {
                    for (auto &cli_fd : connect_list) {
                        if (!FD_ISSET(cli_fd.fd, &fdsr))
                            continue;
                        recv_ret = recv(cli_fd.fd, (char *)recv_buff, 1024, MSG_NOSIGNAL);
                        if (recv_ret <= 0 && !(IGNORE_ERROR) && _errno_) { // socket error
                            closesocket(cli_fd.fd);
                            cli_fd.valid = false;
                            cli_fd.fd = INVALID_SOCKET;
                            connect_change_flag++;
                            continue;
                        }
                        if (((uint32_t)recv_ret == header[5] + SOCKETIPC_HEADLEN) && header[0] == SOCKETIPC_HEADID) {
                            uint32_t l_bcc = (0xAABBCCDD ^ header[0] ^ header[1] ^ header[2] ^ header[3] ^ header[4] ^
                                              header[5] ^ header[6]);
                            if (header[7] == l_bcc) { // head check ok
                                uint64_t cli_mask = ((uint64_t)header[3]) << 32 | (uint64_t)header[2];
                                if (cli_mask != cli_fd.mask || cli_fd.client_id != header[4]) { // 注册mask
                                    cli_fd.client_id = header[4];
                                    cli_fd.mask = cli_mask;

                                    uint64_t s_mask = 0;
                                    std::set<uint32_t> id_set;
                                    for (auto &cli : connect_list) {
                                        s_mask |= (cli.mask);
                                        id_set.insert(cli.client_id);
                                    }
                                    id_set_status.store(false);
                                    connect_id_set = id_set;
                                    send_mask = s_mask;
                                    id_set_status.store(true);
                                }
                                std::lock_guard<std::mutex> lck(send_data_mux); // replay empty data
                                SendData_Info s_data;
                                s_data.id = cli_fd.client_id; // 单播
                                s_data.mask = 0;
                                send_data_list.emplace_back(s_data);
                                send_data_list.back().data.resize(SOCKETIPC_HEADLEN);
                            }
                        }
                    }

                    if (FD_ISSET(server_fd, &fdsr)) { // 服务器连接客户端
                        socket_t cli_fd1 = accept(server_fd, NULL, NULL);
                        if (cli_fd1 != SOCKET_ERROR) {
                            fream_head[1]++;
                            fream_head[7] = 0xAABBCCDD ^ fream_head[0] ^ fream_head[1] ^ fream_head[2] ^ fream_head[3] ^
                                            fream_head[4] ^ fream_head[5] ^ fream_head[6];
                            send(cli_fd1, (char *)fream_head, SOCKETIPC_HEADLEN, MSG_NOSIGNAL); // send the notify data
                            socket_ipc::set_nonblocking(cli_fd1, true);
                            std::lock_guard<std::mutex> recv_lck(connect_mux);
                            Connect_Info _cli_info = {cli_fd1, 0, 0, true, 0};
                            connect_list.emplace_back(_cli_info);
                        }
                    }
                }

                if (ipc_mode & IPC_CLIENT_MODE) // 连接客户端到服务器
                {
                    for (Client_Info &cli_fd : client_list) {
                        if (cli_fd.fd != INVALID_SOCKET && cli_fd.valid == false) {
                            if (FD_ISSET(cli_fd.fd, &fdsr) || FD_ISSET(cli_fd.fd, &fdsw)) {
                                int opt_val = 0;
                                socklen_t val_len = sizeof(opt_val);
                                if (!(getsockopt(cli_fd.fd, SOL_SOCKET, SO_ERROR, (char *)&opt_val, &val_len) < 0 ||
                                      opt_val)) {
                                    cli_fd.valid = true;
                                    send_client_mask();
                                    send_mask_flag++;
                                }
                            }
                        }
                    }
                }
            }

            // 维护客户端
            if ((ipc_mode & IPC_CLIENT_MODE)) {
                if (client_change_flag != client_change) {
                    client_change = client_change_flag;
                    maintain_client_list();
                }

                if ((mask_send_cnt != send_mask_flag) || (now_time - mask_time > SEND_MASK_PEROID)) {
                    mask_time = now_time;
                    if (send_client_mask())
                        mask_send_cnt = send_mask_flag;
                }
            }

            // 维护服务端
            if (ipc_mode & IPC_SERVER_MODE) {
                if (connect_change != connect_change_flag) {
                    connect_change = connect_change_flag;
                    maintain_connect_list();
                }
            }
        }
        if (server_send_status.load() || client_recv_status.load())
            std::this_thread::yield();
        listen_connect_status.store(false);
        client_close_all();
        server_close_all();
    };
    std::thread thread_listen(listen_thread);
    listen_connect_status.store(true);
    thread_listen.detach();
}

void SocketIpc::impl::server_send_thread() {
    auto send_thread = [&]() {
        uint32_t fream_head[8] = {0};
        uint32_t *dat_ptr = NULL;
        fream_head[0] = SOCKETIPC_HEADID;
        struct timeval tv;
        fd_set client_fdset;
        SendData_Info dat;
        bool has_data = false;
        while (true) {
            if (!socket_ipc_status.load())
                break;
            if (send_data_list.empty()) {
                std::unique_lock<std::mutex> lck(send_cv_mtx);
                send_dat_cv.wait_for(lck, std::chrono::milliseconds(500));
            }
            has_data = true;
            send_data_mux.lock();
            if (send_data_list.empty())
                has_data = false;
            else {
                dat = std::move(send_data_list.front());
                send_data_list.pop_front();
            }
            send_data_mux.unlock();
            if (has_data == false)
                continue;

            wait_dat_cv.notify_one();
            fream_head[1]++;
            if ((dat.data.size() < SOCKETIPC_HEADLEN))
                continue;

            dat_ptr = (uint32_t *)&(dat.data[0]);
            fream_head[5] = dat.data.size() - SOCKETIPC_HEADLEN;
            fream_head[6] = dat_ptr[6];
            if (fream_head[5] && fream_head[6] == 0)
                fream_head[6] = socket_ipc::bcc_check(&(dat.data[SOCKETIPC_HEADLEN]), fream_head[5]);
            std::vector<std::list<Connect_Info>::iterator> send_fd;
            std::lock_guard<std::mutex> recv_lck(connect_mux);
            for (auto list_itra = connect_list.begin(); list_itra != connect_list.end(); ++list_itra) {
                if (list_itra->valid && ((list_itra->mask & dat.mask) || (list_itra->client_id == dat.id))) {
                    list_itra->send_len = 0;
                    send_fd.emplace_back(list_itra);
                }
            }

            if (send_fd.empty()) {
                connect_change_flag++;
                continue;
            }

            while (1) {
                socket_t max_fd = 0;
                FD_ZERO(&client_fdset);
                for (auto &cli_fd : send_fd) {
                    if ((cli_fd->valid) && (cli_fd->send_len < dat.data.size())) {
                        FD_SET(cli_fd->fd, &client_fdset);
                        max_fd = (cli_fd->fd > max_fd) ? cli_fd->fd : max_fd;
                    }
                }
                if (max_fd == 0) // send complete
                    break;
                tv.tv_sec = 0;
                tv.tv_usec = 500000;
                int ret = select(max_fd + 1, NULL, &client_fdset, NULL, &tv);
                if (ret <= 0)
                    break;
                for (auto &cli_fd : send_fd) {
                    if (FD_ISSET(cli_fd->fd, &client_fdset)) {
                        uint32_t send_len = dat.data.size() - cli_fd->send_len;
                        if (cli_fd->send_len < SOCKETIPC_HEADLEN) {
                            fream_head[2] = cli_fd->mask & (0xFFFFFFFF);
                            fream_head[3] = (cli_fd->mask >> 32) & (0xFFFFFFFF);
                            fream_head[4] = cli_fd->client_id;
                            fream_head[7] = 0xAABBCCDD ^ fream_head[0] ^ fream_head[1] ^ fream_head[2] ^ fream_head[3] ^
                                            fream_head[4] ^ fream_head[5] ^ fream_head[6];
                            memcpy(&dat.data[0], fream_head, SOCKETIPC_HEADLEN); // add header
                        }

                        if (send_len >= send_pack_size * 2)
                            send_len = (send_len > send_pack_size) ? send_pack_size : send_len;
                        else if (send_len > send_pack_size)
                            send_len = (send_len >> 1);
                        int trans_len = send(cli_fd->fd, (char *)(&dat.data[cli_fd->send_len]), send_len, MSG_NOSIGNAL);
                        if ((trans_len == SOCKET_ERROR) && !(IGNORE_ERROR) && _errno_) {
                            closesocket(cli_fd->fd);
                            cli_fd->valid = false;
                            cli_fd->fd = INVALID_SOCKET;
                            connect_change_flag++;
                        } else {
                            cli_fd->send_len += trans_len;
                        }
                    }
                }
            }
        }
        server_send_status.store(false);
    };
    std::thread thread_send(send_thread);
    server_send_status.store(true);
    thread_send.detach();
}

bool SocketIpc::impl::server_init(const std::string &path) {
#if defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64
    std::string fname = path + ".lck";
    if (_access(fname.c_str(), 0) == 0) {
        if (_unlink(fname.c_str()) == -1)
            return false;
    }
    if (_access(path.c_str(), 0) == 0) {
        if (_unlink(path.c_str()) == -1)
            return false;
    }
#endif
    connect_mux.lock();
    connect_list.clear();
    connect_mux.unlock();
    server_path = path;
    server_fd = socket_ipc::creat_socket();
    if (server_fd == INVALID_SOCKET)
        return false;
    if (socket_ipc::bind_listen(server_fd, path) == false)
        return false;
#if defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64
    fid = fopen(fname.c_str(), "w");
    if (fid == NULL) {
        closesocket(server_fd);
        server_fd = INVALID_SOCKET;
        return false;
    }
#endif
    return true;
}

inline bool SocketIpc::impl::set_client(const std::string &path, uint64_t mask, const ipcfunc_type &func,
                                        void *user_dat, uint8_t flag) {
    std::lock_guard<std::mutex> lck(client_list_mux);
    auto dat_itra = client_map.find(path);
    if (dat_itra != client_map.end()) {
        if (flag & 0x01) {
            (dat_itra->second)->func = func;
            (dat_itra->second)->user_dat = user_dat;
        }
        if (flag & 0x02)
            (dat_itra->second)->set_mask = mask;
        return true;
    }
    return false;
}

inline bool SocketIpc::impl::add_client(const std::string &path, uint64_t mask, const ipcfunc_type &func,
                                        void *user_dat) {
    if (path.empty())
        return false;
    auto dat_itra = client_map.find(path);
    if (dat_itra == client_map.end()) {
        Client_Info cli_info;
        cli_info.path = path;
        cli_info.set_mask = mask;
        cli_info.func = func;
        cli_info.user_dat = user_dat;
        std::lock_guard<std::mutex> lck(client_list_mux);
        client_list.emplace_back(cli_info);
        client_map.insert(std::make_pair(path, std::prev(client_list.end())));
    } else {
        (dat_itra->second)->user_dat = user_dat;
        (dat_itra->second)->func = func;
        (dat_itra->second)->set_mask = mask;
    }
    return true;
}

inline bool SocketIpc::impl::send_client_mask() {
    bool ret = true;
    uint32_t fream_head[10] = {0};
    fream_head[0] = SOCKETIPC_HEADID;
    fream_head[1] = 1;
    for (Client_Info &cli_fd : client_list) {
        if (cli_fd.fd != INVALID_SOCKET && (cli_fd.valid == true)) {
            ret = false;
            fream_head[2] = cli_fd.set_mask & (0xFFFFFFFF);
            fream_head[3] = (cli_fd.set_mask >> 32) & (0xFFFFFFFF);
            fream_head[4] = server_id;
            fream_head[7] = 0xAABBCCDD ^ fream_head[0] ^ fream_head[1] ^ fream_head[2] ^ fream_head[3] ^ fream_head[4] ^
                            fream_head[5] ^ fream_head[6];
            int trans_len = send(cli_fd.fd, (char *)fream_head, SOCKETIPC_HEADLEN, MSG_NOSIGNAL);
            if (trans_len < SOCKETIPC_HEADLEN && !(IGNORE_ERROR) && _errno_) {
                closesocket(cli_fd.fd);
                cli_fd.fd = INVALID_SOCKET;
                cli_fd.valid = false;
            } else
                ret = true;
        }
    }
    return ret;
}

inline void SocketIpc::impl::maintain_client_list() {
    std::lock_guard<std::mutex> recv_lck(client_list_mux);
    for (auto cli_itra = client_list.begin(); cli_itra != client_list.end();) {
        if (cli_itra->del == true) {
            if (cli_itra->fd != INVALID_SOCKET)
                closesocket(cli_itra->fd);
            client_map.erase(cli_itra->path);
            client_list.erase(cli_itra++);
        } else
            cli_itra++;
    }
}

void SocketIpc::impl::client_recv_thread() {
    auto recv_thread = [&]() {
        fd_set client_fdset;
        struct timeval tv;
        uint32_t current_packsize = 0;
        uint8_t *recv_buff = NULL;
        uint32_t *buff_ptr = NULL;
        while (true) {
            socket_t max_fd = 0;
            int ret = 0, trans_len = 0, consume_len = 0, remain_len = 0, complete_len = 0;
            tv.tv_sec = 0;
            tv.tv_usec = 100000;
            if (!socket_ipc_status.load())
                break;
            if (current_packsize != recv_packsize) {
                if (recv_buff)
                    delete[] recv_buff;
                current_packsize = recv_packsize;
                recv_buff = new uint8_t[current_packsize];
                if (recv_buff)
                    buff_ptr = (uint32_t *)recv_buff;
                else
                    break;
            }
            FD_ZERO(&client_fdset);
            std::lock_guard<std::mutex> recv_lck(client_list_mux);
            for (const Client_Info &cli_fd : client_list) {
                if ((cli_fd.del == false) && (cli_fd.fd != INVALID_SOCKET) && cli_fd.valid) {
                    max_fd = (max_fd < cli_fd.fd) ? cli_fd.fd : max_fd;
                    FD_SET((cli_fd.fd), &client_fdset);
                }
            }
            if (max_fd == 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            ret = select(max_fd + 1, &client_fdset, NULL, NULL, &tv);
            if (ret == 0)
                continue;

            if (ret > 0) {
                for (Client_Info &cli_fd : client_list) {
                    buff_ptr[0] = SOCKETIPC_HEADID;
                    trans_len = recv(cli_fd.fd, (char *)buff_ptr, recv_packsize, MSG_NOSIGNAL);
                    if (trans_len <= 0 && !(IGNORE_ERROR) && _errno_) {
                        closesocket(cli_fd.fd);
                        cli_fd.fd = INVALID_SOCKET;
                        cli_fd.valid = false;
                        continue;
                    }
                    if (trans_len > 0) {
                        cli_fd.valid = true;
                        if (cli_fd.func == nullptr) {
                            continue;
                        }

                        auto recv_func = cli_fd.func;
                        uint32_t *header = (uint32_t *)cli_fd.header;
                        consume_len = 0;
                        do {
                            int cp_len = SOCKETIPC_HEADLEN - cli_fd.head_len;
                            if (cp_len) { // find head
                                bool try_flag = false;
                                do {
                                    remain_len = trans_len - consume_len;
                                    try_flag = false;
                                    if (cli_fd.head_len == 0 && buff_ptr[0] != SOCKETIPC_HEADID) {
                                        consume_len = trans_len;
                                        break;
                                    }
                                    if (remain_len >= cp_len) {
                                        memcpy(&(cli_fd.header[cli_fd.head_len]), &recv_buff[consume_len], cp_len);
                                        consume_len += cp_len;
                                        uint32_t l_bcc = (0xAABBCCDD ^ header[0] ^ header[1] ^ header[2] ^ header[3] ^
                                                          header[4] ^ header[5] ^ header[6]);
                                        if (header[7] == l_bcc) { // head check ok
                                            cli_fd.get_mask = ((uint64_t)header[3]) << 32 | (uint64_t)header[2];
                                            cli_fd.client_id = header[4];
                                            if (header[5]) // new header
                                            {
                                                cli_fd.head_len = SOCKETIPC_HEADLEN;
                                                cp_len = 0;
                                                cli_fd.content.resize(header[5]);
                                                cli_fd.recv_len = 0;
                                                cli_fd.head_num = 0;
                                            } else { // empty dat
                                                cli_fd.head_len = 0;
                                                cli_fd.content.clear();
                                                cp_len = SOCKETIPC_HEADLEN;
                                            }
                                        } else // check failed check again
                                        {
                                            try_flag = true;
                                            cli_fd.head_len = 0;
                                            cp_len = SOCKETIPC_HEADLEN;
                                        }
                                    } else {
                                        memcpy(&(cli_fd.header[cli_fd.head_len]), &recv_buff[consume_len], remain_len);
                                        cli_fd.head_len += remain_len;
                                        consume_len += remain_len;
                                    }
                                } while (try_flag);
                            }
                            if (cp_len == 0) {
                                if (header[5] == 0 || header[5] <= cli_fd.recv_len ||
                                    header[5] != cli_fd.content.size()) { // header error  try agin
                                    cli_fd.head_len = 0;
                                    cli_fd.content.clear();
                                    cp_len = SOCKETIPC_HEADLEN;
                                    continue;
                                }

                                if ((consume_len == 0) && (buff_ptr[0] == SOCKETIPC_HEADID)) {
                                    cli_fd.head_num++;
                                }
                                if (cli_fd.head_num > RESET_HEADNUM) {
                                    consume_len = trans_len;
                                    cli_fd.head_len = 0;
                                    cli_fd.content.clear();
                                }
                                complete_len = header[5] - cli_fd.recv_len;
                                remain_len = trans_len - consume_len;
                                if (remain_len >= complete_len) {
                                    memcpy(&(cli_fd.content[cli_fd.recv_len]), &recv_buff[consume_len], complete_len);
                                    consume_len += complete_len;
                                    if (header[6] == socket_ipc::bcc_check(&cli_fd.content[0], cli_fd.content.size())) {
                                        recv_func(cli_fd.content, cli_fd.path, cli_fd.user_dat);
                                    }
                                    cli_fd.head_len = 0;
                                    cli_fd.content.clear();
                                } else if (remain_len) {
                                    memcpy(&(cli_fd.content[cli_fd.recv_len]), &recv_buff[consume_len], remain_len);
                                    consume_len += remain_len;
                                    cli_fd.recv_len += remain_len;
                                }
                            }
                        } while (consume_len < trans_len);
                    }
                }
            }
        }
        if (recv_buff)
            delete[] recv_buff;
        socket_ipc_status.store(false);
        client_recv_status.store(false);
    };
    std::thread thread_recv(recv_thread);
    client_recv_status.store(true);
    thread_recv.detach();
}

inline void SocketIpc::impl::client_close_all() {
    for (Client_Info &cli_fd : client_list) {
        if (cli_fd.fd != INVALID_SOCKET) {
            cli_fd.valid = false;
            closesocket(cli_fd.fd);
            cli_fd.fd = INVALID_SOCKET;
        }
    }
}

// 下面引用
void SocketIpc::set_send_queue_size(uint32_t size) { return impl_->set_send_queue_size(size); }
void SocketIpc::set_send_pack_size(uint32_t size) { return impl_->set_send_pack_size(size); }
size_t SocketIpc::get_connect_num() { return impl_->get_connect_num(); }
size_t SocketIpc::get_client_num() { return impl_->get_client_num(); }
bool SocketIpc::send_data(const std::vector<uint8_t> &dat, uint64_t mask, const std::string &dest) {
    return impl_->send_data(&dat[0], dat.size(), mask, dest, 0);
}
bool SocketIpc::send_data(const uint8_t *dat, size_t len, uint64_t mask, const std::string &dest) {
    return impl_->send_data(dat, len, mask, dest, 0);
}
bool SocketIpc::try_send_data(const std::vector<uint8_t> &dat, uint64_t mask, const std::string &dest) {
    return impl_->send_data(&dat[0], dat.size(), mask, dest, 1);
}
bool SocketIpc::try_send_data(const uint8_t *dat, size_t len, uint64_t mask, const std::string &dest) {
    return impl_->send_data(dat, len, mask, dest, 1);
}
void SocketIpc::clear_queue() { return impl_->clear_queue(); }
bool SocketIpc::add_client(const std::string &path, uint64_t mask, const ipcfunc_type &func, void *user_dat) {
    return impl_->add_client(path, mask, func, user_dat);
}
bool SocketIpc::set_client(const std::string &path, uint64_t mask, const ipcfunc_type &func, void *user_dat) {
    return impl_->set_client(path, mask, func, user_dat);
}
uint32_t SocketIpc::get_send_queue_size() { return impl_->get_send_queue_size(); }
uint32_t SocketIpc::get_send_pack_size() { return impl_->get_send_pack_size(); }
std::string SocketIpc::get_path() { return impl_->get_path(); }
bool SocketIpc::get_status() { return impl_->get_status(); }
bool SocketIpc::set_client(const std::string &path, uint64_t mask) { return impl_->set_client(path, mask); }
bool SocketIpc::set_client(const std::string &path, const ipcfunc_type &func, void *user_dat) {
    return impl_->set_client(path, func, user_dat);
}
void SocketIpc::del_client(const std::string &path) { return impl_->del_client(path); }
bool SocketIpc::get_client_status(const std::string &path) { return impl_->get_client_status(path); }
std::vector<std::string> SocketIpc::get_client_path() { return impl_->get_client_path(); }
void SocketIpc::set_recv_pack_size(uint32_t len) { return impl_->set_recv_pack_size(len); }
uint32_t SocketIpc::get_recv_pack_size() { return impl_->get_recv_pack_size(); }
uint64_t SocketIpc::get_send_mask() { return impl_->get_send_mask(); }
bool SocketIpc::start(const std::string &path, uint8_t mode) { return impl_->socket_ipc_init(path, mode); }
void SocketIpc::stop() { return impl_->socketipc_stop(); }
SocketIpc::SocketIpc() : impl_(std::make_unique<impl>()) {}
SocketIpc::~SocketIpc() {}
