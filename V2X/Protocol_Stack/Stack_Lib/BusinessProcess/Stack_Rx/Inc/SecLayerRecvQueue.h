#ifndef _SECURE_LAYER_RECV_QUEUE_H_
#define _SECURE_LAYER_RECV_QUEUE_H_
#include <thread>
#ifdef __cplusplus
extern "C"
{
#endif

#include "Port.h"

    // std::shared_ptr<tRcvInfo> SecureLayerMessageGetFromQueue();
    // int SecureLayerMessagePushInQueue(std::shared_ptr<tRcvInfo> pdata);

    tRcvInfo *SecureLayerMessageGetFromQueue();
    int SecureLayerMessagePushInQueue(tRcvInfo *pdata);

#ifdef __cplusplus
}
#endif

#endif