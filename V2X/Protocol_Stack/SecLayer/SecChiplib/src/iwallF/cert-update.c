#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include "common.h"
#include "msg-queue.h"
#include "osal-thread.h"
#include "wj_log.h"
#include "osal-timer.h"
#include "IWALL_V2X_API.h"
#include "cert-export.h"
#include "SecuredMessage.h"
#include "cert-update.h"
#include "Chip_iwallF.h"
#include "SecuredMessage.h"
#define SECONDS_BEFORE_Y2004 (1072886400) /*2004.1.1:0:00*/
#define PREUPDATE_TIME_INTRVAL (3600)     /*提前一小时下载*/

#define AC_KEY_ID (21) /*应用证书使用的密钥对ID*/

static int32_t GetCurrentTimeBasedOnYear2004Second(uint32_t *p_pu32CurrTime)
{
    struct timeval tv = {0};

    gettimeofday(&tv, NULL);

    if (tv.tv_sec > SECONDS_BEFORE_Y2004)
    {
        *p_pu32CurrTime = tv.tv_sec - SECONDS_BEFORE_Y2004;
    }
    else /*invalid time*/
    {
        return -1;
    }

    return 0;
}

int32_t GetCertExpiredTime(unsigned char *p_ptSecMsgDataPtr, signed int SecMsgDataLen,
                                              unsigned char *startTme, unsigned char *endTime)
{
    SecuredMessage_t *pSecuredMessage = NULL;
    asn_dec_rval_t EncRVal = {0};
    Certificate_t *l_ptCert = NULL;
    Time32_t l_tEndTime = 0;
    Time32_t l_tstartTime = 0;
    uint32_t l_u32CurrTime = 0;
    uint8_t start_time[64] = {0};
    uint8_t end_time[64] = {0};
    char *temp_time_ptr = NULL;
    uint32_t l_u32ExpiredTimeSecs = 0;

    if (NULL != p_ptSecMsgDataPtr || NULL != startTme || NULL != endTime)
    {
        printf("p_ptSecMsgDataPtr or startTme or endTime is NULL !!!");
        return -1;
    }

    EncRVal = oer_decode(0, &asn_DEF_SecuredMessage, (void **)&pSecuredMessage, p_ptSecMsgDataPtr, SecMsgDataLen);
    if (RC_OK != EncRVal.code)
    {
        printf("oer decode cert file failed\n");
        return -1;
    }

    //  xer_fprint(stdout, &asn_DEF_SecuredMessage, pSecuredMessage);

    if (0 > GetCurrentTimeBasedOnYear2004Second(&l_u32CurrTime))
    {
        printf("current time is invalid \n");
        return -1;
    }

    l_ptCert = pSecuredMessage->payload.choice.signedData.signer.choice.certificateList.list.array[0];
    printf("version:%ld, present:%d \n", l_ptCert->version, l_ptCert->tbs.validityRestrictions.validityPeriod.present);
    if (ValidityPeriod_PR_timeEnd == l_ptCert->tbs.validityRestrictions.validityPeriod.present)
    {
        l_tEndTime = l_ptCert->tbs.validityRestrictions.validityPeriod.choice.timeEnd;
    }
    else if (ValidityPeriod_PR_timeStartAndEnd == l_ptCert->tbs.validityRestrictions.validityPeriod.present)
    {
        l_tstartTime = l_ptCert->tbs.validityRestrictions.validityPeriod.choice.timeStartAndEnd.startValidity;
        l_tEndTime = l_ptCert->tbs.validityRestrictions.validityPeriod.choice.timeStartAndEnd.endValidity;
    }
    else
    {
        printf("forever certificate \n");
        return -1;
    }

    printf("current time:%u, dead time:%lu \n", l_u32CurrTime, l_tEndTime);
    if (l_u32CurrTime >= l_tEndTime) /*如果当前时间已经超过到期时间，应立即更新*/
    {
        printf("should update immediately \n");
        return 0;
    }
    else if ((l_tEndTime - l_u32CurrTime) <= PREUPDATE_TIME_INTRVAL)
    {
        printf("expired in one hour, should update immediately \n");
        return 0;
    }
    else
    {
        l_u32ExpiredTimeSecs = l_tEndTime - l_u32CurrTime - PREUPDATE_TIME_INTRVAL;
    }

    l_tstartTime += SECONDS_BEFORE_Y2004;
    l_tEndTime += SECONDS_BEFORE_Y2004;
    // printf("current time %s \n", asctime(gmtime((time_t *)&l_tstartTime)));
    // printf("expired time %s \n", asctime(gmtime((time_t *)&l_tEndTime)));

    temp_time_ptr = asctime(gmtime((time_t *)&l_tstartTime));
    memcpy(start_time, temp_time_ptr, strlen((const char *)temp_time_ptr) - 1);

    temp_time_ptr = asctime(gmtime((time_t *)&l_tEndTime));
    memcpy(end_time, temp_time_ptr, strlen((const char *)temp_time_ptr) - 1);

    printf("start: %s, end:%s \n", start_time, end_time);
    memcpy(startTme, start_time, 64);
    memcpy(endTime, end_time, 64);

    // write_cert_json_file(start_time, end_time, l_ptCert->tbs.subjectInfo.subjectName.buf,
    //                      p_ptIwallSecLayerInfoPtr->m_n8SignCertPathName,
    //                      p_ptIwallSecLayerInfoPtr->m_n8SignCertJsonInfo);

    return l_u32ExpiredTimeSecs;
}



static int32_t UpdateACCertWithTimer(uint32_t p_u32ExpiredTime)
{
    int32_t l_n32TimerFd = 0;

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "expired time:%us\n", p_u32ExpiredTime);
    l_n32TimerFd = TimerStart(p_u32ExpiredTime * 1000);
    if (-1 == l_n32TimerFd)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "create timer failed");
        return -1;
    }

    if (-1 == TimerExpired(l_n32TimerFd))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "timer expired failed");
        TimerStop(l_n32TimerFd);
        return -1;
    }

    TimerStop(l_n32TimerFd);

    return 0;
}

static void *CertUpdateThreadFun(void *para)
{
    struct IwallSecLayerInfo *ptSecLayInfo = (struct IwallSecLayerInfo *)para;
    struct MsgQueueDataStruct *ptSecMsgDataPtr = NULL;
    int32_t n32DataPtrSize = PTR_SIZE;
    uint32_t l_u32ExpiredTime = 0;
    int32_t ret = 0;
    uint8_t startTime[64] = {0};
    uint8_t endTime[64] = {0};

    while (1)
    {
        if (0 == MsgQueueRecv(ptSecLayInfo->m_n32MsgQueueId, &ptSecMsgDataPtr, &n32DataPtrSize))
        {
            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "recv msg from queue:%p", ptSecMsgDataPtr);
            // l_u32ExpiredTime = GetCertExpiredTime(ptSecMsgDataPtr, para);
            l_u32ExpiredTime = GetCertExpiredTime(ptSecMsgDataPtr->m_u8Buf, ptSecMsgDataPtr->m_n32DataSize,
                                                  startTime, endTime);

            if (0 == l_u32ExpiredTime)
            {
                ret = IWALL_ApplyApplicationTicketWithKeyID(AC_KEY_ID, (unsigned char *)VIN, strlen(VIN), ACA_URL);
                if (0 != ret)
                {
                    LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "download application certificate file failed");
                }

                LogPrint(LOG_LEVEL_NOTICE, MODULE_NAME, "get secure msg again");
                pthread_mutex_lock(&ptSecLayInfo->m_tSecLayerLocker);
                ptSecLayInfo->m_n32CertUpdateFlag = CERT_HAVE_UPDATE;
                pthread_mutex_unlock(&ptSecLayInfo->m_tSecLayerLocker);
            }
            else if (0 < l_u32ExpiredTime)
            {
                write_cert_json_file((const int8_t *)startTime, (const int8_t *)endTime, NULL,
                                     ptSecLayInfo->m_n8SignCertPathName,
                                     ptSecLayInfo->m_n8SignCertJsonInfo);

                if (0 == UpdateACCertWithTimer(l_u32ExpiredTime))
                {
                    LogPrint(LOG_LEVEL_NOTICE, MODULE_NAME, "update AC cert with timer");
                    ret = IWALL_ApplyApplicationTicketWithKeyID(AC_KEY_ID, (unsigned char *)VIN, strlen(VIN), ACA_URL);
                    if (0 != ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "download application certificate file failed");
                    }

                    LogPrint(LOG_LEVEL_NOTICE, MODULE_NAME, "get secure msg again");
                    pthread_mutex_lock(&ptSecLayInfo->m_tSecLayerLocker);
                    ptSecLayInfo->m_n32CertUpdateFlag = CERT_HAVE_UPDATE;
                    pthread_mutex_unlock(&ptSecLayInfo->m_tSecLayerLocker);
                }
            }
            free(ptSecMsgDataPtr);
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "msg queue recv data failed");
        }
    }

    (void)pthread_exit(NULL);
}

int32_t CertUpdaterInit(struct IwallSecLayerInfo *p_ptSecLayInfo)
{
    int32_t l_n32ret = 0;

    l_n32ret = OsalThreadCreate(&p_ptSecLayInfo->m_tCertUpdateTid, CertUpdateThreadFun, (void *)p_ptSecLayInfo);
    if (0 != l_n32ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "cert update thread create failed\n");
        return -1;
    }

    return 0;
}

void CertUpdaterDeinit(struct IwallSecLayerInfo *p_ptSecLayInfo)
{
    OsalThreadDel(p_ptSecLayInfo->m_tCertUpdateTid);
}
