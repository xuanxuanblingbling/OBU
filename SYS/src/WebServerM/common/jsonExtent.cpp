#include "jsonExtent.h"
#include "string_conv.h"


struct JsonKeyFoundException : public exception
{
	const char * what() const throw ()
	{
		return "Key-Value Not Found!";
	}
};

string GetJsonStringData(const json &p_jData, const string &p_strKey, string p_strDefault)
{
	if (p_jData.find(p_strKey) == p_jData.end())
	{
		return invs(p_strDefault);
	}
	else
	{
		try
		{
			return invs(p_jData[p_strKey].get<string>());
		}
		catch (...)
		{
			return invs(p_strDefault);
		}
	}
}


string GetJsonStringData(const json &p_jData, const string &p_strKey)
{
	if (p_jData.find(p_strKey) == p_jData.end())
		throw JsonKeyFoundException();
	else
		return invs(p_jData[p_strKey].get<string>());
}

//lhj
char *GetJsonCStr(const json &p_jData, const string &p_strKey, const string &p_strSecondKey, char *p_dest)
{
	if (p_jData.find(p_strKey) == p_jData.end())
	{	
		throw JsonKeyFoundException();
	}
	else
	{
		if(p_strSecondKey.empty())
		{
    		return strcpy(p_dest, p_jData[p_strKey].get<string>().c_str());
		}
		else
		{
			json l_jtemp = p_jData[p_strKey];
			if(l_jtemp.find(p_strSecondKey) == l_jtemp.end())
			{
				throw JsonKeyFoundException();
			}
			else
			{
    			return strcpy(p_dest, l_jtemp[p_strSecondKey].get<string>().c_str());				
			}
		}	
	}
}


int GetJsonIntData(const json &p_jData, const string &p_strKey)
{
	if (p_jData.find(p_strKey) == p_jData.end())
		throw JsonKeyFoundException();
	else
		if (p_jData[p_strKey].is_string())
			return stoi(p_jData[p_strKey].get<string>());
		else
			return p_jData[p_strKey].get<int>();
}

//lhj
int GetJsonCInt(const json &p_jData, const string &p_strKey, const string &p_strSecondKey)
{
	if (p_jData.find(p_strKey) == p_jData.end())
		throw JsonKeyFoundException();
	else
	{
		if(p_strSecondKey.empty())
		{
			if (p_jData[p_strKey].is_string())
				return stoi(p_jData[p_strKey].get<string>());
			else
				return p_jData[p_strKey].get<int>();
		}
		else
		{
			json l_jtemp = p_jData[p_strKey];
			if(l_jtemp.find(p_strSecondKey) == l_jtemp.end())
			{
				throw JsonKeyFoundException();
			}
			else
			{
    			if (l_jtemp[p_strSecondKey].is_string())
					return stoi(l_jtemp[p_strSecondKey].get<string>());
				else
					return l_jtemp[p_strSecondKey].get<int>();			
			}
		}		
	}
}


int GetJsonIntData(const json &p_jData, const string &p_strKey, int p_nDefault)
{
	if (p_jData.find(p_strKey) == p_jData.end())
	{
		return p_nDefault;
	}
	else
	{
		try
		{
			if (p_jData[p_strKey].is_string())
				return stoi(p_jData[p_strKey].get<string>());
			else
				return p_jData[p_strKey].get<int>();
		}
		catch (...)
		{
			return p_nDefault;
		}
	}
}


unsigned short GetJsonUshortData(const json &p_jData, const string &p_strKey)
{
	if (p_jData.find(p_strKey) == p_jData.end())
		throw JsonKeyFoundException();
	else
		if (p_jData[p_strKey].is_string())
			return stoi(p_jData[p_strKey].get<string>());
		else
			return p_jData[p_strKey].get<unsigned short>();
}


unsigned short GetJsonUshortData(const json &p_jData, const string &p_strKey, unsigned short p_nDefault)
{
	if (p_jData.find(p_strKey) == p_jData.end())
	{
		return p_nDefault;
	}
	else
	{
		try
		{
			if (p_jData[p_strKey].is_string())
				return stoi(p_jData[p_strKey].get<string>());
			else
				return p_jData[p_strKey].get<unsigned short>();
		}
		catch (...)
		{
			return p_nDefault;
		}
	}
}

vector<string> GetJsonVecStringData(const json &p_jData, const string &p_strKey, vector<string> &p_vDefault)
{
	if (p_jData.find(p_strKey) == p_jData.end())
	{
		return invs(p_vDefault);
	}
	else
	{
		try
		{
			if (p_jData[p_strKey].is_string())
				return invs((json::parse(p_jData[p_strKey].get<string>())).get<vector<string>>());
			else
				return invs(p_jData[p_strKey].get<vector<string>>());
		}
		catch (...)
		{
			return invs(p_vDefault);
		}
	}
}


vector<string> GetJsonVecStringData(const json &p_jData, const string &p_strKey)
{
	if (p_jData.find(p_strKey) == p_jData.end())
		throw JsonKeyFoundException();
	else
		if (p_jData[p_strKey].is_string())
			return invs((json::parse(p_jData[p_strKey].get<string>())).get<vector<string>>());
		else
			return invs(p_jData[p_strKey].get<vector<string>>());
}

vector<int> GetJsonVecIntData(const json &p_jData, const string &p_strKey, vector<int> &p_vDefault)
{
	if (p_jData.find(p_strKey) == p_jData.end())
	{
		return p_vDefault;
	}
	else
	{
		try
		{
			if (p_jData[p_strKey].is_string())
				return (json::parse(p_jData[p_strKey].get<string>())).get<vector<int>>();
			else
				return p_jData[p_strKey].get<vector<int>>();
		}
		catch (...)
		{
			return p_vDefault;
		}
	}
}


vector<int> GetJsonVecIntData(const json &p_jData, const string &p_strKey)
{
	if (p_jData.find(p_strKey) == p_jData.end())
		throw JsonKeyFoundException();
	else
		if (p_jData[p_strKey].is_string())
			return (json::parse(p_jData[p_strKey].get<string>())).get<vector<int>>();
		else
			return p_jData[p_strKey].get<vector<int>>();
}

