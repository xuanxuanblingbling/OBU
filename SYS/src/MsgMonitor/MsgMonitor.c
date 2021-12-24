/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       CfgM.c
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : CfgM.c
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
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "wj_log.h"
#include "cJSON.h"
#include "Cfg.h"
#include "MsgMonitor.h"
#include "MsgMonitor_Lcfg.h"

static t_MsgMonitorRetFlag MsgMonitor_ReadJFile(char *filename)
{
    char buf[MSGMONITOR_BUF_SIZE]={0};
    FILE *fp;
    int  f_size;
    int  re_fread;
    int errNum;
    const char *error_ptr;

    if((fp = fopen(filename, "r")) == NULL)
    {
        errNum = errno;
        LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MsgMonitor open fail errno = %d reason = %s \n", errNum, strerror(errNum));
        return MSGMONITOR_FALSE;
    }

    LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor fopen %s r success", filename);

    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp);
    rewind(fp);

    re_fread = fread(buf, f_size, 1, fp);
    if(re_fread != 1)
    {    
        fclose(fp);
        LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MsgMonitor fread %s error", filename);
        return MSGMONITOR_FALSE;
    }
    fclose(fp);

    MSGMONITOR_JSON_FILE = cJSON_Parse(buf);

    if(NULL == MSGMONITOR_JSON_FILE)
    {
        error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MsgMonitor cJSON_Parse error: %s", error_ptr);
        else
            LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MsgMonitor cJSON_Parse %s error", filename);
        return MSGMONITOR_FALSE;
    }
    else
        LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor cJSON_Parse %s success", filename);
    return MSGMONITOR_SUCCESS;
}

static void MsgMonitor_AddInfo(char *DataSrcName, char *DataDesName, uint8_t *Signal, char *Time)
{
	cJSON *SubItem;
	char itemNameHead[] = {"Msg"};
	char itemName[20];
	int i;
	char buf[300];
	char buftmp[10];

	if(GET_MSGMONITOR_FILE_STATE() == MSGMONITOR_NOOPR)
	{
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor file state is noopr");
		MSGMONITOR_SIGNAL_INDEX++;
	}
	else
	{
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor file state is opr");
		SET_MSGMONITOR_FILE_STATE(MSGMONITOR_NOOPR);
		MSGMONITOR_SIGNAL_INDEX = 0;
		if (MSGMONITOR_JSON_FILE)
		{
			cJSON_Delete(MSGMONITOR_JSON_FILE);
			MSGMONITOR_JSON_FILE = NULL;
		}
		MSGMONITOR_JSON_FILE = cJSON_CreateObject();
	}

	/* 定期清除 */
	if(MSGMONITOR_SIGNAL_INDEX == 20)
	{
		SET_MSGMONITOR_FILE_STATE(MSGMONITOR_OPR);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor file index is clean");
	}
	snprintf(itemName, 10, "%s%d", itemNameHead, MSGMONITOR_SIGNAL_INDEX);

	SubItem = cJSON_CreateObject();
	cJSON_AddItemToObject(MSGMONITOR_JSON_FILE, itemName, SubItem);

	cJSON_AddStringToObject(SubItem, "Time", Time);
	cJSON_AddStringToObject(SubItem,"Src",DataSrcName);
	cJSON_AddStringToObject(SubItem,"Des",DataDesName);

	memset(buf, 0, 300);
	memset(buftmp, 0, 10);
	for(i = 0; i < MSGMONITOR_SIGNAL_SIZE; i++)
	{
		/* 前17个字节是车辆ID可以输入字母 */
		if(i<17)
		{
			sprintf(buftmp, "%c", Signal[i]);
			buftmp[1] = '\0';
			strcat(buf, buftmp);
			strcat(buf, " ");
		}
		else
		{
			sprintf(buftmp, "%d", Signal[i]);
			strcat(buf, buftmp);
			strcat(buf, " ");
		}	
	}

	cJSON_AddStringToObject(SubItem,"Msg",buf);

}

t_MsgMonitorRetFlag MsgMonitor_WriteJFile(char *filename, cJSON *json)
{
    char *re_cjprint;
    FILE *fp;
    int  re_fwrite;
    re_cjprint = cJSON_Print(json);

    /*    free CREATOBJECT    */
    if (MSGMONITOR_JSON_FILE)
    {
        cJSON_Delete(MSGMONITOR_JSON_FILE);
        MSGMONITOR_JSON_FILE = NULL;
    }

    fp = fopen(filename, "w");
    if(NULL == fp)
    {
        cJSON_free(re_cjprint);
        LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MsgMonitor fopen a error");
        return MSGMONITOR_FALSE;    
    }
    else
	{
	
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor fopen %s a success",filename);
		re_fwrite = fwrite(re_cjprint, strlen(re_cjprint), 1, fp);
		if(re_fwrite != 1)
		{
			cJSON_free(re_cjprint);
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MsgMonitor fwrite error");
			return MSGMONITOR_FALSE;
		}
		fclose(fp);
	}
   	cJSON_free(re_cjprint);
    return MSGMONITOR_SUCCESS;
}

void MsgMonitor_Main()
{
	int i;
	t_MsgMonitorRetFlag ret;
	
	SET_SIGNAL_B(MSG_MONITOR_END);
	LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "MsgMonitor modle start running");
	while(1)
	{
		GET_SIGNAL_B(MSG_MONITOR_RUN);
		/* 1.有数据接收则处理，否则挂起 */
		GET_SIGNAL_B(MSG_MONITOR_RCV);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor get signal success");

		/* 2.获取json数据 */
		GET_JSON_STRUCT(MSGMONITOR_JSON_STRUCT, (void *)&MSGMONITOR_JSON_INFO);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor get json struct success");
		
		for(i = 0; i < MSGMONITOR_SIGNAL_NUM; i++)
		{
			if(MSGMONITOR_TAG_T ==  MSGMONITOR_TAG_INDEX(i))
			{
		
				/* 3.读文件 */
				LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor start Read File %s", MSGMONITOR_FILE_NAME);
				ret = MsgMonitor_ReadJFile(MSGMONITOR_FILE_NAME);
				if(ret == MSGMONITOR_FALSE)
					break;

				/* 4.添加json结构体内容 */
				LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor start add info into JsonStruct");
				MsgMonitor_AddInfo(MSGMONITOR_SRC_NAME(i), MSGMONITOR_DES_NAME(i), MSGMONITOR_DATA(i), MSGMONITOR_TIME(i));
				LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor add info into JsonStruct end");

				/* 5.写文件加锁 */
				LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor start write Jsonfile");
				GET_SIGNAL_B(MSG_JSON_FILE);
				ret = MsgMonitor_WriteJFile(MSGMONITOR_FILE_NAME, MSGMONITOR_JSON_FILE);
				SET_SIGNAL_B(MSG_JSON_FILE);
				if(ret == MSGMONITOR_FALSE)
				{
					LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MsgMonitor Write Jsonfile false");
					break;
				}
				LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgMonitor Write Jsonfile success");
			}
		}
	}
}

