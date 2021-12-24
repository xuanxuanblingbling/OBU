/*
 * @Descripttion: 
 * @version: 
 * @Author: wanji.net.cn
 * @email: mk_wanji@126.com
 * @Date: 2021-11-15 14:50:16
 * @LastEditors: VanJee Technology Co.,Ltd
 * @LastEditTime: 2021-11-26 10:22:52
 */
/***********************************************************************
* 文 件 名 称 ： Gpio.h
* 功 能 描 述 ： 操作GPIO接口控制设备
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-09 V1.0    黄赛   Create
*
* @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__
/**********************  头文件包含  ********************************/
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "MiscIf.h"
#include "wj_log.h"
/********************** 宏定义 *************************************/
#define BEE_INPUT "113"  /* 蜂鸣器控制端口 */
#define V2X_LED1 "114"   /* V2X状态灯控制端口1 */
#define V2X_LED2 "115"   /* V2X状态灯控制端口2 */
#define SYS_LED1 "79"    /* 系统状态灯控制端口1 */
#define SYS_LED2 "78"    /* 系统状态灯控制端口2 */
#define UPD_LED1 "77"    /* 升级状态灯控制端口1 */
#define UPD_LED2 "76"    /* 升级状态灯控制端口2 */
#define GNSS_LED1 "74"   /* GNSS状态灯控制端口1 */
#define GNSS_LED2 "73"   /* GNSS状态灯控制端口2 */
#define DIRECT_OUT "out" /* 控制引脚电平方向 */
#define BMP_MODE "3"     /* 气压传感器模式 */
#define OPTIONNUM 18     /* 操作引脚个数 */
#define BEE_SLEEP 50     /* 蜂鸣器延500us */
#define BEE_COUNT 1000   /* 蜂鸣器响的时间是1000 * 500us */
/********************** 类型重定义 **********************************/

/********************** 函数外部申明 ********************************/
extern int FS_GpioInit(void);
extern void FS_Bee(void);
#endif /* __GPIO__ */
