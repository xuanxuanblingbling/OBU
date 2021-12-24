/***********************************************************************
* 文 件 名 称 ： HardwareCheck.c
* 功 能 描 述 ： 硬件检查并处理函数
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-09 V1.0    黄赛   Create
*
* @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
/************************  包含的头文件  ********************************/
#include "HardwareCheck.h"
#include <stdlib.h>
#include "wj_log.h"
#include "MiscIf.h"
/***************************  函数定义  ********************************/
static int FCheck_AG15Result(const char *p_pn8para);
static int FCheck_EC20Result(const char *p_pn8para);
static int FCheck_WIFIResult(const char *p_pn8para);
static int FCheck_NETResult(const char *p_pn8para);
static int FCheck_SEC_CHIP(const char *p_pn8para);
/***********************************************************************
* 函 数 名 称 ： FCheck_AG15Result
* 功 能 描 述 ： AG15设备自检检查结果获取
* 输 入 参 数 ： p_pn8para    设备检查命令
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-09 V1.0   黄赛    Create
***********************************************************************/
static int FCheck_AG15Result(const char *p_pn8para)
{
    /* 入参检查 */
    if (NULL == p_pn8para)
    {
            LogPrint(LOG_LEVEL_ERR, "HardwareCheck", "FCheck_AG15Result IS ERR : %p", p_pn8para);
            return IS_ERR;
    }
    int l_n32Ret = 0;
    l_n32Ret = system(p_pn8para);
    if (IS_OK != l_n32Ret)
    {
        return IS_ERR;
    }
    else
    {
        return IS_OK;
    }
}
/***********************************************************************
* 函 数 名 称 ： FCheck_EC20Result
* 功 能 描 述 ： EC20设备自检检查结果获取
* 输 入 参 数 ： p_pn8para    设备检查命令
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-09 V1.0   黄赛    Create
***********************************************************************/
static int FCheck_EC20Result(const char *p_pn8para)
{
    /* 入参检查 */
    if (NULL == p_pn8para)
    {
            LogPrint(LOG_LEVEL_ERR, "HardwareCheck", "FCheck_EC20Result IS ERR : %p", p_pn8para);
            return IS_ERR;
    }
    int l_n32Ret = 0;
    l_n32Ret = system(p_pn8para);
    if (IS_OK != l_n32Ret)
    {
        return IS_ERR;
    }
    else
    {
        return IS_OK;
    }
}
/***********************************************************************
* 函 数 名 称 ： FCheck_WIFIResult
* 功 能 描 述 ： WIFI设备自检检查结果获取
* 输 入 参 数 ： p_pn8para    设备检查命令
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-09 V1.0   黄赛    Create
***********************************************************************/
static int FCheck_WIFIResult(const char *p_pn8para)
{
    /* 入参检查 */
    if (NULL == p_pn8para)
    {
            LogPrint(LOG_LEVEL_ERR, "HardwareCheck", "FCheck_WIFIResult IS ERR : %p", p_pn8para);
            return IS_ERR;
    }
    int l_n32Ret = 0;
    l_n32Ret = system(p_pn8para);
    if (IS_OK != l_n32Ret)
    {
        return IS_ERR;
    }
    else
    {
        return IS_OK;
    }
}
/***********************************************************************
* 函 数 名 称 ： FCheck_NETResult
* 功 能 描 述 ： NET设备自检检查结果获取
* 输 入 参 数 ： p_pn8para    设备检查命令
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-09 V1.0   黄赛    Create
***********************************************************************/
static int FCheck_NETResult(const char *p_pn8para)
{
    /* 入参检查 */
    if (NULL == p_pn8para)
    {
            LogPrint(LOG_LEVEL_ERR, "HardwareCheck", "FCheck_NETResult IS ERR : %p", p_pn8para);
            return IS_ERR;
    }
    int l_n32Ret = 0;
    l_n32Ret = system(p_pn8para);
    if (IS_OK != l_n32Ret)
    {
        return IS_ERR;
    }
    else
    {
        return IS_OK;
    }
}
/***********************************************************************
* 函 数 名 称 ： FCheck_SEC_CHIP
* 功 能 描 述 ： 安全证书模块设备自检检查结果获取
* 输 入 参 数 ： p_pn8para    设备检查命令
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-09 V1.0   黄赛    Create
***********************************************************************/
static int FCheck_SEC_CHIP(const char *p_pn8para)
{
    /* 入参检查 */
    if (NULL == p_pn8para)
    {
            LogPrint(LOG_LEVEL_ERR, "HardwareCheck", "FCheck_SEC_CHIP IS ERR : %p", p_pn8para);
            return IS_ERR;
    }
    int l_n32Ret = 0;
    l_n32Ret = system(p_pn8para);
    if (IS_OK != l_n32Ret)
    {
        return IS_ERR;
    }
    else
    {
        return IS_OK;
    }
}
/***********************************************************************
* 函 数 名 称 ： FS_HardwareCheckInit
* 功 能 描 述 ： 硬件自检初始化，失败返回错误，检查硬件运行状态
* 输 入 参 数 ： 无
* 输 出 参 数 ： 初始化成功和初始化失败
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-09 V1.0    黄赛   Create
***********************************************************************/
int FS_HardwareCheckInit(void)
{
    unsigned int l_u32i = 0;
    int l_n32Ret = 0;
    static moduleInfo_t l_tModuleInfo[] = {
        {"AG15",            "lsusb | grep 0415",            FCheck_AG15Result},
        {"EC20",            "lsusb | grep 0125",            FCheck_EC20Result},
        {"WIFI",            "ifconfig | grep wlan0",        FCheck_WIFIResult},
        {"NET",             "ifconfig | grep eth0",         FCheck_NETResult},
        //{"SEC-CHIP",        NULL,                           FCheck_SEC_CHIP}
    };
    for (l_u32i = 0; l_u32i < sizeof(l_tModuleInfo)/sizeof(moduleInfo_t); l_u32i++)
    {
        if (IS_OK != l_tModuleInfo[l_u32i].m_pCheckFun(l_tModuleInfo[l_u32i].m_pCmd))
        {
            LogPrint(LOG_LEVEL_ERR, "HardwareCheck", "Can't find dev : %s", l_tModuleInfo[l_u32i].m_pModuleName);
        }
    }
    if (IS_OK != l_n32Ret)
    {
        LogPrint(LOG_LEVEL_ERR, "HardwareCheck", "HardwareCheck is err");
    }
    LogPrint(LOG_LEVEL_DEBUG, "HardwareCheck", "HardwareCheck is ok");
    return IS_OK;
}
/***************************  文件结束  ********************************/
