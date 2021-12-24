#include "http_handler.h"

/*
bool HttpServerRegisterEndPoint(HttpServer *p_pHttpServer, string p_strURI, mg_event_handler_t p_hHandler)
{
	if (p_pHttpServer->m_setEndPointURI.find(p_strURI) != p_pHttpServer->m_setEndPointURI.end())
		return false;
	p_pHttpServer->m_setEndPointURI.insert(p_strURI);
	mg_register_http_endpoint(p_pHttpServer->m_pConnect, p_strURI.c_str(), p_hHandler MG_UD_ARG(NULL));
	return true;
}
*/

HttpServer::HttpServer()
{
	m_sJsonSet.resize(JSON_WEBNUM);
	m_sServerOpts.cgi_file_pattern = NULL;
	m_sServerOpts.ip_acl = NULL;
	m_sServerOpts.per_directory_auth_file = NULL;
	m_sServerOpts.global_auth_file = NULL;
	m_sServerOpts.hidden_file_pattern = NULL;
	m_sServerOpts.ssi_pattern = NULL;
	m_sServerOpts.extra_headers = NULL;
	m_sServerOpts.enable_directory_listing = "no";
	m_sServerOpts.url_rewrites = NULL;
	m_sServerOpts.auth_domain = "domain";
	m_sServerOpts.custom_mime_types = NULL;
	m_sServerOpts.ssi_pattern = NULL;
	m_sServerOpts.index_files = "login.html";
}


HttpServer::~HttpServer()
{
	
}


bool HttpServer::AddHttpRequestHandler(string p_strUri, URI_Handler p_hHandler)
{
	string l_strUri = MakeURINorm(p_strUri);
	if (m_mapUriProc.find(l_strUri) != m_mapUriProc.end())
		return false;
	m_mapUriProc.insert(make_pair(l_strUri, p_hHandler));
	return true;
}

void HttpServer::DelHttpRequestHandler(string p_strUri)
{
	string l_strUri = MakeURINorm(p_strUri);
	if (m_mapUriProc.find(l_strUri) != m_mapUriProc.end())
		m_mapUriProc.erase(p_strUri);
}

URI_Handler HttpServer::GetHttpRequestHandler(string p_strUri)
{
	auto l_aItera = m_mapUriProc.find(p_strUri);
	if (l_aItera == m_mapUriProc.end())
	{
		URI_Handler l_Proc = {NULL, 0, 0, "" };
		return l_Proc;
	}
	return l_aItera->second;
}

bool HttpServer::AddUploadPath(string p_strUri, string p_strPath)
{
	string l_strUri = MakeURINorm(p_strUri);
	string l_strPath = MakeURINorm(p_strPath);
#ifdef _WIN32
		l_strPath = l_strPath.substr(1, l_strPath.length() - 1);   // windows save the reletive path
		replace(l_strPath.begin(), l_strPath.end(), '/', '\\');
#endif
	if (m_mapUploadPath.find(l_strUri) != m_mapUploadPath.end())
		return false;
	m_mapUploadPath.insert(make_pair(l_strUri, l_strPath));
	return true;
}

void HttpServer::DelUploadPath(string p_strUri)
{
	string l_strUri = MakeURINorm(p_strUri);
	if (m_mapUploadPath.find(l_strUri) != m_mapUploadPath.end())
		m_mapUploadPath.erase(p_strUri);
}

string HttpServer::GetUploadPath(string p_strUri)
{
	auto l_aItera = m_mapUploadPath.find(p_strUri);
	if (l_aItera == m_mapUploadPath.end())
	{
		return "";
	}
	return l_aItera->second;
}


bool HttpServer::UserAuthentication(struct mg_connection *p_pConn, struct http_message *p_pHttpMsg, unsigned int &p_nUserMask)
{
	string l_strIpAddr, l_strSession;
	l_strIpAddr = GetRemoteIpAddress(p_pConn);
	if (l_strIpAddr.empty())                         // get ip address
		return false;
	l_strSession = GetRequestSessionId(p_pHttpMsg);  // get session id
	if (l_strSession.empty())
		return false;
	return m_cSessionManage->WebSessionAuthentication(l_strSession, l_strIpAddr, p_nUserMask);
}


void HttpServer::UpdateHttpAuthen(void)
{
	if (m_cRBACManage != NULL && (m_cRBACManage->m_UpdataFlag))
	{
		for (auto &l_tData : m_cRBACManage->m_UriAuthen)
		{
			auto l_aItera = m_mapUriProc.find(l_tData.first);
			if (l_aItera != m_mapUriProc.end())
				l_aItera->second.m_nRoleAuthen = l_tData.second;
		}
		m_cRBACManage->m_UpdataFlag = 0;
	}
}

void HttpEventHandler(struct mg_connection *p_pConn, int p_sEventFlag, void *p_pEventData, void *p_pHttpServer)
{
	unsigned int l_nMaskRead = 0x0000FFFF;
	unsigned int l_nMaskWrite = 0xFFFF0000;
	unsigned int l_nMaskRW = 0xFFFFFFFF;

	string l_strOpt;

	json l_jResData;
	string l_strURI;
	unsigned int l_nUserMask;
	int l_nURILen = 0;
	string l_strIpAddr = "", l_strSession = "";
	struct http_message *l_pHttpMsg = (struct http_message *) p_pEventData;


	HttpServer * l_pHttpServer = (HttpServer *)p_pHttpServer;
	URI_Handler l_pReqUriProc;
	switch (p_sEventFlag)
	{
	case MG_EV_HTTP_REQUEST:
		l_strURI = MakeURINorm(string(l_pHttpMsg->uri.p, l_pHttpMsg->uri.len));
		l_nURILen = l_strURI.length();
		cout << l_strURI << endl;


		if (l_strURI == "/")
			return HttpSendRedirect(p_pConn, 301, "page/login.html", "");

		if ((l_strURI.length() >= 4 && (!l_strURI.substr(0, 4).compare("/js/"))))  // 获取库文件
			return mg_serve_http(p_pConn, l_pHttpMsg, l_pHttpServer->m_sServerOpts);

		if (!l_strURI.compare("/page/login.html/") || !l_strURI.compare("/page/desktop.html/"))
			return mg_serve_http(p_pConn, l_pHttpMsg, l_pHttpServer->m_sServerOpts);

		if (!l_strURI.compare("/user/login/authen/"))  // 执行用户登录流程
			return UserLoginAuthentication(p_pConn, l_pHttpMsg, l_pHttpServer);

		if (!l_strURI.compare("/user/login/gettoken/"))
			return UserLoginToken(p_pConn, l_pHttpMsg, l_pHttpServer);

		if(!l_strURI.compare("/favicon.ico/"))
			return HttpSendRedirect(p_pConn, 301, "js/static/images/favicon.ico", "");

		// User Authentication
		l_strIpAddr = GetRemoteIpAddress(p_pConn);
		l_strSession = GetRequestSessionId(l_pHttpMsg);

		if(l_strIpAddr == "" || l_strSession == "")
			return HttpSendRedirect(p_pConn, 301, "/page/login.html", "");

		if (!l_pHttpServer->m_cSessionManage->WebSessionAuthentication(l_strSession, l_strIpAddr, l_nUserMask))
			return HttpSendRedirect(p_pConn, 301, "/page/login.html", "");

		if((l_nURILen > 6) && (!l_strURI.substr(l_nURILen - 6, 6).compare(".html/")))
			return mg_serve_http(p_pConn, l_pHttpMsg, l_pHttpServer->m_sServerOpts);

		l_strOpt = GetHttpUrlQuery(l_pHttpMsg, "op");
		cout << "op:" << l_strOpt << endl;
		if (!l_strOpt.compare("query"))
		{
			l_nUserMask &= l_nMaskRead;
		}
		else if (!l_strOpt.compare("set"))
		{
			l_nUserMask &= l_nMaskWrite;
		}
		else
		{
			l_nUserMask &=l_nMaskRW;
		}
		cout << "l_nUserMask: 0x" << hex << l_nUserMask << endl;

		l_pReqUriProc = l_pHttpServer->GetHttpRequestHandler(l_strURI);
		if (!((l_pReqUriProc.m_nRoleAuthen & l_nUserMask) | l_pReqUriProc.m_nUriAuthen))
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver http request is not authorized");
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("当前请求未授权");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}

		if (l_pReqUriProc.m_Hanlder != NULL)
			l_pReqUriProc.m_Hanlder(p_pConn, p_sEventFlag, l_pHttpMsg, p_pHttpServer);  // 调用系统注册的函数
		else
			HttpSendError(p_pConn, 404, "");
		break;
	case MG_EV_HTTP_PART_BEGIN:  // 防止无意义的分部传输
	case MG_EV_HTTP_PART_DATA:
	case MG_EV_HTTP_PART_END:
	case MG_EV_HTTP_MULTIPART_REQUEST_END:  // 文件传输完成
		p_pConn->flags = MG_F_CLOSE_IMMEDIATELY;
		break;

	}
}


