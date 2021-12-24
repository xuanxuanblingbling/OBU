/******************************************************************************
 * 文 件 名 称 ： V2xBasicTypes.h
 * 功 能 描 述 ： 封装用于V2X模块的基本类型的头文件
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#ifndef __V2X_BASIC_TYPES_H__
#define __V2X_BASIC_TYPES_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

/*
** ===================================================================
**     Compliler.
** ===================================================================
*/
#ifdef __cplusplus
#define V2X_BEGIN_HEADER \
    extern "C"           \
    {
#define V2X_END_HEADER }
#else
#define V2X_BEGIN_HEADER /* nothing */
#define V2X_END_HEADER
#endif

#ifdef __GNUC__
#define V2X_EXTERN extern
#else
#define V2X_EXTERN
#endif

/*
** ===================================================================
**     error types typedef and macros.
** ===================================================================
*/

typedef enum
{
    E_EXIT_OK = 0,
    E_EXIT_ERR = -1,
    E_EXIT_EINVAL = -EINVAL,
    E_EXIT_ENOMEM = -ENOMEM,
    E_EXIT_ETIMEOUT = ETIMEDOUT,
    E_EXIT_EAGAIN = EAGAIN,
    E_EXIT_EEXIST = -EEXIST
} E_exit_state_t;

#ifndef TRUE
#define TRUE 1U
#endif
#ifndef FALSE
#define FALSE 0U
#endif

typedef void *DATA;
#define MALLOC(NAME, TYPE_PTR) TYPE_PTR NAME = (TYPE_PTR)malloc(sizeof(TYPE_PTR##_t))
#define BZERO(NAME, TYPE_PTR) memset(NAME, 0, sizeof(TYPE_PTR##_t))
#define NEW(TYPE, COUNT) (TYPE *)calloc(COUNT, sizeof(TYPE))
#define CODE_TO_STR(...) "" #__VA_ARGS__ ""

typedef enum
{
    E_OK = 0,    /* 函数返回值  代表成功 */
    E_NOT_OK = 1 /* 函数返回值  代表失败 */
} Std_ReturnType;

#endif
