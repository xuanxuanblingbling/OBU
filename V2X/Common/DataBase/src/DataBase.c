/***********************************************************************
 * 文 件 名 称 ： Database.c
 * 功 能 描 述 ： 数据库操作源文件
 * 开 发 人 员 ： huangsai
 * @history
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    huangsai   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
/************************  包含的头文件  ********************************/
#include "DataBase.h"
/*************************** 函数内部申明 *******************************/
static int DataBase_TabNameToDbId(char *p_pn8Tabname, sqlite3** p_pptsqliteDb, uint8* p_pn8Type);
static int DataBase_InsertV2XData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num);
static int DataBase_InsertCerData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num);
static int DataBase_InsertAlgData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num);
static int DataBase_InsertDevStateData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num);
static int DataBase_InsertDevFaultData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num);
static int DataBase_InsertSenSingData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num);
static int DataBase_Update_TRXData(sqlite3 **p_pptsqliteDb, char *p_pn8Tabname, char *p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate);
static int DataBase_Update_CerData(sqlite3 **p_pptsqliteDb, char *p_pn8Tabname, char *p_pn8FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate);
static int DataBase_Update_AlgData(sqlite3 **p_pptsqliteDb, char *p_pn8_Tabname, char *p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate);
static int DataBase_Update_DevStateData(sqlite3 **p_pptsqliteDb, char *p_pn8_Tabname, char *p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate);
static int DataBase_Update_DevFaultData(sqlite3 **p_pptsqliteDb, char *p_pn8_Tabname, char *p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate);
static int DataBase_Update_SenSingData(sqlite3 **p_pptsqliteDb, char *p_pn8_Tabname, char *p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate);
static int DataBase_Select_TRX(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, uint32 p_u32Num, uint32 p_u32Index);
static int DataBase_Select_Cer(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, uint32 p_u32Num, uint32 p_u32Index);
static int DataBase_Select_Alg(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, uint32 p_u32Num, uint32 p_u32Index);
static int DataBase_Select_DevState(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, uint32 p_u32Num, uint32 p_u32Index);
static int DataBase_Select_DevFault(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, uint32 p_u32Num, uint32 p_u32Index);
static int DataBase_Select_SenSing(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, int p_u32Num, int p_u32Index);
static int DataBase_IsTabExists(char* p_pn8_Tabname, sqlite3 **p_pptsqliteDb);
static uint32 DataBase_OpenDB(const char *p_pn8filename, sqlite3 **p_pptsqliteDb);
static uint32 DataBase_CloseDB(sqlite3 **p_pptsqliteDb);
static uint32 DataBase_CreatTab(char *p_pn8_Tabname);
static uint32 DataBase_DeleteTab(char *p_pn8_Tabname);
static uint32 DataBase_Tab_Insert(char *p_pn8_Tabname, DataBaseMsgData_t *p_ptMsgDataSourceDate);
static uint32 DataBase_ClearTab(char *p_pn8_Tabname);
static uint32 DataBase_Tab_Delete(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue);
static uint32 DataBase_Tab_Update(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate);
static uint32 DataBase_Tab_Select(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue, DataBaseMsgData_t *p_ptMsgDataSourceDate);
static int DataBase_CreateDir(char *p_pn8Flow);
static int DataBase_Create_Tab_All(uint8 p_u8Flag);
/***************************  函数定义  ********************************/
/***********************************************************************
 * 函 数 名 称 ： DataBase_TabNameToDbId
 * 功 能 描 述 ： 根据表名匹配数据库
 * 输 入 参 数 ： p_pn8Tabname/p_pn8Type    数据库表名/类型
 * 输 出 参 数 ： p_pptsqliteDb             数据库句柄
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-24 V1.0   黄赛    Create
***********************************************************************/
static int DataBase_TabNameToDbId(char *p_pn8Tabname, sqlite3** p_pptsqliteDb, uint8* p_pn8Type)
{
    /* 入参检查 */
    if ((NULL == p_pn8Tabname) || (NULL == p_pptsqliteDb) || (NULL == p_pn8Type))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8Tabname = %p p_pptsqliteDb = %p p_pn8Type = %p", p_pn8Tabname, p_pptsqliteDb, p_pn8Type);
        return IS_ERR;
    }
    /* 根据表名匹配类型 */
    if (0 == strcmp("ALGSheet", p_pn8Tabname))
    {
        *p_pn8Type = ALG_TYPE;
        *p_pptsqliteDb = g_psqldb_base;
    }
    else if (0 == strcmp("DEVSTATESheet", p_pn8Tabname))
    {
        *p_pn8Type = DEVSTATE_TYPE;
        *p_pptsqliteDb = g_psqldb;
    }
    else if (0 == strcmp("DEVFAULTSheet", p_pn8Tabname))
    {
        *p_pn8Type = DEVFAULT_TYPE;
        *p_pptsqliteDb = g_psqldb;
    }
    else if (0 == strcmp("CERSheet", p_pn8Tabname))
    {
        *p_pn8Type = CER_TYPE;
        *p_pptsqliteDb = g_psqldb_base;
    }
    else if (0 >= strcmp("TRXSheet",p_pn8Tabname))
    {
        *p_pn8Type = TRXBLOCK_TYPE;
        *p_pptsqliteDb = g_psqldb_rtx;
    }
    else if (0 >= strcmp("SENSINGSheet", p_pn8Tabname))
    {
        *p_pn8Type = SENSINGDEVICESDATE_TYPE;
        *p_pptsqliteDb = g_psqldb_rtx;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "type complate is err: p_pn8Tabname = %s", p_pn8Tabname);
        return IS_ERR;
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_InsertV2XData
 * 功 能 描 述 ： 向数据库中V2X收发表中插入v2x数据
 * 输 入 参 数 ： p_ptsqlite3stmt/p_u32Num/p_ptSqlSourceDate  数据库索引/插入数据/索引编号
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_InsertV2XData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num)
{
    /* 入参检查 */
    if ((NULL == p_ptsqlite3stmt) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptsqlite3stmt = %p p_ptSqlSourceDate = %p p_u32Num = %d", p_ptsqlite3stmt, p_ptSqlSourceDate, p_u32Num);
        return IS_ERR;
    }
    uint32 l_u32i = 0;
    uint64 l_u64TimeStamp = 0;
    int8 l_n8YMDHMS[100] = {0};
    Misc_GetCurTimeStamp(&l_u64TimeStamp, l_n8YMDHMS);
    sqlite3_bind_null(p_ptsqlite3stmt, l_u32i++);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_u64Rele_SN);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, l_n8YMDHMS, strlen(l_n8YMDHMS), 0);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_u32TRX);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_na8MsgType, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_na8MsgType), 0);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_u64Sig_StartTime);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_u64Sig_EndTime);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_u64Verify_StratTime);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_u64Verify_EndTime);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_u64Data_RecvTime);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_u64Data_SendTime);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_u64Trans_StartTime);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_u64Trans_EndTime);
    sqlite3_bind_blob(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_na8Data, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_u32DataLen, 0);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_na8reserved, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tRXData.m_na8reserved), 0);
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_InsertCerData
 * 功 能 描 述 ： 向数据库中证书表中插入证书数据
 * 输 入 参 数 ： p_ptsqlite3stmt/p_ptSqlSourceDate/p_u32Num  数据库索引/插入数据/索引编号
 * 输 出 参 数 ： 无
 * 返  回  值  :  IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_InsertCerData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num)
{
    /* 入参检查 */
    if ((NULL == p_ptsqlite3stmt) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptsqlite3stmt = %p p_ptSqlSourceDate = %p p_u32Num = %d", p_ptsqlite3stmt, p_ptSqlSourceDate, p_u32Num);
        return IS_ERR;
    }
    uint32 l_u32i = 0;
    uint64 l_u64TimeStamp = 0;
    int8 l_n8YMDHMS[100] = {0};
    Misc_GetCurTimeStamp(&l_u64TimeStamp, l_n8YMDHMS);
    sqlite3_bind_null(p_ptsqlite3stmt, l_u32i++);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, l_n8YMDHMS, strlen(l_n8YMDHMS), 0);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tCerData.m_u32CerType);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tCerData.m_u32Sec_SN);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tCerData.m_u32Encry_State);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tCerData.m_na8Hash, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tCerData.m_na8Hash), 0);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tCerData.m_na8Private_KEY, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tCerData.m_na8Private_KEY), 0);
    sqlite3_bind_blob(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tCerData.m_na8Cer_Data, p_ptSqlSourceDate[p_u32Num].choice.m_tCerData.m_u32CerDataLen, 0);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tCerData.m_na8reserved, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tCerData.m_na8reserved), 0);
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_InsertAlgData
 * 功 能 描 述 ： 向数据库中算法表中插入算法数据
 * 输 入 参 数 ： p_ptsqlite3stmt/p_ptSqlSourceDate/p_u32Num  数据库索引/插入数据/索引编号
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_InsertAlgData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num)
{
    /* 入参检查 */
    if ((NULL == p_ptsqlite3stmt) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptsqlite3stmt = %p p_ptSqlSourceDate = %p p_u32Num = %d", p_ptsqlite3stmt, p_ptSqlSourceDate, p_u32Num);
        return IS_ERR;
    }
    int32 u32i = 0;
    sqlite3_bind_null(p_ptsqlite3stmt, u32i++);
    sqlite3_bind_text(p_ptsqlite3stmt, u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tAlgData.m_na8Alg_Name, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tAlgData.m_na8Alg_Name), 0);
    sqlite3_bind_int(p_ptsqlite3stmt, u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tAlgData.m_u32Value);
    sqlite3_bind_text(p_ptsqlite3stmt, u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tAlgData.m_na8Reserved, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tAlgData.m_na8Reserved), 0);
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_InsertDevStateData
 * 功 能 描 述 ： 向数据库中设备状态表中插入设备状态数据
 * 输 入 参 数 ： p_ptsqlite3stmt/p_ptSqlSourceDate/p_u32Num  数据库索引/插入数据/索引编号
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_InsertDevStateData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num)
{
    /* 入参检查 */
    if ((NULL == p_ptsqlite3stmt) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptsqlite3stmt = %p p_ptSqlSourceDate = %p p_u32Num = %d", p_ptsqlite3stmt, p_ptSqlSourceDate, p_u32Num);
        return IS_ERR;
    }
    uint32 l_u32i = 0;
    uint64 l_u64TimeStamp = 0;
    int8 l_n8YMDHMS[100] = {0};
    Misc_GetCurTimeStamp(&l_u64TimeStamp, l_n8YMDHMS);
    sqlite3_bind_null(p_ptsqlite3stmt, l_u32i++);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, l_n8YMDHMS, strlen(l_n8YMDHMS), 0);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8DevID, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8DevID), 0);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8IP, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8IP), 0);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8HardVer, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8HardVer), 0);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8SystemVer, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8SystemVer), 0);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8SoftVer, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8SoftVer), 0);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u32DevTemperature);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u32Gnss_unavailable);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u32Gnss_PDOPofUnder5);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u32Gnss_inViewOfUnder5);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u32HardWorkState);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u32V2xState);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u32CommumicationState);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u32AppState);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u64V2xTraffic);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u32DiskState);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u32CPU);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u32Memory);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u64TotalWorkTime);
    sqlite3_bind_int64(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_u64TotalAppFlow);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8reserved, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tDevstateData.m_na8reserved), 0);
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_InsertDevFaultData
 * 功 能 描 述 ： 向数据库中设备故障表中插入设备故障数据
 * 输 入 参 数 ： p_ptsqlite3stmt/p_ptSqlSourceDate/p_u32Num  数据库索引/插入数据/索引编号
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_InsertDevFaultData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num)
{
    /* 入参检查 */
    if ((NULL == p_ptsqlite3stmt) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptsqlite3stmt = %p p_ptSqlSourceDate = %p p_u32Num = %d", p_ptsqlite3stmt, p_ptSqlSourceDate, p_u32Num);
        return IS_ERR;
    }
    uint32 l_u32i = 0;
    sqlite3_bind_null(p_ptsqlite3stmt, l_u32i++);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevFaultData.m_na8FaultTime, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tDevFaultData.m_na8FaultTime), 0);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevFaultData.m_u32FaultLv);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevFaultData.m_u32FaultType);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevFaultData.m_u32Self_Recovery);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tDevFaultData.m_na8reserved, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tDevFaultData.m_na8reserved), 0);
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_InsertSenSingData
 * 功 能 描 述 ： 向数据库中设备感知表中插入设备感知数据
 * 输 入 参 数 ： p_ptsqlite3stmt/p_ptSqlSourceDate/p_u32Num  数据库索引/插入数据/索引编号
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_InsertSenSingData(sqlite3_stmt *p_ptsqlite3stmt, SQL_STRUCTURE_t *p_ptSqlSourceDate, uint32 p_u32Num)
{
    /* 入参检查 */
    if ((NULL == p_ptsqlite3stmt) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptsqlite3stmt = %p p_ptSqlSourceDate = %p p_u32Num = %d", p_ptsqlite3stmt, p_ptSqlSourceDate, p_u32Num);
        return IS_ERR;
    }
    uint32 l_u32i = 0;
    uint64 l_u64TimeStamp = 0;
    int8 l_n8YMDHMS[100] = {0};
    Misc_GetCurTimeStamp(&l_u64TimeStamp, l_n8YMDHMS);
    sqlite3_bind_null(p_ptsqlite3stmt, l_u32i++);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, l_n8YMDHMS, strlen(l_n8YMDHMS), 0);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tSen_DevData.m_u32Rele_SN);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tSen_DevData.m_na8DevID, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tSen_DevData.m_na8DevID), 0);
    sqlite3_bind_int(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tSen_DevData.m_u32DevType);
    sqlite3_bind_blob(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tSen_DevData.m_na8Data, p_ptSqlSourceDate[p_u32Num].choice.m_tSen_DevData.m_u32DataLen, 0);
    sqlite3_bind_text(p_ptsqlite3stmt, l_u32i++, p_ptSqlSourceDate[p_u32Num].choice.m_tSen_DevData.m_na8reserved, strlen(p_ptSqlSourceDate[p_u32Num].choice.m_tSen_DevData.m_na8reserved), 0);
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Update_TRXData
 * 功 能 描 述 ： 更新数据库中的TRX数据
 * 输 入 参 数 ： p_pn8Tabname/p_pn8_FileId/p_ptFileValue/p_ptSqlSourceDate/p_pptsqliteDb
 *              表名/字段名/字段值/要更新的数据/数据库操作句柄
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
__attribute__((unused)) static int DataBase_Update_TRXData(sqlite3 **p_pptsqliteDb, char *p_pn8Tabname, char *p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate)
{
    /* 入参检查 */
    if ((NULL == p_pptsqliteDb) || (NULL == *p_pptsqliteDb) || (NULL == p_pn8Tabname)
            || (NULL == p_pn8_FileId) || (NULL == p_ptFileValue) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pptsqliteDb = %p *p_pptsqliteDb = %p p_pn8Tabname = %p p_pn8_FileId = %p p_ptFileValue = %p p_ptSqlSourceDate = %p", p_pptsqliteDb, *p_pptsqliteDb, p_pn8Tabname, p_pn8_FileId, p_ptFileValue, p_ptSqlSourceDate);
        return IS_ERR;
    }
    int8* l_pn8buff = NULL;
    uint32 l_u32Ret = 0;
    int8* l_pn8ErrMsg = NULL;
    /* 分配缓冲区 */
    l_pn8buff = malloc(sizeof(int8) * 5120);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    uint64 l_u64TimeStamp = 0;
    int8 l_na8YMDHMS[100] = {0};
    Misc_GetCurTimeStamp(&l_u64TimeStamp, l_na8YMDHMS);
    if (enum_string == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_RXT_FILEID_VALUE_STRING, p_pn8Tabname,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Rele_SN,
                                                l_na8YMDHMS,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u32TRX,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_na8MsgType,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Sig_StartTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Sig_EndTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Verify_StratTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Verify_EndTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Data_RecvTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Data_SendTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Trans_StartTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Trans_EndTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_na8Data,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_na8reserved,
                                                p_pn8_FileId,
                                                p_ptFileValue->choic.m_na8FileValue);
    }
    else if (enum_int == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_RXT_FILEID_VALUE_INT, p_pn8Tabname,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Rele_SN,
                                                l_na8YMDHMS,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u32TRX,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_na8MsgType,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Sig_StartTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Sig_EndTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Verify_StratTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Verify_EndTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Data_RecvTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Data_SendTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Trans_StartTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_u64Trans_EndTime,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_na8Data,
                                                p_ptSqlSourceDate->choice.m_tRXData.m_na8reserved,
                                                p_pn8_FileId,
                                                p_ptFileValue->choic.m_u64FileValue);
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "typeflag is err: TypeFlag = %d ", p_ptFileValue->enumTypeFlag);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    l_u32Ret = sqlite3_exec(*p_pptsqliteDb, l_pn8buff, NULL, NULL, &l_pn8ErrMsg);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update_trxtables sqlite3_exec is err: l_u32Ret = %d p_pn8Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8Tabname, l_pn8ErrMsg);
        sqlite3_free(l_pn8ErrMsg);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    /* 释放缓冲区 */
    free(l_pn8buff);
    l_pn8buff = NULL;
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Update_CerData
 * 功 能 描 述 ： 更新数据库中的CER数据
 * 输 入 参 数 ： p_pn8Tabname/p_pn8FileId/p_ptFileValue/p_ptSqlSourceDate/p_pptsqliteDb
 *              表名/字段名/字段值/要更新的数据/数据库操作句柄
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_Update_CerData(sqlite3 **p_pptsqliteDb, char *p_pn8Tabname, char *p_pn8FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate)
{
    /* 入参检查 */
    if ((NULL == p_pptsqliteDb) || (NULL == *p_pptsqliteDb) || (NULL == p_pn8Tabname)
            || (NULL == p_pn8FileId) || (NULL == p_ptFileValue) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pptsqliteDb = %p *p_pptsqliteDb = %p p_pn8Tabname = %p p_pn8FileId = %p p_ptFileValue = %p p_ptSqlSourceDate = %p", p_pptsqliteDb, *p_pptsqliteDb, p_pn8Tabname, p_pn8FileId, p_ptFileValue, p_ptSqlSourceDate);
        return IS_ERR;
    }
    int8* l_pn8buff = NULL;
    uint32 l_u32Ret = 0;
    int8* l_pn8ErrMsg = NULL;
    /* 分配缓冲区 */
    l_pn8buff = malloc(sizeof(int8) * 5120);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    uint64 l_u64TimeStamp = 0;
    int8 l_na8YMDHMS[100] = {0};
    Misc_GetCurTimeStamp(&l_u64TimeStamp, l_na8YMDHMS);
    if (enum_string == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_CER_FILEID_VALUE_STRING, p_pn8Tabname, l_na8YMDHMS,
                                            p_ptSqlSourceDate->choice.m_tCerData.m_u32CerType,
                                            p_ptSqlSourceDate->choice.m_tCerData.m_u32Sec_SN,
                                            p_ptSqlSourceDate->choice.m_tCerData.m_u32Encry_State,
                                            p_ptSqlSourceDate->choice.m_tCerData.m_na8Hash,
                                            p_ptSqlSourceDate->choice.m_tCerData.m_na8Private_KEY,
                                            p_ptSqlSourceDate->choice.m_tCerData.m_na8Cer_Data,
                                            p_ptSqlSourceDate->choice.m_tCerData.m_na8reserved,
                                            p_pn8FileId, p_ptFileValue->choic.m_na8FileValue);
    }
    else if (enum_int == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_CER_FILEID_VALUE_INT, p_pn8Tabname, l_na8YMDHMS,
                                                p_ptSqlSourceDate->choice.m_tCerData.m_u32CerType,
                                                p_ptSqlSourceDate->choice.m_tCerData.m_u32Sec_SN,
                                                p_ptSqlSourceDate->choice.m_tCerData.m_u32Encry_State,
                                                p_ptSqlSourceDate->choice.m_tCerData.m_na8Hash,
                                                p_ptSqlSourceDate->choice.m_tCerData.m_na8Private_KEY,
                                                p_ptSqlSourceDate->choice.m_tCerData.m_na8Cer_Data,
                                                p_ptSqlSourceDate->choice.m_tCerData.m_na8reserved,
                                                p_pn8FileId, p_ptFileValue->choic.m_u64FileValue);
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "typeflag is err: TypeFlag = %d ", p_ptFileValue->enumTypeFlag);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    l_u32Ret = sqlite3_exec(*p_pptsqliteDb, l_pn8buff, NULL, NULL, &l_pn8ErrMsg);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update_certables sqlite3_exec is err: l_u32Ret = %d p_pn8Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8Tabname, l_pn8ErrMsg);
        sqlite3_free(l_pn8ErrMsg);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    /* 释放缓冲区 */
    free(l_pn8buff);
    l_pn8buff = NULL;
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Update_AlgData
 * 功 能 描 述 ： 更新数据库中的ALG数据
 * 输 入 参 数 ： p_pn8_Tabname/p_pn8_FileId/p_ptFileValue/p_ptSqlSourceDate/p_pptsqliteDb
 *              表名/字段名/字段值/要更新的数据/数据库操作句柄
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_Update_AlgData(sqlite3 **p_pptsqliteDb, char *p_pn8_Tabname, char *p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate)
{
    /* 入参检查 */
    if ((NULL == p_pptsqliteDb) || (NULL == *p_pptsqliteDb) || (NULL == p_pn8_Tabname)
            || (NULL == p_pn8_FileId) || (NULL == p_ptFileValue) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pptsqliteDb = %p *p_pptsqliteDb = %p p_pn8_Tabname = %p p_pn8_FileId = %p p_ptFileValue = %p p_ptSqlSourceDate = %p", p_pptsqliteDb, *p_pptsqliteDb, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, p_ptSqlSourceDate);
        return IS_ERR;
    }
    int8* l_pn8buff = NULL;
    uint32 l_u32Ret = 0;
    int8* l_pn8ErrMsg = NULL;
    /* 分配缓冲区 */
    l_pn8buff = malloc(sizeof(int8) * 5120);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    if (enum_string == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_ALG_FILEID_VALUE_STRING, p_pn8_Tabname,
                                                p_ptSqlSourceDate->choice.m_tAlgData.m_na8Alg_Name,
                                                p_ptSqlSourceDate->choice.m_tAlgData.m_u32Value,
                                                p_ptSqlSourceDate->choice.m_tAlgData.m_na8Reserved,
                                                p_pn8_FileId,
                                                p_ptFileValue->choic.m_na8FileValue);
    }
    else if (enum_int == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_ALG_FILEID_VALUE_INT, p_pn8_Tabname,
                                                p_ptSqlSourceDate->choice.m_tAlgData.m_na8Alg_Name,
                                                p_ptSqlSourceDate->choice.m_tAlgData.m_u32Value,
                                                p_ptSqlSourceDate->choice.m_tAlgData.m_na8Reserved,
                                                p_pn8_FileId,
                                                p_ptFileValue->choic.m_u64FileValue);
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "typeflag is err: TypeFlag = %d ", p_ptFileValue->enumTypeFlag);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    l_u32Ret = sqlite3_exec(*p_pptsqliteDb, l_pn8buff, NULL, NULL, &l_pn8ErrMsg);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update_algtables sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
        sqlite3_free(l_pn8ErrMsg);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    /* 释放缓冲区 */
    free(l_pn8buff);
    l_pn8buff = NULL;
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Update_DevstateData
 * 功 能 描 述 ： 更新数据库中的设备状态数据
 * 输 入 参 数 ： p_pn8_Tabname/p_pn8_FileId/p_ptFileValue/p_ptSqlSourceDate/p_pptsqliteDb
 *              表名/字段名/字段值/要更新的数据/数据库操作句柄
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_Update_DevStateData(sqlite3 **p_pptsqliteDb, char *p_pn8_Tabname, char *p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate)
{
    /* 入参检查 */
    if ((NULL == p_pptsqliteDb) || (NULL == *p_pptsqliteDb) || (NULL == p_pn8_Tabname) || (NULL == p_pn8_FileId)
            || (NULL == p_ptFileValue) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pptsqliteDb = %p *p_pptsqliteDb = %p p_pn8_Tabname = %p p_pn8_FileId = %p p_ptFileValue = %p p_ptSqlSourceDate = %p", p_pptsqliteDb, *p_pptsqliteDb, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, p_ptSqlSourceDate);
        return IS_ERR;
    }
    int8* l_pn8buff = NULL;
    uint32 l_u32Ret = 0;
    int8* l_pn8ErrMsg = NULL;
    uint64 l_u64TimeStamp = 0;
    int8 l_na8YMDHMS[100] = {0};
    Misc_GetCurTimeStamp(&l_u64TimeStamp, l_na8YMDHMS);
    /* 分配缓冲区 */
    l_pn8buff = malloc(sizeof(int8) * 5120);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    if (enum_string == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_DEVSTATE_FILEID_VALUE_STRING, p_pn8_Tabname, l_na8YMDHMS,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8DevID,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8IP,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8HardVer,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8SystemVer,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8SoftVer,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32DevTemperature,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32Gnss_unavailable,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32Gnss_PDOPofUnder5,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32Gnss_inViewOfUnder5,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32HardWorkState,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32V2xState,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32CommumicationState,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32AppState,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u64V2xTraffic,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32DiskState,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32CPU,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32Memory,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u64TotalWorkTime,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u64TotalAppFlow,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8reserved,
                                                p_pn8_FileId,
                                                p_ptFileValue->choic.m_na8FileValue);
    }
    else if (enum_int == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_DEVSTATE_FILEID_VALUE_INT, p_pn8_Tabname, l_na8YMDHMS,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8DevID,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8IP,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8HardVer,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8SystemVer,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8SoftVer,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32DevTemperature,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32Gnss_unavailable,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32Gnss_PDOPofUnder5,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32Gnss_inViewOfUnder5,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32HardWorkState,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32V2xState,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32CommumicationState,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32AppState,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u64V2xTraffic,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32DiskState,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32CPU,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u32Memory,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u64TotalWorkTime,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_u64TotalAppFlow,
                                                p_ptSqlSourceDate->choice.m_tDevstateData.m_na8reserved,
                                                p_pn8_FileId,
                                                p_ptFileValue->choic.m_u64FileValue);
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "typeflag is err: TypeFlag = %d ", p_ptFileValue->enumTypeFlag);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    l_u32Ret = sqlite3_exec(*p_pptsqliteDb, l_pn8buff, NULL, NULL, &l_pn8ErrMsg);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update_devstatetables sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
        sqlite3_free(l_pn8ErrMsg);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    /* 释放缓冲区 */
    free(l_pn8buff);
    l_pn8buff = NULL;
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Update_DevFaultData
 * 功 能 描 述 ： 更新数据库中的设备故障数据
 * 输 入 参 数 ： p_pn8_Tabname/p_pn8_FileId/p_ptFileValue/p_ptSqlSourceDate/p_pptsqliteDb
 *              表名/字段名/字段值/要更新的数据/数据库操作句柄
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_Update_DevFaultData(sqlite3 **p_pptsqliteDb, char *p_pn8_Tabname, char *p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate)
{
    /* 入参检查 */
    if ((NULL == p_pptsqliteDb) || (NULL == *p_pptsqliteDb) || (NULL == p_pn8_Tabname)
            || (NULL == p_pn8_FileId) || (NULL == p_ptFileValue) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pptsqliteDb = %p *p_pptsqliteDb = %p p_pn8_Tabname = %p p_pn8_FileId = %p p_ptFileValue = %p p_ptSqlSourceDate = %p", p_pptsqliteDb, *p_pptsqliteDb, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, p_ptSqlSourceDate);
        return IS_ERR;
    }
    int8* l_pn8buff = NULL;
    uint32 l_u32Ret = 0;
    int8* l_pn8ErrMsg = NULL;
    /* 分配缓冲区 */
    l_pn8buff = malloc(sizeof(int8) * 5120);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    if (enum_string == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_DEVFAULT_FILEID_VALUE_STRING, p_pn8_Tabname,
                                                p_ptSqlSourceDate->choice.m_tDevFaultData.m_na8FaultTime,
                                                p_ptSqlSourceDate->choice.m_tDevFaultData.m_u32FaultLv,
                                                p_ptSqlSourceDate->choice.m_tDevFaultData.m_u32FaultType,
                                                p_ptSqlSourceDate->choice.m_tDevFaultData.m_u32Self_Recovery,
                                                p_ptSqlSourceDate->choice.m_tDevFaultData.m_na8reserved,
                                                p_pn8_FileId,
                                                p_ptFileValue->choic.m_na8FileValue);
    }
    else if (enum_int == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_DEVFAULT_FILEID_VALUE_INT, p_pn8_Tabname,
                                                p_ptSqlSourceDate->choice.m_tDevFaultData.m_na8FaultTime,
                                                p_ptSqlSourceDate->choice.m_tDevFaultData.m_u32FaultLv,
                                                p_ptSqlSourceDate->choice.m_tDevFaultData.m_u32FaultType,
                                                p_ptSqlSourceDate->choice.m_tDevFaultData.m_u32Self_Recovery,
                                                p_ptSqlSourceDate->choice.m_tDevFaultData.m_na8reserved,
                                                p_pn8_FileId,
                                                p_ptFileValue->choic.m_u64FileValue);
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "typeflag is err: TypeFlag = %d ", p_ptFileValue->enumTypeFlag);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    l_u32Ret = sqlite3_exec(*p_pptsqliteDb, l_pn8buff, NULL, NULL, &l_pn8ErrMsg);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update_devdevfaluttables sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
        sqlite3_free(l_pn8ErrMsg);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    /* 释放缓冲区 */
    free(l_pn8buff);
    l_pn8buff = NULL;
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Update_SenSingData
 * 功 能 描 述 ： 更新数据库中的sensing数据
 * 输 入 参 数 ： p_pn8_Tabname/p_pn8_FileId/p_ptFileValue/p_ptSqlSourceDate/p_pptsqliteDb
 *              表名/字段名/字段值/要更新的数据/数据库操作句柄
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
__attribute__((unused))  static int DataBase_Update_SenSingData(sqlite3 **p_pptsqliteDb, char *p_pn8_Tabname, char *p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate)
{
    /* 入参检查 */
    if ((NULL == p_pptsqliteDb) || (NULL == *p_pptsqliteDb) || (NULL == p_pn8_Tabname) || (NULL == p_pn8_FileId)
            || (NULL == p_ptFileValue) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pptsqliteDb = %p *p_pptsqliteDb = %p p_pn8_Tabname = %p p_pn8_FileId = %p p_ptFileValue = %p p_ptSqlSourceDate = %p", p_pptsqliteDb, *p_pptsqliteDb, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, p_ptSqlSourceDate);
        return IS_ERR;
    }
    int8* l_pn8buff = NULL;
    uint32 l_u32Ret = 0;
    int8* l_pn8ErrMsg = NULL;
    uint64 l_u64TimeStamp = 0;
    int8 l_na8YMDHMS[100] = {0};
    Misc_GetCurTimeStamp(&l_u64TimeStamp, l_na8YMDHMS);
    /* 分配缓冲区 */
    l_pn8buff = malloc(sizeof(int8) * 5120);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    if (enum_string == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_SENSING_FILEID_VALUE_STRING, p_pn8_Tabname, l_na8YMDHMS,
                                                p_ptSqlSourceDate->choice.m_tSen_DevData.m_u32Rele_SN,
                                                p_ptSqlSourceDate->choice.m_tSen_DevData.m_na8DevID,
                                                p_ptSqlSourceDate->choice.m_tSen_DevData.m_u32DevType,
                                                p_ptSqlSourceDate->choice.m_tSen_DevData.m_na8Data,
                                                p_ptSqlSourceDate->choice.m_tSen_DevData.m_na8reserved,
                                                p_pn8_FileId,
                                                p_ptFileValue->choic.m_na8FileValue);
    }
    else if (enum_int == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, UPDATE_SENSING_FILEID_VALUE_INT, p_pn8_Tabname, l_na8YMDHMS,
                                                p_ptSqlSourceDate->choice.m_tSen_DevData.m_u32Rele_SN,
                                                p_ptSqlSourceDate->choice.m_tSen_DevData.m_na8DevID,
                                                p_ptSqlSourceDate->choice.m_tSen_DevData.m_u32DevType,
                                                p_ptSqlSourceDate->choice.m_tSen_DevData.m_na8Data,
                                                p_ptSqlSourceDate->choice.m_tSen_DevData.m_na8reserved,
                                                p_pn8_FileId,
                                                p_ptFileValue->choic.m_u64FileValue);
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "typeflag is err: TypeFlag = %d ", p_ptFileValue->enumTypeFlag);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    l_u32Ret = sqlite3_exec(*p_pptsqliteDb, l_pn8buff, NULL, NULL, &l_pn8ErrMsg);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update_sensingtables sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
        sqlite3_free(l_pn8ErrMsg);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    /* 释放缓冲区 */
    free(l_pn8buff);
    l_pn8buff = NULL;
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Select_TRX
 * 功 能 描 述 ： 查询TEX表数据的处理函数
 * 输 入 参 数 ： p_ppn8Result/p_u32Num/p_u32Index  收到的信息/个数/索引
 * 输 出 参 数 ： p_ptDate                          查到的数据
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
__attribute__((unused))  static int DataBase_Select_TRX(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, uint32 p_u32Num, uint32 p_u32Index)
{
    /* 入参检查 */
    if ((NULL == p_ptDate) || (NULL == p_ppn8Result) || (NULL == *p_ppn8Result))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptDate = %p p_ppn8Result = %p *p_ppn8Result = %p ", p_ptDate, p_ppn8Result, *p_ppn8Result);
        return IS_ERR;
    }
    if (0 == strcmp("SN", p_ppn8Result[p_u32Num]))
    {
        /* 不操作 */
    }
    else if (0 == strcmp("Rele_SN", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tRXData.m_u64Rele_SN = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Time", p_ppn8Result[p_u32Num]))
    {
        /* 不操作 */
    }
    else if (0 == strcmp("TRX", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tRXData.m_u32TRX = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("MsgType", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tRXData.m_na8MsgType, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else if (0 == strcmp("Sig_StartTime", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tRXData.m_u64Sig_StartTime = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Sig_EndTime", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tRXData.m_u64Sig_EndTime = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Verify_StratTime", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tRXData.m_u64Verify_StratTime = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Verify_EndTime", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tRXData.m_u64Verify_EndTime = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Data_RecvTime", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tRXData.m_u64Data_RecvTime = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Data_SendTime", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tRXData.m_u64Data_SendTime = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Trans_StartTime", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tRXData.m_u64Trans_StartTime = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Trans_EndTime", p_ppn8Result[p_u32Num]))
    {
       p_ptDate->choice.m_tRXData.m_u64Trans_EndTime = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Data", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tRXData.m_na8Data, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
        p_ptDate->choice.m_tRXData.m_u32DataLen = strlen(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("reserved", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tRXData.m_na8reserved, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "this fild is absent: p_ppn8Result[%d] = %s ", p_u32Num, p_ppn8Result[p_u32Num]);
        return IS_ERR;
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Select_Cer
 * 功 能 描 述 ： 查询cer表数据的处理函数
 * 输 入 参 数 ： p_ppn8Result/p_u32Num/p_u32Index  收到的信息/个数/索引
 * 输 出 参 数 ： p_ptDate                          查到的数据
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_Select_Cer(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, uint32 p_u32Num, uint32 p_u32Index)
{
    /* 入参检查 */
    if ((NULL == p_ptDate) || (NULL == p_ppn8Result) || (NULL == *p_ppn8Result))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptDate = %p p_ppn8Result = %p *p_ppn8Result = %p ", p_ptDate, p_ppn8Result, *p_ppn8Result);
        return IS_ERR;
    }
    if (0 == strcmp("SN", p_ppn8Result[p_u32Num]))
    {
        /* 不操作 */
    }
    else if (0 == strcmp("Time", p_ppn8Result[p_u32Num]))
    {
        /* 不操作 */
    }
    else if (0 == strcmp("CerType", p_ppn8Result[p_u32Num]))
    {
        /* 用2字节接收4字节，暂时这样处理 */
        p_ptDate->choice.m_tCerData.m_u32CerType = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Sec_SN", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tCerData.m_u32Sec_SN = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Encry_State", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tCerData.m_u32Encry_State = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Hash", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tCerData.m_na8Hash, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else if (0 == strcmp("Private_Key", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tCerData.m_na8Private_KEY, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else if (0 == strcmp("Cer_Data", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tCerData.m_na8Cer_Data, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
        p_ptDate->choice.m_tCerData.m_u32CerDataLen = strlen(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("reserved", p_ppn8Result[p_u32Num]))
    {
            memcpy(p_ptDate->choice.m_tRXData.m_na8reserved, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "this fild is absent: p_ppn8Result[%d] = %s ", p_u32Num, p_ppn8Result[p_u32Num]);
        return IS_ERR;
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Select_Alg
 * 功 能 描 述 ： 查询alg表数据的处理函数
 * 输 入 参 数 ： p_ppn8Result/p_u32Num/p_u32Index  收到的信息/个数/索引
 * 输 出 参 数 ： p_ptDate                          查到的数据
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_Select_Alg(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, uint32 p_u32Num, uint32 p_u32Index)
{
    /* 入参检查 */
    if ((NULL == p_ptDate) || (NULL == p_ppn8Result) || (NULL == *p_ppn8Result))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptDate = %p p_ppn8Result = %p *p_ppn8Result = %p ", p_ptDate, p_ppn8Result, *p_ppn8Result);
        return IS_ERR;
    }
    if (0 == strcmp("SN", p_ppn8Result[p_u32Num]))
    {
        /* 不操作 */
    }
    else if (0 == strcmp("Alg_Name", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tAlgData.m_na8Alg_Name, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else if (0 == strcmp("Value", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tAlgData.m_u32Value = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("reserved", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tAlgData.m_na8Reserved, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "this fild is absent: p_ppn8Result[%d] = %s ", p_u32Num, p_ppn8Result[p_u32Num]);
        return IS_ERR;
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Select_DevState
 * 功 能 描 述 ： 查询设备状态表数据的处理函数
 * 输 入 参 数 ： p_ppn8Result/p_u32Num/p_u32Index  收到的信息/个数/索引
 * 输 出 参 数 ： p_ptDate                          查到的数据
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_Select_DevState(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, uint32 p_u32Num, uint32 p_u32Index)
{
    /* 入参检查 */
    if ((NULL == p_ptDate) || (NULL == p_ppn8Result) || (NULL == *p_ppn8Result))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptDate = %p p_ppn8Result = %p *p_ppn8Result = %p ", p_ptDate, p_ppn8Result, *p_ppn8Result);
        return IS_ERR;
    }
    if (0 == strcmp("SN", p_ppn8Result[p_u32Num]))
    {
        /* 不操作 */
    }
    else if (0 == strcmp("Time", p_ppn8Result[p_u32Num]))
    {
        /* 不操作 */
    }
    else if (0 == strcmp("DevID", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tDevstateData.m_na8DevID, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else if (0 == strcmp("IP", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tDevstateData.m_na8IP, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else if (0 == strcmp("HardVer", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tDevstateData.m_na8HardVer, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else if (0 == strcmp("SystemVer", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tDevstateData.m_na8SystemVer, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else if (0 == strcmp("SoftVer", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tDevstateData.m_na8SoftVer, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else if (0 == strcmp("DevTemperature", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u32DevTemperature = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Gnss_unavailable", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u32Gnss_unavailable = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Gnss_PDOPofUnder5", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u32Gnss_PDOPofUnder5 = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Gnss_inViewOfUnder5", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u32Gnss_inViewOfUnder5 = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("HardWorkState", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u32HardWorkState = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("V2xState", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u32V2xState = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("CommumicationState", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u32CommumicationState = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("AppState", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u32AppState = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("V2xTraffic", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u64V2xTraffic = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("DiskState", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u32DiskState = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("CPU", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u32CPU = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Memory", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u32Memory = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("TotalWorkTime", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u64TotalWorkTime = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("TotalAppFlow", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevstateData.m_u64TotalAppFlow = atoll(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("reserved", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tDevstateData.m_na8reserved, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "this fild is absent: p_ppn8Result[%d] = %s ", p_u32Num, p_ppn8Result[p_u32Num]);
        return IS_ERR;
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Select_DevFault
 * 功 能 描 述 ： 查询设备故障表数据的处理函数
 * 输 入 参 数 ： p_ppn8Result/p_u32Num/p_u32Index  收到的信息/个数/索引
 * 输 出 参 数 ： p_ptDate                          查到的数据
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_Select_DevFault(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, uint32 p_u32Num, uint32 p_u32Index)
{
    /* 入参检查 */
    if ((NULL == p_ptDate) || (NULL == p_ppn8Result) || (NULL == *p_ppn8Result))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptDate = %p p_ppn8Result = %p *p_ppn8Result = %p ", p_ptDate, p_ppn8Result, *p_ppn8Result);
        return IS_ERR;
    }
    if (0 == strcmp("SN", p_ppn8Result[p_u32Num]))
    {
        /* 不操作 */
    }
    else if (0 == strcmp("FaultTime", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tDevFaultData.m_na8FaultTime, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else if (0 == strcmp("FaultLv", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevFaultData.m_u32FaultLv =  atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("FaultType", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevFaultData.m_u32FaultType = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Self_Recovery", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tDevFaultData.m_u32Self_Recovery = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("reserved", p_ppn8Result[p_u32Num]))
    {
        memcpy(p_ptDate->choice.m_tDevFaultData.m_na8reserved, p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "this fild is absent: p_ppn8Result[%d] = %s ", p_u32Num, p_ppn8Result[p_u32Num]);
        return IS_ERR;
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Select_SenSing
 * 功 能 描 述 ： 查询设备感知表数据的处理函数
 * 输 入 参 数 ： p_ppn8Result/p_u32Num/p_u32Index  收到的信息/个数/索引
 * 输 出 参 数 ： p_ptDate                          查到的数据
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
__attribute__((unused))  static int DataBase_Select_SenSing(SQL_STRUCTURE_t *p_ptDate, char **p_ppn8Result, int p_u32Num, int p_u32Index)
{
    /* 入参检查 */
    if ((NULL == p_ptDate) || (NULL == p_ppn8Result) || (NULL == *p_ppn8Result))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_ptDate = %p p_ppn8Result = %p *p_ppn8Result = %p ", p_ptDate, p_ppn8Result, *p_ppn8Result);
        return IS_ERR;
    }
    if (0 == strcmp("SN", p_ppn8Result[p_u32Num]))
    {
        /* 不操作 */
    }
    else if (0 == strcmp("Time", p_ppn8Result[p_u32Num]))
    {
        /* 不操作 */
    }
    else if (0 == strcmp("Rele_SN", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tSen_DevData.m_u32Rele_SN = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("DevID", p_ppn8Result[p_u32Num]))
    {
        memcpy(&(p_ptDate->choice.m_tSen_DevData.m_na8DevID), p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else if (0 == strcmp("DevType", p_ppn8Result[p_u32Num]))
    {
        p_ptDate->choice.m_tSen_DevData.m_u32DevType = atoi(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("Data", p_ppn8Result[p_u32Num]))
    {
        memcpy(&(p_ptDate->choice.m_tSen_DevData.m_na8Data), p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
        p_ptDate->choice.m_tSen_DevData.m_u32DataLen = strlen(p_ppn8Result[p_u32Index]);
    }
    else if (0 == strcmp("reserved", p_ppn8Result[p_u32Num]))
    {
        memcpy(&(p_ptDate->choice.m_tSen_DevData.m_na8reserved), p_ppn8Result[p_u32Index], strlen(p_ppn8Result[p_u32Index]));
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "this fild is absent: p_ppn8Result[%d] = %s ", p_u32Num, p_ppn8Result[p_u32Num]);
        return IS_ERR;
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_IsTabExists
 * 功 能 描 述 ： 检查当前数据库是否存在相同名字的表
 * 输 入 参 数 ： p_pn8_Tabname/p_pptsqliteDb    表名/数据库句柄
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ：  黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0     黄赛  Create
***********************************************************************/
static int DataBase_IsTabExists(char* p_pn8_Tabname, sqlite3 **p_pptsqliteDb)
{
    /* 入参检查 */
    if ((NULL == p_pn8_Tabname) || (NULL == p_pptsqliteDb) || (NULL == *p_pptsqliteDb))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p p_pptsqliteDb = %p *p_pptsqliteDb = %p ", p_pn8_Tabname, p_pptsqliteDb, *p_pptsqliteDb);
        return IS_ERR;
    }
    int8* l_pn8buff = NULL;
    char **l_ppn8Result = 0;
    int32 l_n32column = PRESENT;
    int32 l_n32row = PRESENT;
    int8* l_pn8ErrMsg = NULL;
    uint32 l_u32Ret = 0;
    /* 分配缓冲区用来存放指令 */
    l_pn8buff = malloc(sizeof(int8) * 100);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    /* 检查表是否存在，打印要检查的表名 */
    sprintf(l_pn8buff, SELECT_TAB_ISEXISTS, p_pn8_Tabname);
    l_u32Ret = sqlite3_get_table(*p_pptsqliteDb, l_pn8buff, &l_ppn8Result, &l_n32row, &l_n32column, &l_pn8ErrMsg);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sqlite3_get_table is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
        sqlite3_free(l_pn8ErrMsg);
        sqlite3_free_table(l_ppn8Result);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    /* 释放缓冲区 */
    free(l_pn8buff);
    l_pn8buff = NULL;
    /* 存在表，但当前表数据是空 */
    if (1 > l_n32row)
    {
        return ABSENT;
    }
    sqlite3_free_table(l_ppn8Result);
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_OpenDB
 * 功 能 描 述 ： 打开指定数据库，并返回数据库操作句柄
 * 输 入 参 数 ： p_pn8filename     数据库文件名
 * 输 出 参 数 ： p_pptsqliteDb     数据库句柄
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static uint32 DataBase_OpenDB(const char *p_pn8filename, sqlite3 **p_pptsqliteDb)
{
    /* 入参检查 */
    if ((NULL == p_pn8filename) || (NULL == p_pptsqliteDb))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8filename = %p p_pptsqliteDb = %p *p_pptsqliteDb = %p ", p_pn8filename, p_pptsqliteDb, *p_pptsqliteDb);
        return IS_ERR;
    }
    uint32 l_u32Ret = 0;
    /* UTF-16格式转换 */
    /* 操作数据库接口，打开数据库, 不存在就创建 */
    l_u32Ret = sqlite3_open(p_pn8filename, p_pptsqliteDb);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sqlite3_open is err: p_pn8filename = %s p_pptsqliteDb = %p *p_pptsqliteDb = %p ", p_pn8filename, p_pptsqliteDb, *p_pptsqliteDb);
        return IS_ERR;
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_CloseDB
 * 功 能 描 述 ： 关闭数据库的句柄
 * 输 入 参 数 ： p_pptsqliteDb    数据库句柄
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static uint32 DataBase_CloseDB(sqlite3 **p_pptsqliteDb)
{
    /* 入参检查 */
    if ((NULL == p_pptsqliteDb) || (NULL == *p_pptsqliteDb))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pptsqliteDb = %p *p_pptsqliteDb = %p ", p_pptsqliteDb, *p_pptsqliteDb);
        return IS_ERR;
    }
    uint32 l_u32Ret = 0;
    /* 关闭数据库句柄 */
    l_u32Ret = sqlite3_close(*p_pptsqliteDb);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sqlite3_close is err: l_u32Ret = %d *p_pptsqliteDb = %p ", l_u32Ret, *p_pptsqliteDb);
        return IS_ERR;
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_CreatTab
 * 功 能 描 述 ： 在数据库中创建表
 * 输 入 参 数 ： p_pn8_Tabname   表名
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static uint32 DataBase_CreatTab(char *p_pn8_Tabname)
{
    /* 入参检查 */
    if (NULL == p_pn8_Tabname)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p ", p_pn8_Tabname);
        return IS_ERR;
    }
    uint32 l_u32Ret = 0;
    int8* l_pn8buff = NULL;
    int8* l_pn8ErrMsg = NULL;
    uint8 l_u8Type = 0;
    sqlite3* l_ptsqliteDb = NULL;
    /* 根据表名匹配类型 */
    l_u32Ret = DataBase_TabNameToDbId(p_pn8_Tabname, &l_ptsqliteDb, &l_u8Type);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_TabNameToDbId is err: p_pn8_Tabname = %s l_u32Ret = %d", p_pn8_Tabname, l_u32Ret);
        return IS_ERR;
    }
    /* 判空检查 */
    if (NULL == l_ptsqliteDb)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is null: l_ptsqliteDb = %p ", l_ptsqliteDb);
        return IS_ERR;
    }
    /* 检查数据库状态 */
    l_u32Ret = sqlite3_busy_timeout(l_ptsqliteDb, DB_BUSY_TIMEOUT);
    if (SQLITE_BUSY == l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is busy: l_ptsqliteDb = %p l_u32Ret =%d ", l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 检查当前表是否存在，存在退出，不存在创建 */
    /* 检查过程出错 */
    l_u32Ret = DataBase_IsTabExists(p_pn8_Tabname, &l_ptsqliteDb);
    if (IS_ERR == l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_IsTabExists is err: p_pn8_Tabname = %s l_ptsqliteDb =%p l_u32Ret = %d", p_pn8_Tabname, l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 当前表存在 */
    else if (IS_OK == l_u32Ret)
    {
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "DataBase_IsTabExists is present: p_pn8_Tabname = %s l_ptsqliteDb =%p l_u32Ret = %d", p_pn8_Tabname, l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 当前表不存在 */
    else
    {
        l_pn8buff = malloc(sizeof(int8) * 5120);
        if (NULL == l_pn8buff)
        {
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
            return IS_ERR;
        }
        /* 根据表类型创建不同的表 */
        switch (l_u8Type)
        {
            case TRXBLOCK_TYPE:
                sprintf(l_pn8buff, CREATE_TAB_TRXSHEET, p_pn8_Tabname);
                break;
            case CER_TYPE:
                sprintf(l_pn8buff, CREATE_TAB_CERSHEET, p_pn8_Tabname);
                break;
            case ALG_TYPE:
                sprintf(l_pn8buff, CREATE_TAB_ALGSHEET, p_pn8_Tabname);
                break;
            case DEVSTATE_TYPE:
                sprintf(l_pn8buff, CREATE_TAB_DEVSTATESHEET, p_pn8_Tabname);
                break;
            case DEVFAULT_TYPE:
                sprintf(l_pn8buff, CREATE_TAB_DEVFAULT, p_pn8_Tabname);
                break;
            case SENSINGDEVICESDATE_TYPE:
                sprintf(l_pn8buff, CREATE_TAB_SENSINGDEVICESDATESHEET, p_pn8_Tabname);
                break;
            default:
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "this type is absent: l_u8Type = %d ", l_u8Type);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
        }
        /* 操作数据库 */
        l_u32Ret = sqlite3_exec(l_ptsqliteDb, l_pn8buff, NULL, NULL, &l_pn8ErrMsg);
        if(SQLITE_OK != l_u32Ret)
        {
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "create table sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
            sqlite3_free(l_pn8ErrMsg);
            /* 释放缓冲区 */
            free(l_pn8buff);
            l_pn8buff = NULL;
            return IS_ERR;
        }
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_OK;
    }
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_DeleteTab
 * 功 能 描 述 ： 删除指定数据库里面的指定表
 * 输 入 参 数 ： p_pn8_Tabname  表名
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static uint32 DataBase_DeleteTab(char *p_pn8_Tabname)
{
    /* 入参检查 */
    if (NULL == p_pn8_Tabname)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p ", p_pn8_Tabname);
        return IS_ERR;
    }
    int8* l_pn8buff = NULL;
    uint32 l_u32Ret = 0;
    int8* l_pn8ErrMsg = NULL;
    uint8 l_u8Type = 0;
    sqlite3* l_ptsqliteDb = NULL;
    /* 根据表名匹配类型 */
    l_u32Ret = DataBase_TabNameToDbId(p_pn8_Tabname, &l_ptsqliteDb, &l_u8Type);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_TabNameToDbId is err: p_pn8_Tabname = %s l_u32Ret = %d", p_pn8_Tabname, l_u32Ret);
        return IS_ERR;
    }
    l_pn8buff = malloc(sizeof(int8) * 5120);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    sprintf(l_pn8buff, DELETE_TABLE, p_pn8_Tabname);
    l_u32Ret = sqlite3_exec(l_ptsqliteDb, l_pn8buff, NULL, NULL, &l_pn8ErrMsg);
    if(SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "create table sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
        sqlite3_free(l_pn8ErrMsg);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    /* 释放缓冲区 */
    free(l_pn8buff);
    l_pn8buff = NULL;
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Tab_Insert
 * 功 能 描 述 ： 在表中插入数据
 * 输 入 参 数 ： p_pn8_Tabname/p_ptMsgDataSourceDate     表名/要插入的数据
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static uint32 DataBase_Tab_Insert(char *p_pn8_Tabname, DataBaseMsgData_t *p_ptMsgDataSourceDate)
{
    /* 入参检查 */
    if ((NULL == p_pn8_Tabname) || (NULL == p_ptMsgDataSourceDate) || (MAX_INSERT_NUM < p_ptMsgDataSourceDate->m_u32Tab_DataNum))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p p_ptMsgDataSourceDate = %p ", p_pn8_Tabname, p_ptMsgDataSourceDate);
        return IS_ERR;
    }
    int8* l_pn8buff = NULL;
    sqlite3_stmt *l_ptsqlitestmt = NULL;
    uint32 l_u32Ret = 0;
    uint32 l_u32i = 0;
    int8* l_pn8ErrMsg = NULL;
    uint8 l_u8Type = 0;
    sqlite3* l_ptsqliteDb = NULL;
    /* 根据表名匹配类型 */
    l_u32Ret = DataBase_TabNameToDbId(p_pn8_Tabname, &l_ptsqliteDb, &l_u8Type);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_TabNameToDbId is err: p_pn8_Tabname = %s l_u32Ret = %d", p_pn8_Tabname, l_u32Ret);
        return IS_ERR;
    }
    /* 判空检查 */
    if (NULL == l_ptsqliteDb)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is null: l_ptsqliteDb = %p ", l_ptsqliteDb);
        return IS_ERR;
    }
    /* 检查数据库状态 */
    l_u32Ret = sqlite3_busy_timeout(l_ptsqliteDb, DB_BUSY_TIMEOUT);
    if (SQLITE_BUSY == l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is busy: l_ptsqliteDb = %p l_u32Ret =%d ", l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 检查当前表是否存在, 不存在退出 */
    l_u32Ret = DataBase_IsTabExists(p_pn8_Tabname, &l_ptsqliteDb);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_IsTabExists is err: p_pn8_Tabname = %s l_ptsqliteDb =%p l_u32Ret = %d", p_pn8_Tabname, l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    l_pn8buff = malloc(sizeof(int8) * 5120);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    /* 在对应的表里面插入数据 */
    switch (l_u8Type)
    {
        /* 插入V2X数据 */
        case TRXBLOCK_TYPE:
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "BEGIN TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "BEGIN TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            sprintf(l_pn8buff, INSERT_V2XMESSAGEDATE, p_pn8_Tabname);
            l_u32Ret = sqlite3_prepare_v2(l_ptsqliteDb, l_pn8buff, strlen(l_pn8buff), &l_ptsqlitestmt, 0);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sqlite3_prepare_v2 is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
            }
            for (l_u32i = 0;l_u32i < p_ptMsgDataSourceDate->m_u32Tab_DataNum; l_u32i++)
            {
                sqlite3_reset(l_ptsqlitestmt);
                l_u32Ret = DataBase_InsertV2XData(l_ptsqlitestmt, p_ptMsgDataSourceDate->m_tTab_Data, l_u32i);
                if (IS_OK != l_u32Ret)
                {
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_InsertV2XData is err: l_u32Ret = %d p_pn8_Tabname = %s l_u32i = %d", l_u32Ret, p_pn8_Tabname, l_u32i);
                    continue;
                }
                sqlite3_step(l_ptsqlitestmt);
            }
            sqlite3_finalize(l_ptsqlitestmt);
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "COMMIT TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "COMMIT TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            break;
        /* 插入证书数据 */
        case CER_TYPE:
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "BEGIN TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "BEGIN TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            sprintf(l_pn8buff, INSERT_CERDATE, p_pn8_Tabname);
            l_u32Ret = sqlite3_prepare_v2(l_ptsqliteDb, l_pn8buff, strlen(l_pn8buff), &l_ptsqlitestmt, 0);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sqlite3_prepare_v2 is err: l_u32Ret = %d p_pn8_Tabname = %s", l_u32Ret, p_pn8_Tabname);
            }
            for (l_u32i = 0; l_u32i < p_ptMsgDataSourceDate->m_u32Tab_DataNum; l_u32i++)
            {
                sqlite3_reset(l_ptsqlitestmt);
                l_u32Ret = DataBase_InsertCerData(l_ptsqlitestmt, p_ptMsgDataSourceDate->m_tTab_Data, l_u32i);
                if (IS_OK != l_u32Ret)
                {
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_InsertCerData is err: l_u32Ret = %d p_pn8_Tabname = %s l_u32i = %d", l_u32Ret, p_pn8_Tabname, l_u32i);
                    continue;
                }
                sqlite3_step(l_ptsqlitestmt);
            }
            sqlite3_finalize(l_ptsqlitestmt);
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "COMMIT TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "COMMIT TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            break;
        /* 插入算法 */
        case ALG_TYPE:
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "BEGIN TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "BEGIN TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            sprintf(l_pn8buff, INSERT_ALGDATE, p_pn8_Tabname);
            l_u32Ret = sqlite3_prepare_v2(l_ptsqliteDb, l_pn8buff, strlen(l_pn8buff), &l_ptsqlitestmt, 0);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sqlite3_prepare_v2 is err: l_u32Ret = %d p_pn8_Tabname = %s", l_u32Ret, p_pn8_Tabname);
            }
            for (l_u32i = 0;l_u32i < p_ptMsgDataSourceDate->m_u32Tab_DataNum;l_u32i++)
            {
                sqlite3_reset(l_ptsqlitestmt);
                l_u32Ret = DataBase_InsertAlgData(l_ptsqlitestmt, p_ptMsgDataSourceDate->m_tTab_Data, l_u32i);
                if (IS_OK != l_u32Ret)
                {
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_InsertAlgData is err: l_u32Ret = %d p_pn8_Tabname = %s l_u32i = %d", l_u32Ret, p_pn8_Tabname, l_u32i);
                    continue;
                }
                sqlite3_step(l_ptsqlitestmt);
            }
            sqlite3_finalize(l_ptsqlitestmt);
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "COMMIT TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "COMMIT TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            break;
        /* 插入设备状态数据 */
        case DEVSTATE_TYPE:
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "BEGIN TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "BEGIN TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            sprintf(l_pn8buff, INSERT_DEVSTATUSDATE, p_pn8_Tabname);
            l_u32Ret = sqlite3_prepare_v2(l_ptsqliteDb, l_pn8buff, strlen(l_pn8buff), &l_ptsqlitestmt, 0);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sqlite3_prepare_v2 is err: l_u32Ret = %d p_pn8_Tabname = %s", l_u32Ret, p_pn8_Tabname);
            }
            for (l_u32i = 0;l_u32i < p_ptMsgDataSourceDate->m_u32Tab_DataNum;l_u32i++)
            {
                sqlite3_reset(l_ptsqlitestmt);
                l_u32Ret = DataBase_InsertDevStateData(l_ptsqlitestmt, p_ptMsgDataSourceDate->m_tTab_Data, l_u32i);
                if (IS_OK != l_u32Ret)
                {
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_InsertDevStateData is err: l_u32Ret = %d p_pn8_Tabname = %s l_u32i = %d", l_u32Ret, p_pn8_Tabname, l_u32i);
                    continue;
                }
                sqlite3_step(l_ptsqlitestmt);
            }
            sqlite3_finalize(l_ptsqlitestmt);
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "COMMIT TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "COMMIT TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            break;
        /* 插入设备故障数据 */
        case DEVFAULT_TYPE:
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "BEGIN TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "BEGIN TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            sprintf(l_pn8buff, INSERT_DEVFAULTDATE, p_pn8_Tabname);
            l_u32Ret = sqlite3_prepare_v2(l_ptsqliteDb, l_pn8buff, strlen(l_pn8buff), &l_ptsqlitestmt, 0);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sqlite3_prepare_v2 is err: l_u32Ret = %d p_pn8_Tabname = %s", l_u32Ret, p_pn8_Tabname);
            }
            for (l_u32i = 0;l_u32i < p_ptMsgDataSourceDate->m_u32Tab_DataNum;l_u32i++)
            {
                sqlite3_reset(l_ptsqlitestmt);
                l_u32Ret = DataBase_InsertDevFaultData(l_ptsqlitestmt, p_ptMsgDataSourceDate->m_tTab_Data, l_u32i);
                if (IS_OK != l_u32Ret)
                {
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_InsertDevFaultData is err: l_u32Ret = %d p_pn8_Tabname = %s l_u32i = %d", l_u32Ret, p_pn8_Tabname, l_u32i);
                    continue;
                }
                sqlite3_step(l_ptsqlitestmt);
            }
            sqlite3_finalize(l_ptsqlitestmt);
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "COMMIT TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "COMMIT TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            break;
        /* 设备感知信息 */
        case SENSINGDEVICESDATE_TYPE:
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "BEGIN TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "BEGIN TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            sprintf(l_pn8buff, INSERT_SENSINGDEVICESDATE, p_pn8_Tabname);
            l_u32Ret = sqlite3_prepare_v2(l_ptsqliteDb, l_pn8buff, strlen(l_pn8buff), &l_ptsqlitestmt, 0);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sqlite3_prepare_v2 is err: l_u32Ret = %d p_pn8_Tabname = %s ", l_u32Ret, p_pn8_Tabname);
            }
            for (l_u32i = 0;l_u32i < p_ptMsgDataSourceDate->m_u32Tab_DataNum;l_u32i++)
            {
                sqlite3_reset(l_ptsqlitestmt);
                l_u32Ret = DataBase_InsertSenSingData(l_ptsqlitestmt, p_ptMsgDataSourceDate->m_tTab_Data, l_u32i);
                if (IS_OK != l_u32Ret)
                {
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_InsertSenSingData is err: l_u32Ret = %d p_pn8_Tabname = %s l_u32i = %d", l_u32Ret, p_pn8_Tabname, l_u32i);
                    continue;
                }
                sqlite3_step(l_ptsqlitestmt);
            }
            sqlite3_finalize(l_ptsqlitestmt);
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, "COMMIT TRANSACTION;", NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "COMMIT TRANSACTION sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            break;
        /* 不能识别的信息 */
        default:
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "type is no case:l_u8Type = %d", l_u8Type);
            /* 释放缓冲区 */
            free(l_pn8buff);
            l_pn8buff = NULL;
            return IS_ERR;
    }
    /* 释放缓冲区 */
    free(l_pn8buff);
    l_pn8buff = NULL;
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_ClearTab
 * 功 能 描 述 ： 清空数据库中相应的表
 * 输 入 参 数 ： p_pn8_Tabname    表名
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-14 V1.0    黄赛   Create
***********************************************************************/
static uint32 DataBase_ClearTab(char *p_pn8_Tabname)
{
    /* 入参检查 */
    if (NULL == p_pn8_Tabname)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p ", p_pn8_Tabname);
        return IS_ERR;
    }
    uint32 l_u32Ret = 0;
    int8* l_pn8ErrMsg = NULL;
    int8* l_pn8buff = NULL;
    uint8 l_u8Type = 0;
    sqlite3* l_ptsqliteDb = NULL;
    /* 根据表名匹配类型 */
    l_u32Ret = DataBase_TabNameToDbId(p_pn8_Tabname, &l_ptsqliteDb, &l_u8Type);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_TabNameToDbId is err: p_pn8_Tabname = %s l_u32Ret = %d", p_pn8_Tabname, l_u32Ret);
        return IS_ERR;
    }
    /* 判空检查 */
    if (NULL == l_ptsqliteDb)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is null: l_ptsqliteDb = %p ", l_ptsqliteDb);
        return IS_ERR;
    }
    /* 检查数据库状态 */
    l_u32Ret = sqlite3_busy_timeout(l_ptsqliteDb, DB_BUSY_TIMEOUT);
    if (SQLITE_BUSY == l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is busy: l_ptsqliteDb = %p l_u32Ret =%d ", l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 检查当前表是否存在, 不存在退出 */
    l_u32Ret = DataBase_IsTabExists(p_pn8_Tabname, &l_ptsqliteDb);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_IsTabExists is err: p_pn8_Tabname = %s l_ptsqliteDb =%p l_u32Ret = %d", p_pn8_Tabname, l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 分配空间 */
    l_pn8buff = malloc(sizeof(int8) * 5120);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    sprintf(l_pn8buff, CLEAR_TAB_DATE, p_pn8_Tabname);
    l_u32Ret = sqlite3_exec(l_ptsqliteDb, l_pn8buff, NULL, NULL, &l_pn8ErrMsg);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, " sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
        sqlite3_free(l_pn8ErrMsg);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    sprintf(l_pn8buff, SET_SN_ZERO, p_pn8_Tabname);
    l_u32Ret = sqlite3_exec(l_ptsqliteDb, l_pn8buff, NULL, NULL, &l_pn8ErrMsg);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, " sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
        sqlite3_free(l_pn8ErrMsg);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    /* 释放缓冲区 */
    free(l_pn8buff);
    l_pn8buff = NULL;
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Tab_Delete
 * 功 能 描 述 ： 删除数据库里面指定字段对应指定值所在的行
 * 输 入 参 数 ： p_pn8_Tabname/p_pn8_FileId/p_ptFileValue 表名/字段名/字段值
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
static uint32 DataBase_Tab_Delete(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue)
{
    /* 入参检查 */
    if ((NULL == p_pn8_Tabname) || (NULL == p_pn8_FileId) || (NULL == p_ptFileValue))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p p_pn8_FileId = %p p_ptFileValue = %p", p_pn8_Tabname, p_pn8_FileId, p_ptFileValue);
        return IS_ERR;
    }
    uint32 l_u32Ret = 0;
    int8* l_pn8ErrMsg = NULL;
    int8* l_pn8buff = NULL;
    sqlite3* l_ptsqliteDb = NULL;
    uint8 l_u8Type = 0;
    DataBaseMsgData_t l_tSelectMsg = {0};
    /* 根据表名匹配类型 */
    l_u32Ret = DataBase_TabNameToDbId(p_pn8_Tabname, &l_ptsqliteDb, &l_u8Type);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_TabNameToDbId is err: p_pn8_Tabname = %s l_u32Ret = %d", p_pn8_Tabname, l_u32Ret);
        return IS_ERR;
    }
    /* 判空检查 */
    if (NULL == l_ptsqliteDb)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is null: l_ptsqliteDb = %p ", l_ptsqliteDb);
        return IS_ERR;
    }
    l_u32Ret = sqlite3_busy_timeout(l_ptsqliteDb, DB_BUSY_TIMEOUT);
    if (SQLITE_BUSY == l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is busy: l_ptsqliteDb = %p l_u32Ret =%d ", l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 检查当前表是否存在, 不存在退出 */
    l_u32Ret = DataBase_IsTabExists(p_pn8_Tabname, &l_ptsqliteDb);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_IsTabExists is err: p_pn8_Tabname = %s l_ptsqliteDb =%p l_u32Ret = %d", p_pn8_Tabname, l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 更新之前先确认是否存在这个字段和字段值的对应关系 */
    l_u32Ret = DataBase_Tab_Select(p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, &l_tSelectMsg);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Tab_Select is err: p_pn8_Tabname = %s p_pn8_FileId =%s l_u32Ret = %d", p_pn8_Tabname, p_pn8_FileId, l_u32Ret);
        return IS_ERR;
    }
    else
    {
        if (0 == l_tSelectMsg.m_u32Tab_DataNum)
        {
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "select is zero:p_pn8_Tabname = %s p_pn8_FileId = %p", p_pn8_Tabname, p_pn8_FileId);
            return IS_ERR;
        }
        else
        {
            /* 分配空间 */
            l_pn8buff = malloc(sizeof(int8) * 5120);
            if (NULL == l_pn8buff)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
                return IS_ERR;
            }
            /* 判断字段类型 */
            if (enum_int == p_ptFileValue->enumTypeFlag)
            {
                sprintf(l_pn8buff, TAB_DELETE_FILEID_DATE_INT, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue->choic.m_u64FileValue);
            }
            else if (enum_string == p_ptFileValue->enumTypeFlag)
            {
                sprintf(l_pn8buff, TAB_DELETE_FILEID_DATE_STRING, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue->choic.m_na8FileValue);
            }
            else
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "typeflag is err: TypeFlag = %d ", p_ptFileValue->enumTypeFlag);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            l_u32Ret = sqlite3_exec(l_ptsqliteDb, l_pn8buff, NULL, NULL, &l_pn8ErrMsg);
            if (SQLITE_OK != l_u32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, " sqlite3_exec is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
                sqlite3_free(l_pn8ErrMsg);
                /* 释放缓冲区 */
                free(l_pn8buff);
                l_pn8buff = NULL;
                return IS_ERR;
            }
            /* 释放缓冲区 */
            free(l_pn8buff);
            l_pn8buff = NULL;
        }
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： FL_DataBase_Tab_Update
 * 功 能 描 述 ： 更新数据库中相关表的数据
 * 输 入 参 数 ： p_pn8_Tabname/p_pn8_FileId/p_ptFileValue/p_ptSqlSourceDate
 *              表名/字段名/字段值/源内容
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
static uint32 DataBase_Tab_Update(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate)
{
    /* 入参检查 */
    if ((NULL == p_pn8_Tabname) || (NULL == p_pn8_FileId)
            || (NULL == p_ptFileValue) || (NULL == p_ptSqlSourceDate))
    {
        /* 初始化后立即调用会导致数据库还没有打开就操作句柄，会使句柄为空 */
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p p_pn8_FileId = %p p_ptFileValue = %p", p_pn8_Tabname, p_pn8_FileId, p_ptFileValue);
        return IS_ERR;
    }
    uint32 l_u32Ret = 0;
    sqlite3* l_ptsqliteDb = NULL;
    uint8 l_u8Type = 0;
    DataBaseMsgData_t l_tSelectMsg = {0};
    /* 根据表名匹配类型 */
    l_u32Ret = DataBase_TabNameToDbId(p_pn8_Tabname, &l_ptsqliteDb, &l_u8Type);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_TabNameToDbId is err: p_pn8_Tabname = %s l_u32Ret = %d", p_pn8_Tabname, l_u32Ret);
        return IS_ERR;
    }
    /* 判空检查 */
    if (NULL == l_ptsqliteDb)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is null: l_ptsqliteDb = %p ", l_ptsqliteDb);
        return IS_ERR;
    }
    l_u32Ret = sqlite3_busy_timeout(l_ptsqliteDb, DB_BUSY_TIMEOUT);
    if (SQLITE_BUSY == l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is busy: l_ptsqliteDb = %p l_u32Ret =%d ", l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 检查当前表是否存在, 不存在退出 */
    l_u32Ret = DataBase_IsTabExists(p_pn8_Tabname, &l_ptsqliteDb);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_IsTabExists is err: p_pn8_Tabname = %s l_ptsqliteDb =%p l_u32Ret = %d", p_pn8_Tabname, l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 更新之前先确认是否存在这个字段和字段值的对应关系 */
    l_u32Ret = DataBase_Tab_Select(p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, &l_tSelectMsg);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Tab_Select is err: p_pn8_Tabname = %s p_pn8_FileId =%s l_u32Ret = %d", p_pn8_Tabname, p_pn8_FileId, l_u32Ret);
        return IS_ERR;
    }
    else
    {
        if (0 == l_tSelectMsg.m_u32Tab_DataNum)
        {
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "select is zero:p_pn8_Tabname = %s p_pn8_FileId = %s", p_pn8_Tabname, p_pn8_FileId);
            return IS_ERR;
        }
        else
        {
            switch (p_ptSqlSourceDate->structenumtype)
            {
                #if DATABASE_BL
                case enum_TRXBLOCK_TYPE:
                    if (MAX_RCVSND_NUM < p_ptSqlSourceDate->choice.m_tRXData.m_u32DataLen)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "rtx datalen out of rang :p_pn8_Tabname = %s  len = %p", p_pn8_Tabname, p_ptSqlSourceDate->choice.m_tRXData.m_u32DataLen);
                        return IS_ERR;
                    }
                    l_u32Ret = DataBase_Update_TRXData(&l_ptsqliteDb, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, p_ptSqlSourceDate);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update TRX update is err: p_pn8_Tabname = %s p_pn8_FileId = %s", p_pn8_Tabname, p_pn8_FileId);
                        return IS_ERR;
                    }
                    break;
                #endif
                case enum_CER_TYPE:
                    if (MAX_CERDATA_NUM < p_ptSqlSourceDate->choice.m_tCerData.m_u32CerDataLen)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "cer datalen out of rang :p_pn8_Tabname = %s  len = %p", p_pn8_Tabname, p_ptSqlSourceDate->choice.m_tCerData.m_u32CerDataLen);
                        return IS_ERR;
                    }
                    l_u32Ret = DataBase_Update_CerData(&l_ptsqliteDb, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, p_ptSqlSourceDate);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update CER update is err: p_pn8_Tabname = %s p_pn8_FileId = %s", p_pn8_Tabname, p_pn8_FileId);
                        return IS_ERR;
                    }
                    break;
                case enum_ALG_TYPE:
                    l_u32Ret = DataBase_Update_AlgData(&l_ptsqliteDb, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, p_ptSqlSourceDate);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update ALG update is err: p_pn8_Tabname = %s p_pn8_FileId = %s", p_pn8_Tabname, p_pn8_FileId);
                        return IS_ERR;
                    }
                    break;
                case enum_DEVSTATE_TYPE:
                    l_u32Ret = DataBase_Update_DevStateData(&l_ptsqliteDb, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, p_ptSqlSourceDate);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update DEV STATE update is err: p_pn8_Tabname = %s p_pn8_FileId = %s", p_pn8_Tabname, p_pn8_FileId);
                        return IS_ERR;
                    }
                    break;
                case enum_DEVFAULT_TYPE:
                    l_u32Ret = DataBase_Update_DevFaultData(&l_ptsqliteDb, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, p_ptSqlSourceDate);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update DEV FAULT update is err: p_pn8_Tabname = %s p_pn8_FileId = %s", p_pn8_Tabname, p_pn8_FileId);
                        return IS_ERR;
                    }
                    break;
                #if DATABASE_BL
                case enum_SENSINGDEVICESDATA_TYPE:
                    if (MAX_RCVSND_NUM < p_ptSqlSourceDate->choice.m_tSen_DevData.m_u32DataLen)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sensing datalen out of rang:p_pn8_Tabname = %s  len = %p", p_pn8_Tabname, p_ptSqlSourceDate->choice.m_tSen_DevData.m_u32DataLen);
                        return IS_ERR;
                    }
                    l_u32Ret = DataBase_Update_SenSingData(&l_ptsqliteDb, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue, p_ptSqlSourceDate);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "update SENSING update is err:p_pn8_Tabname = %s  p_pn8_FileId = %s", p_pn8_Tabname, p_pn8_FileId);
                        return IS_ERR;
                    }
                    break;
                #endif
                default:
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "no this case", p_pn8_Tabname, p_pn8_FileId);
                    return IS_ERR;
            }
        }
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Tab_Select
 * 功 能 描 述 ： 在数据库中查找相应字段内容所在行的数据
 * 输 入 参 数 ： p_pn8_Tabname/p_pn8_FileId/p_ptFileValue  表名/字段名/字段值
 * 输 出 参 数 ： p_ptMsgDataSourceDate   查找的值
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-15 V1.0    黄赛   Create
***********************************************************************/
static uint32 DataBase_Tab_Select(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue, DataBaseMsgData_t *p_ptMsgDataSourceDate)
{
    /* 入参检查 */
    if ((NULL == p_pn8_Tabname) || (NULL == p_pn8_FileId)
            || (NULL == p_ptFileValue) || (NULL == p_ptMsgDataSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p p_pn8_FileId = %p p_ptFileValue = %p", p_pn8_Tabname, p_pn8_FileId, p_ptFileValue);
        return IS_ERR;
    }
    uint32 l_u32Ret = 0;
    uint32 l_u32i = 0;
    uint32 l_u32j = 0;
    uint32 l_u32index = 0;
    int8* l_pn8ErrMsg = NULL;
    int8* l_pn8buff = NULL;
    char **l_ppResult = NULL;
    int32 l_n32column = 0, l_n32row = 0;
    uint8 l_u8Type = 0;
    sqlite3* l_ptsqliteDb = NULL;
    /* 根据表名匹配类型 */
    l_u32Ret = DataBase_TabNameToDbId(p_pn8_Tabname, &l_ptsqliteDb, &l_u8Type);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_TabNameToDbId is err: p_pn8_Tabname = %s l_u32Ret = %d", p_pn8_Tabname, l_u32Ret);
        return IS_ERR;
    }
    /* 判空检查 */
    if (NULL == l_ptsqliteDb)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is null: l_ptsqliteDb = %p ", l_ptsqliteDb);
        return IS_ERR;
    }
    /* 检查数据库忙状态 */
    l_u32Ret = sqlite3_busy_timeout(l_ptsqliteDb, DB_BUSY_TIMEOUT);
    if (SQLITE_BUSY == l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is busy: l_ptsqliteDb = %p l_u32Ret =%d ", l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 检查当前表是否存在, 不存在退出 */
    l_u32Ret = DataBase_IsTabExists(p_pn8_Tabname, &l_ptsqliteDb);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_IsTabExists is err: p_pn8_Tabname = %s l_ptsqliteDb =%p l_u32Ret = %d", p_pn8_Tabname, l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 分配空间 */
    l_pn8buff = malloc(sizeof(int8) * 5120);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    if (enum_string == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, SELECT_DB_TAB_FILE_DATE_STRING, p_pn8_Tabname, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue->choic.m_na8FileValue);
    }
    else if (enum_int == p_ptFileValue->enumTypeFlag)
    {
        sprintf(l_pn8buff, SELECT_DB_TAB_FILE_DATE_INT, p_pn8_Tabname, p_pn8_Tabname, p_pn8_FileId, p_ptFileValue->choic.m_u64FileValue);
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "typeflag is err: TypeFlag = %d ", p_ptFileValue->enumTypeFlag);
        /* 释放缓冲区 */
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    /* 使用get_table查询数据库 */
    l_u32Ret = sqlite3_get_table(l_ptsqliteDb, l_pn8buff, &l_ppResult, &l_n32row, &l_n32column, &l_pn8ErrMsg );
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sqlite3_get_table is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
        /* 释放缓冲区 */
        sqlite3_free_table(l_ppResult);
        sqlite3_free(l_pn8ErrMsg);
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    free(l_pn8buff);
    l_pn8buff = NULL;
    if (MAX_INSERT_NUM < l_n32row)
    {
        p_ptMsgDataSourceDate->m_u32Tab_DataNum = MAX_INSERT_NUM;
    }
    else
    {
        p_ptMsgDataSourceDate->m_u32Tab_DataNum = l_n32row;
    }
    /* 前面第一行数据是字段名称，从 n32column 索引开始才是真正的数据 */
    l_u32index = l_n32column;
    for (l_u32i = 0;l_u32i < p_ptMsgDataSourceDate->m_u32Tab_DataNum;l_u32i++ )
    {
        /* ppResult 的字段值是连续的，从第0索引到第 n32column - 1索引都是字段名称 */
        /* 第 n32column 索引开始，后面都是字段值，它把一个二维的表一维形式来表示 */
        for (l_u32j = 0 ;l_u32j < l_n32column; l_u32j++)
        {
            switch (l_u8Type)
            {
                #if DATABASE_BL
                /* 暂时不提供收发消息表的查询功能 */
                case TRXBLOCK_TYPE:
                    p_ptMsgDataSourceDate->m_tTab_Data[l_u32i].structenumtype = TRXBLOCK_TYPE;
                    l_u32Ret = DataBase_Select_TRX(&(p_ptMsgDataSourceDate->m_tTab_Data[l_u32i]), l_ppResult, l_u32j, l_u32index);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Select_TRX is err: l_u32Ret = %d l_u32j = %d l_u8Type = %d ", l_u32Ret, l_u32j, l_u8Type);
                        /* 释放缓冲区 */
                        sqlite3_free_table(l_ppResult);
                        return IS_ERR;
                    }
                    break;
                #endif
                case CER_TYPE:
                    p_ptMsgDataSourceDate->m_tTab_Data[l_u32i].structenumtype = CER_TYPE;
                    l_u32Ret = DataBase_Select_Cer(&(p_ptMsgDataSourceDate->m_tTab_Data[l_u32i]), l_ppResult, l_u32j, l_u32index);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Select_Cer is err: l_u32Ret = %d l_u32j = %d l_u8Type = %d ", l_u32Ret, l_u32j, l_u8Type);
                        /* 释放缓冲区 */
                        sqlite3_free_table(l_ppResult);
                        return IS_ERR;
                    }
                    break;
                case ALG_TYPE:
                    p_ptMsgDataSourceDate->m_tTab_Data[l_u32i].structenumtype = ALG_TYPE;
                    l_u32Ret = DataBase_Select_Alg(&(p_ptMsgDataSourceDate->m_tTab_Data[l_u32i]), l_ppResult, l_u32j, l_u32index);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Select_Alg is err: l_u32Ret = %d l_u32j = %d l_u8Type = %d ", l_u32Ret, l_u32j, l_u8Type);
                        /* 释放缓冲区 */
                        sqlite3_free_table(l_ppResult);
                        return IS_ERR;
                    }
                    break;
                case DEVSTATE_TYPE:
                    p_ptMsgDataSourceDate->m_tTab_Data[l_u32i].structenumtype = DEVSTATE_TYPE;
                    l_u32Ret = DataBase_Select_DevState(&(p_ptMsgDataSourceDate->m_tTab_Data[l_u32i]), l_ppResult, l_u32j, l_u32index);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Select_DevState is err: l_u32Ret = %d l_u32j = %d l_u8Type = %d ", l_u32Ret, l_u32j, l_u8Type);
                        /* 释放缓冲区 */
                        sqlite3_free_table(l_ppResult);
                        return IS_ERR;
                    }
                    break;
                case DEVFAULT_TYPE:
                    p_ptMsgDataSourceDate->m_tTab_Data[l_u32i].structenumtype = DEVFAULT_TYPE;
                    l_u32Ret = DataBase_Select_DevFault(&(p_ptMsgDataSourceDate->m_tTab_Data[l_u32i]), l_ppResult, l_u32j, l_u32index);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Select_DevFault is err: l_u32Ret = %d l_u32j = %d l_u8Type = %d ", l_u32Ret, l_u32j, l_u8Type);
                        /* 释放缓冲区 */
                        sqlite3_free_table(l_ppResult);
                        return IS_ERR;
                    }
                    break;
                #if DATABASE_BL
                /* 暂时不向外部提供感知设备表查询功能 */
                case SENSINGDEVICESDATE_TYPE:
                    p_ptMsgDataSourceDate->m_tTab_Data[l_u32i].structenumtype = SENSINGDEVICESDATE_TYPE;
                    l_u32Ret = DataBase_Select_SenSing(&(p_ptMsgDataSourceDate->m_tTab_Data[l_u32i]), l_ppResult, l_u32j, l_u32index);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Select_SenSing is err: l_u32Ret = %d l_u32j = %d l_u8Type = %d ", l_u32Ret, l_u32j, l_u8Type);
                        /* 释放缓冲区 */
                        sqlite3_free_table(l_ppResult);
                        return IS_ERR;
                    }
                    break;
                #endif
                default:
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "no this type:l_u8Type = %d", l_u8Type);
                    /* 释放缓冲区 */
                    sqlite3_free_table(l_ppResult);
                    return IS_ERR;
            }
            ++l_u32index;
        }
    }
    sqlite3_free_table(l_ppResult);
    /* 释放缓冲区 */
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： Signal1Hander
 * 功 能 描 述 ： 信号处理函数
 * 输 入 参 数 ： p_n32sig   信号值
 * 输 出 参 数 ： 无
 * 返  回  值  : 无
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-16 V1.0    黄赛   Create
***********************************************************************/
void Signal1Hander(int p_n32sig)
{
    int32 l_n32Ret = 0;
    switch(p_n32sig)
    {
        case SIGUSR1:
            break;
        case SIGALRM:/* 5秒往数据库插入数据 */
            /* 检查数据库是否能操作 */
            if (0 == g_n32SqliteStateFlag)
            {
                if (0 != g_t_DataBaseRXTDateBuff.m_u32Tab_DataNum)
                {
                    /* 插入收发数据 */
                    #if SQL_DEBUG
                    #endif
                    l_n32Ret = DataBase_Tab_Insert(TAB_TRX_DATATIME_NAME, &g_t_DataBaseRXTDateBuff);
                    if (IS_OK != l_n32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert rx data is err");
                    }
                    else
                    {
                        g_t_DataBaseRXTDateBuff.m_u32Tab_DataNum = 0;
                    }
                }
                if (0 != g_t_DataBaseCERDateBuff.m_u32Tab_DataNum)
                {
                    /* 插入证书数据 */
                    l_n32Ret = DataBase_Tab_Insert("CERSheet", &g_t_DataBaseCERDateBuff);
                    if (IS_OK != l_n32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert cer data is err");
                    }
                    else
                    {
                        g_t_DataBaseCERDateBuff.m_u32Tab_DataNum = 0;
                    }
                }
                if (0 != g_t_DataBaseALGDateBuff.m_u32Tab_DataNum)
                {
                    /* 插入算法数据 */
                    l_n32Ret = DataBase_Tab_Insert("ALGSheet", &g_t_DataBaseALGDateBuff);
                    if (IS_OK != l_n32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert alg data is err");
                    }
                    else
                    {
                        g_t_DataBaseALGDateBuff.m_u32Tab_DataNum = 0;
                    }
                }
                if (0 != g_t_DataBaseDEVSTATEDateBuff.m_u32Tab_DataNum)
                {
                    /* 插入设备状态数据 */
                    l_n32Ret = DataBase_Tab_Insert("DEVSTATESheet", &g_t_DataBaseDEVSTATEDateBuff);
                    if (IS_OK != l_n32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert devstate data is err");
                    }
                    else
                    {
                        g_t_DataBaseDEVSTATEDateBuff.m_u32Tab_DataNum = 0;
                    }
                }
                if (0 != g_t_DataBaseDEVFALUTDateBuff.m_u32Tab_DataNum)
                {
                    /* 插入设备故障数据 */
                    l_n32Ret = DataBase_Tab_Insert("DEVFAULTSheet", &g_t_DataBaseDEVFALUTDateBuff);
                    if (IS_OK != l_n32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert devfault data is err");
                    }
                    else
                    {
                        g_t_DataBaseDEVFALUTDateBuff.m_u32Tab_DataNum = 0;
                    }
                }
                if (0 != g_t_DataBaseSENSINGDateBuff.m_u32Tab_DataNum)
                {
                    /* 插入感知设备信息 */
                    l_n32Ret = DataBase_Tab_Insert(TAB_SENSING_DATATIME_NAME, &g_t_DataBaseSENSINGDateBuff);
                    if (IS_OK != l_n32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert sensing data is err");
                    }
                    else
                    {
                        g_t_DataBaseSENSINGDateBuff.m_u32Tab_DataNum = 0;
                    }
                }
            }
            alarm(5);
            break;
        default:      /* 不支持的信号 */
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "this sign is no support");
            return;
    }
    return;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_CreateDir
 * 功 能 描 述 ： 创建文件夹
 * 输 入 参 数 ： p_pn8Flow    文件夹地址
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-24 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_CreateDir(char *p_pn8Flow)
{
    /* 入参检查 */
    if (NULL == p_pn8Flow)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8Flow = %p ", p_pn8Flow);
        return IS_ERR;
    }
    int32 l_n32Ret = 0;
    /* 判断当前文件夹是否存在 */
    l_n32Ret = access(p_pn8Flow, 0);
    if (l_n32Ret < 0)
    {
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "FLOW is absent ");
        l_n32Ret = mkdir(p_pn8Flow, 0777);
        if (0 != l_n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "mkdir is err: p_pn8Flow = %s ", p_pn8Flow);
            perror("mkdir err is :");
            return IS_ERR;
        }
        else
        {
            LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "create flow is ok");
        }
    }
    else
    {
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "FLOW is present, no need to creat");
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： DataBase_Create_Tab_All
 * 功 能 描 述 ： 创建所有的表
 * 输 入 参 数 ： u8Flag     创建证书表和算法表标志位
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-17 V1.0    黄赛   Create
***********************************************************************/
static int DataBase_Create_Tab_All(uint8 p_u8Flag)
{
    int32 l_n32Ret = 0;
    /* 创建表 */
    /* TRX表 */
    l_n32Ret = DataBase_CreatTab(TAB_TRX_DATATIME_NAME);
     if(IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "creat rxt tab is err");
    }
    if (1 == p_u8Flag)
    {
        /* CER表 */
        l_n32Ret = DataBase_CreatTab("CERSheet");
        if(IS_OK != l_n32Ret)
        {
            LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "creat cer tab is err");
        }
        /* ALG表 */
        l_n32Ret = DataBase_CreatTab("ALGSheet");
        if(IS_OK != l_n32Ret)
        {
            LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "creat alg tab is err");
        }
    }
    /* DEVSTATE表 */
    l_n32Ret = DataBase_CreatTab("DEVSTATESheet");
    if(IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "creat devstate tab is err");
    }
    /* DEVFAULT表 */
    l_n32Ret = DataBase_CreatTab("DEVFAULTSheet");
    if(IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "creat devfalut tab is err");
    }
    /*SENDING表 */
    l_n32Ret = DataBase_CreatTab(TAB_SENSING_DATATIME_NAME);
    if(IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "creat sensing tab is err");
    }
    return IS_OK;
}
/***********************************************************************
 * 函 数 名 称 ： Thread_DataBaseInsert_Deal
 * 功 能 描 述 ： 数据库处理线程，每5s创建一个表，每一天创建两个数据库
 * 输 入 参 数 ： 无
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-16 V1.0    黄赛   Create
***********************************************************************/
void Thread_DataBaseInsert_Deal(void *arg)
{
    int32 l_n32Ret = 0;
    key_t l_tKey_Id = 0;
    struct tm *l_ptTm = NULL;
    struct tm l_tTmBase = {0};
    char l_na8DataBasertxPath[60] = {0};
    char l_na8Flow[40] = {0};
    int32 l_n32msgid = 0;
    time_t l_ttime = {0};
    MsgQuence_t l_tRecvMsg = {0};
    l_ttime = time(0);
    l_ptTm = gmtime(&l_ttime);
    l_tTmBase = *l_ptTm;
    /* 创建一个database文件夹 */
    l_n32Ret = DataBase_CreateDir(DATAVASE_HOME_PATH);
    if (IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_CreateDir is err");
        return;
    }
    /* 创建RTX文件夹 */
    l_n32Ret = DataBase_CreateDir(DATABASE_FOLDER_PATH);
    if (IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_CreateDir is err: l_na8Flow = %s ", l_na8Flow);
        return;
    }
    /* 创建BASE的文件夹 */
    l_n32Ret = DataBase_CreateDir(DATABASE_BASE_PATH);
    if (IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_CreateDir no date is err");
        return;
    }
    /* 获取当前文件名 */
    strftime(l_na8DataBasertxPath, sizeof(l_na8DataBasertxPath), DATABASERTX_PATH, localtime(&l_ttime));
    /* 创建database数据库 */
    l_n32Ret = DataBase_OpenDB(DATABASE_PATH, &g_psqldb);
    if(IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_OpenDB is err:");
        return;
    }
    /* 创建RTX数据库 */
    l_n32Ret = DataBase_OpenDB(l_na8DataBasertxPath, &g_psqldb_rtx);
    if(IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_OpenDB is err:l_na8DataBasertxPath = %s", l_na8DataBasertxPath);
        return;
    }
    /* 创建basebase数据库 */
    l_n32Ret = DataBase_OpenDB(DATABASERLONG_PATH, &g_psqldb_base);
    if(IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_OpenDB is err");
        return;
    }
    /* 创建所有的表 */
    l_n32Ret = DataBase_Create_Tab_All(1);
    if (IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Create_Tab_All is err");
        return;
    }
    /* 创建消息队列 */
    l_tKey_Id = ftok("/mnt", DATABASEINSERT);
    if ( l_tKey_Id < 0 )
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err");
        return;
    }
    l_n32msgid = msgget(l_tKey_Id, IPC_CREAT|0666);
    if (l_n32msgid < 0)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "msgget is err");
        return;
    }
    /* 注册SIGALRM，SIGUSR1信号 */
    signal(SIGALRM, Signal1Hander);
    /* 每5秒插入一次数据 设置定时时间 */
    alarm(5);
    while(1)
    {
        /* 循环检测数据库路径和数据库中表的名字 */
        /* 获取当前时间 */
        l_ttime = time(0);
        l_ptTm = gmtime(&l_ttime);
        /* 和旧的时间作比对 */
        if (l_ptTm->tm_hour != l_tTmBase.tm_hour)
        {
            LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "mod time hour:old time = %d new time = %d", l_tTmBase.tm_hour, l_ptTm->tm_hour);
            l_tTmBase = *l_ptTm;
            /* 存放收发消息表和感知设备表的数据库文件名字每小时更新一次形式为：Databasertx_2020061601.db*/
            /* 获取文件名 */
            strftime(l_na8DataBasertxPath, sizeof(l_na8DataBasertxPath), DATABASERTX_PATH, localtime(&l_ttime));
            /* 关闭数据库 */
            l_n32Ret = DataBase_CloseDB(&g_psqldb_rtx);
            if(IS_OK != l_n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_CloseDB is err");
            }
            l_n32Ret = DataBase_OpenDB(l_na8DataBasertxPath, &g_psqldb_rtx);
            if(0 != l_n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_OpenDB is err:l_na8DataBasertxPath = %s", l_na8DataBasertxPath);
            }
            /* 创建表 */
            /* TRX表 */
            l_n32Ret = DataBase_CreatTab(TAB_TRX_DATATIME_NAME);
            if(IS_OK != l_n32Ret)
            {
                LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "creat rxt tab is err");
            }
            /*SENDING表 */
            l_n32Ret = DataBase_CreatTab(TAB_SENSING_DATATIME_NAME);
            if(IS_OK != l_n32Ret)
            {
                LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "creat sensing tab is err");
            }
        }
        else
        {

        }
        /* 读取消息队列里面的内容 */
        /* 阻塞接受数据 */
        l_n32Ret = msgrcv(l_n32msgid, (void *)&l_tRecvMsg, sizeof(l_tRecvMsg.m_tDatabaseMsg), 0, 0);
        if (l_n32Ret < 0)
        {
            if (EINTR == errno)
            {
                continue;
            }
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "msgrcv is err:l_n32msgid = %d", l_n32msgid);
            perror("recv msg is err");
        }
        else
        {
            switch (l_tRecvMsg.m_tDatabaseMsg.structenumtype)
            {
                case enum_TRXBLOCK_TYPE:
                    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "msg quence recv TRXData msgid = %d", l_n32msgid);
                    g_t_DataBaseRXTDateBuff.m_tTab_Data[g_t_DataBaseRXTDateBuff.m_u32Tab_DataNum].structenumtype = l_tRecvMsg.m_tDatabaseMsg.structenumtype;
                    memcpy(&(g_t_DataBaseRXTDateBuff.m_tTab_Data[g_t_DataBaseRXTDateBuff.m_u32Tab_DataNum].choice.m_tRXData),
                            &(l_tRecvMsg.m_tDatabaseMsg.choice.m_tRXData), sizeof(l_tRecvMsg.m_tDatabaseMsg.choice.m_tRXData));
                    g_t_DataBaseRXTDateBuff.m_u32Tab_DataNum++;
                    break;
                case enum_CER_TYPE:
                    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "msg quence recv CERData msgid = %d", l_n32msgid);
                    g_t_DataBaseCERDateBuff.m_tTab_Data[g_t_DataBaseCERDateBuff.m_u32Tab_DataNum].structenumtype = l_tRecvMsg.m_tDatabaseMsg.structenumtype;
                    memcpy(&(g_t_DataBaseCERDateBuff.m_tTab_Data[g_t_DataBaseCERDateBuff.m_u32Tab_DataNum].choice.m_tCerData),
                            &(l_tRecvMsg.m_tDatabaseMsg.choice.m_tCerData), sizeof(l_tRecvMsg.m_tDatabaseMsg.choice.m_tCerData));
                    g_t_DataBaseCERDateBuff.m_u32Tab_DataNum++;
                    break;
                case enum_ALG_TYPE:
                    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "msg quence recv ALGData msgid = %d", l_n32msgid);
                    g_t_DataBaseALGDateBuff.m_tTab_Data[g_t_DataBaseALGDateBuff.m_u32Tab_DataNum].structenumtype = l_tRecvMsg.m_tDatabaseMsg.structenumtype;
                    memcpy(&(g_t_DataBaseALGDateBuff.m_tTab_Data[g_t_DataBaseALGDateBuff.m_u32Tab_DataNum].choice.m_tAlgData),
                            &(l_tRecvMsg.m_tDatabaseMsg.choice.m_tAlgData), sizeof(l_tRecvMsg.m_tDatabaseMsg.choice.m_tAlgData));
                    g_t_DataBaseALGDateBuff.m_u32Tab_DataNum++;
                    break;
                case enum_DEVSTATE_TYPE:
                    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "msg quence recv DEVSTATEData msgid = %d", l_n32msgid);
                    g_t_DataBaseDEVSTATEDateBuff.m_tTab_Data[g_t_DataBaseDEVSTATEDateBuff.m_u32Tab_DataNum].structenumtype = l_tRecvMsg.m_tDatabaseMsg.structenumtype;
                    memcpy(&(g_t_DataBaseDEVSTATEDateBuff.m_tTab_Data[g_t_DataBaseDEVSTATEDateBuff.m_u32Tab_DataNum].choice.m_tDevstateData),
                            &(l_tRecvMsg.m_tDatabaseMsg.choice.m_tDevstateData), sizeof(l_tRecvMsg.m_tDatabaseMsg.choice.m_tDevstateData));
                    g_t_DataBaseDEVSTATEDateBuff.m_u32Tab_DataNum++;
                    break;
                case enum_DEVFAULT_TYPE:
                    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "msg quence recv DEVFALUTData msgid = %d", l_n32msgid);
                    g_t_DataBaseDEVFALUTDateBuff.m_tTab_Data[g_t_DataBaseDEVFALUTDateBuff.m_u32Tab_DataNum].structenumtype = l_tRecvMsg.m_tDatabaseMsg.structenumtype;
                    memcpy(&(g_t_DataBaseDEVFALUTDateBuff.m_tTab_Data[g_t_DataBaseDEVFALUTDateBuff.m_u32Tab_DataNum].choice.m_tDevFaultData),
                            &(l_tRecvMsg.m_tDatabaseMsg.choice.m_tDevFaultData), sizeof(l_tRecvMsg.m_tDatabaseMsg.choice.m_tDevFaultData));
                    g_t_DataBaseDEVFALUTDateBuff.m_u32Tab_DataNum++;
                    break;
                case enum_SENSINGDEVICESDATA_TYPE:
                    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "msg quence recv SENSINGData msgid = %d", l_n32msgid);
                    g_t_DataBaseSENSINGDateBuff.m_tTab_Data[g_t_DataBaseSENSINGDateBuff.m_u32Tab_DataNum].structenumtype = l_tRecvMsg.m_tDatabaseMsg.structenumtype;
                    memcpy(&(g_t_DataBaseSENSINGDateBuff.m_tTab_Data[g_t_DataBaseSENSINGDateBuff.m_u32Tab_DataNum].choice.m_tSen_DevData),
                            &(l_tRecvMsg.m_tDatabaseMsg.choice.m_tSen_DevData), sizeof(l_tRecvMsg.m_tDatabaseMsg.choice.m_tSen_DevData));
                    g_t_DataBaseSENSINGDateBuff.m_u32Tab_DataNum++;
                    break;
                default:
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "msgrcv is type is no typedfef :typedef = %d", l_tRecvMsg.m_tDatabaseMsg.structenumtype);
            }
        }
        /* 获取数据超过1000条插入一次 */
        if (MAX_INSERT_NUM == g_t_DataBaseRXTDateBuff.m_u32Tab_DataNum)
        {
            g_n32SqliteStateFlag = 1;
            /* 插入收发数据 */
            l_n32Ret = DataBase_Tab_Insert(TAB_TRX_DATATIME_NAME, &g_t_DataBaseRXTDateBuff);
            if (IS_OK != l_n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert rx data is err");
            }
            g_t_DataBaseRXTDateBuff.m_u32Tab_DataNum = 0;
        }
        if (1 <= g_t_DataBaseCERDateBuff.m_u32Tab_DataNum)
        {
            g_n32SqliteStateFlag = 1;
            /* 插入证书数据 */
            l_n32Ret = DataBase_Tab_Insert("CERSheet", &g_t_DataBaseCERDateBuff);
            if (IS_OK != l_n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert cer data is err");
            }
            g_t_DataBaseCERDateBuff.m_u32Tab_DataNum = 0;
        }
        if (1 <= g_t_DataBaseALGDateBuff.m_u32Tab_DataNum)
        {
            g_n32SqliteStateFlag = 1;
            /* 插入算法数据 */
            l_n32Ret = DataBase_Tab_Insert("ALGSheet", &g_t_DataBaseALGDateBuff);
            if (IS_OK != l_n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert alg data is err");
            }
            g_t_DataBaseALGDateBuff.m_u32Tab_DataNum = 0;
        }
        if (MAX_INSERT_NUM == g_t_DataBaseDEVSTATEDateBuff.m_u32Tab_DataNum)
        {
            g_n32SqliteStateFlag = 1;
            /* 插入设备状态数据 */
            l_n32Ret = DataBase_Tab_Insert("DEVSTATESheet", &g_t_DataBaseDEVSTATEDateBuff);
            if (IS_OK != l_n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert devstate data is err");
            }
            g_t_DataBaseDEVSTATEDateBuff.m_u32Tab_DataNum = 0;
        }
        if (MAX_INSERT_NUM == g_t_DataBaseDEVFALUTDateBuff.m_u32Tab_DataNum)
        {
            g_n32SqliteStateFlag = 1;
            /* 插入设备故障数据 */
            l_n32Ret = DataBase_Tab_Insert("DEVFAULTSheet", &g_t_DataBaseDEVFALUTDateBuff);
            if (IS_OK != l_n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert devfault data is err");
            }
            g_t_DataBaseDEVFALUTDateBuff.m_u32Tab_DataNum = 0;
        }
        if (MAX_INSERT_NUM == g_t_DataBaseSENSINGDateBuff.m_u32Tab_DataNum)
        {
            g_n32SqliteStateFlag = 1;
            /* 插入感知设备信息 */
            l_n32Ret = DataBase_Tab_Insert(TAB_SENSING_DATATIME_NAME, &g_t_DataBaseSENSINGDateBuff);
            if (IS_OK != l_n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "insert sensing data is err");
            }
            g_t_DataBaseSENSINGDateBuff.m_u32Tab_DataNum = 0;
        }
        g_n32SqliteStateFlag = 0;
    }
}
/***********************************************************************
 * 函 数 名 称 ： Thread_DataBaseOther_Deal
 * 功 能 描 述 ： 数据库处理线程，处理数据库查询和数据库更新
 * 输 入 参 数 ： 无
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-16 V1.0    黄赛   Create
***********************************************************************/
void Thread_DataBaseOther_Deal(void *arg)
{
    /* 共享内存创建 */
    key_t l_tKey_Id = 0;
    uint32 l_u32Ret = 0;
    int32 shmid = 0;
    RecvShmMsg_t *l_ptRecvShmMsg = NULL;
    sem_t *l_ptSemId = NULL;
    /* 创建信号量进行同步互斥的操作 */
    /* 信号量创建 */
    l_ptSemId = sem_open(DATABASEMODULE, O_CREAT, 0666, 0);
    if (SEM_FAILED == l_ptSemId)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sem_open is err:");
        perror("unable to create semaphore");
    }
    /* 创建共享内存，并往共享内存里面写数据 */
    /* 创建一个键值 */
    l_tKey_Id = ftok("/mnt", DATABASESHM);
    if (l_tKey_Id < 0)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err: l_tKey_Id = %d", l_tKey_Id);
        perror("ftok is err");
        return;
    }
    /* 获取共享内存的ID */
    shmid = shmget(l_tKey_Id, sizeof(RecvShmMsg_t), IPC_CREAT | 0666);
    if (0 > shmid)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        return;
    }
    /* 获取共享内存的地址 */
    l_ptRecvShmMsg = shmat(shmid, NULL, 0);
    if (NULL == l_ptRecvShmMsg)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "l_ptRecvShmMsg IS NULL");
        return;
    }
    memset(l_ptRecvShmMsg, 0, sizeof(RecvShmMsg_t));
    l_ptRecvShmMsg->optflag = 0xAA;
    int32 l_n32Num = 0;
    /* 先将信号量清空 */
    sem_getvalue(l_ptSemId, &l_n32Num);
    while(0 != l_n32Num)
    {
        sem_trywait(l_ptSemId);
        sem_getvalue(l_ptSemId, &l_n32Num);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait clear sem");
    }
    /* 循环判断是否收到数据，如果收到数据就进行数据处理 */
    while(1)
    {
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait other db msg");
        sem_wait(l_ptSemId);
        /* 检测共享内存状态 */
        if (0xCC == l_ptRecvShmMsg->optflag)
        {
            switch (l_ptRecvShmMsg->enumRecvMsgType)
            {
                case enum_Seek:
                    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "recv select db msg");
                    /* 接收数据库查询消息，并将结果发送给要查询数据的模块 */
                    l_u32Ret = DataBase_Tab_Select(l_ptRecvShmMsg->m_na8Tabname, l_ptRecvShmMsg->m_na8FileId,
                                                        &(l_ptRecvShmMsg->m_tFileValue), &(l_ptRecvShmMsg->m_tMsgDataSourceDate));
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Tab_Select is err:TabName = %s FileId = %s",
                                                    l_ptRecvShmMsg->m_na8Tabname,
                                                    l_ptRecvShmMsg->m_na8FileId);
                    }
                    /* 共享内存读取完成 */
                    l_ptRecvShmMsg->m_n32Ret = l_u32Ret;
                    l_ptRecvShmMsg->optflag = 0xAA;
                    break;
                case enum_Update:
                    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "recv update db msg");
                    /* 接收数据库更新消息 */
                    l_u32Ret = DataBase_Tab_Update(l_ptRecvShmMsg->m_na8Tabname, l_ptRecvShmMsg->m_na8FileId,
                                                    &(l_ptRecvShmMsg->m_tFileValue), &(l_ptRecvShmMsg->m_tMsgDataSourceDate.m_tTab_Data[0]));
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Tab_Update is err:TabName = %s FileId = %s",
                                                    l_ptRecvShmMsg->m_na8Tabname,
                                                    l_ptRecvShmMsg->m_na8FileId);
                    }
                    /* 共享内存读取完成 */
                    l_ptRecvShmMsg->m_n32Ret = l_u32Ret;
                    l_ptRecvShmMsg->optflag = 0xAA;
                    break;
                case enum_Del:
                    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "recv del db msg");
                    /* 接收数据库删除表字段消息 */
                    l_u32Ret = DataBase_Tab_Delete(l_ptRecvShmMsg->m_na8Tabname, l_ptRecvShmMsg->m_na8FileId,
                                                    &(l_ptRecvShmMsg->m_tFileValue));
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Tab_Delete is err:TabName = %s FileId = %s",
                                                    l_ptRecvShmMsg->m_na8Tabname,
                                                    l_ptRecvShmMsg->m_na8FileId);
                    }
                    /* 共享内存读取完成 */
                    l_ptRecvShmMsg->m_n32Ret = l_u32Ret;
                    l_ptRecvShmMsg->optflag = 0xAA;
                    break;
                case enum_Clear:
                    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "recv clear db msg");
                    /* 接受数据库清空表消息 */
                    l_u32Ret = DataBase_ClearTab(l_ptRecvShmMsg->m_na8Tabname);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_ClearTab is err:TabName = %s FileId = %s",
                                                    l_ptRecvShmMsg->m_na8Tabname);
                    }
                    /* 共享内存读取完成 */
                    l_ptRecvShmMsg->m_n32Ret = l_u32Ret;
                    l_ptRecvShmMsg->optflag = 0xAA;                    break;
                case enum_Deltab:
                    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "recv del tab msg");
                    /* 接收数据库删除表消息 */
                    l_u32Ret = DataBase_DeleteTab(l_ptRecvShmMsg->m_na8Tabname);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_DeleteTab is err:TabName = %s FileId = %s",
                                                    l_ptRecvShmMsg->m_na8Tabname);
                    }
                    /* 共享内存读取完成 */
                    l_ptRecvShmMsg->m_n32Ret = l_u32Ret;
                    l_ptRecvShmMsg->optflag = 0xAA;
                    break;
                default:
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "this type is no support: type = %d", l_ptRecvShmMsg->enumRecvMsgType);
                    /* 共享内存读取完成 */
                    l_ptRecvShmMsg->m_n32Ret = l_u32Ret;
                    l_ptRecvShmMsg->optflag = 0xAA;
            }
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "l_ptRecvShmMsg->optflag = %d", l_ptRecvShmMsg->optflag);
            l_ptRecvShmMsg->optflag = 0xAA;
        }

    }
    return;
}
/***********************************************************************
* 函 数 名 称 ： Thread_DataBaseDel_Deal
* 功 能 描 述 ： 数据库删除文件删除线程
* 输 入 参 数 ： 无
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-17 V1.0    黄赛   Create
***********************************************************************/
void Thread_DataBaseDel_Deal(void *arg)
{
    struct stat l_tStatBuf = {0};
    struct stat l_tLastStatBuf = {0};
    int32 l_n32Ret = 0;
    DIR *l_ptdp = NULL;
    uint32 l_u32DirTotalSize = 0;
    struct dirent *l_ptDirInfo = NULL;
    char l_an8FileName[300] = {0}; /* 文件名 */
    char l_an8TargetFileName[300] = {0}; /* 要删除的文件名 */
    /* 1、 每5秒进行一次检测当Database_RTX/目录下数据库文件数据超过1G的时候，删除当Database_RTX目录最旧的文件 */
    /* 2、 每5秒进行一次检测当Database_Base/文件夹下Database.db和Database_Base.db两个文件数据分别超过100M时，将清空表 */
    while (1)
    {
        sleep(5);
        /* 首先检测 Database.db文件大小，当文件超过100M时，清空数据库里面的文件 */
        l_n32Ret = stat(DATABASE_PATH, &l_tStatBuf);
        if (IS_OK != l_n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "stat Database.db is err");
            continue;
        }
        else
        {
            if (l_tStatBuf.st_size > 100*1000*1000)
            {
                l_n32Ret = DataBase_ClearTab("ALGSheet");
                if (IS_OK != l_n32Ret)
                {
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_ClearTab ALGSheet is err");
                    continue;
                }
                l_n32Ret = DataBase_ClearTab("CERSheet");
                if (IS_OK != l_n32Ret)
                {
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_ClearTab CERSheet is err");
                    continue;
                }
            }
        }
        /* 检测 Database_Base.db文件大小，当文件超过100M时，清空数据库的文件 */
        l_n32Ret = stat(DATABASERLONG_PATH, &l_tStatBuf);
        if (IS_OK != l_n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "stat Database_Base.db is err");
            continue;
        }
        else
        {
            if (l_tStatBuf.st_size > SIZE100M)
            {
                l_n32Ret = DataBase_ClearTab("DEVSTATESheet");
                if (IS_OK != l_n32Ret)
                {
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_ClearTab DEVSTATESheet is err");
                    continue;
                }
                l_n32Ret = DataBase_ClearTab("DEVFAULTSheet");
                if (IS_OK != l_n32Ret)
                {
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_ClearTab DEVFAULTSheet is err");
                    continue;
                }
            }
        }
        /* 检查文件夹下数据超过1G时，删除最旧的文件 */
        l_ptdp = opendir(DATABASE_FOLDER_PATH);
        if (NULL == l_ptdp)
        {
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "opendir Database_RTX dir is err");
            continue;
        }
        l_u32DirTotalSize = 0;
        l_tLastStatBuf.st_mtime = time((time_t*)NULL);
        while(NULL != (l_ptDirInfo = readdir(l_ptdp)))
        {
            if (0 == strcmp(l_ptDirInfo->d_name, ".") || 0 == strcmp(l_ptDirInfo->d_name, ".."))
            {
                continue;
            }
            if (NULL == l_ptDirInfo->d_name)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "l_ptDirInfo->d_name is null");
                continue;
            }
            sprintf(l_an8FileName, "/mnt/RWD/DataBase/Database_RTX/%s", l_ptDirInfo->d_name);
            l_n32Ret = stat(l_an8FileName, &l_tStatBuf);
            if (IS_OK != l_n32Ret)
            {
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "stat Database_Base.db is err");
                continue;
            }
            else
            {
                l_u32DirTotalSize += l_tStatBuf.st_size;
                if (l_tLastStatBuf.st_mtime > l_tStatBuf.st_mtime)
                {
                    l_tLastStatBuf.st_mtime = l_tStatBuf.st_mtime;
                    strcpy(l_an8TargetFileName, l_an8FileName);
                }
            }
        }
        if (l_u32DirTotalSize >= SIZE1G)
        {
            unlink(l_an8TargetFileName);
        }
        closedir(l_ptdp);
    }
    return;
}
/***********************************************************************
 * 函 数 名 称 ： FD_DataBase_Init
 * 功 能 描 述 ： 数据库初始化函数，创建线程
 * 输 入 参 数 ： 无
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-19 V1.0    黄赛   Create
***********************************************************************/
int32 FD_DataBase_Init(void)
{
    int32 l_n32Ret = 0;
    pthread_t l_tthreadid1 = 0;
    pthread_t l_tthreadid2 = 0;
    pthread_t l_tthreadid3 = 0;
    /* 创建数据插入线程 */
    l_n32Ret = pthread_create(&l_tthreadid1, NULL, (void *)Thread_DataBaseInsert_Deal, NULL);
    if (l_n32Ret != 0)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "create pthread is err");
        return IS_ERR;
    }
    /* 数据库插入线程启动成功 */
    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "start database insert pthread is success");
    /* 创建数据处理线程 */
    l_n32Ret = pthread_create(&l_tthreadid2, NULL, (void *)Thread_DataBaseOther_Deal, NULL);
    if (l_n32Ret != 0)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "create pthread is err");
        return IS_ERR;
    }
    /* 数据库处理线程启动成功 */
    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "start database operation pthread is success");
    /* 创建数据库删除线程 */
    l_n32Ret = pthread_create(&l_tthreadid3, NULL, (void *)Thread_DataBaseDel_Deal, NULL);
    if (l_n32Ret != 0)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "create pthread is err");
        return IS_ERR;
    }
    /* 数据库删除线程启动成功 */
    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "start database delete pthread is success");
    return IS_OK;
}
#if 0
/* 整表查询功能暂时不提供 */
/***********************************************************************
 * 函 数 名 称 ： DataBase_Select_Tab
 * 功 能 描 述 ： 查询整张表的内容
 * 输 入 参 数 ： p_pn8_Tabname    要查询的表
 * 输 出 参 数 ： p_ptMsgDataSourceDate   表的内容
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-24 V1.0    黄赛   Create
***********************************************************************/
static int32 DataBase_Select_Tab(char *p_pn8_Tabname, DataBaseMsgData_t *p_ptMsgDataSourceDate)
{
    /* 入参检查 */
    if (NULL == p_pn8_Tabname)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null:p_pn8_Tabname = %p", p_pn8_Tabname);
        return IS_ERR;
    }
    uint32 l_u32Ret = 0;
    uint32 l_u32i = 0;
    uint32 l_u32j = 0;
    uint32 l_u32index = 0;
    sqlite3* l_ptsqliteDb = NULL;
    int8* l_pn8buff = NULL;
    uint8 l_u8Type = 0;
    char **l_ppResult = NULL;
    int32 l_n32column = 0, l_n32row = 0;
    int8* l_pn8ErrMsg = NULL;
    /* 根据表名匹配类型 */
    l_u32Ret = DataBase_TabNameToDbId(p_pn8_Tabname, &l_ptsqliteDb, &l_u8Type);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_TabNameToDbId is err: p_pn8_Tabname = %s l_u32Ret = %d", p_pn8_Tabname, l_u32Ret);
        return IS_ERR;
    }
    /* 判空检查 */
    if (NULL == l_ptsqliteDb)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is null: l_ptsqliteDb = %p ", l_ptsqliteDb);
        return IS_ERR;
    }
    /* 检查数据库忙状态 */
    l_u32Ret = sqlite3_busy_timeout(l_ptsqliteDb, DB_BUSY_TIMEOUT);
    if (SQLITE_BUSY == l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase is busy: l_ptsqliteDb = %p l_u32Ret =%d ", l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 检查当前表是否存在, 不存在退出 */
    l_u32Ret = DataBase_IsTabExists(p_pn8_Tabname, &l_ptsqliteDb);
    if (IS_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_IsTabExists is err: p_pn8_Tabname = %s l_ptsqliteDb =%p l_u32Ret = %d", p_pn8_Tabname, l_ptsqliteDb, l_u32Ret);
        return IS_ERR;
    }
    /* 分配空间 */
    l_pn8buff = malloc(sizeof(int8) * 5120);
    if (NULL == l_pn8buff)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "malloc is null: l_pn8buff = %p ", l_pn8buff);
        return IS_ERR;
    }
    /* 执行查询数据表命令 */
    sprintf(l_pn8buff, SELECT_DB_TAB_ALL, p_pn8_Tabname);
    /* 使用get_table查询数据库 */
    l_u32Ret = sqlite3_get_table(l_ptsqliteDb, l_pn8buff, &l_ppResult, &l_n32row, &l_n32column, &l_pn8ErrMsg);
    if (SQLITE_OK != l_u32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sqlite3_get_table is err: l_u32Ret = %d p_pn8_Tabname = %s l_pn8ErrMsg = %s", l_u32Ret, p_pn8_Tabname, l_pn8ErrMsg);
        /* 释放缓冲区 */
        sqlite3_free_table(l_ppResult);
        sqlite3_free(l_pn8ErrMsg);
        free(l_pn8buff);
        l_pn8buff = NULL;
        return IS_ERR;
    }
    LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "select data num is = %d", l_n32row);
    if (MAX_INSERT_NUM < l_n32row)
    {
        p_ptMsgDataSourceDate->m_u32Tab_DataNum = MAX_INSERT_NUM;
    }
    else
    {
        p_ptMsgDataSourceDate->m_u32Tab_DataNum = l_n32row;
    }
    /* 前面第一行数据是字段名称，从 n32column 索引开始才是真正的数据 */
    l_u32index = l_n32column;
    for (l_u32i = 0;l_u32i < p_ptMsgDataSourceDate->m_u32Tab_DataNum;l_u32i++ )
    {
        /* ppResult 的字段值是连续的，从第0索引到第 n32column - 1索引都是字段名称 */
        /* 第 n32column 索引开始，后面都是字段值，它把一个二维的表一维形式来表示 */
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "this is %d data", l_u32i + 1);
        for (l_u32j = 0 ;l_u32j < l_n32column;l_u32j++)
        {
            switch (l_u8Type)
            {
                case CER_TYPE:
                    p_ptMsgDataSourceDate->m_tTab_Data[p_ptMsgDataSourceDate->m_u32Tab_DataNum -l_u32i - 1].structenumtype = CER_TYPE;
                    l_u32Ret = DataBase_Select_Cer(&(p_ptMsgDataSourceDate->m_tTab_Data[p_ptMsgDataSourceDate->m_u32Tab_DataNum -l_u32i - 1]), l_ppResult, l_u32j, l_u32index);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Select_Cer is err: l_u32Ret = %d l_u32j = %d l_u32index = %d", l_u32Ret, l_u32j, l_u32index);
                        /* 释放缓冲区 */
                        sqlite3_free_table(l_ppResult);
                        free(l_pn8buff);
                        l_pn8buff = NULL;
                        return IS_ERR;
                    }
                    break;
                case ALG_TYPE:
                    p_ptMsgDataSourceDate->m_tTab_Data[p_ptMsgDataSourceDate->m_u32Tab_DataNum -l_u32i - 1].structenumtype = ALG_TYPE;
                    l_u32Ret = DataBase_Select_Alg(&(p_ptMsgDataSourceDate->m_tTab_Data[p_ptMsgDataSourceDate->m_u32Tab_DataNum -l_u32i - 1]), l_ppResult, l_u32j, l_u32index);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Select_Alg is err: l_u32Ret = %d l_u32j = %d l_u32index = %d", l_u32Ret, l_u32j, l_u32index);
                        /* 释放缓冲区 */
                        sqlite3_free_table(l_ppResult);
                        free(l_pn8buff);
                        l_pn8buff = NULL;
                        return IS_ERR;
                    }
                    break;
                case DEVSTATE_TYPE:
                    p_ptMsgDataSourceDate->m_tTab_Data[p_ptMsgDataSourceDate->m_u32Tab_DataNum -l_u32i - 1].structenumtype = DEVSTATE_TYPE;
                    l_u32Ret = DataBase_Select_DevState(&(p_ptMsgDataSourceDate->m_tTab_Data[p_ptMsgDataSourceDate->m_u32Tab_DataNum -l_u32i - 1]), l_ppResult, l_u32j, l_u32index);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Select_DevState is err: l_u32Ret = %d l_u32j = %d l_u32index = %d", l_u32Ret, l_u32j, l_u32index);
                        /* 释放缓冲区 */
                        sqlite3_free_table(l_ppResult);
                        free(l_pn8buff);
                        l_pn8buff = NULL;
                        return IS_ERR;
                    }
                    break;
                case DEVFAULT_TYPE:
                    p_ptMsgDataSourceDate->m_tTab_Data[p_ptMsgDataSourceDate->m_u32Tab_DataNum -l_u32i - 1].structenumtype = DEVFAULT_TYPE;
                    l_u32Ret = DataBase_Select_DevFault(&(p_ptMsgDataSourceDate->m_tTab_Data[p_ptMsgDataSourceDate->m_u32Tab_DataNum -l_u32i - 1]), l_ppResult, l_u32j, l_u32index);
                    if (IS_OK != l_u32Ret)
                    {
                        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "DataBase_Select_DevFault is err: l_u32Ret = %d l_u32j = %d l_u32index = %d", l_u32Ret, l_u32j, l_u32index);
                        /* 释放缓冲区 */
                        sqlite3_free_table(l_ppResult);
                        free(l_pn8buff);
                        l_pn8buff = NULL;
                        return IS_ERR;
                    }
                    break;
                default:
                    LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "this type is absent: l_u8Type = %d", l_u8Type);
                    /* 释放缓冲区 */
                    sqlite3_free_table(l_ppResult);
                    free(l_pn8buff);
                    l_pn8buff = NULL;
                    return IS_ERR;
            }
            ++l_u32index;
        }
    }
    sqlite3_free_table(l_ppResult);
    /* 释放缓冲区 */
    free(l_pn8buff);
    l_pn8buff = NULL;
    return IS_OK;
}
#endif
/***********************************************************************
 * 函 数 名 称 ： FD_DataBase_SendToDb
 * 功 能 描 述 ： 向消息队列里面添加消息
 * 输 入 参 数 ： p_ptMsgQence    要发送的消息
 * 输 出 参 数 ： 无
 * 返  回  值  : IS_OK/IS_ERR              成功/失败
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-04-24 V1.0    黄赛   Create
***********************************************************************/
int32 FD_DataBase_SendToDb(MsgQuence_t *p_ptMsgQence)
{
    /* 入参检查 */
    if (NULL == p_ptMsgQence)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null:p_ptMsgQence = %p", p_ptMsgQence);
        return IS_ERR;
    }
    int32 l_n32Ret = 0;
    int32 l_n32MsqId = 0;
    key_t l_tKey_Id = 0;
    /* 创建消息队列，并往消息队列里面写数据 */
    l_tKey_Id = ftok("/mnt", DATABASEINSERT);
    if ( l_tKey_Id < 0 )
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        perror("ftok is err");
        return IS_ERR;
    }
    l_n32MsqId = msgget(l_tKey_Id, IPC_CREAT|0666);
    if (l_n32MsqId < 0)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "get message id is err: l_n32Ret = %d l_tKey_Id = %d", l_n32Ret, l_tKey_Id);
        return IS_ERR;
    }
    p_ptMsgQence->m_u64MessageType = 1;
    /* 往消息队列里面写数据 */
    l_n32Ret = msgsnd(l_n32MsqId, p_ptMsgQence, sizeof(p_ptMsgQence->m_tDatabaseMsg), 0);
    if (l_n32Ret < 0)
    {
        if (EINTR == errno)
        {
            l_n32Ret = msgsnd(l_n32MsqId, p_ptMsgQence, sizeof(p_ptMsgQence->m_tDatabaseMsg), 0);
            if (l_n32Ret < 0)
            {
                msgctl(l_n32MsqId, IPC_RMID, p_ptMsgQence);
                LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "msgsnd is err: l_n32Ret = %d len = %d l_n32MsqId = %d error = %d", l_n32Ret, sizeof(p_ptMsgQence->m_tDatabaseMsg), l_n32MsqId, errno);
                perror("send msg is err");
                return IS_ERR;
            }
        }
        else
        {
            msgctl(l_n32MsqId, IPC_RMID, p_ptMsgQence);
            LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "msgsnd is err: l_n32Ret = %d len = %d l_n32MsqId = %d error = %d", l_n32Ret, sizeof(p_ptMsgQence->m_tDatabaseMsg), l_n32MsqId, errno);
            perror("send msg is err");
            return IS_ERR;
        }
    }
    return IS_OK;
}
/***********************************************************************
* 函 数 名 称 ： FD_DataBase_Tab_Select
* 功 能 描 述 ： 查找数据库里面的数据
* 输 入 参 数 ： p_pn8_Tabname p_pn8_FileId p_ptFileValue p_ptMsgDataSourceDate
                 表名 字段名 字段值 查出来的信息
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-03 V1.0    黄赛    Create
***********************************************************************/
uint32 FD_DataBase_Tab_Select(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue, DataBaseMsgData_t *p_ptMsgDataSourceDate)
{
    /* 入参检查 */
    if ((NULL == p_pn8_Tabname) || (NULL == p_pn8_FileId)
            || (NULL == p_ptFileValue) || (NULL == p_ptMsgDataSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p p_pn8_FileId = %p p_ptFileValue = %p", p_pn8_Tabname, p_pn8_FileId, p_ptFileValue);
        return IS_ERR;
    }
    sem_t *l_ptSemId = NULL;
    /* 创建信号量进行同步互斥的操作 */
    /* 信号量创建 */
    l_ptSemId = sem_open(DATABASEMODULE, O_CREAT, 0666, 0);
    if (SEM_FAILED == l_ptSemId)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sem_open is err:");
        perror("unable to create semaphore");
    }
    int32 l_n32Ret = 0;
    int32 l_n32RetStatus = 0;
    RecvShmMsg_t *l_ptRecvShmMsg = NULL;
    key_t l_tKey_Id = 0;
    int32 shmid = 0;
    /* 创建共享内存，并往共享内存里面写数据 */
    /* 创建一个键值 */
    l_tKey_Id = ftok("/mnt", DATABASESHM);
    if (l_tKey_Id < 0)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        perror("ftok is err");
        return IS_ERR;
    }
    /* 获取共享内存的ID */
    shmid = shmget(l_tKey_Id, sizeof(RecvShmMsg_t), IPC_CREAT | 0666);
    if (0 > shmid)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        return IS_ERR;
    }
    /* 获取共享内存的地址 */
    l_ptRecvShmMsg = shmat(shmid, NULL, 0);
    if (NULL == l_ptRecvShmMsg)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "l_ptRecvShmMsg IS NULL");
        return IS_ERR;
    }
    while (0xAA != l_ptRecvShmMsg->optflag)
    {
        usleep(1);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait status option done :l_ptRecvShmMsg->optflag = %d", l_ptRecvShmMsg->optflag);
    }
    l_ptRecvShmMsg->optflag = 0xBB;
    /* 将入参传给共享内存 */
    l_ptRecvShmMsg->enumRecvMsgType = enum_Seek;
    /* 填写发送消息的入参 */
    strcpy(l_ptRecvShmMsg->m_na8Tabname, p_pn8_Tabname);
    strcpy(l_ptRecvShmMsg->m_na8FileId, p_pn8_FileId);
    l_ptRecvShmMsg->m_tFileValue.enumTypeFlag = p_ptFileValue->enumTypeFlag;
    if (enum_string == l_ptRecvShmMsg->m_tFileValue.enumTypeFlag)
    {
        strcpy(l_ptRecvShmMsg->m_tFileValue.choic.m_na8FileValue, p_ptFileValue->choic.m_na8FileValue);
    }
    else if (enum_int == l_ptRecvShmMsg->m_tFileValue.enumTypeFlag)
    {
        l_ptRecvShmMsg->m_tFileValue.choic.m_u64FileValue = p_ptFileValue->choic.m_u64FileValue;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "send typeflag is err");
        return IS_ERR;
    }
    l_ptRecvShmMsg->optflag = 0xCC;
    int32 l_n32Num = 0;
    /* 先将信号量清空 */
    sem_getvalue(l_ptSemId, &l_n32Num);
    while(0 != l_n32Num)
    {
        sem_trywait(l_ptSemId);
        sem_getvalue(l_ptSemId, &l_n32Num);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait clear sem");
    }
    sem_post(l_ptSemId);
    /* 获取执行结果 */
    while (0xAA != l_ptRecvShmMsg->optflag)
    {
        usleep(1);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait status option done :l_ptRecvShmMsg->optflag = %d", l_ptRecvShmMsg->optflag);
    }
    if (IS_OK == l_ptRecvShmMsg->m_n32Ret)
    {
        memcpy(p_ptMsgDataSourceDate, &(l_ptRecvShmMsg->m_tMsgDataSourceDate), sizeof(DataBaseMsgData_t));
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "select db is err");
    }
    l_n32Ret = l_ptRecvShmMsg->m_n32Ret;
    l_n32RetStatus = shmdt(l_ptRecvShmMsg);
    if (IS_OK != l_n32RetStatus)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "select db shmdt is err");
        perror("shmdt is err");
        return IS_ERR;
    }
    return l_n32Ret;
}
/***********************************************************************
* 函 数 名 称 ： FD_DataBase_Tab_Update
* 功 能 描 述 ： 更新表里面的数据
* 输 入 参 数 ： p_pn8_Tabname p_pn8_FileId p_ptFileValue p_ptSqlSourceDate
                 表名 字段名 字段值 要更新的值
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-03 V1.0    黄赛    Create
***********************************************************************/
uint32 FD_DataBase_Tab_Update(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue, SQL_STRUCTURE_t *p_ptSqlSourceDate)
{
    /* 入参检查 */
    if ((NULL == p_pn8_Tabname) || (NULL == p_pn8_FileId)
            || (NULL == p_ptFileValue) || (NULL == p_ptSqlSourceDate))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p p_pn8_FileId = %p p_ptFileValue = %p", p_pn8_Tabname, p_pn8_FileId, p_ptFileValue);
        return IS_ERR;
    }
    int32 l_n32Ret = 0;
    int32 l_n32RetStatus = 0;
    sem_t *l_ptSemId = NULL;
    /* 创建信号量进行同步互斥的操作 */
    /* 信号量创建 */
    l_ptSemId = sem_open(DATABASEMODULE, O_CREAT, 0666, 0);
    if (SEM_FAILED == l_ptSemId)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sem_open is err:");
        perror("unable to create semaphore");
    }
    RecvShmMsg_t *l_ptRecvShmMsg = NULL;
    key_t l_tKey_Id = 0;
    int32 shmid = 0;
    /* 创建共享内存，并往共享内存里面写数据 */
    /* 创建一个键值 */
    l_tKey_Id = ftok("/mnt", DATABASESHM);
    if (l_tKey_Id < 0)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        perror("ftok is err");
        return IS_ERR;
    }
    /* 获取共享内存的ID */
    shmid = shmget(l_tKey_Id, sizeof(RecvShmMsg_t), IPC_CREAT | 0666);
    if (0 > shmid)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        return IS_ERR;
    }
    /* 获取共享内存的地址 */
    l_ptRecvShmMsg = shmat(shmid, NULL, 0);
    if (NULL == l_ptRecvShmMsg)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "l_ptRecvShmMsg IS NULL");
        return IS_ERR;
    }
    while (0xAA != l_ptRecvShmMsg->optflag)
    {
        usleep(1);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait status option done :l_ptRecvShmMsg->optflag = %d", l_ptRecvShmMsg->optflag);
    }
    l_ptRecvShmMsg->optflag = 0xBB;
    /* 将入参传给共享内存 */
    l_ptRecvShmMsg->enumRecvMsgType = enum_Update;
    /* 填写发送消息的入参 */
    strcpy(l_ptRecvShmMsg->m_na8Tabname, p_pn8_Tabname);
    strcpy(l_ptRecvShmMsg->m_na8FileId, p_pn8_FileId);
    l_ptRecvShmMsg->m_tFileValue.enumTypeFlag = p_ptFileValue->enumTypeFlag;
    if (enum_string == l_ptRecvShmMsg->m_tFileValue.enumTypeFlag)
    {
        strcpy(l_ptRecvShmMsg->m_tFileValue.choic.m_na8FileValue, p_ptFileValue->choic.m_na8FileValue);
    }
    else if (enum_int == l_ptRecvShmMsg->m_tFileValue.enumTypeFlag)
    {
        l_ptRecvShmMsg->m_tFileValue.choic.m_u64FileValue = p_ptFileValue->choic.m_u64FileValue;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "send typeflag is err");
        return IS_ERR;
    }
    memcpy(&(l_ptRecvShmMsg->m_tMsgDataSourceDate.m_tTab_Data[0]), p_ptSqlSourceDate, sizeof(SQL_STRUCTURE_t));
    l_ptRecvShmMsg->optflag = 0xCC;
    int32 l_n32Num = 0;
    /* 先将信号量清空 */
    sem_getvalue(l_ptSemId, &l_n32Num);
    while(0 != l_n32Num)
    {
        sem_trywait(l_ptSemId);
        sem_getvalue(l_ptSemId, &l_n32Num);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait clear sem");
    }
    sem_post(l_ptSemId);
    /* 获取执行结果 */
    while (0xAA != l_ptRecvShmMsg->optflag)
    {
        usleep(1);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait status option done :l_ptRecvShmMsg->optflag = %d", l_ptRecvShmMsg->optflag);
    }
    l_n32Ret = l_ptRecvShmMsg->m_n32Ret;
    l_n32RetStatus = shmdt(l_ptRecvShmMsg);
    if (IS_OK != l_n32RetStatus)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "select db shmdt is err");
        perror("shmdt is err");
        return IS_ERR;
    }
    return l_n32Ret;
}
/***********************************************************************
* 函 数 名 称 ： FD_DataBase_Tab_Delete
* 功 能 描 述 ： 删除表里面的数据
* 输 入 参 数 ： p_pn8_Tabname p_pn8_FileId p_ptFileValue / 表名 字段名 字段值
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-03 V1.0    黄赛    Create
***********************************************************************/
uint32 FD_DataBase_Tab_Delete(char *p_pn8_Tabname, char* p_pn8_FileId, FileIdValue_t *p_ptFileValue)
{
    /* 入参检查 */
    if ((NULL == p_pn8_Tabname) || (NULL == p_pn8_FileId)
            || (NULL == p_ptFileValue))
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p p_pn8_FileId = %p p_ptFileValue = %p", p_pn8_Tabname, p_pn8_FileId, p_ptFileValue);
        return IS_ERR;
    }
    sem_t *l_ptSemId = NULL;
    int32 l_n32Ret = 0;
    int32 l_n32RetStatus = 0;
    /* 创建信号量进行同步互斥的操作 */
    /* 信号量创建 */
    l_ptSemId = sem_open(DATABASEMODULE, O_CREAT, 0666, 0);
    if (SEM_FAILED == l_ptSemId)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sem_open is err:");
        perror("unable to create semaphore");
    }
    RecvShmMsg_t *l_ptRecvShmMsg = NULL;
    key_t l_tKey_Id = 0;
    int32 shmid = 0;
    /* 创建共享内存，并往共享内存里面写数据 */
    /* 创建一个键值 */
    l_tKey_Id = ftok("/mnt", DATABASESHM);
    if (l_tKey_Id < 0)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        perror("ftok is err");
        return IS_ERR;
    }
    /* 获取共享内存的ID */
    shmid = shmget(l_tKey_Id, sizeof(RecvShmMsg_t), IPC_CREAT | 0666);
    if (0 > shmid)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        return IS_ERR;
    }
    /* 获取共享内存的地址 */
    l_ptRecvShmMsg = shmat(shmid, NULL, 0);
    if (NULL == l_ptRecvShmMsg)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "l_ptRecvShmMsg IS NULL");
        return IS_ERR;
    }
    while (0xAA != l_ptRecvShmMsg->optflag)
    {
        usleep(1);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait status option done :l_ptRecvShmMsg->optflag = %d", l_ptRecvShmMsg->optflag);
    }
    l_ptRecvShmMsg->optflag = 0xBB;
    /* 将入参传给共享内存 */
    l_ptRecvShmMsg->enumRecvMsgType = enum_Del;
    strcpy(l_ptRecvShmMsg->m_na8Tabname, p_pn8_Tabname);
    strcpy(l_ptRecvShmMsg->m_na8FileId, p_pn8_FileId);
    l_ptRecvShmMsg->m_tFileValue.enumTypeFlag = p_ptFileValue->enumTypeFlag;
    if (enum_string == l_ptRecvShmMsg->m_tFileValue.enumTypeFlag)
    {
        strcpy(l_ptRecvShmMsg->m_tFileValue.choic.m_na8FileValue, p_ptFileValue->choic.m_na8FileValue);
    }
    else if (enum_int == l_ptRecvShmMsg->m_tFileValue.enumTypeFlag)
    {
        l_ptRecvShmMsg->m_tFileValue.choic.m_u64FileValue = p_ptFileValue->choic.m_u64FileValue;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "send typeflag is err");
        return IS_ERR;
    }
    l_ptRecvShmMsg->optflag = 0xCC;
    int32 l_n32Num = 0;
    /* 先将信号量清空 */
    sem_getvalue(l_ptSemId, &l_n32Num);
    while(0 != l_n32Num)
    {
        sem_trywait(l_ptSemId);
        sem_getvalue(l_ptSemId, &l_n32Num);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait clear sem");
    }
    sem_post(l_ptSemId);
    /* 获取执行结果 */
    while (0xAA != l_ptRecvShmMsg->optflag)
    {
        usleep(1);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait status option done :l_ptRecvShmMsg->optflag = %d", l_ptRecvShmMsg->optflag);
    }
    l_n32Ret = l_ptRecvShmMsg->m_n32Ret;
    l_n32RetStatus = shmdt(l_ptRecvShmMsg);
    if (IS_OK != l_n32RetStatus)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "select db shmdt is err");
        perror("shmdt is err");
        return IS_ERR;
    }
    return l_n32Ret;
}
/***********************************************************************
* 函 数 名 称 ： FD_DataBase_ClearTab
* 功 能 描 述 ： 清空数据库中指定的表
* 输 入 参 数 ： p_pn8_Tabname / 表名
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-03 V1.0    黄赛    Create
***********************************************************************/
uint32 FD_DataBase_ClearTab(char *p_pn8_Tabname)
{
    /* 入参检查 */
    if (NULL == p_pn8_Tabname)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p", p_pn8_Tabname);
        return IS_ERR;
    }
    int32 l_n32Ret = 0;
    int32 l_n32RetStatus = 0;
    sem_t *l_ptSemId = NULL;
    /* 创建信号量进行同步互斥的操作 */
    /* 信号量创建 */
    l_ptSemId = sem_open(DATABASEMODULE, O_CREAT, 0666, 0);
    if (SEM_FAILED == l_ptSemId)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sem_open is err:");
        perror("unable to create semaphore");
    }
    RecvShmMsg_t *l_ptRecvShmMsg = NULL;
    key_t l_tKey_Id = 0;
    int32 shmid = 0;
    /* 创建共享内存，并往共享内存里面写数据 */
    /* 创建一个键值 */
    l_tKey_Id = ftok("/mnt", DATABASESHM);
    if (l_tKey_Id < 0)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        perror("ftok is err");
        return IS_ERR;
    }
    /* 获取共享内存的ID */
    shmid = shmget(l_tKey_Id, sizeof(RecvShmMsg_t), IPC_CREAT | 0666);
    if (0 > shmid)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        return IS_ERR;
    }
    /* 获取共享内存的地址 */
    l_ptRecvShmMsg = shmat(shmid, NULL, 0);
    if (NULL == l_ptRecvShmMsg)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "l_ptRecvShmMsg IS NULL");
        return IS_ERR;
    }
    while (0xAA != l_ptRecvShmMsg->optflag)
    {
        usleep(1);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait status option done :l_ptRecvShmMsg->optflag = %d", l_ptRecvShmMsg->optflag);
    }
    l_ptRecvShmMsg->optflag = 0xBB;
    /* 将入参传给共享内存 */
    l_ptRecvShmMsg->enumRecvMsgType = enum_Clear;
    strcpy(l_ptRecvShmMsg->m_na8Tabname, p_pn8_Tabname);
    l_ptRecvShmMsg->optflag = 0xCC;
    int32 l_n32Num = 0;
    /* 先将信号量清空 */
    sem_getvalue(l_ptSemId, &l_n32Num);
    while(0 != l_n32Num)
    {
        sem_trywait(l_ptSemId);
        sem_getvalue(l_ptSemId, &l_n32Num);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait clear sem");
    }
    sem_post(l_ptSemId);
    /* 获取执行结果 */
    while (0xAA != l_ptRecvShmMsg->optflag)
    {
        usleep(1);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait status option done :l_ptRecvShmMsg->optflag = %d", l_ptRecvShmMsg->optflag);
    }
    l_n32Ret = l_ptRecvShmMsg->m_n32Ret;
    l_n32RetStatus = shmdt(l_ptRecvShmMsg);
    if (IS_OK != l_n32RetStatus)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "select db shmdt is err");
        perror("shmdt is err");
        return IS_ERR;
    }
    return l_n32Ret;
}
/***********************************************************************
* 函 数 名 称 ： FD_DataBase_DeleteTab
* 功 能 描 述 ： 删除数据库中指定的表
* 输 入 参 数 ： p_pn8_Tabname / 表名
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-03 V1.0    黄赛    Create
***********************************************************************/
uint32 FD_DataBase_DeleteTab(char *p_pn8_Tabname)
{
    /* 入参检查 */
    if (NULL == p_pn8_Tabname)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "input is null: p_pn8_Tabname = %p", p_pn8_Tabname);
        return IS_ERR;
    }
    sem_t *l_ptSemId = NULL;
    int32 l_n32Ret = 0;
    int32 l_n32RetStatus = 0;
    /* 创建信号量进行同步互斥的操作 */
    /* 信号量创建 */
    l_ptSemId = sem_open(DATABASEMODULE, O_CREAT, 0666, 0);
    if (SEM_FAILED == l_ptSemId)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "sem_open is err:");
        perror("unable to create semaphore");
    }
    RecvShmMsg_t *l_ptRecvShmMsg = NULL;
    key_t l_tKey_Id = 0;
    int32 shmid = 0;
    /* 创建共享内存，并往共享内存里面写数据 */
    /* 创建一个键值 */
    l_tKey_Id = ftok("/mnt", DATABASESHM);
    if (l_tKey_Id < 0)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        perror("ftok is err");
        return IS_ERR;
    }
    /* 获取共享内存的ID */
    shmid = shmget(l_tKey_Id, sizeof(RecvShmMsg_t), IPC_CREAT | 0666);
    if (0 > shmid)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "ftok is err is err: l_tKey_Id = %d", l_tKey_Id);
        return IS_ERR;
    }
    /* 获取共享内存的地址 */
    l_ptRecvShmMsg = shmat(shmid, NULL, 0);
    if (NULL == l_ptRecvShmMsg)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "l_ptRecvShmMsg IS NULL");
        return IS_ERR;
    }
    while (0xAA != l_ptRecvShmMsg->optflag)
    {
        usleep(1);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait status option done :l_ptRecvShmMsg->optflag = %d", l_ptRecvShmMsg->optflag);
    }
    l_ptRecvShmMsg->optflag = 0xBB;
    /* 将入参传给共享内存 */
    l_ptRecvShmMsg->enumRecvMsgType = enum_Deltab;
    strcpy(l_ptRecvShmMsg->m_na8Tabname, p_pn8_Tabname);
    l_ptRecvShmMsg->optflag = 0xCC;
    int32 l_n32Num = 0;
    /* 先将信号量清空 */
    sem_getvalue(l_ptSemId, &l_n32Num);
    while(0 != l_n32Num)
    {
        sem_trywait(l_ptSemId);
        sem_getvalue(l_ptSemId, &l_n32Num);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait clear sem");
    }
    sem_post(l_ptSemId);
    /* 获取执行结果 */
    while (0xAA != l_ptRecvShmMsg->optflag)
    {
        usleep(1);
        LogPrint(LOG_LEVEL_DEBUG, DATABASEMODULE, "wait status option done :l_ptRecvShmMsg->optflag = %d", l_ptRecvShmMsg->optflag);
    }
    l_n32Ret = l_ptRecvShmMsg->m_n32Ret;
    l_n32RetStatus = shmdt(l_ptRecvShmMsg);
    if (IS_OK != l_n32RetStatus)
    {
        LogPrint(LOG_LEVEL_ERR, DATABASEMODULE, "select db shmdt is err");
        perror("shmdt is err");
        return IS_ERR;
    }
    return l_n32Ret;
}
/***************************  文件结束  ********************************/
