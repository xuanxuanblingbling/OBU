#ifndef _MY_TIMER_H_
#define _MY_TIMER_H_
#include <mutex>
class MyTimer
{
public:
    MyTimer(int interval_ms = 500);
    ~MyTimer();
    int Start();
    int Reset();
    int IsTimeout();

private:
    int m_TimerFd;
    struct itimerspec m_its;

    std::mutex m_mtx;
    int m_IsTimeout;
    int interval_Maxms;
    uint64_t u64InTime;
};

#endif