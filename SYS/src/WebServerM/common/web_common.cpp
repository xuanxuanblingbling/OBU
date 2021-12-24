#include "web_common.h"
#include "../extern/mongoose/mongoose.h"
#include <map>
#include "string_conv.h"

static map<string, string> g_mapMimeTypes = {
	{ "html", "text/html" },
	{ "html", "text/html" },
	{ "htm", "text/html" },
	{ "shtm", "text/html" },
	{ "shtml", "text/html" },
	{ "css", "text/css" },
	{ "js", "application/x-javascript" },
	{ "ico", "image/x-icon" },
	{ "gif", "image/gif" },
	{ "jpg", "image/jpeg" },
	{ "jpeg", "image/jpeg" },
	{ "png", "image/png" },
	{ "svg", "image/svg+xml" },
	{ "txt", "text/plain" },
	{ "torrent", "application/x-bittorrent" },
	{ "wav", "audio/x-wav" },
	{ "mp3", "audio/x-mp3" },
	{ "mid", "audio/mid" },
	{ "m3u", "audio/x-mpegurl" },
	{ "ogg", "application/ogg" },
	{ "ram", "audio/x-pn-realaudio" },
	{ "xml", "text/xml" },
	{ "ttf", "application/x-font-ttf" },
	{ "json", "application/json" },
	{ "xslt", "application/xml" },
	{ "xsl", "application/xml" },
	{ "ra", "audio/x-pn-realaudio" },
	{ "doc", "application/msword" },
	{ "exe", "application/octet-stream" },
	{ "zip", "application/x-zip-compressed" },
	{ "xls", "application/excel" },
	{ "tgz", "application/x-tar-gz" },
	{ "tar", "application/x-tar" },
	{ "gz", "application/x-gunzip" },
	{ "arj", "application/x-arj-compressed" },
	{ "rar", "application/x-rar-compressed" },
	{ "rtf", "application/rtf" },
	{ "pdf", "application/pdf" },
	{ "swf", "application/x-shockwave-flash" },
	{ "mpg", "video/mpeg" },
	{ "webm", "video/webm" },
	{ "mpeg", "video/mpeg" },
	{ "mov", "video/quicktime" },
	{ "mp4", "video/mp4" },
	{ "m4v", "video/x-m4v" },
	{ "asf", "video/x-ms-asf" },
	{ "avi", "video/x-msvideo" },
	{ "bmp", "image/bmp" }};


string GetMimeType(const string &p_strType)
{
	auto l_aItra = g_mapMimeTypes.find(p_strType);
	if (l_aItra != g_mapMimeTypes.end())
		return l_aItra->second;
	return p_strType;
}

string GetFirstURI(const string &p_strURI, int p_sOff, int *p_sPos)
{
	*p_sPos = -1;
	int l_uPos, l_uLen = p_strURI.length();
	if (p_sOff >= l_uLen || p_strURI[p_sOff] == '/')
		return "";
	l_uPos = p_strURI.find('/', p_sOff);
	if (l_uPos == -1)
		return p_strURI.substr(p_sOff, l_uLen - p_sOff);

	*p_sPos = l_uPos;
	return p_strURI.substr(p_sOff, l_uPos - p_sOff);
}


string MakeURINorm(const string &p_strURI)
{
	string l_strURI = "/";
	int l_flag = 1, l_sLen = p_strURI.length(), k1 = 0;
	for (int k = 0; k < l_sLen; k++)
	{
		if (p_strURI[k] == '/')
		{
			if (!l_flag)
				l_strURI.append(p_strURI.substr(k1, k - k1 + 1));
			l_flag = 1;
		}
		else
		{
			if (l_flag)
				k1 = k;
			l_flag = 0;
		}
	}
	if (l_flag == 0)
	{
		l_strURI.append(p_strURI.substr(k1, p_strURI.length() - 1));
		l_strURI.append("/");
	}
	return l_strURI;
}

void SplitURI(const string &p_strURI, string *p_strSplit, int p_num)
{
	string l_strURI;
	int l_uPos = 1, k = -1, l_uPos1, l_uLen;
	l_strURI = MakeURINorm(p_strURI);
	if (!l_strURI.compare("/"))
		return;

	l_uLen = l_strURI.length();
	while ((++k) < p_num)
	{
		p_strSplit[k] = GetFirstURI(l_strURI, l_uPos, &l_uPos1);
		if (l_uPos1 == l_uLen - 1) // 匹配上最后
		{
			k++;
			l_uPos = l_uPos1 + 1;
			break;
		}
		l_uPos = l_uPos1 + 1;
	}
	if (l_uPos < l_uLen - 1)
	{
		p_strSplit[k] = p_strURI.substr(l_uPos, l_uLen - 2);
		p_strSplit[k + 1] = "";
	}
	else
		p_strSplit[k] = "";
}


string GetHttpHeader(struct http_message *p_pHttpMsg,const string &p_strHeaderName)
{
	struct mg_str *l_mgHeader = mg_get_http_header(p_pHttpMsg, p_strHeaderName.c_str());
	if (l_mgHeader == NULL) return "";
	return string(l_mgHeader->p, l_mgHeader->len);
}


string GetFileName(const string &p_strPathFileName)
{
	int l_nPos = 0, l_nPos1 = 0, l_nLen = p_strPathFileName.length();
	if (p_strPathFileName.empty() || p_strPathFileName[l_nLen - 1] == '/' 
		|| p_strPathFileName[l_nLen - 1] == '\\')
		return "";

	while (1)
	{
		l_nPos1 = p_strPathFileName.find('\\', l_nPos);
		if(l_nPos1 < 0)
			l_nPos1 = p_strPathFileName.find('/', l_nPos);
		if (l_nPos1 < 0)
			break;
		l_nPos = l_nPos1 + 1;
	}
	return p_strPathFileName.substr(l_nPos, l_nLen - l_nPos);
}


string GetHttpVar(const struct mg_str *buf, string name)
{
	char l_cTemp[512];
	int l_sLen = mg_get_http_var(buf, name.c_str(), l_cTemp, sizeof(l_cTemp));
	if (l_sLen <= 0)
		return "";
	return string(l_cTemp, l_sLen);
}

unsigned char ToHex(unsigned char x)
{
	return  x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex(unsigned char x)
{
	unsigned char y;
	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
	else if (x >= '0' && x <= '9') y = x - '0';
	else assert(0);
	return y;
}


std::string UrlEncode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum((unsigned char)str[i]) ||
			(str[i] == '-') ||
			(str[i] == '_') ||
			(str[i] == '.') ||
			(str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ')
			strTemp += "+";
		else
		{
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] % 16);
		}
	}
	return strTemp;
}

std::string UrlDecode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] == '+') strTemp += ' ';
		else if (str[i] == '%')
		{
			assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char)str[++i]);
			unsigned char low = FromHex((unsigned char)str[++i]);
			strTemp += high * 16 + low;
		}
		else strTemp += str[i];
	}
	return strTemp;
}


std::string CharToHex(unsigned char ch)
{
	const std::string hex = "0123456789ABCDEF";
	std::stringstream ss;
	ss << hex[ch >> 4] << hex[ch & 0xf];
	return ss.str();
}

std::string StringToHex(std::string &str, std::string separator = "")
{
	const std::string hex = "0123456789abcdef";
	std::stringstream ss;
	for (std::string::size_type i = 0; i < str.size(); ++i)
		ss << hex[(unsigned char)str[i] >> 4] << hex[(unsigned char)str[i] & 0xf] << separator;
	return ss.str();
}

std::string HexToString(std::string &str)
{
	std::string l_str;
	if (str.empty())
		return "";

	if ((str.length() % 2))
		return "";

	for (unsigned int k = 0; k < (str.length() >> 1); ++k)
	{
		char l_c1 = str[k << 1];
		char l_c2 = str[(k << 1) + 1];
		if (l_c1 >= '0'&& l_c1 <= '9')
			l_c1 = l_c1 - '0';
		else if (l_c1 >= 'A'&& l_c1 <= 'F')
			l_c1 = l_c1 - 'A' + 10;
		else if (l_c1 >= 'a'&& l_c1 <= 'f')
			l_c1 = l_c1 - 'a' + 10;
		else
			return "";

		if (l_c2 >= '0'&& l_c2 <= '9')
			l_c2 = l_c2 - '0';
		else if (l_c2 >= 'A' && l_c2 <= 'F')
			l_c2 = l_c2 - 'A' + 10;
		else if (l_c2 >= 'a' && l_c2 <= 'f')
			l_c2 = l_c2 - 'a' + 10;
		else
			return "";

		l_str.push_back((char)((l_c1 << 4) | l_c2));
	}
	return l_str;
}



// 获取请求的SessionId
string GetRequestSessionId(http_message *p_pHttpMsg)
{
	int l_sLen;
	char l_cSession[36];
	string l_strSession;
	l_sLen = mg_get_http_var(&p_pHttpMsg->query_string, "SessionId", l_cSession, sizeof(l_cSession));
	if (l_sLen < 0)
		l_strSession = GetHttpHeader(p_pHttpMsg, "SessionId");
	else
		l_strSession = string(l_cSession, l_sLen);
	return l_strSession;
}


string GetHttpUrlQuery(http_message *p_pHttpMsg,const string &p_strName)
{
	return GetHttpUrlParma(&(p_pHttpMsg->query_string), p_strName);
}

string GetHttpUrlParma(const struct mg_str *l_strBuf,const string &p_strName)
{
	string l_strRet;
	int l_sLen;
	if (l_strBuf->len == 0)
		return "";
	char *l_cQuery = new char[l_strBuf->len];
	l_sLen = mg_get_http_var(l_strBuf, p_strName.c_str(), l_cQuery, l_strBuf->len);
	if (l_sLen <= 0)
	{
		delete l_cQuery;
		return "";
	}
	else
	{
		l_strRet = invs(string(l_cQuery, l_sLen));
		delete l_cQuery;
		return l_strRet;
	}
}


string GetRemoteIpAddress(struct mg_connection *p_pConn)
{
	char l_cAddr[32];
	int l_sLen = mg_conn_addr_to_str(p_pConn, l_cAddr, sizeof(l_cAddr), MG_SOCK_STRINGIFY_REMOTE | MG_SOCK_STRINGIFY_IP);
	if (!l_sLen)// 获取IP地址
		return "";
	return string(l_cAddr, l_sLen);
}


void HttpSendResponse(struct mg_connection *p_pConn, int p_sStatusCode,const string &p_strType,const string &p_strContent, string p_strHeader = "")
{
	if (!p_strType.empty())
		p_strHeader += "Content-Type: " + GetMimeType(p_strType);
	mg_send_head(p_pConn, p_sStatusCode, p_strContent.length(), p_strHeader.c_str());
	mg_send(p_pConn, p_strContent.c_str(), p_strContent.length());
}


void HttpSendError(struct mg_connection *p_pConn, int p_sStatusCode,const string &p_strReason)
{
	mg_http_send_error(p_pConn, p_sStatusCode, p_strReason.c_str());
}


void HttpSendRedirect(struct mg_connection *p_pConn, int p_sStatusCode,const string &p_strLocation,const string &p_strHeader)
{
	mg_str l_mgLoc, l_mgHeader;
	l_mgLoc.p = p_strLocation.c_str();
	l_mgLoc.len = p_strLocation.length();
	l_mgHeader.p = p_strHeader.c_str();
	l_mgHeader.len = p_strHeader.length();
	mg_http_send_redirect(p_pConn, p_sStatusCode, l_mgLoc, l_mgHeader);
}


void GetPageStartEnd(http_message *p_pHttpMsg, unsigned int &p_nStart, unsigned int &p_nEnd, unsigned int &p_nPageNo, 
	unsigned int &p_nPageSize,unsigned int p_nTotal, unsigned int p_nDefaultSize)
{
	try
	{
		p_nPageNo = stoi(GetHttpUrlParma(&p_pHttpMsg->body, "pageNo"));
		p_nPageSize = stoi(GetHttpUrlParma(&p_pHttpMsg->body, "pageSize"));
	}
	catch (...)
	{
		p_nPageNo = 1;
		p_nPageSize = p_nDefaultSize;
	}
	p_nStart = (p_nPageNo - 1) * p_nPageSize;

	if (p_nStart >= p_nTotal)
		p_nPageNo = 1;

	p_nStart = (p_nPageNo - 1) * p_nPageSize;
	p_nEnd = p_nStart + p_nPageSize;
	p_nEnd = (p_nEnd > p_nTotal) ? p_nTotal : p_nEnd;
}


//指定time_t类型的时间，格式化为YYYYMMDDHH24MISS型的字符串  
string FormatTime(time_t time1)
{
	char l_cTime[32];
	struct tm tm1;
#ifdef WIN32  
	tm1 = *localtime(&time1);
#else  
	localtime_r(&time1, &tm1);
#endif  
	sprintf(l_cTime, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d",
		tm1.tm_year + 1900, tm1.tm_mon + 1, tm1.tm_mday,
		tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
	return string(l_cTime, strlen(l_cTime));
}


string AesEncryptCBC(string &p_strContent, string p_strKey)
{
	unsigned int l_enLen;
	AES t_Aes(128);
	if (p_strContent.empty())
		return "";
	if (p_strKey.length() != 32)
		return "";
	string key = p_strKey.substr(0, 16);
	string iv = p_strKey.substr(16, 16);
	unsigned char *Encrypt = t_Aes.EncryptCBC((unsigned char *)p_strContent.c_str(), p_strContent.length(), 
		(unsigned char *)key.c_str(), (unsigned char *)iv.c_str(), l_enLen);
	string l_strRet = string((char *)Encrypt, l_enLen);
	delete Encrypt;
	return StringToHex(l_strRet, "");
}

string AesDecryptCBC(string &p_strContent, string p_strKey)
{
	AES t_Aes(128);
	if (p_strKey.length() != 32)
		return "";
	string l_deStr = HexToString(p_strContent);
	if (l_deStr.empty())
		return "";
	string key = p_strKey.substr(0, 16);
	string iv = p_strKey.substr(16, 16);
	unsigned char *l_Decry = t_Aes.DecryptCBC((unsigned char *)l_deStr.c_str(), l_deStr.length(),
		(unsigned char *)key.c_str(), (unsigned char *)iv.c_str());
	string l_strRet = string((char *)l_Decry);
	cout << p_strContent << endl;
	cout << p_strKey << endl;
	cout << l_strRet << endl;
	delete l_Decry;
	return l_strRet;
}
