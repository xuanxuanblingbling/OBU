
#include "net_mqtt_client.h"
#include "Config/net_log.h"
#include "Config/file.h"
#include "TongZhou/inc/app_lst.h"

Mqtt_Connect_Info mqtt_connect_info = {{0}, {0}, false};

static int mqtt_connect_server();

static void connlost(void *context, char *cause)
{
    printf("Connection lost cause: %s Reconnecting", cause);
}

static void onDisconnect(void *context, MQTTAsync_successData *response)
{
    printf("Successful disconnection\n");
}
/******************************************************************
 * 函 数 名 称    : onConnectFailure
 * 功 能 描 述    : MQTTAsync_connected连接失败的回调函数
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-26 14:05:34 V1.0     bo_jiang   Create
*=====================================================================*/
static void onConnectFailure(void *context, MQTTAsync_failureData *response)
{
    switch (response->code)
    {
    case 1:
        printf("连接被拒绝：不可接受的协议版本\n");
        break;
    case 2:
        printf("连接被拒绝：标识符被拒绝\n");
        break;
    case 3:
        printf("连接被拒绝：服务器不可用\n");
        break;
    case 4:
        printf("连接被拒绝：用户名或密码错误\n");
        break;
    case 5:
        printf("连接被拒绝：不授权\n");
        break;
    default:
        printf("保留以备将来使用\n");
        break;
    }
}

static void onSubscribe(void *context, MQTTAsync_successData *response)
{
    printf("Subscribe succeeded\n");
}

static void onSubscribeFailure(void *context, MQTTAsync_failureData *response)
{
    printf("Subscribe failed, rc %d\n", response ? response->code : 0);
}
/******************* 链接服务器成功 ************************************************************************
 * 接口： FN_ConnectCallBack(void *p_context, char *p_cause)
 * 描述： 中途与mqtt服务器断开连接处理回调
 * 入参： 1. p_context	 数据类型 void*		 说明：注册时传入的参数，这里传入MQTT客户端结构体指针 
 *	     2. p_cause     数据类型 char*		说明：
 * 出参： 无
 * 返回： 无
 **********************************************************************************************************/

void FN_ConnectCallBack(void *p_context, char *p_cause)
{
    printf("set on connected\n");
    char l_devicesn[64] = {0};
    char self_topic[128] = TOPIC_DOWN_DATAS;
    MQTTAsync client = (MQTTAsync)p_context;
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    opts.onSuccess = onSubscribe;        //订阅成功的回调
    opts.onFailure = onSubscribeFailure; //订阅失败的回调
    opts.context = mqtt_connect_info.client;
    int rc;
    // if (mqtt_connect_info.client != NULL)
    // {
    //     printf("**************************************FN_ConnectCallBack error\n");
    //     MQTTAsync_destroy(&(mqtt_connect_info.client));
    // }
    //获取设备SN号
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "ObuSN", l_devicesn);
    //获取发送的Topic
    strncat(self_topic, l_devicesn, strlen(l_devicesn));
    LogPrint(LOG_LEVEL_DEBUG, MQTT_LOG, "self_topic:%s\n", self_topic);
    if ((rc = MQTTAsync_subscribe(mqtt_connect_info.client, self_topic, MQTT_QOS, &opts)) != MQTTASYNC_SUCCESS)
    {
        printf("Failed  re to start subscribe ALL, return code %d\n", rc);
        exit(-2);
    }
    else
    {
        printf("Subscribe all success\n");
    }
}
/******************************************************************
 * 函 数 名 称    : onSuccess
 * 功 能 描 述    : MQTT连接成功回调函数
 * 输 入 参 数    :  *datas---待上传的数据,  Class--消息的class,  ID--消息的id
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-09 17:11:29 V1.0     bo_jiang   Create
*=====================================================================*/
static void onSuccess(void *context, MQTTAsync_successData *response)
{
    char l_devicesn[64] = {0};
    char self_topic[128] = TOPIC_DOWN_DATAS;
    MQTTAsync client = (MQTTAsync)context;
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    int rc;

    mqtt_connect_info.connected = true;
    LogPrint(LOG_LEVEL_DEBUG, MQTT_LOG, "mqtt_connect_info.connected is %d", mqtt_connect_info.connected);
    LogPrint(LOG_LEVEL_DEBUG, MQTT_LOG, "Successful connection\n");

    opts.onSuccess = onSubscribe;
    opts.onFailure = onSubscribeFailure;
    opts.context = mqtt_connect_info.client;
    //获取设备SN号
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "ObuSN", l_devicesn);
    //获取发送的Topic
    strncat(self_topic, l_devicesn, strlen(l_devicesn));
    LogPrint(LOG_LEVEL_DEBUG, MQTT_LOG, "self_topic:%s\n", self_topic);
    if ((rc = MQTTAsync_subscribe(mqtt_connect_info.client, self_topic, MQTT_QOS, &opts)) != MQTTASYNC_SUCCESS)
    {
        LogPrint(LOG_LEVEL_ERR, MQTT_LOG, "Failed to start subscribe self, return code %d\n", rc);
        exit(-1);
    }
    else
    {
        LogPrint(LOG_LEVEL_DEBUG, MQTT_LOG, "Subscribe self success\n");
    }
}

/******************************************************************
 * 函 数 名 称    : mqtt_msg_recv
 * 功 能 描 述    : 接收到MQTT数据(接收MQTT消息的回调函数)
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-26 13:21:28 V1.0     bo_jiang   Create
*=====================================================================*/
static int mqtt_msg_recv(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    LogPrint(LOG_LEVEL_DEBUG, MQTT_LOG, "Message arrived topic: %s\n", topicName);
    FN_Deal_Mqtt_Recv((uint8_t *)message->payload, (int)message->payloadlen);
    // int32_t i = get_v2xobustate_sequence();

    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}

//连接MQTT服务器
/******************************************************************
 * 函 数 名 称    : mqtt_connect_server
 * 功 能 描 述    : 连接MQTT服务器
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-26 13:21:28 V1.0     bo_jiang   Create
*=====================================================================*/
static int mqtt_connect_server()
{
    int rc;
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer; //通过调用MQTTAync_connectOptions_initializer进行赋初值；
    /*“保持活动”间隔（以秒为单位）定义了客户端和服务器之间没有通信时应该经过的最长时间。客户端将确保在每个保持活动期间内至少有一条消息通过网络。
    如果在该时间段内没有与数据相关的消息，客户端会发送一个非常小的 MQTT“ping”消息，服务器将确认该消息。保持活动间隔使客户端能够检测服务器何时
    不再可用，而无需等待较长的 TCP/IP 超时。如果您不想进行任何保持活动处理，请设置为 0。*/
    conn_opts.keepAliveInterval = 20; //心跳间隔（与服务器保持活动的时间）
    /*这是一个布尔值。cleansession 设置控制客户端和服务器在连接和断开连接时的行为。
    客户端和服务器都维护会话状态信息。此信息用于确保“至少一次”和“恰好一次”传递以及“恰好一次”接收消息。
    会话状态还包括由 MQTT 客户端创建的订阅。您可以选择在会话之间保持或丢弃状态信息。当cleansession 为true 时，
    状态信息在连接和断开连接时被丢弃。将 cleansession 设置为 false 会保留状态信息。当您使用MQTTAsync_connect()连接 
    MQTT 客户端应用程序时，客户端使用客户端标识符和服务器地址来识别连接。服务器检查此客户端的会话信息是否已从先前与服务器
    的连接中保存。如果前一个会话仍然存在，并且cleansession=true，那么客户端和服务器上的前一个会话信息将被清除。
    如果cleansession=false，则恢复先前的会话。如果不存在先前的会话，则开始新的会话。*/
    conn_opts.cleansession = 1; //在connect/disconnect的时候，是否清除上一个连接的seesion状态信息缓存
                                //(重启一个新的)。这个session状态用来确认消息质量保证（至少一次或者只有一次）
    /*如果连接成功完成，则指向要调用的回调函数的指针。可以设置为 NULL，在这种情况下，将不会收到成功完成的指示。
      onSuccess指向连接成功时要调用的回调函数，这个函数内部会有订阅主题的功能（调用MQTTAsync_subscribe订阅主题）*/
    conn_opts.onSuccess = onSuccess; //连接成功的回调函数
    /*如果连接失败，则指向要调用的回调函数的指针。可以设置为 NULL，在这种情况下，不会收到未成功完成的指示。*/
    conn_opts.onFailure = onConnectFailure;       //连接失败的回调函数
    conn_opts.context = mqtt_connect_info.client; //MQTT句柄
    // conn_opts.username = mqtt_token_response.clientId; //用户名
    // conn_opts.password = mqtt_token_response.token;    //密码
    conn_opts.automaticReconnect = 1;                //使能自动重联
    conn_opts.minRetryInterval = 5;                  //最小重试间隔(秒)。 每次失败的重试次数加倍。
    conn_opts.maxRetryInterval = 365 * 24 * 60 * 60; //设设置最大重联时间
    // conn_opts.connectTimeout     = 60;//设置最大重联时间
    while (1)
    {
        rc = MQTTAsync_connect(mqtt_connect_info.client, &conn_opts);
        if (rc == MQTTASYNC_SUCCESS)
        {
            LogPrint(LOG_LEVEL_DEBUG, MQTT_LOG, "Successfully start the request of connect.\n");
            break;
        }
        LogPrint(LOG_LEVEL_ERR, MQTT_LOG, "Failed to start the request of connect, return error code is %d\n", rc);
    }
}

static int mqtt_disconnect_server()
{
    int rc;
    MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
    disc_opts.onSuccess = onDisconnect;
    if ((rc = MQTTAsync_disconnect(mqtt_connect_info.client, &disc_opts)) != MQTTASYNC_SUCCESS)
    {
        printf("Failed to start disconnect, return code %d\n", rc);
        return -1;
    }
    return 0;
}

//MQTT服务线程
static void *mqtt_ps_thread(void *args)
{
    int rc;

    MQTTAsync_create(&mqtt_connect_info.client, mqtt_connect_info.mqtt_addr, mqtt_connect_info.clientId, 1, NULL);

    MQTTAsync_setCallbacks(mqtt_connect_info.client, NULL, connlost, mqtt_msg_recv, NULL);

    mqtt_connect_server();

    pause();

    //断开连接
    mqtt_disconnect_server();
    MQTTAsync_destroy(&mqtt_connect_info.client);

    return NULL;
}

//通过MQTT上传数据
int mqtt_upload_datas(uint8_t *data, int len, char *topic)
{
    if (mqtt_connect_info.connected == false)
    {
        LogPrint(LOG_LEVEL_DEBUG, MQTT_LOG, "mqtt_connect_info.connected is %d", mqtt_connect_info.connected);
        LogPrint(LOG_LEVEL_ERR, MQTT_LOG, "MQTT NOT READY");

        return IS_ERR;
    }
    if ((NULL == data) || (len <= 0))
    {
        LogPrint(LOG_LEVEL_ERR, MQTT_LOG, "MQTT_SEND data is NULL or len is 0");

        return IS_ERR;
    }
    int rc;
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

    opts.context = mqtt_connect_info.client;

    pubmsg.payload = data;
    pubmsg.payloadlen = len;
    pubmsg.qos = MQTT_QOS;
    pubmsg.retained = 0;

    if ((rc = MQTTAsync_sendMessage(mqtt_connect_info.client, topic, &pubmsg, &opts)) != MQTTASYNC_SUCCESS)
    {
        LogPrint(LOG_LEVEL_ERR, MQTT_LOG, "Failed to start sendMessage, return code %d", rc);
        return IS_ERR;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, MQTT_LOG, "send succuss");
        return IS_OK;
    }
}
/******************************************************************
 * 函 数 名 称    : FN_Get_Mqtt_Info
 * 功 能 描 述    : 获取MQTT相关信息
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 15:25:18 V1.0     bo_jiang   Create
*=====================================================================*/
static void FN_Get_Mqtt_Info()
{
    //获取MQTT-ip
    ConfigGetKey(MQTT_ADD_CONFIG, "MQTTInfo", "mqtt_addr", mqtt_connect_info.mqtt_addr);
    LogPrint(LOG_LEVEL_DEBUG, MQTT_LOG, "mqtt_addr is %s", mqtt_connect_info.mqtt_addr);
    //获取Mqtt_clientId
    ConfigGetKey(MQTT_ADD_CONFIG, "MQTTInfo", "mqtt_clientId", mqtt_connect_info.clientId);
    LogPrint(LOG_LEVEL_DEBUG, MQTT_LOG, "mqtt_clientId is %s", mqtt_connect_info.clientId);
}
//MQTT服务初始化
int mqtt_service_init()
{
    //获取MQTT相关信息
    FN_Get_Mqtt_Info();
    pthread_t tid;
    pthread_create(&tid, NULL, mqtt_ps_thread, NULL);
    pthread_detach(tid);
    return 0;
}

// int main(void)
// {
//     int ret = 0;
//     //MQTT服务初始化
//     ret = mqtt_service_init();
//     if (0 != ret)
//     {
//         printf("mqtt_service_init is error!\n");
//     }
//     printf("mqtt_service_init is success!\n");
//     while (1)
//         ;
// }
