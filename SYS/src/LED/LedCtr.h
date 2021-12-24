/***********************************************************************
 * 文 件 名 称 ： Supervison_interface.h
 * 功 能 描 述 ： 
 * 开 发 人 员 ： 
 * 日      期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-05-23 V1.0       Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
#ifndef ___LEDCTR_H__
#define ___LEDCTR_H__
/**********************  头文件包含  ********************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include "unistd.h"
#include <semaphore.h>


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

/********************** 宏定义 *************************************/
#define Cycle_LEDCtrData_Type 2u
#define SYS_Block_Index 0u
#define V2X_Block_Index 1u
#define GNSS_Block_Index 2u

#define Green_LED_Twinking 0u
#define Green_LED_Bright 1u
#define Red_LED_Bright 2u
#define Green_LED_FastTwinking 3u

#define TimerLock 1u
#define TimerUnlock 0u

#define TimerEnable 1u
#define TimerDisenable 0u

#define TwinkingCycleTime 500 //ms
#define FastTwinkingCycleTime 100 //ms


#define V2X_LED1      "v2x-led1/brightness"
#define V2X_LED2      "v2x-led2/brightness"
#define SYS_LED1      "sys-led1/brightness"
#define SYS_LED2      "sys-led2/brightness"
#define UPD_LED1      77
#define UPD_LED2      76
#define GNSS_LED1     "gnss-led1/brightness"
#define GNSS_LED2     "gnss-led2/brightness"

#define RetTure     0
#define RetErr      -1

#ifdef CROSSCOMPILE_8M
#define RHD_GPIO_SYSFS_DIR_High      "/sys/devices/platform/leds/leds"
#else
#define RHD_GPIO_SYSFS_DIR_High      "/sys/class/leds"
#endif

#define RHD_GPIO_SYSFS_DIR_Low      "/sys/class/gpio"

#define GPIO_High                   "1"
#define GPIO_Low                   "0"


/********************** 类型重定义 **********************************/

typedef struct _TimeCtrType{
    char* p_gisterName; 
    int p_n32RegisterLen;
    int p_n32RegisterClockTime;
    sem_t* p_ptSemId;
}TimeCtrType; 

typedef struct _TwinkingTimeCtrType{
	uint8 m_TwinkingIdex;
    uint8 m_TimerCtrState;
    int m_TimerCtrValue;
    int m_LEDCtrState;
    TimeCtrType TimeCtrData;   
}TwinkingTimeCtrType;

typedef enum _LEDNameType{
    SYSLED = 0,
    V2XLED,
    GNSSLED
}LEDNameType;

typedef enum _LEDCtrType{
    GreenLEDBright = 1,
    RedLEDBright,
    Dark
}LEDCtrType;

typedef struct
{
    uint8_t BlockIndex;
    uint8_t LEDState;
} __attribute__((packed)) LEDCtr;

extern LEDCtr LEDCtrCommand;  

/********************** 函数外部申明 ********************************/
extern void  LEDGpioInit();
extern int SYSLEDCtrProcess(uint8 LEDState ,int TwinkingTime);
extern int V2XLEDCtrProcess(uint8 LEDState ,int TwinkingTime);
extern int GNSSLEDCtrProcess(uint8 LEDState ,int TwinkingTime);


#endif /* ___LEDCTR_H__ */
