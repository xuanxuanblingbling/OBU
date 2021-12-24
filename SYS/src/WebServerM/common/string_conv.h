#pragma once


#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include <set>
#ifdef NONUTF8CONV
#define invs(s) s
#define sconv(s) s
#else
#define invs(s)   strinvs(s)
#define sconv(s)  strconv(s)

#endif

std::string strinvs(const std::string &s);

std::string strconv(const std::string &s);

std::vector<std::string> strinvs(std::vector<std::string> s);

std::vector<std::string> strconv(std::vector<std::string> s);

std::wstring s2ws(const std::string& s);

std::string ws2s(const std::wstring& w_str);

std::wstring s2wsinv(const std::string& s);

std::string ws2sinv(const std::wstring& w_str);

std::string subreplace(std::string resource_str, const std::string &sub_str, const std::string &new_str);

std::string VecCharToString(const std::vector<char> &p_vChar);

std::vector<char> StringToVecChar(const std::string &p_strData);

std::vector<std::string> SplitString(std::string &p_strData, std::string p_cSplit, int p_nDeleteBlank);

std::string VectorToString(std::vector<std::string> &p_vStrList);

std::vector<int> VecStringToVecInt(std::vector<std::string> &p_vStrList);

std::vector<std::string> VecIntToVecString(std::vector<int> &p_vIntList);