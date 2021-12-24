#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "general_config.h"


uint64_t CAN_timestamp = 0;
uint64_t GNSS_timestamp = 0;
int GnssLedState = 0xFF;
static double a = 6378245.0;
static double pi = 3.1415926535897932384626;
static double ee = 0.00669342162296594323;

uint32_t   g_DbusTrigFlag = 0x0;
uint32_t   g_VdsEncodeFlag = JSON_VALID;//上电后，允许重新读取静态配置信息。
uint8_t    g_Ag35CfgRqFlag = false;//ag35配置文件更新标志，将发送配置文件信息至ag35模块
uint8_t    g_McuCfgRqFlag = false;//mcu配置文件更新标志，将发送配置文件信息至mcu模块
uint8_t    g_McuCfgReportFlag = false;//mcu配置文件信息上报，将mcu当前配置信息上报至sys

uint8_t    g_VdsFaultStart = false;//故障检测有效标志，程序启动2秒后开始检测
uint32_t   g_lastVdsFaultFlag = false;//VDS故障是否有效标志(保留历史状态)
uint32_t   g_lastMcuFaultFlag = false;//MCU故障是否有效标志(保留历史状态)

/*MCU->AP:spi帧*/
TMcuStaCfgFrame          g_McuStateData;//mcu状态信息数据（下电请求、配置响应、版本号等）
TMcuVehFrame             g_McuVehData;//mcu车身运行数据
TMcuVsionFrame           g_McuVersionData;//mcu版本信息
/*ap->mcu*/
TAppNearCarFrame         g_AppNearCar1;//临车1(id:0x04)
TAppNearCarFrame         g_AppNearCar2;//临车2(id:0x05)
TAppNearCarFrame         g_AppNearCar3;//临车3(id:0x06)
TAppSpatFrame            g_AppSpatData;//红绿灯信息(id:0x07)
TAppOwnCarFrame          g_AppOwnCarData;//自车信息(id:0x08)
TMcuStaCfgFrame          g_McuConfigData;//mcu配置信息（id:0x09）
/*上行帧*/
TVdsVehFrame_st          g_VdsVehFrame;//车辆运行数据（gnss\imu\can\json）
TVdsStatePush_st         g_VdsStatePush;//vds状态推送数据（包括每个线程的运行状态：等待态、运行态）
TVdsFaultPush_st         g_VdsFaultPush;//vds故障推送数据（包括：gnss通讯故障、gnss数据异常故障、soc-mcu通讯故障、4G故障）
TMcuFaultPush_st         g_McuFaultPush;//mcu故障推送数据（包括：CAN_BUS_OFF、高压、低压）
TMcuPowerdownRq_st       g_McuPowerdownRq;//mcu掉电请求数据
TVdsConfigRs_st          g_VdsConfigRs;//vds在线配置文件更新响应数据（包括：vds配置文件更新响应、mcu配置文件更新响应）
TMcuConfigRs_st          g_McuConfigRs;//mcu当前配置信息上报至sys
//TExpactoryTestRs_st      g_ExpactoryTestRs;//产线出厂设置响应数据
/*下行帧*/
TSysPowerdownRs_st       g_SysPowerdownRs; //sys掉电响应数据
TSysConfigRq_st          g_SysConfigRq;//vds配置文件更新请求数据
TResultActSafe_st        g_ResultActSafe;//app功能安全输出数据
TResultTrfcRemind_st     g_ResultTrfcRemind;//app提醒消息数据
TResultSpdGuide_st       g_ResultSpdGuide;//app车身引导数据
//TMcuOnlineCfgRq_st       g_McuOnlineCfgRq;//mcu配置文件更新请求
TNetCanSimulate_st       g_NetCanSimulate;//can模拟数据
//TExpactoryTestRq_st      g_ExpactoryTestRq;//产线出厂设置请求数据





/********声明底层数据模块锁**********/
pthread_mutex_t          g_AG35Mutex = PTHREAD_MUTEX_INITIALIZER;//AG35数据访问锁，用于同步gnss,imu数据结构体

pthread_mutex_t          g_VDSVehFrameMutex = PTHREAD_MUTEX_INITIALIZER;//车辆运行数据同步锁
pthread_mutex_t          g_VDSConfigMutex = PTHREAD_MUTEX_INITIALIZER;//VDS静态配置文件同步锁
pthread_mutex_t          g_VDSStateMutex = PTHREAD_MUTEX_INITIALIZER;//VDS状态监控数据同步锁
pthread_mutex_t          g_VDSFaultMutex = PTHREAD_MUTEX_INITIALIZER;//VDS故障监控数据同步锁
pthread_mutex_t          g_VDSCfgRsMutex = PTHREAD_MUTEX_INITIALIZER;//VDS响应帧同步锁（vds配置文件更新响应、mcu配置文件更新响应）

pthread_mutex_t          g_MCUFaultMutex = PTHREAD_MUTEX_INITIALIZER;//MCU故障监控数据同步锁
pthread_mutex_t          g_MCUPdownMutex = PTHREAD_MUTEX_INITIALIZER;//MCU下电请求数据同步锁
pthread_mutex_t          g_MCUConfigMutex = PTHREAD_MUTEX_INITIALIZER;//MCU配置文件同步锁

pthread_mutex_t          g_APPRecvMutex = PTHREAD_MUTEX_INITIALIZER;//APP下发场景数据同步锁
/*mcu spi 传输锁*/
pthread_mutex_t          g_SpiRecvMutex = PTHREAD_MUTEX_INITIALIZER;//Spi接收缓冲区锁
pthread_mutex_t          g_SpiSendMutex = PTHREAD_MUTEX_INITIALIZER;//Spi发送缓冲区锁
pthread_mutex_t          g_SpiSyncTranMutex = PTHREAD_MUTEX_INITIALIZER;//Spi传输同步锁（spi触发传输与周期传输时，避免同时使用spi总线的情况）
pthread_cond_t           g_SpiSendCond = PTHREAD_COND_INITIALIZER;//定义spi发送线程条件变量

pthread_mutex_t          g_DbusTrigMutex = PTHREAD_MUTEX_INITIALIZER;//定义dbus触发发送锁
pthread_cond_t           g_DbusTrigCond = PTHREAD_COND_INITIALIZER;//定义dbus触发发送条件变量

pthread_mutex_t          g_EncodeTrigMutex = PTHREAD_MUTEX_INITIALIZER;//定义编码层触发编码互斥锁
pthread_cond_t           g_EncodeTrigCond = PTHREAD_COND_INITIALIZER;//定义编码层触发编码条件变量
/*************************************************
  名称: Pthread_MutexCond_Destroy
  描述: 互斥锁、条件变量注销
  输入参数:
  输出参数:
  返回值:  
**************************************************/
void FG_Pthread_MutexCond_Destroy(void)
{
    //gnss,IMU数据访问锁destroy
	if(0 != pthread_mutex_destroy(&g_AG35Mutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"GNSSMutex destroy failed");
    }
    //车辆运行数据同步锁destroy
	if(0 != pthread_mutex_destroy(&g_VDSVehFrameMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"VDSVehDataMutex destroy failed");
    }
    //VDS静态配置文件同步锁destroy
	if(0 != pthread_mutex_destroy(&g_VDSConfigMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"VDSConfigMutex destroy failed");
    }
    //VDS状态监控数据同步锁destroy
    if(0 != pthread_mutex_destroy(&g_VDSStateMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"VDSStateMutex destroy failed");
    }
    //VDS故障监控数据同步锁destroy
	if(0 != pthread_mutex_destroy(&g_VDSFaultMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"VDSFaultMutex destroy failed");
    }
    //VDS数据响应帧同步锁init
	if(0 != pthread_mutex_destroy(&g_VDSCfgRsMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"VDSCfgRsMutex destroy failed");
    }
    //MCU故障监控数据同步锁destroy
	if(0 != pthread_mutex_destroy(&g_MCUFaultMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"MCUFaultMutex destroy failed");
    }
    //MCU下电请求数据同步锁destroy
	if(0 != pthread_mutex_destroy(&g_MCUPdownMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"MCUPdownMutex destroy failed");
    }
    //MCU配置文件同步锁destroy
    if(0 != pthread_mutex_destroy(&g_MCUConfigMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"MCUConfigMutex destroy failed");
    }
     //SPI接收数据同步锁destroy
	if(0 != pthread_mutex_destroy(&g_SpiRecvMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"SpiRecvMutex destroy failed");
    }
    //SPI发送数据同步锁destroy
    if(0 != pthread_mutex_destroy(&g_SpiSendMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"SpiSendMutex destroy failed");
    }
    //SPI总线传输同步锁destroy
    if(0 != pthread_mutex_destroy(&g_SpiSyncTranMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"SpiSyncTranMutex destroy failed");
    }
    //dbus触发发送同步锁destroy
    if(0 != pthread_mutex_destroy(&g_DbusTrigMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"TrigSendMutex destroy failed");
    }
    //编码层触发编码同步锁destroy
    if(0 != pthread_mutex_destroy(&g_EncodeTrigMutex))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"EncodeTrigMutex destroy failed");
    }

    //mcu-spi发送触发条件变量destroy
	if(0 != pthread_cond_destroy(&g_SpiSendCond))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"SpiSendCond destroy failed");

    }
    //dbus事件触发发送条件变量destroy
	if(0 != pthread_cond_destroy(&g_DbusTrigCond))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"SpiSendCond destroy failed");

    }
    //编码层触发编码条件变量destroy
	if(0 != pthread_cond_destroy(&g_EncodeTrigCond))      
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"EncodeTrigCond destroy failed");

    }
}
/*************************************************
  名称: Struct_Init
  描述: 初始化dbus帧结构体参数，设置默认值
  输入参数:
  输出参数:Struct_Init
  返回值:  
**************************************************/
void FG_Vds_Struct_Init(void)
{
    
    // memset(&g_param_veh_info,0,sizeof(Tparam_veh_struct));
    // memset(&g_param_mcu_info,0,sizeof(Tparam_mcu_struct));

    /*vds车辆信息帧初始化*/
    memset(&g_VdsVehFrame.m_vehdata.m_vehId,0xff,sizeof(g_VdsVehFrame.m_vehdata.m_vehId));//17位车辆id
    memset(&g_VdsVehFrame.m_vehdata.m_candata_st,0,sizeof(g_VdsVehFrame.m_vehdata.m_candata_st));
    g_VdsVehFrame.m_vehdata.m_time = 0xFFFFFFFF;//获取车辆位置的时间 
    g_VdsVehFrame.m_vehdata.m_vehicleWidth = 0x0;//车辆宽度
    g_VdsVehFrame.m_vehdata.m_vehicleLength = 0x0;//车辆长度
    g_VdsVehFrame.m_vehdata.m_vehicleHeight = 0x0;//车辆高度
    g_VdsVehFrame.m_vehdata.m_basicVehicleClass = 0xFF;//车辆类型
    g_VdsVehFrame.m_vehdata.m_gpsdata_st.m_int_longitude = 0xFFFFFFFF;//车身纬度
    g_VdsVehFrame.m_vehdata.m_gpsdata_st.m_int_latitude = 0xFFFFFFFF;//车身经度
    g_VdsVehFrame.m_vehdata.m_gpsdata_st.m_int_altitude = -4096;//车身海拔
    g_VdsVehFrame.m_vehdata.m_gpsdata_st.m_int_altitude = 255;//定位系统精度
    g_VdsVehFrame.m_vehdata.m_gpsdata_st.m_dbl_heading = 0xFFFF;//航向角
    g_VdsVehFrame.m_vehdata.m_gpsdata_st.m_dbl_speed = 8191;//车辆速度
    g_VdsVehFrame.m_vehdata.m_int_acclng = 2001;//纵向加速度
    g_VdsVehFrame.m_vehdata.m_int_yawrate = 0xFFFF;//横摆角加速度

    memset(&g_VdsStatePush,0xff,sizeof(TVdsStatePush_st));//vds状态推送帧默认值
    // memset(&g_McuPowerdownRq,0xff,sizeof(TMcuPowerdownRq_st));//mcu下电请求帧默认值
    // memset(&g_VdsConfigRs,0xff,sizeof(TVdsConfigRs_st));//vds配置响应帧默认值
    //故障数据帧默认值，故障无效
    g_VdsFaultPush.m_fault.m_CanInitFault = FAULT_INVALID;
    g_VdsFaultPush.m_fault.m_gnssDataFault = FAULT_INVALID;
    g_VdsFaultPush.m_fault.m_GpsAG15Fault = FAULT_INVALID;
    g_VdsFaultPush.m_fault.m_GpsInitFault = FAULT_INVALID;
    g_VdsFaultPush.m_fault.m_GpsRTKFault = FAULT_INVALID;
    g_VdsFaultPush.m_fault.m_reserverFault = FAULT_INVALID;
    
    // memset(&g_SysPowerdownRs,0,sizeof(TSysPowerdownRs_st));//sys下电响应
    // memset(&g_SysConfigRq,0,sizeof(TSysConfigRq_st));//sys配置请求
    // memset(&g_ResultActSafe,0,sizeof(TResultActSafe_st));//app功能安全场景输出
    // memset(&g_ResultTrfcRemind,0,sizeof(TResultTrfcRemind_st));//app交通标志事件提醒
    // memset(&g_ResultSpdGuide,0,sizeof(TVdsVehData_st));//车速引导信息事件提醒
    // memset(&g_NetCanSimulate,0,sizeof(TNetCanSimulate_st));//模拟can数据

    // memset(&g_McuVehData,0,sizeof(TMcuVehFrame));//mcu车身运行数据(id:0x1)
    // memset(&g_McuVersionData,0,sizeof(TMcuVsionFrame));//mcu版本信息(id:0x3)
    // memset(&g_McuStateData,0,sizeof(TMcuStaCfgFrame));//mcu状态信息(id:0x2)
    // g_McuStateData.m_cfgData.m_faultInfo = 0xff;//mcu故障标志位，0：有故障，1：无故障，初始值：无故障

    // memset(&g_AppNearCar1,0,sizeof(TAppNearCarFrame));//临车1(id:0x04)
    // memset(&g_AppNearCar2,0,sizeof(TAppNearCarFrame));//临车2(id:0x05)
    // memset(&g_AppNearCar3,0,sizeof(TAppNearCarFrame));//临车3(id:0x06)
    // memset(&g_AppSpatData,0,sizeof(TAppSpatFrame));//红绿灯信息(id:0x07)
    // memset(&g_AppOwnCarData,0,sizeof(TAppOwnCarFrame));//自车信息(id:0x08)
    // memset(&g_McuConfigData,0,sizeof(TMcuStaCfgFrame));//mcu配置信息（id:0x09）
	// g_AppNearCar1.m_msgId = 0x04;
	// g_AppNearCar1.m_msglength = APP_NEARCAR_DATA_LEN;
	// g_AppNearCar2.m_msgId = 0x05;
	// g_AppNearCar2.m_msglength = APP_NEARCAR_DATA_LEN;
	// g_AppNearCar3.m_msgId = 0x06;
	// g_AppNearCar3.m_msglength = APP_NEARCAR_DATA_LEN;
	// g_AppSpatData.m_msgId = 0x07;
	// g_AppSpatData.m_msglength = APP_SPAT_DATA_LEN;
    // g_AppOwnCarData.m_msgId = 0x08;
	// g_AppOwnCarData.m_msglength = APP_OWNCAR_DATA_LEN;
    // g_McuConfigData.m_cfgData.m_powerInfo = 0x02;
    // g_McuConfigData.m_msgId = 0x09;
	// g_McuConfigData.m_msglength = MCU_STATE_DATA_LEN;
}
/*************************************************
  名称: FD_CaluBcc
  描述: 求异或 BCC 校验
  输入参数: p_ptValue，数据首指针，p_length校验数据长度
  返回值: bcc
**************************************************/
uint8_t FD_CaluBcc(void *p_ptValue,uint32_t p_length)
{
    uint8_t *l_bcc,bcc = 0;
    l_bcc =(uint8_t *)p_ptValue;
    //求bcc
    for(uint32_t cnt = 0;cnt < p_length; cnt++)
    {
      bcc ^= *l_bcc++;
    } 
    return bcc;
}
/*************************************************
  名称: milliseconds_sleep
  描述: 毫秒级定时器
  输入参数: mSec 毫秒数
  返回值: 无
**************************************************/
void milliseconds_sleep(unsigned long mSec){
    struct timeval tv;
    tv.tv_sec=mSec/1000;
    tv.tv_usec=(mSec%1000)*1000;
    int err;
    do{
       err=select(0,NULL,NULL,NULL,&tv);
    }while(err<0 && errno==EINTR);
}
/*************************************************
  名称: Gprintf_buf
  描述: 数据打印输出
  输入参数: 
        p_buf:数据区
        p_len:数据长度
        p_name:数据名，
        p_type:0-16禁止，1-十进制,
        p_line:一行占多少数据
  返回值: 无
**************************************************/
void Gfprintf(uint8_t *p_buf,uint32_t p_len,char *p_name,uint8_t p_scale,uint8_t p_lineNum)
{ 
  int cnt = 0;
  printf("\nGf:%s:----------------start-printf-------------------\n",p_name);
  printf("Gf:");
  for(cnt=0;cnt<p_len;cnt++)
  {
    if(p_scale)
    {
      printf("%d ",*p_buf++);
    }
    else
    {
      printf("%x ",*p_buf++);
    }
    if (!(cnt % p_lineNum) && cnt != 0)		//p_lineNum个数据为一簇打印
    {
      puts("");
      printf("Gf:");
    }  
  }
  printf("\nGf:%s:----------------end-printf-------------------\n\n",p_name); 
}

/************************经纬度偏转*******************************/
//
void toGCJ02Point(double longitude, double latitude,  double *retLon,double *retLat) 
{
    calDev(latitude, longitude, retLon, retLat);
    *retLat = latitude + *retLat;
    *retLon = longitude + *retLon;
}
//
void calDev(double wgLat, double wgLon, double *dLon,double *dLat)
{
    if (isOutOfChina(wgLat, wgLon, dLon, dLat))
    {
        return;
    }
    printf("step1\n");
    *dLat = calLat(wgLon - 105.0, wgLat - 35.0);
    *dLon = calLon(wgLon - 105.0, wgLat - 35.0);

    double radLat = wgLat / 180.0 * pi;
    double magic = sin(radLat);
    magic = 1 - ee * magic * magic;
    double sqrtMagic = sqrt(magic);
    *dLat = (*dLat * 180.0) / ((a * (1 - ee)) / (magic * sqrtMagic) * pi);
    *dLon = (*dLon * 180.0) / (a / sqrtMagic * cos(radLat) * pi);
}
//
bool isOutOfChina(double lat, double lon, double *dLon,double *dLat)
{
    if (lon < 72.004 || lon > 137.8347)
    {
        *dLon = 0;
        *dLat = 0;
        return true;
    }
    if (lat < 0.8293 || lat > 55.8271)
    {
        *dLon = 0;
        *dLat = 0;
        return true;
    }
    return false;
}
//
double calLat(double x, double y)
{
    double ret = -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * sqrt(abs(x));
    ret += (20.0 * sin(6.0 * x * pi) + 20.0 * sin(2.0 * x * pi)) * 2.0 / 3.0;
    ret += (20.0 * sin(y * pi) + 40.0 * sin(y / 3.0 * pi)) * 2.0 / 3.0;
    ret += (160.0 * sin(y / 12.0 * pi) + 320 * sin(y * pi / 30.0)) * 2.0 / 3.0;
    return ret;
}
//
double calLon(double x, double y)
{
    double ret = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * sqrt(abs(x));
    ret += (20.0 * sin(6.0 * x * pi) + 20.0 * sin(2.0 * x * pi)) * 2.0 / 3.0;
    ret += (20.0 * sin(x * pi) + 40.0 * sin(x / 3.0 * pi)) * 2.0 / 3.0;
    ret += (150.0 * sin(x / 12.0 * pi) + 300.0 * sin(x / 30.0 * pi)) * 2.0 / 3.0;
    return ret;
}