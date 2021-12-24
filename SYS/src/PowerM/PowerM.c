/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       PowerM.c
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : PowerM.c
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
*   01.00.00  07/07/2020   chengwu.wang       N/A         Original
********************************************************************************
*END_FILE_HDR*/

#include <stdio.h>
#include <string.h>
#include "wj_log.h"
#include "PowerM.h"
#include "PowerM_Lcfg.h"
#include "Cfg.h"
#include "MsgRcvSd.h"
void PowerM_Main()
{	
	SysMcuConfigRs_all powerresp;
#if 0
	while(1)
	{
		/* 获取信号 */
		GET_SIGNAL_B(POWER_DOWN_RQ);
		LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "PowerM get signal success");

		/* 获取结构体信息 */
		GET_JSON_STRUCT(MCU_PWRDWN_RQ_STRUCT, (void *)&POWERM_REQUEST_INFO_T);
		LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "PowerM get struct success");

		/* 处理结构体信息 */
		if(POWERM_REQUEST_VALUE == POWERM_POWERDOWN_RQ_VALID)
		{
			POWERM_POWERDOWN_RESP = POWERM_POWERDOWN_RESP_VALID;
			memset(&powerresp, 0xff, sizeof(SysMcuConfigRs_all));
			memcpy(&powerresp.mcursdata.PowerDownResp, &POWERM_POWERDOWN_RESP, sizeof(powerresp.mcursdata.PowerDownResp));
			MSGM_SEND_SIGNAL(&powerresp, sizeof(SysMcuConfigRs_all), SYS_MCU_PD);
			LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "PowerM send respone success");
		}
		else
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "PowerM request value error");


		
	}
#endif
}


