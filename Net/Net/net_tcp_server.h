#ifndef _NETTCPSERVER_H
#define _NETTCPSERVER_H

#include <signal.h>
#include <asio2/asio2.hpp>
#ifdef __cplusplus
extern "C" {
#endif
typedef enum 
{
	NET_CFGDEFAULT,
	NET_CFGSUCCESS,
	NET_CFGFALSE,
}NetStauts_CFG;


extern asio2::tcp_server g_server;
extern void RestartTcpServer();
void tcpSendAll(const char* p_data, unsigned int p_len);
void NetTcpServerInit(void);
#ifdef __cplusplus
}
#endif
#endif // !_TCPSERVER_H
