#include <pthread.h>
#include "SecLayerDeal.h"
#include "SecLayerRecvQueue.h"
//#include "NetLayerQueueRecv.h"
//#include "NetLayerQueue.h"
#include "NetLayerPriorityQueue.h"
#include "SecLayerIntfCom.h"
#include "StateMonitor.h"

extern "C"
{
#include "wj_log.h"
#include "ConfigModuleRW.h"
}

void *SecLayer_Recv_ThreadProcFunc(void *pArg)
{
	int ret = 0;
	MsgLayData_st MsgLayData;
	memset(&MsgLayData, 0x00, sizeof(MsgLayData_st));
	//进入接口后，执行5000次轮询，接口调用时间5s
	int i = 0;
	for (i = 0; i < SecCyclesNum; i++)
	{
		//tRcvInfo *pRcvInfo = NetLayerMessageGetFromQueue();
		tRcvInfo *pRcvInfo = GetDataFromNetLayerPriorityQueue();
		//std::shared_ptr<tRcvInfo> pRcvInfo = GetDataFromNetLayerPriorityQueue2();
		if (pRcvInfo == NULL)
		{
			continue;
		}
		++SecRecvStart;
		SecDiscardedRate = (double)(((double)SecRecvDis) / (double)NetRecvEnd * 100);

		if ((ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_FOUR ||
			 ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_NEW_FOUR ||
			 ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_TWO) &&
			((ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch == 3) ||
			 (ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch == 1)))
		{
			//信大捷安验签将AID作为输入
			MsgLayData.nAID = pRcvInfo->nTxAid;
			MsgLayData.n32MsgLayDataLen = MAX_DUMMY_PACKET_LEN;

			if (pVerifySecureComplete != NULL)
			{
				ret = pVerifySecureComplete((unsigned char *)pRcvInfo->acBuff, pRcvInfo->nBuffLen, &MsgLayData);
				if (ret != 0)
				{
					++SecRecvError;
					LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "SecLay_Decode() Error,AID = %d,ret = %d ", pRcvInfo->nTxAid, ret);
					free(pRcvInfo);
					continue;
				}
				UpdateSeclayerRxDataNum();
			}

			pRcvInfo->nTxAid = MsgLayData.nAID;
			pRcvInfo->nBuffLen = MsgLayData.n32MsgLayDataLen;
			memcpy(pRcvInfo->acBuff, MsgLayData.pu8MsgLayData, MsgLayData.n32MsgLayDataLen);
		}
		++SecRecvEnd;
		SecureLayerMessagePushInQueue(pRcvInfo);
	}

	return NULL;
}

void *SecLayer_Recv_ThreadProc(void *pArg)
{
	int ret = 0;
	MsgLayData_st MsgLayData;
	memset(&MsgLayData, 0x00, sizeof(MsgLayData_st));
	LogPrint(LOG_LEVEL_DEBUG, "Stack_Rx_Debug", "SecLayer_Recv_ThreadProc() %d  ", pthread_self());
	while (1)
	{
		//tRcvInfo *pRcvInfo = NetLayerMessageGetFromQueue();
		tRcvInfo *pRcvInfo = GetDataFromNetLayerPriorityQueue();
		//std::shared_ptr<tRcvInfo> pRcvInfo = GetDataFromNetLayerPriorityQueue2();
		if (pRcvInfo == NULL)
		{
			continue;
		}
		++SecRecvStart;
		SecDiscardedRate = (double)(((double)SecRecvDis) / (double)NetRecvEnd * 100);

		if ((ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_FOUR ||
			 ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_NEW_FOUR ||
			 ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_TWO) &&
			((ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch == 3) ||
			 (ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch == 1)))
		{
			//信大捷安验签将AID作为输入
			MsgLayData.nAID = pRcvInfo->nTxAid;
			MsgLayData.n32MsgLayDataLen = MAX_DUMMY_PACKET_LEN;

			if (pVerifySecureComplete != NULL)
			{
				ret = pVerifySecureComplete((unsigned char *)pRcvInfo->acBuff, pRcvInfo->nBuffLen, &MsgLayData);
				if (ret != 0)
				{
					++SecRecvError;
					LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "SecLay_Decode() Error,AID = %d,ret = %d ", pRcvInfo->nTxAid, ret);
					free(pRcvInfo);
					continue;
				}
				UpdateSeclayerRxDataNum();
			}

			pRcvInfo->nTxAid = MsgLayData.nAID;
			pRcvInfo->nBuffLen = MsgLayData.n32MsgLayDataLen;
			memcpy(pRcvInfo->acBuff, MsgLayData.pu8MsgLayData, MsgLayData.n32MsgLayDataLen);
		}
		++SecRecvEnd;
		SecureLayerMessagePushInQueue(pRcvInfo);
	}
	(void)pthread_exit(NULL);
}
