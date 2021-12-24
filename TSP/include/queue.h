#ifndef _QUEUE_H_
#define _QUEUE_H_


/*上传日志文件时，下发请求内容*/
struct upLoadFile_t
{
    char UpdateUrl[200];
    char UserName[50];
    char PassWord[50];
    int logType;
    int logAmount;
};

struct Link
{
    struct upLoadFile_t mUpLoadFile;
    struct Link* next;
};

struct Queue
{
    struct Link* front;
    struct Link* rear;
    int size;
};

/*初始化队列*/
void initQueue(struct Queue* queue);

/*队列判空*/
int QueueEmpty(struct Queue* queue);

/*插入队列*/
void QueuePush(struct Queue* queue, struct upLoadFile_t data);

/*弹出队列*/
int QueuePop(struct Queue* queue, struct upLoadFile_t *data);

/*队列销毁*/
void QueueDestroy(struct Queue* queue);

#endif //_QUEUE_H_

