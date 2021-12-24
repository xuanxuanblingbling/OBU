/**
* @file         :wjv3_uper_Com.h
* @brief        :该文件为协议栈消息层公共头文件 包含编码解码函数外部申明等
* @details  	:主要包含协议编解码程序的外部申明
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
#ifndef _WJV3_UPER_COM_H_
#define _WJV3_UPER_COM_H_
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "wj_log.h"
#include "./../MsgFrameV3/MessageFrame.h"
/****************************************************************************************/
/* 内部函数声明 */
/****************************************************************************************/
/***********************************DE_FUNC_START****************************************/
int32_t WJV3_PositionConfidence_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_PositionConfidence_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_ElevationConfidence_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_ElevationConfidence_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_SpeedConfidence_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_SpeedConfidence_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_HeadingConfidence_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_HeadingConfidence_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_SteeringWheelAngleConfidence_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_SteeringWheelAngleConfidence_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_BrakePedalStatus_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_BrakePedalStatus_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_TractionControlStatus_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_TractionControlStatus_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_AntiLockBrakeStatus_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_AntiLockBrakeStatus_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_StabilityControlStatus_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_StabilityControlStatus_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_BrakeBoostApplied_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_BrakeBoostApplied_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_AuxiliaryBrakeStatus_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_AuxiliaryBrakeStatus_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_TransmissionState_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_TransmissionState_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_TimeConfidence_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_TimeConfidence_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_SpeedLimitType_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_SpeedLimitType_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_LightState_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_LightState_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_AlertType_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_AlertType_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_BITSTRING_DeEnc(void *pvoidAsnDE, void *pvoidWjDE);
int32_t WJV3_BITSTRING_DeDec(void *pvoidAsnDE, void *pvoidWjDE);
/***********************************DE_FUNC_END******************************************/
/***********************************DF_FUNC_START****************************************/
int32_t WJV3_Position3D_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Position3D_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PositionConfidenceSet_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PositionConfidenceSet_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_MotionConfidenceSet_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_MotionConfidenceSet_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_AccelerationSet4Way_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_AccelerationSet4Way_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_BrakeSystemStatus_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_BrakeSystemStatus_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_VehicleSize_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_VehicleSize_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_VehicleClassification_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_VehicleClassification_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_DDateTime_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_DDateTime_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_FullPositionVector_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_FullPositionVector_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PositionOffsetLL_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PositionOffsetLL_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_VerticalOffset_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_VerticalOffset_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PositionOffsetLLV_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PositionOffsetLLV_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PathHistoryPoint_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PathHistoryPoint_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PathHistoryPointList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PathHistoryPointList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PathHistory_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PathHistory_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PathPrediction_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PathPrediction_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_VehicleSafetyExtensions_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_VehicleSafetyExtensions_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_NodeReferenceID_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_NodeReferenceID_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_RegulatorySpeedLimit_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_RegulatorySpeedLimit_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_SpeedLimitList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_SpeedLimitList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_RoadPoint_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_RoadPoint_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PointList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PointList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Movement_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Movement_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_MovementList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_MovementList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_LaneTypeAttributes_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_LaneTypeAttributes_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_LaneAttributes_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_LaneAttributes_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_ConnectingLane_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_ConnectingLane_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Connection_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Connection_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_ConnectsToList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_ConnectsToList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Lane_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Lane_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_LaneList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_LaneList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Link_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Link_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_LinkList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_LinkList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Node_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Node_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_NodeList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_NodeList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_ParticipantData_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_ParticipantData_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_ParticipantList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_ParticipantList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_TimeChangeDetails_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_TimeChangeDetails_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PhaseState_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PhaseState_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PhaseStateList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PhaseStateList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Phase_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_Phase_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PhaseList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PhaseList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_IntersectionState_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_IntersectionState_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_IntersectionStateList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_IntersectionStateList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PathPointList_DfEnc(void *pvoidAsnDF, void *pvoidWjDF);
int32_t WJV3_PathPointList_DfDec(void *pvoidAsnDF, void *pvoidWjDF);
/***********************************DF_FUNC_END******************************************/
/***********************************MSG_FUNC_START***************************************/
extern int32_t WJV3_BasicSafetyMessage_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJV3_BasicSafetyMessage_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJV3_MapData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJV3_MapData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJV3_RoadsideSafetyMessage_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJV3_RoadsideSafetyMessage_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJV3_SPAT_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJV3_SPAT_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJV3_RoadSideInformation_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJV3_RoadSideInformation_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg);
/***********************************MSG_FUNC_END*****************************************/
int32_t WJV3_Check_IA5String(void *pvoidWjDF, int32_t length);
#endif /* 文件结束 */
