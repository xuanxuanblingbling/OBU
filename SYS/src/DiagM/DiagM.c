/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       DiagM.c
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : DiagM.c
*   Author:         : chengwu.wang                 2020
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
*   01.00.00  07/07/2020   chengwu.wang      N/A         Original
********************************************************************************
*END_FILE_HDR*/
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include "wj_log.h"

#include "cJSON.h"
#include "Cfg.h"
#include "DiagM.h"
#include "DiagM_Lcfg.h"
#include "LED.h"

static t_DiagMRetFlag DiagM_ReadJFile(char *filename)
{
	char buf[DIAGM_BUF_SIZE]={0};
    FILE *fp;
    int  f_size;
    int  re_fread;
	int errNum;
	const char *error_ptr;

	if((fp = fopen(filename, "r")) == NULL)
    {
        errNum = errno;
        LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "DiagM open fail errno = %d reason = %s \n", errNum, strerror(errNum));
        return DIAGM_FALSE;
    }

    LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "DiagM fopen %s r success", filename);

    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp);
    rewind(fp);

    re_fread = fread(buf, f_size, 1, fp);
    if(re_fread != 1)
    {    
        fclose(fp);
        LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "DiagM fread %s error", filename);
        return DIAGM_FALSE;
    }
    fclose(fp);
	
    DIAGM_JSON_FILE = cJSON_Parse(buf);

    if(NULL == DIAGM_JSON_FILE)
    {
		error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "DiagM cJSON_Parse error: %s", error_ptr);
		else
		    LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "DiagM cJSON_Parse %s error", filename);
		return DIAGM_FALSE;
	}
	return DIAGM_SUCCESS;
}


static t_DiagMRetFlag DiagM_WriteJFile(char *filename, cJSON *json)
{
    char *re_cjprint;
    FILE *fp;
    int  re_fwrite;
	re_cjprint = cJSON_Print(json);

	if (DIAGM_JSON_FILE)
	{	
		cJSON_Delete(DIAGM_JSON_FILE);
		DIAGM_JSON_FILE = NULL;
	}

    fp = fopen(filename, "w");
    if(NULL == fp)
    {
        cJSON_free(re_cjprint);
        LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "DiagM fopen a error");
        return DIAGM_FALSE;    
    }
    else
	{
	
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "DiagM fopen %s a success",filename);
		re_fwrite = fwrite(re_cjprint, strlen(re_cjprint), 1, fp);
		if(re_fwrite != 1)
		{
			cJSON_free(re_cjprint);
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "DiagM fwrite error");
			return DIAGM_FALSE;
		}
		fclose(fp);
	}
	cJSON_free(re_cjprint);
	return DIAGM_SUCCESS;
}

static void DiagM_ChgSnapShot_Info(cJSON *SnapShotJson, Diag_Snap_Shot *ptSnapShot)
{
	struct timeval tv;
	char time_buf[20];
	time_t ti;
	FILE *fp;
	cJSON *JsonTmp;
	int temp;
	long microsecond;
	int speed;
	
	/* 修改时间 */	
	JsonTmp = cJSON_GetObjectItem(SnapShotJson, "SysTime");	
	gettimeofday(&tv, NULL);
	ti = tv.tv_sec;
	microsecond = tv.tv_usec/1000;
	memset(time_buf, 0, sizeof(time_buf));
	strftime(time_buf, 20, "%Y.%m.%d %H:%M:%S", localtime(&ti));
	snprintf (ptSnapShot->SysTime, 30, "%s.%03ld", time_buf, microsecond);

	printf("====[test] inforjson %s  %s  \n",cJSON_Print(JsonTmp),ptSnapShot->SysTime);

	cJSON_SetValuestring(JsonTmp, ptSnapShot->SysTime);
	LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "DiagM Diagtime has changed");

	/* 修改温度 */
	JsonTmp = cJSON_GetObjectItem(SnapShotJson, "SocTemp");	
	fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
	if(NULL == fp)
		LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "DIAGM fopen SocTemp r error");
	else
	{
		fscanf(fp, "%d", &temp);	
		fclose(fp);
	}

	sprintf(ptSnapShot->SocTemp, "%.3f", temp/1000.0);
	cJSON_SetValuestring(JsonTmp, ptSnapShot->SocTemp);


	/* 修改速度 */
	GET_JSON_STRUCT(DIAGCFG_SPEED_INT, &speed);
	sprintf(ptSnapShot->CurrentSpeed, "%d", speed);
	JsonTmp = cJSON_GetObjectItem(SnapShotJson, "CurrentSpeed");
	cJSON_SetValuestring(JsonTmp, ptSnapShot->CurrentSpeed);
}

static void DiagM_ChgJFile(int ModleName)
{	
	uint8_t i,j;
	cJSON *DtcName_Json,*Info_Json;
	cJSON *re_FirRoot;

	for(i = 0; i < DIAGM_MODLE_NUM; i++)
	{
		if((DIAGM_MODLE_INDEX(i) & ModleName) != 0)
		{	
			re_FirRoot = cJSON_GetObjectItem(DIAGM_JSON_FILE,DIAGM_MODLE_NAME(i));
			for(j = 0; j < DIAGM_DTC_NUM(i); j++)
			{
				DtcName_Json = cJSON_GetObjectItem(re_FirRoot, DIAGM_DTC_NAME(i,j));
				Info_Json = cJSON_GetObjectItem(DtcName_Json, "DiagState");
				cJSON_SetIntValue(Info_Json, DIAGM_DTC_STATE(i,j));
				LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "DiagM %s DiagState has changed",DIAGM_DTC_NAME(i,j));
		        
				if(DIAGM_DTC_STATE(i,j) == DIAGM_TROUBLE)
				{
					//查找对应模块 并重启
				    DiagM_RestartMoudle(DIAGM_MODLE_NAME(i));
					if(DIAGM_DTC_FLAG(i,j) == DIAGM_INVALID)
					{
						Info_Json = cJSON_GetObjectItem(DtcName_Json, DIAGM_SNAPSHOT2);
						DiagM_ChgSnapShot_Info(Info_Json, &DIAGM_DTC_SNAPSHOT2(i,j));
						DIAGM_DTC_FLAG(i,j) = DIAGM_VALID;
						LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "DiagM %s snapshot2 has changed", DIAGM_DTC_NAME(i,j));
					}
					else
					{
						Info_Json = cJSON_GetObjectItem(DtcName_Json, DIAGM_SNAPSHOT1);
						DiagM_ChgSnapShot_Info(Info_Json, &DIAGM_DTC_SNAPSHOT1(i,j));
						LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "DiagM %s snapshot1 has changed", DIAGM_DTC_NAME(i,j));
					}
				}
			}
		}
	}
}

void DiagM_Main()
{
	t_DiagMRetFlag ret;
	
	LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "DiagM modle start running");

	while(1)
	{
		/* 1.有数据接收则处理，否则挂起 */
		GET_SIGNAL_B(DIAG_PARAMETER_RCV_NOTIFY);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "DiagM get signal success");

		/* 2.获取json数据 */
		GET_JSON_STRUCT(DIAGCFG_JSON_STRUCT, (void *)&DIAGM_JSON_INFO);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "DiagM get json struct success");

		/* 3.读文件 */
		ret = DiagM_ReadJFile(DIAGM_DIAGFILE_NAME);
		if(ret == DIAGM_FALSE)
			continue;
		else
		{
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "DiagM Read File %s success", DIAGM_DIAGFILE_NAME);
	
			/* 4.解析，修改 */
			DiagM_ChgJFile(DIAGM_KEYID);
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "DiagM chg %s struct success", DIAGM_DIAGFILE_NAME);
	
			/* 4.写文件加锁 */
			GET_SIGNAL_B(DIAG_JSON_FILE);
			ret = DiagM_WriteJFile(DIAGM_DIAGFILE_NAME, DIAGM_JSON_FILE);
			SET_SIGNAL_B(DIAG_JSON_FILE);
			if(ret == DIAGM_SUCCESS)
				LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM Write file %s success", DIAGM_DIAGFILE_NAME);
		}
	}
}

/************************************
@ NAME : DiagM_RestartMoudle
@ bref:  重启对应模块进程
@ input： 重启模块的名称
@ output: 是否重启成功
*****************************************/
int DiagM_RestartMoudle(char * MOUDLENAME)
{
    FILE* fp;
	int count = 0;
    char command[50];
	char retbuf[1024];
	char *modulname =NULL;
	uint8_t l_u8RestarFlage= 0;
	static s_u8Count[5]={0};

	if(!strcmp(MOUDLENAME,"App"))
	{
		if(s_u8Count[0] > 2)
		{
			l_u8RestarFlage =1;
		}
		else
		{
			s_u8Count[0] ++;
		}	
		modulname = "app";	
	}
	else if(!strcmp(MOUDLENAME,"V2x"))
	{
		if(s_u8Count[1] > 2)
		{
			l_u8RestarFlage =1;
		}
		else
		{
			s_u8Count[1] ++;
		}
		modulname = "V2X_APP.bin";
		LEDStateSet(V2Xname,RED);
	}
	else if(!strcmp(MOUDLENAME,"Net"))
	{
		if(s_u8Count[2] > 2)
		{
			l_u8RestarFlage =1;
		}
		else
		{
			s_u8Count[2] ++;
		}
		modulname = "NET_ARM.bin";
		LEDStateSet(vdsname,RED);
	} 
	else if(!strcmp(MOUDLENAME,"Vds"))
	{
		if(s_u8Count[3] > 2)
		{
			l_u8RestarFlage =1;
		}
		else
		{
			s_u8Count[3] ++;
		}
		modulname = "vds";
	}
	else
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "recive fault message ERROR");
		return 0;
	}
	
	

	sprintf(command, "ps|grep %s|grep -v grep|cut -c 0-6", modulname);
	 if((fp = popen(command,"r")) == NULL)
	 {
		  LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "ps program popen err");		 
	 }
     while((fgets(retbuf,20,fp))!= NULL )
	 {
		 LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "result %s",retbuf);
		 memset(command,0,sizeof(command));	
		 sprintf(command, "kill -9 %s",retbuf);
		 if((fp = popen(command,"r")) == NULL)
	     {
            LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "kill program popen err");		 
	     }
		 memset(command,0,sizeof(command));
		 sprintf(command, "ps|grep %s|grep -v grep|cut -c 0-6", modulname);
	     if((fp = popen(command,"r")) == NULL)	
		 {
			 LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "ps program popen err");	
		 }  
		 
	 }
     
	 printf("===[test] %d ==\n",l_u8RestarFlage);
	 if(l_u8RestarFlage == 0)
	 {	
		memset(command,0,sizeof(command));
		sprintf(command, "./%s &",modulname);
		if((fp = popen(command,"r")) == NULL)
		{
			LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "restart program popen err");		 
		}
		if((fgets(retbuf,1024,fp))!= NULL )
		{
			LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "restart err info is %s",retbuf);		   
		}
		
	 }

     pclose(fp);
}
