/**
 * @defgroup WJ_Message_Com WJ_Message_Com API
 * @ingroup WJ_Interface_Com API
 * @{
 *
 * 本模块V2X协议栈消息层、网络层对外接口及数据结构头文件.
 *
 * @file wj_Message_com.h
 * @brief API file.
 *
 */

#ifndef _WJ_MESSAGE_COM_H_
#define _WJ_MESSAGE_COM_H_
#include "wjv3_uper_interface.h"
#include "wjv4_uper_interface.h"
#include "wjvn4_uper_interface.h"
#include "wjv2_uper_interface.h"
#include "ExtensionData.h"
typedef struct
{
    uint32_t u32Len;
    uint8_t *pu8buff;
} WJ_UperData;
/* Message Type id. */
typedef enum _MSG_MessageType_ID_en
{
    MSG_MessageType_ID_Two = 2,     //二期场景消息集
    MSG_MessageType_ID_Three = 3,   //三跨消息
    MSG_MessageType_ID_Four = 4,    //四跨消息
    MSG_MessageType_ID_NEW_Four = 5 //新四跨消息

} MSG_MessageType_ID_en;

/* Message Type for all the mesage. */
typedef struct _MSG_MessageType_st
{
    //消息层消息数据结构体
    MSG_MessageType_ID_en messageType;
    union msg_unType
    {
        WJV2_STRU_MessageFrame MessageTwo;      //二期场景消息集
        WJV3_STRU_MessageFrame MessageThree;    //三跨消息
        WJV4_STRU_MessageFrame MessageFour;     //四跨消息
        WJVN4_STRU_MessageFrame MessageNewFour; //新四跨消息
    } msgtype;

    //消息层原始码流，有些项目可能用到
    struct WJ_UperData_t
    {
        uint32_t u32Len;
        uint8_t pu8buff[4096];
    } wj_UperData;

    //网络层/适配层扩展域数据结构体,若无扩展域，则为0
    tExtenSionCommn_st extension;
    //OBU紧急事件标志 0：无紧急事件 1：有紧急事件
    uint8_t nEmergencyEventFlag; //应用层需向消息层传递OBU紧急事件标志，供安全层签名使用，RSU无此设定

} MSG_MessageType_st, *MSG_MessageType_st_ptr;

#endif