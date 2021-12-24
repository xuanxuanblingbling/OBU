#include "../web_service/http_handler.h"

using namespace std;

struct mg_str mg_create_str(string str)
{
	struct mg_str ret;
	ret.len = str.length();
	ret.p = NULL;
	if (ret.len > 0)
	{
		ret.p = (char*)malloc(ret.len);
		memcpy((char*)ret.p, str.c_str(), ret.len);
	}
	return ret;
}


struct upload_file {
	struct mg_str m_filename;
	struct mg_str m_pathname;
	HttpRequestHandler m_Handler;  // 成功传输数据之后执行的函数
};

// 获取文件名字
struct mg_str GetUploadFileName(struct mg_connection* p_pConn, struct mg_str fname)
{
	struct upload_file* path = (struct upload_file*)p_pConn->user_data;
	string l_strPname;
	string l_strFname = GetFileName(string(fname.p, fname.len));
	if (l_strFname.empty())
		return fname;

	if (path == NULL)
		return mg_create_str(l_strFname);

	path->m_filename.len = l_strFname.length();           // save filename
	path->m_filename.p = (char*)malloc(l_strFname.length());
	memcpy((char*)path->m_filename.p, l_strFname.c_str(), l_strFname.length());

	l_strPname = string(path->m_pathname.p, path->m_pathname.len);
	l_strPname.append(l_strFname);
	printf("====[test] filename %s ====\n",l_strPname.c_str());
	return mg_create_str(l_strPname);
}


void FileUploadProcess(struct upload_file p_cUpFile, struct mg_connection* p_pConn, int p_sEventStatus, void* p_pEventData, void* p_pHttpServer)
{
	struct upload_file* data = (struct upload_file*) p_pConn->user_data;
	switch (p_sEventStatus)
	{
	case MG_EV_HTTP_MULTIPART_REQUEST:  // 处理文件传输的函数
		if (!p_cUpFile.m_pathname.len)
		{
			p_pConn->flags |= MG_F_CLOSE_IMMEDIATELY;
			return;
		}
		data = (upload_file*)calloc(1, sizeof(struct upload_file));
		*data = p_cUpFile;
		p_pConn->user_data = data;
		break;

	case MG_EV_HTTP_PART_BEGIN:
	case MG_EV_HTTP_PART_DATA:
	case MG_EV_HTTP_PART_END:
	case MG_EV_HTTP_MULTIPART_REQUEST_END:
		mg_file_upload_handler(p_pConn, p_sEventStatus, p_pEventData, GetUploadFileName, NULL);
		if (p_sEventStatus == MG_EV_HTTP_MULTIPART_REQUEST_END)
		{
			json l_jResData;
			l_jResData["result"] = "success";
			l_jResData["message"] = sconv("上传文件出错!");
			if (data == NULL)
			{
				printf("====[test] uploadfile error ====\n");
				return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
			}
				
			if (data->m_Handler != NULL)
				data->m_Handler(p_pConn, p_sEventStatus, p_pEventData, p_pHttpServer);
		}


		if ((p_pConn->flags & (MG_F_SEND_AND_CLOSE | MG_F_CLOSE_IMMEDIATELY)) && (data != NULL))
		{
			if (p_sEventStatus == MG_EV_HTTP_PART_END)  // Transfer Error
			{
#ifdef _WIN32
				string l_strCmd = "del /F " + string(data->m_pathname.p, data->m_pathname.len) + string(data->m_filename.p, data->m_filename.len);
#else
				string l_strCmd = "rm -f " + string(data->m_pathname.p, data->m_pathname.len) + string(data->m_filename.p, data->m_filename.len);
#endif          
                printf("====[test] shell %s ====\n",l_strCmd.c_str());
				system(l_strCmd.c_str());  // 创建文件夹
			}
			mg_strfree(&(data->m_filename));
			mg_strfree(&(data->m_pathname));
			p_pConn->user_data = NULL;
		}
		break;
	}
}


void FileUploadHandler(struct mg_connection* p_pConn, int p_sEventStatus, void* p_pEventData, void* p_pHttpServer)
{
	string l_strURI, l_strPath = "";
	struct upload_file l_sUpFile;
	struct http_message* l_pHttpMsg = (struct http_message*) p_pEventData;
	HttpServer * l_pHttpServer = (HttpServer *)p_pHttpServer;
	URI_Handler l_pRequstHandler;
	string l_strUpdatePath;
	if (p_sEventStatus == MG_EV_HTTP_MULTIPART_REQUEST) // read URI and Handler
	{
		l_strURI = MakeURINorm(GetHttpUrlQuery(l_pHttpMsg, "uri"));
		l_strPath = l_pHttpServer->GetUploadPath(l_strURI);
		l_strUpdatePath = l_pHttpServer->m_cWebConfig->m_strAppUpdatePath;
		l_strUpdatePath = sconv(l_strUpdatePath);
		l_strUpdatePath = MakeURINorm(l_strUpdatePath);

		printf("====[test]  path %s  Updpath %s  URI %s ====\n",l_strPath.c_str(),l_strUpdatePath.c_str(),l_strURI.c_str());

		if (l_strPath.empty())
		{
			p_pConn->flags |= MG_F_CLOSE_IMMEDIATELY;
			return;
		}
#ifdef  _WIN32
		string l_strCmd = "mkdir " + l_strPath;
#else
		string l_strCmd = "mkdir -p " + l_strPath;
#endif
		system(l_strCmd.c_str());  // 创建文件夹
		if (FILEACCESS(l_strPath.c_str(), 0) < 0)
		{
			p_pConn->flags |= MG_F_CLOSE_IMMEDIATELY;
			return;
		}

		if (l_strPath.empty() || FILEACCESS(l_strPath.c_str(), 0) < 0)
		{
			p_pConn->flags |= MG_F_CLOSE_IMMEDIATELY;
			return;
		}

#ifdef  _WIN32
		string l_strEmptyCmd = "rm -rf " + l_strUpdatePath + '*';
#else
		string l_strEmptyCmd = "rm -rf " + l_strUpdatePath + '*';
#endif		
		system(l_strEmptyCmd.c_str()); //清空文件夹
			
		l_pRequstHandler = l_pHttpServer->GetHttpRequestHandler(l_strURI);
		if (!l_pRequstHandler.m_Hanlder)
			l_pRequstHandler .m_Hanlder= NULL;

		l_sUpFile.m_pathname.len = l_strPath.length();
		l_sUpFile.m_pathname.p = (char*)malloc(l_strPath.length());
		l_sUpFile.m_Handler = l_pRequstHandler.m_Hanlder;
		memcpy((char*)l_sUpFile.m_pathname.p, l_strPath.c_str(), l_strPath.length());
	}
	FileUploadProcess(l_sUpFile, p_pConn, p_sEventStatus, p_pEventData, p_pHttpServer);
}



