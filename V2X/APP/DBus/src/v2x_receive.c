/*******************************************************************************
 * 文 件 名 称 ：v2x_receive.c
 * 功 能 描 述 ： v2x模块gdbus接收接口
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#include <dbus/dbus-glib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <glib/giochannel.h>
#include "v2x_obu_dbus_common.h"
#include "v2x_config.h"
#include "v2x_dbus.h"
#include "Common.h"

#define MODULE_NAME "DBUS_RX"
#include "Debug.h"

V2xObu *g_ptObj = NULL;
static GMainLoop *g_ptLoop = NULL;
static void FV_rcv_vds_message_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data); //监听app信号
static void FV_rcv_sys_message_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data); //监听sys信号
static void FV_v2x_signal_monitor(DBusGConnection *bus);                                     //信号监听初始化

extern int  g_n32Triger;
extern SendBuffer *g_pMsgSendBuffer;

/*************************************************
  名称: FV_DbusMainLoopStart
  描述: dbus模块Loop开启
  输入参数:
  输出参数:无
  返回值:无
**************************************************/
void FV_DbusMainLoopStart(void)
{
    PRINTF("Dbus service is running\n");
    g_main_loop_run(g_ptLoop);
}

/*************************************************
  名称: FV_init_v2x_dbus_communication
  描述:
  输入参数:
  输出参数:
  返回值:无
**************************************************/
gboolean FV_init_v2x_dbus_communication(void)
{
    DBusGConnection *bus;
    DBusGProxy *bus_proxy;
    GError *error = NULL;
    guint request_name_result;
    GIOChannel *chan;

    g_type_init();

    dbus_g_object_type_install_info(V2X_OBU_TYPE, &dbus_glib__object_info);
    g_ptLoop = g_main_loop_new(NULL, FALSE);

    //获取DBUS_BUS_SESSION 句柄
    bus = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (!bus)
    {
        PRINTF("Couldn't connect to system bus\n");
    }
    //链接DBUS总线上某节点
    bus_proxy = dbus_g_proxy_new_for_name(bus, "org.freedesktop.DBus", "/", "org.freedesktop.DBus");
    if (!dbus_g_proxy_call(bus_proxy, "RequestName", &error,
                           G_TYPE_STRING, V2X_OBU_DBUS_V2X_BUS_NAME,
                           G_TYPE_UINT, 0,
                           G_TYPE_INVALID,
                           G_TYPE_UINT, &request_name_result,
                           G_TYPE_INVALID))
    {
        PRINTF("Failed to acquire org.freesmartphone.vehmd\n");
    }

    //信号监听
    FV_v2x_signal_monitor(bus);

    //注册一个object
    g_ptObj = g_object_new(V2X_OBU_TYPE, NULL);
    dbus_g_connection_register_g_object(bus, V2X_OBU_DBUS_V2X_OBJECT_PATH, G_OBJECT(g_ptObj));

    //发送定时器初始化
    PRINTF("Dbus Init done ...\n");
    return TRUE;
}

gboolean FV_deinit_v2x_dbus_communication(void)
{
    PRINTF("Dbus deinit process ...\n");
    gboolean l_bRet = FALSE;
    if (g_ptLoop)
    {
        g_main_loop_quit(g_ptLoop);
        g_main_loop_unref(g_ptLoop);
        l_bRet = TRUE;
    }
    return l_bRet;
}

/*************************************************
  名称: FV_rcv_vds_message_handler
  描述:　信号回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FV_rcv_vds_message_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    static TMsgVehDataFrame_t l_tDbusVehDataFrame;
    uint32_t l_u32Len = pass->len;
    memcpy(&l_tDbusVehDataFrame, pass->data, l_u32Len);
    
    
    uint8_t l_bcc = l_tDbusVehDataFrame.m_Bcc;
    uint8_t l_n8BccSrc = *((uint8_t *)&l_tDbusVehDataFrame+l_u32Len-1);//获取接收数据的最后一个
    uint8_t l_n8BccDst = FV_CheckSum(&l_tDbusVehDataFrame, l_u32Len - 1);

    //OSA_millisecondsleep(1); /* Here Sleep to ensure dbus copy correctly. */
    if (l_n8BccSrc == l_n8BccDst)
    {
        //if (memcmp(&l_tDbusVehDataFrame, &g_tDbusVehDataFrame, sizeof(g_tDbusVehDataFrame)))
        {
            if (MSG_VDS_VEH_DATA_ID == l_tDbusVehDataFrame.m_MsgID)
            {
                memcpy(&g_tDbusVehDataFrame, &l_tDbusVehDataFrame, sizeof(g_tDbusVehDataFrame));
                // printf("g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_HazardLights:%d\n", g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_HazardLights);
#if EN_DBG_PRINT
                char Veh_ID[8] = {0};
                memcpy(Veh_ID, &g_tDbusVehDataFrame.m_MsgData.m_vehId[9], 8);
                printf("Vehicle ID:%s\n", Veh_ID);
                printf("g_tDbusVehDataFrame.m_MsgData.m_time:%d\n", g_tDbusVehDataFrame.m_MsgData.m_time);
                printf("g_tDbusVehDataFrame.m_MsgData.m_vehicleWidth:%d\n", g_tDbusVehDataFrame.m_MsgData.m_vehicleWidth);
                printf("g_tDbusVehDataFrame.m_MsgData.m_vehicleLength:%d\n", g_tDbusVehDataFrame.m_MsgData.m_vehicleLength);
                printf("g_tDbusVehDataFrame.m_MsgData.m_vehicleHeight:%d\n", g_tDbusVehDataFrame.m_MsgData.m_vehicleHeight);
                printf("g_tDbusVehDataFrame.m_MsgData.m_basicVehicleClass:%d\n", g_tDbusVehDataFrame.m_MsgData.m_basicVehicleClass);
                printf("g_tDbusVehDataFrame.m_MsgData.m_latitude:%d\n", g_tDbusVehDataFrame.m_MsgData.m_latitude);
                printf("g_tDbusVehDataFrame.m_MsgData.m_longitude:%d\n", g_tDbusVehDataFrame.m_MsgData.m_longitude);
                printf("g_tDbusVehDataFrame.m_MsgData.m_altitude:%d\n", g_tDbusVehDataFrame.m_MsgData.m_altitude);
                printf("g_tDbusVehDataFrame.m_MsgData.m_semiMajorAxisAccuracy:%d\n", g_tDbusVehDataFrame.m_MsgData.m_semiMajorAxisAccuracy);
                printf("g_tDbusVehDataFrame.m_MsgData.m_heading:%d\n", g_tDbusVehDataFrame.m_MsgData.m_heading);
                printf("g_tDbusVehDataFrame.m_MsgData.m_speed:%d\n", g_tDbusVehDataFrame.m_MsgData.m_speed);
                printf("g_tDbusVehDataFrame.m_MsgData.m_acc_lng:%d\n", g_tDbusVehDataFrame.m_MsgData.m_acc_lng);
                printf("g_tDbusVehDataFrame.m_MsgData.m_yawrate:%d\n", g_tDbusVehDataFrame.m_MsgData.m_yawrate);
                printf("g_tDbusVehDataFrame.m_MsgData.m_brakePedalStatus:%d\n", g_tDbusVehDataFrame.m_MsgData.m_brakePedalStatus);
                printf("g_tDbusVehDataFrame.m_MsgData.m_brakeAppliedStatus:%d\n", g_tDbusVehDataFrame.m_MsgData.m_brakeAppliedStatus);
                printf("g_tDbusVehDataFrame.m_MsgData.m_tractionControlStatus:%d\n", g_tDbusVehDataFrame.m_MsgData.m_tractionControlStatus);
                printf("g_tDbusVehDataFrame.m_MsgData.m_exteriorLights:%d\n", g_tDbusVehDataFrame.m_MsgData.m_exteriorLights);
                printf("g_tDbusVehDataFrame.m_MsgData.m_transmissionState:%d\n", g_tDbusVehDataFrame.m_MsgData.m_transmissionState);
                printf("g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_HazardLights:%d\n", g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_HazardLights);
                printf("g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_ABS:%d\n", g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_ABS);
                printf("g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_Traction:%d\n", g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_Traction);
                printf("g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_Stability:%d\n", g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_Stability);
                printf("g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_HardBraking:%d\n", g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_HardBraking);
                printf("g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_FlatTire:%d\n", g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_FlatTire);
                printf("g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_DisabledVehicle:%d\n", g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_DisabledVehicle);
                printf("g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_AirBagDeployment:%d\n", g_tDbusVehDataFrame.m_MsgData.m_warningevent.Event.m_event_AirBagDeployment);
#endif
            }
            else
            {
                PRINTF("Dismatch of MSG_VDS_VEH_DATA_ID\n");
            }
        }
    }
    else
    {
        PRINTF("Invalid data come from vds, data len %d, l_n8BccSrc: %d, l_n8BccDst:%d\n", pass->len, l_n8BccSrc, l_n8BccDst);
    }
}

/*************************************************
  名称: FV_rcv_sys_message_handler
  描述:　信号回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FV_rcv_sys_message_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    static TSrvConfigRs_t l_tDbusConfigRs = INIT_SRV_CFG_RS();
    uint32_t l_u32Len = pass->len;

    memcpy(&l_tDbusConfigRs, pass->data, l_u32Len);
    uint8_t l_n8BccSrc = l_tDbusConfigRs.m_Bcc;
    uint8_t l_n8BccDst = FV_CheckSum(&l_tDbusConfigRs, l_u32Len - 1);
    OSA_millisecondsleep(2); /* Here Sleep to ensure dbus copy correctly. */

    if (l_n8BccSrc == l_n8BccDst)
    {
        if (memcmp(&l_tDbusConfigRs, &g_tDbusConfigRs, sizeof(g_tDbusConfigRs)))
        {
            if (MSG_SYS_CONFIG_RQ_ID == l_tDbusConfigRs.m_MsgID)
            {
                g_tDbusConfigRs = l_tDbusConfigRs;
                if (g_tDbusConfigRs.m_V2xCfgUpdateNotify != 0xFF)
                {
                    INF("Received online config request\n");
                    FV_OnlineConfigRs();
                }
            }
            else
            {
                PRINTF("Dismatch of MSG_SYS_CONFIG_RQ_ID\n");
                return;
            }
        }
    }
    else
    {
        PRINTF("Invalid data come from vds, data len %d\n", pass->len);
        return;
    }
}
/*************************************************
  名称: FV_rcv_app_message_handler
  描述:　监听其他各节点的信号，注册回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FV_rcv_app_message_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    uint32_t l_u32Len = 0;
    TV2xSrvMsg_t  l_MessageRecv = {0};
    uint8_t l_n8BccSrc = 0;
    uint8_t l_n8BccDst = 0;
    
    l_u32Len = pass->len;
    memcpy(&l_MessageRecv, pass->data, l_u32Len);
    l_n8BccDst = FV_CheckSum(pass->data, l_u32Len - 1);
    l_n8BccSrc = pass->data[l_u32Len-1];
    LogPrint(LOG_LEVEL_DEBUG, STACK_MSG_MODULE, "Receive app msg bcc %d %d ", l_n8BccDst,l_n8BccSrc);
    if (l_n8BccSrc == l_n8BccDst)
    {
        pthread_mutex_lock(&(g_pMsgSendBuffer->m_muxtex));
        memcpy(&(g_pMsgSendBuffer->m_msgbufer.messageType),&l_MessageRecv.m_V2xMessageFrame.messageType, l_u32Len-11);
        pthread_mutex_unlock(&(g_pMsgSendBuffer->m_muxtex));
        g_n32Triger = YES;
    }
    else
    {
        g_n32Triger = NO;
    }
}
/*************************************************
  名称: FV_v2x_signal_monitor
  描述:　监听其他各节点的信号，注册回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FV_v2x_signal_monitor(DBusGConnection *bus)
{
    DBusGProxy *vds_object;
    DBusGProxy *sys_object;
    //连接VDS节点
    vds_object = dbus_g_proxy_new_for_name(bus, V2X_OBU_DBUS_VDS_BUS_NAME, //节点名称
                                           V2X_OBU_DBUS_VDS_OBJECT_PATH,   //节点路径
                                           V2X_OBU_DBUS_VDS_INTFACE_NAME); //接口名称
    if (!vds_object)
        PRINTF("Failed to get name owner\n");
    //监听VDS信号
    dbus_g_proxy_add_signal(vds_object, MSG_VDS_VEH_DATA, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(vds_object, MSG_VDS_VEH_DATA, G_CALLBACK(FV_rcv_vds_message_handler), NULL, NULL);
    //连接SYS节点
    sys_object = dbus_g_proxy_new_for_name(bus, V2X_OBU_DBUS_SYS_BUS_NAME, //节点名称
                                           V2X_OBU_DBUS_SYS_OBJECT_PATH,   //节点路径
                                           V2X_OBU_DBUS_SYS_INTFACE_NAME); //接口名称
    if (!sys_object)
        PRINTF("Failed to get name owner\n");
    //监听SYS信号
    dbus_g_proxy_add_signal(sys_object, MSG_SYS_CONFIG_RQ, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(sys_object, MSG_SYS_CONFIG_RQ, G_CALLBACK(FV_rcv_sys_message_handler), NULL, NULL);

    //连接APP节点
    sys_object = dbus_g_proxy_new_for_name(bus, V2X_OBU_DBUS_APP_BUS_NAME, //节点名称
                                           V2X_OBU_DBUS_APP_OBJECT_PATH,   //节点路径
                                           V2X_OBU_DBUS_APP_INTFACE_NAME); //接口名称
    if (!sys_object)
        PRINTF("Failed to get name owner\n");
    //监听SYS信号
    dbus_g_proxy_add_signal(sys_object, MSG_APP_SEND_V2XMSG, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(sys_object, MSG_APP_SEND_V2XMSG, G_CALLBACK(FV_rcv_app_message_handler), NULL, NULL);
}