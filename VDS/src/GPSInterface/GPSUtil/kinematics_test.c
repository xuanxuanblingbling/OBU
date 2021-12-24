/*
 *  Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <glib.h>
#include "general_config.h"

#include <tunnel_mode.h>
#include <v2x_kinematics_api.h>
#include "./../Include/wj_log.h"

// NaN representation in csv
#define NaN " "

// Number of microseconds that a kinematics fix is valid before timing out
#define KINEMATICS_TIMEOUT (1000000)

#define errExit(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int gVerbosity = 1;
extern GpsLocation g_GpsLocat;

long long gReportInterval_ns = 1000000000;
double gdReportInterval_sec = 1;
FILE *fpkinematics_test = NULL; 

#include "GPS.h"


//GPS数据全局变量，暂存当前提取的GPS数据。
pthread_mutex_t g_mutex_GpsData;

//保存最后一个当前速度不为0的行驶方向值
int g_nlstBearing_AG15 = 0;

int g_nGpsTypeFlag = 0;  // 0--gps, 1--m39
GpsLocation g_GpsLocat_m39;

typedef struct _kinematics_data_t
{
	bool inuse;
	bool has_fix;
	bool initialized;
	uint64_t timestamp;
	v2x_location_fix_t *latest_fix;
} kinematics_data_t;

// Location data relevant to acme messages
typedef struct _location_data_t
{
	bool isvalid;
	v2x_fix_mode_t fix_mode;
	double latitude;
	double longitude;
	double altitude;
	uint32_t qty_SV_used;
	bool has_SemiMajorAxisAccuracy;
	double SemiMajorAxisAccuracy;
	bool has_heading;
	double heading;
	bool has_velocity;
	double velocity;
} location_data_t;

// Timer for kinematics initialization retry
static timer_t init_kinematics_timer;
static int init_kinematics_timer_signo;

// Kinematics fields
static v2x_kinematics_handle_t h_v2x = V2X_KINEMATICS_HANDLE_BAD;
static bool v2x_kinematics_initialized = false;
static kinematics_data_t g_kinematics_data =
{ .inuse = false, .has_fix = false };

// Default IP for kinematics server
char server_ip_str[20] = "192.168.100.1";

/*******************************************************************************
 * return current time stamp in microseconds
 * @return long long
 ******************************************************************************/
static __inline uint64_t timestamp_now(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return  (uint64_t)tv.tv_sec * 1000 +  (uint64_t)tv.tv_usec/1000;
}

/*
 * Checks if latest fix is valid and copies a subset of location fields into the location
 * data struct. These fields include latitude, longitude, altitude, fix_mode,
 * qty_SV_used, heading, velocity, and SemiMajorAxisAccuracy.
 * Returns true if data copied successfully.
 *
 * @return bool
 */
bool load_location_data(location_data_t *location,
		kinematics_data_t *kinematics_data)
{
	location->isvalid = false;
	// Copy the kinematics data into the msg
	if (kinematics_data->has_fix)
	{
		if (timestamp_now() - kinematics_data->timestamp < KINEMATICS_TIMEOUT)
		{
			location->isvalid = true;
			location->latitude = kinematics_data->latest_fix->latitude;
			location->longitude = kinematics_data->latest_fix->longitude;
			location->altitude = kinematics_data->latest_fix->altitude;
			location->fix_mode = kinematics_data->latest_fix->fix_mode;
			location->qty_SV_used = kinematics_data->latest_fix->qty_SV_used;
			if (kinematics_data->latest_fix->has_heading)
			{
				location->has_heading = true;
				location->heading = kinematics_data->latest_fix->heading;
			}
			if (kinematics_data->latest_fix->has_velocity)
			{
				location->has_velocity = true;
				location->velocity = kinematics_data->latest_fix->velocity;
			}
			if (kinematics_data->latest_fix->has_SemiMajorAxisAccuracy)
			{
				location->has_SemiMajorAxisAccuracy = true;
				location->SemiMajorAxisAccuracy =
						kinematics_data->latest_fix->SemiMajorAxisAccuracy;
			}
		}
	}
	return location->isvalid;
}

static void v2x_kinematics_init_cb(v2x_status_enum_type status, void *context)
{
	if (V2X_STATUS_SUCCESS == status)
	{
		if (gVerbosity > 2)
		{
			printf("v2x callback - initialized successfully. \n");
		}
		v2x_kinematics_initialized = true;
	}
}

static void v2x_kinematics_newfix_cb(v2x_location_fix_t *new_fix, void *context)
{
	static uint32_t fix_count = 0u;
	// Don't do anything if SVs used 0.
	if (V2X_GNSS_MODE_NO_FIX == new_fix->fix_mode)
	{
		return;
	}
	g_kinematics_data.has_fix = true;
	g_kinematics_data.latest_fix = new_fix;
	g_kinematics_data.timestamp = timestamp_now();
	GNSS_timestamp = timestamp_now();
	pthread_mutex_lock(&g_mutex_GpsData);
	g_GpsLocat.latitude = g_kinematics_data.latest_fix->latitude * 10000000;
	g_GpsLocat.longitude = g_kinematics_data.latest_fix->longitude * 10000000;
	g_GpsLocat.altitude = g_kinematics_data.latest_fix->altitude * 10;
	g_GpsLocat.speed = g_kinematics_data.latest_fix->velocity;
	g_GpsLocat.heading = g_kinematics_data.latest_fix->heading;
	g_GpsLocat.accuracy = new_fix->SemiMajorAxisAccuracy;
	g_GpsLocat.timestamp =  GNSS_timestamp ;
	//记录有速度时的最后一个有效方向值
	if (g_GpsLocat.speed > 1)
		g_nlstBearing_AG15 = g_GpsLocat.heading;
	//当当前速度为0时，取最后一个有效方向值为当前方向值-----实现停车后保持当前车头方向。
	if (g_GpsLocat.speed <= 2)
		g_GpsLocat.heading = g_nlstBearing_AG15;
    double Lat = (double)(g_GpsLocat.latitude)/10000000;
	double Lon = (double)(g_GpsLocat.longitude)/10000000;
	double Alti = (double)(g_GpsLocat.altitude)/10;
	// printf("9999999 is : %llf\n",g_GpsLocat.heading);
	pthread_mutex_unlock(&g_mutex_GpsData);
}

static void v2x_kinematics_final_cb(v2x_status_enum_type status, void *context)
{
	if (gVerbosity > 3)
	{
		printf("v2x final callback, status=%d\n", status);
	}
}

/*
 * Try to initialize the kinematics client, called on timer trigger.
 * If initialized, register the callback.  Disarm timer if initialization
 * is successful.
 */
static void try_kinematics_initialize(int signum)
{
	v2x_init_t v2x_init;
	v2x_init.log_level_mask = 0xffffffff;
	struct itimerspec its;

	if (gVerbosity)
	{
		printf("Kinematics server IP address is %s\n", server_ip_str);
	}

	snprintf(v2x_init.server_ip_addr, sizeof(v2x_init.server_ip_addr), "%s",
			server_ip_str);

	static uint32_t retryCount = 0u;
	if (!v2x_kinematics_initialized)
	{ 
		if (V2X_KINEMATICS_HANDLE_BAD != h_v2x)
		{
			v2x_kinematics_final(h_v2x, &v2x_kinematics_final_cb, NULL);
		}
		if (retryCount)
		{
			if (gVerbosity)
			{
				printf("Retrying ... \n");
			}
		} else
		{
			if (gVerbosity)
			{
				printf("Initializing Kinematics API.\n");
			}
		}
		h_v2x = v2x_kinematics_init(&v2x_init, v2x_kinematics_init_cb, NULL);
		++retryCount;
	}

	if (v2x_kinematics_initialized)
	{
		// The Kinematics API has been initialized
		if (gVerbosity)
		{
			printf("Kinematics API initialization successful.\n");
		}
		// Register the new_fix listener
		if (V2X_STATUS_SUCCESS
				== v2x_kinematics_register_listener(h_v2x,
						v2x_kinematics_newfix_cb, NULL))
		{
			if (gVerbosity)
			{
				printf("Kinematics listener registration successful.\n");
			}
			// Disarm timer
			its.it_value.tv_sec = 0;
			its.it_value.tv_nsec = 0;
			its.it_interval.tv_nsec = 0;
			its.it_interval.tv_sec = 0;
			if (timer_settime(init_kinematics_timer, 0, &its, NULL) == -1)
			{
				errExit("disarm_timer");
			}
		} else
		{
			if (gVerbosity)
			{
				printf("Kinematics listener registration unsuccessful.\n");
			}
		}
	}
}

/*
 * Setup initializing of the kinematics client.  Starts a timer to trigger intitialization attempts,
 * will retry until successful completion.
 */
void start_kinematics()
{
	/* Initialize the kinematics API */
	struct itimerspec its;
	struct sigevent sev;
	// Setup up the timer and signal
	init_kinematics_timer_signo = SIGUSR2;
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = init_kinematics_timer_signo;
	sev.sigev_value.sival_ptr = &init_kinematics_timer;
	if (timer_create(CLOCK_REALTIME, &sev, &init_kinematics_timer) == -1)
	{
		errExit("timer_create");
	}
	signal(init_kinematics_timer_signo, try_kinematics_initialize);

	/* Start the timer */
	its.it_value.tv_sec = 1;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = its.it_value.tv_sec;
	its.it_interval.tv_nsec = its.it_value.tv_nsec;

	if (timer_settime(init_kinematics_timer, 0, &its, NULL) == -1)
	{
		errExit("arm_timer");
	}

	try_kinematics_initialize(0); // call once now to print header and initialze delta timers
}
int g_nGpsfd = 0;
int GPS_AG15_Open()
{
	GnssLedState =  Green_LED_FastTwinking;
	start_kinematics();
	g_nGpsfd = 10;
	return 0;
}
/*******************************************************************
 * 获取当前GPS数据
 * 函数名称：int GPS_GetData(GpsLocation * fix)
 * 函数功能：读取当前最新的GPS数据，GPS数据格式按照指定的数据格式传出；
 * 参数说明：
 * 		输出参数：GpsLocation * fix 最新获取的GPS信息的指针
 * 函数返回值：执行状态，0 执行成功，非0 执行失败
 ******************************************************************/
int GPS_Ag15_GetData(GpsLocation * fix)  //GpsLocation
{
	int ret = 0 ;

	if (fix == NULL)
		return -1;
	pthread_mutex_lock(&g_mutex_GpsData);
	if (g_nGpsTypeFlag == 0)
		memcpy(&(fix->latitude), &g_GpsLocat.latitude, sizeof(GpsLocation));
	if (g_nGpsTypeFlag == 1)
		memcpy(&(fix->latitude), &g_GpsLocat_m39.latitude, sizeof(GpsLocation));
	pthread_mutex_unlock(&g_mutex_GpsData);
    
	return ret;
}

int GPS_SetFlag(int Flag)
{
	g_nGpsTypeFlag = Flag;
	return 0;
}

/*******************************************************************
 * 关闭GPS模块
 * 函数名称：int GPS_GetData()
 * 函数功能：关闭GPS数据获取模块，即关闭GPS串口，停止GPS数据接收线程，清空相关变量内容；
 * 参数说明：无
 * 函数返回值：执行状态，0 执行成功，非0 执行失败
 *******************************************************************/
int GPS_AG15_Close()
{
	g_nGpsfd = 0;
	return 0;
}
