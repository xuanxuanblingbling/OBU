#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include "zlog.h"
#include "wj_log.h"

#define LOG_DEBUG_CFG_PATH "./obulog.conf"
#define LOG_CONFIG_FILENAME "/etc/obulog.conf"
#define LOG_CATEGORY_NAME "obulog"
#define LOG_DIR "/mnt/RWD/ObuLog"

/**
 * 判断日志等级是否合法。
 * 如果输入的日志等级不合法，那么默认使用DEBUG。
 *
 * @param level[in] 日志等级
 *
 * @return int32_t 肯定合法的日志等级
 *
 * @author sdc
 */
static int32_t log_level_check(int32_t level)
{
    switch (level)
    {
    case LOG_LEVEL_DEBUG:
    case LOG_LEVEL_INFO:
    case LOG_LEVEL_NOTICE:
    case LOG_LEVEL_WARN:
    case LOG_LEVEL_ERR:
    case LOG_LEVEL_CRIT:
    case LOG_LEVEL_ALERT:
    case LOG_LEVEL_EMERG:
        return level;
        break;
    default:
        return LOG_LEVEL_DEBUG;
    }
}

int32_t LogInit(void)
{
    int32_t rc = 0;
    int find_conf = 0;

    /*初始化之前先创建该目录，用于存储生成的日志文件*/
    if (access(LOG_DIR, F_OK))
    {
        mkdir(LOG_DIR, 0755);
    }
    if (access(LOG_CONFIG_FILENAME, F_OK))
    {
        //在/etc未找到obulog.conf使用默认配置文件./obulog.conf
        rc = dzlog_init(LOG_DEBUG_CFG_PATH, LOG_CATEGORY_NAME);
    }
    else
    {
        //在/etc找到obulog.conf使用配置文件/etc/obulog.conf
        rc = dzlog_init(LOG_CONFIG_FILENAME, LOG_CATEGORY_NAME);
        find_conf = 1;
    }

    if (0 != rc)
    {
        printf("dzlog init failed, err code:%d\n", rc);
        if (find_conf)
        {
            printf("### ERROR ### Maybe '%s' or '%s' is not existed, or no " LOG_DIR " dir\n", LOG_CONFIG_FILENAME, LOG_CATEGORY_NAME);
        }
        else
        {
            printf("### ERROR ### Maybe '%s' or '%s' is not existed, or no " LOG_DIR " dir\n", LOG_DEBUG_CFG_PATH, LOG_CATEGORY_NAME);
        }
        return -1;
    }

    return 0;
}

void LogDeinit(void)
{
    zlog_fini();
}

void LogOut(const char *module_name, const char *file, size_t filelen, const char *func, size_t funclen, long line, int level, const char *format, ...)
{
    va_list marker;
    int32_t log_level = 0;

    log_level = log_level_check(level);

    zlog_put_mdc("module-name", (module_name == NULL) ? "" : module_name);
    va_start(marker, format);
    vdzlog(file, filelen, func, funclen, line, log_level, format, marker);
    va_end(marker);
}

void HexLogOut(const char *module_name, const char *file, size_t filelen, const char *func, size_t funclen, long line, int level, const void *buf, size_t buflen)
{
    int32_t log_level = 0;
    if (NULL == buf)
    {
        return;
    }
    log_level = log_level_check(level);
    zlog_put_mdc("module-name", (module_name == NULL) ? "" : module_name);
    hdzlog(file, filelen, func, funclen, line, log_level, buf, buflen);
}
