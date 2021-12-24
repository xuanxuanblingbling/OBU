#include "../web_service/http_handler.h"

void DataDemoRead(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	json l_jResData, l_tData;
	int l_eCode = 200;
	std::fstream  afile;
	std::ostringstream tmpdata;
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	std::string l_strFname = GetHttpUrlQuery(l_pHttpMsg, "fname");
	l_jResData["result"] = "error";
	if (l_strFname.empty())
	{
		l_jResData["message"] = sconv("文件名为空!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	afile.open(l_strFname, std::ios::app | std::ios::in);
	if (!afile)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("打开文件失败!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	try
	{
		tmpdata << afile.rdbuf();
		l_tData = json::parse(tmpdata.str());
		l_eCode = stoi(l_tData["code"].get<string>());
		return HttpSendResponse(p_pConn, l_eCode, "json", l_tData.dump(), "");
	}
	catch (...)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("解析文件数据失败!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
}


void DataDemoWrite(struct mg_connection* p_pConn, int p_nEvent, void* p_pHttpMsg, void *p_vData)
{
	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	json l_jResData;
	std::fstream  afile;
	std::string l_strFname = GetHttpUrlQuery(l_pHttpMsg, "fname");
	l_jResData["result"] = "error";
	if (l_strFname.empty())
	{
		l_jResData["message"] = sconv("文件名为空!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	
	afile.open(l_strFname, std::ios::app | std::ios::out);
	if (!afile)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("打开文件失败!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	try
	{
		afile.write(l_pHttpMsg->body.p, l_pHttpMsg->body.len);
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("写入文件成功!");
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
	}
	catch (...)
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("写入文件数据失败!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
}


void DataDemoHandler(HttpServer *p_cHttpServer)
{
	p_cHttpServer->AddHttpRequestHandler("/demo/data/read/", { DataDemoRead,0,0,"读取测试数据" });
	p_cHttpServer->AddHttpRequestHandler("/demo/data/write/", { DataDemoWrite,0,0,"写入测试数据" });
}