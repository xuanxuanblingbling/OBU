/**
* @file         :wjv4_uper_Df.c
* @brief        :数据帧相关函数的实现
* @details      :主要实现数据帧结构的编码实现
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
#include "wjv4_uper_Df.h"
#include "wjv4_uper_com.h"
/**
* @brief     WJV4_AccelerationSet4Way_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_AccelerationSet4Way_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_AccelerationSet4Way *pstruWjAccelerationSet4Way = (WJV4_STRU_AccelerationSet4Way *)pvoidWjDf;
    AccelerationSet4Way_t *pstruAsnAccelerationSet4Way = (AccelerationSet4Way_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_ACCELERATION_SIZE < pstruWjAccelerationSet4Way->n32long) || (WJV4_MIN_ACCELERATION_SIZE > pstruWjAccelerationSet4Way->n32long))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjAccelerationSet4Way->n32long = %d",
                 pstruWjAccelerationSet4Way->n32long);
        return false;
    }
#endif
    pstruAsnAccelerationSet4Way->Long = pstruWjAccelerationSet4Way->n32long;
#ifdef _CHECK_
    if ((WJV4_MAX_ACCELERATION_SIZE < pstruWjAccelerationSet4Way->n32lat) || (WJV4_MIN_ACCELERATION_SIZE > pstruWjAccelerationSet4Way->n32lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjAccelerationSet4Way->n32lat = %d",
                 pstruWjAccelerationSet4Way->n32lat);
        return false;
    }
#endif
    pstruAsnAccelerationSet4Way->lat = pstruWjAccelerationSet4Way->n32lat;
#ifdef _CHECK_
    if ((WJV4_MAX_VERTICALACCELERATION_SIZE < pstruWjAccelerationSet4Way->n32vert) || (WJV4_MIN_VERTICALACCELERATION_SIZE > pstruWjAccelerationSet4Way->n32vert))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjAccelerationSet4Way->n32vert = %d",
                 pstruWjAccelerationSet4Way->n32vert);
        return false;
    }
#endif
    pstruAsnAccelerationSet4Way->vert = pstruWjAccelerationSet4Way->n32vert;
#ifdef _CHECK_
    if ((WJV4_MAX_YAWRATE_SIZE < pstruWjAccelerationSet4Way->n32yaw) || (WJV4_MIN_YAWRATE_SIZE > pstruWjAccelerationSet4Way->n32yaw))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjAccelerationSet4Way->n32yaw = %d",
                 pstruWjAccelerationSet4Way->n32yaw);
        return false;
    }
#endif
    pstruAsnAccelerationSet4Way->yaw = pstruWjAccelerationSet4Way->n32yaw;
    return true;
}
/**
* @brief     WJV4_AccelerationSet4Way_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_AccelerationSet4Way_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_AccelerationSet4Way *pstruWjAccelerationSet4Way = (WJV4_STRU_AccelerationSet4Way *)pvoidWjDf;
    AccelerationSet4Way_t *pstruAsnAccelerationSet4Way = (AccelerationSet4Way_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_ACCELERATION_SIZE < pstruAsnAccelerationSet4Way->Long) || (WJV4_MIN_ACCELERATION_SIZE > pstruAsnAccelerationSet4Way->Long))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnAccelerationSet4Way->Long = %d",
                 pstruAsnAccelerationSet4Way->Long);
        return false;
    }
#endif
    pstruWjAccelerationSet4Way->n32long = pstruAsnAccelerationSet4Way->Long;
#ifdef _CHECK_
    if ((WJV4_MAX_ACCELERATION_SIZE < pstruAsnAccelerationSet4Way->lat) || (WJV4_MIN_ACCELERATION_SIZE > pstruAsnAccelerationSet4Way->lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnAccelerationSet4Way->lat = %d",
                 pstruAsnAccelerationSet4Way->lat);
        return false;
    }
#endif
    pstruWjAccelerationSet4Way->n32lat = pstruAsnAccelerationSet4Way->lat;
#ifdef _CHECK_
    if ((WJV4_MAX_VERTICALACCELERATION_SIZE < pstruAsnAccelerationSet4Way->vert) || (WJV4_MIN_VERTICALACCELERATION_SIZE > pstruAsnAccelerationSet4Way->vert))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnAccelerationSet4Way->vert = %d",
                 pstruAsnAccelerationSet4Way->vert);
        return false;
    }
#endif
    pstruWjAccelerationSet4Way->n32vert = pstruAsnAccelerationSet4Way->vert;
#ifdef _CHECK_
    if ((WJV4_MAX_YAWRATE_SIZE < pstruAsnAccelerationSet4Way->yaw) || (WJV4_MIN_YAWRATE_SIZE > pstruAsnAccelerationSet4Way->yaw))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnAccelerationSet4Way->yaw = %d",
                 pstruAsnAccelerationSet4Way->yaw);
        return false;
    }
#endif
    pstruWjAccelerationSet4Way->n32yaw = pstruAsnAccelerationSet4Way->yaw;
    return true;
}
/**
* @brief     WJV4_BrakeSystemStatus_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_BrakeSystemStatus_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_BrakeSystemStatus *pstruWjBrakeSystemStatus = (WJV4_STRU_BrakeSystemStatus *)pvoidWjDf;
    BrakeSystemStatus_t *pstruAsnBrakeSystemStatus = (BrakeSystemStatus_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV4_PRESENT == pstruWjBrakeSystemStatus->u8brakePadelPresent)
    {
        pstruAsnBrakeSystemStatus->brakePadel = CALLOC(1, sizeof(BrakePedalStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->brakePadel)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnBrakeSystemStatus->brakePadel) = pstruWjBrakeSystemStatus->enumbrakePadel;
    }
    else
    {
        pstruAsnBrakeSystemStatus->brakePadel = NULL;
    }
    if (WJV4_PRESENT == pstruWjBrakeSystemStatus->u8wheelBrakesPresent)
    {
        pstruAsnBrakeSystemStatus->wheelBrakes = CALLOC(1, sizeof(BrakeAppliedStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->wheelBrakes)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_BrakeAppliedStatus_DeEnc(pstruAsnBrakeSystemStatus->wheelBrakes, &(pstruWjBrakeSystemStatus->strbitwheelBrakes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_BrakeAppliedStatus_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBrakeSystemStatus->wheelBrakes = NULL;
    }
    if (WJV4_PRESENT == pstruWjBrakeSystemStatus->u8tractionPresent)
    {
        pstruAsnBrakeSystemStatus->traction = CALLOC(1, sizeof(TractionControlStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->traction)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnBrakeSystemStatus->traction) = pstruWjBrakeSystemStatus->enumtraction;
    }
    else
    {
        pstruAsnBrakeSystemStatus->traction = NULL;
    }
    if (WJV4_PRESENT == pstruWjBrakeSystemStatus->u8absPresent)
    {
        pstruAsnBrakeSystemStatus->abs = CALLOC(1, sizeof(AntiLockBrakeStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->abs)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnBrakeSystemStatus->abs) = pstruWjBrakeSystemStatus->enumabs;
    }
    else
    {
        pstruAsnBrakeSystemStatus->abs = NULL;
    }
    if (WJV4_PRESENT == pstruWjBrakeSystemStatus->u8scsPresent)
    {
        pstruAsnBrakeSystemStatus->scs = CALLOC(1, sizeof(StabilityControlStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->scs)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnBrakeSystemStatus->scs) = pstruWjBrakeSystemStatus->enumscs;
    }
    else
    {
        pstruAsnBrakeSystemStatus->scs = NULL;
    }
    if (WJV4_PRESENT == pstruWjBrakeSystemStatus->u8brakeBoostPresent)
    {
        pstruAsnBrakeSystemStatus->brakeBoost = CALLOC(1, sizeof(BrakeBoostApplied_t));
        if (NULL == pstruAsnBrakeSystemStatus->brakeBoost)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnBrakeSystemStatus->brakeBoost) = pstruWjBrakeSystemStatus->enumbrakeBoost;
    }
    else
    {
        pstruAsnBrakeSystemStatus->brakeBoost = NULL;
    }
    if (WJV4_PRESENT == pstruWjBrakeSystemStatus->u8auxBrakesPresent)
    {
        pstruAsnBrakeSystemStatus->auxBrakes = CALLOC(1, sizeof(AuxiliaryBrakeStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->auxBrakes)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnBrakeSystemStatus->auxBrakes) = pstruWjBrakeSystemStatus->enumauxBrakes;
    }
    else
    {
        pstruAsnBrakeSystemStatus->auxBrakes = NULL;
    }
    return true;
}
/**
* @brief     WJV4_BrakeSystemStatus_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_BrakeSystemStatus_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_BrakeSystemStatus *pstruWjBrakeSystemStatus = (WJV4_STRU_BrakeSystemStatus *)pvoidWjDf;
    BrakeSystemStatus_t *pstruAsnBrakeSystemStatus = (BrakeSystemStatus_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnBrakeSystemStatus->brakePadel)
    {
        pstruWjBrakeSystemStatus->enumbrakePadel = *(pstruAsnBrakeSystemStatus->brakePadel);
        pstruWjBrakeSystemStatus->u8brakePadelPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8brakePadelPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->wheelBrakes)
    {
        n32Ret = WJV4_BrakeAppliedStatus_DeDec(pstruAsnBrakeSystemStatus->wheelBrakes, &(pstruWjBrakeSystemStatus->strbitwheelBrakes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_BrakeAppliedStatus_DeDec is err");
            return false;
        }
        pstruWjBrakeSystemStatus->u8wheelBrakesPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8wheelBrakesPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->traction)
    {
        pstruWjBrakeSystemStatus->enumtraction = *(pstruAsnBrakeSystemStatus->traction);
        pstruWjBrakeSystemStatus->u8tractionPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8tractionPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->abs)
    {
        pstruWjBrakeSystemStatus->enumabs = *(pstruAsnBrakeSystemStatus->abs);
        pstruWjBrakeSystemStatus->u8absPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8absPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->scs)
    {
        pstruWjBrakeSystemStatus->enumscs = *(pstruAsnBrakeSystemStatus->scs);
        pstruWjBrakeSystemStatus->u8scsPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8scsPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->brakeBoost)
    {
        pstruWjBrakeSystemStatus->enumbrakeBoost = *(pstruAsnBrakeSystemStatus->brakeBoost);
        pstruWjBrakeSystemStatus->u8brakeBoostPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8brakeBoostPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->auxBrakes)
    {
        pstruWjBrakeSystemStatus->enumauxBrakes = *(pstruAsnBrakeSystemStatus->auxBrakes);
        pstruWjBrakeSystemStatus->u8auxBrakesPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8auxBrakesPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_ConnectingLane_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_ConnectingLane_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ConnectingLane *pstruWjConnectingLane = (WJV4_STRU_ConnectingLane *)pvoidWjDf;
    ConnectingLane_t *pstruAsnConnectingLane = (ConnectingLane_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LANEID_SIZE < pstruWjConnectingLane->n32lane) || (WJV4_MIN_LANEID_SIZE > pstruWjConnectingLane->n32lane))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjConnectingLane->n32lane = %d",
                 pstruWjConnectingLane->n32lane);
        return false;
    }
#endif
    pstruAsnConnectingLane->lane = pstruWjConnectingLane->n32lane;
    if (WJV4_PRESENT == pstruWjConnectingLane->u8maneuverPresent)
    {
        pstruAsnConnectingLane->maneuver = CALLOC(1, sizeof(AllowedManeuvers_t));
        if (NULL == pstruAsnConnectingLane->maneuver)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_AllowedManeuvers_DeEnc(pstruAsnConnectingLane->maneuver, &(pstruWjConnectingLane->strbitmaneuver));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_AllowedManeuvers_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnConnectingLane->maneuver = NULL;
    }
    return true;
}
/**
* @brief     WJV4_ConnectingLane_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_ConnectingLane_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ConnectingLane *pstruWjConnectingLane = (WJV4_STRU_ConnectingLane *)pvoidWjDf;
    ConnectingLane_t *pstruAsnConnectingLane = (ConnectingLane_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LANEID_SIZE < pstruAsnConnectingLane->lane) || (WJV4_MIN_LANEID_SIZE > pstruAsnConnectingLane->lane))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnConnectingLane->lane = %d",
                 pstruAsnConnectingLane->lane);
        return false;
    }
#endif
    pstruWjConnectingLane->n32lane = pstruAsnConnectingLane->lane;
    if (NULL != pstruAsnConnectingLane->maneuver)
    {
        n32Ret = WJV4_AllowedManeuvers_DeDec(pstruAsnConnectingLane->maneuver, &(pstruWjConnectingLane->strbitmaneuver));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_AllowedManeuvers_DeDec is err");
            return false;
        }
        pstruWjConnectingLane->u8maneuverPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjConnectingLane->u8maneuverPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_Connection_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Connection_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Connection *pstruWjConnection = (WJV4_STRU_Connection *)pvoidWjDf;
    Connection_t *pstruAsnConnection = (Connection_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_NodeReferenceID_DfEnc(&(pstruAsnConnection->remoteIntersection), &(pstruWjConnection->struremoteIntersection));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjConnection->u8connectingLanePresent)
    {
        pstruAsnConnection->connectingLane = CALLOC(1, sizeof(struct ConnectingLane));
        if (NULL == pstruAsnConnection->connectingLane)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_ConnectingLane_DfEnc(pstruAsnConnection->connectingLane, &(pstruWjConnection->struconnectingLane));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ConnectingLane_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnConnection->connectingLane = NULL;
    }
    if (WJV4_PRESENT == pstruWjConnection->u8phaseIdPresent)
    {
        pstruAsnConnection->phaseId = CALLOC(1, sizeof(PhaseID_t));
        if (NULL == pstruAsnConnection->phaseId)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_PHASEID_SIZE < pstruWjConnection->n32phaseId) || (WJV4_MIN_PHASEID_SIZE > pstruWjConnection->n32phaseId))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjConnection->n32phaseId = %d",
                     pstruWjConnection->n32phaseId);
            return false;
        }
#endif
        *(pstruAsnConnection->phaseId) = pstruWjConnection->n32phaseId;
    }
    else
    {
        pstruAsnConnection->phaseId = NULL;
    }
    return true;
}
/**
* @brief     WJV4_Connection_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Connection_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Connection *pstruWjConnection = (WJV4_STRU_Connection *)pvoidWjDf;
    Connection_t *pstruAsnConnection = (Connection_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_NodeReferenceID_DfDec(&(pstruAsnConnection->remoteIntersection), &(pstruWjConnection->struremoteIntersection));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnConnection->connectingLane)
    {
        n32Ret = WJV4_ConnectingLane_DfDec(pstruAsnConnection->connectingLane, &(pstruWjConnection->struconnectingLane));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ConnectingLane_DfDec is err");
            return false;
        }
        pstruWjConnection->u8connectingLanePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjConnection->u8connectingLanePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnConnection->phaseId)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_PHASEID_SIZE < *(pstruAsnConnection->phaseId)) || (WJV4_MIN_PHASEID_SIZE > *(pstruAsnConnection->phaseId)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnConnection->phaseId) = %d",
                     *(pstruAsnConnection->phaseId));
            return false;
        }
#endif
        pstruWjConnection->n32phaseId = *(pstruAsnConnection->phaseId);
        pstruWjConnection->u8phaseIdPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjConnection->u8phaseIdPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_ConnectsToList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_ConnectsToList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ConnectsToList *pstruWjConnectsToList = (WJV4_STRU_ConnectsToList *)pvoidWjDf;
    ConnectsToList_t *pstruAsnConnectsToList = (ConnectsToList_t *)pvoidAsnDf;
    Connection_t *pstruConnection_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_CONNECTION_LEN < pstruWjConnectsToList->u8ConnectionNum) || (WJV4_MIN_LIST_CONNECTION_LEN > pstruWjConnectsToList->u8ConnectionNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjConnectsToList->u8ConnectionNum = %d",
                 pstruWjConnectsToList->u8ConnectionNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjConnectsToList->u8ConnectionNum; u32i++)
    {
        pstruConnection_node = CALLOC(1, sizeof(Connection_t));
        if (NULL == pstruConnection_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_Connection_DfEnc(pstruConnection_node, &(pstruWjConnectsToList->struConnection[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Connection_DfEnc is err");
            FREEMEM(pstruConnection_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnConnectsToList->list), pstruConnection_node);
    }
    return true;
}
/**
* @brief     WJV4_ConnectsToList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_ConnectsToList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ConnectsToList *pstruWjConnectsToList = (WJV4_STRU_ConnectsToList *)pvoidWjDf;
    ConnectsToList_t *pstruAsnConnectsToList = (ConnectsToList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_CONNECTION_LEN < pstruAsnConnectsToList->list.count) || (WJV4_MIN_LIST_CONNECTION_LEN > pstruAsnConnectsToList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnConnectsToList->list.count = %d",
                 pstruAsnConnectsToList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnConnectsToList->list.count; u32i++)
    {
        n32Ret = WJV4_Connection_DfDec(pstruAsnConnectsToList->list.array[u32i],
                                       &(pstruWjConnectsToList->struConnection[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Connection_DfDec is err");
            return false;
        }
    }
    pstruWjConnectsToList->u8ConnectionNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_DDateTime_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_DDateTime_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_DDateTime *pstruWjDDateTime = (WJV4_STRU_DDateTime *)pvoidWjDf;
    DDateTime_t *pstruAsnDDateTime = (DDateTime_t *)pvoidAsnDf;
    if (WJV4_PRESENT == pstruWjDDateTime->u8yearPresent)
    {
        pstruAsnDDateTime->year = CALLOC(1, sizeof(DYear_t));
        if (NULL == pstruAsnDDateTime->year)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_DYEAR_SIZE < pstruWjDDateTime->n32year) || (WJV4_MIN_DYEAR_SIZE > pstruWjDDateTime->n32year))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjDDateTime->n32year = %d",
                     pstruWjDDateTime->n32year);
            return false;
        }
#endif
        *(pstruAsnDDateTime->year) = pstruWjDDateTime->n32year;
    }
    else
    {
        pstruAsnDDateTime->year = NULL;
    }
    if (WJV4_PRESENT == pstruWjDDateTime->u8monthPresent)
    {
        pstruAsnDDateTime->month = CALLOC(1, sizeof(DMonth_t));
        if (NULL == pstruAsnDDateTime->month)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_DMONTH_SIZE < pstruWjDDateTime->n32month) || (WJV4_MIN_DMONTH_SIZE > pstruWjDDateTime->n32month))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjDDateTime->n32month = %d",
                     pstruWjDDateTime->n32month);
            return false;
        }
#endif
        *(pstruAsnDDateTime->month) = pstruWjDDateTime->n32month;
    }
    else
    {
        pstruAsnDDateTime->month = NULL;
    }
    if (WJV4_PRESENT == pstruWjDDateTime->u8dayPresent)
    {
        pstruAsnDDateTime->day = CALLOC(1, sizeof(DDay_t));
        if (NULL == pstruAsnDDateTime->day)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_DDAY_SIZE < pstruWjDDateTime->n32day) || (WJV4_MIN_DDAY_SIZE > pstruWjDDateTime->n32day))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjDDateTime->n32day = %d",
                     pstruWjDDateTime->n32day);
            return false;
        }
#endif
        *(pstruAsnDDateTime->day) = pstruWjDDateTime->n32day;
    }
    else
    {
        pstruAsnDDateTime->day = NULL;
    }
    if (WJV4_PRESENT == pstruWjDDateTime->u8hourPresent)
    {
        pstruAsnDDateTime->hour = CALLOC(1, sizeof(DHour_t));
        if (NULL == pstruAsnDDateTime->hour)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_DHOUR_SIZE < pstruWjDDateTime->n32hour) || (WJV4_MIN_DHOUR_SIZE > pstruWjDDateTime->n32hour))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjDDateTime->n32hour = %d",
                     pstruWjDDateTime->n32hour);
            return false;
        }
#endif
        *(pstruAsnDDateTime->hour) = pstruWjDDateTime->n32hour;
    }
    else
    {
        pstruAsnDDateTime->hour = NULL;
    }
    if (WJV4_PRESENT == pstruWjDDateTime->u8minutePresent)
    {
        pstruAsnDDateTime->minute = CALLOC(1, sizeof(DMinute_t));
        if (NULL == pstruAsnDDateTime->minute)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_DMINUTE_SIZE < pstruWjDDateTime->n32minute) || (WJV4_MIN_DMINUTE_SIZE > pstruWjDDateTime->n32minute))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjDDateTime->n32minute = %d",
                     pstruWjDDateTime->n32minute);
            return false;
        }
#endif
        *(pstruAsnDDateTime->minute) = pstruWjDDateTime->n32minute;
    }
    else
    {
        pstruAsnDDateTime->minute = NULL;
    }
    if (WJV4_PRESENT == pstruWjDDateTime->u8secondPresent)
    {
        pstruAsnDDateTime->second = CALLOC(1, sizeof(DSecond_t));
        if (NULL == pstruAsnDDateTime->second)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_DSECOND_SIZE < pstruWjDDateTime->n32second) || (WJV4_MIN_DSECOND_SIZE > pstruWjDDateTime->n32second))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjDDateTime->n32second = %d",
                     pstruWjDDateTime->n32second);
            return false;
        }
#endif
        *(pstruAsnDDateTime->second) = pstruWjDDateTime->n32second;
    }
    else
    {
        pstruAsnDDateTime->second = NULL;
    }
    if (WJV4_PRESENT == pstruWjDDateTime->u8offsetPresent)
    {
        pstruAsnDDateTime->offset = CALLOC(1, sizeof(DTimeOffset_t));
        if (NULL == pstruAsnDDateTime->offset)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_DTIMEOFFSET_SIZE < pstruWjDDateTime->n32offset) || (WJV4_MIN_DTIMEOFFSET_SIZE > pstruWjDDateTime->n32offset))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjDDateTime->n32offset = %d",
                     pstruWjDDateTime->n32offset);
            return false;
        }
#endif
        *(pstruAsnDDateTime->offset) = pstruWjDDateTime->n32offset;
    }
    else
    {
        pstruAsnDDateTime->offset = NULL;
    }
    return true;
}
/**
* @brief     WJV4_DDateTime_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_DDateTime_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_DDateTime *pstruWjDDateTime = (WJV4_STRU_DDateTime *)pvoidWjDf;
    DDateTime_t *pstruAsnDDateTime = (DDateTime_t *)pvoidAsnDf;

    if (NULL != pstruAsnDDateTime->year)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_DYEAR_SIZE < *(pstruAsnDDateTime->year)) || (WJV4_MIN_DYEAR_SIZE > *(pstruAsnDDateTime->year)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnDDateTime->year) = %d",
                     *(pstruAsnDDateTime->year));
            return false;
        }
#endif
        pstruWjDDateTime->n32year = *(pstruAsnDDateTime->year);
        pstruWjDDateTime->u8yearPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8yearPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnDDateTime->month)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_DMONTH_SIZE < *(pstruAsnDDateTime->month)) || (WJV4_MIN_DMONTH_SIZE > *(pstruAsnDDateTime->month)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnDDateTime->month) = %d",
                     *(pstruAsnDDateTime->month));
            return false;
        }
#endif
        pstruWjDDateTime->n32month = *(pstruAsnDDateTime->month);
        pstruWjDDateTime->u8monthPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8monthPresent = WJV4_ABSENT;
    }

    if (NULL != pstruAsnDDateTime->day)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_DDAY_SIZE < *(pstruAsnDDateTime->day)) || (WJV4_MIN_DDAY_SIZE > *(pstruAsnDDateTime->day)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnDDateTime->day) = %d",
                     *(pstruAsnDDateTime->day));
            return false;
        }
#endif
        pstruWjDDateTime->n32day = *(pstruAsnDDateTime->day);
        pstruWjDDateTime->u8dayPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8dayPresent = WJV4_ABSENT;
    }

    if (NULL != pstruAsnDDateTime->hour)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_DHOUR_SIZE < *(pstruAsnDDateTime->hour)) || (WJV4_MIN_DHOUR_SIZE > *(pstruAsnDDateTime->hour)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnDDateTime->hour) = %d",
                     *(pstruAsnDDateTime->hour));
            return false;
        }
#endif
        pstruWjDDateTime->n32hour = *(pstruAsnDDateTime->hour);
        pstruWjDDateTime->u8hourPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8hourPresent = WJV4_ABSENT;
    }

    if (NULL != pstruAsnDDateTime->minute)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_DMINUTE_SIZE < *(pstruAsnDDateTime->minute)) || (WJV4_MIN_DMINUTE_SIZE > *(pstruAsnDDateTime->minute)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnDDateTime->minute) = %d",
                     *(pstruAsnDDateTime->minute));
            return false;
        }
#endif
        pstruWjDDateTime->n32minute = *(pstruAsnDDateTime->minute);
        pstruWjDDateTime->u8minutePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8minutePresent = WJV4_ABSENT;
    }

    if (NULL != pstruAsnDDateTime->second)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_DSECOND_SIZE < *(pstruAsnDDateTime->second)) || (WJV4_MIN_DSECOND_SIZE > *(pstruAsnDDateTime->second)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnDDateTime->second) = %d",
                     *(pstruAsnDDateTime->second));
            return false;
        }
#endif
        pstruWjDDateTime->n32second = *(pstruAsnDDateTime->second);
        pstruWjDDateTime->u8secondPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8secondPresent = WJV4_ABSENT;
    }

    if (NULL != pstruAsnDDateTime->offset)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_DTIMEOFFSET_SIZE < *(pstruAsnDDateTime->offset)) || (WJV4_MIN_DTIMEOFFSET_SIZE > *(pstruAsnDDateTime->offset)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnDDateTime->offset) = %d",
                     *(pstruAsnDDateTime->offset));
            return false;
        }
#endif
        pstruWjDDateTime->n32offset = *(pstruAsnDDateTime->offset);
        pstruWjDDateTime->u8offsetPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8offsetPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_Description_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Description_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Description *pstruWjDescription = (WJV4_STRU_Description *)pvoidWjDf;
    Description_t *pstruAsnDescription = (Description_t *)pvoidAsnDf;
    if (WJV4_DescriptiontextString == pstruWjDescription->enumDescriptionStringChoice)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_IA5_STRING_LEN < pstruWjDescription->u32textNum) || (WJV4_MIN_IA5_STRING_LEN > pstruWjDescription->u32textNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjDescription->u32textNum = %d",
                     pstruWjDescription->u32textNum);
            return false;
        }
#endif
        pstruAsnDescription->choice.textString.buf = CALLOC(1, pstruWjDescription->u32textNum);
        if (NULL == pstruAsnDescription->choice.textString.buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        memcpy(pstruAsnDescription->choice.textString.buf, pstruWjDescription->u.u8textString, pstruWjDescription->u32textNum);
        pstruAsnDescription->choice.textString.size = pstruWjDescription->u32textNum;
        pstruAsnDescription->present = Description_PR_textString;
    }
    else if (WJV4_DescriptiontextGB2312 == pstruWjDescription->enumDescriptionStringChoice)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_OCT_STRING_LEN < pstruWjDescription->u32textNum) || (WJV4_MIN_OCT_STRING_LEN > pstruWjDescription->u32textNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjDescription->u32textNum = %d",
                     pstruWjDescription->u32textNum);
            return false;
        }
#endif
        pstruAsnDescription->choice.textGB2312.buf = CALLOC(2, pstruWjDescription->u32textNum);
        if (NULL == pstruAsnDescription->choice.textGB2312.buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        memcpy(pstruAsnDescription->choice.textGB2312.buf, pstruWjDescription->u.u16textGB2312, pstruWjDescription->u32textNum * 2);
        pstruAsnDescription->choice.textGB2312.size = pstruWjDescription->u32textNum * 2;
        pstruAsnDescription->present = Description_PR_textGB2312;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "type is err pstruWjDescription->enumDescriptionStringChoice = %d",
                 pstruWjDescription->enumDescriptionStringChoice);
        return false;
    }
    return true;
}
/**
* @brief     WJV4_Description_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Description_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Description *pstruWjDescription = (WJV4_STRU_Description *)pvoidWjDf;
    Description_t *pstruAsnDescription = (Description_t *)pvoidAsnDf;
    if (Description_PR_textString == pstruAsnDescription->present)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_IA5_STRING_LEN < pstruAsnDescription->choice.textString.size) || (WJV4_MIN_IA5_STRING_LEN > pstruAsnDescription->choice.textString.size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnDescription->choice.textString.size = %d",
                     pstruAsnDescription->choice.textString.size);
            return false;
        }
#endif
        pstruWjDescription->u32textNum = pstruAsnDescription->choice.textString.size;
        memcpy(pstruWjDescription->u.u8textString, pstruAsnDescription->choice.textString.buf, pstruAsnDescription->choice.textString.size);
        pstruWjDescription->enumDescriptionStringChoice = WJV4_DescriptiontextString;
    }
    else if (Description_PR_textGB2312 == pstruAsnDescription->present)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_OCT_STRING_LEN < pstruAsnDescription->choice.textGB2312.size / 2) || (WJV4_MIN_OCT_STRING_LEN > pstruAsnDescription->choice.textGB2312.size / 2))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnDescription->choice.textGB2312.size / 2 = %d",
                     pstruAsnDescription->choice.textGB2312.size / 2);
            return false;
        }
#endif
        pstruWjDescription->u32textNum = pstruAsnDescription->choice.textGB2312.size / 2;
        memcpy(pstruWjDescription->u.u16textGB2312, pstruAsnDescription->choice.textGB2312.buf, pstruAsnDescription->choice.textString.size);
        pstruWjDescription->enumDescriptionStringChoice = WJV4_DescriptiontextGB2312;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "type is err pstruAsnDescription->present = %d",
                 pstruAsnDescription->present);
        return false;
    }
    return true;
}
/**
* @brief     WJV4_FullPositionVector_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_FullPositionVector_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_FullPositionVector *pstruWjFullPositionVector = (WJV4_STRU_FullPositionVector *)pvoidWjDf;
    FullPositionVector_t *pstruAsnFullPositionVector = (FullPositionVector_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV4_PRESENT == pstruWjFullPositionVector->u8utcTimePresent)
    {
        pstruAsnFullPositionVector->utcTime = CALLOC(1, sizeof(struct DDateTime));
        if (NULL == pstruAsnFullPositionVector->utcTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_DDateTime_DfEnc(pstruAsnFullPositionVector->utcTime, &(pstruWjFullPositionVector->struutcTime));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_DDateTime_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnFullPositionVector->utcTime = NULL;
    }
    n32Ret = WJV4_Position3D_DfEnc(&(pstruAsnFullPositionVector->pos), &(pstruWjFullPositionVector->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_Position3D_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjFullPositionVector->u8headingPresent)
    {
        pstruAsnFullPositionVector->heading = CALLOC(1, sizeof(Heading_t));
        if (NULL == pstruAsnFullPositionVector->heading)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_HEADING_SIZE < pstruWjFullPositionVector->n32heading) || (WJV4_MIN_HEADING_SIZE > pstruWjFullPositionVector->n32heading))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjFullPositionVector->n32heading = %d",
                     pstruWjFullPositionVector->n32heading);
            return false;
        }
#endif
        *(pstruAsnFullPositionVector->heading) = pstruWjFullPositionVector->n32heading;
    }
    else
    {
        pstruAsnFullPositionVector->heading = NULL;
    }
    if (WJV4_PRESENT == pstruWjFullPositionVector->u8transmissionPresent)
    {
        pstruAsnFullPositionVector->transmission = CALLOC(1, sizeof(TransmissionState_t));
        if (NULL == pstruAsnFullPositionVector->transmission)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnFullPositionVector->transmission) = pstruWjFullPositionVector->enumtransmission;
    }
    else
    {
        pstruAsnFullPositionVector->transmission = NULL;
    }
    if (WJV4_PRESENT == pstruWjFullPositionVector->u8speedPresent)
    {
        pstruAsnFullPositionVector->speed = CALLOC(1, sizeof(Speed_t));
        if (NULL == pstruAsnFullPositionVector->speed)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_SPEED_SIZE < pstruWjFullPositionVector->n32speed) || (WJV4_MIN_SPEED_SIZE > pstruWjFullPositionVector->n32speed))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjFullPositionVector->n32speed = %d",
                     pstruWjFullPositionVector->n32speed);
            return false;
        }
#endif
        *(pstruAsnFullPositionVector->speed) = pstruWjFullPositionVector->n32speed;
    }
    else
    {
        pstruAsnFullPositionVector->speed = NULL;
    }
    if (WJV4_PRESENT == pstruWjFullPositionVector->u8posAccuracyPresent)
    {
        pstruAsnFullPositionVector->posAccuracy = CALLOC(1, sizeof(struct PositionalAccuracy));
        if (NULL == pstruAsnFullPositionVector->posAccuracy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_PositionalAccuracy_DfEnc(pstruAsnFullPositionVector->posAccuracy, &(pstruWjFullPositionVector->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionalAccuracy_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnFullPositionVector->posAccuracy = NULL;
    }
    if (WJV4_PRESENT == pstruWjFullPositionVector->u8posConficencePresent)
    {
        pstruAsnFullPositionVector->posConficence = CALLOC(1, sizeof(struct PositionConfidenceSet));
        if (NULL == pstruAsnFullPositionVector->posConficence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_PositionConfidenceSet_DfEnc(pstruAsnFullPositionVector->posConficence, &(pstruWjFullPositionVector->struposConficence));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionConfidenceSet_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnFullPositionVector->posConficence = NULL;
    }
    if (WJV4_PRESENT == pstruWjFullPositionVector->u8timeConfidencePresent)
    {
        pstruAsnFullPositionVector->timeConfidence = CALLOC(1, sizeof(TimeConfidence_t));
        if (NULL == pstruAsnFullPositionVector->timeConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnFullPositionVector->timeConfidence) = pstruWjFullPositionVector->enumtimeConfidence;
    }
    else
    {
        pstruAsnFullPositionVector->timeConfidence = NULL;
    }
    if (WJV4_PRESENT == pstruWjFullPositionVector->u8motionCfdPresent)
    {
        pstruAsnFullPositionVector->motionCfd = CALLOC(1, sizeof(struct MotionConfidenceSet));
        if (NULL == pstruAsnFullPositionVector->motionCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_MotionConfidenceSet_DfEnc(pstruAsnFullPositionVector->motionCfd, &(pstruWjFullPositionVector->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_MotionConfidenceSet_DfEnc. is err");
            return false;
        }
    }
    else
    {
        pstruAsnFullPositionVector->motionCfd = NULL;
    }
    return true;
}
/**
* @brief     WJV4_FullPositionVector_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_FullPositionVector_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_FullPositionVector *pstruWjFullPositionVector = (WJV4_STRU_FullPositionVector *)pvoidWjDf;
    FullPositionVector_t *pstruAsnFullPositionVector = (FullPositionVector_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnFullPositionVector->utcTime)
    {
        n32Ret = WJV4_DDateTime_DfDec(pstruAsnFullPositionVector->utcTime, &(pstruWjFullPositionVector->struutcTime));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_DDateTime_DfDec. is err");
            return false;
        }
        pstruWjFullPositionVector->u8utcTimePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjFullPositionVector->u8utcTimePresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_Position3D_DfDec(&(pstruAsnFullPositionVector->pos), &(pstruWjFullPositionVector->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_Position3D_DfDec. is err");
        return false;
    }
    if (NULL != pstruAsnFullPositionVector->heading)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_HEADING_SIZE < *(pstruAsnFullPositionVector->heading)) || (WJV4_MIN_HEADING_SIZE > *(pstruAsnFullPositionVector->heading)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjFullPositionVector->n32heading = %d",
                     pstruWjFullPositionVector->n32heading);
            return false;
        }
#endif
        pstruWjFullPositionVector->n32heading = *(pstruAsnFullPositionVector->heading);
        pstruWjFullPositionVector->u8headingPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjFullPositionVector->u8headingPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnFullPositionVector->transmission)
    {
        pstruWjFullPositionVector->enumtransmission = *(pstruAsnFullPositionVector->transmission);
        pstruWjFullPositionVector->u8transmissionPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjFullPositionVector->u8transmissionPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnFullPositionVector->speed)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_SPEED_SIZE < *(pstruAsnFullPositionVector->speed)) || (WJV4_MIN_SPEED_SIZE > *(pstruAsnFullPositionVector->speed)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjFullPositionVector->n32speed = %d",
                     pstruWjFullPositionVector->n32speed);
            return false;
        }
#endif
        pstruWjFullPositionVector->n32speed = *(pstruAsnFullPositionVector->speed);
        pstruWjFullPositionVector->u8speedPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjFullPositionVector->u8speedPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnFullPositionVector->posAccuracy)
    {
        n32Ret = WJV4_PositionalAccuracy_DfDec(pstruAsnFullPositionVector->posAccuracy, &(pstruWjFullPositionVector->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionalAccuracy_DfDec. is err");
            return false;
        }
        pstruWjFullPositionVector->u8posAccuracyPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjFullPositionVector->u8posAccuracyPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnFullPositionVector->posConficence)
    {
        n32Ret = WJV4_PositionConfidenceSet_DfDec(pstruAsnFullPositionVector->posConficence, &(pstruWjFullPositionVector->struposConficence));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionConfidenceSet_DfDec. is err");
            return false;
        }
        pstruWjFullPositionVector->u8posConficencePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjFullPositionVector->u8posConficencePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnFullPositionVector->timeConfidence)
    {
        pstruWjFullPositionVector->enumtimeConfidence = *(pstruAsnFullPositionVector->timeConfidence);
        pstruWjFullPositionVector->u8timeConfidencePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjFullPositionVector->u8timeConfidencePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnFullPositionVector->motionCfd)
    {
        n32Ret = WJV4_MotionConfidenceSet_DfDec(pstruAsnFullPositionVector->motionCfd, &(pstruWjFullPositionVector->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_MotionConfidenceSet_DfDec. is err");
            return false;
        }
        pstruWjFullPositionVector->u8motionCfdPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjFullPositionVector->u8motionCfdPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_IntersectionState_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_IntersectionState_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_IntersectionState *pstruWjIntersectionState = (WJV4_STRU_IntersectionState *)pvoidWjDf;
    IntersectionState_t *pstruAsnIntersectionState = (IntersectionState_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_NodeReferenceID_DfEnc(&(pstruAsnIntersectionState->intersectionId), &(pstruWjIntersectionState->struintersectionId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfEnc is err");
        return false;
    }
    n32Ret = WJV4_IntersectionStatusObject_DeEnc(&(pstruAsnIntersectionState->status), &(pstruWjIntersectionState->strbitstatus));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_IntersectionStatusObject_DeEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjIntersectionState->u8moyPresent)
    {
        pstruAsnIntersectionState->moy = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnIntersectionState->moy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjIntersectionState->n32moy) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjIntersectionState->n32moy))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjIntersectionState->n32moy = %d",
                     pstruWjIntersectionState->n32moy);
            return false;
        }
#endif
        *(pstruAsnIntersectionState->moy) = pstruWjIntersectionState->n32moy;
    }
    else
    {
        pstruAsnIntersectionState->moy = NULL;
    }
    if (WJV4_PRESENT == pstruWjIntersectionState->u8timeStampPresent)
    {
        pstruAsnIntersectionState->timeStamp = CALLOC(1, sizeof(DSecond_t));
        if (NULL == pstruAsnIntersectionState->timeStamp)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_DSECOND_SIZE < pstruWjIntersectionState->n32timeStamp) || (WJV4_MIN_DSECOND_SIZE > pstruWjIntersectionState->n32timeStamp))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjIntersectionState->n32timeStamp = %d",
                     pstruWjIntersectionState->n32timeStamp);
            return false;
        }
#endif
        *(pstruAsnIntersectionState->timeStamp) = pstruWjIntersectionState->n32timeStamp;
    }
    else
    {
        pstruAsnIntersectionState->timeStamp = NULL;
    }
    if (WJV4_PRESENT == pstruWjIntersectionState->u8timeConfidencePresent)
    {
        pstruAsnIntersectionState->timeConfidence = CALLOC(1, sizeof(TimeConfidence_t));
        if (NULL == pstruAsnIntersectionState->timeConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnIntersectionState->timeConfidence) = pstruWjIntersectionState->enumtimeConfidence;
    }
    else
    {
        pstruAsnIntersectionState->timeConfidence = NULL;
    }
    n32Ret = WJV4_PhaseList_DfEnc(&(pstruAsnIntersectionState->phases), &(pstruWjIntersectionState->struphases));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PhaseList_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_IntersectionState_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_IntersectionState_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_IntersectionState *pstruWjIntersectionState = (WJV4_STRU_IntersectionState *)pvoidWjDf;
    IntersectionState_t *pstruAsnIntersectionState = (IntersectionState_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_NodeReferenceID_DfDec(&(pstruAsnIntersectionState->intersectionId), &(pstruWjIntersectionState->struintersectionId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfDec. is err");
        return false;
    }
    n32Ret = WJV4_IntersectionStatusObject_DeDec(&(pstruAsnIntersectionState->status), &(pstruWjIntersectionState->strbitstatus));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_IntersectionStatusObject_DeDec. is err");
        return false;
    }
    if (NULL != pstruAsnIntersectionState->moy)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnIntersectionState->moy)) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnIntersectionState->moy)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjIntersectionState->n32moy = %d",
                     pstruWjIntersectionState->n32moy);
            return false;
        }
#endif
        pstruWjIntersectionState->n32moy = *(pstruAsnIntersectionState->moy);
        pstruWjIntersectionState->u8moyPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjIntersectionState->u8moyPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnIntersectionState->timeStamp)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_DSECOND_SIZE < *(pstruAsnIntersectionState->timeStamp)) || (WJV4_MIN_DSECOND_SIZE > *(pstruAsnIntersectionState->timeStamp)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjIntersectionState->n32timeStamp = %d",
                     pstruWjIntersectionState->n32timeStamp);
            return false;
        }
#endif
        pstruWjIntersectionState->n32timeStamp = *(pstruAsnIntersectionState->timeStamp);
        pstruWjIntersectionState->u8timeStampPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjIntersectionState->u8timeStampPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnIntersectionState->timeConfidence)
    {
        pstruWjIntersectionState->enumtimeConfidence = *(pstruAsnIntersectionState->timeConfidence);
        pstruWjIntersectionState->u8timeConfidencePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjIntersectionState->u8timeConfidencePresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_PhaseList_DfDec(&(pstruAsnIntersectionState->phases), &(pstruWjIntersectionState->struphases));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PhaseList_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_IntersectionStateList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_IntersectionStateList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_IntersectionStateList *pstruWjIntersectionStateList = (WJV4_STRU_IntersectionStateList *)pvoidWjDf;
    IntersectionStateList_t *pstruAsnIntersectionStateList = (IntersectionStateList_t *)pvoidAsnDf;
    IntersectionState_t *pstruIntersectionState_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_INTERSECTIONSTATE_LEN < pstruWjIntersectionStateList->u8IntersectionStateNum) || (WJV4_MIN_LIST_INTERSECTIONSTATE_LEN > pstruWjIntersectionStateList->u8IntersectionStateNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjIntersectionStateList->u8IntersectionStateNum = %d",
                 pstruWjIntersectionStateList->u8IntersectionStateNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjIntersectionStateList->u8IntersectionStateNum; u32i++)
    {
        pstruIntersectionState_node = CALLOC(1, sizeof(IntersectionState_t));
        if (NULL == pstruIntersectionState_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_IntersectionState_DfEnc(pstruIntersectionState_node, &(pstruWjIntersectionStateList->struIntersectionState[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_IntersectionState_DfEnc is err");
            FREEMEM(pstruIntersectionState_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnIntersectionStateList->list), pstruIntersectionState_node);
    }
    return true;
}
/**
* @brief     WJV4_IntersectionStateList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_IntersectionStateList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_IntersectionStateList *pstruWjIntersectionStateList = (WJV4_STRU_IntersectionStateList *)pvoidWjDf;
    IntersectionStateList_t *pstruAsnIntersectionStateList = (IntersectionStateList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_INTERSECTIONSTATE_LEN < pstruAsnIntersectionStateList->list.count) || (WJV4_MIN_LIST_INTERSECTIONSTATE_LEN > pstruAsnIntersectionStateList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnIntersectionStateList->list.count = %d",
                 pstruAsnIntersectionStateList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnIntersectionStateList->list.count; u32i++)
    {
        n32Ret = WJV4_IntersectionState_DfDec(pstruAsnIntersectionStateList->list.array[u32i],
                                              &(pstruWjIntersectionStateList->struIntersectionState[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_IntersectionState_DfDec is err");
            return false;
        }
    }
    pstruWjIntersectionStateList->u8IntersectionStateNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_Lane_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Lane_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Lane *pstruWjLane = (WJV4_STRU_Lane *)pvoidWjDf;
    Lane_t *pstruAsnLane = (Lane_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LANEID_SIZE < pstruWjLane->n32laneID) || (WJV4_MIN_LANEID_SIZE > pstruWjLane->n32laneID))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjLane->n32laneID = %d",
                 pstruWjLane->n32laneID);
        return false;
    }
#endif
    pstruAsnLane->laneID = pstruWjLane->n32laneID;
    if (WJV4_PRESENT == pstruWjLane->u8laneWidthPresent)
    {
        pstruAsnLane->laneWidth = CALLOC(1, sizeof(LaneWidth_t));
        if (NULL == pstruAsnLane->laneWidth)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_LANEWIDTH_SIZE < pstruWjLane->n32laneWidth) || (WJV4_MIN_LANEWIDTH_SIZE > pstruWjLane->n32laneWidth))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjLane->n32laneWidth = %d",
                     pstruWjLane->n32laneWidth);
            return false;
        }
#endif
        *(pstruAsnLane->laneWidth) = pstruWjLane->n32laneWidth;
    }
    else
    {
        pstruAsnLane->laneWidth = NULL;
    }
    if (WJV4_PRESENT == pstruWjLane->u8laneAttributesPresent)
    {
        pstruAsnLane->laneAttributes = CALLOC(1, sizeof(struct LaneAttributes));
        if (NULL == pstruAsnLane->laneAttributes)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_LaneAttributes_DfEnc(pstruAsnLane->laneAttributes, &(pstruWjLane->strulaneAttributes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributes_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLane->laneAttributes = NULL;
    }
    if (WJV4_PRESENT == pstruWjLane->u8maneuversPresent)
    {
        pstruAsnLane->maneuvers = CALLOC(1, sizeof(AllowedManeuvers_t));
        if (NULL == pstruAsnLane->maneuvers)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_AllowedManeuvers_DeEnc(pstruAsnLane->maneuvers, &(pstruWjLane->strbitmaneuvers));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_AllowedManeuvers_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLane->maneuvers = NULL;
    }
    if (WJV4_PRESENT == pstruWjLane->u8connectsToPresent)
    {
        pstruAsnLane->connectsTo = CALLOC(1, sizeof(struct ConnectsToList));
        if (NULL == pstruAsnLane->connectsTo)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_ConnectsToList_DfEnc(pstruAsnLane->connectsTo, &(pstruWjLane->struConnectsToList));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ConnectsToList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLane->connectsTo = NULL;
    }
    if (WJV4_PRESENT == pstruWjLane->u8speedLimitsPresent)
    {
        pstruAsnLane->speedLimits = CALLOC(1, sizeof(struct SpeedLimitList));
        if (NULL == pstruAsnLane->speedLimits)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_SpeedLimitList_DfEnc(pstruAsnLane->speedLimits, &(pstruWjLane->struspeedLimits));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_SpeedLimitList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLane->speedLimits = NULL;
    }

    if (WJV4_PRESENT == pstruWjLane->u8pointsPresent)
    {
        pstruAsnLane->points = CALLOC(1, sizeof(struct PointList));
        if (NULL == pstruAsnLane->points)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_PointList_DfEnc(pstruAsnLane->points, &(pstruWjLane->strupoints));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PointList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLane->points = NULL;
    }
    return true;
}
/**
* @brief     WJV4_Lane_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Lane_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Lane *pstruWjLane = (WJV4_STRU_Lane *)pvoidWjDf;
    Lane_t *pstruAsnLane = (Lane_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LANEID_SIZE < pstruAsnLane->laneID) || (WJV4_MIN_LANEID_SIZE > pstruAsnLane->laneID))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnLane->laneID = %d",
                 pstruAsnLane->laneID);
        return false;
    }
#endif
    pstruWjLane->n32laneID = pstruAsnLane->laneID;
    if (NULL != pstruAsnLane->laneWidth)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_LANEWIDTH_SIZE < *(pstruAsnLane->laneWidth)) || (WJV4_MIN_LANEWIDTH_SIZE > *(pstruAsnLane->laneWidth)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnLane->laneWidth) = %d",
                     *(pstruAsnLane->laneWidth));
            return false;
        }
#endif
        pstruWjLane->n32laneWidth = *(pstruAsnLane->laneWidth);
        pstruWjLane->u8laneWidthPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLane->u8laneWidthPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnLane->laneAttributes)
    {
        n32Ret = WJV4_LaneAttributes_DfDec(pstruAsnLane->laneAttributes, &(pstruWjLane->strulaneAttributes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributes_DfDec is err");
            return false;
        }
        pstruWjLane->u8laneAttributesPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLane->u8laneAttributesPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnLane->maneuvers)
    {
        n32Ret = WJV4_AllowedManeuvers_DeDec(pstruAsnLane->maneuvers, &(pstruWjLane->strbitmaneuvers));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_AllowedManeuvers_DeDec is err");
            return false;
        }
        pstruWjLane->u8maneuversPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLane->u8maneuversPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnLane->connectsTo)
    {
        n32Ret = WJV4_ConnectsToList_DfDec(pstruAsnLane->connectsTo, &(pstruWjLane->struConnectsToList));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ConnectsToList_DfDec is err");
            return false;
        }
        pstruWjLane->u8connectsToPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLane->u8connectsToPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnLane->speedLimits)
    {
        n32Ret = WJV4_SpeedLimitList_DfDec(pstruAsnLane->speedLimits, &(pstruWjLane->struspeedLimits));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_SpeedLimitList_DfDec is err");
            return false;
        }
        pstruWjLane->u8speedLimitsPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLane->u8speedLimitsPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnLane->points)
    {
        n32Ret = WJV4_PointList_DfDec(pstruAsnLane->points, &(pstruWjLane->strupoints));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PointList_DfDec is err");
            return false;
        }
        pstruWjLane->u8pointsPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLane->u8pointsPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_LaneAttributes_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_LaneAttributes_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_LaneAttributes *pstruWjLaneAttributes = (WJV4_STRU_LaneAttributes *)pvoidWjDf;
    LaneAttributes_t *pstruAsnLaneAttributes = (LaneAttributes_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV4_PRESENT == pstruWjLaneAttributes->u8shareWithPresent)
    {
        pstruAsnLaneAttributes->shareWith = CALLOC(1, sizeof(LaneSharing_t));
        if (NULL == pstruAsnLaneAttributes->shareWith)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_LaneSharing_DeEnc(pstruAsnLaneAttributes->shareWith, &(pstruWjLaneAttributes->strbitshareWith));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneSharing_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLaneAttributes->shareWith = NULL;
    }
    n32Ret = WJV4_LaneTypeAttributes_DfEnc(&(pstruAsnLaneAttributes->laneType), &(pstruWjLaneAttributes->strulaneType));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_LaneTypeAttributes_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_LaneAttributes_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_LaneAttributes_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_LaneAttributes *pstruWjLaneAttributes = (WJV4_STRU_LaneAttributes *)pvoidWjDf;
    LaneAttributes_t *pstruAsnLaneAttributes = (LaneAttributes_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnLaneAttributes->shareWith)
    {
        n32Ret = WJV4_LaneSharing_DeDec(pstruAsnLaneAttributes->shareWith, &(pstruWjLaneAttributes->strbitshareWith));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneSharing_DeDec is err");
            return false;
        }
        pstruWjLaneAttributes->u8shareWithPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLaneAttributes->u8shareWithPresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_LaneTypeAttributes_DfDec(&(pstruAsnLaneAttributes->laneType), &(pstruWjLaneAttributes->strulaneType));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_LaneTypeAttributes_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_LaneList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_LaneList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_LaneList *pstruWjLaneList = (WJV4_STRU_LaneList *)pvoidWjDf;
    LaneList_t *pstruAsnLaneList = (LaneList_t *)pvoidAsnDf;
    Lane_t *pstruLane_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_LANE_LEN < pstruWjLaneList->u8LaneNum) || (WJV4_MIN_LIST_LANE_LEN > pstruWjLaneList->u8LaneNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjLaneList->u8LaneNum = %d",
                 pstruWjLaneList->u8LaneNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjLaneList->u8LaneNum; u32i++)
    {
        pstruLane_node = CALLOC(1, sizeof(Lane_t));
        if (NULL == pstruLane_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_Lane_DfEnc(pstruLane_node, &(pstruWjLaneList->struLane[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Lane_DfEnc is err");
            FREEMEM(pstruLane_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnLaneList->list), pstruLane_node);
    }
    return true;
}
/**
* @brief     WJV4_LaneList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_LaneList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_LaneList *pstruWjLaneList = (WJV4_STRU_LaneList *)pvoidWjDf;
    LaneList_t *pstruAsnLaneList = (LaneList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_LANE_LEN < pstruAsnLaneList->list.count) || (WJV4_MIN_LIST_LANE_LEN > pstruAsnLaneList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnLaneList->list.count = %d",
                 pstruAsnLaneList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnLaneList->list.count; u32i++)
    {
        n32Ret = WJV4_Lane_DfDec(pstruAsnLaneList->list.array[u32i],
                                 &(pstruWjLaneList->struLane[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Lane_DfDec is err");
            return false;
        }
    }
    pstruWjLaneList->u8LaneNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_LaneTypeAttributes_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_LaneTypeAttributes_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_LaneTypeAttributes *pstruWjLaneTypeAttributes = (WJV4_STRU_LaneTypeAttributes *)pvoidWjDf;
    LaneTypeAttributes_t *pstruAsnLaneTypeAttributes = (LaneTypeAttributes_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV4_LaneAttributesVehicle == pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice)
    {
        n32Ret = WJV4_LaneAttributesVehicle_DeEnc(&(pstruAsnLaneTypeAttributes->choice.vehicle), &(pstruWjLaneTypeAttributes->u.strbitvehicle));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesVehicle_DeEnc is err");
            return false;
        }
        pstruAsnLaneTypeAttributes->present = LaneTypeAttributes_PR_vehicle;
    }
    else if (WJV4_LaneAttributesCrosswalk == pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice)
    {
        n32Ret = WJV4_LaneAttributesCrosswalk_DeEnc(&(pstruAsnLaneTypeAttributes->choice.crosswalk), &(pstruWjLaneTypeAttributes->u.strbitcrosswalk));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesCrosswalk_DeEnc is err");
            return false;
        }
        pstruAsnLaneTypeAttributes->present = LaneTypeAttributes_PR_crosswalk;
    }
    else if (WJV4_LaneAttributesBike == pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice)
    {
        n32Ret = WJV4_LaneAttributesBike_DeEnc(&(pstruAsnLaneTypeAttributes->choice.bikeLane), &(pstruWjLaneTypeAttributes->u.strbitbikeLane));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesBike_DeEnc is err");
            return false;
        }
        pstruAsnLaneTypeAttributes->present = LaneTypeAttributes_PR_bikeLane;
    }
    else if (WJV4_LaneAttributesSidewalk == pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice)
    {
        n32Ret = WJV4_LaneAttributesSidewalk_DeEnc(&(pstruAsnLaneTypeAttributes->choice.sidewalk), &(pstruWjLaneTypeAttributes->u.strbitsidewalk));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesSidewalk_DeEnc is err");
            return false;
        }
        pstruAsnLaneTypeAttributes->present = LaneTypeAttributes_PR_sidewalk;
    }
    else if (WJV4_LaneAttributesBarrier == pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice)
    {
        n32Ret = WJV4_LaneAttributesBarrier_DeEnc(&(pstruAsnLaneTypeAttributes->choice.median), &(pstruWjLaneTypeAttributes->u.strbitmedian));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesBarrier_DeEnc is err");
            return false;
        }
        pstruAsnLaneTypeAttributes->present = LaneTypeAttributes_PR_median;
    }
    else if (WJV4_LaneAttributesStriping == pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice)
    {
        n32Ret = WJV4_LaneAttributesStriping_DeEnc(&(pstruAsnLaneTypeAttributes->choice.striping), &(pstruWjLaneTypeAttributes->u.strbitstriping));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesStriping_DeEnc is err");
            return false;
        }
        pstruAsnLaneTypeAttributes->present = LaneTypeAttributes_PR_striping;
    }
    else if (WJV4_LaneAttributesTrackedVehicle == pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice)
    {
        n32Ret = WJV4_LaneAttributesTrackedVehicle_DeEnc(&(pstruAsnLaneTypeAttributes->choice.trackedVehicle), &(pstruWjLaneTypeAttributes->u.strbittrackedVehicle));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesTrackedVehicle_DeEnc is err");
            return false;
        }
        pstruAsnLaneTypeAttributes->present = LaneTypeAttributes_PR_trackedVehicle;
    }
    else if (WJV4_LaneAttributesParking == pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice)
    {
        n32Ret = WJV4_LaneAttributesParking_DeEnc(&(pstruAsnLaneTypeAttributes->choice.parking), &(pstruWjLaneTypeAttributes->u.strbitparking));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesParking_DeEnc is err");
            return false;
        }
        pstruAsnLaneTypeAttributes->present = LaneTypeAttributes_PR_parking;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "choice is err pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice = %d",
                 pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice);
        return false;
    }
    return true;
}
/**
* @brief     WJV4_LaneTypeAttributes_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_LaneTypeAttributes_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_LaneTypeAttributes *pstruWjLaneTypeAttributes = (WJV4_STRU_LaneTypeAttributes *)pvoidWjDf;
    LaneTypeAttributes_t *pstruAsnLaneTypeAttributes = (LaneTypeAttributes_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (LaneTypeAttributes_PR_vehicle == pstruAsnLaneTypeAttributes->present)
    {
        n32Ret = WJV4_LaneAttributesVehicle_DeDec(&(pstruAsnLaneTypeAttributes->choice.vehicle), &(pstruWjLaneTypeAttributes->u.strbitvehicle));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesVehicle_DeDec is err");
            return false;
        }
        pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice = WJV4_LaneAttributesVehicle;
    }
    else if (LaneTypeAttributes_PR_crosswalk == pstruAsnLaneTypeAttributes->present)
    {
        n32Ret = WJV4_LaneAttributesCrosswalk_DeDec(&(pstruAsnLaneTypeAttributes->choice.crosswalk), &(pstruWjLaneTypeAttributes->u.strbitcrosswalk));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesCrosswalk_DeDec is err");
            return false;
        }
        pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice = WJV4_LaneAttributesCrosswalk;
    }
    else if (LaneTypeAttributes_PR_bikeLane == pstruAsnLaneTypeAttributes->present)
    {
        n32Ret = WJV4_LaneAttributesBike_DeDec(&(pstruAsnLaneTypeAttributes->choice.bikeLane), &(pstruWjLaneTypeAttributes->u.strbitbikeLane));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesBike_DeDec is err");
            return false;
        }
        pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice = WJV4_LaneAttributesBike;
    }
    else if (LaneTypeAttributes_PR_sidewalk == pstruAsnLaneTypeAttributes->present)
    {
        n32Ret = WJV4_LaneAttributesSidewalk_DeDec(&(pstruAsnLaneTypeAttributes->choice.sidewalk), &(pstruWjLaneTypeAttributes->u.strbitsidewalk));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesSidewalk_DeDec is err");
            return false;
        }
        pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice = WJV4_LaneAttributesSidewalk;
    }
    else if (LaneTypeAttributes_PR_median == pstruAsnLaneTypeAttributes->present)
    {
        n32Ret = WJV4_LaneAttributesBarrier_DeDec(&(pstruAsnLaneTypeAttributes->choice.median), &(pstruWjLaneTypeAttributes->u.strbitmedian));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesBarrier_DeDec is err");
            return false;
        }
        pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice = LaneTypeAttributes_PR_median;
    }
    else if (LaneTypeAttributes_PR_striping == pstruAsnLaneTypeAttributes->present)
    {
        n32Ret = WJV4_LaneAttributesStriping_DeDec(&(pstruAsnLaneTypeAttributes->choice.striping), &(pstruWjLaneTypeAttributes->u.strbitstriping));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesStriping_DeDec is err");
            return false;
        }
        pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice = LaneTypeAttributes_PR_striping;
    }
    else if (LaneTypeAttributes_PR_trackedVehicle == pstruAsnLaneTypeAttributes->present)
    {
        n32Ret = WJV4_LaneAttributesTrackedVehicle_DeDec(&(pstruAsnLaneTypeAttributes->choice.trackedVehicle), &(pstruWjLaneTypeAttributes->u.strbittrackedVehicle));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesTrackedVehicle_DeDec is err");
            return false;
        }
        pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice = LaneTypeAttributes_PR_trackedVehicle;
    }
    else if (LaneTypeAttributes_PR_parking == pstruAsnLaneTypeAttributes->present)
    {
        n32Ret = WJV4_LaneAttributesParking_DeDec(&(pstruAsnLaneTypeAttributes->choice.parking), &(pstruWjLaneTypeAttributes->u.strbitparking));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LaneAttributesParking_DeDec is err");
            return false;
        }
        pstruWjLaneTypeAttributes->enumLaneTypeAttributesChoice = LaneTypeAttributes_PR_parking;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "choice is err pstruAsnLaneTypeAttributes->present = %d",
                 pstruAsnLaneTypeAttributes->present);
        return false;
    }
    return true;
}
/**
* @brief     WJV4_Link_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Link_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Link *pstruWjLink = (WJV4_STRU_Link *)pvoidWjDf;
    Link_t *pstruAsnLink = (Link_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV4_PRESENT == pstruWjLink->u8namePresent)
    {
        pstruAsnLink->name = CALLOC(1, sizeof(DescriptiveName_t));
        if (NULL == pstruAsnLink->name)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_DescriptiveName_DeEnc(pstruAsnLink->name, &(pstruWjLink->stria5name));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_DescriptiveName_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLink->name = NULL;
    }
    n32Ret = WJV4_NodeReferenceID_DfEnc(&(pstruAsnLink->upstreamNodeId), &(pstruWjLink->struupstreamNodeId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjLink->u8speedLimitsPresent)
    {
        pstruAsnLink->speedLimits = CALLOC(1, sizeof(struct SpeedLimitList));
        if (NULL == pstruAsnLink->speedLimits)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_SpeedLimitList_DfEnc(pstruAsnLink->speedLimits, &(pstruWjLink->struspeedLimits));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_SpeedLimitList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLink->speedLimits = NULL;
    }
    if (WJV4_PRESENT == pstruWjLink->u8linkWidthPresent)
    {
        pstruAsnLink->linkWidth = CALLOC(1, sizeof(LaneWidth_t));
        if (NULL == pstruAsnLink->linkWidth)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_LANEWIDTH_SIZE < pstruWjLink->n32linkWidth) || (WJV4_MIN_LANEWIDTH_SIZE > pstruWjLink->n32linkWidth))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjLink->n32linkWidth = %d",
                     pstruWjLink->n32linkWidth);
            return false;
        }
#endif
        *(pstruAsnLink->linkWidth) = pstruWjLink->n32linkWidth;
    }
    else
    {
        pstruAsnLink->linkWidth = NULL;
    }
    if (WJV4_PRESENT == pstruWjLink->u8pointsPresent)
    {
        pstruAsnLink->points = CALLOC(1, sizeof(struct PointList));
        if (NULL == pstruAsnLink->points)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_PointList_DfEnc(pstruAsnLink->points, &(pstruWjLink->strupoints));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PointList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLink->points = NULL;
    }
    if (WJV4_PRESENT == pstruWjLink->u8MovementListPresent)
    {
        pstruAsnLink->movements = CALLOC(1, sizeof(struct MovementList));
        if (NULL == pstruAsnLink->movements)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_MovementList_DfEnc(pstruAsnLink->movements, &(pstruWjLink->strumovements));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_MovementList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLink->movements = NULL;
    }
    n32Ret = WJV4_LaneList_DfEnc(&(pstruAsnLink->lanes), &(pstruWjLink->strulanes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_LaneList_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_Link_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Link_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Link *pstruWjLink = (WJV4_STRU_Link *)pvoidWjDf;
    Link_t *pstruAsnLink = (Link_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnLink->name)
    {
        n32Ret = WJV4_DescriptiveName_DeDec(pstruAsnLink->name, &(pstruWjLink->stria5name));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_DescriptiveName_DeDec is err");
            return false;
        }
        pstruWjLink->u8namePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLink->u8namePresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_NodeReferenceID_DfDec(&(pstruAsnLink->upstreamNodeId), &(pstruWjLink->struupstreamNodeId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnLink->speedLimits)
    {
        n32Ret = WJV4_SpeedLimitList_DfDec(pstruAsnLink->speedLimits, &(pstruWjLink->struspeedLimits));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_SpeedLimitList_DfDec is err");
            return false;
        }
        pstruWjLink->u8speedLimitsPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLink->u8speedLimitsPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnLink->linkWidth)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_LANEWIDTH_SIZE < *(pstruAsnLink->linkWidth)) || (WJV4_MIN_LANEWIDTH_SIZE > *(pstruAsnLink->linkWidth)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnLink->linkWidth) = %d",
                     *(pstruAsnLink->linkWidth));
            return false;
        }
#endif
        pstruWjLink->n32linkWidth = *(pstruAsnLink->linkWidth);
        pstruWjLink->u8linkWidthPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLink->u8linkWidthPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnLink->points)
    {
        n32Ret = WJV4_PointList_DfDec(pstruAsnLink->points, &(pstruWjLink->strupoints));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PointList_DfDec is err");
            return false;
        }
        pstruWjLink->u8pointsPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLink->u8pointsPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnLink->movements)
    {
        n32Ret = WJV4_MovementList_DfDec(pstruAsnLink->movements, &(pstruWjLink->strumovements));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_MovementList_DfDec is err");
            return false;
        }
        pstruWjLink->u8MovementListPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjLink->u8MovementListPresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_LaneList_DfDec(&(pstruAsnLink->lanes), &(pstruWjLink->strulanes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_LaneList_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_LinkList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_LinkList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_LinkList *pstruWjLinkList = (WJV4_STRU_LinkList *)pvoidWjDf;
    LinkList_t *pstruAsnLinkList = (LinkList_t *)pvoidAsnDf;
    Link_t *pstruLink_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_LINK_LEN < pstruWjLinkList->u8LinkNum) || (WJV4_MIN_LIST_LINK_LEN > pstruWjLinkList->u8LinkNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjLinkList->u8LinkNum = %d",
                 pstruWjLinkList->u8LinkNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjLinkList->u8LinkNum; u32i++)
    {
        pstruLink_node = CALLOC(1, sizeof(Link_t));
        if (NULL == pstruLink_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_Link_DfEnc(pstruLink_node, &(pstruWjLinkList->struLink[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Link_DfEnc is err");
            FREEMEM(pstruLink_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnLinkList->list), pstruLink_node);
    }
    return true;
}
/**
* @brief     WJV4_LinkList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_LinkList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_LinkList *pstruWjLinkList = (WJV4_STRU_LinkList *)pvoidWjDf;
    LinkList_t *pstruAsnLinkList = (LinkList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_LINK_LEN < pstruAsnLinkList->list.count) || (WJV4_MIN_LIST_LINK_LEN > pstruAsnLinkList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnLinkList->list.count = %d",
                 pstruAsnLinkList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnLinkList->list.count; u32i++)
    {
        n32Ret = WJV4_Link_DfDec(pstruAsnLinkList->list.array[u32i],
                                 &(pstruWjLinkList->struLink[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Link_DfDec is err");
            return false;
        }
    }
    pstruWjLinkList->u8LinkNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_MotionConfidenceSet_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_MotionConfidenceSet_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_MotionConfidenceSet *pstruWjMotionConfidenceSet = (WJV4_STRU_MotionConfidenceSet *)pvoidWjDf;
    MotionConfidenceSet_t *pstruAsnMotionConfidenceSet = (MotionConfidenceSet_t *)pvoidAsnDf;
    if (WJV4_PRESENT == pstruWjMotionConfidenceSet->u8speedCfdPresent)
    {
        pstruAsnMotionConfidenceSet->speedCfd = CALLOC(1, sizeof(SpeedConfidence_t));
        if (NULL == pstruAsnMotionConfidenceSet->speedCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnMotionConfidenceSet->speedCfd) = pstruWjMotionConfidenceSet->enumspeedCfd;
    }
    else
    {
        pstruAsnMotionConfidenceSet->speedCfd = NULL;
    }
    if (WJV4_PRESENT == pstruWjMotionConfidenceSet->u8headingCfdPresent)
    {
        pstruAsnMotionConfidenceSet->headingCfd = CALLOC(1, sizeof(HeadingConfidence_t));
        if (NULL == pstruAsnMotionConfidenceSet->headingCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnMotionConfidenceSet->headingCfd) = pstruWjMotionConfidenceSet->enumheadingCfd;
    }
    else
    {
        pstruAsnMotionConfidenceSet->headingCfd = NULL;
    }
    if (WJV4_PRESENT == pstruWjMotionConfidenceSet->u8steerCfdPresent)
    {
        pstruAsnMotionConfidenceSet->steerCfd = CALLOC(1, sizeof(SteeringWheelAngleConfidence_t));
        if (NULL == pstruAsnMotionConfidenceSet->steerCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnMotionConfidenceSet->steerCfd) = pstruWjMotionConfidenceSet->enumsteerCfd;
    }
    else
    {
        pstruAsnMotionConfidenceSet->steerCfd = NULL;
    }
    return true;
}
/**
* @brief     WJV4_MotionConfidenceSet_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_MotionConfidenceSet_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_MotionConfidenceSet *pstruWjMotionConfidenceSet = (WJV4_STRU_MotionConfidenceSet *)pvoidWjDf;
    MotionConfidenceSet_t *pstruAsnMotionConfidenceSet = (MotionConfidenceSet_t *)pvoidAsnDf;
    if (NULL != pstruAsnMotionConfidenceSet->speedCfd)
    {
        pstruWjMotionConfidenceSet->enumspeedCfd = *(pstruAsnMotionConfidenceSet->speedCfd);
        pstruWjMotionConfidenceSet->u8speedCfdPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjMotionConfidenceSet->u8speedCfdPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnMotionConfidenceSet->headingCfd)
    {
        pstruWjMotionConfidenceSet->enumheadingCfd = *(pstruAsnMotionConfidenceSet->headingCfd);
        pstruWjMotionConfidenceSet->u8headingCfdPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjMotionConfidenceSet->u8headingCfdPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnMotionConfidenceSet->steerCfd)
    {
        pstruWjMotionConfidenceSet->enumsteerCfd = *(pstruAsnMotionConfidenceSet->steerCfd);
        pstruWjMotionConfidenceSet->u8steerCfdPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjMotionConfidenceSet->u8steerCfdPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_Movement_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Movement_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Movement *pstruWjMovement = (WJV4_STRU_Movement *)pvoidWjDf;
    Movement_t *pstruAsnMovement = (Movement_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_NodeReferenceID_DfEnc(&(pstruAsnMovement->remoteIntersection),
                                        &(pstruWjMovement->struremoteIntersection));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjMovement->u8phaseIdPresent)
    {
        pstruAsnMovement->phaseId = CALLOC(1, sizeof(PhaseID_t));
        if (NULL == pstruAsnMovement->phaseId)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_PHASEID_SIZE < pstruWjMovement->n32phaseId) || (WJV4_MIN_PHASEID_SIZE > pstruWjMovement->n32phaseId))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjMovement->n32phaseId = %d",
                     pstruWjMovement->n32phaseId);
            return false;
        }
#endif
        *(pstruAsnMovement->phaseId) = pstruWjMovement->n32phaseId;
    }
    else
    {
        pstruAsnMovement->phaseId = NULL;
    }
    return true;
}
/**
* @brief     WJV4_Movement_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Movement_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Movement *pstruWjMovement = (WJV4_STRU_Movement *)pvoidWjDf;
    Movement_t *pstruAsnMovement = (Movement_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_NodeReferenceID_DfDec(&(pstruAsnMovement->remoteIntersection),
                                        &(pstruWjMovement->struremoteIntersection));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnMovement->phaseId)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_PHASEID_SIZE < *(pstruAsnMovement->phaseId)) || (WJV4_MIN_PHASEID_SIZE > *(pstruAsnMovement->phaseId)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnMovement->phaseId) = %d",
                     *(pstruAsnMovement->phaseId));
            return false;
        }
#endif
        pstruWjMovement->n32phaseId = *(pstruAsnMovement->phaseId);
        pstruWjMovement->u8phaseIdPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjMovement->u8phaseIdPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_MovementList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_MovementList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_MovementList *pstruWjMovementList = (WJV4_STRU_MovementList *)pvoidWjDf;
    MovementList_t *pstruAsnMovementList = (MovementList_t *)pvoidAsnDf;
    Movement_t *pstruMovement_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_MOVEMENT_LEN < pstruWjMovementList->u8MovementNum) || (WJV4_MIN_LIST_MOVEMENT_LEN > pstruWjMovementList->u8MovementNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjMovementList->u8MovementNum = %d",
                 pstruWjMovementList->u8MovementNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjMovementList->u8MovementNum; u32i++)
    {
        pstruMovement_node = CALLOC(1, sizeof(Movement_t));
        if (NULL == pstruMovement_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_Movement_DfEnc(pstruMovement_node, &(pstruWjMovementList->struMovement[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Movement_DfEnc is err");
            FREEMEM(pstruMovement_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnMovementList->list), pstruMovement_node);
    }
    return true;
}
/**
* @brief     WJV4_MovementList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_MovementList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_MovementList *pstruWjMovementList = (WJV4_STRU_MovementList *)pvoidWjDf;
    MovementList_t *pstruAsnMovementList = (MovementList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_MOVEMENT_LEN < pstruAsnMovementList->list.count) || (WJV4_MIN_LIST_MOVEMENT_LEN > pstruAsnMovementList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnMovementList->list.count = %d",
                 pstruAsnMovementList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnMovementList->list.count; u32i++)
    {
        n32Ret = WJV4_Movement_DfDec(pstruAsnMovementList->list.array[u32i],
                                     &(pstruWjMovementList->struMovement[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Movement_DfDec is err");
            return false;
        }
    }
    pstruWjMovementList->u8MovementNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_Node_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Node_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Node *pstruWjNode = (WJV4_STRU_Node *)pvoidWjDf;
    Node_t *pstruAsnNode = (Node_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV4_PRESENT == pstruWjNode->u8namePresent)
    {
        pstruAsnNode->name = CALLOC(1, sizeof(DescriptiveName_t));
        if (NULL == pstruAsnNode->name)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_DescriptiveName_DeEnc(pstruAsnNode->name, &(pstruWjNode->stria5name));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_DescriptiveName_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnNode->name = NULL;
    }
    n32Ret = WJV4_NodeReferenceID_DfEnc(&(pstruAsnNode->id), &(pstruWjNode->struid));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfEnc is err");
        return false;
    }
    n32Ret = WJV4_Position3D_DfEnc(&(pstruAsnNode->refPos), &(pstruWjNode->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_Position3D_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjNode->u8inLinksPresent)
    {
        pstruAsnNode->inLinks = CALLOC(1, sizeof(struct LinkList));
        if (NULL == pstruAsnNode->inLinks)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_LinkList_DfEnc(pstruAsnNode->inLinks, &(pstruWjNode->struinLinks));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LinkList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnNode->inLinks = NULL;
    }
    return true;
}
/**
* @brief     WJV4_Node_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Node_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Node *pstruWjNode = (WJV4_STRU_Node *)pvoidWjDf;
    Node_t *pstruAsnNode = (Node_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnNode->name)
    {
        n32Ret = WJV4_DescriptiveName_DeDec(pstruAsnNode->name, &(pstruWjNode->stria5name));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_DescriptiveName_DeDec is err");
            return false;
        }
        pstruWjNode->u8namePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjNode->u8namePresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_NodeReferenceID_DfDec(&(pstruAsnNode->id), &(pstruWjNode->struid));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfDec is err");
        return false;
    }
    n32Ret = WJV4_Position3D_DfDec(&(pstruAsnNode->refPos), &(pstruWjNode->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_Position3D_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnNode->inLinks)
    {
        n32Ret = WJV4_LinkList_DfDec(pstruAsnNode->inLinks, &(pstruWjNode->struinLinks));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_LinkList_DfDec is err");
            return false;
        }
        pstruWjNode->u8inLinksPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjNode->u8inLinksPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_NodeList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_NodeList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_NodeList *pstruWjNodeList = (WJV4_STRU_NodeList *)pvoidWjDf;
    NodeList_t *pstruAsnNodeList = (NodeList_t *)pvoidAsnDf;
    Node_t *pstruNode_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_NODE_LEN < pstruWjNodeList->u8NodeNum) || (WJV4_MIN_LIST_NODE_LEN > pstruWjNodeList->u8NodeNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjNodeList->u8NodeNum = %d",
                 pstruWjNodeList->u8NodeNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjNodeList->u8NodeNum; u32i++)
    {
        pstruNode_node = CALLOC(1, sizeof(Node_t));
        if (NULL == pstruNode_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_Node_DfEnc(pstruNode_node, &(pstruWjNodeList->struNode[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Node_DfEnc is err");
            FREEMEM(pstruNode_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnNodeList->list), pstruNode_node);
    }
    return true;
}
/**
* @brief     WJV4_NodeList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_NodeList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_NodeList *pstruWjNodeList = (WJV4_STRU_NodeList *)pvoidWjDf;
    NodeList_t *pstruAsnNodeList = (NodeList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_NODE_LEN < pstruAsnNodeList->list.count) || (WJV4_MIN_LIST_NODE_LEN > pstruAsnNodeList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnNodeList->list.count = %d",
                 pstruAsnNodeList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnNodeList->list.count; u32i++)
    {
        n32Ret = WJV4_Node_DfDec(pstruAsnNodeList->list.array[u32i],
                                 &(pstruWjNodeList->struNode[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Node_DfDec is err");
            return false;
        }
    }
    pstruWjNodeList->u8NodeNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_NodeReferenceID_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_NodeReferenceID_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_NodeReferenceID *pstruWjNodeReferenceID = (WJV4_STRU_NodeReferenceID *)pvoidWjDf;
    NodeReferenceID_t *pstruAsnNodeReferenceID = (NodeReferenceID_t *)pvoidAsnDf;
    if (WJV4_PRESENT == pstruWjNodeReferenceID->u8regionPresent)
    {
        pstruAsnNodeReferenceID->region = CALLOC(1, sizeof(RoadRegulatorID_t));
        if (NULL == pstruAsnNodeReferenceID->region)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_ROADREGULATORID_SIZE < pstruWjNodeReferenceID->n32region) || (WJV4_MIN_ROADREGULATORID_SIZE > pstruWjNodeReferenceID->n32region))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjNodeReferenceID->n32region = %d",
                     pstruWjNodeReferenceID->n32region);
            return false;
        }
#endif
        *(pstruAsnNodeReferenceID->region) = pstruWjNodeReferenceID->n32region;
    }
    else
    {
        pstruAsnNodeReferenceID->region = NULL;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_NODEID_SIZE < pstruWjNodeReferenceID->n32id) || (WJV4_MIN_NODEID_SIZE > pstruWjNodeReferenceID->n32id))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjNodeReferenceID->n32id = %d",
                 pstruWjNodeReferenceID->n32id);
        return false;
    }
#endif
    pstruAsnNodeReferenceID->id = pstruWjNodeReferenceID->n32id;
    return true;
}
/**
* @brief     WJV4_NodeReferenceID_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_NodeReferenceID_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_NodeReferenceID *pstruWjNodeReferenceID = (WJV4_STRU_NodeReferenceID *)pvoidWjDf;
    NodeReferenceID_t *pstruAsnNodeReferenceID = (NodeReferenceID_t *)pvoidAsnDf;
    if (NULL != pstruAsnNodeReferenceID->region)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_ROADREGULATORID_SIZE < *(pstruAsnNodeReferenceID->region)) || (WJV4_MIN_ROADREGULATORID_SIZE > *(pstruAsnNodeReferenceID->region)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnNodeReferenceID->region) = %d",
                     *(pstruAsnNodeReferenceID->region));
            return false;
        }
#endif
        pstruWjNodeReferenceID->n32region = *(pstruAsnNodeReferenceID->region);
        pstruWjNodeReferenceID->u8regionPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjNodeReferenceID->u8regionPresent = WJV4_ABSENT;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_NODEID_SIZE < pstruAsnNodeReferenceID->id) || (WJV4_MIN_NODEID_SIZE > pstruAsnNodeReferenceID->id))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnNodeReferenceID->id = %d",
                 pstruAsnNodeReferenceID->id);
        return false;
    }
#endif
    pstruWjNodeReferenceID->n32id = pstruAsnNodeReferenceID->id;
    return true;
}
/**
* @brief     WJV4_ParticipantData_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_ParticipantData_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ParticipantData *pstruWjParticipantData = (WJV4_STRU_ParticipantData *)pvoidWjDf;
    ParticipantData_t *pstruAsnParticipantData = (ParticipantData_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    pstruAsnParticipantData->ptcType = pstruWjParticipantData->enumptcType;
#ifdef _CHECK_
    if ((WJV4_MAX_PTCID_SIZE < pstruWjParticipantData->u32ptcId) || (WJV4_MIN_PTCID_SIZE > pstruWjParticipantData->u32ptcId))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjParticipantData->u32ptcId = %d",
                 pstruWjParticipantData->u32ptcId);
        return false;
    }
#endif
    pstruAsnParticipantData->ptcId = pstruWjParticipantData->u32ptcId;
    pstruAsnParticipantData->source = pstruWjParticipantData->enumsource;
    if (WJV4_PRESENT == pstruWjParticipantData->u8OCTidPresent)
    {
        pstruAsnParticipantData->id = CALLOC(1, sizeof(OCTET_STRING_t));
        if (NULL == pstruAsnParticipantData->id)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        pstruAsnParticipantData->id->size = WJV4_MAX_OCTID_SIZE;
        pstruAsnParticipantData->id->buf = CALLOC(pstruAsnParticipantData->id->size, sizeof(uint8_t));
        if (NULL == pstruAsnParticipantData->id)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        memcpy(pstruAsnParticipantData->id->buf, pstruWjParticipantData->u8OCTid, pstruAsnParticipantData->id->size);
    }
    else
    {
        pstruAsnParticipantData->id = NULL;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_DSECOND_SIZE < pstruWjParticipantData->n32secMark) || (WJV4_MIN_DSECOND_SIZE > pstruWjParticipantData->n32secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjParticipantData->n32secMark = %d",
                 pstruWjParticipantData->n32secMark);
        return false;
    }
#endif
    pstruAsnParticipantData->secMark = pstruWjParticipantData->n32secMark;
    n32Ret = WJV4_PositionOffsetLLV_DfEnc(&(pstruAsnParticipantData->pos), &(pstruWjParticipantData->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PositionOffsetLLV_DfEnc is err");
        return false;
    }
    n32Ret = WJV4_PositionConfidenceSet_DfEnc(&(pstruAsnParticipantData->posConfidence), &(pstruWjParticipantData->struposConfidence));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PositionConfidenceSet_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjParticipantData->u8transmissionPresent)
    {
        pstruAsnParticipantData->transmission = CALLOC(1, sizeof(TransmissionState_t));
        if (NULL == pstruAsnParticipantData->transmission)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnParticipantData->transmission) = pstruWjParticipantData->enumtransmission;
    }
    else
    {
        pstruAsnParticipantData->transmission = NULL;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_SPEED_SIZE < pstruWjParticipantData->n32speed) || (WJV4_MIN_SPEED_SIZE > pstruWjParticipantData->n32speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjParticipantData->n32speed = %d",
                 pstruWjParticipantData->n32speed);
        return false;
    }
#endif
    pstruAsnParticipantData->speed = pstruWjParticipantData->n32speed;
#ifdef _CHECK_
    if ((WJV4_MAX_HEADING_SIZE < pstruWjParticipantData->n32heading) || (WJV4_MIN_HEADING_SIZE > pstruWjParticipantData->n32heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjParticipantData->n32heading = %d",
                 pstruWjParticipantData->n32heading);
        return false;
    }
#endif
    pstruAsnParticipantData->heading = pstruWjParticipantData->n32heading;
    if (WJV4_PRESENT == pstruWjParticipantData->u8anglePresent)
    {
        pstruAsnParticipantData->angle = CALLOC(1, sizeof(SteeringWheelAngle_t));
        if (NULL == pstruAsnParticipantData->angle)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_STEERINGWHEELANGLE_SIZE < pstruWjParticipantData->n32angle) || (WJV4_MIN_STEERINGWHEELANGLE_SIZE > pstruWjParticipantData->n32angle))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjParticipantData->n32angle = %d",
                     pstruWjParticipantData->n32angle);
            return false;
        }
#endif
        *(pstruAsnParticipantData->angle) = pstruWjParticipantData->n32angle;
    }
    else
    {
        pstruAsnParticipantData->angle = NULL;
    }
    if (WJV4_PRESENT == pstruWjParticipantData->u8motionCfdPresent)
    {
        pstruAsnParticipantData->motionCfd = CALLOC(1, sizeof(struct MotionConfidenceSet));
        if (NULL == pstruAsnParticipantData->motionCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_MotionConfidenceSet_DfEnc(pstruAsnParticipantData->motionCfd, &(pstruWjParticipantData->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_MotionConfidenceSet_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnParticipantData->motionCfd = NULL;
    }
    if (WJV4_PRESENT == pstruWjParticipantData->u8accelSetPresent)
    {
        pstruAsnParticipantData->accelSet = CALLOC(1, sizeof(struct AccelerationSet4Way));
        if (NULL == pstruAsnParticipantData->accelSet)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_AccelerationSet4Way_DfEnc(pstruAsnParticipantData->accelSet, &(pstruWjParticipantData->struaccelSet));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_AccelerationSet4Way_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnParticipantData->accelSet = NULL;
    }
    n32Ret = WJV4_VehicleSize_DfEnc(&(pstruAsnParticipantData->size), &(pstruWjParticipantData->strusize));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_VehicleSize_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjParticipantData->u8vehicleClassPresent)
    {
        pstruAsnParticipantData->vehicleClass = CALLOC(1, sizeof(struct VehicleClassification));
        if (NULL == pstruAsnParticipantData->vehicleClass)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_VehicleClassification_DfEnc(pstruAsnParticipantData->vehicleClass, &(pstruWjParticipantData->struvehicleClass));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_VehicleClassification_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnParticipantData->vehicleClass = NULL;
    }
    return true;
}
/**
* @brief     WJV4_ParticipantData_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_ParticipantData_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ParticipantData *pstruWjParticipantData = (WJV4_STRU_ParticipantData *)pvoidWjDf;
    ParticipantData_t *pstruAsnParticipantData = (ParticipantData_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    pstruWjParticipantData->enumptcType = pstruAsnParticipantData->ptcType;
#ifdef _CHECK_
    if ((WJV4_MAX_PTCID_SIZE < pstruAsnParticipantData->ptcId) || (WJV4_MIN_PTCID_SIZE > pstruAsnParticipantData->ptcId))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnParticipantData->ptcId = %d",
                 pstruAsnParticipantData->ptcId);
        return false;
    }
#endif
    pstruWjParticipantData->u32ptcId = pstruAsnParticipantData->ptcId;
    pstruWjParticipantData->enumsource = pstruAsnParticipantData->source;
    if (NULL != pstruAsnParticipantData->id)
    {
        if (WJV4_MAX_OCTID_SIZE != pstruAsnParticipantData->id->size)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnParticipantData->id->size = %d",
                     pstruAsnParticipantData->id->size);
            return false;
        }
        memcpy(pstruWjParticipantData->u8OCTid, pstruAsnParticipantData->id->buf, pstruAsnParticipantData->id->size);
        pstruWjParticipantData->u8OCTidPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8OCTidPresent = WJV4_ABSENT;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_DSECOND_SIZE < pstruAsnParticipantData->secMark) || (WJV4_MIN_DSECOND_SIZE > pstruAsnParticipantData->secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnParticipantData->secMark = %d",
                 pstruAsnParticipantData->secMark);
        return false;
    }
#endif
    pstruWjParticipantData->n32secMark = pstruAsnParticipantData->secMark;
    n32Ret = WJV4_PositionOffsetLLV_DfDec(&(pstruAsnParticipantData->pos), &(pstruWjParticipantData->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PositionOffsetLLV_DfDec is err");
        return false;
    }
    n32Ret = WJV4_PositionConfidenceSet_DfDec(&(pstruAsnParticipantData->posConfidence), &(pstruWjParticipantData->struposConfidence));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PositionConfidenceSet_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnParticipantData->transmission)
    {
        pstruWjParticipantData->enumtransmission = *(pstruAsnParticipantData->transmission);
        pstruWjParticipantData->u8transmissionPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8transmissionPresent = WJV4_ABSENT;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_SPEED_SIZE < pstruAsnParticipantData->speed) || (WJV4_MIN_SPEED_SIZE > pstruAsnParticipantData->speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnParticipantData->speed = %d",
                 pstruAsnParticipantData->speed);
        return false;
    }
#endif
    pstruWjParticipantData->n32speed = pstruAsnParticipantData->speed;
#ifdef _CHECK_
    if ((WJV4_MAX_HEADING_SIZE < pstruAsnParticipantData->heading) || (WJV4_MIN_HEADING_SIZE > pstruAsnParticipantData->heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnParticipantData->heading = %d",
                 pstruAsnParticipantData->heading);
        return false;
    }
#endif
    pstruWjParticipantData->n32heading = pstruAsnParticipantData->heading;
    if (NULL != pstruAsnParticipantData->angle)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_STEERINGWHEELANGLE_SIZE < *(pstruAsnParticipantData->angle)) || (WJV4_MIN_STEERINGWHEELANGLE_SIZE > *(pstruAsnParticipantData->angle)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnParticipantData->angle) = %d",
                     *(pstruAsnParticipantData->angle));
            return false;
        }
#endif
        pstruWjParticipantData->n32angle = *(pstruAsnParticipantData->angle);
        pstruWjParticipantData->u8anglePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8anglePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnParticipantData->motionCfd)
    {
        n32Ret = WJV4_MotionConfidenceSet_DfDec(pstruAsnParticipantData->motionCfd, &(pstruWjParticipantData->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_MotionConfidenceSet_DfDec is err");
            return false;
        }
        pstruWjParticipantData->u8motionCfdPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8motionCfdPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnParticipantData->accelSet)
    {
        n32Ret = WJV4_AccelerationSet4Way_DfDec(pstruAsnParticipantData->accelSet, &(pstruWjParticipantData->struaccelSet));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_AccelerationSet4Way_DfDec is err");
            return false;
        }
        pstruWjParticipantData->u8accelSetPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8accelSetPresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_VehicleSize_DfDec(&(pstruAsnParticipantData->size), &(pstruWjParticipantData->strusize));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_VehicleSize_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnParticipantData->vehicleClass)
    {
        n32Ret = WJV4_VehicleClassification_DfDec(pstruAsnParticipantData->vehicleClass, &(pstruWjParticipantData->struvehicleClass));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_VehicleClassification_DfDec is err");
            return false;
        }
        pstruWjParticipantData->u8vehicleClassPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8vehicleClassPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_ParticipantList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_ParticipantList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ParticipantList *pstruWjParticipantList = (WJV4_STRU_ParticipantList *)pvoidWjDf;
    ParticipantList_t *pstruAsnParticipantList = (ParticipantList_t *)pvoidAsnDf;
    ParticipantData_t *pstruParticipantData_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_PARTICIPANTDATA_LEN < pstruWjParticipantList->u8ParticipantDataNum) || (WJV4_MIN_LIST_PARTICIPANTDATA_LEN > pstruWjParticipantList->u8ParticipantDataNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjParticipantList->u8ParticipantDataNum = %d",
                 pstruWjParticipantList->u8ParticipantDataNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjParticipantList->u8ParticipantDataNum; u32i++)
    {
        pstruParticipantData_node = CALLOC(1, sizeof(ParticipantData_t));
        if (NULL == pstruParticipantData_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_ParticipantData_DfEnc(pstruParticipantData_node, &(pstruWjParticipantList->struParticipantData[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ParticipantData_DfEnc is err");
            FREEMEM(pstruParticipantData_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnParticipantList->list), pstruParticipantData_node);
    }
    return true;
}
/**
* @brief     WJV4_ParticipantList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_ParticipantList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ParticipantList *pstruWjParticipantList = (WJV4_STRU_ParticipantList *)pvoidWjDf;
    ParticipantList_t *pstruAsnParticipantList = (ParticipantList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_PARTICIPANTDATA_LEN < pstruAsnParticipantList->list.count) || (WJV4_MIN_LIST_PARTICIPANTDATA_LEN > pstruAsnParticipantList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnParticipantList->list.count = %d",
                 pstruAsnParticipantList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnParticipantList->list.count; u32i++)
    {
        n32Ret = WJV4_ParticipantData_DfDec(pstruAsnParticipantList->list.array[u32i],
                                            &(pstruWjParticipantList->struParticipantData[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ParticipantData_DfDec is err");
            return false;
        }
    }
    pstruWjParticipantList->u8ParticipantDataNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_PathHistory_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PathHistory_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PathHistory *pstruWjPathHistory = (WJV4_STRU_PathHistory *)pvoidWjDf;
    PathHistory_t *pstruAsnPathHistory = (PathHistory_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV4_PRESENT == pstruWjPathHistory->u8initialPositionPresent)
    {
        pstruAsnPathHistory->initialPosition = CALLOC(1, sizeof(struct FullPositionVector));
        if (NULL == pstruAsnPathHistory->initialPosition)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_FullPositionVector_DfEnc(pstruAsnPathHistory->initialPosition, &(pstruWjPathHistory->struinitialPosition));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_FullPositionVector_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPathHistory->initialPosition = NULL;
    }
    if (WJV4_PRESENT == pstruWjPathHistory->u8currGNSSstatusPresent)
    {
        pstruAsnPathHistory->currGNSSstatus = CALLOC(1, sizeof(GNSSstatus_t));
        if (NULL == pstruAsnPathHistory->currGNSSstatus)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV4_GNSSstatus_DeEnc(pstruAsnPathHistory->currGNSSstatus, &(pstruWjPathHistory->strbitcurrGNSSstatus));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_GNSSstatus_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPathHistory->currGNSSstatus = NULL;
    }
    n32Ret = WJV4_PathHistoryPointList_DfEnc(&(pstruAsnPathHistory->crumbData), &(pstruWjPathHistory->strucrumbData));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PathHistoryPointList_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_PathHistory_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PathHistory_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PathHistory *pstruWjPathHistory = (WJV4_STRU_PathHistory *)pvoidWjDf;
    PathHistory_t *pstruAsnPathHistory = (PathHistory_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnPathHistory->initialPosition)
    {
        n32Ret = WJV4_FullPositionVector_DfDec(pstruAsnPathHistory->initialPosition, &(pstruWjPathHistory->struinitialPosition));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_FullPositionVector_DfDec is err");
            return false;
        }
        pstruWjPathHistory->u8initialPositionPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjPathHistory->u8initialPositionPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnPathHistory->currGNSSstatus)
    {
        n32Ret = WJV4_GNSSstatus_DeDec(pstruAsnPathHistory->currGNSSstatus, &(pstruWjPathHistory->strbitcurrGNSSstatus));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_GNSSstatus_DeDec is err");
            return false;
        }
        pstruWjPathHistory->u8currGNSSstatusPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjPathHistory->u8currGNSSstatusPresent = WJV4_ABSENT;
    }
    n32Ret = WJV4_PathHistoryPointList_DfDec(&(pstruAsnPathHistory->crumbData), &(pstruWjPathHistory->strucrumbData));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PathHistoryPointList_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_PathHistoryPoint_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PathHistoryPoint_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PathHistoryPoint *pstruWjPathHistoryPoint = (WJV4_STRU_PathHistoryPoint *)pvoidWjDf;
    PathHistoryPoint_t *pstruAsnPathHistoryPoint = (PathHistoryPoint_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_PositionOffsetLLV_DfEnc(&(pstruAsnPathHistoryPoint->llvOffset), &(pstruWjPathHistoryPoint->strullvOffset));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PathHistoryPointList_DfEnc is err");
        return false;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_TIMEOFFSET_SIZE < pstruWjPathHistoryPoint->n32timeOffset) || (WJV4_MIN_TIMEOFFSET_SIZE > pstruWjPathHistoryPoint->n32timeOffset))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPathHistoryPoint->n32timeOffset = %d",
                 pstruWjPathHistoryPoint->n32timeOffset);
        return false;
    }
#endif
    pstruAsnPathHistoryPoint->timeOffset = pstruWjPathHistoryPoint->n32timeOffset;
    if (WJV4_PRESENT == pstruWjPathHistoryPoint->u8speedPresent)
    {
        pstruAsnPathHistoryPoint->speed = CALLOC(1, sizeof(Speed_t));
        if (NULL == pstruAsnPathHistoryPoint->speed)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_SPEED_SIZE < pstruWjPathHistoryPoint->n32speed) || (WJV4_MIN_SPEED_SIZE > pstruWjPathHistoryPoint->n32speed))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjPathHistoryPoint->n32speed = %d",
                     pstruWjPathHistoryPoint->n32speed);
            return false;
        }
#endif
        *(pstruAsnPathHistoryPoint->speed) = pstruWjPathHistoryPoint->n32speed;
    }
    else
    {
        pstruAsnPathHistoryPoint->speed = NULL;
    }
    if (WJV4_PRESENT == pstruWjPathHistoryPoint->u8posAccuracyPresent)
    {
        pstruAsnPathHistoryPoint->posAccuracy = CALLOC(1, sizeof(struct PositionConfidenceSet));
        if (NULL == pstruAsnPathHistoryPoint->posAccuracy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_PositionConfidenceSet_DfEnc(pstruAsnPathHistoryPoint->posAccuracy, &(pstruWjPathHistoryPoint->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionConfidenceSet_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPathHistoryPoint->posAccuracy = NULL;
    }
    if (WJV4_PRESENT == pstruWjPathHistoryPoint->u8headingPresent)
    {
        pstruAsnPathHistoryPoint->heading = CALLOC(1, sizeof(CoarseHeading_t));
        if (NULL == pstruAsnPathHistoryPoint->heading)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_COARSEHEADING_SIZE < pstruWjPathHistoryPoint->n32heading) || (WJV4_MIN_COARSEHEADING_SIZE > pstruWjPathHistoryPoint->n32heading))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjPathHistoryPoint->n32heading = %d",
                     pstruWjPathHistoryPoint->n32heading);
            return false;
        }
#endif
        *(pstruAsnPathHistoryPoint->heading) = pstruWjPathHistoryPoint->n32heading;
    }
    else
    {
        pstruAsnPathHistoryPoint->heading = NULL;
    }
    return true;
}
/**
* @brief     WJV4_PathHistoryPoint_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PathHistoryPoint_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PathHistoryPoint *pstruWjPathHistoryPoint = (WJV4_STRU_PathHistoryPoint *)pvoidWjDf;
    PathHistoryPoint_t *pstruAsnPathHistoryPoint = (PathHistoryPoint_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_PositionOffsetLLV_DfDec(&(pstruAsnPathHistoryPoint->llvOffset), &(pstruWjPathHistoryPoint->strullvOffset));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PositionOffsetLLV_DfDec is err");
        return false;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_TIMEOFFSET_SIZE < pstruAsnPathHistoryPoint->timeOffset) || (WJV4_MIN_TIMEOFFSET_SIZE > pstruAsnPathHistoryPoint->timeOffset))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPathHistoryPoint->timeOffset = %d",
                 pstruAsnPathHistoryPoint->timeOffset);
        return false;
    }
#endif
    pstruWjPathHistoryPoint->n32timeOffset = pstruAsnPathHistoryPoint->timeOffset;
    if (NULL != pstruAsnPathHistoryPoint->speed)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_SPEED_SIZE < *(pstruAsnPathHistoryPoint->speed)) || (WJV4_MIN_SPEED_SIZE > *(pstruAsnPathHistoryPoint->speed)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnPathHistoryPoint->speed) = %d",
                     *(pstruAsnPathHistoryPoint->speed));
            return false;
        }
#endif
        pstruWjPathHistoryPoint->n32speed = *(pstruAsnPathHistoryPoint->speed);
        pstruWjPathHistoryPoint->u8speedPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjPathHistoryPoint->u8speedPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnPathHistoryPoint->posAccuracy)
    {
        n32Ret = WJV4_PositionConfidenceSet_DfDec(pstruAsnPathHistoryPoint->posAccuracy, &(pstruWjPathHistoryPoint->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionConfidenceSet_DfDec is err");
            return false;
        }
        pstruWjPathHistoryPoint->u8posAccuracyPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjPathHistoryPoint->u8posAccuracyPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnPathHistoryPoint->heading)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_HEADING_SIZE < *(pstruAsnPathHistoryPoint->heading)) || (WJV4_MIN_HEADING_SIZE > *(pstruAsnPathHistoryPoint->heading)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnPathHistoryPoint->heading) = %d",
                     *(pstruAsnPathHistoryPoint->heading));
            return false;
        }
#endif
        pstruWjPathHistoryPoint->n32heading = *(pstruAsnPathHistoryPoint->heading);
        pstruWjPathHistoryPoint->u8headingPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjPathHistoryPoint->u8headingPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_PathHistoryPointList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PathHistoryPointList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PathHistoryPointList *pstruWjPathHistoryPointList = (WJV4_STRU_PathHistoryPointList *)pvoidWjDf;
    PathHistoryPointList_t *pstruAsnPathHistoryPointList = (PathHistoryPointList_t *)pvoidAsnDf;
    PathHistoryPoint_t *pstruPathHistoryPoint_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_PATHHISTORYPOINT_LEN < pstruWjPathHistoryPointList->u8PathHistoryPointNum) || (WJV4_MIN_LIST_PATHHISTORYPOINT_LEN > pstruWjPathHistoryPointList->u8PathHistoryPointNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPathHistoryPointList->u8PathHistoryPointNum = %d",
                 pstruWjPathHistoryPointList->u8PathHistoryPointNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjPathHistoryPointList->u8PathHistoryPointNum; u32i++)
    {
        pstruPathHistoryPoint_node = CALLOC(1, sizeof(PathHistoryPoint_t));
        if (NULL == pstruPathHistoryPoint_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_PathHistoryPoint_DfEnc(pstruPathHistoryPoint_node, &(pstruWjPathHistoryPointList->struPathHistoryPoint[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PathHistoryPoint_DfEnc is err");
            FREEMEM(pstruPathHistoryPoint_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnPathHistoryPointList->list), pstruPathHistoryPoint_node);
    }
    return true;
}
/**
* @brief     WJV4_PathHistoryPointList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PathHistoryPointList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PathHistoryPointList *pstruWjPathHistoryPointList = (WJV4_STRU_PathHistoryPointList *)pvoidWjDf;
    PathHistoryPointList_t *pstruAsnPathHistoryPointList = (PathHistoryPointList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_PATHHISTORYPOINT_LEN < pstruAsnPathHistoryPointList->list.count) || (WJV4_MIN_LIST_PATHHISTORYPOINT_LEN > pstruAsnPathHistoryPointList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPathHistoryPointList->list.count = %d",
                 pstruAsnPathHistoryPointList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnPathHistoryPointList->list.count; u32i++)
    {
        n32Ret = WJV4_PathHistoryPoint_DfDec(pstruAsnPathHistoryPointList->list.array[u32i],
                                             &(pstruWjPathHistoryPointList->struPathHistoryPoint[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PathHistoryPoint_DfDec is err");
            return false;
        }
    }
    pstruWjPathHistoryPointList->u8PathHistoryPointNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_PathPointList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PathPointList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PathPointList *pstruWjPathPointList = (WJV4_STRU_PathPointList *)pvoidWjDf;
    PathPointList_t *pstruAsnPathPointList = (PathPointList_t *)pvoidAsnDf;
    PositionOffsetLLV_t *pstruPositionOffsetLLV_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_POSITIONOFFSETLLV_LEN < pstruWjPathPointList->u8PositionOffsetLLVNum) || (WJV4_MIN_LIST_POSITIONOFFSETLLV_LEN > pstruWjPathPointList->u8PositionOffsetLLVNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPathPointList->u8PositionOffsetLLVNum = %d",
                 pstruWjPathPointList->u8PositionOffsetLLVNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjPathPointList->u8PositionOffsetLLVNum; u32i++)
    {
        pstruPositionOffsetLLV_node = CALLOC(1, sizeof(PositionOffsetLLV_t));
        if (NULL == pstruPositionOffsetLLV_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_PositionOffsetLLV_DfEnc(pstruPositionOffsetLLV_node, &(pstruWjPathPointList->struPositionOffsetLLV[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionOffsetLLV_DfEnc is err");
            FREEMEM(pstruPositionOffsetLLV_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnPathPointList->list), pstruPositionOffsetLLV_node);
    }
    return true;
}
/**
* @brief     WJV4_PathPointList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PathPointList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PathPointList *pstruWjPathPointList = (WJV4_STRU_PathPointList *)pvoidWjDf;
    PathPointList_t *pstruAsnPathPointList = (PathPointList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_POSITIONOFFSETLLV_LEN < pstruAsnPathPointList->list.count) || (WJV4_MIN_LIST_POSITIONOFFSETLLV_LEN > pstruAsnPathPointList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPathPointList->list.count = %d",
                 pstruAsnPathPointList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnPathPointList->list.count; u32i++)
    {
        n32Ret = WJV4_PositionOffsetLLV_DfDec(pstruAsnPathPointList->list.array[u32i],
                                              &(pstruWjPathPointList->struPositionOffsetLLV[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionOffsetLLV_DfDec is err");
            return false;
        }
    }
    pstruWjPathPointList->u8PositionOffsetLLVNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_PathPrediction_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PathPrediction_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PathPrediction *pstruWjPathPrediction = (WJV4_STRU_PathPrediction *)pvoidWjDf;
    PathPrediction_t *pstruAsnPathPrediction = (PathPrediction_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_RADIUSOFCURVATURE_SIZE < pstruWjPathPrediction->n32radiusOfCurve) || (WJV4_MIN_RADIUSOFCURVATURE_SIZE > pstruWjPathPrediction->n32radiusOfCurve))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPathPrediction->n32radiusOfCurve = %d",
                 pstruWjPathPrediction->n32radiusOfCurve);
        return false;
    }
#endif
    pstruAsnPathPrediction->radiusOfCurve = pstruWjPathPrediction->n32radiusOfCurve;
#ifdef _CHECK_
    if ((WJV4_MAX_CONFIDENCE_SIZE < pstruWjPathPrediction->n32confidence) || (WJV4_MIN_CONFIDENCE_SIZE > pstruWjPathPrediction->n32confidence))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPathPrediction->n32confidence = %d",
                 pstruWjPathPrediction->n32confidence);
        return false;
    }
#endif
    pstruAsnPathPrediction->confidence = pstruWjPathPrediction->n32confidence;
    return true;
}
/**
* @brief     WJV4_PathPrediction_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PathPrediction_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PathPrediction *pstruWjPathPrediction = (WJV4_STRU_PathPrediction *)pvoidWjDf;
    PathPrediction_t *pstruAsnPathPrediction = (PathPrediction_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_RADIUSOFCURVATURE_SIZE < pstruAsnPathPrediction->radiusOfCurve) || (WJV4_MIN_RADIUSOFCURVATURE_SIZE > pstruAsnPathPrediction->radiusOfCurve))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPathPrediction->radiusOfCurve = %d",
                 pstruAsnPathPrediction->radiusOfCurve);
        return false;
    }
#endif
    pstruWjPathPrediction->n32radiusOfCurve = pstruAsnPathPrediction->radiusOfCurve;
#ifdef _CHECK_
    if ((WJV4_MAX_CONFIDENCE_SIZE < pstruAsnPathPrediction->confidence) || (WJV4_MIN_CONFIDENCE_SIZE > pstruAsnPathPrediction->confidence))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPathPrediction->confidence = %d",
                 pstruAsnPathPrediction->confidence);
        return false;
    }
#endif
    pstruWjPathPrediction->n32confidence = pstruAsnPathPrediction->confidence;
    return true;
}
/**
* @brief     WJV4_Phase_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Phase_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Phase *pstruWjPhase = (WJV4_STRU_Phase *)pvoidWjDf;
    Phase_t *pstruAsnPhase = (Phase_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_PHASEID_SIZE < pstruWjPhase->n32id) || (WJV4_MIN_PHASEID_SIZE > pstruWjPhase->n32id))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPhase->n32id = %d",
                 pstruWjPhase->n32id);
        return false;
    }
#endif
    pstruAsnPhase->id = pstruWjPhase->n32id;
    n32Ret = WJV4_PhaseStateList_DfEnc(&(pstruAsnPhase->phaseStates), &(pstruWjPhase->struphaseStates));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PhaseStateList_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_Phase_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_Phase_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Phase *pstruWjPhase = (WJV4_STRU_Phase *)pvoidWjDf;
    Phase_t *pstruAsnPhase = (Phase_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_PHASEID_SIZE < pstruAsnPhase->id) || (WJV4_MIN_PHASEID_SIZE > pstruAsnPhase->id))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPhase->id = %d",
                 pstruAsnPhase->id);
        return false;
    }
#endif
    pstruWjPhase->n32id = pstruAsnPhase->id;
    n32Ret = WJV4_PhaseStateList_DfDec(&(pstruAsnPhase->phaseStates), &(pstruWjPhase->struphaseStates));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PhaseStateList_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_PhaseList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PhaseList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PhaseList *pstruWjPhaseList = (WJV4_STRU_PhaseList *)pvoidWjDf;
    PhaseList_t *pstruAsnPhaseList = (PhaseList_t *)pvoidAsnDf;
    Phase_t *pstruPhase_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_PHASE_LEN < pstruWjPhaseList->u8PhaseNum) || (WJV4_MIN_LIST_PHASE_LEN > pstruWjPhaseList->u8PhaseNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPhaseList->u8PhaseNum = %d",
                 pstruWjPhaseList->u8PhaseNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjPhaseList->u8PhaseNum; u32i++)
    {
        pstruPhase_node = CALLOC(1, sizeof(Phase_t));
        if (NULL == pstruPhase_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_Phase_DfEnc(pstruPhase_node, &(pstruWjPhaseList->struPhase[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Phase_DfEnc is err");
            FREEMEM(pstruPhase_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnPhaseList->list), pstruPhase_node);
    }
    return true;
}
/**
* @brief     WJV4_PhaseList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PhaseList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PhaseList *pstruWjPhaseList = (WJV4_STRU_PhaseList *)pvoidWjDf;
    PhaseList_t *pstruAsnPhaseList = (PhaseList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_PHASE_LEN < pstruAsnPhaseList->list.count) || (WJV4_MIN_LIST_PHASE_LEN > pstruAsnPhaseList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPhaseList->list.count = %d",
                 pstruAsnPhaseList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnPhaseList->list.count; u32i++)
    {
        n32Ret = WJV4_Phase_DfDec(pstruAsnPhaseList->list.array[u32i],
                                  &(pstruWjPhaseList->struPhase[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Phase_DfDec is err");
            return false;
        }
    }
    pstruWjPhaseList->u8PhaseNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_PhaseState_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PhaseState_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PhaseState *pstruWjPhaseState = (WJV4_STRU_PhaseState *)pvoidWjDf;
    PhaseState_t *pstruAsnPhaseState = (PhaseState_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    pstruAsnPhaseState->light = pstruWjPhaseState->enumlight;
    if (WJV4_PRESENT == pstruWjPhaseState->u8timingPresent)
    {
        pstruAsnPhaseState->timing = CALLOC(1, sizeof(struct TimeChangeDetails));
        if (NULL == pstruAsnPhaseState->timing)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_TimeChangeDetails_DfEnc(pstruAsnPhaseState->timing, &(pstruWjPhaseState->strutiming));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_TimeChangeDetails_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPhaseState->timing = NULL;
    }
    return true;
}
/**
* @brief     WJV4_PhaseState_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PhaseState_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PhaseState *pstruWjPhaseState = (WJV4_STRU_PhaseState *)pvoidWjDf;
    PhaseState_t *pstruAsnPhaseState = (PhaseState_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    pstruWjPhaseState->enumlight = pstruAsnPhaseState->light;
    if (NULL != pstruAsnPhaseState->timing)
    {
        n32Ret = WJV4_TimeChangeDetails_DfDec(pstruAsnPhaseState->timing, &(pstruWjPhaseState->strutiming));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_TimeChangeDetails_DfDec is err");
            return false;
        }
        pstruWjPhaseState->u8timingPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjPhaseState->u8timingPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_PhaseStateList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PhaseStateList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PhaseStateList *pstruWjPhaseStateList = (WJV4_STRU_PhaseStateList *)pvoidWjDf;
    PhaseStateList_t *pstruAsnPhaseStateList = (PhaseStateList_t *)pvoidAsnDf;
    PhaseState_t *pstruPhaseState_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_PHASESTATE_LEN < pstruWjPhaseStateList->u8PhaseStateNum) || (WJV4_MIN_LIST_PHASESTATE_LEN > pstruWjPhaseStateList->u8PhaseStateNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPhaseStateList->u8PhaseStateNum = %d",
                 pstruWjPhaseStateList->u8PhaseStateNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjPhaseStateList->u8PhaseStateNum; u32i++)
    {
        pstruPhaseState_node = CALLOC(1, sizeof(PhaseState_t));
        if (NULL == pstruPhaseState_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_PhaseState_DfEnc(pstruPhaseState_node, &(pstruWjPhaseStateList->struPhaseState[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PhaseState_DfEnc is err");
            FREEMEM(pstruPhaseState_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnPhaseStateList->list), pstruPhaseState_node);
    }
    return true;
}
/**
* @brief     WJV4_PhaseStateList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PhaseStateList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PhaseStateList *pstruWjPhaseStateList = (WJV4_STRU_PhaseStateList *)pvoidWjDf;
    PhaseStateList_t *pstruAsnPhaseStateList = (PhaseStateList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_PHASESTATE_LEN < pstruAsnPhaseStateList->list.count) || (WJV4_MIN_LIST_PHASESTATE_LEN > pstruAsnPhaseStateList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPhaseStateList->list.count = %d",
                 pstruAsnPhaseStateList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnPhaseStateList->list.count; u32i++)
    {
        n32Ret = WJV4_PhaseState_DfDec(pstruAsnPhaseStateList->list.array[u32i],
                                       &(pstruWjPhaseStateList->struPhaseState[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PhaseState_DfDec is err");
            return false;
        }
    }
    pstruWjPhaseStateList->u8PhaseStateNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_PointList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PointList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PointList *pstruWjPointList = (WJV4_STRU_PointList *)pvoidWjDf;
    PointList_t *pstruAsnPointList = (PointList_t *)pvoidAsnDf;
    RoadPoint_t *pstruRoadPoint_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_ROADPOINT_LEN < pstruWjPointList->u8RoadPointNum) || (WJV4_MIN_LIST_ROADPOINT_LEN > pstruWjPointList->u8RoadPointNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPointList->u8RoadPointNum = %d",
                 pstruWjPointList->u8RoadPointNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjPointList->u8RoadPointNum; u32i++)
    {
        pstruRoadPoint_node = CALLOC(1, sizeof(RoadPoint_t));
        if (NULL == pstruRoadPoint_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_RoadPoint_DfEnc(pstruRoadPoint_node, &(pstruWjPointList->struRoadPoint[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RoadPoint_DfEnc is err");
            FREEMEM(pstruRoadPoint_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnPointList->list), pstruRoadPoint_node);
    }
    return true;
}
/**
* @brief     WJV4_PointList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
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
int32_t WJV4_PointList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PointList *pstruWjPointList = (WJV4_STRU_PointList *)pvoidWjDf;
    PointList_t *pstruAsnPointList = (PointList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_ROADPOINT_LEN < pstruAsnPointList->list.count) || (WJV4_MIN_LIST_ROADPOINT_LEN > pstruAsnPointList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPointList->list.count = %d",
                 pstruAsnPointList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnPointList->list.count; u32i++)
    {
        n32Ret = WJV4_RoadPoint_DfDec(pstruAsnPointList->list.array[u32i],
                                      &(pstruWjPointList->struRoadPoint[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RoadPoint_DfDec is err");
            return false;
        }
    }
    pstruWjPointList->u8RoadPointNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_PositionLL24B_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL24B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL24B *pstruWjPositionLL24B = (WJV4_STRU_PositionLL24B *)pvoidWjDf;
    Position_LL_24B_t *pstruAsnPositionLL24B = (Position_LL_24B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB12_SIZE < pstruWjPositionLL24B->n32lon) || (WJV4_MIN_OFFSETLLB12_SIZE > pstruWjPositionLL24B->n32lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL24B->n32lon = %d",
                 pstruWjPositionLL24B->n32lon);
        return false;
    }
#endif
    pstruAsnPositionLL24B->lon = pstruWjPositionLL24B->n32lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB12_SIZE < pstruWjPositionLL24B->n32lat) || (WJV4_MIN_OFFSETLLB12_SIZE > pstruWjPositionLL24B->n32lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL24B->n32lat = %d",
                 pstruWjPositionLL24B->n32lat);
        return false;
    }
#endif
    pstruAsnPositionLL24B->lat = pstruWjPositionLL24B->n32lat;
    return true;
}
/**
* @brief     WJV4_PositionLL24B_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL24B_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL24B *pstruWjPositionLL24B = (WJV4_STRU_PositionLL24B *)pvoidWjDf;
    Position_LL_24B_t *pstruAsnPositionLL24B = (Position_LL_24B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB12_SIZE < pstruAsnPositionLL24B->lon) || (WJV4_MIN_OFFSETLLB12_SIZE > pstruAsnPositionLL24B->lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL24B->lon = %d",
                 pstruAsnPositionLL24B->lon);
        return false;
    }
#endif
    pstruWjPositionLL24B->n32lon = pstruAsnPositionLL24B->lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB12_SIZE < pstruAsnPositionLL24B->lat) || (WJV4_MIN_OFFSETLLB12_SIZE > pstruAsnPositionLL24B->lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL24B->lat = %d",
                 pstruAsnPositionLL24B->lat);
        return false;
    }
#endif
    pstruWjPositionLL24B->n32lat = pstruAsnPositionLL24B->lat;
    return true;
}
/**
* @brief     WJV4_PositionLL28B_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL28B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL28B *pstruWjPositionLL28B = (WJV4_STRU_PositionLL28B *)pvoidWjDf;
    Position_LL_28B_t *pstruAsnPositionLL28B = (Position_LL_28B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB14_SIZE < pstruWjPositionLL28B->n32lon) || (WJV4_MIN_OFFSETLLB14_SIZE > pstruWjPositionLL28B->n32lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL28B->n32lon = %d",
                 pstruWjPositionLL28B->n32lon);
        return false;
    }
#endif
    pstruAsnPositionLL28B->lon = pstruWjPositionLL28B->n32lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB14_SIZE < pstruWjPositionLL28B->n32lat) || (WJV4_MIN_OFFSETLLB14_SIZE > pstruWjPositionLL28B->n32lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL28B->n32lat = %d",
                 pstruWjPositionLL28B->n32lat);
        return false;
    }
#endif
    pstruAsnPositionLL28B->lat = pstruWjPositionLL28B->n32lat;
    return true;
}
/**
* @brief     WJV4_PositionLL28B_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL28B_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL28B *pstruWjPositionLL28B = (WJV4_STRU_PositionLL28B *)pvoidWjDf;
    Position_LL_28B_t *pstruAsnPositionLL28B = (Position_LL_28B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB14_SIZE < pstruAsnPositionLL28B->lon) || (WJV4_MIN_OFFSETLLB14_SIZE > pstruAsnPositionLL28B->lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL28B->lon = %d",
                 pstruAsnPositionLL28B->lon);
        return false;
    }
#endif
    pstruWjPositionLL28B->n32lon = pstruAsnPositionLL28B->lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB14_SIZE < pstruAsnPositionLL28B->lat) || (WJV4_MIN_OFFSETLLB14_SIZE > pstruAsnPositionLL28B->lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL28B->lat = %d",
                 pstruAsnPositionLL28B->lat);
        return false;
    }
#endif
    pstruWjPositionLL28B->n32lat = pstruAsnPositionLL28B->lat;
    return true;
}
/**
* @brief     WJV4_PositionLL32B_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL32B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL32B *pstruWjPositionLL32B = (WJV4_STRU_PositionLL32B *)pvoidWjDf;
    Position_LL_32B_t *pstruAsnPositionLL32B = (Position_LL_32B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB16_SIZE < pstruWjPositionLL32B->n32lon) || (WJV4_MIN_OFFSETLLB16_SIZE > pstruWjPositionLL32B->n32lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL32B->n32lon = %d",
                 pstruWjPositionLL32B->n32lon);
        return false;
    }
#endif
    pstruAsnPositionLL32B->lon = pstruWjPositionLL32B->n32lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB16_SIZE < pstruWjPositionLL32B->n32lat) || (WJV4_MIN_OFFSETLLB16_SIZE > pstruWjPositionLL32B->n32lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL32B->n32lat = %d",
                 pstruWjPositionLL32B->n32lat);
        return false;
    }
#endif
    pstruAsnPositionLL32B->lat = pstruWjPositionLL32B->n32lat;
    return true;
}
/**
* @brief     WJV4_PositionLL32B_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL32B_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL32B *pstruWjPositionLL32B = (WJV4_STRU_PositionLL32B *)pvoidWjDf;
    Position_LL_32B_t *pstruAsnPositionLL32B = (Position_LL_32B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB16_SIZE < pstruAsnPositionLL32B->lon) || (WJV4_MIN_OFFSETLLB16_SIZE > pstruAsnPositionLL32B->lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL32B->lon = %d",
                 pstruAsnPositionLL32B->lon);
        return false;
    }
#endif
    pstruWjPositionLL32B->n32lon = pstruAsnPositionLL32B->lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB16_SIZE < pstruAsnPositionLL32B->lat) || (WJV4_MIN_OFFSETLLB16_SIZE > pstruAsnPositionLL32B->lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL32B->lat = %d",
                 pstruAsnPositionLL32B->lat);
        return false;
    }
#endif
    pstruWjPositionLL32B->n32lat = pstruAsnPositionLL32B->lat;
    return true;
}
/**
* @brief     WJV4_PositionLL36B_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL36B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL36B *pstruWjPositionLL36B = (WJV4_STRU_PositionLL36B *)pvoidWjDf;
    Position_LL_36B_t *pstruAsnPositionLL36B = (Position_LL_36B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB18_SIZE < pstruWjPositionLL36B->n32lon) || (WJV4_MIN_OFFSETLLB18_SIZE > pstruWjPositionLL36B->n32lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL36B->n32lon = %d",
                 pstruWjPositionLL36B->n32lon);
        return false;
    }
#endif
    pstruAsnPositionLL36B->lon = pstruWjPositionLL36B->n32lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB18_SIZE < pstruWjPositionLL36B->n32lat) || (WJV4_MIN_OFFSETLLB18_SIZE > pstruWjPositionLL36B->n32lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL36B->n32lat = %d",
                 pstruWjPositionLL36B->n32lat);
        return false;
    }
#endif
    pstruAsnPositionLL36B->lat = pstruWjPositionLL36B->n32lat;
    return true;
}
/**
* @brief     WJV4_PositionLL36B_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL36B_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL36B *pstruWjPositionLL36B = (WJV4_STRU_PositionLL36B *)pvoidWjDf;
    Position_LL_36B_t *pstruAsnPositionLL36B = (Position_LL_36B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB18_SIZE < pstruAsnPositionLL36B->lon) || (WJV4_MIN_OFFSETLLB18_SIZE > pstruAsnPositionLL36B->lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL36B->lon = %d",
                 pstruAsnPositionLL36B->lon);
        return false;
    }
#endif
    pstruWjPositionLL36B->n32lon = pstruAsnPositionLL36B->lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB18_SIZE < pstruAsnPositionLL36B->lat) || (WJV4_MIN_OFFSETLLB18_SIZE > pstruAsnPositionLL36B->lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL36B->lat = %d",
                 pstruAsnPositionLL36B->lat);
        return false;
    }
#endif
    pstruWjPositionLL36B->n32lat = pstruAsnPositionLL36B->lat;
    return true;
}
/**
* @brief     WJV4_PositionLL44B_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL44B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL44B *pstruWjPositionLL44B = (WJV4_STRU_PositionLL44B *)pvoidWjDf;
    Position_LL_44B_t *pstruAsnPositionLL44B = (Position_LL_44B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB22_SIZE < pstruWjPositionLL44B->n32lon) || (WJV4_MIN_OFFSETLLB22_SIZE > pstruWjPositionLL44B->n32lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL44B->n32lon = %d",
                 pstruWjPositionLL44B->n32lon);
        return false;
    }
#endif
    pstruAsnPositionLL44B->lon = pstruWjPositionLL44B->n32lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB22_SIZE < pstruWjPositionLL44B->n32lat) || (WJV4_MIN_OFFSETLLB22_SIZE > pstruWjPositionLL44B->n32lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL44B->n32lat = %d",
                 pstruWjPositionLL44B->n32lat);
        return false;
    }
#endif
    pstruAsnPositionLL44B->lat = pstruWjPositionLL44B->n32lat;
    return true;
}
/**
* @brief     WJV4_PositionLL44B_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL44B_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL44B *pstruWjPositionLL44B = (WJV4_STRU_PositionLL44B *)pvoidWjDf;
    Position_LL_44B_t *pstruAsnPositionLL44B = (Position_LL_44B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB22_SIZE < pstruAsnPositionLL44B->lon) || (WJV4_MIN_OFFSETLLB22_SIZE > pstruAsnPositionLL44B->lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL44B->lon = %d",
                 pstruAsnPositionLL44B->lon);
        return false;
    }
#endif
    pstruWjPositionLL44B->n32lon = pstruAsnPositionLL44B->lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB22_SIZE < pstruAsnPositionLL44B->lat) || (WJV4_MIN_OFFSETLLB22_SIZE > pstruAsnPositionLL44B->lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL44B->lat = %d",
                 pstruAsnPositionLL44B->lat);
        return false;
    }
#endif
    pstruWjPositionLL44B->n32lat = pstruAsnPositionLL44B->lat;
    return true;
}
/**
* @brief     WJV4_PositionLL48B_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL48B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL48B *pstruWjPositionLL48B = (WJV4_STRU_PositionLL48B *)pvoidWjDf;
    Position_LL_48B_t *pstruAsnPositionLL48B = (Position_LL_48B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB24_SIZE < pstruWjPositionLL48B->n32lon) || (WJV4_MIN_OFFSETLLB24_SIZE > pstruWjPositionLL48B->n32lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL48B->n32lon = %d",
                 pstruWjPositionLL48B->n32lon);
        return false;
    }
#endif
    pstruAsnPositionLL48B->lon = pstruWjPositionLL48B->n32lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB24_SIZE < pstruWjPositionLL48B->n32lat) || (WJV4_MIN_OFFSETLLB24_SIZE > pstruWjPositionLL48B->n32lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLL48B->n32lat = %d",
                 pstruWjPositionLL48B->n32lat);
        return false;
    }
#endif
    pstruAsnPositionLL48B->lat = pstruWjPositionLL48B->n32lat;
    return true;
}
/**
* @brief     WJV4_PositionLL48B_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLL48B_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLL48B *pstruWjPositionLL48B = (WJV4_STRU_PositionLL48B *)pvoidWjDf;
    Position_LL_48B_t *pstruAsnPositionLL48B = (Position_LL_48B_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB24_SIZE < pstruAsnPositionLL48B->lon) || (WJV4_MIN_OFFSETLLB24_SIZE > pstruAsnPositionLL48B->lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL48B->lon = %d",
                 pstruAsnPositionLL48B->lon);
        return false;
    }
#endif
    pstruWjPositionLL48B->n32lon = pstruAsnPositionLL48B->lon;
#ifdef _CHECK_
    if ((WJV4_MAX_OFFSETLLB24_SIZE < pstruAsnPositionLL48B->lat) || (WJV4_MIN_OFFSETLLB24_SIZE > pstruAsnPositionLL48B->lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLL48B->lat = %d",
                 pstruAsnPositionLL48B->lat);
        return false;
    }
#endif
    pstruWjPositionLL48B->n32lat = pstruAsnPositionLL48B->lat;
    return true;
}
/**
* @brief     WJV4_PositionLLmD64b_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLLmD64b_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLLmD64b *pstruWjPositionLLmD64b = (WJV4_STRU_PositionLLmD64b *)pvoidWjDf;
    Position_LLmD_64b_t *pstruAsnPositionLLmD64b = (Position_LLmD_64b_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_LONGITUDE_SIZE < pstruWjPositionLLmD64b->n32lon) || (WJV4_MIN_LONGITUDE_SIZE > pstruWjPositionLLmD64b->n32lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLLmD64b->n32lon = %d",
                 pstruWjPositionLLmD64b->n32lon);
        return false;
    }
#endif
    pstruAsnPositionLLmD64b->lon = pstruWjPositionLLmD64b->n32lon;
#ifdef _CHECK_
    if ((WJV4_MAX_LATITUDE_SIZE < pstruWjPositionLLmD64b->n32lat) || (WJV4_MIN_LATITUDE_SIZE > pstruWjPositionLLmD64b->n32lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionLLmD64b->n32lat = %d",
                 pstruWjPositionLLmD64b->n32lat);
        return false;
    }
#endif
    pstruAsnPositionLLmD64b->lat = pstruWjPositionLLmD64b->n32lat;
    return true;
}
/**
* @brief     WJV4_PositionLLmD64b_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionLLmD64b_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionLLmD64b *pstruWjPositionLLmD64b = (WJV4_STRU_PositionLLmD64b *)pvoidWjDf;
    Position_LLmD_64b_t *pstruAsnPositionLLmD64b = (Position_LLmD_64b_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_LONGITUDE_SIZE < pstruAsnPositionLLmD64b->lon) || (WJV4_MIN_LONGITUDE_SIZE > pstruAsnPositionLLmD64b->lon))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLLmD64b->lon = %d",
                 pstruAsnPositionLLmD64b->lon);
        return false;
    }
#endif
    pstruWjPositionLLmD64b->n32lon = pstruAsnPositionLLmD64b->lon;
#ifdef _CHECK_
    if ((WJV4_MAX_LATITUDE_SIZE < pstruAsnPositionLLmD64b->lat) || (WJV4_MIN_LATITUDE_SIZE > pstruAsnPositionLLmD64b->lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionLLmD64b->lat = %d",
                 pstruAsnPositionLLmD64b->lat);
        return false;
    }
#endif
    pstruWjPositionLLmD64b->n32lat = pstruAsnPositionLLmD64b->lat;
    return true;
}
/**
* @brief     WJV4_Position3D_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_Position3D_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Position3D *pstruWjPosition3D = (WJV4_STRU_Position3D *)pvoidWjDf;
    Position3D_t *pstruAsnPosition3D = (Position3D_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_LATITUDE_SIZE < pstruWjPosition3D->n32lat) || (WJV4_MIN_LATITUDE_SIZE > pstruWjPosition3D->n32lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPosition3D->n32lat = %d",
                 pstruWjPosition3D->n32lat);
        return false;
    }
#endif
    pstruAsnPosition3D->lat = pstruWjPosition3D->n32lat;
#ifdef _CHECK_
    if ((WJV4_MAX_LONGITUDE_SIZE < pstruWjPosition3D->n32long) || (WJV4_MIN_LONGITUDE_SIZE > pstruWjPosition3D->n32long))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPosition3D->n32long = %d",
                 pstruWjPosition3D->n32long);
        return false;
    }
#endif
    pstruAsnPosition3D->Long = pstruWjPosition3D->n32long;
    if (WJV4_PRESENT == pstruWjPosition3D->u8elevationPresent)
    {
        pstruAsnPosition3D->elevation = CALLOC(1, sizeof(Elevation_t));
        if (NULL == pstruAsnPosition3D->elevation)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnPosition3D->elevation) = pstruWjPosition3D->n32elevation;
    }
    else
    {
        pstruAsnPosition3D->elevation = NULL;
    }
    return true;
}
/**
* @brief     WJV4_Position3D_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_Position3D_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_Position3D *pstruWjPosition3D = (WJV4_STRU_Position3D *)pvoidWjDf;
    Position3D_t *pstruAsnPosition3D = (Position3D_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_LATITUDE_SIZE < pstruAsnPosition3D->lat) || (WJV4_MIN_LATITUDE_SIZE > pstruAsnPosition3D->lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPosition3D->lat = %d",
                 pstruAsnPosition3D->lat);
        return false;
    }
#endif
    pstruWjPosition3D->n32lat = pstruAsnPosition3D->lat;
#ifdef _CHECK_
    if ((WJV4_MAX_LONGITUDE_SIZE < pstruAsnPosition3D->Long) || (WJV4_MIN_LONGITUDE_SIZE > pstruAsnPosition3D->Long))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPosition3D->Long = %d",
                 pstruAsnPosition3D->Long);
        return false;
    }
#endif
    pstruWjPosition3D->n32long = pstruAsnPosition3D->Long;
    if (NULL != pstruAsnPosition3D->elevation)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_ELEVATION_SIZE < *(pstruAsnPosition3D->elevation)) || (WJV4_MIN_ELEVATION_SIZE > *(pstruAsnPosition3D->elevation)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnPosition3D->elevation) = %d",
                     *(pstruAsnPosition3D->elevation));
            return false;
        };
#endif
        pstruWjPosition3D->n32elevation = *(pstruAsnPosition3D->elevation);
    }
    else
    {
        pstruAsnPosition3D->elevation = NULL;
    }
    return true;
}
/**
* @brief     WJV4_PositionalAccuracy_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionalAccuracy_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionalAccuracy *pstruWjPositionalAccuracy = (WJV4_STRU_PositionalAccuracy *)pvoidWjDf;
    PositionalAccuracy_t *pstruAsnPositionalAccuracy = (PositionalAccuracy_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_SEMIMAJORAXISACCURACY_SIZE < pstruWjPositionalAccuracy->n32semiMajor) || (WJV4_MIN_SEMIMAJORAXISACCURACY_SIZE > pstruWjPositionalAccuracy->n32semiMajor))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionalAccuracy->n32semiMajor = %d",
                 pstruWjPositionalAccuracy->n32semiMajor);
        return false;
    }
#endif
    pstruAsnPositionalAccuracy->semiMajor = pstruWjPositionalAccuracy->n32semiMajor;
#ifdef _CHECK_
    if ((WJV4_MAX_SEMIMINORAXISACCURACY_SIZE < pstruWjPositionalAccuracy->n32semiMinor) || (WJV4_MIN_SEMIMINORAXISACCURACY_SIZE > pstruWjPositionalAccuracy->n32semiMinor))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionalAccuracy->n32semiMinor = %d",
                 pstruWjPositionalAccuracy->n32semiMinor);
        return false;
    }
#endif
    pstruAsnPositionalAccuracy->semiMinor = pstruWjPositionalAccuracy->n32semiMinor;
#ifdef _CHECK_
    if ((WJV4_MAX_SEMIMAJORAXISORIENTATION_SIZE < pstruWjPositionalAccuracy->n32orientation) || (WJV4_MIN_SEMIMAJORAXISORIENTATION_SIZE > pstruWjPositionalAccuracy->n32orientation))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjPositionalAccuracy->n32orientation = %d",
                 pstruWjPositionalAccuracy->n32orientation);
        return false;
    }
#endif
    pstruAsnPositionalAccuracy->orientation = pstruWjPositionalAccuracy->n32orientation;
    return true;
}
/**
* @brief     WJV4_PositionalAccuracy_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionalAccuracy_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionalAccuracy *pstruWjPositionalAccuracy = (WJV4_STRU_PositionalAccuracy *)pvoidWjDf;
    PositionalAccuracy_t *pstruAsnPositionalAccuracy = (PositionalAccuracy_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_SEMIMAJORAXISACCURACY_SIZE < pstruAsnPositionalAccuracy->semiMajor) || (WJV4_MIN_SEMIMAJORAXISACCURACY_SIZE > pstruAsnPositionalAccuracy->semiMajor))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionalAccuracy->semiMajor = %d",
                 pstruAsnPositionalAccuracy->semiMajor);
        return false;
    }
#endif
    pstruWjPositionalAccuracy->n32semiMajor = pstruAsnPositionalAccuracy->semiMajor;
#ifdef _CHECK_
    if ((WJV4_MAX_SEMIMINORAXISACCURACY_SIZE < pstruAsnPositionalAccuracy->semiMinor) || (WJV4_MIN_SEMIMINORAXISACCURACY_SIZE > pstruAsnPositionalAccuracy->semiMinor))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionalAccuracy->semiMinor = %d",
                 pstruAsnPositionalAccuracy->semiMinor);
        return false;
    }
#endif
    pstruWjPositionalAccuracy->n32semiMinor = pstruAsnPositionalAccuracy->semiMinor;
#ifdef _CHECK_
    if ((WJV4_MAX_SEMIMAJORAXISORIENTATION_SIZE < pstruAsnPositionalAccuracy->orientation) || (WJV4_MIN_SEMIMAJORAXISORIENTATION_SIZE > pstruAsnPositionalAccuracy->orientation))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnPositionalAccuracy->orientation = %d",
                 pstruAsnPositionalAccuracy->orientation);
        return false;
    }
#endif
    pstruWjPositionalAccuracy->n32orientation = pstruAsnPositionalAccuracy->orientation;
    return true;
}
/**
* @brief     WJV4_PositionConfidenceSet_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionConfidenceSet_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionConfidenceSet *pstruWjPositionConfidenceSet = (WJV4_STRU_PositionConfidenceSet *)pvoidWjDf;
    PositionConfidenceSet_t *pstruAsnPositionConfidenceSet = (PositionConfidenceSet_t *)pvoidAsnDf;
    pstruAsnPositionConfidenceSet->pos = pstruWjPositionConfidenceSet->enumpos;
    if (WJV4_PRESENT == pstruWjPositionConfidenceSet->u8elevationPresent)
    {
        pstruAsnPositionConfidenceSet->elevation = CALLOC(1, sizeof(ElevationConfidence_t));
        if (NULL == pstruAsnPositionConfidenceSet->elevation)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnPositionConfidenceSet->elevation) = pstruWjPositionConfidenceSet->enumelevation;
    }
    else
    {
        pstruAsnPositionConfidenceSet->elevation = NULL;
    }
    return true;
}
/**
* @brief     WJV4_PositionConfidenceSet_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionConfidenceSet_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionConfidenceSet *pstruWjPositionConfidenceSet = (WJV4_STRU_PositionConfidenceSet *)pvoidWjDf;
    PositionConfidenceSet_t *pstruAsnPositionConfidenceSet = (PositionConfidenceSet_t *)pvoidAsnDf;
    pstruWjPositionConfidenceSet->enumpos = pstruAsnPositionConfidenceSet->pos;
    if (NULL != pstruAsnPositionConfidenceSet->elevation)
    {
        pstruWjPositionConfidenceSet->u8elevationPresent = WJV4_PRESENT;
        *(pstruAsnPositionConfidenceSet->elevation) = pstruWjPositionConfidenceSet->enumelevation;
    }
    else
    {
        pstruWjPositionConfidenceSet->u8elevationPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_PositionOffsetLL_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionOffsetLL_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionOffsetLL *pstruWjPositionOffsetLL = (WJV4_STRU_PositionOffsetLL *)pvoidWjDf;
    PositionOffsetLL_t *pstruAsnPositionOffsetLL = (PositionOffsetLL_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV4_PositionLL24B == pstruWjPositionOffsetLL->enumPositionOffsetLLChoice)
    {
        n32Ret = WJV4_PositionLL24B_DfEnc(&(pstruAsnPositionOffsetLL->choice.position_LL1), &(pstruWjPositionOffsetLL->u.strupositionLL1));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL24B_DfEnc is err");
            return false;
        }
        pstruAsnPositionOffsetLL->present = PositionOffsetLL_PR_position_LL1;
    }
    else if (WJV4_PositionLL28B == pstruWjPositionOffsetLL->enumPositionOffsetLLChoice)
    {
        n32Ret = WJV4_PositionLL28B_DfEnc(&(pstruAsnPositionOffsetLL->choice.position_LL2), &(pstruWjPositionOffsetLL->u.strupositionLL2));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL28B_DfEnc is err");
            return false;
        }
        pstruAsnPositionOffsetLL->present = PositionOffsetLL_PR_position_LL2;
    }
    else if (WJV4_PositionLL32B == pstruWjPositionOffsetLL->enumPositionOffsetLLChoice)
    {
        n32Ret = WJV4_PositionLL32B_DfEnc(&(pstruAsnPositionOffsetLL->choice.position_LL3), &(pstruWjPositionOffsetLL->u.strupositionLL3));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL32B_DfEnc is err");
            return false;
        }
        pstruAsnPositionOffsetLL->present = PositionOffsetLL_PR_position_LL3;
    }
    else if (WJV4_PositionLL36B == pstruWjPositionOffsetLL->enumPositionOffsetLLChoice)
    {
        n32Ret = WJV4_PositionLL36B_DfEnc(&(pstruAsnPositionOffsetLL->choice.position_LL4), &(pstruWjPositionOffsetLL->u.strupositionLL4));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL36B_DfEnc is err");
            return false;
        }
        pstruAsnPositionOffsetLL->present = PositionOffsetLL_PR_position_LL4;
    }
    else if (WJV4_PositionLL44B == pstruWjPositionOffsetLL->enumPositionOffsetLLChoice)
    {
        n32Ret = WJV4_PositionLL44B_DfEnc(&(pstruAsnPositionOffsetLL->choice.position_LL5), &(pstruWjPositionOffsetLL->u.strupositionLL5));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL44B_DfEnc is err");
            return false;
        }
        pstruAsnPositionOffsetLL->present = PositionOffsetLL_PR_position_LL5;
    }
    else if (WJV4_PositionLL48B == pstruWjPositionOffsetLL->enumPositionOffsetLLChoice)
    {
        n32Ret = WJV4_PositionLL48B_DfEnc(&(pstruAsnPositionOffsetLL->choice.position_LL6), &(pstruWjPositionOffsetLL->u.strupositionLL6));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL48B_DfEnc is err");
            return false;
        }
        pstruAsnPositionOffsetLL->present = PositionOffsetLL_PR_position_LL6;
    }
    else if (WJV4_PositionLLmD64b == pstruWjPositionOffsetLL->enumPositionOffsetLLChoice)
    {
        n32Ret = WJV4_PositionLLmD64b_DfEnc(&(pstruAsnPositionOffsetLL->choice.position_LatLon), &(pstruWjPositionOffsetLL->u.strupositionLatLon));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLLmD64b_DfEnc is err");
            return false;
        }
        pstruAsnPositionOffsetLL->present = PositionOffsetLL_PR_position_LatLon;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "choice is err pstruWjPositionOffsetLL->enumPositionOffsetLLChoice = %d",
                 pstruWjPositionOffsetLL->enumPositionOffsetLLChoice);
        return false;
    }
    return true;
}
/**
* @brief     WJV4_PositionOffsetLL_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionOffsetLL_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionOffsetLL *pstruWjPositionOffsetLL = (WJV4_STRU_PositionOffsetLL *)pvoidWjDf;
    PositionOffsetLL_t *pstruAsnPositionOffsetLL = (PositionOffsetLL_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (PositionOffsetLL_PR_position_LL1 == pstruAsnPositionOffsetLL->present)
    {
        n32Ret = WJV4_PositionLL24B_DfDec(&(pstruAsnPositionOffsetLL->choice.position_LL1), &(pstruWjPositionOffsetLL->u.strupositionLL1));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL24B_DfDec is err");
            return false;
        }
        pstruWjPositionOffsetLL->enumPositionOffsetLLChoice = WJV4_PositionLL24B;
    }
    else if (PositionOffsetLL_PR_position_LL2 == pstruAsnPositionOffsetLL->present)
    {
        n32Ret = WJV4_PositionLL28B_DfDec(&(pstruAsnPositionOffsetLL->choice.position_LL2), &(pstruWjPositionOffsetLL->u.strupositionLL2));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL28B_DfDec is err");
            return false;
        }
        pstruWjPositionOffsetLL->enumPositionOffsetLLChoice = WJV4_PositionLL28B;
    }
    else if (PositionOffsetLL_PR_position_LL3 == pstruAsnPositionOffsetLL->present)
    {
        n32Ret = WJV4_PositionLL32B_DfDec(&(pstruAsnPositionOffsetLL->choice.position_LL3), &(pstruWjPositionOffsetLL->u.strupositionLL3));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL32B_DfDec is err");
            return false;
        }
        pstruWjPositionOffsetLL->enumPositionOffsetLLChoice = WJV4_PositionLL32B;
    }
    else if (PositionOffsetLL_PR_position_LL4 == pstruAsnPositionOffsetLL->present)
    {
        n32Ret = WJV4_PositionLL36B_DfDec(&(pstruAsnPositionOffsetLL->choice.position_LL4), &(pstruWjPositionOffsetLL->u.strupositionLL4));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL36B_DfDec is err");
            return false;
        }
        pstruWjPositionOffsetLL->enumPositionOffsetLLChoice = WJV4_PositionLL36B;
    }
    else if (PositionOffsetLL_PR_position_LL5 == pstruAsnPositionOffsetLL->present)
    {
        n32Ret = WJV4_PositionLL44B_DfDec(&(pstruAsnPositionOffsetLL->choice.position_LL5), &(pstruWjPositionOffsetLL->u.strupositionLL5));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL44B_DfDec is err");
            return false;
        }
        pstruWjPositionOffsetLL->enumPositionOffsetLLChoice = WJV4_PositionLL44B;
    }
    else if (PositionOffsetLL_PR_position_LL6 == pstruAsnPositionOffsetLL->present)
    {
        n32Ret = WJV4_PositionLL48B_DfDec(&(pstruAsnPositionOffsetLL->choice.position_LL6), &(pstruWjPositionOffsetLL->u.strupositionLL6));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLL48B_DfDec is err");
            return false;
        }
        pstruWjPositionOffsetLL->enumPositionOffsetLLChoice = WJV4_PositionLL48B;
    }
    else if (PositionOffsetLL_PR_position_LatLon == pstruAsnPositionOffsetLL->present)
    {
        n32Ret = WJV4_PositionLLmD64b_DfDec(&(pstruAsnPositionOffsetLL->choice.position_LatLon), &(pstruWjPositionOffsetLL->u.strupositionLatLon));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionLLmD64b_DfDec is err");
            return false;
        }
        pstruWjPositionOffsetLL->enumPositionOffsetLLChoice = WJV4_PositionLLmD64b;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "choice is err pstruAsnPositionOffsetLL->present = %d",
                 pstruAsnPositionOffsetLL->present);
        return false;
    }
    return true;
}
/**
* @brief     WJV4_PositionOffsetLLV_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionOffsetLLV_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionOffsetLLV *pstruWjPositionOffsetLLV = (WJV4_STRU_PositionOffsetLLV *)pvoidWjDf;
    PositionOffsetLLV_t *pstruAsnPositionOffsetLLV = (PositionOffsetLLV_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_PositionOffsetLL_DfEnc(&(pstruAsnPositionOffsetLLV->offsetLL), &(pstruWjPositionOffsetLLV->struoffsetLL));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PositionOffsetLL_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjPositionOffsetLLV->u8offsetVPresent)
    {
        pstruAsnPositionOffsetLLV->offsetV = CALLOC(1, sizeof(struct VerticalOffset));
        if (NULL == pstruAsnPositionOffsetLLV->offsetV)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_VerticalOffset_DfEnc(pstruAsnPositionOffsetLLV->offsetV, &(pstruWjPositionOffsetLLV->struoffsetV));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_VerticalOffset_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPositionOffsetLLV->offsetV = NULL;
    }
    return true;
}
/**
* @brief     WJV4_PositionOffsetLLV_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_PositionOffsetLLV_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_PositionOffsetLLV *pstruWjPositionOffsetLLV = (WJV4_STRU_PositionOffsetLLV *)pvoidWjDf;
    PositionOffsetLLV_t *pstruAsnPositionOffsetLLV = (PositionOffsetLLV_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_PositionOffsetLL_DfDec(&(pstruAsnPositionOffsetLLV->offsetLL), &(pstruWjPositionOffsetLLV->struoffsetLL));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PositionOffsetLL_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnPositionOffsetLLV->offsetV)
    {
        n32Ret = WJV4_VerticalOffset_DfDec(pstruAsnPositionOffsetLLV->offsetV, &(pstruWjPositionOffsetLLV->struoffsetV));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_VerticalOffset_DfDec is err");
            return false;
        }
        pstruWjPositionOffsetLLV->u8offsetVPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjPositionOffsetLLV->u8offsetVPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_ReferenceLink_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_ReferenceLink_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ReferenceLink *pstruWjReferenceLink = (WJV4_STRU_ReferenceLink *)pvoidWjDf;
    ReferenceLink_t *pstruAsnReferenceLink = (ReferenceLink_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_NodeReferenceID_DfEnc(&(pstruAsnReferenceLink->upstreamNodeId), &(pstruWjReferenceLink->struupstreamNodeId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfEnc is err");
        return false;
    }
    n32Ret = WJV4_NodeReferenceID_DfEnc(&(pstruAsnReferenceLink->downstreamNodeId), &(pstruWjReferenceLink->strudownstreamNodeId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfEnc is err");
        return false;
    }
    if (WJV4_PRESENT == pstruWjReferenceLink->u8referenceLanesPresent)
    {
        pstruAsnReferenceLink->referenceLanes = CALLOC(1, sizeof(ReferenceLanes_t));
        if (NULL == pstruAsnReferenceLink->referenceLanes)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_ReferenceLanes_DeEnc(pstruAsnReferenceLink->referenceLanes, &(pstruWjReferenceLink->strbitreferenceLanes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferenceLanes_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnReferenceLink->referenceLanes = NULL;
    }
    return true;
}
/**
* @brief     WJV4_ReferenceLink_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_ReferenceLink_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ReferenceLink *pstruWjReferenceLink = (WJV4_STRU_ReferenceLink *)pvoidWjDf;
    ReferenceLink_t *pstruAsnReferenceLink = (ReferenceLink_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_NodeReferenceID_DfDec(&(pstruAsnReferenceLink->upstreamNodeId), &(pstruWjReferenceLink->struupstreamNodeId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfDec is err");
        return false;
    }
    n32Ret = WJV4_NodeReferenceID_DfDec(&(pstruAsnReferenceLink->downstreamNodeId), &(pstruWjReferenceLink->strudownstreamNodeId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_NodeReferenceID_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnReferenceLink->referenceLanes)
    {
        n32Ret = WJV4_ReferenceLanes_DeDec(pstruAsnReferenceLink->referenceLanes, &(pstruWjReferenceLink->strbitreferenceLanes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferenceLanes_DeDec is err");
            return false;
        }
        pstruWjReferenceLink->u8referenceLanesPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjReferenceLink->u8referenceLanesPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_ReferenceLinkList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_ReferenceLinkList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ReferenceLinkList *pstruWjReferenceLinkList = (WJV4_STRU_ReferenceLinkList *)pvoidWjDf;
    ReferenceLinkList_t *pstruAsnReferenceLinkList = (ReferenceLinkList_t *)pvoidAsnDf;
    ReferenceLink_t *pstruReferenceLink_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_REFERENCELINK_LEN < pstruWjReferenceLinkList->u8ReferenceLinkNum) || (WJV4_MIN_LIST_REFERENCELINK_LEN > pstruWjReferenceLinkList->u8ReferenceLinkNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjReferenceLinkList->u8ReferenceLinkNum = %d",
                 pstruWjReferenceLinkList->u8ReferenceLinkNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjReferenceLinkList->u8ReferenceLinkNum; u32i++)
    {
        pstruReferenceLink_node = CALLOC(1, sizeof(ReferenceLink_t));
        if (NULL == pstruReferenceLink_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_ReferenceLink_DfEnc(pstruReferenceLink_node, &(pstruWjReferenceLinkList->struReferenceLink[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferenceLink_DfEnc is err");
            FREEMEM(pstruReferenceLink_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnReferenceLinkList->list), pstruReferenceLink_node);
    }
    return true;
}
/**
* @brief     WJV4_ReferenceLinkList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_ReferenceLinkList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ReferenceLinkList *pstruWjReferenceLinkList = (WJV4_STRU_ReferenceLinkList *)pvoidWjDf;
    ReferenceLinkList_t *pstruAsnReferenceLinkList = (ReferenceLinkList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_REFERENCELINK_LEN < pstruAsnReferenceLinkList->list.count) || (WJV4_MIN_LIST_REFERENCELINK_LEN > pstruAsnReferenceLinkList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnReferenceLinkList->list.count = %d",
                 pstruAsnReferenceLinkList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnReferenceLinkList->list.count; u32i++)
    {
        n32Ret = WJV4_ReferenceLink_DfDec(pstruAsnReferenceLinkList->list.array[u32i],
                                          &(pstruWjReferenceLinkList->struReferenceLink[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferenceLink_DfDec is err");
            return false;
        }
    }
    pstruWjReferenceLinkList->u8ReferenceLinkNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_ReferencePath_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_ReferencePath_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ReferencePath *pstruWjReferencePath = (WJV4_STRU_ReferencePath *)pvoidWjDf;
    ReferencePath_t *pstruAsnReferencePath = (ReferencePath_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_PathPointList_DfEnc(&(pstruAsnReferencePath->activePath), &(pstruWjReferencePath->struactivePath));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PathPointList_DfEnc is err");
        return false;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_RADIUS_SIZE < pstruWjReferencePath->n32pathRadius) || (WJV4_MIN_RADIUS_SIZE > pstruWjReferencePath->n32pathRadius))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjReferencePath->n32pathRadius = %d",
                 pstruWjReferencePath->n32pathRadius);
        return false;
    }
#endif
    pstruAsnReferencePath->pathRadius = pstruWjReferencePath->n32pathRadius;
    return true;
}
/**
* @brief     WJV4_ReferencePath_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_ReferencePath_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ReferencePath *pstruWjReferencePath = (WJV4_STRU_ReferencePath *)pvoidWjDf;
    ReferencePath_t *pstruAsnReferencePath = (ReferencePath_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_PathPointList_DfDec(&(pstruAsnReferencePath->activePath), &(pstruWjReferencePath->struactivePath));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PathPointList_DfDec is err");
        return false;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_RADIUS_SIZE < pstruAsnReferencePath->pathRadius) || (WJV4_MIN_RADIUS_SIZE > pstruAsnReferencePath->pathRadius))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnReferencePath->pathRadius = %d",
                 pstruAsnReferencePath->pathRadius);
        return false;
    }
#endif
    pstruWjReferencePath->n32pathRadius = pstruAsnReferencePath->pathRadius;
    return true;
}
/**
* @brief     WJV4_ReferencePathList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_ReferencePathList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ReferencePathList *pstruWjReferencePathList = (WJV4_STRU_ReferencePathList *)pvoidWjDf;
    ReferencePathList_t *pstruAsnReferencePathList = (ReferencePathList_t *)pvoidAsnDf;
    ReferencePath_t *pstruReferencePath_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_REFERENCEPATH_LEN < pstruWjReferencePathList->u8ReferencePathNum) || (WJV4_MIN_LIST_REFERENCEPATH_LEN > pstruWjReferencePathList->u8ReferencePathNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjReferencePathList->u8ReferencePathNum = %d",
                 pstruWjReferencePathList->u8ReferencePathNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjReferencePathList->u8ReferencePathNum; u32i++)
    {
        pstruReferencePath_node = CALLOC(1, sizeof(ReferencePath_t));
        if (NULL == pstruReferencePath_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_ReferencePath_DfEnc(pstruReferencePath_node, &(pstruWjReferencePathList->struReferencePath[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferencePath_DfEnc is err");
            FREEMEM(pstruReferencePath_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnReferencePathList->list), pstruReferencePath_node);
    }
    return true;
}
/**
* @brief     WJV4_ReferencePathList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_ReferencePathList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_ReferencePathList *pstruWjReferencePathList = (WJV4_STRU_ReferencePathList *)pvoidWjDf;
    ReferencePathList_t *pstruAsnReferencePathList = (ReferencePathList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_REFERENCEPATH_LEN < pstruAsnReferencePathList->list.count) || (WJV4_MIN_LIST_REFERENCEPATH_LEN > pstruAsnReferencePathList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnReferencePathList->list.count = %d",
                 pstruAsnReferencePathList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnReferencePathList->list.count; u32i++)
    {
        n32Ret = WJV4_ReferencePath_DfDec(pstruAsnReferencePathList->list.array[u32i],
                                          &(pstruWjReferencePathList->struReferencePath[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferencePath_DfDec is err");
            return false;
        }
    }
    pstruWjReferencePathList->u8ReferencePathNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_RegulatorySpeedLimit_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RegulatorySpeedLimit_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RegulatorySpeedLimit *pstruWjRegulatorySpeedLimit = (WJV4_STRU_RegulatorySpeedLimit *)pvoidWjDf;
    RegulatorySpeedLimit_t *pstruAsnRegulatorySpeedLimit = (RegulatorySpeedLimit_t *)pvoidAsnDf;
    pstruAsnRegulatorySpeedLimit->type = pstruWjRegulatorySpeedLimit->enumtype;
#ifdef _CHECK_
    if ((WJV4_MAX_SPEED_SIZE < pstruWjRegulatorySpeedLimit->n32speed) || (WJV4_MIN_SPEED_SIZE > pstruWjRegulatorySpeedLimit->n32speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjRegulatorySpeedLimit->n32speed = %d",
                 pstruWjRegulatorySpeedLimit->n32speed);
        return false;
    }
#endif
    pstruAsnRegulatorySpeedLimit->speed = pstruWjRegulatorySpeedLimit->n32speed;
    return true;
}
/**
* @brief     WJV4_RegulatorySpeedLimit_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RegulatorySpeedLimit_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RegulatorySpeedLimit *pstruWjRegulatorySpeedLimit = (WJV4_STRU_RegulatorySpeedLimit *)pvoidWjDf;
    RegulatorySpeedLimit_t *pstruAsnRegulatorySpeedLimit = (RegulatorySpeedLimit_t *)pvoidAsnDf;
    pstruWjRegulatorySpeedLimit->enumtype = pstruAsnRegulatorySpeedLimit->type;
#ifdef _CHECK_
    if ((WJV4_MAX_SPEED_SIZE < pstruAsnRegulatorySpeedLimit->speed) || (WJV4_MIN_SPEED_SIZE > pstruAsnRegulatorySpeedLimit->speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnRegulatorySpeedLimit->speed = %d",
                 pstruAsnRegulatorySpeedLimit->speed);
        return false;
    }
#endif
    pstruWjRegulatorySpeedLimit->n32speed = pstruAsnRegulatorySpeedLimit->speed;
    return true;
}
/**
* @brief     WJV4_RSITimeDetails_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RSITimeDetails_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RSITimeDetails *pstruWjRSITimeDetails = (WJV4_STRU_RSITimeDetails *)pvoidWjDf;
    RSITimeDetails_t *pstruAsnRSITimeDetails = (RSITimeDetails_t *)pvoidAsnDf;
    if (WJV4_PRESENT == pstruWjRSITimeDetails->u8startTimePresent)
    {
        pstruAsnRSITimeDetails->startTime = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnRSITimeDetails->startTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjRSITimeDetails->n32startTime) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjRSITimeDetails->n32startTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjRSITimeDetails->n32startTime = %d",
                     pstruWjRSITimeDetails->n32startTime);
            return false;
        }
#endif
        *(pstruAsnRSITimeDetails->startTime) = pstruWjRSITimeDetails->n32startTime;
    }
    else
    {
        pstruAsnRSITimeDetails->startTime = NULL;
    }
    if (WJV4_PRESENT == pstruWjRSITimeDetails->u8endTimePresent)
    {
        pstruAsnRSITimeDetails->endTime = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnRSITimeDetails->endTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjRSITimeDetails->n32endTime) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjRSITimeDetails->n32endTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjRSITimeDetails->n32endTime = %d",
                     pstruWjRSITimeDetails->n32endTime);
            return false;
        }
#endif
        *(pstruAsnRSITimeDetails->endTime) = pstruWjRSITimeDetails->n32endTime;
    }
    else
    {
        pstruAsnRSITimeDetails->endTime = NULL;
    }
    if (WJV4_PRESENT == pstruWjRSITimeDetails->u8endTimeConfidencePresent)
    {
        pstruAsnRSITimeDetails->endTimeConfidence = CALLOC(1, sizeof(TimeConfidence_t));
        if (NULL == pstruAsnRSITimeDetails->endTimeConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnRSITimeDetails->endTimeConfidence) = pstruWjRSITimeDetails->enumendTimeConfidence;
    }
    else
    {
        pstruAsnRSITimeDetails->endTimeConfidence = NULL;
    }
    return true;
}
/**
* @brief     WJV4_RSITimeDetails_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RSITimeDetails_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RSITimeDetails *pstruWjRSITimeDetails = (WJV4_STRU_RSITimeDetails *)pvoidWjDf;
    RSITimeDetails_t *pstruAsnRSITimeDetails = (RSITimeDetails_t *)pvoidAsnDf;
    if (NULL != pstruAsnRSITimeDetails->startTime)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnRSITimeDetails->startTime)) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnRSITimeDetails->startTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnRSITimeDetails->startTime) = %d",
                     *(pstruAsnRSITimeDetails->startTime));
            return false;
        }
#endif
        pstruWjRSITimeDetails->n32startTime = *(pstruAsnRSITimeDetails->startTime);
        pstruWjRSITimeDetails->u8startTimePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRSITimeDetails->u8startTimePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRSITimeDetails->endTime)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnRSITimeDetails->endTime)) || (WJV4_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnRSITimeDetails->endTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnRSITimeDetails->endTime) = %d",
                     *(pstruAsnRSITimeDetails->endTime));
            return false;
        }
#endif
        pstruWjRSITimeDetails->n32endTime = *(pstruAsnRSITimeDetails->endTime);
        pstruWjRSITimeDetails->u8endTimePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRSITimeDetails->u8endTimePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRSITimeDetails->endTimeConfidence)
    {
        pstruWjRSITimeDetails->enumendTimeConfidence = *(pstruAsnRSITimeDetails->endTimeConfidence);
        pstruWjRSITimeDetails->u8endTimeConfidencePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRSITimeDetails->u8endTimeConfidencePresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_RTEData_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RTEData_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RTEData *pstruWjRTEData = (WJV4_STRU_RTEData *)pvoidWjDf;
    RTEData_t *pstruAsnRTEData = (RTEData_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_RTEID_SIZE < pstruWjRTEData->u8rteId) || (WJV4_MIN_RTEID_SIZE > pstruWjRTEData->u8rteId))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjRTEData->u8rteId = %d",
                 pstruWjRTEData->u8rteId);
        return false;
    }
#endif
    pstruAsnRTEData->rteId = pstruWjRTEData->u8rteId;
#ifdef _CHECK_
    if ((WJV4_MAX_EVENTTYPE_SIZE < pstruWjRTEData->n32eventType) || (WJV4_MIN_EVENTTYPE_SIZE > pstruWjRTEData->n32eventType))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjRTEData->n32eventType = %d",
                 pstruWjRTEData->n32eventType);
        return false;
    }
#endif
    pstruAsnRTEData->eventType = pstruWjRTEData->n32eventType;
    pstruAsnRTEData->eventSource = pstruWjRTEData->enumeventSource;
    if (WJV4_PRESENT == pstruWjRTEData->u8eventPosPresent)
    {
        pstruAsnRTEData->eventPos = CALLOC(1, sizeof(struct PositionOffsetLLV));
        if (NULL == pstruAsnRTEData->eventPos)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_PositionOffsetLLV_DfEnc(pstruAsnRTEData->eventPos, &(pstruWjRTEData->strueventPos));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionOffsetLLV_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTEData->eventPos = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTEData->u8eventRadiusPresent)
    {
        pstruAsnRTEData->eventRadius = CALLOC(1, sizeof(Radius_t));
        if (NULL == pstruAsnRTEData->eventRadius)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_RADIUS_SIZE < pstruWjRTEData->n32eventRadius) || (WJV4_MIN_RADIUS_SIZE > pstruWjRTEData->n32eventRadius))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjRTEData->n32eventRadius = %d",
                     pstruWjRTEData->n32eventRadius);
            return false;
        }
#endif
        *(pstruAsnRTEData->eventRadius) = pstruWjRTEData->n32eventRadius;
    }
    else
    {
        pstruAsnRTEData->eventPos = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTEData->u8descriptionPresent)
    {
        pstruAsnRTEData->description = CALLOC(1, sizeof(struct Description));
        if (NULL == pstruAsnRTEData->description)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_Description_DfEnc(pstruAsnRTEData->description, &(pstruWjRTEData->strudescription));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Description_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTEData->description = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTEData->u8timeDetailsPresent)
    {
        pstruAsnRTEData->timeDetails = CALLOC(1, sizeof(struct RSITimeDetails));
        if (NULL == pstruAsnRTEData->timeDetails)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_RSITimeDetails_DfEnc(pstruAsnRTEData->timeDetails, &(pstruWjRTEData->strutimeDetails));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RSITimeDetails_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTEData->timeDetails = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTEData->u8priorityPresent)
    {
        pstruAsnRTEData->priority = CALLOC(1, sizeof(RSIPriority_t));
        if (NULL == pstruAsnRTEData->priority)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_RSIPriority_DeEnc(pstruAsnRTEData->priority, &(pstruWjRTEData->stria5priority));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RSIPriority_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTEData->priority = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTEData->u8referencePathsPresent)
    {
        pstruAsnRTEData->referencePaths = CALLOC(1, sizeof(struct ReferencePathList));
        if (NULL == pstruAsnRTEData->referencePaths)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_ReferencePathList_DfEnc(pstruAsnRTEData->referencePaths, &(pstruWjRTEData->strureferencePaths));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferencePathList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTEData->referencePaths = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTEData->u8referenceLinksPresent)
    {
        pstruAsnRTEData->referenceLinks = CALLOC(1, sizeof(struct ReferenceLinkList));
        if (NULL == pstruAsnRTEData->referenceLinks)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_ReferenceLinkList_DfEnc(pstruAsnRTEData->referenceLinks, &(pstruWjRTEData->strureferenceLinks));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferenceLinkList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTEData->referenceLinks = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTEData->u8eventConfidencePresent)
    {
        pstruAsnRTEData->eventConfidence = CALLOC(1, sizeof(Confidence_t));
        if (NULL == pstruAsnRTEData->eventConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_CONFIDENCE_SIZE < pstruWjRTEData->n32eventConfidence) || (WJV4_MIN_CONFIDENCE_SIZE > pstruWjRTEData->n32eventConfidence))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjRTEData->n32eventConfidence = %d",
                     pstruWjRTEData->n32eventConfidence);
            return false;
        }
#endif
        *(pstruAsnRTEData->eventConfidence) = pstruWjRTEData->n32eventConfidence;
    }
    else
    {
        pstruAsnRTEData->eventConfidence = NULL;
    }
    return true;
}
/**
* @brief     WJV4_RTEData_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RTEData_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RTEData *pstruWjRTEData = (WJV4_STRU_RTEData *)pvoidWjDf;
    RTEData_t *pstruAsnRTEData = (RTEData_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_RTEID_SIZE < pstruAsnRTEData->rteId) || (WJV4_MIN_RTEID_SIZE > pstruAsnRTEData->rteId))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnRTEData->rteId = %d",
                 pstruAsnRTEData->rteId);
        return false;
    }
#endif
    pstruWjRTEData->u8rteId = pstruAsnRTEData->rteId;
#ifdef _CHECK_
    if ((WJV4_MAX_EVENTTYPE_SIZE < pstruAsnRTEData->eventType) || (WJV4_MIN_EVENTTYPE_SIZE > pstruAsnRTEData->eventType))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnRTEData->eventType = %d",
                 pstruAsnRTEData->eventType);
        return false;
    }
#endif
    pstruWjRTEData->n32eventType = pstruAsnRTEData->eventType;
    pstruWjRTEData->enumeventSource = pstruAsnRTEData->eventSource;
    if (NULL != pstruAsnRTEData->eventPos)
    {
        n32Ret = WJV4_PositionOffsetLLV_DfDec(pstruAsnRTEData->eventPos, &(pstruWjRTEData->strueventPos));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionOffsetLLV_DfDec is err");
            return false;
        }
        pstruWjRTEData->u8eventPosPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTEData->u8eventPosPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTEData->eventRadius)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_RADIUS_SIZE < *(pstruAsnRTEData->eventRadius)) || (WJV4_MIN_RADIUS_SIZE > *(pstruAsnRTEData->eventRadius)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnRTEData->eventRadius) = %d",
                     *(pstruAsnRTEData->eventRadius));
            return false;
        }
#endif
        pstruWjRTEData->n32eventRadius = *(pstruAsnRTEData->eventRadius);
        pstruWjRTEData->u8eventRadiusPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTEData->u8eventRadiusPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTEData->description)
    {
        n32Ret = WJV4_Description_DfDec(pstruAsnRTEData->description, &(pstruWjRTEData->strudescription));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Description_DfDec is err");
            return false;
        }
        pstruWjRTEData->u8descriptionPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTEData->u8descriptionPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTEData->timeDetails)
    {
        n32Ret = WJV4_RSITimeDetails_DfDec(pstruAsnRTEData->timeDetails, &(pstruWjRTEData->strutimeDetails));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RSITimeDetails_DfDec is err");
            return false;
        }
        pstruWjRTEData->u8timeDetailsPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTEData->u8timeDetailsPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTEData->priority)
    {
        n32Ret = WJV4_RSIPriority_DeDec(pstruAsnRTEData->priority, &(pstruWjRTEData->stria5priority));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RSIPriority_DeDec is err");
            return false;
        }
        pstruWjRTEData->u8priorityPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTEData->u8priorityPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTEData->referencePaths)
    {
        n32Ret = WJV4_ReferencePathList_DfDec(pstruAsnRTEData->referencePaths, &(pstruWjRTEData->strureferencePaths));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferencePathList_DfDec is err");
            return false;
        }
        pstruWjRTEData->u8referencePathsPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTEData->u8referencePathsPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTEData->referenceLinks)
    {
        n32Ret = WJV4_ReferenceLinkList_DfDec(pstruAsnRTEData->referenceLinks, &(pstruWjRTEData->strureferenceLinks));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferenceLinkList_DfDec is err");
            return false;
        }
        pstruWjRTEData->u8referenceLinksPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTEData->u8referenceLinksPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTEData->eventConfidence)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_CONFIDENCE_SIZE < *(pstruAsnRTEData->eventConfidence)) || (WJV4_MIN_CONFIDENCE_SIZE > *(pstruAsnRTEData->eventConfidence)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnRTEData->eventConfidence) = %d",
                     *(pstruAsnRTEData->eventConfidence));
            return false;
        }
#endif
        pstruWjRTEData->n32eventConfidence = *(pstruAsnRTEData->eventConfidence);
        pstruWjRTEData->u8eventConfidencePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTEData->u8eventConfidencePresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_RTEList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RTEList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RTEList *pstruWjRTEList = (WJV4_STRU_RTEList *)pvoidWjDf;
    RTEList_t *pstruAsnRTEList = (RTEList_t *)pvoidAsnDf;
    RTEData_t *pstruRTEData_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_RTEDATA_LEN < pstruWjRTEList->u8RTEDataNum) || (WJV4_MIN_LIST_RTEDATA_LEN > pstruWjRTEList->u8RTEDataNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjRTEList->u8RTEDataNum = %d",
                 pstruWjRTEList->u8RTEDataNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjRTEList->u8RTEDataNum; u32i++)
    {
        pstruRTEData_node = CALLOC(1, sizeof(RTEData_t));
        if (NULL == pstruRTEData_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_RTEData_DfEnc(pstruRTEData_node, &(pstruWjRTEList->struRTEData[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RTEData_DfEnc is err");
            FREEMEM(pstruRTEData_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnRTEList->list), pstruRTEData_node);
    }
    return true;
}
/**
* @brief     WJV4_RTEList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RTEList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RTEList *pstruWjRTEList = (WJV4_STRU_RTEList *)pvoidWjDf;
    RTEList_t *pstruAsnRTEList = (RTEList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_RTEDATA_LEN < pstruAsnRTEList->list.count) || (WJV4_MIN_LIST_RTEDATA_LEN > pstruAsnRTEList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnRTEList->list.count = %d",
                 pstruAsnRTEList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnRTEList->list.count; u32i++)
    {
        n32Ret = WJV4_RTEData_DfDec(pstruAsnRTEList->list.array[u32i],
                                    &(pstruWjRTEList->struRTEData[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RTEData_DfDec is err");
            return false;
        }
    }
    pstruWjRTEList->u8RTEDataNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_RTSData_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RTSData_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RTSData *pstruWjRTSData = (WJV4_STRU_RTSData *)pvoidWjDf;
    RTSData_t *pstruAsnRTSData = (RTSData_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_RTSID_SIZE < pstruWjRTSData->u8rtsId) || (WJV4_MIN_RTSID_SIZE > pstruWjRTSData->u8rtsId))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjRTSData->u8rtsId = %d",
                 pstruWjRTSData->u8rtsId);
        return false;
    }
#endif
    pstruAsnRTSData->rtsId = pstruWjRTSData->u8rtsId;
#ifdef _CHECK_
    if ((WJV4_MAX_SIGNTYPE_SIZE < pstruWjRTSData->n32signType) || (WJV4_MIN_SIGNTYPE_SIZE > pstruWjRTSData->n32signType))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjRTSData->n32signType = %d",
                 pstruWjRTSData->n32signType);
        return false;
    }
#endif
    pstruAsnRTSData->signType = pstruWjRTSData->n32signType;
    if (WJV4_PRESENT == pstruWjRTSData->u8signPosPresent)
    {
        pstruAsnRTSData->signPos = CALLOC(1, sizeof(struct PositionOffsetLLV));
        if (NULL == pstruAsnRTSData->signPos)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_PositionOffsetLLV_DfEnc(pstruAsnRTSData->signPos, &(pstruWjRTSData->strusignPos));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionOffsetLLV_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTSData->signPos = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTSData->u8descriptionPresent)
    {
        pstruAsnRTSData->description = CALLOC(1, sizeof(struct Description));
        if (NULL == pstruAsnRTSData->description)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_Description_DfEnc(pstruAsnRTSData->description, &(pstruWjRTSData->strudescription));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Description_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTSData->description = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTSData->u8timeDetailsPresent)
    {
        pstruAsnRTSData->timeDetails = CALLOC(1, sizeof(struct RSITimeDetails));
        if (NULL == pstruAsnRTSData->timeDetails)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_RSITimeDetails_DfEnc(pstruAsnRTSData->timeDetails, &(pstruWjRTSData->strutimeDetails));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RSITimeDetails_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTSData->timeDetails = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTSData->u8priorityPresent)
    {
        pstruAsnRTSData->priority = CALLOC(1, sizeof(RSIPriority_t));
        if (NULL == pstruAsnRTSData->priority)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_RSIPriority_DeEnc(pstruAsnRTSData->priority, &(pstruWjRTSData->stria5priority));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RSIPriority_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTSData->priority = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTSData->u8referencePathsPresent)
    {
        pstruAsnRTSData->referencePaths = CALLOC(1, sizeof(struct ReferencePathList));
        if (NULL == pstruAsnRTSData->referencePaths)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_ReferencePathList_DfEnc(pstruAsnRTSData->referencePaths, &(pstruWjRTSData->strureferencePaths));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferencePathList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTSData->referencePaths = NULL;
    }
    if (WJV4_PRESENT == pstruWjRTSData->u8referenceLinksPresent)
    {
        pstruAsnRTSData->referenceLinks = CALLOC(1, sizeof(struct ReferenceLinkList));
        if (NULL == pstruAsnRTSData->referenceLinks)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_ReferenceLinkList_DfEnc(pstruAsnRTSData->referenceLinks, &(pstruWjRTSData->strureferenceLinks));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferenceLinkList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnRTSData->referenceLinks = NULL;
    }
    return true;
}
/**
* @brief     WJV4_RTSData_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RTSData_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RTSData *pstruWjRTSData = (WJV4_STRU_RTSData *)pvoidWjDf;
    RTSData_t *pstruAsnRTSData = (RTSData_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_RTSID_SIZE < pstruAsnRTSData->rtsId) || (WJV4_MIN_RTSID_SIZE > pstruAsnRTSData->rtsId))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnRTSData->rtsId = %d",
                 pstruAsnRTSData->rtsId);
        return false;
    }
#endif
    pstruWjRTSData->u8rtsId = pstruAsnRTSData->rtsId;
#ifdef _CHECK_
    if ((WJV4_MAX_SIGNTYPE_SIZE < pstruAsnRTSData->signType) || (WJV4_MIN_SIGNTYPE_SIZE > pstruAsnRTSData->signType))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnRTSData->signType = %d",
                 pstruAsnRTSData->signType);
        return false;
    }
#endif
    pstruWjRTSData->n32signType = pstruAsnRTSData->signType;
    if (NULL != pstruAsnRTSData->signPos)
    {
        n32Ret = WJV4_PositionOffsetLLV_DfDec(pstruAsnRTSData->signPos, &(pstruWjRTSData->strusignPos));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PositionOffsetLLV_DfDec is err");
            return false;
        }
        pstruWjRTSData->u8signPosPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTSData->u8signPosPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTSData->description)
    {
        n32Ret = WJV4_Description_DfDec(pstruAsnRTSData->description, &(pstruWjRTSData->strudescription));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_Description_DfDec is err");
            return false;
        }
        pstruWjRTSData->u8descriptionPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTSData->u8descriptionPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTSData->timeDetails)
    {
        n32Ret = WJV4_RSITimeDetails_DfDec(pstruAsnRTSData->timeDetails, &(pstruWjRTSData->strutimeDetails));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RSITimeDetails_DfDec is err");
            return false;
        }
        pstruWjRTSData->u8timeDetailsPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTSData->u8timeDetailsPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTSData->priority)
    {
        n32Ret = WJV4_RSIPriority_DeDec(pstruAsnRTSData->priority, &(pstruWjRTSData->stria5priority));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RSIPriority_DeDec is err");
            return false;
        }
        pstruWjRTSData->u8priorityPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTSData->u8priorityPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTSData->referencePaths)
    {
        n32Ret = WJV4_ReferencePathList_DfDec(pstruAsnRTSData->referencePaths, &(pstruWjRTSData->strureferencePaths));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferencePathList_DfDec is err");
            return false;
        }
        pstruWjRTSData->u8referencePathsPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTSData->u8referencePathsPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnRTSData->referenceLinks)
    {
        n32Ret = WJV4_ReferenceLinkList_DfDec(pstruAsnRTSData->referenceLinks, &(pstruWjRTSData->strureferenceLinks));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ReferenceLinkList_DfDec is err");
            return false;
        }
        pstruWjRTSData->u8referenceLinksPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjRTSData->u8referenceLinksPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_RTSList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RTSList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RTSList *pstruWjRTSList = (WJV4_STRU_RTSList *)pvoidWjDf;
    RTSList_t *pstruAsnRTSList = (RTSList_t *)pvoidAsnDf;
    RTSData_t *pstruRTSData_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_RTSDATA_LEN < pstruWjRTSList->u8RTSDataNum) || (WJV4_MIN_LIST_RTSDATA_LEN > pstruWjRTSList->u8RTSDataNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjRTSList->u8RTSDataNum = %d",
                 pstruWjRTSList->u8RTSDataNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjRTSList->u8RTSDataNum; u32i++)
    {
        pstruRTSData_node = CALLOC(1, sizeof(RTSData_t));
        if (NULL == pstruRTSData_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_RTSData_DfEnc(pstruRTSData_node, &(pstruWjRTSList->struRTSData[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RTSData_DfEnc is err");
            FREEMEM(pstruRTSData_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnRTSList->list), pstruRTSData_node);
    }
    return true;
}
/**
* @brief     WJV4_RTSList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RTSList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RTSList *pstruWjRTSList = (WJV4_STRU_RTSList *)pvoidWjDf;
    RTSList_t *pstruAsnRTSList = (RTSList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_RTSDATA_LEN < pstruAsnRTSList->list.count) || (WJV4_MIN_LIST_RTSDATA_LEN > pstruAsnRTSList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnRTSList->list.count = %d",
                 pstruAsnRTSList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnRTSList->list.count; u32i++)
    {
        n32Ret = WJV4_RTSData_DfDec(pstruAsnRTSList->list.array[u32i],
                                    &(pstruWjRTSList->struRTSData[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RTSData_DfDec is err");
            return false;
        }
    }
    pstruWjRTSList->u8RTSDataNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_RoadPoint_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RoadPoint_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RoadPoint *pstruWjRoadPoint = (WJV4_STRU_RoadPoint *)pvoidWjDf;
    RoadPoint_t *pstruAsnRoadPoint = (RoadPoint_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_PositionOffsetLLV_DfEnc(&(pstruAsnRoadPoint->posOffset), &(pstruWjRoadPoint->struposOffset));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PositionOffsetLLV_DfEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_RoadPoint_DfDec解码函数
* @details   协议栈Df编解中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_RoadPoint_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_RoadPoint *pstruWjRoadPoint = (WJV4_STRU_RoadPoint *)pvoidWjDf;
    RoadPoint_t *pstruAsnRoadPoint = (RoadPoint_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV4_PositionOffsetLLV_DfDec(&(pstruAsnRoadPoint->posOffset), &(pstruWjRoadPoint->struposOffset));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "WJV4_PositionOffsetLLV_DfDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_SpeedLimitList_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_SpeedLimitList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_SpeedLimitList *pstruWjSpeedLimitList = (WJV4_STRU_SpeedLimitList *)pvoidWjDf;
    SpeedLimitList_t *pstruAsnSpeedLimitList = (SpeedLimitList_t *)pvoidAsnDf;
    RegulatorySpeedLimit_t *pstruRegulatorySpeedLimit_node = NULL;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_REGULATORYSPEEDLIMITNUM_LEN < pstruWjSpeedLimitList->u8RegulatorySpeedLimitNum) || (WJV4_MIN_LIST_REGULATORYSPEEDLIMITNUM_LEN > pstruWjSpeedLimitList->u8RegulatorySpeedLimitNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjSpeedLimitList->u8RegulatorySpeedLimitNum = %d",
                 pstruWjSpeedLimitList->u8RegulatorySpeedLimitNum);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruWjSpeedLimitList->u8RegulatorySpeedLimitNum; u32i++)
    {
        pstruRegulatorySpeedLimit_node = CALLOC(1, sizeof(RegulatorySpeedLimit_t));
        if (NULL == pstruRegulatorySpeedLimit_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_RegulatorySpeedLimit_DfEnc(pstruRegulatorySpeedLimit_node, &(pstruWjSpeedLimitList->struRegulatorySpeedLimit[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RegulatorySpeedLimit_DfEnc is err");
            FREEMEM(pstruRegulatorySpeedLimit_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnSpeedLimitList->list), pstruRegulatorySpeedLimit_node);
    }
    return true;
}
/**
* @brief     WJV4_SpeedLimitList_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_SpeedLimitList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_SpeedLimitList *pstruWjSpeedLimitList = (WJV4_STRU_SpeedLimitList *)pvoidWjDf;
    SpeedLimitList_t *pstruAsnSpeedLimitList = (SpeedLimitList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
#ifdef _CHECK_
    if ((WJV4_MAX_LIST_REGULATORYSPEEDLIMITNUM_LEN < pstruAsnSpeedLimitList->list.count) || (WJV4_MIN_LIST_REGULATORYSPEEDLIMITNUM_LEN > pstruAsnSpeedLimitList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnSpeedLimitList->list.count = %d",
                 pstruAsnSpeedLimitList->list.count);
        return false;
    }
#endif
    for (u32i = 0; u32i < pstruAsnSpeedLimitList->list.count; u32i++)
    {
        n32Ret = WJV4_RegulatorySpeedLimit_DfDec(pstruAsnSpeedLimitList->list.array[u32i],
                                                 &(pstruWjSpeedLimitList->struRegulatorySpeedLimit[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_RegulatorySpeedLimit_DfDec is err");
            return false;
        }
    }
    pstruWjSpeedLimitList->u8RegulatorySpeedLimitNum = (uint8_t)u32i;
    return true;
}
/**
* @brief     WJV4_TimeChangeDetails_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_TimeChangeDetails_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_TimeChangeDetails *pstruWjTimeChangeDetails = (WJV4_STRU_TimeChangeDetails *)pvoidWjDf;
    TimeChangeDetails_t *pstruAsnTimeChangeDetails = (TimeChangeDetails_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV4_TimeChangeDetailsDOWN == pstruWjTimeChangeDetails->enumTimeChangeDetails)
    {
        n32Ret = WJV4_TimeCountingDown_DfEnc(&(pstruAsnTimeChangeDetails->choice.counting),
                                             &(pstruWjTimeChangeDetails->u.strucounting));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_TimeCountingDown_DfEnc is err");
            return false;
        }
        pstruAsnTimeChangeDetails->present = TimeChangeDetails_PR_counting;
    }
    else if (WJV4_TimeChangeDetailsUTC == pstruWjTimeChangeDetails->enumTimeChangeDetails)
    {
        n32Ret = WJV4_UTCTiming_DfEnc(&(pstruAsnTimeChangeDetails->choice.utcTiming),
                                      &(pstruWjTimeChangeDetails->u.struutcTiming));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_UTCTiming_DfEnc is err");
            return false;
        }
        pstruAsnTimeChangeDetails->present = TimeChangeDetails_PR_utcTiming;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "type is err pstruWjTimeChangeDetails->enumTimeChangeDetails = %d",
                 pstruWjTimeChangeDetails->enumTimeChangeDetails);
        return false;
    }
    return true;
}
/**
* @brief     WJV4_TimeChangeDetails_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_TimeChangeDetails_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_TimeChangeDetails *pstruWjTimeChangeDetails = (WJV4_STRU_TimeChangeDetails *)pvoidWjDf;
    TimeChangeDetails_t *pstruAsnTimeChangeDetails = (TimeChangeDetails_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (TimeChangeDetails_PR_counting == pstruAsnTimeChangeDetails->present)
    {
        n32Ret = WJV4_TimeCountingDown_DfDec(&(pstruAsnTimeChangeDetails->choice.counting),
                                             &(pstruWjTimeChangeDetails->u.strucounting));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_TimeCountingDown_DfDec is err");
            return false;
        }
        pstruWjTimeChangeDetails->enumTimeChangeDetails = WJV4_TimeChangeDetailsDOWN;
    }
    else if (TimeChangeDetails_PR_utcTiming == pstruAsnTimeChangeDetails->present)
    {
        n32Ret = WJV4_UTCTiming_DfDec(&(pstruAsnTimeChangeDetails->choice.utcTiming),
                                      &(pstruWjTimeChangeDetails->u.struutcTiming));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_UTCTiming_DfDec is err");
            return false;
        }
        pstruWjTimeChangeDetails->enumTimeChangeDetails = WJV4_TimeChangeDetailsUTC;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "type is err pstruAsnTimeChangeDetails->present = %d",
                 pstruAsnTimeChangeDetails->present);
        return false;
    }
    return true;
}
/**
* @brief     WJV4_TimeCountingDown_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_TimeCountingDown_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_TimeCountingDown *pstruWjTimeCountingDown = (WJV4_STRU_TimeCountingDown *)pvoidWjDf;
    TimeCountingDown_t *pstruAsnTimeCountingDown = (TimeCountingDown_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjTimeCountingDown->n32startTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjTimeCountingDown->n32startTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjTimeCountingDown->n32startTime = %d",
                 pstruWjTimeCountingDown->n32startTime);
        return false;
    }
#endif
    pstruAsnTimeCountingDown->startTime = pstruWjTimeCountingDown->n32startTime;
    if (WJV4_PRESENT == pstruWjTimeCountingDown->u8minEndTimePresent)
    {
        pstruAsnTimeCountingDown->minEndTime = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnTimeCountingDown->minEndTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjTimeCountingDown->n32minEndTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjTimeCountingDown->n32minEndTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjTimeCountingDown->n32minEndTime = %d",
                     pstruWjTimeCountingDown->n32minEndTime);
            return false;
        }
#endif
        *(pstruAsnTimeCountingDown->minEndTime) = pstruWjTimeCountingDown->n32minEndTime;
    }
    else
    {
        pstruAsnTimeCountingDown->minEndTime = NULL;
    }
    if (WJV4_PRESENT == pstruWjTimeCountingDown->u8maxEndTimePresent)
    {
        pstruAsnTimeCountingDown->maxEndTime = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnTimeCountingDown->maxEndTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjTimeCountingDown->n32maxEndTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjTimeCountingDown->n32maxEndTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjTimeCountingDown->n32maxEndTime = %d",
                     pstruWjTimeCountingDown->n32maxEndTime);
            return false;
        }
#endif
        *(pstruAsnTimeCountingDown->maxEndTime) = pstruWjTimeCountingDown->n32maxEndTime;
    }
    else
    {
        pstruAsnTimeCountingDown->maxEndTime = NULL;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjTimeCountingDown->n32likelyEndTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjTimeCountingDown->n32likelyEndTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjTimeCountingDown->n32likelyEndTime = %d",
                 pstruWjTimeCountingDown->n32likelyEndTime);
        return false;
    }
#endif
    pstruAsnTimeCountingDown->likelyEndTime = pstruWjTimeCountingDown->n32likelyEndTime;
    if (WJV4_PRESENT == pstruWjTimeCountingDown->u8timeConfidencePresent)
    {
        pstruAsnTimeCountingDown->timeConfidence = CALLOC(1, sizeof(Confidence_t));
        if (NULL == pstruAsnTimeCountingDown->timeConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_CONFIDENCE_SIZE < pstruWjTimeCountingDown->n32timeConfidence) || (WJV4_MIN_CONFIDENCE_SIZE > pstruWjTimeCountingDown->n32timeConfidence))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjTimeCountingDown->n32timeConfidence = %d",
                     pstruWjTimeCountingDown->n32timeConfidence);
            return false;
        }
#endif
        *(pstruAsnTimeCountingDown->timeConfidence) = pstruWjTimeCountingDown->n32timeConfidence;
    }
    else
    {
        pstruAsnTimeCountingDown->timeConfidence = NULL;
    }
    if (WJV4_PRESENT == pstruWjTimeCountingDown->u8nextStartTimePresent)
    {
        pstruAsnTimeCountingDown->nextStartTime = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnTimeCountingDown->nextStartTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjTimeCountingDown->n32nextStartTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjTimeCountingDown->n32nextStartTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjTimeCountingDown->n32nextStartTime = %d",
                     pstruWjTimeCountingDown->n32nextStartTime);
            return false;
        }
#endif
        *(pstruAsnTimeCountingDown->nextStartTime) = pstruWjTimeCountingDown->n32nextStartTime;
    }
    else
    {
        pstruAsnTimeCountingDown->nextStartTime = NULL;
    }
    if (WJV4_PRESENT == pstruWjTimeCountingDown->u8nextDurationPresent)
    {
        pstruAsnTimeCountingDown->nextDuration = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnTimeCountingDown->nextDuration)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjTimeCountingDown->n32nextDuration) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjTimeCountingDown->n32nextDuration))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjTimeCountingDown->n32nextDuration = %d",
                     pstruWjTimeCountingDown->n32nextDuration);
            return false;
        }
#endif
        *(pstruAsnTimeCountingDown->nextDuration) = pstruWjTimeCountingDown->n32nextDuration;
    }
    else
    {
        pstruAsnTimeCountingDown->nextDuration = NULL;
    }
    return true;
}
/**
* @brief     WJV4_TimeCountingDown_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_TimeCountingDown_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_TimeCountingDown *pstruWjTimeCountingDown = (WJV4_STRU_TimeCountingDown *)pvoidWjDf;
    TimeCountingDown_t *pstruAsnTimeCountingDown = (TimeCountingDown_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_TIMEMARK_SIZE < pstruAsnTimeCountingDown->startTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruAsnTimeCountingDown->startTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnTimeCountingDown->startTime = %d",
                 pstruAsnTimeCountingDown->startTime);
        return false;
    }
#endif
    pstruWjTimeCountingDown->n32startTime = pstruAsnTimeCountingDown->startTime;
    if (NULL != pstruAsnTimeCountingDown->minEndTime)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < *(pstruAsnTimeCountingDown->minEndTime)) || (WJV4_MIN_TIMEMARK_SIZE > *(pstruAsnTimeCountingDown->minEndTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnTimeCountingDown->minEndTime) = %d",
                     *(pstruAsnTimeCountingDown->minEndTime));
            return false;
        }
#endif
        pstruWjTimeCountingDown->n32minEndTime = *(pstruAsnTimeCountingDown->minEndTime);
        pstruWjTimeCountingDown->u8minEndTimePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjTimeCountingDown->u8minEndTimePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnTimeCountingDown->maxEndTime)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < *(pstruAsnTimeCountingDown->maxEndTime)) || (WJV4_MIN_TIMEMARK_SIZE > *(pstruAsnTimeCountingDown->maxEndTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnTimeCountingDown->maxEndTime) = %d",
                     *(pstruAsnTimeCountingDown->maxEndTime));
            return false;
        }
#endif
        pstruWjTimeCountingDown->n32maxEndTime = *(pstruAsnTimeCountingDown->maxEndTime);
        pstruWjTimeCountingDown->u8maxEndTimePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjTimeCountingDown->u8maxEndTimePresent = WJV4_ABSENT;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_TIMEMARK_SIZE < pstruAsnTimeCountingDown->likelyEndTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruAsnTimeCountingDown->likelyEndTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnTimeCountingDown->likelyEndTime = %d",
                 pstruAsnTimeCountingDown->likelyEndTime);
        return false;
    }
#endif
    pstruWjTimeCountingDown->n32likelyEndTime = pstruAsnTimeCountingDown->likelyEndTime;
    if (NULL != pstruAsnTimeCountingDown->timeConfidence)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_CONFIDENCE_SIZE < *(pstruAsnTimeCountingDown->timeConfidence)) || (WJV4_MIN_CONFIDENCE_SIZE > *(pstruAsnTimeCountingDown->timeConfidence)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnTimeCountingDown->timeConfidence) = %d",
                     *(pstruAsnTimeCountingDown->timeConfidence));
            return false;
        }
#endif
        pstruWjTimeCountingDown->n32timeConfidence = *(pstruAsnTimeCountingDown->timeConfidence);
        pstruWjTimeCountingDown->u8timeConfidencePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjTimeCountingDown->u8timeConfidencePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnTimeCountingDown->nextStartTime)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < *(pstruAsnTimeCountingDown->nextStartTime)) || (WJV4_MIN_TIMEMARK_SIZE > *(pstruAsnTimeCountingDown->nextStartTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnTimeCountingDown->nextStartTime) = %d",
                     *(pstruAsnTimeCountingDown->nextStartTime));
            return false;
        }
#endif
        pstruWjTimeCountingDown->n32nextStartTime = *(pstruAsnTimeCountingDown->nextStartTime);
        pstruWjTimeCountingDown->u8nextStartTimePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjTimeCountingDown->u8nextStartTimePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnTimeCountingDown->nextDuration)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < *(pstruAsnTimeCountingDown->nextDuration)) || (WJV4_MIN_TIMEMARK_SIZE > *(pstruAsnTimeCountingDown->nextDuration)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnTimeCountingDown->nextDuration) = %d",
                     *(pstruAsnTimeCountingDown->nextDuration));
            return false;
        }
#endif
        pstruWjTimeCountingDown->n32nextDuration = *(pstruAsnTimeCountingDown->nextDuration);
        pstruWjTimeCountingDown->u8nextDurationPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjTimeCountingDown->u8nextDurationPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_UTCTiming_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_UTCTiming_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_UTCTiming *pstruWjUTCTiming = (WJV4_STRU_UTCTiming *)pvoidWjDf;
    UTCTiming_t *pstruAsnUTCTiming = (UTCTiming_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjUTCTiming->n32startUTCTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjUTCTiming->n32startUTCTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjUTCTiming->n32startUTCTime = %d",
                 pstruWjUTCTiming->n32startUTCTime);
        return false;
    }
#endif
    pstruAsnUTCTiming->startUTCTime = pstruWjUTCTiming->n32startUTCTime;
    if (WJV4_PRESENT == pstruWjUTCTiming->u8minEndUTCTimePresent)
    {
        pstruAsnUTCTiming->minEndUTCTime = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnUTCTiming->minEndUTCTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjUTCTiming->n32minEndUTCTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjUTCTiming->n32minEndUTCTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjUTCTiming->n32minEndUTCTime = %d",
                     pstruWjUTCTiming->n32minEndUTCTime);
            return false;
        }
#endif
        *(pstruAsnUTCTiming->minEndUTCTime) = pstruWjUTCTiming->n32minEndUTCTime;
    }
    else
    {
        pstruAsnUTCTiming->minEndUTCTime = NULL;
    }
    if (WJV4_PRESENT == pstruWjUTCTiming->u8maxEndUTCTimePresent)
    {
        pstruAsnUTCTiming->maxEndUTCTime = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnUTCTiming->maxEndUTCTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjUTCTiming->n32maxEndUTCTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjUTCTiming->n32maxEndUTCTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjUTCTiming->n32maxEndUTCTime = %d",
                     pstruWjUTCTiming->n32maxEndUTCTime);
            return false;
        }
#endif
        *(pstruAsnUTCTiming->maxEndUTCTime) = pstruWjUTCTiming->n32maxEndUTCTime;
    }
    else
    {
        pstruAsnUTCTiming->maxEndUTCTime = NULL;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjUTCTiming->n32likelyEndUTCTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjUTCTiming->n32likelyEndUTCTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjUTCTiming->n32likelyEndUTCTime = %d",
                 pstruWjUTCTiming->n32likelyEndUTCTime);
        return false;
    }
#endif
    pstruAsnUTCTiming->likelyEndUTCTime = pstruWjUTCTiming->n32likelyEndUTCTime;
    if (WJV4_PRESENT == pstruWjUTCTiming->u8timeConfidencePresent)
    {
        pstruAsnUTCTiming->timeConfidence = CALLOC(1, sizeof(Confidence_t));
        if (NULL == pstruAsnUTCTiming->timeConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_CONFIDENCE_SIZE < pstruWjUTCTiming->n32timeConfidence) || (WJV4_MIN_CONFIDENCE_SIZE > pstruWjUTCTiming->n32timeConfidence))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjUTCTiming->n32timeConfidence = %d",
                     pstruWjUTCTiming->n32timeConfidence);
            return false;
        }
#endif
        *(pstruAsnUTCTiming->timeConfidence) = pstruWjUTCTiming->n32timeConfidence;
    }
    else
    {
        pstruAsnUTCTiming->timeConfidence = NULL;
    }
    if (WJV4_PRESENT == pstruWjUTCTiming->u8nextStartUTCTimePresent)
    {
        pstruAsnUTCTiming->nextStartUTCTime = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnUTCTiming->nextStartUTCTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjUTCTiming->n32nextStartUTCTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjUTCTiming->n32nextStartUTCTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjUTCTiming->n32nextStartUTCTime = %d",
                     pstruWjUTCTiming->n32nextStartUTCTime);
            return false;
        }
#endif
        *(pstruAsnUTCTiming->nextStartUTCTime) = pstruWjUTCTiming->n32nextStartUTCTime;
    }
    else
    {
        pstruAsnUTCTiming->nextStartUTCTime = NULL;
    }
    if (WJV4_PRESENT == pstruWjUTCTiming->u8nextEndUTCTimePresent)
    {
        pstruAsnUTCTiming->nextEndUTCTime = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnUTCTiming->nextEndUTCTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < pstruWjUTCTiming->n32nextEndUTCTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruWjUTCTiming->n32nextEndUTCTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjUTCTiming->n32nextEndUTCTime = %d",
                     pstruWjUTCTiming->n32nextEndUTCTime);
            return false;
        }
#endif
        *(pstruAsnUTCTiming->nextEndUTCTime) = pstruWjUTCTiming->n32nextEndUTCTime;
    }
    else
    {
        pstruAsnUTCTiming->nextEndUTCTime = NULL;
    }
    return true;
}
/**
* @brief     WJV4_UTCTiming_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_UTCTiming_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_UTCTiming *pstruWjUTCTiming = (WJV4_STRU_UTCTiming *)pvoidWjDf;
    UTCTiming_t *pstruAsnUTCTiming = (UTCTiming_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_TIMEMARK_SIZE < pstruAsnUTCTiming->startUTCTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruAsnUTCTiming->startUTCTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnUTCTiming->startUTCTime = %d",
                 pstruAsnUTCTiming->startUTCTime);
        return false;
    }
#endif
    pstruWjUTCTiming->n32startUTCTime = pstruAsnUTCTiming->startUTCTime;
    if (NULL != pstruAsnUTCTiming->minEndUTCTime)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < *(pstruAsnUTCTiming->minEndUTCTime)) || (WJV4_MIN_TIMEMARK_SIZE > *(pstruAsnUTCTiming->minEndUTCTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnUTCTiming->minEndUTCTime) = %d",
                     *(pstruAsnUTCTiming->minEndUTCTime));
            return false;
        }
#endif
        pstruWjUTCTiming->n32minEndUTCTime = *(pstruAsnUTCTiming->minEndUTCTime);
        pstruWjUTCTiming->u8minEndUTCTimePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjUTCTiming->u8minEndUTCTimePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnUTCTiming->maxEndUTCTime)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < *(pstruAsnUTCTiming->maxEndUTCTime)) || (WJV4_MIN_TIMEMARK_SIZE > *(pstruAsnUTCTiming->maxEndUTCTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnUTCTiming->maxEndUTCTime) = %d",
                     *(pstruAsnUTCTiming->maxEndUTCTime));
            return false;
        }
#endif
        pstruWjUTCTiming->n32maxEndUTCTime = *(pstruAsnUTCTiming->maxEndUTCTime);
        pstruWjUTCTiming->u8maxEndUTCTimePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjUTCTiming->u8maxEndUTCTimePresent = WJV4_ABSENT;
    }
#ifdef _CHECK_
    if ((WJV4_MAX_TIMEMARK_SIZE < pstruAsnUTCTiming->likelyEndUTCTime) || (WJV4_MIN_TIMEMARK_SIZE > pstruAsnUTCTiming->likelyEndUTCTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnUTCTiming->likelyEndUTCTime = %d",
                 pstruAsnUTCTiming->likelyEndUTCTime);
        return false;
    }
#endif
    pstruWjUTCTiming->n32likelyEndUTCTime = pstruAsnUTCTiming->likelyEndUTCTime;
    if (NULL != pstruAsnUTCTiming->timeConfidence)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_CONFIDENCE_SIZE < *(pstruAsnUTCTiming->timeConfidence)) || (WJV4_MIN_CONFIDENCE_SIZE > *(pstruAsnUTCTiming->timeConfidence)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnUTCTiming->timeConfidence) = %d",
                     *(pstruAsnUTCTiming->timeConfidence));
            return false;
        }
#endif
        pstruWjUTCTiming->n32timeConfidence = *(pstruAsnUTCTiming->timeConfidence);
        pstruWjUTCTiming->u8timeConfidencePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjUTCTiming->u8timeConfidencePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnUTCTiming->nextStartUTCTime)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < *(pstruAsnUTCTiming->nextStartUTCTime)) || (WJV4_MIN_TIMEMARK_SIZE > *(pstruAsnUTCTiming->nextStartUTCTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnUTCTiming->nextStartUTCTime) = %d",
                     *(pstruAsnUTCTiming->nextStartUTCTime));
            return false;
        }
#endif
        pstruWjUTCTiming->n32nextStartUTCTime = *(pstruAsnUTCTiming->nextStartUTCTime);
        pstruWjUTCTiming->u8nextStartUTCTimePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjUTCTiming->u8nextStartUTCTimePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnUTCTiming->nextEndUTCTime)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_TIMEMARK_SIZE < *(pstruAsnUTCTiming->nextEndUTCTime)) || (WJV4_MIN_TIMEMARK_SIZE > *(pstruAsnUTCTiming->nextEndUTCTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnUTCTiming->nextEndUTCTime) = %d",
                     *(pstruAsnUTCTiming->nextEndUTCTime));
            return false;
        }
#endif
        pstruWjUTCTiming->n32nextEndUTCTime = *(pstruAsnUTCTiming->nextEndUTCTime);
        pstruWjUTCTiming->u8nextEndUTCTimePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjUTCTiming->u8nextEndUTCTimePresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_VehicleClassification_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_VehicleClassification_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_VehicleClassification *pstruWjVehicleClassification = (WJV4_STRU_VehicleClassification *)pvoidWjDf;
    VehicleClassification_t *pstruAsnVehicleClassification = (VehicleClassification_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_BASICVEHICLECLASS_SIZE < pstruWjVehicleClassification->n32classification) || (WJV4_MIN_BASICVEHICLECLASS_SIZE > pstruWjVehicleClassification->n32classification))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjVehicleClassification->n32classification = %d",
                 pstruWjVehicleClassification->n32classification);
        return false;
    }
#endif
    pstruAsnVehicleClassification->classification = pstruWjVehicleClassification->n32classification;
    if (WJV4_PRESENT == pstruWjVehicleClassification->u8fuelTypePresent)
    {
        pstruAsnVehicleClassification->fuelType = CALLOC(1, sizeof(FuelType_t));
        if (NULL == pstruAsnVehicleClassification->fuelType)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_FUELTYPE_SIZE < pstruWjVehicleClassification->n32fuelType) || (WJV4_MIN_FUELTYPE_SIZE > pstruWjVehicleClassification->n32fuelType))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjVehicleClassification->n32fuelType = %d",
                     pstruWjVehicleClassification->n32fuelType);
            return false;
        }
#endif
        *(pstruAsnVehicleClassification->fuelType) = pstruWjVehicleClassification->n32fuelType;
    }
    else
    {
        pstruAsnVehicleClassification->fuelType = NULL;
    }
    return true;
}
/**
* @brief     WJV4_VehicleClassification_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_VehicleClassification_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_VehicleClassification *pstruWjVehicleClassification = (WJV4_STRU_VehicleClassification *)pvoidWjDf;
    VehicleClassification_t *pstruAsnVehicleClassification = (VehicleClassification_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_BASICVEHICLECLASS_SIZE < pstruAsnVehicleClassification->classification) || (WJV4_MIN_BASICVEHICLECLASS_SIZE > pstruAsnVehicleClassification->classification))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnVehicleClassification->classification = %d",
                 pstruAsnVehicleClassification->classification);
        return false;
    }
#endif
    pstruWjVehicleClassification->n32classification = pstruAsnVehicleClassification->classification;
    if (NULL != pstruAsnVehicleClassification->fuelType)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_FUELTYPE_SIZE < *(pstruAsnVehicleClassification->fuelType)) || (WJV4_MIN_FUELTYPE_SIZE > *(pstruAsnVehicleClassification->fuelType)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnVehicleClassification->fuelType) = %d",
                     *(pstruAsnVehicleClassification->fuelType));
            return false;
        }
#endif
        pstruWjVehicleClassification->n32fuelType = *(pstruAsnVehicleClassification->fuelType);
        pstruWjVehicleClassification->u8fuelTypePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjVehicleClassification->u8fuelTypePresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_VehicleEmergencyExtensions_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_VehicleEmergencyExtensions_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_VehicleEmergencyExtensions *pstruWjVehicleEmergencyExtensions = (WJV4_STRU_VehicleEmergencyExtensions *)pvoidWjDf;
    VehicleEmergencyExtensions_t *pstruAsnVehicleEmergencyExtensions = (VehicleEmergencyExtensions_t *)pvoidAsnDf;
    if (WJV4_PRESENT == pstruWjVehicleEmergencyExtensions->u8responseTypePresent)
    {
        pstruAsnVehicleEmergencyExtensions->responseType = CALLOC(1, sizeof(ResponseType_t));
        if (NULL == pstruAsnVehicleEmergencyExtensions->responseType)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnVehicleEmergencyExtensions->responseType) = pstruWjVehicleEmergencyExtensions->enumresponseType;
    }
    else
    {
        pstruAsnVehicleEmergencyExtensions->responseType = NULL;
    }
    if (WJV4_PRESENT == pstruWjVehicleEmergencyExtensions->u8sirenUsePresent)
    {
        pstruAsnVehicleEmergencyExtensions->sirenUse = CALLOC(1, sizeof(SirenInUse_t));
        if (NULL == pstruAsnVehicleEmergencyExtensions->sirenUse)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnVehicleEmergencyExtensions->sirenUse) = pstruWjVehicleEmergencyExtensions->enumsirenUse;
    }
    else
    {
        pstruAsnVehicleEmergencyExtensions->sirenUse = NULL;
    }
    if (WJV4_PRESENT == pstruWjVehicleEmergencyExtensions->u8lightsUsePresent)
    {
        pstruAsnVehicleEmergencyExtensions->lightsUse = CALLOC(1, sizeof(LightbarInUse_t));
        if (NULL == pstruAsnVehicleEmergencyExtensions->lightsUse)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        *(pstruAsnVehicleEmergencyExtensions->lightsUse) = pstruWjVehicleEmergencyExtensions->enumlightsUse;
    }
    else
    {
        pstruAsnVehicleEmergencyExtensions->lightsUse = NULL;
    }
    return true;
}
/**
* @brief     WJV4_VehicleEmergencyExtensions_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_VehicleEmergencyExtensions_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_VehicleEmergencyExtensions *pstruWjVehicleEmergencyExtensions = (WJV4_STRU_VehicleEmergencyExtensions *)pvoidWjDf;
    VehicleEmergencyExtensions_t *pstruAsnVehicleEmergencyExtensions = (VehicleEmergencyExtensions_t *)pvoidAsnDf;
    if (NULL != pstruAsnVehicleEmergencyExtensions->responseType)
    {
        pstruWjVehicleEmergencyExtensions->enumresponseType = *(pstruAsnVehicleEmergencyExtensions->responseType);
        pstruWjVehicleEmergencyExtensions->u8responseTypePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjVehicleEmergencyExtensions->u8responseTypePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnVehicleEmergencyExtensions->sirenUse)
    {
        pstruWjVehicleEmergencyExtensions->enumsirenUse = *(pstruAsnVehicleEmergencyExtensions->sirenUse);
        pstruWjVehicleEmergencyExtensions->u8sirenUsePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjVehicleEmergencyExtensions->u8sirenUsePresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnVehicleEmergencyExtensions->lightsUse)
    {
        pstruWjVehicleEmergencyExtensions->enumlightsUse = *(pstruAsnVehicleEmergencyExtensions->lightsUse);
        pstruWjVehicleEmergencyExtensions->u8lightsUsePresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjVehicleEmergencyExtensions->u8lightsUsePresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_VehicleSafetyExtensions_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_VehicleSafetyExtensions_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_VehicleSafetyExtensions *pstruWjVehicleSafetyExtensions = (WJV4_STRU_VehicleSafetyExtensions *)pvoidWjDf;
    VehicleSafetyExtensions_t *pstruAsnVehicleSafetyExtensions = (VehicleSafetyExtensions_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV4_PRESENT == pstruWjVehicleSafetyExtensions->u8eventsPresent)
    {
        pstruAsnVehicleSafetyExtensions->events = CALLOC(1, sizeof(VehicleEventFlags_t));
        if (NULL == pstruAsnVehicleSafetyExtensions->events)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_VehicleEventFlags_DeEnc(pstruAsnVehicleSafetyExtensions->events,
                                              &(pstruWjVehicleSafetyExtensions->strbitevents));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_VehicleEventFlags_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnVehicleSafetyExtensions->events = NULL;
    }
    if (WJV4_PRESENT == pstruWjVehicleSafetyExtensions->u8pathHistoryPresent)
    {
        pstruAsnVehicleSafetyExtensions->pathHistory = CALLOC(1, sizeof(struct PathHistory));
        if (NULL == pstruAsnVehicleSafetyExtensions->pathHistory)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_PathHistory_DfEnc(pstruAsnVehicleSafetyExtensions->pathHistory,
                                        &(pstruWjVehicleSafetyExtensions->strupathHistory));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PathHistory_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnVehicleSafetyExtensions->pathHistory = NULL;
    }
    if (WJV4_PRESENT == pstruWjVehicleSafetyExtensions->u8pathPredictionPresent)
    {
        pstruAsnVehicleSafetyExtensions->pathPrediction = CALLOC(1, sizeof(struct PathPrediction));
        if (NULL == pstruAsnVehicleSafetyExtensions->pathPrediction)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_PathPrediction_DfEnc(pstruAsnVehicleSafetyExtensions->pathPrediction,
                                           &(pstruWjVehicleSafetyExtensions->strupathPrediction));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PathPrediction_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnVehicleSafetyExtensions->pathPrediction = NULL;
    }
    if (WJV4_PRESENT == pstruWjVehicleSafetyExtensions->u8lightsPresent)
    {
        pstruAsnVehicleSafetyExtensions->lights = CALLOC(1, sizeof(ExteriorLights_t));
        if (NULL == pstruAsnVehicleSafetyExtensions->lights)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV4_ExteriorLights_DeEnc(pstruAsnVehicleSafetyExtensions->lights,
                                           &(pstruWjVehicleSafetyExtensions->strbitlights));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ExteriorLights_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnVehicleSafetyExtensions->lights = NULL;
    }
    return true;
}
/**
* @brief     WJV4_VehicleSafetyExtensions_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_VehicleSafetyExtensions_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_VehicleSafetyExtensions *pstruWjVehicleSafetyExtensions = (WJV4_STRU_VehicleSafetyExtensions *)pvoidWjDf;
    VehicleSafetyExtensions_t *pstruAsnVehicleSafetyExtensions = (VehicleSafetyExtensions_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnVehicleSafetyExtensions->events)
    {
        n32Ret = WJV4_VehicleEventFlags_DeDec(pstruAsnVehicleSafetyExtensions->events,
                                              &(pstruWjVehicleSafetyExtensions->strbitevents));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_VehicleEventFlags_DeDec is err");
            return false;
        }
        pstruWjVehicleSafetyExtensions->u8eventsPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjVehicleSafetyExtensions->u8eventsPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnVehicleSafetyExtensions->pathHistory)
    {
        n32Ret = WJV4_PathHistory_DfDec(pstruAsnVehicleSafetyExtensions->pathHistory,
                                        &(pstruWjVehicleSafetyExtensions->strupathHistory));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PathHistory_DfDec is err");
            return false;
        }
        pstruWjVehicleSafetyExtensions->u8pathHistoryPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjVehicleSafetyExtensions->u8pathHistoryPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnVehicleSafetyExtensions->pathPrediction)
    {
        n32Ret = WJV4_PathPrediction_DfDec(pstruAsnVehicleSafetyExtensions->pathPrediction,
                                           &(pstruWjVehicleSafetyExtensions->strupathPrediction));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_PathPrediction_DfDec is err");
            return false;
        }
        pstruWjVehicleSafetyExtensions->u8pathPredictionPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjVehicleSafetyExtensions->u8pathPredictionPresent = WJV4_ABSENT;
    }
    if (NULL != pstruAsnVehicleSafetyExtensions->lights)
    {
        n32Ret = WJV4_ExteriorLights_DeDec(pstruAsnVehicleSafetyExtensions->lights,
                                           &(pstruWjVehicleSafetyExtensions->strbitlights));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "WJV4_ExteriorLights_DeDec is err");
            return false;
        }
        pstruWjVehicleSafetyExtensions->u8lightsPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjVehicleSafetyExtensions->u8lightsPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_VehicleSize_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_VehicleSize_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_VehicleSize *pstruWjVehicleSize = (WJV4_STRU_VehicleSize *)pvoidWjDf;
    VehicleSize_t *pstruAsnVehicleSize = (VehicleSize_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_VEHICLEWIDTH_SIZE < pstruWjVehicleSize->n32width) || (WJV4_MIN_VEHICLEWIDTH_SIZE > pstruWjVehicleSize->n32width))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjVehicleSize->n32width = %d",
                 pstruWjVehicleSize->n32width);
        return false;
    }
#endif
    pstruAsnVehicleSize->width = pstruWjVehicleSize->n32width;
#ifdef _CHECK_
    if ((WJV4_MAX_VEHICLELENGTH_SIZE < pstruWjVehicleSize->n32length) || (WJV4_MIN_VEHICLELENGTH_SIZE > pstruWjVehicleSize->n32length))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruWjVehicleSize->n32length = %d",
                 pstruWjVehicleSize->n32length);
        return false;
    }
#endif
    pstruAsnVehicleSize->length = pstruWjVehicleSize->n32length;
    if (WJV4_PRESENT == pstruWjVehicleSize->u8heightPresent)
    {
        pstruAsnVehicleSize->height = CALLOC(1, sizeof(VehicleHeight_t));
        if (NULL == pstruAsnVehicleSize->height)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
#ifdef _CHECK_
        if ((WJV4_MAX_VEHICLEHEIGHT_SIZE < pstruWjVehicleSize->n32height) || (WJV4_MIN_VEHICLEHEIGHT_SIZE > pstruWjVehicleSize->n32height))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjVehicleSize->n32height = %d",
                     pstruWjVehicleSize->n32height);
            return false;
        }
#endif
        *(pstruAsnVehicleSize->height) = pstruWjVehicleSize->n32height;
    }
    else
    {
        pstruAsnVehicleSize->height = NULL;
    }
    return true;
}
/**
* @brief     WJV4_VehicleSize_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_VehicleSize_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_VehicleSize *pstruWjVehicleSize = (WJV4_STRU_VehicleSize *)pvoidWjDf;
    VehicleSize_t *pstruAsnVehicleSize = (VehicleSize_t *)pvoidAsnDf;
#ifdef _CHECK_
    if ((WJV4_MAX_VEHICLEWIDTH_SIZE < pstruAsnVehicleSize->width) || (WJV4_MIN_VEHICLEWIDTH_SIZE > pstruAsnVehicleSize->width))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnVehicleSize->width = %d",
                 pstruAsnVehicleSize->width);
        return false;
    }
#endif
    pstruWjVehicleSize->n32width = pstruAsnVehicleSize->width;
#ifdef _CHECK_
    if ((WJV4_MAX_VEHICLELENGTH_SIZE < pstruAsnVehicleSize->length) || (WJV4_MIN_VEHICLELENGTH_SIZE > pstruAsnVehicleSize->length))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstruAsnVehicleSize->length = %d",
                 pstruAsnVehicleSize->length);
        return false;
    }
#endif
    pstruWjVehicleSize->n32length = pstruAsnVehicleSize->length;
    if (NULL != pstruAsnVehicleSize->height)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VEHICLEHEIGHT_SIZE < *(pstruAsnVehicleSize->height)) || (WJV4_MIN_VEHICLEHEIGHT_SIZE > *(pstruAsnVehicleSize->height)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:*(pstruAsnVehicleSize->height) = %d",
                     *(pstruAsnVehicleSize->height));
            return false;
        }
#endif
        pstruWjVehicleSize->n32height = *(pstruAsnVehicleSize->height);
        pstruWjVehicleSize->u8heightPresent = WJV4_PRESENT;
    }
    else
    {
        pstruWjVehicleSize->u8heightPresent = WJV4_ABSENT;
    }
    return true;
}
/**
* @brief     WJV4_VerticalOffset_DfEnc编码函数
* @details   协议栈Df编解码中 统一Df的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_VerticalOffset_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_VerticalOffset *pstruWjVerticalOffset = (WJV4_STRU_VerticalOffset *)pvoidWjDf;
    VerticalOffset_t *pstruAsnVerticalOffset = (VerticalOffset_t *)pvoidAsnDf;
    if (WJV4_VertOffsetB07 == pstruWjVerticalOffset->enumVerticalOffsetChoice)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB07_SIZE < pstruWjVerticalOffset->u.n32offset1) || (WJV4_MIN_VERTOFFSETB07_SIZE > pstruWjVerticalOffset->u.n32offset1))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjVerticalOffset->u.n32offset1 = %d",
                     pstruWjVerticalOffset->u.n32offset1);
            return false;
        }
#endif
        pstruAsnVerticalOffset->choice.offset1 = pstruWjVerticalOffset->u.n32offset1;
        pstruAsnVerticalOffset->present = VerticalOffset_PR_offset1;
    }
    else if (WJV4_VertOffsetB08 == pstruWjVerticalOffset->enumVerticalOffsetChoice)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB08_SIZE < pstruWjVerticalOffset->u.n32offset2) || (WJV4_MIN_VERTOFFSETB08_SIZE > pstruWjVerticalOffset->u.n32offset2))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjVerticalOffset->u.n32offset2 = %d",
                     pstruWjVerticalOffset->u.n32offset2);
            return false;
        }
#endif
        pstruAsnVerticalOffset->choice.offset2 = pstruWjVerticalOffset->u.n32offset2;
        pstruAsnVerticalOffset->present = VerticalOffset_PR_offset2;
    }
    else if (WJV4_VertOffsetB09 == pstruWjVerticalOffset->enumVerticalOffsetChoice)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB09_SIZE < pstruWjVerticalOffset->u.n32offset3) || (WJV4_MIN_VERTOFFSETB09_SIZE > pstruWjVerticalOffset->u.n32offset3))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjVerticalOffset->u.n32offset3 = %d",
                     pstruWjVerticalOffset->u.n32offset3);
            return false;
        }
#endif
        pstruAsnVerticalOffset->choice.offset3 = pstruWjVerticalOffset->u.n32offset3;
        pstruAsnVerticalOffset->present = VerticalOffset_PR_offset3;
    }
    else if (WJV4_VertOffsetB10 == pstruWjVerticalOffset->enumVerticalOffsetChoice)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB10_SIZE < pstruWjVerticalOffset->u.n32offset4) || (WJV4_MIN_VERTOFFSETB10_SIZE > pstruWjVerticalOffset->u.n32offset4))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjVerticalOffset->u.n32offset4 = %d",
                     pstruWjVerticalOffset->u.n32offset4);
            return false;
        }
#endif
        pstruAsnVerticalOffset->choice.offset4 = pstruWjVerticalOffset->u.n32offset4;
        pstruAsnVerticalOffset->present = VerticalOffset_PR_offset4;
    }
    else if (WJV4_VertOffsetB11 == pstruWjVerticalOffset->enumVerticalOffsetChoice)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB11_SIZE < pstruWjVerticalOffset->u.n32offset5) || (WJV4_MIN_VERTOFFSETB11_SIZE > pstruWjVerticalOffset->u.n32offset5))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjVerticalOffset->u.n32offset5 = %d",
                     pstruWjVerticalOffset->u.n32offset5);
            return false;
        }
#endif
        pstruAsnVerticalOffset->choice.offset5 = pstruWjVerticalOffset->u.n32offset5;
        pstruAsnVerticalOffset->present = VerticalOffset_PR_offset5;
    }
    else if (WJV4_VertOffsetB12 == pstruWjVerticalOffset->enumVerticalOffsetChoice)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB12_SIZE < pstruWjVerticalOffset->u.n32offset6) || (WJV4_MIN_VERTOFFSETB12_SIZE > pstruWjVerticalOffset->u.n32offset6))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjVerticalOffset->u.n32offset6 = %d",
                     pstruWjVerticalOffset->u.n32offset6);
            return false;
        }
#endif
        pstruAsnVerticalOffset->choice.offset6 = pstruWjVerticalOffset->u.n32offset6;
        pstruAsnVerticalOffset->present = VerticalOffset_PR_offset6;
    }
    else if (WJV4_Elevation == pstruWjVerticalOffset->enumVerticalOffsetChoice)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_ELEVATION_SIZE < pstruWjVerticalOffset->u.n32elevation) || (WJV4_MIN_ELEVATION_SIZE > pstruWjVerticalOffset->u.n32elevation))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruWjVerticalOffset->u.n32elevation = %d",
                     pstruWjVerticalOffset->u.n32elevation);
            return false;
        }
#endif
        pstruAsnVerticalOffset->choice.elevation = pstruWjVerticalOffset->u.n32elevation;
        pstruAsnVerticalOffset->present = VerticalOffset_PR_elevation;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "type is err pstruWjVerticalOffset->enumVerticalOffsetChoice = %d",
                 pstruWjVerticalOffset->enumVerticalOffsetChoice);
        return false;
    }
    return true;
}
/**
* @brief     WJV4_VerticalOffset_DfDec解码函数
* @details   协议栈Df编解码中 统一Df的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int32_t WJV4_VerticalOffset_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV4_STRU_VerticalOffset *pstruWjVerticalOffset = (WJV4_STRU_VerticalOffset *)pvoidWjDf;
    VerticalOffset_t *pstruAsnVerticalOffset = (VerticalOffset_t *)pvoidAsnDf;
    if (VerticalOffset_PR_offset1 == pstruAsnVerticalOffset->present)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB07_SIZE < pstruAsnVerticalOffset->choice.offset1) || (WJV4_MIN_VERTOFFSETB07_SIZE > pstruAsnVerticalOffset->choice.offset1))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnVerticalOffset->choice.offset1 = %d",
                     pstruAsnVerticalOffset->choice.offset1);
            return false;
        }
#endif
        pstruWjVerticalOffset->u.n32offset1 = pstruAsnVerticalOffset->choice.offset1;
        pstruWjVerticalOffset->enumVerticalOffsetChoice = pstruAsnVerticalOffset->present;
    }
    else if (VerticalOffset_PR_offset2 == pstruAsnVerticalOffset->present)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB08_SIZE < pstruAsnVerticalOffset->choice.offset2) || (WJV4_MIN_VERTOFFSETB08_SIZE > pstruAsnVerticalOffset->choice.offset2))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnVerticalOffset->choice.offset2 = %d",
                     pstruAsnVerticalOffset->choice.offset2);
            return false;
        }
#endif
        pstruWjVerticalOffset->u.n32offset2 = pstruAsnVerticalOffset->choice.offset2;
        pstruWjVerticalOffset->enumVerticalOffsetChoice = pstruAsnVerticalOffset->present;
    }
    else if (VerticalOffset_PR_offset3 == pstruAsnVerticalOffset->present)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB09_SIZE < pstruAsnVerticalOffset->choice.offset3) || (WJV4_MIN_VERTOFFSETB09_SIZE > pstruAsnVerticalOffset->choice.offset3))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnVerticalOffset->choice.offset3 = %d",
                     pstruAsnVerticalOffset->choice.offset3);
            return false;
        }
#endif
        pstruWjVerticalOffset->u.n32offset3 = pstruAsnVerticalOffset->choice.offset3;
        pstruWjVerticalOffset->enumVerticalOffsetChoice = pstruAsnVerticalOffset->present;
    }
    else if (VerticalOffset_PR_offset4 == pstruAsnVerticalOffset->present)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB10_SIZE < pstruAsnVerticalOffset->choice.offset4) || (WJV4_MIN_VERTOFFSETB10_SIZE > pstruAsnVerticalOffset->choice.offset4))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnVerticalOffset->choice.offset4 = %d",
                     pstruAsnVerticalOffset->choice.offset4);
            return false;
        }
#endif
        pstruWjVerticalOffset->u.n32offset4 = pstruAsnVerticalOffset->choice.offset4;
        pstruWjVerticalOffset->enumVerticalOffsetChoice = pstruAsnVerticalOffset->present;
    }
    else if (VerticalOffset_PR_offset5 == pstruAsnVerticalOffset->present)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB11_SIZE < pstruAsnVerticalOffset->choice.offset5) || (WJV4_MIN_VERTOFFSETB11_SIZE > pstruAsnVerticalOffset->choice.offset5))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnVerticalOffset->choice.offset5 = %d",
                     pstruAsnVerticalOffset->choice.offset5);
            return false;
        }
#endif
        pstruWjVerticalOffset->u.n32offset5 = pstruAsnVerticalOffset->choice.offset5;
        pstruWjVerticalOffset->enumVerticalOffsetChoice = pstruAsnVerticalOffset->present;
    }
    else if (VerticalOffset_PR_offset6 == pstruAsnVerticalOffset->present)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_VERTOFFSETB12_SIZE < pstruAsnVerticalOffset->choice.offset6) || (WJV4_MIN_VERTOFFSETB12_SIZE > pstruAsnVerticalOffset->choice.offset6))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnVerticalOffset->choice.offset6 = %d",
                     pstruAsnVerticalOffset->choice.offset6);
            return false;
        }
#endif
        pstruWjVerticalOffset->u.n32offset6 = pstruAsnVerticalOffset->choice.offset6;
        pstruWjVerticalOffset->enumVerticalOffsetChoice = pstruAsnVerticalOffset->present;
    }
    else if (VerticalOffset_PR_elevation == pstruAsnVerticalOffset->present)
    {
#ifdef _CHECK_
        if ((WJV4_MAX_ELEVATION_SIZE < pstruAsnVerticalOffset->choice.elevation) || (WJV4_MIN_ELEVATION_SIZE > pstruAsnVerticalOffset->choice.elevation))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstruAsnVerticalOffset->choice.elevation = %d",
                     pstruAsnVerticalOffset->choice.elevation);
            return false;
        }
#endif
        pstruWjVerticalOffset->u.n32elevation = pstruAsnVerticalOffset->choice.elevation;
        pstruWjVerticalOffset->enumVerticalOffsetChoice = pstruAsnVerticalOffset->present;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "type is err pstruAsnVerticalOffset->present = %d",
                 pstruAsnVerticalOffset->present);
        return false;
    }
    return true;
}
/***** 文件结束 *****/