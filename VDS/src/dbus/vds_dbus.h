/************************************************************
  文件名: vds_dbus.h
  作者:            
  描述: vds模块dbus相关定义，接口函数定义
  版本: 
  日期: 
  函数列表:
  历史记录: 
 ***********************************************************/
#ifndef VEH_FEATURES_H
#define VEH_FEATURES_H

#include <glib-object.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/*定时器周期*/
#define VDS_TIME1_OUT        100
#define VDS_TIME2_OUT		     3000
#define VDS_TIME3_OUT		     2000

/*定义信号句柄*/
typedef enum
{
    VDS_VEH_DATA,
    VDS_STATE_PUSH,
    VDS_FAULT_PUSH,
    MCU_FAULT_PUSH,
    MCU_PDOWN_RQ,
    VDS_CONFIG_RS,
    MCU_CONFIG_RS,
    LAST_SIGNAL
}TSignalFd_em;

/*dbus object init*/
typedef struct v2xobu
{
  GObject parent;
}V2xObu;

typedef struct v2xobuclass
{
  GObjectClass parent;
}V2xObuClass;



/*数据结构体*/
typedef struct VehStruct1
{
	uint8_t  data[100];
}VehStruct1;


typedef struct _PadComand{
    uint16_t m_u16Msgid;
    uint16_t m_u16Msglen;
    union 
    {
      uint8_t  m_databuf[32]; //暂定32字节内包含BCC，二期场景命令须跟PAD同步调试
      struct   m_playload{
          uint8_t  m_CMDT;
	        uint8_t  m_CDMT;
	        uint8_t  m_Status;
	        uint16_t m_frameLen;
          uint8_t  m_intent;
          uint32_t m_vaildtime;
      }choice;
    } ;
    
   
}PadComand_st;

/**/
extern V2xObu *obj;
extern GMainLoop *mainloop;
extern guint signals[LAST_SIGNAL];

/*定时器回调接口*/
extern gboolean FD_vds_emit_signal_of_veh_data(gpointer data);
extern gboolean FD_vds_emit_signal_of_state_push(gpointer data);
extern gboolean FD_vds_emit_signal_of_led(gpointer data);
/*信号发送接口*/
extern void v2x_obu_vds_emit_vds_veh_data(V2xObu *obj, GArray *pass);
extern void v2x_obu_vds_emit_vds_state_push(V2xObu *obj, GArray *pass);
extern void v2x_obu_vds_emit_vds_fault_push(V2xObu *obj, GArray *pass);
extern void v2x_obu_vds_emit_mcu_fault_push(V2xObu *obj, GArray *pass);
extern void v2x_obu_vds_emit_mcu_power_down_rq(V2xObu *obj, GArray *pass);
extern void v2x_obu_vds_emit_vds_config_rs(V2xObu *obj, GArray *pass);
//
extern void FD_DbusModuleCreat (void);
extern void FD_DbusModuleInit(void);
extern void DbusGeneralSendFuc(uint8_t *p_data,uint16_t p_len,TSignalFd_em p_sigid);

#endif
