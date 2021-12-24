/*
 * @Descripttion: 
 * @version: 
 * @Author: wanji.net.cn
 * @email: mk_wanji@126.com
 * @Date: 2021-11-11 20:48:02
 * @LastEditors: VanJee Technology Co.,Ltd
 * @LastEditTime: 2021-12-04 11:33:42
 */
#ifndef __APP_EMPTY_FUNCTION_H__
#define __APP_EMPTY_FUNCTION_H__

#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "Config/net_log.h"
#include "Config/file.h"
#include "Dbus/dbus_data_type.h"
#include "Config/cJSON.h"
#include "Net/net_mqtt_client.h"
#include "TongZhou/inc/wanji_v2x_obu_V1.2.pb-c.h"

#define LOG_EMPTY_FUN "empty_function"
#define OBU_INFO_FILE "/mnt/APP/Config/obu/net/Config_OBUInfo.ini"
#define IS_OK 0
#define IS_ERR 1

/********************** 宏定义 *************************************/
#define LOG_MODULE_NAME_APP_LST "app_lst"
#define NAT_FTOK_PATH "/tmp" // 已存在路径，生成IPC键值
#define NAT_FTOK_ID 20       // 生成键值所需的ID号
#define FREE_CONSTANT(ptr) \
    ({                     \
        if (ptr)           \
        {                  \
            free(ptr);     \
            ptr = NULL;    \
        }                  \
    })

#define MAX_NAMELENG_SEM 20 // 有名信号量名称最大长度
#define MAX_NETCARD 20      // 最大网卡数量
#define MAX_PERIPHERAL 10   // 最大连接外设的数量
#define MAX_V2XRAWDATA 5000

#define INTERVAL 100 //发送时间间隔100ms
/********************** 类型重定义 **********************************/
typedef unsigned char uint8;       /* 无符号8位整型变量  */
typedef signed char int8;          /* 有符号8位整型变量  */
typedef unsigned short uint16;     /* 无符号16位整型变量 */
typedef short int16;               /* 有符号16位整型变量 */
typedef unsigned int uint32;       /* 无符号32位整型变量  */
typedef int int32;                 /* 有符号32位整型变量  */
typedef unsigned long long uint64; /* 无符号64位整型变量  */
typedef long long int64;           /* 有符号64位整型变量  */
typedef float fp32;                /* 单精度浮点数（32位长度）*/
typedef double fp64;               /* 双精度浮点数（64位长度）*/

typedef char *LPSTR;
typedef const char *LPCSTR;
typedef unsigned long DWORD;
typedef int BOOL;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned char BYTE;

/********************** 类型重定义 **********************************/

typedef enum CONFIGURATION
{
    ISSUE_CONFIGURATION = 1,
    INQUIRE_CONFIGURATION = 2
} CONFIGURATION_t;
/***************************MQTT Payload*********************************/
typedef struct Payload
{
    uint32_t m_u32Sequence;                 //序列号
    uint64_t m_u64Timestamp;                //UTC时间戳，单位毫秒
    uint8_t m_u8V2xRawData[MAX_V2XRAWDATA]; //V2X相关数据
} Payload_t;
typedef struct Mqtt_Payload
{
    // uint8_t m_u8Preamble;        //0xAE前向引导字符
    // uint8_t m_u8Preamble1;       //0x71前向引导字符
    uint8_t m_u8Class; //payload的标志，可作为消息类型以及版本控制信息来使用
    uint8_t m_u8ID;    //payload的标志，可作为消息类型以及版本控制信息来使用
    // uint16_t m_u16PayloadLength; //payload内通的长度
    Payload_t l_Payload; //报文体，包含：4字节的序列号哦呵，8字节以毫秒为单位的UTC时间戳（表征V2X原始数据产生的时间），以及V2X相关数据
    // uint16_t m_u16Checksum;      //校验和字段，校验内容包括：class,id,payloadlength以及payload

} Mqtt_Payload_t;

// 模块注册标志位
enum SUPERVISION_REGISTER_TYPE
{
    REGISTER_CANCEL = 0, // 取消注册
    REGISTER_CONFIRM     // 注册
};

// 消息队列消息类型
enum SUPERVISION_MSG_TYPE
{
    QUEMSG_REGISTER = 1,   // 注册消息
    QUEMSG_CYCLE_STATUS,   // 模块周期性监控状态消息
    QUEMSG_RUNTIME_STATUS, // 模块运行时监控状态消息
};

// 被监控的模块名
enum MODULE_TYPE
{
    MODULE_RSUBASEINFO = 1, // RSU基本信息
    MODULE_RSURUNTIMEINFO,  // RSU运行时状态信息
    MODULE_NETCOMM,         // 网络通信模块
    MODULE_MSGADAPTER,      // 外设消息标准化模块
    MODULE_V2XSTACK,        // V2X协议栈模块
    MODULE_SAFETYCERT,      // 安全证书模块
    MODULE_GNSSLOCATION,    // GNSS定位模块
    MODULE_DATABASE,        // 数据库模块
    MODULE_DEVMANAGE,       // 设备管理模块
};

/*****************************RSU系统基本信息**************************/
// RSU基本信息
typedef struct _TRsuBaseInfo
{
    uint8 m_u8RsuID[4];       // 设备ID，0x01020304
    int8 m_n8RsuSN[16];       // 设备SN号，913A201700000001
    int8 m_n8WifiIP[50];      // wifi-IP地址
    int8 m_n8WifiMAC[50];     // wifi-MAC地址
    int8 m_n8WifiGateway[50]; // wifi-网关
    int8 m_n8WifiNetMask[50]; // wifi-子网掩码
    int8 m_n8GEIP[50];        // 千兆电口-IP地址
    int8 m_n8GEMAC[50];       // 千兆电口-MAC地址
    int8 m_n8GEGateway[50];   // 千兆电口-网关
    int8 m_n8GENetMask[50];   // 千兆电口-子网掩码
    int8 m_n8GFIP[50];        // 千兆光口-IP地址
    int8 m_n8GFMAC[50];       // 千兆光口-MAC地址
    int8 m_n8GFGateway[50];   // 千兆光口-网关
    int8 m_n8GFNetMask[50];   // 千兆光口-子网掩码
    int8 m_n84GSIM[50];       // 4G-SIM卡号
    int8 m_n8IMEI[50];        // 4G-IMEI
    int8 m_n8IMSI[50];        // 4G-IMSI
} TRsuBaseInfo;

/*************************RSU系统运行时状态信息**************************/
// CPU利用率统计结构体
typedef struct _TCpuUsage
{
    double m_fp64user;
    double m_fp64system;
    double m_fp64nice;
    double m_fp64idle;
} TCpuUsage;

// 内存利用率统计结构体  单位kB
typedef struct _TMemUsage
{
    uint32 m_u32total;
    uint32 m_u32used;
    uint32 m_u32free;
    uint32 m_u32shared;
    uint32 m_u32buffers;
    uint32 m_u32cached;
} TMemUsage;

// 磁盘利用率统计结构体
typedef struct _TDiskUsage
{
    uint8 m_u8RWD;
    uint8 m_u8APP;
    uint8 m_u8USERDATA;
    uint8 m_u8kernel;
} TDiskUsage;

// RSU系统运行时状态信息
typedef struct _TRsuRuntimeInfo_Cycle
{
    float m_fp32DevTemperature;   // 设备温度
    float m_fp32Devhumidity;      // 设备湿度
    TCpuUsage m_tCpuUsage;        // CPU占用率
    TMemUsage m_tMemUsage;        // 内存占用率
    TDiskUsage m_tDiskUsage;      // 磁盘占用率
    uint8 m_u8SoftwareResetTimes; // 软件复位次数
    uint8 m_u8WdogResetTimes;     // 看门狗复位次数
    uint8 m_u8PORResetTimes;      // 掉电复位次数
} TRsuRuntimeInfo_Cycle;

/******************************注册类消息******************************/
// 注册消息结构体
typedef struct _TRegisterMsgQue
{
    long m_n64MsgType;                   // 消息类型 0-注册消息，1-设备周期性状态消息，2-设备运行时状态消息
    uint8 m_u8RegisterFlag;              // 注册标志位，0-注销注册，1-注册
    int8 m_na8SemName[MAX_NAMELENG_SEM]; // 信号量的名称
    sem_t *m_pSemId;                     // 信号量ID
} TRegisterMsgQue;

/*************************RSU模块周期性状态监控结构体********************/
// 网络通信模块状态
typedef struct _TNetCardInfo
{
    int8 m_n8NetCardName[20];     // 网卡名称
    uint8 m_u8NetCardConntStatus; // 网卡开关状态 0-关；1-开
    uint64 m_u64RX;               // 网卡接收流量
    uint64 m_u64RP;               // 网卡接收的数据包
    uint64 m_u64TX;               // 网卡发送流量
    uint64 m_u64TP;               // 网卡发送的数据包
} TNetCardInfo;

typedef struct _TModule_NetComm_Cycle
{
    uint8 m_u8AlivedThreadsinPool;            // 线程池中活动线程数
    int m_n32CurrentTasks;                    // 当前任务数
    uint8 m_u8NetcardCnt;                     // 网卡数量
    TNetCardInfo m_tNetCardInfo[MAX_NETCARD]; // 网卡收发流量信息
} TModule_NetComm_Cycle;

// V2X协议栈模块状态
typedef struct _TModule_V2XStack_Cycle
{
    uint64 m_u64TxQueDataNum;            // 发送消息队列消息数量 累计条数
    uint64 m_u64MsglayerTxDataNum;       // 消息层发送队列成功处理的消息数量 条数(发送的总包数)
    uint64 m_u64MsglayerTxDatabyte;      // 消息层发送队列成功处理的消息数量 条数(发送的总字节数)
    uint64 m_u64MsglayerTxDataArray[20]; // 消息层各个消息类型发送成功的消息数量 条数 下标可以约定消息类型
    uint64 m_u64SeclayerTxDataNum;       // 安全层发送队列成功处理的消息数量 条数
    uint64 m_u64PC5TxDatabyte;           // PC5口 发送 流量统计（发送成功总字节数）
    uint64 m_u64PC5TxDatapak;            // PC5口 发送 流量统计（发送成功总包数）

    uint64 m_u64MsglayerRxDataNum;       // 消息层接收队列成功处理的消息数量 条数(消息层成功接收包数)
    uint64 m_u64MsglayerRxDatabyte;      // 消息层接收队列成功处理的消息字节数(消息层成功接收字节数)
    uint64 m_u64MsglayerRxDataArray[20]; // 消息层各个消息类型接收成功的消息数量 条数 下标可以约定消息类型
    uint64 m_u64SeclayerRxDataNum;       // 安全层接收队列成功处理的消息数量 条数
    uint64 m_u64NetlayerRxDataNum;       // 网络层接收队列成功处理的消息数量 条数
    uint64 m_u64PC5RxDatabyte;           // PC5口 接收 流量统计（接收字节数）
    uint64 m_u64PC5RxDatapak;            // PC5口 接收 流量统计（接收总包数）
} TModule_V2XStack_Cycle;

// GNSS定位模块状态
typedef struct _TModule_GNSS_Cycle
{
    uint8 m_u8GNSSStatus;         // GNSS工作状态
    uint8 m_u8SatellitelockedNum; // 锁星数量
    float m_f32Latitude;          // 纬度
    float m_f32longitude;         // 经度
} TModule_GNSS_Cycle;

// 数据库模块状态
typedef struct _TModule_Database_Cycle
{
    uint8 m_u8DBStatus; // DB工作状态
} TModule_Database_Cycle;

// 各模块周期性监控信息
typedef struct _TModuleCycleStatusList
{
    enum MODULE_TYPE m_enumModuleType;
    union
    {
        TRsuBaseInfo m_tRsuBaseInfo;
        TRsuRuntimeInfo_Cycle m_tRsuRuntimeInfo;
        TModule_NetComm_Cycle m_tNetCommCycleStatus;
        TModule_V2XStack_Cycle m_tV2XStackCycleStatus;
        TModule_GNSS_Cycle m_tGNSSCycleStatus;
        TModule_Database_Cycle m_tDatabaseCycleStatus;
    } ModuleStatus;
} TModuleCycleStatusList;

// 周期性监控消息队列结构体
typedef struct _TCycleSupervisonMsgQue
{
    long m_n64MsgType;                               // 消息类型 0-注册消息，1-设备周期性状态消息,2-设备运行时状态信息
    TModuleCycleStatusList m_tModuleCycleStatusList; // 各模块周期性监控信息
} TCycleSupervisonMsgQue;

/****************************模块运行时（触发式）状态监控结构体****************************/

// 设备管理模块运行时状态
typedef struct _TModule_DevManage_Runtime
{
    uint8 m_u8DeviceDataCycleBackUp;
    uint8 m_u8DeviceDataEventBackUp;
    uint8 m_u8SysUpgradeState;
} TModule_DevManage_Runtime;

// V2X协议栈模块运行时状态
typedef struct _TModule_V2XStack_Runtime
{
    int8 m_n8V2XStatus;        // V2X工作状态
    int8 m_u8SafetyCertStatus; // 安全证书应用状态
} TModule_V2XStack_Runtime;

// 安全证书管理模块运行时状态
typedef struct _TModule_SafetyCert_Runtime
{
    uint8 m_u8CADownloadStatus; // 应用证书下载状态
} TModule_SafetyCert_Runtime;

// 网络通信模块运行时状态
typedef struct _TModule_NetComm_Runtime
{
    uint8 m_u8ConnectDevCnt;                // 连接外设数量
    int m_n32ConnectStatus[MAX_PERIPHERAL]; // 外设的连接状态 -1-未更新；0-断开；1-连接
} TModule_NetComm_Runtime;

// 定位模块运行时状态
typedef struct _TModule_GNSS_Runtime
{
    uint8 m_u8GNSSLocationState; // GNSS模块定位状态，0-已定位；1-未定位，2-定位模块异常
} TModule_GNSS_Runtime;

// 外部设备消息标准化模块运行时状态
typedef struct _TModule_MsgAdapter_Runtime
{
    uint8 m_u8MsgAdapterlibOpenStatus; // 消息标准化动态库dlopen状态
} TModule_MsgAdapter_Runtime;

// 各模块运行时监控信息
typedef struct _TModuleRuntimeStatusList
{
    enum MODULE_TYPE m_enumModuleType;
    union
    {
        //    TModule_DevManage_Runtime m_tDeviceManageStatus;
        TModule_NetComm_Runtime m_tNetCommRuntimeStatus;
        TModule_V2XStack_Runtime m_tV2XStackRuntimeStatus;
        TModule_SafetyCert_Runtime m_tSafetyCertRuntimeStatus;
        TModule_GNSS_Runtime m_tGNSSRuntimeStatus;
        TModule_MsgAdapter_Runtime m_tMsgAdapterRuntimeStatus;
    } RuntimeStatus;
} TModuleRuntimeStatusList;

// 运行时监控消息队列结构体
typedef struct _TRuntimeSupervisonMsgQue
{
    long m_n64MsgType;                                   // 消息类型 0-注册消息，1-设备周期性状态消息,2-设备运行时状态信息
    TModuleRuntimeStatusList m_tModuleRuntimeStatusList; // 各模块运行时监控信息
} TRuntimeSupervisonMsgQue;

int64_t get_timestamp();
int32_t get_v2xobubasicinfo_sequence();

char *get_v2xobubasicinfo_firmwareversion();
char *get_v2xobubasicinfo_appversion();
char *get_v2xobubasicinfo_platenum();
char *get_v2xobubasicinfo_devicesn();
int32_t get_vehicletype();

int32_t get_v2xobustate_sequence();
char *get_v2xobustate_id();
double get_v2xobustate_latitude();
double get_v2xobustate_longitude();
float get_v2xobustate_elevation();
float get_v2xobustate_heading();
float get_v2xobustate_speed();
int32_t get_v2xobustate_vehicletype();
int32_t get_v2xobustate_laneid();
int32_t get_v2xobustate_nodeid();
int32_t get_v2xobustate_autopilotstate();
int32_t get_v2xobustate_faultstate();
int32_t get_v2xobustate_gnssstatus();
int32_t get_v2xobustate_length();
int32_t get_v2xobustate_width();
int32_t get_v2xobustate_height();
/*********************************************OBU统计信息周期上报，目前实现上是针对所有的包数**********************************************************************/
//OBU统计信息序号上报
uint32_t get_v2xobustatistics_sequence();
/*********************************************设置和查询配置的响应**********************************************************************/
uint32_t get_v2xobuconfigrsp_sequence();
/*********************************************设置和查询配置的响应END**********************************************************************/

uint32_t get_v2xseenewarning_sequence();

uint32_t get_V2xObuRunningStatus_sequence();
#endif