/************************************************************
 文件名: ConfigModuleRW.c
 作者:   WangMeng
 描述:   实现对配置文件的读写操作
 版本:   V1.0
 日期:   2020.5.20
 ***********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#ifdef __cplusplus
extern "C"
{
#include "ConfigModuleRW.h"
#include "cJSON.h"
#include "wj_log.h"
#include "RdWrIni.h"
}
#else
#include "ConfigModuleRW.h"
#include "cJSON.h"
#endif
#include "CUseCPP.h"
#include "SimpleIni.h"
#include "PublicMsg.h"

//此处定义全局变量，外部主程序无需重复定义，只包含头文件即可
ProtocolStackParamConfig_t ProtocolStackParamConfig;
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

static char configDir[128] = {0};
static char configName[32] = {0};
static char configFileName[128] = {0};
static int changeSrc = 2; //更新数据来源，1：web，2：本地修改,默认本地修改

static void setStaticAIDFromConfig(ProtocolStackParamConfig_t *p_ProtocolStackParamConfig)
{
    if (NULL == p_ProtocolStackParamConfig)
    {
        return;
    }
    int index = 0, i = 0;

    for (index = 0; index < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; index++)
    {
        if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "BSMAIDGroup") == 0)
        {
            for (i = 0; i < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum; i++)
            {
                if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[i] == 1)
                {
                    //普通车辆+常规型
                    p_ProtocolStackParamConfig->messageParamConfig.msgAid.BSMOrdinaryConven =
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[i];
                }
                else if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[i] == 2)
                {
                    //普通车辆+事件型
                    p_ProtocolStackParamConfig->messageParamConfig.msgAid.BSMOrdinaryEvent =
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[i];
                }
                else if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[i] == 3)
                {
                    //特殊车辆+常规型
                    p_ProtocolStackParamConfig->messageParamConfig.msgAid.BSMSpecialConven =
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[i];
                }
                else if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[i] == 4)
                {
                    //特殊车辆+事件型
                    p_ProtocolStackParamConfig->messageParamConfig.msgAid.BSMSpecialEvent =
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[i];
                }
                else if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[i] == 5)
                {
                    //后装车载终端
                    p_ProtocolStackParamConfig->messageParamConfig.msgAid.BSMAfterLoading =
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[i];
                }
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "RSIAIDGroup") == 0)
        {
            for (i = 0; i < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum; i++)
            {
                if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[i] == 1)
                {
                    //道路信息-静态类应用
                    p_ProtocolStackParamConfig->messageParamConfig.msgAid.RSIRoadStatic =
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[i];
                }
                else if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[i] == 2)
                {
                    //道路信息-半静态类应用
                    p_ProtocolStackParamConfig->messageParamConfig.msgAid.RSIRoadHalfStatic =
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[i];
                }
                else if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[i] == 3)
                {
                    //道路信息-动态类应用
                    p_ProtocolStackParamConfig->messageParamConfig.msgAid.RSIRoadDynamic =
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[i];
                }
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "MapAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //map消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.MAPMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "SpatAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //Spat消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.SPATMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "RSMAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //RSM消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.RSMMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "TESTAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //RSM消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.TESTMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "RTCMAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //RSM消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.RTCMMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "PAMAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //RSM消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.PAMMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "CLPMMAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //RSM消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.CLPMMMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "PSMAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //RSM消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.PSMMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "RSCAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //RSM消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.RSCMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "SSMAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //RSM消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.SSMMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "VIRAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //RSM消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.VIRMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
        else if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, "VPMAIDGroup") == 0)
        {
            if (p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum > 0)
            {
                //RSM消息只有一个aid,此处只复制第一个即可
                p_ProtocolStackParamConfig->messageParamConfig.msgAid.VPMMSGAID =
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[0];
            }
        }
    }

    p_ProtocolStackParamConfig->messageParamConfig.msgAid.DSAMSGAID = 3616;      //DSA发送
    p_ProtocolStackParamConfig->messageParamConfig.msgAid.TESTBSMMSGAID = 3624;  //测试车辆发送
    p_ProtocolStackParamConfig->messageParamConfig.msgAid.TESTRSIMSGAID = 3625;  //测试路测发送1
    p_ProtocolStackParamConfig->messageParamConfig.msgAid.TESTRSIMSGAID2 = 3626; //测试路测发送2
    p_ProtocolStackParamConfig->messageParamConfig.msgAid.PASSMSGAID =
        p_ProtocolStackParamConfig->DSMPParamConfig.PassMessageAID; //消息透传
}

static void setSendSwitch(ProtocolStackParamConfig_t *p_ProtocolStackParamConfig, const char *MsgType, int SendSwitch)
{
    if (NULL == p_ProtocolStackParamConfig || NULL == MsgType)
    {
        return;
    }
    int index = 0;
    for (index = 0; index < p_ProtocolStackParamConfig->messageParamConfig.m_SendParamNum; index++)
    {
        if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSectionName, MsgType) == 0)
        {
            //从本地读取文件情况下，修改发送开关
            if (p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSendSwitch == 2)
                p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSendSwitch = SendSwitch;
        }
    }
}
/**
 * @brief 更新文件并设置结构体数据
 */
static int setParamDataTest(ProtocolStackParamConfig_t *p_ProtocolStackParamConfig, const char *souceString, char *FileName)
{
    if (NULL == FileName || NULL == souceString || NULL == p_ProtocolStackParamConfig)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "param is NULL\n");
        return -1;
    }

    int nRet = 1; //返回1为成功
    //cJSON *jsonReqRoot = cJSON_CreateObject();
    cJSON *jsonReqRoot = cJSON_Parse(souceString);
    char *configType = strGetJsonStringItem(jsonReqRoot, "ConfigType");
    if (configType == NULL)
    {
        if (jsonReqRoot != NULL)
        {
            cJSON_Delete(jsonReqRoot);
            jsonReqRoot = NULL;
        }
        LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "configType is NULL");
        return -1;
    }

    LogPrint(LOG_LEVEL_DEBUG, "Stack_Para_Debug", "configType = %s\n", configType);
    if (strcmp(configType, "MessageStop") == 0)
    {
        char *Messagetype = strGetJsonStringItem(jsonReqRoot, "Messagetype");
        if (NULL == Messagetype)
        {
            LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "MessageStop FAIL\n");
            cJSON_Delete(jsonReqRoot);
            jsonReqRoot = NULL;
            return -1;
        }
        if (strcmp(Messagetype, "bsmmessage") == 0)
        {
            setSendSwitch(p_ProtocolStackParamConfig, "BSMSendConfig", 0);
        }
        else if (strcmp(Messagetype, "rsmmessage") == 0)
        {
            setSendSwitch(p_ProtocolStackParamConfig, "RSMSendConfig", 0);
        }
        else if (strcmp(Messagetype, "mapmessage") == 0)
        {
            setSendSwitch(p_ProtocolStackParamConfig, "MAPSendConfig", 0);
        }
        else if (strcmp(Messagetype, "spatmessage") == 0)
        {
            setSendSwitch(p_ProtocolStackParamConfig, "SPATSendConfig", 0);
        }
        else if (strcmp(Messagetype, "rsimessage") == 0)
        {
            setSendSwitch(p_ProtocolStackParamConfig, "RSISendConfig", 0);
        }
        LogPrint(LOG_LEVEL_DEBUG, "Stack_Para_Debug", "MessageStop Sessuse\n");
        cJSON_Delete(jsonReqRoot);
        jsonReqRoot = NULL;
        return nRet;
    }
    else if (strcmp(configType, "MessageRestart") == 0)
    {
        char *Messageupload = strGetJsonStringItem(jsonReqRoot, "Messageupload");
        if (NULL == Messageupload)
        {
            LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "MessageStop FAIL\n");
            cJSON_Delete(jsonReqRoot);
            jsonReqRoot = NULL;
            return -1;
        }
        if (strcmp(Messageupload, "ok") == 0)
        {
            char *Messagetype = strGetJsonStringItem(jsonReqRoot, "Messagetype");
            if (strcmp(Messagetype, "bsmmessage") == 0)
            {
                setSendSwitch(p_ProtocolStackParamConfig, "BSMSendConfig", 1);
            }
            else if (strcmp(Messagetype, "rsmmessage") == 0)
            {
                setSendSwitch(p_ProtocolStackParamConfig, "RSMSendConfig", 1);
            }
            else if (strcmp(Messagetype, "mapmessage") == 0)
            {
                setSendSwitch(p_ProtocolStackParamConfig, "MAPSendConfig", 1);
            }
            else if (strcmp(Messagetype, "spatmessage") == 0)
            {
                setSendSwitch(p_ProtocolStackParamConfig, "SPATSendConfig", 1);
            }
            else if (strcmp(Messagetype, "rsimessage") == 0)
            {
                setSendSwitch(p_ProtocolStackParamConfig, "RSISendConfig", 1);
            }
        }
        LogPrint(LOG_LEVEL_DEBUG, "Stack_Para_Debug", "MessageRestart Sessuse\n");
        cJSON_Delete(jsonReqRoot);
        jsonReqRoot = NULL;
        return nRet;
    }

    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(FileName);
    if (strcmp(configType, "MsgVersion") == 0)
    {
        char *msgversion = strGetJsonStringItem(jsonReqRoot, "msgversion");
        if ((msgversion != NULL) && (p_ProtocolStackParamConfig->msgFrameConfig.MsgFrameVersion != atoi(msgversion)))
        {
            nRet = ini.SetValue("MsgFrameConfig", "MsgFrameVersion", msgversion);
            if (nRet)
            {
                p_ProtocolStackParamConfig->msgFrameConfig.MsgFrameVersion = atoi(msgversion);
            }
        }
    }
    else if (strcmp(configType, "SecurityParamConfig") == 0)
    {
        //判断是否需要写入文件、更新结构体
        char *isInclude = strGetJsonStringItem(jsonReqRoot, "SecuritySwitch");

        if ((isInclude != NULL) && (p_ProtocolStackParamConfig->securityParamConfig.s8SecuritySwitch != atoi(isInclude)))
        {
            nRet = ini.SetValue(configType, "SecuritySwitch", isInclude);
            if (nRet)
            {
                p_ProtocolStackParamConfig->securityParamConfig.s8SecuritySwitch = atoi(isInclude);
            }
        }

        char *SignDeviceType = strGetJsonStringItem(jsonReqRoot, "SignDeviceType");

        if ((SignDeviceType != NULL) && (p_ProtocolStackParamConfig->securityParamConfig.s8SignDeviceType != atoi(SignDeviceType)))
        {
            nRet = ini.SetValue(configType, "SignDeviceType", SignDeviceType);
            if (nRet)
            {
                p_ProtocolStackParamConfig->securityParamConfig.s8SignDeviceType = atoi(SignDeviceType);
            }
        }
    }
    else if (strcmp(configType, "ThirdPartyLibConfig") == 0)
    {
        //判断是否需要写入文件、更新结构体
        char *SqliteConfig = strGetJsonStringItem(jsonReqRoot, "SqliteConfig");
        if ((SqliteConfig != NULL) && (p_ProtocolStackParamConfig->thirdPartyLibConfig.SqliteConfig != atoi(SqliteConfig)))
        {
            nRet = ini.SetValue(configType, "SqliteConfig", SqliteConfig);
            if (nRet)
            {
                p_ProtocolStackParamConfig->thirdPartyLibConfig.SqliteConfig = atoi(SqliteConfig);
            }
        }
        char *StateMonitorConfig = strGetJsonStringItem(jsonReqRoot, "StateMonitorConfig");
        if ((StateMonitorConfig != NULL) && (p_ProtocolStackParamConfig->thirdPartyLibConfig.StateMonitorConfig != atoi(StateMonitorConfig)))
        {
            nRet = ini.SetValue(configType, "StateMonitorConfig", StateMonitorConfig);
            if (nRet)
            {
                p_ProtocolStackParamConfig->thirdPartyLibConfig.StateMonitorConfig = atoi(StateMonitorConfig);
            }
        }
    }
    else if (strcmp(configType, "DSMPParamConfig") == 0)
    {
        //判断是否需要写入文件、更新结构体
        char *StandardMessageAID = strGetJsonStringItem(jsonReqRoot, "StandardMessageAID");
        if ((StandardMessageAID != NULL) && (p_ProtocolStackParamConfig->DSMPParamConfig.StandardMessageAID != atoi(StandardMessageAID)))
        {
            nRet = ini.SetValue(configType, "StandardMessageAID", StandardMessageAID);
            if (nRet)
            {
                p_ProtocolStackParamConfig->DSMPParamConfig.StandardMessageAID = atoi(StandardMessageAID);
            }
        }

        char *PassMessageAID = strGetJsonStringItem(jsonReqRoot, "PassMessageAID");
        if ((PassMessageAID != NULL) && (p_ProtocolStackParamConfig->DSMPParamConfig.PassMessageAID != atoi(PassMessageAID)))
        {
            nRet = ini.SetValue(configType, "PassMessageAID", PassMessageAID);
            if (nRet)
            {
                p_ProtocolStackParamConfig->DSMPParamConfig.PassMessageAID = atoi(PassMessageAID);
            }
        }

        char *RecvLegalAIDList = strGetJsonStringItem(jsonReqRoot, "RecvLegalAIDList");
        if ((RecvLegalAIDList != NULL))
        {
            nRet = ini.SetValue(configType, "RecvLegalAIDList", RecvLegalAIDList);
            if (nRet)
            {
                int iNum = str2Intlist((const char *)RecvLegalAIDList, p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDList);
                p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDNum = iNum;
                BubbleSort(p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDList,
                           p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDNum);
            }
        }

        char *AIDListCheckMark = strGetJsonStringItem(jsonReqRoot, "AIDListCheckMark");
        if ((AIDListCheckMark != NULL) && (p_ProtocolStackParamConfig->DSMPParamConfig.AIDListCheckMark != atoi(AIDListCheckMark)))
        {
            nRet = ini.SetValue(configType, "AIDListCheckMark", AIDListCheckMark);
            if (nRet)
            {
                p_ProtocolStackParamConfig->DSMPParamConfig.AIDListCheckMark = atoi(AIDListCheckMark);
            }
        }
    }
    else if (strcmp(configType, "RecvParamConfig") == 0)
    {
        char *RecvSwitch = strGetJsonStringItem(jsonReqRoot, "RecvSwitch");
        if ((RecvSwitch != NULL) && p_ProtocolStackParamConfig->messageParamConfig.recvParamConfig.RecvSwitch != atoi(RecvSwitch))
        {
            nRet = ini.SetValue(configType, "RecvSwitch", RecvSwitch);
            if (nRet)
            {
                p_ProtocolStackParamConfig->messageParamConfig.recvParamConfig.RecvSwitch = atoi(RecvSwitch);
            }
        }
    }
    else if (strcmp(configType, "MessageAIDGroup") == 0)
    {
        string strDes = "";
        char *GroupType = strGetJsonStringItem(jsonReqRoot, "GroupType");
        //判断是否需要写入文件、更新结构体
        if ((GroupType != NULL))
        {
            int index = 0;
            string strDes = "";
            for (index = 0; index < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; index++)
            {
                if (atoi(GroupType) == p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupType[index])
                {
                    break;
                }
            }
            if (index >= p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum)
            {
                if (jsonReqRoot != NULL)
                {
                    cJSON_Delete(jsonReqRoot);
                    jsonReqRoot = NULL;
                }
                LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find GroupType = %s\n", configType);
                nRet = -1;
                return nRet;
            }

            char *GroupName = strGetJsonStringItem(jsonReqRoot, "GroupName");
            if (GroupName != NULL)
            {
                if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[index], GroupName) != 0)
                {
                    //判断修改项是否已经存在于结构体中，若存在　则不修改
                    int i = 0;
                    for (i = 0; i < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; i++)
                    {
                        if (strcmp(GroupName, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[i]) == 0)
                        {
                            if (jsonReqRoot != NULL)
                            {
                                cJSON_Delete(jsonReqRoot);
                                jsonReqRoot = NULL;
                            }
                            LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "GroupName is existing ,GroupName = %s\n", GroupName);
                            return -1;
                        }
                    }
                }
                //先修改对应的section
                int inum = 0;
                for (inum = 0; inum < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; inum++)
                {
                    if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[index],
                               p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[inum].m_nGroupName) == 0)
                    {
                        break;
                    }
                }
                if (inum >= p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum)
                {
                    if (jsonReqRoot != NULL)
                    {
                        cJSON_Delete(jsonReqRoot);
                        jsonReqRoot = NULL;
                    }
                    LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find SectionName = %s\n", configType);
                    nRet = -1;
                    return nRet;
                }

                if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[index], GroupName) != 0)
                {
                    //删除旧节点
                    ini.Delete(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[index], NULL);

                    //增加新节点
                    nRet = ini.SetValue(GroupName, NULL, NULL);
                    if (nRet)
                    {
                        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[inum].m_nGroupName, GroupName);

                        strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[inum].m_nMsgIDNum,
                                                p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[inum].m_nMsgName);
                        ini.SetValue(GroupName, "MsgName", (char *)strDes.c_str());

                        strDes = intList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[inum].m_nMsgIDNum,
                                             p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[inum].m_nMsgAIDList);
                        ini.SetValue(GroupName, "MsgAID", (char *)strDes.c_str());

                        strDes = intList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[inum].m_nMsgIDNum,
                                             p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[inum].m_nMsgIDList);
                        ini.SetValue(GroupName, "MsgID", (char *)strDes.c_str());

                        strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[inum].m_nMsgIDNum,
                                                p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[inum].m_nMsgDescrip);
                        ini.SetValue(GroupName, "MsgDescrip", (char *)strDes.c_str());
                    }
                }

                //修改MessageAIDGroup
                memset(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[index], 0, 32);
                strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[index], GroupName);
                strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum,
                                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName);
                ini.SetValue(configType, "GroupName", (char *)strDes.c_str());
            }

            char *GroupDescrip = strGetJsonStringItem(jsonReqRoot, "GroupDescrip");
            if (GroupDescrip != NULL)
            {
                memset(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip[index], 0, 32);
                strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip[index], GroupDescrip);
                strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum,
                                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip);
                ini.SetValue(configType, "GroupDescrip", (char *)strDes.c_str());
            }
        }
    }
    else
    {
        int MsgType = iGetJsonNumberItem(jsonReqRoot, "MsgType");
        //查找对应的发送策略参数
        int index = 0, chooseFlag = -1, m_index = 0;
        for (index = 0; index < p_ProtocolStackParamConfig->messageParamConfig.m_SendParamNum; index++)
        {
            //if(strstr(configType,p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSectionName))
            if ((strcmp(configType, p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSectionName) == 0) ||
                (MsgType == p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nMsgType))
            {
                chooseFlag = 0;
                break;
            }
        }
        if (chooseFlag != 0)
        {
            for (m_index = 0; m_index < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; m_index++)
            {
                if (strcmp(configType, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nGroupName) == 0)
                {
                    chooseFlag = 1;
                    break;
                }
            }
        }

        if (index >= p_ProtocolStackParamConfig->messageParamConfig.m_SendParamNum && m_index >= p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum)
        {
            if (jsonReqRoot != NULL)
            {
                cJSON_Delete(jsonReqRoot);
                jsonReqRoot = NULL;
            }
            LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find SectionName = %s\n", configType);
            nRet = -1;
            return nRet;
        }
        if (chooseFlag == 0)
        {
            char *SendSwitch = strGetJsonStringItem(jsonReqRoot, "SendSwitch");
            //判断是否需要写入文件、更新结构体
            if ((SendSwitch != NULL) && (p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSendSwitch != atoi(SendSwitch)))
            {
                nRet = ini.SetValue(configType, "SendSwitch", SendSwitch);
                if (nRet)
                {
                    p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSendSwitch = atoi(SendSwitch);
                }
            }
            char *SendFrequency = strGetJsonStringItem(jsonReqRoot, "SendFrequency");
            if ((SendFrequency != NULL) && (p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSendFrequency != atoi(SendFrequency)))
            {
                nRet = ini.SetValue(configType, "SendFrequency", SendFrequency);
                if (nRet)
                {
                    p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSendFrequency = atoi(SendFrequency);
                }
            }

            char *SendFilePath = strGetJsonStringItem(jsonReqRoot, "SendFilePath");
            if ((SendFilePath != NULL) && (strcmp(SendFilePath, p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSendFilePath) != 0))
            {
                nRet = ini.SetValue(configType, "SendFilePath", SendFilePath);
                if (nRet)
                {
                    strncpy(ProtocolStackParamConfig.messageParamConfig.m_SendParam[index].m_nSendFilePath, SendFilePath,
                            sizeof(ProtocolStackParamConfig.messageParamConfig.m_SendParam[index].m_nSendFilePath));
                }
            }
        }
        else if (chooseFlag == 1)
        {
            char *MsgID = strGetJsonStringItem(jsonReqRoot, "MsgID");
            if ((MsgID != NULL))
            {
                int inum = 0;
                string strDes = "";
                for (inum = 0; inum < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgIDNum; inum++)
                {
                    if (atoi(MsgID) == p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgIDList[inum])
                    {
                        break;
                    }
                }
                if (inum >= p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgIDNum)
                {
                    if (jsonReqRoot != NULL)
                    {
                        cJSON_Delete(jsonReqRoot);
                        jsonReqRoot = NULL;
                    }
                    LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find MsgID = %s\n", configType);
                    nRet = -1;
                    return nRet;
                }

                char *MsgName = strGetJsonStringItem(jsonReqRoot, "MsgName");
                if (MsgName != NULL)
                {
                    if (strcmp(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgName[inum], MsgName) != 0)
                    {
                        //判断修改项是否已经存在于结构体中，若存在　则不修改
                        int i = 0;
                        for (i = 0; i < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgIDNum; i++)
                        {
                            if (strcmp(MsgName, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgName[i]) == 0)
                            {
                                if (jsonReqRoot != NULL)
                                {
                                    cJSON_Delete(jsonReqRoot);
                                    jsonReqRoot = NULL;
                                }
                                LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find m_nMsgName = %s\n", MsgName);
                                return -1;
                            }
                        }
                    }

                    memset(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgName[inum], 0, 32);
                    strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgName[inum], MsgName);
                    strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgIDNum,
                                            p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgName);
                    ini.SetValue(configType, "MsgName", (char *)strDes.c_str());
                }

                char *MsgDescrip = strGetJsonStringItem(jsonReqRoot, "MsgDescrip");
                if (MsgDescrip != NULL)
                {
                    memset(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgDescrip[inum], 0, 32);
                    strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgDescrip[inum], MsgDescrip);
                    strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgIDNum,
                                            p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgDescrip);
                    ini.SetValue(configType, "MsgDescrip", (char *)strDes.c_str());
                }

                char *MsgAID = strGetJsonStringItem(jsonReqRoot, "MsgAID");
                if (MsgAID != NULL)
                {
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgAIDList[inum] = atoi(MsgAID);
                    strDes = intList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgIDNum,
                                         p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[m_index].m_nMsgAIDList);
                    ini.SetValue(configType, "MsgAID", (char *)strDes.c_str());

                    //依据配置修改publicMsg中的AID
                    setStaticAIDFromConfig(p_ProtocolStackParamConfig);
                }
            }
        }
    }

    ini.SaveFile(FileName);

    if (jsonReqRoot != NULL)
    {
        cJSON_Delete(jsonReqRoot);
        jsonReqRoot = NULL;
    }

    return nRet;
}

/**
 * @brief 更新文件并设置结构体数据
 */
static int addParamDataTest(ProtocolStackParamConfig_t *p_ProtocolStackParamConfig, const char *souceString, char *FileName)
{
    if (NULL == FileName || NULL == souceString || NULL == p_ProtocolStackParamConfig)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "param is NULL\n");
        return -1;
    }

    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(FileName);

    int nRet = 1; //返回1为成功
    //cJSON *jsonReqRoot = cJSON_CreateObject();
    cJSON *jsonReqRoot = cJSON_Parse(souceString);

    char *configType = strGetJsonStringItem(jsonReqRoot, "ConfigType");

    if (strcmp(configType, "MessageAIDGroup") == 0)
    {
        int inum = 0;
        string strDes = "";
        char *GroupName = strGetJsonStringItem(jsonReqRoot, "GroupName");

        //判断添加项是否已经存在于结构体中，若存在　则不添加
        int i = 0;
        for (i = 0; i < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; i++)
        {
            if (strcmp(GroupName, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[i]) == 0)
            {
                if (jsonReqRoot != NULL)
                {
                    cJSON_Delete(jsonReqRoot);
                    jsonReqRoot = NULL;
                }
                LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "GroupName is existing ,GroupName = %s\n", GroupName);
                return -1;
            }
        }
        strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum,
                                p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName);

        if (strDes.length() <= 0)
            strDes += (string)GroupName;
        else
            strDes += "," + (string)GroupName;

        //判断是否需要写入文件、更新结构体
        if ((GroupName != NULL))
        {
            nRet = ini.SetValue(configType, "GroupName", (char *)strDes.c_str());
            if (nRet)
            {
                str2Stringlist((const char *)strDes.c_str(), p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName);
            }
        }

        char *GroupDescrip = strGetJsonStringItem(jsonReqRoot, "GroupDescrip");
        strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum,
                                p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip);
        if (strDes.length() <= 0)
            strDes += (string)GroupDescrip;
        else
            strDes += "," + (string)GroupDescrip;

        //判断是否需要写入文件、更新结构体
        if ((GroupDescrip != NULL))
        {
            nRet = ini.SetValue(configType, "GroupDescrip", (char *)strDes.c_str());
            if (nRet)
            {
                str2Stringlist((const char *)strDes.c_str(), p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip);
            }
        }

        char *GroupType = strGetJsonStringItem(jsonReqRoot, "GroupType");
        strDes = intList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum,
                             p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupType);

        int index = p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum;
        int NewGroupID = p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupType[index - 1] + 1;

        if (strDes.length() <= 0)
            strDes += intTostring(NewGroupID);
        else
            strDes += "," + (string)intTostring(NewGroupID);

        //判断是否需要写入文件、更新结构体
        if ((GroupType != NULL))
        {
            nRet = ini.SetValue(configType, "GroupType", (char *)strDes.c_str());
            if (nRet)
            {
                inum = str2Intlist((const char *)strDes.c_str(), p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupType);
                p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum = inum;
            }
        }
        nRet = ini.SetValue(GroupName, NULL, NULL);
        if (nRet)
        {
            ini.SetValue(GroupName, "MsgName", "");
            ini.SetValue(GroupName, "MsgAID", "");
            ini.SetValue(GroupName, "MsgID", "");
            ini.SetValue(GroupName, "MsgDescrip", "");

            int index = p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum - 1;
            strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, GroupName);
        }
    }
    else
    {
        //查找对应的发送策略参数
        int index = 0;
        for (index = 0; index < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; index++)
        {
            if (strcmp(configType, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName) == 0)
            {
                break;
            }
        }
        if (index >= p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum)
        {
            if (jsonReqRoot != NULL)
            {
                cJSON_Delete(jsonReqRoot);
                jsonReqRoot = NULL;
            }
            LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find m_nGroupName = %s\n", configType);
            nRet = -1;
            return nRet;
        }

        {
            int inum = 0;
            string strDes = "";

            char *MsgName = strGetJsonStringItem(jsonReqRoot, "MsgName");

            //判断添加项是否已经存在于结构体中，若存在　则不添加
            int i = 0;
            for (i = 0; i < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum; i++)
            {
                if (strcmp(MsgName, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgName[i]) == 0)
                {
                    if (jsonReqRoot != NULL)
                    {
                        cJSON_Delete(jsonReqRoot);
                        jsonReqRoot = NULL;
                    }
                    LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find m_nMsgName = %s\n", MsgName);
                    return -1;
                }
            }

            strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum,
                                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgName);

            if (strDes.length() <= 0)
                strDes += (string)MsgName;
            else
                strDes += "," + (string)MsgName;

            //判断是否需要写入文件、更新结构体
            if ((MsgName != NULL))
            {
                nRet = ini.SetValue(configType, "MsgName", (char *)strDes.c_str());
                if (nRet)
                {
                    str2Stringlist((const char *)strDes.c_str(), p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgName);
                }
            }
            char *MsgDescrip = strGetJsonStringItem(jsonReqRoot, "MsgDescrip");
            strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum,
                                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgDescrip);
            if (strDes.length() <= 0)
                strDes += (string)MsgDescrip;
            else
                strDes += "," + (string)MsgDescrip;

            //判断是否需要写入文件、更新结构体
            if ((MsgDescrip != NULL))
            {
                nRet = ini.SetValue(configType, "MsgDescrip", (char *)strDes.c_str());
                if (nRet)
                {
                    str2Stringlist((const char *)strDes.c_str(), p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgDescrip);
                }
            }
            char *MsgAID = strGetJsonStringItem(jsonReqRoot, "MsgAID");
            strDes = intList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum,
                                 p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList);

            if (strDes.length() <= 0)
                strDes += (string)MsgAID;
            else
                strDes += "," + (string)MsgAID;

            //判断是否需要写入文件、更新结构体
            if ((MsgAID != NULL))
            {
                nRet = ini.SetValue(configType, "MsgAID", (char *)strDes.c_str());
                if (nRet)
                {
                    inum = str2Intlist((const char *)strDes.c_str(), p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList);
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum = inum;

                    //依据配置修改publicMsg中的AID
                    setStaticAIDFromConfig(p_ProtocolStackParamConfig);
                }
            }

            char *MsgID = strGetJsonStringItem(jsonReqRoot, "MsgID");
            strDes = intList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum,
                                 p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList);

            int MsgIDNum = p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum;
            int NewMsgID = p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[MsgIDNum - 1] + 1;
            if (strDes.length() <= 0)
                strDes += intTostring(NewMsgID);
            else
                strDes += "," + intTostring(NewMsgID);
            //判断是否需要写入文件、更新结构体
            if ((MsgID != NULL))
            {
                nRet = ini.SetValue(configType, "MsgID", (char *)strDes.c_str());
                if (nRet)
                {
                    inum = str2Intlist((const char *)strDes.c_str(), p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList);
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum = inum;
                }
            }
        }
    }

    ini.SaveFile(FileName);
    if (jsonReqRoot != NULL)
    {
        cJSON_Delete(jsonReqRoot);
        jsonReqRoot = NULL;
    }

    return nRet;
}

/**
 * @brief 更新文件并设置结构体数据
 */
static int deleteParamDataTest(ProtocolStackParamConfig_t *p_ProtocolStackParamConfig, const char *souceString, char *FileName)
{
    if (NULL == FileName || NULL == souceString || NULL == p_ProtocolStackParamConfig)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "param is NULL\n");
        return -1;
    }
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(FileName);

    int nRet = 1; //返回1为成功
    //cJSON *jsonReqRoot = cJSON_CreateObject();
    cJSON *jsonReqRoot = cJSON_Parse(souceString);

    char *configType = strGetJsonStringItem(jsonReqRoot, "ConfigType");

    if (strcmp(configType, "MessageAIDGroup") == 0)
    {

        string strDes = "";
        int index = 0;
        bool FindFlag = true;
        char *GroupName = strGetJsonStringItem(jsonReqRoot, "GroupName");
        //判断添加项是否已经存在于结构体中，若存在　则删除
        for (index = 0; index < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; index++)
        {
            if (strcmp(GroupName, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[index]) == 0)
            {
                FindFlag = false;
                int j = index;
                for (j = index; j < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; j++)
                {
                    memset(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[j], 0x00, 32);
                    memset(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip[j], 0x00, 32);
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupType[j] = 0;

                    memset(&(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[j]), 0x00,
                           sizeof(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[j]));

                    if (j + 1 >= p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum)
                        break;

                    strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[j],
                           p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[j + 1]);

                    strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip[j],
                           p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip[j + 1]);

                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupType[j] =
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupType[j + 1];

                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[j] =
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[j + 1];
                }
                p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum -= 1;
                break;
            }
        }

        if (FindFlag)
        {
            //没有找到情况下
            if (index >= p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum)
            {
                if (jsonReqRoot != NULL)
                {
                    cJSON_Delete(jsonReqRoot);
                    jsonReqRoot = NULL;
                }
                LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find m_nGroupName = %s\n", GroupName);
                return -1;
            }
        }

        strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum,
                                p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName);
        //判断是否需要写入文件、更新结构体
        if ((GroupName != NULL))
        {
            ini.SetValue(configType, "GroupName", (char *)strDes.c_str());
        }

        //char *GroupDescrip = strGetJsonStringItem(jsonReqRoot, "GroupDescrip");
        strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum,
                                p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip);

        //判断是否需要写入文件、更新结构体
        //if ((GroupDescrip != NULL))
        {
            ini.SetValue(configType, "GroupDescrip", (char *)strDes.c_str());
        }

        //char *GroupType = strGetJsonStringItem(jsonReqRoot, "GroupID");
        strDes = intList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum,
                             p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupType);
        //判断是否需要写入文件、更新结构体
        //if ((GroupType != NULL))
        {
            ini.SetValue(configType, "GroupType", (char *)strDes.c_str());
        }

        //删除旧节点
        nRet = ini.Delete(GroupName, NULL);
        if (nRet)
        {
            //此处最好使用vector
            //memset(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName, 0x00, 32);
        }
    }
    else
    {
        //查找对应的发送策略参数
        int index = 0;
        for (index = 0; index < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; index++)
        {
            if (strcmp(configType, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName) == 0)
            {
                break;
            }
        }
        if (index >= p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum)
        {
            if (jsonReqRoot != NULL)
            {
                cJSON_Delete(jsonReqRoot);
                jsonReqRoot = NULL;
            }
            LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find m_nGroupName = %s\n", configType);
            nRet = -1;
            return nRet;
        }

        {
            string strDes = "";

            char *MsgName = strGetJsonStringItem(jsonReqRoot, "MsgName");
            int i = 0;
            bool FindFlag = true;
            //判断添加项是否已经存在于结构体中，若存在　则不添加
            for (i = 0; i < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum; i++)
            {
                if (strcmp(MsgName, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgName[i]) == 0)
                {
                    FindFlag = false;
                    int j = i;
                    for (j = i; j < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum; j++)
                    {
                        memset(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgName[j], 0x00, 32);
                        memset(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgDescrip[j], 0x00, 32);
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[j] = 0;
                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[j] = 0;

                        if (j + 1 >= p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum)
                            break;

                        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgName[j],
                               p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgName[j + 1]);

                        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgDescrip[j],
                               p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgDescrip[j + 1]);

                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[j] =
                            p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[j + 1];

                        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[j] =
                            p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[j + 1];
                    }
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum -= 1;
                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum -= 1;

                    break;
                }
            }
            if (FindFlag)
            {
                if (i >= p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum)
                {
                    if (jsonReqRoot != NULL)
                    {
                        cJSON_Delete(jsonReqRoot);
                        jsonReqRoot = NULL;
                    }
                    LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find m_nMsgName = %s\n", MsgName);
                    return -1;
                }
            }

            strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum,
                                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgName);

            //判断是否需要写入文件、更新结构体
            if ((MsgName != NULL))
            {
                ini.SetValue(configType, "MsgName", (char *)strDes.c_str());
            }
            //char *MsgDescrip = strGetJsonStringItem(jsonReqRoot, "MsgDescrip");
            strDes = stringList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum,
                                    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgDescrip);

            //判断是否需要写入文件、更新结构体
            //if ((MsgDescrip != NULL))
            {
                ini.SetValue(configType, "MsgDescrip", (char *)strDes.c_str());
            }
            //char *MsgAID = strGetJsonStringItem(jsonReqRoot, "MsgAID");
            strDes = intList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum,
                                 p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList);

            //判断是否需要写入文件、更新结构体
            //if ((MsgAID != NULL))
            {
                ini.SetValue(configType, "MsgAID", (char *)strDes.c_str());
                //依据配置修改publicMsg中的AID
                setStaticAIDFromConfig(p_ProtocolStackParamConfig);
            }

            //char *MsgID = strGetJsonStringItem(jsonReqRoot, "MsgID");
            strDes = intList2str(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum,
                                 p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList);
            //判断是否需要写入文件、更新结构体
            //if ((MsgID != NULL))
            {
                ini.SetValue(configType, "MsgID", (char *)strDes.c_str());
            }
        }
    }
    ini.SaveFile(FileName);
    if (jsonReqRoot != NULL)
    {
        cJSON_Delete(jsonReqRoot);
        jsonReqRoot = NULL;
    }

    return nRet;
}
/**
 * @brief 更新文件并设置结构体数据
 */
static int queryParamDataTest(ProtocolStackParamConfig_t *p_ProtocolStackParamConfig, const char *souceString, string &retstring, char *FileName)
{
    if (NULL == FileName || NULL == souceString || NULL == p_ProtocolStackParamConfig)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "param is NULL\n");
        return -1;
    }

    int nRet = 1; //返回1为成功
    char *strPostRequest = NULL;
    //cJSON *jsonReqRoot = cJSON_CreateObject();
    cJSON *jsonRetRoot = cJSON_CreateObject();

    cJSON *jsonReqRoot = cJSON_Parse(souceString);

    char *configType = strGetJsonStringItem(jsonReqRoot, "ConfigType");
    char *ModuleName = strGetJsonStringItem(jsonReqRoot, "ModuleName");
    char *Source = strGetJsonStringItem(jsonReqRoot, "Source");
    char *Operation = strGetJsonStringItem(jsonReqRoot, "Operation");

    //指示本数据的传输对象
    if (ModuleName != NULL)
        cJSON_AddStringToObject(jsonRetRoot, "ModuleName", ModuleName);
    //指示本消息的来源模块
    if (Source != NULL)
        cJSON_AddStringToObject(jsonRetRoot, "Source", Source);
    //本次指令的行为，设置，查询，下载
    if (Operation != NULL)
        cJSON_AddStringToObject(jsonRetRoot, "Operation", Operation);

    cJSON_AddStringToObject(jsonRetRoot, "ConfigType", configType);

    if (strcmp(configType, "AIDLIST") == 0)
    {
        char *parentCode = strGetJsonStringItem(jsonReqRoot, "parentCode");
        if (parentCode != NULL)
        {
            if (strcmp(parentCode, "0") == 0)
            {
                cJSON_AddStringToObject(jsonRetRoot, "parentCode", parentCode);
                cJSON_AddNumberToObject(jsonRetRoot, "count", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum);
                cJSON *subArray = cJSON_CreateArray();
                int i = 0;
                for (i = 0; i < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; i++)
                {
                    cJSON *sub = cJSON_CreateObject();
                    cJSON_AddNumberToObject(sub, "aid", 0);
                    cJSON_AddStringToObject(sub, "descrip", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip[i]);
                    cJSON_AddStringToObject(sub, "id", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[i]);
                    cJSON_AddStringToObject(sub, "isRoot", "TRUE");
                    cJSON_AddStringToObject(sub, "msg", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip[i]);
                    cJSON_AddNumberToObject(sub, "msgid", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupType[i]);
                    cJSON_AddStringToObject(sub, "name", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName[i]);
                    cJSON_AddStringToObject(sub, "parentCode", parentCode);
                    cJSON_AddNumberToObject(sub, "treeLevel", 0);
                    cJSON_AddItemToArray(subArray, sub);
                }
                cJSON_AddItemToObject(jsonRetRoot, "list", subArray);
                cJSON_AddNumberToObject(jsonRetRoot, "pageNo", 1);
                cJSON_AddNumberToObject(jsonRetRoot, "pageSize", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum);
            }
            else
            {
                //查找对应的发送策略参数
                int index = 0;
                for (index = 0; index < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum; index++)
                {
                    //if(strstr(parentCode,p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSectionName))
                    if (strcmp(parentCode, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nGroupName) == 0)
                    {
                        break;
                    }
                }
                if (index >= p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum)
                {
                    cJSON_AddStringToObject(jsonRetRoot, "Result", "FAIL");

                    strPostRequest = cJSON_PrintUnformatted(jsonRetRoot);
                    if (strPostRequest != NULL)
                    {
                        retstring = strPostRequest;
                        cJSON_free(strPostRequest);
                    }
                    nRet = -1;
                    LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find m_nGroupName = %s\n", parentCode);
                    goto ERROR;
                }
                cJSON_AddStringToObject(jsonRetRoot, "parentCode", parentCode);
                cJSON_AddNumberToObject(jsonRetRoot, "count", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum);
                cJSON *subArray = cJSON_CreateArray();
                int i = 0;
                for (i = 0; i < p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDNum; i++)
                {
                    cJSON *sub = cJSON_CreateObject();
                    cJSON_AddNumberToObject(sub, "aid", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[i]);
                    cJSON_AddStringToObject(sub, "descrip", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgDescrip[i]);
                    cJSON_AddStringToObject(sub, "id", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgName[i]);

                    cJSON_AddStringToObject(sub, "isRoot", "FALSE");
                    cJSON_AddStringToObject(sub, "isTreeLeaf", "TRUE");
                    cJSON_AddStringToObject(sub, "msg", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgDescrip[i]);
                    cJSON_AddNumberToObject(sub, "msgid", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgIDList[i]);
                    cJSON_AddStringToObject(sub, "name", p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgName[i]);
                    cJSON_AddStringToObject(sub, "parentCode", parentCode);
                    cJSON_AddNumberToObject(sub, "treeLeaf", 1);
                    cJSON_AddNumberToObject(sub, "treeLevel", 1);

                    cJSON_AddItemToArray(subArray, sub);
                }
                cJSON_AddItemToObject(jsonRetRoot, "list", subArray);
                cJSON_AddNumberToObject(jsonRetRoot, "pageNo", 1);
                cJSON_AddNumberToObject(jsonRetRoot, "pageSize", -1);
            }
        }
    }
    else if (strcmp(configType, "SecurityParamConfig") == 0)
    {
        //cJSON *subRetRoot = cJSON_CreateObject();
        //if (subRetRoot != NULL)
        {
            cJSON_AddStringToObject(jsonRetRoot, "SecuritySwitch",
                                    intTostring(p_ProtocolStackParamConfig->securityParamConfig.s8SecuritySwitch).c_str());

            cJSON_AddStringToObject(jsonRetRoot, "SignDeviceType",
                                    intTostring(p_ProtocolStackParamConfig->securityParamConfig.s8SignDeviceType).c_str());
        }

        //cJSON_AddItemToObject(jsonRetRoot, configType, subRetRoot);
    }
    else if (strcmp(configType, "DSMPParamConfig") == 0)
    {

        //cJSON *subRetRoot = cJSON_CreateObject();
        //if (subRetRoot != NULL)
        {
            cJSON_AddStringToObject(jsonRetRoot, "StandardMessageAID",
                                    intTostring(p_ProtocolStackParamConfig->DSMPParamConfig.StandardMessageAID).c_str());

            cJSON_AddStringToObject(jsonRetRoot, "PassMessageAID",
                                    intTostring(p_ProtocolStackParamConfig->DSMPParamConfig.PassMessageAID).c_str());

            string strRecvLegalAIDList = intList2str(p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDNum,
                                                     p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDList);
            cJSON_AddStringToObject(jsonRetRoot, "RecvLegalAIDList", strRecvLegalAIDList.c_str());
            cJSON_AddStringToObject(jsonRetRoot, "AIDListCheckMark",
                                    intTostring(p_ProtocolStackParamConfig->DSMPParamConfig.AIDListCheckMark).c_str());
        }

        //cJSON_AddItemToObject(jsonRetRoot, configType, subRetRoot);
    }
    else if (strcmp(configType, "RecvParamConfig") == 0)
    {
        //cJSON *subRetRoot = cJSON_CreateObject();
        //if (subRetRoot != NULL)
        {
            cJSON_AddStringToObject(jsonRetRoot, "RecvSwitch",
                                    intTostring(p_ProtocolStackParamConfig->messageParamConfig.recvParamConfig.RecvSwitch).c_str());
        }

        //cJSON_AddItemToObject(jsonRetRoot, configType, subRetRoot);
    }
    else
    {
        //查找对应的发送策略参数
        int index = 0;
        for (index = 0; index < p_ProtocolStackParamConfig->messageParamConfig.m_SendParamNum; index++)
        {
            //if(strstr(configType,p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSectionName))
            if (strcmp(configType, p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSectionName) == 0)
            {
                break;
            }
        }
        if (index >= p_ProtocolStackParamConfig->messageParamConfig.m_SendParamNum)
        {
            cJSON_AddStringToObject(jsonRetRoot, "Result", "FAIL");
            strPostRequest = cJSON_PrintUnformatted(jsonRetRoot);
            if (strPostRequest != NULL)
            {
                retstring = strPostRequest;
                cJSON_free(strPostRequest);
            }
            nRet = -1;
            LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Not find m_nSectionName = %s\n", configType);
            goto ERROR;
        }

        //cJSON *subRetRoot = cJSON_CreateObject();
        //if (subRetRoot != NULL)
        {
            cJSON_AddStringToObject(jsonRetRoot, "SendSwitch",
                                    intTostring(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSendSwitch).c_str());

            cJSON_AddStringToObject(jsonRetRoot, "SendFrequency",
                                    intTostring(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSendFrequency).c_str());

            cJSON_AddStringToObject(jsonRetRoot, "SendSource",
                                    intTostring(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[index].m_nSendSwitch).c_str());
        }
        //cJSON_AddItemToObject(jsonRetRoot, configType, subRetRoot);
    }

    cJSON_AddStringToObject(jsonRetRoot, "Result", "SUCCESS");

    strPostRequest = cJSON_PrintUnformatted(jsonRetRoot);
    if (strPostRequest != NULL)
    {
        retstring = strPostRequest;
        cJSON_free(strPostRequest);
    }

    if (jsonReqRoot != NULL)
    {
        cJSON_Delete(jsonReqRoot);
        jsonReqRoot = NULL;
    }
    //此处无需释放subRetRoot，在释放jsonRetRoot时　已经把subRetRoot释放
    if (jsonRetRoot != NULL)
    {
        cJSON_Delete(jsonRetRoot);
        jsonRetRoot = NULL;
    }

    return nRet;

ERROR:
    if (jsonReqRoot != NULL)
    {
        cJSON_Delete(jsonReqRoot);
        jsonReqRoot = NULL;
    }
    if (jsonRetRoot != NULL)
    {
        cJSON_Delete(jsonRetRoot);
        jsonRetRoot = NULL;
    }

    return nRet;
}
/**************************************************
*名称： 初始化参数函数
*描述： 系统初始化，从配置文件中读取参数
*参数：
*       p_ProtocolStackParamConfig		 配置文件结构体变量
*       FileName		                 配置文件
*返回值：0--成功；
*返回值：非0--错误号。
*说明：无
**************************************************/
int WJ_InitParamDataInterface(ProtocolStackParamConfig_t *p_ProtocolStackParamConfig, char *FileName)
{

    if (NULL == FileName || NULL == p_ProtocolStackParamConfig)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "param is NULL\n");
        return -1;
    }
    int iVariable = 0;
    char strVariable[32] = {0}, strVariableBak[256] = {0};
    const char *strVariablePtr = NULL;

    int index = 0, i = 0, m_index = 0;
    char MessageGroup[32][32] = {0};
    char MessageAIDGroup[32][32] = {0};
    int ides[32] = {0};

    /*判断文件是否存在*/
    int l_n32ret = access(FileName, 0);
    if (l_n32ret < 0)
    {
        //若不存在，则设置关键数值的系统默认值
        //若配置文件不存在情况下，暂时以默认频率设置默认值
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParamNum = 6;
        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[0].m_nSectionName, "BSMSendConfig");
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[0].m_nSendFrequency = 10;
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[0].m_nSendSwitch = 1;
        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[0].m_nSendFilePath, BSMPATH);
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[0].m_nMsgType = 1;

        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[4].m_nSectionName, "RSISendConfig");
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[4].m_nSendFrequency = 2;
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[4].m_nSendSwitch = 1;
        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[4].m_nSendFilePath, RSIPATH);
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[4].m_nMsgType = 5;

        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[1].m_nSectionName, "MAPSendConfig");
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[1].m_nSendFrequency = 2;
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[1].m_nSendSwitch = 1;
        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[1].m_nSendFilePath, MAPPATH);
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[1].m_nMsgType = 2;

        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[3].m_nSectionName, "SPATSendConfig");
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[3].m_nSendFrequency = 2;
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[3].m_nSendSwitch = 1;
        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[3].m_nSendFilePath, SPATPATH);
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[3].m_nMsgType = 4;

        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[2].m_nSectionName, "RSMSendConfig");
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[2].m_nSendFrequency = 10;
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[2].m_nSendSwitch = 1;
        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[2].m_nSendFilePath, RSMPATH);
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[2].m_nMsgType = 3;

        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[5].m_nSectionName, "PassSendConfig");
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[5].m_nSendFrequency = 10;
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[5].m_nSendSwitch = 1;
        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[5].m_nSendFilePath, "");

        //设置为默认包含安全层签名
        p_ProtocolStackParamConfig->securityParamConfig.s8SecuritySwitch = 1;
        p_ProtocolStackParamConfig->securityParamConfig.s8EncryptChipType = 1;
        p_ProtocolStackParamConfig->securityParamConfig.s8SignDeviceType = 1;
        p_ProtocolStackParamConfig->securityParamConfig.s8EncryptChipSpeed = 1;
        p_ProtocolStackParamConfig->securityParamConfig.s32EncryptChipPinInt0 = 1;
        p_ProtocolStackParamConfig->securityParamConfig.s32EncryptChipPinInt1 = 1;

        //DSMP层参数设置
        p_ProtocolStackParamConfig->DSMPParamConfig.StandardMessageAID = 17;
        p_ProtocolStackParamConfig->DSMPParamConfig.PassMessageAID = 16;
        p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDNum = 2;
        p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDList[0] = 16;
        p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDList[1] = 17;
        p_ProtocolStackParamConfig->DSMPParamConfig.AIDListCheckMark = 1;
        //接收参数设置
        p_ProtocolStackParamConfig->messageParamConfig.recvParamConfig.RecvSwitch = 1;

        //第三方库使用设置
        p_ProtocolStackParamConfig->thirdPartyLibConfig.SqliteConfig = 0;
        p_ProtocolStackParamConfig->thirdPartyLibConfig.StateMonitorConfig = 0;

        //AID设置默认值
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.DSAMSGAID = 3616;         //DSA发送
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.BSMOrdinaryConven = 111;  //普通车辆+常规型BSMAID
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.BSMOrdinaryEvent = 112;   //普通车辆+事件型BSMAID
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.BSMSpecialConven = 113;   //特殊车辆+常规型BSMAID
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.BSMSpecialEvent = 114;    //特殊车辆+事件型BSMAID
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.BSMAfterLoading = 3617;   //后装车载终端
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.MAPMSGAID = 3618;         //地图类应用
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.SPATMSGAID = 3619;        //信号灯类应用
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.RSIRoadStatic = 3620;     //道路信息-静态类应用-RSIAID
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.RSIRoadHalfStatic = 3621; //道路信息-半静态类应用-RSIAID
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.RSIRoadDynamic = 3622;    //道路信息-动态类应用-RSIAID
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.RSMMSGAID = 3623;         //道路提醒类应用
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.TESTBSMMSGAID = 3624;     //测试车辆发送
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.TESTRSIMSGAID = 3625;     //测试路测发送1
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.TESTRSIMSGAID2 = 3626;    //测试路测发送2
        p_ProtocolStackParamConfig->messageParamConfig.msgAid.PASSMSGAID = 17;          //消息透传

        //消息层版本设置
        p_ProtocolStackParamConfig->msgFrameConfig.MsgFrameVersion = 4;

        //依据配置文件路径初始化日志模块
        strcpy(ProtocolStackParamConfig.logConfigPath.logConfigFilePath, "/mnt/APP/Config/RsuLogConfig/rsulog.conf");

        ProtocolStackParamConfig.v2xStatusFlag.v2xStatus = 1;
        LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "param is NULL\n");
        return -1;
    }

    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(FileName);
    //消息层参数设置
    strVariablePtr = ini.GetValue("MessageGroup", "GroupName", NULL /*default*/);
    m_index = str2Stringlist(strVariablePtr, MessageGroup);

    strVariablePtr = ini.GetValue("MessageGroup", "GroupID", NULL);
    LogPrint(LOG_LEVEL_DEBUG, "Stack_Para_Debug", "strVariablePtr = %s\n", strVariablePtr);
    if (NULL != strVariablePtr)
    {
        memset(strVariableBak, 0x00, sizeof(strVariableBak));
        memcpy(strVariableBak, strVariablePtr, strlen(strVariablePtr));
    }
    m_index = str2Intlist(strVariablePtr, ides);
    if (m_index < 15)
    {
        printf("%s %s %d %d\n", __FILE__, __FUNCTION__, __LINE__, m_index);
        m_index = str2IntlistBak(strVariableBak, ides);
    }

    p_ProtocolStackParamConfig->messageParamConfig.m_SendParamNum = m_index;

    strVariablePtr = ini.GetValue("MessageAIDGroup", "GroupDescrip", NULL);
    str2Stringlist(strVariablePtr, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupDescrip);

    strVariablePtr = ini.GetValue("MessageAIDGroup", "GroupName", NULL);
    if (NULL != strVariablePtr)
    {
        memset(strVariableBak, 0x00, sizeof(strVariableBak));
        memcpy(strVariableBak, strVariablePtr, strlen(strVariablePtr));
    }
    index = str2Stringlist(strVariablePtr, MessageAIDGroup);
    str2Stringlist(strVariableBak, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupName);

    strVariablePtr = ini.GetValue("MessageAIDGroup", "GroupType", NULL);
    str2Intlist(strVariablePtr, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_nGroupType);

    p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum = index;
    printf("%s %s %d %d %d\n", __FILE__, __FUNCTION__, __LINE__, index, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_GroupNum);
    printf("%s %s %d %d %d\n", __FILE__, __FUNCTION__, __LINE__, m_index, p_ProtocolStackParamConfig->messageParamConfig.m_SendParamNum);
    LogPrint(LOG_LEVEL_DEBUG, "Stack_Para_Debug", "m_SendParamNum = %d\n", p_ProtocolStackParamConfig->messageParamConfig.m_SendParamNum);
    for (i = 0; i < m_index; i++)
    {
        sprintf(strVariable, "%sSendConfig", MessageGroup[i]);
        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[i].m_nSectionName, strVariable);
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[i].m_nMsgType = ides[i];

        iVariable = ini.GetLongValue(strVariable, "SendSwitch", 0);
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[i].m_nSendSwitch = iVariable;

        iVariable = ini.GetLongValue(strVariable, "SendFrequency", 0);
        p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[i].m_nSendFrequency = iVariable;

        strVariablePtr = ini.GetValue(strVariable, "SendFilePath", NULL);
        if (NULL != strVariablePtr)
        {
            strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_SendParam[i].m_nSendFilePath, strVariablePtr);
        }
    }

    for (i = 0; i < index; i++)
    {

        strcpy(p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[i].m_nGroupName, MessageAIDGroup[i]);
        strVariablePtr = ini.GetValue(MessageAIDGroup[i], "MsgID", NULL);
        m_index = str2Intlist(strVariablePtr,
                              p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[i].m_nMsgIDList);
        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[i].m_nMsgIDNum = m_index;

        strVariablePtr = ini.GetValue(MessageAIDGroup[i], "MsgAID", NULL);
        m_index = str2Intlist(strVariablePtr,
                              p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[i].m_nMsgAIDList);
        p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[i].m_nMsgAIDNum = m_index;

        strVariablePtr = ini.GetValue(MessageAIDGroup[i], "MsgName", NULL);
        str2Stringlist(strVariablePtr, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[i].m_nMsgName);

        strVariablePtr = ini.GetValue(MessageAIDGroup[i], "MsgDescrip", NULL);
        str2Stringlist(strVariablePtr, p_ProtocolStackParamConfig->messageParamConfig.m_AIDGroup.m_AidGroupConfig[i].m_nMsgDescrip);
    }

    iVariable = ini.GetLongValue("RecvParamConfig", "RecvSwitch", 0);
    p_ProtocolStackParamConfig->messageParamConfig.recvParamConfig.RecvSwitch = iVariable;

    //安全层参数设置
    iVariable = ini.GetLongValue("SecurityParamConfig", "SecuritySwitch", 0);
    p_ProtocolStackParamConfig->securityParamConfig.s8SecuritySwitch = iVariable;

    iVariable = ini.GetLongValue("SecurityParamConfig", "EncryptChipType", 1);
    p_ProtocolStackParamConfig->securityParamConfig.s8EncryptChipType = iVariable;

    iVariable = ini.GetLongValue("SecurityParamConfig", "SignDeviceType", 1);
    p_ProtocolStackParamConfig->securityParamConfig.s8SignDeviceType = iVariable;

    iVariable = ini.GetLongValue("SecurityParamConfig", "EncryptChipSpeed", 0);
    p_ProtocolStackParamConfig->securityParamConfig.s8EncryptChipSpeed = iVariable;

    iVariable = ini.GetLongValue("SecurityParamConfig", "EncryptChipPinInt0", 0);
    p_ProtocolStackParamConfig->securityParamConfig.s32EncryptChipPinInt0 = iVariable;

    iVariable = ini.GetLongValue("SecurityParamConfig", "EncryptChipPinInt1", 0);
    p_ProtocolStackParamConfig->securityParamConfig.s32EncryptChipPinInt1 = iVariable;
    //DSMP层参数设置
    iVariable = ini.GetLongValue("DSMPParamConfig", "StandardMessageAID", 0);
    p_ProtocolStackParamConfig->DSMPParamConfig.StandardMessageAID = iVariable;

    iVariable = ini.GetLongValue("DSMPParamConfig", "PassMessageAID", 0);
    p_ProtocolStackParamConfig->DSMPParamConfig.PassMessageAID = iVariable;

    strVariablePtr = ini.GetValue("DSMPParamConfig", "RecvLegalAIDList", NULL);
    index = str2Intlist(strVariablePtr, p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDList);
    p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDNum = index;
    BubbleSort(p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDList,
               p_ProtocolStackParamConfig->DSMPParamConfig.RecvLegalAIDNum);

    //2020.07.15 WM add:防止配置文件里没有该节点,默认返回1
    iVariable = ini.GetLongValue("DSMPParamConfig", "AIDListCheckMark", 1);
    p_ProtocolStackParamConfig->DSMPParamConfig.AIDListCheckMark = iVariable;

    //消息层版本设置
    iVariable = ini.GetLongValue("MsgFrameConfig", "MsgFrameVersion", 4);
    p_ProtocolStackParamConfig->msgFrameConfig.MsgFrameVersion = iVariable;

    //日志模块配置文件路径设置
    strVariablePtr = ini.GetValue("LogConfigFilePath", "LogConfigPath", NULL);
    if (NULL != strVariablePtr)
    {
        strcpy(p_ProtocolStackParamConfig->logConfigPath.logConfigFilePath, strVariablePtr);
    }

    //第三方库使用设置
    iVariable = ini.GetLongValue("ThirdPartyLibConfig", "SqliteConfig", 0);
    p_ProtocolStackParamConfig->thirdPartyLibConfig.SqliteConfig = iVariable;

    iVariable = ini.GetLongValue("ThirdPartyLibConfig", "StateMonitorConfig", 0);
    p_ProtocolStackParamConfig->thirdPartyLibConfig.StateMonitorConfig = iVariable;

    iVariable = ini.GetLongValue("ThirdPartyLibConfig", "ForwardingConfig", 0);
    p_ProtocolStackParamConfig->thirdPartyLibConfig.ForwardingConfig = iVariable;

    iVariable = ini.GetLongValue("ThirdPartyLibConfig", "PthreadStateAdjust", 0);
    p_ProtocolStackParamConfig->thirdPartyLibConfig.PthreadStateAdjust = iVariable;

    iVariable = ini.GetLongValue("ThirdPartyLibConfig", "SendingSerial", 0);
    p_ProtocolStackParamConfig->thirdPartyLibConfig.SendingSerial = iVariable;

    //依据配置修改publicMsg中的AID
    setStaticAIDFromConfig(p_ProtocolStackParamConfig);

    //接入层状态默认为1
    ProtocolStackParamConfig.v2xStatusFlag.v2xStatus = 1;
    return 0;
}

/**************************************************
*名称： 设置、查询参数函数
*描述： 设置、查询参数
*参数：
*       p_ProtocolStackParamConfig		 配置文件结构体变量
*       souceString		                 原json字符串
*       retString		                 返回应答json字符串
*       FileName		                 配置文件
*返回值：1--成功；
*返回值：非1--错误号。
*说明：无
**************************************************/
__attribute__((visibility("default"))) int WJ_SetParamDataInterface(ProtocolStackParamConfig_t *p_ProtocolStackParamConfig, const char *souceString, char *retString, char *FileName)
{
    if (NULL == FileName || NULL == souceString || NULL == retString || NULL == p_ProtocolStackParamConfig)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "param is NULL\n");
        return -1;
    }

    int nRet = 1; //返回1为成功
    string retstring = "";
    char *strPostRequest = NULL;
    char *Source = NULL, *Operation = NULL, *ModuleName = NULL, *ConfigType = NULL;
    //cJSON *jsonReqRoot = cJSON_CreateObject();
    cJSON *jsonReqRoot = cJSON_Parse(souceString);

    //指示本数据的传输对象
    ModuleName = strGetJsonStringItem(jsonReqRoot, "ModuleName");
    if (ModuleName == NULL)
    {
        if (jsonReqRoot != NULL)
        {
            cJSON_Delete(jsonReqRoot);
            jsonReqRoot = NULL;
        }
        LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Parameter is invalid ModuleName is NULL\n");
        return -1;
    }
    else if (ModuleName != NULL && strcmp(ModuleName, "Message") != 0)
    {
        if (jsonReqRoot != NULL)
        {
            cJSON_Delete(jsonReqRoot);
            jsonReqRoot = NULL;
        }
        LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Parameter is invalid ModuleName = %s\n", ModuleName);
        return -1;
    }

    //指示本消息的来源模块
    Source = strGetJsonStringItem(jsonReqRoot, "Source");
    //本次指令的行为，设置，查询，下载
    Operation = strGetJsonStringItem(jsonReqRoot, "Operation");

    ConfigType = strGetJsonStringItem(jsonReqRoot, "ConfigType");
    if (Operation != NULL)
    {
        if (strcmp(Operation, "set") == 0)
        {
            changeSrc = 1;
            nRet = setParamDataTest(p_ProtocolStackParamConfig, souceString, FileName);
            if (nRet > 0)
            {
                //组成功应答json
                cJSON *jsonRetRoot = cJSON_CreateObject();
                if (ModuleName != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ModuleName", ModuleName);
                if (Source != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Source", Source);
                if (Operation != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Operation", Operation);

                if (ConfigType != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ConfigType", ConfigType);

                cJSON_AddStringToObject(jsonRetRoot, "Result", "SUCCESS");

                strPostRequest = cJSON_PrintUnformatted(jsonRetRoot);
                if (strPostRequest != NULL)
                {
                    strcpy(retString, strPostRequest);
                    cJSON_free(strPostRequest);
                }

                cJSON_Delete(jsonRetRoot);
            }
            else
            {
                //组失败应答json
                cJSON *jsonRetRoot = cJSON_CreateObject();
                if (ModuleName != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ModuleName", ModuleName);
                if (Source != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Source", Source);
                if (Operation != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Operation", Operation);
                if (ConfigType != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ConfigType", ConfigType);
                cJSON_AddStringToObject(jsonRetRoot, "Result", "FAIL");

                strPostRequest = cJSON_PrintUnformatted(jsonRetRoot);
                if (strPostRequest != NULL)
                {
                    strcpy(retString, strPostRequest);
                    cJSON_free(strPostRequest);
                }

                cJSON_Delete(jsonRetRoot);
            }
            changeSrc = 2;
        }
        else if (strcmp(Operation, "query") == 0) //查询
        {
            nRet = queryParamDataTest(p_ProtocolStackParamConfig, souceString, retstring, FileName);
            strcpy(retString, retstring.c_str());
        }
        else if (strcmp(Operation, "download") == 0) //下载
        {
        }
        else if (strcmp(Operation, "add") == 0) //添加
        {
            changeSrc = 1;
            nRet = addParamDataTest(p_ProtocolStackParamConfig, souceString, FileName);
            if (nRet > 0)
            {
                //组成功应答json
                cJSON *jsonRetRoot = cJSON_CreateObject();
                if (ModuleName != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ModuleName", ModuleName);
                if (Source != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Source", Source);
                if (Operation != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Operation", Operation);
                if (ConfigType != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ConfigType", ConfigType);
                cJSON_AddStringToObject(jsonRetRoot, "Result", "SUCCESS");

                strPostRequest = cJSON_PrintUnformatted(jsonRetRoot);
                if (strPostRequest != NULL)
                {
                    strcpy(retString, strPostRequest);
                    cJSON_free(strPostRequest);
                }

                cJSON_Delete(jsonRetRoot);
            }
            else
            {
                //组失败应答json
                cJSON *jsonRetRoot = cJSON_CreateObject();
                if (ModuleName != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ModuleName", ModuleName);
                if (Source != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Source", Source);
                if (Operation != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Operation", Operation);
                if (ConfigType != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ConfigType", ConfigType);
                cJSON_AddStringToObject(jsonRetRoot, "Result", "FAIL");

                strPostRequest = cJSON_PrintUnformatted(jsonRetRoot);
                if (strPostRequest != NULL)
                {
                    strcpy(retString, strPostRequest);
                    cJSON_free(strPostRequest);
                }

                cJSON_Delete(jsonRetRoot);
            }
            changeSrc = 2;
        }
        else if (strcmp(Operation, "delete") == 0) //删除
        {
            changeSrc = 1;
            nRet = deleteParamDataTest(p_ProtocolStackParamConfig, souceString, FileName);
            if (nRet > 0)
            {
                //组成功应答json
                cJSON *jsonRetRoot = cJSON_CreateObject();
                if (ModuleName != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ModuleName", ModuleName);
                if (Source != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Source", Source);
                if (Operation != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Operation", Operation);
                if (ConfigType != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ConfigType", ConfigType);
                cJSON_AddStringToObject(jsonRetRoot, "Result", "SUCCESS");

                strPostRequest = cJSON_PrintUnformatted(jsonRetRoot);
                if (strPostRequest != NULL)
                {
                    strcpy(retString, strPostRequest);
                    cJSON_free(strPostRequest);
                }

                cJSON_Delete(jsonRetRoot);
            }
            else
            {
                //组失败应答json
                cJSON *jsonRetRoot = cJSON_CreateObject();
                if (ModuleName != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ModuleName", ModuleName);
                if (Source != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Source", Source);
                if (Operation != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "Operation", Operation);
                if (ConfigType != NULL)
                    cJSON_AddStringToObject(jsonRetRoot, "ConfigType", ConfigType);
                cJSON_AddStringToObject(jsonRetRoot, "Result", "FAIL");

                strPostRequest = cJSON_PrintUnformatted(jsonRetRoot);
                if (strPostRequest != NULL)
                {
                    strcpy(retString, strPostRequest);
                    cJSON_free(strPostRequest);
                }

                cJSON_Delete(jsonRetRoot);
            }
            changeSrc = 2;
        }
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Para_Err", "Parameter is invalid Operation is NULL\n");
        nRet = -1;
    }

    if (jsonReqRoot != NULL)
    {
        cJSON_Delete(jsonReqRoot);
        jsonReqRoot = NULL;
    }

    return nRet;
}

/* 检测.conf文件是否改变，改变后重新加载reload */
void *ConfigFileProcessReloadThreadFun(void *argv)
{
    pthread_detach(pthread_self());

    /* 入参检查 */
    if (NULL == argv)
    {
        /* 使用默认的协议栈配置路径 */
        LogPrint(LOG_LEVEL_ERR, "CONFIGPRASE",
                 "input is null:argv = %p", argv);
    }
    else
    {
        /* 使用传入的路径 */
        strcpy(configFileName, (char *)argv);
    }

    int s32ret = 0;
    int s32fd;
    int s32wd;
    char s8buffer[BUF_LEN];
    struct inotify_event *pstruevent = NULL;
    string str, strFile;

    strFile = configFileName;
    s32ret = strFile.rfind("/", string::npos);
    if (s32ret != 0)
    {
        str = strFile.substr(s32ret + 1, strFile.length() - s32ret);
        memcpy(configName, (char *)str.c_str(), sizeof(configName));

        str = strFile.substr(0, s32ret + 1);
        memcpy(configDir, (char *)str.c_str(), sizeof(configDir));
    }

    printf("%s %s %d %s\n", __FILE__, __FUNCTION__, __LINE__, configDir);
    printf("%s %s %d %s\n", __FILE__, __FUNCTION__, __LINE__, configName);
    printf("%s %s %d %s\n", __FILE__, __FUNCTION__, __LINE__, configFileName);

    sleep(10);
    /* 初始化inotify文件系统监控 */
    s32fd = inotify_init();
    if (0 > s32fd)
    {
        perror("inotify_init is err");
        LogPrint(LOG_LEVEL_ERR, "CONFIGPRASE", "Fail to initialize inotify.");
        return NULL;
    }
    s32wd = inotify_add_watch(s32fd, configDir, IN_MODIFY);
    if (0 > s32fd)
    {
        perror("inotify_add_watch is err");
        LogPrint(LOG_LEVEL_ERR, "CONFIGPRASE", "Fail to watch inotify.");
        s32ret = close(s32fd);
        if (0 > s32ret)
        {
            perror("close file descriptor is err");
            LogPrint(LOG_LEVEL_ERR, "CONFIGPRASE", "close file descriptor is err");
        }
        return NULL;
    }
    while (1)
    {
        s32ret = read(s32fd, s8buffer, BUF_LEN);
        if (0 > s32ret)
        {
            perror("read is err");
            LogPrint(LOG_LEVEL_ERR, "CONFIGPRASE", "read is err");
        }
        pstruevent = (struct inotify_event *)s8buffer;
        if (pstruevent->len)
        {
            if (pstruevent->mask & IN_MODIFY)
            {
                if ((strcmp((const char *)pstruevent->name, configName) == 0) &&
                    (changeSrc != 1))
                {
                    s32ret = WJ_InitParamDataInterface(&ProtocolStackParamConfig, configFileName);
                    if (0 != s32ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, "CONFIGPRASE", "WJ_InitParamDataInterface is err");
                    }
                }
            }
        }
    }

    s32ret = inotify_rm_watch(s32fd, s32wd);
    if (0 > s32ret)
    {
        perror("inotify_rm_watch is err");
        LogPrint(LOG_LEVEL_ERR, "CONFIGPRASE", "inotify_rm_watch is err");
    }
    s32ret = close(s32fd);
    if (0 > s32ret)
    {
        perror("close file descriptor is err");
        LogPrint(LOG_LEVEL_ERR, "CONFIGPRASE", "close file descriptor is err");
    }
    return NULL;
}