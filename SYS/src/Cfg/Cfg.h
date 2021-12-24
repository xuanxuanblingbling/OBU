/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       Cfg.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : Cfg.h
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

#ifndef _MAIN_H
#define _MAIN_H

#include <semaphore.h>
#include <signal.h>
#include "DiagM.h"
#include "CfgM.h"
#include "MsgMonitor.h"

typedef enum  _Notify_FlagType
{
	VALID,
	INVALID,
	INIT,
} Notify_FlagType;

typedef enum  _JSON_StructType
{
	CFGM_JSON_STRUCT,
	DIAGCFG_JSON_STRUCT,
	STATECFG_JSON_STRUCT,
	MCU_PWRDWN_RQ_STRUCT,
	CFGM_RESP_STRUCT,
	MSGMONITOR_JSON_STRUCT,
	DIAGCFG_SPEED_INT
} JSON_StructType;

typedef enum  _SignalType
{
	PARAMETER_CFG_WEB_RQ,
	PARAMETER_CFG_SYS_RESP,
	PARAMETER_CFG_WEB_RESP,
	DIAG_PARAMETER_RCV_NOTIFY,
	STATE_RCV_NOTIFY,
	POWER_DOWN_RQ,
	MSG_MONITOR_RCV,
	MSG_MONITOR_RUN,
	MSG_MONITOR_START,
	MSG_MONITOR_END,
	DIAG_JSON_FILE,
	STATE_JSON_FILE,
	MSG_JSON_FILE,
} SignalType;

#ifdef __cplusplus   
extern "C" {
#endif

extern void Get_Json_Struct(JSON_StructType StructType, void * Des);
extern void Set_Json_Struct(JSON_StructType StructType, void * Src);
extern void GetSignal_B(SignalType Signal);
extern void SetSignal_B(SignalType Signal);
extern int GetSignal_NB(SignalType Signal, int gtimeSet);
extern t_MsgMonitorFileFlag Get_MsgMonitor_File_State();
extern void Set_MsgMonitor_File_State(t_MsgMonitorFileFlag Flag);
extern int SemInit();
extern int MutexInit();

#ifdef __cplusplus
}
#endif

#define SEM_INIT(INFO)							 SemInit(INFO)
#define MUTE_INIT(INFO)							 MutexInit(INFO)

#define GET_MSGMONITOR_FILE_STATE(INFO1)       Get_MsgMonitor_File_State(INFO1)
#define SET_MSGMONITOR_FILE_STATE(INFO1)       Set_MsgMonitor_File_State(INFO1)
#define GET_JSON_STRUCT(INFO1, INFO2)          Get_Json_Struct(INFO1, INFO2)
#define SET_JSON_STRUCT(INFO1, INFO2)          Set_Json_Struct(INFO1, INFO2)
#define GET_SIGNAL_B(INFO)                     GetSignal_B(INFO)
#define SET_SIGNAL_B(INFO)                     SetSignal_B(INFO)
#define GET_SIGNAL_NB(INFO1,INFO2)             GetSignal_NB(INFO1,INFO2)

typedef enum  _SendModleType
{
	POWERM,
	CFGM,
} SendModleType;



#endif


