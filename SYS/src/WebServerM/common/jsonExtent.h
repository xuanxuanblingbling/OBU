#pragma once

#include "../extern/json/json.hpp"
#include <iostream>
#include <vector>

using json = nlohmann::json;
using namespace std;

string GetJsonStringData(const json &p_jData, const string &p_strKey, string p_strDefault);

string GetJsonStringData(const json &p_jData, const string &p_strKey);

int GetJsonIntData(const json &p_jData, const string &p_strKey);

int GetJsonIntData(const json &p_jData, const string &p_strKey, int p_nDefault);


char *GetJsonCStr(const json &p_jData, const string &p_strKey, const string &p_strSecondKey, char *p_dest);

int GetJsonCInt(const json &p_jData, const string &p_strKey, const string &p_strSecondKey);


unsigned short GetJsonUshortData(const json &p_jData, const string &p_strKey);

vector<string> GetJsonVecStringData(const json &p_jData, const string &p_strKey);

vector<int> GetJsonVecIntData(const json &p_jData, const string &p_strKey, vector<int>& p_vDefault);

vector<int> GetJsonVecIntData(const json &p_jData, const string &p_strKey);

unsigned short GetJsonUshortData(const json &p_jData, const string &p_strKey, unsigned short p_nDefault);

vector<string> GetJsonVecStringData(const json &p_jData, const string &p_strKey, vector<string>& p_vDefault);


