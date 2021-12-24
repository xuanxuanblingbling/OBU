#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "tsp_file.h"
#include "websockets.h"
#include "queue.h"
#include "SWversynchronise.h"

#define TSP_SOFTVERSION "WJ_OBU_TSP_20210831"

// pthread_t selfCarpt; //用于自车信息上传，线程
pthread_t faultMsg_id; //用于上传故障信息，线程
/*************************************************
  名称:main
  描述: 
  输入参数:
  输出参数:
  返回值:  
**************************************************/
int main()
{
  uint8 mCount = 0;
  int ret;

  //zlog初始化
  if(0 != LogInit())
  {
    LogPrint(LOG_LEVEL_ERR,MODULE_NAME," log module init failed");
    return -1;
  }

  //软件版本号同步
  ret = SW_versionsync(MODULE_NAME, TSP_SOFTVERSION);
  LogPrint(LOG_LEVEL_INFO,MODULE_NAME,"software synchonise result %d ",ret);

  /*初始化队列，用于存储请求日志的内容*/
  initQueue(&mQueue);

  /*与平台建立 websocket 连接，以此进行数据通信等操作*/
  webInit();

  /*用于上传日志线程*/
  if(pthread_create(&upLoadId, NULL, (void *)pthreadFtpUpload, NULL) != 0)
  {
      LogPrint(LOG_LEVEL_ERR, MODULE_NAME, " thread creation failed！");
  }

  // /*自车信息上传*/
  // initTimer();//每5s一次进行读取配置文件查询相关信息
  mselfCarMsg.mrsctl = 0;//将上传自车信息的帧序号设置为0

  /*单独开辟线程占用很大空间*/
  // if(pthread_create(&faultMsg_id, NULL, (void *)faultMsgThread, NULL) != 0) 
  // {
  //   printf("thread creation failed！\n");
  // }

  while (1)
	{
    ++mCount;

    if(0 == (mCount%3))
    {
      /*故障信息,3s一次上传（GPS是3s周期）*/
      faultMsg();
    }

    if(0 == (mCount%5)){
      /*运行状态信息上传，周期5s上传。*/
      runStateData();
    }
    
    sleep(1);
    // if(0 == (mCount%2))
    // {
    //   LogPrint(LOG_LEVEL_INFO,MODULE_NAME," service is running \n");
    // }
    // if(mCount == 10)
    // {
    //   // /*二期，自车信息上传*/
    //   // if(pthread_create(&selfCarpt, NULL, (void *)selfCarMsg, NULL) != 0) 
    //   // {
    //   //   printf("thread creation failed！\n");
    //   // }

    //   // setFTPConfig(0x8001, "0.1", "ftp://106.120.201.126:19350/obuLog/", "v2x-obu-back", "v2x-obu-back");
    // }
  }

  LogDeinit();

  return 0;
}




