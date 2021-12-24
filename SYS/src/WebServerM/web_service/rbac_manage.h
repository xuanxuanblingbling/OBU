#pragma once
#include "../common/string_conv.h"
#include "../common/jsonExtent.h"
#include <string>
#include <unordered_map>
#include "../extern/json/json.hpp"


class RbacManage
{
public:
	map<string, char> m_RoleList;
	string m_strFileName;
	set<string> m_UriList;
	set<string> m_CmdList;
	set<string> m_HtmlList;
	unordered_map<string, unsigned int> m_UriAuthen;
	unordered_map<string, unsigned int> m_FileAuthen;
	unordered_map<string, unsigned int> m_CmdAuthen;
	unordered_map<string, unsigned int> m_HtmlAuthen;
	unsigned int m_SShAuthen;
	unsigned int m_chRootAuthen;
	int m_UpdataFlag;

public:
	RbacManage(string p_strFName);
	~RbacManage();
	bool CheckUserAuthen(string &p_Item, const unordered_map<string, unsigned int> &p_mapAuthen, unsigned int p_nRoleMask);
	bool CheckFileAuthen(string &p_Item, unsigned int p_nRoleMask);
	bool CheckCmdAuthen(string &p_Item, unsigned int p_nRoleMask);
	bool CheckHtmlAuthen(string &p_Item, unsigned int p_nRoleMask);
	bool CheckUriAuthen(string &p_Item, unsigned int p_nRoleMask);
	string GetRoleNameById(char p_nId);
	map<string, char> GetAuthenList(const unordered_map<string, unsigned int> &p_mapAuthen, unsigned int p_nRoleMask);
	set<string> GetAuthenSet(const unordered_map<string, unsigned int> &p_mapAuthen, unsigned int p_nRoleMask);
	map<string, char> GetFileAuthen(unsigned int p_nRoleMask);
	map<string, char> GetUriAuthen(unsigned int p_nRoleMask);
	set<string> GetHtmlAuthen(unsigned int p_nRoleMask);
	set<string> GetCmdAuthen(unsigned int p_nRoleMask);
	void CheckAllParam(void);
	void CheckRoleParam(void);
	void CheckMapParam(const set<string> &p_HtmlList, unordered_map<string, unsigned int> &p_UriAuthen);
	bool SaveToFile(void);
	bool RestoreFromeFile(void);
	void DeleteRole(char p_cId);
	bool EditRole(int p_cId, string p_strName, int ssh, int chroot);
	bool ModifyRoleAuthen(const string &l_strName, unordered_map<string, unsigned int> &p_mapUserAuthen, const map<string, char> &p_mapAuthen);
	bool ModifyRoleUri(const string &l_strName, const map<string, char> &p_mapAuthen);
	bool ModifyRoleFile(const string &l_strName, const map<string, char> &p_mapAuthen);
	bool ModifyRoleCmd(const string &l_strName, const map<string, char> &p_mapAuthen);
	bool ModifyRoleHtml(const string &l_strName, const map<string, char> &p_mapAuthen);
	bool AddFileItem(const string& l_strFile);
	bool DeleteFileItem(const string &l_strFile);
};
