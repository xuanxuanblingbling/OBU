#ifndef _NET_LAYER_QUEUE_RECV_H_
#define _NET_LAYER_QUEUE_RECV_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "Port.h"

tRcvInfo* NetLayerMessageGetFromQueue();
int NetLayerMessagePushInQueue(tRcvInfo *pdata);


#ifdef __cplusplus
}
#endif

#endif
