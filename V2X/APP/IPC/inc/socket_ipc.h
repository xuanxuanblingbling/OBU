#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

#define IPC_SERVER_MODE 0x01
#define IPC_CLIENT_MODE 0x02
#define IPC_BOTH_MODE 0x03

using ipcfunc_type = std::function<void(std::vector<uint8_t> &, std::string &, void *)>;
class SocketIpc {
public:
    SocketIpc();
    ~SocketIpc();

public:
    bool start(const std::string &path, uint8_t mode);
    void stop();
    bool get_status();
    size_t get_connect_num();
    size_t get_client_num();
    std::string get_path();

public:
    bool send_data(const std::vector<uint8_t> &dat, uint64_t mask, const std::string &dest);
    bool send_data(const uint8_t *dat, size_t len, uint64_t mask, const std::string &dest);
    bool try_send_data(const std::vector<uint8_t> &dat, uint64_t mask, const std::string &dest);
    bool try_send_data(const uint8_t *dat, size_t len, uint64_t mask, const std::string &dest);
    void clear_queue();

public:
    bool add_client(const std::string &path, uint64_t mask, const ipcfunc_type &func, void *user_dat);
    bool set_client(const std::string &path, uint64_t mask, const ipcfunc_type &func, void *user_dat);
    bool set_client(const std::string &path, const ipcfunc_type &func, void *user_dat);
    bool set_client(const std::string &path, uint64_t mask);
    void del_client(const std::string &path);
    std::vector<std::string> get_client_path();
    bool get_client_status(const std::string &path);

public:
    void set_send_queue_size(uint32_t num);
    void set_send_pack_size(uint32_t num);
    void set_recv_pack_size(uint32_t num);
    uint32_t get_send_queue_size();
    uint32_t get_send_pack_size();
    uint32_t get_recv_pack_size();
    uint64_t get_send_mask();

private:
    class impl;
    std::unique_ptr<impl> impl_;
};
