/***********************************************************************
 * 文 件 名 称 ： ClockTime_If.h
 * 功 能 描 述 ： 精准定时向外部提供的头文件
 * 开 发 人 员 ： 黄赛
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-05-04 V1.0    黄赛   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
#ifndef __CLOCKTIME_IF_H__
#define __CLOCKTIME_IF_H__
/********************  头文件包含  ********************************/
#include <semaphore.h>
/********************** 宏定义 *************************************/
#define UNREGISTERFLAG 0
/********************** 类型重定义 **********************************/
/********************** 函数外部申明 ********************************/
/**
 * @brief 使用定时模块就需要调用定时模块初始化函数
 * @return  定时模块中，定时模块初始化函数，0表示成功，其他表示失败.
 */
extern int FT_ClockTimeInit(void);
/**
 * @brief 定时模块注册和取消注册函数    
 * @param[in] p_pn8RegisterName   注册名.
 * @param[in] p_n32Len   注册名的长度
 * @param[in] p_n32ClockTime   注册定时时间 （填写UNREGISTERFLAG时为取消注册）
 * @return  0表示成功，其他表示失败.
 */
extern int FT_ClockTimeRegister(char* p_pn8RegisterName, int p_n32RegisterLen, int p_n32RegisterClockTime, sem_t ** p_pptSemId);
#endif /* __CLOCKTIME_IF_H__ */
