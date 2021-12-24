#include "../web_service/http_handler.h"




void SystemAppUpdataStart(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	/*升级包的解压和校验*/
	json l_jResData;
	char l_strNewResultBuf[128], l_strOldResultBuf[128];
    FILE *Newfp, *Oldfp;
    int l_iRc = 0;

	struct stat l_stat;
	string l_strFname, l_strArchiveName, l_strVerifyCmd, l_strMD5Name;
	std::map<string, struct stat> l_mapListAcrhive, l_mapListMD5;

	l_strFname = ((HttpServer*)p_vData)->m_cWebConfig->m_strAppUpdatePath;
	l_strFname = sconv(l_strFname);
	l_strFname = MakeURINorm(l_strFname);

	if (stat(l_strFname.c_str(), &l_stat) < 0)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("请求目录不存在!");
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "web request dir is not exist");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	if (GetDirList(l_strFname, l_mapListAcrhive))
	{
		std::cout<<"firstnum:" << l_mapListAcrhive.size()<<endl;
		for (auto &l_Fname : l_mapListAcrhive)
		{
			std::cout<<"l_fname:" <<l_Fname.first<<endl;
			if (l_Fname.first != "." && l_Fname.first != "..")
			{
				if(l_Fname.first.find(".md5") != -1)
				{
					l_strMD5Name = l_strFname + l_Fname.first;
					continue;
				}
				//else if(l_Fname.first.find(".zip") != -1)
				else if(l_Fname.first.find(".tar") != -1)
				{
					l_strArchiveName = l_strFname + l_Fname.first.substr(0, l_Fname.first.length()-4);
					l_strVerifyCmd = "md5sum " + l_strFname + l_Fname.first;
					continue;
				}
				else
				{
					l_jResData["result"] = "error";
					l_jResData["message"] = sconv("压缩包格式错误!");
					LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "Compressed package format error");
					return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
				}
			}
		}

		if(l_strVerifyCmd.empty())
		{
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("md5文件未找到!");
			LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "md5 file not found");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}

		if(l_strArchiveName.empty())
		{
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("压缩包未找到!");
			LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "archive packet not found");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}
	else
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("未读取到文件夹中文件!");
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "file information in the folder is not obtained");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}


    Newfp = popen(l_strVerifyCmd.c_str(), "r");
	if(NULL == Newfp)
	{
        l_jResData["result"] = "error";
		l_jResData["message"] = sconv("生成MD5值失败!");
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "produced md5 value failed");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");	    
    }
	if(fgets(l_strNewResultBuf, sizeof(l_strNewResultBuf), Newfp) != NULL)
	{
		for(int i=0;i<sizeof(l_strNewResultBuf);i++)
		{
			if(l_strNewResultBuf[i] == ' ')
			{
				memset(&l_strNewResultBuf[i], '\0', sizeof(l_strNewResultBuf)-i);
				break;
			}
		}
	}

    l_iRc = pclose(Newfp);
    if(-1 == l_iRc)
    {
        l_jResData["result"] = "error";
		l_jResData["message"] = sconv("关闭文件值指针失败!");
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "file information in the folder is not obtained");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	Oldfp = fopen(l_strMD5Name.c_str(), "r");
	if(NULL == Oldfp)
	{
        l_jResData["result"] = "error";
		l_jResData["message"] = sconv("打开md5文件失败!");
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "open .md5 file failed");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");	    
    }
	if(fgets(l_strOldResultBuf, sizeof(l_strOldResultBuf), Oldfp) != NULL)
	{
		for(int i=0;i<sizeof(l_strOldResultBuf);i++)
		{
			if(l_strOldResultBuf[i] == '\n')
			{
				memset(&l_strOldResultBuf[i], '\0', sizeof(l_strOldResultBuf)-i);
				break;
			}
		}
	}
	fclose(Oldfp);
	LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "web l_strNewResultBuf %s", l_strNewResultBuf);
	LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "web l_strOldResultBuf %s", l_strOldResultBuf);

    if(memcmp(l_strOldResultBuf, l_strNewResultBuf, 32) == 0)  //md5的固定长度是32
    {
		/* 校验成功后直接进行升级*/
        // l_jResData["result"] = "success";
		// l_jResData["message"] = sconv("升级包校验成功!");
		// return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
    }
    else
    {
        l_jResData["result"] = "error";
		l_jResData["message"] = sconv("升级包校验失败!");
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "update packet verify failed");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
    }
    /* 配置文件写入升级状态 */
	CSimpleIniA l_iniUpdateStatuFile(true, true, true);
	l_iniUpdateStatuFile.SetUnicode();
	l_iniUpdateStatuFile.LoadFile(Update_StateFile);
	l_iniUpdateStatuFile.SetValue("UpdataStatus","ShellStatus","1");
    l_iniUpdateStatuFile.SaveFile(Update_StateFile);
	/* 执行升级脚本 检测脚本执行状态 */
	FILE *fp = NULL;
	char l_an8cmd[128]={0};
	char l_an8recvbuff[256] = {0};
	sprintf(l_an8cmd,"sh %s",Update_Scrip);
    fp = popen(l_an8cmd,"r");
	while(fgets(l_an8recvbuff,sizeof(l_an8recvbuff),fp) != NULL)
	{
		LogPrint(LOG_LEVEL_NOTICE,LOG_MODLE_NAME,"%s",l_an8recvbuff);
	}
	if(pclose(fp) !=0)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("升级脚本执行失败!");
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "update update shell excute failed");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	else
	{
		l_jResData["result"] = "succeed";
		l_jResData["message"] = sconv("升级脚本执行成功!");
		LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "update update shell excute succeed");
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
	}
	
	/* 配置文件写入升级完成状态 */
	/* Http返回信息 */

}


void SystemAppUpdataInfo(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	json l_jData;
	p_nEvent = p_nEvent;
	vector<string> l_vSection;
	HttpServer * l_pHttpServer = (HttpServer *)p_vData;
	string p_strInfoFile = l_pHttpServer->m_cWebConfig->m_strAppUpdateInfoFile;
	printf("====[test] sysdata info %s====\n",p_strInfoFile.c_str());
	ProcInitDataRequest(p_pConn, p_strInfoFile, l_vSection, l_jData);
	/* 配置文件写入升级状态 */
	CSimpleIniA l_iniUpdateStatuFile(true, true, true);
	l_iniUpdateStatuFile.SetUnicode();
	l_iniUpdateStatuFile.LoadFile(Update_StateFile);
	l_iniUpdateStatuFile.SetValue("UpdataStatus","ShellStatus","2");
    l_iniUpdateStatuFile.SaveFile(Update_StateFile);
}


void SystemFileUpdataStart(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	json p_jData;
	p_nEvent = p_nEvent;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strModuleName = GetHttpUrlQuery(l_pHttpMsg, "module"), l_strVersion;
	if (l_strModuleName.empty())
	{
		p_jData["result"] = "error";
		p_jData["message"] = sconv("请求参数异常!");
		return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
	}

	p_jData["ModuleName"] = l_strModuleName;
	p_jData["path"] = sconv(((HttpServer *)p_vData)->m_cWebConfig->m_strFileUploadPath);
	p_jData["ConfigType"] = "UpdataParamFile";
	p_jData["Operation"] = "set";
	p_jData["Source"] = GenerWebSign;
	string l_strSendData = p_jData.dump();
	//return ProcTcpSendData(p_pConn, l_strSendData, CLIENT_MODULE, (HttpServer *)p_vData);
	p_jData["result"] = "error";
	p_jData["message"] = sconv("请求参数异常!");
	return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
}


void AddSystemUpdateHandler(HttpServer *p_pHttpServer)
{
	p_pHttpServer->AddUploadPath("/system/updata/uploadapp", p_pHttpServer->m_cWebConfig->m_strAppUpdatePath);
	p_pHttpServer->AddUploadPath("/system/bakup/uploadfile", p_pHttpServer->m_cWebConfig->m_strFileUploadPath);
	p_pHttpServer->AddHttpRequestHandler("/system/updata/uploadapp", 
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)->void {}, 0,0,"上传程序升级文件" });
	p_pHttpServer->AddHttpRequestHandler("/system/bakup/uploadfile",
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)->void {}, 0,0,"上传数据文件到目录" });

	p_pHttpServer->AddHttpRequestHandler("/system/updata/updatastart", { SystemAppUpdataStart, 0,0,"启动系统升级" });
	p_pHttpServer->AddHttpRequestHandler("/system/updata/updatainfo", { SystemAppUpdataInfo,0,0,"获取当前升级进度" });

	p_pHttpServer->AddHttpRequestHandler("/system/bakup/updatafile", { SystemFileUpdataStart,0,0,"更新数据文件到系统" });
	

	p_pHttpServer->AddHttpRequestHandler("/system/bakup/filebrowser", {
		[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			json l_jResData;
			p_nEvent = p_nEvent;
			struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
			HttpServer* l_Http = (HttpServer*)p_vData;
			string l_strModule = GetHttpUrlQuery(l_pHttpMsg, "module"), l_strRootPath;
			if (l_strModule == "SoftWareRootPath")
				l_strRootPath = l_Http->m_cWebConfig->m_strSoftWareRootPath;
			else if (l_strModule == "ConfigFileRootPath")
				l_strRootPath = l_Http->m_cWebConfig->m_strConfigFileRootPath;
			else if (l_strModule == "DataBaseRootPath")
				l_strRootPath = l_Http->m_cWebConfig->m_strDataBaseRootPath;
			else if (l_strModule == "LogFileRootPath")
				l_strRootPath = l_Http->m_cWebConfig->m_strLogFileRootPath;
			else if (l_strModule == "CertFileRootPath")
				l_strRootPath = l_Http->m_cWebConfig->m_strCertFileRootPath;
			else if (l_strModule == "SysBackupPath")
				l_strRootPath = l_Http->m_cWebConfig->m_strBackupRootPath;
			else
			{
				l_jResData["result"] = "error";
				l_jResData["message"] = sconv("未知文件类型!");
				return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
			}
			l_strRootPath = sconv(l_strRootPath);
			FileBrowserProc(p_pConn, l_pHttpMsg, l_strRootPath);
		}, 0,0, "浏览系统的数据文件" });

}
