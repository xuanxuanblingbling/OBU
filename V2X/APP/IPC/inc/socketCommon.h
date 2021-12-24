#ifndef _SOCKET_COMMON_H_
#define _SOCKET_COMMON_H_

#define IPC_SERVER_MODE 0x01
#define IPC_CLIENT_MODE 0x02
#define IPC_BOTH_MODE 0x03


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "wj_log.h"
#include "Debug.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



typedef void (*recv_func_type)(uint8_t *, uint64_t);

bool startFunc(char *path, uint8_t mode);

void stopFunc();

size_t get_connect_num();

bool sendDataFunc(const uint8_t *dat, size_t len, uint64_t mask, const char *path);

bool recDataFunc(char *path, recv_func_type recv_func, uint64_t mask);

#ifdef __cplusplus
}
#endif

#endif //_SOCKET_COMMON_H_