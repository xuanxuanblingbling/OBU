/*
 * Main.c
 * Created on: May 25, 2018
 * Author: root
 */
#include "GPS_locate.h"
#include "Common.h"
#include "./Include/wj_log.h"
#include "DataSet.h"

#define _GNU_SOURCE
#define Print_Log 1
#define Program_Version (nint8_t *)"V2X_APP_LTEV_AG15(Iwaill)_V3.1.1_20200116"

void Stop(int signo)
{

	CloseGPS();
	_exit(0);
}

int GPSMSTART(void)
{
	int nRet = 0;
	signal(SIGINT, Stop);
	nRet = InitGPS();
	if (nRet == RetTure)
	{
		LogPrint(LOG_LEVEL_NOTICE, "GPSInit", "GPS Init  sucess\n");

	} 
	else
	{
		LogPrint(LOG_LEVEL_NOTICE, "GPSInit", "GPS Init  error ret:%d\n,nRet");
		return ReError;
	}
	return RetTure;
}

