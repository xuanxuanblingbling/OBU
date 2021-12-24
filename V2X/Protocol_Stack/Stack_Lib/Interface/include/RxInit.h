/**
 * @defgroup Stack_RxInterface Stack_RxInterface API
 * @ingroup WJ_Interface_Com API
 * @{
 *
 * 本模块提供V2X接收、发送初始化的API接口.
 *
 * @}
 *
 */

/**
 * @defgroup Stack_Rx Stack_Rx API
 * @ingroup Stack_RxInterface API
 * @{
 *
 * 本模块V2X接收、发送初始化的API接口.
 *
 * @file RxInit.h
 * @brief API file.
 *
 */
#ifndef _STACK_RX_RX_INIT_H_
#define _STACK_RX_RX_INIT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "wj_Message_com.h"
  /**
 * @brief StackRecvInit V2x接收初始化接口（外部不使用）
 *
 */
  __attribute__((visibility("default"))) int StackRecvInit();

  /**
 * @brief MsgLayerMessageGetFromQueue 从接收消息队列中获取数据
 *
 * @return MSG_MessageType_st             获取的消息数据结构体（动态内存，内部申请内存，由外部应用层释放内存）
 *
 * Example Usage:
 * @code
 * {
 *    while (1)
 *    {
 *      MSG_MessageType_st *pdata = MsgLayerMessageGetFromQueue();
 *      if (NULL != pdata)
 *      {
 *        if (pdata->messageType == MSG_MessageType_ID_Three)
 *        {
 *          printf("----------MsgLayerMessageGetFromQueue() type: %d\n", pdata->msgtype.MessageThree.enumMessageFrameType);
 *        }
 *        free(pdata);
 *        pdata = NULL;
 *      }
 *    }
 * }
 * @endcode
 */
  __attribute__((visibility("default"))) MSG_MessageType_st *MsgLayerMessageGetFromQueue();

#ifdef __cplusplus
}
#endif

#endif