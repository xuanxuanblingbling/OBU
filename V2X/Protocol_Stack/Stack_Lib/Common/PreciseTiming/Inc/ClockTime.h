/***********************************************************************
 * 文 件 名 称 ： ClockTime.h
 * 功 能 描 述 ： 精准定时函数包含头文件
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-05-04 V1.0    黄赛   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
#ifndef _CLOCKTIME_H_
#define _CLOCKTIME_H_
/**********************  头文件包含  ********************************/
#include "ClockTimeIf.h"
#include "wj_log.h"
#include <stdbool.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/********************** 宏定义 *************************************/
#define MAX_SEMNAMELENG 20
#define CLOCKFTOKVALUE  80
#define CLOCKTIMEMODULE "ClockTime"
/********************** 类型重定义 **********************************/
/* 消息队列结构体 */
typedef struct _ClockMsgQuence{
    long    m_n64ClockMsgQuenceType;    /* 消息类型 */
    int8_t    m_na8SemName[MAX_SEMNAMELENG];           /* 信号量的名称 */
    uint32_t  m_u32ClockTime;            /* 定时的时间0代表取消注册 */
    sem_t * m_ptsemId;
}ClockMsgQuence_t;
/* 定时信息的结构体 */
typedef struct _ClockInfo{
    sem_t* m_ptsemid;          /* 信号量ID */
    uint32_t m_u32CurTime;        /* 当前时间 (ms)*/
    uint32_t m_u32ClockTime;      /* 定时时间 (ms)*/
}ClockInfo_t;
/* 链表结构 */
typedef struct _ClockLinkList
{
    ClockInfo_t m_tclockinfo;
    struct _ClockLinkList *m_tnext;
}ClockLinkList_t;
/********************** 全局变量定义  ********************************/
/********************** 函数外部申明 ********************************/
#endif /* _CLOCKTIME_H_ */

