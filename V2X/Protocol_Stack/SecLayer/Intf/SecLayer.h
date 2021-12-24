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


struct SecInfoConfig
{
    int32_t m_n32IsInitSecLayer;      //是否初始化安全层 1：开，0：关
    int32_t m_n32Manufacture;         //1 is xdja ; 2 is iwall
    int32_t m_n32DevideType;          //用于OBU与RSU区分证书类型，1：假名证书（OBU），2：应用证书（RSU）
    int32_t m_n32ProtocolType;        //消息层版本标识 1：多版本兼容，3：三跨版本，4：四跨版本，5：新四跨版本，2：二期场景
    int32_t m_n32EncryptChipPinInt0;  //加密芯片引脚配置 6q RSU：166 132 OBU：92 85
    int32_t m_n32EncryptChipPinInt1;  //加密芯片POR复位引脚【可选，不使用保持-1】
    int32_t m_n32EncryptChipPinPor;   //加密芯片GPIO供电引脚【可选，不使用保持-1】
    int32_t m_n32EncryptChipPinPower; //加密芯片低功耗唤醒引脚【可选，不使用保持-1】
    int32_t m_n32EncryptChipPinQwk;   //EncryptChipPinQwk = -1
    int32_t m_n32EncryptChipSpeed;    //加密芯片SPI频率配置,默认20/MHz
};
#define MODULE_NAME "SecLayer"


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
