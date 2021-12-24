/***********************************************************************
 * 文 件 名 称 ： Worker.c
 * 功 能 描 述 ： 线程工作组模型
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/

#include "Worker.h"

#define MODULE_NAME "WORKER"
#include "Debug.h"

static void THR_worker_thread_init(THR_worker worker)
{
    BZERO(worker, THR_worker);
    worker->active = false;
    worker->tid = 0;
    worker->pObj = NULL;
    THR_mutex_init(&worker->mutex);
    THR_cond_init(&worker->cond);
}

THR_worker THR_worker_new(void)
{
    THR_worker new_worker = NEW(THR_worker_t, 1);
    THR_worker_thread_init(new_worker);
    return new_worker;
}

/* The arg is the param of the start_rtn_func, usally give the handle of the app. */
int THR_worker_thread_create(THR_worker worker, start_rtn_t start_rtn_func, THR_sched_t *sched, void *pObj)
{
    if (!worker || !start_rtn_func || !pObj)
    {
        pr_err("Invalid param!");
        return E_EXIT_EINVAL;
    }

    int ret = E_EXIT_ERR;
    do
    {
        worker->pObj = pObj;
        worker->active = true;
        ret = THR_thread_create(&worker->tid, start_rtn_func, sched, pObj);
        if (ret)
        {
            pr_err("Failed to THR_thread_create!");
            break;
        }
    } while (0);
    return ret;
}

void THR_worker_thread_signal(THR_worker worker)
{
    THR_mutex_lock(&worker->mutex);
    THR_cond_signal(&worker->cond);
    THR_mutex_unlock(&worker->mutex);
}

void THR_worker_thread_broadcast(THR_worker worker)
{
    THR_mutex_lock(&worker->mutex);
    THR_cond_broadcast(&worker->cond);
    THR_mutex_unlock(&worker->mutex);
}

void THR_worker_thread_destroy(THR_worker worker)
{
    THR_mutex_lock(&worker->mutex);
    worker->active = false;
    THR_cond_broadcast(&worker->cond);
    THR_mutex_unlock(&worker->mutex);
    if (worker->joinable)
        THR_thread_join(worker->tid, NULL);
    THR_mutex_destroy(&worker->mutex);
    THR_cond_destroy(&worker->cond);
}
