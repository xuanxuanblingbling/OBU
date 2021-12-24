/***********************************************************************
 * 文 件 名 称 ： Worker.h
 * 功 能 描 述 ： 线程工作组模型
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/

#ifndef __WORKER__
#define __WORKER__

#include "V2xBasicTypes.h"
#include "ThreadModule.h"

V2X_BEGIN_HEADER

typedef struct _THR_worker
{
    void *pObj;
    bool active;
    bool joinable;
    THR_cond_t cond;
    THR_mutex_t mutex;
    THR_tid_t tid;
} THR_worker_t, *THR_worker;

V2X_EXTERN THR_worker THR_worker_new(void);
V2X_EXTERN int THR_worker_thread_create( THR_worker worker, start_rtn_t start_rtn_func, THR_sched_t *sched, void* pObj );
V2X_EXTERN void THR_worker_thread_signal(THR_worker worker);
V2X_EXTERN void THR_worker_thread_broadcast(THR_worker worker);
V2X_EXTERN void THR_worker_thread_destroy(THR_worker worker);

V2X_END_HEADER

#endif
