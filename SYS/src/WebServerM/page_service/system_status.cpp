#include "../web_service/http_handler.h"

void AddSystemStatusHandler(HttpServer *p_pHttpServer)
{
	p_pHttpServer->AddHttpRequestHandler("/system/status/static", 
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)->void {
			json l_jData;
			vector<string> l_vSection;
			ProcDataRequestStatic(p_pConn, JSON_DEVSTATIC, l_vSection, l_jData, (HttpServer*)p_vData);
		},0,0,"查询系统静态信息" });
	p_pHttpServer->AddHttpRequestHandler("/system/status/dynamic", 
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)->void {
			json l_jData;
			vector<string> l_vSection;
			ProcJsonDataRequest(p_pConn, JSON_DEVDYNAMIC, l_vSection, l_jData, (HttpServer*)p_vData);
		},0,0,"查询系统的动态信息" });
	p_pHttpServer->AddHttpRequestHandler("/system/status/fault",
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)->void {
			json l_jData;
			vector<string> l_vSection;
			ProcJsonDataRequest(p_pConn, JSON_DEVFAULT, l_vSection, l_jData, (HttpServer*)p_vData);
		},0,0,"查询系统的故障信息" });

	p_pHttpServer->AddHttpRequestHandler("/system/status/msgmonitor",
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)->void {
			json l_jData;
			vector<string> l_vSection;
			MonitorProcJsonDataRequest(p_pConn, p_pHttpMsg, JSON_MSGMONITOR, l_vSection, l_jData, (HttpServer*)p_vData);
		},0,0,"查询总线数据监控信息" });

	p_pHttpServer->AddHttpRequestHandler("/system/status/version", 
		{ [](struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void* p_vData)->void {
			json p_jData;
			struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
			string l_strModuleName = GetHttpUrlQuery(l_pHttpMsg,"module"), l_strVersion;
			printf("====[test] modulename %s =====\n",l_strModuleName.c_str());
			p_jData["result"] = "error";
			p_jData["message"] = sconv("查询版本号失败!");
			if (l_strModuleName.empty())
				return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
			if (!GetJsonDataFromFile(JSON_DEVSTATIC, (HttpServer*)p_vData))
				return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");

			json& l_webData = ((HttpServer*)p_vData)->m_sJsonSet[JSON_DEVSTATIC].data;
			printf("====[test] webdata %s =====\n",l_webData.dump().c_str());
			if (l_webData.find("OBUInfo") == l_webData.end())
				return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");

			try
			{
				l_strVersion = GetJsonStringData(l_webData["OBUInfo"], l_strModuleName);
			}
			catch (...)
			{
				return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
			}
			p_jData["result"] = "success";
			p_jData["message"] = sconv("查询版本号成功!");
			p_jData[l_strModuleName] = sconv(l_strVersion);
			return HttpSendResponse(p_pConn, 200, "json", p_jData.dump(), "");
		},0,0xFFFFFFFF,"查询系统的版本号" });
}


