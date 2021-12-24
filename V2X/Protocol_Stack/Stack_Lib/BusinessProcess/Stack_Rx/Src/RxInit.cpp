#include <pthread.h>
#include <stdio.h>
#include "RxInit.h"
extern "C"
{
#include "NetLayerDeal.h"
#include "MsgLayerDeal.h"
#include "SecLayerDeal.h"
#include "STpthreadpool.h"
#include "ConfigModuleRW.h"
}

//用于各个层次丢包率的计算
int NetRecvStart = 0;
int NetRecvError = 0;
int NetRecvEnd = 0;

double SecDiscardedRate = 0.00;
int SecRecvStart = 0;
int SecRecvDis = 0;
int SecRecvError = 0;
int SecRecvEnd = 0;

double MsgDiscardedRate = 0.00;
int MsgRecvStart = 0;
int MsgRecvError = 0;
int MsgRecvEnd = 0;

double CurrentCBR = 0.00;
int SecCyclesNum = 6000;
int MsgCyclesNum = 6000;
/**
 * @brief 程序启动及退出时，动态加载动态库版本信息
 */
__attribute__((constructor)) static void
so_init(void);
__attribute__((destructor)) static void so_deinit(void);

void so_init(void)
{
    printf("%s !!! Current Version - LibVsersionID(%s) start!!!\n", __DATE__, (char *)LibVsersionID);
}

void so_deinit(void)
{
    if (ProtocolStackParamConfig.thirdPartyLibConfig.PthreadStateAdjust == 1)
    {
        FN_STPthreadPoolDestroy();
    }

    printf("%s !!! Current Version - LibVsersionID(%s) end!!!\n", __DATE__, (char *)LibVsersionID);
}

__attribute__((visibility("default"))) int StackRecvInit()
{
    if (ProtocolStackParamConfig.thirdPartyLibConfig.PthreadStateAdjust == 1)
    {
        //初始化
        FN_STPthreadPoolInit();
        FD_STPthreadPoolAddTask(P_STthreadpool, (void *)ThreadProcMsgRecvFunc, NULL, enumMsg);
        FD_STPthreadPoolAddTask(P_STthreadpool, (void *)SecLayer_Recv_ThreadProcFunc, NULL, enumSec);
    }
    else if (ProtocolStackParamConfig.thirdPartyLibConfig.PthreadStateAdjust == 0)
    {
        pthread_t th_msg_layer;
        pthread_t th_sec_layer;

        pthread_attr_t l_tpthreadattr = {0};
        struct sched_param l_pthreadparam = {0};
        l_pthreadparam.sched_priority = 94;
        pthread_attr_init(&l_tpthreadattr);
        pthread_attr_setschedpolicy(&l_tpthreadattr, SCHED_RR);
        pthread_attr_setschedparam(&l_tpthreadattr, &l_pthreadparam);
        pthread_attr_setinheritsched(&l_tpthreadattr, PTHREAD_EXPLICIT_SCHED);

        pthread_attr_t l_tpthreadattrMSG = {0};
        struct sched_param l_pthreadparamMSG = {0};
        l_pthreadparamMSG.sched_priority = 92;
        pthread_attr_init(&l_tpthreadattrMSG);
        pthread_attr_setschedpolicy(&l_tpthreadattrMSG, SCHED_RR);
        pthread_attr_setschedparam(&l_tpthreadattrMSG, &l_pthreadparamMSG);
        pthread_attr_setinheritsched(&l_tpthreadattrMSG, PTHREAD_EXPLICIT_SCHED);

        //执行修改调度策略，需要在ROOT权限下来执行

        //消息层双线程处理16个数据，平均处理8个
        pthread_create(&th_msg_layer, &l_tpthreadattrMSG, ThreadProcMsgRecv, NULL);
        pthread_detach(th_msg_layer);

        //为降低消息层丢包率，消息可启动双线程解码,双线程可同时执行
        // pthread_t th_msg_layer1;
        // pthread_create(&th_msg_layer1, &l_tpthreadattrMSG, ThreadProcMsgRecv, NULL);
        // pthread_detach(th_msg_layer1);

        //安全层双线程处理16个数据，最坏情况下单线程验签处理32
        /* 创建线程，并将优先级设置为最高 */
        pthread_create(&th_sec_layer, &l_tpthreadattr, SecLayer_Recv_ThreadProc, NULL);
        pthread_detach(th_sec_layer);

        //为降低安全层丢包率，安全层可启动双线程验签，双线程取数据，单线程验签，实际作用增大验签消息队列
        // pthread_t th_sec_layer1;
        // pthread_create(&th_sec_layer1, &l_tpthreadattr, SecLayer_Recv_ThreadProc, NULL);
        // pthread_detach(th_sec_layer1);
    }

    return 0;
}
