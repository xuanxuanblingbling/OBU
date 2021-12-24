/**
* @file         :wjv2_uper_Msg.h
* @brief        :消息帧相关结构体头文件定义
* @details      :主要包含消息帧结构相关结构体定义
* @author       :WM  any question please send mail to WM@wanji.net.cn
* @date         :2020-12-16
* @version      :V1.0
* @copyright    :Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：IMX6
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-16  <td>V1.0      <td>WM  <td>创建初始版本
* </table>
**********************************************************************************
*/
#ifndef __WJV2_UPER_MSG_H_
#define __WJV2_UPER_MSG_H_
/*********************************头文件包含********************************************/
#include "wjv2_uper_Df.h"
/*********************************标准头文件********************************************/

/*********************************自定义头文件******************************************/
#define WJV2_MAX_ID_SIZE 8
#define WJV2_MIN_ID_SIZE 1

typedef enum
{
    MSGV2_MessageFrame_ID_BSM_en = 1,                  /* 普通BSM消息,若不存在以下四种BSM,则为普通BSM */
    MSGV2_MessageFrame_ID_BSM_OrdinaryConven_en = 101, /* 普通车辆+常规型 */
    MSGV2_MessageFrame_ID_BSM_OrdinaryEvent_en = 102,  /* 普通车辆+事件型 */
    MSGV2_MessageFrame_ID_BSM_SpecialConven_en = 103,  /* 特殊车辆+常规型 */
    MSGV2_MessageFrame_ID_BSM_SpecialEvent_en = 104,   /* 特殊车辆+事件型 */
    MSGV2_MessageFrame_ID_MAPDATA_en = 2,              /* MAP消息 */
    MSGV2_MessageFrame_ID_RSM_en = 3,                  /* RSM消息 */
    MSGV2_MessageFrame_ID_SPAT_en = 4,                 /* SPAT消息 */
    MSGV2_MessageFrame_ID_RSI_en = 5,                  /* 普通RSI消息,若不存在以下三种RSI,则为普通RSI */
    MSGV2_MessageFrame_ID_RSI_RoadStatic_en = 501,     /* 道路信息-静态类应用 */
    MSGV2_MessageFrame_ID_RSI_RoadHalfStatic_en = 502, /* 道路信息-半静态类应用 */
    MSGV2_MessageFrame_ID_RSI_RoadDynamic_en = 503,    /* 道路信息-动态类应用 */
    MSGV2_MessageFrame_PR_msgFrameExt = 6              /* 二期扩展消息集 */
}__attribute__ ((packed)) WJV2_ENUM_MessageFrame_PR;
typedef struct _BasicSafetyMessage
{
    WJV2_INT_MsgCount n32msgCnt;
    uint8_t u8idNum;
    uint8_t u8OCTid[WJV2_MAX_ID_SIZE];
    WJV2_INT_DSecond n32secMark;
    uint8_t u8timeConfidencePresent;
    WJV2_ENUM_TimeConfidence enumtimeConfidence; /* OPTIONAL */
    WJV2_STRU_Position3D strupos;
    uint8_t u8posAccuracyPresent;
    WJV2_STRU_PositionalAccuracy struposAccuracy; /* OPTIONAL */
    uint8_t u8posConfidencePresent;
    WJV2_STRU_PositionConfidenceSet struposConfidence; /* OPTIONAL */
    WJV2_ENUM_TransmissionState enumtransmission;
    WJV2_INT_Speed n32speed;
    WJV2_INT_Heading n32heading;
    uint8_t u8anglePresent;
    WJV2_INT_SteeringWheelAngle n32angle; /* OPTIONAL */
    uint8_t u8MotionConfidenceSetPresent;
    WJV2_STRU_MotionConfidenceSet strumotionCfd;
    WJV2_STRU_AccelerationSet4Way struaccelSet;
    WJV2_STRU_BrakeSystemStatus strubrakes;
    WJV2_STRU_VehicleSize strusize;
    WJV2_STRU_VehicleClassification struvehicleClass;
    uint8_t u8safetyExtPresent;
    WJV2_STRU_VehicleSafetyExtensions strusafetyExt; /* OPTIONAL */
    uint8_t u8emergencyExtPresent;
    WJV2_STRU_VehicleEmergencyExtensions struemergencyExt; /* OPTIONAL */
}__attribute__ ((packed)) WJV2_STRU_BasicSafetyMessage;                            /* 车辆基本安全消息 */
typedef struct _MapData
{
    WJV2_INT_MsgCount n32msgCnt;
    uint8_t u8timeStampPresent;
    WJV2_INT_MinuteOfTheYear n32timeStamp; /* OPTIONAL */
    WJV2_STRU_NodeList strunodes;
}__attribute__ ((packed)) WJV2_STRU_MapData; /* 地图消息 */
typedef struct _RoadSideInformation
{
    WJV2_INT_MsgCount n32msgCnt;
    uint8_t u8moyPresent;
    WJV2_INT_MinuteOfTheYear n32moy; /* OPTIONAL */
    uint8_t u8idNum;
    uint8_t u8OCTid[WJV2_MAX_ID_SIZE];
    WJV2_STRU_Position3D strurefPos;
    uint8_t u8rtesPresent;
    WJV2_STRU_RTEList strurtes; /* OPTIONAL */
    uint8_t u8rtssPresent;
    WJV2_STRU_RTSList strurtss;  /* OPTIONAL */
}__attribute__ ((packed)) WJV2_STRU_RoadSideInformation; /* 交通事件信息以及交通标志信息 */
typedef struct _RoadsideSafetyMessage
{
    WJV2_INT_MsgCount n32msgCnt;
    uint8_t u8OCTid[WJV2_MAX_ID_SIZE];
    WJV2_STRU_Position3D strurefPos;
    WJV2_STRU_ParticipantList struparticipants;
}__attribute__ ((packed)) WJV2_STRU_RoadsideSafetyMessage; /* 路侧安全消息 */
typedef struct _SPAT
{
    WJV2_INT_MsgCount n32msgCnt;
    uint8_t u8moyPresent;
    WJV2_INT_MinuteOfTheYear n32moy; /* OPTIONAL */
    uint8_t u8timeStampPresent;
    WJV2_INT_DSecond n32timeStamp; /* OPTIONAL */
    uint8_t u8namePresent;
    WJV2_IA5_DescriptiveName stria5name; /* OPTIONAL */
    WJV2_STRU_IntersectionStateList struintersections;
}__attribute__ ((packed)) WJV2_STRU_SPAT; /* 信号灯消息 */

/* PAMData */
typedef struct _PAMData
{
    WJV2_INT_MsgCount n32msgCnt;
    uint8_t u8timeStampPresent;
    WJV2_INT_MinuteOfTheYear n32timeStamp /* OPTIONAL */;
    WJV2_STRU_ParkingLotInfo struparkingLotInfo;
    WJV2_STRU_PAMNodeList strupamNodes;
    uint8_t u8parkingAreaGuidancePresent;
    WJV2_STRU_parkingAreaGuidance struparkingAreaGuidance; /* OPTIONAL */

}__attribute__ ((packed)) WJV2_STRU_PAMData;

/* CLPMM */
typedef struct _CLPMM
{
    WJV2_INT_MsgCount n32msgCnt;
    uint8_t u8idNum;
    uint8_t u8OCTid[WJV2_MAX_ID_SIZE];
    WJV2_INT_DSecond n32secMark;
#define WJV2_MAX_PID_SIZE 17
    uint8_t u8OCTpid[WJV2_MAX_PID_SIZE];
    WJV2_ENUM_RoleInPlatooning enumrole;
    WJV2_ENUM_StatusInPlatooning enumstatus;
    uint8_t u8leadingExtPresent;
    WJV2_STRU_MemberManagement struleadingExt /* OPTIONAL */;

}__attribute__ ((packed)) WJV2_STRU_CLPMM;

/* PersonalSafetyMessage */
typedef struct _PersonalSafetyMessage
{
    WJV2_INT_MsgCount n32msgCnt;
    uint8_t u8OCTid[WJV2_MAX_ID_SIZE];
    WJV2_INT_DSecond n32secMark;
    uint8_t u8timeConfidencePresent;
    WJV2_ENUM_TimeConfidence enumtimeConfidence /* OPTIONAL */;
    WJV2_STRU_Position3D strupos;
    WJV2_STRU_PositionalAccuracy struposAccuracy;
    WJV2_INT_Speed n32speed;
    WJV2_INT_Heading n32heading;
    uint8_t u8accelSetPresent;
    WJV2_STRU_AccelerationSet4Way struaccelSet /* OPTIONAL */;
    uint8_t u8pathHistoryPresent;
    WJV2_STRU_PathHistory strupathHistory /* OPTIONAL */;
    uint8_t u8path_PlanningPresent;
    WJV2_STRU_PathPlanning strupath_Planning /* OPTIONAL */;
#define WJV2_MAX_OVERALLRADIUS_SIZE 200
#define WJV2_MIN_OVERALLRADIUS_SIZE 0
    int32_t n32overallRadius;
    WJV2_STRU_Non_motorData strunon_motorData;

}__attribute__ ((packed)) WJV2_STRU_PersonalSafetyMessage;

/* RoadsideCoordination */
typedef struct _VehicleCoordinationList
{
    uint8_t u8coordinatesNum;
#define WJV2_MAX_LIST_COORDINATES_LEN 16
#define WJV2_MIN_LIST_COORDINATES_LEN 1
    WJV2_STRU_VehicleCoordination strucoordinates[WJV2_MAX_LIST_COORDINATES_LEN];
}__attribute__ ((packed)) WJV2_STRU_VehicleCoordinationList;
typedef struct _RoadsideCoordinationList
{
    uint8_t u8laneCoordinatesNum;
#define WJV2_MAX_LIST_LANECOORDINATES_LEN 8
#define WJV2_MIN_LIST_LANECOORDINATES_LEN 1
    WJV2_STRU_LaneCoordination strulaneCoordinates[WJV2_MAX_LIST_LANECOORDINATES_LEN];
}__attribute__ ((packed)) WJV2_STRU_LaneCoordinationList;
typedef struct _RoadsideCoordination
{
    WJV2_INT_MsgCount n32msgCnt;
    uint8_t u8OCTid[WJV2_MAX_ID_SIZE];
    WJV2_INT_DSecond n32secMark;
    WJV2_STRU_Position3D strurefPos;
    uint8_t u8coordinatesPresent;
    WJV2_STRU_VehicleCoordinationList strucoordinatesList /* OPTIONAL */;
    uint8_t u8laneCoordinatesPresent;
    WJV2_STRU_LaneCoordinationList strulaneCoordinatesList /* OPTIONAL */;

}__attribute__ ((packed)) WJV2_STRU_RoadsideCoordination;

/* SensorSharingMsg */
typedef struct _SensorSharingMsg
{
    WJV2_INT_MsgCount n32msgCnt;
    uint8_t u8OCTid[WJV2_MAX_ID_SIZE];
    WJV2_ENUM_EquipmentType enumequipmentType;
    WJV2_INT_DSecond n32secMark;
    WJV2_STRU_Position3D strusensorPos;
    uint8_t u8detectedRegionPresent;
    WJV2_STRU_DetectedRegion strudetectedRegion /* OPTIONAL */;
    uint8_t u8participantsPresent;
    WJV2_STRU_DetectedPTCList struparticipants /* OPTIONAL */;
    uint8_t u8obstaclesPresent;
    WJV2_STRU_DetectedObstacleList struobstacles /* OPTIONAL */;
    uint8_t u8rtesPresent;
    WJV2_STRU_RTEList strurtes /* OPTIONAL */;

}__attribute__ ((packed)) WJV2_STRU_SensorSharingMsg;

/* VehIntentionAndRequest */
typedef struct _VehIntentionAndRequest
{
    WJV2_INT_MsgCount n32msgCnt;
    uint8_t u8OCTid[WJV2_MAX_ID_SIZE];
    WJV2_INT_DSecond n32secMark;
    WJV2_STRU_Position3D strurefPos;
    WJV2_STRU_IARData struintAndReq;

}__attribute__ ((packed)) WJV2_STRU_VehIntentionAndRequest;

/* VehiclePaymentMessage */
typedef struct _VehiclePaymentMessage
{
    WJV2_INT_MsgCount n32msgCnt;
    WJV2_STRU_payment strupayment;

}__attribute__ ((packed)) WJV2_STRU_VehiclePaymentMessage;

/* TestMsg */
typedef struct _TestMsg
{
    WJV2_INT_MsgCount n32msgCnt;
    uint16_t u16userDataNum;
#define WJV2_MAX_userData_SIZE 2048
#define WJV2_MIN_userData_SIZE 1
    uint8_t u8OCTuserData[WJV2_MAX_userData_SIZE];

}__attribute__ ((packed)) WJV2_STRU_TestMsg;

/* RTCMcorrections */
typedef struct _RTCMcorrections
{
    WJV2_INT_MsgCount n32msgCnt;
    WJV2_STRU_corrections strucorrections;

}__attribute__ ((packed)) WJV2_STRU_RTCMcorrections;

/* Dependencies */
typedef enum _value_PR
{
    WJV2_value_PR_TestMsg = 7,
    WJV2_value_PR_RTCMcorrections = 8,
    WJV2_value_PR_PAMData = 9,
    WJV2_value_PR_CLPMM = 10,
    WJV2_value_PR_PersonalSafetyMessage = 11,
    WJV2_value_PR_RoadsideCoordination = 12,
    WJV2_value_PR_SensorSharingMsg = 13,
    WJV2_value_PR_VehIntentionAndRequest = 14,
    WJV2_value_PR_VehiclePaymentMessage = 15
}__attribute__ ((packed)) WJV2_ENUM_value_PR;

typedef struct _value
{

    WJV2_ENUM_value_PR enumpresent;
    union WJV2_MessageFrameExt__value_u
    {
        WJV2_STRU_TestMsg struTestMsg;
        WJV2_STRU_RTCMcorrections struRTCMcorrections;
        WJV2_STRU_PAMData struPAMData;
        WJV2_STRU_CLPMM struCLPMM;
        WJV2_STRU_PersonalSafetyMessage struPersonalSafetyMessage;
        WJV2_STRU_RoadsideCoordination struRoadsideCoordination;
        WJV2_STRU_SensorSharingMsg struSensorSharingMsg;
        WJV2_STRU_VehIntentionAndRequest struVehIntentionAndRequest;
        WJV2_STRU_VehiclePaymentMessage struVehiclePaymentMessage;
    } choice;

}__attribute__ ((packed)) WJV2_STRU_MessageFrameExt;
/****************************************************************************************/
/* 内部函数声明 */
/****************************************************************************************/
#endif /* 文件结束 */