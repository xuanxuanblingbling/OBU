#include <unistd.h>
#include "CAN.h"
#include "RdWrIni.h"
#include "RdWrIniIf.h"
#include <net/if.h>
#include <linux/sockios.h>

/**Global Varibles Definition *******************************************/
pthread_mutex_t g_mutex_CANData;
pthread_mutex_t g_mutex_SENDCan0;
pthread_mutex_t g_mutex_SENDCan1;

long int CAN0StremCount = 0;
int  CAN0RespEnable = 0;
long int CAN1StremCount = 0;
int  CAN1RespEnable = 0;
#define Enable 1
#define DisEnable 0
#define DataLargeModel 0
#define DataLitgeModel 1
//#define CANConfigFileName "/mnt/OBUAPP/Config/CAN_Config.ini"
#define CANConfigFileName "/mnt/APP/Config/obu/vds/CAN_Config.ini"
#define CAN0BierateSetCommand "ip link set can0 up type can bitrate"
#define CAN1BierateSetCommand "ip link set can1 up type can bitrate"

can_frame frame[RevDataNum] = {{0}};
can_frame frameS[SendDataNum] = {{0}};

struct timeval delay;
struct ifreq ifr;

pthread_mutex_t mutex_SendDataDB;

//xinchuang.xing
VehCANData VehCANDataRealTime;

VehCANDSingleConfig DE_CommonSingleConfig[50];

static __inline uint64 CAN_timestamp_now(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (uint64) tv.tv_sec * 1000 + (uint64)tv.tv_usec/1000 ;
}

/****************************************************
 * 函数名称:void msTimeDelay(struct timeval delay, int usTxInterval)
 * 功能描述:周期延时函数
 * 输入参数:周期，单位ms
 * 输出参数:无
 * 返 回 值:无
 * 创建日期:
 ****************************************************/

void msTimeDelay(struct timeval delay, int usTxInterval)
{
      delay.tv_sec = 0;
      delay.tv_usec = usTxInterval * 1000;
      select(0, NULL, NULL, NULL, &delay);
}

/*获取配置文件中的各个setion名*/
int GetIniSetionNames(LPCSTR lpFileName)
{
    memset(pSectionNames, 0, sizeof(pSectionNames));
    int mCount = GetPrivateProfileSectionNames(pSectionNames, lpFileName);

    //建立一个相同结构的结构体队列
    char l_s8astrVariable[30] = {0};
    for(int i=0; i<mCount; i++)
    {
        GetPrivateProfileString(pSectionNames[i],"CANID",NULL,l_s8astrVariable,sizeof(l_s8astrVariable),lpFileName);
        DE_CommonSingleConfig[i].CANID = atoi(l_s8astrVariable);           
        GetPrivateProfileString(pSectionNames[i],"LowStartBit",NULL,l_s8astrVariable,sizeof(l_s8astrVariable),lpFileName);
        DE_CommonSingleConfig[i].LowStartBit = atoi(l_s8astrVariable);          
        GetPrivateProfileString(pSectionNames[i],"LowStartByte",NULL,l_s8astrVariable,sizeof(l_s8astrVariable),lpFileName);
        DE_CommonSingleConfig[i].LowStartByte = atoi(l_s8astrVariable);   
        GetPrivateProfileString(pSectionNames[i],"DataModel",NULL,l_s8astrVariable,sizeof(l_s8astrVariable),lpFileName);
        DE_CommonSingleConfig[i].DataModel = atoi(l_s8astrVariable);
        GetPrivateProfileString(pSectionNames[i],"DataLength",NULL,l_s8astrVariable,sizeof(l_s8astrVariable),lpFileName);
        DE_CommonSingleConfig[i].DataLength = atoi(l_s8astrVariable);
        GetPrivateProfileString(pSectionNames[i],"ScaleFactor",NULL,l_s8astrVariable,sizeof(l_s8astrVariable),lpFileName);
        DE_CommonSingleConfig[i].ScaleFactor = atof(l_s8astrVariable);
        GetPrivateProfileString(pSectionNames[i],"Offset",NULL,l_s8astrVariable,sizeof(l_s8astrVariable),lpFileName);
        DE_CommonSingleConfig[i].Offset = atof(l_s8astrVariable);

        //加入队列
        QueuePush(&mQueue, DE_CommonSingleConfig[i]);
    }

    return mCount;
}

/***********************************************************************
* 函 数 名 称 ： CANDataProcess
* 功 能 描 述 ： CAN数据解析
* 输 入 参 数 ： 
* 输 出 参 数 ： 
* 返  回  值  : 
* 开 发 人 员 ： xinchuang.xing
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-09-24 V1.0    xinchuang.xing   Create
***********************************************************************/
static double  CANDataProcess(unsigned char*RecData,VehCANDSingleConfig VehCANDSingleIn)
{
    int i =0;
    static long long a,b = 0;
    int LogiclarBit = 0;
    int LogiclitBit = 0;
    unsigned long long DataBasic = 0;
    unsigned long long Data = 0;
    double DataRe = 0;
    LogiclarBit = (7-VehCANDSingleIn.LowStartByte)*8 + VehCANDSingleIn.LowStartBit;
    LogiclitBit = (VehCANDSingleIn.LowStartByte<<3) + VehCANDSingleIn.LowStartBit;
    DataBasic = (0xFFFFFFFFFFFFFFFF)>>(64-VehCANDSingleIn.DataLength);
    if(VehCANDSingleIn.DataModel == DataLargeModel)
    {
        for(i=0;i<8;i++)
        {
            a = RecData[i] + (b<<8) ;
            b = a;
        }
        Data = (b>>LogiclarBit)&DataBasic ;
    }
    else if(VehCANDSingleIn.DataModel == DataLitgeModel)
    {
        for(i=0;i<8;i++)
        {
            a = RecData[7-i] + (b<<8) ;
            b = a;
        }
        Data = (b>>LogiclitBit)&DataBasic ;
    }
    else
    {
        /* do nothing */
    }    

    DataRe = VehCANDSingleIn.ScaleFactor*Data + VehCANDSingleIn.Offset ;  
    return DataRe;
}

//解析单帧CAN数据内容
void GetCanSingeCommon(can_frame *frameIn, int mCount)
{
    canid_t mCan_id;
    if(frameIn->can_id > CAN_SFF_MASK)
    {
        mCan_id = frameIn->can_id - CAN_EFF_FLAG;
    }
    else
    {
        mCan_id = frameIn->can_id;
    }

    for(int i=0; i<mCount; i++)
    {
        if(mCan_id == DE_CommonSingleConfig[i].CANID)
        {
            double res = CANDataProcess(frameIn->data, DE_CommonSingleConfig[i]);
            if(strcmp(pSectionNames[i], "Speed") == 0)
            {
                printf("----------speed-----------\n");
            }
            else if(strcmp(pSectionNames[i], "LeftTurnLampSt") == 0)
            {
                /*code*/
            }
        }
    }
}

/***********************************************************************
* 函 数 名 称 ： Thread_RecvCANData
* 功 能 描 述 ： CAN数据接收
* 输 入 参 数 ： 
* 输 出 参 数 ： 
* 返  回  值  : 
* 开 发 人 员 ： xinchuang.xing
* 日期       版本  修改人    描述
* ========== ======= ========= =======================================
* 2020-09-24 V1.0    xinchuang.xing   Create
***********************************************************************/
void *Thread_RecvCANData(int mCount)
{
    int sock = -1;
    int nbytes = 0;
    struct can_filter rfilter[RevDataNum];
    /* add by liuruipeng 2020-09-01 start*/
    struct ifreq ifr;
    sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);    //创建套接字
    LogPrint(LOG_LEVEL_NOTICE, "CAN_Modle", "CAN0RecvSock is:%d",sock);            
    strcpy(ifr.ifr_name, "can0" );
    ioctl(sock, SIOCGIFINDEX, &ifr);//指定 can0 设备
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    socklen_t len = sizeof(addr);
    /* add by liuruipeng 2020-09-01 start*/
    if (bind(sock, (struct sockaddr*) &addr, sizeof(addr)) < 0)   //将套接字与can1绑定
    {
        close(sock);
    //  return -1 ;
    }

   setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter)); //设置过滤规则
   while (1)
   {
       memset(&frame, 0, sizeof(can_frame));
       nbytes = recvfrom(sock, &frame, sizeof(can_frame),0, (struct sockaddr*)&addr, &len);
       if (nbytes > 0)
       {
           CallBack(&frame, mCount, (void *)GetCanSingeCommon);
       }
    }
    return 0;
}

void *Thread_RecvCAN1Data(int mCount)
{
    // int sock = *(int *) psock;
    int sock = -1;
    int nbytes = 0;
    struct can_filter rfilter[RevDataNum];
    /* add by liuruipeng 2020-09-01 start*/
    struct ifreq ifr;
    sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);    //创建套接字
    LogPrint(LOG_LEVEL_NOTICE, "CAN_Modle", "CAN1RecvSock is:%d",sock);            
    strcpy(ifr.ifr_name, "can1" );
    ioctl(sock, SIOCGIFINDEX, &ifr);//指定 can0 设备


    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    socklen_t len = sizeof(addr);

    /* add by liuruipeng 2020-09-01 start*/
    if (bind(sock, (struct sockaddr*) &addr, sizeof(addr)) < 0)   //将套接字与can1绑定
    {
        close(sock);
        // return -1 ;
    }

   setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter)); //设置过滤规则
   while (1)
   {
       memset(&frame, 0, sizeof(can_frame));
       nbytes = recvfrom(sock, &frame, sizeof(can_frame),0, (struct sockaddr*)&addr, &len);
       if (nbytes > 0)
       {
           CallBack(&frame, mCount, (void *)GetCanSingeCommon);
       }
    }
    return 0;
}

static void CallBack(can_frame *frame, int mCount, void (*pFunc)(can_frame *frame, int mCount))
{
    pFunc(frame, mCount);
}

static void CANInit()
{
    int ret = 0;
    char l_s8astrVariable[30] = {0};
    char s[50] = " ";
    ret = GetPrivateProfileString("CAN","CAN0Bitrate",NULL,l_s8astrVariable,sizeof(l_s8astrVariable),CANConfigFileName);
    if(ret == 0)
    {
        LogPrint(LOG_LEVEL_NOTICE, "CAN_Modle", "CAN Config is wrong");            

    }
    else
    {
        system("ip link set can0 down");
        sprintf(s, "ip link set can0 up type can bitrate %s", l_s8astrVariable);
        system(s);
        printf("%s",s);
        LogPrint(LOG_LEVEL_NOTICE, "CAN_Modle", "CAN0 set is :%s",s);                      
    }
    ret = GetPrivateProfileString("CAN","CAN1Bitrate",NULL,l_s8astrVariable,sizeof(l_s8astrVariable),CANConfigFileName);
    if(ret == 0)
    {
        LogPrint(LOG_LEVEL_NOTICE, "CAN_Modle", "CAN Config is wrong");                       
    }
    else
    {
        system("ip link set can1 down");
        sprintf(s, "ip link set can1 up type can bitrate %s", l_s8astrVariable);
        system(s);
        printf("%s",s);
        LogPrint(LOG_LEVEL_NOTICE, "CAN_Modle", "CAN1 set is :%s",s);            
    }
}

/****************************************************
 * 函数名称:CAN_Press()
 * 功能描述:CAN收发数据线程
 * 输入参数:无
 * 输出参数:无
 * 返 回 值:CAN接口句柄
 * 创建日期:
 ****************************************************/
int CAN_Press()
   {
    // int sock = CAN_Open("can0");
    // int sock_1 = CAN_Open("can1");
    int nRet1 = 0;
    int nRet2 = 0;
    int nRet3 = 0;
    int nRet4 = 0;
    pthread_t canthreadid;
    CANInit();

    initQueue(&mQueue);

    //从配置文件中获取
    int mCount = GetIniSetionNames(CANConfigFileName);
    LogPrint(LOG_LEVEL_NOTICE, "CAN_Modle", " mCount = %d",mCount); 
    if(mCount > 0)
    {
        for(int i=0; i<mCount; i++)
        {
            QueuePop(&mQueue, &DE_CommonSingleConfig[i]);
        }
    }
    nRet1 = pthread_create(&canthreadid, NULL, (void*)Thread_RecvCANData, mCount);
    if (nRet1 < 0)
        nRet1 = -3;
    nRet2 = pthread_create(&canthreadid, NULL, (void*)Thread_RecvCAN1Data, mCount);
    if (nRet2 < 0)
        nRet2 = -3;
    /*nRet3 = pthread_create(&canthreadid, NULL, (void*)Thread_SendCAN0Data,NULL);
    if (nRet3 < 0)
        nRet3 = -5;
    nRet4 = pthread_create(&canthreadid, NULL, (void*)Thread_SendCAN1Data,NULL);
    if (nRet4 < 0)
        nRet4 = -6; */  
    return 1;
}

/*******************************************************************
 * 获取当前GPS数据
 * 函数名称：int GPS_GetData(GpsLocation * fix)
 * 函数功能：读取当前最新的GPS数据，GPS数据格式按照指定的数据格式传出；
 * 参数说明：
 * 		输出参数：GpsLocation * fix 最新获取的GPS信息的指针
 * 函数返回值：执行状态，0 执行成功，非0 执行失败
 ******************************************************************/
int CAN_GetData(VehCANData * fix)
{
	if (fix == NULL)
		return -1;
	//pthread_mutex_lock(&g_mutex_GpsData);
	memcpy(&fix->LeftTurnLampSt.RecVehLampMessage, &VehCANDataRealTime.LeftTurnLampSt.RecVehLampMessage, sizeof(VehCANData));
    //printf("====[test] VehCANDataRealTime.DE_Speed is %lf fix->DE_Speed is %lf====\n",VehCANDataRealTime.DE_Speed,fix->DE_Speed);
	//pthread_mutex_unlock(&g_mutex_GpsData);
	return 0;
}
/****************************************************
 * 函数名称:CAN_Init()
 * 功能描述:对CAN模块进行初始化
 * 输入参数:无
 * 输出参数:无
 * 返 回 值:是否初始化成功
 * 创建日期:
 ****************************************************/
int CAN_Init(void)
{
    int nRets = 0;
	int nRet = 0;
    //发送CAN数据初始化
    CAN_SendInit(CanNameStr);

	nRets = CAN_Press();
	if (nRets > 0)
    {
        LogPrint(LOG_LEVEL_NOTICE, "Init", "CAn init Success");
    }
	else
    {
        LogPrint(LOG_LEVEL_NOTICE, "Init", "CAn init Faild");
    }

    return nRet;
}

//发送CAN数据初始化
void CAN_SendInit(char CanName[2][10])
{
    LogPrint(LOG_LEVEL_INFO, "CAN_Modle", " send can socket init!");  
    struct ifreq ifr_send[2];

    for(int i=0; i<2; i++)
    {
        /*建立套接字，设置为原始套接字，原始CAN协议 */
        sock_send[i] = socket(PF_CAN,SOCK_RAW,CAN_RAW);

        /*以下是对CAN接口进行初始化，如设置CAN接口名*/
        strcpy(ifr_send[i].ifr_name, CanName[i]);

        ioctl(sock_send[i], SIOCGIFINDEX, &ifr_send[i]);//指定 can 设备

        addr_send[i].can_family = AF_CAN;
        addr_send[i].can_ifindex = ifr_send[i].ifr_ifindex;

        int loopback = 0; /* 0 = disabled, 1 = enabled (default) */
        setsockopt(sock_send[i], SOL_CAN_RAW, CAN_RAW_LOOPBACK, &loopback, sizeof(loopback));

        bind(sock_send[i], (struct sockaddr*)&addr_send[i], sizeof(addr_send[i]));
    }
}

//CAN数据发送函数
int CAN_SendData(canid_t can_id, uint8 data[], int datalen, int CanDevice)
{
    LogPrint(LOG_LEVEL_INFO, "CAN_Modle", " vds can msg send start!");
    unsigned long nbytes;

    if(bind(sock_send[CanDevice], (struct sockaddr*)&addr_send[CanDevice], sizeof(addr_send[CanDevice]))<0)
    {
        close(sock_send[CanDevice]);
    }

    memset(&frame_Send[CanDevice], 0, sizeof(frame_Send[CanDevice]));

    if(can_id > CAN_SFF_MASK)
    {
        frame_Send[CanDevice].can_id = can_id + CAN_EFF_FLAG;
    }
    else
    {
        frame_Send[CanDevice].can_id = can_id;
    }

    for(int i=0; i<datalen; i++){
        frame_Send[CanDevice].data[i] = data[i];
    }
    frame_Send[CanDevice].can_dlc = datalen;

    nbytes = sendto(sock_send[CanDevice], &frame_Send[CanDevice], sizeof(can_frame), 0, 
        (struct sockaddr*)&addr_send[CanDevice], sizeof(addr_send[CanDevice]));
    // nbytes = write(sock_send[CanDevice], &frame_Send[CanDevice], sizeof(can_frame));

    return nbytes;
}



