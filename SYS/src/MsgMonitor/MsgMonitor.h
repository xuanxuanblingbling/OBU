/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       MsgMonitor.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : MsgMonitor.h
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
#ifndef MSGMONITOR_H
#define MSGMONITOR_H

#include "stdio.h"

#define MSGMONITOR_MAIN    					MsgMonitor_Main
#ifdef __cplusplus   
extern "C" {
#endif

extern void MsgMonitor_Main();

#ifdef __cplusplus   
}
#endif


#define MSGMONITOR_SIGNAL_SIZE       60

typedef struct _MsgMonitor_Json{
	char                    TimeBuf[30];
	int                     Tag;
	uint8_t        			SignalValue[MSGMONITOR_SIGNAL_SIZE];
}MsgMonitor_Json;

typedef enum  _t_MsgMonitorFileFlag
{
	MSGMONITOR_OPR,
	MSGMONITOR_NOOPR,
} t_MsgMonitorFileFlag;


#define MSGMONITOR_1001              0


#endif
