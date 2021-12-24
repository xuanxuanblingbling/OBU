#ifndef __WEBSOCKETS_H__
#define __WEBSOCKETS_H__

#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>  
#include <libwebsockets.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/time.h>
#include <cJSON.h>
#include "webDataHandle.h"

#define IP "106.120.201.126"
#define PORT 19353

struct lws_context_creation_info ctx_info;
static struct libwebsocket_context *context = NULL;
static struct libwebsocket *wsi = NULL;

static char host[25] = {0};          //协议host参数（IP:Port）
static char orign[25] = {0};         //协议orign参数（IP:Port）

static pthread_t pt_wsi;             //用于websocket线程
static int registerResult = 1;       //申请注册结果,0：注册成功, 1：注册失败
static bool isRequestRegister = false;  //只一次进行申请注册，除非申请注册失败。

static bool connect_Sts = 0;         //连接状态
static bool Ack = 0;                 //升级结果
static int rsctl = 1;                //消息序列号

static cJSON *runStateJson = NULL;

typedef struct WebSocketClient
{
    uint8_t m_name[10];
    uint8_t m_u8IP[16];
    int32_t m_In32PORT;
}WebSocketClient_t; 

WebSocketClient_t mUSR; //全局websocket client对象

/*定位信息*/
typedef struct Location
{
    int Lon;
    int Lat;
    int Alt;
}Location_t;

/*OBU基本静态信息上报*/
typedef struct OBUStaticData
{
    uint8_t SN[20];
    uint8_t SIM[11];
    uint8_t IMEI[15];
    uint8_t IMSI[15];
    uint8_t ICCID[20];
    int V2XProtocolVersion;
    uint8_t AG15Version[15];
    int ObuStatus;
    Location_t Location;
    uint8_t HardwareVersion[20];
    uint8_t SoftwareVersion[31];
    uint8_t APP_SW[30];
    uint8_t VDS_SW[30];
    uint8_t NET_SW[30];
    uint8_t SYS_SW[30];
    uint8_t V2X_SW[30];
    bool Ack;
}OBUStaticData_t;


// /*运行状态信息*/
// typedef struct OBURunStateData
// {
//     int gnssStatus;
//     uint8_t obuTemp[10];
//     uint8_t cpuUsage[10];
//     uint8_t memUsage[10];
//     uint8_t diskUsage[10];
//     int V2X_State;
//     int _4G_State;
//     uint8_t vdsCpuUsage[10];
//     uint8_t vdsMemUsage[10];
//     uint8_t netCpuUsage[10];
//     uint8_t netMemUsage[10];
//     uint8_t v2xCpuUsage[10];
//     uint8_t v2xMemUsage[10];
//     uint8_t appCpuUsage[10];
//     uint8_t appMemUsage[10];
//     uint8_t sysCpuUsage[10];
//     uint8_t sysMemUsage[10];
// }OBURunStateData_t;


OBUStaticData_t m_OBUStaticData;       //基本静态信息
// OBURunStateData_t m_OBURunStateData;   //OBU运行状态信息


typedef struct selfCarMsg_t
{
    uint8_t mSN[16];
    int mrsctl;
    int gnssStatus;

}selfCarMsg_t;

selfCarMsg_t mselfCarMsg;


/*用于监听websocket消息线程*/
void pthread_websocket_run();

/*websocket 初始化，并建立连接开始*/
int webInit();

/*初始化websocket协议*/
void initWebsocketServer(WebSocketClient_t *user);

/*连接服务器*/
int ConnectServer(WebSocketClient_t *user);

/*回调函数*/
int WebSocketCallBack(struct libwebsocket_context *this, struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len);

/*申请注册*/
void requestRegister();

/*返回注册结果,设置到flag*/
void responseRegister(const char *cjsonStr);

/*FTP 配置以及在此进行相应的OTA 或 日志上传*/
void FTPConfig(void *cjsonStr);

/*反馈上传日志的结果*/
// void responseUploadLog(int dataRcvFlag);
void responseUploadLog(int dataRcvFlag, char fileName[256], int Type);

/*OTA 升级结果反馈*/
void OTAUpgradeToServer(int result, int DownloadStatus);

/*读取OBU基本静态信息*/
void getBasicStaticData();

/*OBU基本静态信息上报*/
void basicStaticData();

/*获取json文件中的内容*/
int getRunStsJsonStr(char *filename);
/*运行状态信息*/
void runStateData();

/*在线配置查询并反馈*/
void OnlineConfigSelectResponese(int type);

/*在线配置设置*/
void OnlineSetConfig(int type, void *cjsonStr);

/*在线配置设置反馈*/
void OnlineSetConfigResponse();

/*OBU 设备重启*/
void rebootOBU(int Status);


/*创建初始化timer,用于100ms上传自车信息*/
void initTimer();
/*5s一次获取car相关信息*/
void getCarMsg();
/*自车信息上传*/
void selfCarMsg();

//请求升级模组配置软件版本
void updateModuleConfig(int type);


/*发送数据到服务器*/
int sendDataToServer(const char *buf, int buflen);

/*时间戳获取*/
void utcFunc(const char *str);

#endif

