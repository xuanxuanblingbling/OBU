
/**********************  头文件  ********************************/
#include "STpthreadpool.h"
#include "wj_log.h"
#include "PublicMsg.h"

/* 全局变量 */
STthreadPool *P_STthreadpool = NULL;

STthreadPool *FD_STPthreadPoolCreate(uint8_t p_nMinPthreadNum, uint8_t p_nMaxPthreadNum, uint8_t p_nQueueMaxTaskNum)
{
    if ((0 == p_nMinPthreadNum) || (0 == p_nMaxPthreadNum) || (0 == p_nQueueMaxTaskNum))
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "FD_PthreadPoolCreate para is error.");
        return NULL;
    }
    // 返回的线程池
    STthreadPool *l_ptPthreadPool = NULL;

    // 申请线程池内存空间
    l_ptPthreadPool = (STthreadPool *)calloc(1, sizeof(STthreadPool));
    if (l_ptPthreadPool == NULL)
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "l_ptPthreadPool malloc flase.");
        FD_STPthreadPoolFree(l_ptPthreadPool);
        return NULL;
    }

    // 线程池互斥锁初始化
    if (pthread_mutex_init(&(l_ptPthreadPool->m_nPthreadPoolLock), NULL) != 0)
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "pthread_mutex init flase.");
        FD_STPthreadPoolFree(l_ptPthreadPool);
        return NULL;
    }

    // 线程池条件变量初始化
    if (pthread_cond_init(&(l_ptPthreadPool->m_nTaskQueueNotEmpty), NULL) != 0)
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "pthread_cond init false.");
        FD_STPthreadPoolFree(l_ptPthreadPool);
        return NULL;
    }

    // 线程池线程数据初始化
    l_ptPthreadPool->m_n32MinPthreadNum = p_nMinPthreadNum;
    l_ptPthreadPool->m_n32MaxPthreadNum = p_nMaxPthreadNum;
    l_ptPthreadPool->m_n32SecMinPthreadNum = PTHREADPOOL_SECMAXNUM;
    l_ptPthreadPool->m_n32MsgMinPthreadNum = PTHREADPOOL_MSGMAXNUM;
    l_ptPthreadPool->m_n32SecLivePthreadNum = 1;
    l_ptPthreadPool->m_n32MsgLivePthreadNum = 1;
    l_ptPthreadPool->m_n32BusyPthreadNum = 0;
    l_ptPthreadPool->m_n32SecWaitDestroyPthreadNum = 0;
    l_ptPthreadPool->m_n32MsgWaitDestroyPthreadNum = 0;

    // 线程池任务队列数据初始化
    l_ptPthreadPool->m_n32QueueMaxTaskNum = p_nQueueMaxTaskNum;
    l_ptPthreadPool->m_n32QueueTaskSize = 0;

    // 线程池开关初始化
    l_ptPthreadPool->m_n32ShutDown = 0;

    // 根据最大线程池中的最大线程数，为工作线程申请内存空间
    l_ptPthreadPool->m_nPthreadTidArray = (STthreadArray *)calloc(1, sizeof(STthreadArray) * p_nMaxPthreadNum);
    if (l_ptPthreadPool->m_nPthreadTidArray == NULL)
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "pthreads malloc false.");
        FD_STPthreadPoolFree(l_ptPthreadPool);
        return NULL;
    }
    int i = 0;
    for (i = 0; i < p_nMaxPthreadNum; i++)
    {
        if ((pthread_cond_init(&(l_ptPthreadPool->m_nPthreadTidArray[i].m_nPthreadCond), NULL) != 0))
        {
            LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "pthread_cond init false.");
            FD_STPthreadPoolFree(l_ptPthreadPool);
            return NULL;
        }
        if ((pthread_mutex_init(&(l_ptPthreadPool->m_nPthreadTidArray[i].m_nPthreadLock), NULL) != 0))
        {
            LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "pthread_mutex init flase.");
            FD_STPthreadPoolFree(l_ptPthreadPool);
            return NULL;
        }
    }

    // 根据线程池中的任务队列的最大任务数，为任务队列申请内存空间
    l_ptPthreadPool->m_nTaskQueue = (STthreadPoolTask *)calloc(1, sizeof(STthreadPoolTask) * p_nQueueMaxTaskNum);
    if (l_ptPthreadPool->m_nTaskQueue == NULL)
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "queues malloc false.");
        FD_STPthreadPoolFree(l_ptPthreadPool);
        return NULL;
    }

    // 设置线程的属性为分离的
    pthread_attr_t attrMsg;
    pthread_attr_init(&attrMsg);
    struct sched_param l_pthreadparamMsg = {0};
    l_pthreadparamMsg.sched_priority = 92;
    pthread_attr_setschedpolicy(&attrMsg, SCHED_RR);
    pthread_attr_setschedparam(&attrMsg, &l_pthreadparamMsg);
    pthread_attr_setinheritsched(&attrMsg, PTHREAD_EXPLICIT_SCHED);

    pthread_attr_t attrSec;
    pthread_attr_init(&attrSec);
    struct sched_param l_pthreadparamSec = {0};
    l_pthreadparamSec.sched_priority = 94;
    pthread_attr_setschedpolicy(&attrSec, SCHED_RR);
    pthread_attr_setschedparam(&attrSec, &l_pthreadparamSec);
    pthread_attr_setinheritsched(&attrSec, PTHREAD_EXPLICIT_SCHED);

    // 创建最小线程数个工作线程
    ThreadPara ParaSec, ParaMsg;
    ParaSec.ptPthreadPool = l_ptPthreadPool;
    ParaMsg.ptPthreadPool = l_ptPthreadPool;
    ParaSec.m_n32SecOrMsg = enumSec;
    ParaMsg.m_n32SecOrMsg = enumMsg;

    //创建消息层最小线程
    for (i = 0; i < l_ptPthreadPool->m_n32MsgMinPthreadNum; i++)
    {
        ParaMsg.index = i + PTHREADPOOL_MSGINDEX;
        if (pthread_create(&(l_ptPthreadPool->m_nPthreadTidArray[ParaMsg.index].m_nPthreadTid), &attrMsg, FD_STWorkPthread, (void *)&ParaMsg) < 0)
        {
            LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "%u pthread create faild.\n", (unsigned int)l_ptPthreadPool->m_nPthreadTidArray[ParaMsg.index].m_nPthreadTid);
        }
        pthread_detach(l_ptPthreadPool->m_nPthreadTidArray[ParaMsg.index].m_nPthreadTid);
        usleep(30 * 1000);
    }

    //创建安全层最小线程
    for (i = 0; i < l_ptPthreadPool->m_n32SecMinPthreadNum; i++)
    {
        ParaSec.index = i + PTHREADPOOL_SECINDEX;
        if (pthread_create(&(l_ptPthreadPool->m_nPthreadTidArray[ParaSec.index].m_nPthreadTid), &attrSec, FD_STWorkPthread, (void *)&ParaSec) < 0)
        {
            LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "%u pthread create faild.\n", (unsigned int)l_ptPthreadPool->m_nPthreadTidArray[ParaSec.index].m_nPthreadTid);
        }
        pthread_detach(l_ptPthreadPool->m_nPthreadTidArray[ParaSec.index].m_nPthreadTid);
        usleep(30 * 1000);
    }
    //分别释放消息层及安全层两个信号量
    // pthread_cond_signal(&(l_ptPthreadPool->m_nPthreadTidArray[PTHREADPOOL_MSGINDEX].m_nPthreadCond));
    // pthread_cond_signal(&(l_ptPthreadPool->m_nPthreadTidArray[PTHREADPOOL_SECINDEX].m_nPthreadCond));

    //程序启动后释放所有信号，运行全部线程，避免刚启动时遇到大数据情况下丢包严重，待后续检查时，在停止线程
    for (i = 0; i < PTHREADPOOL_MAXNUM; i++)
    {
        pthread_cond_signal(&(l_ptPthreadPool->m_nPthreadTidArray[i].m_nPthreadCond));
    }
    l_ptPthreadPool->m_n32SecLivePthreadNum = PTHREADPOOL_SECMAXNUM;
    l_ptPthreadPool->m_n32MsgLivePthreadNum = PTHREADPOOL_MSGMAXNUM;

    // 创建管理线程
    if (pthread_create(&(l_ptPthreadPool->m_nAdminPthread), NULL, FD_STAdminWorkPthread, (void *)l_ptPthreadPool) < 0)
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "%u pthread create faild.\n", (unsigned int)l_ptPthreadPool->m_nAdminPthread);
    }
    pthread_detach(l_ptPthreadPool->m_nAdminPthread);

    return l_ptPthreadPool;
}

void *FD_STWorkPthread(void *p_ptPthreadPool)
{
    if (NULL == p_ptPthreadPool)
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "FD_WorkPthread para is error.");
        return NULL;
    }
    // 将线程池指针的类型转换回来
    ThreadPara *Para = (ThreadPara *)p_ptPthreadPool;
    STthreadPool *l_ptPthreadPool = (STthreadPool *)Para->ptPthreadPool;
    enumAddTaskType m_n32SecOrMsg = Para->m_n32SecOrMsg;
    uint8_t index = Para->index;

    // 将要向线程池中添加的任务
    STthreadPoolTask l_tTask;

    // 工作线程主循环
    while (1)
    {
        // 线程池未关闭，且此时线程池中任务数为0
        if ((l_ptPthreadPool->m_n32ShutDown != 1))
        {
            if (l_ptPthreadPool->m_nPthreadTidArray[index].m_nPthreadStatus == false)
            {
                LogPrint(LOG_LEVEL_INFO, "StackPthreadPool", "FD_WorkPthread wait index = %d,m_n32SecOrMsg =%d", index, m_n32SecOrMsg);
                // 阻塞在条件变量上，丢包率过大时跳出
                pthread_cond_wait(&(l_ptPthreadPool->m_nPthreadTidArray[index].m_nPthreadCond), &(l_ptPthreadPool->m_nPthreadTidArray[index].m_nPthreadLock));
                l_ptPthreadPool->m_nPthreadTidArray[index].m_nPthreadStatus = true;
                pthread_mutex_unlock(&(l_ptPthreadPool->m_nPthreadTidArray[index].m_nPthreadLock));
                LogPrint(LOG_LEVEL_INFO, "StackPthreadPool", "FD_WorkPthread start index = %d,m_n32SecOrMsg =%d", index, m_n32SecOrMsg);
            }
            // 判断是否有消息层等待退出的线程,有就自杀
            if ((l_ptPthreadPool->m_n32MsgWaitDestroyPthreadNum > 0) && (m_n32SecOrMsg == enumMsg))
            {
                if (index != PTHREADPOOL_MSGINDEX)
                {
                    pthread_mutex_lock(&(l_ptPthreadPool->m_nPthreadPoolLock));
                    l_ptPthreadPool->m_n32MsgWaitDestroyPthreadNum--;

                    l_ptPthreadPool->m_nPthreadTidArray[index].m_nPthreadStatus = false;
                    // 判断当前线程数是否大于线程池中的最小线程数,则结束当前线程
                    if (l_ptPthreadPool->m_n32MsgLivePthreadNum > l_ptPthreadPool->m_n32MsgMinPthreadNum)
                    {
                        l_ptPthreadPool->m_n32MsgLivePthreadNum--;
                        LogPrint(LOG_LEVEL_INFO, "StackPthreadPool", "Msg pthread_exit.");
                        pthread_mutex_unlock(&(l_ptPthreadPool->m_nPthreadPoolLock));
                        pthread_exit(NULL);
                    }
                    l_ptPthreadPool->m_n32MsgLivePthreadNum--;

                    pthread_mutex_unlock(&(l_ptPthreadPool->m_nPthreadPoolLock));
                }
            }
            else if ((l_ptPthreadPool->m_n32SecWaitDestroyPthreadNum > 0) && (m_n32SecOrMsg == enumSec))
            {
                if (index != PTHREADPOOL_SECINDEX)
                {
                    pthread_mutex_lock(&(l_ptPthreadPool->m_nPthreadPoolLock));
                    l_ptPthreadPool->m_n32SecWaitDestroyPthreadNum--;

                    l_ptPthreadPool->m_nPthreadTidArray[index].m_nPthreadStatus = false;
                    // 判断当前线程数是否大于线程池中的最小线程数,则结束当前线程
                    if (l_ptPthreadPool->m_n32SecLivePthreadNum > l_ptPthreadPool->m_n32SecMinPthreadNum)
                    {
                        l_ptPthreadPool->m_n32SecLivePthreadNum--;
                        LogPrint(LOG_LEVEL_INFO, "StackPthreadPool", "Sec pthread_exit.");
                        pthread_mutex_unlock(&(l_ptPthreadPool->m_nPthreadPoolLock));
                        pthread_exit(NULL);
                    }
                    l_ptPthreadPool->m_n32SecLivePthreadNum--;

                    pthread_mutex_unlock(&(l_ptPthreadPool->m_nPthreadPoolLock));
                }
            }
        }
        else
        {
            // 线程池置关闭状态,结束当前线程
            pthread_exit(NULL);
        }

        // 以上两种情况都不成立，则可以从任务队列中取出任务，并执行
        l_tTask.m_pvFunction = l_ptPthreadPool->m_nTaskQueue[m_n32SecOrMsg].m_pvFunction;
        //l_tTask.m_pvArg = NULL;
        //l_tTask.tasktype = l_ptPthreadPool->m_nTaskQueue[m_n32SecOrMsg].tasktype;
        if (l_tTask.m_pvFunction != NULL)
        {
            // 执行刚刚取出的任务
            (*(l_tTask.m_pvFunction))(NULL);
        }
        else
        {
            // LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "pthread_taskqueue parameter is NULL.");
            // if (l_ptPthreadPool->m_n32QueueTaskSize == 0)
            // {
            //     // 无任务则阻塞在条件变量任务队列不为空上，有任务时跳出
            //     pthread_cond_wait(&(l_ptPthreadPool->m_nTaskQueueNotEmpty), &(l_ptPthreadPool->m_nPthreadPoolLock));
            //     pthread_mutex_unlock(&(l_ptPthreadPool->m_nPthreadPoolLock));
            // }
            usleep(100 * 1000);
        }
    }
}

void *FD_STAdminWorkPthread(void *p_ptPthreadPool)
{
    if (NULL == p_ptPthreadPool)
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "FD_AdminWorkPthread para is error.");
        return NULL;
    }
    // 用于遍历
    int i = 0;
    // 已经添加的线程数
    int add = 0;
    // 将入参指针转换为线程池结构体类型的指针
    STthreadPool *l_ptPthreadPool = (STthreadPool *)p_ptPthreadPool;

    // 管理线程主循环
    while (!l_ptPthreadPool->m_n32ShutDown)
    {
        // 管理线程的周期
        if ((CurrentCBR <= 10.00) && (CurrentCBR >= 0.00))
            sleep(DEFAULT_TIME * 2);
        else if (CurrentCBR > 30.00)
            sleep(DEFAULT_TIME / 2);
        else
            sleep(DEFAULT_TIME);

        LogPrint(LOG_LEVEL_INFO, "StackPthreadPool", "m_n32SecLivePthreadNum = %d", l_ptPthreadPool->m_n32SecLivePthreadNum);
        LogPrint(LOG_LEVEL_INFO, "StackPthreadPool", "m_n32MsgLivePthreadNum = %d", l_ptPthreadPool->m_n32MsgLivePthreadNum);
        // 当丢包率大于0.3,而且存活线程数小于最大线程数时，创建新的工作线程
        if ((l_ptPthreadPool->m_n32SecLivePthreadNum + l_ptPthreadPool->m_n32MsgLivePthreadNum) < l_ptPthreadPool->m_n32MaxPthreadNum)
        {
            LogPrint(LOG_LEVEL_INFO, "StackPthreadPool", "Admin add pthread.");
            if ((MsgDiscardedRate > MSG_MAX_DiscardedRate) && (l_ptPthreadPool->m_n32MsgLivePthreadNum < PTHREADPOOL_MSGMAXNUM))
            {
                // 唤醒的线程数从0算起
                add = 0;
                for (i = 0; i < (PTHREADPOOL_MSGMAXNUM) && (add < DEFAULT_CHARGE_PTHREAD_NUM); i++)
                {
                    if (l_ptPthreadPool->m_nPthreadTidArray[i].m_nPthreadStatus == false)
                    {
                        add++;
                        pthread_mutex_lock(&(l_ptPthreadPool->m_nPthreadPoolLock));
                        pthread_cond_signal(&(l_ptPthreadPool->m_nPthreadTidArray[i].m_nPthreadCond));
                        l_ptPthreadPool->m_n32MsgLivePthreadNum++;
                        pthread_mutex_unlock(&(l_ptPthreadPool->m_nPthreadPoolLock));
                    }
                }
                LogPrint(LOG_LEVEL_INFO, "StackPthreadPool", "Msg Have added %d pthreads.", add);
            }

            if ((SecDiscardedRate > SEC_MAX_DiscardedRate) && (l_ptPthreadPool->m_n32SecLivePthreadNum < PTHREADPOOL_SECMAXNUM))
            {
                // 唤醒的线程数从0算起
                add = 0;
                for (i = PTHREADPOOL_SECINDEX; (i < l_ptPthreadPool->m_n32MaxPthreadNum) && (add < DEFAULT_CHARGE_PTHREAD_NUM); i++)
                {
                    if (l_ptPthreadPool->m_nPthreadTidArray[i].m_nPthreadStatus == false)
                    {
                        add++;
                        pthread_mutex_lock(&(l_ptPthreadPool->m_nPthreadPoolLock));
                        pthread_cond_signal(&(l_ptPthreadPool->m_nPthreadTidArray[i].m_nPthreadCond));
                        l_ptPthreadPool->m_n32SecLivePthreadNum++;
                        pthread_mutex_unlock(&(l_ptPthreadPool->m_nPthreadPoolLock));
                    }
                }
                LogPrint(LOG_LEVEL_INFO, "StackPthreadPool", "Sec Have added %d pthreads.", add);
            }
        }

        // 当活跃线程数分别大于1时，视情况可分别减少线程数
        if ((l_ptPthreadPool->m_n32SecLivePthreadNum > 1) || (l_ptPthreadPool->m_n32MsgLivePthreadNum > 1))
        {
            // 每次销毁DEFAULT_CHARGE_PTHREAD_NUM个线程
            pthread_mutex_lock(&(l_ptPthreadPool->m_nPthreadPoolLock));

            if ((CurrentCBR <= 10.00) && (CurrentCBR >= 0.00))
            {
                if (MsgDiscardedRate < MSG_MAX_DiscardedRate)
                {
                    //降低工作线程循环次数
                    MsgCyclesNum = 1000;
                    //此处只保留1个线程，一次睡眠一个线程
                    l_ptPthreadPool->m_n32MsgWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32MsgLivePthreadNum > 1) ? 1 : 0);
                }

                if (SecDiscardedRate < SEC_MAX_DiscardedRate)
                {
                    //降低工作线程循环次数
                    SecCyclesNum = 1000;
                    //此处只保留1个线程，一次睡眠一个线程
                    l_ptPthreadPool->m_n32SecWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32SecLivePthreadNum > 1) ? 1 : 0);
                }
            }
            else if ((CurrentCBR <= 25.00) && (CurrentCBR > 10.00))
            {
                if ((MsgDiscardedRate < MSG_MAX_DiscardedRate) && (MsgDiscardedRate >= PUB_MIN_DiscardedRate))
                {
                    MsgCyclesNum = 4000;
                    //此处只保留2个线程
                    l_ptPthreadPool->m_n32MsgWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32MsgLivePthreadNum > 2) ? 1 : 0);
                }
                else if (MsgDiscardedRate < PUB_MIN_DiscardedRate)
                {
                    MsgCyclesNum = 2000;
                    //此处只保留1个线程
                    l_ptPthreadPool->m_n32MsgWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32MsgLivePthreadNum > 1) ? l_ptPthreadPool->m_n32MsgLivePthreadNum - 1 : 0);
                }

                if ((SecDiscardedRate < SEC_MAX_DiscardedRate) && (SecDiscardedRate >= PUB_MIN_DiscardedRate))
                {
                    SecCyclesNum = 4000;
                    //此处只保留2个线程
                    l_ptPthreadPool->m_n32SecWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32SecLivePthreadNum > 2) ? 1 : 0);
                }
                else if (SecDiscardedRate < PUB_MIN_DiscardedRate)
                {
                    SecCyclesNum = 2000;
                    //此处只保留1个线程
                    l_ptPthreadPool->m_n32SecWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32SecLivePthreadNum > 1) ? l_ptPthreadPool->m_n32SecLivePthreadNum - 1 : 0);
                }
            }
            else if ((CurrentCBR <= 35.00) && (CurrentCBR > 25.00))
            {
                if ((MsgDiscardedRate < MSG_MAX_DiscardedRate) && (MsgDiscardedRate >= PUB_MIN_DiscardedRate))
                {
                    MsgCyclesNum = 5000;
                    //此处只保留3个线程
                    l_ptPthreadPool->m_n32MsgWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32MsgLivePthreadNum > 3) ? 1 : 0);
                }
                else if (MsgDiscardedRate < PUB_MIN_DiscardedRate)
                {
                    MsgCyclesNum = 2000;
                    //此处只保留1个线程
                    l_ptPthreadPool->m_n32MsgWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32MsgLivePthreadNum > 1) ? l_ptPthreadPool->m_n32MsgLivePthreadNum - 1 : 0);
                }

                if ((SecDiscardedRate < SEC_MAX_DiscardedRate) && (SecDiscardedRate >= PUB_MIN_DiscardedRate))
                {
                    SecCyclesNum = 5000;
                    //此处只保留3个线程
                    l_ptPthreadPool->m_n32SecWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32SecLivePthreadNum > 3) ? 1 : 0);
                }
                else if (SecDiscardedRate < PUB_MIN_DiscardedRate)
                {
                    SecCyclesNum = 2000;
                    //此处只保留1个线程
                    l_ptPthreadPool->m_n32SecWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32SecLivePthreadNum > 1) ? l_ptPthreadPool->m_n32SecLivePthreadNum - 1 : 0);
                }
            }
            else if ((CurrentCBR <= 60.00) && (CurrentCBR > 35.00))
            {
                if ((MsgDiscardedRate < MSG_MAX_DiscardedRate) && (MsgDiscardedRate >= PUB_MIN_DiscardedRate))
                {
                    MsgCyclesNum = 6000;
                    //此处只保留4个线程
                    l_ptPthreadPool->m_n32MsgWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32MsgLivePthreadNum > 4) ? 1 : 0);
                }
                else if (MsgDiscardedRate < PUB_MIN_DiscardedRate)
                {
                    MsgCyclesNum = 2000;
                    //此处只保留1个线程
                    l_ptPthreadPool->m_n32MsgWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32MsgLivePthreadNum > 1) ? l_ptPthreadPool->m_n32MsgLivePthreadNum - 1 : 0);
                }

                if ((SecDiscardedRate < SEC_MAX_DiscardedRate) && (SecDiscardedRate >= PUB_MIN_DiscardedRate))
                {
                    SecCyclesNum = 6000;
                    //此处只保留4个线程
                    l_ptPthreadPool->m_n32SecWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32SecLivePthreadNum > 4) ? 1 : 0);
                }
                else if (SecDiscardedRate < PUB_MIN_DiscardedRate)
                {
                    SecCyclesNum = 2000;
                    //此处只保留1个线程
                    l_ptPthreadPool->m_n32SecWaitDestroyPthreadNum =
                        ((l_ptPthreadPool->m_n32SecLivePthreadNum > 1) ? l_ptPthreadPool->m_n32SecLivePthreadNum - 1 : 0);
                }
            }

            pthread_mutex_unlock(&(l_ptPthreadPool->m_nPthreadPoolLock));
        }
    }
    return NULL;
}

void FD_STPthreadPoolFree(STthreadPool *p_ptPthreadPool)
{
    if (NULL == p_ptPthreadPool)
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "FD_PthreadPoolFree para is error.");
        return;
    }

    // 先释放结构体内部成员，再释放整个结构体
    if (p_ptPthreadPool->m_nTaskQueue)
    {
        free(p_ptPthreadPool->m_nTaskQueue);
        p_ptPthreadPool->m_nTaskQueue = NULL;
    }
    if (p_ptPthreadPool->m_nPthreadTidArray)
    {
        if (p_ptPthreadPool->m_nPthreadTidArray != NULL)
        {
            int i = 0;
            for (i = 0; i < p_ptPthreadPool->m_n32MaxPthreadNum; i++)
            {
                pthread_mutex_lock(&(p_ptPthreadPool->m_nPthreadTidArray[i].m_nPthreadLock));
                pthread_mutex_destroy(&(p_ptPthreadPool->m_nPthreadTidArray[i].m_nPthreadLock));
                pthread_cond_destroy(&(p_ptPthreadPool->m_nPthreadTidArray[i].m_nPthreadCond));
            }
            free(p_ptPthreadPool->m_nPthreadTidArray);
            p_ptPthreadPool->m_nPthreadTidArray = NULL;
        }

        pthread_mutex_lock(&(p_ptPthreadPool->m_nPthreadPoolLock));
        pthread_mutex_destroy(&(p_ptPthreadPool->m_nPthreadPoolLock));
        pthread_cond_destroy(&(p_ptPthreadPool->m_nTaskQueueNotEmpty));
    }
    free(p_ptPthreadPool);
    p_ptPthreadPool = NULL;
}

void FD_STPthreadPoolDestroy(STthreadPool *p_ptPthreadPool)
{
    if (NULL == p_ptPthreadPool)
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "FD_PthreadPoolDestroy para is error.");
        return;
    }
    // 用于遍历
    int i = 0;

    if (p_ptPthreadPool == NULL)
    {
        return;
    }

    p_ptPthreadPool->m_n32ShutDown = true;

    // 销毁所有阻塞在条件变量任务队列为空的线程
    for (i = 0; i < (p_ptPthreadPool->m_n32SecLivePthreadNum + p_ptPthreadPool->m_n32MsgLivePthreadNum); i++)
    {
        pthread_cond_broadcast(&(p_ptPthreadPool->m_nTaskQueueNotEmpty));
    }

    FD_STPthreadPoolFree(p_ptPthreadPool);

    LogPrint(LOG_LEVEL_INFO, "StackPthreadPool", "FD_PthreadPoolDestroy Success.");
}

int FD_STPthreadAlive(pthread_t p_nPthreadTid)
{
    int pthread_kill_error = pthread_kill(p_nPthreadTid, 0);
    if (ESRCH == pthread_kill_error)
    {
        return false;
    }

    return true;
}

int FD_STPthreadPoolAddTask(STthreadPool *p_ptPthreadPool, void *p_DataProcessFunction, void *p_Arg, enumAddTaskType p_TaskType)
{
    if ((NULL == p_ptPthreadPool) || (NULL == p_DataProcessFunction) || (0 > p_TaskType))
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "FD_PthreadPoolAddTask para is error.");
        return -1;
    }
    // 线程池处于关闭状态
    if (p_ptPthreadPool->m_n32ShutDown)
    {
        return -1;
    }
    pthread_mutex_lock(&(p_ptPthreadPool->m_nPthreadPoolLock));
    if (10 <= p_ptPthreadPool->m_n32QueueTaskSize)
    {
        pthread_mutex_unlock(&(p_ptPthreadPool->m_nPthreadPoolLock));
        return -1;
    }
    pthread_mutex_unlock(&(p_ptPthreadPool->m_nPthreadPoolLock));
    // 任务类型
    if (p_DataProcessFunction != NULL)
    {
        pthread_mutex_lock(&(p_ptPthreadPool->m_nPthreadPoolLock));

        // 入队列
        p_ptPthreadPool->m_nTaskQueue[p_TaskType].m_pvFunction = p_DataProcessFunction;
        p_ptPthreadPool->m_nTaskQueue[p_TaskType].m_pvArg = (void *)p_Arg;
        p_ptPthreadPool->m_nTaskQueue[p_TaskType].tasktype = p_TaskType;
        p_ptPthreadPool->m_n32QueueTaskSize++;
        // 添加任务后，任务队列不对空，叫醒阻塞在条件变量任务队列为空的线程，去执行任务
        pthread_mutex_unlock(&(p_ptPthreadPool->m_nPthreadPoolLock));
        //pthread_cond_signal(&(p_ptPthreadPool->m_nTaskQueueNotEmpty));
        return 0;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "Task type is error.");
        return -1;
    }

    return 0;
}

int FD_STGetPthreadpoolstate(STthreadPool *p_ptPthreadPool, TModule_NetComm_Cycle *pt_CycleDevState)
{
    if ((NULL == p_ptPthreadPool) || (NULL == pt_CycleDevState))
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "FD_GetPthreadpoolstate para is error.");
        return -1;
    }
    pthread_mutex_lock(&(p_ptPthreadPool->m_nPthreadPoolLock));
    pt_CycleDevState->m_u8AlivedThreadsinPool = p_ptPthreadPool->m_n32SecLivePthreadNum + p_ptPthreadPool->m_n32MsgLivePthreadNum;
    pt_CycleDevState->m_n32CurrentTasks = p_ptPthreadPool->m_n32QueueTaskSize;
    if ((0 > pt_CycleDevState->m_u8AlivedThreadsinPool) || (0 > pt_CycleDevState->m_n32CurrentTasks))
    {
        return -1;
    }
    pthread_mutex_unlock(&(p_ptPthreadPool->m_nPthreadPoolLock));
    return 0;
}

int FN_STPthreadPoolInit()
{
    P_STthreadpool = FD_STPthreadPoolCreate(PTHREADPOOL_MINNUM, PTHREADPOOL_MAXNUM, ADDTASKTOPTHREADPOOL_MAXNUM);
    if (P_STthreadpool == NULL)
    {
        LogPrint(LOG_LEVEL_ERR, "StackPthreadPool", "Stack Pthreadpool Init is  error");
        return -1;
    }
    else
    {
        LogPrint(LOG_LEVEL_INFO, "StackPthreadPool", "Stack Pthreadpool Init SUCCESS");
    }
    return 0;
}

void FN_STPthreadPoolDestroy()
{
    if (P_STthreadpool != NULL)
    {
        FD_STPthreadPoolDestroy(P_STthreadpool);
    }
}
