/**
 * @defgroup WJ_Interface_Com WJ_Interface_Com API
 * @{
 *
 * 本模块提供V2X协议栈对外接口及数据结构头文件.
 *
 * @}
 *
 */

/**
 * @defgroup WJ_Interface WJ_Interface API
 * @ingroup WJ_Interface_Com API
 * @{
 *
 * 本模块V2X协议栈对外头文件.
 *
 * @file wj_inc_com.h
 * @brief API file.
 *
 */

#ifndef _WJ_INC_COM_H_
#define _WJ_INC_COM_H_
//协议栈Stack_Lib头文件
#include "InterfaceFrameMsgSending.h"
#include "RxInit.h"
#include "ConfigModuleRW.h"
#include "wj_log.h"
#include "TransparentTransmit.h"
#include "wj_Message_com.h"
#include "SecDataInfo.h"

enum init_status
{
   Param_init_Err = -1,    //参数初始化失败
   Log_init_Err = -2,      //日志初始化失败
   Sec_init_Err = -3,      //安全模块初始化失败
   Stack_RX_init_Err = -4, //协议栈模块接收初始化失败
   Stack_TX_init_Err = -5, //协议栈模块发送初始化失败
   V2X_Rx_init_Err = -6,   //接入模块接收初始化失败
   V2X_Tx_init_Err = -7    //接入模块发送初始化失败
};

typedef struct Stack_Init
{
   char FileName[128];                 //协议栈配置文件路径
   SECSIGNCALL_BACK p_Signfunc;        //安全层签名接口回调(可选)
   SECVERICALL_BACK p_Verifyfunc;      //安全层验签接口回调(可选)
   SENDCALL_BACK p_Sendfunc;           //应用层发送接口回调
   seclayer_status_callback p_Secfunc; //安全层初始化回调(可选)

   /*二期消息集接口*/
   WJV2_UperFromFileEncodeMain_BACK p_WJV2_UperFromFileEncodeMain;
   WJV2_UperEncOrDecMain_BACK p_WJV2_UperEncOrDecMain;
   WJV2_SetGetAIDFromFileCallback p_WJV2_SetGetAIDFromFileCallback;
   /*三跨消息集接口*/
   WJV3_UperFromFileEncodeMain_BACK p_WJV3_UperFromFileEncodeMain;
   WJV3_UperEncOrDecMain_BACK p_WJV3_UperEncOrDecMain;
   WJV3_SetGetAIDFromFileCallback p_WJV3_SetGetAIDFromFileCallback;
   /*四跨消息集接口*/
   WJV4_UperFromFileEncodeMain_BACK p_WJV4_UperFromFileEncodeMain;
   WJV4_UperEncOrDecMain_BACK p_WJV4_UperEncOrDecMain;
   WJV4_SetGetAIDFromFileCallback p_WJV4_SetGetAIDFromFileCallback;
   /*新四跨消息集接口*/
   WJVN4_UperFromFileEncodeMain_BACK p_WJVN4_UperFromFileEncodeMain;
   WJVN4_UperEncOrDecMain_BACK p_WJVN4_UperEncOrDecMain;
   WJVN4_SetGetAIDFromFileCallback p_WJVN4_SetGetAIDFromFileCallback;

   /**
 * 初始化log系统
 *
 * @param log_config_name[in] log配置文件
 *
 * @return int32_t
 *         0:成功;-1:失败，失败后退出整个程序
 */
   int (*WJ_LogInit)(const char *LogConfigPath);
   /**
* @brief 初始化V2X通讯_发送、接收模块
*
* 初始化V2X通讯_接收模块
*
* @param[in] MsgRx_CallBack 接收数据回调函数 @see pFunRecvData
*
* @return  执行状态，0 执行成功，非0 执行失败.
*/
   int (*WJ_V2XTxRxInit)(void (*pFunRecvData)(RecvCallbackReturnInfo));

   /**
 * 安全层初始化
 *
 * @param void
 *
 * @return int32_t 0:成功；-1:失败
 */
   int (*WJ_SecureInit)(seclayer_status_callback cb, void *cb_para, const char *fileName);
} Stack_Init_t;

/**
 * @brief StackInit 协议栈初始化
 *
 * @param[in] Init -- 初始化函数结构体
 *
 * @return 0/-1             成功/失败
 *
 * Example Usage:
 * @code
 * {
 *    Stack_Init_t Init;
 *    memset(&Init, 0x00, sizeof(Init));
 *    strcpy(Init.FileName, "./Config_ProtocolStack.ini");
 *    Init.p_WJV3_SetGetAIDFromFileCallback = SetGetAIDFromFileCallbackV3;
 *    Init.p_WJV3_UperEncOrDecMain = WJV3_UperEncOrDecMain;
 *    Init.p_WJV3_UperFromFileEncodeMain = WJV3_UperFromFileEncodeMain;
 *    Init.p_Sendfunc = SendingCallback;
 *    Init.WJ_LogInit = LogInit;
 *    Init.WJ_V2XRxInit = V2X_Rx_Init;
 *    Init.WJ_V2XTxInit = V2X_Tx_Init;
 *    if(StackInit(&Init)==0)
 *    {
 *       printf("success\n");
 *    }
 * }
 * @endcode
 *
 */
__attribute__((visibility("default"))) int StackInit(Stack_Init_t *Init);

#endif