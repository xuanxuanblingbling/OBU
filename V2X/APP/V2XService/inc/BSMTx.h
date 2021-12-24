/*******************************************************************************
 * 文 件 名 称 ： BSMTx.h
 * 功 能 描 述 ： BSM发送模块，接收VDS模块数据并组包发送
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#ifndef __BSM_TX_H__
#define __BSM_TX_H__

#include "V2xBasicTypes.h"
#include "wj_Message_com.h"

V2X_BEGIN_HEADER

#define OLDVEDDATA 0

//BSM模块运行/组包相关数据结构
typedef enum
{
    NORM_VEH_BSM_MSG_AID = 111U,
    NORM_VEH_EV_BSM_MSG_AID = 112U,
    EMER_VEH_BSM_MSG_AID = 113U,
    EMER_VEH_EV_BSM_MSG_AID = 114U
} TBsmMsgAid_t;

//BSM消息发送周期
enum
{
    BSMTX_CYCLE_100MS = 100,
    BSMTX_CYCLE_200MS = 200,
    BSMTX_CYCLE_400MS = 400,
    BSMTX_CYCLE_500MS = 500,
    BSMTX_CYCLE_1000MS = 1000
};

//发送数据模式选择
typedef enum
{
    BSM,
    V2FRAME,
    VIR
} SendFrameTpye;

//是否发送请求数据
typedef enum
{
    NO,
    YES
} TrigeInitative;

//V2X协议栈的拥塞控制值cbr，单精度浮点数
#define V2X_STACK_CBR_MIN 0.0f
#define V2X_STACK_CBR_LV1 0.3f
#define V2X_STACK_CBR_LV2 0.6f
#define V2X_STACK_CBR_LV3 0.8f
#define V2X_STACK_CBR_LV4 1.0f

//车速的等级，单位为m/s * 50 系数因子
#define VEHICLE_SPEED_MIN 0
#define VEHICLE_SPEED_LV1 (5 * 1000 * 50 / 3600)
#define VEHICLE_SPEED_LV2 (10 * 1000 * 50 / 3600)
#define VEHICLE_SPEED_LV3 (25 * 1000 * 50 / 3600)

//单精度浮点数比较大小的最小因子
#define MIN_FLOAT_DIV 1e-6

//单精度浮点数比较的宏，含相等
#define FLOAT_CMP_EQ(a, b) \
    (((a) > (b) && fabsf((a) - (b)) > MIN_FLOAT_DIV) || fabsf((a) - (b)) <= MIN_FLOAT_DIV)

//单精度浮点数比较的宏，不含相等
#define FLOAT_CMP(a, b) \
    (((a) > (b) && fabsf((a) - (b)) > MIN_FLOAT_DIV))

//车身预警状态结构体
typedef union
{
    struct
    {
        uint8_t m_event_HazardLights : 1;     //双闪
        uint8_t m_event_ABS : 1;              //ABS系统被触发并超过100ms
        uint8_t m_event_Traction : 1;         //电子系统控制牵引力被触发并超过100ms。
        uint8_t m_event_Stability : 1;        //车身稳定控制被触发并超过100ms。
        uint8_t m_event_HardBraking : 1;      //车辆急刹车，并且减速度大于4m/s2。
        uint8_t m_event_FlatTire : 1;         //单个或多个轮胎欠压报警
        uint8_t m_event_DisabledVehicle : 1;  //由上述之外的行车安全故障导致的无法正常行驶。
        uint8_t m_event_AirBagDeployment : 1; //触发条件：至少1个安全气囊从正常状态变为弹出状态。截至条件： 系统掉电。
    } Event;

    uint8_t Byte;
} __attribute__((packed)) EventFlagType;

//车辆状态信息数据结构体
#if OLDVEDDATA
typedef struct vds_veh_data
{
    /*static data*/
    uint8_t m_vehId[17];         //车辆ID
    int64_t m_time;              //获取车辆经纬度的时间
    uint16_t m_vehicleWidth;     //车宽，单位mm
    uint16_t m_vehicleLength;    //车长，单位mm
    uint16_t m_vehicleHeight;    //车高，单位mm
    uint8_t m_basicVehicleClass; //车辆类型
    /*dynamic data*/
    int m_latitude;              //纬度
    int m_longitude;             //经度
    int m_altitude;              //海拔
    int m_semiMajorAxisAccuracy; //定位系统精度
    int m_heading;               //航向角
    double m_speed;              //车速
    int m_acc_lng;               //纵向加速度
    int m_yawrate;               //横摆角加速度
    /*The vehicle data*/
    uint8_t m_brakePedalStatus;      //刹车踏板状态
    uint8_t m_brakeAppliedStatus;    //四轮刹车状态
    uint8_t m_tractionControlStatus; //牵引力控制系统状态
    uint16_t m_exteriorLights;       //车灯状态
    uint8_t m_transmissionState;     //档位状态
    EventFlagType m_warningevent;    //车辆预警事件
    double m_SteeringWheelAngle;     //方向盘转角   ？新增？
} __attribute__((packed)) TVehData_t;
#else

typedef unsigned char uint8;       /* 无符号8位整型变量  */
typedef unsigned long long uint64; /* 无符号64位整型变量  */
typedef struct
{
    int m_int_latitude;        //Represents latitude in degrees*10000000.
    int m_int_longitude;       //Represents longitude in degrees*10000000.
    int m_int_altitude;        // Represents altitude in decimetres above the WGS 84 reference ellipsoid.
    double m_dbl_speed;        //Represents speed in meters per second.
    double m_dbl_heading;      //Represents heading in degrees.
    double m_dbl_accuracy;     //Represents expected accuracy in meters.
    int m_int_CurrentGpsState; // Location State : 0X00: Default ;0X10: RTK E1 ;0X20: RTK E2 ; 0X50: RTK E5 ;0X60: RTK E4; 0X80: AG15_Kernel.
    int m_int_GpsFaultState;   // GPS Model fault:0X00: Default Normal;0X10:AG15 Fault ;0X20:RTK Fault
    uint64_t m_u64_timestamp;  //Timestamp for the location fix.

} GpsLocation_dbus;

/**
 * @brief BrakeSystemStatus.
 */
typedef struct bus_VehLampData_Type
{
    uint8 m_u8_RecVehLampMessage;
    uint64 m_u64_VehGNSS_timestamp;
} VehLampType_bus;

typedef struct bus_BrakeSystenStatus_Type
{
    uint8 m_u8_BrakeSystemStatusData;
    uint64 m_u64_BrakeSystenStatus_timestamp;
} BrakeSystenStatus_bus;

typedef struct bus_VehicleEventFlags_Type
{
    uint8 m_u8_VehicleEventFlagsData;
    uint64 m_u64_VehicleEventFlagsData_timestamp;
} VehicleEventFlags_bus;

typedef struct bus_TransmissionState_Type
{
    uint8 m_u8_TransmissionStateData;
    uint64 m_u64_TransmissionStateData_timestamp;
} TransmissionState_bus;

typedef struct bus_SteeringWheelAngle_Type
{
    double m_dbl_SteeringWheelAngleData;
    uint64 m_u64_SteeringWheelAngle_timestamp;
} SteeringWheelAngle_bus;

typedef struct bus_Speed_Type
{
    double m_dbl_SpeedData;
    uint64 m_u64_SpeedData_timestamp;
} Speed_bus;
typedef struct bus_VehCANData_Type
{
    VehLampType_bus m_LeftTurnLampSt;
    VehLampType_bus m_RightTurnLampSt;
    VehLampType_bus m_LowBeamSt;
    VehLampType_bus m_HighBeamSt;
    VehLampType_bus m_FrontFogLampSt;
    VehLampType_bus m_RearFogLampSt;
    VehLampType_bus m_ParkingLampSt;
    VehLampType_bus m_HazardLampSt;
    VehLampType_bus m_EmergeWarningLightSt;
    BrakeSystenStatus_bus m_DF_BrakeSystemStatus;
    VehicleEventFlags_bus m_DE_VehicleEventFlags;
    TransmissionState_bus m_DE_TransmissionState;
    SteeringWheelAngle_bus m_DE_SteeringWheelAngle;
    Speed_bus m_DE_Speed;
} VehCANData_dbus;

typedef struct _driveintention
{
    uint8_t m_u8GSPAintent;
    uint32_t m_u32GSPAvaildtime;
    uint8_t m_u8CLCintent;
    uint32_t m_u32CLCvaildtime;
} DriveIntention;
typedef struct bus_vds_veh_data
{
    /*static data*/
    uint8_t m_vehId[17];         //车辆ID
    int64_t m_time;              //获取车辆经纬度的时间
    uint16_t m_vehicleWidth;     //车宽，单位mm
    uint16_t m_vehicleLength;    //车长，单位mm
    uint16_t m_vehicleHeight;    //车高，单位mm
    uint8_t m_basicVehicleClass; //车辆类型

    /* IMU数据*/
    int m_int_acclng;  //纵向加速度
    int m_int_yawrate; //横摆角加速度
    int m_int_acclat;  //纵向加速度
    int m_int_accvert; //横摆角加速度

    /*GPS data*/
    GpsLocation_dbus m_gpsdata_st;
    /*The vehicle data*/
    VehCANData_dbus m_candata_st;
    DriveIntention m_driveIntent;
    EventFlagType m_warningevent; //车辆预警事件
} __attribute__((packed)) TVehData_t;
#define VDS_VEH_DATA_LEN_NEW (sizeof(TVdsVehDataNew_st)) //vds车辆数据长

#endif

enum
{
    MSG_VDS_VEH_DATA_ID = 0x1001,
    MSG_SYS_CONFIG_RQ_ID = 0x4001
};

enum
{
    MSG_V2X_SRV_MSG_ID = 0x2001,
    MSG_V2X_SRV_STATE_ID = 0x2002,
    MSG_V2X_SRV_FAULT_PUSH_ID = 0x2003,
    MSG_V2X_SRV_CFG_RS_ID = 0x2004,
    MSG_V2X_NET_COOPERATIVE_ID = 0x2005
};

enum
{
    MSG_V2X_SRV_STATE_LEN = 5U,
    MSG_V2X_SRV_FAULT_PUSH_LEN = 2U,
    MSG_V2X_SRV_CFG_RS_LEN = 1U,
    MSG_V2X_NET_COOPERATIVE_LEN = 168U
};

//从dbus接受的VDS数据帧结构
typedef struct
{
    uint16_t m_MsgID;
    uint16_t m_MsgLength;
    TVehData_t m_MsgData;
    uint8_t m_Bcc;
} __attribute__((packed)) TMsgVehDataFrame_t;

/*
     0--success
    -1--MsgLayer Encode error
    -2--SecureLayer Encode error
    -3--NetLayer Encode error
    -4-- Send erroV2Xr
    */
enum
{
    ERR_SUCCESS = 0,
    ERR_MSG_LAYER_ENCODE = -1,
    ERR_SECURE_LAYER_ENCODE = -2,
    ERR_NET_LAYER_ENCODE = -3,
    ERR_V2X_SEND = -4
};

enum
{
    IS_TROUBLE = 0x80,
    IS_RECOVERY = 0x81,
    IS_DEFAULT = 0xFF
};

typedef struct _Sendbuffer
{
    pthread_mutex_t m_muxtex;
    MSG_MessageType_st m_msgbufer;
} SendBuffer;

V2X_END_HEADER

#endif
