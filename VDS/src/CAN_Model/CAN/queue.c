/************************************************************
  文件名: queue.c
  作者: lixingjian@wanji.net.cn
  描述: 队列操作           
  版本:     
  日期:       
  函数列表:   
  历史记录: 
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

void initQueue(struct Queue* queue)
{
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

int QueueEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}
 
void QueuePush(struct Queue* queue, VehCANDSingleConfig data)
{
    struct Link* node;
    node = (struct Link*)malloc(sizeof(struct Link));
    assert(node != NULL);
    
    node->mVehCANDSingleConfig.CANID = data.CANID;
    node->mVehCANDSingleConfig.LowStartBit = data.LowStartBit;
    node->mVehCANDSingleConfig.LowStartByte = data.LowStartByte;
    node->mVehCANDSingleConfig.DataModel = data.DataModel;
    node->mVehCANDSingleConfig.DataLength = data.DataLength;
    node->mVehCANDSingleConfig.ScaleFactor = data.ScaleFactor;
    node->mVehCANDSingleConfig.Offset = data.Offset;

    node->next = NULL;
    
    if(QueueEmpty(queue))
    {
        queue->front = node;
        queue->rear = node;
    }
    else
    {            
        queue->rear->next = node;
        queue->rear = node;
    }
    ++queue->size;
}
 
int QueuePop(struct Queue* queue, VehCANDSingleConfig* data)
{
    if (QueueEmpty(queue))
    {
        return 0;
    }
    struct Link* tmp = queue->front;
    data->CANID = queue->front->mVehCANDSingleConfig.CANID;
    data->LowStartBit = queue->front->mVehCANDSingleConfig.LowStartBit;
    data->LowStartByte = queue->front->mVehCANDSingleConfig.LowStartByte;
    data->DataModel = queue->front->mVehCANDSingleConfig.DataModel;
    data->DataLength = queue->front->mVehCANDSingleConfig.DataLength;
    data->ScaleFactor = queue->front->mVehCANDSingleConfig.ScaleFactor;
    data->Offset = queue->front->mVehCANDSingleConfig.Offset;

    queue->front = queue->front->next;
    free(tmp);
    --queue->size;

    return 1;
}
 
void QueueDestroy(struct Queue* queue)
{
    struct Link* tmp;
    while(queue->front)
    {
        tmp = queue->front;
        queue->front = queue->front->next;
        free(tmp);
    }
}


