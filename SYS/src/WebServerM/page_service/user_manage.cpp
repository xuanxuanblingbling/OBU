#include "../web_service/http_handler.h"
#include "../web_service/user_info.h"
#include "../common/jsonExtent.h"


void LoadUserInfoList(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	json l_jReqData;
	p_nEvent = p_nEvent;
	p_vData = p_vData;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	auto l_aStorage = GetUserInfoStorage(USER_INFO_DATABASE, USER_INFO_TABLE);
	vector<UserInfo> l_vUserInfo;
	l_jReqData["pageSize"] = 1;
	l_jReqData["pageNo"] = 1;
	l_jReqData["count"] = 1;

	for (auto &employee : l_aStorage.iterate<UserInfo>())
	{
		employee.m_strDesCription = "";
		employee.m_strPassWd = "";
		l_vUserInfo.push_back(employee);
	}
	l_jReqData["list"] = l_vUserInfo;
	HttpSendResponse(p_pConn, 200, "json", l_jReqData.dump(), "");
}

// 查询一个用户的信息
void QueryUserInfo(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	UserInfo l_vUserInfo;
	p_nEvent = p_nEvent;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	json l_jResData;
	HttpServer* l_HttpServer = ((HttpServer*)p_vData);
	int l_nId;
	try
	{
		l_nId = stoi(GetHttpUrlQuery(l_pHttpMsg, "userId"));
	}
	catch (...)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("操作用户不存在!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	l_vUserInfo = GetUserInfo(l_nId);
	if (!CheckUserClass(l_vUserInfo, l_HttpServer->m_cRBACManage->m_RoleList))
		UpdateUserInfo(l_vUserInfo);
	l_vUserInfo.m_strPassWd = "";
	json l_jReqData = l_vUserInfo;
	HttpSendResponse(p_pConn, 200, "json", l_jReqData.dump(), "");
}


// 增加用户的信息
void UserInfoEdit(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	json l_jResData;
	p_nEvent = p_nEvent;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	int l_nCode = 500, l_nId = -1;
	UserInfo l_vUserInfo;
	string location = "/page/security/manage_user_edit.html?";
	string l_strOp = GetHttpUrlQuery(l_pHttpMsg, "act");
	l_jResData["result"] = "error";
	l_jResData["message"] = sconv("操作用户不存在!");
	if (l_strOp == "edit" || l_strOp == "add")
	{
		map<string, char>& l_RoleList = ((HttpServer*)p_vData)->m_cRBACManage->m_RoleList;
		string l_strRole = "&role=";
		for (auto& l_tData : l_RoleList)
			l_strRole += UrlEncode(sconv(l_tData.first)) + ",";

		location += string(l_pHttpMsg->query_string.p, l_pHttpMsg->query_string.len) + l_strRole;   // send redirect
		return HttpSendRedirect(p_pConn, 301, location, "");
	}
	try {
		l_nId = stoi(GetHttpUrlQuery(l_pHttpMsg, "userId"));
		l_vUserInfo = GetUserInfo(l_nId);
		if (l_vUserInfo.m_nUserId < 0)
			return HttpSendResponse(p_pConn, l_nCode, "json", l_jResData.dump(), "");
	}
	catch (...) {
		return HttpSendResponse(p_pConn, l_nCode, "json", l_jResData.dump(), "");
	}

	if (l_vUserInfo.m_strName == "admin")
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Cannot modify administrator information");
		l_jResData["message"] = sconv("不允许编辑管理员用户信息!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	if (l_strOp == "enable")
	{
		l_vUserInfo.m_cStatus = 1;
		if (UpdateUserInfo(l_vUserInfo))
		{
			l_nCode = 200;
			l_jResData["message"] = sconv("用户启用成功!");
		}
		else
			l_jResData["message"] = sconv("用户启用失败!");
	}
	else if (l_strOp == "disable")
	{
		l_vUserInfo.m_cStatus = 0;
		if (UpdateUserInfo(l_vUserInfo))
		{
			l_nCode = 200;
			l_jResData["message"] = sconv("用户禁用成功!");
		}
		else
			l_jResData["message"] = sconv("用户禁用失败!");
	}
	else if (l_strOp == "delete")
	{
		if (DelUserInfo(l_nId))
		{
			l_nCode = 200;
			l_jResData["message"] = sconv("用户删除成功!");
		}
		else
			l_jResData["message"] = sconv("用户删除失败!");
	}
	else
	{
		l_jResData["message"] = sconv("操作失败!");
	}
	if (l_nCode == 200)
		l_jResData["result"] = "success";
	HttpSendResponse(p_pConn, l_nCode, "json", l_jResData.dump(), "");
}


void UserInfoModify(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	// TODO
	int l_nCode = 500;
	p_nEvent = p_nEvent;
	p_vData = p_vData;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	json l_jReqData, l_jResData;
	UserInfo l_vUserInfo, l_oUerInfo;
	l_jResData["result"] = "error";
	l_jResData["message"] = sconv("保存用户信息失败!");
	try
	{
		l_jReqData = json::parse(string(l_pHttpMsg->body.p, l_pHttpMsg->body.len));  // 解析Json对象的内容
		l_vUserInfo = l_jReqData;
	}
	catch (...)
	{
		return HttpSendResponse(p_pConn, 400, "json", l_jResData.dump(), "");
	}

	if (l_vUserInfo.m_nUserId >= 0)
	{
		l_oUerInfo = GetUserInfo(l_vUserInfo.m_nUserId);
		if (l_oUerInfo.m_strName == "admin")
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Cannot modify administrator information");
			l_jResData["message"] = sconv("不允许编辑管理员用户信息!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
		l_vUserInfo.m_cStatus = l_oUerInfo.m_cStatus;
		l_vUserInfo.m_strPassWd = l_oUerInfo.m_strPassWd;
		if (!UpdateUserInfo(l_vUserInfo))
			return HttpSendResponse(p_pConn, 400, "json", l_jResData.dump(), "");
	}
	else
	{
		time_t l_timenow;
		time(&l_timenow);
		l_vUserInfo.m_cStatus = 0;
		l_vUserInfo.m_strPassWd = "";
		l_vUserInfo.m_strCreateTime = FormatTime(l_timenow);
		if (!AddUserInfo(l_vUserInfo))
			return HttpSendResponse(p_pConn, 400, "json", l_jResData.dump(), "");
	}

	l_nCode = 200;
	l_jReqData["result"] = "success";
	l_jReqData["message"] = sconv("保存用户信息成功!");
	HttpSendResponse(p_pConn, l_nCode, "json", l_jReqData.dump(), "");
}

void ManageUserPassword(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	UserInfo l_oUerInfo;
	p_nEvent = p_nEvent;
	json l_jReqData, l_jResData;
	int l_nld, l_userId;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strSessionId = GetRequestSessionId(l_pHttpMsg);
	HttpServer* l_HttpServer = ((HttpServer*)p_vData);
	string l_strOp = GetHttpUrlQuery(l_pHttpMsg, "act");
	if (l_strOp == "edit")
	{
		string location = "/page/security/manage_passwd.html?";
		location += string(l_pHttpMsg->query_string.p, l_pHttpMsg->query_string.len);
		return HttpSendRedirect(p_pConn, 301, location, "");
	}

	Session *l_Session = l_HttpServer->m_cSessionManage->GetSession(l_strSessionId);
	if (l_Session == NULL)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Administrator does not exist");
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("用户管理员信息不存在!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	l_nld = l_Session->m_nUserId;
	string l_SessionKey = l_Session->m_strSessionKey;
	string l_strOldPw, l_strNewPw, l_strConfPw;

	try
	{
		l_userId = stoi(GetHttpUrlQuery(l_pHttpMsg, "userId"));
	}
	catch (...)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("修改用户不存在!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	try {
		l_jReqData = json::parse(string(l_pHttpMsg->body.p, l_pHttpMsg->body.len));
		l_strOldPw = GetJsonStringData(l_jReqData, "oldPw");
		l_strOldPw = AesDecryptCBC(l_strOldPw, l_SessionKey);
		l_strNewPw = GetJsonStringData(l_jReqData, "newPw");
		l_strConfPw = GetJsonStringData(l_jReqData, "confirmPw");
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
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver The administrator password is wrong");
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("用户管理员密码错误!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	l_oUerInfo = GetUserInfo(l_userId);
	if (l_oUerInfo.m_strName == "admin")
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver The administrator password is wrong");
		l_jResData["message"] = sconv("不允许编辑管理员用户信息!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	if (l_oUerInfo.m_nUserId < 0)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Modify user does not exist");
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("修改用户不存在!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	l_oUerInfo.m_strPassWd = l_strNewPw;
	UpdateUserInfo(l_oUerInfo);
	l_jResData["result"] = "success";
	l_jResData["message"] = sconv("修改用户的密码成功!");
	HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
}


void AddUserManageHandler(HttpServer *p_pHttpServer)
{
	p_pHttpServer->AddHttpRequestHandler("/user/manage/infolist", { LoadUserInfoList,0,0,"查看用户信息列表" });
	p_pHttpServer->AddHttpRequestHandler("/user/manage/edit", { UserInfoEdit,0,0,"用户基本信息编辑" });
	p_pHttpServer->AddHttpRequestHandler("/user/manage/modify", { UserInfoModify,0,0,"删除和修改用户状态" });
	p_pHttpServer->AddHttpRequestHandler("/user/manage/infoquery", { QueryUserInfo,0,0, "单用户信息查询"});
	p_pHttpServer->AddHttpRequestHandler("/user/manage/passwd", { ManageUserPassword,0,0,"修改用户密码" });
}