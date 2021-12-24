#ifndef SECLAYER_H
#define SECLAYER_H

#include <stdint.h>


enum cert_status
{
    CERT_NORMAL = 0,
    CERT_CHANGED,   //签名签名证书改变
};


struct seclayer_status_t
{
    enum cert_status cert_change_flg;   //签名证书是否改变
};


//回调函数，通知安全层状态到上层应用。目前用于通知签名证书的改变。
typedef void (*seclayer_status_callback)(void *para, struct seclayer_status_t *sta);

/**
 * 安全层初始化
 *
 * @param cb[in] 回调函数
 * @param cb_para[in] 回调函数参数
 *
 * @return int32_t 0:成功;其他值为错误码。使用信大捷安提供的错误码。
 *
 * @author sdc
 */
int32_t seclayer_init(seclayer_status_callback cb, void *cb_para);

/**
 * 对消息进行签名
 *
 * @param aid[in] aid
 * @param emergency_event_flag[in] 紧急事件标志，不为0表示有紧急事件，此时应附加完整证书
 * @param longitude[in] 当前的经度坐标
 * @param latitude[in] 当前的纬度坐标
 * @param pdu[in] 需要签名的数据
 * @param pdu_size[in] 需要签名的数据大小
 * @param spdu[out] 签名后的数据
 * @param spdu_size[in/out] 签名后的数据大小。该指针必须初始化为存储签名后数据的空间的大小。
 *
 * @return int32_t 0:成功;其他值为错误码
 *
 * @author sdc
 */
int32_t seclayer_sign(int32_t aid, int32_t emergency_event_flag, double longitude, double latitude, uint8_t *pdu, uint32_t pdu_size, uint8_t *spdu, uint32_t *spdu_size);

/**
 * 对消息进行验签并提取出具体消息内容
 *
 * @param spdu[in] 接收到的签名数据
 * @param spdu_size[in] 签名数据的大小
 * @param pdu[in] 从数据中提取的消息
 * @param pdu_size[in/out] 提取的消息大小。该指针必须初始化为存储提取的数据的空间的大小。
 * @param aid[out] aid
 *
 * @return int32_t 0:成功;其他值为错误码
 *
 * @author sdc
 */
int32_t seclayer_verify(long aid, uint8_t *spdu, uint32_t spdu_size, uint8_t *pdu, uint32_t *pdu_size);

/**
 * 安全层反初始化。
 *
 * @param void[in]
 *
 * @return int32_t 0:成功;其他值为错误码
 *
 * @note 调用此函数前保证签名、验签函数没有被调用(杀掉相关线程)
 *
 * @author sdc
 */
int32_t seclayer_deinit(void);

#endif
