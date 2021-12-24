#ifndef _PORT_H_
#define _PORT_H_
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include "PublicMsg.h"

#define RECVQUEUE_MAXNUM 100
#define RECVINFOBUF_MAXSIZE 3000
#define RECVINFORel_MAXSIZE 100

#define WJ_EXTENSIONINFO_LEN 32
#define WJ_EXTEN_NUM 10
/**
 * @brief DSM数据中拓展域数据结构.
 */
typedef struct _ExtenSion
{
	uint8_t ElementID;							 //扩展域信息标识
	uint8_t ByteLength;							 //扩展域信息长度
	uint8_t ExtensionInfo[WJ_EXTENSIONINFO_LEN]; //扩展域信息内容
} __attribute__((packed)) tExtenSion;

typedef struct _ExtenSionCommn_ST
{
	uint8_t u8ExtenNum;						 //扩展域信息个数
	tExtenSion extenSionCommn[WJ_EXTEN_NUM]; //扩展域信息
} __attribute__((packed)) tExtenSionCommn_ST;

typedef struct stc_RcvInfo
{
	int32_t nTxAid;
	int32_t priority;
	uint64_t u64InTime;					 //进入队列时间(us)
	int32_t nBuffLen;					 //数据长度
	int8_t acBuff[MAX_DUMMY_PACKET_LEN]; //数据缓存

	// float Current_CBR; //当前的CBR测量值
	//float Current_CRlimit; //当前满足CR limit要求的Max data rate建议值
	tExtenSionCommn_ST extension;
} __attribute__((packed)) tRcvInfo;

typedef struct stc_Queue
{
	tRcvInfo m_stcqueue[RECVQUEUE_MAXNUM];
	int32_t m_nQIndx_In;
	int32_t m_nQIndx_Out;
	sem_t m_blank_number;
	sem_t m_product_number;
} __attribute__((packed)) tQueue_RevLst;

#endif
