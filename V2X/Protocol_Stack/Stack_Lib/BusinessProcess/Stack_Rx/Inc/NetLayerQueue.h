#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_
#include <thread>
#ifdef __cplusplus
extern "C"
{
#endif

#include "Port.h"
#define QUEUE_SIZE 32
    int PushDataIntoNetLayerPriorityQueue2(std::shared_ptr<tRcvInfo> pdata);
    __attribute__((visibility("default"))) std::shared_ptr<tRcvInfo> GetDataFromNetLayerPriorityQueue2();

#ifdef __cplusplus
}
#endif

#endif