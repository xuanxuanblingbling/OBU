/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       Cfg.c
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : Cfg.c
*   Author:         : wensheng.zhang       2020
********************************************************************************
*   Limitations:      None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version       Date       Initials        CR#        Descriptions
*   -------   ----------  --------------    ------    -------------------
*   01.00.00  07/07/2020  wensheng.zhang      N/A         Original
********************************************************************************
*END_FILE_HDR*/
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "wj_log.h"
#include "DiagM.h"
#include "CfgM.h"
//#include "MsgRcvSd.h"
#include "StateM.h"
//#include "PowerM.h"
#include "WebServerM.h"
#include "MsgMonitor.h"
#include "Cfg.h"

/* 参数配置 */
sem_t gParameter_Cfg_Web_Rq;
sem_t gParameter_Cfg_Sys_Resp;
sem_t gParameter_Cfg_Web_Resp;


/* 故障诊断 */
sem_t gDiag_Parameter_Rcv;

/* 状态监控 */
sem_t gState_RCV;

/* 电源管理 */
sem_t gPower_Down_Rq;

/* 消息监控 */
sem_t gMsgMonitor_Rcv;


/* 全局变量：各线程数据交互 */
static CfgM_Json					  gCfg_Json;
static DiagM_Json					  gDiagCfg_Json;
static StateM_Json		    		  gStateM_Json;
//static PowerM_PwrRq         		  gMcuPwrDwnRq;
static CfgM_Resp            		  gCfgMResp;
static MsgMonitor_Json     			  gMsgMonitorJson;
static int                            gVdsSpeed;
static int							  gMsgMonitorFileState = 0;

pthread_mutex_t gDiagCfg_Json_Mutex;
pthread_mutex_t gNetCfg_Json_Mutex;
pthread_mutex_t gStateCfg_Json_Mutex;
pthread_mutex_t gMcuPwrDwn_Mutex;
pthread_mutex_t gCfgMResp_Mutex;
pthread_mutex_t gMsgMonitorJson_Mutex;
pthread_mutex_t gMsgMonitorFileState_Mutex;
pthread_mutex_t gDiagCfg_SpeedInt_Mutex;

pthread_mutex_t gMsgMonitorStartEnd_Mutex;
pthread_mutex_t gDiagCfg_WriteJF_Mutex;
pthread_mutex_t gStateCfg_WriteJF_Mutex;
pthread_mutex_t gMsgMonitor_WriteJF_Mutex;

int SemInit()
{
	int ret = 0;

	ret = sem_init(&gParameter_Cfg_Web_Rq,0,0);
	ret |= sem_init(&gParameter_Cfg_Web_Resp,0,0);
	ret |= sem_init(&gParameter_Cfg_Sys_Resp,0,0);
	ret |= sem_init(&gDiag_Parameter_Rcv,0,0);
	ret |= sem_init(&gPower_Down_Rq,0,0);
	ret |= sem_init(&gState_RCV,0,0);

	if(ret != 0)
		return 1;
	else
		return 0;
}

int MutexInit()
{
	int ret;
	ret = pthread_mutex_init(&gDiagCfg_Json_Mutex,NULL);
	ret |= pthread_mutex_init(&gNetCfg_Json_Mutex,NULL);
	ret |= pthread_mutex_init(&gStateCfg_Json_Mutex,NULL);
	ret |= pthread_mutex_init(&gMcuPwrDwn_Mutex,NULL);
	ret |= pthread_mutex_init(&gCfgMResp_Mutex,NULL);
	ret |= pthread_mutex_init(&gMsgMonitorJson_Mutex,NULL);
	ret |= pthread_mutex_init(&gMsgMonitorFileState_Mutex,NULL);
	ret |= pthread_mutex_init(&gDiagCfg_SpeedInt_Mutex,NULL);
	ret |= pthread_mutex_init(&gDiagCfg_WriteJF_Mutex,NULL);
	ret |= pthread_mutex_init(&gStateCfg_WriteJF_Mutex,NULL);
	ret |= pthread_mutex_init(&gMsgMonitor_WriteJF_Mutex,NULL);


	if(0 != ret)
		return -1;
	else
		return 0;
}
t_MsgMonitorFileFlag Get_MsgMonitor_File_State()
{
	return gMsgMonitorFileState;
}
void Set_MsgMonitor_File_State(t_MsgMonitorFileFlag Flag)
{
	pthread_mutex_lock(&gMsgMonitorFileState_Mutex);
	gMsgMonitorFileState = Flag;
	pthread_mutex_unlock(&gMsgMonitorFileState_Mutex);
}

void Get_Json_Struct(JSON_StructType StructType, void * Des)
{
	switch(StructType)
	{
		case CFGM_JSON_STRUCT:
			pthread_mutex_lock(&gNetCfg_Json_Mutex);
			memcpy((CfgM_Json *)Des, &gCfg_Json, sizeof(CfgM_Json));
			pthread_mutex_unlock(&gNetCfg_Json_Mutex);
			break;
		case DIAGCFG_JSON_STRUCT:
			pthread_mutex_lock(&gDiagCfg_Json_Mutex);
			memcpy((DiagM_Json *)Des, &gDiagCfg_Json, sizeof(DiagM_Json));
			gDiagCfg_Json.Keyid = 0;
			pthread_mutex_unlock(&gDiagCfg_Json_Mutex);
			break;
		case STATECFG_JSON_STRUCT:
			pthread_mutex_lock(&gStateCfg_Json_Mutex);
			memcpy(Des, &gStateM_Json, sizeof(StateM_Json));
			gStateM_Json.Keyid = 0;
			pthread_mutex_unlock(&gStateCfg_Json_Mutex);
			break;
		case MCU_PWRDWN_RQ_STRUCT:
			pthread_mutex_lock(&gMcuPwrDwn_Mutex);
			//memcpy(Des, &gMcuPwrDwnRq, sizeof(PowerM_PwrRq));
			pthread_mutex_unlock(&gMcuPwrDwn_Mutex);
			break;
		case CFGM_RESP_STRUCT:
			pthread_mutex_lock(&gCfgMResp_Mutex);
			memcpy(Des, &gCfgMResp, sizeof(CfgM_Resp));
			gCfgMResp.RespId = 0;
			pthread_mutex_unlock(&gCfgMResp_Mutex);
			break;
		case MSGMONITOR_JSON_STRUCT:
			pthread_mutex_lock(&gMsgMonitorJson_Mutex);
			memcpy(Des, &gMsgMonitorJson, sizeof(MsgMonitor_Json));
			pthread_mutex_unlock(&gMsgMonitorJson_Mutex);
			break;
		case DIAGCFG_SPEED_INT:
			pthread_mutex_lock(&gDiagCfg_SpeedInt_Mutex);
			memcpy(Des, &gVdsSpeed, sizeof(int));
			pthread_mutex_unlock(&gDiagCfg_SpeedInt_Mutex);
			break;
		default :
			LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "Get Struct Type error");
			break;
	}
	
	LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "Get Struct type %d ID-%d", StructType, gCfg_Json.CfgFileId);
}
void Set_Json_Struct(JSON_StructType StructType, void * Src)
{
	switch(StructType)
	{
		case CFGM_JSON_STRUCT:
			pthread_mutex_lock(&gNetCfg_Json_Mutex);
			memcpy(&gCfg_Json, (CfgM_Json *)Src, sizeof(CfgM_Json));
			pthread_mutex_unlock(&gNetCfg_Json_Mutex);
			break;
		case DIAGCFG_JSON_STRUCT:
			pthread_mutex_lock(&gDiagCfg_Json_Mutex);
			memcpy(&gDiagCfg_Json, (DiagM_Json *)Src,sizeof(DiagM_Json));
			pthread_mutex_unlock(&gDiagCfg_Json_Mutex);
			break;
		case STATECFG_JSON_STRUCT:
			pthread_mutex_lock(&gStateCfg_Json_Mutex);
			memcpy(&gStateM_Json, (StateM_Json *)Src, sizeof(StateM_Json));
			pthread_mutex_unlock(&gStateCfg_Json_Mutex);
			break;
		case MCU_PWRDWN_RQ_STRUCT:
			pthread_mutex_lock(&gMcuPwrDwn_Mutex);
			//memcpy(&gMcuPwrDwnRq, (int *)Src, sizeof(PowerM_PwrRq));
			pthread_mutex_unlock(&gMcuPwrDwn_Mutex);
			break;
		case CFGM_RESP_STRUCT:
			pthread_mutex_lock(&gCfgMResp_Mutex);
			memcpy(&gCfgMResp, (CfgM_Resp *)Src, sizeof(CfgM_Resp));
			pthread_mutex_unlock(&gCfgMResp_Mutex);
			break;
		case MSGMONITOR_JSON_STRUCT:
			pthread_mutex_lock(&gMsgMonitorJson_Mutex);
			memcpy(&gMsgMonitorJson, (MsgMonitor_Json *)Src, sizeof(MsgMonitor_Json));
			pthread_mutex_unlock(&gMsgMonitorJson_Mutex);
			break;
		case DIAGCFG_SPEED_INT:
			pthread_mutex_lock(&gDiagCfg_SpeedInt_Mutex);
			memcpy(&gVdsSpeed,  (int *)Src, sizeof(int));
			pthread_mutex_unlock(&gDiagCfg_SpeedInt_Mutex);
			break;
		default :
			LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "Set Struct Type error");
			break;
	}
}

void GetSignal_B(SignalType Signal)
{
	switch(Signal)
	{
		case PARAMETER_CFG_WEB_RQ:
			sem_wait(&gParameter_Cfg_Web_Rq);
			sem_init(&gParameter_Cfg_Web_Rq,0,0);
			break;
		case PARAMETER_CFG_SYS_RESP:
			sem_wait(&gParameter_Cfg_Sys_Resp);
			sem_init(&gParameter_Cfg_Sys_Resp,0,0);
			break;
		case PARAMETER_CFG_WEB_RESP:
			sem_wait(&gParameter_Cfg_Web_Resp);
			sem_init(&gParameter_Cfg_Web_Resp,0,0);
			break;
		case DIAG_PARAMETER_RCV_NOTIFY:
			sem_wait(&gDiag_Parameter_Rcv);
			sem_init(&gDiag_Parameter_Rcv,0,0);
			break;
		case STATE_RCV_NOTIFY:
			sem_wait(&gState_RCV);
			sem_init(&gState_RCV,0,0);
			break;
		case POWER_DOWN_RQ:
			sem_wait(&gPower_Down_Rq);
			sem_init(&gPower_Down_Rq,0,0);
			break;
		case MSG_MONITOR_RCV:
			sem_wait(&gMsgMonitor_Rcv);
			sem_init(&gMsgMonitor_Rcv,0,0);
			break;
		case MSG_MONITOR_RUN:
			pthread_mutex_lock(&gMsgMonitorStartEnd_Mutex);
			pthread_mutex_unlock(&gMsgMonitorStartEnd_Mutex);
			break;	
		case DIAG_JSON_FILE:
			pthread_mutex_lock(&gDiagCfg_WriteJF_Mutex);
			break;			
		case STATE_JSON_FILE:
			pthread_mutex_lock(&gStateCfg_WriteJF_Mutex);
			break;
		case MSG_JSON_FILE:
			pthread_mutex_lock(&gMsgMonitor_WriteJF_Mutex);
			break;
		default :
			LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "Get Struct Type error");
			break;
	}
}
int GetSignal_NB(SignalType Signal, int gtimeSetMs)
{
	int ret;

	struct timespec l_timeSet;
	struct timeval l_timeCurrent;

	gettimeofday(&l_timeCurrent,NULL);

	l_timeSet.tv_sec = l_timeCurrent.tv_sec;
	l_timeSet.tv_nsec = l_timeCurrent.tv_usec*1000 + gtimeSetMs * 1000 * 1000;
	l_timeSet.tv_sec += l_timeSet.tv_nsec/(1000 * 1000 *1000);
	l_timeSet.tv_nsec %= (1000 * 1000 *1000);

	switch(Signal)
	{
		case PARAMETER_CFG_WEB_RESP:
			ret = sem_timedwait(&gParameter_Cfg_Web_Resp, &l_timeSet);
			break;
		case PARAMETER_CFG_SYS_RESP:
			ret = sem_timedwait(&gParameter_Cfg_Sys_Resp, &l_timeSet);
			break;
		default :
			LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "Get Struct Type error");
			break;
	}
	return ret;
}

void SetSignal_B(SignalType Signal)
{
	switch(Signal)
	{
		case PARAMETER_CFG_WEB_RQ:
			sem_post(&gParameter_Cfg_Web_Rq);
			break;
		case PARAMETER_CFG_SYS_RESP:
			sem_post(&gParameter_Cfg_Sys_Resp);
			break;
		case PARAMETER_CFG_WEB_RESP:
			sem_post(&gParameter_Cfg_Web_Resp);
			break;
		case DIAG_PARAMETER_RCV_NOTIFY:
			sem_post(&gDiag_Parameter_Rcv);
			break;
		case STATE_RCV_NOTIFY:
			sem_post(&gState_RCV);
			break;
		case POWER_DOWN_RQ:
			sem_post(&gPower_Down_Rq);
			break;
		case MSG_MONITOR_RCV:
			sem_post(&gMsgMonitor_Rcv);
			break;
		case MSG_MONITOR_START:
			pthread_mutex_unlock(&gMsgMonitorStartEnd_Mutex);
			break;
		case MSG_MONITOR_END:
			pthread_mutex_unlock(&gMsgMonitorStartEnd_Mutex);
			pthread_mutex_lock(&gMsgMonitorStartEnd_Mutex);
			break;
		case DIAG_JSON_FILE:
			pthread_mutex_unlock(&gDiagCfg_WriteJF_Mutex);
			break;			
		case STATE_JSON_FILE:
			pthread_mutex_unlock(&gStateCfg_WriteJF_Mutex);
			break;
		case MSG_JSON_FILE:
			pthread_mutex_unlock(&gMsgMonitor_WriteJF_Mutex);
			break;
		default :
			LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "Set Struct Type error");
			break;
	}
}




