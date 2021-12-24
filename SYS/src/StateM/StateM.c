/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       StateM.c
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : StateM.c
*   Author:         : chengwu.wang       2020
********************************************************************************
*   Limitations:      None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version       Date       Initials        CR#        Descriptions
*   -------   ----------  --------------    ------    -------------------
*   01.00.00  07/07/2020  chengwu.wang      N/A         Original
********************************************************************************
*END_FILE_HDR*/
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/vfs.h>
#include "wj_log.h"

#include "Cfg.h"
#include "StateM_Lcfg.h"
#include "StateM.h"
#include "LED.h"

static t_StateMRetFlag StateM_ReadJFile(char *filename)
{
	char buf[STATEM_BUF_SIZE] = {0};
	FILE *fp;
	int f_size;
	int re_fread;
	int errNum;
	const char *error_ptr;

	if ((fp = fopen(filename, "r")) == NULL)
	{
		errNum = errno;
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "StateM open fail errno = %d reason = %s \n", errNum, strerror(errNum));
		return STATEM_FALSE;
	}

	LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM fopen %s r success", filename);

	fseek(fp, 0, SEEK_END);
	f_size = ftell(fp);
	rewind(fp);

	re_fread = fread(buf, f_size, 1, fp);
	if (re_fread != 1)
	{
		fclose(fp);
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "StateM fread %s error", filename);
		return STATEM_FALSE;
	}
	fclose(fp);

	STATEM_JSON_FILE = cJSON_Parse(buf);

	if (NULL == STATEM_JSON_FILE)
	{
		error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "StateM cJSON_Parse error: %s", error_ptr);
		else
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "StateM cJSON_Parse %s error", filename);
		return STATEM_FALSE;
	}

	return STATEM_SUCCESS;
}

static t_StateMRetFlag StateM_WriteJFile(char *filename, cJSON *json)
{
	char *re_cjprint;
	FILE *fp;
	int re_fwrite;
	re_cjprint = cJSON_Print(json);

	if (STATEM_JSON_FILE)
	{
		cJSON_Delete(STATEM_JSON_FILE);
		STATEM_JSON_FILE = NULL;
	}

	fp = fopen(filename, "r+");
	if (NULL == fp)
	{
		cJSON_free(re_cjprint);
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "StateM fopen a error");
		return STATEM_FALSE;
	}
	else
	{
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM fopen %s r+ success", filename);
		re_fwrite = fwrite(re_cjprint, strlen(re_cjprint), 1, fp);
		if (re_fwrite != 1)
		{
			cJSON_free(re_cjprint);
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "StateM fwrite error");
			return STATEM_FALSE;
		}
		fclose(fp);
	}
	cJSON_free(re_cjprint);
	return STATEM_SUCCESS;
}

/*获取各个模块的CPU使用率*/
void getModulesCpuMemUsage(long s_all, long f_all)
{
	char filename[1000];
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	int utime, stime, cutime, cstime;
	int pid;
	char name[20];
	for (int i = 0; i < mPidCount; i++)
	{
		memset(filename, 0, sizeof(filename));
		sprintf(filename, "/proc/%d/stat", processID[i]);
		fp1 = fopen(filename, "r");
		if (fp1 != NULL)
		{
			fscanf(fp1, "%d %s %*c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d %d %d %d", &pid, name, &utime, &stime, &cutime, &cstime);
			processCpuTime1[i] = utime + stime + cutime + cstime;
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, " -Before pid=%d, name=%s, utime=%d, stime=%d, cutime=%d, cstime=%d, processCpuTime1=%d", pid, name, utime, stime, cutime, cstime, processCpuTime1[i]);
			fclose(fp1);
			fp1 = NULL;
		}
		else
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, " -Before open file fail!");
		}
	}
	sleep(1);
	for (int i = 0; i < mPidCount; i++)
	{
		memset(filename, 0, sizeof(filename));
		sprintf(filename, "/proc/%d/stat", processID[i]);
		fp2 = fopen(filename, "r");
		if (fp2 != NULL)
		{
			fscanf(fp2, "%d %s %*c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d %d %d %d", &pid, name, &utime, &stime, &cutime, &cstime);
			processCpuTime2[i] = utime + stime + cutime + cstime;
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, " -After pid=%d, name=%s, utime=%d, stime=%d, cutime=%d, cstime=%d, processCpuTime2=%d", pid, name, utime, stime, cutime, cstime, processCpuTime2[i]);
			fclose(fp2);
			fp2 = NULL;
		}
		else
		{
			LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, " -After open file fail!");
		}
	}
	for (int i = 0; i < mPidCount; i++)
	{
		modulesCpuusage[i] = ((double)(processCpuTime2[i] - processCpuTime1[i]) / (double)(s_all - f_all)) * 100.0;
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, " modules modulesCpuusage = %f ", modulesCpuusage[i]);
	}
}

/*获取总的mem,同时输出每个模块的内存使用率*/
void getUsage(int pmodulesMem[5])
{
	char buf[256] = {0};
	long mem_total = 0;
	FILE *fd_mem = NULL;
	fd_mem = fopen("/proc/meminfo", "r");
	if (fd_mem != NULL)
	{
		fgets(buf, sizeof(buf), fd_mem);
		sscanf(buf, "%*s %lu %*s", &mem_total);
		fclose(fd_mem); //关闭文件fd
		fd_mem = NULL;

		for (int i = 0; i < mPidCount; i++)
		{
			memoryusage[i] = (double)((double)pmodulesMem[i] / (double)mem_total) * 100.0;
			// snprintf(memoryusage[i], 20, "%.2lf", memUsage);
		}
	}
	else
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, " -getUsage open meminfo file fail!");
	}
}
/*获取各个程序内存占用率*/
void getModulesMemUsage(int pid[5])
{
	char file[64] = {0};	   //文件名
	FILE *fd = NULL;		   //定义文件指针fd
	char line_buff[256] = {0}; //读取行的缓冲区
	int modulesVrss[5];
	for (int i = 0; i < mPidCount; i++)
	{
		memset(file, 0, sizeof(file));
		sprintf(file, "/proc/%d/status", pid[i]);
		// fprintf (stderr, "current pid:%s\n", pid[i]);
		fd = fopen(file, "r"); //以R读的方式打开文件再赋给指针fd
		if (fd != NULL)
		{
			//获取vmrss:实际物理内存占用
			char name[32]; //存放项目名称
			int vmrss;	   //存放内存
			//读取VmRSS这一行的数据
			for (int i = 0; i < 17; i++)
			{
				char *ret = fgets(line_buff, sizeof(line_buff), fd);
			}
			char *ret1 = fgets(line_buff, sizeof(line_buff), fd);
			sscanf(line_buff, "%s %d", name, &modulesVrss[i]);

			if (fd != NULL)
			{
				fclose(fd);
			}
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, " modules memvrss = %d ", modulesVrss[i]);
		}
	}

	getUsage(modulesVrss);
}

/*输出各个进程ID,使用popen函数进行读取，同时也可以使用system函数将其输出到文件中*/
void getProcessId()
{
	mPidCount = 0;
	char commandStr[5][40] = {"top -n 1 | grep ./vds", "top -n 1 | grep ./NET_ARM.bin", "top -n 1 | grep ./V2X_APP.bin",
							  "top -n 1 | grep ./app", "top -n 1 | grep ./sysm"};

	FILE *fp = NULL;
	for (int i = 0; i < 5; i++)
	{
		char buffer[100] = {0};
		memset(buffer, 0, sizeof(buffer));
		fp = popen(commandStr[i], "r");
		if (fp != NULL)
		{
			if (fgets(buffer, 100, fp) != NULL)
			{
				if (sscanf(buffer, "%d", &processID[mPidCount]) == 1)
				{ //可以输出各个进程ID
					mPidCount++;
				}
			}
		}
		if (fp != NULL)
		{
			pclose(fp);
		}
	}
}

void task(int i)
{
	int errNum;
	FILE *fp;
	char buf[128];
	long int user, nice, sys, idle, iowait, irq, softirq;
	long int f_all, s_all, f_idle, s_idle;

	fp = fopen("/proc/stat", "r");
	if (fp == NULL)
	{
		errNum = errno;
		LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "StateM fopen fail errno = %d reason = %s \n", errNum, strerror(errNum));
		return;
	}
	fgets(buf, sizeof(buf), fp); //获取第一行数据
	sscanf(buf, "%*s %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &sys, &idle, &iowait, &irq, &softirq);

	f_all = user + nice + sys + idle + iowait + irq + softirq;
	f_idle = idle;
	rewind(fp); //重新指向开头

	/*第二次取数据*/
	sleep(1); //间断1秒
	memset(buf, 0, sizeof(buf));
	user = nice = sys = idle = iowait = irq = softirq = 0;

	fgets(buf, sizeof(buf), fp);
	sscanf(buf, "%*s %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &sys, &idle, &iowait, &irq, &softirq);
	fclose(fp);

	s_all = user + nice + sys + idle + iowait + irq + softirq;
	s_idle = idle;
	usage = ((double)(s_all - f_all - (s_idle - f_idle)) / (double)(s_all - f_all)) * 100.0;

	//目的是为了3s执行一次个进程ID更新， 要不然太频繁操作造成顺序错乱
	if (mCount % 2 == 0)
	{
		mCount = 1;
		//获取各个进程ID。
		getProcessId();
		//获取各个进程的CPU使用率
		getModulesCpuMemUsage(s_all, f_all);
	}
	else
	{
		mCount++;
	}
}

/****创建定时器***********/
void create_timer()
{
	struct sigevent evp; //环境结构体
	int ret = 0;

	memset(&evp, 0, sizeof(struct sigevent));

	evp.sigev_value.sival_ptr = &timeid; //绑定i定时器
	evp.sigev_notify = SIGEV_SIGNAL;	 //设置定时器到期后触发的行为是为发送信号
	evp.sigev_signo = SIGUSR1;			 //设置信号为用户自定义信号1
	signal(SIGUSR1, task);				 //绑定产生信号后调用的函数

	ret = timer_create(CLOCK_REALTIME, &evp, &timeid); //创建定时器
	if (ret == 0)
		LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "StateM create_timer success");
}

void init_timer()
{
	int ret = 0;
	struct itimerspec ts;
	ts.it_interval.tv_sec = 3; //设置定时器的定时周期是3s
	ts.it_interval.tv_nsec = 0;
	ts.it_value.tv_sec = 1; //设置定时器1s后启动
	ts.it_value.tv_nsec = 0;

	ret = timer_settime(timeid, 0, &ts, NULL); //初始化定时器
	if (ret == 0)
		LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "StateM timer_settime success");
}

static t_StateMRetFlag Get_SOCTEMP_Info(char *soctemp)
{
	int temp, errNum;
	FILE *fp;
	fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r"); //正式路径
	if (NULL == fp)
	{
		errNum = errno;
		LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "StateM fopen fail errno = %d reason = %s \n", errNum, strerror(errNum));
		return STATEM_FALSE;
	}
	fscanf(fp, "%d", &temp);
	fclose(fp);
	snprintf(soctemp, SOCTEMPMAX, "%.3f", temp / 1000.0);
	return STATEM_SUCCESS;
}

static t_StateMRetFlag StateM_GetMemUsage_Info(char *memoryusage)
{
	FILE *fp;
	int errNum;
	char buf[256] = {0};
	double mem_used_rate = 0;
	long mem_date = 0;
	long mem_total = 0;
	fp = fopen("/proc/meminfo", "r");
	if (NULL == fp)
	{
		errNum = errno;
		LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "StateM fopen fail errno = %d reason = %s \n", errNum, strerror(errNum));
		return STATEM_FALSE;
	}
	fgets(buf, sizeof(buf), fp); //memtotal
	sscanf(buf, "%*s %lu %*s", &mem_total);

	fgets(buf, sizeof(buf), fp); //丢弃不用memfree
	fgets(buf, sizeof(buf), fp); //用memAvailable
	fclose(fp);
	sscanf(buf, "%*s %lu %*s", &mem_date);
	mem_used_rate = (1 - mem_date / (double)mem_total) * 100;
	snprintf(memoryusage, MEMORYUSAGEMAX, "%.2lf", mem_used_rate);
	return STATEM_SUCCESS;
}

static t_StateMRetFlag Get_SOCSTARTTIME_Info(char *socstarttime)
{
	struct sysinfo s_info;
	time_t cur_time = 0;
	time_t start_time = 0;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	cur_time = tv.tv_sec;

	if (sysinfo(&s_info))
	{
		LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "Failed to get sysinfo, errno:%u, reason:%s", errno, strerror(errno));
		return STATEM_FALSE;
	}
	else
	{
		if (cur_time > s_info.uptime)
			start_time = cur_time - s_info.uptime;
		else
			return STATEM_FALSE;
		strftime(socstarttime, 20, "%Y.%m.%d %H:%M:%S", localtime(&start_time));
		return STATEM_SUCCESS;
	}
}

static void Get_CURRENTTIME_Info(char *currenttime)
{
	time_t ti;
	char buf_time[20];
	struct timeval tv;
	int microsecond;

	gettimeofday(&tv, NULL);
	ti = tv.tv_sec;
	microsecond = tv.tv_usec / 1000;
	strftime(buf_time, 20, "%Y.%m.%d %H:%M:%S", localtime(&ti));
	snprintf(currenttime, CURRENTTIMEMAX, "%s:%03d", buf_time, microsecond);
}

/**************************
 * @name: LEDindateState(char *modulename , cJSON *statedata)
 * @bref:  set LED state base on the monitor data
 * @input: modulename: module name
 *         statedata:module state data
 * @output: NO
 * @return: NO
 * ===============================
 * Copyright (C) 2020 by wanji
 * author: CBS  20201221
******/
#define RTK 140
#define NORTK 130
#define RTKFault 141
#define AG15Fault 131

void LEDindateState(char *modulename, cJSON *statedata)
{

	if (!strcmp(modulename, V2Xname)) //V2X 模块
	{
		// LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "=STATE V2X MODULE  matched ==");
		LEDStateSet(V2Xname, TWINKLE);
	}
	else if (!strcmp(modulename, vdsname)) //vds 模块
	{
		if (statedata->valueint == NORTK)
		{
			LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "=STATE VDS IS NORTK ==");
			LEDStateSet(vdsname, TWINKFAST);
		}
		else if (statedata->valueint == RTK)
		{
			LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "=STATE VDS IS RTK ==");
			LEDStateSet(vdsname, TWINKLE);
		}
		else if ((statedata->valueint == RTKFault) || (statedata->valueint == AG15Fault))
		{
			LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "=STATE VDS IS Fault ==");
			LEDStateSet(vdsname, RED);
		}
		else
		{
			LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "Gnss state is Wrong");
		}
	}
	else
	{
		LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "modulename can not matched!!");
	}
}

static t_StateMRetFlag StateM_ChgJFile(int JsonKeyid)
{
	int i, j;
	t_StateMRetFlag ret;
	cJSON *re_SecTemp;
	cJSON *re_FirRoot;

	for (i = 0; i < STATEM_MODLE_NUM; i++)
	{
		if ((STATEM_TABLE_INDEX(i) & JsonKeyid) != 0)
		{
			re_FirRoot = cJSON_GetObjectItem(STATEM_JSON_FILE, STATEM_TABLE_MODLENAME(i));
			if (re_FirRoot->type == CJSON_OBJECT)
			{
				for (j = 0; j < STATEM_TABLE_SMCNUM(i); j++)
				{
					re_SecTemp = cJSON_GetObjectItem(re_FirRoot, STATEM_TABLE_STATEINFO(i)[j].SMCName);
					LEDindateState(STATEM_TABLE_MODLENAME(i), re_SecTemp);
					if (re_SecTemp->type == CJSON_NUMBER)
					{
						cJSON_SetIntValue(re_SecTemp, *STATEM_TABLE_STATEINFO(i)[j].ptKeyValue);
					}
					else if (re_SecTemp->type == CJSON_STRING)
					{
						cJSON_SetValuestring(re_SecTemp, STATEM_TABLE_STATEINFO(i)[j].ptStateInfo);
					}
					else
					{
						LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "StateM %s type error", STATEM_TABLE_STATEINFO(i)[j].SMCName);
						return STATEM_FALSE;
					}
				}
			}
			else if (re_FirRoot->type == CJSON_NUMBER)
			{
				cJSON_SetIntValue(re_FirRoot, *STATEM_TABLE_STATEINFO(i)->ptKeyValue);
			}
			else
			{
				LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "StateM %s type error", STATEM_TABLE_MODLENAME(i));
				return STATEM_FALSE;
			}
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM change json struct success");
		}
	}

	re_FirRoot = cJSON_GetObjectItem(STATEM_JSON_FILE, STATEM_HARDWARESTATE_KEY);
	/* 修改温度 */

	ret = Get_SOCTEMP_Info(STATEM_SOCTEMP_VAL);
	if (ret == STATEM_SUCCESS)
	{
		re_SecTemp = cJSON_GetObjectItem(re_FirRoot, STATEM_SOCTEMP_KEY);
		cJSON_SetValuestring(re_SecTemp, STATEM_SOCTEMP_VAL);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM %s has changed", STATEM_SOCTEMP_KEY);
	}

	/*CPU占有率--取定时器计算得到的值*/
	if (usage != 0)
	{
		snprintf(STATEM_CPUUSAGE_VAL, CPUUSAGEMAX, "%.2lf", usage);
		re_SecTemp = cJSON_GetObjectItem(re_FirRoot, STATEM_CPUUSAGE_KEY);
		cJSON_SetValuestring(re_SecTemp, STATEM_CPUUSAGE_VAL);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM %s has changed", STATEM_CPUUSAGE_KEY);
	}
	//注：用定时器实现-隔3秒计算一次cpu占用率

	/*内存使用率*/
	ret = StateM_GetMemUsage_Info(STATEM_MEMORYUSAGE_VAL);
	if (ret == STATEM_SUCCESS)
	{
		re_SecTemp = cJSON_GetObjectItem(re_FirRoot, STATEM_MEMORYUSAGE_KEY);
		cJSON_SetValuestring(re_SecTemp, STATEM_MEMORYUSAGE_VAL);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM %s has changed", STATEM_MEMORYUSAGE_KEY);
	}

	/*硬盘使用率 */
	ret = Get_DISKUSAGE_Info(STATEM_DISKUSAGE_VAL);
	if (ret == STATEM_SUCCESS)
	{
		re_SecTemp = cJSON_GetObjectItem(re_FirRoot, STATEM_DISKUSAGE_KEY);
		cJSON_SetValuestring(re_SecTemp, STATEM_DISKUSAGE_VAL);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM %s has changed", STATEM_DISKUSAGE_KEY);
	}

	/* 修改时间 */
	re_FirRoot = cJSON_GetObjectItem(STATEM_JSON_FILE, STATEM_TIMEINFO_KEY);
	Get_CURRENTTIME_Info(STATEM_CURRENTTIME_VAL);
	re_SecTemp = cJSON_GetObjectItem(re_FirRoot, STATEM_CURRENTTIME_KEY);
	cJSON_SetValuestring(re_SecTemp, STATEM_CURRENTTIME_VAL);

	LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM %s has changed", STATEM_CURRENTTIME_KEY);

	//系统启动时间
	ret = Get_SOCSTARTTIME_Info(STATEM_SOCSTARTTIME_VAL);
	if (ret == STATEM_SUCCESS)
	{
		re_SecTemp = cJSON_GetObjectItem(re_FirRoot, STATEM_SOCSTARTTIME_KEY);
		cJSON_SetValuestring(re_SecTemp, STATEM_SOCSTARTTIME_VAL);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM %s has changed", STATEM_SOCSTARTTIME_KEY);
	}

	/*modify modules cpu & mem usage*/
	char ModuleName[5][20] = {STATEM_VDSCPUMEM_KEY, STATEM_NETCPUMEM_KEY, STATEM_V2XCPUMEM_KEY, STATEM_APPCPUMEM_KEY, STATEM_SYSCPUMEM_KEY};
	char ModuleCpuUsageKey[5][50] = {STATEM_VDSCPUUSAGE_VAL, STATEM_NETCPUUSAGE_VAL, STATEM_V2XCPUUSAGE_VAL, STATEM_APPCPUUSAGE_VAL, STATEM_SYSCPUUSAGE_VAL};
	char ModuleMemUsageKey[5][50] = {STATEM_VDSMEMORYUSAGE_VAL, STATEM_NETMEMORYUSAGE_VAL, STATEM_V2XMEMORYUSAGE_VAL, STATEM_APPMEMORYUSAGE_VAL, STATEM_SYSMEMORYUSAGE_VAL};

	cJSON *modulesCpuMem = NULL;
	for (int i = 0; i < 5; i++)
	{
		re_FirRoot = cJSON_GetObjectItem(STATEM_JSON_FILE, ModuleName[i]);
		if (re_FirRoot == NULL)
		{
			modulesCpuMem = cJSON_CreateObject();
			cJSON_AddItemToObject(STATEM_JSON_FILE, ModuleName[i], modulesCpuMem);
			cJSON_AddStringToObject(modulesCpuMem, "CpuUsage", "0.00");
			cJSON_AddStringToObject(modulesCpuMem, "MemoryUsage", "0.00");
		}
		else
		{
			/*CPU占有率--取定时器计算得到的值*/
			snprintf(ModuleCpuUsageKey[i], CPUUSAGEMAX, "%.2lf", modulesCpuusage[i]);
			re_SecTemp = cJSON_GetObjectItem(re_FirRoot, STATEM_CPUUSAGE_KEY);
			cJSON_SetValuestring(re_SecTemp, ModuleCpuUsageKey[i]);
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, " %s StateM %s has changed", ModuleName[i], STATEM_CPUUSAGE_KEY);

			/*内存使用率*/
			if (processID[0] != '\0')
			{
				getModulesMemUsage(processID);

				snprintf(ModuleMemUsageKey[i], MEMORYUSAGEMAX, "%.2lf", memoryusage[i]);
				re_SecTemp = cJSON_GetObjectItem(re_FirRoot, STATEM_MEMORYUSAGE_KEY);
				cJSON_SetValuestring(re_SecTemp, ModuleMemUsageKey[i]);

				LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, " %s StateM %s has changed", ModuleName[i], STATEM_MEMORYUSAGE_KEY);
			}
		}
	}
	return STATEM_SUCCESS;
}

static t_StateMRetFlag Get_DISKUSAGE_Info(char *diskusage)
{

	FILE *fp;
	int errNum;
	char buf[500];
	double b, c;
	double total = 0;
	double used = 0;
	double handle_temp;
	fp = popen("/bin/df", "r");
	if (fp == NULL)
	{
		errNum = errno;
		LogPrint(LOG_LEVEL_WARN, LOG_MODLE_NAME, "StateM popen fail errno = %d reason = %s \n", errNum, strerror(errNum));
		return STATEM_FALSE;
	}
	if (fgets(buf, 500, fp) == NULL)
	{
		pclose(fp);
		return STATEM_FALSE;
	}
	else
	{
		while (2 == fscanf(fp, "%*s %lf %lf %*s %*s %*s", &b, &c))
		{
			total += b;
			used += c;
		}
		pclose(fp);
		handle_temp = used / total * 100;
		snprintf(diskusage, DISKUSAGEMAX, "%.2lf", handle_temp);
		return STATEM_SUCCESS;
	}
}

void StateM_Main()
{
	t_StateMRetFlag ret;
	LogPrint(LOG_LEVEL_INFO, LOG_MODLE_NAME, "StateM start running");

	//create_timer();
	//init_timer();

	while (1)
	{
		sleep(3);

		/* 1.有数据接收则处理，否则挂起 */
		GET_SIGNAL_B(STATE_RCV_NOTIFY);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM get signal success");

		/* 2.获取json数据 */
		GET_JSON_STRUCT(STATECFG_JSON_STRUCT, (void *)&STATEM_JSON_INFO);
		LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM get json struct success");

		/* 3.读文件 */
		ret = StateM_ReadJFile(STATEM_STATEFILE_NAME);
		if (ret == STATEM_FALSE)
			continue;
		else
		{
			LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM Read File %s success", STATEM_STATEFILE_NAME);
			/* 4.解析，修改 */
			ret = StateM_ChgJFile(STATEM_KEYID);
			if (ret == STATEM_SUCCESS)
			{
				LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM chg %s struct success", STATEM_STATEFILE_NAME);
				/* 5.写文件加锁 */
				GET_SIGNAL_B(STATE_JSON_FILE);
				ret = StateM_WriteJFile(STATEM_STATEFILE_NAME, STATEM_JSON_FILE);
				SET_SIGNAL_B(STATE_JSON_FILE);
				if (ret == STATEM_SUCCESS)
					LogPrint(LOG_LEVEL_DEBUG, LOG_MODLE_NAME, "StateM Write file %s success", STATEM_STATEFILE_NAME);
			}
		}
	}
	timer_delete(timeid);
}
