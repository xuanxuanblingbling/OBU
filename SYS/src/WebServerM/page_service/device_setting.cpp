#include "../web_service/http_handler.h"
#include <set>
#include <regex>
#include "Cfg.h"  

#define AIDLIST_PAGESIZE  20

void DeviceParamSetToStruct(struct mg_connection* p_pConn, void* p_pHttpMsg,
	int p_nJsonNum, int p_nClientNum, HttpServer * p_pHttpServer)
{
		json l_jReqData, l_jResData;
	string l_strType, l_strModeName;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strOpt = GetHttpUrlQuery(l_pHttpMsg, "op");
	string l_strBody = string(l_pHttpMsg->body.p, l_pHttpMsg->body.len);
	printf("====[test] string %s \n",l_strBody.c_str());

	try {
		l_jReqData = json::parse(l_strBody);
		l_strType = GetJsonStringData(l_jReqData, "ConfigType");
	}
	catch (...)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver request message %s wrong", l_strType);
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("请求消息解析错误!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	switch (p_nJsonNum)
	{
	case JSON_DEVSTATIC:
		l_strModeName = "DevStaticInfo";
		break;
	case JSON_PROTOCOL:
		l_strModeName = "Message";
		break;
	case JSON_BASICINFO :
		l_strModeName = "BasicInfo";
		break;
	case JSON_V2XSERVICE :
		l_strModeName = "V2XService";
		break;
	case JSON_MODULECONFIG :
		l_strModeName = "ModuleConfig";
		break;
	case JSON_VDSMODULE:
		l_strModeName = "VDS";
		break;
	case JSON_MCUMODULE:
		l_strModeName = "MCU";
		break;
	case JSON_NETWORKMODULE:
		l_strModeName = "NetWork";
		break;
	// case JSON_APPASCFG:
	// 	l_strModeName = "AppASCfg";
	// 	break;
	// case JSON_APPMMCFG:
	// 	l_strModeName = "AppMMCfg";
	// 	break;
	// case JSON_APPMTCFG:
	// 	l_strModeName = "AppMTCfg";
	// 	break;
	// case JSON_APPTLCFG:
	// 	l_strModeName = "AppTLCfg";
	// 	break;		
	default:
		l_strModeName = "None";
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Module %d does not exist", p_nJsonNum);
	}
	if (!l_strOpt.compare("set"))
	{
		l_jReqData["ConfigType"] = l_strType;
		l_jReqData["Operation"] = "set";
		l_jReqData["ModuleName"] = l_strModeName;
		ProcJsonDataSetToStruct(p_pConn, p_nJsonNum, l_jReqData, p_pHttpServer);
	}
	else
	{
		vector<string> l_vSection;
		l_jResData["ConfigType"] = l_strType;
		l_jResData["ModuleName"] = l_strModeName;
		l_jResData["Operation"] = "query";
		l_jResData["message"] = sconv("查询参数成功");
		ProcJsonDataRequest(p_pConn, p_nJsonNum, l_vSection, l_jResData, p_pHttpServer);
	}
}

void DeviceParamSetting(struct mg_connection* p_pConn, void* p_pHttpMsg,
	int p_nJsonNum, int p_nClientNum, HttpServer * p_pHttpServer, const set<string> l_setType)
{
	json l_jReqData, l_jResData;
	string l_strType, l_strModeName;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strOpt = GetHttpUrlQuery(l_pHttpMsg, "op");
	string l_strBody = string(l_pHttpMsg->body.p, l_pHttpMsg->body.len);
	try {
		l_jReqData = json::parse(l_strBody);
		l_strType = GetJsonStringData(l_jReqData, "ConfigType"); //添加循环，可能有多项

		if (!l_setType.empty() &&(l_setType.find(l_strType) == l_setType.end()))
		{
			LogPrint(LOG_LEVEL_EMERG, LOG_MODLE_NAME, "the request message: %s is wrong", l_strType);
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("请求消息内容错误!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}
	catch (...)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "the request message parse: %s wrong", l_strType);
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("请求消息解析错误!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	
	switch (p_nJsonNum)
	{
	case JSON_DEVSTATIC:
		l_strModeName = "DevStaticInfo";
		break;
	case JSON_PROTOCOL:
		l_strModeName = "Message";
		break;
	case JSON_BASICINFO :
		l_strModeName = "BasicInfo";
		break;
	case JSON_V2XSERVICE :
		l_strModeName = "V2XService";
		break;
	case JSON_VDSMODULE:
		l_strModeName = "VDS";
		break;
	case JSON_MCUMODULE:
		l_strModeName = "MCU";
		break;
	case JSON_NETWORKMODULE:
		l_strModeName = "NetWork";
		break;	
	 case JSON_APPSET:
	 	l_strModeName = "AppSet";
	 	break;
	default:
		l_strModeName = "None";
	}
	if (!l_strOpt.compare("set"))
	{
		vector<string> l_vSection;
		if (!l_setType.empty())
			l_vSection.push_back(l_strType);
		l_jReqData["ConfigType"] = l_strType;
		l_jReqData["Operation"] = "set";
		l_jReqData["ModuleName"] = l_strModeName;
		ProcJsonDataSetting(p_pConn, p_nJsonNum, l_vSection, l_jReqData, p_pHttpServer);
	}
	else
	{
		vector<string> l_vSection;
		if (!l_setType.empty())
			l_vSection.push_back(l_strType);
		l_jResData["ConfigType"] = l_strType;
		l_jResData["ModuleName"] = l_strModeName;
		l_jResData["Operation"] = "query";
		l_jResData["message"] = sconv("查询参数成功");
		ProcJsonDataRequest(p_pConn, p_nJsonNum, l_vSection, l_jResData, p_pHttpServer);
	}
}



void GetProtocalAidList(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)
{
	json l_jResData, l_jTemp;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	HttpServer * l_pHttpServer = (HttpServer *)p_vData;
	string l_strOpt = GetHttpUrlParma(&l_pHttpMsg->body, "parentCode"), l_strData;
	l_strOpt = l_strOpt.empty() ? "MessageAIDGroup" : l_strOpt;
	std::vector<std::string> l_vName, l_vAID, l_vID, l_vDesc;
	if (!GetJsonDataFromFile(JSON_PROTOCOL, l_pHttpServer))
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("查询文件不存在!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	json &l_webData = ((HttpServer *)p_vData)->m_sJsonSet[JSON_PROTOCOL].data;
	l_jResData["result"] = "error";
	l_jResData["message"] = sconv("解析配置文件失败!");
	if (l_strOpt == "MessageAIDGroup")
	{
		try
		{
			if (l_webData.find("MessageAIDGroup") != l_webData.end())
			{
				l_strData = GetJsonStringData(l_webData["MessageAIDGroup"], "GroupName");
				l_vName = SplitString(l_strData, ",", 1);
				l_strData = GetJsonStringData(l_webData["MessageAIDGroup"], "GroupType");
				l_vID = SplitString(l_strData, ",", 1);
				l_strData = GetJsonStringData(l_webData["MessageAIDGroup"], "GroupDescrip");
				l_vDesc = SplitString(l_strData, ",", 1);
			}
			else
				return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
		catch (exception &e)
		{
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}
	else
	{
		try
		{
			auto index = l_strOpt.rfind("_");
			if (index == std::string::npos)
			{
				l_jResData["result"] = "error";
				l_jResData["message"] = sconv("组节点解析失败!");
				return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
			}
			string l_strItem = l_strOpt.substr(0, index);
			if (l_webData.find(l_strItem) != l_webData.end())
			{
				l_strData = GetJsonStringData(l_webData[l_strItem], "MsgName");
				l_vName = SplitString(l_strData, ",", 1);
				l_strData = GetJsonStringData(l_webData[l_strItem], "MsgID");
				l_vID = SplitString(l_strData, ",", 1);
				l_strData = GetJsonStringData(l_webData[l_strItem], "MsgDescrip");
				l_vDesc = SplitString(l_strData, ",", 1);
				l_strData = GetJsonStringData(l_webData[l_strItem], "MsgAID");
				l_vAID = SplitString(l_strData, ",", 1);
			}
			else
				return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
		catch (exception &e)
		{
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}
	unsigned int l_nCount = l_vName.size() < l_vID.size() ? l_vName.size() : l_vID.size();

	l_jResData["pageNo"] = 1;
	l_jResData["ModuleName"] = "Message";
	if (l_strOpt == "MessageAIDGroup")
	{
		l_jResData["pageSize"] = l_nCount;
		l_jTemp["treeLevel"] = 0;
		l_jTemp["isRoot"] = true;
		l_jTemp["parentCode"] = "0";
	}
	else
	{
		l_jTemp["treeLevel"] = 1;
		l_jResData["pageSize"] = -1;
		l_jTemp["isRoot"] = false;
		l_jTemp["parentCode"] = l_strOpt;
		l_jTemp["treeLeaf"] = "1";
		l_jTemp["isTreeLeaf"] = true;
	}
	vector<json> l_vDataList;

	for (unsigned int k = 0; k < l_nCount; k++)
	{
		l_jTemp["msg"] = (k < l_vDesc.size()) ? sconv(l_vDesc[k]) : "";
		l_jTemp["name"] = sconv(l_vName[k]);
		string l_strId = l_vName[k] + "_" + l_vID[k];
		l_jTemp["id"] = sconv(l_strId);
		l_jTemp["msgid"] = l_vID[k];
		l_jTemp["aid"] = (k < l_vAID.size()) ? l_vAID[k] : "0";
		l_jTemp["descrip"] = (k < l_vDesc.size()) ? sconv(l_vDesc[k]) : "";
		l_vDataList.push_back(l_jTemp);
	}
	if (l_nCount == 0)
	{
		l_jTemp["msg"] =  "New";
		l_jTemp["name"] =  "New";
		l_jTemp["id"] =  "New" + l_strOpt;
		l_jTemp["msgid"] =  -1;
		l_jTemp["aid"] =  0;
		l_jTemp["descrip"] = "New";
		l_vDataList.push_back(l_jTemp);
		l_nCount++;
	}
	l_jResData["list"] = l_vDataList;
	l_jResData["count"] = l_nCount;
	l_jResData["result"].clear();
	l_jResData["message"].clear();
	HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
}


void ProtocalAidEdit(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)
{
	json l_jResData, l_jTemp, l_jReqData, l_jSendData;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	HttpServer* l_pHttpServer = (HttpServer*)p_vData;
	string l_strMsgGroup, l_strMsgId, l_strMsgAId = "", l_strMsgName = "", l_strMsgDescrip ="";
	std::vector<std::string> l_vName, l_vAID, l_vID, l_vDesc;
	std::vector<int> l_vIntID;
	string l_strData = "";
	string l_strOpt = GetHttpUrlQuery(l_pHttpMsg, "act");
	if (l_strOpt != "modify" && l_strOpt != "delete")
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("请求参数解析异常!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	if (!GetJsonDataFromFile(JSON_PROTOCOL, l_pHttpServer))
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("查询文件不存在!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	json& l_webData = ((HttpServer*)p_vData)->m_sJsonSet[JSON_PROTOCOL].data;

	try
	{
		l_jReqData = json::parse(string(l_pHttpMsg->body.p, l_pHttpMsg->body.len));
		l_strMsgGroup = GetJsonStringData(l_jReqData, "MsgGroup");
		l_strMsgGroup = l_strMsgGroup.substr(0,l_strMsgGroup.length()-2);
		cout << "l_strMsgGroup: "<<l_strMsgGroup<<endl;
		l_strMsgId = GetJsonStringData(l_jReqData, "MsgID");
		l_strMsgName = GetJsonStringData(l_jReqData, "MsgName");
		l_strMsgDescrip = GetJsonStringData(l_jReqData, "MsgDescrip");
		if (l_strOpt == "modify")
		{
			l_strMsgAId = GetJsonStringData(l_jReqData, "MsgAID");
		}
	}
	catch (...)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("请求参数解析异常!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	if (l_strMsgGroup == "0")
	{
		try
		{
			if (l_webData.find("MessageAIDGroup") != l_webData.end())
			{
				l_strData = GetJsonStringData(l_webData["MessageAIDGroup"], "GroupName");
				l_vName = SplitString(l_strData, ",", 1);
				l_strData = GetJsonStringData(l_webData["MessageAIDGroup"], "GroupID");
				l_vID = SplitString(l_strData, ",", 1);
				l_strData = GetJsonStringData(l_webData["MessageAIDGroup"], "GroupDescrip");
				l_vDesc = SplitString(l_strData, ",", 1);

				if(l_strMsgId == "-1")
				{
					l_vIntID = VecStringToVecInt(l_vID);
					int i = l_vIntID.size();
					if(i > 0)
					{
						l_vIntID.push_back(l_vIntID[i-1]+1);
					}
					else
					{
						l_vIntID.push_back(1);
					}
					std::vector <std::string>().swap(l_vID);
					l_vID = VecIntToVecString(l_vIntID);

					l_vName.push_back(l_strMsgName);
					l_vDesc.push_back(l_strMsgDescrip);

					l_webData[l_strMsgName]["MsgName"] = "";
					l_webData[l_strMsgName]["MsgAID"] = "";
					l_webData[l_strMsgName]["MsgID"] = "";
					l_webData[l_strMsgName]["MsgDescrip"] = "";
				}
				else
				{	
					int l_itor = l_vID.size();
					for(int i = 0; i < l_itor; i++)
					{
						if(l_vID[i] == l_strMsgId)
						{
							if(l_strOpt == "delete")
							{
								l_vID.erase(l_vID.begin()+i);
								l_webData.erase(l_vName[i]);
							}
							
							l_vName.erase(l_vName.begin()+i);
							if(l_strOpt != "delete") l_vName.insert(l_vName.begin()+i, l_strMsgName);

							l_vDesc.erase(l_vDesc.begin()+i);
							if(l_strOpt != "delete") l_vDesc.insert(l_vDesc.begin()+i, l_strMsgDescrip);

							break;
						}
					}
				}
				l_strData = VectorToString(l_vID);
				l_webData["MessageAIDGroup"]["GroupID"] = l_strData;

				l_strData = VectorToString(l_vName);
				l_webData["MessageAIDGroup"]["GroupName"] = l_strData;

				l_strData = VectorToString(l_vDesc);
				l_webData["MessageAIDGroup"]["GroupDescrip"] = l_strData;

				//再次写入协议栈文件中
				cout << "add setdata:" << l_webData << endl;
    			//保存数据save
				if(!SetJsonDataToFile(JSON_PROTOCOL, l_webData, l_pHttpServer))
				{
					l_jResData["result"] = "error";
					l_jResData["message"] = sconv("参数设置失败!");
					return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
				}

				l_jResData["result"] = "success";
				l_jResData["message"] = sconv("参数设置成功!");
				return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
			}
			else
				return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
		catch (...)
		{
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}
	else
	{
		try
		{
			if (l_webData.find(l_strMsgGroup) != l_webData.end())
			{
				l_strData = GetJsonStringData(l_webData[l_strMsgGroup], "MsgName");
				l_vName = SplitString(l_strData, ",", 1);
				l_strData = GetJsonStringData(l_webData[l_strMsgGroup], "MsgID");
				l_vID = SplitString(l_strData, ",", 1);
				l_strData = GetJsonStringData(l_webData[l_strMsgGroup], "MsgDescrip");
				l_vDesc = SplitString(l_strData, ",", 1);
				l_strData = GetJsonStringData(l_webData[l_strMsgGroup], "MsgAID");
				l_vAID = SplitString(l_strData, ",", 1);

				if(l_strMsgId == "-1")
				{
					l_vIntID = VecStringToVecInt(l_vID);
					int i = l_vIntID.size();
					if(i > 0)
					{
						l_vIntID.push_back(l_vIntID[i-1]+1);
					}
					else
					{
						l_vIntID.push_back(1);
					}
					std::vector <std::string>().swap(l_vID);
					l_vID = VecIntToVecString(l_vIntID);

					l_vName.push_back(l_strMsgName);
					l_vDesc.push_back(l_strMsgDescrip);
					l_vAID.push_back(l_strMsgAId);
				}
				else
				{	
					int l_itor = l_vID.size();
					for(int i = 0; i < l_itor; i++)
					{
						if(l_vID[i] == l_strMsgId)
						{
							if(l_strOpt == "delete") l_vID.erase(l_vID.begin()+i);

							l_vName.erase(l_vName.begin()+i);
							if(l_strOpt != "delete") l_vName.insert(l_vName.begin()+i, l_strMsgName);

							l_vDesc.erase(l_vDesc.begin()+i);
							if(l_strOpt != "delete") l_vDesc.insert(l_vDesc.begin()+i, l_strMsgDescrip);

							l_vAID.erase(l_vAID.begin()+i);
							if(l_strOpt != "delete") l_vAID.insert(l_vAID.begin()+i, l_strMsgAId);

							break;
						}
					}
				}

				l_strData = VectorToString(l_vID);
				l_webData[l_strMsgGroup]["MsgID"] = l_strData;

				l_strData = VectorToString(l_vName);
				l_webData[l_strMsgGroup]["MsgName"] = l_strData;

				l_strData = VectorToString(l_vDesc);
				l_webData[l_strMsgGroup]["MsgDescrip"] = l_strData;

				l_strData = VectorToString(l_vAID);
				l_webData[l_strMsgGroup]["MsgAID"] = l_strData;

				//再次写入协议栈文件中
				cout << "add setdata:" << l_webData << endl;
    			//保存数据save
				if(!SetJsonDataToFile(JSON_PROTOCOL, l_webData, l_pHttpServer))
				{
					l_jResData["result"] = "error";
					l_jResData["message"] = sconv("参数设置失败!");
					return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
				}

				l_jResData["result"] = "success";
				l_jResData["message"] = sconv("参数设置成功!");
				return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
			}
			else
				return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
		catch (...)
		{
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}
		
	l_jResData["result"] = "error";
	l_jResData["message"] = sconv("参数操作失败!");
	return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
}




void AddDeviceSettingHandler(HttpServer* p_cHttpServer)
{
	p_cHttpServer->AddHttpRequestHandler("/setting/protocal/msgsend", 
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
		return DeviceParamSetting(p_pConn, p_pHttpMsg, JSON_PROTOCOL, CLIENT_MODULE, (HttpServer *)p_vData,
			{ "BSMSendConfig" , "RSISendConfig" , "MAPSendConfig" , "SPATSendConfig" , "RSMSendConfig" , "PassSendConfig"});
	}, 0, 0, "查询和设置消息发送参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/protocal/msgsecurity", 
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetting(p_pConn, p_pHttpMsg, JSON_PROTOCOL, CLIENT_MODULE, (HttpServer *)p_vData, {"SecurityParamConfig"});
	}, 0, 0, "查询和设置次消息安全层参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/protocal/dsmp", 
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetting(p_pConn, p_pHttpMsg, JSON_PROTOCOL, CLIENT_MODULE, (HttpServer *)p_vData, { "DSMPParamConfig" });
	}, 0, 0, "查询和设置DSMP参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/protocal/radio", 
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetting(p_pConn, p_pHttpMsg, JSON_PROTOCOL, CLIENT_MODULE, (HttpServer *)p_vData, {"RadioParamConfig"});
	}, 0, 0, "查询和设置射频参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/protocal/receive",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetting(p_pConn, p_pHttpMsg, JSON_PROTOCOL, CLIENT_MODULE, (HttpServer *)p_vData,{ "RecvParamConfig" });
	}, 0, 0, "查询和设置消息接收参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/module/msgversion",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetting(p_pConn, p_pHttpMsg, JSON_PROTOCOL, CLIENT_MODULE, (HttpServer *)p_vData,{ "MsgFrameConfig" });
	}, 0, 0, "查询和设置当前支持协议栈" });

	p_cHttpServer->AddHttpRequestHandler("/setting/module/app/algorithm",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetting(p_pConn, p_pHttpMsg, JSON_APPSET, CLIENT_MODULE, (HttpServer *)p_vData, {});
	}, 0, 0, "查询和设置算法参数" });


//以上都是原RSU设置无需修改

	p_cHttpServer->AddHttpRequestHandler("/setting/basic/basicinfo",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetToStruct(p_pConn, p_pHttpMsg, JSON_BASICINFO, CLIENT_MODULE, (HttpServer *)p_vData);
		}, 0, 0, "查询和设置设备的基本参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/protocal/v2xservice",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetToStruct(p_pConn, p_pHttpMsg, JSON_V2XSERVICE, CLIENT_MODULE, (HttpServer *)p_vData);
		}, 0, 0, "查询和设置V2X服务参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/protocal/moduleconfig",
	{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
		return DeviceParamSetToStruct(p_pConn, p_pHttpMsg, JSON_MODULECONFIG, CLIENT_MODULE, (HttpServer *)p_vData);
	}, 0, 0, "查询和设置模组配置参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/module/vds",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetToStruct(p_pConn, p_pHttpMsg, JSON_VDSMODULE, CLIENT_MODULE, (HttpServer *)p_vData);
		}, 0, 0, "查询和设置VDS模块参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/module/mcu",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetToStruct(p_pConn, p_pHttpMsg, JSON_MCUMODULE, CLIENT_MODULE, (HttpServer *)p_vData);
		}, 0, 0, "查询和设置MCU模块参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/module/network",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetToStruct(p_pConn, p_pHttpMsg, JSON_NETWORKMODULE, CLIENT_MODULE, (HttpServer *)p_vData);
		}, 0, 0, "查询和设置NetWork模块参数" });

/*
	p_cHttpServer->AddHttpRequestHandler("/setting/module/app/activesafety",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetToStruct(p_pConn, p_pHttpMsg, JSON_APPASCFG, CLIENT_MODULE, (HttpServer *)p_vData);
		}, 0, 0, "查询和设置AppASCfg模块参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/module/app/mapmatch",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetToStruct(p_pConn, p_pHttpMsg, JSON_APPMMCFG, CLIENT_MODULE, (HttpServer *)p_vData);
		}, 0, 0, "查询和设置AppMMCfg模块参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/module/app/maintaininfo",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetToStruct(p_pConn, p_pHttpMsg, JSON_APPMTCFG, CLIENT_MODULE, (HttpServer *)p_vData);
		}, 0, 0, "查询和设置AppMTCfg模块参数" });

	p_cHttpServer->AddHttpRequestHandler("/setting/module/app/gwspeedguide",
		{[](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData) -> void {
			return DeviceParamSetToStruct(p_pConn, p_pHttpMsg, JSON_APPTLCFG, CLIENT_MODULE, (HttpServer *)p_vData);
		}, 0, 0, "查询和设置AppTLCfg模块参数" });
*/
	p_cHttpServer->AddHttpRequestHandler("/setting/protocal/aidlist", { GetProtocalAidList,0,0,"获取AID消息列表" });
	p_cHttpServer->AddHttpRequestHandler("/setting/protocal/aid", { ProtocalAidEdit,0,0,"修改消息层AID" });
}
