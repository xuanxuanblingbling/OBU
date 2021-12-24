#ifndef _NETUDPCLIENT_H
#define _NETUDPCLIENT_H
#include <signal.h>

void NetUdpClientInit(void);
void udpSend(const char* p_data, unsigned int p_len);
#endif // !_TCPSERVER_H