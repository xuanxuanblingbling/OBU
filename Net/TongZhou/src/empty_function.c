#include "TongZhou/inc/empty_function.h"

#define MAX_DUMMY_PACKET_LEN 100
/***********************************************************************
* 函 数 名 称 ： ArrayToStr
* 功 能 描 述 ： 将16进制转为字符串
* 输 入 参 数 : 待转16进制
* 输 出 参 数 ：    无
* 返  回  值  : 转换成功后的str
* 开 发 人 员 ： jiangbo
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2021-10-20 V1.0    jiangbo   Create
***********************************************************************/
int ArrayToStr(unsigned char *Buff, unsigned int BuffLen, char *OutputStr)
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
/******************************************************************
 * 函 数 名 称    : get_timestamp
 * 功 能 描 述    : 获取当前UTC时间戳，单位ms
 * 输 入 参 数    : 无
 * 输 出 参 数    : 获取当前UTC时间戳，单位ms
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-06 10:56:15 V1.0     bo_jiang   Create
*=====================================================================*/
int64_t get_timestamp()
{
    int64_t get_now_time = 0;
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    get_now_time = (int64_t)((int64_t)ts.tv_sec * 1000 + ts.tv_nsec / 1000000); //获取当前时间戳，单位：us
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "get_now_time :%lld", get_now_time);
    return get_now_time;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobubasicinfo_vehicletype
 * 功 能 描 述    : OBU静态信息车辆类型上报
 * 输 入 参 数    : 无
 * 输 出 参 数    : 车辆类型
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-06 12:06:36 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_vehicletype()
{
    int32_t Vehicletype = 0;
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "VehType ", Vehicletype);
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "get_v2xobubasicinfo_vehicletype is %d", Vehicletype);
    return Vehicletype;
}
/*********************************************OBU静态信息上报序***********************************************************************/

/******************************************************************
 * 函 数 名 称    : get_v2xobubasicinfo_sequence
 * 功 能 描 述    : OBU静态信息上报序列号
 * 输 入 参 数    : 无
 * 输 出 参 数    : OBU静态信息上报序列号
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-06 11:13:52 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_v2xobubasicinfo_sequence()
{
    static int32_t Sequenec = 0;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobubasicinfo_sequence :%ld", Sequenec);
    return Sequenec++ & 0xFFFF;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobubasicinfo_firmwareversion
 * 功 能 描 述    : OBU静态信息固件版本上报
 * 输 入 参 数    : 无
 * 输 出 参 数    : OBUAG15固件版本
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-06 11:44:38 V1.0     bo_jiang   Create
*=====================================================================*/
char *get_v2xobubasicinfo_firmwareversion()
{
    char l_version[64] = {0};
    char *p_version = NULL;
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "AG15SwVersion", l_version);
    p_version = calloc(sizeof(l_version), sizeof(char));
    if (NULL == p_version)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_EMPTY_FUN, "p_version calloc error!");
    }
    else
    {
        memcpy(p_version, l_version, sizeof(l_version));
        LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobubasicinfo_firmwareversion is %s", p_version);
        return p_version;
    }
}
/******************************************************************
 * 函 数 名 称    : get_v2xobubasicinfo_appversion
 * 功 能 描 述    : OBUApp版本上报
 * 输 入 参 数    : 无
 * 输 出 参 数    : OBUApp版本
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-06 11:48:54 V1.0     bo_jiang   Create
*=====================================================================*/
char *get_v2xobubasicinfo_appversion()
{
    char l_appversion[64] = {0};
    char *p_appversion = NULL;
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "AppVersion", l_appversion);
    p_appversion = calloc(sizeof(l_appversion), sizeof(char));
    if (NULL == p_appversion)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_EMPTY_FUN, "p_appversion calloc error!");
    }
    else
    {
        memcpy(p_appversion, l_appversion, sizeof(l_appversion));
        LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "get_v2xobubasicinfo_appversion is %s", p_appversion);
        return p_appversion;
    }
}
/******************************************************************
 * 函 数 名 称    : get_v2xobubasicinfo_platenum
 * 功 能 描 述    : OBU车牌上报
 * 输 入 参 数    : 无
 * 输 出 参 数    : OBU车牌
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-06 11:52:45 V1.0     bo_jiang   Create
*=====================================================================*/
char *get_v2xobubasicinfo_platenum()
{
    char l_platenum[64] = {0};
    char *p_platenum = NULL;
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "Platenum", l_platenum);
    p_platenum = calloc(sizeof(l_platenum), sizeof(char));
    if (NULL == p_platenum)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_EMPTY_FUN, "p_platenum calloc error!");
    }
    else
    {
        memcpy(p_platenum, l_platenum, sizeof(l_platenum));
        LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "get_v2xobubasicinfo_platenum is %s", p_platenum);
        return p_platenum;
    }
}
/******************************************************************
 * 函 数 名 称    : get_v2xobubasicinfo_devicesn
 * 功 能 描 述    : OBU静态信息SN上报
 * 输 入 参 数    : 无
 * 输 出 参 数    : SN
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-06 11:55:30 V1.0     bo_jiang   Create
*=====================================================================*/
char *get_v2xobubasicinfo_devicesn()
{
    char l_devicesn[64] = {0};
    char *p_devicesn = NULL;
    ConfigGetKey(OBU_INFO_FILE, "ObuBaseInfo", "ObuSN", l_devicesn);
    p_devicesn = calloc(sizeof(l_devicesn), sizeof(char));
    if (NULL == p_devicesn)
    {
        LogPrint(LOG_LEVEL_ERR, LOG_EMPTY_FUN, "p_devicesn calloc error!");
    }
    else
    {
        memcpy(p_devicesn, l_devicesn, sizeof(l_devicesn));
        LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "get_v2xobubasicinfo_devicesn is %s", p_devicesn);
        return p_devicesn;
    }
}

/*********************************************OBU实时状态上报***********************************************************************/
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_sequence
 * 功 能 描 述    : OBU实时状态上报序列号，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : OBU实时状态上报序列号
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-06 12:13:22 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_v2xobustate_sequence()
{
    static int32_t Sequenec = 0;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "get_v2xobustate_sequence :%ld", Sequenec);
    return Sequenec++ & 0xFFFF;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_id
 * 功 能 描 述    : OBU实时状态上报ID，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : ID
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 15:49:56 V1.0     bo_jiang   Create
*=====================================================================*/
char *get_v2xobustate_id()
{
    char *v2xobustate_id = NULL;
    char OoutPutStr[100] = {0};
    int len = ArrayToStr(&g_tDbusVehDataFrame.m_MsgData.m_vehId[9], 8, OoutPutStr);
    v2xobustate_id = calloc(len, sizeof(uint8_t));
    if (v2xobustate_id)
    {
        memcpy(v2xobustate_id, OoutPutStr, len);
        // for (int i = 0; i < sizeof(g_tDbusVehDataFrame.m_MsgData.m_vehId); i++)
        // {
        //     printf("%02x", g_tDbusVehDataFrame.m_MsgData.m_vehId[i]);
        // }
        // printf("\n");
        // LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "sizeof(g_tDbusVehDataFrame.m_MsgData.m_vehId) :%d", sizeof(g_tDbusVehDataFrame.m_MsgData.m_vehId));
        LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "get_v2xobustate_id :%s", v2xobustate_id);
        return v2xobustate_id;
    }
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_latitude
 * 功 能 描 述    : OBU实时状态上报latitude，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : latitude
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 15:52:32 V1.0     bo_jiang   Create
*=====================================================================*/
double get_v2xobustate_latitude()
{
    double v2xobustate_latitude = 0;
    v2xobustate_latitude = ((double)g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_int_latitude) / 10000000;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "get_v2xobustate_latitude :%lf", v2xobustate_latitude);
    return v2xobustate_latitude;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_longitude
 * 功 能 描 述    : OBU实时状态上报longitude，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : longitude
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 15:53:34 V1.0     bo_jiang   Create
*=====================================================================*/
double get_v2xobustate_longitude()
{
    double v2xobustate_longitude = 0;
    v2xobustate_longitude = ((double)g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_int_longitude) / 10000000;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustate_longitude :%lf", v2xobustate_longitude);
    return v2xobustate_longitude;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_elevation
 * 功 能 描 述    : OBU实时状态上报elevation，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : elevation
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 15:56:40 V1.0     bo_jiang   Create
*=====================================================================*/
float get_v2xobustate_elevation()
{
    float v2xobustate_elevation = 0;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustate_elevation :%d", g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_int_altitude);
    v2xobustate_elevation = ((float)g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_int_altitude);
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustate_elevation :%f", v2xobustate_elevation);
    return v2xobustate_elevation;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_heading
 * 功 能 描 述    : OBU实时状态上报heading，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : heading
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 15:59:27 V1.0     bo_jiang   Create
*=====================================================================*/
float get_v2xobustate_heading()
{
    float v2xobustate_heading = 0;
    v2xobustate_heading = (float)g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_dbl_heading;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustate_heading :%f", v2xobustate_heading);
    return v2xobustate_heading;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_speed
 * 功 能 描 述    : OBU实时状态上报speed，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : speed
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 16:01:40 V1.0     bo_jiang   Create
*=====================================================================*/
float get_v2xobustate_speed()
{
    float v2xobustate_speed = 0;
    v2xobustate_speed = (float)g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_dbl_speed;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustate_speed :%f", v2xobustate_speed);
    return v2xobustate_speed;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_vehicletype
 * 功 能 描 述    : OBU实时状态上报车辆类型，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : 车辆类型
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 16:03:59 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_v2xobustate_vehicletype()
{
    int32_t v2xobustate_vehicletype = 0;
    v2xobustate_vehicletype = g_tDbusVehDataFrame.m_MsgData.m_basicVehicleClass;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustate_vehicletype :%d", v2xobustate_vehicletype);
    return v2xobustate_vehicletype;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_laneid
 * 功 能 描 述    : OBU实时状态上报车辆所属车道ID，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : 车辆所属车道ID
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 16:15:30 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_v2xobustate_laneid()
{
    int32_t v2xobustate_laneid = 0;
    /*code*/
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustate_laneid :%d", v2xobustate_laneid);
    return v2xobustate_laneid;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_nodeid
 * 功 能 描 述    : OBU实时状态上报车辆所在地图本地节点ID，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : 车辆所在地图本地节点ID
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 16:20:06 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_v2xobustate_nodeid()
{
    int32_t v2xobustate_nodeid = 0;
    /*code*/
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustate_nodeid :%d", v2xobustate_nodeid);
    return v2xobustate_nodeid;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_autopilotstate
 * 功 能 描 述    : OBU实时状态上报自动驾驶状态：1：自动驾驶; 2:手动驾驶，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : 自动驾驶状态：1：自动驾驶; 2:手动驾驶
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 16:30:31 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_v2xobustate_autopilotstate()
{
    int32_t v2xobustate_autopilotstate = 0;
    /*code*/
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustate_autopilotstate :%d", v2xobustate_autopilotstate);
    return v2xobustate_autopilotstate;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_faultstate
 * 功 能 描 述    : OBU实时状态上报自动驾驶状态：1：自动驾驶; 2:手动驾驶，每秒一次
 * 输 入 参 数    : 无
 * 输 出 参 数    : 故障状态。0:无故障；1:有故障
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 16:32:00 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_v2xobustate_faultstate()
{
    int32_t v2xobustate_faultstate = 0;
    /*code*/
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustate_faultstate :%d", v2xobustate_faultstate);
    return v2xobustate_faultstate;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_gnssstatus
 * 功 能 描 述    : OBU实时状态上报gnss工作状态 0:无效(默认);1:单点定位(E1);2:差分定位(E2);4:差分定位固定解(E4);5:差分定位浮点解(E5)
 * 输 入 参 数    : 无
 * 输 出 参 数    : gnss工作状态 0:无效(默认);1:单点定位(E1);2:差分定位(E2);4:差分定位固定解(E4);5:差分定位浮点解(E5)
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-08 16:37:35 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_v2xobustate_gnssstatus()
{
    //Location State : 0X00: Default ;0X10: RTK E1 ;0X20: RTK E2 ; 0X50: RTK E5 ;0X60: RTK E4; 0X80: AG15_Kernel.
    int32_t v2xobustate_gnssstatus = 0;
    switch (g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_int_CurrentGpsState)
    {
    case 0x00:
        v2xobustate_gnssstatus = 0;
        break;
    case 0x10:
        v2xobustate_gnssstatus = 1;
        break;
    case 0x20:
        v2xobustate_gnssstatus = 2;
        break;
    case 0x50:
        v2xobustate_gnssstatus = 5;
        break;
    case 0x60:
        v2xobustate_gnssstatus = 4;
        break;
    default:
        break;
    }
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustate_gnssstatus :%d", v2xobustate_gnssstatus);
    return v2xobustate_gnssstatus;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_length
 * 功 能 描 述    : OBU实时状态上报车辆尺寸
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-12-03 19:46:22 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_v2xobustate_length()
{
    int32_t v2xobustate_length = 0;
    v2xobustate_length = (int32_t)g_tDbusVehDataFrame.m_MsgData.m_vehicleLength;
    return v2xobustate_length;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_width
 * 功 能 描 述    : OBU实时状态上报车辆尺寸
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-12-03 19:46:22 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_v2xobustate_width()
{
    int32_t v2xobustate_width = 0;
    v2xobustate_width = (int32_t)g_tDbusVehDataFrame.m_MsgData.m_vehicleWidth;
    return v2xobustate_width;
}
/******************************************************************
 * 函 数 名 称    : get_v2xobustate_height
 * 功 能 描 述    : OBU实时状态上报车辆尺寸
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-12-03 19:46:22 V1.0     bo_jiang   Create
*=====================================================================*/
int32_t get_v2xobustate_height()
{
    int32_t v2xobustate_height = 0;
    v2xobustate_height = (int32_t)g_tDbusVehDataFrame.m_MsgData.m_vehicleHeight;
    return v2xobustate_height;
}
/*********************************************OBU统计信息周期上报，目前实现上是针对所有的包数**********************************************************************/
/******************************************************************
 * 函 数 名 称    : get_v2xobustatistics_sequence
 * 功 能 描 述    : OBU统计信息上报序号
 * 输 入 参 数    : 无
 * 输 出 参 数    : OBU统计信息上报序号
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-09 16:44:58 V1.0     bo_jiang   Create
*=====================================================================*/
uint32_t get_v2xobustatistics_sequence()
{
    uint32_t v2xobustatistics_sequence = 0;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobustatistics_sequence :%d", v2xobustatistics_sequence);
    return v2xobustatistics_sequence++ & 0xFFFFFFFF;
}
/*********************************************设置和查询配置的响应**********************************************************************/
/******************************************************************
 * 函 数 名 称    : get_v2xobuconfigrsp_sequence
 * 功 能 描 述    : 设置和查询配置的响应的序号
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-11-12 13:46:02 V1.0     bo_jiang   Create
*=====================================================================*/
uint32_t get_v2xobuconfigrsp_sequence()
{
    uint32_t v2xobuconfigrsp_sequence = 0;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xobuconfigrsp_sequence :%d", v2xobuconfigrsp_sequence);
    return v2xobuconfigrsp_sequence++ & 0xFFFFFFFF;
}

uint32_t get_v2xseenewarning_sequence()
{
    static uint32_t v2xseenewarning_sequence = 0;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "v2xseenewarning_sequence :%d", v2xseenewarning_sequence);
    return v2xseenewarning_sequence++ & 0xFFFFFFFF;
}

uint32_t get_V2xObuRunningStatus_sequence()
{
    static uint32_t V2xObuRunningStatus_sequence = 0;
    LogPrint(LOG_LEVEL_DEBUG, LOG_EMPTY_FUN, "V2xObuRunningStatus_sequence :%d", V2xObuRunningStatus_sequence);
    return V2xObuRunningStatus_sequence++ & 0xFFFFFFFF;
}