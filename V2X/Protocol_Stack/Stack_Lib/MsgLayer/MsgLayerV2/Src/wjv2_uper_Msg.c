/**
* @file         :wjv2_uper_Msg.c.c
* @brief        :消息帧编解码函数
* @details      :主要包含消息帧编解码函数的实现
* @author       :huangsai  any question please send mail to huangsai@wanji,net.cn
* @date         :2020-12-17
* @version      :V1.0
* @copyright    :Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：IMX6
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
/* 头文件包含 */
#include "wjv2_uper_Msg.h"
#include "wjv2_uper_com.h"

/**
* @brief     WJV2_PAMData_MsgEnc解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_PAMData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_PAMData *pstruWjPAMData = (WJV2_STRU_PAMData *)pvoidWjMsg;
    PAMData_t *pstruAsnPAMData = (PAMData_t *)pvoidAsnMsg;
    struct ParkingGuide *pstruParkingGuide_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjPAMData->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjPAMData->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjPAMData->n32msgCnt = %d",
                 pstruWjPAMData->n32msgCnt);
        return false;
    }
    pstruAsnPAMData->msgCnt = pstruWjPAMData->n32msgCnt;
    if (WJV2_PRESENT == pstruWjPAMData->u8timeStampPresent)
    {
        pstruAsnPAMData->timeStamp = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnPAMData->timeStamp)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        if ((WJV2_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjPAMData->n32timeStamp) || (WJV2_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjPAMData->n32timeStamp))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:pstruWjPAMData->n32timeStamp = %d",
                     pstruWjPAMData->n32timeStamp);
            return false;
        }
        *(pstruAsnPAMData->timeStamp) = pstruWjPAMData->n32timeStamp;
    }
    else
    {
        pstruAsnPAMData->timeStamp = NULL;
    }
    n32Ret = WJV2_ParkingLotInfo_DfEnc(&(pstruAsnPAMData->parkingLotInfo), &(pstruWjPAMData->struparkingLotInfo));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_ParkingLotInfo_DfEnc is err");
        return false;
    }
    n32Ret = WJV2_PAMNodeList_DfEnc(&(pstruAsnPAMData->pamNodes), &(pstruWjPAMData->strupamNodes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_PAMNodeList_DfEnc is err");
        return false;
    }
    if (WJV2_PRESENT == pstruWjPAMData->u8parkingAreaGuidancePresent)
    {
        pstruAsnPAMData->parkingAreaGuidance = CALLOC(1, sizeof(struct parkingAreaGuidance));
        if (NULL == pstruAsnPAMData->parkingAreaGuidance)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        if ((WJV2_MAX_LIST_ParkingGuide_LEN < pstruWjPAMData->struparkingAreaGuidance.u8ParkingGuideNum) || (WJV2_MIN_LIST_ParkingGuide_LEN > pstruWjPAMData->struparkingAreaGuidance.u8ParkingGuideNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjPAMData->struparkingAreaGuidance.u8ParkingGuideNum = %d",
                     pstruWjPAMData->struparkingAreaGuidance.u8ParkingGuideNum);
            return false;
        }
        for (u32i = 0; u32i < pstruWjPAMData->struparkingAreaGuidance.u8ParkingGuideNum; u32i++)
        {
            pstruParkingGuide_node = CALLOC(1, sizeof(struct ParkingGuide));
            if (NULL == pstruParkingGuide_node)
            {
                LogPrint(LOG_LEVEL_ERR,
                         STACK_DF_MODULE,
                         "CALLOC is err");
                return false;
            }
            n32Ret = WJV2_ParkingGuide_DfEnc(pstruParkingGuide_node, &(pstruWjPAMData->struparkingAreaGuidance.struParkingGuide[u32i]));
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                         STACK_DF_MODULE,
                         "WJV2_ParkingGuide_DfEnc is err");
                FREEMEM(pstruParkingGuide_node);
                return false;
            }
            asn_sequence_add(&(pstruAsnPAMData->parkingAreaGuidance->list), pstruParkingGuide_node);
        }
    }
    else
    {
        pstruAsnPAMData->parkingAreaGuidance = NULL;
    }
    return true;
}
/**
* @brief     WJV2_PAMData_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_PAMData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_PAMData *pstruWjPAMData = (WJV2_STRU_PAMData *)pvoidWjMsg;
    PAMData_t *pstruAsnPAMData = (PAMData_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnPAMData->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnPAMData->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnPAMData->msgCnt = %d",
                 pstruAsnPAMData->msgCnt);
        return false;
    }
    pstruWjPAMData->n32msgCnt = pstruAsnPAMData->msgCnt;
    if (NULL != pstruAsnPAMData->timeStamp)
    {
        if ((WJV2_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnPAMData->timeStamp)) || (WJV2_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnPAMData->timeStamp)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:*(pstruAsnPAMData->timeStamp) = %d",
                     *(pstruAsnPAMData->timeStamp));
            return false;
        }
        pstruWjPAMData->n32timeStamp = *(pstruAsnPAMData->timeStamp);
        pstruWjPAMData->u8timeStampPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjPAMData->u8timeStampPresent = WJV2_ABSENT;
    }
    n32Ret = WJV2_ParkingLotInfo_DfDec(&(pstruAsnPAMData->parkingLotInfo), &(pstruWjPAMData->struparkingLotInfo));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_ParkingLotInfo_DfDec is err");
        return false;
    }
    n32Ret = WJV2_PAMNodeList_DfDec(&(pstruAsnPAMData->pamNodes), &(pstruWjPAMData->strupamNodes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_PAMNodeList_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnPAMData->parkingAreaGuidance)
    {
        if ((WJV2_MAX_LIST_ParkingGuide_LEN < pstruAsnPAMData->parkingAreaGuidance->list.count) || (WJV2_MIN_LIST_ParkingGuide_LEN > pstruAsnPAMData->parkingAreaGuidance->list.count))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnPAMData->parkingAreaGuidance->list.count = %d",
                     pstruAsnPAMData->parkingAreaGuidance->list.count);
            return false;
        }
        for (u32i = 0; u32i < pstruAsnPAMData->parkingAreaGuidance->list.count; u32i++)
        {
            n32Ret = WJV2_ParkingGuide_DfDec(pstruAsnPAMData->parkingAreaGuidance->list.array[u32i],
                                             &(pstruWjPAMData->struparkingAreaGuidance.struParkingGuide[u32i]));
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                         STACK_DF_MODULE,
                         "WJV2_ParkingGuide_DfDec is err");
                return false;
            }
        }
        pstruWjPAMData->struparkingAreaGuidance.u8ParkingGuideNum = (uint8_t)u32i;
        pstruWjPAMData->u8parkingAreaGuidancePresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjPAMData->u8parkingAreaGuidancePresent = WJV2_ABSENT;
    }
    return true;
}
/**
* @brief     WJV2_CLPMMData_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_CLPMMData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_CLPMM *pstruWjCLPMM = (WJV2_STRU_CLPMM *)pvoidWjMsg;
    CLPMM_t *pstruAsnCLPMM = (CLPMM_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjCLPMM->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjCLPMM->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjCLPMM->n32msgCnt = %d",
                 pstruWjCLPMM->n32msgCnt);
        return false;
    }
    pstruAsnCLPMM->msgCnt = pstruWjCLPMM->n32msgCnt;
    pstruAsnCLPMM->id.size = WJV2_MAX_ID_SIZE;
    pstruAsnCLPMM->id.buf = CALLOC(pstruAsnCLPMM->id.size, sizeof(uint8_t));
    if (NULL == pstruAsnCLPMM->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnCLPMM->id.buf, pstruWjCLPMM->u8OCTid, pstruAsnCLPMM->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruWjCLPMM->n32secMark) || (WJV2_MIN_DSECOND_SIZE > pstruWjCLPMM->n32secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjCLPMM->n32secMark = %d",
                 pstruWjCLPMM->n32secMark);
        return false;
    }
    pstruAsnCLPMM->secMark = pstruWjCLPMM->n32secMark;
    pstruAsnCLPMM->pid.size = WJV2_MAX_PID_SIZE;
    pstruAsnCLPMM->pid.buf = CALLOC(pstruAsnCLPMM->pid.size, sizeof(uint8_t));
    if (NULL == pstruAsnCLPMM->pid.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnCLPMM->pid.buf, pstruWjCLPMM->u8OCTpid, pstruAsnCLPMM->pid.size);
    pstruAsnCLPMM->role = pstruWjCLPMM->enumrole;
    pstruAsnCLPMM->status = pstruWjCLPMM->enumstatus;
    if (WJV2_PRESENT == pstruWjCLPMM->u8leadingExtPresent)
    {
        pstruAsnCLPMM->leadingExt = CALLOC(1, sizeof(struct MemberManagement));
        if (NULL == pstruAsnCLPMM->leadingExt)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_MemberManagement_DfEnc(pstruAsnCLPMM->leadingExt, &(pstruWjCLPMM->struleadingExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_MemberManagement_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnCLPMM->leadingExt = NULL;
    }
    return true;
}
/**
* @brief     WJV2_CLPMMData_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_CLPMMData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_CLPMM *pstruWjCLPMM = (WJV2_STRU_CLPMM *)pvoidWjMsg;
    CLPMM_t *pstruAsnCLPMM = (CLPMM_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnCLPMM->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnCLPMM->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnCLPMM->msgCnt = %d",
                 pstruAsnCLPMM->msgCnt);
        return false;
    }
    pstruWjCLPMM->n32msgCnt = pstruAsnCLPMM->msgCnt;
    memcpy(pstruWjCLPMM->u8OCTid, pstruAsnCLPMM->id.buf, pstruAsnCLPMM->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruAsnCLPMM->secMark) || (WJV2_MIN_DSECOND_SIZE > pstruAsnCLPMM->secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnCLPMM->secMark = %d",
                 pstruAsnCLPMM->secMark);
        return false;
    }
    pstruWjCLPMM->n32secMark = pstruAsnCLPMM->secMark;
    memcpy(pstruWjCLPMM->u8OCTpid, pstruAsnCLPMM->pid.buf, pstruAsnCLPMM->pid.size);
    pstruWjCLPMM->enumrole = pstruAsnCLPMM->role;
    pstruWjCLPMM->enumstatus = pstruAsnCLPMM->status;
    if (NULL != pstruAsnCLPMM->leadingExt)
    {
        n32Ret = WJV2_MemberManagement_DfDec(pstruAsnCLPMM->leadingExt, &(pstruWjCLPMM->struleadingExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_MemberManagement_DfDec is err");
            return false;
        }
        pstruWjCLPMM->u8leadingExtPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjCLPMM->u8leadingExtPresent = WJV2_ABSENT;
    }

    return true;
}
/**
* @brief     WJV2_PSMData_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_PSMData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_PersonalSafetyMessage *pstruWjPersonalSafetyMessage = (WJV2_STRU_PersonalSafetyMessage *)pvoidWjMsg;
    PersonalSafetyMessage_t *pstruAsnPersonalSafetyMessage = (PersonalSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjPersonalSafetyMessage->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjPersonalSafetyMessage->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjPersonalSafetyMessage->n32msgCnt = %d",
                 pstruWjPersonalSafetyMessage->n32msgCnt);
        return false;
    }
    pstruAsnPersonalSafetyMessage->msgCnt = pstruWjPersonalSafetyMessage->n32msgCnt;
    pstruAsnPersonalSafetyMessage->id.size = WJV2_MAX_ID_SIZE;
    pstruAsnPersonalSafetyMessage->id.buf = CALLOC(pstruAsnPersonalSafetyMessage->id.size, sizeof(uint8_t));
    if (NULL == pstruAsnPersonalSafetyMessage->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnPersonalSafetyMessage->id.buf, pstruWjPersonalSafetyMessage->u8OCTid, pstruAsnPersonalSafetyMessage->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruWjPersonalSafetyMessage->n32secMark) || (WJV2_MIN_DSECOND_SIZE > pstruWjPersonalSafetyMessage->n32secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjPersonalSafetyMessage->n32secMark = %d",
                 pstruWjPersonalSafetyMessage->n32secMark);
        return false;
    }
    pstruAsnPersonalSafetyMessage->secMark = pstruWjPersonalSafetyMessage->n32secMark;
    if (WJV2_PRESENT == pstruWjPersonalSafetyMessage->u8timeConfidencePresent)
    {
        pstruAsnPersonalSafetyMessage->timeConfidence = CALLOC(1, sizeof(TimeConfidence_t));
        if (NULL == pstruAsnPersonalSafetyMessage->timeConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnPersonalSafetyMessage->timeConfidence) = pstruWjPersonalSafetyMessage->enumtimeConfidence;
    }
    else
    {
        pstruAsnPersonalSafetyMessage->timeConfidence = NULL;
    }
    n32Ret = WJV2_Position3D_DfEnc(&(pstruAsnPersonalSafetyMessage->pos),
                                   &(pstruWjPersonalSafetyMessage->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfEnc is err");
        return false;
    }
    n32Ret = WJV2_PositionalAccuracy_DfEnc(&(pstruAsnPersonalSafetyMessage->posAccuracy), &(pstruWjPersonalSafetyMessage->struposAccuracy));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_PositionalAccuracy_DfEnc is err");
        return false;
    }
    if ((WJV2_MAX_SPEED_SIZE < pstruWjPersonalSafetyMessage->n32speed) || (WJV2_MIN_SPEED_SIZE > pstruWjPersonalSafetyMessage->n32speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjPersonalSafetyMessage->n32speed = %d",
                 pstruWjPersonalSafetyMessage->n32speed);
        return false;
    }
    pstruAsnPersonalSafetyMessage->speed = pstruWjPersonalSafetyMessage->n32speed;
    if ((WJV2_MAX_HEADING_SIZE < pstruWjPersonalSafetyMessage->n32heading) || (WJV2_MIN_HEADING_SIZE > pstruWjPersonalSafetyMessage->n32heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjPersonalSafetyMessage->n32heading = %d",
                 pstruWjPersonalSafetyMessage->n32heading);
        return false;
    }
    pstruAsnPersonalSafetyMessage->heading = pstruWjPersonalSafetyMessage->n32heading;
    if (WJV2_PRESENT == pstruWjPersonalSafetyMessage->u8accelSetPresent)
    {
        pstruAsnPersonalSafetyMessage->accelSet = CALLOC(1, sizeof(struct AccelerationSet4Way));
        if (NULL == pstruAsnPersonalSafetyMessage->accelSet)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_AccelerationSet4Way_DfEnc(pstruAsnPersonalSafetyMessage->accelSet, &(pstruWjPersonalSafetyMessage->struaccelSet));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_AccelerationSet4Way_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPersonalSafetyMessage->accelSet = NULL;
    }
    if (WJV2_PRESENT == pstruWjPersonalSafetyMessage->u8pathHistoryPresent)
    {
        pstruAsnPersonalSafetyMessage->pathHistory = CALLOC(1, sizeof(struct PathHistory));
        if (NULL == pstruAsnPersonalSafetyMessage->pathHistory)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_PathHistory_DfEnc(pstruAsnPersonalSafetyMessage->pathHistory, &(pstruWjPersonalSafetyMessage->strupathHistory));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PathHistory_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPersonalSafetyMessage->pathHistory = NULL;
    }
    if (WJV2_PRESENT == pstruWjPersonalSafetyMessage->u8path_PlanningPresent)
    {
        pstruAsnPersonalSafetyMessage->path_Planning = CALLOC(1, sizeof(struct PathPlanning));
        if (NULL == pstruAsnPersonalSafetyMessage->path_Planning)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_PathPlanning_DfEnc(pstruAsnPersonalSafetyMessage->path_Planning, &(pstruWjPersonalSafetyMessage->strupath_Planning));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PathPlanning_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPersonalSafetyMessage->path_Planning = NULL;
    }
    if ((WJV2_MAX_OVERALLRADIUS_SIZE < pstruWjPersonalSafetyMessage->n32overallRadius) || (WJV2_MIN_OVERALLRADIUS_SIZE > pstruWjPersonalSafetyMessage->n32overallRadius))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjPersonalSafetyMessage->n32overallRadius = %d",
                 pstruWjPersonalSafetyMessage->n32overallRadius);
        return false;
    }
    pstruAsnPersonalSafetyMessage->overallRadius = pstruWjPersonalSafetyMessage->n32overallRadius;
    n32Ret = WJV2_NonMotorData_DfEnc(&(pstruAsnPersonalSafetyMessage->non_motorData), &(pstruWjPersonalSafetyMessage->strunon_motorData));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_NonMotorData_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_PSMData_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_PSMData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_PersonalSafetyMessage *pstruWjPersonalSafetyMessage = (WJV2_STRU_PersonalSafetyMessage *)pvoidWjMsg;
    PersonalSafetyMessage_t *pstruAsnPersonalSafetyMessage = (PersonalSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnPersonalSafetyMessage->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnPersonalSafetyMessage->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnPersonalSafetyMessage->msgCnt = %d",
                 pstruAsnPersonalSafetyMessage->msgCnt);
        return false;
    }
    pstruWjPersonalSafetyMessage->n32msgCnt = pstruAsnPersonalSafetyMessage->msgCnt;
    memcpy(pstruWjPersonalSafetyMessage->u8OCTid, pstruAsnPersonalSafetyMessage->id.buf, pstruAsnPersonalSafetyMessage->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruAsnPersonalSafetyMessage->secMark) || (WJV2_MIN_DSECOND_SIZE > pstruAsnPersonalSafetyMessage->secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnPersonalSafetyMessage->secMark = %d",
                 pstruAsnPersonalSafetyMessage->secMark);
        return false;
    }
    pstruWjPersonalSafetyMessage->n32secMark = pstruAsnPersonalSafetyMessage->secMark;
    if (NULL != pstruAsnPersonalSafetyMessage->timeConfidence)
    {
        pstruWjPersonalSafetyMessage->enumtimeConfidence = *(pstruAsnPersonalSafetyMessage->timeConfidence);
        pstruWjPersonalSafetyMessage->u8timeConfidencePresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjPersonalSafetyMessage->u8timeConfidencePresent = WJV2_ABSENT;
    }
    n32Ret = WJV2_Position3D_DfDec(&(pstruAsnPersonalSafetyMessage->pos),
                                   &(pstruWjPersonalSafetyMessage->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfDec is err");
        return false;
    }
    if ((WJV2_MAX_SPEED_SIZE < pstruAsnPersonalSafetyMessage->speed) || (WJV2_MIN_SPEED_SIZE > pstruAsnPersonalSafetyMessage->speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnPersonalSafetyMessage->speed = %d",
                 pstruAsnPersonalSafetyMessage->speed);
        return false;
    }
    pstruWjPersonalSafetyMessage->n32speed = pstruAsnPersonalSafetyMessage->speed;
    if ((WJV2_MAX_HEADING_SIZE < pstruAsnPersonalSafetyMessage->heading) || (WJV2_MIN_HEADING_SIZE > pstruAsnPersonalSafetyMessage->heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnPersonalSafetyMessage->heading = %d",
                 pstruAsnPersonalSafetyMessage->heading);
        return false;
    }
    pstruWjPersonalSafetyMessage->n32heading = pstruAsnPersonalSafetyMessage->heading;
    if (NULL != pstruAsnPersonalSafetyMessage->accelSet)
    {
        n32Ret = WJV2_AccelerationSet4Way_DfDec(pstruAsnPersonalSafetyMessage->accelSet, &(pstruWjPersonalSafetyMessage->struaccelSet));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_AccelerationSet4Way_DfDec is err");
            return false;
        }
        pstruWjPersonalSafetyMessage->u8accelSetPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjPersonalSafetyMessage->u8accelSetPresent = WJV2_ABSENT;
    }
    if (NULL != pstruAsnPersonalSafetyMessage->pathHistory)
    {
        n32Ret = WJV2_PathHistory_DfDec(pstruAsnPersonalSafetyMessage->pathHistory, &(pstruWjPersonalSafetyMessage->strupathHistory));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PathHistory_DfDec is err");
            return false;
        }
        pstruWjPersonalSafetyMessage->u8pathHistoryPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjPersonalSafetyMessage->u8pathHistoryPresent = WJV2_ABSENT;
    }
    if (NULL != pstruAsnPersonalSafetyMessage->path_Planning)
    {
        n32Ret = WJV2_PathPlanning_DfDec(pstruAsnPersonalSafetyMessage->path_Planning, &(pstruWjPersonalSafetyMessage->strupath_Planning));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PathPlanning_DfDec is err");
            return false;
        }
        pstruWjPersonalSafetyMessage->u8path_PlanningPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjPersonalSafetyMessage->u8path_PlanningPresent = WJV2_ABSENT;
    }
    if ((WJV2_MAX_OVERALLRADIUS_SIZE < pstruAsnPersonalSafetyMessage->overallRadius) || (WJV2_MIN_OVERALLRADIUS_SIZE > pstruAsnPersonalSafetyMessage->overallRadius))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnPersonalSafetyMessage->overallRadius = %d",
                 pstruAsnPersonalSafetyMessage->overallRadius);
        return false;
    }
    pstruWjPersonalSafetyMessage->n32overallRadius = pstruAsnPersonalSafetyMessage->overallRadius;
    n32Ret = WJV2_NonMotorData_DfDec(&(pstruAsnPersonalSafetyMessage->non_motorData), &(pstruWjPersonalSafetyMessage->strunon_motorData));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_NonMotorData_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_RSCData_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_RSCData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_RoadsideCoordination *pstruWjRoadsideCoordination = (WJV2_STRU_RoadsideCoordination *)pvoidWjMsg;
    RoadsideCoordination_t *pstruAsnRoadsideCoordination = (RoadsideCoordination_t *)pvoidAsnMsg;
    struct VehicleCoordination *pstruVehicleCoordination_node = NULL;
    struct LaneCoordination *pstruLaneCoordination_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjRoadsideCoordination->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjRoadsideCoordination->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjRoadsideCoordination->n32msgCnt = %d",
                 pstruWjRoadsideCoordination->n32msgCnt);
        return false;
    }
    pstruAsnRoadsideCoordination->msgCnt = pstruWjRoadsideCoordination->n32msgCnt;
    pstruAsnRoadsideCoordination->id.size = WJV2_MAX_ID_SIZE;
    pstruAsnRoadsideCoordination->id.buf = CALLOC(pstruAsnRoadsideCoordination->id.size, sizeof(uint8_t));
    if (NULL == pstruAsnRoadsideCoordination->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnRoadsideCoordination->id.buf, pstruWjRoadsideCoordination->u8OCTid, pstruAsnRoadsideCoordination->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruWjRoadsideCoordination->n32secMark) || (WJV2_MIN_DSECOND_SIZE > pstruWjRoadsideCoordination->n32secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjRoadsideCoordination->n32secMark = %d",
                 pstruWjRoadsideCoordination->n32secMark);
        return false;
    }
    pstruAsnRoadsideCoordination->secMark = pstruWjRoadsideCoordination->n32secMark;
    n32Ret = WJV2_Position3D_DfEnc(&(pstruAsnRoadsideCoordination->refPos), &(pstruWjRoadsideCoordination->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfEnc is err");
        return false;
    }
    if (WJV2_PRESENT == pstruWjRoadsideCoordination->u8coordinatesPresent)
    {
        pstruAsnRoadsideCoordination->coordinates = CALLOC(1, sizeof(struct coordinates));
        if (NULL == pstruAsnRoadsideCoordination->coordinates)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        if ((WJV2_MAX_LIST_COORDINATES_LEN < pstruWjRoadsideCoordination->strucoordinatesList.u8coordinatesNum) || (WJV2_MIN_LIST_COORDINATES_LEN > pstruWjRoadsideCoordination->strucoordinatesList.u8coordinatesNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjRoadsideCoordination->strucoordinatesList.u8coordinatesNum = %d",
                     pstruWjRoadsideCoordination->strucoordinatesList.u8coordinatesNum);
            return false;
        }
        for (u32i = 0; u32i < pstruWjRoadsideCoordination->strucoordinatesList.u8coordinatesNum; u32i++)
        {
            pstruVehicleCoordination_node = CALLOC(1, sizeof(struct VehicleCoordination));
            if (NULL == pstruVehicleCoordination_node)
            {
                LogPrint(LOG_LEVEL_ERR,
                         STACK_DF_MODULE,
                         "CALLOC is err");
                return false;
            }
            n32Ret = WJV2_VehicleCoordination_DfEnc(pstruVehicleCoordination_node, &(pstruWjRoadsideCoordination->strucoordinatesList.strucoordinates[u32i]));
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                         STACK_DF_MODULE,
                         "WJV2_VehicleCoordination_DfEnc is err");
                FREEMEM(pstruVehicleCoordination_node);
                return false;
            }
            asn_sequence_add(&(pstruAsnRoadsideCoordination->coordinates->list), pstruVehicleCoordination_node);
        }
    }
    else
    {
        pstruAsnRoadsideCoordination->coordinates = NULL;
    }
    if (WJV2_PRESENT == pstruWjRoadsideCoordination->u8laneCoordinatesPresent)
    {
        pstruAsnRoadsideCoordination->laneCoordinates = CALLOC(1, sizeof(struct laneCoordinates));
        if (NULL == pstruAsnRoadsideCoordination->laneCoordinates)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        if ((WJV2_MAX_LIST_LANECOORDINATES_LEN < pstruWjRoadsideCoordination->strulaneCoordinatesList.u8laneCoordinatesNum) || (WJV2_MIN_LIST_LANECOORDINATES_LEN > pstruWjRoadsideCoordination->strulaneCoordinatesList.u8laneCoordinatesNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjRoadsideCoordination->strulaneCoordinatesList.u8laneCoordinatesNum = %d",
                     pstruWjRoadsideCoordination->strulaneCoordinatesList.u8laneCoordinatesNum);
            return false;
        }
        for (u32i = 0; u32i < pstruWjRoadsideCoordination->strulaneCoordinatesList.u8laneCoordinatesNum; u32i++)
        {
            pstruLaneCoordination_node = CALLOC(1, sizeof(struct LaneCoordination));
            if (NULL == pstruLaneCoordination_node)
            {
                LogPrint(LOG_LEVEL_ERR,
                         STACK_DF_MODULE,
                         "CALLOC is err");
                return false;
            }
            n32Ret = WJV2_LaneCoordination_DfEnc(pstruLaneCoordination_node, &(pstruWjRoadsideCoordination->strulaneCoordinatesList.strulaneCoordinates[u32i]));
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                         STACK_DF_MODULE,
                         "WJV2_LaneCoordination_DfEnc is err");
                FREEMEM(pstruLaneCoordination_node);
                return false;
            }
            asn_sequence_add(&(pstruAsnRoadsideCoordination->laneCoordinates->list), pstruLaneCoordination_node);
        }
    }
    else
    {
        pstruAsnRoadsideCoordination->coordinates = NULL;
    }
    return true;
}
/**
* @brief     WJV2_RSCData_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_RSCData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_RoadsideCoordination *pstruWjRoadsideCoordination = (WJV2_STRU_RoadsideCoordination *)pvoidWjMsg;
    RoadsideCoordination_t *pstruAsnRoadsideCoordination = (RoadsideCoordination_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnRoadsideCoordination->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnRoadsideCoordination->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnRoadsideCoordination->msgCnt = %d",
                 pstruAsnRoadsideCoordination->msgCnt);
        return false;
    }
    pstruWjRoadsideCoordination->n32msgCnt = pstruAsnRoadsideCoordination->msgCnt;
    memcpy(pstruWjRoadsideCoordination->u8OCTid, pstruAsnRoadsideCoordination->id.buf, pstruAsnRoadsideCoordination->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruAsnRoadsideCoordination->secMark) || (WJV2_MIN_DSECOND_SIZE > pstruAsnRoadsideCoordination->secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnRoadsideCoordination->secMark = %d",
                 pstruAsnRoadsideCoordination->secMark);
        return false;
    }
    pstruWjRoadsideCoordination->n32secMark = pstruAsnRoadsideCoordination->secMark;
    n32Ret = WJV2_Position3D_DfDec(&(pstruAsnRoadsideCoordination->refPos), &(pstruWjRoadsideCoordination->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfDec is err");
        return false;
    }

    if (NULL != pstruAsnRoadsideCoordination->coordinates)
    {
        if ((WJV2_MAX_LIST_COORDINATES_LEN < pstruAsnRoadsideCoordination->coordinates->list.count) || (WJV2_MIN_LIST_COORDINATES_LEN > pstruAsnRoadsideCoordination->coordinates->list.count))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnRoadsideCoordination->coordinates->list.count = %d",
                     pstruAsnRoadsideCoordination->coordinates->list.count);
            return false;
        }
        for (u32i = 0; u32i < pstruAsnRoadsideCoordination->coordinates->list.count; u32i++)
        {
            n32Ret = WJV2_VehicleCoordination_DfDec(pstruAsnRoadsideCoordination->coordinates->list.array[u32i],
                                                    &(pstruWjRoadsideCoordination->strucoordinatesList.strucoordinates[u32i]));
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                         STACK_DF_MODULE,
                         "WJV2_LaneCoordination_DfDec is err");
                return false;
            }
        }
        pstruWjRoadsideCoordination->strucoordinatesList.u8coordinatesNum = (uint8_t)u32i;
        pstruWjRoadsideCoordination->u8coordinatesPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjRoadsideCoordination->u8coordinatesPresent = WJV2_ABSENT;
    }
    if (NULL != pstruAsnRoadsideCoordination->laneCoordinates)
    {
        if ((WJV2_MAX_LIST_LANECOORDINATES_LEN < pstruAsnRoadsideCoordination->laneCoordinates->list.count) || (WJV2_MIN_LIST_LANECOORDINATES_LEN > pstruAsnRoadsideCoordination->laneCoordinates->list.count))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnRoadsideCoordination->laneCoordinates->list.count = %d",
                     pstruAsnRoadsideCoordination->laneCoordinates->list.count);
            return false;
        }
        for (u32i = 0; u32i < pstruAsnRoadsideCoordination->laneCoordinates->list.count; u32i++)
        {
            n32Ret = WJV2_LaneCoordination_DfDec(pstruAsnRoadsideCoordination->laneCoordinates->list.array[u32i],
                                                 &(pstruWjRoadsideCoordination->strulaneCoordinatesList.strulaneCoordinates[u32i]));
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                         STACK_DF_MODULE,
                         "WJV2_LaneCoordination_DfDec is err");
                return false;
            }
        }
        pstruWjRoadsideCoordination->strulaneCoordinatesList.u8laneCoordinatesNum = (uint8_t)u32i;
        pstruWjRoadsideCoordination->u8laneCoordinatesPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjRoadsideCoordination->u8laneCoordinatesPresent = WJV2_ABSENT;
    }
    return true;
}
/**
* @brief     WJV2_RTCMData_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_RTCMData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_RTCMcorrections *pstruWjRTCMcorrections = (WJV2_STRU_RTCMcorrections *)pvoidWjMsg;
    RTCMcorrections_t *pstruAsnRTCMcorrections = (RTCMcorrections_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    struct RTCMmsg *pstruRTCMmsg_node = NULL;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjRTCMcorrections->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjRTCMcorrections->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjRTCMcorrections->n32msgCnt = %d",
                 pstruWjRTCMcorrections->n32msgCnt);
        return false;
    }
    pstruAsnRTCMcorrections->msgCnt = pstruWjRTCMcorrections->n32msgCnt;
    if ((WJV2_MAX_LIST_corrections_LEN < pstruWjRTCMcorrections->strucorrections.u8RTCMmsgNum) || (WJV2_MIN_LIST_corrections_LEN > pstruWjRTCMcorrections->strucorrections.u8RTCMmsgNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjRTCMcorrections->strucorrections.u8RTCMmsgNum = %d",
                 pstruWjRTCMcorrections->strucorrections.u8RTCMmsgNum);
        return false;
    }
    for (u32i = 0; u32i < pstruWjRTCMcorrections->strucorrections.u8RTCMmsgNum; u32i++)
    {
        pstruRTCMmsg_node = CALLOC(1, sizeof(struct RTCMmsg));
        if (NULL == pstruRTCMmsg_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_RTCMmsg_DfEnc(pstruRTCMmsg_node, &(pstruWjRTCMcorrections->strucorrections.struRTCMmsg[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV2_RTCMmsg_DfEnc is err");
            FREEMEM(pstruRTCMmsg_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnRTCMcorrections->corrections.list), pstruRTCMmsg_node);
    }
    return true;
}
/**
* @brief     WJV2_RTCMData_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_RTCMData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_RTCMcorrections *pstruWjRTCMcorrections = (WJV2_STRU_RTCMcorrections *)pvoidWjMsg;
    RTCMcorrections_t *pstruAsnRTCMcorrections = (RTCMcorrections_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnRTCMcorrections->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnRTCMcorrections->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnRTCMcorrections->msgCnt = %d",
                 pstruAsnRTCMcorrections->msgCnt);
        return false;
    }
    pstruWjRTCMcorrections->n32msgCnt = pstruAsnRTCMcorrections->msgCnt;
    if ((WJV2_MAX_LIST_corrections_LEN < pstruAsnRTCMcorrections->corrections.list.count) || (WJV2_MIN_LIST_corrections_LEN > pstruAsnRTCMcorrections->corrections.list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnRTCMcorrections->corrections.list.count = %d",
                 pstruAsnRTCMcorrections->corrections.list.count);
        return false;
    }
    for (u32i = 0; u32i < pstruAsnRTCMcorrections->corrections.list.count; u32i++)
    {
        n32Ret = WJV2_RTCMmsg_DfDec(pstruAsnRTCMcorrections->corrections.list.array[u32i],
                                    &(pstruWjRTCMcorrections->strucorrections.struRTCMmsg[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV2_RTCMmsg_DfDec is err");
            return false;
        }
    }
    pstruWjRTCMcorrections->strucorrections.u8RTCMmsgNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV2_SSMData_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_SSMData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_SensorSharingMsg *pstruWjSensorSharingMsg = (WJV2_STRU_SensorSharingMsg *)pvoidWjMsg;
    SensorSharingMsg_t *pstruAsnSensorSharingMsg = (SensorSharingMsg_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjSensorSharingMsg->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjSensorSharingMsg->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjSensorSharingMsg->n32msgCnt = %d",
                 pstruWjSensorSharingMsg->n32msgCnt);
        return false;
    }
    pstruAsnSensorSharingMsg->msgCnt = pstruWjSensorSharingMsg->n32msgCnt;
    pstruAsnSensorSharingMsg->id.size = WJV2_MAX_ID_SIZE;
    pstruAsnSensorSharingMsg->id.buf = CALLOC(pstruAsnSensorSharingMsg->id.size, sizeof(uint8_t));
    if (NULL == pstruAsnSensorSharingMsg->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnSensorSharingMsg->id.buf, pstruWjSensorSharingMsg->u8OCTid, pstruAsnSensorSharingMsg->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruWjSensorSharingMsg->n32secMark) || (WJV2_MIN_DSECOND_SIZE > pstruWjSensorSharingMsg->n32secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjSensorSharingMsg->n32secMark = %d",
                 pstruWjSensorSharingMsg->n32secMark);
        return false;
    }
    pstruAsnSensorSharingMsg->secMark = pstruWjSensorSharingMsg->n32secMark;
    n32Ret = WJV2_Position3D_DfEnc(&(pstruAsnSensorSharingMsg->sensorPos), &(pstruWjSensorSharingMsg->strusensorPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfEnc is err");
        return false;
    }
    if (WJV2_PRESENT == pstruWjSensorSharingMsg->u8detectedRegionPresent)
    {
        pstruAsnSensorSharingMsg->detectedRegion = CALLOC(1, sizeof(struct DetectedRegion));
        if (NULL == pstruAsnSensorSharingMsg->detectedRegion)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_DetectedRegion_DfEnc(pstruAsnSensorSharingMsg->detectedRegion, &(pstruWjSensorSharingMsg->strudetectedRegion));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_DetectedRegion_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnSensorSharingMsg->detectedRegion = NULL;
    }
    if (WJV2_PRESENT == pstruWjSensorSharingMsg->u8participantsPresent)
    {
        pstruAsnSensorSharingMsg->participants = CALLOC(1, sizeof(struct DetectedPTCList));
        if (NULL == pstruAsnSensorSharingMsg->participants)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_DetectedPTCList_DfEnc(pstruAsnSensorSharingMsg->participants, &(pstruWjSensorSharingMsg->struparticipants));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_DetectedPTCList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnSensorSharingMsg->participants = NULL;
    }
    if (WJV2_PRESENT == pstruWjSensorSharingMsg->u8obstaclesPresent)
    {
        pstruAsnSensorSharingMsg->obstacles = CALLOC(1, sizeof(struct DetectedObstacleList));
        if (NULL == pstruAsnSensorSharingMsg->obstacles)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_DetectedObstacleList_DfEnc(pstruAsnSensorSharingMsg->obstacles, &(pstruWjSensorSharingMsg->struobstacles));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_DetectedObstacleList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnSensorSharingMsg->obstacles = NULL;
    }
    if (WJV2_PRESENT == pstruWjSensorSharingMsg->u8rtesPresent)
    {
        pstruAsnSensorSharingMsg->rtes = CALLOC(1, sizeof(struct RTEList));
        if (NULL == pstruAsnSensorSharingMsg->rtes)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_RTEList_DfEnc(pstruAsnSensorSharingMsg->rtes, &(pstruWjSensorSharingMsg->strurtes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RTEList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnSensorSharingMsg->rtes = NULL;
    }
    return true;
}
/**
* @brief     WJV2_SSMData_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_SSMData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_SensorSharingMsg *pstruWjSensorSharingMsg = (WJV2_STRU_SensorSharingMsg *)pvoidWjMsg;
    SensorSharingMsg_t *pstruAsnSensorSharingMsg = (SensorSharingMsg_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnSensorSharingMsg->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnSensorSharingMsg->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnSensorSharingMsg->msgCnt = %d",
                 pstruAsnSensorSharingMsg->msgCnt);
        return false;
    }
    pstruWjSensorSharingMsg->n32msgCnt = pstruAsnSensorSharingMsg->msgCnt;
    memcpy(pstruWjSensorSharingMsg->u8OCTid, pstruAsnSensorSharingMsg->id.buf, pstruAsnSensorSharingMsg->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruAsnSensorSharingMsg->secMark) || (WJV2_MIN_DSECOND_SIZE > pstruAsnSensorSharingMsg->secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnSensorSharingMsg->secMark = %d",
                 pstruAsnSensorSharingMsg->secMark);
        return false;
    }
    pstruWjSensorSharingMsg->n32secMark = pstruAsnSensorSharingMsg->secMark;
    n32Ret = WJV2_Position3D_DfDec(&(pstruAsnSensorSharingMsg->sensorPos), &(pstruWjSensorSharingMsg->strusensorPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnSensorSharingMsg->detectedRegion)
    {
        n32Ret = WJV2_DetectedRegion_DfDec(pstruAsnSensorSharingMsg->detectedRegion, &(pstruWjSensorSharingMsg->strudetectedRegion));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_DetectedRegion_DfDec is err");
            return false;
        }
        pstruWjSensorSharingMsg->u8detectedRegionPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjSensorSharingMsg->u8detectedRegionPresent = WJV2_ABSENT;
    }
    if (NULL != pstruAsnSensorSharingMsg->participants)
    {
        n32Ret = WJV2_DetectedPTCList_DfDec(pstruAsnSensorSharingMsg->participants, &(pstruWjSensorSharingMsg->struparticipants));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_DetectedPTCList_DfDec is err");
            return false;
        }
        pstruWjSensorSharingMsg->u8participantsPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjSensorSharingMsg->u8participantsPresent = WJV2_ABSENT;
    }
    if (NULL != pstruAsnSensorSharingMsg->obstacles)
    {
        n32Ret = WJV2_DetectedObstacleList_DfDec(pstruAsnSensorSharingMsg->obstacles, &(pstruWjSensorSharingMsg->struobstacles));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_DetectedObstacleList_DfDec is err");
            return false;
        }
        pstruWjSensorSharingMsg->u8obstaclesPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjSensorSharingMsg->u8obstaclesPresent = WJV2_ABSENT;
    }
    if (NULL != pstruAsnSensorSharingMsg->rtes)
    {
        n32Ret = WJV2_RTEList_DfDec(pstruAsnSensorSharingMsg->rtes, &(pstruWjSensorSharingMsg->strurtes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RTEList_DfDec is err");
            return false;
        }
        pstruWjSensorSharingMsg->u8rtesPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjSensorSharingMsg->u8rtesPresent = WJV2_ABSENT;
    }
    return true;
}
/**
* @brief     WJV2_VIRData_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_VIRData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_VehIntentionAndRequest *pstruWjVehIntentionAndRequest = (WJV2_STRU_VehIntentionAndRequest *)pvoidWjMsg;
    VehIntentionAndRequest_t *pstruAsnVehIntentionAndRequest = (VehIntentionAndRequest_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjVehIntentionAndRequest->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjVehIntentionAndRequest->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjVehIntentionAndRequest->n32msgCnt = %d",
                 pstruWjVehIntentionAndRequest->n32msgCnt);
        return false;
    }
    pstruAsnVehIntentionAndRequest->msgCnt = pstruWjVehIntentionAndRequest->n32msgCnt;
    pstruAsnVehIntentionAndRequest->id.size = WJV2_MAX_ID_SIZE;
    pstruAsnVehIntentionAndRequest->id.buf = CALLOC(pstruAsnVehIntentionAndRequest->id.size, sizeof(uint8_t));
    if (NULL == pstruAsnVehIntentionAndRequest->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnVehIntentionAndRequest->id.buf, pstruWjVehIntentionAndRequest->u8OCTid, pstruAsnVehIntentionAndRequest->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruWjVehIntentionAndRequest->n32secMark) || (WJV2_MIN_DSECOND_SIZE > pstruWjVehIntentionAndRequest->n32secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjVehIntentionAndRequest->n32secMark = %d",
                 pstruWjVehIntentionAndRequest->n32secMark);
        return false;
    }
    pstruAsnVehIntentionAndRequest->secMark = pstruWjVehIntentionAndRequest->n32secMark;
    n32Ret = WJV2_Position3D_DfEnc(&(pstruAsnVehIntentionAndRequest->refPos), &(pstruWjVehIntentionAndRequest->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfEnc is err");
        return false;
    }
    n32Ret = WJV2_IARData_DfEnc(&(pstruAsnVehIntentionAndRequest->intAndReq), &(pstruWjVehIntentionAndRequest->struintAndReq));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_IARData_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_VIRData_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_VIRData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_VehIntentionAndRequest *pstruWjVehIntentionAndRequest = (WJV2_STRU_VehIntentionAndRequest *)pvoidWjMsg;
    VehIntentionAndRequest_t *pstruAsnVehIntentionAndRequest = (VehIntentionAndRequest_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnVehIntentionAndRequest->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnVehIntentionAndRequest->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnVehIntentionAndRequest->msgCnt = %d",
                 pstruAsnVehIntentionAndRequest->msgCnt);
        return false;
    }
    pstruWjVehIntentionAndRequest->n32msgCnt = pstruAsnVehIntentionAndRequest->msgCnt;
    memcpy(pstruWjVehIntentionAndRequest->u8OCTid, pstruAsnVehIntentionAndRequest->id.buf, pstruAsnVehIntentionAndRequest->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruAsnVehIntentionAndRequest->secMark) || (WJV2_MIN_DSECOND_SIZE > pstruAsnVehIntentionAndRequest->secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnVehIntentionAndRequest->secMark = %d",
                 pstruAsnVehIntentionAndRequest->secMark);
        return false;
    }
    pstruWjVehIntentionAndRequest->n32secMark = pstruAsnVehIntentionAndRequest->secMark;
    n32Ret = WJV2_Position3D_DfDec(&(pstruAsnVehIntentionAndRequest->refPos), &(pstruWjVehIntentionAndRequest->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfDec is err");
        return false;
    }
    n32Ret = WJV2_IARData_DfDec(&(pstruAsnVehIntentionAndRequest->intAndReq), &(pstruWjVehIntentionAndRequest->struintAndReq));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_IARData_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_VPMData_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_VPMData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_VehiclePaymentMessage *pstruWjVehiclePaymentMessage = (WJV2_STRU_VehiclePaymentMessage *)pvoidWjMsg;
    VehiclePaymentMessage_t *pstruAsnVehiclePaymentMessage = (VehiclePaymentMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjVehiclePaymentMessage->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjVehiclePaymentMessage->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjVehiclePaymentMessage->n32msgCnt = %d",
                 pstruWjVehiclePaymentMessage->n32msgCnt);
        return false;
    }
    pstruAsnVehiclePaymentMessage->msgCnt = pstruWjVehiclePaymentMessage->n32msgCnt;
    switch (pstruWjVehiclePaymentMessage->strupayment.enumpresent)
    {
    case WJV2_payment_PR_initialzation_request:
        n32Ret = WJV2_RST_DfEnc(&(pstruAsnVehiclePaymentMessage->payment.choice.initialzation_request),
                                &(pstruWjVehiclePaymentMessage->strupayment.choice.struinitialzation_request));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RST_DfEnc is err");
            return false;
        }
        pstruAsnVehiclePaymentMessage->payment.present = payment_PR_initialzation_request;
        break;
    case WJV2_payment_PR_initialzation_response:
        n32Ret = WJV2_VSI_DfEnc(&(pstruAsnVehiclePaymentMessage->payment.choice.initialzation_response),
                                &(pstruWjVehiclePaymentMessage->strupayment.choice.struinitialzation_response));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_VSI_DfEnc is err");
            return false;
        }
        pstruAsnVehiclePaymentMessage->payment.present = payment_PR_initialzation_response;
        break;
    case WJV2_payment_PR_action_request:
        n32Ret = WJV2_ActionRequest_DfEnc(&(pstruAsnVehiclePaymentMessage->payment.choice.action_request),
                                          &(pstruWjVehiclePaymentMessage->strupayment.choice.struinitialzation_request));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_ActionRequest_DfEnc is err");
            return false;
        }
        pstruAsnVehiclePaymentMessage->payment.present = payment_PR_action_request;
        break;
    case WJV2_payment_PR_action_response:
        n32Ret = WJV2_ActionResponse_DfEnc(&(pstruAsnVehiclePaymentMessage->payment.choice.action_response),
                                           &(pstruWjVehiclePaymentMessage->strupayment.choice.struinitialzation_response));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_ActionResponse_DfEnc is err");
            return false;
        }
        pstruAsnVehiclePaymentMessage->payment.present = payment_PR_action_response;
        break;
    default:
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjVehiclePaymentMessage->strupayment.enumpresent = %d",
                 pstruWjVehiclePaymentMessage->strupayment.enumpresent);
        return false;
    }
    return true;
}
/**
* @brief     WJV2_VPMData_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_VPMData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_VehiclePaymentMessage *pstruWjVehiclePaymentMessage = (WJV2_STRU_VehiclePaymentMessage *)pvoidWjMsg;
    VehiclePaymentMessage_t *pstruAsnVehiclePaymentMessage = (VehiclePaymentMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnVehiclePaymentMessage->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnVehiclePaymentMessage->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnVehiclePaymentMessage->msgCnt = %d",
                 pstruAsnVehiclePaymentMessage->msgCnt);
        return false;
    }
    pstruWjVehiclePaymentMessage->n32msgCnt = pstruAsnVehiclePaymentMessage->msgCnt;
    switch (pstruAsnVehiclePaymentMessage->payment.present)
    {
    case payment_PR_initialzation_request:
        n32Ret = WJV2_RST_DfDec(&(pstruAsnVehiclePaymentMessage->payment.choice.initialzation_request),
                                &(pstruWjVehiclePaymentMessage->strupayment.choice.struinitialzation_request));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RST_DfDec is err");
            return false;
        }
        pstruWjVehiclePaymentMessage->strupayment.enumpresent = WJV2_payment_PR_initialzation_request;
        break;
    case payment_PR_initialzation_response:
        n32Ret = WJV2_VSI_DfDec(&(pstruAsnVehiclePaymentMessage->payment.choice.initialzation_response),
                                &(pstruWjVehiclePaymentMessage->strupayment.choice.struinitialzation_response));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_VSI_DfDec is err");
            return false;
        }
        pstruWjVehiclePaymentMessage->strupayment.enumpresent = WJV2_payment_PR_initialzation_response;
        break;
    case payment_PR_action_request:
        n32Ret = WJV2_ActionRequest_DfDec(&(pstruAsnVehiclePaymentMessage->payment.choice.action_request),
                                          &(pstruWjVehiclePaymentMessage->strupayment.choice.struinitialzation_request));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_ActionRequest_DfDec is err");
            return false;
        }
        pstruWjVehiclePaymentMessage->strupayment.enumpresent = WJV2_payment_PR_action_request;
        break;
    case payment_PR_action_response:
        n32Ret = WJV2_ActionResponse_DfDec(&(pstruAsnVehiclePaymentMessage->payment.choice.action_response),
                                           &(pstruWjVehiclePaymentMessage->strupayment.choice.struinitialzation_response));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_ActionResponse_DfDec is err");
            return false;
        }
        pstruWjVehiclePaymentMessage->strupayment.enumpresent = WJV2_payment_PR_action_response;
        break;
    default:
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnVehiclePaymentMessage->payment.present = %d",
                 pstruAsnVehiclePaymentMessage->payment.present);
        return false;
    }
    return true;
}
/**
* @brief     WJV2_TESTData_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_TESTData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_TestMsg *pstruWjTestMsg = (WJV2_STRU_TestMsg *)pvoidWjMsg;
    TestMsg_t *pstruAsnTestMsg = (TestMsg_t *)pvoidAsnMsg;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjTestMsg->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjTestMsg->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjTestMsg->n32msgCnt = %d",
                 pstruWjTestMsg->n32msgCnt);
        return false;
    }
    pstruAsnTestMsg->msgCnt = pstruWjTestMsg->n32msgCnt;
    if ((WJV2_MAX_userData_SIZE < pstruWjTestMsg->u16userDataNum) || (WJV2_MIN_userData_SIZE > pstruWjTestMsg->u16userDataNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjTestMsg->u16userDataNum = %d",
                 pstruWjTestMsg->u16userDataNum);
        return false;
    }
    pstruAsnTestMsg->userData.size = pstruWjTestMsg->u16userDataNum;
    pstruAsnTestMsg->userData.buf = CALLOC(pstruAsnTestMsg->userData.size, sizeof(uint8_t));
    if (NULL == pstruAsnTestMsg->userData.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnTestMsg->userData.buf, pstruWjTestMsg->u8OCTuserData, pstruAsnTestMsg->userData.size);
    return true;
}
/**
* @brief     WJV2_TESTData_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_TESTData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_TestMsg *pstruWjTestMsg = (WJV2_STRU_TestMsg *)pvoidWjMsg;
    TestMsg_t *pstruAsnTestMsg = (TestMsg_t *)pvoidAsnMsg;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnTestMsg->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnTestMsg->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnTestMsg->msgCnt = %d",
                 pstruAsnTestMsg->msgCnt);
        return false;
    }
    pstruWjTestMsg->n32msgCnt = pstruAsnTestMsg->msgCnt;
    memcpy(pstruWjTestMsg->u8OCTuserData, pstruAsnTestMsg->userData.buf, pstruAsnTestMsg->userData.size);
    return true;
}
/**
* @brief     WJV2_MessageFrameExtData_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_MessageFrameExtData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_MessageFrameExt *pstruWjMessageFrameExt = (WJV2_STRU_MessageFrameExt *)pvoidWjMsg;
    MessageFrameExt_t *pstruAsnMessageFrameExt = (MessageFrameExt_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    switch (pstruWjMessageFrameExt->enumpresent)
    {
    case WJV2_value_PR_TestMsg:
        pstruAsnMessageFrameExt->messageId = 0;
        pstruAsnMessageFrameExt->value.present = value_PR_TestMsg;
        n32Ret = WJV2_TESTData_MsgEnc(&(pstruAsnMessageFrameExt->value.choice.TestMsg), &(pstruWjMessageFrameExt->choice.struTestMsg));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_TESTData_MsgEnc is err");
            return false;
        }
        break;
    case WJV2_value_PR_RTCMcorrections:
        pstruAsnMessageFrameExt->messageId = 10;
        pstruAsnMessageFrameExt->value.present = value_PR_RTCMcorrections;
        n32Ret = WJV2_RTCMData_MsgEnc(&(pstruAsnMessageFrameExt->value.choice.RTCMcorrections), &(pstruWjMessageFrameExt->choice.struRTCMcorrections));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RTCMData_MsgEnc is err");
            return false;
        }
        break;
    case WJV2_value_PR_PAMData:
        pstruAsnMessageFrameExt->messageId = 14;
        pstruAsnMessageFrameExt->value.present = value_PR_PAMData;
        n32Ret = WJV2_PAMData_MsgEnc(&(pstruAsnMessageFrameExt->value.choice.PAMData), &(pstruWjMessageFrameExt->choice.struPAMData));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PAMData_MsgEnc is err");
            return false;
        }
        break;
    case WJV2_value_PR_CLPMM:
        pstruAsnMessageFrameExt->messageId = 16;
        pstruAsnMessageFrameExt->value.present = value_PR_CLPMM;
        n32Ret = WJV2_CLPMMData_MsgEnc(&(pstruAsnMessageFrameExt->value.choice.CLPMM), &(pstruWjMessageFrameExt->choice.struCLPMM));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_CLPMMData_MsgEnc is err");
            return false;
        }
        break;
    case WJV2_value_PR_PersonalSafetyMessage:
        pstruAsnMessageFrameExt->messageId = 15;
        pstruAsnMessageFrameExt->value.present = value_PR_PersonalSafetyMessage;
        n32Ret = WJV2_PSMData_MsgEnc(&(pstruAsnMessageFrameExt->value.choice.PersonalSafetyMessage), &(pstruWjMessageFrameExt->choice.struPersonalSafetyMessage));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PSMData_MsgEnc is err");
            return false;
        }
        break;
    case WJV2_value_PR_RoadsideCoordination:
        pstruAsnMessageFrameExt->messageId = 11;
        pstruAsnMessageFrameExt->value.present = value_PR_RoadsideCoordination;
        n32Ret = WJV2_RSCData_MsgEnc(&(pstruAsnMessageFrameExt->value.choice.RoadsideCoordination), &(pstruWjMessageFrameExt->choice.struRoadsideCoordination));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RSCData_MsgEnc is err");
            return false;
        }
        break;
    case WJV2_value_PR_SensorSharingMsg:
        pstruAsnMessageFrameExt->messageId = 12;
        pstruAsnMessageFrameExt->value.present = value_PR_SensorSharingMsg;
        n32Ret = WJV2_SSMData_MsgEnc(&(pstruAsnMessageFrameExt->value.choice.SensorSharingMsg), &(pstruWjMessageFrameExt->choice.struSensorSharingMsg));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_SSMData_MsgEnc is err");
            return false;
        }
        break;
    case WJV2_value_PR_VehIntentionAndRequest:
        pstruAsnMessageFrameExt->messageId = 13;
        pstruAsnMessageFrameExt->value.present = value_PR_VehIntentionAndRequest;
        n32Ret = WJV2_VIRData_MsgEnc(&(pstruAsnMessageFrameExt->value.choice.VehIntentionAndRequest), &(pstruWjMessageFrameExt->choice.struVehIntentionAndRequest));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_VIRData_MsgEnc is err");
            return false;
        }
        break;
    case WJV2_value_PR_VehiclePaymentMessage:
        pstruAsnMessageFrameExt->messageId = 17;
        pstruAsnMessageFrameExt->value.present = value_PR_VehiclePaymentMessage;
        n32Ret = WJV2_VPMData_MsgEnc(&(pstruAsnMessageFrameExt->value.choice.VehiclePaymentMessage), &(pstruWjMessageFrameExt->choice.struVehiclePaymentMessage));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_VPMData_MsgEnc is err");
            return false;
        }
        break;
    default:
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjMessageFrameExt->enumpresent = %d",
                 pstruWjMessageFrameExt->enumpresent);
        return false;
    }
    return true;
}
/**
* @brief     WJV2_MessageFrameExtData_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_MessageFrameExtData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_MessageFrameExt *pstruWjMessageFrameExt = (WJV2_STRU_MessageFrameExt *)pvoidWjMsg;
    MessageFrameExt_t *pstruAsnMessageFrameExt = (MessageFrameExt_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    switch (pstruAsnMessageFrameExt->value.present)
    {
    case value_PR_TestMsg:
        pstruWjMessageFrameExt->enumpresent = WJV2_value_PR_TestMsg;
        n32Ret = WJV2_TESTData_MsgDec(&(pstruAsnMessageFrameExt->value.choice.TestMsg), &(pstruWjMessageFrameExt->choice.struTestMsg));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_TESTData_MsgDec is err");
            return false;
        }
        break;
    case value_PR_RTCMcorrections:
        pstruWjMessageFrameExt->enumpresent = WJV2_value_PR_RTCMcorrections;
        n32Ret = WJV2_RTCMData_MsgDec(&(pstruAsnMessageFrameExt->value.choice.RTCMcorrections), &(pstruWjMessageFrameExt->choice.struRTCMcorrections));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RTCMData_MsgDec is err");
            return false;
        }
        break;
    case value_PR_PAMData:
        pstruWjMessageFrameExt->enumpresent = WJV2_value_PR_PAMData;
        n32Ret = WJV2_PAMData_MsgDec(&(pstruAsnMessageFrameExt->value.choice.PAMData), &(pstruWjMessageFrameExt->choice.struPAMData));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PAMData_MsgDec is err");
            return false;
        }
        break;
    case value_PR_CLPMM:
        pstruWjMessageFrameExt->enumpresent = WJV2_value_PR_CLPMM;
        n32Ret = WJV2_CLPMMData_MsgDec(&(pstruAsnMessageFrameExt->value.choice.CLPMM), &(pstruWjMessageFrameExt->choice.struCLPMM));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_CLPMMData_MsgDec is err");
            return false;
        }
        break;
    case value_PR_PersonalSafetyMessage:
        pstruWjMessageFrameExt->enumpresent = WJV2_value_PR_PersonalSafetyMessage;
        n32Ret = WJV2_PSMData_MsgDec(&(pstruAsnMessageFrameExt->value.choice.PersonalSafetyMessage), &(pstruWjMessageFrameExt->choice.struPersonalSafetyMessage));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PSMData_MsgDec is err");
            return false;
        }
        break;
    case value_PR_RoadsideCoordination:
        pstruWjMessageFrameExt->enumpresent = WJV2_value_PR_RoadsideCoordination;
        n32Ret = WJV2_RSCData_MsgDec(&(pstruAsnMessageFrameExt->value.choice.RoadsideCoordination), &(pstruWjMessageFrameExt->choice.struRoadsideCoordination));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RSCData_MsgDec is err");
            return false;
        }
        break;
    case value_PR_SensorSharingMsg:
        pstruWjMessageFrameExt->enumpresent = WJV2_value_PR_SensorSharingMsg;
        n32Ret = WJV2_SSMData_MsgDec(&(pstruAsnMessageFrameExt->value.choice.SensorSharingMsg), &(pstruWjMessageFrameExt->choice.struSensorSharingMsg));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_SSMData_MsgDec is err");
            return false;
        }
        break;
    case value_PR_VehIntentionAndRequest:
        pstruWjMessageFrameExt->enumpresent = WJV2_value_PR_VehIntentionAndRequest;
        n32Ret = WJV2_VIRData_MsgDec(&(pstruAsnMessageFrameExt->value.choice.VehIntentionAndRequest), &(pstruWjMessageFrameExt->choice.struVehIntentionAndRequest));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_VIRData_MsgDec is err");
            return false;
        }
        break;
    case value_PR_VehiclePaymentMessage:
        pstruWjMessageFrameExt->enumpresent = WJV2_value_PR_VehiclePaymentMessage;
        n32Ret = WJV2_VPMData_MsgDec(&(pstruAsnMessageFrameExt->value.choice.VehiclePaymentMessage), &(pstruWjMessageFrameExt->choice.struVehiclePaymentMessage));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_VPMData_MsgDec is err");
            return false;
        }
        break;
    default:
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnMessageFrameExt->value.present = %d",
                 pstruAsnMessageFrameExt->value.present);
        return false;
    }
    return true;
}
/**
* @brief     WJV2_BasicSafetyMessage_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_BasicSafetyMessage_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_BasicSafetyMessage *pstruWjBasicSafetyMessage = (WJV2_STRU_BasicSafetyMessage *)pvoidWjMsg;
    BasicSafetyMessage_t *pstruAsnBasicSafetyMessage = (BasicSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjBasicSafetyMessage->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjBasicSafetyMessage->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjBasicSafetyMessage->n32msgCnt = %d",
                 pstruWjBasicSafetyMessage->n32msgCnt);
        return false;
    }
    pstruAsnBasicSafetyMessage->msgCnt = pstruWjBasicSafetyMessage->n32msgCnt;
    pstruAsnBasicSafetyMessage->id.size = WJV2_MAX_ID_SIZE;
    pstruAsnBasicSafetyMessage->id.buf = CALLOC(pstruAsnBasicSafetyMessage->id.size, sizeof(uint8_t));
    if (NULL == pstruAsnBasicSafetyMessage->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnBasicSafetyMessage->id.buf, pstruWjBasicSafetyMessage->u8OCTid, pstruAsnBasicSafetyMessage->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruWjBasicSafetyMessage->n32secMark) || (WJV2_MIN_DSECOND_SIZE > pstruWjBasicSafetyMessage->n32secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjBasicSafetyMessage->n32secMark = %d",
                 pstruWjBasicSafetyMessage->n32secMark);
        return false;
    }
    pstruAsnBasicSafetyMessage->secMark = pstruWjBasicSafetyMessage->n32secMark;
    if (WJV2_PRESENT == pstruWjBasicSafetyMessage->u8timeConfidencePresent)
    {
        pstruAsnBasicSafetyMessage->timeConfidence = CALLOC(1, sizeof(TimeConfidence_t));
        if (NULL == pstruAsnBasicSafetyMessage->timeConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnBasicSafetyMessage->timeConfidence) = pstruWjBasicSafetyMessage->enumtimeConfidence;
    }
    else
    {
        pstruAsnBasicSafetyMessage->timeConfidence = NULL;
    }
    n32Ret = WJV2_Position3D_DfEnc(&(pstruAsnBasicSafetyMessage->pos),
                                   &(pstruWjBasicSafetyMessage->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfEnc is err");
        return false;
    }
    if (WJV2_PRESENT == pstruWjBasicSafetyMessage->u8posAccuracyPresent)
    {
        pstruAsnBasicSafetyMessage->posAccuracy = CALLOC(1, sizeof(struct PositionalAccuracy));
        if (NULL == pstruAsnBasicSafetyMessage->posAccuracy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_PositionalAccuracy_DfEnc(pstruAsnBasicSafetyMessage->posAccuracy, &(pstruWjBasicSafetyMessage->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PositionalAccuracy_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBasicSafetyMessage->posAccuracy = NULL;
    }
    if (WJV2_PRESENT == pstruWjBasicSafetyMessage->u8posConfidencePresent)
    {
        pstruAsnBasicSafetyMessage->posConfidence = CALLOC(1, sizeof(struct PositionConfidenceSet));
        if (NULL == pstruAsnBasicSafetyMessage->posConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_PositionConfidenceSet_DfEnc(pstruAsnBasicSafetyMessage->posConfidence, &(pstruWjBasicSafetyMessage->struposConfidence));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PositionConfidenceSet_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBasicSafetyMessage->posConfidence = NULL;
    }
    pstruAsnBasicSafetyMessage->transmission = pstruWjBasicSafetyMessage->enumtransmission;
    if ((WJV2_MAX_SPEED_SIZE < pstruWjBasicSafetyMessage->n32speed) || (WJV2_MIN_SPEED_SIZE > pstruWjBasicSafetyMessage->n32speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjBasicSafetyMessage->n32speed = %d",
                 pstruWjBasicSafetyMessage->n32speed);
        return false;
    }
    pstruAsnBasicSafetyMessage->speed = pstruWjBasicSafetyMessage->n32speed;
    if ((WJV2_MAX_HEADING_SIZE < pstruWjBasicSafetyMessage->n32heading) || (WJV2_MIN_HEADING_SIZE > pstruWjBasicSafetyMessage->n32heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjBasicSafetyMessage->n32heading = %d",
                 pstruWjBasicSafetyMessage->n32heading);
        return false;
    }
    pstruAsnBasicSafetyMessage->heading = pstruWjBasicSafetyMessage->n32heading;
    if (WJV2_PRESENT == pstruWjBasicSafetyMessage->u8anglePresent)
    {
        pstruAsnBasicSafetyMessage->angle = CALLOC(1, sizeof(SteeringWheelAngle_t));
        if (NULL == pstruAsnBasicSafetyMessage->angle)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        if ((WJV2_MAX_STEERINGWHEELANGLE_SIZE < pstruWjBasicSafetyMessage->n32angle) || (WJV2_MIN_STEERINGWHEELANGLE_SIZE > pstruWjBasicSafetyMessage->n32angle))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:pstruWjBasicSafetyMessage->n32angle = %d",
                     pstruWjBasicSafetyMessage->n32angle);
            return false;
        }
        *(pstruAsnBasicSafetyMessage->angle) = pstruWjBasicSafetyMessage->n32angle;
    }
    else
    {
        pstruAsnBasicSafetyMessage->angle = NULL;
    }
    if (WJV2_PRESENT == pstruWjBasicSafetyMessage->u8MotionConfidenceSetPresent)
    {
        pstruAsnBasicSafetyMessage->motionCfd = CALLOC(1, sizeof(struct MotionConfidenceSet));
        if (NULL == pstruAsnBasicSafetyMessage->motionCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_MotionConfidenceSet_DfEnc(pstruAsnBasicSafetyMessage->motionCfd, &(pstruWjBasicSafetyMessage->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_MotionConfidenceSet_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBasicSafetyMessage->motionCfd = NULL;
    }
    n32Ret = WJV2_AccelerationSet4Way_DfEnc(&(pstruAsnBasicSafetyMessage->accelSet), &(pstruWjBasicSafetyMessage->struaccelSet));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_AccelerationSet4Way_DfEnc is err");
        return false;
    }
    n32Ret = WJV2_BrakeSystemStatus_DfEnc(&(pstruAsnBasicSafetyMessage->brakes), &(pstruWjBasicSafetyMessage->strubrakes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BrakeSystemStatus_DfEnc is err");
        return false;
    }
    n32Ret = WJV2_VehicleSize_DfEnc(&(pstruAsnBasicSafetyMessage->size), &(pstruWjBasicSafetyMessage->strusize));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_VehicleSize_DfEnc is err");
        return false;
    }
    n32Ret = WJV2_VehicleClassification_DfEnc(&(pstruAsnBasicSafetyMessage->vehicleClass), &(pstruWjBasicSafetyMessage->struvehicleClass));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_VehicleClassification_DfEnc is err");
        return false;
    }
    if (WJV2_PRESENT == pstruWjBasicSafetyMessage->u8safetyExtPresent)
    {
        pstruAsnBasicSafetyMessage->safetyExt = CALLOC(1, sizeof(struct VehicleSafetyExtensions));
        if (NULL == pstruAsnBasicSafetyMessage->safetyExt)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_VehicleSafetyExtensions_DfEnc(pstruAsnBasicSafetyMessage->safetyExt, &(pstruWjBasicSafetyMessage->strusafetyExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_VehicleSafetyExtensions_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBasicSafetyMessage->safetyExt = NULL;
    }
    if (WJV2_PRESENT == pstruWjBasicSafetyMessage->u8emergencyExtPresent)
    {
        pstruAsnBasicSafetyMessage->emergencyExt = CALLOC(1, sizeof(struct VehicleEmergencyExtensions));
        if (NULL == pstruAsnBasicSafetyMessage->emergencyExt)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_VehicleEmergencyExtensions_DfEnc(pstruAsnBasicSafetyMessage->emergencyExt, &(pstruWjBasicSafetyMessage->struemergencyExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_VehicleEmergencyExtensions_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBasicSafetyMessage->emergencyExt = NULL;
    }
    return true;
}
/**
* @brief     WJV2_BasicSafetyMessage_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_BasicSafetyMessage_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_BasicSafetyMessage *pstruWjBasicSafetyMessage = (WJV2_STRU_BasicSafetyMessage *)pvoidWjMsg;
    BasicSafetyMessage_t *pstruAsnBasicSafetyMessage = (BasicSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnBasicSafetyMessage->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnBasicSafetyMessage->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnBasicSafetyMessage->msgCnt = %d",
                 pstruAsnBasicSafetyMessage->msgCnt);
        return false;
    }
    pstruWjBasicSafetyMessage->n32msgCnt = pstruAsnBasicSafetyMessage->msgCnt;
    memcpy(pstruWjBasicSafetyMessage->u8OCTid, pstruAsnBasicSafetyMessage->id.buf, pstruAsnBasicSafetyMessage->id.size);
    if ((WJV2_MAX_DSECOND_SIZE < pstruAsnBasicSafetyMessage->secMark) || (WJV2_MIN_DSECOND_SIZE > pstruAsnBasicSafetyMessage->secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnBasicSafetyMessage->secMark = %d",
                 pstruAsnBasicSafetyMessage->secMark);
        return false;
    }
    pstruWjBasicSafetyMessage->n32secMark = pstruAsnBasicSafetyMessage->secMark;
    if (NULL != pstruAsnBasicSafetyMessage->timeConfidence)
    {
        pstruWjBasicSafetyMessage->enumtimeConfidence = *(pstruAsnBasicSafetyMessage->timeConfidence);
        pstruWjBasicSafetyMessage->u8timeConfidencePresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8timeConfidencePresent = WJV2_ABSENT;
    }
    n32Ret = WJV2_Position3D_DfDec(&(pstruAsnBasicSafetyMessage->pos),
                                   &(pstruWjBasicSafetyMessage->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnBasicSafetyMessage->posAccuracy)
    {
        n32Ret = WJV2_PositionalAccuracy_DfDec(pstruAsnBasicSafetyMessage->posAccuracy, &(pstruWjBasicSafetyMessage->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PositionalAccuracy_DfDec is err");
            return false;
        }
        pstruWjBasicSafetyMessage->u8posAccuracyPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8posAccuracyPresent = WJV2_ABSENT;
    }
    if (NULL != pstruAsnBasicSafetyMessage->posConfidence)
    {
        n32Ret = WJV2_PositionConfidenceSet_DfDec(pstruAsnBasicSafetyMessage->posConfidence, &(pstruWjBasicSafetyMessage->struposConfidence));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_PositionConfidenceSet_DfDec is err");
            return false;
        }
        pstruWjBasicSafetyMessage->u8posConfidencePresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8posConfidencePresent = WJV2_ABSENT;
    }
    pstruWjBasicSafetyMessage->enumtransmission = pstruAsnBasicSafetyMessage->transmission;
    if ((WJV2_MAX_SPEED_SIZE < pstruAsnBasicSafetyMessage->speed) || (WJV2_MIN_SPEED_SIZE > pstruAsnBasicSafetyMessage->speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnBasicSafetyMessage->speed = %d",
                 pstruAsnBasicSafetyMessage->speed);
        return false;
    }
    pstruWjBasicSafetyMessage->n32speed = pstruAsnBasicSafetyMessage->speed;
    if ((WJV2_MAX_HEADING_SIZE < pstruAsnBasicSafetyMessage->heading) || (WJV2_MIN_HEADING_SIZE > pstruAsnBasicSafetyMessage->heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnBasicSafetyMessage->heading = %d",
                 pstruAsnBasicSafetyMessage->heading);
        return false;
    }
    pstruWjBasicSafetyMessage->n32heading = pstruAsnBasicSafetyMessage->heading;
    if (NULL != pstruAsnBasicSafetyMessage->angle)
    {
        if ((WJV2_MAX_STEERINGWHEELANGLE_SIZE < *(pstruAsnBasicSafetyMessage->angle)) || (WJV2_MIN_STEERINGWHEELANGLE_SIZE > *(pstruAsnBasicSafetyMessage->angle)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:*(pstruAsnBasicSafetyMessage->angle) = %d",
                     *(pstruAsnBasicSafetyMessage->angle));
            return false;
        }
        pstruWjBasicSafetyMessage->n32angle = *(pstruAsnBasicSafetyMessage->angle);
        pstruWjBasicSafetyMessage->u8anglePresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8anglePresent = WJV2_ABSENT;
    }
    if (NULL != pstruAsnBasicSafetyMessage->motionCfd)
    {
        n32Ret = WJV2_MotionConfidenceSet_DfDec(pstruAsnBasicSafetyMessage->motionCfd, &(pstruWjBasicSafetyMessage->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_MotionConfidenceSet_DfDec is err");
            return false;
        }
        pstruWjBasicSafetyMessage->u8MotionConfidenceSetPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8MotionConfidenceSetPresent = WJV2_ABSENT;
    }
    n32Ret = WJV2_AccelerationSet4Way_DfDec(&(pstruAsnBasicSafetyMessage->accelSet), &(pstruWjBasicSafetyMessage->struaccelSet));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_AccelerationSet4Way_DfDec is err");
        return false;
    }
    n32Ret = WJV2_BrakeSystemStatus_DfDec(&(pstruAsnBasicSafetyMessage->brakes), &(pstruWjBasicSafetyMessage->strubrakes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BrakeSystemStatus_DfDec is err");
        return false;
    }
    n32Ret = WJV2_VehicleSize_DfDec(&(pstruAsnBasicSafetyMessage->size), &(pstruWjBasicSafetyMessage->strusize));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_VehicleSize_DfDec is err");
        return false;
    }
    n32Ret = WJV2_VehicleClassification_DfDec(&(pstruAsnBasicSafetyMessage->vehicleClass), &(pstruWjBasicSafetyMessage->struvehicleClass));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_VehicleClassification_DfDec is err");
        return false;
    }

    if (NULL != pstruAsnBasicSafetyMessage->safetyExt)
    {
        n32Ret = WJV2_VehicleSafetyExtensions_DfDec(pstruAsnBasicSafetyMessage->safetyExt, &(pstruWjBasicSafetyMessage->strusafetyExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_VehicleSafetyExtensions_DfDec is err");
            return false;
        }
        pstruWjBasicSafetyMessage->u8safetyExtPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8safetyExtPresent = WJV2_ABSENT;
    }

    if (NULL != pstruAsnBasicSafetyMessage->emergencyExt)
    {
        n32Ret = WJV2_VehicleEmergencyExtensions_DfDec(pstruAsnBasicSafetyMessage->emergencyExt, &(pstruWjBasicSafetyMessage->struemergencyExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_VehicleEmergencyExtensions_DfDec is err");
            return false;
        }
        pstruWjBasicSafetyMessage->u8emergencyExtPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8emergencyExtPresent = WJV2_ABSENT;
    }
    return true;
}
/**
* @brief     WJV2_MapData_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_MapData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_MapData *pstruWjMapData = (WJV2_STRU_MapData *)pvoidWjMsg;
    MapData_t *pstruAsnMapData = (MapData_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjMapData->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjMapData->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjMapData->n32msgCnt = %d",
                 pstruWjMapData->n32msgCnt);
        return false;
    }
    pstruAsnMapData->msgCnt = pstruWjMapData->n32msgCnt;
    if (WJV2_PRESENT == pstruWjMapData->u8timeStampPresent)
    {
        pstruAsnMapData->timeStamp = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnMapData->timeStamp)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        if ((WJV2_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjMapData->n32timeStamp) || (WJV2_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjMapData->n32timeStamp))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:pstruWjMapData->n32timeStamp = %d",
                     pstruWjMapData->n32timeStamp);
            return false;
        }
        *(pstruAsnMapData->timeStamp) = pstruWjMapData->n32timeStamp;
    }
    else
    {
        pstruAsnMapData->timeStamp = NULL;
    }
    n32Ret = WJV2_NodeList_DfEnc(&(pstruAsnMapData->nodes), &(pstruWjMapData->strunodes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_NodeList_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_MapData_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_MapData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_MapData *pstruWjMapData = (WJV2_STRU_MapData *)pvoidWjMsg;
    MapData_t *pstruAsnMapData = (MapData_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnMapData->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnMapData->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnMapData->msgCnt = %d",
                 pstruAsnMapData->msgCnt);
        return false;
    }
    pstruWjMapData->n32msgCnt = pstruAsnMapData->msgCnt;
    if (NULL != pstruAsnMapData->timeStamp)
    {
        if ((WJV2_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnMapData->timeStamp)) || (WJV2_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnMapData->timeStamp)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:*(pstruAsnMapData->timeStamp) = %d",
                     *(pstruAsnMapData->timeStamp));
            return false;
        }
        pstruWjMapData->n32timeStamp = *(pstruAsnMapData->timeStamp);
        pstruWjMapData->u8timeStampPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjMapData->u8timeStampPresent = WJV2_ABSENT;
    }
    n32Ret = WJV2_NodeList_DfDec(&(pstruAsnMapData->nodes), &(pstruWjMapData->strunodes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_NodeList_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_PamData_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_RoadSideInformation_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_RoadSideInformation *pstruWjRoadSideInformation = (WJV2_STRU_RoadSideInformation *)pvoidWjMsg;
    RoadSideInformation_t *pstruAsnRoadSideInformation = (RoadSideInformation_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjRoadSideInformation->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjRoadSideInformation->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjRoadSideInformation->n32msgCnt = %d",
                 pstruWjRoadSideInformation->n32msgCnt);
        return false;
    }
    pstruAsnRoadSideInformation->msgCnt = pstruWjRoadSideInformation->n32msgCnt;
    if (WJV2_PRESENT == pstruWjRoadSideInformation->u8moyPresent)
    {
        pstruAsnRoadSideInformation->moy = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnRoadSideInformation->moy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        if ((WJV2_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjRoadSideInformation->n32moy) || (WJV2_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjRoadSideInformation->n32moy))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:pstruWjRoadSideInformation->n32moy = %d",
                     pstruWjRoadSideInformation->n32moy);
            return false;
        }
        *(pstruAsnRoadSideInformation->moy) = pstruWjRoadSideInformation->n32moy;
    }
    else
    {
        pstruAsnRoadSideInformation->moy = NULL;
    }
    pstruAsnRoadSideInformation->id.size = WJV2_MAX_ID_SIZE;
    pstruAsnRoadSideInformation->id.buf = CALLOC(pstruAsnRoadSideInformation->id.size, sizeof(uint8_t));
    if (NULL == pstruAsnRoadSideInformation->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnRoadSideInformation->id.buf, pstruWjRoadSideInformation->u8OCTid, pstruAsnRoadSideInformation->id.size);
    n32Ret = WJV2_Position3D_DfEnc(&(pstruAsnRoadSideInformation->refPos),
                                   &(pstruWjRoadSideInformation->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfEnc is err");
        return false;
    }
    if (WJV2_PRESENT == pstruWjRoadSideInformation->u8rtesPresent)
    {
        pstruAsnRoadSideInformation->rtes = CALLOC(1, sizeof(struct RTEList));
        if (NULL == pstruAsnRoadSideInformation->rtes)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_RTEList_DfEnc(pstruAsnRoadSideInformation->rtes, &(pstruWjRoadSideInformation->strurtes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RTEList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRoadSideInformation->rtes = NULL;
    }
    if (WJV2_PRESENT == pstruWjRoadSideInformation->u8rtssPresent)
    {
        pstruAsnRoadSideInformation->rtss = CALLOC(1, sizeof(struct RTSList));
        if (NULL == pstruAsnRoadSideInformation->rtss)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_RTSList_DfEnc(pstruAsnRoadSideInformation->rtss, &(pstruWjRoadSideInformation->strurtss));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RTSList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRoadSideInformation->rtss = NULL;
    }
    return true;
}
/**
* @brief     WJV2_RoadSideInformation_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_RoadSideInformation_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_RoadSideInformation *pstruWjRoadSideInformation = (WJV2_STRU_RoadSideInformation *)pvoidWjMsg;
    RoadSideInformation_t *pstruAsnRoadSideInformation = (RoadSideInformation_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnRoadSideInformation->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnRoadSideInformation->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnRoadSideInformation->msgCnt = %d",
                 pstruAsnRoadSideInformation->msgCnt);
        return false;
    }
    pstruWjRoadSideInformation->n32msgCnt = pstruAsnRoadSideInformation->msgCnt;
    if (NULL != pstruAsnRoadSideInformation->moy)
    {
        if ((WJV2_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnRoadSideInformation->moy)) || (WJV2_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnRoadSideInformation->moy)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:*(pstruAsnRoadSideInformation->moy) = %d",
                     *(pstruAsnRoadSideInformation->moy));
            return false;
        }
        pstruWjRoadSideInformation->n32moy = *(pstruAsnRoadSideInformation->moy);
        pstruWjRoadSideInformation->u8moyPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjRoadSideInformation->u8moyPresent = WJV2_ABSENT;
    }
    memcpy(pstruWjRoadSideInformation->u8OCTid, pstruAsnRoadSideInformation->id.buf, pstruAsnRoadSideInformation->id.size);
    n32Ret = WJV2_Position3D_DfDec(&(pstruAsnRoadSideInformation->refPos),
                                   &(pstruWjRoadSideInformation->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnRoadSideInformation->rtes)
    {
        n32Ret = WJV2_RTEList_DfDec(pstruAsnRoadSideInformation->rtes, &(pstruWjRoadSideInformation->strurtes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RTEList_DfDec is err");
            return false;
        }
        pstruWjRoadSideInformation->u8rtesPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjRoadSideInformation->u8rtesPresent = WJV2_ABSENT;
    }
    if (NULL != pstruAsnRoadSideInformation->rtss)
    {
        n32Ret = WJV2_RTSList_DfDec(pstruAsnRoadSideInformation->rtss, &(pstruWjRoadSideInformation->strurtss));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_RTSList_DfDec is err");
            return false;
        }
        pstruWjRoadSideInformation->u8rtssPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjRoadSideInformation->u8rtssPresent = WJV2_ABSENT;
    }
    return true;
}
/**
* @brief     WJV2_RoadsideSafetyMessage_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_RoadsideSafetyMessage_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_RoadsideSafetyMessage *pstruWjRoadsideSafetyMessage = (WJV2_STRU_RoadsideSafetyMessage *)pvoidWjMsg;
    RoadsideSafetyMessage_t *pstruAsnRoadsideSafetyMessage = (RoadsideSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjRoadsideSafetyMessage->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjRoadsideSafetyMessage->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjRoadsideSafetyMessage->n32msgCnt = %d",
                 pstruWjRoadsideSafetyMessage->n32msgCnt);
        return false;
    }
    pstruAsnRoadsideSafetyMessage->msgCnt = pstruWjRoadsideSafetyMessage->n32msgCnt;
    pstruAsnRoadsideSafetyMessage->id.size = WJV2_MAX_ID_SIZE;
    pstruAsnRoadsideSafetyMessage->id.buf = CALLOC(pstruAsnRoadsideSafetyMessage->id.size, sizeof(uint8_t));
    if (NULL == pstruAsnRoadsideSafetyMessage->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnRoadsideSafetyMessage->id.buf, pstruWjRoadsideSafetyMessage->u8OCTid, pstruAsnRoadsideSafetyMessage->id.size);
    n32Ret = WJV2_Position3D_DfEnc(&(pstruAsnRoadsideSafetyMessage->refPos),
                                   &(pstruWjRoadsideSafetyMessage->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfEnc is err");
        return false;
    }
    n32Ret = WJV2_ParticipantList_DfEnc(&(pstruAsnRoadsideSafetyMessage->participants),
                                        &(pstruWjRoadsideSafetyMessage->struparticipants));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_ParticipantList_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_RoadsideSafetyMessage_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_RoadsideSafetyMessage_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_RoadsideSafetyMessage *pstruWjRoadsideSafetyMessage = (WJV2_STRU_RoadsideSafetyMessage *)pvoidWjMsg;
    RoadsideSafetyMessage_t *pstruAsnRoadsideSafetyMessage = (RoadsideSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnRoadsideSafetyMessage->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnRoadsideSafetyMessage->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnRoadsideSafetyMessage->msgCnt = %d",
                 pstruAsnRoadsideSafetyMessage->msgCnt);
        return false;
    }
    pstruWjRoadsideSafetyMessage->n32msgCnt = pstruAsnRoadsideSafetyMessage->msgCnt;
    memcpy(pstruWjRoadsideSafetyMessage->u8OCTid, pstruAsnRoadsideSafetyMessage->id.buf, pstruAsnRoadsideSafetyMessage->id.size);
    n32Ret = WJV2_Position3D_DfDec(&(pstruAsnRoadsideSafetyMessage->refPos),
                                   &(pstruWjRoadsideSafetyMessage->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_Position3D_DfDec is err");
        return false;
    }
    n32Ret = WJV2_ParticipantList_DfDec(&(pstruAsnRoadsideSafetyMessage->participants),
                                        &(pstruWjRoadsideSafetyMessage->struparticipants));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_ParticipantList_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_SPAT_MsgEnc编码函数
* @details   协议栈Msg编解码中 统一Msg的编码函数入口
* @param   [in]   void * pvoidAsnMsg  编码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_SPAT_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_SPAT *pstruWjSPAT = (WJV2_STRU_SPAT *)pvoidWjMsg;
    SPAT_t *pstruAsnSPAT = (SPAT_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruWjSPAT->n32msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruWjSPAT->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjSPAT->n32msgCnt = %d",
                 pstruWjSPAT->n32msgCnt);
        return false;
    }
    pstruAsnSPAT->msgCnt = pstruWjSPAT->n32msgCnt;
    if (WJV2_PRESENT == pstruWjSPAT->u8moyPresent)
    {
        pstruAsnSPAT->moy = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnSPAT->moy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        if ((WJV2_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjSPAT->n32moy) || (WJV2_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjSPAT->n32moy))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:pstruWjSPAT->n32moy = %d",
                     pstruWjSPAT->n32moy);
            return false;
        }
        *(pstruAsnSPAT->moy) = pstruWjSPAT->n32moy;
    }
    else
    {
        pstruAsnSPAT->moy = NULL;
    }
    if (WJV2_PRESENT == pstruWjSPAT->u8timeStampPresent)
    {
        pstruAsnSPAT->timeStamp = CALLOC(1, sizeof(DSecond_t));
        if (NULL == pstruAsnSPAT->timeStamp)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        if ((WJV2_MAX_DSECOND_SIZE < pstruWjSPAT->n32timeStamp) || (WJV2_MIN_DSECOND_SIZE > pstruWjSPAT->n32timeStamp))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:pstruWjSPAT->n32timeStamp = %d",
                     pstruWjSPAT->n32timeStamp);
            return false;
        }
        *(pstruAsnSPAT->timeStamp) = pstruWjSPAT->n32timeStamp;
    }
    else
    {
        pstruAsnSPAT->timeStamp = NULL;
    }
    if (WJV2_PRESENT == pstruWjSPAT->u8namePresent)
    {
        pstruAsnSPAT->name = CALLOC(1, sizeof(DescriptiveName_t));
        if (NULL == pstruAsnSPAT->name)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV2_DescriptiveName_DeEnc(pstruAsnSPAT->name, &(pstruWjSPAT->stria5name));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_DescriptiveName_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnSPAT->name = NULL;
    }
    n32Ret = WJV2_IntersectionStateList_DfEnc(&(pstruAsnSPAT->intersections), &(pstruWjSPAT->struintersections));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_IntersectionStateList_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_SPAT_MsgDec解码函数
* @details   协议栈Msg编解码中 统一Msg的解码函数入口
* @param   [in]   void * pvoidAsnMsg  解码结构
* @param   [in]   void * pvoidWjMsg   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV2_SPAT_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV2_STRU_SPAT *pstruWjSPAT = (WJV2_STRU_SPAT *)pvoidWjMsg;
    SPAT_t *pstruAsnSPAT = (SPAT_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    if ((WJV2_MAX_MSGCOUNT_SIZE < pstruAsnSPAT->msgCnt) || (WJV2_MIN_MSGCOUNT_SIZE > pstruAsnSPAT->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnSPAT->msgCnt = %d",
                 pstruAsnSPAT->msgCnt);
        return false;
    }
    pstruWjSPAT->n32msgCnt = pstruAsnSPAT->msgCnt;
    if (NULL != pstruAsnSPAT->moy)
    {
        if ((WJV2_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnSPAT->moy)) || (WJV2_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnSPAT->moy)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:*(pstruAsnSPAT->moy) = %d",
                     *(pstruAsnSPAT->moy));
            return false;
        }
        pstruWjSPAT->n32moy = *(pstruAsnSPAT->moy);
        pstruWjSPAT->u8moyPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjSPAT->u8moyPresent = WJV2_ABSENT;
    }
    if (NULL != pstruAsnSPAT->timeStamp)
    {
        if ((WJV2_MAX_DSECOND_SIZE < *(pstruAsnSPAT->timeStamp)) || (WJV2_MIN_DSECOND_SIZE > *(pstruAsnSPAT->timeStamp)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:*(pstruAsnSPAT->timeStamp) = %d",
                     *(pstruAsnSPAT->timeStamp));
            return false;
        }
        pstruWjSPAT->n32timeStamp = *(pstruAsnSPAT->timeStamp);
        pstruWjSPAT->u8timeStampPresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjSPAT->u8timeStampPresent = WJV2_ABSENT;
    }
    if (NULL != pstruAsnSPAT->name)
    {
        n32Ret = WJV2_DescriptiveName_DeDec(pstruAsnSPAT->name, &(pstruWjSPAT->stria5name));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV2_DescriptiveName_DeDec is err");
            return false;
        }
        pstruWjSPAT->u8namePresent = WJV2_PRESENT;
    }
    else
    {
        pstruWjSPAT->u8namePresent = WJV2_ABSENT;
    }
    n32Ret = WJV2_IntersectionStateList_DfDec(&(pstruAsnSPAT->intersections), &(pstruWjSPAT->struintersections));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_IntersectionStateList_DfDec is err");
        return false;
    }
    return true;
}
/* 文件结束 */