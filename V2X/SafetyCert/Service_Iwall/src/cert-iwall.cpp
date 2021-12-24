#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "IWALL_V2X_API.h"
#include <vector>
#include <string>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "SimpleIni.h"
extern "C"{
#include "cert-iwall.h"
#include "wj_log.h"
}

using namespace std;

#define ROOTCA_TYPE  4
#define ECA_TYPE     3
#define ACA_TYPE     2
#define PCA_TYPE     7


// 大唐证书路径
#define DT_CA_NUM          1
#define DT_ROOTCA        "./certs/datang/ROOT.oer"
#define DT_ECA            "./certs/datang/ECA.oer"
#define DT_PCA            "./certs/datang/PCA.oer"
#define DT_ACA            "./certs/datang/ACA.oer"
#define DT_EA            "./certs/datang/EA.oer"
#define DT_AA           "./certs/datang/AA.oer"

//信长城证书路径
#define IWALL_CA_NUM       4
#define IWALL_ROOTCA        "./certs/iwall/ROOT.oer"
#define IWALL_ECA            "./certs/iwall/ECA.oer"
#define IWALL_PCA            "./certs/iwall/PCA.oer"
#define IWALL_ACA            "./certs/iwall/ACA.oer"
#define IWALL_EA            "./certs/iwall/EA.oer"
#define IWALL_AA            "./certs/iwall/AA.oer"
#define HOST_PCA_URL        "www.v2xsec.cn"

// 国汽证书路径
#define CICV_CA_NUM     4
#define CICV_PCA_1        "./certs/guoqi/cicv-PCACert1.oer"
#define CICV_PCA_2        "./certs/guoqi/cicv-PCACert2.oer"
#define CICV_PCA_3        "./certs/guoqi/cicv-PCACert3.oer"
#define CICV_PCA_4        "./certs/guoqi/cicv-PCACert4.oer"

// 华为证书路径
#define HUAWEI_CA_NUM   1
#define HUAWEI_PCA      "./certs/huawei/PCACert.oer"


typedef struct st_File{
    int nFileType;
    char szFilePath[260];
}File_t;


/*return:
    0--root Cert has imported
    1--root Cert no  imported
*/
int Get_ImportCertStatus(char *FileName)
{
    CSimpleIniA ini;
    int CertStatus = 1;

    int l_n32ret = access(FileName, 0);
    if(l_n32ret < 0)
    {
        LogPrint(LOG_LEVEL_NOTICE, MODULE_NAME, "No Config, create %s, set status %d", FileName, CertStatus);
        ini.SetUnicode();
        ini.LoadFile(FileName);
        ini.SetLongValue("RootCAImport", "Status", CertStatus);
        ini.SaveFile(FileName);
    }
    else
    {
        ini.SetUnicode();
        ini.LoadFile(FileName);
        CertStatus = ini.GetLongValue("RootCAImport", "Status", 0);
    }
    return CertStatus;
}

int Set_ImportCertStatus(char *FileName, int status)
{
    CSimpleIniA ini;

    ini.SetUnicode();
    ini.LoadFile(FileName);
    ini.SetLongValue("RootCAImport", "Status", status);
    ini.SaveFile(FileName);

    return 0;
}


// 读取证书编码内容
int read_file(const char *file_path, unsigned char *pbBuf, int *nBufLen)
{
    long file_len = 0;
    FILE *fp = NULL;
    fp = fopen(file_path, "rb");
    if(NULL == fp)
    {
        perror("fopen");
        return -1;
    }
    fseek(fp, 0L, SEEK_END);    // 读取文件长度
    file_len = ftell(fp);
    if(*nBufLen < file_len)
    {
        printf("buffer too small\n");
        return -1;
    }
    *nBufLen = file_len;
    fseek(fp, 0L, SEEK_SET);
    fread(pbBuf, file_len, 1, fp);  // 读取文件
    fclose(fp);
    return 0;
}

void HexStrToByte(const char* source, unsigned char* dest, int sourceLen)
{
    short i;
    unsigned char highByte, lowByte;
    for (i = 0; i < sourceLen; i += 2)
    {
        highByte = toupper(source[i]);
        lowByte  = toupper(source[i + 1]);
        if (highByte > 0x39)
            highByte -= 0x37;
        else
            highByte -= 0x30;
        if (lowByte > 0x39)
            lowByte -= 0x37;
        else
            lowByte -= 0x30;

        dest[i / 2] = (highByte << 4) | lowByte;
    }
    return ;
}

// 离线导入根证书
int importRootCertificate()
{
    int nRet = 0;
    int nCertLen = 0;
    unsigned char pbCert[512] = {0};


    File_t tDTFile[DT_CA_NUM] = {0};
    File_t tIWALLFile[IWALL_CA_NUM] = {0};
    File_t tCICVFile[CICV_CA_NUM] = {0};
    File_t tHuaweiFile[HUAWEI_CA_NUM] = {0};

    // 大唐CA证书
    tDTFile[0].nFileType = PCA_TYPE;
    memcpy(tDTFile[0].szFilePath, DT_PCA, strlen(DT_PCA));
    nRet = IWALL_ImportRootCertificate(pbCert, nCertLen, tDTFile[0].szFilePath, tDTFile[0].nFileType, 1);
    if (0 != nRet)
    {
        printf("%s -->> read_file %s failed\n", __FUNCTION__, tDTFile[0].szFilePath);
        return -1;
    }

     // 信长城 CA证书
    tIWALLFile[0].nFileType = ROOTCA_TYPE;
    memcpy(tIWALLFile[0].szFilePath, IWALL_ROOTCA, strlen(IWALL_ROOTCA));
    tIWALLFile[1].nFileType = ECA_TYPE;
    memcpy(tIWALLFile[1].szFilePath, IWALL_ECA, strlen(IWALL_ECA));
    tIWALLFile[2].nFileType = PCA_TYPE;
    memcpy(tIWALLFile[2].szFilePath, IWALL_PCA, strlen(IWALL_PCA));
    tIWALLFile[3].nFileType = ACA_TYPE;
    memcpy(tIWALLFile[3].szFilePath, IWALL_ACA, strlen(IWALL_ACA));

    // 写入信长城 CA证书
    for(int i = 0; i < IWALL_CA_NUM; i++)
    {
        nCertLen = 512;
        memset(pbCert, 0, 512);
        // 读取证书
        nRet = read_file(tIWALLFile[i].szFilePath, pbCert, &nCertLen);
        if(0 != nRet)
        {
            printf("%s -->> read_file %s failed\n", __FUNCTION__, tIWALLFile[i].szFilePath);
            return -1;
        }
        // 写入证书
        nRet = IWALL_ImportRootCertificate(pbCert, nCertLen, tIWALLFile[i].szFilePath, tIWALLFile[i].nFileType, 0);
        if(0 != nRet)
        {
            printf("%s -->> Import %s failed: %d\n", __FUNCTION__, tIWALLFile[i].szFilePath, nRet);
            return -1;
        }
    }

    // 国汽证书
    tCICVFile[0].nFileType = PCA_TYPE;
    memcpy(tCICVFile[0].szFilePath, CICV_PCA_1, strlen(CICV_PCA_1));
    tCICVFile[1].nFileType = PCA_TYPE;
    memcpy(tCICVFile[1].szFilePath, CICV_PCA_2, strlen(CICV_PCA_2));
    tCICVFile[2].nFileType = PCA_TYPE;
    memcpy(tCICVFile[2].szFilePath, CICV_PCA_3, strlen(CICV_PCA_3));
    tCICVFile[3].nFileType = PCA_TYPE;
    memcpy(tCICVFile[3].szFilePath, CICV_PCA_4, strlen(CICV_PCA_4));
    // 写入国汽PCA
    for(int i = 0; i < CICV_CA_NUM; i++)
    {
        nCertLen = 512;
        memset(pbCert, 0, 512);
        // 读取证书
        nRet = read_file(tCICVFile[i].szFilePath, pbCert, &nCertLen);
        if(0 != nRet)
        {
            printf("%s -->> read_file %s failed\n", __FUNCTION__, tCICVFile[i].szFilePath);
            return -1;
        }
        // 写入证书
        nRet = IWALL_ImportRootCertificate(pbCert, nCertLen, tCICVFile[i].szFilePath, tCICVFile[i].nFileType, 1);
        if(0 != nRet)
        {
            printf("%s -->> Import %s failed: %d\n", __FUNCTION__, tCICVFile[i].szFilePath, nRet);
            return -1;
        }
    }

    // 华为CA证书
    tHuaweiFile[0].nFileType = PCA_TYPE;
    memcpy(tHuaweiFile[0].szFilePath, HUAWEI_PCA, strlen(HUAWEI_PCA));
    // 写入华为CA证书
    for(int i = 0; i < HUAWEI_CA_NUM; i++)
    {
        nCertLen = 512;
        memset(pbCert, 0, 512);
        // 读取证书
        nRet = read_file(tHuaweiFile[i].szFilePath, pbCert, &nCertLen);
        if(0 != nRet)
        {
            printf("%s -->> read_file %s failed\n", __FUNCTION__, tHuaweiFile[i].szFilePath);
            return -1;
        }
        // 写入证书
        nRet = IWALL_ImportRootCertificate(pbCert, nCertLen, tHuaweiFile[i].szFilePath, tHuaweiFile[i].nFileType, 2);
        if(0 != nRet)
        {
            printf("%s -->> Import %s failed: %d\n", __FUNCTION__, tHuaweiFile[i].szFilePath, nRet);
            return -1;
        }
    }
    return nRet;
}

int importEA()
{
    int nRet = 0;
    int nEALen = 512;
    unsigned char pbEA[512] = {0};

    // 读取文件
    nRet = read_file(IWALL_EA, pbEA, &nEALen);

    if(0 != nRet)
    {
        printf("%s -->> read_file EA failed\n", __FUNCTION__);
        return -1;
    }
    // 写入证书
    nRet = IWALL_ImportEnrollmentCredential(pbEA, nEALen);
    if(0 != nRet)
    {
        printf("%s -->> IWALL_ImportEnrollmentCredential failed: 0x%x\n", __FUNCTION__, nRet);
        return -1;
    }
    return nRet;
}

int32_t Apply_PseudonymCert()
{
    int nRet = 0;
    char pVIN[13] = "EA";
    char pURL[256] = "http://39.96.75.192:999";

    struct hostent *h;
    if ((h = gethostbyname(HOST_PCA_URL)) == NULL)
    {
        fprintf(stderr, "can't get ip addr\n");
        exit(1);
    }
    printf("HostName :%s\n", h->h_name);
    printf("IP Address :%s\n", inet_ntoa(*((struct in_addr *)h->h_addr)));
    sprintf(pURL, "http://%s:999", inet_ntoa(*(struct in_addr *)h->h_addr));
    printf("IP Address: %s \n", pURL);

    nRet = IWALL_ApplyPseudonymTicket((unsigned char *)pVIN, strlen(pVIN), pURL);
    if (0 != nRet)
    {
        return -1;
    }

    return nRet;
}



int32_t ImportCertificate()
{
    int ret = 0;
    int ea_keyID = 0 ;//EA 证书 固定keyID = 0;
     int aa_keyID = 21; // AA 证书 固定 keyID = 21;
    std::string private_key_str = "18b206360d0dbf4797ac09642b971dff5d7da19a1b35ce55198696a342776260";
    std::string public_key_str = "48C4339B3132305A6EB6A3B5159CE538BBA6791050FF3E23B85286D2EF5D0495809B25D06C7BB65A46B215BEDBCF1F2A9AA73A860D530F850A0A9554479EC600";


    unsigned char private_key[32] = {0};
    unsigned char public_key[64] = {0};
    HexStrToByte(private_key_str.c_str(), private_key, private_key_str.length());
    HexStrToByte(public_key_str.c_str(),public_key,public_key_str.length());


    // 1、导入根证书 及注册证书密钥对
    ret = importRootCertificate();
    if(0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "import RootCertificate failed");
        return -1;
    }
    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "importRootCertificate success");

    ret = IWALL_WriteKeyPairWithKeyID(ea_keyID, 0, private_key, 32, public_key,64);
    if(ret != 0)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Write KeyPair With KeyID failed");
    }

    sleep(1);

    // 2. 导入注册证书 需将EA.oer 放在 iwall 文件夹下
    ret = importEA();
    if(0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "import EA failed");
        return -1;
    }
    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "import_ea success");
    sleep(1);

    // //3.导入应用证书 密钥对 用指定密钥对
    ret = IWALL_WriteKeyPairWithKeyID(aa_keyID, 0, private_key, 32, public_key,64);
    if(ret != 0)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Write KeyPair With KeyID failed");
    }
    return ret;
}