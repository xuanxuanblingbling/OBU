/************************************************************
 文件名: CuseCPP.h
 作者:   WangMeng
 描述:   数据操作类接口源文件
 版本:   V1.0
 日期:   2020.5.20
 ***********************************************************/
#include "CUseCPP.h"

/**
 * @brief 字符串转整形数组
 */
int str2Intlist(const char *strSource, int iDes[32])
{
    if (NULL == strSource)
    {
        return 0;
    }
    if (strlen(strSource) <= 0)
    {
        return 0;
    }

    memset(iDes, 0x00, (32 * sizeof(int)));

    char *result = NULL;
    result = strtok((char *)strSource, ", "); //注意此处增加检查空格
    int index = 0;                            //数组索引
    while (result != NULL)
    {
        iDes[index] = atoi(result);
        index += 1;
        result = strtok(NULL, ", ");

        if (index >= 32)
            break;
    }
    return index;
}

int str2IntlistBak(const char *strSource, int iDes[32])
{
    if (NULL == strSource)
    {
        return 0;
    }
    if (strlen(strSource) <= 0)
    {
        return 0;
    }
    memset(iDes, 0x00, (32 * sizeof(int)));
    int nlen = strlen(strSource);
    int index = 0;       //整型数组索引
    char iNum[12] = {0}; //存储数字
    int jNum = 0;        //数字位数计数器
    int i = 0;
    for (i = 0; i < nlen; i += jNum)
    {
        jNum = 0;
        if ('0' <= strSource[i] && strSource[i] <= '9')
        {
            jNum += 1;
            int n = i;
            for (n = i; n < nlen; n++) //查询当前位置的下一个逗号，判断当前数字有几位
            {
                if ('0' <= strSource[n] && strSource[n] <= '9')
                    jNum += 1;
                else
                    break;
            }
            memset(iNum, 0, sizeof(iNum));
            memcpy(iNum, &strSource[i], jNum);
            iDes[index] = atoi(iNum);
            index += 1;
            if (index >= 32)
                return index;
        }
        else
        {
            i += 1;
        }
    }
    return index;
}
/**
 * @brief 字符串转字符串数组
 */
int str2Stringlist(const char *strSource, char sDes[32][32])
{
    if (NULL == strSource)
    {
        return 0;
    }
    if (strlen(strSource) <= 0)
    {
        return 0;
    }
    memset(sDes, 0x00, (32 * 32 * sizeof(char)));

    char *result = NULL;
    result = strtok((char *)strSource, ", "); //注意此处增加检查空格
    int index = 0;                            //数组索引
    while (result != NULL)
    {
        strcpy(sDes[index], result);
        index += 1;
        result = strtok(NULL, ", ");

        if (index >= 32)
            break;
    }
    return index;
}

/**
 * @brief 整型转字符串
 */
string intTostring(int n)
{
    // int ת string
    stringstream ss;
    string str;
    ss << n;
    ss >> str;
    return str;
}
/**
 * @brief 字符串数组转字符串，以逗号分割
 */
string intList2str(int nlen, int iDes[32])
{
    string retString = "";
    int i = 0;
    for (i = 0; i < nlen; i++)
    {
        retString += intTostring(iDes[i]);

        if (i + 1 != nlen)
        {
            retString += ",";
        }
    }
    return retString;
}

/**
 * @brief 字符串数组转字符串，以逗号分割
 */
string stringList2str(int nlen, char sDes[32][32])
{
    string retString = "";
    int i = 0;
    for (i = 0; i < nlen; i++)
    {
        retString += sDes[i];

        if (i + 1 != nlen)
        {
            retString += ",";
        }
    }
    return retString;
}

/**
 * @brief 读取json节点字符串数据
 */
char *strGetJsonStringItem(cJSON *jsonRoot, const char *ItemName)
{
    if (NULL == jsonRoot || NULL == ItemName)
    {
        return NULL;
    }
    char *strTemp = NULL;

    cJSON *jsonSub = cJSON_GetObjectItem(jsonRoot, ItemName);

    if (NULL == jsonSub)
    {
        return strTemp;
    }

    strTemp = (char *)(jsonSub->valuestring);
    return (strTemp);
}
/**
 * @brief 读取json节点整型数据
 */
int iGetJsonNumberItem(cJSON *jsonRoot, const char *ItemName)
{
    if (NULL == jsonRoot || NULL == ItemName)
    {
        return -1;
    }
    cJSON *jsonSub = cJSON_GetObjectItem(jsonRoot, ItemName);
    if (NULL == jsonSub)
    {
        return 0;
    }
    return jsonSub->valueint;
}

/**
 * @brief 交换数组数字
 */
void swap(int array[], int i, int j)
{
    int temp = array[i];

    array[i] = array[j];

    array[j] = temp;
}
/**
 * @brief 冒泡排序 小数字向前冒泡
 */
void BubbleSort(int array[], int len) // O(n*n)
{
    int i = 0;
    int j = 0;
    int exchange = 1;
    //判断交换标志，若最后不需要交换，则认为数组也完成排序，直接返回
    for (i = 0; (i < len) && exchange; i++)
    {
        exchange = 0;
        //从后向前比较，小数字向前交换
        for (j = len - 1; j > i; j--)
        {
            if (array[j] < array[j - 1])
            {
                swap(array, j, j - 1);
                exchange = 1;
            }
        }
    }
}
void IntToHex(unsigned int iValue, char *pData, int iCovLen, int iType)
{
    if (iCovLen <= 0)
        return;
    if (iType == ORD_MOTOR)
    {
        int i = 0;
        for (i = 0; i < iCovLen; i++)
            pData[i] = (unsigned char)((iValue >> (8 * (iCovLen - i - 1))) & 0x000000ff);
    }
    else
    {
        int i = 0;
        for (i = 0; i < iCovLen; i++)
            pData[iCovLen - i - 1] = (unsigned char)((iValue >> (8 * (iCovLen - i - 1))) & 0x000000ff);
    }
}

void IntToHexMx(unsigned int iValue, char *pData, int iCovLen)
{
    IntToHex(iValue, pData, iCovLen, ORD_MOTOR);
}