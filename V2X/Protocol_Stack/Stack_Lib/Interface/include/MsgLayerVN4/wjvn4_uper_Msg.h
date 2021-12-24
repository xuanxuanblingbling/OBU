/**
* @file         :wjvn4_uper_Msg.h
* @brief        :消息帧相关结构体头文件定义
* @details      :主要包含消息帧结构相关结构体定义
* @author       :huangsai  any question please send mail to huangsai@wanji.net.cn
* @date         :2020-12-16
* @version      :V1.0
* @copyright    :Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：IMX6
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-16  <td>V1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
#ifndef __WJVN4_UPER_MSG_H_
#define __WJVN4_UPER_MSG_H_
/*********************************头文件包含********************************************/
#include "wjvn4_uper_Df.h"
/*********************************标准头文件********************************************/

/*********************************自定义头文件******************************************/
#define WJVN4_MAX_ID_SIZE 8
typedef enum
{
    MSGVN4_MessageFrame_ID_BSM_en = 1,                  /* 普通BSM消息,若不存在以下四种BSM,则为普通BSM */
    MSGVN4_MessageFrame_ID_BSM_OrdinaryConven_en = 101, /* 普通车辆+常规型 */
    MSGVN4_MessageFrame_ID_BSM_OrdinaryEvent_en = 102,  /* 普通车辆+事件型 */
    MSGVN4_MessageFrame_ID_BSM_SpecialConven_en = 103,  /* 特殊车辆+常规型 */
    MSGVN4_MessageFrame_ID_BSM_SpecialEvent_en = 104,   /* 特殊车辆+事件型 */
    MSGVN4_MessageFrame_ID_MAPDATA_en = 2,              /* MAP消息 */
    MSGVN4_MessageFrame_ID_RSM_en = 3,                  /* RSM消息 */
    MSGVN4_MessageFrame_ID_SPAT_en = 4,                 /* SPAT消息 */
    MSGVN4_MessageFrame_ID_RSI_en = 5,                  /* 普通RSI消息,若不存在以下三种RSI,则为普通RSI */
    MSGVN4_MessageFrame_ID_RSI_RoadStatic_en = 501,     /* 道路信息-静态类应用 */
    MSGVN4_MessageFrame_ID_RSI_RoadHalfStatic_en = 502, /* 道路信息-半静态类应用 */
    MSGVN4_MessageFrame_ID_RSI_RoadDynamic_en = 503     /* 道路信息-动态类应用 */
} WJVN4_ENUM_MessageFrame_PR;
typedef struct _vn4BasicSafetyMessage
{
    WJVN4_INT_MsgCount n32msgCnt;
    uint8_t u8OCTid[WJVN4_MAX_ID_SIZE];
    WJVN4_INT_DSecond n32secMark;
    uint8_t u8timeConfidencePresent;
    WJVN4_ENUM_TimeConfidence enumtimeConfidence;  /* OPTIONAL */
    WJVN4_STRU_Position3D strupos;
    uint8_t u8posAccuracyPresent;
    WJVN4_STRU_PositionalAccuracy struposAccuracy;  /* OPTIONAL */
    uint8_t u8posConfidencePresent;
    WJVN4_STRU_PositionConfidenceSet struposConfidence;  /* OPTIONAL */
    WJVN4_ENUM_TransmissionState enumtransmission;
    WJVN4_INT_Speed n32speed;
    WJVN4_INT_Heading n32heading;
    uint8_t u8anglePresent;
    WJVN4_INT_SteeringWheelAngle n32angle;   /* OPTIONAL */
    uint8_t u8MotionConfidenceSetPresent;
    WJVN4_STRU_MotionConfidenceSet strumotionCfd; /* OPTIONAL */
    WJVN4_STRU_AccelerationSet4Way struaccelSet;
    WJVN4_STRU_BrakeSystemStatus strubrakes;
    WJVN4_STRU_VehicleSize strusize;
    WJVN4_STRU_VehicleClassification struvehicleClass;
    uint8_t u8safetyExtPresent;
    WJVN4_STRU_VehicleSafetyExtensions strusafetyExt;   /* OPTIONAL */
    uint8_t u8emergencyExtPresent;
    WJVN4_STRU_VehicleEmergencyExtensions struemergencyExt;   /* OPTIONAL */
} __attribute__ ((packed)) WJVN4_STRU_BasicSafetyMessage;   /* 车辆基本安全消息 */
typedef struct _vn4MapData
{
    WJVN4_INT_MsgCount n32msgCnt;
    uint8_t u8timeStampPresent;
    WJVN4_INT_MinuteOfTheYear n32timeStamp; /* OPTIONAL */
    WJVN4_STRU_NodeList strunodes;
} __attribute__ ((packed)) WJVN4_STRU_MapData; /* 地图消息 */
typedef struct _vn4RoadSideInformation
{
    WJVN4_INT_MsgCount n32msgCnt;
    uint8_t u8moyPresent;
    WJVN4_INT_MinuteOfTheYear n32moy; /* OPTIONAL */
    uint8_t u8OCTid[WJVN4_MAX_ID_SIZE];
    WJVN4_STRU_Position3D strurefPos;
    uint8_t u8rtesPresent;
    WJVN4_STRU_RTEList strurtes; /* OPTIONAL */
    uint8_t u8rtssPresent;
    WJVN4_STRU_RTSList strurtss; /* OPTIONAL */
} __attribute__ ((packed)) WJVN4_STRU_RoadSideInformation; /* 交通事件信息以及交通标志信息 */
typedef struct _vn4RoadsideSafetyMessage
{
    WJVN4_INT_MsgCount n32msgCnt;
    uint8_t u8OCTid[WJVN4_MAX_ID_SIZE];
    WJVN4_STRU_Position3D strurefPos;
    WJVN4_STRU_ParticipantList struparticipants;
} __attribute__ ((packed)) WJVN4_STRU_RoadsideSafetyMessage; /* 路侧安全消息 */
typedef struct _vn4SPAT
{
    WJVN4_INT_MsgCount n32msgCnt;
    uint8_t u8moyPresent;
    WJVN4_INT_MinuteOfTheYear n32moy; /* OPTIONAL */
    uint8_t u8timeStampPresent;
    WJVN4_INT_DSecond n32timeStamp;   /* OPTIONAL */
    uint8_t u8namePresent;
    WJVN4_IA5_DescriptiveName stria5name;   /* OPTIONAL */
    WJVN4_STRU_IntersectionStateList struintersections;
} __attribute__ ((packed)) WJVN4_STRU_SPAT;  /* 信号灯消息 */
/****************************************************************************************/
/* 内部函数声明 */
/****************************************************************************************/
#endif /* 文件结束 */