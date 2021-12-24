#ifndef OSAL_TIMER_H
#define OSAL_TIMER_H

extern  int32_t TimerStart(uint64_t interval_ms);
extern  int32_t TimerExpired(int32_t timerfd);
extern  void TimerStop(int32_t timerfd);
#endif
