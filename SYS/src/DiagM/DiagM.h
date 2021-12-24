/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       DiagM.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : DiagM.h
*   Author:         :                      2020
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
*   01.00.00  07/07/2020                     N/A         Original
********************************************************************************
*END_FILE_HDR*/
#ifndef DIAGM_H
#define DIAGM_H

//#include<stdint.h>
#ifdef __cplusplus   
extern "C" {
#endif

#define DIAGM_MAIN   					DiagM_Main
extern void DiagM_Main();
#ifdef __cplusplus
}
#endif

#define DIAGM_VDS_TYPE				0x00000001
#define DIAGM_VDS_MASK				0xFFFFFFFE

#define DIAGM_V2X_TYPE				0x00000010	
#define DIAGM_V2X_MASK				0xFFFFFFEF

#define DIAGM_WEBSERVER_TYPE		0x00000100
#define DIAGM_WEBSERVER_MASK		0xFFFFFEFF

#define DIAGM_MCU_TYPE       		0x00001000
#define DIAGM_MCU_MASK       		0xFFFFEFFF

#define DIAGM_APP_TYPE				0x00010000
#define DIAGM_APP_MASK				0xFFFEFFFF

#define DIAGM_NET_TYPE				0x00100000
#define DIAGM_NET_MASK				0xFFEFFFFF


typedef struct _Diag_Snap_Shot{
	char					SysTime[30];
	char					SocTemp[20];
	char					CurrentSpeed[20];
} Diag_Snap_Shot;

typedef struct _Diag_Data{
	int 						DiagVal;
	Diag_Snap_Shot				SnapShot[2];
} Diag_Data;

typedef struct _DiagM_VDS{
	Diag_Data			CANError;
	Diag_Data			GPSError;
	Diag_Data			GnssDataError;
	Diag_Data			ImuComError;
	Diag_Data			McuComError;
	Diag_Data			G4Error;
} DiagM_VDS;

typedef struct _DiagM_V2X{
	Diag_Data			AG15ComError;
	Diag_Data			HSMError;
} DiagM_V2X;

typedef struct _DiagM_WebServer{
	Diag_Data			WIFIError;
} DiagM_WebServer;

typedef struct _DiagM_Mcu{
	Diag_Data			CanBusOff;
	Diag_Data			HighVoltage;
	Diag_Data			LowVoltage;
} DiagM_Mcu;

typedef struct _DiagM_App{
	Diag_Data			GpsDataError;
	Diag_Data			CanDataError;
	Diag_Data			RsuDataError;
} DiagM_App;


typedef struct _DiagM_Net{
	Diag_Data			HTTPError;
	Diag_Data			PadError;
} DiagM_Net;

typedef struct _DiagM_Json{
	int                  Keyid;
	DiagM_VDS		     Diag_VDS;
	DiagM_V2X            Diag_V2X;
	DiagM_WebServer      Diag_WebServer;
	DiagM_Mcu            Diag_Mcu;
	DiagM_App            Diag_App;
	DiagM_Net            Diag_Net;
} DiagM_Json;


#endif
