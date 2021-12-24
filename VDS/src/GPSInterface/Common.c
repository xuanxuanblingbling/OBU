/*
 * Common.c
 *
 *  Created on: May 25, 2018
 *      Author: root
 */
#include "Common.h"
#include <time.h>
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
int GetTimeInfo(uint8_t *pTimeBuf)
{
	time_t at_time = time(NULL);
	struct tm ptr;
	char YMDHMS[24];
	localtime_r(&at_time, &ptr);

	strftime(YMDHMS, 22, "%Y-%m-%d %H:%M:%S", &ptr);
	memcpy(pTimeBuf, YMDHMS, strlen(YMDHMS));

	return 0;
}
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
int GetTimeStamp(uint64_t *pTimeStamp)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	*pTimeStamp = (uint64_t) ((uint64_t) tv.tv_sec * 1000
			+ (uint64_t) (tv.tv_usec / 1000));

	return 0;
}
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
int CreatDir(char *path)
{
	extern int errno;
//	char *path = "/Log";
	if ((access(path, F_OK)) == -1)
	{
		if (mkdir(path, 0766) == 0)
		{
			printf("created the directory %s . \n", path);
		}
		else
		{
			printf("can't creat the directoty %s.\n", path);
			printf("errno : %d\n", errno);
			printf("ERR : %s\n", strerror(errno));
		}
	}
	else
	{
		return 0;
	}
	return 0;
}

/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
int Encode_Frame(uint8_t CmdId, uint8_t SubCmdId, uint8_t State, uint8_t srcbuf[], uint32_t srcLen,
		uint8_t desbuf[], uint32_t *desLen)
{
	int lnBufLen = 0;
	//帧头
	desbuf[lnBufLen++] = 0xFF;
	desbuf[lnBufLen++] = 0xFF;
	//帧序号
	desbuf[lnBufLen++] =1;   // g_u8IndexId;
	// g_u8IndexId += 1;
	// g_u8IndexId &= 0x0F;

	//帧主命令号
	desbuf[lnBufLen++] = CmdId;
	//帧子命令号
	desbuf[lnBufLen++] = SubCmdId;
	//帧状态
	desbuf[lnBufLen++] = State;
	//帧长度
	desbuf[lnBufLen++] = ((srcLen)) & 0xFF;
	desbuf[lnBufLen++] = ((srcLen) >> 8) & 0xFF;
	//拷贝数据
	memcpy(&desbuf[lnBufLen], srcbuf, srcLen);
	lnBufLen += srcLen;

	//校验位
	desbuf[lnBufLen++] = 0x00;
	//帧尾
	desbuf[lnBufLen++] = 0xFF;

	(*desLen) = lnBufLen;
	return lnBufLen;
}

/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
int Encode_Frame_Clt(uint8_t CmdId, uint8_t SubCmdId, uint8_t srcbuf[], uint32_t srcLen,
		uint8_t desbuf[], uint32_t *desLen)
{
	int lnBufLen = 0;
	//帧头
	desbuf[lnBufLen++] = 0x5E;
	desbuf[lnBufLen++] = 0x5D;

	//
	desbuf[lnBufLen++] = CmdId;
	//
	desbuf[lnBufLen++] = SubCmdId;
	//
	lnBufLen += 6;
	//
	desbuf[lnBufLen++] = 0x10;
	//
	desbuf[lnBufLen++] = 0x00;
	//帧长度
	desbuf[lnBufLen++] = ((srcLen)) & 0xFF;
	desbuf[lnBufLen++] = ((srcLen) >> 8) & 0xFF;
	//拷贝数据
	memcpy(&desbuf[lnBufLen], srcbuf, srcLen);
	lnBufLen += srcLen;

	//校验位
	desbuf[lnBufLen++] = 0x00;
	//帧尾
	desbuf[lnBufLen++] = 0x5C;
	desbuf[lnBufLen++] = 0x5B;

	(*desLen) = lnBufLen;
	return lnBufLen;
}

/*从字符串中间截取n个字符*/
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
char * mid(char *dst,char *src, int n,int m) /*n为长度 m为位置*/
{
    char *p = src;
    char *q = dst;
    int len = strlen(src);
    if(n>len) n = len-m;    /**/
    if(m<0) m=0;
    if(m>len) return NULL;
    p += m;
    while(n--) *(q++) = *(p++);
    *(q++)='\0';
    return dst;
}

/**********************************************
 * 函数名  : double FG_Angletoradian(double p_dA)
 * 功能描述: 角度转化弧度值
 * 输入参数: p_dAangel  角度值
 * 输出参数: *
 * 返回值  :  弧度值
 * 作者 : 黄翔宇
 * 创建日期: 2017/2/17 10:57:36
 **********************************************/
double FG_Angletoradian1(double p_dAangel)
{
    return p_dAangel * PI / 180.0;
}

/**********************************************
 * 函数名 :  double FG_Getdistance(double p_dLatObj, double p_dlngObj, double p_dLatTag, double p_dlngTag)
 * 功能描述: 根据经纬度计算两车车距
 * 输入参数: p_dLatObj 自车纬度坐标
		     p_dlngObj 自车经度坐标
		     p_dLatTag 目标车纬度坐标
		     p_dlngTag 目标车经度坐标
 * 输出参数: *
 * 返回值 : p_dDistance 车距
 * 作者 : 黄翔宇
 * 创建日期: 2017/2/17 11:00:10
 **********************************************/

double FG_Getdistance1(double p_dLatObj, double p_dlngObj, double p_dLatTag, double p_dlngTag)
{
	// double p_dDistance = 0;

    // double radLat1 = FG_Angletoradian1(p_dLatObj);
    // double radLat2 = FG_Angletoradian1(p_dLatTag);

    // double a = radLat1 - radLat2;
    // double b = FG_Angletoradian1(p_dlngObj) - FG_Angletoradian1(p_dlngTag);
    // double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2) )));
    // dst = dst * EARTH_RADIUS1/1000;

	// p_dDistance = (dst * 10000000) / 10000;
    // return p_dDistance;
}

/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
void InitV2VParameter()
{
// // Parameter for MapMatch()
// 	g_V2V_Parameter.MapMatch_ConfidenceDis_toLink = 20;

// /// Parameter for isDangerPossible()
// 	g_V2V_Parameter.isDanger_hv_warning_time = 10;
// 	g_V2V_Parameter.isDanger_hv_speed_low = 3;

// /// Parameter forCalVehicleLocation() , CaseDetect()
// 	g_V2V_Parameter.VehLOC_SafeDis_Value = 1;

// ///Parameter for V2V_AVW_Section()
// 	g_V2V_Parameter.AVW_Speed_threshold_value = 10;

// ///Parameter for V2V_FCW_Section()
// 	g_V2V_Parameter.FCW_TTC_threshold_value = 3;
// 	g_V2V_Parameter.FCW_THW_threshold_value = 1;

// ///Parameter for V2V_LCW_Section()
// 	g_V2V_Parameter.LCW_Blind_Spot_Angle = 60;
// 	g_V2V_Parameter.LCW_Blind_Spot_Width = 8;
// 	g_V2V_Parameter.LCW_Blind_Spot_ToMirror = 0.5;

// ///Parameter for V2V_ICW_Section()
// 	g_V2V_Parameter.ICW_TTC_threshold_value = 5;
// 	g_V2V_Parameter.ICW_TTC_SafeDisVeh = 0.5;
}

/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
void InitSpatParameter()
{
// 	g_Spat_Parameter.LightDir_Dis_Value = 30;  //判断下游节点相对为 横向偏移阈值
// /// Parameter for SpeedGuide()
// 	g_Spat_Parameter.SPATWarnDis = 100;
// 	g_Spat_Parameter.WarnCalcTime = 0.7;
// 	g_Spat_Parameter.DistoCrossRdMid = 18;
// 	g_Spat_Parameter.SpeedLimit_High = 15;
// 	g_Spat_Parameter.SpeedLimit_Low = 3;
}

/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
void InitV2IParameter()
{
/// Parameter for IVS()
	// g_V2I_Parameter.IVSWarnDis = 50;
	// g_V2I_Parameter.IVSSpeakDis = 50;
}
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
void InitRSMParameter()
{
	// g_RSM_Parameter.Laser_Lat = 0;
	// g_RSM_Parameter.Laser_Long = 0;
	// g_RSM_Parameter.Laser_Display = 50;
}
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
//void LoadXml(MessageFrame_t **pSendMsg, char *pConfigFileName)
//{
//	char *p;
//	char *xer_buf = NULL;
//	int fsize = 0;
//	FILE *pxerfp;
//	pxerfp = fopen(pConfigFileName, "r"); //Read all bytes in RSI config file
//	fseek(pxerfp, 0, SEEK_END);
//	fsize = ftell(pxerfp);
//	xer_buf = calloc(1, fsize);
//	p = xer_buf;
//	rewind(pxerfp);
//	fread(xer_buf, fsize, 1, pxerfp);
//	fclose(pxerfp);
//	asn_dec_rval_t rval;
//	rval = xer_decode(0, &asn_DEF_MessageFrame, (void **) pSendMsg, xer_buf,
//			fsize);
//	if (rval.code != RC_OK)
//	{
//		(*pSendMsg)->present = MessageFrame_PR_NOTHING;
//	//	printf("11111\n");
//	}
//
//	free(p);
//}
