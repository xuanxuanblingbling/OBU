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
#include "CfgM.h"
#include "CfgM_Lcfg.h"
#include "MsgRcvSd.h"


static t_CfgMRetFlag CfgM_ReadJFile(char *filename)
{
	char buf[CFGM_BUF_SIZE]={0};
    FILE *fp;
    int  f_size;
    int  re_fread;
	int errNum;

	 if((fp = fopen(filename, "r")) == NULL)
    {
        errNum = errno;
        LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM open fail errno = %d reason = %s \n", errNum, strerror(errNum));
        return CFGM_FALSE;
    }

    LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM fopen %s r success", filename);

    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp);
    rewind(fp);

    re_fread = fread(buf, f_size, 1, fp);
    if(re_fread != 1)
    {    
        fclose(fp);
        LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM fread %s error", filename);
        return CFGM_FALSE;
    }
    fclose(fp);

    CFGM_JSON_FILE = cJSON_Parse(buf);

    if(NULL == CFGM_JSON_FILE)
    {
	    LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM cJSON_Parse %s error", filename);	
		return CFGM_FALSE;
	}
	else
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM cJSON_Parse %s success", filename);
	return CFGM_SUCCESS;
}

t_CfgMRetFlag CfgM_WriteJFile(char *filename, cJSON *json)
{
    char *re_cjprint;
    FILE *fp;
    int  re_fwrite;
	re_cjprint = cJSON_Print(json);
	printf("====[test] %s ====\n",re_cjprint);

	if (CFGM_JSON_FILE)
	{
		cJSON_Delete(CFGM_JSON_FILE);
		CFGM_JSON_FILE = NULL;
	}

   	fp = fopen(filename, "w");
    if(NULL == fp)
    {
        cJSON_free(re_cjprint);
        LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM fopen a error");
        return CFGM_FALSE;    
    }
    else
	{
	
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM fopen %s a success",filename);
		re_fwrite = fwrite(re_cjprint, strlen(re_cjprint), 1, fp);
		if(re_fwrite != 1)
		{
			cJSON_free(re_cjprint);
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM fwrite error");
			return CFGM_FALSE;
		}
		fclose(fp);
	}
	cJSON_free(re_cjprint);
	return CFGM_SUCCESS;
}
void CfgM_AppASCfg_Fun()
{
	cJSON *cJsonHandle;
	int i;

	for(i = 0; i < CFGM_APPAS_MKEY_NUM; i++)
	{
		cJsonHandle = cJSON_GetObjectItem(CFGM_JSON_FILE, CFGM_APPAS_MKEY_NAME_T(i));
		if(CFGM_APPAS_MKEY_TYPE_T(i) == CJSON_INT)
		{
			cJSON_SetIntValue(cJsonHandle, *CFGM_APPAS_MKEY_CJSONINT_T(i));
		}
		else if(CFGM_APPAS_MKEY_TYPE_T(i) == CJSON_STRING)
			cJSON_SetValuestring(cJsonHandle, CFGM_APPAS_MKEY_CJSONSTRING_T(i));
	}
}
void CfgM_AppMMCfg_Fun()
{
	cJSON *cJsonHandle;
	int i;

	for(i = 0; i < CFGM_APPMM_MKEY_NUM; i++)
	{
		cJsonHandle = cJSON_GetObjectItem(CFGM_JSON_FILE, CFGM_APPMM_MKEY_NAME_T(i));
		if(CFGM_APPMM_MKEY_TYPE_T(i) == CJSON_INT)
		{
			cJSON_SetIntValue(cJsonHandle, *CFGM_APPMM_MKEY_CJSONINT_T(i));
		}
		else if(CFGM_APPMM_MKEY_TYPE_T(i) == CJSON_STRING)
			cJSON_SetValuestring(cJsonHandle, CFGM_APPMM_MKEY_CJSONSTRING_T(i));
	}
}
void CfgM_AppMTCfg_Fun()
{
	cJSON *cJsonHandle;
	int i;

	for(i = 0; i < CFGM_APPMT_MKEY_NUM; i++)
	{
		cJsonHandle = cJSON_GetObjectItem(CFGM_JSON_FILE, CFGM_APPMT_MKEY_NAME_T(i));
		if(CFGM_APPMT_MKEY_TYPE_T(i) == CJSON_INT)
		{
			cJSON_SetIntValue(cJsonHandle, *CFGM_APPMT_MKEY_CJSONINT_T(i));
		}
		else if(CFGM_APPMT_MKEY_TYPE_T(i) == CJSON_STRING)
			cJSON_SetValuestring(cJsonHandle, CFGM_APPMT_MKEY_CJSONSTRING_T(i));
	}
}
void CfgM_AppTLCfg_Fun()
{
	cJSON *cJsonHandle;
	int i;

	for(i = 0; i < CFGM_APPTL_MKEY_NUM; i++)
	{
		cJsonHandle = cJSON_GetObjectItem(CFGM_JSON_FILE, CFGM_APPTL_MKEY_NAME_T(i));
		if(CFGM_APPTL_MKEY_TYPE_T(i) == CJSON_INT)
		{
			cJSON_SetIntValue(cJsonHandle, *CFGM_APPTL_MKEY_CJSONINT_T(i));
		}
		else if(CFGM_APPTL_MKEY_TYPE_T(i) == CJSON_STRING)
			cJSON_SetValuestring(cJsonHandle, CFGM_APPTL_MKEY_CJSONSTRING_T(i));
	}
}


void CfgM_V2XServerCfg_Fun()
{
	cJSON *cJsonHandle1,*cJsonHandle2;
	int i,j,k = 0;

	for(i = 0; i < CFGM_V2X_MKEY_NUM; i++)
	{
		cJsonHandle1 = cJSON_GetObjectItem(CFGM_JSON_FILE, CFGM_V2X_MKEY_NAME_T(i));
		for(j = 0; j < CFGM_V2X_SKEY_NUM_T(i); j++)
		{
			cJsonHandle2 = cJSON_GetObjectItem(cJsonHandle1, CFGM_V2X_SKEY_NAME_T(k));
			if(CFGM_V2X_SKEY_TYPE_T(k) == CJSON_INT)
			{
				cJSON_SetIntValue(cJsonHandle2, *CFGM_V2X_SKEY_CJSONINT_T(k));
			}
			else if(CFGM_V2X_SKEY_TYPE_T(k) == CJSON_STRING)
				cJSON_SetValuestring(cJsonHandle2, CFGM_V2X_SKEY_CJSONSTRING_T(k));
			k++;
		}
	}
}
void CfgM_VDSCfg_Fun()
{
	cJSON *cJsonHandle1,*cJsonHandle2;
	int i,j,K = 0;
	
	for(i = 0; i < CFGM_VDS_MKEY_NUM; i++)
	{
		cJsonHandle1 = cJSON_GetObjectItem(CFGM_JSON_FILE, CFGM_VDS_MKEY_NAME_T(i));
		for(j = 0; j < CFGM_VDS_SKEY_NUM_T(i); j++)
		{
			cJsonHandle2 = cJSON_GetObjectItem(cJsonHandle1, CFGM_VDS_SKEY_NAME_T(K));
			if(CFGM_VDS_SKEY_TYPE_T(K) == CJSON_INT)
			{
				cJSON_SetIntValue(cJsonHandle2, *CFGM_VDS_SKEY_CJSONINT_T(K));
			}
			else if(CFGM_VDS_SKEY_TYPE_T(K) == CJSON_STRING)
				cJSON_SetValuestring(cJsonHandle2, CFGM_VDS_SKEY_CJSONSTRING_T(K));
			K++;
			
		}
	}
}

void CfgM_MCUCfg_Fun()
{
	cJSON *cJsonHandle;
	int i;
	for(i = 0; i < CFGM_MCU_MKEY_NUM; i++)
	{	
		cJsonHandle = cJSON_GetObjectItem(CFGM_JSON_FILE, CFGM_MCU_MKEY_NAME_T(i));
		if(CFGM_MCU_MKEY_TYPE_T(i) == CJSON_INT)
		{
			cJSON_SetIntValue(cJsonHandle, *CFGM_MCU_MKEY_INT_T(i));
		}
		else if(CFGM_MCU_MKEY_TYPE_T(i) == CJSON_STRING)
			cJSON_SetValuestring(cJsonHandle, CFGM_MCU_MKEY_STRING_T(i));
	}
}

void CfgM_NetCfg_Fun()
{
	cJSON *cJsonHandle1,*cJsonHandle2;
	int i,j,K = 0;

	for(i = 0; i < CFGM_NET_MKEY_NUM; i++)
	{
		cJsonHandle1 = cJSON_GetObjectItem(CFGM_JSON_FILE, CFGM_NET_MKEY_NAME_T(i));
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "keyname %s",CFGM_NET_MKEY_NAME_T(i));
		if(CFGM_NET_MKEY_TYPE_T(i) == CJSON_STRUCT)
		{
			for(j = 0; j < CFGM_NET_SKEY_NUM_T(i); j++)
			{
				cJsonHandle2 = cJSON_GetObjectItem(cJsonHandle1, CFGM_NET_SKEY_NAME_T(K));
				LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "keyname %s",CFGM_NET_SKEY_NAME_T(K));
				if(CFGM_NET_SKEY_TYPE_T(K) == CJSON_INT)
				{
					LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "valueint %d",CFGM_NET_SKEY_CJSONINT_T(K));
					cJSON_SetIntValue(cJsonHandle2, *CFGM_NET_SKEY_CJSONINT_T(K));
				}
				else if(CFGM_NET_SKEY_TYPE_T(K) == CJSON_STRING)
					cJSON_SetValuestring(cJsonHandle2, CFGM_NET_SKEY_CJSONSTRING_T(K));
				K++;
			}
		}
		else if(CFGM_NET_MKEY_TYPE_T(i) == CJSON_INT)
		{
			cJSON_SetIntValue(cJsonHandle1, *CFGM_NET_MKEY_CJSONINT_T(i));
		}
	}
}

static void CfgM_BasicInfoCfg_Fun()
{
	cJSON *cJsonHandle;
	int i;

	for(i = 0; i < CFGM_BASIC_MKEY_NUM; i++)
	{
		cJsonHandle = cJSON_GetObjectItem(CFGM_JSON_FILE, CFGM_BASIC_MKEY_NAME_T(i));
		if(CFGM_BASIC_MKEY_TYPE_T(i) == CJSON_INT)
		{
			cJSON_SetIntValue(cJsonHandle, *CFGM_BASIC_MKEY_INT_T(i));
		}
		else if(CFGM_BASIC_MKEY_TYPE_T(i) == CJSON_STRING)
			cJSON_SetValuestring(cJsonHandle, CFGM_BASIC_MKEY_STRING_T(i));
	}
}

static void CfgM_AppASCfg_Resp_Fun(int i, t_TimeOut_Type TimeOutFlag)
{
	CfgM_Resp tCfgMResp;
	GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);

	if(TimeOutFlag == TIMEOUT_INVALID)
	{
		if(tCfgMResp.tAppCfgResp.AppCfgResp == CFGM_RESP_FALSE)
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM APPAS response false");
			/* do sth */
		}
		else
		{
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM APPAS response success");
		}
	}
	else
	{
		tCfgMResp.tAppCfgResp.AppCfgResp = CFGM_RESP_FALSE;
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
	}

}
static void CfgM_AppMMCfg_Resp_Fun(int i, t_TimeOut_Type TimeOutFlag)
{
	CfgM_Resp tCfgMResp;
	GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);


	if(TimeOutFlag == TIMEOUT_INVALID)
	{
		if(tCfgMResp.tAppCfgResp.AppCfgResp == CFGM_RESP_FALSE)
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM APPMM response false");
			/* do sth */
		}
		else
		{
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM APPMM response success");
		}
	}
	else
	{
		tCfgMResp.tAppCfgResp.AppCfgResp = CFGM_RESP_FALSE;
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
	}


}
static void CfgM_AppMTCfg_Resp_Fun(int i, t_TimeOut_Type TimeOutFlag)
{
	CfgM_Resp tCfgMResp;
	GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);

	if(TimeOutFlag == TIMEOUT_INVALID)
	{
		if(tCfgMResp.tAppCfgResp.AppCfgResp == CFGM_RESP_FALSE)
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM APPMT response false");
			/* do sth */
		}
		else
		{
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM APPMT response success");
		}
	}
	else
	{
		tCfgMResp.tAppCfgResp.AppCfgResp = CFGM_RESP_FALSE;
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
	}
	

}
static void CfgM_AppTLCfg_Resp_Fun(int i, t_TimeOut_Type TimeOutFlag)
{
	CfgM_Resp tCfgMResp;
	GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);

	if(TimeOutFlag == TIMEOUT_INVALID)
	{
		if(tCfgMResp.tAppCfgResp.AppCfgResp == CFGM_RESP_FALSE)
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM APPTL response false");
			/* do sth */
		}
		else
		{
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM APPTL response success");
		}
	}
	else
	{
		tCfgMResp.tAppCfgResp.AppCfgResp = CFGM_RESP_FALSE;
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
	}


}
static void CfgM_V2XProtocolCfg_Resp_Fun(int i, t_TimeOut_Type TimeOutFlag)
{
	CfgM_Resp tCfgMResp;
	GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);

	if(TimeOutFlag == TIMEOUT_INVALID)
	{
		if(tCfgMResp.tV2xCfgResp.V2xCfgResp == CFGM_RESP_FALSE)
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM V2XProtocol response false");
			/* do sth */
		}
		else
		{
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM V2XProtocol response success");
		}
	}
	else
	{
		tCfgMResp.tV2xCfgResp.V2xCfgResp = CFGM_RESP_FALSE;
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
	}

}
static void CfgM_V2XServerCfg_Resp_Fun(int i, t_TimeOut_Type TimeOutFlag)
{
	CfgM_Resp tCfgMResp;
	GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);


	if(TimeOutFlag == TIMEOUT_INVALID)
	{
		if(tCfgMResp.tV2xCfgResp.V2xCfgResp == CFGM_RESP_FALSE)
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM V2XServer response false");
			/* do sth */
		}
		else
		{
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM V2XServer response success");
		}
	}
	else
	{
		tCfgMResp.tV2xCfgResp.V2xCfgResp = CFGM_RESP_FALSE;
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
	}


}
static void CfgM_VDSCfg_Resp_Fun(int i, t_TimeOut_Type TimeOutFlag)
{
	CfgM_Resp tCfgMResp;
	GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);

	if(TimeOutFlag == TIMEOUT_INVALID)
	{
		if(tCfgMResp.tVdsCfgResp.VdsCfgResp == CFGM_RESP_FALSE)
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM VDS response false");
			/* do sth */
		}
		else
		{	
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM VDS response success");
		}
	}
	else
	{
		tCfgMResp.tVdsCfgResp.VdsCfgResp = CFGM_RESP_FALSE;
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
	}

}
static void CfgM_MCUCfg_Resp_Fun(int i, t_TimeOut_Type TimeOutFlag)
{
	CfgM_Resp tCfgMResp;

	GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
	if(TimeOutFlag == TIMEOUT_INVALID)
	{
		if(tCfgMResp.tVdsCfgResp.McuCfgResp == CFGM_RESP_FALSE)
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM Mcu response false");
			/* do sth */
		}
		else
		{
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM Mcu response success");
		}
	}
	else
	{
		tCfgMResp.tVdsCfgResp.McuCfgResp = CFGM_RESP_FALSE;
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
	}
}

static void CfgM_Ag35Cfg_Resp_Fun(int i, t_TimeOut_Type TimeOutFlag)
{
	CfgM_Resp tCfgMResp;

	GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);

	if(TimeOutFlag == TIMEOUT_INVALID)
	{
		if(tCfgMResp.tVdsCfgResp.Ag35CfgResp == CFGM_RESP_FALSE)
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM Ag35 response false");
			/* do sth */
		}
		else
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM Ag35 response success");
		}
	}
	else
	{
		tCfgMResp.tVdsCfgResp.Ag35CfgResp = CFGM_RESP_FALSE;
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
	}
	
}
static void CfgM_McuCfgRq_RespJsonInfo_Fun(int i, t_TimeOut_Type TimeOutFlag)
{
	/* 写入json文件 */
	t_CfgMRetFlag ret;
	CfgM_Resp tCfgMResp;

	tCfgMResp.tVdsCfgResp.McuCfgResp = CFGM_RESP_FALSE;   //初始化回复失败
	if(TimeOutFlag == TIMEOUT_INVALID)
	{
		GET_JSON_STRUCT(CFGM_JSON_STRUCT, (void *)&CFGM_JSON_INFO);
		
		
		ret = CfgM_ReadJFile(CFGM_MCUCFG_FILENAME);
		if(ret == CFGM_SUCCESS)
		{
			/* 1.解析，修改 */
			CFGM_FILE_FUN(i)();
			LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM chg %s file success", CFGM_MCUCFG_FILENAME);
			
			/* 2.写文件 */
			ret = CfgM_WriteJFile(CFGM_MCUCFG_FILENAME, CFGM_JSON_FILE);
			if(ret == CFGM_FALSE)
				LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM Write file %s false", CFGM_MCUCFG_FILENAME);
			else
			{
			/* 3.写成功web标志为置success */
				tCfgMResp.tVdsCfgResp.McuCfgResp = CFGM_RESP_SUCCESS;
				LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM Write file %s success", CFGM_MCUCFG_FILENAME);
				SET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
			}
		}
	}
	else
		LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "CfgM  mcu Inquire cfg file fail, vds no response");
}
static void CfgM_NetCfg_Resp_Fun(int i, t_TimeOut_Type TimeOutFlag)
{
	CfgM_Resp tCfgMResp;
	GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);

	if(tCfgMResp.tNetCfgResp.NetCfgResp == CFGM_RESP_FALSE)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM Net response false");
		/* do sth */
	}
	else
	{
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CfgM Net response success");
	}
}

void CfgM_Main()
{
	SysConfigRq_all configrqdata;
	int i;
	t_CfgMRetFlag ret;
	int SignalRet;
	LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM modle start running");
	CfgM_Resp tCfgMResp;
	t_TimeOut_Type TimeoutFlag;
	while(1)
	{
		/* 1.有数据接收则处理，否则挂起 */
		GET_SIGNAL_B(PARAMETER_CFG_WEB_RQ);
		LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM get signal success");

		/* 2.获取json数据 */
		GET_JSON_STRUCT(CFGM_JSON_STRUCT, (void *)&CFGM_JSON_INFO);
		LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM get json struct success");
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "CFGM_FILE_ID %d",CFGM_FILE_ID);
		for(i = 0; i < CFGM_FILE_NUM; i++)
		{
			if(CFGM_FILE_ID ==  CFGM_FILE_INDEX(i))
			{
				/* 3.读文件 */
				/* 处理透传指令 */
				if(strcmp(CFGM_FILE_NAME(i), "NULL"))
				{
					ret = CfgM_ReadJFile(CFGM_FILE_NAME(i));
					if(ret == CFGM_FALSE)
						break;
					LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM Read File %s success", CFGM_FILE_NAME(i));

					/* 4.解析，修改 */
					CFGM_FILE_FUN(i)();
					LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM chg %s file success", CFGM_FILE_NAME(i));

					/* 5.写文件 */
					ret = CfgM_WriteJFile(CFGM_FILE_NAME(i), CFGM_JSON_FILE);
					if(ret == CFGM_FALSE)
					{
						LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM Write file %s false", CFGM_FILE_NAME(i));
						break;
					}
					LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM Write file %s success", CFGM_FILE_NAME(i));
				}
				/* basicInfo更新不需要通知相应模块 */
				if(CFGM_FILE_RESP_FUN(i) != NULL)
				{
					/* 6.填充发送结构体 */
					memset(&configrqdata,CFGM_INVALID,sizeof(SysConfigRq_all));  //初始化无效值
					switch (CFGM_FILE_INDEX(i))
					{
						case APPASCFG_FILE:
							memcpy(&configrqdata.rqdata.appcfgUpdaeNotify, &CFGM_FILE_RQ_STRUCT_VALUE(i), sizeof(configrqdata.rqdata.appcfgUpdaeNotify));
							break;
						case APPMMCFG_FILE:
							memcpy(&configrqdata.rqdata.appcfgUpdaeNotify, &CFGM_FILE_RQ_STRUCT_VALUE(i), sizeof(configrqdata.rqdata.appcfgUpdaeNotify));
							break;
						case APPMTCFG_FILE:
							memcpy(&configrqdata.rqdata.appcfgUpdaeNotify, &CFGM_FILE_RQ_STRUCT_VALUE(i), sizeof(configrqdata.rqdata.appcfgUpdaeNotify));
							break;
						case APPTLCFG_FILE:
							memcpy(&configrqdata.rqdata.appcfgUpdaeNotify, &CFGM_FILE_RQ_STRUCT_VALUE(i), sizeof(configrqdata.rqdata.appcfgUpdaeNotify));
							break;
						case V2XSERVERCFG_FILE:
							memcpy(&configrqdata.rqdata.v2xcfgUpdaeNotify, &CFGM_FILE_RQ_STRUCT_VALUE(i), sizeof(configrqdata.rqdata.vdscfgUpdaeNotify));
							break;
						case V2XPROTOCOLCFG_FILE:
							memcpy(&configrqdata.rqdata.v2xcfgUpdaeNotify, &CFGM_FILE_RQ_STRUCT_VALUE(i), sizeof(configrqdata.rqdata.vdscfgUpdaeNotify));
							break;
						case VDSCFG_FILE:
							memcpy(&configrqdata.rqdata.vdscfgUpdaeNotify, &CFGM_FILE_RQ_STRUCT_VALUE(i), sizeof(configrqdata.rqdata.vdscfgUpdaeNotify));
							break;
						case MCUCFG_FILE:
							memcpy(&configrqdata.rqdata.vdscfgUpdaeNotify, &CFGM_FILE_RQ_STRUCT_VALUE(i), sizeof(configrqdata.rqdata.vdscfgUpdaeNotify));
							break;
						case AG35CFG_FILE:
							memcpy(&configrqdata.rqdata.vdscfgUpdaeNotify, &CFGM_FILE_RQ_STRUCT_VALUE(i), sizeof(configrqdata.rqdata.vdscfgUpdaeNotify));
							break;
						case MCURQCFG_FILE:
							memcpy(&configrqdata.rqdata.vdscfgUpdaeNotify, &CFGM_FILE_RQ_STRUCT_VALUE(i), sizeof(configrqdata.rqdata.vdscfgUpdaeNotify));
							break;
						case NETCONFIG_FILE:
							memcpy(&configrqdata.rqdata.netcfgUpdaeNotify, &CFGM_FILE_RQ_STRUCT_VALUE(i), sizeof(configrqdata.rqdata.netcfgUpdaeNotify));
							break;
						default:
							LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM file index is %d error", CFGM_FILE_INDEX(i));
							break;
					}	
					/* 7.发送 */
					//MSGM_SEND_SIGNAL(&configrqdata, sizeof(SysConfigRq_all), SYS_CONFIG);
					LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM send %s update notify success", CFGM_FILE_NAME(i));

					/* 8.等待接收应答 */
					//SignalRet = GET_SIGNAL_NB(PARAMETER_CFG_SYS_RESP, 400);
					
					if(SignalRet != 0)
					{
						TimeoutFlag = TIMEOUT_VALID;					
						LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "CfgM receive %s response timeout", CFGM_FILE_NAME(i));						
					}
					else
					{
						TimeoutFlag = TIMEOUT_INVALID;	
						LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM receive %s response success", CFGM_FILE_NAME(i));
					}

					/* 9.进入应答处理函数 */
					CFGM_FILE_RESP_FUN(i)(i, TimeoutFlag);

					/* 10.通知WEB */
					if(TimeoutFlag != TIMEOUT_INVALID)
					{
						LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "CfgM notify Webserver %s require fail", CFGM_FILE_NAME(i));
						break;
					}	
					else
					{
						SET_SIGNAL_B(PARAMETER_CFG_WEB_RESP);
						LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM notify Webserver %s require finished", CFGM_FILE_NAME(i));
						break;				
					}			
				}
				else
				{
					/*BasicInfo 设置成功应答*/
					SET_SIGNAL_B(PARAMETER_CFG_WEB_RESP);
					LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "CfgM notify Webserver %s require finished", CFGM_FILE_NAME(i));				
					break;
				}
				
			}
		}
	}
}

