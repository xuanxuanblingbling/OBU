#include <mutex>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "StateMonitor.h"
#include "SupervisionSrvIf.h"
#include "ConfigModuleRW.h"
#include "PublicMsg.h"
extern "C"
{
#include "wj_log.h"
}

static TCycleSupervisonMsgQue StatusStatistics = {0};
static TRuntimeSupervisonMsgQue RuntimeStatus = {0};
//used to judge if state has changed
static int flag = 0;
static std::mutex mtx_monitor;

//statistics from net dev
typedef struct DevNetStatus_
{
    uint64_t recv_bytes;
    uint64_t recv_pkgs;
    uint64_t send_bytes;
    uint64_t send_pkg;
} DevNetStatus;

static int GetStatisticsFromNetworkDev(char *pDevName, DevNetStatus *pDevInfo)
{
    char read_buf[2 * 1024];
    int read_bytes;
    char *target_buf_p;
    char *divided_tmp_buf;
    char divided_buf[20];
    int count = 0;

    if (1 > strlen(pDevName) || 100 < strlen(pDevName))
    {
        return -1;
    }
    /* 打开文件，读取文件信息 */
    int dev_fd = open("/proc/net/dev", O_RDONLY | O_EXCL);
    if (-1 == dev_fd)
    {
        return -2;
    }
    lseek(dev_fd, 0, SEEK_SET);
    read_bytes = read(dev_fd, read_buf, sizeof(read_buf));
    if (-1 == read_bytes)
    {
        close(dev_fd);
        return -3;
    }
    read_buf[read_bytes] = '\0';
    /* 定位网口名称所在的位置（目标位置） */
    target_buf_p = strstr(read_buf, pDevName);
    if (target_buf_p == NULL)
    {
        return -4;
    }
    /* 运用空格、制表符、换行符等不需要的字段对读到的文件信息进行分割，然后遍历、搜索、匹配 */
    for (divided_tmp_buf = strtok(target_buf_p, " \t\r\n"); divided_tmp_buf != NULL; divided_tmp_buf = strtok(NULL, " \t\r\n"))
    {
        strcpy(divided_buf, divided_tmp_buf);
        count++;
        /* 第二个字符是接收到的字节数 */
        if (2 == count)
        {
            pDevInfo->recv_bytes = strtoull(divided_buf, NULL, 10);
        }
        /* 第三个字符是接收到的数据包数 */
        if (3 == count)
        {
            pDevInfo->recv_pkgs = strtoull(divided_buf, NULL, 10);
        }
        /* 第十个字符是发送的字节数 */
        if (10 == count)
        {
            pDevInfo->send_bytes = strtoull(divided_buf, NULL, 10);
        }
        /* 第十一个字符是发送的数据包数 */
        if (11 == count)
        {
            pDevInfo->send_pkg = strtoull(divided_buf, NULL, 10);
            break;
        }
    }
    close(dev_fd);
    return 0;
}

// static int GetV2xStatus()
// {
//     char cmd[2][64] = {"dmesg | grep \"V2X TX status is active\"",
//                        "dmesg | grep \"V2X RX status is active\""};
//     int ret = 0;
// int i = 0;
//     for ( i = 0; i < 2; i++)
//     {
//         FILE *fp = popen(cmd[i], "r");
//         if (NULL == fp)
//         {
//             ret = -2;
//             break;
//         }

//         char buff[100] = {0};
//         int cnt = fread(buff, 1, 100, fp);
//         pclose(fp);
//         fp = NULL;

//         if (0 == cnt) //command not get content
//         {
//             ret = -1;
//             break;
//         }
//     }
//     return ret;
// }

//发送消息队列消息数量 累计条数
void UpdateTxQueDataNum()
{
    // std::lock_guard<std::mutex> lk(mtx_monitor);
    StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64TxQueDataNum++;
}

//消息层发送队列成功处理的消息数量 条数（发送总包数）
void UpdateMsglayerTxDataNum()
{
    // std::lock_guard<std::mutex> lk(mtx_monitor);
    StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64MsglayerTxDataNum++;
}
//消息层发送队列成功处理的消息数量 条数（发送总包数总字节数）
void UpdateMsglayerTxDatabyte(int Byte)
{
    // std::lock_guard<std::mutex> lk(mtx_monitor);
    StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64MsglayerTxDatabyte =
        (StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64MsglayerTxDatabyte + (uint64)Byte) & 0xFFFFFFFFFFFFFFFF;
}

//消息层各个消息类型发送成功的消息数量 条数
//MsgType--bsm:0, map:1, rsm:2, spat:3, rsi:4, transparent:5
void UpdateMsglayerTxData(int MsgType)
{
    // std::lock_guard<std::mutex> lk(mtx_monitor);
    StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64MsglayerTxDataArray[MsgType]++;
}

void UpdateMsglayerTxDataHelper(int FrameMsgType)
{

    switch (FrameMsgType)
    {
    case MSG_MessageFrame_ID_MAPDATA:
    {
        UpdateMsglayerTxData(1);
        break;
    }
    case MSG_MessageFrame_ID_BSM:
    case MSG_MessageFrame_ID_BSM_OrdinaryConven:
    case MSG_MessageFrame_ID_BSM_OrdinaryEvent:
    case MSG_MessageFrame_ID_BSM_SpecialConven:
    case MSG_MessageFrame_ID_BSM_SpecialEvent:
    {
        UpdateMsglayerTxData(0);
        break;
    }
    case MSG_MessageFrame_ID_RSI:
    case MSG_MessageFrame_ID_RSI_RoadStatic:
    case MSG_MessageFrame_ID_RSI_RoadHalfStatic:
    case MSG_MessageFrame_ID_RSI_RoadDynamic:
    {
        UpdateMsglayerTxData(4);
        break;
    }
    case MSG_MessageFrame_ID_SPAT:
    {
        UpdateMsglayerTxData(3);
        break;
    }
    case MSG_MessageFrame_ID_RSM:
    {
        UpdateMsglayerTxData(2);
        break;
    }
    default:
    {
        break;
    }
    }
}

//安全层发送队列成功处理的消息数量 条数
void UpdateSeclayerTxDataNum()
{
    // std::lock_guard<std::mutex> lk(mtx_monitor);
    StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64SeclayerTxDataNum++;
}

// 消息层接收队列成功接收字节数（成功收到的数据字节数）
void UpdateMsglayerRxDatabyte(int Byte)
{
    // std::lock_guard<std::mutex> lk(mtx_monitor);
    StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64MsglayerRxDatabyte =
        (StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64MsglayerRxDatabyte + (uint64)Byte) & 0xFFFFFFFFFFFFFFFF;
}
// 消息层接收队列成功处理的消息数量 条数（成功收到的总包数）
void UpdateMsglayerRxDataNum()
{
    // std::lock_guard<std::mutex> lk(mtx_monitor);
    StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64MsglayerRxDataNum++;
}

//MsgType--bsm:0, map:1, rsm:2, spat:3, rsi:4, transparent:5
void UpdateMsglayerRxData(int MsgType)
{
    // std::lock_guard<std::mutex> lk(mtx_monitor);
    StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64MsglayerRxDataArray[MsgType]++;
}

void UpdateMsglayerRxDataHelper(int FrameMsgType)
{

    switch (FrameMsgType)
    {
    case MSG_MessageFrame_ID_MAPDATA:
    {
        UpdateMsglayerRxData(1);
        break;
    }
    case MSG_MessageFrame_ID_BSM:
    case MSG_MessageFrame_ID_BSM_OrdinaryConven:
    case MSG_MessageFrame_ID_BSM_OrdinaryEvent:
    case MSG_MessageFrame_ID_BSM_SpecialConven:
    case MSG_MessageFrame_ID_BSM_SpecialEvent:
    {
        UpdateMsglayerRxData(0);
        break;
    }
    case MSG_MessageFrame_ID_RSI:
    case MSG_MessageFrame_ID_RSI_RoadStatic:
    case MSG_MessageFrame_ID_RSI_RoadHalfStatic:
    case MSG_MessageFrame_ID_RSI_RoadDynamic:
    {
        UpdateMsglayerRxData(4);
        break;
    }
    case MSG_MessageFrame_ID_SPAT:
    {
        UpdateMsglayerRxData(3);
        break;
    }
    case MSG_MessageFrame_ID_RSM:
    {
        UpdateMsglayerRxData(2);
        break;
    }
    default:
    {
        break;
    }
    }
}

void UpdateSeclayerRxDataNum()
{
    // std::lock_guard<std::mutex> lk(mtx_monitor);
    StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64SeclayerRxDataNum++;
}

void UpdateNetlayerRxDataNum()
{
    // std::lock_guard<std::mutex> lk(mtx_monitor);
    StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64NetlayerRxDataNum++;
}

///////////////////////////////////////

void UpdateV2XStatus(int8 V2xStatus)
{
    std::lock_guard<std::mutex> lk(mtx_monitor);
    RuntimeStatus.m_tModuleRuntimeStatusList.RuntimeStatus.m_tV2XStackRuntimeStatus.m_n8V2XStatus = V2xStatus;
    flag = 1;
}

void UpdateSafetyCertStatus(int8 CertStatus)
{
    std::lock_guard<std::mutex> lk(mtx_monitor);
    if (CertStatus !=
        RuntimeStatus.m_tModuleRuntimeStatusList.RuntimeStatus.m_tV2XStackRuntimeStatus.m_u8SafetyCertStatus)
    {
        flag = 1;
    }
    RuntimeStatus.m_tModuleRuntimeStatusList.RuntimeStatus.m_tV2XStackRuntimeStatus.m_u8SafetyCertStatus = CertStatus;
}

//thread for sending msg type: TCycleSupervisonMsgQue
static void *ThreadProcV2xRunTimeStatusMonitor(void *)
{
    DevNetStatus DevInfo;
    while (1)
    {
        if (ProtocolStackParamConfig.thirdPartyLibConfig.StateMonitorConfig == 1)
        {
            sleep(2);
            int ret = GetStatisticsFromNetworkDev((char *)"rmnet_data1", &DevInfo);
            if (0 == ret)
            {
                StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64PC5RxDatabyte = DevInfo.recv_bytes; //PC5接收总字节数
                StatusStatistics.m_tModuleCycleStatusList.ModuleStatus.m_tV2XStackCycleStatus.m_u64PC5TxDatabyte = DevInfo.send_bytes; //PC5发送成功字节数
            }
            LogPrint(LOG_LEVEL_DEBUG, "StatusMonitor_Debug", "V2X status : %d\n",
                     RuntimeStatus.m_tModuleRuntimeStatusList.RuntimeStatus.m_tV2XStackRuntimeStatus.m_n8V2XStatus);
            //send statistics out
            StatusStatistics.m_n64MsgType = 1;
            StatusStatistics.m_tModuleCycleStatusList.m_enumModuleType = MODULE_V2XSTACK;

            key_t key = ftok(SUPERVISION_FTOK_PATH, FTOK_SUPERVISION_ID);
            int msgid = msgget(key, 0666 | IPC_CREAT);
            if (msgid == -1)
            {
                LogPrint(LOG_LEVEL_ERR, "StatusMonitor_Err", "open msg error");
                continue;
            }
            ret = msgsnd(msgid, &StatusStatistics, sizeof(StatusStatistics) - sizeof(long), IPC_NOWAIT);

            LogPrint(LOG_LEVEL_DEBUG, "StatusMonitor_Debug", "msgsnd() ret: %d\n", ret);
            //not always send
            {
                std::lock_guard<std::mutex> lk(mtx_monitor);
                if (1 == flag)
                {
                    RuntimeStatus.m_n64MsgType = 2;
                    RuntimeStatus.m_tModuleRuntimeStatusList.m_enumModuleType = MODULE_V2XSTACK;
                    msgsnd(msgid, &RuntimeStatus, sizeof(RuntimeStatus) - sizeof(long), IPC_NOWAIT);
                    flag = 0;
                }
            }
        }
        else
        {
            sleep(60);
            LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "Net CBR----------------------------CBR =%f%% ", CurrentCBR);

            LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "Net Recv Start----------------------------NetRecvStart = %d", NetRecvStart);
            LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "Net Recv End--------------NetRecvError = %d,NetRecvEnd = %d", NetRecvError, NetRecvEnd);

            LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "Sec Recv Start-----------SecRecvStart = %d", SecRecvStart);
            LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "Sec Recv Dis-----------SecDiscarded = %d,SecDiscardedRate =%f%%",
                     (SecRecvDis), SecDiscardedRate);
            LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "Sec Recv End--------------SecRecvError = %d,SecRecvEnd = %d", SecRecvError, SecRecvEnd);

            LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "Msg Recv Start-----------MsgRecvStart = %d", MsgRecvStart);
            LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "Msg Recv Dis-----------MsgDiscarded = %d,MsgDiscardedRate =%f%%",
                     (SecRecvEnd - MsgRecvStart), MsgDiscardedRate);
            LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "Msg Recv End--------------MsgRecvError = %d,MsgRecvEnd = %d ", MsgRecvError, MsgRecvEnd);
        }
    }
}

int StartV2xRunTimmeMonitor()
{
    pthread_t th;
    int ret = pthread_create(&th, NULL, ThreadProcV2xRunTimeStatusMonitor, NULL);
    if (ret != 0)
    {
        return -1;
    }
    pthread_detach(th);
    return 0;
}