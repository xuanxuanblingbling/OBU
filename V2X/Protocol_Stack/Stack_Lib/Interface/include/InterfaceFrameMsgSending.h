/**
 * @defgroup Stack_TxInterface Stack_TxInterface API
 * @ingroup WJ_Interface_Com API
 * @{
 *
 * 本模块提供V2X发送标准消息模块的API接口.
 *
 * @}
 *
 */

/**
 * @defgroup Stack_Tx Stack_Tx API
 * @ingroup Stack_TxInterface API
 * @{
 *
 * 本模块V2X发送标准消息的API接口.
 *
 * @file InterfaceFrameMsgSending.h
 * @brief API file.
 *
 */

#ifndef _INTERFACE_FRAME_MSG_SENDING_H_
#define _INTERFACE_FRAME_MSG_SENDING_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "wj_Message_com.h"
#include "SendDataInfo.h"

  typedef void (*SENDCALL_BACK)(SendCallbackReturnInfo callbackReturnInfo);

  /**
 * @brief StackSendInit 开启发送线程并设置发送消息的回调函数（外部不使用）
 *
 * @param[in] pfunc -- 发送消息回调函数
 *
 * @return true/false             成功/失败
 *
 */
  __attribute__((visibility("default"))) int StackSendInit(SENDCALL_BACK pfunc);

  /**
 * @brief SendFrameMessageData 向发送消息队列存入数据
 *
 * @param[in] pData -- 消息层数据结构体（动态内存，由外部应用层申请内存，内部释放内存）
 *
 * @return true/false             成功/失败
 *
 * Example Usage:
 * @code
 * {
 *    while (1)
 *    {
 *      MSG_MessageType_st *pMsg = (MSG_MessageType_st *)calloc(1, sizeof(MSG_MessageType_st));
 *      if (NULL != pMsg)
 *      {
 *        pMsg->messageType = MSG_MessageType_ID_Three;
 *        SendFrameMessageData(pMsg);
 *      }
 *    }
 * }
 * @endcode
 *
 */
  __attribute__((visibility("default"))) int SendFrameMessageData(MSG_MessageType_st *pData);

#ifdef __cplusplus
}
#endif

#endif