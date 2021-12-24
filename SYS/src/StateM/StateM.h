/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       StateM.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : StateM.h
*   Author:         : chengwu.wang       2020
********************************************************************************
*   Limitations:      None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version       Date       Initials        CR#        Descriptions
*   -------   ----------  --------------    ------    -------------------
*   01.00.00  07/07/2020    chengwu.wang        N/A         Original
********************************************************************************
*END_FILE_HDR*/
#ifndef STATEM_H
#define STATEM_H
#ifdef __cplusplus
	extern "C"{
#endif

#include<stdint.h>

#define STATEM_MAIN                              StateM_Main

extern void StateM_Main();

#define LATITUDEMAX				20
#define LONGGITUDEMAX			20
#define SOCTEMPMAX				20
#define CPUUSAGEMAX				20
#define MEMORYUSAGEMAX			20
#define DISKUSAGEMAX			20
#define CURRENTTIMEMAX			30
#define SOCSTARTTIMEMAX			100

#define STATEM_VDSSTATE_TYPE		0x000000001
#define STATEM_V2XSTATE_TYPE		0x000000010	
#define STATEM_APPSTATE_TYPE		0x000000100
#define STATEM_MCUSTATE_TYPE        0x000001000
#define STATEM_NETSTATE_TYPE		0x000010000


typedef struct _StateM_VdsState{
	int			DataDEcode;
	int			CANSend;
	int			CANRcv;
	int			GnssRcv;
	int 		GnssStatus;
	int			SatelliteslockedNum;
	char		Latitude[LATITUDEMAX];
	char		Longitude[LONGGITUDEMAX];
}StateM_VdsState;

typedef struct _StateM_V2XState{
	int			BSMTx;
	int			CertM;
	int			V2XStackTx;
	int			V2XStackRx;
	int			DbusInterface;
}StateM_V2XState;


typedef struct _StateM_NetState{
	int			LinkClientNum;
	int			TcpRcvNum;
	int			TcpSdNum;
	int			UdpSdNum;
}StateM_NetState;

typedef struct _StateM_HardwareState{
	char			SOCTemp[SOCTEMPMAX];
	char			CpuUsage[CPUUSAGEMAX];
	char			MemoryUsage[MEMORYUSAGEMAX];
	char			DiskUsage[DISKUSAGEMAX];
}StateM_HardwareState;

typedef struct _StateM_TimeInfo{
	char			CurrentTime[CURRENTTIMEMAX];
	char			SocStartTime[SOCSTARTTIMEMAX];
}StateM_TimeInfo;

typedef struct _StateM_VdsCpuMemState{
	char			CpuUsage[CPUUSAGEMAX];
	char			MemoryUsage[MEMORYUSAGEMAX];
}StateM_VdsCpuMemState;

typedef struct _StateM_NetCpuMemState{
	char			CpuUsage[CPUUSAGEMAX];
	char			MemoryUsage[MEMORYUSAGEMAX];
}StateM_NetCpuMemState;

typedef struct _StateM_V2xCpuMemState{
	char			CpuUsage[CPUUSAGEMAX];
	char			MemoryUsage[MEMORYUSAGEMAX];
}StateM_V2xCpuMemState;

typedef struct _StateM_AppCpuMemState{
	char			CpuUsage[CPUUSAGEMAX];
	char			MemoryUsage[MEMORYUSAGEMAX];
}StateM_AppCpuMemState;

typedef struct _StateM_SysCpuMemState{
	char			CpuUsage[CPUUSAGEMAX];
	char			MemoryUsage[MEMORYUSAGEMAX];
}StateM_SysCpuMemState;

typedef struct _StateM_Json{
	int              		Keyid;
	int						AppState;
	int						MCUState;
	StateM_VdsState			VdsState;
	StateM_V2XState			V2XState;
	StateM_NetState         NetState;
	StateM_HardwareState	HardwareState;
	StateM_TimeInfo			TimeInfo;
	StateM_VdsCpuMemState   VdsCpuMemState;
	StateM_NetCpuMemState   NetCpuMemState;
	StateM_V2xCpuMemState   V2xCpuMemState;
	StateM_AppCpuMemState   AppCpuMemState;
	StateM_SysCpuMemState   SysCpuMemState;
}StateM_Json;

#ifdef __cplusplus
}
#endif
#endif


