/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       CfgM.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : CfgM.h
*   Author:         : wensheng.zhang       2020
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
*   01.00.00  07/07/2020  wensheng.zhang      N/A         Original
********************************************************************************
*END_FILE_HDR*/
#ifndef CFGM_H
#define CFGM_H


#include <stdio.h>
#include <stdint.h>

#define CFGM_MAIN                CfgM_Main
#ifdef __cplusplus   
extern "C" {
#endif

extern void CfgM_Main();

#ifdef __cplusplus
}
#endif

typedef enum _t_CfgMFile_Type
{
	APPASCFG_FILE = 1,
	APPMMCFG_FILE = 2,
	APPMTCFG_FILE = 3,
	APPTLCFG_FILE = 4,
	V2XSERVERCFG_FILE = 5,
	V2XPROTOCOLCFG_FILE = 6,
	VDSCFG_FILE = 7,
	MCUCFG_FILE = 8,
	AG35CFG_FILE = 9,
	MCURQCFG_FILE = 10,
	NETCONFIG_FILE = 11,
	BASICINFO_FILE = 12,
	MODULE_CONFIG_FILE = 13,
}t_CfgMFile_Type;

/* BasicInfo.json */
typedef struct _CfgM_BasicInfo{
	char			DeviceModel[50];
	char			DeviceId[50];
	int 			OEM; 
	int  			VehicleModel; 
} CfgM_BasicInfo;

/* V2XServerCfg.json */
typedef struct _CfgM_V2XServerCfg{
	int			wgs2gcj;
	int			randId;
	int			cbrCtrl;
	int			certUpdate;
	int			hsmType;
	int			caPlatform;
} CfgM_V2XServerCfg;

/* VDSCfg.json */
typedef struct _CfgM_VDSCfg{
	char		VehId[20];
	int		    VehType; 
	char	    VehLength[20];
	char        VehWidth[20];
	char        VehHigh[20];
	char	    RtcmFlag[2]; 
	char	    AK[20];
	char        AS[20];
	char        GPSName[20];
	char        GPSName_W[20];
	char        AppKey[20];
	char        AppSectet[64];
	char	    DevId[30];
	char        DevType[30];
} CfgM_VDSCfg;

/* MCUCfg.json */
typedef struct _CfgM_MCUCfg{
	int 		   PwrUpDlyTime;
	int 		   PwrUpDlyTimeFlag;
	int 		   DiagDlyTime;
	int 		   DiagDlyTimeFlag;
	int 		   DiagVoltRangeMin;
	int 		   DiagVoltRangeMinFlag;
	int 		   DiagVoltRangeMax;
	int 		   DiagVoltRangeMaxFlag;
	int 		   DiagHystsVoltUp;
	int 		   DiagHystsVoltUpFlag;
	int 		   DiagHystsVoltDown;
	int 		   DiagHystsVoltDownFlag;

} CfgM_MCUCfg;

/* AppCfg.json */
typedef struct _CfgM_AppASCfg{
	int		 ASF_FCW;
	int		 ASF_ICW;
	int		 ASF_LTA;
	int		 ASF_BSW;
	int		 ASF_LCW;
	int		 ASF_DNPW;
	int		 ASF_EBW;
	int		 ASF_AVW;
	int		 ASF_CLW;
	int		 ASF_EVW;
	int		 ASF_VRUCW;
	int		 ASF_CVF;
	int		 ASF_SVW;
	int		 ASF_SLV;
	int 	 ASP_TTC;
	int 	 ASP_THC;
	int 	 ASP_THR;
	int 	 ASP_BLD_Angle;
	int 	 ASP_BLD_Width;
	int 	 ASP_BLD_Mirror;
	int 	 ASP_ACC_CFD;
	int 	 ASP_Yaw_CFD;
	int 	 ASP_SLStop;
	int      ASP_VehLOC_SafeDis;
	int		 ASP_ICW_SafeDis;
	int      ASP_ICW_TTC;
	int      ASP_AVW_Spd;
	int      ASP_SelfVeh_Dec;
} CfgM_AppASCfg;

typedef struct _CfgM_AppMMCfg{
	int			       MMF_RTS;
	int			       MMF_RTE;
	int			       MMF_SLW;
	int			       MMF_TJW;
	int 			   MMP_PossTH;
	int 			   MMP_LogIdx;
	int 			   MMP_DistTH;
	int 			   MMP_AngTH;
	int 			   MMP_HistTH;
	int 			   MMP_FSTH;
	int 			   MMP_SLStop;
	int				   SIP_Lon;
	int				   SIP_Lat;
	int				   SIP_Speed;
	int				   SIP_Heading;
	int				   SIP_Length;
	int				   SIP_Width;
	int				   SIP_Evaluate;

} CfgM_AppMMCfg;

typedef struct _CfgM_AppMTCfg{
	int		     	  MTF_BSM;
	int			      MTF_RSM;
	int 			  MTP_Rel_Dist;
	int 			  MTP_Rel_Spd;
	int 			  MTP_Rel_Bear;
	int 			  MTP_Act_SpdH;
	int 			  MTP_Act_SpdL;
	int 			  MTP_Rel_Radio;
} CfgM_AppMTCfg;

typedef struct _CfgM_AppTLCfg{
	int			    TLF_GW;
	int			    TLF_RLW;
	int 			TLP_GWSpdH;
	int 			TLP_GWSpdL;
	int 			TLP_GWDistW;
	int 			TLP_GWTimeW;
	int 			TLP_StpLnDist;
	int 			TLP_NodeOffsetDist;
} CfgM_AppTLCfg;


/* NetCfg.json */
typedef struct _CfgM_NetCfg{
	int				       ServerPort;
	int					   MaxConnect;
	int					   enableUDP;
	char				   DestIP[20];
	int					   DestPort;
	int					   HostPort;
	int					   CheckPeriod;
} CfgM_NetCfg;

/* Ag35.json */
//预留


typedef struct _ModuleConfig{
	int  tModuleConfig;
} CfgM_ModuleCfg;

typedef struct _CfgM_Json{
	t_CfgMFile_Type  			   CfgFileId;
	CfgM_BasicInfo 				   BasicInfo;
	CfgM_V2XServerCfg 			   V2XServerCfg;
	CfgM_VDSCfg					   VDSCfg;
	CfgM_MCUCfg 				   MCUCfg;
	CfgM_AppASCfg 				   AppASCfg;
	CfgM_AppMMCfg				   AppMMCfg;
	CfgM_AppMTCfg                  AppMTCfg;
	CfgM_AppTLCfg                  AppTLCfg;	
	CfgM_NetCfg                    NetCfg;
	CfgM_ModuleCfg                 ModuleCfg;
} CfgM_Json;


#define CFGM_VDS_RESP			0x00000001
#define	CFGM_APP_RESP			0x00000010
#define	CFGM_V2X_RESP			0x00000100
#define	CFGM_NET_RESP			0x00001000
#define	CFGM_MCU_RESP			0x00010000


typedef struct _CfgM_VDS_Resp{
	int             			   McuCfgResp;
	int                            VdsCfgResp;
	int                            Ag35CfgResp;
} CfgM_VDS_Resp;

typedef struct _CfgM_APP_Resp{
	int             			   AppCfgResp;
} CfgM_APP_Resp;

typedef struct _CfgM_V2X_Resp{
	int             			   V2xCfgResp;
} CfgM_V2X_Resp;

typedef struct _CfgM_NET_Resp{
	int             			   NetCfgResp;
} CfgM_NET_Resp;
#define CFGM_RESP_SUCCESS               0x90
#define CFGM_RESP_FALSE                 0x91


typedef struct _CfgM_Resp{
	int             			   RespId;
	CfgM_VDS_Resp 				   tVdsCfgResp;
	CfgM_APP_Resp   			   tAppCfgResp;
	CfgM_V2X_Resp				   tV2xCfgResp;
	CfgM_NET_Resp 				   tNetCfgResp;
	CfgM_MCUCfg				       tMcuCfgResp;
} CfgM_Resp;

#endif
