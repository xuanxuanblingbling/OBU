#ifndef __DATASET_H_
#define __DATASET_H_
//#include "../Include/BaseInterface_Include.h"
//#include "../Include/FaciLayer_Include.h"
#include "../NetUtil/TcpServer.h"
#include "../NetUtil/TcpClient.h"
#include "../NetUtil/UdpService.h"
#include "../NetUtil/UdpClient.h"

#define Program_Version (nint8_t *)"V2X_APP_LTEV_V1.3.0.20190116"

extern StcTcpServer g_StcTcpServer;
extern StcTcpClient g_TcpClient;
extern StcUdpClient g_UdpClient;
//extern tStateStore pApp;
extern int msgid;

extern pthread_t tidp_DealBSM;
extern pthread_t tidp_DealMAP;
extern pthread_t tidp_DealRSM;
extern pthread_t tidp_DealRSI;
extern pthread_t tidp_DealSPAT;

extern pthread_t tidp_HostStatus;
extern pthread_t tidp_AroundVeh;
extern pthread_t tidp_AroundRsi;
extern pthread_t tidp_UpD1_2WebService;
extern pthread_t tidp_UpV2X_2WebService;


extern pthread_t  tidp_CANDataSend;  	  //**20190526**/

//主动发送指令时的帧序号
extern uint8_t g_u8IndexId;

//应用是否采用地图模式　0－－是　　1－－不是
extern uint8_t g_IsMapMode;

extern pthread_mutex_t g_mutex_A;

#endif /*__DATASET_H_*/
