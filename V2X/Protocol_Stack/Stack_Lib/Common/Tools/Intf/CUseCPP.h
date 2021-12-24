/************************************************************
 文件名: CuseCPP.h
 作者:   WangMeng
 描述:   数据操作类接口头文件
 版本:   V1.0
 日期:   2020.5.20
 ***********************************************************/
#ifndef _CUSECPP_H_
#define _CUSECPP_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>

extern "C"
{
#include "cJSON.h"
}

using namespace std;

#define ORD_MOTOR 0
#define ORD_INTEL 1
/**
 * @brief 字符串转整形数组
 */
int str2Intlist(const char *strSource, int iDes[32]);
int str2IntlistBak(const char *strSource, int iDes[32]);

/**
 * @brief 字符串转字符串数组
 */
int str2Stringlist(const char *strSource, char sDes[32][32]);

/**
 * @brief 整型转字符串
 */
string intTostring(int n);

/**
 * @brief 字符串数组转字符串，以逗号分割
 */
string intList2str(int nlen, int iDes[32]);

/**
 * @brief 字符串数组转字符串，以逗号分割
 */
string stringList2str(int nlen, char sDes[32][32]);

/**
 * @brief 读取json节点字符串数据
 */
char *strGetJsonStringItem(cJSON *jsonRoot, const char *ItemName);

/**
 * @brief 读取json节点整型数据
 */
int iGetJsonNumberItem(cJSON *jsonRoot, const char *ItemName);
/**
 * @brief 冒泡排序 小数字向前冒泡
 */
void BubbleSort(int array[], int len);

void IntToHexMx(unsigned int iValue, char *pData, int iCovLen);

#endif