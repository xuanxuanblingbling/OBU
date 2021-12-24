
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "rw-ini.h"
#include "scmf_api.h"
#include "wj_log.h"

#define MODULE_NAME "SCMF"
#define SEC_VERSION "1.0.3"

#define SECLAYER_DEBUG(fmt, ...) printf("\033[31m[Seclayer: %s:%d:%s:%s] " #fmt "\033[0m\r\n", __func__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__)
#define SECLAYER_ERR(fmt, ...) printf("\033[31m[Seclayer: %s:%d:%s:%s] " #fmt "\033[0m\r\n", __func__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__)
#define SECLAYER_INFO(fmt, ...) printf("\033[32m[Seclayer: %s:%d:%s:%s] " #fmt "\033[0m\r\n", __func__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__)

struct SecInfoStruct
{
    int32_t m_n32Manufacture;         //1 is xdja ; 2 is iwall
    int32_t m_n32EncryptChipPinInt0;  //加密芯片引脚配置 RSU：166 132 OBU：92 85
    int32_t m_n32EncryptChipPinInt1;  //加密芯片POR复位引脚【可选，不使用保持-1】
    int32_t m_n32EncryptChipPinPor;   //加密芯片GPIO供电引脚【可选，不使用保持-1】
    int32_t m_n32EncryptChipPinPower; //加密芯片低功耗唤醒引脚【可选，不使用保持-1】
    int32_t m_n32EncryptChipPinQwk;   //EncryptChipPinQwk = -1
    int32_t m_n32EncryptChipSpeed;    //加密芯片SPI频率配置,默认20/MHz
    int8_t m_n8Eraurl[512];           //证书申请网址
    int8_t m_n8PraUrl[512];           //证书申请网址
    int8_t m_n8AraUrl[512];           //证书申请网址
    int8_t m_n8CertsPath[512];
    int8_t m_n8ChipLogPath[512];
};

static struct SecInfoStruct s_SecInfo = {0};

/**************************************************
*名称： 初始化参数函数
*描述： 系统初始化，从配置文件中读取参数
*参数：
*       SeclayerParamConfig		 
*       FileName		                 
*返回值：0--成功；
*返回值：非0--错误号。
*说明：无
**************************************************/
static int GetConfigInfo(const char *FileName)
{
    if (NULL == FileName)
    {
        LogPrint(LOG_LEVEL_INFO, "协议栈参数配置", "param is NULL\n");
        SECLAYER_ERR("协议栈参数配置为空");
        return -1;
    }
    int iVariable = 0;
    char strVariable[256] = {0};

    //参数设置
    memset(strVariable, 0, sizeof(strVariable));
    SecGetPrivateProfileString("SecurityParamConfig", "EncryptChipLogFilePath", NULL, strVariable, sizeof(strVariable), FileName);
    memcpy(s_SecInfo.m_n8ChipLogPath, strVariable, strlen(strVariable));

    memset(strVariable, 0, sizeof(strVariable));
    SecGetPrivateProfileString("SecurityParamConfig", "EncryptChipCertPath", NULL, strVariable, sizeof(strVariable), FileName);
    memcpy(s_SecInfo.m_n8CertsPath, strVariable, strlen(strVariable));

    memset(strVariable, 0, sizeof(strVariable));
    SecGetPrivateProfileString("SecurityParamConfig", "EncryptChipEraurl", NULL, strVariable, sizeof(strVariable), FileName);
    memcpy(s_SecInfo.m_n8Eraurl, strVariable, strlen(strVariable));

    memset(strVariable, 0, sizeof(strVariable));
    SecGetPrivateProfileString("SecurityParamConfig", "EncryptChipPraUrl", NULL, strVariable, sizeof(strVariable), FileName);
    memcpy(s_SecInfo.m_n8PraUrl, strVariable, strlen(strVariable));

    memset(strVariable, 0, sizeof(strVariable));
    SecGetPrivateProfileString("SecurityParamConfig", "EncryptChipAraUrl", NULL, strVariable, sizeof(strVariable), FileName);
    memcpy(s_SecInfo.m_n8AraUrl, strVariable, strlen(strVariable));

    s_SecInfo.m_n32Manufacture = SecGetPrivateProfileInt("SecurityParamConfig", "EncryptChipType", iVariable, FileName);

    s_SecInfo.m_n32EncryptChipPinInt0 = SecGetPrivateProfileInt("SecurityParamConfig", "EncryptChipPinInt0", iVariable, FileName);
    s_SecInfo.m_n32EncryptChipPinInt1 = SecGetPrivateProfileInt("SecurityParamConfig", "EncryptChipPinInt1", iVariable, FileName);
    s_SecInfo.m_n32EncryptChipPinPor = SecGetPrivateProfileInt("SecurityParamConfig", "EncryptChipPinPor", iVariable, FileName);
    s_SecInfo.m_n32EncryptChipPinPower = SecGetPrivateProfileInt("SecurityParamConfig", "EncryptChipPinPower", iVariable, FileName);
    s_SecInfo.m_n32EncryptChipPinQwk = SecGetPrivateProfileInt("SecurityParamConfig", "EncryptChipPinQwk", iVariable, FileName);
    s_SecInfo.m_n32EncryptChipSpeed = SecGetPrivateProfileInt("SecurityParamConfig", "EncryptChipSpeed", iVariable, FileName);

    LogPrint(LOG_LEVEL_WARN, "MODULE_NAME", "SecLayer Version:%s, build time:%s:%s", SEC_VERSION, __DATE__, __TIME__);
    SECLAYER_INFO("SecLayer Version:%s, build time:%s:%s", SEC_VERSION, __DATE__, __TIME__);

    return 0;
}

void usage()
{
    printf("\nusage:\n\t./scmf_demo [options] [param]\n\n"
           "where options are:\n"
           "\t 1 : call ITS_SCMF_Version\n"
           "\t 2 : call ITS_SCMF_Status\n"
           "\t 3 : call ITS_SCMF_StartService and other\n");
}

int main(int argc, char **argv)
{
    char ver[100] = {0};
    int len = sizeof(ver);

    GetConfigInfo("./Config_SecScmf.ini");

    int rc = ITS_SCMF_Version(ver, &len);
    if (rc != SCMF_Err_Ok)
    {
        printf("ITS_SCMF_Version failed\n");
        return rc;
    }
    printf("scmf version: %s >>>>>>>>>>>>>>>>>>>>>\n", ver);

    TServiceConfig cfg;
    cfg.eraUrl = (char *)(s_SecInfo.m_n8Eraurl);
    cfg.praUrl = (char *)(s_SecInfo.m_n8PraUrl);
    cfg.araUrl = (char *)(s_SecInfo.m_n8AraUrl);

    cfg.mraUrl = NULL;
    cfg.rdcUrl = NULL;
    cfg.mdcUrl = NULL;
    cfg.cpocUrl = NULL;

    rc = ITS_SCMF_SetSafeChipGpio(s_SecInfo.m_n32EncryptChipPinInt0, s_SecInfo.m_n32EncryptChipPinInt1,
                                  s_SecInfo.m_n32EncryptChipPinPor, s_SecInfo.m_n32EncryptChipPinPower,
                                  s_SecInfo.m_n32EncryptChipPinQwk, s_SecInfo.m_n32EncryptChipSpeed);
    if (0 != rc)
    {
        printf("call ITS_SCMF_SetSafeChipGpio failed\n");
        return rc;
    }
    printf("call ITS_SCMF_SetSafeChipGpio success >>>>>>>>>>>>>>>\n");

    ITS_SCMF_SetLogConf(s_SecInfo.m_n8ChipLogPath, 20);

    rc = ITS_SCMF_Init(0, s_SecInfo.m_n8CertsPath);
    if (0 != rc)
    {
        printf("ITS_SCMF_Init failed\n");
        return rc;
    }
    printf("scmf init ok >>>>>>>>>>>>>>>>>>>>>\n");

    rc = ITS_SCMF_StartService(&cfg);
    if (0 != rc)
    {
        printf("ITS_SCMF_StartService failed\n");
        return rc;
    }
    printf("scmf service start ok >>>>>>>>>>>>>>>>>>>>>>\n");

    while (1)
    {
        //todo

        sleep(300);
        printf("<<<<<<<<<<<<<<<<< 5 mins printf  >>>>>>>>>>>>>>>>>>>>\n");
    }

    ITS_SCMF_Destroy();
    printf("scmf destroy ok >>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    return 0;
}
