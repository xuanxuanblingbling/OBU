/**
* @file         :wjv3_uper_Df.h
* @brief        :该文件为协议栈数据帧映射头文件，包含编码解码函数外部申明和一些结构体定义等
* @details  	:主要包含协议结构体的定义和编解码程序的外部申明
* @author   	:huangsai  any question please send mail to huangsai@wanji.net.cn
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
#ifndef _WJV3_UPER_DF_H_
#define _WJV3_UPER_DF_H_
/* 头文件包含 */
#include "wjv3_uper_De.h"
/***********************************************************************************/
/* 数据帧结构类型定义 */
/***********************************************************************************/
typedef struct
{
	WJV3_STRU_Latitude n32lat;
	WJV3_STRU_Longitude n32Long;
	uint8_t u8elevation_Present;
	WJV3_STRU_Elevation n32elevation; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_Position3D;
typedef struct
{
	WJV3_ENUM_PositionConfidence enumpos;
	uint8_t u8elevation_Present;
	WJV3_ENUM_ElevationConfidence enumelevation; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_PositionConfidenceSet;
typedef struct
{
	uint8_t u8speedCfd_Present;
	WJV3_ENUM_SpeedConfidence enumspeedCfd; /* OPTIONAL */
	uint8_t u8headingCfd_Present;
	WJV3_ENUM_HeadingConfidence enumheadingCfd; /* OPTIONAL */
	uint8_t u8steerCfd_Present;
	WJV3_ENUM_SteeringWheelAngleConfidence enumsteerCfd; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_MotionConfidenceSet;
typedef struct
{
	WJV3_STRU_Acceleration n32Long;
	WJV3_STRU_Acceleration n32lat;
	WJV3_STRU_VerticalAcceleration n32vert;
	WJV3_STRU_YawRate n32yaw;
} __attribute__ ((packed)) WJV3_STRU_AccelerationSet4Way;
typedef struct
{
	uint8_t u8brakePadel_Present;
	WJV3_ENUM_BrakePedalStatus enumbrakePadel; /* OPTIONAL */
	uint8_t u8wheelBrakes_Present;
	union
	{
	#define WJV3_LEN_BITSTR_WHEELBRAKES 5
	#define WJV3_LEN_BYTE_WHEELBRAKES 1
		uint8_t u8wheelBrakes[WJV3_LEN_BYTE_WHEELBRAKES]; /* OPTIONAL */
		struct
		{
			uint8_t bit_brake_status_unavailable :1;
			uint8_t bit_brake_status_leftFront   :1;
			uint8_t bit_brake_status_leftRear    :1;
			uint8_t bit_brake_status_rightFront  :1;
			uint8_t bit_brake_status_rightRear   :1;
			uint8_t bit_reserved                 :3;
		};
	}u;
	uint8_t u8traction_Present;
	WJV3_ENUM_TractionControlStatus enumtraction; /* OPTIONAL */
	uint8_t u8abs_Present;
	WJV3_ENUM_AntiLockBrakeStatus enumabs; /* OPTIONAL */
	uint8_t u8scs_Present;
	WJV3_ENUM_StabilityControlStatus enumscs; /* OPTIONAL */
	uint8_t u8brakeBoost_Present;
	WJV3_ENUM_BrakeBoostApplied enumbrakeBoost; /* OPTIONAL */
	uint8_t u8auxBrakes_Present;
	WJV3_ENUM_AuxiliaryBrakeStatus enumauxBrakes; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_BrakeSystemStatus;
typedef struct
{
	WJV3_STRU_VehicleWidth n32width;
	WJV3_STRU_VehicleLength n32length;
	uint8_t u8height_Present;
	WJV3_STRU_VehicleHeight n32height; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_VehicleSize;
typedef struct
{
	WJV3_STRU_BasicVehicleClass n32classification;
} __attribute__ ((packed)) WJV3_STRU_VehicleClassification;
typedef struct
{
	uint8_t u8year_Present;
	WJV3_STRU_DYear n32year; /* OPTIONAL */
	uint8_t u8month_Present;
	WJV3_STRU_DMonth n32month; /* OPTIONAL */
	uint8_t u8day_Present;
	WJV3_STRU_DDay n32day; /* OPTIONAL */
	uint8_t u8hour_Present;
	WJV3_STRU_DHour n32hour; /* OPTIONAL */
	uint8_t u8minute_Present;
	WJV3_STRU_DMinute n32minute; /* OPTIONAL */
	uint8_t u8second_Present;
	WJV3_STRU_DSecond n32second; /* OPTIONAL */
	uint8_t u8offset_Present;
	WJV3_STRU_DTimeOffset n32offset; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_DDateTime;
typedef struct
{
	uint8_t u8utcTime_Present;
	WJV3_STRU_DDateTime struutcTime; /* OPTIONAL */
	WJV3_STRU_Position3D strupos;
	uint8_t u8heading_Present;
	WJV3_STRU_Heading n32heading; /* OPTIONAL */
	uint8_t u8transmission_Present;
	WJV3_ENUM_TransmissionState enumtransmission; /* OPTIONAL */
	uint8_t u8speed_Present;
	WJV3_STRU_Speed n32speed; /* OPTIONAL */
	uint8_t u8posAccuracy_Present;
	WJV3_STRU_PositionConfidenceSet struposAccuracy; /* OPTIONAL */
	uint8_t u8timeConfidence_Present;
	WJV3_ENUM_TimeConfidence strutimeConfidence; /* OPTIONAL */
	uint8_t u8posConfidence_Present;
	WJV3_STRU_PositionConfidenceSet struposConfidence; /* OPTIONAL */
	uint8_t u8motionCfd_Present;
	WJV3_STRU_MotionConfidenceSet strumotionCfd; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_FullPositionVector;
typedef struct
{
	WJV3_STRU_OffsetLL_B12 n32lon;
	WJV3_STRU_OffsetLL_B12 n32lat;
} __attribute__ ((packed)) WJV3_STRU_Position_LL_24B;
typedef struct
{
	WJV3_STRU_OffsetLL_B14 n32lon;
	WJV3_STRU_OffsetLL_B14 n32lat;
} __attribute__ ((packed)) WJV3_STRU_Position_LL_28B;
typedef struct
{
	WJV3_STRU_OffsetLL_B16 n32lon;
	WJV3_STRU_OffsetLL_B16 n32lat;
} __attribute__ ((packed)) WJV3_STRU_Position_LL_32B;
typedef struct
{
	WJV3_STRU_OffsetLL_B18 n32lon;
	WJV3_STRU_OffsetLL_B18 n32lat;
} __attribute__ ((packed)) WJV3_STRU_Position_LL_36B;
typedef struct
{
	WJV3_STRU_OffsetLL_B22 n32lon;
	WJV3_STRU_OffsetLL_B22 n32lat;
} __attribute__ ((packed)) WJV3_STRU_Position_LL_44B;
typedef struct
{
	WJV3_STRU_OffsetLL_B24 n32lon;
	WJV3_STRU_OffsetLL_B24 n32lat;
} __attribute__ ((packed)) WJV3_STRU_Position_LL_48B;
typedef struct
{
	WJV3_STRU_Longitude n32lon;
	WJV3_STRU_Latitude n32lat;
} __attribute__ ((packed)) WJV3_STRU_Position_LLmD_64b;
typedef enum
{
	WJV3_PositionOffsetLL_PR_NOTHING, /* No components present */
	WJV3_PositionOffsetLL_PR_position_LL1,
	WJV3_PositionOffsetLL_PR_position_LL2,
	WJV3_PositionOffsetLL_PR_position_LL3,
	WJV3_PositionOffsetLL_PR_position_LL4,
	WJV3_PositionOffsetLL_PR_position_LL5,
	WJV3_PositionOffsetLL_PR_position_LL6,
	WJV3_PositionOffsetLL_PR_position_LatLon
} WJV3_ENUM_PositionOffsetLL_PR;
typedef struct
{
	WJV3_ENUM_PositionOffsetLL_PR enumpresent;
	union
	{
		WJV3_STRU_Position_LL_24B struposition_LL1;
		WJV3_STRU_Position_LL_28B struposition_LL2;
		WJV3_STRU_Position_LL_32B struposition_LL3;
		WJV3_STRU_Position_LL_36B struposition_LL4;
		WJV3_STRU_Position_LL_44B struposition_LL5;
		WJV3_STRU_Position_LL_48B struposition_LL6;
		WJV3_STRU_Position_LLmD_64b struposition_LatLon;
	} choice;
} __attribute__ ((packed)) WJV3_STRU_PositionOffsetLL;
typedef enum
{
	WJV3_VerticalOffset_PR_NOTHING, /* No components present */
	WJV3_VerticalOffset_PR_offset1,
	WJV3_VerticalOffset_PR_offset2,
	WJV3_VerticalOffset_PR_offset3,
	WJV3_VerticalOffset_PR_offset4,
	WJV3_VerticalOffset_PR_offset5,
	WJV3_VerticalOffset_PR_offset6,
	WJV3_VerticalOffset_PR_elevation
} WJV3_ENUM_VerticalOffset_PR;
typedef struct
{
	WJV3_ENUM_VerticalOffset_PR present;
	union
	{
		WJV3_STRU_VertOffset_B07 n32offset1;
		WJV3_STRU_VertOffset_B08 n32offset2;
		WJV3_STRU_VertOffset_B09 n32offset3;
		WJV3_STRU_VertOffset_B10 n32offset4;
		WJV3_STRU_VertOffset_B11 n32offset5;
		WJV3_STRU_VertOffset_B12 n32offset6;
		WJV3_STRU_Elevation n32elevation;
	} choice;
} __attribute__ ((packed)) WJV3_STRU_VerticalOffset;
typedef struct
{
	WJV3_STRU_PositionOffsetLL struoffsetLL;
	uint8_t u8offsetV_Present;
	WJV3_STRU_VerticalOffset struoffsetV; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_PositionOffsetLLV;
typedef struct
{
	WJV3_STRU_PositionOffsetLLV strullvOffset;
	WJV3_STRU_TimeOffset n32timeOffset;
	uint8_t u8speed_Present;
	WJV3_STRU_Speed n32speed; /* OPTIONAL */
	uint8_t u8posAccuracy_Present;
	WJV3_STRU_PositionConfidenceSet struposAccuracy; /* OPTIONAL */
	uint8_t u8heading_Present;
	WJV3_STRU_CoarseHeading n32heading;
} __attribute__ ((packed)) WJV3_STRU_PathHistoryPoint;
typedef struct
{
	uint8_t u8PathHistoryPointNum; /* 1 ~ 23 */
	WJV3_STRU_PathHistoryPoint struPathHistoryPointList[WJV3_MAX_PATHHISTORPOINT_NUM];
} __attribute__ ((packed)) WJV3_STRU_PathHistoryPointList;
typedef struct
{
	uint8_t u8initialPosition_Present;
	WJV3_STRU_FullPositionVector struinitialPosition; /* OPTIONAL */
	uint8_t u8currGNSSstatus_Present;
	union
	{
	#define WJV3_LEN_BITSTR_CURRGNSSSTATUS 8
	#define WJV3_LEN_BYTE_CURRGNSSSTATUS 1
		uint8_t u8currGNSSstatus[WJV3_LEN_BYTE_CURRGNSSSTATUS]; /* OPTIONAL */
		struct
		{
			uint8_t bit_GNSSstat_unavailable              :1;
			uint8_t bit_GNSSstat_isHealthy                :1;
			uint8_t bit_GNSSstat_isMonitored              :1;
			uint8_t bit_GNSSstat_baseStationType          :1;
			uint8_t bit_GNSSstat_aPDOPofUnder5            :1;
			uint8_t bit_GNSSstat_inViewOfUnder5           :1;
			uint8_t bit_GNSSstat_localCorrectionPresend   :1;
			uint8_t bit_GNSSstat_networkCorrectionPresend :1;
		};
	}u;
	WJV3_STRU_PathHistoryPointList strucrumbData;
} __attribute__ ((packed)) WJV3_STRU_PathHistory;
typedef struct
{
	WJV3_STRU_RadiusOfCurvature n32radiusOfCurve;
	WJV3_STRU_Confidence n32confidence;
} __attribute__ ((packed)) WJV3_STRU_PathPrediction;
typedef struct
{
	uint8_t u8events_Present;
	union
	{
	#define WJV3_LEN_BITSTR_EVENTS 13
	#define WJV3_LEN_BYTE_EVENTS 2
		uint8_t u8events[WJV3_LEN_BYTE_EVENTS]; /* OPTIONAL */
		struct{
			uint16_t bit_VehicleEventFlags_eventHazardLights              :1;
			uint16_t bit_VehicleEventFlags_eventStopLineViolation         :1;
			uint16_t bit_VehicleEventFlags_eventABSactivated              :1;
			uint16_t bit_VehicleEventFlags_eventTractionControlLoss       :1;
			uint16_t bit_VehicleEventFlags_eventStabilityControlactivated :1;
			uint16_t bit_VehicleEventFlags_eventHazardousMaterials        :1;
			uint16_t bit_VehicleEventFlags_eventReserved1                 :1;
			uint16_t bit_VehicleEventFlags_eventHardBraking               :1;
			uint16_t bit_VehicleEventFlags_eventLightsChanged             :1;
			uint16_t bit_VehicleEventFlags_eventWipersChanged             :1;
			uint16_t bit_VehicleEventFlags_eventFlatTire                  :1;
			uint16_t bit_VehicleEventFlags_eventDisabledVehicle           :1;
			uint16_t bit_VehicleEventFlags_eventAirBagDeployment          :1;
			uint16_t bit_VehicleEventFlags_reserved                       :3;
		};
	}u1;
	uint8_t u8pathHistory_Present;
	WJV3_STRU_PathHistory strupathHistory; /* OPTIONAL */
	uint8_t u8pathPrediction_Present;
	WJV3_STRU_PathPrediction strupathPrediction; /* OPTIONAL */
	uint8_t u8lights_Present;
	union
	{
	#define WJV3_LEN_BITSTR_LIGHTS 9
	#define WJV3_LEN_BYTE_LIGHTS 2
		uint8_t u8lights[WJV3_LEN_BYTE_LIGHTS]; /* OPTIONAL */
		struct
		{
			uint16_t bit_lowBeamHeadlightsOn     :1;
			uint16_t bit_highBeamHeadlightsOn    :1;
			uint16_t bit_leftTurnSignalOn        :1;
			uint16_t bit_rightTurnSignalOn       :1;
			uint16_t bit_hazardSignalOn          :1;
			uint16_t bit_automaticLightControlOn :1;
			uint16_t bit_daytimeRunningLightsOn  :1;
			uint16_t bit_fogLightOn              :1;
			uint16_t bit_parkingLightsOn         :1;
			uint16_t bit_reserved                :7;
    	};
	}u2;
} __attribute__ ((packed)) WJV3_STRU_VehicleSafetyExtensions;
typedef struct
{
	uint8_t u8region_Present;
	WJV3_STRU_RoadRegulatorID n32region /* OPTIONAL */;
	WJV3_STRU_NodeID n32id;
} __attribute__ ((packed)) WJV3_STRU_NodeReferenceID;
typedef struct
{
	WJV3_ENUM_SpeedLimitType enumtype;
	WJV3_STRU_Speed n32speed;
} __attribute__ ((packed)) WJV3_STRU_RegulatorySpeedLimit;
typedef struct
{
	uint8_t u8RegulatorySpeedLimitNum; /* 1 ~ 9 */
	WJV3_STRU_RegulatorySpeedLimit struRegulatorySpeedLimitlist[WJV3_MAX_REGULATORYSPEEDLIMIT_NUM];
} __attribute__ ((packed)) WJV3_STRU_SpeedLimitList;
typedef struct
{
	WJV3_STRU_PositionOffsetLLV struposOffset;
} __attribute__ ((packed)) WJV3_STRU_RoadPoint;
typedef struct
{
	uint8_t u8RoadPointNum; /* 2 ~ 31 */
	WJV3_STRU_RoadPoint struRoadPointlist[WJV3_MAX_ROADPOINT_NUM];
} __attribute__ ((packed)) WJV3_STRU_PointList;
typedef struct
{
	WJV3_STRU_NodeReferenceID struremoteIntersection;
	uint8_t u8phaseId_Present;
	WJV3_STRU_PhaseID n32phaseId; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_Movement;
typedef struct
{
	uint8_t u8MovementNum; /* 1 ~ 32 */
	WJV3_STRU_Movement struMovementlist[WJV3_MAX_MOVEMENT_NUM];
} __attribute__ ((packed)) WJV3_STRU_MovementList;
typedef enum
{
	WJV3_LaneTypeAttributes_PR_NOTHING, /* No components present */
	WJV3_LaneTypeAttributes_PR_vehicle,
	WJV3_LaneTypeAttributes_PR_crosswalk,
	WJV3_LaneTypeAttributes_PR_bikeLane,
	WJV3_LaneTypeAttributes_PR_sidewalk,
	WJV3_LaneTypeAttributes_PR_median,
	WJV3_LaneTypeAttributes_PR_striping,
	WJV3_LaneTypeAttributes_PR_trackedVehicle,
	WJV3_LaneTypeAttributes_PR_parking,
} WJV3_ENUM_LaneTypeAttributes_PR;
typedef struct
{
	WJV3_ENUM_LaneTypeAttributes_PR enumpresent;
	union
	{
		union
		{
		#define WJV3_LEN_BITSTR_VEHICLE 7
		#define WJV3_LEN_BYTE_VEHICLE 1
			uint8_t u8vehicle[WJV3_LEN_BYTE_VEHICLE];
			struct
			{
				uint8_t bit_LaneAttributes_Vehicle_isVehicleRevocableLane   :1;
				uint8_t bit_LaneAttributes_Vehicle_isVehicleFlyOverLane     :1;
				uint8_t bit_LaneAttributes_Vehicle_hovLaneUseOnly           :1;
				uint8_t bit_LaneAttributes_Vehicle_restrictedToBusUse       :1;
				uint8_t bit_LaneAttributes_Vehicle_restrictedToTaxiUse      :1;
				uint8_t bit_LaneAttributes_Vehicle_restrictedFromPublicUse  :1;
				uint8_t bit_LaneAttributes_Vehicle_hasIRbeaconCoverage      :1;
				uint8_t bit_LaneAttributes_Vehicle_permissionOnRequest      :1;
			};
		}u1;
		union
		{
		#define WJV3_LEN_BITSTR_CROSSWALK 16
		#define WJV3_LEN_BYTE_CROSSWALK 2
			uint8_t u8crosswalk[WJV3_LEN_BYTE_CROSSWALK];
			struct
			{
				uint16_t bit_LaneAttributes_Crosswalk_crosswalkRevocableLane         :1;
				uint16_t bit_LaneAttributes_Crosswalk_bicyleUseAllowed               :1;
				uint16_t bit_LaneAttributes_Crosswalk_isXwalkFlyOverLane             :1;
				uint16_t bit_LaneAttributes_Crosswalk_fixedCycleTime                 :1;
				uint16_t bit_LaneAttributes_Crosswalk_biDirectionalCycleTimes        :1;
				uint16_t bit_LaneAttributes_Crosswalk_hasPushToWalkButton            :1;
				uint16_t bit_LaneAttributes_Crosswalk_audioSupport                   :1;
				uint16_t bit_LaneAttributes_Crosswalk_rfSignalRequestPresent         :1;
				uint16_t bit_LaneAttributes_Crosswalk_unsignalizedSegmentsPresent    :1;
				uint16_t bit_LaneAttributes_Crosswalk_reserved                       :7;
			};
		}u2;
		union
		{
		#define WJV3_LEN_BITSTR_BIKELANE 16
		#define WJV3_LEN_BYTE_BIKELANE 2
			uint8_t u8bikeLane[WJV3_LEN_BYTE_BIKELANE];
			struct
			{
				uint16_t bit_LaneAttributes_Bike_bikeRevocableLane            :1;
				uint16_t bit_LaneAttributes_Bike_pedestrianUseAllowed         :1;
				uint16_t bit_LaneAttributes_Bike_isBikeFlyOverLane            :1;
				uint16_t bit_LaneAttributes_Bike_fixedCycleTime               :1;
				uint16_t bit_LaneAttributes_Bike_biDirectionalCycleTimes      :1;
				uint16_t bit_LaneAttributes_Bike_isolatedByBarrier            :1;
				uint16_t bit_LaneAttributes_Bike_unsignalizedSegmentsPresent  :1;
				uint16_t bit_LaneAttributes_Bike_reserved1                    :1;
				uint16_t bit_LaneAttributes_Bike_reserved2                    :8;
			};
		}u3;
		union
		{
		#define WJV3_LEN_BITSTR_SAIDWALK 16
		#define WJV3_LEN_BYTE_SAIDWALK 2
			uint8_t u8sidewalk[WJV3_LEN_BYTE_SAIDWALK];
			struct
			{
				uint16_t bit_LaneAttributes_Sidewalk_sidewalk_RevocableLane      :1;
				uint16_t bit_LaneAttributes_Sidewalk_bicyleUseAllowed            :1;
				uint16_t bit_LaneAttributes_Sidewalk_isSidewalkFlyOverLane       :1;
				uint16_t bit_LaneAttributes_Sidewalk_walkBikes                   :1;
				uint16_t bit_LaneAttributes_Sidewalk_reserved1                   :4;
				uint16_t bit_LaneAttributes_Sidewalk_reserved2                   :8;
			};
		}u4;
		union
		{
		#define WJV3_LEN_BITSTR_BARRIER 16
		#define WJV3_LEN_BYTE_BARRIER 2
			uint8_t u8median[WJV3_LEN_BYTE_BARRIER];
			struct
			{
				uint16_t bit_LaneAttributes_Barrier_median_RevocableLane         :1;
				uint16_t bit_LaneAttributes_Barrier_median                       :1;
				uint16_t bit_LaneAttributes_Barrier_whiteLineHashing             :1;
				uint16_t bit_LaneAttributes_Barrier_stripedLines                 :1;
				uint16_t bit_LaneAttributes_Barrier_doubleStripedLines           :1;
				uint16_t bit_LaneAttributes_Barrier_trafficCones                 :1;
				uint16_t bit_LaneAttributes_Barrier_constructionBarrier          :1;
				uint16_t bit_LaneAttributes_Barrier_trafficChannels              :1;
				uint16_t bit_LaneAttributes_Barrier_lowCurbs                     :1;
				uint16_t bit_LaneAttributes_Barrier_highCurbs                    :1;
				uint16_t bit_LaneAttributes_Barrier_reserved                     :6;
			};
		}u5;
		union
		{
		#define WJV3_LEN_BITSTR_STRIP 16
		#define WJV3_LEN_BYTE_STRIP 2
			uint8_t u8striping[WJV3_LEN_BYTE_STRIP];
			struct
			{
				uint16_t bit_LaneAttributes_Striping_stripeToConnectingLanesRevocableLane    :1;
				uint16_t bit_LaneAttributes_Striping_stripeDrawOnLeft                        :1;
				uint16_t bit_LaneAttributes_Striping_stripeDrawOnRight                       :1;
				uint16_t bit_LaneAttributes_Striping_stripeToConnectingLanesLeft             :1;
				uint16_t bit_LaneAttributes_Striping_stripeToConnectingLanesRight            :1;
				uint16_t bit_LaneAttributes_Striping_stripeToConnectingLanesAhead            :1;
				uint16_t bit_LaneAttributes_Striping_reserved1                               :2;
				uint16_t bit_LaneAttributes_Striping_reserved2                               :8;
			};
		}u6;
		union
		{
		#define WJV3_LEN_BITSTR_TRACKVEH 16
		#define WJV3_LEN_BYTE_TRACKVEH 2
			uint8_t u8trackedVehicle[WJV3_LEN_BYTE_TRACKVEH];
			struct
			{
				uint16_t bit_LaneAttributes_TrackedVehicle_spec_RevocableLane                :1;
				uint16_t bit_LaneAttributes_TrackedVehicle_spec_commuterRailRoadTrack        :1;
				uint16_t bit_LaneAttributes_TrackedVehicle_spec_lightRailRoadTrack           :1;
				uint16_t bit_LaneAttributes_TrackedVehicle_spec_heavyRailRoadTrack           :1;
				uint16_t bit_LaneAttributes_TrackedVehicle_spec_otherRailType                :1;
				uint16_t bit_LaneAttributes_TrackedVehicle_reserved1                         :3;
				uint16_t bit_LaneAttributes_TrackedVehicle_reserved2                         :8;
			};
		}u7;
		union
		{
		#define WJV3_LEN_BITSTR_PARK 16
		#define WJV3_LEN_BYTE_PARK 2
			uint8_t u8parking[WJV3_LEN_BYTE_PARK];
			struct
			{
				uint16_t bit_LaneAttributes_Parking_parkingRevocableLane                  :1;
				uint16_t bit_LaneAttributes_Parking_parallelParkingInUse                  :1;
				uint16_t bit_LaneAttributes_Parking_headInParkingInUse                    :1;
				uint16_t bit_LaneAttributes_Parking_doNotParkZone                         :1;
				uint16_t bit_LaneAttributes_Parking_parkingForBusUse                      :1;
				uint16_t bit_LaneAttributes_Parking_parkingForTaxiUse                     :1;
				uint16_t bit_LaneAttributes_Parking_noPublicParkingUse                    :1;
				uint16_t bit_LaneAttributes_Parking_reserved1                             :1;
				uint16_t bit_LaneAttributes_Parking_reserved2                             :8;
			};
		}u8;
	} choice;
} __attribute__ ((packed)) WJV3_STRU_LaneTypeAttributes;
typedef struct
{
	uint8_t u8shareWith_Present;
	union
	{
	#define WJV3_LEN_BITSTR_SHAREWITH 10
	#define WJV3_LEN_BYTE_SHAREWITH 2
		uint8_t u8shareWith[WJV3_LEN_BYTE_SHAREWITH]; /* OPTIONAL */
		struct
		{
			uint16_t    bit_LaneSharing_overlappingLaneDescriptionProvided        :1;
			uint16_t    bit_LaneSharing_multipleLanesTreatedAsOneLane             :1;
			uint16_t    bit_LaneSharing_otherNonMotorizedTrafficTypes             :1;
			uint16_t    bit_LaneSharing_individualMotorizedVehicleTraffic         :1;
			uint16_t    bit_LaneSharing_busVehicleTraffic                         :1;
			uint16_t    bit_LaneSharing_taxiVehicleTraffic                        :1;
			uint16_t    bit_LaneSharing_pedestriansTraffic                        :1;
			uint16_t    bit_LaneSharing_cyclistVehicleTraffic                     :1;
			uint16_t    bit_LaneSharing_trackedVehicleTraffic                     :1;
			uint16_t    bit_LaneSharing_pedestrianTraffic                         :1;
			uint16_t    bit_LaneSharing_reserved                                  :6;
		};
	}u;
	WJV3_STRU_LaneTypeAttributes strulaneType;
} __attribute__ ((packed)) WJV3_STRU_LaneAttributes;
typedef struct
{
	WJV3_STRU_LaneID n32lane;
	uint8_t u8maneuver_Present;
	union
	{
	#define WJV3_LEN_BITSTR_MANEUVER 12
	#define WJV3_LEN_BYTE_MANEUVER 2
		uint8_t u8maneuver[WJV3_LEN_BYTE_MANEUVER]; /* OPTIONAL */
		struct
		{
			uint16_t bit_AllowedManeuvers_maneuverStraightAllowed            :1;
			uint16_t bit_AllowedManeuvers_maneuverLeftAllowed                :1;
			uint16_t bit_AllowedManeuvers_maneuverRightAllowed               :1;
			uint16_t bit_AllowedManeuvers_maneuverUTurnAllowed               :1;
			uint16_t bit_AllowedManeuvers_maneuverLeftTurnOnRedAllowed       :1;
			uint16_t bit_AllowedManeuvers_maneuverRightTurnOnRedAllowed      :1;
			uint16_t bit_AllowedManeuvers_maneuverLaneChangeAllowed          :1;
			uint16_t bit_AllowedManeuvers_maneuverNoStoppingAllowed          :1;
			uint16_t bit_AllowedManeuvers_yieldAllwaysRequired               :1;
			uint16_t bit_AllowedManeuvers_goWithHalt                         :1;
			uint16_t bit_AllowedManeuvers_caution                            :1;
			uint16_t bit_AllowedManeuvers_reserved                           :4;
		};
	}u;
} __attribute__ ((packed)) WJV3_STRU_ConnectingLane;
typedef struct
{
	WJV3_STRU_NodeReferenceID struremoteIntersection;
	uint8_t u8connectingLane_Present;
	WJV3_STRU_ConnectingLane struconnectingLane; /* OPTIONAL */
	uint8_t u8phase_Present;
	WJV3_STRU_PhaseID n32phaseId; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_Connection;
typedef struct
{
	uint8_t u8ConnectNum; /* 1 ~ 8 */
	WJV3_STRU_Connection struConnectionlist[WJV3_MAX_CONNECT_NUM];
} __attribute__ ((packed)) WJV3_STRU_ConnectsToList;
typedef struct
{
	WJV3_STRU_LaneID n32laneID;
	uint8_t u8laneAttributes_Present;
	WJV3_STRU_LaneAttributes strulaneAttributes; /* OPTIONAL */
	uint8_t u8maneuvers_Present;
	union
	{
	#define WJV3_LEN_BITSTR_MANEUVERS 12
	#define WJV3_LEN_BYTE_MANEUVERS 2
		uint8_t u8maneuvers[WJV3_LEN_BYTE_MANEUVERS]; /* OPTIONAL */
		struct
		{
			uint16_t bit_AllowedManeuvers_maneuverStraightAllowed            :1;
			uint16_t bit_AllowedManeuvers_maneuverLeftAllowed                :1;
			uint16_t bit_AllowedManeuvers_maneuverRightAllowed               :1;
			uint16_t bit_AllowedManeuvers_maneuverUTurnAllowed               :1;
			uint16_t bit_AllowedManeuvers_maneuverLeftTurnOnRedAllowed       :1;
			uint16_t bit_AllowedManeuvers_maneuverRightTurnOnRedAllowed      :1;
			uint16_t bit_AllowedManeuvers_maneuverLaneChangeAllowed          :1;
			uint16_t bit_AllowedManeuvers_maneuverNoStoppingAllowed          :1;
			uint16_t bit_AllowedManeuvers_yieldAllwaysRequired               :1;
			uint16_t bit_AllowedManeuvers_goWithHalt                         :1;
			uint16_t bit_AllowedManeuvers_caution                            :1;
			uint16_t bit_AllowedManeuvers_reserved                           :4;
		};
	}u;
	uint8_t u8connectsTo_Present;
	WJV3_STRU_ConnectsToList struconnectsTo; /* OPTIONAL */
	uint8_t u8speedLimits_Present;
	WJV3_STRU_SpeedLimitList struspeedLimits; /* OPTIONAL */
	uint8_t u8points_Present;
	WJV3_STRU_PointList strupoints; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_Lane;
typedef struct
{
	uint8_t u8LaneNum; /* 1 ~ 32 */
	WJV3_STRU_Lane struLanelist[WJV3_MAX_LANE_NUM];
} __attribute__ ((packed)) WJV3_STRU_LaneList;
typedef struct
{
	uint8_t u8nameNum;					   /* 0 is Absent*/
	uint8_t u8name[WJV3_MAX_IA5_NAME_LEN]; /* OPTIONAL */
	WJV3_STRU_NodeReferenceID struupstreamNodeId;
	uint8_t u8speedLimits_Present;
	WJV3_STRU_SpeedLimitList struspeedLimits; /* OPTIONAL */
	WJV3_STRU_LaneWidth n32laneWidth;
	uint8_t u8points_Present;
	WJV3_STRU_PointList strupoints; /* OPTIONAL */
	uint8_t u8movements_Present;
	WJV3_STRU_MovementList strumovements; /* OPTIONAL */
	WJV3_STRU_LaneList strulanes;
} __attribute__ ((packed)) WJV3_STRU_Link;
typedef struct
{
	uint8_t u8LinkNum; /* 1 ~ 32 */
	WJV3_STRU_Link struLinklist[WJV3_MAX_LINK_NUM];
} __attribute__ ((packed)) WJV3_STRU_LinkList;
typedef struct
{
	uint8_t u8nameNum;					 /* 0 is Absent*/
	uint8_t u8name[WJV3_MAX_IA5_NAME_LEN]; /* OPTIONAL */
	WJV3_STRU_NodeReferenceID struid;
	WJV3_STRU_Position3D strurefPos;
	uint8_t u8inLinks_Present;
	WJV3_STRU_LinkList inLinks; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_Node;
typedef struct
{
	uint8_t u8NodeNum; /* 1 ~ 32 */
	WJV3_STRU_Node struNodelist[WJV3_MAX_NODE_NUM];
} __attribute__ ((packed)) WJV3_STRU_NodeList;
typedef enum
{
	WJV3_ParticipantType_unknown = 0,
	WJV3_ParticipantType_motor = 1,
	WJV3_ParticipantType_non_motor = 2,
	WJV3_ParticipantType_pedestrian = 3,
	WJV3_ParticipantType_rsu = 4
} WJV3_ENUM_ParticipantType;
typedef enum
{
	WJV3_SourceType_unknown = 0,
	WJV3_SourceType_selfinfo = 1,
	WJV3_SourceType_v2x = 2,
	WJV3_SourceType_video = 3,
	WJV3_SourceType_microwaveRadar = 4,
	WJV3_SourceType_loop = 5,
	WJV3_SourceType_microwmixRadar = 6
} WJV3_ENUM_SourceType;
typedef struct
{
	WJV3_ENUM_ParticipantType enumptcType;
	int32_t n32ptcId; /* 0 ~ 65535 0 is itself*/
	WJV3_ENUM_SourceType enumsource;
	uint8_t u8Id_Present;
	uint8_t u8Id[WJV3_MAX_BYTE_ID_LEN]; /* OPTIONAL octstring is 8 */
	uint8_t u8plateNo_Present;
	uint8_t u8plateNo[WJV3_MAX_BYTE_PLATNO_LEN]; /* OPTIONAL octstring is 16 */
	WJV3_STRU_DSecond n32secMark;
	WJV3_STRU_PositionOffsetLLV strupos;
	WJV3_STRU_PositionConfidenceSet struaccuracy;
	uint8_t u8transmission_Present;
	WJV3_ENUM_TransmissionState enumtransmission; /* OPTIONAL */
	WJV3_STRU_Speed n32speed;
	WJV3_STRU_Heading n32heading;
	uint8_t u8angle_Present;
	WJV3_STRU_SteeringWheelAngle n32angle; /* OPTIONAL */
	uint8_t u8motionCfd_Present;
	WJV3_STRU_MotionConfidenceSet strumotionCfd; /* OPTIONAL */
	uint8_t u8accelSet_Present;
	WJV3_STRU_AccelerationSet4Way struaccelSet; /* OPTIONAL */
	WJV3_STRU_VehicleSize strusize;
	uint8_t u8vehicleClass_Present;
	WJV3_STRU_VehicleClassification struvehicleClass; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_ParticipantData;
typedef struct
{
	uint8_t u8ParticipantNum; /* 1 ~ 16 */
	WJV3_STRU_ParticipantData struParticipantDatalist[WJV3_MAX_PARTICIPANT_NUM];
} __attribute__ ((packed)) WJV3_STRU_ParticipantList;
typedef struct
{
	WJV3_STRU_TimeMark n32startTime;
	uint8_t u8minEndTime_Present;
	WJV3_STRU_TimeMark n32minEndTime; /* OPTIONAL */
	uint8_t u8maxEndTime_Present;
	WJV3_STRU_TimeMark n32maxEndTime; /* OPTIONAL */
	WJV3_STRU_TimeMark n32likelyEndTime;
	uint8_t u8timeConfidence_Present;
	WJV3_STRU_Confidence n32timeConfidence; /* OPTIONAL */
	uint8_t u8nextStartTime_Present;
	WJV3_STRU_TimeMark n32nextStartTime; /* OPTIONAL */
	uint8_t u8nextDuration_Present;
	WJV3_STRU_TimeMark n32nextDuration; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_TimeChangeDetails;
typedef struct
{
	WJV3_ENUM_LightState enumlight;
	uint8_t u8timing_Present;
	WJV3_STRU_TimeChangeDetails strutiming; /* OPTIONAL */
} __attribute__ ((packed)) WJV3_STRU_PhaseState;
typedef struct
{
	uint8_t u8PhaseStateNum; /* 1 ~ 16 */
	WJV3_STRU_PhaseState struPhaseStatelist[WJV3_MAX_PHASESTATE_NUM];
} __attribute__ ((packed)) WJV3_STRU_PhaseStateList;
typedef struct
{
	WJV3_STRU_PhaseID n32id;
	WJV3_STRU_PhaseStateList struphaseStates;
} __attribute__ ((packed)) WJV3_STRU_Phase;
typedef struct
{
	uint8_t u8PhaseNum; /* 1 ~ 16 */
	WJV3_STRU_Phase struPhaselist[WJV3_MAX_PHASE_NUM];
} __attribute__ ((packed)) WJV3_STRU_PhaseList;
typedef struct
{
	WJV3_STRU_NodeReferenceID struintersectionId;
	union
	{
	#define WJV3_LEN_BITSTR_INTERSECTIONSTATEOBJ 16
	#define WJV3_LEN_BYTE_INTERSECTIONSTATEOBJ 2
		uint8_t u8status[WJV3_LEN_BYTE_INTERSECTIONSTATEOBJ];
		struct
		{
			uint16_t    bit_InterStatusObj_manualControlIsEnabled             :1;
			uint16_t    bit_InterStatusObj_stopTimeIsActivated                :1;
			uint16_t    bit_InterStatusObj_failureFlash                       :1;
			uint16_t    bit_InterStatusObj_preemptIsActive                    :1;
			uint16_t    bit_InterStatusObj_signalPriorityIsActive             :1;
			uint16_t    bit_InterStatusObj_fixedTimeOperation                 :1;
			uint16_t    bit_InterStatusObj_trafficDependentOperation          :1;
			uint16_t    bit_InterStatusObj_standbyOperation                   :1;
			uint16_t    bit_InterStatusObj_failureMode                        :1;
			uint16_t    bit_InterStatusObj_off                                :1;
			uint16_t    bit_InterStatusObj_recentMAPmessageUpdate             :1;
			uint16_t 	bit_InterStatusObj_recentChangeInMAPassignedLanesIDsUsed :1;
			uint16_t	bit_InterStatusObj_noValidMAPisAvailableAtThisTime    :1;
			uint16_t	bit_InterStatusObj_noValidSPATisAvailableAtThisTime   :1;
			uint16_t	bit_InterStatusObj_reserved                           :2;
		};
	}u;
	uint8_t u8moy_Present;
	WJV3_STRU_MinuteOfTheYear n32moy; /* OPTIONAL */
	uint8_t u8timeStamp_Present;
	WJV3_STRU_DSecond n32timeStamp; /* OPTIONAL */
	WJV3_STRU_PhaseList struphases;
} __attribute__ ((packed)) WJV3_STRU_IntersectionState;
typedef struct
{
	uint8_t u8IntersectionStateNum; /* 1 ~ 32 */
	WJV3_STRU_IntersectionState struIntersectionStatelist[WJV3_MAX_INTERSECTIONSTATE_NUM];
} __attribute__ ((packed)) WJV3_STRU_IntersectionStateList;
typedef struct
{
	uint8_t u8PositionOffsetLLVNum; /* 2 ~ 32 */
	WJV3_STRU_PositionOffsetLLV struPositionOffsetLLVlist[WJV3_MAX_POSITIONOFFSETLLV_NUM];
} __attribute__ ((packed)) WJV3_STRU_PathPointList;
#endif /* end of file */