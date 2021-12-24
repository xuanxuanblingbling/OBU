#ifndef NET_LOG_H
#define NET_LOG_H

#include <stdint.h>
 
#ifdef __cplusplus
	extern "C"{
#endif

/**
 * 不要调用这两个函数，使用下方的 LogPint 和 HexLogPrint 函数即可 
 */
extern  void LogOut(const char *module_name, const char *file, size_t filelen, const char *func, size_t funclen, long line, int level, const char *format, ...);
extern  void HexLogOut(const char *module_name, const char *file, size_t filelen, const char *func, size_t funclen, long line, int level, const void *buf, size_t buflen);

	
#define LOG_MODLE_NAME          "NET"

/*日志等级*/
#define LOG_LEVEL_DEBUG				20
#define	LOG_LEVEL_INFO				40
#define	LOG_LEVEL_WARN				80
#define LOG_LEVEL_ERR				250


/* 暂不使用 */
#define	LOG_LEVEL_NOTICE			60
#define LOG_LEVEL_CRIT				251 
#define LOG_LEVEL_ALERT				252
#define LOG_LEVEL_EMERG				253

/**
 * 初始化log系统
 * 
 * @param log_config_name[in] log配置文件
 * 
 * @return int32_t 
 *         0:成功;-1:失败，失败后退出整个程序
 */

extern  int32_t LogInit(void);

/**
 * log系统释放资源
 */
extern  void LogDeinit(void);

/**
 * 常规输出 
 * level:日志等级 
 * module_name:软件模块名称 
 * format,args:参考printf 
 */
#define LogPrint(level, module_name, format, args...) \
    LogOut(module_name, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
	       level, format, ##args)

/**
 * 输出hex 
 * level:日志等级 
 * module_name:软件模块名称 
 * buf:hex数据缓存地址 
 * buflen:数据缓存大小
 */
#define HexLogPrint(level, module_name, buf, buflen) \
	   HexLogOut(module_name, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
	          level, buf, buflen)

#ifdef __cplusplus
}
#endif

#endif

