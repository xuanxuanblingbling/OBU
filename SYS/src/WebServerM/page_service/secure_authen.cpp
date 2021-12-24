#include "../web_service/http_handler.h"

#define ROLELIST_PAGESIZE   20

#define URIAUTHENTYPE    0
#define FILEAUTHENTYPE   1
#define CMDAUTHENTYPE    2
#define HTMLAUTHENTYPE   3

int GetRequstAuthenType(http_message* p_pHttpMsg)
{
	int l_nType;
	string l_strType = GetHttpUrlQuery(p_pHttpMsg, "type");
	if (l_strType == "uri")
		l_nType = URIAUTHENTYPE;
	else if (l_strType == "html")
		l_nType = HTMLAUTHENTYPE;
	else if (l_strType == "file")
		l_nType = FILEAUTHENTYPE;
	else
		l_nType = CMDAUTHENTYPE;
	return l_nType;
}


void GetRoleAuthenList(struct mg_connection* p_pConn, void* p_pHttpMsg, void *p_vData, int type)
{
	json l_jResData;
	char l_nRoleId = 0;
	vector<json> l_vAuthenList;
	unsigned int l_pageNo, l_pageSize, l_nStart, l_nEnd;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	HttpServer *l_HttpServer = ((HttpServer *)p_vData);
	unordered_map<string,unsigned int> *l_mapData;
	l_jResData["pageSize"] = ROLELIST_PAGESIZE;
	l_jResData["pageNo"] = 1;
	l_jResData["count"] = 0;
	l_jResData["list"] = "";
	try
	{
		l_nRoleId = stoi(GetHttpUrlQuery(l_pHttpMsg, "id"));
	}
	catch (...)
	{
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
	}
	string p_strName = l_HttpServer->m_cRBACManage->GetRoleNameById(l_nRoleId);
	if(p_strName.empty())
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
	l_jResData["name"] = sconv(p_strName);
	if (l_nRoleId == 0)
		l_jResData["message"] = sconv("不允许编辑超级管理员的权限!");

	if(!(l_nRoleId >= 1 && l_nRoleId < 15))
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");

	if (type == URIAUTHENTYPE)
		l_mapData = &(l_HttpServer->m_cRBACManage->m_UriAuthen);
	else if (type == FILEAUTHENTYPE)
		l_mapData = &(l_HttpServer->m_cRBACManage->m_FileAuthen);
	else if (type == CMDAUTHENTYPE)
		l_mapData = &(l_HttpServer->m_cRBACManage->m_CmdAuthen);
	else
		l_mapData = &(l_HttpServer->m_cRBACManage->m_HtmlAuthen);
	if (l_mapData->size() == 0)
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
	GetPageStartEnd(l_pHttpMsg, l_nStart, l_nEnd, l_pageNo, l_pageSize, l_mapData->size(), ROLELIST_PAGESIZE);
	l_jResData["pageSize"] = l_pageSize;
	l_jResData["pageNo"] = l_pageNo;
	auto l_mapIter = l_mapData->begin();
	unsigned int l_nMaskRead = 1 << l_nRoleId;
	unsigned int l_nMaskWrite = (1 << l_nRoleId) << 16;
	for (unsigned int k = 0; k < l_nEnd; k++)
	{
		json l_jTemp;
		int l_nAuthen = l_mapIter->second;
		if (k >= l_nStart)
		{
			l_jTemp["name"] = l_mapIter->first;
			l_jTemp["read"] = (l_nAuthen & l_nMaskRead) ? 1 : 0;
			if (type == URIAUTHENTYPE || type == FILEAUTHENTYPE)
				l_jTemp["write"] = (l_nAuthen & l_nMaskWrite) ? 1 : 0;
			if (type == URIAUTHENTYPE)
			{
				auto l_uriData = l_HttpServer->m_mapUriProc.find(l_mapIter->first);
				l_jTemp["descrip"] = sconv(l_uriData->second.m_strDescrip);
			}
			l_vAuthenList.push_back(l_jTemp);
		}
		l_mapIter++;
	}
	l_jResData["list"] = l_vAuthenList;
	l_jResData["count"] = l_mapData->size();
	l_jResData["message"].clear();
	return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
}

void ModifyRoleAuthen(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)
{
	json l_jResData, l_jReqData;
	p_nEvent = p_nEvent;
	char l_nRoleId = 0, l_nType;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	HttpServer* l_HttpServer = ((HttpServer*)p_vData);
	map<string, char> p_mapAuthen;
	try
	{
		l_nRoleId = stoi(GetHttpUrlQuery(l_pHttpMsg, "id"));
	}
	catch (...)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("请求内容解析失败!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	if (l_nRoleId == 0)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("不允许修改超级管理员权限!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	string l_strName = l_HttpServer->m_cRBACManage->GetRoleNameById(l_nRoleId);
	if (l_strName.empty())
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("未知角色类型!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	try {
		l_jReqData = json::parse(string(l_pHttpMsg->body.p, l_pHttpMsg->body.len));
		for (auto l_jData = l_jReqData.begin(); l_jData != l_jReqData.end(); l_jData++)
		{
			char l_strVal;
			try
			{
				string vale = l_jData.value().get<string>();
				string key = l_jData.key();
				l_strVal = stoi(l_jData.value().get<string>());
				p_mapAuthen.insert(make_pair(l_jData.key(), l_strVal));
			}
			catch (...)
			{
				;
			}
		}
	}
	catch (...)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("未知角色类型!");
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
	}
	l_nType = GetRequstAuthenType(l_pHttpMsg);
	if (l_nType == URIAUTHENTYPE)
		l_HttpServer->m_cRBACManage->ModifyRoleUri(l_strName, p_mapAuthen);
	else if (l_nType == FILEAUTHENTYPE)
		l_HttpServer->m_cRBACManage->ModifyRoleFile(l_strName, p_mapAuthen);
	else if (l_nType == CMDAUTHENTYPE)
		l_HttpServer->m_cRBACManage->ModifyRoleCmd(l_strName, p_mapAuthen);
	else
		l_HttpServer->m_cRBACManage->ModifyRoleHtml(l_strName, p_mapAuthen);
	l_jResData["result"] = "success";
	l_jResData["message"] = sconv("配置用户权限成功!");
	return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");

}

void ReturnAuthenPage(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)
{
	p_nEvent = p_nEvent;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strType = GetHttpUrlQuery(l_pHttpMsg, "type"), location;
	if (l_strType == "uri")
		location = "/page/security/manage_authenuri.html?";
	else if (l_strType == "uri")
		location = "/page/security/manage_authenuri.html?";
	else if (l_strType == "html")
		location = "/page/security/manage_authenhtml.html?";
	else if (l_strType == "file")
		location = "/page/security/manage_authenfile.html?";
	else
		location = "/page/security/manage_authencmd.html?";
	location += string(l_pHttpMsg->query_string.p, l_pHttpMsg->query_string.len);   // send redirect
	return HttpSendRedirect(p_pConn, 301, location, "");
}

void RoleAuthenEdit(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)
{
	json l_jResData;
	p_nEvent = p_nEvent;
	HttpServer *l_HttpServer = ((HttpServer *)p_vData);
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strAct = GetHttpUrlQuery(l_pHttpMsg, "act");
	if (l_strAct == "delete")
	{
		char l_nId;
		try
		{
			l_nId = stoi(GetHttpUrlQuery(l_pHttpMsg, "id"));
		}
		catch (...)
		{
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("请求内容解析失败!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
		l_HttpServer->m_cRBACManage->DeleteRole(l_nId);
		l_jResData["result"] = "success";
		l_jResData["message"] = sconv("删除角色成功!");
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
	}
	else
	{
		char l_cId, l_ssh, l_chroot;
		string l_strName;
		try
		{
			json l_jReqData = json::parse(string(l_pHttpMsg->body.p, l_pHttpMsg->body.len));
			l_cId = GetJsonIntData(l_jReqData, "roleid");
			l_ssh = GetJsonIntData(l_jReqData, "ssh");
			l_chroot = GetJsonIntData(l_jReqData, "chroot");
			l_strName = GetJsonStringData(l_jReqData, "name");
		}
		catch (...)
		{
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("请求内容解析失败!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
		if (l_HttpServer->m_cRBACManage->EditRole(l_cId, l_strName, l_ssh, l_chroot))
		{
			l_jResData["result"] = "success";
			l_jResData["message"] = sconv("修改角色成功!");
			return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
		}
		else
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Failed to modify role");
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("修改角色失败!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}
}


void AuthenFileEdit(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)
{
	json l_jResData;
	p_nEvent = p_nEvent;
	bool l_bRet = false;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strOp = GetHttpUrlQuery(l_pHttpMsg, "act");
	string l_strName = GetHttpUrlQuery(l_pHttpMsg, "name");
	HttpServer* l_HttpServer = ((HttpServer*)p_vData);
	if (l_strName.empty() || l_strOp.empty())
	{
		l_jResData["result"] = "success";
		l_jResData["message"] = sconv("请求内容解析失败!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	if (l_strOp == "add")
		l_bRet = l_HttpServer->m_cRBACManage->AddFileItem(l_strName);
	else if (l_strOp == "delete")
		l_bRet = l_HttpServer->m_cRBACManage->DeleteFileItem(l_strName);

	if (!l_bRet)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("操作失败!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	else
	{
		l_jResData["result"] = "success";
		l_jResData["message"] = sconv("操作成功!");
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
	}
}

void AuthenRoleList(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)
{
	json l_jResData, l_jTemp;
	p_nEvent = p_nEvent;
	vector<json> l_vAuthenList;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	HttpServer* l_HttpServer = ((HttpServer*)p_vData);
	l_jResData["pageSize"] = (l_HttpServer->m_cRBACManage->m_RoleList).size();
	l_jResData["pageNo"] = 1;
	l_jResData["count"] = (l_HttpServer->m_cRBACManage->m_RoleList).size();
	for (auto& l_tData : l_HttpServer->m_cRBACManage->m_RoleList)
	{
		json l_jData;
		unsigned int l_cMask = 1 << l_tData.second;
		l_jData["name"] = sconv(l_tData.first);
		l_jData["roleid"] = l_tData.second;
		l_jData["ssh"] = (l_HttpServer->m_cRBACManage->m_SShAuthen & l_cMask) ? sconv("允许") : sconv("禁止");
		l_jData["chroot"] = (l_HttpServer->m_cRBACManage->m_chRootAuthen & l_cMask) ? sconv("允许") : sconv("禁止");
		l_vAuthenList.push_back(l_jData);
	}
	l_jResData["list"] = l_vAuthenList;
	return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
}

void AddUserAuthenHandler(HttpServer* p_pHttpServer)
{
	p_pHttpServer->AddHttpRequestHandler("/secure/authen/rolelist/", { AuthenRoleList,0,0,"查看用户角色列表" });
	p_pHttpServer->AddHttpRequestHandler("/secure/authen/roleedit", { RoleAuthenEdit,0,0,"编辑用户角色" });
	p_pHttpServer->AddHttpRequestHandler("/secure/authen/page", { ReturnAuthenPage,0,0,"打开授权编辑页面" });
	p_pHttpServer->AddHttpRequestHandler("/secure/authen/modify", { ModifyRoleAuthen,0,0,"编辑角色权限" });
	p_pHttpServer->AddHttpRequestHandler("/secure/authen/fileedit", { AuthenFileEdit,0,0,"编辑带有授权的文件" });
	p_pHttpServer->AddHttpRequestHandler("/secure/authen/authenlist",
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)->void {
			p_nEvent = p_nEvent;
			GetRoleAuthenList(p_pConn,p_pHttpMsg,p_vData, GetRequstAuthenType((struct http_message*)p_pHttpMsg));
		}, 0, 0, "查看权限列表" });
}
