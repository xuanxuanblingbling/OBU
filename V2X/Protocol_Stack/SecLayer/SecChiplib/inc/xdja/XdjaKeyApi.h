/**
* @file XdjaKeyApi.h
* @brief 安全卡通用接口
* @author xdja
* @version 1.0.0.1
* @date 20130608
*/

#ifndef _XDJA_KEY_API_H_
#define _XDJA_KEY_API_H_

#ifdef WIN32
    #ifndef XDJAKEYAPI
        #define XDJAKEYAPI __declspec(dllimport)
    #endif
#else
    #define XDJAKEYAPI
#endif
typedef void* XKF_HANDLE;

/************************************************************************/
/* 错误代码定义                                                          */
/************************************************************************/
#define XKR_BASE                         0//0x0003A000
#define XKR_OK                           0x00000000                     //成功
#define XKR_PWD_N                        XKR_BASE+N                     //口令错误,剩余N重试机会
#define XKR_NO_HANDLE                    XKR_BASE-1                     //指定的句柄不存在
#define XKR_IO_FAILED                    XKR_BASE-2                     //通过卡接口收发数据失败
#define XKR_BACK_LENGTH                  XKR_BASE-3                     //返回数据之长度错误
#define XKR_BACK_DATA                    XKR_BASE-4                     //返回数据错误
#define XKR_RESET_FAILED                 XKR_BASE-5                     //卡重置失败
#define XKR_NO_ROLE                      XKR_BASE-6                     //指定的角色不存在
#define XKR_DATAIN_SIZE                  XKR_BASE-7                     //输入数据的长度不合适
#define XKR_OUTBUF_SIZE                  XKR_BASE-8                     //指定的数据接收缓冲区大小不合适
#define XKR_INVALID_PARA                 XKR_BASE-9                     //接口参数错误
#define XKR_PASSWORD                     XKR_BASE-10                    //口令错误,剩余重试次数为0
#define XKR_EEPROM_WRITE                 XKR_BASE-11                    //EEPROM写入错误
#define XKR_PARAMETER                    XKR_BASE-12                    //COS指令参数错误
#define XKR_CMD_NOTMATCH_LINE            XKR_BASE-13                    //命令与线路保护不适应
#define XKR_CMD_NOTMATCH_FAT             XKR_BASE-14                    //命令与文件结构不相容
#define XKR_NO_POWER                     XKR_BASE-15                    //权限不够
#define XKR_KEY_LOCKED                   XKR_BASE-16                    //密钥被锁死
#define XKR_DATA_PARAMETER               XKR_BASE-18                    //数据域参数错误
#define XKR_APP_LOCKED                   XKR_BASE-19                    //应用锁定
#define XKR_FILE_NOT_EXIST               XKR_BASE-20                    //文件不存在
#define XKR_NO_FILE_SPACE                XKR_BASE-21                    //文件无足够空间
#define XKR_NOT_GET_RANDOM               XKR_BASE-22                    //未取随机数
#define XKR_FILE_EXIST                   XKR_BASE-23                    //文件已存在
#define XKR_FILE_CONTENT                 XKR_BASE-24                    //文件内容错误
#define XKR_WRONG_STATE                  XKR_BASE-25                    //错误的状态
#define XKR_CARD_LOCKED                  XKR_BASE-26                    //卡锁定
#define XKR_WRONG_LE                     XKR_BASE-27                    //Le错误
#define XKR_NO_THIS_CMD                  XKR_BASE-28                    //命令不存在
#define XKR_INVALID_DATA                 XKR_BASE-29                    //数据无效
#define XKR_WRONG_MAC                    XKR_BASE-30                    //MAC错误
#define XKR_KEYFILE_NOT_EXIST            XKR_BASE-31                    //密钥文件不存在
#define XKR_KEY_NOT_EXIST                XKR_BASE-32                    //密钥不存在
#define XKR_WRONG_KEY_TYPE               XKR_BASE-33                    //密钥类型不对
#define XKR_BAD_PUBKEY                   XKR_BASE-34                    //返回公钥内容格式不对
#define XKR_HASH_FAILED                  XKR_BASE-35                    //HASH运算失败
#define XKR_RSAPUBLIC_FAILED             XKR_BASE-36                    //RSA公钥运算失败
#define XKR_BAD_PRIKEY                   XKR_BASE-37                    //返回私钥内容格式不对
#define XKR_SIGN_CONFIRM                 XKR_BASE-38                    //等待用户签名确认
#define XKR_SIGN_CANCEL                  XKR_BASE-39                    //用户签名确认取消
#define XKR_CONDITION                    XKR_BASE-40                    //使用条件不满足
#define XKR_DECRYPT_FAIL                 XKR_BASE-41                    //解密失败
#define XKR_NOT_FIND_DATA                XKR_BASE-42                    //文件偏移地址超出，即未找到数据
#define XKR_DGI_NOT_SUPPORT              XKR_BASE-43                    //DGI不支持
#define XKR_DATA_NOCORRENT               XKR_BASE-44                    //安全报文数据对象不正确
#define XKR_EXAUTH_FAIL                  XKR_BASE-45                    //外部认证失败
#define XKR_RSA_NOT_FIND                 XKR_BASE-46                    //RSA密钥未找到
#define XKR_TLOCK_FAILD	                 XKR_BASE-47                    //创建事务锁失败
#define XKR_TLOCK_TIMEOUT                XKR_BASE-48                    //事务锁超时
#define XKR_BAD_CERT                     XKR_BASE-49                    //证书内容错误
#define XKR_SIGN_VERIFY                  XKR_BASE-50                    //签名验证失败
#define XKR_GETMOUNTPATH_FAILD           XKR_BASE-51                    //获取盘符/挂载路径失败
#define XKR_MALLOC_FALID                 XKR_BASE-95                    //内存申请失败
#define XKR_BUFFERISNULL                 XKR_BASE-96                    //内存为空
#define XKR_NO_KEY                       XKR_BASE-97                    //未插入安全卡
#define XKR_NOT_SUPPORT                  XKR_BASE-98                    //暂不支持
#define XKR_NOT_ACTIVATED                XKR_BASE-99                    //卡未激活,需先激活才能正常使用
#define XKR_UNKNOWN                      XKR_BASE-100                   //未知错误
#define XKR_FP_QUERYWAITE                XKR_BASE-101                   //未查询到指纹状态，请等待
#define XKR_FP_CONDITION_NOTMET          XKR_BASE-102                   //指纹KEY使用条件不满足
#define XKR_FP_NOT_MATCH                 XKR_BASE-103					//指纹验证不匹配
#define XKR_FP_RECV_CANCEL               XKR_BASE-104					//收到取消请求
#define XKR_FP_INVALID                   XKR_BASE-105					//检测到非指纹
#define XKR_FP_VALID                     XKR_BASE-106                   //检测到有效指纹
#define XKR_FP_WAITE_ENROLL              XKR_BASE-107					//等待指纹录入
#define XKR_FP_ENROLLING                 XKR_BASE-108                   //当前正在进行指纹录入操作，如需执行其它指令，需发送取消指令
#define XKR_FP_VERIFYING                 XKR_BASE-109					//当前正在进行指纹验证操作，如需执行其它指令，需发送取消指令
#define XKR_FP_NOROOM					 XKR_BASE-110					//指纹存储器空间不足
#define XKR_FP_NOSTORE					 XKR_BASE-111					//设备不存在有效指纹
#define XKR_FP_CHECKFAILED				 XKR_BASE-112					//未检测到指纹，非中间状态，需要重新发起录入/验证
/************************************************************************/
/* 类型结构定义                                                          */
/************************************************************************/

///安全卡类型(已知)
typedef enum _CARD_TYPE
{
    CT_ALL				= 0x0000,
    CT_USBKEY			= 0x0100,   //USBKEY	              0100
    CT_USBDEV			= 0x0110,   //带驱动的USB设备
    CT_NET				= 0x0120,   //Win32 NET设备,用于ActiveX访问USBKEY。
    //CT_USB_AISINO		=0x0130,    //Aision芯片的USBKEY
    CT_USB_CCORE		= 0x0140,   //国芯芯片无存储USBKEY
    //CT_USB_CCORE_V2	=0X0150，   //国芯芯片带存储USBKEY
    CT_USBCD			= 0x0160,   //国芯芯片无存储USBKEY CDROM
    CT_USBKEY30			= 0x0170,   //华芯芯片带存储USBKEY
    CT_USBCCID			= 0x0180,	//USBKEY CCID驱动
    CT_TF				= 0x0200,   //TF
    CT_TF_XDJA		    = 0x0210,   //XDJATF卡
    //CT_TF_XDJA_V1		=0x0211,    //XDJA多文件卡
    //CT_TF_XDJA_V2		=0x0212,    //XDJA单文件卡
    CT_XDJA_CHIP		= 0x0213,   //Android SD接口芯片
    //CT_TF_XDJA_CUSTOM	=0x0214,    //XDJA自定义文件卡
    CT_ACE				= 0x0215,   //Win32   ACE手机
    CT_XDJA_SPI4		= 0x0216,   //四线SPI接口芯片
    CT_XDJA_SPI			= 0x0217,   //Android SPI接口芯片
    CT_XDJA_SPI6		= 0x0218,   //六线SPI接口芯片
    CT_XDJA_UART		= 0x0219,   //UART接口芯片
    CT_XDJA_I2C			= 0x021A,   //IIC接口芯片
    //CT_TF_INCOMM		=0x0220,    //INCOMM卡
    //CT_TF_ZTEIC_OLD	=0x0221,    //INCOMM低速卡1.0  0221
    //CT_TF_ZTEIC_NEW	=0x0222,    //INCOMM低速卡2.0  0222
    //CT_TF_INCOMM_V1	=0x0223,    //INCOMM多文件，高功耗  0223
    //CT_TF_INCOMM_V2	=0x0224,    //INCOMM多文件，低功耗  0224
    //CT_TF_INCOMM_EX	=0x0225,    //INCOMM单文件卡        0225
    //CT_TF_RDFOX		=0x0230,    //REDFOX卡            0230
    //CT_TF_REDFOX_LOW	=0x0231,    //REDFOX低速卡     0231
    //CT_TF_REDFOX_HIGH	=0x0232,    //REDFOX高速卡     0232
    //CT_TIC			=0x0300,    //双界面IC卡            0300
    //CT_NET			=0x0400,    //                    0400
    CT_IOS				= 0x0500,   //                    0500
    CT_TMC				= 0x0600,   //太思贴膜卡              0600
    CT_TMC_XDJA			= 0x0601,	//XDJA贴膜卡
    CT_BLE				= 0x0700,   //蓝牙KEY             0700
    CT_VHSM				= 0x0800,	//VHSM模块V1版本	0800
    CT_VHSMNET			= 0x0810,	//VHSM模块V2版本
    CT_TPARTY			= 0x0900,	//第三方库			0900
    CT_TEESPI			= 0x0A00,	//恒达TEE arm平台模块	0a00
} CARD_TYPE;
#define  CT_TF_XDJA_CHIP CT_XDJA_CHIP
#define  CT_TF_XDJA_SPI  CT_XDJA_SPI

///设备信息
typedef struct _XDJA_DEVINFO
{
    unsigned char cardid[33];          //硬件编号,一般为长度32字节的字符串
    unsigned char cosver[65];          //COS版本号,不超过64字节的字符串
    CARD_TYPE cardtype;                //卡类型
    int  reserve;					   //保留扩展
} XDJA_DEVINFO, *PXDJA_DEVINFO;
#ifndef SKF_DEVINFO
    typedef XDJA_DEVINFO DEVINFO, *PDEVINFO;
#endif
///设备信息扩展
typedef struct _DEVINFOEX
{
    unsigned char cardid[64];          //硬件编号,一般为长度32字节的字符串
    unsigned char mcosver[256];        //主COS版本号,可能为空
    unsigned char cosver[256];         //附COS版本号
    CARD_TYPE cardtype;                //卡类型
} DEVINFOEX, *PDEVINFOEX;
//口令有效长度范围
#define PIN_MAX_LEN  16 //口令最大长度
#define PIN_MIN_LEN  3  //口令最小长度
#define FILE_ID_LEN  2  //文件ID长度
#define KEY_LEN_MAX  32 //密钥值最大长度
#define DIR_NAME_LEN 8 //目录名字最大字符数
///目录类型
enum DIR_TYPE
{
    ROOT_DIR = 1, //根目录
    APP_DIR = 2 //应用目录
};
///目录结构
typedef struct _XDJA_DIR
{
    unsigned char       id[FILE_ID_LEN];           //目录ID    应用目录时有效
    unsigned char       type;                      //根目录、应用目录
    unsigned short      room;                      //空间大小 当应用目录时有效，最大16K
    unsigned char       create_Acl;                //创建权限：在目录下创建文件的权限
    unsigned char       delete_Acl;                //删除权限：在目录下删除文件的权限
    unsigned char       key_Acl;                   //添加对称密钥、解锁口令密钥最低权限
    unsigned char       name[DIR_NAME_LEN];        //目录名称
} XDJA_DIR, *PXDJA_DIR;
///文件类型
enum FILE_TYPE
{

    FILE_BINARY = 1,  //二进制文件
    FILE_PUBLIC = 2,  //公钥文件
    FILE_PRIVATE = 3,  //私钥文件
    FILE_CONTAINER = 4, //容器多文件类型
    FILE_BINARY_SAFE = 11 //带线路保护的二进制文件
};
///文件结构
typedef struct _XDJA_FILE
{
    unsigned char       id[FILE_ID_LEN];    //文件ID
    unsigned char       type;               //文件类型
    unsigned short      room;               //空间大小  文件类型为二进制文件时有效
    unsigned char       read_Acl;           //读取权限  对rsa私钥文件 该值无效，卡的私钥不允许读取
    unsigned char       write_Acl;          //写入权限
    unsigned char       use_Acl;            //使用权限 当为公私钥文件时有效
} XDJA_FILE, *PXDJA_FILE;
///容器文件结构
typedef struct _XDJA_CONTAINER_FILE
{
    unsigned char       id[FILE_ID_LEN];    //文件ID
    unsigned char       type;               //room type,0 bytes, 1 sector
    unsigned short      room;               //空间大小
    unsigned char       read_Acl;           //读取权限
    unsigned char       write_Acl;          //写入权限
    unsigned short      single_size;        //单个文件大小
} XDJA_CONTAINER_FILE, *PXDJA_CONTAINER_FILE;
///SM1密钥结构
typedef struct  _XDJAKEY_ATTR
{
    unsigned char  id;                      //密钥 ID
    unsigned char  type;                    //密钥类型 sm1加密密钥 sm1解密密钥 解锁口令密钥
    unsigned char  use_Acl ;                //使用权限 sm1加密密钥 sm1解密密钥时有效
    unsigned char  update_Acl;              //更改权限
    unsigned char  key[KEY_LEN_MAX];        //密钥值 有效密钥长度根据密钥类型决定 sm1为16字节，解锁口令密钥有效长度为  PIN_MIN_LEN<=len<=PIN_MAX_LEN
    unsigned char  new_state;               //后续状态,新增

    //以下三个当类型为解锁口令密钥时有效
    unsigned char  try_num;                 //尝试次数
    unsigned char  unlock_role;             //解锁密钥可以解锁的role
    unsigned char  len;                     //密钥长度  有效长度同口令长度
} XDJAKEY_ATTR, *PXDJAKEY_ATTR;
///密钥类型
#define KEY_SM1_ENCRYPT         0x01 //SM1加密密钥
#define KEY_SM1_DECRYPT	        0x02 //SM1解密密钥
#define KEY_PIN_UNLOCK          0x03 //解锁口令 
#define KEY_PIN_ROLE            0x04 //角色口令 
#define KEY_SM1_RELOAD          0x05 //SM1口令重装密钥 
#define KEY_DES_RELOAD          0x06 //3DES口令重装密钥
#define KEY_3DES_EAHTU          0x07 //3DES外部认证密钥
#define KEY_SM4_EAUTH           0x08 //SM4外部认证密钥
#define KEY_SM4_SAFE            0x09 //SM4线路保护密钥
#define KEY_SM4_ENCRYPT         0x0A //SM4加密密钥
#define KEY_SM4_DECRYPT         0x0B //SM4解密密钥
#define KEY_3DES_ENCRYPT        0x0C //3DES加密密钥
#define KEY_3DES_DECRYPT        0x0D //3DES解密密钥
#define KEY_3DES24_ENCRYPT		0x0E //3DES24加解密密钥
#define KEY_AES16_ENCRYPT	    0x0F //AES16加解密密钥
#define KEY_AES24_ENCRYPT       0x10 //AES24加解密密钥    
#define KEY_AES32_ENCRYPT       0x11 //AES32加解密密钥


///对称算法操作类型 加密 解密
#define OP_DECRYPT  0x00
#define OP_ENCRYPT  0x01
///对称算法操作模式  ECB  CBC
#define ECB_MODE    0x00
#define CBC_MODE    0x10
///对称算法模式类型标识
#define ECB_DECRYPT 0x00
#define ECB_ENCRYPT 0x01
#define CBC_DECRYPT 0x10
#define CBC_ENCRYPT 0x11
#define CFB_DECRYPT 0x20
#define CFB_ENCRYPT 0x21
#define CTR_DECRYPT 0x30
#define CTR_ENCRYPT 0x31
//密码杂凑算法标识
#define XDD_SHA1	0
#define XDD_SHA256	1
#define XDD_SM3		2
#define XDD_SHA384	3
#define XDD_SHA512	4
#define XDD_MD5		5

//临时密钥算法标识
typedef enum _XDJA_TMP_ALG
{
    TMP_ALG_SM1 = 0,
    TMP_ALG_DES = 1,
    TMP_ALG_3DES = 2,
    TMP_ALG_SM4 = 3,
    TMP_ALG_AES16 = 4,
    TMP_ALG_AES24 = 5,
    TMP_ALG_AES32 = 6
} TMP_ALG;
///卡中RSA运算的长度
#define CARD_RSA_LEN            128
#define CARD_PRIME_LEN          64
#define MAX_RSA_MODULUS_BITS    2048
#define MAX_CARD_RSA_LEN        256
#define MIN_CARD_PRIME_LEN      128
///RSA公钥结构
typedef struct _XDJA_RSA_PUB_KEY
{
    unsigned int  bits;							//公钥模数长度，1024或2048
    unsigned char m[MAX_CARD_RSA_LEN];			//长度256字节，不足靠前存储
    unsigned int  e;							//可能取值65537
} XDJA_RSA_PUB_KEY, *PXDJA_RSA_PUB_KEY;
///RSA私钥结构
typedef struct _XDJA_RSA_PRI_KEY
{
    unsigned int bits;							//公钥模数长度1024或者2048
    unsigned char p[MIN_CARD_PRIME_LEN];		//长度128字节，不足靠前存储
    unsigned char q[MIN_CARD_PRIME_LEN];		//长度128字节，不足靠前存储
    unsigned char dp[MIN_CARD_PRIME_LEN];		//长度128字节，不足靠前存储
    unsigned char dq[MIN_CARD_PRIME_LEN];		//长度128字节，不足靠前存储
    unsigned char ce[MIN_CARD_PRIME_LEN];		//长度128字节，不足靠前存储
} XDJA_RSA_PRI_KEY, *PXDJA_RSA_PRI_KEY;
#define KEY_LEN_SM2       32
///SM2曲线参数
typedef struct _XDJA_SM2_PARAM
{
    unsigned char p[KEY_LEN_SM2];    //素数p
    unsigned char a[KEY_LEN_SM2];    //系数a
    unsigned char b[KEY_LEN_SM2];    //系数b
    unsigned char n[KEY_LEN_SM2];    //阶
    unsigned char x[KEY_LEN_SM2];    //基点G的x坐标
    unsigned char y[KEY_LEN_SM2];    //基点G的y坐标
} XDJA_SM2_PARAM, *PXDJA_SM2_PARAM, *PXDJA_ECC_PARAM;
///sm2私钥结构
typedef struct _XDJA_SM2_PRIKEY
{
    unsigned char d[KEY_LEN_SM2];	//私钥d 32字节
} XDJA_SM2_PRIKEY, *PXDJA_SM2_PRIKEY, *PXDJA_ECC_PRIKEY;
///sm2公钥结构
typedef struct _XDJA_SM2_PUBKEY
{
    unsigned char x[KEY_LEN_SM2];	//公钥x 32字节
    unsigned char y[KEY_LEN_SM2];	//公钥y 32字节
} XDJA_SM2_PUBKEY, *PXDJA_SM2_PUBKEY, *PXDJA_ECC_PUBKEY;

//每种角色对应一个权限,角色通过认证口令获得,可以认为角色就是权限
//#define ROLE_NUM         5 //权限数量
#define ROLE_A           1     //权限1
#define ROLE_B           2
#define ROLE_C           3
#define ROLE_D           4     //权限4
#define ROLE_E           5     //权限5
#define ROLE_Q           0x11  //权限4

#define SM2_KEY_GENERATE_DICT_SEND 0   //SM2协商密钥发起方
#define SM2_KEY_GENERATE_DICT_RECV 1   //SM2协商密钥响应方
#define SM2_UID_MAX     64             //签名时用户ID的最大长度
#define SM2_BLOCK_MAX   158            //SM2加密时明文的最大长度

//签名数据类型
typedef enum
{
    SIGN_HASH = 0,	//签名数据已经过摘要运算，SM2算法时，表示预处理后的e值
    SIGN_NOHASH = 1	//签名数据未经过摘要运算
} SIGN_DATA_TYPE;
///USB分区
typedef enum
{
    USB_NORMAL_ZONE,  //普通区
    USB_SECU_ZONE,    //加密区
    USB_HEDD_ZONE,    //隐藏区分
    USB_INNOSTOR_ZONE //高速盘分区
} USB_FLASH_TYPE;
///USB FLASH读写模式
typedef enum
{
    USB_READ_TEMP,			//临时只读
    USB_WRITE_TEMP,			//临时可写
    USB_READ_FOREVER,		//永久只读
    USB_WRITE_FORERVER,		//永久可写
    INNOSTOR_WRITE_TEMP		//高速盘临时可写
} USB_FLASH_RW_MODE;

///FFCB文件控制块信息
typedef struct _XDJA_FFCB
{
    int free_ffcb;  //全局空FFCB个数
    int free_dfcb;  //全局空DFCB个数
    int cur_dfcb;   //当前目录DFCB个数
    int cur_ffcb;   //当前目录FFCB个数
} XDJA_FFCB, *PXDJA_FFCB;

///ed25519私钥结构
typedef struct _XDJA_ED25519_PRIKEY{
	unsigned int bits;
	unsigned char priv[32];    //私钥32字节
}XDJA_ED25519_PRIKEY, *PXDJA_ED25519_PRIKEY;
///ed25519公钥结构
typedef struct _XDJA_ED25519_PUBKEY{
	unsigned int bits;
	unsigned char pub[32];    //公钥32字节
}XDJA_ED25519_PUBKEY, *PXDJA_ED25519_PUBKEY;


/// SPI芯片配置信息
typedef struct _SPI_CONFIG
{
	int XDJA_INT0_GPIO;		// 3276 INT1引脚，3275INT4引脚
	int XDJA_INT1_GPIO;		// 3276 INT4引脚，3275INT5引脚
	int XDJA_POR_GPIO;		// POR复位引脚【可选，不使用保持-1】
	int XDJA_POWER_GPIO;	// GPIO供电引脚【可选，不使用保持-1】
	int XDJA_QWK_GPIO;		// 低功耗唤醒引脚【可选，不使用保持-1】
	int SPI_SPEED;			// SPI频率配置,默认20/MHz
}XDJA_SPI_CONFIG, *PXDJA_SPI_CONFIG;

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief 获取卡库版本
*
* @param[out] version   卡库版本
* @param[out] verLen 长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetVersion(unsigned char * version, int * verLen);

/**
* @brief 获取卡库编译日期时间
*
* @param[out] datatime 编译日期时间,格式data=mm:dd:yyyy,time=hh:mm:ss
* @param[out] len   返回长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetDateTime(unsigned char * datatime, int * len);

/************************************************************************/
/* 设备管理类接口                                                       */
/************************************************************************/

/**
* @brief 枚举设备
*
* @param[in]  devType  枚举的设备类型，见Enum CARD_TYPE定义
* @param[out] devNum   枚举到的设备个数，XKF_OpenDev索引从0开始
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_EnumDev(int devType, int * DevNum);
/**
* @brief 通过设备索引打开设备，返回设备句柄
* 说明：需要先枚举设备
*
* @param[in]   index   设备索引,从0开始,上限是枚举到的设备数
* @param[out]  hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_OpenDev(int index, XKF_HANDLE * hHandle);

/**
* @brief 打开指定设备,返回设备句柄
* 说明：信大捷安USBCCID设备专用，不需要枚举设备。
*
* @param[in]   handle window SmartCard API返回的操作卡的句柄
* @param[out]  hHandle 设备句柄
*/
XDJAKEYAPI int XKF_OpenDevByHandle(XKF_HANDLE handle, XKF_HANDLE * hHandle);

/**
* @brief 打开指定设备,返回设备句柄
*  说明：无需枚举设备
*
* @param[in]   devName TF卡挂载路径,约定以'/'结束,如 /mnt/sdcard/, j:/
                       USB设备名称,如 /dev/sdd  //./PHYSICALDRIVE4
					   SPI设备节点,如 /dev/spidev1.0
* @param[out]  hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_OpenDevByName(const unsigned char * devName, XKF_HANDLE * hHandle);
/**
* @brief 打开指定设备,返回设备句柄(仅支持ACE设备)
*  说明：需要枚举设备
*
* @param[in]   sn ACE设备序列号
* @param[out]  hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_OpenDevBySN(const char* sn, XKF_HANDLE * hHandle);
/**
* @brief 根据应用程序的包名,返回设备句柄(只用于Android4.4以上)
*  说明：无需枚举设备
*
* @param[in]   packagePath 根据应用程序的包名，通过getPackageName()获取
* @param[out]  hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_OpenDevByNameEx(const char* packagePath, XKF_HANDLE * hHandle);
/**
* @brief 关闭设备
*
* @param[in] hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_CloseDev(XKF_HANDLE hHandle);
/**
* @brief  获得设备独占使用权（开启事务锁）
* 超时时间20秒
* 应用程序在函数组合或事务操作前通过该接口获取设备独占使用权，结束后必须立即释放独占权
*
* @param[in] hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_LockDev(XKF_HANDLE hHandle);
/**
* @brief  释放设备独占使用权（结束事务锁）
*
* @param[in] hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_UnlockDev(XKF_HANDLE hHandle);
/**
* @brief 设备命令传输
*
* @param[in]  hHandle 设备句柄
* @param[in]  pCmd    设备命令（APDU指令）
* @param[in]  cmdLen  命令长度
* @param[out] outBuf  返回结果数据
* @param[out] outlen  输入表示结果数据缓冲大小，输出表示结果数据实际长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_Transmit(XKF_HANDLE hHandle, unsigned char * pCmd, int cmdLen, unsigned char* outBuf, unsigned int * outlen);
/**
* @brief 设备命令传输
* 说明 返回数据和状态字，格式：数据 || 状态字（2字节）
*
* @param[in]  hHandle 设备句柄
* @param[in]  pCmd    设备命令（APDU指令）
* @param[in]  cmdLen  命令长度
* @param[out] outBuf  返回包含状态码的结果数据
* @param[out] outlen  表示结果数据实际长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_TransmitEx(XKF_HANDLE hHandle, unsigned char * pCmd, int cmdLen, unsigned char* outBuf, unsigned int * outlen);
/**
* @brief 获取设备信息，包括卡ID、COS版本、卡类型等
*
* @param[in] hHandle 设备句柄
* @param[out] pDevInfo 返回设备信息
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetDevInfo(XKF_HANDLE hHandle, PXDJA_DEVINFO pDevInfo);
/**
* @brief 获取设备信息扩展
*
* @param[in] hHandle 设备句柄
* @param[out] pDevInfo 返回设备信息扩展
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetDevInfoEx(XKF_HANDLE hHandle, PDEVINFOEX pDevInfoEx);
/**
* @brief 获取设备ID
*
* @param[in] hHandle 设备句柄
* @param[out] pDevId 新版芯片ID
* @param[out] idLen  ID长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetDevId(XKF_HANDLE hHandle, char* pDevId, int* idLen);
/**
* @brief 设置卡驱动日志保存路径
*
* @param[in] logPath 日志保存路径
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SetLogPath(const char* logPath);
/**
* @brief 设置卡驱动日志大小
*
* @param[in] logFileSize 日志文件大小.单位字节，默认2M
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SetLogSize(const unsigned int logFileSize);
/**
* @brief 启用Socket设备
*
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_EnableSocket();
/*
* @brief 激活芯片设备
*
* @param[in] hHandle 设备句柄
* @param[in] param   激活因子
* @param[in] len     激活因子长度(一般为256字节)
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ActivateCard(XKF_HANDLE hHandle, unsigned char* param, unsigned int len);
/**
* @brief 获取芯片激活状态
*
* @param[in] hHandle 设备句柄
*
* @retval XKR_OK              已经激活
* @retval XKR_NOT_ACTIVATED   未激活
*/
XDJAKEYAPI int XKF_GetActivateState(XKF_HANDLE hHandle);
/**
* @brief 设置芯片COS指令是否返回MAC
*
* @param[in] hHandle 设备句柄
* @param[in] mode    0, 不返回MAC; 1,返回MAC
*
* @return  错误码
*/
XDJAKEYAPI int XKF_SetMacCheck(XKF_HANDLE hHandle, int mode);

/************************************************************************/
/*访问控制类接口                                                         */
/************************************************************************/

/**
* @brief 修改PIN
*  说明：修改PIN成功后，已具有当前PIN权限，不需要重新校验PIN
*
* @param[in] hHandle 设备句柄
* @param[in] pinRole PIN码角色
* @param[in] oldpin  旧PIN码
* @param[in] oldlen  旧PIN码长度
* @param[in] newpin  新PIN码
* @param[in] newlen  新PIN码长度
*
* @return 错误码
* @retval XKR_OK          成功
* @retval XKR_PWD_N       正数,剩余重试次数
* @retval XKR_PASSWORD    密码错误,剩余重试次数0
* @retval XKR_KEY_LOCKED  密钥被锁死
*/
XDJAKEYAPI int XKF_ChangePIN(XKF_HANDLE hHandle, int pinRole, const unsigned char* oldpin, int oldlen, const unsigned char* newpin, int newlen);
/**
* @brief 获取PIN码剩余重试次数
*
* @param[in] hHandle 设备句柄
* @param[in] pinRole PIN码角色
*
* @return 重试次数或错误码
* @retval XKR_PWD_N       正数,剩余重试次数
* @retval XKR_PASSWORD    剩余重试次数0（已锁死）
*/
XDJAKEYAPI int XKF_GetPinTryCount(XKF_HANDLE hHandle, int pinRole);
/**
* @brief 校验PIN
*  用于口令验证以获得某种安全状态
*
* @param[in] hHandle 设备句柄
* @param[in] pinRole PIN码角色
* @param[in] pin     PIN码
* @param[in] pinlen  PIN码长度
*
* @return 错误码
* @retval XKR_OK          成功
* @retval XKR_PWD_N       正数,剩余重试次数
* @retval XKR_PASSWORD    密码错误,剩余重试次数0
* @retval XKR_KEY_LOCKED  密钥被锁死
*/
XDJAKEYAPI int XKF_VerifyPIN(XKF_HANDLE hHandle, int pinRole, const unsigned char* pin, int pinlen);
/**
* @brief 解锁PIN
*	说明：解锁密钥只能解锁特定角色PIN码，在初始化时指定。
*
* @param[in] hHandle 设备句柄
* @param[in] id      解锁密钥ID
* @param[in] key     解锁码
* @param[in] keylen  解锁码长度
* @param[in] newpin  新PIN码
* @param[in] newlen  新PIN码长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_UnlockPIN(XKF_HANDLE hHandle, int id, const unsigned char* key, int keylen, const unsigned char* newpin, int newlen);
/**
* @brief 重装PIN
*	说明：重装密钥可以重装指定角色PIN码。
* @param[in] hHandle 设备句柄
* @param[in] pinRole PIN码角色
* @param[in] key     PIN码重装码
* @param[in] keylen  重装码长度
* @param[in] newpin  新PIN码
* @param[in] newlen  新PIN码长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ReloadPIN(XKF_HANDLE hHandle, int pinRole, const unsigned char* key, int keylen, const unsigned char* newpin, int newlen);
/**
* @brief 卡重置，清除安全状态
*
* @param[in] hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_CardReset(XKF_HANDLE hHandle);
/**
* @brief 外部认证，认证通过后获取密钥对应的权限
*  过程：卡内取随机数，经外部SM1加密，再将密文送入卡内做外部认证（解密并比较）
*  要求：外部SM1加密密钥和卡内外部认证密钥相同
*
* @param[in] hHandle     设备句柄
* @param[in] exterAuthID 外部认证密钥ID
* @param[in] encRandom   16字节的随机数密文，经外部SM1加密
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ExternalAuth(XKF_HANDLE hHandle, unsigned char exterAuthID, const unsigned char *encRandom);
/**
* @brief 内部认证（等同于SM1加密）
*  过程： 卡外产生随机数, 并送入卡内做内部认证运算, 将密文返回; 再由卡外解密并比较
*
* @param[in]  hHandle  设备句柄
* @param[in]  pDataIn  外部传入数据
* @param[in]  dataLen  外部传入数据长度(16的整数倍)
* @param[in]  flag     指示加解密模式,ECB_DECRYPT、ECB_ENCRYPT、CBC_DECRYPT、CBC_ENCRYPT。
* @param[in]  kID      密钥标识ID(仅限0、SM1加密密钥、SM1解密密钥和内部认证密钥四种情况)
*                      当KID为0时, 表示临时密钥做内部认证运算；当kID不为零时, 表示所使用的密钥识号（密钥仅限SM1加密密钥、SM1解密密钥和内部认证密钥）
* @param[in]  tmpKey   临时密钥   当kID=0时,tmpKey有效
* @param[out] pDataOut SM1运算结果
* @param[in,out]  pIV  输入iv输出iv 在CBC时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_InternalAuth(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char kID, const unsigned char *tmpKey, unsigned char *pDataOut, unsigned char *pIV);

/************************************************************************/
/*文件管理类接口                                                         */
/************************************************************************/

/**
* @brief 创建目录
* 条件:创建应用目录时，具有当前目录下，创建目录的权限
* 创建根目录时，当前卡文件系统必须为空。
*
* @param[in] hHandle 设备句柄
* @param[in] pDir    目录属性结构，见XDJA_DIR
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_CreateDir(XKF_HANDLE hHandle, PXDJA_DIR pDir);
/**
* @brief 获取当前目录剩余容量
*
* @param[in]  hHandle 设备句柄
* @param[out] size    剩余容量,单位字节Byte
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetDirSize(XKF_HANDLE hHandle, unsigned int * size);
/**
* @brief 获取当前目录ID
*
* @param[in]  hHandle 设备句柄
* @param[out] fid     当前目录ID
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetCurDirID(XKF_HANDLE hHandle, unsigned char * fid);
/**
* @brief 获取芯片文件系统FFCB(文件控制块信息）
*
* @param[in]  hHandle 设备句柄
* @param[out] ffcb    FFCB
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetFFCB(XKF_HANDLE hHandle, PXDJA_FFCB ffcb);
/**
* @brief 创建文件
* 条件:具有当前目录下，创建文件的权限
*
* @param[in] hHandle 设备句柄
* @param[in] pFile   文件属性结构
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_CreateFile(XKF_HANDLE hHandle, PXDJA_FILE pFile);
/**
* @brief 通过ID选择文件或目录
* 按文件标识符选择，选择当前目录下基本文件或子目录文件。
* 在任何情况下均可通过标识符3F00选择MF
*
* @param[in] hHandle 设备句柄
* @param[in] fid     文件或目录id
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SelectFile(XKF_HANDLE hHandle, const unsigned char* fid);
/**
* @brief 通过目录名选择目录
* 用目录名称选择，选择MF，或当前目录本身，或目录的下级子目录。
*
* @param[in] hHandle 设备句柄
* @param[in] name    目录名
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SelectApp(XKF_HANDLE hHandle, const unsigned char * name);

/**
* @brief 删除文件
*	说明：需要权限
* @param[in] hHandle 设备句柄
* @param[in] fid     文件ID，全0表示删除目录下所有文件
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_DeleteFile(XKF_HANDLE hHandle, const unsigned char* fid);
/**
* @brief 取文件属性
*
* @param[in] hHandle 设备句柄
* @param[in] fid     文件ID
* @param[out] pFile  文件属性，仅文件类型和文件大小有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetFileInfo(XKF_HANDLE hHandle, const unsigned char* fid, PXDJA_FILE pFile);
/**
* @brief 读文件
* 条件：具有读该文件的权限
*
* @param[in] hHandle 设备句柄
* @param[in] fid     文件ID
* @param[in] readPos 起始位置
* @param[in] readLen 要读取的长度
* @param[out] pDataout 读取内容缓冲区
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ReadFile(XKF_HANDLE hHandle, const unsigned char* fid, int readPos, int readLen, unsigned char * pDataout);
/**
* @brief 基于线路保护密钥的安全读文件
* 条件：具有读该文件的权限
*
* @param[in] hHandle 设备句柄
* @param[in] safekey 密钥（仅支持SM4算法）
* @param[in] fid     文件ID
* @param[in] readPos 起始位置
* @param[in] readLen 要读取的长度
* @param[out] pDataout 读取内容缓冲区
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ReadFileSafe(XKF_HANDLE hHandle, const unsigned char* safekey, const unsigned char* fid, int readPos, int readLen, unsigned char * pDataout);
/**
* @brief 写文件
* 条件：具有写该文件的权限
*
* @param[in] hHandle 设备句柄
* @param[in] fid     文件ID
* @param[in] writePos 起始位置
* @param[in] writeLen 写入内容的长度
* @param[out] pDatain 写入内容
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_WriteFile(XKF_HANDLE hHandle, const unsigned char* fid, int writePos, int writeLen, const unsigned char * pDatain);
/**
* @brief 基于线路保护密钥的安全写文件
* 条件：具有写该文件的权限
*
* @param[in] hHandle 设备句柄
* @param[in] safekey 密钥（仅支持SM4算法）
* @param[in] fid     文件ID
* @param[in] writePos 起始位置
* @param[in] writeLen 写入内容的长度
* @param[out] pDatain 写入内容
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_WriteFileSafe(XKF_HANDLE hHandle, const unsigned char* safekey, const unsigned char* fid, int writePos, int writeLen, const unsigned char * pDatain);
/**
* @brief 清空文件操作
* 条件：具有写该文件的权限
*
* @param[in] hHandle 设备句柄
* @param[in] fid     文件ID
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_EmptyFile(XKF_HANDLE hHandle, const unsigned char* fid);
/**
* @brief 读RSA公钥
* 条件：具有读RSA公钥的权限
*
* @param[in] hHandle 设备句柄
* @param[in] fid     文件ID
* @param[out] pPub    RSA公钥
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ReadRsaPubKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_RSA_PUB_KEY pPub);
/**
* @brief 写RSA公钥
* 条件：具有写RSA公钥的权限
*
* @param[in] hHandle 设备句柄
* @param[in] fid     文件ID
* @param[in] pPub    RSA公钥
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_WriteRsaPubKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_RSA_PUB_KEY pPub);
/**
* @brief 写RSA私钥
* 条件：具有写RSA私钥的权限
*
* @param[in] hHandle 设备句柄
* @param[in] fid     文件ID
* @param[in] pPri    RSA私钥
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_WriteRsaPriKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_RSA_PRI_KEY pPri);
/**
* @brief 读sm2公钥
* 条件：具有读sm2公钥的权限
*
* @param[in] hHandle 设备句柄
* @param[in] fid     文件ID
* @param[out] pPub    sm2公钥
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ReadSm2PubKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_SM2_PUBKEY pPub);
/**
* @brief 写sm2公钥
* 条件：具有写sm2公钥的权限
*
* @param[in] hHandle 设备句柄
* @param[in] fid     文件ID
* @param[in] pPub    sm2公钥
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_WriteSm2PubKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_SM2_PUBKEY pPub);
/**
* @brief 写sm2私钥
* 条件：具有写sm2私钥的权限
*
* @param[in] hHandle 设备句柄
* @param[in] fid     文件ID
* @param[in] pPri    sm2私钥
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_WriteSm2PriKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_SM2_PRIKEY pPri);
/**
* @brief 读证书
* 条件：具有读证书的权限
*
* @param[in] hHandle   设备句柄
* @param[in] fid       证书文件ID
* @param[out] certBuf  证书信息
* @param[out] certLen  证书信息长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ReadCert(XKF_HANDLE hHandle, const unsigned char * fid, unsigned char *certBuf, int* certLen);
/**
* @brief 写证书
* 条件：具有写证书的权限
*
* @param[in] hHandle   设备句柄
* @param[in] fid       证书文件ID
* @param[in] certBuf   证书信息(DER编码)
* @param[in] certLen   证书信息长度
*
* @return 错误码
* @retval XKR_OK              成功
* @retval XKR_NO_POWER        权限不够
* @retval XKR_FILE_NOT_EXIST  文件不存在
*/
XDJAKEYAPI int XKF_WriteCert(XKF_HANDLE hHandle, const unsigned char * fid, const unsigned char *certBuf, int certLen);

/************************************************************************/
/*密码服务类接口                                                         */
/************************************************************************/

/**
* @brief 卡内产生随机数
*
* @param[in] hHandle 设备句柄
* @param[in] len     需要获取的随机数长度
* @param[out] Random 输出的随机数缓冲区
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GenRandom(XKF_HANDLE hHandle, unsigned int len, unsigned char* pRandom);
/**
* @brief 创建对称密钥
* 条件:具有当前目录下，增加密钥的权限
*
* @param[in] hHandle 设备句柄
* @param[in] pAttr   对称密钥属性结构
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_CreateKey(XKF_HANDLE hHandle, PXDJAKEY_ATTR pKey);
/**
* @brief 更新密钥
* 条件：具有更新该密钥的权限
*
* @param[in] hHandle 设备句柄
* @param[in] type    导入方式(4bit) 和 导入密钥类型(4bit)。本版本支持明文导入。
* @param[in] pDataIn 密钥数据。密钥长度由密钥类型自动决定。在本版本中，SM1密钥为16字节
* @param[in] kID     密钥ID
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ImportKey(XKF_HANDLE hHandle, unsigned int type, const unsigned char * pDatain, unsigned char kID);
/**
* @brief 删除密钥
* 条件：具有删除该密钥的权限
*
* @param[in] hHandle 设备句柄
* @param[in] kID     密钥ID
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_DeleteKey(XKF_HANDLE hHandle, unsigned char kID);
/**
* @brief 获取密钥类型
*
* @param[in] hHandle 设备句柄
* @param[in] kID     密钥ID
* @param[out] type	 密钥类型
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetKeyType(XKF_HANDLE hHandle, unsigned char kID, unsigned char* type);
/**
* @brief 3DES加解密（硬算法），使用卡内对称密钥
*
* @param[in]  hHandle  设备句柄
* @param[in]  pDataIn  被运算的数据
* @param[in]  dataLen  输入数据长度
* @param[in]  flag     指示加密、解密与运算模式。
* @param[out] pDataOut 3DES运算结果
* @param[in]  kID      密钥ID
* @param[in,out]  pIV  输入iv输出iv 在CBC时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_DES3(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char kID, unsigned char* pIV);
/**
* @brief 3DES 24加解密（硬算法），使用卡内对称密钥
*
* @param[in]  hHandle  设备句柄
* @param[in]  pDataIn  被运算的数据
* @param[in]  dataLen  输入数据长度
* @param[in]  flag     指示加密、解密与运算模式。00表示ECB加密；02表示CBC加密；03表示ECB解密；04表示CBC解密
* @param[out] pDataOut 3DES运算结果
* @param[in]  kID      密钥ID
* @param[in,out]  pIV  输入iv输出iv 在CBC时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_TDES24(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char kID, unsigned char* pIV);
/**
* @brief SM1加解密运算（硬算法），使用卡内密钥
*
* @param[in]  hHandle  设备句柄
* @param[in]  pDataIn  被运算的数据
* @param[in]  dataLen  输入数据长度
* @param[in]  flag     指示加密、解密与运算模式。
* @param[out] pDataOut SM1运算结果
* @param[in]  kID      密钥ID
* @param[in,out]  pIV  输入iv输出iv 在CBC时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM1(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char kID, unsigned char* pIV);
/**
* @brief SM4加解密运算（硬算法），使用卡内密钥
*
* @param[in]  hHandle  设备句柄
* @param[in]  pDataIn  被运算的数据
* @param[in]  dataLen  输入数据长度
* @param[in]  flag     指示加密、解密与运算模式。
* @param[out] pDataOut SM1运算结果
* @param[in]  kID      密钥ID
* @param[in,out]  pIV  输入iv输出iv 在CBC时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM4(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char kID, unsigned char* pIV);
/**
* @brief 导入临时SM1密钥
*
* @param[in] hHandle 设备句柄
* @param[in] tmpkey  SM1密钥 16字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ImportTmpKey(XKF_HANDLE hHandle, const unsigned char *tmpkey);
/**
* @brief 导入临时对称密钥
*
* @param[in] hHandle 设备句柄
* @param[in] tmpkey  密钥 des 8字节,其他16字节
* @param[in] alg     临时密钥算法: 0 sm1 ,1 des, 2 3des , 3 sm4
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ImportCipherKey(XKF_HANDLE hHandle, const unsigned char *tmpkey, TMP_ALG alg);
/**
* @brief SM1加解密（硬算法），使用临时SM1密钥
*
* @param[in]  hHandle  设备句柄
* @param[in]  pDataIn  被运算的数据。
* @param[in]  dataLen  输入数据长度。
* @param[in]  flag     指示加密、解密与运算模式。
* @param[out] pDataOut SM1运算结果。
* @param[in]  pIV      输入iv输出iv 在CBC时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_TmpSM1(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char* pIV);
/**
* @brief 对称加解密（硬算法），使用临时对称密钥 （算法由导入密钥时确定）
*	说明：使用卡内临时对称密钥计算，需要在导入临时密钥、密钥协商之、导入信封数据等操作之后使用。
*
* @param[in]  hHandle  设备句柄
* @param[in]  pDataIn  被运算的数据。
* @param[in]  dataLen  输入数据长度。
* @param[in]  alg      临时密钥算法: 0 sm1 ,1 des, 2 3des , 3 sm4
* @param[in]  flag     指示加密、解密与运算模式。
* @param[out] pDataOut 运算结果。
* @param[in]  pIV      输入iv输出iv 在CBC时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_TmpCipher(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, TMP_ALG alg, int flag, unsigned char *pDataOut, unsigned char* pIV);
/**
* @brief 对称加解密（硬算法），使用临时对称密钥
*
* @param[in]  hHandle  设备句柄
* @param[in]  tmpkey   密钥 des 8字节,其他16字节
* @param[in]  pDataIn  被运算的数据。
* @param[in]  dataLen  输入数据长度。
* @param[in]  alg      临时密钥算法，见TMP_ALG
* @param[in]  flag     指示加密、解密与运算模式。
* @param[out] pDataOut 运算结果。
* @param[in,out]  pIV  输入iv输出iv 在CBC时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_CipherKey(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, TMP_ALG alg, int flag, unsigned char *pDataOut, unsigned char* pIV);
/**
* @brief SM1加解密（硬算法），卡外送入密钥
*
* @param[in] hHandle  设备句柄
* @param[in] tmpkey   SM1密钥 16字节
* @param[in] pDataIn  输入数据，数据长度为16整数倍
* @param[in] dataLen  输入数据长度。
* @param[in] flag     指示加密、解密与运算模式。
* @param[out] pDataOut SM1运算结果。
* @param[in] pIV      采用ECB模式此参数无效，可置为NULL;CBC模式时为初始向量，16字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM1KEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);

/**
* @brief SSF33加解密（硬算法），卡外送入密钥 (分组长度16)
*
* @param[in] hHandle    设备句柄
* @param[in] tmpkey     密钥，16字节
* @param[in] pDataIn    输入数据，数据长度为16整数倍
* @param[in] dataLen    输入数据长度
* @param[in] flag       指示加密、解密与运算模式。
* @param[out] pDataOut  输出数据
* @param[in] pIV        采用ECB模式此参数无效，可置为NULL;CBC模式时为初始向量，16字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SSF33(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);
/**
* @brief 卡外SM4加解密（软算法），卡外送入密钥 (分组长度16)
*
* @param[in] hHandle    设备句柄
* @param[in] tmpkey     密钥，16字节
* @param[in] pDataIn    输入数据，数据长度为16整数倍
* @param[in] dataLen    输入数据长度
* @param[in] flag       指示加密、解密与运算模式。支持ECB，CBC，CFB，OFB，CTR模式
* @param[out] pDataOut  输出数据
* @param[in] pIV        采用ECB模式此参数无效，可置为NULL;其他模式时为初始向量，16字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM4KEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);

/**
* @brief 卡外SM4加解密（软算法），卡外送入密钥 (分组长度16)
*
* @param[in] hHandle    设备句柄
* @param[in] tmpkey     密钥，16字节
* @param[in] pDataIn    输入数据，数据长度为16整数倍
* @param[in] dataLen    输入数据长度 [单位bit]
* @param[in] flag       指示加密、解密与运算模式。支持ECB，CBC，CFB，OFB，CTR模式
* @param[out] pDataOut  输出数据
* @param[in] pIV        采用ECB模式此参数无效，可置为NULL;其他模式时为初始向量，16字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM4KEYBits(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);

/**
* @brief 卡内SM4加解密（硬算法），卡外送入密钥 (分组长度16)
*
* @param[in] hHandle    设备句柄
* @param[in] tmpkey     密钥，16字节
* @param[in] pDataIn    输入数据，数据长度为16整数倍
* @param[in] dataLen    输入数据长度
* @param[in] flag       指示加密、解密与运算模式。
* @param[out] pDataOut  输出数据
* @param[in] pIV        采用ECB模式此参数无效，可置为NULL;CBC模式时为初始向量，16字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM4KEYEx(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);
/**
* @brief SM6加解密（硬算法），卡外送入密钥 (分组长度16)
*（SCB2）
*
* @param[in] hHandle    设备句柄
* @param[in] tmpkey     密钥，32字节
* @param[in] pDataIn    输入数据，数据长度为16整数倍
* @param[in] dataLen    输入数据长度
* @param[in] flag       指示加密、解密与运算模式。
* @param[out] pDataOut  输出数
* @param[in] pIV        采用ECB模式此参数无效，可置为NULL;CBC模式时为初始向量，16字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM6KEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);
/**
* @brief DES加解密（软算法），卡外送入密钥 (分组长度8)
*
* @param[in] hHandle    设备句柄
* @param[in] tmpkey     密钥，8字节
* @param[in] pDataIn    输入数据，数据长度为8整数倍
* @param[in] dataLen    输入数据长度
* @param[in] flag       指示加密、解密与运算模式。
* @param[out] pDataOut  输出数据
* @param[in] pIV        采用ECB模式此参数无效，可置为NULL;CBC模式时为初始向量，8字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_DESKEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);
/**
* @brief 3DES加解密（软算法），卡外送入密钥 (分组长度8)
*
* @param[in] hHandle    设备句柄
* @param[in] tmpkey     密钥，16字节或24字节
* @param[in] keylen     密钥长度 （16 24）
* @param[in] pDataIn    输入数据，数据长度为8整数倍
* @param[in] dataLen    输入数据长度
* @param[in] flag       指示加密、解密与运算模式。
* @param[out] pDataOut  输出数据
* @param[in] pIV        采用ECB模式此参数无效，可置为NULL;CBC模式时为初始向量，8字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_DES3KEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, int keylen, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);

/**
* @brief AES加解密（软算法），卡外送入密钥 (分组长度16)
*
* @param[in] hHandle    设备句柄
* @param[in] tmpkey     密钥，16字节、24字节或32字节 （128位、192位或256位）
* @param[in] keylen     密钥长度 （16 24 32）
* @param[in] pDataIn    输入数据，数据长度为16整数倍
* @param[in] dataLen    输入数据长度
* @param[in] flag       指示加密、解密与运算模式。
* @param[out] pDataOut  输出数据
* @param[in] pIV        采用ECB模式此参数无效，可置为NULL;CBC模式时为初始向量，16字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_AESKEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, int keylen, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);
/**
* @brief AES加解密（硬算法），使用卡内对称密钥
*
* @param[in]  hHandle  设备句柄
* @param[in]  pDataIn  被运算的数据
* @param[in]  dataLen  输入数据长度
* @param[in]  flag     指示加密、解密与运算模式。00表示ECB加密；02表示CBC加密；03表示ECB解密；04表示CBC解密
* @param[out] pDataOut AES运算结果
* @param[in]  kID      密钥ID
* @param[in,out]  pIV  输入iv输出iv 在CBC时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_AES(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char kID, unsigned char* pIV);

/**
* @brief SM4 CCM模式，卡外送入密钥
*
* @param[in] hHandle    设备句柄
* @param[in] pDataIn    输入数据
* @param[in] dataLen    输入数据长度
* @param[in] flag       指示加密、解密模式。OP_DECRYPT  0x00 OP_ENCRYPT  0x01
* @param[out] pDataOut  输出数据
* @param[in] tmpkey     密钥，16字节
* @param[in] keylen     密钥长度16
* @param[in] pIV        初始化向量nonce，长度15-L，相当于GB规范中的开始变量S
* @param[in] Add		CCM模式的附加消息，单位：字节（小于65536）
* @param[in] Addlen     CCM中附加消息的长度
* @param[in/out] Tag    CCM模式中认证值 flag=OP_ENCRYPT 表示输出 flag=OP_DECRYPT 表示输入
* @param[in] M			tag的长度，合法的值为：4, 6, 8, 10, 12, 14 和16。openssl中缺省的为12；相当于GB规范中的t
* @param[in] L			长度域，取值为2~8，openssl中缺省的为8 ；相当于GB规范中的w
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM4CCM( XKF_HANDLE hHandle, unsigned char *pDataIn,int dataLen,int flag,unsigned char *pDataOut,unsigned char* tmpkey,int keyLen,unsigned char *pIV,unsigned char *Add, int Addlen,unsigned char* Tag,int M, int L);

/**
* @brief AES CCM模式，卡外送入密钥 
*
* @param[in] hHandle    设备句柄
* @param[in] pDataIn    输入数据
* @param[in] dataLen    输入数据长度
* @param[in] flag       指示加密、解密模式。OP_DECRYPT  0x00 OP_ENCRYPT  0x01
* @param[out] pDataOut  输出数据
* @param[in] tmpkey     密钥，16字节、24字节或32字节 （128位、192位或256位）
* @param[in] keylen     密钥长度 （16 24 32）
* @param[in] pIV        初始化向量nonce，长度15-L
* @param[in] Add		CCM模式的附加消息
* @param[in] Addlen     CCM中附加消息的长度
* @param[in/out] Tag    CCM模式中认证值 flag=OP_ENCRYPT 表示输出 flag=OP_DECRYPT 表示输入
* @param[in] M			tag的长度，合法的值为：4, 6, 8, 10, 12, 14 和16。
* @param[in] L			长度域，取值为2~8
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_AESCCM(XKF_HANDLE hHandle, unsigned char *pDataIn,unsigned long long dataLen,int flag,unsigned char *pDataOut,unsigned char* tmpkey,int keyLen,unsigned char *pIV,unsigned char *Add, unsigned long long Addlen,unsigned char* Tag,unsigned char M, unsigned char L);

/**
* @brief 卡内产生RSA密钥对
* 条件：密钥对不出卡时要求有写指定公私钥文件的权限
*
* @param[in] hHandle 设备句柄
* @param[in] bits    RSA公钥模数长度，1024或2048
* @param[in] pubfid  公钥文件ID，为0x00 0x00时表示公钥导出卡外
* @param[in] prifid  私钥文件ID，公私钥文件ID均为0x00 0x00时私钥可导出卡外
* @param[in] pPub    RSA公钥结构，公钥文件ID为0x00 0x00时有效
* @param[in] pPri    RSA私钥结构，公私钥文件ID均为0x00 0x00时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GenRSAKeyPair(XKF_HANDLE hHandle, int bits, const unsigned char * pubfid, const unsigned char* prifid, PXDJA_RSA_PUB_KEY pPub, PXDJA_RSA_PRI_KEY pPri);
/**
* @brief SHA1运算(软算法)
*
* @param[in] hHandle  设备句柄
* @param[in] pDataIn  输入数据
* @param[in] dataLen    输入数据长度
* @param[out]  pDataOut 输出运算结果 20个字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SHA1(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut);
/**
* @brief SHA1运算(硬算法)
*
* @param[in] hHandle  设备句柄
* @param[in] pDataIn  输入数据
* @param[in] dataLen    输入数据长度
* @param[out]  pDataOut 输出运算结果 20个字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SHA1Ex(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut);
/**
* @brief SHA256运算(硬算法)
*
* @param[in] hHandle  设备句柄
* @param[in] pDataIn  输入数据
* @param[in] dataLen    输入数据长度
* @param[out]  pDataOut 输出运算结果 32个字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SHA256Ex(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut);
/**
* @brief SM3运算(软算法)
*
* @param[in] hHandle   设备句柄
* @param[in] pDataIn   输入数据
* @param[in] dataLen   输入数据长度
* @param[out] pDataOut 输出运算结果 32字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM3(XKF_HANDLE hHandle, const unsigned char *pDatain, int dataLen, unsigned char *pDataOut);
/**
* @brief SM3运算（硬算法）
*
* @param[in] hHandle   设备句柄
* @param[in] pDataIn   输入数据
* @param[in] dataLen   输入数据长度
* @param[out] pDataOut 输出运算结果 32字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM3Ex(XKF_HANDLE hHandle, const unsigned char *pDatain, int dataLen, unsigned char *pDataOut);

/**
* @brief 协议加速
*
* @param[in] hHandle	设备句柄
* @param[in] pucMsg		输入数据，已经拼装好的协议数据
* @param[in] msgLen		输入数据长度
* @param[out] pucDataOut 输出运算结果
* @param[out] puiOutLen 输出运算结果
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ProtocolAcceleration(XKF_HANDLE hHandle, unsigned char* pucMsg, int msgLen, unsigned char* pucDataOut, unsigned int* puiOutLen);
/**
* @brief 密钥派生函数
*
* @param[in] hHandle   设备句柄
* @param[in] pDataIn   输入数据
* @param[in] dataLen   输入数据长度
* @param[in] keylen    要获得的密钥长度
* @param[out] key	   派生的密钥
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_KDF(XKF_HANDLE hHandle, const unsigned char *pDatain, int dataLen, int keylen, unsigned char *key);

/**
* @brief 摘要运算（一次运算）
*
* @param[in] hHandle   设备句柄
* @param[in] alg	   算法类型
* @param[in] pDataIn   输入数据
* @param[in] dataLen   输入数据长度
* @param[out] pDataOut 输出运算结果
* @param[out] outlen   输出结果长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_Digest( XKF_HANDLE hHandle, int alg, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut, int *outlen);
/**
* @brief 摘要运算初始化
*
* @param[in] hHandle   设备句柄
* @param[out] hd	   摘要运算初始化句柄（不是设备句柄）
* @param[in] alg	   算法类型,见密码杂凑算法标识
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_DigestInit(XKF_HANDLE hHandle, void** hd, int alg);
/**
* @brief 摘要运算计算过程
*	说明：需要先调用摘要运算初始化
*
* @param[in] hHandle   设备句柄
* @param[in] hd		   摘要运算句柄
* @param[in] alg	   算法类型,见密码杂凑算法标识
* @param[in] pDataIn   输入数据
* @param[in] dataLen   输入数据长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_DigestUpdate(XKF_HANDLE hHandle, void* hd, int alg, unsigned char *pDataIn, int dataLen);
/**
* @brief 摘要运算最后过程
*	说明：需要至少调用一次摘要运算计算过程
*
* @param[in] hHandle   设备句柄
* @param[in] hd		   摘要运算句柄
* @param[in] alg	   算法类型,见密码杂凑算法标识
* @param[in] pDataOut  输出运算结果
* @param[in] outlen    输出结果长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_DigestFinal(XKF_HANDLE hHandle, void* hd, int alg, unsigned char *pDataOut, int *outlen);
/**
* @brief HMAC摘要运算（一次运算）
*
* @param[in] hHandle   设备句柄
* @param[in] hmacalg   算法类型,见密码杂凑算法标识
* @param[in] key	   密钥
* @param[in] keylen    密钥长度
* @param[in] pDataIn   输入数据
* @param[in] dataLen   输入数据长度
* @param[out] pDataOut 输出运算结果
* @param[out] outlen   输出结果长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_HmacDigest( XKF_HANDLE hHandle, int hmacalg, const unsigned char *key, int keylen, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut, int *outlen);
/**
* @brief HMAC摘要运算（指定密钥id）
*
* @param[in] hHandle   设备句柄
* @param[in] hmacalg   算法类型,见密码杂凑算法标识
* @param[in] keyid     密钥id
* @param[in] pDataIn   输入数据
* @param[in] dataLen   输入数据长度
* @param[out] pDataOut 输出运算结果
* @param[out] outlen   输出结果长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_HmacDigestByID( XKF_HANDLE hHandle, int hmacalg, int keyid, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut, int *outlen);
/**
* @brief HMAC摘要运算初始化
*
* @param[in] hHandle   设备句柄
* @param[out] hd	   摘要运算初始化句柄（不是设备句柄）
* @param[in] hmacalg   算法类型,见密码杂凑算法标识
* @param[in] key	   密钥
* @param[in] keylen    密钥长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_HmacDigestInit(XKF_HANDLE hHandle, void** hd, int hmacalg, const unsigned char *key, int keylen);
/**
* @brief HMAC摘要运算计算过程
*
* @param[in] hHandle   设备句柄
* @param[in] hd		   摘要运算句柄
* @param[in] hmacalg   算法类型,见密码杂凑算法标识
* @param[in] pDataIn   输入数据
* @param[in] dataLen   输入数据长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_HmacDigestUpdate(XKF_HANDLE hHandle, void* hd, int hmacalg, unsigned char *pDataIn, int dataLen);
/**
* @brief HMAC摘要运算最后过程
*	说明：需要至少调用一次摘要运算计算过程
*
* @param[in] hHandle   设备句柄
* @param[in] hd		   摘要运算句柄
* @param[in] hmacalg   算法类型,见密码杂凑算法标识
* @param[out] pDataOut  输出运算结果
* @param[out] outlen    输出结果长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_HmacDigestFinal(XKF_HANDLE hHandle, void* hd, int hmacalg, unsigned char *pDataOut, int *outlen);

/**
* @brief RSA公钥运算 （RSA签名验证）
* 传入数据填充或解填充由调用者进行
*
* @param[in]  hHandle   设备句柄
* @param[in]  fid       RSA公钥文件ID,为0x00 0x00时使用外部公钥
* @param[in]  pPub      RSA公钥结构，公钥文件ID为0x00 0x00时有效
* @param[in]  pDataIn   输入数据
* @param[in]  dlen      输入数据长度，RSA1024为128，RSA2048为256
* @param[out] pDataOut  输出数据
* @param[out] outLen    输出结果长度，128或256
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_RSAPubKeyCalc(XKF_HANDLE hHandle, const unsigned char *fid, PXDJA_RSA_PUB_KEY pPub, const unsigned char *pDataIn, int dlen, unsigned char * pDataOut, unsigned int *outLen);
/**
* @brief RSA私钥运算 （RSA签名）
* 传入数据由调用者进行填充。
*
* @param[in] hHandle  设备句柄
* @param[in] fid       私钥ID
* @param[in] pDataIn   输入数据
* @param[in] dlen      输入数据长度，RSA1024为128，RSA2048为256
* @param[out] pDataOut 输出数据
* @param[out] outLen   输出结果长度，128或256
*
* @return 错误码
* @retval XKR_OK        成功
* @retval XKR_NO_POWER  权限不够
*/
XDJAKEYAPI int XKF_RSAPriKeyCalc(XKF_HANDLE hHandle, const unsigned char *fid, const unsigned char *pDataIn, int dlen, unsigned char* pDataOut, unsigned int *outLen);
/**
* @brief RSA私钥运算 （RSA签名）
* 传入数据由调用者进行填充。
*
* @param[in] hHandle   设备句柄
* @param[in] pin	   pin码
* @param[in] pinlen	   pin密码
* @param[in] pinrole   pin角色
* @param[in] fid       私钥ID
* @param[in] pDataIn   输入数据
* @param[in] dlen      输入数据长度，RSA1024为128，RSA2048为256(暂不支持)
* @param[out] pDataOut 输出数据
* @param[out] outLen   输出结果长度，128或256
*
* @return 错误码
* @retval XKR_OK        成功
* @retval XKR_NO_POWER  权限不够
*/
XDJAKEYAPI int XKF_RSAPriKeyCalcEx(XKF_HANDLE hHandle, unsigned char* pin, int pinlen, int pinrole, const unsigned char *fid, const unsigned char *pDataIn, int dlen, unsigned char* pDataOut,
                                   unsigned int *outLen);
/**
* @brief RSA数据签名
*
* @param[in] hHandle         设备句柄
* @param[in] bits            RSA公钥模数 RSA1024为1024，RSA2048为2048，RSA1152为1152
* @param[in] prikeyid        私钥ID
* @param[in] datatype        数据类型，见SIGN_DATA_TYPE
* @param[in] pDatain         输入数据
* @param[in] dlen            输入数据长度，datatype=SIGN_HASH时，摘要数据长度必须为20；
* @param[out] signData       输出签名数据
* @param[out] outlen         输出数据长度 128或256
*
* @return 错误码
* @retval XKR_OK        成功
* @retval XKR_NO_POWER  权限不够
*/
XDJAKEYAPI int XKF_RSASign(XKF_HANDLE hHandle, int bits, const unsigned char *prikeyid, int datatype, const unsigned char *pDatain, int dlen, unsigned char *signData, unsigned int *outlen);
/**
* @brief RSA数据签名验证
*
* @param[in] hHandle         设备句柄
* @param[in] bits            RSA公钥模数
* @param[in] pubkeyid        公钥ID
* @param[in] rsaPubkey       签名用公钥，当pubkeyid为0x00 0x00时使用
* @param[in] datatype        数据类型，见SIGN_DATA_TYPE
* @param[in] pDatain         输入数据
* @param[in] dlen            输入数据长度，datatype=SIGN_HASH时，摘要数据长度必须为20；
* @param[in] signData	     验签数据
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_RSASignVerify(XKF_HANDLE hHandle, int bits, const unsigned char *pubkeyid, PXDJA_RSA_PUB_KEY rsaPubkey, int datatype, const unsigned char *pDatain, unsigned int dlen,
                                 unsigned char *signData);

/**
* @brief 产生信封
* 产生16字节的随机数作为会话密钥，用指定公钥加密的结果送出卡外，同时保存随机数在卡内临时密钥区域。
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥文件ID
* @param[in] pPubkey         外部公钥，当pubkeyid为0x00 0x00时使用
* @param[in] alg             会话密钥算法,取值1、2、3、4分别表示SM1、DES、3DES、SM4
* @param[out] pDataout       信封数据
* @param[out] outlen         信封数据长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_PackEnvelope(XKF_HANDLE hHandle, const unsigned char * pubfid, PXDJA_RSA_PUB_KEY pPubkey, int alg, unsigned char *pDataout, unsigned int * outlen);
/**
* @brief 拆信封
* 将送入的数据用指定的私钥进行解密，将解密后的结果保存在临时区域。
*
* @param[in] hHandle         设备句柄
* @param[in] prikeyid        私钥文件ID
* @param[in] alg             会话密钥算法,取值1、2、3、4分别表示SM1、DES、3DES、SM4
* @param[in] pDataIn         信封数据
* @param[in] dlen            信封数据长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_UnpackEnvelope(XKF_HANDLE hHandle, const unsigned char * prifid, int alg, unsigned char * pDataIn, int dlen);
/**
* @brief SM1密钥分散
* 密钥分散只能对SM1加密密钥或者SM1解密密钥进行。其功能是将卡外送入的密钥因子用指定的密钥进行加密，并将加密结果存入临时区域。
*
* @param[in] hHandle  设备句柄
* @param[in] keyId    用于密钥分散的主密钥、SM1加密密钥、解密密钥
* @param[in] KeyParam 分散因子
* @param[in] paramLen 分散因子长度,不能超过16
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_KeyDisperse(XKF_HANDLE hHandle, int keyId, unsigned char * keyParam, unsigned int paramLen);

/**
* @brief 设置SM2算法身份标识
*
* @param[in] hHandle  设备句柄
* @param[in] sm2id    身份标识
* @param[in] dlen     身份标识长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SetSM2Id(XKF_HANDLE hHandle, const unsigned char *sm2id, int dlen);
/**
* @brief 获取SM2算法身份标识
*
* @param[in]  hHandle   设备句柄
* @param[out] sm2id     身份标识
* @param[out] outlen    身份标识长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetSM2Id(XKF_HANDLE hHandle, unsigned char *sm2id, unsigned int *outlen );
/**
* @brief 设置SM2算法参数
*
* @param[in] hHandle      设备句柄
* @param[in] sm2param     参数结构体指针
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SetSM2Param(XKF_HANDLE hHandle, PXDJA_SM2_PARAM sm2param);
/**
* @brief 取得SM2算法参数
*
* @param[in] hHandle     设备句柄
* @param[out] sm2param   参数结构体指针
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetSM2Param(XKF_HANDLE hHandle, PXDJA_SM2_PARAM sm2param);
/**
* @brief 设置ECDSA算法参数
*
* @param[in] hHandle      设备句柄
* @param[in] eccparam     参数结构体指针
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SetECDSAParam(XKF_HANDLE hHandle, PXDJA_ECC_PARAM eccparam);
/**
* @brief 取得ECDSA算法参数
*
* @param[in] hHandle     设备句柄
* @param[out] eccparam   参数结构体指针
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetECDSAParam(XKF_HANDLE hHandle, PXDJA_ECC_PARAM eccparam);

/**
* @brief 生成SM2密钥对
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥文件ID,为0x00 0x00时表示公钥导出卡外
* @param[in] prikeyid        私钥文件ID,公私钥ID均为0x00 0x00时表示私钥导出卡外
* @param[out] sm2pubkey      SM2公钥结构，公钥文件ID为0x00 0x00时有效
* @param[out] sm2prikey      SM2私钥结构，公私钥文件ID均为0x00 0x00时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GenSM2KeyPair(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, PXDJA_SM2_PUBKEY sm2pubkey, PXDJA_SM2_PRIKEY sm2prikey);
/**
* @brief 生成ECDSA密钥对
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥文件ID,为0x00 0x00时表示公钥导出卡外
* @param[in] prikeyid        私钥文件ID,公私钥ID均为0x00 0x00时表示私钥导出卡外
* @param[out] eccpubkey      ECC公钥结构，公钥文件ID为0x00 0x00时有效
* @param[out] eccprikey      ECC私钥结构，公私钥文件ID均为0x00 0x00时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GenECDSAKeyPair(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, PXDJA_ECC_PUBKEY eccpubkey, PXDJA_ECC_PRIKEY eccprikey);

/**
* @brief 使用卡内私钥进行点乘运算
*
* @param[in]	hHandle         设备句柄
* @param[in]	type			点乘基于的曲线，type =0 基于SM2算法曲线 type=1 ECC256曲线
* @param[in]	prikeyid        私钥文件ID
* @param[in]	point			椭圆曲线上的点，x||y,64B
* @param[out]	outData			点乘结果，Px || Py，有效数据长度64B
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ECCMult(XKF_HANDLE hHandle, int type,const unsigned char *prikeyid,unsigned char *point,unsigned char *outData);

/**
* @brief 卡内私钥扩展k_new = (k_seed + f) * e + r mod the curve order
*
* @param[in]	hHandle				设备句柄
* @param[in]	type				点乘基于的曲线，type =0 基于SM2算法曲线 type=1 ECC256曲线
* @param[in]	seedPrikeyid        种子私钥文件ID，对应公式中的k_seed
* @param[in]	newPrikeyid			扩展私钥文件ID，对应公式中的k_new
* @param[in]	f					对应公式中的f，32B
* @param[in]	e					对应公式中的e，32B
* @param[in]	r					对应公式中的r，32B
* @param[out]   sm2pubkey           扩展私钥对应ECC公钥
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ECCDeriveKey(XKF_HANDLE hHandle, int type,const unsigned char *seedPrikeyid,const unsigned char *newPrikeyid,unsigned char *f,unsigned char *e,unsigned char *r, PXDJA_SM2_PUBKEY sm2pubkey);

/**
* @brief SM2公钥加密
*  XDJA密文结构： 0x04 | x(32B) | y(32B) | 密文 | 明文HASH(32B)，即：0x04 C1 C2 C3
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        SM2公钥ID，两字节，第二个字节有效 ，为0x00 0x00表示公钥随数据传入
* @param[in] sm2pubkey       公钥,当pubkeyid为0x00 0x00时有效
* @param[in] pDatain         明文数据,最大长度不超过158
* @param[in] dlen            数据长度
* @param[out] pDataout       加密后密文,缓冲长度至少为dlen+97
* @param[out] outlen         加密后数据长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM2Encrypt(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *pDatain, int dlen, unsigned char *pDataout, unsigned int *outLen);
/*
* @brief SM2公钥加密（国密标准）
* 国密密文结构：  x(32B) | y(32B) | 明文HASH(32B) | 密文长度(4B) | 密文，即：C1 C3 C2_length C2
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        SM2公钥ID，两字节，第二个字节有效 ，为0x00 0x00表示公钥随数据传入
* @param[in] sm2pubkey       公钥,当pubkeyid为0x00 0x00时有效
* @param[in] pDatain         明文数据,最大长度不超过153
* @param[in] dlen            数据长度
* @param[out] pDataout       加密后密文,缓冲长度至少为dlen+100
* @param[out] outlen         加密后数据长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM2Encrypt_GM(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *pDatain, int dlen, unsigned char *pDataout, unsigned int *outLen);
/**
* @brief SM2私钥解密
*
* @param[in] hHandle         设备句柄
* @param[in] prikeyid        SM2私钥ID 两字节，第二个字节有效
* @param[in] pDatain         密文数据,最大长度不超过SM2_BLOCK_MAX+97,格式为：04 C1 C2 C3
* @param[in] dlen            数据长度
* @param[out] pDataout       解密后的明文数据,缓冲区至少为dlen-97
* @param[out] outlen         解密后数据长度
*
* @return 错误码
* @retval XKR_OK        成功
* @retval XKR_NO_POWER  权限不够
*/
XDJAKEYAPI int XKF_SM2Decrypt(XKF_HANDLE hHandle, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *pDataout, unsigned int *outlen);
/**
* @brief SM2私钥解密（国密标准）
*
* @param[in] hHandle         设备句柄
* @param[in] prikeyid        SM2私钥ID 两字节，第二个字节有效
* @param[in] pDatain         密文数据,最大长度不超过255
* @param[in] dlen            数据长度
* @param[out] pDataout       解密后的明文数据,缓冲区至少为dlen-100
* @param[out] outlen         解密后数据长度
*
* @return 错误码
* @retval XKR_OK        成功
* @retval XKR_NO_POWER  权限不够
*/
XDJAKEYAPI int XKF_SM2Decrypt_GM(XKF_HANDLE hHandle, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *pDataout, unsigned int *outlen);

/**
* @brief SM2签名预处理
*
* @param[in] hHandle         设备句柄
* @param[in] pSm2Pubkey      SM2公钥
* @param[in] pSm2Id			 SM2签名者ID
* @param[in] sm2IdLen        签名者ID长度
* @param[in] pData			 待处理数据
* @param[in] dataLen         待处理数据长度
* @param[out] e				 预处理之后的数据，长度32B
*
* @return 错误码
* @retval XKR_OK        成功
* @retval XKR_NO_POWER  权限不够
*/
XDJAKEYAPI int XKF_SM2SignPreProcess(XKF_HANDLE hHandle, PXDJA_SM2_PUBKEY pSm2Pubkey, unsigned char* pSm2Id, int sm2IdLen, unsigned char* pData, int dataLen, unsigned char* e);
/**
* @brief SM2数据签名（软HASH）
* 如果待签名数据已经SM3HASH，直接签名；否则先进行SM3HASH（软算法）
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥ID,当datatype=1时,pubkeyid有效
* @param[in] prikeyid        私钥ID
* @param[in] datatype        数据类型,见SIGN_DATA_TYPE
* @param[in] pDatain         输入数据
* @param[in] dlen            数据长度,如果datatype=SIGN_HASH,数据长度必须为32，即e值
* @param[out] signData       输出签名数据,缓冲区长度必须大于64字节，格式：32字节r+32字节s
* @param[out] outlen         输出数据长度
*
* @return 错误码
* @retval XKR_NO_POWER  权限不够
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM2Sign(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, int datatype, const unsigned char *pDatain, int dlen, unsigned char *signData,
                           unsigned int *outlen);

/**
* @brief ECDSA数据签
* 数据必须是已经做过摘要运算的
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥ID,当datatype=1时,pubkeyid有效
* @param[in] prikeyid        私钥ID
* @param[in] pDatain         输入数据，必须是已经HASH的32字节
* @param[out] signData       输出签名数据,缓冲区长度必须大于64字节
* @param[out] outlen         输出数据长度
*
* @return 错误码
* @retval XKR_NO_POWER  权限不够
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ECDSASign(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, const unsigned char *pDatain, unsigned char *signData, unsigned int *outlen);
/**
* @brief SM2数据签名（硬HASH）
* 先对待签名数据进行SM3HASH(硬算法)，再签名
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥ID,当datatype=SIGN_NOHASH时,pubkeyid有效
* @param[in] prikeyid        私钥ID
* @param[in] pDatain         待签名数据
* @param[in] dlen            待签名数据长度
* @param[out] signData       输出签名数据,缓冲区长度必须大于64字节
* @param[out] outlen         输出数据长度
*
* @return 错误码
* @retval XKR_NO_POWER  权限不够
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM2SignEx(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *signData, unsigned int *outlen);

/**
* @brief SM2数据签名验证（软HASH）
* 如果待签名数据已经SM3HASH，直接验签；否则先进行SM3HASH（软算法）
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥ID
* @param[in] datatype        数据类型，见SIGN_DATA_TYPE
* @param[in] sm2pubkey       签名用公钥，当pubkeyid为0x00 0x00时使用
* @param[in] pDatain         数据
* @param[in] dlen            数据长度，如果datatype=SIGN_HASH,数据长度必须为32，即e值
* @param[in] signData        验签数据
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_SM2SignVerify(XKF_HANDLE hHandle, const unsigned char *pubkeyid, int datatype, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *pDatain, int dlen, unsigned char *signData);
/**
* @brief ECDSA数据签名验证
* 数据必须是已经HASH的32字节
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥ID
* @param[in] eccpubkey       签名用公钥，当pubkeyid为0x00 0x00时使用
* @param[in] pDatain         数据，必须是已经摘要后的32字节
* @param[in] signData        验签数据
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_ECDSASignVerify(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_ECC_PUBKEY eccpubkey, const unsigned char *pDatain, unsigned char *signData);
/**
* @brief SM2数据签名验证（硬HASH）
* 先对待签名数据进行SM3HASH（硬算法），再验签
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥ID
* @param[in] sm2pubkey       签名用公钥，当pubkeyid为0x00 0x00时使用
* @param[in] pDatain         待签名数据
* @param[in] dlen            待签名数据长度
* @param[in] signData        验签数据
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_SM2SignVerifyEx(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *pDatain, int dlen, unsigned char *signData);

/**
* @brief SM2数据签名验证（HASH）
* 待签名数据已经SM3HASH，直接验签；
*
* @param[in] hHandle         设备句柄
* @param[in] datatype        数据类型SIGN_DATA_TYPE
* @param[in] sm2id			 sm2签名id，当datatype=SIGN_NOHASH时有效
* @param[in] idlen			 sm2签名id长度
* @param[in] pubdata1		 第1组验签数据，公钥 	 04+x+y 或 02/03+x
* @param[in] publen1         第1组验签数据，公钥长度
* @param[in] pDatain1        第1组验签数据，待验签数据
* @param[in] dlen1			 第1组验签数据，待验签数据长度，如果是预处理过的数据，数据长度必须是32
* @param[in] signData1		 第1组验签数据，签名数据
* @param[in] pubdata2		 第2组验签数据，公钥 	 04+x+y 或 02/03+x
* @param[in] publen2         第2组验签数据，公钥长度
* @param[in] pDatain2        第2组验签数据，待验签数据
* @param[in] dlen2			 第2组验签数据，待验签数据长度，如果是预处理过的数据，数据长度必须是32
* @param[in] signData2		 第2组验签数据，签名数据
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_SM2SignVerifyMult(XKF_HANDLE hHandle, int datatype, unsigned char *sm2id, int idlen, unsigned char * pubdata1, int publen1, const unsigned char *pDatain1, int dlen1,
                                     unsigned char *signData1, unsigned char * pubdata2, int publen2, const unsigned char *pDatain2, int dlen2, unsigned char *signData2);

/**
* @brief 隐式证书公钥转完整公钥
* 计算公式：RP = [l]Ppc + Ppca
* @param[in] hHandle       设备句柄
* @param[in] pubtype       0 SM2; 1 ECDSA
* @param[in] pcPub         隐式证书公钥
* @param[in] pcaPub        PCA中的公钥
* @param[in] l             输入参数HASH值，字节
* @param[in] message       待签名消息
* @param[in] signData      签名数据
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_ImCertPubConvr(XKF_HANDLE hHandle, int pubtype, PXDJA_ECC_PUBKEY pcPub, PXDJA_ECC_PUBKEY pcaPub, unsigned char * l, PXDJA_ECC_PUBKEY rpPub);

/**
* @brief 蝴蝶密钥加密密钥点乘
*
* @param[in] hHandle    设备句柄
* @param[in] asymalg    非对称算法类型0_SM2, 1_ECDSA
* @param[in] symalg     对称算法类型  参数保留，默认0
* @param[in] i			序列值i
* @param[in] j			序列值j
* @param[in] ek			用于解密私钥计算的ek
* @param[in] prifid		私钥id
* @param[in] xybuf		点乘输入的点坐标x[32B]+y[32B]
* @param[in] xylen		64
* @param[out] outdata   点乘结果的xy
* @param[out] datalen   点乘结果输出长度
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_BKTmpEnPriCalc(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, unsigned int i, unsigned int j, unsigned char* ek, unsigned char *prifid, unsigned char* xybuf,
                                  int xylen, unsigned char* outdata, int *datalen);



/**
* @brief 压缩公钥转完整公钥
* 计算公式：y^2 = x^3 + ax + b
* @param[in] hHandle    设备句柄
* @param[in] pubtype    0 SM2; 1 ECDSA
* @param[in] x          输入公钥 x
* @param[in] y_lsb      压缩y值：0 1
* @param[out] y         输出公钥 y
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_CompressPubConvr(XKF_HANDLE hHandle, int pubtype, unsigned char* x, unsigned char y_lsb, unsigned char* y);
/**
* @brief SM2数据签名验证（HASH）
* 待签名数据已经SM3HASH，直接验签；
*
* @param[in] hHandle         设备句柄
* @param[in] datatype        数据类型，见SIGN_DATA_TYPE
* @param[in] pubtype 	     0 普通公钥; 1 压缩公钥; 2 隐式证书公钥
* @param[in] pubData 	     pubtype=0普通公钥TLV数据;pubData= 78 20 [Pub_x] 79 20 [Pub_y]
*			                 pubtype=1压缩公钥公钥TLV数据; pubData=78 20 [Pub_x] 79 01 [y_lsb]
*							 pubtype=2隐式证书TLV数据;pubData= 6C 20 [l] 78 20 [pcPub_x] 79 20 [pcPub_y]  78 20 [pcaPub_x] 79 20 [pcaPub_y]
* @param[in] pDatain         数据
* @param[in] dlen            数据长度，如果datatype=SIGN_HASH长度必须为32
* @param[in] signData        验签数据
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_SM2SignVerifyEx2(XKF_HANDLE hHandle, int datatype, int pubtype, unsigned char *pubData, const unsigned char *pDatain, int dlen, unsigned char *signData);

/**
* @brief ECDSA数据签名验证（HASH）
*
* @param[in] hHandle         设备句柄
* @param[in] pubtype 	     0 普通公钥;1 压缩公钥; 2 隐式证书公钥
* @param[in] pubData 	     pubtype=0普通公钥TLV数据;pubData= 78 20 [Pub_x] 79 20 [Pub_y]
*			   				 pubtype=1压缩公钥公钥TLV数据; pubData=78 20 [Pub_x] 79 01 [y_lsb]
*							 pubtype=2隐式证书TLV数据;pubData= 6C 20 [l] 78 20 [pcPub_x] 79 20 [pcPub_y]  78 20 [pcaPub_x] 79 20 [pcaPub_y]
* @param[in] pDatain         数据
* @param[in] dlen            数据长度,必须为32
* @param[in] signData        验签数据
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_ECDSASignVerifyEx2(XKF_HANDLE hHandle, int pubtype, unsigned char *pubData, const unsigned char *pDatain, int dlen, unsigned char *signData);

/**
* @brief SM2数据签名（数据未hash）
* 所有数据传给COS，COS内部做hash和签名
*
* @param[in] hHandle         设备句柄
* @param[in] sm2pubkey       SM2公钥结构
* @param[in] prikeyid        私钥ID
* @param[in] sm2id			 SM2签名者ID
* @param[in] idlen			 签名者ID长度
* @param[in] pDatain         待签名数据
* @param[in] dlen            待签名数据长度
* @param[out] signData       输出签名数据,缓冲区长度必须大于64字节
* @param[out] outlen         输出数据长度
*
* @return 错误码
* @retval XKR_NO_POWER  权限不够
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM2SignEx3(XKF_HANDLE hHandle, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *prikeyid, const unsigned char *sm2id, unsigned int idlen, const unsigned char *pDatain, int dlen,
                              unsigned char *signData, unsigned int *outlen);

/**
* @brief SM2数据签名验证（数据未hash）
* 所有数据传给COS，COS内部做hash和签名验证
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥ID
* @param[in] sm2pubkey       签名用公钥，当pubkeyid为0x00 0x00时使用
* @param[in] sm2id			 SM2签名者ID
* @param[in] idlen			 签名者ID长度
* @param[in] pDatain         待签名数据
* @param[in] dlen            待签名数据长度
* @param[in] signData        验签数据
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_SM2SignVerifyEx3(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *sm2id, unsigned int idlen, const unsigned char *pDatain,
                                    int dlen, unsigned char *signData);

/**
* @brief SM2协商密钥初始化
*
* @param[in] hHandle          设备句柄
* @param[in] pubkeyid         SM2公钥ID 两字节,第二个字节有效,第一字节必须为0x00
* @param[out] pdataout        产生协商数据
* @param[out] outlen          输出数据长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM2KeyGenInit(XKF_HANDLE hHandle, const unsigned char *pubkeyid, unsigned char *pdataout, unsigned int *outlen);
/**
* @brief SM2协商密钥 计算步骤
*
* @param[in] hHandle          设备句柄
* @param[in] pubkeyid         SM2公钥ID 两字节,第一节字必须为0x00,第二个字节有效 当dictflag=SM2_KEY_GENERATE_DICT_SEND 时 公钥ID为0x00x00
* @param[in] prikeyid         SM2私钥ID 两字节,第一节字必须为0x00,第二个字节有效
* @param[in] pDatain          输入数据
*								当dictflag=SM2_KEY_GENERATE_DICT_SEND 时，输入数据为 响应方的ID（TLV格式）||响应方公钥x坐标（TLV格式）||响应方公钥y坐标（TLV格式）||响应方临时公钥x坐标（TLV格式）||响应方临时公钥y坐标(TLV格式)
*								当dictflag=SM2_KEY_GENERATE_DICT_RECV 时，输入数据为 发起方的ID（TLV格式）||发起方公钥x坐标（TLV格式）||发起方公钥y坐标（TLV格式）||发起方临时公钥x坐标（TLV格式）||发起方临时公钥y坐标(TLV格式)
* @param[in] dlen             输入数据长度
* @param[out] pDataout        产生协商数据
* @param[out] outlen          输出数据长度
* @param[in] dictflag         发起对象,SM2_KEY_GENERATE_DICT_SEND为发起方,SM2_KEY_GENERATE_DICT_RECV为响应方]
* @param[in] prikeyflag       密钥存储标记 1固定位置,0临时位置
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM2KeyGenCompute(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *pDataout,
                                    unsigned int *outlen, unsigned char dictflag, unsigned char keyflag);
/**
* @brief SM2协商密钥 计算步骤
* 说明：验证对端身份，仅支持发起方使用
*
* @param[in] hHandle          设备句柄
* @param[in] pubkeyid         SM2公钥ID 两字节,第一节字必须为0x00,第二个字节有效 当dictflag=SM2_KEY_GENERATE_DICT_SEND 时 公钥ID为0x00x00
* @param[in] prikeyid         SM2私钥ID 两字节,第一节字必须为0x00,第二个字节有效
* @param[in] pDatain          输入数据
*							  输入数据为 响应方的ID（TLV格式）||响应方公钥x坐标（TLV格式）||响应方公钥y坐标（TLV格式）||响应方临时公钥x坐标（TLV格式）||响应方临时公钥y坐标(TLV格式)
* @param[in] dlen             输入数据长度
* @param[out] pDataout        产生协商数据
* @param[out] outlen          输出数据长度
* @param[in] dictflag         发起对象,仅支持SM2_KEY_GENERATE_DICT_SEND为发起方
* @param[in] prikeyflag       密钥存储标记 2 仅支持车载
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM2KeyGenComputeEx(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *pDataout,
                                      unsigned int *outlen, unsigned char dictflag, unsigned char keyflag);

/**
* @brief SM2协商密钥验证
*
* @param[in] hHandle         设备句柄
* @param[in] pDatain         输入数据
* @param[in] dlen            输入数据长度 固定32字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM2KeyGenVerify(XKF_HANDLE hHandle, const unsigned char *pDatain, int dlen);
/**
* @brief SM2协商密钥验证
* 说明：车载专用
*
* @param[in] hHandle         设备句柄
* @param[in] pDatain         输入数据
* @param[in] dlen            输入数据长度 固定32字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM2KeyGenVerifyEx(XKF_HANDLE hHandle, const unsigned char *pDatain, int dlen);
/**
* @brief SM9数据签名
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        主公钥ID
* @param[in] prikeyid        签名私钥ID
* @param[in] pDatain         数据
* @param[in] dlen            长度
* @param[out] signData       输出签名数据,缓冲区长度至少96字节
* @param[out] outlen         输出数据长度
*
* @return 错误码
* @retval XKR_NO_POWER  权限不够
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM9Sign(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *signData, unsigned int *outlen);
/**
* @brief SM9数据签名验证
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        主公钥ID
* @param[in] idb             对方标识（公钥）
* @param[in] pDatain         数据
* @param[in] dlen            长度
* @param[in] signData        验签数据，96字节
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_SM9Verify(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char * idb, const unsigned char *pDatain, int dlen, unsigned char *signData);
/**
* @brief SM9公钥加密
*  密文结构： C1 C3 C2
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        主公钥ID
* @param[in] idb             对方标识（公钥）
* @param[in] pDatain         明文数据
* @param[in] dlen            数据长度
* @param[in] EncID           encryption identification,0:stream cipher 1:block cipher
* @param[out] pDataout       加密后密文,缓冲长度至少为dlen+96
* @param[out] outlen         加密后数据长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SM9Encrypt(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char * idb, const unsigned char *pDatain, int dlen, int EncID, unsigned char *pDataout,
                              unsigned int *outLen);
/**
* @brief SM9私钥解密
*
* @param[in] hHandle         设备句柄
* @param[in] prikeyid        私钥ID
* @param[in] idb             对方标识（公钥
* @param[in] pDatain         密文数据，最大**
* @param[in] dlen            数据长度
* @param[in] EncID           encryption identification,0:stream cipher 1:block cipher
* @param[out] pDataout       解密后的明文数据,缓冲区至少为dlen-96
* @param[out] outlen         解密后数据长度
*
* @return 错误码
* @retval XKR_OK        成功
* @retval XKR_NO_POWER  权限不够
*/
XDJAKEYAPI int XKF_SM9Decrypt(XKF_HANDLE hHandle, const unsigned char *prikeyid, const unsigned char * idb, const unsigned char *pDatain, int dlen, int EncID, unsigned char *pDataout,
                              unsigned int *outlen);

/************************************************************************/
/*TF卡专用接口                                                        */
/************************************************************************/
/**
* @brief 获取TF卡设备挂载路径
*
* @param[in] hHandle    设备句柄
* @param[out] mountpath 挂载路径  win32下获取盘符   Linux下获取挂载路径
* @param[out] pathlen   路径长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetTFMountPath(XKF_HANDLE hHandle, char* mountpath, int * pathlen);
/**
* @brief 获取隐藏分区容量
*
* @param[in] hHandle 设备句柄
* @param[out] size   返回隐藏分区扇区数量
*
* @return 错误码
* @retval 0 成功
*/
XDJAKEYAPI int XKF_GetTFZoneSize(XKF_HANDLE handle, int* size);
/**
* @brief 读TF卡内隐藏扇区,数据大小为字节
*
* @param[in]     hHandle      设备句柄
* @param[in]     sectorStart  扇区号
* @param[out]	 pDataBuf     数据缓冲区
* @param[in]     buffSize     数据大小
*
* @return 错误码
* @retval 0 成功
*/
XDJAKEYAPI int XKF_ReadTFZone(XKF_HANDLE handle, int sectorStart, unsigned char *pDataBuf, int buffSize);
/**
* @brief 写TF卡内隐藏扇区,数据大小为字节
* @param[in]     hHandle      设备句柄
* @param[in]     sectorStart  扇区号
* @param[in]	 pDataBuf     数据缓冲区
* @param[in]     buffSize    数据大小
*
* @return 错误码
* @retval 0 成功
*/
XDJAKEYAPI int XKF_WriteTFZone(XKF_HANDLE handle, int sectorStart, unsigned char *pDataBuf, int buffSize);

/************************************************************************/
/*加密U盘专用接口                                                        */
/************************************************************************/

/**
* @brief 获取加密U盘指定分区的挂载路径
*
* @param[in] hHandle 设备句柄
* @param[in] type    分区类型，含普通区、加密区、高速盘分区三种
* @param[out] path   返回该分区的挂载路径
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetUsbMountPath(XKF_HANDLE hHandle, USB_FLASH_TYPE type, unsigned char* path);
/**
* @brief 修改加密U盘FLASH读写模式
*
* @param[in] hHandle 设备句柄
* @param[in] mode    新的读写模式：普通区临时可写、临时只读、永久可写、永久只读，高速盘临时可写 共五种
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_SetUsbRWMode(XKF_HANDLE hHandle, USB_FLASH_RW_MODE mode);
/**
* @brief 读加密U盘普通区扇区
*
* @param[in] hHandle 设备句柄
* @param[in] addr    扇区起始地址
* @param[in] secs    扇区数量
* @param[out] pdata  数据接收缓冲区
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ReadUsbNormalSecs(XKF_HANDLE hHandle, int addr, short secs, unsigned char* pdata);
/**
* @brief 写加密U盘普通区扇区
*
* @param[in] hHandle 设备句柄
* @param[in] addr    扇区起始地址
* @param[in] secs    扇区数量
* @param[in] pdata  待写数据缓冲区
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_WriteUsbNormalSecs(XKF_HANDLE hHandle, int addr, short secs, unsigned char* pdata);
/**
* @brief 打开加密U盘加密区
*
* @param[in] hHandle 设备句柄
* @param[in] pass    口令
* @param[in] passlen 口令长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_OpenUsbSecuZone(XKF_HANDLE hHandle, const unsigned char* pass, int passlen);
/**
* @brief 打开加密U盘加密区，加密盘和PIN口令绑定，需要传入PIN对应的角色
*
* @param[in] hHandle 设备句柄
* @param[in] role	 PIN角色
* @param[in] pass    口令
* @param[in] passlen 口令长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_OpenUsbSecuZoneEx(XKF_HANDLE hHandle, unsigned char role, const unsigned char* pass, int passlen);
/**
* @brief 关闭加密U盘加密区
*
* @param[in] hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_CloseUsbSecuZone(XKF_HANDLE hHandle);
/**
* @brief 修改加密U盘加密区口令
* 注：如果旧口令不正确，卡内部就会较少一次旧口令的重试次数。修改口令可以被认为是认证旧口令、修改新口令的联合操作。
*
* @param[in] hHandle 设备句柄
* @param[in] oldpass 旧口令
* @param[in] oldlen  旧口令长度
* @param[in] newpass 新口令
* @param[in] newlen  新口令长度
* @param[in] type    口令类型：1加密盘口令； 2加密盘解锁口令
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ChgUsbSecuZonePin(XKF_HANDLE hHandle, const unsigned char* oldpass, int oldlen, const unsigned char* newpass, int newlen, int type);
/**
* @brief 解锁加密盘口令
* 条件：要求输入正确的加密盘解锁口令
*
* @param[in] hHandle 设备句柄
* @param[in] key     解锁口令
* @param[in] keyLen  解锁口令长度
* @param[in] pin     新的口令
* @param[in] pinLen  新口令的长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_UnlockUsbSecuZone(XKF_HANDLE hHandle, const unsigned char *key, int keyLen, const unsigned char *pin, int pinLen);
/**
* @brief 初始化加密U盘隐藏区
*
* @param[in] hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_InitUsbHiddZone(XKF_HANDLE hHandle);
/**
* @brief 获取加密U盘隐藏扇区大小
*
* @param[in]  hHandle 设备句柄
* @param[out] hdSize  返回大小
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetUsbHiddZoneSize(XKF_HANDLE hHandle, unsigned int * hdSize);
/**
* @brief 读加密U盘隐藏扇区
*
* @param[in] hHandle     设备句柄
* @param[in] dwStartAddr 起始扇区地址
* @param[out] pOutBuff    读缓冲
* @param[in] buffSize    要读取的长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ReadUsbHiddZone(XKF_HANDLE hHandle, unsigned int dwStartAddr, void* pOutBuff, unsigned int buffSize);
/**
* @brief 写加密U盘隐藏扇区
*
* @param[in] hHandle     设备句柄
* @param[in] dwStartAddr 起始扇区地址
* @param[in] pOutBuff    写缓冲
* @param[in] buffSize    要写入长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_WriteUsbHiddZone(XKF_HANDLE hHandle, unsigned int dwStartAddr, void * pInBuff, unsigned int buffSize);
/**
* @brief 发送USB SCSI指令
*
* @param[in] hHandle     设备句柄
* @param[in] pCDBbuff    CDB
* @param[in] cdbLength   CDB长度
* @param[in] sendDataBuf 发送数据缓冲
* @param[in] sendDataLen 发送数据长度
* @param[out] recvDataBuf 接收数据缓冲
* @param[out] recvDataLen 接收数据长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ExecUsbScsiCmd(XKF_HANDLE hHandle, void* pCDBbuff, unsigned int cdbLength, void* sendDataBuf, unsigned int sendDataLen, void * recvDataBuf, unsigned int * recvDataLen);
/***********************************************************************/
/*二代U盾专用接口                                                       */
/***********************************************************************/

/**
* @brief 判断设备是否二代U盾
*
* @param[in] hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_Is2gKey(XKF_HANDLE hHandle);
/**
* @brief 二代盾签名
*
* @param[in] hHandle   设备句柄
* @param[in] prikeyid  私钥ID
* @param[in] pDatain   签名数据
* @param[in] dlen      签名数据长度
* @param[in] pDatain   签名结果
* @param[in] dlen      签名结果长度
* @param[in] dataType  签名数据类型
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_2gKeySign(XKF_HANDLE hHandle, const unsigned char * prikeyid, const unsigned char * pDatain, int dlen, unsigned char *pDataout, unsigned int *outlen, int dataType);
/**
* @brief 获取2代盾剩余电量
*
* @param[in] hHandle 设备句柄
* @param[out] state  充电状态:  1表示未充电, 0表示正在充电
* @param[out] power  返回值为百分比值,例如返回10表示剩余10%的电量
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetRemainPower(XKF_HANDLE hHandle, int * state, int * power);


/***********************************************************************/
/*USB专用接口                                                          */
/***********************************************************************/

/**
* @brief 打开指定设备,返回设备句柄
*  说明：无需枚举设备
*
* @param[in]   devPath 例如：\\?\USB#Vid_04e8&Pid_503b#0002F9A9828E0F06#{a5dcbf10-6530-11d2-901f-00c04fb951ed}
* @param[out]  hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_OpenDevByPath(const unsigned char * devPath, XKF_HANDLE * hHandle);
/**
* @brief 打开指定设备,返回设备句柄
*  说明：无需枚举设备，薄膜卡专用
*
* @param[in]   readerName 通过Windows SmartCard API函数SCardListReaders枚举到的具体Reader名称
* @param[out]  hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_OpenDevByReader(const unsigned char * readerName, XKF_HANDLE * hHandle);

/**
* @brief 获取加密盘打开状态
*
* @param[in]   hHandle 设备句柄
* @param[out]  pucState 打开状态.0:关闭,1:打开
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetSecuZoneOpenState(XKF_HANDLE hHandle, unsigned char* pucState);

/***********************************************************************/
/*设置第三方国密库名称                                                 */
/***********************************************************************/

/**
* @brief 设置第三方国密库名称
*
* @param[in]   pThirdPartySoName
*
* @return 无
*/
XDJAKEYAPI int XKF_SetThirdPartySoName(const char* pThirdPartySoName);

/***********************************************************************/
/*指纹KEY专用接口                                                      */
/***********************************************************************/

/**
* @brief 录入指纹
*  说明：需要进行PIN 口令认证，指纹录入成功后将自动绑定当前角色。
*
* @param[in] hHandle 设备句柄
* @param[in] state	 录入指纹状态：0-发起录入 1-查询录入状态
* @param[out] fpIndex 返回录入成功的指纹编号
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_EnrollFp(XKF_HANDLE hHandle, unsigned char state, unsigned char *fpIndex);

/**
* @brief 验证指纹
*  说明：指纹验证通过后，如果该指纹已绑定角色，则安全芯片将置为对应角色的安全权限
*
* @param[in] hHandle 设备句柄
* @param[in] state	 验证指纹状态：0-发起指纹验证 1-查询验证状态
* @param[out] fpIndex 返回验证成功的指纹编号
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_VerifyFp(XKF_HANDLE hHandle, unsigned char state, unsigned char *fpIndex);

/**
* @brief 删除指纹
*  说明：删除指纹同时删除绑定的角色信息，删除所有指纹的操作要求已存在的指纹都为同一角色并且PIN口令认证通过
*
* @param[in] hHandle 设备句柄
* @param[in] index	 删除指纹索引 0xFF-删除所有指纹 00 01 02删除指定指纹
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_DeleteFp(XKF_HANDLE hHandle, unsigned char index);

/**
* @brief 取消录入/取消验证
*  说明：该指令执行成功后，需要使用录入/验证的查询状态指令读取实际执行结果，以查询出的最终结果为准
*
* @param[in] hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_CancelFp(XKF_HANDLE hHandle);

/**
* @brief 获取指纹列表
*
* @param[in]  hHandle 设备句柄
* @param[out] fplist  指纹列表 两个字节为一组（最多三组），第一个字节为设备指纹编号（00~02），第二个字节为绑定角色（00为未绑定），数据长度6，默认全F
* @param[out] outlen
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetFpList(XKF_HANDLE hHandle, unsigned char* fplist, unsigned int* outlen);

/**
* @brief 获取当前指纹模块状态
*
* @param[in]  hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GetFpState(XKF_HANDLE hHandle);

/***********************************************************************/
/*蝴蝶密钥相关接口                                                     */
/***********************************************************************/
/**
* @brief 蝴蝶密钥初始化,应先设置相应算法曲线参数
*	说明：产生种子签名公私钥（a, A）、种子加密公私钥（p, P），随机对称密钥ck、ek
*
* @param[in] hHandle			设备句柄
* @param[in] asymalg			非对称算法类型0_SM2, 1_ECDSA
* @param[in] signSeedPriFid     种子签名私钥文件id
* @param[in] encSeedPriFid      种子加密私钥文件id
* @param[out] A					种子签名公钥A，固定长度64字节
* @param[out] P					种子加密公钥P，固定长度64字节
* @param[out] ck				用于签名密钥扩展计算的ck，固定长度16字节
* @param[out] ek				用于加密密钥扩展计算的ek，固定长度16字节
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_BKInit(XKF_HANDLE hHandle, unsigned char asymalg, const unsigned char *signSeedPriFid, const unsigned char *encSeedPriFid, unsigned char *A, unsigned char *P, unsigned char *ck,
                          unsigned char *ek);

/**
* @brief 蝴蝶密钥加密密钥点乘
*
* @param[in] hHandle    设备句柄
* @param[in] asymalg    非对称算法类型0_SM2, 1_ECDSA
* @param[in] symalg     对称算法类型  参数保留，默认0
* @param[in] i			序列值i
* @param[in] j			序列值j
* @param[in] ek			用于解密私钥计算的ek
* @param[in] prifid		私钥id
* @param[in] xybuf		点乘输入的点坐标x[32B]+y[32B]
* @param[in] xylen		64
* @param[out] outdata   点乘结果的xy
* @param[out] datalen   点乘结果输出长度
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_BKTmpEnPriCalc(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, unsigned int i, unsigned int j, unsigned char* ek, unsigned char *prifid, unsigned char* xybuf,
                                  int xylen, unsigned char* outdata, int *datalen);

/**
* @brief 蝴蝶密钥解密-CA返回数据
*
* @param[in] hHandle			设备句柄
* @param[in] asymalg			非对称算法类型0_SM2, 1_ECDSA
* @param[in] symalg				对称算法类型  参数保留，默认0
* @param[in] i					序列值i
* @param[in] j					序列值j
* @param[in] ek					初始化用于加密密钥扩展计算的ek
* @param[in] encSeedPriFid		种子加密私钥文件id
* @param[in] inData				密文数据，格式：04|C1|C2|C3
* @param[in] inLen				密文数据长度
* @param[out] outData			明文
* @param[out] outLen			明文长度
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_BKDecrypt(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, unsigned int i, unsigned int j, unsigned char* ek, unsigned char *encSeedPriFid, unsigned char *inData,
                             int inLen, unsigned char* outData, int *outLen);

/**
* @brief 蝴蝶密钥隐式证书时，根据公钥重构值计算最终签名公钥
*	说明：最终签名公钥：ePu + Qca，其中e为CA返回证书的摘要值，Pu为证书中的公钥，即Bl+C，Qca为CA公钥
*
* @param[in] hHandle			设备句柄
* @param[in] asymalg			非对称算法类型0_SM2, 1_ECDSA, 2_brainpoolp256r1
* @param[in] e					e值，即证书数据的摘要值,固定长度32字节
* @param[in] constructPubKey	公钥重构值，隐式证书中的公钥，即：Bl+C，固定长度64字节
* @param[in] caPubKey			CA公钥
* @param[out] pubKey			最终签名公钥
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_BKCalcSignPubkey(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char * e, unsigned char* constructPubKey, unsigned char *caPubKey, unsigned char* pubKey);

/**
* @brief 蝴蝶密钥计算最终签名私钥
*	说明：显式证书时在计算：bl+c(mod n)，其中bl为扩展签名私钥，c为CA返回的私钥重构值，n为曲线参数n。
隐式证书时在计算：e*bl+r(mod n)，其中e为CA返回证书的摘要值，bl为扩展签名私钥，r为CA返回的私钥重构值，n为曲线参数n。
*
* @param[in] hHandle    设备句柄
* @param[in] asymalg    非对称算法类型0_SM2, 1_ECDSA
* @param[in] symalg     对称算法类型   参数保留，默认0
* @param[in] i			序列值i
* @param[in] j			序列值j
* @param[in] ck			初始化用于签名密钥扩展计算的ck
* @param[in] signSeedPriFid	种子签名私钥文件id
* @param[in] priFid		私钥id
* @param[in] certType	证书类型 0 显式证书， 1 隐式证书
* @param[in] component  CA端的私钥重构值 显式（c）隐式（r）
* @param[in] e			CA端证书的hash值在certtype==1时有效
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_BKCalcSignPrikey(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, unsigned int i, unsigned int j, unsigned char* ck, unsigned char *seedprifid,
                                    unsigned char *prifid, int certtype, unsigned char* component, unsigned char* e);

/**
* @brief 蝴蝶密钥计算.取到的证书及计算出的公私钥写入相应文件.
*
*
* @param[in] hHandle		设备句柄
* @param[in] algType		非对称算法类型0_SM2, 1_ECDSA
* @param[in] certType		证书类型,0:ExpCert、1:ImCert
* @param[in] i				序列值i
* @param[in] j				序列值j
* @param[in] ck				用于签名密钥扩展计算的ck，固定长度16字节
* @param[in] ek				用于加密密钥扩展计算的ek，固定长度16字节
* @param[in] caPubKey		CA公钥(x,y)
* @param[in] encCertData	证书密文
* @param[in] encCertLen		证书密文长度
* @param[in] signSeedPriFid	种子签名私钥ID
* @param[in] encSeedPriFid	种子加密私钥ID
* @param[in] pubKeyId		公钥ID
* @param[in] priKeyId		私钥ID
* @param[in] certFileId		证书ID
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_BKCalc(XKF_HANDLE hHandle, unsigned char algType, unsigned char certType, unsigned int i, unsigned int j, unsigned char* ck, unsigned char* ek, unsigned char* caPubKey,
                          unsigned char* encCertData, int encCertLen, unsigned char* signPriFid, unsigned char* encPriFid, unsigned char* pubKeyId, unsigned char* priKeyId, unsigned char* certFileId);

/**
* @brief 蝴蝶密钥计算私钥并对输入数据签名
* 说明：显式证书时在计算：bl+c(mod n)，其中bl为扩展签名私钥，c为CA返回的私钥重构值，n为曲线参数n。
*隐式证书时计算：e*bl+r(mod n)，其中e为CA返回证书的摘要值，bl为扩展签名私钥，r为CA返回的私钥重构值，n为曲线参数n。
*SM2数据签名
*
* @param[in] hHandle    	设备句柄
* @param[in] asymalg    	非对称算法类型0_SM2, 1_ECDSA
* @param[in] symalg     	对称算法类型   参数保留，默认0
* @param[in] certType   	证书类型 0 显式证书， 1 隐式证书
* @param[in] datatype   	数据类型,SIGN_HASH表示inData为经过预处理的e值;SIGN_NOHASH表示原始数据
* @param[in] i          	序列值i
* @param[in] j          	序列值j
* @param[in] ck         	初始化中用于签名密钥扩展计算的ck
* @param[in] signSeedPriFid 种子签名私钥文件id
* @param[in] component    	CA端的私钥重构值 显式（c）|隐式（r）
* @param[in] e            	CA端证书的hash值在certtype=1(隐式证书)时有效
* @param[in] inData       	输入待签名数据
* @param[in] inLen        	数据长度,如果是摘要数据长度(datatype=SIGN_HASH)必须为32
* @param[out] signData    	输出签名数据,缓冲区长度必须大于64字节,数据格式：32字节r+32字节s
* @param[out] outlen      	输出数据长度
*
* @return 错误码
* @retval XKR_NO_POWER  权限不够
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_BKCalcPriAndSign(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, int certType, int datatype, unsigned int i, unsigned int j, unsigned char* ck,
                                    unsigned char *signSeedPriFid, unsigned char* component, unsigned char* e, unsigned char *inData, int inLen, unsigned char* signData, int *outLen);

/**
* @brief 蝴蝶密钥扩展私钥签名
*
* @param[in] hHandle		设备句柄
* @param[in] asymalg		非对称算法类型0_SM2, 1_ECDSA
* @param[in] symalg			对称算法类型  参数保留，默认0
* @param[in] i				序列值i
* @param[in] j				序列值j
* @param[in] ck				初始化中用于签名密钥扩展计算的ck
* @param[in] signSeedPriFid 种子签名私钥id
* @param[in] in				输入数据，SM2算法时为预处理后的数据，ECDSA算法时为sha256之后的hash数据
* @param[out] out			签名值
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_BKPrikeySign(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, unsigned int i, unsigned int j, unsigned char* ck, unsigned char *signSeedPriFid, unsigned char* in, unsigned char* out);

/**
* @brief ECC公钥加密
*  XDJA密文结构： 0x04 | x(32B) | y(32B) | 密文 | HASH(32B)
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        SM2公钥ID，两字节，第二个字节有效 ，为0x00 0x00表示公钥随数据传入
* @param[in] sm2pubkey       公钥,当pubkeyid为0x00 0x00时有效
* @param[in] pDatain         明文数据,最大长度不超过158
* @param[in] dlen            数据长度
* @param[out] pDataout       加密后密文,缓冲长度至少为dlen+97
* @param[out] outlen         加密后数据长度
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ECIESEncrypt(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_ECC_PUBKEY sm2pubkey, const unsigned char *pDatain, int dlen, unsigned char *pDataout,unsigned int *outLen);

/**
* @brief SM2私钥解密
*
* @param[in] hHandle         设备句柄
* @param[in] prikeyid        SM2私钥ID 两字节，第二个字节有效
* @param[in] pDatain         密文数据,最大长度不超过SM2_BLOCK_MAX+97
* @param[in] dlen            数据长度
* @param[out] pDataout       解密后的明文数据,缓冲区至少为dlen-97
* @param[out] outlen         解密后数据长度
*
* @return 错误码
* @retval XKR_OK        成功
* @retval XKR_NO_POWER  权限不够
*/
XDJAKEYAPI int XKF_ECIESDecrypt(XKF_HANDLE hHandle, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *pDataout,unsigned int *outlen);

/************************************************************************/
/*芯片低功耗相关接口                                                    */
/************************************************************************/

/**
* @brief 芯片进入休眠
*
* @param[in] hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ChipEnterSleep(XKF_HANDLE hHandle);

/**
* @brief 芯片进入超低功耗
*
* @param[in] hHandle 设备句柄
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ChipEnterLowPower(XKF_HANDLE hHandle);

/**
* @brief 芯片退出休眠
*
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ChipExitSleep();

/**
* @brief 创建文件
* 条件:具有当前目录下，创建文件的权限
*
* @param[in] hHandle 设备句柄
* @param[in] pFile   XDJA_CONTAINER_FILE文件属性结构
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_CreateContainerFile(XKF_HANDLE hHandle, PXDJA_CONTAINER_FILE pFile);

/**
* @brief SPI配置信息
* 每个进程打开设备前需要配置一次
*
* @param[int] config 配置信息
*
* @return 错误码
* @retval XKR_OK 成功
*/

XDJAKEYAPI int XKF_SPI_CONFIG(XDJA_SPI_CONFIG config);

/***********************************************************************/
/*EDDSA相关接口                                                        */
/***********************************************************************/
/**
* @brief 生成ED25519密钥对（目前仅支持密钥出卡的方式）
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥文件ID,为0x00 0x00时表示公钥导出卡外
* @param[in] prikeyid        私钥文件ID,公私钥ID均为0x00 0x00时表示私钥导出卡外
* @param[out] pubkeyED25519公钥结构，公钥文件ID为0x00 0x00时有效
* @param[out] prikeyED25519私钥结构，公私钥文件ID均为0x00 0x00时有效
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_GenED25519KeyPair(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, PXDJA_ED25519_PUBKEY pubkey, PXDJA_ED25519_PRIKEY prikey);

/**
* @brief ED25519数据签名
*
* @param[in] hHandle         设备句柄
* @param[in] pubkey       ED25519公钥结构
* @param[in] prikeyid        私钥ID，目前仅支持卡外私钥传入方式，即本字段传入"\x00\x00"
* @param[in] prikey             ED25519私钥结构
* @param[in] pDatain         待签名数据
* @param[in] dataLen         待签名数据长度
* @param[out] signData       输出签名数据,缓冲区长度固定64字节
*
* @return 错误码
* @retval XKR_OK 成功
*/
XDJAKEYAPI int XKF_ED25519Sign(XKF_HANDLE hHandle, PXDJA_ED25519_PUBKEY pubkey, const unsigned char *prikeyid, PXDJA_ED25519_PRIKEY prikey, const unsigned char *pDatain, unsigned int dataLen, unsigned char *signData);

/**
* @brief ED25519数据签名验证
*
* @param[in] hHandle         设备句柄
* @param[in] pubkeyid        公钥ID，目前仅支持卡外公钥传入方式，即本字段传入"\x00\x00"
* @param[in] pubkey       签名用公钥，当pubkeyid为0x00 0x00时使用
* @param[in] pDatain         待签名数据
* @param[in] dataLen         待签名数据长度
* @param[in] signData        验签数据，固定64字节
*
* @return 错误码
* @retval XKR_OK        成功
*/
XDJAKEYAPI int XKF_ED25519SignVerify(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_ED25519_PUBKEY pubkey, const unsigned char *pDatain, unsigned int dataLen, unsigned char *signData);

/***********************************************************************/
/*单机版软件密码模块专用接口                                           */
/***********************************************************************/
//XDJAKEYAPI int XKF_VHSMInitModule( int devType, unsigned char* pin, int plen );
#ifdef __cplusplus
}

#endif

#endif

