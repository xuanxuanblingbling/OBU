#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <dirent.h> //目录相关
#include <sys/time.h>
#include "common.h"
#include "wj_log.h"
#include "msg-queue.h"
#include "cert-update.h"
// #include "cert-import.h"
#include "Chip_iwallNewF.h"
#include "IWALL_V2X_API.h"
#include "IWALL_V2X_Chip.h"
#include "rw-ini.h"

#define QUEUE_KEY_ID 'a'
#define IWALL_EA_KEY_ID (0)
#define IWALL_AA_KEY_ID (21)

extern struct IwallSecLayerInfo s_SysIwallInfo;

//信长城证书路径
#define IWALL_CA_NUM 8
#define USE_HOST_NAME 1
#define IWALL_ROOTCA "/iwall/ROOTCA.oer"
#define IWALL_ECA "/iwall/ECA.oer"
#define IWALL_PCA "/iwall/PCA.oer"
#define IWALL_ACA "/iwall/ACA.oer"
#define IWALL_ARA "/iwall/ARA.oer"
#define IWALL_EA "/iwall/EC.oer"
#define IWALL_AA "/iwall/AA.oer"
#define IWALL_PRA "/iwall/PRA.oer"
#define IWALL_ICA "/iwall/ICA.oer"
#define IWALL_CAICT "/iwall/v2x.caict.ac.cn.coer"

#define PCA_CERTS "/pcacerts/"
#define ACA_CERTS "/acacerts/"
#define AA_SK "/iwall/AA.prikey"
#define AA_PK "/iwall/AA.pubkey"
#define EC_SK "/iwall/EC.prikey"
#define EC_PK "/iwall/EC.pubkey"

#define ROOTCA_TYPE 4
#define ECA_TYPE 3
#define ACA_TYPE 2
#define PCA_TYPE 7
#define ICA_TYPE 8
#define PRA_TYPE 9
#define ARA_TYPE 10
#define CAICT_TYPE 11

#define EC_PUBKEY_FILENAME  "./ec.pubkey" /*生成的公钥文件名，用于存储生成的公钥*/
#define PUBKEY_SIZE     (65)    /*公钥内容开始为0x04*/

typedef struct st_File
{
    int nFileType;
    unsigned char szFilePath[260];
} File_t;

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

static int32_t ImportCertFilesToSecureChip_IWALL(int8_t *certsPath);
static int32_t importAllCerts(int8_t *basedir);
static int32_t importAA();
static int32_t importEA();
static int32_t importRootCertificate(int8_t *basedir);
static int32_t ReadCertFileContent(unsigned char *file_path, unsigned char *pbBuf, int *nBufLen);

static int32_t ImportCertFilesToSecureChip_IWALL(int8_t *certsPath)
{
    if (NULL == certsPath)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "certs path is NULL");
        SECLAYER_ERR("<<<<<<<< certs path is NULL");
        return -1;
    }

    if (0 != importAllCerts(certsPath))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "write cert to chip failed");
        SECLAYER_ERR("<<<<<<<< write cert to chip failed");
        return -1;
    }

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "write cert to chip success");
    SECLAYER_INFO("<<<<<<<< write cert to chip success");
    return 0;
}

static int32_t importAllCerts(int8_t *basedir)
{
    int nRet = -1;
    int nCertSecretKeyLen = 32;
    unsigned char pCertSecretKeyName[256] = {0};

    unsigned char private_ea_key[32] = {0};
    unsigned char public_ea_key[64] = {0};
    unsigned char private_aa_key[32] = {0};
    unsigned char public_aa_key[64] = {0};

    nRet = importRootCertificate(basedir);
    if (0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "iwall secure chip vn4 import root certs failed");
        SECLAYER_ERR("<<<<<<<< iwall secure chip vn4 import root certs failed");
    }
    //read EC.oer SK
    strcat(strcat((char *)pCertSecretKeyName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)EC_SK);
    nRet = ReadCertFileContent(pCertSecretKeyName, private_ea_key, &nCertSecretKeyLen);
    if (0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Read CertFileContent Failed %s,  Ret is %d", pCertSecretKeyName, nRet);
        SECLAYER_ERR("<<<<<<<< IWALL Read CertFileContent Failed %s, Ret is %d", pCertSecretKeyName, nRet);
        return -1;
    }
    memset(pCertSecretKeyName, 0, 256);
    //read EC.oer PK
    nCertSecretKeyLen = 64;
    strcat(strcat((char *)pCertSecretKeyName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)EC_PK);
    nRet = ReadCertFileContent(pCertSecretKeyName, public_ea_key, &nCertSecretKeyLen);
    if (0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Read CertFileContent Failed %s,  Ret is %d", pCertSecretKeyName, nRet);
        SECLAYER_ERR("<<<<<<<< IWALL Read CertFileContent Failed %s, Ret is %d", pCertSecretKeyName, nRet);
        return -1;
    }

    nRet = IWALL_WriteKeyPairWithKeyID(IWALL_EA_KEY_ID, 0, private_ea_key, 32, public_ea_key, 64);
    if (nRet != 0)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<<  IWALL_write_keypair_with_keyID Failed,  Ret is %d", nRet);
        SECLAYER_ERR("<<<<<<<< IWALL_write_keypair_with_keyID Failed, Ret is %d", nRet);
        return nRet;
    }
    else
    {
        LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "<<<<<<<<  IWALL_write_keypair_with_keyID Success,  Ret is %d", nRet);
        SECLAYER_INFO("<<<<<<<< IWALL_write_keypair_with_keyID Success, Ret is %d", nRet);
    }

    //2. 导入注册证书 需将EA.oer 放在 iwall 文件夹下
    nRet = importEA();
    if (0 != nRet)
    {
        return nRet;
    }
    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "<<<<<<<< IWALL Import  EA Success");
    SECLAYER_INFO("<<<<<<<< IWALL Import  EA Success");

    memset(pCertSecretKeyName, 0, 256);
    nCertSecretKeyLen = 128;
    //read AA.oer SK
    strcat(strcat((char *)pCertSecretKeyName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)AA_SK);
    nRet = ReadCertFileContent(pCertSecretKeyName, private_aa_key, &nCertSecretKeyLen);
    if (0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Read CertFileContent Failed %s,  Ret is %d", pCertSecretKeyName, nRet);
        SECLAYER_ERR("<<<<<<<< IWALL Read CertFileContent Failed %s, Ret is %d", pCertSecretKeyName, nRet);
        return -1;
    }
    memset(pCertSecretKeyName, 0, 256);
    nCertSecretKeyLen = 128;
    //read AA.oer PK
    strcat(strcat((char *)pCertSecretKeyName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)AA_PK);
    nRet = ReadCertFileContent(pCertSecretKeyName, public_aa_key, &nCertSecretKeyLen);
    if (0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Read CertFileContent Failed %s,  Ret is %d", pCertSecretKeyName, nRet);
        SECLAYER_ERR("<<<<<<<< IWALL Read CertFileContent Failed %s, Ret is %d", pCertSecretKeyName, nRet);
        return -1;
    }
    memset(pCertSecretKeyName, 0, 256);

    // //3.导入应用证书 密钥对 用指定密钥对
    nRet = IWALL_WriteKeyPairWithKeyID(IWALL_AA_KEY_ID, 0, private_aa_key, 32, public_aa_key, 64);
    if (nRet != 0)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<<  IWALL_write_keypair_with_keyID Failed,  Ret is %d", nRet);
        SECLAYER_ERR("<<<<<<<< IWALL_write_keypair_with_keyID Failed, Ret is %d", nRet);
        return nRet;
    }
    else
    {
        LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "<<<<<<<<  IWALL_write_keypair_with_keyID Success,  Ret is %d", nRet);
        SECLAYER_INFO("<<<<<<<< IWALL_write_keypair_with_keyID Success, Ret is %d", nRet);
    }

    //5. 导入应用证书
    nRet = importAA();
    if (nRet != 0)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Import CertFileContent AA Failed,  Ret is %d", nRet);
        SECLAYER_ERR("<<<<<<<< IWALL Import CertFileContent AA Failed, Ret is %d", nRet);
        return nRet;
    }
    else
    {
        LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "<<<<<<<< IWALL Import CertFileContent AA Success");
        SECLAYER_INFO("<<<<<<<< IWALL Import CertFileContent AA Success");
    }

    return 0;
}

// 读取证书编码内容
static int32_t ReadCertFileContent(unsigned char *file_path, unsigned char *pbBuf, int *nBufLen)
{
    long file_len = 0;
    FILE *fp = NULL;
    fp = fopen((const char *)file_path, "rb");
    if (NULL == fp)
    {
        perror("fopen");
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "fopen %s failed", file_path);
        SECLAYER_ERR("<<<<<<<< iwall secure chip vn4 fopen %s failed", file_path);
        return -1;
    }
    fseek(fp, 0L, SEEK_END); // 读取文件长度
    file_len = ftell(fp);
    if (*nBufLen < file_len)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "iwall buffer too small");
        SECLAYER_ERR("<<<<<<<< iwall buffer too small");
        return -1;
    }
    *nBufLen = file_len;
    fseek(fp, 0L, SEEK_SET);
    fread(pbBuf, file_len, 1, fp); // 读取文件
    fclose(fp);
    return 0;
}

//import other type certs
static int32_t ImportOtherCerts(int cert_type, const char *basePath)
{

    DIR *dir;
    int ret = 0;
    struct dirent *ptr;
    unsigned char fileNamePath[256] = {0};
    unsigned char file_buffer[2048] = {0};

    int file_len = 2048;

    File_t certFileName;
    certFileName.nFileType = cert_type;
    if ((dir = opendir(basePath)) == NULL)
    {
        perror("Open dir error ...");
        exit(1);
    }
    while ((ptr = readdir(dir)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;
        else if (ptr->d_type == DT_REG) //文件
        {

            // printf("the search filename is %s  the len is %d,\n", ptr->d_name, ptr->d_reclen);
            sprintf((char *)fileNamePath, "%s%s", (const char *)basePath, (const char *)ptr->d_name);
            // printf("fileNamePath is: %s  \n", fileNamePath);
            file_len = 2048;
            ret = ReadCertFileContent(fileNamePath, file_buffer, &file_len);
            if (ret != 0)
            {
                LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Read Cert Content Failed");
                SECLAYER_ERR("<<<<<<<< IWALL Read Cert Content Failed");
                return ret;
            }
            memset(certFileName.szFilePath, 0, sizeof(certFileName.szFilePath));
            memcpy(certFileName.szFilePath, fileNamePath, strlen((const char *)fileNamePath));
            // 写入证书
            ret = IWALL_ImportRootCertificate(file_buffer, file_len, (const char *)certFileName.szFilePath, certFileName.nFileType, 2);
            if (0 != ret)
            {
                LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Import Cert %s Failed, Ret is %d", certFileName.szFilePath, ret);
                SECLAYER_ERR("<<<<<<<< IWALL Import Cert %s Failed, Ret is %d", certFileName.szFilePath, ret);
                return -1;
            }
            else
            {
                ;
                // LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "<<<<<<<< IWALL Import Cert %s Success", certFileName.szFilePath);
                // SECLAYER_INFO("<<<<<<<< IWALL Import Cert %s Success", certFileName.szFilePath);
            }
        }
    }

    closedir(dir);
    return ret;
}

// 离线导入根证书
static int32_t importRootCertificate(int8_t *basedir)
{
    int nRet = 0;
    int nCertLen = 0;
    unsigned char pbCert[512] = {0};
    char pCertPathName[256] = {0};

    File_t tIWALLFile[IWALL_CA_NUM] = {0};

    // 信长城 CA证书
    tIWALLFile[0].nFileType = ROOTCA_TYPE;
    strcat(strcat(pCertPathName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)IWALL_ROOTCA);
    memcpy(tIWALLFile[0].szFilePath, pCertPathName, strlen(pCertPathName));
    memset(pCertPathName, 0, 256);
    tIWALLFile[1].nFileType = ICA_TYPE;
    strcat(strcat(pCertPathName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)IWALL_ICA);
    memcpy(tIWALLFile[1].szFilePath, pCertPathName, strlen(pCertPathName));
    memset(pCertPathName, 0, 256);
    tIWALLFile[2].nFileType = PCA_TYPE;
    strcat(strcat(pCertPathName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)IWALL_PCA);
    memcpy(tIWALLFile[2].szFilePath, pCertPathName, strlen(pCertPathName));
    memset(pCertPathName, 0, 256);
    tIWALLFile[3].nFileType = ECA_TYPE;
    strcat(strcat(pCertPathName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)IWALL_ECA);
    memcpy(tIWALLFile[3].szFilePath, pCertPathName, strlen(pCertPathName));
    memset(pCertPathName, 0, 256);
    tIWALLFile[4].nFileType = PRA_TYPE;
    strcat(strcat(pCertPathName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)IWALL_PRA);
    memcpy(tIWALLFile[4].szFilePath, pCertPathName, strlen(pCertPathName));
    memset(pCertPathName, 0, 256);
    tIWALLFile[5].nFileType = ACA_TYPE;
    strcat(strcat(pCertPathName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)IWALL_ACA);
    memcpy(tIWALLFile[5].szFilePath, pCertPathName, strlen(pCertPathName));
    memset(pCertPathName, 0, 256);
    tIWALLFile[6].nFileType = ARA_TYPE;
    strcat(strcat(pCertPathName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)IWALL_ARA);
    memcpy(tIWALLFile[6].szFilePath, pCertPathName, strlen(pCertPathName));
    memset(pCertPathName, 0, 256);
    tIWALLFile[7].nFileType = CAICT_TYPE;
    strcat(strcat(pCertPathName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)IWALL_CAICT);
    memcpy(tIWALLFile[7].szFilePath, pCertPathName, strlen(pCertPathName));
    memset(pCertPathName, 0, 256);
    //tIWALLFile[3].nFileType = ACA_TYPE;
    // memcpy(tIWALLFile[3].szFilePath, IWALL_ACA, strlen(IWALL_ACA));

    // 写入信长城 CA证书
    int i = 0;
    for (i = 0; i < IWALL_CA_NUM; i++)
    {
        nCertLen = 512;
        memset(pbCert, 0, 512);
        // 读取证书
        nRet = ReadCertFileContent(tIWALLFile[i].szFilePath, pbCert, &nCertLen);
        if (0 != nRet)
        {
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Read ROOT Cert %s Failed", tIWALLFile[i].szFilePath);
            SECLAYER_ERR("<<<<<<<< IWALL Read ROOT Cert %s Failed", tIWALLFile[i].szFilePath);
            return -1;
        }
        // 写入证书
        nRet = IWALL_ImportRootCertificate(pbCert, nCertLen, (const char *)tIWALLFile[i].szFilePath, tIWALLFile[i].nFileType, 0);
        if (0 != nRet)
        {
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Import ROOT Cert %s Failed", tIWALLFile[i].szFilePath);
            SECLAYER_ERR("<<<<<<<< IWALL Import ROOT Cert %s Failed", tIWALLFile[i].szFilePath);
            return -1;
        }
        else
        {
            LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "<<<<<<<< IWALL Import ROOT Cert %s Success", tIWALLFile[i].szFilePath);
            SECLAYER_INFO("<<<<<<<< IWALL Import ROOT Cert %s Success", tIWALLFile[i].szFilePath);
        }
    }
    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "<<<<<<<< IWALL Import ROOT Cert  Success");
    SECLAYER_INFO("<<<<<<<< IWALL Import ROOT Cert  Success");

    //遍历PCA文件夹
    strcat(strcat(pCertPathName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)PCA_CERTS);
    memcpy(tIWALLFile[0].szFilePath, pCertPathName, strlen(pCertPathName));
    nRet = ImportOtherCerts(PCA_TYPE, pCertPathName);
    if (nRet != 0)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Import  Cert  Failed,  Ret is %d", nRet);
        SECLAYER_ERR("<<<<<<<< IWALL Import  Cert Failed, Ret is %d", nRet);
        return -1;
    }
    memset(pCertPathName, 0, 256);

    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "<<<<<<<< IWALL Import  PCA Files  Certs  Success,  Ret is %d", nRet);
    SECLAYER_INFO("<<<<<<<< IWALL Import  PCA Files Certs Success, Ret is %d", nRet);

    //遍历ACA文件夹
    strcat(strcat(pCertPathName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)ACA_CERTS);
    memcpy(tIWALLFile[0].szFilePath, pCertPathName, strlen(pCertPathName));
    nRet = ImportOtherCerts(ACA_TYPE, pCertPathName);
    if (nRet != 0)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Import  Cert  Failed,  Ret is %d", nRet);
        SECLAYER_ERR("<<<<<<<< IWALL Import  Cert Failed, Ret is %d", nRet);
        return -1;
    }
    memset(pCertPathName, 0, 256);

    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "<<<<<<<< IWALL Import  ACA Files  Certs  Success,  Ret is %d", nRet);
    SECLAYER_INFO("<<<<<<<< IWALL Import  ACA Files Certs Success, Ret is %d", nRet);

    return nRet;
}

// 导入注册证书
static int32_t importEA()
{
    int nRet = 0;
    int nEALen = 512;
    unsigned char pbEA[512] = {0};
    unsigned char pCertEAName[256] = {0};

    strcat(strcat((char *)pCertEAName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)IWALL_EA);

    // 读取文件
    nRet = ReadCertFileContent(pCertEAName, pbEA, &nEALen);
    if (0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Read CertFileContent EA Failed,  Ret is %d", nRet);
        SECLAYER_ERR("<<<<<<<< IWALL Read CertFileContent EA Failed, Ret is %d", nRet);
        return -1;
    }
    // 写入证书
    nRet = IWALL_ImportEnrollmentCredential(pbEA, nEALen);
    if (0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Import CertFileContent EA Failed,  Ret is %d", nRet);
        SECLAYER_ERR("<<<<<<<< IWALL Import CertFileContent EA Failed, Ret is %d", nRet);
        return -1;
    }

    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "<<<<<<<< IWALL Import CertFileContent EA Success,  Ret is %d", nRet);
    SECLAYER_INFO("<<<<<<<< IWALL Import CertFileContent EA Success, Ret is %d", nRet);

    return nRet;
}

// 导入信长城应用证书
static int32_t importAA()
{
    int nRet = 0;
    int nAALen = 512;
    unsigned char pbAA[512] = {0};
    unsigned char pCertEAName[256] = {0};

    strcat(strcat((char *)pCertEAName, (const char *)s_SysIwallInfo.m_n8CertsPath), (const char *)IWALL_AA);

    // 读取文件
    nRet = ReadCertFileContent(pCertEAName, pbAA, &nAALen);
    if (0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Read CertFileContent AA Failed,  Ret is %d", nRet);
        SECLAYER_ERR("<<<<<<<< IWALL Read CertFileContent AA Failed, Ret is %d", nRet);
        return -1;
    }
    // 写入证书
    nRet = IWALL_ImportAplicationCertificate(pbAA, nAALen);
    if (0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Import CertFileContent AA Failed,  Ret is %d", nRet);
        SECLAYER_ERR("<<<<<<<< IWALL Import CertFileContent AA Failed, Ret is %d", nRet);
        return -1;
    }

    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "<<<<<<<< IWALL Import CertFileContent AA Success,  Ret is %d", nRet);
    SECLAYER_INFO("<<<<<<<< IWALL Import CertFileContent AA Success, Ret is %d", nRet);

    return nRet;
}

uint32_t SecChipFactoryCheck()
{
    int nRet = 0;
    int status = 0;
    nRet = IWALL_DeviceInit();
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "iwall secure chip New Four init failed");
        SECLAYER_ERR("<<<<<<<< iwall secure chip vn4 init failed");
        goto EXIT;
    }
    nRet =  IWALL_CheckDevicestatus(status);//status 0:正常 其他：错误 
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "IWALL_CheckDevicestatus failed");
        SECLAYER_ERR("<<<<<<<< IWALL_CheckDevicestatus failed");
        goto EXIT;
    }
    nRet =  IWALL_CloseDevice();
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "IWALL_CloseDevice failed");
        SECLAYER_ERR("<<<<<<<< IWALL_CloseDevice failed");
        goto EXIT;
    }
    return status;
EXIT:
    return -1;
}

int32_t SecChip_Init(seclayer_status_callback cb, void *cb_para, const char *fileName)
{
    int nRet = 0;
    nRet = GetConfigInfo(fileName);
    nRet = IWALL_DeviceInit();
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "iwall secure chip New Four init failed");
        SECLAYER_ERR("<<<<<<<< iwall secure chip vn4 init failed");
        goto EXIT;
    }

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "IWALL_DeviceInit New Four success");
    SECLAYER_INFO("<<<<<<<< IWALL_DeviceInit New Four success");

    nRet = ImportCertFilesToSecureChip_IWALL(s_SysIwallInfo.m_n8CertsPath);
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "import certificates New Four to chip failed");
        SECLAYER_ERR("<<<<<<<< import certificates New Four to chip failed");
        goto EXIT;
    }
    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "ImportCertFilesToSecureChip New Four success");
    SECLAYER_INFO("<<<<<<<< ImportCertFilesToSecureChip New Four success");

    nRet = MsgQueueCreate(s_SysIwallInfo.m_n8CertsPath, QUEUE_KEY_ID, &s_SysIwallInfo.m_n32MsgQueueId);
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "msg queue New Four create failed");
        SECLAYER_ERR("<<<<<<<< msg queue New Four create failed");
        goto EXIT;
    }
    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "MsgQueueCreate New Four success");
    SECLAYER_INFO("<<<<<<<< MsgQueueCreate New Four success");

    nRet = pthread_mutex_init(&s_SysIwallInfo.m_tSecLayerLocker, NULL);
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "mutex init New Four failed");
        SECLAYER_ERR("<<<<<<<< mutex init New Four failed");
        goto EXIT_1;
    }

    // nRet = CertUpdaterInit(&s_SysIwallInfo);
    // if (IS_OK != nRet)
    // {
    //     LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "cert updater New Four init failed");
    //     SECLAYER_ERR("<<<<<<<< cert updater New Fourinit failed");
    //     goto EXIT_1;
    // }
    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "CertUpdaterInit New Four success");
    SECLAYER_INFO("<<<<<<<< CertUpdaterInit New Four success");

    return 0;

EXIT_1:
    MsgQueueDel(s_SysIwallInfo.m_n32MsgQueueId);
EXIT:
    return -1;
}

int32_t SecDataSign_RSU(uint64_t p_u64Aid,
                                        uint8_t *pud, int32_t pud_size,
                                        uint8_t *spud, int32_t *spud_size)
{
    int32_t ret = -1;

    if ((NULL == pud) || (0 >= pud_size) ||
        (NULL == spud) || (NULL == spud_size) || (0 >= *spud_size))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< Sign New_Four_RSU Wrong Para");
        SECLAYER_ERR("<<<<<<<< Sign Four_RSU Wrong Para");

        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "AID %ld ", p_u64Aid);

        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "pud SIZE %d ", pud_size);
        SECLAYER_ERR("pud SIZE %d ", pud_size);
        if (NULL != spud_size)
        {
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Spud SIZE %d ", *spud_size);
            SECLAYER_ERR("Spud SIZE %d ", *spud_size);
        }

        return -1;
    }

    struct MsgQueueDataStruct *ptSendData = NULL;

    ret = IWALL_SignSecuredMessage_RSU(p_u64Aid, pud, pud_size, spud, spud_size);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Sign New Four RSU  Data Failed, Ret is %d", ret);
        SECLAYER_ERR("<<<<<<<< IWALL Sign New Four RSU Data Failed, Ret is %d", ret);
        ret = ImportCertFilesToSecureChip_IWALL(s_SysIwallInfo.m_n8CertsPath);
        if (IS_OK != ret)
        {
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< import certificates New Four to chip failed Ret is %d", ret);
            SECLAYER_ERR("<<<<<<<< import certificates New Four to chip failed,Ret is %d", ret);
        }
        return ret;
    }
    // LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "IWALL Sign New Four pud Result Success, Ret is %d", ret);

    pthread_mutex_lock(&s_SysIwallInfo.m_tSecLayerLocker);
    if (CERT_HAVE_UPDATE == s_SysIwallInfo.m_n32CertUpdateFlag)
    {
        ptSendData = (struct MsgQueueDataStruct *)malloc(sizeof(struct MsgQueueDataStruct) + *spud_size);
        if (NULL != ptSendData)
        {
            ptSendData->m_n32DataSize = *spud_size;
            memcpy(ptSendData->m_u8Buf, spud, *spud_size);
            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "send to download New Four thread:%p", ptSendData);
            MsgQueueSend(s_SysIwallInfo.m_n32MsgQueueId, &ptSendData, PTR_SIZE);
            s_SysIwallInfo.m_n32CertUpdateFlag = 0;
        }
    }
    pthread_mutex_unlock(&s_SysIwallInfo.m_tSecLayerLocker);

    return 0;
}

int32_t SecDataVerify(uint8_t *spud, int32_t spud_size,
                                          uint8_t *pud, int32_t *pud_size,
                                          uint64_t *p_pu64AID)
{
    int32_t ret = -1;
    if ((NULL == spud) || (0 >= spud_size) ||
        (NULL == pud) || (NULL == pud_size) ||
        (0 >= *pud_size) || (NULL == p_pu64AID))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Verify New Four  Wrong Para");
        SECLAYER_ERR("<<<<<<<< IWALL Verify New Four Wrong Para");
        return -1;
    }

    ret = IWALL_VerifySecuredMessage(spud, spud_size, pud, pud_size, p_pu64AID);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL Verify New Four Data Failed, Ret is %d", ret);
        SECLAYER_ERR("<<<<<<<< IWALL Verify New Four Data Failed, Ret is %d", ret);
        return ret;
    }
    // LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "IWALL Verify New Four Spud Result , Ret is %d", ret);

    return 0;
}

int32_t SecDataSign_OBU(uint64_t aid, int32_t emergency_event_flag,
                                  double longitude, double latitude,
                                  uint8_t *pdu, int32_t pdu_size, uint8_t *spdu, int32_t *spdu_size)
{
    LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< IWALL SecDataSign_OBU not support");
    SECLAYER_ERR("<<<<<<<< IWALL SecDataSign_OBU not support");
    return -1;
}




int32_t SecChipDeinit(void)
{
    int32_t nRet = 0;
    pthread_mutex_lock(&s_SysIwallInfo.m_tSecLayerLocker);
    MsgQueueDel(s_SysIwallInfo.m_n32MsgQueueId);
    // CertUpdaterDeinit(&s_SysIwallInfo);
    nRet =  IWALL_CloseDevice();
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "IWALL_CloseDevice failed");
        SECLAYER_ERR("<<<<<<<< IWALL_CloseDevice failed");
    }
    pthread_mutex_unlock(&s_SysIwallInfo.m_tSecLayerLocker);

    return 0;
}
