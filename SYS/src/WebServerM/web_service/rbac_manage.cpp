#include "../web_service/rbac_manage.h"
#include "../common/web_common.h"
#include <sstream>
#include <fstream>
#include <stack>


#define CMDLIST {"ls", "ash", "echo", "lsmod", "rm", "systemd-machine-id-setup", "busybox", "egrep", "lsmod.kmod", "rmdir", "systemd-notify", \
                 "busybox.nosuid", "false", "machinectl", "run-parts", "systemd-sysusers", "busybox.suid", "fgrep", "mkdir", "sed", \
                 "systemd-tmpfiles", "cat", "getopt", "mknod", "sh", "systemd-tty-ask-password-agent", "chattr", "grep", "mktemp", \
                 "sleep", "tar", "chgrp", "gunzip", "more", "stat", "touch", "chmod", "gzip", "mount", "stty", "true", "chown", \
                 "hostname", "mount.util-linux", "su", "udevadm", "cp", "journalctl", "mv", "su.shadow", "umount", "cpio", "kill", \
                 "netstat", "sync", "uname", "date", "kmod", "networkctl", "systemctl", "usleep", "dd", "ln", "pidof", "systemd-ask-password", \
                 "vi", "df", "login", "ping", "systemd-escape", "watch", "dmesg", "login.shadow", "ping6", "systemd-firstboot", "zcat", "dnsdomainname", \
                 "loginctl", "ps", "systemd-hwdb", "dumpkmap", "ls", "pwd", "systemd-inhibit"}


#define HTMLLIST {"check_device.html", "check_param.html", "db_query_algtable.html", "db_query_certable.html", "logfile_bowser.html", "log_analysis.html", "dynamic_info.html", "fault_info.html", \
                  "static_info.html", "certification_list.html", "manage_authenuri.html", "manage_ipacl.html", "manage_user.html", "manage_user_edit.html", "role_manage.html", "basic_param.html", \
                  "connect_device_edit.html", "connect_device_list.html", "message.html", "module_param.html", "backup_setting.html", "data_backup.html", "update_system.html"};



RbacManage::RbacManage(string p_strFName)
{
	m_UpdataFlag = 0;
	m_strFileName = p_strFName;
	m_CmdList = CMDLIST;
	m_HtmlList = HTMLLIST;
}

RbacManage::~RbacManage()
{
	return;
}

bool RbacManage::CheckUserAuthen(string &p_Item, const unordered_map<string, unsigned int> &p_mapAuthen, unsigned int p_nRoleMask)
{
	if (p_mapAuthen.find(p_Item) == p_mapAuthen.end())
		return true;
	return !((p_mapAuthen.at(p_Item) & p_nRoleMask) == 0);
}

bool RbacManage::CheckFileAuthen(string &p_Item, unsigned int p_nRoleMask)
{
	return CheckUserAuthen(p_Item, m_FileAuthen, p_nRoleMask);
}

bool RbacManage::CheckCmdAuthen(string &p_Item, unsigned int p_nRoleMask)
{
	return CheckUserAuthen(p_Item, m_CmdAuthen, p_nRoleMask);
}

bool RbacManage::CheckHtmlAuthen(string &p_Item, unsigned int p_nRoleMask)
{
	return CheckUserAuthen(p_Item, m_HtmlAuthen, p_nRoleMask);
}

bool RbacManage::CheckUriAuthen(string &p_Item, unsigned int p_nRoleMask)
{
	return CheckUserAuthen(p_Item, m_UriAuthen, p_nRoleMask);
}

map<string, char> RbacManage::GetAuthenList(const unordered_map<string, unsigned int> &p_mapAuthen, unsigned int p_nRoleMask)
{
	map<string, char> l_mapRet;
	char l_cAuthen = 0;
	for (auto &l_tData : p_mapAuthen)
	{
		if (l_tData.second & p_nRoleMask & 0xFFFF)
			l_cAuthen |= 0x01;
		if (l_tData.second & p_nRoleMask & 0xFFFF0000)
			l_cAuthen |= 0x02;
		if (l_cAuthen)
			l_mapRet.insert(make_pair(l_tData.first, l_cAuthen));
	}
	return l_mapRet;
}

set<string> RbacManage::GetAuthenSet(const unordered_map<string, unsigned int> &p_mapAuthen, unsigned int p_nRoleMask)
{
	set<string> l_setRet;
	for (auto &l_tData : p_mapAuthen)
		if (l_tData.second & p_nRoleMask & 0xFFFF)
			l_setRet.insert(l_tData.first);
	return l_setRet;
}

map<string, char> RbacManage::GetFileAuthen(unsigned int p_nRoleMask)
{
	return GetAuthenList(m_FileAuthen, p_nRoleMask);
}
 
map<string, char> RbacManage::GetUriAuthen(unsigned int p_nRoleMask)
{
	return GetAuthenList(m_UriAuthen, p_nRoleMask);
}

set<string> RbacManage::GetHtmlAuthen(unsigned int p_nRoleMask)
{
	return GetAuthenSet(m_HtmlAuthen, p_nRoleMask);
}

set<string> RbacManage::GetCmdAuthen(unsigned int p_nRoleMask)
{
	return GetAuthenSet(m_CmdAuthen, p_nRoleMask);
}

string RbacManage::GetRoleNameById(char p_nId)
{
	for (auto &l_tData : m_RoleList)
		if (l_tData.second == p_nId)
			return l_tData.first;
	return "";
}


bool RbacManage::SaveToFile(void)
{
	json l_jData;
	unordered_map<string, char> l_RoleList;
	for (auto l_tData = m_RoleList.begin(); l_tData != m_RoleList.end(); l_tData++)
		l_RoleList.insert(make_pair(sconv(l_tData->first), l_tData->second));
	l_jData["role"] = l_RoleList;
	l_jData["uri"] = m_UriAuthen;
	l_jData["file"] = m_FileAuthen;
	l_jData["html"] = m_HtmlAuthen;
	l_jData["cmd"] = m_CmdAuthen;
	l_jData["ssh"] = m_SShAuthen;
	l_jData["chroot"] = m_chRootAuthen;
	m_UpdataFlag = 1;
	fstream l_File(m_strFileName, ios::out | ios::trunc);
	if (l_File.is_open())
	{
		l_File << l_jData.dump(1, '\t');
		l_File.close();
		return true;
	}
	return false;
}

void RbacManage::CheckRoleParam(void)
{
	set<char> l_setMask;
	set<string> l_deteRole;
	if (m_RoleList.find("超级管理员") == m_RoleList.end())
		m_RoleList.insert(make_pair("超级管理员", 0));
	l_setMask.insert(0);
	for (auto l_tData = m_RoleList.begin(); l_tData != m_RoleList.end(); l_tData++)
	{
		if (l_tData->first != "超级管理员")
			if (l_setMask.find(l_tData->second) != l_setMask.end() || l_tData->second > 15 || l_tData->second < 0)   // 找到
				l_deteRole.insert(l_tData->first);
			else
			{
				try
				{
					l_setMask.insert(l_tData->second);
				}
				catch (...)
				{
					l_deteRole.insert(l_tData->first);
				}
			}
	}

	for (auto &l_tData : l_deteRole)
		m_RoleList.erase(l_tData);
}


void RbacManage::CheckMapParam(const set<string> &p_List, unordered_map<string, unsigned int> &p_Authen)
{
	set<string> l_deteData;
	for (auto &l_tData : p_Authen)
		l_tData.second |= 0x010001;

	for (auto l_tData = p_Authen.begin(); l_tData != p_Authen.end(); l_tData++)
		if (p_List.find(l_tData->first) == p_List.end())
			l_deteData.insert(l_tData->first);
	
	for (auto &l_tData : l_deteData)
		p_Authen.erase(l_tData);

	for (auto &l_tData : p_List)
	{
		if (p_Authen.find(l_tData) == p_Authen.end())
			p_Authen.insert(make_pair(l_tData, 0x010001));
	}

}

void RbacManage::CheckAllParam(void)
{
	CheckRoleParam();
	CheckMapParam(m_UriList, m_UriAuthen);
	CheckMapParam(m_CmdList, m_CmdAuthen);
	CheckMapParam(m_HtmlList, m_HtmlAuthen);

	for (auto &l_tData : m_FileAuthen)
		l_tData.second |= 0x010001;

	m_SShAuthen |= 0x010001;
	m_chRootAuthen |= 0x010001;  
}

bool RbacManage::RestoreFromeFile(void)
{
	json l_jConfigData;
	unordered_map<string, char> l_RoleList;
	unordered_map<string, unsigned int> l_mapList;
	fstream l_File(m_strFileName, ios::in);
	m_RoleList.clear();
	m_UriAuthen.clear();
	m_FileAuthen.clear();
	m_HtmlAuthen.clear();
	if (l_File.is_open())
	{
		l_File.seekg(0, std::ios::beg);
		ostringstream l_Content;
		l_Content << l_File.rdbuf();
		l_File.close();
		try
		{
			l_jConfigData = json::parse(l_Content.str());
			if (l_jConfigData.find("role") != l_jConfigData.end())
				l_RoleList = l_jConfigData["role"].get<unordered_map<string, char> >();

			for (auto l_tData = l_RoleList.begin(); l_tData != l_RoleList.end(); l_tData++)
				m_RoleList.insert(make_pair(invs(l_tData->first), l_tData->second));

			if (l_jConfigData.find("ssh") != l_jConfigData.end())
				m_SShAuthen = l_jConfigData["ssh"].get<unsigned int>();

			if (l_jConfigData.find("chroot") != l_jConfigData.end())
				m_chRootAuthen = l_jConfigData["chroot"].get<unsigned int>();

			if (l_jConfigData.find("uri") != l_jConfigData.end())
				m_UriAuthen = l_jConfigData["uri"].get<unordered_map<string, unsigned int> >();

			if (l_jConfigData.find("file") != l_jConfigData.end())
				l_mapList = l_jConfigData["file"].get<unordered_map<string, unsigned int> >();

			for (auto l_tData = l_mapList.begin(); l_tData != l_mapList.end(); l_tData++)
				m_FileAuthen.insert(make_pair(invs(l_tData->first), l_tData->second));

			if (l_jConfigData.find("cmd") != l_jConfigData.end())
				m_CmdAuthen = l_jConfigData["cmd"].get<unordered_map<string, unsigned int> >();

			if (l_jConfigData.find("html") != l_jConfigData.end())
				m_HtmlAuthen = l_jConfigData["html"].get<unordered_map<string, unsigned int> >();
		}
		catch (...)
		{
			;
		}
	}
	CheckAllParam();
	return SaveToFile();
}

void RbacManage::DeleteRole(char p_cId)
{
	string l_strName = "";
	if (!(p_cId > 0 && p_cId < 16))
		return;

	for (auto &l_tData : m_RoleList)
	{
		if (p_cId == l_tData.second)
		{
			l_strName = l_tData.first; 
		}	
	}

	if (!l_strName.empty())
	{
		unsigned int l_nMask = ((1 << p_cId) << 16) | (1 << p_cId);
		m_RoleList.erase(l_strName);
		for (auto &l_tData : m_UriAuthen)
		{
			l_tData.second ^= l_nMask;
		}
		for (auto &l_tData : m_FileAuthen)
		{
			l_tData.second ^= l_nMask;
		}
		for (auto &l_tData : m_CmdAuthen)
		{
			l_tData.second ^= l_nMask;
		}
		for (auto &l_tData : m_HtmlAuthen)
		{
			l_tData.second ^= l_nMask;
		}
		m_chRootAuthen ^= (1 << p_cId);
		m_SShAuthen ^= (1 << p_cId);
		SaveToFile();
	}
}
bool RbacManage::EditRole(int p_cId, string p_strName, int ssh, int chroot)
{	
	if (p_strName.empty())
		return false;
	char c_cId = p_cId + '0';
	if (p_cId < 0)
	{	
		set<char> l_setMask;
		if (m_RoleList.find(p_strName) != m_RoleList.end())
			return false;
		char k;

		CheckRoleParam();
		for (auto &l_tData : m_RoleList)
			l_setMask.insert(l_tData.second);

		for (k = 1; k < 16; k++)
			if (l_setMask.find(-1) == l_setMask.end())
				break;
		if (k >= 16)
			return false;

		c_cId = k;
		m_RoleList.insert(make_pair(p_strName, c_cId));
		m_RoleList[p_strName] = c_cId;
	}
	if (GetRoleNameById(c_cId) != p_strName)
		return false;
	if(chroot) 
		m_chRootAuthen |= (1 << c_cId);
	else
		m_chRootAuthen &= (~(1 << c_cId));

	if(ssh)
		m_SShAuthen |= (1 << c_cId);
	else
		m_SShAuthen &= (~(1 << c_cId));

	SaveToFile();
	return true;
}


bool RbacManage::ModifyRoleAuthen(const string &l_strName, unordered_map<string, unsigned int> &p_mapUserAuthen, const map<string, char> &p_mapAuthen)
{
	char l_cMask = 0;
	if (m_RoleList.find(l_strName) == m_RoleList.end())
		return false;

	l_cMask = m_RoleList[l_strName];

	if (l_cMask > 0 && l_cMask < 16)
	{
		int l_nMask = ((1 << l_cMask) << 16) | (1 << l_cMask);
		unsigned int l_nMaskRead = (1 << l_cMask);
		unsigned int l_nMaskWrite = ((1 << l_cMask) << 16);
		unsigned int l_nMaskRW = ((1 << l_cMask) << 16) | (1 << l_cMask);

		for (auto &l_tData : p_mapAuthen)
		{
			if (p_mapUserAuthen.find(l_tData.first) != p_mapUserAuthen.end())
			{
				p_mapUserAuthen[l_tData.first] &= (~l_nMaskRW);
				if (l_tData.second == 1)
					p_mapUserAuthen[l_tData.first] |= l_nMaskRead;
				else if (l_tData.second == 2)
					p_mapUserAuthen[l_tData.first] |= l_nMaskWrite;
				else if (l_tData.second == 3)
					p_mapUserAuthen[l_tData.first] |= l_nMaskRW;
			}
		}
	}
	else
	{
		return false;
	}
	return SaveToFile();
}


bool RbacManage::ModifyRoleUri(const string &l_strName, const map<string, char> &p_mapAuthen)
{
	return ModifyRoleAuthen(l_strName, m_UriAuthen, p_mapAuthen);
}


bool RbacManage::ModifyRoleFile(const string &l_strName, const map<string, char> &p_mapAuthen)
{
	return ModifyRoleAuthen(l_strName, m_FileAuthen, p_mapAuthen);
}

bool RbacManage::ModifyRoleCmd(const string &l_strName, const map<string, char> &p_mapAuthen)
{
	return ModifyRoleAuthen(l_strName, m_CmdAuthen, p_mapAuthen);
}

bool RbacManage::ModifyRoleHtml(const string &l_strName, const map<string, char> &p_mapAuthen)
{
	return ModifyRoleAuthen(l_strName, m_HtmlAuthen, p_mapAuthen);
}

bool RbacManage::AddFileItem(const string& l_strFile)
{
	if (l_strFile.empty() || m_FileAuthen.find(l_strFile) != m_FileAuthen.end())
		return false;

	m_FileAuthen.insert(make_pair(l_strFile, 0x010001));
	return SaveToFile();
}


bool RbacManage::DeleteFileItem(const string& l_strFile)
{
	if (m_FileAuthen.find(l_strFile) == m_FileAuthen.end())
		return false;

	m_FileAuthen.erase(l_strFile);
	return SaveToFile();
}