/**
* @file         :wjv3_uper_interface.c
* @brief        :该文件为协议栈消息层对外接口函数定义
* @details  	:主要包含协议消息类型对外编解码主函数
* @author   	:huangsai  any question please send mail to huangsai@wanji,net.cn
* @date     	:2020-8-10
* @version		:V1.0
* @copyright 	:Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
/* 头文件包含 */
#include "wjv3_uper_interface.h"
#include "./../MsgFrameV3/MessageFrame.h"
#include "ConfigModuleRW.h"
#include "wj_log.h"

/*三跨消息集接口*/
WJV3_UperFromFileEncodeMain_BACK wjv3_UperFromFileEncodeMain = NULL;
WJV3_UperEncOrDecMain_BACK wjv3_UperEncOrDecMain = NULL;

int getAIDFromFileV3(void *pstruMsg);

void SetWJV3_MessageCallback(WJV3_UperFromFileEncodeMain_BACK p_wjv3_UperFromFileEncodeMain,
							 WJV3_UperEncOrDecMain_BACK p_wjv3_UperEncOrDecMain,
							 WJV3_SetGetAIDFromFileCallback p_wjv3_SetGetAIDFromFileCallback)
{
	wjv3_UperFromFileEncodeMain = p_wjv3_UperFromFileEncodeMain;
	wjv3_UperEncOrDecMain = p_wjv3_UperEncOrDecMain;
	if (NULL != p_wjv3_SetGetAIDFromFileCallback)
	{
		p_wjv3_SetGetAIDFromFileCallback(getAIDFromFileV3);
		printf("%s %s %d wjv3_SetGetAIDFromFileCallback Success!\n", __FILE__, __FUNCTION__, __LINE__);
	}
}
/**
 * @brief     WJ_getAIDFromFile检查消息号函数
 * @details   协议栈消息层编解码中 统一 消息的解码函数入口
 * @param   [in]   MessageFrame_t *msg_frame_ptr   WJ结构
 * @return      本函数返回执行结果，AID的值
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/09/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int getAIDFromFileV3(void *pstruMsg)
{
	/* 入参为空检查 */
	if (NULL == pstruMsg)
	{
		LogPrint(LOG_LEVEL_ERR,
				 "MSGLAYERV3MSG",
				 "input is null:pstruMsgframe = %p", pstruMsg);
		return -1;
	}
	MessageFrame_t *pstruMsgFrame = (MessageFrame_t *)pstruMsg;
	int MessageAID = ProtocolStackParamConfig.DSMPParamConfig.StandardMessageAID;
	switch (pstruMsgFrame->present)
	{
	case MessageFrame_PR_mapFrame:
		MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.MAPMSGAID;
		break;
	case MessageFrame_PR_bsmFrame:
		if (pstruMsgFrame->choice.bsmFrame.safetyExt != NULL)
		{
			if (pstruMsgFrame->choice.bsmFrame.safetyExt->events != NULL)
			{
				//普通车辆+事件型
				MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryEvent;
			}
			else
			{
				//普通车辆+常规型
				MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryConven;
			}
		}
		else
		{
			//普通车辆+常规型
			MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryConven;
		}
		break;
	case MessageFrame_PR_rsiFrame:
		//道路信息-静态类应用
		MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadStatic;
		break;
	case MessageFrame_PR_spatFrame:
		MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.SPATMSGAID;
		break;
	case MessageFrame_PR_rsmFrame:
		MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSMMSGAID;
		break;
	default:
		LogPrint(LOG_LEVEL_ERR,
				 "MSGLAYERV3MSG",
				 "Msg present is err:pstruMsgFrame->present = %d", pstruMsgFrame->present);
		break;
	}
	return MessageAID;
}