/************************************************************
  文件名: vds_dbusRecv.c
  作者:                 
  描述: 初始化dbus相关参数，注册监听信号回调函数，监听数据            
  版本:     
  日期:       
  函数列表:   
  历史记录: 
 ***********************************************************/
#include <dbus/dbus-glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib/giochannel.h>
#include "v2x_obu_dbus_common.h"
#include "general_config.h"
#include "app_queue.h"
#include "vds_config.h"
#include "vds_dbus.h"
#include "GPS.h"

/*变量定义*/
V2xObu *obj;
GMainLoop *mainloop;
G_DEFINE_TYPE(V2xObu, v2x_obu, G_TYPE_OBJECT) //实现类类型定义
GType v2x_obu_get_type(void);
#define V2X_OBU_TYPE (v2x_obu_get_type())

void FD_DbusModuleInit(void);
static void *DbusInitThreadFun(void *p_para);
static void vds_signal_monitor(DBusGConnection *bus); //信号监听初始化

guint signals[LAST_SIGNAL]; //信号句柄buffer,用于存储信号初始化返回值

/*************************************************
  名称: v2x_obu_init
  描述: 类成员构造函数初始化（不可变）
  输入参数:　
  返回值: 无
**************************************************/
static void v2x_obu_init(V2xObu *obj)
{
}
/*************************************************
  名称: v2x_obu_class_init
  描述: 类结构构造函数初始化，信号初始化（不可变）
  输入参数:
  返回值: 无
**************************************************/
static void v2x_obu_class_init(V2xObuClass *klass)
{
    signals[VDS_VEH_DATA] = g_signal_new(
        NEW_VDS_VEH_DATA,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    signals[VDS_STATE_PUSH] = g_signal_new(
        NEW_VDS_STATE_PUSH,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    signals[VDS_FAULT_PUSH] = g_signal_new(
        NEW_VDS_FAULT_PUSH,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    signals[MCU_FAULT_PUSH] = g_signal_new(
        NEW_VDS_MCU_FAULT_PUSH,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    signals[MCU_PDOWN_RQ] = g_signal_new(
        NEW_VDS_MCU_PD_RQ,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    signals[VDS_CONFIG_RS] = g_signal_new(
        NEW_VDS_CONFIG_RS,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    signals[MCU_CONFIG_RS] = g_signal_new(
        NEW_MCU_CONFIG_RS,
        G_OBJECT_CLASS_TYPE(klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
}

/*************************************************
  名称: FD_DbusModuleCreat
  描述: dbus模块创建
  输入参数:
  输出参数:无
  返回值:无
**************************************************/
void FD_DbusModuleCreat(void)
{
    FD_DbusModuleInit(); //dbus模块初始化

    /*创建glib-dbus,mainloop线程，用于阻塞监听各信号*/
    pthread_t l_dbus_id = 0;
    pthread_attr_t l_dbus_attr = {0};
    pthread_attr_init(&l_dbus_attr);
    pthread_attr_setdetachstate(&l_dbus_attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&l_dbus_id, &l_dbus_attr, DbusInitThreadFun, (void *)obj);
    pthread_attr_destroy(&l_dbus_attr);
}
/*************************************************
  名称: DbusInitThreadFun
  描述: dbus初始化线程，用于阻塞监听各信号
  输入参数:obj
  输出参数:无
  返回值:无
**************************************************/
static void *DbusInitThreadFun(void *p_para)
{
    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "service is running");
    g_main_loop_run(mainloop);
}
/*************************************************
  名称: FD_DbusModuleInit
  描述: dbus模块初始化
  输入参数:
  输出参数:无
  返回值:无
**************************************************/
void FD_DbusModuleInit(void)
{
    DBusGConnection *bus;
    DBusGProxy *bus_proxy;
    GError *error = NULL;
    guint request_name_result;
    GIOChannel *chan;
    //初始化
    g_type_init();
    dbus_g_object_type_install_info(V2X_OBU_TYPE, &dbus_glib__object_info);
    mainloop = g_main_loop_new(NULL, FALSE);
    //获取DBUS_BUS_SESSION 句柄
    bus = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (!bus)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Couldn't connect to system bus");
    }
    //链接DBUS总线上某节点
    bus_proxy = dbus_g_proxy_new_for_name(bus, "org.freedesktop.DBus", "/", "org.freedesktop.DBus");
    if (!dbus_g_proxy_call(bus_proxy, "RequestName", &error,
                           G_TYPE_STRING, V2X_OBU_DBUS_VDS_BUS_NAME,
                           G_TYPE_UINT, 0,
                           G_TYPE_INVALID,
                           G_TYPE_UINT, &request_name_result,
                           G_TYPE_INVALID))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Failed to acquire %s", V2X_OBU_DBUS_VDS_BUS_NAME);
    }
    //信号监听
    vds_signal_monitor(bus);
    //注册一个object
    obj = g_object_new(V2X_OBU_TYPE, NULL);
    dbus_g_connection_register_g_object(bus, V2X_OBU_DBUS_VDS_OBJECT_PATH, G_OBJECT(obj));
    //定时器初始化
    g_timeout_add(VDS_TIME1_OUT, FD_vds_emit_signal_of_veh_data, G_OBJECT(obj));
    g_timeout_add(VDS_TIME2_OUT, FD_vds_emit_signal_of_state_push, G_OBJECT(obj));
    g_timeout_add(VDS_TIME2_OUT, FD_vds_emit_signal_of_led, G_OBJECT(obj));
}
/*************************************************
  名称: FD_signal_of_app_result_act_safe_handler
  描述:　信号回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FD_signal_of_app_result_act_safe_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    uint16_t l_n32Len = 0;
    uint8_t l_recvBuf[DBUS_MAX_SIZE] = {
        0,
    }; //设定APP可能发来的数据最大为10000字节
    TAppData l_ActSafe;
    TAppQueueMember l_AppQueueMember;
    memset(&l_ActSafe, 0, sizeof(TAppData));
    l_n32Len = pass->len; //获取接收数据长度
    if (l_n32Len <= DBUS_MAX_SIZE)
    {
        memcpy(l_recvBuf, pass->data, l_n32Len); //获取dbus总线下发的数据
    }
    memcpy(&l_ActSafe, l_recvBuf, APP_ACT_SAFE_FRAME_LEN - 1); //提取有效数据
    l_ActSafe.m_bcc = FD_CaluBcc(l_recvBuf, l_n32Len - 1);     //求bcc
    //判断bcc是否正确
    if (l_ActSafe.m_bcc != l_recvBuf[l_n32Len - 1])
    {
        LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "app_result_act_safe bcc not match");
        return FALSE;
    }
    else
    { //判断接收长度
        if (l_n32Len > APP_ACT_SAFE_FRAME_LEN)
        {
            l_ActSafe.m_length = APP_ACT_SAFE_DATA_LEN; //得到最大数据长度
        }
        //判断msgid
        if (l_ActSafe.m_id == APP_ACT_SAFE_ID)
        {
            memcpy(&l_AppQueueMember.m_appData, &l_ActSafe, sizeof(TAppData));
            pthread_mutex_lock(&g_APPRecvMutex); //加锁
            FD_AppQueueInsert(&g_app_recv_queue, &l_AppQueueMember);
            pthread_mutex_unlock(&g_APPRecvMutex); //解锁
            // //信号通知MCU模块，发送app场景输出数据
            // pthread_mutex_lock(&g_SpiSendMutex);//加锁
            // //g_SpiSendFlag|=APP_SCENE_VALID;
            // pthread_mutex_unlock(&g_SpiSendMutex);//解锁
            // pthread_cond_signal(&g_SpiSendCond);//触发编码层组帧
        }
        else
        {
            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "app_result_act_safe id:%d not match", l_ActSafe.m_id);
        }
    }
}
/*************************************************
  名称: FD_signal_of_app_result_trfc_remind_handler
  描述:　信号回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FD_signal_of_app_result_trfc_remind_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    uint16_t l_n32Len = 0;
    uint8_t l_recvBuf[DBUS_MAX_SIZE] = {
        0,
    }; //设定APP可能发来的数据最大为10000字节
    TAppData l_TrfcRemind;
    TAppQueueMember l_AppQueueMember;
    memset(&l_TrfcRemind, 0, sizeof(TAppData));
    l_n32Len = pass->len; //获取接收数据长度
    if (l_n32Len <= DBUS_MAX_SIZE)
    {
        memcpy(l_recvBuf, pass->data, l_n32Len); //获取dbus总线下发的数据
    }
    memcpy(&l_TrfcRemind, l_recvBuf, APP_TRFC_REMIND_FRAME_LEN - 1); //提取有效数据
    l_TrfcRemind.m_bcc = FD_CaluBcc(l_recvBuf, l_n32Len - 1);        //求bcc
    //判断bcc是否正确
    if (l_TrfcRemind.m_bcc != l_recvBuf[l_n32Len - 1])
    {
        LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "app_result_trfc_remind bcc not match");
    }
    else
    { //判断接收长度
        if (l_n32Len > APP_TRFC_REMIND_FRAME_LEN)
        {
            l_TrfcRemind.m_length = APP_TRFC_REMIND_DATA_LEN;
        }
        //判断msgid
        if (l_TrfcRemind.m_id == APP_TRFC_REMIND_ID)
        {
            memcpy(&l_AppQueueMember.m_appData, &l_TrfcRemind, sizeof(TAppData));
            pthread_mutex_lock(&g_APPRecvMutex); //加锁
            FD_AppQueueInsert(&g_app_recv_queue, &l_AppQueueMember);
            pthread_mutex_unlock(&g_APPRecvMutex); //解锁
            // //信号通知MCU模块，发送app场景输出数据
            // pthread_mutex_lock(&g_SpiSendMutex);//加锁
            // //g_SpiSendFlag|=APP_SCENE_VALID;
            // pthread_mutex_unlock(&g_SpiSendMutex);//解锁
            // pthread_cond_signal(&g_SpiSendCond);//触发编码层组帧
        }
        else
        {
            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "app_result_trfc_remind id:%d not match", l_TrfcRemind.m_id);
        }
    }
}
/*************************************************
  名称: FD_signal_of_app_result_spd_guide_handler
  描述:　信号回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FD_signal_of_app_result_spd_guide_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    uint16_t l_n32Len = 0;
    uint8_t l_recvBuf[DBUS_MAX_SIZE] = {
        0,
    }; //设定APP可能发来的数据最大为1000字节
    TAppData l_SpdGuide;
    TAppQueueMember l_AppQueueMember;
    memset(&l_SpdGuide, 0, sizeof(TAppData));
    l_n32Len = pass->len; //获取接收数据长度
    if (l_n32Len <= DBUS_MAX_SIZE)
    {
        memcpy(l_recvBuf, pass->data, l_n32Len); //获取dbus总线下发的数据
    }

    memcpy(&l_SpdGuide, l_recvBuf, APP_SPD_GUIDE_FRAME_LEN - 1); //提取有效数据
    l_SpdGuide.m_bcc = FD_CaluBcc(l_recvBuf, l_n32Len - 1);      //求bcc
    //判断bcc是否正确
    if (l_SpdGuide.m_bcc != l_recvBuf[l_n32Len - 1])
    {
        LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "app_result_spd_guide bcc not match");
    }
    else
    {
        //判断接收长度
        if (l_n32Len > APP_SPD_GUIDE_FRAME_LEN)
        {
            l_SpdGuide.m_length = APP_SPD_GUIDE_DATA_LEN;
        }
        //判断msgid
        if (l_SpdGuide.m_id == APP_SPD_GUIDE_ID)
        {
            memcpy(&l_AppQueueMember.m_appData, &l_SpdGuide, sizeof(TAppData));
            pthread_mutex_lock(&g_APPRecvMutex); //加锁
            FD_AppQueueInsert(&g_app_recv_queue, &l_AppQueueMember);
            pthread_mutex_unlock(&g_APPRecvMutex); //解锁
            // //信号通知MCU模块，发送app场景输出数据
            // pthread_mutex_lock(&g_SpiSendMutex);//加锁
            // //g_SpiSendFlag|=APP_SCENE_VALID;
            // pthread_mutex_unlock(&g_SpiSendMutex);//解锁
            // pthread_cond_signal(&g_SpiSendCond);//触发编码层组帧
        }
        else
        {
            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "app_result_spd_guide id:%d not match", l_SpdGuide.m_id);
        }
    }
}
/*************************************************
  名称: FD_signal_of_app_result_spd_guide_handler
  描述:　信号回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FD_signal_of_app_candata_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    int l_n32len = 0;
    unsigned char l_u8Bcc = 0;
    SenarioCanResult l_AppCanDatast = {0};
    l_n32len = pass->len;
    memcpy(&l_AppCanDatast, pass->data, l_n32len);
    l_u8Bcc = FD_CaluBcc(pass->data, l_n32len - 1); //求bcc
    if (l_u8Bcc != pass->data[l_n32len - 1])
    {
        LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "receive app can data but bcc failed!\n");
    }
    else
    {
        LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "receive app can data success!\n");
    }
}
/*************************************************
  名称: FD_signal_of_sys_config_rq_handler
  描述:　信号回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FD_signal_of_sys_config_rq_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    int l_n32Len = 0;
    uint8_t l_recvBuf[DBUS_MAX_SIZE] = {
        0,
    };
    l_n32Len = pass->len; //获取接收数据长度
    if (l_n32Len <= DBUS_MAX_SIZE)
    {
        memcpy(l_recvBuf, pass->data, l_n32Len); //获取dbus总线下发的数据
    }
    memcpy(&g_SysConfigRq, l_recvBuf, SYS_CONFIG_RQ_FRAME_LEN); //提取有效数据
    g_SysConfigRq.m_bcc = FD_CaluBcc(l_recvBuf, l_n32Len - 1);  //求bcc
    //判断bcc是否正确
    if (g_SysConfigRq.m_bcc != l_recvBuf[l_n32Len - 1])
    {
        printf("bcc is %x\n", g_SysConfigRq.m_bcc);
        LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "sys_config_rq bcc not match");
    }
    else
    {
        //判断msgid
        if (g_SysConfigRq.m_id == SYS_CONFIG_RQ_ID)
        {
            uint8_t l_CfgUpFaiFlag = FALSE; //触发响应标志
            switch (g_SysConfigRq.m_configRq.m_VdsCfgFlag)
            {
            //VDS参数发生更新
            case SYS_CFGRq_VDS:
            {
                //车辆配置信息
                if (0 != param_veh_parse(VDS_CONFIG_FILE_NAME, &g_param_veh_info))
                {
                    l_CfgUpFaiFlag = TRUE;
                    //车辆配置文件获取成功，发送响应
                    g_VdsConfigRs.m_config_rs.m_VdsCfgRs = VDS_CFGRs_FAILE; //vds配置文件更新失败
                    LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "config file %s parse failed", VDS_CONFIG_FILE_NAME);
                }
                else
                {
                    //通知编码层更新车辆信息配置文件
                    pthread_mutex_lock(&g_EncodeTrigMutex); //加锁
                    g_VdsEncodeFlag |= JSON_VALID;
                    pthread_mutex_unlock(&g_EncodeTrigMutex); //解锁
                    pthread_cond_signal(&g_EncodeTrigCond);   //触发编码层组帧
                    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "config file %s parse sucess", VDS_CONFIG_FILE_NAME);
                }
            }
            break;
            //MCU参数发生更新
            case SYS_CFGRq_MCU:
            {
                // if(0 != param_mcu_parse(MCU_CONFIG_FILE_NAME, &g_param_mcu_info))
                // {
                //     l_CfgUpFaiFlag = TRUE;
                //     //车辆配置文件获取成功，发送响应
                //     g_VdsConfigRs.m_config_rs.m_McucfgRs = MCU_CFGRs_FAILE;//vds配置文件更新失败
                //     LogPrint(LOG_LEVEL_ERR,MODULE_NAME, "config file %s parse failed", MCU_CONFIG_FILE_NAME);
                // }
                // else
                // {
                //     g_McuCfgRqFlag = true;
                //     //通知spi发送线程，发送配置文件信息
                //     pthread_mutex_lock(&g_SpiSendMutex);//加锁
                //     //g_SpiSendFlag |= SYS_CONFIG_VALID;//SYS MCU配置文件更新
                //     pthread_mutex_unlock(&g_SpiSendMutex);//解锁
                //     pthread_cond_signal(&g_SpiSendCond);//触发spi发送信号
                //     LogPrint(LOG_LEVEL_INFO,MODULE_NAME, "config file %s parse sucess", MCU_CONFIG_FILE_NAME);
                // }
            }
            break;
            //AG35参数发生更新（ag35配置信息确定）
            case SYS_CFGRq_AG35:
            {
                // //1.ag35配置信息获取
                // if(0 != param_veh_parse(VDS_CONFIG_FILE_NAME, &g_param_veh_info))
                // {
                //     l_CfgUpFaiFlag = TRUE;
                //     //车辆配置文件获取成功，发送响应
                //     g_VdsConfigRs.m_config_rs.m_Ag35cfgRs = AG35_CFGRs_FAILE;//vds配置文件更新失败
                //     LogPrint(LOG_LEVEL_ERR,MODULE_NAME, "config file %s parse failed", VDS_CONFIG_FILE_NAME);
                // }
                // else
                // {
                //     g_Ag35CfgRqFlag |= 0x3;//（bit0:ag35配置请求发送标志、向ag35发送一次配置请求后清零，bit1:ag35配置请求有效标志）
                //     LogPrint(LOG_LEVEL_INFO,MODULE_NAME,  "config file %s parse sucess", VDS_CONFIG_FILE_NAME);
                // }
            }
            break;
            //sys主动获取mcu当前配置信息
            case SYS_CFGGt_MCU:
            {
                //g_McuCfgReportFlag = true;
            }
            break;
            default:
                break;
            }
            //更新失败，通知系统管理模块配置文件更新结果
            if (l_CfgUpFaiFlag)
            {
                pthread_mutex_lock(&g_VDSCfgRsMutex);
                DbusGeneralSendFuc((uint8_t *)&g_VdsConfigRs, sizeof(TVdsConfigRs_st), VDS_CONFIG_RS); //dbus发送vds配置响应帧
                pthread_mutex_unlock(&g_VDSCfgRsMutex);
            }
        }
        else
        {
            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "sys_config_rq id:%d not match", g_SysConfigRq.m_id);
        }
    }
}
/*************************************************
  名称: FD_signal_of_sys_mcu_power_down_rs_handler
  描述:　信号回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FD_signal_of_sys_mcu_power_down_rs_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    // int      l_n32Len = 0;
    // uint8_t  l_recvBuf[DBUS_MAX_SIZE] = {0,};
    // l_n32Len = pass->len;//获取接收数据长度
    // if(l_n32Len<=DBUS_MAX_SIZE)
    // {
    //     memcpy(l_recvBuf,pass->data,l_n32Len);//获取dbus总线下发的数据
    // }
    // memcpy(&g_SysPowerdownRs,l_recvBuf,SYS_PDOWN_RS_FRAME_LEN);//提取有效数据
    // g_SysPowerdownRs.m_bcc = FD_CaluBcc(l_recvBuf,l_n32Len-1);//求bcc
    // //判断bcc是否正确
    // if(g_SysPowerdownRs.m_bcc != l_recvBuf[l_n32Len-1])
    // {
    //     LogPrint(LOG_LEVEL_DEBUG,MODULE_NAME,"sys_mcu_power_down_rs bcc not match");
    // }
    // else
    // {
    //     //判断msgid
    //     if(g_SysPowerdownRs.m_id == SYS_PDOWN_RS_ID)
    //     {
    //         //通知spi发送线程，发送配置文件信息
    //         pthread_mutex_lock(&g_SpiSendMutex);//加锁
    //         //g_SpiSendFlag |= SYS_POWER_VALID;//SYS MCU配置文件更新
    //         pthread_mutex_unlock(&g_SpiSendMutex);//解锁
    //         pthread_cond_signal(&g_SpiSendCond);//触发spi发送信号
    //     }
    //     else
    //     {
    //         LogPrint(LOG_LEVEL_DEBUG,MODULE_NAME,"sys_mcu_power_down_rs id:%d not match",g_SysPowerdownRs.m_id);
    //     }
    // }
}
/*************************************************
  名称: FD_signal_of_net_sim_can_data_handler
  描述:　信号回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FD_signal_of_net_sim_can_data_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{

    int l_n32Len = 0;
    uint8_t l_recvBuf[DBUS_MAX_SIZE] = {
        0,
    };
    struct timeval tv;
    uint64_t timestamp = 0;
    l_n32Len = pass->len; //获取接收数据长度
    printf("====[test] Recive sim can data ==\n");
    if (l_n32Len <= DBUS_MAX_SIZE)
    {
        memcpy(l_recvBuf, pass->data, l_n32Len); //获取dbus总线下发的数据
    }
    memcpy(&g_NetCanSimulate, l_recvBuf, NET_CAN_SIMULATE_FRAME_LEN); //提取有效数据
    g_NetCanSimulate.m_bcc = FD_CaluBcc(l_recvBuf, l_n32Len - 1);     //求bcc
    //判断bcc是否正确
    if (g_NetCanSimulate.m_bcc != l_recvBuf[l_n32Len - 1])
    {
        LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "net_sim_can_data bcc not match");
    }
    else
    {
        printf("====[test] simcan data  bcc WRITE====\n");
        //判断msgid
        if (g_NetCanSimulate.m_id == NET_SIM_CAN_ID)
        {
            gettimeofday(&tv, NULL);
            timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec * 0.001;

            //赋值到VDS车辆数据帧
            pthread_mutex_lock(&g_VDSVehFrameMutex); //加锁
            /***刹车踏板***/
            g_VdsVehFrame.m_vehdata.m_candata_st.m_DF_BrakeSystemStatus.m_u8_BrakeSystemStatusData = g_NetCanSimulate.m_canSimuData.m_n32brakePedalStatus; //刹车踏板
            g_VdsVehFrame.m_vehdata.m_candata_st.m_DF_BrakeSystemStatus.m_u64_BrakeSystenStatus_timestamp = timestamp;
            if (2 == g_VdsVehFrame.m_vehdata.m_candata_st.m_DF_BrakeSystemStatus.m_u8_BrakeSystemStatusData)
            {
                g_VdsVehFrame.m_vehdata.m_warningevent.Event.m_event_HardBraking = 0x1;
            }
            else
            {
                g_VdsVehFrame.m_vehdata.m_warningevent.Event.m_event_HardBraking = 0;
            }

            /***车辆档位状态***/
            g_VdsVehFrame.m_vehdata.m_candata_st.m_DE_TransmissionState.m_u8_TransmissionStateData = g_NetCanSimulate.m_canSimuData.m_u8transmissionState; //车辆档位状态
            g_VdsVehFrame.m_vehdata.m_candata_st.m_DE_TransmissionState.m_u64_TransmissionStateData_timestamp = timestamp;

            //车辆类型
            g_VdsVehFrame.m_vehdata.m_basicVehicleClass = g_NetCanSimulate.m_canSimuData.m_n32basicVehicleClass;

            /*****车速****/
            g_VdsVehFrame.m_vehdata.m_candata_st.m_DE_Speed.m_dbl_SpeedData = (double)(g_NetCanSimulate.m_canSimuData.m_u32speed);
            g_VdsVehFrame.m_vehdata.m_candata_st.m_DE_Speed.m_u64_SpeedData_timestamp = timestamp;

            /**方向盘转角**/
            g_VdsVehFrame.m_vehdata.m_candata_st.m_DE_SteeringWheelAngle.m_dbl_SteeringWheelAngleData = (double)(g_NetCanSimulate.m_canSimuData.m_u32wheelTurn);
            g_VdsVehFrame.m_vehdata.m_candata_st.m_DE_SteeringWheelAngle.m_u64_SteeringWheelAngle_timestamp = timestamp;
            /**车灯**/
            if ((g_NetCanSimulate.m_canSimuData.m_u16exteriorLights & 0x10) == 0x10) //危险信号灯
            {
                g_VdsVehFrame.m_vehdata.m_warningevent.Event.m_event_HazardLights = 0x1;
                g_VdsVehFrame.m_vehdata.m_candata_st.m_HazardLampSt.m_u8_RecVehLampMessage = 0x1;
                g_VdsVehFrame.m_vehdata.m_candata_st.m_HazardLampSt.m_u64_VehGNSS_timestamp = timestamp;
            }
            else
            {
                g_VdsVehFrame.m_vehdata.m_warningevent.Event.m_event_HazardLights = 0x0;
                g_VdsVehFrame.m_vehdata.m_candata_st.m_HazardLampSt.m_u8_RecVehLampMessage = 0;
            }

            //远光
            g_VdsVehFrame.m_vehdata.m_candata_st.m_HighBeamSt.m_u8_RecVehLampMessage =
                (uint8_t)((g_NetCanSimulate.m_canSimuData.m_u16exteriorLights & 0x0002) >> 1);
            g_VdsVehFrame.m_vehdata.m_candata_st.m_HighBeamSt.m_u64_VehGNSS_timestamp = timestamp;

            //近光
            g_VdsVehFrame.m_vehdata.m_candata_st.m_LowBeamSt.m_u8_RecVehLampMessage =
                (uint8_t)(g_NetCanSimulate.m_canSimuData.m_u16exteriorLights & 0x0001);
            g_VdsVehFrame.m_vehdata.m_candata_st.m_LowBeamSt.m_u64_VehGNSS_timestamp = timestamp;
            //左转
            g_VdsVehFrame.m_vehdata.m_candata_st.m_LeftTurnLampSt.m_u8_RecVehLampMessage =
                (uint8_t)((g_NetCanSimulate.m_canSimuData.m_u16exteriorLights & 0x0004) >> 2);
            g_VdsVehFrame.m_vehdata.m_candata_st.m_LeftTurnLampSt.m_u64_VehGNSS_timestamp = timestamp;

            //右转
            g_VdsVehFrame.m_vehdata.m_candata_st.m_RightTurnLampSt.m_u8_RecVehLampMessage =
                (uint8_t)((g_NetCanSimulate.m_canSimuData.m_u16exteriorLights & 0x0008) >> 3);
            g_VdsVehFrame.m_vehdata.m_candata_st.m_RightTurnLampSt.m_u64_VehGNSS_timestamp = timestamp;

            //停车灯
            g_VdsVehFrame.m_vehdata.m_candata_st.m_ParkingLampSt.m_u8_RecVehLampMessage =
                (uint8_t)((g_NetCanSimulate.m_canSimuData.m_u16exteriorLights & 0x0100) >> 8);
            g_VdsVehFrame.m_vehdata.m_candata_st.m_ParkingLampSt.m_u64_VehGNSS_timestamp = timestamp;

            //紧急车辆警示灯
            g_VdsVehFrame.m_vehdata.m_candata_st.m_EmergeWarningLightSt.m_u8_RecVehLampMessage =
                (uint8_t)((g_NetCanSimulate.m_canSimuData.m_u16exteriorLights & 0x0200) >> 9);
            g_VdsVehFrame.m_vehdata.m_candata_st.m_EmergeWarningLightSt.m_u64_VehGNSS_timestamp = timestamp;
            uint8_t driving_status = (uint8_t)((g_NetCanSimulate.m_canSimuData.m_u16exteriorLights & 0x0018) >> 3);
            g_NetCanSimulate.m_canSimuData.m_u16exteriorLights = g_NetCanSimulate.m_canSimuData.m_u16exteriorLights & 0x0000;
            // printf("***********************************g_NetCanSimulate.m_canSimuData.m_u16exteriorLights %d\n", g_NetCanSimulate.m_canSimuData.m_u16exteriorLights);
            // printf("***********************************driving_status is %d\n", driving_status);
            if (driving_status == 1)
            {
                g_VdsVehFrame.m_vehdata.m_driveIntent.m_u8CLCintent = 1;
                g_VdsVehFrame.m_vehdata.m_driveIntent.m_u32CLCvaildtime = timestamp;
                //汇入
            }
            else if (driving_status == 2)
            {
                g_VdsVehFrame.m_vehdata.m_driveIntent.m_u8CLCintent = 2;
                g_VdsVehFrame.m_vehdata.m_driveIntent.m_u32CLCvaildtime = timestamp;
                //汇出
            }
            else
            {
                //结束请求
                g_VdsVehFrame.m_vehdata.m_driveIntent.m_u8CLCintent = 0;
                g_VdsVehFrame.m_vehdata.m_driveIntent.m_u32CLCvaildtime = timestamp;
            }

            //牵引力制动系统
            if (2 == g_NetCanSimulate.m_canSimuData.m_n32auxiliaryBrakeSystem)
            {
                g_VdsVehFrame.m_vehdata.m_warningevent.Event.m_event_Traction = 0x01;
            }
            else
            {
                g_VdsVehFrame.m_vehdata.m_warningevent.Event.m_event_Traction = 0x00;
            }

            pthread_mutex_unlock(&g_VDSVehFrameMutex); //解锁
        }
        else
        {
            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "net_sim_can_data bcc id:%d not match", g_NetCanSimulate.m_id);
        }
        printf("====[test] simcan ID WRITE   speed  %d ======\n", g_NetCanSimulate.m_canSimuData.m_u32speed);
        printf("====[test] simcan ID WRITE   LeftTrun %d ======\n", g_VdsVehFrame.m_vehdata.m_candata_st.m_LeftTurnLampSt.m_u8_RecVehLampMessage);
        printf("====[test] simcan ID WRITE   WriteTrun %d ======\n", g_VdsVehFrame.m_vehdata.m_candata_st.m_RightTurnLampSt.m_u8_RecVehLampMessage);
        printf("====[test] simcan ID WRITE   vehclass  %d ======\n", g_VdsVehFrame.m_vehdata.m_basicVehicleClass);
        printf("====[test] simcan g_NetCanSimulate   m_event_HazardLights  %d ======\n", g_NetCanSimulate.m_canSimuData.m_u16exteriorLights);
        printf("====[test] simcan m_n32brakePedalStatus   %d ======\n", g_NetCanSimulate.m_canSimuData.m_n32brakePedalStatus);
        printf("====[test] simcan m_n32auxiliaryBrakeSystem   %d ======\n", g_NetCanSimulate.m_canSimuData.m_n32auxiliaryBrakeSystem);
    }
}

/*************************************************
  名称: FD_signal_of_net_sim_can_data_handler
  描述:　信号回调函数
  输入参数:
  返回值: 无
**************************************************/
static void FD_signal_of_net_Day2_data_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    int l_n32Len;
    uint8_t l_u8bcc = 0;
    uint8_t l_u8Msgbcc = 0;
    PadComand_st l_PadComanData;
    l_n32Len = pass->len; //获取接收数据长度
    l_u8Msgbcc = pass->data[l_n32Len - 1];

    printf(" VDS Receive NET Data:==\n ");
    for (int i = 0; i < l_n32Len; i++)
    {
        printf(" %02X ", pass->data[i]);
    }
    printf(" \n ");
    l_u8bcc = FD_CaluBcc(pass->data, l_n32Len - 1); //求bcc
    if (l_u8bcc != l_u8Msgbcc)
    {
        return;
    }
    else
    {
        memcpy(&l_PadComanData, pass->data, l_n32Len);
        printf(" INTENT %d  INTENTIME %d \n", l_PadComanData.choice.m_intent, l_PadComanData.choice.m_vaildtime);
        if (0xE8 == pass->data[4])
        {
            pthread_mutex_lock(&g_VDSVehFrameMutex); //加锁
            g_VdsVehFrame.m_vehdata.m_driveIntent.m_u8GSPAintent = pass->data[9];
            g_VdsVehFrame.m_vehdata.m_driveIntent.m_u32GSPAvaildtime = (uint32_t)(pass->data[10] | pass->data[11] | pass->data[12] | pass->data[13]);
            pthread_mutex_unlock(&g_VDSVehFrameMutex); //加锁
        }
        else if (0xA2 == pass->data[4])
        {
            pthread_mutex_lock(&g_VDSVehFrameMutex); //加锁
            g_VdsVehFrame.m_vehdata.m_driveIntent.m_u8CLCintent = pass->data[9];
            g_VdsVehFrame.m_vehdata.m_driveIntent.m_u32CLCvaildtime = (uint32_t)(pass->data[10] | pass->data[11] | pass->data[12] | pass->data[13]);
            pthread_mutex_unlock(&g_VDSVehFrameMutex); //加锁
        }
        else
        {
        }
    }
}
/*************************************************
  名称:    FD_signal_v2x_srv_msg_handler
  描述:　  接收V2X模块的 消息，只接收二期消息中的
  输入参数: dbus 传输参数
  返回值: 无
**************************************************/
static void FD_signal_v2x_srv_msg_handler(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
    uint8_t l_bcc = 0;
    uint32_t l_n32Len = 0;
    uint16_t l_msgtype = 0;
    uint16_t l_frametype = 0;
    uint32_t l_ExtMsgtype = 0;
    uint16_t l_u16playloadlen = 0;
    uint8_t *lpplayload = NULL;
    uint8_t l_U8RTCMnum = 0;
    uint8_t l_u8MsgBcc = 0;

    TV2xSrvMsg_t l_V2XMsg;

    if (MSG_MessageType_ID_Two != *((uint16_t *)&pass->data[6]))
    {
        LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "frame is not for Day2 !!");
        return;
    }

    l_n32Len = pass->len; //获取长度
    memcpy(&l_V2XMsg, pass->data, l_n32Len);
    l_u8MsgBcc = pass->data[l_n32Len - 1];

    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "========BsmMessageFrame:l_BsmMsg.m_msgBsm.messageid==========");

    l_msgtype = l_V2XMsg.m_Version;
    l_frametype = l_V2XMsg.m_AID;
    if ((MSG_MessageType_ID_Two == l_msgtype) && (WJV2_value_PR_RTCMcorrections == l_frametype))
    {
        l_ExtMsgtype = l_V2XMsg.m_V2xMessageFrame.MessageTwo.uniUperMsg.struFrameExt.enumpresent;
        if (WJV2_value_PR_RTCMcorrections == l_ExtMsgtype)
        {
            l_bcc = FD_CaluBcc(&l_V2XMsg, l_n32Len - 1); //求bcc
            if (l_bcc == l_u8MsgBcc)
            {
                //**Code  trans RTCM to F9P  -- callback **/
                l_U8RTCMnum = l_V2XMsg.m_V2xMessageFrame.MessageTwo.uniUperMsg.struFrameExt.choice.struRTCMcorrections.strucorrections.u8RTCMmsgNum;
                LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "RTCmnum: %d \n", l_U8RTCMnum);
                for (uint8_t i = 0; i < l_U8RTCMnum; i++)
                {
                    lpplayload = l_V2XMsg.m_V2xMessageFrame.MessageTwo.uniUperMsg.struFrameExt.choice.struRTCMcorrections.strucorrections.struRTCMmsg[i].strupayload.u8OCTRTCMPayload;
                    l_u16playloadlen = l_V2XMsg.m_V2xMessageFrame.MessageTwo.uniUperMsg.struFrameExt.choice.struRTCMcorrections.strucorrections.struRTCMmsg[i].strupayload.u16OCTRTCMPayloadNum;
                    Recv_DDS_Data_CallBack(lpplayload, l_u16playloadlen);
                }
            }
        }
    }
}

/*************************************************
  名称: vds_signal_monitor
  描述:　监听其他各节点的信号，注册回调函数
  输入参数:
  返回值: 无
**************************************************/
static void vds_signal_monitor(DBusGConnection *bus)
{
    DBusGProxy *app_object;
    DBusGProxy *sys_object;
    DBusGProxy *net_object;
    DBusGProxy *v2x_object;

    //连接APP节点
    app_object = dbus_g_proxy_new_for_name(bus, V2X_OBU_DBUS_APP_BUS_NAME, //节点名称
                                           V2X_OBU_DBUS_APP_OBJECT_PATH,   //节点路径
                                           V2X_OBU_DBUS_APP_INTFACE_NAME); //接口名称
    if (!app_object)
        printf("Failed to get name owner\n");
    //监听APP信号
    dbus_g_proxy_add_signal(app_object, MSG_APP_RESULT_ACT_SAFE, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(app_object, MSG_APP_RESULT_ACT_SAFE, G_CALLBACK(FD_signal_of_app_result_act_safe_handler), NULL, NULL);
    dbus_g_proxy_add_signal(app_object, MSG_APP_RESULT_TRFC_REMIND, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(app_object, MSG_APP_RESULT_TRFC_REMIND, G_CALLBACK(FD_signal_of_app_result_trfc_remind_handler), NULL, NULL);
    dbus_g_proxy_add_signal(app_object, MSG_APP_RESULT_SPD_GUIDE, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(app_object, MSG_APP_RESULT_SPD_GUIDE, G_CALLBACK(FD_signal_of_app_result_spd_guide_handler), NULL, NULL);
    dbus_g_proxy_add_signal(app_object, MSG_APP_SEND_CANDATA, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(app_object, MSG_APP_SEND_CANDATA, G_CALLBACK(FD_signal_of_app_candata_handler), NULL, NULL);
    //连接SYS节点
    sys_object = dbus_g_proxy_new_for_name(bus, V2X_OBU_DBUS_SYS_BUS_NAME, //节点名称
                                           V2X_OBU_DBUS_SYS_OBJECT_PATH,   //节点路径
                                           V2X_OBU_DBUS_SYS_INTFACE_NAME); //接口名称
    if (!sys_object)
        printf("Failed to get name owner\n");
    //监听SYS信号
    dbus_g_proxy_add_signal(sys_object, MSG_SYS_CONFIG_RQ, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(sys_object, MSG_SYS_CONFIG_RQ, G_CALLBACK(FD_signal_of_sys_config_rq_handler), NULL, NULL);
    dbus_g_proxy_add_signal(sys_object, MSG_SYS_MCU_PD_RQ, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(sys_object, MSG_SYS_MCU_PD_RQ, G_CALLBACK(FD_signal_of_sys_mcu_power_down_rs_handler), NULL, NULL);
    //连接NET节点
    net_object = dbus_g_proxy_new_for_name(bus, V2X_OBU_DBUS_NET_BUS_NAME, //节点名称
                                           V2X_OBU_DBUS_NET_OBJECT_PATH,   //节点路径
                                           V2X_OBU_DBUS_NET_INTFACE_NAME); //接口名称
    if (!net_object)
        printf("Failed to get name owner\n");
    //监听NET信号
    dbus_g_proxy_add_signal(net_object, MSG_NET_SIM_CAN_DATA, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(net_object, MSG_NET_SIM_CAN_DATA, G_CALLBACK(FD_signal_of_net_sim_can_data_handler), NULL, NULL);
    dbus_g_proxy_add_signal(net_object, MSG_NET_PAD_COMMAND, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(net_object, MSG_NET_PAD_COMMAND, G_CALLBACK(FD_signal_of_net_Day2_data_handler), NULL, NULL);

    //连接V2X节点
    v2x_object = dbus_g_proxy_new_for_name(bus, V2X_OBU_DBUS_V2X_BUS_NAME, //节点名称
                                           V2X_OBU_DBUS_V2X_OBJECT_PATH,   //节点路径
                                           V2X_OBU_DBUS_V2X_INTFACE_NAME); //接口名称
    if (!v2x_object)
        printf("Failed to get name owner\n");
    //监听V2X信号
    dbus_g_proxy_add_signal(v2x_object, MSG_V2X_SRV_MSG, DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal(v2x_object, MSG_V2X_SRV_MSG, G_CALLBACK(FD_signal_v2x_srv_msg_handler), NULL, NULL);
}