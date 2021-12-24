/**
* @file         :wjv4_uper_interface.h
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
#ifndef _WJV4_UPER_INTERFDACE_H_
#define _WJV4_UPER_INTERFDACE_H_
/*********************************头文件包含********************************************/
#include "wjv4_uper_Msg.h"
/*********************************标准头文件********************************************/
#define DLL_PUBLIC __attribute__((visibility("default")))
typedef struct
{
    WJV4_ENUM_MessageFrame_PR enumMessageFrameType;
    union
    {
        WJV4_STRU_BasicSafetyMessage strubsmFrame;
        WJV4_STRU_MapData strumapFrame;
        WJV4_STRU_RoadsideSafetyMessage strursmFrame;
        WJV4_STRU_SPAT struspatFrame;
        WJV4_STRU_RoadSideInformation strursiFrame;
    } uniUperMsg;
} WJV4_STRU_MessageFrame;
typedef struct
{
    uint32_t u32MsgNo;
    /* 编码函数 */
    int32_t (*Encode_func)(void *, void *);
    /* 解码函数 */
    int32_t (*Decode_func)(void *, void *);
} FUNC_WJV4_UPER_SCHE;
typedef struct
{
    uint32_t u32Len;
#define MAXV4_UPERBUFF_SIZE 250000
    uint8_t *pu8buff;
} WJV4_UperData;
typedef enum
{
    MSGV4_MessageFrame_UperDecode = 1, /* 消息解码 */
    MSGV4_MessageFrame_UperEncode = 2, /* 消息编码 */

} WJV4_ENUM_InterFace;
/**
 * @brief SetGetAIDFromFileCallbackV4 设置获取AID回调函数接口（外部不使用）
 *
 * @param[in] pFunGetAid -- 获取AID的回调函数
 *
 * @return true/false             成功/失败
 *
 */
extern DLL_PUBLIC void SetGetAIDFromFileCallbackV4(int (*pFunGetAid)(void *pstruMsg));

/**
 * @brief WJV4_UperFromFileEncodeMain 从本地文件解析xml数据，并输出uper码流
 *
 * @param[in] pn8FileName -- 文件路径及名称
 * @param[out] pstruUperData -- 消息层码流长度及uper码流
 * @param[out] pn32MsgAid -- 消息AID
 *
 * @return true/false             成功/失败
 *
 */
extern DLL_PUBLIC int32_t WJV4_UperFromFileEncodeMain(WJV4_UperData *pstruUperData, char *pn8FileName, int *pn32MsgAid);

/**
 * @brief WJV4_UperEncOrDecMain 四跨消息编解码接口
 *
 * @param[in] InterFace -- 选择编码或解码
 * @param[in/out] pstruUperData -- 消息层码流长度及uper码流
 * @param[in/out] pstruWjMsg -- 应用层结构体
 *
 * @return true/false             成功/失败
 *
 */
extern DLL_PUBLIC int32_t WJV4_UperEncOrDecMain(WJV4_UperData *pstruUperData, WJV4_STRU_MessageFrame *pstruWjMsg, WJV4_ENUM_InterFace InterFace);

/*四跨消息集接口*/
typedef int32_t (*WJV4_UperFromFileEncodeMain_BACK)(WJV4_UperData *pstruUperData, char *pn8FileName, int *pn32MsgAid);
typedef int32_t (*WJV4_UperEncOrDecMain_BACK)(WJV4_UperData *pstruUperData, WJV4_STRU_MessageFrame *pstruWjMsg, WJV4_ENUM_InterFace InterFace);
typedef void (*WJV4_SetGetAIDFromFileCallback)(int (*pFunGetAid)(void *pstruMsg));
#define WJV4_MessageFrame_PR_bsmFrame_NO 1
#define WJV4_MessageFrame_PR_bsmFrameOC_NO 101
#define WJV4_MessageFrame_PR_bsmFrameOE_NO 102
#define WJV4_MessageFrame_PR_bsmFrameSC_NO 103
#define WJV4_MessageFrame_PR_bsmFrameSE_NO 104
#define WJV4_MessageFrame_PR_mapFrame_NO 2
#define WJV4_MessageFrame_PR_rsmFrame_NO 3
#define WJV4_MessageFrame_PR_spatFrame_NO 4
#define WJV4_MessageFrame_PR_rsiFrame_NO 5
#define WJV4_MessageFrame_PR_rsiFrameRC_NO 501
#define WJV4_MessageFrame_PR_rsiFrameRH_NO 502
#define WJV4_MessageFrame_PR_rsiFrameRD_NO 503
#define WJV4_MessageFrame_PR_TOTALNUM 12
#endif /* 文件结束 */