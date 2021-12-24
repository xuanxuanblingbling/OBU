#ifndef COMMON_H
#define COMMON_H

//#include "SecLayer.h"

#define LOCAL_CERTFILE_DIR "/mnt/APP/Config/certs" /*系统中存储证书的根目录*/

#define VIN ("EA")                        /*应用证书下载时需要用到的VIN*/
#define ACA_URL "http://39.96.75.192:999" /*应用证书下载地址*/

#define PTR_SIZE (sizeof(void *)) /*指针占用的字节数*/
#define CERT_HAVE_UPDATE (1)      /*证书已更新*/


#define CERT_TYPE 1 //输入证书类型:1 PC，2 AC ,3 保留



#define SECLAYER_ERR(fmt, ...) printf("\033[31m[Seclayer: %s:%d:%s:%s] " #fmt "\033[0m\r\n", __func__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__)
#define SECLAYER_INFO(fmt, ...) printf("\033[32m[Seclayer: %s:%d:%s:%s] " #fmt "\033[0m\r\n", __func__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__)

#define IS_OK 0

enum cert_status
{
    CERT_NORMAL = 0,
    CERT_CHANGED, //签名签名证书改变
};

struct seclayer_status_t
{
    enum cert_status cert_change_flg; //签名证书是否改变
};

//回调函数，通知安全层状态到上层应用。目前用于通知签名证书的改变。
typedef void (*seclayer_status_callback)(struct seclayer_status_t *sta, void *para);


enum sign_mode
{
    SMALL_MODE_SIGN = 0, //以小模式进行签名
    BIG_MODE_SIGN        //以大模式进行签名
};

struct postion_t
{
    double longitude; //经度
    double latitude;  //纬度
};

/*消息队列通信数据结构体*/
struct MsgQueueDataStruct
{
    int32_t m_n32DataSize;
    uint8_t m_u8Buf[0];
};

struct IwallSecLayerInfo
{
    int32_t m_n32MsgQueueId;           /*消息队列ID*/
    pthread_mutex_t m_tSecLayerLocker; /*对自身结构体的锁*/
    pthread_t m_tCertUpdateTid;        /*证书更新线程ID*/
    int32_t m_n32CertUpdateFlag;       /*证书更新标识。1:表示证书已更新，需要重新获取证书状态*/
    int8_t m_n8IwallLibName[256];
    int8_t m_n8SignCertPathName[256];
    int8_t m_n8SignCertJsonInfo[256];
    int8_t m_n8CertsPath[256];
    int8_t m_n8ChipLogPath[256];
};


typedef unsigned char uint8_t;		 /* 无符号8位整型变量  */
typedef signed char int8_t;			 /* 有符号8位整型变量  */
typedef unsigned short uint16_t;	 /* 无符号16位整型变量 */
typedef signed short int16_t;		 /* 有符号16位整型变量 */
typedef unsigned int uint32_t;		 /* 无符号32位整型变量  */
typedef signed int int32_t;			 /* 有符号32位整型变量  */
// typedef unsigned long long uint64_t; /* 无符号64位整型变量  */
// typedef signed long long int64_t;	 /* 有符号64位整型变量  */
typedef float fp32;					 /* 单精度浮点数（32位长度）*/
typedef double fp64;				 /* 双精度浮点数（64位长度）*/
#endif
