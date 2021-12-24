#include "TBlockingQueue.h"
//2020.07.03 WM add:加 extern
extern "C"
{
#include "wj_log.h"
#include "ConfigModuleRW.h"
}

#include "SecLayerRecvQueue.h"

//static TBlockingQueue<std::shared_ptr<tRcvInfo>> SecureLayerRecvQueue;
static TBlockingQueue<tRcvInfo *> SecureLayerRecvQueue;

//std::shared_ptr<tRcvInfo> SecureLayerMessageGetFromQueue()
tRcvInfo *SecureLayerMessageGetFromQueue()
{
	return SecureLayerRecvQueue.DataGetFromQueue();

	//判断是否接收
	// if ((ProtocolStackParamConfig.messageParamConfig.recvParamConfig.RecvSwitch != 1) ||
	// 	(MsgDiscardedRate < MSG_MAX_DiscardedRate))
	// {
	// 	//信号阻塞
	// 	return SecureLayerRecvQueue.DataGetFromQueue();
	// }
	// else
	// {
	// 	//信号阻塞+时间轮转
	// 	return SecureLayerRecvQueue.DataGetFromQueueWait();
	// }
}

//int SecureLayerMessagePushInQueue(std::shared_ptr<tRcvInfo> pdata)
int SecureLayerMessagePushInQueue(tRcvInfo *pdata)
{
	//SecureLayerRecvQueue.DataPushInSharePtrQueue(pdata);
	SecureLayerRecvQueue.DataPushInQueue(pdata);

	return 0;
}
