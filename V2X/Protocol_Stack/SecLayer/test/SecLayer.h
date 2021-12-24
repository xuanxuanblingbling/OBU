/*
 * SecLayer.h
 *
 *  Created on: Apr 7, 2020
 *      Author: wanijv2x
 */

#ifndef SECLAYER_SECLAYER_H_
#define SECLAYER_SECLAYER_H_
#include <stdint.h>
#include "SecDataInfo.h"

#define DLL_PUBLIC __attribute__((visibility("default")))

/**
 * 安全层初始化
 * 
 * @param void
 * 
 * @return int32_t 0:成功；-1:失败
 */

DLL_PUBLIC int32_t SecureLayerInit(seclayer_status_callback cb, void *cb_para, const char *fileName);

/**************************************************
*名称： 安全层消息签名
*描述： 将待签名数据按照aid和使用证书类型，签名组成安全消息,输出安全消息码流及长度, 签名时自动选择之前导入的应用证书进行签名。
*参数：
*       n64AID			             [IN]       智能交通应用标识
*       u8UseCerType		         [IN]       使用证书类型
*       pu8MsgLayData			     [IN]       待签名数据
*       n32MsgLayDataLen             [IN]       待签名数据长度
*       pu8SecLayData	             [OUT]      签名后的安全层消息码流
*       pn32SecLayDataLen            [OUT]      签名后的安全层消息码流长度
*返回值：0————成功；
*     其他————错误号。
*说明：签名时自动选择之前导入的应用证书进行签名
**************************************************/
DLL_PUBLIC int32_t SignSecuredMessage(MsgLayData_st MsgLayData, uint8_t *pu8SecLayData, int32_t *pn32SecLayDataLen);
/**************************************************
*名称： 安全消息验签
*描述： 验证消息签名是否正确，如不正确，则返回错误码，正确则返回消息层数据，如果验签不同CA供应商的安全消息，需导入不同CA供应商的ACA证书/PCA证书用作验证证书链。
*参数：
*       pu8SecLayData		[IN]        待验签的安全层消息码流
*       n32SecLayDataLen    [IN]        待验签的安全层消息码流长度
*       pu8MsgLayData       [OUT]       通过验签的消息层数据码流
*       pn32MsgLayDataLen   [OUT]       通过验签的消息层数据码流长度
*       pu64AID             [OUT]       安全层消息内的智能交通应用标识
*返回值：0--成功；
*返回值：非0--错误号。
*说明：如果验签不同CA供应商的安全消息，需导入不同CA供应商的ACA证书/PCA证书用作验证证书链
**************************************************/
DLL_PUBLIC int32_t VerifySecuredMessage(uint8_t *pu8SecLayData, int32_t n32SecLayDataLen, MsgLayData_st *MsgLayData);
/**
 * 安全层反初始化。
 * 
 * @param void 
 * @return int32_t 0:成功;其他值为错误码
 * @note 调用此函数前保证签名、验签函数没有被调用(杀掉相关线程)
 * @author gdh    
 */
DLL_PUBLIC int32_t SecureLayerDeinit(void);

#endif /* SECLAYER_SECLAYER_H_ */
