#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "common.h"
#include "wj_log.h"
#include "msg-queue.h"
#include "rw-ini.h"
#include "cert-update.h"
#include "cert-import.h"
#include "Chip_iwallF.h"
#include "IWALL_V2X_API.h"
#include "IWALL_V2X_Chip.h"
#include "SecuredMessage.h"
#define QUEUE_KEY_ID 'a'

struct IwallSecLayerInfo s_SysIwallInfo;

static int GetConfigInfo(const char *FileName)
{
    if (NULL == FileName)
    {
        LogPrint(LOG_LEVEL_INFO, "协议栈参数配置", "param is NULL\n");
        SECLAYER_ERR("协议栈参数配置为空");
        return -1;
    }

    char strVariable[256] = {0};

    //参数设置
    memset(strVariable, 0, sizeof(strVariable));
    SecGetPrivateProfileString("SecurityParamConfig", "EncryptChipCertPath", NULL, strVariable, sizeof(strVariable), FileName);
    memcpy(s_SysIwallInfo.m_n8CertsPath, strVariable, strlen(strVariable));

    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "CertPath is %s", s_SysIwallInfo.m_n8CertsPath);
    SECLAYER_INFO("CertPath is %s", s_SysIwallInfo.m_n8CertsPath);

    memset(strVariable, 0, sizeof(strVariable));
    SecGetPrivateProfileString("SecurityParamConfig", "EncryptChipLogFilePath", NULL, strVariable, sizeof(strVariable), FileName);
    memcpy(s_SysIwallInfo.m_n8ChipLogPath, strVariable, strlen(strVariable));

    memset(strVariable, 0, sizeof(strVariable));
    SecGetPrivateProfileString("SecurityParamConfig", "EncryptChipACCertPathName", NULL, strVariable, sizeof(strVariable), FileName);
    memcpy(s_SysIwallInfo.m_n8SignCertJsonInfo, strVariable, strlen(strVariable));

    memset(strVariable, 0, sizeof(strVariable));
    SecGetPrivateProfileString("SecurityParamConfig", "IwallLibPathName", NULL, strVariable, sizeof(strVariable), FileName);
    memcpy(s_SysIwallInfo.m_n8IwallLibName, strVariable, strlen(strVariable));

    return 0;
}

int32_t ImportCertFilesToSecureChip(int8_t *certsPath)
{
    if (NULL == certsPath)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "certs path is NULL");
        SECLAYER_ERR("<<<<<<<< certs path is NULL");
        return -1;
    }

    if (0 != write_cert(certsPath))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "write cert to chip failed");
        SECLAYER_ERR("<<<<<<<< write cert to chip failed");
        return -1;
    }

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "write cert to chip success");
    SECLAYER_INFO("<<<<<<<< write cert to chip success");
    return 0;
}

//芯片厂商检查 --信长城
uint32_t SecChipFactoryCheck()
{
    int nRet = 0;
    int status = 0;
    unsigned char hash[64] = {0x0};
    unsigned char buf[100] = {0x0};
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        nRet = IWALL_DeviceInit();
        if (IS_OK != nRet)
        {
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "iwall secure chip  Four init failed");
            SECLAYER_ERR("<<<<<<<< iwall secure chip v4 init failed");
        }
        else
        {
            SECLAYER_ERR("<<<<<<<< iwall secure  init success");
            break;
        }
        
    }
    for (int i = 0; i < 10; i++)
    {
        if (0 == ITS_digest(buf, sizeof(buf), 1, hash))
        {
            nRet = 0;
            break;
        }
        nRet = -1;
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "IWALL chip check failed, count is %d", i);
        SECLAYER_ERR("<<<<<<<< IWALL chip check  failed, count is %d", i);
    }
    // nRet =  IWALL_CloseDevice();
    // if (IS_OK != nRet)
    // {
    //     LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "IWALL_CloseDevice failed");
    //     SECLAYER_ERR("<<<<<<<< IWALL_CloseDevice failed");
    //     goto EXIT;
    // }
    return nRet;
}

int32_t SecChip_Init(seclayer_status_callback cb, void *cb_para, const char *fileName)
{
    int nRet = 0;
    nRet = GetConfigInfo(fileName);
    nRet = IWALL_DeviceInit();
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "iwall secure chip init failed");
        SECLAYER_ERR("<<<<<<<< iwall secure chip init failed");
        goto EXIT;
    }

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "IWALL_DeviceInit success");
    SECLAYER_INFO("<<<<<<<< IWALL_DeviceInit success");

    nRet = ImportCertFilesToSecureChip(s_SysIwallInfo.m_n8CertsPath);
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "import certificates to chip failed");
        SECLAYER_ERR("<<<<<<<< import certificates to chip failed");
        goto EXIT;
    }
    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "ImportCertFilesToSecureChip success");
    SECLAYER_INFO("<<<<<<<< ImportCertFilesToSecureChip success");

    nRet = MsgQueueCreate(s_SysIwallInfo.m_n8CertsPath, QUEUE_KEY_ID, &s_SysIwallInfo.m_n32MsgQueueId);
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "msg queue create failed");
        SECLAYER_ERR("<<<<<<<< msg queue create failed");
        goto EXIT;
    }
    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "MsgQueueCreate success");
    SECLAYER_INFO("<<<<<<<< MsgQueueCreate success");

    nRet = pthread_mutex_init(&s_SysIwallInfo.m_tSecLayerLocker, NULL);
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "mutex init failed");
        SECLAYER_ERR("<<<<<<<< mutex init failed");
        goto EXIT_1;
    }

    nRet = CertUpdaterInit(&s_SysIwallInfo);
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "cert updater init failed");
        SECLAYER_ERR("<<<<<<<< cert updater init failed");
        goto EXIT_1;
    }
    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "CertUpdaterInit success");
    SECLAYER_INFO("<<<<<<<< CertUpdaterInit success");

    return 0;

EXIT_1:
    MsgQueueDel(s_SysIwallInfo.m_n32MsgQueueId);
EXIT:
    return -1;
}

int32_t SecDataSign_RSU(uint64_t p_u64Aid,
                               uint8_t *pdu, int32_t pdu_size,
                               uint8_t *spdu, int32_t *spdu_size)
{
    int32_t ret = -1;

    if ((NULL == pdu) || (0 >= pdu_size) ||
        (NULL == spdu) || (NULL == spdu_size) || (0 >= *spdu_size))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< Sign Four_RSU Wrong Para");
        SECLAYER_ERR("<<<<<<<< Sign Four_RSU Wrong Para");
        return -1;
    }

    struct MsgQueueDataStruct *ptSendData = NULL;
    SECLAYER_ERR("<<<<<<<< IWALL Sign Four_RSU Data pdu =%s,pdu_size = %d\n",pdu,pdu_size);
    ret = IWALL_SignSecuredMessage_RSU(p_u64Aid, pdu, pdu_size, spdu, spdu_size);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Sign Four_RSU Data Failed, Ret is %d", ret);
        SECLAYER_ERR("<<<<<<<< IWALL Sign Four_RSU Data Failed,Ret is %d", ret);
        ret = ImportCertFilesToSecureChip(s_SysIwallInfo.m_n8CertsPath);
        if (IS_OK != ret)
        {
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< import certificates to chip failed,Ret is %d", ret);
            SECLAYER_ERR("<<<<<<<< import certificates to chip failed,Ret is %d", ret);
        }
        return ret;
    }
    // LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "Sign PDU Result Success, Ret is %d", ret);
    SECLAYER_ERR("<<<<<<<< IWALL Sign Four_RSU Data ok");
    pthread_mutex_lock(&s_SysIwallInfo.m_tSecLayerLocker);
    if (CERT_HAVE_UPDATE == s_SysIwallInfo.m_n32CertUpdateFlag)
    {
        ptSendData = (struct MsgQueueDataStruct *)malloc(sizeof(struct MsgQueueDataStruct) + *spdu_size);
        if (NULL != ptSendData)
        {
            ptSendData->m_n32DataSize = *spdu_size;
            memcpy(ptSendData->m_u8Buf, spdu, *spdu_size);
            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "send to download thread:%p", ptSendData);
            MsgQueueSend(s_SysIwallInfo.m_n32MsgQueueId, &ptSendData, PTR_SIZE);
        SECLAYER_ERR("<<<<<<<< IWALL MsgQueueDataStruct MsgQueueSend ok");
            s_SysIwallInfo.m_n32CertUpdateFlag = 0;
        }
    }
    pthread_mutex_unlock(&s_SysIwallInfo.m_tSecLayerLocker);
    SECLAYER_ERR("<<<<<<<< IWALL MsgQueueDataStruct Four_RSU Data ok");
    return 0;
}

int32_t SecDataVerify(uint8_t *spdu, int32_t spdu_size,
                                 uint8_t *pdu, int32_t *pdu_size,
                                 uint64_t *p_pu64AID)
{
    int32_t ret = -1;
    if ((NULL == spdu) || (0 >= spdu_size) ||
        (NULL == pdu) || (NULL == pdu_size) ||
        (0 >= *pdu_size) || (NULL == p_pu64AID))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Verify Four_RSU Wrong Para");
        SECLAYER_ERR("<<<<<<<< IWALL Verify Four_RSU Wrong Para");
        return -1;
    }
    ret = IWALL_VerifySecuredMessage(spdu, spdu_size, pdu, pdu_size, p_pu64AID);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Verify Four_RSU Data Failed, Ret is %d", ret);
        SECLAYER_ERR("<<<<<<<< IWALL Verify Four_RSU Data Failed, Ret is %d", ret);
        return ret;
    }
    // LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "IWALL Verify SPDU Result , Ret is %d", ret);
    return 0;
}

int32_t SecDataSign_OBU(uint64_t aid, int32_t emergency_event_flag,
                                  double longitude, double latitude,
                                  uint8_t *pdu, int32_t pdu_size, uint8_t *spdu, int32_t *spdu_size)
{
    LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL SecDataVerify_OBU not support");
    SECLAYER_ERR("<<<<<<<< IWALL SecDataVerify_OBU not support");
    return -1;
}

int32_t SecChipDeinit(void)
{
    int32_t nRet = 0;
    pthread_mutex_lock(&s_SysIwallInfo.m_tSecLayerLocker);
    MsgQueueDel(s_SysIwallInfo.m_n32MsgQueueId);
    CertUpdaterDeinit(&s_SysIwallInfo);
    // nRet =  IWALL_CloseDevice();
    // if (IS_OK != nRet)
    // {
    //     LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "IWALL_CloseDevice failed");
    //     SECLAYER_ERR("<<<<<<<< IWALL_CloseDevice failed");
    // }
    pthread_mutex_unlock(&s_SysIwallInfo.m_tSecLayerLocker);

    return 0;
}
