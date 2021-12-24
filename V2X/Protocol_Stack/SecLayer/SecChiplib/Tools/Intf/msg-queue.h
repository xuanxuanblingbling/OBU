#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <stdint.h>

extern  int32_t MsgQueueCreate(const int8_t *p_pn8QueueName, uint8_t p_u8QueueId, int32_t *p_n32QueueFd);
extern  int32_t MsgQueueSend(int32_t p_n32QueueFd, void *p_Msg, int32_t p_n32MsgSize);
extern  int32_t MsgQueueRecv(int32_t p_n32QueueFd, void *p_RecvMsgBuf, int32_t *p_pn32MsgSize);
extern  void MsgQueueDel(int32_t p_n32QueueFd);

#endif
