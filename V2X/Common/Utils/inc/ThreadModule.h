/***********************************************************************
 * 文 件 名 称 ： ThreadModule.h
 * 功 能 描 述 ： 线程模型
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/

#ifndef __THREAD_MODULE_H__
#define __THREAD_MODULE_H__

#include "V2xBasicTypes.h"

V2X_BEGIN_HEADER

#include <pthread.h>
typedef pthread_t THR_tid_t;
typedef pthread_mutex_t THR_mutex_t;
typedef pthread_cond_t THR_cond_t;

#include <sched.h>
#define THR_SCHED_OTHER SCHED_OTHER /* 分时调度策略 */
#define THR_SCHED_FIFO SCHED_OTHER  /* 实时调度策略，先到先服务。一旦占用cpu则一直运行。一直运行直到有更高优先级任务到达或自己放弃 */
#define THR_SCHE_RR SCHED_RR        /* 实时调度策略，时间片轮转。当进程的时间片用完，系统将重新分配时间片，并置于就绪队列尾。放在队列尾保证了所有具有相同优先级的RR任务的调度公平 */

#define DEF_HIGHEST_SCHED_PRORITY 98U
#define DEF_HIGHER_SCHED_PRORITY 90U
#define DEF_INTER_SCHED_PRIORITY 80U
#define DEF_LOW_SCHED_PRIORITY 70U

typedef pthread_attr_t THR_attr_t;
typedef int THR_policy_t;
typedef struct sched_param THR_sched_param_t;

typedef struct
{
    THR_policy_t policy;
    THR_attr_t attr;
    THR_sched_param_t param;
} THR_sched_t;

typedef struct
{
    THR_policy_t policy;
    THR_sched_param_t param;
} THR_dynamic_sched_t;

/* The state of the main cyle function. */
enum
{
    THR_RUN = 0,
    THR_STOP = 1,
    THR_EXIT = 2
};

/*
** ===================================================================
**     THR mutex APIS declaration.
** ===================================================================
*/

/* init the mutex */
V2X_EXTERN int THR_mutex_init(THR_mutex_t *mutex);

/* Free the mutex */
V2X_EXTERN void THR_mutex_destroy(THR_mutex_t *mutex);

/* Try lock the mutex */
V2X_EXTERN int THR_mutex_try_lock(THR_mutex_t *mutex);

/* Lock the mutex */
V2X_EXTERN int THR_mutex_lock(THR_mutex_t *mutex);

/* Unlock the mutex */
V2X_EXTERN int THR_mutex_unlock(THR_mutex_t *mutex);

/*
** ===================================================================
**     THR cond APIS declaration.
** ===================================================================
*/

/** Init one cond variable. */
V2X_EXTERN int THR_cond_init(THR_cond_t *cond);

/** Destroy one cond variable. */
V2X_EXTERN int THR_cond_destroy(THR_cond_t *cond);

/** Block the current thread until the condition is ready. */
V2X_EXTERN int THR_cond_wait(THR_cond_t *cond, THR_mutex_t *mutex);

/** Block the current thread util the condition ready within assigned time. */
V2X_EXTERN int THR_cond_timed_wait(THR_cond_t *cond, THR_mutex_t *mutex, unsigned int ms);

/** Signal special thread to contiue run. */
V2X_EXTERN int THR_cond_signal(THR_cond_t *cond);

/** Broadcast to all the threads to keep alive. */
V2X_EXTERN int THR_cond_broadcast(THR_cond_t *cond);

/*
** ===================================================================
**     THR thread APIS declaration.
** ===================================================================
*/
typedef int (*start_rtn_t)(void *p_obj, int cur_state);

V2X_EXTERN THR_tid_t THR_thread_self_ID(void);

/* Create and run the thread. */
V2X_EXTERN int THR_thread_create(THR_tid_t *tid_ptr, start_rtn_t start_rtn, THR_sched_t *sched, void *arg);

/* Release the resource of the thread after the thread exit. */
V2X_EXTERN int THR_thread_join(THR_tid_t thread, void **retval);

/* Cancel one thread */
V2X_EXTERN void THR_thread_cancel(THR_tid_t thread);

/* Record the returned value, and exit. */
V2X_EXTERN void THR_thread_exit(void *retval);

/*
** ===================================================================
**     THR sched APIS declaration.
** ===================================================================
*/

V2X_EXTERN int THR_attr_init(THR_attr_t *attr_ptr);
V2X_EXTERN int THR_attr_deinit(THR_attr_t *attr_ptr);
V2X_EXTERN int THR_get_max_priority(THR_policy_t policy);
V2X_EXTERN int THR_get_min_priority(THR_policy_t policy);
V2X_EXTERN int THR_set_policy(THR_attr_t *attr_ptr, THR_policy_t policy);
V2X_EXTERN int THR_get_policy(THR_attr_t *attr_ptr, THR_policy_t *policy_ptr);
V2X_EXTERN int THR_set_priority(THR_attr_t *attr_ptr, int priority);
V2X_EXTERN int THR_get_priority(THR_attr_t *attr_ptr, int *priority_ptr);
V2X_EXTERN int THR_init_sched_properties(THR_sched_t *sched, bool is_detached);
V2X_EXTERN int THR_deinit_sched_properties(THR_sched_t *sched);
V2X_EXTERN int THR_set_main_pthread_param(THR_dynamic_sched_t *sched);
V2X_EXTERN int THR_get_pthread_param_dynamic(THR_dynamic_sched_t *sched);

V2X_END_HEADER

#endif
