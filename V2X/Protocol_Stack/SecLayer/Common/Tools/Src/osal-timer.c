#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <sys/ioctl.h>


int32_t TimerStart(uint64_t interval_ms)
{
    int32_t timerfd = 0;
    struct itimerspec its = {0};

    timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (timerfd < 0) 
    {
        return -1;
    }

    /* Start the timer */
    its.it_value.tv_sec = interval_ms / 1000;
    its.it_value.tv_nsec = (interval_ms % 1000) * 1000000;
    its.it_interval = its.it_value;

    if (timerfd_settime(timerfd, 0, &its, NULL) < 0) 
    {
        close(timerfd);
        return -1;
    }

    return timerfd;
}

int32_t TimerExpired(int32_t timerfd)
{
    uint64_t exp;
    ssize_t s;

    s = read(timerfd, &exp, sizeof(uint64_t));
    if (s != sizeof(uint64_t)) 
    {
        return -1;
    }

    return 0;
}

void TimerStop(int32_t timerfd)
{
    close(timerfd);
}
