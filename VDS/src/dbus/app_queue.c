#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include "app_queue.h"


TAppQueue g_app_recv_queue;//app数据接收队列

/*************************************************
  名称: FD_AppQueueInit
  描述: app接收队列初始化
  输入参数:　app队列名
  输出参数:　无
  返回值: 无
**************************************************/
void FD_AppQueueInit(TAppQueue *p_app_queue)
{
    for(int cnt=0;cnt<APP_RECV_QUEUE_SIZE;cnt++)
    {
	    memset((uint8_t *)p_app_queue,0,sizeof(TAppQueue));//
    }
}
/*************************************************
  名称: FD_AppQueueInsert
  描述: 向app接收队列中插入数据
  输入参数:　p_app_queue，app队列名称。p_data，需要插入的app数据
  输出参数:　无
  返回值:  返回插入结果
**************************************************/
EtRetstatus FD_AppQueueInsert(TAppQueue *p_app_queue,TAppQueueMember *p_data)
{
	static uint8_t l_coverflag;

	if(p_app_queue->size >= APP_RECV_QUEUE_SIZE)//判断队列成员数量是否大于最大限制
	{
		p_app_queue->tail++;
		l_coverflag = true;
	}
	else
	{
		p_app_queue->size++;
	}

	memcpy((TAppQueueMember *)&(p_app_queue->buf[p_app_queue->head]),p_data,sizeof(TAppQueueMember));
	p_app_queue->head++;

    if(p_app_queue->head >= APP_RECV_QUEUE_SIZE)
	{
		p_app_queue->head = 0;
		if(l_coverflag==true)
		{
		   p_app_queue->tail=0;
		}
	}
	l_coverflag = false;
	return SUCCESS;
}
/*************************************************
  名称: FD_AppQueueRemove
  描述: 从app接收队列中移除数据
  输入参数:　p_app_queue，app队列名｜data，从app队列获取数据
  输出参数:　无
  返回值:  返回移除数据是否成功
**************************************************/
EtRetstatus FD_AppQueueRemove(TAppQueue *p_app_queue,TAppQueueMember *p_data)
{
	memset(p_data,0,sizeof(TAppQueueMember));

	if(p_app_queue->size == 0)//队列为空，直接返回
	{
		return QUEUE_EMPTY_ERROR;	
	}
	else
	{
		p_app_queue->size--;
	}
	
	memcpy(p_data,&p_app_queue->buf[p_app_queue->tail],sizeof(TAppQueueMember));
	memset((TAppQueueMember *)&(p_app_queue->buf[p_app_queue->tail]),0,sizeof(TAppQueueMember));
	p_app_queue->tail++;

    if(p_app_queue->tail >= APP_RECV_QUEUE_SIZE)
	{
		p_app_queue->tail = 0;
	}
	
	return SUCCESS;
}
/*************************************************
  名称: FD_AppQueueEmpty
  描述: 检查app接收队列是否为空
  输入参数:　p_app_queue，app队列名
  输出参数:无
  返回值: 返回检查结果
**************************************************/
EtRetstatus FD_AppQueueEmpty(TAppQueue *p_app_queue)
{
	if(p_app_queue->size == 0)
	{
		return SUCCESS;
	}
	return ERROR;	
}
/*************************************************
  名称: FD_AppQueueFull
  描述: 检查app队列是否为满
  输入参数:　p_app_queue，app队列名
  输出参数:　无
  返回值:  返回检查结果
**************************************************/
EtRetstatus FD_AppQueueFull(TAppQueue *p_app_queue)
{
	if(p_app_queue->size >= APP_RECV_QUEUE_SIZE)
	{
		return SUCCESS;
	}
	return ERROR;
}