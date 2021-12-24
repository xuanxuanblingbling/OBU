#include "../web_service/http_handler.h"

#define IPBACKUPSET_PAGESIZE  20

typedef struct _BackUpSet
{
	int m_nId;               
	string m_strSource;    
	string m_strFileType;   
}BackUpSet;

typedef struct _BackUpParam
{
	string m_strFileType;
	string m_strBackUpPath;
	string m_strFileSize;
	string m_strFilePeroid;
	string m_strFileTimes;
	string m_srtBackUpPeroid;

}BackUpParam;


void to_json(json& p_j, const BackUpParam& p_sData)
{
	p_j = json{ { "filetype",p_sData.m_strFileType},
	{ "backuppath", sconv(p_sData.m_strBackUpPath)},
	{ "filesize", sconv(p_sData.m_strFileSize)} ,
	{ "fileperoid", sconv(p_sData.m_strFilePeroid)},
	{ "filetimes", sconv(p_sData.m_strFileTimes)},
	{ "backupperoid", sconv(p_sData.m_srtBackUpPeroid)}
	};
}

void from_json(const json& p_j, BackUpParam& p_sData)
{
	p_sData.m_strFileType = GetJsonStringData(p_j, "filetype");
	p_sData.m_strBackUpPath = GetJsonStringData(p_j, "backuppath");
	p_sData.m_strFileSize = GetJsonStringData(p_j, "filesize");
	p_sData.m_strFilePeroid = GetJsonStringData(p_j, "fileperoid");
	p_sData.m_strFileTimes = GetJsonStringData(p_j, "filetimes");
	p_sData.m_srtBackUpPeroid = GetJsonStringData(p_j, "backupperoid");
}


void to_json(json& p_j, const BackUpSet& p_sData)
{
	p_j = json{ { "seqid",p_sData.m_nId},
	{ "source", sconv(p_sData.m_strSource)},
	{ "filetype", sconv(p_sData.m_strFileType)}};
}

void from_json(const json& p_j, BackUpSet& p_sData)
{
	p_sData.m_nId = GetJsonIntData(p_j, "seqid");
	p_sData.m_strSource = GetJsonStringData(p_j, "source");
	p_sData.m_strFileType = GetJsonStringData(p_j, "filetype");

}

void SaveBackUpSetListToFile(list<BackUpSet> &p_BackUpSetList, HttpServer *p_HttpSever)
{
	struct stat l_stat;
	json l_jData;
	string l_strFname = p_HttpSever->m_cWebConfig->m_strBackUpSetConfigFile;
	fstream l_File(l_strFname, ios::out | ios::trunc);
	if (l_File.is_open())
	{
		if (p_BackUpSetList.empty())
			l_File << "[]";
		else
		{
			l_jData = json(p_BackUpSetList);
			l_File << l_jData.dump(1, '\t');
		}
		l_File.close();
		if (stat(l_strFname.c_str(), &l_stat) >= 0)
		{
			p_HttpSever->m_sJsonSet[JSON_BACKUPSET].data = l_jData;
			p_HttpSever->m_sJsonSet[JSON_BACKUPSET].mtime = l_stat.st_mtime;
		}
	}
}

void BackUpSetListInsert(list<BackUpSet> &p_BackUpSetList, BackUpSet p_BackUpSet, int p_nAfterId)
{

	unsigned int l_nCount = 1;
	if (p_nAfterId <= 0)
		p_BackUpSetList.push_front(p_BackUpSet);
	else if (p_nAfterId > p_BackUpSetList.size())
		p_BackUpSetList.push_back(p_BackUpSet);
	else
	{
		for (auto l_lData = p_BackUpSetList.begin(); l_lData != p_BackUpSetList.end(); l_lData++)
		{
			if (p_nAfterId == l_nCount)
			{
				p_BackUpSetList.insert(l_lData, p_BackUpSet);
				break;
			}
			l_nCount++;
		}
	}
	l_nCount = 1;
	for (auto &l_lData : p_BackUpSetList)
		l_lData.m_nId = l_nCount++;
}

void BackUpSetListDelete(list<BackUpSet> &p_BackUpSetList, int p_nCurrentId)
{
	unsigned int l_nCount = 1;
	for (auto l_lData = p_BackUpSetList.begin(); l_lData != p_BackUpSetList.end(); l_lData++)
	{
		if (p_nCurrentId == (*l_lData).m_nId)
		{
			p_BackUpSetList.erase(l_lData);
			break;
		}
	}
	for (auto &l_lData : p_BackUpSetList)
		l_lData.m_nId = l_nCount++;

}
bool ConvertJsonToBackUpSetLits(json &p_jData, list<BackUpSet> &p_BackUpSetList, HttpServer *p_HttpSever)
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
				p_BackUpSetList.push_back(p_jData[k]);
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
		SaveBackUpSetListToFile(p_BackUpSetList, p_HttpSever);
	}
	return l_RetVal;
}

void SystemBackUpSetList(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	json l_jReqData;
	unsigned int l_pageNo, l_pageSize, l_nStart, l_nEnd;
	list<BackUpSet> l_BackUpSetList;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	HttpServer * l_pHttpServer = (HttpServer *)p_vData;

	GetJsonDataFromFile(JSON_BACKUPSET, (HttpServer *)p_vData);
	json &l_webData = ((HttpServer *)p_vData)->m_sJsonSet[JSON_BACKUPSET].data;

	l_jReqData["pageSize"] = IPBACKUPSET_PAGESIZE;
	l_jReqData["pageNo"] = 1;
	l_jReqData["count"] = 0;
	l_jReqData["list"] = "";
	ConvertJsonToBackUpSetLits(l_webData, l_BackUpSetList, l_pHttpServer);

	try
	{
		l_pageNo = stoi(GetHttpUrlParma(&l_pHttpMsg->body, "pageNo"));
		l_pageSize = stoi(GetHttpUrlParma(&l_pHttpMsg->body, "pageSize"));
	}
	catch (...)
	{
		l_pageNo = 1;
		l_pageSize = IPBACKUPSET_PAGESIZE;
	}
	l_nStart = (l_pageNo - 1) * l_pageSize;

	if (l_nStart >= l_webData.size())
		l_pageNo = 1;

	l_nStart = (l_pageNo - 1) * l_pageSize;
	l_nEnd = l_nStart + l_pageSize;
	l_nEnd = (l_nEnd > l_webData.size()) ? l_webData.size() : l_nEnd;

	l_jReqData["pageSize"] = l_pageSize;
	l_jReqData["pageNo"] = l_pageNo;
	l_jReqData["count"] = l_BackUpSetList.size();
	vector<json> l_jDataList;
	auto l_listData = l_BackUpSetList.begin();
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
void SystemBackUpSetDel(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	json l_jResData;
	int l_nID;
	list<BackUpSet> p_BackUpSetList;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	GetJsonDataFromFile(JSON_BACKUPSET, (HttpServer *)p_vData);
	json &l_webData = ((HttpServer *)p_vData)->m_sJsonSet[JSON_BACKUPSET].data;

	ConvertJsonToBackUpSetLits(l_webData, p_BackUpSetList, (HttpServer *)p_vData);


	try
	{
		l_nID = stoi(GetHttpUrlQuery(l_pHttpMsg, "id"));
		if (l_nID <= 0 || l_nID > p_BackUpSetList.size())
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
	BackUpSetListDelete(p_BackUpSetList, l_nID);
	SaveBackUpSetListToFile(p_BackUpSetList, (HttpServer *)p_vData);
	l_jResData["result"] = "success";
	l_jResData["message"] = sconv("删除Item成功!");
	return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
}

void SystemBackUpSetSave(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	int l_nAfterId;
	json l_jRecData, l_jResData;
	BackUpSet l_BackUpSet;
	list<BackUpSet> l_BackUpSetList;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strBody = string(l_pHttpMsg->body.p, l_pHttpMsg->body.len);
	GetJsonDataFromFile(JSON_BACKUPSET, (HttpServer *)p_vData);
	json &l_webData = ((HttpServer *)p_vData)->m_sJsonSet[JSON_BACKUPSET].data;

	ConvertJsonToBackUpSetLits(l_webData, l_BackUpSetList, (HttpServer *)p_vData);

	try {
		l_jRecData = json::parse(l_strBody);
		l_BackUpSet = l_jRecData; //将JSON转换为结构体，转换方式to_json和from_json
		if (l_BackUpSet.m_nId < 0)
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

	if (l_BackUpSet.m_nId < 0)
	{
		BackUpSetListInsert(l_BackUpSetList, l_BackUpSet, l_nAfterId);
		SaveBackUpSetListToFile(l_BackUpSetList, (HttpServer *)p_vData);
	}
	else
	{
		for (auto &l_lData : l_BackUpSetList)
		{
			if (l_lData.m_nId == l_BackUpSet.m_nId)
			{
				l_lData = l_BackUpSet;
				break;
			}
		}
		SaveBackUpSetListToFile(l_BackUpSetList, (HttpServer *)p_vData);
	}


	l_jResData["result"] = "success";
	l_jResData["message"] = sconv("保存数据成功!");
	return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");

}

/*****************/

void SaveBackUpParamListToFile(list<BackUpParam> &p_BackUpParamList, HttpServer *p_HttpSever)
{
	struct stat l_stat;
	json l_jData;
	string l_strFname = p_HttpSever->m_cWebConfig->m_strBackUpParamConfigFile;
	fstream l_File(l_strFname, ios::out | ios::trunc);
	if (l_File.is_open())
	{
		if (p_BackUpParamList.empty())
			l_File << "[]";
		else
		{
			l_jData = json(p_BackUpParamList);
			l_File << l_jData.dump(1, '\t');
		}
		l_File.close();
		if (stat(l_strFname.c_str(), &l_stat) >= 0)
		{
			p_HttpSever->m_sJsonSet[JSON_BACKUPPARAM].data = l_jData;
			p_HttpSever->m_sJsonSet[JSON_BACKUPPARAM].mtime = l_stat.st_mtime;
		}
	}
}

bool ConvertJsonToBackUpParamLits(json &p_jData, list<BackUpParam> &p_BackUpParamList, HttpServer *p_HttpSever)
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
				p_BackUpParamList.push_back(p_jData[k]);
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
		SaveBackUpParamListToFile(p_BackUpParamList, p_HttpSever);
	}
	return l_RetVal;
}
void SaveParam(BackUpParam &p_BackUpParam, HttpServer *p_HttpSever)
{
	list<BackUpParam> l_BackUpParamList;
	GetJsonDataFromFile(JSON_BACKUPPARAM, p_HttpSever);
	json &l_webData = (p_HttpSever)->m_sJsonSet[JSON_BACKUPPARAM].data;

	ConvertJsonToBackUpParamLits(l_webData, l_BackUpParamList, p_HttpSever);
	if (l_BackUpParamList.empty())
	{
		l_BackUpParamList.push_back(p_BackUpParam);
	}
	else
	{
		for (auto l_lData = l_BackUpParamList.begin(); l_lData != l_BackUpParamList.end(); l_lData++)
		{
			if (p_BackUpParam.m_strFileType == (*l_lData).m_strFileType)
			{
				(*l_lData) = p_BackUpParam;
				SaveBackUpParamListToFile(l_BackUpParamList, p_HttpSever);
				return;
			}
		}
		l_BackUpParamList.push_back(p_BackUpParam);
	}
	
	SaveBackUpParamListToFile(l_BackUpParamList, p_HttpSever);
}

void ListParam(struct mg_connection* p_pConn, BackUpParam &p_BackUpParam, HttpServer *p_HttpSever)
{
	unsigned int l_nCnt = 1;
	json l_jResData ,l_jReqData;
	list<BackUpParam> l_BackUpParamList;

	GetJsonDataFromFile(JSON_BACKUPPARAM, p_HttpSever);
	json &l_webData = (p_HttpSever)->m_sJsonSet[JSON_BACKUPPARAM].data;

	ConvertJsonToBackUpParamLits(l_webData, l_BackUpParamList, p_HttpSever);

	json l_jDataList;

	if (l_BackUpParamList.empty())
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("配置文件为空!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	else
	{
		for (auto l_lData = l_BackUpParamList.begin(); l_lData != l_BackUpParamList.end(); l_lData++)
		{
	
		
			if (p_BackUpParam.m_strFileType == (*l_lData).m_strFileType)
			{
				l_jDataList["filetype"] = (*l_lData).m_strFileType;
				l_jDataList["backuppath"] = (*l_lData).m_strBackUpPath;
				l_jDataList["filesize"] = (*l_lData).m_strFileSize;
				l_jDataList["fileperoid"] = (*l_lData).m_strFilePeroid;
				l_jDataList["filetimes"] = (*l_lData).m_strFileTimes;
				l_jDataList["backupperoid"] = (*l_lData).m_srtBackUpPeroid;

				l_jResData["list"] = l_jDataList;
				l_jResData["ConfigType"] = "setParam";
				l_jResData["Operation"] = "query";
				l_jResData["result"] = "success";
				l_jResData["message"] = sconv("读取成功");

				HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
				return;
			}
		}
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("没有此配置文件");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");

	}
	
}
void SystemBackUpParam(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	json l_jReqData, l_jResData;
	string l_strType, l_strModeName;
	BackUpParam l_BackUpParam;
	list<BackUpParam> l_BackUpParamList;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strOpt = GetHttpUrlQuery(l_pHttpMsg, "op");
	string l_strBody = string(l_pHttpMsg->body.p, l_pHttpMsg->body.len);
	try {
		l_jReqData = json::parse(l_strBody);
		l_BackUpParam = l_jReqData;
		//l_strType = GetJsonStringData(l_jReqData, "ConfigType");
	}
	catch (...)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("请求消息解析错误!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	if (!l_strOpt.compare("set"))
	{	
		SaveParam(l_BackUpParam,(HttpServer *)p_vData);

		l_jResData["result"] = "success";
		l_jResData["message"] = sconv("参数保存成功!");
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
	}
	else
	{
		ListParam(p_pConn, l_BackUpParam, (HttpServer *)p_vData);
	}
}
/****************************************/

void SystemBackUpSet(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{

	list<BackUpParam> l_BackUpParamList;
	list<BackUpSet> l_BackUpSetList;
	string cmd;

	json l_jReqData;
	HttpServer * l_pHttpServer = (HttpServer *)p_vData;
	GetJsonDataFromFile(JSON_BACKUPPARAM, (HttpServer *)p_vData);
	json &l_webData = ((HttpServer *)p_vData)->m_sJsonSet[JSON_BACKUPPARAM].data;
	ConvertJsonToBackUpParamLits(l_webData, l_BackUpParamList, l_pHttpServer);

	//HttpServer * l_pHttpServer = (HttpServer *)p_vData;
	GetJsonDataFromFile(JSON_BACKUPSET, (HttpServer *)p_vData);
	json &l_webData2 = ((HttpServer *)p_vData)->m_sJsonSet[JSON_BACKUPSET].data;
	ConvertJsonToBackUpSetLits(l_webData2, l_BackUpSetList, l_pHttpServer);
	system("systemctl disable bkset.timer");
	system("systemctl disable bksetfile.timer");
	system("systemctl disable bkapp.timer");
	system("systemctl disable bkappfile.timer");
	system("systemctl disable bklog.timer");
	system("systemctl disable bklogfile.timer");
	system("systemctl disable bkdata.timer");
	system("systemctl disable bkdatafile.timer");

	for (auto l_lData = l_BackUpParamList.begin(); l_lData != l_BackUpParamList.end(); l_lData++)
	{
		if ((*l_lData).m_strFileType == "0")
		{
			for (auto l_lSetData = l_BackUpSetList.begin(); l_lSetData != l_BackUpSetList.end(); l_lSetData++)
			{
				if ((*l_lSetData).m_strFileType == "配置文件")
				{
					cmd = "sed -i \"2cmkdir -p " + (*l_lData).m_strBackUpPath + "setfile/setfile" + (*l_lSetData).m_strSource + "\""+ " config/bksetparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"3crsync -azvr " + (*l_lSetData).m_strSource + " " + (*l_lData).m_strBackUpPath + "setfile/setfile" + (*l_lSetData).m_strSource+"\"" + " config/bksetparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"4ccd "  + (*l_lData).m_strBackUpPath + "setfile/" +"\""+ " config/bksetparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"10climitfilesize=" + (*l_lData).m_strFileSize + "\""+ " config/bksetparam.sh";
					system((char *)cmd.c_str());
				}
			}//备份脚本设置

			if ((*l_lData).m_srtBackUpPeroid == "0")
			{
				system("sed -i \"5cOnUnitActiveSec=5min\" /lib/systemd/system/bkset.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "1")
			{
				system("sed -i \"5cOnUnitActiveSec=1hrs\" /lib/systemd/system/bkset.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "2")
			{
				system("sed -i \"5cOnUnitActiveSec=12hrs\" /lib/systemd/system/bkset.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "3")
			{
				system("sed -i \"5cOnUnitActiveSec=24hrs\" /lib/systemd/system/bkset.timer");
			}
			else
			{
				l_jReqData["result"] = "error";
				l_jReqData["message"] = sconv("备份周期设置失败!");
				return HttpSendResponse(p_pConn, 500, "json", l_jReqData.dump(), "");
			}
			system("systemctl enable bkset.timer");//备份周期的设置

			cmd = "sed -i \"2ccd " + (*l_lData).m_strBackUpPath + "setfile/" + "\""+" config/bksetfile.sh";
			system((char *)cmd.c_str());

			cmd = "sed -i \"4cfiletimes= " + (*l_lData).m_strFileTimes +"\""+ " config/bksetfile.sh";
			system((char *)cmd.c_str());//归档次数设置

			cmd = "sed -i \"5c5cOnUnitActiveSec=" + (*l_lData).m_strFilePeroid + "days" + "\"" + " /lib/systemd/system/bksetfile.timer";
			system((char *)cmd.c_str());
			system("systemctl enable bksetfile.timer");//归档周期的设置
		}
		else if ((*l_lData).m_strFileType == "1")
		{
			for (auto l_lSetData = l_BackUpSetList.begin(); l_lSetData != l_BackUpSetList.end(); l_lSetData++)
			{
				if ((*l_lSetData).m_strFileType == "日志文件")
				{
					cmd = "sed -i \"2cmkdir -p " + (*l_lData).m_strBackUpPath + "logfile/logfile" + (*l_lSetData).m_strSource + "\"" + " config/bklogparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"3crsync -azvr " + (*l_lSetData).m_strSource + " " + (*l_lData).m_strBackUpPath + "logfile/logfile" + (*l_lSetData).m_strSource + "\"" + " config/bklogparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"4ccd " + (*l_lData).m_strBackUpPath + "logfile/" + "\"" + " config/bklogparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"10climitfilesize=" + (*l_lData).m_strFileSize + "\"" + " config/bklogparam.sh";
					system((char *)cmd.c_str());
				}
			}//备份脚本设置

			if ((*l_lData).m_srtBackUpPeroid == "0")
			{
				system("sed -i \"5cOnUnitActiveSec=5min\" /lib/systemd/system/bklog.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "1")
			{
				system("sed -i \"5cOnUnitActiveSec=1hrs\" /lib/systemd/system/bklog.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "2")
			{
				system("sed -i \"5cOnUnitActiveSec=12hrs\" /lib/systemd/system/bklog.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "3")
			{
				system("sed -i \"5cOnUnitActiveSec=24hrs\" /lib/systemd/system/bklog.timer");
			}
			else
			{
				l_jReqData["result"] = "error";
				l_jReqData["message"] = sconv("备份周期设置失败!");
				return HttpSendResponse(p_pConn, 500, "json", l_jReqData.dump(), "");
			}

			system("systemctl enable bklog.timer");//备份周期的设置

			cmd = "sed -i \"2ccd " + (*l_lData).m_strBackUpPath + "logfile/" + "\"" + " config/bklogfile.sh";
			system((char *)cmd.c_str());

			cmd = "sed -i \"4cfiletimes= " + (*l_lData).m_strFileTimes + "\"" + " config/bklogfile.sh";
			system((char *)cmd.c_str());//归档次数设置

			cmd = "sed -i \"5c5cOnUnitActiveSec=" + (*l_lData).m_strFilePeroid + "days" + "\"" + " /lib/systemd/system/bklogfile.timer";
			system((char *)cmd.c_str());
			system("systemctl enable bklogfile.timer");//归档周期的设置
		}
		else if ((*l_lData).m_strFileType == "2")
		{
			for (auto l_lSetData = l_BackUpSetList.begin(); l_lSetData != l_BackUpSetList.end(); l_lSetData++)
			{
				if ((*l_lSetData).m_strFileType == "应用程序文件")
				{
					cmd = "sed -i \"2cmkdir -p " + (*l_lData).m_strBackUpPath + "appfile/appfile" + (*l_lSetData).m_strSource + "\"" + " config/bkappparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"3crsync -azvr " + (*l_lSetData).m_strSource + " " + (*l_lData).m_strBackUpPath + "appfile/appfile" + (*l_lSetData).m_strSource + "\"" + " config/bkappparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"4ccd " + (*l_lData).m_strBackUpPath + "appfile/" + "\"" + " config/bkappparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"10climitfilesize=" + (*l_lData).m_strFileSize + "\"" + " config/bkappparam.sh";
					system((char *)cmd.c_str());
				}
			}//备份脚本设置

			if ((*l_lData).m_srtBackUpPeroid == "0")
			{
				system("sed -i \"5cOnUnitActiveSec=5min\" /lib/systemd/system/bkapp.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "1")
			{
				system("sed -i \"5cOnUnitActiveSec=1hrs\" /lib/systemd/system/bkapp.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "2")
			{
				system("sed -i \"5cOnUnitActiveSec=12hrs\" /lib/systemd/system/bkapp.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "3")
			{
				system("sed -i \"5cOnUnitActiveSec=24hrs\" /lib/systemd/system/bkapp.timer");
			}
			else
			{
				l_jReqData["result"] = "error";
				l_jReqData["message"] = sconv("备份周期设置失败!");
				return HttpSendResponse(p_pConn, 500, "json", l_jReqData.dump(), "");
			}

			system("systemctl enable bkapp.timer");//备份周期的设置


			cmd = "sed -i \"2ccd " + (*l_lData).m_strBackUpPath + "appfile/" + "\"" + " config/bkappfile.sh";
			system((char *)cmd.c_str());

			cmd = "sed -i \"4cfiletimes= " + (*l_lData).m_strFileTimes + "\"" + " config/bkappfile.sh";
			system((char *)cmd.c_str());//归档次数设置

			cmd = "sed -i \"5c5cOnUnitActiveSec=" + (*l_lData).m_strFilePeroid + "days" + "\"" + " /lib/systemd/system/bkappfile.timer";
			system((char *)cmd.c_str());
			system("systemctl enable bkappfile.timer");//归档周期的设置
		}
		else if ((*l_lData).m_strFileType == "3")
		{
			for (auto l_lSetData = l_BackUpSetList.begin(); l_lSetData != l_BackUpSetList.end(); l_lSetData++)
			{
				if ((*l_lSetData).m_strFileType == "数据库文件")
				{
					cmd = "sed -i \"2cmkdir -p " + (*l_lData).m_strBackUpPath + "datafile/datafile" + (*l_lSetData).m_strSource + "\"" + " config/bkdataparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"3crsync -azvr " + (*l_lSetData).m_strSource + " " + (*l_lData).m_strBackUpPath + "datafile/datafile" + (*l_lSetData).m_strSource + "\"" + " config/bkdataparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"4ccd " + (*l_lData).m_strBackUpPath + "datafile/" + "\"" + " config/bkdataparam.sh";
					system((char *)cmd.c_str());
					cmd = "sed -i \"10climitfilesize=" + (*l_lData).m_strFileSize + "\"" + " config/bkdataparam.sh";
					system((char *)cmd.c_str());
				}
			}//备份脚本设置

			if ((*l_lData).m_srtBackUpPeroid == "0")
			{
				system("sed -i \"5cOnUnitActiveSec=5min\" /lib/systemd/system/bkdata.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "1")
			{
				system("sed -i \"5cOnUnitActiveSec=1hrs\" /lib/systemd/system/bkdata.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "2")
			{
				system("sed -i \"5cOnUnitActiveSec=12hrs\" /lib/systemd/system/bkdata.timer");
			}
			else if ((*l_lData).m_srtBackUpPeroid == "3")
			{
				system("sed -i \"5cOnUnitActiveSec=24hrs\" /lib/systemd/system/bkdata.timer");
			}
			else
			{
				l_jReqData["result"] = "error";
				l_jReqData["message"] = sconv("备份周期设置失败!");
				return HttpSendResponse(p_pConn, 500, "json", l_jReqData.dump(), "");
			}

			system("systemctl enable bkdata.timer");//备份周期的设置


			cmd = "sed -i \"2ccd " + (*l_lData).m_strBackUpPath + "datafile/" + "\"" + " config/bkdatafile.sh";
			system((char *)cmd.c_str());

			cmd = "sed -i \"4cfiletimes= " + (*l_lData).m_strFileTimes + "\"" + " config/bkdatafile.sh";
			system((char *)cmd.c_str());//归档次数设置

			cmd = "sed -i \"5c5cOnUnitActiveSec=" + (*l_lData).m_strFilePeroid + "days" + "\"" + " /lib/systemd/system/bkdatafile.timer";
			system((char *)cmd.c_str());
			system("systemctl enable bkdatafile.timer");//归档周期的设置
			}
			else
			{
				l_jReqData["result"] = "error";
				l_jReqData["message"] = sconv("文件类型设置失败!");
				return HttpSendResponse(p_pConn, 500, "json", l_jReqData.dump(), "");
			}
	}

	l_jReqData["result"] = "success";
	l_jReqData["message"] = sconv("设置数据成功!");
	return HttpSendResponse(p_pConn, 200, "json", l_jReqData.dump(), "");


}
void AddBackUpSystemHandler(HttpServer* p_cHttpServer)
{
	p_cHttpServer->AddHttpRequestHandler("/update/system/backuplist", { SystemBackUpSetList,0,0,"查询备份列表" });
	p_cHttpServer->AddHttpRequestHandler("/update/system/backupdelete", {SystemBackUpSetDel,0,0,"删除备份信息" });
	p_cHttpServer->AddHttpRequestHandler("/update/system/backupsave", {SystemBackUpSetSave,0,0,"保存备份信息" });
	p_cHttpServer->AddHttpRequestHandler("/update/system/backupparam", {SystemBackUpParam,0,0,"备份路径设置" });
	p_cHttpServer->AddHttpRequestHandler("/update/system/backupset", {SystemBackUpSet,0,0,"设置备份信息" });
}