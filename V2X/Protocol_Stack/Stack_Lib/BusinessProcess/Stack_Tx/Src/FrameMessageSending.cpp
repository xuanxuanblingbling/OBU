#include "FrameMessageSending.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

extern "C"
{
#include "NetLayer.h"
#include "wj_log.h"
#include "PublicMsg.h"
#include "ClockTimeIf.h"
#include "BusinessTool.h"
#include "ConfigModuleRW.h"
#include "SecLayerIntfCom.h"
#include "StateMonitor.h"
}

/*二期消息集接口*/
extern WJV2_UperFromFileEncodeMain_BACK wjv2_UperFromFileEncodeMain;
extern WJV2_UperEncOrDecMain_BACK wjv2_UperEncOrDecMain;
/*三跨消息集接口*/
extern WJV3_UperFromFileEncodeMain_BACK wjv3_UperFromFileEncodeMain;
extern WJV3_UperEncOrDecMain_BACK wjv3_UperEncOrDecMain;
/*四跨消息集接口*/
extern WJV4_UperFromFileEncodeMain_BACK wjv4_UperFromFileEncodeMain;
extern WJV4_UperEncOrDecMain_BACK wjv4_UperEncOrDecMain;
/*新四跨消息集接口*/
extern WJVN4_UperFromFileEncodeMain_BACK wjvn4_UperFromFileEncodeMain;
extern WJVN4_UperEncOrDecMain_BACK wjvn4_UperEncOrDecMain;

void MessageSendingFromFile(union sigval value)
{
    if (ProtocolStackParamConfig.v2xStatusFlag.v2xStatus != 1)
    {
        return;
    }
    FrameMessageSendingblock *Sendingblock = (FrameMessageSendingblock *)(value.sival_ptr);
    if (Sendingblock == NULL)
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "Sendingblock is NULL");
        return;
    }

    int ret = 0, MsgAid = 0;
    SendCallbackReturnInfo callbackReturnInfo;
    memset(&callbackReturnInfo, 0x00, sizeof(SendCallbackReturnInfo));

    int index = Sendingblock->index;

    if (Sendingblock->block == NULL || Sendingblock->block->buf == NULL)
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "Sendingblock->block is NULL");
        Sendingblock->block = std::make_shared<MemoryBlock>(MAX_DUMMY_PACKET_LEN);
        if ((NULL == Sendingblock->block) || (NULL == Sendingblock->block->buf))
            return;
    }
    if (Sendingblock->pstruUperData == NULL)
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "Sendingblock->pstruUperData is NULL");
        Sendingblock->pstruUperData = (WJ_UperData *)calloc(1, sizeof(WJ_UperData));
        if (NULL == Sendingblock->pstruUperData)
            return;
    }

    bzero(Sendingblock->block->buf, MAX_DUMMY_PACKET_LEN);
    if ((MSG_MESSAGETYPE_ID_FOUR == ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion) &&
        (NULL != wjv4_UperFromFileEncodeMain))
    {
        if (Sendingblock->pstruUperDataV4 == NULL)
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataV4 is %p", Sendingblock->pstruUperDataV4);
            Sendingblock->pstruUperDataV4 = (WJV4_UperData *)calloc(1, sizeof(WJV4_UperData));
            if (NULL == Sendingblock->pstruUperDataV4)
                return;
        }
        Sendingblock->pstruUperDataV4->pu8buff = Sendingblock->block->buf;
        ret = wjv4_UperFromFileEncodeMain((WJV4_UperData *)Sendingblock->pstruUperDataV4, ProtocolStackParamConfig.messageParamConfig.m_SendParam[index].m_nSendFilePath, &MsgAid);
        if (true != ret)
        {
            LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "WJV4_UperFromFileEncodeMain is err");
            return;
        }
        Sendingblock->pstruUperData->pu8buff = Sendingblock->pstruUperDataV4->pu8buff;
        Sendingblock->pstruUperData->u32Len = Sendingblock->pstruUperDataV4->u32Len;
    }
    else if ((MSG_MESSAGETYPE_ID_NEW_FOUR == ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion) &&
             (NULL != wjvn4_UperFromFileEncodeMain))
    {
        if (Sendingblock->pstruUperDataVN4 == NULL)
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataVN4 is %p", Sendingblock->pstruUperDataVN4);
            Sendingblock->pstruUperDataVN4 = (WJVN4_UperData *)calloc(1, sizeof(WJVN4_UperData));
            if (NULL == Sendingblock->pstruUperDataVN4)
                return;
        }
        Sendingblock->pstruUperDataVN4->pu8buff = Sendingblock->block->buf;
        ret = wjvn4_UperFromFileEncodeMain((WJVN4_UperData *)Sendingblock->pstruUperDataVN4, ProtocolStackParamConfig.messageParamConfig.m_SendParam[index].m_nSendFilePath, &MsgAid);
        if (true != ret)
        {
            LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "WJVN4_UperFromFileEncodeMain is err");
            return;
        }
        Sendingblock->pstruUperData->pu8buff = Sendingblock->pstruUperDataVN4->pu8buff;
        Sendingblock->pstruUperData->u32Len = Sendingblock->pstruUperDataVN4->u32Len;
    }
    else if ((MSG_MESSAGETYPE_ID_THREE == ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion) &&
             (NULL != wjv3_UperFromFileEncodeMain))
    {
        if (Sendingblock->pstruUperDataV3 == NULL)
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataV3 is %p", Sendingblock->pstruUperDataV3);
            Sendingblock->pstruUperDataV3 = (WJV3_UperData *)calloc(1, sizeof(WJV3_UperData));
            if (NULL == Sendingblock->pstruUperDataV3)
                return;
        }
        Sendingblock->pstruUperDataV3->pu8buff = Sendingblock->block->buf;
        ret = wjv3_UperFromFileEncodeMain((WJV3_UperData *)Sendingblock->pstruUperDataV3, ProtocolStackParamConfig.messageParamConfig.m_SendParam[index].m_nSendFilePath, &MsgAid);
        if (true != ret)
        {
            LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "WJV3_UperFromFileEncodeMain is err");
            return;
        }
        Sendingblock->pstruUperData->pu8buff = Sendingblock->pstruUperDataV3->pu8buff;
        Sendingblock->pstruUperData->u32Len = Sendingblock->pstruUperDataV3->u32Len;
    }
    else
    {
        if (NULL != wjv2_UperFromFileEncodeMain)
        {
            if (Sendingblock->pstruUperDataV2 == NULL)
            {
                LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataV2 is %p", Sendingblock->pstruUperDataV2);
                Sendingblock->pstruUperDataV2 = (WJV2_UperData *)calloc(1, sizeof(WJV2_UperData));
                if (NULL == Sendingblock->pstruUperDataV2)
                    return;
            }
            Sendingblock->pstruUperDataV2->pu8buff = Sendingblock->block->buf;
            ret = wjv2_UperFromFileEncodeMain((WJV2_UperData *)Sendingblock->pstruUperDataV2, ProtocolStackParamConfig.messageParamConfig.m_SendParam[index].m_nSendFilePath, &MsgAid);
            if (true != ret)
            {
                LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "WJV2_UperFromFileEncodeMain is err");
                return;
            }
            Sendingblock->pstruUperData->pu8buff = Sendingblock->pstruUperDataV2->pu8buff;
            Sendingblock->pstruUperData->u32Len = Sendingblock->pstruUperDataV2->u32Len;
        }
    }

    if (ret)
    {
        ret = Sendingblock->MessageSending(Sendingblock->pstruUperData, MsgAid, &callbackReturnInfo.sendDataInfo);
        if (Sendingblock->pOnSendingComplete != nullptr)
        {
            callbackReturnInfo.data_type = MsgAid;
            callbackReturnInfo.error_type = ret;
            Sendingblock->pOnSendingComplete(callbackReturnInfo);
        }
    }
    return;
}

int FrameMessageSending::DataPushInQueue(MSG_MessageType_st *data)
{
    queue.DataPushInQueue(data);
    // int nSta, nSize;
    // queue.GetQueueStatus(nSta, nSize);
    // if (nSta == 1)
    // {
    //     LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Debug", "Send nSta = %d  nSize = %d", nSta, nSize);
    // }
    return 0;
}

void FrameMessageSending::ThreadProcFrameMsg()
{
    LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "ThreadProcFrameMsg() start:%d ", std::this_thread::get_id());

    int ret = 0;
    int messageType = 0;
    SendCallbackReturnInfo callbackReturnInfo;
    memset(&callbackReturnInfo, 0x00, sizeof(SendCallbackReturnInfo));
    while (1)
    {
        MSG_MessageType_st *data = this->queue.DataGetFromQueue();
        if (data != NULL)
        {
            if (ProtocolStackParamConfig.v2xStatusFlag.v2xStatus != 1)
            {
                free(data);
                data = nullptr;
                continue;
            }

            if (this->block == NULL || this->block->buf == NULL)
            {
                LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->block is NULL");
                this->block = std::make_shared<MemoryBlock>(MAX_DUMMY_PACKET_LEN);
                if ((NULL == this->block) || (NULL == this->block->buf))
                    continue;
            }
            if (MSG_MessageType_ID_Three == data->messageType)
            {
                ret = MessageSending(&(data->msgtype.MessageThree), &(data->extension), &callbackReturnInfo.sendDataInfo);
                callbackReturnInfo.data_type = data->msgtype.MessageThree.enumMessageFrameType;
            }
            else if (MSG_MessageType_ID_Four == data->messageType)
            {
                ret = MessageSending(&(data->msgtype.MessageFour), &(data->extension), (int)data->nEmergencyEventFlag, &callbackReturnInfo.sendDataInfo);
                callbackReturnInfo.data_type = data->msgtype.MessageFour.enumMessageFrameType;
            }
            else if (MSG_MessageType_ID_NEW_Four == data->messageType)
            {
                ret = MessageSending(&(data->msgtype.MessageNewFour), &(data->extension), (int)data->nEmergencyEventFlag, &callbackReturnInfo.sendDataInfo);
                callbackReturnInfo.data_type = data->msgtype.MessageNewFour.enumMessageFrameType;
            }
            else
            {
                if (data->msgtype.MessageTwo.enumMessageFrameType == MSGV2_MessageFrame_PR_msgFrameExt)
                    messageType = data->msgtype.MessageTwo.uniUperMsg.struFrameExt.enumpresent;
                else
                    messageType = data->msgtype.MessageTwo.enumMessageFrameType;

                ret = MessageSending(&(data->msgtype.MessageTwo), &(data->extension), (int)data->nEmergencyEventFlag, &callbackReturnInfo.sendDataInfo);
                callbackReturnInfo.data_type = messageType;
            }

            if (this->pOnSendingComplete != nullptr)
            {
                callbackReturnInfo.error_type = ret;
                this->pOnSendingComplete(callbackReturnInfo);
            }
            free(data);
            data = nullptr;
        }
    }
}

int FrameMessageSending::MessageSending(WJV2_STRU_MessageFrame *data, tExtenSionCommn_st *extension, int nEmergencyEventFlag, SendDataInfo *sendDataInfo)
{
    if (NULL == data || NULL == extension || NULL == sendDataInfo)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "MessageSending Param is NULL");
        return Para_Error;
    }
    int error_code = 0;
    int ret = 0;
    int messageType = 0;

    if (data->enumMessageFrameType == MSGV2_MessageFrame_PR_msgFrameExt)
        messageType = data->uniUperMsg.struFrameExt.enumpresent;
    else
        messageType = data->enumMessageFrameType;

    if (this->pstruUperDataV2 == NULL)
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataV2 is %p", this->pstruUperDataV2);
        this->pstruUperDataV2 = (WJV2_UperData *)calloc(1, sizeof(WJV2_UperData));
        if (NULL == this->pstruUperDataV2)
        {
            return Calloc_Error;
        }
    }

    //MsgLayer
    bzero(this->block->buf, MAX_DUMMY_PACKET_LEN);
    this->pstruUperDataV2->pu8buff = this->block->buf;
    if (NULL != wjv2_UperEncOrDecMain)
    {
        ret = wjv2_UperEncOrDecMain(this->pstruUperDataV2, data, MSGV2_MessageFrame_UperEncode);
        if (!ret)
        {
            error_code = Message_Encode_Error;
            LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "wjv2_UperEncOrDecMain() Error");
            return error_code;
        }
    }
    else
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "wjv2_UperEncOrDecMain() is NULL");
    }

    this->block->size = this->pstruUperDataV2->u32Len;
    if (this->block->size <= 0)
    {
        error_code = Message_Encode_Error;
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "MsgLay_Encode() Error,data->enumMessageFrameType = %d,error_code = %d", messageType, error_code);
        return error_code;
    }

    UpdateMsglayerTxDataNum();
    UpdateMsglayerTxDataHelper(messageType);

    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "MsgLay_Encode() passed,data->enumMessageFrameType = %d,data_len = %d", messageType, this->block->size);
    //SecureLayer option
    TDSMEncReq DsmReq;
    memset(&DsmReq, 0x00, sizeof(TDSMEncReq));
    DsmReq.pExtension = extension;
    DsmReq.Priority = getPriorityFromID(messageType);
    DsmReq.AID = getAIDFromID(messageType);
    //判断是否包含安全层
    if (((2 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch) ||
         (3 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch)) &&
        (pSignSecuredComplete != NULL))
    {
        MsgLayData_st MsgLayData;
        memset(&MsgLayData, 0x00, sizeof(MsgLayData_st));
        MsgLayData.nAID = getAIDFromID(messageType);
        MsgLayData.u8UseCerType = (CerType)ProtocolStackParamConfig.securityParamConfig.s8SignDeviceType;
        memcpy(MsgLayData.pu8MsgLayData, this->block->buf, block->size);
        MsgLayData.n32MsgLayDataLen = this->block->size;

        //判断如果是OBU设备，需填充OBU紧急事件标志及经纬度信息
        if (ProtocolStackParamConfig.securityParamConfig.s8SignDeviceType == 1)
        {
            MsgLayData.nEmergencyEventFlag = nEmergencyEventFlag;
            MsgLayData.dLongitude = data->uniUperMsg.strubsmFrame.strupos.n32long;
            MsgLayData.dLatitude = data->uniUperMsg.strubsmFrame.strupos.n32lat;
        }

        bzero(this->block->buf, MAX_DUMMY_PACKET_LEN);
        this->block->size = MAX_DUMMY_PACKET_LEN;
        ret = pSignSecuredComplete(MsgLayData, (uint8_t *)this->block->buf, &this->block->size);
        UpdateSafetyCertStatus(ret);
        if (ret != 0)
        {
            error_code = SignMsg_Error;
            LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "SecLay_Encode() Error,data->enumMessageFrameType = %d,ret = %d", messageType, ret);
            return error_code;
        }
        UpdateSeclayerTxDataNum();
        // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "SecLay_Encode() passed,data->enumMessageFrameType = %d,data_len = %d", messageType, this->block->size);
    }
    DsmReq.Length = this->block->size;
    DsmReq.Data = (int8_t *)this->block->buf;
    //NetLayer
    ret = NetLay_Encode(DsmReq, (int8_t *)sendDataInfo->p_pcBuf, &sendDataInfo->p_nLen);
    if (ret != 0)
    {
        error_code = NetLay_Encode_Error;
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "NetLay_Encode() Error,data->enumMessageFrameType = %d,ret = %d", messageType, ret);
        return error_code;
    }
    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "NetLay_Encode() passed,data->enumMessageFrameType = %d,sendDataInfo->p_nLen = %d ", messageType, sendDataInfo->p_nLen);
    Adapter_Encode(DsmReq, sendDataInfo);

    return error_code;
}

int FrameMessageSending::MessageSending(WJV4_STRU_MessageFrame *data, tExtenSionCommn_st *extension, int nEmergencyEventFlag, SendDataInfo *sendDataInfo)
{
    if (NULL == data || NULL == extension || NULL == sendDataInfo)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "MessageSending Param is NULL");
        return Para_Error;
    }
    int error_code = 0;
    int ret = 0;

    if (this->pstruUperDataV4 == NULL)
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataV4 is %p", this->pstruUperDataV4);
        this->pstruUperDataV4 = (WJV4_UperData *)calloc(1, sizeof(WJV4_UperData));
        if (NULL == this->pstruUperDataV4)
        {
            return Calloc_Error;
        }
    }

    //MsgLayer
    bzero(this->block->buf, MAX_DUMMY_PACKET_LEN);
    this->pstruUperDataV4->pu8buff = this->block->buf;
    if (NULL != wjv4_UperEncOrDecMain)
    {
        ret = wjv4_UperEncOrDecMain(this->pstruUperDataV4, data, MSGV4_MessageFrame_UperEncode);
        if (!ret)
        {
            error_code = Message_Encode_Error;
            LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "wjv4_UperEncOrDecMain() Error");
            return error_code;
        }
    }
    else
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "wjv4_UperEncOrDecMain() is NULL");
    }

    this->block->size = this->pstruUperDataV4->u32Len;
    if (this->block->size <= 0)
    {
        error_code = Message_Encode_Error;
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "MsgLay_Encode() Error,data->enumMessageFrameType = %d,error_code = %d", data->enumMessageFrameType, error_code);
        return error_code;
    }
    UpdateMsglayerTxDataNum();
    UpdateMsglayerTxDataHelper(data->enumMessageFrameType);

    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "MsgLay_Encode() passed,data->enumMessageFrameType = %d,data_len = %d", data->enumMessageFrameType, this->block->size);

    //SecureLayer option
    TDSMEncReq DsmReq;
    memset(&DsmReq, 0x00, sizeof(TDSMEncReq));
    DsmReq.pExtension = extension;
    DsmReq.Priority = getPriorityFromID(data->enumMessageFrameType);
    DsmReq.AID = getAIDFromID(data->enumMessageFrameType);
    //判断是否包含安全层
    if (((2 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch) ||
         (3 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch)) &&
        (pSignSecuredComplete != NULL))
    {
        MsgLayData_st MsgLayData;
        memset(&MsgLayData, 0x00, sizeof(MsgLayData_st));
        MsgLayData.nAID = getAIDFromID(data->enumMessageFrameType);
        MsgLayData.u8UseCerType = (CerType)ProtocolStackParamConfig.securityParamConfig.s8SignDeviceType;
        memcpy(MsgLayData.pu8MsgLayData, this->block->buf, block->size);
        MsgLayData.n32MsgLayDataLen = this->block->size;

        //判断如果是OBU设备，需填充OBU紧急事件标志及经纬度信息
        if (ProtocolStackParamConfig.securityParamConfig.s8SignDeviceType == 1)
        {
            MsgLayData.nEmergencyEventFlag = nEmergencyEventFlag;
            MsgLayData.dLongitude = data->uniUperMsg.strubsmFrame.strupos.n32long;
            MsgLayData.dLatitude = data->uniUperMsg.strubsmFrame.strupos.n32lat;
        }
        bzero(this->block->buf, MAX_DUMMY_PACKET_LEN);
        this->block->size = MAX_DUMMY_PACKET_LEN;
        ret = pSignSecuredComplete(MsgLayData, (uint8_t *)this->block->buf, &this->block->size);
        UpdateSafetyCertStatus(ret);
        if (ret != 0)
        {
            error_code = SignMsg_Error;
            LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "SecLay_Encode() Error,data->enumMessageFrameType = %d,ret = %d", data->enumMessageFrameType, ret);
            return error_code;
        }
        UpdateSeclayerTxDataNum();
        // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "SecLay_Encode() passed,data->enumMessageFrameType = %d,data_len = %d", data->enumMessageFrameType, block->size);
    }

    DsmReq.Length = this->block->size;
    DsmReq.Data = (int8_t *)this->block->buf;
    //NetLayer
    ret = NetLay_Encode(DsmReq, (int8_t *)sendDataInfo->p_pcBuf, &sendDataInfo->p_nLen);
    if (ret != 0)
    {
        error_code = NetLay_Encode_Error;
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "NetLay_Encode() Error,data->enumMessageFrameType = %d,ret = %d", data->enumMessageFrameType, ret);
        return error_code;
    }
    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "NetLay_Encode() passed,data->enumMessageFrameType = %d,sendDataInfo->p_nLen = %d ", data->enumMessageFrameType, sendDataInfo->p_nLen);
    Adapter_Encode(DsmReq, sendDataInfo);

    return error_code;
}

int FrameMessageSending::MessageSending(WJVN4_STRU_MessageFrame *data, tExtenSionCommn_st *extension, int nEmergencyEventFlag, SendDataInfo *sendDataInfo)
{
    if (NULL == data || NULL == extension || NULL == sendDataInfo)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "MessageSending Param is NULL");
        return Para_Error;
    }

    int error_code = 0;
    int ret = 0;

    if (this->pstruUperDataVN4 == NULL)
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataVN4 is %p", this->pstruUperDataVN4);
        this->pstruUperDataVN4 = (WJVN4_UperData *)calloc(1, sizeof(WJVN4_UperData));
        if (NULL == this->pstruUperDataVN4)
        {
            return Calloc_Error;
        }
    }

    //MsgLayer
    bzero(this->block->buf, MAX_DUMMY_PACKET_LEN);
    this->pstruUperDataVN4->pu8buff = this->block->buf;
    if (NULL != wjvn4_UperEncOrDecMain)
    {
        ret = wjvn4_UperEncOrDecMain(this->pstruUperDataVN4, data, MSGVN4_MessageFrame_UperEncode);
        if (!ret)
        {
            error_code = Message_Encode_Error;
            LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "wjvn4_UperEncOrDecMain() Error ");
            return error_code;
        }
    }
    else
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "wjvn4_UperEncOrDecMain() is NULL");
    }

    this->block->size = this->pstruUperDataVN4->u32Len;
    if (this->block->size <= 0)
    {
        error_code = Message_Encode_Error;
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "MsgLay_Encode() Error,data->enumMessageFrameType = %d,error_code = %d", data->enumMessageFrameType, error_code);
        return error_code;
    }

    UpdateMsglayerTxDataNum();
    UpdateMsglayerTxDatabyte(this->block->size);
    UpdateMsglayerTxDataHelper(data->enumMessageFrameType);

    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "MsgLay_Encode() passed,data->enumMessageFrameType = %d,data_len = %d", data->enumMessageFrameType, this->block->size);
    //SecureLayer option
    TDSMEncReq DsmReq;
    memset(&DsmReq, 0x00, sizeof(TDSMEncReq));
    DsmReq.pExtension = extension;
    DsmReq.Priority = getPriorityFromID(data->enumMessageFrameType);
    DsmReq.AID = getAIDFromID(data->enumMessageFrameType);
    //判断是否包含安全层
    if (((2 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch) ||
         (3 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch)) &&
        (pSignSecuredComplete != NULL))
    {
        MsgLayData_st MsgLayData;
        memset(&MsgLayData, 0x00, sizeof(MsgLayData_st));
        MsgLayData.nAID = getAIDFromID(data->enumMessageFrameType);
        MsgLayData.u8UseCerType = (CerType)ProtocolStackParamConfig.securityParamConfig.s8SignDeviceType;
        memcpy(MsgLayData.pu8MsgLayData, this->block->buf, this->block->size);
        MsgLayData.n32MsgLayDataLen = this->block->size;

        //判断如果是OBU设备，需填充OBU紧急事件标志及经纬度信息
        if (ProtocolStackParamConfig.securityParamConfig.s8SignDeviceType == 1)
        {
            MsgLayData.nEmergencyEventFlag = nEmergencyEventFlag;
            MsgLayData.dLongitude = data->uniUperMsg.strubsmFrame.strupos.n32long;
            MsgLayData.dLatitude = data->uniUperMsg.strubsmFrame.strupos.n32lat;
        }
        bzero(this->block->buf, MAX_DUMMY_PACKET_LEN);
        this->block->size = MAX_DUMMY_PACKET_LEN;
        ret = pSignSecuredComplete(MsgLayData, (uint8_t *)this->block->buf, &this->block->size);
        UpdateSafetyCertStatus(ret);
        if (ret != 0)
        {
            error_code = SignMsg_Error;
            LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "SecLay_Encode() Error,data->enumMessageFrameType = %d,ret = %d", data->enumMessageFrameType, ret);
            return error_code;
        }
        UpdateSeclayerTxDataNum();
        // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "SecLay_Encode() passed,data->enumMessageFrameType = %d,data_len = %d", data->enumMessageFrameType, this->block->size);
    }
    DsmReq.Length = this->block->size;
    DsmReq.Data = (int8_t *)this->block->buf;
    //NetLayer
    ret = NetLay_Encode(DsmReq, (int8_t *)sendDataInfo->p_pcBuf, &sendDataInfo->p_nLen);
    if (ret != 0)
    {
        error_code = NetLay_Encode_Error;
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "NetLay_Encode() Error,data->enumMessageFrameType = %d,ret = %d", data->enumMessageFrameType, ret);
        return error_code;
    }
    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "NetLay_Encode() passed,data->enumMessageFrameType = %d,sendDataInfo->p_nLen = %d ", data->enumMessageFrameType, sendDataInfo->p_nLen);
    Adapter_Encode(DsmReq, sendDataInfo);

    return error_code;
}

int FrameMessageSending::MessageSending(WJV3_STRU_MessageFrame *data, tExtenSionCommn_st *extension, SendDataInfo *sendDataInfo)
{
    if (NULL == data || NULL == extension || NULL == sendDataInfo)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "MessageSending Param is NULL");
        return Para_Error;
    }
    int error_code = 0;
    int ret = 0;

    if (this->pstruUperDataV3 == NULL)
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataV3 is %p", this->pstruUperDataV3);
        this->pstruUperDataV3 = (WJV3_UperData *)calloc(1, sizeof(WJV3_UperData));
        if (NULL == this->pstruUperDataV3)
        {
            return Calloc_Error;
        }
    }

    bzero(this->block->buf, MAX_DUMMY_PACKET_LEN);
    this->pstruUperDataV3->pu8buff = this->block->buf;
    if (NULL != wjv3_UperEncOrDecMain)
    {
        ret = wjv3_UperEncOrDecMain(this->pstruUperDataV3, data, MSGV3_MessageFrame_UperEncode);
        if (!ret)
        {
            error_code = Message_Encode_Error;
            LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "MsgLay_Encode() Error,data->enumMessageFrameType = %d,error_code = %d", data->enumMessageFrameType, error_code);
            return error_code;
        }
    }
    else
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "wjv3_UperEncOrDecMain() is NULL");
    }

    UpdateMsglayerTxDataNum();
    UpdateMsglayerTxDataHelper(data->enumMessageFrameType);

    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "MsgLay_Encode() passed,data->enumMessageFrameType = %d,Length = %d", data->enumMessageFrameType, this->pstruUperDataV3->u32Len);

    //SecureLayer option
    TDSMEncReq DsmReq;
    memset(&DsmReq, 0x00, sizeof(TDSMEncReq));
    DsmReq.pExtension = extension;
    DsmReq.Priority = getPriorityFromID(data->enumMessageFrameType);
    DsmReq.AID = getAIDFromID(data->enumMessageFrameType);
    DsmReq.Length = this->pstruUperDataV3->u32Len;
    DsmReq.Data = (int8_t *)this->pstruUperDataV3->pu8buff;
    //NetLayer
    ret = NetLay_Encode(DsmReq, (int8_t *)sendDataInfo->p_pcBuf, &sendDataInfo->p_nLen);
    if (ret != 0)
    {
        error_code = NetLay_Encode_Error;
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "NetLay_Encode() Error,data->enumMessageFrameType = %d,ret = %d", data->enumMessageFrameType, ret);
        return error_code;
    }
    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "NetLay_Encode() passed,data->enumMessageFrameType = %d,sendDataInfo->p_nLen = %d ", data->enumMessageFrameType, sendDataInfo->p_nLen);

    Adapter_Encode(DsmReq, sendDataInfo);

    return error_code;
}

int FrameMessageSendingblock::MessageSending(WJ_UperData *p_pstruUperData, int MsgAid, SendDataInfo *sendDataInfo)
{
    if (NULL == p_pstruUperData || NULL == sendDataInfo)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "MessageSending Param is NULL");
        return Para_Error;
    }

    int error_code = 0;
    int ret = 0;

    //MsgLayer
    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "MsgLay_Encode() passed,MsgAid = %d,Length = %d", MsgAid, p_pstruUperData->u32Len);

    UpdateMsglayerTxDataNum();
    UpdateMsglayerTxDataHelper(getMessageidFromAIDBak(MsgAid));

    TDSMEncReq DsmReq;
    memset(&DsmReq, 0x00, sizeof(TDSMEncReq));
    if (MsgAid == 0)
    {
        MsgAid = ProtocolStackParamConfig.DSMPParamConfig.StandardMessageAID;
    }
    DsmReq.pExtension = NULL;
    DsmReq.Priority = getPriorityFromID(MsgAid);
    DsmReq.AID = MsgAid;
    //SecureLayer option
    if (((MSG_MESSAGETYPE_ID_FOUR == ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion) ||
         (MSG_MESSAGETYPE_ID_NEW_FOUR == ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion) ||
         (MSG_MESSAGETYPE_ID_TWO == ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion)) &&
        ((ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch == 2) ||
         (ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch == 3)))
    {
        if (pSignSecuredComplete != NULL)
        {
            MsgLayData_st MsgLayData;
            memset(&MsgLayData, 0x00, sizeof(MsgLayData_st));
            MsgLayData.nAID = MsgAid;
            MsgLayData.u8UseCerType = (CerType)ProtocolStackParamConfig.securityParamConfig.s8SignDeviceType;
            memcpy(MsgLayData.pu8MsgLayData, p_pstruUperData->pu8buff, p_pstruUperData->u32Len);
            MsgLayData.n32MsgLayDataLen = p_pstruUperData->u32Len;

            bzero(this->block->buf, MAX_DUMMY_PACKET_LEN);
            this->block->size = MAX_DUMMY_PACKET_LEN;
            ret = pSignSecuredComplete(MsgLayData, (uint8_t *)this->block->buf, &this->block->size);
            UpdateSafetyCertStatus(ret);
            if (ret != 0)
            {
                error_code = SignMsg_Error;
                LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "SecLay_Encode() Error,MsgAid = %d,ret = %d", MsgAid, ret);
                return error_code;
            }
            UpdateSeclayerTxDataNum();
            // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "SecLay_Encode() passed,MsgAid = %d,data_len = %d", MsgAid, block->size);

            DsmReq.Length = this->block->size;
            DsmReq.Data = (int8_t *)this->block->buf;
        }
        else
        {
            DsmReq.Length = p_pstruUperData->u32Len;
            DsmReq.Data = (int8_t *)p_pstruUperData->pu8buff;
        }
    }
    else
    {
        DsmReq.Length = p_pstruUperData->u32Len;
        DsmReq.Data = (int8_t *)p_pstruUperData->pu8buff;
    }

    //NetLayer
    ret = NetLay_Encode(DsmReq, (int8_t *)sendDataInfo->p_pcBuf, &sendDataInfo->p_nLen);
    if (ret != 0)
    {
        error_code = NetLay_Encode_Error;
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "NetLay_Encode() Error,MsgAid = %d,ret = %d", MsgAid, ret);
        return error_code;
    }
    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "NetLay_Encode() passed,MsgAid = %d,sendDataInfo->p_nLen =%d ", MsgAid, sendDataInfo->p_nLen);
    Adapter_Encode(DsmReq, sendDataInfo);

    return error_code;
}

int FrameMessageSendingSerial::MessageSending(MSG_MessageType_st *data)
{
    if (NULL == data)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "MessageSending Param is NULL");
        return Para_Error;
    }
    int error_code = 0;
    int ret = 0, SignFlag = 1;
    double dLongitude = 0, dLatitude = 0;

    SendCallbackReturnInfo callbackReturnInfo;
    memset(&callbackReturnInfo, 0x00, sizeof(SendCallbackReturnInfo));

    if (this->block == NULL || this->block->buf == NULL)
    {
        LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->block is NULL");
        this->block = std::make_shared<MemoryBlock>(MAX_DUMMY_PACKET_LEN);
        if ((NULL == this->block) || (NULL == this->block->buf))
            return Calloc_Error;
    }
    //MsgLayer
    bzero(this->block->buf, MAX_DUMMY_PACKET_LEN);
    if (data->messageType == MSG_MessageType_ID_Four)
    {
        callbackReturnInfo.data_type = data->msgtype.MessageFour.enumMessageFrameType;
        if (callbackReturnInfo.data_type == MSG_MessageFrame_ID_BSM ||
            callbackReturnInfo.data_type / 100 == MSG_MessageFrame_ID_BSM)
        {
            dLongitude = data->msgtype.MessageFour.uniUperMsg.strubsmFrame.strupos.n32long;
            dLatitude = data->msgtype.MessageFour.uniUperMsg.strubsmFrame.strupos.n32lat;
        }
        if (this->pstruUperDataV4 == NULL)
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataV4 is %p", this->pstruUperDataV4);
            this->pstruUperDataV4 = (WJV4_UperData *)calloc(1, sizeof(WJV4_UperData));
            if (NULL == this->pstruUperDataV4)
            {
                return Calloc_Error;
            }
        }
        this->pstruUperDataV4->pu8buff = this->block->buf;
        if (NULL != wjv4_UperEncOrDecMain)
        {
            ret = wjv4_UperEncOrDecMain(this->pstruUperDataV4, &data->msgtype.MessageFour, MSGV4_MessageFrame_UperEncode);
            if (!ret)
            {
                error_code = Message_Encode_Error;
                LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "wjv4_UperEncOrDecMain() Error");
                return error_code;
            }
        }
        else
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "wjv4_UperEncOrDecMain() is NULL");
        }
        this->block->size = this->pstruUperDataV4->u32Len;
    }
    else if (data->messageType == MSG_MessageType_ID_NEW_Four)
    {
        callbackReturnInfo.data_type = data->msgtype.MessageNewFour.enumMessageFrameType;
        if (callbackReturnInfo.data_type == MSG_MessageFrame_ID_BSM ||
            callbackReturnInfo.data_type / 100 == MSG_MessageFrame_ID_BSM)
        {
            dLongitude = data->msgtype.MessageNewFour.uniUperMsg.strubsmFrame.strupos.n32long;
            dLatitude = data->msgtype.MessageNewFour.uniUperMsg.strubsmFrame.strupos.n32lat;
        }
        if (this->pstruUperDataVN4 == NULL)
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataVN4 is %p", this->pstruUperDataVN4);
            this->pstruUperDataVN4 = (WJVN4_UperData *)calloc(1, sizeof(WJVN4_UperData));
            if (NULL == this->pstruUperDataVN4)
            {
                return Calloc_Error;
            }
        }
        this->pstruUperDataVN4->pu8buff = this->block->buf;
        if (NULL != wjvn4_UperEncOrDecMain)
        {
            ret = wjvn4_UperEncOrDecMain(this->pstruUperDataVN4, &data->msgtype.MessageNewFour, MSGVN4_MessageFrame_UperEncode);
            if (!ret)
            {
                error_code = Message_Encode_Error;
                LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "wjv4_UperEncOrDecMain() Error");
                return error_code;
            }
        }
        else
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "wjv4_UperEncOrDecMain() is NULL");
        }
        this->block->size = this->pstruUperDataVN4->u32Len;
    }
    else if (data->messageType == MSG_MessageType_ID_Three)
    {
        SignFlag = 0;
        callbackReturnInfo.data_type = data->msgtype.MessageThree.enumMessageFrameType;
        if (this->pstruUperDataV3 == NULL)
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataV3 is %p", this->pstruUperDataV3);
            this->pstruUperDataV3 = (WJV3_UperData *)calloc(1, sizeof(WJV3_UperData));
            if (NULL == this->pstruUperDataV3)
            {
                return Calloc_Error;
            }
        }
        this->pstruUperDataV3->pu8buff = this->block->buf;
        if (NULL != wjv3_UperEncOrDecMain)
        {
            ret = wjv3_UperEncOrDecMain(this->pstruUperDataV3, &data->msgtype.MessageThree, MSGV3_MessageFrame_UperEncode);
            if (!ret)
            {
                error_code = Message_Encode_Error;
                LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "wjv4_UperEncOrDecMain() Error");
                return error_code;
            }
        }
        else
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "wjv4_UperEncOrDecMain() is NULL");
        }
        this->block->size = this->pstruUperDataV3->u32Len;
    }
    else
    {
        if (data->msgtype.MessageTwo.enumMessageFrameType == MSGV2_MessageFrame_PR_msgFrameExt)
            callbackReturnInfo.data_type = data->msgtype.MessageTwo.uniUperMsg.struFrameExt.enumpresent;
        else
            callbackReturnInfo.data_type = data->msgtype.MessageTwo.enumMessageFrameType;

        if (callbackReturnInfo.data_type == MSG_MessageFrame_ID_BSM ||
            callbackReturnInfo.data_type / 100 == MSG_MessageFrame_ID_BSM)
        {
            dLongitude = data->msgtype.MessageTwo.uniUperMsg.strubsmFrame.strupos.n32long;
            dLatitude = data->msgtype.MessageTwo.uniUperMsg.strubsmFrame.strupos.n32lat;
        }
        if (this->pstruUperDataV2 == NULL)
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "this->pstruUperDataV2 is %p", this->pstruUperDataV2);
            this->pstruUperDataV2 = (WJV2_UperData *)calloc(1, sizeof(WJV2_UperData));
            if (NULL == this->pstruUperDataV2)
            {
                return Calloc_Error;
            }
        }
        this->pstruUperDataV2->pu8buff = this->block->buf;
        if (NULL != wjv2_UperEncOrDecMain)
        {
            ret = wjv2_UperEncOrDecMain(this->pstruUperDataV2, &data->msgtype.MessageTwo, MSGV2_MessageFrame_UperEncode);
            if (!ret)
            {
                error_code = Message_Encode_Error;
                LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "wjv2_UperEncOrDecMain() Error");
                return error_code;
            }
                }
        else
        {
            LogPrint(LOG_LEVEL_WARN, "Stack_Tx_Warn", "wjv2_UperEncOrDecMain() is NULL");
        }
        this->block->size = this->pstruUperDataV2->u32Len;
    }

    UpdateMsglayerTxDataNum();
    UpdateMsglayerTxDataHelper(callbackReturnInfo.data_type);
    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "MsgLay_Encode() passed,data->enumMessageFrameType = %d,data_len = %d", callbackReturnInfo.data_type, this->block->size);

    if (SignFlag)
    {
        //判断是否包含安全层
        if (((2 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch) ||
             (3 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch)) &&
            (pSignSecuredComplete != NULL))
        {
            MsgLayData_st MsgLayData;
            memset(&MsgLayData, 0x00, sizeof(MsgLayData_st));
            MsgLayData.nAID = getAIDFromID(callbackReturnInfo.data_type);
            MsgLayData.u8UseCerType = (CerType)ProtocolStackParamConfig.securityParamConfig.s8SignDeviceType;
            memcpy(MsgLayData.pu8MsgLayData, this->block->buf, block->size);
            MsgLayData.n32MsgLayDataLen = this->block->size;

            //判断如果是OBU设备，需填充OBU紧急事件标志及经纬度信息
            if (ProtocolStackParamConfig.securityParamConfig.s8SignDeviceType == 1)
            {
                MsgLayData.nEmergencyEventFlag = data->nEmergencyEventFlag;
                MsgLayData.dLongitude = dLongitude;
                MsgLayData.dLatitude = dLatitude;
            }
            bzero(this->block->buf, MAX_DUMMY_PACKET_LEN);
            this->block->size = MAX_DUMMY_PACKET_LEN;
            ret = pSignSecuredComplete(MsgLayData, (uint8_t *)this->block->buf, &this->block->size);
            UpdateSafetyCertStatus(ret);
            if (ret != 0)
            {
                error_code = SignMsg_Error;
                LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "SecLay_Encode() Error,data->enumMessageFrameType = %d,ret = %d", callbackReturnInfo.data_type, ret);
                return error_code;
            }
            UpdateSeclayerTxDataNum();
            // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "SecLay_Encode() passed,data->enumMessageFrameType = %d,data_len = %d", callbackReturnInfo.data_type, block->size);
        }
    }
    //SecureLayer option
    TDSMEncReq DsmReq;
    memset(&DsmReq, 0x00, sizeof(TDSMEncReq));
    DsmReq.pExtension = &data->extension;
    DsmReq.Priority = getPriorityFromID(callbackReturnInfo.data_type);
    DsmReq.AID = getAIDFromID(callbackReturnInfo.data_type);
    DsmReq.Length = this->block->size;
    DsmReq.Data = (int8_t *)this->block->buf;
    //NetLayer
    ret = NetLay_Encode(DsmReq, (int8_t *)callbackReturnInfo.sendDataInfo.p_pcBuf, &callbackReturnInfo.sendDataInfo.p_nLen);
    if (ret != 0)
    {
        error_code = NetLay_Encode_Error;
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "NetLay_Encode() Error,data->enumMessageFrameType = %d,ret = %d", callbackReturnInfo.data_type, ret);
        return error_code;
    }
    // LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "NetLay_Encode() passed,data->enumMessageFrameType = %d,sendDataInfo->p_nLen = %d ", callbackReturnInfo.data_type, callbackReturnInfo.sendDataInfo.p_nLen);
    Adapter_Encode(DsmReq, &callbackReturnInfo.sendDataInfo);

    if (this->pOnSendingComplete != nullptr)
    {
        callbackReturnInfo.error_type = ret;
        this->pOnSendingComplete(callbackReturnInfo);
    }

    return error_code;
}