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
#include "SecuredMessage.h"
#include "Certificate.h"
#include "IWALL_V2X_API.h"
#include "cert-export.h"
#include "cert-iwall.h"

#define SECONDS_BEFORE_Y2004    (1072886400) /*2004.1.1:0:00*/
#define PREUPDATE_TIME_INTRVAL  (3600)       /*提前一小时下载*/

#define AC_KEY_ID               (21)    /*应用证书使用的密钥对ID*/

/*获取秒级时间，基于 2004.1.1:0:00*/
static int32_t GetCurrentTimeBasedOnYear2004Second(uint32_t *p_pu32CurrTime)
{
    struct timeval tv = {0};

    gettimeofday(&tv, NULL);

    if (tv.tv_sec > SECONDS_BEFORE_Y2004)
    {
        *p_pu32CurrTime = tv.tv_sec - SECONDS_BEFORE_Y2004;
    }
    else    /*invalid time*/
    {
        return -1;
    }

    return 0;
}

static int32_t GetCertExpiredTime(struct MsgQueueDataStruct *p_ptSecMsgDataPtr)
{
    SecuredMessage_t *pSecuredMessage = NULL;
    asn_dec_rval_t EncRVal = {0};
    Certificate_t *l_ptCert = NULL;
    Time32_t l_tEndTime = 0;
    Time32_t l_tstartTime = 0;
    uint32_t l_u32CurrTime = 0;
    uint8_t start_time[64] = {0};
    uint8_t end_time[64] = {0};
    uint8_t *temp_time_ptr = NULL;
    uint32_t l_u32ExpiredTimeSecs = 0;

    EncRVal = oer_decode(0, &asn_DEF_SecuredMessage, (void **)&pSecuredMessage, p_ptSecMsgDataPtr->m_u8Buf, p_ptSecMsgDataPtr->m_n32DataSize);
    if (RC_OK != EncRVal.code)
    {
        printf("oer decode cert file failed\n");
        return -1;
    }

    // asn_fprint(stdout, &asn_DEF_SecuredMessage, pSecuredMessage);

    if (0 > GetCurrentTimeBasedOnYear2004Second(&l_u32CurrTime))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "current time is invalid");
        return -1;
    }

    l_ptCert = pSecuredMessage->payload.choice.signedData.signer.choice.certificateList.list.array[0];
    asn_fprint(stdout, &asn_DEF_Certificate, l_ptCert);
    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "version:%d, present:%d", l_ptCert->version, l_ptCert->tbs.validityRestrictions.validityPeriod.present);
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
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "forever certificate");
        return -1;
    }

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "current time:%u, dead time:%u", l_u32CurrTime, l_tEndTime);
    if (l_u32CurrTime >= l_tEndTime)   /*如果当前时间已经超过到期时间，应立即更新*/
    {
        LogPrint(LOG_LEVEL_NOTICE, MODULE_NAME, "should update immediately");
        return 0;
    }
    else if ((l_tEndTime - l_u32CurrTime) <= PREUPDATE_TIME_INTRVAL)
    {
        LogPrint(LOG_LEVEL_NOTICE, MODULE_NAME, "expired in one hour, should update immediately");
        return 0;
    }
    else
    {
        l_u32ExpiredTimeSecs = l_tEndTime - l_u32CurrTime - PREUPDATE_TIME_INTRVAL;
    }

    l_tstartTime += SECONDS_BEFORE_Y2004;
    l_tEndTime += SECONDS_BEFORE_Y2004;
    LogPrint(LOG_LEVEL_NOTICE, MODULE_NAME,"current time %s", asctime(gmtime((time_t *)&l_tstartTime)));
    LogPrint(LOG_LEVEL_NOTICE, MODULE_NAME,"expired time %s", asctime(gmtime((time_t *)&l_tEndTime)));

    temp_time_ptr = asctime(gmtime((time_t *)&l_tstartTime));
    memcpy(start_time, temp_time_ptr, strlen(temp_time_ptr) - 1);

    temp_time_ptr = asctime(gmtime((time_t *)&l_tEndTime));
    memcpy(end_time, temp_time_ptr, strlen(temp_time_ptr) - 1);

    LogPrint(LOG_LEVEL_NOTICE, MODULE_NAME,"start: %s, end:%s", start_time, end_time);

    // write_cert_json_file(start_time, end_time, l_ptCert->tbs.subjectInfo.subjectName.buf);

    return l_u32ExpiredTimeSecs;
}

static int32_t UpdateACCertWithTimer(uint32_t p_u32ExpiredTime)
{
    int32_t l_n32TimerFd = 0;
    int32_t ret = 0;

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "expired time:%us\n", p_u32ExpiredTime);
    l_n32TimerFd = TimerStart(p_u32ExpiredTime * 1000);
    if (-1 == l_n32TimerFd)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "create timer failed");
        return -1;
    }

    if(-1 == TimerExpired(l_n32TimerFd))
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

    while (1)
    {
        if(0 == MsgQueueRecv(ptSecLayInfo->m_n32MsgQueueId, &ptSecMsgDataPtr, &n32DataPtrSize))
        {
            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "recv msg from queue:%p", ptSecMsgDataPtr);
            l_u32ExpiredTime = GetCertExpiredTime(ptSecMsgDataPtr);
            if (0 == l_u32ExpiredTime)
            {
                // ret = IWALL_ApplyApplicationTicketWithKeyID(AC_KEY_ID, (unsigned char *)VIN, strlen(VIN), ACA_URL);
                ret = Apply_PseudonymCert();
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
                if (0 == UpdateACCertWithTimer(l_u32ExpiredTime))
                {
                    LogPrint(LOG_LEVEL_NOTICE, MODULE_NAME, "update PC cert with timer");
                    // ret = IWALL_ApplyApplicationTicketWithKeyID(AC_KEY_ID, (unsigned char *)VIN, strlen(VIN), ACA_URL);
                    ret = Apply_PseudonymCert();
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
            LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "msg queue recv data failed");
        }
    }
}


int32_t CertUpdaterInit(struct IwallSecLayerInfo *p_ptSecLayInfo)
{
    pthread_t l_tpid = 0;
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
