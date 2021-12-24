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

typedef unsigned char uint8_t;		 /* 无符号8位整型变量  */
typedef signed char int8_t;			 /* 有符号8位整型变量  */
typedef unsigned short uint16_t;	 /* 无符号16位整型变量 */
typedef signed short int16_t;		 /* 有符号16位整型变量 */
typedef unsigned int uint32_t;		 /* 无符号32位整型变量  */
typedef signed int int32_t;			 /* 有符号32位整型变量  */
typedef unsigned long long uint64_t; /* 无符号64位整型变量  */
typedef signed long long int64_t;	 /* 有符号64位整型变量  */
typedef float fp32;					 /* 单精度浮点数（32位长度）*/
typedef double fp64;				 /* 双精度浮点数（64位长度）*/

#define MODE_SECMODE_AG15_HARD 1
#define MODE_SECMODE_AG15_SOFT 1
#define MODE_SECMODE_DMD31_DT 0

#if MODE_SECMODE_AG15_HARD | MODE_SECMODE_AG15_SOFT

#endif

/**
 * @brief 安全验证结果码.
 */
typedef enum SecurityResultCode
{
	SecurityResultCode_unknown = 0,							//未知
	SecurityResultCode_incorrectSecureMessageVersion = 1,	//安全消息版本号信息非法
	SecurityResultCode_incorrectSignerType = 2,				//签名者信息中签名方式非法
	SecurityResultCode_incorrectCertVersion = 3,			//数字证书版本号信息非法
	SecurityResultCode_incorrectCertIssueDigest = 4,		// 数字证书签发者信息非法
	SecurityResultCode_incorrectCertSubjectInfo = 5,		//数字证书中待签主题信息非法
	SecurityResultCode_incorrectCertSubjectAttribute = 6,	//数字证书中待签主题属性信息非法
	SecurityResultCode_incorrectCertValidityPeriod = 7,		//数字证书中有效限定信息非法
	SecurityResultCode_incorrectCertTimeStartAndEnd = 8,	//数字证书中有效时间信息非法
	SecurityResultCode_incorrectSubcertAuthority = 9,		//数字证书父子关系非法
	SecurityResultCode_incorrectCertChain = 10,				//证书链非法
	SecurityResultCode_incorrectCertSignature = 11,			//数字证书签名信息非法
	SecurityResultCode_incorrectTbsDataGenTime = 12,		//待签数据中数据产生时间信息非法
	SecurityResultCode_incorrectTbsDataHashAlg = 13,		// 待签数据中杂凑算法信息非法
	SecurityResultCode_incorrectTbsDataItsAid = 14,			//待签数据中 AID 信息非法
	SecurityResultCode_incorrectSignedMessageSignature = 15 //安全消息中签名信息非法
															/*
	 * Enumeration is extensible
	 */
} e_SecurityResultCode;

#endif /* SECLAYER_INC_SECDATA_H_ */
