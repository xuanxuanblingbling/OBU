/*
 * V2X_INTERFACE.c
 *
 *  Created on: May 9, 2018
 *      Author: root
 */
extern "C"
{
#include "V2XInterface.h"
}
#include <string>
#include <dlfcn.h>
using namespace std;

typedef int (*dll_LTEV2X_TxRxInit)(pFunRecvData MsgRx_CallBack);
typedef int (*dll_LTEV2X_SendData)(SendDataInfo ag15SendDataInfo, SendDataReturnInfo *ag15SendDataReturnInfo);
typedef int (*dll_LTEV2X_Close)();
typedef float (*dll_LTEV2X_GetCBR)();
typedef struct dlopen_so
{
	void *pDll;
	dll_LTEV2X_TxRxInit wj_LTEV2X_TxRxInit;
	dll_LTEV2X_SendData wj_LTEV2X_SendData;
	dll_LTEV2X_Close wj_LTEV2X_Close;
	dll_LTEV2X_GetCBR wj_LTEV2X_GetCBR;
	string AG15_SO;
	string CX7100_SO;
	string DT_SO;
	string LTEV2X_TxRxInit;
	string LTEV2X_SendData;
	string LTEV2X_Close;
	string LTEV2X_GetCBR;
} dlopen_so_t;

static dlopen_so_t g_dlopen_so = {
	.pDll = NULL,
	.wj_LTEV2X_TxRxInit = NULL,
	.wj_LTEV2X_SendData = NULL,
	.wj_LTEV2X_Close = NULL,
	.wj_LTEV2X_GetCBR = NULL,
	.AG15_SO = "libv2xAG15.so",
	.CX7100_SO = "libv2xCX7100.so",
	.DT_SO = "libv2xDMD3A.so",
	.LTEV2X_TxRxInit = "V2X_TxRx_Init",
	.LTEV2X_SendData = "V2X_SendData",
	.LTEV2X_Close = "V2X_Close",
	.LTEV2X_GetCBR = "V2X_GetCBR"};

static int V2XDllOpen(string soName)
{
	g_dlopen_so.pDll = dlopen((char *)soName.c_str(), RTLD_NOW);
	if (g_dlopen_so.pDll == NULL)
	{
		printf("%s %d --- dlopen error: %s ---\n", __FUNCTION__, __LINE__, dlerror());
		return -1;
	}

	g_dlopen_so.wj_LTEV2X_TxRxInit = (dll_LTEV2X_TxRxInit)dlsym(g_dlopen_so.pDll,
																(char *)g_dlopen_so.LTEV2X_TxRxInit.c_str());
	g_dlopen_so.wj_LTEV2X_SendData = (dll_LTEV2X_SendData)dlsym(g_dlopen_so.pDll,
																(char *)g_dlopen_so.LTEV2X_SendData.c_str());
	g_dlopen_so.wj_LTEV2X_Close = (dll_LTEV2X_Close)dlsym(g_dlopen_so.pDll,
														  (char *)g_dlopen_so.LTEV2X_Close.c_str());
	g_dlopen_so.wj_LTEV2X_GetCBR = (dll_LTEV2X_GetCBR)dlsym(g_dlopen_so.pDll,
															(char *)g_dlopen_so.LTEV2X_GetCBR.c_str());

	if (g_dlopen_so.wj_LTEV2X_TxRxInit == NULL ||
		g_dlopen_so.wj_LTEV2X_SendData == NULL ||
		g_dlopen_so.wj_LTEV2X_Close == NULL ||
		g_dlopen_so.wj_LTEV2X_GetCBR == NULL)
	{
		printf("%s %d --- dlopen error: %s ---\n", __FUNCTION__, __LINE__, dlerror());
		return -1;
	}
	printf("%s %d --- dlopen success: %s ---\n", __FUNCTION__, __LINE__, soName.c_str());
	return 0;
}

static int V2XDllLoad(int mode)
{
	int ret = 0;
	switch (mode)
	{
	case MODE_LTEV_AG15:
		ret = V2XDllOpen(g_dlopen_so.AG15_SO);
		break;
	case MODE_LTEV_CX7100:
		ret = V2XDllOpen(g_dlopen_so.CX7100_SO);
		break;
	case MODE_LTEV_DMD3A:
		ret = V2XDllOpen(g_dlopen_so.DT_SO);
		break;
	default:
		return -1;
		break;
	}
	return ret;
}

static int V2XDllUnload()
{
	if (g_dlopen_so.pDll != NULL)
	{
		dlclose(g_dlopen_so.pDll);
		g_dlopen_so.pDll = NULL;
	}
	g_dlopen_so.wj_LTEV2X_TxRxInit = NULL;
	g_dlopen_so.wj_LTEV2X_SendData = NULL;
	g_dlopen_so.wj_LTEV2X_Close = NULL;
	g_dlopen_so.wj_LTEV2X_GetCBR = NULL;
	return 0;
}

static int V2XFindDifferences()
{

	//if (0 == system("ifconfig | grep rmnet_usb0"))
	if (0 == system("cv2x-config --get-v2x-status | grep rx_status"))
	{
		printf("%s %d --- To prepare dlopen: %s ---\n", __FUNCTION__, __LINE__, g_dlopen_so.AG15_SO.c_str());
		return MODE_LTEV_AG15;
	}
	else if (0 == system("ifconfig | grep lmi40") ||
			 0 == system("ifconfig | grep rmnet_usb0"))
	{
		printf("%s %d --- To prepare dlopen: %s ---\n", __FUNCTION__, __LINE__, g_dlopen_so.CX7100_SO.c_str());
		return MODE_LTEV_CX7100;
	}
	else if (0 == system("ifconfig | grep DT"))
	{
		printf("%s %d --- To prepare dlopen: %s ---\n", __FUNCTION__, __LINE__, g_dlopen_so.DT_SO.c_str());
		return MODE_LTEV_DMD3A;
	}

	printf("%s %d --- Not find ifconfig\n", __FUNCTION__, __LINE__);
	return 0;

	// std::string cmd = "ifconfig";
	// FILE *fp = popen(cmd.c_str(), "r");
	// if (fp == NULL)
	// {
	// 	return 0;
	// }

	// char buffer[4096] = {0};
	// fread(buffer, sizeof(char), 4096, fp);
	// pclose(fp);

	// //parse string
	// std::string str = buffer;
	// std::size_t findAg15 = str.find("rmnet_usb0");
	// std::size_t findCx7100 = str.find("lmi40");
	// std::size_t findDT = str.find("DT");
	// if (findAg15 != std::string::npos)
	// {
	// 	printf("%s %d --- To prepare dlopen: %s ---\n", __FUNCTION__, __LINE__, g_dlopen_so.AG15_SO.c_str());
	// 	return MODE_LTEV_AG15;
	// }
	// else if (findCx7100 != std::string::npos)
	// {
	// 	printf("%s %d --- To prepare dlopen: %s ---\n", __FUNCTION__, __LINE__, g_dlopen_so.CX7100_SO.c_str());
	// 	return MODE_LTEV_CX7100;
	// }
	// else if (findDT != std::string::npos)
	// {
	// 	printf("%s %d --- To prepare dlopen: %s ---\n", __FUNCTION__, __LINE__, g_dlopen_so.DT_SO.c_str());
	// 	return MODE_LTEV_DMD3A;
	// }

	// printf("%s %d --- Not find ifconfig\n", __FUNCTION__, __LINE__);
	// return 0;
}

/************************************************************************
 * 初始化V2X通讯_发送模块
 * 函数名称：int V2X_Tx_Init()
 * 函数功能：初始化V2X通讯
 * 参数说明：无
 * 函数返回值：执行状态，0 执行成功，非0 执行失败
 ************************************************************************/
DLL_PUBLIC int V2X_TxRx_Init(pFunRecvData MsgRx_CallBack)
{
	printf("----------------V2X_TxRx_Init-----------------\n");
	//判断模组，暂时通过网卡信息寻找差异性
	int ModeFlag = V2XFindDifferences();
	//加载so
	int ret = V2XDllLoad(ModeFlag);
	if (ret == 0)
	{
		if (g_dlopen_so.wj_LTEV2X_TxRxInit != NULL)
			ret = g_dlopen_so.wj_LTEV2X_TxRxInit(MsgRx_CallBack);
	}
	else
	{
		V2XDllUnload();
	}

	return ret;
}

/*********************************************************************
 * 发送指定数据
 * 函数名称：int V2X_SendData(AG15SendDataInfo ag15SendDataInfo)
 * 函数功能：将指定的数据按照当前的发送参数发送出去
 * 参数说明：AG15SendDataInfo ag15SendDataInfo 发送数据结构体
 * 函数返回值：>0 成功发送数据的长度（字节数） <0 表示发送失败，返回结果代表错误类型
 *********************************************************************/
DLL_PUBLIC int V2X_SendData(SendDataInfo ag15SendDataInfo, SendDataReturnInfo *ag15SendDataReturnInfo)
{
	int nRet = 0;

	if (g_dlopen_so.wj_LTEV2X_SendData != NULL)
		nRet = g_dlopen_so.wj_LTEV2X_SendData(ag15SendDataInfo, ag15SendDataReturnInfo);

	return nRet;
}
/************************************************************************
 * 停止接收数据
 * 函数名称：int V2X_Close();
 * 函数功能：关闭V2X通讯
 * 参数说明：无
 * 函数返回值：执行状态，0 执行成功，非0 执行失败
 ************************************************************************/
DLL_PUBLIC int V2X_Close()
{
	if (g_dlopen_so.wj_LTEV2X_Close != NULL)
		g_dlopen_so.wj_LTEV2X_Close();

	V2XDllUnload();
	return 0;
}

/**
 * @brief 实时获取CBR（信道忙率）
 *
 * 实时获取CBR（信道忙率）
 *
 * @param 无
 *
 * @return 执行状态，0 执行成功，非0 执行失败
 */
DLL_PUBLIC float V2X_GetCBR()
{
	if (g_dlopen_so.wj_LTEV2X_GetCBR != NULL)
		return g_dlopen_so.wj_LTEV2X_GetCBR();
}