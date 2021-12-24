#include "../web_service/http_handler.h"

bool GetDirList(std::string p_strPath, std::map<string, struct stat> &p_mapList)
{
	struct stat l_stat;
	struct dirent *dp;
	DIR *dirp;
	if ((dirp = (opendir(p_strPath.c_str()))) != NULL) {
		while ((dp = readdir(dirp)) != NULL) {
			std::string l_strFname = invs(p_strPath + std::string(dp->d_name));
			if (stat(l_strFname.c_str(), &l_stat) >= 0)
			{
				p_mapList.insert(make_pair(invs(std::string(dp->d_name)), l_stat));
			}
		}
		closedir(dirp);
	}
	else {
		return false;
	}
	return true;
}


void FileBrowserProc(struct mg_connection* p_pConn,struct http_message* p_pHttpMsg, string p_strRoot)
{
	LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "filebroser start");
	json l_jResData;
	std::map<string, struct stat> l_mapList;
	struct stat l_stat;
	string l_strFname, l_Type, l_Name, l_Path, l_strPath, l_strParent;
	l_Path = (GetHttpUrlQuery(p_pHttpMsg, "path"));
	l_Name = (GetHttpUrlQuery(p_pHttpMsg, "name"));
	l_Type = (GetHttpUrlQuery(p_pHttpMsg, "type"));
	p_strRoot = MakeURINorm(p_strRoot);
	LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "filebroser query");

#ifdef _WIN32
	if (p_strRoot.find(":/") == std::string::npos)
		p_strRoot = "." + p_strRoot.substr(0, p_strRoot.length() - 1);
	else
		p_strRoot = p_strRoot.substr(1, p_strRoot.length() - 2);
		
#else
	p_strRoot = p_strRoot.substr(0, p_strRoot.length() - 1);
	LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "filebroser p_strRoot %s :", p_strRoot.c_str());
#endif
	l_strPath = MakeURINorm(l_Path + "/" + l_Name);
	if (l_strPath.length() > 1)
	{
		int l_index = l_strPath.find_last_of('/', l_strPath.length() - 2);
		l_strParent = l_strPath.substr(0, l_index + 1);
	}
	else
		l_strParent = l_strPath;

	if (l_Type == "file" && (!l_Name.empty()))
		l_strFname = p_strRoot + l_strPath.substr(0, l_strPath.length() - 1);
	else if(l_Type == "path")
		l_strFname = p_strRoot + l_strPath;
	else
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("请求参数异常!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(),"");
	}

	if (stat(l_strFname.c_str(), &l_stat) < 0)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("请求文件或者目录不存在!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	if (S_ISDIR(l_stat.st_mode))
	{
		if (GetDirList(l_strFname, l_mapList))
		{
			vector<json> l_Flist;
			l_jResData["current"] = l_strPath;
			l_jResData["parent"] = l_strParent;

			for (auto &l_Fname : l_mapList)
			{
				if (l_Fname.first != "." && l_Fname.first != "..")
				{
					json l_Temp;
					l_Temp["name"] = sconv(l_Fname.first);
					l_Temp["size"] = l_Fname.second.st_size;
					l_Temp["mtime"] = l_Fname.second.st_mtime;
					if(S_ISDIR(l_Fname.second.st_mode))
						l_Temp["type"] = 1;
					else
						l_Temp["type"] = 0;
					l_Flist.push_back(l_Temp);
				}
			}
			l_jResData["count"] = l_Flist.size();
			l_jResData["list"] = l_Flist;
			return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
		}
		else
		{
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("获取目录信息失败!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}
	else if ((S_ISREG(l_stat.st_mode)))  // File Download
	{
		DownloadFile(p_pConn, p_pHttpMsg, sconv(l_strFname), sconv(l_Name));
	}
	else
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("不支持的文件类型!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
}


void AddFileBroswerHandler(HttpServer *p_cHttpServer)
{
	p_cHttpServer->AddHttpRequestHandler("/devdata/logfile/browser", 
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void
		{
			p_nEvent = p_nEvent;
			string l_strRootPath = ((HttpServer*)p_vData)->m_cWebConfig->m_strLogFileRootPath;
			l_strRootPath = sconv(l_strRootPath);
			FileBrowserProc(p_pConn, (struct http_message*)p_pHttpMsg, l_strRootPath);
		},0,0, "下载日志文件" });
	p_cHttpServer->AddHttpRequestHandler("/devdata/database/browser", 
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void
		{
			p_nEvent = p_nEvent;
			string l_strRootPath = ((HttpServer*)p_vData)->m_cWebConfig->m_strDataBaseRootPath;
			l_strRootPath = sconv(l_strRootPath);
			FileBrowserProc(p_pConn, (struct http_message*)p_pHttpMsg, l_strRootPath);
		},0,0,"下载数据库文件" });
}

