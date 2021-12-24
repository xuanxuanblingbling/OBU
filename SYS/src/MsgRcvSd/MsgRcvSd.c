/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       MsgRcvSd.c
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : MsgRcvSd.c
*   Author:         : wensheng.zhang       2020
********************************************************************************
*   Limitations:      None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version       Date       Initials        CR#        Descriptions
*   -------   ----------  --------------    ------    -------------------
*   01.00.00  07/07/2020  wensheng.zhang      N/A         Original
********************************************************************************
*END_FILE_HDR*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <glib.h>
#include <dbus/dbus-glib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

#include "sys_config.h"
#include "sys_dbus.h"
#include "v2x_obu_dbus_common.h"
#include "wj_log.h"
#include "Cfg.h"
#include "DiagM.h"
#include "CfgM.h"
#include "MsgRcvSd.h"
#include "StateM.h"
//#include "PowerM.h"
#include "WebServerM.h"
#include "MsgRcvSd_Lcfg.h"



G_DEFINE_TYPE(V2xObu, v2x_obu, G_TYPE_OBJECT)

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

/*init*/
static void v2x_obu_init (V2xObu *obj)
{}
static void v2x_obu_class_init (V2xObuClass *klass)
{
    //M51 init
    signals[SYS_CONFIG] = g_signal_new (
        NEW_SYS_CONFIG_RQ,
        G_OBJECT_CLASS_TYPE (klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
    //M52 init
    signals[SYS_MCU_PD] = g_signal_new (
        NEW_SYS_MCU_PD_RQ,
        G_OBJECT_CLASS_TYPE (klass),
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        g_cclosure_marshal_VOID__UCHARv,
        G_TYPE_NONE, 1, DBUS_TYPE_G_UCHAR_ARRAY);
}

/*************************************************
  名称: milliseconds_sleep
  描述: 毫秒级定时器
  输入参数: mSec 毫秒数
  返回值: 无
**************************************************/
void milliseconds_sleep(unsigned long mSec){
    struct timeval tv;
    tv.tv_sec=mSec/1000;
    tv.tv_usec=(mSec%1000)*1000;
    int err;
    do{
       err=select(0,NULL,NULL,NULL,&tv);
    }while(err<0 && errno==EINTR);
}

void MsgM_Send_Fun(uint8_t *DataStruct, int StructLen, int index)
{
	int i = 0;
	int enven_flag = 0;
	int BccPos = 0;
	uint8_t BccValue = 0x0;
	GArray *pass= NULL;//定义GArray变量
	pass = g_array_new(FALSE,TRUE,sizeof(uint8_t));//GArray变量初始化

	switch (index)
    {
        case SYS_CONFIG:
        {
            DataStruct[0] = SYS_CONFIG_RQ_ID&0xff;//id
            DataStruct[1] = (SYS_CONFIG_RQ_ID>>8)&0xff;
            DataStruct[2] = SYSCONFIGRQ_LEN&0xff;//数据长度
            DataStruct[3] = (SYSCONFIGRQ_LEN>>8)&0xff;
        }
     		break;
        case SYS_MCU_PD:
        {
            DataStruct[0] = SYS_MCU_PD_RS_ID&0xff;//id
            DataStruct[1] = (SYS_MCU_PD_RS_ID>>8)&0xff;
            DataStruct[2] = SYSMCUCONFIGRS_LEN&0xff;//数据长度
            DataStruct[3] = (SYSMCUCONFIGRS_LEN>>8)&0xff;
			enven_flag = 1;
        }
        	break;
		default:
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MsgRcvSd MsgM_Send_Fun  index is %d error", index);
			break;
	}
	for(i = 0; i<StructLen-1; i++)
    {
        BccValue ^= DataStruct[i];
    }
	BccPos = StructLen-1;
	DataStruct[BccPos] = BccValue;    //最后一位加上bcc校验位

	g_array_append_vals(pass, DataStruct, StructLen);//将结构体变量赋值给GArray变量
	if(enven_flag)
	{
		enven_flag = 0;
		for ( i = 0; i < EVENT_REPEAT_PUSH_NUM; i++)
		{
			g_signal_emit (obj, signals[index], 0,pass);
			milliseconds_sleep(EVENT_REPEAT_CYCLE_TIME);
		}
	}
	else
	{
		g_signal_emit (obj, signals[index], 0,pass);
	}

    g_array_free(pass,TRUE);//GArray变量空间释放

}

t_MsgMValidityType MsgM_Data_Validity_Judgment(int SignalLen, char * DataBuf, int TagValue)
{
	int BccCalLength=0;
	int DataLen = 0;
	int SignalDataLength = 0;
	int Index = 0;
	int BccValue = 0;
	int BccPos = 0;
	int SigTagValue = 0;

	memcpy(&SigTagValue, &DataBuf[MSGM_TAG_POS], MSGM_TAG_BYTE_SIZE);
	if(SigTagValue != TagValue)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM Tag invalid . receive is %d, current is %d", TagValue, SigTagValue);
		return MSGM_INVALID;
	}

	DataLen = SignalLen - MSGM_TAG_BYTE_SIZE - MSGM_LENGTH_BYTE_SIZE - MSGM_BCC_BYTE_SIZE;
	memcpy(&SignalDataLength, &DataBuf[MSGM_LENGTH_POS], MSGM_LENGTH_BYTE_SIZE);
	if(DataLen != SignalDataLength)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM data Length invalid:TagValue is %d CalLen-%d, DataLen-%d",TagValue, DataLen, SignalDataLength);
		return MSGM_INVALID;
	}

	BccCalLength = MSGM_TAG_BYTE_SIZE + MSGM_LENGTH_BYTE_SIZE + DataLen;
    while(Index < BccCalLength)
    {
        BccValue ^= DataBuf[Index];
        Index++;
    }

	BccPos = SignalLen-1;
	if(BccValue != DataBuf[BccPos])
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM bcc verification failed.");
		return MSGM_INVALID;
	}
	
	return MSGM_VALID;
}

static void MsgM_VDS_Data_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	t_MsgMValidityType ret;
	MsgMonitor_Json MsgMonitorJson;
	int speed = 0;
	StateM_Json StateMJson;
	uint32_t ValueTmp;
	struct timeval tv;
	long microsecond;
	time_t ti;
	char time_tmp[20];

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_VDS_VEHDATA_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM VDS data receive format error");
	else
	{
		/* 2.填充数据 */
		GET_JSON_STRUCT(MSGMONITOR_JSON_STRUCT, &MsgMonitorJson);
		MsgMonitorJson.Tag = MSGMONITOR_1001;
		gettimeofday(&tv, NULL);
		ti = tv.tv_sec;
		microsecond = tv.tv_usec/1000;
		memset(time_tmp, 0, sizeof(time_tmp));
		strftime(time_tmp, 20, "%Y.%m.%d %H:%M:%S", localtime(&ti));
		snprintf(MsgMonitorJson.TimeBuf, 30, "%s:%ld", time_tmp, microsecond);

		memcpy(&MsgMonitorJson.SignalValue, &pass->data[MSGM_VDS_DATA_POS], MSGM_VDS_DATA_LEN);
		/* 填充速度 */
		GET_JSON_STRUCT(DIAGCFG_SPEED_INT, &speed);
		memcpy(&speed, &pass->data[MSGM_VDS_DATA_SPEED_POS], MSGM_VDS_DATA_SPEED_LEN);
		SET_JSON_STRUCT(DIAGCFG_SPEED_INT, &speed);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "MsgM_VDS_Data_Rcv_Fun  speed receive is %d", speed);

		/* 填充经纬度 */
		GET_JSON_STRUCT(STATECFG_JSON_STRUCT, &StateMJson);
		memcpy(&ValueTmp, &pass->data[MSGM_VDS_LATITUDE_STATE_POS], MSGM_VDS_LATITUDE_STATE_LEN);
		snprintf(StateMJson.VdsState.Latitude, 20, "%.7f", ValueTmp/10000000.0);
		memcpy(&ValueTmp, &pass->data[MSGM_VDS_LONGITUDE_STATE_POS], MSGM_VDS_LONGITUDE_STATE_LEN);
		snprintf(StateMJson.VdsState.Longitude, 20, "%.7f", ValueTmp/10000000.0);
		SET_JSON_STRUCT(STATECFG_JSON_STRUCT, &StateMJson);
		
		/* 3.设置结构体 */
		SET_JSON_STRUCT(MSGMONITOR_JSON_STRUCT, &MsgMonitorJson);

		/* 4. 通知状态管理 */
		SET_SIGNAL_B(MSG_MONITOR_RCV);
	}
}


static void MsgM_VDS_State_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	t_MsgMValidityType ret;
	StateM_Json  tStateMJson;
	int     ValueTmp;

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_VDS_STATE_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM VDS STATE data format error");
	else
	{
		/* 2.填充结构体 */
		GET_JSON_STRUCT(STATECFG_JSON_STRUCT, &tStateMJson);
		tStateMJson.Keyid |= STATEM_VDSSTATE_TYPE;
		memcpy(&tStateMJson.VdsState.DataDEcode, &pass->data[MSGM_VDS_DATADECODE_STATE_POS], MSGM_VDS_DATADECODE_STATE_LEN);
		memcpy(&tStateMJson.VdsState.CANSend, &pass->data[MSGM_VDS_MCUSD_STATE_POS], MSGM_VDS_MCUSD_STATE_LEN);
		memcpy(&tStateMJson.VdsState.CANRcv, &pass->data[MSGM_VDS_MCURCV_STATE_POS], MSGM_VDS_MCURCV_STATE_LEN);
		memcpy(&tStateMJson.VdsState.GnssRcv, &pass->data[MSGM_VDS_GNSSRCV_STATE_POS], MSGM_VDS_GNSSRCV_STATE_LEN);
		memcpy(&tStateMJson.VdsState.GnssStatus, &pass->data[MSGM_VDS_GNSS_STATE_POS], MSGM_VDS_GNSS_STATE_LEN);
		memcpy(&tStateMJson.VdsState.SatelliteslockedNum, &pass->data[MSGM_VDS_QTYSVUSED_STATE_POS], MSGM_VDS_QTYSVUSED_STATE_LEN);
		LogPrint(LOG_LEVEL_NOTICE, LOG_MODLE_NAME, "MSGM VDS GNSS State is :%d",tStateMJson.VdsState.GnssStatus);
		memcpy(&ValueTmp, &pass->data[MSGM_VDS_LATITUDEINT_STATE_POS], MSGM_VDS_LATITUDEINT_STATE_LEN);
		snprintf(tStateMJson.VdsState.Latitude, 20, "%.7f", ValueTmp/10000000.0);
		memcpy(&ValueTmp, &pass->data[MSGM_VDS_LONGTUDEINT_STATE_POS], MSGM_VDS_LONGTUDEINT_STATE_LEN);
		snprintf(tStateMJson.VdsState.Longitude, 20, "%.7f", ValueTmp/10000000.0);
		

		/* 3.设置结构体 */
		SET_JSON_STRUCT(STATECFG_JSON_STRUCT, &tStateMJson);

		/* 4.通知数据收到 */
		SET_SIGNAL_B(STATE_RCV_NOTIFY);
	}
}

static void MsgM_VDS_DTC_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	t_MsgMValidityType ret;
	DiagM_Json	   tDiagJson;

	printf("====[test] Recive vds fault =====\n");

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_VDS_DTC_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM VDS DTC data format error");
	else
	{	
		/* 2.填充结构体 */
		GET_JSON_STRUCT(DIAGCFG_JSON_STRUCT, &tDiagJson);
		tDiagJson.Keyid |= DIAGM_VDS_TYPE;
		memcpy(&tDiagJson.Diag_VDS.CANError.DiagVal, &pass->data[MSGM_VDS_AG35COM_DTC_POS], MSGM_VDS_AG35COM_DTC_LEN);
		memcpy(&tDiagJson.Diag_VDS.GPSError.DiagVal, &pass->data[MSGM_VDS_GNSSCOM_DTC_POS], MSGM_VDS_GNSSCOM_DTC_LEN);
        		
		/* 3.设置结构体 */
		SET_JSON_STRUCT(DIAGCFG_JSON_STRUCT, &tDiagJson);

		/* 4.通知数据收到 */
		SET_SIGNAL_B(DIAG_PARAMETER_RCV_NOTIFY);
	}
}

static void MsgM_MCU_DTC_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
#if 0	
	t_MsgMValidityType ret;
	DiagM_Json	   tDiagJson;

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_MCU_DTC_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM MCU DTC data format error");
	else
	{
		/* 2.填充结构体 */
		GET_JSON_STRUCT(DIAGCFG_JSON_STRUCT, &tDiagJson);
		tDiagJson.Keyid |= DIAGM_MCU_TYPE;
		memcpy(&tDiagJson.Diag_Mcu.CanBusOff.DiagVal, &pass->data[MSGM_MCU_CANBUSOFF_DTC_POS], MSGM_MCU_CANBUSOFF_DTC_LEN);
		memcpy(&tDiagJson.Diag_Mcu.HighVoltage.DiagVal, &pass->data[MSGM_MCU_HIGHVOLTAGE_DTC_POS], MSGM_MCU_HIGHVOLTAGE_DTC_LEN);
		memcpy(&tDiagJson.Diag_Mcu.LowVoltage.DiagVal, &pass->data[MSGM_MCU_LOWVOLTAGE_DTC_POS], MSGM_MCU_LOWVOLTAGE_DTC_LEN);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(DIAGCFG_JSON_STRUCT, &tDiagJson);

		/* 4.通知数据收到 */
		SET_SIGNAL_B(DIAG_PARAMETER_RCV_NOTIFY);
	}
#endif
}

static void MsgM_MCU_PowerRq_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
#if 0
	t_MsgMValidityType ret;
	PowerM_PwrRq PwrDwnRqData;

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_MCU_POWRQ_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM MCU powerRq data format error");
	else
	{
		/* 2.填充数据 */
		GET_JSON_STRUCT(MCU_PWRDWN_RQ_STRUCT, &PwrDwnRqData);
		memcpy(&PwrDwnRqData.PowerRqValue, &pass->data[MSGM_MCU_PWRDWN_RQ_POS], MSGM_MCU_PWRDWN_RQ_LEN);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(MCU_PWRDWN_RQ_STRUCT, &PwrDwnRqData);

		/* 4.通知电源管理模块 */
		SET_SIGNAL_B(POWER_DOWN_RQ);
	}
#endif
}

static void MsgM_VDS_CfgResp_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	t_MsgMValidityType ret;
	CfgM_Resp CfgMResp;
	

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_VDS_CFGRESP_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM VDS config response format error");
	else
	{
		/* 2.填充数据 */
		GET_JSON_STRUCT(CFGM_RESP_STRUCT, &CfgMResp);
		CfgMResp.RespId |= CFGM_VDS_RESP;
		memcpy(&CfgMResp.tVdsCfgResp.McuCfgResp, &pass->data[MSGM_MCU_CFG_RESP_POS], MSGM_MCU_CFG_RESP_LEN);
		memcpy(&CfgMResp.tVdsCfgResp.VdsCfgResp, &pass->data[MSGM_VDS_CFG_RESP_POS], MSGM_VDS_CFG_RESP_LEN);
		memcpy(&CfgMResp.tVdsCfgResp.Ag35CfgResp, &pass->data[MSGM_AG35_CFG_RESP_POS], MSGM_AG35_CFG_RESP_LEN);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, &CfgMResp);

		/* 4.通知配置管理模块 */
		SET_SIGNAL_B(PARAMETER_CFG_SYS_RESP);
	}
}

static void MsgM_MCU_CfgResp_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
#if 0
	t_MsgMValidityType ret;
	CfgM_Json  tCfgMJson;

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_MCU_CFGRESP_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM MCU config response format error");
	else
	{
		/* 2.填充结构体 */
		GET_JSON_STRUCT(CFGM_JSON_STRUCT, &tCfgMJson);
		
		tCfgMJson.CfgFileId |= MCUCFG_FILE;
		memset(&tCfgMJson.MCUCfg, 0, sizeof(CfgM_MCUCfg));	
		memcpy(&tCfgMJson.MCUCfg.PwrUpDlyTime, &pass->data[MSGM_MCUCFG_PWRUP_DELAYTIME_POS], MSGM_MCUCFG_PWRUP_DELAYTIME_LEN);
		memcpy(&tCfgMJson.MCUCfg.PwrUpDlyTimeFlag, &pass->data[MSGM_MCUCFG_PWRUP_DELAYTIME_FLAG_POS], MSGM_MCUCFG_PWRUP_DELAYTIME_FLAG_LEN);
		memcpy(&tCfgMJson.MCUCfg.DiagDlyTime, &pass->data[MSGM_MCUCFG_DIAG_DELAYTIME_POS], MSGM_MCUCFG_DIAG_DELAYTIME_LEN);
		memcpy(&tCfgMJson.MCUCfg.DiagDlyTimeFlag, &pass->data[MSGM_MCUCFG_DIAG_DELAYTIME_FLAG_POS], MSGM_MCUCFG_DIAG_DELAYTIME_FLAG_LEN);
		memcpy(&tCfgMJson.MCUCfg.DiagVoltRangeMin, &pass->data[MSGM_MCUCFG_DIAG_VMIN_POS], MSGM_MCUCFG_DIAG_VMIN_LEN);
		memcpy(&tCfgMJson.MCUCfg.DiagVoltRangeMinFlag, &pass->data[MSGM_MCUCFG_DIAG_VMIN_FLAG_POS], MSGM_MCUCFG_DIAG_VMIN_FLAG_LEN);
		memcpy(&tCfgMJson.MCUCfg.DiagVoltRangeMax, &pass->data[MSGM_MCUCFG_DIAG_VMAX_POS], MSGM_MCUCFG_DIAG_VMAX_LEN);
		memcpy(&tCfgMJson.MCUCfg.DiagVoltRangeMaxFlag, &pass->data[MSGM_MCUCFG_DIAG_VMAX_FLAG_POS], MSGM_MCUCFG_DIAG_VMAX_FLAG_LEN);
		memcpy(&tCfgMJson.MCUCfg.DiagHystsVoltUp, &pass->data[MSGM_MCUCFG_DIAG_VUP_DELAY_POS], MSGM_MCUCFG_DIAG_VUP_DELAY_LEN);
		memcpy(&tCfgMJson.MCUCfg.DiagHystsVoltUpFlag, &pass->data[MSGM_MCUCFG_DIAG_VUP_DELAY_FLAG_POS], MSGM_MCUCFG_DIAG_VUP_DELAY_FLAG_LEN);
		memcpy(&tCfgMJson.MCUCfg.DiagHystsVoltDown, &pass->data[MSGM_MCUCFG_DIAG_VDOME_DELAY_POS], MSGM_MCUCFG_DIAG_VDOME_DELAY_LEN);
		memcpy(&tCfgMJson.MCUCfg.DiagHystsVoltDownFlag, &pass->data[MSGM_MCUCFG_DIAG_VDOME_DELAY_FLAG_POS], MSGM_MCUCFG_DIAG_VDOME_DELAY_FLAG_LEN);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(CFGM_JSON_STRUCT, &tCfgMJson);
		/* 4.通知数据收到 */
		SET_SIGNAL_B(PARAMETER_CFG_SYS_RESP);
	}
#endif
}

static void MsgM_V2X_State_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	t_MsgMValidityType ret;
	StateM_Json  tStateMJson;     

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_V2X_STATE_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM V2X state data format error");
	else
	{
		/* 2.填充结构体 */
		GET_JSON_STRUCT(STATECFG_JSON_STRUCT, &tStateMJson);
		tStateMJson.Keyid |= STATEM_V2XSTATE_TYPE;
		memcpy(&tStateMJson.V2XState.V2XStackTx, &pass->data[MSGM_V2X_V2XSTACKTX_STATE_POS], MSGM_V2X_V2XSTACKTX_STATE_LEN);
		memcpy(&tStateMJson.V2XState.V2XStackRx, &pass->data[MSGM_V2X_V2XSTACKRX_STATE_POS], MSGM_V2X_V2XSTACKRX_STATE_LEN);
		memcpy(&tStateMJson.V2XState.BSMTx, &pass->data[MSGM_V2X_BSMTX_STATE_POS], MSGM_V2X_BSMTX_STATE_LEN);
		memcpy(&tStateMJson.V2XState.CertM, &pass->data[MSGM_V2X_CERTM_STATE_POS], MSGM_V2X_CERTM_STATE_LEN);
		memcpy(&tStateMJson.V2XState.DbusInterface, &pass->data[MSGM_V2X_DBUSINTERFACE_STATE_POS], MSGM_V2X_DBUSINTERFACE_STATE_LEN);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(STATECFG_JSON_STRUCT, &tStateMJson);
		/* 4.通知数据收到 */
		SET_SIGNAL_B(STATE_RCV_NOTIFY);
	}
}

static void MsgM_V2X_DTC_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	DiagM_Json	   tDiagJson;
	t_MsgMValidityType ret;

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_V2X_DTC_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM V2X DTC data format error");
	else
	{
		/* 2.填充结构体 */
		GET_JSON_STRUCT(DIAGCFG_JSON_STRUCT, &tDiagJson);
		tDiagJson.Keyid |= DIAGM_V2X_TYPE;
		memcpy(&tDiagJson.Diag_V2X.AG15ComError.DiagVal, &pass->data[MSGM_V2X_AG15Com_DTC_POS], MSGM_V2X_AG15Com_DTC_LEN);
		memcpy(&tDiagJson.Diag_V2X.HSMError.DiagVal, &pass->data[MSGM_V2X_HSM_DTC_POS], MSGM_V2X_HSM_DTC_LEN);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(DIAGCFG_JSON_STRUCT, &tDiagJson);
		/* 4.通知数据收到 */
		SET_SIGNAL_B(DIAG_PARAMETER_RCV_NOTIFY);
	}
}

static void MsgM_V2X_CfgResp_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	t_MsgMValidityType ret;
	CfgM_Resp CfgMResp;

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_V2X_CFGRESP_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM V2X config response format error");
	else
	{
		/* 2.填充数据 */
		GET_JSON_STRUCT(CFGM_RESP_STRUCT, &CfgMResp);
		CfgMResp.RespId |= CFGM_V2X_RESP;
		memcpy(&CfgMResp.tV2xCfgResp.V2xCfgResp, &pass->data[MSGM_V2X_CFG_RESP_POS], MSGM_V2X_CFG_RESP_LEN);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, &CfgMResp);

		/* 4.通知配置管理模块 */
		SET_SIGNAL_B(PARAMETER_CFG_SYS_RESP);
	}
}

static void MsgM_APP_CfgResp_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	t_MsgMValidityType ret;
	CfgM_Resp CfgMResp;

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_APP_CFGRESP_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM APP config response format error");
	else
	{
		/* 2.填充数据 */
		GET_JSON_STRUCT(CFGM_RESP_STRUCT, &CfgMResp);
		CfgMResp.RespId |= CFGM_APP_RESP;
		memcpy(&CfgMResp.tAppCfgResp.AppCfgResp, &pass->data[MSGM_APP_CFG_RESP_POS], MSGM_APP_CFG_RESP_LEN);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, &CfgMResp);

		/* 4.通知配置管理模块 */
		SET_SIGNAL_B(PARAMETER_CFG_SYS_RESP);
	}
}

static void MsgM_APP_DTC_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	t_MsgMValidityType ret;
	DiagM_Json	   tDiagJson;

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_APP_DTC_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM APP DTC data format error");
	else
	{
		/* 2.填充结构体 */
		GET_JSON_STRUCT(DIAGCFG_JSON_STRUCT, &tDiagJson);
		tDiagJson.Keyid |= DIAGM_APP_TYPE;
		memcpy(&tDiagJson.Diag_App.GpsDataError.DiagVal, &pass->data[MSGM_APP_GPSDATA_DTC_POS], MSGM_APP_GPSDATA_DTC_LEN);
		memcpy(&tDiagJson.Diag_App.CanDataError.DiagVal, &pass->data[MSGM_APP_CANDATA_DTC_POS], MSGM_APP_CANDATA_DTC_LEN);
		memcpy(&tDiagJson.Diag_App.RsuDataError.DiagVal, &pass->data[MSGM_APP_RSUDATA_DTC_POS], MSGM_APP_RSUDATA_DTC_LEN);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(DIAGCFG_JSON_STRUCT, &tDiagJson);
		/* 4.通知数据收到 */
		SET_SIGNAL_B(DIAG_PARAMETER_RCV_NOTIFY);
	}
}

static void MsgM_NET_State_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	t_MsgMValidityType ret;
	StateM_Json  tStateMJson;
	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_NET_STATE_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM NET state data format error");
	else
	{

		
		/* 2.填充结构体 */
		GET_JSON_STRUCT(STATECFG_JSON_STRUCT, &tStateMJson);
		tStateMJson.Keyid |= STATEM_NETSTATE_TYPE;
		memcpy(&tStateMJson.NetState.LinkClientNum, &pass->data[MSGM_NET_LINKCLIENTNUM_STATE_POS], MSGM_NET_LINKCLIENTNUM_STATE_LEN);
		memcpy(&tStateMJson.NetState.TcpRcvNum, &pass->data[MSGM_NET_TCPRCVNUM_STATE_POS], MSGM_NET_TCPRCVNUM_STATE_LEN);
		memcpy(&tStateMJson.NetState.TcpSdNum, &pass->data[MSGM_NET_TCPSDNUM_STATE_POS], MSGM_NET_TCPSDNUM_STATE_LEN);
		memcpy(&tStateMJson.NetState.UdpSdNum, &pass->data[MSGM_NET_UDPSDNUM_STATE_POS], MSGM_NET_UDPSDNUM_STATE_LEN);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(STATECFG_JSON_STRUCT, &tStateMJson);
		/* 4.通知数据收到 */
		SET_SIGNAL_B(STATE_RCV_NOTIFY);
	}
}

static void MsgM_NET_CfgResp_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	t_MsgMValidityType ret;
	CfgM_Resp CfgMResp;

	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_NET_CFGRESP_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM NET config response format error");
	else
	{
		/* 2.填充数据 */
		GET_JSON_STRUCT(CFGM_RESP_STRUCT, &CfgMResp);
		CfgMResp.RespId |= CFGM_NET_RESP;
		memcpy(&CfgMResp.tAppCfgResp.AppCfgResp, &pass->data[MSGM_NET_CFG_RESP_POS], MSGM_NET_CFG_RESP_LEN);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(CFGM_RESP_STRUCT, &CfgMResp);

		/* 4. 通知状态管理 */
		SET_SIGNAL_B(PARAMETER_CFG_SYS_RESP);
	}
}

static void MsgM_NET_Fault_Rcv_Fun(DBusGProxy *proxy, GArray *pass, gpointer user_data)
{
	t_MsgMValidityType  ret;
	DiagM_Json	     tDiagJson;
    
	printf("====[test] Recived NET FAULT ==\n");
	/* 1.判断数据有效性 */
	ret = MsgM_Data_Validity_Judgment(pass->len, pass->data, MSGM_NET_FAULT_TAG);
	if(ret == MSGM_INVALID)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM APP DTC data format error");
	else
	{
		/* 2.填充结构体 */
		GET_JSON_STRUCT(DIAGCFG_JSON_STRUCT, &tDiagJson);
		tDiagJson.Keyid |= DIAGM_NET_TYPE;
		memcpy(&tDiagJson.Diag_Net.PadError.DiagVal, &pass->data[MSGM_NET_PAD_FAULT_POS], MSGM_NET_PAD_FAULT_LEN);
		memcpy(&tDiagJson.Diag_Net.HTTPError.DiagVal, &pass->data[MSGM_NET_HTTP_FAULT_POS], MSGM_NET_HTTP_FAULT_LEN);

		printf("====[test] recieve HTTP %d  PAD %d ====\n",tDiagJson.Diag_Net.PadError.DiagVal,tDiagJson.Diag_Net.HTTPError.DiagVal);
		printf("====[test] recieve %d %d %d %d HTTP %d  PAD %d ====\n",pass->data[0],pass->data[1],pass->data[2],pass->data[3],pass->data[4],pass->data[5]);

		/* 3.设置结构体 */
		SET_JSON_STRUCT(DIAGCFG_JSON_STRUCT, &tDiagJson);
		/* 4.通知数据收到 */
		SET_SIGNAL_B(DIAG_PARAMETER_RCV_NOTIFY);
	}
}

void MsgM_Signal_Monitor(DBusGConnection *bus)
{
    DBusGProxy *vds_object;
    DBusGProxy *v2x_object;
    DBusGProxy *app_object;

    //连接VDS节点
    vds_object = dbus_g_proxy_new_for_name (bus, V2X_OBU_DBUS_VDS_BUS_NAME,//节点名称
        V2X_OBU_DBUS_VDS_OBJECT_PATH, //节点路径
        V2X_OBU_DBUS_VDS_INTFACE_NAME); //接口名称
    if (!vds_object)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM Failed to get VDS name owner");

    //监听VDS信号
    dbus_g_proxy_add_signal (vds_object, MSG_VDS_VEH_DATA,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (vds_object, MSG_VDS_VEH_DATA, G_CALLBACK (MsgM_VDS_Data_Rcv_Fun), NULL, NULL);
    dbus_g_proxy_add_signal (vds_object, MSG_VDS_STATE_PUSH,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (vds_object, MSG_VDS_STATE_PUSH, G_CALLBACK (MsgM_VDS_State_Rcv_Fun), NULL, NULL);
    dbus_g_proxy_add_signal (vds_object, MSG_VDS_FAULT_PUSH,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (vds_object,MSG_VDS_FAULT_PUSH, G_CALLBACK (MsgM_VDS_DTC_Rcv_Fun), NULL, NULL);
    dbus_g_proxy_add_signal (vds_object, MSG_VDS_CONFIG_RS,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (vds_object, MSG_VDS_CONFIG_RS, G_CALLBACK (MsgM_VDS_CfgResp_Rcv_Fun), NULL, NULL);

    dbus_g_proxy_add_signal (vds_object, MSG_VDS_MCU_FAULT_PUSH,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (vds_object, MSG_VDS_MCU_FAULT_PUSH, G_CALLBACK (MsgM_MCU_DTC_Rcv_Fun), NULL, NULL);  //回调无代码
    dbus_g_proxy_add_signal (vds_object, MSG_VDS_MCU_PD_RQ,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (vds_object, MSG_VDS_MCU_PD_RQ, G_CALLBACK (MsgM_MCU_PowerRq_Rcv_Fun), NULL, NULL);   //回调无代码
	dbus_g_proxy_add_signal (vds_object, MSG_MCU_CONFIG_RS,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (vds_object, MSG_MCU_CONFIG_RS, G_CALLBACK (MsgM_MCU_CfgResp_Rcv_Fun), NULL, NULL);  //回调无代码
    
    //连接V2X节点
    v2x_object = dbus_g_proxy_new_for_name (bus, V2X_OBU_DBUS_V2X_BUS_NAME,//节点名称
        V2X_OBU_DBUS_V2X_OBJECT_PATH, //节点路径
        V2X_OBU_DBUS_V2X_INTFACE_NAME); //接口名称
    if (!v2x_object)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM Failed to get V2X name owner");
    //监听V2X信号
    dbus_g_proxy_add_signal (v2x_object, MSG_V2X_SRV_STATE,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (v2x_object, MSG_V2X_SRV_STATE, G_CALLBACK (MsgM_V2X_State_Rcv_Fun), NULL, NULL);
    dbus_g_proxy_add_signal (v2x_object, MSG_V2X_SRV_FAULT_PUSH,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (v2x_object, MSG_V2X_SRV_FAULT_PUSH, G_CALLBACK (MsgM_V2X_DTC_Rcv_Fun), NULL, NULL);
    dbus_g_proxy_add_signal (v2x_object, MSG_V2X_SRV_CONFIG_RS,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (v2x_object, MSG_V2X_SRV_CONFIG_RS, G_CALLBACK (MsgM_V2X_CfgResp_Rcv_Fun), NULL, NULL);

    //连接APP节点
    app_object = dbus_g_proxy_new_for_name (bus, V2X_OBU_DBUS_APP_BUS_NAME,//节点名称
        V2X_OBU_DBUS_APP_OBJECT_PATH, //节点路径
        V2X_OBU_DBUS_APP_INTFACE_NAME); //接口名称
    if (!app_object)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM Failed to get APP name owner");
    //监听APP信号
    dbus_g_proxy_add_signal (app_object, MSG_APP_CONFIG_RS,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (app_object, MSG_APP_CONFIG_RS, G_CALLBACK (MsgM_APP_CfgResp_Rcv_Fun), NULL, NULL);
    dbus_g_proxy_add_signal (app_object, MSG_APP_FAULT_PUSH,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (app_object, MSG_APP_FAULT_PUSH, G_CALLBACK (MsgM_APP_DTC_Rcv_Fun), NULL, NULL);
    
    //连接NET节点
    app_object = dbus_g_proxy_new_for_name (bus, V2X_OBU_DBUS_NET_BUS_NAME,//节点名称
        V2X_OBU_DBUS_NET_OBJECT_PATH, //节点路径
        V2X_OBU_DBUS_NET_INTFACE_NAME); //接口名称
    if (!app_object)
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM Failed to get NET name owner");
    //监听NET信号
    dbus_g_proxy_add_signal (app_object, MSG_NET_STATUS,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (app_object, MSG_NET_STATUS, G_CALLBACK (MsgM_NET_State_Rcv_Fun), NULL, NULL);
    dbus_g_proxy_add_signal (app_object, MSG_NET_CONFIG_RS,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (app_object, MSG_NET_CONFIG_RS, G_CALLBACK (MsgM_NET_CfgResp_Rcv_Fun), NULL, NULL);
	dbus_g_proxy_add_signal (app_object, MSG_NET_FAULLT,DBUS_TYPE_G_UCHAR_ARRAY, G_TYPE_INVALID);
    dbus_g_proxy_connect_signal (app_object, MSG_NET_FAULLT, G_CALLBACK (MsgM_NET_Fault_Rcv_Fun), NULL, NULL);
  
}



void MsgM_RcvSd_Main()
{
    DBusGConnection *bus;
    DBusGProxy *bus_proxy;
    GError *error = NULL;
    GMainLoop *mainloop;
    guint request_name_result;

    g_type_init ();
    dbus_g_object_type_install_info (V2X_OBU_TYPE, &dbus_glib__object_info);
    mainloop = g_main_loop_new (NULL, FALSE);

    //获取DBUS_BUS_SESSION 句柄
    bus = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
    if (!bus)
    {
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM Couldn't connect to system bus");
    }
    //链接DBUS总线上某节点
    bus_proxy = dbus_g_proxy_new_for_name (bus, "org.freedesktop.DBus","/", "org.freedesktop.DBus");
    //调用org.freedesktop.DBus节点的RequestName方法，创建org.freesmartphone.sysmd节点
    if (!dbus_g_proxy_call (bus_proxy, "RequestName", &error,
				        G_TYPE_STRING, V2X_OBU_DBUS_SYS_BUS_NAME,
				        G_TYPE_UINT, 0,
				        G_TYPE_INVALID,
				        G_TYPE_UINT, &request_name_result,
				        G_TYPE_INVALID))
    {
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "Failed to acquire org.freesmartphone.sysmd\n");
    }
						
    //信号监听
    MsgM_Signal_Monitor(bus); 
    //注册一个object
    obj = g_object_new (V2X_OBU_TYPE, NULL);
    dbus_g_connection_register_g_object (bus, V2X_OBU_DBUS_SYS_OBJECT_PATH, G_OBJECT (obj));

	LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "MSGM start running");
    g_main_loop_run(mainloop);
	LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "MSGM abnormal exit");
    exit (0);
}


