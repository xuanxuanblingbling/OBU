/**
* @file         :wjv2_uper_De.h
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
#ifndef __WJV2_UPER_DE_H_
#define __WJV2_UPER_DE_H_
/*********************************头文件包含********************************************/
#include <stdint.h>
/*********************************标准头文件********************************************/

/*********************************自定义头文件******************************************/

/****************************************************************************************/
/* 内部函数声明 */
#define WJV2_PRESENT 0xA3
#define WJV2_ABSENT 0xB4
/* 数据元素定义 */
#define WJV2_MAX_ACCELERATION_SIZE 2001
#define WJV2_MIN_ACCELERATION_SIZE -2000
#define WJV2_INT_Acceleration int32_t /* 车辆加速度 分辨率为0.01m/s2，数值2001为无效数值 */
typedef union
{
#define WJV2_LEN_BITSTR_ALLOWEDMANEUVERS 12
#define WJV2_LEN_BYTE_ALLOWEDMANEUVERS 2
    uint8_t u8AllowedManeuvers[WJV2_LEN_BYTE_ALLOWEDMANEUVERS];
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
}__attribute__ ((packed))  WJV2_BIT_AllowedManeuvers; /* 车道允许转向行为 */
typedef enum
{
    WJV2_AntiLockBrakeStatusunavailable = 0,
    WJV2_AntiLockBrakeStatusoff = 1,
    WJV2_AntiLockBrakeStatuson = 2,
    WJV2_AntiLockBrakeStatusengaged = 3,
}__attribute__ ((packed))  WJV2_ENUM_AntiLockBrakeStatus; /* ABS状态 */
typedef enum
{
    WJV2_AuxiliaryBrakeStatusunavailable = 0,
    WJV2_AuxiliaryBrakeStatusoff = 1,
    WJV2_AuxiliaryBrakeStatuson = 2,
    WJV2_AuxiliaryBrakeStatusreserved = 3,
}__attribute__ ((packed))  WJV2_ENUM_AuxiliaryBrakeStatus; /* 刹车辅助系统 */
typedef enum
{
    WJV2_BasicVehicleClassunknownVehicleClass = 0,
    WJV2_BasicVehicleClassspecialVehicleClass = 1,
    WJV2_BasicVehicleClasspassengerVehicleTypeUnknown = 10,
    WJV2_BasicVehicleClasspassengerVehicleTypeOther = 11,
    WJV2_BasicVehicleClasslightTruckVehicleTypeUnknown = 20,
    WJV2_BasicVehicleClasslightTruckVehicleTypeOther = 21,
    WJV2_BasicVehicleClasstruckVehicleTypeUnknown = 25,
    WJV2_BasicVehicleClasstruckVehicleTypeOther = 26,
    WJV2_BasicVehicleClasstruckaxleCnt2 = 27,
    WJV2_BasicVehicleClasstruckaxleCnt3 = 28,
    WJV2_BasicVehicleClasstruckaxleCnt4 = 29,
    WJV2_BasicVehicleClasstruckaxleCnt4Traile = 30,
    WJV2_BasicVehicleClasstruckaxleCnt5Traile = 31,
    WJV2_BasicVehicleClasstruckaxleCnt6Traile = 32,
    WJV2_BasicVehicleClasstruckaxleCnt5MultiTrailer = 33,
    WJV2_BasicVehicleClasstruckaxleCnt6MultiTrailer = 34,
    WJV2_BasicVehicleClasstruckaxleCnt7MultiTrailer = 35,
    WJV2_BasicVehicleClassmotorcycleTypeUnknown = 40,
    WJV2_BasicVehicleClassmotorcycleTypeOther = 41,
    WJV2_BasicVehicleClassmotorcycleCruiserStandard = 42,
    WJV2_BasicVehicleClassmotorcycleSportUnclad = 43,
    WJV2_BasicVehicleClassmotorcycleSportTouring = 44,
    WJV2_BasicVehicleClassmotorcycleSuperSport = 45,
    WJV2_BasicVehicleClassmotorcycleTouring = 46,
    WJV2_BasicVehicleClassmotorcycleTrike = 47,
    WJV2_BasicVehicleClassmotorcyclewPassengers = 48,
    WJV2_BasicVehicleClasstransitTypeUnknown = 50,
    WJV2_BasicVehicleClasstransitTypeOther = 51,
    WJV2_BasicVehicleClasstransitBRT = 52,
    WJV2_BasicVehicleClasstransitExpressBus = 53,
    WJV2_BasicVehicleClasstransitLocalBus = 54,
    WJV2_BasicVehicleClasstransitSchoolBus = 55,
    WJV2_BasicVehicleClasstransitFixedGuideway = 56,
    WJV2_BasicVehicleClasstransitParatransit = 57,
    WJV2_BasicVehicleClasstransitParatransitAmbulance = 58,
    WJV2_BasicVehicleClassemergencyTypeUnknown = 60,
    WJV2_BasicVehicleClassemergencyTypeOther = 61,
    WJV2_BasicVehicleClassemergencyFireLightVehicle = 62,
    WJV2_BasicVehicleClassemergencyFireHeavyVehicle = 63,
    WJV2_BasicVehicleClassemergencyFireParamedicVehicle = 64,
    WJV2_BasicVehicleClassemergencyFireAmbulanceVehicle = 65,
    WJV2_BasicVehicleClassemergencyPoliceLightVehicle = 66,
    WJV2_BasicVehicleClassemergencyPoliceHeavyVehicle = 67,
    WJV2_BasicVehicleClassemergencyOtherResponder = 68,
    WJV2_BasicVehicleClassemergencyOtherAmbulance = 69,
    WJV2_BasicVehicleClassotherTravelerTypeUnknown = 80,
    WJV2_BasicVehicleClassotherTravelerTypeOther = 81,
    WJV2_BasicVehicleClassotherTravelerPedestrian = 82,
    WJV2_BasicVehicleClassotherTravelerVisuallyDisabled = 83,
    WJV2_BasicVehicleClassotherTravelerPhysicallyDisabled = 84,
    WJV2_BasicVehicleClassotherTravelerBicycle = 85,
    WJV2_BasicVehicleClassotherTravelerVulnerableRoadworker = 86,
    WJV2_BasicVehicleClassinfrastructureTypeUnknown = 90,
    WJV2_BasicVehicleClassinfrastructureFixed = 91,
    WJV2_BasicVehicleClassinfrastructureMovable = 92,
    WJV2_BasicVehicleClassequippedCargoTrailer = 93,
}__attribute__ ((packed))  WJV2_ENUM_BasicVehicleClass;
#define WJV2_MAX_BASICVEHICLECLASS_SIZE 255
#define WJV2_MIN_BASICVEHICLECLASS_SIZE 0
#define WJV2_INT_BasicVehicleClass int32_t /* 车辆基本类型 */
typedef union
{
#define WJV2_LEN_BITSTR_BRAFEAPPLIEDSTATUS 5
#define WJV2_LEN_BYTE_BRAFEAPPLIEDSTATUS 1
    uint8_t u8BrakeAppliedStatus[WJV2_LEN_BYTE_BRAFEAPPLIEDSTATUS];
    struct
    {
        uint8_t bit_unavailable : 1;
        uint8_t bit_leftFront : 1;
        uint8_t bit_leftRear : 1;
        uint8_t bit_rightFront : 1;
        uint8_t bit_rightRear : 1;
        uint8_t bit_reserved : 3;
    };
}__attribute__ ((packed))  WJV2_BIT_BrakeAppliedStatus; /* 四轮分别的刹车状态 */
typedef enum
{
    WJV2_BrakeBoostAppliedunavailable = 0,
    WJV2_BrakeBoostAppliedoff = 1,
    WJV2_BrakeBoostAppliedon = 2,
}__attribute__ ((packed))  WJV2_ENUM_BrakeBoostApplied; /* 刹车辅助系统的状态 */
typedef enum
{
    WJV2_BrakePedalStatusunavailable = 0,
    WJV2_BrakePedalStatusoff = 1,
    WJV2_BrakePedalStatuson = 2,
}__attribute__ ((packed))  WJV2_ENUM_BrakePedalStatus; /* 刹车踏板状态 */
#define WJV2_MAX_COARSEHEADING_SIZE 240
#define WJV2_MIN_COARSEHEADING_SIZE 0
#define WJV2_INT_CoarseHeading int32_t /* 粗粒度的车辆航向角 分辨率为1.5° */
#define WJV2_MAX_CONFIDENCE_SIZE 200
#define WJV2_MIN_CONFIDENCE_SIZE 0
#define WJV2_INT_Confidence int32_t /* 置信度 分辨率为0.005 */
#define WJV2_MAX_DDAY_SIZE 31
#define WJV2_MIN_DDAY_SIZE 0
#define WJV2_INT_DDay int32_t /* 1月中的日期 有效范围是1~31。0表示未知日期 */
#define WJV2_MAX_IA5_DESCIPTIVENAME_LEN 63
#define WJV2_MAX_DESCRIPTIVENAME_SIZE 127
#define WJV2_MIN_DESCRIPTIVENAME_SIZE 0
typedef struct
{
    uint8_t u8DescriptiveNameNum;
    uint8_t u8DescriptiveName[WJV2_MAX_IA5_DESCIPTIVENAME_LEN];
}__attribute__ ((packed))  WJV2_IA5_DescriptiveName; /* 名称字符串类型 */
#define WJV2_MAX_DHOUR_SIZE 31
#define WJV2_MIN_DHOUR_SIZE 0
#define WJV2_INT_DHour int32_t /* 一天中的小时时刻 24及以上表示未知或无效 */
#define WJV2_MAX_DMINUTE_SIZE 60
#define WJV2_MIN_DMINUTE_SIZE 0
#define WJV2_INT_DMinute int32_t /* 1小时的分钟时刻 60表示未知分钟时刻 */
#define WJV2_MAX_DMONTH_SIZE 12
#define WJV2_MIN_DMONTH_SIZE 0
#define WJV2_INT_DMonth int32_t /* 1年中的月份 0表示未知月份 */
#define WJV2_MAX_DSECOND_SIZE 65535
#define WJV2_MIN_DSECOND_SIZE 0
#define WJV2_INT_DSecond int32_t /* 1分钟内的毫秒级时刻 分辨率为1毫秒，有效范围是0~59999。60000及以上表示未知 */
#define WJV2_MAX_DTIMEOFFSET_SIZE 840
#define WJV2_MIN_DTIMEOFFSET_SIZE -840
#define WJV2_INT_DTimeOffset int32_t /* UTC时间的分钟差，用来表示时区。比UTC快为正，否则为负 */
#define WJV2_MAX_DYEAR_SIZE 4095
#define WJV2_MIN_DYEAR_SIZE 0
#define WJV2_INT_DYear int32_t /* 公历年份 0代表未知年份 */
#define WJV2_MAX_ELEVATION_SIZE 61439
#define WJV2_MIN_ELEVATION_SIZE -4096
#define WJV2_INT_Elevation int32_t /* 车辆海拔高程 分辨率为0.1米。数值-4096表示无效数值 */

//ExPAM
#define WJV2_INT_PARKINGLOTINFO_ID 65535
#define WJV2_INT_PARKINGLOTINFO_NUMBUER 65535
#define WJV2_INT_PARKINGLOTINFO_BUILDINGLAYER 256
typedef enum
{
    WJV2_ElevationConfidenceunavailable = 0,
    WJV2_ElevationConfidenceelev500_00 = 1,
    WJV2_ElevationConfidenceelev200_00 = 2,
    WJV2_ElevationConfidenceelev100_00 = 3,
    WJV2_ElevationConfidenceelev050_00 = 4,
    WJV2_ElevationConfidenceelev020_00 = 5,
    WJV2_ElevationConfidenceelev010_00 = 6,
    WJV2_ElevationConfidenceelev005_00 = 7,
    WJV2_ElevationConfidenceelev002_00 = 8,
    WJV2_ElevationConfidenceelev001_00 = 9,
    WJV2_ElevationConfidenceelev000_50 = 10,
    WJV2_ElevationConfidenceelev000_20 = 11,
    WJV2_ElevationConfidenceelev000_10 = 12,
    WJV2_ElevationConfidenceelev000_05 = 13,
    WJV2_ElevationConfidenceelev000_02 = 14,
    WJV2_ElevationConfidenceelev000_01 = 15
}__attribute__ ((packed))  WJV2_ENUM_ElevationConfidence; /* 95%置信水平的车辆高程精度 */
typedef enum
{
    WJV2_EventSourceunknown = 0,
    WJV2_EventSourcepolice = 1,
    WJV2_EventSourcegovernment = 2,
    WJV2_EventSourcemeteorological = 3,
    WJV2_EventSourceinternet = 4,
    WJV2_EventSourcedetection = 5
}__attribute__ ((packed))  WJV2_ENUM_EventSource; /* 道路交通事件的信息来源 */
#define WJV2_MAX_EVENTTYPE_SIZE 65535
#define WJV2_MIN_EVENTTYPE_SIZE 0
#define WJV2_INT_EventType int32_t /* 道路交通事件类型 参考GB/T 29100-2012定义 */
typedef union
{
#define WJV2_LEN_BITSTR_EXTERIORLIGHT 9
#define WJV2_LEN_BYTE_EXTERIORLIGHT 2
    uint8_t u8ExteriorLights[WJV2_LEN_BYTE_EXTERIORLIGHT];
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
}__attribute__ ((packed))  WJV2_BIT_ExteriorLights; /* 车身的灯光状态 */
typedef enum
{
    WJV2_FuelTypeunknownFuel = 0,
    WJV2_FuelTypegasoline = 1,
    WJV2_FuelTypeethanol = 2,
    WJV2_FuelTypediesel = 3,
    WJV2_FuelTypeelectric = 4,
    WJV2_FuelTypehybrid = 5,
    WJV2_FuelTypehydrogen = 6,
    WJV2_FuelTypenatGasLiquid = 7,
    WJV2_FuelTypenatGasComp = 8,
    WJV2_FuelTypepropane = 9,
}__attribute__ ((packed))  WJV2_ENUM_FuelType;
#define WJV2_MAX_FUELTYPE_SIZE 15
#define WJV2_MIN_FUELTYPE_SIZE 0
#define WJV2_INT_FuelType int32_t /* 车辆的燃料类型 */
typedef union
{
#define WJV2_LEN_BITSTR_GNSSSTATUS 8
#define WJV2_LEN_BYTE_GNSSSTATUS 1
    uint8_t u8GNSSstatus[WJV2_LEN_BYTE_GNSSSTATUS];
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
}__attribute__ ((packed))  WJV2_BIT_GNSSstatus; /* GNSS系统工作状态 */
#define WJV2_MAX_HEADING_SIZE 28800
#define WJV2_MIN_HEADING_SIZE 0
#define WJV2_INT_Heading int32_t /* 航向角 分辨率为0.0125° */
typedef enum
{
    WJV2_HeadingConfidenceunavailable = 0,
    WJV2_HeadingConfidenceprec10deg = 1,
    WJV2_HeadingConfidenceprec05deg = 2,
    WJV2_HeadingConfidenceprec01deg = 3,
    WJV2_HeadingConfidenceprec0x1deg = 4,
    WJV2_HeadingConfidenceprec0x05deg = 5,
    WJV2_HeadingConfidenceprec0x01deg = 6,
    WJV2_HeadingConfidenceprec0x0125deg = 7,
}__attribute__ ((packed))  WJV2_ENUM_HeadingConfidence; /* 95%置信水平的航向精度 */
typedef union
{
#define WJV2_LEN_BITSTR_INTERSECTIONSTATUSPBJECT 16
#define WJV2_LEN_BYTE_INTERSECTIONSTATUSPBJECT 2
    uint8_t u8IntersectionStatusObject[WJV2_LEN_BYTE_INTERSECTIONSTATUSPBJECT];
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
}__attribute__ ((packed))  WJV2_BIT_IntersectionStatusObject; /* 信号机的工作状态 */
typedef union
{
#define WJV2_LEN_BITSTR_LANEATTRIBUTESBARRIER 16
#define WJV2_LEN_BYTE_LANEATTRIBUTESBARRIER 2
    uint8_t u8LaneAttributesBarrier[WJV2_LEN_BYTE_LANEATTRIBUTESBARRIER];
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
}__attribute__ ((packed))  WJV2_BIT_LaneAttributesBarrier; /* 车道隔离的属性 */
typedef union
{
#define WJV2_LEN_BITSTR_LANEATTRIBUTESBIKE 16
#define WJV2_LEN_BYTE_LANEATTRIBUTESBIKE 2
    uint8_t u8LaneAttributesBike[WJV2_LEN_BYTE_LANEATTRIBUTESBIKE];
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
}__attribute__ ((packed))  WJV2_BIT_LaneAttributesBike; /* 自行车道的属性定义 */
typedef union
{
#define WJV2_LEN_BITSTR_LANEATTRIBUTESCROSSWALK 16
#define WJV2_LEN_BYTE_LANEATTRIBUTESCROSSWALK 2
    uint8_t u8LaneAttributesCrosswalk[WJV2_LEN_BYTE_LANEATTRIBUTESCROSSWALK];
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
}__attribute__ ((packed))  WJV2_BIT_LaneAttributesCrosswalk; /* 人行横道的属性定义 */
typedef union
{
#define WJV2_LEN_BITSTR_LANEATTRIBUTESPARKING 16
#define WJV2_LEN_BYTE_LANEATTRIBUTESPARKING 2
    uint8_t u8LaneAttributesParking[WJV2_LEN_BYTE_LANEATTRIBUTESPARKING];
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
}__attribute__ ((packed))  WJV2_BIT_LaneAttributesParking; /* 停车车道的属性定义 */
typedef union
{
#define WJV2_LEN_BITSTR_LANEATTRIBUTESSIDEWALK 16
#define WJV2_LEN_BYTE_LANEATTRIBUTESSIDEWALK 2
    uint8_t u8LaneAttributesSidewalk[WJV2_LEN_BYTE_LANEATTRIBUTESSIDEWALK];
    struct
    {
        uint16_t bit_sidewalkRevocableLane : 1;
        uint16_t bit_bicyleUseAllowed : 1;
        uint16_t bit_isSidewalkFlyOverLane : 1;
        uint16_t bit_walkBikes : 1;
        uint16_t bit_reserved : 12;
    };
}__attribute__ ((packed))  WJV2_BIT_LaneAttributesSidewalk; /* 人行道的属性 */
typedef union
{
#define WJV2_LEN_BITSTR_LANEATTRIBUTESSTRIPING 16
#define WJV2_LEN_BYTE_LANEATTRIBUTESSTRIPING 2
    uint8_t u8LaneAttributesStriping[WJV2_LEN_BYTE_LANEATTRIBUTESSTRIPING];
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
}__attribute__ ((packed))  WJV2_BIT_LaneAttributesStriping; /* 标线车道的属性 */
typedef union
{
#define WJV2_LEN_BITSTR_LANEATTRIBUTESTRACKEDVEHICLE 16
#define WJV2_LEN_BYTE_LANEATTRIBUTESTRACKEDVEHICLE 2
    uint8_t u8LaneAttributesTrackedVehicle[WJV2_LEN_BYTE_LANEATTRIBUTESTRACKEDVEHICLE];
    struct
    {
        uint16_t bit_specRevocableLane : 1;
        uint16_t bit_speccommuterRailRoadTrack : 1;
        uint16_t bit_speclightRailRoadTrack : 1;
        uint16_t bit_specheavyRailRoadTrack : 1;
        uint16_t bit_specotherRailType : 1;
        uint16_t bit_reserved : 11;
    };
}__attribute__ ((packed))  WJV2_BIT_LaneAttributesTrackedVehicle; /* 轨道车辆车道的属性 */
typedef union
{
#define WJV2_LEN_BITSTR_LANEATTRIBUTESVEHICLE 8
#define WJV2_LEN_BYTE_LANEATTRIBUTESVEHICLE 1
    uint8_t u8LaneAttributesVehicle[WJV2_LEN_BYTE_LANEATTRIBUTESVEHICLE];
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
}__attribute__ ((packed))  WJV2_BIT_LaneAttributesVehicle; /* 车辆行驶车道的属性 */
#define WJV2_MAX_LANEID_SIZE 255
#define WJV2_MIN_LANEID_SIZE 0
#define WJV2_INT_LaneID int32_t /* 车道ID */
typedef union
{
#define WJV2_LEN_BITSTR_LANESHARING 10
#define WJV2_LEN_BYTE_LANESHARING 2
    uint8_t u8LaneSharing[WJV2_LEN_BYTE_LANESHARING];
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
}__attribute__ ((packed))  WJV2_BIT_LaneSharing; /* 车道被共享的情况 */
#define WJV2_MAX_LANEWIDTH_SIZE 32767
#define WJV2_MIN_LANEWIDTH_SIZE 0
#define WJV2_INT_LaneWidth int32_t /* 车道宽度 */
#define WJV2_MAX_LATITUDE_SIZE 900000001
#define WJV2_MIN_LATITUDE_SIZE -900000000
#define WJV2_INT_Latitude int32_t /* 分辨率1e-7° 纬度数值，北纬为正，南纬为负 */
typedef enum
{
    WJV2_LightbarInUseunavailable = 0,
    WJV2_LightbarInUsenotInUse = 1,
    WJV2_LightbarInUseinUse = 2,
    WJV2_LightbarInUseyellowCautionLights = 3,
    WJV2_LightbarInUseschooldBusLights = 4,
    WJV2_LightbarInUsearrowSignsActive = 5,
    WJV2_LightbarInUseslowMovingVehicle = 6,
    WJV2_LightbarInUsefreqStops = 7,
}__attribute__ ((packed))  WJV2_ENUM_LightbarInUse; /* 紧急车辆或特殊车辆的警示灯或外置专用显示设备的工作状态 */
typedef enum
{
    WJV2_LightStateunavailable = 0,
    WJV2_LightStatedark = 1,
    WJV2_LightStateflashingred = 2,
    WJV2_LightStatered = 3,
    WJV2_LightStateflashinggreen = 4,
    WJV2_LightStatepermissivegreen = 5,
    WJV2_LightStateprotectedgreen = 6,
    WJV2_LightStateyellow = 7,
    WJV2_LightStateflashingyellow = 8,
}__attribute__ ((packed))  WJV2_ENUM_LightState; /* 信号灯相位的灯色状态 */
#define WJV2_MAX_LONGITUDE_SIZE 1800000001
#define WJV2_MIN_LONGITUDE_SIZE -1799999999
#define WJV2_INT_Longitude int32_t /* 经度数值。东经为正，西经为负 分辨率为1e-7° */
#define WJV2_MAX_MINUTEOFTHEYEAR_SIZE 527040
#define WJV2_MIN_MINUTEOFTHEYEAR_SIZE 0
#define WJV2_INT_MinuteOfTheYear int32_t /* 当前年份已经过去的总分钟数 分辨率为1分钟 */
#define WJV2_MAX_MSGCOUNT_SIZE 127
#define WJV2_MIN_MSGCOUNT_SIZE 0
#define WJV2_INT_MsgCount int32_t /* 消息编号 */
#define WJV2_MAX_NODEID_SIZE 65535
#define WJV2_MIN_NODEID_SIZE 0
#define WJV2_INT_NodeID int32_t /* 节点ID 数值0~255预留为测试使用 */
#define WJV2_MAX_OFFSETLLB12_SIZE 2047
#define WJV2_MIN_OFFSETLLB12_SIZE -2048
#define WJV2_INT_OffsetLLB12 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 12比特 */
#define WJV2_MAX_OFFSETLLB14_SIZE 8191
#define WJV2_MIN_OFFSETLLB14_SIZE -8192
#define WJV2_INT_OffsetLLB14 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 14比特 */
#define WJV2_MAX_OFFSETLLB16_SIZE 32767
#define WJV2_MIN_OFFSETLLB16_SIZE -32768
#define WJV2_INT_OffsetLLB16 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 16比特 */
#define WJV2_MAX_OFFSETLLB18_SIZE 131071
#define WJV2_MIN_OFFSETLLB18_SIZE -131072
#define WJV2_INT_OffsetLLB18 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 18比特 */
#define WJV2_MAX_OFFSETLLB22_SIZE 2097151
#define WJV2_MIN_OFFSETLLB22_SIZE -2097152
#define WJV2_INT_OffsetLLB22 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 22比特 */
#define WJV2_MAX_OFFSETLLB24_SIZE 8388607
#define WJV2_MIN_OFFSETLLB24_SIZE -8388608
#define WJV2_INT_OffsetLLB24 int32_t /* 当前位置点关于参考位置点的经纬度偏差 分辨率为1e-7° 24比特 */
typedef enum
{
    WJV2_ParticipantTypeunknow = 0,
    WJV2_ParticipantTypemotor = 1,
    WJV2_ParticipantTypenonmotor = 2,
    WJV2_ParticipantTypepedestrian = 3,
    WJV2_ParticipantTypersu = 4,
}__attribute__ ((packed))  WJV2_ENUM_ParticipantType; /* 交通参与者类型 */
#define WJV2_MAX_PHASEID_SIZE 255
#define WJV2_MIN_PHASEID_SIZE 0
#define WJV2_INT_PhaseID int32_t /* 信号灯相位ID */
typedef enum
{
    WJV2_PositionConfidenceunavailable = 0,
    WJV2_PositionConfidencea500m = 1,
    WJV2_PositionConfidencea200m = 2,
    WJV2_PositionConfidencea100m = 3,
    WJV2_PositionConfidencea50m = 4,
    WJV2_PositionConfidencea20m = 5,
    WJV2_PositionConfidencea10m = 6,
    WJV2_PositionConfidencea5m = 7,
    WJV2_PositionConfidencea2m = 8,
    WJV2_PositionConfidencea1m = 9,
    WJV2_PositionConfidencea50cm = 10,
    WJV2_PositionConfidencea20cm = 11,
    WJV2_PositionConfidencea10cm = 12,
    WJV2_PositionConfidencea5cm = 13,
    WJV2_PositionConfidencea2cm = 14,
    WJV2_PositionConfidencea1cm = 15,
}__attribute__ ((packed))  WJV2_ENUM_PositionConfidence; /* 95%置信水平的车辆位置精度 */
#define WJV2_MAX_RADIUS_SIZE 65535
#define WJV2_MIN_RADIUS_SIZE 0
#define WJV2_INT_Radius int32_t /* 绝对值半径大小 */
#define WJV2_MAX_RADIUSOFCURVATURE_SIZE 32767
#define WJV2_MIN_RADIUSOFCURVATURE_SIZE -32767
#define WJV2_INT_RadiusOfCurvation int32_t /* 车辆预测自身前方行驶轨迹的曲率半径 */
typedef union
{
#define WJV2_LEN_BITSTR_REFERENCELANES 16
#define WJV2_LEN_BYTE_REFERENCELANES 2
    uint8_t u8ReferenceLanes[WJV2_LEN_BYTE_REFERENCELANES];
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
}__attribute__ ((packed))  WJV2_BIT_ReferenceLanes; /* 路段中指定的关联车道 */
typedef enum
{
    WJV2_ResponseTypenotInUseOrNotEquipped = 0,
    WJV2_ResponseTypeemergency = 1,
    WJV2_ResponseTypenonEmergency = 2,
    WJV2_ResponseTypepursuit = 3,
    WJV2_ResponseTypestationary = 4,
    WJV2_ResponseTypeslowMoving = 5,
    WJV2_ResponseTypestopAndGoMovement = 6
}__attribute__ ((packed))  WJV2_ENUM_ResponseType; /* 紧急车辆或特殊车辆当前的行驶状态或驾驶行为 */
#define WJV2_MAX_IA5_RSIPRIORITY_LEN 1
typedef struct
{
    uint8_t u8RSIPriorityNum; /* 0 代表不存在 */
    uint8_t u8RSIPriority[WJV2_MAX_IA5_RSIPRIORITY_LEN];
}__attribute__ ((packed))  WJV2_IA5_RSIPriority; /* 数值长度占8位，其中低五位为0，为无效位，高三位为有效数据位 */
#define WJV2_MAX_ROADREGULATORID_SIZE 65535
#define WJV2_MIN_ROADREGULATORID_SIZE 0
#define WJV2_INT_RoadRegulatorID int32_t /* 地图中各个划分区域的ID号,数值0仅用于测试 */
#define WJV2_MAX_SEMIMAJORAXISACCURACY_SIZE 255
#define WJV2_MIN_SEMIMAJORAXISACCURACY_SIZE 0
#define WJV2_INT_SemiMajorAxisAccuracy int32_t /* 用椭圆模型表示的GNSS系统精度中半长轴的大小,分辨率为0.05米 */
#define WJV2_MAX_SEMIMAJORAXISORIENTATION_SIZE 65535
#define WJV2_MIN_SEMIMAJORAXISORIENTATION_SIZE 0
#define WJV2_INT_SemiMajorAxisOrientation int32_t /* 正北方向顺时针到最近半长轴的夹角大小,分辨率为0.0054932479度 */
#define WJV2_MAX_SEMIMINORAXISACCURACY_SIZE 255
#define WJV2_MIN_SEMIMINORAXISACCURACY_SIZE 0
#define WJV2_INT_SemiMinorAxisAccuracy int32_t /* 用椭圆模型表示的GNSS系统精度中半短轴的大小,分辨率0.05 */
#define WJV2_MAX_SIGNTYPE_SIZE 65535
#define WJV2_MIN_SIGNTYPE_SIZE 0
#define WJV2_INT_SignType int32_t /* 道路交通标志的类型 */
typedef enum
{
    WJV2_SirenInUseunavailable = 0,
    WJV2_SirenInUsenotInUse = 1,
    WJV2_SirenInUseinUse = 2,
    WJV2_SirenInUsereserved = 3,
}__attribute__ ((packed))  WJV2_ENUM_SirenInUse; /* 紧急车辆或特殊车辆的警笛或任何专用发声装置的状态 */
typedef enum
{
    WJV2_SourceTypeunknown = 0,
    WJV2_SourceTypeselfinfo = 1,
    WJV2_SourceTypev2x = 2,
    WJV2_SourceTypevideo = 3,
    WJV2_SourceTypemicrowaveRadar = 4,
    WJV2_SourceTypeloop = 5,
    WJV2_SourceTypelidar = 6,
    WJV2_SourceTypeintegrated = 7,
}__attribute__ ((packed))  WJV2_ENUM_SourceType; /* 交通参与者数据的来源 */
#define WJV2_MAX_SPEED_SIZE 8191
#define WJV2_MIN_SPEED_SIZE 0
#define WJV2_INT_Speed int32_t /* 速度分辨率为0.02m/s。数值8191表示无效数值 */
typedef enum
{
    WJV2_SpeedConfidenceunavailable = 0,
    WJV2_SpeedConfidenceprec100ms = 1,
    WJV2_SpeedConfidenceprec10ms = 2,
    WJV2_SpeedConfidenceprec5ms = 3,
    WJV2_SpeedConfidenceprec1ms = 4,
    WJV2_SpeedConfidenceprec01ms = 5,
    WJV2_SpeedConfidenceprec005ms = 6,
    WJV2_SpeedConfidenceprec001ms = 7,
}__attribute__ ((packed))  WJV2_ENUM_SpeedConfidence; /* 95%置信水平的速度精度 */
typedef enum
{
    WJV2_SpeedLimitTypeunknown = 0,
    WJV2_SpeedLimitTypemaxSpeedInSchoolZone = 1,
    WJV2_SpeedLimitTypemaxSpeedInSchoolZoneWhenChildrenArePresent = 2,
    WJV2_SpeedLimitTypemaxSpeedInConstructionZone = 3,
    WJV2_SpeedLimitTypevehicleMinSpeed = 4,
    WJV2_SpeedLimitTypevehicleMaxSpeed = 5,
    WJV2_SpeedLimitTypetruckMinSpeed = 6,
    WJV2_SpeedLimitTypetruckMaxSpeed = 7,
    WJV2_SpeedLimitTypetruckNightMaxSpeed = 9,
    WJV2_SpeedLimitTypevehiclesWithTrailersMinSpeed = 10,
    WJV2_SpeedLimitTypevehiclesWithTrailersMaxSpeed = 11,
    WJV2_SpeedLimitTypevehiclesWithTrailersNightMaxSpeed = 12,
}__attribute__ ((packed))  WJV2_ENUM_SpeedLimitType; /* 限速类型，指示给出的限速大小对应的参考类型 */
typedef enum
{
    WJV2_StabilityControlStatusunavailable = 0,
    WJV2_StabilityControlStatusoff = 1,
    WJV2_StabilityControlStatuson = 2,
    WJV2_StabilityControlStatusengaged = 3,
}__attribute__ ((packed))  WJV2_ENUM_StabilityControlStatus; /* 车辆动态稳定控制系统状态 */
#define WJV2_MAX_STEERINGWHEELANGLE_SIZE 127
#define WJV2_MIN_STEERINGWHEELANGLE_SIZE -126
#define WJV2_INT_SteeringWheelAngle int32_t /* 车辆转向轮角度。向右为正，向左为负 */
typedef enum
{
    WJV2_SteeringWheelAngleConfidenceunavailable = 0,
    WJV2_SteeringWheelAngleConfidenceprec2deg = 1,
    WJV2_SteeringWheelAngleConfidenceprec1deg = 2,
    WJV2_SteeringWheelAngleConfidenceprec002deg = 3,
}__attribute__ ((packed))  WJV2_ENUM_SteeringWheelAngleConfidence; /* 95%置信水平的车辆转向轮角度精度 */
typedef enum
{
    WJV2_TimeConfidenceunavailable = 0,
    WJV2_TimeConfidencetime100000 = 1,
    WJV2_TimeConfidencetime050000 = 2,
    WJV2_TimeConfidencetime020000 = 3,
    WJV2_TimeConfidencetime010000 = 4,
    WJV2_TimeConfidencetime002000 = 5,
    WJV2_TimeConfidencetime001000 = 6,
    WJV2_TimeConfidencetime000500 = 7,
    WJV2_TimeConfidencetime000200 = 8,
    WJV2_TimeConfidencetime000100 = 9,
    WJV2_TimeConfidencetime000050 = 10,
    WJV2_TimeConfidencetime000020 = 11,
    WJV2_TimeConfidencetime000010 = 12,
    WJV2_TimeConfidencetime000005 = 13,
    WJV2_TimeConfidencetime000002 = 14,
    WJV2_TimeConfidencetime000001 = 15,
    WJV2_TimeConfidencetime0000005 = 16,
    WJV2_TimeConfidencetime0000002 = 17,
    WJV2_TimeConfidencetime0000001 = 18,
    WJV2_TimeConfidencetime00000005 = 19,
    WJV2_TimeConfidencetime00000002 = 20,
    WJV2_TimeConfidencetime00000001 = 21,
    WJV2_TimeConfidencetime000000005 = 22,
    WJV2_TimeConfidencetime000000002 = 23,
    WJV2_TimeConfidencetime000000001 = 24,
    WJV2_TimeConfidencetime0000000005 = 25,
    WJV2_TimeConfidencetime0000000002 = 26,
    WJV2_TimeConfidencetime0000000001 = 27,
    WJV2_TimeConfidencetime00000000005 = 28,
    WJV2_TimeConfidencetime00000000002 = 29,
    WJV2_TimeConfidencetime00000000001 = 30,
    WJV2_TimeConfidencetime000000000005 = 31,
    WJV2_TimeConfidencetime000000000002 = 32,
    WJV2_TimeConfidencetime000000000001 = 33,
    WJV2_TimeConfidencetime0000000000005 = 34,
    WJV2_TimeConfidencetime0000000000002 = 35,
    WJV2_TimeConfidencetime0000000000001 = 36,
    WJV2_TimeConfidencetime00000000000005 = 37,
    WJV2_TimeConfidencetime00000000000002 = 38,
    WJV2_TimeConfidencetime00000000000001 = 39,
}__attribute__ ((packed))  WJV2_ENUM_TimeConfidence; /* 95%置信水平的时间精度 */
#define WJV2_MAX_TIMEMARK_SIZE 36001
#define WJV2_MIN_TIMEMARK_SIZE 0
#define WJV2_INT_TimeMark int32_t /* 一小时中的时间 分辨率为0.1秒。有效范围是0~35999 */
#define WJV2_MAX_TIMEOFFSET_SIZE 65535
#define WJV2_MIN_TIMEOFFSET_SIZE 1
#define WJV2_INT_TimeOffset int32_t /* 10毫秒为单位 描述时刻（较早）相对于参考时间点（较晚）的偏差 */
typedef enum
{
    WJV2_TractionControlStatusunavailable = 0,
    WJV2_TractionControlStatusoff = 1,
    WJV2_TractionControlStatuson = 2,
    WJV2_TractionControlStatusengaged = 3,
}__attribute__ ((packed))  WJV2_ENUM_TractionControlStatus; /* 牵引力控制系统实时状态 */
typedef enum
{
    WJV2_TransmissionStateneutral = 0,
    WJV2_TransmissionStatepark = 1,
    WJV2_TransmissionStateforwardGears = 2,
    WJV2_TransmissionStatereverseGears = 3,
    WJV2_TransmissionStatereserved1 = 4,
    WJV2_TransmissionStatereserved2 = 5,
    WJV2_TransmissionStatereserved3 = 6,
    WJV2_TransmissionStateunavailable = 7,
}__attribute__ ((packed))  WJV2_ENUM_TransmissionState; /* 车辆档位状态 */
typedef union
{
#define WJV2_LEN_BITSTR_VEHICLEEVENTFLAGS 12
#define WJV2_LEN_BYTE_VEHICLEEVENTFLAGS 2
    uint8_t u8VehicleEventFlags[WJV2_LEN_BYTE_VEHICLEEVENTFLAGS];
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
}__attribute__ ((packed))  WJV2_BIT_VehicleEventFlags;
#define WJV2_MAX_VEHICLEHEIGHT_SIZE 127
#define WJV2_MIN_VEHICLEHEIGHT_SIZE 0
#define WJV2_INT_VehicleHeight int32_t /* 车辆车身高度 分辨率为5cm 数值0表示无效数据 */
#define WJV2_MAX_VEHICLELENGTH_SIZE 4095
#define WJV2_MIN_VEHICLELENGTH_SIZE 0
#define WJV2_INT_VehicleLength int32_t /* 车辆车身长度 分辨率为1cm 数值0表示无效数据 */
#define WJV2_MAX_VEHICLEWIDTH_SIZE 1023
#define WJV2_MIN_VEHICLEWIDTH_SIZE 0
#define WJV2_INT_VehicleWidth int32_t /* 车辆车身宽度 分辨率为1cm 数值0表示无效数据 */
#define WJV2_MAX_VERTICALACCELERATION_SIZE 127
#define WJV2_MIN_VERTICALACCELERATION_SIZE -127
#define WJV2_INT_VerticalAcceleration int32_t /* Z轴方向的加速度大小 分辨率为0.02G */
#define WJV2_MAX_VERTOFFSETB07_SIZE 63
#define WJV2_MIN_VERTOFFSETB07_SIZE -64
#define WJV2_INT_VertOffsetB07 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJV2_MAX_VERTOFFSETB08_SIZE 127
#define WJV2_MIN_VERTOFFSETB08_SIZE -128
#define WJV2_INT_VertOffsetB08 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJV2_MAX_VERTOFFSETB09_SIZE 255
#define WJV2_MIN_VERTOFFSETB09_SIZE -256
#define WJV2_INT_VertOffsetB09 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJV2_MAX_VERTOFFSETB10_SIZE 511
#define WJV2_MIN_VERTOFFSETB10_SIZE -512
#define WJV2_INT_VertOffsetB10 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJV2_MAX_VERTOFFSETB11_SIZE 1023
#define WJV2_MIN_VERTOFFSETB11_SIZE -1024
#define WJV2_INT_VertOffsetB11 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJV2_MAX_VERTOFFSETB12_SIZE 2047
#define WJV2_MIN_VERTOFFSETB12_SIZE -2048
#define WJV2_INT_VertOffsetB12 int32_t /* 垂直方向（Z轴）关于参考位置点的偏差 分辨率为10厘米 */
#define WJV2_MAX_YAWRATE_SIZE 32767
#define WJV2_MIN_YAWRATE_SIZE -32767
#define WJV2_INT_YawRate int32_t /* 车辆横摆角速度 分辨率为0.01°/s  */
/****************************************************************************************/

/* 数据元素定义 */

typedef enum WJV2_AccConfidence
{
    WJV2_AccConfidence_unavailable = 0,
    WJV2_AccConfidence_prec100deg = 1,
    WJV2_AccConfidence_prec10deg = 2,
    WJV2_AccConfidence_prec5deg = 3,
    WJV2_AccConfidence_prec1deg = 4,
    WJV2_AccConfidence_prec0_1deg = 5,
    WJV2_AccConfidence_prec0_05deg = 6,
    WJV2_AccConfidence_prec0_01deg = 7
}__attribute__ ((packed))  WJV2_ENUM_AccConfidence;

typedef enum WJV2_AngularVConfidence
{
    WJV2_AngularVConfidence_unavailable = 0,
    WJV2_AngularVConfidence_prec100deg = 1,
    WJV2_AngularVConfidence_prec10deg = 2,
    WJV2_AngularVConfidence_prec5deg = 3,
    WJV2_AngularVConfidence_prec1deg = 4,
    WJV2_AngularVConfidence_prec0_1deg = 5,
    WJV2_AngularVConfidence_prec0_05deg = 6,
    WJV2_AngularVConfidence_prec0_01deg = 7
}__attribute__ ((packed))  WJV2_ENUM_AngularVConfidence;

typedef enum WJV2_AnimalPropelledType
{
    WJV2_AnimalPropelledType_unavailable = 0,
    WJV2_AnimalPropelledType_otherTypes = 1,
    WJV2_AnimalPropelledType_animalMounted = 2,
    WJV2_AnimalPropelledType_animalDrawnCarriage = 3
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_AnimalPropelledType;

typedef struct _ApduData
{
    uint8_t u8OCTidNum;
#define WJV2_MAX_OCTApduID_SIZE 127
    uint8_t u8OCTid[WJV2_MAX_OCTApduID_SIZE];
}__attribute__ ((packed))  WJV2_OCT_ApduData;

#define WJV2_MAX_LIST_APDULIST_LEN 127
#define WJV2_MIN_LIST_APDULIST_LEN 1
typedef struct _ApduList
{
    uint8_t u8ApduDataNum;
    WJV2_OCT_ApduData struApduData[WJV2_MAX_LIST_APDULIST_LEN];
}__attribute__ ((packed))  WJV2_STRU_ApduList;

typedef enum WJV2_Attachment
{
    WJV2_Attachment_unavailable = 0,
    WJV2_Attachment_stroller = 1,
    WJV2_Attachment_bicycleTrailer = 2,
    WJV2_Attachment_cart = 3,
    WJV2_Attachment_wheelchair = 4,
    WJV2_Attachment_otherWalkAssistAttachments = 5,
    WJV2_Attachment_pet = 6
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_Attachment;

typedef enum WJV2_AuxiliarySignDirection
{
    WJV2_AuxiliarySignDirection_straight = 1,
    WJV2_AuxiliarySignDirection_leftAndRight = 2,
    WJV2_AuxiliarySignDirection_right = 3,
    WJV2_AuxiliarySignDirection_left = 4,
    WJV2_AuxiliarySignDirection_leftFrontTurn = 5,
    WJV2_AuxiliarySignDirection_rightFronTurn = 6,
    WJV2_AuxiliarySignDirection_rightRearTurn = 7,
    WJV2_AuxiliarySignDirection_leftRearTurn = 8
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_AuxiliarySignDirection;

/* AuxiliarySignVehicleType */
typedef union
{
#define WJV2_LEN_BITSTR_AuxiliarySignVehicleType 5
#define WJV2_LEN_BYTE_AuxiliarySignVehicleType 1
    uint8_t u8AuxiliarySignVehicleType[WJV2_LEN_BYTE_AuxiliarySignVehicleType];
    struct
    {
        uint8_t bit_AuxiliarySignVehicleType_restrictedFromBus : 1;
        uint8_t bit_AuxiliarySignVehicleType_vehicle : 1;
        uint8_t bit_AuxiliarySignVehicleType_truck : 1;
        uint8_t bit_AuxiliarySignVehicleType_tractor : 1;
        uint8_t bit_AuxiliarySignVehicleType_private : 1;
        uint8_t bit_reserved : 3;
    };
}__attribute__ ((packed))  WJV2_BIT_AuxiliarySignVehicleType;

typedef enum WJV2_AVPType
{
    WJV2_AVPType_p0 = 0,
    WJV2_AVPType_p1 = 1,
    WJV2_AVPType_p2 = 2,
    WJV2_AVPType_p3 = 3,
    WJV2_AVPType_p4 = 4,
    WJV2_AVPType_p5 = 5
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_AVPType;

typedef enum WJV2_ChannelID
{
    WJV2_ChannelID_obu = 0,
    WJV2_ChannelID_esam = 1,
    WJV2_ChannelID_icc = 2,
    WJV2_ChannelID_hmi = 3,
    WJV2_ChannelID_beeper = 4
}__attribute__ ((packed))  WJV2_ENUM_ChannelID;

/* CoordinationInfo */
typedef union
{
#define WJV2_LEN_BITSTR_CoordinationInfo 8
#define WJV2_LEN_BYTE_CoordinationInfo 1
    uint8_t u8CoordinationInfo[WJV2_LEN_BYTE_CoordinationInfo];
    struct
    {
        uint8_t bit_CoordinationInfo_cooperativeLaneChanging : 1;
        uint8_t bit_CoordinationInfo_cooperativeVehMerging : 1;
        uint8_t bit_CoordinationInfo_laneChangingAtIntersection : 1;
        uint8_t bit_CoordinationInfo_no_signalIntersectionPassing : 1;
        uint8_t bit_CoordinationInfo_dynamicLaneManagement : 1;
        uint8_t bit_CoordinationInfo_laneReservation : 1;
        uint8_t bit_CoordinationInfo_laneRestriction : 1;
        uint8_t bit_CoordinationInfo_signalPriority : 1;
    };
}__attribute__ ((packed))  WJV2_BIT_CoordinationInfo;

typedef enum WJV2_DetectedPTCType
{
    WJV2_DetectedPTCType_unknown = 0,
    WJV2_DetectedPTCType_unknown_movable = 1,
    WJV2_DetectedPTCType_unknown_unmovable = 2,
    WJV2_DetectedPTCType_car = 3,
    WJV2_DetectedPTCType_van = 4,
    WJV2_DetectedPTCType_truck = 5,
    WJV2_DetectedPTCType_bus = 6,
    WJV2_DetectedPTCType_cyclist = 7,
    WJV2_DetectedPTCType_motorcyclist = 8,
    WJV2_DetectedPTCType_tricyclist = 9,
    WJV2_DetectedPTCType_pedestrian = 10
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_DetectedPTCType;

/* DriveBehavior */
typedef union
{
#define WJV2_LEN_BITSTR_DriveBehavior 14
#define WJV2_LEN_BYTE_DriveBehavior 2
    uint8_t u8DriveBehavior[WJV2_LEN_BYTE_DriveBehavior];
    struct
    {
        uint8_t bit_DriveBehavior_goStraightForward : 1;
        uint8_t bit_DriveBehavior_laneChangingToLeft : 1;
        uint8_t bit_DriveBehavior_laneChangingToRight : 1;
        uint8_t bit_DriveBehavior_rampIn : 1;
        uint8_t bit_DriveBehavior_rampOut : 1;
        uint8_t bit_DriveBehavior_intersectionStraightThrough : 1;
        uint8_t bit_DriveBehavior_intersectionTurnLeft : 1;
        uint8_t bit_DriveBehavior_intersectionTurnRight : 1;
        uint8_t bit_DriveBehavior_intersectionUTurn : 1;
        uint8_t bit_DriveBehavior_stop_and_go : 1;
        uint8_t bit_DriveBehavior_stop : 1;
        uint8_t bit_DriveBehavior_slow_down : 1;
        uint8_t bit_DriveBehavior_speed_up : 1;
        uint8_t bit_DriveBehavior_parking : 1;
        uint8_t bit_reserved : 2;
    };
}__attribute__ ((packed))  WJV2_BIT_DriveBehavior;

typedef enum WJV2_EquipmentType
{
    WJV2_EquipmentType_unknown = 0,
    WJV2_EquipmentType_rsu = 1,
    WJV2_EquipmentType_obu = 2,
    WJV2_EquipmentType_vru = 3
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_EquipmentType;

typedef enum WJV2_EquipmentClass
{
    WJV2_EquipmentClass_onechipOBU = 0,
    WJV2_EquipmentClass_iccOBU = 1,
    WJV2_EquipmentClass_cpcOBU = 2
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_EquipmentClass;

typedef struct _FileData
{
    uint8_t u8OCTidNum;
#define WJV2_MAX_OCTFileID_SIZE 127
    uint8_t u8OCTid[WJV2_MAX_OCTFileID_SIZE];
}__attribute__ ((packed))  WJV2_OCT_FileData;

typedef enum WJV2_HumanPropelledType
{
    WJV2_HumanPropelledType_unavailable = 0,
    WJV2_HumanPropelledType_otherTypes = 1,
    WJV2_HumanPropelledType_onFoot = 2,
    WJV2_HumanPropelledType_skateboard = 3,
    WJV2_HumanPropelledType_pushOrKickScooter = 4,
    WJV2_HumanPropelledType_wheelchair = 5
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_HumanPropelledType;

/* DriveBehavior */
typedef union
{
#define WJV2_LEN_BITSTR_LaneAttributes_Vehicle 8
#define WJV2_LEN_BYTE_LaneAttributes_Vehicle 1
    uint8_t u8LaneAttributes_Vehicle[WJV2_LEN_BYTE_LaneAttributes_Vehicle];
    struct
    {
        uint8_t bit_LaneAttributes_Vehicle_isVehicleRevocableLane : 1;
        uint8_t bit_LaneAttributes_Vehicle_isVehicleFlyOverLane : 1;
        uint8_t bit_LaneAttributes_Vehicle_hovLaneUseOnly : 1;
        uint8_t bit_LaneAttributes_Vehicle_restrictedToBusUse : 1;
        uint8_t bit_LaneAttributes_Vehicle_restrictedToTaxiUse : 1;
        uint8_t bit_LaneAttributes_Vehicle_restrictedFromPublicUse : 1;
        uint8_t bit_LaneAttributes_Vehicle_hasIRbeaconCoverage : 1;
        uint8_t bit_LaneAttributes_Vehicle_permissionOnRequest : 1;
    };
}__attribute__ ((packed))  WJV2_BIT_LaneAttributes_Vehicle;

/* LaneRefID */
#define WJV2_MAX_LaneRefID_SIZE 31
#define WJV2_MIN_LaneRefID_SIZE -31
#define WJV2_INT_LaneRefID int32_t

typedef enum WJV2_Maneuver
{
    WJV2_Maneuver_maneuverStraight = 0,
    WJV2_Maneuver_maneuverLeftTurn = 1,
    WJV2_Maneuver_maneuverRightTurn = 2,
    WJV2_Maneuver_maneuverUTurn = 3
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_Maneuver;

typedef enum WJV2_MotorizedPropelledType
{
    WJV2_MotorizedPropelledType_unavailable = 0,
    WJV2_MotorizedPropelledType_otherTypes = 1,
    WJV2_MotorizedPropelledType_wheelChair = 2,
    WJV2_MotorizedPropelledType_bicycle = 3,
    WJV2_MotorizedPropelledType_scooter = 4,
    WJV2_MotorizedPropelledType_selfBalancingDevice = 5
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_MotorizedPropelledType;

typedef enum WJV2_NumberOfParticipantsInCluster
{
    WJV2_NumberOfParticipantsInCluster_unavailable = 0,
    WJV2_NumberOfParticipantsInCluster_small = 1,
    WJV2_NumberOfParticipantsInCluster_medium = 2,
    WJV2_NumberOfParticipantsInCluster_large = 3
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_NumberOfParticipantsInCluster;

typedef enum WJV2_ObstacleType
{
    WJV2_ObstacleType_unknown = 0,
    WJV2_ObstacleType_rockfall = 1,
    WJV2_ObstacleType_landslide = 2,
    WJV2_ObstacleType_animal_intrusion = 3,
    WJV2_ObstacleType_liquid_spill = 4,
    WJV2_ObstacleType_goods_scattered = 5,
    WJV2_ObstacleType_trafficcone = 6,
    WJV2_ObstacleType_safety_triangle = 7,
    WJV2_ObstacleType_traffic_roadblock = 8,
    WJV2_ObstacleType_inspection_shaft_without_cover = 9,
    WJV2_ObstacleType_unknown_fragments = 10,
    WJV2_ObstacleType_unknown_hard_object = 11,
    WJV2_ObstacleType_unknown_soft_object = 12
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_ObstacleType;

typedef enum WJV2_OBUType
{
    WJV2_OBUType_oemObu = 0,
    WJV2_OBUType_aftermarketObu = 1,
    WJV2_OBUType_mobilePhone = 2
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_OBUType;

typedef enum WJV2_ParkingLock
{
    WJV2_ParkingLock_unknown = 0,
    WJV2_ParkingLock_nolock = 1,
    WJV2_ParkingLock_locked = 2,
    WJV2_ParkingLock_unlocked = 3
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_ParkingLock;

typedef union
{
#define WJV2_LEN_BITSTR_ParkingRequest 12
#define WJV2_LEN_BYTE_ParkingRequest 2
    uint8_t u8ParkingRequest[WJV2_LEN_BYTE_ParkingRequest];
    struct
    {
        uint16_t bit_ParkingRequest_enter : 1;
        uint16_t bit_ParkingRequest_exit : 1;
        uint16_t bit_ParkingRequest_park : 1;
        uint16_t bit_ParkingRequest_pay : 1;
        uint16_t bit_ParkingRequest_unloadPassenger : 1;
        uint16_t bit_ParkingRequest_pickupPassenger : 1;
        uint16_t bit_ParkingRequest_unloadCargo : 1;
        uint16_t bit_ParkingRequest_loadCargo : 1;
        uint16_t bit_ParkingRequest_reserved1 : 1;
        uint16_t bit_ParkingRequest_reverved2 : 1;
        uint16_t bit_ParkingRequest_reserved3 : 1;
        uint16_t bit_ParkingRequest_reverved4 : 1;
        uint16_t bit_reserved : 4;
    };
}__attribute__ ((packed))  WJV2_BIT_ParkingRequest;

typedef enum WJV2_ParkingSpaceTheta
{
    WJV2_ParkingSpaceTheta_unknown = 0,
    WJV2_ParkingSpaceTheta_vertical = 1,
    WJV2_ParkingSpaceTheta_side = 2,
    WJV2_ParkingSpaceTheta_oblique = 3
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_ParkingSpaceTheta;

typedef union
{
#define WJV2_LEN_BITSTR_ParkingType 10
#define WJV2_LEN_BYTE_ParkingType 2
    uint8_t u8ParkingType[WJV2_LEN_BYTE_ParkingType];
    struct
    {
        uint16_t bit_ParkingType_ordinary : 1;
        uint16_t bit_ParkingType_disabled : 1;
        uint16_t bit_ParkingType_mini : 1;
        uint16_t bit_ParkingType_attached : 1;
        uint16_t bit_ParkingType_charging : 1;
        uint16_t bit_ParkingType_stereo : 1;
        uint16_t bit_ParkingType_lady : 1;
        uint16_t bit_ParkingType_extended : 1;
        uint16_t bit_ParkingType_private : 1;
        uint16_t bit_reserved : 6;
    };
}__attribute__ ((packed))  WJV2_BIT_ParkingType;

typedef union
{
#define WJV2_LEN_BITSTR_PAMNodeAttributes 8
#define WJV2_LEN_BYTE_PAMNodeAttributes 1
    uint8_t u8PAMNodeAttributes[WJV2_LEN_BYTE_PAMNodeAttributes];
    struct
    {
        uint8_t bit_PAMNodeAttributes_entrance : 1;
        uint8_t bit_PAMNodeAttributes_exit : 1;
        uint8_t bit_PAMNodeAttributes_toUpstair : 1;
        uint8_t bit_PAMNodeAttributes_toDownstair : 1;
        uint8_t bit_PAMNodeAttributes_etc : 1;
        uint8_t bit_PAMNodeAttributes_mtc : 1;
        uint8_t bit_PAMNodeAttributes_passAfterPayment : 1;
        uint8_t bit_PAMNodeAttributes_blocked : 1;
    };
}__attribute__ ((packed))  WJV2_BIT_PAMNodeAttributes;

#define WJV2_MAX_PAMNodeID_SIZE 65535
#define WJV2_MIN_PAMNodeID_SIZE 0
#define WJV2_INT_PAMNodeID int32_t

typedef enum WJV2_PaymentEntityID
{
    WJV2_PaymentEntityID_system = 0,
    WJV2_PaymentEntityID_freeflow = 1,
    WJV2_PaymentEntityID_enclosed = 2,
    WJV2_PaymentEntityID_congestion = 3,
    WJV2_PaymentEntityID_charging = 4,
    WJV2_PaymentEntityID_parking = 5
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_PaymentEntityID;

typedef union
{
#define WJV2_LEN_BITSTR_PersonalAssistive 6
#define WJV2_LEN_BYTE_PersonalAssistive 1
    uint8_t u8PersonalAssistive[WJV2_LEN_BYTE_PersonalAssistive];
    struct
    {
        uint8_t bit_PersonalAssistive_unavailable : 1;
        uint8_t bit_PersonalAssistive_otherType : 1;
        uint8_t bit_PersonalAssistive_vision : 1;
        uint8_t bit_PersonalAssistive_hearing : 1;
        uint8_t bit_PersonalAssistive_movement : 1;
        uint8_t bit_PersonalAssistive_cognition : 1;
        uint8_t bit_reserved : 2;
    };
}__attribute__ ((packed))  WJV2_BIT_PersonalAssistive;

typedef enum WJV2_PersonalCrossing
{
    WJV2_PersonalCrossing_unavailable = 0,
    WJV2_PersonalCrossing_request = 1,
    WJV2_PersonalCrossing_crossing = 2,
    WJV2_PersonalCrossing_finish = 3
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_PersonalCrossing;

typedef union
{
#define WJV2_LEN_BITSTR_PersonalDeviceUsageState 9
#define WJV2_LEN_BYTE_PersonalDeviceUsageState 2
    uint8_t u8PersonalDeviceUsageState[WJV2_LEN_BYTE_PersonalDeviceUsageState];
    struct
    {
        uint16_t bit_PersonalDeviceUsageState_unavailable : 1;
        uint16_t bit_PersonalDeviceUsageState_other : 1;
        uint16_t bit_PersonalDeviceUsageState_idle : 1;
        uint16_t bit_PersonalDeviceUsageState_listeningToAudio : 1;
        uint16_t bit_PersonalDeviceUsageState_typing : 1;
        uint16_t bit_PersonalDeviceUsageState_calling : 1;
        uint16_t bit_PersonalDeviceUsageState_playingGames : 1;
        uint16_t bit_PersonalDeviceUsageState_reading : 1;
        uint16_t bit_PersonalDeviceUsageState_viewing : 1;
        uint16_t bit_reserved : 7;
    };
}__attribute__ ((packed))  WJV2_BIT_PersonalDeviceUsageState;

typedef enum WJV2_PersonalDeviceUserType
{
    WJV2_PersonalDeviceUserType_unavailable = 0,
    WJV2_PersonalDeviceUserType_aPEDESTRIAN = 1,
    WJV2_PersonalDeviceUserType_aPEDALCYCLIST = 2,
    WJV2_PersonalDeviceUserType_aROADWORKER = 3,
    WJV2_PersonalDeviceUserType_anANIMAL = 4
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_PersonalDeviceUserType;

#define WJV2_MAX_Pitch_SIZE 7200
#define WJV2_MIN_Pitch_SIZE -7200
#define WJV2_INT_Pitch int32_t

#define WJV2_MAX_PitchRate_SIZE 32767
#define WJV2_MIN_PitchRate_SIZE -32767
#define WJV2_INT_PitchRate int32_t

#define WJV2_MAX_PlanningDuration_SIZE 600
#define WJV2_MIN_PlanningDuration_SIZE 0
#define WJV2_INT_PlanningDuration int32_t

typedef struct _RandStr8Data
{
    uint8_t u8OCTRandStr8Num;
#define WJV2_MAX_OCTRandStr8_SIZE 8
    uint8_t u8OCTRandStr8[WJV2_MAX_OCTRandStr8_SIZE];
}__attribute__ ((packed))  WJV2_OCT_RandStr8Data;

typedef enum WJV2_ReqStatus
{
    WJV2_ReqStatus_unknown = 0,
    WJV2_ReqStatus_request = 1,
    WJV2_ReqStatus_comfirmed = 2,
    WJV2_ReqStatus_cancel = 3,
    WJV2_ReqStatus_complete = 4
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_ReqStatus;

typedef enum WJV2_ReturnStatus
{
    WJV2_ReturnStatus_noError = 0,
    WJV2_ReturnStatus_accessDenied = 1,
    WJV2_ReturnStatus_argumnetError = 2,
    WJV2_ReturnStatus_complexityLimitation = 3,
    WJV2_ReturnStatus_processingFailure = 4,
    WJV2_ReturnStatus_processing = 5
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_ReturnStatus;

typedef union
{
#define WJV2_LEN_BITSTR_RoadWorkerActivityType 6
#define WJV2_LEN_BYTE_RoadWorkerActivityType 1
    uint8_t u8RoadWorkerActivityType[WJV2_LEN_BYTE_RoadWorkerActivityType];
    struct
    {
        uint8_t bit_RoadWorkerActivityType_unavailable : 1;
        uint8_t bit_RoadWorkerActivityType_workingOnRoad : 1;
        uint8_t bit_RoadWorkerActivityType_settingUpClosures : 1;
        uint8_t bit_RoadWorkerActivityType_respondingToEvents : 1;
        uint8_t bit_RoadWorkerActivityType_directingTraffic : 1;
        uint8_t bit_RoadWorkerActivityType_otherActivities : 1;
        uint8_t bit_reserved : 2;
    };
}__attribute__ ((packed))  WJV2_BIT_RoadWorkerActivityType;

typedef enum WJV2_RoadWorkerType
{
    WJV2_RoadWorkerType_unavailable = 0,
    WJV2_RoadWorkerType_trafficPolice = 1,
    WJV2_RoadWorkerType_constructionPersonnel = 2,
    WJV2_RoadWorkerType_policeOfficers = 3,
    WJV2_RoadWorkerType_trafficControlPersons = 4,
    WJV2_RoadWorkerType_railroadCrossingGuards = 5,
    WJV2_RoadWorkerType_emergencyOrganizationPersonnel = 6
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_RoadWorkerType;

typedef enum WJV2_RoleInPlatooning
{
    WJV2_RoleInPlatooning_leader = 0,
    WJV2_RoleInPlatooning_follower = 1,
    WJV2_RoleInPlatooning_tail = 2,
    WJV2_RoleInPlatooning_free_vehicle = 3
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_RoleInPlatooning;

#define WJV2_MAX_Roll_SIZE 7200
#define WJV2_MIN_Roll_SIZE -7200
#define WJV2_INT_Roll int32_t

#define WJV2_MAX_RollRate_SIZE 32767
#define WJV2_MIN_RollRate_SIZE -32767
#define WJV2_INT_RollRate int32_t

#define WJV2_MAX_RTCM_ID_SIZE 32767
#define WJV2_MIN_RTCM_ID_SIZE 0
#define WJV2_INT_RTCM_ID int32_t

typedef struct _RTCM_PayloadData
{
    uint16_t u16OCTRTCMPayloadNum;
#define WJV2_MAX_OCTRTCMPayload_SIZE 2047
#define WJV2_MIN_OCTRTCMPayload_SIZE 1
    uint8_t u8OCTRTCMPayload[WJV2_MAX_OCTRTCMPayload_SIZE];
}__attribute__ ((packed))  WJV2_OCT_RTCM_PayloadData;

typedef enum WJV2_RTCM_Revision
{
    WJV2_RTCM_Revision_unknown = 0,
    WJV2_RTCM_Revision_reserved = 1,
    WJV2_RTCM_Revision_rtcmCMR = 2,
    WJV2_RTCM_Revision_rtcmCMR_Plus = 3,
    WJV2_RTCM_Revision_rtcmSAPOS = 4,
    WJV2_RTCM_Revision_rtcmSAPOS_Adv = 5,
    WJV2_RTCM_Revision_rtcmRTCA = 6,
    WJV2_RTCM_Revision_rtcmRAW = 7,
    WJV2_RTCM_Revision_rtcmRINEX = 8,
    WJV2_RTCM_Revision_rtcmSP3 = 9,
    WJV2_RTCM_Revision_rtcmBINEX = 10,
    WJV2_RTCM_Revision_rtcmRev2_x = 19,
    WJV2_RTCM_Revision_rtcmRev2_0 = 20,
    WJV2_RTCM_Revision_rtcmRev2_1 = 21,
    WJV2_RTCM_Revision_rtcmRev2_3 = 23,
    WJV2_RTCM_Revision_rtcmRev3_0 = 30,
    WJV2_RTCM_Revision_rtcmRev3_1 = 31,
    WJV2_RTCM_Revision_rtcmRev3_2 = 32
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_RTCM_Revision;

#define WJV2_MAX_SectionId_SIZE 63
#define WJV2_MIN_SectionId_SIZE 1
#define WJV2_INT_SectionId int32_t

#define WJV2_MAX_SizeValue_SIZE 1023
#define WJV2_MIN_SizeValue_SIZE 0
#define WJV2_INT_SizeValue int32_t

typedef enum WJV2_SizeValueConfidence
{
    WJV2_SizeValueConfidence_unavailable = 0,
    WJV2_SizeValueConfidence_size_100_00 = 1,
    WJV2_SizeValueConfidence_size_050_00 = 2,
    WJV2_SizeValueConfidence_size_020_00 = 3,
    WJV2_SizeValueConfidence_size_010_00 = 4,
    WJV2_SizeValueConfidence_size_005_00 = 5,
    WJV2_SizeValueConfidence_size_002_00 = 6,
    WJV2_SizeValueConfidence_size_001_00 = 7,
    WJV2_SizeValueConfidence_size_000_50 = 8,
    WJV2_SizeValueConfidence_size_000_20 = 9,
    WJV2_SizeValueConfidence_size_000_10 = 10,
    WJV2_SizeValueConfidence_size_000_05 = 11,
    WJV2_SizeValueConfidence_size_000_02 = 12,
    WJV2_SizeValueConfidence_size_000_01 = 13
}__attribute__ ((packed))  WJV2_ENUM_SizeValueConfidence;

typedef enum WJV2_SlotStatus
{
    WJV2_SlotStatus_unknown = 0,
    WJV2_SlotStatus_available = 1,
    WJV2_SlotStatus_occupied = 2
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_SlotStatus;

#define WJV2_MAX_StationOrGantryId_SIZE 4294967295
#define WJV2_MIN_StationOrGantryId_SIZE 0
#define WJV2_INT_StationOrGantryId int32_t

typedef enum WJV2_StatusInPlatooning
{
    WJV2_StatusInPlatooning_navigating = 0,
    WJV2_StatusInPlatooning_beginToDissmiss = 1,
    WJV2_StatusInPlatooning_askForJoining = 2,
    WJV2_StatusInPlatooning_joining = 3,
    WJV2_StatusInPlatooning_following = 4,
    WJV2_StatusInPlatooning_askForLeaving = 5,
    WJV2_StatusInPlatooning_leaving = 6
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_StatusInPlatooning;

typedef enum WJV2_TollingDirection
{
    WJV2_TollingDirection_north = 0,
    WJV2_TollingDirection_northeast = 1,
    WJV2_TollingDirection_east = 2,
    WJV2_TollingDirection_southeast = 3,
    WJV2_TollingDirection_south = 4,
    WJV2_TollingDirection_southwest = 5,
    WJV2_TollingDirection_west = 6,
    WJV2_TollingDirection_northwest = 7
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_TollingDirection;

typedef enum WJV2_TollResult
{
    WJV2_TollResult_ok = 0,
    WJV2_TollResult_nok = 1,
    WJV2_TollResult_contactOperator = 2
}__attribute__ ((packed))  WJV2_ENUM_TollResult;

typedef enum WJV2_TollingNodeType
{
    WJV2_TollingNodeType_entranceStation = 0,
    WJV2_TollingNodeType_exitStatino = 1,
    WJV2_TollingNodeType_entranceAndExitStation = 2,
    WJV2_TollingNodeType_gantry = 3
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_TollingNodeType;

#define WJV2_MAX_Yaw_SIZE 14400
#define WJV2_MIN_Yaw_SIZE -14400
#define WJV2_INT_Yaw int32_t

/* Dependencies */
typedef enum WJV2_Dotted_SolidMarkingLineType
{
    WJV2_Dotted_SolidMarkingLineType_whiteDottedLine = 0,
    WJV2_Dotted_SolidMarkingLineType_whiteSolidLine = 1,
    WJV2_Dotted_SolidMarkingLineType_yellowDottedLine = 2,
    WJV2_Dotted_SolidMarkingLineType_yellowSolidLine = 3,
    WJV2_Dotted_SolidMarkingLineType_whiteDotted_solidLine = 4,
    WJV2_Dotted_SolidMarkingLineType_whiteSotted_dottedLine = 5,
    WJV2_Dotted_SolidMarkingLineType_yellowDotted_solidLine = 6,
    WJV2_Dotted_SolidMarkingLineType_yellowSotted_dottedLine = 7
    /*
	 * Enumeration is extensible
	 */
}__attribute__ ((packed))  WJV2_ENUM_Dotted_SolidMarkingLineType;

#define WJV2_MAX_OFFSET_SIZE 32767
#define WJV2_MIN_OFFSET_SIZE 0
#define WJV2_INT_OFFSET int32_t

#define WJV2_MAX_LENGTH_SIZE 127
#define WJV2_MIN_LENGTH_SIZE 0
#define WJV2_INT_LENGTH int32_t

#define WJV2_MAX_keyIdForAC_SIZE 255
#define WJV2_MIN_keyIdForAC_SIZE 0
#define WJV2_INT_keyIdForAC int32_t

#define WJV2_MAX_keyIdForAuthen_SIZE 255
#define WJV2_MIN_keyIdForAuthen_SIZE 0
#define WJV2_INT_keyIdForAuthen int32_t

#define WJV2_MAX_keyIdForEncrypt_SIZE 255
#define WJV2_MIN_keyIdForEncrypt_SIZE 0
#define WJV2_INT_keyIdForEncrypt int32_t

#define WJV2_MAX_price_SIZE 424967295
#define WJV2_MIN_price_SIZE 0
#define WJV2_INT_price int32_t

#define WJV2_MAX_obsId_SIZE 65535
#define WJV2_MIN_obsId_SIZE 0
#define WJV2_INT_obsId int32_t

#define WJV2_MAX_tracking_SIZE 65535
#define WJV2_MIN_tracking_SIZE 1
#define WJV2_INT_tracking int32_t

#define WJV2_MAX_overallRadius_SIZE 200
#define WJV2_MIN_overallRadius_SIZE 0
#define WJV2_INT_overallRadius int32_t

#define WJV2_MAX_distance2Intersection_SIZE 10000
#define WJV2_MIN_distance2Intersection_SIZE 0
#define WJV2_INT_distance2Intersection int32_t

#define WJV2_MAX_expectedParkingSlotID_SIZE 65535
#define WJV2_MIN_expectedParkingSlotID_SIZE 0
#define WJV2_INT_expectedParkingSlotID int32_t

#define WJV2_MAX_reqID_SIZE 255
#define WJV2_MIN_reqID_SIZE 0
#define WJV2_INT_reqID int32_t

#define WJV2_MAX_s_axis_SIZE 65535
#define WJV2_MIN_s_axis_SIZE -1024
#define WJV2_INT_s_axis int32_t

#define WJV2_MAX_t_axis_SIZE 32767
#define WJV2_MIN_t_axis_SIZE -32768
#define WJV2_INT_t_axis int32_t

#define WJV2_MAX_capacity_SIZE 32
#define WJV2_MIN_capacity_SIZE 1
#define WJV2_INT_capacity int32_t

#define WJV2_MAX_contractType_SIZE 127
#define WJV2_MIN_contractType_SIZE 0
#define WJV2_INT_contractType int32_t

#define WJV2_MAX_contractVersion_SIZE 127
#define WJV2_MIN_contractVersion_SIZE 0
#define WJV2_INT_contractVersion int32_t

#define WJV2_MAX_vehicleTollingClass_SIZE 127
#define WJV2_MIN_vehicleTollingClass_SIZE 0
#define WJV2_INT_vehicleTollingClass int32_t

#define WJV2_MAX_vehicleUserType_SIZE 127
#define WJV2_MIN_vehicleUserType_SIZE 0
#define WJV2_INT_vehicleUserType int32_t

#define WJV2_MAX_vehicleWheels_SIZE 127
#define WJV2_MIN_vehicleWheels_SIZE 0
#define WJV2_INT_vehicleWheels int32_t

#define WJV2_MAX_vehicleAxles_SIZE 127
#define WJV2_MIN_vehicleAxles_SIZE 0
#define WJV2_INT_vehicleAxles int32_t

#define WJV2_MAX_vehicleWheelBases_SIZE 65535
#define WJV2_MIN_vehicleWheelBases_SIZE 0
#define WJV2_INT_vehicleWheelBases int32_t

#define WJV2_MAX_vehicleWeightLimits_SIZE 16777215
#define WJV2_MIN_vehicleWeightLimits_SIZE 0
#define WJV2_INT_vehicleWeightLimits int32_t

#define WJV2_MAX_BOOLEAN_SIZE 4294967295
#define WJV2_MIN_BOOLEAN_SIZE 0
#define WJV2_INT_BOOLEAN int32_t

#define WJV2_MAX_ParkingLotInfo_id_SIZE 65535
#define WJV2_MIN_ParkingLotInfo_id_SIZE 0
#define WJV2_INT_ParkingLotInfo_id int32_t

#define WJV2_MAX_number_SIZE 65535
#define WJV2_MIN_number_SIZE 0
#define WJV2_INT_number int32_t

#define WJV2_MAX_buildingLayerNum_SIZE 256
#define WJV2_MIN_buildingLayerNum_SIZE 0
#define WJV2_INT_buildingLayerNum int32_t

#define WJV2_MAX_slotID_SIZE 65535
#define WJV2_MIN_slotID_SIZE 0
#define WJV2_INT_slotID int32_t

#define WJV2_MAX_driveID_SIZE 255
#define WJV2_MIN_driveID_SIZE 0
#define WJV2_INT_driveID int32_t

#define WJV2_MAX_heightRestriction_SIZE 100
#define WJV2_MIN_heightRestriction_SIZE 0
#define WJV2_INT_heightRestriction int32_t

#define WJV2_MAX_laneNum_SIZE 100
#define WJV2_MIN_laneNum_SIZE 0
#define WJV2_INT_laneNum int32_t

#define WJV2_MAX_floor_SIZE 128
#define WJV2_MIN_floor_SIZE -128
#define WJV2_INT_floor int32_t

#define WJV2_MAX_targetParkingSlot_SIZE 65535
#define WJV2_MIN_targetParkingSlot_SIZE 0
#define WJV2_INT_targetParkingSlot int32_t
#endif /* 文件结束 */