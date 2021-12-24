#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wj_inc_com.h"
#include "SecLayerIntf.h"

extern void SetWJV2_MessageCallback(WJV2_UperFromFileEncodeMain_BACK p_wjv2_UperFromFileEncodeMain,
                                    WJV2_UperEncOrDecMain_BACK p_wjv2_UperEncOrDecMain,
                                    WJV2_SetGetAIDFromFileCallback p_wjv2_SetGetAIDFromFileCallback);

extern void SetWJV3_MessageCallback(WJV3_UperFromFileEncodeMain_BACK p_wjv3_UperFromFileEncodeMain,
                                    WJV3_UperEncOrDecMain_BACK p_wjv3_UperEncOrDecMain,
                                    WJV3_SetGetAIDFromFileCallback p_wjv3_SetGetAIDFromFileCallback);

extern void SetWJV4_MessageCallback(WJV4_UperFromFileEncodeMain_BACK p_wjv4_UperFromFileEncodeMain,
                                    WJV4_UperEncOrDecMain_BACK p_wjv4_UperEncOrDecMain,
                                    WJV4_SetGetAIDFromFileCallback p_wjv4_SetGetAIDFromFileCallback);

extern void SetWJVN4_MessageCallback(WJVN4_UperFromFileEncodeMain_BACK p_wjvn4_UperFromFileEncodeMain,
                                     WJVN4_UperEncOrDecMain_BACK p_wjvn4_UperEncOrDecMain,
                                     WJVN4_SetGetAIDFromFileCallback p_wjvn4_SetGetAIDFromFileCallback);

/**
 * @brief StackInit 协议栈初始化
 *
 * @param[in] Init -- 初始化函数结构体
 *
 * @return true/false             成功/失败
 *
 */
__attribute__((visibility("default"))) int StackInit(Stack_Init_t *Init)
{
    if (NULL == Init)
    {
        printf("%s %s %d Init is NULL!!\n", __FILE__, __FUNCTION__, __LINE__);
        return -1;
    }
    int ret = 0;
    SetWJV2_MessageCallback(Init->p_WJV2_UperFromFileEncodeMain, Init->p_WJV2_UperEncOrDecMain,
                            Init->p_WJV2_SetGetAIDFromFileCallback);

    SetWJV3_MessageCallback(Init->p_WJV3_UperFromFileEncodeMain, Init->p_WJV3_UperEncOrDecMain,
                            Init->p_WJV3_SetGetAIDFromFileCallback);

    SetWJV4_MessageCallback(Init->p_WJV4_UperFromFileEncodeMain, Init->p_WJV4_UperEncOrDecMain,
                            Init->p_WJV4_SetGetAIDFromFileCallback);

    SetWJVN4_MessageCallback(Init->p_WJVN4_UperFromFileEncodeMain, Init->p_WJVN4_UperEncOrDecMain,
                             Init->p_WJVN4_SetGetAIDFromFileCallback);

    /* 1.初始化参数配置 */
    if (strlen(Init->FileName) > 0)
    {
        memset(&ProtocolStackParamConfig, 0, sizeof(ProtocolStackParamConfig_t));
        ret = WJ_InitParamDataInterface(&ProtocolStackParamConfig, Init->FileName);
        if (0 != ret)
        {
            printf("%s %s %d Param init failed!!\n", __FILE__, __FUNCTION__, __LINE__);
            return Param_init_Err;
        }
        /* 创建线程监控协议栈配置文件 */
        pthread_t l_tpthreadid = 0;
        ret = pthread_create(&l_tpthreadid, NULL, (void *)ConfigFileProcessReloadThreadFun, Init->FileName);
        if (ret != 0)
        {
            printf("pthread_create is err: ret = %d", ret);
            return Param_init_Err;
        }
    }

    /* 2.初始化日志配置 */
    if (NULL != Init->WJ_LogInit)
    {
        ret = Init->WJ_LogInit((const char *)ProtocolStackParamConfig.logConfigPath.logConfigFilePath);
        if (0 != ret)
        {
            printf("%s %s %d Log init failed!!\n", __FILE__, __FUNCTION__, __LINE__);
            return Log_init_Err;
        }
    }
    /* 3.初始化安全层 */
    if ((NULL != Init->WJ_SecureInit) && (strlen(Init->FileName) > 0))
    {
        ret = Init->WJ_SecureInit(Init->p_Secfunc, NULL, Init->FileName);
        if (0 != ret)
        {
            LogPrint(LOG_LEVEL_ERR, "Stack_Init_Err", "Secure layer init failed!!\n");
            return Sec_init_Err;
        }
    }
    /* 4.设置安全层签名、验签回调函数，供协议栈使用 */
    SetSecuredMessageCallback(Init->p_Signfunc, Init->p_Verifyfunc);

    /* 5.初始化接收模块配置 */
    ret = StackRecvInit();
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Init_Err", "Stack_RX init failed!!\n");
        return Stack_RX_init_Err;
    }

    /* 6.初始化接入层接收配置并设置接收回调函数 */
    if (NULL != Init->WJ_V2XTxRxInit)
    {
        ret = Init->WJ_V2XTxRxInit(MsgRx_CallBack);
        if (0 != ret)
        {
            LogPrint(LOG_LEVEL_ERR, "Stack_Init_Err", "V2X_Rx init failed!!\n");
            return V2X_Rx_init_Err;
        }
    }

    /* 7.初始化发送模块配置 */
    ret = StackSendInit(Init->p_Sendfunc);
    if (0 > ret)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Init_Err", "Stack_Tx init failed!!\n");
        return Stack_TX_init_Err;
    }
    return 0;
}