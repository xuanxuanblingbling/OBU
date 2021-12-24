/**
* @file         :wjv3_uper_De.c
* @brief        :该文件为协议栈数据帧编解码源文件
* @details  	:主要包含协议栈数据帧编解码接口入口函数
* @author   	:huangsai  any question please send mail to huangsai@wanji.net.cn
* @date     	:2020-8-10
* @version		:V1.0
* @copyright 	:Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：IMAX6
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
/* 头文件包含 */
#include "wjv3_uper_Df.h"
#include "wjv3_uper_com.h"
/**
 * @brief    WJV3_Position3D_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 Position3D 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Position3D_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Position3D *pstruWjPosition3D = (WJV3_STRU_Position3D *)pvoidWjDf;
    Position3D_t *pstruAsnPosition3D = (Position3D_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_LATITUDE_SIZE < pstruWjPosition3D->n32lat)
        || (WJV3_MIN_LATITUDE_SIZE > pstruWjPosition3D->n32lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32lat = %d",
                 pstruWjPosition3D->n32lat);
        return false;
    }
    #endif
    pstruAsnPosition3D->lat = pstruWjPosition3D->n32lat;
    #ifdef _CHECK_
    if ((WJV3_MAX_LONGITUDE_SIZE < pstruWjPosition3D->n32Long)
         || (WJV3_MIN_LONGITUDE_SIZE > pstruWjPosition3D->n32Long))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32Long = %d",
                 pstruWjPosition3D->n32Long);
        return false;
    }
    #endif
    pstruAsnPosition3D->Long = pstruWjPosition3D->n32Long;
    if (WJV3_PRESENT == pstruWjPosition3D->u8elevation_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_ELEVATION_SIZE < pstruWjPosition3D->n32elevation)
            || (WJV3_MIN_ELEVATION_SIZE > pstruWjPosition3D->n32elevation))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32elevation = %d",
                     pstruWjPosition3D->n32elevation);
            return false;
        }
        #endif
        pstruAsnPosition3D->elevation = CALLOC(1, sizeof(Elevation_t));
        if (NULL == pstruAsnPosition3D->elevation)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
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
 * @brief    WJV3_Position3D_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 Position3D 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Position3D_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Position3D *pstruWjPosition3D = (WJV3_STRU_Position3D *)pvoidWjDf;
    Position3D_t *pstruAsnPosition3D = (Position3D_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_LATITUDE_SIZE < pstruAsnPosition3D->lat)
        || (WJV3_MIN_LATITUDE_SIZE > pstruAsnPosition3D->lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32lat = %d",
                 pstruAsnPosition3D->lat);
        return false;
    }
    #endif
    pstruWjPosition3D->n32lat = pstruAsnPosition3D->lat;
    #ifdef _CHECK_
    if ((WJV3_MAX_LONGITUDE_SIZE < pstruAsnPosition3D->Long)
         || (WJV3_MIN_LONGITUDE_SIZE > pstruAsnPosition3D->Long))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32Long = %d",
                 pstruAsnPosition3D->Long);
        return false;
    }
    #endif
    pstruWjPosition3D->n32Long = pstruAsnPosition3D->Long;
    if (NULL != pstruAsnPosition3D->elevation)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_ELEVATION_SIZE < *(pstruAsnPosition3D->elevation))
             || (WJV3_MIN_ELEVATION_SIZE > *(pstruAsnPosition3D->elevation)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32elevation = %d",
                     *(pstruAsnPosition3D->elevation));
            return false;
        }
        #endif
        pstruWjPosition3D->n32elevation = *(pstruAsnPosition3D->elevation);
        pstruWjPosition3D->u8elevation_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjPosition3D->u8elevation_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_PositionConfidenceSet_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PositionConfidenceSet 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PositionConfidenceSet_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PositionConfidenceSet *pstruWjPositionConfidenceSet = (WJV3_STRU_PositionConfidenceSet *)pvoidWjDf;
    PositionConfidenceSet_t *pstruAsnPositionConfidenceSet = (PositionConfidenceSet_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_PositionConfidence_DeEnc(&(pstruAsnPositionConfidenceSet->pos), &(pstruWjPositionConfidenceSet->enumpos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionConfidence_DeEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjPositionConfidenceSet->u8elevation_Present)
    {
        pstruAsnPositionConfidenceSet->elevation = CALLOC(1, sizeof(ElevationConfidence_t));
        if (NULL == pstruAsnPositionConfidenceSet->elevation)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_ElevationConfidence_DeEnc(pstruAsnPositionConfidenceSet->elevation, &(pstruWjPositionConfidenceSet->enumelevation));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_ElevationConfidence_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPositionConfidenceSet->elevation = NULL;
    }
    return true;
}
/**
 * @brief    WJV3_PositionConfidenceSet_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PositionConfidenceSet 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PositionConfidenceSet_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PositionConfidenceSet *pstruWjPositionConfidenceSet = (WJV3_STRU_PositionConfidenceSet *)pvoidWjDf;
    PositionConfidenceSet_t *pstruAsnPositionConfidenceSet = (PositionConfidenceSet_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_PositionConfidence_DeDec(&(pstruAsnPositionConfidenceSet->pos), &(pstruWjPositionConfidenceSet->enumpos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionConfidence_DeEnc is err");
        return false;
    }
    if (NULL != pstruAsnPositionConfidenceSet->elevation)
    {
        n32Ret = WJV3_ElevationConfidence_DeDec(pstruAsnPositionConfidenceSet->elevation, &(pstruWjPositionConfidenceSet->enumelevation));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_ElevationConfidence_DeEnc is err");
            return false;
        }
        pstruWjPositionConfidenceSet->u8elevation_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjPositionConfidenceSet->u8elevation_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_MotionConfidenceSet_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 MotionConfidenceSet 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_MotionConfidenceSet_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_MotionConfidenceSet *pstruWjMotionConfidenceSet = (WJV3_STRU_MotionConfidenceSet *)pvoidWjDf;
    MotionConfidenceSet_t *pstruAsnMotionConfidenceSet = (MotionConfidenceSet_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV3_PRESENT == pstruWjMotionConfidenceSet->u8speedCfd_Present)
    {
        pstruAsnMotionConfidenceSet->speedCfd = CALLOC(1, sizeof(SpeedConfidence_t));
        if (NULL == pstruAsnMotionConfidenceSet->speedCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_SpeedConfidence_DeEnc(pstruAsnMotionConfidenceSet->speedCfd, &(pstruWjMotionConfidenceSet->enumspeedCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_SpeedConfidence_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnMotionConfidenceSet->speedCfd = NULL;
    }
    if (WJV3_PRESENT == pstruWjMotionConfidenceSet->u8headingCfd_Present)
    {
        pstruAsnMotionConfidenceSet->headingCfd = CALLOC(1, sizeof(HeadingConfidence_t));
        if (NULL == pstruAsnMotionConfidenceSet->headingCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_HeadingConfidence_DeEnc(pstruAsnMotionConfidenceSet->headingCfd, &(pstruWjMotionConfidenceSet->enumheadingCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_HeadingConfidence_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnMotionConfidenceSet->headingCfd = NULL;
    }
    if (WJV3_PRESENT == pstruWjMotionConfidenceSet->u8steerCfd_Present)
    {
        pstruAsnMotionConfidenceSet->steerCfd = CALLOC(1, sizeof(SteeringWheelAngleConfidence_t));
        if (NULL == pstruAsnMotionConfidenceSet->steerCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_SteeringWheelAngleConfidence_DeEnc(pstruAsnMotionConfidenceSet->steerCfd, &(pstruWjMotionConfidenceSet->enumsteerCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_SteeringWheelAngleConfidence_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnMotionConfidenceSet->steerCfd = NULL;
    }
    return true;
}
/**
 * @brief    WJV3_MotionConfidenceSet_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 MotionConfidenceSet 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_MotionConfidenceSet_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_MotionConfidenceSet *pstruWjMotionConfidenceSet = (WJV3_STRU_MotionConfidenceSet *)pvoidWjDf;
    MotionConfidenceSet_t *pstruAsnMotionConfidenceSet = (MotionConfidenceSet_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnMotionConfidenceSet->speedCfd)
    {
        n32Ret = WJV3_SpeedConfidence_DeDec(pstruAsnMotionConfidenceSet->speedCfd, &(pstruWjMotionConfidenceSet->enumspeedCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_SpeedConfidence_DeDec is err");
            return false;
        }
        pstruWjMotionConfidenceSet->u8speedCfd_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjMotionConfidenceSet->u8speedCfd_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnMotionConfidenceSet->headingCfd)
    {
        n32Ret = WJV3_HeadingConfidence_DeDec(pstruAsnMotionConfidenceSet->headingCfd, &(pstruWjMotionConfidenceSet->enumheadingCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_HeadingConfidence_DeDec is err");
            return false;
        }
        pstruWjMotionConfidenceSet->u8headingCfd_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjMotionConfidenceSet->u8headingCfd_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnMotionConfidenceSet->steerCfd)
    {
        n32Ret = WJV3_SteeringWheelAngleConfidence_DeDec(pstruAsnMotionConfidenceSet->steerCfd, &(pstruWjMotionConfidenceSet->enumsteerCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_SteeringWheelAngleConfidence_DeDec is err");
            return false;
        }
        pstruWjMotionConfidenceSet->u8steerCfd_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjMotionConfidenceSet->u8steerCfd_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_AccelerationSet4Way_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 AccelerationSet4Way 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_AccelerationSet4Way_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_AccelerationSet4Way *pstruWjAccelerationSet4Way = (WJV3_STRU_AccelerationSet4Way *)pvoidWjDf;
    AccelerationSet4Way_t *pstruAsnAccelerationSet4Way = (AccelerationSet4Way_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_ACCELERATION_SIZE < pstruWjAccelerationSet4Way->n32Long)
        || (WJV3_MIN_ACCELERATION_SIZE > pstruWjAccelerationSet4Way->n32Long))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32Long = %d",
                 pstruWjAccelerationSet4Way->n32Long);
        return false;
    }
    #endif
    pstruAsnAccelerationSet4Way->Long = pstruWjAccelerationSet4Way->n32Long;
    #ifdef _CHECK_
    if ((WJV3_MAX_ACCELERATION_SIZE < pstruWjAccelerationSet4Way->n32lat)
        || (WJV3_MIN_ACCELERATION_SIZE > pstruWjAccelerationSet4Way->n32lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32lat = %d",
                 pstruWjAccelerationSet4Way->n32lat);
        return false;
    }
    #endif
    pstruAsnAccelerationSet4Way->lat = pstruWjAccelerationSet4Way->n32lat;
    #ifdef _CHECK_
    if ((WJV3_MAX_VERTICALACCELERATION_SIZE < pstruWjAccelerationSet4Way->n32vert)
        || (WJV3_MIN_VERTICALACCELERATION_SIZE > pstruWjAccelerationSet4Way->n32vert))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32vert = %d",
                 pstruWjAccelerationSet4Way->n32vert);
        return false;
    }
    #endif
    pstruAsnAccelerationSet4Way->vert = pstruWjAccelerationSet4Way->n32vert;
    #ifdef _CHECK_
    if ((WJV3_MAX_YAWRATE_SIZE < pstruWjAccelerationSet4Way->n32yaw)
        || (WJV3_MIN_YAWRATE_SIZE > pstruWjAccelerationSet4Way->n32yaw))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32yaw = %d",
                 pstruWjAccelerationSet4Way->n32yaw);
        return false;
    }
    #endif
    pstruAsnAccelerationSet4Way->yaw = pstruWjAccelerationSet4Way->n32yaw;
    return true;
}
/**
 * @brief    WJV3_AccelerationSet4Way_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 AccelerationSet4Way 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_AccelerationSet4Way_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_AccelerationSet4Way *pstruWjAccelerationSet4Way = (WJV3_STRU_AccelerationSet4Way *)pvoidWjDf;
    AccelerationSet4Way_t *pstruAsnAccelerationSet4Way = (AccelerationSet4Way_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_ACCELERATION_SIZE < pstruAsnAccelerationSet4Way->Long)
        || (WJV3_MIN_ACCELERATION_SIZE > pstruAsnAccelerationSet4Way->Long))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:Long = %d",
                 pstruAsnAccelerationSet4Way->Long);
        return false;
    }
    #endif
    pstruWjAccelerationSet4Way->n32Long = pstruAsnAccelerationSet4Way->Long;
    #ifdef _CHECK_
    if ((WJV3_MAX_ACCELERATION_SIZE < pstruAsnAccelerationSet4Way->lat)
         || (WJV3_MIN_ACCELERATION_SIZE > pstruAsnAccelerationSet4Way->lat))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:lat = %d",
                 pstruAsnAccelerationSet4Way->lat);
        return false;
    }
    #endif
    pstruWjAccelerationSet4Way->n32lat = pstruAsnAccelerationSet4Way->lat;
    #ifdef _CHECK_
    if ((WJV3_MAX_VERTICALACCELERATION_SIZE < pstruAsnAccelerationSet4Way->vert)
        || (WJV3_MIN_VERTICALACCELERATION_SIZE > pstruAsnAccelerationSet4Way->vert))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:vert = %d",
                 pstruAsnAccelerationSet4Way->vert);
        return false;
    }
    #endif
    pstruWjAccelerationSet4Way->n32vert = pstruAsnAccelerationSet4Way->vert;
    #ifdef _CHECK_
    if ((WJV3_MAX_YAWRATE_SIZE < pstruAsnAccelerationSet4Way->yaw)
        || (WJV3_MIN_YAWRATE_SIZE > pstruAsnAccelerationSet4Way->yaw))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:yaw = %d",
                 pstruAsnAccelerationSet4Way->yaw);
        return false;
    }
    #endif
    pstruWjAccelerationSet4Way->n32yaw = pstruAsnAccelerationSet4Way->yaw;
    return true;
}
/**
 * @brief    WJV3_BrakeSystemStatus_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 BrakeSystemStatus 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_BrakeSystemStatus_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_BrakeSystemStatus *pstruWjBrakeSystemStatus = (WJV3_STRU_BrakeSystemStatus *)pvoidWjDf;
    BrakeSystemStatus_t *pstruAsnBrakeSystemStatus = (BrakeSystemStatus_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV3_PRESENT == pstruWjBrakeSystemStatus->u8brakePadel_Present)
    {
        pstruAsnBrakeSystemStatus->brakePadel = CALLOC(1, sizeof(BrakePedalStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->brakePadel)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_BrakePedalStatus_DeEnc(pstruAsnBrakeSystemStatus->brakePadel, &(pstruWjBrakeSystemStatus->enumbrakePadel));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_BrakePedalStatus_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBrakeSystemStatus->brakePadel = NULL;
    }
    if (WJV3_PRESENT == pstruWjBrakeSystemStatus->u8wheelBrakes_Present)
    {
        pstruAsnBrakeSystemStatus->wheelBrakes = CALLOC(1, sizeof(BrakeAppliedStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->wheelBrakes)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnBrakeSystemStatus->wheelBrakes->size = WJV3_LEN_BYTE_WHEELBRAKES;
        pstruAsnBrakeSystemStatus->wheelBrakes->bits_unused = (8 * WJV3_LEN_BYTE_WHEELBRAKES) - WJV3_LEN_BITSTR_WHEELBRAKES;
        pstruAsnBrakeSystemStatus->wheelBrakes->buf = CALLOC(1, pstruAsnBrakeSystemStatus->wheelBrakes->size);
        if (NULL == pstruAsnBrakeSystemStatus->wheelBrakes->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "calloc is err");
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeEnc(pstruAsnBrakeSystemStatus->wheelBrakes, pstruWjBrakeSystemStatus->u.u8wheelBrakes);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "WJV3_BITSTRING_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBrakeSystemStatus->wheelBrakes = NULL;
    }
    if (WJV3_PRESENT == pstruWjBrakeSystemStatus->u8traction_Present)
    {
        pstruAsnBrakeSystemStatus->traction = CALLOC(1, sizeof(TractionControlStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->traction)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_TractionControlStatus_DeEnc(pstruAsnBrakeSystemStatus->traction, &(pstruWjBrakeSystemStatus->enumtraction));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_TractionControlStatus_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBrakeSystemStatus->traction = NULL;
    }
    if (WJV3_PRESENT == pstruWjBrakeSystemStatus->u8abs_Present)
    {
        pstruAsnBrakeSystemStatus->abs = CALLOC(1, sizeof(AntiLockBrakeStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->abs)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_AntiLockBrakeStatus_DeEnc(pstruAsnBrakeSystemStatus->abs, &(pstruWjBrakeSystemStatus->enumabs));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_AntiLockBrakeStatus_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBrakeSystemStatus->abs = NULL;
    }
    if (WJV3_PRESENT == pstruWjBrakeSystemStatus->u8scs_Present)
    {
        pstruAsnBrakeSystemStatus->scs = CALLOC(1, sizeof(StabilityControlStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->scs)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_StabilityControlStatus_DeEnc(pstruAsnBrakeSystemStatus->scs, &(pstruWjBrakeSystemStatus->enumscs));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_StabilityControlStatus_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBrakeSystemStatus->scs = NULL;
    }
    if (WJV3_PRESENT == pstruWjBrakeSystemStatus->u8brakeBoost_Present)
    {
        pstruAsnBrakeSystemStatus->brakeBoost = CALLOC(1, sizeof(BrakeBoostApplied_t));
        if (NULL == pstruAsnBrakeSystemStatus->brakeBoost)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_BrakeBoostApplied_DeEnc(pstruAsnBrakeSystemStatus->brakeBoost, &(pstruWjBrakeSystemStatus->enumbrakeBoost));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_BrakeBoostApplied_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBrakeSystemStatus->brakeBoost = NULL;
    }
    if (WJV3_PRESENT == pstruWjBrakeSystemStatus->u8auxBrakes_Present)
    {
        pstruAsnBrakeSystemStatus->auxBrakes = CALLOC(1, sizeof(AuxiliaryBrakeStatus_t));
        if (NULL == pstruAsnBrakeSystemStatus->auxBrakes)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_AuxiliaryBrakeStatus_DeEnc(pstruAsnBrakeSystemStatus->auxBrakes, &(pstruWjBrakeSystemStatus->enumauxBrakes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_AuxiliaryBrakeStatus_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnBrakeSystemStatus->auxBrakes = NULL;
    }
    return true;
}
/**
 * @brief    WJV3_BrakeSystemStatus_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 BrakeSystemStatus 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_BrakeSystemStatus_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_BrakeSystemStatus *pstruWjBrakeSystemStatus = (WJV3_STRU_BrakeSystemStatus *)pvoidWjDf;
    BrakeSystemStatus_t *pstruAsnBrakeSystemStatus = (BrakeSystemStatus_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnBrakeSystemStatus->brakePadel)
    {
        n32Ret = WJV3_BrakePedalStatus_DeDec(pstruAsnBrakeSystemStatus->brakePadel, &(pstruWjBrakeSystemStatus->enumbrakePadel));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_BrakePedalStatus_DeDec is err");
            return false;
        }
        pstruWjBrakeSystemStatus->u8brakePadel_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8brakePadel_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->wheelBrakes)
    {
        if ((NULL == pstruAsnBrakeSystemStatus->wheelBrakes->buf)
            || (WJV3_LEN_BYTE_CURRGNSSSTATUS != pstruAsnBrakeSystemStatus->wheelBrakes->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:size = %d",
                     pstruAsnBrakeSystemStatus->wheelBrakes->size);
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeDec(pstruAsnBrakeSystemStatus->wheelBrakes, pstruWjBrakeSystemStatus->u.u8wheelBrakes);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeDec is err");
            return false;
        }
        pstruWjBrakeSystemStatus->u8wheelBrakes_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8wheelBrakes_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->traction)
    {
        n32Ret = WJV3_TractionControlStatus_DeDec(pstruAsnBrakeSystemStatus->traction, &(pstruWjBrakeSystemStatus->enumtraction));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_TractionControlStatus_DeDec is err");
            return false;
        }
        pstruWjBrakeSystemStatus->u8traction_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8traction_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->abs)
    {
        n32Ret = WJV3_AntiLockBrakeStatus_DeDec(pstruAsnBrakeSystemStatus->abs, &(pstruWjBrakeSystemStatus->enumabs));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_AntiLockBrakeStatus_DeDec is err");
            return false;
        }
        pstruWjBrakeSystemStatus->u8abs_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8abs_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->scs)
    {
        n32Ret = WJV3_StabilityControlStatus_DeDec(pstruAsnBrakeSystemStatus->scs, &(pstruWjBrakeSystemStatus->enumscs));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_StabilityControlStatus_DeDec is err");
            return false;
        }
        pstruWjBrakeSystemStatus->u8scs_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8scs_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->brakeBoost)
    {
        n32Ret = WJV3_BrakeBoostApplied_DeDec(pstruAsnBrakeSystemStatus->brakeBoost, &(pstruWjBrakeSystemStatus->enumbrakeBoost));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_BrakeBoostApplied_DeDec is err");
            return false;
        }
        pstruWjBrakeSystemStatus->u8brakeBoost_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8brakeBoost_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnBrakeSystemStatus->auxBrakes)
    {
        n32Ret = WJV3_AuxiliaryBrakeStatus_DeDec(pstruAsnBrakeSystemStatus->auxBrakes, &(pstruWjBrakeSystemStatus->enumauxBrakes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_AuxiliaryBrakeStatus_DeDec is err");
            return false;
        }
        pstruWjBrakeSystemStatus->u8auxBrakes_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjBrakeSystemStatus->u8auxBrakes_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_VehicleSize_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 VehicleSize 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_VehicleSize_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_VehicleSize *pstruWjVehicleSize = (WJV3_STRU_VehicleSize *)pvoidWjDf;
    VehicleSize_t *pstruAsnVehicleSize = (VehicleSize_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_VEHICLEWIDTH_SIZE < pstruWjVehicleSize->n32width)
         || (WJV3_MIN_VEHICLEWIDTH_SIZE > pstruWjVehicleSize->n32width))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32width = %d",
                 pstruWjVehicleSize->n32width);
        return false;
    }
    #endif
    pstruAsnVehicleSize->width = pstruWjVehicleSize->n32width;
    #ifdef _CHECK_
    if ((WJV3_MAX_VEHICLELENGTH_SIZE < pstruWjVehicleSize->n32length)
        || (WJV3_MIN_VEHICLELENGTH_SIZE > pstruWjVehicleSize->n32length))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32length = %d",
                 pstruWjVehicleSize->n32length);
        return false;
    }
    #endif
    pstruAsnVehicleSize->length = pstruWjVehicleSize->n32length;
    if (WJV3_PRESENT == pstruWjVehicleSize->u8height_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_VEHICLEHEIGHT_SIZE < pstruWjVehicleSize->n32height)
            || (WJV3_MIN_VEHICLEHEIGHT_SIZE > pstruWjVehicleSize->n32height))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32height = %d",
                     pstruWjVehicleSize->n32height);
            return false;
        }
        #endif
        pstruAsnVehicleSize->height = CALLOC(1, sizeof(VehicleHeight_t));
        if (NULL == pstruAsnVehicleSize->height)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnVehicleSize->height) = pstruWjVehicleSize->n32height;
    }
    else
    {
        pstruAsnVehicleSize->height = NULL;
    }
    return true;
}
/**
 * @brief    WJV3_VehicleSize_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 VehicleSize 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_VehicleSize_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_VehicleSize *pstruWjVehicleSize = (WJV3_STRU_VehicleSize *)pvoidWjDf;
    VehicleSize_t *pstruAsnVehicleSize = (VehicleSize_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_VEHICLEWIDTH_SIZE < pstruAsnVehicleSize->width)
        || (WJV3_MIN_VEHICLEWIDTH_SIZE > pstruAsnVehicleSize->width))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32width = %d",
                 pstruAsnVehicleSize->width);
        return false;
    }
    #endif
    pstruWjVehicleSize->n32width = pstruAsnVehicleSize->width;
    #ifdef _CHECK_
    if ((WJV3_MAX_VEHICLELENGTH_SIZE < pstruAsnVehicleSize->length)
        || (WJV3_MIN_VEHICLELENGTH_SIZE > pstruAsnVehicleSize->length))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32length = %d",
                 pstruAsnVehicleSize->length);
        return false;
    }
    #endif
    pstruWjVehicleSize->n32length = pstruAsnVehicleSize->length;
    if (NULL != pstruAsnVehicleSize->height)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_VEHICLEHEIGHT_SIZE < *(pstruAsnVehicleSize->height))
            || (WJV3_MIN_VEHICLEHEIGHT_SIZE > *(pstruAsnVehicleSize->height)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32height = %d",
                     *(pstruAsnVehicleSize->height));
            return false;
        }
        #endif
        pstruWjVehicleSize->n32height = *(pstruAsnVehicleSize->height);
        pstruWjVehicleSize->u8height_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjVehicleSize->u8height_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_VehicleClassification_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 VehicleClassification 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_VehicleClassification_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_VehicleClassification *pstruWjVehicleClassification = (WJV3_STRU_VehicleClassification *)pvoidWjDf;
    VehicleClassification_t *pstruAsnVehicleClassification = (VehicleClassification_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_BASICVEHICLECLASS_SIZE < pstruWjVehicleClassification->n32classification)
        || (WJV3_MIN_BASICVEHICLECLASS_SIZE > pstruWjVehicleClassification->n32classification))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32classification = %d",
                 pstruWjVehicleClassification->n32classification);
        return false;
    }
    #endif
    pstruAsnVehicleClassification->classification = pstruWjVehicleClassification->n32classification;
    return true;
}
/**
 * @brief    WJV3_VehicleClassification_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 VehicleClassification 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_VehicleClassification_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_VehicleClassification *pstruWjVehicleClassification = (WJV3_STRU_VehicleClassification *)pvoidWjDf;
    VehicleClassification_t *pstruAsnVehicleClassification = (VehicleClassification_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_BASICVEHICLECLASS_SIZE < pstruAsnVehicleClassification->classification)
        || (WJV3_MIN_BASICVEHICLECLASS_SIZE > pstruAsnVehicleClassification->classification))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:classification = %d",
                 pstruAsnVehicleClassification->classification);
        return false;
    }
    #endif
    pstruWjVehicleClassification->n32classification = pstruAsnVehicleClassification->classification;
    return true;
}
/**
 * @brief    WJV3_DDateTime_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 DDateTime 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_DDateTime_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_DDateTime *pstruWjDDateTime = (WJV3_STRU_DDateTime *)pvoidWjDf;
    DDateTime_t *pstruAsnDDateTime = (DDateTime_t *)pvoidAsnDf;
    if (WJV3_PRESENT == pstruWjDDateTime->u8year_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DYEAR_SIZE < pstruWjDDateTime->n32year)
            || (WJV3_MIN_DYEAR_SIZE > pstruWjDDateTime->n32year))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32year = %d",
                     pstruWjDDateTime->n32year);
            return false;
        }
        #endif
        pstruAsnDDateTime->year = CALLOC(1, sizeof(DYear_t));
        if (NULL == pstruAsnDDateTime->year)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnDDateTime->year) = pstruWjDDateTime->n32year;
    }
    else
    {
        pstruAsnDDateTime->year = NULL;
    }
    if (WJV3_PRESENT == pstruWjDDateTime->u8month_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DMONTH_SIZE < pstruWjDDateTime->n32month)
            || (WJV3_MIN_DMONTH_SIZE > pstruWjDDateTime->n32month))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32month = %d",
                     pstruWjDDateTime->n32month);
            return false;
        }
        #endif
        pstruAsnDDateTime->month = CALLOC(1, sizeof(DMonth_t));
        if (NULL == pstruAsnDDateTime->month)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnDDateTime->month) = pstruWjDDateTime->n32month;
    }
    else
    {
        pstruAsnDDateTime->month = NULL;
    }
    if (WJV3_PRESENT == pstruWjDDateTime->u8day_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DDAY_SIZE < pstruWjDDateTime->n32day)
            || (WJV3_MIN_DDAY_SIZE > pstruWjDDateTime->n32day))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32day = %d",
                     pstruWjDDateTime->n32day);
            return false;
        }
        #endif
        pstruAsnDDateTime->day = CALLOC(1, sizeof(DDay_t));
        if (NULL == pstruAsnDDateTime->day)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnDDateTime->day) = pstruWjDDateTime->n32day;
    }
    else
    {
        pstruAsnDDateTime->day = NULL;
    }
    if (WJV3_PRESENT == pstruWjDDateTime->u8hour_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DHOUR_SIZE < pstruWjDDateTime->n32hour)
            || (WJV3_MIN_DHOUR_SIZE > pstruWjDDateTime->n32hour))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32hour = %d",
                     pstruWjDDateTime->n32hour);
            return false;
        }
        #endif
        pstruAsnDDateTime->hour = CALLOC(1, sizeof(DHour_t));
        if (NULL == pstruAsnDDateTime->hour)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnDDateTime->hour) = pstruWjDDateTime->n32hour;
    }
    else
    {
        pstruAsnDDateTime->hour = NULL;
    }
    if (WJV3_PRESENT == pstruWjDDateTime->u8minute_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DMINUTE_SIZE < pstruWjDDateTime->n32minute)
            || (WJV3_MIN_DMINUTE_SIZE > pstruWjDDateTime->n32minute))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32minute = %d",
                     pstruWjDDateTime->n32minute);
            return false;
        }
        #endif
        pstruAsnDDateTime->minute = CALLOC(1, sizeof(DMinute_t));
        if (NULL == pstruAsnDDateTime->minute)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnDDateTime->minute) = pstruWjDDateTime->n32minute;
    }
    else
    {
        pstruAsnDDateTime->minute = NULL;
    }
    if (WJV3_PRESENT == pstruWjDDateTime->u8second_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DSECOND_SIZE < pstruWjDDateTime->n32second)
            || (WJV3_MIN_DSECOND_SIZE > pstruWjDDateTime->n32second))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32second = %d",
                     pstruWjDDateTime->n32second);
            return false;
        }
        #endif
        pstruAsnDDateTime->second = CALLOC(1, sizeof(DSecond_t));
        if (NULL == pstruAsnDDateTime->second)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnDDateTime->second) = pstruWjDDateTime->n32second;
    }
    else
    {
        pstruAsnDDateTime->second = NULL;
    }
    if (WJV3_PRESENT == pstruWjDDateTime->u8offset_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DTIMEOFFSET_SIZE < pstruWjDDateTime->n32offset)
            || (WJV3_MIN_DTIMEOFFSET_SIZE> pstruWjDDateTime->n32offset))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32offset = %d",
                     pstruWjDDateTime->n32offset);
            return false;
        }
        #endif
        pstruAsnDDateTime->offset = CALLOC(1, sizeof(DTimeOffset_t));
        if (NULL == pstruAsnDDateTime->offset)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnDDateTime->offset) = pstruWjDDateTime->n32offset;
    }
    else
    {
        pstruAsnDDateTime->offset = NULL;
    }
    return true;
}
/**
 * @brief    WJV3_DDateTime_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 DDateTime 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_DDateTime_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_DDateTime *pstruWjDDateTime = (WJV3_STRU_DDateTime *)pvoidWjDf;
    DDateTime_t *pstruAsnDDateTime = (DDateTime_t *)pvoidAsnDf;
    if (NULL != pstruAsnDDateTime->year)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DYEAR_SIZE < *(pstruAsnDDateTime->year))
            || (WJV3_MIN_DYEAR_SIZE > *(pstruAsnDDateTime->year)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32year = %d",
                     *(pstruAsnDDateTime->year));
            return false;
        }
        #endif
        pstruWjDDateTime->n32year = *(pstruAsnDDateTime->year);
        pstruWjDDateTime->u8year_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8year_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnDDateTime->month)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DMONTH_SIZE < *(pstruAsnDDateTime->month))
            || (WJV3_MIN_DMONTH_SIZE > *(pstruAsnDDateTime->month)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32month = %d",
                     *(pstruAsnDDateTime->month));
            return false;
        }
        #endif
        pstruWjDDateTime->n32month = *(pstruAsnDDateTime->month);
        pstruWjDDateTime->u8month_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8month_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnDDateTime->day)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DDAY_SIZE < *(pstruAsnDDateTime->day))
            || (WJV3_MIN_DDAY_SIZE > *(pstruAsnDDateTime->day)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32day = %d",
                     *(pstruAsnDDateTime->day));
            return false;
        }
        #endif
        pstruWjDDateTime->n32day = *(pstruAsnDDateTime->day);
        pstruWjDDateTime->u8day_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8day_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnDDateTime->hour)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DHOUR_SIZE < *(pstruAsnDDateTime->hour))
            || (WJV3_MIN_DHOUR_SIZE > *(pstruAsnDDateTime->hour)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32hour = %d",
                     *(pstruAsnDDateTime->hour));
            return false;
        }
        #endif
        pstruWjDDateTime->n32hour = *(pstruAsnDDateTime->hour);
        pstruWjDDateTime->u8hour_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8hour_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnDDateTime->minute)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DMINUTE_SIZE < *(pstruAsnDDateTime->minute))
            || (WJV3_MIN_DMINUTE_SIZE > *(pstruAsnDDateTime->minute)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32minute = %d",
                     *(pstruAsnDDateTime->minute));
            return false;
        }
        #endif
        pstruWjDDateTime->n32minute = *(pstruAsnDDateTime->minute);
        pstruWjDDateTime->u8minute_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8minute_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnDDateTime->second)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DSECOND_SIZE < *(pstruAsnDDateTime->second))
            || (WJV3_MIN_DSECOND_SIZE > *(pstruAsnDDateTime->second)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32second = %d",
                     *(pstruAsnDDateTime->second));
            return false;
        }
        #endif
        pstruWjDDateTime->n32second = *(pstruAsnDDateTime->second);
        pstruWjDDateTime->u8second_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8second_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnDDateTime->offset)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DTIMEOFFSET_SIZE < *(pstruAsnDDateTime->offset))
            || (WJV3_MIN_DTIMEOFFSET_SIZE > *(pstruAsnDDateTime->offset)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32offset = %d",
                     *(pstruAsnDDateTime->offset));
            return false;
        }
        #endif
        pstruWjDDateTime->n32offset = *(pstruAsnDDateTime->offset);
        pstruWjDDateTime->u8offset_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjDDateTime->u8offset_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_FullPositionVector_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 FullPositionVector 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_FullPositionVector_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_FullPositionVector *pstruWjFullPositionVector = (WJV3_STRU_FullPositionVector *)pvoidWjDf;
    FullPositionVector_t *pstruAsnFullPositionVector = (FullPositionVector_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV3_PRESENT == pstruWjFullPositionVector->u8utcTime_Present)
    {
        pstruAsnFullPositionVector->utcTime = CALLOC(1, sizeof(DDateTime_t));
        if (NULL == pstruAsnFullPositionVector->utcTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_DDateTime_DfEnc(pstruAsnFullPositionVector->utcTime, &(pstruWjFullPositionVector->struutcTime));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_DDateTime_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnFullPositionVector->utcTime = NULL;
    }
    n32Ret = WJV3_Position3D_DfEnc(&(pstruAsnFullPositionVector->pos), &(pstruWjFullPositionVector->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_Position3D_DfEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjFullPositionVector->u8heading_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_HEADING_SIZE < pstruWjFullPositionVector->n32heading)
            || (WJV3_MIN_HEADING_SIZE > pstruWjFullPositionVector->n32heading))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32heading = %d",
                     pstruWjFullPositionVector->n32heading);
            return false;
        }
        #endif
        pstruAsnFullPositionVector->heading = CALLOC(1, sizeof(Heading_t));
        if (NULL == pstruAsnFullPositionVector->heading)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnFullPositionVector->heading) = pstruWjFullPositionVector->n32heading;
    }
    else
    {
        pstruAsnFullPositionVector->heading = NULL;
    }
    if (WJV3_PRESENT == pstruWjFullPositionVector->u8transmission_Present)
    {
        pstruAsnFullPositionVector->transmission = CALLOC(1, sizeof(TransmissionState_t));
        if (NULL == pstruAsnFullPositionVector->transmission)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_TransmissionState_DeEnc(pstruAsnFullPositionVector->transmission, &(pstruWjFullPositionVector->enumtransmission));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_TransmissionState_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnFullPositionVector->transmission = NULL;
    }
    if (WJV3_PRESENT == pstruWjFullPositionVector->u8speed_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_SPEED_SIZE < pstruWjFullPositionVector->n32speed)
            || (WJV3_MIN_SPEED_SIZE > pstruWjFullPositionVector->n32speed))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32speed = %d",
                     pstruWjFullPositionVector->n32speed);
            return false;
        }
        #endif
        pstruAsnFullPositionVector->speed = CALLOC(1, sizeof(Speed_t));
        if (NULL == pstruAsnFullPositionVector->speed)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnFullPositionVector->speed) = pstruWjFullPositionVector->n32speed;
    }
    else
    {
        pstruAsnFullPositionVector->speed = NULL;
    }
    if (WJV3_PRESENT == pstruWjFullPositionVector->u8posAccuracy_Present)
    {
        pstruAsnFullPositionVector->posAccuracy = CALLOC(1, sizeof(PositionConfidenceSet_t));
        if (NULL == pstruAsnFullPositionVector->posAccuracy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_PositionConfidenceSet_DfEnc(pstruAsnFullPositionVector->posAccuracy, &(pstruWjFullPositionVector->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PositionConfidenceSet_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnFullPositionVector->posAccuracy = NULL;
    }
    if (WJV3_PRESENT == pstruWjFullPositionVector->u8timeConfidence_Present)
    {
        pstruAsnFullPositionVector->timeConfidence = CALLOC(1, sizeof(TimeConfidence_t));
        if (NULL == pstruAsnFullPositionVector->timeConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_TimeConfidence_DeEnc(pstruAsnFullPositionVector->timeConfidence, &(pstruWjFullPositionVector->strutimeConfidence));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_TimeConfidence_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnFullPositionVector->timeConfidence = NULL;
    }
    if (WJV3_PRESENT == pstruWjFullPositionVector->u8posConfidence_Present)
    {
        pstruAsnFullPositionVector->posConfidence = CALLOC(1, sizeof(PositionConfidenceSet_t));
        if (NULL == pstruAsnFullPositionVector->posConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_PositionConfidenceSet_DfEnc(pstruAsnFullPositionVector->posConfidence, &(pstruWjFullPositionVector->struposConfidence));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PositionConfidenceSet_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnFullPositionVector->posConfidence = NULL;
    }
    if (WJV3_PRESENT == pstruWjFullPositionVector->u8motionCfd_Present)
    {
        pstruAsnFullPositionVector->motionCfd = CALLOC(1, sizeof(MotionConfidenceSet_t));
        if (NULL == pstruAsnFullPositionVector->motionCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_MotionConfidenceSet_DfEnc(pstruAsnFullPositionVector->motionCfd, &(pstruWjFullPositionVector->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_MotionConfidenceSet_DfEnc is err");
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
 * @brief    WJV3_FullPositionVector_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 FullPositionVector 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_FullPositionVector_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_FullPositionVector *pstruWjFullPosition = (WJV3_STRU_FullPositionVector *)pvoidWjDf;
    FullPositionVector_t *pstruAsnFullPosition = (FullPositionVector_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnFullPosition->utcTime)
    {
        n32Ret = WJV3_DDateTime_DfDec(pstruAsnFullPosition->utcTime, &(pstruWjFullPosition->struutcTime));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_DDateTime_DfDec is err");
            return false;
        }
        pstruWjFullPosition->u8utcTime_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjFullPosition->u8utcTime_Present = WJV3_ABSENT;
    }
    n32Ret = WJV3_Position3D_DfDec(&(pstruAsnFullPosition->pos), &(pstruWjFullPosition->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_Position3D_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnFullPosition->heading)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_HEADING_SIZE < *(pstruAsnFullPosition->heading))
            || (WJV3_MIN_HEADING_SIZE > *(pstruAsnFullPosition->heading)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:heading = %d",
                     *(pstruAsnFullPosition->heading));
            return false;
        }
        #endif
        pstruWjFullPosition->n32heading = *(pstruAsnFullPosition->heading);
        pstruWjFullPosition->u8heading_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjFullPosition->u8heading_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnFullPosition->transmission)
    {
        n32Ret = WJV3_TransmissionState_DeDec(pstruAsnFullPosition->transmission, &(pstruWjFullPosition->enumtransmission));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_TransmissionState_DeDec is err");
            return false;
        }
        pstruWjFullPosition->u8transmission_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjFullPosition->u8transmission_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnFullPosition->speed)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_SPEED_SIZE < *(pstruAsnFullPosition->speed))
            || (WJV3_MIN_SPEED_SIZE > *(pstruAsnFullPosition->speed)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:speed = %d",
                     *(pstruAsnFullPosition->speed));
            return false;
        }
        #endif
        pstruWjFullPosition->n32speed = *(pstruAsnFullPosition->speed);
        pstruWjFullPosition->u8speed_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjFullPosition->u8speed_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnFullPosition->posAccuracy)
    {
        n32Ret = WJV3_PositionConfidenceSet_DfDec(pstruAsnFullPosition->posAccuracy, &(pstruWjFullPosition->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PositionConfidenceSet_DfDec is err");
            return false;
        }
        pstruWjFullPosition->u8posAccuracy_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjFullPosition->u8posAccuracy_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnFullPosition->timeConfidence)
    {
        n32Ret = WJV3_TimeConfidence_DeDec(pstruAsnFullPosition->timeConfidence, &(pstruWjFullPosition->strutimeConfidence));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_TimeConfidence_DeDec is err");
            return false;
        }
        pstruWjFullPosition->u8timeConfidence_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjFullPosition->u8timeConfidence_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnFullPosition->posConfidence)
    {
        n32Ret = WJV3_PositionConfidenceSet_DfDec(pstruAsnFullPosition->posConfidence, &(pstruWjFullPosition->struposConfidence));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PositionConfidenceSet_DfDec is err");
            return false;
        }
        pstruWjFullPosition->u8posConfidence_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjFullPosition->u8posConfidence_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnFullPosition->motionCfd)
    {
        n32Ret = WJV3_MotionConfidenceSet_DfDec(pstruAsnFullPosition->motionCfd, &(pstruWjFullPosition->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_MotionConfidenceSet_DfEnc is err");
            return false;
        }
        pstruWjFullPosition->u8motionCfd_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjFullPosition->u8motionCfd_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_PositionOffsetLL_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PositionOffsetLL 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PositionOffsetLL_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PositionOffsetLL *pstruWjPositionOffsetLL = (WJV3_STRU_PositionOffsetLL *)pvoidWjDf;
    PositionOffsetLL_t *pstruAsnPositionOffsetLL = (PositionOffsetLL_t *)pvoidAsnDf;
    pstruAsnPositionOffsetLL->present = pstruWjPositionOffsetLL->enumpresent;
    switch (pstruWjPositionOffsetLL->enumpresent)
    {
        case WJV3_PositionOffsetLL_PR_NOTHING:
            break;
        case WJV3_PositionOffsetLL_PR_position_LL1:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB12_SIZE <  pstruWjPositionOffsetLL->choice.struposition_LL1.n32lat)
                || (WJV3_MIN_0FFSETLLB12_SIZE >  pstruWjPositionOffsetLL->choice.struposition_LL1.n32lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lat = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL1.n32lat);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL1.lat = pstruWjPositionOffsetLL->choice.struposition_LL1.n32lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB12_SIZE < pstruWjPositionOffsetLL->choice.struposition_LL1.n32lon)
                || (WJV3_MIN_0FFSETLLB12_SIZE > pstruWjPositionOffsetLL->choice.struposition_LL1.n32lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lon = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL1.n32lon);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL1.lon = pstruWjPositionOffsetLL->choice.struposition_LL1.n32lon;
            break;
        case WJV3_PositionOffsetLL_PR_position_LL2:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB14_SIZE < pstruWjPositionOffsetLL->choice.struposition_LL2.n32lat)
                || (WJV3_MIN_0FFSETLLB14_SIZE > pstruWjPositionOffsetLL->choice.struposition_LL2.n32lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lat = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL2.n32lat);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL2.lat = pstruWjPositionOffsetLL->choice.struposition_LL2.n32lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB14_SIZE < pstruWjPositionOffsetLL->choice.struposition_LL2.n32lon)
                || (WJV3_MIN_0FFSETLLB14_SIZE > pstruWjPositionOffsetLL->choice.struposition_LL2.n32lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lon = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL2.n32lon);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL2.lon = pstruWjPositionOffsetLL->choice.struposition_LL2.n32lon;
            break;
        case WJV3_PositionOffsetLL_PR_position_LL3:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB16_SIZE < pstruWjPositionOffsetLL->choice.struposition_LL3.n32lat)
                || (WJV3_MIN_0FFSETLLB16_SIZE > pstruWjPositionOffsetLL->choice.struposition_LL3.n32lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lat = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL3.n32lat);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL3.lat = pstruWjPositionOffsetLL->choice.struposition_LL3.n32lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB16_SIZE < pstruWjPositionOffsetLL->choice.struposition_LL3.n32lon)
                || (WJV3_MIN_0FFSETLLB16_SIZE > pstruWjPositionOffsetLL->choice.struposition_LL3.n32lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lon = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL3.n32lon);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL3.lon = pstruWjPositionOffsetLL->choice.struposition_LL3.n32lon;
            break;
        case WJV3_PositionOffsetLL_PR_position_LL4:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB18_SIZE < pstruWjPositionOffsetLL->choice.struposition_LL4.n32lat)
                || (WJV3_MIN_0FFSETLLB18_SIZE > pstruWjPositionOffsetLL->choice.struposition_LL4.n32lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lat = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL4.n32lat);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL4.lat = pstruWjPositionOffsetLL->choice.struposition_LL4.n32lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB18_SIZE < pstruWjPositionOffsetLL->choice.struposition_LL4.n32lon)
                || (WJV3_MIN_0FFSETLLB18_SIZE > pstruWjPositionOffsetLL->choice.struposition_LL4.n32lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lon = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL4.n32lon);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL4.lon = pstruWjPositionOffsetLL->choice.struposition_LL4.n32lon;
            break;
        case WJV3_PositionOffsetLL_PR_position_LL5:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB22_SIZE < pstruWjPositionOffsetLL->choice.struposition_LL5.n32lat)
                || (WJV3_MIN_0FFSETLLB22_SIZE > pstruWjPositionOffsetLL->choice.struposition_LL5.n32lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lat = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL5.n32lat);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL5.lat = pstruWjPositionOffsetLL->choice.struposition_LL5.n32lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB22_SIZE < pstruWjPositionOffsetLL->choice.struposition_LL5.n32lon)
                || (WJV3_MIN_0FFSETLLB22_SIZE > pstruWjPositionOffsetLL->choice.struposition_LL5.n32lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lon = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL5.n32lon);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL5.lon = pstruWjPositionOffsetLL->choice.struposition_LL5.n32lon;
            break;
        case WJV3_PositionOffsetLL_PR_position_LL6:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB24_SIZE < pstruWjPositionOffsetLL->choice.struposition_LL6.n32lat)
                || (WJV3_MIN_0FFSETLLB24_SIZE > pstruWjPositionOffsetLL->choice.struposition_LL6.n32lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lat = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL6.n32lat);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL6.lat = pstruWjPositionOffsetLL->choice.struposition_LL6.n32lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB24_SIZE < pstruWjPositionOffsetLL->choice.struposition_LL6.n32lon)
                || (WJV3_MIN_0FFSETLLB24_SIZE > pstruWjPositionOffsetLL->choice.struposition_LL6.n32lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lon = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LL6.n32lon);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LL6.lon = pstruWjPositionOffsetLL->choice.struposition_LL6.n32lon;
            break;
        case WJV3_PositionOffsetLL_PR_position_LatLon:
            #ifdef _CHECK_
            if ((WJV3_MAX_LATITUDE_SIZE < pstruWjPositionOffsetLL->choice.struposition_LatLon.n32lat)
                || (WJV3_MIN_LATITUDE_SIZE > pstruWjPositionOffsetLL->choice.struposition_LatLon.n32lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lat = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LatLon.n32lat);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LatLon.lat = pstruWjPositionOffsetLL->choice.struposition_LatLon.n32lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_LONGITUDE_SIZE < pstruWjPositionOffsetLL->choice.struposition_LatLon.n32lon)
                || (WJV3_MIN_LONGITUDE_SIZE > pstruWjPositionOffsetLL->choice.struposition_LatLon.n32lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32lon = %d",
                        pstruWjPositionOffsetLL->choice.struposition_LatLon.n32lon);
                return false;
            }
            #endif
            pstruAsnPositionOffsetLL->choice.position_LatLon.lon = pstruWjPositionOffsetLL->choice.struposition_LatLon.n32lon;
            break;
        default:
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "pstruWjPosition->enumpresent = %d,is error!",
                    pstruWjPositionOffsetLL->enumpresent);
            return false;
    }
    return true;
}
/**
 * @brief    WJV3_PositionOffsetLL_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PositionOffsetLL 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PositionOffsetLL_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PositionOffsetLL *pstruWjPosition = (WJV3_STRU_PositionOffsetLL *)pvoidWjDf;
    PositionOffsetLL_t *pstruAsnOffsetLL = (PositionOffsetLL_t *)pvoidAsnDf;
    pstruWjPosition->enumpresent = pstruAsnOffsetLL->present;
    switch (pstruAsnOffsetLL->present)
    {
        case PositionOffsetLL_PR_NOTHING:
            break;
        case PositionOffsetLL_PR_position_LL1:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB12_SIZE < pstruAsnOffsetLL->choice.position_LL1.lat)
                || (WJV3_MIN_0FFSETLLB12_SIZE > pstruAsnOffsetLL->choice.position_LL1.lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lat = %d",
                        pstruAsnOffsetLL->choice.position_LL1.lat);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL1.n32lat = pstruAsnOffsetLL->choice.position_LL1.lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB12_SIZE < pstruAsnOffsetLL->choice.position_LL1.lon)
                || (WJV3_MIN_0FFSETLLB12_SIZE > pstruAsnOffsetLL->choice.position_LL1.lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lon = %d",
                        pstruAsnOffsetLL->choice.position_LL1.lon);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL1.n32lon = pstruAsnOffsetLL->choice.position_LL1.lon;
            break;
        case PositionOffsetLL_PR_position_LL2:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB14_SIZE < pstruAsnOffsetLL->choice.position_LL2.lat)
                || (WJV3_MIN_0FFSETLLB14_SIZE > pstruAsnOffsetLL->choice.position_LL2.lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lat = %d",
                        pstruAsnOffsetLL->choice.position_LL2.lat);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL2.n32lat = pstruAsnOffsetLL->choice.position_LL2.lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB14_SIZE < pstruAsnOffsetLL->choice.position_LL2.lon)
                || (WJV3_MIN_0FFSETLLB14_SIZE > pstruAsnOffsetLL->choice.position_LL2.lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lon = %d",
                        pstruAsnOffsetLL->choice.position_LL2.lon);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL2.n32lon = pstruAsnOffsetLL->choice.position_LL2.lon;
            break;
        case PositionOffsetLL_PR_position_LL3:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB16_SIZE < pstruAsnOffsetLL->choice.position_LL3.lat)
                || (WJV3_MIN_0FFSETLLB16_SIZE > pstruAsnOffsetLL->choice.position_LL3.lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lat = %d",
                        pstruAsnOffsetLL->choice.position_LL3.lat);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL3.n32lat = pstruAsnOffsetLL->choice.position_LL3.lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB16_SIZE < pstruAsnOffsetLL->choice.position_LL3.lon)
                || (WJV3_MIN_0FFSETLLB16_SIZE > pstruAsnOffsetLL->choice.position_LL3.lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lon = %d",
                        pstruAsnOffsetLL->choice.position_LL3.lon);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL3.n32lon = pstruAsnOffsetLL->choice.position_LL3.lon;
            break;
        case PositionOffsetLL_PR_position_LL4:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB18_SIZE < pstruAsnOffsetLL->choice.position_LL4.lat)
                || (WJV3_MIN_0FFSETLLB18_SIZE > pstruAsnOffsetLL->choice.position_LL4.lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lat = %d",
                        pstruAsnOffsetLL->choice.position_LL4.lat);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL4.n32lat = pstruAsnOffsetLL->choice.position_LL4.lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB18_SIZE < pstruAsnOffsetLL->choice.position_LL4.lon)
                || (WJV3_MIN_0FFSETLLB18_SIZE > pstruAsnOffsetLL->choice.position_LL4.lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lon = %d",
                        pstruAsnOffsetLL->choice.position_LL4.lon);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL4.n32lon = pstruAsnOffsetLL->choice.position_LL4.lon;
            break;
        case PositionOffsetLL_PR_position_LL5:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB22_SIZE < pstruAsnOffsetLL->choice.position_LL5.lat)
                || (WJV3_MIN_0FFSETLLB22_SIZE > pstruAsnOffsetLL->choice.position_LL5.lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lat = %d",
                        pstruAsnOffsetLL->choice.position_LL5.lat);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL5.n32lat = pstruAsnOffsetLL->choice.position_LL5.lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB22_SIZE < pstruAsnOffsetLL->choice.position_LL5.lon)
                || (WJV3_MIN_0FFSETLLB22_SIZE > pstruAsnOffsetLL->choice.position_LL5.lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lon = %d",
                        pstruAsnOffsetLL->choice.position_LL5.lon);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL5.n32lon = pstruAsnOffsetLL->choice.position_LL5.lon;
            break;
        case PositionOffsetLL_PR_position_LL6:
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB24_SIZE < pstruAsnOffsetLL->choice.position_LL6.lat)
                || (WJV3_MIN_0FFSETLLB24_SIZE > pstruAsnOffsetLL->choice.position_LL6.lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lat = %d",
                        pstruAsnOffsetLL->choice.position_LL6.lat);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL6.n32lat = pstruAsnOffsetLL->choice.position_LL6.lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_0FFSETLLB24_SIZE < pstruAsnOffsetLL->choice.position_LL6.lon)
                || (WJV3_MIN_0FFSETLLB24_SIZE > pstruAsnOffsetLL->choice.position_LL6.lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lon = %d",
                        pstruAsnOffsetLL->choice.position_LL6.lon);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LL6.n32lon = pstruAsnOffsetLL->choice.position_LL6.lon;
            break;
        case PositionOffsetLL_PR_position_LatLon:
            #ifdef _CHECK_
            if ((WJV3_MAX_LATITUDE_SIZE < pstruAsnOffsetLL->choice.position_LatLon.lat)
                || (WJV3_MIN_LATITUDE_SIZE > pstruAsnOffsetLL->choice.position_LatLon.lat))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lat = %d",
                        pstruAsnOffsetLL->choice.position_LatLon.lat);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LatLon.n32lat = pstruAsnOffsetLL->choice.position_LatLon.lat;
            #ifdef _CHECK_
            if ((WJV3_MAX_LONGITUDE_SIZE < pstruAsnOffsetLL->choice.position_LatLon.lon)
                || (WJV3_MIN_LONGITUDE_SIZE > pstruAsnOffsetLL->choice.position_LatLon.lon))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:lon = %d",
                        pstruAsnOffsetLL->choice.position_LatLon.lon);
                return false;
            }
            #endif
            pstruWjPosition->choice.struposition_LatLon.n32lon = pstruAsnOffsetLL->choice.position_LatLon.lon;
            break;
        default:
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "pstruAsnOffsetLL->present = %d,is error!",
                    pstruAsnOffsetLL->present);
            return false;
        }
    }
    return true;
}
/**
 * @brief    WJV3_VerticalOffset_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 VerticalOffset 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_VerticalOffset_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_VerticalOffset *pstruWjVerticalOffset = (WJV3_STRU_VerticalOffset *)pvoidWjDf;
    VerticalOffset_t *pstruAsnVerticalOffset = (VerticalOffset_t *)pvoidAsnDf;
    pstruAsnVerticalOffset->present = pstruWjVerticalOffset->present;
    switch (pstruWjVerticalOffset->present)
    {
        case WJV3_VerticalOffset_PR_NOTHING:
            break;
        case WJV3_VerticalOffset_PR_offset1:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB07_SIZE < pstruWjVerticalOffset->choice.n32offset1)
                || (WJV3_MIN_VERTOFFSETB07_SIZE > pstruWjVerticalOffset->choice.n32offset1))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset1 = %d",
                        pstruWjVerticalOffset->choice.n32offset1);
                return false;
            }
            #endif
            pstruAsnVerticalOffset->choice.offset1 = pstruWjVerticalOffset->choice.n32offset1;
            break;
        case WJV3_VerticalOffset_PR_offset2:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB08_SIZE < pstruWjVerticalOffset->choice.n32offset2)
                || (WJV3_MIN_VERTOFFSETB08_SIZE > pstruWjVerticalOffset->choice.n32offset2))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset2 = %d",
                        pstruWjVerticalOffset->choice.n32offset2);
                return false;
            }
            #endif
            pstruAsnVerticalOffset->choice.offset2 = pstruWjVerticalOffset->choice.n32offset2;
            break;
        case WJV3_VerticalOffset_PR_offset3:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB09_SIZE < pstruWjVerticalOffset->choice.n32offset3)
                || (WJV3_MIN_VERTOFFSETB09_SIZE > pstruWjVerticalOffset->choice.n32offset3))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset3 = %d",
                        pstruWjVerticalOffset->choice.n32offset3);
                return false;
            }
            #endif
            pstruAsnVerticalOffset->choice.offset3 = pstruWjVerticalOffset->choice.n32offset3;
            break;
        case WJV3_VerticalOffset_PR_offset4:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB10_SIZE < pstruWjVerticalOffset->choice.n32offset4)
                || (WJV3_MIN_VERTOFFSETB10_SIZE > pstruWjVerticalOffset->choice.n32offset4))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset4 = %d",
                        pstruWjVerticalOffset->choice.n32offset4);
                return false;
            }
            #endif
            pstruAsnVerticalOffset->choice.offset4 = pstruWjVerticalOffset->choice.n32offset4;
            break;
        case WJV3_VerticalOffset_PR_offset5:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB11_SIZE < pstruWjVerticalOffset->choice.n32offset5)
                || (WJV3_MIN_VERTOFFSETB11_SIZE > pstruWjVerticalOffset->choice.n32offset5))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset5 = %d",
                        pstruWjVerticalOffset->choice.n32offset5);
                return false;
            }
            #endif
            pstruAsnVerticalOffset->choice.offset5 = pstruWjVerticalOffset->choice.n32offset5;
            break;
        case WJV3_VerticalOffset_PR_offset6:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB12_SIZE < pstruWjVerticalOffset->choice.n32offset6)
                || (WJV3_MIN_VERTOFFSETB12_SIZE > pstruWjVerticalOffset->choice.n32offset6))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset6 = %d",
                        pstruWjVerticalOffset->choice.n32offset6);
                return false;
            }
            #endif
            pstruAsnVerticalOffset->choice.offset6 = pstruWjVerticalOffset->choice.n32offset6;
            break;
        case WJV3_VerticalOffset_PR_elevation:
            #ifdef _CHECK_
            if ((WJV3_MAX_ELEVATION_SIZE < pstruWjVerticalOffset->choice.n32elevation)
                || (WJV3_MIN_ELEVATION_SIZE > pstruWjVerticalOffset->choice.n32elevation))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32elevation = %d",
                        pstruWjVerticalOffset->choice.n32elevation);
                return false;
            }
            #endif
            pstruAsnVerticalOffset->choice.elevation = pstruWjVerticalOffset->choice.n32elevation;
            break;
        default:
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "pstruWjOffsetv->present = %d,is error!",
                    pstruWjVerticalOffset->present);
            return false;
    }
    return true;
}
/**
 * @brief    WJV3_VerticalOffset_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 VerticalOffset 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_VerticalOffset_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_VerticalOffset *pstruWjOffsetv = (WJV3_STRU_VerticalOffset *)pvoidWjDf;
    VerticalOffset_t *pstruAsnOffsetv = (VerticalOffset_t *)pvoidAsnDf;
    pstruWjOffsetv->present = pstruAsnOffsetv->present;
    switch (pstruAsnOffsetv->present)
    {
        case VerticalOffset_PR_NOTHING:
            break;
        case VerticalOffset_PR_offset1:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB07_SIZE < pstruAsnOffsetv->choice.offset1)
                || (WJV3_MIN_VERTOFFSETB07_SIZE > pstruAsnOffsetv->choice.offset1))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset1 = %d",
                        pstruAsnOffsetv->choice.offset1);
                return false;
            }
            #endif
            pstruWjOffsetv->choice.n32offset1 = pstruAsnOffsetv->choice.offset1;
            break;
        case VerticalOffset_PR_offset2:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB08_SIZE < pstruAsnOffsetv->choice.offset2)
                || (WJV3_MIN_VERTOFFSETB08_SIZE > pstruAsnOffsetv->choice.offset2))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset2 = %d",
                        pstruAsnOffsetv->choice.offset2);
                return false;
            }
            #endif
            pstruWjOffsetv->choice.n32offset2 = pstruAsnOffsetv->choice.offset2;
            break;
        case VerticalOffset_PR_offset3:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB09_SIZE < pstruAsnOffsetv->choice.offset3)
                || (WJV3_MIN_VERTOFFSETB09_SIZE > pstruAsnOffsetv->choice.offset3))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset3 = %d",
                        pstruAsnOffsetv->choice.offset3);
                return false;
            }
            #endif
            pstruWjOffsetv->choice.n32offset3 = pstruAsnOffsetv->choice.offset3;
            break;
        case VerticalOffset_PR_offset4:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB10_SIZE < pstruAsnOffsetv->choice.offset4)
                || (WJV3_MIN_VERTOFFSETB10_SIZE > pstruAsnOffsetv->choice.offset4))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset4 = %d",
                        pstruAsnOffsetv->choice.offset4);
                return false;
            }
            #endif
            pstruWjOffsetv->choice.n32offset4 = pstruAsnOffsetv->choice.offset4;
            break;
        case VerticalOffset_PR_offset5:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB11_SIZE < pstruAsnOffsetv->choice.offset5)
                || (WJV3_MIN_VERTOFFSETB11_SIZE > pstruAsnOffsetv->choice.offset5))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset5 = %d",
                        pstruAsnOffsetv->choice.offset5);
                return false;
            }
            #endif
            pstruWjOffsetv->choice.n32offset5 = pstruAsnOffsetv->choice.offset5;
            break;
        case VerticalOffset_PR_offset6:
            #ifdef _CHECK_
            if ((WJV3_MAX_VERTOFFSETB12_SIZE < pstruAsnOffsetv->choice.offset6)
                || (WJV3_MIN_VERTOFFSETB12_SIZE > pstruAsnOffsetv->choice.offset6))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32offset6 = %d",
                        pstruAsnOffsetv->choice.offset6);
                return false;
            }
            #endif
            pstruWjOffsetv->choice.n32offset6 = pstruAsnOffsetv->choice.offset6;
            break;
        case VerticalOffset_PR_elevation:
            #ifdef _CHECK_
            if ((WJV3_MAX_ELEVATION_SIZE < pstruAsnOffsetv->choice.elevation)
                || (WJV3_MIN_ELEVATION_SIZE > pstruAsnOffsetv->choice.elevation))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:n32elevation = %d",
                        pstruAsnOffsetv->choice.elevation);
                return false;
            }
            #endif
            pstruWjOffsetv->choice.n32elevation = pstruAsnOffsetv->choice.elevation;
            break;
        default:
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "pstruAsnOffsetv->present = %d,is error!",
                    pstruAsnOffsetv->present);
            return false;
    }
    return true;
}
/**
 * @brief    WJV3_PositionOffsetLLV_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PositionOffsetLLV 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PositionOffsetLLV_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PositionOffsetLLV *pstruWjPositionOffsetLLV = (WJV3_STRU_PositionOffsetLLV *)pvoidWjDf;
    PositionOffsetLLV_t *pstruAsnPositionOffsetLLV = (PositionOffsetLLV_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_PositionOffsetLL_DfEnc(&(pstruAsnPositionOffsetLLV->offsetLL), &(pstruWjPositionOffsetLLV->struoffsetLL));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionOffsetLL_DfEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjPositionOffsetLLV->u8offsetV_Present)
    {
        pstruAsnPositionOffsetLLV->offsetV = CALLOC(1, sizeof(VerticalOffset_t));
        if (NULL == pstruAsnPositionOffsetLLV->offsetV)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_VerticalOffset_DfEnc(pstruAsnPositionOffsetLLV->offsetV, &(pstruWjPositionOffsetLLV->struoffsetV));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_VerticalOffset_DfEnc is err");
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
 * @brief    WJV3_PositionOffsetLLV_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PositionOffsetLLV 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PositionOffsetLLV_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PositionOffsetLLV *pstruWjPositionOffsetLLV = (WJV3_STRU_PositionOffsetLLV *)pvoidWjDf;
    PositionOffsetLLV_t *pstruAsnPositionOffsetLLV = (PositionOffsetLLV_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_PositionOffsetLL_DfDec(&(pstruAsnPositionOffsetLLV->offsetLL), &(pstruWjPositionOffsetLLV->struoffsetLL));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionOffsetLL_DfEnc is err");
        return false;
    }
    if (NULL != pstruAsnPositionOffsetLLV->offsetV)
    {
        n32Ret = WJV3_VerticalOffset_DfDec(pstruAsnPositionOffsetLLV->offsetV, &(pstruWjPositionOffsetLLV->struoffsetV));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_VerticalOffset_DfEnc is err");
            return false;
        }
        pstruWjPositionOffsetLLV->u8offsetV_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjPositionOffsetLLV->u8offsetV_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_PathHistoryPoint_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PathHistoryPoint 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PathHistoryPoint_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PathHistoryPoint *pstruWjPathHistoryPoint = (WJV3_STRU_PathHistoryPoint *)pvoidWjDf;
    PathHistoryPoint_t *pstruAsnPathHistoryPoint = (PathHistoryPoint_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_PositionOffsetLLV_DfEnc(&(pstruAsnPathHistoryPoint->llvOffset), &(pstruWjPathHistoryPoint->strullvOffset));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionOffsetLLV_DfEnc is err");
        return false;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_TIMEOFFSET_SIZE < pstruWjPathHistoryPoint->n32timeOffset)
        || (WJV3_MIN_TIMEOFFSET_SIZE > pstruWjPathHistoryPoint->n32timeOffset))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32timeOffset = %d",
                 pstruWjPathHistoryPoint->n32timeOffset);
        return false;
    }
    #endif
    pstruAsnPathHistoryPoint->timeOffset = pstruWjPathHistoryPoint->n32timeOffset;
    if (WJV3_PRESENT == pstruWjPathHistoryPoint->u8speed_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_SPEED_SIZE < pstruWjPathHistoryPoint->n32speed)
            || (WJV3_MIN_SPEED_SIZE > pstruWjPathHistoryPoint->n32speed))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32speed = %d",
                     pstruWjPathHistoryPoint->n32speed);
            return false;
        }
        #endif
        pstruAsnPathHistoryPoint->speed = CALLOC(1, sizeof(Speed_t));
        if (NULL == pstruAsnPathHistoryPoint->speed)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnPathHistoryPoint->speed) = pstruWjPathHistoryPoint->n32speed;
    }
    else
    {
        pstruAsnPathHistoryPoint->speed = NULL;
    }
    if (WJV3_PRESENT == pstruWjPathHistoryPoint->u8posAccuracy_Present)
    {
        pstruAsnPathHistoryPoint->posAccuracy = CALLOC(1, sizeof(struct PositionConfidenceSet));
        if (NULL == pstruAsnPathHistoryPoint->posAccuracy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_PositionConfidenceSet_DfEnc(pstruAsnPathHistoryPoint->posAccuracy, &(pstruWjPathHistoryPoint->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PositionConfidenceSet_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPathHistoryPoint->posAccuracy = NULL;
    }
    if (WJV3_PRESENT == pstruWjPathHistoryPoint->u8heading_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_COARSEHEADING_SIZE < pstruWjPathHistoryPoint->n32heading)
           ||  (WJV3_MIN_COARSEHEADING_SIZE > pstruWjPathHistoryPoint->n32heading))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32heading = %d",
                     pstruWjPathHistoryPoint->n32heading);
            return false;
        }
        #endif
        pstruAsnPathHistoryPoint->heading = CALLOC(1, sizeof(CoarseHeading_t));
        if (NULL == pstruAsnPathHistoryPoint->heading)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnPathHistoryPoint->heading) = pstruWjPathHistoryPoint->n32heading;
    }
    else
    {
        pstruAsnPathHistoryPoint->heading = NULL;
    }
    return true;
}
/**
 * @brief    WJV3_PathHistoryPoint_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PathHistoryPoint 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PathHistoryPoint_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PathHistoryPoint *pstruWjPoint = (WJV3_STRU_PathHistoryPoint *)pvoidWjDf;
    PathHistoryPoint_t *pstruAsnPoint = (PathHistoryPoint_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_PositionOffsetLLV_DfDec(&(pstruAsnPoint->llvOffset), &(pstruWjPoint->strullvOffset));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionOffsetLLV_DfDec is err");
        return false;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_TIMEOFFSET_SIZE < pstruAsnPoint->timeOffset)
        || (WJV3_MIN_TIMEOFFSET_SIZE > pstruAsnPoint->timeOffset))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:timeOffset = %d",
                 pstruAsnPoint->timeOffset);
        return false;
    }
    #endif
    pstruWjPoint->n32timeOffset = pstruAsnPoint->timeOffset;
    if (NULL != pstruAsnPoint->speed)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_SPEED_SIZE < *(pstruAsnPoint->speed))
            || (WJV3_MIN_SPEED_SIZE > *(pstruAsnPoint->speed)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:speed = %d",
                     *(pstruAsnPoint->speed));
            return false;
        }
        #endif
        pstruWjPoint->n32speed = *(pstruAsnPoint->speed);
        pstruWjPoint->u8speed_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjPoint->u8speed_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnPoint->posAccuracy)
    {
        n32Ret = WJV3_PositionConfidenceSet_DfDec(pstruAsnPoint->posAccuracy, &(pstruWjPoint->struposAccuracy));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PositionConfidenceSet_DfDec is err");
            return false;
        }
        pstruWjPoint->u8posAccuracy_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjPoint->u8posAccuracy_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnPoint->heading)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_COARSEHEADING_SIZE < *(pstruAsnPoint->heading))
            || (WJV3_MIN_COARSEHEADING_SIZE > *(pstruAsnPoint->heading)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:heading = %d",
                     *(pstruAsnPoint->heading));
            return false;
        }
        #endif
        pstruWjPoint->n32heading = *(pstruAsnPoint->heading);
        pstruWjPoint->u8heading_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjPoint->u8heading_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_PathHistoryPointList_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PathHistoryPointList 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PathHistoryPointList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PathHistoryPointList *pstruWjPathHistoryPointList = (WJV3_STRU_PathHistoryPointList *)pvoidWjDf;
    PathHistoryPointList_t *pstruAsnPathHistoryPointList = (PathHistoryPointList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    PathHistoryPoint_t *pstruPathHistoryPoint_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_PATHHISTORPOINT_NUM < pstruWjPathHistoryPointList->u8PathHistoryPointNum)
        || (1 > pstruWjPathHistoryPointList->u8PathHistoryPointNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8PathHistoryPointNum = %d",
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
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_PathHistoryPoint_DfEnc(pstruPathHistoryPoint_node, &(pstruWjPathHistoryPointList->struPathHistoryPointList[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_PathHistoryPoint_DfEnc is err");
            FREEMEM(pstruPathHistoryPoint_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnPathHistoryPointList->list), pstruPathHistoryPoint_node);
    }
    return true;
}
/**
 * @brief    WJV3_PathHistoryPointList_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PathHistoryPointList 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PathHistoryPointList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PathHistoryPointList *pstruWjPathHistoryPointList = (WJV3_STRU_PathHistoryPointList *)pvoidWjDf;
    PathHistoryPointList_t *pstruAsnPathHistoryPointList = (PathHistoryPointList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_PATHHISTORPOINT_NUM < pstruAsnPathHistoryPointList->list.count)
        || (1 > pstruAsnPathHistoryPointList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnPathHistoryPointList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnPathHistoryPointList->list.count; u32i++)
    {
        n32Ret = WJV3_PathHistoryPoint_DfDec(pstruAsnPathHistoryPointList->list.array[u32i],
                                           &(pstruWjPathHistoryPointList->struPathHistoryPointList[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PathHistoryPoint_DfDec is err");
            return false;
        }
    }
    pstruWjPathHistoryPointList->u8PathHistoryPointNum = (uint8_t)u32i;
    return true;
}
/**
 * @brief    WJV3_PathHistory_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PathHistory 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PathHistory_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PathHistory *pstruWjPathHistory = (WJV3_STRU_PathHistory *)pvoidWjDf;
    PathHistory_t *pstruAsnPathHistory = (PathHistory_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV3_PRESENT == pstruWjPathHistory->u8initialPosition_Present)
    {
        pstruAsnPathHistory->initialPosition = CALLOC(1, sizeof(FullPositionVector_t));
        if (NULL == pstruAsnPathHistory->initialPosition)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_FullPositionVector_DfEnc(pstruAsnPathHistory->initialPosition, &(pstruWjPathHistory->struinitialPosition));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_FullPositionVector_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPathHistory->initialPosition = NULL;
    }
    if (WJV3_PRESENT == pstruWjPathHistory->u8currGNSSstatus_Present)
    {
        pstruAsnPathHistory->currGNSSstatus = CALLOC(1, sizeof(GNSSstatus_t));
        if (NULL == pstruAsnPathHistory->currGNSSstatus)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnPathHistory->currGNSSstatus->size = WJV3_LEN_BYTE_CURRGNSSSTATUS;
        pstruAsnPathHistory->currGNSSstatus->bits_unused = (8 * WJV3_LEN_BYTE_CURRGNSSSTATUS) - WJV3_LEN_BITSTR_CURRGNSSSTATUS;
        pstruAsnPathHistory->currGNSSstatus->buf = CALLOC(1, pstruAsnPathHistory->currGNSSstatus->size);
        if (NULL == pstruAsnPathHistory->currGNSSstatus->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeEnc(pstruAsnPathHistory->currGNSSstatus, pstruWjPathHistory->u.u8currGNSSstatus);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_BITSTRING_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnPathHistory->currGNSSstatus = NULL;
    }
    n32Ret = WJV3_PathHistoryPointList_DfEnc(&(pstruAsnPathHistory->crumbData), &(pstruWjPathHistory->strucrumbData));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PathHistoryPointList_DfEnc is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_PathHistory_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PathHistory 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PathHistory_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PathHistory *pstruWjPathHistory = (WJV3_STRU_PathHistory *)pvoidWjDf;
    PathHistory_t *pstruAsnPathHistory = (PathHistory_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnPathHistory->initialPosition)
    {
        n32Ret = WJV3_FullPositionVector_DfDec(pstruAsnPathHistory->initialPosition, &(pstruWjPathHistory->struinitialPosition));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_FullPositionVector_DfDec is err");
            return false;
        }
        pstruWjPathHistory->u8initialPosition_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjPathHistory->u8initialPosition_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnPathHistory->currGNSSstatus)
    {
        if ((NULL == pstruAsnPathHistory->currGNSSstatus->buf)
            || (WJV3_LEN_BYTE_CURRGNSSSTATUS != pstruAsnPathHistory->currGNSSstatus->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:size = %d",
                     pstruAsnPathHistory->currGNSSstatus->size);
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeDec(pstruAsnPathHistory->currGNSSstatus, pstruWjPathHistory->u.u8currGNSSstatus);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeDec is err");
            return false;
        }
        pstruWjPathHistory->u8currGNSSstatus_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjPathHistory->u8currGNSSstatus_Present = WJV3_ABSENT;
    }
    n32Ret = WJV3_PathHistoryPointList_DfDec(&(pstruAsnPathHistory->crumbData), &(pstruWjPathHistory->strucrumbData));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PathHistoryPointList_DfDec is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_PathPrediction_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PathPrediction 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PathPrediction_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PathPrediction *pstruWjPathPrediction = (WJV3_STRU_PathPrediction *)pvoidWjDf;
    PathPrediction_t *pstruAsnPathPrediction = (PathPrediction_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_RADIUSOFCURVATURE_SIZE < pstruWjPathPrediction->n32radiusOfCurve)
        || (WJV3_MIN_RADIUSOFCURVATURE_SIZE > pstruWjPathPrediction->n32radiusOfCurve))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32radiusOfCurve = %d",
                 pstruWjPathPrediction->n32radiusOfCurve);
        return false;
    }
    #endif
    pstruAsnPathPrediction->radiusOfCurve = pstruWjPathPrediction->n32radiusOfCurve;
    #ifdef _CHECK_
    if ((WJV3_MAX_CONFIDENCE_SIZE < pstruWjPathPrediction->n32confidence)
        || (WJV3_MIN_CONFIDENCE_SIZE > pstruWjPathPrediction->n32confidence))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32confidence = %d",
                 pstruWjPathPrediction->n32confidence);
        return false;
    }
    #endif
    pstruAsnPathPrediction->confidence = pstruWjPathPrediction->n32confidence;
    return true;
}
/**
 * @brief    WJV3_PathPrediction_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PathPrediction 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PathPrediction_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PathPrediction *pstruWjPathPrediction = (WJV3_STRU_PathPrediction *)pvoidWjDf;
    PathPrediction_t *pstruAsnPathPrediction = (PathPrediction_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_RADIUSOFCURVATURE_SIZE < pstruAsnPathPrediction->radiusOfCurve)
        || (WJV3_MIN_RADIUSOFCURVATURE_SIZE > pstruAsnPathPrediction->radiusOfCurve))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:radiusOfCurve = %d",
                 pstruAsnPathPrediction->radiusOfCurve);
        return false;
    }
    #endif
    pstruWjPathPrediction->n32radiusOfCurve = pstruAsnPathPrediction->radiusOfCurve;
    #ifdef _CHECK_
    if ((WJV3_MAX_CONFIDENCE_SIZE < pstruAsnPathPrediction->confidence)
        || (WJV3_MIN_CONFIDENCE_SIZE > pstruAsnPathPrediction->confidence))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:confidence = %d",
                 pstruAsnPathPrediction->confidence);
        return false;
    }
    #endif
    pstruWjPathPrediction->n32confidence = pstruAsnPathPrediction->confidence;
    return true;
}
/**
 * @brief    WJV3_VehicleSafetyExtensions_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 VehicleSafetyExtensions 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_VehicleSafetyExtensions_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_VehicleSafetyExtensions *pstruWjVehicleSafetyExtensions = (WJV3_STRU_VehicleSafetyExtensions *)pvoidWjDf;
    VehicleSafetyExtensions_t *pstruAsnVehicleSafetyExtensions = (VehicleSafetyExtensions_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV3_PRESENT == pstruWjVehicleSafetyExtensions->u8events_Present)
    {
        pstruAsnVehicleSafetyExtensions->events = CALLOC(1, sizeof(VehicleEventFlags_t));
        if (NULL == pstruAsnVehicleSafetyExtensions->events)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnVehicleSafetyExtensions->events->size = WJV3_LEN_BYTE_EVENTS;
        pstruAsnVehicleSafetyExtensions->events->bits_unused =  (8 * WJV3_LEN_BYTE_EVENTS) - WJV3_LEN_BITSTR_EVENTS;
        pstruAsnVehicleSafetyExtensions->events->buf = CALLOC(1, pstruAsnVehicleSafetyExtensions->events->size);
        if (NULL == pstruAsnVehicleSafetyExtensions->events->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeEnc(pstruAsnVehicleSafetyExtensions->events, pstruWjVehicleSafetyExtensions->u1.u8events);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_BITSTRING_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnVehicleSafetyExtensions->events = NULL;
    }
    if (WJV3_PRESENT == pstruWjVehicleSafetyExtensions->u8pathHistory_Present)
    {
        pstruAsnVehicleSafetyExtensions->pathHistory = CALLOC(1, sizeof(struct PathHistory));
        if (NULL == pstruAsnVehicleSafetyExtensions->pathHistory)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_PathHistory_DfEnc(pstruAsnVehicleSafetyExtensions->pathHistory, &(pstruWjVehicleSafetyExtensions->strupathHistory));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PathHistory_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnVehicleSafetyExtensions->pathHistory = NULL;
    }
    if (WJV3_PRESENT == pstruWjVehicleSafetyExtensions->u8pathPrediction_Present)
    {
        pstruAsnVehicleSafetyExtensions->pathPrediction = CALLOC(1, sizeof(PathPrediction_t));
        if (NULL == pstruAsnVehicleSafetyExtensions->pathPrediction)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_PathPrediction_DfEnc(pstruAsnVehicleSafetyExtensions->pathPrediction, &(pstruWjVehicleSafetyExtensions->strupathPrediction));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PathPrediction_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnVehicleSafetyExtensions->pathPrediction = NULL;
    }
    if (WJV3_PRESENT == pstruWjVehicleSafetyExtensions->u8lights_Present)
    {
        pstruAsnVehicleSafetyExtensions->lights = CALLOC(1, sizeof(ExteriorLights_t));
        if (NULL == pstruAsnVehicleSafetyExtensions->lights)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnVehicleSafetyExtensions->lights->size = WJV3_LEN_BYTE_LIGHTS;
        pstruAsnVehicleSafetyExtensions->lights->bits_unused = (8 * WJV3_LEN_BYTE_LIGHTS) - WJV3_LEN_BITSTR_LIGHTS;
        pstruAsnVehicleSafetyExtensions->lights->buf = CALLOC(1, pstruAsnVehicleSafetyExtensions->lights->size);
        if (NULL == pstruAsnVehicleSafetyExtensions->lights->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeEnc(pstruAsnVehicleSafetyExtensions->lights, pstruWjVehicleSafetyExtensions->u2.u8lights);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_BITSTRING_DeEnc is err");
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
 * @brief    WJV3_VehicleSafetyExtensions_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 VehicleSafetyExtensions 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_VehicleSafetyExtensions_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_VehicleSafetyExtensions *pstruWjVehicleSafety = (WJV3_STRU_VehicleSafetyExtensions *)pvoidWjDf;
    VehicleSafetyExtensions_t *pstruAsnVehicleSafety = (VehicleSafetyExtensions_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnVehicleSafety->events)
    {
        if ((NULL == pstruAsnVehicleSafety->events->buf)
            || (WJV3_LEN_BYTE_EVENTS != pstruAsnVehicleSafety->events->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:size = %d",
                     pstruAsnVehicleSafety->events->size);
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeDec(pstruAsnVehicleSafety->events, pstruWjVehicleSafety->u1.u8events);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeDec is err");
            return false;
        }
        pstruWjVehicleSafety->u8events_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjVehicleSafety->u8events_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnVehicleSafety->pathHistory)
    {
        n32Ret = WJV3_PathHistory_DfDec(pstruAsnVehicleSafety->pathHistory, &(pstruWjVehicleSafety->strupathHistory));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PathHistory_DfDec is err");
            return false;
        }
        pstruWjVehicleSafety->u8pathHistory_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjVehicleSafety->u8pathHistory_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnVehicleSafety->pathPrediction)
    {
        n32Ret = WJV3_PathPrediction_DfDec(pstruAsnVehicleSafety->pathPrediction, &(pstruWjVehicleSafety->strupathPrediction));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PathPrediction_DfDec is err");
            return false;
        }
        pstruWjVehicleSafety->u8pathPrediction_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjVehicleSafety->u8pathPrediction_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnVehicleSafety->lights)
    {
        if ((NULL == pstruAsnVehicleSafety->lights->buf)
            || (WJV3_LEN_BYTE_LIGHTS != pstruAsnVehicleSafety->lights->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:size = %d",
                     pstruAsnVehicleSafety->lights->size);
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeDec(pstruAsnVehicleSafety->lights, pstruWjVehicleSafety->u2.u8lights);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeDec is err");
            return false;
        }
        pstruWjVehicleSafety->u8lights_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjVehicleSafety->u8lights_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_NodeReferenceID_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 NodeReferenceID 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_NodeReferenceID_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_NodeReferenceID *pstruWjNodeReferenceID = (WJV3_STRU_NodeReferenceID *)pvoidWjDf;
    NodeReferenceID_t *pstruAsnNodeReferenceID = (NodeReferenceID_t *)pvoidAsnDf;
    if (WJV3_PRESENT == pstruWjNodeReferenceID->u8region_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_ROADREGULATORID_SIZE < pstruWjNodeReferenceID->n32region)
            || (WJV3_MIN_ROADREGULATORID_SIZE > pstruWjNodeReferenceID->n32region))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32region = %d",
                     pstruWjNodeReferenceID->n32region);
            return false;
        }
        #endif
        pstruAsnNodeReferenceID->region = CALLOC(1, sizeof(RoadRegulatorID_t));
        if (NULL == pstruAsnNodeReferenceID->region)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnNodeReferenceID->region) = pstruWjNodeReferenceID->n32region;
    }
    else
    {
        pstruAsnNodeReferenceID->region = NULL;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_NODEID_SIZE < pstruWjNodeReferenceID->n32id)
        || (WJV3_MIN_NODEID_SIZE > pstruWjNodeReferenceID->n32id))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32id = %d",
                 pstruWjNodeReferenceID->n32id);
        return false;
    }
    #endif
    pstruAsnNodeReferenceID->id = pstruWjNodeReferenceID->n32id;
    return true;
}
/**
 * @brief    WJV3_NodeReferenceID_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 NodeReferenceID 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_NodeReferenceID_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_NodeReferenceID *pstruWjReferenceID = (WJV3_STRU_NodeReferenceID *)pvoidWjDf;
    NodeReferenceID_t *pstruAsnReferenceID = (NodeReferenceID_t *)pvoidAsnDf;
    if (NULL != pstruAsnReferenceID->region)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_ROADREGULATORID_SIZE < *(pstruAsnReferenceID->region))
            || (WJV3_MIN_ROADREGULATORID_SIZE > *(pstruAsnReferenceID->region)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:region = %d",
                     *(pstruAsnReferenceID->region));
            return false;
        }
        #endif
        pstruWjReferenceID->n32region = *(pstruAsnReferenceID->region);
        pstruWjReferenceID->u8region_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjReferenceID->u8region_Present = WJV3_ABSENT;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_NODEID_SIZE < pstruAsnReferenceID->id)
        || (WJV3_MIN_NODEID_SIZE > pstruAsnReferenceID->id))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:id = %d",
                 pstruAsnReferenceID->id);
        return false;
    }
    #endif
    pstruWjReferenceID->n32id = pstruAsnReferenceID->id;
    return true;
}
/**
 * @brief    WJV3_RegulatorySpeedLimit_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 RegulatorySpeedLimit 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_RegulatorySpeedLimit_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_RegulatorySpeedLimit *pstruWjRegulatorySpeedLimit = (WJV3_STRU_RegulatorySpeedLimit *)pvoidWjDf;
    RegulatorySpeedLimit_t *pstruAsnRegulatorySpeedLimit = (RegulatorySpeedLimit_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_SpeedLimitType_DeEnc(&(pstruAsnRegulatorySpeedLimit->type), &(pstruWjRegulatorySpeedLimit->enumtype));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_SpeedLimitType_DeEnc is err");
        return false;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_SPEED_SIZE < pstruWjRegulatorySpeedLimit->n32speed)
        || (WJV3_MIN_SPEED_SIZE > pstruWjRegulatorySpeedLimit->n32speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32speed = %d",
                 pstruWjRegulatorySpeedLimit->n32speed);
        return false;
    }
    #endif
    pstruAsnRegulatorySpeedLimit->speed = pstruWjRegulatorySpeedLimit->n32speed;
    return true;
}
/**
 * @brief    WJV3_RegulatorySpeedLimit_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 RegulatorySpeedLimit 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_RegulatorySpeedLimit_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_RegulatorySpeedLimit *pstruWjRegulatorySpeedLimit = (WJV3_STRU_RegulatorySpeedLimit *)pvoidWjDf;
    RegulatorySpeedLimit_t *pstruAsnRegulatorySpeedLimit = (RegulatorySpeedLimit_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_SpeedLimitType_DeDec(&(pstruAsnRegulatorySpeedLimit->type), &(pstruWjRegulatorySpeedLimit->enumtype));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_SpeedLimitType_DeDec is err");
        return false;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_SPEED_SIZE < pstruAsnRegulatorySpeedLimit->speed)
        || (WJV3_MIN_SPEED_SIZE > pstruAsnRegulatorySpeedLimit->speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:speed = %d",
                 pstruAsnRegulatorySpeedLimit->speed);
        return false;
    }
    #endif
    pstruWjRegulatorySpeedLimit->n32speed = pstruAsnRegulatorySpeedLimit->speed;
    return true;
}
/**
 * @brief    WJV3_SpeedLimitList_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 SpeedLimitList 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_SpeedLimitList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_SpeedLimitList *pstruWjspeed = (WJV3_STRU_SpeedLimitList *)pvoidWjDf;
    SpeedLimitList_t *pstruAsnspeed = (SpeedLimitList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    RegulatorySpeedLimit_t *pstruRegulatorySpeedLimit_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_REGULATORYSPEEDLIMIT_NUM < pstruWjspeed->u8RegulatorySpeedLimitNum)
        || (1 > pstruWjspeed->u8RegulatorySpeedLimitNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8RegulatorySpeedLimitNum = %d",
                 pstruWjspeed->u8RegulatorySpeedLimitNum);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruWjspeed->u8RegulatorySpeedLimitNum; u32i++)
    {
        pstruRegulatorySpeedLimit_node = CALLOC(1, sizeof(RegulatorySpeedLimit_t));
        if (NULL == pstruRegulatorySpeedLimit_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_RegulatorySpeedLimit_DfEnc(pstruRegulatorySpeedLimit_node, &(pstruWjspeed->struRegulatorySpeedLimitlist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "WJV3_RegulatorySpeedLimit_DfEnc is err");
            FREEMEM(pstruRegulatorySpeedLimit_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnspeed->list), pstruRegulatorySpeedLimit_node);
    }
    return true;
}
/**
 * @brief    WJV3_SpeedLimitList_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 SpeedLimitList 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_SpeedLimitList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_SpeedLimitList *pstruWjspeed = (WJV3_STRU_SpeedLimitList *)pvoidWjDf;
    SpeedLimitList_t *pstruAsnspeed = (SpeedLimitList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_REGULATORYSPEEDLIMIT_NUM < pstruAsnspeed->list.count)
        || (1 > pstruAsnspeed->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnspeed->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnspeed->list.count; u32i++)
    {
        n32Ret = WJV3_RegulatorySpeedLimit_DfDec(pstruAsnspeed->list.array[u32i],
                                               &(pstruWjspeed->struRegulatorySpeedLimitlist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_RegulatorySpeedLimit_DfDec is err");
            return false;
        }
    }
    pstruWjspeed->u8RegulatorySpeedLimitNum = (uint8_t)u32i;
    return true;
}
/**
 * @brief    WJV3_RoadPoint_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 RoadPoint 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_RoadPoint_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_RoadPoint *pstruWjPoint = (WJV3_STRU_RoadPoint *)pvoidWjDf;
    RoadPoint_t *pstruAsnPoint = (RoadPoint_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_PositionOffsetLLV_DfEnc(&(pstruAsnPoint->posOffset),
                                        &(pstruWjPoint->struposOffset));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionOffsetLLV_DfEnc is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_RoadPoint_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 RoadPoint 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_RoadPoint_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_RoadPoint *pstruWjPoint = (WJV3_STRU_RoadPoint *)pvoidWjDf;
    RoadPoint_t *pstruAsnPoint = (RoadPoint_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_PositionOffsetLLV_DfDec(&(pstruAsnPoint->posOffset),
                                        &(pstruWjPoint->struposOffset));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionOffsetLLV_DfDec is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_PointList_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PointList 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PointList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PointList *pstruWjPointList = (WJV3_STRU_PointList *)pvoidWjDf;
    PointList_t *pstruAsnPointList = (PointList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    RoadPoint_t *pstruRoadPoint_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_ROADPOINT_NUM < pstruWjPointList->u8RoadPointNum)
        || (2 > pstruWjPointList->u8RoadPointNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8RoadPointNum = %d",
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
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_RoadPoint_DfEnc(pstruRoadPoint_node, &(pstruWjPointList->struRoadPointlist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_RoadPoint_DfEnc is err");
            FREEMEM(pstruRoadPoint_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnPointList->list), pstruRoadPoint_node);
    }
    return true;
}
/**
 * @brief    WJV3_PointList_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PointList 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PointList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PointList *pstruWjPointList = (WJV3_STRU_PointList *)pvoidWjDf;
    PointList_t *pstruAsnPointList = (PointList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_ROADPOINT_NUM < pstruAsnPointList->list.count)
        || (2 > pstruAsnPointList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnPointList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnPointList->list.count; u32i++)
    {
        n32Ret = WJV3_RoadPoint_DfDec(pstruAsnPointList->list.array[u32i],
                                    &(pstruWjPointList->struRoadPointlist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_RoadPoint_DfDec is err");
            return false;
        }
    }
    pstruWjPointList->u8RoadPointNum = (uint8_t)u32i;
    return true;
}
/**
 * @brief    WJV3_Movement_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 Movement 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Movement_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Movement *pstruWjMovement = (WJV3_STRU_Movement *)pvoidWjDf;
    Movement_t *pstruAsnMovement = (Movement_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_NodeReferenceID_DfEnc(&(pstruAsnMovement->remoteIntersection), &(pstruWjMovement->struremoteIntersection));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeReferenceID_DfEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjMovement->u8phaseId_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_PHASEID_SIZE < pstruWjMovement->n32phaseId)
            || (WJV3_MIN_PHASEID_SIZE > pstruWjMovement->n32phaseId))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32phaseId = %d",
                     pstruWjMovement->n32phaseId);
            return false;
        }
        #endif
        pstruAsnMovement->phaseId = CALLOC(1, sizeof(*(pstruAsnMovement->phaseId)));
        if (NULL == pstruAsnMovement->phaseId)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnMovement->phaseId) = pstruWjMovement->n32phaseId;
    }
    else
    {
        pstruAsnMovement->phaseId= NULL;
    }
    return true;
}
/**
 * @brief    WJV3_Movement_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 Movement 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Movement_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Movement *pstruWjMovement = (WJV3_STRU_Movement *)pvoidWjDf;
    Movement_t *pstruAsnMovement = (Movement_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_NodeReferenceID_DfDec(&(pstruAsnMovement->remoteIntersection), &(pstruWjMovement->struremoteIntersection));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeReferenceID_DfEnc is err");
        return false;
    }
    if (NULL != pstruAsnMovement->phaseId)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_PHASEID_SIZE < *(pstruAsnMovement->phaseId))
            || (WJV3_MIN_PHASEID_SIZE > *(pstruAsnMovement->phaseId)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:phaseId = %d",
                     *(pstruAsnMovement->phaseId));
            return false;
        }
        #endif
        pstruWjMovement->n32phaseId = *(pstruAsnMovement->phaseId);
        pstruWjMovement->u8phaseId_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjMovement->u8phaseId_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_MovementList_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 MovementList 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_MovementList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_MovementList *pstruWjMovementList = (WJV3_STRU_MovementList *)pvoidWjDf;
    MovementList_t *pstruAsnMovementList = (MovementList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    Movement_t *pstruMovement_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_MOVEMENT_NUM < pstruWjMovementList->u8MovementNum)
        || (1 > pstruWjMovementList->u8MovementNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8MovementNum = %d",
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
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_Movement_DfEnc(pstruMovement_node, &(pstruWjMovementList->struMovementlist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_Movement_DfEnc is err");
            FREEMEM(pstruMovement_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnMovementList->list), pstruMovement_node);
    }
    return true;
}
/**
 * @brief    WJV3_MovementList_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 MovementList 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_MovementList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_MovementList *pstruWjMovementList = (WJV3_STRU_MovementList *)pvoidWjDf;
    MovementList_t *pstruAsnMovementList = (MovementList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_MOVEMENT_NUM < pstruAsnMovementList->list.count)
        || (1 > pstruAsnMovementList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnMovementList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnMovementList->list.count; u32i++)
    {
        n32Ret = WJV3_Movement_DfDec(pstruAsnMovementList->list.array[u32i],
                                   &(pstruWjMovementList->struMovementlist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_Movement_DfDec is err");
            return false;
        }
    }
    pstruWjMovementList->u8MovementNum = (uint8_t)u32i;
    return true;
}
/**
 * @brief    WJV3_LaneTypeAttributes_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 LaneTypeAttributes 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_LaneTypeAttributes_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_LaneTypeAttributes *pstruWjTypeAttributes = (WJV3_STRU_LaneTypeAttributes *)pvoidWjDf;
    LaneTypeAttributes_t *pstruAsnTypeAttributes = (LaneTypeAttributes_t *)pvoidAsnDf;
    pstruAsnTypeAttributes->present = pstruWjTypeAttributes->enumpresent;
    int32_t n32Ret = 0;
    switch (pstruWjTypeAttributes->enumpresent)
    {
        case WJV3_LaneTypeAttributes_PR_NOTHING:
            break;
        case WJV3_LaneTypeAttributes_PR_vehicle:
            pstruAsnTypeAttributes->choice.vehicle.size = WJV3_LEN_BYTE_VEHICLE;
            pstruAsnTypeAttributes->choice.vehicle.size = WJV3_LEN_BYTE_VEHICLE;
            pstruAsnTypeAttributes->choice.vehicle.bits_unused = (8 * WJV3_LEN_BYTE_VEHICLE) - WJV3_LEN_BITSTR_VEHICLE;
            pstruAsnTypeAttributes->choice.vehicle.buf = CALLOC(1, pstruAsnTypeAttributes->choice.vehicle.size);
            if (NULL == pstruAsnTypeAttributes->choice.vehicle.buf)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "calloc is err");
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeEnc(&(pstruAsnTypeAttributes->choice.vehicle), pstruWjTypeAttributes->choice.u1.u8vehicle);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeEnc is err");
                return false;
            }
            break;
        case WJV3_LaneTypeAttributes_PR_crosswalk:
            pstruAsnTypeAttributes->choice.crosswalk.size = WJV3_LEN_BYTE_CROSSWALK;
            pstruAsnTypeAttributes->choice.crosswalk.bits_unused = (8 * WJV3_LEN_BYTE_CROSSWALK) - WJV3_LEN_BITSTR_CROSSWALK;
            pstruAsnTypeAttributes->choice.crosswalk.buf = CALLOC(1, pstruAsnTypeAttributes->choice.crosswalk.size);
            if (NULL == pstruAsnTypeAttributes->choice.crosswalk.buf)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "calloc is err");
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeEnc(&(pstruAsnTypeAttributes->choice.crosswalk), pstruWjTypeAttributes->choice.u2.u8crosswalk);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeEnc is err");
                return false;
            }
            break;
        case WJV3_LaneTypeAttributes_PR_bikeLane:
            pstruAsnTypeAttributes->choice.bikeLane.size = WJV3_LEN_BYTE_BIKELANE;
            pstruAsnTypeAttributes->choice.bikeLane.bits_unused = (8 * WJV3_LEN_BYTE_BIKELANE) - WJV3_LEN_BITSTR_BIKELANE;
            pstruAsnTypeAttributes->choice.bikeLane.buf = CALLOC(1, pstruAsnTypeAttributes->choice.bikeLane.size);
            if (NULL == pstruAsnTypeAttributes->choice.bikeLane.buf)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "calloc is err");
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeEnc(&(pstruAsnTypeAttributes->choice.bikeLane), pstruWjTypeAttributes->choice.u3.u8bikeLane);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeEnc is err");
                return false;
            }
            break;
        case WJV3_LaneTypeAttributes_PR_sidewalk:
            pstruAsnTypeAttributes->choice.sidewalk.size = WJV3_LEN_BYTE_SAIDWALK;
            pstruAsnTypeAttributes->choice.sidewalk.bits_unused = (8 * WJV3_LEN_BYTE_SAIDWALK) - WJV3_LEN_BITSTR_SAIDWALK;
            pstruAsnTypeAttributes->choice.sidewalk.buf = CALLOC(1, pstruAsnTypeAttributes->choice.sidewalk.size);
            if (NULL == pstruAsnTypeAttributes->choice.sidewalk.buf)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "calloc is err");
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeEnc(&(pstruAsnTypeAttributes->choice.sidewalk), pstruWjTypeAttributes->choice.u4.u8sidewalk);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeEnc is err");
                return false;
            }
            break;
        case WJV3_LaneTypeAttributes_PR_median:
            pstruAsnTypeAttributes->choice.median.size = WJV3_LEN_BYTE_BARRIER;
            pstruAsnTypeAttributes->choice.median.bits_unused = (8 * WJV3_LEN_BYTE_BARRIER) - WJV3_LEN_BITSTR_BARRIER;
            pstruAsnTypeAttributes->choice.median.buf = CALLOC(1, pstruAsnTypeAttributes->choice.median.size);
            if (NULL == pstruAsnTypeAttributes->choice.median.buf)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "calloc is err");
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeEnc(&(pstruAsnTypeAttributes->choice.median), pstruWjTypeAttributes->choice.u5.u8median);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeEnc is err");
                return false;
            }
            break;
        case WJV3_LaneTypeAttributes_PR_striping:
            pstruAsnTypeAttributes->choice.striping.size = WJV3_LEN_BYTE_STRIP;
            pstruAsnTypeAttributes->choice.striping.bits_unused = (8 * WJV3_LEN_BYTE_STRIP) - WJV3_LEN_BITSTR_STRIP;
            pstruAsnTypeAttributes->choice.striping.buf = CALLOC(1, pstruAsnTypeAttributes->choice.striping.size);
            if (NULL == pstruAsnTypeAttributes->choice.striping.buf)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "calloc is err");
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeEnc(&(pstruAsnTypeAttributes->choice.striping), pstruWjTypeAttributes->choice.u6.u8striping);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeEnc is err");
                return false;
            }
            break;
        case WJV3_LaneTypeAttributes_PR_trackedVehicle:
            pstruAsnTypeAttributes->choice.trackedVehicle.size = WJV3_LEN_BYTE_TRACKVEH;
            pstruAsnTypeAttributes->choice.trackedVehicle.bits_unused = (8 * WJV3_LEN_BYTE_TRACKVEH) - WJV3_LEN_BITSTR_TRACKVEH;
            pstruAsnTypeAttributes->choice.trackedVehicle.buf = CALLOC(1, pstruAsnTypeAttributes->choice.trackedVehicle.size);
            if (NULL == pstruAsnTypeAttributes->choice.trackedVehicle.buf)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "calloc is err");
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeEnc(&(pstruAsnTypeAttributes->choice.trackedVehicle), pstruWjTypeAttributes->choice.u7.u8trackedVehicle);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeEnc is err");
                return false;
            }
            break;
        case WJV3_LaneTypeAttributes_PR_parking:
            pstruAsnTypeAttributes->choice.parking.size = WJV3_LEN_BYTE_PARK;
            pstruAsnTypeAttributes->choice.parking.bits_unused = (8 * WJV3_LEN_BYTE_PARK) - WJV3_LEN_BITSTR_PARK;
            pstruAsnTypeAttributes->choice.parking.buf = CALLOC(1, pstruAsnTypeAttributes->choice.parking.size);
            if (NULL == pstruAsnTypeAttributes->choice.parking.buf)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "calloc is err");
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeEnc(&(pstruAsnTypeAttributes->choice.parking), pstruWjTypeAttributes->choice.u8.u8parking);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeEnc is err");
                return false;
            }
            break;
        default:
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "out of rangth of  enumpresent %d",
                    pstruWjTypeAttributes->enumpresent);
            return false;
            break;
    }
    return true;
}
/**
 * @brief    WJV3_LaneTypeAttributes_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 LaneTypeAttributes 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_LaneTypeAttributes_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_LaneTypeAttributes *pstruWjTypeAttributes = (WJV3_STRU_LaneTypeAttributes *)pvoidWjDf;
    LaneTypeAttributes_t *pstruAsnTypeAttributes = (LaneTypeAttributes_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    pstruWjTypeAttributes->enumpresent = pstruAsnTypeAttributes->present;
    switch (pstruAsnTypeAttributes->present)
    {
        case LaneTypeAttributes_PR_NOTHING:
            break;
        case LaneTypeAttributes_PR_vehicle:
            if ((NULL == pstruAsnTypeAttributes->choice.vehicle.buf)
                || (WJV3_LEN_BYTE_VEHICLE != pstruAsnTypeAttributes->choice.vehicle.size))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:size = %d",
                        pstruAsnTypeAttributes->choice.vehicle.size);
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeDec(&(pstruAsnTypeAttributes->choice.vehicle), pstruWjTypeAttributes->choice.u1.u8vehicle);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                            STACK_MSG_MODULE,
                            "WJV3_BITSTRING_DeDec is err");
                return false;
            }
            break;
        case LaneTypeAttributes_PR_crosswalk:
            if ((NULL == pstruAsnTypeAttributes->choice.crosswalk.buf)
                || (WJV3_LEN_BYTE_CROSSWALK != pstruAsnTypeAttributes->choice.crosswalk.size))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:size = %d",
                        pstruAsnTypeAttributes->choice.crosswalk.size);
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeDec(&(pstruAsnTypeAttributes->choice.crosswalk), pstruWjTypeAttributes->choice.u2.u8crosswalk);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                            STACK_MSG_MODULE,
                            "WJV3_BITSTRING_DeDec is err");
                return false;
            }
            break;
        case LaneTypeAttributes_PR_bikeLane:
            if ((NULL == pstruAsnTypeAttributes->choice.bikeLane.buf)
                || (WJV3_LEN_BYTE_BIKELANE != pstruAsnTypeAttributes->choice.bikeLane.size))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:size = %d",
                        pstruAsnTypeAttributes->choice.bikeLane.size);
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeDec(&(pstruAsnTypeAttributes->choice.bikeLane), pstruWjTypeAttributes->choice.u3.u8bikeLane);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                            STACK_MSG_MODULE,
                            "WJV3_BITSTRING_DeDec is err");
                return false;
            }
            break;
        case LaneTypeAttributes_PR_sidewalk:
            if ((NULL == pstruAsnTypeAttributes->choice.sidewalk.buf)
                || (WJV3_LEN_BYTE_SAIDWALK != pstruAsnTypeAttributes->choice.sidewalk.size))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:size = %d",
                        pstruAsnTypeAttributes->choice.sidewalk.size);
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeDec(&(pstruAsnTypeAttributes->choice.sidewalk), pstruWjTypeAttributes->choice.u4.u8sidewalk);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                            STACK_MSG_MODULE,
                            "WJV3_BITSTRING_DeDec is err");
                return false;
            }
            break;
        case LaneTypeAttributes_PR_median:
            if ((NULL == pstruAsnTypeAttributes->choice.median.buf)
                || (WJV3_LEN_BYTE_BARRIER != pstruAsnTypeAttributes->choice.median.size))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:size = %d",
                        pstruAsnTypeAttributes->choice.median.size);
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeDec(&(pstruAsnTypeAttributes->choice.median), pstruWjTypeAttributes->choice.u5.u8median);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                            STACK_MSG_MODULE,
                            "WJV3_BITSTRING_DeDec is err");
                return false;
            }
            break;
        case LaneTypeAttributes_PR_striping:
            if ((NULL == pstruAsnTypeAttributes->choice.striping.buf)
                || (WJV3_LEN_BYTE_STRIP != pstruAsnTypeAttributes->choice.striping.size))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:size = %d",
                        pstruAsnTypeAttributes->choice.striping.size);
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeDec(&(pstruAsnTypeAttributes->choice.striping), pstruWjTypeAttributes->choice.u6.u8striping);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                            STACK_MSG_MODULE,
                            "WJV3_BITSTRING_DeDec is err");
                return false;
            }
            break;
        case LaneTypeAttributes_PR_trackedVehicle:
            if ((NULL == pstruAsnTypeAttributes->choice.trackedVehicle.buf)
                || (WJV3_LEN_BYTE_TRACKVEH != pstruAsnTypeAttributes->choice.trackedVehicle.size))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:size = %d",
                        pstruAsnTypeAttributes->choice.trackedVehicle.size);
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeDec(&(pstruAsnTypeAttributes->choice.trackedVehicle), pstruWjTypeAttributes->choice.u7.u8trackedVehicle);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                            STACK_MSG_MODULE,
                            "WJV3_BITSTRING_DeDec is err");
                return false;
            }
            break;
        case LaneTypeAttributes_PR_parking:
            if ((NULL == pstruAsnTypeAttributes->choice.parking.buf)
                || (WJV3_LEN_BYTE_PARK != pstruAsnTypeAttributes->choice.parking.size))
            {
                LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "out of rangth:size = %d",
                        pstruAsnTypeAttributes->choice.parking.size);
                return false;
            }
            n32Ret = WJV3_BITSTRING_DeDec(&(pstruAsnTypeAttributes->choice.parking), pstruWjTypeAttributes->choice.u8.u8parking);
            if (true != n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR,
                            STACK_MSG_MODULE,
                            "WJV3_BITSTRING_DeDec is err");
                return false;
            }
            break;
        default:
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "out of rangth of  present： %d",
                    pstruAsnTypeAttributes->present);
            return false;
            break;
    }
    return true;
}
/**
 * @brief    WJV3_LaneAttributes_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 LaneAttributes 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_LaneAttributes_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_LaneAttributes *pstruWjLaneAttributes = (WJV3_STRU_LaneAttributes *)pvoidWjDf;
    LaneAttributes_t *pstruAsnLaneAttributes = (LaneAttributes_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (WJV3_PRESENT == pstruWjLaneAttributes->u8shareWith_Present)
    {
        pstruAsnLaneAttributes->shareWith = CALLOC(1, sizeof(LaneSharing_t));
        if (NULL == pstruAsnLaneAttributes->shareWith)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnLaneAttributes->shareWith->size = WJV3_LEN_BYTE_SHAREWITH;
        pstruAsnLaneAttributes->shareWith->bits_unused = (8 * WJV3_LEN_BYTE_SHAREWITH) - WJV3_LEN_BITSTR_SHAREWITH;
        pstruAsnLaneAttributes->shareWith->buf = CALLOC(1, pstruAsnLaneAttributes->shareWith->size);
        if (NULL == pstruAsnLaneAttributes->shareWith->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "calloc is err");
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeEnc(pstruAsnLaneAttributes->shareWith, pstruWjLaneAttributes->u.u8shareWith);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "WJV3_BITSTRING_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLaneAttributes->shareWith = NULL;
    }
    n32Ret = WJV3_LaneTypeAttributes_DfEnc(&(pstruAsnLaneAttributes->laneType), &(pstruWjLaneAttributes->strulaneType));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_LaneTypeAttributes_DfEnc is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_LaneAttributes_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 LaneAttributes 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_LaneAttributes_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_LaneAttributes *pstruWjLaneAttributes = (WJV3_STRU_LaneAttributes *)pvoidWjDf;
    LaneAttributes_t *pstruAsnLaneAttributes = (LaneAttributes_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnLaneAttributes->shareWith)
    {
        if ((NULL == pstruAsnLaneAttributes->shareWith->buf)
            || (WJV3_LEN_BYTE_EVENTS != pstruAsnLaneAttributes->shareWith->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:size = %d",
                     pstruAsnLaneAttributes->shareWith->size);
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeDec(pstruAsnLaneAttributes->shareWith, pstruWjLaneAttributes->u.u8shareWith);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeDec is err");
            return false;
        }
        pstruWjLaneAttributes->u8shareWith_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjLaneAttributes->u8shareWith_Present = WJV3_ABSENT;
    }
    n32Ret = WJV3_LaneTypeAttributes_DfDec(&(pstruAsnLaneAttributes->laneType), &(pstruWjLaneAttributes->strulaneType));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_LaneTypeAttributes_DfDec is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_ConnectingLane_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 ConnectingLane 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_ConnectingLane_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_ConnectingLane *pstruWjConnectingLane = (WJV3_STRU_ConnectingLane *)pvoidWjDf;
    ConnectingLane_t *pstruAsnConnectingLane = (ConnectingLane_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_LANEID_SIZE < pstruWjConnectingLane->n32lane)
        || (WJV3_MIN_LANEID_SIZE > pstruWjConnectingLane->n32lane))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32lane = %d",
                 pstruWjConnectingLane->n32lane);
        return false;
    }
    #endif
    pstruAsnConnectingLane->lane = pstruWjConnectingLane->n32lane;
    if (WJV3_PRESENT == pstruWjConnectingLane->u8maneuver_Present)
    {
        pstruAsnConnectingLane->maneuver = CALLOC(1, sizeof(AllowedManeuvers_t));
        if (NULL == pstruAsnConnectingLane->maneuver)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnConnectingLane->maneuver->size = WJV3_LEN_BYTE_MANEUVER;
        pstruAsnConnectingLane->maneuver->bits_unused = (8 * WJV3_LEN_BYTE_MANEUVER) - WJV3_LEN_BITSTR_MANEUVER;
        pstruAsnConnectingLane->maneuver->buf = CALLOC(1, pstruAsnConnectingLane->maneuver->size);
        if (NULL == pstruAsnConnectingLane->maneuver->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "calloc is err");
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeEnc(pstruAsnConnectingLane->maneuver, pstruWjConnectingLane->u.u8maneuver);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "WJV3_BITSTRING_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnConnectingLane->maneuver= NULL;
    }
    return true;
}
/**
 * @brief    WJV3_ConnectingLane_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 ConnectingLane 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_ConnectingLane_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_ConnectingLane *pstruWjConnectingLane = (WJV3_STRU_ConnectingLane *)pvoidWjDf;
    ConnectingLane_t *pstruAsnConnectingLane = (ConnectingLane_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_LANEID_SIZE < pstruAsnConnectingLane->lane)
        || (WJV3_MIN_LANEID_SIZE > pstruAsnConnectingLane->lane))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:lane = %d",
                 pstruAsnConnectingLane->lane);
        return false;
    }
    #endif
    pstruWjConnectingLane->n32lane = pstruAsnConnectingLane->lane;
    if (NULL != pstruAsnConnectingLane->maneuver)
    {
        if ((NULL == pstruAsnConnectingLane->maneuver->buf)
            || (WJV3_LEN_BYTE_EVENTS != pstruAsnConnectingLane->maneuver->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:size = %d",
                     pstruAsnConnectingLane->maneuver->size);
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeDec(pstruAsnConnectingLane->maneuver, pstruWjConnectingLane->u.u8maneuver);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeDec is err");
            return false;
        }
        pstruWjConnectingLane->u8maneuver_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjConnectingLane->u8maneuver_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_Connection_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 Connection 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Connection_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Connection *pstruWjConnection = (WJV3_STRU_Connection *)pvoidWjDf;
    Connection_t *pstruAsnConnection = (Connection_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_NodeReferenceID_DfEnc(&(pstruAsnConnection->remoteIntersection), &(pstruWjConnection->struremoteIntersection));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeReferenceID_DfEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjConnection->u8connectingLane_Present)
    {
        pstruAsnConnection->connectingLane = CALLOC(1, sizeof(struct ConnectingLane));
        if (NULL == pstruAsnConnection->connectingLane)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_ConnectingLane_DfEnc(pstruAsnConnection->connectingLane, &(pstruWjConnection->struconnectingLane));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_ConnectingLane_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnConnection->connectingLane = NULL;
    }
    if (WJV3_PRESENT == pstruWjConnection->u8phase_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_PHASEID_SIZE < pstruWjConnection->n32phaseId)
            || (WJV3_MIN_PHASEID_SIZE > pstruWjConnection->n32phaseId))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32phaseId = %d",
                     pstruWjConnection->n32phaseId);
            return false;
        }
        #endif
        pstruAsnConnection->phaseId = CALLOC(1, sizeof(PhaseID_t));
        if (NULL == pstruAsnConnection->phaseId)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnConnection->phaseId) = pstruWjConnection->n32phaseId;
    }
    else
    {
        pstruAsnConnection->phaseId = NULL;
    }
    return true;
}
/**
 * @brief    WJV3_Connection_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 Connection 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Connection_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Connection *pstruWjConnection = (WJV3_STRU_Connection *)pvoidWjDf;
    Connection_t *pstruAsnConnection = (Connection_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_NodeReferenceID_DfDec(&(pstruAsnConnection->remoteIntersection), &(pstruWjConnection->struremoteIntersection));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeReferenceID_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnConnection->connectingLane)
    {
        n32Ret = WJV3_ConnectingLane_DfDec(pstruAsnConnection->connectingLane, &(pstruWjConnection->struconnectingLane));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_ConnectingLane_DfDec is err");
            return false;
        }
        pstruWjConnection->u8connectingLane_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjConnection->u8connectingLane_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnConnection->phaseId)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_PHASEID_SIZE < *(pstruAsnConnection->phaseId))
            || (WJV3_MIN_PHASEID_SIZE > *(pstruAsnConnection->phaseId)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:phaseId = %d",
                     *(pstruAsnConnection->phaseId));
            return false;
        }
        #endif
        pstruWjConnection->n32phaseId = *(pstruAsnConnection->phaseId);
        pstruWjConnection->u8phase_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjConnection->u8phase_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_ConnectsToList_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 ConnectsToList 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_ConnectsToList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_ConnectsToList *pstruWjConnectsToList = (WJV3_STRU_ConnectsToList *)pvoidWjDf;
    ConnectsToList_t *pstruAsnConnectsToList = (ConnectsToList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    Connection_t *pstruConnection_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_CONNECT_NUM < pstruWjConnectsToList->u8ConnectNum)
        || (1 > pstruWjConnectsToList->u8ConnectNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8ConnectNum = %d",
                 pstruWjConnectsToList->u8ConnectNum);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruWjConnectsToList->u8ConnectNum; u32i++)
    {
        pstruConnection_node = CALLOC(1, sizeof(*(pstruConnection_node)));
        if (NULL == pstruConnection_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_Connection_DfEnc(pstruConnection_node, &(pstruWjConnectsToList->struConnectionlist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_Connection_DfEnc is err");
            FREEMEM(pstruConnection_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnConnectsToList->list), pstruConnection_node);
    }
    return true;
}
/**
 * @brief    WJV3_ConnectsToList_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 ConnectsToList 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_ConnectsToList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_ConnectsToList *pstruWjConnectsToList = (WJV3_STRU_ConnectsToList *)pvoidWjDf;
    ConnectsToList_t *pstruAsnConnectsToList = (ConnectsToList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_CONNECT_NUM < pstruAsnConnectsToList->list.count)
        || (1 > pstruAsnConnectsToList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnConnectsToList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnConnectsToList->list.count; u32i++)
    {
        n32Ret = WJV3_Connection_DfDec(pstruAsnConnectsToList->list.array[u32i],
                                     &(pstruWjConnectsToList->struConnectionlist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_Connection_DfDec is err");
            return false;
        }
    }
    pstruWjConnectsToList->u8ConnectNum = (uint8_t)u32i;
    return true;
}
/**
 * @brief    WJV3_Lane_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 Lane 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Lane_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Lane *pstruWjLane = (WJV3_STRU_Lane *)pvoidWjDf;
    Lane_t *pstruAsnLane = (Lane_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_LANEID_SIZE < pstruWjLane->n32laneID)
        || (WJV3_MIN_LANEID_SIZE > pstruWjLane->n32laneID))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32laneID = %d",
                 pstruWjLane->n32laneID);
        return false;
    }
    #endif
    pstruAsnLane->laneID = pstruWjLane->n32laneID;
    if (WJV3_PRESENT == pstruWjLane->u8laneAttributes_Present)
    {
        pstruAsnLane->laneAttributes = CALLOC(1, sizeof(LaneAttributes_t));
        if (NULL == pstruAsnLane->laneAttributes)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_LaneAttributes_DfEnc(pstruAsnLane->laneAttributes, &(pstruWjLane->strulaneAttributes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_LaneAttributes_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLane->laneAttributes = NULL;
    }
    if (WJV3_PRESENT == pstruWjLane->u8maneuvers_Present)
    {
        pstruAsnLane->maneuvers = CALLOC(1, sizeof(AllowedManeuvers_t));
        if (NULL == pstruAsnLane->maneuvers)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnLane->maneuvers->size = WJV3_LEN_BYTE_MANEUVERS;
        pstruAsnLane->maneuvers->bits_unused = (8 * WJV3_LEN_BYTE_MANEUVERS) - WJV3_LEN_BITSTR_MANEUVERS;
        pstruAsnLane->maneuvers->buf = CALLOC(1, pstruAsnLane->maneuvers->size);
        if (NULL == pstruAsnLane->maneuvers->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeEnc(pstruAsnLane->maneuvers, pstruWjLane->u.u8maneuvers);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_BITSTRING_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLane->maneuvers = NULL;
    }
    if (WJV3_PRESENT == pstruWjLane->u8connectsTo_Present)
    {
        pstruAsnLane->connectsTo = CALLOC(1, sizeof(ConnectsToList_t));
        if (NULL == pstruAsnLane->connectsTo)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_ConnectsToList_DfEnc(pstruAsnLane->connectsTo, &(pstruWjLane->struconnectsTo));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_ConnectsToList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLane->connectsTo = NULL;
    }
    if (WJV3_PRESENT == pstruWjLane->u8speedLimits_Present)
    {
        pstruAsnLane->speedLimits = CALLOC(1, sizeof(SpeedLimitList_t));
        if (NULL == pstruAsnLane->speedLimits)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_SpeedLimitList_DfEnc(pstruAsnLane->speedLimits, &(pstruWjLane->struspeedLimits));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_SpeedLimitList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLane->speedLimits = NULL;
    }
    if (WJV3_PRESENT == pstruWjLane->u8points_Present)
    {
        pstruAsnLane->points = CALLOC(1, sizeof(PointList_t));
        if (NULL == pstruAsnLane->points)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_PointList_DfEnc(pstruAsnLane->points, &(pstruWjLane->strupoints));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PointList_DfEnc is err");
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
 * @brief    WJV3_Lane_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 Lane 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Lane_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Lane *pstruWjLane = (WJV3_STRU_Lane *)pvoidWjDf;
    Lane_t *pstruAsnLane = (Lane_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_LANEID_SIZE < pstruAsnLane->laneID)
        || (WJV3_MIN_LANEID_SIZE > pstruAsnLane->laneID))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:laneID = %d",
                 pstruAsnLane->laneID);
        return false;
    }
    #endif
    pstruWjLane->n32laneID = pstruAsnLane->laneID;
    if (NULL != pstruAsnLane->laneAttributes)
    {
        n32Ret = WJV3_LaneAttributes_DfDec(pstruAsnLane->laneAttributes, &(pstruWjLane->strulaneAttributes));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_LaneAttributes_DfDec is err");
            return false;
        }
        pstruWjLane->u8laneAttributes_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjLane->u8laneAttributes_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnLane->maneuvers)
    {
        if ((NULL == pstruAsnLane->maneuvers->buf)
            || (WJV3_LEN_BYTE_MANEUVERS != pstruAsnLane->maneuvers->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:size = %d",
                     pstruAsnLane->maneuvers->size);
            return false;
        }
        n32Ret = WJV3_BITSTRING_DeDec(pstruAsnLane->maneuvers, pstruWjLane->u.u8maneuvers);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_BITSTRING_DeDec is err");
            return false;
        }
        pstruWjLane->u8maneuvers_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjLane->u8maneuvers_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnLane->connectsTo)
    {
        n32Ret = WJV3_ConnectsToList_DfDec(pstruAsnLane->connectsTo, &(pstruWjLane->struconnectsTo));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_ConnectsToList_DfDec is err");
            return false;
        }
        pstruWjLane->u8connectsTo_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjLane->u8connectsTo_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnLane->speedLimits)
    {
        n32Ret = WJV3_SpeedLimitList_DfDec(pstruAsnLane->speedLimits, &(pstruWjLane->struspeedLimits));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_SpeedLimitList_DfDec is err");
            return false;
        }
        pstruWjLane->u8speedLimits_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjLane->u8speedLimits_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnLane->points)
    {
        n32Ret = WJV3_PointList_DfDec(pstruAsnLane->points, &(pstruWjLane->strupoints));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PointList_DfDec is err");
            return false;
        }
        pstruWjLane->u8points_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjLane->u8points_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_LaneList_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 LaneList 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_LaneList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_LaneList *pstruWjLaneList = (WJV3_STRU_LaneList *)pvoidWjDf;
    LaneList_t *pstruAsnLaneList = (LaneList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    Lane_t *pstruLant_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_LANE_NUM < pstruWjLaneList->u8LaneNum)
        || (1 > pstruWjLaneList->u8LaneNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8LaneNum = %d",
                 pstruWjLaneList->u8LaneNum);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruWjLaneList->u8LaneNum; u32i++)
    {
        pstruLant_node = CALLOC(1, sizeof(Lane_t));
        if (NULL == pstruLant_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_Lane_DfEnc(pstruLant_node, &(pstruWjLaneList->struLanelist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_Lane_DfEnc is err");
            FREEMEM(pstruLant_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnLaneList->list), pstruLant_node);
    }
    return true;
}
/**
 * @brief    WJV3_LaneList_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 LaneList 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_LaneList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_LaneList *pstruWjLaneList = (WJV3_STRU_LaneList *)pvoidWjDf;
    LaneList_t *pstruAsnLaneList = (LaneList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_LANE_NUM < pstruAsnLaneList->list.count)
        || (1 > pstruAsnLaneList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnLaneList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnLaneList->list.count; u32i++)
    {
        n32Ret = WJV3_Lane_DfDec(pstruAsnLaneList->list.array[u32i],
                               &(pstruWjLaneList->struLanelist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_Lane_DfDec is err");
            return false;
        }
    }
    pstruWjLaneList->u8LaneNum = (uint8_t)u32i;
    return true;
}
/**
 * @brief    WJV3_Link_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 Link 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Link_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Link *pstruWjLink = (WJV3_STRU_Link *)pvoidWjDf;
    Link_t *pstruAsnLink = (Link_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (0 != pstruWjLink->u8nameNum)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_IA5_NAME_LEN < pstruWjLink->u8nameNum)
            || (0 > pstruWjLink->u8nameNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "out of rangth:u8nameNum = %d",
                    pstruWjLink->u8nameNum);
            return false;
        }
        #endif
        n32Ret = WJV3_Check_IA5String(pstruWjLink->u8name, pstruWjLink->u8nameNum);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "WJV3_Check_IA5String is err");
            return false;
        }
        pstruAsnLink->name = CALLOC(1, sizeof(DescriptiveName_t));
        if (NULL == pstruAsnLink->name)
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "calloc is err");
            return false;
        }
        pstruAsnLink->name->size = pstruWjLink->u8nameNum;
        pstruAsnLink->name->buf = CALLOC(1, pstruAsnLink->name->size);
        if (NULL == pstruAsnLink->name->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "calloc is err");
            return false;
        }
        memcpy(pstruAsnLink->name->buf, pstruWjLink->u8name, pstruAsnLink->name->size);
    }
    else
    {
        pstruAsnLink->name = NULL;
    }
    n32Ret = WJV3_NodeReferenceID_DfEnc(&(pstruAsnLink->upstreamNodeId), &(pstruWjLink->struupstreamNodeId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeReferenceID_DfEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjLink->u8speedLimits_Present)
    {
        pstruAsnLink->speedLimits = CALLOC(1, sizeof(*(pstruAsnLink->speedLimits)));
        if (NULL == pstruAsnLink->speedLimits)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_SpeedLimitList_DfEnc(pstruAsnLink->speedLimits, &(pstruWjLink->struspeedLimits));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_SpeedLimitList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLink->speedLimits = NULL;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_LANEWIDTH_SIZE < pstruWjLink->n32laneWidth)
        || (WJV3_MIN_LANEWIDTH_SIZE > pstruWjLink->n32laneWidth))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32laneWidth = %d",
                 pstruWjLink->n32laneWidth);
        return false;
    }
    #endif
    pstruAsnLink->laneWidth = pstruWjLink->n32laneWidth;
    if (WJV3_PRESENT == pstruWjLink->u8points_Present)
    {
        pstruAsnLink->points = CALLOC(1, sizeof(*(pstruAsnLink->points)));
        if (NULL == pstruAsnLink->points)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_PointList_DfEnc(pstruAsnLink->points, &(pstruWjLink->strupoints));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PointList_DfEnc is err");
            return false;
        }
    }
    else
    {
         pstruAsnLink->points = NULL;
    }
    if (WJV3_PRESENT == pstruWjLink->u8movements_Present)
    {
        pstruAsnLink->movements = CALLOC(1, sizeof(*(pstruAsnLink->movements)));
        if (NULL == pstruAsnLink->movements)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_MovementList_DfEnc(pstruAsnLink->movements, &(pstruWjLink->strumovements));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_MovementList_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnLink->movements = NULL;
    }
    n32Ret = WJV3_LaneList_DfEnc(&(pstruAsnLink->lanes), &(pstruWjLink->strulanes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_LaneList_DfEnc is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_Link_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 Link 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Link_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Link *pstruWjLink = (WJV3_STRU_Link *)pvoidWjDf;
    Link_t *pstruAsnLink = (Link_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnLink->name)
    {
        if ((WJV3_MAX_IA5_NAME_LEN < pstruAsnLink->name->size)
            || (1 > pstruAsnLink->name->size)
            || (NULL == pstruAsnLink->name->buf))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:size = %d",
                     pstruAsnLink->name->size);
            return false;
        }
        memcpy(pstruWjLink->u8name, pstruAsnLink->name->buf, pstruAsnLink->name->size);
        pstruWjLink->u8nameNum = pstruAsnLink->name->size;
    }
    else
    {
        pstruWjLink->u8nameNum = 0;
    }
    n32Ret = WJV3_NodeReferenceID_DfDec(&(pstruAsnLink->upstreamNodeId), &(pstruWjLink->struupstreamNodeId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeReferenceID_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnLink->speedLimits)
    {
        n32Ret = WJV3_SpeedLimitList_DfDec(pstruAsnLink->speedLimits, &(pstruWjLink->struspeedLimits));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_SpeedLimitList_DfDec is err");
            return false;
        }
        pstruWjLink->u8speedLimits_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjLink->u8speedLimits_Present = WJV3_ABSENT;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_LANEWIDTH_SIZE < pstruAsnLink->laneWidth)
        || (WJV3_MIN_LANEWIDTH_SIZE > pstruAsnLink->laneWidth))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:laneWidth = %d",
                 pstruAsnLink->laneWidth);
        return false;
    }
    #endif
    pstruWjLink->n32laneWidth = pstruAsnLink->laneWidth;
    if (NULL != pstruAsnLink->points)
    {
        n32Ret = WJV3_PointList_DfDec(pstruAsnLink->points, &(pstruWjLink->strupoints));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PointList_DfDec is err");
            return false;
        }
        pstruWjLink->u8points_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjLink->u8points_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnLink->movements)
    {
        n32Ret = WJV3_MovementList_DfDec(pstruAsnLink->movements, &(pstruWjLink->strumovements));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_MovementList_DfDec is err");
            return false;
        }
        pstruWjLink->u8movements_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjLink->u8movements_Present = WJV3_ABSENT;
    }
    n32Ret = WJV3_LaneList_DfDec(&(pstruAsnLink->lanes), &(pstruWjLink->strulanes));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_LaneList_DfDec is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_LinkList_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 LinkList 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_LinkList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_LinkList *pstruWjLinkList = (WJV3_STRU_LinkList *)pvoidWjDf;
    LinkList_t *pstruAsnLinkList = (LinkList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    Link_t *pstruLink_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_LINK_NUM < pstruWjLinkList->u8LinkNum)
        || (1 > pstruWjLinkList->u8LinkNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8LinkNum = %d",
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
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_Link_DfEnc(pstruLink_node, &(pstruWjLinkList->struLinklist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_Link_DfEnc is err");
            FREEMEM(pstruLink_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnLinkList->list), pstruLink_node);
    }
    return true;
}
/**
 * @brief    WJV3_LinkList_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 LinkList 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_LinkList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_LinkList *pstruWjLinkList = (WJV3_STRU_LinkList *)pvoidWjDf;
    LinkList_t *pstruAsnLinkList = (LinkList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_LINK_NUM < pstruAsnLinkList->list.count)
        || (1 > pstruAsnLinkList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnLinkList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnLinkList->list.count; u32i++)
    {
        n32Ret = WJV3_Link_DfDec(pstruAsnLinkList->list.array[u32i],
                               &(pstruWjLinkList->struLinklist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_Link_DfDec is err");
            return false;
        }
    }
    pstruWjLinkList->u8LinkNum = (uint8_t)u32i;
    return true;
}
/**
 * @brief    WJV3_Node_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 Node 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Node_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Node *pstruWjNode = (WJV3_STRU_Node *)pvoidWjDf;
    Node_t *pstruAsnNode = (Node_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (0 != pstruWjNode->u8nameNum)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_IA5_NAME_LEN < pstruWjNode->u8nameNum)
            || (0 > pstruWjNode->u8nameNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8nameNum = %d",
                 pstruWjNode->u8nameNum);
            return false;
        }
        #endif
        n32Ret = WJV3_Check_IA5String(pstruWjNode->u8name, pstruWjNode->u8nameNum);
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_Check_IA5String is err");
            return false;
        }
        pstruAsnNode->name = CALLOC(1, sizeof(DescriptiveName_t));
        if (NULL == pstruAsnNode->name)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnNode->name->buf = CALLOC(1, pstruWjNode->u8nameNum);
        if (NULL == pstruAsnNode->name->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        memcpy(pstruAsnNode->name->buf, pstruWjNode->u8name, pstruWjNode->u8nameNum);
        pstruAsnNode->name->size = pstruWjNode->u8nameNum;
    }
    else
    {
        pstruAsnNode->name = NULL;
    }
    n32Ret = WJV3_NodeReferenceID_DfEnc(&(pstruAsnNode->id), &(pstruWjNode->struid));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeReferenceID_DfEnc is err");
        return false;
    }
    n32Ret = WJV3_Position3D_DfEnc(&(pstruAsnNode->refPos), &(pstruWjNode->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_Position3D_DfEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjNode->u8inLinks_Present)
    {
        pstruAsnNode->inLinks = CALLOC(1, sizeof(*(pstruAsnNode->inLinks)));
        if (NULL == pstruAsnNode->inLinks)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_LinkList_DfEnc(pstruAsnNode->inLinks, &(pstruWjNode->inLinks));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_NodeReferenceID_DfEnc is err");
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
 * @brief    WJV3_Node_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 Node 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Node_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Node *pstruWjNode = (WJV3_STRU_Node *)pvoidWjDf;
    Node_t *pstruAsnNode = (Node_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    if (NULL != pstruAsnNode->name)
    {
        if ((WJV3_MAX_IA5_NAME_LEN < pstruAsnNode->name->size)
            || (0 >= pstruAsnNode->name->size)
            || (NULL == pstruAsnNode->name->buf))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:size = %d",
                     pstruAsnNode->name->size);
            return false;
        }
        memcpy(pstruWjNode->u8name, pstruAsnNode->name->buf, pstruAsnNode->name->size);
        pstruWjNode->u8nameNum = pstruAsnNode->name->size;
    }
    else
    {
        pstruWjNode->u8nameNum = 0;
    }
    n32Ret = WJV3_NodeReferenceID_DfDec(&(pstruAsnNode->id), &(pstruWjNode->struid));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeReferenceID_DfDec is err");
        return false;
    }
    n32Ret = WJV3_Position3D_DfDec(&(pstruAsnNode->refPos), &(pstruWjNode->strurefPos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_Position3D_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnNode->inLinks)
    {
        n32Ret = WJV3_LinkList_DfDec(pstruAsnNode->inLinks, &(pstruWjNode->inLinks));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_LinkList_DfDec is err");
            return false;
        }
        pstruWjNode->u8inLinks_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjNode->u8inLinks_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_Node_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 Node 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_NodeList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_NodeList *pstruWjNodeList = (WJV3_STRU_NodeList *)pvoidWjDf;
    NodeList_t *pstruAsnNodeList = (NodeList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    Node_t *pstruNodeList_Node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_NODE_NUM < pstruWjNodeList->u8NodeNum)
        || (1 > pstruWjNodeList->u8NodeNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8NodeNum = %d",
                 pstruWjNodeList->u8NodeNum);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruWjNodeList->u8NodeNum; u32i++)
    {
        pstruNodeList_Node = CALLOC(1, sizeof(Node_t));
        if ( NULL == pstruNodeList_Node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_Node_DfEnc(pstruNodeList_Node, &(pstruWjNodeList->struNodelist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_Node_DfEnc is err");
            FREEMEM(pstruNodeList_Node);
            return false;
        }
        asn_sequence_add(&(pstruAsnNodeList->list), pstruNodeList_Node);
    }
    return true;
}
/**
 * @brief    WJV3_Node_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 Node 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_NodeList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_NodeList *pstruWjNodeList = (WJV3_STRU_NodeList *)pvoidWjDf;
    NodeList_t *pstruAsnNodeList = (NodeList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_NODE_NUM < pstruAsnNodeList->list.count)
        || (1 > pstruAsnNodeList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnNodeList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnNodeList->list.count; u32i++)
    {
        n32Ret = WJV3_Node_DfDec(pstruAsnNodeList->list.array[u32i],
                               &(pstruWjNodeList->struNodelist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_Node_DfDec is err");
            return false;
        }
    }
    pstruWjNodeList->u8NodeNum = (uint8_t)u32i;
    return true;
}
/**
 * @brief    WJV3_ParticipantData_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 ParticipantData 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_ParticipantData_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_ParticipantData *pstruWjParticipantData = (WJV3_STRU_ParticipantData *)pvoidWjDf;
    ParticipantData_t *pstruAsnParticipantData = (ParticipantData_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_ParticipantType_rsu < pstruWjParticipantData->enumptcType)
        || (WJV3_ParticipantType_unknown > pstruWjParticipantData->enumptcType))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:enumptcType = %d",
                 pstruWjParticipantData->enumptcType);
        return false;
    }
    #endif
    pstruAsnParticipantData->ptcType = pstruWjParticipantData->enumptcType;
    #ifdef _CHECK_
    if ((WJV3_MAX_PTCID_SIZE< pstruWjParticipantData->n32ptcId)
        || (WJV3_MIN_PTCID_SIZE> pstruWjParticipantData->n32ptcId))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32ptcId = %d",
                 pstruWjParticipantData->n32ptcId);
        return false;
    }
    #endif
    pstruAsnParticipantData->ptcId = pstruWjParticipantData->n32ptcId;
    #ifdef _CHECK_
    if ((WJV3_SourceType_microwmixRadar < pstruWjParticipantData->enumsource)
        || (WJV3_SourceType_unknown > pstruWjParticipantData->enumsource))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:enumsource = %d",
                 pstruWjParticipantData->enumsource);
        return false;
    }
    #endif
    pstruAsnParticipantData->source = pstruWjParticipantData->enumsource;
    if (WJV3_PRESENT == pstruWjParticipantData->u8Id_Present)
    {
        pstruAsnParticipantData->id = CALLOC(1, sizeof(OCTET_STRING_t));
        if (NULL == pstruAsnParticipantData->id)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnParticipantData->id->size = WJV3_MAX_BYTE_ID_LEN;
        pstruAsnParticipantData->id->buf = CALLOC(1, pstruAsnParticipantData->id->size);
        if (NULL == pstruAsnParticipantData->id->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        memcpy(pstruAsnParticipantData->id->buf, pstruWjParticipantData->u8Id, pstruAsnParticipantData->id->size);
    }
    else
    {
        pstruAsnParticipantData->id = NULL;
    }
    if (WJV3_PRESENT == pstruWjParticipantData->u8plateNo_Present)
    {
        pstruAsnParticipantData->plateNo = CALLOC(1, sizeof(OCTET_STRING_t));
        if (NULL == pstruAsnParticipantData->plateNo)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        pstruAsnParticipantData->plateNo->size = WJV3_MAX_BYTE_PLATNO_LEN;
        pstruAsnParticipantData->plateNo->buf = CALLOC(1, pstruAsnParticipantData->plateNo->size);
        if (NULL == pstruAsnParticipantData->plateNo->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        memcpy(pstruAsnParticipantData->plateNo->buf, pstruWjParticipantData->u8plateNo, pstruAsnParticipantData->plateNo->size);
    }
    else
    {
        pstruAsnParticipantData->plateNo = NULL;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_DSECOND_SIZE < pstruWjParticipantData->n32secMark)
        || (WJV3_MIN_DSECOND_SIZE > pstruWjParticipantData->n32secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32secMark = %d",
                 pstruWjParticipantData->n32secMark);
        return false;
    }
    #endif
    pstruAsnParticipantData->secMark = pstruWjParticipantData->n32secMark;
    n32Ret = WJV3_PositionOffsetLLV_DfEnc(&(pstruAsnParticipantData->pos), &(pstruWjParticipantData->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionOffsetLLV_DfEnc is err");
        return false;
    }
    n32Ret = WJV3_PositionConfidenceSet_DfEnc(&(pstruAsnParticipantData->accuracy), &(pstruWjParticipantData->struaccuracy));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionConfidenceSet_DfEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjParticipantData->u8transmission_Present)
    {
        pstruAsnParticipantData->transmission = CALLOC(1, sizeof(TransmissionState_t));
        if (NULL == pstruAsnParticipantData->transmission)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_TransmissionState_DeEnc(pstruAsnParticipantData->transmission, &(pstruWjParticipantData->enumtransmission));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_TransmissionState_DeEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnParticipantData->transmission = NULL;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_SPEED_SIZE < pstruWjParticipantData->n32speed)
        || (WJV3_MIN_SPEED_SIZE > pstruWjParticipantData->n32speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32speed = %d",
                 pstruWjParticipantData->n32speed);
        return false;
    }
    #endif
    pstruAsnParticipantData->speed = pstruWjParticipantData->n32speed;
    #ifdef _CHECK_
    if ((WJV3_MAX_HEADING_SIZE < pstruWjParticipantData->n32heading)
        || (WJV3_MIN_HEADING_SIZE > pstruWjParticipantData->n32heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32heading = %d",
                 pstruWjParticipantData->n32heading);
        return false;
    }
    #endif
    pstruAsnParticipantData->heading = pstruWjParticipantData->n32heading;
    if (WJV3_PRESENT == pstruWjParticipantData->u8angle_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_STEETINGWHEELANGLE_SIZE < pstruWjParticipantData->n32angle)
            || (WJV3_MIN_STEETINGWHEELANGLE_SIZE > pstruWjParticipantData->n32angle))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32angle = %d",
                     pstruWjParticipantData->n32angle);
            return false;
        }
        #endif
        pstruAsnParticipantData->angle = CALLOC(1, sizeof(SteeringWheelAngle_t));
        if (NULL == pstruAsnParticipantData->angle)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnParticipantData->angle) = pstruWjParticipantData->n32angle;
    }
    else
    {
        pstruAsnParticipantData->angle = NULL;
    }
    if (WJV3_PRESENT == pstruWjParticipantData->u8motionCfd_Present)
    {
        pstruAsnParticipantData->motionCfd = CALLOC(1, sizeof(MotionConfidenceSet_t));
        if (NULL == pstruAsnParticipantData->motionCfd)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_MotionConfidenceSet_DfEnc(pstruAsnParticipantData->motionCfd, &(pstruWjParticipantData->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_MotionConfidenceSet_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnParticipantData->motionCfd = NULL;
    }
    if (WJV3_PRESENT == pstruWjParticipantData->u8motionCfd_Present)
    {
        pstruAsnParticipantData->accelSet = CALLOC(1, sizeof(struct AccelerationSet4Way));
        if (NULL == pstruAsnParticipantData->accelSet)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_AccelerationSet4Way_DfEnc(pstruAsnParticipantData->accelSet, &(pstruWjParticipantData->struaccelSet));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_AccelerationSet4Way_DfEnc is err");
            return false;
        }
    }
    else
    {
        pstruAsnParticipantData->accelSet = NULL;
    }
    n32Ret = WJV3_VehicleSize_DfEnc(&(pstruAsnParticipantData->size), &(pstruWjParticipantData->strusize));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_VehicleSize_DfEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjParticipantData->u8vehicleClass_Present)
    {
        pstruAsnParticipantData->vehicleClass = CALLOC(1, sizeof(struct AccelerationSet4Way));
        if (NULL == pstruAsnParticipantData->vehicleClass)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_VehicleClassification_DfEnc(pstruAsnParticipantData->vehicleClass, &(pstruWjParticipantData->struvehicleClass));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_VehicleClassification_DfEnc is err");
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
 * @brief    WJV3_ParticipantData_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 ParticipantData 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_ParticipantData_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_ParticipantData *pstruWjParticipantData = (WJV3_STRU_ParticipantData *)pvoidWjDf;
    ParticipantData_t *pstruAsnParticipantData = (ParticipantData_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_ParticipantType_rsu < pstruAsnParticipantData->ptcType)
        || (WJV3_ParticipantType_unknown > pstruAsnParticipantData->ptcType))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:ptcType = %d",
                 pstruAsnParticipantData->ptcType);
        return false;
    }
    #endif
    pstruWjParticipantData->enumptcType = pstruAsnParticipantData->ptcType;
    #ifdef _CHECK_
    if ((WJV3_MAX_PTCID_SIZE < pstruAsnParticipantData->ptcId)
        || (WJV3_MIN_PTCID_SIZE > pstruAsnParticipantData->ptcId))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:ptcId = %d",
                 pstruAsnParticipantData->ptcId);
        return false;
    }
    #endif
    pstruWjParticipantData->n32ptcId = pstruAsnParticipantData->ptcId;
    #ifdef _CHECK_
    if ((WJV3_SourceType_microwmixRadar < pstruAsnParticipantData->source)
        || (WJV3_SourceType_unknown > pstruAsnParticipantData->source))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:source = %d",
                 pstruAsnParticipantData->source);
        return false;
    }
    #endif
    pstruWjParticipantData->enumsource = pstruAsnParticipantData->source;
    if (NULL != pstruAsnParticipantData->id)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_BYTE_ID_LEN != pstruAsnParticipantData->id->size)
            || (NULL == pstruAsnParticipantData->id->buf))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:u8IdLen = %d",
                     pstruAsnParticipantData->id->size);
            return false;
        }
        #endif
        memcpy(pstruWjParticipantData->u8Id, pstruAsnParticipantData->id->buf, pstruAsnParticipantData->id->size);
        pstruWjParticipantData->u8Id_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8Id_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnParticipantData->plateNo)
    {
        if ((NULL == pstruAsnParticipantData->plateNo->buf)
         || (WJV3_MAX_BYTE_PLATNO_LEN != pstruAsnParticipantData->plateNo->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:size = %d",
                     pstruAsnParticipantData->plateNo->size);
            return false;
        }
        memcpy((uint8_t *)pstruWjParticipantData->u8plateNo, (uint8_t *)pstruAsnParticipantData->plateNo->buf, pstruAsnParticipantData->plateNo->size);
        pstruWjParticipantData->u8plateNo_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8plateNo_Present = WJV3_ABSENT;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_DSECOND_SIZE < pstruAsnParticipantData->secMark)
        || (WJV3_MIN_DSECOND_SIZE > pstruAsnParticipantData->secMark))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:secMark = %d",
                 pstruAsnParticipantData->secMark);
        return false;
    }
    #endif
    pstruWjParticipantData->n32secMark = pstruAsnParticipantData->secMark;
    n32Ret = WJV3_PositionOffsetLLV_DfDec(&(pstruAsnParticipantData->pos), &(pstruWjParticipantData->strupos));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionOffsetLLV_DfDec is err");
        return false;
    }
    n32Ret = WJV3_PositionConfidenceSet_DfDec(&(pstruAsnParticipantData->accuracy), &(pstruWjParticipantData->struaccuracy));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PositionConfidenceSet_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnParticipantData->transmission)
    {
        n32Ret = WJV3_TransmissionState_DeDec(pstruAsnParticipantData->transmission, &(pstruWjParticipantData->enumtransmission));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_TransmissionState_DeDec is err");
            return false;
        }
        pstruWjParticipantData->u8transmission_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8transmission_Present = WJV3_ABSENT;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_SPEED_SIZE < pstruAsnParticipantData->speed)
        || (WJV3_MIN_SPEED_SIZE > pstruAsnParticipantData->speed))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:speed = %d",
                 pstruAsnParticipantData->speed);
        return false;
    }
    #endif
    pstruWjParticipantData->n32speed = pstruAsnParticipantData->speed;
    #ifdef _CHECK_
    if ((WJV3_MAX_HEADING_SIZE < pstruAsnParticipantData->heading)
        || (WJV3_MIN_HEADING_SIZE > pstruAsnParticipantData->heading))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:heading = %d",
                 pstruAsnParticipantData->heading);
        return false;
    }
    #endif
    pstruWjParticipantData->n32heading = pstruAsnParticipantData->heading;
    if (NULL != pstruAsnParticipantData->angle)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_STEETINGWHEELANGLE_SIZE < *(pstruAsnParticipantData->angle))
            || (WJV3_MIN_STEETINGWHEELANGLE_SIZE > *(pstruAsnParticipantData->angle)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:angle = %d",
                     *(pstruAsnParticipantData->angle));
            return false;
        }
        #endif
        pstruWjParticipantData->n32angle = *(pstruAsnParticipantData->angle);
        pstruWjParticipantData->u8angle_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8angle_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnParticipantData->motionCfd)
    {
        n32Ret = WJV3_MotionConfidenceSet_DfDec(pstruAsnParticipantData->motionCfd, &(pstruWjParticipantData->strumotionCfd));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_MotionConfidenceSet_DfDec is err");
            return false;
        }
        pstruWjParticipantData->u8motionCfd_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8motionCfd_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnParticipantData->accelSet)
    {
        n32Ret = WJV3_AccelerationSet4Way_DfDec(pstruAsnParticipantData->accelSet, &(pstruWjParticipantData->struaccelSet));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_AccelerationSet4Way_DfDec is err");
            return false;
        }
        pstruWjParticipantData->u8accelSet_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8accelSet_Present = WJV3_ABSENT;
    }
    n32Ret = WJV3_VehicleSize_DfDec(&(pstruAsnParticipantData->size), &(pstruWjParticipantData->strusize));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_VehicleSize_DfDec is err");
        return false;
    }
    if (NULL != pstruAsnParticipantData->vehicleClass)
    {
        n32Ret = WJV3_VehicleClassification_DfDec(pstruAsnParticipantData->vehicleClass, &(pstruWjParticipantData->struvehicleClass));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_VehicleClassification_DfDec is err");
            return false;
        }
        pstruWjParticipantData->u8vehicleClass_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjParticipantData->u8vehicleClass_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_ParticipantList_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 ParticipantList 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_ParticipantList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_ParticipantList *pstruWjParticipantList = (WJV3_STRU_ParticipantList *)pvoidWjDf;
    ParticipantList_t *pstruAsnParticipantList = (ParticipantList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    ParticipantData_t *pstruParticipantData_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_PARTICIPANT_NUM < pstruWjParticipantList->u8ParticipantNum)
        || (1 > pstruWjParticipantList->u8ParticipantNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8ParticipantNum = %d",
                 pstruWjParticipantList->u8ParticipantNum);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruWjParticipantList->u8ParticipantNum; u32i++)
    {
        pstruParticipantData_node = CALLOC(1, sizeof(ParticipantData_t));
        if (NULL == pstruParticipantData_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_ParticipantData_DfEnc(pstruParticipantData_node, &(pstruWjParticipantList->struParticipantDatalist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_ParticipantData_DfEnc is err");
            FREEMEM(pstruParticipantData_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnParticipantList->list), pstruParticipantData_node);
    }
    return true;
}
/**
 * @brief    WJV3_ParticipantList_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 ParticipantList 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_ParticipantList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_ParticipantList *pstruWjParticipantList = (WJV3_STRU_ParticipantList *)pvoidWjDf;
    ParticipantList_t *pstruAsnParticipantList = (ParticipantList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_PARTICIPANT_NUM < pstruAsnParticipantList->list.count)
        || (1 > pstruAsnParticipantList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnParticipantList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnParticipantList->list.count; u32i++)
    {
        n32Ret = WJV3_ParticipantData_DfDec(pstruAsnParticipantList->list.array[u32i],
                                          &(pstruWjParticipantList->struParticipantDatalist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_ParticipantData_DfDec is err");
            return false;
        }
    }
    pstruWjParticipantList->u8ParticipantNum = (uint8_t)u32i;
    return true;
}
/**
 * @brief    WJV3_TimeChangeDetails_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 TimeChangeDetails 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_TimeChangeDetails_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_TimeChangeDetails *pstruWjChangeDetails = (WJV3_STRU_TimeChangeDetails *)pvoidWjDf;
    TimeChangeDetails_t *pstruAsnChangeDetails = (TimeChangeDetails_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_TIMEMARK_SIZE < pstruWjChangeDetails->n32startTime)
        || (WJV3_MIN_TIMEMARK_SIZE > pstruWjChangeDetails->n32startTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32startTime = %d",
                 pstruWjChangeDetails->n32startTime);
        return false;
    }
    #endif
    pstruAsnChangeDetails->startTime = pstruWjChangeDetails->n32startTime;
    if (WJV3_PRESENT == pstruWjChangeDetails->u8minEndTime_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_TIMEMARK_SIZE < pstruWjChangeDetails->n32minEndTime)
            || (WJV3_MIN_TIMEMARK_SIZE > pstruWjChangeDetails->n32minEndTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32minEndTime = %d",
                     pstruWjChangeDetails->n32minEndTime);
            return false;
        }
        #endif
        pstruAsnChangeDetails->minEndTime = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnChangeDetails->minEndTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnChangeDetails->minEndTime) = pstruWjChangeDetails->n32minEndTime;
    }
    else
    {
        pstruAsnChangeDetails->minEndTime = NULL;
    }
    if (WJV3_PRESENT == pstruWjChangeDetails->u8maxEndTime_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_TIMEMARK_SIZE < pstruWjChangeDetails->n32maxEndTime)
            || (WJV3_MIN_TIMEMARK_SIZE > pstruWjChangeDetails->n32maxEndTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32maxEndTime = %d",
                     pstruWjChangeDetails->n32maxEndTime);
            return false;
        }
        #endif
        pstruAsnChangeDetails->maxEndTime = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnChangeDetails->maxEndTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnChangeDetails->maxEndTime) = pstruWjChangeDetails->n32maxEndTime;
    }
    else
    {
        pstruAsnChangeDetails->maxEndTime = NULL;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_TIMEMARK_SIZE < pstruWjChangeDetails->n32likelyEndTime)
        || (WJV3_MIN_TIMEMARK_SIZE > pstruWjChangeDetails->n32likelyEndTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32likelyEndTime = %d",
                 pstruWjChangeDetails->n32likelyEndTime);
        return false;
    }
    #endif
    pstruAsnChangeDetails->likelyEndTime = pstruWjChangeDetails->n32likelyEndTime;
    if (WJV3_PRESENT == pstruWjChangeDetails->u8timeConfidence_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_CONFIDENCE_SIZE < pstruWjChangeDetails->n32timeConfidence)
            || (WJV3_MIN_CONFIDENCE_SIZE > pstruWjChangeDetails->n32timeConfidence))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32timeConfidence = %d",
                     pstruWjChangeDetails->n32timeConfidence);
            return false;
        }
        #endif
        pstruAsnChangeDetails->timeConfidence = CALLOC(1, sizeof(Confidence_t));
        if (NULL == pstruAsnChangeDetails->timeConfidence)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnChangeDetails->timeConfidence) = pstruWjChangeDetails->n32timeConfidence;
    }
    else
    {
        pstruAsnChangeDetails->timeConfidence = NULL;
    }
    if (WJV3_PRESENT == pstruWjChangeDetails->u8nextStartTime_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_TIMEMARK_SIZE < pstruWjChangeDetails->n32nextStartTime)
            || (WJV3_MIN_TIMEMARK_SIZE > pstruWjChangeDetails->n32nextStartTime))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32nextStartTime = %d",
                     pstruWjChangeDetails->n32nextStartTime);
            return false;
        }
        #endif
        pstruAsnChangeDetails->nextStartTime = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnChangeDetails->nextStartTime)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnChangeDetails->nextStartTime) = pstruWjChangeDetails->n32nextStartTime;
    }
    else
    {
        pstruAsnChangeDetails->nextStartTime = NULL;
    }
    if (WJV3_PRESENT == pstruWjChangeDetails->u8nextDuration_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_TIMEMARK_SIZE < pstruWjChangeDetails->n32nextDuration)
            || (WJV3_MIN_TIMEMARK_SIZE > pstruWjChangeDetails->n32nextDuration))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32nextDuration = %d",
                     pstruWjChangeDetails->n32nextDuration);
            return false;
        }
        #endif
        pstruAsnChangeDetails->nextDuration = CALLOC(1, sizeof(TimeMark_t));
        if (NULL == pstruAsnChangeDetails->nextDuration)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnChangeDetails->nextDuration) = pstruWjChangeDetails->n32nextDuration;
    }
    return true;
}
/**
 * @brief    WJV3_TimeChangeDetails_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 TimeChangeDetails 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_TimeChangeDetails_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_TimeChangeDetails *pstruWjChangeDetails = (WJV3_STRU_TimeChangeDetails *)pvoidWjDf;
    TimeChangeDetails_t *pstruAsnChangeDetails = (TimeChangeDetails_t *)pvoidAsnDf;
    #ifdef _CHECK_
    if ((WJV3_MAX_TIMEMARK_SIZE < pstruAsnChangeDetails->startTime)
        || (WJV3_MIN_TIMEMARK_SIZE > pstruAsnChangeDetails->startTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:startTime = %d",
                 pstruAsnChangeDetails->startTime);
        return false;
    }
    #endif
    pstruWjChangeDetails->n32startTime = pstruAsnChangeDetails->startTime;
    if (NULL != pstruAsnChangeDetails->minEndTime)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_TIMEMARK_SIZE < *(pstruAsnChangeDetails->minEndTime))
            || (WJV3_MIN_TIMEMARK_SIZE > *(pstruAsnChangeDetails->minEndTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:minEndTime = %d",
                     *(pstruAsnChangeDetails->minEndTime));
            return false;
        }
        #endif
        pstruWjChangeDetails->n32minEndTime = *(pstruAsnChangeDetails->minEndTime);
        pstruWjChangeDetails->u8minEndTime_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjChangeDetails->u8minEndTime_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnChangeDetails->maxEndTime)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_TIMEMARK_SIZE < *(pstruAsnChangeDetails->maxEndTime))
            || (WJV3_MIN_TIMEMARK_SIZE > *(pstruAsnChangeDetails->maxEndTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:maxEndTime = %d",
                     *(pstruAsnChangeDetails->maxEndTime));
            return false;
        }
        #endif
        pstruWjChangeDetails->n32maxEndTime = *(pstruAsnChangeDetails->maxEndTime);
        pstruWjChangeDetails->u8maxEndTime_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjChangeDetails->u8maxEndTime_Present = WJV3_ABSENT;
    }
    #ifdef _CHECK_
    if ((WJV3_MAX_TIMEMARK_SIZE < pstruAsnChangeDetails->likelyEndTime)
        || (WJV3_MIN_TIMEMARK_SIZE > pstruAsnChangeDetails->likelyEndTime))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:likelyEndTime = %d",
                 pstruAsnChangeDetails->likelyEndTime);
        return false;
    }
    #endif
    pstruWjChangeDetails->n32likelyEndTime = pstruAsnChangeDetails->likelyEndTime;
    if (NULL != pstruAsnChangeDetails->timeConfidence)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_CONFIDENCE_SIZE < *(pstruAsnChangeDetails->timeConfidence))
            || (WJV3_MIN_CONFIDENCE_SIZE > *(pstruAsnChangeDetails->timeConfidence)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:timeConfidence = %d",
                     *(pstruAsnChangeDetails->timeConfidence));
            return false;
        }
        #endif
        pstruWjChangeDetails->n32timeConfidence = *(pstruAsnChangeDetails->timeConfidence);
        pstruWjChangeDetails->u8timeConfidence_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjChangeDetails->u8timeConfidence_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnChangeDetails->nextStartTime)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_TIMEMARK_SIZE < *(pstruAsnChangeDetails->nextStartTime))
            || (WJV3_MIN_TIMEMARK_SIZE > *(pstruAsnChangeDetails->nextStartTime)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:nextStartTime = %d",
                     *(pstruAsnChangeDetails->nextStartTime));
            return false;
        }
        #endif
        pstruWjChangeDetails->n32nextStartTime = *(pstruAsnChangeDetails->nextStartTime);
        pstruWjChangeDetails->u8nextStartTime_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjChangeDetails->u8nextStartTime_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnChangeDetails->nextDuration)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_TIMEMARK_SIZE < *(pstruAsnChangeDetails->nextDuration))
            || (WJV3_MIN_TIMEMARK_SIZE > *(pstruAsnChangeDetails->nextDuration)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:nextDuration = %d",
                     *(pstruAsnChangeDetails->nextDuration));
            return false;
        }
        #endif
        pstruWjChangeDetails->n32nextDuration = *(pstruAsnChangeDetails->nextDuration);
        pstruWjChangeDetails->u8nextDuration_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjChangeDetails->u8nextDuration_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_PhaseState_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PhaseState 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PhaseState_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PhaseState *pstruWjPhaseState = (WJV3_STRU_PhaseState *)pvoidWjDf;
    PhaseState_t *pstruAsnPhaseState = (PhaseState_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_LightState_DeEnc(&(pstruAsnPhaseState->light), &(pstruWjPhaseState->enumlight));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_LightState_DeEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjPhaseState->u8timing_Present)
    {
        pstruAsnPhaseState->timing = CALLOC(1, sizeof(struct TimeChangeDetails));
        if (NULL == pstruAsnPhaseState->timing)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        n32Ret = WJV3_TimeChangeDetails_DfEnc(pstruAsnPhaseState->timing, &(pstruWjPhaseState->strutiming));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_TimeChangeDetails_DfEnc is err");
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
 * @brief    WJV3_PhaseState_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PhaseState 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PhaseState_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PhaseState *pstruWjPhaseState = (WJV3_STRU_PhaseState *)pvoidWjDf;
    PhaseState_t *pstruAsnPhaseState = (PhaseState_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_LightState_DeDec(&(pstruAsnPhaseState->light), &(pstruWjPhaseState->enumlight));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_LightState_DeDec is err");
        return false;
    }
    if (NULL != pstruAsnPhaseState->timing)
    {
        n32Ret = WJV3_TimeChangeDetails_DfDec(pstruAsnPhaseState->timing, &(pstruWjPhaseState->strutiming));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_TimeChangeDetails_DfDec is err");
            return false;
        }
        pstruWjPhaseState->u8timing_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjPhaseState->u8timing_Present = WJV3_ABSENT;
    }
    return true;
}
/**
 * @brief    WJV3_PhaseStateList_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PhaseStateList 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PhaseStateList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PhaseStateList *pstruWjPhaseStateList = (WJV3_STRU_PhaseStateList *)pvoidWjDf;
    PhaseStateList_t *pstruAsnPhaseStateList = (PhaseStateList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    PhaseState_t *pstruPhaseState_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_PHASESTATE_NUM < pstruWjPhaseStateList->u8PhaseStateNum)
        || (1 > pstruWjPhaseStateList->u8PhaseStateNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8PhaseNum = %d",
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
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_PhaseState_DfEnc(pstruPhaseState_node, &(pstruWjPhaseStateList->struPhaseStatelist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PhaseState_DfEnc is err");
            FREEMEM(pstruPhaseState_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnPhaseStateList->list), pstruPhaseState_node);
    }
    return true;
}
/**
 * @brief    WJV3_PhaseStateList_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PhaseStateList 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PhaseStateList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PhaseStateList *pstruWjPhaseStateList = (WJV3_STRU_PhaseStateList *)pvoidWjDf;
    PhaseStateList_t *pstruAsnPhaseStateList = (PhaseStateList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_PHASESTATE_NUM < pstruAsnPhaseStateList->list.count)
        || (1 > pstruAsnPhaseStateList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8NodeNum = %d",
                 pstruAsnPhaseStateList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnPhaseStateList->list.count; u32i++)
    {
        n32Ret = WJV3_PhaseState_DfDec(pstruAsnPhaseStateList->list.array[u32i],
                                     &(pstruWjPhaseStateList->struPhaseStatelist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PhaseState_DfDec is err");
            return false;
        }
    }
    pstruWjPhaseStateList->u8PhaseStateNum = (uint8_t)u32i;
    return true;
}
/**
 * @brief    WJV3_Phase_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 Phase 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Phase_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Phase *pstruWjPhase = (WJV3_STRU_Phase *)pvoidWjDf;
    Phase_t *pstruAsnPhase = (Phase_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_PHASEID_SIZE < pstruWjPhase->n32id)
        || (WJV3_MIN_PHASEID_SIZE > pstruWjPhase->n32id))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32id = %d",
                 pstruWjPhase->n32id);
        return false;
    }
    #endif
    pstruAsnPhase->id = pstruWjPhase->n32id;
    n32Ret = WJV3_PhaseStateList_DfEnc(&(pstruAsnPhase->phaseStates), &(pstruWjPhase->struphaseStates));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PhaseStateList_DfEnc is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_Phase_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 Phase 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_Phase_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_Phase *pstruWjPhase = (WJV3_STRU_Phase *)pvoidWjDf;
    Phase_t *pstruAsnPhase = (Phase_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_PHASEID_SIZE < pstruAsnPhase->id)
        || (WJV3_MIN_PHASEID_SIZE > pstruAsnPhase->id))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:n32id = %d",
                 pstruAsnPhase->id);
        return false;
    }
    #endif
    pstruWjPhase->n32id = pstruAsnPhase->id;
    n32Ret = WJV3_PhaseStateList_DfDec(&(pstruAsnPhase->phaseStates), &(pstruWjPhase->struphaseStates));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PhaseStateList_DfDec is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_PhaseList_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PhaseList 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PhaseList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PhaseList *pstruWjPhaseList = (WJV3_STRU_PhaseList *)pvoidWjDf;
    PhaseList_t *pstruAsnPhaseList = (PhaseList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    Phase_t *pstruphase_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_PHASE_NUM < pstruWjPhaseList->u8PhaseNum)
        || (1 > pstruWjPhaseList->u8PhaseNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8PhaseNum = %d",
                 pstruWjPhaseList->u8PhaseNum);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruWjPhaseList->u8PhaseNum; u32i++)
    {
        pstruphase_node = CALLOC(1, sizeof(Phase_t));
        if (NULL == pstruphase_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_Phase_DfEnc(pstruphase_node, &(pstruWjPhaseList->struPhaselist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_Phase_DfEnc is err");
            FREEMEM(pstruphase_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnPhaseList->list), pstruphase_node);
    }
    return true;
}
/**
 * @brief    WJV3_PhaseList_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PhaseList 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PhaseList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PhaseList *pstruWjPhaseList = (WJV3_STRU_PhaseList *)pvoidWjDf;
    PhaseList_t *pstruAsnPhaseList = (PhaseList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_PHASE_NUM < pstruAsnPhaseList->list.count)
        || (1 > pstruAsnPhaseList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnPhaseList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnPhaseList->list.count; u32i++)
    {
        n32Ret = WJV3_Phase_DfDec(pstruAsnPhaseList->list.array[u32i],
                                &(pstruWjPhaseList->struPhaselist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_Phase_DfDec is err");
            return false;
        }
    }
    pstruWjPhaseList->u8PhaseNum = u32i;
    return true;
}
/**
 * @brief    WJV3_IntersectionState_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 IntersectionState 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_IntersectionState_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_IntersectionState *pstruWjIntersectionState = (WJV3_STRU_IntersectionState *)pvoidWjDf;
    IntersectionState_t *pstruAsnIntersectionState = (IntersectionState_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_NodeReferenceID_DfEnc(&(pstruAsnIntersectionState->intersectionId), &(pstruWjIntersectionState->struintersectionId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeReferenceID_DfEnc is err");
        return false;
    }
    pstruAsnIntersectionState->status.size = WJV3_LEN_BYTE_INTERSECTIONSTATEOBJ;
    pstruAsnIntersectionState->status.bits_unused = (8 * WJV3_LEN_BYTE_INTERSECTIONSTATEOBJ) - WJV3_LEN_BITSTR_INTERSECTIONSTATEOBJ;
    pstruAsnIntersectionState->status.buf = CALLOC(1, pstruAsnIntersectionState->status.size);
    if (NULL == pstruAsnIntersectionState->status.buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                STACK_MSG_MODULE,
                "calloc is err");
        return false;
    }
    n32Ret = WJV3_BITSTRING_DeEnc(&(pstruAsnIntersectionState->status), pstruWjIntersectionState->u.u8status);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                STACK_MSG_MODULE,
                "WJV3_BITSTRING_DeEnc is err");
        return false;
    }
    if (WJV3_PRESENT == pstruWjIntersectionState->u8moy_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_MINUTEOFTHEYEAR_SIZE < pstruWjIntersectionState->n32moy)
            || (WJV3_MIN_MINUTEOFTHEYEAR_SIZE > pstruWjIntersectionState->n32moy))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32moy = %d",
                     pstruWjIntersectionState->n32moy);
            return false;
        }
        #endif
        pstruAsnIntersectionState->moy = CALLOC(1, sizeof(MinuteOfTheYear_t));
        if (NULL == pstruAsnIntersectionState->moy)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnIntersectionState->moy) = pstruWjIntersectionState->n32moy;
    }
    else
    {
        pstruAsnIntersectionState->moy = NULL;
    }
    if (WJV3_PRESENT == pstruWjIntersectionState->u8timeStamp_Present)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DSECOND_SIZE < pstruWjIntersectionState->n32timeStamp)
            || (WJV3_MIN_DSECOND_SIZE > pstruWjIntersectionState->n32timeStamp))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:n32timeStamp = %d",
                     pstruWjIntersectionState->n32timeStamp);
            return false;
        }
        #endif
        pstruAsnIntersectionState->timeStamp = CALLOC(1, sizeof(DSecond_t));
        if (NULL == pstruAsnIntersectionState->timeStamp)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        *(pstruAsnIntersectionState->timeStamp) = pstruWjIntersectionState->n32timeStamp;
    }
    else
    {
        pstruAsnIntersectionState->timeStamp = NULL;
    }
    n32Ret = WJV3_PhaseList_DfEnc(&(pstruAsnIntersectionState->phases), &(pstruWjIntersectionState->struphases));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PhaseList_DfEnc is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_IntersectionState_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 IntersectionState 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_IntersectionState_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_IntersectionState *pstruWjIntersectionState = (WJV3_STRU_IntersectionState *)pvoidWjDf;
    IntersectionState_t *pstruAsnIntersectionState = (IntersectionState_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    n32Ret = WJV3_NodeReferenceID_DfDec(&(pstruAsnIntersectionState->intersectionId), &(pstruWjIntersectionState->struintersectionId));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_NodeReferenceID_DfDec is err");
        return false;
    }
    if ((NULL == pstruAsnIntersectionState->status.buf)
        || (WJV3_LEN_BYTE_INTERSECTIONSTATEOBJ != pstruAsnIntersectionState->status.size))
    {
        LogPrint(LOG_LEVEL_ERR,
                STACK_MSG_MODULE,
                "out of rangth:size = %d",
                pstruAsnIntersectionState->status.size);
        return false;
    }
    n32Ret = WJV3_BITSTRING_DeDec(&(pstruAsnIntersectionState->status), pstruWjIntersectionState->u.u8status);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                    STACK_MSG_MODULE,
                    "WJV3_BITSTRING_DeDec is err");
        return false;
    }
    if (NULL != pstruAsnIntersectionState->moy)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_MINUTEOFTHEYEAR_SIZE < *(pstruAsnIntersectionState->moy))
            || (WJV3_MIN_MINUTEOFTHEYEAR_SIZE > *(pstruAsnIntersectionState->moy)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:moy = %d",
                     *(pstruAsnIntersectionState->moy));
            return false;
        }
        #endif
        pstruWjIntersectionState->n32moy = *(pstruAsnIntersectionState->moy);
        pstruWjIntersectionState->u8moy_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjIntersectionState->u8moy_Present = WJV3_ABSENT;
    }
    if (NULL != pstruAsnIntersectionState->timeStamp)
    {
        #ifdef _CHECK_
        if ((WJV3_MAX_DSECOND_SIZE < *(pstruAsnIntersectionState->timeStamp))
            || (WJV3_MIN_DSECOND_SIZE > *(pstruAsnIntersectionState->timeStamp)))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:timeStamp = %d",
                     *(pstruAsnIntersectionState->timeStamp));
            return false;
        }
        #endif
        pstruWjIntersectionState->n32timeStamp = *(pstruAsnIntersectionState->timeStamp);
        pstruWjIntersectionState->u8timeStamp_Present = WJV3_PRESENT;
    }
    else
    {
        pstruWjIntersectionState->u8timeStamp_Present = WJV3_ABSENT;
    }
    n32Ret = WJV3_PhaseList_DfDec(&(pstruAsnIntersectionState->phases), &(pstruWjIntersectionState->struphases));
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV3_PhaseList_DfDec is err");
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_IntersectionStateList_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 IntersectionStateList 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_IntersectionStateList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_IntersectionStateList *pstruWjIntersectionStateList = (WJV3_STRU_IntersectionStateList *)pvoidWjDf;
    IntersectionStateList_t *pstruAsnIntersectionStateList = (IntersectionStateList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    IntersectionState_t *pstruIntersectionstate_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_INTERSECTIONSTATE_NUM < pstruWjIntersectionStateList->u8IntersectionStateNum)
        || (1 > pstruWjIntersectionStateList->u8IntersectionStateNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8IntersectionStateNum = %d",
                 pstruWjIntersectionStateList->u8IntersectionStateNum);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruWjIntersectionStateList->u8IntersectionStateNum; u32i++)
    {
        pstruIntersectionstate_node = CALLOC(1, sizeof(IntersectionState_t));
        if (NULL == pstruIntersectionstate_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_IntersectionState_DfEnc(pstruIntersectionstate_node, &(pstruWjIntersectionStateList->struIntersectionStatelist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_IntersectionState_DfEnc is err");
            FREEMEM(pstruIntersectionstate_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnIntersectionStateList->list), pstruIntersectionstate_node);
    }
    return true;
}
/**
 * @brief    WJV3_IntersectionStateList_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 IntersectionStateList 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_IntersectionStateList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_IntersectionStateList *pstruWjIntersectionStateList = (WJV3_STRU_IntersectionStateList *)pvoidWjDf;
    IntersectionStateList_t *pstruAsnIntersectionStateList = (IntersectionStateList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_INTERSECTIONSTATE_NUM < pstruAsnIntersectionStateList->list.count)
        || (1 > pstruAsnIntersectionStateList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnIntersectionStateList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnIntersectionStateList->list.count; u32i++)
    {
        n32Ret = WJV3_IntersectionState_DfDec(pstruAsnIntersectionStateList->list.array[u32i],
                                            &(pstruWjIntersectionStateList->struIntersectionStatelist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_IntersectionState_DfDec is err");
            return false;
        }
    }
    pstruWjIntersectionStateList->u8IntersectionStateNum = (uint8_t)u32i;
    return true;
}
/**
 * @brief    WJV3_PhaseState_DfEnc数据帧编码函数
 * @details   协议栈消息层编解码中 PhaseState 数据帧的编码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PathPointList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PathPointList *pstruWjPointList = (WJV3_STRU_PathPointList *)pvoidWjDf;
    PathPointList_t *pstruAsnPointList = (PathPointList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    PositionOffsetLLV_t *pstruPositionOffsetLLV_node = NULL;
    #ifdef _CHECK_
    if ((WJV3_MAX_POSITIONOFFSETLLV_NUM < pstruWjPointList->u8PositionOffsetLLVNum)
        || (2 > pstruWjPointList->u8PositionOffsetLLVNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:u8PositionOffsetLLVNum = %d",
                 pstruWjPointList->u8PositionOffsetLLVNum);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruWjPointList->u8PositionOffsetLLVNum; u32i++)
    {
        pstruPositionOffsetLLV_node = CALLOC(1, sizeof(PositionOffsetLLV_t));
        if (NULL == pstruPositionOffsetLLV_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "CALLOC is err");
            return false;
        }
        n32Ret = WJV3_PositionOffsetLLV_DfEnc(pstruPositionOffsetLLV_node, &(pstruWjPointList->struPositionOffsetLLVlist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                        STACK_MSG_MODULE,
                        "WJV3_PositionOffsetLLV_DfEnc is err");
            FREEMEM(pstruPositionOffsetLLV_node);
            return false;
        }
        asn_sequence_add(&(pstruAsnPointList->list), pstruPositionOffsetLLV_node);
    }
    return true;
}
/**
 * @brief    WJV3_PhaseState_DfDec数据帧解码函数
 * @details   协议栈消息层编解码中 PhaseState 数据帧的解码函数入口
 * @param   [in]   void * pvoidAsnMsg  asn结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      wangmeng
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>wangmeng  <td>创建初始版本
* <tr><td>2020/08/31  <td>1.0      <td>huangsai  <td>走查通过
* </table>
*/
int32_t WJV3_PathPointList_DfDec(void *pvoidAsnDf, void *pvoidWjDf)
{
    if ((NULL == pvoidAsnDf) || (NULL == pvoidWjDf))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDf, pvoidWjDf);
        return false;
    }
    WJV3_STRU_PathPointList *pstruWjPointList = (WJV3_STRU_PathPointList *)pvoidWjDf;
    PathPointList_t *pstruAsnPointList = (PathPointList_t *)pvoidAsnDf;
    int32_t n32Ret = 0;
    uint32_t u32i = 0;
    #ifdef _CHECK_
    if ((WJV3_MAX_POSITIONOFFSETLLV_NUM < pstruAsnPointList->list.count)
        || (1 > pstruAsnPointList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:count = %d",
                 pstruAsnPointList->list.count);
        return false;
    }
    #endif
    for (u32i = 0; u32i < pstruAsnPointList->list.count; u32i++)
    {
        n32Ret = WJV3_PositionOffsetLLV_DfDec(pstruAsnPointList->list.array[u32i],
                                            &(pstruWjPointList->struPositionOffsetLLVlist[u32i]));
        if (true != n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "WJV3_PositionOffsetLLV_DfDec is err");
            return false;
        }
    }
    pstruWjPointList->u8PositionOffsetLLVNum = (uint8_t)u32i;
    return true;
}