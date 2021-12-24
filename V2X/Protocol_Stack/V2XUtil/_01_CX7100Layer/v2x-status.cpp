#include <iostream>
#include "v2x-status.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <string>
extern "C"
{
// #include "libgpsmm.h"
// #include "gps.h"
#include "wj_log.h"
}

using namespace std;

static int str2Stringlist(char *strSource, char sDes[32][32])
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

    char *ptr1 = strSource;
    char *ptr2 = strSource;
    int index = 0, i = 0;
    while (*ptr1 != '\0')
    {
        if (*ptr1 == ',')
        {
            memcpy(sDes[i], ptr2, index);
            ptr1 += 1;
            index = 0;
            ptr2 = ptr1;
            i += 1;
        }
        else if (*(ptr1 + 1) == '\0')
        {
            memcpy(sDes[i], ptr2, index + 1);
            ptr1 += 1;
            i += 1;
        }
        else
        {
            ptr1 += 1;
            index += 1;
        }

        if (i >= 31)
            break;
    }
    return i;
}

#if 0
//CX AP
int CheckV2xState()
{
    std::string cmd = "cat /dev/ttyS1";
    FILE *fp = popen(cmd.c_str(), "r");
    if (fp == NULL)
    {
        return -1;
    }

    char buffer[128] = {0};
    fread(buffer, sizeof(char), 128, fp);
    pclose(fp);

    char sub[32][32] = {0};
    //parse string
    std::string str = buffer;
    std::size_t findIndex = str.find("$GNRMC");
    if (findIndex != std::string::npos)
    {
        std::size_t findIndex2 = str.find("\n", findIndex);
        std::string subStr = str.substr(findIndex, findIndex2 - findIndex);
        printf("%s %d %s\n", __FUNCTION__, __LINE__, subStr.c_str());
        int num = str2Stringlist((char *)subStr.c_str(), sub);
        if (num > 0)
        {
            if ((strcmp(sub[2], "A") == 0))
            {
                return 0;
            }
            else
            {
                printf("%s %d %s\n", __FUNCTION__, __LINE__, sub[2]);
                return -1;
            }
        }
    }

    return -1;
}
#endif

static int FS_CX7100IsExist(void)
{
    FILE *fd = NULL, *fd1 = NULL;
    char l_Line[128] = {0};
    char l_SrcCXStatus[10] = {0};
    int GpsRet = 0, findFlag = 0, StatusRet = 0;

    //检查gps
    fd = popen("echo -en \"AT^V2XGPS?\r\" | busybox microcom -t 500 /dev/ttyUSB0", "r");
    if (fd == NULL)
    {
        //popen执行失败后，默认正常
        LogPrint(LOG_LEVEL_ERR, "V2XUtil_Debug", "popen error\n");
        return 1;
    }
    while (NULL != fgets(l_Line, sizeof(l_Line), fd))
    {
        l_Line[strlen(l_Line) - 1] = '\0'; /*去除最后的 '\n'字符，防止输出空行*/
        char *l_pcNumstr;
        l_pcNumstr = strstr(l_Line, "^V2XGPS: ");
        if (NULL != l_pcNumstr)
        {
            findFlag = 1;
            memcpy(l_SrcCXStatus, &l_pcNumstr[9], strlen("valid"));
            l_SrcCXStatus[strlen("valid")] = '\0';
            if (strcmp(l_SrcCXStatus, "valid") == 0)
            {
                GpsRet = 1;
                break;
            }
            else
            {
                LogPrint(LOG_LEVEL_WARN, "V2XUtil_Debug", "l_SrcCXStatus = %s", l_SrcCXStatus);
            }
        }
    }
    pclose(fd);

    if (findFlag == 0)
    {
        //未找到关键字情况下，不代表模组不正常，此处默认返回正常
        LogPrint(LOG_LEVEL_WARN, "V2XUtil_Debug", "Not Find V2XGPS");
        GpsRet = 0;
    }

    usleep(100);

    //检查模组状态
    findFlag = 0;
    fd1 = popen("echo -en \"at^v2xcs=2\r\" | busybox microcom -t 500 /dev/ttyUSB0", "r");
    if (fd1 == NULL)
    {
        //popen执行失败后，默认正常
        LogPrint(LOG_LEVEL_ERR, "V2XUtil_Debug", "popen error\n");
        return 1;
    }
    while (NULL != fgets(l_Line, sizeof(l_Line), fd1))
    {
        l_Line[strlen(l_Line) - 1] = '\0'; /*去除最后的 '\n'字符，防止输出空行*/
        char *l_pcNumstr;
        l_pcNumstr = strstr(l_Line, "^V2XCSNC: ");
        if (NULL != l_pcNumstr)
        {
            findFlag = 1;
            memcpy(l_SrcCXStatus, &l_pcNumstr[10], 1);
            l_SrcCXStatus[1] = '\0';
            if (strcmp(l_SrcCXStatus, "1") == 0)
            {
                StatusRet = 1;
                break;
            }
            else
            {
                LogPrint(LOG_LEVEL_WARN, "V2XUtil_Debug", "l_SrcCXStatus = %s", l_SrcCXStatus);
            }
        }
    }
    pclose(fd1);

    if (findFlag == 0)
    {
        LogPrint(LOG_LEVEL_WARN, "V2XUtil_Debug", "Not Find V2XCSNC");
        StatusRet = 1;
    }

    if (StatusRet == 1 && GpsRet == 1)
    {
        //能发 能收
        return 1;
    }
    else if (StatusRet == 1 && GpsRet == 0)
    {
        //不发 能收
        return 0;
    }

    return -1;
}

static void deleteAllMark(string &s, const string &mark)
{
    size_t nSize = mark.size();
    while (1)
    {
        size_t pos = s.find(mark);
        if (pos == string::npos)
        {
            return;
        }

        s.erase(pos, nSize);
    }
}

//imx6
int CheckV2xState()
{
    int ret = 0;
    int flag = 0;
    string strLine = "";
    char bufLine[64] = {0};
    const char *ConfigPath = "/mnt/APP/Config/Module_MsgVersion.ini";

    ifstream fin(ConfigPath);
    if (!fin)
    {
        return 1;
    }
    while (fin.getline(bufLine, 64))
    {
        strLine = bufLine;
        deleteAllMark(strLine, " ");
        if (strLine.find(string("rsucascadeid=0"), 0) != string::npos)
        {
            //printf("%s %d %s\n", __FILE__, __LINE__, strLine.c_str());
            flag = 1;
            break;
        }
    }
    fin.close();

    if (flag)
    {
        //检查设备gps是否正常，此处暂不检查设备gps，直接检查模组gps即可
        // gpsmm gps_rec(GPSD_SHARED_MEMORY, NULL);
        // gps_rec.stream(WATCH_ENABLE | WATCH_JSON);
        // struct gps_data_t *newdata;
        // newdata = gps_rec.read();
        // if (newdata->status == 1)
        // {
        //     ret = 1;
        // }
        // if (ret)
        ret = FS_CX7100IsExist();
        return ret;
    }
    else
    {
        return 1;
    }
}