#include <sys/time.h>
#include <signal.h>
#include <string.h>
//static struct itimerval new_value;
extern "C"
{
#include "TimerProc.h"
}

int StartTimer(int s_delay,int ms_delay, void (*call_back)(int))
{
    signal(SIGALRM, call_back);
    struct itimerval new_value;
    memset(&new_value, 0, sizeof(new_value));

    new_value.it_interval.tv_sec = s_delay;
    new_value.it_interval.tv_usec = ms_delay * 1000;
    new_value.it_value.tv_sec = s_delay;
    new_value.it_value.tv_usec = ms_delay * 1000;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL);
    if (0 != ret)
    {
        return -1;
    }
    return 0;
}

void StopTimer()
{
    struct itimerval tv = {0};
    setitimer(ITIMER_REAL, &tv, NULL);
    signal(SIGALRM, SIG_IGN);
}

