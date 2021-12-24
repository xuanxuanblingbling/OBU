/*******************************************************************************
 * 文 件 名 称 ： net_data_send.cpp
 * 功 能 描 述 ： 数据发送模块
 * 开 发 人 员 ： GongMinghao
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2021-08-18 V1.0    GongMinghao   Create
 *
 * @Copyright (C)  2021  .wanji. all right reserved
*******************************************************************************/
#include <iostream>
#include <signal.h>
#include <condition_variable>
#include "net_data_send.h"
#include "net_tcp_server.h"
#include "net_udp_client.h"
#include <asio2/asio2.hpp>
#include <atomic>
#include <deque>
#include "TongZhou/inc/app_lst.h"

uint8_t g_nIndex;
std::mutex g_AppMsgMutex;
std::deque<AppMsgData> g_ListAppMsg;
std::condition_variable g_vNetSendConVar;
std::atomic_bool g_flag = true;

std::mutex g_SecMsgMutex;
std::deque<V2xPlatformSceneWarn> g_ListV2xPlatformSceneWarn;
std::condition_variable g_vNetSecConVar;
std::atomic_bool g_Sec_flag = true;

/***************************************************************** 
 * 函数名称：SendAppMsgData()
 * 描述：发送组帧接口
 * 函数参数：p_mainCmd：p_subCmd：p_data：数据：p_len：数据长度
 * 返回结果：NET_CFGSUCCESS成功  NET_CFGFALSE失败
 * ****************************************************************/
void SendAppMsgData(char p_mainCmd, char p_subCmd, const char *p_data, uint32_t p_len)
{
	std::vector<char> l_vdata;
	std::vector<char> l_vdata1;
	std::vector<char> l_vdata2;
	std::vector<char> l_vdata3;
	std::vector<char> l_vdata4;
	std::vector<char> l_vdata5;
	uint8_t m_int_CurrentGpsState = 0;
	switch (g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_int_CurrentGpsState)
	{
	case 0x00:
		m_int_CurrentGpsState = 0;
		break;
	case 0x10:
		m_int_CurrentGpsState = 1;
		break;
	case 0x20:
		m_int_CurrentGpsState = 2;
		break;
	case 0x50:
		m_int_CurrentGpsState = 5;
		break;
	case 0x60:
		m_int_CurrentGpsState = 4;
		break;
	case 0x80:
		m_int_CurrentGpsState = 10;
		break;
	}
	// uint8_t m_int_CurrentGpsState = g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_int_CurrentGpsState;
	if (p_mainCmd == 0x10)
	{
		l_vdata.emplace_back(0xFF);
		l_vdata.emplace_back(0xFF);		  //FF FF 帧开始位
		l_vdata.emplace_back(g_nIndex++); //帧序号
		g_nIndex &= 0x0F;
		l_vdata.emplace_back(p_mainCmd); //帧主命令
		l_vdata.emplace_back(p_subCmd);	 //帧子命令
		l_vdata.emplace_back(0x00);		 //状态位
		uint32_t l_u32i = 0;
		uint16_t len = (*(uint16_t *)(p_data + l_u32i));
		l_u32i = l_u32i + 2;
		l_vdata.emplace_back(((len + 1 + 8) & 0x00ff));
		l_vdata.emplace_back(((len + 1 + 8) & 0xff00) >> 16);
		// l_vdata.emplace_back(((len + 1) & 0x00ff));
		// l_vdata.emplace_back(((len + 1) & 0xff00) >> 16);
		struct timeval l_ttimevall;
		gettimeofday(&l_ttimevall, NULL);
		uint64_t Time = (l_ttimevall.tv_sec * 1000000LL + l_ttimevall.tv_usec) / 1000;
		l_vdata.emplace_back((Time & 0x00000000000000ff));
		l_vdata.emplace_back((Time & 0x000000000000ff00) >> 16);
		l_vdata.emplace_back((Time & 0x0000000000ff0000) >> 24);
		l_vdata.emplace_back((Time & 0x00000000ff000000) >> 32);
		l_vdata.emplace_back((Time & 0x000000ff00000000) >> 40);
		l_vdata.emplace_back((Time & 0x0000ff0000000000) >> 48);
		l_vdata.emplace_back((Time & 0x00ff000000000000) >> 56);
		l_vdata.emplace_back((Time & 0xff00000000000000) >> 64);

		l_vdata.emplace_back(m_int_CurrentGpsState);
		l_vdata.insert(l_vdata.end(), p_data + l_u32i, p_data + p_len); //数据透传
		l_vdata.emplace_back(0x00);										//奇偶校验位置空
		l_vdata.emplace_back(0xFF);										//帧结束位
		tcpSendAll(&l_vdata[0], l_vdata.size() * sizeof(l_vdata[0]));
		if ((p_mainCmd == 0x10))
		{
			udpSend(&l_vdata[0], l_vdata.size() * sizeof(l_vdata[0]));
		}
	}
	else if ((p_mainCmd == 0x11) || (p_mainCmd == 0x12) || (p_mainCmd == 0x14) || (p_mainCmd == 0x13) || (p_mainCmd == 0x19))
	{
		l_vdata4.emplace_back(0xFF);
		l_vdata4.emplace_back(0xFF);	   //FF FF 帧开始位
		l_vdata4.emplace_back(g_nIndex++); //帧序号
		g_nIndex &= 0x0F;
		l_vdata4.emplace_back(p_mainCmd);						 //帧主命令
		l_vdata4.emplace_back(p_subCmd);						 //帧子命令
		l_vdata4.emplace_back(0x00);							 //状态位
		l_vdata4.insert(l_vdata4.end(), p_data, p_data + p_len); //数据透传
		l_vdata4.emplace_back(0x00);							 //奇偶校验位置空
		l_vdata4.emplace_back(0xFF);							 //帧结束位
		tcpSendAll(&l_vdata4[0], l_vdata4.size() * sizeof(l_vdata4[0]));
	}
	else
	{
		/* code */
	}

	if (p_mainCmd == 0x12)
	{
		l_vdata2.emplace_back(0xFF);
		l_vdata2.emplace_back(0xFF);	   //FF FF 帧开始位
		l_vdata2.emplace_back(g_nIndex++); //帧序号
		g_nIndex &= 0x0F;
		l_vdata2.emplace_back(p_mainCmd);																						   //帧主命令
		l_vdata2.emplace_back(p_subCmd);																						   //帧子命令
		l_vdata2.emplace_back(0x00);																							   //状态位
		l_vdata2.insert(l_vdata2.end(), &g_tDbusVehDataFrame.m_MsgData.m_vehId[9], &g_tDbusVehDataFrame.m_MsgData.m_vehId[9] + 8); //UEID
		l_vdata2.insert(l_vdata2.end(), p_data, p_data + p_len);																   //数据透传
		l_vdata2.emplace_back(0x00);																							   //奇偶校验位置空
		l_vdata2.emplace_back(0xFF);																							   //帧结束位
		udpSend(&l_vdata2[0], l_vdata2.size() * sizeof(l_vdata2[0]));
	}
	if (p_mainCmd == 0x19)
	{
		l_vdata3.emplace_back(0xFF);
		l_vdata3.emplace_back(0xFF);	   //FF FF 帧开始位
		l_vdata3.emplace_back(g_nIndex++); //帧序号
		g_nIndex &= 0x0F;
		l_vdata3.emplace_back(p_mainCmd);																						   //帧主命令
		l_vdata3.emplace_back(p_subCmd);																						   //帧子命令
		l_vdata3.emplace_back(0x00);																							   //状态位
		l_vdata3.insert(l_vdata3.end(), &g_tDbusVehDataFrame.m_MsgData.m_vehId[9], &g_tDbusVehDataFrame.m_MsgData.m_vehId[9] + 8); //UEID
		l_vdata3.insert(l_vdata3.end(), p_data, p_data + p_len);																   //数据透传
		l_vdata3.emplace_back(0x00);																							   //奇偶校验位置空
		l_vdata3.emplace_back(0xFF);																							   //帧结束位
		udpSend(&l_vdata3[0], l_vdata3.size() * sizeof(l_vdata3[0]));
	}
	// if (p_mainCmd == 0x15)
	// {
	// 	l_vdata3.emplace_back(0xFF);
	// 	l_vdata3.emplace_back(0xFF);	   //FF FF 帧开始位
	// 	l_vdata3.emplace_back(g_nIndex++); //帧序号
	// 	g_nIndex &= 0x0F;
	// 	l_vdata3.emplace_back(p_mainCmd); //帧主命令
	// 	l_vdata3.emplace_back(p_subCmd);  //帧子命令
	// 	l_vdata3.emplace_back(0x00);	  //状态位
	// 	l_vdata3.emplace_back((p_len)&0x00ff);
	// 	l_vdata3.emplace_back(((p_len)&0xff00) >> 16);
	// 	l_vdata3.insert(l_vdata3.end(), p_data, p_data + p_len); //数据透传
	// 	l_vdata3.emplace_back(0x00);							 //奇偶校验位置空
	// 	l_vdata3.emplace_back(0xFF);							 //帧结束位
	// 	tcpSendAll(&l_vdata3[0], l_vdata3.size() * sizeof(l_vdata3[0]));
	// }
}

/***************************************************************** 
 * 函数名称：ScenSendThread()
 * 描述：千寻场景数据发送线程
 * 函数参数：无
 * 返回结果：无
 * ****************************************************************/
void ScenSendThread(void) //消费者模式
{
	size_t l_MsgNum = 0;
	V2xPlatformSceneWarn l_v2xplatformscenewarn;
	while (g_Sec_flag)
	{

		std::unique_lock<std::mutex> l_lck(g_SecMsgMutex);

		//如果条件变量被唤醒，检查队列非空条件是否为真，为真则直接返回，为假则继续等待
		g_vNetSecConVar.wait(l_lck, []() { return !g_ListV2xPlatformSceneWarn.empty(); });
		printf("g_ListV2xPlatformSceneWarn.size() is %d\n", g_ListV2xPlatformSceneWarn.size());
		l_v2xplatformscenewarn = g_ListV2xPlatformSceneWarn.front();

		g_ListV2xPlatformSceneWarn.pop_front(); //数据出队锁保护
		// g_ListV2xPlatformSceneWarn.clear();
		l_lck.unlock();

		printf("l_v2xplatformscenewarn.type is %d\n", l_v2xplatformscenewarn.type);
		SendSecMsgData(l_v2xplatformscenewarn);
		l_MsgNum--;
	}
}
/***************************************************************** 
 * 函数名称：NetSendThread()
 * 描述：数据发送线程
 * 函数参数：无
 * 返回结果：无
 * ****************************************************************/
void NetSendThread(void) //消费者模式
{
	size_t l_MsgNum = 0;
	AppMsgData l_appMsg;
	while (g_flag)
	{
		std::unique_lock<std::mutex> l_lck(g_AppMsgMutex);
		//如果条件变量被唤醒，检查队列非空条件是否为真，为真则直接返回，为假则继续等待
		g_vNetSendConVar.wait(l_lck, []() { return !g_ListAppMsg.empty(); });

		l_appMsg = g_ListAppMsg.front();
		g_ListAppMsg.pop_front(); //数据出队锁保护
		l_lck.unlock();

		SendAppMsgData(l_appMsg.m_mainCmd, l_appMsg.m_subCmd, l_appMsg.m_data, l_appMsg.m_len);
		delete l_appMsg.m_data;
		l_MsgNum--;
	}
}

/***************************************************************** 
 * 函数名称：NetDataSendInit()
 * 描述：数据发送初始化函数
 * 函数参数：无
 * 返回结果：无
 * ****************************************************************/
void NetDataSendInit(void)
{
	//初始化
	g_ListAppMsg.clear();

	//创建线程
	std::thread m_netDataSend(NetSendThread);

	if (m_netDataSend.joinable())
		m_netDataSend.detach();
	//创建QX场景上报线程
	std::thread m_SecDataSend(ScenSendThread);

	if (m_SecDataSend.joinable())
		m_SecDataSend.detach();
}
