#include <stdint.h>
#include <stdlib.h>
#include <thread>
#include "StackCodec.h"
#include "MemoryBlock.h"
extern "C"
{
#include "NetLayer.h"
#include "Port.h"
#include "wj_log.h"
#include "ConfigModuleRW.h"
#include "BusinessTool.h"
#include "SecLayerIntfCom.h"
#include "StateMonitor.h"
}

int DataSend(void *pdata, int lens, int AID, SendDataInfo *sendDataInfo)
{
    std::shared_ptr<MemoryBlock> block = std::make_shared<MemoryBlock>(MAX_DUMMY_PACKET_LEN);
    if ((NULL == block) || (NULL == block->buf))
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "block is NULL");
        return Calloc_Error;
    }
    int error_code = 0;
    int ret = 0;

    do
    {
        //SecLayer
        if (((2 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch) ||
             (3 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch)) &&
            (pSignSecuredComplete != NULL))
        {
            MsgLayData_st MsgLayData;
            memset(&MsgLayData, 0x00, sizeof(MsgLayData_st));
            MsgLayData.nAID = AID;
            MsgLayData.u8UseCerType = (CerType)ProtocolStackParamConfig.securityParamConfig.s8SignDeviceType;
            memcpy(MsgLayData.pu8MsgLayData, (uint8_t *)pdata, lens);
            MsgLayData.n32MsgLayDataLen = lens;

            ret = pSignSecuredComplete(MsgLayData, (uint8_t *)block->buf, &block->size);
            UpdateSafetyCertStatus(ret);
            if (ret != 0)
            {
                error_code = SignMsg_Error;
                LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "SecLay_Encode() Error,ret = %d ", ret);
                break;
            }
            UpdateSeclayerTxDataNum();
            LogPrint(LOG_LEVEL_DEBUG, "Stack_Tx_Debug", "SecLay_Encode() passed,data_len = %d", block->size);
        }
        else
        {
            block->size = lens;
            memcpy(block->buf, pdata, block->size);
        }

        //NetLayer
        TDSMEncReq DsmReq;
        memset(&DsmReq, 0x00, sizeof(TDSMEncReq));
        DsmReq.pExtension = NULL;
        DsmReq.AID = AID; //nAID is set according to msg type
        DsmReq.Priority = getPriorityFromID(DsmReq.AID);
        DsmReq.Length = block->size;
        DsmReq.Data = (int8_t *)block->buf;

        ret = NetLay_Encode(DsmReq, (int8_t *)sendDataInfo->p_pcBuf, &sendDataInfo->p_nLen);
        if (ret != 0)
        {
            error_code = NetLay_Encode_Error;
            LogPrint(LOG_LEVEL_DEBUG, "Stack_Tx_Debug", "NetLay_Encode() Error ,ret = %d ", ret);
            break;
        }
        LogPrint(LOG_LEVEL_DEBUG, "Stack_Tx_Debug", "NetLay_Encode() passed,sendDataInfo->p_nLen = %d ", sendDataInfo->p_nLen);
        //AG15Layer
        Adapter_Encode(DsmReq, sendDataInfo);
    } while (0);
    return error_code;
}

//parse data from GA15 layer to direct plain data(MsgLayer)
int RawDataParse(char *pSrc, int SrcLen, char *pDst, int *DstLen)
{
    TDSMEncReq *pDsmInfo = (TDSMEncReq *)calloc(1, sizeof(TDSMEncReq));
    if (NULL == pDsmInfo)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "pDsmInfo is NULL");
        return Calloc_Error;
    }
    int error_code = 0;

    do
    {
        int ret = NetLay_Decode((int8_t *)pSrc, &SrcLen, pDsmInfo);
        if (ret != 0)
        {
            error_code = NetLay_Decode_Error;
            LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "NetLay_Decode() Error ,ret = %d ", ret);
            break;
        }
        if (((3 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch) ||
             (1 == ProtocolStackParamConfig.securityParamConfig.s8SecuritySwitch)) &&
            (pVerifySecureComplete != NULL))
        {
            MsgLayData_st MsgLayData;
            memset(&MsgLayData, 0x00, sizeof(MsgLayData_st));
            //信大捷安验签将AID作为输入
            MsgLayData.nAID = pDsmInfo->AID;
            MsgLayData.n32MsgLayDataLen = MAX_DUMMY_PACKET_LEN;

            ret = pVerifySecureComplete((uint8_t *)pDsmInfo->Data, pDsmInfo->Length, &MsgLayData);
            if (ret != 0)
            {
                error_code = Verify_Error;
                LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "pVerifySecureComplete() Error ,ret = %d ", ret);
                break;
            }
            UpdateSeclayerRxDataNum();

            memcpy(pDst, MsgLayData.pu8MsgLayData, MsgLayData.n32MsgLayDataLen);
            *DstLen = MsgLayData.n32MsgLayDataLen;
        }
        else
        {
            memcpy(pDst, pDsmInfo->Data, pDsmInfo->Length);
            *DstLen = pDsmInfo->Length;
        }

    } while (0);

    if (pDsmInfo->Data != NULL)
    {
        free(pDsmInfo->Data);
    }
    if (pDsmInfo->pExtension != NULL)
    {
        free(pDsmInfo->pExtension);
    }
    free(pDsmInfo);
    return error_code;
}
