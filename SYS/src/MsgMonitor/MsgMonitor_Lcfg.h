
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
#ifndef MSGMONITOR_LCFG_H
#define MSGMONITOR_LCFG_H

#include "MsgMonitor.h"

static cJSON *gpMsgMonitor_Json_File;
#define MSGMONITOR_JSON_FILE                  gpMsgMonitor_Json_File

static int gMsgMonitor_SignalIndex = 0;
#define MSGMONITOR_SIGNAL_INDEX                  gMsgMonitor_SignalIndex

static MsgMonitor_Json gMsgMonitorJson;
#define MSGMONITOR_JSON_INFO                gMsgMonitorJson
#define MSGMONITOR_TAG_T                    gMsgMonitorJson.Tag
#define MSGMONITOR_SIGNAL_VALUE_T           gMsgMonitorJson.SignalValue
#define MSGMONITOR_TIME_T                   gMsgMonitorJson.TimeBuf

#define MSGMONITOR_BUF_SIZE					1024*10

typedef struct _MsgMonitor_InfoTable{
	int						   			Tag;
	char                    			DataSrcName[10];
	char                    			DataDesName[30];
	uint8_t                     		*Data;
	char 								*Time;
} MsgMonitor_InfoTable;


#define MSGMONITOR_SIGNAL_NUM    				     1
static MsgMonitor_InfoTable gMsgMonitorInfoTable[MSGMONITOR_SIGNAL_NUM] = {
	{MSGMONITOR_1001, "VDS", "V2X APP NET SYS", MSGMONITOR_SIGNAL_VALUE_T, MSGMONITOR_TIME_T},
};


#define MSGMONITOR_TAG_INDEX(INDEX)          gMsgMonitorInfoTable[INDEX].Tag
#define MSGMONITOR_SRC_NAME(INDEX)           gMsgMonitorInfoTable[INDEX].DataSrcName
#define MSGMONITOR_DES_NAME(INDEX)           gMsgMonitorInfoTable[INDEX].DataDesName
#define MSGMONITOR_DATA(INDEX)               gMsgMonitorInfoTable[INDEX].Data
#define MSGMONITOR_TIME(INDEX)               gMsgMonitorInfoTable[INDEX].Time

#define MSGMONITOR_FILE_NAME                  "/mnt/APP/Config/obu/sysm/MsgMonitor/MsgMonitor.json"

typedef enum  _t_MsgMonitorRetFlag
{
	MSGMONITOR_SUCCESS,
	MSGMONITOR_FALSE,
} t_MsgMonitorRetFlag;

#endif
