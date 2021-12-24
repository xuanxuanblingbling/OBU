#ifndef PLATFORM_WARN_TYPE
#define PLATFORM_WARN_TYPE
#include <stdint.h>

#if defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64
#pragma pack(push, 1)
#define PACKAGE_ALIGN
#else
#define PACKAGE_ALIGN __attribute__((packed))
#endif

#define RV_Source_BSM 1
#define RV_Source_RSM 2
#define RV_Source_UNKOWN 0

#define TZ_LATFORMTEST 1
#define TZ_PLATFORM_V2VTEST 1
#define TZ_PLATFORM_SPATTEST 0
#define TZ_PLATFORM_SLWTEST 0
#define TZ_PLATFORM_RSITEST 0

typedef enum _V2xPtcpType
{
    V2xPtcpType_UNKNOWN = 0,
    V2xPtcpType_MOTOR = 1,
    V2xPtcpType_NON_MOTOR = 2,
    V2xPtcpType_PEDESTRIAN = 3,
    V2xPtcpType_RSU = 4,
    V2xPtcpType_TRUCK = 5
} V2xPtcpType;

typedef enum _V2xWarningType
{
    V2xWarningType_None = 0,
    V2xWarningType_V2V = 101,
    V2xWarningType_SPAT = 102,
    V2xWarningType_RTES = 103,
    V2xWarningType_RTSS = 104
} V2xWarningType;

typedef enum _V2xGnssStatus
{
    V2xGnssStatus_None = 0,
    V2xGnssStatus_E1 = 1,
    V2xGnssStatus_E2 = 2,
    V2xGnssStatus_E4 = 4,
    V2xGnssStatus_E5 = 5,
} V2xGnssStatus;

typedef enum _V2xSpatWarnType
{
    V2xSpatWarnType_None = 0,
    V2xSpatWarnType_Normal = 1,
    V2xSpatWarnType_SVW = 2,
    V2xSpatWarnType_GLOSA = 3
} V2xSpatWarnType;

typedef enum _V2xSubWarnType
{
    V2xSubWarnType_FCW = 1,     // 前向碰撞预警
    V2xSubWarnType_ICW = 2,     // 交叉路口碰撞预警
    V2xSubWarnType_LTA = 3,     // 左转辅助
    V2xSubWarnType_BSW_LCW = 4, // 盲区预警/变道预警
    V2xSubWarnType_DNPW = 5,    // 逆向超车预警
    V2xSubWarnType_EBW = 6,     // 紧急制动预警
    V2xSubWarnType_AVW = 7,     // 异常车辆预警
    V2xSubWarnType_CLW = 8,     // 车辆失控预警
    V2xSubWarnType_EVW = 9,     // 紧急车辆让贤
    V2xSubWarnType_VRUCW = 200, // 弱势交通参与者
    V2xSubWarnType_SLW = 201,   // 车辆限速预警
} V2xSubWarnType;

typedef struct _V2xCollisionWarn
{
    uint8_t rv_source;      // V2v中远车的来源，BSM\RSM
    V2xSubWarnType subtype; // 参考V2X事件标识标定说明
    uint8_t rv_id[8];       // 远车车辆ID
    V2xPtcpType ptcp_type;  // 交通参与者的类型
    uint8_t veh_class;      // 远车的类型
    uint16_t ptcp_id;       // 远车的ID
    double rv_lat;          // 远车的纬度
    double rv_lon;          // 远车的经度
    double rv_ele;          // 远车的海拔
    double rv_heading;      // 远车的航向角
    double rv_speed;        // 远车的速度 m/s
    double rv_distance;     // 远车距离本车的距离 m/s
    double rv_ttc;          // 远车的 ttc s
    float max_speed_limit;  // m/s 限速车速上限
    float min_speed_limit;  // m/s 限速车速下限
} PACKAGE_ALIGN V2xCollisionWarn;

typedef struct _V2xSpatWarn
{
    uint16_t spat_region_id;    // 区域号
    uint16_t spat_intersect_id; // 路口号; 区域号路口号用于唯一标识信号机身份
    V2xSpatWarnType spat_warn;  // 信号灯预警
    uint8_t phase_id;           // 红绿灯相位ID
    uint8_t light_state;        // 灯色状态 1:绿色; 2:红色; 3:黄色
    uint8_t phase_state;        // 转向关系, 直行、左转、右转等--ZZH
    uint16_t time_left;         // 剩余时间 单位秒
    float max_guid_speed;       // 绿波车速引导下限  m/s
    float min_guid_speed;       // 绿波车速引导上限  m/s
} PACKAGE_ALIGN V2xSpatWarn;

typedef struct _V2xRsiWarn
{
    uint8_t rsu_id[8];        // V2I事件时生效 RSU ID
    uint8_t priority;         // 优先级 0-7 ，数字越小，优先级越高
    double rsu_lat;           // RSU的纬度
    double rsu_lon;           // RSU的经度
    double rsu_ele;           // RSU的海拔
    uint16_t rsi_type;        // RSI的事件类型
    double rsi_start_lon;     // RSI的起点的经度
    double rsi_start_lat;     // RSI的起点的纬度
    double rsi_end_lon;       // RSI的终点的经度
    double rsi_end_lat;       // RSI的终点的纬度
    uint16_t content_len;     // RSI事件内容的长度
    uint8_t rsi_content[256]; // RSI的内容
} PACKAGE_ALIGN V2xRsiWarn;

typedef struct _V2xPlatformSceneWarn
{
    int64_t timestamp;         // 事件戳
    uint8_t hv_id[8];          // 主车的ID
    double hv_lat;             // 主车的纬度
    double hv_lon;             // 主车的经度
    double hv_ele;             // 主车的海拔
    double hv_head;            // 车头朝向(0°~360°)，正北为 0，顺时针旋转的角度
    double hv_speed;           // 本车速度m/s
    V2xGnssStatus gnss_status; // gnss的状态
    uint8_t hv_type;           // 1:特殊车辆; 10:普通轿车; 60:紧急车辆; BRT:52; 快速公交:53; 本地公交:54; 校车:55
    uint32_t hv_node_id;       // 主车地图匹配的节点ID
    uint8_t hv_lane_id;        // 主车地图匹配的车道ID
    V2xWarningType type;       // 101：V2V事件，102：红绿灯事件，103：交通事件，104：交通标识
    union V2xSceneWarn
    {
        V2xCollisionWarn collision_warn;
        V2xSpatWarn spat_warn;
        V2xRsiWarn rsi_warn;
    } warn;
} PACKAGE_ALIGN V2xPlatformSceneWarn;

typedef struct _V2xPlatformSceneWarnDbus
{
    uint16_t ID;     // 信号ID
    uint16_t LENGTH; // DATA数据长度
    V2xPlatformSceneWarn v2xplatformsceneWarn;
    uint8_t BBC; //奇偶校验位
} PACKAGE_ALIGN V2xPlatformSceneWarnDbus;

#if defined _WIN32 || defined WIN32 || defined _WIN64 || defined WIN64
#pragma pack(pop)
#endif

#endif
