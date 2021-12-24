/*
 * @Descripttion: 
 * @version: 
 * @Author: wanji.net.cn
 * @email: mk_wanji@126.com
 * @Date: 2021-12-03 20:16:46
 * @LastEditors: VanJee Technology Co.,Ltd
 * @LastEditTime: 2021-12-03 20:18:43
 */
#ifndef _NET_DATA_HANDLER_H
#define _NET_DATA_HANDLER_H

#include <stdint.h>
#include <string.h>
#include "Net/net_platform_warn_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define maxsize 5000
#define sendstatus 8
#define QueryLen 11U
#define SendLen 57U
#define TestLen 14U
#define Currentbehavior 32U

    typedef enum _CanDataStatus
    { // 默认状态.
        Can_buff0 = 0x00,
        Can_buff1,
        Can_buff2,
        Can_buff3,
        Can_buff4,
        Can_buff5,
        Can_buff6,
        Can_buff7,
        Can_buff8,
    } CanDataStatus;

    uint8_t DBUS_CaluBcc(void *p_ptValue, uint32_t p_length);
    void GetAppMsgData(char p_mainCmd, char p_subCmd, const char *p_data, uint32_t p_len);
    void FN_sFunRecvDatacallback(uint8_t *p_data, uint32_t p_BufSize);
    void GetAppScenMsgData(V2xPlatformSceneWarn v2xplatformscenewarn);

#ifdef __cplusplus
}
#endif

#endif
