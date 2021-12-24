/*******************************************************************************
 * 文 件 名 称 ： main.c
 * 功 能 描 述 ： 数据服务模块主进程
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#include "Common.h"
#include "v2x_dbus.h"
#include "SWversynchronise.h"

#define MODULE_NAME "BSMTx"
#include "Debug.h"
#include <semaphore.h>

#define THREAD_INTERVAL 10U
#define COMMON_INTERVAL 5U
#define MONITOR_CYCLE_TIMER 100U

#define V2X_SOFTVERSION "WJ_OBU_V2X_20210714"
#define module "V2X"


//全局变量
TPObjSetHndl_t g_tPObjSet = {NULL};

//全局在线配置变量
TV2XOnLineConfigType g_tV2XOnlineCfg;

//安全层回调函数响应全局变量
static uint8_t g_u8IsRecvdSecurityUpdate = 0;

sem_t *m_sem = NULL;

static void FV_OnDestroy(DATA data)
{
    if (data)
    {
        free((void *)data);
        data = (DATA)NULL;
    }
}

static void FV_destroy_main_worker(TMainProcObjHdl p_ptMainProcObj)
{
    THR_mutex_lock(&p_ptMainProcObj->m_Worker->mutex);
    p_ptMainProcObj->m_Worker->active = false;
    THR_cond_broadcast(&p_ptMainProcObj->m_Worker->cond);
    THR_mutex_unlock(&p_ptMainProcObj->m_Worker->mutex);
    THR_mutex_destroy(&p_ptMainProcObj->m_Worker->mutex);
    THR_cond_destroy(&p_ptMainProcObj->m_Worker->cond);
}

static void FV_MainProcThreadsErrorExit(TMainProcObjHdl p_ptMainProcObj)
{
    THR_worker_thread_signal(p_ptMainProcObj->m_Worker);
}

static void FV_RecreatThreadsAccordingAliveStatus(void)
{
    int l_n32ThrBsmKillerErr, l_n32ThrV2xKillerErr, l_n32ThrGdbusKillerErr;

    l_n32ThrBsmKillerErr = pthread_kill(g_tPObjSet.m_BsmPObj->m_Worker->tid, 0);
    l_n32ThrV2xKillerErr = pthread_kill(g_tPObjSet.m_V2xStackPObj->m_Worker->tid, 0);
    l_n32ThrGdbusKillerErr = pthread_kill(g_tPObjSet.m_GdbusPObj->m_Worker->tid, 0);

    if (ESRCH == l_n32ThrBsmKillerErr)
    {
        g_tPObjSet.m_BsmPObj->m_IsInited = false;
        g_tPObjSet.m_BsmPObj->m_Worker->active = false;
        FV_FreeBsmGlobalBuffer();
        THR_worker_thread_create(g_tPObjSet.m_BsmPObj->m_Worker, FV_BsmMessageProcessThread, &g_tPObjSet.m_BsmPObj->sched, g_tPObjSet.m_BsmPObj);
        OSA_millisecondsleep(THREAD_INTERVAL);
        THR_worker_thread_signal(g_tPObjSet.m_BsmPObj->m_Worker);
        OSA_millisecondsleep(THREAD_INTERVAL);
    }
    if (ESRCH == l_n32ThrV2xKillerErr)
    {
        g_tPObjSet.m_V2xStackPObj->m_IsInited = false;
        g_tPObjSet.m_V2xStackPObj->m_Worker->active = false;
        THR_worker_thread_create(g_tPObjSet.m_V2xStackPObj->m_Worker, FV_V2xStackHandleMessageThread, &g_tPObjSet.m_V2xStackPObj->sched, g_tPObjSet.m_V2xStackPObj);
        OSA_millisecondsleep(THREAD_INTERVAL);
        THR_worker_thread_signal(g_tPObjSet.m_V2xStackPObj->m_Worker);
        OSA_millisecondsleep(THREAD_INTERVAL);
    }
    if (ESRCH == l_n32ThrGdbusKillerErr)
    {
        g_tPObjSet.m_GdbusPObj->m_IsInited = false;
        g_tPObjSet.m_GdbusPObj->m_Worker->active = false;
        FV_deinit_v2x_dbus_communication();
        OSA_millisecondsleep(THREAD_INTERVAL);
        THR_worker_thread_create(g_tPObjSet.m_GdbusPObj->m_Worker, FV_GdbusProcessMessageThread, NULL, g_tPObjSet.m_GdbusPObj);
        OSA_millisecondsleep(THREAD_INTERVAL);
        THR_worker_thread_signal(g_tPObjSet.m_GdbusPObj->m_Worker);
    }
}

/***********************************************************************
 * 函 数 名 称 ：FV_GdbusProcessMessageThread
 * 功 能 描 述 ：Gdbus线程运行函数
 * 输 入 参 数 ：p_pvArg：线程参数
 * 输 入 参 数 ：p_n32CurState：线程状态
 * 输 出 参 数 ：无
 * 返  回  值  :  E_EXIT_OK
 * 开 发 人 员 ：姚志强
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/
int FV_GdbusProcessMessageThread(void *p_pvArg, int p_n32CurState)
{
    TModuleObjHdl l_ptObj = (TModuleObjHdl)p_pvArg;

    if (!l_ptObj->m_IsInited)
    {
        THR_cond_wait(&l_ptObj->m_Worker->cond, &l_ptObj->m_Worker->mutex);
        l_ptObj->m_IsInited = true;
        INF("%s Start\n", __func__);
    }

    //开启dbus循环接收
    FV_DbusMainLoopStart();
    if (l_ptObj->m_Worker->active)
    {
        THR_mutex_lock(&l_ptObj->m_Worker->mutex);
        THR_cond_wait(&l_ptObj->m_Worker->cond, &l_ptObj->m_Worker->mutex);
        THR_mutex_unlock(&l_ptObj->m_Worker->mutex);
    }

    INF("%s quit\n", __func__);
    l_ptObj->m_Worker->active = false;
    l_ptObj->m_IsInited = false;
    THR_thread_exit(NULL);
    return E_EXIT_OK;
}

static void FV_StartTimerCycle(TModuleObjHdl p_ptObj, uint32_t p_u32TimerS, uint32_t p_u32TimerMS)
{
    OSA_TimerHndl l_tTimerHndl = p_ptObj->m_ObjTimerHndl.m_TimerHndl;
    l_tTimerHndl.period_s = p_u32TimerS;
    l_tTimerHndl.period_ms = p_u32TimerMS;
    OSA_timerStart(&l_tTimerHndl);
}

static void FV_StopAndDeleteTimerCycle(TModuleObjHdl p_ptObj)
{
    OSA_TimerHndl l_tTimerHndl = p_ptObj->m_ObjTimerHndl.m_TimerHndl;
    OSA_timerStop(&l_tTimerHndl);
    OSA_timerDelete(&l_tTimerHndl);
}

static void FV_CreateOrRecreateTimer(bool p_bReCreate, TModuleObjHdl p_ptObj, OSA_TimerCb p_fTimerCbFunc)
{
    if (p_bReCreate)
    {
        FV_StopAndDeleteTimerCycle(p_ptObj);
    }
    p_ptObj->m_ObjTimerHndl.m_UnValue.sival_ptr = p_ptObj;
    OSA_timerCreate(&p_ptObj->m_ObjTimerHndl.m_TimerHndl, p_fTimerCbFunc, p_ptObj->m_ObjTimerHndl.m_UnValue);
}

static void FV_MonitorThreadsTimer(void)
{
    int ret;
    // if ((ret = OSA_DelayTimerReachMax(&g_tPObjSet.m_BsmPObj->m_ObjTimerHndl.m_TimerHndl)) < 0)
    // {
    //     ERR("Invlid timer handle!\n");
    // }
    // else if (TIMER_DLY_MAX == ret)
    // {
    //     INF("Bsm timer delay overun DELAYTIMER_MAX\n");
    //     FV_FreeBsmGlobalBuffer();
    //     FV_CreateOrRecreateTimer(true, g_tPObjSet.m_BsmPObj, FV_BsmProcessMsgTimerCb);
    //     FV_StartTimerCycle(g_tPObjSet.m_BsmPObj, 0, DEF_BSM_CYCLE);
    // }

    if ((ret = OSA_DelayTimerReachMax(&g_tPObjSet.m_ServicePObj->m_ObjTimerHndl.m_TimerHndl)) < 0)
    {
        ERR("Invlid timer handle!\n");
    }
    else if (TIMER_DLY_MAX == ret)
    {
        INF("Service timer delay overun DELAYTIMER_MAX\n");
        FV_CreateOrRecreateTimer(true, g_tPObjSet.m_ServicePObj, FV_ServiceCycleCheckTimerCb);
        FV_StartTimerCycle(g_tPObjSet.m_ServicePObj, DEF_SVC_CYCLE, 0);
    }
}

//get Cert switch state callback
void FV_recv_notify_pachange_process(void *para, struct seclayer_status_t *sta)
{

    LogPrint(LOG_LEVEL_INFO, "BSMTx", "recv_notify_pachange\n");
    UpdataTrigger_L2_ID();
    g_u8IsRecvdSecurityUpdate = 1;
}

uint8_t FV_IsSecurityCertUpdate(void)
{
    return g_u8IsRecvdSecurityUpdate;
}

void FV_ResetSecurityCertUpdateFlag(void)
{
    g_u8IsRecvdSecurityUpdate = 0;
}

//应用层编写回调函数，供安全层使用，主要作用通知应用层安全证书已经切换
static void seclayer_cert_status_callback(struct seclayer_status_t *sta, void *para)
{
    if(sta != NULL)       //否则会出现段错误
    {
        // LogPrint(LOG_LEVEL_INFO, "BSMTx", "SecLayData.Cert_Switchstate : %d\n", sta->cert_change_flg);
        // printf("SecLayData.Cert_Switchstate : %d\n", sta->cert_change_flg);
    }
}
//应用层编写回调函数，供协议栈使用，主要作用完成消息发送
static void SendingCallback(SendCallbackReturnInfo callbackReturnInfo)
{
    if (callbackReturnInfo.error_type == 0)
    {
        SendDataReturnInfo ag15SendDataReturnInfo;
        int ret = V2X_SendData(callbackReturnInfo.sendDataInfo, &ag15SendDataReturnInfo);
        if (ret != -1)
            LogPrint(LOG_LEVEL_DEBUG, "Stack ", "V2X_SendData ok \n");
        else
            LogPrint(LOG_LEVEL_DEBUG, "Stack ", "V2X_SendData error \n");
    }
}

static Std_ReturnType FV_InitV2xComponents(void)
{
#define DEF_STACK_CFG "./ProtocolStack.ini"
    const char *l_pCfg;
    int l_n32Ret = 0;
    int ret = 0;

    LogInit();

    //软件版本号同步
    ret = SW_versionsync(module, V2X_SOFTVERSION);
    LogPrint(LOG_LEVEL_INFO, module, "software synchonise result %d ", ret);
    //Alloc Bsm send buffer
    FV_CallocBsmGlobalBuffer();

    //解析cJson文件
    memset(&g_tV2XOnlineCfg, 0x00, sizeof(g_tV2XOnlineCfg));
    if (FV_ParseV2XOnlineCfg(&g_tV2XOnlineCfg, ETC_BSMTX_CFG) < 0)
    {
        ERR("Parse the on line json error, use the default param\n");
    }

    //1.加载参数
    if (access(ETC_STACK_CFG, F_OK))
    {
        l_pCfg = DEF_STACK_CFG;
    }
    else
    {
        l_pCfg = ETC_STACK_CFG;
    }

    Stack_Init_t Init;
    memset(&Init, 0x00, sizeof(Init));
    strcpy(Init.FileName, l_pCfg);

    Init.p_WJV2_SetGetAIDFromFileCallback = SetGetAIDFromFileCallbackV2;
    Init.p_WJV2_UperEncOrDecMain = WJV2_UperEncOrDecMain;
    Init.p_WJV2_UperFromFileEncodeMain = WJV2_UperFromFileEncodeMain;

    Init.p_WJV3_SetGetAIDFromFileCallback = SetGetAIDFromFileCallbackV3;
    Init.p_WJV3_UperEncOrDecMain = WJV3_UperEncOrDecMain;
    Init.p_WJV3_UperFromFileEncodeMain = WJV3_UperFromFileEncodeMain;

    Init.p_WJV4_SetGetAIDFromFileCallback = SetGetAIDFromFileCallbackV4;
    Init.p_WJV4_UperEncOrDecMain = WJV4_UperEncOrDecMain;
    Init.p_WJV4_UperFromFileEncodeMain = WJV4_UperFromFileEncodeMain;

    Init.p_WJVN4_SetGetAIDFromFileCallback = SetGetAIDFromFileCallbackVN4;
    Init.p_WJVN4_UperEncOrDecMain = WJVN4_UperEncOrDecMain;
    Init.p_WJVN4_UperFromFileEncodeMain = WJVN4_UperFromFileEncodeMain;

    Init.p_Signfunc = SignSecuredMessage;
    Init.p_Verifyfunc = VerifySecuredMessage;
    Init.p_Sendfunc = SendingCallback;
    Init.p_Secfunc = seclayer_cert_status_callback;

    Init.WJ_LogInit = NULL; //RSU主程序无需调用此接口
    Init.WJ_V2XTxRxInit = V2X_TxRx_Init;
    // Init.WJ_SecureInit = SecureLayerInit;

    l_n32Ret = StackInit(&Init);
    if (l_n32Ret < 0)
    {
        INF("V2x stack init error\n");
    }
    else
    {
        INF("V2x stack init successfully\n");
    }
    
    return E_OK;
}

static void FV_ThreadsModuleDeInit(bool p_bDeInitWorker)
{
    static bool l_pRunOnce = false;
    if (!l_pRunOnce)
    {
        if (g_tPObjSet.m_pMainProcPObj->m_IsInited)
        {
            FV_StopAndDeleteTimerCycle(g_tPObjSet.m_BsmPObj);
            FV_StopAndDeleteTimerCycle(g_tPObjSet.m_ServicePObj);

            /* DeInit the attr of the child pthread. */
            THR_deinit_sched_properties(&g_tPObjSet.m_GdbusPObj->sched);
            THR_deinit_sched_properties(&g_tPObjSet.m_BsmPObj->sched);
            THR_deinit_sched_properties(&g_tPObjSet.m_V2xStackPObj->sched);
            THR_deinit_sched_properties(&g_tPObjSet.m_MonitorObj->sched);

            /* Destroy the workers of the threads. */
            if (p_bDeInitWorker)
            {
                FV_destroy_main_worker(g_tPObjSet.m_pMainProcPObj);
                THR_worker_thread_destroy(g_tPObjSet.m_GdbusPObj->m_Worker);
                THR_worker_thread_destroy(g_tPObjSet.m_BsmPObj->m_Worker);
                THR_worker_thread_destroy(g_tPObjSet.m_V2xStackPObj->m_Worker);
                THR_worker_thread_destroy(g_tPObjSet.m_ServicePObj->m_Worker);
                THR_worker_thread_destroy(g_tPObjSet.m_MonitorObj->m_Worker);
            }

            /* Deinit the linkedlist. */
            linkedlist_clear_exit(g_tPObjSet.m_pMainProcPObj->m_List, FV_OnDestroy);
            g_tPObjSet.m_pMainProcPObj->m_IsInited = false;
            /* Free the bsm sending buffer. */
            FV_FreeBsmGlobalBuffer();
#if EN_TEST_LOG
            FL_DestroyMsgLog();
#endif
            INF("%s:Recycle all the resources done!\n", __func__);
        }
        l_pRunOnce = true;
    }
}

/***********************************************************************
 * 函 数 名 称 ：FV_MonitorSupervisorThread
 * 功 能 描 述 ：系统监控线程，在线程异常时候可以拉起，拥有最高优先级
 * 输 入 参 数 ：p_pvArg: 线程入参，会传入相关句柄
 * 输 入 参 数 ：p_n32CurState: 线程当前的状态
 * 输 出 参 数 ：无
 * 返  回  值  :  E_EXIT_OK
 * 开 发 人 员 ：姚志强
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-09-03 V1.0   YaoZhiqiang    Create
***********************************************************************/
int FV_MonitorSupervisorThread(void *p_pvArg, int p_n32CurState)
{
    TModuleObjHdl l_ptObj = (TModuleObjHdl)p_pvArg;
    TMainProcObjHdl l_ptMainProcObj;

    if (!l_ptObj->m_IsInited)
    {
        THR_cond_wait(&l_ptObj->m_Worker->cond, &l_ptObj->m_Worker->mutex);
        l_ptMainProcObj = g_tPObjSet.m_pMainProcPObj;
        l_ptObj->m_IsInited = true;
        INF("%s Start\n", __func__);
    }

    if (l_ptObj->m_Worker->active)
    {
        while (l_ptMainProcObj->m_Worker->active)
        {
            THR_mutex_lock(&l_ptMainProcObj->m_Worker->mutex);
            static utils_timer start;
            DBG("___monitor___ interval: %lld\n", utils_timer_ms() - start);
            start = utils_timer_ms();
            FV_MonitorThreadsTimer();
            int l_n32Ret = E_EXIT_OK;
            sleep(1);
            l_n32Ret = THR_cond_timed_wait(&l_ptMainProcObj->m_Worker->cond, &l_ptMainProcObj->m_Worker->mutex, MONITOR_CYCLE_TIMER);
            switch (l_n32Ret)
            {
            case E_EXIT_OK:
                INF("THR_cond_timed_wait:THR_EXIT_OK!\n");
                l_ptObj->m_Worker->active = false;
                l_ptMainProcObj->m_Worker->active = false;
                break;
            case E_EXIT_EAGAIN:
                FV_RecreatThreadsAccordingAliveStatus();
                THR_mutex_unlock(&l_ptMainProcObj->m_Worker->mutex);
                continue;
            default:
                ERR("THR_cond_timed_wait error!\n");
                break;
            }
            THR_mutex_unlock(&l_ptMainProcObj->m_Worker->mutex);
        }
    }

    INF("%s quit\n", __func__);
    l_ptObj->m_IsInited = false;
    FV_ThreadsModuleDeInit(true);
    THR_thread_exit(NULL);
    return E_EXIT_OK;
}

/***********************************************************************
 * 函 数 名 称 ：FV_ThreadsModuleInit
 * 功 能 描 述 ：初始化BSMTx模块的所有线程
 * 输 入 参 数 ：无
 * 输 入 参 数 ：无
 * 输 出 参 数 ：无
 * 返  回  值  :  无
 * 开 发 人 员 ：姚志强
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/
void FV_ThreadsModuleInit(void)
{
    pthread_t BSMSendthreadid;

    MALLOC(l_ptMainProcObj, TMainProcObjHdl);
    MALLOC(l_ptBsmThrObj, TModuleObjHdl);
    MALLOC(l_ptServiceThrObj, TModuleObjHdl);
    MALLOC(l_ptV2xStackThrObj, TModuleObjHdl);
    MALLOC(l_ptGdbusThrObj, TModuleObjHdl);
    MALLOC(l_ptMonitorThrObj, TModuleObjHdl);

    BZERO(l_ptMainProcObj, TMainProcObjHdl);
    BZERO(l_ptBsmThrObj, TModuleObjHdl);
    BZERO(l_ptServiceThrObj, TModuleObjHdl);
    BZERO(l_ptV2xStackThrObj, TModuleObjHdl);
    BZERO(l_ptGdbusThrObj, TModuleObjHdl);
    BZERO(l_ptMonitorThrObj, TModuleObjHdl);

    g_tPObjSet.m_pMainProcPObj = l_ptMainProcObj;
    g_tPObjSet.m_BsmPObj = l_ptBsmThrObj;
    g_tPObjSet.m_ServicePObj = l_ptServiceThrObj;
    g_tPObjSet.m_V2xStackPObj = l_ptV2xStackThrObj;
    g_tPObjSet.m_GdbusPObj = l_ptGdbusThrObj;
    g_tPObjSet.m_MonitorObj = l_ptMonitorThrObj;

    if (!l_ptMainProcObj->m_IsInited)
    {
        /* Create the main thread obj to recycle the process resource. */
        l_ptMainProcObj->m_Worker = THR_worker_new();
        l_ptMainProcObj->m_Worker->active = true;

        /* Init the linked list of the objs. */
        l_ptMainProcObj->m_List = linkedlist_alloc();
        linkedlist_init(l_ptMainProcObj->m_List);
        linkedlist_append(l_ptMainProcObj->m_List, (DATA)l_ptMainProcObj);

        //初始化dbus模块
        FV_init_v2x_dbus_communication();
        l_ptMainProcObj->m_IsInited = true;

    }

    linkedlist_append(l_ptMainProcObj->m_List, (DATA)l_ptBsmThrObj);
    linkedlist_append(l_ptMainProcObj->m_List, (DATA)l_ptServiceThrObj);
    linkedlist_append(l_ptMainProcObj->m_List, (DATA)l_ptV2xStackThrObj);
    linkedlist_append(l_ptMainProcObj->m_List, (DATA)l_ptGdbusThrObj);
    linkedlist_append(l_ptMainProcObj->m_List, (DATA)l_ptMonitorThrObj);
    l_ptBsmThrObj->m_Worker = THR_worker_new();
    l_ptServiceThrObj->m_Worker = THR_worker_new();
    l_ptV2xStackThrObj->m_Worker = THR_worker_new();
    l_ptGdbusThrObj->m_Worker = THR_worker_new();
    l_ptMonitorThrObj->m_Worker = THR_worker_new();

    //设置各个线程各自回收资源
    l_ptBsmThrObj->m_Worker->joinable = false;
    l_ptServiceThrObj->m_Worker->joinable = false;
    l_ptV2xStackThrObj->m_Worker->joinable = false;
    l_ptGdbusThrObj->m_Worker->joinable = false;
    l_ptMonitorThrObj->m_Worker->joinable = false;

    //创建各个线程模型运行的时钟
    // FV_CreateOrRecreateTimer(false, l_ptBsmThrObj, FV_BsmProcessMsgTimerCb);
    FV_CreateOrRecreateTimer(false, l_ptServiceThrObj, FV_ServiceCycleCheckTimerCb);

    //主线程属性初始化
    THR_dynamic_sched_t sched;
    sched.policy = THR_SCHE_RR;
    sched.param.sched_priority = DEF_HIGHER_SCHED_PRORITY;
    THR_set_main_pthread_param(&sched);

    //子线程属性初始化
    l_ptGdbusThrObj->sched.policy = THR_SCHE_RR;
    l_ptGdbusThrObj->sched.param.sched_priority = DEF_HIGHER_SCHED_PRORITY;
    l_ptBsmThrObj->sched.policy = THR_SCHE_RR;
    l_ptBsmThrObj->sched.param.sched_priority = DEF_HIGHER_SCHED_PRORITY;
    l_ptV2xStackThrObj->sched.policy = THR_SCHE_RR;
    l_ptV2xStackThrObj->sched.param.sched_priority = DEF_HIGHER_SCHED_PRORITY;
    l_ptMonitorThrObj->sched.policy = THR_SCHE_RR;
    l_ptMonitorThrObj->sched.param.sched_priority = DEF_HIGHEST_SCHED_PRORITY;

    //设置线程模型的调度策略为高优先级, 线程属性PTHREAD_CREATE_DETACHED, 线程资源自回收
    THR_init_sched_properties(&l_ptGdbusThrObj->sched, true);
    THR_init_sched_properties(&l_ptBsmThrObj->sched, true);
    THR_init_sched_properties(&l_ptV2xStackThrObj->sched, true);
    THR_init_sched_properties(&l_ptMonitorThrObj->sched, true);

    //创建线程模型
    pthread_attr_t l_tpthreadattr = {0};
    struct sched_param l_pthreadparam = {0};
    l_pthreadparam.sched_priority = 92;
    pthread_attr_init(&l_tpthreadattr);
    pthread_attr_setschedpolicy(&l_tpthreadattr, SCHED_RR);
    pthread_attr_setschedparam(&l_tpthreadattr, &l_pthreadparam);
    pthread_attr_setinheritsched(&l_tpthreadattr, PTHREAD_EXPLICIT_SCHED);

    pthread_create(&BSMSendthreadid, &l_tpthreadattr, (void*)FV_BsmProcessMsgTimerCb,NULL);


    THR_worker_thread_create(l_ptGdbusThrObj->m_Worker, FV_GdbusProcessMessageThread, &l_ptGdbusThrObj->sched, l_ptGdbusThrObj);
    OSA_millisecondsleep(THREAD_INTERVAL);
    THR_worker_thread_create(l_ptBsmThrObj->m_Worker, FV_BsmMessageProcessThread, &l_ptBsmThrObj->sched, l_ptBsmThrObj);
    OSA_millisecondsleep(THREAD_INTERVAL);
    THR_worker_thread_create(l_ptV2xStackThrObj->m_Worker, FV_V2xStackHandleMessageThread, &l_ptV2xStackThrObj->sched, l_ptV2xStackThrObj);
    OSA_millisecondsleep(THREAD_INTERVAL);
    THR_worker_thread_create(l_ptMonitorThrObj->m_Worker, FV_MonitorSupervisorThread, &l_ptMonitorThrObj->sched, l_ptMonitorThrObj);
    OSA_millisecondsleep(THREAD_INTERVAL);
    THR_worker_thread_signal(l_ptGdbusThrObj->m_Worker);
    OSA_millisecondsleep(COMMON_INTERVAL);
    // FV_StartTimerCycle(l_ptBsmThrObj, 0, DEF_BSM_CYCLE);     /* Start bsm timer cycle 100ms. */
    FV_StartTimerCycle(l_ptServiceThrObj, DEF_SVC_CYCLE, 0); /* Start service module timer cycle 1s. */
    OSA_millisecondsleep(COMMON_INTERVAL);
    THR_worker_thread_signal(l_ptBsmThrObj->m_Worker);
    OSA_millisecondsleep(COMMON_INTERVAL);
    THR_worker_thread_signal(l_ptV2xStackThrObj->m_Worker);
    OSA_millisecondsleep(COMMON_INTERVAL);
    THR_worker_thread_signal(l_ptMonitorThrObj->m_Worker);

    while (l_ptMainProcObj->m_Worker->active)
    {
        OSA_millisecondsleep(COMMON_INTERVAL);
    }
    FV_deinit_v2x_dbus_communication();
    FV_ThreadsModuleDeInit(true);
}

static void FV_sigstop(int sig_num)
{
    INF("Receive stop signal(%d).\n", sig_num);
    FV_MainProcThreadsErrorExit(g_tPObjSet.m_pMainProcPObj);
    /* Give some time to deinit process, then exit process whatever. */
    OSA_millisecondsleep(500U);
    /* Recyle the resource and join the threads. */
    FV_ThreadsModuleDeInit(false);
    exit(EXIT_FAILURE);
}

static void FV_InstallSignalHandler(void)
{
    struct sigaction l_SigAction;

    l_SigAction.sa_handler = FV_sigstop;
    sigemptyset(&l_SigAction.sa_mask);
    l_SigAction.sa_flags = 0;

    sigaction(SIGINT, &l_SigAction, NULL);
    sigaction(SIGHUP, &l_SigAction, NULL);
    sigaction(SIGQUIT, &l_SigAction, NULL);
    sigaction(SIGTERM, &l_SigAction, NULL);
}

int main(int argc, const char *argv[])
{

    FV_InstallSignalHandler();
    FV_InitV2xComponents();

    /* To wait for v2x stack ready to run. */
    sleep(2);

    bzero(&g_tDbusVehDataFrame, sizeof(g_tDbusVehDataFrame));
    FV_ThreadsModuleInit();

    while (1)
    {
        sleep(10);
    }

    exit(EXIT_SUCCESS);
}
