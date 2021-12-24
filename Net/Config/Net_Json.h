/*
 * @Descripttion: 
 * @version: 
 * @Author: wanji.net.cn
 * @email: mk_wanji@126.com
 * @Date: 2021-12-03 14:11:30
 * @LastEditors: VanJee Technology Co.,Ltd
 * @LastEditTime: 2021-12-09 11:05:17
 */
#ifndef _NET_JSON_H
#define _NET_JSON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

	/*****************
 * F2  带有帧头帧尾信息的消息帧
 * ***********************/
	typedef struct _F2
	{
		uint16_t frameHead;
		uint8_t frameNum;
		uint8_t frameCMDT;
		uint8_t framSubCDMT;
		uint8_t frameStatus;
		uint16_t frameLen;
		uint32_t blockState; //档位状态
		uint8_t canFlag;	 //是否使用CAN数据
		uint32_t speed;
		uint32_t wheelTurn;			   //方向盘转角
		uint16_t exteriorLights;	   //车灯
		int32_t brakePedalStatus;	   //刹车
		int32_t tractionControlSystem; //车轮制动系统
		int32_t tractionControlStatus; //辅助制动系统
		int32_t AntilockbrakeSystem;   //防抱死系统
		int32_t bodyStabilitySystem;   //车身稳定系统
		int32_t brakeAssistSystem;	   //刹车辅助系统
		int32_t auxiliaryBrakeSystem;  //牵引力控制系统状态
		int32_t basicVehicleClass;
		uint8_t check;
		uint8_t end;

	} __attribute__((packed)) F2;

	typedef struct _F2N
	{
		uint32_t speed;
		uint32_t wheelTurn;			   //方向盘转角
		uint16_t exteriorLights;	   //车灯
		int32_t brakePedalStatus;	   //刹车
		int32_t tractionControlSystem; //车轮制动系统
		int32_t tractionControlStatus; //辅助制动系统
		int32_t AntilockbrakeSystem;   //防抱死系统
		int32_t bodyStabilitySystem;   //车身稳定系统
		int32_t brakeAssistSystem;	   //刹车辅助系统
		int32_t auxiliaryBrakeSystem;  //牵引力控制系统状态
		int32_t basicVehicleClass;
		uint8_t transmissionState; //Net_EncodeMessCan.h

	} __attribute__((packed)) F2_N;

	typedef struct _F4
	{
		uint16_t frameHead;
		uint8_t frameNum;
		uint8_t frameCMDT;
		uint8_t framSubCDMT;
		uint8_t frameStatus;
		uint16_t frameLen;
		uint8_t canRequest;
		uint8_t check;
		uint8_t end;
	} __attribute__((packed)) F4;

	typedef struct _F5
	{
		uint16_t frameHead;
		uint8_t frameNum;
		uint8_t frameCMDT;
		uint8_t framSubCDMT;
		uint8_t frameStatus;
		uint16_t frameLen;
		uint8_t request_status;		 //请求状态（0：关闭请求 1：单次请求 2：周期性请求）
		uint16_t driving_status;	 //驾驶状态
		uint8_t driving_request;	 //驾驶请求
		uint8_t target_lane;		 //目标车道
		uint8_t request_target;		 //请求目标
		uint8_t device_id[8];		 //请求设备的ID
		uint32_t request_start_time; //请求开始的UTC
		uint32_t request_end_time;	 //请求结束的UTC
		uint8_t check;
		uint8_t end;
	} __attribute__((packed)) F5;

	extern F2 FN_readCanData();
	extern uint32_t FN_WriteCanDataJson(F2 p_veh);
	extern F5 FN_readRampIntoData();
	extern uint32_t FN_CreatRampIntoDataJson(F5 p_ramp_into);
	extern F2 init_F2();

#ifdef __cplusplus
}
#endif

#endif