/*
 * @Descripttion: 
 * @version: 
 * @Author: wanji.net.cn
 * @email: mk_wanji@126.com
 * @Date: 2021-11-13 15:36:47
 * @LastEditors: VanJee Technology Co.,Ltd
 * @LastEditTime: 2021-12-09 16:59:03
 */
/*******************************************************************************
 * 文 件 名 称 ： main.cpp
 * 功 能 描 述 ： NET模块主进程
 * 开 发 人 员 ： GongMinghao
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2021-08-18 V1.0    GongMinghao   Create
 *
 * @Copyright (C)  2021  .wanji. all right reserved
*******************************************************************************/
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>
#include "Config/net_log.h"
#include "Dbus/net_dbus.h"
#include "Net/net_data_send.h"
#include "Net/net_tcp_server.h"
#include "Net/net_udp_client.h"
#include "Net/net_udp_server.h"
#include "Config/SWversynchronise.h"
#include "Dbus/dbus_data_type.h"
#include "TongZhou/inc/app_lst.h"
#include "Config/Net_Json.h"

#define NET_SOFTVERSION "WJ_OBU_NET_20210831"
TMsgVehDataFrame_t g_tDbusVehDataFrame;
VehMapMatchInfo g_tVehMapMatchInfo;
void AllThreadStart()
{
    //Can数据初始化
    F2 l_veh;
    l_veh = init_F2();
    FN_WriteCanDataJson(l_veh);
    //dbus C语言的所以在这里起线程
    std::thread l_tNetDbus(NetDbusRecvThread);
    if (l_tNetDbus.joinable())
        l_tNetDbus.detach();

    //其余全部文件内部起线程
    NetTcpServerInit();
    NetDataSendInit();
    NetUdpClientInit();
    Cloud_Platform_TZ();
}

int main()
{
    uint32_t ret = 0;
    //初始化LOG
    ret = LogInit();
    if (ret == 0)
    {
        LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "main LogInit is success");
    }
    else
    {
        LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "main LogInit is failed");
    }

    //软件版本号同步
    ret = SW_versionsync(LOG_MODLE_NAME, NET_SOFTVERSION);
    LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "main software synchonise result %d", ret);

    //启动全部线程
    AllThreadStart();

    while (g_flag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    //关闭日志
    LogDeinit();

    return 0;
}
