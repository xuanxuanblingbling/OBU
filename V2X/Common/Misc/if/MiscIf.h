/*********************************************************************
* 文 件 名 称   ：  MiscIf.h
* 功 能 描 述   ：  公共外部接口头文件
* 开 发 人 员   ：  黄赛
* 文 件 版 本   ：  V1.0
* 修 改 记 录   ：  修改描述            修改时间        修改人
                  创建文件            20200413       黄赛
********************************************************************/
#ifndef _MISC_INTERFACE_H_
#define _MISC_INTERFACE_H_
/**********************  头文件包含  ********************************/
#include <pthread.h>
#define ABSENT 0xAA
#define PRESENT 0xCC
#define ENCODE_ABSENT 0
#define ENCODE_PRESENT 1
/********************** 宏定义 *************************************/
#define IS_OK 0  /* 函数返回值  代表成功 */
#define IS_ERR 1 /* 函数返回值  代表失败 */
#define MAX_U8VALUE 0xFF                        /* 无符号8位的最大值 */
#define MAX_S8VALUE 0x7F                        /* 有符号8位的最大值 */
#define MAX_U16VALUE 0xFFFF                     /* 无符号16位的最大值 */
#define MAX_S16VALUE 0x7FFF                     /* 有符号16位的最大值 */
#define MAX_U32VALUE 0xFFFFFFFF                 /* 无符号32位的最大值 */
#define MAX_S32VALUE 0x7FFFFFFF                 /* 有符号32位的最大值 */
#define MAX_U64VALUE 0xFFFFFFFFFFFFFFFF         /* 无符号64位的最大值 */
#define MAX_S64VALUE 0x7FFFFFFFFFFFFFFF         /* 有符号64位的最大值 */
#define INT64_TO_NET(val)    ((uint64) ( \
      (((uint64) (val) &                        \
    (uint64) (0x00000000000000ffU)) << 56) |    \
      (((uint64) (val) &                        \
    (uint64) (0x000000000000ff00U)) << 40) |    \
      (((uint64) (val) &                        \
    (uint64) (0x0000000000ff0000U)) << 24) |    \
      (((uint64) (val) &                        \
    (uint64) (0x00000000ff000000U)) <<  8) |    \
      (((uint64) (val) &                        \
    (uint64) (0x000000ff00000000U)) >>  8) |    \
      (((uint64) (val) &                        \
    (uint64) (0x0000ff0000000000U)) >> 24) |    \
      (((uint64) (val) &                        \
    (uint64) (0x00ff000000000000U)) >> 40) |    \
      (((uint64) (val) &                        \
    (uint64) (0xff00000000000000U)) >> 56)))

/********************** 类型重定义 **********************************/
typedef unsigned char  uint8;     /* 无符号8位整型变量  */
typedef signed char  int8;      /* 有符号8位整型变量  */
typedef unsigned short  uint16;   /* 无符号16位整型变量 */
typedef short  int16;    /* 有符号16位整型变量 */
typedef unsigned int    uint32;   /* 无符号32位整型变量  */
typedef int    int32;    /* 有符号32位整型变量  */
typedef unsigned long long  uint64;    /* 无符号64位整型变量  */
typedef long long int64;     /* 有符号64位整型变量  */
typedef float           fp32;     /* 单精度浮点数（32位长度）*/
typedef double          fp64;     /* 双精度浮点数（64位长度）*/

typedef char *LPSTR;
typedef const char *LPCSTR;
typedef unsigned long  DWORD;
typedef int BOOL;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned char BYTE;

/* 线程锁 */
typedef struct _SendMsgMutex
{
    pthread_mutex_t m_tmutex;
    pthread_mutexattr_t m_tmutexattr;
}SendMsgMutex_t;
/********************** 函数外部申明 ********************************/
/**
 * @brief 获取当前时间的函数
 * @param[in] pu64TimeStamp    秒的格式时间.
 * @param[in] ps8YMDHMS        年月日时分秒的格式时间.
 * @return  无
 */
extern int Misc_GetCurTimeStamp(uint64 *p_pu64TimeStamp, int8* p_ps8YMDHMS);
/**
 * @brief 实现秒级定时的函数
 * @param[in] p_u64mSec    要定时的秒数.
 * @return  无
 */
extern void Misc_secondsleep(uint32 p_u32seconds);
/**
 * @brief 实现毫秒级定时的函数
 * @param[in] p_u64mSec    要定时的毫秒数.
 * @return  无
 */
extern void Misc_millisecondsleep(uint64 p_u64mSec);
/**
 * @brief 实现微秒级定时的函数
 * @param[in] p_u64uSec    要定时的微妙数.
 * @return  无
 */
extern void Misc_microsecondsleep(uint64 p_u64uSec);
#endif
