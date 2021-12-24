/*******************************************************************************
 * 文 件 名 称 ： Service.h
 * 功 能 描 述 ： 系统状态监控模块
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#ifndef __SERVICE_H__
#define __SERVICE_H__

#include "V2xBasicTypes.h"

V2X_BEGIN_HEADER

typedef struct _PlanpathPoint
{
    uint32_t planpathPointlat;
    uint32_t planpathPointlon;
} PlanpathPoint_t;
typedef struct
{
    uint16_t m_MsgID; // 信号ID
    uint16_t m_MsgLength;
    uint8_t hv_id[8]; // 主车的ID
    // double hv_lat;           // 主车的纬度
    // double hv_lon;           // 主车的经度
    // double hv_ele;           // 主车的海拔
    // double hv_head;          // 车头朝向(0°~360°)，正北为 0，顺时针旋转的角度
    // double hv_speed;         // 本车速度m/s
    uint8_t guideStart;      //引导信息状态 0：引导失败 1：引导成功
    uint8_t collSceType;     //协同场景类型
    uint8_t bootDeviceType;  //引导设备类型  0：目标未知  1：RSU引导 2：OBU引导
    uint8_t bootDeviceId[8]; //引导设备ID
    uint32_t bootDeviceLat;  //引导设备纬度
    uint32_t bootDeviceLng;  //引导设备经度
    uint16_t driving_advice; //驾驶建议
    uint16_t arrival_time;   //到达时间
    uint32_t tarLat;         //路径目标点纬度
    uint32_t tarLon;         //路径目标点经度
    uint8_t planpathpoints;  //规划路径点的数目
    PlanpathPoint_t planpathpoint[WJV2_MAX_LIST_PathPlanning_LEN];
    uint8_t BBC; //奇偶校验位
} __attribute__((packed)) RoadsideCoordination_t;
typedef struct
{
    uint16_t m_MsgID;
    uint16_t m_MsgLength;
    uint8_t m_V2XStackRxState;
    uint8_t m_V2XStackTxState;
    uint8_t m_BSMTxState;
    uint8_t m_CertMState;
    uint8_t m_DbusState;
    uint8_t m_Bcc;
} __attribute__((packed)) TV2xSrvState_t;

#define INIT_V2X_SRV_STATE()       \
    {                              \
        .m_V2XStackTxState = 0xFF, \
        .m_V2XStackRxState = 0xFF, \
        .m_BSMTxState = 0xFF,      \
        .m_CertMState = 0xFF,      \
        .m_DbusState = 0xFF        \
    }

typedef struct
{
    uint16_t m_MsgID;
    uint16_t m_MsgLength;
    uint8_t m_IsAg15ComFault;
    uint8_t m_IsHsmComFault;
    uint8_t m_Bcc;
} __attribute__((packed)) TSrvFaultPush_t;

#define INIT_SRV_FAULT_PUSH()     \
    {                             \
        .m_IsAg15ComFault = 0xFF, \
        .m_IsHsmComFault = 0xFF   \
    }

typedef struct
{
    uint16_t m_MsgID;
    uint16_t m_MsgLength;
    uint8_t m_AppCfgUpdateNotify;
    uint8_t m_V2xCfgUpdateNotify;
    uint8_t m_VdsCfgUpdateNotify;
    uint8_t m_NetCfgUpdateNotify;
    uint8_t m_Bcc;
} __attribute__((packed)) TSrvConfigRs_t;

#define INIT_SRV_CFG_RS()             \
    {                                 \
        .m_AppCfgUpdateNotify = 0xFF, \
        .m_V2xCfgUpdateNotify = 0xFF, \
        .m_VdsCfgUpdateNotify = 0xFF, \
        .m_NetCfgUpdateNotify = 0xFF  \
    }

typedef struct
{
    uint16_t m_MsgID;
    uint16_t m_MsgLength;
    uint8_t m_OnlinecfgRs;
    uint8_t m_Bcc;
} __attribute__((packed)) TSrvConfigRsCb_t;

#define INIT_SRV_CFG_RS_CB()  \
    {                         \
        .m_OnlinecfgRs = 0xFF \
    }

enum
{
    THR_SUSPEND = 0x80,
    THR_RUNNING = 0x82
};

enum
{
    STATE_SUSPENDED = 0x80,
    STATE_READY = 0x81,
    STATE_RUNNING = 0x82,
    STATE_WAITING = 0x83
};

enum
{
    CONFIG_RS_SUCCESS = 0x90,
    CONFIG_RS_FAILURE = 0x91
};

enum
{
    V2X_STACK_CFG_CHG = 0x80,
    V2X_SERVICE_CFG_CHG = 0x81,
};

V2X_END_HEADER

#endif
