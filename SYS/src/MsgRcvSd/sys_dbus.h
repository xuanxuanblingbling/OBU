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
#define S1_TIME_OUT          200
#define S2_TIME_OUT		     200
#define S3_TIME_OUT		     200
#define S4_TIME_OUT		     200

/*dbus object init*/
typedef struct v2xobu
{
  GObject parent;
}V2xObu;

typedef struct v2xobuclass
{
  GObjectClass parent;
}V2xObuClass;
#define V2X_OBU_TYPE  (v2x_obu_get_type ())
GType   v2x_obu_get_type(void);

/*数据结构体*/
typedef struct VehStruct1
{
	uint8_t  data[100];
}VehStruct1;

/*定时器回调接口*/
extern gboolean callback1(gpointer data);
extern gboolean callback2(gpointer data);
/*信号发送接口*/
void sys_emit_message1(V2xObu *obj, GArray *pass);
void sys_emit_message2(V2xObu *obj, GArray *pass);

#endif
