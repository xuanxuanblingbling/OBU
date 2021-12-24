/***********************************************************************
 * 文 件 名 称 ： NewFourSpanLogIf.h
 * 功 能 描 述 ： 新四跨大规模测试日志记录用于外部引用文件
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-08-18 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/

#ifndef __NEW_FOUR_SPAN_LOGIF_H__
#define __NEW_FOUR_SPAN_LOGIF_H__

#include "BSMTx.h"
//协议栈消息层头文件
#include "wj_Message_com.h"

#ifdef __cplusplus
extern "C"
{
#endif

    char *mystrdup(const char *str);
    extern int FL_SetRecvdSelfBsmMsg(char *p_pBsmNameId, TVehData_t *p_ptVehData);

    /* 调用下面接口之前必须先调用上面接口进行初始化自身BSM数据 */
    extern int FL_WriteRecvdMsgLog(WJV4_STRU_MessageFrame *p_tV2xMsgRecvd);
    extern int FL_WriteSendMsgLog(WJV4_STRU_MessageFrame *p_tV2xMsgRecvd, TVehData_t *p_ptVehData);
    extern int FL_DestroyMsgLog(void);

#ifdef __cplusplus
}
#endif

#endif