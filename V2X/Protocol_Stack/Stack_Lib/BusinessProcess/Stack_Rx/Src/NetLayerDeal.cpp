/*
 * NetLayerDeal.c
 *
 *  Created on: May 17, 2020
 *      Author: wanijv2x
 */
#include "NetLayerDeal.h"
//#include "NetLayerQueueRecv.h"
//#include "NetLayerQueue.h"
#include "NetLayerPriorityQueue.h"
#include "DataSet.h"
#include "StackCodec.h"
#include "StateMonitor.h"
#include "MemoryBlock.h"
extern "C"
{
#include "wj_log.h"
#include "ConfigModuleRW.h"
#include "Timer.h"

	uint64_t u64InTime = 0;
	uint64_t u64InTime1 = 0;
}
#include <thread>

class CTDSMEncReq
{
public:
	CTDSMEncReq()
	{
		pDsmInfo = (TDSMEncReq *)calloc(1, sizeof(TDSMEncReq));
		//pDsmInfo->Data = (int8_t *)calloc(1, MAX_DUMMY_PACKET_LEN);
		//pDsmInfo->pExtension = (tExtenSionCommn_st *)calloc(1, sizeof(tExtenSionCommn_st));
	}
	~CTDSMEncReq()
	{

		if (pDsmInfo->Data != NULL)
		{
			free(pDsmInfo->Data);
			pDsmInfo->Data = NULL;
		}
		if (NULL != pDsmInfo->pExtension)
		{
			free(pDsmInfo->pExtension);
			pDsmInfo->pExtension = NULL;
		}
		if (pDsmInfo != NULL)
		{
			free(pDsmInfo);
			pDsmInfo = NULL;
		}
	}

public:
	TDSMEncReq *pDsmInfo;
};

//callback registered to AG15 layer to recv data
__attribute__((visibility("default"))) void MsgRx_CallBack(RecvCallbackReturnInfo ag15CallbackReturnInfo)
{
	//判断是否接收
	if (ProtocolStackParamConfig.messageParamConfig.recvParamConfig.RecvSwitch != 1)
	{
		return;
	}
	if (ag15CallbackReturnInfo.pnRecvBufSize == 0)
	{
		return;
	}

	//make_shared比calloc慢一点，此处暂不使用
	std::shared_ptr<CTDSMEncReq> pDsmInfo_Ptr = std::make_shared<CTDSMEncReq>();
	if ((NULL == pDsmInfo_Ptr) || (NULL == pDsmInfo_Ptr->pDsmInfo))
	{
		LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "pDsmInfo calloc error! ");
		return;
	}
	TDSMEncReq *pDsmInfo = pDsmInfo_Ptr->pDsmInfo;

	// TDSMEncReq *pDsmInfo = (TDSMEncReq *)calloc(1, sizeof(TDSMEncReq));
	// if (pDsmInfo == NULL)
	// {
	// 	return;
	// }

	UpdateNetlayerRxDataNum();
	CurrentCBR = ag15CallbackReturnInfo.Current_CBR;
	++NetRecvStart;
	int ret = NetLay_Decode((int8_t *)ag15CallbackReturnInfo.p_cRecvBuf, &ag15CallbackReturnInfo.pnRecvBufSize, pDsmInfo);
	if (ret != 0)
	{
		NetRecvError++;
		goto EXIT;
	}

	Adapter_Decode(ag15CallbackReturnInfo, pDsmInfo);

	//transparent transmit data
	if (pDsmInfo->AID == ProtocolStackParamConfig.DSMPParamConfig.PassMessageAID)
	{
		++NetRecvError;
		std::shared_ptr<MemoryBlock> block = std::make_shared<MemoryBlock>(MAX_DUMMY_PACKET_LEN);
		if ((NULL == block) || (NULL == block->buf))
		{
			LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "pbuff is NULL");
			goto EXIT;
		}
		ret = RawDataParse(ag15CallbackReturnInfo.p_cRecvBuf, ag15CallbackReturnInfo.pnRecvBufSize, (char *)block->buf, &block->size);
		if (ret == 0)
		{
			TransparentTransmitDataPushInQueue((unsigned char *)block->buf, block->size);
		}
	}
	else
	{
		//std::shared_ptr<tRcvInfo> pRcvInfo = std::make_shared<tRcvInfo>();
		tRcvInfo *pRcvInfo = (tRcvInfo *)calloc(1, sizeof(tRcvInfo));
		if (NULL == pRcvInfo)
		{
			LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "pRcvInfo calloc error! ");
			goto EXIT;
		}

		pRcvInfo->nTxAid = pDsmInfo->AID;
		//从适配层的映射关系解析优先级
		pRcvInfo->priority = pDsmInfo->Priority;
		pRcvInfo->u64InTime = st_Timestamp_now(3);

		if (NULL != pDsmInfo->pExtension)
		{
			pRcvInfo->extension.u8ExtenNum = pDsmInfo->pExtension->u8ExtenNum;
			uint32_t u32i = 0;
			for (u32i = 0; u32i < pRcvInfo->extension.u8ExtenNum; u32i++)
			{

				pRcvInfo->extension.extenSionCommn[u32i].ElementID = pDsmInfo->pExtension->extenSionCommn[u32i].ElementID;
				pRcvInfo->extension.extenSionCommn[u32i].ByteLength = pDsmInfo->pExtension->extenSionCommn[u32i].ByteLength;
				memcpy(pRcvInfo->extension.extenSionCommn[u32i].ExtensionInfo,
					   pDsmInfo->pExtension->extenSionCommn[u32i].ExtensionInfo, pDsmInfo->pExtension->extenSionCommn[u32i].ByteLength);
			}
		}

		if (pDsmInfo->Length < MAX_DUMMY_PACKET_LEN && pDsmInfo->Length > 0)
		{
			++NetRecvEnd;
			pRcvInfo->nBuffLen = pDsmInfo->Length;
			memcpy(pRcvInfo->acBuff, pDsmInfo->Data, pDsmInfo->Length);
			//NetLayerMessagePushInQueue(pRcvInfo);
			PushDataInNetLayerPriorityQueue(pRcvInfo);
			//PushDataIntoNetLayerPriorityQueue2(pRcvInfo);
		}
		else
		{
			++NetRecvError;
		}
	}
EXIT:
	// if (pDsmInfo != NULL)
	// {
	// 	if (NULL != pDsmInfo->Data)
	// 	{
	// 		free(pDsmInfo->Data);
	// 		pDsmInfo->Data = NULL;
	// 	}
	// 	if (NULL != pDsmInfo->pExtension)
	// 	{
	// 		free(pDsmInfo->pExtension);
	// 		pDsmInfo->pExtension = NULL;
	// 	}
	// 	free(pDsmInfo);
	// 	pDsmInfo = NULL;
	// }
	return;
}
