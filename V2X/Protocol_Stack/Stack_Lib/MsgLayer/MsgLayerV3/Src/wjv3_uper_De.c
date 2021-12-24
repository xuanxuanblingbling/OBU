/**
* @file         :wjv3_uper_De.c
* @brief        :该文件为协议栈数据元素编解码源文件
* @details  	:主要包含协议栈数据元素编解码接口入口函数
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
#include "wjv3_uper_De.h"
#include "wjv3_uper_com.h"
/**
 * @brief    WJV3_TransmissionState_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 TransmissionState 数据元素的编码函数入口
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
int32_t WJV3_TransmissionState_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_TransmissionState *pstruWjTransmissionState = (WJV3_ENUM_TransmissionState *)pvoidWjDe;
    TransmissionState_t *pstruAsnTransmissionState = (TransmissionState_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_TransmissionState_unavailable < (*pstruWjTransmissionState)) || (WJV3_TransmissionState_neutral > (*pstruWjTransmissionState)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjTransmissionState) = %d",
                 (*pstruWjTransmissionState));
        return false;
    }
#endif
    *pstruAsnTransmissionState = *pstruWjTransmissionState;
    return true;
}
/**
 * @brief    WJV3_TransmissionState_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 TransmissionState 数据元素的解码函数入口
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
int32_t WJV3_TransmissionState_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_TransmissionState *pstruWjTransmissionState = (WJV3_ENUM_TransmissionState *)pvoidWjDe;
    TransmissionState_t *pstruAsnTransmissionState = (TransmissionState_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_TransmissionState_unavailable < (*pstruAsnTransmissionState)) || (WJV3_TransmissionState_neutral > (*pstruAsnTransmissionState)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnTransmissionState) = %d",
                 (*pstruAsnTransmissionState));
        return false;
    }
#endif
    *pstruWjTransmissionState = *pstruAsnTransmissionState;
    return true;
}
/**
 * @brief    WJV3_PositionConfidence_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 PositionConfidence 数据元素的编码函数入口
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
int32_t WJV3_PositionConfidence_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_PositionConfidence *pstruWjPositionConfidence = (WJV3_ENUM_PositionConfidence *)pvoidWjDe;
    PositionConfidence_t *pstruAsnPositionConfidence = (PositionConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_PositionConfidence_a1cm < (*pstruWjPositionConfidence)) || (WJV3_PositionConfidence_unavailable > (*pstruWjPositionConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjPositionConfidence) = %d",
                 (*pstruWjPositionConfidence));
        return false;
    }
#endif
    *pstruAsnPositionConfidence = *pstruWjPositionConfidence;
    return true;
}
/**
 * @brief    WJV3_PositionConfidence_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 PositionConfidence 数据元素的解码函数入口
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
int32_t WJV3_PositionConfidence_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_PositionConfidence *pstruWjPositionConfidence = (WJV3_ENUM_PositionConfidence *)pvoidWjDe;
    PositionConfidence_t *pstruAsnPositionConfidence = (PositionConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_PositionConfidence_a1cm < (*pstruAsnPositionConfidence)) || (WJV3_PositionConfidence_unavailable > (*pstruAsnPositionConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnPositionConfidence) = %d",
                 (*pstruAsnPositionConfidence));
        return false;
    }
#endif
    *pstruWjPositionConfidence = *pstruAsnPositionConfidence;
    return true;
}
/**
 * @brief    WJV3_ElevationConfidence_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 ElevationConfidence 数据元素的编码函数入口
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
int32_t WJV3_ElevationConfidence_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_ElevationConfidence *pstruWjElevationConfidence = (WJV3_ENUM_ElevationConfidence *)pvoidWjDe;
    ElevationConfidence_t *pstruAsnElevationConfidence = (ElevationConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_ElevationConfidence_elev_000_01 < (*pstruWjElevationConfidence)) || (WJV3_ElevationConfidence_unavailable > (*pstruWjElevationConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjElevationConfidence) = %d",
                 (*pstruWjElevationConfidence));
        return false;
    }
#endif
    *pstruAsnElevationConfidence = *pstruWjElevationConfidence;
    return true;
}
/**
 * @brief    WJV3_ElevationConfidence_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 ElevationConfidence 数据元素的解码函数入口
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
int32_t WJV3_ElevationConfidence_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_ElevationConfidence *pstruWjElevationConfidence = (WJV3_ENUM_ElevationConfidence *)pvoidWjDe;
    ElevationConfidence_t *pstruAsnElevationConfidence = (ElevationConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_ElevationConfidence_elev_000_01 < (*pstruAsnElevationConfidence)) || (WJV3_ElevationConfidence_unavailable > (*pstruAsnElevationConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnElevationConfidence) = %d",
                 (*pstruAsnElevationConfidence));
        return false;
    }
#endif
    *pstruWjElevationConfidence = *pstruAsnElevationConfidence;
    return true;
}
/**
 * @brief    WJV3_SpeedConfidence_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 SpeedConfidence 数据元素的编码函数入口
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
int32_t WJV3_SpeedConfidence_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_SpeedConfidence *pstruWjSpeedConfidence = (WJV3_ENUM_SpeedConfidence *)pvoidWjDe;
    SpeedConfidence_t *pstruAsnSpeedConfidence = (SpeedConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_SpeedConfidence_prec0_01ms < (*pstruWjSpeedConfidence)) || (WJV3_SpeedConfidence_unavailable > (*pstruWjSpeedConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjSpeedConfidence) = %d",
                 (*pstruWjSpeedConfidence));
        return false;
    }
#endif
    *pstruAsnSpeedConfidence = *pstruWjSpeedConfidence;
    return true;
}
/**
 * @brief    WJV3_SpeedConfidence_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 SpeedConfidence 数据元素的解码函数入口
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
int32_t WJV3_SpeedConfidence_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_SpeedConfidence *pstruWjSpeedConfidence = (WJV3_ENUM_SpeedConfidence *)pvoidWjDe;
    SpeedConfidence_t *pstruAsnSpeedConfidence = (SpeedConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_SpeedConfidence_prec0_01ms < (*pstruAsnSpeedConfidence)) || (WJV3_SpeedConfidence_unavailable > (*pstruAsnSpeedConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnSpeedConfidence) = %d",
                 (*pstruAsnSpeedConfidence));
        return false;
    }
#endif
    *pstruWjSpeedConfidence = *pstruAsnSpeedConfidence;
    return true;
}
/**
 * @brief    WJV3_HeadingConfidence_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 HeadingConfidence 数据元素的编码函数入口
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
int32_t WJV3_HeadingConfidence_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_HeadingConfidence *pstruWjHeadingConfidence = (WJV3_ENUM_HeadingConfidence *)pvoidWjDe;
    HeadingConfidence_t *pstruAsnHeadingConfidence = (HeadingConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_HeadingConfidence_prec0_0125deg < (*pstruWjHeadingConfidence)) || (WJV3_HeadingConfidence_unavailable > (*pstruWjHeadingConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjHeadingConfidence) = %d",
                 (*pstruWjHeadingConfidence));
        return false;
    }
#endif
    *pstruAsnHeadingConfidence = *pstruWjHeadingConfidence;
    return true;
}
/**
 * @brief    WJV3_HeadingConfidence_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 HeadingConfidence 数据元素的解码函数入口
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
int32_t WJV3_HeadingConfidence_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_HeadingConfidence *pstruWjHeadingConfidence = (WJV3_ENUM_HeadingConfidence *)pvoidWjDe;
    HeadingConfidence_t *pstruAsnHeadingConfidence = (HeadingConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_HeadingConfidence_prec0_0125deg < (*pstruAsnHeadingConfidence)) || (WJV3_HeadingConfidence_unavailable > (*pstruAsnHeadingConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnHeadingConfidence) = %d",
                 (*pstruAsnHeadingConfidence));
        return false;
    }
#endif
    *pstruWjHeadingConfidence = *pstruAsnHeadingConfidence;
    return true;
}
/**
 * @brief    WJV3_SteeringWheelAngleConfidence_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 SteeringWheelAngleConfidence 数据元素的编码函数入口
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
int32_t WJV3_SteeringWheelAngleConfidence_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_SteeringWheelAngleConfidence *pstruWjSteeringWheelAngleConfidence = (WJV3_ENUM_SteeringWheelAngleConfidence *)pvoidWjDe;
    SteeringWheelAngleConfidence_t *pstruAsnSteeringWheelAngleConfidence = (SteeringWheelAngleConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_SteeringWheelAngleConfidence_prec0_02deg < (*pstruWjSteeringWheelAngleConfidence)) || (WJV3_SteeringWheelAngleConfidence_unavailable > (*pstruWjSteeringWheelAngleConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjSteeringWheelAngleConfidence) = %d",
                 (*pstruWjSteeringWheelAngleConfidence));
        return false;
    }
#endif
    *pstruAsnSteeringWheelAngleConfidence = *pstruWjSteeringWheelAngleConfidence;
    return true;
}
/**
 * @brief    WJV3_SteeringWheelAngleConfidence_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 SteeringWheelAngleConfidence 数据元素的解码函数入口
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
int32_t WJV3_SteeringWheelAngleConfidence_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_SteeringWheelAngleConfidence *pstruWjSteeringWheelAngleConfidence = (WJV3_ENUM_SteeringWheelAngleConfidence *)pvoidWjDe;
    SteeringWheelAngleConfidence_t *pstruAsnSteeringWheelAngleConfidence = (SteeringWheelAngleConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_SteeringWheelAngleConfidence_prec0_02deg < (*pstruAsnSteeringWheelAngleConfidence)) || (WJV3_SteeringWheelAngleConfidence_unavailable > (*pstruAsnSteeringWheelAngleConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnSteeringWheelAngleConfidence) = %d",
                 (*pstruAsnSteeringWheelAngleConfidence));
        return false;
    }
#endif
    *pstruWjSteeringWheelAngleConfidence = *pstruAsnSteeringWheelAngleConfidence;
    return true;
}
/**
 * @brief    WJV3_BrakePedalStatus_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 BrakePedalStatus 数据元素的编码函数入口
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
int32_t WJV3_BrakePedalStatus_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_BrakePedalStatus *pstruWjBrakePedalStatus = (WJV3_ENUM_BrakePedalStatus *)pvoidWjDe;
    BrakePedalStatus_t *pstruAsnBrakePedalStatus = (BrakePedalStatus_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_BrakePedalStatus_on < (*pstruWjBrakePedalStatus)) || (WJV3_BrakePedalStatus_unavailable > (*pstruWjBrakePedalStatus)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjBrakePedalStatus) = %d",
                 (*pstruWjBrakePedalStatus));
        return false;
    }
#endif
    *pstruAsnBrakePedalStatus = *pstruWjBrakePedalStatus;
    return true;
}
/**
 * @brief    WJV3_BrakePedalStatus_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 BrakePedalStatus 数据元素的解码函数入口
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
int32_t WJV3_BrakePedalStatus_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_BrakePedalStatus *pstruWjBrakePedalStatus = (WJV3_ENUM_BrakePedalStatus *)pvoidWjDe;
    BrakePedalStatus_t *pstruAsnBrakePedalStatus = (BrakePedalStatus_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_BrakePedalStatus_on < (*pstruAsnBrakePedalStatus)) || (WJV3_BrakePedalStatus_unavailable > (*pstruAsnBrakePedalStatus)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnBrakePedalStatus) = %d",
                 (*pstruAsnBrakePedalStatus));
        return false;
    }
#endif
    *pstruWjBrakePedalStatus = *pstruAsnBrakePedalStatus;
    return true;
}
/**
 * @brief    WJV3_TractionControlStatus_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 TractionControlStatus 数据元素的编码函数入口
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
int32_t WJV3_TractionControlStatus_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_TractionControlStatus *pstruWjTractionControlStatus = (WJV3_ENUM_TractionControlStatus *)pvoidWjDe;
    TractionControlStatus_t *pstruAsnTractionControlStatus = (TractionControlStatus_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_TractionControlStatus_engaged < (*pstruWjTractionControlStatus)) || (WJV3_TractionControlStatus_unavailable > (*pstruWjTractionControlStatus)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjTractionControlStatus) = %d",
                 (*pstruWjTractionControlStatus));
        return false;
    }
#endif
    *pstruAsnTractionControlStatus = *pstruWjTractionControlStatus;
    return true;
}
/**
 * @brief    WJV3_TractionControlStatus_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 TractionControlStatus 数据元素的解码函数入口
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
int32_t WJV3_TractionControlStatus_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_TractionControlStatus *pstruWjTractionControlStatus = (WJV3_ENUM_TractionControlStatus *)pvoidWjDe;
    TractionControlStatus_t *pstruAsnTractionControlStatus = (TractionControlStatus_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_TractionControlStatus_engaged < (*pstruAsnTractionControlStatus)) || (WJV3_TractionControlStatus_unavailable > (*pstruAsnTractionControlStatus)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnTractionControlStatus) = %d",
                 (*pstruAsnTractionControlStatus));
        return false;
    }
#endif
    *pstruWjTractionControlStatus = *pstruAsnTractionControlStatus;
    return true;
}
/**
 * @brief    WJV3_AntiLockBrakeStatus_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 AntiLockBrakeStatus 数据元素的编码函数入口
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
int32_t WJV3_AntiLockBrakeStatus_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_AntiLockBrakeStatus *pstruWjAntiLockBrakeStatus = (WJV3_ENUM_AntiLockBrakeStatus *)pvoidWjDe;
    AntiLockBrakeStatus_t *pstruAsnAntiLockBrakeStatus = (AntiLockBrakeStatus_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_AntiLockBrakeStatus_engaged < (*pstruWjAntiLockBrakeStatus)) || (WJV3_AntiLockBrakeStatus_unavailable > (*pstruWjAntiLockBrakeStatus)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjAntiLockBrakeStatus) = %d",
                 (*pstruWjAntiLockBrakeStatus));
        return false;
    }
#endif
    *pstruAsnAntiLockBrakeStatus = *pstruWjAntiLockBrakeStatus;
    return true;
}
/**
 * @brief    WJV3_AntiLockBrakeStatus_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 AntiLockBrakeStatus 数据元素的解码函数入口
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
int32_t WJV3_AntiLockBrakeStatus_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_AntiLockBrakeStatus *pstruWjAntiLockBrakeStatus = (WJV3_ENUM_AntiLockBrakeStatus *)pvoidWjDe;
    AntiLockBrakeStatus_t *pstruAsnAntiLockBrakeStatus = (AntiLockBrakeStatus_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_AntiLockBrakeStatus_engaged < (*pstruAsnAntiLockBrakeStatus)) || (WJV3_AntiLockBrakeStatus_unavailable > (*pstruAsnAntiLockBrakeStatus)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnAntiLockBrakeStatus) = %d",
                 (*pstruAsnAntiLockBrakeStatus));
        return false;
    }
#endif
    *pstruWjAntiLockBrakeStatus = *pstruAsnAntiLockBrakeStatus;
    return true;
}
/**
 * @brief    WJV3_StabilityControlStatus_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 StabilityControlStatus 数据元素的编码函数入口
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
int32_t WJV3_StabilityControlStatus_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_StabilityControlStatus *pstruWjStabilityControlStatus = (WJV3_ENUM_StabilityControlStatus *)pvoidWjDe;
    StabilityControlStatus_t *pstruAsnStabilityControlStatus = (StabilityControlStatus_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_StabilityControlStatus_engaged < (*pstruWjStabilityControlStatus)) || (WJV3_StabilityControlStatus_unavailable > (*pstruWjStabilityControlStatus)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjStabilityControlStatus) = %d",
                 (*pstruWjStabilityControlStatus));
        return false;
    }
#endif
    *pstruAsnStabilityControlStatus = *pstruWjStabilityControlStatus;
    return true;
}
/**
 * @brief    WJV3_StabilityControlStatus_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 StabilityControlStatus 数据元素的解码函数入口
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
int32_t WJV3_StabilityControlStatus_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_StabilityControlStatus *pstruWjStabilityControlStatus = (WJV3_ENUM_StabilityControlStatus *)pvoidWjDe;
    StabilityControlStatus_t *pstruAsnStabilityControlStatus = (StabilityControlStatus_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_StabilityControlStatus_engaged < (*pstruAsnStabilityControlStatus)) || (WJV3_StabilityControlStatus_unavailable > (*pstruAsnStabilityControlStatus)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnStabilityControlStatus) = %d",
                 (*pstruAsnStabilityControlStatus));
        return false;
    }
#endif
    *pstruWjStabilityControlStatus = *pstruAsnStabilityControlStatus;
    return true;
}
/**
 * @brief    WJV3_BrakeBoostApplied_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 BrakeBoostApplied 数据元素的编码函数入口
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
int32_t WJV3_BrakeBoostApplied_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_BrakeBoostApplied *pstruWjBrakeBoostApplied = (WJV3_ENUM_BrakeBoostApplied *)pvoidWjDe;
    BrakeBoostApplied_t *pstruAsnBrakeBoostApplied = (BrakeBoostApplied_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_BrakeBoostApplied_on < (*pstruWjBrakeBoostApplied)) || (WJV3_BrakeBoostApplied_unavailable > (*pstruWjBrakeBoostApplied)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjBrakeBoostApplied) = %d",
                 (*pstruWjBrakeBoostApplied));
        return false;
    }
#endif
    *pstruAsnBrakeBoostApplied = *pstruWjBrakeBoostApplied;
    return true;
}
/**
 * @brief    WJV3_BrakeBoostApplied_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 BrakeBoostApplied 数据元素的解码函数入口
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
int32_t WJV3_BrakeBoostApplied_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_BrakeBoostApplied *pstruWjBrakeBoostApplied = (WJV3_ENUM_BrakeBoostApplied *)pvoidWjDe;
    BrakeBoostApplied_t *pstruAsnBrakeBoostApplied = (BrakeBoostApplied_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_BrakeBoostApplied_on < (*pstruAsnBrakeBoostApplied)) || (WJV3_BrakeBoostApplied_unavailable > (*pstruAsnBrakeBoostApplied)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnBrakeBoostApplied) = %d",
                 (*pstruAsnBrakeBoostApplied));
        return false;
    }
#endif
    *pstruWjBrakeBoostApplied = *pstruAsnBrakeBoostApplied;
    return true;
}
/**
 * @brief    WJV3_AuxiliaryBrakeStatus_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 AuxiliaryBrakeStatus 数据元素的编码函数入口
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
int32_t WJV3_AuxiliaryBrakeStatus_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_AuxiliaryBrakeStatus *pstruWjAuxiliaryBrakeStatus = (WJV3_ENUM_AuxiliaryBrakeStatus *)pvoidWjDe;
    AuxiliaryBrakeStatus_t *pstruAsnAuxiliaryBrakeStatus = (AuxiliaryBrakeStatus_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_AuxiliaryBrakeStatus_reserved < (*pstruWjAuxiliaryBrakeStatus)) || (WJV3_AuxiliaryBrakeStatus_unavailable > (*pstruWjAuxiliaryBrakeStatus)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjAuxiliaryBrakeStatus) = %d",
                 (*pstruWjAuxiliaryBrakeStatus));
        return false;
    }
#endif
    *pstruAsnAuxiliaryBrakeStatus = *pstruWjAuxiliaryBrakeStatus;
    return true;
}
/**
 * @brief    WJV3_BrakeBoostApplied_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 BrakeBoostApplied 数据元素的解码函数入口
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
int32_t WJV3_AuxiliaryBrakeStatus_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_AuxiliaryBrakeStatus *pstruWjAuxiliaryBrakeStatus = (WJV3_ENUM_AuxiliaryBrakeStatus *)pvoidWjDe;
    AuxiliaryBrakeStatus_t *pstruAsnAuxiliaryBrakeStatus = (AuxiliaryBrakeStatus_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_AuxiliaryBrakeStatus_reserved < (*pstruAsnAuxiliaryBrakeStatus)) || (WJV3_AuxiliaryBrakeStatus_unavailable > (*pstruAsnAuxiliaryBrakeStatus)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnAuxiliaryBrakeStatus) = %d",
                 (*pstruAsnAuxiliaryBrakeStatus));
        return false;
    }
#endif
    *pstruWjAuxiliaryBrakeStatus = *pstruAsnAuxiliaryBrakeStatus;
    return true;
}
/**
 * @brief    WJV3_TimeConfidence_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 TimeConfidence 数据元素的编码函数入口
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
int32_t WJV3_TimeConfidence_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_TimeConfidence *pstruWjTimeConfidence = (WJV3_ENUM_TimeConfidence *)pvoidWjDe;
    TimeConfidence_t *pstruAsnTimeConfidence = (TimeConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_TimeConfidence_time_000_000_000_000_01 < (*pstruWjTimeConfidence)) || (WJV3_TimeConfidence_unavailable > (*pstruWjTimeConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjTimeConfidence) = %d",
                 (*pstruWjTimeConfidence));
        return false;
    }
#endif
    *pstruAsnTimeConfidence = *pstruWjTimeConfidence;
    return true;
}
/**
 * @brief    WJV3_TimeConfidence_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 TimeConfidence 数据元素的解码函数入口
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
int32_t WJV3_TimeConfidence_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_TimeConfidence *pstruWjTimeConfidence = (WJV3_ENUM_TimeConfidence *)pvoidWjDe;
    TimeConfidence_t *pstruAsnTimeConfidence = (TimeConfidence_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_TimeConfidence_time_000_000_000_000_01 < (*pstruAsnTimeConfidence)) || (WJV3_TimeConfidence_unavailable > (*pstruAsnTimeConfidence)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnTimeConfidence) = %d",
                 (*pstruAsnTimeConfidence));
        return false;
    }
#endif
    *pstruWjTimeConfidence = *pstruAsnTimeConfidence;
    return true;
}
/**
 * @brief    WJV3_SpeedLimitType_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 SpeedLimitType 数据元素的编码函数入口
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
int32_t WJV3_SpeedLimitType_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_SpeedLimitType *pstruWjSpeedLimitType = (WJV3_ENUM_SpeedLimitType *)pvoidWjDe;
    SpeedLimitType_t *pstruAsnSpeedLimitType = (SpeedLimitType_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_SpeedLimitType_vehiclesWithTrailersNightMaxSpeed < (*pstruWjSpeedLimitType)) || (WJV3_SpeedLimitType_unknown > (*pstruWjSpeedLimitType)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjSpeedLimitType) = %d",
                 (*pstruWjSpeedLimitType));
        return false;
    }
#endif
    *pstruAsnSpeedLimitType = *pstruWjSpeedLimitType;
    return true;
}
/**
 * @brief    WJV3_SpeedLimitType_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 SpeedLimitType 数据元素的解码函数入口
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
int32_t WJV3_SpeedLimitType_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_SpeedLimitType *pstruWjSpeedLimitType = (WJV3_ENUM_SpeedLimitType *)pvoidWjDe;
    SpeedLimitType_t *pstruAsnSpeedLimitType = (SpeedLimitType_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_SpeedLimitType_vehiclesWithTrailersNightMaxSpeed < (*pstruAsnSpeedLimitType)) || (WJV3_SpeedLimitType_unknown > (*pstruAsnSpeedLimitType)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnSpeedLimitType) = %d",
                 (*pstruAsnSpeedLimitType));
        return false;
    }
#endif
    *pstruWjSpeedLimitType = *pstruAsnSpeedLimitType;
    return true;
}
/**
 * @brief    WJV3_LightState_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 LightState 数据元素的编码函数入口
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
int32_t WJV3_LightState_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_LightState *pstruWjLightState = (WJV3_ENUM_LightState *)pvoidWjDe;
    LightState_t *pstruAsnLightState = (LightState_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_LightState_caution_Conflicting_Traffic < (*pstruWjLightState)) || (WJV3_LightState_unavailable > (*pstruWjLightState)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjLightState) = %d",
                 (*pstruWjLightState));
        return false;
    }
#endif
    *pstruAsnLightState = *pstruWjLightState;
    return true;
}
/**
 * @brief    WJV3_LightState_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 LightState 数据元素的解码函数入口
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
int32_t WJV3_LightState_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_ENUM_LightState *pstruWjLightState = (WJV3_ENUM_LightState *)pvoidWjDe;
    LightState_t *pstruAsnLightState = (LightState_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_LightState_caution_Conflicting_Traffic < (*pstruAsnLightState)) || (WJV3_LightState_unavailable > (*pstruAsnLightState)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnLightState) = %d",
                 (*pstruAsnLightState));
        return false;
    }
#endif
    *pstruWjLightState = *pstruAsnLightState;
    return true;
}
/**
 * @brief    WJV3_AlertType_DeEnc数据元素编码函数
 * @details   协议栈消息层编解码中 AlertType 数据元素的编码函数入口
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
int32_t WJV3_AlertType_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_STRU_AlertType *pstruWjAlertType = (WJV3_STRU_AlertType *)pvoidWjDe;
    AlertType_t *pstruAsnAlertType = (AlertType_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_MAX_ALERTTYPE_SIZE < (*pstruWjAlertType)) || (WJV3_MIN_ALERTTYPE_SIZE > (*pstruWjAlertType)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruWjAlertType) = %d",
                 (*pstruWjAlertType));
        return false;
    }
#endif
    *pstruAsnAlertType = *pstruWjAlertType;
    return true;
}
/**
 * @brief    WJV3_AlertType_DeDec数据元素解码函数
 * @details   协议栈消息层编解码中 AlertType 数据元素的解码函数入口
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
int32_t WJV3_AlertType_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDF = %p pvoidWjDF = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV3_STRU_AlertType *pstruWjAlertType = (WJV3_STRU_AlertType *)pvoidWjDe;
    AlertType_t *pstruAsnAlertType = (AlertType_t *)pvoidAsnDe;
#ifdef _CHECK_
    if ((WJV3_MAX_ALERTTYPE_SIZE < (*pstruAsnAlertType)) || (WJV3_MIN_ALERTTYPE_SIZE > (*pstruAsnAlertType)))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:(*pstruAsnAlertType) = %d",
                 (*pstruAsnAlertType));
        return false;
    }
#endif
    *pstruWjAlertType = *pstruAsnAlertType;
    return true;
}
/**
 * @brief    WJV3_BITSTRING_DeEnc数据元素解码函数
 * @details   协议栈消息层编解码中 BITSTRING 字段编码函数
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
int32_t WJV3_BITSTRING_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    BIT_STRING_t *pAsnBitString = (BIT_STRING_t *)pvoidAsnDe;
    uint8_t *pstruWjbuf = (uint8_t *)pvoidWjDe;
    uint8_t bit8 = 0x00;
    uint16_t bit16 = 0x0000;
    int n = 0;
    if (pAsnBitString->size == 1)
    {
        int i = 7;
        for (i = 7; i >= 0; i--)
        {
            bit8 |= (((*pstruWjbuf) & (0x01 << n)) >> n) << i;
            n++;
        }
        pAsnBitString->buf[0] = bit8;
    }
    else if (pAsnBitString->size == 2)
    {
        uint16_t Bit16 = 0x0000;
        Bit16 = (pstruWjbuf[0] << 8) | pstruWjbuf[1];
        int i = 15;
        for (i = 15; i >= 0; i--)
        {
            bit16 |= ((Bit16 & (0x0001 << n)) >> n) << i;
            n++;
        }

        pAsnBitString->buf[1] = (bit16 >> 8) & 0xFF;
        pAsnBitString->buf[0] = (bit16 & 0xFF);
        //此处可能存在问题
        //pAsnBitString->buf[0] = (bit16 >> 8) & 0xFF;
        //pAsnBitString->buf[1] = (bit16 & 0xFF);
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:size = %d",
                 pAsnBitString->size);
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_BITSTRING_DeDec的bitstring字段解码
 * @details   协议栈消息层编解码中 BITSTRING 字段解码函数
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
int32_t WJV3_BITSTRING_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    BIT_STRING_t *pAsnBitString = (BIT_STRING_t *)pvoidAsnDe;
    uint8_t *pstruWjbuf = (uint8_t *)pvoidWjDe;
    uint8_t bit8 = 0x00;
    uint16_t bit16 = 0x0000;
    int n = 0;
    if (pAsnBitString->size == 1)
    {
        int i = 7;
        for (i = 7; i >= 0; i--)
        {
            bit8 |= ((pAsnBitString->buf[0] & (0x80 >> n)) << n) >> i;
            n++;
        }
        *pstruWjbuf = bit8;
    }
    else if (pAsnBitString->size == 2)
    {
        uint16_t Bit16 = 0x0000;
        Bit16 = (pAsnBitString->buf[0] << 8) | pAsnBitString->buf[1];
        int i = 15;
        for (i = 15; i >= 0; i--)
        {
            bit16 |= ((Bit16 & (0x8000 >> n)) << n) >> i;
            n++;
        }
        pstruWjbuf[1] = (bit16 >> 8) & 0xFF;
        pstruWjbuf[0] = (bit16 & 0xFF);
        //此处可能存在问题
        //pstruWjbuf[0] = (bit16 >> 8) & 0xFF;
        //pstruWjbuf[1] = (bit16 & 0xFF);
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "out of rangth:size = %d",
                 pAsnBitString->size);
        return false;
    }
    return true;
}
/**
 * @brief    WJV3_Check_IA5String检查函数
 * @details   协议栈消息层编解码中 IA5String 字段检查
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @param   [in]   int32 * length  长度
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
int32_t WJV3_Check_IA5String(void *pvoidWjDF, int32_t length)
{
    uint8_t *IA5String = (uint8_t *)pvoidWjDF;
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if (IA5String[i] >= 0x80)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "out of rangth:u8name[%d] = %02x",
                     i, IA5String[i]);
            return false;
        }
    }
    return true;
}