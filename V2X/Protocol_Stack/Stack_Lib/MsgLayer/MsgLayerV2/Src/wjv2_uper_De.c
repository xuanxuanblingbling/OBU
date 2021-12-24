/**
* @file         :wjv2_uper_De.c
* @brief        :数据元素编解码结构
* @details      :关于数据元素中的bitstring格式和枚举格式的编解码函数
* @author       :huangsai  any question please send mail to huangsai@wanji,net.cn
* @date         :2020-12-18
* @version      :V1.0
* @copyright    :Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：IMX6
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-18  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
/* 头文件包含 */
#include "wjv2_uper_De.h"
#include "wjv2_uper_com.h"

/**
* @brief     WJV2_AllowedManeuvers_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_AllowedManeuvers_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_AllowedManeuvers *pstrbitWjAllowedManeuvers = (WJV2_BIT_AllowedManeuvers *)pvoidWjDe;
    AllowedManeuvers_t *pstrbitAsnAllowedManeuvers = (AllowedManeuvers_t *)pvoidAsnDe;

    pstrbitAsnAllowedManeuvers->size = WJV2_LEN_BYTE_ALLOWEDMANEUVERS;
    pstrbitAsnAllowedManeuvers->bits_unused = 8 * WJV2_LEN_BYTE_ALLOWEDMANEUVERS - WJV2_LEN_BITSTR_ALLOWEDMANEUVERS;
    pstrbitAsnAllowedManeuvers->buf = CALLOC(1, pstrbitAsnAllowedManeuvers->size);
    if (NULL == pstrbitAsnAllowedManeuvers->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }

    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnAllowedManeuvers, pstrbitWjAllowedManeuvers);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_AllowedManeuvers_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_AllowedManeuvers_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_AllowedManeuvers *pstrbitWjAllowedManeuvers = (WJV2_BIT_AllowedManeuvers *)pvoidWjDe;
    AllowedManeuvers_t *pstrbitAsnAllowedManeuvers = (AllowedManeuvers_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnAllowedManeuvers->buf) || (WJV2_LEN_BYTE_ALLOWEDMANEUVERS != pstrbitAsnAllowedManeuvers->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnAllowedManeuvers->size,
                 pstrbitAsnAllowedManeuvers->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnAllowedManeuvers, pstrbitWjAllowedManeuvers);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_BrakeAppliedStatus_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_BrakeAppliedStatus_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_BrakeAppliedStatus *pstrbitWjBrakeAppliedStatus = (WJV2_BIT_BrakeAppliedStatus *)pvoidWjDe;
    BrakeAppliedStatus_t *pstrbitAsnBrakeAppliedStatus = (BrakeAppliedStatus_t *)pvoidAsnDe;

    pstrbitAsnBrakeAppliedStatus->size = WJV2_LEN_BYTE_BRAFEAPPLIEDSTATUS;
    pstrbitAsnBrakeAppliedStatus->bits_unused = 8 * WJV2_LEN_BYTE_BRAFEAPPLIEDSTATUS - WJV2_LEN_BITSTR_BRAFEAPPLIEDSTATUS;
    pstrbitAsnBrakeAppliedStatus->buf = CALLOC(1, pstrbitAsnBrakeAppliedStatus->size);
    if (NULL == pstrbitAsnBrakeAppliedStatus->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnBrakeAppliedStatus, pstrbitWjBrakeAppliedStatus);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_BrakeAppliedStatus_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_BrakeAppliedStatus_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_BrakeAppliedStatus *pstrbitWjBrakeAppliedStatus = (WJV2_BIT_BrakeAppliedStatus *)pvoidWjDe;
    BrakeAppliedStatus_t *pstrbitAsnBrakeAppliedStatus = (BrakeAppliedStatus_t *)pvoidAsnDe;

    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnBrakeAppliedStatus, pstrbitWjBrakeAppliedStatus);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_DescriptiveName_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_DescriptiveName_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_IA5_DescriptiveName *pstria5WjDescriptiveName = (WJV2_IA5_DescriptiveName *)pvoidWjDe;
    DescriptiveName_t *pstria5AsnDescriptiveName = (DescriptiveName_t *)pvoidAsnDe;
    uint32_t u32i = 0;
    if ((WJV2_MAX_IA5_DESCIPTIVENAME_LEN < pstria5WjDescriptiveName->u8DescriptiveNameNum) || (1 > pstria5WjDescriptiveName->u8DescriptiveNameNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:pstria5WjDescriptiveName->u8DescriptiveNameNum = %d",
                 pstria5WjDescriptiveName->u8DescriptiveNameNum);
        return false;
    }
    pstria5AsnDescriptiveName->buf = CALLOC(1, pstria5WjDescriptiveName->u8DescriptiveNameNum);
    if (NULL == pstria5AsnDescriptiveName->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    pstria5AsnDescriptiveName->size = pstria5WjDescriptiveName->u8DescriptiveNameNum;
    for (u32i = 0; u32i < pstria5AsnDescriptiveName->size; u32i++)
    {
        if ((WJV2_MAX_DESCRIPTIVENAME_SIZE < pstria5WjDescriptiveName->u8DescriptiveName[u32i]) || (WJV2_MIN_DESCRIPTIVENAME_SIZE > pstria5WjDescriptiveName->u8DescriptiveName[u32i]))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "out of rangth:pstria5WjDescriptiveName->u8DescriptiveName[%d] = %d",
                     u32i, pstria5WjDescriptiveName->u8DescriptiveName[u32i]);
            return false;
        }
    }
    memcpy(pstria5AsnDescriptiveName->buf, pstria5WjDescriptiveName->u8DescriptiveName, pstria5AsnDescriptiveName->size);
    return true;
}
/**
* @brief     WJV2_DescriptiveName_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_DescriptiveName_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_IA5_DescriptiveName *pstria5WjDescriptiveName = (WJV2_IA5_DescriptiveName *)pvoidWjDe;
    DescriptiveName_t *pstria5AsnDescriptiveName = (DescriptiveName_t *)pvoidAsnDe;
    if (0 < pstria5AsnDescriptiveName->size)
    {
        if ((WJV2_MAX_IA5_DESCIPTIVENAME_LEN < pstria5AsnDescriptiveName->size) || (1 > pstria5AsnDescriptiveName->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "out of rangth:pstria5AsnDescriptiveName->size = %d",
                     pstria5AsnDescriptiveName->size);
            return false;
        }
        if (NULL == pstria5AsnDescriptiveName->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "buf is null:pstria5AsnDescriptiveName->buf = %p",
                     pstria5AsnDescriptiveName->buf);
            return false;
        }
        pstria5WjDescriptiveName->u8DescriptiveNameNum = pstria5AsnDescriptiveName->size;
        memcpy(pstria5WjDescriptiveName->u8DescriptiveName, pstria5AsnDescriptiveName->buf, pstria5AsnDescriptiveName->size);
    }
    else
    {
        pstria5WjDescriptiveName->u8DescriptiveNameNum = 0;
    }
    return true;
}
/**
* @brief     WJV2_ExteriorLights_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_ExteriorLights_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_ExteriorLights *pstrbitWjExteriorLights = (WJV2_BIT_ExteriorLights *)pvoidWjDe;
    ExteriorLights_t *pstrbitAsnExteriorLights = (ExteriorLights_t *)pvoidAsnDe;

    pstrbitAsnExteriorLights->size = WJV2_LEN_BYTE_EXTERIORLIGHT;
    pstrbitAsnExteriorLights->bits_unused = 8 * WJV2_LEN_BYTE_EXTERIORLIGHT - WJV2_LEN_BITSTR_EXTERIORLIGHT;
    pstrbitAsnExteriorLights->buf = CALLOC(1, pstrbitAsnExteriorLights->size);
    if (NULL == pstrbitAsnExteriorLights->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnExteriorLights, pstrbitWjExteriorLights);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_ExteriorLights_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_ExteriorLights_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_ExteriorLights *pstrbitWjExteriorLights = (WJV2_BIT_ExteriorLights *)pvoidWjDe;
    ExteriorLights_t *pstrbitAsnExteriorLights = (ExteriorLights_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnExteriorLights->buf) || (WJV2_LEN_BYTE_EXTERIORLIGHT != pstrbitAsnExteriorLights->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnExteriorLights->size,
                 pstrbitAsnExteriorLights->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnExteriorLights, pstrbitWjExteriorLights);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_GNSSstatus_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_GNSSstatus_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_GNSSstatus *pstrbitWjGNSSstatus = (WJV2_BIT_GNSSstatus *)pvoidWjDe;
    GNSSstatus_t *pstrbitAsnGNSSstatus = (GNSSstatus_t *)pvoidAsnDe;

    pstrbitAsnGNSSstatus->size = WJV2_LEN_BYTE_GNSSSTATUS;
    pstrbitAsnGNSSstatus->bits_unused = 8 * WJV2_LEN_BYTE_GNSSSTATUS - WJV2_LEN_BITSTR_GNSSSTATUS;
    pstrbitAsnGNSSstatus->buf = CALLOC(1, pstrbitAsnGNSSstatus->size);
    if (NULL == pstrbitAsnGNSSstatus->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnGNSSstatus, pstrbitWjGNSSstatus);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_GNSSstatus_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_GNSSstatus_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_GNSSstatus *pstrbitWjGNSSstatus = (WJV2_BIT_GNSSstatus *)pvoidWjDe;
    GNSSstatus_t *pstrbitAsnGNSSstatus = (GNSSstatus_t *)pvoidAsnDe;
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnGNSSstatus, pstrbitWjGNSSstatus);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_IntersectionStatusObject_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_IntersectionStatusObject_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_IntersectionStatusObject *pstrbitWjIntersectionStatusObject = (WJV2_BIT_IntersectionStatusObject *)pvoidWjDe;
    IntersectionStatusObject_t *pstrbitAsnIntersectionStatusObject = (IntersectionStatusObject_t *)pvoidAsnDe;

    pstrbitAsnIntersectionStatusObject->size = WJV2_LEN_BYTE_INTERSECTIONSTATUSPBJECT;
    pstrbitAsnIntersectionStatusObject->bits_unused = 8 * WJV2_LEN_BYTE_INTERSECTIONSTATUSPBJECT - WJV2_LEN_BITSTR_INTERSECTIONSTATUSPBJECT;
    pstrbitAsnIntersectionStatusObject->buf = CALLOC(1, pstrbitAsnIntersectionStatusObject->size);
    if (NULL == pstrbitAsnIntersectionStatusObject->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnIntersectionStatusObject, pstrbitWjIntersectionStatusObject);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_IntersectionStatusObject_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_IntersectionStatusObject_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_IntersectionStatusObject *pstrbitWjIntersectionStatusObject = (WJV2_BIT_IntersectionStatusObject *)pvoidWjDe;
    IntersectionStatusObject_t *pstrbitAsnIntersectionStatusObject = (IntersectionStatusObject_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnIntersectionStatusObject->buf) || (WJV2_LEN_BYTE_INTERSECTIONSTATUSPBJECT != pstrbitAsnIntersectionStatusObject->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnIntersectionStatusObject->size,
                 pstrbitAsnIntersectionStatusObject->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnIntersectionStatusObject, pstrbitWjIntersectionStatusObject);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesBarrier_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesBarrier_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesBarrier *pstrbitWjLaneAttributesBarrier = (WJV2_BIT_LaneAttributesBarrier *)pvoidWjDe;
    LaneAttributes_Barrier_t *pstrbitAsnLaneAttributesBarrier = (LaneAttributes_Barrier_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesBarrier->size = WJV2_LEN_BYTE_LANEATTRIBUTESBARRIER;
    pstrbitAsnLaneAttributesBarrier->bits_unused = 8 * WJV2_LEN_BYTE_LANEATTRIBUTESBARRIER - WJV2_LEN_BITSTR_LANEATTRIBUTESBARRIER;
    pstrbitAsnLaneAttributesBarrier->buf = CALLOC(1, pstrbitAsnLaneAttributesBarrier->size);
    if (NULL == pstrbitAsnLaneAttributesBarrier->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnLaneAttributesBarrier, pstrbitWjLaneAttributesBarrier);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesBarrier_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesBarrier_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesBarrier *pstrbitWjLaneAttributesBarrier = (WJV2_BIT_LaneAttributesBarrier *)pvoidWjDe;
    LaneAttributes_Barrier_t *pstrbitAsnLaneAttributesBarrier = (LaneAttributes_Barrier_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesBarrier->buf) || (WJV2_LEN_BYTE_LANEATTRIBUTESBARRIER != pstrbitAsnLaneAttributesBarrier->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesBarrier->size,
                 pstrbitAsnLaneAttributesBarrier->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnLaneAttributesBarrier, pstrbitWjLaneAttributesBarrier);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesBike_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesBike_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesBike *pstrbitWjLaneAttributesBike = (WJV2_BIT_LaneAttributesBike *)pvoidWjDe;
    LaneAttributes_Bike_t *pstrbitAsnLaneAttributesBike = (LaneAttributes_Bike_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesBike->size = WJV2_LEN_BYTE_LANEATTRIBUTESBIKE;
    pstrbitAsnLaneAttributesBike->bits_unused = 8 * WJV2_LEN_BYTE_LANEATTRIBUTESBIKE - WJV2_LEN_BITSTR_LANEATTRIBUTESBIKE;
    pstrbitAsnLaneAttributesBike->buf = CALLOC(1, pstrbitAsnLaneAttributesBike->size);
    if (NULL == pstrbitAsnLaneAttributesBike->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnLaneAttributesBike, pstrbitWjLaneAttributesBike);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesBike_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesBike_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesBike *pstrbitWjLaneAttributesBike = (WJV2_BIT_LaneAttributesBike *)pvoidWjDe;
    LaneAttributes_Bike_t *pstrbitAsnLaneAttributesBike = (LaneAttributes_Bike_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesBike->buf) || (WJV2_LEN_BYTE_LANEATTRIBUTESBIKE != pstrbitAsnLaneAttributesBike->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesBike->size,
                 pstrbitAsnLaneAttributesBike->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnLaneAttributesBike, pstrbitWjLaneAttributesBike);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesCrosswalk_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesCrosswalk_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesCrosswalk *pstrbitWjLaneAttributesCrosswalk = (WJV2_BIT_LaneAttributesCrosswalk *)pvoidWjDe;
    LaneAttributes_Crosswalk_t *pstrbitAsnLaneAttributesCrosswalk = (LaneAttributes_Crosswalk_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesCrosswalk->size = WJV2_LEN_BYTE_LANEATTRIBUTESCROSSWALK;
    pstrbitAsnLaneAttributesCrosswalk->bits_unused = 8 * WJV2_LEN_BYTE_LANEATTRIBUTESCROSSWALK - WJV2_LEN_BITSTR_LANEATTRIBUTESCROSSWALK;
    pstrbitAsnLaneAttributesCrosswalk->buf = CALLOC(1, pstrbitAsnLaneAttributesCrosswalk->size);
    if (NULL == pstrbitAsnLaneAttributesCrosswalk->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnLaneAttributesCrosswalk, pstrbitWjLaneAttributesCrosswalk);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesCrosswalk_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesCrosswalk_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesCrosswalk *pstrbitWjLaneAttributesCrosswalk = (WJV2_BIT_LaneAttributesCrosswalk *)pvoidWjDe;
    LaneAttributes_Crosswalk_t *pstrbitAsnLaneAttributesCrosswalk = (LaneAttributes_Crosswalk_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesCrosswalk->buf) || (WJV2_LEN_BYTE_LANEATTRIBUTESCROSSWALK != pstrbitAsnLaneAttributesCrosswalk->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesCrosswalk->size,
                 pstrbitAsnLaneAttributesCrosswalk->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnLaneAttributesCrosswalk, pstrbitWjLaneAttributesCrosswalk);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesParking_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesParking_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesParking *pstrbitWjLaneAttributesParking = (WJV2_BIT_LaneAttributesParking *)pvoidWjDe;
    LaneAttributes_Parking_t *pstrbitAsnLaneAttributesParking = (LaneAttributes_Parking_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesParking->size = WJV2_LEN_BYTE_LANEATTRIBUTESPARKING;
    pstrbitAsnLaneAttributesParking->bits_unused = 8 * WJV2_LEN_BYTE_LANEATTRIBUTESPARKING - WJV2_LEN_BITSTR_LANEATTRIBUTESPARKING;
    pstrbitAsnLaneAttributesParking->buf = CALLOC(1, pstrbitAsnLaneAttributesParking->size);
    if (NULL == pstrbitAsnLaneAttributesParking->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnLaneAttributesParking, pstrbitWjLaneAttributesParking);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesParking_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesParking_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesParking *pstrbitWjLaneAttributesParking = (WJV2_BIT_LaneAttributesParking *)pvoidWjDe;
    LaneAttributes_Parking_t *pstrbitAsnLaneAttributesParking = (LaneAttributes_Parking_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesParking->buf) || (WJV2_LEN_BYTE_LANEATTRIBUTESPARKING != pstrbitAsnLaneAttributesParking->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesParking->size,
                 pstrbitAsnLaneAttributesParking->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnLaneAttributesParking, pstrbitWjLaneAttributesParking);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesSidewalk_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesSidewalk_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesSidewalk *pstrbitWjLaneAttributesSidewalk = (WJV2_BIT_LaneAttributesSidewalk *)pvoidWjDe;
    LaneAttributes_Sidewalk_t *pstrbitAsnLaneAttributesSidewalk = (LaneAttributes_Sidewalk_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesSidewalk->size = WJV2_LEN_BYTE_LANEATTRIBUTESSIDEWALK;
    pstrbitAsnLaneAttributesSidewalk->bits_unused = 8 * WJV2_LEN_BYTE_LANEATTRIBUTESSIDEWALK - WJV2_LEN_BITSTR_LANEATTRIBUTESSIDEWALK;
    pstrbitAsnLaneAttributesSidewalk->buf = CALLOC(1, pstrbitAsnLaneAttributesSidewalk->size);
    if (NULL == pstrbitAsnLaneAttributesSidewalk->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }

    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnLaneAttributesSidewalk, pstrbitWjLaneAttributesSidewalk);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesSidewalk_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesSidewalk_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesSidewalk *pstrbitWjLaneAttributesSidewalk = (WJV2_BIT_LaneAttributesSidewalk *)pvoidWjDe;
    LaneAttributes_Sidewalk_t *pstrbitAsnLaneAttributesSidewalk = (LaneAttributes_Sidewalk_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesSidewalk->buf) || (WJV2_LEN_BYTE_LANEATTRIBUTESSIDEWALK != pstrbitAsnLaneAttributesSidewalk->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesSidewalk->size,
                 pstrbitAsnLaneAttributesSidewalk->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnLaneAttributesSidewalk, pstrbitWjLaneAttributesSidewalk);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesStriping_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesStriping_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesStriping *pstrbitWjLaneAttributesStriping = (WJV2_BIT_LaneAttributesStriping *)pvoidWjDe;
    LaneAttributes_Striping_t *pstrbitAsnLaneAttributesStriping = (LaneAttributes_Striping_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesStriping->size = WJV2_LEN_BYTE_LANEATTRIBUTESSTRIPING;
    pstrbitAsnLaneAttributesStriping->bits_unused = 8 * WJV2_LEN_BYTE_LANEATTRIBUTESSTRIPING - WJV2_LEN_BITSTR_LANEATTRIBUTESSTRIPING;
    pstrbitAsnLaneAttributesStriping->buf = CALLOC(1, pstrbitAsnLaneAttributesStriping->size);
    if (NULL == pstrbitAsnLaneAttributesStriping->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnLaneAttributesStriping, pstrbitWjLaneAttributesStriping);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesStriping_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesStriping_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesStriping *pstrbitWjLaneAttributesStriping = (WJV2_BIT_LaneAttributesStriping *)pvoidWjDe;
    LaneAttributes_Striping_t *pstrbitAsnLaneAttributesStriping = (LaneAttributes_Striping_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesStriping->buf) || (WJV2_LEN_BYTE_LANEATTRIBUTESSTRIPING != pstrbitAsnLaneAttributesStriping->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesStriping->size,
                 pstrbitAsnLaneAttributesStriping->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnLaneAttributesStriping, pstrbitWjLaneAttributesStriping);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesTrackedVehicle_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesTrackedVehicle_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesTrackedVehicle *pstrbitWjLaneAttributesTrackedVehicle = (WJV2_BIT_LaneAttributesTrackedVehicle *)pvoidWjDe;
    LaneAttributes_TrackedVehicle_t *pstrbitAsnLaneAttributesTrackedVehicle = (LaneAttributes_TrackedVehicle_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesTrackedVehicle->size = WJV2_LEN_BYTE_LANEATTRIBUTESTRACKEDVEHICLE;
    pstrbitAsnLaneAttributesTrackedVehicle->bits_unused = 8 * WJV2_LEN_BYTE_LANEATTRIBUTESTRACKEDVEHICLE - WJV2_LEN_BITSTR_LANEATTRIBUTESTRACKEDVEHICLE;
    pstrbitAsnLaneAttributesTrackedVehicle->buf = CALLOC(1, pstrbitAsnLaneAttributesTrackedVehicle->size);
    if (NULL == pstrbitAsnLaneAttributesTrackedVehicle->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnLaneAttributesTrackedVehicle, pstrbitWjLaneAttributesTrackedVehicle);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesTrackedVehicle_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesTrackedVehicle_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesTrackedVehicle *pstrbitWjLaneAttributesTrackedVehicle = (WJV2_BIT_LaneAttributesTrackedVehicle *)pvoidWjDe;
    LaneAttributes_TrackedVehicle_t *pstrbitAsnLaneAttributesTrackedVehicle = (LaneAttributes_TrackedVehicle_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesTrackedVehicle->buf) || (WJV2_LEN_BYTE_LANEATTRIBUTESTRACKEDVEHICLE != pstrbitAsnLaneAttributesTrackedVehicle->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesTrackedVehicle->size,
                 pstrbitAsnLaneAttributesTrackedVehicle->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnLaneAttributesTrackedVehicle, pstrbitWjLaneAttributesTrackedVehicle);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesVehicle_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesVehicle_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesVehicle *pstrbitWjLaneAttributesVehicle = (WJV2_BIT_LaneAttributesVehicle *)pvoidWjDe;
    LaneAttributes_Vehicle_t *pstrbitAsnLaneAttributesVehicle = (LaneAttributes_Vehicle_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesVehicle->size = WJV2_LEN_BYTE_LANEATTRIBUTESVEHICLE;
    pstrbitAsnLaneAttributesVehicle->bits_unused = 8 * WJV2_LEN_BYTE_LANEATTRIBUTESVEHICLE - WJV2_LEN_BITSTR_LANEATTRIBUTESVEHICLE;
    pstrbitAsnLaneAttributesVehicle->buf = CALLOC(1, pstrbitAsnLaneAttributesVehicle->size);
    if (NULL == pstrbitAsnLaneAttributesVehicle->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnLaneAttributesVehicle, pstrbitWjLaneAttributesVehicle);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneAttributesVehicle_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneAttributesVehicle_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneAttributesVehicle *pstrbitWjLaneAttributesVehicle = (WJV2_BIT_LaneAttributesVehicle *)pvoidWjDe;
    LaneAttributes_Vehicle_t *pstrbitAsnLaneAttributesVehicle = (LaneAttributes_Vehicle_t *)pvoidAsnDe;
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnLaneAttributesVehicle, pstrbitWjLaneAttributesVehicle);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_LaneSharing_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneSharing_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneSharing *pstrbitWjLaneSharing = (WJV2_BIT_LaneSharing *)pvoidWjDe;
    LaneSharing_t *pstrbitAsnLaneSharing = (LaneSharing_t *)pvoidAsnDe;

    pstrbitAsnLaneSharing->size = WJV2_LEN_BYTE_LANESHARING;
    pstrbitAsnLaneSharing->bits_unused = 8 * WJV2_LEN_BYTE_LANESHARING - WJV2_LEN_BITSTR_LANESHARING;
    pstrbitAsnLaneSharing->buf = CALLOC(1, pstrbitAsnLaneSharing->size);
    if (NULL == pstrbitAsnLaneSharing->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnLaneSharing, pstrbitWjLaneSharing);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_LaneSharing_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_LaneSharing_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_LaneSharing *pstrbitWjLaneSharing = (WJV2_BIT_LaneSharing *)pvoidWjDe;
    LaneSharing_t *pstrbitAsnLaneSharing = (LaneSharing_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneSharing->buf) || (WJV2_LEN_BYTE_LANESHARING != pstrbitAsnLaneSharing->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneSharing->size,
                 pstrbitAsnLaneSharing->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnLaneSharing, pstrbitWjLaneSharing);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_ReferenceLanes_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_ReferenceLanes_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_ReferenceLanes *pstrbitWjReferenceLanes = (WJV2_BIT_ReferenceLanes *)pvoidWjDe;
    ReferenceLanes_t *pstrbitAsnReferenceLanes = (ReferenceLanes_t *)pvoidAsnDe;

    pstrbitAsnReferenceLanes->size = WJV2_LEN_BYTE_REFERENCELANES;
    pstrbitAsnReferenceLanes->bits_unused = 8 * WJV2_LEN_BYTE_REFERENCELANES - WJV2_LEN_BITSTR_REFERENCELANES;
    pstrbitAsnReferenceLanes->buf = CALLOC(1, pstrbitAsnReferenceLanes->size);
    if (NULL == pstrbitAsnReferenceLanes->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnReferenceLanes, pstrbitWjReferenceLanes);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_ReferenceLanes_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_ReferenceLanes_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_ReferenceLanes *pstrbitWjReferenceLanes = (WJV2_BIT_ReferenceLanes *)pvoidWjDe;
    ReferenceLanes_t *pstrbitAsnReferenceLanes = (ReferenceLanes_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnReferenceLanes->buf) || (WJV2_LEN_BYTE_REFERENCELANES != pstrbitAsnReferenceLanes->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnReferenceLanes->size,
                 pstrbitAsnReferenceLanes->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnReferenceLanes, pstrbitWjReferenceLanes);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_RSIPriority_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_RSIPriority_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_IA5_RSIPriority *pstria5WjRSIPriority = (WJV2_IA5_RSIPriority *)pvoidWjDe;
    RSIPriority_t *pstria5AsnRSIPriority = (RSIPriority_t *)pvoidAsnDe;
    if (0 != pstria5WjRSIPriority->u8RSIPriorityNum)
    {
        if ((WJV2_MAX_IA5_RSIPRIORITY_LEN < pstria5WjRSIPriority->u8RSIPriorityNum) || (0 > pstria5WjRSIPriority->u8RSIPriorityNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "out of rangth:pstria5WjRSIPriority->u8RSIPriorityNum = %d",
                     pstria5WjRSIPriority->u8RSIPriorityNum);
            return false;
        }
        pstria5AsnRSIPriority->buf = CALLOC(1, pstria5AsnRSIPriority->size);
        if (NULL == pstria5AsnRSIPriority->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "calloc is err");
            return false;
        }
        pstria5AsnRSIPriority->size = pstria5WjRSIPriority->u8RSIPriorityNum;
        memcpy(pstria5AsnRSIPriority->buf, pstria5WjRSIPriority->u8RSIPriority, pstria5AsnRSIPriority->size);
    }
    else
    {
        pstria5AsnRSIPriority->size = 0;
        pstria5AsnRSIPriority->buf = NULL;
    }
    return true;
}
/**
* @brief     WJV2_RSIPriority_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_RSIPriority_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_IA5_RSIPriority *pstria5WjRSIPriority = (WJV2_IA5_RSIPriority *)pvoidWjDe;
    RSIPriority_t *pstria5AsnRSIPriority = (RSIPriority_t *)pvoidAsnDe;
    if (0 < pstria5AsnRSIPriority->size)
    {
        if ((WJV2_MAX_IA5_RSIPRIORITY_LEN < pstria5AsnRSIPriority->size) || (0 > pstria5AsnRSIPriority->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "out of rangth:pstria5AsnRSIPriority->size = %d",
                     pstria5AsnRSIPriority->size);
            return false;
        }
        if (NULL == pstria5AsnRSIPriority->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "buf is null:pstria5AsnRSIPriority->buf = %p",
                     pstria5AsnRSIPriority->buf);
            return false;
        }
        pstria5WjRSIPriority->u8RSIPriorityNum = pstria5AsnRSIPriority->size;
        memcpy(pstria5WjRSIPriority->u8RSIPriority, pstria5AsnRSIPriority->buf, pstria5AsnRSIPriority->size);
    }
    else
    {
        pstria5WjRSIPriority->u8RSIPriorityNum = 0;
    }
    return true;
}
/**
* @brief     WJV2_VehicleEventFlags_DeEnc编码函数
* @details   协议栈De编解码中 统一De的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_VehicleEventFlags_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_VehicleEventFlags *pstrbitWjVehicleEventFlags = (WJV2_BIT_VehicleEventFlags *)pvoidWjDe;
    VehicleEventFlags_t *pstrbitAsnVehicleEventFlags = (VehicleEventFlags_t *)pvoidAsnDe;

    pstrbitAsnVehicleEventFlags->size = WJV2_LEN_BYTE_VEHICLEEVENTFLAGS;
    pstrbitAsnVehicleEventFlags->bits_unused = 8 * WJV2_LEN_BYTE_VEHICLEEVENTFLAGS - WJV2_LEN_BITSTR_VEHICLEEVENTFLAGS;
    pstrbitAsnVehicleEventFlags->buf = CALLOC(1, pstrbitAsnVehicleEventFlags->size);
    if (NULL == pstrbitAsnVehicleEventFlags->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnVehicleEventFlags, pstrbitWjVehicleEventFlags);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_VehicleEventFlags_DeDec解码函数
* @details   协议栈De编解码中 统一De的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
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
int32_t WJV2_VehicleEventFlags_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_VehicleEventFlags *pstrbitWjVehicleEventFlags = (WJV2_BIT_VehicleEventFlags *)pvoidWjDe;
    VehicleEventFlags_t *pstrbitAsnVehicleEventFlags = (VehicleEventFlags_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnVehicleEventFlags->buf) || (WJV2_LEN_BYTE_VEHICLEEVENTFLAGS != pstrbitAsnVehicleEventFlags->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnVehicleEventFlags->size,
                 pstrbitAsnVehicleEventFlags->buf);
        return false;
    }
    int n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnVehicleEventFlags, pstrbitWjVehicleEventFlags);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/* 文件结束标志 */

/**
* @brief     WJV2_ApduList_DeEnc编码函数
* @details   协议栈ApduList编解码中 统一ApduList的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_ApduList_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_STRU_ApduList *pstrbitWjApduList = (WJV2_STRU_ApduList *)pvoidWjDe;
    ApduList_t *pstrbitAsnApduList = (ApduList_t *)pvoidAsnDe;
    OCTET_STRING_t *pstruOctetString_node = NULL;
    int32_t u32i = 0;
    if ((WJV2_MAX_LIST_APDULIST_LEN < pstrbitWjApduList->u8ApduDataNum) || (WJV2_MIN_LIST_APDULIST_LEN > pstrbitWjApduList->u8ApduDataNum))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstrbitWjApduList->u8ApduDataNum = %d",
                 pstrbitWjApduList->u8ApduDataNum);
        return false;
    }

    for (u32i = 0; u32i < pstrbitWjApduList->u8ApduDataNum; u32i++)
    {
        pstruOctetString_node = CALLOC(1, sizeof(OCTET_STRING_t));
        if (NULL == pstruOctetString_node)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        pstruOctetString_node->size = pstrbitWjApduList->struApduData[u32i].u8OCTidNum;
        pstruOctetString_node->buf = CALLOC(1, pstruOctetString_node->size);
        if (NULL == pstruOctetString_node->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "CALLOC is err");
            return false;
        }
        memcpy(pstruOctetString_node->buf, pstrbitWjApduList->struApduData[u32i].u8OCTid, pstruOctetString_node->size);
        asn_sequence_add(&(pstrbitAsnApduList->list), pstruOctetString_node);
    }
    pstrbitAsnApduList->list.count = pstrbitWjApduList->u8ApduDataNum;

    return true;
}
/**
* @brief     WJV2_ApduList_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_ApduList_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_STRU_ApduList *pstrbitWjApduList = (WJV2_STRU_ApduList *)pvoidWjDe;
    ApduList_t *pstrbitAsnApduList = (ApduList_t *)pvoidAsnDe;
    uint32_t u32i = 0;
    if ((WJV2_MAX_LIST_APDULIST_LEN < pstrbitAsnApduList->list.count) || (WJV2_MIN_LIST_APDULIST_LEN > pstrbitAsnApduList->list.count))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DF_MODULE,
                 "out of rangth:pstrbitAsnApduList->list.count = %d",
                 pstrbitAsnApduList->list.count);
        return false;
    }
    for (u32i = 0; u32i < pstrbitAsnApduList->list.count; u32i++)
    {
        if (NULL == pstrbitAsnApduList->list.array[u32i]->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DF_MODULE,
                     "out of rangth:pstrbitAsnApduList->list.array[u32i]->buf = NULL");
            return false;
        }
        pstrbitWjApduList->struApduData[u32i].u8OCTidNum = pstrbitAsnApduList->list.array[u32i]->size;
        memcpy(pstrbitWjApduList->struApduData[u32i].u8OCTid, pstrbitAsnApduList->list.array[u32i]->buf, pstrbitAsnApduList->list.array[u32i]->size);
    }
    pstrbitWjApduList->u8ApduDataNum = (uint8_t)u32i;

    return true;
}
/**
* @brief     WJV2_AuxiliarySignVehicleType_DeEnc编码函数
* @details   协议栈AuxiliarySignVehicleType编解码中 统一AuxiliarySignVehicleType的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_AuxiliarySignVehicleType_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_AuxiliarySignVehicleType *pstrbitWjAuxiliarySignVehicleType = (WJV2_BIT_AuxiliarySignVehicleType *)pvoidWjDe;
    AuxiliarySignVehicleType_t *pstrbitAsnAuxiliarySignVehicleType = (AuxiliarySignVehicleType_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    pstrbitAsnAuxiliarySignVehicleType->size = WJV2_LEN_BYTE_AuxiliarySignVehicleType;
    pstrbitAsnAuxiliarySignVehicleType->bits_unused = (8 * WJV2_LEN_BYTE_AuxiliarySignVehicleType) - WJV2_LEN_BITSTR_AuxiliarySignVehicleType;
    pstrbitAsnAuxiliarySignVehicleType->buf = CALLOC(1, pstrbitAsnAuxiliarySignVehicleType->size);
    if (NULL == pstrbitAsnAuxiliarySignVehicleType->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnAuxiliarySignVehicleType, pstrbitWjAuxiliarySignVehicleType);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_AuxiliarySignVehicleType_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_AuxiliarySignVehicleType_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_AuxiliarySignVehicleType *pstrbitWjAuxiliarySignVehicleType = (WJV2_BIT_AuxiliarySignVehicleType *)pvoidWjDe;
    AuxiliarySignVehicleType_t *pstrbitAsnAuxiliarySignVehicleType = (AuxiliarySignVehicleType_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    if ((NULL == pstrbitAsnAuxiliarySignVehicleType->buf) ||
        (WJV2_LEN_BYTE_AuxiliarySignVehicleType != pstrbitAsnAuxiliarySignVehicleType->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnAuxiliarySignVehicleType->size,
                 pstrbitAsnAuxiliarySignVehicleType->buf);
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnAuxiliarySignVehicleType, pstrbitWjAuxiliarySignVehicleType);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_CoordinationInfo_DeEnc编码函数
* @details   协议栈CoordinationInfo编解码中 统一CoordinationInfo的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_CoordinationInfo_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_CoordinationInfo *pstrbitWjCoordinationInfo = (WJV2_BIT_CoordinationInfo *)pvoidWjDe;
    CoordinationInfo_t *pstrbitAsnCoordinationInfo = (CoordinationInfo_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    pstrbitAsnCoordinationInfo->size = WJV2_LEN_BYTE_CoordinationInfo;
    pstrbitAsnCoordinationInfo->bits_unused = (8 * WJV2_LEN_BYTE_CoordinationInfo) - WJV2_LEN_BITSTR_CoordinationInfo;
    pstrbitAsnCoordinationInfo->buf = CALLOC(1, pstrbitAsnCoordinationInfo->size);
    if (NULL == pstrbitAsnCoordinationInfo->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnCoordinationInfo, pstrbitWjCoordinationInfo);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_CoordinationInfo_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_CoordinationInfo_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_CoordinationInfo *pstrbitWjCoordinationInfo = (WJV2_BIT_CoordinationInfo *)pvoidWjDe;
    CoordinationInfo_t *pstrbitAsnCoordinationInfo = (CoordinationInfo_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    if ((NULL == pstrbitAsnCoordinationInfo->buf) ||
        (WJV2_LEN_BYTE_CoordinationInfo != pstrbitAsnCoordinationInfo->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnCoordinationInfo->size,
                 pstrbitAsnCoordinationInfo->buf);
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnCoordinationInfo, pstrbitWjCoordinationInfo);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_DriveBehavior_DeEnc编码函数
* @details   协议栈DriveBehavior编解码中 统一DriveBehavior的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_DriveBehavior_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_DriveBehavior *pstrbitWjDriveBehavior = (WJV2_BIT_DriveBehavior *)pvoidWjDe;
    DriveBehavior_t *pstrbitAsnDriveBehavior = (DriveBehavior_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    pstrbitAsnDriveBehavior->size = WJV2_LEN_BYTE_DriveBehavior;
    pstrbitAsnDriveBehavior->bits_unused = (8 * WJV2_LEN_BYTE_DriveBehavior) - WJV2_LEN_BITSTR_DriveBehavior;
    pstrbitAsnDriveBehavior->buf = CALLOC(1, pstrbitAsnDriveBehavior->size);
    if (NULL == pstrbitAsnDriveBehavior->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnDriveBehavior, pstrbitWjDriveBehavior);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_DriveBehavior_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_DriveBehavior_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_DriveBehavior *pstrbitWjDriveBehavior = (WJV2_BIT_DriveBehavior *)pvoidWjDe;
    DriveBehavior_t *pstrbitAsnDriveBehavior = (DriveBehavior_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    if ((NULL == pstrbitAsnDriveBehavior->buf) ||
        (WJV2_LEN_BYTE_DriveBehavior != pstrbitAsnDriveBehavior->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnDriveBehavior->size,
                 pstrbitAsnDriveBehavior->buf);
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnDriveBehavior, pstrbitWjDriveBehavior);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_File_DeEnc编码函数
* @details   协议栈File编解码中 统一File的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_File_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_OCT_FileData *pstrbitWjFileData = (WJV2_OCT_FileData *)pvoidWjDe;
    File_t *pstrbitAsnFileData = (File_t *)pvoidAsnDe;
    if (0 != pstrbitWjFileData->u8OCTidNum)
    {
        if ((WJV2_MAX_OCTFileID_SIZE < pstrbitWjFileData->u8OCTidNum) || (0 > pstrbitWjFileData->u8OCTidNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "out of rangth:pstrbitWjFileData->u8OCTidNum = %d",
                     pstrbitWjFileData->u8OCTidNum);
            return false;
        }
        pstrbitAsnFileData->buf = CALLOC(1, pstrbitWjFileData->u8OCTidNum);
        if (NULL == pstrbitAsnFileData->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "calloc is err");
            return false;
        }
        pstrbitAsnFileData->size = pstrbitWjFileData->u8OCTidNum;
        memcpy(pstrbitAsnFileData->buf, pstrbitWjFileData->u8OCTid, pstrbitAsnFileData->size);
    }

    return true;
}
/**
* @brief     WJV2_File_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_File_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_OCT_FileData *pstrbitWjFileData = (WJV2_OCT_FileData *)pvoidWjDe;
    File_t *pstrbitAsnFileData = (File_t *)pvoidAsnDe;
    if (0 != pstrbitAsnFileData->size)
    {
        if ((WJV2_MAX_OCTFileID_SIZE < pstrbitAsnFileData->size) || (0 > pstrbitAsnFileData->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "out of rangth:pstrbitAsnFileData->size = %d",
                     pstrbitAsnFileData->size);
            return false;
        }
        if (NULL == pstrbitWjFileData->u8OCTid)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "pstrbitWjFileData->u8OCTid is null");
            return false;
        }
        pstrbitWjFileData->u8OCTidNum = pstrbitAsnFileData->size;
        memcpy(pstrbitWjFileData->u8OCTid, pstrbitAsnFileData->buf, pstrbitAsnFileData->size);
    }

    return true;
}

/**
* @brief     WJV2_ParkingRequest_DeEnc编码函数
* @details   协议栈ParkingRequest编解码中 统一ParkingRequest的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_ParkingRequest_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_ParkingRequest *pstrbitWjParkingRequest = (WJV2_BIT_ParkingRequest *)pvoidWjDe;
    ParkingRequest_t *pstrbitAsnParkingRequest = (ParkingRequest_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    pstrbitAsnParkingRequest->size = WJV2_LEN_BYTE_ParkingRequest;
    pstrbitAsnParkingRequest->bits_unused = (8 * WJV2_LEN_BYTE_ParkingRequest) - WJV2_LEN_BITSTR_ParkingRequest;
    pstrbitAsnParkingRequest->buf = CALLOC(1, pstrbitAsnParkingRequest->size);
    if (NULL == pstrbitAsnParkingRequest->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnParkingRequest, pstrbitWjParkingRequest);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_ParkingRequest_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_ParkingRequest_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_ParkingRequest *pstrbitWjParkingRequest = (WJV2_BIT_ParkingRequest *)pvoidWjDe;
    ParkingRequest_t *pstrbitAsnParkingRequest = (ParkingRequest_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    if ((NULL == pstrbitAsnParkingRequest->buf) ||
        (WJV2_LEN_BYTE_ParkingRequest != pstrbitAsnParkingRequest->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnParkingRequest->size,
                 pstrbitAsnParkingRequest->buf);
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnParkingRequest, pstrbitWjParkingRequest);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_ParkingType_DeEnc编码函数
* @details   协议栈ParkingType编解码中 统一ParkingType的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_ParkingType_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_ParkingType *pstrbitWjParkingType = (WJV2_BIT_ParkingType *)pvoidWjDe;
    ParkingType_t *pstrbitAsnParkingType = (ParkingType_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    pstrbitAsnParkingType->size = WJV2_LEN_BYTE_ParkingType;
    pstrbitAsnParkingType->bits_unused = (8 * WJV2_LEN_BYTE_ParkingType) - WJV2_LEN_BITSTR_ParkingType;
    pstrbitAsnParkingType->buf = CALLOC(1, pstrbitAsnParkingType->size);
    if (NULL == pstrbitAsnParkingType->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnParkingType, pstrbitWjParkingType);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_ParkingType_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_ParkingType_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_ParkingType *pstrbitWjParkingType = (WJV2_BIT_ParkingType *)pvoidWjDe;
    ParkingType_t *pstrbitAsnParkingType = (ParkingType_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    if ((NULL == pstrbitAsnParkingType->buf) ||
        (WJV2_LEN_BYTE_ParkingType != pstrbitAsnParkingType->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnParkingType->size,
                 pstrbitAsnParkingType->buf);
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnParkingType, pstrbitWjParkingType);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_PAMNodeAttributes_DeEnc编码函数
* @details   协议栈PAMNodeAttributes编解码中 统一PAMNodeAttributes的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_PAMNodeAttributes_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_PAMNodeAttributes *pstrbitWjPAMNodeAttributes = (WJV2_BIT_PAMNodeAttributes *)pvoidWjDe;
    PAMNodeAttributes_t *pstrbitAsnPAMNodeAttributes = (PAMNodeAttributes_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    pstrbitAsnPAMNodeAttributes->size = WJV2_LEN_BYTE_PAMNodeAttributes;
    pstrbitAsnPAMNodeAttributes->bits_unused = (8 * WJV2_LEN_BYTE_PAMNodeAttributes) - WJV2_LEN_BITSTR_PAMNodeAttributes;
    pstrbitAsnPAMNodeAttributes->buf = CALLOC(1, pstrbitAsnPAMNodeAttributes->size);
    if (NULL == pstrbitAsnPAMNodeAttributes->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnPAMNodeAttributes, pstrbitWjPAMNodeAttributes);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV2_PAMNodeAttributes_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_PAMNodeAttributes_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_PAMNodeAttributes *pstrbitWjPAMNodeAttributes = (WJV2_BIT_PAMNodeAttributes *)pvoidWjDe;
    PAMNodeAttributes_t *pstrbitAsnPAMNodeAttributes = (PAMNodeAttributes_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    if ((NULL == pstrbitAsnPAMNodeAttributes->buf) ||
        (WJV2_LEN_BYTE_PAMNodeAttributes != pstrbitAsnPAMNodeAttributes->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnPAMNodeAttributes->size,
                 pstrbitAsnPAMNodeAttributes->buf);
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnPAMNodeAttributes, pstrbitWjPAMNodeAttributes);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_PersonalDeviceUsageState_DeEnc编码函数
* @details   协议栈PersonalDeviceUsageState编解码中 统一PersonalDeviceUsageState的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_PersonalDeviceUsageState_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_PersonalDeviceUsageState *pstrbitWjPersonalDeviceUsageState = (WJV2_BIT_PersonalDeviceUsageState *)pvoidWjDe;
    PersonalDeviceUsageState_t *pstrbitAsnPersonalDeviceUsageState = (PersonalDeviceUsageState_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    pstrbitAsnPersonalDeviceUsageState->size = WJV2_LEN_BYTE_PersonalDeviceUsageState;
    pstrbitAsnPersonalDeviceUsageState->bits_unused = (8 * WJV2_LEN_BYTE_PersonalDeviceUsageState) - WJV2_LEN_BITSTR_PersonalDeviceUsageState;
    pstrbitAsnPersonalDeviceUsageState->buf = CALLOC(1, pstrbitAsnPersonalDeviceUsageState->size);
    if (NULL == pstrbitAsnPersonalDeviceUsageState->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnPersonalDeviceUsageState, pstrbitWjPersonalDeviceUsageState);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_PersonalDeviceUsageState_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_PersonalDeviceUsageState_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_PersonalDeviceUsageState *pstrbitWjPersonalDeviceUsageState = (WJV2_BIT_PersonalDeviceUsageState *)pvoidWjDe;
    PersonalDeviceUsageState_t *pstrbitAsnPersonalDeviceUsageState = (PersonalDeviceUsageState_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    if ((NULL == pstrbitAsnPersonalDeviceUsageState->buf) ||
        (WJV2_LEN_BYTE_PersonalDeviceUsageState != pstrbitAsnPersonalDeviceUsageState->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnPersonalDeviceUsageState->size,
                 pstrbitAsnPersonalDeviceUsageState->buf);
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnPersonalDeviceUsageState, pstrbitWjPersonalDeviceUsageState);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_PersonalAssistive_DeEnc编码函数
* @details   协议栈PersonalAssistive编解码中 统一PersonalAssistive的编码函数入口
* @param   [in]   void * pvoidAsnDf  编码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-08  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_PersonalAssistive_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_PersonalAssistive *pstrbitWjPersonalAssistive = (WJV2_BIT_PersonalAssistive *)pvoidWjDe;
    PersonalAssistive_t *pstrbitAsnPersonalAssistive = (PersonalAssistive_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    pstrbitAsnPersonalAssistive->size = WJV2_LEN_BYTE_PersonalAssistive;
    pstrbitAsnPersonalAssistive->bits_unused = (8 * WJV2_LEN_BYTE_PersonalAssistive) - WJV2_LEN_BITSTR_PersonalAssistive;
    pstrbitAsnPersonalAssistive->buf = CALLOC(1, pstrbitAsnPersonalAssistive->size);
    if (NULL == pstrbitAsnPersonalAssistive->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnPersonalAssistive, pstrbitWjPersonalAssistive);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_PersonalAssistive_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDf  解码结构
* @param   [in]   void * pvoidWjDf   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-08  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_PersonalAssistive_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDf = %p pvoidWjDf = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_PersonalAssistive *pstrbitWjPersonalAssistive = (WJV2_BIT_PersonalAssistive *)pvoidWjDe;
    PersonalAssistive_t *pstrbitAsnPersonalAssistive = (PersonalAssistive_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    if ((NULL == pstrbitAsnPersonalAssistive->buf) ||
        (WJV2_LEN_BYTE_PersonalAssistive != pstrbitAsnPersonalAssistive->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnPersonalAssistive->size,
                 pstrbitAsnPersonalAssistive->buf);
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnPersonalAssistive, pstrbitWjPersonalAssistive);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_RandStr8_DeEnc编码函数
* @details   协议栈RandStr8编解码中 统一RandStr8的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_RandStr8_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_OCT_RandStr8Data *pstrbitWjRandStr8 = (WJV2_OCT_RandStr8Data *)pvoidWjDe;
    RandStr8_t *pstrbitAsnRandStr8 = (RandStr8_t *)pvoidAsnDe;
    if (0 != pstrbitWjRandStr8->u8OCTRandStr8Num)
    {
        if ((WJV2_MAX_OCTRandStr8_SIZE < pstrbitWjRandStr8->u8OCTRandStr8Num) || (0 > pstrbitWjRandStr8->u8OCTRandStr8Num))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "out of rangth:pstrbitWjRandStr8->u8OCTRandStr8Num = %d",
                     pstrbitWjRandStr8->u8OCTRandStr8Num);
            return false;
        }
        pstrbitAsnRandStr8->buf = CALLOC(1, pstrbitWjRandStr8->u8OCTRandStr8Num);
        if (NULL == pstrbitAsnRandStr8->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "calloc is err");
            return false;
        }
        pstrbitAsnRandStr8->size = pstrbitWjRandStr8->u8OCTRandStr8Num;
        memcpy(pstrbitAsnRandStr8->buf, pstrbitWjRandStr8->u8OCTRandStr8, pstrbitAsnRandStr8->size);
    }

    return true;
}
/**
* @brief     WJV2_RandStr8_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_RandStr8_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_OCT_RandStr8Data *pstrbitWjRandStr8 = (WJV2_OCT_RandStr8Data *)pvoidWjDe;
    RandStr8_t *pstrbitAsnRandStr8 = (RandStr8_t *)pvoidAsnDe;
    if (0 != pstrbitAsnRandStr8->size)
    {
        if ((WJV2_MAX_OCTRandStr8_SIZE < pstrbitAsnRandStr8->size) || (0 > pstrbitAsnRandStr8->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "out of rangth:pstrbitAsnRandStr8->size = %d",
                     pstrbitAsnRandStr8->size);
            return false;
        }
        if (NULL == pstrbitWjRandStr8->u8OCTRandStr8)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "pstrbitWjRandStr8->u8OCTRandStr8 is null");
            return false;
        }
        pstrbitWjRandStr8->u8OCTRandStr8Num = pstrbitAsnRandStr8->size;
        memcpy(pstrbitWjRandStr8->u8OCTRandStr8, pstrbitAsnRandStr8->buf, pstrbitAsnRandStr8->size);
    }

    return true;
}
/**
* @brief     WJV2_RoadWorkerActivityType_DeEnc编码函数
* @details   协议栈RoadWorkerActivityType编解码中 统一RoadWorkerActivityType的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_RoadWorkerActivityType_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_RoadWorkerActivityType *pstrbitWjRoadWorkerActivityType = (WJV2_BIT_RoadWorkerActivityType *)pvoidWjDe;
    RoadWorkerActivityType_t *pstrbitAsnRoadWorkerActivityType = (RoadWorkerActivityType_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    pstrbitAsnRoadWorkerActivityType->size = WJV2_LEN_BYTE_RoadWorkerActivityType;
    pstrbitAsnRoadWorkerActivityType->bits_unused = (8 * WJV2_LEN_BYTE_RoadWorkerActivityType) - WJV2_LEN_BITSTR_RoadWorkerActivityType;
    pstrbitAsnRoadWorkerActivityType->buf = CALLOC(1, pstrbitAsnRoadWorkerActivityType->size);
    if (NULL == pstrbitAsnRoadWorkerActivityType->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "calloc is err");
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeEnc(pstrbitAsnRoadWorkerActivityType, pstrbitWjRoadWorkerActivityType);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_RoadWorkerActivityType_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_RoadWorkerActivityType_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_BIT_RoadWorkerActivityType *pstrbitWjRoadWorkerActivityType = (WJV2_BIT_RoadWorkerActivityType *)pvoidWjDe;
    RoadWorkerActivityType_t *pstrbitAsnRoadWorkerActivityType = (RoadWorkerActivityType_t *)pvoidAsnDe;
    int32_t n32Ret = 0;
    if ((NULL == pstrbitAsnRoadWorkerActivityType->buf) ||
        (WJV2_LEN_BYTE_RoadWorkerActivityType != pstrbitAsnRoadWorkerActivityType->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnRoadWorkerActivityType->size,
                 pstrbitAsnRoadWorkerActivityType->buf);
        return false;
    }
    n32Ret = WJV2_BITSTRING_DeDec(pstrbitAsnRoadWorkerActivityType, pstrbitWjRoadWorkerActivityType);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV2_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV2_RTCMPayload_DeEnc编码函数
* @details   协议栈RTCMPayload编解码中 统一RTCMPayload的编码函数入口
* @param   [in]   void * pvoidAsnDe  编码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_RTCMPayload_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_OCT_RTCM_PayloadData *pstrbitWjRTCMPayload = (WJV2_OCT_RTCM_PayloadData *)pvoidWjDe;
    RTCM_Payload_t *pstrbitAsnRTCMPayload = (RTCM_Payload_t *)pvoidAsnDe;
    if (0 != pstrbitWjRTCMPayload->u16OCTRTCMPayloadNum)
    {
        if ((WJV2_MAX_OCTRTCMPayload_SIZE < pstrbitWjRTCMPayload->u16OCTRTCMPayloadNum) ||
            (WJV2_MIN_OCTRTCMPayload_SIZE > pstrbitWjRTCMPayload->u16OCTRTCMPayloadNum))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "out of rangth:pstrbitWjRTCMPayload->u16OCTRTCMPayloadNum = %d",
                     pstrbitWjRTCMPayload->u16OCTRTCMPayloadNum);
            return false;
        }
        pstrbitAsnRTCMPayload->buf = CALLOC(1, pstrbitWjRTCMPayload->u16OCTRTCMPayloadNum);
        if (NULL == pstrbitAsnRTCMPayload->buf)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "calloc is err");
            return false;
        }
        pstrbitAsnRTCMPayload->size = pstrbitWjRTCMPayload->u16OCTRTCMPayloadNum;
        memcpy(pstrbitAsnRTCMPayload->buf, pstrbitWjRTCMPayload->u8OCTRTCMPayload, pstrbitAsnRTCMPayload->size);
    }

    return true;
}
/**
* @brief     WJV2_RTCMPayload_DeDec解码函数
* @details   协议栈编解码中 统一的解码函数入口
* @param   [in]   void * pvoidAsnDe  解码结构
* @param   [in]   void * pvoidWjDe   WJ结构
* @return      本函数返回执行结果
*                  若成功则返回   true
*                  否则返回      false
* @author      guofenghe
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021-01-04  <td>1.0      <td>guofenghe  <td>创建初始版本
* </table>
*/
int32_t WJV2_RTCMPayload_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV2_OCT_RTCM_PayloadData *pstrbitWjRTCMPayload = (WJV2_OCT_RTCM_PayloadData *)pvoidWjDe;
    RTCM_Payload_t *pstrbitAsnRTCMPayload = (RTCM_Payload_t *)pvoidAsnDe;
    if (0 != pstrbitAsnRTCMPayload->size)
    {
        if ((WJV2_MAX_OCTRTCMPayload_SIZE < pstrbitAsnRTCMPayload->size) || (WJV2_MIN_OCTRTCMPayload_SIZE > pstrbitAsnRTCMPayload->size))
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "out of rangth:pstrbitAsnRTCMPayload->size = %d",
                     pstrbitAsnRTCMPayload->size);
            return false;
        }
        if (NULL == pstrbitWjRTCMPayload->u8OCTRTCMPayload)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_DE_MODULE,
                     "pstrbitWjRTCMPayload->u8OCTRTCMPayload is null");
            return false;
        }
        pstrbitWjRTCMPayload->u16OCTRTCMPayloadNum = pstrbitAsnRTCMPayload->size;
        memcpy(pstrbitWjRTCMPayload->u8OCTRTCMPayload, pstrbitAsnRTCMPayload->buf, pstrbitAsnRTCMPayload->size);
    }

    return true;
}
/**
 * @brief    WJV2_BITSTRING_DeEnc数据元素解码函数
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
int32_t WJV2_BITSTRING_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
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
 * @brief    WJV2_BITSTRING_DeDec的bitstring字段解码
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
int32_t WJV2_BITSTRING_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
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
/* 文件结束标志 */
