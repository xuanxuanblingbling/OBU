/*******************************************************************************
 * 文 件 名 称 ： net_tcp_server.cpp
 * 功 能 描 述 ： TCP Server
 * 开 发 人 员 ： GongMinghao
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2021-08-18 V1.0    GongMinghao   Create
 *
 * @Copyright (C)  2021  .wanji. all right reserved
*******************************************************************************/
#include <set>
#include <thread>
#include <chrono>
#include <iostream>
#include <signal.h>
#include <asio2/asio2.hpp>
#include "Config/cJSON.h"
#include "net_tcp_server.h"
#include "Dbus/net_data_handler.h"
#include "Dbus/dbus_data_type.h"
#include "Dbus/net_dbus.h"
#include "Config/net_log.h"

asio2::tcp_server g_server;
std::string g_netport;
uint32_t g_MaxConnet;
std::condition_variable g_SeverCV;
std::set<std::shared_ptr<asio2::tcp_session>> g_tcpinfo;


#define NET_CFG_PATH   		   "/mnt/APP/Config/obu/net/NetConfig.json"
#define NET_HOST               "0.0.0.0"
#define MR_PORT                "5555"
#define NET_PORT               g_netport

/***************************************************************** 
 * 函数名称：Cfg_ReadJson()
 * 描述：从配置文件中读TCP的配置信息
 * 函数参数：无
 * 返回结果：NET_CFGSUCCESS成功  NET_CFGFALSE失败
 * ****************************************************************/
static NetStauts_CFG Cfg_ReadJson()
{
	char *buf;
	FILE *fp;
	int  f_size, re_fread, errNum;
	cJSON *JsonFile;
	cJSON* l_object;
	cJSON* l_item;
	g_netport.clear();

	if((fp = fopen(NET_CFG_PATH, "r")) == NULL)
    {
	    errNum = errno;
		return NET_CFGFALSE;
    }
    else
    {

        fseek(fp, 0, SEEK_END);
        f_size = ftell(fp);
 		
        rewind(fp);
        buf = (char *)malloc(f_size+1);
        memset(buf, 0, f_size+1);
		re_fread = fread(buf, f_size, 1, fp);
		if(re_fread != 1)
		{
		    free(buf);
			fclose(fp);
			return NET_CFGFALSE;
		}
        fclose(fp);
    }
	
    JsonFile = cJSON_Parse(buf);
	free(buf);		
    if(NULL == JsonFile)
    {
		return NET_CFGFALSE;
	}
	else
	{
		l_object = cJSON_GetObjectItem(JsonFile, "TcpServer");
		l_item = cJSON_GetObjectItem(l_object, "ServerPort");
		NET_PORT = std::to_string(l_item->valueint);
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME,"Cfg_ReadJson NET PORT %d\n",NET_PORT);

		l_item = cJSON_GetObjectItem(l_object, "MaxConnect");
		g_MaxConnet = l_item->valueint;
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME,"Cfg_ReadJson Max Connet %d\n",g_MaxConnet);
	}
	return NET_CFGSUCCESS;
}

/***************************************************************** 
 * 函数名称：tcpServerConnect()
 * 描述：TCP Server的启动函数
 * 函数参数：无
 * 返回结果：无
 * ****************************************************************/
static void tcpServerConnect()
{
	g_server.bind_init([]()
	{
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME,"tcpServerConnect server init\n");

	}).bind_connect([&](auto& session_ptr)
	{
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME,"tcpServerConnect TCP connet success,client enter : %s %u %s %u\n",
			session_ptr->remote_address().c_str(), session_ptr->remote_port(),
			session_ptr->local_address().c_str(), session_ptr->local_port());
		//传给全局，发送使用
		g_tcpinfo.insert(session_ptr);
		session_ptr->no_delay(true);
		
		g_status.linkClientNum++;                                         //客户端个数统计
		//LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME,"tcpServerConnect linkClientNum: %d",g_status.linkClientNum);
	}).bind_recv([&](std::shared_ptr<asio2::tcp_session>& session_ptr, std::string_view data)
	{
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME,"tcpServerConnect bind_recv: %u %.*s\n",
		(unsigned)data.size(), (int)data.size(), data.data());

		std::string l_data_copy(data);
		FN_sFunRecvDatacallback((uint8_t*)l_data_copy.c_str(),data.size());//回调函数
		g_status.tcpRecvNUm +=data.size();                                 //数据接收统计
		//LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME,"linkClientNum: %d",g_status.linkClientNum);
	}).bind_disconnect([&](auto& session_ptr)
	{
		g_tcpinfo.erase(session_ptr);
		
	});

    g_server.start(NET_HOST, NET_PORT);
}

/***************************************************************** 
 * 函数名称：tcpSendAll()
 * 描述：TCP发送接口
 * 函数参数：p_data：数据 p_len：数据长度
 * 返回结果：无
 * ****************************************************************/
void tcpSendAll(const char* p_data, unsigned int p_len)
{
	if (g_tcpinfo.empty())//TCP无连接，返回
		return;
	printf("tcpSendAll Send Data is: ");
		for (uint32_t i = 0; i < p_len; i++)	
	{		printf(" %.2x",p_data[i]);	}	
	printf("\n");

	g_status.tcpSendNum += p_len;                                    //数据发送统计
	LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME,"tcpSendAll tcpSendNum:[%d] g_tcpinfo:[%d]\n：",
	g_status.tcpSendNum,g_tcpinfo.size());

	LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME,"tcpSendAll data：%d\n",p_len);
	for (auto &l_data : g_tcpinfo)
		l_data->send(p_data, p_len);                                //数据发送 
}

/***************************************************************** 
 * 函数名称：NetTcpServerThread()
 * 描述：TCP线程调用函数
 * 函数参数：无
 * 返回结果：无
 * ****************************************************************/
static void NetTcpServerThread()
{
	tcpServerConnect();
}

/***************************************************************** 
 * 函数名称：NetTcpServerInit()
 * 描述：TCP初始化函数
 * 函数参数：无
 * 返回结果：无
 * ****************************************************************/
void NetTcpServerInit(void)
{
	//初始化
	g_tcpinfo.clear();
	memset(&g_status, 0, sizeof(NetLinkStatus));
	
	if (g_server.is_started())  
		g_server.stop();

	if(Cfg_ReadJson()==NET_CFGFALSE)
		NET_PORT = MR_PORT;//失败了，就设置默认端口

	LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME,"NetTcpServerInit port：%d\n",NET_PORT);
	//创建线程
	std::thread m_netTcpServer(NetTcpServerThread);

	if (m_netTcpServer.joinable())
		m_netTcpServer.detach();
}

void RestartTcpServer()
{
	if (g_server.is_started())  
		g_server.stop();

	if(Cfg_ReadJson()==NET_CFGFALSE)
		NET_PORT = MR_PORT;//失败了，就设置默认端口

	if(g_server.is_stopped())
		g_server.start(NET_HOST,NET_PORT);
}
