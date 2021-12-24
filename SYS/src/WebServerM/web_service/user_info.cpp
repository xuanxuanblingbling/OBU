#include "user_info.h"
#include "../common/string_conv.h"
#include <unordered_map>
#include <vector>


void to_json(json& p_j, const UserInfo& p_sInfo)
{
	p_j = json{ { "id", (p_sInfo.m_nUserId)},
		{ "name", sconv(p_sInfo.m_strName)},
		{ "company", sconv(p_sInfo.m_strCompany)},
		{ "department", sconv(p_sInfo.m_strDepartment)},
		{ "role", sconv(p_sInfo.m_strRole)},
		{ "phone", sconv(p_sInfo.m_strPhoneNum)},
		{ "email", sconv(p_sInfo.m_strEmail)},
		{ "passwd", sconv(p_sInfo.m_strPassWd)},
		{ "createTime", sconv(p_sInfo.m_strCreateTime)},
		{ "description", sconv(p_sInfo.m_strDesCription)},
		{ "status", p_sInfo.m_cStatus}};
}

void from_json(const json &p_j, UserInfo& p_sInfo)
{
	p_sInfo.m_cStatus = GetJsonIntData(p_j, "status");
	p_sInfo.m_nUserId = GetJsonIntData(p_j, "id");
	p_sInfo.m_strRole = GetJsonStringData(p_j, "role");
	p_sInfo.m_strEmail = GetJsonStringData(p_j, "email");
	p_sInfo.m_strEmail = GetJsonStringData(p_j, "email");
	p_sInfo.m_strCompany = GetJsonStringData(p_j, "company");
	p_sInfo.m_strName = GetJsonStringData(p_j, "name");
	p_sInfo.m_strDepartment = GetJsonStringData(p_j, "department");
	p_sInfo.m_strPhoneNum = GetJsonStringData(p_j, "phone");
	p_sInfo.m_strPassWd = GetJsonStringData(p_j, "passwd");
	p_sInfo.m_strDesCription = GetJsonStringData(p_j, "description");
	p_sInfo.m_strCreateTime = GetJsonStringData(p_j, "createTime");
	p_sInfo.m_strEmail = GetJsonStringData(p_j, "email");
}

void InitUserInfoStorage()
{
	auto l_aStorage1 = GetUserInfoStorage(USER_INFO_DATABASE, USER_INFO_TABLE);
	l_aStorage1.sync_schema();
	UserInfo l_uUser = { -1, "admin", "admin", " ", "万集科技", "智能网联", "18813441111","wanji@wanji.net", "初始测试用户", "超级管理员", 1};
	AddUserInfo(l_uUser);
}

// set user info, when userid = -1, add user
bool AddUserInfo(UserInfo p_pUserInfo)
{
	auto l_aStorage = GetUserInfoStorage(USER_INFO_DATABASE, USER_INFO_TABLE);
	try
	{
		l_aStorage.insert(p_pUserInfo);
		return true;
	}
	catch (...) {   // 一般由于用户名重名造成的失败
		return false;
	}
}


bool UpdateUserInfo(UserInfo p_pUserInfo)
{
	if (p_pUserInfo.m_nUserId < 0) return false;
	auto l_aStorage = GetUserInfoStorage(USER_INFO_DATABASE, USER_INFO_TABLE);
	try
	{
		l_aStorage.update(p_pUserInfo);
		return true;
	}
	catch (...) {   // 一般由于用户名重名造成的失败
		return false;
	}
}


// delete user info by id
bool DelUserInfo(string p_nUserName)
{
	int l_nUserId = -1;
	auto l_aStorage = GetUserInfoStorage(USER_INFO_DATABASE, USER_INFO_TABLE);
	auto l_aInfoList = l_aStorage.select(&UserInfo::m_nUserId, where(c(&UserInfo::m_strName) == p_nUserName));
	if (l_aInfoList.size())
		l_nUserId = l_aInfoList[0];

	return DelUserInfo(l_nUserId);
}


bool DelUserInfo(int p_nUserId)
{
	auto l_aStorage = GetUserInfoStorage(USER_INFO_DATABASE, USER_INFO_TABLE);
	try
	{
		l_aStorage.remove<UserInfo>(p_nUserId);
		return true;
	}
	catch (...) {
		return false;
	}
}

// Get user info by id
UserInfo GetUserInfo(int p_nUserId)
{
	UserInfo l_sUserInfo;
	l_sUserInfo.m_nUserId = -1;
	l_sUserInfo.m_cStatus = 1;
	auto l_aStorage = GetUserInfoStorage(USER_INFO_DATABASE, USER_INFO_TABLE);
	auto l_pUserInfo = l_aStorage.get_pointer<UserInfo>(p_nUserId);
	if (l_pUserInfo)
	{
		l_sUserInfo = *l_pUserInfo;
	}
	return l_sUserInfo;
}

// Get user info by name
UserInfo GetUserInfo(string p_nUserName)
{
	int l_nUserId = -1;
	auto l_aStorage = GetUserInfoStorage(USER_INFO_DATABASE, USER_INFO_TABLE);
	auto l_aInfoList = l_aStorage.select(&UserInfo::m_nUserId, where(c(&UserInfo::m_strName) == p_nUserName));
	if (l_aInfoList.size())
		l_nUserId = l_aInfoList[0];

	return GetUserInfo(l_nUserId);
}


bool CheckUserClass(UserInfo &p_pUserInfo, const map<string, char> &p_Role)
{
	bool l_strRet = true;
	vector<string> l_vRole = SplitString(p_pUserInfo.m_strRole, ",", 1), l_addRole;
	for (auto &l_tData : l_vRole)
	{
		if (p_Role.find(l_tData) == p_Role.end())
			l_strRet = false;
		else
			l_addRole.push_back(l_tData);
	}

	if (!l_strRet)
	{
		string l_strRole = "";
		for (auto& l_tData : l_addRole)
			l_strRole += l_tData + ",";
		if (!l_strRole.empty())
			p_pUserInfo.m_strRole = l_strRole.substr(0, l_strRole.length() - 1);
		else
			p_pUserInfo.m_strRole = "";
	}
	return l_strRet;
}

unsigned int GetUserRoleMask(string& p_strRole, const map<string, char>& p_Role)
{
	unsigned int l_nRoleMask = 0;
	vector<string> l_vRole = SplitString(p_strRole, ",", 1);
	for (auto& l_tData : l_vRole)
	{
		if (p_Role.find(l_tData) != p_Role.end())
		{
			char l_cID = p_Role.at(l_tData);
			if ((l_cID >= 0) && (l_cID < 16))
				l_nRoleMask |= (((1 << l_cID) << 16) | (1 << l_cID));
		}
	}
	return l_nRoleMask;
}
