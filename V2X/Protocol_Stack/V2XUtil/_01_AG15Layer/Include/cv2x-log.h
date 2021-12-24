/*
 *  Copyright (c) 2017 Qualcomm Technologies, Inc.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <stdarg.h>
#include <stdio.h>
#include <syslog.h>

#define LOGI(fmt, args...) \
    cv2xlog(LOG_NOTICE, "[I][%s:%d] " fmt, __func__, __LINE__, ## args)
#define LOGD(fmt, args...) \
    cv2xlog(LOG_DEBUG, "[D][%s:%d] " fmt, __func__, __LINE__, ## args)
#define LOGE(fmt, args...) \
    cv2xlog(LOG_ERR, "[E][%s:%d] " fmt, __func__, __LINE__, ## args)

#ifdef __cplusplus
extern "C" {
#endif

void cv2xlog(int level, const char *fmt, ...);

#ifdef __cplusplus
}
#endif
