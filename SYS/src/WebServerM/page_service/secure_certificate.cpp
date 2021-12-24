#include "../web_service/http_handler.h"

#define CERTIFICATE_PAGESIZE  20

typedef struct _CertificateInfo {
	int m_nId;
	char m_cStatus;
	std::string m_strSerialNum;
	std::string m_strStartData;
	std::string m_strExpiryData;
	std::string m_strClass;
	std::string m_strCAName;
	std::string m_strAlgorithm;
	std::string m_strPath;
}CertificateInfo;

void to_json(json& p_j, const CertificateInfo& p_sData)
{
	p_j = json{ { "serialnum", sconv(p_sData.m_strSerialNum)},
	{ "startdata", sconv(p_sData.m_strStartData)},
	{ "expirydata", sconv(p_sData.m_strExpiryData)},
	{ "class", sconv(p_sData.m_strClass)},
	{ "ca", sconv(p_sData.m_strCAName)},
	{ "algorithm", sconv(p_sData.m_strAlgorithm)},
	{ "status", p_sData.m_cStatus},
	{ "path", sconv(p_sData.m_strPath)},
	{ "id", p_sData.m_nId}};
}

void from_json(const json& p_j, CertificateInfo& p_sData)
{
	p_sData.m_cStatus = GetJsonIntData(p_j, "status");
	p_sData.m_nId = GetJsonIntData(p_j, "id");
	p_sData.m_strPath = GetJsonStringData(p_j, "path");
	p_sData.m_strAlgorithm = GetJsonStringData(p_j, "algorithm");
	p_sData.m_strCAName = GetJsonStringData(p_j, "ca");
	p_sData.m_strClass = GetJsonStringData(p_j, "class");
	p_sData.m_strExpiryData = GetJsonStringData(p_j, "expirydata");
	p_sData.m_strStartData = GetJsonStringData(p_j, "startdata");
	p_sData.m_strSerialNum = GetJsonStringData(p_j, "serialnum");
}

void CertificateInfoList(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)
{
	int l_pageNo, l_pageSize, l_nStart, l_nEnd;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	vector<CertificateInfo> l_DataList;
	json l_jReqData;
	l_jReqData["pageSize"] = CERTIFICATE_PAGESIZE;
	l_jReqData["pageNo"] = 1;
	l_jReqData["count"] = 0;
	l_jReqData["list"] = "";
	
	if (!GetJsonDataFromFile(JSON_CERTICATE, (HttpServer *)p_vData))
		return HttpSendResponse(p_pConn, 200, "json", l_jReqData.dump(), "");

	json &l_webData = ((HttpServer *)p_vData)->m_sJsonSet[JSON_CERTICATE].data;

	if (!(l_webData.is_array() && l_webData.size()))
		return HttpSendResponse(p_pConn, 200, "json", l_jReqData.dump(), "");

	try
	{
		l_pageNo = stoi(GetHttpUrlParma(&l_pHttpMsg->body, "pageNo"));
		l_pageSize = stoi(GetHttpUrlParma(&l_pHttpMsg->body, "pageSize"));
	}
	catch (...)
	{
		l_pageNo = 1;
		l_pageSize = CERTIFICATE_PAGESIZE;
	}
	l_nStart = (l_pageNo - 1) * l_pageSize;

	if (l_nStart >= l_webData.size())
		l_pageNo = 1;

	l_nStart = (l_pageNo - 1) * l_pageSize;
	l_nEnd = l_nStart + l_pageSize;
	l_nEnd = (l_nEnd > l_webData.size()) ? l_webData.size() : l_nEnd;

	l_jReqData["pageSize"] = l_pageSize;
	l_jReqData["pageNo"] = l_pageNo;

	for (int k = l_nStart; k < l_nEnd; ++k)
	{
		try
		{
			CertificateInfo l_Data = l_webData[k];
			l_Data.m_strPath = "";
			l_DataList.push_back(l_Data);
		}
		catch (...)
		{
			return HttpSendResponse(p_pConn, 200, "json", l_jReqData.dump(), "");
		}
	}
	l_jReqData["list"] = l_DataList;
	l_jReqData["count"] = l_webData.size();
	HttpSendResponse(p_pConn, 200, "json", l_jReqData.dump(), "");
}

bool VerifyCertId(struct mg_connection* p_pConn, http_message* p_pHttpMsg, HttpServer * p_vData, CertificateInfo &p_Cert)
{
	int n_ID = 0, k = 0;
	json l_jResData;
	l_jResData["result"] = "error";
	l_jResData["message"] = sconv("该证书不存在!");
	try {
		n_ID = stoi(GetHttpUrlQuery(p_pHttpMsg, "certificateId"));
	}
	catch (...) {
		l_jResData["message"] = sconv("请求参数异常!");
		HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		return false;
	}
	if (!GetJsonDataFromFile(JSON_CERTICATE, (HttpServer *)p_vData))
	{
		HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		return false;
	}
	json &l_webData = ((HttpServer *)p_vData)->m_sJsonSet[JSON_CERTICATE].data;
	if (!(l_webData.is_array() && l_webData.size()))   // 检查证书ID是否存在
	{
		HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
		return false;
	}

	for (k = 0; k < l_webData.size(); k++)
	{
		try {
			if (l_webData[k]["id"].get<int>() == n_ID)
			{
				p_Cert = l_webData[k];
				break;
			}	
		}
		catch (...)
		{
			l_jResData["message"] = sconv("证书参数文件内容格式错误!");
			HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
			return false;
		}
	}
	if (k == l_webData.size())
	{
		HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		return false;
	}
	return true;
}

void CertificateEdit(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)
{
	CertificateInfo l_Cert;
	json l_jResData, l_jSendData;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strAct = GetHttpUrlQuery(l_pHttpMsg, "act");
	l_Cert.m_nId = -1;
	l_jSendData["ConfigType"] = "Certification";
	l_jSendData["Operation"] = "set";
	if (l_strAct == "disable")
		l_jSendData["ConfigType"] = "CertDisable";
	else if (l_strAct == "enable")
		l_jSendData["ConfigType"] = "CertEnable";
	else if (l_strAct == "delete")
		l_jSendData["Operation"] = "delete";
	else if (l_strAct == "add")
		l_jSendData["Operation"] = "add";
	else if (l_strAct == "updata")
	{
		l_jSendData["ConfigType"] = "CertUpdata";
	}
	else
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("请求参数异常!");
		HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	if (l_strAct == "add" || VerifyCertId(p_pConn, l_pHttpMsg, (HttpServer *)p_vData, l_Cert))
	{
		l_jSendData["id"] = l_Cert.m_nId;
		l_jSendData["ModuleName"] = "Cer";
		string l_strData = l_jSendData.dump();
		//return ProcTcpSendData(p_pConn, l_strData, CLIENT_MODULE, (HttpServer *)p_vData);

		l_jSendData["result"] = "error";
		l_jSendData["message"] = sconv("请求参数异常!");
		HttpSendResponse(p_pConn, 500, "json", l_jSendData.dump(), "");
	}
}


void AddCertificateHandler(HttpServer *p_pHttpServer)
{
	p_pHttpServer->AddHttpRequestHandler("/secure/certificate/list", {CertificateInfoList,0,0,"查询证书列表"});
	p_pHttpServer->AddHttpRequestHandler("/secure/certificate/edit", { CertificateEdit,0,0,"证书删除和状态修改" });
	p_pHttpServer->AddHttpRequestHandler("/secure/certificate/apply",
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)->void {
			struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
			json l_jSendData;
			p_nEvent = p_nEvent;
			l_jSendData["ConfigType"] = "CertApply";
			l_jSendData["Operation"] = "set";
			l_jSendData["ModuleName"] = "Cer";
			string l_strSend = string(l_pHttpMsg->body.p, l_pHttpMsg->body.len);
			//return ProcTcpSendDataExtent(p_pConn, l_strSend, CLIENT_MODULE, (HttpServer*)p_vData, l_jSendData);

			l_jSendData["result"] = "error";
			l_jSendData["message"] = sconv("请求参数异常!");
			HttpSendResponse(p_pConn, 500, "json", l_jSendData.dump(), "");
		},0,0,"证书申请" });

	p_pHttpServer->AddHttpRequestHandler("/secure/certificate/download",
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)->void {
			CertificateInfo l_Cert;
			json l_jResData;
			p_nEvent = p_nEvent;
			if (VerifyCertId(p_pConn, (struct http_message*)p_pHttpMsg, (HttpServer*)p_vData, l_Cert))
			{
				string l_strFname;
				if (l_Cert.m_strPath.empty() || l_Cert.m_strPath[l_Cert.m_strPath.length() - 1] == '/')
				{
					l_jResData["result"] = "error";
					l_jResData["message"] = sconv("请求文件不存在!");
					HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
				}
				int l_nIndex = l_Cert.m_strPath.find_last_of("/");
				if (l_nIndex < 0)
					l_strFname = l_Cert.m_strPath;
				else
					l_strFname = l_Cert.m_strPath.substr(l_nIndex + 1, l_Cert.m_strPath.length() - l_nIndex - 1);
				DownloadFile(p_pConn, (struct http_message*)p_pHttpMsg, l_Cert.m_strPath.c_str(), l_strFname);
			}
		},0,0,"证书文件下载" });

	p_pHttpServer->AddHttpRequestHandler("/secure/certificate/upload", 
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)->void {},0,0, "上传证书文件到设备" });
	p_pHttpServer->AddUploadPath("/secure/certificate/upload", p_pHttpServer->m_cWebConfig->m_strCertUploadPath);
}
