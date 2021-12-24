/***********************************************************************
 * 文 件 名 称 ： NewFourSpanLogIf.cpp
 * 功 能 描 述 ： 新四跨大规模测试日志记录实现接口
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-08-18 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
#include "NewFourSpanLogIf.h"
#include "NewFourSpanLog.hpp"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <mutex>
#include <unordered_map>
#include <algorithm>  /* find and find_if interfaces. */
#include <functional> /* 使用lambda表达式 */

#define MODULE_NAME "TEST_LOG"
#define USE_ZLOG 1U
#include "Debug.h"

#define EN_LOCAL_TEST 0U

#define RECV_PREFIX "Recv-"
#define SEND_PREFIX "Send-"
#define TIME_STR_FMT "-%Y-%m-%d-%H-%M-%S.txt"
#define LOG_FILE_PATH "/opt/TestLog/"

#define ID_FIXED_LEN 8U
// MSG TYPE
enum
{
    BSM_MSG = 1,
    RSM_MSG = 2,
    RSI_MSG = 3,
    SPAT_MSG = 4,
    MAP_MSG = 5
};

#define TYPE_SEND "S"
#define TYPE_RECV "R"

typedef unordered_map<string, NewFourSpanFile *> LogFileSetMapType;
typedef unordered_map<int, string> LogIdFileNameMapType;

/* Global file map obj. */
static LogFileSetMapType g_LogFileMapIdSet;
static LogIdFileNameMapType g_LogIdFileNameMap;
/* Global self Msg param. */
static TMsgSelfBsmSet_t g_tMsgSelfBsm;
/* The Lock of global param copy. */
static std::mutex mtx;

/**************************COMMON LOG INTERFACE********************************/
char *mystrdup(const char *str)
{
    char *newstr = NULL;
    if (LOOK_LIKELY(str))
    {
        size_t len = strlen(str);
        newstr = new char[len + 1];
        if (LOOK_LIKELY(newstr))
        {
            strncpy(newstr, str, len);
            newstr[len] = '\0';
        }
    }
    return newstr;
}

static void FL_GetTimeString(char *p_n8TmStr, size_t p_u32Len, const char *p_pn8fmt)
{
    if (LOOK_LIKELY(p_n8TmStr))
    {
        time_t current = time(NULL);
        strftime(p_n8TmStr, p_u32Len, p_pn8fmt, localtime(&current));
    }
    else
    {
        ERR("Invlid param\n");
    }
}

static string FL_GenerateFileName(const char *p_pn8Prefix, const char *p_n8MsgId, const char *p_n8TmStr)
{
    string l_sFilePath, l_sPrefixStr, l_sTimeStr, l_sMsgIdStr;
    l_sFilePath = LOG_FILE_PATH;
    l_sPrefixStr = p_pn8Prefix;
    l_sTimeStr = p_n8TmStr;
    l_sMsgIdStr = p_n8MsgId;
    return l_sFilePath + l_sPrefixStr + l_sMsgIdStr + l_sTimeStr;
}

static int FL_CreateOrFindNewFourSpanFile(string p_tMsgId, NewFourSpanFile **p_pcFileObj)
{
    if (LOOK_UNLIKELY(p_pcFileObj))
    {
        ERR("Invalid param\n");
        return -1;
    }

    char l_n8IdBuf[8] = {0};
    memcpy(l_n8IdBuf, &p_tMsgId.c_str()[1], 8);
    l_n8IdBuf[8] = '\0';
    int l_n32Id = atoi(&l_n8IdBuf[5]);
    auto l_MapObj = g_LogFileMapIdSet.find(p_tMsgId);
    if (l_MapObj != g_LogFileMapIdSet.end())
    {
        //如果找到已经存储在容器中的文件对象，则进行返回已有的文件句柄，进行文件操作
        *p_pcFileObj = l_MapObj->second;
        auto l_Search = g_LogIdFileNameMap.find(l_n32Id);
        if (l_Search != g_LogIdFileNameMap.end())
        {
            cout << "Get Msg Id: " << l_Search->first << ":file name: " << l_Search->second << endl;
        }
        else
        {
            g_LogIdFileNameMap.emplace(make_pair(l_n32Id, (*p_pcFileObj)->GetFileName()));
        }
    }
    else
    {
        //如果找到不是存储在容器中的文件对象，则进行容器存储，map键值对存储
        cout << "New Id coming !!!" << endl;
        char l_n8TimeStr[128] = "";
        //获取当前时间的时间戳字符串
        FL_GetTimeString(l_n8TimeStr, sizeof(l_n8TimeStr), TIME_STR_FMT);
        const char *l_pPrefix = (!memcmp(TYPE_RECV, &p_tMsgId.c_str()[0], 1U)) ? RECV_PREFIX : SEND_PREFIX;
        string l_sFileNameStr = FL_GenerateFileName(l_pPrefix, l_n8IdBuf, l_n8TimeStr);
        //创建文件句柄， 进行log存储
        *p_pcFileObj = new NewFourSpanFile(l_sFileNameStr);
        if (LOOK_UNLIKELY(*p_pcFileObj))
        {
            ERR("Fail to create file object\n");
            return -1;
        }

        //将目标的对象压入到unordered_map中
        g_LogFileMapIdSet.emplace(make_pair(p_tMsgId, *p_pcFileObj));
        //进行键值对存储
        g_LogIdFileNameMap.emplace(make_pair(l_n32Id, l_sFileNameStr));
    }
    return 0;
}

static unsigned long long local_timer_ms()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

static int FL_LocalWriteRecdMsgLog(int p_MsgId, WJV4_STRU_MessageFrame *p_tV2xMsgRecvd, NewFourSpanFile *p_pFileObj)
{
    TMsgRecvSet_t l_tMsgRecvSet;

    unique_lock<mutex> l_lock(mtx); /* Lock here to confirm copy atomically. */
    memset(&l_tMsgRecvSet, 0U, MSG_RECV_SET_LEN);
    l_tMsgRecvSet.m_MsgOtherID = p_MsgId;
    l_tMsgRecvSet.m_MsgRecvTime = local_timer_ms() % 60000;
    l_tMsgRecvSet.m_MsgSelfBsmSet = g_tMsgSelfBsm; /* Copy the global selfMsg. */
#if 0
    //判断BsmMsg消息类型
    switch (p_tV2xMsgRecvd->enumMessageFrameType)
    {
    //BSM
    case MSGV4_MessageFrame_ID_BSM_en:
    case MSGV4_MessageFrame_ID_BSM_OrdinaryConven_en:
    case MSGV4_MessageFrame_ID_BSM_OrdinaryEvent_en:
    case MSGV4_MessageFrame_ID_BSM_SpecialConven_en:
    case MSGV4_MessageFrame_ID_BSM_SpecialEvent_en:
    {
        l_tMsgRecvSet.m_MsgOtherType = BSM_MSG;
        //l_tMsgRecvSet.m_MsgOtherSeqNum = bsctyp_encode(DE_Elevation, p_tV2xMsgRecvd->uniUperMsg.strubsmFrame.strupos.n32elevation);
        l_tMsgRecvSet.m_MsgOtherSecMark = p_tV2xMsgRecvd->uniUperMsg.strubsmFrame.bsm_secMark % 60000;
        l_tMsgRecvSet.m_MsgOtherLatitude = p_tV2xMsgRecvd->uniUperMsg.strubsmFrame.strupos.n32lat * 10000000;
        l_tMsgRecvSet.m_MsgOtherLongtitude = p_tV2xMsgRecvd->uniUperMsg.strubsmFrame.strupos.n32long * 10000000;
        l_tMsgRecvSet.m_MsgOtherSpeed = p_tV2xMsgRecvd->uniUperMsg.strubsmFrame.bsm_speed * 50 + 1; /* TBD Driving speed. Unit m/s */
        l_tMsgRecvSet.m_MsgOtherHeading = p_tV2xMsgRecvd->uniUperMsg.strubsmFrame.bsm_heading * 80; /* Driving direction. Unit degree. */
        l_tMsgRecvSet.m_MsgEvent = p_tV2xMsgRecvd->uniUperMsg.strubsmFrame.bsm_safetyExt.events.bit.VehicleEventFlags_eventHardBraking;
    }
    break;
    //RSI
    case MSGV4_MessageFrame_ID_RSI_en:
    case MSGV4_MessageFrame_ID_RSI_RoadStatic_en:
    case MSGV4_MessageFrame_ID_RSI_RoadHalfStatic_en:
    case MSGV4_MessageFrame_ID_RSI_RoadDynamic_en:
    {
        l_tMsgRecvSet.m_MsgOtherType = RSI_MSG;
        l_tMsgRecvSet.m_MsgOtherSecMark = p_tV2xMsgRecvd->uniUperMsg.rsi.rsi_moy % 60000;
        l_tMsgRecvSet.m_MsgOtherLatitude = p_tV2xMsgRecvd->uniUperMsg.rsi.rsi_refPos.pos_lat * 10000000;
        l_tMsgRecvSet.m_MsgOtherLongtitude = p_tV2xMsgRecvd->uniUperMsg.rsi.rsi_refPos.pos_lon * 10000000;
        l_tMsgRecvSet.m_MsgOtherSeqNum = bsctyp_encode(DE_Elevation, p_tV2xMsgRecvd->uniUperMsg.rsi.rsi_refPos.pos_ele);
    }
    break;
    //RSM
    case MSGV4_MessageFrame_ID_RSM_en:
    {
        l_tMsgRecvSet.m_MsgOtherType = RSM_MSG;
        l_tMsgRecvSet.m_MsgOtherSecMark = p_tV2xMsgRecvd->uniUperMsg.rsm.participants.array[0].secMark % 60000;
        l_tMsgRecvSet.m_MsgOtherLatitude = p_tV2xMsgRecvd->uniUperMsg.rsm.refPos.pos_lat * 10000000;
        l_tMsgRecvSet.m_MsgOtherLongtitude = p_tV2xMsgRecvd->uniUperMsg.rsm.refPos.pos_lon * 10000000;
        l_tMsgRecvSet.m_MsgOtherSeqNum = bsctyp_encode(DE_Elevation, p_tV2xMsgRecvd->uniUperMsg.rsm.refPos.pos_ele);
    }
    break;
    //MAP
    case MSGV4_MessageFrame_ID_MAPDATA_en:
    {
        l_tMsgRecvSet.m_MsgOtherType = MAP_MSG;
        l_tMsgRecvSet.m_MsgOtherSecMark = p_tV2xMsgRecvd->uniUperMsg.mapdata.timestamp % 60000;
        l_tMsgRecvSet.m_MsgOtherSeqNum = bsctyp_encode(DE_Elevation, p_tV2xMsgRecvd->uniUperMsg.mapdata.nodes.NodeList_data[0].refPos.pos_ele);
        l_tMsgRecvSet.m_MsgOtherLatitude = p_tV2xMsgRecvd->uniUperMsg.mapdata.nodes.NodeList_data[0].refPos.pos_lat * 10000000;
        l_tMsgRecvSet.m_MsgOtherLongtitude = p_tV2xMsgRecvd->uniUperMsg.mapdata.nodes.NodeList_data[0].refPos.pos_lon * 10000000;
    }
    break;
    //SPAT
    case MSGV4_MessageFrame_ID_SPAT_en:
    {
        l_tMsgRecvSet.m_MsgOtherType = SPAT_MSG;
        l_tMsgRecvSet.m_MsgOtherSeqNum = bsctyp_encode(DE_DSecond, p_tV2xMsgRecvd->uniUperMsg.spat.moy);
        l_tMsgRecvSet.m_MsgOtherSecMark = p_tV2xMsgRecvd->uniUperMsg.spat.timestamp % 60000; /* second. Unit: millisecond. */
    }
    break;
    default:
        ERR("Invliad MsgId:%d\n", p_tV2xMsgRecvd->messageid);
        return -1;
    }
#endif
    //文件操作
    p_pFileObj->OpenFile();
    if (p_pFileObj->IsFileExist())
    {
        *p_pFileObj->m_file_stream << l_tMsgRecvSet.m_MsgOtherID << "," << l_tMsgRecvSet.m_MsgOtherType << ","
                                   << l_tMsgRecvSet.m_MsgOtherSeqNum - 4096U << "," << l_tMsgRecvSet.m_MsgOtherSecMark << ","
                                   << l_tMsgRecvSet.m_MsgOtherLongtitude << "," << l_tMsgRecvSet.m_MsgOtherLatitude << ","
                                   << l_tMsgRecvSet.m_MsgOtherSpeed << "," << l_tMsgRecvSet.m_MsgOtherHeading << ","
                                   << l_tMsgRecvSet.m_MsgEvent << "," << l_tMsgRecvSet.m_MsgRecvTime << ","
                                   << l_tMsgRecvSet.m_MsgSelfBsmSet.m_MsgSelfID << ","
                                   << l_tMsgRecvSet.m_MsgSelfBsmSet.m_MsgSelfGPSLongtitude << ","
                                   << l_tMsgRecvSet.m_MsgSelfBsmSet.m_MsgSelfGPSLatitude << ","
                                   << l_tMsgRecvSet.m_MsgSelfBsmSet.m_MsgSelfSpeed << ","
                                   << l_tMsgRecvSet.m_MsgSelfBsmSet.m_MsgSelfHeading << endl;
        p_pFileObj->CloseFile();
    }
    return 0;
}

int FL_SetRecvdSelfBsmMsg(char *p_pBsmNameId, TVehData_t *p_ptVehData)
{
    if (access(LOG_FILE_PATH, F_OK))
    {
        mkdir(LOG_FILE_PATH, 0755);
    }

    if (LOOK_UNLIKELY(p_ptVehData) || LOOK_UNLIKELY(p_pBsmNameId))
    {
        ERR("Invalid param\n");
        return -1;
    }
    unique_lock<mutex> l_lock(mtx);
    memset(&g_tMsgSelfBsm, 0, MSG_SELF_BSM_LEN);
    int l_BsmSelfID = atoi(&p_pBsmNameId[5]);
    memcpy(g_tMsgSelfBsm.m_BsmIDbuf, p_pBsmNameId, 8U);
    g_tMsgSelfBsm.m_BsmIDbuf[8] = '\0';
    g_tMsgSelfBsm.m_MsgSelfID = l_BsmSelfID;
    g_tMsgSelfBsm.m_MsgSelfGPSLatitude = p_ptVehData->m_gpsdata_st.m_int_latitude;
    g_tMsgSelfBsm.m_MsgSelfGPSLongtitude = p_ptVehData->m_gpsdata_st.m_int_longitude;
    g_tMsgSelfBsm.m_MsgSelfSpeed = p_ptVehData->m_gpsdata_st.m_dbl_speed;
    g_tMsgSelfBsm.m_MsgSelfHeading = p_ptVehData->m_gpsdata_st.m_dbl_heading;
    return 0;
}

int FL_WriteRecvdMsgLog(WJV4_STRU_MessageFrame *p_tV2xMsgRecvd)
{
    if (LOOK_UNLIKELY(p_tV2xMsgRecvd))
    {
        ERR("Invalid param\n");
        return -1;
    }

    char l_n8ID[ID_FIXED_LEN] = {0};
    int l_n32Id;
    NewFourSpanFile *l_pFileObj = nullptr;
    string l_MsgId, l_BsmId;
    l_BsmId = g_tMsgSelfBsm.m_BsmIDbuf;
    l_MsgId = TYPE_RECV + l_BsmId;

    //判断BsmMsg消息类型
    switch (p_tV2xMsgRecvd->enumMessageFrameType)
    {
    //BSM
    case MSGV4_MessageFrame_ID_BSM_en:
    case MSGV4_MessageFrame_ID_BSM_OrdinaryConven_en:
    case MSGV4_MessageFrame_ID_BSM_OrdinaryEvent_en:
    case MSGV4_MessageFrame_ID_BSM_SpecialConven_en:
    case MSGV4_MessageFrame_ID_BSM_SpecialEvent_en:
    {
        memcpy(l_n8ID, p_tV2xMsgRecvd->uniUperMsg.strubsmFrame.u8OCTid, ID_FIXED_LEN);
        l_n32Id = atoi(&l_n8ID[5]);
        if (l_n32Id >= 1 && l_n32Id <= 200)
        {
            FL_CreateOrFindNewFourSpanFile(l_MsgId, &l_pFileObj);
            FL_LocalWriteRecdMsgLog(l_n32Id, p_tV2xMsgRecvd, l_pFileObj);
        }
        else
        {
            DBG("BSM ID not match:%d", l_n32Id);
            return -1;
        }
    }
    break;
    //RSI
    case MSGV4_MessageFrame_ID_RSI_en:
    case MSGV4_MessageFrame_ID_RSI_RoadStatic_en:
    case MSGV4_MessageFrame_ID_RSI_RoadHalfStatic_en:
    case MSGV4_MessageFrame_ID_RSI_RoadDynamic_en:
    {
        memcpy(l_n8ID, p_tV2xMsgRecvd->uniUperMsg.strursiFrame.u8OCTid, ID_FIXED_LEN);
        l_n32Id = atoi(&l_n8ID[5]);
        if (l_n32Id >= 301 && l_n32Id <= 302)
        {
            FL_CreateOrFindNewFourSpanFile(l_MsgId, &l_pFileObj);
            FL_LocalWriteRecdMsgLog(l_n32Id, p_tV2xMsgRecvd, l_pFileObj);
        }
        else
        {
            DBG("RSI ID not match:%d", l_n32Id);
            return -1;
        }
    }
    break;
    //RSM
    case MSGV4_MessageFrame_ID_RSM_en:
    {
        memcpy(l_n8ID, p_tV2xMsgRecvd->uniUperMsg.strursmFrame.u8OCTid, ID_FIXED_LEN);
        l_n32Id = atoi(&l_n8ID[5]);
        if (l_n32Id >= 301 && l_n32Id <= 302)
        {
            FL_CreateOrFindNewFourSpanFile(l_MsgId, &l_pFileObj);
            FL_LocalWriteRecdMsgLog(l_n32Id, p_tV2xMsgRecvd, l_pFileObj);
        }
        else
        {
            DBG("RSM not match:%d", l_n32Id);
            return -1;
        }
    }
    break;
    //MAP
    case MSGV4_MessageFrame_ID_MAPDATA_en:
    {
        memcpy(l_n8ID, p_tV2xMsgRecvd->uniUperMsg.strumapFrame.strunodes.struNode[0].stria5name.u8DescriptiveName, ID_FIXED_LEN);
        l_n32Id = atoi(&l_n8ID[5]);
        if (l_n32Id >= 301 && l_n32Id <= 302)
        {
            FL_CreateOrFindNewFourSpanFile(l_MsgId, &l_pFileObj);
            FL_LocalWriteRecdMsgLog(l_n32Id, p_tV2xMsgRecvd, l_pFileObj);
        }
        else
        {
            DBG("MAP ID not match:%d", l_n32Id);
            return -1;
        }
    }
    break;
    //SPAT
    case MSGV4_MessageFrame_ID_SPAT_en:
    {
        memcpy(l_n8ID, p_tV2xMsgRecvd->uniUperMsg.struspatFrame.stria5name.u8DescriptiveName, ID_FIXED_LEN);
        l_n32Id = atoi(&l_n8ID[5]);
        if (l_n32Id >= 301 && l_n32Id <= 302)
        {
            FL_CreateOrFindNewFourSpanFile(l_MsgId, &l_pFileObj);
            FL_LocalWriteRecdMsgLog(l_n32Id, p_tV2xMsgRecvd, l_pFileObj);
        }
        else
        {
            DBG("SPAT ID not match:%d", l_n32Id);
            return -1;
        }
    }
    break;
    default:
        ERR("Invliad MsgId:%d\n", p_tV2xMsgRecvd->enumMessageFrameType);
        return -1;
    }
    return 0;
}

#if EN_LOCAL_TEST
static void test_log(void)
{
    outertyp_t s_speed = 8190;

    /* Decode basic type data and return the inner type data. */
    innertyp_t d_speed = bsctyp_decode(DE_Speed, s_speed);
    printf("==========d_speed:%.6f\n", d_speed);
    outertyp_t e_speed = bsctyp_encode(DE_Speed, d_speed);
    printf("==========e_speed:%ld\n", e_speed);
    /* Decode basic type data and return the inner type data. */
    d_speed = bsctyp_decode(DE_Speed, e_speed);
    printf("==========d_speed:%.6f\n", d_speed);

    printf("=============================================\n");
    outertyp_t a = 12, b = 13, c = 14, d = 15, f = 16, g = 17, h = 18, i = 19;
    outertyp_t o_s = 6130;
    innertyp_t d_s = bsctyp_decode(DE_Speed, o_s);
    outertyp_t e_s = bsctyp_encode(DE_Speed, d_s);
    innertyp_t d_a = bsctyp_decode(DE_Elevation, a);
    outertyp_t e_a = bsctyp_encode(DE_Elevation, d_a);
    innertyp_t d_b = bsctyp_decode(DE_Elevation, b);
    outertyp_t e_b = bsctyp_encode(DE_Elevation, d_b);
    innertyp_t d_c = bsctyp_decode(DE_Elevation, c);
    outertyp_t e_c = bsctyp_encode(DE_Elevation, d_c);
    innertyp_t d_d = bsctyp_decode(DE_Elevation, d);
    outertyp_t e_d = bsctyp_encode(DE_Elevation, d_d);
    printf("==========decode_speed:%.6f\n", d_s);
    printf("==========encode_speed:%ld\n", e_s);
    printf("==========decode_a:%.6f\n", d_a);
    printf("==========encode_a:%ld\n", e_a);
    printf("==========decode_b:%.6f\n", d_b);
    printf("==========encode_b:%ld\n", e_b);
    printf("==========decode_c:%.6f\n", d_c);
    printf("==========encode_c:%ld\n", e_c);
    printf("==========decode_d:%.6f\n", d_d);
    printf("==========encode_d:%ld\n", e_d);
    innertyp_t d_f = bsctyp_decode(DE_DSecond, f);
    outertyp_t e_f = bsctyp_encode(DE_DSecond, d_f);
    innertyp_t d_g = bsctyp_decode(DE_DSecond, g);
    outertyp_t e_g = bsctyp_encode(DE_DSecond, d_g);
    innertyp_t d_h = bsctyp_decode(DE_DSecond, h);
    outertyp_t e_h = bsctyp_encode(DE_DSecond, d_h);
    innertyp_t d_i = bsctyp_decode(DE_DSecond, i);
    outertyp_t e_i = bsctyp_encode(DE_DSecond, d_i);
    printf("==========decode_f:%.6f\n", d_f);
    printf("==========encode_f:%ld\n", e_f);
    printf("==========decode_g:%.6f\n", d_g);
    printf("==========encode_g:%ld\n", e_g);
    printf("==========decode_h:%.6f\n", d_h);
    printf("==========encode_h:%ld\n", e_h);
    printf("==========decode_i:%.6f\n", d_i);
    printf("==========encode_i:%ld\n", e_i);
}
#endif

int FL_WriteSendMsgLog(WJV4_STRU_MessageFrame *p_tV2xMsgRecvd, TVehData_t *p_ptVehData)
{
    if (access(LOG_FILE_PATH, F_OK))
    {
        mkdir(LOG_FILE_PATH, 0755);
    }

    if (LOOK_UNLIKELY(p_tV2xMsgRecvd) || LOOK_UNLIKELY(p_ptVehData))
    {
        ERR("Invalid param\n");
        return -1;
    }
#if EN_LOCAL_TEST
    test_log();
#endif
    char l_n8ID[ID_FIXED_LEN] = {0};
    NewFourSpanFile *l_pFileObj = nullptr;
    string l_MsgId, l_BsmId;
    static int l_BsmMsgCnt = 1;

    //判断BsmMsg消息类型
    switch (p_tV2xMsgRecvd->enumMessageFrameType)
    {
    //BSM
    case MSGV4_MessageFrame_ID_BSM_en:
    case MSGV4_MessageFrame_ID_BSM_OrdinaryConven_en:
    case MSGV4_MessageFrame_ID_BSM_OrdinaryEvent_en:
    case MSGV4_MessageFrame_ID_BSM_SpecialConven_en:
    case MSGV4_MessageFrame_ID_BSM_SpecialEvent_en:
    {
        unique_lock<mutex> l_lock(mtx); /* Lock here to confirm copy atomically. */
        memcpy(l_n8ID, p_tV2xMsgRecvd->uniUperMsg.strubsmFrame.u8OCTid, ID_FIXED_LEN);
        l_n8ID[ID_FIXED_LEN] = '\0';
        int l_n32Id = atoi(&l_n8ID[5]);
        l_BsmId = l_n8ID;
        l_MsgId = TYPE_SEND + l_BsmId;
        FL_CreateOrFindNewFourSpanFile(l_MsgId, &l_pFileObj);
        l_pFileObj->OpenFile();
        if (l_pFileObj->IsFileExist())
        {
            *l_pFileObj->m_file_stream << l_n32Id << "," << l_BsmMsgCnt << ","
                                       << p_tV2xMsgRecvd->uniUperMsg.strubsmFrame.n32secMark << ","
                                       << p_ptVehData->m_gpsdata_st.m_int_longitude << ","
                                       << p_ptVehData->m_gpsdata_st.m_int_latitude << ","
                                       << p_ptVehData->m_gpsdata_st.m_dbl_speed << ","
                                       << p_ptVehData->m_gpsdata_st.m_dbl_speed << ","
                                       << p_tV2xMsgRecvd->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventHardBraking << endl;
            l_pFileObj->CloseFile();
            l_BsmMsgCnt++ > 60000 ? (l_BsmMsgCnt = 1) : (l_BsmMsgCnt = l_BsmMsgCnt);
        }
    }
    break;
    default:
        ERR("Invliad MsgId:%d\n", p_tV2xMsgRecvd->enumMessageFrameType);
        return -1;
    }
    return 0;
}

int FL_DestroyMsgLog(void)
{
    for (auto &its : g_LogFileMapIdSet)
    {
        NewFourSpanFile *l_ptFileObj = its.second;
        l_ptFileObj->CloseFile();
        delete l_ptFileObj;
        l_ptFileObj = nullptr;
    }
    g_LogFileMapIdSet.clear();
    g_LogIdFileNameMap.clear();
    return 0;
}