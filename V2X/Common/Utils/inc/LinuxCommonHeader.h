/******************************************************************************
 * 文 件 名 称 ： LinuxCommonHeader.h
 * 功 能 描 述 ： Linux通用头文件
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#ifndef _LINUX_COMMON_HEADER_H_
#define _LINUX_COMMON_HEADER_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Standard C includes */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>
#include <setjmp.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <pthread.h>

/* Socket stream common headers. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

/* Network ioctls. */
#include <net/if.h>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <linux/tcp.h>

#if !defined(min) && !defined(max)
#define min(m, n) ((m) < (n) ? (m) : (n))
#define max(m, n) ((m) > (n) ? (m) : (n))
#endif

#define DEF_OPEN_WO_TR_FLAG             (O_CREAT | O_WRONLY | O_TRUNC | O_DSYNC)
#define EXCL_OPEN_WO_TR_FLAG           (O_CREAT | O_WRONLY | O_EXCL | O_TRUNC | O_DSYNC)
#define DEF_OPEN_WO_AP_FLAG             (O_CREAT | O_WRONLY | O_APPEND | O_DSYNC)
#define EXCL_OPEN_WO_AP_FLAG           (O_CREAT | O_WRONLY | O_EXCL | O_APPEND | O_DSYNC)
#define DEF_OPEN_WO_FLAG                     (O_CREAT | O_WRONLY | O_DSYNC)
#define EXCL_OPEN_WO_FLAG                   (O_CREAT | O_WRONLY | O_EXCL | O_DSYNC)

#define DEF_OPEN_RO_FLAG                      (O_RDONLY)
#define EXCL_OPEN_RO_FLAG                    (O_RDONLY | O_EXCL)
#define DEF_OPEN_RW_TR_FLAG              (O_CREAT | O_RDWR | O_TRUNC | O_DSYNC)
#define EXCL_OPEN_RW_TR_FLAG            (O_CREAT | O_RDWR | O_EXCL | O_APPEND | O_DSYNC)
#define DEF_OPEN_RW_AP_FLAG              (O_CREAT | O_RDWR | O_TRUNC | O_DSYNC)
#define EXCL_OPEN_RW_AP_FLAG            (O_CREAT | O_RDWR | O_EXCL | O_APPEND | O_DSYNC)
#define DEF_OPEN_RW_FLAG                     (O_CREAT | O_RDWR | O_DSYNC)
#define EXCL_OPEN_RW_FLAG                   (O_CREAT | O_RDWR | O_EXCL | O_DSYNC)

#define DEF_FILE_PERM (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
