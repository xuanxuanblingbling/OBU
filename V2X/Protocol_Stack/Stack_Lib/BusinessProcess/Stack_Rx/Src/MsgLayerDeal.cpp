#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include "MsgLayerDeal.h"
#include "SecLayerRecvQueue.h"
#include "MsgLayerRecvQueue.h"
#include "PublicMsg.h"
#include "wj_Message_com.h"
#include "StateMonitor.h"

extern "C"
{
#include "wj_log.h"
#include "BusinessTool.h"
#include "ConfigModuleRW.h"
}

/*二期消息集接口*/
extern WJV2_UperEncOrDecMain_BACK wjv2_UperEncOrDecMain;
/*三跨消息集接口*/
extern WJV3_UperEncOrDecMain_BACK wjv3_UperEncOrDecMain;
/*四跨消息集接口*/
extern WJV4_UperEncOrDecMain_BACK wjv4_UperEncOrDecMain;
/*新四跨消息集接口*/
extern WJVN4_UperEncOrDecMain_BACK wjvn4_UperEncOrDecMain;

void *ThreadProcMsgRecvFunc(void *pArg)
{
    int ret = 0;
    int messageid = 0;
    WJV4_UperData pstruUperDataV4;
    memset(&pstruUperDataV4, 0x00, sizeof(WJV4_UperData));

    WJV3_UperData pstruUperDataV3;
    memset(&pstruUperDataV3, 0x00, sizeof(WJV3_UperData));

    WJV2_UperData pstruUperDataV2;
    memset(&pstruUperDataV2, 0x00, sizeof(WJV2_UperData));

    WJVN4_UperData pstruUperDataVN4;
    memset(&pstruUperDataVN4, 0x00, sizeof(WJVN4_UperData));

    //进入接口后，执行5000次轮询，接口调用时间10s
    int i = 0;
    for (i = 0; i < MsgCyclesNum; i++)
    {
        //std::shared_ptr<tRcvInfo> pRcvInfo = SecureLayerMessageGetFromQueue();
        tRcvInfo *pRcvInfo = SecureLayerMessageGetFromQueue();
        if (pRcvInfo == NULL)
        {
            continue;
        }
        ++MsgRecvStart;
        MsgDiscardedRate = (double)(((double)SecRecvEnd - (double)MsgRecvStart) / (double)SecRecvEnd * 100);

        MSG_MessageType_st_ptr msg_ptr = (MSG_MessageType_st_ptr)calloc(1, sizeof(MSG_MessageType_st));
        if (NULL == msg_ptr)
        {
            ++MsgRecvError;
            free(pRcvInfo);
            continue;
        }

        //向应用层推送原始码流
        if (pRcvInfo->nBuffLen > sizeof(msg_ptr->wj_UperData.pu8buff))
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Rx_Debug", "The length is too large，pRcvInfo->nBuffLen = %d", pRcvInfo->nBuffLen);
            msg_ptr->wj_UperData.u32Len = sizeof(msg_ptr->wj_UperData.pu8buff);
        }
        else
        {
            msg_ptr->wj_UperData.u32Len = (uint32_t)pRcvInfo->nBuffLen;
        }
        memcpy(msg_ptr->wj_UperData.pu8buff, (uint8_t *)pRcvInfo->acBuff, msg_ptr->wj_UperData.u32Len);

        if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_FOUR &&
            NULL != wjv4_UperEncOrDecMain)
        {
            pstruUperDataV4.u32Len = (uint32_t)pRcvInfo->nBuffLen;
            pstruUperDataV4.pu8buff = (uint8_t *)pRcvInfo->acBuff;
            ret = wjv4_UperEncOrDecMain((WJV4_UperData *)&pstruUperDataV4, &(msg_ptr->msgtype.MessageFour), MSGV4_MessageFrame_UperDecode);
            if (!ret)
            {
                ++MsgRecvError;
                LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "MsgLay_Decode() Error,AID = %d,ret = %d ", pRcvInfo->nTxAid, ret);
                free(msg_ptr);
                free(pRcvInfo);
                continue;
            }
            msg_ptr->messageType = MSG_MessageType_ID_Four;
            //使用AID映射id时，各类消息的AID不能一致，否则无法识别id
            messageid = getMessageidFromAID(pRcvInfo->nTxAid, (int)msg_ptr->msgtype.MessageFour.enumMessageFrameType);
            if (messageid < 0)
            {
                LogPrint(LOG_LEVEL_WARN, "Stack_Rx_Warn", "MsgLay_GetMessageid() Warn,AID = %d,Messageid = %d", pRcvInfo->nTxAid,
                         (int)msg_ptr->msgtype.MessageFour.enumMessageFrameType);
                messageid = (int)msg_ptr->msgtype.MessageFour.enumMessageFrameType;
            }
            msg_ptr->msgtype.MessageFour.enumMessageFrameType = (WJV4_ENUM_MessageFrame_PR)messageid;
        }
        else if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_NEW_FOUR &&
                 NULL != wjvn4_UperEncOrDecMain)
        {
            pstruUperDataVN4.u32Len = (uint32_t)pRcvInfo->nBuffLen;
            pstruUperDataVN4.pu8buff = (uint8_t *)pRcvInfo->acBuff;
            ret = wjvn4_UperEncOrDecMain((WJVN4_UperData *)&pstruUperDataVN4, &(msg_ptr->msgtype.MessageNewFour), MSGVN4_MessageFrame_UperDecode);
            if (!ret)
            {
                ++MsgRecvError;
                LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "MsgLay_Decode() Error,AID = %d,ret = %d ", pRcvInfo->nTxAid, ret);
                free(msg_ptr);
                free(pRcvInfo);
                continue;
            }
            msg_ptr->messageType = MSG_MessageType_ID_NEW_Four;
            //使用AID映射id时，各类消息的AID不能一致，否则无法识别id
            messageid = getMessageidFromAID(pRcvInfo->nTxAid, (int)msg_ptr->msgtype.MessageNewFour.enumMessageFrameType);
            if (messageid < 0)
            {
                LogPrint(LOG_LEVEL_WARN, "Stack_Rx_Warn", "MsgLay_GetMessageid() Warn,AID = %d,Messageid = %d", pRcvInfo->nTxAid,
                         (int)msg_ptr->msgtype.MessageNewFour.enumMessageFrameType);
                messageid = (int)msg_ptr->msgtype.MessageNewFour.enumMessageFrameType;
                free(msg_ptr);
                free(pRcvInfo);
                continue;
            }
            msg_ptr->msgtype.MessageNewFour.enumMessageFrameType = (WJVN4_ENUM_MessageFrame_PR)messageid;
        }
        else if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_THREE &&
                 NULL != wjv3_UperEncOrDecMain)
        {
            pstruUperDataV3.u32Len = (uint32_t)pRcvInfo->nBuffLen;
            pstruUperDataV3.pu8buff = (uint8_t *)pRcvInfo->acBuff;
            ret = wjv3_UperEncOrDecMain((WJV3_UperData *)&pstruUperDataV3, &(msg_ptr->msgtype.MessageThree), MSGV3_MessageFrame_UperDecode);
            if (!ret)
            {
                ++MsgRecvError;
                LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "MsgLay_Decode() Error,AID = %d,ret = %d ", pRcvInfo->nTxAid, ret);
                free(msg_ptr);
                free(pRcvInfo);
                continue;
            }
            messageid = msg_ptr->msgtype.MessageThree.enumMessageFrameType;
            msg_ptr->messageType = MSG_MessageType_ID_Three;
        }
        else
        {
            if (NULL != wjv2_UperEncOrDecMain)
            {
                pstruUperDataV2.u32Len = (uint32_t)pRcvInfo->nBuffLen;
                pstruUperDataV2.pu8buff = (uint8_t *)pRcvInfo->acBuff;
                ret = wjv2_UperEncOrDecMain((WJV2_UperData *)&pstruUperDataV2, &(msg_ptr->msgtype.MessageTwo), MSGV2_MessageFrame_UperDecode);
                if (!ret)
                {
                    ++MsgRecvError;
                    LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "MsgLay_Decode() Error,AID = %d,ret = %d ", pRcvInfo->nTxAid, ret);
                    free(msg_ptr);
                    free(pRcvInfo);
                    continue;
                }
            }

            msg_ptr->messageType = MSG_MessageType_ID_Two;
            //使用AID映射id时，各类消息的AID不能一致，否则无法识别id
            if (msg_ptr->msgtype.MessageTwo.enumMessageFrameType == MSGV2_MessageFrame_PR_msgFrameExt)
            {
                messageid = msg_ptr->msgtype.MessageTwo.uniUperMsg.struFrameExt.enumpresent;
            }
            else
            {
                messageid = getMessageidFromAID(pRcvInfo->nTxAid, (int)msg_ptr->msgtype.MessageTwo.enumMessageFrameType);
                if (messageid < 0)
                {
                    LogPrint(LOG_LEVEL_WARN, "Stack_Rx_Warn", "MsgLay_GetMessageid() Warn,AID = %d,Messageid = %d", pRcvInfo->nTxAid,
                             (int)msg_ptr->msgtype.MessageTwo.enumMessageFrameType);
                    messageid = (int)msg_ptr->msgtype.MessageTwo.enumMessageFrameType;
                }
                msg_ptr->msgtype.MessageTwo.enumMessageFrameType = (WJV2_ENUM_MessageFrame_PR)messageid;
            }
        }

        //网络层扩展域
        if (pRcvInfo->extension.u8ExtenNum > 0)
        {
            msg_ptr->extension.u8ExtenNum = pRcvInfo->extension.u8ExtenNum;
            uint32_t u32i = 0;
            for (u32i = 0; u32i < msg_ptr->extension.u8ExtenNum; u32i++)
            {
                msg_ptr->extension.extenSionCommn[u32i].ElementID = pRcvInfo->extension.extenSionCommn[u32i].ElementID;
                msg_ptr->extension.extenSionCommn[u32i].ByteLength = pRcvInfo->extension.extenSionCommn[u32i].ByteLength;
                memcpy(msg_ptr->extension.extenSionCommn[u32i].ExtensionInfo,
                       pRcvInfo->extension.extenSionCommn[u32i].ExtensionInfo, pRcvInfo->extension.extenSionCommn[u32i].ByteLength);
            }
        }

        ++MsgRecvEnd;
        UpdateMsglayerRxDataNum();
        UpdateMsglayerRxDataHelper(messageid);
        MsgLayerMessagePushInQueue(msg_ptr);
        if (pRcvInfo != NULL)
        {
            free(pRcvInfo);
        }
    }

    return NULL;
}

void *ThreadProcMsgRecv(void *pArg)
{
    LogPrint(LOG_LEVEL_DEBUG, "Stack_Rx_Debug", "ThreadProcMsgRecv() loop is start %d  ", pthread_self());
    int ret = 0;
    int messageid = 0;
    WJV4_UperData pstruUperDataV4;
    memset(&pstruUperDataV4, 0x00, sizeof(WJV4_UperData));

    WJV3_UperData pstruUperDataV3;
    memset(&pstruUperDataV3, 0x00, sizeof(WJV3_UperData));

    WJV2_UperData pstruUperDataV2;
    memset(&pstruUperDataV2, 0x00, sizeof(WJV2_UperData));

    WJVN4_UperData pstruUperDataVN4;
    memset(&pstruUperDataVN4, 0x00, sizeof(WJVN4_UperData));

    while (1)
    {
        //std::shared_ptr<tRcvInfo> pRcvInfo = SecureLayerMessageGetFromQueue();
        tRcvInfo *pRcvInfo = SecureLayerMessageGetFromQueue();
        if (pRcvInfo == NULL)
        {
            continue;
        }
        ++MsgRecvStart;
        MsgDiscardedRate = (double)(((double)SecRecvEnd - (double)MsgRecvStart) / (double)SecRecvEnd * 100);

        MSG_MessageType_st_ptr msg_ptr = (MSG_MessageType_st_ptr)calloc(1, sizeof(MSG_MessageType_st));
        if (NULL == msg_ptr)
        {
            ++MsgRecvError;
            free(pRcvInfo);
            continue;
        }

        //向应用层推送原始码流
        if (pRcvInfo->nBuffLen > sizeof(msg_ptr->wj_UperData.pu8buff))
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Rx_Debug", "The length is too large，pRcvInfo->nBuffLen = %d", pRcvInfo->nBuffLen);
            msg_ptr->wj_UperData.u32Len = sizeof(msg_ptr->wj_UperData.pu8buff);
        }
        else
        {
            msg_ptr->wj_UperData.u32Len = (uint32_t)pRcvInfo->nBuffLen;
        }
        memcpy(msg_ptr->wj_UperData.pu8buff, (uint8_t *)pRcvInfo->acBuff, msg_ptr->wj_UperData.u32Len);

        if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_FOUR &&
            NULL != wjv4_UperEncOrDecMain)
        {
            pstruUperDataV4.u32Len = (uint32_t)pRcvInfo->nBuffLen;
            pstruUperDataV4.pu8buff = (uint8_t *)pRcvInfo->acBuff;
            ret = wjv4_UperEncOrDecMain((WJV4_UperData *)&pstruUperDataV4, &(msg_ptr->msgtype.MessageFour), MSGV4_MessageFrame_UperDecode);
            if (!ret)
            {
                ++MsgRecvError;
                LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "MsgLay_Decode() Error,AID = %d,ret = %d ", pRcvInfo->nTxAid, ret);
                free(msg_ptr);
                free(pRcvInfo);
                continue;
            }
            msg_ptr->messageType = MSG_MessageType_ID_Four;
            //使用AID映射id时，各类消息的AID不能一致，否则无法识别id
            messageid = getMessageidFromAID(pRcvInfo->nTxAid, (int)msg_ptr->msgtype.MessageFour.enumMessageFrameType);
            if (messageid < 0)
            {
                LogPrint(LOG_LEVEL_WARN, "Stack_Rx_Warn", "MsgLay_GetMessageid() Warn,AID = %d,Messageid = %d", pRcvInfo->nTxAid,
                         (int)msg_ptr->msgtype.MessageFour.enumMessageFrameType);
                messageid = (int)msg_ptr->msgtype.MessageFour.enumMessageFrameType;
            }
            msg_ptr->msgtype.MessageFour.enumMessageFrameType = (WJV4_ENUM_MessageFrame_PR)messageid;
        }
        else if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_NEW_FOUR &&
                 NULL != wjvn4_UperEncOrDecMain)
        {
            pstruUperDataVN4.u32Len = (uint32_t)pRcvInfo->nBuffLen;
            pstruUperDataVN4.pu8buff = (uint8_t *)pRcvInfo->acBuff;
            ret = wjvn4_UperEncOrDecMain((WJVN4_UperData *)&pstruUperDataVN4, &(msg_ptr->msgtype.MessageNewFour), MSGVN4_MessageFrame_UperDecode);
            if (!ret)
            {
                ++MsgRecvError;
                LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "MsgLay_Decode() Error,AID = %d,ret = %d ", pRcvInfo->nTxAid, ret);
                free(msg_ptr);
                free(pRcvInfo);
                continue;
            }
            msg_ptr->messageType = MSG_MessageType_ID_NEW_Four;
            //使用AID映射id时，各类消息的AID不能一致，否则无法识别id
            messageid = getMessageidFromAID(pRcvInfo->nTxAid, (int)msg_ptr->msgtype.MessageNewFour.enumMessageFrameType);
            if (messageid < 0)
            {
                LogPrint(LOG_LEVEL_WARN, "Stack_Rx_Warn", "MsgLay_GetMessageid() Warn,AID = %d,Messageid = %d", pRcvInfo->nTxAid,
                         (int)msg_ptr->msgtype.MessageNewFour.enumMessageFrameType);
                messageid = (int)msg_ptr->msgtype.MessageNewFour.enumMessageFrameType;
            }
            msg_ptr->msgtype.MessageNewFour.enumMessageFrameType = (WJVN4_ENUM_MessageFrame_PR)messageid;
        }
        else if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == MSG_MESSAGETYPE_ID_THREE &&
                 NULL != wjv3_UperEncOrDecMain)
        {
            pstruUperDataV3.u32Len = (uint32_t)pRcvInfo->nBuffLen;
            pstruUperDataV3.pu8buff = (uint8_t *)pRcvInfo->acBuff;
            ret = wjv3_UperEncOrDecMain((WJV3_UperData *)&pstruUperDataV3, &(msg_ptr->msgtype.MessageThree), MSGV3_MessageFrame_UperDecode);
            if (!ret)
            {
                ++MsgRecvError;
                LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "MsgLay_Decode() Error,AID = %d,ret = %d ", pRcvInfo->nTxAid, ret);
                free(msg_ptr);
                free(pRcvInfo);
                continue;
            }
            messageid = msg_ptr->msgtype.MessageThree.enumMessageFrameType;
            msg_ptr->messageType = MSG_MessageType_ID_Three;
        }
        else
        {
            if (NULL != wjv2_UperEncOrDecMain)
            {
                pstruUperDataV2.u32Len = (uint32_t)pRcvInfo->nBuffLen;
                pstruUperDataV2.pu8buff = (uint8_t *)pRcvInfo->acBuff;
                ret = wjv2_UperEncOrDecMain((WJV2_UperData *)&pstruUperDataV2, &(msg_ptr->msgtype.MessageTwo), MSGV2_MessageFrame_UperDecode);
                if (!ret)
                {
                    ++MsgRecvError;
                    LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "MsgLay_Decode() Error,AID = %d,ret = %d ", pRcvInfo->nTxAid, ret);
                    free(msg_ptr);
                    free(pRcvInfo);
                    continue;
                }
            }

            msg_ptr->messageType = MSG_MessageType_ID_Two;
            //使用AID映射id时，各类消息的AID不能一致，否则无法识别id
            if (msg_ptr->msgtype.MessageTwo.enumMessageFrameType == MSGV2_MessageFrame_PR_msgFrameExt)
            {
                messageid = msg_ptr->msgtype.MessageTwo.uniUperMsg.struFrameExt.enumpresent;
            }
            else
            {
                messageid = getMessageidFromAID(pRcvInfo->nTxAid, (int)msg_ptr->msgtype.MessageTwo.enumMessageFrameType);
                if (messageid < 0)
                {
                    LogPrint(LOG_LEVEL_WARN, "Stack_Rx_Warn", "MsgLay_GetMessageid() Warn,AID = %d,Messageid = %d", pRcvInfo->nTxAid,
                             (int)msg_ptr->msgtype.MessageTwo.enumMessageFrameType);
                    messageid = (int)msg_ptr->msgtype.MessageTwo.enumMessageFrameType;
                }
                msg_ptr->msgtype.MessageTwo.enumMessageFrameType = (WJV2_ENUM_MessageFrame_PR)messageid;
            }
        }

        //网络层扩展域
        if (pRcvInfo->extension.u8ExtenNum > 0)
        {
            msg_ptr->extension.u8ExtenNum = pRcvInfo->extension.u8ExtenNum;
            uint32_t u32i = 0;
            for (u32i = 0; u32i < msg_ptr->extension.u8ExtenNum; u32i++)
            {
                msg_ptr->extension.extenSionCommn[u32i].ElementID = pRcvInfo->extension.extenSionCommn[u32i].ElementID;
                msg_ptr->extension.extenSionCommn[u32i].ByteLength = pRcvInfo->extension.extenSionCommn[u32i].ByteLength;
                memcpy(msg_ptr->extension.extenSionCommn[u32i].ExtensionInfo,
                       pRcvInfo->extension.extenSionCommn[u32i].ExtensionInfo, pRcvInfo->extension.extenSionCommn[u32i].ByteLength);
            }
        }
        ++MsgRecvEnd;
        UpdateMsglayerRxDataNum();
        UpdateMsglayerRxDataHelper(messageid);
        MsgLayerMessagePushInQueue(msg_ptr);
        free(pRcvInfo);
    }
    (void)pthread_exit(NULL);
}
