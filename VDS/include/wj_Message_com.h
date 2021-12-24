#ifndef _WJ_MESSAGE_COM_H_
#define _WJ_MESSAGE_COM_H_
#include "wjv2_uper_interface.h"
// #include "ExtensionData.h"
#include <stdint.h>
#define WJ_MAX_EXTENSIONINFO_LEN 32
#define WJ_MAX_EXTEN_NUM 10
/**
 * @brief DSM数据中拓展域数据结构.
 */
typedef struct ExtenSionCommn
{
    uint8_t ElementID;                               //扩展域信息标识
    uint8_t ByteLength;                              //扩展域信息长度
    uint8_t ExtensionInfo[WJ_MAX_EXTENSIONINFO_LEN]; //扩展域信息内容
} __attribute__((packed)) tExtenSionCommn;

typedef struct _ExtenSionCommn_st
{
    uint8_t layerIDChanged;                           //适配层是否修改源层2ID标志位(0:不修改，1：修改；程序启动后适配层源层2ID会默认为初始随机值)
    uint8_t u8ExtenNum;                               //网络层扩展域信息个数，若不存在扩展域，则为0
    tExtenSionCommn extenSionCommn[WJ_MAX_EXTEN_NUM]; //网络层扩展域信息
} __attribute__((packed)) tExtenSionCommn_st;

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
 
    WJV2_STRU_MessageFrame MessageTwo;      //二期场景消息集


    //网络层/适配层扩展域数据结构体,若无扩展域，则为0
    tExtenSionCommn_st extension;
    //OBU紧急事件标志 0：无紧急事件 1：有紧急事件
    int nEmergencyEventFlag; //应用层需向消息层传递OBU紧急事件标志，供安全层签名使用，RSU无此设定

} MSG_MessageType_st, *MSG_MessageType_st_ptr;

#endif
