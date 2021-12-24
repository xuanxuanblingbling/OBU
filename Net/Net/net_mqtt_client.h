/*
 * @Author: your name
 * @Date: 2021-05-09 15:29:36
 * @LastEditTime: 2021-11-15 15:52:14
 * @LastEditors: VanJee Technology Co.,Ltd
 * @Description: In User Settings Edit
 * @FilePath: /V2X/APP/LarScale/LarScale/inc/app_mqtt.h
 */
#ifndef __APP_MQTT_H__
#define __APP_MQTT_H__

#include "mqtt/MQTTClient.h"
#include "mqtt/MQTTAsync.h"
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define MQTT_LOG "net_mqtt_client"
#define OBU_INFO_FILE "/mnt/APP/Config/obu/net/Config_OBUInfo.ini"
//MQTT_ADD
#define MQTT_ADD_CONFIG "/mnt/APP/Config/obu/net/Config_MQTTInfo.ini"
//MQTT的topoic规则
#define TOPIC_DOWN_DATAS "wj/v2x_downlink/"
#define TOPIC_UPLOAD_DATAS "wj/v2x_uplink/" //数据上报
#define MQTT_QOS 2                          //Mqtt服务质量等级
#define IS_OK 0                             //成功
#define IS_ERR 1                            //失败

typedef struct _Mqtt_Connect_Info
{
    char mqtt_addr[128]; //MQTT服务器和端口
    char clientId[123];
    MQTTAsync client; //MQTT客户端句柄
    bool connected;   //MQTT是否连接到服务器
} Mqtt_Connect_Info;

extern Mqtt_Connect_Info mqtt_connect_info;

//MQTT服务初始化
int mqtt_service_init();

//通过MQTT上传数据
int mqtt_upload_datas(uint8_t *data, int len, char *topic);

#endif
