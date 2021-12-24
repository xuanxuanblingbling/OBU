#ifndef __NET_WEBSOCKET_CLIENT_H__
#define __NET_WEBSOCKET_CLIENT_H__

#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
#include <libwebsockets.h>
#include <event2/event.h>

typedef struct TWebsocket_client_
{
    struct lws_context_creation_info info;
    struct libwebsocket_context *context;
	struct libwebsocket *lws;
    int ietf_version;
    bool use_ssl;

    /* 传参信息 */
    uint8_t m_u8ClientId[64];
    uint8_t m_u8Ip[64];
    int32_t m_in32Port;

    /* 连接状态 */
    bool    m_IsConnect;
    /* 线程 */
    pthread_t m_in32Pt;
    /*  */
}TWebsocket_client_t,TWebsocket_client_p;

/* 数据发送接口 */
typedef struct TWebsocketSendStruct_
{
    uint32_t 	 m_u32ChannelId;
	uint8_t 	*m_u8Data;
	int32_t 	 m_u32Datalen;
}TWebsocketSendStruct_t;


/* 函数声明 */
int FN_WebsocketClientInit(struct event_base *base,TWebsocket_client_t *p_ws);
void FN_WebsocketDeInit(TWebsocket_client_t *p_ws);

#endif