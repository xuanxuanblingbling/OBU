/**
* @file         :wjv3_uper_Msg.c
* @brief        :该文件为协议栈消息类型编解码函数定义
* @details  	:主要包含协议消息类型编解码函数
* @author   	:huangsai  any question please send mail to huangsai@wanji,net.cn
* @date     	:2020-8-10
* @version		:V1.0
* @copyright 	:Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
/* 头文件包含 */
#include "wjv3_uper_Msg.h"
#include "wjv3_uper_com.h"
/**
 * @brief     BSM消息编码函数
 * @details   协议栈消息层编解码中 BasicSafetyMessage 消息的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
 */
int32_t WJV3_BasicSafetyMessage_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV3_STRU_BasicSafetyMessage *pstruWjBsmMsg = (WJV3_STRU_BasicSafetyMessage *)pvoidWjMsg;
    BasicSafetyMessage_t *pstruAsnBsmMsg = (BasicSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_MSGCOUNT_SIZE < pstruWjBsmMsg->n32msgcnt)
        || (WJV3_MIN_MSGCOUNT_SIZE > pstruWjBsmMsg->n32msgcnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32msgcnt = %d",
                 pstruWjBsmMsg->n32msgcnt);
        return false;
    }
    #endif
    pstruAsnBsmMsg->msgCnt = pstruWjBsmMsg->n32msgcnt;
    pstruAsnBsmMsg->id.size = WJV3_MAX_BYTE_ID_LEN;
    pstruAsnBsmMsg->id.buf = CALLOC(1, pstruAsnBsmMsg->id.size);
    if (NULL == pstruAsnBsmMsg->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    /* 容易出错，请注意 */
    memcpy(pstruAsnBsmMsg->id.buf, pstruWjBsmMsg->u8Id, pstruAsnBsmMsg->id.size);
    if (0 < pstruWjBsmMsg->u8platNo_Len)
    {
        pstruAsnBsmMsg->plateNo = CALLOC(1, sizeof(OCTET_STRING_t));
        if (NULL == pstruAsnBsmMsg->plateNo)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        if ((4 > pstruWjBsmMsg->u8platNo_Len)
            || (WJV3_MAX_BYTE_PLATNO_LEN < pstruWjBsmMsg->u8platNo_Len))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:u8platNo_Len = %d",
                     pstruWjBsmMsg->u8platNo_Len);
            return false;
        }
        pstruAsnBsmMsg->plateNo->size = (int32_t)pstruWjBsmMsg->u8platNo_Len;
        pstruAsnBsmMsg->plateNo->buf = CALLOC(1, pstruAsnBsmMsg->plateNo->size);
        if (NULL == pstruAsnBsmMsg->plateNo->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        /* 容易出错，请注意 */
        memcpy(pstruAsnBsmMsg->plateNo->buf, (uint8_t *)pstruWjBsmMsg->u8platNo, pstruAsnBsmMsg->plateNo->size);
    }
    else
    {
        pstruAsnBsmMsg->plateNo = NULL;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_DSECOND_SIZE < pstruWjBsmMsg->n32secMark)
        || (WJV3_MIN_DSECOND_SIZE > pstruWjBsmMsg->n32secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32secMark = %d",
                 pstruWjBsmMsg->n32secMark);
        return false;
    }
    #endif
    pstruAsnBsmMsg->secMark = pstruWjBsmMsg->n32secMark;
    n32Ret = WJV3_Position3D_DfEnc(&(pstruAsnBsmMsg->pos), &(pstruWjBsmMsg->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_Position3D_DfEnc is err");
        return false;
    }
    n32Ret = WJV3_PositionConfidenceSet_DfEnc(&(pstruAsnBsmMsg->accuracy), &(pstruWjBsmMsg->struaccuracy));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionConfidenceSet_DfEnc is err");
        return false;
    }
    n32Ret = WJV3_TransmissionState_DeEnc(&(pstruAsnBsmMsg->transmission), &(pstruWjBsmMsg->enumTransmissionState));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_TransmissionState_DeEnc is err");
        return false;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_SPEED_SIZE < pstruWjBsmMsg->n32speed)
        || (WJV3_MIN_SPEED_SIZE > pstruWjBsmMsg->n32speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32speed = %d",
                 pstruWjBsmMsg->n32speed);
        return false;
    }
    #endif
    pstruAsnBsmMsg->speed = pstruWjBsmMsg->n32speed;
    #ifdef _CHECK_
    if ((WJV3_MAX_HEADING_SIZE < pstruWjBsmMsg->n32heading)
        || (WJV3_MIN_HEADING_SIZE > pstruWjBsmMsg->n32heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32heading = %d",
                 pstruWjBsmMsg->n32heading);
        return false;
    }
    #endif
    pstruAsnBsmMsg->heading = pstruWjBsmMsg->n32heading;
    if (WJV3_PRESENT == pstruWjBsmMsg->u8angle_Present)
    {
        pstruAsnBsmMsg->angle = CALLOC(1, sizeof(SteeringWheelAngle_t));
        if (NULL == pstruAsnBsmMsg->angle)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        #ifdef _CHECK_
        if ((WJV3_MAX_STEETINGWHEELANGLE_SIZE < pstruWjBsmMsg->n32angle)
                || (WJV3_MIN_STEETINGWHEELANGLE_SIZE > pstruWjBsmMsg->n32angle))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32angle = %d",
                     pstruWjBsmMsg->n32angle);
            return false;
        }
        #endif
        *(pstruAsnBsmMsg->angle) = pstruWjBsmMsg->n32angle;
    }
    else
    {
        pstruAsnBsmMsg->angle = NULL;
    }
    if (WJV3_PRESENT == pstruWjBsmMsg->u8motionCfd_Present)
    {
        pstruAsnBsmMsg->motionCfd = CALLOC(1, sizeof(MotionConfidenceSet_t));
        if (NULL == pstruAsnBsmMsg->motionCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_MotionConfidenceSet_DfEnc(pstruAsnBsmMsg->motionCfd, &(pstruWjBsmMsg->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_STRU_MotionConfidenceSet_DfEnc is err ");
            return false;
        }
    }
    else
    {
        pstruAsnBsmMsg->motionCfd = NULL;
    }
    n32Ret = WJV3_AccelerationSet4Way_DfEnc(&(pstruAsnBsmMsg->accelSet), &(pstruWjBsmMsg->struaccelSet));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_AccelerationSet4Way_DfEnc is err");
        return false;
    }
    n32Ret = WJV3_BrakeSystemStatus_DfEnc(&(pstruAsnBsmMsg->brakes), &(pstruWjBsmMsg->strubrakes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_BrakeSystemStatus_DfEnc is err");
        return false;
    }
    n32Ret = WJV3_VehicleSize_DfEnc(&(pstruAsnBsmMsg->size), &(pstruWjBsmMsg->strusize));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_VehicleSize_DfEnc is err");
        return false;
    }
    n32Ret = WJV3_VehicleClassification_DfEnc(&(pstruAsnBsmMsg->vehicleClass), &(pstruWjBsmMsg->struvehicleClass));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_VehicleClassification_DfEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjBsmMsg->u8safetyExt_Present)
    {
        pstruAsnBsmMsg->safetyExt = CALLOC(1, sizeof(struct VehicleSafetyExtensions));
        if (NULL == pstruAsnBsmMsg->safetyExt)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_VehicleSafetyExtensions_DfEnc(pstruAsnBsmMsg->safetyExt, &(pstruWjBsmMsg->strusafetyExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_VehicleSafetyExtensions_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBsmMsg->safetyExt = NULL;
    }
    return true;
}
/**
 * @brief     BSM消息解码函数
 * @details   协议栈消息层编解码中 BasicSafetyMessage 消息的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
 */
int32_t WJV3_BasicSafetyMessage_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV3_STRU_BasicSafetyMessage *pstruWjBsmMsg = (WJV3_STRU_BasicSafetyMessage *)pvoidWjMsg;
    BasicSafetyMessage_t *pstruAsnBsmMsg = (BasicSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_MSGCOUNT_SIZE < pstruAsnBsmMsg->msgCnt)
        || (WJV3_MIN_MSGCOUNT_SIZE > pstruAsnBsmMsg->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:msgCnt = %d",
                 pstruAsnBsmMsg->msgCnt);
        return false;
    }
    #endif
    pstruWjBsmMsg->n32msgcnt = pstruAsnBsmMsg->msgCnt;
    if ((WJV3_MAX_BYTE_ID_LEN != pstruAsnBsmMsg->id.size)
        || (NULL == pstruAsnBsmMsg->id.buf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rang:size = %d",
                 pstruAsnBsmMsg->id.size);
        return false;
    }
    /* 容易出错，请注意 */
    memcpy(pstruWjBsmMsg->u8Id, pstruAsnBsmMsg->id.buf, pstruAsnBsmMsg->id.size);
    if (NULL != pstruAsnBsmMsg->plateNo)
    {
        if ((4 > pstruAsnBsmMsg->plateNo->size)
            || (WJV3_MAX_BYTE_PLATNO_LEN < pstruAsnBsmMsg->plateNo->size)
            || (NULL == (pstruAsnBsmMsg->plateNo->buf)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rang:size = %d",
                     pstruAsnBsmMsg->plateNo->size);
            return false;
        }
        /* 容易出错，请注意 */
        memcpy(pstruWjBsmMsg->u8platNo, pstruAsnBsmMsg->plateNo->buf, pstruAsnBsmMsg->plateNo->size);
        pstruWjBsmMsg->u8platNo_Len = (uint8_t)pstruAsnBsmMsg->plateNo->size;
    }
    else
    {
        pstruWjBsmMsg->u8platNo_Len = 0;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_DSECOND_SIZE < pstruAsnBsmMsg->secMark)
        || (WJV3_MIN_DSECOND_SIZE > pstruAsnBsmMsg->secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rang:secMark = %d",
                 pstruAsnBsmMsg->secMark);
        return false;
    }
    #endif
    pstruWjBsmMsg->n32secMark = pstruAsnBsmMsg->secMark;
    n32Ret = WJV3_Position3D_DfDec(&(pstruAsnBsmMsg->pos), &(pstruWjBsmMsg->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_Position3D_DfDec is err");
        return false;
    }
    n32Ret = WJV3_PositionConfidenceSet_DfDec(&(pstruAsnBsmMsg->accuracy), &(pstruWjBsmMsg->struaccuracy));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_Position3D_DfDec is err");
        return false;
    }
    n32Ret = WJV3_TransmissionState_DeDec(&(pstruAsnBsmMsg->transmission), &(pstruWjBsmMsg->enumTransmissionState));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_TransmissionState_DeDec is err");
        return false;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_SPEED_SIZE < pstruAsnBsmMsg->speed)
        || (WJV3_MIN_SPEED_SIZE > pstruAsnBsmMsg->speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rang:speed = %d",
                 pstruAsnBsmMsg->speed);
        return false;
    }
    #endif
    pstruWjBsmMsg->n32speed = pstruAsnBsmMsg->speed;
    #ifdef _CHECK_
    if ((WJV3_MAX_HEADING_SIZE < pstruAsnBsmMsg->heading)
        || (WJV3_MIN_HEADING_SIZE > pstruAsnBsmMsg->heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rang:heading = %d",
                 pstruAsnBsmMsg->heading);
        return false;
    }
    #endif
    pstruWjBsmMsg->n32heading = pstruAsnBsmMsg->heading;
    if (NULL != pstruAsnBsmMsg->angle)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_STEETINGWHEELANGLE_SIZE < *(pstruAsnBsmMsg->angle))
            || (WJV3_MIN_STEETINGWHEELANGLE_SIZE > *(pstruAsnBsmMsg->angle)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rang:angle = %d",
                     pstruAsnBsmMsg->angle);
            return false;
        }
        #endif
        pstruWjBsmMsg->n32angle = *(pstruAsnBsmMsg->angle);
        pstruWjBsmMsg->u8angle_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjBsmMsg->u8angle_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnBsmMsg->motionCfd)
    {
        n32Ret = WJV3_MotionConfidenceSet_DfDec(pstruAsnBsmMsg->motionCfd, &(pstruWjBsmMsg->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_MotionConfidenceSet_DfDec is err");
            return false;
        }
        pstruWjBsmMsg->u8motionCfd_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjBsmMsg->u8motionCfd_Present = WJV3_ABSENT;
    }
    n32Ret = WJV3_AccelerationSet4Way_DfDec(&(pstruAsnBsmMsg->accelSet), &(pstruWjBsmMsg->struaccelSet));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_AccelerationSet4Way_DfDec is err");
        return false;
    }
    n32Ret = WJV3_BrakeSystemStatus_DfDec(&(pstruAsnBsmMsg->brakes), &(pstruWjBsmMsg->strubrakes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_BrakeSystemStatus_DfDec is err");
        return false;
    }
    n32Ret = WJV3_VehicleSize_DfDec(&(pstruAsnBsmMsg->size), &(pstruWjBsmMsg->strusize));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_VehicleSize_DfDec is err");
        return false;
    }
    n32Ret = WJV3_VehicleClassification_DfDec(&(pstruAsnBsmMsg->vehicleClass), &(pstruWjBsmMsg->struvehicleClass));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_VehicleClassification_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnBsmMsg->safetyExt)
    {
        n32Ret = WJV3_VehicleSafetyExtensions_DfDec(pstruAsnBsmMsg->safetyExt, &(pstruWjBsmMsg->strusafetyExt));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_VehicleSafetyExtensions_DfDec is err");
            return false;
        }
        pstruWjBsmMsg->u8safetyExt_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjBsmMsg->u8motionCfd_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief     MAP消息编码函数
 * @details   协议栈消息层编解码中 MapData 消息的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
 */
int32_t WJV3_MapData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV3_STRU_MapData *pstruWjMapMsg = (WJV3_STRU_MapData *)pvoidWjMsg;
    MapData_t *pstruAsnMapMsg = (MapData_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_MSGCOUNT_SIZE < pstruWjMapMsg->n32msgcnt)
        || (WJV3_MIN_MSGCOUNT_SIZE > pstruWjMapMsg->n32msgcnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32msgcnt = %d",
                 pstruWjMapMsg->n32msgcnt);
        return false;
    }
    #endif
    pstruAsnMapMsg->msgCnt = pstruWjMapMsg->n32msgcnt;
    if (WJV3_PRESENT == pstruWjMapMsg->u8timeStamp_Present)
    {
        pstruAsnMapMsg->timeStamp = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnMapMsg->timeStamp)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        #ifdef _CHECK_
        if ((WJV3_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjMapMsg->n32timeStamp) || (WJV3_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjMapMsg->n32timeStamp))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32timeStamp = %d",
                     pstruWjMapMsg->n32timeStamp);
            return false;
        }
        #endif
        *(pstruAsnMapMsg->timeStamp) = pstruWjMapMsg->n32timeStamp;
    }
    else
    {
        pstruAsnMapMsg->timeStamp = NULL;
    }
    n32Ret = WJV3_NodeList_DfEnc(&(pstruAsnMapMsg->nodes), &(pstruWjMapMsg->strunodes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeList_MsgEnc is err");
        return false;
    }
    return true;
}
/**
 * @brief     MAP消息解码函数
 * @details   协议栈消息层编解码中 MapData 消息的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
 */
int32_t WJV3_MapData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV3_STRU_MapData *pstruWjMapMsg = (WJV3_STRU_MapData *)pvoidWjMsg;
    MapData_t *pstruAsnMapMsg = (MapData_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_MSGCOUNT_SIZE < pstruAsnMapMsg->msgCnt)
        || (WJV3_MIN_MSGCOUNT_SIZE > pstruAsnMapMsg->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:msgCnt = %d",
                 pstruAsnMapMsg->msgCnt);
        return false;
    }
    #endif
    pstruWjMapMsg->n32msgcnt = pstruAsnMapMsg->msgCnt;
    if (NULL != pstruAsnMapMsg->timeStamp)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnMapMsg->timeStamp)) || (WJV3_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnMapMsg->timeStamp)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:timeStamp = %d",
                     *(pstruAsnMapMsg->timeStamp));
        }
        #endif
        pstruWjMapMsg->n32timeStamp = *(pstruAsnMapMsg->timeStamp);
        pstruWjMapMsg->u8timeStamp_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjMapMsg->u8timeStamp_Present = WJV3_ABSENT;
    }
    n32Ret = WJV3_NodeList_DfDec(&(pstruAsnMapMsg->nodes), &(pstruWjMapMsg->strunodes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeList_DfDec is err");
        return false;
    }
    return true;
}
/**
 * @brief     RSM消息编码函数
 * @details   协议栈消息层编解码中 RoadsideSafetyMessage 消息的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
 */
int32_t WJV3_RoadsideSafetyMessage_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV3_STRU_RoadsideSafetyMessage *pstruWjRsmMsg = (WJV3_STRU_RoadsideSafetyMessage *)pvoidWjMsg;
    RoadsideSafetyMessage_t *pstruAsnRsmMsg = (RoadsideSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_MSGCOUNT_SIZE < pstruWjRsmMsg->n32msgcnt)
        || (WJV3_MIN_MSGCOUNT_SIZE > pstruWjRsmMsg->n32msgcnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32msgcnt = %d",
                 pstruWjRsmMsg->n32msgcnt);
        return false;
    }
    #endif
    pstruAsnRsmMsg->msgCnt = pstruWjRsmMsg->n32msgcnt;
    pstruAsnRsmMsg->id.size = WJV3_MAX_BYTE_ID_LEN;
    pstruAsnRsmMsg->id.buf = CALLOC(1, pstruAsnRsmMsg->id.size);
    if (NULL == pstruAsnRsmMsg->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    /* 容易出错，请注意 */
    memcpy(pstruAsnRsmMsg->id.buf, pstruWjRsmMsg->u8Id, pstruAsnRsmMsg->id.size);
    n32Ret = WJV3_Position3D_DfEnc(&(pstruAsnRsmMsg->refPos), &(pstruWjRsmMsg->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_Position3D_DfEnc is err");
        return false;
    }
    n32Ret = WJV3_ParticipantList_DfEnc(&(pstruAsnRsmMsg->participants), &(pstruWjRsmMsg->struparticipants));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_ParticipantList_DfEnc is err");
        return false;
    }
    return true;
}
/**
 * @brief     RSM消息解码函数
 * @details   协议栈消息层编解码中 RoadsideSafetyMessage 消息的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
 */
int32_t WJV3_RoadsideSafetyMessage_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV3_STRU_RoadsideSafetyMessage *pstruWjRsmMsg = (WJV3_STRU_RoadsideSafetyMessage *)pvoidWjMsg;
    RoadsideSafetyMessage_t *pstruAsnRsmMsg = (RoadsideSafetyMessage_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_MSGCOUNT_SIZE < pstruAsnRsmMsg->msgCnt)
        || (WJV3_MIN_MSGCOUNT_SIZE > pstruAsnRsmMsg->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:msgCnt = %d",
                 pstruAsnRsmMsg->msgCnt);
        return false;
    }
    #endif
    pstruWjRsmMsg->n32msgcnt = pstruAsnRsmMsg->msgCnt;
    #ifdef _CHECK_
    if ((WJV3_MAX_BYTE_ID_LEN != pstruAsnRsmMsg->id.size)
        || (NULL == (pstruAsnRsmMsg->id.buf)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rang:size = %d",
                 pstruAsnRsmMsg->id.size);
        return false;
    }
    #endif
    /* 容易出错，请注意 */
    memcpy(pstruWjRsmMsg->u8Id, pstruAsnRsmMsg->id.buf, pstruAsnRsmMsg->id.size);
    n32Ret = WJV3_Position3D_DfDec(&(pstruAsnRsmMsg->refPos), &(pstruWjRsmMsg->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_Position3D_DfDec is err");
        return false;
    }
    n32Ret = WJV3_ParticipantList_DfDec(&(pstruAsnRsmMsg->participants), &(pstruWjRsmMsg->struparticipants));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_ParticipantList_DfDec is err");
        return false;
    }
    return true;
}
/**
 * @brief    SPAT消息编码函数
 * @details   协议栈消息层编解码中 SPAT 消息的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
 */
int32_t WJV3_SPAT_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV3_STRU_SPAT *pstruWjSpatMsg = (WJV3_STRU_SPAT *)pvoidWjMsg;
    SPAT_t *pstruAsnSpatMsg = (SPAT_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_MSGCOUNT_SIZE < pstruWjSpatMsg->n32msgcnt)
        || (WJV3_MIN_MSGCOUNT_SIZE > pstruWjSpatMsg->n32msgcnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32msgcnt = %d",
                 pstruWjSpatMsg->n32msgcnt);
        return false;
    }
    #endif
    pstruAsnSpatMsg->msgCnt = pstruWjSpatMsg->n32msgcnt;
    if (WJV3_PRESENT == pstruWjSpatMsg->u8timeStamp_Present)
    {
        pstruAsnSpatMsg->timeStamp = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnSpatMsg->timeStamp)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        #ifdef _CHECK_
        if ((WJV3_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjSpatMsg->n32timeStamp)
            || (WJV3_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjSpatMsg->n32timeStamp))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32timeStamp = %d",
                     pstruWjSpatMsg->n32timeStamp);
            return false;
        }
        #endif
        *(pstruAsnSpatMsg->timeStamp) = pstruWjSpatMsg->n32timeStamp;
    }
    else
    {
        pstruAsnSpatMsg->timeStamp = NULL;
    }
    if (0 != pstruWjSpatMsg->u8nameNum)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_IA5_NAME_LEN < pstruWjSpatMsg->u8nameNum)
            || (0 > pstruWjSpatMsg->u8nameNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:u8nameNum = %d",
                     pstruWjSpatMsg->u8nameNum);
            return false;
        }
        #endif
        /* 检查IA5String_t类型 */
        n32Ret = WJV3_Check_IA5String(pstruWjSpatMsg->u8name, pstruWjSpatMsg->u8nameNum);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_Check_IA5String is err");
            return false;
        }
        pstruAsnSpatMsg->name = CALLOC(1, sizeof(DescriptiveName_t));
        if (NULL == pstruAsnSpatMsg->name)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        /* 容易出错，请注意 */
        pstruAsnSpatMsg->name->buf = CALLOC(1, pstruWjSpatMsg->u8nameNum);
        if (NULL == pstruAsnSpatMsg->name->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        memcpy(pstruAsnSpatMsg->name->buf, pstruWjSpatMsg->u8name, pstruWjSpatMsg->u8nameNum);
        pstruAsnSpatMsg->name->size = (size_t)pstruWjSpatMsg->u8nameNum;
    }
    else
    {
        pstruAsnSpatMsg->name = NULL;
    }
    n32Ret = WJV3_IntersectionStateList_DfEnc(&(pstruAsnSpatMsg->intersections), &(pstruWjSpatMsg->struintersections));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_IntersectionStateList_DfEnc is err");
        return false;
    }
    return true;
}
/**
 * @brief     SPAT消息解码函数
 * @details   协议栈消息层编解码中 SPAT 消息的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
 */
int32_t WJV3_SPAT_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV3_STRU_SPAT *pstruWjSpatMsg = (WJV3_STRU_SPAT *)pvoidWjMsg;
    SPAT_t *pstruAsnSpatMsg = (SPAT_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_MSGCOUNT_SIZE < pstruAsnSpatMsg->msgCnt)
        || (WJV3_MIN_MSGCOUNT_SIZE > pstruAsnSpatMsg->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:msgCnt = %d",
                 pstruAsnSpatMsg->msgCnt);
        return false;
    }
    #endif
    pstruWjSpatMsg->n32msgcnt = pstruAsnSpatMsg->msgCnt;
    if (NULL != pstruAsnSpatMsg->timeStamp)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnSpatMsg->timeStamp))
            || (WJV3_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnSpatMsg->timeStamp)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:timeStamp = %d",
                     *(pstruAsnSpatMsg->timeStamp));
        }
        #endif
        pstruWjSpatMsg->n32timeStamp = *(pstruAsnSpatMsg->timeStamp);
        pstruWjSpatMsg->u8timeStamp_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjSpatMsg->u8timeStamp_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnSpatMsg->name)
    {
        if ((0 == pstruAsnSpatMsg->name->size)
            || (WJV3_MAX_IA5_NAME_LEN < pstruAsnSpatMsg->name->size)
            || (NULL == (pstruAsnSpatMsg->name->buf)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rang:size = %d",
                     pstruAsnSpatMsg->name->size);
            return false;
        }
        memcpy(pstruWjSpatMsg->u8name, pstruAsnSpatMsg->name->buf, pstruAsnSpatMsg->name->size);
        pstruWjSpatMsg->u8nameNum = (uint8_t)pstruAsnSpatMsg->name->size;
    }
    else
    {
        pstruWjSpatMsg->u8nameNum = 0;
    }
    n32Ret = WJV3_IntersectionStateList_DfDec(&(pstruAsnSpatMsg->intersections), &(pstruWjSpatMsg->struintersections));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_IntersectionStateList_DfDec is err");
        return false;
    }
    return true;
}
/**
 * @brief    RoadSideInformation消息编码函数
 * @details   协议栈消息层编解码中 RoadSideInformation 消息的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
 */
int32_t WJV3_RoadSideInformation_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV3_STRU_RoadSideInformation *pstruWjRsiMsg = (WJV3_STRU_RoadSideInformation *)pvoidWjMsg;
    RoadSideInformation_t *pstruAsnRsiMsg = (RoadSideInformation_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_MSGCOUNT_SIZE < pstruWjRsiMsg->n32msgcnt)
        || (WJV3_MIN_MSGCOUNT_SIZE > pstruWjRsiMsg->n32msgcnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32msgcnt = %d",
                 pstruWjRsiMsg->n32msgcnt);
        return false;
    }
    #endif
    pstruAsnRsiMsg->msgCnt = pstruWjRsiMsg->n32msgcnt;
    if (WJV3_PRESENT == pstruWjRsiMsg->u8timeStamp_Present)
    {
        pstruAsnRsiMsg->timeStamp = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnRsiMsg->timeStamp)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        #ifdef _CHECK_
        if ((WJV3_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjRsiMsg->n32timeStamp)
            || (WJV3_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjRsiMsg->n32timeStamp))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32timeStamp = %d",
                     pstruWjRsiMsg->n32timeStamp);
            return false;
        }
        #endif
        *(pstruAsnRsiMsg->timeStamp) = pstruWjRsiMsg->n32timeStamp;
    }
    else
    {
        pstruAsnRsiMsg->timeStamp = NULL;
    }
    pstruAsnRsiMsg->id.size = WJV3_MAX_BYTE_ID_LEN;
    pstruAsnRsiMsg->id.buf = CALLOC(1, pstruAsnRsiMsg->id.size);
    if (NULL == pstruAsnRsiMsg->id.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    /* 容易出错，请注意 */
    memcpy(pstruAsnRsiMsg->id.buf, pstruWjRsiMsg->u8Id, pstruAsnRsiMsg->id.size);
    #ifdef _CHECK_
    if ((WJV3_MAX_RSIID_SIZE < pstruWjRsiMsg->n32rsiId)
        || (WJV3_MIN_RSIID_SIZE > pstruWjRsiMsg->n32rsiId))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32rsiId = %d",
                 pstruWjRsiMsg->n32rsiId);
        return false;
    }
    #endif
    pstruAsnRsiMsg->rsiId = pstruWjRsiMsg->n32rsiId;
    n32Ret = WJV3_AlertType_DeEnc(&(pstruAsnRsiMsg->alertType), &(pstruWjRsiMsg->n32alertType));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_AlertType_DeEnc is err");
        return false;
    }
    if (0 != pstruWjRsiMsg->u16descriptionNum)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DESCRIPTION_LEN < pstruWjRsiMsg->u16descriptionNum)
        || (0 > pstruWjRsiMsg->u16descriptionNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:u16descriptionNum = %d",
                     pstruWjRsiMsg->u16descriptionNum);
            return false;
        }
        #endif
        /* 检查IA5String_t类型 */
        n32Ret = WJV3_Check_IA5String(pstruWjRsiMsg->u8description, pstruWjRsiMsg->u16descriptionNum);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_Check_IA5String is err");
            return false;
        }
        pstruAsnRsiMsg->description = CALLOC(1, sizeof(IA5String_t));
        if (NULL == pstruAsnRsiMsg->description)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnRsiMsg->description->buf = CALLOC(1, pstruWjRsiMsg->u16descriptionNum);
        if (NULL == pstruAsnRsiMsg->description->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        /* 容易出错，请注意 */
        memcpy(pstruAsnRsiMsg->description->buf, pstruWjRsiMsg->u8description, pstruWjRsiMsg->u16descriptionNum);
        pstruAsnRsiMsg->description->size = (size_t)pstruWjRsiMsg->u16descriptionNum;
    }
    else
    {
        pstruAsnRsiMsg->description = NULL;
    }
    if (0 != pstruWjRsiMsg->u8priorityNum)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_PRIORITY_LEN < pstruWjRsiMsg->u8priorityNum)
            || (0 > pstruWjRsiMsg->u8priorityNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:u8priorityNum = %d",
                     pstruWjRsiMsg->u8priorityNum);
            return false;
        }
        #endif
        pstruAsnRsiMsg->priority = CALLOC(1, sizeof(IA5String_t));
        if (NULL == pstruAsnRsiMsg->priority)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnRsiMsg->priority->size = (int32_t)pstruWjRsiMsg->u8priorityNum;
        pstruAsnRsiMsg->priority->buf = CALLOC(1, pstruAsnRsiMsg->description->size);
        if (NULL == pstruAsnRsiMsg->description->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        /* 容易出错，请注意 */
        memcpy(pstruAsnRsiMsg->priority->buf, (uint8_t *)pstruWjRsiMsg->u8priority, pstruAsnRsiMsg->priority->size);
    }
    else
    {
        pstruAsnRsiMsg->priority = NULL;
    }
    n32Ret = WJV3_Position3D_DfEnc(&(pstruAsnRsiMsg->refPos), &(pstruWjRsiMsg->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_Position3D_DfEnc is err");
        return false;
    }
    n32Ret = WJV3_PathPointList_DfEnc(&(pstruAsnRsiMsg->alertPath), &(pstruWjRsiMsg->strualertPath));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PathPointList_DfEnc is err");
        return false;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_RADIUS_SIZE < pstruWjRsiMsg->n32alertRadius)
        || (WJV3_MIN_RADIUS_SIZE > pstruWjRsiMsg->n32alertRadius) )
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32alertRadius = %d",
                 pstruWjRsiMsg->n32alertRadius);
        return false;
    }
    #endif
    pstruAsnRsiMsg->alertRadius = pstruWjRsiMsg->n32alertRadius;
    return true;
}
/**
 * @brief     RoadSideInformation消息解码函数
 * @details   协议栈消息层编解码中 RoadSideInformation 消息的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
 */
int32_t WJV3_RoadSideInformation_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg)
{
    if ((NULL == pvoidAsnMsg) || (NULL == pvoidWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnMsg = %p pvoidWjMsg = %p",
                 pvoidAsnMsg, pvoidWjMsg);
        return false;
    }
    WJV3_STRU_RoadSideInformation *pstruWjRsiMsg = (WJV3_STRU_RoadSideInformation *)pvoidWjMsg;
    RoadSideInformation_t *pstruAsnRsiMsg = (RoadSideInformation_t *)pvoidAsnMsg;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_MSGCOUNT_SIZE < pstruAsnRsiMsg->msgCnt)
        || (WJV3_MIN_MSGCOUNT_SIZE > pstruAsnRsiMsg->msgCnt))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:msgCnt = %d",
                 pstruAsnRsiMsg->msgCnt);
        return false;
    }
    #endif
    pstruWjRsiMsg->n32msgcnt = pstruAsnRsiMsg->msgCnt;
    if (NULL != pstruAsnRsiMsg->timeStamp)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnRsiMsg->timeStamp))
            || (WJV3_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnRsiMsg->timeStamp)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:timeStamp = %d",
                     *(pstruAsnRsiMsg->timeStamp));
        }
        #endif
        pstruWjRsiMsg->n32timeStamp = *(pstruAsnRsiMsg->timeStamp);
        pstruWjRsiMsg->u8timeStamp_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjRsiMsg->u8timeStamp_Present = WJV3_ABSENT;
    }
    if ((WJV3_MAX_BYTE_ID_LEN != pstruAsnRsiMsg->id.size)
        || (NULL == (pstruAsnRsiMsg->id.buf)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rang:size = %d",
                 pstruAsnRsiMsg->id.size);
        return false;
    }
    /* 容易出错，请注意 */
    memcpy(pstruWjRsiMsg->u8Id, pstruAsnRsiMsg->id.buf, pstruAsnRsiMsg->id.size);
    #ifdef _CHECK_
    if ((WJV3_MAX_RSIID_SIZE < pstruAsnRsiMsg->rsiId)
        || (WJV3_MIN_RSIID_SIZE > pstruAsnRsiMsg->rsiId))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:rsiId = %d",
                 pstruAsnRsiMsg->rsiId);
        return false;
    }
    #endif
    pstruWjRsiMsg->n32rsiId = pstruAsnRsiMsg->rsiId;
    n32Ret = WJV3_AlertType_DeDec(&(pstruAsnRsiMsg->alertType), &(pstruWjRsiMsg->n32alertType));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_AlertType_DeDec is err");
        return false;
    }
    if (NULL != pstruAsnRsiMsg->description)
    {
        if ((0 == pstruAsnRsiMsg->description->size)
            || (WJV3_MAX_DESCRIPTION_LEN < pstruAsnRsiMsg->description->size)
            || (NULL == (pstruAsnRsiMsg->description->buf)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rang:size = %d",
                     pstruAsnRsiMsg->description->size);
            return false;
        }
        memcpy(pstruWjRsiMsg->u8description, pstruAsnRsiMsg->description->buf, pstruAsnRsiMsg->description->size);
        pstruWjRsiMsg->u16descriptionNum = (uint16_t)pstruAsnRsiMsg->description->size;
    }
    else
    {
        pstruWjRsiMsg->u16descriptionNum = 0;
    }
    if (NULL != pstruAsnRsiMsg->priority)
    {
        if ((0 == pstruAsnRsiMsg->priority->size)
            || (WJV3_MAX_PRIORITY_LEN < pstruAsnRsiMsg->priority->size)
            || (NULL == (pstruAsnRsiMsg->priority->buf)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rang:size = %d",
                     pstruAsnRsiMsg->priority->size);
            return false;
        }
        memcpy(pstruWjRsiMsg->u8priority, pstruAsnRsiMsg->priority->buf, pstruAsnRsiMsg->priority->size);
        pstruWjRsiMsg->u8priorityNum = pstruAsnRsiMsg->priority->size;
    }
    else
    {
        pstruWjRsiMsg->u8priorityNum = 0;
    }
    n32Ret = WJV3_Position3D_DfDec(&(pstruAsnRsiMsg->refPos), &(pstruWjRsiMsg->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_Position3D_DfDec is err");
        return false;
    }
    n32Ret = WJV3_PathPointList_DfDec(&(pstruAsnRsiMsg->alertPath), &(pstruWjRsiMsg->strualertPath));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PathPointList_DfDec is err");
        return false;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_RADIUS_SIZE < pstruAsnRsiMsg->alertRadius)
        || (WJV3_MIN_RADIUS_SIZE > pstruAsnRsiMsg->alertRadius))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:alertRadius = %d",
                 pstruAsnRsiMsg->alertRadius);
        return false;
    }
    #endif
    pstruWjRsiMsg->n32alertRadius = pstruAsnRsiMsg->alertRadius;
    return true;
}