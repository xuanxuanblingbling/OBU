/**
* @file         :wjvn4_uper_com.h
* @brief        :协议栈公共头文件 ，包含一些函数的申明
* @details      :主要包含消息帧，数据帧，数据元素等函数申明
* @author       :huangsai  any question please send mail to huangsai@wanji.net.cn
* @date         :2020-12-17
* @version      :V1.0
* @copyright    :Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：IMX6
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-17  <td>V1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
#ifndef __WJVN4_UPER_COM_H_
#define __WJVN4_UPER_COM_H_
/*********************************头文件包含********************************************/
#include <stdint.h>
#include "wj_log.h"
#include <stddef.h>
#include <stdbool.h>
#include "./../MsgFrameVN4/MessageFrame.h"
/*********************************标准头文件********************************************/
/*********************************自定义头文件******************************************/
#define STACK_MSG_MODULE "MSGLAYERVN4MSG"
#define STACK_DF_MODULE "MSGLAYERVN4DF"
#define STACK_DE_MODULE "MSGLAYERVN4DE"
/****************************************************************************************/
/* 内部函数声明 */
/****************************************************************************************/
/* MSG消息帧结构函数外部申明 */
extern int32_t WJVN4_BasicSafetyMessage_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJVN4_BasicSafetyMessage_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJVN4_MapData_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJVN4_MapData_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJVN4_RoadSideInformation_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJVN4_RoadSideInformation_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJVN4_RoadsideSafetyMessage_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJVN4_RoadsideSafetyMessage_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJVN4_SPAT_MsgEnc(void *pvoidAsnMsg, void *pvoidWjMsg);
extern int32_t WJVN4_SPAT_MsgDec(void *pvoidAsnMsg, void *pvoidWjMsg);
/* DF数据帧结构函数外部申明 */
extern int32_t WJVN4_AccelerationSet4Way_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_AccelerationSet4Way_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_BrakeSystemStatus_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_BrakeSystemStatus_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ConnectingLane_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ConnectingLane_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Connection_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Connection_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ConnectsToList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ConnectsToList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_DDateTime_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_DDateTime_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Description_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Description_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_FullPositionVector_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_FullPositionVector_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_IntersectionState_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_IntersectionState_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_IntersectionStateList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_IntersectionStateList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Lane_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Lane_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_LaneAttributes_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_LaneAttributes_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_LaneList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_LaneList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_LaneTypeAttributes_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_LaneTypeAttributes_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Link_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Link_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_LinkList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_LinkList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_MotionConfidenceSet_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_MotionConfidenceSet_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Movement_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Movement_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_MovementList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_MovementList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Node_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Node_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_NodeList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_NodeList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_NodeReferenceID_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_NodeReferenceID_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ParticipantData_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ParticipantData_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ParticipantList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ParticipantList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PathHistory_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PathHistory_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PathHistoryPoint_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PathHistoryPoint_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PathHistoryPointList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PathHistoryPointList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PathPointList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PathPointList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PathPrediction_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PathPrediction_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Phase_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Phase_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PhaseList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PhaseList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PhaseState_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PhaseState_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PhaseStateList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PhaseStateList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PointList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PointList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL24B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL24B_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL28B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL28B_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL32B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL32B_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL36B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL36B_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL44B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL44B_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL48B_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLL48B_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLLmD64b_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionLLmD64b_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Position3D_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_Position3D_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionalAccuracy_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionalAccuracy_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionConfidenceSet_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionConfidenceSet_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionOffsetLL_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionOffsetLL_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionOffsetLLV_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_PositionOffsetLLV_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ReferenceLink_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ReferenceLink_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ReferenceLinkList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ReferenceLinkList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ReferencePath_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ReferencePath_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ReferencePathList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_ReferencePathList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RegulatorySpeedLimit_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RegulatorySpeedLimit_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RSITimeDetails_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RSITimeDetails_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RTEData_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RTEData_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RTEList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RTEList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RTSData_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RTSData_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RTSList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RTSList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RoadPoint_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_RoadPoint_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_SignalState_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_SignalState_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_SpeedLimitList_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_SpeedLimitList_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_TimeChangeDetails_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_TimeChangeDetails_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_TimeCountingDown_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_TimeCountingDown_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_UTCTiming_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_UTCTiming_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_VehicleClassification_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_VehicleClassification_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_VehicleEmergencyExtensions_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_VehicleEmergencyExtensions_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_VehicleSafetyExtensions_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_VehicleSafetyExtensions_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_VehicleSize_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_VehicleSize_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_VerticalOffset_DfEnc(void *pvoidAsnDf, void *pvoidWjDf);
extern int32_t WJVN4_VerticalOffset_DfDec(void *pvoidAsnDf, void *pvoidWjDf);
/* DE数据元素结构函数外部申明 */
extern int32_t WJVN4_AllowedManeuvers_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_AllowedManeuvers_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_BrakeAppliedStatus_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_BrakeAppliedStatus_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_DescriptiveName_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_DescriptiveName_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_ExteriorLights_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_ExteriorLights_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_GNSSstatus_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_GNSSstatus_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_IntersectionStatusObject_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_IntersectionStatusObject_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesBarrier_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesBarrier_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesBike_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesBike_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesCrosswalk_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesCrosswalk_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesParking_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesParking_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesSidewalk_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesSidewalk_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesStriping_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesStriping_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesTrackedVehicle_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesTrackedVehicle_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesVehicle_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneAttributesVehicle_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneSharing_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_LaneSharing_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_ReferenceLanes_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_ReferenceLanes_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_RSIPriority_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_RSIPriority_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_VehicleEventFlags_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_VehicleEventFlags_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_BITSTRING_DeEnc(void *pvoidAsnDe, void *pvoidWjDe);
extern int32_t WJVN4_BITSTRING_DeDec(void *pvoidAsnDe, void *pvoidWjDe);
#endif /* 文件结束 */