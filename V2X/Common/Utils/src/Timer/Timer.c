/*******************************************************************************
 * 文 件 名 称 ： Timer.c
 * 功 能 描 述 ： POSIX精准时钟封装
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#include "LinuxCommonHeader.h"
#include "Timer.h"

#define MODULE_NAME "TIMER"
#include "Debug.h"

int32_t OSA_timerCreate(OSA_TimerHndl *hndl, OSA_TimerCb cbf, union sigval value)
{
    int32_t retVal = -1;
    pthread_mutexattr_t mutex_attr;
    struct sigevent sev;

    retVal = pthread_mutexattr_init(&mutex_attr);
    retVal += pthread_mutex_init(&hndl->lock, &mutex_attr);

    memset(&sev, 0, sizeof(sev));

    sev.sigev_notify = SIGEV_THREAD;             /* Notify via thread */
    sev.sigev_value.sival_int = value.sival_int; /*Callback function params */
    sev.sigev_value.sival_ptr = value.sival_ptr; /*Callback function params */
    sev.sigev_notify_function = cbf;             /* callback start function */
    sev.sigev_notify_attributes = NULL;

    /* Create Real Time Timer */
    retVal = timer_create(CLOCK_REALTIME, &sev, &hndl->timerid);
    if (retVal < 0)
    {
        ERR(" OSA_TIMER: Could not create Timer\n");
        assert(0);
    }

    INF("timer ID is 0x%lx\n", (long)hndl->timerid);
    pthread_mutexattr_destroy(&mutex_attr);

    return retVal;
}

int32_t OSA_timerDelete(OSA_TimerHndl *hndl)
{
    int32_t retVal = -1;
    struct itimerspec value = {{0, 0}, {0, 0}};

    pthread_mutex_lock(&hndl->lock);

    /* Disarm Timer */
    retVal = timer_settime(hndl->timerid, 0, &value, NULL);
    retVal += timer_delete(hndl->timerid);
    pthread_mutex_unlock(&hndl->lock);

    pthread_mutex_destroy(&hndl->lock);

    return retVal;
}

int32_t OSA_timerStart(OSA_TimerHndl *hndl)
{
    int32_t retVal = -1;
    struct itimerspec value = {{0, 0}, {0, 0}};
    value.it_value.tv_sec = hndl->period_s;
    value.it_value.tv_nsec = hndl->period_ms * 1000000;
    value.it_interval.tv_sec = hndl->period_s;
    value.it_interval.tv_nsec = hndl->period_ms * 1000000;

    pthread_mutex_lock(&hndl->lock);
    /* Arm Timer */
    retVal = timer_settime(hndl->timerid, 0, &value, NULL);
    pthread_mutex_unlock(&hndl->lock);

    return retVal;
}

int32_t OSA_timerStop(OSA_TimerHndl *hndl)
{
    int32_t retVal = -1;
    struct itimerspec value = {{0, 0}, {0, 0}};
    pthread_mutex_lock(&hndl->lock);
    /* Disarm Timer */
    retVal = timer_settime(hndl->timerid, 0, &value, NULL);

    pthread_mutex_unlock(&hndl->lock);

    return retVal;
}

int32_t OSA_getTimerOverRun(OSA_TimerHndl *hndl)
{
    return timer_getoverrun(hndl->timerid);
}

int32_t OSA_DelayTimerReachMax(OSA_TimerHndl *hndl)
{
    int count;
    if ((count = OSA_getTimerOverRun(hndl)) < 0)
    {
        ERR("OSA_getTimerOverRun\n");
        return TIMER_INVLID;
    }
    else if (DELAYTIMER_MAX == count)
    {
        return TIMER_DLY_MAX;
    }
    else
    {
        return TIMER_OK;
    }
}

utils_timer utils_timer_ms()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

utils_timer utils_timer_us()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
}

utils_timer utils_timer_s()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec);
}

void OSA_secondsleep(uint32_t p_u32seconds)
{
    struct timeval l_ttv = {0};
    l_ttv.tv_sec = p_u32seconds;
    l_ttv.tv_usec = 0;
    int32_t l_n32err = 0;
    do
    {
        l_n32err = select(0, NULL, NULL, NULL, &l_ttv);
    } while ((l_n32err < 0) && (EINTR == errno));
    return;
}

void OSA_millisecondsleep(uint64_t p_u64mSec)
{
    struct timeval l_ttv = {0};
    l_ttv.tv_sec = p_u64mSec / 1000;
    l_ttv.tv_usec = (p_u64mSec % 1000) * 1000;
    int l_n32err = 0;
    do
    {
        l_n32err = select(0, NULL, NULL, NULL, &l_ttv);
    } while ((l_n32err < 0) && (EINTR == errno));
    return;
}

void OSA_microsecondsleep(uint64_t p_u64uSec)
{
    struct timeval l_ttv = {0};
    l_ttv.tv_sec = p_u64uSec / 1000000;
    l_ttv.tv_usec = p_u64uSec % 1000000;
    int32_t l_n32err = 0;
    do
    {
        l_n32err = select(0, NULL, NULL, NULL, &l_ttv);
    } while ((l_n32err < 0) && (EINTR == errno));
    return;
}