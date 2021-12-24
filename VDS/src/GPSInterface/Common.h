/*
 * Common.c
 *
 *  Created on: May 25, 2018
 *      Author: root
 */

#ifndef __APPLYLAYER_COMMON_COMMON_C_
#define __APPLYLAYER_COMMON_COMMON_C_

//#include "../../Include/BaseInterface_Include.h"
#include "DataSet.h"
//#include "../../Algorithm/DataSet/DataSet.h"

#define EARTH_RADIUS1  6371004
#define PI 3.1415926
#define RetTure  0   
#define ReError  1   
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
int GetTimeInfo(uint8_t *pTimeBuf);
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
int GetTimeStamp(uint64_t *pTimeStamp);
/****************************************************
 * 函数名称:CreatDir
 * 功能描述:创建指定名称的目录，如果该目录存在，则直接返回成功
 * 输入参数:char *path 需要创建的文件夹名称，不支持多级目录同时创建
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
int CreatDir(char *path);
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
int Encode_Frame_YT_Veh(int nMsgType, int nPRIO, char VID[], uint8_t srcbuf[], uint32_t srcLen,
                        uint8_t desbuf[], uint32_t *desLen);
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
int Encode_Frame(uint8_t CmdId, uint8_t SubCmdId, uint8_t State, uint8_t srcbuf[], uint32_t srcLen,
                 uint8_t desbuf[], uint32_t *desLen);
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
int Encode_Frame_Clt(uint8_t CmdId, uint8_t SubCmdId, uint8_t srcbuf[], uint32_t srcLen,
                     uint8_t desbuf[], uint32_t *desLen);

/*从字符串中间截取n个字符*/
/****************************************************
 * 函数名称:
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 * 创建日期:
 ****************************************************/
char * mid(char *dst, char *src, int n, int m); /*n为长度 m为位置*/

/**********************************************
 * 函数名 :  double FG_Getdistance(double p_dLatObj, double p_dlngObj, double p_dLatTag, double p_dlngTag)
 * 功能描述: 根据经纬度计算两车车距
 * 输入参数:
 * 			p_dLatObj 自车纬度坐标
 * 			p_dlngObj 自车经度坐标
 * 			p_dLatTag 目标车纬度坐标
 * 			p_dlngTag 目标车经度坐标
 * 输出参数: *
 * 返回值 : p_dDistance 车距
 * 作者 : 黄翔宇
 * 创建日期: 2017/2/17 11:00:10
 **********************************************/

double FG_Getdistance1(double p_dLatObj, double p_dlngObj, double p_dLatTag,
                       double p_dlngTag);

void InitV2VParameter();
void InitSpatParameter();
void InitV2IParameter();
void InitRSMParameter();
//void LoadXml(MessageFrame_t **pSendMsg, char *pConfigFileName);
#endif /* __APPLYLAYER_COMMON_COMMON_C_ */
