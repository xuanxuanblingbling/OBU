/***********************************************************************
 * 文 件 名 称 ： DataBaseIf.h
 * 功 能 描 述 ： 向外部提供数据库的头文件
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-24 V1.0    黄赛   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
#ifndef __DATABASEIF_H__
#define __DATABASEIF_H__
/**********************  头文件包含  ********************************/
#include "MiscIf.h"
/********************** 宏定义 *************************************/
/* 数据库表类型定义 */
#define TRXBLOCK_TYPE   1
#define CER_TYPE        2
#define ALG_TYPE        3
#define DEVSTATE_TYPE   4
#define DEVFAULT_TYPE   5
#define SENSINGDEVICESDATE_TYPE   6
/* 消息类型个数 */
#define MSGTYPE_SIZE 10
/* 收发消息码流长度的最大值 */
#define MAX_RCVSND_NUM 2000
/* 证书摘要hash值最大值 */
#define MAX_HASH_SIZE   48
/* 私钥内容长度最大值 */
#define MAX_PRIVATEKET_SIZE   48
/* 证书内容长度最大值 */
#define MAX_CERDATA_NUM 1024
/* 算法名占用的最大字节数 */
#define MAX_ALGNAME_SIZE 10
/* 设备ID占用的最大字节数 */
#define MAX_DEVID_SIZE 20
/* IP地址占用最大字节数 */
#define MAX_IPADDR_SIZE 20
/* 硬件版本占用最大字节数 */
#define MAX_HARDVER_SIZE 20
/* 系统版本占用最大字节数 */
#define MAX_SYSVER_SIZE 20
/* 软件版本占用字节数 */
#define MAX_SOFTVER_SIZE 20
/* 故障时间占用最大字节数 */
#define MAX_FALUTTIME_SIZE 20
/* 查找字段的最大长度 */
#define MAX_SELECT_FILD_LEN 40
/* 插入最大条数 */
#define MAX_INSERT_NUM  1000
/********************** 类型重定义 **********************************/
/********************** 数据库表定义 ********************************/
/* 收发消息表 */
typedef struct  _RXMessage
{
    uint64      m_u64Rele_SN;                     /* 数据条数 按照天数 不小于 24*60*60*10 */
    uint32      m_u32TRX;                         /* 数据是被RSU发送，还是被RSU接收 */
    int8        m_na8MsgType[MSGTYPE_SIZE];        /* V2X消息类型 */
    uint64      m_u64Sig_StartTime;               /* 签名起始时间，单位为us，距离1970年1月1日0时的us数，下同 */
    uint64      m_u64Sig_EndTime;                 /* 签名结束时间，单位为us */
    uint64      m_u64Verify_StratTime;            /* 验签起始时间，单位为us */
    uint64      m_u64Verify_EndTime;              /* 验签结束时间，单位为us */
    uint64      m_u64Data_RecvTime;               /* 数据收到时间，单位为us */
    uint64      m_u64Data_SendTime;               /* 数据发送时间，单位为us */
    uint64      m_u64Trans_StartTime;             /* 转发起始时间，单位为us */
    uint64      m_u64Trans_EndTime;               /* 转发结束时间，单位为us */
    uint32      m_u32DataLen;                     /* 收到消息的长度 */
    int8        m_na8Data[MAX_RCVSND_NUM];         /* 原始数据码流 */
    int8        m_na8reserved[MAX_U8VALUE];        /* 预留 */
}__attribute__ ((packed)) RXMessage_t;
/* 安全证书表 */
typedef struct _Cer
{
    uint32      m_u32CerType;                         /* 证书类型 */
    uint32      m_u32Sec_SN;                          /* 某一类型证书下的序号 */
    uint32      m_u32Encry_State;                     /* 证书内容是否加密 */
    int8        m_na8Hash[MAX_HASH_SIZE];              /* 暂时固定长度为32 证书摘要 */
    int8        m_na8Private_KEY[MAX_PRIVATEKET_SIZE]; /* 暂时固定长度为32 私钥内容 */
    uint32      m_u32CerDataLen;                      /* 指定证书内容长度 */
    int8        m_na8Cer_Data[MAX_CERDATA_NUM];        /* 具体证书内容 */
    int8        m_na8reserved[MAX_U8VALUE];            /* 预留 */
}__attribute__ ((packed)) Cer_t;
/* 算法表 */
typedef struct _Alg
{
    int8        m_na8Alg_Name[MAX_ALGNAME_SIZE];   /* 算法名称 */
    uint32      m_u32Value;                       /* 算法值 */
    int8        m_na8Reserved[MAX_U8VALUE];        /* 预留 */
}__attribute__ ((packed)) Alg_t;
/* 设备状态表 */
typedef struct _DevState
{
    int8        m_na8DevID[MAX_DEVID_SIZE];                /* 设备ID */
    int8        m_na8IP[MAX_IPADDR_SIZE];                  /* 设备IP */
    int8        m_na8HardVer[MAX_HARDVER_SIZE];            /* 硬件版本 */
    int8        m_na8SystemVer[MAX_SYSVER_SIZE];           /* 系统版本 */
    int8        m_na8SoftVer[MAX_SOFTVER_SIZE];            /* 软件版本 */
    uint32      m_u32DevTemperature;                      /* 设备温度 */
    uint32      m_u32Gnss_unavailable;                    /* GNSS是否可用 */
    uint32      m_u32Gnss_PDOPofUnder5;                   /* PDOP精度是否大于5 */
    uint32      m_u32Gnss_inViewOfUnder5;                 /* 可搜到星数是否大于5 */
    uint32      m_u32HardWorkState;                       /* 硬件工作状态 */
    uint32      m_u32V2xState;                            /* V2X工作状态 */
    uint32      m_u32CommumicationState;                  /* 软件通讯接口状态 */
    uint32      m_u32AppState;                            /* 应用程序运行状态 */
    uint64      m_u64V2xTraffic;                          /* V2X模块通信流量统计 */
    uint32      m_u32DiskState;                           /* 磁盘使用率 */
    uint32      m_u32CPU;                                 /* CPU使用率 */
    uint32      m_u32Memory;                              /* 内存使用率 */
    uint64      m_u64TotalWorkTime;                       /* 秒为单位 */
    uint64      m_u64TotalAppFlow;                        /*  */
    int8        m_na8reserved[MAX_U8VALUE];                /* 预留 */
}__attribute__ ((packed)) DevState_t;
/* 设备故障表 */
typedef struct _DevFault
{
    int8        m_na8FaultTime[MAX_FALUTTIME_SIZE];                /* 故障时间 */
    uint32      m_u32FaultLv;                                     /* 故障等级 */
    uint32      m_u32FaultType;                                   /* 故障类型 */
    uint32      m_u32Self_Recovery;                               /* 是否自恢复 */
    int8        m_na8reserved[MAX_U8VALUE];                        /* 预留 */
}__attribute__ ((packed)) DevFault_t;
/* 设备感知表 */
typedef struct _SensingDevicesData
{
    uint32          m_u32Rele_SN;                     /* 关联序号 */
    int8            m_na8DevID[MAX_DEVID_SIZE];        /* 设备ID */
    uint32          m_u32DevType;                     /* 设备类型 */
    uint32          m_u32DataLen;                        /* */
    int8            m_na8Data[MAX_RCVSND_NUM];                    /* 数据 */
    int8            m_na8reserved[MAX_U8VALUE];        /* 预留 */
}__attribute__ ((packed))SensingDevicesData_t;
enum _enumType {
    enum_TRXBLOCK_TYPE = 1,
    enum_CER_TYPE,
    enum_ALG_TYPE,
    enum_DEVSTATE_TYPE,
    enum_DEVFAULT_TYPE,
    enum_SENSINGDEVICESDATA_TYPE
};
typedef struct _SQL_STRUCTURE
{
    enum _enumType structenumtype;
    union  u{
        RXMessage_t  m_tRXData;               /* 收发消息 */
        Cer_t  m_tCerData;                         /* 安全证书表 */
        Alg_t  m_tAlgData;                         /* 算法表 */
        DevState_t  m_tDevstateData;               /* 设备状态表 */
        DevFault_t  m_tDevFaultData;               /* 设备故障表 */
        SensingDevicesData_t  m_tSen_DevData;      /* 设备感知表 */
    } choice;
}SQL_STRUCTURE_t;

enum _enumFileType {
    enum_string,
    enum_int,
};
typedef struct _FileValue{
    enum _enumFileType enumTypeFlag;
    union
    {
        uint64 m_u64FileValue;
        int8 m_na8FileValue[MAX_SELECT_FILD_LEN];
    }choic;
}FileIdValue_t;
/* 查找消息存储结构体 */
typedef struct _DataBaseMsgData{
    uint32 m_u32Tab_DataNum;
    SQL_STRUCTURE_t m_tTab_Data[MAX_INSERT_NUM];
}DataBaseMsgData_t;
/********************** 消息队列接口定义 ******************************/
typedef struct _MsgQuence{
    long m_u64MessageType;
    SQL_STRUCTURE_t m_tDatabaseMsg;
}MsgQuence_t;
/****************** 共享内存结构体接口定义 **************************/
enum _RecvMsgType{
    enum_Seek = 11,      /* 匹配字段查询 */
    enum_Update,    /* 匹配字段更新*/
    enum_Del,       /* 删除数据库指定表指定字段匹配的行 */
    enum_Clear,     /* 清空数据库里面指定表 */
    enum_Deltab     /* 删除数据库里面的指定表 */
};
typedef struct _RecvShmMsg{
    int optflag; /* 0xAA 代表线程操作完成，0xBB代表正在写占用，0xCC代表写完成 */
    enum _RecvMsgType enumRecvMsgType;
    char m_na8Tabname[40];
    char m_na8FileId[40];
    FileIdValue_t m_tFileValue;
    DataBaseMsgData_t m_tMsgDataSourceDate;
    int  m_n32Ret;
}RecvShmMsg_t;
/********************** 函数外部申明 ********************************/
/**
 * @brief 使用数据库函数就需要调用数据库初始化函数
 * @return  数据库中，数据库初始化函数，0表示成功，其他表示失败.
 */
extern int32 FD_DataBase_Init(void);
/**
 * @brief 往消息队列中发送要插入的消息
 * @return  数据库中，发送数据给消息队列函数，0表示成功，其他表示失败.
 */
extern int32 FD_DataBase_SendToDb(MsgQuence_t *p_ptMsgQence);
/**
 * @brief 在数据库的指定表中，查找字段名为p_pn8_FileId的字段中，字段值为p_ptFileValue的信息.
 * @param[in] p_pn8_Tabname    查找表的名称.
 * @param[in] p_pn8_FileId   字段名称.
 * @param[in] p_ptFileValue   字段值.
 * @param[in] p_ptMsgDataSourceDate
 * @return  数据库中，对表中的数据进行删除操作的执行状态，0表示成功，其他表示失败.
 */
extern uint32 FD_DataBase_Tab_Select(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue, DataBaseMsgData_t *p_ptMsgDataSourceDate);
/**
 * @brief 在数据库的指定表中，更新指定字段指定数据所在行的信息.
 * @param[in] p_pn8_Tabname    数据库中表名.
 * @param[in] p_pn8_FileId   字段名称.
 * @param[in] p_ptFileValue   字段值.
 * @param[in] p_ptSqlSourceDate   要更新的内容.
 * @return  数据库中，对表中的数据进行删除操作的执行状态，0表示成功，其他表示失败.
 */
extern uint32 FD_DataBase_Tab_Update(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate);
/**
 * @brief 在数据库的指定表中，删除字段名为p_pn8_FileId的字段中，字段值为pstructFileValue的一行信息.
 * @param[in] p_pn8_Tabname    数据库中表名.
 * @param[in] p_pn8_FileId   字段名称.
 * @param[in] p_ptFileValue   字段内容.
 * @return  数据库中，对表中的数据进行删除操作的执行状态，0表示成功，其他表示失败.
 */
extern uint32 FD_DataBase_Tab_Delete(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue);
/**
 * @brief 删除指定表的数据.
 * @param[in] p_pn8_Tabname    数据库中表名.
 * @return  数据库中，对表中的数据进行删除操作的执行状态，0表示成功，其他表示失败.
 */
extern uint32 FD_DataBase_ClearTab(char *p_pn8_Tabname);
/**
 * @brief 删除指定表.
 * @param[in] p_pn8_Tabname    数据库中表名.
 * @return  数据库中，对表中的数据进行删除操作的执行状态，0表示成功，其他表示失败.
 */
extern uint32 FD_DataBase_DeleteTab(char *p_pn8_Tabname);
#endif /* __DATABASEIF_H__ */

