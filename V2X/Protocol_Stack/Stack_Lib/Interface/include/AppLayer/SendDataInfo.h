/**
 * @ingroup Stack_TxInterface API
 * @{
 *
 * 本模块提供发送及接收模块基本的数据结构.
 *
 * @file SendDataInfo.h
 * @brief API file.
 *
 */
#ifndef __SENDDATAINFO_H_
#define __SENDDATAINFO_H_
#include <stdint.h>

#define Para_Error -1           //参数错误
#define Message_Encode_Error -2 //消息层编码失败
#define NetLay_Encode_Error -3  //网络层编码失败
#define SignMsg_Error -4        //安全层签名失败
#define Calloc_Error -5         //申请内存失败

#define Message_Decode_Error -6  //消息层解码失败
#define NetLay_Decode_Error -7   //网络层解码失败
#define Verify_Error -8          //安全层验签失败
#define NetLay_CheckAid_Error -9 //检查AID失败
#define Other_Error -10          //其他错误

/*AG15接收与发送相关结构体*/
#define MAX_DUMMY_PACKET_LEN (5000)
/***********************************发送数据结构体*****************************************/
/**
 * @brief 高层请求发送的打包数据信息.
 */
typedef struct _SendDataInfo
{
    //有些模组可能需要上层协议栈提供以下两个ID才能正常发送（若模组不需要，可预留）
    unsigned char SourceLayer2ID[3];      //源层2id（若模组不需要，可预留）
    unsigned char DestinationLayer2ID[3]; //目标层2id（若模组不需要，可预留）
    unsigned char pppp;                   //优先级
    int p_nLen;                           //打包后的码流数据长度
    char p_pcBuf[MAX_DUMMY_PACKET_LEN];   //打包后的码流
} __attribute__((packed)) SendDataInfo;

/**
 * @brief 标准消息打包结构体
 */
typedef struct _SendCallbackReturnInfo
{
    int data_type;  //数据类型
    int error_type; //数据发送错误类型
    SendDataInfo sendDataInfo;
} __attribute__((packed)) SendCallbackReturnInfo;
/**
 * @brief 透传消息打包结构体
 */
typedef struct _SendTransInfo
{
    int data_type;                 //数据类型
    int error_type;                //数据发送错误类型
    int sendDataNum;               //透传消息分包个数
    SendDataInfo sendDataInfo[10]; //目前最多分解10个数据包，支持10000字节的发送
} __attribute__((packed)) SendTransInfo;

/***********************************接收数据结构体*****************************************/
/**
 * @brief 接入层反馈给上层的数据信息.
 */
typedef struct _RecvCallbackReturnInfo
{
    float Current_CBR;                     //当前的CBR测量值（若无法提供可预留）
    unsigned char pppp;                    //适配层pppp
    int pnRecvBufSize;                     //接收到的数据长度
    char p_cRecvBuf[MAX_DUMMY_PACKET_LEN]; //接收到的数据
} __attribute__((packed)) RecvCallbackReturnInfo;

/**
 * @brief MsgRx_CallBack 接收数据处理函数
 *
 * @param[in] RecvCallbackReturnInfo -- 接入层收到数据的结构体
 *
 */
__attribute__((visibility("default"))) void MsgRx_CallBack(RecvCallbackReturnInfo ag15CallbackReturnInfo);

#endif