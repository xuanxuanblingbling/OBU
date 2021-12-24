/*
 * SecData.h
 *
 *  Created on: May 4, 2020
 *      Author: wanijv2x
 */

#ifndef SECLAYER_INC_SECDATA_H_
#define SECLAYER_INC_SECDATA_H_
#include <stdio.h>
#include <sys/times.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <fcntl.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <assert.h>
#include <inttypes.h>
#include <termios.h>

#include <sys/time.h> // for rate control
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <pthread.h>

#include <getopt.h>
#include <linux/if_ether.h>

#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/if_ether.h>
#include <netinet/tcp.h>
#include <linux/sockios.h>

#include <stdint.h>
#include <stdbool.h>
#include <sys/select.h>
#include <linux/filter.h>
#include <sys/msg.h>
#include <semaphore.h>
#include "SecLayer.h"

typedef unsigned char uint8_t;		 /* 无符号8位整型变量  */
typedef signed char int8_t;			 /* 有符号8位整型变量  */
typedef unsigned short uint16_t;	 /* 无符号16位整型变量 */
typedef signed short int16_t;		 /* 有符号16位整型变量 */
typedef unsigned int uint32_t;		 /* 无符号32位整型变量  */
typedef signed int int32_t;			 /* 有符号32位整型变量  */
// typedef unsigned long long uint64_t; /* 无符号64位整型变量  */
// typedef signed long long int64_t;	 /* 有符号64位整型变量  */
typedef float fp32;					 /* 单精度浮点数（32位长度）*/
typedef double fp64;				 /* 双精度浮点数（64位长度）*/




typedef uint32_t (*dll_SecChipFactoryCheck)();
typedef int32_t (*dll_SecChip_Init)(seclayer_status_callback cb, void *cb_para, const char *fileName);
typedef int32_t (*dll_SecDataSign_RSU)(uint64_t aid,
                                    uint8_t *pdu, int32_t pdu_size,
                                    uint8_t *spdu, int32_t *spdu_size);

typedef int32_t (*dll_SecDataSign_OBU)(uint64_t aid, int32_t emergency_event_flag,
                                  double longitude, double latitude,
                                  uint8_t *pdu, int32_t pdu_size, uint8_t *spdu, int32_t *spdu_size);


typedef int32_t (*dll_SecDataVerify)(uint8_t *spdu, int32_t spdu_size,
                                 uint8_t *pdu, int32_t *pdu_size,
                                 uint64_t *p_pu64AID);
typedef int32_t (*dll_SecChipDeinit)(void);


struct DLL_FUN_st
{
	dll_SecChipFactoryCheck			wj_SecChipFactoryCheck;
	dll_SecChip_Init 				wj_SecChip_Init;
	dll_SecDataSign_RSU 			wj_SecDataSign_RSU;
	dll_SecDataSign_OBU 			wj_SecDataSign_OBU;
	dll_SecDataVerify 				wj_SecDataVerify;
	dll_SecChipDeinit 				wj_SecChipDeinit;
}SECFUNTION;

uint32_t dllOpenInit(int32_t ProtocolType, int32_t ChipType, const char *FileName);
uint32_t dllOpenDeinit(); 

#endif /* SECLAYER_INC_SECDATA_H_ */
