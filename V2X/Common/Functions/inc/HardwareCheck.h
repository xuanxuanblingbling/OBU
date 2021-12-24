/***********************************************************************
* 文 件 名 称 ： HardwareCheck.h
* 功 能 描 述 ： 硬件自检处理头文件
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-09 V1.0    黄赛   Create
*
* @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
#ifndef __HARDWARECHECK_H__
#define __HARDWARECHECK_H__
/**********************  头文件包含  ********************************/
/********************** 宏定义 *************************************/
/********************** 类型重定义 **********************************/
typedef struct _moduleInfo{
    char *m_pModuleName;    /*模块名称*/
    char *m_pCmd;            /*模块检测命令*/
    int (*m_pCheckFun)(const char *p_pn8para);          /*模块检测函数*/
}moduleInfo_t;
/********************** 函数外部申明 ********************************/
extern int FS_HardwareCheckInit(void);
#endif /* __HARDWARECHECK_H__ */