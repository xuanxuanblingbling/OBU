/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       StateM_Lcfg.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : StateM_Lcfg.h
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
#ifndef STATEM_LCFG
#define STATEM_LCFG

#include "StateM.h"
#include "cJSON.h"

#define STATEM_STATEFILE_NAME	"/mnt/APP/Config/obu/sysm/DynamicInfo/DynamicInfo.json"
#define CJSON_NUMBER 		(1 << 3)
#define CJSON_STRING 		(1 << 4)
#define CJSON_OBJECT 		(1 << 6)

timer_t timeid;  //定义一个全局的定时器id
double usage = 0;

int processID[5]={0};              //用于存储各个进程的ID
int mPidCount=0;
int processCpuTime1[5];        //各个进程CPU Time1
int processCpuTime2[5];        //各个进程CPU Time2
double modulesCpuusage[5];     //各个进程CPU使用率
double memoryusage[5];         //各个进程内存使用率
int mCount = 1;

static cJSON *gpStateM_Json_File;
static StateM_Json gStateM_Json_Info;

#define STATEM_JSON_INFO                 gStateM_Json_Info
#define STATEM_JSON_FILE                 gpStateM_Json_File

#define STATEM_BUF_SIZE					 1024*2

typedef enum  _t_StateMRetFlag
{
	STATEM_SUCCESS,
	STATEM_FALSE,
} t_StateMRetFlag;

static t_StateMRetFlag Get_SOCTEMP_Info(char *soctemp);
static t_StateMRetFlag StateM_GetCpuUsage_Info(char *cpuusage);
static t_StateMRetFlag StateM_GetMemUsage_Info(char *memoryusage);
static t_StateMRetFlag Get_SOCSTARTTIME_Info(char *socstarttime);
static void Get_CURRENTTIME_Info(char *currenttime);
static t_StateMRetFlag Get_DISKUSAGE_Info(char *diskusage);

static void addKeyToJson(char ModuleName[5][20]);

#define STATEM_KEYID    			gStateM_Json_Info.Keyid

#define STATEM_DataDEcode_I    		&gStateM_Json_Info.VdsState.DataDEcode
#define STATEM_MCUSEND_I    		&gStateM_Json_Info.VdsState.CANSend
#define STATEM_MCURCV_I    			&gStateM_Json_Info.VdsState.CANRcv
#define STATEM_GNSSRCV_I    		&gStateM_Json_Info.VdsState.GnssRcv
#define STATEM_GNSSSTATUS_I         &gStateM_Json_Info.VdsState.GnssStatus
#define STATEM_SATELLITES_I         &gStateM_Json_Info.VdsState.SatelliteslockedNum
#define STATEM_LATITUDE_P           gStateM_Json_Info.VdsState.Latitude
#define STATEM_LONGITUDE_P          gStateM_Json_Info.VdsState.Longitude

#define STATEM_BSMTX_I    		    &gStateM_Json_Info.V2XState.BSMTx
#define STATEM_CERTM_I    		    &gStateM_Json_Info.V2XState.CertM
#define STATEM_V2XSTACKTX_I    		&gStateM_Json_Info.V2XState.V2XStackTx
#define STATEM_V2XSTACKRX_I    		&gStateM_Json_Info.V2XState.V2XStackRx
#define STATEM_DBUSINTERFACE_I      &gStateM_Json_Info.V2XState.DbusInterface

#define STATEM_LINKCLIENTNUM_I      &gStateM_Json_Info.NetState.LinkClientNum
#define STATEM_TCPRCVNUM_I          &gStateM_Json_Info.NetState.TcpRcvNum
#define STATEM_TCPSDNUM_I          	&gStateM_Json_Info.NetState.TcpSdNum
#define STATEM_UDPSDNUM_I          	&gStateM_Json_Info.NetState.UdpSdNum

#define STATEM_APPSTATE_I           &gStateM_Json_Info.AppState
#define STATEM_MCUSTATE_I           &gStateM_Json_Info.MCUState


#define STATEM_HARDWARESTATE_KEY    "HardwareState"
#define STATEM_SOCTEMP_KEY    		"SOCTemp"
#define STATEM_CPUUSAGE_KEY    		"CpuUsage"
#define STATEM_MEMORYUSAGE_KEY    	"MemoryUsage"
#define STATEM_DISKUSAGE_KEY    	"DiskUsage"

#define STATEM_VDSCPUMEM_KEY        "VDSCpuMem"
#define STATEM_NETCPUMEM_KEY        "NETCpuMem"
#define STATEM_V2XCPUMEM_KEY        "V2XCpuMem"
#define STATEM_APPCPUMEM_KEY        "APPCpuMem"
#define STATEM_SYSCPUMEM_KEY        "SYSCpuMem"


#define STATEM_TIMEINFO_KEY    		"TimeInfo"
#define STATEM_CURRENTTIME_KEY    	"CurrentTime"
#define STATEM_SOCSTARTTIME_KEY    	"SocStartTime"

#define STATEM_SOCTEMP_VAL           gStateM_Json_Info.HardwareState.SOCTemp
#define STATEM_CPUUSAGE_VAL          gStateM_Json_Info.HardwareState.CpuUsage
#define STATEM_MEMORYUSAGE_VAL       gStateM_Json_Info.HardwareState.MemoryUsage
#define STATEM_DISKUSAGE_VAL         gStateM_Json_Info.HardwareState.DiskUsage

#define STATEM_CURRENTTIME_VAL       gStateM_Json_Info.TimeInfo.CurrentTime
#define STATEM_SOCSTARTTIME_VAL      gStateM_Json_Info.TimeInfo.SocStartTime

#define STATEM_VDSCPUUSAGE_VAL       gStateM_Json_Info.VdsCpuMemState.CpuUsage
#define STATEM_VDSMEMORYUSAGE_VAL    gStateM_Json_Info.VdsCpuMemState.MemoryUsage
#define STATEM_NETCPUUSAGE_VAL       gStateM_Json_Info.NetCpuMemState.CpuUsage
#define STATEM_NETMEMORYUSAGE_VAL    gStateM_Json_Info.NetCpuMemState.MemoryUsage
#define STATEM_V2XCPUUSAGE_VAL       gStateM_Json_Info.V2xCpuMemState.CpuUsage
#define STATEM_V2XMEMORYUSAGE_VAL    gStateM_Json_Info.V2xCpuMemState.MemoryUsage
#define STATEM_APPCPUUSAGE_VAL       gStateM_Json_Info.AppCpuMemState.CpuUsage
#define STATEM_APPMEMORYUSAGE_VAL    gStateM_Json_Info.AppCpuMemState.MemoryUsage
#define STATEM_SYSCPUUSAGE_VAL       gStateM_Json_Info.SysCpuMemState.CpuUsage
#define STATEM_SYSMEMORYUSAGE_VAL    gStateM_Json_Info.SysCpuMemState.MemoryUsage

typedef struct _StateM_SMC_Table{
	char               SMCName[20];
	char               *ptStateInfo;
	int 			   *ptKeyValue;
} StateM_SMC_Table;

typedef struct _StateM_State_Table{
	int              		index;
	char                    ModleName[20];
	int                     SMCNum;
	StateM_SMC_Table        *SMC_Struct;
} StateM_State_Table;


#define STATEM_VDSSTATE_NUM     8
static StateM_SMC_Table gStateM_VdsState[STATEM_VDSSTATE_NUM] = {
	{"DataDEcode", NULL, STATEM_DataDEcode_I},
	{"McuSend", NULL, STATEM_MCUSEND_I},
	{"McuRcv", NULL, STATEM_MCURCV_I},
	{"GnssRcv", NULL, STATEM_GNSSRCV_I},
	{"GnssStatus", NULL, STATEM_GNSSSTATUS_I},
	{"SatelliteslockedNum", NULL, STATEM_SATELLITES_I},
	{"Latitude", STATEM_LATITUDE_P, NULL},
	{"Longitude", STATEM_LONGITUDE_P, NULL}
};

#define STATEM_V2XSTATE_NUM     5
static StateM_SMC_Table gStateM_V2xState[STATEM_V2XSTATE_NUM] = {
	{"BSMTx", NULL, STATEM_BSMTX_I},
	{"CertM", NULL, STATEM_CERTM_I},
	{"V2XStackTx", NULL, STATEM_V2XSTACKTX_I},
	{"V2XStackRx", NULL, STATEM_V2XSTACKRX_I},
	{"DbusInterface", NULL, STATEM_DBUSINTERFACE_I},

};

#define STATEM_NETSTATE_NUM     4
static StateM_SMC_Table gStateM_NetState[STATEM_NETSTATE_NUM] = {
	{"LinkClientNum", NULL, STATEM_LINKCLIENTNUM_I},
	{"TcpRcvNum", NULL, STATEM_TCPRCVNUM_I},
	{"TcpSdNum", NULL, STATEM_TCPSDNUM_I},
	{"UdpSdNum", NULL, STATEM_UDPSDNUM_I}
};

#define STATEM_APPSTATE_NUM     0
static StateM_SMC_Table gStateM_AppState[] = {
	{"AppState", NULL, STATEM_APPSTATE_I}
};

#define STATEM_MCUSTATE_NUM     0
static StateM_SMC_Table gStateM_McuState[] = {
	{"MCUState", NULL, STATEM_MCUSTATE_I}
};

#define STATEM_MODLE_NUM		5
static StateM_State_Table StateM_ModleName[STATEM_MODLE_NUM] = {
	{STATEM_VDSSTATE_TYPE, "VdsState", STATEM_VDSSTATE_NUM, gStateM_VdsState},
	{STATEM_V2XSTATE_TYPE, "V2XState", STATEM_V2XSTATE_NUM, gStateM_V2xState},
	{STATEM_APPSTATE_TYPE, "AppState", STATEM_APPSTATE_NUM, gStateM_AppState},
	{STATEM_MCUSTATE_TYPE, "MCUState", STATEM_MCUSTATE_NUM, gStateM_McuState},
	{STATEM_NETSTATE_TYPE, "NetState", STATEM_NETSTATE_NUM, gStateM_NetState},
};

#define STATEM_TABLE_INDEX(INDEX)               StateM_ModleName[INDEX].index
#define STATEM_TABLE_MODLENAME(INDEX)        	StateM_ModleName[INDEX].ModleName
#define STATEM_TABLE_SMCNUM(INDEX)              StateM_ModleName[INDEX].SMCNum
#define STATEM_TABLE_STATEINFO(INDEX)           StateM_ModleName[INDEX].SMC_Struct


#endif

