#include "MsgLayerRecvQueue.h"
#include "TBlockingQueue.h"
extern "C"
{
#include "wj_log.h"
}

static TBlockingQueue<MSG_MessageType_st *> MsgLayerRecvQueue;

__attribute__((visibility("default"))) MSG_MessageType_st *MsgLayerMessageGetFromQueue()
{
    return MsgLayerRecvQueue.DataGetFromQueue();
    //return MsgLayerRecvQueue.DataGetFromQueueWait();
}

int MsgLayerMessagePushInQueue(MSG_MessageType_st *pdata)
{
    MsgLayerRecvQueue.DataPushInQueue(pdata);
    // int nSta, nSize;
    // MsgLayerRecvQueue.GetQueueStatus(nSta, nSize);
    // if (nSta == 1)
    // {
    //     LogPrint(LOG_LEVEL_DEBUG, "Stack_Rx_Debug",
    //              "MsgLayerRecvQueue nSta = %d  nSize = %d", nSta, nSize);
    // }
    return 0;
}
