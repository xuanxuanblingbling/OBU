#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>
#include "zlog.h"
#include "wj_log.h"

#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <sys/inotify.h>
#include "cJSON.h"
#include "readFile.h"

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

#define RSU_LOG_VERSION ("1.4.0") /*日志模块版本号，用于区分当前使用的是否时最新版本*/

/*日志等级*/
enum
{
    LEVEL_DEBUG = 8,
    LEVEL_INFO = 7,
    LEVEL_NOTICE = 6,
    LEVEL_WARN = 5,
    LEVEL_ERR = 4,
    LEVEL_CRIT = 3,
    LEVEL_ALERT = 2,
    LEVEL_EMERG = 1
};

#define SYSLOGLEVEL_PATH "/mnt/APP/Config/Config_SystemLog.json"
#ifdef _CPPUTEST_
#define LOG_CONFIG_FILENAME "./rsu_log/rsulog.conf"
#define LOG_CONFIG_FILEDIR "./rsu_log"
#else
#define LOG_CONFIG_FILENAME "/mnt/APP/Config/RsuLogConfig/rsulog.conf"
#define LOG_CONFIG_FILEDIR "/mnt/APP/Config/RsuLogConfig"
#endif
#define LOG_CATEGORY_NAME "rsulog_process_module"

static void *ProcessReloadThreadFun(void *para);
static int logInitFlag = 0;

char LogConfigFILEDIR[128] = {0};
char LogFILENAME[32] = {0};
char LogConfigFileName[128] = {0};
char LogCATEGORYName[128] = {0};

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

__attribute__((visibility("default"))) int32_t LogInit(const char *LogConfigPath)
{
    if (NULL == LogConfigPath)
    {
        return -1;
    }
    int32_t rc = 0;
    pthread_t tid = 0;
    pthread_attr_t attr = {0};

    // #ifdef _CPPUTEST_
    //     rc = system("mkdir -p ./rsu_log"); /*初始化之前先创建该目录，用于存储生成的日志文件*/
    //     if (0 != rc)
    //     {
    //         printf("mkdir rsu_log faild \n");

    //         return -1;
    //     }
    // #else
    //     system((char *)"mkdir -p /mnt/RWD/RsuLog"); /*初始化之前先创建该目录，用于存储生成的日志文件*/
    // #endif

    rc = readFile(LogConfigPath);
    if (0 != rc)
    {
        printf("---3---dzlog init failed, err code:%d\n", rc);
        printf("maybe '%s' or '%s' is not existed, or no '/mnt/RWD/RsuLog' dir\n", LogConfigPath, LogCATEGORYName);
        return -1;
    }

    rc = dzlog_init(LogConfigPath, LogCATEGORYName);
    if (0 != rc)
    {
        printf("dzlog init failed, err code:%d\n", rc);
        printf("maybe '%s' or '%s' is not existed, or no '/mnt/RWD/RsuLog' dir\n", LogConfigPath, LogCATEGORYName);
        return -1;
    }

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    rc = pthread_create(&tid, &attr, ProcessReloadThreadFun, NULL);
    pthread_attr_destroy(&attr);

    if (0 != rc)
    {
        printf("create socket server recv loglevel thread faild ! \n");
        return -1;
    }

    logInitFlag = 1;

    return 0;
}

__attribute__((visibility("default"))) void LogDeinit(void)
{
    if (logInitFlag != 1)
    {
        return;
    }
    zlog_fini();
}

__attribute__((visibility("default"))) void LogOut(const char *module_name, const char *file, size_t filelen, const char *func, size_t funclen, long line, int level, const char *format, ...)
{
    if (logInitFlag != 1)
    {
        return;
    }
    va_list marker;
    int32_t log_level = 0;

    log_level = log_level_check(level);

    zlog_put_mdc("module-name", (module_name == NULL) ? "" : module_name);
    va_start(marker, format);
    vdzlog(file, filelen, func, funclen, line, log_level, format, marker);
    va_end(marker);
}

__attribute__((visibility("default"))) void HexLogOut(const char *module_name, const char *file, size_t filelen, const char *func, size_t funclen, long line, int level, const void *buf, size_t buflen)
{
    if (logInitFlag != 1)
    {
        return;
    }
    int32_t log_level = 0;
    if (NULL == buf)
    {
        return;
    }
    log_level = log_level_check(level);
    zlog_put_mdc("module-name", (module_name == NULL) ? "" : module_name);
    hdzlog(file, filelen, func, funclen, line, log_level, buf, buflen);
}

/* 检测.conf文件是否改变，改变后重新加载reload */
static void *ProcessReloadThreadFun(void *para)
{
    int length;
    int fd;
    int wd;
    char buffer[BUF_LEN];

    int nRet;

    fd = inotify_init();

    if (fd < 0)
    {
        printf("%s %s %d inotify_init error\n", __FILE__, __FUNCTION__, __LINE__);
        return NULL;
    }

    wd = inotify_add_watch(fd, LogConfigFILEDIR, IN_MODIFY);
    if (wd < 0)
    {
        printf("%s %s %d inotify_add_watch error\n", __FILE__, __FUNCTION__, __LINE__);
        (void)close(fd);
        return NULL;
    }

    while (1)
    {
        length = read(fd, buffer, BUF_LEN);
        if (length < 0)
        {
            perror("read");
        }
        struct inotify_event *event = (struct inotify_event *)&buffer[0];
        if (event->len)
        {
            if (event->mask & IN_MODIFY)
            {
                //printf("The directory %s was IN_MODIFY.\n", event->name);
                if (strcmp(event->name, LogFILENAME) == 0)
                {
                    nRet = zlog_reload(LogConfigFileName);
                    if (0 == nRet)
                    {
                        LogPrint(LOG_LEVEL_INFO, "Log", "modify log confg success \n");
                    }
                    printf("The file name is%s \n", event->name);
                }
            }
        }
    }

    (void)inotify_rm_watch(fd, wd);
    (void)close(fd);
}
