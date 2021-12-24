/**
* @file         :wjvn4_uper_De.h
* @brief        :数据元素相关结构体义头文件
* @details      :主要包含数据元素的类型定义，数据元素中各元素的范围以及相关枚举值
* @author       :huangsai  any question please send mail to huangsai@wanji.net.cn
* @date         :2020-12-09
* @version      :V1.0
* @copyright    :Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：IMX6
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-09  <td>V1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
#ifndef __WJVN4_UPER_DE_H_
#define __WJVN4_UPER_DE_H_
/*********************************头文件包含********************************************/
#include <stdint.h>
/*********************************标准头文件********************************************/

/*********************************自定义头文件******************************************/

/****************************************************************************************/
/* 内部函数声明 */
#define WJVN4_PRESENT 0xA3
#define WJVN4_ABSENT 0xB4
/* 数据元素定义 */
#define WJVN4_MAX_ACCELERATION_SIZE 2001
#define WJVN4_MIN_ACCELERATION_SIZE -2000
#define WJVN4_INT_Acceleration int32_t /* 车辆加速度 分辨率为0.01m/s2，数值2001为无效数值 */
typedef union
{
#define WJVN4_LEN_BITSTR_ALLOWEDMANEUVERS 12
#define WJVN4_LEN_BYTE_ALLOWEDMANEUVERS 2
    uint8_t u8AllowedManeuvers[WJVN4_LEN_BYTE_ALLOWEDMANEUVERS];
    struct
    {
        uint16_t bit_maneuverStraightAllowed : 1;
        uint16_t bit_maneuverLeftAllowed : 1;
        uint16_t bit_maneuverRightAllowed : 1;
        uint16_t bit_maneuverUTurnAllowed : 1;
        uint16_t bit_maneuverLeftTurnOnRedAllowed : 1;
        uint16_t bit_maneuverRightTurnOnRedAllowed : 1;
        uint16_t bit_maneuverLaneChangeAllowed : 1;
        uint16_t bit_maneuverNoStoppingAllowed : 1;
        uint16_t bit_yieldAllwaysRequired : 1;
        uint16_t bit_goWithHalt : 1;
        uint16_t bit_caution : 1;
        uint16_t bit_reserved : 5;
    };
} WJVN4_BIT_AllowedManeuvers; /* 车道允许转向行为 */
typedef enum
{
    WJVN4_AntiLockBrakeStatusunavailable = 0,
    WJVN4_AntiLockBrakeStatusoff = 1,
    WJVN4_AntiLockBrakeStatuson = 2,
    WJVN4_AntiLockBrakeStatusengaged = 3,
} WJVN4_ENUM_AntiLockBrakeStatus; /* ABS状态 */
typedef enum
{
    WJVN4_AuxiliaryBrakeStatusunavailable = 0,
    WJVN4_AuxiliaryBrakeStatusoff = 1,
    WJVN4_AuxiliaryBrakeStatuson = 2,
    WJVN4_AuxiliaryBrakeStatusreserved = 3,
} WJVN4_ENUM_AuxiliaryBrakeStatus; /* 刹车辅助系统 */
typedef enum
{
    WJVN4_BasicVehicleClassunknownVehicleClass = 0,
    WJVN4_BasicVehicleClassspecialVehicleClass = 1,
    WJVN4_BasicVehicleClasspassengerVehicleTypeUnknown = 10,
    WJVN4_BasicVehicleClasspassengerVehicleTypeOther = 11,
    WJVN4_BasicVehicleClasslightTruckVehicleTypeUnknown = 20,
    WJVN4_BasicVehicleClasslightTruckVehicleTypeOther = 21,
    WJVN4_BasicVehicleClasstruckVehicleTypeUnknown = 25,
    WJVN4_BasicVehicleClasstruckVehicleTypeOther = 26,
    WJVN4_BasicVehicleClasstruckaxleCnt2 = 27,
    WJVN4_BasicVehicleClasstruckaxleCnt3 = 28,
    WJVN4_BasicVehicleClasstruckaxleCnt4 = 29,
    WJVN4_BasicVehicleClasstruckaxleCnt4Traile = 30,
    WJVN4_BasicVehicleClasstruckaxleCnt5Traile = 31,
    WJVN4_BasicVehicleClasstruckaxleCnt6Traile = 32,
    WJVN4_BasicVehicleClasstruckaxleCnt5MultiTrailer = 33,
    WJVN4_BasicVehicleClasstruckaxleCnt6MultiTrailer = 34,
    WJVN4_BasicVehicleClasstruckaxleCnt7MultiTrailer = 35,
    WJVN4_BasicVehicleClassmotorcycleTypeUnknown = 40,
    WJVN4_BasicVehicleClassmotorcycleTypeOther = 41,
    WJVN4_BasicVehicleClassmotorcycleCruiserStandard = 42,
    WJVN4_BasicVehicleClassmotorcycleSportUnclad = 43,
    WJVN4_BasicVehicleClassmotorcycleSportTouring = 44,
    WJVN4_BasicVehicleClassmotorcycleSuperSport = 45,
    WJVN4_BasicVehicleClassmotorcycleTouring = 46,
    WJVN4_BasicVehicleClassmotorcycleTrike = 47,
    WJVN4_BasicVehicleClassmotorcyclewPassengers = 48,
    WJVN4_BasicVehicleClasstransitTypeUnknown = 50,
    WJVN4_BasicVehicleClasstransitTypeOther = 51,
    WJVN4_BasicVehicleClasstransitBRT = 52,
    WJVN4_BasicVehicleClasstransitExpressBus = 53,
    WJVN4_BasicVehicleClasstransitLocalBus = 54,
    WJVN4_BasicVehicleClasstransitSchoolBus = 55,
    WJVN4_BasicVehicleClasstransitFixedGuideway = 56,
    WJVN4_BasicVehicleClasstransitParatransit = 57,
    WJVN4_BasicVehicleClasstransitParatransitAmbulance = 58,
    WJVN4_BasicVehicleClassemergencyTypeUnknown = 60,
    WJVN4_BasicVehicleClassemergencyTypeOther = 61,
    WJVN4_BasicVehicleClassemergencyFireLightVehicle = 62,
    WJVN4_BasicVehicleClassemergencyFireHeavyVehicle = 63,
    WJVN4_BasicVehicleClassemergencyFireParamedicVehicle = 64,
    WJVN4_BasicVehicleClassemergencyFireAmbulanceVehicle = 65,
    WJVN4_BasicVehicleClassemergencyPoliceLightVehicle = 66,
    WJVN4_BasicVehicleClassemergencyPoliceHeavyVehicle = 67,
    WJVN4_BasicVehicleClassemergencyOtherResponder = 68,
    WJVN4_BasicVehicleClassemergencyOtherAmbulance = 69,
    WJVN4_BasicVehicleClassotherTravelerTypeUnknown = 80,
    WJVN4_BasicVehicleClassotherTravelerTypeOther = 81,
    WJVN4_BasicVehicleClassotherTravelerPedestrian = 82,
    WJVN4_BasicVehicleClassotherTravelerVisuallyDisabled = 83,
    WJVN4_BasicVehicleClassotherTravelerPhysicallyDisabled = 84,
    WJVN4_BasicVehicleClassotherTravelerBicycle = 85,
    WJVN4_BasicVehicleClassotherTravelerVulnerableRoadworker = 86,
    WJVN4_BasicVehicleClassinfrastructureTypeUnknown = 90,
    WJVN4_BasicVehicleClassinfrastructureFixed = 91,
    WJVN4_BasicVehicleClassinfrastructureMovable = 92,
    WJVN4_BasicVehicleClassequippedCargoTrailer = 93,
} WJVN4_ENUM_BasicVehicleClass;
#define WJVN4_MAX_BASICVEHICLECLASS_SIZE 255
#define WJVN4_MIN_BASICVEHICLECLASS_SIZE 0
#define WJVN4_INT_BasicVehicleClass int32_t /* 车辆基本类型 */
typedef union
{
#define WJVN4_LEN_BITSTR_BRAFEAPPLIEDSTATUS 5
#define WJVN4_LEN_BYTE_BRAFEAPPLIEDSTATUS 1
    uint8_t u8BrakeAppliedStatus[WJVN4_LEN_BYTE_BRAFEAPPLIEDSTATUS];
    struct
    {
        uint8_t bit_unavailable : 1;
        uint8_t bit_leftFront : 1;
        uint8_t bit_leftRear : 1;
        uint8_t bit_rightFront : 1;
        uint8_t bit_rightRear : 1;
        uint8_t bit_reserved : 3;
    };
} WJVN4_BIT_BrakeAppliedStatus; /* 四轮分别的刹车状态 */
typedef enum
{
    WJVN4_BrakeBoostAppliedunavailable = 0,
    WJVN4_BrakeBoostAppliedoff = 1,
    WJVN4_BrakeBoostAppliedon = 2,
} WJVN4_ENUM_BrakeBoostApplied; /* 刹车辅助系统的状态 */
typedef enum
{
    WJVN4_BrakePedalStatusunavailable = 0,
    WJVN4_BrakePedalStatusoff = 1,
    WJVN4_BrakePedalStatuson = 2,
} WJVN4_ENUM_BrakePedalStatus; /* 刹车踏板状态 */
#define WJVN4_MAX_COARSEHEADING_SIZE 240
#define WJVN4_MIN_COARSEHEADING_SIZE 0
#define WJVN4_INT_CoarseHeading int32_t /* 粗粒度的车辆航向角 分辨率为1.5° */
#define WJVN4_MAX_CONFIDENCE_SIZE 200
#define WJVN4_MIN_CONFIDENCE_SIZE 0
#define WJVN4_INT_Confidence int32_t /* 置信度 分辨率为0.005 */
#define WJVN4_MAX_DDAY_SIZE 31
#define WJVN4_MIN_DDAY_SIZE 0
#define WJVN4_INT_DDay int32_t /* 1月中的日期 有效范围是1~31。0表示未知日期 */
#define WJVN4_MAX_IA5_DESCIPTIVENAME_LEN 63
#define WJVN4_MAX_DESCRIPTIVENAME_SIZE 127
#define WJVN4_MIN_DESCRIPTIVENAME_SIZE 0
typedef struct
{
    uint8_t u8DescriptiveNameNum;
    uint8_t u8DescriptiveName[WJVN4_MAX_IA5_DESCIPTIVENAME_LEN];
} WJVN4_IA5_DescriptiveName; /* 名称字符串类型 */
#define WJVN4_MAX_DHOUR_SIZE 31
#define WJVN4_MIN_DHOUR_SIZE 0
#define WJVN4_INT_DHour int32_t /* 一天中的小时时刻 24及以上表示未知或无效 */
#define WJVN4_MAX_DMINUTE_SIZE 60
#define WJVN4_MIN_DMINUTE_SIZE 0
#define WJVN4_INT_DMinute int32_t /* 1小时的分钟时刻 60表示未知分钟时刻 */
#define WJVN4_MAX_DMONTH_SIZE 12
#define WJVN4_MIN_DMONTH_SIZE 0
#define WJVN4_INT_DMonth int32_t /* 1年中的月份 0表示未知月份 */
#define WJVN4_MAX_DSECOND_SIZE 65535
#define WJVN4_MIN_DSECOND_SIZE 0
#define WJVN4_INT_DSecond int32_t /* 1分钟内的毫秒级时刻 分辨率为1毫秒，有效范围是0~59999。60000及以上表示未知 */
#define WJVN4_MAX_DTIMEOFFSET_SIZE 840
#define WJVN4_MIN_DTIMEOFFSET_SIZE -840
#define WJVN4_INT_DTimeOffset int32_t /* UTC时间的分钟差，用来表示时区。比UTC快为正，否则为负 */
#define WJVN4_MAX_DYEAR_SIZE 4095
#define WJVN4_MIN_DYEAR_SIZE 0
#define WJVN4_INT_DYear int32_t /* 公历年份 0代表未知年份 */
#define WJVN4_MAX_ELEVATION_SIZE 61439
#define WJVN4_MIN_ELEVATION_SIZE -4096
#define WJVN4_INT_Elevation int32_t /* 车辆海拔高程 分辨率为0.1米。数值-4096表示无效数值 */
typedef enum
{
    WJVN4_ElevationConfidenceunavailable = 0,
    WJVN4_ElevationConfidenceelev500_00 = 1,
    WJVN4_ElevationConfidenceelev200_00 = 2,
    WJVN4_ElevationConfidenceelev100_00 = 3,
    WJVN4_ElevationConfidenceelev050_00 = 4,
    WJVN4_ElevationConfidenceelev020_00 = 5,
    WJVN4_ElevationConfidenceelev010_00 = 6,
    WJVN4_ElevationConfidenceelev005_00 = 7,
    WJVN4_ElevationConfidenceelev002_00 = 8,
    WJVN4_ElevationConfidenceelev001_00 = 9,
    WJVN4_ElevationConfidenceelev000_50 = 10,
    WJVN4_ElevationConfidenceelev000_20 = 11,
    WJVN4_ElevationConfidenceelev000_10 = 12,
    WJVN4_ElevationConfidenceelev000_05 = 13,
    WJVN4_ElevationConfidenceelev000_02 = 14,
    WJVN4_ElevationConfidenceelev000_01 = 15
} WJVN4_ENUM_ElevationConfidence; /* 95%置信水平的车辆高程精度 */
typedef enum
{
    WJVN4_EventSourceunknown = 0,
    WJVN4_EventSourcepolice = 1,
    WJVN4_EventSourcegovernment = 2,
    WJVN4_EventSourcemeteorological = 3,
    WJVN4_EventSourceinternet = 4,
    WJVN4_EventSourcedetection = 5
} WJVN4_ENUM_EventSource; /* 道路交通事件的信息来源 */
#define WJVN4_MAX_EVENTTYPE_SIZE 65535
#define WJVN4_MIN_EVENTTYPE_SIZE 0
#define WJVN4_INT_EventType int32_t /* 道路交通事件类型 参考GB/T 29100-2012定义 */
typedef union
{
#define WJVN4_LEN_BITSTR_EXTERIORLIGHT 9
#define WJVN4_LEN_BYTE_EXTERIORLIGHT 2
    uint8_t u8ExteriorLights[WJVN4_LEN_BYTE_EXTERIORLIGHT];
    struct
    {
        uint16_t bit_lowBeamHeadlightsOn : 1;
        uint16_t bit_highBeamHeadlightsOn : 1;
        uint16_t bit_leftTurnSignalOn : 1;
        uint16_t bit_rightTurnSignalOn : 1;
        uint16_t bit_hazardSignalOn : 1;
        uint16_t bit_automaticLightControlOn : 1;
        uint16_t bit_daytimeRunningLightsOn : 1;
        uint16_t bit_fogLightOn : 1;
        uint16_t bit_parkingLightsOn : 1;
        uint16_t bit_reserved : 7;
    };
} WJVN4_BIT_ExteriorLights; /* 车身的灯光状态 */
typedef enum
{
    WJVN4_FuelTypeunknownFuel = 0,
    WJVN4_FuelTypegasoline = 1,
    WJVN4_FuelTypeethanol = 2,
    WJVN4_FuelTypediesel = 3,
    WJVN4_FuelTypeelectric = 4,
    WJVN4_FuelTypehybrid = 5,
    WJVN4_FuelTypehydrogen = 6,
    WJVN4_FuelTypenatGasLiquid = 7,
    WJVN4_FuelTypenatGasComp = 8,
    WJVN4_FuelTypepropane = 9,
} WJVN4_ENUM_FuelType;
#define WJVN4_MAX_FUELTYPE_SIZE 15
#define WJVN4_MIN_FUELTYPE_SIZE 0
#define WJVN4_INT_FuelType int32_t /* 车辆的燃料类型 */
typedef union
{
#define WJVN4_LEN_BITSTR_GNSSSTATUS 8
#define WJVN4_LEN_BYTE_GNSSSTATUS 1
    uint8_t u8GNSSstatus[WJVN4_LEN_BYTE_GNSSSTATUS];
    struct
    {
        uint8_t bit_unavailable : 1;
        uint8_t bit_isHealthy : 1;
        uint8_t bit_isMonitored : 1;
        uint8_t bit_baseStationType : 1;
        uint8_t bit_aPDOPofUnder5 : 1;
        uint8_t bit_inViewOfUnder5 : 1;
        uint8_t bit_localCorrectionsPresent : 1;
        uint8_t bit_networkCorrectionsPresent : 1;
    };
} WJVN4_BIT_GNSSstatus; /* GNSS系统工作状态 */
#define WJVN4_MAX_HEADING_SIZE 28800
#define WJVN4_MIN_HEADING_SIZE 0
#define WJVN4_INT_Heading int32_t /* 航向角 分辨率为0.0125° */
typedef enum
{
    WJVN4_HeadingConfidenceunavailable = 0,
    WJVN4_HeadingConfidenceprec10deg = 1,
    WJVN4_HeadingConfidenceprec05deg = 2,
    WJVN4_HeadingConfidenceprec01deg = 3,
    WJVN4_HeadingConfidenceprec0x1deg = 4,
    WJVN4_HeadingConfidenceprec0x05deg = 5,
    WJVN4_HeadingConfidenceprec0x01deg = 6,
    WJVN4_HeadingConfidenceprec0x0125deg = 7,
} WJVN4_ENUM_HeadingConfidence; /* 95%置信水平的航向精度 */
typedef union
{
#define WJVN4_LEN_BITSTR_INTERSECTIONSTATUSPBJECT 16
#define WJVN4_LEN_BYTE_INTERSECTIONSTATUSPBJECT 2
    uint8_t u8IntersectionStatusObject[WJVN4_LEN_BYTE_INTERSECTIONSTATUSPBJECT];
    struct
    {
        uint16_t bit_manualControlIsEnabled : 1;
        uint16_t bit_stopTimeIsActivated : 1;
        uint16_t bit_failureFlash : 1;
        uint16_t bit_preemptIsActive : 1;
        uint16_t bit_signalPriorityIsActive : 1;
        uint16_t bit_fixedTimeOperation : 1;
        uint16_t bit_trafficDependentOperation : 1;
        uint16_t bit_standbyOperation : 1;
        uint16_t bit_failureMode : 1;
        uint16_t bit_off : 1;
        uint16_t bit_recentMAPmessageUpdate : 1;
        uint16_t bit_recentChangeInMAPassignedLanesIDsUsed : 1;
        uint16_t bit_noValidMAPisAvailableAtThisTime : 1;
        uint16_t bit_noValidSPATisAvailableAtThisTime : 1;
        uint16_t bit_reserved : 2;
    };
} WJVN4_BIT_IntersectionStatusObject; /* 信号机的工作状态 */
typedef union
{
#define WJVN4_LEN_BITSTR_LANEATTRIBUTESBARRIER 16
#define WJVN4_LEN_BYTE_LANEATTRIBUTESBARRIER 2
    uint8_t u8LaneAttributesBarrier[WJVN4_LEN_BYTE_LANEATTRIBUTESBARRIER];
    struct
    {
        uint16_t bit_medianRevocableLane : 1;
        uint16_t bit_median : 1;
        uint16_t bit_whiteLineHashing : 1;
        uint16_t bit_stripedLines : 1;
        uint16_t bit_doubleStripedLines : 1;
        uint16_t bit_trafficCones : 1;
        uint16_t bit_constructionBarrier : 1;
        uint16_t bit_trafficChannels : 1;
        uint16_t bit_lowCurbs : 1;
        uint16_t bit_highCurbs : 1;
        uint16_t bit_reserved : 6;
    };
} WJVN4_BIT_LaneAttributesBarrier; /* 车道隔离的属性 */
typedef union
{
#define WJVN4_LEN_BITSTR_LANEATTRIBUTESBIKE 16
#define WJVN4_LEN_BYTE_LANEATTRIBUTESBIKE 2
    uint8_t u8LaneAttributesBike[WJVN4_LEN_BYTE_LANEATTRIBUTESBIKE];
    struct
    {
        uint16_t bit_bikeRevocableLane : 1;
        uint16_t bit_pedestrianUseAllowed : 1;
        uint16_t bit_isBikeFlyOverLane : 1;
        uint16_t bit_fixedCycleTime : 1;
        uint16_t bit_biDirectionalCycleTimes : 1;
        uint16_t bit_isolatedByBarrier : 1;
        uint16_t bit_unsignalizedSegmentsPresent : 1;
        uint16_t bit_reserved : 9;
    };
} WJVN4_BIT_LaneAttributesBike; /* 自行车道的属性定义 */
typedef union
{
#define WJVN4_LEN_BITSTR_LANEATTRIBUTESCROSSWALK 16
#define WJVN4_LEN_BYTE_LANEATTRIBUTESCROSSWALK 2
    uint8_t u8LaneAttributesCrosswalk[WJVN4_LEN_BYTE_LANEATTRIBUTESCROSSWALK];
    struct
    {
        uint16_t bit_crosswalkRevocableLane : 1;
        uint16_t bit_bicyleUseAllowed : 1;
        uint16_t bit_isXwalkFlyOverLane : 1;
        uint16_t bit_fixedCycleTime : 1;
        uint16_t bit_biDirectionalCycleTimes : 1;
        uint16_t bit_hasPushToWalkButton : 1;
        uint16_t bit_audioSupport : 1;
        uint16_t bit_rfSignalRequestPresent : 1;
        uint16_t bit_unsignalizedSegmentsPresent : 1;
        uint16_t bit_reserved : 7;
    };
} WJVN4_BIT_LaneAttributesCrosswalk; /* 人行横道的属性定义 */
typedef union
{
#define WJVN4_LEN_BITSTR_LANEATTRIBUTESPARKING 16
#define WJVN4_LEN_BYTE_LANEATTRIBUTESPARKING 2
    uint8_t u8LaneAttributesParking[WJVN4_LEN_BYTE_LANEATTRIBUTESPARKING];
    struct
    {
        uint16_t bit_parkingRevocableLane : 1;
        uint16_t bit_parallelParkingInUse : 1;
        uint16_t bit_headInParkingInUse : 1;
        uint16_t bit_doNotParkZone : 1;
        uint16_t bit_parkingForBusUse : 1;
        uint16_t bit_parkingForTaxiUse : 1;
        uint16_t bit_noPublicParkingUse : 1;
        uint16_t bit_reserved : 9;
    };
} WJVN4_BIT_LaneAttributesParking; /* 停车车道的属性定义 */
typedef union
{
#define WJVN4_LEN_BITSTR_LANEATTRIBUTESSIDEWALK 16
#define WJVN4_LEN_BYTE_LANEATTRIBUTESSIDEWALK 2
    uint8_t u8LaneAttributesSidewalk[WJVN4_LEN_BYTE_LANEATTRIBUTESSIDEWALK];
    struct
    {
        uint16_t bit_sidewalkRevocableLane : 1;
        uint16_t bit_bicyleUseAllowed : 1;
        uint16_t bit_isSidewalkFlyOverLane : 1;
        uint16_t bit_walkBikes : 1;
        uint16_t bit_reserved : 12;
    };
} WJVN4_BIT_LaneAttributesSidewalk; /* 人行道的属性 */
typedef union
{
#define WJVN4_LEN_BITSTR_LANEATTRIBUTESSTRIPING 16
#define WJVN4_LEN_BYTE_LANEATTRIBUTESSTRIPING 2
    uint8_t u8LaneAttributesStriping[WJVN4_LEN_BYTE_LANEATTRIBUTESSTRIPING];
    struct
    {
        uint16_t bit_stripeToConnectingLanesRevocableLane : 1;
        uint16_t bit_stripeDrawOnLeft : 1;
        uint16_t bit_stripeDrawOnRight : 1;
        uint16_t bit_stripeToConnectingLanesLeft : 1;
        uint16_t bit_stripeToConnectingLanesRight : 1;
        uint16_t bit_stripeToConnectingLanesAhead : 1;
        uint16_t bit_reserved : 10;
    };
} WJVN4_BIT_LaneAttributesStriping; /* 标线车道的属性 */
typedef union
{
#define WJVN4_LEN_BITSTR_LANEATTRIBUTESTRACKEDVEHICLE 16
#define WJVN4_LEN_BYTE_LANEATTRIBUTESTRACKEDVEHICLE 2
    uint8_t u8LaneAttributesTrackedVehicle[WJVN4_LEN_BYTE_LANEATTRIBUTESTRACKEDVEHICLE];
    struct
    {
        uint16_t bit_specRevocableLane : 1;
        uint16_t bit_speccommuterRailRoadTrack : 1;
        uint16_t bit_speclightRailRoadTrack : 1;
        uint16_t bit_specheavyRailRoadTrack : 1;
        uint16_t bit_specotherRailType : 1;
        uint16_t bit_reserved : 11;
    };
} WJVN4_BIT_LaneAttributesTrackedVehicle; /* 轨道车辆车道的属性 */
typedef union
{
#define WJVN4_LEN_BITSTR_LANEATTRIBUTESVEHICLE 8
#define WJVN4_LEN_BYTE_LANEATTRIBUTESVEHICLE 1
    uint8_t u8LaneAttributesVehicle[WJVN4_LEN_BYTE_LANEATTRIBUTESVEHICLE];
    struct
    {
        uint8_t bit_isVehicleRevocableLane : 1;
        uint8_t bit_isVehicleFlyOverLane : 1;
        uint8_t bit_hovLaneUseOnly : 1;
        uint8_t bit_restrictedToBusUse : 1;
        uint8_t bit_restrictedToTaxiUse : 1;
        uint8_t bit_restrictedFromPublicUse : 1;
        uint8_t bit_hasIRbeaconCoverage : 1;
        uint8_t bit_permissionOnRequest : 1;
    };
} WJVN4_BIT_LaneAttributesVehicle; /* 车辆行驶车道的属性 */
#define WJVN4_MAX_LANEID_SIZE 255
#define WJVN4_MIN_LANEID_SIZE 0
#define WJVN4_INT_LaneID int32_t /* 车道ID */
typedef union
{
#define WJVN4_LEN_BITSTR_LANESHARING 10
#define WJVN4_LEN_BYTE_LANESHARING 2
    uint8_t u8LaneSharing[WJVN4_LEN_BYTE_LANESHARING];
    struct
    {
        uint16_t bit_overlappingLaneDescriptionProvided : 1;
        uint16_t bit_multipleLanesTreatedAsOneLane : 1;
        uint16_t bit_otherNonMotorizedTrafficTypes : 1;
        uint16_t bit_individualMotorizedVehicleTraffic : 1;
        uint16_t bit_busVehicleTraffic : 1;
        uint16_t bit_taxiVehicleTraffic : 1;
        uint16_t bit_pedestriansTraffic : 1;
        uint16_t bit_cyclistVehicleTraffic : 1;
        uint16_t bit_trackedVehicleTraffic : 1;
        uint16_t bit_pedestrianTraffic : 1;
        uint16_t bit_reserved : 6;
    };
} WJVN4_BIT_LaneSharing; /* 车道被共享的情况 */
#define WJVN4_MAX_LANEWIDTH_SIZE 32767
#define WJVN4_MIN_LANEWIDTH_SIZE 0
#define WJVN4_INT_LaneWidth int32_t /* 车道宽度 */
#define WJVN4_MAX_LATITUDE_SIZE 900000001
#define WJVN4_MIN_LATITUDE_SIZE -900000000
#define WJVN4_INT_Latitude int32_t /* 分辨率1e-7° 纬度数值，北纬为正，南纬为负 */
typedef enum
{
    WJVN4_LightbarInUseunavailable = 0,
    WJVN4_LightbarInUsenotInUse = 1,
    WJVN4_LightbarInUseinUse = 2,
    WJVN4_LightbarInUseyellowCautionLights = 3,
    WJVN4_LightbarInUseschooldBusLights = 4,
    WJVN4_LightbarInUsearrowSignsActive = 5,
    WJVN4_LightbarInUseslowMovingVehicle = 6,
    WJVN4_LightbarInUsefreqStops = 7,
} WJVN4_ENUM_LightbarInUse; /* 紧急车辆或特殊车辆的警示灯或外置专用显示设备的工作状态 */
typedef enum
{
    WJVN4_LightStateunavailable = 0,
    WJVN4_LightStatedark = 1,
    WJVN4_LightStateflashingred = 2,
    WJVN4_LightStatered = 3,
    WJVN4_LightStateflashinggreen = 4,
    WJVN4_LightStatepermissivegreen = 5,
    WJVN4_LightStateprotectedgreen = 6,
    WJVN4_LightStateyellow = 7,
    WJVN4_LightStateflashingyellow = 8,
} WJVN4_ENUM_LightState; /* 信号灯相位的灯色状态 */
#define WJVN4_MAX_LONGITUDE_SIZE 1800000001
#define WJVN4_MIN_LONGITUDE_SIZE -1799999999
#define WJVN4_INT_Longitude int32_t /* 经度数值。东经为正，西经为负 分辨率为1e-7° */
#define WJVN4_MAX_MINUTEOFTHEYEAR_SIZE 527040
#define WJVN4_MIN_MINUTEOFTHEYEAR_SIZE 0
#define WJVN4_INT_MinuteOfTheYear int32_t /* 当前年份已经过去的总分钟数 分辨率为1分钟 */
#define WJVN4_MAX_MSGCOUNT_SIZE 127
#define WJVN4_MIN_MSGCOUNT_SIZE 0
#define WJVN4_INT_MsgCount int32_t /* 消息编号 */
#define WJVN4_MAX_NODEID_SIZE 65535
#define WJVN4_MIN_NODEID_SIZE 0
#define WJVN4_INT_NodeID int32_t /* 节点ID 数值0~255预留为测试使用 */
#define WJVN4_MAX_OFFSETLLB12_SIZE 2047
#define WJVN4_MIN_OFFSETLLB12_SIZE -2048
#define WJVN4_INT_OffsetLLB12 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 12比特 */
#define WJVN4_MAX_OFFSETLLB14_SIZE 8191
#define WJVN4_MIN_OFFSETLLB14_SIZE -8192
#define WJVN4_INT_OffsetLLB14 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 14比特 */
#define WJVN4_MAX_OFFSETLLB16_SIZE 32767
#define WJVN4_MIN_OFFSETLLB16_SIZE -32768
#define WJVN4_INT_OffsetLLB16 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 16比特 */
#define WJVN4_MAX_OFFSETLLB18_SIZE 131071
#define WJVN4_MIN_OFFSETLLB18_SIZE -131072
#define WJVN4_INT_OffsetLLB18 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 18比特 */
#define WJVN4_MAX_OFFSETLLB22_SIZE 2097151
#define WJVN4_MIN_OFFSETLLB22_SIZE -2097152
#define WJVN4_INT_OffsetLLB22 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 22比特 */
#define WJVN4_MAX_OFFSETLLB24_SIZE 8388607
#define WJVN4_MIN_OFFSETLLB24_SIZE -8388608
#define WJVN4_INT_OffsetLLB24 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 24比特 */
typedef enum
{
    WJVN4_ParticipantTypeunknow = 0,
    WJVN4_ParticipantTypemotor = 1,
    WJVN4_ParticipantTypenonmotor = 2,
    WJVN4_ParticipantTypepedestrian = 3,
    WJVN4_ParticipantTypersu = 4,
} WJVN4_ENUM_ParticipantType; /* 交通参与者类型 */
#define WJVN4_MAX_PHASEID_SIZE 255
#define WJVN4_MIN_PHASEID_SIZE 0
#define WJVN4_INT_PhaseID int32_t /* 信号灯相位ID */
typedef enum
{
    WJVN4_PositionConfidenceunavailable = 0,
    WJVN4_PositionConfidencea500m = 1,
    WJVN4_PositionConfidencea200m = 2,
    WJVN4_PositionConfidencea100m = 3,
    WJVN4_PositionConfidencea50m = 4,
    WJVN4_PositionConfidencea20m = 5,
    WJVN4_PositionConfidencea10m = 6,
    WJVN4_PositionConfidencea5m = 7,
    WJVN4_PositionConfidencea2m = 8,
    WJVN4_PositionConfidencea1m = 9,
    WJVN4_PositionConfidencea50cm = 10,
    WJVN4_PositionConfidencea20cm = 11,
    WJVN4_PositionConfidencea10cm = 12,
    WJVN4_PositionConfidencea5cm = 13,
    WJVN4_PositionConfidencea2cm = 14,
    WJVN4_PositionConfidencea1cm = 15,
} WJVN4_ENUM_PositionConfidence; /* 95%置信水平的车辆位置精度 */
#define WJVN4_MAX_RADIUS_SIZE 65535
#define WJVN4_MIN_RADIUS_SIZE 0
#define WJVN4_INT_Radius int32_t /* 绝对值半径大小 */
#define WJVN4_MAX_RADIUSOFCURVATURE_SIZE 32767
#define WJVN4_MIN_RADIUSOFCURVATURE_SIZE -32767
#define WJVN4_INT_RadiusOfCurvation int32_t /* 车辆预测自身前方行驶轨迹的曲率半径 */
typedef union
{
#define WJVN4_LEN_BITSTR_REFERENCELANES 16
#define WJVN4_LEN_BYTE_REFERENCELANES 2
    uint8_t u8ReferenceLanes[WJVN4_LEN_BYTE_REFERENCELANES];
    struct
    {
        uint16_t bit_reserved : 1;
        uint16_t bit_lane1 : 1;
        uint16_t bit_lane2 : 1;
        uint16_t bit_lane3 : 1;
        uint16_t bit_lane4 : 1;
        uint16_t bit_lane5 : 1;
        uint16_t bit_lane6 : 1;
        uint16_t bit_lane7 : 1;
        uint16_t bit_lane8 : 1;
        uint16_t bit_lane9 : 1;
        uint16_t bit_lane10 : 1;
        uint16_t bit_lane11 : 1;
        uint16_t bit_lane12 : 1;
        uint16_t bit_lane13 : 1;
        uint16_t bit_lane14 : 1;
        uint16_t bit_lane15 : 1;
    };
} WJVN4_BIT_ReferenceLanes; /* 路段中指定的关联车道 */
typedef enum
{
    WJVN4_ResponseTypenotInUseOrNotEquipped = 0,
    WJVN4_ResponseTypeemergency = 1,
    WJVN4_ResponseTypenonEmergency = 2,
    WJVN4_ResponseTypepursuit = 3,
    WJVN4_ResponseTypestationary = 4,
    WJVN4_ResponseTypeslowMoving = 5,
    WJVN4_ResponseTypestopAndGoMovement = 6
} WJVN4_ENUM_ResponseType; /* 紧急车辆或特殊车辆当前的行驶状态或驾驶行为 */
#define WJVN4_MAX_IA5_RSIPRIORITY_LEN 1
typedef struct
{
    uint8_t u8RSIPriorityNum; /* 0 代表不存在 */
    uint8_t u8RSIPriority[WJVN4_MAX_IA5_RSIPRIORITY_LEN];
} WJVN4_IA5_RSIPriority; /* 数值长度占8位，其中低五位为0，为无效位，高三位为有效数据位 */
#define WJVN4_MAX_ROADREGULATORID_SIZE 65535
#define WJVN4_MIN_ROADREGULATORID_SIZE 0
#define WJVN4_INT_RoadRegulatorID int32_t /* 地图中各个划分区域的ID号,数值0仅用于测试 */
#define WJVN4_MAX_SEMIMAJORAXISACCURACY_SIZE 255
#define WJVN4_MIN_SEMIMAJORAXISACCURACY_SIZE 0
#define WJVN4_INT_SemiMajorAxisAccuracy int32_t /* 用椭圆模型表示的GNSS系统精度中半长轴的大小,分辨率为0.05米 */
#define WJVN4_MAX_SEMIMAJORAXISORIENTATION_SIZE 65535
#define WJVN4_MIN_SEMIMAJORAXISORIENTATION_SIZE 0
#define WJVN4_INT_SemiMajorAxisOrientation int32_t /* 正北方向顺时针到最近半长轴的夹角大小,分辨率为0.0054932479度 */
#define WJVN4_MAX_SEMIMINORAXISACCURACY_SIZE 255
#define WJVN4_MIN_SEMIMINORAXISACCURACY_SIZE 0
#define WJVN4_INT_SemiMinorAxisAccuracy int32_t /* 用椭圆模型表示的GNSS系统精度中半短轴的大小,分辨率0.05 */
#define WJVN4_MAX_SIGNTYPE_SIZE 65535
#define WJVN4_MIN_SIGNTYPE_SIZE 0
#define WJVN4_INT_SignType int32_t /* 道路交通标志的类型 */
typedef enum
{
    WJVN4_SirenInUseunavailable = 0,
    WJVN4_SirenInUsenotInUse = 1,
    WJVN4_SirenInUseinUse = 2,
    WJVN4_SirenInUsereserved = 3,
} WJVN4_ENUM_SirenInUse; /* 紧急车辆或特殊车辆的警笛或任何专用发声装置的状态 */
typedef enum
{
    WJVN4_SourceTypeunknown = 0,
    WJVN4_SourceTypeselfinfo = 1,
    WJVN4_SourceTypev2x = 2,
    WJVN4_SourceTypevideo = 3,
    WJVN4_SourceTypemicrowaveRadar = 4,
    WJVN4_SourceTypeloop = 5,
    WJVN4_SourceTypelidar = 6,
    WJVN4_SourceTypeintegrated = 7,
} WJVN4_ENUM_SourceType; /* 交通参与者数据的来源 */
#define WJVN4_MAX_SPEED_SIZE 8191
#define WJVN4_MIN_SPEED_SIZE 0
#define WJVN4_INT_Speed int32_t /* 速度分辨率为0.02m/s。数值8191表示无效数值 */
typedef enum
{
    WJVN4_SpeedConfidenceunavailable = 0,
    WJVN4_SpeedConfidenceprec100ms = 1,
    WJVN4_SpeedConfidenceprec10ms = 2,
    WJVN4_SpeedConfidenceprec5ms = 3,
    WJVN4_SpeedConfidenceprec1ms = 4,
    WJVN4_SpeedConfidenceprec01ms = 5,
    WJVN4_SpeedConfidenceprec005ms = 6,
    WJVN4_SpeedConfidenceprec001ms = 7,
} WJVN4_ENUM_SpeedConfidence; /* 95%置信水平的速度精度 */
typedef enum
{
    WJVN4_SpeedLimitTypeunknown = 0,
    WJVN4_SpeedLimitTypemaxSpeedInSchoolZone = 1,
    WJVN4_SpeedLimitTypemaxSpeedInSchoolZoneWhenChildrenArePresent = 2,
    WJVN4_SpeedLimitTypemaxSpeedInConstructionZone = 3,
    WJVN4_SpeedLimitTypevehicleMinSpeed = 4,
    WJVN4_SpeedLimitTypevehicleMaxSpeed = 5,
    WJVN4_SpeedLimitTypetruckMinSpeed = 6,
    WJVN4_SpeedLimitTypetruckMaxSpeed = 7,
    WJVN4_SpeedLimitTypetruckNightMaxSpeed = 9,
    WJVN4_SpeedLimitTypevehiclesWithTrailersMinSpeed = 10,
    WJVN4_SpeedLimitTypevehiclesWithTrailersMaxSpeed = 11,
    WJVN4_SpeedLimitTypevehiclesWithTrailersNightMaxSpeed = 12,
} WJVN4_ENUM_SpeedLimitType; /* 限速类型，指示给出的限速大小对应的参考类型 */
typedef enum
{
    WJVN4_StabilityControlStatusunavailable = 0,
    WJVN4_StabilityControlStatusoff = 1,
    WJVN4_StabilityControlStatuson = 2,
    WJVN4_StabilityControlStatusengaged = 3,
} WJVN4_ENUM_StabilityControlStatus; /* 车辆动态稳定控制系统状态 */
#define WJVN4_MAX_STEERINGWHEELANGLE_SIZE 127
#define WJVN4_MIN_STEERINGWHEELANGLE_SIZE -126
#define WJVN4_INT_SteeringWheelAngle int32_t /* 车辆转向轮角度。向右为正，向左为负 */
typedef enum
{
    WJVN4_SteeringWheelAngleConfidenceunavailable = 0,
    WJVN4_SteeringWheelAngleConfidenceprec2deg = 1,
    WJVN4_SteeringWheelAngleConfidenceprec1deg = 2,
    WJVN4_SteeringWheelAngleConfidenceprec002deg = 3,
} WJVN4_ENUM_SteeringWheelAngleConfidence; /* 95%置信水平的车辆转向轮角度精度 */
typedef enum
{
    WJVN4_TimeConfidenceunavailable = 0,
    WJVN4_TimeConfidencetime100000 = 1,
    WJVN4_TimeConfidencetime050000 = 2,
    WJVN4_TimeConfidencetime020000 = 3,
    WJVN4_TimeConfidencetime010000 = 4,
    WJVN4_TimeConfidencetime002000 = 5,
    WJVN4_TimeConfidencetime001000 = 6,
    WJVN4_TimeConfidencetime000500 = 7,
    WJVN4_TimeConfidencetime000200 = 8,
    WJVN4_TimeConfidencetime000100 = 9,
    WJVN4_TimeConfidencetime000050 = 10,
    WJVN4_TimeConfidencetime000020 = 11,
    WJVN4_TimeConfidencetime000010 = 12,
    WJVN4_TimeConfidencetime000005 = 13,
    WJVN4_TimeConfidencetime000002 = 14,
    WJVN4_TimeConfidencetime000001 = 15,
    WJVN4_TimeConfidencetime0000005 = 16,
    WJVN4_TimeConfidencetime0000002 = 17,
    WJVN4_TimeConfidencetime0000001 = 18,
    WJVN4_TimeConfidencetime00000005 = 19,
    WJVN4_TimeConfidencetime00000002 = 20,
    WJVN4_TimeConfidencetime00000001 = 21,
    WJVN4_TimeConfidencetime000000005 = 22,
    WJVN4_TimeConfidencetime000000002 = 23,
    WJVN4_TimeConfidencetime000000001 = 24,
    WJVN4_TimeConfidencetime0000000005 = 25,
    WJVN4_TimeConfidencetime0000000002 = 26,
    WJVN4_TimeConfidencetime0000000001 = 27,
    WJVN4_TimeConfidencetime00000000005 = 28,
    WJVN4_TimeConfidencetime00000000002 = 29,
    WJVN4_TimeConfidencetime00000000001 = 30,
    WJVN4_TimeConfidencetime000000000005 = 31,
    WJVN4_TimeConfidencetime000000000002 = 32,
    WJVN4_TimeConfidencetime000000000001 = 33,
    WJVN4_TimeConfidencetime0000000000005 = 34,
    WJVN4_TimeConfidencetime0000000000002 = 35,
    WJVN4_TimeConfidencetime0000000000001 = 36,
    WJVN4_TimeConfidencetime00000000000005 = 37,
    WJVN4_TimeConfidencetime00000000000002 = 38,
    WJVN4_TimeConfidencetime00000000000001 = 39,
} WJVN4_ENUM_TimeConfidence; /* 95%置信水平的时间精度 */
#define WJVN4_MAX_TIMEMARK_SIZE 36001
#define WJVN4_MIN_TIMEMARK_SIZE 0
#define WJVN4_INT_TimeMark int32_t /* 一小时中的时间 分辨率为0.1秒。有效范围是0~35999 */
#define WJVN4_MAX_TIMEOFFSET_SIZE 65535
#define WJVN4_MIN_TIMEOFFSET_SIZE 1
#define WJVN4_INT_TimeOffset int32_t /* 10毫秒为单位 描述时刻（较早）相对于参考时间点（较晚）的偏差 */
typedef enum
{
    WJVN4_TractionControlStatusunavailable = 0,
    WJVN4_TractionControlStatusoff = 1,
    WJVN4_TractionControlStatuson = 2,
    WJVN4_TractionControlStatusengaged = 3,
} WJVN4_ENUM_TractionControlStatus; /* 牵引力控制系统实时状态 */
typedef enum
{
    WJVN4_TransmissionStateneutral = 0,
    WJVN4_TransmissionStatepark = 1,
    WJVN4_TransmissionStateforwardGears = 2,
    WJVN4_TransmissionStatereverseGears = 3,
    WJVN4_TransmissionStatereserved1 = 4,
    WJVN4_TransmissionStatereserved2 = 5,
    WJVN4_TransmissionStatereserved3 = 6,
    WJVN4_TransmissionStateunavailable = 7,
} WJVN4_ENUM_TransmissionState; /* 车辆档位状态 */
typedef union
{
#define WJVN4_LEN_BITSTR_VEHICLEEVENTFLAGS 13
#define WJVN4_LEN_BYTE_VEHICLEEVENTFLAGS 2
    uint8_t u8VehicleEventFlags[WJVN4_LEN_BYTE_VEHICLEEVENTFLAGS];
    struct
    {
        uint16_t bit_eventHazardLights : 1;
        uint16_t bit_eventStopLineViolation : 1;
        uint16_t bit_eventABSactivated : 1;
        uint16_t bit_eventTractionControlLoss : 1;
        uint16_t bit_eventStabilityControlactivated : 1;
        uint16_t bit_eventHazardousMaterials : 1;
        uint16_t bit_eventReserved1 : 1;
        uint16_t bit_eventHardBraking : 1;
        uint16_t bit_eventLightsChanged : 1;
        uint16_t bit_eventWipersChanged : 1;
        uint16_t bit_eventFlatTire : 1;
        uint16_t bit_eventDisabledVehicle : 1;
        uint16_t bit_eventAirBagDeployment : 1;
    };
} WJVN4_BIT_VehicleEventFlags;
#define WJVN4_MAX_VEHICLEHEIGHT_SIZE 127
#define WJVN4_MIN_VEHICLEHEIGHT_SIZE 0
#define WJVN4_INT_VehicleHeight int32_t /* 车辆车身高度 分辨率为5cm 数值0表示无效数据 */
#define WJVN4_MAX_VEHICLELENGTH_SIZE 4095
#define WJVN4_MIN_VEHICLELENGTH_SIZE 0
#define WJVN4_INT_VehicleLength int32_t /* 车辆车身长度 分辨率为1cm 数值0表示无效数据 */
#define WJVN4_MAX_VEHICLEWIDTH_SIZE 1023
#define WJVN4_MIN_VEHICLEWIDTH_SIZE 0
#define WJVN4_INT_VehicleWidth int32_t /* 车辆车身宽度 分辨率为1cm 数值0表示无效数据 */
#define WJVN4_MAX_VERTICALACCELERATION_SIZE 127
#define WJVN4_MIN_VERTICALACCELERATION_SIZE -127
#define WJVN4_INT_VerticalAcceleration int32_t /* Z轴方向的加速度大小 分辨率为0.02G */
#define WJVN4_MAX_VERTOFFSETB07_SIZE 63
#define WJVN4_MIN_VERTOFFSETB07_SIZE -64
#define WJVN4_INT_VertOffsetB07 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJVN4_MAX_VERTOFFSETB08_SIZE 127
#define WJVN4_MIN_VERTOFFSETB08_SIZE -128
#define WJVN4_INT_VertOffsetB08 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJVN4_MAX_VERTOFFSETB09_SIZE 255
#define WJVN4_MIN_VERTOFFSETB09_SIZE -256
#define WJVN4_INT_VertOffsetB09 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJVN4_MAX_VERTOFFSETB10_SIZE 511
#define WJVN4_MIN_VERTOFFSETB10_SIZE -512
#define WJVN4_INT_VertOffsetB10 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJVN4_MAX_VERTOFFSETB11_SIZE 1023
#define WJVN4_MIN_VERTOFFSETB11_SIZE -1024
#define WJVN4_INT_VertOffsetB11 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJVN4_MAX_VERTOFFSETB12_SIZE 2047
#define WJVN4_MIN_VERTOFFSETB12_SIZE -2048
#define WJVN4_INT_VertOffsetB12 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJVN4_MAX_YAWRATE_SIZE 32767
#define WJVN4_MIN_YAWRATE_SIZE -32767
#define WJVN4_INT_YawRate int32_t /* 车辆横摆角速度 分辨率为0.01°/s  */
/****************************************************************************************/
#endif /* 文件结束 */