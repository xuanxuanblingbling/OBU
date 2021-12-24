#include <sys/time.h>
#include "LED.h"
#include "string.h"
#include "unistd.h"
#include <sys/types.h>
#include "stddef.h"
#include "pthread.h"
#include "wj_log.h"
#include "LedCtr.h"


TimeSt  ClockLedV2X;     //V2X定时关必小灯模块计时器
TimeSt  ClockLedvds;

pthread_mutex_t  gClockV2X_Mutex;
pthread_mutex_t  gClockvds_Mutex;
//pthread_mutex_lock(&gNetCfg_Json_Mutex)
//pthread_mutex_unlock(&gNetCfg_Json_Mutex)
__uint8_t BlockLEDState[3] = {Green_LED_Bright,Green_LED_Bright,Green_LED_Bright};
/**************************
 * @name: SetCloctimer(char *TimeName, int Tim)
 * @bref: set Clock a determine time
 * @input: TimeName: the modulename vds V2X .etc
 *         Tim : the time LED be acived for
 * @output: NO
 * @return: 0 function exc success !0 function exc Error
 * ===============================
 * Copyright (C) 2020 by wanji
 * author: CBS  20201221
******/
__uint8_t SetCloctimer(char *ClockName, int Tim)
{
    struct  timeval tv;

    if((0 == Tim)|| (NULL == ClockName))
    {
        return 1;
    }
    
    if(0 !=  gettimeofday(&tv,NULL))
    {
        return 1;
    }

    if( !strcmp(V2Xname, ClockName))
    {
        ClockLedV2X.starttime = tv.tv_sec;
        // LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "Current V2X Timer is : %d",ClockLedV2X.starttime);
    }
    else if( !strcmp(vdsname, ClockName)) 
    {
        ClockLedvds.starttime =  tv.tv_sec;
        // LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "Current GNSS Timer is : %d",ClockLedvds.starttime);
    }
    else
    {
        return 1;
    }

    return 0;  
}
/**************************
 * @name: __uint8_t CheckCloctimer(char *ClockName)
 * @bref:  check the clock time 
 * @input: ClockName: the modulename vds V2X .etc
 * @output: NO
 * @return: 0 function exc success !0 function exc Error
 * ===============================
 * Copyright (C) 2020 by wanji
 * author: CBS  20201221
******/
__uint8_t CheckCloctimer(void)
{
    struct  timeval tv;
    static long int InitTimer = 0 ;
    static int Count = 0 ;
    static int V2XLedRedState = 0 ;
    static int GNSSLedRedState = 0 ;
    if(0 !=  gettimeofday(&tv,NULL))
    {
        return 1;
    }
    if (Count == 0)
    {
        InitTimer = tv.tv_sec ;
        Count++;
    }
    if(((tv.tv_sec - ClockLedV2X.starttime) > NormalTimePeriod)&&((tv.tv_sec - InitTimer) > NormalTimePeriod))
    {
        BlockLEDState[V2X_Block_Index] = Red_LED_Bright;
        V2XLedRedState = 1;

    }
    else
    {
        /* code */
    }  
    if(((tv.tv_sec - ClockLedvds.starttime) > NormalTimePeriod)&&((tv.tv_sec - InitTimer) > NormalTimePeriod))
    {
        
        BlockLEDState[GNSS_Block_Index] = Red_LED_Bright;
        GNSSLedRedState = 1;  
    }
    else 
    {
        /* code */
    }
    return 0;

}

/**************************
 * @name: LEDPinControl(int pin, int color,int time);
 * @bref: set th LED state indate the system run state
 * @input: pin: the modulename vds V2X .etc
 *         color:  normal, fault
 *         time : the time LED be acived for
 * @output: NO
 * @return: 0 function exc success !0 function exc Error
 * ===============================
 * Copyright (C) 2020 by wanji
 * author: CBS  20201221
**/
int LEDControl(int LEDid, __uint8_t color)
{

   if (LEDid == V2XLEDP)
   {
        BlockLEDState[V2X_Block_Index] = color ;
        // LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "Ctr V2X LED State is :%d ",color);
       /** 设置V2X灯为指定颜色   红  绿  闪**/
   }
   else  if(LEDid == vdsLEDP)
   {
        BlockLEDState[GNSS_Block_Index] = color ;
        // LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "Ctr GNSS LED State is :%d ",color);
       /** 设置VDS灯为指定颜色   红  绿  闪**/
   }
   else
   {
       
   }  
}
/**************************
 * @name: LEDStateSet(char *modulename , int state)
 * @bref: set th LED state indate the system run state
 * @input: modulename: the modulename vds V2X .etc
 *         state:  normal, fault
 * @output: NO
 * @return: 0 function exc success !0 function exc Error
 * ===============================
 * Copyright (C) 2020 by wanji
 * author: CBS  20201221
******/
int LEDStateSet(char *modulename , LedState state)
{
    int PeriodTim = 0;
    int LEDid = 0xFF;
    int lEDstate = 0xFF;
    // LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "parameter modulename is   %s  %d ",modulename,state);
    
    if(modulename == NULL)
    {
        return 0;
    }
    
    if (!strcmp(V2Xname, modulename))
    {
       LEDid = V2XLEDP;
    }
    else if(!strcmp(vdsname, modulename))
    {
       LEDid = vdsLEDP;
    }
    else{
        //printf(" [%s] [%s] [%d] : parameter modulename is ERROR  %s  \n",__FILE__, __func__,__LINE__,modulename);
        LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "parameter modulename is ERROR  %s  ",modulename);
    }

    if (GREEN == state)
    {
        lEDstate = Green_LED_Bright;
        PeriodTim = RedTime;
    }
    else if(state == RED)
    {
        lEDstate = Red_LED_Bright;
        PeriodTim = RedTime;       
    }
    else if(TWINKLE == state)
    {
        lEDstate = Green_LED_Twinking;
        PeriodTim = TwinkTime;
        
    }
    else if(TWINKFAST == state)
    {
        lEDstate = Green_LED_FastTwinking;
        PeriodTim = TwinkTime;
        
    }
    else 
    {
         LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "parameter modulename is ERROR  %d  ",state);
    }
    SetCloctimer(modulename, PeriodTim);
    LEDControl(LEDid,lEDstate);          // 第三个参数需要调整
}
/**************************
 * @name: LEDstatusMonitorProcess(void)
 * @bref: set th LED state indate the system run state
 * @input: modulename: the modulename vds V2X .etc
 *         state:  normal, fault
 * @output: NO
 * @return: NO 
 * ===============================
 * Copyright (C) 2020 by wanji
 * author: CBS  20201221
******/ 
int LEDCtrProcess(__uint8_t *CurrentLedState)
{
    int ret = 0;
	int id = 0;
    static uint8 SYS_LED_State = Green_LED_Bright;
	static uint8 V2X_LED_State = Green_LED_Bright;
	static uint8 GNSS_LED_State = Green_LED_Bright;
	TwinkingTimeCtrType SYSTwinkCtr,GNSSTwinkCtr,V2XTwinkCtr;	
	SYS_LED_State = CurrentLedState[SYS_Block_Index];
	V2X_LED_State = CurrentLedState[V2X_Block_Index];
	GNSS_LED_State = CurrentLedState[GNSS_Block_Index];
	ret = GNSSLEDCtrProcess(GNSS_LED_State,TwinkingCycleTime/100);
	if(0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Process Failed:%d\n",ret);
        return RetErr;
    }
	
	ret = V2XLEDCtrProcess(V2X_LED_State,TwinkingCycleTime/100);
	if(0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Process Failed:%d\n",ret);
        return RetErr;
    }
	ret = SYSLEDCtrProcess(SYS_LED_State,TwinkingCycleTime/100);
	if(0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Process Failed:%d\n",ret);
        return RetErr;
    }
    return RetTure ;
}

/**************************
 * @name: LEDstatusMonitorProcess(void)
 * @bref: set th LED state indate the system run state
 * @input: modulename: the modulename vds V2X .etc
 *         state:  normal, fault
 * @output: NO
 * @return: NO 
 * ===============================
 * Copyright (C) 2020 by wanji
 * author: CBS  20201221
******/
void  LEDstatusMonitorProcess(void)
{
   while(1)
   {
        CheckCloctimer();    
        // if(CLOCKEXPIRED == ClockLedV2X.expirflag)
        // {
        //     ClockLedV2X.expirflag = CLOCKOFF;
        //     //printf("====[test][LED]  SET V2X led off ==\n");
        //     LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, " SET V2X led off  ");
        //     LEDControl(V2XLEDP, GREEN);
        // }

        // if(CLOCKEXPIRED == ClockLedvds.expirflag)
        // {
        //     ClockLedvds.expirflag = CLOCKOFF;
        //     //printf("====[test][LED]  SET vds led off ==\n");
        //     LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, " SET V2X led off ");
        //     LEDControl(vdsLEDP, GREEN);
        // }
        // LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "Ctr LED State is :%d,%d ",BlockLEDState.m_u8BlockIndex,BlockLEDState.LEDState);
        LEDCtrProcess(&BlockLEDState[0]) ;
		usleep(100000);
   }
   
}
/**************************
 * @name: LEDinit(void)
 * @bref: init LED struct and thread
 * @input: NO
 * @output: NO
 * @return: NO
 * ===============================
 * Copyright (C) 2020 by wanji
 * author: CBS  20201221
******/
void LEDinit(void)
{
    pthread_t LEDstateMontorid = 0;
    int ret = 0;
	uint8 SYS_LED_State = Green_LED_Bright;
	uint8 V2X_LED_State = Green_LED_Bright;
	uint8 GNSS_LED_State = Green_LED_Bright;
    ClockLedV2X.expirflag = CLOCKOFF;
    ClockLedvds.expirflag = CLOCKOFF;
	LEDGpioInit();
	ret = FT_ClockTimeInit();
    if(0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr ClockTime Init Failed\n");
        return RetErr;
    }
    else
    {
        //do nothing
    }
	GNSSLEDCtrProcess(GNSS_LED_State,TwinkingCycleTime/100);
	V2XLEDCtrProcess(V2X_LED_State,TwinkingCycleTime/100);
	SYSLEDCtrProcess(SYS_LED_State,TwinkingCycleTime/100);
    
    pthread_create(&LEDstateMontorid,NULL,LEDstatusMonitorProcess,NULL);

    pthread_detach(LEDstateMontorid);
}