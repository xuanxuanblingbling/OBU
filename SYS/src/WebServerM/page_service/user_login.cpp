#include "../web_service/http_handler.h"
#include "../web_service/user_info.h"


void UserLoginToken(struct mg_connection* p_pConn, struct http_message* p_pHttpMsg, void *p_vData)
{
	json l_jReqData;
	string l_strData;
	HttpServer *p_cHttpServer = (HttpServer *)p_vData;
	l_jReqData["token"] = p_cHttpServer -> m_cSessionManage->CreateWebToken(GetRemoteIpAddress(p_pConn));
	l_strData = l_jReqData.dump();
	HttpSendResponse(p_pConn, 200, "json", l_strData, "");
}


// 用户登录验证
void UserLoginAuthentication(struct mg_connection* p_pConn, struct http_message* p_pHttpMsg, HttpServer* p_pHttpServer)
{
	json l_jReqData, l_jResData;
	Session l_LoginInfo;
	string l_strIpAddr = GetRemoteIpAddress(p_pConn);
	HttpServer* l_pHttpServer = (HttpServer*)p_pHttpServer;
	UserInfo l_cUserInfo;
	l_LoginInfo.m_cIpAddress = l_strIpAddr;
	try
	{
		l_jReqData = json::parse(string(p_pHttpMsg->body.p, p_pHttpMsg->body.len));  // 解析Json对象的内容
		l_LoginInfo.m_strUserName = l_jReqData["username"].get<string>();
		l_LoginInfo.m_strUserPassWd = l_jReqData["password"].get<string>();
		l_LoginInfo.m_strWebToken = l_jReqData["webtoken"].get<string>();
		l_LoginInfo.m_strDynamicCode = l_jReqData["dynamiccode"].get<string>();
	}
	catch(exception &e)
	{
		cout << "User Login Authentication Parse Error!"<<e.what() << endl;
		return HttpSendResponse(p_pConn,500 , "json", "", "");
	}
	l_cUserInfo = GetUserInfo(l_LoginInfo.m_strUserName);
	cout << "l_cUserInfo.m_nUserId:" << l_cUserInfo.m_nUserId << endl;
	if (l_cUserInfo.m_nUserId < 0)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver User %d does not exist", l_cUserInfo.m_nUserId);
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("用户名不存在!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	string l_strKey = l_LoginInfo.m_cIpAddress + l_LoginInfo.m_strUserName, l_strMsg;
	if (!l_pHttpServer->m_cSessionManage->UserLoginCtrl(l_strKey, l_strMsg, false))
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv(l_strMsg);
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	l_LoginInfo.m_nUserId = l_cUserInfo.m_nUserId;
	l_LoginInfo.m_AuthenMask = GetUserRoleMask(l_cUserInfo.m_strRole, l_pHttpServer->m_cRBACManage->m_RoleList);

	string l_ErrorMsg;
	bool l_bRet = l_pHttpServer->m_cSessionManage->UserAuthentication(l_LoginInfo, l_ErrorMsg);
	if (!l_bRet)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Login error !");
		l_pHttpServer->m_cSessionManage->UserLoginCtrl(l_strKey, l_strMsg, true);
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv(l_ErrorMsg + l_strMsg);
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	else
	{
		l_jResData["sessionid"] = l_LoginInfo.m_strSessionID;
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
	}
}

void UserInfoOperation(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	UserInfo l_vUserInfo, l_oUerInfo;
	json l_jReqData, l_jResData;
	int l_nld;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strOpt = GetHttpUrlQuery(l_pHttpMsg, "op");
	string l_strSessionId = GetRequestSessionId(l_pHttpMsg);
	HttpServer* l_HttpServer = ((HttpServer*)p_vData);
	Session *l_Session = l_HttpServer->m_cSessionManage->GetSession(l_strSessionId);
	if (l_Session == NULL)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("当前用户信息不存在!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	l_nld = l_Session->m_nUserId;

	if (l_strOpt == "set")
	{
		try{
			l_jReqData = json::parse(string(l_pHttpMsg->body.p, l_pHttpMsg->body.len));
			l_vUserInfo = l_jReqData;

		}
		catch (...)
		{
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("解析用户信息失败!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
		l_oUerInfo = GetUserInfo(l_nld);
		l_vUserInfo.m_nUserId = l_oUerInfo.m_nUserId;
		l_vUserInfo.m_cStatus = l_oUerInfo.m_cStatus;
		l_vUserInfo.m_strPassWd = l_oUerInfo.m_strPassWd;
		l_vUserInfo.m_strRole = l_oUerInfo.m_strRole;
		if (!UpdateUserInfo(l_vUserInfo))
		{
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("保存用户信息失败!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
		l_jResData["result"] = "sucess";
		l_jResData["message"] = sconv("修改用户信息成功!");
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");

	}
	else
	{
		l_vUserInfo = GetUserInfo(l_nld);
		if (!CheckUserClass(l_vUserInfo, l_HttpServer->m_cRBACManage->m_RoleList))
			UpdateUserInfo(l_vUserInfo);
		l_vUserInfo.m_strPassWd = "";
		json l_jReqData = l_vUserInfo;
		HttpSendResponse(p_pConn, 200, "json", l_jReqData.dump(), "");

	}
}

void ModifyUserPassword(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	UserInfo l_oUerInfo;
	json l_jReqData, l_jResData;
	int l_nld;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strSessionId = GetRequestSessionId(l_pHttpMsg);
	HttpServer* l_HttpServer = ((HttpServer*)p_vData);
	Session *l_Session = l_HttpServer->m_cSessionManage->GetSession(l_strSessionId);
	if (l_Session == NULL)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("当前用户信息不存在!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	l_nld = l_Session->m_nUserId;
	string l_SessionKey = l_Session->m_strSessionKey;
	string l_strOldPw, l_strNewPw, l_strConfPw;

	try {
		l_jReqData = json::parse(string(l_pHttpMsg->body.p, l_pHttpMsg->body.len));
		l_strOldPw = GetJsonStringData(l_jReqData, "oldPw");
		l_strOldPw = AesDecryptCBC(l_strOldPw, l_SessionKey);
		l_strNewPw = GetJsonStringData(l_jReqData, "newPw");
		l_strConfPw =GetJsonStringData(l_jReqData, "confirmPw");
		if (l_strNewPw != l_strConfPw)
		{
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("用户的密码和确认密码不一致!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}
	catch (...)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("解析用户信息失败!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	l_strNewPw = AesDecryptCBC(l_strConfPw, l_SessionKey);
	l_oUerInfo = GetUserInfo(l_nld);
	if (l_oUerInfo.m_strPassWd != l_strOldPw)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("用户的旧密码输入错误!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	l_oUerInfo.m_strPassWd = l_strNewPw;
	UpdateUserInfo(l_oUerInfo);
	l_jResData["result"] = "success";
	l_jResData["message"] = sconv("修改用户的密码成功!");
	HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
}


// 写一个获取用户名和用户Id的函数 然后注册
void AddUserInfoHandler(HttpServer *p_cHttpServer)
{
	p_cHttpServer->AddHttpRequestHandler("/user/info/basic",
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			json l_jResData;
			HttpServer* l_pHttpServer = (HttpServer*)p_vData;
			struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
			string l_strSession = GetRequestSessionId(l_pHttpMsg);
			Session* l_pSession = NULL;
			l_pSession = l_pHttpServer->m_cSessionManage->GetSession(l_strSession);
			if (l_pSession == NULL)
			{
				l_jResData["result"] = "error";
				l_jResData["message"] = sconv("当前用户信息不存在");
				HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
			}
			else
			{
				l_jResData["id"] = l_pSession->m_nUserId;
				l_jResData["name"] = l_pSession->m_strUserName;
				HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
			}
		}, 0, 0xFFFFFFFF, "返回登录用户的基础信息" });
	p_cHttpServer->AddHttpRequestHandler("/user/login/logout",
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			HttpServer* l_pHttpServer = (HttpServer*)p_vData;
			struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
			string l_strSession = GetRequestSessionId(l_pHttpMsg);
			l_pHttpServer->m_cSessionManage->DeleteSession(l_strSession);
			return HttpSendRedirect(p_pConn, 301, "page/login.html", "");
		},0,0xFFFFFFFF,"退出当前登录状态" });

	p_cHttpServer->AddHttpRequestHandler("/user/info/info", { UserInfoOperation,0,0,"查询和修改用户个人信息" });
	p_cHttpServer->AddHttpRequestHandler("/user/info/modifyPassWd", { ModifyUserPassword,0,0,"用户修改个人密码" });

}



