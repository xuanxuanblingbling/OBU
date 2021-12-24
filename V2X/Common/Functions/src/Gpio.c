/***********************************************************************
* 文 件 名 称 ： Gpio.c
* 功 能 描 述 ： 操作GPIO实现对设备的控制
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-09 V1.0    黄赛   Create
*
* @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
/************************  包含的头文件  ********************************/
#include "Gpio.h"
#include <unistd.h>


#define SYSFS_GPIO_EXPORT    "/sys/class/gpio/export"
/***************************  函数定义  ********************************/
/***********************************************************************
* 函 数 名 称 ： FS_GpioInit
* 功 能 描 述 ： 操作GPIO
* 输 入 参 数 ：    无
* 输 出 参 数 ：    无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-09 V1.0    黄赛   Create
***********************************************************************/
int FS_GpioInit(void)
{
    char l_an8str[50];
 //   int32 l_n32fd = 0;
 //   int32 l_n32Ret = 0;
    uint32 l_u32i = 0;
 //   char buf[20] = " ";
    char* l_pn8LedOpt[OPTIONNUM][2] = {   /* 打开操作IO接口控制文件 /sys/class/gpio/export */
                            {SYSFS_GPIO_EXPORT, V2X_LED1},
                            {SYSFS_GPIO_EXPORT, V2X_LED2},
                            {SYSFS_GPIO_EXPORT, SYS_LED1},
                            {SYSFS_GPIO_EXPORT, SYS_LED2},
                            {SYSFS_GPIO_EXPORT, UPD_LED1},
                            {SYSFS_GPIO_EXPORT, UPD_LED2},
                            {SYSFS_GPIO_EXPORT, GNSS_LED1},
                            {SYSFS_GPIO_EXPORT, GNSS_LED2},
                            {SYSFS_GPIO_EXPORT, BEE_INPUT},
                            /* 设置操作接口 */
                            {"/sys/class/gpio/gpio114/direction", DIRECT_OUT},
                            {"/sys/class/gpio/gpio115/direction", DIRECT_OUT},
                            {"/sys/class/gpio/gpio79/direction", DIRECT_OUT},
                            {"/sys/class/gpio/gpio78/direction", DIRECT_OUT},
                            {"/sys/class/gpio/gpio77/direction", DIRECT_OUT},
                            {"/sys/class/gpio/gpio76/direction", DIRECT_OUT},
                            {"/sys/class/gpio/gpio74/direction", DIRECT_OUT},
                            {"/sys/class/gpio/gpio73/direction", DIRECT_OUT},
                            {"/sys/class/gpio/gpio113/direction", DIRECT_OUT},
                        //    {"/sys/class/input/input0/op_mode", BMP_MODE}
                            };
 //   chmod(SYSFS_GPIO_EXPORT, 0777);
    for (l_u32i = 0; l_u32i < OPTIONNUM; l_u32i++)
    {
        #if 0
        l_n32fd = open(l_pn8LedOpt[l_u32i][0], O_RDWR);
        if(-1 == l_n32fd)
        {
            LogPrint(LOG_LEVEL_ERR, "GpioInit", "Open Gpio File Failed");
            perror("open file is err");
            return IS_ERR;
        }
        printf("l_n32fd=%d\n", l_n32fd);
        snprintf(buf, sizeof(buf), "%d", V2X_LED1);
        l_n32Ret = write(l_n32fd, buf, strlen(buf));
     //   l_n32Ret = write(l_n32fd, l_pn8LedOpt[l_u32i][1], (size_t)sizeof(l_pn8LedOpt[l_u32i][1]));
        if(0 > l_n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR, "GpioInit", "write Gpio-%s File Failed", l_pn8LedOpt[l_u32i][1]);
            perror("write file is err");
            return IS_ERR;
        }
        l_n32Ret = close(l_n32fd);
        if(IS_OK == l_n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR, "GpioInit", "close Gpio File Failed");
            perror("close file is err");
            return IS_ERR;
        }
        #endif
        sprintf(l_an8str, "echo %s > %s", l_pn8LedOpt[l_u32i][1], l_pn8LedOpt[l_u32i][0]);
        system(l_an8str);
        LogPrint(LOG_LEVEL_DEBUG, "GpioInit", "GpioInit is OK");
    }
    return IS_OK;
}
/***********************************************************************
* 函 数 名 称 ： FS_Bee
* 功 能 描 述 ： 响蜂鸣器告诉系统进程创建完成
* 输 入 参 数 ： 无
* 输 出 参 数 ： 无
* 返  回  值  : IS_OK/IS_ERR              成功/失败
* 开 发 人 员 ： 黄赛
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-06-10 V1.0    黄赛   Create
***********************************************************************/
void FS_Bee(void)
{
    int32 l_n32fd = 0;
    int32 l_n32Ret = 0;
    uint32 l_u32i = 0;
    for (l_u32i = 0; l_u32i < BEE_COUNT; l_u32i++)
    {
        /* 向文件里面写1 */
        l_n32fd = open("/sys/class/gpio/gpio113/value", O_WRONLY);
        if(-1 == l_n32fd)
        {
            LogPrint(LOG_LEVEL_ERR, "GpioInit", "Open Gpio File Failed");
            perror("open file is err");
            return;
        }
        l_n32Ret = write(l_n32fd, "1", 1);
        if(0 > l_n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR, "GpioInit", "write Gpio File Failed");
            perror("write file is err");
            return;
        }
        l_n32Ret = close(l_n32fd);
        if(IS_OK != l_n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR, "GpioInit", "close Gpio File Failed");
            perror("close file is err");
            return;
        }
        usleep(BEE_SLEEP);
        /* 向文件里面写1 */
        l_n32fd = open("/sys/class/gpio/gpio113/value", O_WRONLY);
        if(-1 == l_n32fd)
        {
            LogPrint(LOG_LEVEL_ERR, "GpioInit", "Open Gpio File Failed");
            perror("open file is err");
            return;
        }
        l_n32Ret = write(l_n32fd, "0", 1);
        if(0 > l_n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR, "GpioInit", "write Gpio File Failed");
            perror("write file is err");
            return;
        }
        l_n32Ret = close(l_n32fd);
        if(IS_OK != l_n32Ret)
        {
            LogPrint(LOG_LEVEL_ERR, "GpioInit", "close Gpio File Failed");
            perror("close file is err");
            return;
        }
        usleep(BEE_SLEEP);
    }
    return;
}
/***************************  文件结束  ********************************/






