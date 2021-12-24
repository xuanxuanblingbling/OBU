/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       DiagM_Lcfg.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : DiagM_Lcfg.h
*   Author:         :                   2020
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
*   01.00.00  07/07/2020                      N/A         Original
********************************************************************************
*END_FILE_HDR*/
#ifndef DIAGM_LCFG_H
#define DIAGM_LCFG_H

#include "Cfg.h"

#define DIAGM_SNAPSHOT1					"SnapShot1"
#define DIAGM_SNAPSHOT2					"SnapShot2"
#define DIAGM_DIAGFILE_NAME 			"/mnt/APP/Config/obu/sysm/Diag/Diag.json"

#define DIAGM_BUF_SIZE					1024*10

typedef enum  _t_DiagMRetFlag
{
	DIAGM_SUCCESS,
	DIAGM_FALSE,
} t_DiagMRetFlag;

typedef enum  _t_DiagMDTCValueFlag
{
	DIAGM_NOTROUBLE = 0x80,
	DIAGM_TROUBLE = 0x81,
} t_DiagMDTCValueFlag;

typedef enum  _t_DiagSnapShotFlag
{
	DIAGM_INVALID,
	DIAGM_VALID,
} t_DiagSnapShotFlag;

typedef struct _DiagM_DTC_Table{
	char                    DTCName[20];
	Diag_Data               *ptDiagInfo;
	t_DiagSnapShotFlag		Flagvalue;
} DiagM_DTC_Table;

typedef struct _DiagM_ModeName_Table{
	int			    		index;
	char                    ModleName[20];
	int                     DTCNum;
	DiagM_DTC_Table         *DTC_Struct;
} DiagM_ModeName_Table;

static cJSON *gpDiagM_Json_File;
static DiagM_Json gDiagM_Json_Info;


#define DIAGM_JSON_INFO                 gDiagM_Json_Info
#define DIAGM_JSON_FILE                 gpDiagM_Json_File

#define DIAGM_CANERROR_T    		    &gDiagM_Json_Info.Diag_VDS.CANError
#define DIAGM_GPSERROR_T    		    &gDiagM_Json_Info.Diag_VDS.GPSError
#define DIAGM_GNSSDATAERROR_T    		&gDiagM_Json_Info.Diag_VDS.GnssDataError
#define DIAGM_IMUCOMERROR_T    		    &gDiagM_Json_Info.Diag_VDS.ImuComError
#define DIAGM_MCUCOMERROR_T    			&gDiagM_Json_Info.Diag_VDS.McuComError
#define DIAGM_G4ERROR_T    				&gDiagM_Json_Info.Diag_VDS.G4Error

#define DIAGM_AG15COMERROR_T    		&gDiagM_Json_Info.Diag_V2X.AG15ComError
#define DIAGM_HSMERROR_T    			&gDiagM_Json_Info.Diag_V2X.HSMError

#define DIAGM_WIFIERROR_T    			&gDiagM_Json_Info.Diag_WebServer.WIFIError

#define DIAGM_CANBUSOFF_T    			&gDiagM_Json_Info.Diag_Mcu.CanBusOff
#define DIAGM_HIGHVOLTAGE_T    			&gDiagM_Json_Info.Diag_Mcu.HighVoltage
#define DIAGM_LOWVOLTAGE_T    			&gDiagM_Json_Info.Diag_Mcu.LowVoltage


#define DIAGM_CANDATAERROR_T    		&gDiagM_Json_Info.Diag_App.CanDataError
#define DIAGM_GPSDATAERROR_T    		&gDiagM_Json_Info.Diag_App.GpsDataError
#define DIAGM_RSUDATAERROR_T    		&gDiagM_Json_Info.Diag_App.RsuDataError

#define DIAGM_HTTPERROR_T    		    &gDiagM_Json_Info.Diag_Net.HTTPError
#define DIAGM_PADRROR_T    		        &gDiagM_Json_Info.Diag_Net.PadError


#define DIAGM_KEYID			    		gDiagM_Json_Info.Keyid


#define DIAGM_VDSDTC_NUM    				6
static DiagM_DTC_Table gDiagM_VDSDTC_Table[DIAGM_VDSDTC_NUM] = {
	{"CANError", DIAGM_CANERROR_T, DIAGM_INVALID},
	{"GPSError", DIAGM_GPSERROR_T, DIAGM_INVALID},
	{"GnssDataError", DIAGM_GNSSDATAERROR_T, DIAGM_INVALID},
	{"ImuComError", DIAGM_GNSSDATAERROR_T, DIAGM_INVALID},	
	{"McuComError", DIAGM_MCUCOMERROR_T, DIAGM_INVALID},
	{"4GError", DIAGM_G4ERROR_T, DIAGM_INVALID}
};
	
#define DIAGM_V2XDTC_NUM    				2
static DiagM_DTC_Table gDiagM_V2XDTC_Table[DIAGM_V2XDTC_NUM] = {
	{"AG15ComError", DIAGM_AG15COMERROR_T, DIAGM_INVALID},
	{"HSMError", DIAGM_HSMERROR_T, DIAGM_INVALID}
};
	
#define DIAGM_WEBSERVERDTC_NUM    				1	
static DiagM_DTC_Table gDiagM_WebServerDTC_Table[DIAGM_WEBSERVERDTC_NUM] = {
	{"WIFIError", DIAGM_WIFIERROR_T, DIAGM_INVALID}
};
	
#define DIAGM_MCUDTC_NUM    				3
static DiagM_DTC_Table gDiagM_MCUDTC_Table[DIAGM_MCUDTC_NUM] = {
	{"CanBusOff", DIAGM_CANBUSOFF_T, DIAGM_INVALID},
	{"HighVoltage", DIAGM_HIGHVOLTAGE_T, DIAGM_INVALID},
	{"LowVoltage", DIAGM_LOWVOLTAGE_T, DIAGM_INVALID}
};
	
#define DIAGM_APPDTC_NUM    				3		
static DiagM_DTC_Table gDiagM_APPDTC_Table[DIAGM_APPDTC_NUM] = {
	{"GpsDataError", DIAGM_GPSDATAERROR_T, DIAGM_INVALID},
	{"CanDataError", DIAGM_CANDATAERROR_T, DIAGM_INVALID},
	{"RsuDataError", DIAGM_RSUDATAERROR_T, DIAGM_INVALID}
	
};
#define DIAGM_NETDTC_NUM    				2		
static DiagM_DTC_Table gDiagM_NETDTC_Table[DIAGM_NETDTC_NUM] = {
	{"HTTPError", DIAGM_HTTPERROR_T, DIAGM_INVALID},
	{"PadError", DIAGM_PADRROR_T, DIAGM_INVALID}	
};
	
#define DIAGM_MODLE_NUM    				6
static DiagM_ModeName_Table DiagM_ModleName[DIAGM_MODLE_NUM] = {
	{DIAGM_VDS_TYPE, "Vds", DIAGM_VDSDTC_NUM, gDiagM_VDSDTC_Table},
	{DIAGM_V2X_TYPE, "V2x", DIAGM_V2XDTC_NUM, gDiagM_V2XDTC_Table},
	{DIAGM_WEBSERVER_TYPE, "WebServer", DIAGM_WEBSERVERDTC_NUM, gDiagM_WebServerDTC_Table},
	{DIAGM_MCU_TYPE, "Mcu", DIAGM_MCUDTC_NUM, gDiagM_MCUDTC_Table},
	{DIAGM_APP_TYPE, "App", DIAGM_APPDTC_NUM, gDiagM_APPDTC_Table},
	{DIAGM_NET_TYPE, "Net", DIAGM_NETDTC_NUM, gDiagM_NETDTC_Table}
};
#define DIAGM_MODLE_INDEX(INDEX)                    DiagM_ModleName[INDEX].index
#define DIAGM_MODLE_NAME(INDEX)                     DiagM_ModleName[INDEX].ModleName
#define DIAGM_DTC_NUM(INDEX)                        DiagM_ModleName[INDEX].DTCNum
#define DIAGM_DTC_NAME(INDEX1,INDEX2)               DiagM_ModleName[INDEX1].DTC_Struct[INDEX2].DTCName
#define DIAGM_DTC_INFO(INDEX1,INDEX2)               DiagM_ModleName[INDEX1].DTC_Struct[INDEX2].ptDiagInfo
#define DIAGM_DTC_FLAG(INDEX1,INDEX2)				DiagM_ModleName[INDEX1].DTC_Struct[INDEX2].Flagvalue
#define DIAGM_DTC_STATE(INDEX1,INDEX2)              DiagM_ModleName[INDEX1].DTC_Struct[INDEX2].ptDiagInfo->DiagVal
#define DIAGM_DTC_SNAPSHOT1(INDEX1,INDEX2)          DiagM_ModleName[INDEX1].DTC_Struct[INDEX2].ptDiagInfo->SnapShot[0]
#define DIAGM_DTC_SNAPSHOT2(INDEX1,INDEX2)          DiagM_ModleName[INDEX1].DTC_Struct[INDEX2].ptDiagInfo->SnapShot[1]


#endif
