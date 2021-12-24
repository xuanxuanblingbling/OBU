#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "wj_log.h"
#include <dlfcn.h>
#include "dllopen.h"
#include "SecLayer.h"

#define XDJA_NEWF_DLL          1
#define XDJA_OFFLINE_DLL       2
#define IWALL_NEWF_DLL         3
#define IWALL_F_DLL            4
#define MODULE_NAME_DLL			   "Dllopen_Chip"

void *g_phDll = NULL;
#define SECLAYER_ERR(fmt, ...) printf("\033[31m[Seclayer: %s:%d:%s:%s] " #fmt "\033[0m\r\n", __func__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__)
static void *SecLoadLibrary(const char *dllName)
{
	void *pDll = NULL;
	pDll = dlopen(dllName, RTLD_NOW);
	if (pDll == NULL)
	{
		printf("--- dlopen error: %s ---\n", dlerror());
		return NULL;
	}
	return pDll;
}

static void *SecGetFunc(void *hDll, char *funcName)
{
	return dlsym(hDll, funcName);
}

static uint32_t SecDllLoad(uint32_t dllType)
{
	char	*dllName = NULL;
	void* hDll = NULL;
	char pCertPathName[256] = {0};
	switch(dllType)
	{
		case XDJA_NEWF_DLL:	
			dllName = "libxdja_newf.so";
			break;	
		case XDJA_OFFLINE_DLL:	
			dllName = "libxdja_offline.so";
			break;	
		case IWALL_F_DLL:	
			dllName = "libiwall_f.so";
			break;
		case IWALL_NEWF_DLL:	
			dllName = "libiwall_newf.so";
			break;	
		default:
			dllName = NULL;
			break;
	}
	if (dllName == NULL)
		return -1;
	strcat(strcat(pCertPathName,(const char *)s_SecInfoConfig.m_n8DllPath), (const char *)dllName);
	LogPrint(LOG_LEVEL_ERR, MODULE_NAME_DLL, "pCertPathName = %s",pCertPathName);
	SECLAYER_ERR("<<<<<<<< pCertPathName = %s ",pCertPathName);
//加载失败，有可能是加载的库不存在，也可能是加载的库的关联库不存在。
	hDll = SecLoadLibrary((const char*)pCertPathName);
	if ( hDll == NULL )
	{
		return -1;
	}	
	g_phDll = hDll;
	return 0;
}

static uint32_t SecDllUnload(void* g_phDll)
{
	if (dlclose(g_phDll))
		return -1;
	g_phDll = NULL;
	return 0;
}

static uint32_t SecFuctionLoad() 
{
	void* hDll = g_phDll;
	if (hDll == NULL)
		return -1;
	SECFUNTION.wj_SecChipFactoryCheck = (dll_SecChip_Init)SecGetFunc(hDll, "SecChipFactoryCheck");
	SECFUNTION.wj_SecChip_Init = (dll_SecChip_Init)SecGetFunc(hDll, "SecChip_Init");
	SECFUNTION.wj_SecDataSign_RSU = (dll_SecDataSign_RSU)SecGetFunc(hDll, "SecDataSign_RSU");
	SECFUNTION.wj_SecDataSign_OBU = (dll_SecDataSign_OBU)SecGetFunc(hDll, "SecDataSign_OBU");
	SECFUNTION.wj_SecDataVerify = (dll_SecDataVerify)SecGetFunc(hDll, "SecDataVerify");
	SECFUNTION.wj_SecChipDeinit = (dll_SecChipDeinit)SecGetFunc(hDll, "SecChipDeinit");
	return 0;
}

static void SecFuctionUnload()
{
	SECFUNTION.wj_SecChipFactoryCheck =0;
	SECFUNTION.wj_SecChip_Init = 0;
	SECFUNTION.wj_SecDataSign_RSU = 0;
	SECFUNTION.wj_SecDataSign_OBU = 0;
	SECFUNTION.wj_SecDataVerify = 0;
	SECFUNTION.wj_SecChipDeinit = 0;
	return;
}

uint32_t FindChip(uint32_t dllType)
{
	uint32_t mRv = 0;
	mRv = SecDllLoad(dllType);
	if(mRv != 0)
	{
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME_DLL, "SecDllLoad, error");
		SECLAYER_ERR("<<<<<<<< SecDllLoad , error");
		return -1;
	}
	else
	{
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME_DLL, "SecDllLoad  success");
		SECLAYER_ERR("<<<<<<<< SecDllLoad  success");
	}
	mRv = SecFuctionLoad();
	if(mRv != 0)
	{
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME_DLL, "SecFuctionLoad error ");
		SECLAYER_ERR("SecFuctionLoad error");
		return -1;
	}
	mRv = SECFUNTION.wj_SecChipFactoryCheck();
	if(mRv != 0)
	{
		dllOpenDeinit();
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME_DLL, "Chip not find ,go to next");
		SECLAYER_ERR("Chip not find, go to next");
	}
	else
	{
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME_DLL, "Chip find");
		SECLAYER_ERR("Chip find");
		return 0;
	}
} 
#define CHIPFACTORY_NUM 2
uint32_t dllOpenInit(int32_t ProtocolType, int32_t ChipType, const char *FileName) 
{

	uint32_t mRv = 0;
	uint32_t dllType = 0;
	if(3 == ChipType) //信大离线SDK 
	{
		goto XDJAOFF;
	}
XDJA:
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME_DLL, "load libxdja_newf.so begain ");
	SECLAYER_ERR("<<<<<<<< load libxdja_newf.so begain");
	dllType = XDJA_NEWF_DLL;
	mRv = FindChip(dllType);
	if(mRv == 0)
	{
		LogPrint(LOG_LEVEL_INFO, MODULE_NAME_DLL, "load libxdja_newf.so success");
		SECLAYER_ERR("<<<<<<<< load libxdja_newf.so success");
		s_SecInfoConfig.m_n32Manufacture = 1;
		goto EXIT;
		// break;
	}
	else
	{
		dllOpenDeinit();
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME_DLL, "load libxdja_newf.so error,go to load iwall");
		SECLAYER_ERR("<<<<<<<< load libxdja_newf.so error,go to load iwall");
		// ChipType = 2;
	}		
IWALL:
	if(4 == ProtocolType)
	{
		dllType = IWALL_F_DLL;
		LogPrint(LOG_LEVEL_INFO, MODULE_NAME_DLL, "load libiwall_f.so begain");
		SECLAYER_ERR("<<<<<<<< load libiwall_f.so begain");
	}
	if(5 == ProtocolType || 2 == ProtocolType)
	{
		dllType = IWALL_NEWF_DLL;
		LogPrint(LOG_LEVEL_INFO, MODULE_NAME_DLL, "load libiwall_newf.so begain");
		SECLAYER_ERR("<<<<<<<< load libiwall_newf.so begain");
	}
	mRv = FindChip(dllType);
	printf("after findchio\n");
	if(mRv == 0)
	{
		LogPrint(LOG_LEVEL_INFO, MODULE_NAME_DLL, "load iwall success");
		SECLAYER_ERR("<<<<<<<< load iwall success");
		s_SecInfoConfig.m_n32Manufacture = 2;
		goto EXIT;
		// break;
	}
	else
	{
		dllOpenDeinit();
		LogPrint(LOG_LEVEL_INFO, MODULE_NAME_DLL, "load iwall error");
		SECLAYER_ERR("<<<<<<<< load iwall error");
		ChipType = 1;
	}	

XDJAOFF:
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME_DLL, "load libxdja_offline.so begain");
	SECLAYER_ERR("<<<<<<<< load libxdja_offline.so begain");
	dllType = XDJA_OFFLINE_DLL;
	mRv = FindChip(dllType);
	if(mRv == 0)
	{
		LogPrint(LOG_LEVEL_INFO, MODULE_NAME_DLL, "load libxdja_offline success");
		SECLAYER_ERR("<<<<<<<< load libxdja_offline success");
		s_SecInfoConfig.m_n32Manufacture = 3;
		goto EXIT;
	}
	else
	{
		dllOpenDeinit();
		LogPrint(LOG_LEVEL_INFO, MODULE_NAME_DLL, "load libxdja_offline error");
		SECLAYER_ERR("<<<<<<<< load libxdja_offline error");
		goto ERROR;
	}
	
EXIT:
	SecWritePrivateProfileInt("SecurityParamConfig", "EncryptChipType", s_SecInfoConfig.m_n32Manufacture, FileName);
	return 0;
ERROR:
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME_DLL, "Not find any chip");
	SECLAYER_ERR("<<<<<<<< Not find any chip");
	return -1; // 0 for not be killed
}

uint32_t dllOpenDeinit() 
{
	uint32_t mRv = 0;
	if(NULL != g_phDll)
	{
		mRv = SecDllUnload(g_phDll);
		if(mRv != 0)
		{
			LogPrint(LOG_LEVEL_ERR, MODULE_NAME_DLL, "SecDllUnload error");
			return -1;
		}
	}
	SecFuctionUnload();
	return 0;
}

