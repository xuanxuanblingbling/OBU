#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include "common.h"
#include "msg-queue.h"
#include "IWALL_V2X_API.h"
#include "wj_log.h"
#include "cert-update.h"
#include "cert-import.h"
#include "cert-iwall.h"

#define QUEUE_PATH_NAME "/usr/local/config/IwallStrategy.ini"   /*使用iwall的配置文件当做消息队列的路径*/
char filePath[] = "./test.ini";
#define QUEUE_KEY_ID    'a'

static struct IwallSecLayerInfo s_SysIwallInfo = {.m_n32CertUpdateFlag = 1};

int32_t SecureLayerInit(int (*callback)())
{
    int32_t ret = 0;
    int32_t l_n32MsgQueueId = 0;

    ret = IWALL_DeviceInit();
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "iwall secure chip init failed");
        goto EXIT;
    }

    ret = IWALL_Register_PA_Change_Handle(callback);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Register_PA_Change_Handle failed");
        goto EXIT;
    }


    ret = Get_ImportCertStatus(filePath);
    if (1 == ret)
    {
        // ret = ImportCertFilesToSecureChip();
        ret = ImportCertificate();
        if (0 != ret)
        {
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "import certificates to chip failed");
            goto EXIT;
        }
        else
        {
            ret = Apply_PseudonymCert();
            if (0 != ret)
            {
                LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Pseudonym Cert download failed: %d", ret);
                goto EXIT;
            }
            else
            {
                /* code */
                Set_ImportCertStatus(filePath, 0);
            }
        }

    }
    else
    {
        LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "root certs has imported");
    }

    // ret = MsgQueueCreate(QUEUE_PATH_NAME, QUEUE_KEY_ID, &s_SysIwallInfo.m_n32MsgQueueId);
    // if (0 != ret)
    // {
    //     LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "msg queue create failed");
    //     goto EXIT;
    // }

    // ret = pthread_mutex_init(&s_SysIwallInfo.m_tSecLayerLocker, NULL);
    // if (0 != ret)
    // {
    //     LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "mutex init failed");
    //     goto EXIT_1;
    // }
    // ret = CertUpdaterInit(&s_SysIwallInfo);
    // if (0 != ret)
    // {
    //     LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "cert updater init failed");
    //     goto EXIT_1;
    // }

    return 0;

EXIT_1:
    MsgQueueDel(s_SysIwallInfo.m_n32MsgQueueId);
EXIT:
    printf("------------SecureLayerInit return -1----------------\n");
    return -1;
}

int32_t SecureLayerDeinit(void)
{
    pthread_mutex_lock(&s_SysIwallInfo.m_tSecLayerLocker);
    MsgQueueDel(s_SysIwallInfo.m_n32MsgQueueId);
    CertUpdaterDeinit(&s_SysIwallInfo);
    pthread_mutex_unlock(&s_SysIwallInfo.m_tSecLayerLocker);
}

int32_t SecureDataSign(uint64_t p_u64Aid,
                        uint8_t *p_pu8PlainData, int32_t p_n32PlainDataLen,
                        uint8_t *p_pu8bSecuredMessage, int32_t *p_pn32SecuredMessageLen)
{
    int32_t ret = 0;
    struct MsgQueueDataStruct *ptSendData = NULL;

    if ((NULL == p_pu8PlainData) || (0 >= p_n32PlainDataLen) ||
        (NULL == p_pu8bSecuredMessage) || (NULL == p_pn32SecuredMessageLen) || (0 >= *p_pn32SecuredMessageLen))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "wrong para");
        return -1;
    }

    // ret = IWALL_SignSecuredMessage_RSU(p_u64Aid, p_pu8PlainData, p_n32PlainDataLen, p_pu8bSecuredMessage, p_pn32SecuredMessageLen);
    // ret = IWALL_SignSecuredMessageWithCertificateDigest(p_u64Aid, p_pu8PlainData, p_n32PlainDataLen, p_pu8bSecuredMessage, p_pn32SecuredMessageLen);
    ret = IWALL_SignSecuredMessage(p_u64Aid, p_pu8PlainData, p_n32PlainDataLen, p_pu8bSecuredMessage, p_pn32SecuredMessageLen);
       if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "iwall sign data failed");
        return -1;
    }

    pthread_mutex_lock(&s_SysIwallInfo.m_tSecLayerLocker);
    if (CERT_HAVE_UPDATE == s_SysIwallInfo.m_n32CertUpdateFlag)
    {
        ptSendData = (struct MsgQueueDataStruct *)malloc(sizeof(struct MsgQueueDataStruct) + *p_pn32SecuredMessageLen);
        if (NULL != ptSendData)
        {
            ptSendData->m_n32DataSize = *p_pn32SecuredMessageLen;
            memcpy(ptSendData->m_u8Buf, p_pu8bSecuredMessage, *p_pn32SecuredMessageLen);
            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "send to download thread:%p", ptSendData);
            MsgQueueSend(s_SysIwallInfo.m_n32MsgQueueId, &ptSendData, PTR_SIZE);
            s_SysIwallInfo.m_n32CertUpdateFlag = 0;
        }
    }
    pthread_mutex_unlock(&s_SysIwallInfo.m_tSecLayerLocker);

    return 0;
}

int32_t SecureDataVerify(uint8_t *p_pu8SecuredMsg, int32_t p_n32SecuredMsgSize,
                         uint8_t *p_pu8PlainData, int32_t *p_pn32PlainDataSize, uint64_t *p_pu64AID)
{

    if ((NULL == p_pu8SecuredMsg) || (0 >= p_n32SecuredMsgSize) ||
        (NULL == p_pu8PlainData) || (NULL == p_pn32PlainDataSize) || (0 >= *p_pn32PlainDataSize) || (NULL == p_pu64AID))
    {
        printf("wrong para\n");
        return -1;
    }

    // return IWALL_VerifySecuredMessage(p_pu8SecuredMsg, p_n32SecuredMsgSize, p_pu8PlainData, p_pn32PlainDataSize, p_pu64AID);
    return IWALL_VerifySecuredMessageWithCertificateDigest(p_pu8SecuredMsg, p_n32SecuredMsgSize, p_pu8PlainData, p_pn32PlainDataSize, p_pu64AID);
}

