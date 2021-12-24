
#ifndef __STPTHREADPOOL_H_
#define __STPTHREADPOOL_H_

/**********************  头文件  ********************************/
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/syscall.h>

#define gettidv1() syscall(__NR_gettid)
#define gettidv2() syscall(SYS_gettid)

/********************** 宏定义 *************************************/
#define MIN_WAIT_TASK_NUM 2          // 最小等待任务数，一般和线程池中的最小线程数相等
#define DEFAULT_TIME 30              // 管理线程工作周期
#define DEFAULT_CHARGE_PTHREAD_NUM 1 // 每次默认增加的线程数

/* 线程相关宏 */
#define PTHREADPOOL_MINNUM 8 //消息层4个，安全层4个
#define PTHREADPOOL_MAXNUM 8 //消息层4个，0-3，安全层4个，4-7
#define ADDTASKTOPTHREADPOOL_MAXNUM 2

#define PTHREADPOOL_MSGMAXNUM 4
#define PTHREADPOOL_SECMAXNUM 4

#define PTHREADPOOL_MSGINDEX 0 //消息层线程起始索引
#define PTHREADPOOL_SECINDEX 4 //安全层线程起始索引

/* 任务类型 */
typedef enum __AddTaskType__
{
    enumMsg = 0,
    enumSec = 1
} enumAddTaskType;

/* 线程池任务结构体 */
typedef struct _STthreadPoolTask
{
    void *(*m_pvFunction)(void *);
    void *m_pvArg;
    enumAddTaskType tasktype;
} STthreadPoolTask;

/* 线程结构体 */
typedef struct _STthreadArray
{
    pthread_t m_nPthreadTid;
    pthread_cond_t m_nPthreadCond;
    pthread_mutex_t m_nPthreadLock;
    bool m_nPthreadStatus;
} STthreadArray;

/* 线程池结构体 */
typedef struct _STthreadPool
{
    pthread_mutex_t m_nPthreadPoolLock;  //用于先线程池全局的锁
    pthread_cond_t m_nTaskQueueNotEmpty; //条件锁，在任务队列空时，线程阻塞

    STthreadArray *m_nPthreadTidArray; //线程池数组
    pthread_t m_nAdminPthread;         //admin_tid,管理者线程
    STthreadPoolTask *m_nTaskQueue;    //任务队列

    /* 线程池信息 */
    uint8_t m_n32MinPthreadNum;  //线程池中的最小线程数
    uint8_t m_n32MaxPthreadNum;  //线程池中的最大线程数
    uint8_t m_n32BusyPthreadNum; //线程池中正在执行任务的线程数

    uint8_t m_n32SecMinPthreadNum;         //线程池中安全层的最小线程数
    uint8_t m_n32MsgMinPthreadNum;         //线程池中消息层的最小线程数
    uint8_t m_n32SecLivePthreadNum;        //线程池中安全层当前存活的线程数
    uint8_t m_n32MsgLivePthreadNum;        //线程池中消息层当前存活的线程数
    uint8_t m_n32SecWaitDestroyPthreadNum; //线程池中安全层等待被销毁的线程数
    uint8_t m_n32MsgWaitDestroyPthreadNum; //线程池中消息层等待被销毁的线程数

    /* 任务队列信息 */
    uint8_t m_n32QueueMaxTaskNum; //任务队列中最大任务数
    uint8_t m_n32QueueTaskSize;   //当前任务队列中的任务数

    /* 是否关闭线程池 */
    uint8_t m_n32ShutDown;
} STthreadPool;

typedef struct _ThreadPara
{
    STthreadPool *ptPthreadPool; // 线程池中活动线程数
    /*安全层、消息层线程池标志位*/
    enumAddTaskType m_n32SecOrMsg;
    uint8_t index; //信号量索引
} ThreadPara;

typedef struct _TModule_NetComm_Cycle
{
    uint8_t m_u8AlivedThreadsinPool; // 线程池中活动线程数
    int m_n32CurrentTasks;           // 当前任务数
} TModule_NetComm_Cycle;

/* 全局变量 */
extern STthreadPool *P_STthreadpool;

/* 创建线程池 */
STthreadPool *FD_STPthreadPoolCreate(uint8_t p_nMinPthreadNum, uint8_t p_nMaxPthreadNum, uint8_t p_nQueueMaxTaskNum);

/* 工作线程 */
void *FD_STWorkPthread(void *p_ptPthreadPool);

/* 管理工作线程 */
void *FD_STAdminWorkPthread(void *p_ptPthreadPool);

/* 释放线程池空间 */
void FD_STPthreadPoolFree(STthreadPool *p_ptPthreadPool);

/* 销毁线程池 */
void FD_STPthreadPoolDestroy(STthreadPool *p_ptPthreadPool);

/* 向线程池任务队列中添加一个任务,添加成功返回0,添加失败返回1. */
int FD_STPthreadPoolAddTask(STthreadPool *p_ptPthreadPool, void *p_DataProcessFunction, void *p_Arg, enumAddTaskType p_TaskType);

/* 任务函数 */
void STtask_function(void *data);

/* 线程是否存活 */
int FD_STPthreadAlive(pthread_t p_nPthreadTid);

/* 线程池状态 */
int FD_STGetPthreadpoolstate(STthreadPool *p_ptPthreadPool, TModule_NetComm_Cycle *pt_CycleDevState);

int FN_STPthreadPoolInit();

void FN_STPthreadPoolDestroy();

#endif