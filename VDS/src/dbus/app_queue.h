#ifndef _APP_QUEUE_H_
#define _APP_QUEUE_H_

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<pthread.h>
#include "general_config.h"

#define APP_RECV_QUEUE_SIZE		10 //定义app队列节点数

#define APP_MAX(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))

#define APP_BUF_MAX_SIZE	APP_MAX(APP_ACT_SAFE_FRAME_LEN,APP_TRFC_REMIND_FRAME_LEN,APP_SPD_GUIDE_FRAME_LEN)//设定vds模块接收APP数据最大字节

#define DBUS_MAX_SIZE	10000//设定DBUS数据最大为1000字节
/*
*APP-VDS传输队列　成员数据定义
*/
typedef struct app_data
{
	uint16_t       m_id;
	uint16_t       m_length;
	uint8_t		   m_appdata[APP_BUF_MAX_SIZE-5];//帧数据
	uint8_t        m_bcc;
}__attribute__ ((packed))TAppData;
/**
 * 
 */
typedef struct app_queue_member
{
	TAppData       m_appData;//app 数据域
}__attribute__ ((packed))TAppQueueMember;
/*
*@brief　APP-VDS传输队列定义，作为数据缓存区使用。
*/
typedef struct app_queue 
{
	uint8_t  		head;
	TAppQueueMember buf[APP_RECV_QUEUE_SIZE];
    uint8_t  		tail;
	uint16_t  		size;
}__attribute__ ((packed))TAppQueue;

/*************************************/
extern TAppQueue g_app_recv_queue;//spi数据接收队列

/************************************/
extern void        FD_AppQueueInit(TAppQueue *p_app_queue);//app队列初始化
extern EtRetstatus FD_AppQueueEmpty(TAppQueue *p_app_queue);//判断app队列是否为空
extern EtRetstatus FD_AppQueueFull(TAppQueue *p_app_queue);//判断app队列是否溢出
extern EtRetstatus FD_AppQueueRemove(TAppQueue *p_app_queue,TAppQueueMember *p_data);//从app队列中移除数据
extern EtRetstatus FD_AppQueueInsert(TAppQueue *p_app_queue,TAppQueueMember *p_data);//向app队列中插入数据


#endif

