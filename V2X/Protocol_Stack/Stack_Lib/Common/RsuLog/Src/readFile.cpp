#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

extern "C"
{
#include "../Inc/readFile.h"
}

using namespace std;

extern char LogConfigFILEDIR[128];
extern char LogFILENAME[32];
extern char LogConfigFileName[128];
extern char LogCATEGORYName[128];
static int CreateDir(string strSrc, string subStr)
{
    string strbuf = "";
    string strDes = "";

    int index = 0;
    int index1 = 0;
    int index2 = 0;
    int Ret = 0;
    index = strSrc.find(subStr, 0);
    if (index != string::npos)
    {
        strbuf = strSrc.substr(0, index);
        index1 = strbuf.rfind('/', string::npos);
        index2 = strbuf.rfind('"', string::npos);
        if ((index1 != 0) && (index2 != 0) && (index1 > index2))
        {
            strDes = strbuf.substr(index2 + 1, index1 - index2);
            /* 判断当前文件夹是否存在 */
            Ret = access((char *)strDes.c_str(), 0);
            if (Ret < 0)
            {
                Ret = mkdir((char *)strDes.c_str(), 0777);
                if (0 != Ret)
                {
                    return -1;
                }
            }
        }
    }
    return 0;
}

static int replaceStr(string &strSrc, string findStr, string subStr)
{
    int index = 0;
    int index1 = 0;
    int index2 = 0;

    index = strSrc.find(findStr, 0);
    if (index != string::npos)
    {
        index1 = strSrc.find(" ", index);
        if (index1 != string::npos)
        {
            index2 = index + findStr.length();
            strSrc.replace(index2, index1 - index2, subStr, 0, subStr.length());
        }
    }

    if (findStr == "rsulog_.")
    {
        index = strSrc.rfind(findStr, string::npos);
        if (index != 0)
        {
            index1 = strSrc.find(" ", index);
            if (index1 != string::npos)
            {
                index2 = index + findStr.length();
                strSrc.replace(index2, index1 - index2, subStr, 0, subStr.length());
            }
        }
    }

    return 0;
}

//以下文件读写方式严格遵循现有配置文件格式，空格，双引号等特殊字符不能修改

int readFile(const char *LogConfigPath)
{
    char bufLine[1024] = {0};
    string strLine = "", strbuf = "", strSubbuf = "";
    int index = 0;
    ifstream fin(LogConfigPath);
    if (!fin)
    {
        return -1;
    }

    while (fin.getline(bufLine, 1024))
    {
        strLine += bufLine;
        strLine += "\n";

        strbuf = bufLine;
        index = strbuf.find(string("_process_module"), 0);
        if (index != string::npos)
        {
            strSubbuf = strbuf.substr(0, index);

            if (strSubbuf.find("// ", 0) != string::npos)
                strSubbuf = strSubbuf.substr(strSubbuf.find_first_not_of(string("// "), 0), strSubbuf.length());
            else if (strSubbuf.find("# ", 0) != string::npos)
                strSubbuf = strSubbuf.substr(strSubbuf.find_first_not_of(string("# "), 0), strSubbuf.length());
            else if (strSubbuf.find("#", 0) != string::npos)
                strSubbuf = strSubbuf.substr(strSubbuf.find_first_not_of(string("#"), 0), strSubbuf.length());
            else if (strSubbuf.find("//", 0) != string::npos)
                strSubbuf = strSubbuf.substr(strSubbuf.find_first_not_of(string("//"), 0), strSubbuf.length());

            strSubbuf += string("_process_module");
        }
    }
    fin.close();

    CreateDir(strLine, string(".#r.log"));
    CreateDir(strLine, string("%T.#r.log"));
    CreateDir(strLine, string("%M(module-name).#r.log"));

    //截取文件名及路径
    string strFile = LogConfigPath;
    int in = strFile.rfind("/", string::npos);
    if (in != 0)
    {
        string str = strFile.substr(in + 1, strFile.length() - in);
        memcpy(LogFILENAME, (char *)str.c_str(), sizeof(LogFILENAME));

        str = strFile.substr(0, in + 1);
        memcpy(LogConfigFILEDIR, (char *)str.c_str(), sizeof(LogConfigFILEDIR));
    }
    memcpy(LogConfigFileName, LogConfigPath, sizeof(LogConfigFileName));
    memcpy(LogCATEGORYName, (char *)strSubbuf.c_str(), sizeof(LogCATEGORYName));

    printf("%s %s %d %s\n", __FILE__, __FUNCTION__, __LINE__, LogConfigFILEDIR);
    printf("%s %s %d %s\n", __FILE__, __FUNCTION__, __LINE__, LogFILENAME);
    printf("%s %s %d %s\n", __FILE__, __FUNCTION__, __LINE__, LogConfigFileName);
    printf("%s %s %d %s\n", __FILE__, __FUNCTION__, __LINE__, LogCATEGORYName);
    return 0;
}

int writeFile(const char *LogConfigPath)
{
    char bufLine[1024] = {0};
    string strLine = "";

    ifstream fin(LogConfigPath);
    if (!fin)
    {
        return -1;
    }

    while (fin.getline(bufLine, 1024))
    {
        strLine += bufLine;
        strLine += "\n";
    }
    fin.close();

    replaceStr(strLine, "rsulog_.", "DEBUG");
    replaceStr(strLine, "rsulog_process_.", "WARN");
    replaceStr(strLine, "rsulog_process_module.", "DEBUG");

    replaceStr(strLine, ".log\",", "100M");
    replaceStr(strLine, "%T.log\",", "20M");
    replaceStr(strLine, "%M(module-name).log\",", "100M");

    ofstream fout(LogConfigPath);
    if (!fout)
    {
        return -1;
    }
    fout << strLine;

    fout.close();
    return 0;
}