/**
 * @defgroup V2X_Interface_Com V2X_Interface_Com API
 * @{
 *
 * 本模块提供V2X接入层对外接口及数据结构头文件.
 *
 * @}
 *
 */

/**
 * @defgroup V2X_Interface V2X_Interface API
 * @ingroup V2X_Interface_Com API
 * @{
 *
 * 本模块V2X接入层对外头文件.
 *
 * @file V2XInterface.h
 * @brief API file.
 *
 */

#ifndef V2X_INTERFACE_H_
#define V2X_INTERFACE_H_
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <linux/in6.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <syslog.h>
#include "SendDataInfo.h"
#define MODE_LTEV_AG15 1
#define MODE_LTEV_CX7100 2
#define MODE_LTEV_DMD3A 3

#define DLL_PUBLIC __attribute__((visibility("default")))

/**
 * @brief 发送数据后的返回结构体.
 */
typedef struct _SendDataReturnInfo
{
    float Current_CBR; //当前的CBR测量值
    int sendLen;
} __attribute__((packed)) SendDataReturnInfo;
/**
 * 接收数据处理接口
 */
typedef void (*pFunRecvData)(RecvCallbackReturnInfo);

/**
* @brief V2X_Tx_Init 初始化V2X通讯_发送、接收模块
*
* @param 无
*
* @return  执行状态，0 执行成功，非0 执行失败.
*/
DLL_PUBLIC int V2X_TxRx_Init(pFunRecvData MsgRx_CallBack);

/**
* @brief V2X_SendData 将指定的数据按照当前的发送参数发送出去
*
*
* @param[in] AG15SendDataInfo ag15SendDataInfo 发送数据结构体
* @param[out] ag15SendDataReturnInfo 发送后的返回结构体
*
* @return >0 成功发送数据的长度（字节数） <0 表示发送失败，返回结果代表错误类型
*/
DLL_PUBLIC int V2X_SendData(SendDataInfo ag15SendDataInfo, SendDataReturnInfo *ag15SendDataReturnInfo);

/**
 * @brief 关闭V2X通讯
 *
 * 关闭V2X通讯
 *
 * @param 无
 *
 * @return 执行状态，0 执行成功，非0 执行失败
 */
DLL_PUBLIC int V2X_Close();

/**
 * @brief 实时获取CBR（信道芒率）
 *
 * 实时获取CBR（信道芒率）
 *
 * @param 无
 *
 * @return 执行状态，0 执行成功，非0 执行失败
 */
DLL_PUBLIC float V2X_GetCBR();

#endif /* V2X_INTERFACE_H_ */
