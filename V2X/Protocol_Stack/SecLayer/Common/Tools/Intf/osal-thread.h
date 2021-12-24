#ifndef OSAL_THREAD_H
#define OSAL_THREAD_H

extern  int32_t OsalThreadCreate(pthread_t *p_ptPid, void *(*start_routine)(void *), void *para);

extern  void OsalThreadDel(pthread_t p_tPid);

#endif
