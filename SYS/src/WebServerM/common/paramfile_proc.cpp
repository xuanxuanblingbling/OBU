#include "web_common.h"
#include "string_conv.h"
#include "../web_service/http_server.h"
#include "../web_service/http_handler.h"
#include <fstream>
#include <stdio.h>
#include "Cfg.h"  

#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdlib.h>
#include <sys/file.h> 
#include <unistd.h>

#define MAXINTERFACES 10    		/* 最大接口数 */
 
int fd;         					/* 套接字 */
int if_len;     					/* 接口数量 */
struct ifreq buf[MAXINTERFACES];    /* ifreq结构数组 */
struct ifconf ifc; 

#define INTERFACE			"wlan0"
#define WIFINAMEADDR		"/etc/hostapd-80211n-2G.conf"
#define VERSIONNAMEADDR		"/mnt/APP/Config/obu/DevInfo/DevInfo.json"

#define FILETYPEINI    1
#define FILETYPEJSON   0

/*
	ini.SetValue("section", "key", sconv("这是一个汉字测试").c_str());
	ini.SaveFile("KeyTest_Down1.ini");
*/

CfgM_Json g_tJsonInfo;

//BasicInfo
void to_json(json& p_j, const CfgM_BasicInfo& p_tData)
{
	p_j = json{ { "DeviceModel", p_tData.DeviceModel},
	{"DeviceId", p_tData.DeviceId},
	{ "OEM", p_tData.OEM},
	{"VehicleModel", p_tData.VehicleModel}};
}

void from_json(const json& p_j, CfgM_BasicInfo& p_tData)
{
	GetJsonCStr(p_j, "DeviceModel", "", p_tData.DeviceModel);
	GetJsonCStr(p_j, "DeviceId", "", p_tData.DeviceId);
	p_tData.OEM = GetJsonCInt(p_j, "OEM", "");
	p_tData.VehicleModel = GetJsonCInt(p_j, "VehicleModel", "");
}


//V2XServerCfg
void to_json(json& p_j, const CfgM_V2XServerCfg& p_tData)
{
	p_j = json{
		{"BSMTx", {{"wgs2gcj",p_tData.wgs2gcj},{"randId", p_tData.randId},{"cbrCtrl",p_tData.cbrCtrl}}},
		{"CertM", {{"certUpdate",p_tData.certUpdate},{"hsmType", p_tData.hsmType},{"caPlatform",p_tData.caPlatform}}}
	};
}

void from_json(const json& p_j, CfgM_V2XServerCfg& p_tData)
{
	p_tData.wgs2gcj = GetJsonCInt(p_j, "BSMTx", "wgs2gcj");
	p_tData.randId = GetJsonCInt(p_j, "BSMTx", "randId");
	p_tData.cbrCtrl = GetJsonCInt(p_j, "BSMTx", "cbrCtrl");
	p_tData.certUpdate = GetJsonCInt(p_j, "CertM", "certUpdate");
	p_tData.hsmType = GetJsonCInt(p_j, "CertM", "hsmType");
	p_tData.caPlatform = GetJsonCInt(p_j, "CertM", "caPlatform");
}

//VDSCfg
void to_json(json& p_j, const CfgM_VDSCfg& p_tData)
{
	p_j = json{
		{"VEH", {{"VehId", p_tData.VehId},{"VehType", p_tData.VehType},{"VehLength", p_tData.VehLength},{"VehWidth", p_tData.VehWidth},{"VehHigh", p_tData.VehHigh}}},
		{"GNSS", {{"LocationType",p_tData.RtcmFlag}}},
		{"QXWZ", {{"AK", p_tData.AK},{"AS", p_tData.AS},{"DevId", p_tData.DevId},{"DevType", p_tData.DevType}}}
	};
}

void from_json(const json& p_j, CfgM_VDSCfg& p_tData)
{
	GetJsonCStr(p_j, "VEH", "VehId", p_tData.VehId);
	p_tData.VehType = GetJsonCInt(p_j, "VEH", "VehType");
	GetJsonCStr(p_j, "VEH", "VehLength", p_tData.VehLength);
	GetJsonCStr(p_j, "VEH", "VehWidth", p_tData.VehWidth);
	GetJsonCStr(p_j, "VEH", "VehHigh", p_tData.VehHigh);
     
	// p_tData.VehLength = GetJsonCInt(p_j, "VEH", "VehLength");
	// p_tData.VehWidth = GetJsonCInt(p_j, "VEH", "VehWidth");
	// p_tData.VehHigh = GetJsonCInt(p_j, "VEH", "VehHigh");
	//p_tData.LocationType = GetJsonCInt(p_j, "GNSS", "RtcmFlag");
	GetJsonCStr(p_j, "GNSS", "RtcmFlag", p_tData.RtcmFlag);
	GetJsonCStr(p_j, "QXWZ", "AK", p_tData.AK);
	GetJsonCStr(p_j, "QXWZ", "AS", p_tData.AS);
	GetJsonCStr(p_j, "QXWZ", "GPSName", p_tData.GPSName);
	GetJsonCStr(p_j, "QXWZ", "GPSName_W", p_tData.GPSName_W);
	GetJsonCStr(p_j, "QXWZ", "AppKey", p_tData.AppKey);
	GetJsonCStr(p_j, "QXWZ", "AppSectet", p_tData.AppSectet);
	// GetJsonCStr(p_j, "QXWZ", "DevId", p_tData.DevId);
	// GetJsonCStr(p_j, "QXWZ", "DevType", p_tData.DevType);
}

//MCUCfg
void to_json(json& p_j, const CfgM_MCUCfg& p_tData)
{
	p_j = json{ { "PwrUpDlyTime", p_tData.PwrUpDlyTime},
	{ "PwrUpDlyTimeFlag", p_tData.PwrUpDlyTimeFlag},
	{"DiagDlyTime", p_tData.DiagDlyTime},
	{"DiagDlyTimeFlag", p_tData.DiagDlyTimeFlag},
	{ "DiagVoltRangeMin", p_tData.DiagVoltRangeMin},
	{ "DiagVoltRangeMinFlag", p_tData.DiagVoltRangeMinFlag},
	{"DiagVoltRangeMax", p_tData.DiagVoltRangeMax},
	{"DiagVoltRangeMaxFlag", p_tData.DiagVoltRangeMaxFlag},
	{ "DiagHystsVoltUp", p_tData.DiagHystsVoltUp},
	{ "DiagHystsVoltUpFlag", p_tData.DiagHystsVoltUpFlag},
	{"DiagHystsVoltDown", p_tData.DiagHystsVoltDown},
	{"DiagHystsVoltDownFlag", p_tData.DiagHystsVoltDownFlag}};
}

void from_json(const json& p_j, CfgM_MCUCfg& p_tData)
{
	p_tData.PwrUpDlyTime = GetJsonCInt(p_j, "PwrUpDlyTime", "");
	p_tData.PwrUpDlyTimeFlag = GetJsonCInt(p_j, "PwrUpDlyTimeFlag", "");
	p_tData.DiagDlyTime = GetJsonCInt(p_j, "DiagDlyTime", "");
	p_tData.DiagDlyTimeFlag = GetJsonCInt(p_j, "DiagDlyTimeFlag", "");
	p_tData.DiagVoltRangeMin = GetJsonCInt(p_j, "DiagVoltRangeMin", "");
	p_tData.DiagVoltRangeMinFlag = GetJsonCInt(p_j, "DiagVoltRangeMinFlag", "");
	p_tData.DiagVoltRangeMax = GetJsonCInt(p_j, "DiagVoltRangeMax", "");
	p_tData.DiagVoltRangeMaxFlag = GetJsonCInt(p_j, "DiagVoltRangeMaxFlag", "");
	p_tData.DiagHystsVoltUp = GetJsonCInt(p_j, "DiagHystsVoltUp", "");
	p_tData.DiagHystsVoltUpFlag = GetJsonCInt(p_j, "DiagHystsVoltUpFlag", "");
	p_tData.DiagHystsVoltDown = GetJsonCInt(p_j, "DiagHystsVoltDown", "");
	p_tData.DiagHystsVoltDownFlag = GetJsonCInt(p_j, "DiagHystsVoltDownFlag", "");
}

//AppCfg ,四个设置，这里需要分成四部分，分别传值
//ActiveSafety
void to_json(json& p_j, const CfgM_AppASCfg& p_tData)
{
	p_j = json{ { "ASF_FCW", p_tData.ASF_FCW},
	{"ASF_ICW", p_tData.ASF_ICW},
	{ "ASF_LTA", p_tData.ASF_LTA},
	{"ASF_BSW", p_tData.ASF_BSW},
	{ "ASF_LCW", p_tData.ASF_LCW},
	{"ASF_DNPW", p_tData.ASF_DNPW},
	{"ASF_EBW", p_tData.ASF_EBW},
	{ "ASF_AVW", p_tData.ASF_AVW},
	{"ASF_CLW", p_tData.ASF_CLW},
	{ "ASF_EVW", p_tData.ASF_EVW},
	{"ASF_VRUCW", p_tData.ASF_VRUCW},
	{"ASF_CVF", p_tData.ASF_CVF},
	{ "ASF_SVW", p_tData.ASF_SVW},
	{"ASF_SLV", p_tData.ASF_SLV},
	{ "ASP_TTC", p_tData.ASP_TTC},
	{"ASP_THC", p_tData.ASP_THC},
	{"ASP_THR", p_tData.ASP_THR},
	{ "ASP_BLD_Angle", p_tData.ASP_BLD_Angle},
	{"ASP_BLD_Width", p_tData.ASP_BLD_Width},
	{ "ASP_BLD_Mirror", p_tData.ASP_BLD_Mirror},
	{"ASP_ACC_CFD", p_tData.ASP_ACC_CFD},
	{"ASP_Yaw_CFD", p_tData.ASP_Yaw_CFD},
	{ "ASP_SLStop", p_tData.ASP_SLStop},
	{"ASP_VehLOC_SafeDis", p_tData.ASP_VehLOC_SafeDis},
	{ "ASP_ICW_SafeDis", p_tData.ASP_ICW_SafeDis},
	{"ASP_ICW_TTC", p_tData.ASP_ICW_TTC},
	{"ASP_AVW_Spd", p_tData.ASP_AVW_Spd},
	{ "ASP_SelfVeh_Dec", p_tData.ASP_SelfVeh_Dec}};
}


void from_json(const json& p_j, CfgM_AppASCfg& p_tData)
{
	p_tData.ASF_FCW = GetJsonCInt(p_j, "ASF_FCW", "");
	p_tData.ASF_ICW = GetJsonCInt(p_j, "ASF_ICW", "");
	p_tData.ASF_LTA = GetJsonCInt(p_j, "ASF_LTA", "");
	p_tData.ASF_BSW = GetJsonCInt(p_j, "ASF_BSW", "");
	p_tData.ASF_LCW = GetJsonCInt(p_j, "ASF_LCW", "");
	p_tData.ASF_DNPW = GetJsonCInt(p_j, "ASF_DNPW", "");
	p_tData.ASF_EBW = GetJsonCInt(p_j, "ASF_EBW", "");
	p_tData.ASF_AVW = GetJsonCInt(p_j, "ASF_AVW", "");
	p_tData.ASF_CLW = GetJsonCInt(p_j, "ASF_CLW", "");
	p_tData.ASF_EVW = GetJsonCInt(p_j, "ASF_EVW", "");
	p_tData.ASF_VRUCW = GetJsonCInt(p_j, "ASF_VRUCW", "");
	p_tData.ASF_CVF = GetJsonCInt(p_j, "ASF_CVF", "");
	p_tData.ASF_SVW = GetJsonCInt(p_j, "ASF_SVW", "");
	p_tData.ASF_SLV = GetJsonCInt(p_j, "ASF_SLV", "");
	p_tData.ASP_TTC = GetJsonCInt(p_j, "ASP_TTC", "");
	p_tData.ASP_THC = GetJsonCInt(p_j, "ASP_THC", "");
	p_tData.ASP_THR = GetJsonCInt(p_j, "ASP_THR", "");
	p_tData.ASP_BLD_Angle = GetJsonCInt(p_j, "ASP_BLD_Angle", "");
	p_tData.ASP_BLD_Width = GetJsonCInt(p_j, "ASP_BLD_Width", "");
	p_tData.ASP_BLD_Mirror = GetJsonCInt(p_j, "ASP_BLD_Mirror", "");
	p_tData.ASP_ACC_CFD = GetJsonCInt(p_j, "ASP_ACC_CFD", "");
	p_tData.ASP_Yaw_CFD = GetJsonCInt(p_j, "ASP_Yaw_CFD", "");
	p_tData.ASP_SLStop = GetJsonCInt(p_j, "ASP_SLStop", "");
	p_tData.ASP_VehLOC_SafeDis = GetJsonCInt(p_j, "ASP_VehLOC_SafeDis", "");
	p_tData.ASP_ICW_SafeDis = GetJsonCInt(p_j, "ASP_ICW_SafeDis", "");
	p_tData.ASP_ICW_TTC = GetJsonCInt(p_j, "ASP_ICW_TTC", "");
	p_tData.ASP_AVW_Spd = GetJsonCInt(p_j, "ASP_AVW_Spd", "");
	p_tData.ASP_SelfVeh_Dec = GetJsonCInt(p_j, "ASP_SelfVeh_Dec", "");
}

//MapMatch
void to_json(json& p_j, const CfgM_AppMMCfg& p_tData)
{
	p_j = json{ { "MMF_RTS", p_tData.MMF_RTS},
	{"MMF_RTE", p_tData.MMF_RTE},
	{ "MMF_SLW", p_tData.MMF_SLW},
	{"MMF_TJW", p_tData.MMF_TJW},
	{ "MMP_PossTH", p_tData.MMP_PossTH},
	{"MMP_LogIdx", p_tData.MMP_LogIdx},
	{"MMP_DistTH", p_tData.MMP_DistTH},
	{ "MMP_AngTH", p_tData.MMP_AngTH},
	{"MMP_HistTH", p_tData.MMP_HistTH},
	{ "MMP_FSTH", p_tData.MMP_FSTH},
	{"MMP_SLStop", p_tData.MMP_SLStop},
	{ "SIP_Lon", p_tData.SIP_Lon},
	{"SIP_Lat", p_tData.SIP_Lat},
	{"SIP_Speed", p_tData.SIP_Speed},
	{ "SIP_Heading", p_tData.SIP_Heading},
	{"SIP_Length", p_tData.SIP_Length},
	{ "SIP_Width", p_tData.SIP_Width},
	{"SIP_Evaluate", p_tData.SIP_Evaluate}};
}


void from_json(const json& p_j, CfgM_AppMMCfg& p_tData)
{
	p_tData.MMF_RTS = GetJsonCInt(p_j, "MMF_RTS", "");
	p_tData.MMF_RTE = GetJsonCInt(p_j, "MMF_RTE", "");
	p_tData.MMF_SLW = GetJsonCInt(p_j, "MMF_SLW", "");
	p_tData.MMF_TJW = GetJsonCInt(p_j, "MMF_TJW", "");
	p_tData.MMP_PossTH = GetJsonCInt(p_j, "MMP_PossTH", "");
	p_tData.MMP_LogIdx = GetJsonCInt(p_j, "MMP_LogIdx", "");
	p_tData.MMP_DistTH = GetJsonCInt(p_j, "MMP_DistTH", "");
	p_tData.MMP_AngTH = GetJsonCInt(p_j, "MMP_AngTH", "");
	p_tData.MMP_HistTH = GetJsonCInt(p_j, "MMP_HistTH", "");
	p_tData.MMP_FSTH = GetJsonCInt(p_j, "MMP_FSTH", "");
	p_tData.MMP_SLStop = GetJsonCInt(p_j, "MMP_SLStop", "");
	p_tData.SIP_Lon = GetJsonCInt(p_j, "SIP_Lon", "");
	p_tData.SIP_Lat = GetJsonCInt(p_j, "SIP_Lat", "");
	p_tData.SIP_Speed = GetJsonCInt(p_j, "SIP_Speed", "");
	p_tData.SIP_Heading = GetJsonCInt(p_j, "SIP_Heading", "");
	p_tData.SIP_Length = GetJsonCInt(p_j, "SIP_Length", "");
	p_tData.SIP_Width = GetJsonCInt(p_j, "SIP_Width", "");
	p_tData.SIP_Evaluate = GetJsonCInt(p_j, "SIP_Evaluate", "");
}

//MaintainInfo
void to_json(json& p_j, const CfgM_AppMTCfg& p_tData)
{
	p_j = json{ { "MTF_BSM", p_tData.MTF_BSM},
	{"MTF_RSM", p_tData.MTF_RSM},
	{ "MTP_Rel_Dist", p_tData.MTP_Rel_Dist},
	{"MTP_Rel_Spd", p_tData.MTP_Rel_Spd},
	{ "MTP_Rel_Bear", p_tData.MTP_Rel_Bear},
	{"MTP_Act_SpdH", p_tData.MTP_Act_SpdH},
	{"MTP_Act_SpdL", p_tData.MTP_Act_SpdL},
	{ "MTP_Rel_Radio", p_tData.MTP_Rel_Radio}};
}


void from_json(const json& p_j, CfgM_AppMTCfg& p_tData)
{
	p_tData.MTF_BSM = GetJsonCInt(p_j, "MTF_BSM", "");
	p_tData.MTF_RSM = GetJsonCInt(p_j, "MTF_RSM", "");
	p_tData.MTP_Rel_Dist = GetJsonCInt(p_j, "MTP_Rel_Dist", "");
	p_tData.MTP_Rel_Spd = GetJsonCInt(p_j, "MTP_Rel_Spd", "");
	p_tData.MTP_Rel_Bear = GetJsonCInt(p_j, "MTP_Rel_Bear", "");
	p_tData.MTP_Act_SpdH = GetJsonCInt(p_j, "MTP_Act_SpdH", "");
	p_tData.MTP_Act_SpdL = GetJsonCInt(p_j, "MTP_Act_SpdL", "");
	p_tData.MTP_Rel_Radio = GetJsonCInt(p_j, "MTP_Rel_Radio", "");
}

//GWSpeedGuide
void to_json(json& p_j, const CfgM_AppTLCfg& p_tData)
{
	p_j = json{ { "TLF_GW", p_tData.TLF_GW},
	{"TLF_RLW", p_tData.TLF_RLW},
	{ "TLP_GWSpdH", p_tData.TLP_GWSpdH},
	{"TLP_GWSpdL", p_tData.TLP_GWSpdL},
	{ "TLP_GWDistW", p_tData.TLP_GWDistW},
	{"TLP_GWTimeW", p_tData.TLP_GWTimeW},
	{"TLP_StpLnDist", p_tData.TLP_StpLnDist},
	{ "TLP_NodeOffsetDist", p_tData.TLP_NodeOffsetDist}};
}


void from_json(const json& p_j, CfgM_AppTLCfg& p_tData)
{
	p_tData.TLF_GW = GetJsonCInt(p_j, "TLF_GW", "");
	p_tData.TLF_RLW = GetJsonCInt(p_j, "TLF_RLW", "");
	p_tData.TLP_GWSpdH = GetJsonCInt(p_j, "TLP_GWSpdH", "");
	p_tData.TLP_GWSpdL = GetJsonCInt(p_j, "TLP_GWSpdL", "");
	p_tData.TLP_GWDistW = GetJsonCInt(p_j, "TLP_GWDistW", "");
	p_tData.TLP_GWTimeW = GetJsonCInt(p_j, "TLP_GWTimeW", "");
	p_tData.TLP_StpLnDist = GetJsonCInt(p_j, "TLP_StpLnDist", "");
	p_tData.TLP_NodeOffsetDist = GetJsonCInt(p_j, "TLP_NodeOffsetDist", "");
}

//NetCfg
void to_json(json& p_j, const CfgM_NetCfg& p_tData)
{
	p_j = json{ 
		{"TcpServer", {{"ServerPort",p_tData.ServerPort},{"MaxConnect", p_tData.MaxConnect}}},
		{"UDP", {{"enable",p_tData.enableUDP},{"DestIP", p_tData.DestIP},{"DestPort",p_tData.DestPort},{"HostPort", p_tData.HostPort}}},
		{ "CheckPeriod", p_tData.CheckPeriod}};
}

void from_json(const json& p_j, CfgM_NetCfg& p_tData)
{
	p_tData.ServerPort = GetJsonCInt(p_j, "TcpServer", "ServerPort");	
	p_tData.MaxConnect = GetJsonCInt(p_j, "TcpServer", "MaxConnect");
	p_tData.enableUDP = GetJsonCInt(p_j, "UDP", "enable");
	GetJsonCStr(p_j, "UDP", "DestIP", p_tData.DestIP);
	p_tData.DestPort = GetJsonCInt(p_j, "UDP", "DestPort");
	p_tData.HostPort = GetJsonCInt(p_j, "UDP", "HostPort");
	p_tData.CheckPeriod = GetJsonCInt(p_j, "CheckPeriod", "");
}

//ModuleCfg--暂时不使用
void to_json(json& p_j, const CfgM_ModuleCfg& p_tData)
{
	p_j = json{
		{"MCfg", {{"ModuleConfig",p_tData.tModuleConfig}}},
	};
}

void from_json(const json& p_j, CfgM_ModuleCfg& p_tData)
{
	p_tData.tModuleConfig = GetJsonCInt(p_j, "MCfg", "ModuleConfig");
}

 
void ProcJsonDataSetToStruct(struct mg_connection* p_pConn, int p_nJsonNum, json &p_jData, HttpServer * p_pHttpServer)
{
	//多个to_json和from_json可以放在一个文件中，但是形参结构体应不同。
	json l_jResData;

	l_jResData["Operation"] = "set";
	l_jResData["ModuleName"] = p_jData["ModuleName"];
	l_jResData["Source"] = GenerWebSign;


    string l_strType = p_jData["ConfigType"];

	printf("====[test] p_jData json %s ====\n",p_jData["QXWZ"]["AK"].dump().c_str());

	//结构体的传值
	switch (p_nJsonNum)
	{
	case JSON_BASICINFO :
		g_tJsonInfo.BasicInfo = p_jData;
		g_tJsonInfo.CfgFileId = BASICINFO_FILE;
		break;
	case JSON_V2XSERVICE :
		g_tJsonInfo.V2XServerCfg = p_jData;
		g_tJsonInfo.CfgFileId = V2XSERVERCFG_FILE;
		break;
	case JSON_VDSMODULE:
		g_tJsonInfo.VDSCfg = p_jData;
		g_tJsonInfo.CfgFileId = VDSCFG_FILE;
		break;
	case JSON_MCUMODULE:
		g_tJsonInfo.MCUCfg = p_jData;
		g_tJsonInfo.CfgFileId = MCUCFG_FILE;
		break;
	case JSON_APPASCFG:
		g_tJsonInfo.AppASCfg = p_jData;
		g_tJsonInfo.CfgFileId = APPASCFG_FILE;
		break;
	case JSON_APPMMCFG:
		g_tJsonInfo.AppMMCfg = p_jData;
		g_tJsonInfo.CfgFileId = APPMMCFG_FILE;
		break;
	case JSON_APPMTCFG:
		g_tJsonInfo.AppMTCfg = p_jData;
		g_tJsonInfo.CfgFileId = APPMTCFG_FILE;
		break;
	case JSON_APPTLCFG:
		g_tJsonInfo.AppTLCfg = p_jData;
		g_tJsonInfo.CfgFileId = APPTLCFG_FILE;
		break;
	case JSON_NETWORKMODULE:
		g_tJsonInfo.NetCfg = p_jData;
		g_tJsonInfo.CfgFileId = NETCONFIG_FILE;
		break;
	case JSON_MODULECONFIG:
		g_tJsonInfo.ModuleCfg.tModuleConfig = GetJsonIntData(p_jData, "ModuleConfig");
		g_tJsonInfo.CfgFileId = MODULE_CONFIG_FILE;
		updateModuleConfig(p_pConn, p_jData, g_tJsonInfo.ModuleCfg.tModuleConfig);
		break;
	default:
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Parameter setting failed");
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("参数设置失败!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
	LogPrint(LOG_LEVEL_INFO,LOG_MODLE_NAME, "ProcJsonDataSetToStruct %d",g_tJsonInfo.CfgFileId);
	if(p_nJsonNum == JSON_MCUMODULE)
	{
		if((!g_tJsonInfo.MCUCfg.PwrUpDlyTimeFlag) && (!g_tJsonInfo.MCUCfg.DiagDlyTimeFlag) && (!g_tJsonInfo.MCUCfg.DiagVoltRangeMinFlag) && 
			(!g_tJsonInfo.MCUCfg.DiagVoltRangeMaxFlag) && (!g_tJsonInfo.MCUCfg.DiagHystsVoltUpFlag) && (!g_tJsonInfo.MCUCfg.DiagHystsVoltDownFlag))
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MCU all the number is zero");
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("不允许所有参数为无效值!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}

	Set_Json_Struct(CFGM_JSON_STRUCT, &g_tJsonInfo);
	
	SET_SIGNAL_B(PARAMETER_CFG_WEB_RQ);
	
	int l_iSemResult = 0;

	l_iSemResult = GET_SIGNAL_NB(PARAMETER_CFG_WEB_RESP, 500);
	if(l_iSemResult == 0)
	{
		l_jResData["result"] = "success";
		l_jResData["message"] = sconv("参数设置成功!");
		return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
	}
	if(l_iSemResult==-1)
	{
		//给模块再回复一个信号
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Parameter setting failed");
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("参数设置失败!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}
}

bool IniDataToJson(const CSimpleIniA &p_iniFile, std::vector<std::string> &p_vSection, json &p_jData)
{
	bool l_Flag = false;
	cout << "p_vSection.size:" << p_vSection.size() << endl;
	if (p_vSection.size())
	{
		for (auto l_sec = p_vSection.begin(); l_sec != p_vSection.end(); l_sec++)
		{
			json l_jTemp;
			l_jTemp.clear();
			CSimpleIniA::TNamesDepend l_keys;
			p_iniFile.GetAllKeys(l_sec->c_str(), l_keys);
			for (auto l_key = l_keys.begin(); l_key != l_keys.end(); l_key++)
			{
				string l_strValue = p_iniFile.GetValue(l_sec->c_str(), l_key->pItem, "");
				l_jTemp[string(l_key->pItem)] = l_strValue;
				l_Flag = true;
			}
			if (l_keys.size())
				p_jData[*l_sec] = l_jTemp;
			else
				p_jData[*l_sec] = "";
		}
	}
	else
	{
		CSimpleIniA::TNamesDepend l_sections;
		p_iniFile.GetAllSections(l_sections);
		for (auto l_sec = l_sections.begin(); l_sec != l_sections.end(); l_sec++)
		{
			json l_jTemp;
			l_jTemp.clear();
			CSimpleIniA::TNamesDepend l_keys;
			p_iniFile.GetAllKeys(l_sec->pItem, l_keys);
			for (auto l_key = l_keys.begin(); l_key != l_keys.end(); l_key++)
			{
				l_Flag = true;
				string l_strValue = p_iniFile.GetValue(l_sec->pItem, l_key->pItem, "");
				l_jTemp[string(l_key->pItem)] = l_strValue;
			}
			p_jData[string(l_sec->pItem)] = l_jTemp;
		}
	}
	return l_Flag;
}



bool JsonDataToIni(const json &p_jData, std::vector<std::string> &p_vSection, CSimpleIniA &p_iniFile)
{
	bool l_Flag = false;
	p_iniFile.SetMultiKey(false);
	p_iniFile.SetSpaces(false);
	if (p_vSection.size())  //有节点的区分，下边是没有节点的情况
	{
		for (auto l_sec = p_vSection.begin(); l_sec != p_vSection.end(); l_sec++)
		{
			if (p_jData.contains(*l_sec))
			{
				string l_strData = p_jData[*l_sec].get<string>();
				try
				{
					json l_jTemp = json::parse(l_strData);
					for (auto it = l_jTemp.begin(); it != l_jTemp.end(); ++it)
					{
						l_Flag = true;
						p_iniFile.SetValue((*l_sec).c_str(), it.key().c_str(), it.value().get<string>().c_str());
					}
				}
				catch (...)
				{
					;
				}
			}
		}
	}
	else
	{
		for (auto k = p_jData.begin(); k != p_jData.end(); ++k)
		{
			try
			{
				json l_jTemp = k.value();
				for (auto it = l_jTemp.begin(); it != l_jTemp.end(); ++it)
				{
					l_Flag = true;
					p_iniFile.SetValue(k.key().c_str(), it.key().c_str(), it.value().get<string>().c_str());
				}
			}
			catch (...)
			{
				continue;
			}
		}
	}
	return l_Flag;
}


std::string MacToStr(unsigned char * pMac,const char chKen/* = ':'*/)  
{  
    char szFormat[] = "%02X:%02X:%02X:%02X:%02X:%02X";  
    int nLen = strlen(szFormat);  
    if (chKen != ':')  
    {  
        for (int i = 2;i < nLen;i += 3)  
        {  
            szFormat[i] = chKen;  
        }  
    }  
  
    char szMac[32] = {0};  
    sprintf(szMac, szFormat, pMac[0], pMac[1], pMac[2], pMac[3], pMac[4], pMac[5]);  
    std::string strRet(szMac);  
    return strRet;  
}

int network(std::vector<std::string> &p_vRet)
{
    string l_strInerface;
    string l_strIpAddr;
    string l_strNetMask;
    string l_strBrAddr;
    string l_strMacAddr;


    /* 建立IPv4的UDP套接字fd */
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket(AF_INET, SOCK_DGRAM, 0)");
        close(fd);
        return -1;
    }

    /* 初始化ifconf结构 */
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = (caddr_t) buf;
 
    /* 获得接口列表 */
    if (ioctl(fd, SIOCGIFCONF, (char *) &ifc) == -1)
    {
        perror("SIOCGIFCONF ioctl");
        close(fd);
        return -1;
    }
 
    if_len = ifc.ifc_len / sizeof(struct ifreq); /* 接口数量 */
	LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "static info interfaces number:%d", if_len);
 
    for(if_len=if_len-1;if_len>=0;if_len--)/* 遍历每个接口 */
    {   
        /* 接口名称 */
        l_strInerface=string(buf[if_len].ifr_name);
		LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "static info interfaces name:%s", l_strInerface.c_str());

        if(l_strInerface == INTERFACE)
        {
            /* IP地址 */
            if (!(ioctl(fd, SIOCGIFADDR, (char *) &buf[if_len])))
            {
                l_strIpAddr=string((char*)inet_ntoa(((struct sockaddr_in*) (&buf[if_len].ifr_addr))->sin_addr));
				LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "static info interfaces ip addr:%s", l_strIpAddr.c_str());
            }
            else
            {
                perror("SIOCGIFADDR ioctl fail");
                close(fd);
                return -1;
            }
    
            /* 子网掩码 */
            if (!(ioctl(fd, SIOCGIFNETMASK, (char *) &buf[if_len])))
            {
                l_strNetMask=string((char*)inet_ntoa(((struct sockaddr_in*) (&buf[if_len].ifr_addr))->sin_addr));
				LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "static info interfaces netmask:%s", l_strNetMask.c_str());
            }
            else
            {
                perror("SIOCGIFNETMASK ioctl fail");
                close(fd);
                return -1;
            }
    
            /* 广播地址 */
            if (!(ioctl(fd, SIOCGIFBRDADDR, (char *) &buf[if_len])))
            {
                l_strBrAddr=string((char*)inet_ntoa(((struct sockaddr_in*) (&buf[if_len].ifr_addr))->sin_addr));
				LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "static info interfaces braddr:%s", l_strBrAddr.c_str());
            }
            else
            {
                perror("SIOCGIFBRDADDR ioctl fail");
                close(fd);
                return -1;
            }
    
            /*MAC地址 */
            if (!(ioctl(fd, SIOCGIFHWADDR, (char *) &buf[if_len])))
            {
                l_strMacAddr=  MacToStr((unsigned char *)buf[if_len].ifr_hwaddr.sa_data,':');
				LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "static info interfaces MACaddr:%s", l_strMacAddr.c_str());
            }
            else
            {
                perror("SIOCGIFHWADDR ioctl fail");
                close(fd);
                return -1;
            }
            p_vRet.push_back(l_strIpAddr);
            p_vRet.push_back(l_strNetMask);
            p_vRet.push_back(l_strBrAddr);
            p_vRet.push_back(l_strMacAddr);

            close(fd);
            return 0;
        }
    }
    close(fd);
    return -1;
}

int GetWifiName(std::vector<std::string> &p_vRet)
{
	FILE *fp = NULL;
    char linebuffer[512];
	char buffer1[32];
	char buffer2[32];
	
	bzero(linebuffer, 512);
	bzero(buffer2, 32);
	bzero(buffer1, 32);

	fp = fopen(WIFINAMEADDR, "r");
	if(fp == NULL)
	{
		fclose(fp);
		return -1;
	}
	else
	{
		while(fgets(linebuffer, 512, fp))
		{
	        if(sscanf(linebuffer, "%[^=]=%[^=]", buffer1,buffer2) == 0)
	        {
                continue;
			}
	        else
	        {
	            if(!strncmp("ssid", buffer1, 4))
	            {
                    buffer2[strlen(buffer2)-1]='\0';
                    printf("wifi name: %s \n",buffer2);
                    p_vRet.push_back(string(buffer2));
					fclose(fp);
					return 0;
				}
	        }
	 	}
        return -1;	
	}
	return -1;
}


int GetVersionName(std::vector<std::string> &p_vRet)
{
	string l_strVersionName = VERSIONNAMEADDR;
	FILE *fp = NULL;
    json pjFileCont ; 
	fstream l_File(l_strVersionName, ios::in);
	if(l_File.is_open())
	{
		l_File.seekg(0,std::ios::beg);
		ostringstream l_Content;
		l_Content << l_File.rdbuf();
		try
		{
			pjFileCont = json::parse(l_Content.str());
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return -1;
		}
		l_File.close();
		p_vRet.push_back(pjFileCont["HardwareVersion"]);
		p_vRet.push_back(pjFileCont["ApplicationSoftwareVersion"]["VDS"]);
		p_vRet.push_back(pjFileCont["ApplicationSoftwareVersion"]["NET"]);
		p_vRet.push_back(pjFileCont["ApplicationSoftwareVersion"]["SYS"]);
		p_vRet.push_back(pjFileCont["ApplicationSoftwareVersion"]["APP"]);
		p_vRet.push_back(pjFileCont["ApplicationSoftwareVersion"]["V2X"]);
		return 0;
	}
	else
	{
		return -1;
	}
	
#if 0
    string line;

    string l_strVersionName = VERSIONNAMEADDR;
    int l_istart = 0;
    fstream l_File(l_strVersionName, ios::in);
    if(l_File.is_open())
    {
        while(getline(l_File, line))
	    {
            l_istart = line.find(':', 0);
			if((l_istart < 0)||(line.size() == l_istart))
			{
				continue;
			}
            if(line[l_istart+1] == ' ')
            {
                l_istart+=2;
            }
            line = line.substr(l_istart, line.size()-l_istart);
			LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "Version Name %s", line.c_str());
            p_vRet.push_back(line);
	    }
        l_File.close();
        return 0;
    }
    return -1;
#endif
}


void ProcDataRequestStatic(struct mg_connection* p_pConn, int p_nJsonNum, std::vector<std::string> &p_vSection, json &p_jData, HttpServer * p_pHttpServer)
{
    std::vector<std::string> l_vRet;

	if (!GetJsonDataFromFile(p_nJsonNum, p_pHttpServer))
	{
		p_jData["result"] = "error";
		p_jData["message"] = sconv("查询文件不存在!");
		return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
	}

	json &l_webData = p_pHttpServer->m_sJsonSet[p_nJsonNum].data;
	cout << l_webData <<endl;

	if (p_vSection.size())  
	{
		for (auto &l_name : p_vSection)
		{
			if (l_webData.find(l_name) != l_webData.end())
				p_jData[l_name] = l_webData[l_name];
			else
			{
				p_jData["result"] = "error";
				p_jData["message"] = sconv("查询信息字段不存在!");
				return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
			}
		}
		return HttpSendResponse(p_pConn, 200, "json", p_jData.dump(), "");
	}
	else	//数据从文件中全读出来
	{
        for(auto l_jData = l_webData.begin(); l_jData != l_webData.end(); ++l_jData)
            p_jData[l_jData.key()] = l_jData.value();
		if(0 != GetVersionName(l_vRet))
		{
			p_jData["result"] = "error";
		    p_jData["message"] = sconv("版本查询错误!");
		    return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
		}

    	if(0 != network(l_vRet))
		{
			p_jData["result"] = "error";
		    p_jData["message"] = sconv("网络查询错误!");
		    return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
		}

    	if(0 != GetWifiName(l_vRet))
		{
			p_jData["result"] = "error";
		    p_jData["message"] = sconv("WIFI名称查询错误!");
		    return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
		}
		
        p_jData["OBUInfo"]["ObuHdSW"] = l_vRet[0];
		p_jData["OBUInfo"]["VDS"] = l_vRet[1];
		p_jData["OBUInfo"]["NET"] = l_vRet[2];
		p_jData["OBUInfo"]["SYS"] = l_vRet[3];
		p_jData["OBUInfo"]["APP"] = l_vRet[4];
		p_jData["OBUInfo"]["V2X"] = l_vRet[5];
        p_jData["OBUInfo"]["McuSW"] = "no mcu";
        p_jData["OBUInfo"]["AG35SW"] = "no AG35";

		p_jData["WIFIInfo"]["IpAddr"] = l_vRet[6];
		p_jData["WIFIInfo"]["NetMask"] = l_vRet[7];
		p_jData["WIFIInfo"]["BrAddr"] = l_vRet[8];
		p_jData["WIFIInfo"]["MacAddr"] = l_vRet[9];
		p_jData["WIFIInfo"]["WifiName"] = l_vRet[10];

        return HttpSendResponse(p_pConn, 200, "json", p_jData.dump(), "");
	}
}


void ProcInitDataRequest(struct mg_connection* p_pConn, string p_strFileName, std::vector<std::string> &p_vSection, json &p_jResData)
{
	CSimpleIniA l_iniFile(true, true, true);
	if (l_iniFile.LoadFile(p_strFileName.c_str()) < 0)
	{
		p_jResData["result"] = "error";
		p_jResData["message"] = sconv("打开文件失败!");
		return HttpSendResponse(p_pConn, 500, "json", p_jResData.dump(), "");
	}
	if (!IniDataToJson(l_iniFile, p_vSection, p_jResData))
	{
		p_jResData["result"] = "error";
		p_jResData["message"] = sconv("数据文件为空!");
		return HttpSendResponse(p_pConn, 500, "json", p_jResData.dump(), "");
	}
	try {
		p_jResData["result"] = "success";
		p_jResData["message"] = sconv("查询成功!");
		return HttpSendResponse(p_pConn, 200, "json", p_jResData.dump(), "");
		
	}
	catch (...)
	{
		p_jResData["result"] = "error";
		p_jResData["message"] = sconv("解析数据文件出错!");
		return HttpSendResponse(p_pConn, 500, "json", p_jResData.dump(), "");
	}
}


bool RefreshJsonDataFromFile(const string &p_strFileName, int p_FileType, json &p_jData, long &p_nModifyTime)
{
	struct stat l_stat;

	if (stat( p_strFileName.c_str(), &l_stat) < 0)
	{
		return false;
	}
	
	cout << "l_stat.st_mtime:" << l_stat.st_mtime << endl;

	if (p_nModifyTime == l_stat.st_mtime)  // The File Note Edit
		return true;

	cout << "p_nMondifyTime:" << p_nModifyTime << endl;

	if (p_FileType == FILETYPEINI)
	{
		CSimpleIniA l_iniFile(true, true, true);
		if (l_iniFile.LoadFile(p_strFileName.c_str()) < 0)
			return false;
		std::vector<string> l_vData;
		p_jData.clear();
		if (!IniDataToJson(l_iniFile, l_vData, p_jData))
			return false;
	}
	else
	{
		fstream l_File(p_strFileName, ios::in);
		if (l_File.is_open())
		{
			int fd = open(p_strFileName.c_str(), O_RDONLY);
			printf("%d locked now!\n", getpid());
			if (flock(fd, LOCK_EX) == -1)
			{
				perror("flock");
				close(fd);
				exit(1);
			}
			l_File.seekg(0, std::ios::beg);
			ostringstream l_Content;
			l_Content << l_File.rdbuf();
			try
			{
				p_jData = json::parse(l_Content.str());
			}
			catch (...)
			{
				return false;
			}
			if (flock(fd, LOCK_UN) == -1)
			{
				perror("fulock");
				close(fd);
				exit(1);
			}
			printf("lock was released now!\n");
			l_File.close();
		}
		else
			return false;
	}
	p_nModifyTime = l_stat.st_mtime;
	return true;
}


bool GetJsonDataFromFile(int p_nJsonNum, HttpServer * p_pHttpServer)
{
	string l_strFileName;
	int l_nType = FILETYPEJSON;
	switch (p_nJsonNum)
	{
	case JSON_DEVSTATIC:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strStaticInfoFile;
		break;
	case JSON_DEVDYNAMIC:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strDynamicInfoFile;
		break;
	case JSON_DEVFAULT:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strDevFaultInfoFile;
		break;
	case JSON_PROTOCOL:
		l_nType = FILETYPEINI;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strProtocolInfoFile;
		break;
	case JSON_CERTICATE:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strCertInfoFile;
		break;
	case JSON_UPDATAINFO:
		l_nType = FILETYPEINI;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strAppUpdateInfoFile;
		break;
	case JSON_IPACL:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strIpAclConfigFile;
		break;
	case JSON_DEVTESTREAD:
		l_nType = FILETYPEINI;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strDevTestReadFile;
		break;
	case JSON_DEVTESTWRITE:
		l_nType = FILETYPEINI;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strDevTestWriteFile;
		break;
	case JSON_BACKUPSET:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strBackUpSetConfigFile;
		break;
	case JSON_BACKUPPARAM:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strBackUpParamConfigFile;
		break;
	case JSON_BASICINFO:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strBasicInfoFile;
		break;
	case JSON_V2XSERVICE:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strV2XServiceFile;
		break;
	case JSON_VDSMODULE:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strVDSModuleFile;
		break;
	case JSON_MCUMODULE:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strMCUModuleFile;
		break;
	case JSON_MSGMONITOR:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strMsgMonitorFile;
		break;
	case JSON_NETWORKMODULE:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strNetWorkModuleFile;
		break;
	case JSON_APPASCFG:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strAppASCfgFile;
		break;
	case JSON_APPMMCFG:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strAppMMCfgFile;
		break;
	case JSON_APPMTCFG:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strAppMTCfgFile;
		break;
	case JSON_APPTLCFG:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strAppTLCfgFile;
		break;	
	 case JSON_APPSET:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strAppSetFile;
	 	break;	
	default:
		return false;
	}
	l_strFileName = sconv(l_strFileName);

	cout << "l_strFileName:" << l_strFileName << endl;
	return RefreshJsonDataFromFile(l_strFileName, l_nType, p_pHttpServer->m_sJsonSet[p_nJsonNum].data, p_pHttpServer->m_sJsonSet[p_nJsonNum].mtime);
}


void ProcJsonDataRequest(struct mg_connection* p_pConn, int p_nJsonNum, std::vector<std::string> &p_vSection, json &p_jData, HttpServer * p_pHttpServer)
{
	CfgM_Json gCfgM_Json_Info;
	CfgM_Resp tCfgMResp;
	int l_iSemResult = 0;

	if(p_nJsonNum == JSON_MCUMODULE)
	{
		GET_JSON_STRUCT(CFGM_JSON_STRUCT, (void *)&gCfgM_Json_Info);
		gCfgM_Json_Info.CfgFileId = MCURQCFG_FILE;
		SET_JSON_STRUCT(CFGM_JSON_STRUCT, (void *)&gCfgM_Json_Info);
		SET_SIGNAL_B(PARAMETER_CFG_WEB_RQ);
		l_iSemResult = GET_SIGNAL_NB(PARAMETER_CFG_WEB_RESP, 500);

		if(l_iSemResult==-1)
		{
			//给模块再回复一个信号
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Parameter query failed");
			p_jData["result"] = "error";
			p_jData["message"] = sconv("参数查询失败!");
			return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
		}
		else
		{
			GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
			
			if(tCfgMResp.tVdsCfgResp.McuCfgResp== CFGM_RESP_FALSE)
			{
				//给模块再回复一个信号
				LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Parameter query failed");
				p_jData["result"] = "error";
				p_jData["message"] = sconv("参数查询失败!");
				return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
			}
			else
			{
				//给模块再回复一个信号
				LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "Webserver Parameter query success");
				p_jData["result"] = "success";
				p_jData["message"] = sconv("参数查询成功!");
				//return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
			}
		}
	}

	if (!GetJsonDataFromFile(p_nJsonNum, p_pHttpServer))
	{
		p_jData["result"] = "error";
		p_jData["message"] = sconv("查询文件不存在!");
		return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
	}

	json &l_webData = p_pHttpServer->m_sJsonSet[p_nJsonNum].data;
	cout << l_webData <<endl;

	cout << "p_vSection.size:" << p_vSection.size() << endl;
	if (p_vSection.size())  
	{
		for (auto &l_name : p_vSection)
		{
			if (l_webData.find(l_name) != l_webData.end())
				p_jData[l_name] = l_webData[l_name];
			else
			{
				p_jData["result"] = "error";
				p_jData["message"] = sconv("查询信息字段不存在!");
				return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
			}
		}
		return HttpSendResponse(p_pConn, 200, "json", p_jData.dump(), "");
	}
	else	//数据从文件中全读出来
	{
		if (p_jData.empty())
			return HttpSendResponse(p_pConn, 200, "json", l_webData.dump(), "");
		else
		{
			//p_jData += l_webData;
			for(auto l_jData = l_webData.begin(); l_jData != l_webData.end(); ++l_jData)
				p_jData[l_jData.key()] = l_jData.value();

			return HttpSendResponse(p_pConn, 200, "json", p_jData.dump(), "");
		}
	}
}

void ProcJsonDataSetting(struct mg_connection* p_pConn, int p_nJsonNum, std::vector<std::string> &p_vSection, json &p_jData, HttpServer * p_pHttpServer)
{
	CfgM_Json gCfgM_Json_Info;
	CfgM_Resp tCfgMResp; 
	int l_iSemResult = 0; 
	/* 修改 存入，或者将json转换为ini,然后存入*/
	json l_jResData;

	GetJsonDataFromFile(p_nJsonNum, p_pHttpServer); //注意第一次文件是否存在
	json &l_setData = p_pHttpServer->m_sJsonSet[p_nJsonNum].data; //只需要写到文件中数据

	std::cout << "++++++++++++++++++++++++++set"<< p_jData << endl;
	
	

	l_jResData["Operation"] = "set";
	l_jResData["ModuleName"] = p_jData["ModuleName"];
	l_jResData["Source"] = GenerWebSign;
	
	if(p_vSection.size())
	{   //{配置类型：多个内容}
		std::cout << "p_vSection.size()" << endl;
		string ConfigType = p_jData["ConfigType"];
		l_setData.erase(ConfigType);       //不管有没有，都可以擦除

		std::cout << "----------------------------set"<< l_setData << endl;

		for(auto it = p_jData.begin(); it != p_jData.end(); ++it)
		{
			if((it.key() != "ConfigType") && (it.key() != "Operation") && (it.key() != "ModuleName"))
			{
				l_setData[ConfigType][it.key()] = it.value();
			}
		}

		l_jResData["ConfigType"] = ConfigType;
		if(l_setData.find(ConfigType) == l_setData.end())
		{
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("参数设置失败!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}
	else
	{
		for(auto it = p_jData.begin(); it != p_jData.end(); ++it)
		{
			if((it.key() != "ConfigType") && (it.key() != "Operation") && (it.key() != "ModuleName"))
			{
				l_setData[it.key()] = it.value();
			}
		}
		if(l_setData.empty())
		{
			l_jResData["result"] = "error";
			l_jResData["message"] = sconv("参数设置失败!");
			return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
		}
	}

	cout << "add setdata:" << l_setData << endl;
    //保存数据save
	if(!SetJsonDataToFile(p_nJsonNum, l_setData, p_pHttpServer))
	{
		l_jResData["result"] = "error";
		l_jResData["message"] = sconv("参数设置失败!");
		return HttpSendResponse(p_pConn, 500, "json", l_jResData.dump(), "");
	}

	if(p_nJsonNum == JSON_PROTOCOL)
	{
		GET_JSON_STRUCT(CFGM_JSON_STRUCT, (void *)&gCfgM_Json_Info);
		gCfgM_Json_Info.CfgFileId = V2XPROTOCOLCFG_FILE;
		SET_JSON_STRUCT(CFGM_JSON_STRUCT, (void *)&gCfgM_Json_Info);
		SET_SIGNAL_B(PARAMETER_CFG_WEB_RQ);
		l_iSemResult = GET_SIGNAL_NB(PARAMETER_CFG_WEB_RESP, 500);

		if(l_iSemResult==-1)
		{
			//给模块再回复一个信号
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Parameter setting failed");
			p_jData["result"] = "error";
			p_jData["message"] = sconv("参数设置失败!");
			return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
		}
		else
		{
			GET_JSON_STRUCT(CFGM_RESP_STRUCT, (void *)&tCfgMResp);
			
			if(tCfgMResp.tV2xCfgResp.V2xCfgResp == CFGM_RESP_FALSE)
			{
				//给模块再回复一个信号
				LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Webserver Parameter setting failed");
				p_jData["result"] = "error";
				p_jData["message"] = sconv("参数设置失败!");
				return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
			}
		}
	}


	l_jResData["result"] = "success";
	l_jResData["message"] = sconv("参数设置成功!");
	return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
}



bool SetJsonDataToFile(int p_nJsonNum, json &p_jData, HttpServer * p_pHttpServer)
{
	string l_strFileName;
	int l_nType = FILETYPEINI;
	switch (p_nJsonNum)
	{
	case JSON_DEVSTATIC:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strStaticInfoFile;
		break;
	case JSON_DEVDYNAMIC:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strDynamicInfoFile;
		break;
	case JSON_DEVFAULT:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strDevFaultInfoFile;
		break;
	case JSON_PROTOCOL:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strProtocolInfoFile;
		break;
	case JSON_CERTICATE:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strCertInfoFile;
		break;
	case JSON_UPDATAINFO:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strAppUpdateInfoFile;
		break;
	case JSON_IPACL:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strIpAclConfigFile;
		break;
	case JSON_DEVTESTREAD:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strDevTestReadFile;
		break;
	case JSON_DEVTESTWRITE:
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strDevTestWriteFile;
		break;
	case JSON_BACKUPSET:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strBackUpSetConfigFile;
		break;
	case JSON_BACKUPPARAM:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strBackUpParamConfigFile;
		break;
	case JSON_BASICINFO:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strBasicInfoFile;
		break;
	case JSON_V2XSERVICE:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strV2XServiceFile;
		break;
	case JSON_VDSMODULE:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strVDSModuleFile;
		break;
	case JSON_MCUMODULE:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strMCUModuleFile;
		break;
	case JSON_MSGMONITOR:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strMsgMonitorFile;
		break;
	case JSON_NETWORKMODULE:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strNetWorkModuleFile;
		break;
	case JSON_APPSET:
		l_nType = FILETYPEJSON;
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strAppSetFile;
	break;		
	default:
		return false;
	}
	l_strFileName = sconv(l_strFileName);
	cout << "l_strFileName:" << l_strFileName << endl;
	return SaveSetParamJsonToFile(l_strFileName, l_nType, p_nJsonNum, p_jData, p_pHttpServer);
}

bool SaveSetParamJsonToFile(const string &p_strFileName, int p_FileType, int p_nJsonNum, json &p_jData,  HttpServer * p_pHttpServer)
{
	struct stat l_stat;

	if (p_FileType == FILETYPEINI)  //只能写带section的ini文件
	{
		CSimpleIniA l_iniFile(true, true, true);
		std::vector<string> l_vData;
		if(!JsonDataToIni(p_jData, l_vData, l_iniFile))
			return false;
		if(l_iniFile.SaveFile(p_strFileName.c_str()) < 0) //清空写
			return false;
		if (stat(p_strFileName.c_str(), &l_stat) >= 0)
		{
			p_pHttpServer->m_sJsonSet[p_nJsonNum].data = p_jData;
			p_pHttpServer->m_sJsonSet[p_nJsonNum].mtime = l_stat.st_mtime;
		}
		return true;
	}
	else
	{
		fstream l_File(p_strFileName, ios::out | ios::trunc);
		if (l_File.is_open())
		{
			l_File << p_jData.dump(1, '\t');  //一个Tab键缩进

			
			l_File.close();
			if (stat(p_strFileName.c_str(), &l_stat) >= 0)
			{
				p_pHttpServer->m_sJsonSet[p_nJsonNum].data = p_jData;
				p_pHttpServer->m_sJsonSet[p_nJsonNum].mtime = l_stat.st_mtime;
			}
			return true;
		}
	}
	return false;
}

void MonitorProcJsonDataRequest(struct mg_connection* p_pConn, void* p_pHttpMsg, int p_nJsonNum, std::vector<std::string> &p_vSection, json &p_jData, HttpServer * p_pHttpServer)
{
	struct stat l_stat;
	string l_strFileName;

	struct http_message* l_pHttpMsg = (struct http_message*)p_pHttpMsg;
	string l_strOpt = GetHttpUrlQuery(l_pHttpMsg, "op");
	if (!l_strOpt.compare("end"))   //收到总线数据监控中的暂时信号进入if语句
	{
		/*给其它模块发送停止信号动作请放到此处*/
		SET_SIGNAL_B(MSG_MONITOR_END);
		p_jData["result"] = "success";
		p_jData["message"] = sconv("总线监控数据停止接收!");
		return HttpSendResponse(p_pConn, 200, "json", p_jData.dump(), "");
	}
	else
	{
		SET_SIGNAL_B(MSG_MONITOR_START);
		l_strFileName = p_pHttpServer->m_cWebConfig->m_strMsgMonitorFile;

		if (stat( l_strFileName.c_str(), &l_stat) < 0)
		{
			p_jData["result"] = "error";
			p_jData["message"] = sconv("查询文件不存在!");
			return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
		}

		if (p_pHttpServer->m_sJsonSet[p_nJsonNum].mtime == l_stat.st_mtime)  // The File Note Edit
		{
			p_jData["result"] = "error";
			p_jData["message"] = sconv("数据未更新!");
			return HttpSendResponse(p_pConn, 200, "json", p_jData.dump(), "");
		}


		if (!GetJsonDataFromFile(p_nJsonNum, p_pHttpServer))
		{
			p_jData["result"] = "error";
			p_jData["message"] = sconv("查询文件不存在!");
			return HttpSendResponse(p_pConn, 500, "json", p_jData.dump(), "");
		}

		json l_jsonList;

		json &l_webData = p_pHttpServer->m_sJsonSet[p_nJsonNum].data;

		for(auto l_jData = l_webData.begin(); l_jData != l_webData.end(); ++l_jData)
		{	
			json sub_jsonList;
			json &sub_jsonData = l_jData.value();
			for(auto sub_jData = sub_jsonData.begin(); sub_jData != sub_jsonData.end(); ++sub_jData)
			{
				if(sub_jData.key() == "Msg"){
					string value = sub_jData.value();
					sub_jData.value() = value.substr(0,30);
				}
			}
			l_jsonList.push_back(l_jData.value());
		}
		p_jData["list"] = l_jsonList;
		p_jData["result"] = "success";
		//p_jData["message"] = sconv("数据查询成功");
		SET_MSGMONITOR_FILE_STATE(MSGMONITOR_OPR);
		return HttpSendResponse(p_pConn, 200, "json", p_jData.dump(), "");	
		
	}
	


}


/*升级V2X模组软件，即是四跨还是新四跨*/
void updateModuleConfig(struct mg_connection* p_pConn, json &p_jData, int type)
{
	// json l_jResData;

	// l_jResData["Operation"] = "set";
	// l_jResData["ModuleName"] = p_jData["ModuleName"];
	// l_jResData["Source"] = GenerWebSign;

	/*code*/
	system("systemctl stop cv2x");
	sleep(1);
	if(type == 1){
		system("cv2x-config --update-config-file /mnt/APP/Config/v2x_sikua.xml");
	}
	else if(type == 2){
		system("cv2x-config --update-config-file /mnt/APP/Config/v2x_newsikua.xml");
	}
	sleep(1);
	system("systemctl start cv2x");
	sleep(5);
	system("reboot");
	
	// l_jResData["result"] = "success";
	// l_jResData["message"] = sconv("参数设置成功!");
	// return HttpSendResponse(p_pConn, 200, "json", l_jResData.dump(), "");
}



