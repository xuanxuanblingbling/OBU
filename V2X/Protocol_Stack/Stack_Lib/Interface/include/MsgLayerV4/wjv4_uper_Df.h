/**
* @file         :wjv4_uper_Df.h
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
#ifndef __WJV4_UPER_DF_H_
#define __WJV4_UPER_DF_H_
/*********************************头文件包含********************************************/
#include "wjv4_uper_De.h"
/*********************************标准头文件********************************************/

/*********************************自定义头文件******************************************/
typedef struct _v4AccelerationSet4Way
{
    WJV4_INT_Acceleration n32long;
    WJV4_INT_Acceleration n32lat;
    WJV4_INT_VerticalAcceleration n32vert;
    WJV4_INT_YawRate n32yaw;
} __attribute__((packed)) WJV4_STRU_AccelerationSet4Way; /* 车辆四轴加速度 */
typedef struct _v4BrakeSystemStatus
{
    uint8_t u8brakePadelPresent;
    WJV4_ENUM_BrakePedalStatus enumbrakePadel; /* OPTIONAL */
    uint8_t u8wheelBrakesPresent;
    WJV4_BIT_BrakeAppliedStatus strbitwheelBrakes; /* OPTIONAL */
    uint8_t u8tractionPresent;
    WJV4_ENUM_TractionControlStatus enumtraction; /* OPTIONAL */
    uint8_t u8absPresent;
    WJV4_ENUM_AntiLockBrakeStatus enumabs; /* OPTIONAL */
    uint8_t u8scsPresent;
    WJV4_ENUM_StabilityControlStatus enumscs; /* OPTIONAL */
    uint8_t u8brakeBoostPresent;
    WJV4_ENUM_BrakeBoostApplied enumbrakeBoost; /* OPTIONAL */
    uint8_t u8auxBrakesPresent;
    WJV4_ENUM_AuxiliaryBrakeStatus enumauxBrakes;      /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_BrakeSystemStatus; /* 车辆的刹车系统状态 */
typedef struct _v4ConnectingLane
{
    WJV4_INT_LaneID n32lane;
    uint8_t u8maneuverPresent;
    WJV4_BIT_AllowedManeuvers strbitmaneuver;       /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_ConnectingLane; /* 定位上游车道转向连接的下游车道 */
typedef struct _v4NodeReferenceID
{
    uint8_t u8regionPresent;
    WJV4_INT_RoadRegulatorID n32region; /* OPTIONAL */
    WJV4_INT_NodeID n32id;
} __attribute__((packed)) WJV4_STRU_NodeReferenceID; /* 节点ID */
typedef struct _v4Connection
{
    WJV4_STRU_NodeReferenceID struremoteIntersection;
    uint8_t u8connectingLanePresent;
    WJV4_STRU_ConnectingLane struconnectingLane; /* OPTIONAL */
    uint8_t u8phaseIdPresent;
    WJV4_INT_PhaseID n32phaseId;                /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_Connection; /* 当前车道与下游路段中车道的连接关系 */
#define WJV4_MAX_LIST_CONNECTION_LEN 8          /* 协议规定 1 ～ 16 暂定 1～ 8与新四跨一致 */
#define WJV4_MIN_LIST_CONNECTION_LEN 1
typedef struct _v4ConnectsToList
{
    uint8_t u8ConnectionNum; /* 1 ~ 16 */
    WJV4_STRU_Connection struConnection[WJV4_MAX_LIST_CONNECTION_LEN];
} __attribute__((packed)) WJV4_STRU_ConnectsToList; /* 路段中每条车道，在下游路口处与下游路段中车道的转向连接关系列表 */
typedef struct _v4DDateTime
{
    uint8_t u8yearPresent;
    WJV4_INT_DYear n32year; /* OPTIONAL */
    uint8_t u8monthPresent;
    WJV4_INT_DMonth n32month; /* OPTIONAL */
    uint8_t u8dayPresent;
    WJV4_INT_DDay n32day; /* OPTIONAL */
    uint8_t u8hourPresent;
    WJV4_INT_DHour n32hour; /* OPTIONAL */
    uint8_t u8minutePresent;
    WJV4_INT_DMinute n32minute; /* OPTIONAL */
    uint8_t u8secondPresent;
    WJV4_INT_DSecond n32second; /* OPTIONAL */
    uint8_t u8offsetPresent;
    WJV4_INT_DTimeOffset n32offset;            /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_DDateTime; /* 完整的日期和时间数据单元 */
typedef enum
{

    WJV4_DescriptionNOTHING = 0,
    WJV4_DescriptiontextString = 1,
    WJV4_DescriptiontextGB2312 = 2,
} WJV4_ENUM_DescriptionStringChoice;
typedef struct _v4Description
{
    WJV4_ENUM_DescriptionStringChoice enumDescriptionStringChoice;
    uint32_t u32textNum;
    union
    {
#define WJV4_MAX_IA5_STRING_LEN 512
#define WJV4_MIN_IA5_STRING_LEN 1
        uint8_t u8textString[WJV4_MAX_IA5_STRING_LEN]; /* 1 ~ 512 */
#define WJV4_MAX_OCT_STRING_LEN 256
#define WJV4_MIN_OCT_STRING_LEN 1
        uint16_t u16textGB2312[WJV4_MAX_OCT_STRING_LEN]; /* 2 ~ 512 */
    } u;
} __attribute__((packed)) WJV4_STRU_Description; /* 文本描述信息 */
typedef struct _v4MotionConfidenceSet
{
    uint8_t u8speedCfdPresent;
    WJV4_ENUM_SpeedConfidence enumspeedCfd; /* OPTIONAL */
    uint8_t u8headingCfdPresent;
    WJV4_ENUM_HeadingConfidence enumheadingCfd; /* OPTIONAL */
    uint8_t u8steerCfdPresent;
    WJV4_ENUM_SteeringWheelAngleConfidence enumsteerCfd; /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_MotionConfidenceSet; /* 车辆运行状态的精度 */
typedef struct _v4PositionConfidenceSet
{
    WJV4_ENUM_PositionConfidence enumpos;
    uint8_t u8elevationPresent;
    WJV4_ENUM_ElevationConfidence enumelevation;           /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_PositionConfidenceSet; /* 当前实时位置（经纬度和高程）的精度大小 */
typedef struct _v4Position3D
{
    WJV4_INT_Latitude n32lat;
    WJV4_INT_Longitude n32long;
    uint8_t u8elevationPresent;
    WJV4_INT_Elevation n32elevation;            /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_Position3D; /* 三维的坐标位置，经纬度和高程 */
typedef struct _v4PositionalAccuracy
{
    WJV4_INT_SemiMajorAxisAccuracy n32semiMajor;
    WJV4_INT_SemiMinorAxisAccuracy n32semiMinor;
    WJV4_INT_SemiMajorAxisOrientation n32orientation;
} __attribute__((packed)) WJV4_STRU_PositionalAccuracy; /* 基于椭圆模型定义一个定位系统自身的精度 */
typedef struct _v4FullPositionVector
{
    uint8_t u8utcTimePresent;
    WJV4_STRU_DDateTime struutcTime; /* OPTIONAL */
    WJV4_STRU_Position3D strupos;
    uint8_t u8headingPresent;
    WJV4_INT_Heading n32heading; /* OPTIONAL */
    uint8_t u8transmissionPresent;
    WJV4_ENUM_TransmissionState enumtransmission; /* OPTIONAL */
    uint8_t u8speedPresent;
    WJV4_INT_Speed n32speed; /* OPTIONAL */
    uint8_t u8posAccuracyPresent;
    WJV4_STRU_PositionalAccuracy struposAccuracy; /* OPTIONAL */
    uint8_t u8posConficencePresent;
    WJV4_STRU_PositionConfidenceSet struposConficence; /* OPTIONAL */
    uint8_t u8timeConfidencePresent;
    WJV4_ENUM_TimeConfidence enumtimeConfidence; /* OPTIONAL */
    uint8_t u8motionCfdPresent;
    WJV4_STRU_MotionConfidenceSet strumotionCfd;        /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_FullPositionVector; /* 完整的参考轨迹点信息 */
typedef struct _v4TimeCountingDown
{
    WJV4_INT_TimeMark n32startTime;
    uint8_t u8minEndTimePresent;
    WJV4_INT_TimeMark n32minEndTime; /* OPTIONAL */
    uint8_t u8maxEndTimePresent;
    WJV4_INT_TimeMark n32maxEndTime; /* OPTIONAL */
    WJV4_INT_TimeMark n32likelyEndTime;
    uint8_t u8timeConfidencePresent;
    WJV4_INT_Confidence n32timeConfidence; /* OPTIONAL */
    uint8_t u8nextStartTimePresent;
    WJV4_INT_TimeMark n32nextStartTime; /* OPTIONAL */
    uint8_t u8nextDurationPresent;
    WJV4_INT_TimeMark n32nextDuration;                /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_TimeCountingDown; /* 用倒计时形式，描述一个信号灯相位状态的完整计时状态 */
typedef struct _v4UTCTiming
{
    WJV4_INT_TimeMark n32startUTCTime;
    uint8_t u8minEndUTCTimePresent;
    WJV4_INT_TimeMark n32minEndUTCTime; /* OPTIONAL */
    uint8_t u8maxEndUTCTimePresent;
    WJV4_INT_TimeMark n32maxEndUTCTime; /* OPTIONAL */
    WJV4_INT_TimeMark n32likelyEndUTCTime;
    uint8_t u8timeConfidencePresent;
    WJV4_INT_Confidence n32timeConfidence; /* OPTIONAL */
    uint8_t u8nextStartUTCTimePresent;
    WJV4_INT_TimeMark n32nextStartUTCTime; /* OPTIONAL */
    uint8_t u8nextEndUTCTimePresent;
    WJV4_INT_TimeMark n32nextEndUTCTime;       /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_UTCTiming; /* 一个信号灯相位状态的完整计时状态 */
typedef enum
{
    WJV4_TimeChangeDetailsDOWN = 0, /* 倒计时 */
    WJV4_TimeChangeDetailsUTC = 1,  /* 正数 */
} WJV4_ENUM_TimeChangeDetailsChoice;
typedef struct _v4TimeChangeDetails
{
    WJV4_ENUM_TimeChangeDetailsChoice enumTimeChangeDetails;
    union
    {
        WJV4_STRU_TimeCountingDown strucounting;
        WJV4_STRU_UTCTiming struutcTiming;
    } u;
} __attribute__((packed)) WJV4_STRU_TimeChangeDetails; /* 信号灯相位的计时状态 */
typedef struct _v4PhaseState
{
    WJV4_ENUM_LightState enumlight;
    uint8_t u8timingPresent;
    WJV4_STRU_TimeChangeDetails strutiming;     /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_PhaseState; /* 信号灯的一个相位状态 */
#define WJV4_MAX_LIST_PHASESTATE_LEN 16
#define WJV4_MIN_LIST_PHASESTATE_LEN 1
typedef struct _v4PhaseStateList
{
    uint8_t u8PhaseStateNum; /* 1 ~ 16 */
    WJV4_STRU_PhaseState struPhaseState[WJV4_MAX_LIST_PHASESTATE_LEN];
} __attribute__((packed)) WJV4_STRU_PhaseStateList; /* 一个信号灯的一个相位中的相位状态列表 */
typedef struct _v4Phase
{
    WJV4_INT_PhaseID n32id;
    WJV4_STRU_PhaseStateList struphaseStates;
} __attribute__((packed)) WJV4_STRU_Phase; /* 信号灯相位 */
#define WJV4_MAX_LIST_PHASE_LEN 16
#define WJV4_MIN_LIST_PHASE_LEN 1
typedef struct _v4PhaseList
{
    uint8_t u8PhaseNum; /* 1 ~ 16 */
    WJV4_STRU_Phase struPhase[WJV4_MAX_LIST_PHASE_LEN];
} __attribute__((packed)) WJV4_STRU_PhaseList; /* 一组信号灯包含的所有相位的列表 */
typedef struct _v4IntersectionState
{
    WJV4_STRU_NodeReferenceID struintersectionId;
    WJV4_BIT_IntersectionStatusObject strbitstatus;
    uint8_t u8moyPresent;
    WJV4_INT_MinuteOfTheYear n32moy; /* OPTIONAL */
    uint8_t u8timeStampPresent;
    WJV4_INT_DSecond n32timeStamp; /* OPTIONAL */
    uint8_t u8timeConfidencePresent;
    WJV4_ENUM_TimeConfidence enumtimeConfidence; /* OPTIONAL */
    WJV4_STRU_PhaseList struphases;
} __attribute__((packed)) WJV4_STRU_IntersectionState; /* 路口信号灯的属性和当前状态 */
#define WJV4_MAX_LIST_INTERSECTIONSTATE_LEN 32
#define WJV4_MIN_LIST_INTERSECTIONSTATE_LEN 1
typedef struct _v4IntersectionStateList
{
    uint8_t u8IntersectionStateNum; /* 1 ~ 32 */
    WJV4_STRU_IntersectionState struIntersectionState[WJV4_MAX_LIST_INTERSECTIONSTATE_LEN];
} __attribute__((packed)) WJV4_STRU_IntersectionStateList; /* 一个路口信号灯集合 */
typedef enum
{
    WJV4_LaneAttributesVehicle = 0,
    WJV4_LaneAttributesCrosswalk = 1,
    WJV4_LaneAttributesBike = 2,
    WJV4_LaneAttributesSidewalk = 3,
    WJV4_LaneAttributesBarrier = 4,
    WJV4_LaneAttributesStriping = 5,
    WJV4_LaneAttributesTrackedVehicle = 6,
    WJV4_LaneAttributesParking = 7
} WJV4_ENUM_LaneTypeAttributesChoice;
typedef struct _v4LaneTypeAttributes
{
    WJV4_ENUM_LaneTypeAttributesChoice enumLaneTypeAttributesChoice;
    union
    {
        WJV4_BIT_LaneAttributesVehicle strbitvehicle;
        WJV4_BIT_LaneAttributesCrosswalk strbitcrosswalk;
        WJV4_BIT_LaneAttributesBike strbitbikeLane;
        WJV4_BIT_LaneAttributesSidewalk strbitsidewalk;
        WJV4_BIT_LaneAttributesBarrier strbitmedian;
        WJV4_BIT_LaneAttributesStriping strbitstriping;
        WJV4_BIT_LaneAttributesTrackedVehicle strbittrackedVehicle;
        WJV4_BIT_LaneAttributesParking strbitparking;
    } u;
} __attribute__((packed)) WJV4_STRU_LaneTypeAttributes; /* 不同类别车道的属性集合 */
typedef struct _v4LaneAttributes
{
    uint8_t u8shareWithPresent;
    WJV4_BIT_LaneSharing strbitshareWith; /* OPTIONAL */
    WJV4_STRU_LaneTypeAttributes strulaneType;
} __attribute__((packed)) WJV4_STRU_LaneAttributes; /* 车道属性 */
typedef struct _v4PositionLL24B
{
    WJV4_INT_OffsetLLB12 n32lon;
    WJV4_INT_OffsetLLB12 n32lat;
} __attribute__((packed)) WJV4_STRU_PositionLL24B; /* 24比特相对经纬度位置 */
typedef struct _v4PositionLL28B
{
    WJV4_INT_OffsetLLB14 n32lon;
    WJV4_INT_OffsetLLB14 n32lat;
} __attribute__((packed)) WJV4_STRU_PositionLL28B; /* 28比特相对经纬度位置 */
typedef struct _v4PositionLL32B
{
    WJV4_INT_OffsetLLB16 n32lon;
    WJV4_INT_OffsetLLB16 n32lat;
} __attribute__((packed)) WJV4_STRU_PositionLL32B; /* 32比特相对经纬度位置 */
typedef struct _v4PositionLL36B
{
    WJV4_INT_OffsetLLB18 n32lon;
    WJV4_INT_OffsetLLB18 n32lat;
} __attribute__((packed)) WJV4_STRU_PositionLL36B; /* 36比特相对经纬度位置 */
typedef struct _v4PositionLL44B
{
    WJV4_INT_OffsetLLB22 n32lon;
    WJV4_INT_OffsetLLB22 n32lat;
} __attribute__((packed)) WJV4_STRU_PositionLL44B; /* 44比特相对经纬度位置 */
typedef struct _v4PositionLL48B
{
    WJV4_INT_OffsetLLB24 n32lon;
    WJV4_INT_OffsetLLB24 n32lat;
} __attribute__((packed)) WJV4_STRU_PositionLL48B; /* 48比特相对经纬度位置 */
typedef struct _v4PositionLLmD64b
{
    WJV4_INT_Longitude n32lon;
    WJV4_INT_Latitude n32lat;
} __attribute__((packed)) WJV4_STRU_PositionLLmD64b; /* 64比特经纬度位置 */
typedef enum
{
    WJV4_PositionLL24B = 1,
    WJV4_PositionLL28B,
    WJV4_PositionLL32B,
    WJV4_PositionLL36B,
    WJV4_PositionLL44B,
    WJV4_PositionLL48B,
    WJV4_PositionLLmD64b
} WJV4_ENUM_PositionOffsetLLChoice;
typedef struct _v4PositionOffsetLL
{
    WJV4_ENUM_PositionOffsetLLChoice enumPositionOffsetLLChoice;
    union
    {
        WJV4_STRU_PositionLL24B strupositionLL1;
        WJV4_STRU_PositionLL28B strupositionLL2;
        WJV4_STRU_PositionLL32B strupositionLL3;
        WJV4_STRU_PositionLL36B strupositionLL4;
        WJV4_STRU_PositionLL44B strupositionLL5;
        WJV4_STRU_PositionLL48B strupositionLL6;
        WJV4_STRU_PositionLLmD64b strupositionLatLon;
    } u;
} __attribute__((packed)) WJV4_STRU_PositionOffsetLL; /* 经纬度偏差 */
typedef enum
{
    WJV4_VertOffsetB07 = 1,
    WJV4_VertOffsetB08,
    WJV4_VertOffsetB09,
    WJV4_VertOffsetB10,
    WJV4_VertOffsetB11,
    WJV4_VertOffsetB12,
    WJV4_Elevation
} WJV4_ENUM_VerticalOffsetChoice;
typedef struct _v4VerticalOffset
{
    WJV4_ENUM_VerticalOffsetChoice enumVerticalOffsetChoice;
    union
    {
        WJV4_INT_VertOffsetB07 n32offset1;
        WJV4_INT_VertOffsetB08 n32offset2;
        WJV4_INT_VertOffsetB09 n32offset3;
        WJV4_INT_VertOffsetB10 n32offset4;
        WJV4_INT_VertOffsetB11 n32offset5;
        WJV4_INT_VertOffsetB12 n32offset6;
        WJV4_INT_Elevation n32elevation;
    } u;
} __attribute__((packed)) WJV4_STRU_VerticalOffset; /* 垂直方向位置偏差 */
typedef struct _v4PositionOffsetLLV
{
    WJV4_STRU_PositionOffsetLL struoffsetLL;
    uint8_t u8offsetVPresent;
    WJV4_STRU_VerticalOffset struoffsetV;              /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_PositionOffsetLLV; /* 三维的相对位置（相对经纬度和相对高程） */
typedef struct _v4RoadPoint
{
    WJV4_STRU_PositionOffsetLLV struposOffset;
} __attribute__((packed)) WJV4_STRU_RoadPoint; /* 完整道路上标记的一个位置点属性 */
#define WJV4_MAX_LIST_ROADPOINT_LEN 10         /* 协议规定 2 ～ 32 暂定 2～ 10 */
#define WJV4_MIN_LIST_ROADPOINT_LEN 2
typedef struct _v4PointList
{
    uint8_t u8RoadPointNum; /* 2 ~ 31 */
    WJV4_STRU_RoadPoint struRoadPoint[WJV4_MAX_LIST_ROADPOINT_LEN];
} __attribute__((packed)) WJV4_STRU_PointList; /* 一个有向路段上的中间位置点列表 */
typedef struct _v4RegulatorySpeedLimit
{
    WJV4_ENUM_SpeedLimitType enumtype;
    WJV4_INT_Speed n32speed;
} __attribute__((packed)) WJV4_STRU_RegulatorySpeedLimit; /* 限速属性 */
#define WJV4_MAX_LIST_REGULATORYSPEEDLIMITNUM_LEN 9
#define WJV4_MIN_LIST_REGULATORYSPEEDLIMITNUM_LEN 1
typedef struct _v4SpeedLimitList
{
    uint8_t u8RegulatorySpeedLimitNum; /* 1 ~ 9 */
    WJV4_STRU_RegulatorySpeedLimit struRegulatorySpeedLimit[WJV4_MAX_LIST_REGULATORYSPEEDLIMITNUM_LEN];
} __attribute__((packed)) WJV4_STRU_SpeedLimitList; /* 路段或车道的限速列表 */
typedef struct _v4Lane
{
    WJV4_INT_LaneID n32laneID;
    uint8_t u8laneWidthPresent;
    WJV4_INT_LaneWidth n32laneWidth; /* OPTIONAL */
    uint8_t u8laneAttributesPresent;
    WJV4_STRU_LaneAttributes strulaneAttributes; /* OPTIONAL */
    uint8_t u8maneuversPresent;
    WJV4_BIT_AllowedManeuvers strbitmaneuvers; /* OPTIONAL */
    uint8_t u8connectsToPresent;
    WJV4_STRU_ConnectsToList struConnectsToList; /* OPTIONAL */
    uint8_t u8speedLimitsPresent;
    WJV4_STRU_SpeedLimitList struspeedLimits; /* OPTIONAL */
    uint8_t u8pointsPresent;
    WJV4_STRU_PointList strupoints;       /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_Lane; /* 车道 */
#define WJV4_MAX_LIST_LANE_LEN 16         /* 协议规定 1 ～ 32 暂定 1～ 16 */
#define WJV4_MIN_LIST_LANE_LEN 1
typedef struct _v4LaneList
{
    uint8_t u8LaneNum; /* 1 ~ 32 */
    WJV4_STRU_Lane struLane[WJV4_MAX_LIST_LANE_LEN];
} __attribute__((packed)) WJV4_STRU_LaneList; /* 一个路段中包含的车道列表 */
typedef struct _v4Movement
{
    WJV4_STRU_NodeReferenceID struremoteIntersection;
    uint8_t u8phaseIdPresent;
    WJV4_INT_PhaseID n32phaseId;              /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_Movement; /* 道路与下游路段的连接关系 */
#define WJV4_MAX_LIST_MOVEMENT_LEN 8          /* 协议规定 1 ～ 32 暂定 1～ 8 */
#define WJV4_MIN_LIST_MOVEMENT_LEN 1
typedef struct _v4MovementList
{
    uint8_t u8MovementNum; /* 1 ~ 32 */
    WJV4_STRU_Movement struMovement[WJV4_MAX_LIST_MOVEMENT_LEN];
} __attribute__((packed)) WJV4_STRU_MovementList; /* 一条路段与下游路段的连接关系列表 */
typedef struct _v4Link
{
    uint8_t u8namePresent;
    WJV4_IA5_DescriptiveName stria5name; /* OPTIONAL */
    WJV4_STRU_NodeReferenceID struupstreamNodeId;
    uint8_t u8speedLimitsPresent;
    WJV4_STRU_SpeedLimitList struspeedLimits; /* OPTIONAL */
    uint8_t u8linkWidthPresent;
    WJV4_INT_LaneWidth n32linkWidth; /* OPTIONAL */
    uint8_t u8pointsPresent;
    WJV4_STRU_PointList strupoints; /* OPTIONAL */
    uint8_t u8MovementListPresent;
    WJV4_STRU_MovementList strumovements; /* OPTIONAL */
    WJV4_STRU_LaneList strulanes;
} __attribute__((packed)) WJV4_STRU_Link; /* 路段 */
#define WJV4_MAX_LIST_LINK_LEN 8          /* 协议规定 1 ～ 32 暂定 1～ 8 */
#define WJV4_MIN_LIST_LINK_LEN 1
typedef struct _v4LinkList
{
    uint8_t u8LinkNum; /* 1 ~ 32 */
    WJV4_STRU_Link struLink[WJV4_MAX_LIST_LINK_LEN];
} __attribute__((packed)) WJV4_STRU_LinkList; /* 路段列表 */
typedef struct _v4Node
{
    uint8_t u8namePresent;
    WJV4_IA5_DescriptiveName stria5name; /* OPTIONAL */
    WJV4_STRU_NodeReferenceID struid;
    WJV4_STRU_Position3D strurefPos;
    uint8_t u8inLinksPresent;
    WJV4_STRU_LinkList struinLinks;       /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_Node; /* 地图节点 */
#define WJV4_MAX_LIST_NODE_LEN 8          /* 协议规定 1 ～ 63 暂定 1～ 8 */
#define WJV4_MIN_LIST_NODE_LEN 1
typedef struct _v4NodeList
{
    uint8_t u8NodeNum; /* 1 ~ 63 */
    WJV4_STRU_Node struNode[WJV4_MAX_LIST_NODE_LEN];
} __attribute__((packed)) WJV4_STRU_NodeList; /* 地图节点列表 */
typedef struct _v4VehicleClassification
{
    WJV4_INT_BasicVehicleClass n32classification;
    uint8_t u8fuelTypePresent;
    WJV4_INT_FuelType n32fuelType;                         /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_VehicleClassification; /* 车辆的分类 */
typedef struct _v4VehicleSize
{
    WJV4_INT_VehicleWidth n32width;
    WJV4_INT_VehicleLength n32length;
    uint8_t u8heightPresent;
    WJV4_INT_VehicleHeight n32height;            /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_VehicleSize; /* 车辆尺寸大小 */
#define WJV4_MAX_PTCID_SIZE 65535
#define WJV4_MIN_PTCID_SIZE 0
typedef struct _v4ParticipantData
{
    WJV4_ENUM_ParticipantType enumptcType;
    uint32_t u32ptcId; /* 0 ~ 65535 0 is RSU itself */
    WJV4_ENUM_SourceType enumsource;
    uint8_t u8OCTidPresent;
#define WJV4_MAX_OCTID_SIZE 8
#define WJV4_MIN_OCTID_SIZE 0
    uint8_t u8OCTid[WJV4_MAX_OCTID_SIZE]; /* OPTIONAL */
    WJV4_INT_DSecond n32secMark;
    WJV4_STRU_PositionOffsetLLV strupos;
    WJV4_STRU_PositionConfidenceSet struposConfidence;
    uint8_t u8transmissionPresent;
    WJV4_ENUM_TransmissionState enumtransmission; /* OPTIONAL */
    WJV4_INT_Speed n32speed;
    WJV4_INT_Heading n32heading;
    uint8_t u8anglePresent;
    WJV4_INT_SteeringWheelAngle n32angle; /* OPTIONAL */
    uint8_t u8motionCfdPresent;
    WJV4_STRU_MotionConfidenceSet strumotionCfd; /* OPTIONAL */
    uint8_t u8accelSetPresent;
    WJV4_STRU_AccelerationSet4Way struaccelSet; /* OPTIONAL */
    WJV4_STRU_VehicleSize strusize;
    uint8_t u8vehicleClassPresent;
    WJV4_STRU_VehicleClassification struvehicleClass; /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_ParticipantData;  /* 交通参与者的基本安全信息 */
#define WJV4_MAX_LIST_PARTICIPANTDATA_LEN 16
#define WJV4_MIN_LIST_PARTICIPANTDATA_LEN 1
typedef struct _v4NodeListParticipantList
{
    uint8_t u8ParticipantDataNum; /* 1 ~ 16 */
    WJV4_STRU_ParticipantData struParticipantData[WJV4_MAX_LIST_PARTICIPANTDATA_LEN];
} __attribute__((packed)) WJV4_STRU_ParticipantList; /* 地图节点列表 */
typedef struct _v4PathHistoryPoint
{
    WJV4_STRU_PositionOffsetLLV strullvOffset;
    WJV4_INT_TimeOffset n32timeOffset;
    uint8_t u8speedPresent;
    WJV4_INT_Speed n32speed;
    uint8_t u8posAccuracyPresent;
    WJV4_STRU_PositionConfidenceSet struposAccuracy; /* OPTIONAL */
    uint8_t u8headingPresent;
    WJV4_INT_CoarseHeading n32heading;                /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_PathHistoryPoint; /* 车辆的历史轨迹点 */
#define WJV4_MAX_LIST_PATHHISTORYPOINT_LEN 23
#define WJV4_MIN_LIST_PATHHISTORYPOINT_LEN 1
typedef struct _v4PathHistoryPointList
{
    uint8_t u8PathHistoryPointNum; /* 1 ~ 23 */
    WJV4_STRU_PathHistoryPoint struPathHistoryPoint[WJV4_MAX_LIST_PATHHISTORYPOINT_LEN];
} __attribute__((packed)) WJV4_STRU_PathHistoryPointList; /* 车辆的历史轨迹 */
typedef struct _v4PathHistory
{
    uint8_t u8initialPositionPresent;
    WJV4_STRU_FullPositionVector struinitialPosition; /* OPTIONAL */
    uint8_t u8currGNSSstatusPresent;
    WJV4_BIT_GNSSstatus strbitcurrGNSSstatus; /* OPTIONAL */
    WJV4_STRU_PathHistoryPointList strucrumbData;
} __attribute__((packed)) WJV4_STRU_PathHistory; /* 车辆历史轨迹 */
#define WJV4_MAX_LIST_POSITIONOFFSETLLV_LEN 32
#define WJV4_MIN_LIST_POSITIONOFFSETLLV_LEN 1
typedef struct _v4PathPointList
{
    uint8_t u8PositionOffsetLLVNum; /* 1 ~32 */
    WJV4_STRU_PositionOffsetLLV struPositionOffsetLLV[WJV4_MAX_LIST_POSITIONOFFSETLLV_LEN];
} __attribute__((packed)) WJV4_STRU_PathPointList; /* 用有序位置点列的方式，定义一个有向的作用范围 */
typedef struct _v4PathPrediction
{
    WJV4_INT_RadiusOfCurvation n32radiusOfCurve;
    WJV4_INT_Confidence n32confidence;
} __attribute__((packed)) WJV4_STRU_PathPrediction; /* 车辆的预测线路 */
typedef struct _v4ReferenceLink
{
    WJV4_STRU_NodeReferenceID struupstreamNodeId;
    WJV4_STRU_NodeReferenceID strudownstreamNodeId;
    uint8_t u8referenceLanesPresent;
    WJV4_BIT_ReferenceLanes strbitreferenceLanes;  /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_ReferenceLink; /* 关联路段，用路段的上下游节点ID表示 */
#define WJV4_MAX_LIST_REFERENCELINK_LEN 16
#define WJV4_MIN_LIST_REFERENCELINK_LEN 1
typedef struct _v4ReferenceLinkList
{
    uint8_t u8ReferenceLinkNum; /* 1 ~ 16 */
    WJV4_STRU_ReferenceLink struReferenceLink[WJV4_MAX_LIST_REFERENCELINK_LEN];
} __attribute__((packed)) WJV4_STRU_ReferenceLinkList; /* 关联路段集合 */
typedef struct _v4ReferencePath
{
    WJV4_STRU_PathPointList struactivePath;
    WJV4_INT_Radius n32pathRadius;
} __attribute__((packed)) WJV4_STRU_ReferencePath; /* 道路交通事件和标志的关联路径 */
#define WJV4_MAX_LIST_REFERENCEPATH_LEN 8
#define WJV4_MIN_LIST_REFERENCEPATH_LEN 1
typedef struct _v4ReferencePathList
{
    uint8_t u8ReferencePathNum; /* 1 ～ 8 */
    WJV4_STRU_ReferencePath struReferencePath[WJV4_MAX_LIST_REFERENCEPATH_LEN];
} __attribute__((packed)) WJV4_STRU_ReferencePathList; /* 道路交通事件和标志的关联路径集合 */
typedef struct _v4RSITimeDetails
{
    uint8_t u8startTimePresent;
    WJV4_INT_MinuteOfTheYear n32startTime; /* OPTIONAL */
    uint8_t u8endTimePresent;
    WJV4_INT_MinuteOfTheYear n32endTime; /* OPTIONAL */
    uint8_t u8endTimeConfidencePresent;
    WJV4_ENUM_TimeConfidence enumendTimeConfidence; /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_RSITimeDetails; /* 道路交通事件和道路交通标志信息的生效时间属性 */
#define WJV4_MAX_RTEID_SIZE 255
#define WJV4_MIN_RTEID_SIZE 0
typedef struct _v4RTEData
{
    uint8_t u8rteId; /* 0 ~ 255 */
    WJV4_INT_EventType n32eventType;
    WJV4_ENUM_EventSource enumeventSource;
    uint8_t u8eventPosPresent;
    WJV4_STRU_PositionOffsetLLV strueventPos; /* OPTIONAL */
    uint8_t u8eventRadiusPresent;
    WJV4_INT_Radius n32eventRadius; /* OPTIONAL */
    uint8_t u8descriptionPresent;
    WJV4_STRU_Description strudescription; /* OPTIONAL */
    uint8_t u8timeDetailsPresent;
    WJV4_STRU_RSITimeDetails strutimeDetails; /* OPTIONAL */
    uint8_t u8priorityPresent;
    WJV4_IA5_RSIPriority stria5priority; /* OPTIONAL */
    uint8_t u8referencePathsPresent;
    WJV4_STRU_ReferencePathList strureferencePaths; /* OPTIONAL */
    uint8_t u8referenceLinksPresent;
    WJV4_STRU_ReferenceLinkList strureferenceLinks; /* OPTIONAL */
    uint8_t u8eventConfidencePresent;
    WJV4_INT_Confidence n32eventConfidence;  /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_RTEData; /* 道路交通事件信息 */
#define WJV4_MAX_LIST_RTEDATA_LEN 8
#define WJV4_MIN_LIST_RTEDATA_LEN 1
typedef struct _v4RTEList
{
    uint8_t u8RTEDataNum; /* 1 ~ 8 */
    WJV4_STRU_RTEData struRTEData[WJV4_MAX_LIST_RTEDATA_LEN];
} __attribute__((packed)) WJV4_STRU_RTEList; /* 道路交通事件集合 */
#define WJV4_MAX_RTSID_SIZE 255
#define WJV4_MIN_RTSID_SIZE 0
typedef struct _v4RTSData
{
    uint8_t u8rtsId; /* 0 ~ 255 */
    WJV4_INT_SignType n32signType;
    uint8_t u8signPosPresent;
    WJV4_STRU_PositionOffsetLLV strusignPos; /* OPTIONAL */
    uint8_t u8descriptionPresent;
    WJV4_STRU_Description strudescription; /* OPTIONAL */
    uint8_t u8timeDetailsPresent;
    WJV4_STRU_RSITimeDetails strutimeDetails; /* OPTIONAL */
    uint8_t u8priorityPresent;
    WJV4_IA5_RSIPriority stria5priority; /* OPTIONAL */
    uint8_t u8referencePathsPresent;
    WJV4_STRU_ReferencePathList strureferencePaths; /* OPTIONAL */
    uint8_t u8referenceLinksPresent;
    WJV4_STRU_ReferenceLinkList strureferenceLinks; /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_RTSData;
#define WJV4_MAX_LIST_RTSDATA_LEN 16
#define WJV4_MIN_LIST_RTSDATA_LEN 1
typedef struct _v4RTSList
{
    uint8_t u8RTSDataNum; /* 1 ~ 16 */
    WJV4_STRU_RTSData struRTSData[WJV4_MAX_LIST_RTSDATA_LEN];
} __attribute__((packed)) WJV4_STRU_RTSList; /* 道路交通标志集合 */
typedef struct _v4VehicleEmergencyExtensions
{
    uint8_t u8responseTypePresent;
    WJV4_ENUM_ResponseType enumresponseType; /* OPTIONAL */
    uint8_t u8sirenUsePresent;
    WJV4_ENUM_SirenInUse enumsirenUse; /* OPTIONAL */
    uint8_t u8lightsUsePresent;
    WJV4_ENUM_LightbarInUse enumlightsUse;                      /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_VehicleEmergencyExtensions; /* 紧急车辆或特种车辆的辅助信息集合 */
typedef struct _v4VehicleSafetyExtensions
{
    uint8_t u8eventsPresent;
    WJV4_BIT_VehicleEventFlags strbitevents; /* OPTIONAL */
    uint8_t u8pathHistoryPresent;
    WJV4_STRU_PathHistory strupathHistory; /* OPTIONAL */
    uint8_t u8pathPredictionPresent;
    WJV4_STRU_PathPrediction strupathPrediction; /* OPTIONAL */
    uint8_t u8lightsPresent;
    WJV4_BIT_ExteriorLights strbitlights;                    /* OPTIONAL */
} __attribute__((packed)) WJV4_STRU_VehicleSafetyExtensions; /* 车辆安全辅助信息集合 */
/****************************************************************************************/
/* 内部函数声明 */
/****************************************************************************************/
#endif /* 文件结束 */