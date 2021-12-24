/***********************************************************************
 * 文 件 名 称 ： get_num.h
 * 功 能 描 述 ： 处理命令行参数的API
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/

#ifndef GET_NUM_H
#define GET_NUM_H

#define GN_NONNEG 01 /* Value must be >= 0 */
#define GN_GT_0 02   /* Value must be > 0 */

/* By default, integers are decimal */
#define GN_ANY_BASE 0100 /* Can use any base - like strtol(3) */
#define GN_BASE_8 0200   /* Value is expressed in octal */
#define GN_BASE_16 0400  /* Value is expressed in hexadecimal */

long getLong(const char *arg, int flags, const char *name);
int getInt(const char *arg, int flags, const char *name);

/* Get the Gcj location which transform from wgs84 to gcj02 */
void gps_transform(double wgLat, double wgLon, double *pMgLat, double *pMgLon);

#endif
