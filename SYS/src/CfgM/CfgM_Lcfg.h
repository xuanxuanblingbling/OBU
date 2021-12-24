
/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       cfgM.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : cfgM.h
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
#ifndef CFGM_LCFG_H
#define CFGM_LCFG_H
#include "CfgM.h"

static cJSON *gpCfgM_Json_File;
#define CFGM_JSON_FILE                  gpCfgM_Json_File

#define CFGM_BUF_SIZE                  	1024

static CfgM_Json gCfgM_Json_Info;
#define CFGM_JSON_INFO                   gCfgM_Json_Info
#define CFGM_FILE_ID                     gCfgM_Json_Info.CfgFileId
#define CFGM_BASIC_CFG_T           	 	 gCfgM_Json_Info.BasicInfo
#define CFGM_BASIC_DEVICEID          	 gCfgM_Json_Info.BasicInfo.DeviceId
#define CFGM_BASIC_DEVICEMODEL           gCfgM_Json_Info.BasicInfo.DeviceModel
#define CFGM_BASIC_OEM           		 gCfgM_Json_Info.BasicInfo.OEM
#define CFGM_BASIC_VEHICLEMODEL          gCfgM_Json_Info.BasicInfo.VehicleModel

#define CFGM_V2XSERVER_CFG_T        	 gCfgM_Json_Info.V2XServerCfg
#define CFGM_V2XSERVER_WGS2GCJ       	 gCfgM_Json_Info.V2XServerCfg.wgs2gcj
#define CFGM_V2XSERVER_RANDID        	 gCfgM_Json_Info.V2XServerCfg.randId
#define CFGM_V2XSERVER_CBRCTRL       	 gCfgM_Json_Info.V2XServerCfg.cbrCtrl
#define CFGM_V2XSERVER_CERTUPDATE    	 gCfgM_Json_Info.V2XServerCfg.certUpdate
#define CFGM_V2XSERVER_HSMTYPE       	 gCfgM_Json_Info.V2XServerCfg.hsmType
#define CFGM_V2XSERVER_CAPLATFORM    	 gCfgM_Json_Info.V2XServerCfg.caPlatform

#define CFGM_VDS_CFG_T             	 	 gCfgM_Json_Info.VDSCfg
#define CFGM_VDS_VEHID             	     gCfgM_Json_Info.VDSCfg.VehId
#define CFGM_VDS_VEHTYPE           		 gCfgM_Json_Info.VDSCfg.VehType
#define CFGM_VDS_VEHLENGTH         		 gCfgM_Json_Info.VDSCfg.VehLength
#define CFGM_VDS_VEHWIDTH          		 gCfgM_Json_Info.VDSCfg.VehWidth
#define CFGM_VDS_VEHHIGH           		 gCfgM_Json_Info.VDSCfg.VehHigh
#define CFGM_VDS_RtcmFlag        		 gCfgM_Json_Info.VDSCfg.RtcmFlag
#define CFGM_VDS_AK		         		 gCfgM_Json_Info.VDSCfg.AK
#define CFGM_VDS_AS      		         gCfgM_Json_Info.VDSCfg.AS
#define CFGM_VDS_GPSName   		         gCfgM_Json_Info.VDSCfg.GPSName
#define CFGM_VDS_GPSName_W   		     gCfgM_Json_Info.VDSCfg.GPSName_W
#define CFGM_VDS_AppKey    		         gCfgM_Json_Info.VDSCfg.AppKey
#define CFGM_VDS_AppSectet 		         gCfgM_Json_Info.VDSCfg.AppSectet
#define CFGM_VDS_DevId		         	 gCfgM_Json_Info.VDSCfg.DevId
#define CFGM_VDS_DevType      		     gCfgM_Json_Info.VDSCfg.DevType

#define CFGM_MCU_CFG_T               	 gCfgM_Json_Info.MCUCfg
#define CFGM_MCU_PWRUPDLYTIME         	 gCfgM_Json_Info.MCUCfg.PwrUpDlyTime
#define CFGM_MCU_PWRUPDLYTIMEFLAG    	 gCfgM_Json_Info.MCUCfg.PwrUpDlyTimeFlag
#define CFGM_MCU_DIAGDLYTIME         	 gCfgM_Json_Info.MCUCfg.DiagDlyTime
#define CFGM_MCU_DIAGDLYTIMEFLAG     	 gCfgM_Json_Info.MCUCfg.DiagDlyTimeFlag
#define CFGM_MCU_DIAGVOLTRANGEMIN  	 	 gCfgM_Json_Info.MCUCfg.DiagVoltRangeMin
#define CFGM_MCU_DIAGVOLTRANGEMINFLAG 	 gCfgM_Json_Info.MCUCfg.DiagVoltRangeMinFlag
#define CFGM_MCU_DIAGVOLTRANGEMAX  		 gCfgM_Json_Info.MCUCfg.DiagVoltRangeMax
#define CFGM_MCU_DIAGVOLTRANGEMAXFLAG  	 gCfgM_Json_Info.MCUCfg.DiagVoltRangeMaxFlag
#define CFGM_MCU_DIAGHYSTSVOLTUP   		 gCfgM_Json_Info.MCUCfg.DiagHystsVoltUp
#define CFGM_MCU_DIAGHYSTSVOLTUPFLAG   	 gCfgM_Json_Info.MCUCfg.DiagHystsVoltUpFlag
#define CFGM_MCU_DIAGHYSTSVOLTDOWN 		 gCfgM_Json_Info.MCUCfg.DiagHystsVoltDown
#define CFGM_MCU_DIAGHYSTSVOLTDOWNFLAG 	 gCfgM_Json_Info.MCUCfg.DiagHystsVoltDownFlag

#define CFGM_NET_CFG_T             gCfgM_Json_Info.NetCfg
#define CFGM_NET_SERVERPORT        gCfgM_Json_Info.NetCfg.ServerPort
#define CFGM_NET_MAXCONNECT        gCfgM_Json_Info.NetCfg.MaxConnect
#define CFGM_NET_ENABLEUDP         gCfgM_Json_Info.NetCfg.enableUDP
#define CFGM_NET_DESTIP            gCfgM_Json_Info.NetCfg.DestIP
#define CFGM_NET_DESTPORT          gCfgM_Json_Info.NetCfg.DestPort
#define CFGM_NET_HOSTPORT          gCfgM_Json_Info.NetCfg.HostPort
#define CFGM_NET_CHECKPERIOD       gCfgM_Json_Info.NetCfg.CheckPeriod


#define CFGM_APPAS_CFG_T               gCfgM_Json_Info.AppASCfg
#define CFGM_APPAS_ASF_FCW             gCfgM_Json_Info.AppASCfg.ASF_FCW
#define CFGM_APPAS_ASF_ICW             gCfgM_Json_Info.AppASCfg.ASF_ICW
#define CFGM_APPAS_ASF_LTA             gCfgM_Json_Info.AppASCfg.ASF_LTA
#define CFGM_APPAS_ASF_BSW             gCfgM_Json_Info.AppASCfg.ASF_BSW
#define CFGM_APPAS_ASF_LCW             gCfgM_Json_Info.AppASCfg.ASF_LCW
#define CFGM_APPAS_ASF_DNPW            gCfgM_Json_Info.AppASCfg.ASF_DNPW
#define CFGM_APPAS_ASF_EBW             gCfgM_Json_Info.AppASCfg.ASF_EBW
#define CFGM_APPAS_ASF_AVW             gCfgM_Json_Info.AppASCfg.ASF_AVW
#define CFGM_APPAS_ASF_CLW             gCfgM_Json_Info.AppASCfg.ASF_CLW
#define CFGM_APPAS_ASF_EVW             gCfgM_Json_Info.AppASCfg.ASF_EVW
#define CFGM_APPAS_ASF_VRUCW           gCfgM_Json_Info.AppASCfg.ASF_VRUCW
#define CFGM_APPAS_ASF_CVF             gCfgM_Json_Info.AppASCfg.ASF_CVF
#define CFGM_APPAS_ASF_SVW             gCfgM_Json_Info.AppASCfg.ASF_SVW
#define CFGM_APPAS_ASF_SLV             gCfgM_Json_Info.AppASCfg.ASF_SLV
#define CFGM_APPAS_ASP_TTC             gCfgM_Json_Info.AppASCfg.ASP_TTC
#define CFGM_APPAS_ASP_THC             gCfgM_Json_Info.AppASCfg.ASP_THC
#define CFGM_APPAS_ASP_THR             gCfgM_Json_Info.AppASCfg.ASP_THR
#define CFGM_APPAS_ASP_BLD_Angle       gCfgM_Json_Info.AppASCfg.ASP_BLD_Angle
#define CFGM_APPAS_ASP_BLD_Width       gCfgM_Json_Info.AppASCfg.ASP_BLD_Width
#define CFGM_APPAS_ASP_BLD_Mirror      gCfgM_Json_Info.AppASCfg.ASP_BLD_Mirror
#define CFGM_APPAS_ASP_ACC_CFD         gCfgM_Json_Info.AppASCfg.ASP_ACC_CFD
#define CFGM_APPAS_ASP_Yaw_CFD         gCfgM_Json_Info.AppASCfg.ASP_Yaw_CFD
#define CFGM_APPAS_ASP_SLStop          gCfgM_Json_Info.AppASCfg.ASP_SLStop
#define CFGM_APPAS_ASP_VEHLOC_SAFEDIS       gCfgM_Json_Info.AppASCfg.ASP_VehLOC_SafeDis
#define CFGM_APPAS_ASP_ICW_SAFEDIS          gCfgM_Json_Info.AppASCfg.ASP_ICW_SafeDis
#define CFGM_APPAS_ASP_ICW_TTC         gCfgM_Json_Info.AppASCfg.ASP_ICW_TTC
#define CFGM_APPAS_ASP_AVW_SPD         gCfgM_Json_Info.AppASCfg.ASP_AVW_Spd
#define CFGM_APPAS_ASP_SELFVEH_DEC         gCfgM_Json_Info.AppASCfg.ASP_SelfVeh_Dec


#define CFGM_APPMM_CFG_T             gCfgM_Json_Info.AppMMCfg
#define CFGM_APPMM_MMF_RTS           gCfgM_Json_Info.AppMMCfg.MMF_RTS
#define CFGM_APPMM_MMF_RTE           gCfgM_Json_Info.AppMMCfg.MMF_RTE
#define CFGM_APPMM_MMF_SLW           gCfgM_Json_Info.AppMMCfg.MMF_SLW
#define CFGM_APPMM_MMF_TJW           gCfgM_Json_Info.AppMMCfg.MMF_TJW
#define CFGM_APPMM_MMP_PossTH        gCfgM_Json_Info.AppMMCfg.MMP_PossTH
#define CFGM_APPMM_MMP_LogIdx        gCfgM_Json_Info.AppMMCfg.MMP_LogIdx
#define CFGM_APPMM_MMP_DistTH        gCfgM_Json_Info.AppMMCfg.MMP_DistTH
#define CFGM_APPMM_MMP_AngTH         gCfgM_Json_Info.AppMMCfg.MMP_AngTH
#define CFGM_APPMM_MMP_HistTH        gCfgM_Json_Info.AppMMCfg.MMP_HistTH
#define CFGM_APPMM_MMP_FSTH          gCfgM_Json_Info.AppMMCfg.MMP_FSTH
#define CFGM_APPMM_MMP_SLStop        gCfgM_Json_Info.AppMMCfg.MMP_SLStop
#define CFGM_APPMM_SIP_LON       	 gCfgM_Json_Info.AppMMCfg.SIP_Lon
#define CFGM_APPMM_SIP_LAT       	 gCfgM_Json_Info.AppMMCfg.SIP_Lat
#define CFGM_APPMM_SIP_SPEED       	 gCfgM_Json_Info.AppMMCfg.SIP_Speed
#define CFGM_APPMM_SIP_HEADING     	 gCfgM_Json_Info.AppMMCfg.SIP_Heading
#define CFGM_APPMM_SIP_LENGTH   	 gCfgM_Json_Info.AppMMCfg.SIP_Length
#define CFGM_APPMM_SIP_WIDTH    	 gCfgM_Json_Info.AppMMCfg.SIP_Width
#define CFGM_APPMM_SIP_EVALUATE      gCfgM_Json_Info.AppMMCfg.SIP_Evaluate



#define CFGM_APPMT_CFG_T                  gCfgM_Json_Info.AppMTCfg
#define CFGM_APPMT_MTF_BSM                gCfgM_Json_Info.AppMTCfg.MTF_BSM
#define CFGM_APPMT_MTF_RSM                gCfgM_Json_Info.AppMTCfg.MTF_RSM
#define CFGM_APPMT_MTP_Rel_Dist           gCfgM_Json_Info.AppMTCfg.MTP_Rel_Dist
#define CFGM_APPMT_MTP_Rel_Spd            gCfgM_Json_Info.AppMTCfg.MTP_Rel_Spd
#define CFGM_APPMT_MTP_Rel_Bear           gCfgM_Json_Info.AppMTCfg.MTP_Rel_Bear
#define CFGM_APPMT_MTP_Act_SpdH           gCfgM_Json_Info.AppMTCfg.MTP_Act_SpdH
#define CFGM_APPMT_MTP_Act_SpdL           gCfgM_Json_Info.AppMTCfg.MTP_Act_SpdL
#define CFGM_APPMT_MTP_Rel_Radio          gCfgM_Json_Info.AppMTCfg.MTP_Rel_Radio

#define CFGM_APPTL_CFG_T                 gCfgM_Json_Info.AppTLCfg
#define CFGM_APPTL_TLF_GW                gCfgM_Json_Info.AppTLCfg.TLF_GW
#define CFGM_APPTL_TLF_RLW               gCfgM_Json_Info.AppTLCfg.TLF_RLW
#define CFGM_APPTL_TLP_GWSpdH            gCfgM_Json_Info.AppTLCfg.TLP_GWSpdH
#define CFGM_APPTL_TLP_GWSpdL            gCfgM_Json_Info.AppTLCfg.TLP_GWSpdL
#define CFGM_APPTL_TLP_GWDistW           gCfgM_Json_Info.AppTLCfg.TLP_GWDistW
#define CFGM_APPTL_TLP_GWTimeW           gCfgM_Json_Info.AppTLCfg.TLP_GWTimeW
#define CFGM_APPTL_TLP_StpLnDist         gCfgM_Json_Info.AppTLCfg.TLP_StpLnDist
#define CFGM_APPTL_TLP_NodeOffsetDist    gCfgM_Json_Info.AppTLCfg.TLP_NodeOffsetDist

typedef enum  _t_TimeOut_Type
{
	TIMEOUT_VALID,
	TIMEOUT_INVALID,
} t_TimeOut_Type;


/* 文件索引：用于open写入json文件 */
typedef struct _CfgM_FileNameTable{
	t_CfgMFile_Type			FileIndex;
	char                    FileName[200];
    void                    (* Indication)(void); 
    void                    (* IndicationResp)(int i, t_TimeOut_Type TimeOutFlag); 
	int                     SendStructValue;
} CfgM_FileNameTable;


static void CfgM_AppASCfg_Fun();
static void CfgM_AppMMCfg_Fun();
static void CfgM_AppMTCfg_Fun();
static void CfgM_AppTLCfg_Fun();
static void CfgM_V2XServerCfg_Fun();
static void CfgM_VDSCfg_Fun();
static void CfgM_MCUCfg_Fun();
static void CfgM_NetCfg_Fun();
static void CfgM_BasicInfoCfg_Fun();
static void CfgM_AppASCfg_Resp_Fun();
static void CfgM_AppMMCfg_Resp_Fun();
static void CfgM_AppMTCfg_Resp_Fun();
static void CfgM_AppTLCfg_Resp_Fun();
static void CfgM_V2XProtocolCfg_Resp_Fun();
static void CfgM_V2XServerCfg_Resp_Fun();
static void CfgM_VDSCfg_Resp_Fun();
static void CfgM_MCUCfg_Resp_Fun();
static void CfgM_Ag35Cfg_Resp_Fun();
static void CfgM_McuCfgRq_RespJsonInfo_Fun();
static void CfgM_NetCfg_Resp_Fun();
#define   CFGM_APPAS_UPDATE_NOTIFY				0x80
#define   CFGM_APPMM_UPDATE_NOTIFY				0x81
#define   CFGM_APPMT_UPDATE_NOTIFY				0x82
#define   CFGM_APPTL_UPDATE_NOTIFY				0x83
#define   CFGM_V2XPROTO_UPDATE_NOTIFY            0x80
#define   CFGM_V2XSERVER_UPDATE_NOTIFY           0x81
#define   CFGM_VDS_UPDATE_NOTIFY                 0x80
#define   CFGM_MCU_UPDATE_NOTIFY                 0x81
#define   CFGM_AG35_UPDATE_NOTIFY                0x82
#define   CFGM_MCU_CFG_FILE_RQ                   0x83
#define   CFGM_NET_UPDATE_NOTIFY                 0x80
#define   CFGM_INVALID                           0xff

#define	  CFGM_MCUCFG_FILENAME		"/mnt/APP/Config/obu/vds/MCUCfg.json"

#define CFGM_FILE_NUM    				     12
static CfgM_FileNameTable gtCfgM_FileNameTable[CFGM_FILE_NUM] = {
	{APPASCFG_FILE, "/mnt/APP/Config/obu/app/AppASCfg.json", &CfgM_AppASCfg_Fun, &CfgM_AppASCfg_Resp_Fun, CFGM_APPAS_UPDATE_NOTIFY},
	{APPMMCFG_FILE, "/mnt/APP/Config/obu/app/AppMMCfg.json", &CfgM_AppMMCfg_Fun, &CfgM_AppMMCfg_Resp_Fun, CFGM_APPMM_UPDATE_NOTIFY},
	{APPMTCFG_FILE, "/mnt/APP/Config/obu/app/AppMTCfg.json", &CfgM_AppMTCfg_Fun, &CfgM_AppMTCfg_Resp_Fun, CFGM_APPMT_UPDATE_NOTIFY},
	{APPTLCFG_FILE, "/mnt/APP/Config/obu/app/AppTLCfg.json", &CfgM_AppTLCfg_Fun, &CfgM_AppTLCfg_Resp_Fun, CFGM_APPTL_UPDATE_NOTIFY},
	{V2XSERVERCFG_FILE, "/mnt/APP/Config/obu/v2x/V2XServerCfg.json", &CfgM_V2XServerCfg_Fun, &CfgM_V2XServerCfg_Resp_Fun, CFGM_V2XSERVER_UPDATE_NOTIFY},
	{V2XPROTOCOLCFG_FILE, "NULL", NULL, &CfgM_V2XProtocolCfg_Resp_Fun, CFGM_V2XPROTO_UPDATE_NOTIFY},
	{VDSCFG_FILE, "/mnt/APP/Config/obu/vds/VDSCfg.json", &CfgM_VDSCfg_Fun, &CfgM_VDSCfg_Resp_Fun, CFGM_VDS_UPDATE_NOTIFY},
	{MCUCFG_FILE, "/mnt/APP/Config/obu/vds/MCUCfg.json", &CfgM_MCUCfg_Fun, &CfgM_MCUCfg_Resp_Fun, CFGM_MCU_UPDATE_NOTIFY},
	{AG35CFG_FILE, "NULL", NULL, &CfgM_Ag35Cfg_Resp_Fun, CFGM_INVALID},
	{MCURQCFG_FILE, "NULL", &CfgM_MCUCfg_Fun, &CfgM_McuCfgRq_RespJsonInfo_Fun, CFGM_MCU_CFG_FILE_RQ},
	{NETCONFIG_FILE, "/mnt/APP/Config/obu/net/NetConfig.json", &CfgM_NetCfg_Fun, &CfgM_NetCfg_Resp_Fun, CFGM_NET_UPDATE_NOTIFY},
	{BASICINFO_FILE, "/mnt/APP/Config/obu/sysm/BasicInfo/BasicInfo.json", &CfgM_BasicInfoCfg_Fun, NULL, 0},
};

#define CFGM_FILE_INDEX(INDEX)          	gtCfgM_FileNameTable[INDEX].FileIndex
#define CFGM_FILE_NAME(INDEX)           	gtCfgM_FileNameTable[INDEX].FileName
#define CFGM_FILE_FUN(INDEX)            	gtCfgM_FileNameTable[INDEX].Indication
#define CFGM_FILE_RESP_FUN(INDEX)       	gtCfgM_FileNameTable[INDEX].IndicationResp
#define CFGM_FILE_RQ_STRUCT_VALUE(INDEX)    gtCfgM_FileNameTable[INDEX].SendStructValue


/* 文件索引：一级key索引 */
#define CFGM_BASIC_MKEY_NUM              4
#define CFGM_V2X_MKEY_NUM                2
#define CFGM_V2X_SKEY_BSMTX_NUM          3
#define CFGM_V2X_SKEY_CERTM_NUM          3
#define CFGM_V2X_SKEY_NUM                6

#define CFGM_VDS_MKEY_NUM                3
#define CFGM_VDS_SKEY_NUM                12
#define CFGM_VDS_SKEY_VEH_NUM            5
#define CFGM_VDS_SKEY_GNSS_NUM           1
#define CFGM_VDS_SKEY_QXWZ_NUM           6

#define CFGM_MCU_MKEY_NUM                12

#define CFGM_AG35_MKEY_NUM               0

#define CFGM_NET_MKEY_NUM                3
#define CFGM_NET_SKEY_NUM                6
#define CFGM_NET_SKEY_TCP_NUM            2
#define CFGM_NET_SKEY_UDP_NUM            4

#define CFGM_APPAS_MKEY_NUM              28
#define CFGM_APPMM_MKEY_NUM              18
#define CFGM_APPMT_MKEY_NUM              8
#define CFGM_APPTL_MKEY_NUM              8

#define CFGM_INVALID                    0xff
typedef enum  _t_CJson_Type
{
	CJSON_STRING = 1<<4,
	CJSON_INT =  1<<3,
	CJSON_ARRAY = 1<<5,
	CJSON_STRUCT = 1<<6,
} t_CJson_Type;

typedef struct _CfgM_SKeyInfoTable{
	char                    KeyName[20];
	t_CJson_Type 			Type;
	int                     *cJsonInit;
	char                    *cJsonString;
} CfgM_SKeyInfoTable;



typedef struct _CfgM_MKeyInfoTable{
	char                    KeyName[30];
	int                     SubKeyNum;
	t_CJson_Type 			Type;
	int                     *cJsonInit;
	char                    *cJsonString;
} CfgM_MKeyInfoTable;

//V2XServerCfg

static CfgM_MKeyInfoTable gtCfgM_V2XMKeyTable[CFGM_BASIC_MKEY_NUM] = {
	{"BSMTx", CFGM_V2X_SKEY_BSMTX_NUM, CJSON_STRUCT, NULL, NULL},
	{"CertM", CFGM_V2X_SKEY_CERTM_NUM, CJSON_STRUCT, NULL, NULL},
};

//VDSCfg
static CfgM_MKeyInfoTable gtCfgM_VDSMKeyTable[CFGM_VDS_MKEY_NUM] = {
	{"VEH", CFGM_VDS_SKEY_VEH_NUM, CJSON_STRUCT, NULL, NULL},
	{"GNSS", CFGM_VDS_SKEY_GNSS_NUM, CJSON_STRUCT, NULL, NULL},
	{"QXWZ", CFGM_VDS_SKEY_QXWZ_NUM, CJSON_STRUCT, NULL, NULL},
	
};


//NetConfig
static CfgM_MKeyInfoTable gtCfgM_NetMKeyTable[CFGM_NET_MKEY_NUM] = {
	{"TcpServer", CFGM_NET_SKEY_TCP_NUM, CJSON_STRUCT, NULL, NULL},
	{"UDP", CFGM_NET_SKEY_UDP_NUM, CJSON_STRUCT, NULL, NULL},
	{"CheckPeriod", 0, CJSON_INT, &CFGM_NET_CHECKPERIOD, NULL},
};

//MCUCfg
static CfgM_MKeyInfoTable gtCfgM_MCUMKeyTable[CFGM_MCU_MKEY_NUM] = {
	{"PwrUpDlyTime", 0, CJSON_INT, &CFGM_MCU_PWRUPDLYTIME, NULL},
	{"PwrUpDlyTimeFlag", 0, CJSON_INT, &CFGM_MCU_PWRUPDLYTIMEFLAG, NULL},
	{"DiagDlyTime", 0, CJSON_INT, &CFGM_MCU_DIAGDLYTIME, NULL},
	{"DiagDlyTimeFlag", 0, CJSON_INT, &CFGM_MCU_DIAGDLYTIMEFLAG, NULL},
	{"DiagVoltRangeMin", 0, CJSON_INT, &CFGM_MCU_DIAGVOLTRANGEMIN, NULL},
	{"DiagVoltRangeMinFlag", 0, CJSON_INT, &CFGM_MCU_DIAGVOLTRANGEMINFLAG, NULL},
	{"DiagVoltRangeMax", 0, CJSON_INT, &CFGM_MCU_DIAGVOLTRANGEMAX, NULL},
	{"DiagVoltRangeMaxFlag", 0, CJSON_INT, &CFGM_MCU_DIAGVOLTRANGEMAXFLAG, NULL},
	{"DiagHystsVoltUp", 0, CJSON_INT, &CFGM_MCU_DIAGHYSTSVOLTUP, NULL},
	{"DiagHystsVoltUpFlag", 0, CJSON_INT, &CFGM_MCU_DIAGHYSTSVOLTUPFLAG, NULL},
	{"DiagHystsVoltDown", 0,CJSON_INT, &CFGM_MCU_DIAGHYSTSVOLTDOWN, NULL},
	{"DiagHystsVoltDownFlag", 0,CJSON_INT, &CFGM_MCU_DIAGHYSTSVOLTDOWNFLAG, NULL},
};
#if 0
//AG35rCfg

static CfgM_MKeyInfoTable gtCfgM_Ag35MKeyTable[CFGM_BASIC_MKEY_NUM] = {
	{"BSMTx", CFGM_V2X_SKEY_BSMTX_NUM, CJSON_STRUCT, NULL, NULL},
	{"CertM", CFGM_V2X_SKEY_CERTM_NUM, CJSON_STRUCT, NULL, NULL},
};
#endif
//BasicInfo
static CfgM_MKeyInfoTable gtCfgM_BasicMKeyTable[CFGM_BASIC_MKEY_NUM] = {
	{"DeviceModel", 0, CJSON_STRING, NULL, CFGM_BASIC_DEVICEMODEL},
	{"DeviceId", 0, CJSON_STRING, NULL, CFGM_BASIC_DEVICEID},
	{"OEM", 0, CJSON_INT, &CFGM_BASIC_OEM, NULL},
	{"VehicleModel", 0, CJSON_INT, &CFGM_BASIC_VEHICLEMODEL, NULL},
};

//AppASCfg
static CfgM_MKeyInfoTable gtCfgM_APPASMKeyTable[CFGM_APPAS_MKEY_NUM] = {
	{"ASF_FCW", 0, CJSON_INT, &CFGM_APPAS_ASF_FCW, NULL},
	{"ASF_ICW", 0, CJSON_INT, &CFGM_APPAS_ASF_ICW, NULL},
	{"ASF_LTA", 0, CJSON_INT, &CFGM_APPAS_ASF_LTA, NULL},
	{"ASF_BSW", 0, CJSON_INT, &CFGM_APPAS_ASF_BSW, NULL},
	{"ASF_LCW", 0, CJSON_INT, &CFGM_APPAS_ASF_LCW, NULL},
	{"ASF_DNPW", 0, CJSON_INT, &CFGM_APPAS_ASF_DNPW, NULL},
	{"ASF_EBW", 0, CJSON_INT, &CFGM_APPAS_ASF_EBW, NULL},
	{"ASF_AVW", 0, CJSON_INT, &CFGM_APPAS_ASF_AVW, NULL},
	{"ASF_CLW", 0, CJSON_INT, &CFGM_APPAS_ASF_CLW, NULL},
	{"ASF_EVW", 0, CJSON_INT, &CFGM_APPAS_ASF_EVW, NULL},
	{"ASF_VRUCW", 0, CJSON_INT, &CFGM_APPAS_ASF_VRUCW, NULL},
	{"ASF_CVF", 0, CJSON_INT, &CFGM_APPAS_ASF_CVF, NULL},
	{"ASF_SVW", 0, CJSON_INT, &CFGM_APPAS_ASF_SVW, NULL},
	{"ASF_SLV", 0, CJSON_INT, &CFGM_APPAS_ASF_SLV, NULL},
	{"ASP_TTC", 0, CJSON_INT, &CFGM_APPAS_ASP_TTC, NULL},
	{"ASP_THC", 0, CJSON_INT, &CFGM_APPAS_ASP_THC, NULL},
	{"ASP_THR", 0, CJSON_INT, &CFGM_APPAS_ASP_THR, NULL},
	{"ASP_BLD_Angle", 0, CJSON_INT, &CFGM_APPAS_ASP_BLD_Angle, NULL},
	{"ASP_BLD_Width", 0, CJSON_INT, &CFGM_APPAS_ASP_BLD_Width, NULL},
	{"ASP_BLD_Mirror", 0, CJSON_INT, &CFGM_APPAS_ASP_BLD_Mirror, NULL},
	{"ASP_ACC_CFD", 0, CJSON_INT, &CFGM_APPAS_ASP_ACC_CFD, NULL},
	{"ASP_Yaw_CFD", 0, CJSON_INT, &CFGM_APPAS_ASP_Yaw_CFD, NULL},
	{"ASP_SLStop", 0, CJSON_INT, &CFGM_APPAS_ASP_SLStop, NULL},
	{"ASP_VehLOC_SafeDis", 0, CJSON_INT, &CFGM_APPAS_ASP_VEHLOC_SAFEDIS, NULL},
	{"ASP_ICW_SafeDis", 0, CJSON_INT, &CFGM_APPAS_ASP_ICW_SAFEDIS, NULL},
	{"ASP_ICW_TTC", 0, CJSON_INT, &CFGM_APPAS_ASP_ICW_TTC, NULL},
	{"ASP_AVW_Spd", 0, CJSON_INT, &CFGM_APPAS_ASP_AVW_SPD, NULL},
	{"ASP_SelfVeh_Dec", 0, CJSON_INT, &CFGM_APPAS_ASP_SELFVEH_DEC, NULL},
};

//AppMMCfg
static CfgM_MKeyInfoTable gtCfgM_APPMMMKeyTable[CFGM_APPMM_MKEY_NUM] = {
	{"MMF_RTS", 0, CJSON_INT, &CFGM_APPMM_MMF_RTS, NULL},
	{"MMF_RTE", 0, CJSON_INT, &CFGM_APPMM_MMF_RTE, NULL},
	{"MMF_SLW", 0, CJSON_INT, &CFGM_APPMM_MMF_SLW, NULL},
	{"MMF_TJW", 0, CJSON_INT, &CFGM_APPMM_MMF_TJW, NULL},
	{"MMP_PossTH", 0, CJSON_INT, &CFGM_APPMM_MMP_PossTH, NULL},
	{"MMP_LogIdx", 0, CJSON_INT, &CFGM_APPMM_MMP_LogIdx, NULL},
	{"MMP_DistTH", 0, CJSON_INT, &CFGM_APPMM_MMP_DistTH, NULL},
	{"MMP_AngTH", 0, CJSON_INT, &CFGM_APPMM_MMP_AngTH, NULL},
	{"MMP_HistTH", 0, CJSON_INT, &CFGM_APPMM_MMP_HistTH, NULL},
	{"MMP_FSTH", 0, CJSON_INT, &CFGM_APPMM_MMP_FSTH, NULL},
	{"MMP_SLStop", 0, CJSON_INT, &CFGM_APPMM_MMP_SLStop, NULL},
	{"SIP_Lon", 0, CJSON_INT, &CFGM_APPMM_SIP_LON, NULL},
	{"SIP_Lat", 0, CJSON_INT, &CFGM_APPMM_SIP_LAT, NULL},
	{"SIP_Speed", 0, CJSON_INT, &CFGM_APPMM_SIP_SPEED, NULL},
	{"SIP_Heading", 0, CJSON_INT, &CFGM_APPMM_SIP_HEADING, NULL},
	{"SIP_Length", 0, CJSON_INT, &CFGM_APPMM_SIP_LENGTH, NULL},
	{"SIP_Width", 0, CJSON_INT, &CFGM_APPMM_SIP_WIDTH, NULL},
	{"SIP_Evaluate", 0, CJSON_INT, &CFGM_APPMM_SIP_EVALUATE, NULL},
};

//AppMTCfg
static CfgM_MKeyInfoTable gtCfgM_APPMTMKeyTable[CFGM_APPMT_MKEY_NUM] = {
	{"MTF_BSM", 0, CJSON_INT, &CFGM_APPMT_MTF_BSM, NULL},
	{"MTF_RSM", 0, CJSON_INT, &CFGM_APPMT_MTF_RSM, NULL},
	{"MTP_Rel_Dist", 0, CJSON_INT, &CFGM_APPMT_MTP_Rel_Dist, NULL},
	{"MTP_Rel_Spd", 0, CJSON_INT, &CFGM_APPMT_MTP_Rel_Spd, NULL},
	{"MTP_Rel_Bear", 0, CJSON_INT, &CFGM_APPMT_MTP_Rel_Bear, NULL},
	{"MTP_Act_SpdH", 0, CJSON_INT, &CFGM_APPMT_MTP_Act_SpdH, NULL},
	{"MTP_Act_SpdL", 0, CJSON_INT, &CFGM_APPMT_MTP_Act_SpdL, NULL},
	{"MTP_Rel_Radio", 0, CJSON_INT, &CFGM_APPMT_MTP_Rel_Radio, NULL},
};

//AppTLCfg
static CfgM_MKeyInfoTable gtCfgM_APPTLMKeyTable[CFGM_APPTL_MKEY_NUM] = {
	{"TLF_GW", 0, CJSON_INT, &CFGM_APPTL_TLF_GW, NULL},
	{"TLF_RLW", 0, CJSON_INT, &CFGM_APPTL_TLF_RLW, NULL},
	{"TLP_GWSpdH", 0, CJSON_INT, &CFGM_APPTL_TLP_GWSpdH, NULL},
	{"TLP_GWSpdL", 0, CJSON_INT, &CFGM_APPTL_TLP_GWSpdL, NULL},
	{"TLP_GWDistW", 0, CJSON_INT, &CFGM_APPTL_TLP_GWDistW, NULL},
	{"TLP_GWTimeW", 0, CJSON_INT, &CFGM_APPTL_TLP_GWTimeW, NULL},
	{"TLP_StpLnDist", 0, CJSON_INT, &CFGM_APPTL_TLP_StpLnDist, NULL},
	{"TLP_NodeOffsetDist", 0, CJSON_INT, &CFGM_APPTL_TLP_NodeOffsetDist, NULL},
};


//V2xServer
static CfgM_SKeyInfoTable gtCfgM_V2XSKey_Table[CFGM_V2X_SKEY_NUM] = {
	{"wgs2gcj", CJSON_INT,&CFGM_V2XSERVER_WGS2GCJ, NULL},
	{"randId", CJSON_INT, &CFGM_V2XSERVER_RANDID, NULL},
	{"cbrCtrl", CJSON_INT, &CFGM_V2XSERVER_CBRCTRL, NULL},
	{"certUpdate", CJSON_INT, &CFGM_V2XSERVER_CERTUPDATE, NULL},
	{"hsmType", CJSON_INT, &CFGM_V2XSERVER_HSMTYPE, NULL},
	{"caPlatform", CJSON_INT, &CFGM_V2XSERVER_CAPLATFORM, NULL},
};

//VDSCfg
static CfgM_SKeyInfoTable gtCfgM_VDSSKey_Table[CFGM_VDS_SKEY_NUM] = {
	{"VehId", CJSON_STRING, NULL, CFGM_VDS_VEHID},
	{"VehType", CJSON_INT, &CFGM_VDS_VEHTYPE, NULL},
	{"VehLength", CJSON_STRING, NULL, CFGM_VDS_VEHLENGTH},
	{"VehWidth", CJSON_STRING, NULL, CFGM_VDS_VEHWIDTH},
	{"VehHigh", CJSON_STRING, NULL, CFGM_VDS_VEHHIGH},
	{"RtcmFlag", CJSON_STRING, NULL, CFGM_VDS_RtcmFlag},
	{"AK", CJSON_STRING, NULL, CFGM_VDS_AK},
	{"AS", CJSON_STRING, NULL, CFGM_VDS_AS},
	{"GPSName", CJSON_STRING, NULL, CFGM_VDS_GPSName},
	{"GPSName_W", CJSON_STRING, NULL, CFGM_VDS_GPSName_W},
	{"AppKey", CJSON_STRING, NULL, CFGM_VDS_AppKey},
	{"AppSectet", CJSON_STRING, NULL, CFGM_VDS_AppSectet},
	{"DevId", CJSON_STRING, NULL, CFGM_VDS_DevId},
	{"DevType", CJSON_STRING, NULL,CFGM_VDS_DevType}
};

//NetConfig
static CfgM_SKeyInfoTable gtCfgM_NETSKey_Table[CFGM_NET_SKEY_NUM] = {
	{"ServerPort", CJSON_INT, &CFGM_NET_SERVERPORT, NULL},
	{"MaxConnect", CJSON_INT, &CFGM_NET_MAXCONNECT, NULL},
	{"enable", CJSON_INT, &CFGM_NET_ENABLEUDP, NULL},
	{"DestIP", CJSON_STRING, NULL, CFGM_NET_DESTIP},
	{"DestPort", CJSON_INT, &CFGM_NET_DESTPORT, NULL},
	{"HostPort", CJSON_INT, &CFGM_NET_HOSTPORT, NULL},
};

#define CFGM_BASIC_MKEY_NAME_T(INDEX)     		     gtCfgM_BasicMKeyTable[INDEX].KeyName
#define CFGM_BASIC_MKEY_TYPE_T(INDEX)     		     gtCfgM_BasicMKeyTable[INDEX].Type
#define CFGM_BASIC_MKEY_INT_T(INDEX)     		   	 gtCfgM_BasicMKeyTable[INDEX].cJsonInit
#define CFGM_BASIC_MKEY_STRING_T(INDEX)     		 gtCfgM_BasicMKeyTable[INDEX].cJsonString
  

#define CFGM_V2X_MKEY_NAME_T(INDEX)       			 gtCfgM_V2XMKeyTable[INDEX].KeyName
#define CFGM_V2X_SKEY_NUM_T(INDEX)       			 gtCfgM_V2XMKeyTable[INDEX].SubKeyNum

#define CFGM_V2X_SKEY_NAME_T(INDEX)                     gtCfgM_V2XSKey_Table[INDEX].KeyName
#define CFGM_V2X_SKEY_TYPE_T(INDEX)             		gtCfgM_V2XSKey_Table[INDEX].Type
#define CFGM_V2X_SKEY_CJSONINT_T(INDEX)                 gtCfgM_V2XSKey_Table[INDEX].cJsonInit
#define CFGM_V2X_SKEY_CJSONSTRING_T(INDEX)              gtCfgM_V2XSKey_Table[INDEX].cJsonString


#define CFGM_VDS_MKEY_NAME_T(INDEX)      	    		gtCfgM_VDSMKeyTable[INDEX].KeyName
#define CFGM_VDS_SKEY_NUM_T(INDEX)          			gtCfgM_VDSMKeyTable[INDEX].SubKeyNum

#define CFGM_VDS_SKEY_NAME_T(INDEX)              	    gtCfgM_VDSSKey_Table[INDEX].KeyName
#define CFGM_VDS_SKEY_TYPE_T(INDEX)             		gtCfgM_VDSSKey_Table[INDEX].Type
#define CFGM_VDS_SKEY_CJSONINT_T(INDEX)                 gtCfgM_VDSSKey_Table[INDEX].cJsonInit
#define CFGM_VDS_SKEY_CJSONSTRING_T(INDEX)              gtCfgM_VDSSKey_Table[INDEX].cJsonString

#define CFGM_MCU_MKEY_NAME_T(INDEX)     		     gtCfgM_MCUMKeyTable[INDEX].KeyName
#define CFGM_MCU_MKEY_TYPE_T(INDEX)     		     gtCfgM_MCUMKeyTable[INDEX].Type
#define CFGM_MCU_MKEY_INT_T(INDEX)     		   	     gtCfgM_MCUMKeyTable[INDEX].cJsonInit
#define CFGM_MCU_MKEY_STRING_T(INDEX)     		     gtCfgM_MCUMKeyTable[INDEX].cJsonString


#define CFGM_NET_MKEY_NAME_T(INDEX)          		 gtCfgM_NetMKeyTable[INDEX].KeyName
#define CFGM_NET_SKEY_NUM_T(INDEX)          		 gtCfgM_NetMKeyTable[INDEX].SubKeyNum
#define CFGM_NET_MKEY_TYPE_T(INDEX)          		 gtCfgM_NetMKeyTable[INDEX].Type
#define CFGM_NET_MKEY_CJSONINT_T(INDEX)              gtCfgM_NetMKeyTable[INDEX].cJsonInit
#define CFGM_NET_MKEY_CJSONSTRING_T(INDEX)           gtCfgM_NetMKeyTable[INDEX].cJsonString

#define CFGM_NET_SKEY_NAME_T(INDEX)              	 gtCfgM_NETSKey_Table[INDEX].KeyName
#define CFGM_NET_SKEY_TYPE_T(INDEX)             	 gtCfgM_NETSKey_Table[INDEX].Type
#define CFGM_NET_SKEY_CJSONINT_T(INDEX)              gtCfgM_NETSKey_Table[INDEX].cJsonInit
#define CFGM_NET_SKEY_CJSONSTRING_T(INDEX)           gtCfgM_NETSKey_Table[INDEX].cJsonString



#define CFGM_APPAS_MKEY_NAME_T(INDEX)          		 gtCfgM_APPASMKeyTable[INDEX].KeyName
#define CFGM_APPAS_MKEY_TYPE_T(INDEX)          		 gtCfgM_APPASMKeyTable[INDEX].Type
#define CFGM_APPAS_MKEY_CJSONINT_T(INDEX)            gtCfgM_APPASMKeyTable[INDEX].cJsonInit
#define CFGM_APPAS_MKEY_CJSONSTRING_T(INDEX)         gtCfgM_APPASMKeyTable[INDEX].cJsonString

#define CFGM_APPMM_MKEY_NAME_T(INDEX)          		 gtCfgM_APPMMMKeyTable[INDEX].KeyName
#define CFGM_APPMM_MKEY_TYPE_T(INDEX)          		 gtCfgM_APPMMMKeyTable[INDEX].Type
#define CFGM_APPMM_MKEY_CJSONINT_T(INDEX)            gtCfgM_APPMMMKeyTable[INDEX].cJsonInit
#define CFGM_APPMM_MKEY_CJSONSTRING_T(INDEX)         gtCfgM_APPMMMKeyTable[INDEX].cJsonString

#define CFGM_APPMT_MKEY_NAME_T(INDEX)          		 gtCfgM_APPMTMKeyTable[INDEX].KeyName
#define CFGM_APPMT_MKEY_TYPE_T(INDEX)          		 gtCfgM_APPMTMKeyTable[INDEX].Type
#define CFGM_APPMT_MKEY_CJSONINT_T(INDEX)            gtCfgM_APPMTMKeyTable[INDEX].cJsonInit
#define CFGM_APPMT_MKEY_CJSONSTRING_T(INDEX)         gtCfgM_APPMTMKeyTable[INDEX].cJsonString

#define CFGM_APPTL_MKEY_NAME_T(INDEX)          		 gtCfgM_APPTLMKeyTable[INDEX].KeyName
#define CFGM_APPTL_MKEY_TYPE_T(INDEX)          		 gtCfgM_APPTLMKeyTable[INDEX].Type
#define CFGM_APPTL_MKEY_CJSONINT_T(INDEX)            gtCfgM_APPTLMKeyTable[INDEX].cJsonInit
#define CFGM_APPTL_MKEY_CJSONSTRING_T(INDEX)         gtCfgM_APPTLMKeyTable[INDEX].cJsonString

typedef enum  _t_CfgMRetFlag
{
	CFGM_SUCCESS,
	CFGM_FALSE,
} t_CfgMRetFlag;

#endif
