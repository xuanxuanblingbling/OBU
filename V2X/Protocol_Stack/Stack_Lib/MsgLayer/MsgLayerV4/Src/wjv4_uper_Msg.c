/**
* @file         :wjv4_uper_Msg.c.c
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
#include "wjv4_uper_Msg.h"
#include "wjv4_uper_com.h"
/**
* @brief     WJV4_BasicSafetyMessage_MsgEnc编码函数
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
int32_t WJV4_BasicSafetyMessage_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV4_STRU_BasicSafetyMessage *pstruWjBasicSafetyMessage = (WJV4_STRU_BasicSafetyMessage *)pvoidWjMsg;
    BasicSafetyMessage_t *pstruAsnBasicSafetyMessage = (BasicSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_MSGCOUNT_SIZE < pstruWjBasicSafetyMessage->n32msgCnt) || (WJV4_MIN_MSGCOUNT_SIZE > pstruWjBasicSafetyMessage->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjBasicSafetyMessage->n32msgCnt = %d",
                 pstruWjBasicSafetyMessage->n32msgCnt);
        return false;
    }
#endif
    pstruAsnBasicSafetyMessage->msgCnt = pstruWjBasicSafetyMessage->n32msgCnt;
    pstruAsnBasicSafetyMessage->id.size = WJV4_MAX_ID_SIZE;
    pstruAsnBasicSafetyMessage->id.buf = CALLOC(pstruAsnBasicSafetyMessage->id.size, sizeof(uint8_t));
    if (NULL == pstruAsnBasicSafetyMessage->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnBasicSafetyMessage->id.buf, pstruWjBasicSafetyMessage->u8OCTid, pstruAsnBasicSafetyMessage->id.size);
#ifdef _CHECK_
    if ((WJV4_MAX_DSECOND_SIZE < pstruWjBasicSafetyMessage->n32secMark) || (WJV4_MIN_DSECOND_SIZE > pstruWjBasicSafetyMessage->n32secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjBasicSafetyMessage->n32secMark = %d",
                 pstruWjBasicSafetyMessage->n32secMark);
        return false;
    }
#endif
    pstruAsnBasicSafetyMessage->secMark = pstruWjBasicSafetyMessage->n32secMark;
    if (WJV4_PRESENT == pstruWjBasicSafetyMessage->u8timeConfidencePresent)
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
    n32Ret = WJV4_Position3D_DfEnc(&(pstruAsnBasicSafetyMessage->pos),
                                   &(pstruWjBasicSafetyMessage->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_Position3D_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjBasicSafetyMessage->u8posAccuracyPresent)
    {
        pstruAsnBasicSafetyMessage->posAccuracy = CALLOC(1, sizeof(struct PositionalAccuracy));
        if (NULL == pstruAsnBasicSafetyMessage->posAccuracy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_PositionalAccuracy_DfEnc(pstruAsnBasicSafetyMessage->posAccuracy, &(pstruWjBasicSafetyMessage->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_PositionalAccuracy_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBasicSafetyMessage->posAccuracy = NULL;
    }
    if (WJV4_PRESENT == pstruWjBasicSafetyMessage->u8posConfidencePresent)
    {
        pstruAsnBasicSafetyMessage->posConfidence = CALLOC(1, sizeof(struct PositionConfidenceSet));
        if (NULL == pstruAsnBasicSafetyMessage->posConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_PositionConfidenceSet_DfEnc(pstruAsnBasicSafetyMessage->posConfidence, &(pstruWjBasicSafetyMessage->struposConfidence));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_PositionConfidenceSet_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBasicSafetyMessage->posConfidence = NULL;
    }
    pstruAsnBasicSafetyMessage->transmission = pstruWjBasicSafetyMessage->enumtransmission;
#ifdef _CHECK_
    if ((WJV4_MAX_SPEED_SIZE < pstruWjBasicSafetyMessage->n32speed) || (WJV4_MIN_SPEED_SIZE > pstruWjBasicSafetyMessage->n32speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjBasicSafetyMessage->n32speed = %d",
                 pstruWjBasicSafetyMessage->n32speed);
        return false;
    }
#endif
    pstruAsnBasicSafetyMessage->speed = pstruWjBasicSafetyMessage->n32speed;
#ifdef _CHECK_
    if ((WJV4_MAX_HEADING_SIZE < pstruWjBasicSafetyMessage->n32heading) || (WJV4_MIN_HEADING_SIZE > pstruWjBasicSafetyMessage->n32heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjBasicSafetyMessage->n32heading = %d",
                 pstruWjBasicSafetyMessage->n32heading);
        return false;
    }
#endif
    pstruAsnBasicSafetyMessage->heading = pstruWjBasicSafetyMessage->n32heading;
    if (WJV4_PRESENT == pstruWjBasicSafetyMessage->u8anglePresent)
    {
        pstruAsnBasicSafetyMessage->angle = CALLOC(1, sizeof(SteeringWheelAngle_t));
        if (NULL == pstruAsnBasicSafetyMessage->angle)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_STEERINGWHEELANGLE_SIZE < pstruWjBasicSafetyMessage->n32angle) || (WJV4_MIN_STEERINGWHEELANGLE_SIZE > pstruWjBasicSafetyMessage->n32angle))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:pstruWjBasicSafetyMessage->n32angle = %d",
                     pstruWjBasicSafetyMessage->n32angle);
            return false;
        }
#endif
        *(pstruAsnBasicSafetyMessage->angle) = pstruWjBasicSafetyMessage->n32angle;
    }
    else
    {
        pstruAsnBasicSafetyMessage->angle = NULL;
    }
    if (WJV4_PRESENT == pstruWjBasicSafetyMessage->u8MotionConfidenceSetPresent)
    {
        pstruAsnBasicSafetyMessage->motionCfd = CALLOC(1, sizeof(struct MotionConfidenceSet));
        if (NULL == pstruAsnBasicSafetyMessage->motionCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_MotionConfidenceSet_DfEnc(pstruAsnBasicSafetyMessage->motionCfd, &(pstruWjBasicSafetyMessage->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_MotionConfidenceSet_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBasicSafetyMessage->motionCfd = NULL;
    }
    n32Ret = WJV4_AccelerationSet4Way_DfEnc(&(pstruAsnBasicSafetyMessage->accelSet), &(pstruWjBasicSafetyMessage->struaccelSet));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_AccelerationSet4Way_DfEnc is err");
        return false;
    }
    n32Ret = WJV4_BrakeSystemStatus_DfEnc(&(pstruAsnBasicSafetyMessage->brakes), &(pstruWjBasicSafetyMessage->strubrakes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BrakeSystemStatus_DfEnc is err");
        return false;
    }
    n32Ret = WJV4_VehicleSize_DfEnc(&(pstruAsnBasicSafetyMessage->size), &(pstruWjBasicSafetyMessage->strusize));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_VehicleSize_DfEnc is err");
        return false;
    }
    n32Ret = WJV4_VehicleClassification_DfEnc(&(pstruAsnBasicSafetyMessage->vehicleClass), &(pstruWjBasicSafetyMessage->struvehicleClass));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_VehicleClassification_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjBasicSafetyMessage->u8safetyExtPresent)
    {
        pstruAsnBasicSafetyMessage->safetyExt = CALLOC(1, sizeof(struct VehicleSafetyExtensions));
        if (NULL == pstruAsnBasicSafetyMessage->safetyExt)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_VehicleSafetyExtensions_DfEnc(pstruAsnBasicSafetyMessage->safetyExt, &(pstruWjBasicSafetyMessage->strusafetyExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_VehicleSafetyExtensions_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBasicSafetyMessage->safetyExt = NULL;
    }
    if (WJV4_PRESENT == pstruWjBasicSafetyMessage->u8emergencyExtPresent)
    {
        pstruAsnBasicSafetyMessage->emergencyExt = CALLOC(1, sizeof(struct VehicleEmergencyExtensions));
        if (NULL == pstruAsnBasicSafetyMessage->emergencyExt)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_VehicleEmergencyExtensions_DfEnc(pstruAsnBasicSafetyMessage->emergencyExt, &(pstruWjBasicSafetyMessage->struemergencyExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_VehicleEmergencyExtensions_DfEnc is err");
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
* @brief     WJV4_BasicSafetyMessage_MsgDec解码函数
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
int32_t WJV4_BasicSafetyMessage_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV4_STRU_BasicSafetyMessage *pstruWjBasicSafetyMessage = (WJV4_STRU_BasicSafetyMessage *)pvoidWjMsg;
    BasicSafetyMessage_t *pstruAsnBasicSafetyMessage = (BasicSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_MSGCOUNT_SIZE < pstruAsnBasicSafetyMessage->msgCnt) || (WJV4_MIN_MSGCOUNT_SIZE > pstruAsnBasicSafetyMessage->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnBasicSafetyMessage->msgCnt = %d",
                 pstruAsnBasicSafetyMessage->msgCnt);
        return false;
    }
#endif
    pstruWjBasicSafetyMessage->n32msgCnt = pstruAsnBasicSafetyMessage->msgCnt;
    memcpy(pstruWjBasicSafetyMessage->u8OCTid, pstruAsnBasicSafetyMessage->id.buf, pstruAsnBasicSafetyMessage->id.size);
#ifdef _CHECK_
    if ((WJV4_MAX_DSECOND_SIZE < pstruAsnBasicSafetyMessage->secMark) || (WJV4_MIN_DSECOND_SIZE > pstruAsnBasicSafetyMessage->secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnBasicSafetyMessage->secMark = %d",
                 pstruAsnBasicSafetyMessage->secMark);
        return false;
    }
#endif
    pstruWjBasicSafetyMessage->n32secMark = pstruAsnBasicSafetyMessage->secMark;
    if (NULL != pstruAsnBasicSafetyMessage->timeConfidence)
    {
        pstruWjBasicSafetyMessage->enumtimeConfidence = *(pstruAsnBasicSafetyMessage->timeConfidence);
        pstruWjBasicSafetyMessage->u8timeConfidencePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8timeConfidencePresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_Position3D_DfDec(&(pstruAsnBasicSafetyMessage->pos),
                                   &(pstruWjBasicSafetyMessage->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_Position3D_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnBasicSafetyMessage->posAccuracy)
    {
        n32Ret = WJV4_PositionalAccuracy_DfDec(pstruAsnBasicSafetyMessage->posAccuracy, &(pstruWjBasicSafetyMessage->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_PositionalAccuracy_DfDec is err");
            return false;
        }
        pstruWjBasicSafetyMessage->u8posAccuracyPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8posAccuracyPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnBasicSafetyMessage->posConfidence)
    {
        n32Ret = WJV4_PositionConfidenceSet_DfDec(pstruAsnBasicSafetyMessage->posConfidence, &(pstruWjBasicSafetyMessage->struposConfidence));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_PositionConfidenceSet_DfDec is err");
            return false;
        }
        pstruWjBasicSafetyMessage->u8posConfidencePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8posConfidencePresent = WJV4_ABSENT;
    }
    pstruWjBasicSafetyMessage->enumtransmission = pstruAsnBasicSafetyMessage->transmission;
#ifdef _CHECK_
    if ((WJV4_MAX_SPEED_SIZE < pstruAsnBasicSafetyMessage->speed) || (WJV4_MIN_SPEED_SIZE > pstruAsnBasicSafetyMessage->speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnBasicSafetyMessage->speed = %d",
                 pstruAsnBasicSafetyMessage->speed);
        return false;
    }
#endif
    pstruWjBasicSafetyMessage->n32speed = pstruAsnBasicSafetyMessage->speed;
#ifdef _CHECK_
    if ((WJV4_MAX_HEADING_SIZE < pstruAsnBasicSafetyMessage->heading) || (WJV4_MIN_HEADING_SIZE > pstruAsnBasicSafetyMessage->heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnBasicSafetyMessage->heading = %d",
                 pstruAsnBasicSafetyMessage->heading);
        return false;
    }
#endif
    pstruWjBasicSafetyMessage->n32heading = pstruAsnBasicSafetyMessage->heading;
    if (NULL != pstruAsnBasicSafetyMessage->angle)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_STEERINGWHEELANGLE_SIZE < *(pstruAsnBasicSafetyMessage->angle)) || (WJV4_MIN_STEERINGWHEELANGLE_SIZE > *(pstruAsnBasicSafetyMessage->angle)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:*(pstruAsnBasicSafetyMessage->angle) = %d",
                     *(pstruAsnBasicSafetyMessage->angle));
            return false;
        }
#endif
        pstruWjBasicSafetyMessage->n32angle = *(pstruAsnBasicSafetyMessage->angle);
        pstruWjBasicSafetyMessage->u8anglePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8anglePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnBasicSafetyMessage->motionCfd)
    {
        n32Ret = WJV4_MotionConfidenceSet_DfDec(pstruAsnBasicSafetyMessage->motionCfd, &(pstruWjBasicSafetyMessage->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_MotionConfidenceSet_DfDec is err");
            return false;
        }
        pstruWjBasicSafetyMessage->u8MotionConfidenceSetPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8MotionConfidenceSetPresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_AccelerationSet4Way_DfDec(&(pstruAsnBasicSafetyMessage->accelSet), &(pstruWjBasicSafetyMessage->struaccelSet));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_AccelerationSet4Way_DfDec is err");
        return false;
    }
    n32Ret = WJV4_BrakeSystemStatus_DfDec(&(pstruAsnBasicSafetyMessage->brakes), &(pstruWjBasicSafetyMessage->strubrakes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BrakeSystemStatus_DfDec is err");
        return false;
    }
    n32Ret = WJV4_VehicleSize_DfDec(&(pstruAsnBasicSafetyMessage->size), &(pstruWjBasicSafetyMessage->strusize));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_VehicleSize_DfDec is err");
        return false;
    }
    n32Ret = WJV4_VehicleClassification_DfDec(&(pstruAsnBasicSafetyMessage->vehicleClass), &(pstruWjBasicSafetyMessage->struvehicleClass));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_VehicleClassification_DfDec is err");
        return false;
    }

    if (NULL != pstruAsnBasicSafetyMessage->safetyExt)
    {
        n32Ret = WJV4_VehicleSafetyExtensions_DfDec(pstruAsnBasicSafetyMessage->safetyExt, &(pstruWjBasicSafetyMessage->strusafetyExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_VehicleSafetyExtensions_DfDec is err");
            return false;
        }
        pstruWjBasicSafetyMessage->u8safetyExtPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8safetyExtPresent = WJV4_ABSENT;
    }

    if (NULL != pstruAsnBasicSafetyMessage->emergencyExt)
    {
        n32Ret = WJV4_VehicleEmergencyExtensions_DfDec(pstruAsnBasicSafetyMessage->emergencyExt, &(pstruWjBasicSafetyMessage->struemergencyExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_VehicleEmergencyExtensions_DfDec is err");
            return false;
        }
        pstruWjBasicSafetyMessage->u8emergencyExtPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBasicSafetyMessage->u8emergencyExtPresent = WJV4_ABSENT;
    }

    return true;
}
/**
* @brief     WJV4_MapData_MsgEnc编码函数
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
int32_t WJV4_MapData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV4_STRU_MapData *pstruWjMapData = (WJV4_STRU_MapData *)pvoidWjMsg;
    MapData_t *pstruAsnMapData = (MapData_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_MSGCOUNT_SIZE < pstruWjMapData->n32msgCnt) || (WJV4_MIN_MSGCOUNT_SIZE > pstruWjMapData->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjMapData->n32msgCnt = %d",
                 pstruWjMapData->n32msgCnt);
        return false;
    }
#endif
    pstruAsnMapData->msgCnt = pstruWjMapData->n32msgCnt;
    if (WJV4_PRESENT == pstruWjMapData->u8timeStampPresent)
    {
        pstruAsnMapData->timeStamp = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnMapData->timeStamp)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjMapData->n32timeStamp) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjMapData->n32timeStamp))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:pstruWjMapData->n32timeStamp = %d",
                     pstruWjMapData->n32timeStamp);
            return false;
        }
#endif
        *(pstruAsnMapData->timeStamp) = pstruWjMapData->n32timeStamp;
    }
    else
    {
        pstruAsnMapData->timeStamp = NULL;
    }
    n32Ret = WJV4_NodeList_DfEnc(&(pstruAsnMapData->nodes), &(pstruWjMapData->strunodes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_NodeList_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_MapData_MsgDec解码函数
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
int32_t WJV4_MapData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV4_STRU_MapData *pstruWjMapData = (WJV4_STRU_MapData *)pvoidWjMsg;
    MapData_t *pstruAsnMapData = (MapData_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_MSGCOUNT_SIZE < pstruAsnMapData->msgCnt) || (WJV4_MIN_MSGCOUNT_SIZE > pstruAsnMapData->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnMapData->msgCnt = %d",
                 pstruAsnMapData->msgCnt);
        return false;
    }
#endif
    pstruWjMapData->n32msgCnt = pstruAsnMapData->msgCnt;
    if (NULL != pstruAsnMapData->timeStamp)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnMapData->timeStamp)) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnMapData->timeStamp)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:*(pstruAsnMapData->timeStamp) = %d",
                     *(pstruAsnMapData->timeStamp));
            return false;
        }
#endif
        pstruWjMapData->n32timeStamp = *(pstruAsnMapData->timeStamp);
        pstruWjMapData->u8timeStampPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjMapData->u8timeStampPresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_NodeList_DfDec(&(pstruAsnMapData->nodes), &(pstruWjMapData->strunodes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_NodeList_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_RoadSideInformation_MsgEnc编码函数
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
int32_t WJV4_RoadSideInformation_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV4_STRU_RoadSideInformation *pstruWjRoadSideInformation = (WJV4_STRU_RoadSideInformation *)pvoidWjMsg;
    RoadSideInformation_t *pstruAsnRoadSideInformation = (RoadSideInformation_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_MSGCOUNT_SIZE < pstruWjRoadSideInformation->n32msgCnt) || (WJV4_MIN_MSGCOUNT_SIZE > pstruWjRoadSideInformation->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjRoadSideInformation->n32msgCnt = %d",
                 pstruWjRoadSideInformation->n32msgCnt);
        return false;
    }
#endif
    pstruAsnRoadSideInformation->msgCnt = pstruWjRoadSideInformation->n32msgCnt;
    if (WJV4_PRESENT == pstruWjRoadSideInformation->u8moyPresent)
    {
        pstruAsnRoadSideInformation->moy = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnRoadSideInformation->moy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjRoadSideInformation->n32moy) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjRoadSideInformation->n32moy))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:pstruWjRoadSideInformation->n32moy = %d",
                     pstruWjRoadSideInformation->n32moy);
            return false;
        }
#endif
        *(pstruAsnRoadSideInformation->moy) = pstruWjRoadSideInformation->n32moy;
    }
    else
    {
        pstruAsnRoadSideInformation->moy = NULL;
    }
    pstruAsnRoadSideInformation->id.size = WJV4_MAX_ID_SIZE;
    pstruAsnRoadSideInformation->id.buf = CALLOC(pstruAsnRoadSideInformation->id.size, sizeof(uint8_t));
    if (NULL == pstruAsnRoadSideInformation->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnRoadSideInformation->id.buf, pstruWjRoadSideInformation->u8OCTid, pstruAsnRoadSideInformation->id.size);
    n32Ret = WJV4_Position3D_DfEnc(&(pstruAsnRoadSideInformation->refPos),
                                   &(pstruWjRoadSideInformation->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_Position3D_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjRoadSideInformation->u8rtesPresent)
    {
        pstruAsnRoadSideInformation->rtes = CALLOC(1, sizeof(struct RTEList));
        if (NULL == pstruAsnRoadSideInformation->rtes)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_RTEList_DfEnc(pstruAsnRoadSideInformation->rtes, &(pstruWjRoadSideInformation->strurtes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_RTEList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRoadSideInformation->rtes = NULL;
    }
    if (WJV4_PRESENT == pstruWjRoadSideInformation->u8rtssPresent)
    {
        pstruAsnRoadSideInformation->rtss = CALLOC(1, sizeof(struct RTSList));
        if (NULL == pstruAsnRoadSideInformation->rtss)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_RTSList_DfEnc(pstruAsnRoadSideInformation->rtss, &(pstruWjRoadSideInformation->strurtss));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_RTSList_DfEnc is err");
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
* @brief     WJV4_RoadSideInformation_MsgDec解码函数
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
int32_t WJV4_RoadSideInformation_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV4_STRU_RoadSideInformation *pstruWjRoadSideInformation = (WJV4_STRU_RoadSideInformation *)pvoidWjMsg;
    RoadSideInformation_t *pstruAsnRoadSideInformation = (RoadSideInformation_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_MSGCOUNT_SIZE < pstruAsnRoadSideInformation->msgCnt) || (WJV4_MIN_MSGCOUNT_SIZE > pstruAsnRoadSideInformation->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnRoadSideInformation->msgCnt = %d",
                 pstruAsnRoadSideInformation->msgCnt);
        return false;
    }
#endif
    pstruWjRoadSideInformation->n32msgCnt = pstruAsnRoadSideInformation->msgCnt;
    if (NULL != pstruAsnRoadSideInformation->moy)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnRoadSideInformation->moy)) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnRoadSideInformation->moy)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:*(pstruAsnRoadSideInformation->moy) = %d",
                     *(pstruAsnRoadSideInformation->moy));
            return false;
        }
#endif
        pstruWjRoadSideInformation->n32moy = *(pstruAsnRoadSideInformation->moy);
        pstruWjRoadSideInformation->u8moyPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRoadSideInformation->u8moyPresent = WJV4_ABSENT;
    }
    memcpy(pstruWjRoadSideInformation->u8OCTid, pstruAsnRoadSideInformation->id.buf, pstruAsnRoadSideInformation->id.size);
    n32Ret = WJV4_Position3D_DfDec(&(pstruAsnRoadSideInformation->refPos),
                                   &(pstruWjRoadSideInformation->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_Position3D_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnRoadSideInformation->rtes)
    {
        n32Ret = WJV4_RTEList_DfDec(pstruAsnRoadSideInformation->rtes, &(pstruWjRoadSideInformation->strurtes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_RTEList_DfDec is err");
            return false;
        }
        pstruWjRoadSideInformation->u8rtesPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRoadSideInformation->u8rtesPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRoadSideInformation->rtss)
    {
        n32Ret = WJV4_RTSList_DfDec(pstruAsnRoadSideInformation->rtss, &(pstruWjRoadSideInformation->strurtss));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_RTSList_DfDec is err");
            return false;
        }
        pstruWjRoadSideInformation->u8rtssPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRoadSideInformation->u8rtssPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_RoadsideSafetyMessage_MsgEnc编码函数
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
int32_t WJV4_RoadsideSafetyMessage_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV4_STRU_RoadsideSafetyMessage *pstruWjRoadsideSafetyMessage = (WJV4_STRU_RoadsideSafetyMessage *)pvoidWjMsg;
    RoadsideSafetyMessage_t *pstruAsnRoadsideSafetyMessage = (RoadsideSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_MSGCOUNT_SIZE < pstruWjRoadsideSafetyMessage->n32msgCnt) || (WJV4_MIN_MSGCOUNT_SIZE > pstruWjRoadsideSafetyMessage->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjRoadsideSafetyMessage->n32msgCnt = %d",
                 pstruWjRoadsideSafetyMessage->n32msgCnt);
        return false;
    }
#endif
    pstruAsnRoadsideSafetyMessage->msgCnt = pstruWjRoadsideSafetyMessage->n32msgCnt;
    pstruAsnRoadsideSafetyMessage->id.size = WJV4_MAX_ID_SIZE;
    pstruAsnRoadsideSafetyMessage->id.buf = CALLOC(pstruAsnRoadsideSafetyMessage->id.size, sizeof(uint8_t));
    if (NULL == pstruAsnRoadsideSafetyMessage->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "CALLOC is err");
        return false;
    }
    memcpy(pstruAsnRoadsideSafetyMessage->id.buf, pstruWjRoadsideSafetyMessage->u8OCTid, pstruAsnRoadsideSafetyMessage->id.size);
    n32Ret = WJV4_Position3D_DfEnc(&(pstruAsnRoadsideSafetyMessage->refPos),
                                   &(pstruWjRoadsideSafetyMessage->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_Position3D_DfEnc is err");
        return false;
    }
    n32Ret = WJV4_ParticipantList_DfEnc(&(pstruAsnRoadsideSafetyMessage->participants),
                                        &(pstruWjRoadsideSafetyMessage->struparticipants));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_ParticipantList_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_RoadsideSafetyMessage_MsgDec解码函数
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
int32_t WJV4_RoadsideSafetyMessage_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV4_STRU_RoadsideSafetyMessage *pstruWjRoadsideSafetyMessage = (WJV4_STRU_RoadsideSafetyMessage *)pvoidWjMsg;
    RoadsideSafetyMessage_t *pstruAsnRoadsideSafetyMessage = (RoadsideSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_MSGCOUNT_SIZE < pstruAsnRoadsideSafetyMessage->msgCnt) || (WJV4_MIN_MSGCOUNT_SIZE > pstruAsnRoadsideSafetyMessage->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnRoadsideSafetyMessage->msgCnt = %d",
                 pstruAsnRoadsideSafetyMessage->msgCnt);
        return false;
    }
#endif
    pstruWjRoadsideSafetyMessage->n32msgCnt = pstruAsnRoadsideSafetyMessage->msgCnt;
    memcpy(pstruWjRoadsideSafetyMessage->u8OCTid, pstruAsnRoadsideSafetyMessage->id.buf, pstruAsnRoadsideSafetyMessage->id.size);
    n32Ret = WJV4_Position3D_DfDec(&(pstruAsnRoadsideSafetyMessage->refPos),
                                   &(pstruWjRoadsideSafetyMessage->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_Position3D_DfDec is err");
        return false;
    }
    n32Ret = WJV4_ParticipantList_DfDec(&(pstruAsnRoadsideSafetyMessage->participants),
                                        &(pstruWjRoadsideSafetyMessage->struparticipants));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_ParticipantList_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_SPAT_MsgEnc编码函数
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
int32_t WJV4_SPAT_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV4_STRU_SPAT *pstruWjSPAT = (WJV4_STRU_SPAT *)pvoidWjMsg;
    SPAT_t *pstruAsnSPAT = (SPAT_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_MSGCOUNT_SIZE < pstruWjSPAT->n32msgCnt) || (WJV4_MIN_MSGCOUNT_SIZE > pstruWjSPAT->n32msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruWjSPAT->n32msgCnt = %d",
                 pstruWjSPAT->n32msgCnt);
        return false;
    }
#endif
    pstruAsnSPAT->msgCnt = pstruWjSPAT->n32msgCnt;
    if (WJV4_PRESENT == pstruWjSPAT->u8moyPresent)
    {
        pstruAsnSPAT->moy = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnSPAT->moy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjSPAT->n32moy) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjSPAT->n32moy))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:pstruWjSPAT->n32moy = %d",
                     pstruWjSPAT->n32moy);
            return false;
        }
#endif
        *(pstruAsnSPAT->moy) = pstruWjSPAT->n32moy;
    }
    else
    {
        pstruAsnSPAT->moy = NULL;
    }
    if (WJV4_PRESENT == pstruWjSPAT->u8timeStampPresent)
    {
        pstruAsnSPAT->timeStamp = CALLOC(1, sizeof(DSecond_t));
        if (NULL == pstruAsnSPAT->timeStamp)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_DSECOND_SIZE < pstruWjSPAT->n32timeStamp) || (WJV4_MIN_DSECOND_SIZE > pstruWjSPAT->n32timeStamp))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:pstruWjSPAT->n32timeStamp = %d",
                     pstruWjSPAT->n32timeStamp);
            return false;
        }
#endif
        *(pstruAsnSPAT->timeStamp) = pstruWjSPAT->n32timeStamp;
    }
    else
    {
        pstruAsnSPAT->timeStamp = NULL;
    }
    if (WJV4_PRESENT == pstruWjSPAT->u8namePresent)
    {
        pstruAsnSPAT->name = CALLOC(1, sizeof(DescriptiveName_t));
        if (NULL == pstruAsnSPAT->name)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_DescriptiveName_DeEnc(pstruAsnSPAT->name, &(pstruWjSPAT->stria5name));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_DescriptiveName_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnSPAT->name = NULL;
    }
    n32Ret = WJV4_IntersectionStateList_DfEnc(&(pstruAsnSPAT->intersections), &(pstruWjSPAT->struintersections));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_IntersectionStateList_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_SPAT_MsgDec解码函数
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
int32_t WJV4_SPAT_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV4_STRU_SPAT *pstruWjSPAT = (WJV4_STRU_SPAT *)pvoidWjMsg;
    SPAT_t *pstruAsnSPAT = (SPAT_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_MSGCOUNT_SIZE < pstruAsnSPAT->msgCnt) || (WJV4_MIN_MSGCOUNT_SIZE > pstruAsnSPAT->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:pstruAsnSPAT->msgCnt = %d",
                 pstruAsnSPAT->msgCnt);
        return false;
    }
#endif
    pstruWjSPAT->n32msgCnt = pstruAsnSPAT->msgCnt;
    if (NULL != pstruAsnSPAT->moy)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnSPAT->moy)) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnSPAT->moy)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:*(pstruAsnSPAT->moy) = %d",
                     *(pstruAsnSPAT->moy));
            return false;
        }
#endif
        pstruWjSPAT->n32moy = *(pstruAsnSPAT->moy);
        pstruWjSPAT->u8moyPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjSPAT->u8moyPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnSPAT->timeStamp)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_DSECOND_SIZE < *(pstruAsnSPAT->timeStamp)) || (WJV4_MIN_DSECOND_SIZE > *(pstruAsnSPAT->timeStamp)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:*(pstruAsnSPAT->timeStamp) = %d",
                     *(pstruAsnSPAT->timeStamp));
            return false;
        }
#endif
        pstruWjSPAT->n32timeStamp = *(pstruAsnSPAT->timeStamp);
        pstruWjSPAT->u8timeStampPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjSPAT->u8timeStampPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnSPAT->name)
    {
        n32Ret = WJV4_DescriptiveName_DeDec(pstruAsnSPAT->name, &(pstruWjSPAT->stria5name));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV4_DescriptiveName_DeDec is err");
            return false;
        }
        pstruWjSPAT->u8namePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjSPAT->u8namePresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_IntersectionStateList_DfDec(&(pstruAsnSPAT->intersections), &(pstruWjSPAT->struintersections));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_IntersectionStateList_DfDec is err");
        return false;
    }
    return true;
}
/* 文件结束 */