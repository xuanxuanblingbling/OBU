#include "MyTimer.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <thread>
extern "C"
{
#include "wj_log.h"
#include "Timer.h"
}

MyTimer::MyTimer(int interval_ms)
{
    // m_TimerFd = timerfd_create(CLOCK_MONOTONIC, 0);
    // if (m_TimerFd < 0)
    // {
    //     return;
    // }
    // m_its.it_value.tv_sec = interval_ms / 1000;
    // m_its.it_value.tv_nsec = (interval_ms % 1000) * 1000000;
    // m_its.it_interval.tv_sec = 0;
    // m_its.it_interval.tv_nsec = 0;

    m_IsTimeout = 0;
    interval_Maxms = interval_ms;
    u64InTime = 0;
}

MyTimer::~MyTimer()
{
    // if (m_TimerFd != 0)
    //     close(m_TimerFd);
    LogPrint(LOG_LEVEL_DEBUG, "BG_TRANSMIT", "timer destroy\n");
}

int MyTimer::Start()
{
    // int ret = timerfd_settime(m_TimerFd, 0, &m_its, NULL);
    // std::thread th([this]() {
    //     uint64_t exp;
    //     ssize_t s;

    //     s = read(m_TimerFd, &exp, sizeof(uint64_t));
    //     if (s != sizeof(uint64_t))
    //     {
    //         LogPrint(LOG_LEVEL_ERR, "BG_TRANSMIT", "timer waitting error\n");
    //     }
    //     std::lock_guard<std::mutex> lk(m_mtx);
    //     m_IsTimeout = 1;
    // });
    // th.detach();
    // return ret;

    std::lock_guard<std::mutex> lk(m_mtx);
    u64InTime = st_Timestamp_now(3);
    return 0;
}

int MyTimer::Reset()
{
    // int ret = timerfd_settime(m_TimerFd, 0, &m_its, NULL);
    // return ret;

    std::lock_guard<std::mutex> lk(m_mtx);
    u64InTime = st_Timestamp_now(3);
    return 0;
}

int MyTimer::IsTimeout()
{
    // std::lock_guard<std::mutex> lk(m_mtx);
    // return m_IsTimeout;

    std::lock_guard<std::mutex> lk(m_mtx);
    uint64_t time = st_Timestamp_now(3);
    if (int(time - u64InTime) > interval_Maxms)
    {
        m_IsTimeout = 1;
    }
    return m_IsTimeout;
}
