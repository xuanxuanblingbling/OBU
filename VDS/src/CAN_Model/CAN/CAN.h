/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ CAN.h]
 .Company;[WANJI TECHNOLOGY]
 .Author; [ZhangZeng]
 .Date; 2019/9/5
 .Update Time; 22:30:36
 .Gen File Name: GAC_A30_CAN_V1.0.xlsx
 .*****************************************************************************
****************************** .FILE_HEADER_END ******************************/

#ifndef __APPLYLAYER_CAN_CAN_H_
#define __APPLYLAYER_CAN_CAN_H_
#include "CAN.h"
#include "./../log/wj_log.h"
#include "misc.h"

#define FramePrint  0
#define SignalPrint  1
//#define unused  0
#define Grav        (9.80665)

#define PF_CAN 29
#define AF_CAN PF_CAN
#define SIOCSCANBAUDRATE        (SIOCDEVPRIVATE+0)
#define SIOCGCANBAUDRATE        (SIOCDEVPRIVATE+1)

#define SOL_CAN_RAW (SOL_CAN_BASE + CAN_RAW)
#define CAN_RAW_FILTER  1
#define CAN_RAW_LOOPBACK 3
#define CAN_RAW_RECV_OWN_MSGS 0x4
#define RevDataNum  14
#define SendDataNum   13

#define CAN_u8gLowByte(value)   (uint8)(value)
#define CAN_u8gHighByte(value)  (uint8)(value >> 8)

/** controller area network (CAN) kernel definitions */
/** special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000U /** EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000U /** remote transmission request */
#define CAN_ERR_FLAG 0x20000000U /** error frame */
/** valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFU /** standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFU /** extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFU /** omit EFF, RTR, ERR flags */

/** particular protocols of the protocol family PF_CAN */
#define CAN_RAW     1 /** RAW sockets */
#define CAN_BCM     2 /** Broadcast Manager */
#define CAN_TP16    3 /** VAG Transport Protocol v1.6 */
#define CAN_TP20    4 /** VAG Transport Protocol v2.0 */
#define CAN_MCNET   5 /** Bosch MCNet */
#define CAN_ISOTP   6 /** ISO 15765-2 Transport Protocol */
#define CAN_NPROTO  7

#define SOL_CAN_BASE 100
#define CAN_INV_FILTER 0x20000000U /** to be set in can_filter.can_id */

/**
 * Controller Area Network Identifier structure
 *
 * bit 0-28 : CAN identifier (11/29 bit)
 * bit 29   : error frame flag (0 = data frame, 1 = error frame)
 * bit 30   : remote transmission request flag (1 = rtr frame)
 * bit 31   : frame format flag (0 = standard 11 bit, 1 = extended 29 bit)
 */
/**
 * @brief Represents a location.
 */
typedef uint32 canid_t;
typedef const char *LPCSTR;
typedef char *LPSTR;
typedef unsigned long  DWORD;


/**
 * Controller Area Network Error Frame Mask structure
 *
 * bit 0-28 : error class mask (see include/linux/can/error.h)
 * bit 29-31    : set to zero
 */
//typedef uint32 can_err_mask_t;

/**
 * struct can_frame - basic CAN frame structure
 * @can_id:  the CAN ID of the frame and CAN_*_FLAG flags, see above.
 * @can_dlc: the data length field of the CAN frame
 * @data:    the CAN frame payload.
 */
/**
 * @brief Represents a location.
 */
typedef struct _Typecan_frame {
    canid_t can_id;  /** 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8 can_dlc; /** data length code: 0 .. 8 */
    uint8 data[8] __attribute__((aligned(8)));
}can_frame;

/**
 * struct sockaddr_can - the sockaddr structure for CAN sockets
 * @can_family:  address family number AF_CAN.
 * @can_ifindex: CAN network interface index.
 * @can_addr:    protocol specific address information
 */

/**
 * @brief Represents a location.
 */
struct sockaddr_can {
    unsigned short int can_family;
    int         can_ifindex;
    union {
        /** transport protocol class address information (e.g. ISOTP) */
        struct { canid_t rx_id, tx_id; } tp;

        /** reserved for future CAN protocols address information */
    } can_addr;
};

/**
 * struct can_filter - CAN ID based filter in can_register().
 * @can_id:   relevant bits of CAN ID which are not masked out.
 * @can_mask: CAN mask (see description)
 *
 * Description:
 * A filter matches, when
 *
 *          <received_can_id> & mask == can_id & mask
 *
 * The filter can be inverted (CAN_INV_FILTER bit set in can_id) or it can
 * filter for error frames (CAN_ERR_FLAG bit set in mask).
 */
/**
 * @brief can_Filter.
 */
struct can_filter {
    canid_t can_id;
    canid_t can_mask;
};

 /*****************************************
 * @brief VehicleSize.
 ***************************************/
typedef struct __VehicleSize1 {
    //车宽
    uint16 width;
    //车长
    uint16 length;
    //车高
    uint8 height;
    uint8 Release1[3];
} VehicleSize_t1;

/**
 * @brief BrakeSystemStatus.
 */
typedef struct BrakeSystemStatus1 {
    uint8 brakePadel;
    uint8 wheelBrakes;
    uint8 traction;
    uint8 abs;
    uint8 scs;
    uint8 brakeBoost;
    uint8 auxBrakes;
    uint8 Release1;
} BrakeSystemStatus_t1;

/**
 * @brief AccelerationSet4Way.
 */
typedef struct AccelerationSet4Way1 {
    uint16 Long;
    uint16 lat;
    uint8 vert;
    uint8 Release1;
    uint16 yaw;
} AccelerationSet4Way_t1;

/**
 * @brief MotionConfidenceSet.
 */
typedef struct MotionConfidenceSet1 {
    uint8 speedCfd;
    uint8 headingCfd;
    uint8 steerCfd;
    uint8 Release1;//预留字段
} MotionConfidenceSet_t1;

//xinchuang.xing
typedef struct VehLamp_Type 
{
    uint8    BCM_LeftTurnLampSt;
    uint8    BCM_RightTurnLampSt;
    uint8    BCM_LowBeamSt;
    uint8    BCM_HighBeamSt;
    uint8    BCM_FrontFogLampSt;
    uint8    BCM_RearFogLampSt;
    uint8    BCM_ParkingLampSt;
    uint8    BCM_HazardLampSt;   //危险报警灯
} VehLamp;

typedef struct VehLampData_Type 
{
    uint8    RecVehLampMessage;
    uint64   VehGNSS_timestamp;
} VehLampType;

typedef struct BrakeSystenStatus_Type
{
    uint8    BrakeSystemStatusData;
    uint64   BrakeSystenStatus_timestamp;
} BrakeSystenStatus;

typedef struct VehicleEventFlags_Type
{
    uint8    VehicleEventFlagsData;
    uint64   VehicleEventFlagsData_timestamp;
} VehicleEventFlags;

typedef struct TransmissionState_Type
{
    uint8    TransmissionStateData;
    uint64   TransmissionStateData_timestamp;
} TransmissionState;

typedef struct SteeringWheelAngle_Type
{
    double    SteeringWheelAngleData;
    uint64   SteeringWheelAngle_timestamp;
} SteeringWheelAngle;

typedef struct Speed_Type
{
    double    SpeedData;
    uint64   SpeedData_timestamp;
} Speed;
typedef struct VehCANData_Type 
{
    VehLampType          LeftTurnLampSt;
    VehLampType          RightTurnLampSt;
    VehLampType          LowBeamSt;
    VehLampType          HighBeamSt;
    VehLampType          FrontFogLampSt;
    VehLampType          RearFogLampSt;
    VehLampType          ParkingLampSt;
    VehLampType          HazardLampSt;
    BrakeSystenStatus    DF_BrakeSystemStatus;
    VehicleEventFlags    DE_VehicleEventFlags;
    TransmissionState    DE_TransmissionState;
    SteeringWheelAngle   DE_SteeringWheelAngle;
    Speed                DE_Speed;
} VehCANData;

// typedef struct VehCANDSingleConfig_Type 
// {
//     int    CANID;
//     int    LowStartBit;
//     int    LowStartByte;
//     int    DataModel;
//     int    DataLength;
//     double ScaleFactor;
//     double Offset;
// } VehCANDSingleConfig;

typedef enum _SingleType{
    SingleSpeed = 0,
    SingleTransmissionState,
    SingleSteeringWheelAngle,
    LeftTurnLampSt,
    RightTurnLampSt,
    LowBeamSt,
    HighBeamSt,
    FrontFogLampSt,
    RearFogLampSt,
    ParkingLampSt,
    HazardLampSt,
    SingleVehicleEventFlags,
    SingleAccelerationSet4Way,
    SingleBrakeSystemStatus
}SingleType;

/**
 * @brief CANCAN总线数据结构.
 */

/* Define CAN uint16 receive signals enum...*/

/* Define CAN uint32 receive signals enum...*/
typedef enum CAN_enu32VarNumber
{
        CAN_nu32ErrorCode,
        CAN_nu32MsgNeverRecFlg,
        CAN_nu32Max
}CAN_tenu32VarNumber;

int CAN_Press();

void *Thread_RecvCANData(int mCount);
void *Thread_RecvCAN1Data(int mCount);

/********************************************
* @brief 发送CAN数据线程.
 *
 * 接受CAN数据线程，并按照定义解析；
 *
 * @param[in] p  线程输入参数.
 *******************************************/
void *Thread_SendCAN0Data(void *psock);
//void *Thread_SendCAN1Data(void *psock);
void *Thread_SendCAN1Data(void *psock);

extern int CAN_Init(void);

//CAN 信息接收回调函数
static void CallBack(can_frame *frame, int mCount, void (*pFunc)(can_frame *frame, int mCount));

#include "queue.h"
struct Queue mQueue;

char pSectionNames[50][50];
//获取配置文件中的各个setion名
int GetIniSetionNames(LPCSTR lpFileName);


static char CanNameStr[2][10] = {"can0", "can1"};
static int sock_send[2];
static struct sockaddr_can addr_send[2];
static can_frame frame_Send[2];
//发送CAN数据初始化
void CAN_SendInit(char CanName[2][10]);
//CAN数据发送函数
int CAN_SendData(canid_t can_id, uint8 data[], int datalen, int CanDevice);

#undef extern
#endif



