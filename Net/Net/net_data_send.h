/*
 * @Descripttion: 
 * @version: 
 * @Author: wanji.net.cn
 * @email: mk_wanji@126.com
 * @Date: 2021-11-26 13:06:30
 * @LastEditors: VanJee Technology Co.,Ltd
 * @LastEditTime: 2021-12-01 16:08:01
 */
#include <iostream>
#include <mutex>
#include <signal.h>
#include <condition_variable>
#include <set>
#include <list>
#include <atomic>
#include <deque>
#include "Dbus/dbus_data_type.h"
#include "net_platform_warn_type.h"
extern "C"
{
#include <sys/time.h>
}

typedef struct
{
	uint32_t m_len;
	char m_mainCmd;
	char m_subCmd;
	char *m_data;
} AppMsgData;

#define NETSEND_PEROID 500
#define PORTNUMST 5555

extern std::mutex g_AppMsgMutex;
extern std::deque<AppMsgData> g_ListAppMsg;
extern std::condition_variable g_vNetSendConVar;
extern std::atomic_bool g_flag;

extern std::mutex g_SecMsgMutex;
extern std::deque<V2xPlatformSceneWarn> g_ListV2xPlatformSceneWarn;
extern std::condition_variable g_vNetSecConVar;
extern std::atomic_bool g_Sec_flag;

void NetDataSendInit(void);

void NetSendThread(void);

void SendAppMsgData(char p_mainCmd, char p_subCmd, const char *p_data, uint32_t p_len);
