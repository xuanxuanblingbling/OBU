/************************************************************
  文件名: v2x_obu_dbus_common.h
  作者:            
  描述: 定义v2xobu各子模块dbus通讯通用信息     
  版本: 
  日期: 
  函数列表: 
  历史记录: 
 ***********************************************************/
#ifndef _V2X_OBU_DBUS_COMMON_H
#define _V2X_OBU_DBUS_COMMON_H

#define V2X_OBU_DBUS_V2X_OBJECT_PATH "/dbus/obu/v2x"
#define V2X_OBU_DBUS_V2X_BUS_NAME "dbus.obu.v2x"
#define V2X_OBU_DBUS_V2X_INTFACE_NAME "dbus.obu.v2x.interface"

#define V2X_OBU_DBUS_APP_OBJECT_PATH "/dbus/obu/app"
#define V2X_OBU_DBUS_APP_BUS_NAME "dbus.obu.app"
#define V2X_OBU_DBUS_APP_INTFACE_NAME "dbus.obu.app.interface"

#define V2X_OBU_DBUS_VDS_OBJECT_PATH "/dbus/obu/vds"
#define V2X_OBU_DBUS_VDS_BUS_NAME "dbus.obu.vds"
#define V2X_OBU_DBUS_VDS_INTFACE_NAME "dbus.obu.vds.interface"

#define V2X_OBU_DBUS_NET_OBJECT_PATH "/dbus/obu/net"
#define V2X_OBU_DBUS_NET_BUS_NAME "dbus.obu.net"
#define V2X_OBU_DBUS_NET_INTFACE_NAME "dbus.obu.net.interface"

#define V2X_OBU_DBUS_SYS_OBJECT_PATH "/dbus/obu/sys"
#define V2X_OBU_DBUS_SYS_BUS_NAME "dbus.obu.sys"
#define V2X_OBU_DBUS_SYS_INTFACE_NAME "dbus.obu.sys.interface"

/*信号名称*/
#define MSG_V2X_SRV_MSG "V2xSrvMsg"
#define MSG_V2X_SRV_STATE "V2xSrvState"
#define MSG_V2X_SRV_FAULT_PUSH "V2xSrvFaultPush"
#define MSG_V2X_SRV_CONFIG_RS "V2xSrvConfigRs"

#define MSG_APP_RESULT_ACT_SAFE "AppResultActSafe"
#define MSG_APP_RESULT_TRFC_REMIND "AppResultTrfcRemind"
#define MSG_APP_RESULT_SPD_GUIDE "AppResultSpdGuide"
#define MSG_APP_CONFIG_RS "AppConfigRs"
#define MSG_APP_FAULT_PUSH "AppFaultPush"

#define MSG_VDS_VEH_DATA "VdsVehData"
#define MSG_VDS_STATE_PUSH "VdsStatePush"
#define MSG_VDS_FAULT_PUSH "VdsFaultPush"
#define MSG_VDS_MCU_FAULT_PUSH "McuFaultPush"
#define MSG_VDS_MCU_PD_RQ "McuPowerDownRq"
#define MSG_VDS_CONFIG_RS "VdsConfigRs"
#define MSG_MCU_CONFIG_RS "McuConfigRs"


#define MSG_NET_SIM_CAN_DATA  "NetSimCanData"
#define MSG_NET_STATUS  "NetLinkStatus"
#define MSG_NET_CONFIG_RS  "NetConfigRs"
#define MSG_NET_FAULLT   "NetFaultStatus"



#define MSG_SYS_CONFIG_RQ "SysConfigRq"
#define MSG_SYS_MCU_PD_RQ "SysMcuPowerDownRs"

//信号new
#define NEW_V2X_SRV_MSG "v2x_srv_msg"
#define NEW_V2X_SRV_STATE "v2x_srv_state"
#define NEW_V2X_SRV_FAULT_PUSH "v2x_srv_fault_push"
#define NEW_V2X_SRV_CONFIG_RS "v2x_srv_config_rs"

#define NEW_APP_RESULT_ACT_SAFE "app_result_act_safe"
#define NEW_APP_RESULT_TRFC_REMIND "app_result_trfc_remind"
#define NEW_APP_RESULT_SPD_GUIDE "app_result_spd_guide"
#define NEW_APP_CONFIG_RS "app_config_rs"
#define NEW_APP_FAULT_PUSH "app_fault_push"

#define NEW_VDS_VEH_DATA "vds_veh_data"
#define NEW_VDS_STATE_PUSH "vds_state_push"
#define NEW_VDS_FAULT_PUSH "vds_fault_push"
#define NEW_VDS_MCU_FAULT_PUSH "mcu_fault_push"
#define NEW_VDS_MCU_PD_RQ "mcu_power_down_rq"
#define NEW_VDS_CONFIG_RS "vds_config_rs"

#define NEW_NET_SIM_CAN_DATA "net_sim_can_data"
#define NEW_NET_STATUS "net_link_status"
#define NEW_NET_CONFIG_RS "net_config_rs"

#define NEW_SYS_CONFIG_RQ "sys_config_rq"
#define NEW_SYS_MCU_PD_RQ "sys_mcu_power_down_rs"

#endif
