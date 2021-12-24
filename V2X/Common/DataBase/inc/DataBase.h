/***********************************************************************
 * 文 件 名 称 ： Database.h
 * 功 能 描 述 ： 数据库引用头文件
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
#ifndef __DATABASE_h__
#define __DATABASE_h__
/**********************  头文件包含  ********************************/
#include "DataBaseIf.h"
#include "sqlite3.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include "wj_log.h"
/********************** SQLITE命令定义 *****************************/
/* 创建读写V2X数据表命令 */
#define CREATE_TAB_TRXSHEET "CREATE TABLE '%s'(SN INTEGER PRIMARY KEY AUTOINCREMENT,Rele_SN INT64,"\
                            "Time VARCHAR(20),TRX INTEGER,MsgType VARCHAR(5),Sig_StartTime INT64,Sig_EndTime INT64,"\
                            "Verify_StratTime INT64,Verify_EndTime INT64,Data_RecvTime INT64,Data_SendTime INT64,"\
                            "Trans_StartTime INT64,Trans_EndTime INT64,Data Blob,reserved VARCHAR(255));"
/* 创建证书表命令 */
#define CREATE_TAB_CERSHEET "CREATE TABLE '%s'(SN INTEGER PRIMARY KEY AUTOINCREMENT,Time VARCHAR(20),"\
                            "CerType INTEGER,Sec_SN INTEGER,Encry_State INTEGER,Hash VARCHAR(48),Private_Key VARCHAR(48),"\
                            "Cer_Data Blob,reserved VARCHAR(255));"
/* 创建算法表命令 */
#define CREATE_TAB_ALGSHEET "CREATE TABLE '%s'(SN INTEGER PRIMARY KEY AUTOINCREMENT,Alg_Name VARCHAR(10),Value INTEGER,reserved VARCHAR(255));"
/* 创建设备状态表命令 */
#define CREATE_TAB_DEVSTATESHEET    "CREATE TABLE '%s'(SN INTEGER PRIMARY KEY AUTOINCREMENT,Time VARCHAR(20),"\
                                    "DevID VARCHAR(20),IP VARCHAR(20),HardVer VARCHAR(20),SystemVer VARCHAR(20),"\
                                    "SoftVer VARCHAR(20),DevTemperature INTEGER,Gnss_unavailable INTEGER,Gnss_PDOPofUnder5 INTEGER,"\
                                    "Gnss_inViewOfUnder5 INTEGER,HardWorkState INTEGER,V2xState INTEGER,CommumicationState INTEGER,"\
                                    "AppState INTEGER,V2xTraffic INT64,DiskState INTEGER,CPU INTEGER,Memory INTEGER,TotalWorkTime INT64,"\
                                    "TotalAppFlow INT64,reserved VARCHAR(255));"
/* 创建设备故障表命令 */
#define CREATE_TAB_DEVFAULT         "CREATE TABLE '%s'(SN INTEGER PRIMARY KEY AUTOINCREMENT,FaultTime VARCHAR(20),FaultLv INTEGER,"\
                                    "FaultType INTEGER,Self_Recovery INTEGER,reserved VARCHAR(255));"
/* 创建感知设备表命令 */
#define CREATE_TAB_SENSINGDEVICESDATESHEET  "CREATE TABLE '%s'(SN INTEGER PRIMARY KEY AUTOINCREMENT,Time VARCHAR(20),Rele_SN INTEGER,"\
                                            "DevID VARCHAR(10),DevType INTEGER,Data Blob,reserved VARCHAR(255));"
/* 删除表的操作 */
#define DELETE_TABLE "DROP TABLE %s"
/* 开始操作数据库 */
#define START_OP_DB "BEGIN TRANSACTION;"
/* 停止操作数据库 */
#define END_OP_DB   "COMMIT TRANSACTION;"
/* 往数据库里面插入V2X收发数据 */
#define INSERT_V2XMESSAGEDATE   "INSERT INTO '%s' (SN,Rele_SN,Time,TRX,MsgType,"\
                                "Sig_StartTime,Sig_EndTime,Verify_StratTime,Verify_EndTime,"\
                                "Data_RecvTime,Data_SendTime,Trans_StartTime,Trans_EndTime,"\
                                "Data,reserved)"\
                                " VALUES(NULL,?,?,?,?,?,?,?,?,?,?,?,?,?,?);"
/* 往数据库里面插入证书数据 */
#define INSERT_CERDATE  "INSERT INTO '%s' (SN,Time,CerType,Sec_SN,Encry_State,Hash,Private_Key,Cer_Data,reserved)"\
                        " VALUES(NULL,?,?,?,?,?,?,?,?);"
/* 往数据库里面插入算法数据 */
#define INSERT_ALGDATE      "INSERT INTO '%s' (SN,Alg_Name,Value,reserved)"\
                            " VALUES(NULL,?,?,?);"
/* 往数据库里面插入设备状态数据 */
#define INSERT_DEVSTATUSDATE    "INSERT INTO '%s' (SN,Time,DevID,IP,HardVer,SystemVer,SoftVer,DevTemperature,Gnss_unavailable,"\
                                "Gnss_PDOPofUnder5,Gnss_inViewOfUnder5,HardWorkState,V2xState,CommumicationState,AppState,V2xTraffic,"\
                                "DiskState,CPU,Memory,TotalWorkTime,TotalAppFlow,reserved)"\
                                " VALUES(NULL,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);"
/* 往数据库里面插入设备故障数据 */
#define INSERT_DEVFAULTDATE     "INSERT INTO '%s' (SN,FaultTime,FaultLv,FaultType,Self_Recovery,reserved)"\
                                " VALUES(NULL,?,?,?,?,?);"
/* 往数据库里面插入设备感知数据 */
#define INSERT_SENSINGDEVICESDATE   "INSERT INTO '%s' (SN,Time,Rele_SN,DevID,DevType,Data,reserved)"\
                                    " VALUES(NULL,?,?,?,?,?,?);"
/* 查看某表是否存在 */
#define SELECT_TAB_ISEXISTS "select * from sqlite_master where type = 'table' and name = '%s';"
/* 数据库自增归零 */
#define SET_SN_ZERO "UPDATE sqlite_sequence SET seq = 0 WHERE NAME ='%s';"
/* 删除指定的表数据 */
#define CLEAR_TAB_DATE "DELETE FROM '%s';"
/* 删除指定表里面对应指定字段指定字段值所对应的指定数据行 */
#define TAB_DELETE_FILEID_DATE_STRING "DELETE FROM '%s' WHERE %s = '%s';"
#define TAB_DELETE_FILEID_DATE_INT "DELETE FROM '%s' WHERE %s = '%lld';"
/* 更新RXT表 */
#define UPDATE_RXT_FILEID_VALUE_STRING  "UPDATE %s SET Rele_SN = '%lld', Time = '%s', TRX = '%d', MsgType = '%s', Sig_StartTime = '%lld', Sig_EndTime = '%lld',"\
                                        "Verify_StratTime = '%lld', Verify_EndTime = '%lld', Data_RecvTime = '%lld', Data_SendTime = '%lld',"\
                                        "Trans_StartTime = '%lld', Trans_EndTime = '%lld', Data = '%s',reserved = '%s'"\
                                        "WHERE %s = '%s';"
#define UPDATE_RXT_FILEID_VALUE_INT "UPDATE %s SET Rele_SN = '%lld', Time = '%s', TRX = '%d', MsgType = '%s', Sig_StartTime = '%lld', Sig_EndTime = '%lld',"\
                                    "Verify_StratTime = '%lld', Verify_EndTime = '%lld', Data_RecvTime = '%lld', Data_SendTime = '%lld',"\
                                    "Trans_StartTime = '%lld', Trans_EndTime = '%lld', Data = '%s',reserved = '%s'"\
                                    "WHERE %s = '%lld';"
/* 更新CER表 */
#define UPDATE_CER_FILEID_VALUE_STRING  "UPDATE %s SET Time = '%s', CerType = '%d', Sec_SN = '%d', Encry_State = '%d', Hash = '%s',"\
                                        "Private_Key = '%s', Cer_Data = '%s', reserved = '%s'"\
                                        "WHERE %s = '%s';"
#define UPDATE_CER_FILEID_VALUE_INT "UPDATE %s SET Time = '%s', CerType = '%d', Sec_SN = '%d', Encry_State = '%d', Hash = '%s',"\
                                    "Private_Key = '%s', Cer_Data = '%s', reserved = '%s'"\
                                    "WHERE %s = '%lld';"
/* 更新ALG表 */
#define UPDATE_ALG_FILEID_VALUE_STRING  "UPDATE %s SET Alg_Name = '%s', Value = '%d', reserved = '%s'"\
                                        "WHERE %s = '%s';"
#define UPDATE_ALG_FILEID_VALUE_INT     "UPDATE %s SET Alg_Name = '%s', Value = '%d', reserved = '%s'"\
                                        "WHERE %s = '%lld';"
/* 更新DEVSTATE表 */
#define UPDATE_DEVSTATE_FILEID_VALUE_STRING "UPDATE %s SET Time = '%s', DevID = '%s', IP = '%s', HardVer= '%s', SystemVer = '%s', SoftVer = '%s', DevTemperature = '%d',"\
                                            "Gnss_unavailable = '%d', Gnss_PDOPofUnder5 = '%d', Gnss_inViewOfUnder5 = '%d', HardWorkState = '%d', V2xState = '%d', CommumicationState = '%d'," \
                                            "AppState = '%d', V2xTraffic = '%lld', DiskState = '%d', CPU = '%d', Memory = '%d', TotalWorkTime = '%lld', TotalAppFlow = '%lld', reserved = '%s'" \
                                            "WHERE %s = '%s';"
#define UPDATE_DEVSTATE_FILEID_VALUE_INT    "UPDATE %s SET Time = '%s', DevID = '%s', IP = '%s', HardVer= '%s', SystemVer = '%s', SoftVer = '%s', DevTemperature = '%d',"\
                                            "Gnss_unavailable = '%d', Gnss_PDOPofUnder5 = '%d', Gnss_inViewOfUnder5 = '%d', HardWorkState = '%d', V2xState = '%d', CommumicationState = '%d'," \
                                            "AppState = '%d', V2xTraffic = '%lld', DiskState = '%d', CPU = '%d', Memory = '%d', TotalWorkTime = '%lld', TotalAppFlow = '%lld', reserved = '%s'" \
                                            "WHERE %s = '%lld';"
/* 更新DEVFALUT表 */
#define UPDATE_DEVFAULT_FILEID_VALUE_STRING     "UPDATE %s SET FaultTime = '%s', FaultLv = '%d', FaultType = '%d', Self_Recovery = '%d', reserved = '%s'"\
                                                "WHERE %s = '%s';"
#define UPDATE_DEVFAULT_FILEID_VALUE_INT    "UPDATE %s SET FaultTime = '%s', FaultLv = '%d', FaultType = '%d', Self_Recovery = '%d', reserved = '%s'"\
                                            "WHERE %s = '%lld';"
/* 更新SENSING表 */
#define UPDATE_SENSING_FILEID_VALUE_STRING  "UPDATE %s SET Time = '%s', Rele_SN = '%d', DevID = '%s', DevType = '%d', Data = '%s', reserved = '%s'"\
                                            "WHERE %s = '%s';"
#define UPDATE_SENSING_FILEID_VALUE_INT     "UPDATE %s SET Time = '%s', Rele_SN = '%d', DevID = '%s', DevType = '%d', Data = '%s', reserved = '%s'"\
                                            "WHERE %s = '%lld';"
/* 查询指定数据库指定表指定字段指定值对应的行 */
#define SELECT_DB_TAB_FILE_DATE_STRING      "SELECT * FROM %s WHERE SN IN (SELECT SN FROM %s WHERE %s = '%s');"
#define SELECT_DB_TAB_FILE_DATE_INT         "SELECT * FROM %s WHERE SN IN (SELECT SN FROM %s WHERE %s = '%lld');"
/* 查询整张表 */
#define SELECT_DB_TAB_ALL "SELECT * FROM %s;"
/********************** 宏定义 *************************************/
#define DATABASEMODULE "DataBase"
#define DATABASEINSERT  71   /* 不能使用70，会出错，数据库使用插入数据的消息队列*/
#define DATABASESHM     73   /* 数据库使用共享内存 */
/* 数据库忙超时时间 ms*/
#define DB_BUSY_TIMEOUT 1100
#define DATAVASE_HOME_PATH "/mnt/RWD/DataBase"
#define DATABASE_FOLDER_PATH   "/mnt/RWD/DataBase/Database_RTX"
#define DATABASE_BASE_PATH "/mnt/RWD/DataBase/Database_Base"
#define DATABASE_PATH  "/mnt/RWD/DataBase/Database_Base/Database.db"
#define DATABASERTX_PATH   "/mnt/RWD/DataBase/Database_RTX/Databasertx_%Y%m%d%H.db"
#define DATABASERLONG_PATH   "/mnt/RWD/DataBase/Database_Base/Database_Base.db"
#define TAB_TRX_DATATIME_NAME "TRXSheet"
#define TAB_SENSING_DATATIME_NAME "SENSINGSheet"
#define SIZE1G 1000*1000*1000
#define SIZE100M 100*1000*1000
/********************** 全局变量定义  ********************************/
int32 g_n32SqliteStateFlag; /* O is available  1 is unavailable */
/* 数据库句柄定义 */
sqlite3 *g_psqldb;
sqlite3 *g_psqldb_rtx;
sqlite3 *g_psqldb_base;
/* 数据缓冲区 */
DataBaseMsgData_t g_t_DataBaseRXTDateBuff;
DataBaseMsgData_t g_t_DataBaseCERDateBuff;
DataBaseMsgData_t g_t_DataBaseALGDateBuff;
DataBaseMsgData_t g_t_DataBaseDEVSTATEDateBuff;
DataBaseMsgData_t g_t_DataBaseDEVFALUTDateBuff;
DataBaseMsgData_t g_t_DataBaseSENSINGDateBuff;
/* 数据库模块线程锁 */
SendMsgMutex_t *g_p_tSendMsgMutex;
#endif /* __DATABASE_h__ */

