/************************************************************
  文件名: queue.c
  作者: 
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
 
void QueuePush(struct Queue* queue, struct upLoadFile_t data)
{
    struct Link* node;
    node = (struct Link*)malloc(sizeof(struct Link));
    assert(node != NULL);
    
    node->mUpLoadFile.logAmount = data.logAmount;
    node->mUpLoadFile.logType = data.logType;
    strcpy(node->mUpLoadFile.PassWord, data.PassWord);
    strcpy(node->mUpLoadFile.UpdateUrl, data.UpdateUrl);
    strcpy(node->mUpLoadFile.UserName, data.UserName);

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
 
int QueuePop(struct Queue* queue, struct upLoadFile_t* data)
{
    if (QueueEmpty(queue))
    {
        return 0;
    }
    struct Link* tmp = queue->front;
    data->logAmount = queue->front->mUpLoadFile.logAmount;
    data->logType = queue->front->mUpLoadFile.logType;
    strcpy(data->PassWord, queue->front->mUpLoadFile.PassWord);
    strcpy(data->UpdateUrl, queue->front->mUpLoadFile.UpdateUrl);
    strcpy(data->UserName, queue->front->mUpLoadFile.UserName);

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


