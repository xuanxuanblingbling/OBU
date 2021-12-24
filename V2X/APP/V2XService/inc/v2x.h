/*******************************************************************************
 * 文 件 名 称 ： v2x.h
 * 功 能 描 述 ： v2x协议栈交互模块
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#ifndef __V2X_H__
#define __V2X_H__

//#include "cv_msg_frame.h"
#include "wjv4_uper_interface.h"
#include "V2xBasicTypes.h"

V2X_BEGIN_HEADER
#define  LENGTH(A, B)   (sizeof( WJV ## A ## _STRU_ ## B))

typedef struct
{
    uint16_t m_MsgID;
    uint32_t m_MsgLength;
    uint16_t m_Version;
    uint16_t m_AID;
    MSG_MessageType_st   m_V2xMessageFrame;
    uint8_t  m_Bcc;
} __attribute__((packed)) TV2xSrvMsg_t;

typedef struct
{
    uint16_t m_MsgID;
    uint32_t m_MsgLength;
    uint16_t m_Version;
    uint16_t m_AID;
    WJV4_STRU_MessageFrame m_V2xMessageFrame;   
    uint8_t m_Bcc;
} __attribute__((packed)) TV2xSrvMsgN4_t;

#define INIT_V2X_SRV_MSG()   \
    {                        \
        .m_Version = 0xFFFF, \
        .m_AID = 0xFFFF      \
    }

/**
 * @brief V2X全局变量定义
 * @note 用于BSMTx模块通信的全局变量声明.
 */
extern TV2xSrvMsg_t g_tDbusV2xSrvMsg;
extern TV2xSrvMsgN4_t  g_tDbusV2xSrvMsgN4;

V2X_END_HEADER

#endif