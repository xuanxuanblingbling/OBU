/*******************************************************************************
 * 文 件 名 称 ： Common.h
 * 功 能 描 述 ： 各线程之间通用的结构体模型，函数接口
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

/* Utils headers. */
#include "LinuxCommonHeader.h"
#include "V2xBasicTypes.h"
#include "Timer.h"
#include "Worker.h"
#include "LinkedList.h"
#include "Msgque.h"

/* V2x Stack headers. */
#include "wj_log.h"
//协议栈Stack_Lib头文件
#include "wj_inc_com.h"
//协议栈接入层头文件
#include "V2XInterface.h"
//协议栈安全层头文件
#include "SecLayer.h"

/* App modules headers. */
#include "BSMTx.h"
#include "Service.h"
#include "v2x.h"
#include "v2x_dbus.h"
#include "OnlineCfg.h"
#include "get_num.h"

V2X_BEGIN_HEADER

#define EN_TEST_LOG 0U

#if EN_TEST_LOG
#include "NewFourSpanLogIf.h"
#endif

#define EN_SECURITY_INIT 0U

#define DEF_BSM_CYCLE 100U //毫秒为单位
#define DEF_SVC_CYCLE 3U   //秒为单位

#define EN_DBG_PRINT 0U

#define ETC_STACK_CFG "/mnt/APP/Config/obu/v2x/ProtocolStack.ini"
#define ETC_BSMTX_CFG "/mnt/APP/Config/obu/v2x/V2XServerCfg.json"
#define V2X_AG15_IF_IP "192.168.100.1"

#define PAKAGE_ALIGN __attribute__((packed))
typedef struct
{
   OSA_TimerHndl m_TimerHndl;
   union sigval m_UnValue;
} TObjTimerHndl_t;

typedef struct
{
   bool m_IsInited;
   THR_worker m_Worker;
   linkedlist m_List;
} TMainProcObjHdl_t, *TMainProcObjHdl;

typedef struct obj
{
   bool m_IsInited;
   THR_worker m_Worker;
   TObjTimerHndl_t m_ObjTimerHndl;
   THR_sched_t sched;
} TModuleObjHdl_t, *TModuleObjHdl;

typedef struct
{
   TMainProcObjHdl m_pMainProcPObj;
   TModuleObjHdl m_BsmPObj;
   TModuleObjHdl m_ServicePObj;
   TModuleObjHdl m_V2xStackPObj;
   TModuleObjHdl m_GdbusPObj;
   TModuleObjHdl m_MonitorObj;
} TPObjSetHndl_t;

#define GUIDESTART_SUCCESS 1
#define GUIDESTART_FAIL 0
#define BOOTDEVICETYEP_RSU 1
#define BOOTDEVICETYEP_OBU 2
#define BOOTDEVICETYEP_UNKNOWN 0

/**
 * @brief 全局线程句柄集
 * @note 用于所有模块通信的全局变量声明.
 */
extern TPObjSetHndl_t g_tPObjSet;

/**
 * @brief 全局在线配置变量
 * @note 用于所有模块通信的全局在线配置声明.
*/
extern TV2XOnLineConfigType g_tV2XOnlineCfg;

/**
 * @brief 全局线程函数，用于外部引用
 * @note 用于所有模块通信的全局函数声明.
 */
extern int FV_BsmMessageProcessThread(void *, int);
extern int FV_V2xStackHandleMessageThread(void *, int);
extern int FV_GdbusProcessMessageThread(void *, int);

/**
 * @brief BSM全局变量定义
 * @note 用于BSMTx模块通信的全局变量声明.
 */
extern TMsgVehDataFrame_t g_tDbusVehDataFrame;
extern char g_aBsmDynamicId[8]; //BSM 消息ID

/**
 * @brief BSM全局函数，用于外部引用
 * @note BSMTx模块通信的全局函数声明.
 */
extern uint8_t FV_CheckSum(void *p_pvData, size_t p_u32Len);
//extern Std_ReturnType FV_CreateBsmMinmumPackage(WJV4_STRU_MessageFrame *pmsg_frame, TVehData_t p_ptVehData);
extern Std_ReturnType FV_CreateBsmMinmumPackage(WJVN4_STRU_MessageFrame *pmsg_frame, TVehData_t p_ptVehData);
extern Std_ReturnType FV_CreateV2BsmMinmumPackage(WJV2_STRU_MessageFrame *pmsg_frame, TVehData_t p_ptVehData);
extern Std_ReturnType FV_CreateVIRMinmumPackage(WJV2_STRU_MessageFrame *pmsg_frame, TVehData_t p_ptVehData);
extern void FV_BsmProcessMsgTimerCb(union sigval value);
extern void FV_ChangeBsmTimerCycleDynamic(TModuleObjHdl p_ptObj);
extern void FV_V2xStackSendingCallback(SendCallbackReturnInfo returnInfo);
extern void FV_CallocBsmGlobalBuffer(void);
extern void FV_FreeBsmGlobalBuffer(void);

/**
 * @brief SERVICE全局变量定义
 * @note 用于SERVICE模块通信的全局变量声明.
 */
extern TV2xSrvState_t g_tDbusV2xSrvState;
extern TSrvFaultPush_t g_tDbusSrvFaultPush;
extern TSrvConfigRs_t g_tDbusConfigRs;
extern TSrvConfigRsCb_t g_tDbusConfigRsCb;
extern RoadsideCoordination_t g_tRoadsideCoordination;

/**
 * @brief SERVICE全局函数，用于外部引用
 * @note SERVICE模块通信的全局函数声明.
 */
extern void FV_ServiceCycleCheckTimerCb(union sigval value);
extern int FV_ServiceHandleMessageThread(void *p_pvArg, int p_n32CurState);
extern void FV_OnlineConfigRs(void);

/**
 * @brief V2X_RX全局函数，用于外部引用
 * @note V2X_RX模块通信的全局函数声明.
 */
extern int FV_V2xStackHandleMessageThread(void *p_pvArg, int p_n32CurState);

/**
 * @brief BSMTx在线配置全局函数，用于外部引用
 * @note BSMTx模块通信的全局函数声明.
*/
extern int FV_ParseV2XOnlineCfg(TV2XOnLineConfigType *p_pOnlineCfg, const char *p_pPathFile);
extern uint8_t FV_IsSecurityCertUpdate(void);
extern void FV_ResetSecurityCertUpdateFlag(void);

V2X_END_HEADER

#endif
