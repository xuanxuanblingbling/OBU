/**
* @file         :wjvn4_uper_Df.h
* @brief        :数据帧结构相关结构体头文件定义
* @details      :主要包含数据帧结构相关结构体定义
* @author       :huangsai  any question please send mail to huangsai@wanji.net.cn
* @date         :2020-12-15
* @version      :V1.0
* @copyright    :Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：IMX6
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-15  <td>V1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
#ifndef __WJVN4_UPER_DF_H_
#define __WJVN4_UPER_DF_H_
/*********************************头文件包含********************************************/
#include "wjvn4_uper_De.h"
/*********************************标准头文件********************************************/

/*********************************自定义头文件******************************************/
typedef struct _vn4AccelerationSet4Way
{
    WJVN4_INT_Acceleration n32long;
    WJVN4_INT_Acceleration n32lat;
    WJVN4_INT_VerticalAcceleration n32vert;
    WJVN4_INT_YawRate n32yaw;
} __attribute__((packed)) WJVN4_STRU_AccelerationSet4Way; /* 车辆四轴加速度 */
typedef struct _vn4BrakeSystemStatus
{
    uint8_t u8brakePadelPresent;
    WJVN4_ENUM_BrakePedalStatus enumbrakePadel; /* OPTIONAL */
    uint8_t u8wheelBrakesPresent;
    WJVN4_BIT_BrakeAppliedStatus strbitwheelBrakes; /* OPTIONAL */
    uint8_t u8tractionPresent;
    WJVN4_ENUM_TractionControlStatus enumtraction; /* OPTIONAL */
    uint8_t u8absPresent;
    WJVN4_ENUM_AntiLockBrakeStatus enumabs; /* OPTIONAL */
    uint8_t u8scsPresent;
    WJVN4_ENUM_StabilityControlStatus enumscs; /* OPTIONAL */
    uint8_t u8brakeBoostPresent;
    WJVN4_ENUM_BrakeBoostApplied enumbrakeBoost; /* OPTIONAL */
    uint8_t u8auxBrakesPresent;
    WJVN4_ENUM_AuxiliaryBrakeStatus enumauxBrakes;      /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_BrakeSystemStatus; /* 车辆的刹车系统状态 */
typedef struct _vn4ConnectingLane
{
    WJVN4_INT_LaneID n32lane;
    uint8_t u8maneuverPresent;
    WJVN4_BIT_AllowedManeuvers strbitmaneuver;       /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_ConnectingLane; /* 定位上游车道转向连接的下游车道 */
typedef struct _vn4NodeReferenceID
{
    uint8_t u8regionPresent;
    WJVN4_INT_RoadRegulatorID n32region; /* OPTIONAL */
    WJVN4_INT_NodeID n32id;
} __attribute__((packed)) WJVN4_STRU_NodeReferenceID; /* 节点ID */
typedef struct _vn4Connection
{
    WJVN4_STRU_NodeReferenceID struremoteIntersection;
    uint8_t u8connectingLanePresent;
    WJVN4_STRU_ConnectingLane struconnectingLane; /* OPTIONAL */
    uint8_t u8phaseIdPresent;
    WJVN4_INT_PhaseID n32phaseId;                /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_Connection; /* 当前车道与下游路段中车道的连接关系 */
#define WJVN4_MAX_LIST_CONNECTION_LEN 8
#define WJVN4_MIN_LIST_CONNECTION_LEN 1
typedef struct _vn4ConnectsToList
{
    uint8_t u8ConnectionNum; /* 1 ~ 8 */
    WJVN4_STRU_Connection struConnection[WJVN4_MAX_LIST_CONNECTION_LEN];
} __attribute__((packed)) WJVN4_STRU_ConnectsToList; /* 路段中每条车道，在下游路口处与下游路段中车道的转向连接关系列表 */
typedef struct _vn4DDateTime
{
    uint8_t u8yearPresent;
    WJVN4_INT_DYear n32year; /* OPTIONAL */
    uint8_t u8monthPresent;
    WJVN4_INT_DMonth n32month; /* OPTIONAL */
    uint8_t u8dayPresent;
    WJVN4_INT_DDay n32day; /* OPTIONAL */
    uint8_t u8hourPresent;
    WJVN4_INT_DHour n32hour; /* OPTIONAL */
    uint8_t u8minutePresent;
    WJVN4_INT_DMinute n32minute; /* OPTIONAL */
    uint8_t u8secondPresent;
    WJVN4_INT_DSecond n32second; /* OPTIONAL */
    uint8_t u8offsetPresent;
    WJVN4_INT_DTimeOffset n32offset;            /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_DDateTime; /* 完整的日期和时间数据单元 */
typedef enum
{

    WJVN4_DescriptionNOTHING = 0,
    WJVN4_DescriptiontextString = 1,
    WJVN4_DescriptiontextGB2312 = 2,
} WJVN4_ENUM_DescriptionStringChoice;
typedef struct _vn4Description
{
    WJVN4_ENUM_DescriptionStringChoice enumDescriptionStringChoice;
    uint32_t u32textNum;
    union
    {
#define WJVN4_MAX_IA5_STRING_LEN 512
#define WJVN4_MIN_IA5_STRING_LEN 1
        uint8_t u8textString[WJVN4_MAX_IA5_STRING_LEN]; /* 1 ~ 512 */
#define WJVN4_MAX_OCT_STRING_LEN 256
#define WJVN4_MIN_OCT_STRING_LEN 1
        uint16_t u16textGB2312[WJVN4_MAX_OCT_STRING_LEN]; /* 2 ~ 512 */
    } u;
} __attribute__((packed)) WJVN4_STRU_Description; /* 文本描述信息 */
typedef struct _vn4MotionConfidenceSet
{
    uint8_t u8speedCfdPresent;
    WJVN4_ENUM_SpeedConfidence enumspeedCfd; /* OPTIONAL */
    uint8_t u8headingCfdPresent;
    WJVN4_ENUM_HeadingConfidence enumheadingCfd; /* OPTIONAL */
    uint8_t u8steerCfdPresent;
    WJVN4_ENUM_SteeringWheelAngleConfidence enumsteerCfd; /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_MotionConfidenceSet; /* 车辆运行状态的精度 */
typedef struct _vn4PositionConfidenceSet
{
    WJVN4_ENUM_PositionConfidence enumpos;
    uint8_t u8elevationPresent;
    WJVN4_ENUM_ElevationConfidence enumelevation;           /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_PositionConfidenceSet; /* 当前实时位置（经纬度和高程）的精度大小 */
typedef struct _vn4Position3D
{
    WJVN4_INT_Latitude n32lat;
    WJVN4_INT_Longitude n32long;
    uint8_t u8elevationPresent;
    WJVN4_INT_Elevation n32elevation;            /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_Position3D; /* 三维的坐标位置，经纬度和高程 */
typedef struct _vn4PositionalAccuracy
{
    WJVN4_INT_SemiMajorAxisAccuracy n32semiMajor;
    WJVN4_INT_SemiMinorAxisAccuracy n32semiMinor;
    WJVN4_INT_SemiMajorAxisOrientation n32orientation;
} __attribute__((packed)) WJVN4_STRU_PositionalAccuracy; /* 基于椭圆模型定义一个定位系统自身的精度 */
typedef struct _vn4FullPositionVector
{
    uint8_t u8utcTimePresent;
    WJVN4_STRU_DDateTime struutcTime; /* OPTIONAL */
    WJVN4_STRU_Position3D strupos;
    uint8_t u8headingPresent;
    WJVN4_INT_Heading n32heading; /* OPTIONAL */
    uint8_t u8transmissionPresent;
    WJVN4_ENUM_TransmissionState enumtransmission; /* OPTIONAL */
    uint8_t u8speedPresent;
    WJVN4_INT_Speed n32speed; /* OPTIONAL */
    uint8_t u8posConficencePresent;
    WJVN4_STRU_PositionConfidenceSet struposConficence; /* OPTIONAL */
    uint8_t u8timeConfidencePresent;
    WJVN4_ENUM_TimeConfidence enumtimeConfidence; /* OPTIONAL */
    uint8_t u8motionCfdPresent;
    WJVN4_STRU_MotionConfidenceSet strumotionCfd;        /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_FullPositionVector; /* 完整的参考轨迹点信息 */
typedef struct _vn4TimeCountingDown
{
    WJVN4_INT_TimeMark n32startTime;
    uint8_t u8minEndTimePresent;
    WJVN4_INT_TimeMark n32minEndTime; /* OPTIONAL */
    uint8_t u8maxEndTimePresent;
    WJVN4_INT_TimeMark n32maxEndTime; /* OPTIONAL */
    WJVN4_INT_TimeMark n32likelyEndTime;
    uint8_t u8timeConfidencePresent;
    WJVN4_INT_Confidence n32timeConfidence; /* OPTIONAL */
    uint8_t u8nextStartTimePresent;
    WJVN4_INT_TimeMark n32nextStartTime; /* OPTIONAL */
    uint8_t u8nextDurationPresent;
    WJVN4_INT_TimeMark n32nextDuration;                /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_TimeCountingDown; /* 用倒计时形式，描述一个信号灯相位状态的完整计时状态 */
typedef struct _vn4UTCTiming
{
    WJVN4_INT_TimeMark n32startUTCTime;
    uint8_t u8minEndUTCTimePresent;
    WJVN4_INT_TimeMark n32minEndUTCTime; /* OPTIONAL */
    uint8_t u8maxEndUTCTimePresent;
    WJVN4_INT_TimeMark n32maxEndUTCTime; /* OPTIONAL */
    WJVN4_INT_TimeMark n32likelyEndUTCTime;
    uint8_t u8timeConfidencePresent;
    WJVN4_INT_Confidence n32timeConfidence; /* OPTIONAL */
    uint8_t u8nextStartUTCTimePresent;
    WJVN4_INT_TimeMark n32nextStartUTCTime; /* OPTIONAL */
    uint8_t u8nextEndUTCTimePresent;
    WJVN4_INT_TimeMark n32nextEndUTCTime;       /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_UTCTiming; /* 一个信号灯相位状态的完整计时状态 */
typedef enum
{
    WJVN4_TimeChangeDetailsDOWN = 0, /* 倒计时 */
    WJVN4_TimeChangeDetailsUTC = 1,  /* 正数 */
} WJVN4_ENUM_TimeChangeDetailsChoice;
typedef struct _vn4TimeChangeDetails
{
    WJVN4_ENUM_TimeChangeDetailsChoice enumTimeChangeDetails;
    union
    {
        WJVN4_STRU_TimeCountingDown strucounting;
        WJVN4_STRU_UTCTiming struutcTiming;
    } u;
} __attribute__((packed)) WJVN4_STRU_TimeChangeDetails; /* 信号灯相位的计时状态 */
typedef struct _vn4PhaseState
{
    WJVN4_ENUM_LightState enumlight;
    uint8_t u8timingPresent;
    WJVN4_STRU_TimeChangeDetails strutiming;     /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_PhaseState; /* 信号灯的一个相位状态 */
#define WJVN4_MAX_LIST_PHASESTATE_LEN 16
#define WJVN4_MIN_LIST_PHASESTATE_LEN 1
typedef struct _vn4PhaseStateList
{
    uint8_t u8PhaseStateNum; /* 1 ~ 16 */
    WJVN4_STRU_PhaseState struPhaseState[WJVN4_MAX_LIST_PHASESTATE_LEN];
} __attribute__((packed)) WJVN4_STRU_PhaseStateList; /* 一个信号灯的一个相位中的相位状态列表 */
typedef struct _vn4Phase
{
    WJVN4_INT_PhaseID n32id;
    WJVN4_STRU_PhaseStateList struphaseStates;
} __attribute__((packed)) WJVN4_STRU_Phase; /* 信号灯相位 */
#define WJVN4_MAX_LIST_PHASE_LEN 16
#define WJVN4_MIN_LIST_PHASE_LEN 1
typedef struct _vn4PhaseList
{
    uint8_t u8PhaseNum; /* 1 ~ 16 */
    WJVN4_STRU_Phase struPhase[WJVN4_MAX_LIST_PHASE_LEN];
} __attribute__((packed)) WJVN4_STRU_PhaseList; /* 一组信号灯包含的所有相位的列表 */
typedef struct _vn4IntersectionState
{
    WJVN4_STRU_NodeReferenceID struintersectionId;
    WJVN4_BIT_IntersectionStatusObject strbitstatus;
    uint8_t u8moyPresent;
    WJVN4_INT_MinuteOfTheYear n32moy; /* OPTIONAL */
    uint8_t u8timeStampPresent;
    WJVN4_INT_DSecond n32timeStamp; /* OPTIONAL */
    uint8_t u8timeConfidencePresent;
    WJVN4_ENUM_TimeConfidence enumtimeConfidence; /* OPTIONAL */
    WJVN4_STRU_PhaseList struphases;
} __attribute__((packed)) WJVN4_STRU_IntersectionState; /* 路口信号灯的属性和当前状态 */
#define WJVN4_MAX_LIST_INTERSECTIONSTATE_LEN 32
#define WJVN4_MIN_LIST_INTERSECTIONSTATE_LEN 1
typedef struct _vn4IntersectionStateList
{
    uint8_t u8IntersectionStateNum; /* 1 ~ 32 */
    WJVN4_STRU_IntersectionState struIntersectionState[WJVN4_MAX_LIST_INTERSECTIONSTATE_LEN];
} __attribute__((packed)) WJVN4_STRU_IntersectionStateList; /* 一个路口信号灯集合 */
typedef enum
{
    WJVN4_LaneAttributesVehicle = 0,
    WJVN4_LaneAttributesCrosswalk = 1,
    WJVN4_LaneAttributesBike = 2,
    WJVN4_LaneAttributesSidewalk = 3,
    WJVN4_LaneAttributesBarrier = 4,
    WJVN4_LaneAttributesStriping = 5,
    WJVN4_LaneAttributesTrackedVehicle = 6,
    WJVN4_LaneAttributesParking = 7
} WJVN4_ENUM_LaneTypeAttributesChoice;
typedef struct _vn4LaneTypeAttributes
{
    WJVN4_ENUM_LaneTypeAttributesChoice enumLaneTypeAttributesChoice;
    union
    {
        WJVN4_BIT_LaneAttributesVehicle strbitvehicle;
        WJVN4_BIT_LaneAttributesCrosswalk strbitcrosswalk;
        WJVN4_BIT_LaneAttributesBike strbitbikeLane;
        WJVN4_BIT_LaneAttributesSidewalk strbitsidewalk;
        WJVN4_BIT_LaneAttributesBarrier strbitmedian;
        WJVN4_BIT_LaneAttributesStriping strbitstriping;
        WJVN4_BIT_LaneAttributesTrackedVehicle strbittrackedVehicle;
        WJVN4_BIT_LaneAttributesParking strbitparking;
    } u;
} __attribute__((packed)) WJVN4_STRU_LaneTypeAttributes; /* 不同类别车道的属性集合 */
typedef struct _vn4LaneAttributes
{
    uint8_t u8shareWithPresent;
    WJVN4_BIT_LaneSharing strbitshareWith; /* OPTIONAL */
    WJVN4_STRU_LaneTypeAttributes strulaneType;
} __attribute__((packed)) WJVN4_STRU_LaneAttributes; /* 车道属性 */
typedef struct _vn4PositionLL24B
{
    WJVN4_INT_OffsetLLB12 n32lon;
    WJVN4_INT_OffsetLLB12 n32lat;
} __attribute__((packed)) WJVN4_STRU_PositionLL24B; /* 24比特相对经纬度位置 */
typedef struct _vn4PositionLL28B
{
    WJVN4_INT_OffsetLLB14 n32lon;
    WJVN4_INT_OffsetLLB14 n32lat;
} __attribute__((packed)) WJVN4_STRU_PositionLL28B; /* 28比特相对经纬度位置 */
typedef struct _vn4PositionLL32B
{
    WJVN4_INT_OffsetLLB16 n32lon;
    WJVN4_INT_OffsetLLB16 n32lat;
} __attribute__((packed)) WJVN4_STRU_PositionLL32B; /* 32比特相对经纬度位置 */
typedef struct _vn4PositionLL36B
{
    WJVN4_INT_OffsetLLB18 n32lon;
    WJVN4_INT_OffsetLLB18 n32lat;
} __attribute__((packed)) WJVN4_STRU_PositionLL36B; /* 36比特相对经纬度位置 */
typedef struct _vn4PositionLL44B
{
    WJVN4_INT_OffsetLLB22 n32lon;
    WJVN4_INT_OffsetLLB22 n32lat;
} __attribute__((packed)) WJVN4_STRU_PositionLL44B; /* 44比特相对经纬度位置 */
typedef struct _vn4PositionLL48B
{
    WJVN4_INT_OffsetLLB24 n32lon;
    WJVN4_INT_OffsetLLB24 n32lat;
} __attribute__((packed)) WJVN4_STRU_PositionLL48B; /* 48比特相对经纬度位置 */
typedef struct _vn4PositionLLmD64b
{
    WJVN4_INT_Longitude n32lon;
    WJVN4_INT_Latitude n32lat;
} __attribute__((packed)) WJVN4_STRU_PositionLLmD64b; /* 64比特经纬度位置 */
typedef enum
{
    WJVN4_PositionLL24B = 1,
    WJVN4_PositionLL28B,
    WJVN4_PositionLL32B,
    WJVN4_PositionLL36B,
    WJVN4_PositionLL44B,
    WJVN4_PositionLL48B,
    WJVN4_PositionLLmD64b
} WJVN4_ENUM_PositionOffsetLLChoice;
typedef struct _vn4PositionOffsetLL
{
    WJVN4_ENUM_PositionOffsetLLChoice enumPositionOffsetLLChoice;
    union
    {
        WJVN4_STRU_PositionLL24B strupositionLL1;
        WJVN4_STRU_PositionLL28B strupositionLL2;
        WJVN4_STRU_PositionLL32B strupositionLL3;
        WJVN4_STRU_PositionLL36B strupositionLL4;
        WJVN4_STRU_PositionLL44B strupositionLL5;
        WJVN4_STRU_PositionLL48B strupositionLL6;
        WJVN4_STRU_PositionLLmD64b strupositionLatLon;
    } u;
} __attribute__((packed)) WJVN4_STRU_PositionOffsetLL; /* 经纬度偏差 */
typedef enum
{
    WJVN4_VertOffsetB07 = 1,
    WJVN4_VertOffsetB08,
    WJVN4_VertOffsetB09,
    WJVN4_VertOffsetB10,
    WJVN4_VertOffsetB11,
    WJVN4_VertOffsetB12,
    WJVN4_Elevation
} WJVN4_ENUM_VerticalOffsetChoice;
typedef struct _vn4VerticalOffset
{
    WJVN4_ENUM_VerticalOffsetChoice enumVerticalOffsetChoice;
    union
    {
        WJVN4_INT_VertOffsetB07 n32offset1;
        WJVN4_INT_VertOffsetB08 n32offset2;
        WJVN4_INT_VertOffsetB09 n32offset3;
        WJVN4_INT_VertOffsetB10 n32offset4;
        WJVN4_INT_VertOffsetB11 n32offset5;
        WJVN4_INT_VertOffsetB12 n32offset6;
        WJVN4_INT_Elevation n32elevation;
    } u;
} __attribute__((packed)) WJVN4_STRU_VerticalOffset; /* 垂直方向位置偏差 */
typedef struct _vn4PositionOffsetLLV
{
    WJVN4_STRU_PositionOffsetLL struoffsetLL;
    uint8_t u8offsetVPresent;
    WJVN4_STRU_VerticalOffset struoffsetV;              /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_PositionOffsetLLV; /* 三维的相对位置（相对经纬度和相对高程） */
typedef struct _vn4RoadPoint
{
    WJVN4_STRU_PositionOffsetLLV struposOffset;
} __attribute__((packed)) WJVN4_STRU_RoadPoint; /* 完整道路上标记的一个位置点属性 */
#define WJVN4_MAX_LIST_ROADPOINT_LEN 31         /* 协议规定 2 ～ 32 暂定 2～ 10 */
#define WJVN4_MIN_LIST_ROADPOINT_LEN 2
typedef struct _vn4PointList
{
    uint8_t u8RoadPointNum; /* 2 ~ 31 */
    WJVN4_STRU_RoadPoint struRoadPoint[WJVN4_MAX_LIST_ROADPOINT_LEN];
} __attribute__((packed)) WJVN4_STRU_PointList; /* 一个有向路段上的中间位置点列表 */
typedef struct _vn4RegulatorySpeedLimit
{
    WJVN4_ENUM_SpeedLimitType enumtype;
    WJVN4_INT_Speed n32speed;
} __attribute__((packed)) WJVN4_STRU_RegulatorySpeedLimit; /* 限速属性 */
#define WJVN4_MAX_LIST_REGULATORYSPEEDLIMITNUM_LEN 9
#define WJVN4_MIN_LIST_REGULATORYSPEEDLIMITNUM_LEN 1
typedef struct _vn4SpeedLimitList
{
    uint8_t u8RegulatorySpeedLimitNum; /* 1 ~ 9 */
    WJVN4_STRU_RegulatorySpeedLimit struRegulatorySpeedLimit[WJVN4_MAX_LIST_REGULATORYSPEEDLIMITNUM_LEN];
} __attribute__((packed)) WJVN4_STRU_SpeedLimitList; /* 路段或车道的限速列表 */
typedef struct _vn4Lane
{
    WJVN4_INT_LaneID n32laneID;
    uint8_t u8laneWidthPresent;
    WJVN4_INT_LaneWidth n32laneWidth; /* OPTIONAL */
    uint8_t u8laneAttributesPresent;
    WJVN4_STRU_LaneAttributes strulaneAttributes; /* OPTIONAL */
    uint8_t u8maneuversPresent;
    WJVN4_BIT_AllowedManeuvers strbitmaneuvers; /* OPTIONAL */
    uint8_t u8connectsToPresent;
    WJVN4_STRU_ConnectsToList struConnectsToList; /* OPTIONAL */
    uint8_t u8speedLimitsPresent;
    WJVN4_STRU_SpeedLimitList struspeedLimits; /* OPTIONAL */
    uint8_t u8pointsPresent;
    WJVN4_STRU_PointList strupoints;       /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_Lane; /* 车道 */
#define WJVN4_MAX_LIST_LANE_LEN 16         /* 协议规定 1 ～ 32 暂定 1～ 16 */
#define WJVN4_MIN_LIST_LANE_LEN 1
typedef struct _vn4LaneList
{
    uint8_t u8LaneNum; /* 1 ~ 32 */
    WJVN4_STRU_Lane struLane[WJVN4_MAX_LIST_LANE_LEN];
} __attribute__((packed)) WJVN4_STRU_LaneList; /* 一个路段中包含的车道列表 */
typedef struct _vn4Movement
{
    WJVN4_STRU_NodeReferenceID struremoteIntersection;
    uint8_t u8phaseIdPresent;
    WJVN4_INT_PhaseID n32phaseId;              /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_Movement; /* 道路与下游路段的连接关系 */
#define WJVN4_MAX_LIST_MOVEMENT_LEN 8          /* 协议规定 1 ～ 32 暂定 1～ 8 */
#define WJVN4_MIN_LIST_MOVEMENT_LEN 1
typedef struct _vn4MovementList
{
    uint8_t u8MovementNum; /* 1 ~ 32 */
    WJVN4_STRU_Movement struMovement[WJVN4_MAX_LIST_MOVEMENT_LEN];
} __attribute__((packed)) WJVN4_STRU_MovementList; /* 一条路段与下游路段的连接关系列表 */
typedef struct _vn4Link
{
    uint8_t u8namePresent;
    WJVN4_IA5_DescriptiveName stria5name; /* OPTIONAL */
    WJVN4_STRU_NodeReferenceID struupstreamNodeId;
    uint8_t u8speedLimitsPresent;
    WJVN4_STRU_SpeedLimitList struspeedLimits; /* OPTIONAL */
    WJVN4_INT_LaneWidth n32linkWidth;
    uint8_t u8pointsPresent;
    WJVN4_STRU_PointList strupoints; /* OPTIONAL */
    uint8_t u8MovementListPresent;
    WJVN4_STRU_MovementList strumovements; /* OPTIONAL */
    WJVN4_STRU_LaneList strulanes;
} __attribute__((packed)) WJVN4_STRU_Link; /* 路段 */
#define WJVN4_MAX_LIST_LINK_LEN 8          /* 协议规定 1 ～ 32 暂定 1～ 8 */
#define WJVN4_MIN_LIST_LINK_LEN 1
typedef struct _vn4LinkList
{
    uint8_t u8LinkNum; /* 1 ~ 32 */
    WJVN4_STRU_Link struLink[WJVN4_MAX_LIST_LINK_LEN];
} __attribute__((packed)) WJVN4_STRU_LinkList; /* 路段列表 */
typedef struct _vn4Node
{
    uint8_t u8namePresent;
    WJVN4_IA5_DescriptiveName stria5name; /* OPTIONAL */
    WJVN4_STRU_NodeReferenceID struid;
    WJVN4_STRU_Position3D strurefPos;
    uint8_t u8inLinksPresent;
    WJVN4_STRU_LinkList struinLinks;       /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_Node; /* 地图节点 */
#define WJVN4_MAX_LIST_NODE_LEN 8          /* 协议规定 1 ～ 32 暂定 1～ 8 */
#define WJVN4_MIN_LIST_NODE_LEN 1
typedef struct _vn4NodeList
{
    uint8_t u8NodeNum; /* 1 ~ 32 */
    WJVN4_STRU_Node struNode[WJVN4_MAX_LIST_NODE_LEN];
} __attribute__((packed)) WJVN4_STRU_NodeList; /* 地图节点列表 */
typedef struct _vn4VehicleClassification
{
    WJVN4_INT_BasicVehicleClass n32classification;
    uint8_t u8fuelTypePresent;
    WJVN4_INT_FuelType n32fuelType;                         /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_VehicleClassification; /* 车辆的分类 */
typedef struct _vn4VehicleSize
{
    WJVN4_INT_VehicleWidth n32width;
    WJVN4_INT_VehicleLength n32length;
    uint8_t u8heightPresent;
    WJVN4_INT_VehicleHeight n32height;            /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_VehicleSize; /* 车辆尺寸大小 */
#define WJVN4_MAX_PTCID_SIZE 65535
#define WJVN4_MIN_PTCID_SIZE 0
typedef struct _vn4ParticipantData
{
    WJVN4_ENUM_ParticipantType enumptcType;
    uint32_t u32ptcId; /* 0 ~ 65535 0 is RSU itself */
    WJVN4_ENUM_SourceType enumsource;
    uint8_t u8OCTidPresent;
#define WJVN4_MAX_OCTID_SIZE 8
#define WJVN4_MIN_OCTID_SIZE 0
    uint8_t u8OCTid[WJVN4_MAX_OCTID_SIZE]; /* OPTIONAL */
    WJVN4_INT_DSecond n32secMark;
    WJVN4_STRU_PositionOffsetLLV strupos;
    WJVN4_STRU_PositionConfidenceSet struposConfidence;
    uint8_t u8transmissionPresent;
    WJVN4_ENUM_TransmissionState enumtransmission; /* OPTIONAL */
    WJVN4_INT_Speed n32speed;
    WJVN4_INT_Heading n32heading;
    uint8_t u8anglePresent;
    WJVN4_INT_SteeringWheelAngle n32angle; /* OPTIONAL */
    uint8_t u8motionCfdPresent;
    WJVN4_STRU_MotionConfidenceSet strumotionCfd; /* OPTIONAL */
    uint8_t u8accelSetPresent;
    WJVN4_STRU_AccelerationSet4Way struaccelSet; /* OPTIONAL */
    WJVN4_STRU_VehicleSize strusize;
    uint8_t u8vehicleClassPresent;
    WJVN4_STRU_VehicleClassification struvehicleClass; /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_ParticipantData;  /* 交通参与者的基本安全信息 */
#define WJVN4_MAX_LIST_PARTICIPANTDATA_LEN 16
#define WJVN4_MIN_LIST_PARTICIPANTDATA_LEN 1
typedef struct _vn4NodeListParticipantList
{
    uint8_t u8ParticipantDataNum; /* 1 ~ 16 */
    WJVN4_STRU_ParticipantData struParticipantData[WJVN4_MAX_LIST_PARTICIPANTDATA_LEN];
} __attribute__((packed)) WJVN4_STRU_ParticipantList; /* 地图节点列表 */
typedef struct _vn4PathHistoryPoint
{
    WJVN4_STRU_PositionOffsetLLV strullvOffset;
    WJVN4_INT_TimeOffset n32timeOffset;
    uint8_t u8speedPresent;
    WJVN4_INT_Speed n32speed;
    uint8_t u8posAccuracyPresent;
    WJVN4_STRU_PositionConfidenceSet struposAccuracy; /* OPTIONAL */
    uint8_t u8headingPresent;
    WJVN4_INT_CoarseHeading n32heading;                /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_PathHistoryPoint; /* 车辆的历史轨迹点 */
#define WJVN4_MAX_LIST_PATHHISTORYPOINT_LEN 23
#define WJVN4_MIN_LIST_PATHHISTORYPOINT_LEN 1
typedef struct _vn4PathHistoryPointList
{
    uint8_t u8PathHistoryPointNum; /* 1 ~ 23 */
    WJVN4_STRU_PathHistoryPoint struPathHistoryPoint[WJVN4_MAX_LIST_PATHHISTORYPOINT_LEN];
} __attribute__((packed)) WJVN4_STRU_PathHistoryPointList; /* 车辆的历史轨迹 */
typedef struct _vn4PathHistory
{
    uint8_t u8initialPositionPresent;
    WJVN4_STRU_FullPositionVector struinitialPosition; /* OPTIONAL */
    uint8_t u8currGNSSstatusPresent;
    WJVN4_BIT_GNSSstatus strbitcurrGNSSstatus; /* OPTIONAL */
    WJVN4_STRU_PathHistoryPointList strucrumbData;
} __attribute__((packed)) WJVN4_STRU_PathHistory; /* 车辆历史轨迹 */
#define WJVN4_MAX_LIST_POSITIONOFFSETLLV_LEN 32
#define WJVN4_MIN_LIST_POSITIONOFFSETLLV_LEN 2
typedef struct _vn4PathPointList
{
    uint8_t u8PositionOffsetLLVNum; /* 2 ~32 */
    WJVN4_STRU_PositionOffsetLLV struPositionOffsetLLV[WJVN4_MAX_LIST_POSITIONOFFSETLLV_LEN];
} __attribute__((packed)) WJVN4_STRU_PathPointList; /* 用有序位置点列的方式，定义一个有向的作用范围 */
typedef struct _vn4PathPrediction
{
    WJVN4_INT_RadiusOfCurvation n32radiusOfCurve;
    WJVN4_INT_Confidence n32confidence;
} __attribute__((packed)) WJVN4_STRU_PathPrediction; /* 车辆的预测线路 */
typedef struct _vn4ReferenceLink
{
    WJVN4_STRU_NodeReferenceID struupstreamNodeId;
    WJVN4_STRU_NodeReferenceID strudownstreamNodeId;
    uint8_t u8referenceLanesPresent;
    WJVN4_BIT_ReferenceLanes strbitreferenceLanes;  /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_ReferenceLink; /* 关联路段，用路段的上下游节点ID表示 */
#define WJVN4_MAX_LIST_REFERENCELINK_LEN 16
#define WJVN4_MIN_LIST_REFERENCELINK_LEN 1
typedef struct _vn4ReferenceLinkList
{
    uint8_t u8ReferenceLinkNum; /* 1 ~ 16 */
    WJVN4_STRU_ReferenceLink struReferenceLink[WJVN4_MAX_LIST_REFERENCELINK_LEN];
} __attribute__((packed)) WJVN4_STRU_ReferenceLinkList; /* 关联路段集合 */
typedef struct _vn4ReferencePath
{
    WJVN4_STRU_PathPointList struactivePath;
    WJVN4_INT_Radius n32pathRadius;
} __attribute__((packed)) WJVN4_STRU_ReferencePath; /* 道路交通事件和标志的关联路径 */
#define WJVN4_MAX_LIST_REFERENCEPATH_LEN 8
#define WJVN4_MIN_LIST_REFERENCEPATH_LEN 1
typedef struct _vn4ReferencePathList
{
    uint8_t u8ReferencePathNum; /* 1 ～ 8 */
    WJVN4_STRU_ReferencePath struReferencePath[WJVN4_MAX_LIST_REFERENCEPATH_LEN];
} __attribute__((packed)) WJVN4_STRU_ReferencePathList; /* 道路交通事件和标志的关联路径集合 */
typedef struct _vn4RSITimeDetails
{
    uint8_t u8startTimePresent;
    WJVN4_INT_MinuteOfTheYear n32startTime; /* OPTIONAL */
    uint8_t u8endTimePresent;
    WJVN4_INT_MinuteOfTheYear n32endTime; /* OPTIONAL */
    uint8_t u8endTimeConfidencePresent;
    WJVN4_ENUM_TimeConfidence enumendTimeConfidence; /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_RSITimeDetails; /* 道路交通事件和道路交通标志信息的生效时间属性 */
#define WJVN4_MAX_RTEID_SIZE 255
#define WJVN4_MIN_RTEID_SIZE 0
typedef struct _vn4RTEData
{
    uint8_t u8rteId; /* 0 ~ 255 */
    WJVN4_INT_EventType n32eventType;
    WJVN4_ENUM_EventSource enumeventSource;
    uint8_t u8eventPosPresent;
    WJVN4_STRU_PositionOffsetLLV strueventPos; /* OPTIONAL */
    uint8_t u8eventRadiusPresent;
    WJVN4_INT_Radius n32eventRadius; /* OPTIONAL */
    uint8_t u8descriptionPresent;
    WJVN4_STRU_Description strudescription; /* OPTIONAL */
    uint8_t u8timeDetailsPresent;
    WJVN4_STRU_RSITimeDetails strutimeDetails; /* OPTIONAL */
    uint8_t u8priorityPresent;
    WJVN4_IA5_RSIPriority stria5priority; /* OPTIONAL */
    uint8_t u8referencePathsPresent;
    WJVN4_STRU_ReferencePathList strureferencePaths; /* OPTIONAL */
    uint8_t u8referenceLinksPresent;
    WJVN4_STRU_ReferenceLinkList strureferenceLinks; /* OPTIONAL */
    uint8_t u8eventConfidencePresent;
    WJVN4_INT_Confidence n32eventConfidence;  /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_RTEData; /* 道路交通事件信息 */
#define WJVN4_MAX_LIST_RTEDATA_LEN 8
#define WJVN4_MIN_LIST_RTEDATA_LEN 1
typedef struct _vn4RTEList
{
    uint8_t u8RTEDataNum; /* 1 ~ 8 */
    WJVN4_STRU_RTEData struRTEData[WJVN4_MAX_LIST_RTEDATA_LEN];
} __attribute__((packed)) WJVN4_STRU_RTEList; /* 道路交通事件集合 */
#define WJVN4_MAX_RTSID_SIZE 255
#define WJVN4_MIN_RTSID_SIZE 0
typedef struct _vn4RTSData
{
    uint8_t u8rtsId; /* 0 ~ 255 */
    WJVN4_INT_SignType n32signType;
    uint8_t u8signPosPresent;
    WJVN4_STRU_PositionOffsetLLV strusignPos; /* OPTIONAL */
    uint8_t u8descriptionPresent;
    WJVN4_STRU_Description strudescription; /* OPTIONAL */
    uint8_t u8timeDetailsPresent;
    WJVN4_STRU_RSITimeDetails strutimeDetails; /* OPTIONAL */
    uint8_t u8priorityPresent;
    WJVN4_IA5_RSIPriority stria5priority; /* OPTIONAL */
    uint8_t u8referencePathsPresent;
    WJVN4_STRU_ReferencePathList strureferencePaths; /* OPTIONAL */
    uint8_t u8referenceLinksPresent;
    WJVN4_STRU_ReferenceLinkList strureferenceLinks; /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_RTSData;
#define WJVN4_MAX_LIST_RTSDATA_LEN 16
#define WJVN4_MIN_LIST_RTSDATA_LEN 1
typedef struct _vn4RTSList
{
    uint8_t u8RTSDataNum; /* 1 ~ 16 */
    WJVN4_STRU_RTSData struRTSData[WJVN4_MAX_LIST_RTSDATA_LEN];
} __attribute__((packed)) WJVN4_STRU_RTSList; /* 道路交通标志集合 */
typedef struct _vn4VehicleEmergencyExtensions
{
    uint8_t u8responseTypePresent;
    WJVN4_ENUM_ResponseType enumresponseType; /* OPTIONAL */
    uint8_t u8sirenUsePresent;
    WJVN4_ENUM_SirenInUse enumsirenUse; /* OPTIONAL */
    uint8_t u8lightsUsePresent;
    WJVN4_ENUM_LightbarInUse enumlightsUse;                      /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_VehicleEmergencyExtensions; /* 紧急车辆或特种车辆的辅助信息集合 */
typedef struct _vn4VehicleSafetyExtensions
{
    uint8_t u8eventsPresent;
    WJVN4_BIT_VehicleEventFlags strbitevents; /* OPTIONAL */
    uint8_t u8pathHistoryPresent;
    WJVN4_STRU_PathHistory strupathHistory; /* OPTIONAL */
    uint8_t u8pathPredictionPresent;
    WJVN4_STRU_PathPrediction strupathPrediction; /* OPTIONAL */
    uint8_t u8lightsPresent;
    WJVN4_BIT_ExteriorLights strbitlights;                    /* OPTIONAL */
} __attribute__((packed)) WJVN4_STRU_VehicleSafetyExtensions; /* 车辆安全辅助信息集合 */
/****************************************************************************************/
/* 内部函数声明 */
/****************************************************************************************/
#endif /* 文件结束 */