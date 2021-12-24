/************************************************************
  文件名: vds_dbusSend.c
  作者:                 
  描述: vds模块dbus数据发送函数，用于向dbsu总线推送数据           
  版本:      
  日期:       
  函数列表:   
  历史记录: 
 ***********************************************************/
#include <dbus/dbus-glib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vds_dbus.h"
#include "v2x_obu_dbus_common.h"
#include "general_config.h"
#include "GPS_locate.h"

#include "../GPSInterface/GPS-M.h"`  
#include "../CAN_Model/CAN/CAN.h"

//自测试用
extern int LocateSource;
extern int latitude;
extern int lontitude ;
extern int SpeedData ;
extern int HeadingData ;
extern GpsLocation g_GpsLocat;

#define OFFSET 0
#define TEST 0

/*************************************************
  名称: DbusGeneralSendFuc
  描述: dbus通用发送接口
  输入参数:p_data:需要发送的数据，p_len：数据长度，p_sigid：信号id
  输出参数:无
  返回值:无
**************************************************/
void DbusGeneralSendFuc(uint8_t *p_data,uint16_t p_len,TSignalFd_em p_sigid)
{
    uint8_t l_eRepatFlag = false;
    GArray *pass= NULL;//定义GArray变量
    pass = g_array_new(FALSE,TRUE,sizeof(uint8_t));

    //判断信号类型，设置信号id,信号长度
    switch (p_sigid)
    {
        case VDS_VEH_DATA:
        {
            p_data[0] = VEH_DATA_ID&0xff;//id
            p_data[1] = (VEH_DATA_ID>>8)&0xff;
            p_data[2] = VDS_VEH_DATA_LEN&0xff;//数据长度
            p_data[3] = (VDS_VEH_DATA_LEN>>8)&0xff;
        }
        break;
        case VDS_STATE_PUSH:
        {
            p_data[0] = VDS_STATE_ID&0xff;//id
            p_data[1] = (VDS_STATE_ID>>8)&0xff;
            p_data[2] = VDS_STATE_DATA_LEN&0xff;//数据长度
            p_data[3] = (VDS_STATE_DATA_LEN>>8)&0xff;
        }
        break;
        case VDS_FAULT_PUSH:
        {
            l_eRepatFlag = true;//event repat frame,触发后连续推送特定次数
            p_data[0] = VDS_FAULT_ID&0xff;//id
            p_data[1] = (VDS_FAULT_ID>>8)&0xff;
            p_data[2] = VDS_FAULT_DATA_LEN&0xff;//数据长度
            p_data[3] = (VDS_FAULT_DATA_LEN>>8)&0xff;
        }
        break;
        case MCU_FAULT_PUSH:
        {
            l_eRepatFlag = true;//event repat frame,触发后连续推送特定次数
            p_data[0] = MCU_FAULT_ID&0xff;//id
            p_data[1] = (MCU_FAULT_ID>>8)&0xff;
            p_data[2] = MCU_FAULT_DATA_LEN&0xff;//数据长度
            p_data[3] = (MCU_FAULT_DATA_LEN>>8)&0xff;
        }
        break;
        case MCU_PDOWN_RQ:
        {
            p_data[0] = MCU_PDOWN_ID&0xff;//id
            p_data[1] = (MCU_PDOWN_ID>>8)&0xff;
            p_data[2] = MCU_PDOWN_RQ_DATA_LEN&0xff;//数据长度
            p_data[3] = (MCU_PDOWN_RQ_DATA_LEN>>8)&0xff;
        }
        break;   
        case VDS_CONFIG_RS:
        {
            p_data[0] = VDS_CONFIG_ID&0xff;//id
            p_data[1] = (VDS_CONFIG_ID>>8)&0xff;
            p_data[2] = VDS_CONFIG_DATA_LEN&0xff;//数据长度
            p_data[3] = (VDS_CONFIG_DATA_LEN>>8)&0xff;
        }
        break;  
        case MCU_CONFIG_RS:
        {
            p_data[0] = MCU_CONFIG_ID&0xff;//id
            p_data[1] = (MCU_CONFIG_ID>>8)&0xff;
            p_data[2] = MCU_CONFIG_DATA_RS_LEN&0xff;//数据长度
            p_data[3] = (MCU_CONFIG_DATA_RS_LEN>>8)&0xff;
        }
        break;  
        default:
           g_array_free(pass,TRUE);//GArray变量空间释放
           return;
    }
    p_data[p_len-1] = FD_CaluBcc(p_data,p_len-1);//求bcc
    g_array_append_vals(pass,p_data,p_len);//赋值给GArray
    
    if(l_eRepatFlag)//Event Repate事件触发，周期推送固定次数
    {
        l_eRepatFlag = false;
        for(int l_cnt=0;l_cnt<EVENT_REPEAT_PUSH_NUM;l_cnt++)
        {
            g_signal_emit(obj,signals[p_sigid], 0,pass);//发送数据
            milliseconds_sleep( EVENT_REPEAT_CYCLE_TIME);
        }
    }
    else//其他事件触发，仅发送一次
    {
        g_signal_emit(obj,signals[p_sigid], 0,pass);//发送数据
    }
    g_array_free(pass,TRUE);//GArray变量空间释放
}

/*************************************************
  名称: FD_vds_emit_signal_of_veh_data
  描述:　定时器回调函数，发送车辆运行状态帧
  输入参数:
  返回值: 无
**************************************************/
void GetVehData(void)
{
    GpsLocation l_GpsLocateT;
    VehCANData  l_CANdataT;
    static uint64_t static_lasttime;
    struct timeval tv;
    int ret = 0;
    
    ret = GetGnssData(&l_GpsLocateT);
    CAN_GetData(&l_CANdataT);
      
    // //车辆灯状态
    // l_CANdataT.m_exteriorLights = (l_CANdataT.RecVehLampMessage.BCM_FrontFogLampSt | (l_CANdataT.RecVehLampMessage.BCM_HighBeamSt<<1)
    //                          | (l_CANdataT.RecVehLampMessage.BCM_LeftTurnLampSt<<2)| (l_CANdataT.RecVehLampMessage.BCM_LowBeamSt<<3)
    //                          | (l_CANdataT.RecVehLampMessage.BCM_ParkingLampSt<<4) | (l_CANdataT.RecVehLampMessage.BCM_RearFogLampSt<<5)
    //                          | (l_CANdataT.RecVehLampMessage.BCM_RightTurnLampSt<<6) | (l_CANdataT.RecVehLampMessage.BCM_VehReverseSt<<7));
   

    pthread_mutex_lock(&g_VDSVehFrameMutex);//加锁
    memcpy(&g_VdsVehFrame.m_vehdata.m_gpsdata_st.m_int_latitude,&l_GpsLocateT.latitude,sizeof(l_GpsLocateT));
    if((0 == g_VdsVehFrame.m_vehdata.m_basicVehicleClass)|| (0xFF == g_VdsVehFrame.m_vehdata.m_basicVehicleClass))
    {
        g_VdsVehFrame.m_vehdata.m_basicVehicleClass = 59;
    }
    if(l_CANdataT.LeftTurnLampSt.VehGNSS_timestamp != static_lasttime)
    {
        // static_lasttime = l_CANdataT.LeftTurnLampSt.VehGNSS_timestamp;
        // memcpy(&g_VdsVehFrame.m_vehdata.m_candata_st,&l_CANdataT,sizeof(l_CANdataT));
    }
    else
    {}
    
    memcpy(&g_VdsVehFrame.m_vehdata.m_vehId[0],&g_param_veh_info.veh.VehId[0],17);     //车辆ID
    g_VdsVehFrame.m_vehdata.m_vehicleHeight = g_param_veh_info.veh.vehicleHeight;      //车身高度
    g_VdsVehFrame.m_vehdata.m_vehicleLength = g_param_veh_info.veh.vehicleLength;      //车身长度
    g_VdsVehFrame.m_vehdata.m_vehicleWidth = g_param_veh_info.veh.vehicleWidth;        //车身宽度
    g_VdsVehFrame.m_vehdata.m_basicVehicleClass = g_param_veh_info.veh.VehType;        //车辆类型
    g_VdsVehFrame.m_vehdata.m_int_acclat = 0;
    g_VdsVehFrame.m_vehdata.m_int_acclng = 0;
    g_VdsVehFrame.m_vehdata.m_int_accvert = 0;
    g_VdsVehFrame.m_vehdata.m_int_yawrate = 0;
    
    if(1 == LocateSource)
    {
        g_VdsVehFrame.m_vehdata.m_gpsdata_st.m_int_latitude = latitude;
        g_VdsVehFrame.m_vehdata.m_gpsdata_st.m_int_longitude = lontitude;
        g_VdsVehFrame.m_vehdata.m_gpsdata_st.m_dbl_speed = SpeedData;
        g_VdsVehFrame.m_vehdata.m_gpsdata_st.m_dbl_heading = HeadingData;
    }

    pthread_mutex_unlock(&g_VDSVehFrameMutex);//解锁
    
}

/*************************************************
  名称: FD_vds_emit_signal_of_veh_data
  描述:　定时器回调函数，发送车辆运行状态帧
  输入参数:
  返回值: 无
**************************************************/
void faultCheckProcess(GNSS_State_Type *GNSS_CAN_State) 
{
    uint64_t timestamp = 0;
    struct timeval tv;
	gettimeofday(&tv, NULL);
	timestamp = (uint64_t)tv.tv_sec * 1000 +  (uint64_t)tv.tv_usec/1000 ;
    GNSS_CAN_State->LEDState = GnssLedState ;
    LogPrint(LOG_LEVEL_NOTICE, "GPS Model State", "Current GPS Timer Period is : %d \n",timestamp - GNSS_timestamp);
    LogPrint(LOG_LEVEL_NOTICE, "GPS Model State", "Current GPS LED is : %d \n",GNSS_CAN_State->LEDState);

    if((timestamp - GNSS_timestamp) >= NormalTimePeriod)
    {
        if(RtcmFlag == RTK_Model)
        {
            GNSS_CAN_State->GNSSFaultState = RTK_GNSS_Fault ;
        }
        else
        {
             GNSS_CAN_State->GNSSFaultState = AG15_GNSS_Fault ;
        }
        
    }
    else
    {
        GNSS_CAN_State->GNSSFaultState = GNSS_Normal_State ;            
    }
}

/*************************************************
  名称: FD_vds_emit_signal_of_veh_data
  描述:　定时器回调函数，发送车辆运行状态帧
  输入参数:
  返回值: 无s
**************************************************/
gboolean FD_vds_emit_signal_of_veh_data(gpointer data)
{
    GetVehData();
    pthread_mutex_lock(&g_VDSVehFrameMutex);//加锁
    printf("DBUS Send Data: %d  %d  %d  %d \n",g_VdsVehFrame.m_vehdata.m_driveIntent.m_u8GSPAintent,g_VdsVehFrame.m_vehdata.m_driveIntent.m_u32GSPAvaildtime
                                               ,g_VdsVehFrame.m_vehdata.m_driveIntent.m_u8CLCintent,g_VdsVehFrame.m_vehdata.m_driveIntent.m_u32CLCvaildtime);
    DbusGeneralSendFuc((uint8_t*)&g_VdsVehFrame,sizeof(TVdsVehFrame_st),VDS_VEH_DATA);//发送车辆运行数据帧
    pthread_mutex_unlock(&g_VDSVehFrameMutex);//解锁
    return TRUE;
}
/*************************************************
  名称: FD_vds_emit_signal_of_led
  描述:　定时器回调函数，发送LED状态推送帧
  输入参数:
  返回值: 无
**************************************************/
gboolean FD_vds_emit_signal_of_led(gpointer data)
{
    // static GNSS_State_Type COM_GNSS_CAN_State = {0,0} ;
    // static GNSS_State_Type Current_GNSS_CAN_State = {0,0} ;
    // faultCheckProcess(&Current_GNSS_CAN_State);
    // LogPrint(LOG_LEVEL_NOTICE, "GPS Model State", "Current GPS LED State is : %d \n",Current_GNSS_CAN_State.LEDState);
    // LogPrint(LOG_LEVEL_NOTICE, "GPS Model State", "Current GPS Fault State is : %d \n",Current_GNSS_CAN_State.GNSSFaultState);
    // if((COM_GNSS_CAN_State.LEDState != Current_GNSS_CAN_State.LEDState)
    // ||(COM_GNSS_CAN_State.GNSSFaultState != Current_GNSS_CAN_State.GNSSFaultState))
    // {
    //     COM_GNSS_CAN_State.LEDState = Current_GNSS_CAN_State.LEDState;
    //     COM_GNSS_CAN_State.GNSSFaultState = Current_GNSS_CAN_State.GNSSFaultState;
    //     //DbusGeneralSendFuc((uint8_t*)(&Current_GNSS_CAN_State),sizeof(Current_GNSS_CAN_State),VDS_STATE_PUSH);//发送vds运行状态帧
    // }
    // return TRUE;
}
/*************************************************
  名称: FD_vds_emit_signal_of_led
  描述:　定时器回调函数，发送LED状态推送帧
  输入参数:
  返回值: 无
**************************************************/
gboolean FD_vds_emit_signal_of_state_push(gpointer data)
{  
    GpsLocation l_GpsLocateTstate;
    static uint64_t l_u64time;
    struct timeval tv;
    int ret = 0;

    ret = GetGnssData(&l_GpsLocateTstate);

    gettimeofday(&tv, NULL);
    l_u64time = (uint64_t)tv.tv_sec*1000 + (uint64_t)tv.tv_usec/1000;

    if((l_u64time - l_GpsLocateTstate.timestamp) >= NormalTimePeriod)
    {
        if(RtcmFlag == RTK_Model)
        {
            g_VdsStatePush.m_state.m_GnssStatus = GnssRTKFAULT;
        }
        else
        {
            g_VdsStatePush.m_state.m_GnssStatus = GnssAG15FAULT;
        }
        
    }
    else
    {
        if(l_GpsLocateTstate.CurrentGpsState == RTKE4)
        {
            g_VdsStatePush.m_state.m_GnssStatus = GnssRTKNormal;
            LogPrint(LOG_LEVEL_NOTICE, "GPS Model State", "Current GPS LED State is : %d \n",l_GpsLocateTstate.CurrentGpsState);
        }
        else
        {
            g_VdsStatePush.m_state.m_GnssStatus = GnssAG15Normal;
            LogPrint(LOG_LEVEL_NOTICE, "GPS Model State", "Current GPS LED State is : %d \n",l_GpsLocateTstate.CurrentGpsState);
        }         
    }
    
    
    DbusGeneralSendFuc((uint8_t*)(&g_VdsStatePush),sizeof(g_VdsStatePush),VDS_STATE_PUSH);//发送vds运行状态帧
    return TRUE;
}
