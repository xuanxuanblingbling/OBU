#pragma once
#include <iostream>
#include "../extern/sqlite3/sqlite_orm.h"
#include <iostream>
#include "../common/jsonExtent.h"
/*
* This file is used to manage user info, including username, userpasswd, useremail, userphone
* and UserAuthentication Info.
*/

#define USER_INFO_DATABASE  "/mnt/APP/Config/obu/sysm/WebServerM/config/UserInfo.db"
#define USER_INFO_TABLE      "USERINFO"
#define USER_PASSWD_TABLE    "USERPASSWD"

using namespace std;
using namespace sqlite_orm;

typedef struct _UserInfo
{
	int m_nUserId;           // 用户ID
	string m_strName;        // 用户姓名
	string m_strPassWd;      // 用户密码
	string m_strCreateTime;  // 创建时间
	string m_strCompany;     // 用户公司
	string m_strDepartment;  // 用户部门
	string m_strPhoneNum;    // 用户电话
	string m_strEmail;       // 用户邮箱
	string m_strDesCription; // 用户简介
	string m_strRole;        // 用户角色
	char m_cStatus;          // 用户状态
}UserInfo;

#define GetUserInfoStorage(p_strDataBase, p_strTable)  make_storage(p_strDataBase,\
		make_table(p_strTable,\
		make_column("id", &UserInfo::m_nUserId, primary_key()),\
		make_column("name", &UserInfo::m_strName, unique()),\
		make_column("passwd", &UserInfo::m_strPassWd),\
		make_column("company", &UserInfo::m_strCompany),\
		make_column("department", &UserInfo::m_strDepartment),\
		make_column("role", &UserInfo::m_strRole),\
		make_column("phone", &UserInfo::m_strPhoneNum),\
		make_column("email", &UserInfo::m_strEmail),\
		make_column("createTime", &UserInfo::m_strCreateTime),\
		make_column("description", &UserInfo::m_strDesCription),\
		make_column("status", &UserInfo::m_cStatus)))


void to_json(json& p_j, const UserInfo& p_sInfo);

void from_json(const json &p_j, UserInfo& p_sInfo);

void InitUserInfoStorage();

// set user info, when userid = -1, add user
bool AddUserInfo(UserInfo p_pUserInfo);

bool UpdateUserInfo(UserInfo p_pUserInfo);

// delete user info by id
bool DelUserInfo(string p_nUserName);


// delete user info by id
bool DelUserInfo(int p_nUserId);


// Get user info by id
UserInfo GetUserInfo(int p_nUserId);


// Get user info by name
UserInfo GetUserInfo(string p_nUserName);

bool CheckUserClass(UserInfo& p_pUserInfo, const map<string, char>& p_Role);

unsigned int GetUserRoleMask(string& p_strRole, const map<string, char>& p_Role);

