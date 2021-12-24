/**
* @file         :wjv4_uper_De.c
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
#include "wjv4_uper_De.h"
#include "wjv4_uper_com.h"
/**
* @brief     WJV4_AllowedManeuvers_DeEnc编码函数
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
int32_t WJV4_AllowedManeuvers_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_AllowedManeuvers *pstrbitWjAllowedManeuvers = (WJV4_BIT_AllowedManeuvers *)pvoidWjDe;
    AllowedManeuvers_t *pstrbitAsnAllowedManeuvers = (AllowedManeuvers_t *)pvoidAsnDe;

    pstrbitAsnAllowedManeuvers->size = WJV4_LEN_BYTE_ALLOWEDMANEUVERS;
    pstrbitAsnAllowedManeuvers->bits_unused = 8 * WJV4_LEN_BYTE_ALLOWEDMANEUVERS - WJV4_LEN_BITSTR_ALLOWEDMANEUVERS;
    pstrbitAsnAllowedManeuvers->buf = CALLOC(1, pstrbitAsnAllowedManeuvers->size);
    if (NULL == pstrbitAsnAllowedManeuvers->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }

    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnAllowedManeuvers, pstrbitWjAllowedManeuvers);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_AllowedManeuvers_DeDec解码函数
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
int32_t WJV4_AllowedManeuvers_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_AllowedManeuvers *pstrbitWjAllowedManeuvers = (WJV4_BIT_AllowedManeuvers *)pvoidWjDe;
    AllowedManeuvers_t *pstrbitAsnAllowedManeuvers = (AllowedManeuvers_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnAllowedManeuvers->buf) || (WJV4_LEN_BYTE_ALLOWEDMANEUVERS != pstrbitAsnAllowedManeuvers->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnAllowedManeuvers->size,
                 pstrbitAsnAllowedManeuvers->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnAllowedManeuvers, pstrbitWjAllowedManeuvers);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_BrakeAppliedStatus_DeEnc编码函数
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
int32_t WJV4_BrakeAppliedStatus_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_BrakeAppliedStatus *pstrbitWjBrakeAppliedStatus = (WJV4_BIT_BrakeAppliedStatus *)pvoidWjDe;
    BrakeAppliedStatus_t *pstrbitAsnBrakeAppliedStatus = (BrakeAppliedStatus_t *)pvoidAsnDe;

    pstrbitAsnBrakeAppliedStatus->size = WJV4_LEN_BYTE_BRAFEAPPLIEDSTATUS;
    pstrbitAsnBrakeAppliedStatus->bits_unused = 8 * WJV4_LEN_BYTE_BRAFEAPPLIEDSTATUS - WJV4_LEN_BITSTR_BRAFEAPPLIEDSTATUS;
    pstrbitAsnBrakeAppliedStatus->buf = CALLOC(1, pstrbitAsnBrakeAppliedStatus->size);
    if (NULL == pstrbitAsnBrakeAppliedStatus->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnBrakeAppliedStatus, pstrbitWjBrakeAppliedStatus);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_BrakeAppliedStatus_DeDec解码函数
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
int32_t WJV4_BrakeAppliedStatus_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_BrakeAppliedStatus *pstrbitWjBrakeAppliedStatus = (WJV4_BIT_BrakeAppliedStatus *)pvoidWjDe;
    BrakeAppliedStatus_t *pstrbitAsnBrakeAppliedStatus = (BrakeAppliedStatus_t *)pvoidAsnDe;

    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnBrakeAppliedStatus, pstrbitWjBrakeAppliedStatus);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_DescriptiveName_DeEnc编码函数
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
int32_t WJV4_DescriptiveName_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_IA5_DescriptiveName *pstria5WjDescriptiveName = (WJV4_IA5_DescriptiveName *)pvoidWjDe;
    DescriptiveName_t *pstria5AsnDescriptiveName = (DescriptiveName_t *)pvoidAsnDe;
    uint32_t u32i = 0;
    if ((WJV4_MAX_IA5_DESCIPTIVENAME_LEN < pstria5WjDescriptiveName->u8DescriptiveNameNum) || (1 > pstria5WjDescriptiveName->u8DescriptiveNameNum))
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
        if ((WJV4_MAX_DESCRIPTIVENAME_SIZE < pstria5WjDescriptiveName->u8DescriptiveName[u32i]) || (WJV4_MIN_DESCRIPTIVENAME_SIZE > pstria5WjDescriptiveName->u8DescriptiveName[u32i]))
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
* @brief     WJV4_DescriptiveName_DeDec解码函数
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
int32_t WJV4_DescriptiveName_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_IA5_DescriptiveName *pstria5WjDescriptiveName = (WJV4_IA5_DescriptiveName *)pvoidWjDe;
    DescriptiveName_t *pstria5AsnDescriptiveName = (DescriptiveName_t *)pvoidAsnDe;
    if (0 < pstria5AsnDescriptiveName->size)
    {
        if ((WJV4_MAX_IA5_DESCIPTIVENAME_LEN < pstria5AsnDescriptiveName->size) || (1 > pstria5AsnDescriptiveName->size))
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
* @brief     WJV4_ExteriorLights_DeEnc编码函数
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
int32_t WJV4_ExteriorLights_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_ExteriorLights *pstrbitWjExteriorLights = (WJV4_BIT_ExteriorLights *)pvoidWjDe;
    ExteriorLights_t *pstrbitAsnExteriorLights = (ExteriorLights_t *)pvoidAsnDe;

    pstrbitAsnExteriorLights->size = WJV4_LEN_BYTE_EXTERIORLIGHT;
    pstrbitAsnExteriorLights->bits_unused = 8 * WJV4_LEN_BYTE_EXTERIORLIGHT - WJV4_LEN_BITSTR_EXTERIORLIGHT;
    pstrbitAsnExteriorLights->buf = CALLOC(1, pstrbitAsnExteriorLights->size);
    if (NULL == pstrbitAsnExteriorLights->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnExteriorLights, pstrbitWjExteriorLights);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_ExteriorLights_DeDec解码函数
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
int32_t WJV4_ExteriorLights_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_ExteriorLights *pstrbitWjExteriorLights = (WJV4_BIT_ExteriorLights *)pvoidWjDe;
    ExteriorLights_t *pstrbitAsnExteriorLights = (ExteriorLights_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnExteriorLights->buf) || (WJV4_LEN_BYTE_EXTERIORLIGHT != pstrbitAsnExteriorLights->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnExteriorLights->size,
                 pstrbitAsnExteriorLights->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnExteriorLights, pstrbitWjExteriorLights);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_GNSSstatus_DeEnc编码函数
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
int32_t WJV4_GNSSstatus_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_GNSSstatus *pstrbitWjGNSSstatus = (WJV4_BIT_GNSSstatus *)pvoidWjDe;
    GNSSstatus_t *pstrbitAsnGNSSstatus = (GNSSstatus_t *)pvoidAsnDe;

    pstrbitAsnGNSSstatus->size = WJV4_LEN_BYTE_GNSSSTATUS;
    pstrbitAsnGNSSstatus->bits_unused = 8 * WJV4_LEN_BYTE_GNSSSTATUS - WJV4_LEN_BITSTR_GNSSSTATUS;
    pstrbitAsnGNSSstatus->buf = CALLOC(1, pstrbitAsnGNSSstatus->size);
    if (NULL == pstrbitAsnGNSSstatus->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnGNSSstatus, pstrbitWjGNSSstatus);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_GNSSstatus_DeDec解码函数
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
int32_t WJV4_GNSSstatus_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_GNSSstatus *pstrbitWjGNSSstatus = (WJV4_BIT_GNSSstatus *)pvoidWjDe;
    GNSSstatus_t *pstrbitAsnGNSSstatus = (GNSSstatus_t *)pvoidAsnDe;
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnGNSSstatus, pstrbitWjGNSSstatus);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_IntersectionStatusObject_DeEnc编码函数
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
int32_t WJV4_IntersectionStatusObject_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_IntersectionStatusObject *pstrbitWjIntersectionStatusObject = (WJV4_BIT_IntersectionStatusObject *)pvoidWjDe;
    IntersectionStatusObject_t *pstrbitAsnIntersectionStatusObject = (IntersectionStatusObject_t *)pvoidAsnDe;

    pstrbitAsnIntersectionStatusObject->size = WJV4_LEN_BYTE_INTERSECTIONSTATUSPBJECT;
    pstrbitAsnIntersectionStatusObject->bits_unused = 8 * WJV4_LEN_BYTE_INTERSECTIONSTATUSPBJECT - WJV4_LEN_BITSTR_INTERSECTIONSTATUSPBJECT;
    pstrbitAsnIntersectionStatusObject->buf = CALLOC(1, pstrbitAsnIntersectionStatusObject->size);
    if (NULL == pstrbitAsnIntersectionStatusObject->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnIntersectionStatusObject, pstrbitWjIntersectionStatusObject);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_IntersectionStatusObject_DeDec解码函数
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
int32_t WJV4_IntersectionStatusObject_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_IntersectionStatusObject *pstrbitWjIntersectionStatusObject = (WJV4_BIT_IntersectionStatusObject *)pvoidWjDe;
    IntersectionStatusObject_t *pstrbitAsnIntersectionStatusObject = (IntersectionStatusObject_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnIntersectionStatusObject->buf) || (WJV4_LEN_BYTE_INTERSECTIONSTATUSPBJECT != pstrbitAsnIntersectionStatusObject->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnIntersectionStatusObject->size,
                 pstrbitAsnIntersectionStatusObject->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnIntersectionStatusObject, pstrbitWjIntersectionStatusObject);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesBarrier_DeEnc编码函数
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
int32_t WJV4_LaneAttributesBarrier_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesBarrier *pstrbitWjLaneAttributesBarrier = (WJV4_BIT_LaneAttributesBarrier *)pvoidWjDe;
    LaneAttributes_Barrier_t *pstrbitAsnLaneAttributesBarrier = (LaneAttributes_Barrier_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesBarrier->size = WJV4_LEN_BYTE_LANEATTRIBUTESBARRIER;
    pstrbitAsnLaneAttributesBarrier->bits_unused = 8 * WJV4_LEN_BYTE_LANEATTRIBUTESBARRIER - WJV4_LEN_BITSTR_LANEATTRIBUTESBARRIER;
    pstrbitAsnLaneAttributesBarrier->buf = CALLOC(1, pstrbitAsnLaneAttributesBarrier->size);
    if (NULL == pstrbitAsnLaneAttributesBarrier->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnLaneAttributesBarrier, pstrbitWjLaneAttributesBarrier);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesBarrier_DeDec解码函数
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
int32_t WJV4_LaneAttributesBarrier_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesBarrier *pstrbitWjLaneAttributesBarrier = (WJV4_BIT_LaneAttributesBarrier *)pvoidWjDe;
    LaneAttributes_Barrier_t *pstrbitAsnLaneAttributesBarrier = (LaneAttributes_Barrier_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesBarrier->buf) || (WJV4_LEN_BYTE_LANEATTRIBUTESBARRIER != pstrbitAsnLaneAttributesBarrier->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesBarrier->size,
                 pstrbitAsnLaneAttributesBarrier->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnLaneAttributesBarrier, pstrbitWjLaneAttributesBarrier);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesBike_DeEnc编码函数
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
int32_t WJV4_LaneAttributesBike_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesBike *pstrbitWjLaneAttributesBike = (WJV4_BIT_LaneAttributesBike *)pvoidWjDe;
    LaneAttributes_Bike_t *pstrbitAsnLaneAttributesBike = (LaneAttributes_Bike_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesBike->size = WJV4_LEN_BYTE_LANEATTRIBUTESBIKE;
    pstrbitAsnLaneAttributesBike->bits_unused = 8 * WJV4_LEN_BYTE_LANEATTRIBUTESBIKE - WJV4_LEN_BITSTR_LANEATTRIBUTESBIKE;
    pstrbitAsnLaneAttributesBike->buf = CALLOC(1, pstrbitAsnLaneAttributesBike->size);
    if (NULL == pstrbitAsnLaneAttributesBike->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnLaneAttributesBike, pstrbitWjLaneAttributesBike);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesBike_DeDec解码函数
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
int32_t WJV4_LaneAttributesBike_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesBike *pstrbitWjLaneAttributesBike = (WJV4_BIT_LaneAttributesBike *)pvoidWjDe;
    LaneAttributes_Bike_t *pstrbitAsnLaneAttributesBike = (LaneAttributes_Bike_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesBike->buf) || (WJV4_LEN_BYTE_LANEATTRIBUTESBIKE != pstrbitAsnLaneAttributesBike->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesBike->size,
                 pstrbitAsnLaneAttributesBike->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnLaneAttributesBike, pstrbitWjLaneAttributesBike);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesCrosswalk_DeEnc编码函数
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
int32_t WJV4_LaneAttributesCrosswalk_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesCrosswalk *pstrbitWjLaneAttributesCrosswalk = (WJV4_BIT_LaneAttributesCrosswalk *)pvoidWjDe;
    LaneAttributes_Crosswalk_t *pstrbitAsnLaneAttributesCrosswalk = (LaneAttributes_Crosswalk_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesCrosswalk->size = WJV4_LEN_BYTE_LANEATTRIBUTESCROSSWALK;
    pstrbitAsnLaneAttributesCrosswalk->bits_unused = 8 * WJV4_LEN_BYTE_LANEATTRIBUTESCROSSWALK - WJV4_LEN_BITSTR_LANEATTRIBUTESCROSSWALK;
    pstrbitAsnLaneAttributesCrosswalk->buf = CALLOC(1, pstrbitAsnLaneAttributesCrosswalk->size);
    if (NULL == pstrbitAsnLaneAttributesCrosswalk->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnLaneAttributesCrosswalk, pstrbitWjLaneAttributesCrosswalk);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesCrosswalk_DeDec解码函数
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
int32_t WJV4_LaneAttributesCrosswalk_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesCrosswalk *pstrbitWjLaneAttributesCrosswalk = (WJV4_BIT_LaneAttributesCrosswalk *)pvoidWjDe;
    LaneAttributes_Crosswalk_t *pstrbitAsnLaneAttributesCrosswalk = (LaneAttributes_Crosswalk_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesCrosswalk->buf) || (WJV4_LEN_BYTE_LANEATTRIBUTESCROSSWALK != pstrbitAsnLaneAttributesCrosswalk->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesCrosswalk->size,
                 pstrbitAsnLaneAttributesCrosswalk->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnLaneAttributesCrosswalk, pstrbitWjLaneAttributesCrosswalk);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesParking_DeEnc编码函数
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
int32_t WJV4_LaneAttributesParking_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesParking *pstrbitWjLaneAttributesParking = (WJV4_BIT_LaneAttributesParking *)pvoidWjDe;
    LaneAttributes_Parking_t *pstrbitAsnLaneAttributesParking = (LaneAttributes_Parking_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesParking->size = WJV4_LEN_BYTE_LANEATTRIBUTESPARKING;
    pstrbitAsnLaneAttributesParking->bits_unused = 8 * WJV4_LEN_BYTE_LANEATTRIBUTESPARKING - WJV4_LEN_BITSTR_LANEATTRIBUTESPARKING;
    pstrbitAsnLaneAttributesParking->buf = CALLOC(1, pstrbitAsnLaneAttributesParking->size);
    if (NULL == pstrbitAsnLaneAttributesParking->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnLaneAttributesParking, pstrbitWjLaneAttributesParking);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesParking_DeDec解码函数
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
int32_t WJV4_LaneAttributesParking_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesParking *pstrbitWjLaneAttributesParking = (WJV4_BIT_LaneAttributesParking *)pvoidWjDe;
    LaneAttributes_Parking_t *pstrbitAsnLaneAttributesParking = (LaneAttributes_Parking_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesParking->buf) || (WJV4_LEN_BYTE_LANEATTRIBUTESPARKING != pstrbitAsnLaneAttributesParking->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesParking->size,
                 pstrbitAsnLaneAttributesParking->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnLaneAttributesParking, pstrbitWjLaneAttributesParking);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesSidewalk_DeEnc编码函数
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
int32_t WJV4_LaneAttributesSidewalk_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesSidewalk *pstrbitWjLaneAttributesSidewalk = (WJV4_BIT_LaneAttributesSidewalk *)pvoidWjDe;
    LaneAttributes_Sidewalk_t *pstrbitAsnLaneAttributesSidewalk = (LaneAttributes_Sidewalk_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesSidewalk->size = WJV4_LEN_BYTE_LANEATTRIBUTESSIDEWALK;
    pstrbitAsnLaneAttributesSidewalk->bits_unused = 8 * WJV4_LEN_BYTE_LANEATTRIBUTESSIDEWALK - WJV4_LEN_BITSTR_LANEATTRIBUTESSIDEWALK;
    pstrbitAsnLaneAttributesSidewalk->buf = CALLOC(1, pstrbitAsnLaneAttributesSidewalk->size);
    if (NULL == pstrbitAsnLaneAttributesSidewalk->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }

    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnLaneAttributesSidewalk, pstrbitWjLaneAttributesSidewalk);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesSidewalk_DeDec解码函数
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
int32_t WJV4_LaneAttributesSidewalk_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesSidewalk *pstrbitWjLaneAttributesSidewalk = (WJV4_BIT_LaneAttributesSidewalk *)pvoidWjDe;
    LaneAttributes_Sidewalk_t *pstrbitAsnLaneAttributesSidewalk = (LaneAttributes_Sidewalk_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesSidewalk->buf) || (WJV4_LEN_BYTE_LANEATTRIBUTESSIDEWALK != pstrbitAsnLaneAttributesSidewalk->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesSidewalk->size,
                 pstrbitAsnLaneAttributesSidewalk->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnLaneAttributesSidewalk, pstrbitWjLaneAttributesSidewalk);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesStriping_DeEnc编码函数
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
int32_t WJV4_LaneAttributesStriping_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesStriping *pstrbitWjLaneAttributesStriping = (WJV4_BIT_LaneAttributesStriping *)pvoidWjDe;
    LaneAttributes_Striping_t *pstrbitAsnLaneAttributesStriping = (LaneAttributes_Striping_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesStriping->size = WJV4_LEN_BYTE_LANEATTRIBUTESSTRIPING;
    pstrbitAsnLaneAttributesStriping->bits_unused = 8 * WJV4_LEN_BYTE_LANEATTRIBUTESSTRIPING - WJV4_LEN_BITSTR_LANEATTRIBUTESSTRIPING;
    pstrbitAsnLaneAttributesStriping->buf = CALLOC(1, pstrbitAsnLaneAttributesStriping->size);
    if (NULL == pstrbitAsnLaneAttributesStriping->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnLaneAttributesStriping, pstrbitWjLaneAttributesStriping);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesStriping_DeDec解码函数
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
int32_t WJV4_LaneAttributesStriping_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesStriping *pstrbitWjLaneAttributesStriping = (WJV4_BIT_LaneAttributesStriping *)pvoidWjDe;
    LaneAttributes_Striping_t *pstrbitAsnLaneAttributesStriping = (LaneAttributes_Striping_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesStriping->buf) || (WJV4_LEN_BYTE_LANEATTRIBUTESSTRIPING != pstrbitAsnLaneAttributesStriping->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesStriping->size,
                 pstrbitAsnLaneAttributesStriping->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnLaneAttributesStriping, pstrbitWjLaneAttributesStriping);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesTrackedVehicle_DeEnc编码函数
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
int32_t WJV4_LaneAttributesTrackedVehicle_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesTrackedVehicle *pstrbitWjLaneAttributesTrackedVehicle = (WJV4_BIT_LaneAttributesTrackedVehicle *)pvoidWjDe;
    LaneAttributes_TrackedVehicle_t *pstrbitAsnLaneAttributesTrackedVehicle = (LaneAttributes_TrackedVehicle_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesTrackedVehicle->size = WJV4_LEN_BYTE_LANEATTRIBUTESTRACKEDVEHICLE;
    pstrbitAsnLaneAttributesTrackedVehicle->bits_unused = 8 * WJV4_LEN_BYTE_LANEATTRIBUTESTRACKEDVEHICLE - WJV4_LEN_BITSTR_LANEATTRIBUTESTRACKEDVEHICLE;
    pstrbitAsnLaneAttributesTrackedVehicle->buf = CALLOC(1, pstrbitAsnLaneAttributesTrackedVehicle->size);
    if (NULL == pstrbitAsnLaneAttributesTrackedVehicle->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnLaneAttributesTrackedVehicle, pstrbitWjLaneAttributesTrackedVehicle);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesTrackedVehicle_DeDec解码函数
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
int32_t WJV4_LaneAttributesTrackedVehicle_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesTrackedVehicle *pstrbitWjLaneAttributesTrackedVehicle = (WJV4_BIT_LaneAttributesTrackedVehicle *)pvoidWjDe;
    LaneAttributes_TrackedVehicle_t *pstrbitAsnLaneAttributesTrackedVehicle = (LaneAttributes_TrackedVehicle_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneAttributesTrackedVehicle->buf) || (WJV4_LEN_BYTE_LANEATTRIBUTESTRACKEDVEHICLE != pstrbitAsnLaneAttributesTrackedVehicle->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneAttributesTrackedVehicle->size,
                 pstrbitAsnLaneAttributesTrackedVehicle->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnLaneAttributesTrackedVehicle, pstrbitWjLaneAttributesTrackedVehicle);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesVehicle_DeEnc编码函数
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
int32_t WJV4_LaneAttributesVehicle_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesVehicle *pstrbitWjLaneAttributesVehicle = (WJV4_BIT_LaneAttributesVehicle *)pvoidWjDe;
    LaneAttributes_Vehicle_t *pstrbitAsnLaneAttributesVehicle = (LaneAttributes_Vehicle_t *)pvoidAsnDe;

    pstrbitAsnLaneAttributesVehicle->size = WJV4_LEN_BYTE_LANEATTRIBUTESVEHICLE;
    pstrbitAsnLaneAttributesVehicle->bits_unused = 8 * WJV4_LEN_BYTE_LANEATTRIBUTESVEHICLE - WJV4_LEN_BITSTR_LANEATTRIBUTESVEHICLE;
    pstrbitAsnLaneAttributesVehicle->buf = CALLOC(1, pstrbitAsnLaneAttributesVehicle->size);
    if (NULL == pstrbitAsnLaneAttributesVehicle->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnLaneAttributesVehicle, pstrbitWjLaneAttributesVehicle);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneAttributesVehicle_DeDec解码函数
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
int32_t WJV4_LaneAttributesVehicle_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneAttributesVehicle *pstrbitWjLaneAttributesVehicle = (WJV4_BIT_LaneAttributesVehicle *)pvoidWjDe;
    LaneAttributes_Vehicle_t *pstrbitAsnLaneAttributesVehicle = (LaneAttributes_Vehicle_t *)pvoidAsnDe;
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnLaneAttributesVehicle, pstrbitWjLaneAttributesVehicle);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }
    return true;
}
/**
* @brief     WJV4_LaneSharing_DeEnc编码函数
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
int32_t WJV4_LaneSharing_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneSharing *pstrbitWjLaneSharing = (WJV4_BIT_LaneSharing *)pvoidWjDe;
    LaneSharing_t *pstrbitAsnLaneSharing = (LaneSharing_t *)pvoidAsnDe;

    pstrbitAsnLaneSharing->size = WJV4_LEN_BYTE_LANESHARING;
    pstrbitAsnLaneSharing->bits_unused = 8 * WJV4_LEN_BYTE_LANESHARING - WJV4_LEN_BITSTR_LANESHARING;
    pstrbitAsnLaneSharing->buf = CALLOC(1, pstrbitAsnLaneSharing->size);
    if (NULL == pstrbitAsnLaneSharing->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnLaneSharing, pstrbitWjLaneSharing);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_LaneSharing_DeDec解码函数
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
int32_t WJV4_LaneSharing_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_LaneSharing *pstrbitWjLaneSharing = (WJV4_BIT_LaneSharing *)pvoidWjDe;
    LaneSharing_t *pstrbitAsnLaneSharing = (LaneSharing_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnLaneSharing->buf) || (WJV4_LEN_BYTE_LANESHARING != pstrbitAsnLaneSharing->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnLaneSharing->size,
                 pstrbitAsnLaneSharing->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnLaneSharing, pstrbitWjLaneSharing);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_ReferenceLanes_DeEnc编码函数
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
int32_t WJV4_ReferenceLanes_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_ReferenceLanes *pstrbitWjReferenceLanes = (WJV4_BIT_ReferenceLanes *)pvoidWjDe;
    ReferenceLanes_t *pstrbitAsnReferenceLanes = (ReferenceLanes_t *)pvoidAsnDe;

    pstrbitAsnReferenceLanes->size = WJV4_LEN_BYTE_REFERENCELANES;
    pstrbitAsnReferenceLanes->bits_unused = 8 * WJV4_LEN_BYTE_REFERENCELANES - WJV4_LEN_BITSTR_REFERENCELANES;
    pstrbitAsnReferenceLanes->buf = CALLOC(1, pstrbitAsnReferenceLanes->size);
    if (NULL == pstrbitAsnReferenceLanes->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnReferenceLanes, pstrbitWjReferenceLanes);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_ReferenceLanes_DeDec解码函数
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
int32_t WJV4_ReferenceLanes_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_ReferenceLanes *pstrbitWjReferenceLanes = (WJV4_BIT_ReferenceLanes *)pvoidWjDe;
    ReferenceLanes_t *pstrbitAsnReferenceLanes = (ReferenceLanes_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnReferenceLanes->buf) || (WJV4_LEN_BYTE_REFERENCELANES != pstrbitAsnReferenceLanes->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnReferenceLanes->size,
                 pstrbitAsnReferenceLanes->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnReferenceLanes, pstrbitWjReferenceLanes);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_RSIPriority_DeEnc编码函数
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
int32_t WJV4_RSIPriority_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_IA5_RSIPriority *pstria5WjRSIPriority = (WJV4_IA5_RSIPriority *)pvoidWjDe;
    RSIPriority_t *pstria5AsnRSIPriority = (RSIPriority_t *)pvoidAsnDe;
    if (0 != pstria5WjRSIPriority->u8RSIPriorityNum)
    {
        if ((WJV4_MAX_IA5_RSIPRIORITY_LEN < pstria5WjRSIPriority->u8RSIPriorityNum) || (0 > pstria5WjRSIPriority->u8RSIPriorityNum))
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
* @brief     WJV4_RSIPriority_DeDec解码函数
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
int32_t WJV4_RSIPriority_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_IA5_RSIPriority *pstria5WjRSIPriority = (WJV4_IA5_RSIPriority *)pvoidWjDe;
    RSIPriority_t *pstria5AsnRSIPriority = (RSIPriority_t *)pvoidAsnDe;
    if (0 < pstria5AsnRSIPriority->size)
    {
        if ((WJV4_MAX_IA5_RSIPRIORITY_LEN < pstria5AsnRSIPriority->size) || (1 > pstria5AsnRSIPriority->size))
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
* @brief     WJV4_VehicleEventFlags_DeEnc编码函数
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
int32_t WJV4_VehicleEventFlags_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_VehicleEventFlags *pstrbitWjVehicleEventFlags = (WJV4_BIT_VehicleEventFlags *)pvoidWjDe;
    VehicleEventFlags_t *pstrbitAsnVehicleEventFlags = (VehicleEventFlags_t *)pvoidAsnDe;

    pstrbitAsnVehicleEventFlags->size = WJV4_LEN_BYTE_VEHICLEEVENTFLAGS;
    pstrbitAsnVehicleEventFlags->bits_unused = 8 * WJV4_LEN_BYTE_VEHICLEEVENTFLAGS - WJV4_LEN_BITSTR_VEHICLEEVENTFLAGS;
    pstrbitAsnVehicleEventFlags->buf = CALLOC(1, pstrbitAsnVehicleEventFlags->size);
    if (NULL == pstrbitAsnVehicleEventFlags->buf)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "calloc is err");
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeEnc(pstrbitAsnVehicleEventFlags, pstrbitWjVehicleEventFlags);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeEnc is err");
        return false;
    }

    return true;
}
/**
* @brief     WJV4_VehicleEventFlags_DeDec解码函数
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
int32_t WJV4_VehicleEventFlags_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
{
    if ((NULL == pvoidAsnDe) || (NULL == pvoidWjDe))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "input is null:pvoidAsnDe = %p pvoidWjDe = %p",
                 pvoidAsnDe, pvoidWjDe);
        return false;
    }
    WJV4_BIT_VehicleEventFlags *pstrbitWjVehicleEventFlags = (WJV4_BIT_VehicleEventFlags *)pvoidWjDe;
    VehicleEventFlags_t *pstrbitAsnVehicleEventFlags = (VehicleEventFlags_t *)pvoidAsnDe;

    if ((NULL == pstrbitAsnVehicleEventFlags->buf) || (WJV4_LEN_BYTE_VEHICLEEVENTFLAGS != pstrbitAsnVehicleEventFlags->size))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_DE_MODULE,
                 "out of rangth:size = %d - %p",
                 pstrbitAsnVehicleEventFlags->size,
                 pstrbitAsnVehicleEventFlags->buf);
        return false;
    }
    int n32Ret = WJV4_BITSTRING_DeDec(pstrbitAsnVehicleEventFlags, pstrbitWjVehicleEventFlags);
    if (true != n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "WJV4_BITSTRING_DeDec is err");
        return false;
    }

    return true;
}

/**
 * @brief    WJV4_BITSTRING_DeEnc数据元素解码函数
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
int32_t WJV4_BITSTRING_DeEnc(void *pvoidAsnDe, void *pvoidWjDe)
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
 * @brief    WJV4_BITSTRING_DeDec的bitstring字段解码
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
int32_t WJV4_BITSTRING_DeDec(void *pvoidAsnDe, void *pvoidWjDe)
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
