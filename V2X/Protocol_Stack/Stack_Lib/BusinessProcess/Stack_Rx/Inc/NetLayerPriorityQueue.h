#ifndef _NET_LAYER_PRIORITY_QUEUE_H_
#define _NET_LAYER_PRIORITY_QUEUE_H_
#include <thread>
#ifdef __cplusplus
extern "C"
{
#endif

#include "Port.h"

    // __attribute__((visibility("default"))) std::shared_ptr<tRcvInfo> GetDataFromNetLayerPriorityQueue();
    // int PushDataInNetLayerPriorityQueue(std::shared_ptr<tRcvInfo> pdata);

    __attribute__((visibility("default"))) tRcvInfo *GetDataFromNetLayerPriorityQueue();
    int PushDataInNetLayerPriorityQueue(tRcvInfo *pdata);

#ifdef __cplusplus
}
#endif

#endif