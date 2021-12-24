/*******************************************************************************
 * 文 件 名 称 ： Debug.h
 * 功 能 描 述 ： 常用调试宏定义
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "error_functions.h"

  enum
  {
    LOG_LV_ERR = 0,
    LOG_LV_DBG,
    LOG_LV_WRN,
    LOG_LV_INF
  };

#define B_RED(str) "\033[1;31m" str "\033[0m"
#define B_WHITE(str) "\033[1;37m" str "\033[0m"
#define B_GREEN(str) "\033[1;32m" str "\033[0m"
#define B_BLUE(str) "\033[1;34m" str "\033[0m"
#define B_YELLOW(str) "\033[1;33m" str "\033[0m"

#define EN_LOG_STDIO 1U
#define EN_DBG 0U
#ifndef USE_ZLOG
#define USE_ZLOG 1U
#endif

#if EN_LOG_STDIO
#undef EN_DBG
#define EN_DBG 1U
#endif

#if (!EN_LOG_STDIO)
#define DEF_LOG_FILE "/opt/obu.log"
#else
#define DEF_LOG_FILE ""
#endif

#ifndef MODULE_NAME
#define MODULE_NAME "V2X_OBU"
#endif

#define PRINT(type, fmt, ...)                                                                                                            \
  do                                                                                                                                     \
  {                                                                                                                                      \
    char pre_str[128] = "";                                                                                                              \
    time_t current = time(NULL);                                                                                                         \
    strftime(pre_str, sizeof(pre_str), "[%Y/%m/%d-%H:%M:%S]", localtime(&current));                                                      \
    if (EN_LOG_STDIO)                                                                                                                    \
    {                                                                                                                                    \
      if ((type) == LOG_LV_ERR)                                                                                                          \
      {                                                                                                                                  \
        printf("%s[%s][%s]:" B_RED("%s:%d:") B_WHITE(fmt), pre_str, MODULE_NAME, B_RED("ERROR"), __func__, __LINE__, ##__VA_ARGS__);     \
      }                                                                                                                                  \
      else if ((type) == LOG_LV_DBG)                                                                                                     \
      {                                                                                                                                  \
        if (!EN_DBG)                                                                                                                     \
          (void)0;                                                                                                                       \
        else                                                                                                                             \
          printf("%s[%s][%s]:" B_WHITE(fmt), pre_str, MODULE_NAME, B_BLUE("DEBUG"), ##__VA_ARGS__);                                      \
      }                                                                                                                                  \
      else if ((type) == LOG_LV_WRN)                                                                                                     \
      {                                                                                                                                  \
        printf("%s[%s][%s]:" B_GREEN("%s:%d:") B_WHITE(fmt), pre_str, MODULE_NAME, B_GREEN("WARN "), __func__, __LINE__, ##__VA_ARGS__); \
      }                                                                                                                                  \
      else if ((type) == LOG_LV_INF)                                                                                                     \
      {                                                                                                                                  \
        printf("%s[%s][%s]:" B_WHITE(fmt), pre_str, MODULE_NAME, B_WHITE("INFO "), ##__VA_ARGS__);                                       \
      }                                                                                                                                  \
    }                                                                                                                                    \
    else                                                                                                                                 \
    {                                                                                                                                    \
      FILE *fp = fopen(DEF_LOG_FILE, "a");                                                                                               \
      if ((type) == LOG_LV_ERR)                                                                                                          \
      {                                                                                                                                  \
        fprintf(fp, "%s[%s][ERROR]:%s:%d:" fmt, pre_str, MODULE_NAME, __func__, __LINE__, ##__VA_ARGS__);                                \
      }                                                                                                                                  \
      else if ((type) == LOG_LV_DBG)                                                                                                     \
      {                                                                                                                                  \
        if (!EN_DBG)                                                                                                                     \
          (void)0;                                                                                                                       \
        else                                                                                                                             \
          fprintf(fp, "%s[%s][DEBUG]: " fmt, pre_str, MODULE_NAME, ##__VA_ARGS__);                                                       \
      }                                                                                                                                  \
      else if ((type) == LOG_LV_WRN)                                                                                                     \
      {                                                                                                                                  \
        fprintf(fp, "%s[%s][WARN ]:%s:%d:" fmt, pre_str, MODULE_NAME, __func__, __LINE__, ##__VA_ARGS__);                                \
      }                                                                                                                                  \
      else if ((type) == LOG_LV_INF)                                                                                                     \
      {                                                                                                                                  \
        fprintf(fp, "%s[%s][INFO ]: " fmt, pre_str, MODULE_NAME, ##__VA_ARGS__);                                                         \
      }                                                                                                                                  \
      fflush(fp);                                                                                                                        \
      fclose(fp);                                                                                                                        \
    }                                                                                                                                    \
  } while (0)

#if USE_ZLOG

#include "wj_log.h"

#define EMERG(fmt, ...) \
  ({ LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, fmt, ##__VA_ARGS__); })

#define ALERT(fmt, ...) \
  ({ LogPrint(LOG_LEVEL_ALERT, MODULE_NAME, fmt, ##__VA_ARGS__); })

#define CRIT(fmt, ...) \
  ({ LogPrint(LOG_LEVEL_CRIT, MODULE_NAME, fmt, ##__VA_ARGS__); })

#define ERR(fmt, ...) \
  ({ LogPrint(LOG_LEVEL_ERR, MODULE_NAME, fmt, ##__VA_ARGS__); })

#define DBG(fmt, ...) \
  ({ LogPrint(LOG_LEVEL_INFO, MODULE_NAME, fmt, ##__VA_ARGS__); })

#define WRN(fmt, ...) \
  ({ LogPrint(LOG_LEVEL_WARN, MODULE_NAME, fmt, ##__VA_ARGS__); })

#define INF(fmt, ...) \
  ({ LogPrint(LOG_LEVEL_INFO, MODULE_NAME, fmt, ##__VA_ARGS__); })

#define pr_err(fmt, ...) \
  ({ LogPrint(LOG_LEVEL_ERR, MODULE_NAME, fmt, ##__VA_ARGS__); })

#else /* else of USE_ZLOG */

#define EMERG(fmt, ...) (void)0

#define ALERT(fmt, ...) (void)0

#define CRIT(fmt, ...) (void)0

#define ERR(fmt, ...) \
  ({ PRINT(LOG_LV_ERR, fmt, ##__VA_ARGS__); })

#define DBG(fmt, ...) \
  ({ PRINT(LOG_LV_DBG, fmt, ##__VA_ARGS__); })

#define WRN(fmt, ...) \
  ({ PRINT(LOG_LV_WRN, fmt, ##__VA_ARGS__); })

#define INF(fmt, ...) \
  ({ PRINT(LOG_LV_INF, fmt, ##__VA_ARGS__); })

#define pr_err(fmt, ...) \
  ({ PRINT(LOG_LV_ERR, fmt "\n", ##__VA_ARGS__); })

#endif /* end of USE_ZLOG */

#define ERR_MSG(fmt, ...) \
  ({ errMsg("%s:%d:" fmt, __func__, __LINE__, ##__VA_ARGS__); })

/*! GCC prediction built-in function
 * @param x expected to be true
 */
#define LOOK_LIKELY(x) (!!(x) == 1)

/*! GCC prediction built-in function
 * @param x expected to be false
 */
 #define LOOK_UNLIKELY(x) (!!(x) == 0)


#ifndef UTILS_MEM_HEAP_MIN_ALIGN
#define UTILS_MEM_HEAP_MIN_ALIGN (512U)
#endif
#define ETH_ALIGN(value) ((((value) + ((UTILS_MEM_HEAP_MIN_ALIGN)-1)) / (UTILS_MEM_HEAP_MIN_ALIGN)) * (UTILS_MEM_HEAP_MIN_ALIGN))
#define ETH_FLOOR(value) (((value) / (UTILS_MEM_HEAP_MIN_ALIGN)) * (UTILS_MEM_HEAP_MIN_ALIGN))
#define ROUND_UP(num, align) (((num) + ((align)-1u)) & ~((align)-1u))
#define ROUND_UP_DEF(num) ROUND_UP(num, UTILS_MEM_HEAP_MIN_ALIGN)

#ifndef OSA_assert
#define OSA_assert(x)                                                          \
  {                                                                            \
    if ((x) == 0)                                                              \
    {                                                                          \
      fprintf(stderr, " ASSERT (%s|%s|%d)\r\n", __FILE__, __func__, __LINE__); \
      while (getchar() != 'q')                                                 \
        ;                                                                      \
    }                                                                          \
  }
#endif

#ifndef UTILS_assert
#define UTILS_assert(x) OSA_assert(x)
#endif

#define DEF_ALIGN 32U
#define MALLOC_CONSTANT(type, ptr, size, align)     \
  ({                                                \
    uint32 aligned_size = ROUND_UP(size, align);    \
    ptr = (typeof( type *))calloc(1U, aligned_size); \
    ptr;                                            \
  })

#define FREE_CONSTANT(ptr) \
  ({                       \
    if (ptr)               \
    {                      \
      free(ptr);           \
      ptr = NULL;          \
    }                      \
  })

/*************************************************
  名称: Gprintf_buf
  描述: 数据打印输出
  输入参数:
        p_buf:数据区
        p_len:数据长度
        p_name:数据名
        p_type:0-16进制，1-十进制
        p_line:一行占多少数据
  返回值: 无
**************************************************/
static inline void Gfprintf(uint8_t *p_buf, int32_t p_len, char *p_name, uint8_t p_scale, uint8_t p_lineNum)
{
  int cnt = 0;
  printf("%s:----------------start-of-printf-------------------\n",p_name);
  for(cnt=0; cnt<p_len; cnt++)
  {
    if(p_scale)
    {
      printf("%d ",*p_buf++);
    }
    else
    {
      printf("%#x ", *p_buf++);
    }
    if (!(cnt % p_lineNum) && cnt != 0)
    puts("");
  }
  printf("\n%s:----------------end-of-printf-------------------\n",p_name);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
