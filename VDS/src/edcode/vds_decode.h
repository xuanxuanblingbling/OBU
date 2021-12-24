#ifndef _VDS_DECODE_H
#define _VDS_DECODE_H

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "cv_msg_bsm_frame.h"
#include "wj_Message_com.h"

/*故障判断*/
#define MCU_SPI_COM_FAULT_CNT     10//接收MCU数据帧10次无效时，报mcu spi通讯故障
/*ap->mcu 组帧最大个数*/
#define MCU_ENCODE_FRMAE_MAX_NUM  6//AP传至MCU最大帧个数
/*通过改变以下三个宏定义，可以改变需要接收的可变数据个数，如果接收数据小于配置个数，
则从前开始排列，后续填充0，若大于配置个数，则取配置个数*/
#define NEAR_CAR_MAX_NUM          3//周围临车最大个数
#define TRFC_REMIND_MAX_NUM       10//交通标志事件提醒最大个数
#define TLIGHT_PTHASE_MAX_NUM     16//红绿灯相位最大个数

/*车辆预警事件标识*/
#define HL_Flag               0x01//双闪事件标志
#define ABS_Flag              0x02//ABS触发事件标志
#define TCS_Flag              0x04//电子系统牵引力控制事件标志
#define VSC_Flag              0x08//车身稳定控制事件标志

#define HB_Flag               0x10//急刹车事件标志
#define FT_Flag               0x20//轮胎欠压事件标志
#define DV_Flag               0x40//车辆无法正常行驶事件标志
#define AB_Flag               0x80//空气气囊弹出事件标志
#define OTH_Flag              0xE1//其他事件标志（双闪事件、轮胎欠压、行车安全故障、安全气囊弹出）

/*各模块运行状态*/
#define SUSPEND               0x80//停止态
#define REDAY                 0x81//准备态
#define RUNNING               0x82//运行态
#define WAITING               0x83//等待态

/*signal id*/
#define VEH_DATA_ID           0x1001//车辆数据帧ID
#define VDS_STATE_ID          0x1002//VDS状态推送帧ID
#define VDS_FAULT_ID          0x1003//VDS故障推送帧ID
#define VDS_CONFIG_ID         0x1006//VDS配置响应帧ID
#define MCU_CONFIG_ID         0x1007//MCU配置响应帧ID
#define MCU_FAULT_ID          0x1004//MCU故障推送帧ID
#define MCU_PDOWN_ID          0x1005//MCU下电请求帧ID

#define APP_ACT_SAFE_ID       0x3001//APP功能安全数据帧ID
#define APP_TRFC_REMIND_ID    0x3002//APP交通标志事件提醒帧ID
#define APP_SPD_GUIDE_ID      0x3003//APP车速引导信息帧ID

#define SYS_CONFIG_RQ_ID      0x4001//SYS系统管理模块参数配置更新通知
#define SYS_PDOWN_RS_ID       0x4002//SYS掉电应答帧ID
#define NET_SIM_CAN_ID        0x5001//NET模拟车身CAN数据帧ID

/*****************************上行帧*********************************************
                        VDS -> APP,V2X,SYS
******************************上行帧*********************************************/
/**
 * 事件触发类BSM消息关键事件列表
 */
enum
{
    Hazard_Lights           = 0x01,//双闪
    event_ABS               = 0x02,
    event_Traction          = 0x04,
    event_Stability         = 0x08,
    event_HardBraking       = 0x10,
    event_FlatTire          = 0x20,
    event_DisabledVehicle   = 0x40,
    event_AirBagDeployment  = 0x80,
};
/*
*车身预警状态结构体
*/
typedef union 
{ 
    struct 
    {    
        uint8_t     m_event_HazardLights      :1;//双闪
        uint8_t     m_event_ABS               :1;//ABS系统被触发并超过100ms
        uint8_t     m_event_Traction          :1;//电子系统控制牵引力被触发并超过100ms。
        uint8_t     m_event_Stability         :1;//车身稳定控制被触发并超过100ms。
        uint8_t     m_event_HardBraking       :1;//车辆急刹车，并且减速度大于4m/s2。
        uint8_t     m_event_FlatTire          :1;//单个或多个轮胎欠压报警
        uint8_t     m_event_DisabledVehicle   :1;//由上述之外的行车安全故障导致的无法正常行驶。
        uint8_t     m_event_AirBagDeployment  :1;//触发条件：至少1个安全气囊从正常状态变为弹出状态。截至条件： 系统掉电。   
    }Event;
    uint8_t Byte;
}__attribute__ ((packed))WEvent;
/*
*车辆状态数据结构体
*/
#if 0
typedef struct vds_veh_data
{
    /*static data*/
    uint8_t                   m_vehId[17];//车辆ID
    int64_t                   m_time;//获取车辆经纬度的时间
    uint16_t                  m_vehicleWidth;//车宽，单位mm
    uint16_t                  m_vehicleLength;//车长，单位mm
    uint16_t                  m_vehicleHeight;//车高，单位mm
    uint8_t                   m_basicVehicleClass;//车辆类型
    /*dynamic data*/
    int                       m_latitude;//纬度
    int                       m_longitude;//经度
    int                       m_altitude;//海拔
    int                       m_semiMajorAxisAccuracy;//定位系统精度
    int                       m_heading;//航向角
    double                    m_speed;//车速
    int                       m_acc_lng;//纵向加速度
    int                       m_yawrate;//横摆角加速度
    
    /*The vehicle data*/
    uint8_t                   m_brakePedalStatus;//刹车踏板状态
    uint8_t                   m_brakeAppliedStatus;//四轮刹车状态
    uint8_t                   m_tractionControlStatus;//牵引力控制系统状态
    uint16_t                  m_exteriorLights;//车灯状态
    uint8_t                   m_transmissionState;//档位状态
    WEvent                    m_warningevent;//车辆预警事件
    double                    m_SteeringWheelAngle;//方向盘转角   ？新增？
}__attribute__ ((packed))TVdsVehData_st;
  #define VDS_VEH_DATA_LEN    (sizeof(TVdsVehData_st))  //vds车辆数据长
#else

typedef unsigned char  uint8;       /* 无符号8位整型变量  */
typedef unsigned long long  uint64;    /* 无符号64位整型变量  */
typedef struct
{ 
    int		    m_int_latitude;   //Represents latitude in degrees*10000000.
    int		    m_int_longitude;  //Represents longitude in degrees*10000000.
    int		    m_int_altitude;   // Represents altitude in decimetres above the WGS 84 reference ellipsoid.
    double	    m_dbl_speed;     //Represents speed in meters per second.
    double		m_dbl_heading;   //Represents heading in degrees.
    double	    m_dbl_accuracy;   //Represents expected accuracy in meters.
    int         m_int_CurrentGpsState;  // Location State : 0X00: Default ;0X10: RTK E1 ;0X20: RTK E2 ; 0X50: RTK E5 ;0X60: RTK E4; 0X80: AG15_Kernel.
    int         m_int_GpsFaultState;   // GPS Model fault:0X00: Default Normal;0X10:AG15 Fault ;0X20:RTK Fault
	uint64_t    m_u64_timestamp;  //Timestamp for the location fix.

} GpsLocation_dbus;

/**
 * @brief BrakeSystemStatus.
 */
typedef struct bus_VehLampData_Type 
{
    uint8    m_u8_RecVehLampMessage;
    uint64   m_u64_VehGNSS_timestamp;
} VehLampType_bus;

typedef struct bus_BrakeSystenStatus_Type
{
    uint8    m_u8_BrakeSystemStatusData;
    uint64   m_u64_BrakeSystenStatus_timestamp;
} BrakeSystenStatus_bus;

typedef struct bus_VehicleEventFlags_Type
{
    uint8    m_u8_VehicleEventFlagsData;
    uint64   m_u64_VehicleEventFlagsData_timestamp;
} VehicleEventFlags_bus;

typedef struct bus_TransmissionState_Type
{
    uint8    m_u8_TransmissionStateData;
    uint64   m_u64_TransmissionStateData_timestamp;
} TransmissionState_bus;

typedef struct bus_SteeringWheelAngle_Type
{
    double    m_dbl_SteeringWheelAngleData;
    uint64    m_u64_SteeringWheelAngle_timestamp;
} SteeringWheelAngle_bus;

typedef struct bus_Speed_Type
{
    double    m_dbl_SpeedData;
    uint64    m_u64_SpeedData_timestamp;
} Speed_bus;
typedef struct bus_VehCANData_Type 
{
    VehLampType_bus          m_LeftTurnLampSt;
    VehLampType_bus          m_RightTurnLampSt;
    VehLampType_bus          m_LowBeamSt;
    VehLampType_bus          m_HighBeamSt;
    VehLampType_bus          m_FrontFogLampSt;
    VehLampType_bus          m_RearFogLampSt;
    VehLampType_bus          m_ParkingLampSt;
    VehLampType_bus          m_HazardLampSt;
    VehLampType_bus          m_EmergeWarningLightSt;
    BrakeSystenStatus_bus    m_DF_BrakeSystemStatus;
    VehicleEventFlags_bus    m_DE_VehicleEventFlags;
    TransmissionState_bus    m_DE_TransmissionState;
    SteeringWheelAngle_bus   m_DE_SteeringWheelAngle;
    Speed_bus                m_DE_Speed;
} VehCANData_dbus;

////驾驶意图
typedef enum{
    GSPAUNVAILD,
    GSPAACTIVE,
    GSPAINACTIVE
}GSPAIntentEnum;

typedef enum{
    CLCINVAILD,
    CLCLEFTTURN,
    CLCRIGHTTURN
}CLCIntentEnum;


typedef struct _driveintention{
    uint8_t   m_u8GSPAintent;
    uint32_t  m_u32GSPAvaildtime;
    uint8_t   m_u8CLCintent;
    uint32_t  m_u32CLCvaildtime;
}DriveIntention;

typedef struct vds_veh_data
{
    /*static data*/
    uint8_t                   m_vehId[17];//车辆ID
    int64_t                   m_time;//获取车辆经纬度的时间
    uint16_t                  m_vehicleWidth;//车宽，单位mm
    uint16_t                  m_vehicleLength;//车长，单位mm
    uint16_t                  m_vehicleHeight;//车高，单位mm
    uint8_t                   m_basicVehicleClass;//车辆类型

    /* IMU数据*/
    int                       m_int_acclng;//纵向加速度
    int                       m_int_yawrate;//横摆角加速度
    int                       m_int_acclat;//纵向加速度
    int                       m_int_accvert;//横摆角加速度

    /*GPS data*/
    GpsLocation_dbus          m_gpsdata_st;
    /*The vehicle data*/
    VehCANData_dbus           m_candata_st;
    DriveIntention            m_driveIntent;
    WEvent                    m_warningevent;//车辆预警事件
}__attribute__ ((packed))TVdsVehData_st;
  #define VDS_VEH_DATA_LEN    (sizeof(TVdsVehData_st))  //vds车辆数据长

#endif



/*
*车辆状态数据帧
*/
typedef struct vds_veh_frame
{
    /*frame   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /*frame  data*/
    TVdsVehData_st            m_vehdata;//车辆数据长度
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验）
}__attribute__ ((packed))TVdsVehFrame_st;
#define VDS_VEH_FRAME_LEN    (sizeof(TVdsVehFrame_st))  //vds车辆帧帧长

/*
*vds模块状态数据
*/
typedef struct vds_state_data
{
    uint8_t                   m_dataDecodeState;//数据编解码线程状态
    uint8_t                   m_canSendState;//mcu数据发送线程状态
    uint8_t                   m_canRecvState;//mcu数据接收线程状态
    uint8_t                   m_gnssRecvState;//gnss数据接收线程状态
    /*locating info*/
    uint8_t                   m_GnssStatus;//gnss数据有效性
    uint8_t                   m_qtySvUsed;//gnss可用卫星个数

    int                       m_latitude;
    int                       m_longitude;
}__attribute__ ((packed))TVdsStateData_st;

#define VDS_STATE_DATA_LEN    (sizeof(TVdsStateData_st))  //vds状态帧帧长
/*
*vds模块状态推送帧
*/
typedef struct vds_state_push
{
    /*frame struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /*vds state*/
    TVdsStateData_st          m_state;//vds运行状态
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验）
}__attribute__ ((packed))TVdsStatePush_st;

/*
*vds模块故障推数据
*/
typedef struct vds_fault_data
{
    uint8_t                   m_CanInitFault;//CAN模块初始化故障通讯故障
    uint8_t                   m_GpsInitFault;//Gps初始化故障
    uint8_t                   m_gnssDataFault;//gnss数据故障
    uint8_t                   m_GpsAG15Fault;//AG15定位通讯故障
    uint8_t                   m_GpsRTKFault;//RTK故障
    uint8_t                   m_reserverFault;//保留扩展字段
}__attribute__ ((packed))TVdsFaultData_st;

#define VDS_FAULT_DATA_LEN    (sizeof(TVdsFaultData_st))  //vds故障帧帧长
/*
*vds模块故障推送
*/
typedef struct vds_fault_push
{
    /*frme   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /*error  info*/
    TVdsFaultData_st          m_fault;//故障信息
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验）    
}__attribute__ ((packed))TVdsFaultPush_st;

/*
*mcu模块故障数据
*/
typedef struct mcu_fault_data
{
    uint8_t                   m_canBusoffFault;//CAN总线BUS OFF
    uint8_t                   m_highVoltageFault;//电池电压过高故障
    uint8_t                   m_lowVoltageFault;//电池电压过低故障
}__attribute__ ((packed))TMcuFaultData_st;
#define MCU_FAULT_DATA_LEN    (sizeof(TMcuFaultData_st))  //mcu故障帧帧长
/*
*mcu模块故障推送
*/
typedef struct mcu_fault_push
{
    /*frme   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /*error  info*/
    TMcuFaultData_st          m_fault;//故障信息
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验）    
}__attribute__ ((packed))TMcuFaultPush_st;


/*
*电源管理掉电请求数据
*/
typedef struct mcu_pdown_rq_data
{
    uint8_t                   m_pDownRqData;//MCU电源管理掉电请求 
}__attribute__ ((packed))TMcuPDownRqData_st;

#define MCU_PDOWN_RQ_DATA_LEN    (sizeof(TMcuPDownRqData_st))  //MCU电源管理掉电请求帧帧长
/*
*电源管理掉电请求帧
*/
typedef struct sys_pdown_rq_data
{
    /*frme   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /*pow down rq*/
    TMcuPDownRqData_st        m_pDownRq;//下电请求
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验）    
}__attribute__ ((packed))TMcuPowerdownRq_st;

/*
*VDS在线配置更新数据 0x90：参数修改成功,0x91：参数修改失败,其他：无效
*/
typedef struct vds_config_data
{
    uint8_t                   m_McucfgRs;
    uint8_t                   m_VdsCfgRs; 
    uint8_t                   m_Ag35cfgRs; 
}__attribute__ ((packed))TVdsConfigData_st;

#define VDS_CONFIG_DATA_LEN    (sizeof(TVdsConfigData_st))  //VDS车辆配置文件更新响应帧帧长
/*
*VDS在线配置更新响应帧
*/
typedef struct vds_config_rs
{
    /*frme   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /*config rs*/
    TVdsConfigData_st         m_config_rs;//vds配置响应数据
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验）    
}__attribute__ ((packed))TVdsConfigRs_st;

/*
* mcu当前配置信息
*/
typedef struct mcu_config_data_rs
{
    //配置信息
    uint16_t                  m_ponDelayTime;//上电延时时间
    uint8_t                   m_ponDelayTimeStorFlag;//上电延时存储标志
    uint16_t                  m_diagDelayTime;//诊断延时时间
    uint8_t                   m_diagDelayTimeStorFlag;//诊断延时存储标志
    uint16_t                  m_diagVolRangeH;//诊断电压区间高限
    uint8_t                   m_diagVolRangeHStorFlag;//诊断电压区间高限存储标志
    uint16_t                  m_diagVolRangeL;//诊断电压区间高限
    uint8_t                   m_diagVolRangeLStorFlag;//诊断电压区间高限存储标志      
    uint16_t                  m_diagHysVolH;//诊断迟滞电压-高限
    uint8_t                   m_diagHysVolHStorFlag;//诊断迟滞电压-高限存储标志
    uint16_t                  m_diagHysVolL;//诊断迟滞电压-低限
    uint8_t                   m_diagHysVolLStorFlag;//诊断迟滞电压-低限存储标志
}__attribute__ ((packed))TMcuConfigDataRs_st;
#define MCU_CONFIG_DATA_RS_LEN    (sizeof(TMcuConfigDataRs_st))  //VDS车辆配置文件更新响应帧帧长
/*
*mcu当前配置信息响应帧，将mcu当前配置信息上报至sys
*/
typedef struct mcu_config_rs
{
    /*frme   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /*config rs*/
    TMcuConfigDataRs_st       m_config_rs;//vds配置响应数据
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验）    
}__attribute__ ((packed))TMcuConfigRs_st;
#define MCU_CONFIG_FRAME_RS_LEN    (sizeof(TMcuConfigRs_st))  //VDS车辆配置文件更新响应帧帧长
/*
*产线出厂测试响应帧
*/
/*typedef struct expactory_test_rs
{
    uint8_t                   m_ExpTestRs;
}__attribute__ ((packed))TExpactoryTestRs_st;*/

//#define EXPACT_TEST_RS_LEN    (sizeof(TExpactoryTestRs_st))  //产线出厂测试响应帧帧长


/*****************************下行帧*********************************************
                        APP,VDS,NET -> VDS 
******************************下行帧*********************************************/
/*
*电源管理应答数据
*/
typedef struct sys_pdown_rs_data
{
    uint8_t                   m_pDownRsData;//系统管理模块电源管理应答帧
}__attribute__ ((packed))TSysPDownRsData_st;

#define SYS_PDOWN_RS_DATA_LEN    (sizeof(TSysPDownRsData_st))
/*
*电源管理应答帧
*/
typedef struct sys_powerdown_rs
{
    /*frme   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /*pdown  rs*/
    TSysPDownRsData_st        m_pDownRs;//掉电响应
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验） 
}__attribute__ ((packed))TSysPowerdownRs_st;
#define SYS_PDOWN_RS_FRAME_LEN    (sizeof(TSysPowerdownRs_st))

/*
*车辆配置文件更新事件类型
*/
typedef struct sys_config_rq_data
{
    uint8_t                   m_AppCfgFlag;//App配置请求
    uint8_t                   m_V2xCfgFlag;//V2x配置请求
    uint8_t                   m_VdsCfgFlag;//Vds配置请求(０x80:VDS配置文件更新，０x81:MCU配置文件更新，0x82:AG35配置文件更新)
    uint8_t                   m_NetCfgFlag;//Net配置请求
}__attribute__ ((packed))TSysConfigRqData_st;
#define SYS_CONFIG_RQ_DATA_LEN    (sizeof(TSysConfigRqData_st))
/*
*车辆配置文件更新事件帧
*/
typedef struct sys_config_rq
{
    /*frme   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /*config rq*/
    TSysConfigRqData_st       m_configRq;//配置请求
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验） 
}__attribute__ ((packed))TSysConfigRq_st;
#define SYS_CONFIG_RQ_FRAME_LEN    (sizeof(TSysConfigRq_st))

/*
* 主动安全数据 - 临车信息
*/
typedef struct adve_data
{
    uint8_t                   m_nAdveUEID[8];// 邻车UEID
    uint32_t                  m_nAdveLat;// 邻车纬度
    uint32_t                  m_nAdveLong;// 邻车经度
    uint16_t                  m_nAdveTrack;// 邻车航向角    
    uint16_t                  m_nAdveSpeed;// 邻车车速
    uint16_t                  m_nAdveAccY;// 邻车纵向加速度
    uint16_t                  m_nAdveAccX;// 邻车横向加速度
    uint16_t                  m_nAdveAccZ;// 邻车垂直加速度
    uint16_t                  m_nAdveLgtSt;// 车身周围车灯状态
    uint8_t                   m_nAdveVehCls;// 邻车车辆类型
    uint8_t                   m_nAdveGear;// 邻车车辆档位状态
    uint8_t                   m_nAdveBreak;// 邻车刹车踏板状态
}__attribute__ ((packed))TAdveData_st;
/*
*APP场景输出帧－主动安全数据
*/
typedef struct result_act_safe_data
{
    uint8_t                   m_upLoadID;// 信息上传标识
    // 自车信息
    uint8_t                   m_UEID[8];// 自车UEID
    uint32_t                  m_nSelfLat;// 自车纬度
    uint32_t                  m_nSelfLong;// 自车经度
    uint16_t                  m_nSelfSpeed;// 自车车速
    uint16_t                  m_nSelfTrack;// 自车方向
    uint8_t                   m_nSelfTurn;// 转向信息
    // 危险车辆信息
    uint8_t                   m_dangerAdveUEID[8];// 危险状态车ID
    uint16_t                  m_nAdveSafeState;// 危险车预警信息
    uint8_t                   m_nAdvePriority;// 预警信息优先级
    uint8_t                   m_nAdveRelativeOrientation;// 危险车安全状态优先级
    // 周围车辆信息
    uint16_t                  m_nAdveCnt;// 周围车个数
    TAdveData_st              m_nAdveData[NEAR_CAR_MAX_NUM];
}__attribute__ ((packed))TResultActSafeData_st;
#define APP_ACT_SAFE_DATA_LEN    (sizeof(TResultActSafeData_st))
/*
*APP场景输出帧－主动安全信号帧
*/
typedef struct result_act_safe
{
    /*frme   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /*act safe data*/
    TResultActSafeData_st     m_actSafe;//主动安全提醒数据
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验） 
}__attribute__ ((packed))TResultActSafe_st;
#define APP_ACT_SAFE_FRAME_LEN    (sizeof(TResultActSafe_st))

/*
*APP场景输出帧－交通标志提醒数据
*/
typedef struct adve_rsi
{
    uint8_t                   m_wStr;//V2I应用场景
    uint16_t                  m_RsiType;//RSI事件类型
    uint32_t                  m_dAdveLat;//RSI事件纬度
    uint32_t                  m_dAdveLong;//RSI事件经度
    // 事件相关信息
    uint16_t                  m_DesLen;//事件描述内容长度
    uint8_t                   m_DesFlag;//事件描述标志
    uint8_t                   m_DesData[256];//事件描述内容
}__attribute__ ((packed))AdveRsi_st;
/*
*APP场景输出帧－交通标志提醒数据组
*/
typedef struct result_trfc_remind_data
{
    uint16_t                  m_dAdveRsiCnt;//周围RSI消息个数
    AdveRsi_st                m_dAdveRsiData[TRFC_REMIND_MAX_NUM];//RSI信息
}__attribute__ ((packed))TResultTrfcRemindData_st;
#define APP_TRFC_REMIND_DATA_LEN    (sizeof(TResultTrfcRemindData_st))
/*
*APP场景输出帧－交通标志提醒信号帧
*/
typedef struct result_trfc_remind
{
    /*frme   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /**/
    TResultTrfcRemindData_st  m_TrfcRemindData;
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验）   
}__attribute__ ((packed))TResultTrfcRemind_st;
#define APP_TRFC_REMIND_FRAME_LEN    (sizeof(TResultTrfcRemind_st))

/*
*APP场景输出帧－信号灯状态数据
*/
typedef struct traffic_light
{
    uint16_t                  m_phaseId;//相位ID
    uint8_t                   m_Status;//灯色状态
    uint8_t                   m_LightDirection;//灯的方向
    uint8_t                   m_TimeLeft;//剩余时间
    uint8_t                   m_SuggSdType;//建议操作
    uint8_t                   m_SuggSd;//建议时速
}__attribute__ ((packed))TrafficLight_st;
/*
*APP场景输出帧－绿波车速引导数据组
*/
typedef struct result_spd_guide_data
{
    uint32_t                  m_SPATLat;//信号灯纬度
    uint32_t                  m_SPATLong;//信号灯经度
    uint8_t                   m_wType;//应用场景
    uint8_t                   m_PhaseCnt;//前方相位个数
    TrafficLight_st           m_TraffLight[TLIGHT_PTHASE_MAX_NUM];//红绿灯相位个数
}__attribute__ ((packed))TResultSpdGuideData_st;
#define APP_SPD_GUIDE_DATA_LEN    (sizeof(TResultSpdGuideData_st))
/*
*APP场景输出帧－绿波车速引导信号帧
*/
typedef struct result_spd_guide
{
    /*frme   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    TResultSpdGuideData_st    m_spdGuide;//
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验） 
}__attribute__ ((packed))TResultSpdGuide_st;
#define APP_SPD_GUIDE_FRAME_LEN    (sizeof(TResultSpdGuide_st))

/*
*　模拟CAN数据
*/
typedef struct net_can_simulate_data
{
    uint32_t m_u32speed;
	uint32_t m_u32wheelTurn; 		//方向盘转角
	uint16_t m_u16exteriorLights;	//车灯
	int32_t m_n32brakePedalStatus;	  //刹车
	int32_t m_n32tractionControlSystem;		//车轮制动系统
	int32_t m_n32tractionControlStatus;	//辅助制动系统
	int32_t m_n32AntilockbrakeSystem;    //防抱死系统
	int32_t m_n32bodyStabilitySystem;      //车身稳定系统
	int32_t m_n32brakeAssistSystem;	//刹车辅助系统
	int32_t m_n32auxiliaryBrakeSystem;   //牵引力控制系统状态
	int32_t m_n32basicVehicleClass;
	uint8_t m_u8transmissionState;     //Net_EncodeMessCan.h
}__attribute__ ((packed))TNetCanSimulateData_st;

#define NET_CAN_SIMULATE_DATA_LEN    (sizeof(TNetCanSimulateData_st))
/*
*　CAN数据模拟帧
*/
typedef struct net_can_simulate
{
    /*frme   struct*/
    uint16_t                  m_id;//信号ID
    uint16_t                  m_length;//信号长度
    /*The vehicle data*/
    TNetCanSimulateData_st    m_canSimuData;//模拟CAN数据
    /*bcc*/
    uint8_t                   m_bcc;//信号校验（异或校验） 
}__attribute__ ((packed))TNetCanSimulate_st;

#define NET_CAN_SIMULATE_FRAME_LEN    (sizeof(TNetCanSimulate_st))

//APP 算法输出结果can数据
typedef struct _SenarioCanResult
{
    uint16_t ID; // 信号ID
    uint16_t LENGTH; // DATA数据长度
    uint8_t m_nPtcpType; // 交通参与者类型 BSM:0 RSM:1
    uint8_t m_nVehId[8]; // 车辆的ID
    uint16_t m_nPtcpId; // 交通参与者ID
    uint16_t m_nWarnType; // 预警类型
    uint16_t m_nWarnLevel; // 预警等级 0-1000
    uint8_t m_nBlind; // 左右盲区
    uint8_t m_nBear; // 相对位置 
    int m_nTTC; // 碰撞TTC ms
    int m_nRelaHead; // 速度相对朝向 度
    int m_nRelaVel; // 相对速度 mm/s
    int m_CenterDis; // 中心距离 mm
    int m_PathDis; // 路径距离 mm
    int m_VertDis; // 横向距离 mm
}__attribute__ ((packed)) SenarioCanResult;

/******************************上行帧*********************************************
                             MCU -> AP(vds)
******************************上行帧*********************************************/
/**
 * 车身数据
 */
typedef struct mcu_veh_data
{
    uint16_t                  m_speed;//车速
    uint8_t                   m_brakePedalStatus;//刹车踏板状态
    uint8_t                   m_brakeAppliedStatus;//四轮刹车状态
    uint8_t                   m_tractionControlStatus;//牵引力控制系统状态
    uint16_t                  m_exteriorLights;//车灯状态
    uint8_t                   m_transmissionState;//档位状态
    uint8_t                   m_abnormalEvent;//异常事件
}__attribute__ ((packed))TMcuVehData;
#define MCU_VEH_DATA_LEN   sizeof(TMcuVehData)
/**
 * 车身数据帧,id:0x01，帧长：12，数据长度：9
 */
typedef struct mcu_veh_frame
{
    uint8_t                   m_validByte;//有效字节数
    uint8_t                   m_msgId;//帧id
    uint8_t                   m_msglength;//数据长度
    TMcuVehData               m_vehdata;//帧数据
    uint8_t                   m_bcc;//校验位
}__attribute__ ((packed))TMcuVehFrame;
#define MCU_VEH_FRAME_LEN   sizeof(TMcuVehFrame)

/**
 * MCU配置信息
 */
typedef struct mcu_config_data
{
    //配置信息
    uint16_t                  m_ponDelayTime;//上电延时时间
    uint8_t                   m_ponDelayTimeStorFlag;//上电延时存储标志
    uint16_t                  m_diagDelayTime;//诊断延时时间
    uint8_t                   m_diagDelayTimeStorFlag;//诊断延时存储标志
    uint16_t                  m_diagVolRangeL;//诊断电压区间高限
    uint8_t                   m_diagVolRangeLStorFlag;//诊断电压区间高限存储标志
    uint16_t                  m_diagVolRangeH;//诊断电压区间高限
    uint8_t                   m_diagVolRangeHStorFlag;//诊断电压区间高限存储标志      
    uint16_t                  m_diagHysVolH;//诊断迟滞电压-高限
    uint8_t                   m_diagHysVolHStorFlag;//诊断迟滞电压-高限存储标志
    uint16_t                  m_diagHysVolL;//诊断迟滞电压-低限
    uint8_t                   m_diagHysVolLStorFlag;//诊断迟滞电压-低限存储标志
}__attribute__ ((packed))TMcuConfigData;
typedef struct mcu_sta_data
{
    uint8_t                   m_powerInfo;//电源管理
    uint8_t                   m_faultInfo;//故障信息
    //配置信息
    TMcuConfigData            m_configData;//mcu配置信息
}__attribute__ ((packed))TMcuStateData;
#define MCU_STATE_DATA_LEN   sizeof(TMcuStateData)
/**
 * MCU配置信息帧,id:0x02，0x09，帧长：41，数据长度：38
 */
typedef struct mcu_sta_frame
{
    uint8_t                   m_validByte;//有效字节数
    uint8_t                   m_msgId;//帧id
    uint8_t                   m_msglength;//数据长度
    TMcuStateData             m_cfgData;//帧数据
    uint8_t                   m_bcc;//校验位
}__attribute__ ((packed))TMcuStaCfgFrame;
#define MCU_STATE_FRAME_LEN   sizeof(TMcuStateFrame)

/**
 * MCU版本信息
 */
typedef struct mcu_vsion_data
{
    uint8_t                  m_versionNum[27];//版本号
}__attribute__ ((packed))TMcuVsionData;
#define MCU_VSION_DATA_LEN   sizeof(TMcuVsionData)
/**
 * MCU版本信息帧,id:0x03，帧长：30，数据长度：27
 */
typedef struct mcu_vsion_frame
{
    uint8_t                   m_validByte;//有效字节数
    uint8_t                   m_msgId;//帧id
    uint8_t                   m_msglength;//数据长度
    TMcuVsionData             m_vsionData;//帧数据
    uint8_t                   m_bcc;//校验位
}__attribute__ ((packed))TMcuVsionFrame;
#define MCU_VSION_FRAME_LEN   sizeof(TMcuVsionFrame)

/**
 * 临车信息 car1:0x04,car2:0x05,car3:0x06
 */
typedef struct app_near_car_data
{
    uint16_t                  m_speed;//车速
    uint16_t                  m_LongAcc;//纵向加速度
    uint16_t                  m_LatAcc;//横向加速度
    uint8_t                   m_vertAcc;//垂直加速度
    uint8_t                   m_lights;//车辆周围车灯状态
    uint8_t                   m_id;//车辆id
    uint16_t                  m_heading;//车辆航向角
    uint8_t                   m_VehicleClass;//车辆类型
    uint8_t                   m_transmission;//车辆档位状态
    uint8_t                   m_brakePadel;//车辆刹车踏板状态
    uint32_t                  m_latitude;//纬度
    uint32_t                  m_longitude;//经度
}__attribute__ ((packed))TAppNearCarData;
#define APP_NEARCAR_DATA_LEN   sizeof(TAppNearCarData)
/**
 * 临车信息帧,id:0x04,0x05,0x06，帧长：26，数据长度：23
 */
typedef struct app_near_car_frame
{
    uint8_t                   m_validByte;//有效字节数
    uint8_t                   m_msgId;//帧id
    uint8_t                   m_msglength;//数据长度
    TAppNearCarData           m_carData;//帧数据
    uint8_t                   m_bcc;//校验位
}__attribute__ ((packed))TAppNearCarFrame;
#define APP_NEARCAR_FRAME_LEN   sizeof(TAppNearCarFrame)

/**
 * 红绿灯信息
 */
typedef struct app_spat_data
{
    uint8_t                   m_timeLeftL;//左转车道剩余时间
    uint8_t                   m_timeLeftR;//右转车道剩余时间
    uint8_t                   m_timeLeftGo;//直行车道剩余时间
    uint8_t                   m_lightId;//红绿灯id
    uint8_t                   m_turnLightStsL;//左转车道灯状态
    uint8_t                   m_turnLightStsR;//右转车道灯状
    uint8_t                   m_turnLightStsGo;//直行车道灯状态
    uint8_t                   m_spatType;//应用场景
    uint8_t                   m_phaseCnt;//前方相位数
    uint32_t                  m_lightLat;//红绿灯纬度
    uint32_t                  m_lightLong;//红绿灯经度
}__attribute__ ((packed))TAppSpatData;
#define APP_SPAT_DATA_LEN   sizeof(TAppSpatData)
/**
 * 红绿灯信息帧,id:0x07
 */
typedef struct app_spat_frame
{
    uint8_t                   m_validByte;//有效字节数
    uint8_t                   m_msgId;//帧id
    uint8_t                   m_msglength;//数据长度
    TAppSpatData              m_spatData;//帧数据
    uint8_t                   m_bcc;//校验位
}__attribute__ ((packed))TAppSpatFrame;
#define APP_SPAT_FRAME_LEN   sizeof(TAppSpatFrame)

/**
 * 本车信息
 */
typedef struct app_own_car_data
{
    uint32_t                  m_longRoll;//横滚角度
    uint32_t                  m_latRoll;//俯仰角度
    uint32_t                  m_heading;//航向
    uint32_t                  m_gpsTime;//gps获取时间
    uint64_t                  m_latitude;//纬度
    uint64_t                  m_longitude;//经度
    uint16_t                  m_longAcceleration;//北向加速度
    uint16_t                  m_latAcceleration;//东向加速度
    uint16_t                  m_vertAcceleration;//地向加速度
    uint16_t                  m_AdveSafeState;//危险车预警信息
    uint8_t                   m_AdvePriority;//危险车安全状态优先级
    uint8_t                   m_AdveRelativeOrientation;//危险车相对方位
}__attribute__ ((packed))TAppOwnCarData;
#define APP_OWNCAR_DATA_LEN   sizeof(TAppOwnCarData)
/**
 * 本车信息帧,id:0x08
 */
typedef struct app_own_car_frame
{
    uint8_t                   m_validByte;//有效字节数
    uint8_t                   m_msgId;//帧id
    uint8_t                   m_msglength;//数据长度
    TAppOwnCarData            m_owncarData;//帧数据
    uint8_t                   m_bcc;//校验位
}__attribute__ ((packed))TAppOwnCarFrame;
#define APP_OWNCAR_FRAME_LEN   sizeof(TAppOwnCarFrame)
/******************************内部结构体*********************************************/

/******************************内部结构体*********************************************/
/*内部结构体*/
typedef struct wevent_timer
{
    uint64_t                  m_InitTime;//双闪事件初始时间
    uint64_t                  m_CurrentTime;//双闪事件当前时间
    uint8_t                   m_TrigFlag;//双闪事件触发标志
}__attribute__ ((packed))TWEventTimer;

/**************function definition**************/
extern void FE_EcodeModuleCreat(void);//创建vds编解码线程

/**************v2x frame for RTCM**************/
typedef struct
{
    uint16_t m_MsgID;
    uint32_t m_MsgLength;
    uint16_t m_Version;
    uint16_t m_AID;
    MSG_MessageType_st   m_V2xMessageFrame;
    uint8_t  m_Bcc;
} __attribute__((packed)) TV2xSrvMsg_t;

#endif
