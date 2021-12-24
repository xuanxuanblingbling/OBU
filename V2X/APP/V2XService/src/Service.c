/*******************************************************************************
 * 文 件 名 称 ： Service.c
 * 功 能 描 述 ： 系统状态监控模块
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#include "Common.h"

#define MODULE_NAME "BSMTx"
#include "Debug.h"

//全局线程句柄集合
extern TPObjSetHndl_t g_tPObjSet;

//用于外部引用全局变量
TV2xSrvState_t g_tDbusV2xSrvState = INIT_V2X_SRV_STATE();
TSrvFaultPush_t g_tDbusSrvFaultPush = INIT_SRV_FAULT_PUSH();
TSrvConfigRs_t g_tDbusConfigRs = INIT_SRV_CFG_RS();
TSrvConfigRsCb_t g_tDbusConfigRsCb = INIT_SRV_CFG_RS_CB();
RoadsideCoordination_t g_tRoadsideCoordination;

//用于内部引用的全局变量
//static TRuntimeSupervisonMsgQue g_tRuntimeSupervisonMsgQue;

enum
{
    V2X_IS_INACTIVE = 0,   /**< V2X communication is disabled. */
    V2X_IS_ACTIVE,         /**< V2X communication is enabled. Transmit and
                              receive are possible. */
    V2X_TX_IS_SUSPENDED,   /**< Small loss of timing precision occurred.
                                                            Transmit is no longer supported. */
    V2X_RX_IS_SUSPENDED,   /**< Radio can no longer receive any messages. */
    V2X_TXRX_IS_SUSPENDED, /**< Radio can no longer transmit or receive, for
                              some reason. @newpage */
};

/***********************************************************************
 * 函 数 名 称 ：FV_ServiceCycleCheckTimerCb
 * 功 能 描 述 ：系统服务管理的posix时钟回调函数，3s为周期调用
 * 输 入 参 数 ：value：信号结构体
 * 输 入 参 数 ：无
 * 输 出 参 数 ：无
 * 返  回  值  :  无
 * 开 发 人 员 ：姚志强
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/
void FV_ServiceCycleCheckTimerCb(union sigval value)
{
    static utils_timer start;
    TModuleObjHdl l_ptObj = (TModuleObjHdl)value.sival_ptr;
    int l_n32ThrBsmKillerErr, l_n32ThrV2xKillerErr, l_n32ThrDbusKillerErr;

    DBG("___service___ interval: %lld\n", utils_timer_ms() - start);
    start = utils_timer_ms();

    THR_mutex_lock(&l_ptObj->m_Worker->mutex);
    //memset(&g_tRuntimeSupervisonMsgQue, 0, sizeof(TRuntimeSupervisonMsgQue));
    //每次进来要清空复位状态为0xFF
    memset(&g_tDbusV2xSrvState, 0xFF, sizeof(g_tDbusV2xSrvState));
    l_n32ThrBsmKillerErr = pthread_kill(g_tPObjSet.m_BsmPObj->m_Worker->tid, 0);
    l_n32ThrV2xKillerErr = pthread_kill(g_tPObjSet.m_V2xStackPObj->m_Worker->tid, 0);
    l_n32ThrDbusKillerErr = pthread_kill(g_tPObjSet.m_GdbusPObj->m_Worker->tid, 0);

    if (ESRCH == l_n32ThrBsmKillerErr)
    {
        g_tDbusV2xSrvState.m_BSMTxState = THR_SUSPEND;
    }
    else if (EINVAL == l_n32ThrBsmKillerErr)
    {
        ERR("Unlawful transmission of signals\n");
    }
    else
    {
        g_tDbusV2xSrvState.m_BSMTxState = THR_RUNNING;
    }

    if (ESRCH == l_n32ThrV2xKillerErr)
    {
        g_tDbusV2xSrvState.m_V2XStackRxState = THR_SUSPEND;
    }
    else if (EINVAL == l_n32ThrV2xKillerErr)
    {
        ERR("Unlawful transmission of signals\n");
    }
    else
    {
        g_tDbusV2xSrvState.m_V2XStackRxState = THR_RUNNING;
    }

    if (ESRCH == l_n32ThrDbusKillerErr)
    {
        g_tDbusV2xSrvState.m_DbusState = THR_SUSPEND;
    }
    else if (EINVAL == l_n32ThrDbusKillerErr)
    {
        ERR("Unlawful transmission of signals\n");
    }
    else
    {
        g_tDbusV2xSrvState.m_DbusState = THR_RUNNING;
    }

    //GetV2xRunStatus((TRuntimeSupervisonMsgQue *)&g_tRuntimeSupervisonMsgQue);
    // if (g_tRuntimeSupervisonMsgQue.m_tModuleRuntimeStatusList.m_enumModuleType == MODULE_V2XSTACK)
    // {
    //     int8_t l_n8V2xStatus = g_tRuntimeSupervisonMsgQue.m_tModuleRuntimeStatusList.RuntimeStatus.m_tV2XStackRuntimeStatus.m_n8V2XStatus;
    //     uint8_t l_u8SafetyCertStatus = g_tRuntimeSupervisonMsgQue.m_tModuleRuntimeStatusList.RuntimeStatus.m_tV2XStackRuntimeStatus.m_u8SafetyCertStatus;
    //     switch (l_n8V2xStatus)
    //     {
    //     case V2X_IS_INACTIVE:
    //         g_tDbusV2xSrvState.m_V2XStackTxState = STATE_WAITING;
    //         g_tDbusV2xSrvState.m_V2XStackRxState = STATE_WAITING;
    //         break;
    //     case V2X_IS_ACTIVE:
    //         g_tDbusV2xSrvState.m_V2XStackTxState = STATE_RUNNING;
    //         g_tDbusV2xSrvState.m_V2XStackRxState = STATE_RUNNING;
    //         break;
    //     case V2X_TX_IS_SUSPENDED:
    //         g_tDbusV2xSrvState.m_V2XStackTxState = STATE_SUSPENDED;
    //         break;
    //     case V2X_RX_IS_SUSPENDED:
    //         g_tDbusV2xSrvState.m_V2XStackRxState = STATE_SUSPENDED;
    //         break;
    //     case V2X_TXRX_IS_SUSPENDED:
    //         g_tDbusV2xSrvState.m_V2XStackTxState = STATE_SUSPENDED;
    //         g_tDbusV2xSrvState.m_V2XStackRxState = STATE_SUSPENDED;
    //         break;
    //     default:
    //         break;
    //     }
    //     if (!l_u8SafetyCertStatus)
    //     {
    //         g_tDbusV2xSrvState.m_CertMState = STATE_RUNNING;
    //     }
    //     else
    //     {
    //         g_tDbusV2xSrvState.m_CertMState = STATE_SUSPENDED;
    //     }
    // }
    FV_emit_v2x_srv_state();
    THR_mutex_unlock(&l_ptObj->m_Worker->mutex);
}

/***********************************************************************
 * 函 数 名 称 ：FV_OnlineConfigRs
 * 功 能 描 述 ：在线配置响应函数
 * 输 入 参 数 ：无
 * 输 入 参 数 ：无
 * 输 出 参 数 ：无
 * 返  回  值  :  无
 * 开 发 人 员 ：姚志强
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/

void FV_OnlineConfigRs(void)
{
    if (V2X_STACK_CFG_CHG == g_tDbusConfigRs.m_V2xCfgUpdateNotify)
    {
        //重新加载ProtocolStack.ini文件
        if (WJ_InitParamDataInterface(&ProtocolStackParamConfig, (char *)ETC_STACK_CFG) < 0)
        {
            ERR("Config the V2X stack error, use the default param\n");
            g_tDbusConfigRsCb.m_OnlinecfgRs = CONFIG_RS_FAILURE;
        }
        else
        {
            g_tDbusConfigRsCb.m_OnlinecfgRs = CONFIG_RS_SUCCESS;
        }
    }

    if (V2X_SERVICE_CFG_CHG == g_tDbusConfigRs.m_V2xCfgUpdateNotify)
    {
        //重新加载cJson文件
        memset(&g_tV2XOnlineCfg, 0x00, sizeof(g_tV2XOnlineCfg));
        if (FV_ParseV2XOnlineCfg(&g_tV2XOnlineCfg, ETC_BSMTX_CFG) < 0)
        {
            ERR("Parse the on line json error, use the default param\n");
            g_tDbusConfigRsCb.m_OnlinecfgRs = CONFIG_RS_FAILURE;
        }
        else
        {
            g_tDbusConfigRsCb.m_OnlinecfgRs = CONFIG_RS_SUCCESS;
        }
    }

    /* 连续发送5帧 , 100ms周期 */
    for (int l_n32Cnt = 0; l_n32Cnt < 5; ++l_n32Cnt)
    {
        FV_emit_v2x_srv_cfg_rs();
        OSA_millisecondsleep(100);
    }

    /* 重置状态为默认值 */
    memset(&g_tDbusConfigRs, 0xFF, sizeof(g_tDbusConfigRs));
    memset(&g_tDbusConfigRsCb, 0xFF, sizeof(g_tDbusConfigRsCb));
}