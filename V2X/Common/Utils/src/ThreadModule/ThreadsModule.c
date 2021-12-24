/***********************************************************************
 * 文 件 名 称 ： ThreadsModule.c
 * 功 能 描 述 ： 线程模型
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/

/*
** ===================================================================
**     Include files.
** ===================================================================
*/
#include "LinuxCommonHeader.h"
#include "ThreadModule.h"
#include "LinkedList.h"

#define MODULE_NAME "THREAD"
#include "Debug.h"

/*
** ===================================================================
**     mutex APIS defination.
** ===================================================================
*/
int THR_mutex_init(THR_mutex_t *mutex)
{
    int ret = E_EXIT_OK;
    pthread_mutexattr_t attr;
    ret |= pthread_mutexattr_init(&attr);

    /*This attr make sure of avoiding dead lock. */
    ret |= pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    ret |= pthread_mutex_init(mutex, &attr);
    pthread_mutexattr_destroy(&attr);
    return ret;
}

void THR_mutex_destroy(THR_mutex_t *mutex)
{
    if (pthread_mutex_destroy(mutex) != 0)
    {
        errMsg("pthread_mutex_destroy");
    }
}

int THR_mutex_try_lock(THR_mutex_t *mutex)
{
    int ret = E_EXIT_ERR;
    if ((ret = pthread_mutex_trylock(mutex)) != 0)
    {
        errMsg("pthread_mutex_trylock");
    }
    return ret;
}

int THR_mutex_lock(THR_mutex_t *mutex)
{
    int ret = E_EXIT_ERR;
    if ((ret = pthread_mutex_lock(mutex)) != 0)
    {
        errMsg("pthread_mutex_lock");
    }
    return ret;
}

int THR_mutex_unlock(THR_mutex_t *mutex)
{
    int ret = E_EXIT_ERR;
    if ((ret = pthread_mutex_unlock(mutex)) != 0)
    {
        errMsg("pthread_mutex_unlock");
    }
    return ret;
}

/*
** ===================================================================
**     cond APIS defination.
** ===================================================================
*/
int THR_cond_init(THR_cond_t *cond)
{
    int ret = E_EXIT_ERR;
    if ((ret = pthread_cond_init(cond, NULL)) != 0)
    {
        errMsg("pthread_cond_init");
    }
    return ret;
}

int THR_cond_destroy(THR_cond_t *cond)
{
    int ret = E_EXIT_ERR;
    if ((ret = pthread_cond_destroy(cond)) != 0)
    {
        errMsg("pthread_cond_destroy");
    }
    return ret;
}

int THR_cond_wait(THR_cond_t *cond, THR_mutex_t *mutex)
{
    int ret = E_EXIT_ERR;
    if ((ret = pthread_cond_wait(cond, mutex)) != 0)
    {
        //errMsg("pthread_cond_wait");
    }
    return ret;
}

static void get_interval_timeout(unsigned int ms, struct timespec *pTs)
{
    //必须使用CLOCK_REALTIME
    clock_gettime(CLOCK_REALTIME, pTs);
    pTs->tv_sec += ms / 1000U;
    //在ts的基础上，增加ms毫秒
    //pTs->tv_nsec为纳秒，1微秒=1000纳秒
    //tv_nsec此值再加上剩余的毫秒数 ms%1000，有可能超过1秒。需要特殊处理
    uint64_t us = pTs->tv_nsec / 1000 + 1000 * (ms % 1000);
    pTs->tv_sec += us / 1000000;
    us = us % 1000000;
    pTs->tv_nsec = us * 1000; //换算成纳秒
}

/* Waiting until get the set time milliseconds. */
int THR_cond_timed_wait(THR_cond_t *cond, THR_mutex_t *mutex, unsigned int ms)
{
    struct timespec ts;
    int ret = E_EXIT_ERR;

    get_interval_timeout(ms, &ts);
    //DBG("Cond wait:%d s, %d ns!", ts.tv_sec, ts.tv_nsec);
    ret = pthread_cond_timedwait(cond, mutex, &ts);
    switch (ret)
    {
    case 0:
        break;
    case ETIMEDOUT:
        return E_EXIT_EAGAIN;
    default:
        errMsg("pthread_cond_timedwait");
        break;
    }
    return ret;
}

int THR_cond_signal(THR_cond_t *cond)
{
    int ret = E_EXIT_ERR;
    if ((ret = pthread_cond_signal(cond)) != 0)
    {
        errMsg("pthread_cond_signal");
    }
    return ret;
}

int THR_cond_broadcast(THR_cond_t *cond)
{
    int ret = E_EXIT_ERR;
    if ((ret = pthread_cond_broadcast(cond)) != 0)
    {
        errMsg("pthread_cond_broadcast");
    }
    return ret;
}

/*
** ===================================================================
**     thread APIS defination.
** ===================================================================
*/
typedef struct _THR_thread_contex
{
    start_rtn_t func;
    void *arg;
    THR_tid_t tid;
    linkedlist_node node;
} THR_thread_context_t, *THR_thread_context;

static struct THR_thread_module
{
    bool is_inited;
    THR_mutex_t mutex;
    linkedlist threads_list;
} THR_thread_self;

THR_tid_t THR_thread_self_ID(void)
{
    return pthread_self();
}

static THR_thread_context THR_thread_find(THR_tid_t tid)
{
    linkedlist_node node = NULL;
    THR_thread_context ctx = NULL;

    do
    {
        THR_mutex_lock(&THR_thread_self.mutex);
        linkedlist_for_each(node, THR_thread_self.threads_list)
        {
            ctx = (THR_thread_context)(node->data);
            if (tid == ctx->tid)
            {
                THR_mutex_unlock(&THR_thread_self.mutex);
                break;
            }
        }
        THR_mutex_unlock(&THR_thread_self.mutex);
    } while (0);
    return ctx;
}

static THR_thread_context THR_thread_get_unlink(THR_tid_t tid)
{
    THR_thread_context ctx = NULL;
    do
    {
        THR_mutex_lock(&THR_thread_self.mutex);
        ctx = THR_thread_find(tid);
        if (ctx)
        {
            /* Unlink the thread from the thread linkedlist. */
            linkedlist_unlink(THR_thread_self.threads_list, ctx->node);
        }
        THR_mutex_unlock(&THR_thread_self.mutex);
    } while (0);
    return ctx;
}

static void *THR_start_routine(void *arg)
{
    THR_thread_context ctx = (THR_thread_context)arg;
    do
    {
        if (THR_thread_self.is_inited && ctx->func)
        {
            ctx->func(ctx->arg, THR_RUN);
        }
        else
        {
            errMsg("The THR_thread module does not init!");
            break;
        }
        THR_mutex_lock(&THR_thread_self.mutex);
        linkedlist_delete_node(THR_thread_self.threads_list, ctx->node);
        linkedlist_node_free(ctx);
        THR_mutex_unlock(&THR_thread_self.mutex);
        pthread_exit(NULL);
    } while (0);
    return NULL;
}

/*
 * @param:
 * tid_ptr:return the hanlde of the thread.
 * start_rtn:the thread routine function to running the app.
 * sched:thread attr init param to set the prioirity/policy and other init components.
 * arg:the param for the routine function. The arg normally the handle of the app module object.
 */
int THR_thread_create(THR_tid_t *tid_ptr, start_rtn_t start_rtn, THR_sched_t *sched, void *arg)
{
    int ret = E_EXIT_ERR;
    linkedlist_node node = NULL;

    if (!THR_thread_self.is_inited)
    {
        THR_thread_self.threads_list = linkedlist_alloc();
        linkedlist_init(THR_thread_self.threads_list);
        if (THR_mutex_init(&THR_thread_self.mutex))
        {
            errExit("THR_mutex_init");
        }
        THR_thread_self.is_inited = true;
    }
    THR_thread_context ctx = NEW(THR_thread_context_t, 1);
    ctx->func = start_rtn;
    ctx->arg = arg;
    do
    {
#ifdef PTHREAD_CANCEL_ASYNCHRONOUS
        if ((ret = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL)) != 0)
        {
            errMsg("pthread_setcanceltype");
            break;
        }
#endif
        THR_attr_t *attr_ptr = NULL;
        if (sched)
        {
            attr_ptr = &sched->attr;
        }
        ret = pthread_create(&ctx->tid, attr_ptr, THR_start_routine, (void *)ctx);
        if (ret != 0)
        {
            errExitEN(ret, "pthread_create");
        }

        THR_mutex_lock(&THR_thread_self.mutex);
        /* Store the contex of the thread as linkedlist. */
        node = linkedlist_append(THR_thread_self.threads_list, (DATA)ctx);
        if (!node)
        {
            THR_mutex_unlock(&THR_thread_self.mutex);
            errMsg("linkedlist_append");
            ret = E_EXIT_ENOMEM;
            break;
        }

        /* Return the tid and the node of the thread. */
        *tid_ptr = ctx->tid;
        ctx->node = node;
        THR_mutex_unlock(&THR_thread_self.mutex);
    } while (0);
    return ret;
}

int THR_thread_join(THR_tid_t tid, void **retval)
{
    int ret = E_EXIT_ERR;
    if ((ret = pthread_join(tid, retval)) != 0)
    {
        errMsg("pthread_join");
    }
    return ret;
}

void THR_thread_cancel(THR_tid_t tid)
{
#ifdef PTHREAD_CANCEL_ASYNCHRONOUS
    if (pthread_cancel(tid) != 0)
    {
        errMsg("pthread_cancel");
    }
#else
    if (pthread_kill(tid, SIGKILL) != 0)
    {
        errMsg("pthread_kill");
    }
#endif
}

void THR_thread_exit(void *retval)
{
    THR_tid_t tid_self = 0;
    THR_thread_context ctx = NULL;

    do
    {
        tid_self = THR_thread_self_ID();
        THR_mutex_lock(&THR_thread_self.mutex);
        ctx = THR_thread_get_unlink(tid_self);
        if (ctx)
        {
            linkedlist_node_free(ctx);
        }
        pthread_exit(retval);
        THR_mutex_unlock(&THR_thread_self.mutex);
    } while (0);
}

/*
** ===================================================================
**     THR sched APIS declaration.
** ===================================================================
*/

int THR_attr_init(THR_attr_t *attr_ptr)
{
    int ret = E_EXIT_ERR;
    if (!attr_ptr)
    {
        pr_err("Invalid param");
        return ret;
    }

    if ((ret = pthread_attr_init(attr_ptr)) != 0)
    {
        errMsg("pthread_attr_init");
    }
    return ret;
}

int THR_attr_deinit(THR_attr_t *attr_ptr)
{
    int ret = E_EXIT_ERR;
    if (!attr_ptr)
    {
        pr_err("Invalid param");
        return ret;
    }

    if ((ret = pthread_attr_destroy(attr_ptr)) != 0)
    {
        errMsg("pthread_attr_destroy");
    }
    return ret;
}

int THR_get_max_priority(THR_policy_t policy)
{
    return sched_get_priority_max(policy);
}

int THR_get_min_priority(THR_policy_t policy)
{
    return sched_get_priority_min(policy);
}

int THR_set_policy(THR_attr_t *attr_ptr, THR_policy_t policy)
{
    int ret = E_EXIT_ERR;
    if (!attr_ptr)
    {
        pr_err("Invalid param");
        return ret;
    }

    if ((ret = pthread_attr_setschedpolicy(attr_ptr, policy)) != 0)
    {
        errMsg("pthread_attr_setschedpolicy");
    }
    return ret;
}

int THR_get_policy(THR_attr_t *attr_ptr, THR_policy_t *policy_ptr)
{
    int ret = E_EXIT_ERR;
    if (!attr_ptr || !policy_ptr)
    {
        pr_err("Invalid param");
        return ret;
    }

    if ((ret = pthread_attr_getschedpolicy(attr_ptr, policy_ptr)) != 0)
    {
        errMsg("pthread_attr_getschedpolicy");
    }
    return ret;
}

int THR_set_priority(THR_attr_t *attr_ptr, int priority)
{
    int ret = E_EXIT_ERR;
    if (!attr_ptr)
    {
        pr_err("Invalid param");
        return ret;
    }

    THR_sched_param_t param;
    param.sched_priority = priority;
    if ((ret = pthread_attr_setschedparam(attr_ptr, &param)) != 0)
    {
        errMsg("pthread_attr_getschedpolicy");
    }
    return ret;
}

int THR_get_priority(THR_attr_t *attr_ptr, int *priority_ptr)
{
    int ret = E_EXIT_ERR;
    if (!attr_ptr || !priority_ptr)
    {
        pr_err("Invalid param");
        return ret;
    }

    THR_sched_param_t param;
    if ((ret = pthread_attr_getschedparam(attr_ptr, &param)) != 0)
    {
        errMsg("pthread_attr_getschedpolicy");
    }
    else
    {
        *priority_ptr = param.sched_priority;
    }
    return ret;
}

int THR_init_sched_properties(THR_sched_t *sched, bool is_detached)
{
    int ret = E_EXIT_ERR;
    if (!sched)
    {
        pr_err("Invalid param");
        return ret;
    }

    if (sched->policy != THR_SCHED_FIFO &&
        sched->policy != THR_SCHE_RR &&
        sched->policy != THR_SCHED_OTHER)
    {
        sched->policy = THR_SCHED_OTHER; /* Set the default policy od SCHED_OTHER. */
    }

    if (sched->param.sched_priority > THR_get_max_priority(sched->policy))
    {
        sched->param.sched_priority = DEF_HIGHEST_SCHED_PRORITY;
    }

    ret = THR_attr_init(&sched->attr);
    ret |= THR_set_policy(&sched->attr, sched->policy);
    if (sched->param.sched_priority > 0)
    {
        ret |= pthread_attr_setinheritsched(&sched->attr, PTHREAD_EXPLICIT_SCHED);
        ret |= THR_set_priority(&sched->attr, sched->param.sched_priority);
    }

    if (is_detached)
        ret |= pthread_attr_setdetachstate(&sched->attr, PTHREAD_CREATE_DETACHED);

    return ret;
}

int THR_deinit_sched_properties(THR_sched_t *sched)
{
    int ret = E_EXIT_ERR;
    if (!sched)
    {
        pr_err("Invalid param");
        return ret;
    }

    ret = THR_attr_deinit(&sched->attr);
    return ret;
}

/* 设置主线程的优先级，子线程默认继承父进程的优先级和属性. */
int THR_set_main_pthread_param(THR_dynamic_sched_t *sched)
{
    int ret = E_EXIT_ERR;
    if (!sched)
    {
        pr_err("Invalid param");
        return ret;
    }

    if (sched->policy != THR_SCHED_FIFO &&
        sched->policy != THR_SCHE_RR &&
        sched->policy != THR_SCHED_OTHER)
    {
        sched->policy = THR_SCHED_OTHER; /* Set the default policy od SCHED_OTHER. */
    }

    if (sched->param.sched_priority > THR_get_max_priority(sched->policy))
    {
        sched->param.sched_priority = DEF_HIGHEST_SCHED_PRORITY;
    }
    if (sched->param.sched_priority > 0)
        ret = pthread_setschedparam(pthread_self(), sched->policy, &sched->param);
    return ret;
}

/* 动态获取线程的优先级和调度策略 */
int THR_get_pthread_param_dynamic(THR_dynamic_sched_t *sched)
{
    int ret = E_EXIT_ERR;
    if (!sched)
    {
        pr_err("Invalid param");
        return ret;
    }
    bzero(sched, sizeof(THR_dynamic_sched_t));
    ret = pthread_getschedparam(pthread_self(), &sched->policy, &sched->param);
    return ret;
}
