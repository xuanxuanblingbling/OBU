//#include <telux/cv2x/legacy/v2x_radio_api.h>

#include <signal.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include "V2XInterface.h"
#include "ipcq.h"
#include "Include/v2x_radio_api.h"
#include "wj_log.h"
#include "v2x-status.h"

//包含配置文件头文件
#include "ConfigModuleRW.h"

// Regarding these sample port#: any unused ports could be selected, and additional ports
// could also be set-up for additional reservations and near unlimited number of event flows.
#define SAMPLE_SPS_PORT (2500)
#define SAMPLE_EVENT_PORT (2501)

//const char default_loopback_iface_name[] = "lo";
static const char g_aDefault_v2x_non_ip_iface_name[] = "rmnet_data1";
//const char default_db820_ethernet_name[] = "enP2p1s0";

#ifdef SIM_BUILD
static char g_aDest_ipv6_addr_str[50] = "::1";
#else
static char g_aDest_ipv6_addr_str[50] = "ff02::1";
#endif

//uint16_t cla_portnum = 0; // CLA command line argument for port spec, 0 indicates use default

#define RX_OPT 1U // receive mode
#define TX_OPT 1U // send mode
#define EVENT_OPT 1U

// Default Verbosity of 1, totally Quiet = 0
#define USE_SYS_LOG 0
#define DELAY_MS 100
#define IF_VERBOSITY 1

//static int qty = -1; // number of packets after which to quit, either tx/rx or echo. -1 = indefinite.
//static int payload_len = 100;

static v2x_priority_et tx_prio = V2X_PRIO_2;

static uint16_t sps_port = SAMPLE_SPS_PORT;
static uint16_t event_port = SAMPLE_EVENT_PORT;
static v2x_radio_handle_t g_V2xHandler = -1;
// static v2x_iface_capabilities_t g_tCapabilities;

static int sps_sock = 0;
static int event_sock = 0;
static struct sockaddr_in6 sps_sockaddr;
static struct sockaddr_in6 event_sockaddr;

static int tx_sock = 0;
static int rx_sock = 0;
static struct sockaddr_in6 rx_sockaddr;

static int rx_count = 0; // number of packets to RX or TX. -1 = indefinite.
static int tx_count = 0; // number of tx packets

//static v2x_sps_mac_details_t g_tMacDetails;

//static char g_n8DummyPacketBuf[MAX_DUMMY_PACKET_LEN];
static RecvCallbackReturnInfo g_ag15CallbackReturnInfo;
static int rx_len = 0;
static int g_nV2XStatus = 0;
static float g_fCBRStatus = 0;

pthread_mutex_t g_mutex_V2XSendData;
static pthread_t tidp_Read_AG15_LTEData = 0;

extern void UpdateV2XStatus(int8_t V2xStatus);

enum
{
    V2X_DEV_ERROR = -1,
    V2X_DEV_MISSING = -2,
    V2X_DEV_DOWN = -3,
    V2X_DEV_EXIST = 1,
    V2X_DEV_UP = 2
};

/*******************************************************************************
 * return current time stamp in milliseconds
 * @return long long
 ******************************************************************************/
static __inline uint64_t timestamp_now(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

/* Stubs for the various callbacks made on the radio interface */
void init_complete(v2x_status_enum_type status, void *ctx)
{
    if (NULL != ctx)
    {
        LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "Init complete callback. status=%d",
                 status);
    }
}
void radio_listener(v2x_event_t event, void *ctx)
{
    if (NULL != ctx)
    {
        LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "Radio event listener callback: status=%d",
                 event);
    }

    if (event == V2X_ACTIVE)
    {
        int ret = IpcQueueSendingActiveMsg();
        LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "IpcQueueSendingActiveMsg() %d", ret);
        g_nV2XStatus = event;
    }
    else
    {
        int ret = IpcQueueSendingAbnormalMsg();
        LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "IpcQueueSendingAbnormalMsg() %d", ret);
    }

    UpdateV2XStatus((int8_t)event);
}

void meas_listener(v2x_chan_measurements_t *meas_p, void *ctx)
{
    //printf("Radio measurement callback. CBR =%f%%\n",
    //       meas_p->channel_busy_percentage);

    g_fCBRStatus = meas_p->channel_busy_percentage;
}

void l2_changed_listener(int new_l2_address, void *ctx)
{
    // if (NULL != ctx)
    // {
    //     LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "l2_addr-changed listener");
    // }
}

int UpdataTrigger_L2_ID()
{
    int ret = v2x_radio_trigger_l2_update(g_V2xHandler);
    if (ret != 0)
    {
        LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "l2_addr trigger update  =%d", ret);
    }

    return ret;
}
/*******************************************************************************
 * Function: print_buffer
 * Description: Print out a buffer in hex
 * Input Parameters:
 *      buffer: buffer to print
 *      buffer_len: number of bytes in buffer
 ******************************************************************************/
void print_buffer(uint8_t *buffer, int buffer_len)
{
    uint8_t *pkt_buf_ptr;
    int items_printed = 0;

    pkt_buf_ptr = buffer;

    while (items_printed < buffer_len)
    {
        if (items_printed && items_printed % 16 == 0)
        {
            printf("\n");
        }
        printf("%02x ", *pkt_buf_ptr);
        pkt_buf_ptr++;
        items_printed++;
    }
    printf("\n");
}

void termination_handler(int signum)
{

    LogPrint(LOG_LEVEL_DEBUG, "V2XUtil_Debug", "Got signal %d, tearing down all services", signum);
    IpcQueueSendingAbnormalMsg();

    if (rx_sock >= 0)
    {
        v2x_radio_sock_close(&rx_sock);
        rx_sock = 0;
    }
    if (tx_sock >= 0)
    {
        v2x_radio_sock_close(&tx_sock);
        tx_sock = 0;
    }

    if (g_V2xHandler != V2X_RADIO_HANDLE_BAD)
    {
        v2x_radio_deinit(g_V2xHandler);
        g_V2xHandler = 0;
    }

    signal(signum, SIG_DFL);
    raise(signum);
}

void install_signal_handler()
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

static void (*AG15_LTEV2X_FunRecvData)(RecvCallbackReturnInfo ag15CallbackReturnInfo);
int sample_rx(int rx_sock)
{
    int rc = 0;
    int flags = 0;

    rc = recv(rx_sock, g_ag15CallbackReturnInfo.p_cRecvBuf, MAX_DUMMY_PACKET_LEN, flags);
    if (rc < 0)
    {
        return rc;
    }
    if (rc > 0)
    {
        if (AG15_LTEV2X_FunRecvData != NULL)
        {
            g_ag15CallbackReturnInfo.Current_CBR = g_fCBRStatus;
            g_ag15CallbackReturnInfo.pnRecvBufSize = rc;
            g_ag15CallbackReturnInfo.pppp = 0x01;
            AG15_LTEV2X_FunRecvData(g_ag15CallbackReturnInfo);
        }
    }
    rx_count++;
    rx_len = rc;
    return rc;
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

    int bytes_sent = 0;
    struct msghdr message = {0};
    struct iovec iov[1] = {0};
    struct cmsghdr *cmsghp = NULL;
    char control[CMSG_SPACE(sizeof(int))];

    /* Send data using sendmsg to provide IPV6_TCLASS per packet */
    iov[0].iov_base = ag15SendDataInfo.p_pcBuf;
    iov[0].iov_len = ag15SendDataInfo.p_nLen;
    message.msg_iov = iov;
    message.msg_iovlen = 1;
    message.msg_control = control;
    message.msg_controllen = sizeof(control);

    /* Fill ancillary data */
    cmsghp = CMSG_FIRSTHDR(&message);
    cmsghp->cmsg_level = IPPROTO_IPV6;
    cmsghp->cmsg_type = IPV6_TCLASS;
    cmsghp->cmsg_len = CMSG_LEN(sizeof(int));

    if (ag15SendDataInfo.pppp != 0)
        tx_prio = ag15SendDataInfo.pppp; //根据适配层PPPP,重新设置优先级
    //LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "ag15SendDataInfo tx_prio = %d", tx_prio);

    *((int *)CMSG_DATA(cmsghp)) = v2x_convert_priority_to_traffic_class(tx_prio);

    bytes_sent = sendmsg(tx_sock, &message, 0);
    if (bytes_sent < 0)
    {
        LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "Error sending message: %d", bytes_sent);
        bytes_sent = -1;
    }
    else
    {
        if (bytes_sent == ag15SendDataInfo.p_nLen)
        {
            tx_count++;
        }
        else
        {
            LogPrint(LOG_LEVEL_WARN, "V2XUtil_Debug", "TX bytes sent were short");
        }
    }

    ag15SendDataReturnInfo->sendLen = bytes_sent;
    ag15SendDataReturnInfo->Current_CBR = g_fCBRStatus;

    pthread_mutex_unlock(&g_mutex_V2XSendData);

    return bytes_sent;
}

int cshell_AG15_status()
{
    char buffer[BUFSIZ];
    char cmd[100];
    FILE *read_fp;
    int chars_read;
    int ret = 0;

    memset(buffer, 0, BUFSIZ);
    memset(cmd, 0, 100);
    sprintf(cmd, "/bin/dmesg | /bin/grep \"V2X TX status is active\"");
    read_fp = popen(cmd, "r");
    if (read_fp != NULL)
    {
        chars_read = fread(buffer, sizeof(char), BUFSIZ - 1, read_fp);
        pclose(read_fp);

        if (chars_read > 5)
        {
            ret = 1;
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "DEVICE_NONE\n");
            return 0;
        }
    }

    if (ret == 1)
    {
        memset(buffer, 0, BUFSIZ);
        memset(cmd, 0, 100);
        sprintf(cmd, "/bin/dmesg | /bin/grep \"V2X RX status is active\"");
        read_fp = popen(cmd, "r");
        if (read_fp != NULL)
        {
            chars_read = fread(buffer, sizeof(char), BUFSIZ - 1, read_fp);
            pclose(read_fp);

            if (chars_read > 5)
            {
                return 2;
            }
            else
            {
                LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "DEVICE_NONE\n");
                return 1;
            }
        }
    }
    return -1;
}

int cshell_netlink_status(const char *if_name)
{
    char buffer[BUFSIZ];
    char cmd[100];
    FILE *read_fp;
    int chars_read;
    int ret = V2X_DEV_ERROR;

    memset(buffer, 0, BUFSIZ);
    memset(cmd, 0, 100);
    sprintf(cmd, "/sbin/ifconfig | /bin/grep %s", if_name);
    read_fp = popen(cmd, "r");
    if (read_fp != NULL)
    {
        chars_read = fread(buffer, sizeof(char), sizeof(buffer) - 1, read_fp);
        pclose(read_fp);

        if (chars_read > 0)
        {
            ret = V2X_DEV_EXIST;
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "DEVICE_NOTE MISSING\n");
            return V2X_DEV_MISSING;
        }
    }
    else
    {
        perror("popen");
        return V2X_DEV_ERROR;
    }

    if (ret == V2X_DEV_EXIST)
    {
        memset(buffer, 0, BUFSIZ);
        memset(cmd, 0, 100);
        sprintf(cmd, "/sbin/ifconfig %s | /bin/grep RUNNING | awk '{print $1}'", if_name);
        read_fp = popen(cmd, "r");
        if (read_fp != NULL)
        {
            chars_read = fread(buffer, sizeof(char), sizeof(buffer) - 1, read_fp);
            pclose(read_fp);
            if (!strncmp(buffer, "UP", 2U))
            {
                LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "DEVICE_LINKED\n");
                ret = V2X_DEV_UP;
            }
            else
            {
                LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "%s:DEVICE_DOWN\n", buffer);
                ret = V2X_DEV_DOWN;
            }
        }
        else
        {
            perror("popen");
            ret = V2X_DEV_ERROR;
        }
    }
    return ret;
}

void *Thread_Read_AG15_LTEData(void *arg)
{
    pthread_detach(pthread_self());
    while (1)
    {
        //判断是否接收
        if ((g_nV2XStatus == V2X_ACTIVE || g_nV2XStatus == V2X_TX_SUSPENDED) &&
            (ProtocolStackParamConfig.messageParamConfig.recvParamConfig.RecvSwitch == 1))
        {
            sample_rx(rx_sock);
            usleep(1);
        }
        else
        {
            sleep(1);
        }
    }
    return NULL;
}

int AG15_LTEV2X_RealInit()
{
    v2x_concurrency_sel_t mode = V2X_WWAN_NONCONCURRENT;
    unsigned long test_ctx = 0xfeedbeef; // Just a dummy test context to make sure is maintained properly
    v2x_api_ver_t verinfo;
    int traffic_class;
    int loglevel;
    int rx_opt = RX_OPT;
    int tx_opt = TX_OPT;
    v2x_tx_bandwidth_reservation_t v2x_res_req;
    static v2x_radio_calls_t radio_calls;
    static v2x_per_sps_reservation_calls_t sps_function_calls;

    // Set-up the requested radio channel parameters
    //    params.channel_center_khz = 5915000;
    //    params.channel_bandwidth_mhz = 10;
    //    params.tx_power_limit_decidbm = 100;
    //    params.qty_auto_retrans = 1;
    //    params.l2_source_addr_length_bytes = 6;
    //    params.l2_source_addr_p = pseudo_mac;

    radio_calls.v2x_radio_init_complete = init_complete;
    radio_calls.v2x_radio_status_listener = radio_listener;
    radio_calls.v2x_radio_chan_meas_listener = meas_listener;
    radio_calls.v2x_radio_l2_addr_changed_listener = l2_changed_listener;

    // Must be 1, 2, 3, 4 for default config in most pre-configured units. NOTE: also used for event only flows.
    if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == 5 ||
        ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == 2)
    {
        v2x_res_req.v2xid = 3623;
    }
    else
    {
        v2x_res_req.v2xid = 1;
    }

    v2x_res_req.priority = V2X_PRIO_2; // 2 = lowest priority supported in TQ.
    v2x_res_req.period_interval_ms = DELAY_MS;
    v2x_res_req.tx_reservation_size_bytes = 300;

    switch (IF_VERBOSITY)
    {
    case 1:
        loglevel = LOG_ERR;
        break;
    case 2:
        loglevel = LOG_NOTICE;
        break;
    case 3:
        loglevel = LOG_INFO;
        break;
    case 4:
    default:
        loglevel = LOG_DEBUG;
        break;
    }
    v2x_radio_set_log_level(loglevel, USE_SYS_LOG);

    verinfo = v2x_radio_api_version();
    LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "API Version#%d, built on <%s> @ %s \n", verinfo.version_num, verinfo.build_date_str, verinfo.build_time_str);

    g_V2xHandler = v2x_radio_init((char *)g_aDefault_v2x_non_ip_iface_name, mode, &radio_calls, &test_ctx);
    if (g_V2xHandler == V2X_RADIO_HANDLE_BAD || g_V2xHandler >= V2X_MAX_RADIO_SESSIONS)
    {
        LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "Error initializing the V2X radio, bail\n");
        return -1;
    }
    v2x_set_dest_ipv6_addr(g_aDest_ipv6_addr_str);

    // Command line argument(CLA) for portnumber could be either
    // Note:  that since same param used for both Tx/RX, in echo mode,
    // at the portnumber is used for the TX
    // If not receving, then we're running a TX test, so setup the flows (event, or event+SPS)
    if (tx_opt)
    {
        while (1)
        {
            if (EVENT_OPT)
            {
                if (v2x_radio_tx_event_sock_create_and_bind((char *)g_aDefault_v2x_non_ip_iface_name,
                                                            v2x_res_req.v2xid, event_port, &event_sockaddr, &event_sock) != V2X_STATUS_SUCCESS)
                {
                    event_port++;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (v2x_radio_tx_sps_sock_create_and_bind(g_V2xHandler, &v2x_res_req,
                                                          &sps_function_calls, sps_port, event_port, &sps_sock,
                                                          &sps_sockaddr, &event_sock, &event_sockaddr) != V2X_STATUS_SUCCESS)
                {
                    event_port++;
                    sps_port++;
                }
                else
                {
                    break;
                }
            }
        }

        /* Set default TCLASS on event socket */
        traffic_class = v2x_convert_priority_to_traffic_class(tx_prio);
        LogPrint(LOG_LEVEL_DEBUG, "V2XUtil_Debug", "traffic_class=%d\n", traffic_class);

        if (event_sock)
        {
            if (setsockopt(event_sock, IPPROTO_IPV6, IPV6_TCLASS, (void *)&traffic_class, sizeof(traffic_class)) < 0)
            {
                LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "setsockopt(IPV6_TCLASS) on event socket failed err=%d\n", errno);
            }
        }

        if (sps_sock)
        {
            if (setsockopt(sps_sock, IPPROTO_IPV6, IPV6_TCLASS, (void *)&traffic_class, sizeof(traffic_class)) < 0)
            {
                LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "setsockopt(IPV6_TCLASS) on SPS socket failed err=%d\n", errno);
            }
        }
    }

    if (EVENT_OPT)
    {
        tx_sock = event_sock;
        if (IF_VERBOSITY)
        {
            LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "Transmitting out the event socket instead of SPS \n");
        }
    }
    else
    {
        tx_sock = sps_sock;
    }
    //开启接收数据操作
    if (rx_opt)
    {
        if (v2x_radio_rx_sock_create_and_bind(g_V2xHandler, &rx_sock, &rx_sockaddr))
        {
            LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "Error creating RX socket");
            return -1;
        }
        // int nNetTimeOut = 10; //10毫秒
        // setsockopt(rx_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeOut, sizeof(int));
        // int flags = fcntl(rx_sock, F_GETFL, 0);
        // fcntl(rx_sock, F_SETFL, flags & ~O_NONBLOCK); //设置成阻塞模式；
    }

    return 0;
}

static void kill_pthread(pthread_t *tid) /*pthread_kill的返回值：成功（0） 线程不存在（ESRCH） 信号不合法（EINVAL）*/
{
    if (*tid != 0)
    {
        int pthread_kill_err = pthread_kill(*tid, 0);
        if (pthread_kill_err == ESRCH)
        {
            LogPrint(LOG_LEVEL_ERR, "V2XUtil_Debug", "ID为%ld的线程不存在或者已经退出。", *tid);
        }
        else if (pthread_kill_err == EINVAL)
        {
            LogPrint(LOG_LEVEL_ERR, "V2XUtil_Debug", "发送信号非法。");
        }
        else
        {
            LogPrint(LOG_LEVEL_ERR, "V2XUtil_Debug", "ID为%ld的线程目前仍然存活。", *tid);
            pthread_cancel(*tid);
            LogPrint(LOG_LEVEL_ERR, "V2XUtil_Debug", "退出该线程成功。");
        }
        *tid = 0;
        return;
    }
}

static void create_Rxpthread(pthread_t *tid) /*pthread_kill的返回值：成功（0） 线程不存在（ESRCH） 信号不合法（EINVAL）*/
{
    //pthread_t tidp_Read_AG15_LTEData;
    pthread_attr_t attr = {0};
    struct sched_param param = {0};
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    param.sched_priority = 94;
    pthread_attr_setschedparam(&attr, &param);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    //开启接收线程接收tcp传来的数据
    int ret = pthread_create(tid, &attr, Thread_Read_AG15_LTEData, NULL);
    if (ret != 0)
    {
        return;
    }
    pthread_attr_destroy(&attr);
}

/*********************************************************************
 * 开启接收数据
 * 函数名称：int LTEV2X_Rx_SetDevParam()
 * 函数功能：将当前接收参数配置到设备中，进入接收数据状态，如果接收到数据，则进行数据处理；
 * 参数说明：无
 * 函数返回值：执行状态，0 执行成功，非0 执行失败
 *********************************************************************/
int LTEV2X_Rx_SetDevParam(
    void (*pFunRecvData)(RecvCallbackReturnInfo ag15CallbackReturnInfo))
{
    AG15_LTEV2X_FunRecvData = pFunRecvData;

    create_Rxpthread(&tidp_Read_AG15_LTEData);

    return 0;
}

DLL_PUBLIC int V2X_Close()
{
    LogPrint(LOG_LEVEL_INFO, "V2XUtil_Warn", "V2X_Close");
    if (rx_sock >= 0)
    {
        v2x_radio_sock_close(&rx_sock);
        rx_sock = 0;
    }

    if (sps_sock >= 0)
    {
        v2x_radio_sock_close(&sps_sock);
        sps_sock = 0;
        tx_sock = 0;
    }
    if (event_sock >= 0)
    {
        v2x_radio_sock_close(&event_sock);
        event_sock = 0;
        tx_sock = 0;
    }

    assert(v2x_radio_deinit(g_V2xHandler) == V2X_STATUS_SUCCESS);

    return 0;
}

DLL_PUBLIC float V2X_GetCBR()
{
    return g_fCBRStatus;
}

void *Thread_Ag15_StatusCheck(void *arg)
{
    int nRet = 0, txnum = 0, rxnum = 0, ret = 0;
    // int last_rx_count = 0, last_tx_count = 0, recvnum = 0, restartflag = 0, restartnum = 0;
    pthread_detach(pthread_self());
    while (1)
    {
        //检查周期90秒，若连续出现3次不正常，则会有30秒停止发送，待下次正常后，继续发送
        sleep(30);
        nRet = CheckV2xState();
        if (nRet != 0)
        {
            LogPrint(LOG_LEVEL_WARN, "V2XUtil_Warn", "CheckV2xState() = %d", nRet);
            if (nRet == 2)
            {
                txnum += 1;
                rxnum = 0;
                //连续出现3次不正常，则停止发送
                if (txnum == 3)
                {
                    g_nV2XStatus = V2X_TX_SUSPENDED;
                    ProtocolStackParamConfig.v2xStatusFlag.v2xStatus = V2X_TX_SUSPENDED;
                    IpcQueueSendingAbnormalMsg();
                    UpdateV2XStatus((int8_t)V2X_TX_SUSPENDED);
                    txnum = 0;
                    continue;
                }
            }
            else if (nRet == 1)
            {
                rxnum += 1;
                txnum = 0;
                //连续出现3次不正常，则停止发送、接收
                if (rxnum == 3)
                {
                    g_nV2XStatus = V2X_INACTIVE;
                    ProtocolStackParamConfig.v2xStatusFlag.v2xStatus = V2X_INACTIVE;
                    IpcQueueSendingAbnormalMsg();
                    UpdateV2XStatus((int8_t)V2X_INACTIVE);
                    continue;
                }
                //连续出现3次不正常，则关闭套接字，待下次正常后重新初始化套接字
                else if (rxnum == 4)
                {
                    V2X_Close();
                    rxnum = 0;
                    continue;
                }
            }
        }
        else
        {
            LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "CheckV2xState() = %d", nRet);
            rxnum = 0;
            txnum = 0;
            if (rx_sock == 0 || tx_sock == 0)
            {
                //初始化接口
                ret = AG15_LTEV2X_RealInit();
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
#if 0
        //接收状态检查
        {
            //空口无数据时，只发4类消息，cbr最大3%，所以此处最好大于3，才可判定为空口有数据
            if ((g_fCBRStatus > 1) &&
                (rx_count > 0) && (last_rx_count == rx_count) &&
                (g_nV2XStatus == V2X_ACTIVE) &&
                (ProtocolStackParamConfig.messageParamConfig.recvParamConfig.RecvSwitch == 1))
            {
                if (restartflag == 1)
                {
                    //此时接收线程已经重启过，若还是收不到数据，空口可能没有数据，待连续3次后，在重启接收线程
                    restartnum += 1;
                    if (restartnum == 3)
                    {
                        restartnum = 0;
                        restartflag = 0;
                    }
                    else
                    {
                        continue;
                    }
                }
                //不发送数据时，cbr最好>2,判定为空口有数据。若发送数据时，cbr最好>4,判定为空口有数据
                if ((last_tx_count == tx_count && g_fCBRStatus >= 2) ||
                    (last_tx_count != tx_count && g_fCBRStatus >= 4))
                {
                    recvnum += 1;
                    LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "No pkgs,last_tx_count = %d,tx_count = %d,CBR =%f%%",
                             last_tx_count, tx_count, g_fCBRStatus);
                    LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "No pkgs,last_rx_count = %d,rx_count = %d,recvnum = %d",
                             last_rx_count, rx_count, recvnum);
                    if (recvnum == 4 && restartflag == 0)
                    {
                        LogPrint(LOG_LEVEL_INFO, "V2XUtil_Debug", "rx_sock = %d\n", rx_sock);
                        kill_pthread(&tidp_Read_AG15_LTEData);
                        sleep(1);
                        if (rx_sock >= 0)
                        {
                            v2x_radio_sock_close(&rx_sock);
                            rx_sock = 0;
                        }
                        sleep(1);
                        if (v2x_radio_rx_sock_create_and_bind(g_V2xHandler, &rx_sock, &rx_sockaddr))
                        {
                            LogPrint(LOG_LEVEL_ERR, "V2XUtil_Err", "Error creating RX socket");
                        }
                        create_Rxpthread(&tidp_Read_AG15_LTEData);
                        restartflag = 1;
                        recvnum = 0;
                    }
                    else if (recvnum > 4)
                    {
                        recvnum = 0;
                    }
                }
                else
                {
                    recvnum = 0;
                }
            }
            else
            {
                recvnum = 0;
            }

            last_rx_count = rx_count;
            last_tx_count = tx_count;
        }
#endif
    }
    return NULL;
}

void *Thread_Ag15_Init(void *arg)
{
    int Init = 0;
    int nRet = 0;
    install_signal_handler();
    pthread_detach(pthread_self());
    ProtocolStackParamConfig.v2xStatusFlag.v2xStatus = g_nV2XStatus;
    LogPrint(LOG_LEVEL_DEBUG, "Stack_Rx_Debug", "Thread_Ag15_Init() loop is start %d  ", pthread_self());
    while (1)
    {
        sleep(1);
        if (Init == 0)
        {
            //判断data0 data1 成功启动
            nRet = cshell_netlink_status(g_aDefault_v2x_non_ip_iface_name);
            if (V2X_DEV_UP != nRet)
            {
                LogPrint(LOG_LEVEL_WARN, "V2XUtil_Warn", "cshell_netlink_status() = %d", nRet);
                continue;
            }
            else
            {
                Init = 1;
            }
        }
        if (Init == 1)
        {
            //判断active是否完成
            nRet = CheckV2xState();
            if (nRet != 0)
            {
                LogPrint(LOG_LEVEL_WARN, "V2XUtil_Warn", "cshell_AG15_status() = %d", nRet);
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
            AG15_LTEV2X_RealInit();
            Init = 3;
            LogPrint(LOG_LEVEL_DEBUG, "V2XUtil_Debug", "v2x_radio Init Success = %d", Init);
        }

        LogPrint(LOG_LEVEL_DEBUG, "V2XUtil_Debug", "g_nV2XStatus = %d", g_nV2XStatus);
        if (g_nV2XStatus == V2X_ACTIVE)
        {
            ProtocolStackParamConfig.v2xStatusFlag.v2xStatus = g_nV2XStatus;
            pthread_t tid = 0;
            pthread_create(&tid, NULL, Thread_Ag15_StatusCheck, NULL);
            break;
        }
    }

    return NULL;
}

int LTEV2X_Init()
{
    pthread_t tidp_Ag15_Init;
    pthread_attr_t attr = {0};
    struct sched_param param = {0};

    pthread_attr_init(&attr);

    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    param.sched_priority = 94;
    pthread_attr_setschedparam(&attr, &param);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    int nRet = pthread_create(&tidp_Ag15_Init, NULL, Thread_Ag15_Init, NULL);
    if (nRet != 0)
    {
        return -1;
    }
    pthread_attr_destroy(&attr);
    return nRet;
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
