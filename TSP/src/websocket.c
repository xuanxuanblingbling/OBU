#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <libwebsockets.h>
// #include <cJSON.h>

#include "websockets.h"
#include "wj_log.h"
#include "tsp_config.h"
#include "tsp_file.h"
#include "Config.h"

#define NET_Config_OBUInfo_Path "/mnt/APP/Config/obu/net/Config_OBUInfo.ini"
#define NET_Config_Supervision_Path "/mnt/APP/Config/obu/net/Config_Supervision.ini"
#define DevInfo_Config_DevInfo_Path "/mnt/APP/Config/obu/DevInfo/DevInfo.json"
#define DYNAMICINFO_Config_Path "/mnt/APP/Config/obu/sysm/DynamicInfo/DynamicInfo.json"

#define TSP_Config_Path "/mnt/APP/Config/obu/tsp/TSP_Config.ini"
#define V2X_ProtocolStack_Path "/mnt/APP/Config/obu/v2x/ProtocolStack.ini"

#define MAX_PAYLOAD_SIZE  10 * 1024

/*全局变量*/
int logType = 1;                   //需要上传日志文件类型
int logAmount = 1;                 //需要上传日志文件个数

/**
 * 会话上下文对象，结构根据需要自定义
 */
struct session_data {
	uint16_t frametype;
    unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + MAX_PAYLOAD_SIZE];
    int len;
};

/*
声明协议结构体
*/
static struct libwebsocket_protocols protocols[2] = {
    {
        //协议名称，协议回调，接收缓冲区大小
        "ws", WebSocketCallBack, sizeof( struct session_data ), MAX_PAYLOAD_SIZE,
    },
    {
        NULL, NULL, 0, 0 // 最后一个元素固定为此格式
    }
};

/*websocket初始化*/
int webInit()
{
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " webInit start!");

	//读取配置文件中的 服务器的ip,port等信息
	if(access(TSP_Config_Path, F_OK) == 0) 
	{
		GetPrivateProfileString("WebSocket", "IP", NULL, mUSR.m_u8IP, sizeof(mUSR.m_u8IP), TSP_Config_Path);
		mUSR.m_In32PORT = GetPrivateProfileInt("WebSocket", "PORT", 19353, TSP_Config_Path);
		GetPrivateProfileString("WebSocket", "Name", NULL, mUSR.m_name, sizeof(mUSR.m_name), TSP_Config_Path);
	}
	else
	{
		strcpy(mUSR.m_u8IP, "106.120.201.126");
		mUSR.m_In32PORT = 19353;
		strcpy(mUSR.m_name, "TSP");
	}

	//新线程进行websocket初始化，以及监听消息
	if(0 != pthread_create(&pt_wsi, NULL, (void *)pthread_websocket_run, NULL))
	{
    	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " creat websocket pthread error!");
		return -1;
	}
	return 0;
}


void initWebsocketServer(WebSocketClient_t *user)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," initWebsocketServer start!");
	/* 回调声明初始化 */
	memset(protocols, 0, sizeof(protocols));

	// struct libwebsocket_protocols protocols[2] = {0};
	protocols[0].name = (const char *)user->m_name;
	protocols[0].callback = WebSocketCallBack;
	protocols[0].rx_buffer_size = 10240;/* 接收server数据的缓存区大小 */

	//初始化lws_context_creation_info
	ctx_info.port = CONTEXT_PORT_NO_LISTEN;
    ctx_info.iface = NULL;
    ctx_info.protocols = protocols;
    ctx_info.gid = -1;
    ctx_info.uid = -1;

	//创建context.
	if(context != NULL)
	{
		free(context);
		context = NULL;
	}
	context = libwebsocket_create_context(&(ctx_info));
	if (context == NULL) 
	{
		LogPrint(LOG_LEVEL_ERR,MODULE_NAME," Creating libwebsocket context failed!");
		return -1;
	}

	sprintf((char *)host,"%s:%d",user->m_u8IP,user->m_In32PORT);
	sprintf((char *)orign,"%s:%d",user->m_u8IP,user->m_In32PORT);
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," webserver host = %s", host);
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," webserver orign = %s", orign);
}

/*连接websocket服务器*/
int ConnectServer(WebSocketClient_t *user)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," ConnectServer start!");

	/* 连接服务器接口 */ 
	// free(wsi);
	wsi = NULL;
	wsi = libwebsocket_client_connect(context, 
											(const char *)user->m_u8IP,(int)user->m_In32PORT, 
											0,
											"/v2x-obu-back/obuWebSocket", 
											host,
											orign,
											protocols[0].name, 
											-1//,
											//wsi  //libwebsocket_client_connect_extended
											);
	if (wsi == NULL)
	{
		LogPrint(LOG_LEVEL_ERR,MODULE_NAME," libwebsocket_client_connect_extended fail!");
		libwebsocket_context_destroy(context);
		return -1;
	}
	/* 处理客户端与服务器之间的消息交互 */
	while (1)
	{
		libwebsocket_service(context, 1000);//第二个为超时时间 单位ms
		if(wsi == NULL){
			// libwebsocket_context_destroy(context);
			pthread_exit(NULL);
		}
	}
	return 0;
}

/*用于监听websocket消息线程*/
void pthread_websocket_run()
{
	initWebsocketServer(&mUSR);
	ConnectServer(&mUSR);
}


/*websocket 消息回调函数*/
int WebSocketCallBack(struct libwebsocket_context *this,struct libwebsocket *m_wsi, enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," WebSocketCallBack - reason = %d",reason);

	switch (reason) {
	case LWS_CALLBACK_PROTOCOL_DESTROY:
		initWebsocketServer(&mUSR);
		sleep(60);
		ConnectServer(&mUSR);
		break;
	case LWS_CALLBACK_CLOSED:
		connect_Sts = 0;//表示连接状态断开，不能发送数据。
		// WebSocketClient_t *user_temp = (WebSocketClient_t *)user;
		free(wsi);

		int kill_rc = pthread_kill(pt_wsi, 0);   // 发送信号0，探测线程是否存活
		// 打印探测结果
		if (kill_rc == ESRCH || kill_rc == EINVAL)
		{
			if(0 != pthread_create((&pt_wsi), NULL, (void *)pthread_websocket_run, NULL))
			{
				LogPrint(LOG_LEVEL_ERR, MODULE_NAME," Creat websocket pthread error");
				return -1;
			}
		}
		else
		{
			while(ConnectServer(&mUSR) != 0)//不断重新连接
			{
				// sleep(1);
				LogPrint(LOG_LEVEL_NOTICE,MODULE_NAME," reconnect to server IP:%s, Port:%d",mUSR.m_u8IP,mUSR.m_In32PORT);
			}
		}
		
		break;
	case LWS_CALLBACK_CLIENT_RECEIVE:
		((char*)in)[len] = '\0';
		cJSON *mcJson = NULL;
		mcJson = cJSON_Parse(in);

		switch (cJSON_GetObjectItem(mcJson,"frametype")->valueint)
		{
			case 0x8001://请求上传对应的日志文件
				if(registerResult == 0)
				{
					FTPConfig(mcJson);
				}
				break;

			case 0x8101: //请求OTA升级,获取FTP 路径,用户名,密码等信息
				if(registerResult == 0)
				{
					//在OBU 设备远程注册成功之后,才能进行相关的远程升级等
					FTPConfig(mcJson);
				}
				break;

			case 0x8103: //请求模组软件版本
				if(registerResult == 0)
				{
					//在OBU 设备远程注册成功之后,才能进行相关的远程升级等
					updateModuleConfig(cJSON_GetObjectItem(mcJson,"Type")->valueint);			
				}
				break;

			case 0x8202://注册反馈
				responseRegister(in);
				break;

			case 0x8301://接收在线请求查看相应配置参数，并进行应答反馈。
				if(registerResult == 0)
				{
					OnlineConfigSelectResponese(cJSON_GetObjectItem(mcJson,"inquireType")->valueint);
				}
				break;

			case 0x8303://接收在线请求配置设置
				if(registerResult == 0)
				{
					OnlineSetConfig(cJSON_GetObjectItem(mcJson,"setType")->valueint, mcJson);
				}
				break;

			case 0x9001: // 远程在线重启
				if(registerResult == 0)
				{
					rebootOBU(cJSON_GetObjectItem(mcJson,"Status")->valueint);
				}
				break;
				
			default:
				break;
		}
		if(mcJson != NULL)
			cJSON_Delete(mcJson);

		break;

	case LWS_CALLBACK_CLIENT_WRITEABLE:     // 当此客户端可以发送数据时的回调
		// if ( data->msg_count < 3 ) {
		// 	// 前面LWS_PRE个字节必须留给LWS
		// 	memset( data->buf, 0, sizeof( data->buf ));
		// 	char *msg = (char *) &data->buf[ LWS_PRE ];
		// 	data->len = sprintf( msg, "你好 %d", ++data->msg_count );
		// 	lwsl_notice( "Tx: %s\n", msg );
		// 	// 通过WebSocket发送文本消息
		// 	lws_write( wsi, &data->buf[ LWS_PRE ], data->len, LWS_WRITE_TEXT );
		// }
		break;

	case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
		break;

	case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER: /* 完成握手 */
		break;

	case LWS_CALLBACK_CLIENT_ESTABLISHED: /* 连接成功 */
		LogPrint(LOG_LEVEL_INFO,MODULE_NAME," LWS_CALLBACK_CLIENT_ESTABLISHED websocket connect success!");
		connect_Sts = 1;

		//websocket 连接成功后，进行请求注册，注册只进行一次，除非注册失败，需要重新进行注册
		// if(!isRequestRegister)
		// {
			// sleep(1);
			requestRegister();
		// }
		break;

	case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
		sleep(60);
		wsi = NULL;
		wsi = libwebsocket_client_connect(context, 
												(const char *)mUSR.m_u8IP,(int)mUSR.m_In32PORT, 
												0,
												"/v2x-obu-back/obuWebSocket", 
												host,
												orign,
												protocols[0].name, 
												-1//,
												//wsi  //libwebsocket_client_connect_extended
												);
		break;

	default:
		break;
	}
}

//OBU 主动请求申请注册
void requestRegister()
{
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " requestRegister start!");
	int frametype = 0x8201;//33281
	char SN[20] = {0};
	char utc[30] = {0};
	char ver[] = "1.6";

	rsctl = (rsctl >= 0xFFFF) ? 1 : (rsctl + 1);
	GetPrivateProfileString("ObuBaseInfo","ObuSN",NULL,SN,sizeof(SN),NET_Config_OBUInfo_Path);
	utcFunc(utc);
	
	/*转换成字符串类型*/
	cJSON *registerData = cJSON_CreateObject();
	cJSON_AddNumberToObject(registerData, "frametype", frametype);
	cJSON_AddNumberToObject(registerData, "rsctl", rsctl);
	cJSON_AddStringToObject(registerData, "SN", SN);
	cJSON_AddStringToObject(registerData, "utc", utc);
	cJSON_AddStringToObject(registerData, "ver", ver);

	char *buf = cJSON_Print(registerData);
	cJSON_Minify(buf);//去除格式
	
	int len = strlen(buf);

	/*添加中间变量为了进行释放*/
	char buf_temp[1024] = {0};
	strcpy(buf_temp, buf);

	/*释放指针*/
	free(buf);
	if(registerData != NULL)
		cJSON_Delete(registerData);

	// sendDataToServer(buf_temp, len);
	int ret = libwebsocket_write(wsi, (uint8_t*)buf_temp, len, LWS_WRITE_TEXT);
}

//返回注册结果
void responseRegister(const char* cjsonStr)
{
	cJSON *mcJson = NULL;
	mcJson = cJSON_Parse(cjsonStr);

	//0：注册成功, 1：注册失败
	registerResult = cJSON_GetObjectItem(mcJson, "registerFlag")->valueint;
	if(registerResult == 0){
		LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " Register Success!");
	} else {
		LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " Register Fail!");
	}

	if(mcJson != NULL)
		cJSON_Delete(mcJson);

	if(registerResult == 0)
	{
		// isRequestRegister = true;
		/*只有注册成功后，同时是第一次开机，OBU基本静态信息上报*/
		getBasicStaticData();
	}
	else
	{
		// isRequestRegister = false;
		// if(!isRequestRegister)
		// {
			sleep(60);
			requestRegister();//注册反馈失败，需要重新进行注册
		// }
	}	
}

/*FTP 配置以及在此进行相应的OTA 或 日志上传*/
void FTPConfig(void* cjsonStr)
{
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " FTPConfig start!");

	int frameType = 0;
	char UpdateVersion[50] = {0};
	char UpdateUrl[100] = {0};
	char UserName[30] = {0};
	char PassWord[30] = {0};

	frameType = cJSON_GetObjectItem(cjsonStr, "frametype")->valueint;
	sprintf(UpdateUrl,"%s", cJSON_GetObjectItem(cjsonStr, "UpdateUrl")->valuestring);
	sprintf(UserName,"%s", cJSON_GetObjectItem(cjsonStr, "UserName")->valuestring);
	sprintf(PassWord,"%s", cJSON_GetObjectItem(cjsonStr, "PassWord")->valuestring);

	if(frameType == 0x8101)//OTA 升级
    {
		sprintf(UpdateVersion,"%s", cJSON_GetObjectItem(cjsonStr, "UpdateVersion")->valuestring);
		Ack = cJSON_GetObjectItem(cjsonStr,"Ack")->valueint;
    }
    else if(frameType == 0x8001)//日志上传
	{
		logType = cJSON_GetObjectItem(cjsonStr, "Type")->valueint;
		logAmount = cJSON_GetObjectItem(cjsonStr, "Amount")->valueint;
	}
	
	//设置FTP配置参数,同时此时进行相应的软件版本下载或日志上传操作，FTP 方式
	setFTPConfig(frameType, UpdateVersion, UpdateUrl, UserName, PassWord);

	// if(2 == setFTPConfig(frameType, UpdateVersion, UpdateUrl, UserName, PassWord))
	// {//表示上传日志文件。
	// 	// responseUploadLog(1);
	// }
}

/*反馈上传日志的结果*/
void responseUploadLog(int dataRcvFlag, char fileName[256], int Type)
{
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " responseUploadLog start!");

	/*转换成字符串类型*/
	cJSON *mcJson = NULL;
	mcJson = cJSON_CreateObject();
	int frametype = 0x8003;//32771
	rsctl = (rsctl >= 0xFFFF) ? 1 : (rsctl + 1);
	char utc[30] = {0};
	utcFunc(utc);

	cJSON_AddNumberToObject(mcJson, "frametype", frametype);
	cJSON_AddNumberToObject(mcJson, "rsctl", rsctl);
	cJSON_AddStringToObject(mcJson, "utc", utc);
	cJSON_AddStringToObject(mcJson, "filename", fileName);
	cJSON_AddNumberToObject(mcJson, "Type", Type);
	cJSON_AddNumberToObject(mcJson, "dataRcvFlag", dataRcvFlag);

	char *buf = cJSON_Print(mcJson);

	if(mcJson != NULL)
		cJSON_Delete(mcJson);

	cJSON_Minify(buf);//去除格式
	int len = strlen(buf);

	/*添加中间变量为了进行释放*/
	char buf_temp[1024] = {0};
	strcpy(buf_temp, buf);

	free(buf);
	
	sendDataToServer(buf_temp, len);
}

/*OTA 升级结果反馈*/
void OTAUpgradeToServer(int result, int DownloadStatus)
{
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " OTAUpgradeToServer result = %d", result);
	/*转换成字符串类型0x8102*/
	int frametype = 0x8102;
	cJSON *mcJson = NULL;
	mcJson = cJSON_CreateObject();
	cJSON_AddNumberToObject(mcJson, "frametype", frametype);
	//0-成功，1-失败
	cJSON_AddNumberToObject(mcJson, "UpdateStatus", result);
	//0-下载成功， 1-下载失败
	cJSON_AddNumberToObject(mcJson, "DownloadStatus", DownloadStatus);

	char *buf = cJSON_Print(mcJson);
	cJSON_Minify(buf);//去除格式
	int len = strlen(buf);

	/*添加中间变量为了进行释放*/
	char buf_temp[1024] = {0};
	strcpy(buf_temp, buf);

	free(buf);
	if(mcJson != NULL)
		cJSON_Delete(mcJson);

	if(Ack)
	{//需要根据Ack进行判断是否需要上传升级结果.
		sendDataToServer(buf_temp, len);
	}
	else
	{
		LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " Ack == false, so not need to response result!");
	}
}

/*读取OBU基本静态信息*/
void getBasicStaticData()
{
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " getBasicStaticData start!");
	//从INI文件中获取数据。
	GetPrivateProfileString("ObuBaseInfo","ObuSN",NULL,m_OBUStaticData.SN,sizeof(m_OBUStaticData.SN),NET_Config_OBUInfo_Path);
	GetPrivateProfileString("Module4GInfo","SIM",NULL,m_OBUStaticData.SIM,sizeof(m_OBUStaticData.SIM),NET_Config_OBUInfo_Path);
	GetPrivateProfileString("Module4GInfo","IMEI",NULL,m_OBUStaticData.IMEI,sizeof(m_OBUStaticData.IMEI),NET_Config_OBUInfo_Path);
	GetPrivateProfileString("Module4GInfo","IMSI",NULL,m_OBUStaticData.IMSI,sizeof(m_OBUStaticData.IMSI),NET_Config_OBUInfo_Path);

	m_OBUStaticData.V2XProtocolVersion = GetPrivateProfileInt("MsgFrameConfig", "MsgFrameVersion", 4, V2X_ProtocolStack_Path);

	GetPrivateProfileString("ObuBaseInfo","AG15SwVersion",NULL,m_OBUStaticData.AG15Version,sizeof(m_OBUStaticData.AG15Version),NET_Config_OBUInfo_Path);
	
	//需要根据gnssStatus，V2X State， 4GState三个状态同时判断
	int GnssStatus=0;
	GnssStatus = GetPrivateProfileInt("GNSSInfo","GnssStatus",0,NET_Config_Supervision_Path);
	int V2XStatus=0;
	V2XStatus = GetPrivateProfileInt("V2XInfo","V2XStatus",0,NET_Config_Supervision_Path);
	if((GnssStatus == 0) && (V2XStatus == 0))
	{
		m_OBUStaticData.ObuStatus = 0;
	}

	int l_n32iVariable = 0;
    l_n32iVariable = GetPrivateProfileInt("GNSSInfo","longitude",l_n32iVariable,NET_Config_Supervision_Path);
    m_OBUStaticData.Location.Lon = l_n32iVariable;
	l_n32iVariable = GetPrivateProfileInt("GNSSInfo","latitude",l_n32iVariable,NET_Config_Supervision_Path);
    m_OBUStaticData.Location.Lat = l_n32iVariable;
	// GetConfigIntValue(NET_Config_Supervision_Path, "GNSSInfo", "Alt", &m_OBUStaticData.Location.Alt);

	GetPrivateProfileString("ObuBaseInfo","HardWarVersion",NULL,m_OBUStaticData.HardwareVersion,sizeof(m_OBUStaticData.HardwareVersion),NET_Config_OBUInfo_Path);
	GetPrivateProfileString("ObuBaseInfo","AppVersion",NULL,m_OBUStaticData.SoftwareVersion,sizeof(m_OBUStaticData.SoftwareVersion),NET_Config_OBUInfo_Path);

	GetConfigStringValue(DevInfo_Config_DevInfo_Path, "ApplicationSoftwareVersion", "APP", m_OBUStaticData.APP_SW);
	GetConfigStringValue(DevInfo_Config_DevInfo_Path, "ApplicationSoftwareVersion", "VDS", m_OBUStaticData.VDS_SW);
	GetConfigStringValue(DevInfo_Config_DevInfo_Path, "ApplicationSoftwareVersion", "NET", m_OBUStaticData.NET_SW);
	GetConfigStringValue(DevInfo_Config_DevInfo_Path, "ApplicationSoftwareVersion", "SYS", m_OBUStaticData.SYS_SW);
	GetConfigStringValue(DevInfo_Config_DevInfo_Path, "ApplicationSoftwareVersion", "V2X", m_OBUStaticData.V2X_SW);

	//发送OBU基本静态信息
	basicStaticData();
}

/*OBU基本静态信息上报*/
void basicStaticData()
{
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " BasicStaticData start !");
	/*转换成字符串类型*/
	cJSON *mcJson = NULL;
	mcJson = cJSON_CreateObject();
	cJSON *Location;
	int frametype = 0x7401;//29697
	cJSON_AddNumberToObject(mcJson,"frametype",frametype);

	cJSON_AddStringToObject(mcJson, "SN", m_OBUStaticData.SN);
	cJSON_AddStringToObject(mcJson, "SIM", m_OBUStaticData.SIM);
	cJSON_AddStringToObject(mcJson, "IMEI", m_OBUStaticData.IMEI);
	cJSON_AddStringToObject(mcJson, "IMSI", m_OBUStaticData.IMSI);
	cJSON_AddStringToObject(mcJson, "ICCID", "0");

	cJSON_AddNumberToObject(mcJson, "v2xVersion", m_OBUStaticData.V2XProtocolVersion);

	cJSON_AddStringToObject(mcJson, "ag15", m_OBUStaticData.AG15Version);
	cJSON_AddStringToObject(mcJson, "ObuStatus", 0);//m_OBUStaticData.ObuStatus);

	cJSON_AddItemToObject(mcJson,"Location",Location=cJSON_CreateObject());
	cJSON_AddNumberToObject(Location, "Lon", m_OBUStaticData.Location.Lon);
	cJSON_AddNumberToObject(Location, "Lat", m_OBUStaticData.Location.Lat);
	cJSON_AddNumberToObject(Location, "Alt", 0);

	cJSON_AddStringToObject(mcJson, "HardwareVersion", m_OBUStaticData.HardwareVersion);
	cJSON_AddStringToObject(mcJson, "SoftwareVersion", m_OBUStaticData.SoftwareVersion);
	cJSON_AddStringToObject(mcJson, "APP_SW", m_OBUStaticData.APP_SW);
	cJSON_AddStringToObject(mcJson, "VDS_SW", m_OBUStaticData.VDS_SW);
	cJSON_AddStringToObject(mcJson, "NET_SW", m_OBUStaticData.NET_SW);
	cJSON_AddStringToObject(mcJson, "SYS_SW", m_OBUStaticData.SYS_SW);
	cJSON_AddStringToObject(mcJson, "V2X_SW", m_OBUStaticData.V2X_SW);

	cJSON_AddBoolToObject(mcJson, "Ack", FALSE);

	// LogPrint(LOG_LEVEL_INFO,MODULE_NAME,"request register data = %s\n", buf);
	char *buf = cJSON_Print(mcJson);
	cJSON_Minify(buf);//去除格式
	int len = strlen(buf);

	/*添加中间变量为了进行释放*/
	char buf_temp[2048] = {0};
	strcpy(buf_temp, buf);

	free(buf);
	if(mcJson != NULL)
		cJSON_Delete(mcJson);

	sendDataToServer(buf_temp, len);
}

/*获取json文件中的内容*/
int getRunStsJsonStr(char *filename)
{
	char buf[1024*5]={0};
    FILE *fp;
    int  f_size;
    int  re_fread;
	
	if((fp = fopen(filename, "r")) == NULL){
		LogPrint(LOG_LEVEL_ERR,MODULE_NAME," --open json fail!");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp);
    rewind(fp);

    re_fread = fread(buf, f_size, 1, fp);
    if(re_fread != 1){ 
		LogPrint(LOG_LEVEL_ERR,MODULE_NAME," --read json fail!");   
        fclose(fp);
        return -1;
    }
    fclose(fp);

	runStateJson = cJSON_Parse(buf);

	return 0;
}

/*运行状态信息*/
void runStateData()
{
	/*从json文件中获取数据。GNSS：130（普通定位：单点、E1、E2、E5），141（RTK error)，131（AG15 error )，140（E4）。*/
	if(registerResult == 1)
	{
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " websocket is not register, so send runstate fail!");
		return ;
	}
	
	int ret = getRunStsJsonStr(DYNAMICINFO_Config_Path);
	if(ret == -1){
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " -- runStateData getJsonStr fail --!");
		return;
	}
	
	int intTemp;
	uint8_t strTemp[10]={0};
	cJSON *VdsState = cJSON_GetObjectItem(runStateJson, "VdsState");
	if(cJSON_HasObjectItem(VdsState, "GnssStatus")){
		intTemp = cJSON_GetObjectItem(VdsState,"GnssStatus")->valueint;
	}

	switch (intTemp)
	{
		case 130:
			intTemp = 6;
			break;
		case 131:
		case 141:
			intTemp = 0;
			break;
		case 140:
			intTemp = 4;
			break;
		default:
			break;
	}

	/*转换成字符串类型*/
	cJSON *mcJsonRun = NULL;
	mcJsonRun = cJSON_CreateObject();
	int frametype = 0x7101;//29441
	rsctl = (rsctl >= 0xFFFF) ? 1 : (rsctl + 1);
	char utc[50] = {0};
	utcFunc(utc);

	cJSON_AddNumberToObject(mcJsonRun,"frametype",frametype);
	cJSON_AddNumberToObject(mcJsonRun,"rsctl",rsctl);

	cJSON_AddNumberToObject(mcJsonRun, "gnssStatus", intTemp);
	cJSON_AddStringToObject(mcJsonRun, "utc", utc);

	memset(strTemp, 0, sizeof(strTemp));
	cJSON *HardwareState = cJSON_GetObjectItem(runStateJson, "HardwareState");
	if(cJSON_HasObjectItem(HardwareState, "SOCTemp")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(HardwareState,"SOCTemp")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "obuTemp", strTemp);

	memset(strTemp, 0, sizeof(strTemp));
	if(cJSON_HasObjectItem(HardwareState, "CpuUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(HardwareState,"CpuUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "cpuUsage", strTemp);

	memset(strTemp, 0, sizeof(strTemp));
	if(cJSON_HasObjectItem(HardwareState, "MemoryUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(HardwareState,"MemoryUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "memUsage", strTemp);

	memset(strTemp, 0, sizeof(strTemp));
	if(cJSON_HasObjectItem(HardwareState, "DiskUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(HardwareState,"DiskUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "diskUsage", strTemp);


	cJSON_AddNumberToObject(mcJsonRun, "V2XState", 0);
	cJSON_AddNumberToObject(mcJsonRun, "State4G", 0);

	memset(strTemp, 0, sizeof(strTemp));//因为cpu,mem都是保留两位小数，所以不必每次都memset

	cJSON *VDSCpuMem = cJSON_GetObjectItem(runStateJson, "VDSCpuMem");
	if(cJSON_HasObjectItem(VDSCpuMem, "CpuUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(VDSCpuMem,"CpuUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "vdsCpuUsage", strTemp);

	if(cJSON_HasObjectItem(VDSCpuMem, "MemoryUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(VDSCpuMem,"MemoryUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "vdsMemUsage", strTemp);

	cJSON *NETCpuMem = cJSON_GetObjectItem(runStateJson, "NETCpuMem");
	if(cJSON_HasObjectItem(NETCpuMem, "CpuUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(NETCpuMem,"CpuUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "netCpuUsage", strTemp);

	if(cJSON_HasObjectItem(NETCpuMem, "MemoryUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(NETCpuMem,"MemoryUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "netMemUsage", strTemp);

	cJSON *V2XCpuMem = cJSON_GetObjectItem(runStateJson, "V2XCpuMem");
	if(cJSON_HasObjectItem(V2XCpuMem, "CpuUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(V2XCpuMem,"CpuUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "v2xCpuUsage", strTemp);

	if(cJSON_HasObjectItem(V2XCpuMem, "MemoryUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(V2XCpuMem,"MemoryUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "v2xMemUsage", strTemp);

	cJSON *APPCpuMem = cJSON_GetObjectItem(runStateJson, "APPCpuMem");
	if(cJSON_HasObjectItem(APPCpuMem, "CpuUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(APPCpuMem,"CpuUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "appCpuUsage", strTemp);
	if(cJSON_HasObjectItem(APPCpuMem, "MemoryUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(APPCpuMem,"MemoryUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "appMemUsage", strTemp);

	cJSON *SYSCpuMem = cJSON_GetObjectItem(runStateJson, "SYSCpuMem");
	if(cJSON_HasObjectItem(SYSCpuMem, "CpuUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(SYSCpuMem,"CpuUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "sysCpuUsage", strTemp);
	if(cJSON_HasObjectItem(SYSCpuMem, "MemoryUsage")){
		sprintf(strTemp,"%s", cJSON_GetObjectItem(SYSCpuMem,"MemoryUsage")->valuestring);
	}
	cJSON_AddStringToObject(mcJsonRun, "sysMemUsage", strTemp);

	if(runStateJson != NULL)
		cJSON_Delete(runStateJson);

	//直接赋值给sendDataToserver，会出现问题。
	char *buf_run = cJSON_Print(mcJsonRun);
	if(mcJsonRun != NULL)
		cJSON_Delete(mcJsonRun);

	cJSON_Minify(buf_run);//去除格式
	int len = strlen(buf_run);

	char buf_temp[1024*5] = {0};
	strcpy(buf_temp, buf_run);

	free(buf_run);

	sendDataToServer(buf_temp, len);
}


/*根据平台下发的请求查看数据类型，并在线配置查询并反馈*/
void OnlineConfigSelectResponese(int type)
{
	//根据type类型，进行查找反馈不同数据。
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," ConfigSelectResponese type = %d", type);

	/*转换成字符串类型*/
	cJSON *mcJson = NULL;
	mcJson = cJSON_CreateObject();
	int frametype = 0x8302;//33538
	rsctl = (rsctl >= 0xFFFF) ? 1 : (rsctl + 1);
	char utc[50] = {0};
	utcFunc(utc);

	cJSON_AddNumberToObject(mcJson,"frametype",frametype);
	cJSON_AddNumberToObject(mcJson,"rsctl",rsctl);
	cJSON_AddStringToObject(mcJson, "utc", utc);
	cJSON_AddNumberToObject(mcJson,"respInquireType",type);

	cJSON *data = cJSON_AddObjectToObject(mcJson, "data");

	if(type == 0)//VDS 配置参数
	{
		onlineSelectConfig_VDShandle(data);
	}
	else if( type == 1)//场景算法配置参数
	{
		onlineSelectConfig_APPhandle(data);
	}
	else if( type == 2)//V2X协议栈配置参数
	{
		onlineSelectConfig_V2Xhandle(data);
	}

	char *buf = cJSON_Print(mcJson);

	if(mcJson != NULL)
		cJSON_Delete(mcJson);

	cJSON_Minify(buf);//去除格式
	int len = strlen(buf);

	/*添加中间变量为了进行释放*/
	char buf_temp[2048] = {0};
	strcpy(buf_temp, buf);

	free(buf);
	
	sendDataToServer(buf_temp, len);
}


/*在线配置设置*/
void OnlineSetConfig(int type, void *cjsonStr)
{
	int cfgResult = 0;//表示是否设置成功与否 0：成功 1：失败
	/*
	在线配置操作
	*/
	if(type == 0)      //vds配置参数
	{
		cfgResult = onlineSetConfig_VDShandle(cjsonStr);
	}
	else if(type == 1) //场景算法配置参数
	{
		cfgResult = onlineSetConfig_APPhandle(cjsonStr);
	}
	else if(type == 2) //V2X协议栈配置参数
	{
		cfgResult = onlineSetConfig_V2Xhandle(cjsonStr);
	}
	
	//反馈在线设置结果
	OnlineSetConfigResponse(type, cfgResult);
}

/*在线配置设置反馈*/
void OnlineSetConfigResponse(int type, int cfgResult)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," OnlineSetConfigResponse type = %d, cfgResult = %d", type, cfgResult);

	/*转换成字符串类型*/
	cJSON *mcJson = NULL;
	mcJson = cJSON_CreateObject();
	int frametype = 0x8304;//33540
	rsctl = (rsctl >= 0xFFFF) ? 1 : (rsctl + 1);
	char utc[50] = {0};
	utcFunc(utc);

	cJSON_AddNumberToObject(mcJson,"frametype",frametype);
	cJSON_AddNumberToObject(mcJson,"rsctl",rsctl);
	cJSON_AddStringToObject(mcJson, "utc", utc);
	cJSON_AddNumberToObject(mcJson,"respSetType",type);
	cJSON_AddNumberToObject(mcJson,"cfgResult",cfgResult);
	
	char *buf = cJSON_Print(mcJson);
	cJSON_Minify(buf);//去除格式
	int len = strlen(buf);

	/*添加中间变量为了进行释放*/
	char buf_temp[2048] = {0};
	strcpy(buf_temp, buf);

	free(buf);
	if(mcJson != NULL)
		cJSON_Delete(mcJson);

	sendDataToServer(buf_temp, len);
}

/*远程在线重启OBU设备*/
void rebootOBU(int Status)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," remote request rebootOBU Status = %d", Status);
	if(Status == 1)
	{
		/*转换成字符串类型*/
		cJSON *mcJson = NULL;
		mcJson = cJSON_CreateObject();
		int frametype = 0x9002;//36866

		cJSON_AddNumberToObject(mcJson,"frametype",frametype);
		cJSON_AddNumberToObject(mcJson,"Status",1);

		char *buf = cJSON_Print(mcJson);
		cJSON_Minify(buf);//去除格式
		int len = strlen(buf);

		/*添加中间变量为了进行释放*/
		char buf_temp[1024] = {0};
		strcpy(buf_temp, buf);

		free(buf);
		if(mcJson != NULL)
			cJSON_Delete(mcJson);

		sendDataToServer(buf_temp, len);
		
		//反馈远程在线重启请求之后 1s进行OBU 设备重启。
		sleep(5);
		system("reboot");
	}
}


/*创建初始化timer,用于100ms上传自车信息*/
void initTimer()
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," -initTimer start-!\n");
	timer_t timerid; 
    struct sigevent evp; 
    memset(&evp, 0, sizeof(struct sigevent));       //清零初始化 
 
    evp.sigev_value.sival_int = 1;                //也是标识定时器的，回调函数可以获得 
    evp.sigev_notify = SIGEV_THREAD;                //线程通知的方式，派驻新线程 
    evp.sigev_notify_function = getCarMsg;          //线程函数地址 
 
    if (timer_create(CLOCK_REALTIME, &evp, &timerid) == -1) 
    {   
        perror(" -fail to timer_create-"); 
        exit(-1); 
    }
 
    /* 第一次间隔it.it_value这么长,以后每次都是it.it_interval这么长,就是说it.it_value变0的时候会>装载it.it_interval的值 */
    struct itimerspec it; 
    it.it_interval.tv_sec = 5;    // 回调函数执行频率为5s运行1次
    it.it_interval.tv_nsec = 0; 
    it.it_value.tv_sec = 1;       // 倒计时3秒开始调用回调函数
    it.it_value.tv_nsec = 0; 
 
    if (timer_settime(timerid, 0, &it, NULL) == -1) 
    {   
        perror(" -fail to timer_settime-"); 
        exit(-1); 
    }
}

/*5s一次获取car相关信息*/
void getCarMsg()//union sigval v
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," -getCarMsg start!");
	GetPrivateProfileString("ObuBaseInfo", "ObuSN", "0123456789123456", mselfCarMsg.mSN, sizeof(mselfCarMsg.mSN), NET_Config_OBUInfo_Path);
	GetConfigIntValue(DYNAMICINFO_Config_Path, "VdsState", "GnssStatus", &mselfCarMsg.gnssStatus);
	switch (mselfCarMsg.gnssStatus)
	{
		case 130:
			mselfCarMsg.gnssStatus = 6;
			break;
		case 131:
		case 141:
			mselfCarMsg.gnssStatus = 0;
			break;
		case 140:
			mselfCarMsg.gnssStatus = 4;
			break;
		default:
			mselfCarMsg.gnssStatus = 0;
			break;
	}
}

/*自车信息上传*/
void selfCarMsg()
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," ownerCarMsg start!\n");
	while (1)
	{
		usleep(100000);//延迟100ms更新一次
		/*转换成字符串类型*/
		cJSON *mcJson = cJSON_CreateObject();
		int frametype = 0x7001;//28637
		mselfCarMsg.mrsctl = (mselfCarMsg.mrsctl >= 0xFFFF) ? 1 : (mselfCarMsg.mrsctl + 1);
		char utc[50] = {0};
		utcFunc(utc);

		//设置基本信息
		cJSON_AddNumberToObject(mcJson,"frametype",frametype);
		cJSON_AddNumberToObject(mcJson,"rsctl",rsctl);
		cJSON_AddStringToObject(mcJson, "utc", utc);
		cJSON_AddStringToObject(mcJson, "SN", mselfCarMsg.mSN);
		cJSON_AddNumberToObject(mcJson, "gnssStatus", mselfCarMsg.gnssStatus);

		//缺少自车信息
		/*
		code
		*/

		char *buf = cJSON_Print(mcJson);
		cJSON_Minify(buf);//去除格式

		int ret = libwebsocket_write(wsi, buf, strlen(buf), LWS_WRITE_TEXT);
		
		LogPrint(LOG_LEVEL_INFO,MODULE_NAME," ownerCarMsg send success!\n");
	}
}

//请求升级模组配置软件版本
void updateModuleConfig(int type)
{
	LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME," request update module config type = %d", type);
	system("systemctl stop cv2x");
	sleep(1);
	if(type == 1){
		system("cv2x-config --update-config-file /mnt/APP/Config/v2x_sikua.xml");
		WritePrivateProfileInt("MsgFrameConfig", "MsgFrameVersion", 4, V2X_ProtocolStack_Path);
	}
	else if(type == 2){
		system("cv2x-config --update-config-file /mnt/APP/Config/v2x_newsikua.xml");
		WritePrivateProfileInt("MsgFrameConfig", "MsgFrameVersion", 5, V2X_ProtocolStack_Path);
	}
	sleep(1);
	system("systemctl start cv2x");
	sleep(5);
	system("reboot");
}


/*发送数据到服务器*/
int sendDataToServer(const char *buf, int buflen)
{
	if(connect_Sts)
	{//发送请求注册数据
		// LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME," sendDataToServer send buf  = %s", buf);
		int ret = 0;
		ret = libwebsocket_write(wsi, (uint8_t*)buf, buflen, LWS_WRITE_TEXT);
	}
	else
	{
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME," sendDataToServer websocket not connect,so can't send data!");
	}
	
}

/*时间戳获取*/
void utcFunc(const char *str)
{
	struct timeval tv;
    gettimeofday(&tv,NULL);
    
	sprintf(str, "%ld" , tv.tv_sec);
	// LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "utcFunc() send data time utc = %s\n", str);
}




