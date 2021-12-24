/**
* @file         :wjv3_uper_Msg.h
* @brief        :该文件为协议栈消息层消息映射头文件，包含编码解码函数外部申明和一些结构体定义等
* @details  	:主要包含协议结构体的定义和消息级的编解码程序的外部申明
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
#ifndef _WJV3_UPER_MSG_H_
#define _WJV3_UPER_MSG_H_
/***********************************************************************************/
/* 外部头文件包含 */
/***********************************************************************************/
#include "wjv3_uper_Df.h"
/***********************************************************************************/
/* 消息类型结构体定义 */
/***********************************************************************************/
typedef enum
{
    WJV3_MessageFrame_PR_NOTHING,
    WJV3_MessageFrame_PR_bsmFrame,
    WJV3_MessageFrame_PR_mapFrame,
    WJV3_MessageFrame_PR_rsmFrame,
    WJV3_MessageFrame_PR_spatFrame,
    WJV3_MessageFrame_PR_rsiFrame,
} WJV3_ENUM_MessageFrame_PR;
typedef struct
{
    WJV3_STRU_MsgCount n32msgcnt;
    uint8_t u8Id[WJV3_MAX_BYTE_ID_LEN]; /* oct string is 8 */
    uint8_t u8platNo_Len;
    uint8_t u8platNo[WJV3_MAX_BYTE_PLATNO_LEN]; /* OPTIONAL  oct string is 4 ～ 16 */
    WJV3_STRU_DSecond n32secMark;
    WJV3_STRU_Position3D strupos;
    WJV3_STRU_PositionConfidenceSet struaccuracy;
    WJV3_ENUM_TransmissionState enumTransmissionState;
    WJV3_STRU_Speed n32speed;
    WJV3_STRU_Heading n32heading;
    uint8_t u8angle_Present;
    WJV3_STRU_SteeringWheelAngle n32angle; /* OPTIONAL */
    uint8_t u8motionCfd_Present;
    WJV3_STRU_MotionConfidenceSet strumotionCfd; /* OPTIONAL */
    WJV3_STRU_AccelerationSet4Way struaccelSet;
    WJV3_STRU_BrakeSystemStatus strubrakes;
    WJV3_STRU_VehicleSize strusize;
    WJV3_STRU_VehicleClassification struvehicleClass;
    uint8_t u8safetyExt_Present;
    WJV3_STRU_VehicleSafetyExtensions strusafetyExt;
} __attribute__ ((packed)) WJV3_STRU_BasicSafetyMessage;
typedef struct
{
    WJV3_STRU_MsgCount n32msgcnt;
    uint8_t u8timeStamp_Present;
    WJV3_STRU_MinuteOfTheYear n32timeStamp; /* OPTIONAL */
    WJV3_STRU_NodeList strunodes;
} __attribute__ ((packed)) WJV3_STRU_MapData;
typedef struct
{
    WJV3_STRU_MsgCount n32msgcnt;
    uint8_t u8Id[WJV3_MAX_BYTE_ID_LEN]; /* octe string is 8 */
    WJV3_STRU_Position3D strurefPos;
    WJV3_STRU_ParticipantList struparticipants;
} __attribute__ ((packed)) WJV3_STRU_RoadsideSafetyMessage;
typedef struct
{
    WJV3_STRU_MsgCount n32msgcnt;
    uint8_t u8timeStamp_Present;
    WJV3_STRU_MinuteOfTheYear n32timeStamp; /* OPTIONAL */
    uint8_t u8nameNum;                    /* 0 is Absent*/
    uint8_t u8name[WJV3_MAX_IA5_NAME_LEN];  /* OPTIONAL */
    WJV3_STRU_IntersectionStateList struintersections;
} __attribute__ ((packed)) WJV3_STRU_SPAT;
typedef struct
{
    WJV3_STRU_MsgCount n32msgcnt;
    uint8_t u8timeStamp_Present;
    WJV3_STRU_MinuteOfTheYear n32timeStamp; /* OPTIONAL */
    uint8_t u8Id[WJV3_MAX_BYTE_ID_LEN];     /* octe string is 8 */
    int32_t n32rsiId;
    WJV3_STRU_AlertType n32alertType;
    uint16_t u16descriptionNum;                    /* 0 ~ 256 0代表该字段不存在 */
    uint8_t u8description[WJV3_MAX_DESCRIPTION_LEN]; /* OPTIONAL */
    uint8_t u8priorityNum;                         /* 0 ~ 1 0代表该字段不存在 */
    uint8_t u8priority[WJV3_MAX_PRIORITY_LEN];       /* OPTIONAL */
    WJV3_STRU_Position3D strurefPos;
    WJV3_STRU_PathPointList strualertPath;
    WJV3_STRU_Radius n32alertRadius;
} __attribute__ ((packed)) WJV3_STRU_RoadSideInformation;
#endif /* end of file */
