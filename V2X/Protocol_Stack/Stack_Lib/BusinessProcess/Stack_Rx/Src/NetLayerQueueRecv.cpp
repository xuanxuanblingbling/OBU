#include "NetLayerQueueRecv.h"
//2020.07.03 WM add:加 extern
extern "C"
{
#include "wj_log.h"
}
#include "TBlockingQueue.h"

static TBlockingQueue<tRcvInfo *> NetLayerRecvQueue;

tRcvInfo *NetLayerMessageGetFromQueue()
{
	return NetLayerRecvQueue.DataGetFromQueue();
}

int NetLayerMessagePushInQueue(tRcvInfo *pdata)
{
	NetLayerRecvQueue.DataPushInQueue(pdata);

	// int nSta, nSize;
	// NetLayerRecvQueue.GetQueueStatus(nSta, nSize);
	// if (nSta == 1)
	// {
	// 	LogPrint(LOG_LEVEL_DEBUG, "Stack_Rx_Debug",
	// 			 "NetLayerQueueRecv nSta = %d  nSize = %d", nSta, nSize);
	// }
	return 0;
}
