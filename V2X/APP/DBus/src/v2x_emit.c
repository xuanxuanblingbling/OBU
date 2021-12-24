/*******************************************************************************
 * 文 件 名 称 ：  v2x_emit.h
 * 功 能 描 述 ： v2x模块dbus发送接口
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#include <dbus/dbus-glib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "v2x_obu_dbus_common.h"
#include "v2x_dbus.h"
#include "Common.h"
#include "socketCommon.h"

#define MODULE_NAME "DBUS_TX"
#include "Debug.h"

/*定义信号句柄*/
typedef enum
{
    V2X_SRV_MSG,
    V2X_SRV_STATE,
    V2X_SRV_FAULT_PUSH,
    V2X_SRV_CONFIG_RS,
    V2X_NET_COOPERATIVE,
    LAST_SIGNAL
} TSignalFd_t;

static guint signals[LAST_SIGNAL];                //信号句柄buffer,用于存储信号初始化返回值
G_DEFINE_TYPE(V2xObu, FV_v2x_obu, G_TYPE_OBJECT); //实现类类型定义

/*************************************************
  名称: FV_v2x_obu_init
  描述: 类成员构造函数初始化（不可变）
  输入参数:　
  返回值: 无
**************************************************/
static void FV_v2x_obu_init(V2xObu *obj)
{
}

/*************************************************
  名称: FV_v2x_obu_class_init
  描述: 类结构构造函数初始化，信号初始化（不可变）
  输入参数:
  返回值: 无
**************************************************/
static void FV_v2x_obu_class_init(V2xObuClass *klass)
{
    signals[V2X_SRV_MSG] = g_signal_new(
        NEW_V2X_SRV_MSG,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        (GSignalCMarshaller)g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    signals[V2X_SRV_STATE] = g_signal_new(
        NEW_V2X_SRV_STATE,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        (GSignalCMarshaller)g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    signals[V2X_SRV_FAULT_PUSH] = g_signal_new(
        NEW_V2X_SRV_FAULT_PUSH,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        (GSignalCMarshaller)g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    signals[V2X_SRV_CONFIG_RS] = g_signal_new(
        NEW_V2X_SRV_CONFIG_RS,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        (GSignalCMarshaller)g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    signals[V2X_NET_COOPERATIVE] = g_signal_new(
        NEW_V2X_NET_COOPERATIVE,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        (GSignalCMarshaller)g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
}

/*************************************************
  名称: FV_dbus_general_send_func
  描述: dbus通用发送接口
  输入参数:p_data:需要发送的数据，p_len：数据长度，p_sigid：信号id
  输出参数:无
  返回值:无
**************************************************/
void FV_dbus_general_send_func(uint8_t *p_data, uint32_t p_len, TSignalFd_t p_sigid)
{
    GArray *l_pPass = NULL; //定义GArray变量
    l_pPass = g_array_new(FALSE, TRUE, sizeof(uint8_t));
    uint16_t *p_pID = (uint16_t *)&p_data[0];
    uint16_t *l_pLen = (uint16_t *)&p_data[2];
    uint32_t *pMsgLen = (uint32_t *)&p_data[2];

    LogPrint(LOG_LEVEL_INFO, "V2X", "Meswage Type  = %d\n", *(uint16_t *)&p_data[8]);

    //判断信号类型，设置信号id,信号长度
    switch (p_sigid)
    {
    case V2X_SRV_MSG:
        *p_pID = MSG_V2X_SRV_MSG_ID;
        *pMsgLen = p_len - 2 - 4 - 1; /* ID:2bytes, LEN: 4bytes, BCC: 1byte. */
        //*pMsgLen = p_len + 2 + 2;       // m_version 2bytes   m_AID 2bytes

        //*********************IPC发送*********************
        if (true == sendDataFunc(p_data, p_len, 0X01, "NULL"))
        {
            int num = get_connect_num();
            LogPrint(LOG_LEVEL_INFO, "V2X", "Send Data Success , connet_num = %d\n", num);
            return;
        }
        else
        {
            LogPrint(LOG_LEVEL_INFO, "V2X", "Send Data failed !!\n");
            return;
        }
        //*********************IPC发送*********************

        break;
    case V2X_SRV_STATE:
        *p_pID = MSG_V2X_SRV_STATE_ID;
        *l_pLen = MSG_V2X_SRV_STATE_LEN;
        break;
    case V2X_SRV_FAULT_PUSH:
        *p_pID = MSG_V2X_SRV_FAULT_PUSH_ID;
        *l_pLen = MSG_V2X_SRV_FAULT_PUSH_LEN;
        break;
    case V2X_SRV_CONFIG_RS:
        *p_pID = MSG_V2X_SRV_CFG_RS_ID;
        *l_pLen = MSG_V2X_SRV_CFG_RS_LEN;
        break;
    case V2X_NET_COOPERATIVE:
        *p_pID = MSG_V2X_NET_COOPERATIVE_ID;
        *l_pLen = MSG_V2X_NET_COOPERATIVE_LEN;
        break;
    default:
        return;
    }
    p_data[p_len - 1] = FV_CheckSum(p_data, p_len - 1);   //求bcc
    g_array_append_vals(l_pPass, p_data, p_len);          //赋值给GArray
    g_signal_emit(g_ptObj, signals[p_sigid], 0, l_pPass); //发送数据
    g_array_free(l_pPass, TRUE);                          //GArray变量空间释放
}

/*************************************************
  名称: FV_emit_v2x_srv_msg
  描述: 信号发送函数，向总线推送数据
  输入参数:
  返回值: 无
**************************************************/
void FV_emit_v2x_srv_msg(int Msglen, int PortocVersion, int AID)
{
    g_tDbusV2xSrvMsg.m_Version = PortocVersion;
    g_tDbusV2xSrvMsg.m_AID = (uint16_t)AID;
    FV_dbus_general_send_func((uint8_t *)&g_tDbusV2xSrvMsg, Msglen, V2X_SRV_MSG);
}

void FV_emit_v2x_srv_state(void)
{
    FV_dbus_general_send_func((uint8_t *)&g_tDbusV2xSrvState, sizeof(g_tDbusV2xSrvState), V2X_SRV_STATE);
}

void FV_emit_v2x_srv_fault_push(void)
{
    FV_dbus_general_send_func((uint8_t *)&g_tDbusSrvFaultPush, sizeof(g_tDbusSrvFaultPush), V2X_SRV_FAULT_PUSH);
}

void FV_emit_v2x_srv_cfg_rs(void)
{
    FV_dbus_general_send_func((uint8_t *)&g_tDbusConfigRsCb, sizeof(g_tDbusConfigRsCb), V2X_SRV_CONFIG_RS);
}
void FV_emit_v2x_net_cooperative(void)
{
    FV_dbus_general_send_func((uint8_t *)&g_tRoadsideCoordination, sizeof(g_tRoadsideCoordination), V2X_NET_COOPERATIVE);
}
