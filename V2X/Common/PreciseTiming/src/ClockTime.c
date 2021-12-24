/***********************************************************************
 * 文 件 名 称 ： ClockTime.c
 * 功 能 描 述 ： 精准定时函数源文件,注意定时模块不使用打印信息，避免时间准确度不够
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-05-04 V1.0    黄赛   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
/************************  包含的头文件  ********************************/
#include "ClockTime.h"
/***************************  函数定义  ********************************/
/***********************************************************************
 * 函 数 名 称 ： FT_ClockRegister
 * 功 能 描 述 ： 定时模块注册和取消注册函数
 * 输 入 参 数 ： 无
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-05-05 V1.0    黄赛   Create
***********************************************************************/
int32 FT_ClockTimeRegister(char* p_pn8RegisterName, int p_n32RegisterLen, int p_n32RegisterClockTime, sem_t** p_pptSemId)
{
    /* 入参检查 */
    if ((NULL == p_pn8RegisterName) || (p_n32RegisterLen > MAX_SEMNAMELENG) || (NULL == p_pptSemId))
    {
        LogPrint(LOG_LEVEL_ERR, CLOCKTIMEMODULE, "input is null:p_pn8RegisterName = %p  p_n32RegisterLen = %d", p_pn8RegisterName, p_n32RegisterLen);
        return IS_ERR;
    }
    ClockMsgQuence_t l_tClockTimeMsg = {0};
    int32 l_n32Ret = 0;
    int32 l_n32Msqid = 0;
    key_t l_tKey_Id = {0};
    /* 组要发送的消息 */
    memcpy(l_tClockTimeMsg.m_na8SemName, p_pn8RegisterName, p_n32RegisterLen);
    l_tClockTimeMsg.m_u32ClockTime = p_n32RegisterClockTime;
    l_tClockTimeMsg.m_n64ClockMsgQuenceType = 1;
    /* 打开创建信号量 */
    *p_pptSemId = sem_open(l_tClockTimeMsg.m_na8SemName, O_CREAT, 0666, 0);
    if (SEM_FAILED == *p_pptSemId)
    {
        LogPrint(LOG_LEVEL_ERR, CLOCKTIMEMODULE, "sem_open is err:");
        perror("unable to create semaphore");
    }
    /* 创建消息队列，并往消息队列里面写数据 */
    l_tKey_Id = ftok("/mnt", CLOCKFTOKVALUE);
    if (l_tKey_Id < 0)
    {
        LogPrint(LOG_LEVEL_ERR, CLOCKTIMEMODULE, "ftok is err: l_tKey_Id = %d", l_tKey_Id);
        perror("ftok is err");
        return IS_ERR;
    }
    l_n32Msqid = msgget(l_tKey_Id, IPC_CREAT|0666);
    if (l_n32Msqid < 0)
    {
        LogPrint(LOG_LEVEL_ERR, CLOCKTIMEMODULE, "msgget is err: l_n32Ret = %d", l_n32Ret);
        return IS_ERR;
    }

    /* 往消息队列里面写数据 */
    l_n32Ret = msgsnd(l_n32Msqid, &l_tClockTimeMsg, (sizeof(ClockMsgQuence_t) - sizeof(long)), IPC_NOWAIT);
    if (l_n32Ret < 0)
    {
        msgctl(l_n32Msqid, IPC_RMID, &l_tClockTimeMsg);
        LogPrint(LOG_LEVEL_ERR, CLOCKTIMEMODULE, "msgsnd is err: l_n32Ret = %d", l_n32Ret);
        perror("send msg is err");
        return IS_ERR;
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： Thread_ClockTime_Deal
 * 功 能 描 述 ： 定时处理函数
 * 输 入 参 数 ： 无
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-05-05 V1.0    黄赛   Create
***********************************************************************/
void Thread_ClockTime_Deal(void *arg)
{
    int32 l_n32msgid = 0;
    sem_t* l_ptSemId = 0;
    int32 l_n32Ret = 0;
    ClockLinkList_t *l_ptclocklinklist = NULL;
    ClockLinkList_t *l_ptClockLinknode = NULL;
    struct timespec l_tcurnstimeStart = {0};
    struct timespec l_tcurnstimeEnd = {0};
    ClockLinkList_t* l_ptclockLinklistDel = NULL;
    ClockLinkList_t* l_ptclockLinklistDelPro = NULL;
    ClockLinkList_t* l_ptclockLinklistSer = NULL;
    ClockMsgQuence_t l_tRecvClockMsg = {0};
    struct timeval l_ttv = {0};
    key_t l_tKey_Id = {0};
    int32 l_s32CorrectValue = 0;
    int8 l_u8Count = 0;
    int32 l_n32Num = 0;
    uint8 l_u8CheckFlag = 0;
    /* 创建消息队列 */
    umask(0);
    l_tKey_Id = ftok("/mnt", CLOCKFTOKVALUE);
    if ( l_tKey_Id < 0 )
    {
        LogPrint(LOG_LEVEL_ERR, CLOCKTIMEMODULE, "ftok is err: l_tKey_Id = %d", l_tKey_Id);
        perror("ftok is err");
        return;
    }
    l_n32msgid = msgget(l_tKey_Id, IPC_CREAT|0666);
    if (l_n32msgid < 0)
    {
        LogPrint(LOG_LEVEL_ERR, CLOCKTIMEMODULE, "msgget is err: l_n32msgid = %d", l_n32msgid);
        perror("msgget is err");
        return;
    }
    /* 创建链表 */
    l_ptclocklinklist = (ClockLinkList_t *)malloc(sizeof(ClockLinkList_t));
    l_ptclocklinklist->m_tnext = NULL;
    clock_gettime(CLOCK_REALTIME, &l_tcurnstimeStart);
    while(1)
    {
        /* 接受消息，如果是注册请求就添加链表，如果是取消注册就删除链表 */
        /* 从消息队列获取数据，并将数据写入链表 */
        l_n32Ret = 0;
        while(0 <= l_n32Ret)
        {
            l_n32Ret = msgrcv(l_n32msgid, (void *)&l_tRecvClockMsg, (sizeof(ClockMsgQuence_t) - sizeof(long)), 0, IPC_NOWAIT);
            if (0 < l_n32Ret)
            {
                /* 打开创建信号量 */
                l_ptSemId = sem_open(l_tRecvClockMsg.m_na8SemName, O_CREAT, 0666, 0);
                if (SEM_FAILED == l_ptSemId)
                {
                    LogPrint(LOG_LEVEL_ERR, CLOCKTIMEMODULE, "sem_open is err: l_ptSemId = %d", l_ptSemId);
                    perror("sem_open is err");
                }
                /* 判断消息的内容是增加还是删除 */
                /* 如果是注册一个信号量 */
                if (l_tRecvClockMsg.m_u32ClockTime > 0)
                {
                    /* 使用头插法实现了链表的增加 */
                    /* 首先检查链表里面有没有相关数据 */
                    /* 删除链表对应的信号量 */
                    l_ptclockLinklistDel = l_ptclocklinklist->m_tnext;
                    l_ptclockLinklistDelPro = l_ptclocklinklist;
                    while(NULL != l_ptclockLinklistDel)
                    {
                        /* 遍历整个链表，找到指定节点并删除 */
                        if(l_ptSemId == l_ptclockLinklistDel->m_tclockinfo.m_ptsemid)
                        {
                                l_ptclockLinklistDelPro->m_tnext = l_ptclockLinklistDel->m_tnext;
                                free(l_ptclockLinklistDel);
                                l_ptclockLinklistDel = NULL;
                                break;
                        }
                        l_ptclockLinklistDel = l_ptclockLinklistDel->m_tnext;
                        l_ptclockLinklistDelPro = l_ptclockLinklistDelPro->m_tnext;
                    }
                    /* 初始化 */
                    l_ptClockLinknode = (ClockLinkList_t *)malloc(sizeof(ClockLinkList_t));
                    l_ptClockLinknode->m_tclockinfo.m_ptsemid = l_ptSemId;
                    l_ptClockLinknode->m_tclockinfo.m_u32CurTime = 0;
                    l_ptClockLinknode->m_tclockinfo.m_u32ClockTime = l_tRecvClockMsg.m_u32ClockTime;
                    /* 插入 */
                    l_ptClockLinknode->m_tnext = l_ptclocklinklist->m_tnext;
                    l_ptclocklinklist->m_tnext = l_ptClockLinknode;
                }
                /* 如果是删除一个信号量 */
                else
                {
                    sem_close(l_ptSemId);
                    sem_unlink(l_tRecvClockMsg.m_na8SemName);
                    /* 删除链表对应的信号量 */
                    l_ptclockLinklistDel = l_ptclocklinklist->m_tnext;
                    l_ptclockLinklistDelPro = l_ptclocklinklist;
                    while(NULL != l_ptclockLinklistDel)
                    {
                        /* 遍历整个链表，找到指定节点并删除 */
                        if(l_ptSemId == l_ptclockLinklistDel->m_tclockinfo.m_ptsemid)
                        {
                                l_ptclockLinklistDelPro->m_tnext = l_ptclockLinklistDel->m_tnext;
                                free(l_ptclockLinklistDel);
                                l_ptclockLinklistDel = NULL;
                                break;
                        }
                        l_ptclockLinklistDel = l_ptclockLinklistDel->m_tnext;
                        l_ptclockLinklistDelPro = l_ptclockLinklistDelPro->m_tnext;
                    }
                }
            }
        }
        l_ptclockLinklistSer = l_ptclocklinklist->m_tnext;
        /* 检测是否达到定时时间，如果达到定时时间就像外面抛消息并且清空计时，没有到定时时间就加1 */
        while(NULL != l_ptclockLinklistSer)
        {
            /* 比较当前是否到定时时间，到达定时时间，就往外抛信号量，没有到就把当前时间加1 */
            if (l_ptclockLinklistSer->m_tclockinfo.m_u32CurTime == l_ptclockLinklistSer->m_tclockinfo.m_u32ClockTime)
            {
                if (1 == l_u8CheckFlag)
                {
                    sem_getvalue(l_ptclockLinklistSer->m_tclockinfo.m_ptsemid, &l_n32Num);
                    while(0 != l_n32Num)
                    {
                        sem_trywait(l_ptclockLinklistSer->m_tclockinfo.m_ptsemid);
                        sem_getvalue(l_ptclockLinklistSer->m_tclockinfo.m_ptsemid, &l_n32Num);
                        LogPrint(LOG_LEVEL_DEBUG, CLOCKTIMEMODULE, "wait clear sem");
                    }
                    /* 抛信号量 */
                    sem_post(l_ptclockLinklistSer->m_tclockinfo.m_ptsemid);
                    /* 将当前时间置0，开始下一次循环 */
                    l_ptclockLinklistSer->m_tclockinfo.m_u32CurTime = 1;
                }
            }
            else
            {
                l_ptclockLinklistSer->m_tclockinfo.m_u32CurTime++;
            }
            l_ptclockLinklistSer = l_ptclockLinklistSer->m_tnext;
        }
        /* 循环延时100ms */
        l_ttv.tv_sec = 0;
        l_ttv.tv_usec = 100000 - l_s32CorrectValue;
        select(0, NULL, NULL, NULL, &l_ttv);
        if (0 == l_u8CheckFlag)
        {
            if (10 > l_u8Count)
            {
                l_u8Count++;
                clock_gettime(CLOCK_REALTIME, &l_tcurnstimeEnd);
            }
            else
            {
                l_s32CorrectValue = ((1000000000 * (l_tcurnstimeEnd.tv_sec - l_tcurnstimeStart.tv_sec) + (l_tcurnstimeEnd.tv_nsec - l_tcurnstimeStart.tv_nsec)) / 10 - 100000000)/1000 ;
                l_u8CheckFlag = 1;
            }
        }
    }
    return;
}
/***********************************************************************
 * 函 数 名 称 ： FT_ClockInit
 * 功 能 描 述 ： 定时初始化函数，创建线程
 * 输 入 参 数 ： 无
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-05-05 V1.0    黄赛   Create
***********************************************************************/
int32 FT_ClockTimeInit(void)
{
    int32 l_n32Ret = 0;
    pthread_t l_tpthreadid = 0;
    /************************ 线程相关使用配置 *****************************/
    pthread_attr_t l_tpthreadattr = {0};
    struct sched_param l_pthreadparam = {0};
    pthread_attr_init(&l_tpthreadattr);
    pthread_attr_setschedpolicy(&l_tpthreadattr, SCHED_RR);
    l_pthreadparam.sched_priority = 99;
    pthread_attr_setschedparam(&l_tpthreadattr, &l_pthreadparam);
    /* 创建线程，并将优先级设置为最高 */
    l_n32Ret = pthread_create(&l_tpthreadid, &l_tpthreadattr, (void *)Thread_ClockTime_Deal, NULL);
    if (l_n32Ret != 0)
    {
        LogPrint(LOG_LEVEL_ERR, CLOCKTIMEMODULE, "pthread_create is err: l_n32Ret = %d", l_n32Ret);
        return IS_ERR;
    }
    return IS_OK;
}
/***************************  文件结束  ********************************/
