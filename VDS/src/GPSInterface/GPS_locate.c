#include "GPS_locate.h"
#include "./Include/wj_log.h"
//#define GPS_Config_Path  "/mnt/OBUAPP/Config/GPS_Config.ini"
#define GPS_Config_Path "/mnt/APP/Config/obu/vds/VDSCfg.json"
int RtcmFlag = 0;
int LocateSource = 0;
int latitude = 0;
int lontitude = 0;
int SpeedData = 0;
int HeadingData = 0;
int InitGPS()
{
	int nRet = 0;
	int  ConfigVal = 0;
	double ConfigVal1 = 0;
	if (!(GetConfigIntValue(GPS_Config_Path, "GNSS", "RtcmFlag", &ConfigVal)))
	{
		RtcmFlag = ConfigVal;
		LogPrint(LOG_LEVEL_NOTICE, "GPSInit", "GPS Model is: %d ",RtcmFlag);
	}
	else
	{
		LogPrint(LOG_LEVEL_ERR, "GPSInit", "GPS Config  File is error\n");
	}
	if (!(GetConfigIntValue(GPS_Config_Path, "GNSS", "Locationsource", &ConfigVal)))
	{
		LocateSource = ConfigVal;
		if(1 == LocateSource)
	    {
			if (!(GetConfigIntValue(GPS_Config_Path, "GNSS", "Latitude", &ConfigVal)))
			{
				latitude = ConfigVal;
			}
			if (!(GetConfigIntValue(GPS_Config_Path, "GNSS", "longtitude", &ConfigVal)))
			{
				lontitude = ConfigVal;
			}
			if (!(GetConfigIntValue(GPS_Config_Path, "GNSS", "Speed", &ConfigVal)))
			{
				SpeedData = ConfigVal;
			}
			if (!(GetConfigIntValue(GPS_Config_Path, "GNSS", "Heading", &ConfigVal)))
			{
				HeadingData = ConfigVal;
			}
		}
		LogPrint(LOG_LEVEL_NOTICE, "GPSInit", "GPS location source: %d  lat:%d  lon:%d  Speed :%d  Heading :%d",LocateSource,latitude,lontitude,SpeedData,HeadingData);
	}

	if(RtcmFlag == RTK_Model)
	{
		LogPrint(LOG_LEVEL_NOTICE, "GPSInit", "GPS Model is RTK\n");
		nRet = GPS_RTK_Open();
	}
	else
	{
		nRet = GPS_AG15_Open();
		LogPrint(LOG_LEVEL_NOTICE, "GPSInit", "GPS Model is AG15\n");
	}
	return nRet;
}

int GetGnssData(GpsLocation * fix)  //GpsLocation
{
	int ret = 0 ;
	if(RtcmFlag == RTK_Model)
	{
		ret = GPS_RTK_GetData(fix);
	}
	else
	{
		ret = GPS_Ag15_GetData(fix);
		
	}	
	return ret;
}


int CloseGPS()
{
	int nRet = 0;
	if(RtcmFlag == RTK_Model)
	{
		nRet = GPS_RTK_Close();
	}
	else 
	{
		nRet = GPS_AG15_Close();
	}
	return nRet;
}
