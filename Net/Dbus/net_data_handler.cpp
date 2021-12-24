
#include <stdio.h>
#include <vector>
#include <set>
#include <list>
#include <cstring>
#include "net_data_can.h"
#include "net_data_handler.h"
#include "dbus_data_type.h"
#include "Net/net_data_send.h"
#include "Net/net_tcp_server.h"
#include "Config/Net_Json.h"
#include "Config/net_log.h"

#define OFFSET(structure, member) ((int64_t) & ((structure *)0)->member)
std::mutex l_mtx;
/***************************************************************** 
 * 函数名称：DBUS_CaluBcc()
 * 描述：BCC校验函数
 * 函数参数：p_ptValue：数据 p_length：长度
 * 返回结果：无
 * ****************************************************************/
uint8_t DBUS_CaluBcc(void *p_ptValue, uint32_t p_length)
{
	uint8_t *l_bcc, bcc = 0;
	l_bcc = (uint8_t *)p_ptValue;
	for (uint32_t cnt = 0; cnt < p_length; cnt++)
	{
		bcc ^= *l_bcc++;
	}
	return bcc;
}

/***************************************************************** 
 * 函数名称：GetAppMsgData()
 * 描述：APP算法数据处理及存入队列函数
 * 函数参数：
 * 返回结果：无
 * ****************************************************************/
void GetAppMsgData(char p_mainCmd, char p_subCmd, const char *p_data, uint32_t p_len) //生产者模式
{
	AppMsgData l_msgData;
	if (p_mainCmd == 0x10) // BSM 协议转换
	{
		ResultActSafe *l_VehData = (ResultActSafe *)p_data;
		uint64_t p_num1 = 0;
		uint8_t l_tFlag = (l_VehData->upLoadID) & 0x02;
		if (l_VehData->nAdveCnt > MAX_ADVE_VEH_NUM)
			return;
		printf("l_VehData->upLoadID is %d\n", l_VehData->upLoadID);
		if (l_tFlag) // 有危险车
			p_num1 = OFFSET(ResultActSafe, aAdveVeh) - 2;
		else
			p_num1 = OFFSET(ResultActSafe, dangerAdveUEID);

		p_len = p_num1 + uint32_t(l_VehData->nAdveCnt) * 18;

		l_VehData->LENGTH = p_len - 2;
		l_msgData.m_data = (char *)malloc(p_len);
		if (l_msgData.m_data == NULL)
			return;
		if (l_tFlag)
		{
			memcpy(l_msgData.m_data, &(l_VehData->LENGTH), p_num1);
		}
		else
		{
			p_num1 -= 2;
			memcpy(l_msgData.m_data, &(l_VehData->LENGTH), p_num1);
			memcpy(l_msgData.m_data + p_num1, &(l_VehData->nAdveCnt), 2);
			p_num1 += 2;
		}

		for (uint8_t k = 0; k < l_VehData->nAdveCnt; ++k)
		{
			memcpy((l_msgData.m_data + p_num1), &(l_VehData->aAdveVeh[k]), 18);
			p_num1 += 18;
		}
	}
	else
	{
		l_msgData.m_data = (char *)malloc(p_len);
		if (l_msgData.m_data == NULL)
			return;
		memcpy(l_msgData.m_data, p_data, p_len);
	}
	if (p_mainCmd == 0x19)
	{
		RoadsideCoordination_t *l_roadsideCoordination = (RoadsideCoordination_t *)p_data;
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "l_roadsideCoordination.planpathpoints is %d", l_roadsideCoordination->planpathpoints);
		uint64_t p_num = 0;
		p_num = OFFSET(RoadsideCoordination_t, planpathpoint) - 2;
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "p_num1 is %d", p_num);
		p_len = p_num + uint32_t(l_roadsideCoordination->planpathpoints) * 8;
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "p_len is %d", p_len);
		l_roadsideCoordination->m_MsgLength = p_len - 2;
		l_msgData.m_data = (char *)malloc(p_len);
		if (l_msgData.m_data == NULL)
			return;
		p_num -= 1;
		memcpy(l_msgData.m_data, &(l_roadsideCoordination->m_MsgLength), p_num);
		memcpy(l_msgData.m_data + p_num, &(l_roadsideCoordination->planpathpoints), 1);
		p_num += 1;
		for (uint8_t i = 0; i < l_roadsideCoordination->planpathpoints; ++i)
		{
			memcpy((l_msgData.m_data + p_num), &(l_roadsideCoordination->planpathpoint[i]), 8);
			p_num += 8;
		}
	}
	l_msgData.m_mainCmd = p_mainCmd;
	l_msgData.m_subCmd = p_subCmd;
	l_msgData.m_len = p_len;
	std::unique_lock<std::mutex> l_ck(g_AppMsgMutex);
	g_ListAppMsg.emplace_back(l_msgData); //数据入队锁保护
	l_ck.unlock();
	g_vNetSendConVar.notify_one(); //向一个等待线程发出“条件已满足”的通知
}
/***************************************************************** 
 * 函数名称：GetAppScenMsgData()
 * 描述：APP算法数据处理及存入队列函数
 * 函数参数：
 * 返回结果：无
 * ****************************************************************/
void GetAppScenMsgData(V2xPlatformSceneWarn v2xplatformscenewarn) //生产者模式
{
	LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "GetAppScenMsgData");
	std::unique_lock<std::mutex> l_ck(g_SecMsgMutex);
	g_ListV2xPlatformSceneWarn.emplace_back(v2xplatformscenewarn); //数据入队锁保护
	l_ck.unlock();
	g_vNetSecConVar.notify_one(); //向一个等待线程发出“条件已满足”的通知
}

/***************************************************************** 
 * 函数名称：init_F2()
 * 描述：F2帧初始化函数
 * 函数参数：无
 * 返回结果：F2帧数据
 * ****************************************************************/
F2 init_F2()
{
	F2 l_veh;
	l_veh.frameHead = 0xFFFF;
	l_veh.frameNum = 0x01;
	l_veh.frameCMDT = 0xF2;
	l_veh.framSubCDMT = 0x00;
	l_veh.frameStatus = 0x01;
	l_veh.frameLen = 0x2F;
	l_veh.blockState = 0x00;
	l_veh.canFlag = 0x00;
	l_veh.speed = 0x00;
	l_veh.wheelTurn = 0x00;
	l_veh.exteriorLights = 0x00;
	l_veh.brakePedalStatus = 0x01;
	l_veh.tractionControlSystem = 0x00;
	l_veh.tractionControlStatus = 0x00;
	l_veh.AntilockbrakeSystem = 0x00;
	l_veh.bodyStabilitySystem = 0x00;
	l_veh.brakeAssistSystem = 0x00;
	l_veh.auxiliaryBrakeSystem = 0x01;
	l_veh.basicVehicleClass = 0x3b;
	l_veh.check = 0x00;
	l_veh.end = 0xFF;
	return l_veh;
}

F5 init_F5()
{
	F5 l_ramp_into;
	l_ramp_into.frameHead = 0xFFFF;
	l_ramp_into.frameNum = 0x01;
	l_ramp_into.frameCMDT = 0xF5;
	l_ramp_into.framSubCDMT = 0x00;
	l_ramp_into.frameStatus = 0x01;
	l_ramp_into.frameLen = 0x11;
	l_ramp_into.request_status = 0x00;
	l_ramp_into.driving_status = 0x0000;
	l_ramp_into.driving_request = 0x00;
	l_ramp_into.request_target = 0x00;
	memset(l_ramp_into.device_id, 0x00, 8);
	l_ramp_into.request_start_time = 0x00000000;
	l_ramp_into.request_end_time = 0x00000000;
	l_ramp_into.check = 0x00;
	l_ramp_into.end = 0xFF;
	return l_ramp_into;
}
/***************************************************************** 
 * 函数名称：FN_sendStatus(uint32_t p_sig)
 * 描述：状态发送函数
 * 函数参数：p_sig：状态位
 * 返回结果：Can数据状态帧
 * ****************************************************************/
std::string FN_sendStatus(uint32_t p_sig)
{
	std::string l_sendBuf;
	l_sendBuf.clear();

	switch (p_sig)
	{
	case Can_buff0:
		l_sendBuf = (char *)can_buf0;
		break;
	case Can_buff1:
		l_sendBuf = (char *)can_buf1;
		break;
	case Can_buff2:
		l_sendBuf = (char *)can_buf2;
		break;
	case Can_buff3:
		l_sendBuf = (char *)can_buf3;
		break;
	case Can_buff4:
		l_sendBuf = (char *)can_buf4;
		break;
	case Can_buff5:
		l_sendBuf = (char *)can_buf5;
		break;
	case Can_buff6:
		l_sendBuf = (char *)can_buf6;
		break;
	case Can_buff7:
		l_sendBuf = (char *)can_buf7;
		break;
	case Can_buff8:
		l_sendBuf = (char *)can_buf8;
		break;
	default:
		LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "FN_sendStatus p_sig:%d\n", p_sig);
		break;
	}

	return l_sendBuf;
}

/***************************************************************** 
 * 函数名称：FN_sFunRecvDatacallback(uint8_t *p_data,uint32_t p_BufSize)
 * 描述：状态发送函数
 * 函数参数：p_data：数据 p_BufSize：数据长度
 * 返回结果：无
 * ****************************************************************/
void FN_sFunRecvDatacallback(uint8_t *p_data, uint32_t p_BufSize)
{
	F2 l_veh;
	F4 l_fourNet;
	F5 l_ramp_into;
	std::string l_datasend;
	uint32_t l_len = p_BufSize;
	uint8_t l_sendBuf[maxsize];

	l_datasend.clear();
	if (l_len == QueryLen) //查询指令
	{
		std::unique_lock<std::mutex> lck(l_mtx);
		l_veh = FN_readCanData(); //读取配置文件中的数据
		lck.unlock();
		l_datasend.assign((const char *)&l_veh, sizeof(l_veh)); //赋值
	}
	else if (l_len == SendLen) //发送指令
	{
		memcpy(&l_veh, p_data, p_BufSize);

		FN_WriteCanDataJson(l_veh);

		if (l_veh.canFlag)
		{
			l_veh = FN_readCanData();
		}
		else
		{
			l_veh = init_F2();
		}
		l_datasend.assign((const char *)&l_veh, sizeof(l_veh));
	}
	else if (l_len == Currentbehavior) //匝道汇入
	{
		// printf("匝道汇入\n");
		l_veh = init_F2();
		memcpy(&l_ramp_into, p_data, p_BufSize);
		l_veh.exteriorLights = l_ramp_into.driving_status & 0x0018;
		// printf("******************l_veh.exteriorLights is %d\n", l_veh.exteriorLights);
		// printf("******************l_ramp_into.driving_status %d\n", l_ramp_into.driving_status);
		if (l_ramp_into.request_status != 0)
		{
			l_veh.canFlag = 1;
			FN_WriteCanDataJson(l_veh);
		}
		else
		{
			l_veh.canFlag = 1;
			l_ramp_into = init_F5();
			l_veh.exteriorLights = l_ramp_into.driving_status & 0x0018;
			FN_WriteCanDataJson(l_veh);
		}
		// FN_CreatRampIntoDataJson(l_ramp_into);
	}
	else if (l_len == TestLen) //测试指令（保留上代代码）
	{
		l_datasend = FN_sendStatus(p_data[sendstatus]); //发送测试指令
	}
	else
	{
		LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "FN_sFunRecvDatacallback len: %d\n", l_len);
	}

	if (!l_datasend.empty())
		tcpSendAll(l_datasend.data(), l_datasend.size());
}
