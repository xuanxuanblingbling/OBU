#pragma once

#include "http_server.h"
#include <vector>
#include <set>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../common/web_common.h"
#include "../common/string_conv.h"
#include "../common/jsonExtent.h"
#include "../extern/mongoose/mongoose.h"




#ifdef _WIN32
#define FILEACCESS  _access
#else
#define FILEACCESS  eaccess
#endif // _WIN32

//升级状态文件
#define  Update_Scrip       "/mnt/APP/Scripts/V2XAPP_UpdateFile.sh"
#define  Update_StateFile   "/mnt/Update/UpdateProcess/Config_Update.ini"

extern unsigned char g_nSeqNum;

#define GenerWebSign "WBE-" + to_string(g_nSeqNum++)

bool JsonDataToIni(const json &p_jData, std::vector<std::string> &p_vSection, CSimpleIniA &p_iniFile);

void FileBrowserProc(struct mg_connection* p_pConn, struct http_message* p_pHttpMsg, string p_strRoot);

void ProcTcpSendDataExtent(struct mg_connection* p_pConn, string &p_strJson, int p_nClientNum, HttpServer * p_pHttpServer, json &p_jData);

void ProcTcpSendData(struct mg_connection* p_pConn, string &p_strContent, int p_nClientNum, HttpServer * p_pHttpServer);

void TcpClientThread(void);

bool GetJsonDataFromFile(int p_nJsonNum, HttpServer * p_pHttpServer);

void ProcJsonDataRequest(struct mg_connection* p_pConn, int p_nJsonNum, std::vector<std::string> &p_vSection, json &p_jData, HttpServer * p_pHttpServer);

void ProcDataRequestStatic(struct mg_connection* p_pConn, int p_nJsonNum, std::vector<std::string> &p_vSection, json &p_jData, HttpServer * p_pHttpServer);

void MonitorProcJsonDataRequest(struct mg_connection* p_pConn, void* p_pHttpMsg, int p_nJsonNum, std::vector<std::string> &p_vSection, json &p_jData, HttpServer * p_pHttpServer);

void RegisterHttpHandler(HttpServer *p_pHttpServer);

void AddUserAuthenHandler(HttpServer *p_pHttpServer);

void AddUserManageHandler(HttpServer *p_pHttpServer);

void AddSystemUpdateHandler(HttpServer *p_pHttpServer);

void AddSystemStatusHandler(HttpServer *p_pHttpServer);

void DataDemoHandler(HttpServer *p_cHttpServer);

void AddDeviceSettingHandler(HttpServer* p_cHttpServer);

void AddCertificateHandler(HttpServer *p_pHttpServer);

void AddFileBroswerHandler(HttpServer *p_cHttpServer);

void AddSecureSystemHandler(HttpServer* p_cHttpServer);

void AddUserInfoHandler(HttpServer *p_cHttpServer);

void AddBackUpSystemHandler(HttpServer* p_cHttpServer);

void FileUploadHandler(struct mg_connection* p_pConn, int p_sEventStatus, void* p_pEventData, void* p_pHttpServer);

void UserLoginToken(struct mg_connection* p_pConn, struct http_message* p_pHttpMsg, void *p_vData);

// 用户登录验证
void UserLoginAuthentication(struct mg_connection* p_pConn, struct http_message* p_pHttpMsg, HttpServer *p_pHttpServer);

void DownloadFile(struct mg_connection* p_pConn, struct http_message* p_pHttpMsg, string p_strFile, string p_strName);

void ProcJsonDataSetting(struct mg_connection* p_pConn, int p_nJsonNum, std::vector<std::string> &p_vSection, json &p_jData, HttpServer * p_pHttpServer);

void ProcJsonDataSetToStruct(struct mg_connection* p_pConn, int p_nJsonNum, json &p_jData, HttpServer * p_pHttpServer);

bool SetJsonDataToFile(int p_nJsonNum, json &p_jData, HttpServer * p_pHttpServer);

bool SaveSetParamJsonToFile(const string &p_strFileName, int p_FileType, int p_nJsonNum, json &p_jData,  HttpServer * p_pHttpServer);

bool GetDirList(std::string p_strPath, std::map<string, struct stat> &p_mapList);
//升级 模块用
void ProcInitDataRequest(struct mg_connection* p_pConn, string p_strFileName, std::vector<std::string> &p_vSection, json &p_jResData);

/*升级V2X模组软件，即是四跨还是新四跨*/
void updateModuleConfig(struct mg_connection* p_pConn, json &p_jData, int type);