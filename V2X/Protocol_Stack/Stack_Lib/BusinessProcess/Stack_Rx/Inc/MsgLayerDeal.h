#ifndef _MSG_LAYER_DEAL_H_
#define _MSG_LAYER_DEAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "wj_Message_com.h"

    void *ThreadProcMsgRecv(void *pArg);
    void *ThreadProcMsgRecvFunc(void *pArg);
#ifdef __cplusplus
}
#endif

#endif
