/************************************************************
  文件名: v2x_obu_dbus_common.c
  作者:            
  描述: 定义v2xobu各子模块dbus通讯通用信息     
  版本: 
  日期: 
  函数列表: 1.void g_cclosure_marshal_VOID__UCHARv()
  历史记录: 
 ***********************************************************/
#include <dbus/dbus-glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "v2x_obu_dbus_common.h"

/**/
void g_cclosure_marshal_VOID__UCHARv (GClosure     *closure,
                                 GValue       *return_value,
                                 gpointer      instance,
                                 va_list       args,
                                 gpointer      marshal_data,
                                 int           n_params,
                                 GType        *param_types)
{
  typedef void (*GMarshalFunc_VOID__UCHAR) (gpointer     instance,
                                            guchar       arg_0,
                                            gpointer     data);
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  GMarshalFunc_VOID__UCHAR callback;
  guchar arg0;
  va_list args_copy;

  G_VA_COPY (args_copy, args);
  arg0 = (guchar) va_arg (args_copy, guint);
  va_end (args_copy);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = instance;
    }
  else
    {
      data1 = instance;
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UCHAR) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            arg0,
            data2);
}

