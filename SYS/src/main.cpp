/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       main.c
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : main.c
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
#include <thread>
#include <unistd.h>

#include "wj_log.h"
#include "DiagM.h"
#include "CfgM.h"
#include "MsgRcvSd.h"
#include "StateM.h"
//#include "PowerM.h"
#include "WebServerM.h"
#include "MsgMonitor.h"
#include "Cfg.h"
#include "LED.h"
#ifdef __cplusplus
extern "C"
{
#endif
#include "SWversynchronise.h"
#ifdef __cplusplus
}
#endif

#define SYS_SOFTVERSION "WJ_OBU_SYS_20210906"
#define MODULE_NAME "SYS"

int main()
{
	int ret;
	/* 1.log模块初始化 */
	LogInit();
	LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "sysM start running.");

	//软件版本号同步;
	ret = SW_versionsync(MODULE_NAME, SYS_SOFTVERSION);
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "software synchonise result %d ", ret);

	/* 2.互斥量初始化 */
	ret = MUTE_INIT();
	if (ret != 0)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Mutex init error.");
		return 0;
	}

	/* 3. 信号量初始化 */
	ret = SEM_INIT();
	if (ret != 0)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "sem_init error");
		return 0;
	}
	LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "sem init success.");

	/* 4.线程创建 */
	std::thread threadObj_LEDinit(LEDINIT);
	std::thread threadObj_MsgM(MSGM_RCVSD_MAIN);
	std::thread threadObj_StateM(STATEM_MAIN);
	std::thread threadObj_DiagM(DIAGM_MAIN);
	//std::thread threadObj_CfgM(CFGM_MAIN);
	// std::thread threadObj_PowerM(POWERM_MAIN);       //后装OBU无电源管理模块
	// std::thread threadObj_WebserverM(WEBSERVERM_MAIN);
	std::thread threadObj_MsgMonitor(MSGMONITOR_MAIN);

	threadObj_MsgM.join();
	threadObj_StateM.join();
	threadObj_DiagM.join();
	//threadObj_CfgM.join();
	// threadObj_PowerM.join();         //后装OBU无电源管理模块
	// threadObj_WebserverM.join();
	threadObj_MsgMonitor.join();
	LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "SYSM EXIT.");

	return 0;
}
