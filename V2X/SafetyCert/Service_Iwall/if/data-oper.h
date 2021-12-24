#ifndef DATA_OPER_H
#define DATA_OPER_H

#include <stdint.h>

/**
 * 安全层初始化
 *
 * @param void
 *
 * @return int32_t 0:成功；-1:失败
 */
// extern  int32_t SecureLayerInit(void);
extern int32_t SecureLayerInit(int (*callback)());

/**
 * 数据签名接口
 *
 * @param p_u64Aid[in] 应用AID
 * @param p_pu8PlainData[in] 经过UPER编码的消息
 * @param p_n32PlainDataLen[in] 消息长度
 * @param p_pu8bSecuredMessage[out] 带证书的消息
 * @param p_pn32SecuredMessageLen[in/out]
 *                               带证书的消息大小
 *
 * @return int32_t 0:成功；-1:失败
 */
extern  int32_t SecureDataSign(uint64_t p_u64Aid,
                        uint8_t *p_pu8PlainData, int32_t p_n32PlainDataLen,
                        uint8_t *p_pu8bSecuredMessage, int32_t *p_pn32SecuredMessageLen);

/**
 * 数据验签接口
 *
 * @param p_pu8SecuredMsg[in] 带证书的安全消息
 * @param p_n32SecuredMsgSize[in] 安全消息大小
 * @param p_pu8PlainData[out] 去除证书后的消息
 * @param p_pn32PlainDataSize[in/out] 消息大小
 * @param p_pu64AID[out] 对应的应用AID
 *
 * @return int32_t 0:成功；-1:失败
 */
extern  int32_t SecureDataVerify(uint8_t *p_pu8SecuredMsg, int32_t p_n32SecuredMsgSize,
                         uint8_t *p_pu8PlainData, int32_t *p_pn32PlainDataSize, uint64_t *p_pu64AID);

/**
 * 安全层反初始化
 *
 * @param void
 *
 * @return int32_t 0:成功；-1:失败
 */
extern  int32_t SecureLayerDeinit(void);

#endif
