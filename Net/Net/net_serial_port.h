#ifndef _NETSERIALPORT_H
#define _NETSERIALPORT_H
#include <signal.h>

void NetSerialPortInit(void);
void SerialPortSend(const char* p_data, unsigned int p_len);
#endif // !_TCPSERVER_H