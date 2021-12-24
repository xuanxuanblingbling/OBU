/**
 * @defgroup WJ_ConfigInterface WJ_ConfigInterface API
 * @ingroup WJ_Interface_Com API
 * @{
 *
 * 本模块提供V2X配置模块的API接口.
 *
 * @file ConfigModuleRW.h
 * @brief API file.
 *
 */
#ifndef _CONFIGMODULERW_H_
#define _CONFIGMODULERW_H_

#define BSMMSGTYPE 1
#define RSIMSGTYPE 2
#define MAPMSGTYPE 3
#define SPATMSGTYPE 4
#define RSMMSGTYPE 5
#define PASSMSGTYPE 6

#define BSMPATH "/mnt/RWD/MsgFile/BSM.xml"
#define RSIPATH "/mnt/RWD/MsgFile/RSI.xml"
#define SPATPATH "/mnt/RWD/MsgFile/SPAT.xml"
#define RSMPATH "/mnt/RWD/MsgFile/RSM.xml"
#define MAPPATH "/mnt/RWD/MsgFile/MAP.xml"

//*******************************消息层配置信息***************************************//
//*******************************发送策略参数***************************************//
/**
 * @brief 发送策略参数
 */
typedef struct _MsgSendParamConfig
{
    char m_nSectionName[32]; //发送策略参数的消息类型BSM, RSI, MAP, SPAT, RSM, Pass
    int m_nMsgType;          //为了程序内部区分消息类型，消息类型 1, 2, 3, 4, 5, 6,RSM RSI SPAT ...

    int m_nSendSwitch;    //发送开关，0:关, 1:消息队列发送, 2:本地发送
    int m_nSendFrequency; //发送频率 ? HZ
    char m_nSendFilePath[64]; //协议栈消息文件路径设置
} __attribute__((packed)) MsgSendParamConfig;

/**
 * @brief 组内AID消息列表
 */
typedef struct _AIDGroupConfig
{
    char m_nGroupName[32];      //消息对应的section
    int m_nMsgIDNum;            //该类型下具体消息的ID标识的个数
    int m_nMsgIDList[32];       //该类型下具体消息的ID标识, 为了程序内部区分消息，无具体含义
    int m_nMsgAIDNum;           //对应具体消息的AID的个数
    int m_nMsgAIDList[32];      //对应具体消息的AID
    char m_nMsgName[32][32];    //消息对应名称
    char m_nMsgDescrip[32][32]; //消息对应名称（中文）
} __attribute__((packed)) AIDGroupConfig;
/**
 * @brief 组内各类消息的AID
 */
typedef struct _MsgAid
{
    int DSAMSGAID;         //DSA发送
    int BSMOrdinaryConven; //普通车辆+常规型BSMAID
    int BSMOrdinaryEvent;  //普通车辆+事件型BSMAID
    int BSMSpecialConven;  //特殊车辆+常规型BSMAID
    int BSMSpecialEvent;   //特殊车辆+事件型BSMAID
    int BSMAfterLoading;   //后装车载终端
    int MAPMSGAID;         //地图类应用
    int SPATMSGAID;        //信号灯类应用
    int RSIRoadStatic;     //道路信息-静态类应用-RSIAID
    int RSIRoadHalfStatic; //道路信息-半静态类应用-RSIAID
    int RSIRoadDynamic;    //道路信息-动态类应用-RSIAID
    int RSMMSGAID;         //道路提醒类应用
    int TESTBSMMSGAID;     //测试车辆发送
    int TESTRSIMSGAID;     //测试路测发送1
    int TESTRSIMSGAID2;    //测试路测发送2
    int PASSMSGAID;        //消息透传
    /*二期场景消息集*/
    int TESTMSGAID;  //提供测试使用的私有消息格式
    int RTCMMSGAID;  //RTCM差分增强信息的消息
    int PAMMSGAID;   //场站内部地图的消息
    int CLPMMMSGAID; //车队管理消息
    int PSMMSGAID;   //弱势交通参与者（行人、非机动车）的基础安全消息
    int RSCMSGAID;   //路侧单元进行车辆协作或引导的消息
    int SSMMSGAID;   //交通参与者、道路障碍物和交通事件的感知共享消息
    int VIRMSGAID;   //车辆意图及请求消息
    int VPMMSGAID;   //车辆支付消息

} __attribute__((packed)) MsgAid_t;

//*******************************接收参数设置***************************************//
/**
 * @brief 接收参数设置
 */
typedef struct RecvParamConfig
{
    //接收开关，1：开，0：关
    int RecvSwitch;
} __attribute__((packed)) RecvParamConfig_t;

/**
 * @brief AID消息组列表
 */
typedef struct _MessageAIDGroupConfig
{
    int m_GroupNum;
    int m_nGroupType[32];         //该类型下具体消息的ID标识, 为了程序内部区分消息，无具体含义
    char m_nGroupName[32][32];    //消息对应名称
    char m_nGroupDescrip[32][32]; //消息对应名称（中文）
    AIDGroupConfig m_AidGroupConfig[20];
} __attribute__((packed)) MessageAIDGroupConfig;

/**
 * @brief 消息层参数设置
 */
typedef struct MessageParamConfig
{
    //发送策略参数的个数
    int m_SendParamNum;
    //AID消息组
    MessageAIDGroupConfig m_AIDGroup;
    //发送策略参数
    MsgSendParamConfig m_SendParam[20]; // 这里的List代表不同消息类型的List 可以支持增加除了6种消息内容以外的新的消息的类型
    //接收参数设置
    RecvParamConfig_t recvParamConfig;
    //组内各类消息的AID
    MsgAid_t msgAid;
} __attribute__((packed)) MessageParamConfig_t;

//*******************************安全层参数设置***************************************//
/**
 * @brief 安全层参数设置
 */
typedef struct SecurityParamConfig
{
    char s8SecuritySwitch;   /* 安全层开关 0(00):关闭安全层, 1(01):关闭签名打开验签, 2(10):打开签名关闭验签,  3(11):打开签名打开验签 */
    char s8EncryptChipType;  /* 加密芯片类型      1:信大捷安, 2:信长城 */
    char s8SignDeviceType;   /* 签名时的设备类型   1:假名证书(OBU), 2:应用证书(RSU)*/
    char s8EncryptChipSpeed; /* 加密芯片SPI频率配置 6q配置20    8q配置10 单位(MHz) */
    int s32EncryptChipPinInt0;
    int s32EncryptChipPinInt1;
} __attribute__((packed)) SecurityParamConfig_t;

//*******************************DSMP层参数设置***************************************//
/**
 * @brief DSMP层参数设置
 */
typedef struct DSMPParamConfig
{
    //标准消息的AID
    int StandardMessageAID;
    //透传消息的AID
    int PassMessageAID;
    //合法AID列表的个数
    int RecvLegalAIDNum;
    //接收消息的合法AID列表
    int RecvLegalAIDList[32];
    //AID列表检查标志 1：检查，0：不检查
    int AIDListCheckMark;

} __attribute__((packed)) DSMPParamConfig_t;

//*******************************消息层版本设置***************************************//
/**
 * @brief 消息层版本设置
 */
typedef struct MsgFrameConfig
{
    int MsgFrameVersion;

} __attribute__((packed)) MsgFrameConfig_t;

//*******************************日志模块配置文件路径设置***************************************//
/**
 * @brief 日志模块配置文件路径设置
 */
typedef struct LogConfigPath
{
    char logConfigFilePath[256];

} __attribute__((packed)) LogConfigPath_t;

//*******************************第三方库使用设置***************************************//
/**
 * @brief 第三方库使用设置
 */
typedef struct ThirdPartyLibConfig
{
    //是否引用数据库（0不使用，1使用）
    int SqliteConfig;
    //是否引用状态监控（0不使用，1使用）
    int StateMonitorConfig;
    //是否转发数据（0不使用，1使用(预留，暂不使用)）
    int ForwardingConfig;
    //接收数据是否引用动态调整（0不使用，1使用）
    int PthreadStateAdjust;
    //是否引用串行数据发送(0不使用,1使用)
    int SendingSerial;

} __attribute__((packed)) ThirdPartyLibConfig_t;

//*******************************接入层状态标志***************************************//
/**
 * @brief 接入层状态标志
 */
typedef struct V2XStatus
{
    //v2x状态
    int v2xStatus;
} __attribute__((packed)) V2XStatus_t;

//*******************************协议栈参数设置***************************************//
/**
 * @brief 协议栈参数设置
 */
typedef struct ProtocolStackParamConfig
{
    //消息层参数设置
    MessageParamConfig_t messageParamConfig;
    //安全层参数设置
    SecurityParamConfig_t securityParamConfig;
    //DSMP层参数设置
    DSMPParamConfig_t DSMPParamConfig;
    //消息层版本设置
    MsgFrameConfig_t msgFrameConfig;
    //日志模块配置文件路径设置
    LogConfigPath_t logConfigPath;
    //第三方库使用设置
    ThirdPartyLibConfig_t thirdPartyLibConfig;
    //接入层状态标志
    V2XStatus_t v2xStatusFlag;

} __attribute__((packed)) ProtocolStackParamConfig_t;

//内部已定义全局变量，外部主程序无需重复定义，只包含头文件即可
extern ProtocolStackParamConfig_t ProtocolStackParamConfig;

/**
 * @brief ConfigFileProcessReloadThreadFun
 *
 * @param[in] FileName -- 配置文件路径
 *
 * @return 0/-1             成功/失败
 *
 */
void *ConfigFileProcessReloadThreadFun(void *argv);

/**
 * @brief WJ_InitParamDataInterface 系统初始化，从配置文件中读取参数（外部不使用）
 *
 * @param[out] ProtocolStackParamConfig -- 配置文件结构体变量
 * @param[in] FileName -- 配置文件
 *
 * @return 0/-1             成功/失败
 *
 */
int WJ_InitParamDataInterface(ProtocolStackParamConfig_t *p_ProtocolStackParamConfig, char *FileName);

/**
 * @brief WJ_SetParamDataInterface 设置,查询,增加,删除参数接口
 *
 * @param[in] ProtocolStackParamConfig -- 配置文件结构体变量
 * @param[in] souceString -- 原json字符串
 * @param[in] FileName -- 配置文件
 * @param[out] retString -- 返回应答json字符串
 *
 * @return 1/-1             成功/失败
 *
 */
__attribute__((visibility("default"))) int WJ_SetParamDataInterface(ProtocolStackParamConfig_t *ProtocolStackParamConfig, const char *souceString, char *retString, char *FileName);

#endif