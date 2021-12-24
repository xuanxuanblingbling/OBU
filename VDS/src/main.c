#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include "general_config.h"
#include "vds_decode.h"
#include "vds_dbus.h"
#include "locate.h"
#include "app_queue.h"
#include "v2x_obu_dbus_common.h"
#include "./GPSInterface/GPS-M.h"
#include "SWversynchronise.h"


#define VDS_SOFTVERSION  "WJ_OBU_VDS_20210831"

/**/
void faultCheckStart() 
{ 
  g_VdsFaultStart = true;
  LogPrint(LOG_LEVEL_INFO,MODULE_NAME,"Vds Fault Check start up,g_VdsFaultStart is %d",g_VdsFaultStart);
}
/*************************************************
  名称:main
  描述: 
  输入参数:
  输出参数:
  返回值:  
**************************************************/
int main(int argc, char *argv[])
{
    signal(SIGALRM, faultCheckStart);//创建定时器，2s后启动故障检查
    alarm(FAULE_CHECK_VALID_TIMER);//启动定时器
     

    FG_Vds_Struct_Init();//结构体变量初始化
    //zlog初始化
    if(0 != LogInit())
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"log module init failed");
        return -1;
    }
    
    //软件版本号同步
    int ret = 0;
    ret = SW_versionsync(MODULE_NAME, VDS_SOFTVERSION);
    LogPrint(LOG_LEVEL_INFO,MODULE_NAME,"software synchonise result %d ",ret);


    //车辆配置信息
    if(0 != param_veh_parse(VDS_CONFIG_FILE_NAME, &g_param_veh_info))
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME, "config file %s parse failed", VDS_CONFIG_FILE_NAME);
        goto EXIT;
    }   
    
    FD_DbusModuleCreat();//dbus模块创建
    //GPS模块
    if(RetTure != GPSMSTART())
    {
        g_VdsFaultPush.m_fault.m_GpsInitFault = FAULT_VALID;
        DbusGeneralSendFuc((uint8_t*)&g_VdsFaultPush,sizeof(g_VdsFaultPush),VDS_FAULT_PUSH);
    }

    //CAN模块初始化
    if(0 > CAN_Init())
    {
        g_VdsFaultPush.m_fault.m_CanInitFault = FAULT_VALID;
        DbusGeneralSendFuc((uint8_t*)&g_VdsFaultPush,sizeof(g_VdsFaultPush),VDS_FAULT_PUSH);     
    }
    

    while(1)
    {
        uint8_t buf[sizeof(TAppQueueMember)] = {0,};
        TAppQueueMember l_AppQueueMember;
        memset(&l_AppQueueMember,0,sizeof(TAppQueueMember));
        if(FD_AppQueueEmpty(&g_app_recv_queue)==SUCCESS)
        {
            printf("app recv queue is empty\n");
        }       
        milliseconds_sleep(1000);
    }
    FG_Pthread_MutexCond_Destroy();//销毁全局定义锁、条件变量
EXIT:
    LogDeinit();
    return 0;
}
