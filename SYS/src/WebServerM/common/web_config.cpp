#include "../web_service/http_handler.h"

#define WEB_PORT              8000
#define IPC_PORT              3001
#define IPC_TIMEOUT           50
#define SESSION_TIMEOUT       3600  // 登录用户会话过期的时间
#define TOKEN_TIMEOUT         120   // 页面TOKEN的过期时间
#define WEBCONFIG_FILE        "/mnt/APP/Config/obu/sysm/WebServerM/config/WebConfig.json"

#define PROTOCOLINFO_FILE    "/mnt/APP/Config/obu/v2x/ProtocolStack.ini"
#define CERTIINFO_FILE       "/mnt/APP/Config/obu/sysm/WebServerM/config/Certification-1.json"   

#define UPDATE_PATH           "/opt/ObuUpgrade/"
#define STATICINFO_FILE       "/mnt/APP/Config/obu/sysm/StaticInfo/StaticInfo.json"
#define DYNAMICINFO_FILE      "/mnt/APP/Config/obu/sysm/DynamicInfo/DynamicInfo.json"
#define DEVFAULTINFO_FILE     "/mnt/APP/Config/obu/sysm/Diag/Diag.json"

#define UPDATAINFO_FILE        "/mnt/APP/Config/obu/sysm/WebServerM/config/Config.ini"
#define UPDATASHELL_FILE       "V2XAPP_UpdateFile.sh"

#define CERTIUPLOAD_PATH        "/mnt/APP/Config/obu/sysm/WebServerM/config/certificate/"

#define LOGFILE_ROOT            "/opt"
#define DATABASE_ROOT           "/opt"
#define BACKUPFILE_PAHT         "/mnt/APP/Config/obu/sysm/WebServerM/config/bak_up"
#define UPLOADFILE_PATH         "/mnt/APP/Config/obu/sysm/WebServerM/config/upload"
#define SOFTWARE_ROOTPATH       "/mnt/APP/Config/obu/sysm/WebServerM/config/software"
#define CONFIGFILE_ROOTPATH     "/mnt/APP/Config/obu/sysm/WebServerM/config/config"
#define CERTFILE_ROOTPATH       "/mnt/APP/Config/obu/sysm/WebServerM/config/certfile"
#define BACKUP_ROOTPATH         "/mnt/APP/Config/obu/sysm/WebServerM/config/backup"
#define IPTABLE_CONFIGFILE      "/mnt/APP/Config/obu/sysm/WebServerM/config/ipacl.json"
#define DEVTEST_WRITEFILE       "/mnt/APP/Config/obu/sysm/WebServerM/config/ThirdTest_DownParam.ini"
#define DEVTEST_READFILE        "/mnt/APP/Config/obu/sysm/WebServerM/config/ThirdTest_UpParam.ini"
#define DEVTEST_SHELLFILE       "KeyTest_Rsu.sh"
#define BACKUP_CONFIGFILE       "/mnt/APP/Config/obu/sysm/WebServerM/config/backupset.json"
#define BACKUPPARAM_CONFIGFILE  "/mnt/APP/Config/obu/sysm/WebServerM/config/backupparam.json"

#define BASICINFO_FILE          "/mnt/APP/Config/obu/sysm/BasicInfo/BasicInfo.json"
#define V2XSERVICE_FILE         "/mnt/APP/Config/obu/v2x/V2XServerCfg.json"
#define VDSMODULE_FILE          "/mnt/APP/Config/obu/vds/VDSCfg.json"
#define MCUMODULE_FILE          "/mnt/APP/Config/obu/vds/MCUCfg.json"
#define MSGMONITOR_FILE         "/mnt/APP/Config/obu/sysm/MsgMonitor/MsgMonitor.json"
#define NETWORKMODULE_FILE      "/mnt/APP/Config/obu/net/NetConfig.json"

#define APPASCFG_FILE          "/mnt/APP/Config/obu/app/AppASCfg.json"
#define APPMMCFG_FILE          "/mnt/APP/Config/obu/app/AppMMCfg.json"
#define APPMTCFG_FILE          "/mnt/APP/Config/obu/app/AppMTCfg.json"
#define APPTLCFG_FILE          "/mnt/APP/Config/obu/app/AppTLCfg.json"
#define APPSET_FILE			   "/mnt/APP/mainprogram/AppConfig.json"

/*
#ifdef  _WIN32
#define PROTOCOLINFO_FILE    "config/ProtocolStack.ini"
#define CERTIINFO_FILE       "config/Certification.json"   

#define UPDATE_PATH           "/mnt/path/"
#define STATICINFO_FILE       "config/StaticInfo.ini"
#define DYNAMICINFO_FILE      "config/Supervion.ini"
#define DEVFAULTINFO_FILE     "config/DevFault.ini"

#define UPDATAINFO_FILE        "config/Config.ini"
#define UPDATASHELL_FILE       "V2XAPP_UpdateFile.sh"
#define PERIPHINFO_FILE        "config/Peripheral.json"

#define CERTIUPLOAD_PATH        "config/certificate/"

#define LOGFILE_ROOT            "/"
#define DATABASE_ROOT           "/"
#define BACKUPFILE_PAHT         "config/bak_up"
#define UPLOADFILE_PATH         "config/upload"

#else
#define CERTIINFO_FILE       "Certification.json"   
#define PROTOCOLINFO_FILE     "ProtocolStack.ini"
#define UPDATE_PATH           "/mnt/APP/Update/DownloadFilePath/"
#define STATICINFO_FILE       "Config.ini"
#define DYNAMICINFO_FILE      "Supervion.ini"
#define DEVFAULTINFO_FILE     "DevFault.ini"

#define UPDATASHELL_FILE       "/mnt/APP/Scripts/V2XAPP_UpdateFile.sh"
#define UPDATAINFO_FILE        "/mnt/RWD/UpdateLog/Config.ini"


#define CERTIUPLOAD_PATH        "/certi/data/"

#define LOGFILE_ROOT            "/home/"
#define DATABASE_ROOT           "/home/"
#define DATABASE_FILE           "Database_Base.db"

#define BACKUPFILE_PAHT         "config/bak_up"
#define UPLOADFILE_PATH         "config/upload"

#endif
*/



#define PROTOCOLPARAM_INI  "ProtocolStack.ini"
#define MODULEPARAM_INN    "ModuleConfig.ini"

void to_json(json& p_j, const WebConfigParam& p_sData)
{
	p_j = json{ { "WebPort", (p_sData.m_nWebPort)},
	{ "IpcPort", (p_sData.m_nIpcPort)},
	{ "IpcTimeOut", (p_sData.m_nIpcTimeOut)},
	{ "SessionTimeOut", (p_sData.m_nSessionTimeOut)},
	{ "TokenTimeOut", (p_sData.m_nTokenTimeOut)},
	{ "StaticInfoFile", sconv(p_sData.m_strStaticInfoFile)},
	{ "DynamicInfoFile", sconv(p_sData.m_strDynamicInfoFile)},
	{ "DevFaultInfoFile", sconv(p_sData.m_strDevFaultInfoFile)},
	{ "ProtocolInfoFile", sconv(p_sData.m_strProtocolInfoFile)},
	{ "CertInfoFile", sconv(p_sData.m_strCertInfoFile)},
	{ "AppUpdatePath", sconv(p_sData.m_strAppUpdatePath)},
	{ "AppUpdateInfoFile", sconv(p_sData.m_strAppUpdateInfoFile)},
	{ "AppUpdateCmd", sconv(p_sData.m_vAppUpdateCmd)},
	{ "AppUpdataShFile", sconv(p_sData.m_strAppUpdataShFile)},
	{ "CertUploadPath", sconv(p_sData.m_strCertUploadPath)},
	{ "LogFileRootPath", sconv(p_sData.m_strLogFileRootPath)},
	{ "DataBaseRootPath", sconv(p_sData.m_strDataBaseRootPath)},
	{ "SysBackupPath", sconv(p_sData.m_strSysBackupPath)},
	{ "FileUploadPath", sconv(p_sData.m_strFileUploadPath)},
	{ "SoftWareRootPath", sconv(p_sData.m_strSoftWareRootPath)},
	{ "ConfigFileRootPath", sconv(p_sData.m_strConfigFileRootPath)},
	{ "CertFileRootPath", sconv(p_sData.m_strCertFileRootPath)},
	{ "BackupRootPath", sconv(p_sData.m_strBackupRootPath)},
	{"IpAclConfigFile", sconv(p_sData.m_strIpAclConfigFile)},
	{"DevTestWriteFile", sconv(p_sData.m_strDevTestWriteFile)},
	{"DevTestReadFile", sconv(p_sData.m_strDevTestReadFile)},
	{"DevTestShellFile", sconv(p_sData.m_strDevTestShellFile)},
	{"DevRsuTestCmd", sconv(p_sData.m_vDevRsuTestCmd)},
	{"BackUpSetConfigFile", sconv(p_sData.m_strBackUpSetConfigFile)},
	{"BackUpParamConfigFile", sconv(p_sData.m_strBackUpParamConfigFile)},
	{"BasicInfoFile", sconv(p_sData.m_strBasicInfoFile)},
	{"V2XServiceFile", sconv(p_sData.m_strV2XServiceFile)},
	{"VDSModuleFile", sconv(p_sData.m_strVDSModuleFile)},
	{"MCUModuleFile", sconv(p_sData.m_strMCUModuleFile)},
	{"MsgMonitorFile", sconv(p_sData.m_strMsgMonitorFile)},
	{"NetWorkModuleFile", sconv(p_sData.m_strNetWorkModuleFile)},
	{"AppASCfgFile", sconv(p_sData.m_strAppASCfgFile)},
	{"AppMMCfgFile", sconv(p_sData.m_strAppMMCfgFile)},
	{"AppMTCfgFile", sconv(p_sData.m_strAppMTCfgFile)},
	{"AppTLCfgFile", sconv(p_sData.m_strAppTLCfgFile)},
	{"AppSetFile", sconv(p_sData.m_strAppSetFile)}
	};
}

string m_strDevTestShellFile;
vector<string> m_vDevRsuTestCmd;

void from_json(const json& p_j, WebConfigParam& p_sData)
{
	p_sData.m_nWebPort = GetJsonIntData(p_j, "WebPort", WEB_PORT);
	p_sData.m_nIpcPort = GetJsonIntData(p_j, "IpcPort", IPC_PORT);
	p_sData.m_nIpcTimeOut = GetJsonIntData(p_j, "IpcTimeOut", IPC_TIMEOUT);
	p_sData.m_nSessionTimeOut = GetJsonIntData(p_j, "SessionTimeOut", SESSION_TIMEOUT);
	p_sData.m_nTokenTimeOut = GetJsonIntData(p_j, "TokenTimeOut", TOKEN_TIMEOUT);
	p_sData.m_strStaticInfoFile = GetJsonStringData(p_j, "StaticInfoFile", STATICINFO_FILE);
	p_sData.m_strDynamicInfoFile = GetJsonStringData(p_j, "DynamicInfoFile", DYNAMICINFO_FILE);
	p_sData.m_strDevFaultInfoFile = GetJsonStringData(p_j, "DevFaultInfoFile", DEVFAULTINFO_FILE);

	p_sData.m_strProtocolInfoFile = GetJsonStringData(p_j, "ProtocolInfoFile", PROTOCOLINFO_FILE);
	p_sData.m_strCertInfoFile = GetJsonStringData(p_j, "CertInfoFile", CERTIINFO_FILE);
	p_sData.m_strAppUpdatePath = GetJsonStringData(p_j, "AppUpdatePath", UPDATE_PATH);
	p_sData.m_strAppUpdateInfoFile = GetJsonStringData(p_j, "AppUpdateInfoFile", UPDATAINFO_FILE);
	p_sData.m_strAppUpdataShFile = GetJsonStringData(p_j, "AppUpdataShFile", UPDATASHELL_FILE);
	p_sData.m_strCertUploadPath = GetJsonStringData(p_j, "CertUploadPath", CERTIUPLOAD_PATH);
	p_sData.m_strLogFileRootPath = GetJsonStringData(p_j, "LogFileRootPath", LOGFILE_ROOT);
	p_sData.m_strDataBaseRootPath = GetJsonStringData(p_j, "DataBaseRootPath", DATABASE_ROOT);
	p_sData.m_strSysBackupPath = GetJsonStringData(p_j, "SysBackupPath", BACKUPFILE_PAHT);
	p_sData.m_strFileUploadPath = GetJsonStringData(p_j, "FileUploadPath", UPLOADFILE_PATH);
	p_sData.m_strSoftWareRootPath = GetJsonStringData(p_j, "SoftWareRootPath", SOFTWARE_ROOTPATH);
	p_sData.m_strConfigFileRootPath = GetJsonStringData(p_j, "ConfigFileRootPath", CONFIGFILE_ROOTPATH);
	p_sData.m_strCertFileRootPath = GetJsonStringData(p_j, "CertFileRootPath", CERTFILE_ROOTPATH);
	p_sData.m_strBackupRootPath = GetJsonStringData(p_j, "BackupRootPath", BACKUP_ROOTPATH);
	p_sData.m_strIpAclConfigFile = GetJsonStringData(p_j, "IpAclConfigFile", IPTABLE_CONFIGFILE);
	p_sData.m_strDevTestWriteFile = GetJsonStringData(p_j, "DevTestWriteFile", DEVTEST_WRITEFILE);
	p_sData.m_strDevTestReadFile = GetJsonStringData(p_j, "DevTestReadFile", DEVTEST_READFILE);
	p_sData.m_strDevTestShellFile = GetJsonStringData(p_j, "DevTestShellFile", DEVTEST_SHELLFILE);
	p_sData.m_strBackUpSetConfigFile = GetJsonStringData(p_j, "BackUpSetConfigFile", BACKUP_CONFIGFILE);
	p_sData.m_strBackUpParamConfigFile = GetJsonStringData(p_j, "BackUpParamConfigFile", BACKUPPARAM_CONFIGFILE);
	p_sData.m_strBasicInfoFile = GetJsonStringData(p_j, "BasicInfoFile", BASICINFO_FILE);
	p_sData.m_strV2XServiceFile = GetJsonStringData(p_j, "V2XServiceFile", V2XSERVICE_FILE);
	p_sData.m_strVDSModuleFile = GetJsonStringData(p_j, "VDSModuleFile", VDSMODULE_FILE);
	p_sData.m_strMCUModuleFile = GetJsonStringData(p_j, "MCUModuleFile", MCUMODULE_FILE);
	p_sData.m_strMsgMonitorFile = GetJsonStringData(p_j, "MsgMonitorFile", MSGMONITOR_FILE);
	p_sData.m_strNetWorkModuleFile = GetJsonStringData(p_j, "NetWorkModuleFile", NETWORKMODULE_FILE);
	p_sData.m_strAppASCfgFile = GetJsonStringData(p_j, "AppASCfgFile", APPASCFG_FILE);
	p_sData.m_strAppMMCfgFile = GetJsonStringData(p_j, "AppMMCfgFile", APPMMCFG_FILE);
	p_sData.m_strAppMTCfgFile = GetJsonStringData(p_j, "AppMTCfgFile", APPMTCFG_FILE);
	p_sData.m_strAppTLCfgFile = GetJsonStringData(p_j, "AppTLCfgFile", APPTLCFG_FILE);
	p_sData.m_strAppSetFile = GetJsonStringData(p_j, "AppSetFile", APPSET_FILE);

	vector<string> l_vData = { "chmod /mnt/APP/Scripts/V2XAPP_UpdateFile.sh" , "sh /mnt/APP/Scripts/V2XAPP_UpdateFile.sh &" };
	p_sData.m_vAppUpdateCmd = GetJsonVecStringData(p_j, "AppUpdateCmd", l_vData);
	l_vData = { "chmod -R 755 /wanji_rsu/Keytest/rsu-test/" , "sh /wanji_rsu/Keytest/rsu-test/KeyTest_Rsu.sh &" };
	p_sData.m_vDevRsuTestCmd = GetJsonVecStringData(p_j, "DevRsuTestCmd", l_vData);
}


void WebConfigCheck(WebConfigParam &p_sData)
{
	if (p_sData.m_nSessionTimeOut < 600 || p_sData.m_nSessionTimeOut > 86400)
		p_sData.m_nSessionTimeOut = SESSION_TIMEOUT;
	if (p_sData.m_nTokenTimeOut < 60 || p_sData.m_nTokenTimeOut > 600)
		p_sData.m_nTokenTimeOut = TOKEN_TIMEOUT;
}


void WebConfigInit(WebConfigParam &p_sData)
{
	json l_jConfigData;
	string l_strFname = WEBCONFIG_FILE;
	fstream l_File(l_strFname, ios::in);
	if (l_File.is_open())
	{
		l_File.seekg(0, std::ios::beg);
		ostringstream l_Content;
		l_Content << l_File.rdbuf();
		
		try
		{
			l_jConfigData = json::parse(l_Content.str());
		}
		catch (...)
		{
			;
		}
		l_File.close();
	}
	p_sData = l_jConfigData;

	WebConfigCheck(p_sData);
	l_File.open(l_strFname, ios::out | ios::trunc);
	l_File << json(p_sData).dump(1,'\t');
	l_File.close();
}
