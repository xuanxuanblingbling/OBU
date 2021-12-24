#pragma once

#include <assert.h>  
#include <iostream>
#include <sstream>
#include "../extern/crypto/aes.h"

using namespace std;

string GetMimeType(const string &p_strType);

/* 返回字符串中的内容URI  */
string GetFirstURI(const string &p_strURI, int p_sOff, int *p_sPos);

/* 总是把地址规范为 /type/class/item/...的形式 */
string MakeURINorm(const string &p_strURI);

/* 将URI中的内容进行分割，存放在数组中 */
void SplitURI(const string &p_strURI, string *p_strSplit, int p_num);

// 获取HTTP header 中的内容
string GetHttpHeader(struct http_message *p_pHttpMsg,const string &p_strHeaderName);

string GetFileName(const string &p_strPathFileName);

unsigned char ToHex(unsigned char x);

unsigned char FromHex(unsigned char x);

std::string UrlEncode(const std::string& str);

std::string UrlDecode(const std::string& str);

std::string CharToHex(unsigned char ch);

std::string StringToHex(std::string &str, std::string separator);

std::string HexToString(std::string &str);

string GetHttpVar(const struct mg_str *buf, string name);

void HttpSendResponse(struct mg_connection *p_pConn, int p_sStatusCode,const string &p_strType,const string &p_strContent, string p_strHeader);

void HttpSendError(struct mg_connection *p_pConn, int p_sStatusCode,const string &p_strReason);

void HttpSendRedirect(struct mg_connection *p_pConn, int p_sStatusCode,const string &p_strLocation, const string &p_strHeader);

void GetPageStartEnd(http_message *p_pHttpMsg, unsigned int &p_nStart, unsigned int &p_nEnd, unsigned int &p_nPageNo,
	unsigned int &p_nPageSize, unsigned int p_nTotal, unsigned int p_nDefaultSize);

string GetRequestSessionId(http_message *p_pHttpMsg);

string GetHttpUrlQuery(http_message *p_pHttpMsg,const string &p_strName);

string GetHttpUrlParma(const struct mg_str *l_strBuf,const string &p_strName);

string GetRemoteIpAddress(struct mg_connection *p_pConn);

string FormatTime(time_t time1);

string AesEncryptCBC(string &p_strContent, string p_strKey);

string AesDecryptCBC(string &p_strContent, string p_strKey);