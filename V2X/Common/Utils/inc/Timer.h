/*******************************************************************************
 * 文 件 名 称 ： Timer.h
 * 功 能 描 述 ： POSIX精准时钟封装
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>

    enum
    {
        TIMER_OK = 0,
        TIMER_INVLID = -1,
        TIMER_DLY_MAX = 1
    };

    typedef struct
    {
        timer_t timerid;
        pthread_mutex_t lock;
        uint32_t period_s;
        uint32_t period_ms;
    } OSA_TimerHndl;

    typedef void (*OSA_TimerCb)(union sigval value);

    int32_t OSA_timerCreate(OSA_TimerHndl *hndl, OSA_TimerCb cbf, union sigval sevVal);
    int32_t OSA_timerDelete(OSA_TimerHndl *hndl);
    int32_t OSA_timerStart(OSA_TimerHndl *hndl);
    int32_t OSA_timerStop(OSA_TimerHndl *hndl);
    int32_t OSA_getTimerOverRun(OSA_TimerHndl *hndl);
    int32_t OSA_DelayTimerReachMax(OSA_TimerHndl *hndl);

    typedef unsigned long long utils_timer;

    utils_timer utils_timer_ms();
    utils_timer utils_timer_us();
    utils_timer utils_timer_s();
    void OSA_secondsleep(uint32_t p_u32seconds);
    void OSA_millisecondsleep(uint64_t p_u64mSec);
    void OSA_microsecondsleep(uint64_t p_u64uSec);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif