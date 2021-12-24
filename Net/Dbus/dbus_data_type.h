#pragma once
#include <stdint.h>

#ifdef _WIN32
#pragma pack(push, 1)
#endif

#ifdef _WIN32
#define PAKAGE_ALIGN
#else
#define PAKAGE_ALIGN __attribute__((packed))
#endif // __WIN32

// APP端DBus协议
#define MAX_ADVE_VEH_NUM 100
#define MAX_TRFC_INFO_NUM 16
#define MAX_SUGG_INFO_NUM 255

typedef enum _upLoadID_en
{
    allHave = 0b111, // 有自车信息，有预警信息，有邻车消息.
    noWarn = 0b101,  // 有自车信息，无预警信息，有邻车消息.
    noRound = 0b110  // 有自车信息，有预警信息，无邻车消息.
} upLoadID_en;

// 预警类型
typedef enum _warnStateV2V_en
{
    WNS_DEFAULT = 0x0000, // 默认状态.
    WNS_FCW = 0x0001,     // 前向碰撞预警.
    WNS_ICW = 0x0002,     // 交叉路口碰撞预警.
    WNS_LTA = 0x0003,     // 左转辅助.
    WNS_BSW = 0x0004,     // 盲区预警.
    WNS_LCW = 0x0005,     // 变道预警.
    WNS_DNPW = 0x0006,    // 逆向超车预警.
    WNS_EBW = 0x0007,     // 紧急制动预警.
    WNS_AVW = 0x0008,     // 异常车辆提醒.
    WNS_CLW = 0x0009,     // 失控车辆预警.
    WNS_EVW = 0x000A,     // 紧急车辆预警.
    WNS_VRUCW = 0x000B,   // 弱势交通参与者车辆预警.
    WNS_TCW = 0x000C,     // 跟车过近.
    WNS_SSW = 0x000D,     // 静止车辆预警.
    WNS_LSW = 0x000F,     // 慢速车辆预警.
} warnStateV2V_en;

// 相对方位
typedef enum _relativeOrientation_en
{
    RLO_DEFAULT = 0,
    FRONT_RLO = 1,        // 前方.
    FRONT_RLO_DIRECT = 2, // 正前方.
    BACK_RLO = 3,         // 后方.
    BACK_RLO_SIDE = 4,    // 侧后方.
    FRONT_RLO_Left = 5,   // 左前方.
    FRONT_RLO_Right = 6,  // 右前方.
    BACK_RLO_Left = 7,    // 左后方.
    BACK_RLO_Right = 8,   // 右后方.
} relativeOrientation_en;

// 转向信息
typedef enum _turningOri_en
{
    turnOri_left = 1,  // 左转.
    turnOri_front = 2, // 直行(默认).
    turnOri_right = 3  // 右转.
} turningOri_en;

// 优先级
typedef enum WARN_PRIO
{
    PRIO_DEFAULT = 0,
    HIGH_PRIO = 4,
    MEDIUM_PRIO = 3,
    LOW_PRIO = 2,
    Lower_V2I_PRIO = 1
} WARN_PRIO;

typedef struct _AroundVehInfo
{
    uint8_t nAdveUEID[8]; // 邻车UEID
    uint32_t nAdveLat;    // 邻车纬度
    uint32_t nAdveLong;   // 邻车经度
    uint16_t nAdveTrack;  // 邻车航向角
    uint16_t nAdveSpeed;  // 邻车车速
    uint16_t nAdveAccY;   // 邻车纵向加速度
    uint16_t nAdveAccX;   // 邻车横向加速度
    uint16_t nAdveAccZ;   // 邻车垂直加速度
    uint16_t nAdveLgtSt;  // 车身周围车灯状态
    uint8_t nAdveVehCls;  // 邻车车辆类型
    uint8_t nAdveGear;    // 邻车车辆档位状态
    uint8_t nAdveBreak;   // 邻车刹车踏板状态
} PAKAGE_ALIGN AroundVehInfo;

typedef struct _ActSafe
{
    uint16_t ID;      // 信号ID
    uint16_t LENGTH;  // DATA数据长度
    uint8_t upLoadID; // 信息上传标识
    //自车信息
    uint8_t UEID[8];     // 自车UEID
    uint32_t nSelfLat;   // 自车纬度
    uint32_t nSelfLong;  // 自车经度
    uint16_t nSelfSpeed; // 自车车速
    uint16_t nSelfTrack; // 自车方向
    uint8_t nSelfTurn;   // 转向信息
    //危险车辆信息
    uint8_t dangerAdveUEID[8];        // 危险状态车ID
    uint16_t nAdveSafeState;          // 危险车预警信息
    uint8_t nAdvePriority;            // 危险车安全状态优先级
    uint8_t nAdveRelativeOrientation; //危险车相对方位
    uint16_t nAdveCnt;                // 周围车个数
    AroundVehInfo aAdveVeh[MAX_ADVE_VEH_NUM];
    uint8_t BBC; //奇偶校验位
} PAKAGE_ALIGN ResultActSafe;

//####################RSI消息##########################

typedef enum _warnStateV2I_en
{
    V2I_STR_DEFAULT = -1,   // 默认状态.
    RTS_Warning = (1 << 1), // RTS
    RTE_Warning = (1 << 2), // RTE
    SLW_Warning = (1 << 3), // 道路限速提醒
} warnStateV2I_en;

typedef struct _TrfcRemindInfo
{
    uint8_t wStr;         //V2I应用场景
    uint16_t RsiType;     //RSI事件类型
    uint32_t dAdveLat;    //RSI事件纬度
    uint32_t dAdveLong;   //RSI事件经度
    uint16_t DesLen;      //事件描述内容长度
    uint8_t DesFlag;      //事件内容编码
    uint8_t DesData[256]; //事件描述内容
} PAKAGE_ALIGN TrfcRemindInfo;

typedef struct _TrfcRemind
{
    uint16_t ID;          // 信号ID
    uint16_t LENGTH;      //DATA数据长度
    uint16_t dAdveRsiCnt; //周围RSI消息
    TrfcRemindInfo aTrfcInfo[MAX_TRFC_INFO_NUM];
    uint8_t BBC; //奇偶校验位
} PAKAGE_ALIGN ResultTrfcRemind;

// ###################SPAT红绿灯和车速引导################

typedef enum _spdGuideV2I_en
{
    SPAT_INFO = (1 << 0),     // 红绿灯提示（默认）
    GLOSA_Warning = (1 << 1), // 速度引导.
    RLVW_Waring = (1 << 2),   // 闯红灯预警
} spdGuideV2I_en;

typedef enum _lightStat_en
{
    unavailable = 0,      // 不可用
    dark = 1,             // 关闭
    flashing_red = 2,     // 红闪
    red = 3,              // 红灯
    flashing_green = 4,   // 绿闪
    permissive_green = 5, // 绿灯
    protected_green = 6,  // 绿灯
    yellow = 7,           // 黄灯
    flashing_yellow = 8   // 黄闪
} lightStat_en;

typedef enum _lightDire_en
{
    lightDire_none = 0,         // 未知
    lightDire_left = 1,         // 左转
    lightDire_forward = 2,      // 直行
    lightDire_right = 3,        // 右转
    lightDire_leftForward = 4,  // 左转直行
    lightDire_rightForward = 5, // 右转直行
    lightDire_leftRight = 6,    // 左转右转
    lightDire_turnOver = 7,     // 掉头
    lightDire_leftOver = 8,     // 左转掉头
    lightDire_forwardOver = 9,  // 直行掉头
} lightDire_en;

typedef enum _suggManner_en
{
    manner_stay = 1,       // 保持车速
    manner_decelerate = 2, // 减速慢行
    manner_wait = 3,       // 停车等待
    manner_start = 4,      // 绿灯，车辆起步注意安全
    manner_speed = 5,      // 实际速度
} suggManner_en;

typedef struct _SuggInfo
{
    uint16_t phaseId;       //相位ID
    uint8_t Status;         //灯色状态
    uint8_t LightDirection; //灯的方向
    uint8_t TimeLeft;       //剩余时间
    uint8_t SuggSdType;     //建议操作
    uint8_t SuggSd;         //建议时速
} PAKAGE_ALIGN SuggInfo;

typedef struct _SpdGuide
{
    uint16_t ID;       // 信号ID
    uint16_t LENGTH;   // DATA数据长度
    uint32_t SPATLat;  //信号灯纬度
    uint32_t SPATLong; //信号灯经度
    uint8_t wType;     //应用场景
    uint8_t PhaseCnt;  //前方相位个数
    SuggInfo aSuggInfo[MAX_SUGG_INFO_NUM];
    uint8_t BBC; //奇偶校验位
} PAKAGE_ALIGN ResultSpdGuide;

//################# RSM 弱势交通参与者################

typedef enum _warnStateV2P_en
{
    V2P_DEFAULT = 0x0000,   // 默认状态.
    VRUCW_Warning = 0x000B, // 弱势交通参与者车辆预警.
} warnStateV2P_en;

typedef struct _AroundParticiptInfo
{
    uint16_t nAdvePtcID; // 车辆ID
    uint8_t nAdveVehCls; // 车辆类型
    uint32_t nAdveLat;   // 纬度
    uint32_t nAdveLong;  // 经度
    uint8_t nAdveColor;  // 车身颜色
    uint16_t nAdveHead;  // 航向角
} PAKAGE_ALIGN AroundParticiptInfo;

typedef struct _ResultVulSafe
{
    uint16_t ID;                      // 信号ID
    uint16_t LENGTH;                  // DATA数据长度
    uint32_t nLidarLat;               // 激光器纬度
    uint32_t nLidarLng;               // 激光器纬度
    uint8_t uploadID;                 // 预警信息
    uint16_t dangerAdvePtcID;         // 危险状态车ID
    uint16_t nAdveSafeState;          // 危险车预警信息
    uint8_t nAdvePriority;            // 危险车安全状态优先级
    uint8_t nAdveRelativeOrientation; // 危险车相对方位
    uint8_t nAdveCnt;                 // 交通参与者个数
    AroundParticiptInfo aAdveVeh[MAX_ADVE_VEH_NUM];
    uint8_t BBC; //奇偶校验位
} PAKAGE_ALIGN ResultVulSafe;

typedef struct _ResultSysFrame
{
    uint16_t ID;
    uint16_t LENGTH;
    uint8_t AppNotify;
    uint8_t V2xNotify;
    uint8_t VdsNotify;
    uint8_t NetNotify;
    uint8_t BBC;
} PAKAGE_ALIGN ResultSysFrame;

// DBUS传输匹配结果
typedef struct _VehMapMatchInfo
{
    uint16_t m_id;             //信号ID
    uint16_t m_length;         //信号长度
    uint64_t m_nTime;          // 获取匹配结果的时间
    uint8_t m_nFlag;           // 当前是否存在地图匹配结果
    uint32_t m_nNodeId[2];     // 匹配路段的上下游NodeId
    uint32_t m_MapId;          // 匹配地图的ID
    uint32_t m_SegmentId;      // 匹配路段的ID
    uint8_t m_LaneId;          // 匹配道路的ID
    double m_nVehPos[2];       // 匹配时车辆的经纬度
    double m_dRoadStartPos[2]; // 当前道路末端节点的经纬度
    double m_dRoadEndPos[2];   // 当前道路末端节点的经纬度
    double m_dCrossDis[2];     // 距离起始节点和终止节点的距离 负值表示还没有走到 正值表示离开的距离
    uint8_t m_bcc;             //信号校验（异或校验）
} PAKAGE_ALIGN VehMapMatchInfo;
extern VehMapMatchInfo g_tVehMapMatchInfo; // DBUS传输匹配结果

//################# 发送模拟can至VDS################
typedef struct _SendSimCan
{
    uint16_t ID;     // 信号ID
    uint16_t LENGTH; // DATA数据长度
    uint8_t GearState;
    uint8_t BrakePedalStatus;
    uint8_t TractionControlSystem;
    uint8_t VehicleClass;
    uint16_t ExteriorLights;
    uint8_t BBC; //奇偶校验位
} PAKAGE_ALIGN SendSimCan;

//################# 发送sys配置应答################
typedef struct _SendCfgRs
{
    uint16_t ID;
    uint16_t LENGTH;
    uint8_t CfgRs;
    uint8_t BBC;
} PAKAGE_ALIGN SendCfgRs;

//################# 发送NET状态################
typedef struct _SendNetStatus
{
    uint16_t ID;
    uint16_t LENGTH;
    uint32_t CltCnt;
    uint32_t RcvCltCnt;
    uint32_t SdCltCnt;
    uint32_t SdCloudCnt;
    uint8_t BBC;
} PAKAGE_ALIGN SendNetStatus;

//#################### 接收VDS数据 ####################
enum
{
    MSG_VDS_VEH_DATA_ID = 0x1001,
    MSG_SYS_CONFIG_RQ_ID = 0x4001
};
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
} PAKAGE_ALIGN EventFlagType;
typedef struct _driveintention
{
    uint8_t m_u8GSPAintent;
    uint32_t m_u32GSPAvaildtime;
    uint8_t m_u8CLCintent;
    uint32_t m_u32CLCvaildtime;
} DriveIntention;
typedef struct bus_Speed_Type
{
    double m_dbl_SpeedData;
    uint64_t m_u64_SpeedData_timestamp;
} Speed_bus;
typedef struct bus_SteeringWheelAngle_Type
{
    double m_dbl_SteeringWheelAngleData;
    uint64_t m_u64_SteeringWheelAngle_timestamp;
} SteeringWheelAngle_bus;
typedef struct bus_TransmissionState_Type
{
    uint8_t m_u8_TransmissionStateData;
    uint64_t m_u64_TransmissionStateData_timestamp;
} TransmissionState_bus;
typedef struct bus_VehicleEventFlags_Type
{
    uint8_t m_u8_VehicleEventFlagsData;
    uint64_t m_u64_VehicleEventFlagsData_timestamp;
} VehicleEventFlags_bus;
typedef struct bus_BrakeSystenStatus_Type
{
    uint8_t m_u8_BrakeSystemStatusData;
    uint64_t m_u64_BrakeSystenStatus_timestamp;
} BrakeSystenStatus_bus;
typedef struct bus_VehLampData_Type
{
    uint8_t m_u8_RecVehLampMessage;
    uint64_t m_u64_VehGNSS_timestamp;
} VehLampType_bus;
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
    DriveIntention m_driverIntent;
    EventFlagType m_warningevent; //车辆预警事件
} PAKAGE_ALIGN TVehData_t;
#define VDS_VEH_DATA_LEN_NEW (sizeof(TVdsVehDataNew_st)) //vds车辆数据长
//从dbus接受的VDS数据帧结构
typedef struct
{
    uint16_t m_MsgID;
    uint16_t m_MsgLength;
    TVehData_t m_MsgData;
    uint8_t m_Bcc;
} PAKAGE_ALIGN TMsgVehDataFrame_t;
extern TMsgVehDataFrame_t g_tDbusVehDataFrame;

typedef struct _PlanpathPoint
{
    uint32_t planpathPointlat;
    uint32_t planpathPointlon;
} PlanpathPoint_t;
typedef struct
{
    uint16_t m_MsgID; // 信号ID
    uint16_t m_MsgLength;
    uint8_t hv_id[8]; // 主车的ID
    // double hv_lat;           // 主车的纬度
    // double hv_lon;           // 主车的经度
    // double hv_ele;           // 主车的海拔
    // double hv_head;          // 车头朝向(0°~360°)，正北为 0，顺时针旋转的角度
    // double hv_speed;         // 本车速度m/s
    uint8_t guideStart;      //引导信息状态 0：引导失败 1：引导成功
    uint8_t collSceType;     //协同场景类型
    uint8_t bootDeviceType;  //引导设备类型  0：目标未知  1：RSU引导 2：OBU引导
    uint8_t bootDeviceId[8]; //引导设备ID
    uint32_t bootDeviceLat;  //引导设备纬度
    uint32_t bootDeviceLng;  //引导设备经度
    uint16_t driving_advice; //驾驶建议
    uint16_t arrival_time;   //到达时间
    uint32_t tarLat;         //路径目标点纬度
    uint32_t tarLon;         //路径目标点经度
    uint8_t planpathpoints;  //规划路径点的数目
    PlanpathPoint_t planpathpoint[16];
    uint8_t BBC; //奇偶校验位
} PAKAGE_ALIGN RoadsideCoordination_t;
#ifdef _WIN32
#pragma pack(pop)
#endif