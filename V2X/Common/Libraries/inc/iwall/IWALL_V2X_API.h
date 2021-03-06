#ifndef __IWALL_V2X_API_H__
#define __IWALL_V2X_API_H__

#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif

/*
*名称： 初始化安全芯片
*描述： 初始化安全芯片
*参数： 无
*返回值：0————成功；其他————错误号。
*说明：第一次调用动态库接口时，需要调用该接口初始化安全芯片
*/
__attribute__((visibility("default"))) int IWALL_DeviceInit();

/*
*名称： 导入根证书
*描述： 导入根证书到安全芯片
*参数：
*       pbCert                   [IN] 证书编码
*       nCertLen                 [IN] 证书编码长度
*       pCertName                [IN] 证书名称
*       nCertType                [IN] 证书类型，ROOT：4， ECA：3， ACA：2， PCA：7
*       CA_Provider              [IN] CA供应商：大唐：0，国汽：1，华为：2
*返回值：0————成功；其他————错误号。
*说明：国汽CA证书不验证证书链
*/
__attribute__((visibility("default"))) int IWALL_ImportRootCertificate(unsigned char *pbCert, int nCertLen, const char *pCertName, int nCertType, int CA_Provider);

/*
*名称： 生成注册证书公钥文件
*描述： 生成公钥文件用来申请注册证书
*参数：
*        szFilePathName                [IN]  公钥文件路径，例如：./EA.key
*返回值：0————成功；其他————错误号。
*说明： 一个OBU设备只有一张注册证书，因此申请新的公钥文件，会删除老的注册证书及对应私钥
*/
__attribute__((visibility("default"))) int IWALL_GenKeyPair_File(const char *szFilePathName);

/*
*名称： 导入注册证书
*描述： 将注册证书写入安全芯片
*参数：
*       pbCert                   [IN] 证书编码
*       pCertLen                 [IN] 证书长度
*返回值：0————成功；其他————错误号。
*说明：无
*/
__attribute__((visibility("default"))) int IWALL_ImportEnrollmentCredential(unsigned char *pbCert, int nCertLen);

/*
*名称： 导入注册证书
*描述： 将注册证书写入安全芯片
*参数：
*       pbCert                   [IN] 证书编码
*       pCertLen                 [IN] 证书长度
*返回值：0————成功；其他————错误号。
*说明：无
*/
__attribute__((visibility("default"))) int IWALL_ImportAplicationCertificate(unsigned char *pbCert, int nCertLen);
/*
*名称： 在线申请假名证书
*描述： 申请假名证书并写入芯片
*参数：
*       pbVIN                   [IN] OBU标识
*       nVINLen                    [IN] OBU标识长度
*       pUrl                    [IN] 在线申请地址
*返回值：0————成功；其他————错误号。
*说明：申请假名证书时会删除之前的所有假名证书
*/
__attribute__((visibility("default"))) int IWALL_ApplyPseudonymTicket(unsigned char *pbVIN, int nVINLen, const char *pUrl);

/*
*名称： 在线申请应用证书
*描述： 申请应用证书并写入芯片
*参数：
*       pbVIN                   [IN] RSU标识
*       nVINLen                    [IN] RSU标识长度
*       pUrl                    [IN] 在线申请地址
*返回值：0————成功；其他————错误号。
*说明：申请假名证书时会删除之前的所有假名证书
*/
__attribute__((visibility("default"))) int IWALL_ApplyApplicationTicket(unsigned char *pbVIN, int nVINLen, const char *pUrl);

/*
*名称： 根据指定keyID 在线申请应用证书
*描述： 申请应用证书并写入芯片
*参数：
*       keyID                   [IN] 指定密钥标识
*       pbVIN                   [IN] RSU标识
*       nVINLen                    [IN] RSU标识长度
*       pUrl                    [IN] 在线申请地址
*返回值：0————成功；其他————错误号。
*说明：
* 1. 申请假名证书时会删除之前的所有假名证书
* 2. 会生成AA.oer 文件 方便后续直接导入
*/
__attribute__((visibility("default"))) int IWALL_ApplyApplicationTicketWithKeyID(unsigned int keyID,unsigned char *pbVIN, int nVINLen, const char *pUrl);

/*
*名称： 导入假名证书及私钥
*描述： 将假名证书及对应的私钥写入安全芯片
*参数：
*       pbCert                   [IN] 证书编码
*       pCertLen                 [IN] 证书长度
*       pbPrivateKey             [IN] 假名证书私钥，32字节
*       nKeyId                    [IN] 密钥对标识：1~20
*       CA_Provider              [IN] CA供应商：大唐：0，国汽：1
*返回值：0————成功；其他————错误号。
*说明：如果有相同KeyId，会删除之前的证书及私钥；需提前导入PCA；
*/
__attribute__((visibility("default"))) int IWALL_ImportPseudonymTicket(unsigned char *pbCert, int nCertLen, unsigned char *pbPrivateKey, int nKeyId, int CA_Provider);

/*
*名称： 签名
*描述： 签名
*参数：
*       pbPlainData            [IN]       待签名原文
*       nPlainDataLen       [IN]       待签名原文长度
*       pbPrivateKey        [IN]       私钥，32字节
*       pbSignature         [OUT]      签名值，64字节：r + s
*返回值：0————成功；其他————错误号。
*说明：IDa默认为China
*/
__attribute__((visibility("default"))) int IWALL_SignData(unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbPrivateKey, unsigned char *pbSignature);

/*
*名称： 验签
*描述： 验签
*参数：
*       pbPlainData            [IN]        签名原文
*       nPlainDataLen       [IN]        签名原文长度
*       pbPublicKey         [IN]        未压缩公钥，64字节
*       pbSignature         [IN]        签名值，64字节：r + s
*返回值：0————成功；其他————错误号。
*说明：IDa默认为China，公钥为未压缩，64字节；
*/
__attribute__((visibility("default"))) int IWALL_VerifySign(unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbPublicKey, unsigned char *pbSignature);

/*
*名称： 消息签名
*描述： 将待签名数据签名组成安全消息
*参数：
*       AID                             [IN]       智能交通应用标识
*       pbPlainData                     [IN]       待签名原文
*       nPlainDataLen                [IN]       待签名原文长度
*       pbSecuredMessage             [OUT]      签名后的安全消息
*       nSecuredMessageLen           [IN/OUT]   签名后的安全消息长度
*返回值：0————成功；其他————错误号。
*说明：签名时自动选择之前导入的假名证书进行签名，每五分钟更换一张证书
*/
__attribute__((visibility("default"))) int IWALL_SignSecuredMessage(uint64_t AID, unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbSecuredMessage, int *nSecuredMessageLen);

/*
*名称： 消息签名[支持假名证书摘要]
*描述： 将待签名数据签名组成安全消息
*参数：
*       AID                             [IN]       智能交通应用标识
*       pbPlainData                     [IN]       待签名原文
*       nPlainDataLen                [IN]       待签名原文长度
*       pbSecuredMessage             [OUT]      签名后的安全消息
*       nSecuredMessageLen           [IN/OUT]   签名后的安全消息长度
*返回值：0————成功；其他————错误号。
*说明：签名时自动选择之前导入的假名证书进行签名，每五分钟更换一张证书
*    450ms 以内 除第一次使用 完整证书,其余时间使用 带摘要的证书信息。
*/

__attribute__((visibility("default"))) int IWALL_SignSecuredMessageWithCertificateDigest(uint64_t AID, unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbSecuredMessage, int *nSecuredMessageLen);

/*
*名称： RSU消息签名
*描述： 将待签名数据签名组成安全消息
*参数：
*       AID                             [IN]       智能交通应用标识
*       pbPlainData                     [IN]       待签名原文
*       nPlainDataLen                [IN]       待签名原文长度
*       pbSecuredMessage             [OUT]      签名后的安全消息
*       nSecuredMessageLen           [IN/OUT]   签名后的安全消息长度
*返回值：0————成功；其他————错误号。
*说明：
*  nPlainDataLen长度最大2048.
*/
__attribute__((visibility("default"))) int IWALL_SignSecuredMessage_RSU(uint64_t AID, unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbSecuredMessage, int *nSecuredMessageLen);


/*
*名称： 消息验签
*描述： 验证消息签名
*参数：
*       pbSecuredMsg        [IN]        安全消息
*       nSecuredMsgLen      [IN]        安全消息长度
*       pbBSMData           [OUT]       UPER编码的BSM消息
*       nBSMDataLen         [IN/OUT]    UPER编码的BSM消息长度
*       AID                 [OUT]       智能交通应用标识
*返回值：0————成功；其他————错误号。
*说明：如果验签不同CA供应商的安全消息，需导入不同CA供应商的PCA证书用作验证证书链
*/
__attribute__((visibility("default"))) int IWALL_VerifySecuredMessage(unsigned char *pbSecuredMsg, int nSecuredMsgLen, unsigned char *pbBSMData, int *nBSMDataLen, uint64_t *AID);

/*
*名称： 安全消息验签[支持带假名证书摘要]
*描述： 验证消息签名
*参数：
*       pbSecuredMsg        [IN]        安全消息
*       nSecuredMsgLen      [IN]        安全消息长度
*       pbBSMData           [OUT]       UPER编码的BSM消息
*       nBSMDataLen         [IN/OUT]    UPER编码的BSM消息长度
*       AID                 [OUT]       智能交通应用标识
*返回值：0————成功；其他————错误号。
*说明：如果验签不同CA供应商的安全消息，需导入不同CA供应商的PCA证书用作验证证书链
*     对带完整假名证书
*/
__attribute__((visibility("default"))) int IWALL_VerifySecuredMessageWithCertificateDigest(unsigned char *pbSecuredMsg, int nSecuredMsgLen, unsigned char *pbBSMData, int *nBSMDataLen, uint64_t *AID);

/*
*名称： 生成密钥对
*描述： 生成密钥对用来申请假名证书和注册证书
*参数：
*       nKeyId                       [IN]  密钥对标识
*        pbPublicVerifyKey            [OUT] 签名公钥
*        nPublicVerifyKeyLen            [IN/OUT] 签名公钥长度
*        pbPublicEncryptionKey        [OUT] 加密公钥
*        nPublicEncryptionKeyLen        [IN/OUT] 加密公钥长度
*返回值：0————成功；其他————错误号。
*说明：  公钥采用uncompressed,长度为64，前32字节为X，后32字节为Y；传入的KeyId对应两对密钥对，私钥存储在安全芯片中，密钥对用于注册证书和假名证书的生成，其中假名证书使用的KeyId为：1～20；
*/
__attribute__((visibility("default"))) int IWALL_GenKeyPair(int nKeyId, unsigned char *pbPublicVerifyKey, int *nPublicVerifyKeyLen, unsigned char *pbPublicEncryptionKey, int *nPublicEncryptionKeyLen);

/*
*名称： 申请注册证书（暂不支持）
*描述： 申请国汽注册证书写入安全芯片
*参数： 无
*返回值：0————成功；其他————错误号。
*说明：在线申请国汽的注册证书，需预置国汽的数字证书
*/
//int IWALL_ApplyEnrollmentCredential();

/*
*名称： 解析应用证书响应数据
*描述： 解码应用证书响应数据
*参数：
*       nKeyId                       [IN]  密钥对标识
*        pbPublicVerifyKey            [OUT] 签名公钥
*        nPublicVerifyKeyLen            [IN/OUT] 签名公钥长度
*        pbPublicEncryptionKey        [OUT] 加密公钥
*        nPublicEncryptionKeyLen        [IN/OUT] 加密公钥长度
*返回值：0————成功；其他————错误号。
*说明：  公钥采用uncompressed,长度为64，前32字节为X，后32字节为Y；传入的KeyId对应两对密钥对，私钥存储在安全芯片中，密钥对用于注册证书和假名证书的生成，其中假名证书使用的KeyId为：1～20；
*/
 __attribute__((visibility("default")))   int IWALL_Decode_ACA_RespMsg_To_Cert(unsigned char *pbEncMsg, int nEncMsgLen, unsigned char pbPCert[][512], int nPCertLen[], int *nPcertNum);

/*
*名称： 写入公私钥密钥对文件
*描述： 根据keyType 及keyID 写入不同的公私钥文件
*参数： 
*       keyID                        [IN] 私钥对应使用的keyID。  
*       keyType                      [IN] 0 为 签名私钥 , 1 为 解密私钥 。  
*       keyprivate                   [IN] 私钥首地址。
*       key_private_len              [IN] 私钥文件长度，必须为32字节。
*       keypubkey                    [IN] 私钥首地址。
*       key_pubkey_len               [IN] 私钥文件长度，必须为64字节。
*返回值：0————写入文件成功；其他————错误。
*说明：
*/
 __attribute__((visibility("default")))  int IWALL_WriteKeyPairWithKeyID(unsigned int keyID, unsigned int keyType, unsigned char *keyprivate, unsigned int key_private_len, unsigned char *keypubkey, unsigned int key_pubkey_len);

/*
*名称： 注册 假名证书变更 通知函数
*描述： 用于 通知 签名安全消息时，假名证书的变更
*参数： 
*       callback                       [IN] 回调通知函数。  
*返回值：0————成功；其他————错误。
*说明：
*/
 __attribute__((visibility("default")))  int IWALL_Register_PA_Change_Handle(int (*callback)());
#ifdef  __cplusplus
}
#endif

#endif
