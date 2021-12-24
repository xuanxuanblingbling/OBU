/**
* @file         wjv2_uper_Df.h
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
#ifndef __WJV2_UPER_DF_H_
#define __WJV2_UPER_DF_H_
/*********************************头文件包含********************************************/
#include "wjv2_uper_De.h"
/*********************************标准头文件********************************************/

/*********************************自定义头文件******************************************/
typedef struct _AccelerationSet4Way
{
    WJV2_INT_Acceleration n32long;
    WJV2_INT_Acceleration n32lat;
    WJV2_INT_VerticalAcceleration n32vert;
    WJV2_INT_YawRate n32yaw;
} __attribute__((packed)) WJV2_STRU_AccelerationSet4Way; /* 车辆四轴加速度 */
typedef struct _BrakeSystemStatus
{
    uint8_t u8brakePadelPresent;
    WJV2_ENUM_BrakePedalStatus enumbrakePadel; /* OPTIONAL */
    uint8_t u8wheelBrakesPresent;
    WJV2_BIT_BrakeAppliedStatus strbitwheelBrakes; /* OPTIONAL */
    uint8_t u8tractionPresent;
    WJV2_ENUM_TractionControlStatus enumtraction; /* OPTIONAL */
    uint8_t u8absPresent;
    WJV2_ENUM_AntiLockBrakeStatus enumabs; /* OPTIONAL */
    uint8_t u8scsPresent;
    WJV2_ENUM_StabilityControlStatus enumscs; /* OPTIONAL */
    uint8_t u8brakeBoostPresent;
    WJV2_ENUM_BrakeBoostApplied enumbrakeBoost; /* OPTIONAL */
    uint8_t u8auxBrakesPresent;
    WJV2_ENUM_AuxiliaryBrakeStatus enumauxBrakes;      /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_BrakeSystemStatus; /* 车辆的刹车系统状态 */
typedef struct _ConnectingLane
{
    WJV2_INT_LaneID n32lane;
    uint8_t u8maneuverPresent;
    WJV2_BIT_AllowedManeuvers strbitmaneuver;       /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_ConnectingLane; /* 定位上游车道转向连接的下游车道 */
typedef struct _NodeReferenceID
{
    uint8_t u8regionPresent;
    WJV2_INT_RoadRegulatorID n32region; /* OPTIONAL */
    WJV2_INT_NodeID n32id;
} __attribute__((packed)) WJV2_STRU_NodeReferenceID; /* 节点ID */
typedef struct _Connection
{
    WJV2_STRU_NodeReferenceID struremoteIntersection;
    uint8_t u8connectingLanePresent;
    WJV2_STRU_ConnectingLane struconnectingLane; /* OPTIONAL */
    uint8_t u8phaseIdPresent;
    WJV2_INT_PhaseID n32phaseId;                /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_Connection; /* 当前车道与下游路段中车道的连接关系 */
#define WJV2_MAX_LIST_CONNECTION_LEN 8
#define WJV2_MIN_LIST_CONNECTION_LEN 1
typedef struct _ConnectsToList
{
    uint8_t u8ConnectionNum; /* 1 ~ 16 */
    WJV2_STRU_Connection struConnection[WJV2_MAX_LIST_CONNECTION_LEN];
} __attribute__((packed)) WJV2_STRU_ConnectsToList; /* 路段中每条车道，在下游路口处与下游路段中车道的转向连接关系列表 */
typedef struct _DDateTime
{
    uint8_t u8yearPresent;
    WJV2_INT_DYear n32year; /* OPTIONAL */
    uint8_t u8monthPresent;
    WJV2_INT_DMonth n32month; /* OPTIONAL */
    uint8_t u8dayPresent;
    WJV2_INT_DDay n32day; /* OPTIONAL */
    uint8_t u8hourPresent;
    WJV2_INT_DHour n32hour; /* OPTIONAL */
    uint8_t u8minutePresent;
    WJV2_INT_DMinute n32minute; /* OPTIONAL */
    uint8_t u8secondPresent;
    WJV2_INT_DSecond n32second; /* OPTIONAL */
    uint8_t u8offsetPresent;
    WJV2_INT_DTimeOffset n32offset;            /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_DDateTime; /* 完整的日期和时间数据单元 */
typedef enum
{

    WJV2_DescriptionNOTHING = 0,
    WJV2_DescriptiontextString = 1,
    WJV2_DescriptiontextGB2312 = 2,
} __attribute__((packed)) WJV2_ENUM_DescriptionStringChoice;
typedef struct _Description
{
    WJV2_ENUM_DescriptionStringChoice enumDescriptionStringChoice;
    int32_t n32textNum;
    union
    {
#define WJV2_MAX_IA5_STRING_LEN 512
#define WJV2_MIN_IA5_STRING_LEN 1
        uint8_t u8textString[WJV2_MAX_IA5_STRING_LEN]; /* 1 ~ 512 */
#define WJV2_MAX_OCT_STRING_LEN 256
#define WJV2_MIN_OCT_STRING_LEN 1
        uint16_t u16textGB2312[WJV2_MAX_OCT_STRING_LEN]; /* 2 ~ 512 */
    } u;
} __attribute__((packed)) WJV2_STRU_Description; /* 文本描述信息 */
typedef struct _MotionConfidenceSet
{
    uint8_t u8speedCfdPresent;
    WJV2_ENUM_SpeedConfidence enumspeedCfd; /* OPTIONAL */
    uint8_t u8headingCfdPresent;
    WJV2_ENUM_HeadingConfidence enumheadingCfd; /* OPTIONAL */
    uint8_t u8steerCfdPresent;
    WJV2_ENUM_SteeringWheelAngleConfidence enumsteerCfd; /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_MotionConfidenceSet; /* 车辆运行状态的精度 */
typedef struct _PositionConfidenceSet
{
    WJV2_ENUM_PositionConfidence enumpos;
    uint8_t u8elevationPresent;
    WJV2_ENUM_ElevationConfidence enumelevation;           /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_PositionConfidenceSet; /* 当前实时位置（经纬度和高程）的精度大小 */
typedef struct _Position3D
{
    WJV2_INT_Latitude n32lat;
    WJV2_INT_Longitude n32long;
    uint8_t u8elevationPresent;                 /*if present , will 1 byte lost*/
    WJV2_INT_Elevation n32elevation;            /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_Position3D; /* 三维的坐标位置，经纬度和高程 */
typedef struct _PositionalAccuracy
{
    WJV2_INT_SemiMajorAxisAccuracy n32semiMajor;
    WJV2_INT_SemiMinorAxisAccuracy n32semiMinor;
    WJV2_INT_SemiMajorAxisOrientation n32orientation;
} __attribute__((packed)) WJV2_STRU_PositionalAccuracy; /* 基于椭圆模型定义一个定位系统自身的精度 */

typedef struct _v2FullPositionVector
{
    uint8_t u8utcTimePresent;
    WJV2_STRU_DDateTime struutcTime; /* OPTIONAL */
    WJV2_STRU_Position3D strupos;
    uint8_t u8headingPresent;
    WJV2_INT_Heading n32heading; /* OPTIONAL */
    uint8_t u8transmissionPresent;
    WJV2_ENUM_TransmissionState enumtransmission; /* OPTIONAL */
    uint8_t u8speedPresent;
    WJV2_INT_Speed n32speed; /* OPTIONAL */
    uint8_t u8posAccuracyPresent;
    WJV2_STRU_PositionConfidenceSet struposAccuracy; /* OPTIONAL */
    uint8_t u8timeConfidencePresent;
    WJV2_ENUM_TimeConfidence enumtimeConfidence; /* OPTIONAL */
    uint8_t u8motionCfdPresent;
    WJV2_STRU_MotionConfidenceSet strumotionCfd;        /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_FullPositionVector; /* 完整的参考轨迹点信息 */
typedef struct _TimeCountingDown
{
    WJV2_INT_TimeMark n32startTime;
    uint8_t u8minEndTimePresent;
    WJV2_INT_TimeMark n32minEndTime; /* OPTIONAL */
    uint8_t u8maxEndTimePresent;
    WJV2_INT_TimeMark n32maxEndTime; /* OPTIONAL */
    WJV2_INT_TimeMark n32likelyEndTime;
    uint8_t u8timeConfidencePresent;
    WJV2_INT_Confidence n32timeConfidence; /* OPTIONAL */
    uint8_t u8nextStartTimePresent;
    WJV2_INT_TimeMark n32nextStartTime; /* OPTIONAL */
    uint8_t u8nextDurationPresent;
    WJV2_INT_TimeMark n32nextDuration;                /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_TimeCountingDown; /* 用倒计时形式，描述一个信号灯相位状态的完整计时状态 */
typedef struct _UTCTiming
{
    WJV2_INT_TimeMark n32startUTCTime;
    uint8_t u8minEndUTCTimePresent;
    WJV2_INT_TimeMark n32minEndUTCTime; /* OPTIONAL */
    uint8_t u8maxEndUTCTimePresent;
    WJV2_INT_TimeMark n32maxEndUTCTime; /* OPTIONAL */
    WJV2_INT_TimeMark n32likelyEndUTCTime;
    uint8_t u8timeConfidencePresent;
    WJV2_INT_Confidence n32timeConfidence; /* OPTIONAL */
    uint8_t u8nextStartUTCTimePresent;
    WJV2_INT_TimeMark n32nextStartUTCTime; /* OPTIONAL */
    uint8_t u8nextEndUTCTimePresent;
    WJV2_INT_TimeMark n32nextEndUTCTime;       /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_UTCTiming; /* 一个信号灯相位状态的完整计时状态 */
typedef enum
{
    WJV2_TimeChangeDetailsDOWN = 0, /* 倒计时 */
    WJV2_TimeChangeDetailsUTC = 1,  /* 正数 */
} __attribute__((packed)) WJV2_ENUM_TimeChangeDetailsChoice;
typedef struct _TimeChangeDetails
{
    WJV2_ENUM_TimeChangeDetailsChoice enumTimeChangeDetails;
    union
    {
        WJV2_STRU_TimeCountingDown strucounting;
        WJV2_STRU_UTCTiming struutcTiming;
    } u;
} __attribute__((packed)) WJV2_STRU_TimeChangeDetails; /* 信号灯相位的计时状态 */
typedef struct _PhaseState
{
    WJV2_ENUM_LightState enumlight;
    uint8_t u8timingPresent;
    WJV2_STRU_TimeChangeDetails strutiming;     /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_PhaseState; /* 信号灯的一个相位状态 */
#define WJV2_MAX_LIST_PHASESTATE_LEN 16
#define WJV2_MIN_LIST_PHASESTATE_LEN 1
typedef struct _PhaseStateList
{
    uint8_t u8PhaseStateNum; /* 1 ~ 16 */
    WJV2_STRU_PhaseState struPhaseState[WJV2_MAX_LIST_PHASESTATE_LEN];
} __attribute__((packed)) WJV2_STRU_PhaseStateList; /* 一个信号灯的一个相位中的相位状态列表 */
typedef struct _Phase
{
    WJV2_INT_PhaseID n32id;
    WJV2_STRU_PhaseStateList struphaseStates;
} __attribute__((packed)) WJV2_STRU_Phase; /* 信号灯相位 */
#define WJV2_MAX_LIST_PHASE_LEN 16
#define WJV2_MIN_LIST_PHASE_LEN 1
typedef struct _PhaseList
{
    uint8_t u8PhaseNum; /* 1 ~ 16 */
    WJV2_STRU_Phase struPhase[WJV2_MAX_LIST_PHASE_LEN];
} __attribute__((packed)) WJV2_STRU_PhaseList; /* 一组信号灯包含的所有相位的列表 */
typedef struct _IntersectionState
{
    WJV2_STRU_NodeReferenceID struintersectionId;
    WJV2_BIT_IntersectionStatusObject strbitstatus;
    uint8_t u8moyPresent;
    WJV2_INT_MinuteOfTheYear n32moy; /* OPTIONAL */
    uint8_t u8timeStampPresent;
    WJV2_INT_DSecond n32timeStamp; /* OPTIONAL */
    uint8_t u8timeConfidencePresent;
    WJV2_ENUM_TimeConfidence enumtimeConfidence; /* OPTIONAL */
    WJV2_STRU_PhaseList struphases;
} __attribute__((packed)) WJV2_STRU_IntersectionState; /* 路口信号灯的属性和当前状态 */
#define WJV2_MAX_LIST_INTERSECTIONSTATE_LEN 32         /* 与协议不一致 协议为32 暂定为16 */
#define WJV2_MIN_LIST_INTERSECTIONSTATE_LEN 1
typedef struct _IntersectionStateList
{
    uint8_t u8IntersectionStateNum; /* 1 ~ 32 */
    WJV2_STRU_IntersectionState struIntersectionState[WJV2_MAX_LIST_INTERSECTIONSTATE_LEN];
} __attribute__((packed)) WJV2_STRU_IntersectionStateList; /* 一个路口信号灯集合 */
typedef enum
{
    WJV2_LaneAttributesVehicle = 0,
    WJV2_LaneAttributesCrosswalk = 1,
    WJV2_LaneAttributesBike = 2,
    WJV2_LaneAttributesSidewalk = 3,
    WJV2_LaneAttributesBarrier = 4,
    WJV2_LaneAttributesStriping = 5,
    WJV2_LaneAttributesTrackedVehicle = 6,
    WJV2_LaneAttributesParking = 7
} __attribute__((packed)) WJV2_ENUM_LaneTypeAttributesChoice;
typedef struct _LaneTypeAttributes
{
    WJV2_ENUM_LaneTypeAttributesChoice enumLaneTypeAttributesChoice;
    union
    {
        WJV2_BIT_LaneAttributesVehicle strbitvehicle;
        WJV2_BIT_LaneAttributesCrosswalk strbitcrosswalk;
        WJV2_BIT_LaneAttributesBike strbitbikeLane;
        WJV2_BIT_LaneAttributesSidewalk strbitsidewalk;
        WJV2_BIT_LaneAttributesBarrier strbitmedian;
        WJV2_BIT_LaneAttributesStriping strbitstriping;
        WJV2_BIT_LaneAttributesTrackedVehicle strbittrackedVehicle;
        WJV2_BIT_LaneAttributesParking strbitparking;
    } u;
} __attribute__((packed)) WJV2_STRU_LaneTypeAttributes; /* 不同类别车道的属性集合 */
typedef struct _LaneAttributes
{
    uint8_t u8shareWithPresent;
    WJV2_BIT_LaneSharing strbitshareWith; /* OPTIONAL */
    WJV2_STRU_LaneTypeAttributes strulaneType;
} __attribute__((packed)) WJV2_STRU_LaneAttributes; /* 车道属性 */
typedef struct _PositionLL24B
{
    WJV2_INT_OffsetLLB12 n32lon;
    WJV2_INT_OffsetLLB12 n32lat;
} __attribute__((packed)) WJV2_STRU_PositionLL24B; /* 24比特相对经纬度位置 */
typedef struct _PositionLL28B
{
    WJV2_INT_OffsetLLB14 n32lon;
    WJV2_INT_OffsetLLB14 n32lat;
} __attribute__((packed)) WJV2_STRU_PositionLL28B; /* 28比特相对经纬度位置 */
typedef struct _PositionLL32B
{
    WJV2_INT_OffsetLLB16 n32lon;
    WJV2_INT_OffsetLLB16 n32lat;
} __attribute__((packed)) WJV2_STRU_PositionLL32B; /* 32比特相对经纬度位置 */
typedef struct _PositionLL36B
{
    WJV2_INT_OffsetLLB18 n32lon;
    WJV2_INT_OffsetLLB18 n32lat;
} __attribute__((packed)) WJV2_STRU_PositionLL36B; /* 36比特相对经纬度位置 */
typedef struct _PositionLL44B
{
    WJV2_INT_OffsetLLB22 n32lon;
    WJV2_INT_OffsetLLB22 n32lat;
} __attribute__((packed)) WJV2_STRU_PositionLL44B; /* 44比特相对经纬度位置 */
typedef struct _PositionLL48B
{
    WJV2_INT_OffsetLLB24 n32lon;
    WJV2_INT_OffsetLLB24 n32lat;
} __attribute__((packed)) WJV2_STRU_PositionLL48B; /* 48比特相对经纬度位置 */
typedef struct _PositionLLmD64b
{
    WJV2_INT_Longitude n32lon;
    WJV2_INT_Latitude n32lat;
} __attribute__((packed)) WJV2_STRU_PositionLLmD64b; /* 64比特经纬度位置 */
typedef enum
{
    WJV2_PositionLL24B = 1,
    WJV2_PositionLL28B,
    WJV2_PositionLL32B,
    WJV2_PositionLL36B,
    WJV2_PositionLL44B,
    WJV2_PositionLL48B,
    WJV2_PositionLLmD64b
} __attribute__((packed)) WJV2_ENUM_PositionOffsetLLChoice;
typedef struct _PositionOffsetLL
{
    WJV2_ENUM_PositionOffsetLLChoice enumPositionOffsetLLChoice;
    union
    {
        WJV2_STRU_PositionLL24B strupositionLL1;
        WJV2_STRU_PositionLL28B strupositionLL2;
        WJV2_STRU_PositionLL32B strupositionLL3;
        WJV2_STRU_PositionLL36B strupositionLL4;
        WJV2_STRU_PositionLL44B strupositionLL5;
        WJV2_STRU_PositionLL48B strupositionLL6;
        WJV2_STRU_PositionLLmD64b strupositionLatLon;
    } u;
} __attribute__((packed)) WJV2_STRU_PositionOffsetLL; /* 经纬度偏差 */
typedef enum
{
    WJV2_VertOffsetB07 = 1,
    WJV2_VertOffsetB08,
    WJV2_VertOffsetB09,
    WJV2_VertOffsetB10,
    WJV2_VertOffsetB11,
    WJV2_VertOffsetB12,
    WJV2_Elevation
} __attribute__((packed)) WJV2_ENUM_VerticalOffsetChoice;
typedef struct _VerticalOffset
{
    WJV2_ENUM_VerticalOffsetChoice enumVerticalOffsetChoice;
    union
    {
        WJV2_INT_VertOffsetB07 n32offset1;
        WJV2_INT_VertOffsetB08 n32offset2;
        WJV2_INT_VertOffsetB09 n32offset3;
        WJV2_INT_VertOffsetB10 n32offset4;
        WJV2_INT_VertOffsetB11 n32offset5;
        WJV2_INT_VertOffsetB12 n32offset6;
        WJV2_INT_Elevation n32elevation;
    } u;
} __attribute__((packed)) WJV2_STRU_VerticalOffset; /* 垂直方向位置偏差 */
typedef struct _PositionOffsetLLV
{
    WJV2_STRU_PositionOffsetLL struoffsetLL;
    uint8_t u8offsetVPresent;
    WJV2_STRU_VerticalOffset struoffsetV;              /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_PositionOffsetLLV; /* 三维的相对位置（相对经纬度和相对高程） */
typedef struct _RoadPoint
{
    WJV2_STRU_PositionOffsetLLV struposOffset;
} __attribute__((packed)) WJV2_STRU_RoadPoint; /* 完整道路上标记的一个位置点属性 */
#define WJV2_MAX_LIST_ROADPOINT_LEN 31         /* 与协议不一致 协议为31 暂定为6 */
#define WJV2_MIN_LIST_ROADPOINT_LEN 2
typedef struct _PointList
{
    uint8_t u8RoadPointNum; /* 2 ~ 31 */
    WJV2_STRU_RoadPoint struRoadPoint[WJV2_MAX_LIST_ROADPOINT_LEN];
} __attribute__((packed)) WJV2_STRU_PointList; /* 一个有向路段上的中间位置点列表 */
typedef struct _RegulatorySpeedLimit
{
    WJV2_ENUM_SpeedLimitType enumtype;
    WJV2_INT_Speed n32speed;
} __attribute__((packed)) WJV2_STRU_RegulatorySpeedLimit; /* 限速属性 */
#define WJV2_MAX_LIST_REGULATORYSPEEDLIMITNUM_LEN 9       /* 与协议不一致 协议为9 暂定为4 */
#define WJV2_MIN_LIST_REGULATORYSPEEDLIMITNUM_LEN 1
typedef struct _SpeedLimitList
{
    uint8_t u8RegulatorySpeedLimitNum; /* 1 ~ 9 */
    WJV2_STRU_RegulatorySpeedLimit struRegulatorySpeedLimit[WJV2_MAX_LIST_REGULATORYSPEEDLIMITNUM_LEN];
} __attribute__((packed)) WJV2_STRU_SpeedLimitList; /* 路段或车道的限速列表 */
typedef struct _Lane
{
    WJV2_INT_LaneID n32laneID;
    uint8_t u8laneWidthPresent;
    WJV2_INT_LaneWidth n32laneWidth; /* OPTIONAL */
    uint8_t u8laneAttributesPresent;
    WJV2_STRU_LaneAttributes strulaneAttributes; /* OPTIONAL */
    uint8_t u8maneuversPresent;
    WJV2_BIT_AllowedManeuvers strbitmaneuvers; /* OPTIONAL */
    uint8_t u8connectsToPresent;
    WJV2_STRU_ConnectsToList struConnectsToList; /* OPTIONAL */
    uint8_t u8speedLimitsPresent;
    WJV2_STRU_SpeedLimitList struspeedLimits; /* OPTIONAL */
    uint8_t u8pointsPresent;
    WJV2_STRU_PointList strupoints;       /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_Lane; /* 车道 */
#define WJV2_MAX_LIST_LANE_LEN 16         /* 与协议不一致 协议为32 暂定为8 */
#define WJV2_MIN_LIST_LANE_LEN 1
typedef struct _LaneList
{
    uint8_t u8LaneNum; /* 1 ~ 32 */
    WJV2_STRU_Lane struLane[WJV2_MAX_LIST_LANE_LEN];
} __attribute__((packed)) WJV2_STRU_LaneList; /* 一个路段中包含的车道列表 */
typedef struct _Movement
{
    WJV2_STRU_NodeReferenceID struremoteIntersection;
    uint8_t u8phaseIdPresent;
    WJV2_INT_PhaseID n32phaseId;              /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_Movement; /* 道路与下游路段的连接关系 */
#define WJV2_MAX_LIST_MOVEMENT_LEN 8          /* 与协议不一致 协议为32 暂定为4 */
#define WJV2_MIN_LIST_MOVEMENT_LEN 1
typedef struct _MovementList
{
    uint8_t u8MovementNum; /* 1 ~ 32 */
    WJV2_STRU_Movement struMovement[WJV2_MAX_LIST_MOVEMENT_LEN];
} __attribute__((packed)) WJV2_STRU_MovementList; /* 一条路段与下游路段的连接关系列表 */
typedef struct _Link
{
    uint8_t u8namePresent;
    WJV2_IA5_DescriptiveName stria5name; /* OPTIONAL */
    WJV2_STRU_NodeReferenceID struupstreamNodeId;
    uint8_t u8speedLimitsPresent;
    WJV2_STRU_SpeedLimitList struspeedLimits; /* OPTIONAL */
    uint8_t u8linkWidthPresent;
    WJV2_INT_LaneWidth n32linkWidth; /* OPTIONAL */
    uint8_t u8pointsPresent;
    WJV2_STRU_PointList strupoints; /* OPTIONAL */
    uint8_t u8MovementListPresent;
    WJV2_STRU_MovementList strumovements; /* OPTIONAL */
    WJV2_STRU_LaneList strulanes;
} __attribute__((packed)) WJV2_STRU_Link; /* 路段 */
#define WJV2_MAX_LIST_LINK_LEN 8          /* 与协议不一致 协议为32 暂定为4 */
#define WJV2_MIN_LIST_LINK_LEN 1
typedef struct _LinkList
{
    uint8_t u8LinkNum; /* 1 ~ 32 */
    WJV2_STRU_Link struLink[WJV2_MAX_LIST_LINK_LEN];
} __attribute__((packed)) WJV2_STRU_LinkList; /* 路段列表 */

typedef struct _VehicleClassification
{
    WJV2_INT_BasicVehicleClass n32classification;
    uint8_t u8fuelTypePresent;
    WJV2_INT_FuelType n32fuelType;                         /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_VehicleClassification; /* 车辆的分类 */
typedef struct _VehicleSize
{
    WJV2_INT_VehicleWidth n32width;
    WJV2_INT_VehicleLength n32length;
    uint8_t u8heightPresent;
    WJV2_INT_VehicleHeight n32height;            /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_VehicleSize; /* 车辆尺寸大小 */
#define WJV2_MAX_PTCID_SIZE 65535
#define WJV2_MIN_PTCID_SIZE 0
typedef struct _ParticipantData
{
    WJV2_ENUM_ParticipantType enumptcType;
    int32_t n32ptcId; /* 0 ~ 65535 0 is RSU itself */
    WJV2_ENUM_SourceType enumsource;
    uint8_t u8OCTidPresent;
#define WJV2_MAX_OCTID_SIZE 8
#define WJV2_MIN_OCTID_SIZE 0
    uint8_t u8OCTid[WJV2_MAX_OCTID_SIZE]; /* OPTIONAL */
    WJV2_INT_DSecond n32secMark;
    WJV2_STRU_PositionOffsetLLV strupos;
    WJV2_STRU_PositionConfidenceSet struposConfidence;
    uint8_t u8transmissionPresent;
    WJV2_ENUM_TransmissionState enumtransmission; /* OPTIONAL */
    WJV2_INT_Speed n32speed;
    WJV2_INT_Heading n32heading;
    uint8_t u8anglePresent;
    WJV2_INT_SteeringWheelAngle n32angle; /* OPTIONAL */
    uint8_t u8motionCfdPresent;
    WJV2_STRU_MotionConfidenceSet strumotionCfd; /* OPTIONAL */
    uint8_t u8accelSetPresent;
    WJV2_STRU_AccelerationSet4Way struaccelSet; /* OPTIONAL */
    WJV2_STRU_VehicleSize strusize;
    uint8_t u8vehicleClassPresent;
    WJV2_STRU_VehicleClassification struvehicleClass; /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_ParticipantData;  /* 交通参与者的基本安全信息 */
#define WJV2_MAX_LIST_PARTICIPANTDATA_LEN 16
#define WJV2_MIN_LIST_PARTICIPANTDATA_LEN 1
typedef struct _NodeListParticipantList
{
    uint8_t u8ParticipantDataNum; /* 1 ~ 16 */
    WJV2_STRU_ParticipantData struParticipantData[WJV2_MAX_LIST_PARTICIPANTDATA_LEN];
} __attribute__((packed)) WJV2_STRU_ParticipantList; /* 地图节点列表 */
typedef struct _PathHistoryPoint
{
    WJV2_STRU_PositionOffsetLLV strullvOffset;
    WJV2_INT_TimeOffset n32timeOffset;
    uint8_t u8speedPresent;
    WJV2_INT_Speed n32speed;
    uint8_t u8posAccuracyPresent;
    WJV2_STRU_PositionConfidenceSet struposAccuracy; /* OPTIONAL */
    uint8_t u8headingPresent;
    WJV2_INT_CoarseHeading n32heading;                /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_PathHistoryPoint; /* 车辆的历史轨迹点 */
#define WJV2_MAX_LIST_PATHHISTORYPOINT_LEN 23         /* 与协议不一致 协议为23 暂定为8 */
#define WJV2_MIN_LIST_PATHHISTORYPOINT_LEN 1
typedef struct _PathHistoryPointList
{
    uint8_t u8PathHistoryPointNum; /* 1 ~ 23 */
    WJV2_STRU_PathHistoryPoint struPathHistoryPoint[WJV2_MAX_LIST_PATHHISTORYPOINT_LEN];
} __attribute__((packed)) WJV2_STRU_PathHistoryPointList; /* 车辆的历史轨迹 */
typedef struct _PathHistory
{
    uint8_t u8initialPositionPresent;
    WJV2_STRU_FullPositionVector struinitialPosition; /* OPTIONAL */
    uint8_t u8currGNSSstatusPresent;
    WJV2_BIT_GNSSstatus strbitcurrGNSSstatus; /* OPTIONAL */
    WJV2_STRU_PathHistoryPointList strucrumbData;
} __attribute__((packed)) WJV2_STRU_PathHistory; /* 车辆历史轨迹 */
#define WJV2_MAX_LIST_POSITIONOFFSETLLV_LEN 32   /* 与协议不一致 协议为32 暂定为8 */
#define WJV2_MIN_LIST_POSITIONOFFSETLLV_LEN 2
typedef struct _PathPointList
{
    uint8_t u8PositionOffsetLLVNum; /* 2 ~32 */
    WJV2_STRU_PositionOffsetLLV struPositionOffsetLLV[WJV2_MAX_LIST_POSITIONOFFSETLLV_LEN];
} __attribute__((packed)) WJV2_STRU_PathPointList; /* 用有序位置点列的方式，定义一个有向的作用范围 */
typedef struct _PathPrediction
{
    WJV2_INT_RadiusOfCurvation n32radiusOfCurve;
    WJV2_INT_Confidence n32confidence;
} __attribute__((packed)) WJV2_STRU_PathPrediction; /* 车辆的预测线路 */
typedef struct _ReferenceLink
{
    WJV2_STRU_NodeReferenceID struupstreamNodeId;
    WJV2_STRU_NodeReferenceID strudownstreamNodeId;
    uint8_t u8referenceLanesPresent;
    WJV2_BIT_ReferenceLanes strbitreferenceLanes;  /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_ReferenceLink; /* 关联路段，用路段的上下游节点ID表示 */
#define WJV2_MAX_LIST_REFERENCELINK_LEN 16         /* 与协议不一致 协议为16 暂定为8 */
#define WJV2_MIN_LIST_REFERENCELINK_LEN 1
typedef struct _ReferenceLinkList
{
    uint8_t u8ReferenceLinkNum; /* 1 ~ 16 */
    WJV2_STRU_ReferenceLink struReferenceLink[WJV2_MAX_LIST_REFERENCELINK_LEN];
} __attribute__((packed)) WJV2_STRU_ReferenceLinkList; /* 关联路段集合 */
typedef struct _ReferencePath
{
    WJV2_STRU_PathPointList struactivePath;
    WJV2_INT_Radius n32pathRadius;
} __attribute__((packed)) WJV2_STRU_ReferencePath; /* 道路交通事件和标志的关联路径 */
#define WJV2_MAX_LIST_REFERENCEPATH_LEN 8
#define WJV2_MIN_LIST_REFERENCEPATH_LEN 1
typedef struct _ReferencePathList
{
    uint8_t u8ReferencePathNum; /* 1 ～ 8 */
    WJV2_STRU_ReferencePath struReferencePath[WJV2_MAX_LIST_REFERENCEPATH_LEN];
} __attribute__((packed)) WJV2_STRU_ReferencePathList; /* 道路交通事件和标志的关联路径集合 */
typedef struct _RSITimeDetails
{
    uint8_t u8startTimePresent;
    WJV2_INT_MinuteOfTheYear n32startTime; /* OPTIONAL */
    uint8_t u8endTimePresent;
    WJV2_INT_MinuteOfTheYear n32endTime; /* OPTIONAL */
    uint8_t u8endTimeConfidencePresent;
    WJV2_ENUM_TimeConfidence enumendTimeConfidence; /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_RSITimeDetails; /* 道路交通事件和道路交通标志信息的生效时间属性 */
#define WJV2_MAX_RTEID_SIZE 255
#define WJV2_MIN_RTEID_SIZE 0
typedef struct _RTEData
{
    uint8_t u8rteId; /* 0 ~ 255 */
    WJV2_INT_EventType n32eventType;
    WJV2_ENUM_EventSource enumeventSource;
    uint8_t u8eventPosPresent;
    WJV2_STRU_PositionOffsetLLV strueventPos; /* OPTIONAL */
    uint8_t u8eventRadiusPresent;
    WJV2_INT_Radius n32eventRadius; /* OPTIONAL */
    uint8_t u8descriptionPresent;
    WJV2_STRU_Description strudescription; /* OPTIONAL */
    uint8_t u8timeDetailsPresent;
    WJV2_STRU_RSITimeDetails strutimeDetails; /* OPTIONAL */
    uint8_t u8priorityPresent;
    WJV2_IA5_RSIPriority stria5priority; /* OPTIONAL */
    uint8_t u8referencePathsPresent;
    WJV2_STRU_ReferencePathList strureferencePaths; /* OPTIONAL */
    uint8_t u8referenceLinksPresent;
    WJV2_STRU_ReferenceLinkList strureferenceLinks; /* OPTIONAL */
    uint8_t u8eventConfidencePresent;
    WJV2_INT_Confidence n32eventConfidence;  /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_RTEData; /* 道路交通事件信息 */
#define WJV2_MAX_LIST_RTEDATA_LEN 8
#define WJV2_MIN_LIST_RTEDATA_LEN 1
typedef struct _RTEList
{
    uint8_t u8RTEDataNum; /* 1 ~ 8 */
    WJV2_STRU_RTEData struRTEData[WJV2_MAX_LIST_RTEDATA_LEN];
} __attribute__((packed)) WJV2_STRU_RTEList; /* 道路交通事件集合 */
#define WJV2_MAX_RTSID_SIZE 255
#define WJV2_MIN_RTSID_SIZE 0
typedef struct _RTSData
{
    uint8_t u8rtsId; /* 0 ~ 255 */
    WJV2_INT_SignType n32signType;
    uint8_t u8signPosPresent;
    WJV2_STRU_PositionOffsetLLV strusignPos; /* OPTIONAL */
    uint8_t u8descriptionPresent;
    WJV2_STRU_Description strudescription; /* OPTIONAL */
    uint8_t u8timeDetailsPresent;
    WJV2_STRU_RSITimeDetails strutimeDetails; /* OPTIONAL */
    uint8_t u8priorityPresent;
    WJV2_IA5_RSIPriority stria5priority; /* OPTIONAL */
    uint8_t u8referencePathsPresent;
    WJV2_STRU_ReferencePathList strureferencePaths; /* OPTIONAL */
    uint8_t u8referenceLinksPresent;
    WJV2_STRU_ReferenceLinkList strureferenceLinks; /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_RTSData;
#define WJV2_MAX_LIST_RTSDATA_LEN 16
#define WJV2_MIN_LIST_RTSDATA_LEN 1
typedef struct _RTSList
{
    uint8_t u8RTSDataNum; /* 1 ~ 16 */
    WJV2_STRU_RTSData struRTSData[WJV2_MAX_LIST_RTSDATA_LEN];
} __attribute__((packed)) WJV2_STRU_RTSList; /* 道路交通标志集合 */
typedef struct _VehicleEmergencyExtensions
{
    uint8_t u8responseTypePresent;
    WJV2_ENUM_ResponseType enumresponseType; /* OPTIONAL */
    uint8_t u8sirenUsePresent;
    WJV2_ENUM_SirenInUse enumsirenUse; /* OPTIONAL */
    uint8_t u8lightsUsePresent;
    WJV2_ENUM_LightbarInUse enumlightsUse;                      /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_VehicleEmergencyExtensions; /* 紧急车辆或特种车辆的辅助信息集合 */
typedef struct _VehicleSafetyExtensions
{
    uint8_t u8eventsPresent;
    WJV2_BIT_VehicleEventFlags strbitevents; /* OPTIONAL */
    uint8_t u8pathHistoryPresent;
    WJV2_STRU_PathHistory strupathHistory; /* OPTIONAL */
    uint8_t u8pathPredictionPresent;
    WJV2_STRU_PathPrediction strupathPrediction; /* OPTIONAL */
    uint8_t u8lightsPresent;
    WJV2_BIT_ExteriorLights strbitlights;                    /* OPTIONAL */
} __attribute__((packed)) WJV2_STRU_VehicleSafetyExtensions; /* 车辆安全辅助信息集合 */
/****************************************************************************************/
/* 内部函数声明 */
/****************************************************************************************/

/* Dependencies */
typedef struct _AccountInfoData
{
    uint8_t u8OCTAccountInfoNum;
#define WJV2_MAX_OCTAccountInfo_SIZE 32
#define WJV2_MIN_OCTAccountInfo_SIZE 2
    uint8_t u8OCTAccountInfo[WJV2_MAX_OCTAccountInfo_SIZE];
} __attribute__((packed)) WJV2_OCT_AccountInfoData;

/* AccSet4WayConfidence */
typedef struct _AccSet4WayConfidence
{
    WJV2_ENUM_AccConfidence enumlonAccConfidence;
    WJV2_ENUM_AccConfidence enumlatAccConfidence;
    WJV2_ENUM_AccConfidence enumvertAccConfidence;
    WJV2_ENUM_AngularVConfidence enumyawRateCon;

} __attribute__((packed)) WJV2_STRU_AccSet4WayConfidence;

/* RangeOfFile */
typedef struct _RangeOfFile
{
    WJV2_INT_OFFSET n32offset;
    WJV2_INT_LENGTH n32lengh;
} __attribute__((packed)) WJV2_STRU_RangeOfFile;

/* GetTollDataRq */
typedef struct _GetTollDataRq
{
    WJV2_STRU_RangeOfFile struvehicleInfo;
    uint8_t u8tollInfoPresent;
    WJV2_STRU_RangeOfFile strutollInfo /* OPTIONAL */;
    uint8_t u8keyIdForACPresent;
    WJV2_INT_keyIdForAC n32keyIdForAC /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_GetTollDataRq;

/* GetTollDataRs */
typedef struct _GetTollDataRs
{
    WJV2_OCT_FileData octvehicleInfo;
    uint8_t u8tollInfoPresent;
    WJV2_OCT_FileData octtollInfo /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_GetTollDataRs;

/* GetSecureRq */
typedef struct _GetSecureRq
{
    WJV2_STRU_RangeOfFile struvehicleInfo;
    WJV2_OCT_RandStr8Data octrndRsuForAuthen;
    WJV2_INT_keyIdForAuthen n32keyIdForAuthen;
    uint8_t u8keyIdForEncryptPresent;
    WJV2_INT_keyIdForEncrypt n32keyIdForEncrypt /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_GetSecureRq;

/* GetSecureRs */
typedef struct _GetSecureRs
{
    WJV2_STRU_RangeOfFile strufile;
    uint8_t u8OCTauthenticatorNum;
#define WJV2_MAX_OCTauthenticator_SIZE 8
    uint8_t u8OCTauthenticator[WJV2_MAX_OCTauthenticator_SIZE];

} __attribute__((packed)) WJV2_STRU_GetSecureRs;

/* TacPara */
typedef struct _TacPara
{
    uint8_t u8OCTtransAmountNum;
#define WJV2_MAX_OCTtransAmount_SIZE 4
    uint8_t u8OCTtransAmount[WJV2_MAX_OCTtransAmount_SIZE];

    uint8_t u8OCTtransTypeNum;
#define WJV2_MAX_OCTtransType_SIZE 1
    uint8_t u8OCTtransType[WJV2_MAX_OCTtransType_SIZE];

    uint8_t u8OCTterminalIDNum;
#define WJV2_MAX_OCTterminalID_SIZE 6
    uint8_t u8OCTterminalID[WJV2_MAX_OCTterminalID_SIZE];

    uint8_t u8OCTtransSNNum;
#define WJV2_MAX_OCTtransSN_SIZE 4
    uint8_t u8OCTtransSN[WJV2_MAX_OCTtransSN_SIZE];

    uint8_t u8OCTtransTimeNum;
#define WJV2_MAX_OCTtransTime_SIZE 7
    uint8_t u8OCTtransTime[WJV2_MAX_OCTtransTime_SIZE];

    uint8_t u8OCTtransStationIDNum;
#define WJV2_MAX_OCTtransStationID_SIZE 3
    uint8_t u8OCTtransStationID[WJV2_MAX_OCTtransStationID_SIZE];

} __attribute__((packed)) WJV2_STRU_TacPara;

/* PartOfFile */
typedef struct _PartOfFile
{
    WJV2_INT_OFFSET n32offset;
    WJV2_INT_LENGTH n32lenght;
    WJV2_OCT_FileData octfileContent;

} __attribute__((packed)) WJV2_STRU_PartOfFile;

/* TollingPos */
typedef struct _TollingPos
{
    WJV2_INT_StationOrGantryId id;
    uint8_t u8posPresent;
    WJV2_STRU_Position3D sturpos /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_TollingPos;

/* SetTollDataRq */
typedef struct _SetTollDataRq
{
    WJV2_OCT_RandStr8Data octrndRSU;
    uint8_t u8transParaPresent;
    WJV2_STRU_TacPara strutransPara /* OPTIONAL */;
    uint8_t u8tollInfoPresent;
    WJV2_STRU_PartOfFile strutollInfo /* OPTIONAL */;
    uint8_t u8tollingPosPresent;
    WJV2_STRU_TollingPos tollingPos /* OPTIONAL */;
    uint8_t u8keyIdForAuthenPresent;
    WJV2_INT_keyIdForAuthen n32keyIdForAuthen /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_SetTollDataRq;

/* Dependencies */
typedef struct _TransCredential
{
    uint8_t u8OCTTransCredentialNum;
#define WJV2_MAX_OCTTransCredential_SIZE 32
#define WJV2_MIN_OCTTransCredential_SIZE 1
    uint8_t u8OCTTransCredential[WJV2_MAX_OCTTransCredential_SIZE];
} __attribute__((packed)) WJV2_OCT_TransCredential;

/* SetTollDataRs */
typedef struct _SetTollDataRs
{
    uint8_t u8OCTtacInfoNum;
#define WJV2_MAX_OCTtacInfo_SIZE 4
    uint8_t u8OCTtacInfo[WJV2_MAX_OCTtacInfo_SIZE];

    uint8_t u8OCTauthenticatorNum;
#define WJV2_MAX_OCTauthenticator_SIZE 8
    uint8_t u8OCTauthenticator[WJV2_MAX_OCTauthenticator_SIZE];

    uint8_t u8accountInfoPresent;
    WJV2_OCT_AccountInfoData octaccountInfo /* OPTIONAL */;
    uint8_t u8transCredentialPresent;
    WJV2_OCT_TransCredential transCredential /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_SetTollDataRs;

/* ChannelRq */
typedef struct _ChannelRq
{
    WJV2_ENUM_ChannelID enumchannelid;
    WJV2_STRU_ApduList struapdu;

} __attribute__((packed)) WJV2_STRU_ChannelRq;

/* ChannelRs */
typedef struct _ChannelRs
{
    WJV2_ENUM_ChannelID enumchannelid;
    WJV2_STRU_ApduList struapdu;

} __attribute__((packed)) WJV2_STRU_ChannelRs;

/* SetMMIRq */
typedef struct _SetMMIRq
{
    WJV2_ENUM_TollResult enumtoll;

} __attribute__((packed)) WJV2_STRU_SetMMIRq;

/* Dependencies */
typedef enum _TransInfo_PR
{
    WJV2_TransInfo_PR_NOTHING, /* No components present */
    WJV2_TransInfo_PR_getTollDataRq,
    WJV2_TransInfo_PR_getTollDataRs,
    WJV2_TransInfo_PR_getSecureRq,
    WJV2_TransInfo_PR_getSecureRs,
    WJV2_TransInfo_PR_setTollDataRq,
    WJV2_TransInfo_PR_setTollDataRs,
    WJV2_TransInfo_PR_transferChannelRq,
    WJV2_TransInfo_PR_transferChannelRs,
    WJV2_TransInfo_PR_setMMIRq
    /* Extensions may appear below */

} __attribute__((packed)) WJV2_ENUM_TransInfo_PR;

/* TransInfo */
typedef struct _TransInfo
{
    WJV2_ENUM_TransInfo_PR present;
    union WJV2_TransInfo_u
    {
        WJV2_STRU_GetTollDataRq strugetTollDataRq;
        WJV2_STRU_GetTollDataRs strugetTollDataRs;
        WJV2_STRU_GetSecureRq strugetSecureRq;
        WJV2_STRU_GetSecureRs strugetSecureRs;
        WJV2_STRU_SetTollDataRq strusetTollDataRq;
        WJV2_STRU_SetTollDataRs strusetTollDataRs;
        WJV2_STRU_ChannelRq strutransferChannelRq;
        WJV2_STRU_ChannelRs strutransferChannelRs;
        WJV2_STRU_SetMMIRq strusetMMIRq;
        /*
		 * This type is extensible,
		 * possible extensions are below.
		 */
    } choice;

} __attribute__((packed)) WJV2_STRU_TransInfo;

/* Action-Request */
typedef struct _Action_Request
{
    WJV2_STRU_DDateTime strutime;
    WJV2_INT_BOOLEAN n32mode;
    uint8_t u8OCTsourceIdNum;
#define WJV2_MAX_OCTsourceId_SIZE 8
    uint8_t u8OCTsourceId[WJV2_MAX_OCTsourceId_SIZE];
    uint8_t u8OCTtargetIdNum;
#define WJV2_MAX_OCTtargetId_SIZE 8
    uint8_t u8targetIdPresent;
    uint8_t u8OCTtargetId[WJV2_MAX_OCTtargetId_SIZE]; /* OPTIONAL */
    WJV2_ENUM_PaymentEntityID enumpaymentEntityId;
    WJV2_STRU_TransInfo struactionParameter;
    uint8_t u8OCTaccessCredentialsNum;
#define WJV2_MAX_OCTaccessCredentials_SIZE 8
    uint8_t u8accessCredentialsPresent;
    uint8_t u8OCTaccessCredentials[WJV2_MAX_OCTaccessCredentials_SIZE]; /* OPTIONAL */

} __attribute__((packed)) WJV2_STRU_Action_Request;

/* Action-Response */
typedef struct _Action_Response
{
    WJV2_STRU_DDateTime strutime;
    uint8_t u8OCTsourceIdNum;
#define WJV2_MAX_OCTsourceId_SIZE 8
    uint8_t u8OCTsourceId[WJV2_MAX_OCTsourceId_SIZE];

    uint8_t u8OCTtargetIdNum;
#define WJV2_MAX_OCTtargetId_SIZE 8
    uint8_t u8targetIdPresent;
    uint8_t u8OCTtargetId[WJV2_MAX_OCTtargetId_SIZE]; /* OPTIONAL */

    WJV2_ENUM_PaymentEntityID enumpaymentEntityId;
    uint8_t u8responseParameterPresent;
    WJV2_STRU_TransInfo struresponseParameter /* OPTIONAL */;

    WJV2_ENUM_ReturnStatus enumret;

} __attribute__((packed)) WJV2_STRU_Action_Response;

/* AngularVelocity */
typedef struct _AngularVelocity
{
    WJV2_INT_PitchRate n32pitchRate;
    WJV2_INT_RollRate n32rollRate;
    WJV2_INT_YawRate n32yawRate;

} __attribute__((packed)) WJV2_STRU_AngularVelocity;

/* AngularVelocityConfidence */
typedef struct _AngularVelocityConfidence
{
    WJV2_ENUM_AngularVConfidence enumpitchRate;
    WJV2_ENUM_AngularVConfidence enumrollRate;
    WJV2_ENUM_AngularVConfidence enumyawRate;

} __attribute__((packed)) WJV2_STRU_AngularVelocityConfidence;

/* TollingNodeInfo */
typedef struct _TollingNodeInfo
{
    uint8_t u8idPresent;
    WJV2_INT_StationOrGantryId id /* OPTIONAL */;
    uint8_t u8posPresent;
    WJV2_STRU_Position3D strupos /* OPTIONAL */;
    uint8_t u8tollingNodeTypePresent;
    WJV2_ENUM_TollingNodeType enumtollingNodeType /* OPTIONAL */;
    uint8_t u8tollingDirectionPresent;
    WJV2_ENUM_TollingDirection enumtollingDirection /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_TollingNodeInfo;

#define WJV2_MAX_LIST_tollRoad_LEN 256
#define WJV2_MIN_LIST_tollRoad_LEN 2
/* TollingNodeInfo */
typedef struct _tollRoad
{
    uint16_t u16NodeReferenceIDNum; /* 2 ~ 256 */
    WJV2_STRU_NodeReferenceID struNodeReferenceID[WJV2_MAX_LIST_tollRoad_LEN];

} __attribute__((packed)) WJV2_STRU_tollRoadList;

/* TollInfo */
typedef struct _TollInfo
{
    uint8_t u8pricePresent;
    WJV2_INT_price n32price /* OPTIONAL */;
    uint8_t u8entrancePosPresent;
    WJV2_STRU_PositionOffsetLLV struentrancePos /* OPTIONAL */;
    uint8_t u8exitPosPresent;
    WJV2_STRU_PositionOffsetLLV struexitPos /* OPTIONAL */;
    uint8_t u8tollRoadPresent;
    WJV2_STRU_tollRoadList strutollRoad; /* OPTIONAL */
    uint8_t u8tollPathPresent;
    WJV2_STRU_ReferencePath strutollPath /* OPTIONAL */;
    uint8_t u8timeBeginPresent;
    WJV2_STRU_DDateTime strutimeBegin /* OPTIONAL */;
    uint8_t u8timeEndPresent;
    WJV2_STRU_DDateTime strutimeEnd /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_TollInfo;

/* PaymentInfoType1 */
typedef struct _PaymentInfoType1
{
    uint8_t u8tollingNodeInfoPresent;
    WJV2_STRU_TollingNodeInfo strutollingNodeInfo /* OPTIONAL */;
    uint8_t u8tollInfoPresent;
    WJV2_STRU_TollInfo strutollInfo /* OPTIONAL */;
    uint8_t u8serviceInfoPresent;
    uint16_t u16OCTserviceInfoNum;
#define WJV2_MAX_OCTserviceInfo_SIZE 512
#define WJV2_MIN_OCTserviceInfo_SIZE 1
    uint8_t u8OCTserviceInfo[WJV2_MAX_OCTserviceInfo_SIZE]; /* OPTIONAL */

} __attribute__((packed)) WJV2_STRU_PaymentInfoType1;

/* Dependencies */
typedef enum _PaymentInfo_PR
{
    WJV2_PaymentInfo_PR_NOTHING, /* No components present */
    WJV2_PaymentInfo_PR_paymentInfoType1
    /* Extensions may appear below */

} __attribute__((packed)) WJV2_ENUM_PaymentInfo_PR;

/* PaymentInfo */
typedef struct _PaymentInfo
{
    WJV2_ENUM_PaymentInfo_PR present;
    union WJV2_PaymentInfo_u
    {
        WJV2_STRU_PaymentInfoType1 strupaymentInfoType1;
        /*
		 * This type is extensible,
		 * possible extensions are below.
		 */
    } choice;

} __attribute__((packed)) WJV2_STRU_PaymentInfo;

/* ApplicationParameter */
typedef struct _ApplicationParameter
{
    WJV2_ENUM_PaymentEntityID enumpid;
    WJV2_STRU_PaymentInfo strupaymentInfo;

} __attribute__((packed)) WJV2_STRU_ApplicationParameter;

/* Attitude */
typedef struct _Attitude
{
    WJV2_INT_Pitch n32pitch;
    WJV2_INT_Roll n32roll;
    WJV2_INT_Yaw n32yaw;

} __attribute__((packed)) WJV2_STRU_Attitude;

/* AttitudeConfidence */
typedef struct _AttitudeConfidence
{
    WJV2_ENUM_HeadingConfidence enumpitchConfidence;
    WJV2_ENUM_HeadingConfidence enumrollRateConfidence;
    WJV2_ENUM_HeadingConfidence enumyawRate;

} __attribute__((packed)) WJV2_STRU_AttitudeConfidence;

/* ConnectingLaneEx */
typedef struct _ConnectingLaneEx
{
    WJV2_INT_SectionId n32target_section;
    WJV2_INT_LaneRefID n32target_lane;
    uint8_t u8connectingLaneWidthPresent;
    WJV2_INT_LaneWidth n32connectingLaneWidth /* OPTIONAL */;
    uint8_t u8connectingLanePointsPresent;
    WJV2_STRU_PointList struconnectingLanePoints /* OPTIONAL */;
    uint8_t u8isolatedConnectingLanePresent;
    WJV2_INT_BOOLEAN n32isolatedConnectingLane /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_ConnectingLaneEx;

#define WJV2_MAX_LIST_phaseId_LEN 7
#define WJV2_MIN_LIST_phaseId_LEN 1
typedef struct _allowedPhaseIdsList
{
    uint8_t u8phaseIdNum;
    WJV2_INT_PhaseID n32phaseId[WJV2_MAX_LIST_phaseId_LEN];
} __attribute__((packed)) WJV2_STRU_allowedPhaseIdsList;

/* SignalWaitingLane */
typedef struct _SignalWaitingLane
{
    WJV2_INT_LaneWidth n32laneWidth;
    WJV2_STRU_PointList strupoints;
    uint8_t u8allowedPhaseIdsPresent;
    WJV2_STRU_allowedPhaseIdsList struallowedPhaseIds; /* OPTIONAL */

} __attribute__((packed)) WJV2_STRU_SignalWaitingLane;

#define WJV2_MAX_LIST_ConnectingLaneEx_LEN 8 /* 与协议不一致 协议为16 暂定为8 */
#define WJV2_MIN_LIST_ConnectingLaneEx_LEN 1
typedef struct _connectingLaneList
{
    uint8_t u8ConnectingLaneExNum;
    WJV2_STRU_ConnectingLaneEx n32ConnectingLaneEx[WJV2_MAX_LIST_ConnectingLaneEx_LEN];
} __attribute__((packed)) WJV2_STRU_connectingLaneList;

/* ConnectionEx */
typedef struct _ConnectionEx
{

    WJV2_STRU_NodeReferenceID struremoteIntersection;
    uint8_t u8swlPresent;
    WJV2_STRU_SignalWaitingLane struswl /* OPTIONAL */;
    uint8_t u8connectingLanePresent;
    WJV2_STRU_connectingLaneList struconnectingLane; /* OPTIONAL */
    uint8_t u8phaseIdPresent;
    WJV2_INT_PhaseID n32phaseId /* OPTIONAL */;
    uint8_t u8turn_directionPresent;
    WJV2_ENUM_Maneuver enumturn_direction /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_ConnectionEx;

#define WJV2_MAX_LIST_ConnectsToEx_LEN 4 /* 与协议不一致 协议为32 暂定为4 */
#define WJV2_MIN_LIST_ConnectsToEx_LEN 1
typedef struct _ConnectsToExList
{
    uint8_t u8ConnectsToExNum;
    WJV2_STRU_ConnectionEx struConnectsToEx[WJV2_MAX_LIST_ConnectsToEx_LEN];
} __attribute__((packed)) WJV2_STRU_ConnectsToExList;

/* ObjectSize */
typedef struct _ObjectSize
{
    WJV2_INT_SizeValue n32width;
    WJV2_INT_SizeValue n32length;
    uint8_t u8heightPresent;
    WJV2_INT_SizeValue n32height /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_ObjectSize;

/* ObjectSizeConfidence */
typedef struct _ObjectSizeConfidence
{
    WJV2_ENUM_SizeValueConfidence enumwidthConf;
    WJV2_ENUM_SizeValueConfidence enumlengthConf;
    uint8_t u8heightConfPresent;
    WJV2_ENUM_SizeValueConfidence enumheightConf /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_ObjectSizeConfidence;

#define WJV2_MAX_LIST_Polygon_LEN 6 /* 与协议不一致 协议为32 暂定为6 */
#define WJV2_MIN_LIST_Polygon_LEN 4
/* Polygon */
typedef struct _Polygon
{
    uint8_t u8PositionOffsetLLVNum; /* 4 ~32 */
    WJV2_STRU_PositionOffsetLLV struPositionOffsetLLV[WJV2_MAX_LIST_Polygon_LEN];
} __attribute__((packed)) WJV2_STRU_Polygon;

/* DetectedObstacleData */
typedef struct _DetectedObstacleData
{

    WJV2_ENUM_ObstacleType enumobsType;
    uint8_t u8objTypeConfidencePresent;
    WJV2_INT_Confidence n32objTypeConfidence /* OPTIONAL */;
    WJV2_INT_obsId n32obsId;
    WJV2_ENUM_SourceType enumsource;
    WJV2_INT_DSecond n32secMark;
    WJV2_STRU_PositionOffsetLLV strupos;
    WJV2_STRU_PositionConfidenceSet struposConfidence;
    WJV2_INT_Speed n32speed;
    uint8_t u8speedCfdPresent;
    WJV2_ENUM_SpeedConfidence enumspeedCfd /* OPTIONAL */;
    WJV2_INT_Heading n32heading;
    uint8_t u8headingCfdPresent;
    WJV2_ENUM_HeadingConfidence enumheadingCfd /* OPTIONAL */;
    uint8_t u8verSpeedPresent;
    WJV2_INT_Speed n32verSpeed /* OPTIONAL */;
    uint8_t u8verSpeedConfidencePresent;
    WJV2_ENUM_SpeedConfidence enumverSpeedConfidence /* OPTIONAL */;
    uint8_t u8accelSetPresent;
    WJV2_STRU_AccelerationSet4Way struaccelSet /* OPTIONAL */;
    WJV2_STRU_ObjectSize strusize;
    uint8_t u8pobjSizeConfidencePresent;
    WJV2_STRU_ObjectSizeConfidence struobjSizeConfidence /* OPTIONAL */;
    uint8_t u8trackingPresent;
    WJV2_INT_tracking n32tracking /* OPTIONAL */;
    uint8_t u8polygonPresent;
    WJV2_STRU_Polygon strupolygon /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_DetectedObstacleData;

#define WJV2_MAX_LIST_DetectedObstacleData_LEN 16 /* 与协议不一致 协议为64 暂定为16 */
#define WJV2_MIN_LIST_DetectedObstacleData_LEN 1
/* DetectedObstacleList */
typedef struct _DetectedObstacleList
{
    uint8_t u8DetectedObstacleDataNum; /* 1 ~64 */
    WJV2_STRU_DetectedObstacleData struDetectedObstacle[WJV2_MAX_LIST_DetectedObstacleData_LEN];
} __attribute__((packed)) WJV2_STRU_DetectedObstacleList;

/* PathPlanningPoint */
typedef struct _PathPlanningPoint
{

    uint8_t u8ReferenceLinkPresent;
    WJV2_STRU_ReferenceLink struposInMap /* OPTIONAL */;
    WJV2_STRU_PositionOffsetLLV strupos;
    uint8_t u8posAccuracyPresent;
    WJV2_STRU_PositionConfidenceSet struposAccuracy /* OPTIONAL */;
    uint8_t u8speedPresent;
    WJV2_INT_Speed n32speed /* OPTIONAL */;
    uint8_t u8speedCfdPresent;
    WJV2_ENUM_SpeedConfidence enumspeedCfd /* OPTIONAL */;
    uint8_t u8headingPresent;
    WJV2_INT_Heading n32heading /* OPTIONAL */;
    uint8_t u8headingCfdPresent;
    WJV2_ENUM_HeadingConfidence enumheadingCfd /* OPTIONAL */;
    uint8_t u8accelSetPresent;
    WJV2_STRU_AccelerationSet4Way struaccelSet /* OPTIONAL */;
    uint8_t u8acc4WayConfidencePresent;
    WJV2_STRU_AccSet4WayConfidence struacc4WayConfidence /* OPTIONAL */;
    uint8_t u8estimatedTimePresent;
    WJV2_INT_TimeOffset n32estimatedTime /* OPTIONAL */;
    uint8_t u8timeConfidencePresent;
    WJV2_INT_Confidence n32timeConfidence /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_PathPlanningPoint;

#define WJV2_MAX_LIST_PathPlanning_LEN 16 /* 与协议不一致 协议为100 暂定为16 */
#define WJV2_MIN_LIST_PathPlanning_LEN 1
/* PathPlanning */
typedef struct _PathPlanning
{
    uint8_t u8PathPlanningPointNum; /* 1 ~100 */
    WJV2_STRU_PathPlanningPoint struPathPlanningPoint[WJV2_MAX_LIST_PathPlanning_LEN];

} __attribute__((packed)) WJV2_STRU_PathPlanning;

/* Planning */
typedef struct _Planning
{

    uint8_t u8durationPresent;
    WJV2_INT_PlanningDuration n32duration /* OPTIONAL */;
    uint8_t u8planConfidencePresent;
    WJV2_INT_Confidence n32planConfidence /* OPTIONAL */;
    uint8_t u8drivingBehaviorPresent;
    WJV2_BIT_DriveBehavior bitdrivingBehavior /* OPTIONAL */;
    uint8_t u8pathPlanningPresent;
    WJV2_STRU_PathPlanning strupathPlanning /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_Planning;

#define WJV2_MAX_LIST_Planning_LEN 8
#define WJV2_MIN_LIST_Planning_LEN 1
/* PlanningList */
typedef struct _PlanningList
{
    uint8_t u8PlanningListNum; /* 1 ~8 */
    WJV2_STRU_Planning struPlanning[WJV2_MAX_LIST_Planning_LEN];
} __attribute__((packed)) WJV2_STRU_PlanningList;

/* MotorDataExtension */
typedef struct _MotorDataExtension
{
    uint8_t u8lightsPresent;
    WJV2_BIT_ExteriorLights bitlights /* OPTIONAL */;
    uint8_t u8vehAttitudePresent;
    WJV2_STRU_Attitude struvehAttitude /* OPTIONAL */;
    uint8_t u8vehAttitudeConfidencePresent;
    WJV2_STRU_AttitudeConfidence struvehAttitudeConfidence /* OPTIONAL */;
    uint8_t u8vehAngVelPresent;
    WJV2_STRU_AngularVelocity struvehAngVel /* OPTIONAL */;
    uint8_t u8vehAngVelConfidencePresent;
    WJV2_STRU_AngularVelocityConfidence struvehAngVelConfidence /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_MotorDataExtension;

/* Dependencies */
typedef enum _PropelledInformation_PR
{
    WJV2_PropelledInformation_PR_NOTHING, /* No components present */
    WJV2_PropelledInformation_PR_human,
    WJV2_PropelledInformation_PR_animal,
    WJV2_PropelledInformation_PR_motor
    /* Extensions may appear below */

} __attribute__((packed)) WJV2_ENUM_PropelledInformation_PR;

/* PropelledInformation */
typedef struct _PropelledInformation
{
    WJV2_ENUM_PropelledInformation_PR enumpresent;
    union WJV2_PropelledInformation_u
    {
        WJV2_ENUM_HumanPropelledType enumhuman;
        WJV2_ENUM_AnimalPropelledType enumanimal;
        WJV2_ENUM_MotorizedPropelledType enummotor;
        /*
		 * This type is extensible,
		 * possible extensions are below.
		 */
    } choice;

} __attribute__((packed)) WJV2_STRU_PropelledInformation;

/* PersonalExtensions */
typedef struct _PersonalExtensions
{
    uint8_t u8useStatePresent;
    WJV2_BIT_PersonalDeviceUsageState bituseState /* OPTIONAL */;
    uint8_t u8assistTypePresent;
    WJV2_BIT_PersonalAssistive bitassistType /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_PersonalExtensions;

/* RoadWorkerExtensions */
typedef struct _RoadWorkerExtensions
{
    uint8_t u8workerTypePresent;
    WJV2_ENUM_RoadWorkerType enumworkerType /* OPTIONAL */;
    uint8_t u8activityTypePresent;
    WJV2_BIT_RoadWorkerActivityType bitactivityType /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_RoadWorkerExtensions;

/* PersonalRequest */
typedef struct _PersonalRequest
{
    uint8_t u8crossingPresent;
    WJV2_ENUM_PersonalCrossing enumcrossing /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_PersonalRequest;

/* Non-motorData */
typedef struct _Non_motorData
{

    WJV2_ENUM_PersonalDeviceUserType enumbasicType;
    uint8_t u8propulsionPresent;
    WJV2_STRU_PropelledInformation strupropulsion /* OPTIONAL */;
    uint8_t u8clusterSizePresent;
    WJV2_ENUM_NumberOfParticipantsInCluster enumclusterSize /* OPTIONAL */;
    uint8_t u8attachmentPresent;
    WJV2_ENUM_Attachment enumattachment /* OPTIONAL */;
    uint8_t u8personalExtPresent;
    WJV2_STRU_PersonalExtensions strupersonalExt /* OPTIONAL */;
    uint8_t u8roadWorkerExtPresent;
    WJV2_STRU_RoadWorkerExtensions struroadWorkerExt /* OPTIONAL */;
    uint8_t u8personalReqPresent;
    WJV2_STRU_PersonalRequest strupersonalReq /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_Non_motorData;

/* Non-motorDataExtension */
typedef struct _Non_motorDataExtension
{
    WJV2_INT_overallRadius n32overallRadius;
    WJV2_STRU_Non_motorData strunon_motorData;

} __attribute__((packed)) WJV2_STRU_Non_motorDataExtension;

/* Dependencies */
typedef enum _type_relatedExt_PR
{
    WJV2_type_relatedExt_PR_NOTHING, /* No components present */
    WJV2_type_relatedExt_PR_motorExt,
    WJV2_type_relatedExt_PR_non_motorExt
    /* Extensions may appear below */

} __attribute__((packed)) WJV2_ENUM_type_relatedExt_PR;

typedef struct _type_relatedExt
{
    WJV2_ENUM_type_relatedExt_PR enumpresent;
    union WJV2_DetectedPTCData__type_relatedExt_u
    {
        WJV2_STRU_MotorDataExtension strumotorExt;
        WJV2_STRU_Non_motorDataExtension strunon_motorExt;
        /*
			 * This type is extensible,
			 * possible extensions are below.
			 */
    } choice;

} __attribute__((packed)) WJV2_STRU_type_relatedExt;

/* DetectedPTCData */
typedef struct _DetectedPTCData
{
    WJV2_STRU_ParticipantData struptc;
    uint8_t u8objSizeConfidencePresent;
    WJV2_STRU_ObjectSizeConfidence struobjSizeConfidence /* OPTIONAL */;
    uint8_t u8detectedPTCTypePresent;
    WJV2_ENUM_DetectedPTCType enumdetectedPTCType /* OPTIONAL */;
    uint8_t u8typeConfidencePresent;
    WJV2_INT_Confidence n32typeConfidence /* OPTIONAL */;
    uint8_t u8acc4WayConfidencePresent;
    WJV2_STRU_AccSet4WayConfidence struacc4WayConfidence /* OPTIONAL */;
    uint8_t u8statusDurationPresent;
    WJV2_INT_TimeOffset n32statusDuration /* OPTIONAL */;
    uint8_t u8pathHistoryPresent;
    WJV2_STRU_PathHistory strupathHistory /* OPTIONAL */;
    uint8_t u8planningListPresent;
    WJV2_STRU_PlanningList struplanningList /* OPTIONAL */;
    uint8_t u8trackingPresent;
    WJV2_INT_tracking n32tracking /* OPTIONAL */;
    uint8_t u8polygonPresent;
    WJV2_STRU_Polygon strupolygon /* OPTIONAL */;
    uint8_t u8type_relatedExtPresent;
    WJV2_STRU_type_relatedExt strutype_relatedExt; /* OPTIONAL */

} __attribute__((packed)) WJV2_STRU_DetectedPTCData;

#define WJV2_MAX_LIST_DetectedPTCData_LEN 32 /* 与协议不一致 协议为512 暂定为48 */
#define WJV2_MIN_LIST_DetectedPTCData_LEN 1
/* DetectedPTCList */
typedef struct _DetectedPTCList
{
    uint16_t u16DetectedPTCDataNum; /* 1 ~512 */ //此处最大200个节点，编码成功，但不能解码，问题未知
    WJV2_STRU_DetectedPTCData struDetectedPTCData[WJV2_MAX_LIST_DetectedPTCData_LEN];
} __attribute__((packed)) WJV2_STRU_DetectedPTCList;

#define WJV2_MAX_LIST_DetectedRegion_LEN 6 /* 与协议不一致 协议为8 暂定为6 */
#define WJV2_MIN_LIST_DetectedRegion_LEN 1
/* DetectedRegionList */
typedef struct _DetectedRegion
{
    uint8_t u8PolygonNum; /* 1 ~8 */
    WJV2_STRU_Polygon struPolygon[WJV2_MAX_LIST_DetectedRegion_LEN];
} __attribute__((packed)) WJV2_STRU_DetectedRegion;

/* Dependencies */
typedef enum _ReqInfo_PR
{
    WJV2_ReqInfo_PR_NOTHING, /* No components present */
    WJV2_ReqInfo_PR_laneChange,
    WJV2_ReqInfo_PR_clearTheWay,
    WJV2_ReqInfo_PR_signalPriority,
    WJV2_ReqInfo_PR_sensorSharing,
    WJV2_ReqInfo_PR_parking
    /* Extensions may appear below */

} __attribute__((packed)) WJV2_ENUM_ReqInfo_PR;

/* Req-LaneChange */
typedef struct _Req_LaneChange
{
    WJV2_STRU_NodeReferenceID struupstreamNode;
    WJV2_STRU_NodeReferenceID strudownstreamNode;
    WJV2_INT_LaneID n32targetLane;

} __attribute__((packed)) WJV2_STRU_Req_LaneChange;

/* Req-ClearTheWay */
typedef struct _Req_ClearTheWay
{
    WJV2_STRU_NodeReferenceID struupstreamNode;
    WJV2_STRU_NodeReferenceID strudownstreamNode;
    WJV2_INT_LaneID n32targetLane;
    uint8_t u8relatedPathPresent;
    WJV2_STRU_ReferencePath strurelatedPath /* OPTIONAL */;
    uint8_t u8tBeginPresent;
    WJV2_STRU_DDateTime strutBegin /* OPTIONAL */;
    uint8_t u8tEndPresent;
    WJV2_STRU_DDateTime strutEnd /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_Req_ClearTheWay;

/* MovementEx */
typedef struct _MovementEx
{

    WJV2_STRU_NodeReferenceID struremoteIntersection;
    uint8_t u8phaseIdPresent;
    WJV2_INT_PhaseID n32phaseId /* OPTIONAL */;
    uint8_t u8turn_directionPresent;
    WJV2_ENUM_Maneuver enumturn_direction /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_MovementEx;

/* Req-SignalPriority */
typedef struct _Req_SignalPriority
{
    WJV2_STRU_NodeReferenceID struintersectionId;
    WJV2_STRU_MovementEx strurequiredMov;
    uint8_t u8estimatedArrivalTimePresent;
    WJV2_INT_TimeOffset n32estimatedArrivalTime /* OPTIONAL */;
    uint8_t u8distance2IntersectionPresent;
    WJV2_INT_distance2Intersection n32distance2Intersection /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_Req_SignalPriority;

/* Req-SensorSharing */
typedef struct _Req_SensorSharing
{
    WJV2_STRU_ReferencePathList strudetectArea;

} __attribute__((packed)) WJV2_STRU_Req_SensorSharing;

/* Req-ParkingArea */
typedef struct _Req_ParkingArea
{
    WJV2_STRU_VehicleClassification struvehicleClass;
    WJV2_BIT_ParkingRequest bitreq;
    uint8_t u8parkingTypePresent;
    WJV2_BIT_ParkingType bitparkingType /* OPTIONAL */;
    uint8_t u8expectedParkingSlotIDPresent;
    WJV2_INT_expectedParkingSlotID n32expectedParkingSlotID /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_Req_ParkingArea;

/* ReqInfo */
typedef struct _ReqInfo
{
    WJV2_ENUM_ReqInfo_PR enumpresent;
    union WJV2_ReqInfo_u
    {
        WJV2_STRU_Req_LaneChange strulaneChange;
        WJV2_STRU_Req_ClearTheWay struclearTheWay;
        WJV2_STRU_Req_SignalPriority strusignalPriority;
        WJV2_STRU_Req_SensorSharing strusensorSharing;
        WJV2_STRU_Req_ParkingArea struparking;
        /*
		 * This type is extensible,
		 * possible extensions are below.
		 */
    } choice;

} __attribute__((packed)) WJV2_STRU_ReqInfo;

/* DriveRequest */
typedef struct _DriveRequest
{
    WJV2_INT_reqID n32reqID;
    WJV2_ENUM_ReqStatus enumstatus;
    uint8_t u8reqPriorityPresent;
    uint8_t u8OCTreqPriorityNum;
#define WJV2_MAX_OCTreqPriority_SIZE 1
    uint8_t u8OCTreqPriority[WJV2_MAX_OCTreqPriority_SIZE] /* OPTIONAL */;

    uint8_t u8targetVehPresent;
    uint8_t u8OCTtargetVehNum;
#define WJV2_MAX_OCTtargetVeh_SIZE 8
    uint8_t u8OCTtargetVeh[WJV2_MAX_OCTtargetVeh_SIZE] /* OPTIONAL */;

    uint8_t u8targetRSUPresent;
    uint8_t u8OCTtargetRSUNum;
#define WJV2_MAX_OCTtargetRSU_SIZE 8
    uint8_t u8OCTtargetRSU[WJV2_MAX_OCTtargetRSU_SIZE] /* OPTIONAL */;

    uint8_t u8infoPresent;
    WJV2_STRU_ReqInfo struinfo /* OPTIONAL */;
    uint8_t u8lifeTimePresent;
    WJV2_INT_TimeOffset n32lifeTime /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_DriveRequest;

/* DriveSuggestion */
typedef struct _DriveSuggestion
{

    WJV2_BIT_DriveBehavior bitsuggestion;
    uint8_t u8lifeTimePresent;
    WJV2_INT_TimeOffset n32lifeTime /* OPTIONAL */;
    uint8_t u8relatedLinkPresent;
    WJV2_STRU_ReferenceLink strurelatedLink /* OPTIONAL */;
    uint8_t u8relatedPathPresent;
    WJV2_STRU_ReferencePath strurelatedPath /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_DriveSuggestion;

/* GBICCInfo */
typedef struct _GBICCInfo
{
    uint8_t u8OCTiccIssueInfoNum;
#define WJV2_MAX_OCTiccIssueInfo_SIZE 127
#define WJV2_MIN_OCTiccIssueInfo_SIZE 0
    uint8_t u8OCTiccIssueInfo[WJV2_MAX_OCTiccIssueInfo_SIZE];

    uint8_t u8OCTiccUniTollInfoNum;
#define WJV2_MAX_OCTiccUniTollInfo_SIZE 127
#define WJV2_MIN_OCTiccUniTollInfo_SIZE 0
    uint8_t u8OCTiccUniTollInfo[WJV2_MAX_OCTiccUniTollInfo_SIZE];

    uint8_t u8OCTiccBalanceNum;
#define WJV2_MAX_OCTiccBalance_SIZE 127
#define WJV2_MIN_OCTiccBalance_SIZE 0
    uint8_t u8OCTiccBalance[WJV2_MAX_OCTiccBalance_SIZE];

} __attribute__((packed)) WJV2_STRU_GBICCInfo;

#define WJV2_MAX_LIST_DriveRequest_LEN 8
#define WJV2_MIN_LIST_DriveRequest_LEN 1
typedef struct _reqs
{

    uint8_t u8DriveRequestNum; /* 1 ~8 */
    WJV2_STRU_DriveRequest struDriveRequest[WJV2_MAX_LIST_DriveRequest_LEN];

} __attribute__((packed)) WJV2_STRU_reqsList;

/* IARData */
typedef struct _IARData
{
    uint8_t u8currentPosPresent;
    WJV2_STRU_PathPlanningPoint strucurrentPos /* OPTIONAL */;
    uint8_t u8path_PlanningPresent;
    WJV2_STRU_PathPlanning strupath_Planning /* OPTIONAL */;
    uint8_t u8currentBehaviorPresent;
    WJV2_BIT_DriveBehavior bitcurrentBehavior /* OPTIONAL */;
    uint8_t u8reqsPresent;
    WJV2_STRU_reqsList strureqs; /* OPTIONAL */

} __attribute__((packed)) WJV2_STRU_IARData;

/* LaneCoordination */
typedef struct _LaneCoordination
{
    WJV2_STRU_ReferenceLink strutargetLane;
    uint8_t u8relatedPathPresent;
    WJV2_STRU_ReferencePath strurelatedPath /* OPTIONAL */;
    uint8_t u8tBeginPresent;
    WJV2_STRU_DDateTime strutBegin /* OPTIONAL */;
    uint8_t u8tEndPresent;
    WJV2_STRU_DDateTime strutEnd /* OPTIONAL */;
    uint8_t u8recommendedSpeedPresent;
    WJV2_INT_Speed n32recommendedSpeed /* OPTIONAL */;
    uint8_t u8recommendedBehaviorPresent;
    WJV2_BIT_DriveBehavior bitrecommendedBehavior /* OPTIONAL */;
    uint8_t u8infoPresent;
    WJV2_BIT_CoordinationInfo bitinfo /* OPTIONAL */;
    uint8_t u8descriptionPresent;
    WJV2_STRU_Description strudescription /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_LaneCoordination;

/* ST-Point */
typedef struct _ST_Point
{
    WJV2_INT_s_axis n32s_axis;
    WJV2_INT_t_axis n32t_axis;

} __attribute__((packed)) WJV2_STRU_ST_Point;

#define WJV2_MAX_LIST_ST_Point_LEN 6 /* 与协议不一致 协议为63 暂定为6 */
#define WJV2_MIN_LIST_ST_Point_LEN 2
/* STPointList */
typedef struct _STPointList
{
    uint8_t u8ST_PointNum; /* 2 ~63 */
    WJV2_STRU_ST_Point struST_Point[WJV2_MAX_LIST_ST_Point_LEN];
} __attribute__((packed)) WJV2_STRU_STPointList;

/* LaneLineType */
typedef struct _LaneLineType
{
    WJV2_ENUM_Dotted_SolidMarkingLineType enumleftLaneLine;
    WJV2_ENUM_Dotted_SolidMarkingLineType enumrightLaneLine;

} __attribute__((packed)) WJV2_STRU_LaneLineType;

/* LaneEx */
typedef struct _LaneEx
{
    WJV2_INT_LaneRefID n32laneRefID;
    uint8_t u8laneWidthPresent;
    WJV2_INT_LaneWidth n32laneWidth /* OPTIONAL */;
    uint8_t u8laneAttributesPresent;
    WJV2_STRU_LaneAttributes strulaneAttributes /* OPTIONAL */;
    uint8_t u8maneuversPresent;
    WJV2_BIT_AllowedManeuvers bitmaneuvers /* OPTIONAL */;
    uint8_t u8connectsTo_exPresent;
    WJV2_STRU_ConnectsToExList struconnectsTo_ex /* OPTIONAL */;
    uint8_t u8speedLimitsPresent;
    WJV2_STRU_SpeedLimitList struspeedLimits /* OPTIONAL */;
    uint8_t u8st_pointsPresent;
    WJV2_STRU_STPointList strust_points /* OPTIONAL */;
    uint8_t u8laneLineTypePresent;
    WJV2_STRU_LaneLineType strulaneLineType /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_LaneEx;

#define WJV2_MAX_LIST_LaneEx_LEN 4 /* 与协议不一致 协议为32 暂定为4 */
#define WJV2_MIN_LIST_LaneEx_LEN 1
/* LaneExList */
typedef struct _LaneExList
{
    uint8_t u8LaneExNum; /* 1 ~32 */
    WJV2_STRU_LaneEx struLaneEx[WJV2_MAX_LIST_LaneEx_LEN];
} __attribute__((packed)) WJV2_STRU_LaneExList;

#define WJV2_MAX_LIST_MovementEx_LEN 4 /* 与协议不一致 协议为32 暂定为4 */
#define WJV2_MIN_LIST_MovementEx_LEN 1
/* MovementExList */
typedef struct _MovementExList
{
    uint8_t u8MovementExNum; /* 1 ~32*/
    WJV2_STRU_MovementEx struMovementEx[WJV2_MAX_LIST_MovementEx_LEN];
} __attribute__((packed)) WJV2_STRU_MovementExList;

/* Section */
typedef struct _Section
{
    WJV2_INT_SectionId n32secId;
    WJV2_STRU_LaneExList strulanes;

} __attribute__((packed)) WJV2_STRU_Section;

#define WJV2_MAX_LIST_Section_LEN 4 /* 与协议不一致 协议为32 暂定为4 */
#define WJV2_MIN_LIST_Section_LEN 1
/* SectionList */
typedef struct _SectionList
{
    uint8_t u8SectionNum; /* 1 ~32*/
    WJV2_STRU_Section struSection[WJV2_MAX_LIST_Section_LEN];
} __attribute__((packed)) WJV2_STRU_SectionList;

/* LinkEx */
typedef struct _LinkEx
{
    uint8_t u8namePresent;
    WJV2_IA5_DescriptiveName strname /* OPTIONAL */;
    WJV2_STRU_NodeReferenceID struupstreamNodeId;
    uint8_t u8speedLimitsPresent;
    WJV2_STRU_SpeedLimitList struspeedLimits /* OPTIONAL */;
    uint8_t u8linkWidthPresent;
    WJV2_INT_LaneWidth n32linkWidth /* OPTIONAL */;
    uint8_t u8refLinePresent;
    WJV2_STRU_PointList strurefLine /* OPTIONAL */;
    uint8_t u8movements_exPresent;
    WJV2_STRU_MovementExList strumovements_ex /* OPTIONAL */;
    WJV2_STRU_SectionList strusections;

} __attribute__((packed)) WJV2_STRU_LinkEx;

#define WJV2_MAX_LIST_LinkEx_LEN 2 /* 与协议不一致 协议为32 暂定为2 */
#define WJV2_MIN_LIST_LinkEx_LEN 1
/* LinkExList */
typedef struct _LinkExList
{
    uint8_t u8LinkExNum; /* 1 ~32*/
    WJV2_STRU_LinkEx struLinkEx[WJV2_MAX_LIST_LinkEx_LEN];
} __attribute__((packed)) WJV2_STRU_LinkExList;

/* MemberNode */
typedef struct _MemberNode
{
    uint8_t u8OCTvidNum;
#define WJV2_MAX_OCTvid_SIZE 8
    uint8_t u8OCTvid[WJV2_MAX_OCTvid_SIZE];

} __attribute__((packed)) WJV2_STRU_MemberNode;

#define WJV2_MAX_LIST_Member_LEN 16 /* 与协议不一致 协议为32 暂定为16 */
#define WJV2_MIN_LIST_Member_LEN 1
/* MemberList */
typedef struct _MemberList
{
    uint8_t u8MemberNodeNum; /* 1 ~32*/
    WJV2_STRU_MemberNode struMember[WJV2_MAX_LIST_Member_LEN];
} __attribute__((packed)) WJV2_STRU_MemberList;

/* MemberManagement */
typedef struct _MemberManagement
{
    WJV2_STRU_MemberList strumemberList;
    uint8_t u8joiningListPresent;
    WJV2_STRU_MemberList strujoiningList /* OPTIONAL */;
    uint8_t u8leavingListPresent;
    WJV2_STRU_MemberList struleavingList /* OPTIONAL */;
    WJV2_INT_capacity n32capacity;
    WJV2_INT_BOOLEAN n32openToJoin;

} __attribute__((packed)) WJV2_STRU_MemberManagement;

#define WJV2_MAX_LIST_motorVehicleProhibitedZones_LEN 4 /* 与协议不一致 协议为16 暂定为4 */
#define WJV2_MIN_LIST_motorVehicleProhibitedZones_LEN 1
typedef struct _non_motorVehicleProhibitedZones
{
    uint8_t u8PolygonNum; /* 1 ~16 */
    WJV2_STRU_Polygon struPolygon[WJV2_MAX_LIST_motorVehicleProhibitedZones_LEN];
} __attribute__((packed)) WJV2_STRU_non_motorVehicleProhibitedZones;

#define WJV2_MAX_LIST_gridLineMarkingProhibitedZones_LEN 4 /* 与协议不一致 协议为16 暂定为4 */
#define WJV2_MIN_LIST_gridLineMarkingProhibitedZones_LEN 2
typedef struct _gridLineMarkingProhibitedZones
{
    uint8_t u8PolygonNum; /* 2~16 */
    WJV2_STRU_Polygon struPolygon[WJV2_MAX_LIST_gridLineMarkingProhibitedZones_LEN];
} __attribute__((packed)) WJV2_STRU_gridLineMarkingProhibitedZones;

/* ProhibitedZone */
typedef struct _ProhibitedZone
{
    uint8_t u8centralCircleProhibitedZonePresent;
    WJV2_STRU_Polygon strucentralCircleProhibitedZone /* OPTIONAL */;
    uint8_t u8motorVehicleProhibitedZonesPresent;
    WJV2_STRU_non_motorVehicleProhibitedZones strunon_motorVehicleProhibitedZones; /* OPTIONAL */
    uint8_t u8gridLineMarkingProhibitedZonesPresent;
    WJV2_STRU_gridLineMarkingProhibitedZones strugridLineMarkingProhibitedZones; /* OPTIONAL */

} __attribute__((packed)) WJV2_STRU_ProhibitedZone;

typedef struct _Node
{
    uint8_t u8namePresent;
    WJV2_IA5_DescriptiveName stria5name; /* OPTIONAL */
    WJV2_STRU_NodeReferenceID struid;
    WJV2_STRU_Position3D strurefPos;
    uint8_t u8inLinksPresent;
    WJV2_STRU_LinkList struinLinks; /* OPTIONAL */
    uint8_t u8inLinks_exPresent;
    WJV2_STRU_LinkExList struinLinks_ex; /* OPTIONAL */
    uint8_t u8prohibitedzonePresent;
    WJV2_STRU_ProhibitedZone struprohibitedzone /* OPTIONAL */;
} __attribute__((packed)) WJV2_STRU_Node; /* 地图节点 */

#define WJV2_MAX_LIST_NODE_LEN 8 /* 与协议不一致 协议为32 暂定为4 */
#define WJV2_MIN_LIST_NODE_LEN 1
typedef struct _NodeList
{
    uint8_t u8NodeNum; /* 1 ~ 32 */
    WJV2_STRU_Node struNode[WJV2_MAX_LIST_NODE_LEN];
} __attribute__((packed)) WJV2_STRU_NodeList; /* 地图节点列表 */

#define WJV2_MAX_LIST_Payment_LEN 16
#define WJV2_MIN_LIST_Payment_LEN 1
typedef struct _PaymentList
{
    uint8_t u8ApplicationParameterNum; /* 1 ~ 16 */
    WJV2_STRU_ApplicationParameter struApplicationParameter[WJV2_MAX_LIST_Payment_LEN];
} __attribute__((packed)) WJV2_STRU_PaymentList;

/* RST */
typedef struct _RST
{
    WJV2_STRU_DDateTime strutime;
    uint8_t u8OCTidNum;
#define WJV2_MAX_OCTid_SIZE 8
    uint8_t u8OCTid[WJV2_MAX_OCTid_SIZE];

    WJV2_STRU_PaymentList strupaymentList;

} __attribute__((packed)) WJV2_STRU_RST;

/* RTCMmsg */
typedef struct _RTCMmsg
{
    uint8_t u8revPresent;
    WJV2_ENUM_RTCM_Revision enumrev /* OPTIONAL */;
    uint8_t u8rtcmIDPresent;
    WJV2_INT_RTCM_ID n32rtcmID /* OPTIONAL */;
    WJV2_OCT_RTCM_PayloadData strupayload;

} __attribute__((packed)) WJV2_STRU_RTCMmsg;

/* Date */
typedef struct _Date
{
    WJV2_INT_DYear n32year;
    WJV2_INT_DMonth n32month;
    WJV2_INT_DDay n32day;

} __attribute__((packed)) WJV2_STRU_Date;
/* SysInfo */
typedef struct _SysInfo
{
#define WJV2_MAX_OCTcontractProvider_SIZE 8
    uint8_t u8OCTcontractProvider[WJV2_MAX_OCTcontractProvider_SIZE];
    WJV2_INT_contractType n32contractType;
    WJV2_INT_contractVersion n32contractVersion;
#define WJV2_MAX_OCTcontractSerialNumer_SIZE 8
    uint8_t u8OCTcontractSerialNumer[WJV2_MAX_OCTcontractSerialNumer_SIZE];
    WJV2_STRU_Date strucontractSignedDate;
    WJV2_STRU_Date strucontractExpiredDate;
#define WJV2_MAX_OCTreserved_SIZE 64
    uint8_t u8OCTreserved[WJV2_MAX_OCTreserved_SIZE];

} __attribute__((packed)) WJV2_STRU_SysInfo;

/* VehicleCoordination */
typedef struct _VehicleCoordination
{
    uint8_t u8OCTvehIdNum;
#define WJV2_MAX_OCTvehId_SIZE 8
    uint8_t u8OCTvehId[WJV2_MAX_OCTvehId_SIZE];
    uint8_t u8driveSuggestionPresent;
    WJV2_STRU_DriveSuggestion strudriveSuggestion /* OPTIONAL */;
    uint8_t u8pathGuidancePresent;
    WJV2_STRU_PathPlanning strupathGuidance /* OPTIONAL */;
    uint8_t u8infoPresent;
    WJV2_BIT_CoordinationInfo bitinfo /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_VehicleCoordination;

/* VehicleDimensions */
typedef struct _VehicleDimensions
{
    WJV2_INT_VehicleLength n32vehicleLength;
    WJV2_INT_VehicleWidth n32vehicleWidth;
    WJV2_INT_VehicleHeight vehicleHeigth;

} __attribute__((packed)) WJV2_STRU_VehicleDimensions;

/* VehicleInfo */
typedef struct _VehicleInfo
{
#define WJV2_MAX_OCTvehicleLicencePlateNumber_SIZE 12
    uint8_t u8OCTvehicleLicencePlateNumber[WJV2_MAX_OCTvehicleLicencePlateNumber_SIZE];

#define WJV2_MAX_OCTvehicleLicencePlateColor_SIZE 2
    uint8_t u8OCTvehicleLicencePlateColor[WJV2_MAX_OCTvehicleLicencePlateColor_SIZE];

    WJV2_INT_vehicleTollingClass n32vehicleTollingClass;
    WJV2_INT_vehicleUserType n32vehicleUserType;
    WJV2_STRU_VehicleDimensions struvehicleDimensions;
    WJV2_INT_vehicleWheels n32vehicleWheels;
    WJV2_INT_vehicleAxles n32vehicleAxles;
    WJV2_INT_vehicleWheelBases n32vehicleWheelBases;
    WJV2_INT_vehicleWeightLimits n32vehicleWeightLimits;
    uint8_t u8OCTvehicleSpecificInformationNum;
#define WJV2_MAX_OCTvehicleSpecificInformation_SIZE 16
    uint8_t u8OCTvehicleSpecificInformation[WJV2_MAX_OCTvehicleSpecificInformation_SIZE];

#define WJV2_MAX_OCTvehicleEngineNumber_SIZE 16
    uint8_t u8OCTvehicleEngineNumber[WJV2_MAX_OCTvehicleEngineNumber_SIZE];

    uint8_t u8descriptionPresent;
    uint16_t u16OCTdescriptionNum;
#define WJV2_MAX_OCTdescription_SIZE 256
#define WJV2_MIN_OCTdescription_SIZE 1
    uint8_t u8OCTdescription[WJV2_MAX_OCTdescription_SIZE]; /* OPTIONAL */

} __attribute__((packed)) WJV2_STRU_VehicleInfo;

/* Dependencies */
typedef enum _OBUPaymentInfo_PR
{
    WJV2_OBUPaymentInfo_PR_NOTHING, /* No components present */
    WJV2_OBUPaymentInfo_PR_obuPaymentInfoType1
    /* Extensions may appear below */

} __attribute__((packed)) WJV2_ENUM_OBUPaymentInfo_PR;

/* PassedPos */
typedef struct _PassedPos
{
    WJV2_STRU_TollingPos strutollingPos;
    WJV2_STRU_DDateTime strutollingTime;
    uint8_t u8tollingAmountPresent;
    uint8_t u8OCTtollingAmountNum;
#define WJV2_MAX_OCTtollingAmount_SIZE 4
    uint8_t u8OCTtollingAmount[WJV2_MAX_OCTtollingAmount_SIZE]; /* OPTIONAL */

} __attribute__((packed)) WJV2_STRU_PassedPos;

#define WJV2_MAX_LIST_PassedPos_LEN 200 /*Over 200 decode faild, such as 201*/
#define WJV2_MIN_LIST_PassedPos_LEN 2
typedef struct _PassedPosList
{
    uint16_t u16PassedPosNum; /* 2 ~ 512 */ /*Over 200 encode success but decode failed; such as 201 ;Pay Attention*/
    WJV2_STRU_PassedPos struPassedPos[WJV2_MAX_LIST_PassedPos_LEN];
} __attribute__((packed)) WJV2_STRU_PassedPosList;

/* PassedSitesInfo */
typedef struct _PassedSitesInfo
{
    uint8_t u8entranceInfoPresent;
    WJV2_STRU_PassedPos struentranceInfo /* OPTIONAL */;
    uint8_t u8passedPosPresent;
    WJV2_STRU_PassedPosList strupassedPos; /* OPTIONAL */

} __attribute__((packed)) WJV2_STRU_PassedSitesInfo;

/* OBUPaymentInfoType1 */
typedef struct _OBUPaymentInfoType1
{
    uint8_t u8equipmentClassPresent;
    WJV2_ENUM_EquipmentClass enumequipmentClass /* OPTIONAL */;
    uint8_t u8gbiCCInfoPresent;
    WJV2_STRU_GBICCInfo strugbiCCInfo /* OPTIONAL */;
    uint8_t u8sysInfoPresent;
    WJV2_STRU_SysInfo strusysInfo /* OPTIONAL */;
    uint8_t u8vehicleInfoPresent;
    WJV2_STRU_VehicleInfo struvehicleInfo /* OPTIONAL */;
    uint8_t u8passedSitesInfoPresent;
    WJV2_STRU_PassedSitesInfo strupassedSitesInfo /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_OBUPaymentInfoType1;

/* OBUPaymentInfo */
typedef struct _OBUPaymentInfo
{
    WJV2_ENUM_OBUPaymentInfo_PR enumpresent;
    union WJV2_OBUPaymentInfo_u
    {
        WJV2_STRU_OBUPaymentInfoType1 struobuPaymentInfoType1;
        /*
		 * This type is extensible,
		 * possible extensions are below.
		 */
    } choice;

} __attribute__((packed)) WJV2_STRU_OBUPaymentInfo;

/* VPApplicationParameter */
typedef struct _VPApplicationParameter
{
    WJV2_ENUM_PaymentEntityID enumpid;
    WJV2_STRU_OBUPaymentInfo struobuPaymentInfo;

} __attribute__((packed)) WJV2_STRU_VPApplicationParameter;

#define WJV2_MAX_LIST_VPApplicationParameter_LEN 16
#define WJV2_MIN_LIST_VPApplicationParameter_LEN 1
typedef struct _VPApplicationList
{
    uint8_t u8VPApplicationParameterNum; /* 1 ~ 16 */
    WJV2_STRU_VPApplicationParameter struVPApplicationParameter[WJV2_MAX_LIST_VPApplicationParameter_LEN];
} __attribute__((packed)) WJV2_STRU_VPApplicationList;

/* OBUMotionStatus */
typedef struct _OBUMotionStatus
{
    uint8_t u8posPresent;
    WJV2_STRU_Position3D strupos /* OPTIONAL */;
    uint8_t u8headingPresent;
    WJV2_INT_Heading n32heading /* OPTIONAL */;
    uint8_t u8speedPresent;
    WJV2_INT_Speed n32speed /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_OBUMotionStatus;

/* OBUInfo */
typedef struct _OBUInfo
{
    WJV2_ENUM_OBUType enumobuType;
    uint8_t u8obuMotionStatusPresent;
    WJV2_STRU_OBUMotionStatus struobuMotionStatus /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_OBUInfo;

/* VSI */
typedef struct _VSI
{
    WJV2_STRU_DDateTime strutime;
#define WJV2_MAX_OCTobuId_SIZE 8
    uint8_t u8OCTobuId[WJV2_MAX_OCTobuId_SIZE];
    uint8_t u8targetIdPresent;
#define WJV2_MAX_OCTtargetId_SIZE 8
    uint8_t u8OCTtargetId[WJV2_MAX_OCTtargetId_SIZE]; /* OPTIONAL */
    uint8_t u8obuInfoPresent;
    WJV2_STRU_OBUInfo struobuInfo /* OPTIONAL */;
    uint8_t u8vpapplicationListPresent;
    WJV2_STRU_VPApplicationList struvpapplicationList /* OPTIONAL */;
    uint8_t u8rndOBUPresent;
    WJV2_OCT_RandStr8Data strurndOBU /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_VSI;

/* ParkingLotInfo */
typedef struct _ParkingLotInfo
{
    uint8_t u8idPresent;
    WJV2_INT_ParkingLotInfo_id n32id /* OPTIONAL */;
    uint8_t u8namePresent;
    WJV2_IA5_DescriptiveName strname /* OPTIONAL */;
    uint8_t u8numberPresent;
    WJV2_INT_number n32number /* OPTIONAL */;
    uint8_t u8buildingLayerNumPresent;
    WJV2_INT_buildingLayerNum n32buildingLayerNum /* OPTIONAL */;
    uint8_t u8avpTypePresent;
    WJV2_ENUM_AVPType enumavpType /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_ParkingLotInfo;

#define WJV2_MAX_LIST_PAMNodeID_LEN 32
#define WJV2_MIN_LIST_PAMNodeID_LEN 1
typedef struct _PAMMovementList
{
    uint8_t u8PAMNodeIDNum; /* 1 ~ 32 */
    WJV2_INT_PAMNodeID struPAMNodeID[WJV2_MAX_LIST_PAMNodeID_LEN];
} __attribute__((packed)) WJV2_STRU_PAMMovementList;

/* ParkingSlotPosition */
typedef struct _ParkingSlotPosition
{
    WJV2_STRU_PositionOffsetLLV strutopLeft;
    WJV2_STRU_PositionOffsetLLV strutopRight;
    WJV2_STRU_PositionOffsetLLV strubottomLeft;

} __attribute__((packed)) WJV2_STRU_ParkingSlotPosition;

/* ParkingSlot */
typedef struct _ParkingSlot
{
    WJV2_INT_slotID n32slotID;
    uint8_t u8positionPresent;
    WJV2_STRU_ParkingSlotPosition struposition /* OPTIONAL */;
    uint8_t u8signPresent;
    WJV2_IA5_DescriptiveName strsign /* OPTIONAL */;
    WJV2_BIT_ParkingType bitparkingType;
    WJV2_ENUM_SlotStatus enumstatus;
    WJV2_ENUM_ParkingSpaceTheta enumparkingSpaceTheta;
    WJV2_ENUM_ParkingLock enumparkingLock;

} __attribute__((packed)) WJV2_STRU_ParkingSlot;

#define WJV2_MAX_LIST_ParkingSlot_LEN 32 /* 与协议不一致 协议为256 暂定为32 */
#define WJV2_MIN_LIST_ParkingSlot_LEN 1
typedef struct _ParkingSlots
{
    uint16_t u16ParkingSlotNum; /* 1 ~ 256 */
    WJV2_STRU_ParkingSlot struParkingSlot[WJV2_MAX_LIST_ParkingSlot_LEN];
} __attribute__((packed)) WJV2_STRU_ParkingSlots;

/* PAMDrive */
typedef struct _PAMDrive
{
    WJV2_INT_PAMNodeID n32upstreamPAMNodeId;
    uint8_t u8driveIDPresent;
    WJV2_INT_driveID n32driveID /* OPTIONAL */;
    uint8_t u8twowaySeprationPresent;
    WJV2_INT_BOOLEAN n32twowaySepration /* OPTIONAL */;
    uint8_t u8speedLimitPresent;
    WJV2_INT_Speed n32speedLimit /* OPTIONAL */;
    uint8_t u8heightRestrictionPresent;
    WJV2_INT_heightRestriction n32heightRestriction /* OPTIONAL */;
    uint8_t u8driveWidthPresent;
    WJV2_INT_LaneWidth n32driveWidth /* OPTIONAL */;
    uint8_t u8laneNumPresent;
    WJV2_INT_laneNum n32laneNum /* OPTIONAL */;
    uint8_t u8pointsPresent;
    WJV2_STRU_PointList strupoints /* OPTIONAL */;
    uint8_t u8movementsPresent;
    WJV2_STRU_PAMMovementList strumovements /* OPTIONAL */;
    uint8_t u8parkingSlotsPresent;
    WJV2_STRU_ParkingSlots struparkingSlots /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_PAMDrive;

#define WJV2_MAX_LIST_PAMDrive_LEN 16 /* 与协议不一致 协议为63 暂定为16 */
#define WJV2_MIN_LIST_PAMDrive_LEN 1
typedef struct _PAMDriveList
{
    uint8_t u8PAMDriveNum; /* 1 ~ 63 */
    WJV2_STRU_PAMDrive struPAMDrive[WJV2_MAX_LIST_PAMDrive_LEN];
} __attribute__((packed)) WJV2_STRU_PAMDriveList;

/* PAMNode */
typedef struct _PAMNode
{
    WJV2_INT_PAMNodeID n32id;
    WJV2_STRU_Position3D strurefPos;
    uint8_t u8floorPresent;
    WJV2_INT_floor n32floor /* OPTIONAL */;
    uint8_t u8attributesPresent;
    WJV2_BIT_PAMNodeAttributes bitattributes /* OPTIONAL */;
    uint8_t u8inDrivesPresent;
    WJV2_STRU_PAMDriveList struinDrives /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_PAMNode;

#define WJV2_MAX_LIST_PAMNode_LEN 8 /* 与协议不一致 协议为63 暂定为8 */
#define WJV2_MIN_LIST_PAMNode_LEN 1
typedef struct _PAMNodeList
{
    uint8_t u8PAMNodeNum; /* 1 ~ 63 */
    WJV2_STRU_PAMNode struPAMNode[WJV2_MAX_LIST_PAMNode_LEN];
} __attribute__((packed)) WJV2_STRU_PAMNodeList;

typedef struct _drivePath
{
    uint8_t u8PAMNodeIDNum; /* 1 ~ 32 */
    WJV2_INT_PAMNodeID struPAMNodeID[WJV2_MAX_LIST_PAMNodeID_LEN];
} __attribute__((packed)) WJV2_STRU_drivePath;

/* ParkingGuide */
typedef struct _ParkingGuide
{
#define WJV2_MAX_OCTvehId_SIZE 8
    uint8_t u8OCTvehId[WJV2_MAX_OCTvehId_SIZE];

    WJV2_STRU_drivePath strudrivePath;

    uint8_t u8targetParkingSlotPresent;
    WJV2_INT_targetParkingSlot n32targetParkingSlot /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_ParkingGuide;

#define WJV2_MAX_LIST_ParkingGuide_LEN 16
#define WJV2_MIN_LIST_ParkingGuide_LEN 1
typedef struct _parkingAreaGuidance
{
    uint8_t u8ParkingGuideNum; /* 1 ~ 16 */
    WJV2_STRU_ParkingGuide struParkingGuide[WJV2_MAX_LIST_ParkingGuide_LEN];
} __attribute__((packed)) WJV2_STRU_parkingAreaGuidance;

/* Dependencies */
typedef enum _payment_PR
{
    WJV2_payment_PR_NOTHING, /* No components present */
    WJV2_payment_PR_initialzation_request,
    WJV2_payment_PR_initialzation_response,
    WJV2_payment_PR_action_request,
    WJV2_payment_PR_action_response
    /* Extensions may appear below */

} __attribute__((packed)) WJV2_ENUM_payment_PR;

typedef struct _payment
{
    WJV2_ENUM_payment_PR enumpresent;
    union WJV2_VehiclePaymentMessage__payment_u
    {
        WJV2_STRU_RST struinitialzation_request;
        WJV2_STRU_VSI struinitialzation_response;
        WJV2_STRU_Action_Request struaction_request;
        WJV2_STRU_Action_Response struaction_response;
        /*
			 * This type is extensible,
			 * possible extensions are below.
			 */
    } choice;

} __attribute__((packed)) WJV2_STRU_payment;

#define WJV2_MAX_LIST_corrections_LEN 5
#define WJV2_MIN_LIST_corrections_LEN 1
typedef struct _corrections
{
    uint8_t u8RTCMmsgNum; /* 1 ~ 5 */
    WJV2_STRU_RTCMmsg struRTCMmsg[WJV2_MAX_LIST_corrections_LEN];
} __attribute__((packed)) WJV2_STRU_corrections;

/* AuxiliarySign */
typedef struct _AuxiliarySign
{
    uint8_t u8signWithVehicleTypePresent;
    WJV2_BIT_AuxiliarySignVehicleType bitsignWithVehicleType /* OPTIONAL */;
    uint8_t u8signDirectionPresent;
    WJV2_ENUM_AuxiliarySignDirection enumsignDirection /* OPTIONAL */;

} __attribute__((packed)) WJV2_STRU_AuxiliarySign;
#endif /* 文件结束 */