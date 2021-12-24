/**
* @file         :wjvn4_uper_interface.h
* @brief        :消息层对外接口头文件定义
* @details      :主要包含消息接口相关结构体定义
* @author       :huangsai  any question please send mail to huangsai@wanji.net.cn
* @date         :2020-12-15
* @version      :V1.0
* @copyright    :Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：IMX6
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020-12-15  <td>V1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
#ifndef _WJVN4_UPER_INTERFDACE_H_
#define _WJVN4_UPER_INTERFDACE_H_
/*********************************头文件包含********************************************/
#include "wjvn4_uper_Msg.h"
/*********************************标准头文件********************************************/
#define DLL_PUBLIC __attribute__((visibility("default")))
typedef struct
{
    WJVN4_ENUM_MessageFrame_PR enumMessageFrameType;
    union
    {
        WJVN4_STRU_BasicSafetyMessage strubsmFrame;
        WJVN4_STRU_MapData strumapFrame;
        WJVN4_STRU_RoadsideSafetyMessage strursmFrame;
        WJVN4_STRU_SPAT struspatFrame;
        WJVN4_STRU_RoadSideInformation strursiFrame;
    } uniUperMsg;
} WJVN4_STRU_MessageFrame;
typedef struct
{
    uint32_t u32MsgNo;
    /* 编码函数 */
    int32_t (*Encode_func)(void *, void *);
    /* 解码函数 */
    int32_t (*Decode_func)(void *, void *);
} FUNC_WJVN4_UPER_SCHE;
typedef struct
{
    uint32_t u32Len;
#define MAXVN4_UPERBUFF_SIZE 250000
    uint8_t *pu8buff;
} WJVN4_UperData;

typedef enum
{
    MSGVN4_MessageFrame_UperDecode = 1, /* 消息解码 */
    MSGVN4_MessageFrame_UperEncode = 2, /* 消息编码 */

} WJVN4_ENUM_InterFace;

/**
 * @brief SetGetAIDFromFileCallbackVN4 设置获取AID回调函数接口（外部不使用）
 *
 * @param[in] pFunGetAid -- 获取AID的回调函数
 *
 * @return true/false             成功/失败
 *
 */
extern DLL_PUBLIC void SetGetAIDFromFileCallbackVN4(int (*pFunGetAid)(void *pstruMsg));

/**
 * @brief WJVN4_UperFromFileEncodeMain 从本地文件解析xml数据，并输出uper码流
 *
 * @param[in] pn8FileName -- 文件路径及名称
 * @param[out] pstruUperData -- 消息层码流长度及uper码流
 * @param[out] pn32MsgAid -- 消息AID
 *
 * @return true/false             成功/失败
 *
 */
extern DLL_PUBLIC int32_t WJVN4_UperFromFileEncodeMain(WJVN4_UperData *pstruUperData, char *pn8FileName, int *pn32MsgAid);

/**
 * @brief WJVN4_UperEncOrDecMain 新四跨消息编解码接口
 *
 * @param[in] InterFace -- 选择编码或解码
 * @param[in/out] pstruUperData -- 消息层码流长度及uper码流
 * @param[in/out] pstruWjMsg -- 应用层结构体
 *
 * @return true/false             成功/失败
 *
 */
extern DLL_PUBLIC int32_t WJVN4_UperEncOrDecMain(WJVN4_UperData *pstruUperData, WJVN4_STRU_MessageFrame *pstruWjMsg, WJVN4_ENUM_InterFace InterFace);
/*新四跨消息集接口*/
typedef int32_t (*WJVN4_UperFromFileEncodeMain_BACK)(WJVN4_UperData *pstruUperData, char *pn8FileName, int *pn32MsgAid);
typedef int32_t (*WJVN4_UperEncOrDecMain_BACK)(WJVN4_UperData *pstruUperData, WJVN4_STRU_MessageFrame *pstruWjMsg, WJVN4_ENUM_InterFace InterFace);
typedef void (*WJVN4_SetGetAIDFromFileCallback)(int (*pFunGetAid)(void *pstruMsg));

#define WJVN4_MessageFrame_PR_bsmFrame_NO 1
#define WJVN4_MessageFrame_PR_bsmFrameOC_NO 101
#define WJVN4_MessageFrame_PR_bsmFrameOE_NO 102
#define WJVN4_MessageFrame_PR_bsmFrameSC_NO 103
#define WJVN4_MessageFrame_PR_bsmFrameSE_NO 104
#define WJVN4_MessageFrame_PR_mapFrame_NO 2
#define WJVN4_MessageFrame_PR_rsmFrame_NO 3
#define WJVN4_MessageFrame_PR_spatFrame_NO 4
#define WJVN4_MessageFrame_PR_rsiFrame_NO 5
#define WJVN4_MessageFrame_PR_rsiFrameRC_NO 501
#define WJVN4_MessageFrame_PR_rsiFrameRH_NO 502
#define WJVN4_MessageFrame_PR_rsiFrameRD_NO 503
#define WJVN4_MessageFrame_PR_TOTALNUM 12
#endif /* 文件结束 */