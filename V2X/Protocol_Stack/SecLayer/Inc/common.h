#ifndef COMMON_H
#define COMMON_H

#include "SecLayer.h"

#define DEVIDE_TYPE_OBU 1
#define DEVIDE_TYPE_RSU 2


#define SECLAYER_ERR(fmt, ...) printf("\033[31m[Seclayer: %s:%d:%s:%s] " #fmt "\033[0m\r\n", __func__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__)
#define SECLAYER_INFO(fmt, ...) printf("\033[32m[Seclayer: %s:%d:%s:%s] " #fmt "\033[0m\r\n", __func__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__)

#define IS_OK 0




#endif
