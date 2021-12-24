#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGQUEUE_BUF_SIZE (2048) /*消息队列的数据缓存大小*/
/*消息队列使用的通信结构体*/
struct QueueMsgBuf
{
    long m_n32MsgType;
    char m_n8MsgData[MSGQUEUE_BUF_SIZE];
};

int32_t MsgQueueCreate(const int8_t *p_pn8QueueName, uint8_t p_u8QueueId, int32_t *p_n32QueueFd)
{
    key_t l_tQueueKey = 0;
    int32_t l_tQueueId = 0;
    // struct msqid_ds l_tQueueAttr = {.msg_qbytes = 12 * 1024};

    if ((NULL == p_pn8QueueName) || (0 == p_u8QueueId) || (NULL == p_n32QueueFd))
    {
        printf("wrong para\n");
        return -1;
    }

    l_tQueueKey = ftok((const char *)p_pn8QueueName, p_u8QueueId);
    if (-1 == l_tQueueKey)
    {
        printf("ftok failed\n");
        return -1;
    }

    l_tQueueId = msgget(l_tQueueKey, IPC_CREAT | 0666);
    if (-1 == l_tQueueId)
    {
        printf("msg queue create failed\n");
        return -1;
    }

    *p_n32QueueFd = l_tQueueId;
    //  printf("msg queue id:%d\n", l_tQueueId);
    return 0;
}

int32_t MsgQueueSend(int32_t p_n32QueueFd, void *p_Msg, int32_t p_n32MsgSize)
{
    struct QueueMsgBuf l_tMsgBuf = {0};

    if ((-1 == p_n32QueueFd) || (NULL == p_Msg) || (0 >= p_n32MsgSize) || (MSGQUEUE_BUF_SIZE <= p_n32MsgSize))
    {
        printf("wrong para, size:%d\n", p_n32MsgSize);
        return -1;
    }

    l_tMsgBuf.m_n32MsgType = 1;
    memcpy(l_tMsgBuf.m_n8MsgData, p_Msg, p_n32MsgSize);

    if (-1 == msgsnd(p_n32QueueFd, &l_tMsgBuf, p_n32MsgSize, IPC_NOWAIT))
    {
        printf("msg send failed\n");
        return -1;
    }

    return 0;
}

int32_t MsgQueueRecv(int32_t p_n32QueueFd, void *p_RecvMsgBuf, int32_t *p_pn32MsgSize)
{
    struct QueueMsgBuf l_tMsgBuf = {0};
    int32_t l_n32MsgRecvSize = 0;

    if ((-1 == p_n32QueueFd) || (NULL == p_RecvMsgBuf) || (NULL == p_pn32MsgSize) || (0 >= *p_pn32MsgSize))
    {
        printf("wrong para\n");
        return -1;
    }
    //  printf("begin recv\n");
    if (-1 == (l_n32MsgRecvSize = msgrcv(p_n32QueueFd, &l_tMsgBuf, MSGQUEUE_BUF_SIZE, 1, 0)))
    {
        printf("recv failed\n");
        return -1;
    }
    //  printf("recv bytes:%d\n", l_n32MsgRecvSize);
    if (l_n32MsgRecvSize > *p_pn32MsgSize)
    {
        printf("msg buffer is too small\n");
        return -1;
    }

    memcpy(p_RecvMsgBuf, l_tMsgBuf.m_n8MsgData, l_n32MsgRecvSize);
    *p_pn32MsgSize = l_n32MsgRecvSize;

    return 0;
}

void MsgQueueDel(int32_t p_n32QueueFd)
{
    if (-1 == p_n32QueueFd)
    {
        printf("wrong para\n");
        return;
    }
    msgctl(p_n32QueueFd, IPC_RMID, NULL);
}
