#include <stdlib.h>

extern "C"
{
#include "BusinessTool.h"
#include "ConfigModuleRW.h"
#include "wj_log.h"
}
#include "CUseCPP.h"

void getMsgNameFromAID(char *MsgType, int AID)
{
    //查找时可将AID与ID同时兼容,若出现AID与ID冲突,去其一,以ID为主
    if (NULL == MsgType)
    {
        return;
    }
    int AidMatching = 1;
    //ID的匹配
    switch (AID)
    {
    case MSG_MessageFrame_ID_BSM:
    case MSG_MessageFrame_ID_BSM_OrdinaryConven:
    case MSG_MessageFrame_ID_BSM_OrdinaryEvent:
    case MSG_MessageFrame_ID_BSM_SpecialConven:
    case MSG_MessageFrame_ID_BSM_SpecialEvent:
        strcpy(MsgType, "BSM");
        AidMatching = 0;
        break;
    case MSG_MessageFrame_ID_MAPDATA:
        strcpy(MsgType, "MAP");
        AidMatching = 0;
        break;
    case MSG_MessageFrame_ID_SPAT:
        strcpy(MsgType, "SPAT");
        AidMatching = 0;
        break;
    case MSG_MessageFrame_ID_RSI:
    case MSG_MessageFrame_ID_RSI_RoadStatic:
    case MSG_MessageFrame_ID_RSI_RoadHalfStatic:
    case MSG_MessageFrame_ID_RSI_RoadDynamic:
        strcpy(MsgType, "RSI");
        AidMatching = 0;
        break;
    case MSG_MessageFrame_ID_RSM:
        strcpy(MsgType, "RSM");
        AidMatching = 0;
        break;
    default:
        break;
    }

    //AID的匹配
    if (AidMatching)
    {
        if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.DSAMSGAID)
            strcpy(MsgType, "DSA");
        else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryConven ||
                 AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryEvent ||
                 AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialConven ||
                 AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialEvent ||
                 AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMAfterLoading)
            strcpy(MsgType, "BSM");
        else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.MAPMSGAID)
            strcpy(MsgType, "MAP");
        else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.SPATMSGAID)
            strcpy(MsgType, "SPAT");
        else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadStatic ||
                 AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadHalfStatic ||
                 AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadDynamic)
            strcpy(MsgType, "RSI");
        else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSMMSGAID)
            strcpy(MsgType, "RSM");
        else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.TESTBSMMSGAID)
            strcpy(MsgType, "TESTBSM");
        else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.TESTRSIMSGAID ||
                 AID == ProtocolStackParamConfig.messageParamConfig.msgAid.TESTRSIMSGAID2)
            strcpy(MsgType, "TESTRSI");
        else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.PASSMSGAID)
            strcpy(MsgType, "PASS");
        else
            strcpy(MsgType, "PASS");
    }
}

int getAIDFromID(int messageid)
{
    int MessageAID = ProtocolStackParamConfig.DSMPParamConfig.StandardMessageAID;

    switch (messageid)
    {
    case MSG_MessageFrame_ID_MAPDATA:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.MAPMSGAID;
        break;
    }
    case MSG_MessageFrame_ID_BSM:
    case MSG_MessageFrame_ID_BSM_OrdinaryConven:
    {
        //普通车辆+常规型
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryConven;
        break;
    }
    case MSG_MessageFrame_ID_BSM_OrdinaryEvent:
    {
        //普通车辆+事件型
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryEvent;
        break;
    }
    case MSG_MessageFrame_ID_BSM_SpecialConven:
    {
        //特殊车辆+常规型
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialConven;
        break;
    }
    case MSG_MessageFrame_ID_BSM_SpecialEvent:
    {
        //特殊车辆+事件型
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialEvent;
        break;
    }
    case MSG_MessageFrame_ID_RSI:
    case MSG_MessageFrame_ID_RSI_RoadStatic:
    {
        //道路信息-静态类应用
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadStatic;
        break;
    }
    case MSG_MessageFrame_ID_RSI_RoadHalfStatic:
    {
        //道路信息-半静态类应用
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadHalfStatic;
        break;
    }
    case MSG_MessageFrame_ID_RSI_RoadDynamic:
    {
        //道路信息-动态类应用
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadDynamic;
        break;
    }
    case MSG_MessageFrame_ID_SPAT:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.SPATMSGAID;
        break;
    }
    case MSG_MessageFrame_ID_RSM:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSMMSGAID;
        break;
    }
    /*二期场景消息集*/
    case MSG_MessageFrame_ID_TestMsg:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.TESTMSGAID;
        break;
    }
    case MSG_MessageFrame_ID_RTCMcorrections:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RTCMMSGAID;
        break;
    }
    case MSG_MessageFrame_ID_PAMData:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.PAMMSGAID;
        break;
    }
    case MSG_MessageFrame_ID_CLPMM:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.CLPMMMSGAID;
        break;
    }
    case MSG_MessageFrame_ID_PersonalSafetyMessage:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.PSMMSGAID;
        break;
    }
    case MSG_MessageFrame_ID_RoadsideCoordination:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSCMSGAID;
        break;
    }
    case MSG_MessageFrame_ID_SensorSharingMsg:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.SSMMSGAID;
        break;
    }
    case MSG_MessageFrame_ID_VehIntentionAndRequest:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.VIRMSGAID;
        break;
    }
    case MSG_MessageFrame_ID_VehiclePaymentMessage:
    {
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.VPMMSGAID;
        break;
    }
    default:
    {
        LogPrint(LOG_LEVEL_ERR,
                 "Tools",
                 "getAIDFromID is Error! messageid = %d", messageid);
        break;
    }
    }

    return MessageAID;
}

int getMessageidFromAID(int MessageAID, int Messageid)
{
    int messageid = 0;
    //AID的匹配
    if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.MAPMSGAID &&
        Messageid == MSG_MessageFrame_ID_MAPDATA)
        messageid = MSG_MessageFrame_ID_MAPDATA;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryConven &&
             Messageid == MSG_MessageFrame_ID_BSM) //普通车辆+常规型
        messageid = MSG_MessageFrame_ID_BSM_OrdinaryConven;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMAfterLoading &&
             Messageid == MSG_MessageFrame_ID_BSM) //普通车辆+常规型
        messageid = MSG_MessageFrame_ID_BSM_OrdinaryConven;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryEvent &&
             Messageid == MSG_MessageFrame_ID_BSM) //普通车辆+事件型
        messageid = MSG_MessageFrame_ID_BSM_OrdinaryEvent;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialConven &&
             Messageid == MSG_MessageFrame_ID_BSM) //特殊车辆+常规型
        messageid = MSG_MessageFrame_ID_BSM_SpecialConven;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialEvent &&
             Messageid == MSG_MessageFrame_ID_BSM) //特殊车辆+事件型
        messageid = MSG_MessageFrame_ID_BSM_SpecialEvent;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadStatic &&
             Messageid == MSG_MessageFrame_ID_RSI) //道路信息-静态类应用
        messageid = MSG_MessageFrame_ID_RSI_RoadStatic;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadHalfStatic &&
             Messageid == MSG_MessageFrame_ID_RSI) //道路信息-半静态类应用
        messageid = MSG_MessageFrame_ID_RSI_RoadHalfStatic;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadDynamic &&
             Messageid == MSG_MessageFrame_ID_RSI) //道路信息-动态类应用
        messageid = MSG_MessageFrame_ID_RSI_RoadDynamic;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.SPATMSGAID &&
             Messageid == MSG_MessageFrame_ID_SPAT)
        messageid = MSG_MessageFrame_ID_SPAT;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSMMSGAID &&
             Messageid == MSG_MessageFrame_ID_RSM)
        messageid = MSG_MessageFrame_ID_RSM;
    /*二期场景消息集*/
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.TESTMSGAID &&
             Messageid == MSG_MessageFrame_ID_TestMsg)
        messageid = MSG_MessageFrame_ID_TestMsg;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RTCMMSGAID &&
             Messageid == MSG_MessageFrame_ID_RTCMcorrections)
        messageid = MSG_MessageFrame_ID_RTCMcorrections;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.PAMMSGAID &&
             Messageid == MSG_MessageFrame_ID_PAMData)
        messageid = MSG_MessageFrame_ID_PAMData;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.CLPMMMSGAID &&
             Messageid == MSG_MessageFrame_ID_CLPMM)
        messageid = MSG_MessageFrame_ID_CLPMM;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.PSMMSGAID &&
             Messageid == MSG_MessageFrame_ID_PersonalSafetyMessage)
        messageid = MSG_MessageFrame_ID_PersonalSafetyMessage;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSCMSGAID &&
             Messageid == MSG_MessageFrame_ID_RoadsideCoordination)
        messageid = MSG_MessageFrame_ID_RoadsideCoordination;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.SSMMSGAID &&
             Messageid == MSG_MessageFrame_ID_SensorSharingMsg)
        messageid = MSG_MessageFrame_ID_SensorSharingMsg;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.VIRMSGAID &&
             Messageid == MSG_MessageFrame_ID_VehIntentionAndRequest)
        messageid = MSG_MessageFrame_ID_VehIntentionAndRequest;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.VPMMSGAID &&
             Messageid == MSG_MessageFrame_ID_VehiclePaymentMessage)
        messageid = MSG_MessageFrame_ID_VehiclePaymentMessage;
    else
    {
        // LogPrint(LOG_LEVEL_ERR,
        //          "Tools",
        //          "getMessageidFromAID is Error! MessageAID = %d", MessageAID);
        return -1;
    }

    //以下代码，一致性测试使用，测试过程中 测试主程序可能会对 BSMOrdinaryConven 等全局变量有影响，所以此处AID写死
    // int messageid = 0;
    // //AID的匹配
    // if (MessageAID == 3618 &&
    //     Messageid == MSG_MessageFrame_ID_MAPDATA)
    //     messageid = MSG_MessageFrame_ID_MAPDATA;
    // else if (MessageAID == 111 &&
    //          Messageid == MSG_MessageFrame_ID_BSM) //普通车辆+常规型
    //     messageid = MSG_MessageFrame_ID_BSM_OrdinaryConven;
    // else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMAfterLoading &&
    //          Messageid == MSG_MessageFrame_ID_BSM) //普通车辆+常规型
    //     messageid = MSG_MessageFrame_ID_BSM_OrdinaryConven;
    // else if (MessageAID == 112 &&
    //          Messageid == MSG_MessageFrame_ID_BSM) //普通车辆+事件型
    //     messageid = MSG_MessageFrame_ID_BSM_OrdinaryEvent;
    // else if (MessageAID == 113 &&
    //          Messageid == MSG_MessageFrame_ID_BSM) //特殊车辆+常规型
    //     messageid = MSG_MessageFrame_ID_BSM_SpecialConven;
    // else if (MessageAID == 114 &&
    //          Messageid == MSG_MessageFrame_ID_BSM) //特殊车辆+事件型
    //     messageid = MSG_MessageFrame_ID_BSM_SpecialEvent;
    // else if (MessageAID == 3620 &&
    //          Messageid == MSG_MessageFrame_ID_RSI) //道路信息-静态类应用
    //     messageid = MSG_MessageFrame_ID_RSI_RoadStatic;
    // else if (MessageAID == 3621 &&
    //          Messageid == MSG_MessageFrame_ID_RSI) //道路信息-半静态类应用
    //     messageid = MSG_MessageFrame_ID_RSI_RoadHalfStatic;
    // else if (MessageAID == 3622 &&
    //          Messageid == MSG_MessageFrame_ID_RSI) //道路信息-动态类应用
    //     messageid = MSG_MessageFrame_ID_RSI_RoadDynamic;
    // else if (MessageAID == 3619 &&
    //          Messageid == MSG_MessageFrame_ID_SPAT)
    //     messageid = MSG_MessageFrame_ID_SPAT;
    // else if (MessageAID == 3623 &&
    //          Messageid == MSG_MessageFrame_ID_RSM)
    //     messageid = MSG_MessageFrame_ID_RSM;
    // else
    // {
    //     LogPrint(LOG_LEVEL_ERR,
    //              "Tools",
    //              "getMessageidFromAID is Error! MessageAID = %d", MessageAID);

    //     return -1;
    // }

    return messageid;
}

int getMessageidFromAIDBak(int MessageAID)
{
    int messageid = 0;
    //AID的匹配
    if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.MAPMSGAID)
        messageid = MSG_MessageFrame_ID_MAPDATA;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryConven) //普通车辆+常规型
        messageid = MSG_MessageFrame_ID_BSM_OrdinaryConven;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryEvent) //普通车辆+事件型
        messageid = MSG_MessageFrame_ID_BSM_OrdinaryEvent;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialConven) //特殊车辆+常规型
        messageid = MSG_MessageFrame_ID_BSM_SpecialConven;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialEvent) //特殊车辆+事件型
        messageid = MSG_MessageFrame_ID_BSM_SpecialEvent;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadStatic) //道路信息-静态类应用
        messageid = MSG_MessageFrame_ID_RSI_RoadStatic;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadHalfStatic) //道路信息-半静态类应用
        messageid = MSG_MessageFrame_ID_RSI_RoadHalfStatic;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadDynamic) //道路信息-动态类应用
        messageid = MSG_MessageFrame_ID_RSI_RoadDynamic;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.SPATMSGAID)
        messageid = MSG_MessageFrame_ID_SPAT;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSMMSGAID)
        messageid = MSG_MessageFrame_ID_RSM;
    /*二期场景消息集*/
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.TESTMSGAID)
        messageid = MSG_MessageFrame_ID_TestMsg;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RTCMMSGAID)
        messageid = MSG_MessageFrame_ID_RTCMcorrections;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.PAMMSGAID)
        messageid = MSG_MessageFrame_ID_PAMData;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.CLPMMMSGAID)
        messageid = MSG_MessageFrame_ID_CLPMM;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.PSMMSGAID)
        messageid = MSG_MessageFrame_ID_PersonalSafetyMessage;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSCMSGAID)
        messageid = MSG_MessageFrame_ID_RoadsideCoordination;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.SSMMSGAID)
        messageid = MSG_MessageFrame_ID_SensorSharingMsg;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.VIRMSGAID)
        messageid = MSG_MessageFrame_ID_VehIntentionAndRequest;
    else if (MessageAID == ProtocolStackParamConfig.messageParamConfig.msgAid.VPMMSGAID)
        messageid = MSG_MessageFrame_ID_VehiclePaymentMessage;
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 "Tools",
                 "getMessageidFromAID is Error! MessageAID = %d", MessageAID);

        return -1;
    }

    return messageid;
}

int getPriorityFromID(int messageid)
{
    //查找时可将AID与ID同时兼容,若出现AID与ID冲突,去其一,以ID为主
    int Priority = 0;
    int AidMatching = 1;
    //ID的匹配
    switch (messageid)
    {
    case MSG_MessageFrame_ID_MAPDATA:
    {
        Priority = 16;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_BSM:
    case MSG_MessageFrame_ID_BSM_OrdinaryConven:
    {
        //普通车辆+常规型
        Priority = 208;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_BSM_OrdinaryEvent:
    {
        //普通车辆+事件型
        Priority = 112;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_BSM_SpecialConven:
    {
        //特殊车辆+常规型
        Priority = 208;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_BSM_SpecialEvent:
    {
        //特殊车辆+事件型
        Priority = 112;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_RSI:
    case MSG_MessageFrame_ID_RSI_RoadStatic:
    {
        //道路信息-静态类应用
        Priority = 48;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_RSI_RoadHalfStatic:
    {
        //道路信息-半静态类应用
        Priority = 80;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_RSI_RoadDynamic:
    {
        //道路信息-动态类应用
        Priority = 112;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_SPAT:
    {
        Priority = 176;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_RSM:
    {
        Priority = 208;
        AidMatching = 0;
        break;
    }
    /*二期场景消息集*/
    case MSG_MessageFrame_ID_TestMsg:
    {
        Priority = 16;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_RTCMcorrections:
    {
        Priority = 16;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_PAMData:
    {
        Priority = 16;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_CLPMM:
    {
        Priority = 16;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_PersonalSafetyMessage:
    {
        Priority = 16;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_RoadsideCoordination:
    {
        Priority = 16;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_SensorSharingMsg:
    {
        Priority = 208;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_VehIntentionAndRequest:
    {
        Priority = 208;
        AidMatching = 0;
        break;
    }
    case MSG_MessageFrame_ID_VehiclePaymentMessage:
    {
        Priority = 208;
        AidMatching = 0;
        break;
    }
    default:
    {
        Priority = 16;
        break;
    }
    }

    if (AidMatching)
    {
        //AID的匹配
        if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.MAPMSGAID)
            Priority = 16;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryConven) //普通车辆+常规型
            Priority = 208;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryEvent) //普通车辆+事件型
            Priority = 112;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialConven) //特殊车辆+常规型
            Priority = 208;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialEvent) //特殊车辆+事件型
            Priority = 112;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadStatic) //道路信息-静态类应用
            Priority = 48;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadHalfStatic) //道路信息-半静态类应用
            Priority = 80;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadDynamic) //道路信息-动态类应用
            Priority = 112;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.SPATMSGAID)
            Priority = 176;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.RSMMSGAID)
            Priority = 208;
        /*二期场景消息集*/
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.TESTMSGAID)
            Priority = 16;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.RTCMMSGAID)
            Priority = 112;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.PAMMSGAID)
            Priority = 16;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.CLPMMMSGAID)
            Priority = 16;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.PSMMSGAID)
            Priority = 16;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.RSCMSGAID)
            Priority = 112;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.SSMMSGAID)
            Priority = 208;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.VIRMSGAID)
            Priority = 208;
        else if (messageid == ProtocolStackParamConfig.messageParamConfig.msgAid.VPMMSGAID)
            Priority = 208;
    }

    return Priority;
}

void setDestinationLayer2ID(int AID, unsigned char DestinationLayer2ID[3])
{
    //AID的匹配
    if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.MAPMSGAID)
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x06", 3);
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryConven) //普通车辆+常规型
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x01", 3);
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryEvent) //普通车辆+事件型
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x02", 3);
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialConven) //特殊车辆+常规型
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x03", 3);
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialEvent) //特殊车辆+事件型
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x04", 3);
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMAfterLoading) //BSM 后装车载终端
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x05", 3);
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadStatic) //道路信息-静态类应用
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x08", 3);
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadHalfStatic) //道路信息-半静态类应用
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x09", 3);
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadDynamic) //道路信息-动态类应用
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x0A", 3);
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.SPATMSGAID)
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x07", 3);
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSMMSGAID)
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x0B", 3);
    else
        memcpy(&DestinationLayer2ID[0], "\x00\x00\x00", 3);
}

unsigned char setPPPP(int Priority)
{
    unsigned char pppp = 0x00;
    if (Priority >= 224 && Priority <= 255)
    {
        pppp = 0x01;
    }
    else if (Priority >= 192 && Priority <= 223)
    {
        pppp = 0x02;
    }
    else if (Priority >= 160 && Priority <= 191)
    {
        pppp = 0x03;
    }
    else if (Priority >= 128 && Priority <= 159)
    {
        pppp = 0x04;
    }
    else if (Priority >= 96 && Priority <= 127)
    {
        pppp = 0x05;
    }
    else if (Priority >= 64 && Priority <= 95)
    {
        pppp = 0x06;
    }
    else if (Priority >= 32 && Priority <= 63)
    {
        pppp = 0x07;
    }
    else if (Priority >= 0 && Priority <= 31)
    {
        pppp = 0x08;
    }

    return pppp;
}

int setPriority(unsigned char pppp)
{
    int Priority = 0;
    switch (pppp)
    {
    case 0x01:
        Priority = 255;
        break;
    case 0x02:
        Priority = 223;
        break;
    case 0x03:
        Priority = 191;
        break;
    case 0x04:
        Priority = 159;
        break;
    case 0x05:
        Priority = 127;
        break;
    case 0x06:
        Priority = 95;
        break;
    case 0x07:
        Priority = 63;
        break;
    case 0x08:
        Priority = 31;
        break;
    default:
        Priority = 31;
        break;
    }

    return Priority;
}

int setPriorityFromNetAid(int AID)
{
    int Priority = 0;
    //AID的匹配
    if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.MAPMSGAID)
        Priority = 31;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryConven) //普通车辆+常规型
        Priority = 223;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryEvent) //普通车辆+事件型
        Priority = 127;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialConven) //特殊车辆+常规型
        Priority = 223;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialEvent) //特殊车辆+事件型
        Priority = 127;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.BSMAfterLoading) //BSM 后装车载终端
        Priority = 127;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadStatic) //道路信息-静态类应用
        Priority = 63;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadHalfStatic) //道路信息-半静态类应用
        Priority = 95;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadDynamic) //道路信息-动态类应用
        Priority = 127;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.SPATMSGAID)
        Priority = 191;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSMMSGAID)
        Priority = 223;
    /*二期场景消息集*/
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.TESTMSGAID)
        Priority = 31;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RTCMMSGAID)
        Priority = 95;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.PAMMSGAID)
        Priority = 31;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.CLPMMMSGAID)
        Priority = 127;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.PSMMSGAID)
        Priority = 223;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.RSCMSGAID)
        Priority = 127;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.SSMMSGAID)
        Priority = 223;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.VIRMSGAID)
        Priority = 255;
    else if (AID == ProtocolStackParamConfig.messageParamConfig.msgAid.VPMMSGAID)
        Priority = 255;
    else
        Priority = 31;

    return Priority;
}
/**
 * @brief 计算min-max之间的随机数,并转换成16进制
 */
int setSrandSourceLayer2ID(int max, int min, unsigned char returnNum[], int size)
{
    memset(returnNum, 0x00, size);
    int dNum = 0;
    srand((unsigned)time(NULL));
    dNum = rand();

    dNum = (dNum % (max - min)) + min;

    IntToHexMx(dNum, (char *)returnNum, size);

    return dNum;
}

/**
 * @brief 检查AID列表；如匹配失败，则返回错误代码。
 * @param[in] pDsmpHdr   		底层数据解析成的网络层结构体格式
 * @return 0--成功;非0--错误号。
 */
int32_t NetLay_AIDCheck(uint64_t aid)
{
    int index = 0;
    int result = 0;
    int AID = aid;
    if (ProtocolStackParamConfig.DSMPParamConfig.AIDListCheckMark == 0)
    {
        return result;
    }
    //接收消息的合法AID列表检查
    if (ProtocolStackParamConfig.DSMPParamConfig.RecvLegalAIDNum > 0)
    {
        int low = 0;
        int high = ProtocolStackParamConfig.DSMPParamConfig.RecvLegalAIDNum;
        int ret = -1;
        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (ProtocolStackParamConfig.DSMPParamConfig.RecvLegalAIDList[mid] == AID)
            {
                ret = mid;
                //LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "pDsmpHdr->AID = %d, is OK", AID);
                result = 0;
                return result;
            }
            else if (AID < ProtocolStackParamConfig.DSMPParamConfig.RecvLegalAIDList[mid])
            {
                high = mid - 1;
            }
            else if (AID > ProtocolStackParamConfig.DSMPParamConfig.RecvLegalAIDList[mid])
            {
                low = mid + 1;
            }
        }
        if (ret < 0)
        {
            //LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "RecvLegalAIDNum = %d",
            //         ProtocolStackParamConfig.DSMPParamConfig.RecvLegalAIDNum);
            //LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "pDsmpHdr->AID = %d, is NOT find", AID);
            result = -1;
        }
#if 0
		for(index = 0;index < ProtocolStackParamConfig.DSMPParamConfig.RecvLegalAIDNum;index++)
		{
			if(pDsmpHdr->AID == ProtocolStackParamConfig.DSMPParamConfig.RecvLegalAIDList[index])
			{
				LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug","pDsmpHdr->AID = %d, is OK",pDsmpHdr->AID);
				result = 0;
				return result;
			}
		}

		if(index >= ProtocolStackParamConfig.DSMPParamConfig.RecvLegalAIDNum)
		{
			LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err","pDsmpHdr->AID = %d, is NOT find",pDsmpHdr->AID);
			result = -1;
		}
#endif
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "RecvLegalAIDList is NULL");
        result = -1;
    }

    return result;

    //如果接收消息列表查找不到情况下，查找消息层消息对应AID配置列表
    if (result != 0)
    {
        if (ProtocolStackParamConfig.messageParamConfig.m_AIDGroup.m_GroupNum > 0)
        {
            int inum = 0;
            for (index = 0; index < ProtocolStackParamConfig.messageParamConfig.m_AIDGroup.m_GroupNum; index++)
            {
                for (inum = 0; inum < ProtocolStackParamConfig.messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDNum; inum++)
                {
                    if (AID == ProtocolStackParamConfig.messageParamConfig.m_AIDGroup.m_AidGroupConfig[index].m_nMsgAIDList[inum])
                    {
                        LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "pDsmpHdr->AID = %d, is OK", AID);
                        result = 0;
                        return result;
                    }
                }
            }

            if (index >= ProtocolStackParamConfig.messageParamConfig.m_AIDGroup.m_GroupNum)
            {
                //LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "pDsmpHdr->AID = %d, is NOT find", AID);
                result = -1;
            }
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "m_GroupNum is NULL");
            result = -1;
        }
    }
    return result;
}

int32_t SendFrameIDCheck(int id)
{
    int result = 0;
    if (ProtocolStackParamConfig.messageParamConfig.m_SendParamNum > 0)
    {
        int low = 0;
        int high = ProtocolStackParamConfig.messageParamConfig.m_SendParamNum;
        int ret = -1;
        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (ProtocolStackParamConfig.messageParamConfig.m_SendParam[mid].m_nMsgType == id)
            {
                ret = mid;
                //LogPrint(LOG_LEVEL_INFO, "Stack_Tx_Debug", "m_nMsgType = %d, is OK", id);
                result = 1;
                return result;
            }
            else if (id < ProtocolStackParamConfig.messageParamConfig.m_SendParam[mid].m_nMsgType)
            {
                high = mid - 1;
            }
            else if (id > ProtocolStackParamConfig.messageParamConfig.m_SendParam[mid].m_nMsgType)
            {
                low = mid + 1;
            }
        }
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "m_SendParamNum is NULL");
    }

    return result;
}