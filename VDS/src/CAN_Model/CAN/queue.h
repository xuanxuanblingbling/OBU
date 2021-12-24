#ifndef _QUEUE_H_
#define _QUEUE_H_


typedef struct VehCANDSingleConfig_Type 
{
    int    CANID;
    int    LowStartBit;
    int    LowStartByte;
    int    DataModel;
    int    DataLength;
    double ScaleFactor;
    double Offset;
} VehCANDSingleConfig;

struct Link
{
    VehCANDSingleConfig mVehCANDSingleConfig;
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
void QueuePush(struct Queue* queue, VehCANDSingleConfig data);

/*弹出队列*/
int QueuePop(struct Queue* queue, VehCANDSingleConfig *data);

/*队列销毁*/
void QueueDestroy(struct Queue* queue);

#endif //_QUEUE_H_

