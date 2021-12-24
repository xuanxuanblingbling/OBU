/*
 * @Author: your name
 * @Date: 2021-10-23 12:25:57
 * @LastEditTime: 2021-12-06 19:52:17
 * @LastEditors: VanJee Technology Co.,Ltd
 * @Description: In User Settings Edit
 * @FilePath: /protobuf/inc/app_lst.h
 */
/**********************  头文件包含  ********************************/
#include "Dbus/dbus_data_type.h"
int Cloud_Platform_TZ();
#ifdef __cplusplus
extern "C"
{
#endif
    void FN_Deal_Mqtt_Recv(uint8_t *data, int len);
    int CooperativeSendSecMsgData(RoadsideCoordination_t *p_roadsideCoordination);

#ifdef __cplusplus
}

int SendSecMsgData(V2xPlatformSceneWarn v2xplatformscenewarn);

#endif