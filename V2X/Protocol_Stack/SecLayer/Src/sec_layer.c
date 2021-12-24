#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "wj_log.h"
#include "common.h"
#include "rw-ini.h"
#include "dllopen.h"
#include "SecLayer.h"

#define SEC_VERSION "1.1.0"


#define SECLAYER_ERR(fmt, ...) printf("\033[31m[Seclayer: %s:%d:%s:%s] " #fmt "\033[0m\r\n", __func__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__)
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
    s_SecInfoConfig.m_n32IsInitSecLayer = SecGetPrivateProfileInt("SecurityParamConfig", "isInitSecLayer", iVariable, FileName);
    s_SecInfoConfig.m_n32DevideType = SecGetPrivateProfileInt("SecurityParamConfig", "SignDeviceType", iVariable, FileName);
    s_SecInfoConfig.m_n32ProtocolType = SecGetPrivateProfileInt("MsgFrameConfig", "MsgFrameVersion", iVariable, FileName);
    s_SecInfoConfig.m_n32Manufacture = SecGetPrivateProfileInt("SecurityParamConfig", "EncryptChipType", iVariable, FileName);

    memset(strVariable, 0, sizeof(strVariable));
    SecGetPrivateProfileString("SecurityParamConfig", "IwallLibPathName", NULL, strVariable, sizeof(strVariable), FileName);
    memcpy(s_SecInfoConfig.m_n8DllPath, strVariable, strlen(strVariable));
    
    LogPrint(LOG_LEVEL_EMERG, "SEC_VERSION", "SecLayer Version:%s, build time:%s:%s", SEC_VERSION, __DATE__, __TIME__);
    SECLAYER_INFO("SecLayer Version:%s, build time:%s:%s", SEC_VERSION, __DATE__, __TIME__);
    return 0;
}

int32_t SecureLayerInit(seclayer_status_callback cb, void *cb_para, const char *fileName)
{
    int32_t nRet = -1;
    nRet = GetConfigInfo(fileName);
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Read ConfigInfo From ConfigFile Faild");
        SECLAYER_ERR("<<<<<<<< Read ConfigInfo From ConfigFile Faild");
    }
    nRet = dllOpenInit(s_SecInfoConfig.m_n32ProtocolType, s_SecInfoConfig.m_n32Manufacture, fileName);
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "dllopenInit error");
       SECLAYER_ERR("<<<<<<<< dllopenInit error");
        return -1;
    }
    nRet = SECFUNTION.wj_SecChip_Init(cb, cb_para, fileName);
    if (IS_OK != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "wj_SecChip_Init error，nRet is %d",nRet);
        SECLAYER_ERR("<<<<<<<< wj_SecChip_Init error");
        return -1;
    }
    return 0;
}

DLL_PUBLIC int32_t SignSecuredMessage(MsgLayData_st MsgLayData, uint8_t *pu8SecLayData, int32_t *pn32SecLayDataLen)
{
    int32_t nRet = -1;
    if(DEVIDE_TYPE_RSU == s_SecInfoConfig.m_n32DevideType)
    {
        nRet = SECFUNTION.wj_SecDataSign_RSU(MsgLayData.nAID, 
                                             MsgLayData.pu8MsgLayData, MsgLayData.n32MsgLayDataLen, 
                                             pu8SecLayData, pn32SecLayDataLen);
        if(IS_OK != nRet)
        {
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "wj_SecDataSign_RSU error nRet = %d",nRet);
            return -1;
        }
        SECLAYER_ERR("<<<<<<<< wj_SecDataSign_RSU , ok");
        return 0;
    }
    if(DEVIDE_TYPE_OBU == s_SecInfoConfig.m_n32DevideType)
    {
        nRet = SECFUNTION.wj_SecDataSign_OBU(MsgLayData.nAID, MsgLayData.nEmergencyEventFlag, 
                                            MsgLayData.dLongitude, MsgLayData.dLatitude,
                                            MsgLayData.pu8MsgLayData, MsgLayData.n32MsgLayDataLen, 
                                            pu8SecLayData,pn32SecLayDataLen);
        if(IS_OK != nRet)
        {
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "wj_SecDataSign_OBU error nRet = %d",nRet);
            return -1;
        }
        SECLAYER_ERR("<<<<<<<< wj_SecDataSign_OBU , ok");
        return 0;
    }
    LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "s_SecInfoConfig error DevideType is %d",s_SecInfoConfig.m_n32DevideType);
    return -1;
}

DLL_PUBLIC int32_t VerifySecuredMessage(uint8_t *pu8SecLayData, int32_t n32SecLayDataLen, MsgLayData_st *MsgLayData)
{
    int32_t nRet = -1;
    nRet = SECFUNTION.wj_SecDataVerify(pu8SecLayData, n32SecLayDataLen, 
                                        MsgLayData->pu8MsgLayData, &(MsgLayData->n32MsgLayDataLen),
                                        &(MsgLayData->nAID));
    if(0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< wj_SecDataVerify Error , ret is %d", nRet);
        SECLAYER_ERR("<<<<<<<< wj_SecDataVerify, ret is %d", nRet);
        return -1;
    }
    SECLAYER_ERR("<<<<<<<< wj_SecDataVerify , ok");
    return 0;
}

DLL_PUBLIC int32_t SecureLayerDeinit(void)
{
    int32_t nRet = -1; 
    nRet = SECFUNTION.wj_SecChipDeinit();
    if(0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< wj_SecChipDeinit Error , nRet is %d", nRet);
        SECLAYER_ERR("<<<<<<<< wj_SecChipDeinit Error , nRet is %d", nRet);
        return -1;
    }
    SECLAYER_ERR("<<<<<<<< SecureLayerDeinit , ok");
    return 0;
}
