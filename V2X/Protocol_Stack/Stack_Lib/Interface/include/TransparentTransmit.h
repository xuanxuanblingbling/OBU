/**
 * @defgroup TransInterface TransInterface API
 * @ingroup WJ_Interface_Com API
 * @{
 *
 * 本模块提供V2X发送透传消息模块的API接口.
 *
 * @}
 *
 */

/**
 * @defgroup Transmit Transmit API
 * @ingroup TransInterface API
 * @{
 *
 * 本模块V2X发送透传消息的API接口.
 *
 * @file TransparentTransmit.h
 * @brief API file.
 *
 */

#ifndef _TRANSPARENT_TRANSMIT_H_
#define _TRANSPARENT_TRANSMIT_H_

#include "SendDataInfo.h"
#ifdef __cplusplus
extern "C"
{
#endif
  /**
 * @brief TransparentTransmitDataSend 开始发送透传消息
 *
 * @param[in] data -- 发送数据
 * @param[in] data_len -- 发送数据的长度
 * @param[out] callbackReturnInfo -- 反馈的分包后的数据
 *
 * @return true/false             成功/失败
 *
 * Example Usage:
 * @code
 * {
 *    while (1)
 *    {
 *      SendTransInfo *sendTransInfo = (SendTransInfo *)calloc(1, sizeof(SendTransInfo));
 *      if (NULL != sendTransInfo)
 *      {
 *        TransparentTransmitDataSend(data, data_len, sendTransInfo);
 *        if (sendTransInfo->error_type == 0)
 *        {
 *          SendDataReturnInfo ag15SendDataReturnInfo;
 *          for (int i = 0; i < sendTransInfo->sendDataNum; i++)
 *          {
 *            V2X_SendData(sendTransInfo->sendDataInfo[i], &ag15SendDataReturnInfo);
 *          }
 *        }
 *        free(sendTransInfo);
 *      }
 *    }
 * }
 * @endcode
 *
 */
  __attribute__((visibility("default"))) int TransparentTransmitDataSend(unsigned char *data, int data_len, SendTransInfo *callbackReturnInfo);
  /**
 * @brief TransparentTransmitDataRecv 从队列获取数据
 *
 * @param[in] devid -- 设备编号
 * @param[out] data -- 获取到的数据（动态内存，内部申请内存，由应用层外部释放内存）
 * @param[out] data_len -- 获取到数据的长度
 *
 * @return true/false             成功/失败
 *
 * Example Usage:
 * @code
 * {
 *    while (1)
 *    {
 *      unsigned char *pdata = NULL;
 *      int data_len = 0;
 *      ret = TransparentTransmitDataRecv(0, &pdata, &data_len);
 *      if (ret == 0)
 *      {
 *        printf("TransparentTransmitDataRecv(),data_len = %d\n", data_len);
 *        free(pdata);
 *      }
 *    }
 * }
 * @endcode
 *
 */
  __attribute__((visibility("default"))) int TransparentTransmitDataRecv(int devid, unsigned char **data, int *data_len);
#ifdef __cplusplus
}
#endif

#endif