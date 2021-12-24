#ifndef TSP_FILE_H
#define TSP_FILE_H
 
#include<sys/stat.h>
#include <stdio.h>
#include "wj_log.h"
#include "tsp_config.h"
#include <curl/curl.h>
#include "misc.h"
#include "RdWrIni.h"
#include "RdWrIniIf.h"
#include <libgen.h>
#include <dirent.h>
#include "queue.h"

static char UpdateVersion[30] = {0};
static char UpdateUrl[200] = {0};
static char UserName[50] = {0};
static char PassWord[50] = {0};

static char url[100] = {0};

static CURL *curlUpLoadHandle = NULL;
static CURL *curlDownHandle = NULL;

pthread_t upLoadId;                       //上传log线程
static char fileName[50][256] = {0};      //查找上传log文件名存储
static unsigned int cnt = 0;              //文件名数组个数
extern int logType;                   //需要上传日志文件类型
extern int logAmount;                 //需要上传日志文件个数

static char upLoadFileLocalUrl[30] = {0}; //上传日志文件时，本地存储日志文件的路径

struct Queue mQueue;
struct upLoadFile_t mUpLoadFileData;
pthread_mutex_t mute;
 
size_t getContentFunc(void *ptr, size_t size, size_t nmemb, void *stream);

size_t writeFunc(void *ptr, size_t size, size_t nmemb, void *stream);

/*下载文件*/
int downLoad();//CURL *curlhandle, const char *ftppath, const char *localpath

/*上传文件*/
int upLoad(CURL *curlhandle, const char *ftppath, const char *localpath, /*long timeout, */ long tries);

/*MD5校验*/
void checkSum(const char *localpath, int DownloadStatus);

/*软件升级*/
void upgrade();

/*升级*/
void updateSoftWareCountTime();

/*检查本地版本和远程要升级版本是否相同，相同情况下，不进行下载以及本地升级操作！*/
int checkVersion(const char *versionSn);

/*FTP相关配置参数设置*/
int setFTPConfig(int frameType, char *Version, char *Url, char *Name, char *Pwd);

/*FTP 下载*/
void ftpDownLoad();

/*FTP 上传日志*/
void ftpUpLoad();

/*查找log目录下的文件名*/
int findFile(int logType, int logAmount);

/*排序查找*/
void sortFileName(char name[50][256], int type);

pthread_t pthid;
void pthreadFtpUpload();

#endif //TSP_FILE_H

