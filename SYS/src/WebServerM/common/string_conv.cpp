#include "string_conv.h"
//#include <locale>

std::string strinvs(const std::string &s)
{
	return ws2sinv(s2wsinv(s));
}


std::string strconv(const std::string &s)
{
	return ws2s(s2ws(s));
}

std::vector<std::string> strinvs(std::vector<std::string> s)
{
	std::vector<std::string> l_strRet;
	for (auto &l_strData : s)
		l_strRet.push_back(ws2sinv(s2wsinv(l_strData)));
	return l_strRet;
}

std::vector<std::string> strconv(std::vector<std::string> s)
{
	std::vector<std::string> l_strRet;
	for (auto &l_strData : s)
		l_strRet.push_back(ws2s(s2ws(l_strData)));
	return l_strRet;
}


std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, "en_US.UTF-8");
	return result;
}

std::string ws2s(const std::wstring& w_str) {
	if (w_str.empty()) {
		return "";
	}
	unsigned len = w_str.size() * 4 + 1;
	setlocale(LC_CTYPE, "en_US.UTF-8");
	std::unique_ptr<char[]> p(new char[len]);
	wcstombs(p.get(), w_str.c_str(), len);
	std::string str(p.get());
	return str;
}

std::wstring s2wsinv(const std::string& s)
{
	setlocale(LC_ALL, "en_US.UTF-8");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	return result;
}

std::string ws2sinv(const std::wstring& w_str) 
{
	if (w_str.empty()) {
		return "";
	}
	unsigned len = w_str.size() * 4 + 1;
	setlocale(LC_CTYPE, "chs");
	std::unique_ptr<char[]> p(new char[len]);
	wcstombs(p.get(), w_str.c_str(), len);
	std::string str(p.get());
	return str;
}


std::string subreplace(std::string resource_str,const std::string &sub_str,const std::string &new_str)
{
	std::string::size_type pos = 0;
	while ((pos = resource_str.find(sub_str)) != std::string::npos)   
	{
		resource_str.replace(pos, sub_str.length(), new_str);
	}
	return resource_str;
}



std::string VecCharToString(const std::vector<char> &p_vChar)
{
	std::string l_strTemp = "";
	for (int k = 0; k < p_vChar.size(); ++k)
		l_strTemp.push_back(p_vChar[k]);
	return l_strTemp;
}

std::vector<char> StringToVecChar(const std::string &p_strData)
{
	std::vector<char> l_vChar;
	for (int k = 0; k < p_strData.size(); ++k)
		l_vChar.push_back(p_strData[k]);
	return l_vChar;
}


//vector 转换成字符串，中间用逗号分割，没有空格

std::string VectorToString(std::vector<std::string> &p_vStrList)
{
    std::string retString = "";

	int l_itor = p_vStrList.size();
	if(l_itor <= 0)
	{
		return retString;
	}
	else
	{
		for(int i = 0; i < l_itor; i++)
		{
			retString +=p_vStrList[i];
			if(i + 1 != l_itor)
			{
				retString += ",";
			}
		}
		return retString;
	}
}


std::vector<std::string> VecIntToVecString(std::vector<int> &p_vIntList)
{
	std::vector<std::string> l_vRet;
	int l_itor = p_vIntList.size();
	if(l_itor <= 0)
	{
		return l_vRet;
	}
	else
	{
		for(int i = 0; i < l_itor; i++)
		{
			l_vRet.push_back(std::to_string(p_vIntList[i]));
		}
		return l_vRet;
	}
}


std::vector<int> VecStringToVecInt(std::vector<std::string> &p_vStrList)
{
	std::vector<int> l_vRet;
	int l_itor = p_vStrList.size();
	if(l_itor <= 0)
	{
		return l_vRet;
	}
	else
	{
		for(int i = 0; i < l_itor; i++)
		{
			l_vRet.push_back(stoi(p_vStrList[i]));
		}
		return l_vRet;
	}
}


std::vector<std::string> SplitString(std::string &p_strData, std::string p_cSplit, int p_nDeleteBlank)
{
	std::vector<std::string> l_vRet;
	int l_nStart = 0;
	if (p_strData.empty())
		return l_vRet;

	while(1)
	{
		int l_nEnd = p_strData.find(p_cSplit, l_nStart);
		std::string l_strTemp;
		if (l_nEnd > l_nStart)
			l_strTemp = p_strData.substr(l_nStart, l_nEnd - l_nStart);
		else
		{
			l_nEnd = p_strData.size();
			l_strTemp = p_strData.substr(l_nStart, p_strData.size() - l_nStart);
		}


		if (p_nDeleteBlank)  // 删除多余空格
		{
			int l_nS = l_strTemp.find_first_not_of(" ");
			int l_nE = l_strTemp.find_last_not_of(" ");
			if (l_nE == std::string::npos || l_nS == std::string::npos)
				l_vRet.push_back("");
			else
				l_vRet.push_back(l_strTemp.substr(l_nS, l_nE - l_nS + 1));
		}
		else
			l_vRet.push_back(l_strTemp);
		l_nStart = l_nEnd + p_cSplit.size();
		if (l_nStart >= p_strData.size())
		{
			break;
		}
	}
	return l_vRet;
}