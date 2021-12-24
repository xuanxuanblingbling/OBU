#include "InterfaceFrameMsgSending.h"
#include "FrameMessageSending.h"
#include <thread>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <map>
#include <string>

extern "C"
{
#include "PublicMsg.h"
#include "wj_log.h"
#include "ClockTimeIf.h"
#include "BusinessTool.h"
}

#include "ConfigModuleRW.h"
#include "StateMonitor.h"

using namespace std;

static map<int, shared_ptr<FrameMessageSendingFromFile>> ALLMsgType;

static FrameMessageSending ALLMsg;

static SENDCALL_BACK g_pfunc = NULL;

void ThreadMonitoring(void)
{
	int MsgType = 0;
	int index = 0;
	// LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "m_SendParamNum = %d", ProtocolStackParamConfig.messageParamConfig.m_SendParamNum);
	// LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "ThreadMonitoring() start:%d ", std::this_thread::get_id());

	while (1)
	{
		for (index = 0; index < ProtocolStackParamConfig.messageParamConfig.m_SendParamNum; index++)
		{
			//透传消息不在此处设置发送线程，由应用层控制
			if (strcmp(ProtocolStackParamConfig.messageParamConfig.m_SendParam[index].m_nSectionName, "PassSendConfig") == 0)
			{
				continue;
			}
			MsgType = ProtocolStackParamConfig.messageParamConfig.m_SendParam[index].m_nMsgType;
			if (ProtocolStackParamConfig.messageParamConfig.m_SendParam[index].m_nSendSwitch == 2)
			{
				if ((ALLMsgType.find(MsgType) == ALLMsgType.end()))
				{
					shared_ptr<FrameMessageSendingFromFile> msg = std::make_shared<FrameMessageSendingFromFile>();
					msg->block->SetMsgCallback(g_pfunc);
					msg->block->SetIndex(index);
					ALLMsgType.insert(pair<int, shared_ptr<FrameMessageSendingFromFile>>(MsgType, msg));
				}

				//如果修改发送频率情况下，重新设置定时器
				if (ALLMsgType.at(MsgType)->m_hz != ((1000 / ProtocolStackParamConfig.messageParamConfig.m_SendParam[index].m_nSendFrequency)))
				{
					//确定输出频率,例如：RSM消息默认10hz，则每一包的间隔时间为 1000/10 = 100ms,此处经确定时以100毫秒为单位，所以此处需再除以100
					ALLMsgType.at(MsgType)->m_hz = (1000 / ProtocolStackParamConfig.messageParamConfig.m_SendParam[index].m_nSendFrequency);
				}
				//创建定时器并开启
				if (ALLMsgType.at(MsgType)->Hndl.timerid == NULL)
				{
					ALLMsgType.at(MsgType)->Hndl.period_ms = ALLMsgType.at(MsgType)->m_hz;
					ALLMsgType.at(MsgType)->sevVal.sival_ptr = (void *)ALLMsgType.at(MsgType)->block;

					ST_OSA_timerCreate(&ALLMsgType.at(MsgType)->Hndl, MessageSendingFromFile,
									   ALLMsgType.at(MsgType)->sevVal);
					ST_OSA_timerStart(&ALLMsgType.at(MsgType)->Hndl);
				}
				else
				{
					if (ALLMsgType.at(MsgType)->Hndl.period_ms != ALLMsgType.at(MsgType)->m_hz)
					{
						ST_OSA_timerStop(&ALLMsgType.at(MsgType)->Hndl);
						ALLMsgType.at(MsgType)->Hndl.period_ms = ALLMsgType.at(MsgType)->m_hz;
						ST_OSA_timerStart(&ALLMsgType.at(MsgType)->Hndl);
					}
				}
			}
			else
			{
				if ((ALLMsgType.find(MsgType) != ALLMsgType.end()))
				{
					if (ALLMsgType.at(MsgType)->Hndl.timerid != NULL)
					{
						ST_OSA_timerStop(&ALLMsgType.at(MsgType)->Hndl);
						std::this_thread::sleep_for(std::chrono::milliseconds(ALLMsgType.at(MsgType)->Hndl.period_ms));
						ST_OSA_timerDelete(&ALLMsgType.at(MsgType)->Hndl);
						std::this_thread::sleep_for(std::chrono::milliseconds(10));
						memset(&ALLMsgType.at(MsgType)->Hndl, 0x00, sizeof(ST_OSA_TimerHndl));
					}

					ALLMsgType.erase(MsgType);
					// LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "ALLMsgType.size = %d ", ALLMsgType.size());
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

static void StartFrameMsgSending(void (*pfunc)(SendCallbackReturnInfo))
{
	g_pfunc = pfunc;

	std::thread Thread(&ThreadMonitoring);
	Thread.detach();

	ALLMsg.SetMsgCallback(pfunc);
	sched_param sch;
	int policy = 0;

	sch.sched_priority = 92;
	//policy =SCHED_FIFO;
	policy = SCHED_RR;
	//policy=SCHED_OTHER
	std::thread th_msg(&FrameMessageSending::ThreadProcFrameMsg, &ALLMsg);
	pthread_setschedparam(th_msg.native_handle(), policy, &sch);
	th_msg.detach();
}

__attribute__((visibility("default"))) int StackSendInit(SENDCALL_BACK pfunc)
{
	int ret = 0;
	//精确定时初始化
	//ret = FT_ClockTimeInit();

	//状态监控初始化
	ret = StartV2xRunTimmeMonitor();

	//启动发送线程
	StartFrameMsgSending(pfunc);
	return ret;
}

__attribute__((visibility("default"))) int SendFrameMessageData(MSG_MessageType_st *pData)
{
	if (NULL == pData)
	{
		return -1;
	}
	int messageType = 0, ret = 0;
	if (pData->messageType == MSG_MessageType_ID_Three)
	{
		messageType = pData->msgtype.MessageThree.enumMessageFrameType;
	}
	else if (pData->messageType == MSG_MessageType_ID_Four)
	{
		messageType = pData->msgtype.MessageFour.enumMessageFrameType;
	}
	else if (pData->messageType == MSG_MessageType_ID_NEW_Four)
	{
		messageType = pData->msgtype.MessageNewFour.enumMessageFrameType;
	}
	else
	{
		if (pData->msgtype.MessageTwo.enumMessageFrameType == MSGV2_MessageFrame_PR_msgFrameExt)
		{
			messageType = pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.enumpresent;
		}
		else
		{
			messageType = pData->msgtype.MessageTwo.enumMessageFrameType;
		}
	}

	//适应二期场景的变化，加入此判断
	if (messageType > 100)
	{
		messageType /= 100;
	}

	if (SendFrameIDCheck(messageType))
	{
		UpdateTxQueDataNum();
		if (ProtocolStackParamConfig.thirdPartyLibConfig.SendingSerial == 1)
		{
			FrameMessageSendingSerial SendMsg;
			SendMsg.SetMsgCallback(g_pfunc);
			ret = SendMsg.MessageSending(pData);
			free(pData);
			pData = NULL;
		}
		else
		{
			//所有消息存储到统一队列
			ret = ALLMsg.DataPushInQueue(pData);
		}
	}
	else
	{
		free(pData);
		pData = NULL;
		// LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "messageType = %d is not find! free(pData) is success!", messageType);
		return -1;
	}

	return ret;
}
