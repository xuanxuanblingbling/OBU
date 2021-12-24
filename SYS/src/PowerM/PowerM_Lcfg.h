/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       PowerM.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : PowerM.h
*   Author:         : chengwu.wang       2020
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
*   01.00.00  07/07/2020  chengwu.wang      N/A         Original
********************************************************************************
*END_FILE_HDR*/

#ifndef POWERM_LCFG_H
#define POWERM_LCFG_H


#include "PowerM.h"
#include "Cfg.h"

typedef struct _PowerM_PwrResp{
	int					PowerRespValue;
} PowerM_PwrResp;


static PowerM_PwrResp  gPowerM_Resp_Info;
//static PowerM_PwrRq	 gPowerM_Rq_Info;

// #define POWERM_REQUEST_INFO_T      			gPowerM_Rq_Info
// #define POWERM_REQUEST_VALUE       			gPowerM_Rq_Info.PowerRqValue
// #define POWERM_POWERDOWN_RQ_VALID			0X81

#define POWERM_RESP_INFO_T         			gPowerM_Resp_Info
#define POWERM_POWERDOWN_RESP	   			gPowerM_Resp_Info.PowerRespValue
#define POWERM_POWERDOWN_RESP_VALID 		0x80

#endif

