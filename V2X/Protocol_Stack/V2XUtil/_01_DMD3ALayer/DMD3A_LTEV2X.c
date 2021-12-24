
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>

#include <netinet/in.h>
#include <arpa/inet.h>

//包含配置文件头文件
#include "ConfigModuleRW.h"
#include "wj_log.h"
#include "ipcq.h"
#include "v2x-status.h"
#include "V2XInterface.h"

pthread_mutex_t g_mutex_V2XSendData;

int LTEV2X_Init()
{
    return 0;
}

int LTEV2X_Rx_SetDevParam(void (*pFunRecvData)(RecvCallbackReturnInfo CallbackReturnInfo))
{
    return 0;
}

DLL_PUBLIC int V2X_SendData(SendDataInfo ag15SendDataInfo, SendDataReturnInfo *ag15SendDataReturnInfo)
{
    pthread_mutex_lock(&g_mutex_V2XSendData);
    pthread_mutex_unlock(&g_mutex_V2XSendData);
    return 0;
}

DLL_PUBLIC int V2X_Close()
{

    return 0;
}
DLL_PUBLIC float V2X_GetCBR()
{
    return 0;
}

DLL_PUBLIC int V2X_TxRx_Init(pFunRecvData MsgRx_CallBack)
{
    int ret = 0;
    //初始化互斥信号量
    pthread_mutex_init(&g_mutex_V2XSendData, NULL);

    ret = LTEV2X_Rx_SetDevParam(MsgRx_CallBack);
    if (ret < 0)
    {
        return ret;
    }

    ret = LTEV2X_Init();
    return ret;
}
