/**
* @file         :wjv2_uper_interface.c
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
#include "wjv2_uper_interface.h"
#include "wjv2_uper_com.h"

/* 函数调度关系表 */
FUNC_WJV2_UPER_SCHE g_pfuncMsgSche[WJV2_MessageFrame_PR_TOTALNUM] = {
    /* BasicSafetyMessage */
    {WJV2_MessageFrame_PR_bsmFrame_NO, WJV2_BasicSafetyMessage_MsgEnc, WJV2_BasicSafetyMessage_MsgDec},
    {WJV2_MessageFrame_PR_bsmFrameOC_NO, WJV2_BasicSafetyMessage_MsgEnc, WJV2_BasicSafetyMessage_MsgDec},
    {WJV2_MessageFrame_PR_bsmFrameOE_NO, WJV2_BasicSafetyMessage_MsgEnc, WJV2_BasicSafetyMessage_MsgDec},
    {WJV2_MessageFrame_PR_bsmFrameSC_NO, WJV2_BasicSafetyMessage_MsgEnc, WJV2_BasicSafetyMessage_MsgDec},
    {WJV2_MessageFrame_PR_bsmFrameSE_NO, WJV2_BasicSafetyMessage_MsgEnc, WJV2_BasicSafetyMessage_MsgDec},
    /* MapData */
    {WJV2_MessageFrame_PR_mapFrame_NO, WJV2_MapData_MsgEnc, WJV2_MapData_MsgDec},
    /* RoadsideSafetyMessage */
    {WJV2_MessageFrame_PR_rsmFrame_NO, WJV2_RoadsideSafetyMessage_MsgEnc, WJV2_RoadsideSafetyMessage_MsgDec},
    /* SPAT */
    {WJV2_MessageFrame_PR_spatFrame_NO, WJV2_SPAT_MsgEnc, WJV2_SPAT_MsgDec},
    /* RoadSideInformation */
    {WJV2_MessageFrame_PR_rsiFrame_NO, WJV2_RoadSideInformation_MsgEnc, WJV2_RoadSideInformation_MsgDec},
    {WJV2_MessageFrame_PR_rsiFrameRC_NO, WJV2_RoadSideInformation_MsgEnc, WJV2_RoadSideInformation_MsgDec},
    {WJV2_MessageFrame_PR_rsiFrameRH_NO, WJV2_RoadSideInformation_MsgEnc, WJV2_RoadSideInformation_MsgDec},
    {WJV2_MessageFrame_PR_rsiFrameRD_NO, WJV2_RoadSideInformation_MsgEnc, WJV2_RoadSideInformation_MsgDec},
    /* MessageFrameExtData */
    {WJV2_MessageFrame_PR_ExtDataFrame_NO, WJV2_MessageFrameExtData_MsgEnc, WJV2_MessageFrameExtData_MsgDec},
};

static int (*pFunGetAidCompleteV2)(void *pstruMsg);
__attribute__((visibility("default"))) void SetGetAIDFromFileCallbackV2(int (*pFunGetAid)(void *pstruMsg))
{
    pFunGetAidCompleteV2 = pFunGetAid;
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
 * @brief     WJV2_CheckMsgCount检查消息号函数
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
void WJV2_CheckMsgCount(MessageFrame_t *pstruMsgFrame, int CertSwitchState)
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

    static int32_t s_n32TestMsgCountBefore = 0;
    static int32_t s_n32TestMsgCountafter = 0;
    static int32_t s_n32RtcmMsgCountBefore = 0;
    static int32_t s_n32RtcmMsgCountafter = 0;
    static int32_t s_n32PamMsgCountBefore = 0;
    static int32_t s_n32PamMsgCountafter = 0;
    static int32_t s_n32ClpmmMsgCountBefore = 0;
    static int32_t s_n32ClpmmMsgCountafter = 0;
    static int32_t s_n32PsmMsgCountBefore = 0;
    static int32_t s_n32PsmMsgCountafter = 0;
    static int32_t s_n32RscMsgCountBefore = 0;
    static int32_t s_n32RscMsgCountafter = 0;
    static int32_t s_n32SsmMsgCountBefore = 0;
    static int32_t s_n32SsmMsgCountafter = 0;
    static int32_t s_n32VirMsgCountBefore = 0;
    static int32_t s_n32VirMsgCountafter = 0;
    static int32_t s_n32VpmMsgCountBefore = 0;
    static int32_t s_n32VpmMsgCountafter = 0;
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

    case MessageFrame_PR_msgFrameExt:
        switch (pstruMsgFrame->choice.msgFrameExt.value.present)
        {
        /*二期场景消息集*/
        case value_PR_NOTHING:
            break;
        case value_PR_TestMsg:
        {
            if (s_n32TestMsgCountBefore == 0 && s_n32TestMsgCountafter == 0)
            {
                s_n32TestMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.TestMsg.msgCnt;
                s_n32TestMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.TestMsg.msgCnt;
            }
            else
            {
                //文件为及时更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.msgFrameExt.value.choice.TestMsg.msgCnt == s_n32TestMsgCountBefore)
                {
                    s_n32TestMsgCountafter += 1;
                    if (s_n32TestMsgCountafter > 127)
                    {
                        s_n32TestMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.msgFrameExt.value.choice.TestMsg.msgCnt = s_n32TestMsgCountafter;
                }
                else
                {
                    //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                    if (pstruMsgFrame->choice.msgFrameExt.value.choice.TestMsg.msgCnt == s_n32TestMsgCountafter)
                    {
                        s_n32TestMsgCountafter += 1;
                        if (s_n32TestMsgCountafter > 127)
                        {
                            s_n32TestMsgCountafter = 0;
                        }
                        pstruMsgFrame->choice.msgFrameExt.value.choice.TestMsg.msgCnt = s_n32TestMsgCountafter;
                    }
                    else
                    {
                        s_n32TestMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.TestMsg.msgCnt;
                        s_n32TestMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.TestMsg.msgCnt;
                    }
                }
            }
            break;
        }
        case value_PR_RTCMcorrections:
        {
            if (s_n32RtcmMsgCountBefore == 0 && s_n32RtcmMsgCountafter == 0)
            {
                s_n32RtcmMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.RTCMcorrections.msgCnt;
                s_n32RtcmMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.RTCMcorrections.msgCnt;
            }
            else
            {
                //文件为及时更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.msgFrameExt.value.choice.RTCMcorrections.msgCnt == s_n32RtcmMsgCountBefore)
                {
                    s_n32RtcmMsgCountafter += 1;
                    if (s_n32RtcmMsgCountafter > 127)
                    {
                        s_n32RtcmMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.msgFrameExt.value.choice.RTCMcorrections.msgCnt = s_n32RtcmMsgCountafter;
                }
                else
                {
                    //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                    if (pstruMsgFrame->choice.msgFrameExt.value.choice.RTCMcorrections.msgCnt == s_n32RtcmMsgCountafter)
                    {
                        s_n32RtcmMsgCountafter += 1;
                        if (s_n32RtcmMsgCountafter > 127)
                        {
                            s_n32RtcmMsgCountafter = 0;
                        }
                        pstruMsgFrame->choice.msgFrameExt.value.choice.RTCMcorrections.msgCnt = s_n32RtcmMsgCountafter;
                    }
                    else
                    {
                        s_n32RtcmMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.RTCMcorrections.msgCnt;
                        s_n32RtcmMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.RTCMcorrections.msgCnt;
                    }
                }
            }
            break;
        }
        case value_PR_PAMData:
        {
            if (s_n32PamMsgCountBefore == 0 && s_n32PamMsgCountafter == 0)
            {
                s_n32PamMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.PAMData.msgCnt;
                s_n32PamMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.PAMData.msgCnt;
            }
            else
            {
                //文件为及时更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.msgFrameExt.value.choice.PAMData.msgCnt == s_n32PamMsgCountBefore)
                {
                    s_n32PamMsgCountafter += 1;
                    if (s_n32PamMsgCountafter > 127)
                    {
                        s_n32PamMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.msgFrameExt.value.choice.PAMData.msgCnt = s_n32PamMsgCountafter;
                }
                else
                {
                    //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                    if (pstruMsgFrame->choice.msgFrameExt.value.choice.PAMData.msgCnt == s_n32PamMsgCountafter)
                    {
                        s_n32PamMsgCountafter += 1;
                        if (s_n32PamMsgCountafter > 127)
                        {
                            s_n32PamMsgCountafter = 0;
                        }
                        pstruMsgFrame->choice.msgFrameExt.value.choice.PAMData.msgCnt = s_n32PamMsgCountafter;
                    }
                    else
                    {
                        s_n32PamMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.PAMData.msgCnt;
                        s_n32PamMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.PAMData.msgCnt;
                    }
                }
            }
            //时间类动态信息调整
            if (NULL != pstruMsgFrame->choice.msgFrameExt.value.choice.PAMData.timeStamp)
                *(pstruMsgFrame->choice.msgFrameExt.value.choice.PAMData.timeStamp) = FL_Timestamp_now(5);
            break;
        }
        case value_PR_CLPMM:
        {
            if (s_n32ClpmmMsgCountBefore == 0 && s_n32ClpmmMsgCountafter == 0)
            {
                s_n32ClpmmMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.CLPMM.msgCnt;
                s_n32ClpmmMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.CLPMM.msgCnt;
            }
            else
            {
                //文件为及时更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.msgFrameExt.value.choice.CLPMM.msgCnt == s_n32ClpmmMsgCountBefore)
                {
                    s_n32ClpmmMsgCountafter += 1;
                    if (s_n32ClpmmMsgCountafter > 127)
                    {
                        s_n32ClpmmMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.msgFrameExt.value.choice.CLPMM.msgCnt = s_n32ClpmmMsgCountafter;
                }
                else
                {
                    //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                    if (pstruMsgFrame->choice.msgFrameExt.value.choice.CLPMM.msgCnt == s_n32ClpmmMsgCountafter)
                    {
                        s_n32ClpmmMsgCountafter += 1;
                        if (s_n32ClpmmMsgCountafter > 127)
                        {
                            s_n32ClpmmMsgCountafter = 0;
                        }
                        pstruMsgFrame->choice.msgFrameExt.value.choice.CLPMM.msgCnt = s_n32ClpmmMsgCountafter;
                    }
                    else
                    {
                        s_n32ClpmmMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.CLPMM.msgCnt;
                        s_n32ClpmmMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.CLPMM.msgCnt;
                    }
                }
            }
            //时间类动态信息调整
            pstruMsgFrame->choice.msgFrameExt.value.choice.CLPMM.secMark = FL_Timestamp_now(4);
            break;
        }
        case value_PR_PersonalSafetyMessage:
        {
            if (s_n32PsmMsgCountBefore == 0 && s_n32PsmMsgCountafter == 0)
            {
                s_n32PsmMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.PersonalSafetyMessage.msgCnt;
                s_n32PsmMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.PersonalSafetyMessage.msgCnt;
            }
            else
            {
                //文件为及时更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.msgFrameExt.value.choice.PersonalSafetyMessage.msgCnt == s_n32PsmMsgCountBefore)
                {
                    s_n32PsmMsgCountafter += 1;
                    if (s_n32PsmMsgCountafter > 127)
                    {
                        s_n32PsmMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.msgFrameExt.value.choice.PersonalSafetyMessage.msgCnt = s_n32PsmMsgCountafter;
                }
                else
                {
                    //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                    if (pstruMsgFrame->choice.msgFrameExt.value.choice.PersonalSafetyMessage.msgCnt == s_n32PsmMsgCountafter)
                    {
                        s_n32PsmMsgCountafter += 1;
                        if (s_n32PsmMsgCountafter > 127)
                        {
                            s_n32PsmMsgCountafter = 0;
                        }
                        pstruMsgFrame->choice.msgFrameExt.value.choice.PersonalSafetyMessage.msgCnt = s_n32PsmMsgCountafter;
                    }
                    else
                    {
                        s_n32PsmMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.PersonalSafetyMessage.msgCnt;
                        s_n32PsmMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.PersonalSafetyMessage.msgCnt;
                    }
                }
            }
            //时间类动态信息调整
            pstruMsgFrame->choice.msgFrameExt.value.choice.PersonalSafetyMessage.secMark = FL_Timestamp_now(4);
            break;
        }
        case value_PR_RoadsideCoordination:
        {
            if (s_n32RscMsgCountBefore == 0 && s_n32RscMsgCountafter == 0)
            {
                s_n32RscMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.RoadsideCoordination.msgCnt;
                s_n32RscMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.RoadsideCoordination.msgCnt;
            }
            else
            {
                //文件为及时更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.msgFrameExt.value.choice.RoadsideCoordination.msgCnt == s_n32RscMsgCountBefore)
                {
                    s_n32RscMsgCountafter += 1;
                    if (s_n32RscMsgCountafter > 127)
                    {
                        s_n32RscMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.msgFrameExt.value.choice.RoadsideCoordination.msgCnt = s_n32RscMsgCountafter;
                }
                else
                {
                    //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                    if (pstruMsgFrame->choice.msgFrameExt.value.choice.RoadsideCoordination.msgCnt == s_n32RscMsgCountafter)
                    {
                        s_n32RscMsgCountafter += 1;
                        if (s_n32RscMsgCountafter > 127)
                        {
                            s_n32RscMsgCountafter = 0;
                        }
                        pstruMsgFrame->choice.msgFrameExt.value.choice.RoadsideCoordination.msgCnt = s_n32RscMsgCountafter;
                    }
                    else
                    {
                        s_n32RscMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.RoadsideCoordination.msgCnt;
                        s_n32RscMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.RoadsideCoordination.msgCnt;
                    }
                }
            }
            //时间类动态信息调整
            pstruMsgFrame->choice.msgFrameExt.value.choice.RoadsideCoordination.secMark = FL_Timestamp_now(4);
            break;
        }
        case value_PR_SensorSharingMsg:
        {
            if (s_n32SsmMsgCountBefore == 0 && s_n32SsmMsgCountafter == 0)
            {
                s_n32SsmMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.SensorSharingMsg.msgCnt;
                s_n32SsmMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.SensorSharingMsg.msgCnt;
            }
            else
            {
                //文件为及时更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.msgFrameExt.value.choice.SensorSharingMsg.msgCnt == s_n32SsmMsgCountBefore)
                {
                    s_n32SsmMsgCountafter += 1;
                    if (s_n32SsmMsgCountafter > 127)
                    {
                        s_n32SsmMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.msgFrameExt.value.choice.SensorSharingMsg.msgCnt = s_n32SsmMsgCountafter;
                }
                else
                {
                    //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                    if (pstruMsgFrame->choice.msgFrameExt.value.choice.SensorSharingMsg.msgCnt == s_n32SsmMsgCountafter)
                    {
                        s_n32SsmMsgCountafter += 1;
                        if (s_n32SsmMsgCountafter > 127)
                        {
                            s_n32SsmMsgCountafter = 0;
                        }
                        pstruMsgFrame->choice.msgFrameExt.value.choice.SensorSharingMsg.msgCnt = s_n32SsmMsgCountafter;
                    }
                    else
                    {
                        s_n32SsmMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.SensorSharingMsg.msgCnt;
                        s_n32SsmMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.SensorSharingMsg.msgCnt;
                    }
                }
            }
            //时间类动态信息调整
            pstruMsgFrame->choice.msgFrameExt.value.choice.SensorSharingMsg.secMark = FL_Timestamp_now(4);
            break;
        }
        case value_PR_VehIntentionAndRequest:
        {
            if (s_n32VirMsgCountBefore == 0 && s_n32VirMsgCountafter == 0)
            {
                s_n32VirMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.VehIntentionAndRequest.msgCnt;
                s_n32VirMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.VehIntentionAndRequest.msgCnt;
            }
            else
            {
                //文件为及时更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.msgFrameExt.value.choice.VehIntentionAndRequest.msgCnt == s_n32VirMsgCountBefore)
                {
                    s_n32VirMsgCountafter += 1;
                    if (s_n32VirMsgCountafter > 127)
                    {
                        s_n32VirMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.msgFrameExt.value.choice.VehIntentionAndRequest.msgCnt = s_n32VirMsgCountafter;
                }
                else
                {
                    //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                    if (pstruMsgFrame->choice.msgFrameExt.value.choice.VehIntentionAndRequest.msgCnt == s_n32VirMsgCountafter)
                    {
                        s_n32VirMsgCountafter += 1;
                        if (s_n32VirMsgCountafter > 127)
                        {
                            s_n32VirMsgCountafter = 0;
                        }
                        pstruMsgFrame->choice.msgFrameExt.value.choice.VehIntentionAndRequest.msgCnt = s_n32VirMsgCountafter;
                    }
                    else
                    {
                        s_n32VirMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.VehIntentionAndRequest.msgCnt;
                        s_n32VirMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.VehIntentionAndRequest.msgCnt;
                    }
                }
            }
            //时间类动态信息调整
            pstruMsgFrame->choice.msgFrameExt.value.choice.VehIntentionAndRequest.secMark = FL_Timestamp_now(4);
            break;
        }
        case value_PR_VehiclePaymentMessage:
        {
            if (s_n32VpmMsgCountBefore == 0 && s_n32VpmMsgCountafter == 0)
            {
                s_n32VpmMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.VehiclePaymentMessage.msgCnt;
                s_n32VpmMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.VehiclePaymentMessage.msgCnt;
            }
            else
            {
                //文件为及时更新情况下，msgCnt程序内部自动加1
                if (pstruMsgFrame->choice.msgFrameExt.value.choice.VehiclePaymentMessage.msgCnt == s_n32VpmMsgCountBefore)
                {
                    s_n32VpmMsgCountafter += 1;
                    if (s_n32VpmMsgCountafter > 127)
                    {
                        s_n32VpmMsgCountafter = 0;
                    }
                    pstruMsgFrame->choice.msgFrameExt.value.choice.VehiclePaymentMessage.msgCnt = s_n32VpmMsgCountafter;
                }
                else
                {
                    //文件更新，并且程序也更新情况下，msgCnt程序内部自动加1
                    if (pstruMsgFrame->choice.msgFrameExt.value.choice.VehiclePaymentMessage.msgCnt == s_n32VpmMsgCountafter)
                    {
                        s_n32VpmMsgCountafter += 1;
                        if (s_n32VpmMsgCountafter > 127)
                        {
                            s_n32VpmMsgCountafter = 0;
                        }
                        pstruMsgFrame->choice.msgFrameExt.value.choice.VehiclePaymentMessage.msgCnt = s_n32VpmMsgCountafter;
                    }
                    else
                    {
                        s_n32VpmMsgCountBefore = pstruMsgFrame->choice.msgFrameExt.value.choice.VehiclePaymentMessage.msgCnt;
                        s_n32VpmMsgCountafter = pstruMsgFrame->choice.msgFrameExt.value.choice.VehiclePaymentMessage.msgCnt;
                    }
                }
            }
            break;
        }
        }
        break;
    default:
        LogPrint(LOG_LEVEL_ERR,
                 "MsgLayer",
                 "Msg present is err:pstruMsgFrame->present = %d", pstruMsgFrame->present);
        break;
    }
}
/**
 * @brief     WJV2_UperEncodeMain消息层编码主函数
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
DLL_PUBLIC int32_t WJV2_UperEncOrDecMain(WJV2_UperData *pstruUperData, WJV2_STRU_MessageFrame *pstruWjMsg, WJV2_ENUM_InterFace InterFace)
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

    if (InterFace == MSGV2_MessageFrame_UperDecode)
    {
        /* 变量定义 */
        asn_dec_rval_t struAsnDecRet = {0};
        asn_codec_ctx_t structdecode_ctx = {0};
        MessageFrame_t *pstruAsnMsgFrame = NULL;
        uint32_t u32i = 0;
        int32_t n32Ret = 0;
        /* 调用UPER_decode进行解码 */
        // HexLogPrint(LOG_LEVEL_INFO, STACK_MSG_MODULE, pstruUperData->pu8buff, pstruUperData->u32Len);
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
        if (pstruAsnMsgFrame->present == MessageFrame_PR_msgFrameExt)
        {
            if (pstruAsnMsgFrame->choice.msgFrameExt.value.present == value_PR_RoadsideCoordination)
            {
                xer_fprint(stdout, &asn_DEF_MessageFrame, pstruAsnMsgFrame);
            }
        }
        // asn_fprint(stdout, &asn_DEF_MessageFrame, pstruAsnMsgFrame);
        // xer_fprint(stdout, &asn_DEF_MessageFrame, pstruAsnMsgFrame);
        /* 结构体映射,遍历数组，查询函数 */
        for (u32i = 0; u32i < WJV2_MessageFrame_PR_TOTALNUM; u32i++)
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
        if (u32i >= WJV2_MessageFrame_PR_TOTALNUM)
        {
            LogPrint(LOG_LEVEL_ERR,
                     STACK_MSG_MODULE,
                     "MsgNo is out of range: %d", u32i);
            return false;
        }
        LogPrint(LOG_LEVEL_ERR, STACK_MSG_MODULE, "unknow err");
        return true;
    }
    else if (InterFace == MSGV2_MessageFrame_UperEncode)
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
        for (u32i = 0; u32i < WJV2_MessageFrame_PR_TOTALNUM; u32i++)
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
                                                          (size_t)MAXV2_UPERBUFF_SIZE); /* 码流的最大长度 */
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
        if (u32i >= WJV2_MessageFrame_PR_TOTALNUM)
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
 * @brief     WJV2_UperDecodeMain消息层文件读取编码主函数
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
DLL_PUBLIC int32_t WJV2_UperFromFileEncodeMain(WJV2_UperData *pstruUperData, char *pn8FileName, int *pn32MsgAid)
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
    WJV2_CheckMsgCount(pstruMsgFrame, 0);
    if (NULL != pFunGetAidCompleteV2)
    {
        *pn32MsgAid = pFunGetAidCompleteV2(pstruMsgFrame);
    }
    /* 调用UPER_encode进行编码 */
    struAsnEncRet = uper_encode_to_buffer(&asn_DEF_MessageFrame,
                                          0,
                                          pstruMsgFrame,
                                          pstruUperData->pu8buff,
                                          MAXV2_UPERBUFF_SIZE);
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