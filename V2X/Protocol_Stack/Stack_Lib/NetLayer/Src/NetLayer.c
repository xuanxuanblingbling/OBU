/*
 * NetLayer.c
 *
 *  Created on: Apr 8, 2020
 *      Author: wanijv2x
 */

#include "NetLayer.h"
#include "wj_log.h"
#include <arpa/inet.h>
#include "BusinessTool.h"
#include "Timer.h"

#define Layer2ID_MAX 16777214
#define Layer2ID_MIN 65537
static unsigned char SourceLayer2ID[3] = {0x00};
pthread_t th = 0;
static ST_OSA_TimerHndl hd;
static union sigval value;
static void TimerCallback(union sigval value)
{
	setSrandSourceLayer2ID(Layer2ID_MAX, Layer2ID_MIN, SourceLayer2ID, 3);
}
/**
 * @brief 程序启动后,自行调用此接口
 */
__attribute__((constructor)) static void so_init(void);

void so_init(void)
{
	setSrandSourceLayer2ID(Layer2ID_MAX, Layer2ID_MIN, SourceLayer2ID, 3);

	// if (0 != system("cv2x-config --get-v2x-status | grep rx_status"))
	// {
	//非AG15模组时，设置定时修改源层2id
	hd.period_s = 10;
	hd.timerid = NULL;
	hd.period_ms = 0;
	ST_OSA_timerCreate(&hd, TimerCallback, value);
	ST_OSA_timerStart(&hd);
	// }
}

/**************************************************
*名称： 适配层打包函数
*描述： 将待打包的网络层数据结构体按照网络层数据码流格式打包；如打包失败，则返回错误代码。
*参数：
*       dsmSend_rq		 [IN]        待打包的适配层数据结构体
*       pn8DstBuf        [OUT]       打包后的适配层数据码流
*       pn32DstBufSize   [OUT]       打包后的适配层数据码流长度
*返回值：0--成功；
*返回值：非0--错误号。
*说明：无
**************************************************/
int32_t Adapter_Encode(TDSMEncReq tDSMEncReq, SendDataInfo *ag15SendDataInfo)
{
	if (NULL == ag15SendDataInfo)
	{
		LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "Adapter_Encode Param is NULL");
		return -1;
	}

	unsigned char returnNum[3] = {0x00};
	//源层2id
	if ((tDSMEncReq.pExtension != NULL) && (tDSMEncReq.pExtension->layerIDChanged))
	{
		setSrandSourceLayer2ID(Layer2ID_MAX, Layer2ID_MIN, SourceLayer2ID, 3);
	}

	memcpy(ag15SendDataInfo->SourceLayer2ID, SourceLayer2ID, 3);

	//目标层2id
	setDestinationLayer2ID(tDSMEncReq.AID, returnNum);
	memcpy(&ag15SendDataInfo->DestinationLayer2ID, returnNum, 3);

	//pppp
	ag15SendDataInfo->pppp = setPPPP(tDSMEncReq.Priority);

	return 0;
}
/**************************************************
*名称： 适配层解包函数
*描述： 将底层的的数据按照适配层头的格式解析；如解析失败，则返回错误代码。
*参数：
*       pn8SrcBuf		    [IN]        底层推送过来的数据码流
*       pn32SrcBufSize      [IN]        底层推送过来的数据码流长度
*       pDsmpHdr            [OUT]       底层数据解析成的网络层结构体格式
*返回值：0--成功；
*返回值：非0--错误号。
*说明：无
**************************************************/
int32_t Adapter_Decode(RecvCallbackReturnInfo ag15CallbackReturnInfo, TDSMEncReq *pDsmpHdr)
{
	if (NULL == pDsmpHdr)
	{
		LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "Adapter_Decode Param is NULL");
		return -1;
	}
	//源层2id
	//目标层2id
	//pppp，此处PPPP接入层设为默认值，暂不使用
	//pDsmpHdr->Priority = setPriority(ag15CallbackReturnInfo.pppp);
	//由于接入层未提供消息优先级PPPP，此处使用网络层AID映射验签优先级
	pDsmpHdr->Priority = setPriorityFromNetAid(pDsmpHdr->AID);

	return 0;
}

/**************************************************
*名称： 网络层打包函数
*描述： 将待打包的网络层数据结构体按照网络层数据码流格式打包；如打包失败，则返回错误代码。
*参数：
*       dsmSend_rq		 [IN]        待打包的网络层数据结构体
*       pn8DstBuf        [OUT]       打包后的网络层数据码流
*       pn32DstBufSize   [OUT]       打包后的网络层数据码流长度
*返回值：0--成功；
*返回值：非0--错误号。
*说明：无
**************************************************/
__attribute__((visibility("default"))) int32_t NetLay_Encode(TDSMEncReq tDSMEncReq, int8_t *pn8DstBuf, int32_t *pn32DstBufSize)
{

	if (NULL == pn8DstBuf || NULL == pn32DstBufSize)
	{
		LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "NetLay_Encode Param is NULL");
		return -1;
	}

	int HdrLen = 0;
	char Hdr[MAX_DUMMY_PACKET_LEN] = {0};
	uint8_t IsHvExt = 0x00;
	uint8_t Version = 0x00;

	if ((tDSMEncReq.pExtension != NULL) && (tDSMEncReq.pExtension->u8ExtenNum != 0))
	{
		IsHvExt = 1;
	}
	else
	{
		IsHvExt = 0;
	}

	Version = (0xFF & DSMP_VERSION) << 5;
	Version |= (IsHvExt << 4);

	//Adapt Layer Protocol Type(该字段为适配层协议类型，暂放在这儿)
	Hdr[HdrLen++] = 0x04;

	//DSMP Version(3 bits), Option Indicator(1 bit) and reserved(4 bits --- 0000)
	Hdr[HdrLen++] = Version;

	if (IsHvExt == 1)
	{
		Hdr[HdrLen++] = tDSMEncReq.pExtension->u8ExtenNum;
		uint32_t u32i = 0;
		for (u32i = 0; u32i < tDSMEncReq.pExtension->u8ExtenNum; u32i++)
		{
			Hdr[HdrLen++] = tDSMEncReq.pExtension->extenSionCommn[u32i].ElementID;
			Hdr[HdrLen++] = tDSMEncReq.pExtension->extenSionCommn[u32i].ByteLength;
			memcpy(&Hdr[HdrLen], tDSMEncReq.pExtension->extenSionCommn[u32i].ExtensionInfo,
				   tDSMEncReq.pExtension->extenSionCommn[u32i].ByteLength);
			HdrLen += tDSMEncReq.pExtension->extenSionCommn[u32i].ByteLength;
		}
	}

	//LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "DSM AID:%d", tDSMEncReq.AID);
	//AID Type
	if (tDSMEncReq.AID <= 0x7F)
	{
		//1 Byte
		Hdr[HdrLen++] = (char)tDSMEncReq.AID;
	}
	else
	{
		Hdr[HdrLen++] = ((tDSMEncReq.AID + 0x7F80) >> 8) & 0xFF;
		Hdr[HdrLen++] = (tDSMEncReq.AID + 0x7F80);
	}

	//Data Length
	short Len = htons(tDSMEncReq.Length);
	memcpy(&Hdr[HdrLen], &Len, sizeof(short));
	HdrLen += sizeof(uint16_t);

	//Add DSM Data pDSMPayLoad in send pBuf
	memcpy(&Hdr[HdrLen], tDSMEncReq.Data, tDSMEncReq.Length);
	HdrLen += tDSMEncReq.Length;

	*pn32DstBufSize = HdrLen;
	memcpy(pn8DstBuf, Hdr, HdrLen);

	return 0;
}
/**************************************************
*名称： 网络层解包函数
*描述： 将底层的的数据按照网络层头的格式解析；如解析失败，则返回错误代码。
*参数：
*       pn8SrcBuf		    [IN]        底层推送过来的数据码流
*       pn32SrcBufSize      [IN]        底层推送过来的数据码流长度
*       pDsmpHdr            [OUT]       底层数据解析成的网络层结构体格式
*返回值：0--成功；
*返回值：非0--错误号。
*说明：无
**************************************************/
__attribute__((visibility("default"))) int32_t NetLay_Decode(int8_t *pn8SrcBuf, int32_t *pn32SrcBufSize, TDSMEncReq *pDsmpHdr)
{
	if (NULL == pn8SrcBuf || NULL == pn32SrcBufSize || NULL == pDsmpHdr)
	{
		LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "NetLay_Decode error：Param is NULL");
		return -1;
	}
	if (pn8SrcBuf[0] != 0x04)
	{
		LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "NetLay_Decode error：pn8SrcBuf[0] != 0x04,pn32SrcBufSize = %d", *pn32SrcBufSize);
		return -1;
	}

	int nIndex = 1;

	//get DSMP Version and Indicator
	uint8_t Temp_MultInfo = pn8SrcBuf[nIndex++];
	uint8_t Version = (Temp_MultInfo & 0xFF) >> 5;
	uint8_t IsHvExt = (Temp_MultInfo & 0x10) >> 4;

	if (IsHvExt == 1)
	{
		pDsmpHdr->pExtension = calloc(1, sizeof(tExtenSionCommn_st));
		if (NULL == pDsmpHdr->pExtension)
		{
			LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "NetLay_Decode error：pDsmpHdr->pExtension is NULL");
			return -1;
		}
		pDsmpHdr->pExtension->u8ExtenNum = pn8SrcBuf[nIndex++];
		uint32_t u32i = 0;
		for (u32i = 0; u32i < pDsmpHdr->pExtension->u8ExtenNum; u32i++)
		{
			pDsmpHdr->pExtension->extenSionCommn[u32i].ElementID = pn8SrcBuf[nIndex++];
			pDsmpHdr->pExtension->extenSionCommn[u32i].ByteLength = pn8SrcBuf[nIndex++];
			memcpy(pDsmpHdr->pExtension->extenSionCommn[u32i].ExtensionInfo, &pn8SrcBuf[nIndex],
				   pDsmpHdr->pExtension->extenSionCommn[u32i].ByteLength);
			nIndex += pDsmpHdr->pExtension->extenSionCommn[u32i].ByteLength;
		}
	}
	else
	{
		pDsmpHdr->pExtension = NULL;
	}

	//get AID Type
	uint8_t Temp_AIDJudege = pn8SrcBuf[nIndex++];
	if (Temp_AIDJudege <= 0x7F)
	{
		pDsmpHdr->AID = Temp_AIDJudege;
	}
	else
	{
		//此处可能因为有符号与无符号字节的差异，造成获取异常AID.
		//char类型，有符号单字节数字，直接取值可能会取到符号位。所以替换成&0xFF，直接取低8位即可
		pDsmpHdr->AID = (((Temp_AIDJudege & 0xFF) << 8) | (pn8SrcBuf[nIndex++] & 0xFF)) - 0x7F80;
	}

	int ret = NetLay_AIDCheck(pDsmpHdr->AID);
	if (ret != 0)
	{
		LogPrint(LOG_LEVEL_WARN, "Stack_Rx_Warn", "NetLay_AIDCheck nAid fail: ret = %d,nAid = %d", ret, pDsmpHdr->AID);
		return -1;
	}

	//get Data Length
	short *pLen = (short *)&pn8SrcBuf[nIndex];
	pDsmpHdr->Length = ntohs(*pLen);
	nIndex += 2;

	//get Data Buffer
	if ((nIndex + pDsmpHdr->Length - 1) > *pn32SrcBufSize)
	{
		LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "NetLay_Decode error：nIndex: %d, pDsmpHdr->Length: %d, pn32SrcBufSize: %d", nIndex, pDsmpHdr->Length, *pn32SrcBufSize);
		goto ERROR;
	}

	pDsmpHdr->Data = calloc(1, pDsmpHdr->Length);
	if (NULL == pDsmpHdr->Data)
	{
		LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "NetLay_Decode error：pDsmpHdr->Data is NULL");
		goto ERROR;
	}
	memcpy(pDsmpHdr->Data, &pn8SrcBuf[nIndex], pDsmpHdr->Length);

	//映射优先级
	pDsmpHdr->Priority = setPriorityFromNetAid(pDsmpHdr->AID);

#if NETLAYER_PRINTLOG
	LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "DSM Version:%d,\nDSMP_OptionIdr:%d,\nDSM AID:%d,\nLength:%d",
			 pDsmpHdr->Version, pDsmpHdr->IsHvExt, pDsmpHdr->AID,
			 pDsmpHdr->Length);
#endif

	return 0;
ERROR:
	return -1;
}
