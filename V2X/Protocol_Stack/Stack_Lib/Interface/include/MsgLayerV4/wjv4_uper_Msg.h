/**
* @file         :wjv4_uper_Msg.h
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
#ifndef __WJV4_UPER_MSG_H_
#define __WJV4_UPER_MSG_H_
/*********************************头文件包含********************************************/
#include "wjv4_uper_Df.h"
/*********************************标准头文件********************************************/

/*********************************自定义头文件******************************************/
#define WJV4_MAX_ID_SIZE 8
typedef enum
{
    MSGV4_MessageFrame_ID_BSM_en = 1,                  /* 普通BSM消息,若不存在以下四种BSM,则为普通BSM */
    MSGV4_MessageFrame_ID_BSM_OrdinaryConven_en = 101, /* 普通车辆+常规型 */
    MSGV4_MessageFrame_ID_BSM_OrdinaryEvent_en = 102,  /* 普通车辆+事件型 */
    MSGV4_MessageFrame_ID_BSM_SpecialConven_en = 103,  /* 特殊车辆+常规型 */
    MSGV4_MessageFrame_ID_BSM_SpecialEvent_en = 104,   /* 特殊车辆+事件型 */
    MSGV4_MessageFrame_ID_MAPDATA_en = 2,              /* MAP消息 */
    MSGV4_MessageFrame_ID_RSM_en = 3,                  /* RSM消息 */
    MSGV4_MessageFrame_ID_SPAT_en = 4,                 /* SPAT消息 */
    MSGV4_MessageFrame_ID_RSI_en = 5,                  /* 普通RSI消息,若不存在以下三种RSI,则为普通RSI */
    MSGV4_MessageFrame_ID_RSI_RoadStatic_en = 501,     /* 道路信息-静态类应用 */
    MSGV4_MessageFrame_ID_RSI_RoadHalfStatic_en = 502, /* 道路信息-半静态类应用 */
    MSGV4_MessageFrame_ID_RSI_RoadDynamic_en = 503     /* 道路信息-动态类应用 */
} WJV4_ENUM_MessageFrame_PR;
typedef struct _v4BasicSafetyMessage
{
    WJV4_INT_MsgCount n32msgCnt;
    uint8_t u8OCTid[WJV4_MAX_ID_SIZE];
    WJV4_INT_DSecond n32secMark;
    uint8_t u8timeConfidencePresent;
    WJV4_ENUM_TimeConfidence enumtimeConfidence;  /* OPTIONAL */
    WJV4_STRU_Position3D strupos;
    uint8_t u8posAccuracyPresent;
    WJV4_STRU_PositionalAccuracy struposAccuracy;  /* OPTIONAL */
    uint8_t u8posConfidencePresent;
    WJV4_STRU_PositionConfidenceSet struposConfidence;  /* OPTIONAL */
    WJV4_ENUM_TransmissionState enumtransmission;
    WJV4_INT_Speed n32speed;
    WJV4_INT_Heading n32heading;
    uint8_t u8anglePresent;
    WJV4_INT_SteeringWheelAngle n32angle;   /* OPTIONAL */
    uint8_t u8MotionConfidenceSetPresent;
    WJV4_STRU_MotionConfidenceSet strumotionCfd; /* OPTIONAL */
    WJV4_STRU_AccelerationSet4Way struaccelSet;
    WJV4_STRU_BrakeSystemStatus strubrakes;
    WJV4_STRU_VehicleSize strusize;
    WJV4_STRU_VehicleClassification struvehicleClass;
    uint8_t u8safetyExtPresent;
    WJV4_STRU_VehicleSafetyExtensions strusafetyExt;   /* OPTIONAL */
    uint8_t u8emergencyExtPresent;
    WJV4_STRU_VehicleEmergencyExtensions struemergencyExt;   /* OPTIONAL */
} __attribute__ ((packed)) WJV4_STRU_BasicSafetyMessage;   /* 车辆基本安全消息 */
typedef struct _v4MapData
{
    WJV4_INT_MsgCount n32msgCnt;
    uint8_t u8timeStampPresent;
    WJV4_INT_MinuteOfTheYear n32timeStamp; /* OPTIONAL */
    WJV4_STRU_NodeList strunodes;
} __attribute__ ((packed)) WJV4_STRU_MapData; /* 地图消息 */
typedef struct _v4RoadSideInformation
{
    WJV4_INT_MsgCount n32msgCnt;
    uint8_t u8moyPresent;
    WJV4_INT_MinuteOfTheYear n32moy; /* OPTIONAL */
    uint8_t u8OCTid[WJV4_MAX_ID_SIZE];
    WJV4_STRU_Position3D strurefPos;
    uint8_t u8rtesPresent;
    WJV4_STRU_RTEList strurtes; /* OPTIONAL */
    uint8_t u8rtssPresent;
    WJV4_STRU_RTSList strurtss; /* OPTIONAL */
} __attribute__ ((packed)) WJV4_STRU_RoadSideInformation; /* 交通事件信息以及交通标志信息 */
typedef struct _v4RoadsideSafetyMessage
{
    WJV4_INT_MsgCount n32msgCnt;
    uint8_t u8OCTid[WJV4_MAX_ID_SIZE];
    WJV4_STRU_Position3D strurefPos;
    WJV4_STRU_ParticipantList struparticipants;
} __attribute__ ((packed)) WJV4_STRU_RoadsideSafetyMessage; /* 路侧安全消息 */
typedef struct _v4SPAT
{
    WJV4_INT_MsgCount n32msgCnt;
    uint8_t u8moyPresent;
    WJV4_INT_MinuteOfTheYear n32moy; /* OPTIONAL */
    uint8_t u8timeStampPresent;
    WJV4_INT_DSecond n32timeStamp;   /* OPTIONAL */
    uint8_t u8namePresent;
    WJV4_IA5_DescriptiveName stria5name;   /* OPTIONAL */
    WJV4_STRU_IntersectionStateList struintersections;
} __attribute__ ((packed)) WJV4_STRU_SPAT;  /* 信号灯消息 */
/****************************************************************************************/
/* 内部函数声明 */
/****************************************************************************************/
#endif /* 文件结束 */