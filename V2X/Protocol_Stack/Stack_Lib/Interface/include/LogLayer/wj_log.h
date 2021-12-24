/**
 * @defgroup WJ_LogInterface WJ_LogInterface API
 * @ingroup WJ_Interface_Com API
 * @{
 *
 * 本模块提供记录日至对外接口及数据结构头文件.
 *
 * @file wj_log.h
 * @brief API file.
 *
 */
#ifndef WJ_LOG_H
#define WJ_LOG_H

#include <stdint.h>
#include <stddef.h>
/*日志等级*/
enum
{
    LOG_LEVEL_DEBUG = 20,
    LOG_LEVEL_INFO = 40,
    LOG_LEVEL_NOTICE = 60,
    LOG_LEVEL_WARN = 80,
    LOG_LEVEL_ERR = 250,
    LOG_LEVEL_CRIT = 251,
    LOG_LEVEL_ALERT = 252,
    LOG_LEVEL_EMERG = 253
};

/**
 * 不要调用这两个函数，使用下方的 LogPint 和 HexLogPrint 函数即可
 */
extern __attribute__((visibility("default"))) void LogOut(const char *module_name, const char *file, size_t filelen, const char *func, size_t funclen, long line, int level, const char *format, ...);
extern __attribute__((visibility("default"))) void HexLogOut(const char *module_name, const char *file, size_t filelen, const char *func, size_t funclen, long line, int level, const void *buf, size_t buflen);

/**
 * 初始化log系统
 *
 * @param log_config_name[in] log配置文件
 *
 * @return int32_t
 *         0:成功;-1:失败，失败后退出整个程序
 */
extern __attribute__((visibility("default"))) int32_t LogInit(const char *LogConfigPath);

/**
 * log系统释放资源
 */
extern __attribute__((visibility("default"))) void LogDeinit(void);

/**
 * 常规输出
 * level:日志等级
 * module_name:软件模块名称
 * format,args:参考printf
 */
#define LogPrint(level, module_name, format, args...)                                             \
    LogOut(module_name, __FILE__, sizeof(__FILE__) - 1, __func__, sizeof(__func__) - 1, __LINE__, \
           level, format, ##args)

/**
 * 输出hex
 * level:日志等级
 * module_name:软件模块名称
 * buf:hex数据缓存地址
 * buflen:数据缓存大小
 */
#define HexLogPrint(level, module_name, buf, buflen)                                                 \
    HexLogOut(module_name, __FILE__, sizeof(__FILE__) - 1, __func__, sizeof(__func__) - 1, __LINE__, \
              level, buf, buflen)

#endif
