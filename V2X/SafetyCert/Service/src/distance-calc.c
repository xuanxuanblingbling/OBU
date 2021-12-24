#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EARTH_RADIUS 6371004
#define PI 3.1415926

/**********************************************
* 函数名 : double FG_Angletoradian(double p_dA)
* 功能描述: 角度转化弧度值
* 输入参数: p_dAangel 角度值
* 输出参数: *
* 返回值 : 弧度值
* 作者 : 黄翔宇
* 创建日期: 2017/2/17 10:57:36
**********************************************/
static double FG_Angletoradian(double p_dAangel)
{
    return p_dAangel * PI / 180.0;
}

/**********************************************
* 函数名 : double FG_RadiantoAngle(double p_dR)
* 功能描述: 弧度转化值角度
* 输入参数: p_dRadian 弧度值
* 输出参数: *
* 返回值 : 角度值
* 作者 : 黄翔宇
* 创建日期: 2017/2/17 10:58:55
**********************************************/
static double FG_RadiantoAngle(double p_dRadian)
{
    return p_dRadian * 180.0 / PI;
}

/**********************************************
* 函数名 : double FG_Getdistance(double p_dLatObj, double p_dlngObj, double p_dLatTag, double p_dlngTag)
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
double FG_Getdistance(double p_dLatObj, double p_dlngObj, double p_dLatTag, double p_dlngTag)
{
    double p_dDistance = 0;

    double radLat1 = FG_Angletoradian(p_dLatObj);
    double radLat2 = FG_Angletoradian(p_dLatTag);
    double a = radLat1 - radLat2;
    double b = FG_Angletoradian(p_dlngObj) - FG_Angletoradian(p_dlngTag);
    double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2) )));

    dst = dst * EARTH_RADIUS/1000;

    p_dDistance = (dst * 10000000) / 10000;

    return p_dDistance;
}
