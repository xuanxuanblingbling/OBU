#ifndef _TIMER_H_
#define _TIMER_H_


int StartTimer(int s_delay,int ms_delay, void (*call_back)(int));
void StopTimer();

#endif