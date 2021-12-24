/**
 * 
 * @ingroup Stack_Rx API
 * @{
 *
 * 本模块V2X接收模块操作队列的API接口.
 *
 * @file MsgLayerRecvQueue.h
 * @brief API file.
 *
 */

#ifndef _MSG_LAYER_RECV_QUEUE_H_
#define _MSG_LAYER_RECV_QUEUE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "wj_Message_com.h"
#include "RxInit.h"
  /**
 * @brief MsgLayerMessagePushInQueue 将消息结构体存入队列
 *
 * @param[in] pdata -- 消息结构体
 *
 * @return true/false             成功/失败
 * 
 */
  int MsgLayerMessagePushInQueue(MSG_MessageType_st *pdata);

#ifdef __cplusplus
}
#endif

#endif
