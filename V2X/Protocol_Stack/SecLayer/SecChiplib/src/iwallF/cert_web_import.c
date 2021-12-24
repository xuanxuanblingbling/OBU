#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "cJSON.h"
#include "common.h"
#include "glib.h"
#include "wj_log.h"
#include "IWALL_V2X_API.h"
#include "Chip_iwallF.h"
#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0])) /*计算数组的大小*/

#define CERT_FILE_SUFFIX ".oer" /*证书文件后缀*/

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9004
#define VALID_CERT_PATH "/mnt/APP/Config/certs/guoqi"
#define CERT_TYPE_PCA 7 //PCA
#define CA_PROVIDER 1   //国汽

/*************************************************
  名称:              ParseRecvJsonData
  描述:              Parse Receive Json Data
  输入参数:           Recv data buf
  输出参数:           Import certs path
  返回值:            success 0 or faild -1
*************************************************/
int32_t ParseRecvJsonData(const char *recvdata, char *importCertPath)
{
    int nRet = -1;

    cJSON *parseRoot = NULL;

    cJSON *levelItem = NULL;
    cJSON *moduleNameItem = NULL;
    cJSON *OperationItem = NULL;

    if (NULL == recvdata)
    {
        return -1;
    }

    parseRoot = cJSON_Parse(recvdata);

    if (parseRoot)
    {
        moduleNameItem = cJSON_GetObjectItem(parseRoot, "ModuleName");
        OperationItem = cJSON_GetObjectItem(parseRoot, "Operation");

        if (moduleNameItem && OperationItem)
        {
            if (strcmp("Cer", moduleNameItem->valuestring) ||
                strcmp("add", OperationItem->valuestring))
            {
                LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Not import path command ");

                nRet = -1;
                goto END;
            }
        }

        levelItem = cJSON_GetObjectItem(parseRoot, "Path");
        if (levelItem)
        {
            memcpy(importCertPath, levelItem->valuestring, strlen(levelItem->valuestring));
            nRet = 0;
        }
        else
        {
            nRet = -1;
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Import path is NULL ! ");
            goto END;
        }
    }
    else
    {
        nRet = -1;
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Parse Json faild ! ");
        goto END;
    }

END:
    if (parseRoot)
    {
        cJSON_Delete(parseRoot);
        parseRoot = NULL;
    }
    return nRet;
}

/*************************************************
  名称:              CreateRespondInfoJson
  描述:              Create Respond Information Json
  输入参数:           Query Json Cmd  Previous operation result
  输出参数:           respond Information Json Buf
  返回值:             success 0 or faild -1
*************************************************/
int32_t CreateRespondInfoJson(char *respondInfoJson, const char *recvJsonData, const int lastResult)
{
    cJSON *parseRoot = NULL;
    char *convertJsonToBuf = NULL;

    if (NULL == respondInfoJson || NULL == recvJsonData)
    {
        return -1;
    }

    parseRoot = cJSON_Parse(recvJsonData);

    if (parseRoot)
    {
        cJSON_AddStringToObject(parseRoot, "Result", "FAIL");
        if (0 == lastResult)
        {
            cJSON_ReplaceItemInObject(parseRoot, "Result", cJSON_CreateString("SUCCESS"));
        }
    }

    convertJsonToBuf = cJSON_Print(parseRoot);
    memcpy(respondInfoJson, convertJsonToBuf, strlen(convertJsonToBuf));

    if (parseRoot)
    {
        cJSON_Delete(parseRoot);
        parseRoot = NULL;
    }

    if (convertJsonToBuf)
    {
        free(convertJsonToBuf);
        convertJsonToBuf = NULL;
    }

    return 0;
}

/*************************************************
  名称:              SocketServer_Init
  描述:              init socket server
  输入参数:           ip / listen port
  返回值:             socket fd
*************************************************/
int32_t SocketServer_Init(const char *ip, const int port)
{
    int sockServer = -1;
    socklen_t reuse = 1;
    int err = -1;

    if (port <= 0)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "server port error ");
        return -1;
    }

    //01 create socket
    sockServer = socket(AF_INET, SOCK_STREAM, 0);

    if (sockServer < 0)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "create socket server faild!");
        return -1;
    }

    //02 init server, fullfill sockaddr_in
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    //set port multiplexing
    setsockopt(sockServer, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    //03 bind socket
    err = bind(sockServer, (struct sockaddr *)&addr, sizeof(addr));

    if (err < 0)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "bind() called failed!");
        return -1;
    }

    //04 set the socket to listen mode, ready to receive client requests
    if (listen(sockServer, 5) < 0)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "listen() called failed!");
        return -1;
    }

    return sockServer;
}

/*将各厂家验证证书导入到芯片中*/
/*************************************************
  名称:              import_certfile_to_chip
  描述:              Now, only import *.oer certs and
  	  	  	  	  	not check cert supplier
  输入参数:           Certs path
  返回值:             faild -1 suceess 0
*************************************************/
static int32_t import_certfile_to_chip(int8_t *dirpath)
{
    GDir *dir = NULL;
    // int32_t i = 0;
    const gchar *filename = NULL;
    gchar *abspath = NULL;
    gchar *filecontent = NULL;
    gsize contentsize = 0;

    int8_t copyValidCertFileCmd[256] = {0};

    dir = g_dir_open((const char *)dirpath, 0, NULL);
    if (NULL == dir)
    {
        LogPrint(LOG_LEVEL_ERR, "test", "directory %s open failed", dirpath);
        return -1;
    }

    while ((filename = g_dir_read_name(dir)))
    {
        LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "file %s in %s", filename, dirpath);

        if (g_str_has_suffix(filename, CERT_FILE_SUFFIX)) /*过滤证书文件*/
        {
            abspath = g_strjoin("/", dirpath, filename, NULL);

            if (g_file_get_contents(abspath, &filecontent, &contentsize, NULL))
            {
                LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "file size %d, name:%s", contentsize, abspath);

                if (0 != IWALL_ImportRootCertificate((unsigned char *)filecontent, contentsize, abspath, CERT_TYPE_PCA, CA_PROVIDER))
                {
                    LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "write %s to chip failed", filename);
                }

                g_free(filecontent);
            }
            else //delete unvalid cert
            {
                sprintf((char *)copyValidCertFileCmd, "rm -r %s", abspath);
                if (0 == system((const char *)copyValidCertFileCmd))
                {
                    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "delete unvalid  cert  succ !");
                }
                else
                {
                    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "delete unvalid  cert  faild !");
                }
            }
        }
    }

    g_dir_close(dir);
    return 0;
}

/*************************************************
  名称:              ImportCertFilesToSecChip
  描述:              Import CertFiles To SecureChip
  输入参数:           Certs path
  返回值:             faild -1 suceess 0
*************************************************/
int32_t ImportCertFilesToSecChip(int8_t *certPath)
{
    if (0 != import_certfile_to_chip(certPath))
    {
        return -1;
    }

    return 0;
}

/*************************************************
  名称:              ProcessClientDataThreadFun
  描述:              Process Client Data Thread Funtion
  输入参数:           NULL
  输出参数:           NULL
  返回值:            Block Funtion, NULL
*************************************************/
static void *ProcessClientDataThreadFun(void *para)
{
    int serverFd = -1;

    int connfd = 0;
    int nRet = -1;

    int8_t importCertsPath[512] = {0};
    int8_t recvbuf[512] = {0};
    int8_t pSendRespond[512] = {0};
    int8_t copyValidCertFileCmd[256] = {0};

    int8_t deleteImpoetCertFileCmd[256] = {0};

    struct sockaddr_in addrClient; //client addr
    // socklen_t sin_size = sizeof(struct sockaddr_in);

    serverFd = SocketServer_Init(SERVER_IP, SERVER_PORT);
    if (-1 == serverFd)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "create serverFd faild ");
        return NULL;
    }

    while (1)
    {
        LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "wait client connect ......");
        connfd = accept(serverFd, NULL, NULL);
        LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "client connect success !!! client ip is: %s ", (inet_ntoa)(addrClient.sin_addr));

        while (connfd)
        {
            nRet = recv(connfd, recvbuf, sizeof(recvbuf), 0);
            nRet = ParseRecvJsonData((const char *)recvbuf, (char *)importCertsPath);
            if (!nRet)
            {
                nRet = ImportCertFilesToSecChip(importCertsPath);
                if (!nRet)
                {
                    sprintf((char *)copyValidCertFileCmd, "cp %s/* %s", importCertsPath, VALID_CERT_PATH);

                    if (0 == system((const char *)copyValidCertFileCmd))
                    {
                        LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "copy  valid cert to specified directory succ\n");
                        sprintf((char *)deleteImpoetCertFileCmd, "rm -r %s/*", importCertsPath);

                        if (0 == system((const char *)deleteImpoetCertFileCmd))
                        {
                            printf("clear ImpoetCertPathFile succ \n");
                            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "clear ImpoetCertPathFile succ\n");
                        }
                        else
                        {
                            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "clear ImpoetCertPathFile faild faild\n");
                        }
                    }
                    else
                    {
                        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "copy  valid cert to specified directory faild");
                    }
                }
                else
                {
                    LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "ImportCertFilesToSecureChip faild");
                }

                CreateRespondInfoJson((char *)pSendRespond, (const char *)recvbuf, nRet);

                if (send(connfd, pSendRespond, strlen((const char *)pSendRespond), 0) < 0)
                {
                    LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "send msg error :%s(errno:%d)", strerror(errno), errno);
                }
            }

            memset(recvbuf, 0, sizeof(recvbuf));

            close(connfd);
            connfd = 0;
        }
    }

    close(serverFd);
}

/*************************************************
  名称:              InitServerThreadFun
  描述:              Init Server Thread Funtion
  输入参数:           NULL
  输出参数:           NULL
  返回值:            Create Thread result
*************************************************/
int32_t InitServerThreadFun()
{
    int32_t nRet = 0;

    pthread_t tid = 0;
    pthread_attr_t attr = {0};

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    nRet = pthread_create(&tid, &attr, ProcessClientDataThreadFun, NULL);
    pthread_attr_destroy(&attr);

    if (0 != nRet)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Create import cert thread faild! ");
        return -1;
    }

    return 0;
}
