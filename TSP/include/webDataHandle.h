#ifndef __WEBDATAHANDLE_H__
#define __WEBDATAHANDLE_H__

#include <stdint.h>
#include <stdbool.h>
#include <libwebsockets.h>
#include <fcntl.h>
#include "websockets.h"

/*定义故障信息结构体*/
typedef struct SnapShot1
{
    char SysTime[20];
    char SocTemp[20];
    char CurrentSpeed[20];
}SnapShot1;
typedef struct SnapShot2
{
    char SysTime[20];
    char SocTemp[20];
    char CurrentSpeed[20];
}SnapShot2;
typedef struct fault_t{
    int DiagState;
    SnapShot1 mSnapShot1;
    SnapShot2 mSnapShot2;
}fault_t;

static fault_t mFaultData[9];

typedef struct VDSCfg_t
{
    char VehId[50];
    int VehType;
    char VehLength[10];
    char VehWidth[10];
    char VehHigh[10];

    int RtcmFlag;
    int Locationsource;
    int Latitude;
    int longtitude;
    int Speed;
    int Heading;

    char AK[30];
    char AS[30];
    char GPSName[30];
    int RtcmDataSource;
    char GPSName_W[30];
    char AppKey[30];
    char AppSectet[30];
    char Dev_id[30];
    char Dev_type[30];

    int CANSendSwitch;
}VDSCfg_t;

typedef struct APPCfg_t
{
    int BrakeWarnTTC;
    int DisFactor_EVW;
    int DisFactor_LCW;
    int DisOffset_EVW;
    int DisOffset_LCW;
    int MapMatchAngleFactor;
    int MapMatchDistanceFactor;
    int MapMatchIncThres;
    int MapMatchLinkFactor;
    int MapMatchValidThres;
    int MaxGuideSpeed;
    int MinGuideSpeed;
    int NormalWarnTTC;
    int PathDisFactor;
    int PathDisOffset;
    int SafeBorderBackFactor;
    int SafeBorderFrontFactor;
    int SafeBorderLeftFactor;
    int SafeBorderMesFactor;
    int SafeBorderRightFactor;
    int ScenarioSpeed;
    int ShowSpatDistance;
    int VertDisFactor;
    int VertDisOffset;
    int WarnTTC_EVW;
    int WarnTTC_LCW;
    
    int BlindLength;
    int BlindMirrorPos;
    int BlindOffset;
    int BlindWidth;
    int BsmFuelType;
    int BsmVehicleClass;
    int GnssFrontOffset;
    int GnssRightOffset;
    int SpeedLimitVehType;
    int VehicleHeight;
    int VehicleLength;
    int VehicleWidth;
}APPCfg_t;


typedef struct BSMAIDGroup
{
    char MsgName[5][30];
    char MsgAID[5][10];
}BSMAIDGroup;
typedef struct RSIAIDGroup
{
    char MsgName[3][30];
    char MsgAID[3][10];
}RSIAIDGroup;
typedef struct MapAIDGroup
{
    char MsgName[30];
    char MsgAID[10];
}MapAIDGroup;
typedef struct SpatAIDGroup
{
    char MsgName[30];
    char MsgAID[10];
}SpatAIDGroup;
typedef struct RSMAIDGroup
{
    char MsgName[30];
    char MsgAID[10];
}RSMAIDGroup;

typedef struct V2XCfg_t
{
    int isInitSecLayer;
    int isInclude;
    int SignDeviceType;
    char aidList[100];
    char mBSMAIDMsgName[200];
    char mBSMAIDMsgAID[100];
    char mRSIAIDMsgName[200];
    char mRSIAIDMsgAID[100];
    int MsgFrameVersion;
    int RecvSwitch;
    BSMAIDGroup mBSMAIDGroup;
    RSIAIDGroup mRSIAIDGroup;
    MapAIDGroup mMapAIDGroup;
    SpatAIDGroup mSpatAIDGroup;
    RSMAIDGroup mRSMAIDGroup;
}V2XCfg_t;

static VDSCfg_t m_VDSCfgData;       //VDS配置参数
static APPCfg_t m_APPCfgData;       //APP配置参数
static V2XCfg_t m_V2XCfgData;       //V2X配置参数

static cJSON *faultMsgJson = NULL;

/*从JSON文件中获取相关字段信息，并存储在全局结构体中*/
void getVDSJsonValue();
/*在线设置配置查询，VDS数据处理*/
int onlineSelectConfig_VDShandle(void *cjsonStr);

/*从APP JSON文件中获取相关字段信息值*/
void getAPPJsonValue();
/*在线设置配置查询，场景算法数据处理*/
int onlineSelectConfig_APPhandle(void *cjsonStr);

/*获取V2X配置文件中的相关字段值*/
void getV2XConfigValue();
/*在线设置配置查询，V2X数据处理*/
int onlineSelectConfig_V2Xhandle(void *cjsonStr);

/*在线设置配置参数，VDS数据处理*/
int onlineSetConfig_VDShandle(void *cjsonStr);

/*在线设置配置参数，场景算法数据处理*/
int onlineSetConfig_APPhandle(const char *cjsonStr);

/*在线设置配置参数，V2X数据处理*/
int onlineSetConfig_V2Xhandle(const char *cjsonStr);


void faultMsgThread();
/*故障信息上传*/
void faultMsg();

/*在线设置测试*/
int test();

/*获取三层或者四层叠加json格式*/
void GetJsonIntValue(char *pInFileName, char *pInSectionName1, char *pInSectionName2, char *pInSectionName3, char *pInKeyName, int *pOutKeyValue);
void GetJsonStringValue(char *pInFileName, char *pInSectionName1, char *pInSectionName2, char *pInSectionName3, char *pInKeyName, char *pOutKeyValue);


#endif

