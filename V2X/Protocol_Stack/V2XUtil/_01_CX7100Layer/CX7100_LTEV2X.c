
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//包含配置文件头文件
#include "ConfigModuleRW.h"
#include "wj_log.h"
#include "ipcq.h"
#include "v2x-status.h"
#include "V2XInterface.h"

static int sockfd = 0;
static void (*CX7100_LTEV2X_FunRecvData)(RecvCallbackReturnInfo CallbackReturnInfo);
static int g_nV2XStatus = 0;
static float g_fCBRStatus = 0;
static char g_n8DummyPacketBuf1[MAX_DUMMY_PACKET_LEN];
static char g_n8DummyPacketBuf2[MAX_DUMMY_PACKET_LEN];
static RecvCallbackReturnInfo g_ag15CallbackReturnInfo;
static int rx_len = 0;
static int rx_count = 0; // number of packets to RX or TX. -1 = indefinite.
static int tx_count = 0; // number of tx packets
#define DELAY_MS 100
#define POWER 23 //发送功率
typedef enum
{
    V2X_INACTIVE = 0,   /**< V2X communication is disabled. */
    V2X_ACTIVE,         /**< V2X communication is enabled. Transmit and
                              receive are possible. */
    V2X_TX_SUSPENDED,   /**< Small loss of timing precision occurred.                                                       Transmit is no longer supported. */
    V2X_RX_SUSPENDED,   /**< Radio can no longer receive any messages. */
    V2X_TXRX_SUSPENDED, /**< Radio can no longer transmit or receive, for
                              some reason. @newpage */
} v2x_event_t;

typedef struct PC5Heard
{
    unsigned char sync[2];              //帧边界，固定：Sync[0] : 0xF3 Sync[1] : 0x64
    unsigned short length;              //该条消息的总长度，不包括 sync 和 length,Length：发送可以不填写
    unsigned char source_l2_id[4];      //源 UE ID，低 24 个比特有效，是 UE 自己分配给自己的，为安全考虑，需定时变化。每个终端的源 UE ID 必须唯一不重复。
    unsigned char destination_l2_id[4]; //目的 UE 的 ID，低 24 个比特有效，DestinationLayer - 2 ID(s) 和 V2X 业务存在映射关系。
    unsigned short period;              //应 用 数 据 的 生 成 周 期 ， 取 值 范 围 ：{20, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 10 00} ，单位 ms设置为 0，表示非周期性数据
    unsigned char power;                //PC5 口发送功率，txPower-r14，integer[-30，23]，单位是 dBm对于接收端，此字段为保留字段。
    unsigned char pppp;                 //数据发送优先级,取值范围 integer[1，8]，数值越小，优先级越大
    unsigned char snr;                  //CP->AP(接收)：信噪比，取值范围：[-30,+50]dB,AP->CP(发送)：保留字段
    unsigned char cbr;                  //CP->AP(接收)：放大100 倍，取值范围 integer[0，100]，AP->CP(发送)：保留字段
    unsigned short data_length;         //AP->CP(发送)：真正需要发送的数据长度，数值范围：[1,3800]
    //CP->AP(接收)：真正接收的数据长度，数值范围：[0,3800]，length=20，data_length=0 时，意味着是单独的CBR上报，
    //source_l2_id、destination_l2_id、 period、power、pppp、snr 都是无效数据，只有cbr是有数值的
} PC5Heard_t;

typedef struct
{
    const char *const host_ip;
    const char *const peer_ip;

    unsigned int host_port;
    unsigned int peer_port;

    struct sockaddr_in host_addr;
    struct sockaddr_in peer_addr;
} ip_service;
static ip_service g_ip_service = {.host_ip = "192.168.0.100",
                                  .peer_ip = "192.168.0.2",
                                  .host_port = 30208,
                                  .peer_port = 30208};

pthread_mutex_t g_mutex_V2XSendData;

extern void UpdateV2XStatus(int8_t V2xStatus);

static void termination_handler(int signum)
{

    LogPrint(LOG_LEVEL_DEBUG, "V2XUtil_Debug", "Got signal %d, tearing down all services", signum);
    IpcQueueSendingAbnormalMsg();
    UpdateV2XStatus((int8_t)V2X_INACTIVE);
    if (sockfd != 0)
    {
        close(sockfd);
        sockfd = -1;
    }
    signal(signum, SIG_DFL);
    raise(signum);
}

static void install_signal_handler()
{
    struct sigaction new_action, old_action;

    new_action.sa_handler = termination_handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;

    sigaction(SIGINT, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
    {
        sigaction(SIGINT, &new_action, NULL);
    }
    sigaction(SIGHUP, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
    {
        sigaction(SIGHUP, &new_action, NULL);
    }
    sigaction(SIGTERM, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
    {
        sigaction(SIGTERM, &new_action, NULL);
    }
}

static int LTE_V2X_ParamInit()
{
    memset(&g_ip_service.peer_addr, 0, sizeof(g_ip_service.peer_addr));
    g_ip_service.peer_addr.sin_family = AF_INET;
    //g_ip_service.peer_addr.sin_addr.s_addr = inet_addr(g_ip_service.peer_ip);
    g_ip_service.peer_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    g_ip_service.peer_addr.sin_port = htons(g_ip_service.peer_port);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        printf("socket error.\n");
        return -1;
    }

    int optval = 1;
    if (0 != setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval)))
    {
        printf("[ip]: setsockopt BROADCAST error !\n");
        return -1;
    }
    optval = 1;
    if (0 != setsockopt(sockfd, SOL_SOCKET, SO_NO_CHECK, &optval, sizeof(optval)))
    {
        printf("[ip]: setsockopt BROADCAST error !\n");
        return -1;
    }
    optval = 1;
    if (0 != setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
    {
        printf("[ip]: TCP server setsockopt addrreused error !\n");
        return -1;
    }

    //设置 socket为非阻塞
    // if (0 != fcntl(sockfd, F_SETFL, O_NONBLOCK))
    // {
    //     printf("[ip]: fcntl  error !\n");
    //     return -1;
    // }

    if (bind(sockfd, (struct sockaddr *)&g_ip_service.peer_addr, sizeof(g_ip_service.peer_addr)) == -1)
    {
        printf("bind error. \n");
        close(sockfd);
        return -1;
    }

    memset(&g_ip_service.host_addr, 0, sizeof(g_ip_service.host_addr));
    g_ip_service.host_addr.sin_family = AF_INET;
    g_ip_service.host_addr.sin_addr.s_addr = inet_addr(g_ip_service.host_ip);
    g_ip_service.host_addr.sin_port = htons(g_ip_service.host_port);

    if (connect(sockfd, (struct sockaddr *)&g_ip_service.host_addr, sizeof(g_ip_service.host_addr)) == -1)
    {
        printf("connect error.\n");
        close(sockfd);
        return -1;
    }

    return 0;
}

static int LTE_V2X_Tx_SendData(char *p_pSendData, int nDataLen)
{
    int write_len = 0;
    int try_counts = 0;

    unsigned char *bp;
    unsigned int len_res;

    if (sockfd <= 0)
    {
        printf("fd(%d) is not valid.\n", sockfd);
        return -1;
    }

    if (!p_pSendData)
    {
        printf("p_pSendData is null");
        return -1;
    }

    if (nDataLen <= 0)
    {
        printf("nDataLen (%d) is not valid.\n", (int)nDataLen);
        return -1;
    }

    bp = (unsigned char *)p_pSendData;
    len_res = (unsigned int)nDataLen;

    while (try_counts < 100)
    {
        if (len_res == 0)
            break;

        write_len = write(sockfd, bp, len_res);

        if (write_len < 0)
        {
            printf("write to device failure error:%d-%s. fd:%d.\n", errno, strerror(errno), sockfd);
            usleep(10 * 1000);
            try_counts++;
            continue;
        }

        if ((unsigned int)write_len != len_res)
        {
            bp += write_len;
            len_res -= write_len;
            usleep(10 * 1000);
            try_counts++;
            continue;
        }
        else
        {
            break;
        }
    }

    if (try_counts >= 100)
    {
        printf("write to device failure (timeout) len_res:%d, fd: [%d].\n", len_res, sockfd);
        return -1;
    }

    return write_len;
}

static int sample_rx(int rx_sock)
{
    int rc = 0;
    PC5Heard_t pc5Heard;
    int structLen = sizeof(PC5Heard_t);
    bzero(g_ag15CallbackReturnInfo.p_cRecvBuf, MAX_DUMMY_PACKET_LEN);
    rc = read(rx_sock, g_ag15CallbackReturnInfo.p_cRecvBuf, MAX_DUMMY_PACKET_LEN);
    if (rc < 0)
    {
        return rc;
    }
    if (rc >= structLen)
    {
        memcpy(&pc5Heard, &g_ag15CallbackReturnInfo.p_cRecvBuf[0], structLen);
        //printf("%s %d pc5Heard.length = %d,data_length = %d,rc - structLen = %d\n", __FUNCTION__, __LINE__, pc5Heard.length, pc5Heard.data_length, rc - structLen);
        g_fCBRStatus = pc5Heard.cbr;
        //printf("%s %d g_fCBRStatus = %f\n", __FUNCTION__, __LINE__, g_fCBRStatus);

        if ((CX7100_LTEV2X_FunRecvData != NULL) && (pc5Heard.data_length > 0))
        {
            g_ag15CallbackReturnInfo.Current_CBR = g_fCBRStatus;
            memcpy(&g_ag15CallbackReturnInfo.p_cRecvBuf[0], &g_ag15CallbackReturnInfo.p_cRecvBuf[structLen], sizeof(g_ag15CallbackReturnInfo.p_cRecvBuf));
            g_ag15CallbackReturnInfo.pnRecvBufSize = pc5Heard.data_length;
            g_ag15CallbackReturnInfo.pppp = 0x01;
            CX7100_LTEV2X_FunRecvData(g_ag15CallbackReturnInfo);
        }
    }
    rx_count++;
    rx_len = rc;
    return rc;
}

static int getCBR_rx(int rx_sock)
{
    int rc = 0;
    PC5Heard_t pc5Heard;
    int structLen = sizeof(PC5Heard_t);
    bzero(g_n8DummyPacketBuf2, MAX_DUMMY_PACKET_LEN);
    rc = read(rx_sock, g_n8DummyPacketBuf2, MAX_DUMMY_PACKET_LEN);
    if (rc < 0)
    {
        return rc;
    }
    if (rc >= structLen)
    {
        memcpy(&pc5Heard, &g_n8DummyPacketBuf2[0], structLen);
        //printf("%s %d pc5Heard.length = %d,data_length = %d,rc - structLen = %d\n", __FUNCTION__, __LINE__, pc5Heard.length, pc5Heard.data_length, rc - structLen);
        g_fCBRStatus = pc5Heard.cbr;
        //printf("%s %d g_fCBRStatus = %f\n", __FUNCTION__, __LINE__, g_fCBRStatus);
    }
    return rc;
}

static int sample_rxTest(int rx_sock)
{
    int rc = 0;
    PC5Heard_t pc5Heard;
    int structLen = sizeof(PC5Heard_t);
    bzero(g_n8DummyPacketBuf1, MAX_DUMMY_PACKET_LEN);
    rc = read(rx_sock, g_n8DummyPacketBuf1, MAX_DUMMY_PACKET_LEN);
    if (rc < 0)
    {
        return rc;
    }
    if (rc > structLen)
    {
        memcpy(&pc5Heard, &g_n8DummyPacketBuf1[0], structLen);
        //printf("%s %d pc5Heard.length = %d,data_length = %d,rc - structLen = %d\n", __FUNCTION__, __LINE__, pc5Heard.length, pc5Heard.data_length, rc - structLen);
        g_fCBRStatus = pc5Heard.cbr;
        return rc;
    }
    return 0;
}

void *Thread_CX7100_StatusCheck(void *arg)
{
    int nRet = 0, num = 0, ret = 0;

    while (1)
    {
        //检查周期90秒，若连续出现3次不正常，则会有30秒停止发送，待下次正常后，继续发送
        sleep(30);
        nRet = CheckV2xState();
        if (nRet < 0)
        {
            LogPrint(LOG_LEVEL_WARN, "V2XUtil_Warn", "CheckV2xState() = %d", nRet);
            num += 1;
            //连续出现3次不正常，则停止发送、接收
            if (num == 3)
            {
                g_nV2XStatus = V2X_INACTIVE;
                ProtocolStackParamConfig.v2xStatusFlag.v2xStatus = V2X_INACTIVE;
                IpcQueueSendingAbnormalMsg();
                UpdateV2XStatus((int8_t)V2X_INACTIVE);
                continue;
            }
            //连续出现4次不正常，则关闭套接字，待下次正常后重新初始化套接字
            else if (num == 4)
            {
                V2X_Close();
                num = 0;
                continue;
            }
        }
        else
        {
            LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "CheckV2xState() = %d", nRet);
            num = 0;
            if (sockfd == -1)
            {
                //初始化接口
                ret = LTE_V2X_ParamInit();
            }
            if (ProtocolStackParamConfig.v2xStatusFlag.v2xStatus != V2X_ACTIVE && ret == 0)
            {
                g_nV2XStatus = V2X_ACTIVE;
                LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "v2x_radio Init Success = %d", g_nV2XStatus);
                ProtocolStackParamConfig.v2xStatusFlag.v2xStatus = V2X_ACTIVE;
                IpcQueueSendingActiveMsg();
                UpdateV2XStatus((int8_t)V2X_ACTIVE);
            }
        }
        sleep(60);
    }

    pthread_detach(pthread_self());
    return NULL;
}

void *Thread_CX7100_Init(void *arg)
{
    int Init = 0;
    int nRet = 0;
    install_signal_handler();
    ProtocolStackParamConfig.v2xStatusFlag.v2xStatus = g_nV2XStatus;
    LogPrint(LOG_LEVEL_DEBUG, "Stack_Rx_Debug", "Thread_CX7100_Init() loop is start %d  ", pthread_self());
    while (1)
    {
        sleep(1);
        if (Init == 0)
        {
            //判断data0 data1 成功启动
            // if (LTE_V2X_ParamInit() != 0)
            // {
            //     LogPrint(LOG_LEVEL_DEBUG, "V2XUtil_Warn", "LTE_V2X_ParamInit error");
            //     continue;
            // }
            // else
            {
                Init = 1;
            }
        }
        if (Init == 1)
        {
            //判断GNSS状态是否正常，设置级联RSU后，级联设备无gnss状态下，也能接收、发送数据，此处级联设备暂不检查gnss状态，只检查主机设备
            nRet = CheckV2xState();
            if (nRet <= 0)
            {
                LogPrint(LOG_LEVEL_WARN, "V2XUtil_Warn", "CheckV2xState() = %d", nRet);
                continue;
            }
            else
            {
                Init = 2;
            }
        }
        if (Init == 2)
        {
            //初始化接口
            if (LTE_V2X_ParamInit() == 0)
            {
                g_nV2XStatus = V2X_ACTIVE;
                Init = 3;
                LogPrint(LOG_LEVEL_DEBUG, "V2XUtil_Debug", "v2x_radio Init Success = %d", Init);
            }
        }

        LogPrint(LOG_LEVEL_DEBUG, "V2XUtil_Debug", "g_nV2XStatus = %d", g_nV2XStatus);
        if (g_nV2XStatus == V2X_ACTIVE)
        {
            ProtocolStackParamConfig.v2xStatusFlag.v2xStatus = g_nV2XStatus;
            int ret = IpcQueueSendingActiveMsg();
            LogPrint(LOG_LEVEL_DEBUG, "V2XUtil_Debug", "IpcQueueSendingActiveMsg() %d", ret);
            pthread_t tid = 0;
            pthread_create(&tid, NULL, Thread_CX7100_StatusCheck, NULL);
            break;
        }
    }
    pthread_detach(pthread_self());
    return NULL;
}

int LTEV2X_Init()
{
    pthread_t tidp_Init;
    pthread_attr_t attr = {0};
    struct sched_param param = {0};

    pthread_attr_init(&attr);

    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    param.sched_priority = 94;
    pthread_attr_setschedparam(&attr, &param);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    int nRet = pthread_create(&tidp_Init, NULL, Thread_CX7100_Init, NULL);
    if (nRet != 0)
    {
        return -1;
    }
    pthread_attr_destroy(&attr);
    return nRet;
}

DLL_PUBLIC int V2X_SendData(SendDataInfo ag15SendDataInfo, SendDataReturnInfo *ag15SendDataReturnInfo)
{
    if (g_nV2XStatus != V2X_ACTIVE)
    {
        LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "AG15_LTEV2X_SendData g_nV2XStatus = %d", g_nV2XStatus);
        return -1;
    }
    if (NULL == ag15SendDataReturnInfo)
    {
        LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "AG15_LTEV2X_SendData ag15SendDataReturnInfo is NULL");
        return -1;
    }
    pthread_mutex_lock(&g_mutex_V2XSendData);

    PC5Heard_t pc5Heard;
    int structLen = sizeof(PC5Heard_t);
    memset(&pc5Heard, 0x00, structLen);
    unsigned char sendBuf[5000] = {0};

    pc5Heard.sync[0] = 0xF3;
    pc5Heard.sync[1] = 0x64;
    pc5Heard.source_l2_id[0] = ag15SendDataInfo.SourceLayer2ID[2];
    pc5Heard.source_l2_id[1] = ag15SendDataInfo.SourceLayer2ID[1];
    pc5Heard.source_l2_id[2] = ag15SendDataInfo.SourceLayer2ID[0];
    pc5Heard.destination_l2_id[0] = ag15SendDataInfo.DestinationLayer2ID[2];
    pc5Heard.destination_l2_id[1] = ag15SendDataInfo.DestinationLayer2ID[1];
    pc5Heard.destination_l2_id[2] = ag15SendDataInfo.DestinationLayer2ID[0];
    pc5Heard.period = DELAY_MS;
    pc5Heard.power = POWER;
    pc5Heard.pppp = ag15SendDataInfo.pppp;
    pc5Heard.data_length = ag15SendDataInfo.p_nLen;

    memcpy(&sendBuf[0], (unsigned char *)&pc5Heard, structLen);
    memcpy(&sendBuf[structLen], ag15SendDataInfo.p_pcBuf, ag15SendDataInfo.p_nLen);
    int sendLen = ag15SendDataInfo.p_nLen + structLen;

    // printf("%s %d sendLen = %d\n", __FUNCTION__, __LINE__, sendLen);
    // int i = 0;
    // for (i = 0; i < sendLen; i++)
    // {
    //     printf("%02x ", sendBuf[i]);
    // }
    // printf("\n");

    int bytes_sent = LTE_V2X_Tx_SendData((char *)sendBuf, sendLen);
    if (bytes_sent > 0)
    {
        tx_count++;
        ag15SendDataReturnInfo->sendLen = bytes_sent;
        ag15SendDataReturnInfo->Current_CBR = g_fCBRStatus;
    }
    else
    {
        bytes_sent = -1;
    }
    pthread_mutex_unlock(&g_mutex_V2XSendData);
    return bytes_sent;
}

void *Thread_Read_CX7100_LTEData(void *arg)
{
    while (1)
    {
        if (g_nV2XStatus == V2X_ACTIVE)
        {
            if (ProtocolStackParamConfig.messageParamConfig.recvParamConfig.RecvSwitch == 1)
            {
                sample_rx(sockfd);
                usleep(1);
            }
            else
            {
                getCBR_rx(sockfd);
                usleep(100 * 1000);
            }
        }
        else
        {
            sleep(1);
        }
    }
    pthread_detach(pthread_self());
    return NULL;
}

int LTEV2X_Rx_SetDevParam(void (*pFunRecvData)(RecvCallbackReturnInfo CallbackReturnInfo))
{
    CX7100_LTEV2X_FunRecvData = pFunRecvData;

    pthread_t tidp_Read_LTEData;
    pthread_attr_t attr = {0};
    struct sched_param param = {0};

    pthread_attr_init(&attr);

    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    param.sched_priority = 94;
    pthread_attr_setschedparam(&attr, &param);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    //开启接收线程接收tcp传来的数据
    int ret = pthread_create(&tidp_Read_LTEData, &attr, Thread_Read_CX7100_LTEData, NULL);
    if (ret != 0)
    {
        return -1;
    }
    pthread_attr_destroy(&attr);
    return 0;
}

DLL_PUBLIC int V2X_Close()
{
    LogPrint(LOG_LEVEL_INFO, "V2XUtil_Warn", "V2X_Close");
    if (sockfd != 0)
    {
        close(sockfd);
        sockfd = -1;
    }
    return 0;
}
DLL_PUBLIC float V2X_GetCBR()
{
    return g_fCBRStatus;
}

DLL_PUBLIC int V2X_TxRx_Init(pFunRecvData MsgRx_CallBack)
{
    int ret = 0;

    //初始化互斥信号量
    pthread_mutex_init(&g_mutex_V2XSendData, NULL);

    ret = LTEV2X_Rx_SetDevParam(MsgRx_CallBack);
    if (ret < 0)
    {
        return ret;
    }

    ret = LTEV2X_Init();
    return ret;
}
