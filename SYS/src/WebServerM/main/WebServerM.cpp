#include "../web_service/http_handler.h"
#include "../web_service/rbac_manage.h"
#include "../web_service/session_manage.h"
#include "../web_service/user_info.h"
#include <future>
#include <thread>
#include <chrono>
#include <signal.h>

using namespace std;

void WebServer_Main()
{
	HttpServer l_cHttpServer;
	struct mg_mgr l_sWebMgr;
	struct mg_connection *l_sMgConn;
	WebConfigParam l_cWebConfig;

	WebConfigInit(l_cWebConfig);
	InitUserInfoStorage();
	RbacManage l_cRbacManage("/mnt/APP/Config/obu/sysm/WebServerM/config/Authen.json");
	SessionManage l_cSessionManage(l_cWebConfig.m_nTokenTimeOut, l_cWebConfig.m_nSessionTimeOut);

    // Set Http Param
	l_cHttpServer.m_strPort = std::to_string(l_cWebConfig.m_nWebPort);
	l_cHttpServer.m_cRBACManage = &l_cRbacManage;
	l_cHttpServer.m_cSessionManage = &l_cSessionManage;
	l_cHttpServer.m_cWebConfig = &l_cWebConfig;
	l_cHttpServer.m_sPollTime = 500;
	l_cHttpServer.m_sServerOpts.document_root = "/mnt/APP/Config/obu/sysm/WebServerM/web";

	RegisterHttpHandler(&l_cHttpServer);
	for (auto &l_tData : l_cHttpServer.m_mapUriProc)
	{
		if(l_tData.second.m_nUriAuthen != 0xFFFFFFFF)
			l_cRbacManage.m_UriList.insert(l_tData.first);
	}
	l_cRbacManage.RestoreFromeFile();

	mg_mgr_init(&l_sWebMgr, NULL);
	l_sMgConn = mg_bind(&l_sWebMgr, l_cHttpServer.m_strPort.c_str(),HttpEventHandler, (void *)&l_cHttpServer);
	if (l_sMgConn == NULL)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver bing failure");
		//return 1;
	}
		
	mg_set_protocol_http_websocket(l_sMgConn);
	mg_register_http_endpoint(l_sMgConn, "/upload", FileUploadHandler, (void *)&l_cHttpServer);
	cout << "服务器启动成功!端口:" + l_cHttpServer.m_strPort << endl;

	for (;;) {
		mg_mgr_poll(&l_sWebMgr, l_cHttpServer.m_sPollTime);
		//cout<< "this is the for addr" <<endl;
		l_cHttpServer.m_cSessionManage->SessionTokenFresh();
		l_cHttpServer.UpdateHttpAuthen();

	}

	mg_mgr_free(&l_sWebMgr);
	//return 0;
}

