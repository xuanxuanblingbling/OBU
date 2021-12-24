#include "socketCommon.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "socket_ipc.h"

SocketIpc mSocketIpc;

void fun(std::vector<uint8_t> &data, std::string &path, void *user_dat)
{
    recv_func_type recv_func = (recv_func_type)user_dat;
    (*recv_func)(data.data(), data.size());
}

extern "C" bool startFunc(char *path, uint8_t mode)
{
    return mSocketIpc.start(path, mode);
}
extern "C" void stopFunc()
{
    mSocketIpc.stop();
}

extern "C" bool sendDataFunc(const uint8_t *dat, size_t len, uint64_t mask, const char *path)
{
    // printf("send_data = ");
    // for(int i=0; i<20; i++)
    // {
    //     printf("%c", dat[i]);

    // }
    return mSocketIpc.send_data(dat, len, mask, path);
}

extern "C" bool recDataFunc(char *path, recv_func_type recv_func, uint64_t mask)
{

    return mSocketIpc.add_client(path, mask, &fun, (void *)recv_func);
}

extern "C" size_t get_connect_num()
{
    return mSocketIpc.get_connect_num();
}
