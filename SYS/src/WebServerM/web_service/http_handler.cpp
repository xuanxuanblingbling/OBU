#include "http_handler.h"


unsigned char g_nSeqNum = 0;

void RegisterHttpHandler(HttpServer *p_pHttpServer)
{
	//DataDemoHandler(p_pHttpServer);

	AddUserAuthenHandler(p_pHttpServer);

	AddUserManageHandler(p_pHttpServer);

	AddSystemUpdateHandler(p_pHttpServer);

	AddSystemStatusHandler(p_pHttpServer);

	AddDeviceSettingHandler(p_pHttpServer);

	AddCertificateHandler(p_pHttpServer);

	AddFileBroswerHandler(p_pHttpServer);

	AddSecureSystemHandler(p_pHttpServer);

	AddUserInfoHandler(p_pHttpServer);

	AddBackUpSystemHandler(p_pHttpServer);

}


void DownloadFile(struct mg_connection* p_pConn, struct http_message* p_pHttpMsg, string p_strFile, string p_strName)
{
	string mine_type = "application/octet-stream";
	string l_extraHeader = "Content-Disposition: attachment; filename=" + p_strName;
	mg_http_serve_file(p_pConn, p_pHttpMsg, p_strFile.c_str(), mg_mk_str(mine_type.c_str()), mg_mk_str(l_extraHeader.c_str()));
}