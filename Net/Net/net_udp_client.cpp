/*
 * @Author: your name
 * @Date: 2021-09-24 13:39:47
 * @LastEditTime: 2021-12-02 09:50:53
 * @LastEditors: VanJee Technology Co.,Ltd
 * @Description: In User Settings Edit
 * @FilePath: /NET/Net/net_udp_client.cpp
 */
#include <set>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <signal.h>
#include <asio2/asio2.hpp>
#include <nlohmann/json.hpp>
#include "net_udp_client.h"
#include "httplib/httplib.h"
#include "Config/cJSON.h"
#include "Dbus/net_data_handler.h"
#include "Dbus/dbus_data_type.h"

#define SUB_CMD_00 0x00
#define MAIN_CMD_15 0x15

#define myFormatStringByMacro_ReturnFormatString(format, ...) \
	({                                                        \
		int size = snprintf(NULL, 0, format, ##__VA_ARGS__);  \
		size++;                                               \
		char *buf = (char *)malloc(size);                     \
		snprintf(buf, size, format, ##__VA_ARGS__);           \
		buf;                                                  \
	});

#define NET_CFG_PATH "/mnt/APP/Config/obu/net/NetConfig.json"
uint32_t LanId = 0;
uint32_t Http_Falg = 0;
static int32_t RecvManagePlatformTypeV2xmsgHandle(const char *p_pu8RecvBuf, const unsigned int p_u32RecvBufSize);

// std::string_view udp_host = "111.204.198.32";
// std::string_view udp_port = "8904";
std::string udp_host;
std::string udp_port;
int udp_client_port = 0;
asio2::udp_client g_client;
using json = nlohmann::json;
using namespace std;
#define NET_PORT udp_port
namespace jsonns
{
	struct Asset
	{
		int recordId;
		int instructionLevel;
		string msg;
		int msgType;
		int value1;
		int value2;
		int value3;
		long sendTime;
	};

	void form_json(json &j, Asset &a)
	{
		j.at("recordId").get_to(a.recordId);
		j.at("instructionLevel").get_to(a.instructionLevel);
		j.at("msg").get_to(a.msg);
		j.at("msgType").get_to(a.msgType);
		j.at("value1").get_to(a.value1);
		j.at("value2").get_to(a.value2);
		j.at("value3").get_to(a.value3);
		j.at("sendTime").get_to(a.sendTime);
	}

} // namespace jsonns
jsonns::Asset a;

/***************************************************************** 
 * 函数名称：Cfg_ReadJson()
 * 描述：从配置文件中读UDP的配置信息
 * 函数参数：无
 * 返回结果：NET_CFGSUCCESS成功  NET_CFGFALSE失败
 * ****************************************************************/
static int Cfg_ReadJson()
{
	char *buf;
	FILE *fp;
	int f_size, re_fread, errNum;
	cJSON *JsonFile;
	cJSON *l_object;
	cJSON *l_item;
	udp_port.clear();
	udp_host.clear();

	if ((fp = fopen(NET_CFG_PATH, "r")) == NULL)
	{
		errNum = errno;
		return 2;
	}
	else
	{

		fseek(fp, 0, SEEK_END);
		f_size = ftell(fp);

		rewind(fp);
		buf = (char *)malloc(f_size + 1);
		memset(buf, 0, f_size + 1);
		re_fread = fread(buf, f_size, 1, fp);
		if (re_fread != 1)
		{
			free(buf);
			fclose(fp);
			return 2;
		}
		fclose(fp);
	}

	JsonFile = cJSON_Parse(buf);
	free(buf);
	if (NULL == JsonFile)
	{
		return 2;
	}
	else
	{
		l_object = cJSON_GetObjectItem(JsonFile, "UdpServer");
		l_item = cJSON_GetObjectItem(l_object, "ServerPort");
		NET_PORT = std::to_string(l_item->valueint);
		// LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "Cfg_ReadJson NET PORT %d\n", NET_PORT);

		l_item = cJSON_GetObjectItem(l_object, "ServerIp");
		udp_host = l_item->valuestring;

		l_item = cJSON_GetObjectItem(l_object, "ClientPort");
		udp_client_port = l_item->valueint;
	}
	return 1;
}

static int32_t RecvManagePlatformTypeV2xmsgHandle(const char *p_pu8RecvBuf, const unsigned int p_u32RecvBufSize)
{
	/* 入参检查 */
	if (NULL == p_pu8RecvBuf)
	{
		printf("input is null:p_pu8RecvBuf = %s", p_pu8RecvBuf);
		return -1;
	}
	for (int i = 0; i < p_u32RecvBufSize; i++)
	{
		printf("%02x", p_pu8RecvBuf[i]);
	}
	printf("\n");
	printf("entry RecvManagePlatformTypeMapHandle");
	uint32_t l_u32i = 0;
	uint16_t data_len = 0;
	uint8_t *data_buf = NULL;

	std::vector<char> l_vdata;
	json j;
	if ((p_pu8RecvBuf[0] == 0xFF) && (p_pu8RecvBuf[1] == 0xFF) && (p_pu8RecvBuf[p_u32RecvBufSize - 1] == 0xFF))
	{
		l_u32i += 2;
		data_len = htons(*(uint16_t *)(p_pu8RecvBuf + l_u32i));
		l_u32i += 2;
		printf("data_len is %d p_u32RecvBufSize is %d\n", data_len, p_u32RecvBufSize);
		if (p_u32RecvBufSize == (data_len + 5))
		{

			data_buf = (uint8_t *)malloc(data_len);
			memcpy(data_buf, p_pu8RecvBuf + l_u32i, data_len);
			printf("****************%s\n", data_buf);
			j = json::parse(data_buf);
			jsonns::form_json(j, a);
			// std::cout << a.instructionLevel << std::endl;
			// std::cout << a.msg << std::endl;
			// std::cout << a.msgType << std::endl;
			// std::cout << a.recordId << std::endl;
			// std::cout << a.sendTime << std::endl;
			// std::cout << a.value1 << std::endl;
			// std::cout << a.value2 << std::endl;
			// std::cout << a.value2 << std::endl;
			// std::cout << a.msg.size() << std::endl;
			l_vdata.emplace_back((a.msg.length()) & 0x00ff);
			l_vdata.emplace_back(((a.msg.length()) & 0xff00) >> 16);
			l_vdata.emplace_back(a.instructionLevel);
			l_vdata.insert(l_vdata.end(), a.msg.data(), a.msg.data() + a.msg.size()); //数据透传

			Http_Falg = 1;
			if (1 == a.msgType)
			{
				LanId = g_tVehMapMatchInfo.m_LaneId;
			}
			GetAppMsgData(MAIN_CMD_15, SUB_CMD_00, (char *)&l_vdata[0], l_vdata.size() * sizeof(l_vdata[0]));
		}
		else
		{
			/* code */
		}
		if (NULL != data_buf)
			free(data_buf);
	}
	else
	{
		/* code */
	}

	return 0;
}

static void udpClientConnect()
{
	printf("udpClient Connect");
	//g_client.local_endpoint(asio::ip::address_v4::from_string("192.168.200.1"), 9876);
	g_client.local_endpoint(asio::ip::udp::v4(), udp_client_port);

	g_client.bind_connect([&](asio::error_code ec) {
				if (asio2::get_last_error())
					printf("connect failure : %d %s\n", asio2::last_error_val(), asio2::last_error_msg().c_str());
				else
					printf("connect success : %s %u\n", g_client.local_address().c_str(), g_client.local_port());
			})
		.bind_disconnect([](asio::error_code ec) {
			printf("disconnect : %d %s\n", asio2::last_error_val(), asio2::last_error_msg().c_str());
		})
		.bind_recv([&](std::string_view sv) {
			printf("recv : %u %.*s\n", (unsigned)sv.size(), (int)sv.size(), sv.data());
			RecvManagePlatformTypeV2xmsgHandle(sv.data(), sv.size());
		})
		.bind_handshake([&](asio::error_code ec) {
			if (asio2::get_last_error())
				printf("handshake failure : %d %s\n", asio2::last_error_val(), asio2::last_error_msg().c_str());
			else
				printf("handshake success : %d %s\n", asio2::last_error_val(), asio2::last_error_msg().c_str());
		});

	g_client.async_start(udp_host, udp_port);
}
static void httpClientConnect()
{
	int sec = 0;
	char des[50];
	httplib::Client cli("10.100.12.105", 8801);
	while (1)
	{
		if (1 == Http_Falg)
		{
			sec++;
			if (0 == a.msgType)
			{
				//加速
				if (0 == a.value2)
				{
					if (sec == a.value1)
					{
						if (g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_dbl_accuracy < a.value3)
						{
							std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=0", a.recordId);
							//执行失败
							auto res = cli.Get(rep_dat.data());
							if (res)
							{
								std::cout << res->status << std::endl;
								std::cout << res->get_header_value("Content-Type") << std::endl;
								std::cout << res->body << std::endl;
							}
						}
						else
						{

							std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=1", a.recordId);
							/* 执行成功 */
							auto res = cli.Get(rep_dat.data());
							if (res)
							{
								std::cout << res->status << std::endl;
								std::cout << res->get_header_value("Content-Type") << std::endl;
								std::cout << res->body << std::endl;
							}
						}
						sec = 0;
						Http_Falg = 0;
					}
				}
				else if (1 == a.value2) /*减速*/
				{
					if (sec == a.value1)
					{
						if (g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_dbl_accuracy > a.value3)
						{
							std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=0", a.recordId);
							auto res = cli.Get(rep_dat.data());
							// auto res = cli.Get("/deviceScene/updateObuSendStatus?recordId=1&executeStatus=0");
							if (res)
							{
								std::cout << res->status << std::endl;
								std::cout << res->get_header_value("Content-Type") << std::endl;
								std::cout << res->body << std::endl;
							}
							/*执行失败*/
						}
						else
						{
							std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=1", a.recordId);
							auto res = cli.Get(rep_dat.data());
							// auto res = cli.Get("/deviceScene/updateObuSendStatus?recordId=1&executeStatus=1");
							if (res)
							{
								std::cout << res->status << std::endl;
								std::cout << res->get_header_value("Content-Type") << std::endl;
								std::cout << res->body << std::endl;
							}
							/* 执行成功 */
						}
						sec = 0;
						Http_Falg = 0;
					}
				}
			}
			else if (1 == a.msgType) //变道
			{
				if (sec == a.value1)
				{
					if (0 == a.value2) //向左变道
					{
						if (g_tVehMapMatchInfo.m_LaneId < LanId)
						{
							//向左变道执行成功
							std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=1", a.recordId);
							auto res = cli.Get(rep_dat.data());
							// auto res = cli.Get("/deviceScene/updateObuSendStatus?recordId=1&executeStatus=1");
							if (res)
							{
								std::cout << res->status << std::endl;
								std::cout << res->get_header_value("Content-Type") << std::endl;
								std::cout << res->body << std::endl;
							}
						}
						else
						{
							/* 向左变道执行失败 */
							std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=0", a.recordId);
							auto res = cli.Get(rep_dat.data());
							// auto res = cli.Get("/deviceScene/updateObuSendStatus?recordId=1&executeStatus=0");
							if (res)
							{
								std::cout << res->status << std::endl;
								std::cout << res->get_header_value("Content-Type") << std::endl;
								std::cout << res->body << std::endl;
							}
						}
					}
					else if (1 == a.value2) //向右变道
					{
						if (g_tVehMapMatchInfo.m_LaneId > LanId)
						{
							//执行成功
							std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=1", a.recordId);
							auto res = cli.Get(rep_dat.data());
							// auto res = cli.Get("/deviceScene/updateObuSendStatus?recordId=1&executeStatus=1");
							if (res)
							{
								std::cout << res->status << std::endl;
								std::cout << res->get_header_value("Content-Type") << std::endl;
								std::cout << res->body << std::endl;
							}
						}
						else
						{
							//执行失败
							std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=0", a.recordId);
							auto res = cli.Get(rep_dat.data());
							// auto res = cli.Get("/deviceScene/updateObuSendStatus?recordId=1&executeStatus=0");
							if (res)
							{
								std::cout << res->status << std::endl;
								std::cout << res->get_header_value("Content-Type") << std::endl;
								std::cout << res->body << std::endl;
							}
						}
					}
					else
					{
						/* code */
					}
					sec = 0;
				}
			}
			else if (2 == a.msgType) //限制
			{
				if (sec == a.value1)
				{
					if (g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_dbl_speed <= a.value3)
					{
						//执行成功
						std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=1", a.recordId);
						auto res = cli.Get(rep_dat.data());
						// auto res = cli.Get("/deviceScene/updateObuSendStatus?recordId=1&executeStatus=1");
						if (res)
						{
							std::cout << res->status << std::endl;
							std::cout << res->get_header_value("Content-Type") << std::endl;
							std::cout << res->body << std::endl;
						}
					}
					else
					{
						/* 执行失败 */
						std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=0", a.recordId);
						auto res = cli.Get(rep_dat.data());
						// auto res = cli.Get("/deviceScene/updateObuSendStatus?recordId=1&executeStatus=0");
						if (res)
						{
							std::cout << res->status << std::endl;
							std::cout << res->get_header_value("Content-Type") << std::endl;
							std::cout << res->body << std::endl;
						}
					}
					sec = 0;
					Http_Falg = 0;
				}
			}
			else if (3 == a.msgType) //禁止变道
			{
				if (sec == a.value1)
				{
					if (g_tVehMapMatchInfo.m_LaneId != LanId)
					{
						//执行成功
						std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=1", a.recordId);
						auto res = cli.Get(rep_dat.data());
						// auto res = cli.Get("/deviceScene/updateObuSendStatus?recordId=1&executeStatus=1");
						if (res)
						{
							std::cout << res->status << std::endl;
							std::cout << res->get_header_value("Content-Type") << std::endl;
							std::cout << res->body << std::endl;
						}
					}
					else
					{
						/*执行失败*/
						std::string rep_dat = myFormatStringByMacro_ReturnFormatString("/deviceScene/updateObuSendStatus?recordId=%d&executeStatus=0", a.recordId);
						auto res = cli.Get(rep_dat.data());
						// auto res = cli.Get("/deviceScene/updateObuSendStatus?recordId=1&executeStatus=0");
						if (res)
						{
							std::cout << res->status << std::endl;
							std::cout << res->get_header_value("Content-Type") << std::endl;
							std::cout << res->body << std::endl;
						}
					}
					sec = 0;
					Http_Falg = 0;
				}
			}
			sleep(1);
		}
	}
}

void udpSend(const char *p_data, unsigned int p_len)
{
	printf("udp Send Data is: ");
	for (uint32_t i = 0; i < p_len; i++)
	{
		printf(" %x", p_data[i]);
	}
	printf("\n");
	g_client.send(p_data, p_len); //数据发送
}

static void NetHttpClientThread()
{
	httpClientConnect();
}
static void NetUdpClientThread()
{
	udpClientConnect();
}

void NetUdpClientInit(void)
{
	//初始化
	if (Cfg_ReadJson() == 2)
	{
		NET_PORT = "5555"; //失败了，就设置默认端口
		udp_host = "192.168.20.110";
	}

	// LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME,"NetTcpServerInit port：%d\n",NET_PORT);

	//创建线程
	std::thread m_netUdpClient(NetUdpClientThread);

	if (m_netUdpClient.joinable())
		m_netUdpClient.detach();
	//创建HTTP线程
	std::thread m_netHttpClient(NetHttpClientThread);
	if (m_netHttpClient.joinable())
		m_netHttpClient.detach();
}
