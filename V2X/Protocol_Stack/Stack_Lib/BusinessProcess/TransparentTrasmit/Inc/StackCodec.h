#ifndef _STACK_CODEC_H_
#define _STACK_CODEC_H_
#include "SendDataInfo.h"
#ifdef __cplusplus
extern "C"
{

#endif

    int DataSend(void *pdata, int lens, int AID, SendDataInfo *sendDataInfo);
    int RawDataParse(char *pSrc, int SrcLen, char *pDst, int *DstLen);

    /**
 * @brief TransparentTransmitDataPushInQueue 将收到的透传消息数据存入队列
 *
 * @param[in] data -- 收到的数据
 * @param[in] data_len -- 收到数据的长度
 *
 * @return true/false             成功/失败
 * 
 */
    int TransparentTransmitDataPushInQueue(unsigned char *data, int data_len);

#ifdef __cplusplus
}
#endif
#endif