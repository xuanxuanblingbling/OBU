#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

int32_t OsalThreadCreate(pthread_t *p_ptPid, void *(*start_routine)(void *), void *para)
{
    pthread_attr_t attr = {0};
    int32_t ret = 0;

    if (NULL == p_ptPid)
    {
        goto EXIT;
    }

    ret = pthread_attr_init(&attr);
    if (0 != ret)
    {
        goto EXIT;
    }

    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (0 != ret)
    {
        goto EXIT_1;
    }

    ret = pthread_create(p_ptPid, &attr, start_routine, para);
    if (0 != ret)
    {
        goto EXIT_1;
    }

    ret = pthread_attr_destroy(&attr);
    if (0 != ret)
    {
        goto EXIT_2;
    }

    return 0;

EXIT_2:
    pthread_cancel(*p_ptPid);
EXIT_1:
    pthread_attr_destroy(&attr);
EXIT:
    return -1;
}

void OsalThreadDel(pthread_t p_tPid)
{
    pthread_cancel(p_tPid);
    pthread_join(p_tPid, NULL);     /*可能不需要*/
}
