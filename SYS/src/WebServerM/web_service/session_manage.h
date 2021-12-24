#pragma once

#include <string>
#include <map>


using namespace std;

typedef struct _Session
{
	int m_nUserId;					// 用户的ID
	unsigned int m_AuthenMask;      // 用户权限的掩码
	string m_strUserName;           // 用户名
	string m_strUserPassWd;         // 被加密的用户密码 
	string m_strSessionID;          // 当前会话的SessionID
	string m_strSessionKey;         // 当前会话的加密密钥
	string m_strWebToken;			// Web服务器Token
	string m_cIpAddress;            // 当前会话的IP地址
	time_t m_tLatestActiveTime;     // 最新活动的时间
	time_t m_tConnectTime;          // 创建连接的时间
	string m_strDynamicCode;        // 下发的动态码
}Session;


typedef struct _WebToken
{
	string m_strWebToken;         // 产生的Token
	string m_cIpAddress;          // 当前会话的IP地址
	time_t m_tCreateTime;         // 创建Token的时间
}WebToken;

// 用于控制用户的登录行为
typedef struct _LogActCtrl
{
	int m_nErrorTimes;              // 登录失败的次数
	time_t m_tLoginTime;            // 最后一次登录失败的时间
}LogActCtrl;


class SessionManage
{
private:
	unsigned int m_SessionTimeOut;
	unsigned int m_TokenTimeOut;
	map<string, Session *> m_mapSession; // SessionId Session
	map<string, WebToken *> m_mapToken;  // IP地址 后面是TOKEN
	map<string, LogActCtrl*> m_mapActCtrl;  // 用户登录行为控制
	time_t m_LatestSessionTime = 0;     // 最早Session的活动时间
	string m_LatestSessionID = "";
	time_t m_LatestTokenTime = 0;       // 最早Token的活动时间
	string m_LatestTokenIp = "";      
	time_t m_LatestActCtrlTime = 0;     
	string m_LatestActCtrlKey = "";

private:
	void LatestSessionFresh(void);
	void LatestTokenFresh(void);
	void LatestActCtrlFresh(void);
	WebToken *GetWebToken(string p_cIpAdress);
	void DeleteWebToken(string p_cIpAdress);
	LogActCtrl* GetActCtrl(string p_strKey);
	void DeleteActCtrl(string p_strKey);
	LogActCtrl* CreatActCtrl(string p_strKey, bool b_addTime);
	string CreateWebTokenHash(const string p_sHashString);
	string CalculateSessionId(Session *p_sSession, string p_strPassWd);         // 计算用户的Session ID
	string CalculateSessionKey(Session *p_sSession, string p_strPassWd);
	string CalculateUserPassWd(Session *p_sSession, string p_strPassWd);
	Session *GetSessionByName(string p_strName);
	

public:
	SessionManage(unsigned int p_nTokenTimeout, unsigned int p_nSessionTimeout);
	~SessionManage(void);
	void SessionTokenFresh(void);
	void DeleteSession(string p_sSessionID);
	unsigned int GetAuthenMask(string p_sSessionID);                       // 获取当前用户的
	Session *GetSession(string p_sSessionID);
	string GetSessionKey(string p_strSession);                             // 获取会话的加密密钥
	string CreateWebToken(string p_cIpAdress);                             // 定期更新会话的SessionToken
	bool UserAuthentication(Session &p_sSession, string &message);                          // 用户提交登录信息的时候认证函数
	bool WebSessionAuthentication(string p_strSession, string p_strIPAddr,unsigned int &p_nUserMask);
	bool UserLoginCtrl(const string p_strKey, string &p_strMsg, bool b_addFlag);
};
