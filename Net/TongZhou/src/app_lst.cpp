/*
 * @Author: your name
 * @Date: 2021-10-23 12:23:53
 * @LastEditTime: 2021-12-17 11:10:26
 * @LastEditors: VanJee Technology Co.,Ltd
 * @Description: In User Settings Edit
 * @FilePath: /protobuf/src/app_lst.c
 */

#include <iostream>
#include <vector>

extern "C"
{
#include "Net/net_platform_warn_type.h"
#include "TongZhou/inc/empty_function.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
}

//OBU自身静态信息（protobuf）初始化
V2xObuBasicInfo V2xobubasicinfo = V2X_OBU_BASIC_INFO__INIT;
//OBU设备实时的状态信息（protobuf）初始化
V2xObuState V2xobustate = V2X_OBU_STATE__INIT;
//OBU 实时上报场景预警事件（protobuf）初始化
V2xSceneWarning V2xseenewarning = V2X_SCENE_WARNING__INIT;
//OBU统计信息周期上报，目前实现上是针对所有的包数（protobuf）初始化
V2xObuStatistics V2xobustatistics = V2X_OBU_STATISTICS__INIT;
//设置和查询配置的响应（protobuf）初始化
V2xObuConfigRsp V2xobuconfigrsp = V2X_OBU_CONFIG_RSP__INIT;
//OBU运行状态信息周期上报（protobuf）初始化
V2xObuRunningStatus V2xoburunningstatus = V2X_OBU_RUNNING_STATUS__INIT;
//场景优先级，目前平台未使用，故填默认值
#define PRIORITY 0
//OBU运行状态信息配置文件
#define DYNAMICINFO_Config_Path "/mnt/APP/Config/obu/sysm/DynamicInfo/DynamicInfo.json"
//OBU基本实时状态信息上报频率，默认1s一次
int ObuSendBasicStateperiodInterval = INTERVAL;
//OBU统计信息上报频率，默认1s一次
int ObuSendStatisticsperiodInterval = INTERVAL * 10;

pthread_mutex_t g_SendFuncMutex = PTHREAD_MUTEX_INITIALIZER;
#define MAX_DUMMY_PACKET_LEN 100
static int ArrayToStr(unsigned char *Buff, unsigned int BuffLen, char *OutputStr)
{
    int i = 0;
    char TempBuff[MAX_DUMMY_PACKET_LEN] = {0};
    char strBuff[MAX_DUMMY_PACKET_LEN] = {0};

    for (i = 0; i < BuffLen; i++)
    {
        sprintf(TempBuff, "%02x", Buff[i]);      //以十六进制格式输出到TempBuff，宽度为2
        strncat(strBuff, TempBuff, BuffLen * 2); //将TempBuff追加到strBuff结尾
    }
    strncpy(OutputStr, strBuff, BuffLen * 2); //将strBuff复制到OutputStr
    return BuffLen * 2;
}
/******************* 获取配置文件json字符串 *****************************************
 * 接口： FN_GetConfigJsonValueof_Char(const char * p_filename)
 * 描述： 获取配置文件的json格式数据，以char *Pvalue,返回需要free
 * 入参： 1. p_filename	 数据类型 const char*		 说明：配置文件名
 *	   
 * 出参： 无
 * 返回： 类型：char* 成功：返回配置文件内容指针 失败：NULL
 *********************************************************************************/
char *FN_GetConfigJsonValueof_Char(const char *p_filename)
{
    if (p_filename != NULL)
    {
        char *gbuf = NULL;
        int fd = open(p_filename, O_RDONLY);
        if (0 > fd)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "FN_GetConfigJsonValueof_Char unable open this config filename:%s ", p_filename);
            return NULL;
        }
        struct stat buf;
        int ret = fstat(fd, &buf);
        if (ret != 0)
        {
            return NULL;
        }
        uint32_t len = buf.st_size;
        gbuf = (char *)malloc((size_t)len + 1);
        if (NULL == gbuf)
        {
            if (0 < fd)
            {
                close(fd);
                fd = -1;
            }
            return gbuf;
        }
        if (read(fd, gbuf, len) <= 0)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "FN_GetConfigJsonValueof_Char read is error");
            if (NULL != gbuf)
                free(gbuf);
            gbuf = NULL;
            if (0 < fd)
            {
                close(fd);
                fd = -1;
            }
            return gbuf;
        }
        /* 校验JSON 格式*/

        cJSON *filejsonArry = cJSON_Parse(gbuf);
        if (filejsonArry == NULL)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "FN_GetConfigJsonValueof_Char check readed char isn't json");
            if (NULL != gbuf)
                free(gbuf);
            gbuf = NULL;
            if (0 < fd)
            {
                close(fd);
                fd = -1;
            }
            return gbuf;
        }
        cJSON_Delete(filejsonArry); //释放cJSON_Parse申请的内存空间
        /* 正常返回值  外面释放 */
        if (0 < fd)
        {
            close(fd);
            fd = -1;
        }
        return gbuf;
    }
    return NULL;
}
/******************************************************************
 * 函 数 名 称    : FN_Qxwz_V2xOBuConfigRsp
 * 功 能 描 述    : 设置和查询配置的响应
 * 输 入 参 数    : ack --确认请求的顺序 ;type--1. 配置回复，2.查询回复 ;result --1.执行失败  2.执行成功 
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang  
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-23 14:32:46 V1.0     bo_jiang   Create
*=====================================================================*/
// static int FN_Qxwz_V2xOBuConfigRsp(uint32_t ack,uint32_t type,uint32_t result)
// {
//     v2xobuconfigrsp.sequence = get_v2xobuconfigrsp_sequence();     //唯一的序列号，用于区分响应
//     v2xobuconfigrsp.timestamp = get_timestamp();   // UTC时间戳，毫秒
//     v2xobuconfigrsp.ack = ack;               //确认请求的顺序
//     v2xobuconfigrsp.type = type;             //1. 配置回复，2.查询回复
//     if(1 == v2xobuconfigrsp.type)
//     {
//         v2xobuconfigrsp.result = result;
//     }
//     else if (2 == v2xobuconfigrsp.type)
//     {

//     }else
//     {

//     }
// }
/******************************************************************
 * 函 数 名 称    : FN_Issue_Congfiguration
 * 功 能 描 述    : 解析下发的配置信息
 * 输 入 参 数    : data --配置内容 len--接收到的数据长度
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang  
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-23 14:32:46 V1.0     bo_jiang   Create
*=====================================================================*/
static int FN_Issue_Congfiguration(char *data, int len)
{
    if (NULL == data)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "FN_Issue_Congfiguration: data invalid");
        return IS_ERR;
    }
    char *CenterAdd = NULL;
    int CenterPort = 0;
    char ConfigSetBuf[128] = {0};
    cJSON *root = cJSON_Parse(data); //将data格式的json数据转化为JSON对象格式
    if (NULL == root)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "cJSON_Parse error!!!");
        return IS_ERR;
    }
    cJSON *Config = cJSON_GetObjectItem(root, "server.conf");
    if (NULL != Config)
    {
        //NLCenterAdd
        cJSON *NLCenterAdd = cJSON_GetObjectItem(Config, "NLCenterAdd");
        if (NULL == NLCenterAdd)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "cJSON_GetObjectItem NLCenterAdd error!!!");
            return IS_ERR;
        }
        LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "NLCenterAdd is %s", NLCenterAdd->valuestring);
        CenterAdd = (char *)calloc(sizeof(NLCenterAdd->valuestring), sizeof(char));
        if (NULL == CenterAdd)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "CenterAdd calloc error!!!");
            return IS_ERR;
        }

        memcpy(CenterAdd, NLCenterAdd->valuestring, sizeof(NLCenterAdd->valuestring));
        cJSON *NLCenterPort = cJSON_GetObjectItem(Config, "NLCenterPort");
        if (NULL == NLCenterPort)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "NLCenterPort calloc error!!!");
            return IS_ERR;
        }
        LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "NLCenterPort is %d", NLCenterPort->valueint);
        CenterPort = NLCenterPort->valueint;
        sprintf(ConfigSetBuf, "%s:%d", CenterAdd, CenterPort);
        ConfigSetKey(MQTT_ADD_CONFIG, "MQTTInfo", "mqtt_addr", ConfigSetBuf);
        if (CenterAdd)
        {
            free(CenterAdd);
            CenterAdd = NULL;
        }
        //设置和查询配置响应

        //断开MQTT连接，使用新的地址进行连接
    }
    else
    {
        Config = cJSON_GetObjectItem(root, "upload.conf");
        if (NULL != Config)
        {
            cJSON *FrameType = cJSON_GetObjectItem(Config, "FrameType");
            if (NULL == FrameType)
            {
                LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "NLCenterPort FrameType error!!!");
                return IS_ERR;
            }
            switch (FrameType->valueint)
            {
            case OBU_SEND_FRAME_TYPE__ObuSendUnknownType:
                LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "OBU_SEND_FRAME_TYPE__ObuSendUnknownType!!!");
                break;
            case OBU_SEND_FRAME_TYPE__ObuSendBasicState:
            {
                cJSON *periodInterval = cJSON_GetObjectItem(Config, "periodInterval");
                if (NULL == periodInterval)
                {
                    LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "NLCenterPort periodInterval error!!!");
                    return IS_ERR;
                }
                //OBU实时状态信息上报频率
                ObuSendBasicStateperiodInterval = periodInterval->valueint;
                LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "ObuSendBasicStateperiodInterval is %dms", ObuSendBasicStateperiodInterval);
            }
            break;
            case OBU_SEND_FRAME_TYPE__ObuSendStatistics:
            {
                cJSON *periodInterval = cJSON_GetObjectItem(Config, "periodInterval");
                if (NULL == periodInterval)
                {
                    LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "NLCenterPort periodInterval error!!!");
                    return IS_ERR;
                }
                //OBU实时状态信息上报频率
                ObuSendStatisticsperiodInterval = periodInterval->valueint;
                LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "ObuSendStatisticsperiodInterval is %dms", ObuSendStatisticsperiodInterval);
            }
            break;
            default:
                LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "FrameType->valueint is %d", FrameType->valueint);
                break;
            }
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "cJSON_GetObjectItem Config error!!!");
            return IS_ERR;
        }
    }
    return IS_OK;
}
/******************************************************************
 * 函 数 名 称    : FN_Deal_Mqtt_Recv
 * 功 能 描 述    : 处理MQTT接收到的数据
 * 输 入 参 数    : data --接收到的数据 len--接收到的数据长度
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang  
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-23 14:32:46 V1.0     bo_jiang   Create
*=====================================================================*/
extern "C"
{
    void FN_Deal_Mqtt_Recv(uint8_t *data, int len)
    {
        if (NULL == data)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "FN_Deal_Mqtt_Recv: data invalid");
            return;
        }
        uint32_t Index = 0;
        uint32_t Sequence = 0;
        uint64_t Timestamp = 0;
        uint32_t Confinglen = 0;
        uint8_t *ObuConfig = NULL;
        if ((data[0] == 0xC0) && (data[1] == 0x06))
        {
            Index = Index + 2;
            Sequence = (*(uint32_t *)(data + Index));
            LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "Sequence is %d", Sequence);
            Index = Index + 4;
            Timestamp = (*(uint64_t *)(data + Index));
            LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "Timestamp is %ld", Timestamp);
            Index = Index + 8;
            Confinglen = len - Index;
            ObuConfig = (uint8_t *)calloc(Confinglen, sizeof(uint8_t));
            if (ObuConfig)
            {
                LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "V2xObuConfig calloc error!!!");
                return;
            }
            memcpy(ObuConfig, data + Index, Confinglen);
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "Class & id is err! calss is %d , id is %d", data[0], data[1]);
            return;
        }

        //配置信息反序列化
        V2xObuConfig *p_V2xObuConfig = v2x_obu_config__unpack(NULL, Confinglen, ObuConfig);

        if (p_V2xObuConfig)
        {
            LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "p_V2xObuConfig->sequence is %d", p_V2xObuConfig->sequence);
            LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "p_V2xObuConfig->timestamp is %ld", p_V2xObuConfig->timestamp);
            //1、下发配置 2、查询配置
            switch (p_V2xObuConfig->type)
            {
            case ISSUE_CONFIGURATION:
                //下发配置
                /*code*/
                FN_Issue_Congfiguration(((p_V2xObuConfig->configcontext)), sizeof(p_V2xObuConfig->configcontext));
                break;
            case INQUIRE_CONFIGURATION:
                //查询配置
                /*code*/
                break;
            default:
                break;
            }
        }

        if (ObuConfig)
        {
            free(ObuConfig);
            ObuConfig = NULL;
        }
        //释放
        v2x_obu_config__free_unpacked(p_V2xObuConfig, NULL);
    }
}
/******************************************************************
 * 函 数 名 称    : get_V2xObuBasicInfo
 * 功 能 描 述    : 获取OBU自身静态信息（上线时上报一次）
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang  
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-23 14:32:46 V1.0     bo_jiang   Create
*=====================================================================*/
static void get_V2xObuBasicInfo()
{
    V2xobubasicinfo.timestamp = get_timestamp();                             //UTC时间戳，毫秒
    V2xobubasicinfo.sequence = get_v2xobubasicinfo_sequence();               //上报序列号
    V2xobubasicinfo.firmwareversion = get_v2xobubasicinfo_firmwareversion(); //固件版本
    V2xobubasicinfo.appversion = get_v2xobubasicinfo_appversion();           //应用程序版本
    V2xobubasicinfo.platenum = get_v2xobubasicinfo_platenum();               //车牌号
    V2xobubasicinfo.devicesn = get_v2xobubasicinfo_devicesn();               //设备SN
    V2xobubasicinfo.vehicletype = get_vehicletype();                         //车辆类型：参考《车辆类型表》1:特殊车辆; 10:普通轿车; 60:紧急车辆; BRT:52; 快速公交:53; 本地公交:54; 校车:55
}
/******************************************************************
 * 函 数 名 称    : get_V2xObuState
 * 功 能 描 述    : OBU设备实时的状态信息（1Hz,实时状态）
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-23 14:34:57 V1.0     bo_jiang   Create
*=====================================================================*/
static void get_V2xObuState()
{
    V2xobustate.timestamp = get_timestamp();                       //UTC时间戳，毫秒
    V2xobustate.sequence = get_v2xobustate_sequence();             //上报序列号
    V2xobustate.id = get_v2xobustate_id();                         //V2X车辆ID
    V2xobustate.latitude = get_v2xobustate_latitude();             //V2X车辆的纬度（单位：度）
    V2xobustate.longitude = get_v2xobustate_longitude();           //V2X车辆的经度（单位：度）
    V2xobustate.elevation = get_v2xobustate_elevation();           //V2X车辆的海拔（单位：米）
    V2xobustate.heading = get_v2xobustate_heading();               //V2X车辆的航向角（单位：度）
    V2xobustate.speed = get_v2xobustate_speed();                   //V2X车辆的速度（单位：m/s）
    V2xobustate.vehicletype = get_v2xobustate_vehicletype();       //V2X车辆的车辆类型
    V2xobustate.laneid = get_v2xobustate_laneid();                 //车辆所属车道ID
    V2xobustate.nodeid = get_v2xobustate_nodeid();                 //车辆所在地图本地节点ID
    V2xobustate.autopilotstate = get_v2xobustate_autopilotstate(); //自动驾驶状态：1：自动驾驶; 2:手动驾驶
    V2xobustate.faultstate = get_v2xobustate_faultstate();         //故障状态。0:无故障；1:有故障
    V2xobustate.gnssstatus = get_v2xobustate_gnssstatus();         //gnss工作状态 0:无效(默认);1:单点定位(E1);2:差分定位(E2);4:差分定位固定解(E4);5:差分定位浮点解(E5)
    V2xobustate.length = get_v2xobustate_length();
    V2xobustate.width = get_v2xobustate_width();
    V2xobustate.height = get_v2xobustate_height();
}

/******************************************************************
 * 函 数 名 称    : get_V2xSceneWarning
 * 功 能 描 述    : OBU 实时上报场景预警事件(场景预警事件消息中包括多种预警类型，
 *                上报时预警事件对应字段可选，根据消息体中的对应事件进行信息填充。)
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-23 14:53:46 V1.0     bo_jiang   Create
*=====================================================================*/
static int get_V2xSceneWarning(V2xPlatformSceneWarn v2xplatformscenewarn)
{
    char OoutPutStr[100] = {0};
    char rvOoutPutStr[100] = {0};
    if (v2xplatformscenewarn.warn.collision_warn.subtype == 0)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "v2xplatformscenewarn.warn.collision_warn.subtype is 0");
        return IS_ERR;
    }
    V2xseenewarning.timestamp = get_timestamp();               //UTC时间戳，毫秒
    V2xseenewarning.sequence = get_v2xseenewarning_sequence(); //上报序列号
    /*************************本车状态信息*****************************/
    int len = ArrayToStr(v2xplatformscenewarn.hv_id, 8, OoutPutStr);
    V2xseenewarning.id = (char *)calloc(len, sizeof(uint8_t));
    memcpy(V2xseenewarning.id, OoutPutStr, len);
    // V2xseenewarning.id = (char *)v2xplatformscenewarn.hv_id; //本车消息ID
    LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "v2xplatformscenewarn.hv_id is %s", v2xplatformscenewarn.hv_id);
    LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, " V2xseenewarning.id %s", V2xseenewarning.id);
    V2xseenewarning.devicesn = get_v2xobubasicinfo_devicesn(); //OBU设备序列号
    V2xseenewarning.hvlatitude = v2xplatformscenewarn.hv_lat;  //本车纬度
    V2xseenewarning.hvlongitude = v2xplatformscenewarn.hv_lon; //本车经度
    V2xseenewarning.hvelevation = v2xplatformscenewarn.hv_ele; //本车海拔
    V2xseenewarning.hvheading = v2xplatformscenewarn.hv_head;  //车头朝向(0°~360°)，正北为 0，顺时针旋转的角度
    LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "v2xplatformscenewarn.hv_speed is %f", v2xplatformscenewarn.hv_speed);
    V2xseenewarning.hvspeed = v2xplatformscenewarn.hv_speed;        //本车速度m/s
    V2xseenewarning.drivestatus = DRIVE_STATUS__DriveStatusUNKNOWN; //手动驾驶或者自动驾驶状态(0:未知  1：自动驾驶  2：手动驾驶)
    /***************************事件预警类型、子类型、优先级等*****************/
    LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "v2xplatformscenewarn.type is %d", v2xplatformscenewarn.type);
    //101：V2V事件，102：红绿灯事件，103：交通事件，104：交通标识
    switch (v2xplatformscenewarn.type)
    {
    case WARNING_TYPE__WarningTypeNone:
        V2xseenewarning.type = WARNING_TYPE__WarningTypeNone;
        break;
    case WARNING_TYPE__WarningTypeV2V:
    {
        //101：V2V事件
        V2xseenewarning.type = WARNING_TYPE__WarningTypeV2V;
        V2xseenewarning.subtype = v2xplatformscenewarn.warn.collision_warn.subtype; //参考V2X事件标识标定说明
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "V2xseenewarning.subtype is %ld", V2xseenewarning.subtype);
        if (V2xseenewarning.subtype == V2xSubWarnType_SLW)
        {
            V2xseenewarning.priority = PRIORITY;
            V2xseenewarning.maxlimitedspeed = v2xplatformscenewarn.warn.collision_warn.max_speed_limit;
            V2xseenewarning.minlimitedspeed = v2xplatformscenewarn.warn.collision_warn.min_speed_limit;
        }
        else
        {
            V2xseenewarning.priority = PRIORITY; //优先级 0-7 ，数字越小，优先级越高
            /***************************V2V 事件与感知事件预警子事件**********************/
            if (RV_Source_BSM == v2xplatformscenewarn.warn.collision_warn.rv_source)
            {
                V2xseenewarning.targettype = TARGET_TYPE__TargetTypeMOTOR;
                int rvlen = ArrayToStr(v2xplatformscenewarn.warn.collision_warn.rv_id, 8, rvOoutPutStr);
                V2xseenewarning.rvobjectid = (char *)calloc(len, sizeof(uint8_t));
                memcpy(V2xseenewarning.rvobjectid, rvOoutPutStr, len);
                // V2xseenewarning.rvobjectid = (char *)v2xplatformscenewarn.warn.collision_warn.rv_id; //V2X事件参与者设备ID, 远车车辆 BSM消息 ID或者 目标监测ID
                LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "v2xplatformscenewarn.warn.collision_warn.rv_id is %s", v2xplatformscenewarn.warn.collision_warn.rv_id);
                LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "V2xseenewarning.rvobjectid is %s", V2xseenewarning.rvobjectid);
                V2xseenewarning.rvlatitude = v2xplatformscenewarn.warn.collision_warn.rv_lat;           // 远车的纬度
                V2xseenewarning.rvlongitude = v2xplatformscenewarn.warn.collision_warn.rv_lon;          // 远车的经度
                V2xseenewarning.rvelevation = v2xplatformscenewarn.warn.collision_warn.rv_ele;          // 远车的海拔
                V2xseenewarning.rvheading = v2xplatformscenewarn.warn.collision_warn.rv_heading;        // 远车的航向角
                V2xseenewarning.rvspeed = v2xplatformscenewarn.warn.collision_warn.rv_speed;            // 远车的速度 m/s
                V2xseenewarning.disttocollision = v2xplatformscenewarn.warn.collision_warn.rv_distance; // 远车距离本车的距离
                V2xseenewarning.timetocollision = v2xplatformscenewarn.warn.collision_warn.rv_ttc;      // 远车的 ttc s
            }
            else if (RV_Source_RSM == v2xplatformscenewarn.warn.collision_warn.rv_source)
            {
                V2xseenewarning.trackid = v2xplatformscenewarn.warn.collision_warn.ptcp_id;
                switch (v2xplatformscenewarn.warn.collision_warn.ptcp_type) //目标类型
                {
                case TARGET_TYPE__TargetTypeUNKNOWN:
                    V2xseenewarning.targettype = TARGET_TYPE__TargetTypeUNKNOWN; //未定义，如果目标未识别，定位为0
                    break;
                case TARGET_TYPE__TargetTypeMOTOR:
                    V2xseenewarning.targettype = TARGET_TYPE__TargetTypeMOTOR; //机动车
                    break;
                case TARGET_TYPE__TargetTypeNON_MOTOR:
                    V2xseenewarning.targettype = TARGET_TYPE__TargetTypeNON_MOTOR; // 非机动车
                    break;
                case TARGET_TYPE__TargetTypePEDESTRIAN:
                    V2xseenewarning.targettype = TARGET_TYPE__TargetTypePEDESTRIAN; //行人
                    break;
                case TARGET_TYPE__TargetTypeRSU:
                    V2xseenewarning.targettype = TARGET_TYPE__TargetTypeRSU; //交通灯
                    break;
                case TARGET_TYPE__TargetTypeTRUCK:
                    V2xseenewarning.targettype = TARGET_TYPE__TargetTypeTRUCK; //卡车
                    break;
                default:
                    break;
                }
                LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "V2xseenewarning.targettype is %s", V2xseenewarning.rvobjectid);
                // v2xseenewarning.vehclass = get_v2xseenewarning_vehclass(); //预警事件类型为V2V时生效,车辆类型 平台没有用
                // v2xseenewarning.platenum = get_v2xseenewarning_platenum(); //预警事件类型为V2V时生效,车牌号 平台没有用
                V2xseenewarning.rvlatitude = v2xplatformscenewarn.warn.collision_warn.rv_lat;           // 远车的纬度
                V2xseenewarning.rvlongitude = v2xplatformscenewarn.warn.collision_warn.rv_lon;          // 远车的经度
                V2xseenewarning.rvelevation = v2xplatformscenewarn.warn.collision_warn.rv_ele;          // 远车的海拔
                V2xseenewarning.rvheading = v2xplatformscenewarn.warn.collision_warn.rv_heading;        // 远车的航向角
                V2xseenewarning.rvspeed = v2xplatformscenewarn.warn.collision_warn.rv_speed;            // 远车的速度 m/s
                V2xseenewarning.disttocollision = v2xplatformscenewarn.warn.collision_warn.rv_distance; // 远车距离本车的距离
                V2xseenewarning.timetocollision = v2xplatformscenewarn.warn.collision_warn.rv_ttc;      // 远车的 ttc s
            }
        }
    }
    break;
    case WARNING_TYPE__WarningTypeSPAT:
    {
        V2xseenewarning.type = WARNING_TYPE__WarningTypeSPAT;
        if (V2xSpatWarnType_SVW == v2xplatformscenewarn.warn.spat_warn.spat_warn)
        {
            V2xseenewarning.subtype = 1;                                                            //参考V2X事件标识标定说明 闯红灯预警
            V2xseenewarning.priority = PRIORITY;                                                    //优先级 0-7 ，数字越小，优先级越高 目前平台没有使用
            V2xseenewarning.regionid = v2xplatformscenewarn.warn.spat_warn.spat_region_id;          //区域号
            V2xseenewarning.intersectionid = v2xplatformscenewarn.warn.spat_warn.spat_intersect_id; //路口号; 区域号路口号用于唯一标识信号机身份
            V2xseenewarning.phaseid = v2xplatformscenewarn.warn.spat_warn.phase_id;                 // 红绿灯相位ID
            // 转向角度,度; 左转:dir>180&&(dir<315); 右转:dir>45&&dir<=180; 直行:其它角度; 调头:-180
            if (1 == v2xplatformscenewarn.warn.spat_warn.phase_state)
            {
                V2xseenewarning.turnangle = 190; //左转
            }
            else if (3 == v2xplatformscenewarn.warn.spat_warn.phase_state)
            {
                V2xseenewarning.turnangle = 90; //右转
            }
            else if (7 == v2xplatformscenewarn.warn.spat_warn.phase_state)
            {
                V2xseenewarning.turnangle = -180; //掉头
            }
            else if (2 == v2xplatformscenewarn.warn.spat_warn.phase_state)
            {
                V2xseenewarning.turnangle = 30; //直行
            }
            else
            {
                /* code */
            }

            V2xseenewarning.lightstate = v2xplatformscenewarn.warn.spat_warn.light_state; //灯色状态 1:绿色; 2:红色; 3:黄色
            V2xseenewarning.timeleft = v2xplatformscenewarn.warn.spat_warn.time_left;     //剩余时间 单位秒
        }
        else if (V2xSpatWarnType_GLOSA == v2xplatformscenewarn.warn.spat_warn.spat_warn)
        {
            V2xseenewarning.subtype = 2;                                                            //参考V2X事件标识标定说明 闯红灯预警
            V2xseenewarning.priority = PRIORITY;                                                    //优先级 0-7 ，数字越小，优先级越高 目前平台没有使用
            V2xseenewarning.regionid = v2xplatformscenewarn.warn.spat_warn.spat_region_id;          //区域号
            V2xseenewarning.intersectionid = v2xplatformscenewarn.warn.spat_warn.spat_intersect_id; //路口号; 区域号路口号用于唯一标识信号机身份
            V2xseenewarning.phaseid = v2xplatformscenewarn.warn.spat_warn.phase_id;                 // 红绿灯相位ID
            // 转向角度,度; 左转:dir>180&&(dir<315); 右转:dir>45&&dir<=180; 直行:其它角度; 调头:-180
            if (1 == v2xplatformscenewarn.warn.spat_warn.phase_state)
            {
                V2xseenewarning.turnangle = 190; //左转
            }
            else if (3 == v2xplatformscenewarn.warn.spat_warn.phase_state)
            {
                V2xseenewarning.turnangle = 90; //右转
            }
            else if (7 == v2xplatformscenewarn.warn.spat_warn.phase_state)
            {
                V2xseenewarning.turnangle = -180; //掉头
            }
            else if (2 == v2xplatformscenewarn.warn.spat_warn.phase_state)
            {
                V2xseenewarning.turnangle = 30; //直行
            }
            else
            {
                V2xseenewarning.turnangle = 0;
            }

            V2xseenewarning.lightstate = v2xplatformscenewarn.warn.spat_warn.light_state;         //灯色状态 1:绿色; 2:红色; 3:黄色
            V2xseenewarning.timeleft = v2xplatformscenewarn.warn.spat_warn.time_left;             //剩余时间 单位秒
            V2xseenewarning.speedguideceil = v2xplatformscenewarn.warn.spat_warn.max_guid_speed;  //绿波车速引导上限
            V2xseenewarning.speedguidefloor = v2xplatformscenewarn.warn.spat_warn.min_guid_speed; //绿波车速引导下限
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "v2xplatformscenewarn.warn.spat_warn.spat_warn is %d", v2xplatformscenewarn.warn.spat_warn.spat_warn);
            return IS_ERR;
        }
    }
    break;
    case WARNING_TYPE__WarningTypeRTES:
        //交通事件
        V2xseenewarning.type = WARNING_TYPE__WarningTypeRTES;
        //交通拥堵
        if (v2xplatformscenewarn.warn.rsi_warn.rsi_type == 707)
        {
            V2xseenewarning.subtype = 9902;
            V2xseenewarning.priority = PRIORITY;                                             //优先级 0-7 ，数字越小，优先级越高 目前平台没有使用
            V2xseenewarning.rsudeviceid = (char *)v2xplatformscenewarn.warn.rsi_warn.rsu_id; //V2I事件时生效 RSU ID
            V2xseenewarning.rvlatitude = v2xplatformscenewarn.warn.rsi_warn.rsu_lat;         //V2I事件时为RSU位置信息  RSU的纬度
            V2xseenewarning.rvlongitude = v2xplatformscenewarn.warn.rsi_warn.rsu_lon;        //V2I事件时为RSU位置信息  RSU的经度
            V2xseenewarning.rvelevation = v2xplatformscenewarn.warn.rsi_warn.rsu_ele;        //V2I事件时为RSU位置信息  RSU的海拔
            V2xseenewarning.rvheading = 0;                                                   //V2I事件时为RSU位置信息  RSU的航向角
            V2xseenewarning.rvspeed = 0;                                                     //V2I事件时为RSU位置信息  RSU的速度

            V2xseenewarning.level = TRAFFIC_JAM_WARNING_LEVEL__NoTrafficJam;                   //拥堵等级
            V2xseenewarning.startlatitude = v2xplatformscenewarn.warn.rsi_warn.rsi_start_lat;  //拥堵起点经度(靠近车辆行驶方向),degree
            V2xseenewarning.startlongitude = v2xplatformscenewarn.warn.rsi_warn.rsi_start_lon; //拥堵起点纬度(靠近车辆行驶方向),degree
            V2xseenewarning.endlatitude = v2xplatformscenewarn.warn.rsi_warn.rsi_end_lat;      // 拥堵终点经度,degree
            V2xseenewarning.endlongitude = v2xplatformscenewarn.warn.rsi_warn.rsi_end_lon;     //拥堵终点维度,degree
        }
        // else if (v2xplatformscenewarn.warn.rsi_warn.rsi_type == 101) //车辆故障
        // {
        // }

        break;
    case WARNING_TYPE__WarningTypeRTSS:
        //交通标志
        V2xseenewarning.type = WARNING_TYPE__WarningTypeRTSS;
        //前方牲畜
        if (v2xplatformscenewarn.warn.rsi_warn.rsi_type == 12)
        {
            V2xseenewarning.subtype = 12;                                                    //注意牲畜
            V2xseenewarning.priority = PRIORITY;                                             //优先级 0-7 ，数字越小，优先级越高 目前平台没有使用
            V2xseenewarning.rsudeviceid = (char *)v2xplatformscenewarn.warn.rsi_warn.rsu_id; //V2I事件时生效 RSU ID
            V2xseenewarning.rvlatitude = v2xplatformscenewarn.warn.rsi_warn.rsu_lat;         //V2I事件时为RSU位置信息  RSU的纬度
            V2xseenewarning.rvlongitude = v2xplatformscenewarn.warn.rsi_warn.rsu_lon;        //V2I事件时为RSU位置信息  RSU的经度
            V2xseenewarning.rvelevation = v2xplatformscenewarn.warn.rsi_warn.rsu_ele;        //V2I事件时为RSU位置信息  RSU的海拔
            V2xseenewarning.rvheading = 0;                                                   //V2I事件时为RSU位置信息  RSU的航向角
            V2xseenewarning.rvspeed = 0;                                                     //V2I事件时为RSU位置信息  RSU的速度
        }
        break;
    default:
        break;
    }
    return IS_OK;
}
/******************************************************************
 * 函 数 名 称    : get_V2xCooperativeSceneWarning
 * 功 能 描 述    : OBU 实时上报协作时匝道汇入场景预警事件(场景预警事件消息中包括多种预警类型，
 *                上报时预警事件对应字段可选，根据消息体中的对应事件进行信息填充。)
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-23 14:53:46 V1.0     bo_jiang   Create
*=====================================================================*/
static int get_V2xCooperativeSceneWarning(RoadsideCoordination_t *p_roadsideCoordination)
{
    V2xseenewarning.timestamp = get_timestamp();               //UTC时间戳，毫秒
    V2xseenewarning.sequence = get_v2xseenewarning_sequence(); //上报序列号
    /*************************本车状态信息*****************************/
    V2xseenewarning.id = (char *)p_roadsideCoordination->hv_id; //本车消息ID
    V2xseenewarning.devicesn = get_v2xobubasicinfo_devicesn();  //OBU设备序列号
    // V2xseenewarning.hvlatitude = p_roadsideCoordination->hv_lat;    //本车纬度
    // V2xseenewarning.hvlongitude = p_roadsideCoordination->hv_lon;   //本车经度
    // V2xseenewarning.hvelevation = p_roadsideCoordination->hv_ele;   //本车海拔
    // V2xseenewarning.hvheading = p_roadsideCoordination->hv_head;    //车头朝向(0°~360°)，正北为 0，顺时针旋转的角度
    // V2xseenewarning.hvspeed = p_roadsideCoordination->hv_speed;     //本车速度m/s
    V2xseenewarning.drivestatus = DRIVE_STATUS__DriveStatusUNKNOWN; //手动驾驶或者自动驾驶状态(0:未知  1：自动驾驶  2：手动驾驶)
    /***************************事件预警类型、子类型、优先级等*****************/
    //103：V2V事件
    V2xseenewarning.type = WARNING_TYPE__WarningTypeRTES;
    V2xseenewarning.subtype = 9921; //参考V2X事件标识标定说明

    V2xseenewarning.priority = PRIORITY;                                                    //优先级 0-7 ，数字越小，优先级越高 目前平台没有使用
    V2xseenewarning.rsudeviceid = (char *)p_roadsideCoordination->bootDeviceId;             //V2I事件时生效 RSU ID
    V2xseenewarning.rvlatitude = (double)p_roadsideCoordination->bootDeviceLat / 10000000;  //V2I事件时为RSU位置信息  RSU的纬度
    V2xseenewarning.rvlongitude = (double)p_roadsideCoordination->bootDeviceLng / 10000000; //V2I事件时为RSU位置信息  RSU的经度
    V2xseenewarning.rvelevation = 0;                                                        //V2I事件时为RSU位置信息  RSU的海拔
    V2xseenewarning.rvheading = 0;                                                          //V2I事件时为RSU位置信息  RSU的航向角
    V2xseenewarning.rvspeed = 0;                                                            //V2I事件时为RSU位置信息  RSU的速度
    //驾驶建议
    switch (p_roadsideCoordination->driving_advice)
    {
    case 1:
        //直行
        V2xseenewarning.description = (char *)calloc(1, sizeof("直行"));
        memcpy(V2xseenewarning.description, "直行", sizeof("直行"));
        break;
    case 2:
        //变道至左侧
        V2xseenewarning.description = (char *)calloc(1, sizeof("变道至左侧"));
        memcpy(V2xseenewarning.description, "变道至左侧", sizeof("变道至左侧"));
        break;
    case 4:
        //变道至右侧
        V2xseenewarning.description = (char *)calloc(1, sizeof("变道至右侧"));
        memcpy(V2xseenewarning.description, "变道至右侧", sizeof("变道至右侧"));
        break;
    case 8:
        //汇入
        V2xseenewarning.description = (char *)calloc(1, sizeof("汇入"));
        memcpy(V2xseenewarning.description, "汇入", sizeof("汇入"));
        break;
    case 16:
        //汇出
        V2xseenewarning.description = (char *)calloc(1, sizeof("汇出"));
        memcpy(V2xseenewarning.description, "汇出", sizeof("汇出"));
        break;
    case 32:
        //交叉路由直行
        V2xseenewarning.description = (char *)calloc(1, sizeof("交叉路由直行"));
        memcpy(V2xseenewarning.description, "交叉路由直行", sizeof("交叉路由直行"));
        break;
    case 64:
        //交叉路由左转
        V2xseenewarning.description = (char *)calloc(1, sizeof("交叉路由左转"));
        memcpy(V2xseenewarning.description, "交叉路由左转", sizeof("交叉路由左转"));
        break;
    case 128:
        //交叉路由右转
        V2xseenewarning.description = (char *)calloc(1, sizeof("交叉路由右转"));
        memcpy(V2xseenewarning.description, "交叉路由右转", sizeof("交叉路由右转"));
        break;
    case 256:
        //交叉路口U型掉头
        V2xseenewarning.description = (char *)calloc(1, sizeof("交叉路口U型掉头"));
        memcpy(V2xseenewarning.description, "交叉路口U型掉头", sizeof("交叉路口U型掉头"));
        break;
    case 512:
        //启动
        V2xseenewarning.description = (char *)calloc(1, sizeof("启动"));
        memcpy(V2xseenewarning.description, "启动", sizeof("启动"));
        break;
    case 1024:
        //停止
        V2xseenewarning.description = (char *)calloc(1, sizeof("停止"));
        memcpy(V2xseenewarning.description, "停止", sizeof("停止"));
        break;
    case 2048:
        //减速
        V2xseenewarning.description = (char *)calloc(1, sizeof("减速"));
        memcpy(V2xseenewarning.description, "减速", sizeof("减速"));
        break;
    case 4096:
        //加速
        V2xseenewarning.description = (char *)calloc(1, sizeof("加速"));
        memcpy(V2xseenewarning.description, "加速", sizeof("加速"));
        break;
    case 8192:
        //泊车
        V2xseenewarning.description = (char *)calloc(1, sizeof("泊车"));
        memcpy(V2xseenewarning.description, "泊车", sizeof("泊车"));
        break;
    default:
        break;
    }
}

/******************************************************************
 * 函 数 名 称    : 
 * 功 能 描 述    : OBU统计信息周期上报，目前实现上是针对所有的包数
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-23 15:54:35 V1.0     bo_jiang   Create
*=====================================================================*/
static void get_V2xObuStatistics(TModule_V2XStack_Cycle *pParam)
{
    if (NULL == pParam)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "FS_Module_V2XStack_Cycle_Proc: params invalid");
    }
    TModule_V2XStack_Cycle *l_tV2XStack_Cycle = pParam;
    V2xobustatistics.timestamp = get_timestamp();                                            // UTC时间戳，毫秒
    V2xobustatistics.sequence = get_v2xobustatistics_sequence();                             //唯一的序列号，用于区分响应
    V2xobustatistics.sendtotalbyte = (uint32_t)l_tV2XStack_Cycle->m_u64MsglayerTxDatabyte;   //发送的总的字节数   //uint32
    V2xobustatistics.sendtotalpak = (uint32_t)l_tV2XStack_Cycle->m_u64MsglayerTxDataNum;     //发送的总包数
    V2xobustatistics.sendsuccessbyte = (uint32_t)l_tV2XStack_Cycle->m_u64PC5TxDatabyte;      //发送成功的字节数
    V2xobustatistics.sengsuccesspak = (uint32_t)l_tV2XStack_Cycle->m_u64PC5TxDatapak;        //发送成功的包数
    V2xobustatistics.recvtotalbyte = (uint32_t)l_tV2XStack_Cycle->m_u64PC5RxDatabyte;        //收到数据总字节数
    V2xobustatistics.recvtotalpak = (uint32_t)l_tV2XStack_Cycle->m_u64PC5RxDatapak;          //收到总包数
    V2xobustatistics.recvsuccessbyte = (uint32_t)l_tV2XStack_Cycle->m_u64MsglayerRxDatabyte; //成功收到的数据字节数
    V2xobustatistics.recvsuccesspak = (uint32_t)l_tV2XStack_Cycle->m_u64MsglayerRxDataNum;   //成功收到的总包数
}
/******************************************************************
 * 函 数 名 称    : get_V2xObuConfigRsp
 * 功 能 描 述    : 设置和查询配置的响应
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-23 16:03:17 V1.0     bo_jiang   Create
*=====================================================================*/
// static void get_V2xObuConfigRsp()
// {
//     v2xobuconfigrsp.sequence = get_v2xobuconfigrsp_sequence();     //唯一的序列号，用于区分响应
//     v2xobuconfigrsp.timestamp = get_timestamp();                   // UTC时间戳，毫秒
//     v2xobuconfigrsp.ack = get_v2xobuconfigrsp_ack();               //确认请求的顺序
//     v2xobuconfigrsp.type = get_v2xobuconfigrsp_type();             //1. 配置回复，2.查询回复
//     v2xobuconfigrsp.result = get_v2xobuconfigrsp_result();         //1.执行失败  2.执行成功
//     v2xobuconfigrsp.rspcontent = get_v2xobuconfigrsp_rspcontent(); //查询回复有此字段，例如{”server.conf”:{"NLCenterAdd":"data.nebula- link.com"}}
// }

/******************************************************************
 * 函 数 名 称    : Qxwz_V2xObuConfigRsp_send_data
 * 功 能 描 述    : 设置和查询配置的响应数据上传
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-10-23 16:10:56 V1.0     bo_jiang   Create
*=====================================================================*/
// void Qxwz_V2xObuConfigRsp_send_data(void)
// {
//     uint8_t *mqtt_send_buf = NULL; //MQTT上传的数据指针
//     int mqtt_send_len = 0;         //MQTT上传的数据长度
//     //获取设置和查询配置的响应数据
//     get_V2xObuConfigRsp();
//     //打包设置和查询配置的响应数据
//     uint8_t v2xobuconfigrsp_len = v2x_obu_config_rsp__get_packed_size(&v2xobuconfigrsp);
//     v2x_obu_config_rsp__pack_to_buffer();
// }
/******************************************************************
 * 函 数 名 称    : FS_CycleSupervisionProc
 * 功 能 描 述    : 周期性监控消息处理
 * 输 入 参 数    : p_ptMsgQue   待处理的消息体
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-09 17:14:17 V1.0     bo_jiang   Create
*=====================================================================*/
int FS_CycleSupervisionProc(TCycleSupervisonMsgQue *p_ptMsgQue)
{
    if (NULL == p_ptMsgQue)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "FS_CycleSupervisionProc: params invalid");
        return 1;
    }

    TModuleCycleStatusList l_tModuleStatus = p_ptMsgQue->m_tModuleCycleStatusList;

    switch (l_tModuleStatus.m_enumModuleType)
    {
    case MODULE_NETCOMM: // 网络通信模块周期性状态

        break;
    case MODULE_V2XSTACK: // V2X协议栈模块周期性状态
        get_V2xObuStatistics(&l_tModuleStatus.ModuleStatus.m_tV2XStackCycleStatus);
        break;
    case MODULE_GNSSLOCATION: // GNSS定位模块周期性状态

        break;
    case MODULE_DATABASE: // DB数据库模块周期性状态  预留函数接口

        break;
    default:
        break;
    }

    return 0;
}
/******************************************************************
 * 函 数 名 称    : pack_into_data
 * 功 能 描 述    : 数据组包上传MQTT服务器
 * 输 入 参 数    :  *datas---待上传的数据,  Class--消息的class,  ID--消息的id
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-09 17:11:29 V1.0     bo_jiang   Create
*=====================================================================*/
static int pack_into_data_V2xobustate(uint8_t *datas, uint32_t len, uint8_t Class, uint8_t ID)
{
    // pthread_mutex_lock(&g_SendFuncMutex);
    uint8_t *buf = datas;
    char self_topic[128] = TOPIC_UPLOAD_DATAS;

    std::vector<char> l_vdata;
    char l_devicesn[64] = {0};
    static uint32_t m_u32Sequence;
    uint64_t m_u64Timestamp = 0;
    int ret = 0;

    l_vdata.emplace_back(Class);
    l_vdata.emplace_back(ID);
    m_u32Sequence = m_u32Sequence & 0xFFFFFFFF;
    l_vdata.insert(l_vdata.end(), &m_u32Sequence, &m_u32Sequence + sizeof(m_u32Sequence));
    m_u32Sequence++;
    m_u64Timestamp = get_timestamp();
    l_vdata.insert(l_vdata.end(), &m_u64Timestamp, &m_u64Timestamp + sizeof(m_u64Timestamp));
    l_vdata.insert(l_vdata.end(), datas, datas + len);

    // for (int i = 0; i < len; i++)
    // {
    //     printf("%02x", datas[i]);
    // }
    // printf("\n");
    //获取设备SN号
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "ObuSN", l_devicesn);
    //获取发送的Topic
    strncat(self_topic, l_devicesn, strlen(l_devicesn));
    //发送到MQTT
    ret = mqtt_upload_datas((uint8_t *)(&l_vdata[0]), l_vdata.size() * sizeof(l_vdata[0]), self_topic);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "MQTT SEND ERROR!!!");
        return IS_ERR;
    }
    else
    {
        // LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "l_vdata is %s");
        LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "MQTT SEND SUCCESS!!!");
        return IS_OK;
    }
    // pthread_mutex_unlock(&g_SendFuncMutex);
}
static int pack_into_data_V2xObuBasicInfo(uint8_t *datas, uint32_t len, uint8_t Class, uint8_t ID)
{
    // pthread_mutex_lock(&g_SendFuncMutex);
    uint8_t *buf = datas;
    char self_topic[128] = TOPIC_UPLOAD_DATAS;

    std::vector<char> l_vdata;
    char l_devicesn[64] = {0};
    static uint32_t m_u32Sequence;
    uint64_t m_u64Timestamp = 0;
    int ret = 0;

    l_vdata.emplace_back(Class);
    l_vdata.emplace_back(ID);
    m_u32Sequence = m_u32Sequence & 0xFFFFFFFF;
    l_vdata.insert(l_vdata.end(), &m_u32Sequence, &m_u32Sequence + sizeof(m_u32Sequence));
    m_u32Sequence++;
    m_u64Timestamp = get_timestamp();
    l_vdata.insert(l_vdata.end(), &m_u64Timestamp, &m_u64Timestamp + sizeof(m_u64Timestamp));
    l_vdata.insert(l_vdata.end(), datas, datas + len);

    // for (int i = 0; i < len; i++)
    // {
    //     printf("%02x", datas[i]);
    // }
    // printf("\n");
    //获取设备SN号
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "ObuSN", l_devicesn);
    //获取发送的Topic
    strncat(self_topic, l_devicesn, strlen(l_devicesn));
    //发送到MQTT
    ret = mqtt_upload_datas((uint8_t *)(&l_vdata[0]), l_vdata.size() * sizeof(l_vdata[0]), self_topic);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "MQTT SEND ERROR!!!");
        return IS_ERR;
    }
    else
    {
        // LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "l_vdata is %s");
        LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "MQTT SEND SUCCESS!!!");
        return IS_OK;
    }
    // pthread_mutex_unlock(&g_SendFuncMutex);
}
static int pack_into_data_V2xObuStatistics(uint8_t *datas, uint32_t len, uint8_t Class, uint8_t ID)
{
    // pthread_mutex_lock(&g_SendFuncMutex);
    uint8_t *buf = datas;
    char self_topic[128] = TOPIC_UPLOAD_DATAS;

    std::vector<char> l_vdata;
    char l_devicesn[64] = {0};
    static uint32_t m_u32Sequence;
    uint64_t m_u64Timestamp = 0;
    int ret = 0;

    l_vdata.emplace_back(Class);
    l_vdata.emplace_back(ID);
    m_u32Sequence = m_u32Sequence & 0xFFFFFFFF;
    l_vdata.insert(l_vdata.end(), &m_u32Sequence, &m_u32Sequence + sizeof(m_u32Sequence));
    m_u32Sequence++;
    m_u64Timestamp = get_timestamp();
    l_vdata.insert(l_vdata.end(), &m_u64Timestamp, &m_u64Timestamp + sizeof(m_u64Timestamp));
    l_vdata.insert(l_vdata.end(), datas, datas + len);

    // for (int i = 0; i < len; i++)
    // {
    //     printf("%02x", datas[i]);
    // }
    // printf("\n");
    //获取设备SN号
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "ObuSN", l_devicesn);
    //获取发送的Topic
    strncat(self_topic, l_devicesn, strlen(l_devicesn));
    //发送到MQTT
    ret = mqtt_upload_datas((uint8_t *)(&l_vdata[0]), l_vdata.size() * sizeof(l_vdata[0]), self_topic);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "MQTT SEND ERROR!!!");
        return IS_ERR;
    }
    else
    {
        // LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "l_vdata is %s");
        LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "MQTT SEND SUCCESS!!!");
        return IS_OK;
    }
    // pthread_mutex_unlock(&g_SendFuncMutex);
}
static int pack_into_data_CooperativeSendSecMsgData(uint8_t *datas, uint32_t len, uint8_t Class, uint8_t ID)
{
    // pthread_mutex_lock(&g_SendFuncMutex);
    uint8_t *buf = datas;
    char self_topic[128] = TOPIC_UPLOAD_DATAS;

    std::vector<char> l_vdata;
    char l_devicesn[64] = {0};
    static uint32_t m_u32Sequence;
    uint64_t m_u64Timestamp = 0;
    int ret = 0;

    l_vdata.emplace_back(Class);
    l_vdata.emplace_back(ID);
    m_u32Sequence = m_u32Sequence & 0xFFFFFFFF;
    l_vdata.insert(l_vdata.end(), &m_u32Sequence, &m_u32Sequence + sizeof(m_u32Sequence));
    m_u32Sequence++;
    m_u64Timestamp = get_timestamp();
    l_vdata.insert(l_vdata.end(), &m_u64Timestamp, &m_u64Timestamp + sizeof(m_u64Timestamp));
    l_vdata.insert(l_vdata.end(), datas, datas + len);

    // for (int i = 0; i < len; i++)
    // {
    //     printf("%02x", datas[i]);
    // }
    // printf("\n");
    //获取设备SN号
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "ObuSN", l_devicesn);
    //获取发送的Topic
    strncat(self_topic, l_devicesn, strlen(l_devicesn));
    //发送到MQTT
    ret = mqtt_upload_datas((uint8_t *)(&l_vdata[0]), l_vdata.size() * sizeof(l_vdata[0]), self_topic);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "MQTT SEND ERROR!!!");
        return IS_ERR;
    }
    else
    {
        // LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "l_vdata is %s");
        LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "MQTT SEND SUCCESS!!!");
        return IS_OK;
    }
    // pthread_mutex_unlock(&g_SendFuncMutex);
}
static int pack_into_data_V2xSceneWarning(uint8_t *datas, uint32_t len, uint8_t Class, uint8_t ID)
{
    // pthread_mutex_lock(&g_SendFuncMutex);
    uint8_t *buf = datas;
    char self_topic[128] = TOPIC_UPLOAD_DATAS;

    std::vector<char> l_vdata;
    char l_devicesn[64] = {0};
    static uint32_t m_u32Sequence;
    uint64_t m_u64Timestamp = 0;
    int ret = 0;

    l_vdata.emplace_back(Class);
    l_vdata.emplace_back(ID);
    m_u32Sequence = m_u32Sequence & 0xFFFFFFFF;
    l_vdata.insert(l_vdata.end(), &m_u32Sequence, &m_u32Sequence + sizeof(m_u32Sequence));
    m_u32Sequence++;
    m_u64Timestamp = get_timestamp();
    l_vdata.insert(l_vdata.end(), &m_u64Timestamp, &m_u64Timestamp + sizeof(m_u64Timestamp));
    l_vdata.insert(l_vdata.end(), datas, datas + len);

    // for (int i = 0; i < len; i++)
    // {
    //     printf("%02x", datas[i]);
    // }
    // printf("\n");
    //获取设备SN号
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "ObuSN", l_devicesn);
    //获取发送的Topic
    strncat(self_topic, l_devicesn, strlen(l_devicesn));
    //发送到MQTT
    ret = mqtt_upload_datas((uint8_t *)(&l_vdata[0]), l_vdata.size() * sizeof(l_vdata[0]), self_topic);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "MQTT SEND ERROR!!!");
        return IS_ERR;
    }
    else
    {
        // LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "l_vdata is %s");
        LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "MQTT SEND SUCCESS!!!");
        return IS_OK;
    }
    // pthread_mutex_unlock(&g_SendFuncMutex);
}

static int pack_into_data(uint8_t *datas, uint32_t len, uint8_t Class, uint8_t ID)
{
    // pthread_mutex_lock(&g_SendFuncMutex);
    uint8_t *buf = datas;
    char self_topic[128] = TOPIC_UPLOAD_DATAS;

    std::vector<char> l_vdata;
    char l_devicesn[64] = {0};
    static uint32_t m_u32Sequence;
    uint64_t m_u64Timestamp = 0;
    int ret = 0;

    l_vdata.emplace_back(Class);
    l_vdata.emplace_back(ID);
    m_u32Sequence = m_u32Sequence & 0xFFFFFFFF;
    l_vdata.insert(l_vdata.end(), &m_u32Sequence, &m_u32Sequence + sizeof(m_u32Sequence));
    m_u32Sequence++;
    m_u64Timestamp = get_timestamp();
    l_vdata.insert(l_vdata.end(), &m_u64Timestamp, &m_u64Timestamp + sizeof(m_u64Timestamp));
    l_vdata.insert(l_vdata.end(), datas, datas + len);

    // for (int i = 0; i < len; i++)
    // {
    //     printf("%02x", datas[i]);
    // }
    // printf("\n");
    //获取设备SN号
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "ObuSN", l_devicesn);
    //获取发送的Topic
    strncat(self_topic, l_devicesn, strlen(l_devicesn));
    //发送到MQTT
    ret = mqtt_upload_datas((uint8_t *)(&l_vdata[0]), l_vdata.size() * sizeof(l_vdata[0]), self_topic);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "MQTT SEND ERROR!!!");
        return IS_ERR;
    }
    else
    {
        // LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "l_vdata is %s");
        LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "MQTT SEND SUCCESS!!!");
        return IS_OK;
    }
    // pthread_mutex_unlock(&g_SendFuncMutex);
}
/******************************************************************
 * 函 数 名 称    : FN_Qxwz_V2xObuBasicInfo
 * 功 能 描 述    : OBU上报自身静态信息，上线时上报一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-09 17:11:29 V1.0     bo_jiang   Create
*=====================================================================*/
static int FN_Qxwz_V2xObuBasicInfo()
{
    int ret = 0;
    uint8_t *buf = NULL;
    int len = 0;
    //获取OBU自身静态信息
    get_V2xObuBasicInfo();
    //序列化
    len = v2x_obu_basic_info__get_packed_size(&V2xobubasicinfo);
    buf = (uint8_t *)malloc(len);
    if (buf == NULL)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "V2xObuBasicInfo malloc error!");
        return IS_ERR;
    }
    //打包主结构
    v2x_obu_basic_info__pack(&V2xobubasicinfo, buf);
    while (1)
    {
        ret = pack_into_data_V2xObuBasicInfo(buf, len, 0x90, 0x05);
        if (ret)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "pack_into_data_v2xobubasicinfo error!");
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "pack_into_data_v2xobubasicinfo success!");
            break;
        }
        usleep(1000 * 1000);
    }

    //内存释放

    FREE_CONSTANT(V2xobubasicinfo.firmwareversion);
    FREE_CONSTANT(V2xobubasicinfo.appversion);
    FREE_CONSTANT(V2xobubasicinfo.platenum);
    FREE_CONSTANT(V2xobubasicinfo.devicesn);
    FREE_CONSTANT(buf);
    return IS_OK;
}
/******************************************************************
 * 函 数 名 称    : Thread_Qxwz_Qxwz_V2xObuStatistics
 * 功 能 描 述    : OBU统计信息周期上报线程
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-09 17:11:29 V1.0     bo_jiang   Create
*=====================================================================*/
static void *Thread_Qxwz_Qxwz_V2xObuStatistics(void *arg)
{
    int l_n32Ret = 0;
    key_t l_n32KeyId = 0;
    int l_n32MsgId = 0;
    TCycleSupervisonMsgQue l_tCycleSupervisionMsgQue;

    memset(&l_tCycleSupervisionMsgQue, 0, sizeof(TCycleSupervisonMsgQue));
    // 打开或创建消息队列
    l_n32KeyId = ftok(NAT_FTOK_PATH, NAT_FTOK_ID);
    if (l_n32KeyId < 0)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "ftok return err, KeyId = %d", l_n32KeyId);
        perror("<Supervision> ftok return err");
        pthread_exit(NULL);
    }
    l_n32MsgId = msgget(l_n32KeyId, IPC_CREAT | 0666);
    if (l_n32MsgId < 0)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "msgget return err, MsgId=%d", l_n32MsgId);
        perror("<Supervision> msgget return err");
        pthread_exit(NULL);
    }
    while (1)
    {
        // MSG3：运行时监控消息
        l_n32Ret = msgrcv(l_n32MsgId, (void *)&l_tCycleSupervisionMsgQue,
                          (sizeof(l_tCycleSupervisionMsgQue) - sizeof(long)), QUEMSG_REGISTER, IPC_NOWAIT);
        if (l_n32Ret > 0)
        {
            LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "Recv Runtime_Supervision msg from Module_%d", l_tCycleSupervisionMsgQue.m_tModuleCycleStatusList.m_enumModuleType);
            FS_CycleSupervisionProc(&l_tCycleSupervisionMsgQue);
            //序列化
            uint8_t *buf = NULL;
            int len = 0;
            len = v2x_obu_statistics__get_packed_size(&V2xobustatistics);
            buf = (uint8_t *)malloc(len);
            if (buf == NULL)
            {
                LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "V2xObuState buf calloc err!!!");
                FREE_CONSTANT(buf);
                continue;
                // return;
            }
            //打包主结构
            v2x_obu_statistics__pack(&V2xobustatistics, buf);
            pack_into_data(buf, len, 0xC1, 0x06);
            // pack_into_data_V2xObuStatistics(buf, len, 0xC1, 0x06);
            //内存释放

            FREE_CONSTANT(buf);
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "Recv Runtime_Supervision msg from Module is err!!!");
        }
        usleep(ObuSendStatisticsperiodInterval * 1000);
    }
}
/*OBU实时状态，每秒一次*/
/******************************************************************
 * 函 数 名 称    : Thread_Qxwz_V2xObuState
 * 功 能 描 述    : OBU实时状态上报线程，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-09 17:12:05 V1.0     bo_jiang   Create
*=====================================================================*/
static void *Thread_Qxwz_V2xObuState(void *arg)
{
    int ret = 0;
    while (1)
    {
        //获取OBU实时状态数据进行组包
        get_V2xObuState();
        // if (V2xobustate.latitude == 0)
        // {
        //     LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "V2xobustate err!!!");
        //     continue;
        // }
        // LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "V2xobustate.sequence  is %d!!!", V2xobustate.sequence);
        //序列化
        uint8_t *buf = NULL;
        int len = 0;
        len = v2x_obu_state__get_packed_size(&V2xobustate);
        buf = (uint8_t *)malloc(len);
        if (buf == NULL)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "V2xObuState buf calloc err!!!");
            FREE_CONSTANT(V2xobustate.id);
            FREE_CONSTANT(buf);
            continue;
            // return;
        }

        //打包主结构
        v2x_obu_state__pack(&V2xobustate, buf);

        ret = pack_into_data(buf, len, 0x90, 0x06);
        // ret = pack_into_data_V2xobustate(buf, len, 0x90, 0x06);
        // mqtt_upload_datas(buf, len, TOPIC_UPLOAD_DATAS);

        if (ret)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "pack_into_data_V2xObuState error!V2xobustate.sequence  is %d", V2xobustate.sequence);
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "pack_into_data_V2xObuState success V2xobustate.sequence  is %d", V2xobustate.sequence);
        }

        //内存释放
        FREE_CONSTANT(V2xobustate.id);
        FREE_CONSTANT(buf);

        usleep(100 * 1000);
    }
}

/******************************************************************
 * 函 数 名 称    : FN_InitConfigStruct
 * 功 能 描 述    : OBU运行状态信息获取
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-09 17:12:05 V1.0     bo_jiang   Create
*=====================================================================*/
int FN_InitConfigStruct(const char *p_filename)
{
    /* 入参判断 */
    if ((NULL == p_filename))
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "Inputs p_filename[%p]", p_filename);
        return -1;
    }
    int ret = -1;
    char buffer[1000];
    FILE *read_fp;
    char cmd[100];
    int chars_read;
    cJSON *arry_handl = NULL;
    cJSON *VdsState = NULL;
    cJSON *GnssStatus = NULL;
    cJSON *HardwareState = NULL;
    cJSON *SocTemp = NULL;
    cJSON *CpuUsage = NULL;
    cJSON *Memusage = NULL;
    cJSON *Diskusage = NULL;
    cJSON *V2XState = NULL;
    cJSON *V2XStackTx = NULL;
    cJSON *V2XStackRx = NULL;
    char *pbuf = FN_GetConfigJsonValueof_Char(p_filename);
    if (pbuf == NULL)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "FN_GetConfigJsonValueof_Char return is NULL");
        ret = -1;
        goto EXIT;
    }
    /* 默认jSON数组解 */
    arry_handl = cJSON_Parse(pbuf);
    if (arry_handl == NULL)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "cJSON_Parse arry_handl is NULL");
        cJSON_Delete(arry_handl);
        ret = -1;
        goto EXIT;
    }
    VdsState = cJSON_GetObjectItem(arry_handl, "VdsState");
    if (NULL == VdsState)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "VdsState  is NULL");
        cJSON_Delete(arry_handl);
        ret = -1;
        goto EXIT;
    }
    GnssStatus = cJSON_GetObjectItem(VdsState, "GnssStatus");
    if (NULL == GnssStatus)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "GnssStatus  is NULL");
        cJSON_Delete(arry_handl);
        ret = -1;
        goto EXIT;
    }
    /*GNSS工作状态 0:无效(默认);1:单点定位(E1);2:差分定位(E2);4:差分定位固定解(E4);5:差分定位浮点解(E5)*/
    switch (GnssStatus->valueint)
    {
    case 130:
        //普通定位
        V2xoburunningstatus.gnssstatus = 1;
        break;
    case 131:
    case 141:
        //无效
        V2xoburunningstatus.gnssstatus = 0;
        break;
    case 140:
        //差分定位固定解
        V2xoburunningstatus.gnssstatus = 4;
        break;
    default:
        //无效
        V2xoburunningstatus.gnssstatus = 0;
        break;
    }
    HardwareState = cJSON_GetObjectItem(arry_handl, "HardwareState");
    if (NULL == HardwareState)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "HardwareState  is NULL");
        cJSON_Delete(arry_handl);
        ret = -1;
        goto EXIT;
    }
    SocTemp = cJSON_GetObjectItem(HardwareState, "SOCTemp");
    if (NULL == SocTemp)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "SocTemp  is NULL");
        cJSON_Delete(arry_handl);
        ret = -1;
        goto EXIT;
    }

    //设备温度 单位：摄氏度
    V2xoburunningstatus.obutemp = (char *)calloc(1, strlen(SocTemp->valuestring));
    memcpy(V2xoburunningstatus.obutemp, SocTemp->valuestring, strlen(SocTemp->valuestring));

    CpuUsage = cJSON_GetObjectItem(HardwareState, "CpuUsage");
    if (NULL == CpuUsage)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "CpuUsage  is NULL");
        cJSON_Delete(arry_handl);
        ret = -1;
        goto EXIT;
    }
    //CPU占用率 单位%
    V2xoburunningstatus.cpuusage = (char *)calloc(1, strlen(CpuUsage->valuestring));
    memcpy(V2xoburunningstatus.cpuusage, CpuUsage->valuestring, strlen(CpuUsage->valuestring));

    Memusage = cJSON_GetObjectItem(HardwareState, "MemoryUsage");
    if (NULL == Memusage)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "MemoryUsage  is NULL");
        cJSON_Delete(arry_handl);
        ret = -1;
        goto EXIT;
    }
    //内存占有率 单位%
    V2xoburunningstatus.memusage = (char *)calloc(1, strlen(Memusage->valuestring));
    memcpy(V2xoburunningstatus.memusage, Memusage->valuestring, strlen(Memusage->valuestring));

    Diskusage = cJSON_GetObjectItem(HardwareState, "DiskUsage");
    if (NULL == Diskusage)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "SocTemp  is NULL");
        cJSON_Delete(arry_handl);
        ret = -1;
        goto EXIT;
    }
    //磁盘占用率，单位%;
    V2xoburunningstatus.diskusage = (char *)calloc(1, strlen(Diskusage->valuestring));
    memcpy(V2xoburunningstatus.diskusage, Diskusage->valuestring, strlen(Diskusage->valuestring));

    /*V2X 运行状态，0-正常 1-异常*/

    memset(cmd, 0, 100);
    sprintf(cmd, "cv2x-config --get-v2x-status |grep \"rx_status\"");
    read_fp = popen(cmd, "r");
    if (read_fp != NULL)
    {
        chars_read = fread(buffer, sizeof(char), 1000 - 1, read_fp);
        pclose(read_fp);
        if ((strstr(buffer, "tx_status=1") != NULL) && (strstr(buffer, "rx_status=1") != NULL))
        {
            V2xoburunningstatus.v2xstate = 0;
        }
        else
        {
            V2xoburunningstatus.v2xstate = 1;
        }
    }

    //4G 运行状态，0-正常，1-异常
    V2xoburunningstatus.state4g = 0;

    ret = 0;
    goto EXIT;
EXIT:
    if (NULL != pbuf)
    {
        free(pbuf);
        pbuf = NULL;
    }
    return ret;
}

/******************************************************************
 * 函 数 名 称    : SendSecMsgData
 * 功 能 描 述    : OBU场景数据组protobuf包
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 15:25:18 V1.0     bo_jiang   Create
*=====================================================================*/
int SendSecMsgData(V2xPlatformSceneWarn v2xplatformscenewarn)
{
    LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "SendSecMsgData");
    int ret = 0;
    uint8_t *buf = NULL;
    int len = 0;
    int scenewarning = 0;
    //获取场景数据进行组包

    scenewarning = get_V2xSceneWarning(v2xplatformscenewarn);
    if (scenewarning == IS_ERR)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "scenewarning is %d", scenewarning);
        return IS_ERR;
    }

    //序列化
    len = v2x_scene_warning__get_packed_size(&V2xseenewarning);
    buf = (uint8_t *)malloc(len);
    if (buf == NULL)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "v2xseenewarning malloc error!");
        return IS_ERR;
    }
    //打包主结构
    v2x_scene_warning__pack(&V2xseenewarning, buf);
    // ret = pack_into_data_V2xSceneWarning(buf, len, 0x90, 0x07);
    ret = pack_into_data(buf, len, 0x90, 0x07);
    if (ret)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "pack_into_data_V2xSceneWarning error!");
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "pack_into_data_V2xSceneWarning success!");
    }

    //内存释放

    FREE_CONSTANT(buf);
    return IS_OK;
}
/******************************************************************
 * 函 数 名 称    : CooperativeSendSecMsgData
 * 功 能 描 述    : OBU协作时匝道汇入场景数据组protobuf包
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 15:25:18 V1.0     bo_jiang   Create
*=====================================================================*/
extern "C"
{
    int CooperativeSendSecMsgData(RoadsideCoordination_t *p_roadsideCoordination)
    {
        LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "CooperativeSendSecMsgData");
        int ret = 0;
        uint8_t *buf = NULL;
        int len = 0;
        //获取场景数据进行组包
        // LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "v2xplatformscenewarn.type is %d", v2xplatformscenewarn.type);
        get_V2xCooperativeSceneWarning(p_roadsideCoordination);

        //序列化
        len = v2x_scene_warning__get_packed_size(&V2xseenewarning);
        buf = (uint8_t *)malloc(len);
        if (buf == NULL)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "v2xseenewarning malloc error!");
            return IS_ERR;
        }
        //打包主结构
        v2x_scene_warning__pack(&V2xseenewarning, buf);
        // ret = pack_into_data_CooperativeSendSecMsgData(buf, len, 0x90, 0x07);
        ret = pack_into_data(buf, len, 0x90, 0x07);
        if (ret)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "pack_into_data_CooperativeSendSecMsgData error!");
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "pack_into_data_CooperativeSendSecMsgData success!");
        }

        //内存释放

        FREE_CONSTANT(V2xseenewarning.description);
        FREE_CONSTANT(buf);
        return IS_OK;
    }
}
/******************************************************************
 * 函 数 名 称    : Thread_Qxwz_V2xObuRunningStatus
 * 功 能 描 述    : OBU运行状态上报线程，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-09 17:12:05 V1.0     bo_jiang   Create
*=====================================================================*/
static void *Thread_Qxwz_V2xObuRunningStatus(void *arg)
{

    while (1)
    {
        uint8_t *buf = NULL;
        int len = 0;
        //读取设备运行状态
        V2xoburunningstatus.sequence = get_V2xObuRunningStatus_sequence();
        V2xoburunningstatus.timestamp = get_timestamp();
        V2xoburunningstatus.ueid = get_v2xobustate_id();

        FN_InitConfigStruct(DYNAMICINFO_Config_Path);

        //序列化

        len = v2x_obu_running_status__get_packed_size(&V2xoburunningstatus);
        buf = (uint8_t *)malloc(len);
        if (buf == NULL)
        {
            LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "V2xObuState buf calloc err!!!");
            FREE_CONSTANT(V2xoburunningstatus.obutemp);
            FREE_CONSTANT(V2xoburunningstatus.cpuusage);
            FREE_CONSTANT(V2xoburunningstatus.memusage);
            FREE_CONSTANT(V2xoburunningstatus.diskusage);
            FREE_CONSTANT(buf);
            continue;
        }

        //打包主结构
        v2x_obu_running_status__pack(&V2xoburunningstatus, buf);

        //反序列化
        // V2xObuRunningStatus *V2xObuRunningStatu = v2x_obu_running_status__unpack(NULL, len, buf);
        // if (V2xObuRunningStatu)
        // {
        //     LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "V2xObuRunningStatu->ueid is %s", V2xObuRunningStatu->ueid);
        //     LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "V2xObuRunningStatu->gnssstatus is %d", V2xObuRunningStatu->gnssstatus);
        //     LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "V2xObuRunningStatu->obutemp is %s", V2xObuRunningStatu->obutemp);
        //     LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "V2xObuRunningStatu->cpuusage is %s", V2xObuRunningStatu->cpuusage);
        //     LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "V2xObuRunningStatu->v2xstate is %d", V2xObuRunningStatu->v2xstate);
        //     LogPrint(LOG_LEVEL_DEBUG, LOG_MODULE_NAME_APP_LST, "V2xObuRunningStatu->state4g is %d", V2xObuRunningStatu->state4g);
        //     v2x_obu_running_status__free_unpacked(V2xObuRunningStatu, NULL);
        // }
        pack_into_data_CooperativeSendSecMsgData(buf, len, 0x90, 0x08);
        pack_into_data(buf, len, 0x90, 0x08);

        //内存释放
        FREE_CONSTANT(V2xoburunningstatus.obutemp);
        FREE_CONSTANT(V2xoburunningstatus.cpuusage);
        FREE_CONSTANT(V2xoburunningstatus.memusage);
        FREE_CONSTANT(V2xoburunningstatus.diskusage);
        FREE_CONSTANT(buf);

        usleep(1000 * 1000);
    }
}

/******************************************************************
 * 函 数 名 称    : Qxwz_V2xObu_init
 * 功 能 描 述    : OBU上报线程初始化
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 15:25:18 V1.0     bo_jiang   Create
*=====================================================================*/
int Qxwz_V2xObu_init()
{
    pthread_t Qxwz_V2xObuState_tid;
    pthread_create(&Qxwz_V2xObuState_tid, NULL, Thread_Qxwz_V2xObuState, NULL);
    pthread_detach(Qxwz_V2xObuState_tid);

    pthread_t Qxwz_V2xObuStatistics_tid;
    pthread_create(&Qxwz_V2xObuStatistics_tid, NULL, Thread_Qxwz_Qxwz_V2xObuStatistics, NULL);
    pthread_detach(Qxwz_V2xObuStatistics_tid);

    pthread_t Qxwz_V2xObuRunningStatus_tid;
    pthread_create(&Qxwz_V2xObuRunningStatus_tid, NULL, Thread_Qxwz_V2xObuRunningStatus, NULL);
    pthread_detach(Qxwz_V2xObuRunningStatus_tid);

    return 0;
}
/******************************************************************
 * 函 数 名 称    : Cloud_Platform_TZ
 * 功 能 描 述    : OBU上报线程初始化
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 15:25:18 V1.0     bo_jiang   Create
*=====================================================================*/
int Cloud_Platform_TZ()
{
    int ret = 0;
    pthread_mutex_init(&g_SendFuncMutex, NULL);
    //MQTT初始化
    ret = mqtt_service_init();
    if (ret)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "mqtt_service_init err!!!");
        return IS_ERR;
    }
    //MQTT初始化成功启动OBU自身静态信息上报，上线时上报一次
    ret = FN_Qxwz_V2xObuBasicInfo();
    if (ret)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "OBU自身静态信息上报失败!!!");
        return IS_ERR;
    }
    //OBU上报线程初始化
    ret = Qxwz_V2xObu_init();
    if (ret)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_MODULE_NAME_APP_LST, "OBU上报线程初始化失败!!!");
        return IS_ERR;
    }
    return IS_OK;
}
