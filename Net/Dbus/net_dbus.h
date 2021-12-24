/*
 * @Descripttion: 
 * @version: 
 * @Author: wanji.net.cn
 * @email: mk_wanji@126.com
 * @Date: 2021-12-03 20:04:04
 * @LastEditors: VanJee Technology Co.,Ltd
 * @LastEditTime: 2021-12-07 16:12:04
 */
/************************************************************
  文件名: vds_dbus.h
  作者:
  描述: vds模块dbus相关定义，接口函数定义
  版本:
  日期:
  函数列表:
  历史记录:
 ***********************************************************/
#ifndef VEH_FEATURES_H
#define VEH_FEATURES_H

#include <stdint.h>
#include <glib-object.h>

#ifdef __cplusplus
extern "C"
{
#endif

	enum
	{
		NET_CAN_DATA,
		NET_LINK_STATUS,
		NET_CONFIG_RS,
		NET_FAULT_STATUS,
		NET_LAST_SIGNAL
	};

	typedef enum _UpdateType
	{
		UPDATE_SUCCESS = 0x90,
		UPDATE_FAIL = 0x91,
		UPDATE_DEFAULT,
	} UpdateType;

	typedef struct _NetLinkStatus
	{

		uint32_t linkClientNum; //客户端连接个数
		uint32_t tcpRecvNUm;	//从tcp接收数据长度
		uint32_t tcpSendNum;	//发送给tcp数据长度
		uint32_t udpSendNUm;
	} __attribute__((packed)) NetLinkStatus;

#define APP_ACT_SAFE_ID 0x3001		 //APP功能安全数据帧ID
#define APP_TRFC_REMIND_ID 0x3002	 //APP交通标志事件提醒帧ID
#define APP_SPD_GUIDE_ID 0x3003		 //APP车速引导信息帧ID
#define APP_CFG_RS_ID 0x3004		 //APP配置响应帧ID
#define APP_FAULT_PUSH_ID 0x3005	 //APP故障推送帧ID
#define APP_VRU_SAFE_ID 0x3006		 //APP弱势交通安全信息帧ID
#define APP_SEND_MATCHDATA_ID 0x3009 // APP发送地图匹配的数据
#define APP_SEND_PLATFORM_ID 0x3010	 // APP发送通州平台的数据
#define APP_SYS_CFGRQ_TAG 0x4001
#define V2X_NET_COORDINATION_ID 0x2005 //V2X发送协作式匝道汇入数据

#define MSGM_NET_SIM_CAN_TAG 0x5001
#define MSGM_NET_LINK_STATUS_TAG 0x5002
#define MSGM_NET_CONFIG_RS_TAG 0x5003
#define MSGM_NET_Fault_Status_TAG 0x5004

#define SUB_CMD_00 0x00
#define MAIN_CMD_10 0x10
#define MAIN_CMD_11 0x11
#define MAIN_CMD_12 0x12
#define MAIN_CMD_13 0x13
#define MAIN_CMD_19 0x19
#define DBUS_SEND_TIMER 2000

	extern NetLinkStatus g_status;

	void NetDbusRecvThread(void);

	void SendNetDbusData(uint8_t *p_data, uint32_t p_len, uint8_t p_sigid);

	gboolean FN_FaultStatus_Send();

#ifdef __cplusplus
}
#endif

#endif
