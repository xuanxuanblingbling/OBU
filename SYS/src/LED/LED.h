#ifndef  LED_H
#define  LED_H

#include "stdio.h"

#define  LEDINIT    			LEDinit

#ifdef __cplusplus   
extern "C" {
#endif


typedef unsigned char uint8_t;

extern void LEDinit(void);

extern void MsgM_Send_Fun(uint8_t *DataStruct, int StructLen, int index);

#ifdef __cplusplus   
}
#endif


////定义模块名称
#define NormalTimePeriod  30 //30S
#define  V2Xname     "V2XState"
#define  vdsname     "VdsState"
#define  V2XLEDP    2
#define  vdsLEDP    3
#define  SysLEDP    0

typedef enum {
    GREEN = 0,
    TWINKLE = 1,
    TWINKFAST,
    RED
}LedState;

#define GreenTime    0xFF       //绿灯持续点亮时间
#define RedTime      0xFF      //红灯点亮为永久点亮
#define TwinkTime    0x06      
#define NULL ((void *)0)

#define  CLOCKACTIVE   0
#define  CLOCKEXPIRED  1
#define  CLOCKOFF     0xFFFFFFFF
typedef unsigned char  uint8;     /* 无符号8位整型变量  */
#define InvalidLedCtrData   0xFF

typedef struct _LEDCtalgrcv{
    uint8 m_u8BlockIndex;  
    uint8 LEDState;  
}LEDCtalgrcv;

typedef struct _timest{
        int starttime;
        int period;
        int expirflag;
 }TimeSt;


/********************/
int LEDStateSet(char *modulename , LedState state);

#endif

