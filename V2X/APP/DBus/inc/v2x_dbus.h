/*
 * @Descripttion: 
 * @version: 
 * @Author: wanji.net.cn
 * @email: mk_wanji@126.com
 * @Date: 2021-12-06 18:05:09
 * @LastEditors: VanJee Technology Co.,Ltd
 * @LastEditTime: 2021-12-06 18:05:09
 */
/*******************************************************************************
 * 文 件 名 称 ： v2x_dbus.h
 * 功 能 描 述 ： v2x模块dbus初始化接口
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/
#ifndef __V2X_GDBUS_H__
#define __V2X_GDBUS_H__

#include <glib-object.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "v2x_obu_dbus_common.h"
#include "V2xBasicTypes.h"

V2X_BEGIN_HEADER

/** thread function's definition */

extern gboolean FV_init_v2x_dbus_communication(void);
extern gboolean FV_deinit_v2x_dbus_communication(void);
extern void FV_DbusMainLoopStart(void);

/*定时器周期*/
#define TIMEOUT_STATE 3000

/*dbus object init*/
typedef struct v2xobu
{
    GObject parent;
} V2xObu;

typedef struct v2xobuclass
{
    GObjectClass parent;
} V2xObuClass;

#define V2X_OBU_TYPE (FV_v2x_obu_get_type())
GType FV_v2x_obu_get_type(void);

/*信号发送接口*/
void FV_emit_v2x_srv_msg(int Msglen, int PortocVersion, int AID);
void FV_emit_v2x_srv_state(void);
void FV_emit_v2x_srv_fault_push(void);
void FV_emit_v2x_srv_cfg_rs(void);
void FV_emit_v2x_net_cooperative(void);

extern V2xObu *g_ptObj;

V2X_END_HEADER

#endif
