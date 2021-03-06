#include "GPS.h"
#include "qxwz_sdk.h"
#include "Common.h"
#include "general_config.h"

#define DEBUG_PRINT 0
#define DEMO_LOG(fmt, ...)  printf("[DEMO]"fmt, ##__VA_ARGS__)
#define RTKConfigPath   "/mnt/APP/Config/obu/vds/VDSCfg.json"
#define LOG_MODLE_NAME           "GPS"

char acGpsName[50];
char acGpsName_W[50];

#define GPS_DATA 5003
pthread_mutex_t g_mutex_GpsData;
//接收数据线程循环控制变量
static volatile uint8_t i_serial_open = 0;

//组合接收数据接收数据缓存buf 及接收数据长度
char g_acRecvGPSDataBuf[512];
int g_nRecvGPSDataBufSize = 0;

//GPS串口句柄
int g_nGpsfd;
int g_nGps_W_fd;
//GPS数据全局变量，暂存当前提取的GPS数据。
GpsLocation g_GpsLocat;

//保存最后一个当前速度不为0的行驶方向值
int g_nlstBearing_RTK = 0;
//保存最后一个当前速度不为0的行驶Lat值
int g_nlstLat = 0;
//保存最后一个当前速度不为0的行驶Long值
int g_nlstLong = 0;

char DATA[512];
#define SHARE_MAXNUM 5
typedef struct _WriteData
{
	char In;
	char Out;
	char WriteBuf[SHARE_MAXNUM][2048];
	int WriteLen[SHARE_MAXNUM];
} tWriteData;
  
tWriteData g_tWriteData;
tWriteData g_tWriteData_DDS;
int RtcmDataSource = 0;
//static qxwz_uint32_t glob_flag = 0;
//static qxwz_uint64_t glob_ts = 0;

static qxwz_uint32_t sdk_auth_flag = 0;
static qxwz_uint32_t sdk_start_flag = 0;
qxwz_sdk_cap_info_t sdk_cap_info =
{ 0 };

//文件存储
int GPSfileFlag = 1;
FILE *fpGPSc = NULL; 

static __inline uint64_t RTK_timestamp_now(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return  (uint64_t)tv.tv_sec * 1000 +  (uint64_t)tv.tv_usec/1000;
}

static qxwz_void_t demo_show_caps(qxwz_sdk_cap_info_t *cap_info)
{
	qxwz_int32_t loop = 0;

	DEMO_LOG("total capabilities: %d\n", cap_info->caps_num);
	for (loop = 0; loop < cap_info->caps_num; ++loop)
	{
		DEMO_LOG(
				"idx: %d, cap_id: %u, state: %d, act_method: %d, expire_time: %llu\n",
				loop + 1, cap_info->caps[loop].cap_id,
				cap_info->caps[loop].state, cap_info->caps[loop].act_method,
				cap_info->caps[loop].expire_time);
	}
}

static qxwz_void_t demo_on_auth(qxwz_int32_t status_code,
		qxwz_sdk_cap_info_t *cap_info)
{
	if (status_code == QXWZ_SDK_STAT_AUTH_SUCC)
	{
		sdk_auth_flag = 1;
		sdk_cap_info = *cap_info;
		demo_show_caps(cap_info);
	} else
	{
		DEMO_LOG("auth failed, code=%d\n", status_code);
		if (status_code == -101)
		{
//			qxwz_sdk_init(&sdk_config);
			qxwz_sdk_auth();
		}
	}
}

static qxwz_void_t demo_on_start(qxwz_int32_t status_code, qxwz_uint32_t cap_id)
{
	DEMO_LOG("on start cap:status_code=%d, cap_id=%d\n", status_code, cap_id);
	sdk_start_flag = 1;
}

static qxwz_void_t demo_on_status(int code)
{
	DEMO_LOG(" on status code: %d\n", code);
}

static qxwz_void_t demo_on_data(qxwz_uint32_t type, const qxwz_void_t *data,
		qxwz_uint32_t len)
{
	// DEMO_LOG(" on data: %d, ptr: %p, len: %d\n", type, data, len);

	switch (type)
	{
	case QXWZ_SDK_DATA_TYPE_RAW_NOSR:
		DEMO_LOG("QXWZ_SDK_DATA_TYPE_RAW_NOSR\n");
		if (len < 1024)
		{
			memcpy(&g_tWriteData.WriteBuf[g_tWriteData.In][0], data, len);
			g_tWriteData.WriteLen[g_tWriteData.In] = len;
			g_tWriteData.In++;
			g_tWriteData.In %= SHARE_MAXNUM;
		}
		break;
	default:
		DEMO_LOG("unknown type: %d\n", type);
	}
}

//DDS 
void Recv_DDS_Data_CallBack(char *data,int len)
{
	memcpy(&g_tWriteData_DDS.WriteBuf[g_tWriteData.In][0], data, len);
	g_tWriteData_DDS.WriteLen[g_tWriteData.In] = len;
	g_tWriteData_DDS.In++;
	g_tWriteData_DDS.In %= SHARE_MAXNUM;
}
 void WriteRtcmDataProcessing()
 {
	 	int send_ret;
	 	if (g_tWriteData.Out != g_tWriteData.In)
		{
			//以读写O_RDWR方式
			g_nGps_W_fd = open(acGpsName_W, O_RDWR);
			if (g_nGps_W_fd == -1)
			{
				perror("Serial open error\n");
			} else
			{
				send_ret = write(g_nGps_W_fd,
						g_tWriteData.WriteBuf[g_tWriteData.Out],
						g_tWriteData.WriteLen[g_tWriteData.Out]);
				if (send_ret != g_tWriteData.WriteLen[g_tWriteData.Out])
				{
#if DEBUG_PRINT
					printf("write error, send_ret = %d\n", send_ret);
#endif
				} else
				{
#if DEBUG_PRINT
					printf("write succeed, send_ret = %d\n", send_ret);
#endif
				}
				close(g_nGps_W_fd);
			}
			g_nGps_W_fd = 0;

			g_tWriteData.Out = g_tWriteData.In;
		}

		if (sdk_auth_flag > 0)
		{
			sdk_auth_flag = 0;
			if (sdk_cap_info.caps_num > 0)
			{
				qxwz_sdk_start(QXWZ_SDK_CAP_ID_NOSR); /* start NOSR capability */
			}
		}
 }

 void WriteDDSRtcmDataProcessing()
 {
	 	int send_ret;
	 	if (g_tWriteData_DDS.Out != g_tWriteData_DDS.In)
		{
			//以读写O_RDWR方式
			g_nGps_W_fd = open(acGpsName_W, O_RDWR);
			if (g_nGps_W_fd == -1)
			{
				perror("Serial open error\n");
			} else
			{
				send_ret = write(g_nGps_W_fd,
						g_tWriteData_DDS.WriteBuf[g_tWriteData_DDS.Out],
						g_tWriteData_DDS.WriteLen[g_tWriteData_DDS.Out]);
				if (send_ret != g_tWriteData_DDS.WriteLen[g_tWriteData_DDS.Out])
				{
#if DEBUG_PRINT
					printf("write error, send_ret = %d\n", send_ret);
#endif
				} else
				{
#if DEBUG_PRINT
					printf("write succeed, send_ret = %d\n", send_ret);
#endif
				}
				close(g_nGps_W_fd);
			}
			g_nGps_W_fd = 0;

			g_tWriteData_DDS.Out = g_tWriteData_DDS.In;
		}
 }

void Thread_WriteRtcmDate(void *p)
{
	while (1)
	{
		
		usleep(100 * 1000); /* 100ms */
		if(RtcmDataSource == 1)
		{
			WriteDDSRtcmDataProcessing();
		}
		else
		{
			WriteRtcmDataProcessing();
		}
	}
}

/******************************************************************
 * 函数名称：	double Degree2Decimal(double l_dInput)
 * 功能描述：将直接获取的GPS度数值（度分秒格式），转化为小数值（度数小数格式）
 * 参数列表：
 *			double l_dInput 需要转换的GPS经/纬度值（度分秒格式）
 * 返回结果：
 *			double 转换后的GPS经/纬度（度数小数格式）
 ******************************************************************/
double Degree2Decimal(double l_dInput)
{
	double l_dOut = 0;
	double l_dTemp1 = (int) (l_dInput / 100);
	double l_dTemp2 = l_dInput - l_dTemp1 * 100;
	l_dTemp2 = l_dTemp2 / 60;
	l_dOut = l_dTemp1 + l_dTemp2;
	return l_dOut;
}

/*******************************************************************
 * 函数名称：	void ParamInit_GPSData()
 * 功能描述：保证GPS数据互斥操作的信号量的初始化
 * 参数列表：
 *			无
 * 返回结果：
 *			无
 *******************************************************************/

///**
// * GPS模块参数配置
// * 函数名称：int GPS_SetParam(char *p_PortName, int nBaud, int nAdjustMode)
// * 函数功能：包括串口名称，波特率，是否进行差分操作的使能开关的设置，或其它相关参数的设置；
// * 参数说明：
// * 		输入参数：char *p_PortName,GPS的串口号，int nBaud GPS串口波特率, int nAdjustMode 查分模式
// *		输出参数：无
// * 函数返回值：执行状态，0 执行成功，非0 执行失败
// * */
//int GPS_SetParam(char *p_PortName, int nBaud, int nAdjustMode)
//{
//	return 0;
//}
/******************************************************************
 * 函数名称：	int GPS_DataProcess(nint8_t *buf, uint32_t len)
 * 功能描述：	对串口获取的GPS数据进行截取完整帧处理，保证当前操作数据是$开头，\n或者\r结束。
 * 参数列表：	nint8_t *buf 接收到的数据缓存, uint32_t len 接收到的数据长度
 * 返回结果：	0--成功接收一组完整帧，非0--未成功解析到一组完整帧
 ******************************************************************/
int GPS_DataProcess(nint8_t *buf, uint32_t len)
{
	uint32_t i = 0;
	uint8_t *pBuf = (uint8_t *) buf;
	for (i = 0; i < len; i++)
	{
		if (g_nRecvGPSDataBufSize == 0)
		{
			if (pBuf[i] == '$')
			{
				g_acRecvGPSDataBuf[g_nRecvGPSDataBufSize++] = pBuf[i];
			} else
				g_nRecvGPSDataBufSize = 0;
		} else if ((g_nRecvGPSDataBufSize > 0) && (g_nRecvGPSDataBufSize < 200))
		{
		
			if (pBuf[i] == '$')
			{
				g_nRecvGPSDataBufSize = 0;
				g_acRecvGPSDataBuf[g_nRecvGPSDataBufSize++] = pBuf[i];
				continue;
			}
			g_acRecvGPSDataBuf[g_nRecvGPSDataBufSize++] = pBuf[i];
			if ((g_acRecvGPSDataBuf[g_nRecvGPSDataBufSize - 1] == '\n')
					|| (g_acRecvGPSDataBuf[g_nRecvGPSDataBufSize - 1] == '\r'))
			{

				GPS_ExtractData(g_acRecvGPSDataBuf, g_nRecvGPSDataBufSize);
				memset(g_acRecvGPSDataBuf, 0x00, sizeof(g_acRecvGPSDataBuf));
				g_nRecvGPSDataBufSize = 0;
			} else if (g_nRecvGPSDataBufSize >= 200)
			{
				g_nRecvGPSDataBufSize = 0;
			}
		}
	}
	return -1;
}
/******************************************************************
 * 函数名称：	int GPS_ExtractData(nint8_t *buf, uint32_t len)
 * 功能描述：	对GPS完整帧进行解析，提取经纬度/海拔/方向/速度等参数，并保存至全局变量结构体中。
 * 参数列表：	nint8_t *buf GPS完整帧缓存, uint32_t len GPS完整帧数据长度
 * 返回结果：	0--数据帧解析成功，非0--数据帧解析失败
 ******************************************************************/
int GPS_ExtractData(nint8_t *buf, uint32_t len)
{
	double l_dTemp;
	char *Gpgga_Break_Data = NULL;
	int i = 0;
    int State = 0;
	double UTCtime = 0;
	double Lat = 0;
	double Lon = 0;
	double Alti = 0;
         //文件存储
	if (GPSfileFlag)
	{
		fpGPSc = fopen("GPSc.txt","w");
	    if (fpGPSc == NULL)
	    {
	       printf("Write fpGPSc faild!");
	    }
		GPSfileFlag = 0;
	}
 
	if ((buf[1] == 'G') && (buf[3] == 'G') && (buf[4] == 'G')
			&& (buf[5] == 'A')) //GPGGA
	{
		GNSS_timestamp = RTK_timestamp_now();
		g_GpsLocat.timestamp = GNSS_timestamp;
		if (1 == 1)
		{

			//*********************Up Load GAA Data	***************
			while (1)
			{
				DATA[i] = g_acRecvGPSDataBuf[i];
				i++;
				if (g_acRecvGPSDataBuf[i] == '\n')
					break;
				if (g_acRecvGPSDataBuf[i] == '\0')
					break;
				if (g_acRecvGPSDataBuf[i] == '\r')
					break;
			}
			DATA[i++] = '\r';
			DATA[i++] = '\n';
			DATA[i++] = 0;

			qxwz_sdk_upload_gga(DATA, strlen(DATA));

			//*********************Up Load GAA Data	***************
		}
#if DEBUG_PRINT
			printf("*******************************************************\n");
			printf("%s\n", DATA);
#endif
//		printf("buf = %s\n",buf);
		Gpgga_Break_Data = strtok(buf, ",");		//GPGGA
		if (Gpgga_Break_Data == NULL)
		{
			return -1;
		}
//		printf("1\n");

		Gpgga_Break_Data = strtok(NULL, ",");		//<1> UTC 时间，格式为hhmmss.sss；
		if (Gpgga_Break_Data == NULL)
		{
			return -1;
		}
        l_dTemp = atof(Gpgga_Break_Data);
		UTCtime = l_dTemp;
        // printf("g_GpsLocat.utctime = %f",g_GpsLocat.utctime);

//		printf("12\n");
//		g_GpsLocat.timestamp = (int) atof(Gpgga_Break_Data);
		Gpgga_Break_Data = strtok(NULL, ",");//<2> 纬度，格式为ddmm.mmmm(第一位是零也将传送)；
		if (Gpgga_Break_Data == NULL)
		{
			return -1;
		}
//		printf("13\n");
		if (5 > strlen(Gpgga_Break_Data))
		{
			pthread_mutex_lock(&g_mutex_GpsData);
			g_GpsLocat.altitude = 666;
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
//		printf("14\n");
		pthread_mutex_lock(&g_mutex_GpsData);
		l_dTemp = atof(Gpgga_Break_Data);
		l_dTemp = Degree2Decimal(l_dTemp);
//		if ((fabs(l_dTemp - 40) > 10)) {
////			printf("GPGGA : %s\n" , buf);
////			printf("latitude %d longitude %d",g_GpsLocat.latitude,g_GpsLocat.longitude);
//		} else
		{
			g_GpsLocat.latitude = l_dTemp * 10000000;
            
			//记录有速度时的最后一个有效方向值
			if ((g_GpsLocat.speed > 0.5) || (g_nlstLat == 0))
				g_nlstLat = g_GpsLocat.latitude;
			//当当前速度为0时，取最后一个有效方向值为当前方向值-----实现停车后保持当前车头方向。
			if (g_GpsLocat.speed <= 0.5)
				g_GpsLocat.latitude = g_nlstLat;
		}
      	Lat = l_dTemp;//printf("lon  %lf",l_dTemp);

		Gpgga_Break_Data = strtok(NULL, ",");		//<3> 纬度半球，N 或S(北纬或南纬)
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
//		printf("15\n");
		Gpgga_Break_Data = strtok(NULL, ",");//<4> 经度，格式为dddmm.mmmm(第一位零也将传送)；
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
		l_dTemp = atof(Gpgga_Break_Data);
		l_dTemp = Degree2Decimal(l_dTemp);
//		if ((fabs(l_dTemp - 116) > 10)) {
////			printf("GPGGA : %s\n" , buf);
////			printf("latitude %d longitude %d",g_GpsLocat.latitude,g_GpsLocat.longitude);
//		}
//		else
		{
			g_GpsLocat.longitude = l_dTemp * 10000000;
			
			//记录有速度时的最后一个有效方向值
			if ((g_GpsLocat.speed > 0.5) || (g_nlstLong == 0))
				g_nlstLong = g_GpsLocat.longitude;
			//当当前速度为0时，取最后一个有效方向值为当前方向值-----实现停车后保持当前车头方向。
			if (g_GpsLocat.speed <= 0.5)
				g_GpsLocat.longitude = g_nlstLong;
   
		}
		Lon = l_dTemp;  //printf("lat  %lf\n",l_dTemp);
		//printf("******Lon  %lf\n",Lon);
		Gpgga_Break_Data = strtok(NULL, ",");		//<5> 经度半球，E 或W(东经或西经)
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
		Gpgga_Break_Data = strtok(NULL, ",");		//<6> 定位质量指示，0=定位无效，1=定位有效； 5
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
        State = atof(Gpgga_Break_Data);
		switch (State)
		{
			case 1:	g_GpsLocat.CurrentGpsState	= 0x10;	break;
			case 2:	g_GpsLocat.CurrentGpsState	= 0x20;	break;
			case 4:	g_GpsLocat.CurrentGpsState	= 0x60;	break;
			case 5:	g_GpsLocat.CurrentGpsState	= 0x50;	break;
			default:break;
		}
        // LogPrint(LOG_LEVEL_NOTICE, "GPS Model State", "Current GPS State is : %d \n",g_GpsLocat.CurrentGpsState);
		if(State == 4)
		{
			GnssLedState =  Green_LED_Twinking;
		}
		else
		{
			GnssLedState =  Green_LED_FastTwinking;
		}
		
		Gpgga_Break_Data = strtok(NULL, ",");		//<7>使用卫星数量，从00到12(第一个零也将传送)
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
		Gpgga_Break_Data = strtok(NULL, ",");		//<8>水平精确度，0.5到99.9
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
		l_dTemp = atof(Gpgga_Break_Data);
		g_GpsLocat.accuracy = l_dTemp;
		Gpgga_Break_Data = strtok(NULL, ",");//<9>天线离海平面的高度，-9999.9到9999.9米M指单位米
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}

		l_dTemp = atof(Gpgga_Break_Data);
		//printf("alt  %lf",l_dTemp);
		Alti = l_dTemp;
		g_GpsLocat.altitude = (int) (l_dTemp * 10);
		pthread_mutex_unlock(&g_mutex_GpsData);
	}
		if ((buf[1] == 'G') && (buf[3] == 'R') && (buf[4] == 'M')
			&& (buf[5] == 'C'))
		{
#if DEBUG_PRINT
		printf("GPRMC BEGIN\n");
#endif
		Gpgga_Break_Data = strtok(buf, ",");	//GPRMC
		if (Gpgga_Break_Data == NULL)
		{
			return -1;
		}
		Gpgga_Break_Data = strtok(NULL, ",");	//<1> UTC 时间，hhmmss(时分秒)格式
		if (Gpgga_Break_Data == NULL)
		{
			return -1;
		}
		Gpgga_Break_Data = strtok(NULL, ",");	//<2> 定位状态，A=有效定位，V=无效定位
		if (Gpgga_Break_Data == NULL)
		{
			return -1;
		}
		if (Gpgga_Break_Data[0] == 'V')
		{
			fflush(stdout);
			return -2;
		}
		pthread_mutex_lock(&g_mutex_GpsData);
		Gpgga_Break_Data = strtok(NULL, ",");//<3>纬度ddmm.mmmm(度分)格式(前面的0也将被传输)
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
		l_dTemp = atof(Gpgga_Break_Data);
		l_dTemp = Degree2Decimal(l_dTemp);
		// if ((fabs(l_dTemp - 40) > 10))
		// {
		// 	pthread_mutex_unlock(&g_mutex_GpsData);
		// 	return -1;
		// }
		Gpgga_Break_Data = strtok(NULL, ",");	//<4> 纬度半球N(北半球)或S(南半球)
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
		Gpgga_Break_Data = strtok(NULL, ",");//<5>经度dddmm.mmmm(度分)格式(前面的0也将被传输)
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
		l_dTemp = atof(Gpgga_Break_Data);
		l_dTemp = Degree2Decimal(l_dTemp);
		// if ((fabs(l_dTemp - 116) > 10))
		// {
		// 	pthread_mutex_unlock(&g_mutex_GpsData);
		// 	return -1;
		// }

		Gpgga_Break_Data = strtok(NULL, ",");	//<6> 经度半球E(东经)或W(西经)
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
		Gpgga_Break_Data = strtok(NULL, ",");//<7>地面速率(000.0~999.9节，前面的0也将被传输)
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
		// printf("Speed is : %s\n",Gpgga_Break_Data);
		l_dTemp = atof(Gpgga_Break_Data);
		g_GpsLocat.speed = (l_dTemp) * (float) 0.514;//(l_dTemp / 2)此处需要转换为节，若值为1则约为0.514m/s
		Gpgga_Break_Data = strtok(NULL, ",");//<8>地面航向(000.0~359.9度，以真北为参考基准，前面的0也将被传输)
		// printf("Heading is : %s\n",Gpgga_Break_Data);
		if (Gpgga_Break_Data == NULL)
		{
			pthread_mutex_unlock(&g_mutex_GpsData);
			return -1;
		}
		g_GpsLocat.heading = atof(Gpgga_Break_Data);
		if (g_GpsLocat.heading > 1000)
			g_GpsLocat.heading = 0;
		//记录有速度时的最后一个有效方向值
		if (g_GpsLocat.speed > 1)
			g_nlstBearing_RTK = g_GpsLocat.heading;
		//当当前速度为0时，取最后一个有效方向值为当前方向值-----实现停车后保持当前车头方向。
		if (g_GpsLocat.speed <= 1)
			g_GpsLocat.heading = g_nlstBearing_RTK;

		pthread_mutex_unlock(&g_mutex_GpsData);
#if DEBUG_PRINT
		printf("GPRMC ----- %s\n",buf);
#endif
#if DEBUG_PRINT
		printf("GPRMC END\n");
#endif

#if DEBUG_PRINT
	Lat = (double)(g_GpsLocat.latitude)/10000000;
	Lon = (double)(g_GpsLocat.longitude)/10000000;
	Alti = (double)(g_GpsLocat.altitude)/10;
		if ( State == 5)
		{
			printf("state = %d\n",State);
			LogPrint(LOG_LEVEL_NOTICE, "GPSRTK_Statistics_E5",
        "   Time:%lf Lat:%0.7lf Long:%0.7lf ALti:%0.2lf Speed:%lf Bearing:%d.",
        UTCtime,
        Lat,
        Lon,
		Alti,
        g_GpsLocat.speed,
		g_GpsLocat.heading);
		}
		else if ( State == 4 )
		{
			LogPrint(LOG_LEVEL_NOTICE, "GPSRTK_Statistics_E4",
        "   Time:%lf Lat:%0.7lf Long:%0.7lf ALti:%0.2lf Speed:%lf Bearing:%d.",
        UTCtime,
        Lat,
        Lon,
		Alti,
        g_GpsLocat.speed,
		g_GpsLocat.heading);
		}
		else if ( State == 2 )
		{
			LogPrint(LOG_LEVEL_NOTICE, "GPSRTK_Statistics_E2",
        "   Time:%lf Lat:%0.7lf Long:%0.7lf ALti:%0.2lf Speed:%lf Bearing:%d.",
        UTCtime,
        Lat,
        Lon,
		Alti,
        g_GpsLocat.speed,
		g_GpsLocat.heading);
		}
		else if ( State == 1 )
		{
			LogPrint(LOG_LEVEL_NOTICE, "GPSRTK_Statistics_E1",
        "   Time:%lf Lat:%0.7lf Long:%0.7lf ALti:%0.2lf Speed:%lf Bearing:%d.",
        UTCtime,
        Lat,
        Lon,
		Alti,
        g_GpsLocat.speed,
		g_GpsLocat.heading);
		}
		else 
		{
			//do
		}

   
#endif
	}
	return 0;
}
/******************************************************************
 * 函数名称：	void Thread_RecvGPSData(void *p)
 * 功能描述：	读取GPS串口数据线程函数
 * 参数列表：
 *			p	--	传入主界面窗口指针
 * 返回结果：	void
 ******************************************************************/
void Thread_RecvGPSData(void *p)
{
	char buff[512];
	i_serial_open = 1;
	int nread = 0;
	while (i_serial_open)
	{
		nread = read(g_nGpsfd, &buff, 512);
		if (nread > 0)
		{
			if (GPS_DataProcess(buff, nread) == 0)	//收到正确数据帧发送串口事件
			{
				//do nothing
			}
		}/* end if(rxlen > 0) */
		memset(buff, 0x00, sizeof(buff));
		nread = 0;
	}/* end while(i_serial_open) */
	fclose(fpGPSc);
}

/********************************************************************
 * GPS模块初始化
 * 函数名称：int GPS_Open()
 * 函数功能：打开获取GPS数据的串口，并开启接收GPS数据线程；
 * 参数说明：无
 * 函数返回值：执行状态，0 执行成功，非0 执行失败
 * 注意，GPS串口名称在/etc/V2X_APP.ini文件中的[GPSUtil]-GPSName中获取，
 * 如果没有该字段或者配置文件，请手动添加。
 *******************************************************************/
int GPS_RTK_Open()
{
	char appkey[50];
	char appSecret[100];
	char dev_id[50];
	char dev_type[50];
	int ret = 0;
	pthread_t serialThread;
	int iRetCode = 0;
	int  ConfigVal = 0;
	memset(acGpsName, 0x00, sizeof(acGpsName));
	memset(acGpsName_W, 0x00, sizeof(acGpsName_W));
	memset(&g_tWriteData, 0x00, sizeof(g_tWriteData));
//初始化互斥信号量
	pthread_mutex_init(&g_mutex_GpsData, NULL);

	system("stty -F /dev/ttymxc2 460800");

	system("stty -F /dev/ttymxc2 460800 raw -echo");
	if (!(GetConfigIntValue(RTKConfigPath, "QXWZ", "RtcmDataSource", &ConfigVal)))
	{
		RtcmDataSource = ConfigVal ;
		LogPrint(LOG_LEVEL_NOTICE, "GPS", "GPS Rtcm Data Source is: %d ",RtcmDataSource) ;
	}
//读取配置文件中GPS的串口号
	iRetCode = GetConfigStringValue(RTKConfigPath, "QXWZ", "GPSName",
			acGpsName);
	if (iRetCode)
	{
		printf("iRetCode1 : %d !\n", iRetCode);
		return ReError;
	}
	iRetCode = GetConfigStringValue(RTKConfigPath, "QXWZ", "GPSName_W",
			acGpsName_W);
	if (iRetCode)
	{
		printf("iRetCode2 : %d !\n", iRetCode);
		return ReError;
	}

	iRetCode = GetConfigStringValue(RTKConfigPath, "QXWZ", "AppKey",
			appkey);
	if (iRetCode)
	{
		printf("iRetCode3 : %d !\n", iRetCode);
		return ReError;
	}

	iRetCode = GetConfigStringValue(RTKConfigPath, "QXWZ", "AppSectet",
			appSecret);
	if (iRetCode)
	{
		printf("iRetCode4 : %d !\n", iRetCode);
		return ReError;
	}

	iRetCode = GetConfigStringValue(RTKConfigPath, "QXWZ", "Dev_id", dev_id);
	if (iRetCode)
	{
		printf("iRetCode5 : %d !\n", iRetCode);
		return ReError;
	}
	iRetCode = GetConfigStringValue(RTKConfigPath, "QXWZ", "Dev_type", dev_type);
	if (iRetCode)
	{
		printf("iRetCode6 : %d !\n", iRetCode);
		return ReError;
	}
	//以只读O_RDONLY方式
	g_nGpsfd = open(acGpsName, O_RDONLY);
	if (g_nGpsfd == -1)
	{
		perror("Serial open error\n");
		return ReError;
	} else
	{

	}
//创建串口线程
	ret = pthread_create(&serialThread, NULL,
			(void *(*)(void *)) Thread_RecvGPSData, NULL);
	if(ret != 0)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "GPS MsgRcv pthread creat error");
		return ReError;
	}
	qxwz_sdk_config_t sdk_config ={ 0 };
	sdk_config.key_type = QXWZ_SDK_KEY_TYPE_AK;
	strcpy(sdk_config.key, appkey);
	strcpy(sdk_config.secret, appSecret);
	strcpy(sdk_config.dev_id, dev_id);
	strcpy(sdk_config.dev_type, dev_type);

	sdk_config.status_cb = demo_on_status;
	sdk_config.data_cb = demo_on_data;
	sdk_config.auth_cb = demo_on_auth;
	sdk_config.start_cb = demo_on_start;

	printf("sdk_config.key = %s\n", sdk_config.key);
	printf("sdk_config.secret = %s\n", sdk_config.secret);
	printf("sdk_config.dev_id = %s\n", sdk_config.dev_id);
	printf("sdk_config.dev_type = %s\n", sdk_config.dev_type);

	struct timeval tval ={ 0 };
	gettimeofday(&tval, NULL);
	ret = qxwz_sdk_init(&sdk_config);
	if(ret != 0)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "GPS qxwz_sdk_init error");
		return ReError;
	}
	ret = qxwz_sdk_auth();
	if(ret != 0)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "GPS qxwz_sdk_auth error");
		return ReError;
	}
	pthread_t rtcm_sendGGAThread;
	pthread_create(&rtcm_sendGGAThread, NULL,
				(void *(*)(void *)) Thread_WriteRtcmDate, NULL);
	if(ret != 0)
	{
		LogPrint(LOG_LEVEL_ERR, LOG_MODLE_NAME, "GPS MsgRcv pthread creat error");
		return ReError;
	}	
	return RetTure;
}

/*******************************************************************
 * 获取当前GPS数据
 * 函数名称：int GPS_GetData(GpsLocation * fix)
 * 函数功能：读取当前最新的GPS数据，GPS数据格式按照指定的数据格式传出；
 * 参数说明：
 * 		输出参数：GpsLocation * fix 最新获取的GPS信息的指针
 * 函数返回值：执行状态，0 执行成功，非0 执行失败
 ******************************************************************/
int GPS_RTK_GetData(GpsLocation * fix)
{
	if (fix == NULL)
		return -1;
	pthread_mutex_lock(&g_mutex_GpsData);
	memcpy(&fix->latitude, &g_GpsLocat.latitude, sizeof(GpsLocation));
	pthread_mutex_unlock(&g_mutex_GpsData);
	return 0;
}
/*******************************************************************
 * 关闭GPS模块
 * 函数名称：int GPS_GetData()
 * 函数功能：关闭GPS数据获取模块，即关闭GPS串口，停止GPS数据接收线程，清空相关变量内容；
 * 参数说明：无
 * 函数返回值：执行状态，0 执行成功，非0 执行失败
 *******************************************************************/
int GPS_RTK_Close()
{
	i_serial_open = 0;
	if (g_nGpsfd > 0)
		close(g_nGpsfd);
	g_nGpsfd = 0;
	qxwz_sdk_stop(QXWZ_SDK_CAP_ID_NOSR); /* stop NOSR capability */

	qxwz_sdk_cleanup();
	return 0;
}

