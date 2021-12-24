#include "../web_service/http_handler.h"

#define IPACLTABLE_PAGESIZE  20

typedef struct _IPAcl
{
	int m_nId;              // ID
	string m_strOption;     // 选项允许或者禁止
	string m_strNetSrc;     // 网卡
	string m_strProtocal;   // 协议
	string m_strIpStart;    // 起始IP
	string m_strIpEnd;      // 终止IP
	string m_strPortStart;     // 起始端口
	string m_strPortEnd;       // 终止端口
}IPAcl;

void to_json(json& p_j, const IPAcl& p_sData)
{
	p_j = json{ { "seqid",p_sData.m_nId},
	{ "option", sconv(p_sData.m_strOption)},
	{ "ipStart", sconv(p_sData.m_strIpStart)},
	{ "ipEnd", sconv(p_sData.m_strIpEnd)},
	{ "portStart", sconv(p_sData.m_strPortStart)},
	{ "portEnd", sconv(p_sData.m_strPortEnd)},
	{ "protocal", sconv(p_sData.m_strProtocal)},
	{ "netsrc", sconv(p_sData.m_strNetSrc)}};
}

void from_json(const json& p_j, IPAcl& p_sData)
{
	p_sData.m_nId = GetJsonIntData(p_j, "seqid");
	p_sData.m_strOption = GetJsonStringData(p_j, "option");
	p_sData.m_strIpStart = GetJsonStringData(p_j, "ipStart");
	p_sData.m_strIpEnd = GetJsonStringData(p_j, "ipEnd");
	p_sData.m_strPortStart = GetJsonStringData(p_j, "portStart");
	p_sData.m_strPortEnd = GetJsonStringData(p_j, "portEnd");
	p_sData.m_strProtocal = GetJsonStringData(p_j, "protocal");
	p_sData.m_strNetSrc = GetJsonStringData(p_j, "netsrc");
}


unsigned int IPtoINT(const string &p_strIP)
{
	int a[4];
	if (sscanf(p_strIP.c_str(), "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]) != 4)
		return 0;
	int k = 4;
	while (k--)
	{
		if (0 < a[k] || a[k] > 255)
			return 0;
	}
	return (a[0] << 24 | a[1] << 16 | a[2] << 8 | a[3]);
}


void SaveIpAclListToFile(list<IPAcl> &p_IpAclList, HttpServer *p_HttpSever)
{
	struct stat l_stat;
	json l_jData;
	string l_strFname = p_HttpSever->m_cWebConfig->m_strIpAclConfigFile;
	fstream l_File(l_strFname, ios::out | ios::trunc);
	if (l_File.is_open())
	{
		if (p_IpAclList.empty())
			l_File << "[]";
		else
		{
			l_jData = json(p_IpAclList);
			l_File << l_jData.dump(1, '\t');
		}
		l_File.close();
		if (stat(l_strFname.c_str(), &l_stat) >= 0)
		{
			p_HttpSever->m_sJsonSet[JSON_IPACL].data = l_jData;
			p_HttpSever->m_sJsonSet[JSON_IPACL].mtime = l_stat.st_mtime;
		}
	}
}

bool ConvertJsonToIpAclLits(json &p_jData, list<IPAcl> &p_IpAclList, HttpServer *p_HttpSever)
{
	bool l_RetVal = true;
	if (p_jData.empty() || (!p_jData.is_array()))
		l_RetVal = false;
	else
	{
		for (unsigned int k = 0; k < p_jData.size(); k++)
		{
			try
			{
				p_IpAclList.push_back(p_jData[k]);
			}
			catch (...)
			{
				l_RetVal = false;
				break;
			}
		}
	}
	if (!l_RetVal)
	{
		p_jData.clear();
		SaveIpAclListToFile(p_IpAclList, p_HttpSever);
	}
	return l_RetVal;
}

string IPAclCheck( IPAcl &p_IPAcl)
{
	unsigned int l_nIPStart = IPtoINT(p_IPAcl.m_strIpStart);
	unsigned int l_nIPEnd = IPtoINT(p_IPAcl.m_strIpEnd);

	unsigned int l_nPortStart = atoi(p_IPAcl.m_strPortStart.c_str());
	unsigned int l_nPortEnd = atoi(p_IPAcl.m_strPortEnd.c_str());
	

	if ((l_nIPStart == 0) && (l_nIPEnd == 0) && (l_nPortStart != 0) && (l_nPortEnd == 0))
	{
		//离散port
		return " --dport " + p_IPAcl.m_strPortStart;
	}
	else if ((l_nIPStart == 0) && (l_nIPEnd == 0) && (l_nPortStart != 0) && (l_nPortEnd != 0) && (l_nPortStart < l_nPortEnd))
	{
		//连续port
		return " --dport " + p_IPAcl.m_strPortStart + ":" + p_IPAcl.m_strPortEnd;
	}
	else if ((l_nIPStart != 0) && (l_nIPEnd == 0) && (l_nPortStart == 0) && (l_nPortEnd == 0))
	{
		//离散ip
		return " -s " + p_IPAcl.m_strIpStart;
	}
	else if ((l_nIPStart != 0) && (l_nIPEnd != 0) && (l_nPortStart == 0) && (l_nPortEnd == 0) && (l_nIPStart < l_nIPEnd))
	{
		//连续ip
		return " -m iprange --src-range " + p_IPAcl.m_strIpStart + "-" + p_IPAcl.m_strIpEnd;
	}
	else if ((l_nIPStart != 0) && (l_nIPEnd == 0) && (l_nPortStart != 0) && (l_nPortEnd == 0))
	{
		//离散ip+离散port
		return " -s " + p_IPAcl.m_strIpStart + " --dport " + p_IPAcl.m_strPortStart;
	}
	else if ((l_nIPStart != 0) && (l_nIPEnd == 0) && (l_nPortStart != 0) && (l_nPortEnd != 0) && (l_nPortStart < l_nPortEnd))
	{
		//离散ip+连续port
		return " -s " + p_IPAcl.m_strIpStart + " --dport " + p_IPAcl.m_strPortStart + ":" + p_IPAcl.m_strPortEnd;
	}
	else if ((l_nIPStart != 0) && (l_nIPEnd != 0) && (l_nPortStart != 0) && (l_nPortEnd == 0))
	{
		//连续ip+离散port
		return " -m iprange --src-range " + p_IPAcl.m_strIpStart + "-" + p_IPAcl.m_strIpEnd + " --dport " + p_IPAcl.m_strPortStart;
	}
	else if ((l_nIPStart != 0) && (l_nPortStart != 0) && (l_nIPStart < l_nIPEnd) && (l_nPortStart < l_nPortEnd))
	{
		//连续ip+连续port
		return " -m iprange --src-range " + p_IPAcl.m_strIpStart + "-" + p_IPAcl.m_strIpEnd + " --dport " + p_IPAcl.m_strPortStart + ":" + p_IPAcl.m_strPortEnd;
	}
	else
		return "";
}

string OptionCheck(const string &p_strOption)
{
	if (p_strOption == "允许")
		return " -j ACCEPT ";
	else
		return " -j DROP ";
}
string NetSrcCheck(const string &p_strNetSrc)
{
	if (p_strNetSrc == "光口")
		return " -i eth0 ";
	else if (p_strNetSrc == "电口")
		return " -i eth1 ";
	else if (p_strNetSrc == "4G")
		return " -i eth2 ";
	else if (p_strNetSrc == "wifi")
		return " -i wlan0 ";
	else 
		return "";
}

string ProtocalCheck(const string &p_strProcotal)
{
	if (p_strProcotal == "TCP")
		return " -p TCP ";
	else if ((p_strProcotal == "UDP"))
		return " -p UDP ";
	else
		return "";
}


void SystemIpAclSet(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	list<IPAcl> l_IpAclList;

	json l_jReqData;

	HttpServer * l_pHttpServer = (HttpServer *)p_vData;

	GetJsonDataFromFile(JSON_IPACL, (HttpServer *)p_vData);
	json &l_webData = ((HttpServer *)p_vData)->m_sJsonSet[JSON_IPACL].data;
	ConvertJsonToIpAclLits(l_webData, l_IpAclList, l_pHttpServer);

	fstream l_File("config/ipacl.sh", ios::out | ios::trunc);
	l_File << "#!/bin/sh" << endl;
	l_File << "iptables -t filter -F INPUT" << endl;

	for (auto l_lData = l_IpAclList.begin(); l_lData != l_IpAclList.end(); l_lData++)
	{

		if ((IPAclCheck((*l_lData)) == ""))
		{
			l_jReqData["result"] = "error";
			l_jReqData["message"] = sconv("设置数据失败!");
			return HttpSendResponse(p_pConn, 500, "json", l_jReqData.dump(), "");
		}
		else
		{
			l_File << "iptables -t filter -A INPUT " + NetSrcCheck((*l_lData).m_strNetSrc) + ProtocalCheck((*l_lData).m_strProtocal) + IPAclCheck((*l_lData)) + OptionCheck((*l_lData).m_strOption) << endl;
		}
	}

	l_File << "iptables-save > /etc/ipacl.rules" << endl;

	l_File.close();

	l_jReqData["result"] = "success";
	l_jReqData["message"] = sconv("设置数据成功!");
	return HttpSendResponse(p_pConn, 200, "json", l_jReqData.dump(), "");
	
	//system("./ ipacl.sh");
}


void IpAclListInsert(list<IPAcl> &p_IpAclList, IPAcl p_IpAcl, int p_nAfterId)
{

	unsigned int l_nCount = 1;
	if (p_nAfterId <= 0)
		p_IpAclList.push_front(p_IpAcl);
	else if (p_nAfterId > p_IpAclList.size())
		p_IpAclList.push_back(p_IpAcl);
	else
	{
		for (auto l_lData = p_IpAclList.begin(); l_lData != p_IpAclList.end(); l_lData++)
		{
			if (p_nAfterId == l_nCount)
			{
				p_IpAclList.insert(l_lData, p_IpAcl);
				break;
			}
			l_nCount++;
		}
	}
	l_nCount = 1;
	for (auto &l_lData : p_IpAclList)
		l_lData.m_nId = l_nCount++;
}

void IpAclListDelete(list<IPAcl> &p_IpAclList, int p_nCurrentId)
{
	unsigned int l_nCount = 1;
	for (auto l_lData = p_IpAclList.begin(); l_lData != p_IpAclList.end(); l_lData++)
	{
		if (p_nCurrentId == (*l_lData).m_nId)
		{
			p_IpAclList.erase(l_lData);
			break;
		}
	}
	for (auto &l_lData : p_IpAclList)
		l_lData.m_nId = l_nCount++;

}

void SystemIpAclList(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	json l_jReqData;
	unsigned int l_pageNo, l_pageSize, l_nStart, l_nEnd;
	list<IPAcl> l_IpAclList;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	HttpServer * l_pHttpServer = (HttpServer *)p_vData;

	GetJsonDataFromFile(JSON_IPACL, (HttpServer *)p_vData);
	json &l_webData = ((HttpServer *)p_vData)->m_sJsonSet[JSON_IPACL].data;

	l_jReqData["pageSize"] = IPACLTABLE_PAGESIZE;
	l_jReqData["pageNo"] = 1;
	l_jReqData["count"] = 0;
	l_jReqData["list"] = "";
	ConvertJsonToIpAclLits(l_webData, l_IpAclList, l_pHttpServer);

	try
	{
		l_pageNo = stoi(GetHttpUrlParma(&l_pHttpMsg->body, "pageNo"));
		l_pageSize = stoi(GetHttpUrlParma(&l_pHttpMsg->body, "pageSize"));
	}
	catch (...)
	{
		l_pageNo = 1;
		l_pageSize = IPACLTABLE_PAGESIZE;
	}
	l_nStart = (l_pageNo - 1) * l_pageSize;

	if (l_nStart >= l_webData.size())
		l_pageNo = 1;

	l_nStart = (l_pageNo - 1) * l_pageSize;
	l_nEnd = l_nStart + l_pageSize;
	l_nEnd = (l_nEnd > l_webData.size()) ? l_webData.size() : l_nEnd;

	l_jReqData["pageSize"] = l_pageSize;
	l_jReqData["pageNo"] = l_pageNo;
	l_jReqData["count"] = l_IpAclList.size();
	vector<json> l_jDataList;
	auto l_listData = l_IpAclList.begin();
	for (unsigned int k = 0; k < l_nEnd; k++)
	{
		if (k >= l_nStart)
		{
			json l_jTemp = (*l_listData);
			l_jTemp["afterid"] = std::to_string(k + 1);
			l_jDataList.push_back(l_jTemp);
		}
		l_listData++;
	}
	l_jReqData["list"] = l_jDataList;
	HttpSendResponse(p_pConn, 200, "json", l_jReqData.dump(), "");
}


void SystemIpAclSave(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	int l_nAfterId;
	json l_jRecData, l_jResData;
	IPAcl l_IpAcl;
	list<IPAcl> l_IpAclList;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strBody = string(l_pHttpMsg->body.p, l_pHttpMsg->body.len);
	GetJsonDataFromFile(JSON_IPACL, (HttpServer *)p_vData);
	json &l_webData = ((HttpServer *)p_vData)->m_sJsonSet[JSON_IPACL].data;

	ConvertJsonToIpAclLits(l_webData, l_IpAclList, (HttpServer *)p_vData);

	try {
		l_jRecData = json::parse(l_strBody);
		l_IpAcl = l_jRecData;
		if (l_IpAcl.m_nId < 0)
		{
			l_nAfterId = GetJsonIntData(l_jRecData, "afterid");
		}
	}
	catch (...)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("保存数据错误!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	if (l_IpAcl.m_nId < 0)
	{
		IpAclListInsert(l_IpAclList, l_IpAcl, l_nAfterId);
		SaveIpAclListToFile(l_IpAclList, (HttpServer *)p_vData);
	}
		
	else
	{
		for (auto &l_lData : l_IpAclList)
		{
			if (l_lData.m_nId == l_IpAcl.m_nId)
			{
				l_lData = l_IpAcl;
				break;
			}
		}
		SaveIpAclListToFile(l_IpAclList, (HttpServer *)p_vData);
	}
	

	l_jResData["result"] = "success";
	l_jResData["message"] = sconv("保存数据成功!");
	return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
}

void SystemIpAclDel(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	json l_jResData;
	int l_nID;
	list<IPAcl> p_IpAclList;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	GetJsonDataFromFile(JSON_IPACL, (HttpServer *)p_vData);
	json &l_webData = ((HttpServer *)p_vData)->m_sJsonSet[JSON_IPACL].data;

	ConvertJsonToIpAclLits(l_webData, p_IpAclList, (HttpServer *)p_vData);

	try
	{
		l_nID = stoi(GetHttpUrlQuery(l_pHttpMsg, "id"));
		if (l_nID <= 0 || l_nID > p_IpAclList.size())
		{
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("删除数据错误!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}
	catch (...)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("删除数据错误!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	IpAclListDelete(p_IpAclList, l_nID);
	SaveIpAclListToFile(p_IpAclList, (HttpServer *)p_vData);
	l_jResData["result"] = "success";
	l_jResData["message"] = sconv("删除Item成功!");
	return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
}


void AddSecureSystemHandler(HttpServer* p_cHttpServer)
{
	p_cHttpServer->AddHttpRequestHandler("/secure/system/ipacllist", { SystemIpAclList,0,0,"返回IP-ACL列表" });
	p_cHttpServer->AddHttpRequestHandler("/secure/system/ipacldelete", { SystemIpAclDel,0,0,"删除IP-ACL项目" });
	p_cHttpServer->AddHttpRequestHandler("/secure/system/ipaclsave", { SystemIpAclSave,0,0,"生成IP-ACL设置脚本" });
	p_cHttpServer->AddHttpRequestHandler("/secure/system/ipaclset", { SystemIpAclSet,0,0,"修改IP-ACL设置信息" });
}
