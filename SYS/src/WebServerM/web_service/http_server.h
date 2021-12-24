#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "session_manage.h"
#include "rbac_manage.h"
#include "../extern/mongoose/mongoose.h"
#include <set>
#include "../extern/iniparse/SimpleIni.h"
#include <condition_variable>


#include "wj_log.h"
#include "CfgM.h"

typedef struct _WebJson
{
	json data;
	long mtime;
}WebJson;


typedef struct _WebConfigParam
{
	unsigned short m_nWebPort;                 // WEB服务器的端口
	unsigned short m_nIpcPort;
	unsigned short m_nIpcTimeOut;
	unsigned int  m_nSessionTimeOut;
	unsigned int m_nTokenTimeOut;
	string m_strStaticInfoFile;
	string m_strDynamicInfoFile;
	string m_strDevFaultInfoFile;
	string m_strProtocolInfoFile;
	string m_strCertInfoFile;
	string m_strAppUpdatePath;
	string m_strAppUpdateInfoFile;
	vector<string> m_vAppUpdateCmd;
	string m_strAppUpdataShFile;
	string m_strCertUploadPath;
	string m_strLogFileRootPath;
	string m_strDataBaseRootPath;
	string m_strSoftWareRootPath;
	string m_strConfigFileRootPath;
	string m_strCertFileRootPath;
	string m_strBackupRootPath;
	string m_strSysBackupPath;
	string m_strFileUploadPath;
	string m_strIpAclConfigFile;
	string m_strDevTestWriteFile;
	string m_strDevTestReadFile;
	string m_strDevTestShellFile;
	string m_strBackUpSetConfigFile;
	string m_strBackUpParamConfigFile;
	string m_strBasicInfoFile;
	string m_strV2XServiceFile;
	string m_strVDSModuleFile;
	string m_strMCUModuleFile;
	string m_strMsgMonitorFile;
	string m_strNetWorkModuleFile;
	string m_strAppASCfgFile;
	string m_strAppMMCfgFile;
	string m_strAppMTCfgFile;
	string m_strAppTLCfgFile;
	vector<string> m_vDevRsuTestCmd; 
	string m_strAppSetFile;
}WebConfigParam;

void WebConfigInit(WebConfigParam &p_sData);


#define JSON_WEBNUM        25    //注意值的范围，vector

#define JSON_DEVSTATIC      0
#define JSON_DEVDYNAMIC     1
#define JSON_PROTOCOL       2
#define JSON_CERTICATE      3

#define JSON_UPDATAINFO     7



#define JSON_APPASCFG      8
#define JSON_APPMMCFG      9
#define JSON_APPMTCFG      10
#define JSON_APPTLCFG      11

#define JSON_DEVFAULT       12
#define JSON_IPACL          13
#define JSON_DEVTESTREAD    14
#define JSON_DEVTESTWRITE   15
#define JSON_BACKUPSET      16
#define JSON_BACKUPPARAM    17

#define JSON_BASICINFO      18
#define JSON_V2XSERVICE     19
#define JSON_VDSMODULE      20
#define JSON_MCUMODULE      21
#define JSON_MSGMONITOR     22
#define JSON_NETWORKMODULE  23

#define JSON_APPSET 		24

#define JSON_MODULECONFIG   25

//APP参数配置
// #define JSON_APPTTC      24
// #define JSON_APPSEF      25
// #define JSON_APPMMP      26
// #define JSON_APPSBD      27
// #define JSON_APPGS       28
// #define JSON_APPST       29
// #define JSON_APPBP       30
// #define JSON_APPVBI      31
// #define JSON_APPGP       32





#define CLIENT_WEBNUM  1
#define CLIENT_MODULE  0

// typedef struct _WebTcpClient
// {
// 	unsigned short port;
// 	unsigned int timeout;
// 	tacopie::tcp_client *client;
// }WebTcpClient;


typedef void OnRspCallback(mg_connection *c, std::string);
using HttpRequestHandler = std::function<void(struct mg_connection *,int , void *, void *)>;

typedef struct _URI_PROC
{
	HttpRequestHandler m_Hanlder;
	unsigned int m_nRoleAuthen;          // 角色授权状态
	unsigned int m_nUriAuthen;           // 当前URI的授权方式
	string m_strDescrip;
}URI_Handler;



class HttpServer
{
public:
	//mg_mgr m_cMgr;
	string m_strPort = "8000";
	int m_sPollTime = 1000;
	struct mg_connection* m_pConnect = NULL;
	RbacManage* m_cRBACManage = NULL;
	SessionManage* m_cSessionManage = NULL;
	WebConfigParam *m_cWebConfig = NULL;
	vector<WebJson> m_sJsonSet;
	//vector<WebTcpClient> m_sTcpClient;
	mg_serve_http_opts m_sServerOpts;
	unordered_map<std::string, URI_Handler> m_mapUriProc;
	unordered_map<std::string, std::string> m_mapUploadPath;

public:
	HttpServer();
	~HttpServer();
	bool AddUploadPath(string p_strUri, string p_strPath);
	void DelUploadPath(string p_strUri);
	string GetUploadPath(string p_strUri);
	bool AddHttpRequestHandler(string p_strUri, URI_Handler p_hHandler);
	void DelHttpRequestHandler(string p_strUri);
	URI_Handler GetHttpRequestHandler(string p_strUri);
	void UpdateHttpAuthen(void);
	bool UserAuthentication(struct mg_connection *p_pConn, struct http_message *p_pHttpMsg, unsigned int &p_nUserMask);
};

void HttpEventHandler(struct mg_connection *p_pConn, int p_sEventFlag, void *p_pEventData, void *p_pHttpServer);

