#ifndef XDJA_NEW_FOUR_CROSS_H
#define XDJA_NEW_FOUR_CROSS_H

#include <stdint.h>

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
struct xdja_seclayer_info_t
{
    int32_t first_paket;              //1表示为第一包签名数据；
    int32_t curr_cert_id;             //当前使用的证书id
    uint32_t last_big_mode_time_ms;   //最近一次携带完整证书(大模式)的时间
    uint32_t cert_used_first_time_ms; //当前证书第一次使用的时间
    struct postion_t last_pos;        //第一次使用当前证书签名时的位置
    seclayer_status_callback cb_fun;  //回调函数，用于证书切换时通知上层应用
    void *cb_para;                    //回调函数参数
    pthread_mutex_t seclayer_lock;    //对句柄进行加锁
};

struct XdjaPinConfig
{
    int32_t m_n32EncryptChipPinInt0;  //加密芯片引脚配置 6q RSU：166 132 OBU：92 85
    int32_t m_n32EncryptChipPinInt1;  //加密芯片POR复位引脚【可选，不使用保持-1】
    int32_t m_n32EncryptChipPinPor;   //加密芯片GPIO供电引脚【可选，不使用保持-1】
    int32_t m_n32EncryptChipPinPower; //加密芯片低功耗唤醒引脚【可选，不使用保持-1】
    int32_t m_n32EncryptChipPinQwk;   //EncryptChipPinQwk = -1
    int32_t m_n32EncryptChipSpeed;    //加密芯片SPI频率配置,默认20/MHz
};


#define SEC_EncryptChipPinPor -1   //加密芯片POR复位引脚【可选，不使用保持-1】
#define SEC_EncryptChipPinPower -1 //加密芯片GPIO供电引脚【可选，不使用保持 - 1】
#define SEC_EncryptChipPinQwk -1   //加密芯片低功耗唤醒引脚【可选，不使用保持-1】

#define PC_CERTS_NUM (20)           //20个PC证书
#define CERT_EXPIRED_TIME (300000)  //300秒换一张证书
#define BIG_SMALL_MODE_CYCLE (450)  //一大四小模式450毫秒为一个周期
#define CERT_CHANGE_DISTANCE (2000) //超过2000m后再进行证书切换

#define PC_CERT_SIGN (1) /*使用pc证书进行签名*/
#define AC_CERT_SIGN (2) /*使用ac证书进行签名*/
#define COMPLETE_CERT (2)

uint32_t SecChipFactoryCheck();
uint32_t RandomCertIdGet(void);
int32_t SecChip_Init(seclayer_status_callback cb, void *cb_para, const char *fileName);
int32_t SecDataSign_RSU(uint64_t aid,
                                    uint8_t *pdu, int32_t pdu_size,
                                    uint8_t *spdu, int32_t *spdu_size);

int32_t SecDataSign_OBU(uint64_t aid, int32_t emergency_event_flag,
                                  double longitude, double latitude,
                                  uint8_t *pdu, int32_t pdu_size, uint8_t *spdu, int32_t *spdu_size);


int32_t SecDataVerify(uint8_t *spdu, int32_t spdu_size,
                                 uint8_t *pdu, int32_t *pdu_size,
                                 uint64_t *p_pu64AID);
int32_t SecChipDeinit(void);

#endif