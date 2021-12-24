#ifndef __PUBLICMSG_h__
#define __PUBLICMSG_h__
#include <stdio.h>
#include <string.h>
#include <time.h>

/*各类消息ID*/
//此处定义与配置文件对应，处理规则：个位数*100+1
#define MSG_MessageFrame_ID_BSM 1                  //普通BSM消息,若不存在以下四种BSM,则为普通BSM
#define MSG_MessageFrame_ID_BSM_OrdinaryConven 101 //普通车辆+常规型
#define MSG_MessageFrame_ID_BSM_OrdinaryEvent 102  //普通车辆+事件型
#define MSG_MessageFrame_ID_BSM_SpecialConven 103  //特殊车辆+常规型
#define MSG_MessageFrame_ID_BSM_SpecialEvent 104   //特殊车辆+事件型
#define MSG_MessageFrame_ID_MAPDATA 2              //MAP消息
#define MSG_MessageFrame_ID_RSM 3                  //RSM消息
#define MSG_MessageFrame_ID_SPAT 4                 //SPAT消息
#define MSG_MessageFrame_ID_RSI 5                  //普通RSI消息,若不存在以下三种RSI,则为普通RSI
#define MSG_MessageFrame_ID_RSI_RoadStatic 501     //道路信息-静态类应用
#define MSG_MessageFrame_ID_RSI_RoadHalfStatic 502 //道路信息-半静态类应用
#define MSG_MessageFrame_ID_RSI_RoadDynamic 503    //道路信息-动态类应用
/*二期场景消息集*/
#define MSG_MessageFrame_ID_TestMsg 7
#define MSG_MessageFrame_ID_RTCMcorrections 8
#define MSG_MessageFrame_ID_PAMData 9
#define MSG_MessageFrame_ID_CLPMM 10
#define MSG_MessageFrame_ID_PersonalSafetyMessage 11
#define MSG_MessageFrame_ID_RoadsideCoordination 12
#define MSG_MessageFrame_ID_SensorSharingMsg 13
#define MSG_MessageFrame_ID_VehIntentionAndRequest 14
#define MSG_MessageFrame_ID_VehiclePaymentMessage 15

/*各类动态库版本信息*/
#define LibVsersionID "VWJV2X.2021.07.30"

#define MAX_DUMMY_PACKET_LEN (5000)

/*消息版本信息*/
#define MSG_MESSAGETYPE_ID_TWO 2      //二期场景消息集
#define MSG_MESSAGETYPE_ID_THREE 3    //三跨消息
#define MSG_MESSAGETYPE_ID_FOUR 4     //四跨消息
#define MSG_MESSAGETYPE_ID_NEW_FOUR 5 //新四跨消息

#define MSG_MAX_DiscardedRate 0.3 //消息层最大丢包率
#define SEC_MAX_DiscardedRate 0.3 //安全层最大丢包率
#define PUB_MIN_DiscardedRate 0.1 //最小丢包率

//用于各个层次丢包率的计算
extern int NetRecvStart;
extern int NetRecvError;
extern int NetRecvEnd;

extern double SecDiscardedRate;
extern int SecRecvStart;
extern int SecRecvDis;
extern int SecRecvError;
extern int SecRecvEnd;

extern double MsgDiscardedRate;
extern int MsgRecvStart;
extern int MsgRecvError;
extern int MsgRecvEnd;

extern double CurrentCBR;
extern int SecCyclesNum;
extern int MsgCyclesNum;

#endif
