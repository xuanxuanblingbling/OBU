#ifndef COMMON_H
#define COMMON_H

#define LOCAL_CERTFILE_DIR "/mnt/APP/Config/certs"    /*系统中存储证书的根目录*/

#define VIN     ("EA")  /*应用证书下载时需要用到的VIN*/
#define ACA_URL "http://39.96.75.192:999"   /*应用证书下载地址*/

#define PTR_SIZE    (sizeof(void *))    /*指针占用的字节数*/

#define CERT_HAVE_UPDATE    (1)     /*证书已更新*/

#define MODULE_NAME "cert-manager"

/*消息队列通信数据结构体*/
struct MsgQueueDataStruct {
    int32_t m_n32DataSize;
    uint8_t m_u8Buf[0];
};


struct IwallSecLayerInfo {
    int32_t m_n32MsgQueueId;    /*消息队列ID*/
    pthread_mutex_t m_tSecLayerLocker;  /*对自身结构体的锁*/
    pthread_t m_tCertUpdateTid; /*证书更新线程ID*/
    int32_t m_n32CertUpdateFlag;    /*证书更新标识。1:表示证书已更新，需要重新获取证书状态*/
};

#endif
