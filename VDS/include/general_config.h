#ifndef _GENERAL_CONFIG
#define _GENERAL_CONFIG

#include "obu_config.h"
#include "wj_log.h"
#include "param_parse.h"
#include "vds_decode.h"
#include "locate.h"
#include "GPS.h"
#include "vds_dbus.h"

#define MODULE_NAME "VDS"   //用于zlog输出
#define RetTure  0   
#define ReError  1   
typedef unsigned char  uint8;     /* 无符号8位整型变量  */


typedef enum{
    GnssAG15Normal = 130,
	GnssAG15FAULT,
	GnssRTKNormal = 140,
	GnssRTKFAULT
};


typedef enum{
	RTKE1 = 0x10,
	RTKE2 = 0X20,
    RTKE4 = 0x60,
	RTKE5 = 0x50
};

typedef enum
{
	SUCCESS=0,
	ERROR=1,
	
	/*queue error*/
	QUEUE_EMPTY_ERROR=20,
	QUEUE_FULL_ERROR,
	LINK_LOCK_ERROR,
	QUEUE_REMOVE_ERROR,
	QUEUE_INSERT_ERROR,

	DRIVER_SEND_ERROR,
}EtRetstatus;

typedef struct _GNSS_State_Type
{
	uint8 LEDState;
    uint8 GNSSFaultState;  
}GNSS_State_Type;
typedef struct _GNSS_CAN_State_Type
{
	GNSS_State_Type GnssState;
    uint8             CANFaultState;  
}GNSS_CAN_State_Type;

#define Green_LED_Twinking 0u
#define Green_LED_Bright 1u
#define Red_LED_Bright 2u
#define Green_LED_FastTwinking 3u

#define AG15_GNSS_Fault 0x10 
#define RTK_GNSS_Fault 0x20 
#define GNSS_Normal_State  0u


#define FAULE_CHECK_VALID_TIMER  2//故障检测开始时间，程序启动2秒后
#define EVENT_REPEAT_CYCLE_TIME  100//Event Repate事件触发后的推送时间(ms)
#define EVENT_REPEAT_PUSH_NUM    5//Event Repate事件触发后的推送次数

/*故障监控*/
#define FAULT_VALID        0x81//故障有效值
#define FAULT_INVALID      0x80//故障无效值
/*VDS故障：用于记录各种故障当前状态*/
#define AG35_COM_FAULT     0x01
#define GNSS_COM_FAULT     0x02
#define GNSS_DATA_FAULT    0x04
#define IMU_COM_FAULT      0x08
#define MCU_COM_FAULT      0x10
#define V4G_COM_FAULT      0x20 
/*MCU故障：用于记录各种故障当前状态*/  
#define HIGH_VAL_FAULT     0x01
#define LOW_VAL_FAULT      0x02
#define CAN_BUSOFF_FAULT   0x04

#define SYS_CFGRq_VDS	   0X80
#define SYS_CFGRq_MCU	   0X81
#define SYS_CFGRq_AG35	   0X82
#define SYS_CFGGt_MCU	   0X83//sys主动获取mcu配置信息

#define VDS_CFGRs_SUCESS   0X90//VDS配置更新响应成功
#define VDS_CFGRs_FAILE    0X91//VDS配置更新响应失败
#define MCU_CFGRs_SUCESS   0X90//MCU配置更新响应成功
#define MCU_CFGRs_FAILE    0X91//MCU配置更新响应失败
#define AG35_CFGRs_SUCESS  0X90//AG35配置更新响应成功
#define AG35_CFGRs_FAILE   0X91//AG35配置更新响应失败
/*
 * 描述：dbus事件监控标志
 * bit0:can车身预警事件  
 * bit1:vds故障  
 * bit2:mcu故障  
 * bit3:mcu下电请求  
 * bit4:mcu在线配置响应  
 * bit5:vds配置文件更新响应  
 * bit6:出厂测试响应
*/
#define VDS_VDATA   0x01
#define VDS_FAULT   0x02
#define MCU_FAULT   0x04
#define MCU_PDOWN   0x08
#define VDS_CFG_RS  0x10

#define NormalTimePeriod  1000*30 //30S

extern uint32_t                 g_DbusTrigFlag;	

/*
 * 描述：vds编码有效标志
 * bit0:can数据有效  
 * bit1:gnss/imu数据有效  
 * bit2:veh静态配置文件更新  
*/
#define CAN_VALID    0x01
#define AG35_VALID   0x02
#define JSON_VALID   0x04
extern uint32_t                 g_VdsEncodeFlag;
extern uint8_t                  g_Ag35CfgRqFlag;//ag35配置信息更新有效，通知定位模块发送信息至ag35
extern uint8_t                  g_McuCfgRqFlag;//mcu配置文件更新标志，将发送配置文件信息至mcu模块
extern uint8_t                  g_McuCfgReportFlag;//上报mcu当前配置信息至sys

extern uint8_t                  g_VdsFaultStart;//故障检测有效标志，程序启动2秒后开始检测
extern uint32_t                 g_lastVdsFaultFlag;//故障是否有效标志(保留历史状态)
extern uint32_t                 g_lastMcuFaultFlag;//MCU故障是否有效标志(保留历史状态)
/*mcu->ap*/
extern  TMcuVehFrame            g_McuVehData;//mcu车身运行数据(id:0x01)
extern  TMcuStaCfgFrame         g_McuStateData;//mcu状态信息数据（id:0x02）
extern  TMcuVsionFrame          g_McuVersionData;//mcu版本信息(id:0x03)
/*ap->mcu*/
extern  TAppNearCarFrame        g_AppNearCar1;//临车1(id:0x04)
extern  TAppNearCarFrame        g_AppNearCar2;//临车2(id:0x05)
extern  TAppNearCarFrame        g_AppNearCar3;//临车3(id:0x06)
extern  TAppSpatFrame           g_AppSpatData;//红绿灯信息(id:0x07)
extern  TAppOwnCarFrame         g_AppOwnCarData;//自车信息(id:0x08)
extern  TMcuStaCfgFrame         g_McuConfigData;//mcu配置信息（id:0x09）

/*dbus上行帧*/
extern TVdsVehFrame_st          g_VdsVehFrame;
extern TVdsStatePush_st         g_VdsStatePush;
extern TVdsFaultPush_st         g_VdsFaultPush;
extern TMcuFaultPush_st         g_McuFaultPush;
extern TMcuPowerdownRq_st       g_McuPowerdownRq;
extern TVdsConfigRs_st          g_VdsConfigRs;
extern TMcuConfigRs_st          g_McuConfigRs;
//extern TExpactoryTestRs_st      g_ExpactoryTestRs;
/*dbus下行帧*/
extern TSysPowerdownRs_st       g_SysPowerdownRs;
extern TSysConfigRq_st          g_SysConfigRq;
extern TResultActSafe_st        g_ResultActSafe;
extern TResultTrfcRemind_st     g_ResultTrfcRemind;
extern TResultSpdGuide_st       g_ResultSpdGuide;
//extern TMcuOnlineCfgRq_st       g_McuOnlineCfgRq;
extern TNetCanSimulate_st       g_NetCanSimulate;
//extern TExpactoryTestRq_st      g_ExpactoryTestRq;

extern uint64_t CAN_timestamp ;
extern uint64_t GNSS_timestamp ;
extern int GnssLedState ;


/********声明文件读写锁**********/
extern pthread_mutex_t g_VDSCfgMutex;//vds车辆静态配置同步锁
extern pthread_mutex_t g_MCUCfgMutex;//MCU在线配置同步锁

/********声明底层数据模块读写锁**********/
extern pthread_mutex_t g_AG35Mutex;

extern pthread_mutex_t g_VDSVehFrameMutex;//车辆运行数据同步锁
extern pthread_mutex_t g_VDSConfigMutex;//VDS静态配置文件同步锁
extern pthread_mutex_t g_VDSStateMutex;//VDS状态监控数据同步锁
extern pthread_mutex_t g_VDSFaultMutex;//VDS故障监控数据同步锁
extern pthread_mutex_t g_VDSCfgRsMutex;//VDS响应帧同步锁（vds配置文件更新响应、mcu配置文件更新响应）

extern pthread_mutex_t g_MCUFaultMutex;//MCU故障监控数据同步锁
extern pthread_mutex_t g_MCUPdownMutex;//MCU下电请求数据同步锁
extern pthread_mutex_t g_MCUConfigMutex;//MCU配置文件同步锁

extern pthread_mutex_t g_APPRecvMutex;//APP下发场景数据同步锁
/*extern pthread_mutex_t SYSExptestMutex;//出厂测试
extern pthread_mutex_t APPActSafeMutex;//
extern pthread_mutex_t APPTrfcRemindMutex;//
extern pthread_mutex_t APPSpdGuideMutex;//
extern pthread_mutex_t NETCanSimulateMutex;//*/

/********synchronization mechanism**********/
extern pthread_mutex_t g_SpiRecvMutex;//Spi接收缓冲区互斥锁
extern pthread_mutex_t g_SpiSendMutex;//Spi发送缓冲区互斥锁
extern pthread_mutex_t g_SpiSyncTranMutex;//Spi传输同步锁（spi触发传输与周期传输时，避免同时使用spi总线的情况）
extern pthread_cond_t  g_SpiSendCond;//定义spi发送线程条件变量

extern pthread_mutex_t g_DbusTrigMutex;//定义dbus触发发送锁
extern pthread_cond_t  g_DbusTrigCond;//定义dbus触发事件信号发送条件变量

extern pthread_mutex_t g_EncodeTrigMutex;//定义编码层触发编码互斥锁
extern pthread_cond_t  g_EncodeTrigCond;//定义编码层触发编码条件变量

/**************function define*********/
extern void FG_Pthread_MutexCond_Init(void);
extern void FG_Pthread_MutexCond_Destroy(void);
extern void FG_Vds_Struct_Init(void);
extern uint8_t FD_CaluBcc(void *p_ptValue,uint32_t p_length);//计算器校验值
extern void milliseconds_sleep(unsigned long mSec);//毫秒级延时
extern void Gfprintf(uint8_t *p_buf,uint32_t p_len,char *p_name,uint8_t p_scale,uint8_t p_lineNum);
//偏转算法
extern void toGCJ02Point(double longitude, double latitude,  double *retLon,double *retLat);
extern void calDev(double wgLat, double wgLon, double *dLon,double *dLat);
extern bool isOutOfChina(double lat, double lon, double *dLon,double *dLat);
extern double calLat(double x, double y);
extern double calLon(double x, double y);

#endif