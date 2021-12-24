/**
* @file         :wjv2_uper_interface.h
* @brief        :消息层对外接口头文件定义
* @details      :主要包含消息接口相关结构体定义
* @author       :WM  any question please send mail to WM@wanji.net.cn
* @date         :2020-12-15
* @version      :V1.0
* @copyright    :Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：IMX6
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-15  <td>V1.0      <td>WM  <td>创建初始版本
* </table>
**********************************************************************************
*/
#ifndef _WJV2_UPER_INTERFDACE_H_
#define _WJV2_UPER_INTERFDACE_H_
/*********************************头文件包含********************************************/
#include "wjv2_uper_Msg.h"
/*********************************标准头文件********************************************/
#define DLL_PUBLIC __attribute__((visibility("default")))
typedef struct
{
    WJV2_ENUM_MessageFrame_PR enumMessageFrameType;
    union
    {
        WJV2_STRU_BasicSafetyMessage strubsmFrame;
        WJV2_STRU_MapData strumapFrame;
        WJV2_STRU_RoadsideSafetyMessage strursmFrame;
        WJV2_STRU_SPAT struspatFrame;
        WJV2_STRU_RoadSideInformation strursiFrame;
        WJV2_STRU_MessageFrameExt struFrameExt;
    } uniUperMsg;
}__attribute__ ((packed)) WJV2_STRU_MessageFrame;
typedef struct
{
    uint32_t u32MsgNo;
    /* 编码函数 */
    int32_t (*Encode_func)(void *, void *);
    /* 解码函数 */
    int32_t (*Decode_func)(void *, void *);
} FUNC_WJV2_UPER_SCHE;
typedef struct
{
    uint32_t u32Len;
#define MAXV2_UPERBUFF_SIZE 2500000
    uint8_t *pu8buff;
}__attribute__ ((packed)) WJV2_UperData;
__attribute__((visibility("default"))) void SetGetAIDFromFileCallbackV2(int (*pFunGetAid)(void *pstruMsg));
extern DLL_PUBLIC int32_t WJV2_UperFromFileEncodeMain(WJV2_UperData *pstruUperData, char *pn8FileName, int *pn32MsgAid);
extern DLL_PUBLIC int32_t WJV2_UperDecodeMain(WJV2_UperData *pstruUperData, WJV2_STRU_MessageFrame *pstruWjMsg);
extern DLL_PUBLIC int32_t WJV2_UperEncodeMain(WJV2_UperData *pstruUperData, WJV2_STRU_MessageFrame *pstruWjMsg);

#define WJV2_MessageFrame_PR_bsmFrame_NO 1
#define WJV2_MessageFrame_PR_bsmFrameOC_NO 101
#define WJV2_MessageFrame_PR_bsmFrameOE_NO 102
#define WJV2_MessageFrame_PR_bsmFrameSC_NO 103
#define WJV2_MessageFrame_PR_bsmFrameSE_NO 104
#define WJV2_MessageFrame_PR_mapFrame_NO 2
#define WJV2_MessageFrame_PR_rsmFrame_NO 3
#define WJV2_MessageFrame_PR_spatFrame_NO 4
#define WJV2_MessageFrame_PR_rsiFrame_NO 5
#define WJV2_MessageFrame_PR_rsiFrameRC_NO 501
#define WJV2_MessageFrame_PR_rsiFrameRH_NO 502
#define WJV2_MessageFrame_PR_rsiFrameRD_NO 503
#define WJV2_MessageFrame_PR_ExtDataFrame_NO 6
#define WJV2_MessageFrame_PR_TOTALNUM 13

#define WJV2_MessageFrame_PR_TestMsg 7
#define WJV2_MessageFrame_PR_RTCMcorrections 8
#define WJV2_MessageFrame_PR_PAMData 9
#define WJV2_MessageFrame_PR_CLPMM 10
#define WJV2_MessageFrame_PR_PersonalSafetyMessage 11
#define WJV2_MessageFrame_PR_RoadsideCoordination 12
#define WJV2_MessageFrame_PR_SensorSharingMsg 13
#define WJV2_MessageFrame_PR_VehIntentionAndRequest 14
#define WJV2_MessageFrame_PR_VehiclePaymentMessage 15
#define WJV2_MessageFrame_PR_ExtTOTALNUM 9
#endif /* 文件结束 */