//#include "RdWrIni.h"
#include <stdio.h>
#include <unistd.h>  
#include <dlfcn.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "LedCtr.h"
#include "ClockTimeIf.h"
#include <string.h>
#include "wj_log.h"
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
/***********************************************************************
* 函 数 名 称 ： LEDGpioInit
* 功 能 描 述 ： LED GPIO Init
* 输 入 参 数 ：     
* 输 出 参 数 ： 
* 返  回  值  : 成功/失败
* 开 发 人 员 ： xinchuang.xing
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-04 V1.0    xinchuang.xing   Create
***********************************************************************/

void  LEDGpioInit()
{
	/*char s[50] = " ";
	//GNSS LED1 Init
	sprintf(s, "echo %d > /sys/class/gpio/export", GNSS_LED1);
	system(s);
	sprintf(s, "echo out > /sys/class/gpio/gpio%d/direction", GNSS_LED1);
	system(s);
	//GNSS LED2 Init
	sprintf(s, "echo %d > /sys/class/gpio/export", GNSS_LED2);
	system(s);
	sprintf(s, "echo out > /sys/class/gpio/gpio%d/direction", GNSS_LED2);
	system(s);
	//SYS LED1 Init
	sprintf(s, "echo %d > /sys/class/gpio/export", SYS_LED1);
	system(s);
	sprintf(s, "echo out > /sys/class/gpio/gpio%d/direction", SYS_LED1);
	system(s);	
	//SYS LED2 Init
	sprintf(s, "echo %d > /sys/class/gpio/export", SYS_LED2);
	system(s);
	sprintf(s, "echo out > /sys/class/gpio/gpio%d/direction", SYS_LED2);
	system(s);
	//UPD LED1 Init
	sprintf(s, "echo %d > /sys/class/gpio/export", UPD_LED1);
	system(s);
	sprintf(s, "echo out > /sys/class/gpio/gpio%d/direction", UPD_LED1);
	system(s);
	//UPD LED2 Init
	sprintf(s, "echo %d > /sys/class/gpio/export", UPD_LED2);
	system(s);
	sprintf(s, "echo out > /sys/class/gpio/gpio%d/direction", UPD_LED2);
	system(s);
	//V2X LED1 Init
	sprintf(s, "echo %d > /sys/class/gpio/export", V2X_LED1);
	system(s);
	sprintf(s, "echo out > /sys/class/gpio/gpio%d/direction", V2X_LED1);
	system(s);
	//V2X LED2 Init
	sprintf(s, "echo %d > /sys/class/gpio/export", V2X_LED2);
	system(s);
	sprintf(s, "echo out > /sys/class/gpio/gpio%d/direction", V2X_LED2);
	system(s);	*/
}
/***********************************************************************
* 函 数 名 称 ： LEDGpioValueCtr
* 功 能 描 述 ： 写入LED状态值
* 输 入 参 数 ： GpioIndex，value
* 输 出 参 数 ： 
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： xinchuang.xing
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-04 V1.0    xinchuang.xing   Create
***********************************************************************/
static int LEDGpioValueCtr(char *GpioIndex,char* value)
{
	int ret = 0; 
	char buf[100] = " ";
	int fd = 0;
	snprintf(buf, sizeof(buf), RHD_GPIO_SYSFS_DIR_High"/%s", GpioIndex);
	fd = open(buf, O_RDWR);
	if(fd == RetErr)
	{
        LogPrint(LOG_LEVEL_ERR, "LEDCtr", "Open Gpio File Failed %s\n",GpioIndex);
		return RetErr;
	}
	ret = write(fd, value, sizeof(value));
	if(ret == RetErr)
	{
        LogPrint(LOG_LEVEL_ERR, "LEDCtr", "Write Gpio File Failed %s\n",GpioIndex);
		return RetErr;
	}
	ret = close(fd);
	if(ret == RetErr)
	{
        LogPrint(LOG_LEVEL_ERR, "LEDCtr", "Close Gpio File Failed %s\n",GpioIndex);
		return RetErr;
	}	
	 return RetTure;
}
/***********************************************************************
* 函 数 名 称 ： LEDGpioCtr
* 功 能 描 述 ： LED状态执行控制
* 输 入 参 数 ： LEDName，LEDCtr
* 输 出 参 数 ： 
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： xinchuang.xing
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-04 V1.0    xinchuang.xing   Create
***********************************************************************/
static int LEDGpioCtr(LEDNameType LEDName,LEDCtrType LEDCtr)
{
	int ret = 0; 
	int fd = 0; 
	char s[50] = " ";
	char buf[50] = " ";

#ifdef CROSSCOMPILE_8M
	switch(LEDName)
	{
		case SYSLED:
			if(LEDCtr == RedLEDBright)
			{
				ret = LEDGpioValueCtr(SYS_LED1,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Green Failed:%d\n",SYS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(SYS_LED2,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Green Failed:%d\n",SYS_LED2);
        			return RetErr;
    			}	
			}
			else if(LEDCtr == GreenLEDBright)
			{
				ret = LEDGpioValueCtr(SYS_LED1,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Red Failed:%d\n",SYS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(SYS_LED2,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Red Failed:%d\n",SYS_LED2);
        			return RetErr;
    			}					

			}
			else if(LEDCtr == Dark)
			{
				ret = LEDGpioValueCtr(SYS_LED1,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Dark Failed:%d\n",SYS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(SYS_LED2,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Dark Failed:%d\n",SYS_LED2);
        			return RetErr;
    			}					
			}
			else 
			{
				
				LogPrint(LOG_LEVEL_ERR, "LEDCtr", "Invaild Led command Stype\n");
				return RetErr;
			}
		    break; 
		case V2XLED:
			if(LEDCtr == RedLEDBright)
			{
				ret = LEDGpioValueCtr(V2X_LED1,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Green Failed:%d\n",V2X_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(V2X_LED2,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Green Failed:%d\n",V2X_LED2);
        			return RetErr;
    			}			
			}
			else if(LEDCtr == GreenLEDBright)
			{
				ret = LEDGpioValueCtr(V2X_LED1,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Red Failed:%d\n",V2X_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(V2X_LED2,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Red Failed:%d\n",V2X_LED2);
        			return RetErr;
    			}					
			}
			else if(LEDCtr == Dark)
			{
				ret = LEDGpioValueCtr(V2X_LED1,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Dark Failed:%d\n",V2X_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(V2X_LED2,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Dark Failed:%d\n",V2X_LED2);
        			return RetErr;
    			}					
			}
			else 
			{
				LogPrint(LOG_LEVEL_ERR, "LEDCtr", "Invaild Led command Stype\n");
				return RetErr;
			}
			break;

		case GNSSLED:
			if(LEDCtr == RedLEDBright)
			{
				ret = LEDGpioValueCtr(GNSS_LED1,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Green Failed:%d\n",GNSS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(GNSS_LED2,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Green Failed:%d\n",GNSS_LED2);
        			return RetErr;
    			}	
			}
			else if(LEDCtr == GreenLEDBright)
			{
				ret = LEDGpioValueCtr(GNSS_LED1,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Red Failed:%d\n",GNSS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(GNSS_LED2,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Red Failed:%d\n",GNSS_LED2);
        			return RetErr;
    			}					
			}
			else if(LEDCtr == Dark)
			{
				ret = LEDGpioValueCtr(GNSS_LED1,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Dark Failed:%d\n",GNSS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(GNSS_LED2,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Dark Failed:%d\n",GNSS_LED2);
        			return RetErr;
    			}	
			}
			else 
			{
				LogPrint(LOG_LEVEL_ERR, "LEDCtr", "Invaild Led command Stype\n");
				return RetErr;
			}
		    break;
		default: return RetErr;break;									
	}
#else
	switch(LEDName)
	{
		case SYSLED:
			if(LEDCtr == RedLEDBright)
			{
				ret = LEDGpioValueCtr(SYS_LED1,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Green Failed:%d\n",SYS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(SYS_LED2,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Green Failed:%d\n",SYS_LED2);
        			return RetErr;
    			}	
			}
			else if(LEDCtr == GreenLEDBright)
			{
				ret = LEDGpioValueCtr(SYS_LED1,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Red Failed:%d\n",SYS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(SYS_LED2,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Red Failed:%d\n",SYS_LED2);
        			return RetErr;
    			}					

			}
			else if(LEDCtr == Dark)
			{
				ret = LEDGpioValueCtr(SYS_LED1,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Dark Failed:%d\n",SYS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(SYS_LED2,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS LED Control Dark Failed:%d\n",SYS_LED2);
        			return RetErr;
    			}					
			}
			else 
			{
				
				LogPrint(LOG_LEVEL_ERR, "LEDCtr", "Invaild Led command Stype\n");
				return RetErr;
			}
		    break; 
		case V2XLED:
			if(LEDCtr == RedLEDBright)
			{
				ret = LEDGpioValueCtr(V2X_LED1,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Green Failed:%d\n",V2X_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(V2X_LED2,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Green Failed:%d\n",V2X_LED2);
        			return RetErr;
    			}			
			}
			else if(LEDCtr == GreenLEDBright)
			{
				ret = LEDGpioValueCtr(V2X_LED1,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Red Failed:%d\n",V2X_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(V2X_LED2,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Red Failed:%d\n",V2X_LED2);
        			return RetErr;
    			}					
			}
			else if(LEDCtr == Dark)
			{
				ret = LEDGpioValueCtr(V2X_LED1,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Dark Failed:%d\n",V2X_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(V2X_LED2,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X LED Control Dark Failed:%d\n",V2X_LED2);
        			return RetErr;
    			}					
			}
			else 
			{
				LogPrint(LOG_LEVEL_ERR, "LEDCtr", "Invaild Led command Stype\n");
				return RetErr;
			}
			break;

		case GNSSLED:
			if(LEDCtr == RedLEDBright)
			{
				ret = LEDGpioValueCtr(GNSS_LED1,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Green Failed:%d\n",GNSS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(GNSS_LED2,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Green Failed:%d\n",GNSS_LED2);
        			return RetErr;
    			}	
			}
			else if(LEDCtr == GreenLEDBright)
			{
				ret = LEDGpioValueCtr(GNSS_LED1,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Red Failed:%d\n",GNSS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(GNSS_LED2,GPIO_High);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Red Failed:%d\n",GNSS_LED2);
        			return RetErr;
    			}					
			}
			else if(LEDCtr == Dark)
			{
				ret = LEDGpioValueCtr(GNSS_LED1,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Dark Failed:%d\n",GNSS_LED1);
        			return RetErr;
    			}
				ret = LEDGpioValueCtr(GNSS_LED2,GPIO_Low);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS LED Control Dark Failed:%d\n",GNSS_LED2);
        			return RetErr;
    			}	
			}
			else 
			{
				LogPrint(LOG_LEVEL_ERR, "LEDCtr", "Invaild Led command Stype\n");
				return RetErr;
			}
		    break;
		default: return RetErr;break;									
	}
	
#endif
	return RetTure;
}
/***********************************************************************
* 函 数 名 称 ： TwinkingTimeCtrProcess
* 功 能 描 述 ： LED 闪烁定时周期非阻塞执行
* 输 入 参 数 ： TwinkCtrData
* 输 出 参 数 ： 
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： xinchuang.xing
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-04 V1.0    xinchuang.xing   Create
***********************************************************************/

static int TwinkingTimeCtrProcess(TwinkingTimeCtrType* TwinkCtrData)
{
	int ret = 0; 
	if(TwinkCtrData->m_TimerCtrState == TimerUnlock)
	{
		ret = FT_ClockTimeRegister(TwinkCtrData->TimeCtrData.p_gisterName, TwinkCtrData->TimeCtrData.p_n32RegisterLen,
	TwinkCtrData->TimeCtrData.p_n32RegisterClockTime, &(TwinkCtrData->TimeCtrData.p_ptSemId));
		if(0 != ret)
    	{
        	LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr ClockTime Registe Failed\n");
        	return RetErr;
    	}
		TwinkCtrData->m_TimerCtrState = TimerLock;
	}
	else
	{
		ret = sem_getvalue(TwinkCtrData->TimeCtrData.p_ptSemId,&(TwinkCtrData->m_TimerCtrValue));
		if(0 != ret)
    	{
        	LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr  Get ClockTime Value Failed\n");
        	return RetErr;
    	}
		else
		{
			/* code */
		}

		if((TwinkCtrData->m_TimerCtrValue) == TimerEnable)
		{
			if(TwinkCtrData->m_LEDCtrState == GreenLEDBright)
			{
				ret = LEDGpioCtr(TwinkCtrData->m_TwinkingIdex,Dark);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr  Twink Ctr Failed\n");
        			return RetErr;
    			}				
				TwinkCtrData->m_LEDCtrState = Dark;				 
			}
			else if(TwinkCtrData->m_LEDCtrState == Dark)
			{
				ret = LEDGpioCtr(TwinkCtrData->m_TwinkingIdex,GreenLEDBright);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr  Twink Ctr Failed\n");
        			return RetErr;
    			}					
				TwinkCtrData->m_LEDCtrState = GreenLEDBright;			
			}
			else
			{
				ret = LEDGpioCtr(TwinkCtrData->m_TwinkingIdex,Dark);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr  Twink Ctr Failed\n");
        			return RetErr;
    			}					
				TwinkCtrData->m_LEDCtrState = Dark;				
			}			
			ret = sem_trywait(TwinkCtrData->TimeCtrData.p_ptSemId);
			if(0 != ret)
    		{
        		LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr  Realse ClockTime Semaphore Failed\n");
        		return RetErr;
    		}
			else
			{
				//do nothing
			}
		}	
		else
		{
			//wating ClockTime Semaphore
		}		
	}
    return 0;
}

/***********************************************************************
* 函 数 名 称 ： LEDTwinkTimerRealse
* 功 能 描 述 ： LED 闪烁定时器释放资源
* 输 入 参 数 ：     TwinkCtrData
* 输 出 参 数 ： 
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： xinchuang.xing
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-04 V1.0    xinchuang.xing   Create
***********************************************************************/
static int LEDTwinkTimerRealse(TwinkingTimeCtrType* TwinkCtrData)
{
	int ret = 0;
	if(	TwinkCtrData->m_TimerCtrState == TimerLock)
	{
		ret = FT_ClockTimeRegister(TwinkCtrData->TimeCtrData.p_gisterName, TwinkCtrData->TimeCtrData.p_n32RegisterLen,
									UNREGISTERFLAG, &(TwinkCtrData->TimeCtrData.p_ptSemId));
		if(0 != ret)
    	{
        	LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr Timer Realse Failed %d\n",TwinkCtrData->m_TwinkingIdex);
        	return RetErr;
   		}
		TwinkCtrData->m_TimerCtrState =	TimerUnlock;
	}
	else 
	{
		//do nothing
	}
	return 0;	
}
/***********************************************************************
* 函 数 名 称 ： SYSLEDCtrProcess
* 功 能 描 述 ： 子模块LED状态实现
* 输 入 参 数 ： LEDState，TwinkingTime
* 输 出 参 数 ： 
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： xinchuang.xing
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-04 V1.0    xinchuang.xing   Create
***********************************************************************/
int SYSLEDCtrProcess(uint8 LEDState ,int TwinkingTime)
{
	static TwinkingTimeCtrType SYSTwinkCtrData;
	int ret = 0;
	SYSTwinkCtrData.m_TwinkingIdex = SYS_Block_Index;
	switch(LEDState)
	{
		case Green_LED_Twinking:
			if(SYSTwinkCtrData.m_TimerCtrState == TimerUnlock)
			{
				SYSTwinkCtrData.TimeCtrData.p_gisterName = "SYSLEDTwinkingTime";
				SYSTwinkCtrData.TimeCtrData.p_n32RegisterLen = strlen("SYSLEDTwinkingTime");
				SYSTwinkCtrData.TimeCtrData.p_n32RegisterClockTime = TwinkingTime;	
			}
			else
			{
				//do nothing
			}			 
			ret = TwinkingTimeCtrProcess(&SYSTwinkCtrData);
			if(0 != ret)
    		{
        		LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS Twinking Process Failed\n");
        		return RetErr;
    		}
			else
			{
				/* code */
			}
		break;
		case Green_LED_Bright:
			if(SYSTwinkCtrData.m_LEDCtrState != GreenLEDBright)
			{
				LEDGpioCtr(SYSLED,GreenLEDBright);
				SYSTwinkCtrData.m_LEDCtrState = GreenLEDBright;
				LogPrint(LOG_LEVEL_NOTICE, "LEDCtr", "LEDCtr SYS LED Turn Green\n");
			}
			else
			{
				//do nothing
			}		
			ret = LEDTwinkTimerRealse(&SYSTwinkCtrData);
			if(0 != ret)
    		{
        		LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS Twinking Timer Realse Failed\n");
        		return RetErr;
    		}
			break;
		case Red_LED_Bright:
			if(SYSTwinkCtrData.m_LEDCtrState != RedLEDBright)
			{
				LEDGpioCtr(SYSLED,RedLEDBright);
				SYSTwinkCtrData.m_LEDCtrState = RedLEDBright;
				LogPrint(LOG_LEVEL_NOTICE, "LEDCtr", "LEDCtr SYS LED Turn Red\n");
			}
			else
			{
				//do nothing
			}			 
			LEDTwinkTimerRealse(&SYSTwinkCtrData);
			if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr SYS Twinking Timer Realse Failed\n");
        			return RetErr;
    			}				
			break;
 		default: break;			
	}
	return 0;
}
/***********************************************************************
* 函 数 名 称 ： V2XLEDCtrProcess
* 功 能 描 述 ： 子模块LED状态实现
* 输 入 参 数 ： LEDState，TwinkingTime
* 输 出 参 数 ： 
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： xinchuang.xing
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-04 V1.0    xinchuang.xing   Create
***********************************************************************/
int V2XLEDCtrProcess(uint8 LEDState ,int TwinkingTime)
{
	static TwinkingTimeCtrType V2XTwinkCtrData;
	int ret = 0;
	V2XTwinkCtrData.m_TwinkingIdex = V2X_Block_Index;
	switch(LEDState)
	{
		case Green_LED_Twinking:
			if(V2XTwinkCtrData.m_TimerCtrState == TimerUnlock)
			{
				V2XTwinkCtrData.TimeCtrData.p_gisterName = "V2XLEDTwinkingTime";
				V2XTwinkCtrData.TimeCtrData.p_n32RegisterLen = strlen("V2XLEDTwinkingTime");
				V2XTwinkCtrData.TimeCtrData.p_n32RegisterClockTime = TwinkingTime;	
			}
			else
			{
				//do nothing
			}			 
			ret = TwinkingTimeCtrProcess(&V2XTwinkCtrData);
			if(0 != ret)
    		{
        		LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X Twinking Process Failed\n");
        		return RetErr;
    		}
			else
			{
				//do nothing
			}
			break;
		case Green_LED_Bright:
			if(V2XTwinkCtrData.m_LEDCtrState != GreenLEDBright)
			{
				LEDGpioCtr(V2XLED,GreenLEDBright);
				V2XTwinkCtrData.m_LEDCtrState = GreenLEDBright;
				LogPrint(LOG_LEVEL_NOTICE, "LEDCtr", "LEDCtr V2X LED Turn Green\n");
			}
			else
			{
				//do nothing
			}			
			ret = LEDTwinkTimerRealse(&V2XTwinkCtrData);
			if(0 != ret)
    		{
        		LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X Twinking Timer Realse Failed\n");
        		return RetErr;
    		}					
			break;
		case Red_LED_Bright:
			if(V2XTwinkCtrData.m_LEDCtrState != RedLEDBright)
			{
			 	LEDGpioCtr(V2XLED,RedLEDBright); 
				V2XTwinkCtrData.m_LEDCtrState = RedLEDBright;
				LogPrint(LOG_LEVEL_NOTICE, "LEDCtr", "LEDCtr V2X LED Turn Red\n");
			}
			else
			{
				//do nothing
			}	
			ret = LEDTwinkTimerRealse(&V2XTwinkCtrData);
			if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr V2X Twinking Timer Realse Failed\n");
        			return RetErr;
    			}					
			break;
 		default: break;			
	}
	return 0;
}
/***********************************************************************
* 函 数 名 称 ： GNSSLEDCtrProcess
* 功 能 描 述 ： 子模块LED状态实现
* 输 入 参 数 ： LEDState，TwinkingTime
* 输 出 参 数 ： 
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： xinchuang.xing
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-04 V1.0    xinchuang.xing   Create
***********************************************************************/
int GNSSLEDCtrProcess(uint8 LEDState ,int TwinkingTime)
{
	static TwinkingTimeCtrType GNSSTwinkCtrData;
	static int TwinkingSwitch = 0;
	GNSSTwinkCtrData.m_TwinkingIdex = GNSS_Block_Index;
	int ret = 0;
	switch(LEDState)
	{
		case Green_LED_Twinking:
			if(TwinkingSwitch ==2)
			{
				ret = LEDTwinkTimerRealse(&GNSSTwinkCtrData);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS Twinking Timer Realse Failed\n");
        			return RetErr;
    			}					
			}
			if(GNSSTwinkCtrData.m_TimerCtrState == TimerUnlock)
			{
				GNSSTwinkCtrData.TimeCtrData.p_gisterName = "GNSSLEDTwinkingTime";
				GNSSTwinkCtrData.TimeCtrData.p_n32RegisterLen = strlen("GNSSLEDTwinkingTime");
				GNSSTwinkCtrData.TimeCtrData.p_n32RegisterClockTime = TwinkingTime;
				TwinkingSwitch = 1;	
			}
			else
			{
				//do nothing
			}			 
			ret = TwinkingTimeCtrProcess(&GNSSTwinkCtrData);
			if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS Twinking Process Failed\n");
        			return RetErr;
    			}
			else
			{
				/* code */
			}
			break;
		case Green_LED_FastTwinking:
			if(TwinkingSwitch ==1)
			{
				ret = LEDTwinkTimerRealse(&GNSSTwinkCtrData);
				if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS Twinking Timer Realse Failed\n");
        			return RetErr;
    			}					
			}
			if(GNSSTwinkCtrData.m_TimerCtrState == TimerUnlock)
			{
				GNSSTwinkCtrData.TimeCtrData.p_gisterName = "GNSSLEDFTwinkingTime";
				GNSSTwinkCtrData.TimeCtrData.p_n32RegisterLen = strlen("GNSSLEDFTwinkingTime");
				GNSSTwinkCtrData.TimeCtrData.p_n32RegisterClockTime = FastTwinkingCycleTime/100;
				TwinkingSwitch = 2;	
        		LogPrint(LOG_LEVEL_NOTICE, "LEDCtr", "LEDCtr GNSS FastTwinking Process \n");
			}
			else
			{
				//do nothing
			}			 
			ret = TwinkingTimeCtrProcess(&GNSSTwinkCtrData);
			if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS Twinking Process Failed\n");
        			return RetErr;
    			}
			else
			{
				/* code */
			}
			break;
		case Green_LED_Bright:
			if(GNSSTwinkCtrData.m_LEDCtrState != GreenLEDBright)
			{
				TwinkingSwitch = 0;		
				LEDGpioCtr(GNSSLED,GreenLEDBright);
				GNSSTwinkCtrData.m_LEDCtrState = GreenLEDBright;
				LogPrint(LOG_LEVEL_NOTICE, "LEDCtr", "LEDCtr GNSS LED Turn Green\n");
			}
			else
			{
				//do nothing
			}	
			ret = LEDTwinkTimerRealse(&GNSSTwinkCtrData);
			if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS Twinking Timer Realse Failed\n");
        			return RetErr;
    			}					
			break;
		case Red_LED_Bright:
			if(GNSSTwinkCtrData.m_LEDCtrState != RedLEDBright)
			{
				TwinkingSwitch = 0;
			 	LEDGpioCtr(GNSSLED,RedLEDBright); 
				GNSSTwinkCtrData.m_LEDCtrState = RedLEDBright;
				LogPrint(LOG_LEVEL_NOTICE, "LEDCtr", "LEDCtr GNSS LED Turn Red\n");
			}
			else
			{
				//do nothing
			}
			ret = LEDTwinkTimerRealse(&GNSSTwinkCtrData);
			if(0 != ret)
    			{
        			LogPrint(LOG_LEVEL_ERR, "LEDCtr", "LEDCtr GNSS Twinking Timer Realse Failed\n");
        			return RetErr;
    			}					
			break;
 		default: break;			
	}
	return 0;
}

