#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h> 
#include "general_config.h"
#include "wj_log.h"
#include "locate.h"

TLOCATE_Data	 g_Location_Data;
/*************************************************
  名称：GnssFaultDetect
  描述：ag35故障信息检查函数，无故障：0X80,有故障：0X81
  输入参数: p_Ag35Falut_Data:ag35故障信息
  输出参数：
  返回值：无
 * ************************************************/
static void GnssFaultDetect(void)
{
   
}
/*************************************************
  名称：FL_Ag35DataEncode
  描述：ag35数据解析
  输入参数: l_sockbuf:从ag35获取到的数据 【Tag+len+data+bcc】
  输出参数：
  返回值：无
 * ************************************************/
static int FL_Ag35DataEncode(void)
{
    
}
/*************************************************
  名称：GnssThreadFun
  描述：Gnss线程回调，执行Gnss模块基本功能。
  输入参数: 
  输出参数：
  返回值：无
 **************************************************/
static void *GnssThreadFun(void* arg)
{
    
}
/***********************************************************
 * *function：Gnss模块初始化
 * *parameter:{void}
************************************************************/
void FL_GnssModuleCreat(void)
{
    pthread_t gnss_id = 0;
    pthread_attr_t gnss_attr = {0};

    pthread_attr_init(&gnss_attr);
    pthread_attr_setdetachstate(&gnss_attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&gnss_id, &gnss_attr, GnssThreadFun,NULL);
    pthread_attr_destroy(&gnss_attr);
}