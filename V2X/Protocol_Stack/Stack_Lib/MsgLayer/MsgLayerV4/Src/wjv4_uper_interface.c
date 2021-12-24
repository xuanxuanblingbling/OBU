/**
* @file         :wjv4_uper_interface.c
* @brief        :该文件为协议栈消息层对外接口函数定义
* @details  	:主要包含协议消息类型对外编解码主函数
* @author   	:huangsai  any question please send mail to huangsai@wanji,net.cn
* @date     	:2020-12-31
* @version		:V1.0
* @copyright 	:Copyright (c) 2020-2025  万集科技股份有限公司
**********************************************************************************
* @attention
* SDK版本：
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/12/31  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
**********************************************************************************
*/
/* 头文件包含 */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "wjv4_uper_interface.h"
#include "wjv4_uper_com.h"
/* 函数调度关系表 */
FUNC_WJV4_UPER_SCHE g_pfuncMsgSche[WJV4_MessageFrame_PR_TOTALNUM] = {
    /* BasicSafetyMessage */
    {WJV4_MessageFrame_PR_bsmFrame_NO, WJV4_BasicSafetyMessage_MsgEnc, WJV4_BasicSafetyMessage_MsgDec},
    {WJV4_MessageFrame_PR_bsmFrameOC_NO, WJV4_BasicSafetyMessage_MsgEnc, WJV4_BasicSafetyMessage_MsgDec},
    {WJV4_MessageFrame_PR_bsmFrameOE_NO, WJV4_BasicSafetyMessage_MsgEnc, WJV4_BasicSafetyMessage_MsgDec},
    {WJV4_MessageFrame_PR_bsmFrameSC_NO, WJV4_BasicSafetyMessage_MsgEnc, WJV4_BasicSafetyMessage_MsgDec},
    {WJV4_MessageFrame_PR_bsmFrameSE_NO, WJV4_BasicSafetyMessage_MsgEnc, WJV4_BasicSafetyMessage_MsgDec},
    /* MapData */
    {WJV4_MessageFrame_PR_mapFrame_NO, WJV4_MapData_MsgEnc, WJV4_MapData_MsgDec},
    /* RoadsideSafetyMessage */
    {WJV4_MessageFrame_PR_rsmFrame_NO, WJV4_RoadsideSafetyMessage_MsgEnc, WJV4_RoadsideSafetyMessage_MsgDec},
    /* SPAT */
    {WJV4_MessageFrame_PR_spatFrame_NO, WJV4_SPAT_MsgEnc, WJV4_SPAT_MsgDec},
    /* RoadSideInformation */
    {WJV4_MessageFrame_PR_rsiFrame_NO, WJV4_RoadSideInformation_MsgEnc, WJV4_RoadSideInformation_MsgDec},
    {WJV4_MessageFrame_PR_rsiFrameRC_NO, WJV4_RoadSideInformation_MsgEnc, WJV4_RoadSideInformation_MsgDec},
    {WJV4_MessageFrame_PR_rsiFrameRH_NO, WJV4_RoadSideInformation_MsgEnc, WJV4_RoadSideInformation_MsgDec},
    {WJV4_MessageFrame_PR_rsiFrameRD_NO, WJV4_RoadSideInformation_MsgEnc, WJV4_RoadSideInformation_MsgDec},
};

static int (*pFunGetAidCompleteV4)(void *pstruMsg);
__attribute__((visibility("default"))) void SetGetAIDFromFileCallbackV4(int (*pFunGetAid)(void *pstruMsg))
{
    pFunGetAidCompleteV4 = pFunGetAid;
}
static uint64_t FL_Timestamp_now(int TimePrec)
{
    struct timeval l_ttimeval;
    gettimeofday(&l_ttimeval, NULL);
    if (1 == TimePrec) //分钟 utc时间
    {
        return ((l_ttimeval.tv_sec) / 60);
    }
    else if (2 == TimePrec) //秒UTC时间
    {
        return (l_ttimeval.tv_sec);
    }
    else if (3 == TimePrec) //毫秒 UTC时间
    {
        return (l_ttimeval.tv_sec * 1000000LL + l_ttimeval.tv_usec) / 1000;
    }
    else if (4 == TimePrec) //当前分钟内经过的毫秒 UTC时间
    {
        struct tm *info = localtime(&l_ttimeval.tv_sec);
        return (info->tm_sec * 1000 + (int)(l_ttimeval.tv_usec / 1000));
    }
    else if (5 == TimePrec) //当前年份以经过的分钟 UTC时间
    {
        time_t timep;
        struct tm *p;
        time(&timep);
        p = gmtime(&timep);
        return ((p->tm_yday * 24 * 60) + (p->tm_hour * 60) + p->tm_min);
    }
    else //微秒 utc时间
    {
        return (l_ttimeval.tv_sec * 1000000LL + l_ttimeval.tv_usec);
    }
}
/**
 * @brief     WJV4_CheckMsgCount检查消息号函数
 * @details   协议栈消息层编解码中 统一 消息的解码函数入口
 * @param   [in]   MessageFrame_t *pstruMsgFrame  接口结构体
 * @param   [in]   int CertSwitchState   证书开关状态
 * @return      本函数返回执行结果，void
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/09/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
void WJV4_CheckMsgCount(MessageFrame_t *pstruMsgFrame, int CertSwitchState)
{
    /* 入参为空检查 */
    if (NULL == pstruMsgFrame)
    {
        LogPrint(LOG_LEVEL_ERR,
                 "MsgLayer",
                 "input is null:pstruMsgframe = %p", pstruMsgFrame);
        return;
    }
    static int32_t s_n32bsmMsgCountBefore = 0;
    static int32_t s_n32bsmMsgCountafter = 0;
    static int32_t s_n32mapMsgCountBefore = 0;
    static int32_t s_n32mapMsgCountafter = 0;
    static int32_t s_n32rsmMsgCountBefore = 0;
    static int32_t s_n32rsmMsgCountafter = 0;
    static int32_t s_n32spatMsgCountBefore = 0;
    static int32_t s_n32spatMsgCountafter = 0;
    static int32_t s_n32rsiMsgCountBefore = 0;
    static int32_t s_n32rsiMsgCountafter = 0;
    switch (pstruMsgFrame->present)
    {
    case MessageFrame_PR_bsmFrame:
        if (s_n32bsmMsgCountBefore == 0 && s_n32bsmMsgCountafter == 0)
        {
            s_n32bsmMsgCountBefore = pstruMsgFrame->choice.bsmFrame.msgCnt;
            s_n32bsmMsgCountafter = pstruMsgFrame->choice.bsmFrame.msgCnt;
        }
        else
        {
            //文件为及时更新情况下，msgCnt程序内部自动加1
            if (pstruMsgFrame->choice.bsmFrame.msgCnt == s_n32bsmMsgCountBefore)
            {
                s_n32bsmMsgCountafter += 1;
                if (s_n32bsmMsgCountafter > 127)
                {
                    s_n32bsmMsgCountafter = 0;
                }
                pstruMsgFrame->choice.bsmFrame.msgCnt = s_n32bsmMsgCountafter;
            }
            else
            {
                //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.bsmFrame.msgCnt == s_n32bsmMsgCountafter)
                {
                    s_n32bsmMsgCountafter += 1;
                    if (s_n32bsmMsgCountafter > 127)
                    {
                        s_n32bsmMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.bsmFrame.msgCnt = s_n32bsmMsgCountafter;
                }
                else
                {
                    s_n32bsmMsgCountBefore = pstruMsgFrame->choice.bsmFrame.msgCnt;
                    s_n32bsmMsgCountafter = pstruMsgFrame->choice.bsmFrame.msgCnt;
                }
            }
        }
        if (CertSwitchState == 1)
        {
            s_n32bsmMsgCountafter = 0;
            pstruMsgFrame->choice.bsmFrame.msgCnt = 0;
        }
        //时间类动态信息调整
        pstruMsgFrame->choice.bsmFrame.secMark = FL_Timestamp_now(4);
        break;
    case MessageFrame_PR_mapFrame:
        if (s_n32mapMsgCountBefore == 0 && s_n32mapMsgCountafter == 0)
        {
            s_n32mapMsgCountBefore = pstruMsgFrame->choice.mapFrame.msgCnt;
            s_n32mapMsgCountafter = pstruMsgFrame->choice.mapFrame.msgCnt;
        }
        else
        {
            //文件为及时更新情况下，msgCnt程序内部自动加1
            if (pstruMsgFrame->choice.mapFrame.msgCnt == s_n32mapMsgCountBefore)
            {
                s_n32mapMsgCountafter += 1;
                if (s_n32mapMsgCountafter > 127)
                {
                    s_n32mapMsgCountafter = 0;
                }
                pstruMsgFrame->choice.mapFrame.msgCnt = s_n32mapMsgCountafter;
            }
            else
            {
                //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.mapFrame.msgCnt == s_n32mapMsgCountafter)
                {
                    s_n32mapMsgCountafter += 1;
                    if (s_n32mapMsgCountafter > 127)
                    {
                        s_n32mapMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.mapFrame.msgCnt = s_n32mapMsgCountafter;
                }
                else
                {
                    s_n32mapMsgCountBefore = pstruMsgFrame->choice.mapFrame.msgCnt;
                    s_n32mapMsgCountafter = pstruMsgFrame->choice.mapFrame.msgCnt;
                }
            }
        }
        if (CertSwitchState == 1)
        {
            s_n32mapMsgCountafter = 0;
            pstruMsgFrame->choice.mapFrame.msgCnt = 0;
        }
        //时间类动态信息调整
        if (NULL != pstruMsgFrame->choice.mapFrame.timeStamp)
            *(pstruMsgFrame->choice.mapFrame.timeStamp) = FL_Timestamp_now(5);
        break;
    case MessageFrame_PR_rsmFrame:
        if (s_n32rsmMsgCountBefore == 0 && s_n32rsmMsgCountafter == 0)
        {
            s_n32rsmMsgCountBefore = pstruMsgFrame->choice.rsmFrame.msgCnt;
            s_n32rsmMsgCountafter = pstruMsgFrame->choice.rsmFrame.msgCnt;
        }
        else
        {
            //文件为及时更新情况下，msgCnt程序内部自动加1
            if (pstruMsgFrame->choice.rsmFrame.msgCnt == s_n32rsmMsgCountBefore)
            {
                s_n32rsmMsgCountafter += 1;
                if (s_n32rsmMsgCountafter > 127)
                {
                    s_n32rsmMsgCountafter = 0;
                }
                pstruMsgFrame->choice.rsmFrame.msgCnt = s_n32rsmMsgCountafter;
            }
            else
            {
                //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.rsmFrame.msgCnt == s_n32rsmMsgCountafter)
                {
                    s_n32rsmMsgCountafter += 1;
                    if (s_n32rsmMsgCountafter > 127)
                    {
                        s_n32rsmMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.rsmFrame.msgCnt = s_n32rsmMsgCountafter;
                }
                else
                {
                    s_n32rsmMsgCountBefore = pstruMsgFrame->choice.rsmFrame.msgCnt;
                    s_n32rsmMsgCountafter = pstruMsgFrame->choice.rsmFrame.msgCnt;
                }
            }
        }
        if (CertSwitchState == 1)
        {
            s_n32rsmMsgCountafter = 0;
            pstruMsgFrame->choice.rsmFrame.msgCnt = 0;
        }
        break;
    case MessageFrame_PR_spatFrame:
        if (s_n32spatMsgCountBefore == 0 && s_n32spatMsgCountafter == 0)
        {
            s_n32spatMsgCountBefore = pstruMsgFrame->choice.spatFrame.msgCnt;
            s_n32spatMsgCountafter = pstruMsgFrame->choice.spatFrame.msgCnt;
        }
        else
        {
            //文件为及时更新情况下，msgCnt程序内部自动加1
            if (pstruMsgFrame->choice.spatFrame.msgCnt == s_n32spatMsgCountBefore)
            {
                s_n32spatMsgCountafter += 1;
                if (s_n32spatMsgCountafter > 127)
                {
                    s_n32spatMsgCountafter = 0;
                }
                pstruMsgFrame->choice.spatFrame.msgCnt = s_n32spatMsgCountafter;
            }
            else
            {
                //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.spatFrame.msgCnt == s_n32spatMsgCountafter)
                {
                    s_n32spatMsgCountafter += 1;
                    if (s_n32spatMsgCountafter > 127)
                    {
                        s_n32spatMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.spatFrame.msgCnt = s_n32spatMsgCountafter;
                }
                else
                {
                    s_n32spatMsgCountBefore = pstruMsgFrame->choice.spatFrame.msgCnt;
                    s_n32spatMsgCountafter = pstruMsgFrame->choice.spatFrame.msgCnt;
                }
            }
        }
        if (CertSwitchState == 1)
        {
            s_n32spatMsgCountafter = 0;
            pstruMsgFrame->choice.spatFrame.msgCnt = 0;
        }
        //时间类动态信息调整
        if (NULL != pstruMsgFrame->choice.spatFrame.timeStamp)
            *(pstruMsgFrame->choice.spatFrame.timeStamp) = FL_Timestamp_now(4);
        break;
    case MessageFrame_PR_rsiFrame:
        if (s_n32rsiMsgCountBefore == 0 && s_n32rsiMsgCountafter == 0)
        {
            s_n32rsiMsgCountBefore = pstruMsgFrame->choice.rsiFrame.msgCnt;
            s_n32rsiMsgCountafter = pstruMsgFrame->choice.rsiFrame.msgCnt;
        }
        else
        {
            //文件为及时更新情况下，msgCnt程序内部自动加1
            if (pstruMsgFrame->choice.rsiFrame.msgCnt == s_n32rsiMsgCountBefore)
            {
                s_n32rsiMsgCountafter += 1;
                if (s_n32rsiMsgCountafter > 127)
                {
                    s_n32rsiMsgCountafter = 0;
                }
                pstruMsgFrame->choice.rsiFrame.msgCnt = s_n32rsiMsgCountafter;
            }
            else
            {
                //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.rsiFrame.msgCnt == s_n32rsiMsgCountafter)
                {
                    s_n32rsiMsgCountafter += 1;
                    if (s_n32rsiMsgCountafter > 127)
                    {
                        s_n32rsiMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.rsiFrame.msgCnt = s_n32rsiMsgCountafter;
                }
                else
                {
                    s_n32rsiMsgCountBefore = pstruMsgFrame->choice.rsiFrame.msgCnt;
                    s_n32rsiMsgCountafter = pstruMsgFrame->choice.rsiFrame.msgCnt;
                }
            }
        }
        if (CertSwitchState == 1)
        {
            s_n32rsiMsgCountafter = 0;
            pstruMsgFrame->choice.rsiFrame.msgCnt = 0;
        }
        //时间类动态信息调整
        if (NULL != pstruMsgFrame->choice.rsiFrame.moy)
            *(pstruMsgFrame->choice.rsiFrame.moy) = FL_Timestamp_now(5);
        break;
    default:
        LogPrint(LOG_LEVEL_ERR,
                 "MsgLayer",
                 "Msg present is err:pstruMsgFrame->present = %d", pstruMsgFrame->present);
        break;
    }
}
/**
 * @brief     WJV4_UperEncodeMain消息层编码主函数
 * @details   协议栈消息层编解码中 统一 消息的编码函数入口
 * @param   [in]   void * pstruUperData  编码结构
 * @param   [in]   void * pvoidWjMsg   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
 */
DLL_PUBLIC int32_t WJV4_UperEncOrDecMain(WJV4_UperData *pstruUperData, WJV4_STRU_MessageFrame *pstruWjMsg, WJV4_ENUM_InterFace InterFace)
{
    /* 入参为空检查 */
    if ((NULL == pstruUperData) || (NULL == pstruWjMsg))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pstruUperData = %p pstruWjMsg = %p",
                 pstruUperData, pstruWjMsg);
        return false;
    }
    if (NULL == pstruUperData->pu8buff)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pstruUperData->pu8buff = %p",
                 pstruUperData->pu8buff);
        return false;
    }
    if (InterFace == MSGV4_MessageFrame_UperDecode)
    {
        /* 变量定义 */
        asn_dec_rval_t struAsnDecRet = {0};
        asn_codec_ctx_t structdecode_ctx = {0};
        MessageFrame_t *pstruAsnMsgFrame = NULL;
        uint32_t u32i = 0;
        int32_t n32Ret = 0;
        /* 调用UPER_decode进行解码 */
        // HexLogPrint(LOG_LEVEL_INFO, STACK_MSG_MODULE, pstruUperData->pu8buff, pstruUperData->u32Len);
        // printf("pstruUperData->u32Len = %d\n", pstruUperData->u32Len);
        struAsnDecRet = uper_decode(&structdecode_ctx,
                                    &asn_DEF_MessageFrame,
                                    (void **)&pstruAsnMsgFrame, /* 输出的asn结构体 */
                                    pstruUperData->pu8buff,     /* 输入的buff内容 */
                                    pstruUperData->u32Len,      /* 输入的长度 */
                                    0,
                                    0);
        if (RC_OK != struAsnDecRet.code)
        {
            if (NULL != pstruAsnMsgFrame)
            {
                ASN_STRUCT_FREE(asn_DEF_MessageFrame, pstruAsnMsgFrame);
            }
            LogPrint(LOG_LEVEL_ERR, STACK_MSG_MODULE, "decode fail reason is %d", (char *)struAsnDecRet.code);
            return false;
        }
        // asn_fprint(stdout, &asn_DEF_MessageFrame, pstruAsnMsgFrame);
        // xer_fprint(stdout, &asn_DEF_MessageFrame, pstruAsnMsgFrame);
        /* 结构体映射,遍历数组，查询函数 */
        for (u32i = 0; u32i < WJV4_MessageFrame_PR_TOTALNUM; u32i++)
        {
            if (pstruAsnMsgFrame->present == g_pfuncMsgSche[u32i].u32MsgNo)
            {
                n32Ret = g_pfuncMsgSche[u32i].Decode_func(&(pstruAsnMsgFrame->choice), &(pstruWjMsg->uniUperMsg));
                if (true != n32Ret)
                {
                    /* 释放空间*/
                    if (NULL != pstruAsnMsgFrame)
                    {
                        ASN_STRUCT_FREE(asn_DEF_MessageFrame, pstruAsnMsgFrame);
                    }
                    LogPrint(LOG_LEVEL_ERR,
                             STACK_MSG_MODULE,
                             "convert is err MsgNo : %d", u32i);
                    return false;
                }
                else
                {
                    pstruWjMsg->enumMessageFrameType = g_pfuncMsgSche[u32i].u32MsgNo;
                    /* 释放空间*/
                    if (NULL != pstruAsnMsgFrame)
                    {
                        ASN_STRUCT_FREE(asn_DEF_MessageFrame, pstruAsnMsgFrame);
                    }
                    /* 编码成功，跳出循环 */
                    // LogPrint(LOG_LEVEL_INFO,
                    //          STACK_MSG_MODULE,
                    //          "convert is success：MsgNo is %d", u32i);
                    return true;
                }
            }
        }
        /* 释放空间*/
        if (NULL != pstruAsnMsgFrame)
        {
            ASN_STRUCT_FREE(asn_DEF_MessageFrame, pstruAsnMsgFrame);
        }
        /* 超过数组长度 */
        if (u32i >= WJV4_MessageFrame_PR_TOTALNUM)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "MsgNo is out of range: %d", u32i);
            return false;
        }
        LogPrint(LOG_LEVEL_ERR, STACK_MSG_MODULE, "unknow err");
        return false;
    }
    else if (InterFace == MSGV4_MessageFrame_UperEncode)
    {
        /* 变量定义 */
        asn_enc_rval_t struAsnEncRet = {0};
        uint32_t u32i = 0;
        int32_t n32Ret = 0;
        MessageFrame_t *pstruAsnMsgFrame = NULL;
        pstruAsnMsgFrame = CALLOC(1, sizeof(MessageFrame_t));
        if (NULL == pstruAsnMsgFrame)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "calloc is err");
            return false;
        }
        /* 结构体映射,遍历数组，查询函数 */
        for (u32i = 0; u32i < WJV4_MessageFrame_PR_TOTALNUM; u32i++)
        {
            if (pstruWjMsg->enumMessageFrameType == g_pfuncMsgSche[u32i].u32MsgNo)
            {

                if (g_pfuncMsgSche[u32i].u32MsgNo > 100)
                    pstruAsnMsgFrame->present = g_pfuncMsgSche[u32i].u32MsgNo / 100;
                else
                    pstruAsnMsgFrame->present = g_pfuncMsgSche[u32i].u32MsgNo;
                n32Ret = g_pfuncMsgSche[u32i].Encode_func(&(pstruAsnMsgFrame->choice), &(pstruWjMsg->uniUperMsg));
                if (true != n32Ret)
                {
                    /* 释放空间*/
                    if (NULL != pstruAsnMsgFrame)
                    {
                        ASN_STRUCT_FREE(asn_DEF_MessageFrame, pstruAsnMsgFrame);
                    }
                    LogPrint(LOG_LEVEL_ERR,
                             STACK_MSG_MODULE,
                             "convert is err MsgNo : %d", u32i);
                    return false;
                }
                else
                {
                    /* 编码成功，跳出循环 */
                    // LogPrint(LOG_LEVEL_INFO,
                    //          STACK_MSG_MODULE,
                    //          "convert is success：MsgNo is %d", u32i);
                    // asn_fprint(stdout, &asn_DEF_MessageFrame, (const void *)pstruAsnMsgFrame);
                    // xer_fprint(stdout, &asn_DEF_MessageFrame, pstruAsnMsgFrame);
                    /* 调用UPER_encode进行编码 */
                    struAsnEncRet = uper_encode_to_buffer(&asn_DEF_MessageFrame,
                                                          0,
                                                          pstruAsnMsgFrame,             /* 编码输入的asn结构体 */
                                                          pstruUperData->pu8buff,       /* 编码的得到的码流 */
                                                          (size_t)MAXV4_UPERBUFF_SIZE); /* 码流的最大长度 */
                    if (NULL != pstruAsnMsgFrame)
                    {
                        ASN_STRUCT_FREE(asn_DEF_MessageFrame, pstruAsnMsgFrame);
                    }
                    if (struAsnEncRet.encoded == -1)
                    {
                        LogPrint(LOG_LEVEL_ERR, STACK_MSG_MODULE, "encode fail reason is %s\n", (char *)struAsnEncRet.failed_type->name);
                        return false;
                    }
                    pstruUperData->u32Len = (struAsnEncRet.encoded + 7) / 8;
                    // HexLogPrint(LOG_LEVEL_INFO, STACK_MSG_MODULE, pstruUperData->pu8buff, pstruUperData->u32Len);
                    // printf("pstruUperData->u32Len = %d\n", pstruUperData->u32Len);
                    return true;
                }
            }
        }
        /* 释放空间*/
        if (NULL != pstruAsnMsgFrame)
        {
            ASN_STRUCT_FREE(asn_DEF_MessageFrame, pstruAsnMsgFrame);
        }
        /* 超过数组长度 */
        if (u32i >= WJV4_MessageFrame_PR_TOTALNUM)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "MsgNo is out of range: %d - %d", u32i, pstruWjMsg->enumMessageFrameType);
            return false;
        }
        LogPrint(LOG_LEVEL_ERR, STACK_MSG_MODULE, "unknow err");
        return false;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "InterFace if error !InterFace = %d",
                 InterFace);
        return false;
    }
    return false;
}

/**
 * @brief     WJV4_UperDecodeMain消息层文件读取编码主函数
 * @details   协议栈消息层编解码中 统一 读取文件消息的解码函数入口
 * @param   [in]   void * pstruUperData  编码结构
 * @param   [in]   void * pn8FileName   WJ结构
 * @return      本函数返回执行结果，
 *                  若成功则返回   true
 *                  否则返回      false
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/08/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
DLL_PUBLIC int32_t WJV4_UperFromFileEncodeMain(WJV4_UperData *pstruUperData, char *pn8FileName, int *pn32MsgAid)
{
    /* 入参为空检查 */
    if ((NULL == pstruUperData) || (NULL == pn8FileName))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pstruUperData = %p pn8FileName = %p",
                 pstruUperData, pn8FileName);
        return false;
    }
    if (NULL == pstruUperData->pu8buff)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "input is null:pstruUperData->pu8buff = %p",
                 pstruUperData->pu8buff);
        return false;
    }
    /* 变量定义 */
    int32_t n32Ret = 0;
    int32_t n32fd = 0;
    uint8_t *pu8XmlBuf = NULL;
    struct stat struStatBuf = {0};
    asn_dec_rval_t struAsnDecRet = {0};
    asn_enc_rval_t struAsnEncRet = {0};
    MessageFrame_t *pstruMsgFrame = NULL;
    struct flock file_lock = {
        .l_type = F_RDLCK, /* 选用读锁 */
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0, /* 0 表示整个文件加锁 */
        .l_pid = -1};
    /*读取文件信息*/
    n32Ret = stat(pn8FileName, &struStatBuf);
    if ((n32Ret < 0) || (struStatBuf.st_size <= 0))
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "stat  %s failed", pn8FileName);
        return false;
    }
    n32fd = open(pn8FileName, O_RDONLY);
    if (n32fd < 0)
    {
        close(n32fd);
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "open filename %s failed", pn8FileName);
        return false;
    }
    /* 判断文件是否可以上锁 */
    // fcntl(n32fd, F_GETLK, &file_lock);
    // if (file_lock.l_type != F_UNLCK)
    // {
    //     /* 判断文件不能上锁的原因 */
    //     if (file_lock.l_type == F_RDLCK) /* 该文件已有读取锁 */
    //     {
    //         close(n32fd);
    //         LogPrint(LOG_LEVEL_ERR,
    //                  STACK_MSG_MODULE,
    //                  "Read lock already set by %d", file_lock.l_pid);
    //         return false;
    //     }
    //     else if (file_lock.l_type == F_WRLCK) /* 该文件已有写入锁 */
    //     {
    //         close(n32fd);
    //         LogPrint(LOG_LEVEL_ERR,
    //                  STACK_MSG_MODULE,
    //                  "Write lock already set by %d", file_lock.l_pid);
    //         return false;
    //     }
    // }
    /* 开辟文件空间 */
    pu8XmlBuf = (unsigned char *)malloc(struStatBuf.st_size);
    if (NULL == pu8XmlBuf)
    {
        close(n32fd);
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "malloc xmlbuf is err");
        return false;
    }
    /* 设置读锁 */
    // file_lock.l_type = F_RDLCK;
    // n32Ret = fcntl(n32fd, F_SETLKW, &file_lock);
    // if (n32Ret < 0)
    // {
    //     LogPrint(LOG_LEVEL_ERR,
    //              STACK_MSG_MODULE,
    //              "Read Lock failed  :type = %d!\n", file_lock.l_type);
    //     if (pu8XmlBuf != NULL)
    //     {
    //         free(pu8XmlBuf);
    //         pu8XmlBuf = NULL;
    //     }
    //     close(n32fd);
    //     return false;
    // }
    /* 读文件 */
    n32Ret = read(n32fd, pu8XmlBuf, struStatBuf.st_size);
    if (n32Ret != struStatBuf.st_size)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "read  failed");
        if (pu8XmlBuf != NULL)
        {
            free(pu8XmlBuf);
            pu8XmlBuf = NULL;
        }
        close(n32fd);
        return false;
    }
    /* 关闭读锁 */
    // file_lock.l_type = F_UNLCK;
    // fcntl(n32fd, F_SETLKW, &file_lock);
    close(n32fd);
    /* 开辟空间 */
    pstruMsgFrame = calloc(1, sizeof(MessageFrame_t));
    if (pstruMsgFrame == NULL)
    {
        if (pu8XmlBuf != NULL)
        {
            free(pu8XmlBuf);
            pu8XmlBuf = NULL;
        }
    }
    /* xer解析文件为asn */
    struAsnDecRet = xer_decode(0,
                               &asn_DEF_MessageFrame,
                               (void **)&pstruMsgFrame,
                               pu8XmlBuf,
                               struStatBuf.st_size);
    if (pu8XmlBuf != NULL)
    {
        free(pu8XmlBuf);
        pu8XmlBuf = NULL;
    }
    if (struAsnDecRet.code != RC_OK)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "xer_decode failed  :st_size = %d  %s failed", struStatBuf.st_size, pn8FileName);
        if (NULL != pstruMsgFrame)
        {
            ASN_STRUCT_FREE(asn_DEF_MessageFrame, pstruMsgFrame);
        }
        return false;
    }
    WJV4_CheckMsgCount(pstruMsgFrame, 0);
    if (NULL != pFunGetAidCompleteV4)
    {
        *pn32MsgAid = pFunGetAidCompleteV4(pstruMsgFrame);
    }
    /* 调用UPER_encode进行编码 */
    struAsnEncRet = uper_encode_to_buffer(&asn_DEF_MessageFrame,
                                          0,
                                          pstruMsgFrame,
                                          pstruUperData->pu8buff,
                                          MAXV4_UPERBUFF_SIZE);
    if (NULL != pstruMsgFrame)
    {
        ASN_STRUCT_FREE(asn_DEF_MessageFrame, pstruMsgFrame);
    }
    if (struAsnEncRet.encoded == -1)
    {
        LogPrint(LOG_LEVEL_ERR,
                 STACK_MSG_MODULE,
                 "encode fail reason is %s\n",
                 (char *)struAsnEncRet.failed_type->name);
        return false;
    }
    pstruUperData->u32Len = (struAsnEncRet.encoded + 7) / 8;
    return true;
}