/************************************************************
  文件名: tsp_file.c
  作者: 
  描述: 进行相关FTP文件的上传和下载， 包括下载软件版本，上传日志文件           
  版本:     
  日期:       
  函数列表:   
  历史记录: 
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "tsp_file.h"
#include <pthread.h>

#include "websockets.h"

#define UPDATE_CONFIG_FILE_NAME "/mnt/UPDATE/UpdateProcess/Config_Update.ini"

#define APP_LOG_PATH "/mnt/RWD/ObuLog/"                  //应用日志存储路径
#define ALG_LOG_PATH "/mnt/RWD/RsuLog/"                  //算法日志存储路径
#define SYSTEM_LOG_PATH "/mnt/RWD/ObuLog/"               //系统日志存储路径
#define KEY_CONFIG_LOG_PATH "/mnt/RWD/ObuLog/"           //关键配置日志存储路径

/*获取相关参数*/
size_t getContentFunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
    int r;
    long len = 0;
    r = sscanf((const char*)ptr, "Content-Length: %ld", &len);
    if(r)
    {
        *((long *)stream) = len;
    }
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," getContentFunc start !");
    return size*nmemb;
}

/*将下载的写入文件中*/
size_t writeFunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
	// LogPrint(LOG_LEVEL_INFO,MODULE_NAME," writeFunc start ! \n");
    return fwrite(ptr, size, nmemb, (FILE*)stream);
}

size_t discardFunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
    return size*nmemb;
}

size_t readFunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
    FILE *fp = (FILE *)stream;
    size_t n;
    if(ferror(fp))
    {
        return CURL_READFUNC_ABORT;
    }
    n = fread(ptr, size, nmemb, fp) * size;
    return n;
}

/*下载文件，使用被动模式进行传输*/
int downLoad(CURL *curlhandle, const char *ftppath, const char *localpath)//CURL *curlhandle, 
{
    LogPrint(LOG_LEVEL_INFO,MODULE_NAME," downLoad() - ftppath = %s", ftppath);
    LogPrint(LOG_LEVEL_INFO,MODULE_NAME," downLoad() - localpath = %s", localpath);

    FILE *fp;
    curl_off_t local_file_len = -1;
    long filesize = 0;
    CURLcode result = CURLE_GOT_NOTHING;

    //用于断点续传使用。
    struct stat file_info;
    int use_resume = 0;
    if(stat(localpath, &file_info) == 0)//将文件的所有状态复制到参数file_info指定的结构体中
    {
        local_file_len = file_info.st_size;
        use_resume = 1;
    }
	
    //断点叙传
    fp = fopen(localpath, "ab+");
    if(fp == NULL)
    {
		LogPrint(LOG_LEVEL_INFO,MODULE_NAME," file open fail!");
        return -1;
    }

    char userPwd[100] = {0};
    sprintf(userPwd,"%s:%s", UserName, PassWord);

    curl_easy_setopt(curlhandle, CURLOPT_URL, ftppath);
    curl_easy_setopt(curlhandle, CURLOPT_USERPWD, userPwd);
    // curl_easy_setopt(curlhandle, CURLOPT_CONNECTTIMEOUT, timeout);

    // //设置主动模式
    // curl_easy_setopt(curlhandle, CURLOPT_FTP_USE_EPRT,FALSE);
    // curl_easy_setopt(curlhandle, CURLOPT_FTP_USE_EPSV,FALSE);
    // curl_easy_setopt(curlhandle, CURLOPT_FTPPORT,"106.120.201.126,150.75");//找到任意一个空闲的端口进行传输数据。
    curl_easy_setopt(curlhandle, CURLOPT_HEADERFUNCTION,getContentFunc);
    curl_easy_setopt(curlhandle, CURLOPT_HEADERDATA, &filesize);
	//断点续传
    curl_easy_setopt(curlhandle, CURLOPT_RESUME_FROM_LARGE, use_resume ? local_file_len : 0);

    curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, writeFunc);
    curl_easy_setopt(curlhandle, CURLOPT_WRITEDATA, fp);
    
    curl_easy_setopt(curlhandle, CURLOPT_NOPROGRESS, 1L);//启用时关闭curl传输的进度条，此项的默认设置为启用。
    curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, 1L);//启用时会汇报所有的信息，存放在STDERR或指定的CURLOPT_STDERR中。

    sleep(1);
    result = curl_easy_perform(curlhandle);

    if(result == CURLE_OK) {
		LogPrint(LOG_LEVEL_INFO,MODULE_NAME," DownLoad OBU SoftWare - Version Success!");
        checkSum(localpath, 0);
        return 1;
    } else {
        //需要添加下载失败的时候处理。
		LogPrint(LOG_LEVEL_INFO,MODULE_NAME," DownLoad OBU SoftWare Version Fail!");
        checkSum(localpath, 1);
        return 0;
    }
}

/*上传文件*/
int upLoad(CURL *curlhandle, const char *ftppath, const char *localpath, /*long timeout, */ long tries)
{
    FILE *fp;
    long upload_len = 0;
    CURLcode result = CURLE_GOT_NOTHING;
    int c;

    fp = fopen(localpath, "rb");
    if(fp == NULL)
    {
		LogPrint(LOG_LEVEL_INFO,MODULE_NAME," file open fail!");
        return 1;
    }
    curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curlhandle, CURLOPT_URL, ftppath);

    char userPwd[100] = {0};
    sprintf(userPwd,"%s:%s", UserName, PassWord);
    curl_easy_setopt(curlhandle, CURLOPT_USERPWD, userPwd);
    // curl_easy_setopt(curlhandle, CURLOPT_CONNECTTIMEOUT, timeout);

    curl_easy_setopt(curlhandle, CURLOPT_HEADERFUNCTION,getContentFunc);
    curl_easy_setopt(curlhandle, CURLOPT_HEADERDATA, &upload_len);

	//断点续传
    curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, discardFunc);
    curl_easy_setopt(curlhandle, CURLOPT_READFUNCTION, readFunc);
    curl_easy_setopt(curlhandle, CURLOPT_READDATA, fp);
    // curl_easy_setopt(curlhandle, CURLOPT_FTPPORT, "-");

    curl_easy_setopt(curlhandle, CURLOPT_FTP_CREATE_MISSING_DIRS, 1L);
    curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, 1L);

    for(c= 0; (result != CURLE_OK)&&(c<tries); c++)
    {
        if(c){
            curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 1L);
            curl_easy_setopt(curlhandle, CURLOPT_HEADER, 1L);
            result = curl_easy_perform(curlhandle);
            if(result != CURLE_OK){
                continue;
            }
            curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 0L);
            curl_easy_setopt(curlhandle, CURLOPT_HEADER, 0L);
            fseek(fp, upload_len, SEEK_SET);
            curl_easy_setopt(curlhandle, CURLOPT_APPEND, 1L);
        }
        else
        {
            curl_easy_setopt(curlhandle, CURLOPT_APPEND, 0L);
        }
        result = curl_easy_perform(curlhandle);

    }

    fclose(fp);

    if(result == CURLE_OK){
		LogPrint(LOG_LEVEL_INFO,MODULE_NAME," upLoad OBU log Success!");
        return 0;
    }else{
		LogPrint(LOG_LEVEL_INFO,MODULE_NAME," upLoad OBU log Fail!");
        return 1;
    }
}


/*MD5校验*/
void checkSum(const char *localpath, int DownloadStatus)
{
    if(DownloadStatus)
    {//下载升级包失败，反馈升级失败结果
        updateSoftWareCountTime(DownloadStatus);
        return;
    }
    sleep(1);
    /*解压下载的压缩包文件到指定目录下*/
    char tar[100] = "tar -xvf ";
    strcat(tar, localpath);
    strcat(tar, " -C /mnt/UPDATE/DownloadFilePath");
    system(tar);//"tar -xvf /mnt/UPDATE/DownloadFilePath/WVO-L9_20210330_001.tar -C /mnt/UPDATE/DownloadFilePath"

    char rmTar[50] = "rm ";
    strcat(rmTar, localpath);
    system(rmTar);//删除最外层压缩包

    if(access("/mnt/UPDATE/DownloadFilePath/V2XUpgrade.tar", F_OK) != 0)
    {
        //解压后不存在V2XUpgrade.tar文件，所以需要上传升级失败结果
        LogPrint(LOG_LEVEL_INFO,MODULE_NAME," not exist V2XUpgrade.tar, so upgrade fail!");
        OTAUpgradeToServer(1, 0);
        return;
    }

    /*查找解压后的文件名,以下方案是根据动态名进行查找的，但是实际升级包名称都是固定的*/
    char url[]="/mnt/UPDATE/DownloadFilePath";
    DIR *pDir = NULL;
	struct dirent * pEnt = NULL;
    pDir = opendir(url);
    char name[256]={0};
	if (NULL == pDir)
	{
		LogPrint(LOG_LEVEL_ERR,MODULE_NAME," opendir fail!");
		return -1;
	}

	while (1)
	{
		pEnt = readdir(pDir);
        if(pEnt != NULL)
        {
            if(strstr(pEnt->d_name, ".tar") != NULL)
            {
                strcpy(name, pEnt->d_name);
                LogPrint(LOG_LEVEL_INFO,MODULE_NAME," tar file name = %s", name);
            }
        }
        else
        {
            break;
        }
	};

    /*获取文件名，不包含后缀*/
    char delims[] = ".";
    char *result = NULL;
    result = strtok(name, delims);

    sleep(1);
    /*打开其对应文件名的md5文件，并将其md5值进行保存buf*/
    char temp[100]={0};
    strcat(temp, "/mnt/UPDATE/DownloadFilePath/");
    strcat(temp, result);
    strcat(temp, ".md5");
    // FILE *fp = fopen("/mnt/UPDATE/DownloadFilePath/V2XUpgrade.md5", "ab+");
    FILE *fp = fopen(temp, "ab+");
    char *pbuf = NULL;
    fseek(fp, 0, SEEK_SET);
    pbuf= (char *) malloc(32+1);
    memset(pbuf,0,32+1);
    /* 读取并显示数据 */
    fread(pbuf, 32, 1, fp);
    fclose(fp);

    //切换到此目录下，创建临时的md5值
    chdir("/mnt/UPDATE/DownloadFilePath");
    char temp1[100]={0};
    strcat(temp1, "md5sum ");
    strcat(temp1, name);
    strcat(temp1, ".tar");
    strcat(temp1, " > temp.md5");
    system(temp1);
    // system("md5sum V2XUpgrade.tar > temp.md5");

    /*打开临时对应文件名的md5文件，并将其md5值进行保存buf_temp*/
    FILE *fp_temp = fopen("/mnt/UPDATE/DownloadFilePath/temp.md5", "ab+");
    char *pbuf_temp = NULL;
    fseek(fp_temp, 0, SEEK_SET);
    pbuf_temp= (char *) malloc(32+1);
    memset(pbuf_temp,0,32+1);
    /* 读取并显示数据 */
    fread(pbuf_temp, 32, 1, fp_temp);
    fclose(fp_temp);
    
    /*校验md5值*/
    if(strcmp(pbuf, pbuf_temp) == 0) {//校验MD5成功后，需要删除，原始下载的文件以及其对应的md5值，同时删除临时md5值文件。
        LogPrint(LOG_LEVEL_INFO,MODULE_NAME," MD5 check Success!");
        system("rm /mnt/UPDATE/DownloadFilePath/temp.md5");//删除临时创建的md5文件

        char temp_1[100] = "rm ";
        strcat(temp_1, localpath);
        system(temp_1);

        char rmFile[100] = "rm ";
        strcat(rmFile, temp);
        system(rmFile);
        system("rm /mnt/UPDATE/DownloadFilePath/V2XUpgrade.md5");//删除原压缩文件

        if(pthread_create(&pthid, NULL, (void *)upgrade, NULL) != 0) {//在升级时，单起线程进行计时操作
		    printf("thread creation failed！");
        }else{
            pthread_detach(pthid);//分离线程在函数运行完成之后可以自动释放资源
        }
        
        free(pbuf);
        free(pbuf_temp);
    } else {
        LogPrint(LOG_LEVEL_INFO,MODULE_NAME," MD5 check Fail, so response upgrade fail!");
        OTAUpgradeToServer(1, 0);
        return;
    }
    updateSoftWareCountTime(DownloadStatus);
}

/*升级执行脚本*/
void upgrade()
{
    //切换到/mnt/APP/mainprogram目录下，并在校验完MD5成功后，需要停掉所有进程，以供后续的拷贝！
    // chdir("/mnt/APP/mainprogram");
    system("sh /mnt/APP/mainprogram/stop-process");

    //开始升级，执行升级脚本
    system("sh /mnt/APP/Scripts/V2XAPP_UpdateFile.sh");
}

/*软件升级，根据下载的OBU软件版本，运行脚本进行升级操作！*/
void updateSoftWareCountTime(int DownloadStatus)
{
    //开始升级
    int ShellStatus = 0;
    int Progress = 0;
    int counter = 0;
    int result = 0;
    if(!DownloadStatus)
    {
        while (1)
        {
            sleep(1);
            counter++;
            ShellStatus = GetPrivateProfileInt("UpdataStatus","ShellStatus", 0, UPDATE_CONFIG_FILE_NAME);
            Progress = GetPrivateProfileInt("UpdataStatus","Progress", 0, UPDATE_CONFIG_FILE_NAME);

            LogPrint(LOG_LEVEL_INFO,MODULE_NAME," OBU is upgrading, Please wait for a minute .....!");

            if(Progress == 4)
            {
                LogPrint(LOG_LEVEL_INFO,MODULE_NAME," Upgrade completed & Success!");
                result = 0;
                break;
            } 
            else if(Progress == 3)
            {
                LogPrint(LOG_LEVEL_INFO,MODULE_NAME," Upgrade uncompleted & Fail!");
                result = 1;
                break;
            }

            if(counter > 60*10)
            {//10分钟超时，升级失败处理
                LogPrint(LOG_LEVEL_INFO,MODULE_NAME," Upgrade Timeout!");
                result = 1;
                break;
            }
        }
        LogPrint(LOG_LEVEL_INFO,MODULE_NAME," Upgrade completed Progress = %d", Progress);
    }
    else
    {
        LogPrint(LOG_LEVEL_INFO,MODULE_NAME," dowload fail, so upgrade fail!");
        result = 1;
    }
    //将升级结果反馈出去.
    OTAUpgradeToServer(result, DownloadStatus);
}

/*FTP相关配置参数设置*/
int setFTPConfig(int frameType, char *Version, char *Url, char *Name, char *Pwd)
{
    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " setFTPConfig start!");
    memset(UpdateVersion, 0, sizeof(UpdateVersion));
    memset(UpdateUrl, 0, sizeof(UpdateUrl));
    memset(UserName, 0, sizeof(UserName));
    memset(PassWord, 0, sizeof(PassWord));

    // memcpy(UpdateVersion, Version, strlen(Version)+1);
    // memcpy(UpdateUrl, Url, strlen(Url)+1);
    // memcpy(UserName, Name, strlen(Name)+1);
    // memcpy(PassWord, Pwd, strlen(Pwd)+1);

    strcat(UpdateVersion, Version);
    strcat(UpdateUrl, Url);
    strcat(UserName, Name);
    strcat(PassWord, Pwd);

    int result = 0;

    if(frameType == 0x8101)//OTA 升级
    {
        ftpDownLoad();
        result = 1;
    }
    else if(frameType == 0x8001)//日志上传
    {
        mUpLoadFileData.logAmount = logAmount;
        mUpLoadFileData.logType = logType;
        strcpy(mUpLoadFileData.PassWord, PassWord);
        strcpy(mUpLoadFileData.UpdateUrl, UpdateUrl);
        strcpy(mUpLoadFileData.UserName, UserName);

        QueuePush(&mQueue, mUpLoadFileData);

        // if(pthread_create(&upLoadId, NULL, (void *)ftpUpLoad, NULL) != 0)
        // {
        //     LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " thread creation failed！");
        // }
        result = 2;
    }

    return result;
}

/*FTP 下载*/
void ftpDownLoad()
{
    LogPrint(LOG_LEVEL_INFO,MODULE_NAME," ftpDownLoad start!");
    
    curl_global_init(CURL_GLOBAL_ALL);
    curlDownHandle = NULL;
    curlDownHandle = curl_easy_init();

    if(curlDownHandle != NULL)
    {
        char* name = basename(UpdateUrl);
        char localUrl[100] = "/mnt/UPDATE/DownloadFilePath/";
        strcat(localUrl, name);
        //下载软件版本
        downLoad(curlDownHandle, UpdateUrl, localUrl);
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " curl_easy_init curlDownHandle fail!");
    }
    // curl_easy_cleanup(curlDownHandle);//free problem?
    curl_global_cleanup();
}

void pthreadFtpUpload()
{
    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " pthreadFtpUpload start");
    while(1)
    {
        sleep(1);
        if(!QueueEmpty(&mQueue))
        {
            ftpUpLoad();
        }
    }
}


/*FTP 上传日志*/
void ftpUpLoad()
{
    LogPrint(LOG_LEVEL_INFO,MODULE_NAME," ftpUpLoad start!\n");
    //上锁，函数是阻塞的
    pthread_mutex_lock(&mute);

    if(access("/mnt/RWD/ObuLog/Obu.tar.gz", F_OK) == 0)
    {
        system("rm -rf /mnt/RWD/ObuLog/Obu.tar.gz");
    }
    else if(access("/mnt/RWD/RsuLog/APP.tar.gz", F_OK) == 0)
    {
        system("rm -rf /mnt/RWD/RsuLog/APP.tar.gz");
    }

    struct upLoadFile_t mUpLoadFile_Temp;
    QueuePop(&mQueue, &mUpLoadFile_Temp);
    
    curl_global_init(CURL_GLOBAL_ALL);
    curlUpLoadHandle = NULL;
    curlUpLoadHandle = curl_easy_init();

    if(curlUpLoadHandle != NULL)
    {
        //查找相应类型以及个数的日志文件，并存储在一个string数组中
        int ret = findFile(mUpLoadFile_Temp.logType, mUpLoadFile_Temp.logAmount);
        if(ret == -1){
            curl_easy_cleanup(curlUpLoadHandle);
            curl_global_cleanup();
            return;
        }
        
        /*将保存的日志文件名进行排序处理以便用于上传日志文件*/
        sortFileName(fileName, mUpLoadFile_Temp.logType);

        char command[200] = {0};
        switch (mUpLoadFile_Temp.logType)
        {
            case 1:
                //切换到ObuLog目录
                chdir("/mnt/RWD/ObuLog");
                strcat(command, "tar -czf Obu.tar.gz");
                break;
            case 2:
                //切换到APPLog目录
                chdir("/mnt/RWD/RsuLog");
                strcat(command, "tar -cvf APP.tar");
                break;
            default:
                break;
        }

        for(int i=0; i<mUpLoadFile_Temp.logAmount; i++)
        {
            strcat(command, " ");
            strcat(command, fileName[i]);
        }
        LogPrint(LOG_LEVEL_INFO,MODULE_NAME," ftpUpLoad -command-:%s\n", command);
        //执行打包压缩处理
        system(command);

        switch (mUpLoadFile_Temp.logType)
        {
            case 1:
                if(access("/mnt/RWD/ObuLog/Obu.tar.gz", F_OK) == 0)
                {
                    char url[200] = {0};
                    struct timeval tv;
                    gettimeofday(&tv,NULL);//获取1970-1-1到现在的时间结果保存到tv中
                    uint64_t sec=tv.tv_sec;
                    uint64_t min=tv.tv_sec/60;
                    struct tm cur_tm;//保存转换后的时间结果
                    localtime_r((time_t*)&sec,&cur_tm);
                    char cur_time[20];
                    snprintf(cur_time,20,"%d%02d%02d%02d%02d%02d",cur_tm.tm_year+1900,cur_tm.tm_mon+1,cur_tm.tm_mday,cur_tm.tm_hour,cur_tm.tm_min,cur_tm.tm_sec);
    
                    strcat(url, mUpLoadFile_Temp.UpdateUrl);
                    strcat(url, "Obu_");
                    strcat(url, cur_time);
                    strcat(url,".tar.gz");

                    char urlName[200] = {0};
                    strcat(urlName, "Obu_");
                    strcat(urlName, cur_time);
                    strcat(urlName,".tar.gz");

                    int ret = upLoad(curlUpLoadHandle, url, "/mnt/RWD/ObuLog/Obu.tar.gz", 3);

                    responseUploadLog(ret, urlName, mUpLoadFile_Temp.logType);
                    if(ret == 0)
                    {
                        system("rm -rf /mnt/RWD/ObuLog/Obu.tar.gz");
                    }
                }
                break;
            case 2:
                if(access("/mnt/RWD/RsuLog/APP.tar.gz", F_OK) == 0)
                {
                    char url[100] = {0};
                    
                    
                    struct timeval tv;
                    gettimeofday(&tv,NULL);//获取1970-1-1到现在的时间结果保存到tv中
                    uint64_t sec=tv.tv_sec;
                    uint64_t min=tv.tv_sec/60;
                    struct tm cur_tm;//保存转换后的时间结果
                    localtime_r((time_t*)&sec,&cur_tm);
                    char cur_time[20];
                    snprintf(cur_time,20,"%d%02d%02d%02d%02d%02d",cur_tm.tm_year+1900,cur_tm.tm_mon+1,cur_tm.tm_mday,cur_tm.tm_hour,cur_tm.tm_min,cur_tm.tm_sec);
    
                    strcat(url, mUpLoadFile_Temp.UpdateUrl);
                    strcat(url, "APP_");
                    strcat(url, cur_time);
                    strcat(url,".tar.gz");

                    char urlName[200] = {0};
                    strcat(urlName, "APP_");
                    strcat(urlName, cur_time);
                    strcat(urlName,".tar.gz");

                    int ret = upLoad(curlUpLoadHandle, url, "/mnt/RWD/RsuLog/APP.tar.gz", 3);

                    responseUploadLog(ret, urlName, mUpLoadFile_Temp.logType);
                    if(ret == 0)
                    {
                        system("rm -rf /mnt/RWD/RsuLog/APP.tar.gz");
                    }
                }
                break;
            
            default:
                break;
        }
        
        // for (int i = 0; i < mUpLoadFile_Temp.logAmount; i++)//每次上传一个日志文件
        // {
        //     char url[100] = {0};
        //     char localurl[50] = {0};
        //     //本地日志文件全路径名拼接
        //     strcat(localurl,upLoadFileLocalUrl);
        //     strcat(localurl, fileName[i]);  
        //     //上传日志
        //     strcat(url, mUpLoadFile_Temp.UpdateUrl);
        //     strcat(url,fileName[i]);

        //     LogPrint(LOG_LEVEL_INFO,MODULE_NAME," ftpUpLoad - url = %s", url);
        //     LogPrint(LOG_LEVEL_INFO,MODULE_NAME," ftpUpLoad - localurl = %s", localurl);
        //     int ret = upLoad(curlUpLoadHandle, url, localurl, 3);

        //     responseUploadLog(ret, fileName[i], mUpLoadFile_Temp.logType);
        // }

        curl_easy_cleanup(curlUpLoadHandle);
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " curl_easy_init curlUpLoadHandle fail!");
    }
    
    curl_global_cleanup();
    //解锁
    pthread_mutex_unlock(&mute);
}

/*文件名数组排序，以便上传最新的日志文件内容*/
// void sortFileName(char name[50][256])
// {
//     LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " sortFileName start!");
//     char tmpStr[256] = {0};
//     for (int i = 0; i< (cnt-1); i++)    //比较m-1次
//     {
//         for (int j = 0; j < (cnt-i-1); j++)   // 最后一次比较a[m-i-1]与a[m-i-2]
//         {
//             if (strcmp(name[j],name[j+1]))    //如果a[j]比a[j+1]大则交换内容
//             {
//                 memset(tmpStr, 0, 256);
//                 strcpy(tmpStr, name[j+1]);
//                 memset(name[j+1], 0, 256);
//                 strcpy(name[j+1], name[j]);
//                 memset(name[j], 0, 256);
//                 strcpy(name[j], tmpStr);
//             }
//         }
//     }

//     //此部分是把 最后一个置于最开始
//     memset(tmpStr, 0, 256);
//     strcpy(tmpStr, name[cnt-1]);
//     for(int i = (cnt-1); i >= 0; i--)
//     {
//         memset(name[i], 0, 256);
//         strcpy(name[i], name[i-1]);
//     }
//     strcpy(name[0], tmpStr);

//     for (int i = 0; i < cnt; i++)
//     {
//         LogPrint(LOG_LEVEL_INFO, MODULE_NAME, " ---fileName---:%s", name[i]);
//     }
// }


/*文件名数组排序，以便上传最新的日志文件内容*/
void sortFileName(char name[50][256], int type)
{
    LogPrint(LOG_LEVEL_INFO,MODULE_NAME," sortFileName start!");
    char temp[50][256] = {0};
    
    if(type == 1)
    {
        strcpy(temp[0], "obu.log");
        for(int i=0; i<(cnt-1); i++)
        {
            char nameStr[10] = {"obu."};
            char itoaStr[5]={0};
            sprintf(itoaStr, "%d", i); 
            strcat(nameStr, itoaStr);
            strcat(nameStr, ".log");
            strcpy(temp[i+1], nameStr);
        }
    }
    else if(type == 2)
    {
        strcpy(temp[0], "APP.txt");
        for(int i=0; i<(cnt-1); i++)
        {
            char nameStr[10] = {"APP."};
            char itoaStr[5]={0};
            sprintf(itoaStr, "%d", i); 
            strcat(nameStr, itoaStr);
            strcat(nameStr, ".txt");
            strcpy(temp[i+1], nameStr);
        }
    }
    for(int i=0; i<cnt; i++){
        strcpy(name[i], temp[i]);
    }
}

/*查找log目录下的文件名
/mnt/RWD/ObuLog/AppLog.txt
/mnt/RWD/ObuLog/obu.log
*/
int findFile(int logType, int logAmount)
{
	LogPrint(LOG_LEVEL_INFO,MODULE_NAME," find log file logType = %d, logAmount =  %d!", logType, logAmount);
	memset(fileName, 0, sizeof(fileName));//清空数组

    int countFlag = 0;
	DIR *pDir = NULL;
	struct dirent * pEnt = NULL;
    char subStr[10] = {0}; 
    cnt = 0;
    memset(upLoadFileLocalUrl, 0, sizeof(upLoadFileLocalUrl));

    switch (logType)
    {
        case 1://应用
            pDir = opendir(APP_LOG_PATH);
            strcat(subStr, "obu");
            strcat(upLoadFileLocalUrl,APP_LOG_PATH);
            break;
        case 2://算法
            pDir = opendir(ALG_LOG_PATH);
            strcat(subStr, "AppLog");
            strcat(upLoadFileLocalUrl,ALG_LOG_PATH);
            break;
        case 3://系统
            pDir = opendir(SYSTEM_LOG_PATH);
            strcat(subStr, "system");
            strcat(upLoadFileLocalUrl,SYSTEM_LOG_PATH);
            break;
        case 4://配置
            pDir = opendir(KEY_CONFIG_LOG_PATH);
            strcat(subStr, "config");
            strcat(upLoadFileLocalUrl,KEY_CONFIG_LOG_PATH);
            break;
        default:
            break;
    }
	
	if (NULL == pDir)
	{
		LogPrint(LOG_LEVEL_ERR,MODULE_NAME," opendir fail!");
		return -1;
	}	

	while (1)
	{
		pEnt = readdir(pDir);
        if(pEnt != NULL)
        {
            if(strstr(pEnt->d_name, subStr) != NULL)
            {
                countFlag = 1;
                strcpy(fileName[cnt], pEnt->d_name);
                LogPrint(LOG_LEVEL_INFO,MODULE_NAME," file -0- name = %s", fileName[cnt]);
                cnt++;
            }
        }
        else
        {
            if(countFlag == 0){
                return -1;
            }
            break;
        }
	}
	return 0;
}


void getCurrentTime(char cur_time[20])
{
    struct timeval tv;
    gettimeofday(&tv,NULL);//获取1970-1-1到现在的时间结果保存到tv中
    uint64_t sec=tv.tv_sec;
    uint64_t min=tv.tv_sec/60;
    struct tm cur_tm;//保存转换后的时间结果
    localtime_r((time_t*)&sec,&cur_tm);
    snprintf(cur_time,20,"%d%02d%02d%02d%02d%02d",cur_tm.tm_year+1900,cur_tm.tm_mon+1,cur_tm.tm_mday,cur_tm.tm_hour,cur_tm.tm_min,cur_tm.tm_sec);
    printf("current time is %s\n",cur_time);//打印当前时间
}



