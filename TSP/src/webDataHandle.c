#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <cJSON.h>

#include "wj_log.h"
#include "tsp_config.h"
#include "webDataHandle.h"

#define NET_Config_OBUInfo_Path "/mnt/APP/Config/obu/net/Config_OBUInfo.json"
#define NET_Config_Supervision_Path "/mnt/APP/Config/obu/net/Config_Supervision.ini"
#define DevInfo_Config_DevInfo_Path "/mnt/APP/Config/obu/DevInfo/DevInfo.json"
#define DYNAMICINFO_Config_Path "/etc/obu/sysm/DynamicInfo/DynamicInfo.json"

#define VDS_Config_Path "/mnt/APP/Config/obu/vds/VDSCfg.json"
#define V2X_Config_Path "/mnt/APP/Config/obu/v2x/ProtocolStack.ini"
#define APP_Config_Path "/mnt/APP/mainprogram/AppConfig.json"

#define DIAG_Config_Path "/mnt/APP/Config/obu/sysm/Diag/Diag.json"

#define TSP_Config_Path "/mnt/APP/Config/obu/tsp/TSP_Config.ini"


/*从JSON文件中获取相关字段信息，并存储在全局结构体中*/
void getVDSJsonValue()
{
	char buf[1024*5]={0};
    FILE *fp;
    int  f_size;
    int  re_fread;
	
	if((fp = fopen(VDS_Config_Path, "r")) == NULL){
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " -- getVDSJsonValue  open fail --!");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp);
    rewind(fp);

    re_fread = fread(buf, f_size, 1, fp);
    if(re_fread != 1){    
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " -- getVDSJsonValue  read fail --!");
        fclose(fp);
        return -1;
    }
    fclose(fp);

	cJSON * VDSJson = NULL;
	VDSJson = cJSON_Parse(buf);

	if(VDSJson != NULL)
	{
		cJSON *VEH = cJSON_GetObjectItem(VDSJson, "VEH");
		sprintf(m_VDSCfgData.VehId,"%s", cJSON_GetObjectItem(VEH,"VehId")->valuestring);
		m_VDSCfgData.VehType = cJSON_GetObjectItem(VEH,"VehType")->valueint;
		sprintf(m_VDSCfgData.VehLength,"%s", cJSON_GetObjectItem(VEH,"VehLength")->valuestring);
		sprintf(m_VDSCfgData.VehWidth,"%s", cJSON_GetObjectItem(VEH,"VehWidth")->valuestring);
		sprintf(m_VDSCfgData.VehHigh,"%s", cJSON_GetObjectItem(VEH,"VehHigh")->valuestring);

		cJSON *GNSS = cJSON_GetObjectItem(VDSJson, "GNSS");
		m_VDSCfgData.RtcmFlag = cJSON_GetObjectItem(GNSS,"RtcmFlag")->valueint;
		m_VDSCfgData.Locationsource = cJSON_GetObjectItem(GNSS,"Locationsource")->valueint;
		m_VDSCfgData.Latitude = cJSON_GetObjectItem(GNSS,"Latitude")->valueint;
		m_VDSCfgData.longtitude = cJSON_GetObjectItem(GNSS,"longtitude")->valueint;
		m_VDSCfgData.Speed = cJSON_GetObjectItem(GNSS,"Speed")->valueint;
		m_VDSCfgData.Heading = cJSON_GetObjectItem(GNSS,"Heading")->valueint;

		cJSON *QXWZ = cJSON_GetObjectItem(VDSJson, "QXWZ");
		sprintf(m_VDSCfgData.AK,"%s", cJSON_GetObjectItem(QXWZ,"AK")->valuestring);
		sprintf(m_VDSCfgData.AS,"%s", cJSON_GetObjectItem(QXWZ,"AS")->valuestring);
		sprintf(m_VDSCfgData.GPSName,"%s", cJSON_GetObjectItem(QXWZ,"GPSName")->valuestring);
		m_VDSCfgData.RtcmDataSource = cJSON_GetObjectItem(QXWZ,"RtcmDataSource")->valueint;
		sprintf(m_VDSCfgData.GPSName_W,"%s", cJSON_GetObjectItem(QXWZ,"GPSName_W")->valuestring);
		sprintf(m_VDSCfgData.AppKey,"%s", cJSON_GetObjectItem(QXWZ,"AppKey")->valuestring);
		sprintf(m_VDSCfgData.AppSectet,"%s", cJSON_GetObjectItem(QXWZ,"AppSectet")->valuestring);
		sprintf(m_VDSCfgData.Dev_id,"%s", cJSON_GetObjectItem(QXWZ,"Dev_id")->valuestring);
		sprintf(m_VDSCfgData.Dev_type,"%s", cJSON_GetObjectItem(QXWZ,"Dev_type")->valuestring);

		cJSON *CANCTROL = cJSON_GetObjectItem(VDSJson, "CANCTROL");
		m_VDSCfgData.CANSendSwitch = cJSON_GetObjectItem(CANCTROL,"CANSendSwitch")->valueint;

		cJSON_Delete(VDSJson);
	}

}

/*在线设置配置查询，VDS数据处理*/
int onlineSelectConfig_VDShandle(void *cjsonStr)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSelectConfig_VDShandle  start!");
	getVDSJsonValue();

	// cJSON *vds;
	// cJSON_AddItemToObject(cjsonStr,"vds",vds=cJSON_CreateObject());
	cJSON *VEH;
	cJSON_AddItemToObject(cjsonStr,"VEH",VEH=cJSON_CreateObject());
	cJSON_AddStringToObject(VEH,"VehId",m_VDSCfgData.VehId);
	cJSON_AddNumberToObject(VEH,"VehType",m_VDSCfgData.VehType);
	cJSON_AddStringToObject(VEH,"VehLength", m_VDSCfgData.VehLength);
	cJSON_AddStringToObject(VEH,"VehWidth", m_VDSCfgData.VehWidth);
	cJSON_AddStringToObject(VEH,"VehHigh", m_VDSCfgData.VehHigh);

	cJSON *GNSS;
	cJSON_AddItemToObject(cjsonStr,"GNSS",GNSS=cJSON_CreateObject());
	cJSON_AddNumberToObject(GNSS,"RtcmFlag",m_VDSCfgData.RtcmFlag);
	cJSON_AddNumberToObject(GNSS,"Locationsource",m_VDSCfgData.Locationsource);
	cJSON_AddNumberToObject(GNSS,"Latitude",m_VDSCfgData.Latitude);
	cJSON_AddNumberToObject(GNSS,"longtitude",m_VDSCfgData.longtitude);
	cJSON_AddNumberToObject(GNSS,"Speed",m_VDSCfgData.Speed);
	cJSON_AddNumberToObject(GNSS,"Heading",m_VDSCfgData.Heading);

	cJSON *QXWZ;
	cJSON_AddItemToObject(cjsonStr,"QXWZ",QXWZ=cJSON_CreateObject());
	cJSON_AddStringToObject(QXWZ,"AK", m_VDSCfgData.AK);
	cJSON_AddStringToObject(QXWZ,"AS", m_VDSCfgData.AS);
	cJSON_AddStringToObject(QXWZ,"GPSName",m_VDSCfgData.GPSName);
	cJSON_AddNumberToObject(QXWZ,"RtcmDataSource",m_VDSCfgData.RtcmDataSource);
	cJSON_AddStringToObject(QXWZ,"GPSName_W",m_VDSCfgData.GPSName_W);
	cJSON_AddStringToObject(QXWZ,"AppKey",m_VDSCfgData.AppKey);
	cJSON_AddStringToObject(QXWZ,"AppSectet",m_VDSCfgData.AppSectet);
	cJSON_AddStringToObject(QXWZ,"Dev_id",m_VDSCfgData.Dev_id);
	cJSON_AddStringToObject(QXWZ,"Dev_type",m_VDSCfgData.Dev_type);

	cJSON *CANCTROL;
	cJSON_AddItemToObject(cjsonStr,"CANCTROL",CANCTROL=cJSON_CreateObject());
	cJSON_AddNumberToObject(CANCTROL,"CANSendSwitch",m_VDSCfgData.CANSendSwitch);

	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSelectConfig_VDShandle  end!");
}

/*从APP JSON文件中获取相关字段信息值*/
void getAPPJsonValue()
{
	char buf[1024*2]={0};
    FILE *fp;
    int  f_size;
    int  re_fread;
	
	if((fp = fopen(APP_Config_Path, "r")) == NULL){
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " -- getAPPJsonValue  open fail --!");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp);
    rewind(fp);

    re_fread = fread(buf, f_size, 1, fp);
    if(re_fread != 1){    
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " -- getAPPJsonValue  read fail --!");
        fclose(fp);
        return -1;
    }
    fclose(fp);

	cJSON * APPJson = NULL;
	APPJson = cJSON_Parse(buf);
	if(APPJson != NULL)
	{
		cJSON *AlgorithmParam = cJSON_GetObjectItem(APPJson, "AlgorithmParam");
		m_APPCfgData.BrakeWarnTTC = cJSON_GetObjectItem(AlgorithmParam,"BrakeWarnTTC")->valueint;
		m_APPCfgData.DisFactor_EVW = cJSON_GetObjectItem(AlgorithmParam,"DisFactor_EVW")->valueint;
		m_APPCfgData.DisFactor_LCW = cJSON_GetObjectItem(AlgorithmParam,"DisFactor_LCW")->valueint;
		m_APPCfgData.DisOffset_EVW = cJSON_GetObjectItem(AlgorithmParam,"DisOffset_EVW")->valueint;
		m_APPCfgData.DisOffset_LCW = cJSON_GetObjectItem(AlgorithmParam,"DisOffset_LCW")->valueint;
		m_APPCfgData.MapMatchAngleFactor = cJSON_GetObjectItem(AlgorithmParam,"MapMatchAngleFactor")->valueint;
		m_APPCfgData.MapMatchDistanceFactor = cJSON_GetObjectItem(AlgorithmParam,"MapMatchDistanceFactor")->valueint;
		m_APPCfgData.MapMatchIncThres = cJSON_GetObjectItem(AlgorithmParam,"MapMatchIncThres")->valueint;
		m_APPCfgData.MapMatchLinkFactor = cJSON_GetObjectItem(AlgorithmParam,"MapMatchLinkFactor")->valueint;
		m_APPCfgData.MapMatchValidThres = cJSON_GetObjectItem(AlgorithmParam,"MapMatchValidThres")->valueint;
		m_APPCfgData.MaxGuideSpeed = cJSON_GetObjectItem(AlgorithmParam,"MaxGuideSpeed")->valueint;
		m_APPCfgData.MinGuideSpeed = cJSON_GetObjectItem(AlgorithmParam,"MinGuideSpeed")->valueint;
		m_APPCfgData.NormalWarnTTC = cJSON_GetObjectItem(AlgorithmParam,"NormalWarnTTC")->valueint;
		m_APPCfgData.PathDisFactor = cJSON_GetObjectItem(AlgorithmParam,"PathDisFactor")->valueint;
		m_APPCfgData.PathDisOffset = cJSON_GetObjectItem(AlgorithmParam,"PathDisOffset")->valueint;
		m_APPCfgData.SafeBorderBackFactor = cJSON_GetObjectItem(AlgorithmParam,"SafeBorderBackFactor")->valueint;
		m_APPCfgData.SafeBorderFrontFactor = cJSON_GetObjectItem(AlgorithmParam,"SafeBorderFrontFactor")->valueint;
		m_APPCfgData.SafeBorderLeftFactor = cJSON_GetObjectItem(AlgorithmParam,"SafeBorderLeftFactor")->valueint;
		m_APPCfgData.SafeBorderMesFactor = cJSON_GetObjectItem(AlgorithmParam,"SafeBorderMesFactor")->valueint;
		m_APPCfgData.SafeBorderRightFactor = cJSON_GetObjectItem(AlgorithmParam,"SafeBorderRightFactor")->valueint;
		m_APPCfgData.ScenarioSpeed = cJSON_GetObjectItem(AlgorithmParam,"ScenarioSpeed")->valueint;
		m_APPCfgData.ShowSpatDistance = cJSON_GetObjectItem(AlgorithmParam,"ShowSpatDistance")->valueint;
		m_APPCfgData.VertDisFactor = cJSON_GetObjectItem(AlgorithmParam,"VertDisFactor")->valueint;
		m_APPCfgData.VertDisOffset = cJSON_GetObjectItem(AlgorithmParam,"VertDisOffset")->valueint;
		m_APPCfgData.WarnTTC_EVW = cJSON_GetObjectItem(AlgorithmParam,"WarnTTC_EVW")->valueint;
		m_APPCfgData.WarnTTC_LCW = cJSON_GetObjectItem(AlgorithmParam,"WarnTTC_LCW")->valueint;

		cJSON *StaticParam = cJSON_GetObjectItem(APPJson, "StaticParam");
		m_APPCfgData.BlindLength = cJSON_GetObjectItem(StaticParam,"BlindLength")->valueint;
		m_APPCfgData.BlindMirrorPos = cJSON_GetObjectItem(StaticParam,"BlindMirrorPos")->valueint;
		m_APPCfgData.BlindOffset = cJSON_GetObjectItem(StaticParam,"BlindOffset")->valueint;
		m_APPCfgData.BlindWidth = cJSON_GetObjectItem(StaticParam,"BlindWidth")->valueint;
		m_APPCfgData.BsmFuelType = cJSON_GetObjectItem(StaticParam,"BsmFuelType")->valueint;
		m_APPCfgData.BsmVehicleClass = cJSON_GetObjectItem(StaticParam,"BsmVehicleClass")->valueint;
		m_APPCfgData.GnssFrontOffset = cJSON_GetObjectItem(StaticParam,"GnssFrontOffset")->valueint;
		m_APPCfgData.GnssRightOffset = cJSON_GetObjectItem(StaticParam,"GnssRightOffset")->valueint;
		m_APPCfgData.SpeedLimitVehType = cJSON_GetObjectItem(StaticParam,"SpeedLimitVehType")->valueint;
		m_APPCfgData.VehicleHeight = cJSON_GetObjectItem(StaticParam,"VehicleHeight")->valueint;
		m_APPCfgData.VehicleLength = cJSON_GetObjectItem(StaticParam,"VehicleLength")->valueint;
		m_APPCfgData.VehicleWidth = cJSON_GetObjectItem(StaticParam,"VehicleWidth")->valueint;

		cJSON_Delete(APPJson);
	}	
}

/*在线设置配置查询，场景算法数据处理*/
int onlineSelectConfig_APPhandle(void *cjsonStr)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSelectConfig_APPhandle  start!");
	getAPPJsonValue();
	// cJSON *APP=cJSON_CreateObject();
	// cJSON_AddItemToObject(cjsonStr,"APP",APP);
	cJSON *Alg=cJSON_CreateObject();
	cJSON_AddItemToObject(cjsonStr,"AlgorithmParam",Alg);
	cJSON_AddNumberToObject(Alg,"BrakeWarnTTC", m_APPCfgData.BrakeWarnTTC);
	cJSON_AddNumberToObject(Alg,"DisFactor_EVW", m_APPCfgData.DisFactor_EVW);
	cJSON_AddNumberToObject(Alg,"DisFactor_LCW", m_APPCfgData.DisFactor_LCW);
	cJSON_AddNumberToObject(Alg,"DisOffset_EVW", m_APPCfgData.DisOffset_EVW);
	cJSON_AddNumberToObject(Alg,"DisOffset_LCW", m_APPCfgData.DisOffset_LCW);
	cJSON_AddNumberToObject(Alg,"MapMatchAngleFactor", m_APPCfgData.MapMatchAngleFactor);
	cJSON_AddNumberToObject(Alg,"MapMatchDistanceFactor", m_APPCfgData.MapMatchDistanceFactor);
	cJSON_AddNumberToObject(Alg,"MapMatchValidThres", m_APPCfgData.MapMatchValidThres);
	cJSON_AddNumberToObject(Alg,"MapMatchLinkFactor", m_APPCfgData.MapMatchLinkFactor);
	cJSON_AddNumberToObject(Alg,"MapMatchIncThres", m_APPCfgData.MapMatchIncThres);
	cJSON_AddNumberToObject(Alg,"MaxGuideSpeed", m_APPCfgData.MaxGuideSpeed);
	cJSON_AddNumberToObject(Alg,"MinGuideSpeed", m_APPCfgData.MinGuideSpeed);
	cJSON_AddNumberToObject(Alg,"NormalWarnTTC", m_APPCfgData.NormalWarnTTC);
	cJSON_AddNumberToObject(Alg,"PathDisFactor", m_APPCfgData.PathDisFactor);
	cJSON_AddNumberToObject(Alg,"PathDisOffset", m_APPCfgData.PathDisOffset);
	cJSON_AddNumberToObject(Alg,"SafeBorderBackFactor", m_APPCfgData.SafeBorderBackFactor);
	cJSON_AddNumberToObject(Alg,"SafeBorderFrontFactor", m_APPCfgData.SafeBorderFrontFactor);
	cJSON_AddNumberToObject(Alg,"SafeBorderLeftFactor", m_APPCfgData.SafeBorderLeftFactor);
	cJSON_AddNumberToObject(Alg,"SafeBorderMesFactor", m_APPCfgData.SafeBorderMesFactor);
	cJSON_AddNumberToObject(Alg,"SafeBorderRightFactor", m_APPCfgData.SafeBorderRightFactor);
	cJSON_AddNumberToObject(Alg,"ScenarioSpeed", m_APPCfgData.ScenarioSpeed);
	cJSON_AddNumberToObject(Alg,"ShowSpatDistance", m_APPCfgData.ShowSpatDistance);
	cJSON_AddNumberToObject(Alg,"VertDisFactor", m_APPCfgData.VertDisFactor);
	cJSON_AddNumberToObject(Alg,"VertDisOffset", m_APPCfgData.VertDisOffset);
	cJSON_AddNumberToObject(Alg,"WarnTTC_EVW", m_APPCfgData.WarnTTC_EVW);
	cJSON_AddNumberToObject(Alg,"WarnTTC_LCW", m_APPCfgData.WarnTTC_LCW);

	cJSON *StaCP = cJSON_CreateObject();
	cJSON_AddItemToObject(cjsonStr,"StaticParam", StaCP);
	cJSON_AddNumberToObject(StaCP,"BlindLength",m_APPCfgData.BlindLength);
	cJSON_AddNumberToObject(StaCP,"BlindMirrorPos",m_APPCfgData.BlindMirrorPos);
	cJSON_AddNumberToObject(StaCP,"BlindOffset",m_APPCfgData.BlindOffset);
	cJSON_AddNumberToObject(StaCP,"BlindWidth",m_APPCfgData.BlindWidth);
	cJSON_AddNumberToObject(StaCP,"BsmFuelType",m_APPCfgData.BsmFuelType);
	cJSON_AddNumberToObject(StaCP,"BsmVehicleClass",m_APPCfgData.BsmVehicleClass);
	cJSON_AddNumberToObject(StaCP,"GnssFrontOffset",m_APPCfgData.GnssFrontOffset);
	cJSON_AddNumberToObject(StaCP,"GnssRightOffset",m_APPCfgData.GnssRightOffset);
	cJSON_AddNumberToObject(StaCP,"SpeedLimitVehType",m_APPCfgData.SpeedLimitVehType);
	cJSON_AddNumberToObject(StaCP,"VehicleHeight",m_APPCfgData.VehicleHeight);
	cJSON_AddNumberToObject(StaCP,"VehicleLength",m_APPCfgData.VehicleLength);
	cJSON_AddNumberToObject(StaCP,"VehicleWidth",m_APPCfgData.VehicleWidth);

	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSelectConfig_APPhandle  end!");
}

/*获取V2X配置文件中的相关字段值*/
void getV2XConfigValue()
{
	m_V2XCfgData.isInitSecLayer = GetPrivateProfileInt("SecurityParamConfig", "isInitSecLayer", 0, V2X_Config_Path);
	m_V2XCfgData.isInclude = GetPrivateProfileInt("SecurityParamConfig", "isInclude", 0, V2X_Config_Path);
	m_V2XCfgData.SignDeviceType = GetPrivateProfileInt("SecurityParamConfig", "SignDeviceType", 1, V2X_Config_Path);

	memset(m_V2XCfgData.aidList, "", sizeof(m_V2XCfgData.aidList));
	GetPrivateProfileString("DSMPParamConfig", "RecvLegalAIDList", "", m_V2XCfgData.aidList, sizeof(m_V2XCfgData.aidList), V2X_Config_Path);

	m_V2XCfgData.MsgFrameVersion = GetPrivateProfileInt("MsgFrameConfig", "MsgFrameVersion", 4, V2X_Config_Path);
	m_V2XCfgData.RecvSwitch = GetPrivateProfileInt("RecvParamConfig", "RecvSwitch", 1, V2X_Config_Path);

	memset(m_V2XCfgData.mBSMAIDMsgName, "", sizeof(m_V2XCfgData.mBSMAIDMsgName));
	GetPrivateProfileString("BSMAIDGroup", "MsgName", "", m_V2XCfgData.mBSMAIDMsgName, sizeof(m_V2XCfgData.mBSMAIDMsgName), V2X_Config_Path);
	memset(m_V2XCfgData.mBSMAIDMsgAID, "", sizeof(m_V2XCfgData.mBSMAIDMsgAID));
	GetPrivateProfileString("BSMAIDGroup", "MsgAID", "", m_V2XCfgData.mBSMAIDMsgAID, sizeof(m_V2XCfgData.mBSMAIDMsgAID), V2X_Config_Path);

	memset(m_V2XCfgData.mRSIAIDMsgName, "", sizeof(m_V2XCfgData.mRSIAIDMsgName));
	GetPrivateProfileString("RSIAIDGroup", "MsgName", "", m_V2XCfgData.mRSIAIDMsgName, sizeof(m_V2XCfgData.mRSIAIDMsgName), V2X_Config_Path);
	memset(m_V2XCfgData.mRSIAIDMsgAID, "", sizeof(m_V2XCfgData.mRSIAIDMsgAID));
	GetPrivateProfileString("RSIAIDGroup", "MsgAID", "", m_V2XCfgData.mRSIAIDMsgAID, sizeof(m_V2XCfgData.mRSIAIDMsgAID), V2X_Config_Path);

	GetPrivateProfileString("MapAIDGroup", "MsgName", "MapApplication", m_V2XCfgData.mMapAIDGroup.MsgName, sizeof(m_V2XCfgData.mMapAIDGroup.MsgName), V2X_Config_Path);
	GetPrivateProfileString("MapAIDGroup", "MsgAID", "3618", m_V2XCfgData.mMapAIDGroup.MsgAID, sizeof(m_V2XCfgData.mMapAIDGroup.MsgAID), V2X_Config_Path);
	
	GetPrivateProfileString("SpatAIDGroup", "MsgName", "SpatApplication", m_V2XCfgData.mSpatAIDGroup.MsgName, sizeof(m_V2XCfgData.mSpatAIDGroup.MsgName), V2X_Config_Path);
	GetPrivateProfileString("SpatAIDGroup", "MsgAID", "3619", m_V2XCfgData.mSpatAIDGroup.MsgAID, sizeof(m_V2XCfgData.mSpatAIDGroup.MsgAID), V2X_Config_Path);

	GetPrivateProfileString("RSMAIDGroup", "MsgName", "RSMRoadRemind", m_V2XCfgData.mRSMAIDGroup.MsgName, sizeof(m_V2XCfgData.mRSMAIDGroup.MsgName), V2X_Config_Path);
	GetPrivateProfileString("RSMAIDGroup", "MsgAID", "3623", m_V2XCfgData.mRSMAIDGroup.MsgAID, sizeof(m_V2XCfgData.mRSMAIDGroup.MsgAID), V2X_Config_Path);

}
/*在线设置配置查询，V2X数据处理*/
int onlineSelectConfig_V2Xhandle(void *cjsonStr)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSelectConfig_V2Xhandle start!");
	getV2XConfigValue();

	cJSON *V2X;
	cJSON_AddItemToObject(cjsonStr,"V2X",V2X=cJSON_CreateObject());

	cJSON *SecurityParamConfig;
	cJSON_AddItemToObject(cjsonStr,"SecurityParamConfig",SecurityParamConfig=cJSON_CreateObject());
	cJSON_AddNumberToObject(SecurityParamConfig,"isInitSecLayer",m_V2XCfgData.isInitSecLayer);
	cJSON_AddNumberToObject(SecurityParamConfig,"isInclude",m_V2XCfgData.isInclude);
	cJSON_AddNumberToObject(SecurityParamConfig,"SignDeviceType",m_V2XCfgData.SignDeviceType);

	cJSON *DSMPParamConfig;
	cJSON_AddItemToObject(cjsonStr,"DSMPParamConfig",DSMPParamConfig=cJSON_CreateObject());
	cJSON_AddStringToObject(DSMPParamConfig,"RecvLegalAIDList",m_V2XCfgData.aidList);

	cJSON *MsgFrameConfig;
	cJSON_AddItemToObject(cjsonStr,"MsgFrameConfig",MsgFrameConfig=cJSON_CreateObject());
	cJSON_AddNumberToObject(MsgFrameConfig,"MsgFrameVersion",m_V2XCfgData.MsgFrameVersion);

	cJSON *RecvParamConfig;
	cJSON_AddItemToObject(cjsonStr,"RecvParamConfig",RecvParamConfig=cJSON_CreateObject());
	cJSON_AddNumberToObject(RecvParamConfig,"RecvSwitch",m_V2XCfgData.RecvSwitch);

	cJSON *BSMAIDGroup;
	cJSON_AddItemToObject(cjsonStr,"BSMAIDGroup",BSMAIDGroup=cJSON_CreateObject());
	cJSON_AddStringToObject(BSMAIDGroup,"MsgName",m_V2XCfgData.mBSMAIDMsgName);
	cJSON_AddStringToObject(BSMAIDGroup,"MsgAID",m_V2XCfgData.mBSMAIDMsgAID);

	cJSON *RSIAIDGroup;
	cJSON_AddItemToObject(cjsonStr,"RSIAIDGroup",RSIAIDGroup=cJSON_CreateObject());
	cJSON_AddStringToObject(RSIAIDGroup,"MsgName",m_V2XCfgData.mRSIAIDMsgName);
	cJSON_AddStringToObject(RSIAIDGroup,"MsgAID",m_V2XCfgData.mRSIAIDMsgAID);

	cJSON *MapAIDGroup;
	cJSON_AddItemToObject(cjsonStr,"MapAIDGroup",MapAIDGroup=cJSON_CreateObject());
	cJSON_AddStringToObject(MapAIDGroup,"MsgName",m_V2XCfgData.mMapAIDGroup.MsgName);
	cJSON_AddStringToObject(MapAIDGroup,"MsgAID",m_V2XCfgData.mMapAIDGroup.MsgAID);

	cJSON *SpatAIDGroup;
	cJSON_AddItemToObject(cjsonStr,"SpatAIDGroup",SpatAIDGroup=cJSON_CreateObject());
	cJSON_AddStringToObject(SpatAIDGroup,"MsgName",m_V2XCfgData.mSpatAIDGroup.MsgName);
	cJSON_AddStringToObject(SpatAIDGroup,"MsgAID",m_V2XCfgData.mSpatAIDGroup.MsgAID);

	cJSON *RSMAIDGroup;
	cJSON_AddItemToObject(cjsonStr,"RSMAIDGroup",RSMAIDGroup=cJSON_CreateObject());
	cJSON_AddStringToObject(RSMAIDGroup,"MsgName",m_V2XCfgData.mRSMAIDGroup.MsgName);
	cJSON_AddStringToObject(RSMAIDGroup,"MsgAID",m_V2XCfgData.mRSMAIDGroup.MsgAID);

	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSelectConfig_V2Xhandle -1- end!");
}


/*在线设置配置参数，VDS数据处理*/
int onlineSetConfig_VDShandle(void *cjsonStr)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSetConfig_VDShandle start!");
	int mHasChanged = 0;
	// VDSCfg_t mVDSCfg_t;	
	/*从JSON文件中获取相关字段信息，并存储在全局结构体中*/
	void getVDSJsonValue();

	cJSON *mData=cJSON_GetObjectItem(cjsonStr,"data"); 

	cJSON *mVeh=cJSON_GetObjectItem(mData,"VEH");
	if(cJSON_HasObjectItem(mVeh, "VehId") && strcmp(cJSON_GetObjectItem(mVeh, "VehId")->valuestring, m_VDSCfgData.VehId) != 0){
		sprintf(m_VDSCfgData.VehId,"%s", cJSON_GetObjectItem(mVeh, "VehId")->valuestring);
		mHasChanged = 1;
	}
	if(cJSON_HasObjectItem(mVeh, "VehType") && (m_VDSCfgData.VehType != cJSON_GetObjectItem(mVeh, "VehType")->valueint)){
		m_VDSCfgData.VehType = cJSON_GetObjectItem(mVeh, "VehType")->valueint;
		mHasChanged = 1;
	}
	if(cJSON_HasObjectItem(mVeh, "VehLength") && strcmp(cJSON_GetObjectItem(mVeh, "VehLength")->valuestring, m_VDSCfgData.VehLength) != 0){
		sprintf(m_VDSCfgData.VehLength,"%s", cJSON_GetObjectItem(mVeh, "VehLength")->valuestring);
		mHasChanged = 1;
	}
	if(cJSON_HasObjectItem(mVeh, "VehWidth") && strcmp(cJSON_GetObjectItem(mVeh, "VehWidth")->valuestring, m_VDSCfgData.VehWidth) != 0){
		sprintf(m_VDSCfgData.VehWidth,"%s", cJSON_GetObjectItem(mVeh, "VehWidth")->valuestring);
		mHasChanged = 1;
	}
	if(cJSON_HasObjectItem(mVeh, "VehHigh") && strcmp(cJSON_GetObjectItem(mVeh, "VehHigh")->valuestring, m_VDSCfgData.VehHigh) != 0){
		sprintf(m_VDSCfgData.VehHigh,"%s", cJSON_GetObjectItem(mVeh, "VehHigh")->valuestring);
		mHasChanged = 1;
	}

	cJSON *mGNSS=cJSON_GetObjectItem(mData,"GNSS");
	if(cJSON_HasObjectItem(mGNSS, "RtcmFlag") && (m_VDSCfgData.RtcmFlag != cJSON_GetObjectItem(mGNSS, "RtcmFlag")->valueint)){
		m_VDSCfgData.RtcmFlag = cJSON_GetObjectItem(mGNSS, "RtcmFlag")->valueint;
		mHasChanged = 1;
	}
	if(cJSON_HasObjectItem(mGNSS, "Locationsource") && (m_VDSCfgData.Locationsource != cJSON_GetObjectItem(mGNSS, "Locationsource")->valueint)){
		m_VDSCfgData.Locationsource = cJSON_GetObjectItem(mGNSS, "Locationsource")->valueint;
		mHasChanged = 1;
	}
	if(cJSON_HasObjectItem(mGNSS, "Latitude") && (m_VDSCfgData.Latitude != cJSON_GetObjectItem(mGNSS, "Latitude")->valueint)){
		m_VDSCfgData.Latitude = cJSON_GetObjectItem(mGNSS, "Latitude")->valueint;
		mHasChanged = 1;
	}
	if(cJSON_HasObjectItem(mGNSS, "longtitude") && (m_VDSCfgData.longtitude != cJSON_GetObjectItem(mGNSS, "longtitude")->valueint)){
		m_VDSCfgData.longtitude = cJSON_GetObjectItem(mGNSS, "longtitude")->valueint;
		mHasChanged = 1;
	}
	if(cJSON_HasObjectItem(mGNSS, "Speed") && (m_VDSCfgData.Speed != cJSON_GetObjectItem(mGNSS, "Speed")->valueint)){
		m_VDSCfgData.Speed = cJSON_GetObjectItem(mGNSS, "Speed")->valueint;
		mHasChanged = 1;
	}
	if(cJSON_HasObjectItem(mGNSS, "Heading") && (m_VDSCfgData.Heading != cJSON_GetObjectItem(mGNSS, "Heading")->valueint)){
		m_VDSCfgData.Heading = cJSON_GetObjectItem(mGNSS, "Heading")->valueint;
		mHasChanged = 1;
	}

	cJSON *mQXWZ=cJSON_GetObjectItem(mData,"QXWZ");
	if(cJSON_HasObjectItem(mQXWZ, "AK") && strcmp(cJSON_GetObjectItem(mQXWZ, "AK")->valuestring, m_VDSCfgData.AK) != 0){
		sprintf(m_VDSCfgData.AK,"%s", cJSON_GetObjectItem(mQXWZ, "AK")->valuestring);
	}
	if(cJSON_HasObjectItem(mQXWZ, "AS") && strcmp(cJSON_GetObjectItem(mQXWZ, "AS")->valuestring, m_VDSCfgData.AS) != 0){
		sprintf(m_VDSCfgData.AS,"%s", cJSON_GetObjectItem(mQXWZ, "AS")->valuestring);
	}
	if(cJSON_HasObjectItem(mQXWZ, "GPSName") && strcmp(cJSON_GetObjectItem(mQXWZ, "GPSName")->valuestring, m_VDSCfgData.GPSName) != 0){
		sprintf(m_VDSCfgData.GPSName,"%s", cJSON_GetObjectItem(mQXWZ, "GPSName")->valuestring);
	}
	if(cJSON_HasObjectItem(mQXWZ, "RtcmDataSource") && (m_VDSCfgData.RtcmDataSource != cJSON_GetObjectItem(mQXWZ, "RtcmDataSource")->valueint)){
		m_VDSCfgData.RtcmDataSource = cJSON_GetObjectItem(mQXWZ, "RtcmDataSource")->valueint;
		mHasChanged = 1;
	}
	if(cJSON_HasObjectItem(mQXWZ, "GPSName_W") && strcmp(cJSON_GetObjectItem(mQXWZ, "GPSName_W")->valuestring, m_VDSCfgData.GPSName_W) != 0){
		sprintf(m_VDSCfgData.GPSName_W,"%s", cJSON_GetObjectItem(mQXWZ, "GPSName_W")->valuestring);
	}
	if(cJSON_HasObjectItem(mQXWZ, "AppKey") && strcmp(cJSON_GetObjectItem(mQXWZ, "AppKey")->valuestring, m_VDSCfgData.AppKey) != 0){
		sprintf(m_VDSCfgData.AppKey,"%s", cJSON_GetObjectItem(mQXWZ, "AppKey")->valuestring);
	}
	if(cJSON_HasObjectItem(mQXWZ, "AppSectet") && strcmp(cJSON_GetObjectItem(mQXWZ, "AppSectet")->valuestring, m_VDSCfgData.AppSectet) != 0){
		sprintf(m_VDSCfgData.AppSectet,"%s", cJSON_GetObjectItem(mQXWZ, "AppSectet")->valuestring);
	}
	if(cJSON_HasObjectItem(mQXWZ, "Dev_id") && strcmp(cJSON_GetObjectItem(mQXWZ, "Dev_id")->valuestring, m_VDSCfgData.Dev_id) != 0){
		sprintf(m_VDSCfgData.Dev_id,"%s", cJSON_GetObjectItem(mQXWZ, "Dev_id")->valuestring);
		mHasChanged = 1;
	}
	if(cJSON_HasObjectItem(mQXWZ, "Dev_type") && strcmp(cJSON_GetObjectItem(mQXWZ, "Dev_type")->valuestring, m_VDSCfgData.Dev_type) != 0){
		sprintf(m_VDSCfgData.Dev_type,"%s", cJSON_GetObjectItem(mQXWZ, "Dev_type")->valuestring);
		mHasChanged = 1;
	}

	cJSON *mCANCTROL=cJSON_GetObjectItem(mData,"CANCTROL");
	if(cJSON_HasObjectItem(mCANCTROL, "CANSendSwitch") && (m_VDSCfgData.CANSendSwitch != cJSON_GetObjectItem(mCANCTROL, "CANSendSwitch")->valueint)){
		m_VDSCfgData.CANSendSwitch = cJSON_GetObjectItem(mCANCTROL, "CANSendSwitch")->valueint;
		mHasChanged = 1;
	}

	if(mHasChanged == 0)
	{
		LogPrint(LOG_LEVEL_ERR,MODULE_NAME," no changed date, so do not write json!");
		return 0;
	}


	/*转换成字符串类型*/
	cJSON *mcJson = NULL;
	mcJson = cJSON_CreateObject();
	cJSON *VEH = NULL;
	cJSON_AddItemToObject(mcJson,"VEH",VEH=cJSON_CreateObject());
	cJSON_AddStringToObject(VEH,"VehId",m_VDSCfgData.VehId);
	cJSON_AddNumberToObject(VEH,"VehType",m_VDSCfgData.VehType);
	cJSON_AddStringToObject(VEH,"VehLength", m_VDSCfgData.VehLength);
	cJSON_AddStringToObject(VEH,"VehWidth", m_VDSCfgData.VehWidth);
	cJSON_AddStringToObject(VEH,"VehHigh", m_VDSCfgData.VehHigh);
	cJSON *GNSS = NULL;
	cJSON_AddItemToObject(mcJson,"GNSS",GNSS=cJSON_CreateObject());
	cJSON_AddNumberToObject(GNSS,"RtcmFlag",m_VDSCfgData.RtcmFlag);
	cJSON_AddNumberToObject(GNSS,"Locationsource",m_VDSCfgData.Locationsource);
	cJSON_AddNumberToObject(GNSS,"Latitude",m_VDSCfgData.Latitude);
	cJSON_AddNumberToObject(GNSS,"longtitude",m_VDSCfgData.longtitude);
	cJSON_AddNumberToObject(GNSS,"Speed",m_VDSCfgData.Speed);
	cJSON_AddNumberToObject(GNSS,"Heading",m_VDSCfgData.Heading);
	cJSON *QXWZ = NULL;
	cJSON_AddItemToObject(mcJson,"QXWZ",QXWZ=cJSON_CreateObject());
	cJSON_AddStringToObject(QXWZ,"AK", m_VDSCfgData.AK);
	cJSON_AddStringToObject(QXWZ,"AS", m_VDSCfgData.AS);
	cJSON_AddStringToObject(QXWZ,"GPSName",m_VDSCfgData.GPSName);
	cJSON_AddNumberToObject(QXWZ,"RtcmDataSource",m_VDSCfgData.RtcmDataSource);
	cJSON_AddStringToObject(QXWZ,"GPSName_W",m_VDSCfgData.GPSName_W);
	cJSON_AddStringToObject(QXWZ,"AppKey",m_VDSCfgData.AppKey);
	cJSON_AddStringToObject(QXWZ,"AppSectet",m_VDSCfgData.AppSectet);
	cJSON_AddStringToObject(QXWZ,"Dev_id",m_VDSCfgData.Dev_id);
	cJSON_AddStringToObject(QXWZ,"Dev_type",m_VDSCfgData.Dev_type);
	cJSON *CANCTROL = NULL;
	cJSON_AddItemToObject(mcJson,"CANCTROL",CANCTROL=cJSON_CreateObject());
	cJSON_AddNumberToObject(CANCTROL,"CANSendSwitch",m_VDSCfgData.CANSendSwitch);

	FILE *fp = fopen(VDS_Config_Path, "w");
	if(fp == NULL)
	{
		LogPrint(LOG_LEVEL_ERR,MODULE_NAME," open APP_Config_Path fail!");
	}
	char *buf = NULL;
	buf = cJSON_Print(mcJson);
	fwrite(buf, strlen(buf), 1, fp);

	fclose(fp);
	free(buf);

	if(mcJson != NULL)
		cJSON_Delete(mcJson);

	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSetConfig_VDShandle end!");
}

/*在线设置配置参数，场景算法数据处理*/
int onlineSetConfig_APPhandle(const char *cjsonStr)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSetConfig_APPhandle start!");

	/*从APP JSON文件中获取相关字段信息值*/
	getAPPJsonValue();	
	int mChangedStatus = 0;

	cJSON *mData=cJSON_GetObjectItem(cjsonStr,"data"); 

	cJSON *mAlg=cJSON_GetObjectItem(mData,"AlgorithmParam");
	if(cJSON_HasObjectItem(mAlg, "BrakeWarnTTC") && (m_APPCfgData.BrakeWarnTTC != cJSON_GetObjectItem(mAlg, "BrakeWarnTTC")->valueint)){
		m_APPCfgData.BrakeWarnTTC = cJSON_GetObjectItem(mAlg, "BrakeWarnTTC")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "DisFactor_EVW") && (m_APPCfgData.DisFactor_EVW != cJSON_GetObjectItem(mAlg, "DisFactor_EVW")->valueint)){
		m_APPCfgData.DisFactor_EVW = cJSON_GetObjectItem(mAlg, "DisFactor_EVW")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "DisFactor_LCW") && (m_APPCfgData.DisFactor_LCW != cJSON_GetObjectItem(mAlg, "DisFactor_LCW")->valueint)){
		m_APPCfgData.DisFactor_LCW = cJSON_GetObjectItem(mAlg, "DisFactor_LCW")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "DisOffset_EVW") && (m_APPCfgData.DisOffset_EVW != cJSON_GetObjectItem(mAlg, "DisOffset_EVW")->valueint)){
		m_APPCfgData.DisOffset_EVW = cJSON_GetObjectItem(mAlg, "DisOffset_EVW")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "DisOffset_LCW") && (m_APPCfgData.DisOffset_LCW != cJSON_GetObjectItem(mAlg, "DisOffset_LCW")->valueint)){
		m_APPCfgData.DisOffset_LCW = cJSON_GetObjectItem(mAlg, "DisOffset_LCW")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "MapMatchAngleFactor") && (m_APPCfgData.MapMatchAngleFactor != cJSON_GetObjectItem(mAlg, "MapMatchAngleFactor")->valueint)){
		m_APPCfgData.MapMatchAngleFactor = cJSON_GetObjectItem(mAlg, "MapMatchAngleFactor")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "MapMatchDistanceFactor") && (m_APPCfgData.MapMatchDistanceFactor != cJSON_GetObjectItem(mAlg, "MapMatchDistanceFactor")->valueint)){
		m_APPCfgData.MapMatchDistanceFactor = cJSON_GetObjectItem(mAlg, "MapMatchDistanceFactor")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "MapMatchValidThres") && (m_APPCfgData.MapMatchValidThres != cJSON_GetObjectItem(mAlg, "MapMatchValidThres")->valueint)){
		m_APPCfgData.MapMatchValidThres = cJSON_GetObjectItem(mAlg, "MapMatchValidThres")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "MapMatchLinkFactor") && (m_APPCfgData.MapMatchLinkFactor != cJSON_GetObjectItem(mAlg, "MapMatchLinkFactor")->valueint)){
		m_APPCfgData.MapMatchLinkFactor = cJSON_GetObjectItem(mAlg, "MapMatchLinkFactor")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "MapMatchIncThres") && (m_APPCfgData.MapMatchIncThres != cJSON_GetObjectItem(mAlg, "MapMatchIncThres")->valueint)){
		m_APPCfgData.MapMatchIncThres = cJSON_GetObjectItem(mAlg, "MapMatchIncThres")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "MaxGuideSpeed") && (m_APPCfgData.MaxGuideSpeed != cJSON_GetObjectItem(mAlg, "MaxGuideSpeed")->valueint)){
		m_APPCfgData.MaxGuideSpeed = cJSON_GetObjectItem(mAlg, "MaxGuideSpeed")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "MinGuideSpeed") && (m_APPCfgData.MinGuideSpeed != cJSON_GetObjectItem(mAlg, "MinGuideSpeed")->valueint)){
		m_APPCfgData.MinGuideSpeed = cJSON_GetObjectItem(mAlg, "MinGuideSpeed")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "NormalWarnTTC") && (m_APPCfgData.NormalWarnTTC != cJSON_GetObjectItem(mAlg, "NormalWarnTTC")->valueint)){
		m_APPCfgData.NormalWarnTTC = cJSON_GetObjectItem(mAlg, "NormalWarnTTC")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "PathDisFactor") && (m_APPCfgData.PathDisFactor != cJSON_GetObjectItem(mAlg, "PathDisFactor")->valueint)){
		m_APPCfgData.PathDisFactor = cJSON_GetObjectItem(mAlg, "PathDisFactor")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "PathDisOffset") && (m_APPCfgData.PathDisOffset != cJSON_GetObjectItem(mAlg, "PathDisOffset")->valueint)){
		m_APPCfgData.PathDisOffset = cJSON_GetObjectItem(mAlg, "PathDisOffset")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "SafeBorderBackFactor") && (m_APPCfgData.SafeBorderBackFactor != cJSON_GetObjectItem(mAlg, "SafeBorderBackFactor")->valueint)){
		m_APPCfgData.SafeBorderBackFactor = cJSON_GetObjectItem(mAlg, "SafeBorderBackFactor")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "SafeBorderFrontFactor") && m_APPCfgData.SafeBorderFrontFactor != cJSON_GetObjectItem(mAlg, "SafeBorderFrontFactor")->valueint){
		m_APPCfgData.SafeBorderFrontFactor = cJSON_GetObjectItem(mAlg, "SafeBorderFrontFactor")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "SafeBorderLeftFactor") && (m_APPCfgData.SafeBorderLeftFactor != cJSON_GetObjectItem(mAlg, "SafeBorderLeftFactor")->valueint)){
		m_APPCfgData.SafeBorderLeftFactor = cJSON_GetObjectItem(mAlg, "SafeBorderLeftFactor")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "SafeBorderMesFactor") && (m_APPCfgData.SafeBorderMesFactor != cJSON_GetObjectItem(mAlg, "SafeBorderMesFactor")->valueint)){
		m_APPCfgData.SafeBorderMesFactor = cJSON_GetObjectItem(mAlg, "SafeBorderMesFactor")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "SafeBorderRightFactor") && (m_APPCfgData.SafeBorderRightFactor != cJSON_GetObjectItem(mAlg, "SafeBorderRightFactor")->valueint)){
		m_APPCfgData.SafeBorderRightFactor = cJSON_GetObjectItem(mAlg, "SafeBorderRightFactor")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "ScenarioSpeed") && (m_APPCfgData.ScenarioSpeed != cJSON_GetObjectItem(mAlg, "ScenarioSpeed")->valueint)){
		m_APPCfgData.ScenarioSpeed = cJSON_GetObjectItem(mAlg, "ScenarioSpeed")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "ShowSpatDistance") && (m_APPCfgData.ShowSpatDistance != cJSON_GetObjectItem(mAlg, "ShowSpatDistance")->valueint)){
		m_APPCfgData.ShowSpatDistance = cJSON_GetObjectItem(mAlg, "ShowSpatDistance")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "VertDisFactor") && (m_APPCfgData.VertDisFactor != cJSON_GetObjectItem(mAlg, "VertDisFactor")->valueint)){
		m_APPCfgData.VertDisFactor = cJSON_GetObjectItem(mAlg, "VertDisFactor")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "VertDisOffset") && (m_APPCfgData.VertDisOffset != cJSON_GetObjectItem(mAlg, "VertDisOffset")->valueint)){
		m_APPCfgData.VertDisOffset = cJSON_GetObjectItem(mAlg, "VertDisOffset")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "WarnTTC_EVW") && (m_APPCfgData.WarnTTC_EVW != cJSON_GetObjectItem(mAlg, "WarnTTC_EVW")->valueint)){
		m_APPCfgData.WarnTTC_EVW = cJSON_GetObjectItem(mAlg, "WarnTTC_EVW")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mAlg, "WarnTTC_LCW") && (m_APPCfgData.WarnTTC_LCW != cJSON_GetObjectItem(mAlg, "WarnTTC_LCW")->valueint)){
		m_APPCfgData.WarnTTC_LCW = cJSON_GetObjectItem(mAlg, "WarnTTC_LCW")->valueint;
		mChangedStatus = 1;
	}

	cJSON *mStaCP=cJSON_GetObjectItem(mData,"StaticParam");
	if(cJSON_HasObjectItem(mData, "BlindLength") && (m_APPCfgData.BlindLength != cJSON_GetObjectItem(mAlg, "BlindLength")->valueint)){
		m_APPCfgData.BlindLength = cJSON_GetObjectItem(mAlg, "BlindLength")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mData, "BlindMirrorPos") && (m_APPCfgData.BlindMirrorPos != cJSON_GetObjectItem(mAlg, "BlindMirrorPos")->valueint)){
		m_APPCfgData.BlindMirrorPos = cJSON_GetObjectItem(mAlg, "BlindMirrorPos")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mData, "BlindOffset") && (m_APPCfgData.BlindOffset != cJSON_GetObjectItem(mAlg, "BlindOffset")->valueint)){
		m_APPCfgData.BlindOffset = cJSON_GetObjectItem(mAlg, "BlindOffset")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mData, "BlindWidth") && (m_APPCfgData.BlindWidth != cJSON_GetObjectItem(mAlg, "BlindWidth")->valueint)){
		m_APPCfgData.BlindWidth = cJSON_GetObjectItem(mAlg, "BlindWidth")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mData, "BsmFuelType") && (m_APPCfgData.BsmFuelType != cJSON_GetObjectItem(mAlg, "BsmFuelType")->valueint)){
		m_APPCfgData.BsmFuelType = cJSON_GetObjectItem(mAlg, "BsmFuelType")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mData, "BsmVehicleClass") && (m_APPCfgData.BsmVehicleClass != cJSON_GetObjectItem(mAlg, "BsmVehicleClass")->valueint)){
		m_APPCfgData.BsmVehicleClass = cJSON_GetObjectItem(mAlg, "BsmVehicleClass")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mData, "GnssFrontOffset") && (m_APPCfgData.GnssFrontOffset != cJSON_GetObjectItem(mAlg, "GnssFrontOffset")->valueint)){
		m_APPCfgData.GnssFrontOffset = cJSON_GetObjectItem(mAlg, "GnssFrontOffset")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mData, "GnssRightOffset") && (m_APPCfgData.GnssRightOffset != cJSON_GetObjectItem(mAlg, "GnssRightOffset")->valueint)){
		m_APPCfgData.GnssRightOffset = cJSON_GetObjectItem(mAlg, "GnssRightOffset")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mData, "SpeedLimitVehType") && (m_APPCfgData.SpeedLimitVehType != cJSON_GetObjectItem(mAlg, "SpeedLimitVehType")->valueint)){
		m_APPCfgData.SpeedLimitVehType = cJSON_GetObjectItem(mAlg, "SpeedLimitVehType")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mData, "VehicleHeight") && (m_APPCfgData.VehicleHeight != cJSON_GetObjectItem(mAlg, "VehicleHeight")->valueint)){
		m_APPCfgData.VehicleHeight = cJSON_GetObjectItem(mAlg, "VehicleHeight")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mData, "VehicleLength") && (m_APPCfgData.VehicleLength != cJSON_GetObjectItem(mAlg, "VehicleLength")->valueint)){
		m_APPCfgData.VehicleLength = cJSON_GetObjectItem(mAlg, "VehicleLength")->valueint;
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(mData, "VehicleWidth") && (m_APPCfgData.VehicleWidth != cJSON_GetObjectItem(mAlg, "VehicleWidth")->valueint)){
		m_APPCfgData.VehicleWidth = cJSON_GetObjectItem(mAlg, "VehicleWidth")->valueint;
		mChangedStatus = 1;
	}

	if(mChangedStatus == 0)
	{
		LogPrint(LOG_LEVEL_ERR,MODULE_NAME," no data changed, so do not need to write json!");
		return 0;
	}
	
	cJSON *mcJson = NULL;
	mcJson = cJSON_CreateObject();
	cJSON *Alg = NULL;
	cJSON_AddItemToObject(mcJson,"AlgorithmParam",Alg = cJSON_CreateObject());
	cJSON_AddNumberToObject(Alg,"BrakeWarnTTC", m_APPCfgData.BrakeWarnTTC);
	cJSON_AddNumberToObject(Alg,"DisFactor_EVW", m_APPCfgData.DisFactor_EVW);
	cJSON_AddNumberToObject(Alg,"DisFactor_LCW", m_APPCfgData.DisFactor_LCW);
	cJSON_AddNumberToObject(Alg,"DisOffset_EVW", m_APPCfgData.DisOffset_EVW);
	cJSON_AddNumberToObject(Alg,"DisOffset_LCW", m_APPCfgData.DisOffset_LCW);
	cJSON_AddNumberToObject(Alg,"MapMatchAngleFactor", m_APPCfgData.MapMatchAngleFactor);
	cJSON_AddNumberToObject(Alg,"MapMatchDistanceFactor", m_APPCfgData.MapMatchDistanceFactor);
	cJSON_AddNumberToObject(Alg,"MapMatchValidThres", m_APPCfgData.MapMatchValidThres);
	cJSON_AddNumberToObject(Alg,"MapMatchLinkFactor", m_APPCfgData.MapMatchLinkFactor);
	cJSON_AddNumberToObject(Alg,"MapMatchIncThres", m_APPCfgData.MapMatchIncThres);
	cJSON_AddNumberToObject(Alg,"MaxGuideSpeed", m_APPCfgData.MaxGuideSpeed);
	cJSON_AddNumberToObject(Alg,"MinGuideSpeed", m_APPCfgData.MinGuideSpeed);
	cJSON_AddNumberToObject(Alg,"NormalWarnTTC", m_APPCfgData.NormalWarnTTC);
	cJSON_AddNumberToObject(Alg,"PathDisFactor", m_APPCfgData.PathDisFactor);
	cJSON_AddNumberToObject(Alg,"PathDisOffset", m_APPCfgData.PathDisOffset);
	cJSON_AddNumberToObject(Alg,"SafeBorderBackFactor", m_APPCfgData.SafeBorderBackFactor);
	cJSON_AddNumberToObject(Alg,"SafeBorderFrontFactor", m_APPCfgData.SafeBorderFrontFactor);
	cJSON_AddNumberToObject(Alg,"SafeBorderLeftFactor", m_APPCfgData.SafeBorderLeftFactor);
	cJSON_AddNumberToObject(Alg,"SafeBorderMesFactor", m_APPCfgData.SafeBorderMesFactor);
	cJSON_AddNumberToObject(Alg,"SafeBorderRightFactor", m_APPCfgData.SafeBorderRightFactor);
	cJSON_AddNumberToObject(Alg,"ScenarioSpeed", m_APPCfgData.ScenarioSpeed);
	cJSON_AddNumberToObject(Alg,"ShowSpatDistance", m_APPCfgData.ShowSpatDistance);
	cJSON_AddNumberToObject(Alg,"VertDisFactor", m_APPCfgData.VertDisFactor);
	cJSON_AddNumberToObject(Alg,"VertDisOffset", m_APPCfgData.VertDisOffset);
	cJSON_AddNumberToObject(Alg,"WarnTTC_EVW", m_APPCfgData.WarnTTC_EVW);
	cJSON_AddNumberToObject(Alg,"WarnTTC_LCW", m_APPCfgData.WarnTTC_LCW);

	cJSON *StaCP = NULL;
	cJSON_AddItemToObject(mcJson,"StaticParam", StaCP = cJSON_CreateObject());
	cJSON_AddNumberToObject(StaCP,"BlindLength",m_APPCfgData.BlindLength);
	cJSON_AddNumberToObject(StaCP,"BlindMirrorPos",m_APPCfgData.BlindMirrorPos);
	cJSON_AddNumberToObject(StaCP,"BlindOffset",m_APPCfgData.BlindOffset);
	cJSON_AddNumberToObject(StaCP,"BlindWidth",m_APPCfgData.BlindWidth);
	cJSON_AddNumberToObject(StaCP,"BsmFuelType",m_APPCfgData.BsmFuelType);
	cJSON_AddNumberToObject(StaCP,"BsmVehicleClass",m_APPCfgData.BsmVehicleClass);
	cJSON_AddNumberToObject(StaCP,"GnssFrontOffset",m_APPCfgData.GnssFrontOffset);
	cJSON_AddNumberToObject(StaCP,"GnssRightOffset",m_APPCfgData.GnssRightOffset);
	cJSON_AddNumberToObject(StaCP,"SpeedLimitVehType",m_APPCfgData.SpeedLimitVehType);
	cJSON_AddNumberToObject(StaCP,"VehicleHeight",m_APPCfgData.VehicleHeight);
	cJSON_AddNumberToObject(StaCP,"VehicleLength",m_APPCfgData.VehicleLength);
	cJSON_AddNumberToObject(StaCP,"VehicleWidth",m_APPCfgData.VehicleWidth);

	FILE *fp = fopen(APP_Config_Path, "w");

	if(fp == NULL)
	{
		LogPrint(LOG_LEVEL_ERR,MODULE_NAME," open APP_Config_Path fail!");
	}

	char *buf = NULL;
	buf = cJSON_Print(mcJson);

	fwrite(buf, strlen(buf), 1, fp);

	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " --APP Config buf--: %s", buf);

	fclose(fp);
	free(buf);

	if(mcJson != NULL)
		cJSON_Delete(mcJson);

	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSetConfig_APPhandle end!");
}

/*在线设置配置参数，V2X数据处理*/
int onlineSetConfig_V2Xhandle(const char *cjsonStr)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSetConfig_V2Xhandle!");
	int mChangedStatus = 0;

	getV2XConfigValue();

	// cJSON *V2X = cJSON_GetObjectItem(cjsonStr, "V2X");
	cJSON *SecurityParamConfig = cJSON_GetObjectItem(cjsonStr, "SecurityParamConfig");
	if(cJSON_HasObjectItem(SecurityParamConfig, "isInitSecLayer") && (cJSON_GetObjectItem(SecurityParamConfig,"isInitSecLayer")->valueint != m_V2XCfgData.isInitSecLayer)){
		WriteConfigData("SecurityParamConfig", "isInitSecLayer", cJSON_GetObjectItem(SecurityParamConfig,"isInitSecLayer")->valueint, V2X_Config_Path);
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(SecurityParamConfig, "isInclude") && (cJSON_GetObjectItem(SecurityParamConfig,"isInclude")->valueint != m_V2XCfgData.isInclude)){
		WriteConfigData("SecurityParamConfig", "isInclude", cJSON_GetObjectItem(SecurityParamConfig,"isInclude")->valueint, V2X_Config_Path);
		mChangedStatus = 1;
	}
	if(cJSON_HasObjectItem(SecurityParamConfig, "SignDeviceType") && (cJSON_GetObjectItem(SecurityParamConfig,"SignDeviceType")->valueint != m_V2XCfgData.SignDeviceType)){
		WriteConfigData("SecurityParamConfig", "SignDeviceType", cJSON_GetObjectItem(SecurityParamConfig,"SignDeviceType")->valueint, V2X_Config_Path);
		mChangedStatus = 1;
	}

	cJSON *DSMPParamConfig = cJSON_GetObjectItem(cjsonStr, "DSMPParamConfig");
	if(cJSON_HasObjectItem(DSMPParamConfig, "RecvLegalAIDList") && strcmp(cJSON_GetObjectItem(DSMPParamConfig, "RecvLegalAIDList")->valuestring, m_V2XCfgData.aidList) != 0){
		WriteConfigData("DSMPParamConfig", "RecvLegalAIDList", cJSON_GetObjectItem(DSMPParamConfig, "RecvLegalAIDList")->valuestring, V2X_Config_Path);
		mChangedStatus = 1;
	}

	cJSON *MsgFrameConfig = cJSON_GetObjectItem(cjsonStr, "MsgFrameConfig");
	if(cJSON_HasObjectItem(MsgFrameConfig, "MsgFrameVersion") && (cJSON_GetObjectItem(MsgFrameConfig,"MsgFrameVersion")->valueint != m_V2XCfgData.MsgFrameVersion)){
		WriteConfigData("MsgFrameConfig", "MsgFrameVersion", cJSON_GetObjectItem(MsgFrameConfig,"MsgFrameVersion")->valueint, V2X_Config_Path);
		mChangedStatus = 1;
	}
	
	cJSON *RecvParamConfig = cJSON_GetObjectItem(cjsonStr, "RecvParamConfig");
	if(cJSON_HasObjectItem(RecvParamConfig, "RecvSwitch") && (cJSON_GetObjectItem(RecvParamConfig,"RecvSwitch")->valueint != m_V2XCfgData.RecvSwitch)){
		WriteConfigData("RecvParamConfig", "RecvSwitch", cJSON_GetObjectItem(RecvParamConfig,"RecvSwitch")->valueint, V2X_Config_Path);
		mChangedStatus = 1;
	}

	cJSON *BSMAIDGroup = cJSON_GetObjectItem(cjsonStr, "BSMAIDGroup");
	if(cJSON_HasObjectItem(BSMAIDGroup, "BSMAIDGroup") && 
	(strcmp(cJSON_GetObjectItem(BSMAIDGroup, "MsgName")->valuestring, m_V2XCfgData.mBSMAIDGroup.MsgName) != 0 
	|| strcmp(cJSON_GetObjectItem(BSMAIDGroup, "MsgAID")->valuestring, m_V2XCfgData.mBSMAIDGroup.MsgAID) != 0)){

		WriteConfigData("BSMAIDGroup", "MsgName", cJSON_GetObjectItem(BSMAIDGroup, "MsgName")->valuestring, V2X_Config_Path);
		WriteConfigData("BSMAIDGroup", "MsgAID", cJSON_GetObjectItem(BSMAIDGroup, "MsgAID")->valuestring, V2X_Config_Path);
		mChangedStatus = 1;
	}

	cJSON *RSIAIDGroup = cJSON_GetObjectItem(cjsonStr, "RSIAIDGroup");
	if(cJSON_HasObjectItem(RSIAIDGroup, "RSIAIDGroup") && 
	(strcmp(cJSON_GetObjectItem(RSIAIDGroup, "MsgName")->valuestring, m_V2XCfgData.mRSIAIDGroup.MsgName) != 0 
	|| strcmp(cJSON_GetObjectItem(RSIAIDGroup, "MsgAID")->valuestring, m_V2XCfgData.mRSIAIDGroup.MsgAID) != 0)){

		WriteConfigData("RSIAIDGroup", "MsgName", cJSON_GetObjectItem(RSIAIDGroup, "MsgName")->valuestring, V2X_Config_Path);
		WriteConfigData("RSIAIDGroup", "MsgAID", cJSON_GetObjectItem(RSIAIDGroup, "MsgAID")->valuestring, V2X_Config_Path);
		mChangedStatus = 1;
	}

	cJSON *MapAIDGroup = cJSON_GetObjectItem(cjsonStr, "MapAIDGroup");
	if(cJSON_HasObjectItem(MapAIDGroup, "MapAIDGroup") && 
	(strcmp(cJSON_GetObjectItem(MapAIDGroup, "MsgName")->valuestring, m_V2XCfgData.mMapAIDGroup.MsgName) != 0 
	|| strcmp(cJSON_GetObjectItem(MapAIDGroup, "MsgAID")->valuestring, m_V2XCfgData.mMapAIDGroup.MsgAID) != 0)){

		WriteConfigData("MapAIDGroup", "MsgName", cJSON_GetObjectItem(MapAIDGroup,"MsgName")->valuestring, V2X_Config_Path);
		WriteConfigData("MapAIDGroup", "MsgAID", cJSON_GetObjectItem(MapAIDGroup,"MsgAID")->valuestring, V2X_Config_Path);
	}

	cJSON *SpatAIDGroup = cJSON_GetObjectItem(cjsonStr, "SpatAIDGroup");
	if(cJSON_HasObjectItem(SpatAIDGroup, "SpatAIDGroup") &&
	(strcmp(cJSON_GetObjectItem(SpatAIDGroup, "MsgName")->valuestring, m_V2XCfgData.mSpatAIDGroup.MsgName) != 0 
	|| strcmp(cJSON_GetObjectItem(SpatAIDGroup, "MsgAID")->valuestring, m_V2XCfgData.mSpatAIDGroup.MsgAID) != 0)){

		WriteConfigData("SpatAIDGroup", "MsgName", cJSON_GetObjectItem(SpatAIDGroup,"MsgName")->valuestring, V2X_Config_Path);
		WriteConfigData("SpatAIDGroup", "MsgAID", cJSON_GetObjectItem(SpatAIDGroup,"MsgAID")->valuestring, V2X_Config_Path);
	}

	cJSON *RSMAIDGroup = cJSON_GetObjectItem(cjsonStr, "RSMAIDGroup");
	if(cJSON_HasObjectItem(RSMAIDGroup, "RSMAIDGroup") &&
	(strcmp(cJSON_GetObjectItem(RSMAIDGroup, "MsgName")->valuestring, m_V2XCfgData.mRSMAIDGroup.MsgName) != 0 
	|| strcmp(cJSON_GetObjectItem(RSMAIDGroup, "MsgAID")->valuestring, m_V2XCfgData.mRSMAIDGroup.MsgAID) != 0)){
		
		WriteConfigData("RSMAIDGroup", "MsgName", cJSON_GetObjectItem(RSMAIDGroup,"MsgName")->valuestring, V2X_Config_Path);
		WriteConfigData("RSMAIDGroup", "MsgAID", cJSON_GetObjectItem(RSMAIDGroup,"MsgAID")->valuestring, V2X_Config_Path);
	}

}

// /*在线设置测试*/
// int test()
// {
// 	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSetConfig_APPhandle start! \n");
//     // 测试使用字符串
// 	char *char_json = "{\n\t\"frametype\":\t28673,\n\t\"rsctl\":\t60,\n\t\"utc\":\t\"1619689628\",\n\t\"SN\":\t\"\",\n\t\"gnssStatus\":\t6\n}";//"{\"data\":{\"APP\":{\"AlgorithmParam\":{\"BrakeWarnTTC\":\"8.0\", \"DisFactor_EVW\":\"7.0\"}}}}";
// 	cJSON *cjsonStr = cJSON_Parse(char_json);

// 	char *buf = NULL;
// 	buf = cJSON_Print(cjsonStr);

// 	FILE *fp = fopen(APP_Config_Path, "w");

// 	if(fp == NULL)
// 	{
// 		LogPrint(LOG_LEVEL_ERR,MODULE_NAME," open APP_Config_Path fail!\n");
// 	}
// 	fwrite(buf, strlen(buf), 1, fp);

// 	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " --APP Config buf--: %s\n", buf);

// 	fclose(fp);
// 	free(buf);

// 	cJSON_Delete(cjsonStr);

// 	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," onlineSetConfig_APPhandle end! \n");
// }

/*单独开辟一个线程用于发送故障信息数据，但是这样造成很大的内存空间*/
void faultMsgThread()
{
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " faultMsgThread start!");
	int mCount = 0;
	while (1)
	{
		sleep(1);
		++mCount;

		if(0 == (mCount%3))
		{
			/*故障信息,3s一次上传（GPS是3s周期）*/
			faultMsg();
		}
	}
}

/*获取json文件中的内容*/
int getFaultJsonStr(char *filename)
{
	char buf[1024*5]={0};
    FILE *fp;
    int  f_size;
    int  re_fread;
	
	if((fp = fopen(filename, "r")) == NULL){
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " -- getFaultJsonStr  open fail --!");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp);
    rewind(fp);

    re_fread = fread(buf, f_size, 1, fp);
    if(re_fread != 1){    
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " -- getFaultJsonStr  read fail --!");
        fclose(fp);
        return -1;
    }
    fclose(fp);

	faultMsgJson = cJSON_Parse(buf);

	return 0;
}
/*故障信息上传*/
void faultMsg()
{
	LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " faultMsg start!");

	// V2X:"AG15ComError", "HSMError"  WebServer:"WIFIError"  Mcu: "HighVoltage", "LowVoltage" 
	// vds: "GPSError", "gnssComFault", "GnssDataError", "4GError"
	char strName[][20] = {"GPSError", "RFUError", "GnssDataError", "4GError", 
	"AG15ComError", "HSMError", "HighVoltage", "LowVoltage", "WIFIError"};

	/*获取json文件中的内容*/
	int ret = getFaultJsonStr(DIAG_Config_Path);
	if(ret == -1){
		LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " -- faultMsg getFaultJsonStr fail --!");
		return;
	}

	cJSON *Vds = cJSON_GetObjectItem(faultMsgJson, "Vds");
	cJSON *V2x = cJSON_GetObjectItem(faultMsgJson, "V2x");
	cJSON *Mcu = cJSON_GetObjectItem(faultMsgJson, "Mcu");
	cJSON *WebServer = cJSON_GetObjectItem(faultMsgJson, "WebServer");
	
	cJSON *mSubCode[9]={0};

	for(int i=0; i<9; i++)
	{
		switch (i)
		{
			case 0:
			case 1:
			case 2:
			case 3:
				mSubCode[i] = cJSON_GetObjectItem(Vds, strName[i]);
				break;
			case 4:
			case 5:
				mSubCode[i] = cJSON_GetObjectItem(V2x, strName[i]);
				break;
			case 6:
			case 7:
				mSubCode[i] = cJSON_GetObjectItem(Mcu, strName[i]);
				break;
			case 8:
				mSubCode[i] = cJSON_GetObjectItem(WebServer, strName[i]);
				break;
			default:
				break;
		}
		
		mFaultData[i].DiagState = cJSON_GetObjectItem(mSubCode[i],"DiagState")->valueint;

		cJSON *SnapShot1 = cJSON_GetObjectItem(mSubCode[i], "SnapShot1");
		sprintf(mFaultData[i].mSnapShot1.SysTime,"%s", cJSON_GetObjectItem(SnapShot1,"SysTime")->valuestring);
		sprintf(mFaultData[i].mSnapShot1.SocTemp,"%s", cJSON_GetObjectItem(SnapShot1,"SocTemp")->valuestring);
		sprintf(mFaultData[i].mSnapShot1.CurrentSpeed,"%s", cJSON_GetObjectItem(SnapShot1,"CurrentSpeed")->valuestring);

		cJSON *SnapShot2 = cJSON_GetObjectItem(mSubCode[i], "SnapShot2");
		sprintf(mFaultData[i].mSnapShot1.SysTime,"%s", cJSON_GetObjectItem(SnapShot2,"SysTime")->valuestring);
		sprintf(mFaultData[i].mSnapShot1.SocTemp,"%s", cJSON_GetObjectItem(SnapShot2,"SocTemp")->valuestring);
		sprintf(mFaultData[i].mSnapShot1.CurrentSpeed,"%s", cJSON_GetObjectItem(SnapShot2,"CurrentSpeed")->valuestring);
	}

	if(faultMsgJson != NULL){
		cJSON_Delete(faultMsgJson);
	}

	int frametype = 0x7201;//29185
	rsctl = (rsctl >= 0xFFFF) ? 1 : (rsctl + 1);
	char utc[50] = {0};
	utcFunc(utc);

	/*转换成字符串类型*/
	cJSON *cjsonstr = NULL;
	cjsonstr = cJSON_CreateObject();
 
	cJSON_AddNumberToObject(cjsonstr, "frametype", frametype);
	cJSON_AddNumberToObject(cjsonstr, "rsctl", rsctl);
	cJSON_AddStringToObject(cjsonstr, "utc", utc);

	cJSON *faultJson = NULL;
	cJSON *SnapShlsot1 = NULL;
	cJSON *SnapShot2 = NULL;
	for(int i=0; i<9; i++)
	{
		if(i == 1)
		{
			cJSON_AddItemToObject(cjsonstr, "GNSSComFault", faultJson=cJSON_CreateObject());
		}
		else if(i == 3)
		{
			cJSON_AddItemToObject(cjsonstr, "Error4G", faultJson=cJSON_CreateObject());
		}
		else
		{
			cJSON_AddItemToObject(cjsonstr, strName[i], faultJson=cJSON_CreateObject());
		}
		cJSON_AddNumberToObject(faultJson, "DiagState", mFaultData[i].DiagState);

		cJSON_AddItemToObject(faultJson, "SnapShot1", SnapShlsot1=cJSON_CreateObject());
		cJSON_AddStringToObject(SnapShlsot1, "SysTime", mFaultData[i].mSnapShot1.SysTime);
		cJSON_AddStringToObject(SnapShlsot1, "SocTemp", mFaultData[i].mSnapShot1.SocTemp);
		cJSON_AddStringToObject(SnapShlsot1, "CurrentSpeed", mFaultData[i].mSnapShot1.CurrentSpeed);
	
		cJSON_AddItemToObject(faultJson, "SnapShot2", SnapShot2=cJSON_CreateObject());
		cJSON_AddStringToObject(SnapShot2, "SysTime", mFaultData[i].mSnapShot2.SysTime);
		cJSON_AddStringToObject(SnapShot2, "SocTemp", mFaultData[i].mSnapShot2.SocTemp);
		cJSON_AddStringToObject(SnapShot2, "CurrentSpeed", mFaultData[i].mSnapShot2.CurrentSpeed);
	}

	char *buf = cJSON_Print(cjsonstr);
	if(cjsonstr != NULL)
		cJSON_Delete(cjsonstr);

	cJSON_Minify(buf);//去除格式
	int len = strlen(buf);

	/*添加中间变量为了进行释放*/
	char buf_temp[1024*2] = {0};
	strcpy(buf_temp, buf);

	free(buf);

	sendDataToServer(buf_temp, len);
}

/*使用这种方式适合 非频繁读取json文件*/
/*此两个函数是用于故障信息上传时，需要查找故障信息函数*/
void GetJsonIntValue(char *pInFileName, char *pInSectionName1, char *pInSectionName2, char *pInSectionName3, char *pInKeyName, int *pOutKeyValue)
{
	FILE *fp = NULL;
	fp = open(DIAG_Config_Path,02);

	struct stat l_buf;
	if((fstat(fp,&l_buf)) < 0)
	{ /* return*/}
     
    char * l_pfilebuf =NULL ;
	l_pfilebuf = (char *)malloc((size_t)(l_buf.st_size)+1);
    
    if(read(fp,l_pfilebuf,l_buf.st_size)<=0)
	{
		goto ERR_EXIT;
	}
    // 修改 json数据
	cJSON *pfiledatajson = NULL;
	pfiledatajson = cJSON_Parse(l_pfilebuf);
	if(NULL == pfiledatajson)
	{
		 goto ERR_EXIT;	
	}

	cJSON *pSection1 = cJSON_GetObjectItem(pfiledatajson,pInSectionName1);
    if(NULL == pSection1)
	{
		 goto ERR_EXIT;	
	}

	if(pInSectionName2 == NULL && pInSectionName3 == NULL)
	{
		cJSON *pkeyvalue = cJSON_GetObjectItem(pSection1,pInKeyName);
		if(NULL == pkeyvalue)
		{
			goto ERR_EXIT;	
		}
		strcpy(pOutKeyValue,pkeyvalue->valuestring);
   		// printf("pOutKeyValue is : %d",*pOutKeyValue);
	}
	else if(pInSectionName2 != NULL && pInSectionName3 == NULL)
	{
		cJSON *pSection2 = cJSON_GetObjectItem(pSection1,pInSectionName2);
		if(NULL == pSection2)
		{
			goto ERR_EXIT;	
		}
		cJSON *pkeyvalue = cJSON_GetObjectItem(pSection2,pInKeyName);
		if(NULL == pkeyvalue)
		{
			goto ERR_EXIT;	
		}
		strcpy(pOutKeyValue,pkeyvalue->valuestring);
   		// printf("pOutKeyValue is : %d",*pOutKeyValue);
	}
	else if(pInSectionName2 != NULL && pInSectionName3 != NULL)
	{
		cJSON *pSection2 = cJSON_GetObjectItem(pSection1,pInSectionName2);
		if(NULL == pSection2)
		{
			goto ERR_EXIT;	
		}
		cJSON *pSection3 = cJSON_GetObjectItem(pSection2,pInSectionName3);
		if(NULL == pSection3)
		{
			goto ERR_EXIT;	
		}
		cJSON *pkeyvalue = cJSON_GetObjectItem(pSection3,pInKeyName);
		if(NULL == pkeyvalue)
		{
			goto ERR_EXIT;	
		}
		strcpy(pOutKeyValue,pkeyvalue->valuestring);
   		// printf("pOutKeyValue is : %d",*pOutKeyValue);
	}
    //pOutKeyValue = cJSON_Print(pkeyvalue);
ERR_EXIT:
	close(fp);
	free(l_pfilebuf);
	if(pfiledatajson != NULL)
		cJSON_Delete(pfiledatajson);
}

void GetJsonStringValue(char *pInFileName, char *pInSectionName1, char *pInSectionName2, char *pInSectionName3, char *pInKeyName, char *pOutKeyValue)
{
	FILE *fp = NULL;
	fp = open(DIAG_Config_Path,02);

	struct stat l_buf;
	if((fstat(fp,&l_buf)) < 0)
	{ /* return*/}
     
    char * l_pfilebuf =NULL ;
	l_pfilebuf = (char *)malloc((size_t)(l_buf.st_size)+1);
    
    if(read(fp,l_pfilebuf,l_buf.st_size)<=0)
	{
		goto ERR_EXIT;
	}
    // 修改 json数据
	cJSON *pfiledatajson = NULL;
	pfiledatajson = cJSON_Parse(l_pfilebuf);
	if(NULL == pfiledatajson)
	{
		 goto ERR_EXIT;	
	}

	cJSON *pSection1 = cJSON_GetObjectItem(pfiledatajson,pInSectionName1);
    if(NULL == pSection1)
	{
		 goto ERR_EXIT;	
	}

	if(pInSectionName2 == NULL && pInSectionName3 == NULL)
	{
		cJSON *pkeyvalue = cJSON_GetObjectItem(pSection1,pInKeyName);
		if(NULL == pkeyvalue)
		{
			goto ERR_EXIT;	
		}
		strcpy(pOutKeyValue,pkeyvalue->valuestring);
   		// printf("pOutKeyValue is : %d",*pOutKeyValue);
	}
	else if(pInSectionName2 != NULL && pInSectionName3 == NULL)
	{
		cJSON *pSection2 = cJSON_GetObjectItem(pSection1,pInSectionName2);
		if(NULL == pSection2)
		{
			goto ERR_EXIT;	
		}
		cJSON *pkeyvalue = cJSON_GetObjectItem(pSection2,pInKeyName);
		if(NULL == pkeyvalue)
		{
			goto ERR_EXIT;	
		}
		strcpy(pOutKeyValue,pkeyvalue->valuestring);
   		// printf("pOutKeyValue is : %d",*pOutKeyValue);
	}
	else if(pInSectionName2 != NULL && pInSectionName3 != NULL)
	{
		cJSON *pSection2 = cJSON_GetObjectItem(pSection1,pInSectionName2);
		if(NULL == pSection2)
		{
			goto ERR_EXIT;	
		}
		cJSON *pSection3 = cJSON_GetObjectItem(pSection2,pInSectionName3);
		if(NULL == pSection3)
		{
			goto ERR_EXIT;	
		}
		cJSON *pkeyvalue = cJSON_GetObjectItem(pSection3,pInKeyName);
		if(NULL == pkeyvalue)
		{
			goto ERR_EXIT;	
		}
		strcpy(pOutKeyValue,pkeyvalue->valuestring);
   		// printf("pOutKeyValue is : %d",*pOutKeyValue);
	}
    //pOutKeyValue = cJSON_Print(pkeyvalue);
ERR_EXIT:
	close(fp);
	free(l_pfilebuf);
	if(pfiledatajson != NULL)
		cJSON_Delete(pfiledatajson);
}



