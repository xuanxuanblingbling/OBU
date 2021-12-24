#include "session_manage.h"
#include <time.h>
#include "../extern/crypto/md5.h"
#include "../extern/mongoose/mongoose.h"
#include "user_info.h"

#define BLOCK_LOGINTIME     300
#define MAX_LOGINTRYTIME    5

using namespace std;

SessionManage::SessionManage(unsigned int p_nTokenTimeout = 120, unsigned int p_nSessionTimeout = 3600)
{
	m_SessionTimeOut = p_nSessionTimeout;
	m_TokenTimeOut = p_nTokenTimeout;
}

SessionManage::~SessionManage(void)
{
	for (auto &l_aTter : m_mapSession)
		delete l_aTter.second;
	for (auto &l_aTter : m_mapToken)
		delete l_aTter.second;
}


Session *SessionManage::GetSession(string p_sSessionID)
{
	auto l_aTter = m_mapSession.find(p_sSessionID);
	if (l_aTter != m_mapSession.end())
		return l_aTter->second;
	else
		return NULL;
}

unsigned int SessionManage::GetAuthenMask(string p_sSessionID)
{
	Session *l_pSession = NULL;
	l_pSession = GetSession(p_sSessionID);
	if (l_pSession != NULL)
		return l_pSession->m_AuthenMask;
	return 0;
}

Session *SessionManage::GetSessionByName(string p_strName)
{
	for (auto l_aIter = m_mapSession.begin(); l_aIter != m_mapSession.end(); l_aIter++)
	{
		if (l_aIter->second->m_strUserName == p_strName)
			return l_aIter->second;
	}
	return NULL;
}


void SessionManage::DeleteSession(string p_sSessionID)
{
	Session * l_sWebSession = NULL;
	l_sWebSession = GetSession(p_sSessionID);
	if (l_sWebSession != NULL)
	{
		delete l_sWebSession;
		m_mapSession.erase(p_sSessionID);
	}
}


WebToken *SessionManage::GetWebToken(string p_cIpAdress)
{
	auto l_aTter = m_mapToken.find(p_cIpAdress);
	if (l_aTter != m_mapToken.end())
		return l_aTter->second;
	else
		return NULL;
}


string SessionManage::CreateWebToken(string p_cIpAdress)
{
	WebToken *l_WebToken = NULL;
	l_WebToken = GetWebToken(p_cIpAdress);
	if (l_WebToken == NULL)
	{
		l_WebToken = new WebToken();
		m_mapToken.insert(make_pair(p_cIpAdress, l_WebToken));
	}
	time(&l_WebToken->m_tCreateTime);     // 更新时间
	l_WebToken->m_strWebToken = CreateWebTokenHash(p_cIpAdress);
	LatestTokenFresh();
	return l_WebToken->m_strWebToken;
}


void SessionManage::DeleteWebToken(string p_cIpAdress)
{
	WebToken *l_WebToken;
	l_WebToken = GetWebToken(p_cIpAdress);
	if (l_WebToken != NULL)
	{
		delete l_WebToken;
		m_mapToken.erase(p_cIpAdress);
	}
}

LogActCtrl* SessionManage::GetActCtrl(string p_strKey)
{
	auto l_aTter = m_mapActCtrl.find(p_strKey);
	if (l_aTter != m_mapActCtrl.end())
		return l_aTter->second;
	else
		return NULL;
}


void SessionManage::DeleteActCtrl(string p_strKey)
{
	LogActCtrl* l_ActCtrl = GetActCtrl(p_strKey);
	if (l_ActCtrl != NULL)
	{
		delete l_ActCtrl;
		m_mapActCtrl.erase(p_strKey);
	}
}

LogActCtrl* SessionManage::CreatActCtrl(string p_strKey, bool b_addTime)
{
	LogActCtrl* l_ActCtrl = NULL;
	l_ActCtrl = GetActCtrl(p_strKey);
	if (l_ActCtrl == NULL)
	{
		l_ActCtrl = new LogActCtrl();
		l_ActCtrl->m_nErrorTimes = 0;
		m_mapActCtrl.insert(make_pair(p_strKey, l_ActCtrl));
	}
	if (l_ActCtrl->m_nErrorTimes < MAX_LOGINTRYTIME)
	{
		if (b_addTime)
			l_ActCtrl->m_nErrorTimes++;
		time(&(l_ActCtrl->m_tLoginTime));
	}
	LatestActCtrlFresh();
	return l_ActCtrl;
}


// 使用加密算法生成TOKEN
string SessionManage::CreateWebTokenHash(const string p_sHashString)
{
	double l_dTime = cs_time();
	int l_s32RandNum;
	string l_sText = "";
	int l_sec = int(l_dTime);
	int l_uSec = (l_dTime - l_sec) * 1000000;
	srand(l_uSec);
	l_s32RandNum = rand();
	l_sText = p_sHashString + std::to_string(l_sec) + std::to_string(l_s32RandNum);
	return MD5(l_sText).toStr();
}



string ProcEncryption(string &p_sSource)
{
	return p_sSource + "1";
}


// 用户的会话认证 
bool SessionManage::UserAuthentication(Session &p_sSession, string &message)
{
	Session *l_cSession, *l_cOldSession = NULL;
	string l_strPassWd;
	string l_strEncryCode;
	WebToken *l_WebToken;
	l_WebToken = GetWebToken(p_sSession.m_cIpAddress);
	if (l_WebToken == NULL)   // 没有IP 
	{
		message = "获取客户端IP信息失败!";
		return false;
	}
	
	if (l_WebToken->m_strWebToken != p_sSession.m_strWebToken)
	{
		message = "请刷新浏览器后，重新尝试登陆!";
		return false;
	}

	UserInfo l_UserInfo = GetUserInfo(p_sSession.m_nUserId);

	if (l_UserInfo.m_cStatus == 0)
	{
		message = "用户被停用，登录失败!";
		return false;
	}

	p_sSession.m_nUserId = l_UserInfo.m_nUserId;

	if(1 == l_UserInfo.m_nUserId)
	{
		l_strPassWd = l_UserInfo.m_strPassWd;
		cout << CalculateUserPassWd(&p_sSession, l_strPassWd) << endl;
		cout << p_sSession.m_strUserPassWd << endl;
		if (CalculateUserPassWd(&p_sSession, l_strPassWd) != p_sSession.m_strUserPassWd) // 密码校验失败
		{
			message = "用户登录密码错误!";
			return false;
		}
	}
	else
	{
		// l_strEncryCode = ProcEncryption(p_sSession.m_strDynamicCode);
		// if(CalculateUserPassWd(&p_sSession, l_strEncryCode) != p_sSession.m_strUserPassWd) // 密码校验失败
		// {
		// 	message = "用户动态登录密码错误，请联系管理员!";
		// 	return false;
		// }
	}
	
	
	l_cSession = new Session();
	*l_cSession = p_sSession;
	time(&l_cSession->m_tConnectTime);
	time(&l_cSession->m_tLatestActiveTime);

	l_cOldSession = GetSessionByName(p_sSession.m_strUserName);
	if (l_cOldSession != NULL)  // 剔除重复登录的用户
		DeleteSession(l_cOldSession->m_strSessionID);
	l_cSession->m_strSessionKey = CalculateSessionKey(l_cSession, l_strPassWd);
	l_cSession->m_strSessionID = CalculateSessionId(l_cSession, l_strPassWd);
	m_mapSession.insert(make_pair(l_cSession->m_strSessionID, l_cSession));
	string l_strKey = l_cSession->m_cIpAddress + l_cSession->m_strUserName;
	DeleteActCtrl(l_strKey);
	LatestSessionFresh();
	p_sSession = (*l_cSession);
	return true;
}

// 使用加密算法计算得到用户的SessionID
string SessionManage::CalculateSessionId(Session *p_sSession, string p_strPassWd)
{
	string l_strTemp = "";
	l_strTemp = p_sSession->m_strWebToken + p_sSession->m_strWebToken +
		p_sSession->m_cIpAddress + p_strPassWd + p_strPassWd;

	return MD5(l_strTemp).toStr();
}


string SessionManage::CalculateSessionKey(Session *p_sSession, string p_strPassWd)
{
	string l_strTemp = "";
	l_strTemp = p_sSession->m_strWebToken + p_sSession->m_strWebToken +
		p_strPassWd + p_strPassWd;

	return MD5(l_strTemp).toStr();
}


// 使用MD5算法计算用户的加密后的密码
string SessionManage::CalculateUserPassWd(Session *p_sSession, string p_strPassWd)
{
	string l_strTemp = "";
	l_strTemp = p_sSession->m_strWebToken + p_strPassWd;
	char l_cTempBufCode[64] = { 0 };
	return MD5(l_strTemp).toStr();
}

// 用户会话Session认证
bool SessionManage::WebSessionAuthentication(string p_strSession, string p_strIPAddr,unsigned int &p_nUserMask)
{
	Session *l_pSession = NULL;
	l_pSession = GetSession(p_strSession);
	if (l_pSession != NULL && l_pSession->m_cIpAddress == p_strIPAddr)
	{
		p_nUserMask = l_pSession->m_AuthenMask;
		time(&l_pSession->m_tLatestActiveTime);
		return true;
	}
	cout << "Requets:" <<  p_strSession << endl;
	cout << "SessionNum:" << m_mapSession.size() << endl;
	for (auto &l_data : m_mapSession)
	{
		cout << l_data.first << endl;
	}
	return false;
}

string SessionManage::GetSessionKey(string p_strSession)
{
	Session *l_pSession = NULL;
	l_pSession = GetSession(p_strSession);
	if (l_pSession != NULL)
		return l_pSession->m_strSessionKey;
	return "";
}

void SessionManage::SessionTokenFresh(void)
{
	time_t l_timeNow;
	time(&l_timeNow);
	while (m_LatestSessionTime && (l_timeNow - m_LatestSessionTime > m_SessionTimeOut))
	{
		LatestSessionFresh();
		if (m_LatestSessionTime && (l_timeNow - m_LatestSessionTime > m_SessionTimeOut))
		{
			cout << "Delete:" << m_LatestSessionTime << " "<< l_timeNow 
				<< " "<<  m_SessionTimeOut << " " <<  m_LatestSessionID << endl;

			cout << "SessionNum:" << m_mapSession.size() << endl;
			for (auto &l_data : m_mapSession)
			{
				cout << l_data.first << endl;
			}
			DeleteSession(m_LatestSessionID);
		}
			
	}

	while (m_LatestTokenTime && (l_timeNow - m_LatestTokenTime > m_TokenTimeOut))
	{
		LatestTokenFresh();
		if(m_LatestTokenTime && (l_timeNow - m_LatestTokenTime > m_TokenTimeOut))
			DeleteWebToken(m_LatestTokenIp);
	}

	while (m_LatestActCtrlTime && (l_timeNow - m_LatestActCtrlTime > BLOCK_LOGINTIME))
	{
		LatestActCtrlFresh();
		if (m_LatestActCtrlTime && (l_timeNow - m_LatestActCtrlTime > BLOCK_LOGINTIME))
			DeleteActCtrl(m_LatestActCtrlKey);
	}

}


void SessionManage::LatestSessionFresh(void)
{
	if (!m_mapSession.size())
	{
		m_LatestSessionID = "";
		m_LatestSessionTime = 0;
		return;
	}
	auto l_aIter = m_mapSession.begin();
	m_LatestSessionTime = l_aIter->second->m_tLatestActiveTime;
	m_LatestSessionID = l_aIter->first;
	for (l_aIter++; l_aIter != m_mapSession.end(); l_aIter++)
	{
		if (l_aIter->second->m_tLatestActiveTime < m_LatestSessionTime)
		{
			m_LatestSessionTime = l_aIter->second->m_tLatestActiveTime;
			m_LatestSessionID = l_aIter->first;
		}
	}
}


void SessionManage::LatestTokenFresh(void)
{
	if (!m_mapToken.size())
	{
		m_LatestTokenIp = "";
		m_LatestTokenTime = 0;
		return;
	}

	auto l_aIter = m_mapToken.begin();
	m_LatestTokenTime = l_aIter->second->m_tCreateTime;
	m_LatestTokenIp = l_aIter->first;
	for (l_aIter++; l_aIter != m_mapToken.end(); l_aIter++)
	{
		if (l_aIter->second->m_tCreateTime < m_LatestTokenTime)
		{
			m_LatestTokenTime = l_aIter->second->m_tCreateTime;
			m_LatestTokenIp = l_aIter->first;
		}
	}
}

void SessionManage::LatestActCtrlFresh(void)
{
	if (!m_mapActCtrl.size())
	{
		m_LatestActCtrlTime = 0; 
		m_LatestActCtrlKey = "";
		return;
	}
	auto l_aIter = m_mapActCtrl.begin();
	m_LatestActCtrlTime = l_aIter->second->m_tLoginTime;
	m_LatestActCtrlKey = l_aIter->first;
	for (l_aIter++; l_aIter != m_mapActCtrl.end(); l_aIter++)
	{
		if (l_aIter->second->m_tLoginTime < m_LatestActCtrlTime)
		{
			m_LatestActCtrlTime = l_aIter->second->m_tLoginTime;
			m_LatestActCtrlKey = l_aIter->first;
		}
	}
}

bool SessionManage::UserLoginCtrl(const string p_strKey, string& p_strMsg, bool b_addFlag)
{
	time_t l_timeNow;
	time(&l_timeNow);
	LogActCtrl* l_ActCtrl = CreatActCtrl(p_strKey, b_addFlag);
	if (l_ActCtrl == NULL)
		return true;
	if (l_ActCtrl->m_nErrorTimes >= MAX_LOGINTRYTIME)
	{
		p_strMsg = "已经达到最大失败次数，请" + to_string(BLOCK_LOGINTIME + l_ActCtrl->m_tLoginTime - l_timeNow) + "s后再次尝试登录!";
		return false;
	}

	p_strMsg = ", 您还剩余" + to_string(MAX_LOGINTRYTIME - l_ActCtrl->m_nErrorTimes) + "次登录机会!";
	return true;
}