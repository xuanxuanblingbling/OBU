/**
* @file         :WJV3_uper_De.h
* @brief        :该文件为协议栈数据元素映射头文件，包含函数外部申明，长度范围定义，类型结构体定义等
* @details  	:主要包含协议结构体的定义和编解码程序的外部申明
* @author   	:huangsai  any question please send mail to huangsai@wanji,net.cn
* @date     	:2020-8-10
* @version		:V1.0
* @copyright 	:Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：IMAX6
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
#ifndef _WJV3_UPER_DE_H_
#define _WJV3_UPER_DE_H_
#include <stdint.h>
/* 存在和不存在标识 */
#define WJV3_ABSENT 0xA5
#define WJV3_PRESENT 0xB6
/* 协议栈V3标识 */
#define STACK_MSG_MODULE "STACKV3_MSG_MODULE"
/* list范围宏定义 */
#define WJV3_MAX_BYTE_ID_LEN 8
#define WJV3_MAX_BYTE_PLATNO_LEN 16
#define WJV3_MAX_BYTE_PLATENO_LEN 8
#define WJV3_MAX_DESCRIPTION_LEN 256
#define WJV3_MAX_PRIORITY_LEN 1
#define WJV3_MAX_PATHHISTORPOINT_NUM 23
#define WJV3_MAX_NODE_NUM 8 /* 协议规定 1 ～ 32 暂定 1～ 8 */
#define WJV3_MAX_INTERSECTIONSTATE_NUM 16
#define WJV3_MAX_POSITIONOFFSETLLV_NUM 32
#define WJV3_MAX_PHASESTATE_NUM 16
#define WJV3_MAX_PHASE_NUM 8
#define WJV3_MAX_LINK_NUM 8 /* 协议规定 1 ～ 32 暂定 1～ 8 */
#define WJV3_MAX_IA5_NAME_LEN 63
#define WJV3_MAX_REGULATORYSPEEDLIMIT_NUM 9
#define WJV3_MAX_ROADPOINT_NUM 10 /* 协议规定 1 ～ 31 暂定 1～ 10 */
#define WJV3_MAX_MOVEMENT_NUM 8 /* 协议规定 1 ～ 32 暂定 1～ 8 */
#define WJV3_MAX_LANE_NUM 16 /* 协议规定 1 ～ 32 暂定 1～ 16 */
#define WJV3_MAX_CONNECT_NUM 8
#define WJV3_MAX_PARTICIPANT_NUM 16
/* DE取值范围宏定义 */
#define WJV3_MAX_MSGCOUNT_SIZE 127
#define WJV3_MIN_MSGCOUNT_SIZE 0
#define WJV3_MAX_DYEAR_SIZE 4095
#define WJV3_MIN_DYEAR_SIZE 0
#define WJV3_MAX_DMONTH_SIZE 12
#define WJV3_MIN_DMONTH_SIZE 0
#define WJV3_MAX_DDAY_SIZE 31
#define WJV3_MIN_DDAY_SIZE 0
#define WJV3_MAX_DHOUR_SIZE 24
#define WJV3_MIN_DHOUR_SIZE 0
#define WJV3_MAX_DMINUTE_SIZE 60
#define WJV3_MIN_DMINUTE_SIZE 0
#define WJV3_MAX_DSECOND_SIZE 65535
#define WJV3_MIN_DSECOND_SIZE 0
#define WJV3_MAX_DTIMEOFFSET_SIZE 840
#define WJV3_MIN_DTIMEOFFSET_SIZE -840
#define WJV3_MAX_LATITUDE_SIZE 900000001
#define WJV3_MIN_LATITUDE_SIZE -900000000
#define WJV3_MAX_LONGITUDE_SIZE 1800000001
#define WJV3_MIN_LONGITUDE_SIZE -1799999999
#define WJV3_MAX_ELEVATION_SIZE 61439
#define WJV3_MIN_ELEVATION_SIZE -4096
#define WJV3_MAX_SPEED_SIZE 8191
#define WJV3_MIN_SPEED_SIZE 0
#define WJV3_MAX_HEADING_SIZE 28800
#define WJV3_MIN_HEADING_SIZE 0
#define WJV3_MAX_STEETINGWHEELANGLE_SIZE 127
#define WJV3_MIN_STEETINGWHEELANGLE_SIZE -126
#define WJV3_MAX_MINUTEOFTHEYEAR_SIZE 527040
#define WJV3_MIN_MINUTEOFTHEYEAR_SIZE 0
#define WJV3_MAX_ACCELERATION_SIZE 2001
#define WJV3_MIN_ACCELERATION_SIZE -2000
#define WJV3_MAX_VERTICALACCELERATION_SIZE 127
#define WJV3_MIN_VERTICALACCELERATION_SIZE -127
#define WJV3_MAX_YAWRATE_SIZE 32767
#define WJV3_MIN_YAWRATE_SIZE -32767
#define WJV3_MAX_VEHICLEWIDTH_SIZE 1023
#define WJV3_MIN_VEHICLEWIDTH_SIZE 0
#define WJV3_MAX_VEHICLELENGTH_SIZE 4095
#define WJV3_MIN_VEHICLELENGTH_SIZE 0
#define WJV3_MAX_VEHICLEHEIGHT_SIZE 127
#define WJV3_MIN_VEHICLEHEIGHT_SIZE 0
#define WJV3_MAX_BASICVEHICLECLASS_SIZE 255
#define WJV3_MIN_BASICVEHICLECLASS_SIZE 0
#define WJV3_MAX_TIMEOFFSET_SIZE 65535
#define WJV3_MIN_TIMEOFFSET_SIZE 1
#define WJV3_MAX_COARSEHEADING_SIZE 240
#define WJV3_MIN_COARSEHEADING_SIZE 0
#define WJV3_MAX_VERTOFFSETB07_SIZE 63
#define WJV3_MIN_VERTOFFSETB07_SIZE -64
#define WJV3_MAX_VERTOFFSETB08_SIZE 127
#define WJV3_MIN_VERTOFFSETB08_SIZE -128
#define WJV3_MAX_VERTOFFSETB09_SIZE 255
#define WJV3_MIN_VERTOFFSETB09_SIZE -256
#define WJV3_MAX_VERTOFFSETB10_SIZE 511
#define WJV3_MIN_VERTOFFSETB10_SIZE -512
#define WJV3_MAX_VERTOFFSETB11_SIZE 1023
#define WJV3_MIN_VERTOFFSETB11_SIZE -1024
#define WJV3_MAX_VERTOFFSETB12_SIZE 2047
#define WJV3_MIN_VERTOFFSETB12_SIZE -2048
#define WJV3_MAX_0FFSETLLB12_SIZE 2047
#define WJV3_MIN_0FFSETLLB12_SIZE -2048
#define WJV3_MAX_0FFSETLLB14_SIZE 8191
#define WJV3_MIN_0FFSETLLB14_SIZE -8192
#define WJV3_MAX_0FFSETLLB16_SIZE 32767
#define WJV3_MIN_0FFSETLLB16_SIZE -32768
#define WJV3_MAX_0FFSETLLB18_SIZE 131071
#define WJV3_MIN_0FFSETLLB18_SIZE -131072
#define WJV3_MAX_0FFSETLLB22_SIZE 2097151
#define WJV3_MIN_0FFSETLLB22_SIZE -2097152
#define WJV3_MAX_0FFSETLLB24_SIZE 8388607
#define WJV3_MIN_0FFSETLLB24_SIZE -8388608
#define WJV3_MAX_CONFIDENCE_SIZE 200
#define WJV3_MIN_CONFIDENCE_SIZE 0
#define WJV3_MAX_RADIUSOFCURVATURE_SIZE 32767
#define WJV3_MIN_RADIUSOFCURVATURE_SIZE -32767
#define WJV3_MAX_ROADREGULATORID_SIZE 65535
#define WJV3_MIN_ROADREGULATORID_SIZE 0
#define WJV3_MAX_NODEID_SIZE 65535
#define WJV3_MIN_NODEID_SIZE 0
#define WJV3_MAX_LANEWIDTH_SIZE 32767
#define WJV3_MIN_LANEWIDTH_SIZE 0
#define WJV3_MAX_PHASEID_SIZE 255
#define WJV3_MIN_PHASEID_SIZE 0
#define WJV3_MAX_LANEID_SIZE 255
#define WJV3_MIN_LANEID_SIZE 0
#define WJV3_MAX_TIMEMARK_SIZE 35999
#define WJV3_MIN_TIMEMARK_SIZE 0
#define WJV3_MAX_RADIUS_SIZE 1024
#define WJV3_MIN_RADIUS_SIZE 0
#define WJV3_MAX_RSIID_SIZE 255
#define WJV3_MIN_RSIID_SIZE 0
#define WJV3_MAX_PTCID_SIZE 65535
#define WJV3_MIN_PTCID_SIZE 0
#define WJV3_MAX_ALERTTYPE_SIZE 65535
#define WJV3_MIN_ALERTTYPE_SIZE 0
/* 类型结构体重定义*/
#define WJV3_STRU_MsgCount int32_t			 /* 0 ~ 127 */
#define WJV3_STRU_DYear int32_t				 /* 0 ~ 4095  eq 0 is invalid */
#define WJV3_STRU_DMonth int32_t				 /* 0 ~ 12  eq 0 is invalid */
#define WJV3_STRU_DDay int32_t				 /* 0 ~ 31  gt 0 is invalid */
#define WJV3_STRU_DHour int32_t				 /* 0 ~ 24  eq 24 is invalid */
#define WJV3_STRU_DMinute int32_t				 /* 0 ~ 60  gt 60 is invalid */
#define WJV3_STRU_DSecond int32_t				 /* 0 ~ 65535  gt 60000 is invalid */
#define WJV3_STRU_DTimeOffset int32_t			 /* -840 ~ +840 */
#define WJV3_STRU_Latitude int32_t			 /* -900000000 ～ 900000001 */
#define WJV3_STRU_Longitude int32_t			 /* -1799999999 ～ 1800000001 */
#define WJV3_STRU_Elevation int32_t			 /* -4096 ～ 61439 -4096 is invalid unit is 0.1m */
#define WJV3_STRU_Speed int32_t				 /* 0 ~ 8191 unit : 0.02m/s*/
#define WJV3_STRU_Heading int32_t				 /* 0 ～ 28800 unit 0.0125度 */
#define WJV3_STRU_SteeringWheelAngle int32_t	 /* -126 ～ 127 unit 1.5度 */
#define WJV3_STRU_MinuteOfTheYear int32_t		 /* 0 ~ 527040 */
#define WJV3_STRU_Acceleration int32_t		 /* -2000 ~ 2001 2001 IS invalid */
#define WJV3_STRU_VerticalAcceleration int32_t /* -127 ~ 127 */
#define WJV3_STRU_YawRate int32_t				 /* -32767 ~ 32767 */
#define WJV3_STRU_VehicleWidth int32_t		 /* 0 ~ 1023 0 is invalid unit is 1cm */
#define WJV3_STRU_VehicleLength int32_t		 /* 0 ~ 4095 0 is invalid unit is 1cm */
#define WJV3_STRU_VehicleHeight int32_t		 /* 0 ~ 127 0 is invalid unit is 5cm */
#define WJV3_STRU_BasicVehicleClass int32_t	 /* 0 ~ 255 */
#define WJV3_STRU_TimeOffset int32_t			 /* 1 ~ 65535 eq 6535 is invalid unit: 10 ms */
#define WJV3_STRU_CoarseHeading int32_t		 /* 0 ~240 unit: 1.5 */
#define WJV3_STRU_VertOffset_B07 int32_t		 /* -64 ~ 63 unit: 10cm  eq -64 is invalid */
#define WJV3_STRU_VertOffset_B08 int32_t		 /* -128 ~ 127 unit: 10cm eq -128 is invalid */
#define WJV3_STRU_VertOffset_B09 int32_t		 /* -256 ~ 255 unit: 10 cm eq -256 is invalid */
#define WJV3_STRU_VertOffset_B10 int32_t		 /* -512 ~ 511 unit: 10 cm eq -512 is invalid */
#define WJV3_STRU_VertOffset_B11 int32_t		 /* -1024 ~ 1023 unit: 10 cm eq -1024 is invalid */
#define WJV3_STRU_VertOffset_B12 int32_t		 /* -2048 ~ 2047 unit: 10 cm eq -2048 is invalid */
#define WJV3_STRU_OffsetLL_B12 int32_t		 /* -2048 ~2047 */
#define WJV3_STRU_OffsetLL_B14 int32_t		 /* -8192 ~8191 */
#define WJV3_STRU_OffsetLL_B16 int32_t		 /* -32768 ~32767 */
#define WJV3_STRU_OffsetLL_B18 int32_t		 /* -131072 ~131071 */
#define WJV3_STRU_OffsetLL_B22 int32_t		 /* -2097152 ~2097151 */
#define WJV3_STRU_OffsetLL_B24 int32_t		 /* -8388608 ~8388607 */
#define WJV3_STRU_Confidence int32_t			 /* 0 ~ 200 unit: 0.005 */
#define WJV3_STRU_RadiusOfCurvature int32_t	 /* -32767 ~ 32767 unit:10cm */
#define WJV3_STRU_RoadRegulatorID int32_t		 /* 0 ~ 65535 0 in order to test */
#define WJV3_STRU_NodeID int32_t				 /* 0 ~ 65535   0 ~ 255 in order to test */
#define WJV3_STRU_LaneWidth int32_t			 /* 0 ~ 32767 */
#define WJV3_STRU_PhaseID int32_t				 /* 0 ~ 255 0 is invalid */
#define WJV3_STRU_LaneID int32_t				 /* 0 ~ 255 0 is invalid */
#define WJV3_STRU_TimeMark int32_t			 /* 0 ~ 35999 unit:0.1s */
#define WJV3_STRU_Radius int32_t				 /* 0 ~ 1024 unit:0.1m */
#define WJV3_STRU_AlertType int32_t			 /* 0 ~ 65535 0 in order to test */
/* 枚举结构体定义 */
typedef enum
{
	WJV3_TransmissionState_neutral = 0,
	WJV3_TransmissionState_park = 1,
	WJV3_TransmissionState_forwardGears = 2,
	WJV3_TransmissionState_reverseGears = 3,
	WJV3_TransmissionState_reserved1 = 4,
	WJV3_TransmissionState_reserved2 = 5,
	WJV3_TransmissionState_reserved3 = 6,
	WJV3_TransmissionState_unavailable = 7
} WJV3_ENUM_TransmissionState;
typedef enum
{
	WJV3_Textmessagewarning = 0,
	WJV3_SharpTurn = 2,
	WJV3_Rockfall = 15,
	WJV3_Slippy = 17,
	WJV3_Tunnel = 21,
	WJV3_Danger = 37,
	WJV3_UnderConstruction = 38
} WJV3_ENUM_AlertType;
typedef enum
{
	WJV3_PositionConfidence_unavailable = 0,
	WJV3_PositionConfidence_a500m = 1,
	WJV3_PositionConfidence_a200m = 2,
	WJV3_PositionConfidence_a100m = 3,
	WJV3_PositionConfidence_a50m = 4,
	WJV3_PositionConfidence_a20m = 5,
	WJV3_PositionConfidence_a10m = 6,
	WJV3_PositionConfidence_a5m = 7,
	WJV3_PositionConfidence_a2m = 8,
	WJV3_PositionConfidence_a1m = 9,
	WJV3_PositionConfidence_a50cm = 10,
	WJV3_PositionConfidence_a20cm = 11,
	WJV3_PositionConfidence_a10cm = 12,
	WJV3_PositionConfidence_a5cm = 13,
	WJV3_PositionConfidence_a2cm = 14,
	WJV3_PositionConfidence_a1cm = 15
} WJV3_ENUM_PositionConfidence;
typedef enum
{
	WJV3_ElevationConfidence_unavailable = 0,
	WJV3_ElevationConfidence_elev_500_00 = 1,
	WJV3_ElevationConfidence_elev_200_00 = 2,
	WJV3_ElevationConfidence_elev_100_00 = 3,
	WJV3_ElevationConfidence_elev_050_00 = 4,
	WJV3_ElevationConfidence_elev_020_00 = 5,
	WJV3_ElevationConfidence_elev_010_00 = 6,
	WJV3_ElevationConfidence_elev_005_00 = 7,
	WJV3_ElevationConfidence_elev_002_00 = 8,
	WJV3_ElevationConfidence_elev_001_00 = 9,
	WJV3_ElevationConfidence_elev_000_50 = 10,
	WJV3_ElevationConfidence_elev_000_20 = 11,
	WJV3_ElevationConfidence_elev_000_10 = 12,
	WJV3_ElevationConfidence_elev_000_05 = 13,
	WJV3_ElevationConfidence_elev_000_02 = 14,
	WJV3_ElevationConfidence_elev_000_01 = 15
} WJV3_ENUM_ElevationConfidence;
typedef enum
{
	WJV3_SpeedConfidence_unavailable = 0,
	WJV3_SpeedConfidence_prec100ms = 1,
	WJV3_SpeedConfidence_prec10ms = 2,
	WJV3_SpeedConfidence_prec5ms = 3,
	WJV3_SpeedConfidence_prec1ms = 4,
	WJV3_SpeedConfidence_prec0_1ms = 5,
	WJV3_SpeedConfidence_prec0_05ms = 6,
	WJV3_SpeedConfidence_prec0_01ms = 7
} WJV3_ENUM_SpeedConfidence;
typedef enum
{
	WJV3_HeadingConfidence_unavailable = 0,
	WJV3_HeadingConfidence_prec10deg = 1,
	WJV3_HeadingConfidence_prec05deg = 2,
	WJV3_HeadingConfidence_prec01deg = 3,
	WJV3_HeadingConfidence_prec0_1deg = 4,
	WJV3_HeadingConfidence_prec0_05deg = 5,
	WJV3_HeadingConfidence_prec0_01deg = 6,
	WJV3_HeadingConfidence_prec0_0125deg = 7
} WJV3_ENUM_HeadingConfidence;
typedef enum
{
	WJV3_SteeringWheelAngleConfidence_unavailable = 0,
	WJV3_SteeringWheelAngleConfidence_prec2deg = 1,
	WJV3_SteeringWheelAngleConfidence_prec1deg = 2,
	WJV3_SteeringWheelAngleConfidence_prec0_02deg = 3
} WJV3_ENUM_SteeringWheelAngleConfidence;
typedef enum
{
	WJV3_BrakePedalStatus_unavailable = 0,
	WJV3_BrakePedalStatus_off = 1,
	WJV3_BrakePedalStatus_on = 2
} WJV3_ENUM_BrakePedalStatus;
typedef enum
{
	WJV3_BrakeAppliedStatus_unavailable = 0,
	WJV3_BrakeAppliedStatus_leftFront = 1,
	WJV3_BrakeAppliedStatus_leftRear = 2,
	WJV3_BrakeAppliedStatus_rightFront = 3,
	WJV3_BrakeAppliedStatus_rightRear = 4
} WJV3_ENUM_BrakeAppliedStatus;
typedef enum
{
	WJV3_TractionControlStatus_unavailable = 0,
	WJV3_TractionControlStatus_off = 1,
	WJV3_TractionControlStatus_on = 2,
	WJV3_TractionControlStatus_engaged = 3
} WJV3_ENUM_TractionControlStatus;
typedef enum
{
	WJV3_AntiLockBrakeStatus_unavailable = 0,
	WJV3_AntiLockBrakeStatus_off = 1,
	WJV3_AntiLockBrakeStatus_on = 2,
	WJV3_AntiLockBrakeStatus_engaged = 3
} WJV3_ENUM_AntiLockBrakeStatus;
typedef enum
{
	WJV3_StabilityControlStatus_unavailable = 0,
	WJV3_StabilityControlStatus_off = 1,
	WJV3_StabilityControlStatus_on = 2,
	WJV3_StabilityControlStatus_engaged = 3
} WJV3_ENUM_StabilityControlStatus;
typedef enum
{
	WJV3_BrakeBoostApplied_unavailable = 0,
	WJV3_BrakeBoostApplied_off = 1,
	WJV3_BrakeBoostApplied_on = 2
} WJV3_ENUM_BrakeBoostApplied;
typedef enum
{
	WJV3_AuxiliaryBrakeStatus_unavailable = 0,
	WJV3_AuxiliaryBrakeStatus_off = 1,
	WJV3_AuxiliaryBrakeStatus_on = 2,
	WJV3_AuxiliaryBrakeStatus_reserved = 3
} WJV3_ENUM_AuxiliaryBrakeStatus;
typedef enum
{
	WJV3_TimeConfidence_unavailable = 0,
	WJV3_TimeConfidence_time_100_000 = 1,
	WJV3_TimeConfidence_time_050_000 = 2,
	WJV3_TimeConfidence_time_020_000 = 3,
	WJV3_TimeConfidence_time_010_000 = 4,
	WJV3_TimeConfidence_time_002_000 = 5,
	WJV3_TimeConfidence_time_001_000 = 6,
	WJV3_TimeConfidence_time_000_500 = 7,
	WJV3_TimeConfidence_time_000_200 = 8,
	WJV3_TimeConfidence_time_000_100 = 9,
	WJV3_TimeConfidence_time_000_050 = 10,
	WJV3_TimeConfidence_time_000_020 = 11,
	WJV3_TimeConfidence_time_000_010 = 12,
	WJV3_TimeConfidence_time_000_005 = 13,
	WJV3_TimeConfidence_time_000_002 = 14,
	WJV3_TimeConfidence_time_000_001 = 15,
	WJV3_TimeConfidence_time_000_000_5 = 16,
	WJV3_TimeConfidence_time_000_000_2 = 17,
	WJV3_TimeConfidence_time_000_000_1 = 18,
	WJV3_TimeConfidence_time_000_000_05 = 19,
	WJV3_TimeConfidence_time_000_000_02 = 20,
	WJV3_TimeConfidence_time_000_000_01 = 21,
	WJV3_TimeConfidence_time_000_000_005 = 22,
	WJV3_TimeConfidence_time_000_000_002 = 23,
	WJV3_TimeConfidence_time_000_000_001 = 24,
	WJV3_TimeConfidence_time_000_000_000_5 = 25,
	WJV3_TimeConfidence_time_000_000_000_2 = 26,
	WJV3_TimeConfidence_time_000_000_000_1 = 27,
	WJV3_TimeConfidence_time_000_000_000_05 = 28,
	WJV3_TimeConfidence_time_000_000_000_02 = 29,
	WJV3_TimeConfidence_time_000_000_000_01 = 30,
	WJV3_TimeConfidence_time_000_000_000_005 = 31,
	WJV3_TimeConfidence_time_000_000_000_002 = 32,
	WJV3_TimeConfidence_time_000_000_000_001 = 33,
	WJV3_TimeConfidence_time_000_000_000_000_5 = 34,
	WJV3_TimeConfidence_time_000_000_000_000_2 = 35,
	WJV3_TimeConfidence_time_000_000_000_000_1 = 36,
	WJV3_TimeConfidence_time_000_000_000_000_05 = 37,
	WJV3_TimeConfidence_time_000_000_000_000_02 = 38,
	WJV3_TimeConfidence_time_000_000_000_000_01 = 39
} WJV3_ENUM_TimeConfidence;
typedef enum
{
	WJV3_SpeedLimitType_unknown = 0,
	WJV3_SpeedLimitType_maxSpeedInSchoolZone = 1,
	WJV3_SpeedLimitType_maxSpeedInSchoolZoneWhenChildrenArePresent = 2,
	WJV3_SpeedLimitType_maxSpeedInConstructionZone = 3,
	WJV3_SpeedLimitType_vehicleMinSpeed = 4,
	WJV3_SpeedLimitType_vehicleMaxSpeed = 5,
	WJV3_SpeedLimitType_vehicleNightMaxSpeed = 6,
	WJV3_SpeedLimitType_truckMinSpeed = 7,
	WJV3_SpeedLimitType_truckMaxSpeed = 8,
	WJV3_SpeedLimitType_truckNightMaxSpeed = 9,
	WJV3_SpeedLimitType_vehiclesWithTrailersMinSpeed = 10,
	WJV3_SpeedLimitType_vehiclesWithTrailersMaxSpeed = 11,
	WJV3_SpeedLimitType_vehiclesWithTrailersNightMaxSpeed = 12
} WJV3_ENUM_SpeedLimitType;
typedef enum
{
	WJV3_LightState_unavailable = 0,
	WJV3_LightState_dark = 1,
	WJV3_LightState_stop_Then_Proceed = 2,
	WJV3_LightState_stop_And_Remain = 3,
	WJV3_LightState_pre_Movement = 4,
	WJV3_LightState_permissive_Movement_Allowed = 5,
	WJV3_LightState_protected_Movement_Allowed = 6,
	WJV3_LightState_intersection_clearance = 7,
	WJV3_LightState_caution_Conflicting_Traffic = 8
} WJV3_ENUM_LightState;
#endif /* end of file */