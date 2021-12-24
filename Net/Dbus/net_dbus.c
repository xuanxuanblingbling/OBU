/*******************************************************************************
 * 文 件 名 称 ： net_dbus.c
 * 功 能 描 述 ： dbus消息收发模块
 * 开 发 人 员 ： GongMinghao
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2021-08-18 V1.0    GongMinghao   Create
 *
 * @Copyright (C)  2021  .wanji. all right reserved
*******************************************************************************/
#include <dbus/dbus-glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>
#include <glib/giochannel.h>
#include "dbus_config.h"
#include "net_dbus.h"
#include "dbus_common.h"
#include "dbus_data_type.h"
#include "net_data_handler.h"
#include "Config/net_log.h"
#include "Config/Net_Json.h"
#include "Net/net_platform_warn_type.h"
#include "TongZhou/inc/app_lst.h"

/*dbus object init*/
typedef struct netobul_databuf
{
    GObject parent;
} NetObu;

typedef struct netobuclass
{
    GObjectClass parent;
} NetObuClass;
#define NET_OBU_TYPE (net_obu_get_type())
GType net_obu_get_type(void);

NetObu *g_netDbusObj;

G_DEFINE_TYPE(NetObu, net_obu, G_TYPE_OBJECT) //实现类类型定义
static guint net_signals[NET_LAST_SIGNAL];    //信号句柄buffer,用于存储信号初始化返回值

#define maxsize 5000

NetLinkStatus g_status;

/***********************************************************************
 * 函 数 名 称 ：FV_CheckSum
 * 功 能 描 述 ：异或校验
 * 输 入 参 数 ：p_pvData: buffer地址
 * 输 入 参 数 ：p_u32Len: buffer长度
 * 输 出 参 数 ：无
 * 返  回  值  :  校验值
 * 开 发 人 员 ：Yaozhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/
uint8_t FV_CheckSum(void *p_pvData, size_t p_u32Len)
{
    uint8_t *l_pu8Data = (uint8_t *)p_pvData;
    uint8_t l_u8Bcc = 0;
    for (size_t l_u32Cnt = 0; l_u32Cnt < p_u32Len; l_u32Cnt++)
    {
        l_u8Bcc ^= *l_pu8Data++;
    }
    return l_u8Bcc;
}
/***************************************************************************************************/
/*                                        dbus消息接收                                              */
/***************************************************************************************************/
// 类成员构造函数初始化（不可变）
static void net_obu_init(NetObu *obj)
{
}

static void net_obu_class_init(NetObuClass *klass)
{
    net_signals[NET_CAN_DATA] = g_signal_new(
        NEW_NET_SIM_CAN_DATA,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    net_signals[NET_LINK_STATUS] = g_signal_new(
        NEW_NET_STATUS,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    net_signals[NET_CONFIG_RS] = g_signal_new(
        NEW_NET_CONFIG_RS,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);

    net_signals[NET_FAULT_STATUS] = g_signal_new(
        NEW_NET_FAULLT,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
}

void vds_VdsVehData_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    static TMsgVehDataFrame_t l_tDbusVehDataFrame;
    uint32_t l_u32Len = pass->len;
    memcpy(&l_tDbusVehDataFrame, pass->data, l_u32Len);

    uint8_t l_bcc = l_tDbusVehDataFrame.m_Bcc;
    uint8_t l_n8BccSrc = *((uint8_t *)&l_tDbusVehDataFrame + l_u32Len - 1); //获取接收数据的最后一个
    uint8_t l_n8BccDst = DBUS_CaluBcc(&l_tDbusVehDataFrame, l_u32Len - 1);

    if (l_n8BccSrc == l_n8BccDst)
    {
        {
            if (MSG_VDS_VEH_DATA_ID == l_tDbusVehDataFrame.m_MsgID)
            {
                memcpy(&g_tDbusVehDataFrame, &l_tDbusVehDataFrame, sizeof(g_tDbusVehDataFrame));
            }
            else
            {
                printf("Dismatch of MSG_VDS_VEH_DATA_ID\n");
            }
        }
    }
    else
    {
        printf("Invalid data come from vds, data len %d, l_n8BccSrc: %d, l_n8BccDst:%d\n", pass->len, l_n8BccSrc, l_n8BccDst);
    }
}

void FN_ResultActSafe_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "FN_ResultActSafe_handler app -> ActSafe\n");

    ResultActSafe *l_VehData = (ResultActSafe *)(pass->data);
    if (pass->len != (l_VehData->LENGTH + 5) || l_VehData->ID != APP_ACT_SAFE_ID)
        return;

    uint8_t l_nCalBcc = DBUS_CaluBcc(pass->data, pass->len - 1);

    if (l_nCalBcc != (uint8_t)pass->data[pass->len - 1])
        return;

    GetAppMsgData(MAIN_CMD_10, SUB_CMD_00, (char *)l_VehData, pass->len - 3);
    return;
}

void FN_ResultTrfcRemind_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "FN_ResultTrfcRemind_handler app -> TrfcRemind\n");

    ResultTrfcRemind *l_VehData = (ResultTrfcRemind *)(pass->data);
    if (pass->len != (l_VehData->LENGTH + 5) || l_VehData->ID != APP_TRFC_REMIND_ID)
        return;

    uint8_t l_nCalBcc = DBUS_CaluBcc(pass->data, pass->len - 1);
    if (l_nCalBcc != (uint8_t)pass->data[pass->len - 1])
        return;

    GetAppMsgData(MAIN_CMD_12, SUB_CMD_00, (char *)&(l_VehData->LENGTH), pass->len - 3);
    return;
}

void FN_ResultSpdGuide_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "FN_ResultSpdGuide_handler app -> SpdGuide\n");

    ResultSpdGuide *l_VehData = (ResultSpdGuide *)(pass->data);
    if (pass->len != (l_VehData->LENGTH + 5) || l_VehData->ID != APP_SPD_GUIDE_ID)
        return;

    uint8_t l_nCalBcc = DBUS_CaluBcc(pass->data, pass->len - 1);
    if (l_nCalBcc != (uint8_t)pass->data[pass->len - 1])
        return;

    GetAppMsgData(MAIN_CMD_11, SUB_CMD_00, (char *)&(l_VehData->LENGTH), pass->len - 3);
    return;
}

void FN_ResultVruSafe_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "FN_ResultVruSafe_handler app -> VruSafe\n");

    ResultVulSafe *l_VehData = (ResultVulSafe *)(pass->data);
    if (pass->len != (l_VehData->LENGTH + 5) || l_VehData->ID != APP_VRU_SAFE_ID)
        return;

    uint8_t l_nCalBcc = DBUS_CaluBcc(pass->data, pass->len - 1);
    if (l_nCalBcc != (uint8_t)pass->data[pass->len - 1])
        return;

    GetAppMsgData(MAIN_CMD_13, SUB_CMD_00, (char *)&(l_VehData->LENGTH), pass->len - 3);
    return;
}
void FN_ResultMatch_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    printf("dbus收到app消息地图匹配结果\n");
    static VehMapMatchInfo l_VehMapMatchInfo;
    uint32_t l_u32Len = pass->len;
    memcpy(&l_VehMapMatchInfo, pass->data, l_u32Len);

    uint8_t l_bcc = l_VehMapMatchInfo.m_bcc;
    uint8_t l_n8BccSrc = *((uint8_t *)&l_VehMapMatchInfo + l_u32Len - 1); //获取接收数据的最后一个
    uint8_t l_n8BccDst = FV_CheckSum(&l_VehMapMatchInfo, l_u32Len - 1);

    if (l_n8BccSrc == l_n8BccDst)
    {
        {
            if (MSG_VDS_VEH_DATA_ID == l_VehMapMatchInfo.m_id)
            {
                memcpy(&g_tVehMapMatchInfo, &l_VehMapMatchInfo, sizeof(g_tVehMapMatchInfo));
            }
            else
            {
                printf("Dismatch of MSG_VDS_VEH_DATA_ID\n");
            }
        }
    }
    else
    {
        printf("Invalid data come from vds, data len %d, l_n8BccSrc: %d, l_n8BccDst:%d\n", pass->len, l_n8BccSrc, l_n8BccDst);
    }
}

void FN_ResultPlatfrom_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "FN_ResultPlatfrom_handler app -> Platfrom\n");

    V2xPlatformSceneWarnDbus *p_V2xPlatformSceneWarnDbus = (V2xPlatformSceneWarnDbus *)(pass->data);
    if (pass->len != (p_V2xPlatformSceneWarnDbus->LENGTH + 5) || p_V2xPlatformSceneWarnDbus->ID != APP_SEND_PLATFORM_ID)
        return;

    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "p_V2xPlatformSceneWarnDbus->v2xplatformsceneWarn.type is %d\n", p_V2xPlatformSceneWarnDbus->v2xplatformsceneWarn.type);
    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "p_V2xPlatformSceneWarnDbus->v2xplatformsceneWarn.hv_ele is %f\n", p_V2xPlatformSceneWarnDbus->v2xplatformsceneWarn.hv_ele);
    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "p_V2xPlatformSceneWarnDbus->v2xplatformsceneWarn.hv_head is %f\n", p_V2xPlatformSceneWarnDbus->v2xplatformsceneWarn.hv_head);
    uint8_t l_nCalBcc = DBUS_CaluBcc(pass->data, pass->len - 1);
    if (l_nCalBcc != (uint8_t)pass->data[pass->len - 1])
        return;
    GetAppScenMsgData(p_V2xPlatformSceneWarnDbus->v2xplatformsceneWarn);
    return;
}

void FN_sys_ConfigRq_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "FN_sys_ConfigRq_handler sys\n");
    ResultSysFrame *l_VehData = (ResultSysFrame *)(pass->data);
    if (pass->len != (l_VehData->LENGTH + 5) || l_VehData->ID != APP_SYS_CFGRQ_TAG)
        return;

    uint8_t l_nCalBcc = DBUS_CaluBcc(pass->data, pass->len - 1);
    if (l_nCalBcc != (uint8_t)pass->data[pass->len - 1])
        return;

    if (l_VehData->NetNotify == 0x80)
    {
        RestartTcpServer();
        Net_Dbus_Send_SysConfigRq();
    }
}

void FN_v2x_Cooperative_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "FN_ResultActSafe_handler V2X -> Cooperative\n");

    RoadsideCoordination_t *l_roadsideCoordination = (RoadsideCoordination_t *)(pass->data);
    if (pass->len != (l_roadsideCoordination->m_MsgLength + 5) || l_roadsideCoordination->m_MsgID != V2X_NET_COORDINATION_ID)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "pass->len is %d  l_roadsideCoordination->m_MsgLength is %d l_roadsideCoordination->m_MsgID is %d", pass->len, l_roadsideCoordination->m_MsgLength, l_roadsideCoordination->m_MsgID);
        return;
    }

    uint8_t l_nCalBcc = DBUS_CaluBcc(pass->data, pass->len - 1);

    if (l_nCalBcc != (uint8_t)pass->data[pass->len - 1])
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "l_nCalBcc != (uint8_t)pass->data[pass->len - 1]");
        return;
    }
    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "l_roadsideCoordination->planpathpoints is %d", l_roadsideCoordination->planpathpoints);
    GetAppMsgData(MAIN_CMD_19, SUB_CMD_00, (char *)l_roadsideCoordination, pass->len - 3);
    // CooperativeSendSecMsgData(l_roadsideCoordination);
    return;
}

void net_signal_monitor(DBusGConnection *bus)
{
    printf("dbus信号监听函数\n");
    DBusGProxy *vds_object;
    DBusGProxy *app_object;
    DBusGProxy *sys_object;
    DBusGProxy *v2x_object;
    //连接VDS节点
    vds_object = dbus_g_proxy_new_for_name(bus, V2X_OBU_DBUS_VDS_BUS_NAME, //节点名称
                                           V2X_OBU_DBUS_VDS_OBJECT_PATH,   //节点路径
                                           V2X_OBU_DBUS_VDS_INTFACE_NAME); //接口名称
    if (!vds_object)
        LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "net_signal_monitor VDS Failed to get name owner\n");

    //监听VDS信号
    dbus_g_proxy_add_signal(vds_object, MSG_VDS_VEH_DATA, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(vds_object, MSG_VDS_VEH_DATA, G_CALLBACK(vds_VdsVehData_handler), NULL, NULL);
    //连接APP节点
    app_object = dbus_g_proxy_new_for_name(bus, V2X_OBU_DBUS_APP_BUS_NAME, //节点名称
                                           V2X_OBU_DBUS_APP_OBJECT_PATH,   //节点路径
                                           V2X_OBU_DBUS_APP_INTFACE_NAME); //接口名称
    if (!app_object)
        LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "net_signal_monitor APP Failed to get name owner\n");

    //监听APP信号
    dbus_g_proxy_add_signal(app_object, MSG_APP_RESULT_ACT_SAFE, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(app_object, MSG_APP_RESULT_ACT_SAFE, G_CALLBACK(FN_ResultActSafe_handler), NULL, NULL);
    dbus_g_proxy_add_signal(app_object, MSG_APP_RESULT_TRFC_REMIND, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(app_object, MSG_APP_RESULT_TRFC_REMIND, G_CALLBACK(FN_ResultTrfcRemind_handler), NULL, NULL);
    dbus_g_proxy_add_signal(app_object, MSG_APP_RESULT_VRUSAFE, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(app_object, MSG_APP_RESULT_VRUSAFE, G_CALLBACK(FN_ResultVruSafe_handler), NULL, NULL);
    //监听APP的MAP匹配结果信号
    dbus_g_proxy_add_signal(app_object, MSG_APP_SEND_MATCHDATA, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(app_object, MSG_APP_SEND_MATCHDATA, G_CALLBACK(FN_ResultMatch_handler), NULL, NULL);

    //监听APP的往平台推送数据信号
    dbus_g_proxy_add_signal(app_object, MSG_APP_SEND_PLATFROM, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(app_object, MSG_APP_SEND_PLATFROM, G_CALLBACK(FN_ResultPlatfrom_handler), NULL, NULL);

    //连接SYS节点
    sys_object = dbus_g_proxy_new_for_name(bus, V2X_OBU_DBUS_SYS_BUS_NAME, //节点名称
                                           V2X_OBU_DBUS_SYS_OBJECT_PATH,   //节点路径
                                           V2X_OBU_DBUS_SYS_INTFACE_NAME); //接口名称
    if (!sys_object)
        LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "net_signal_monitor SYS Failed to get name owner\n");

    //监听SYS信号
    dbus_g_proxy_add_signal(sys_object, MSG_SYS_CONFIG_RQ, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(sys_object, MSG_SYS_CONFIG_RQ, G_CALLBACK(FN_sys_ConfigRq_handler), NULL, NULL);

    //连接V2X节点
    v2x_object = dbus_g_proxy_new_for_name(bus, V2X_OBU_DBUS_V2X_BUS_NAME, //节点名称
                                           V2X_OBU_DBUS_V2X_OBJECT_PATH,   //节点路径
                                           V2X_OBU_DBUS_V2X_INTFACE_NAME); //接口名称
    if (!v2x_object)
        LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "net_signal_monitor V2X Failed to get name owner\n");
    //监听V2X节点
    dbus_g_proxy_add_signal(v2x_object, MSG_V2X_NET_COOPERATIVE, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(v2x_object, MSG_V2X_NET_COOPERATIVE, G_CALLBACK(FN_v2x_Cooperative_handler), NULL, NULL);
}

NetObu *NetDbusModuleInit(void)
{
    LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "DBUS 初始化\n");
    DBusGConnection *l_dBus;
    DBusGProxy *l_dBusProxy;
    GError *l_gError = NULL;
    guint request_name_result;

    g_type_init();
    dbus_g_object_type_install_info(NET_OBU_TYPE, &dbus_glib__object_info);
    //获取DBUS_BUS_SESSION 句柄
    l_dBus = dbus_g_bus_get(DBUS_BUS_SESSION, &l_gError);
    if (!l_dBus)
    {
        LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "NetDbusModuleInit Couldn't connect to system bus\n");
    }
    //链接DBUS总线上某节点
    l_dBusProxy = dbus_g_proxy_new_for_name(l_dBus, "org.freedesktop.DBus", "/", "org.freedesktop.DBus");
    if (!dbus_g_proxy_call(l_dBusProxy, "RequestName", &l_gError,
                           G_TYPE_STRING, V2X_OBU_DBUS_NET_BUS_NAME,
                           G_TYPE_UINT, 0,
                           G_TYPE_INVALID,
                           G_TYPE_UINT, &request_name_result,
                           G_TYPE_INVALID))
    {
        LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "NetDbusModuleInit Failed to acquire %s\n", V2X_OBU_DBUS_APP_BUS_NAME);
    }
    //信号监听
    net_signal_monitor(l_dBus);
    //注册一个object
    NetObu *l_obj = g_object_new(NET_OBU_TYPE, NULL);
    dbus_g_connection_register_g_object(l_dBus, V2X_OBU_DBUS_NET_OBJECT_PATH, G_OBJECT(l_obj));
    return l_obj;
}

/***************************************************************************************************/
/*                                               dbus消息发送                                        /
/***************************************************************************************************/

/*************************************************
  名称: FN_callback_NetLinkStatus
  描述:　周期发送网络连接状态消息
  输入参数:无
  返回值: 无
**************************************************/
static void Net_Send_LinkStatus()
{
    uint8_t l_databuf[maxsize];
    uint16_t l_id = MSGM_NET_LINK_STATUS_TAG;
    uint32_t l_datalen = 0;

    //NetLinkStatus status;
    memcpy(l_databuf, &l_id, 2);
    uint16_t l_len = sizeof(NetLinkStatus);
    memcpy(&l_databuf[2], &l_len, 2);
    memcpy(&l_databuf[4], &g_status, l_len);

    uint8_t l_bbcResult = DBUS_CaluBcc(l_databuf, l_len + 4);

    memcpy(&l_databuf[4 + l_len], &l_bbcResult, 1);
    l_len += 5;

    GArray *pass = NULL;
    pass = g_array_new(FALSE, TRUE, sizeof(uint8_t));
    g_array_append_vals(pass, l_databuf, l_len);
    g_signal_emit(g_netDbusObj, net_signals[NET_LINK_STATUS], 0, pass);
    g_array_free(pass, TRUE); //GArray变量空间释放
}

/*************************************************
  名称: Net_Dbus_Send_SysConfigRq
  描述:　周期发送配置信息消息
  输入参数:无
  返回值: 无
**************************************************/
void Net_Dbus_Send_SysConfigRq()
{
    uint8_t l_databuf[maxsize];
    uint16_t l_id = MSGM_NET_CONFIG_RS_TAG;
    uint8_t l_result = UPDATE_SUCCESS;
    uint16_t l_buflen = 1U;

    //对数据进行封装
    memcpy(l_databuf, &l_id, 2);
    memcpy(&l_databuf[2], &l_buflen, 2);
    memcpy(&l_databuf[4], &l_result, l_buflen);
    uint8_t l_bbcResult = DBUS_CaluBcc(l_databuf, l_buflen + 4);
    memcpy(&l_databuf[4 + l_buflen], &l_bbcResult, 1);
    l_buflen += 5;

    GArray *pass = NULL;
    pass = g_array_new(FALSE, TRUE, sizeof(uint8_t));
    g_array_append_vals(pass, l_databuf, l_buflen);
    g_signal_emit(g_netDbusObj, net_signals[NET_CONFIG_RS], 0, pass);
    g_array_free(pass, TRUE); //GArray变量空间释放
}

/*************************************************
  名称: MsgM_Send_Candata
  描述:　触发之后按照一定的周期发送模拟CAN消息
  输入参数:无
  返回值: 无
**************************************************/
static void Net_Dbus_Send_Candata()
{
    F2 l_veh;
    F2_N l_net;
    uint8_t l_databuf[maxsize];
    //std::unique_lock<std::mutex> lck(l_mtx);
    l_veh = FN_readCanData();
    //lck.unlock();
    if (l_veh.canFlag)
    {
        uint16_t l_buflen = 0;
        uint16_t l_id = MSGM_NET_SIM_CAN_TAG;
        uint8_t l_bbcResult = 0;

        l_buflen = sizeof(F2_N);
        memcpy(&(l_net.speed), &(l_veh.speed), l_buflen - 1);
        l_net.transmissionState = 3;

        memcpy(&l_databuf[0], &l_id, 2);
        memcpy(&l_databuf[2], &l_buflen, 2);
        memcpy(&l_databuf[4], &l_net, l_buflen);
        l_bbcResult = DBUS_CaluBcc(l_databuf, l_buflen + 4);
        memcpy(&l_databuf[4 + l_buflen], &l_bbcResult, 1);
        l_buflen = l_buflen + 5;

        GArray *pass = NULL;                              //定义GArray变量
        pass = g_array_new(FALSE, TRUE, sizeof(uint8_t)); //GArray变量初始化
        g_array_append_vals(pass, l_databuf, l_buflen);
        g_signal_emit(g_netDbusObj, net_signals[NET_CAN_DATA], 0, pass);
        g_array_free(pass, TRUE); //GArray变量空间释放
    }
    else
    {
        LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "Net_Dbus_Send_Candata canFlag：%d\n", l_veh.canFlag);
    }
}

/*************************************************
  名称: FN_FaultStatus_Send
  描述:　NET模块错误状态发送
  输入参数:无
  返回值: 无
**************************************************/
gboolean FN_FaultStatus_Send()
{
    GArray *pass = NULL;
    uint8_t l_databuf[maxsize];
    uint16_t l_id = MSGM_NET_Fault_Status_TAG;
    uint8_t l_result = 0x81;
    uint16_t l_buflen = 2U;

    memcpy(l_databuf, &l_id, 2);
    memcpy(&l_databuf[2], &l_buflen, 2);
    memcpy(&l_databuf[4], &l_result, l_buflen);
    uint8_t l_bbcResult = DBUS_CaluBcc(l_databuf, l_buflen + 4);
    memcpy(&l_databuf[4 + l_buflen], &l_bbcResult, 1);

    pass = g_array_new(FALSE, TRUE, sizeof(uint8_t));
    g_array_append_vals(pass, l_bbcResult, l_buflen + 5);
    g_signal_emit(g_netDbusObj, net_signals[NET_FAULT_STATUS], 0, pass);
    g_array_free(pass, TRUE); //GArray变量空间释放

    return 0;
}

/*****************************************************
* 名称：Net_Send_Fun
*  描述:　NET模块错误状态发送
*  输入参数:无
*  返回值: 无
* ****************************************************/
static gboolean Net_Send_Fun()
{
    Net_Dbus_Send_Candata();
    Net_Send_LinkStatus();
    return TRUE;
}

/*****************************************************
* 名称：NetDbusRecvThread
*  描述:　NET模块错误状态发送
*  输入参数:无
*  返回值: 无
* ****************************************************/
void NetDbusRecvThread(void)
{
    struct itimerval tv, otv;
    GMainLoop *l_gLoop = g_main_loop_new(NULL, FALSE);
    g_netDbusObj = NetDbusModuleInit();

    g_timeout_add(DBUS_SEND_TIMER, Net_Send_Fun, NULL);
    g_main_loop_run(l_gLoop);
    return;
}
