#ifndef __IWALL_V2X_API_H__
#define __IWALL_V2X_API_H__

#include <stdint.h>


// using namespace std;
// using std::string;
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
*       nCertLen		     [IN] 证书编码长度
*       pCertName                [IN] 证书名称
*       nCertType                [IN] 证书类型，ROOT：4， ECA：3， ACA：2， PCA：7
*       CA_Provider              [IN] CA供应商 信长城：0 ，1，大唐，2 国汽
*返回值：0————成功；其他————错误号。
*说明：预置根证书 时，CA_Provider 为 1，2 不验证证书链
*/
__attribute__((visibility("default"))) int IWALL_ImportRootCertificate(unsigned char *pbCert, int nCertLen, const char *pCertName, int nCertType, int CA_Provider);

__attribute__((visibility("default"))) int IWALL_RecodeAllcertsInfo(int nCertType, char *basePath);

__attribute__((visibility("default"))) int IWALL_RecodeCertInfo(unsigned char *pbCert, int nCertLen, const char *pCertName, int nCertType, int CA_Provider);

/*
*名称： 生成注册证书公钥文件
*描述： 生成公钥文件用来申请注册证书
*参数：
*		szFilePathName			    [IN]  公钥文件路径，例如：./EA.key
*返回值：0————成功；其他————错误号。
*说明： 一个OBU设备只有一张注册证书，因此申请新的公钥文件，会删除老的注册证书及对应私钥
* 新四跨不使用此接口
*/
//__attribute__((visibility("default"))) int IWALL_GenKeyPair_File(const char *szFilePathName);

/*
*名称： 导入注册证书
*描述： 将注册证书写入安全芯片
*参数： 
*       pbCert                   [IN] 证书编码
*       pCertLen				 [IN] 证书长度
*返回值：0————成功；其他————错误号。
*说明：无
*/
__attribute__((visibility("default"))) int IWALL_ImportEnrollmentCredential(unsigned char *pbCert, int nCertLen);

/*
*名称： 导入应用证书
*描述： 将注册证书写入安全芯片
*参数： 
*       pbCert                   [IN] 证书编码
*       pCertLen				 [IN] 证书长度
*返回值：0————成功；其他————错误号。
*说明：无
*/
__attribute__((visibility("default"))) int IWALL_ImportAplicationCertificate(unsigned char *pbCert, int nCertLen);
/*
*名称： 在线申请假名证书
*描述： 申请假名证书并写入芯片
*参数： 
*       pbVIN                   [IN] OBU标识
*       nVINLen				    [IN] OBU标识长度
*       request_url             [IN] 在线申请地址
*       download_time           [OUT] 申请下载时间
*       download_url            [OUT] 申请下载的地址
*       request_hash            [OUT] 对应请求的HASH 值 8个字节 
*返回值：0————成功；其他————错误号。
*说明：申请假名证书时会删除之前的所有假名证书
*  download_url  暂时为预留。
*/
__attribute__((visibility("default"))) int IWALL_ApplyPseudonymTicket(unsigned char *pbVIN, int nVINLen, const char *request_url, uint32_t *download_time, unsigned char *download_url, unsigned char *request_hash);

/*
*名称： 配合信通院一致性测试用例【5.1.16】证书申请请求信息测试
*描述： 输出证书申请请求信息
*参数： 
*       pbVIN                   [IN] OBU标识
*       nVINLen				    [IN] OBU标识长度
*       request                 [OUT] 请求的数据
*       request_len             [OUT] 请求的数据长度
*返回值：0————成功；其他————错误号。
*说明：
*/
__attribute__((visibility("default"))) int IWALL_ApplyPseudonymTicketTest(unsigned char *pbVIN, int nVINLen, unsigned char *request, int *request_len);

/*
*名称： 配合信通院一致性测试用例 DUT证书管理接口测试中解析TS 发送的CertAck
*描述： 解析CertAck 
*参数： 
*       pbCertAck               [IN] 响应缓冲池开始地址
*       nCertAckLen			    [IN] 响应的长度
*       download_time           [OUT] 下载时间
*       request_hash            [OUT] 请求下载的Hash值
*返回值：0————成功；其他————错误号。
*说明：
*/
__attribute__((visibility("default"))) int IWALL_ApplyPseudonymTicketTestParseCertAck(unsigned char *pbCertAck, int nCertAckLen,uint32_t *download_time, unsigned char *request_hash);

/*
*名称： 在线下载假名证书
*描述： 申请应用证书并写入芯片
*参数： 
*       pcert_download_time           [IN] 申请下载时间
*       pcert_download_url            [IN] 申请下载的地址
*       request_hash                  [IN] 对应请求的HASH 值 8个字节
*返回值：0————成功；其他————错误号。
*说明：
*/
__attribute__((visibility("default"))) int IWALL_DownloadPseudonymCetificate(uint32_t pcert_download_time, const char *pcert_download_url, unsigned char *request_hash);

/*
*名称： 配合信通院一致性测试用例【5.1.17】证书下载信息测试
*描述： 输出证书申请请求信息
*参数： 
*       pcert_download_tiem     [IN] 下载时间
*       request_hash     	    [IN] 请求的hash 值
*       request_data                 [OUT] 请求的数据
*       request_data_len             [OUT] 请求的数据长度
*返回值：0————成功；其他————错误号。
*说明：
*/

__attribute__((visibility("default"))) int IWALL_DownloadPseudonymCetificateTest(uint32_t pcert_download_time, unsigned char *request_hash, unsigned char *request_data, int *request_data_len);

/*
*名称： 在线申请应用证书
*描述： 申请应用证书并写入芯片
*参数： 
*       pbVIN                   [IN] RSU标识
*       nVINLen				    [IN] RSU标识长度
*       request_url             [IN] 在线申请地址
*       download_time           [OUT] 申请下载时间
*       download_url            [OUT] 申请下载的地址
*       request_hash            [OUT] 对应请求的HASH 值 8个字节 
*返回值：0————成功；其他————错误号。
*说明：
*/
__attribute__((visibility("default"))) int IWALL_ApplyApplicationTicket(unsigned char *pbVIN, int nVINLen, const char *request_url, uint32_t *download_time, unsigned char *download_url , unsigned char *request_hash);//std::string &download_url


/*
*名称： 在线下载应用证书
*描述： 申请应用证书并写入芯片
*参数： 
*       acert_download_time           [IN] 申请下载时间
*       acert_download_url            [IN] 申请下载的地址
*       request_hash                  [IN] 对应请求的HASH 值 8个字节
*返回值：0————成功；其他————错误号。
*说明：
*/
__attribute__((visibility("default"))) int IWALL_DownloadApplicationCetificate(uint32_t acert_download_time, const char *acert_download_url, unsigned char *request_hash);

/*
*名称： 在线下载PkiCtl
*描述： 申请下载PkiCtl
*参数： 
*       download_url                  [IN] 申请下载的地址
*       ctl                           [OUT] ctl 缓冲区首地址
*       ctl_len                       [OUT] ctl 长度
*       ctl_name                      [OUT] ctl 名字
*       clt_name_len                  [OUT] ctl 名字长度 
*返回值：0————成功；其他————错误号。
*说明：
*/
__attribute__((visibility("default"))) int IWALL_DownloadPkiCtl(const char *download_url, unsigned char *ctl,  int *ctl_len, unsigned char *ctl_name, int *ctl_name_len);


/*
*名称： 根据指定keyID 在线申请应用证书
*描述： 申请应用证书并写入芯片
*参数： 
*       keyID                   [IN] 指定密钥标识 
*       pbVIN                   [IN] RSU标识
*       nVINLen				    [IN] RSU标识长度
*       pUrl                    [IN] 在线申请地址
*返回值：0————成功；其他————错误号。
*说明：
* 1. 申请假名证书时会删除之前的所有假名证书
* 2. 会生成AA.oer 文件 方便后续直接导入 
* 新四跨不使用此接口
*/
//__attribute__((visibility("default"))) int IWALL_ApplyApplicationTicketWithKeyID(unsigned int keyID,unsigned char *pbVIN, int nVINLen, const char *pUrl);


/*
*名称： 注册证书申请 NEW
*描述： 申请应用证书并写入芯片
*参数： 
*       keyID                   [IN] 指定密钥标识 
*       pbVIN                   [IN] RSU标识
*       nVINLen				    [IN] RSU标识长度
*       pUrl                    [IN] 在线申请地址
*返回值：0————成功；其他————错误号。
*说明：
* 1. 申请假名证书时会删除之前的所有假名证书
* 2. 会生成AA.oer 文件 方便后续直接导入 
*/
__attribute__((visibility("default"))) int IWALL_ApplyEnrollmentCertificate(const char *request_url, unsigned char *vin, int vin_len, unsigned char *cert,int *cert_len);

/*
*名称： 导入假名证书及私钥
*描述： 将假名证书及对应的私钥写入安全芯片
*参数： 
*       pbCert                   [IN] 证书编码
*       pCertLen				 [IN] 证书长度
*       pbPrivateKey             [IN] 假名证书私钥，32字节
*       nKeyId           		 [IN] 密钥对标识：1~20
*       CA_Provider              [IN] CA供应商：大唐：0，国汽：1
*返回值：0————成功；其他————错误号。
*说明：如果有相同KeyId，会删除之前的证书及私钥；需提前导入PCA；
*/
__attribute__((visibility("default"))) int IWALL_ImportPseudonymTicket(unsigned char *pbCert, int nCertLen, unsigned char *pbPrivateKey, int nKeyId, int CA_Provider);

/*
*名称： 签名
*描述： 签名 
*参数： 
*       pbPlainData	        [IN]       待签名原文
*       nPlainDataLen       [IN]       待签名原文长度
*       pbPrivateKey        [IN]       私钥，32字节
*       pbSignature         [OUT]      签名值，64字节：r + s
*返回值：0————成功；其他————错误号。
*说明：IDa默认为China
*/
__attribute__((visibility("default"))) int IWALL_SignData(unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbPrivateKey, unsigned char *pbSignature);


/*
*名称： 签名
*描述： 签名 外部传入 IDA
*参数： 
*       nMobe               [IN]       nMode 模式选择 0：使用软件算法，1: 使用硬件签名算法
*       nZAFlag             [IN]       nZAFlag ZA计算标志 0：内部计算;1:使用传入的公钥计算ZA.
*       pbIDA               [IN]       IDA首地址
*       nIDALen             [IN]       IDA长度
*       pbPlainData	        [IN]       待签名原文
*       nPlainDataLen       [IN]       待签名原文长度
*       pbPrivateKey        [IN]       私钥，32字节
*       pbPublicKey         [IN]       公钥，64字节
*       pbSignature         [OUT]      签名值，64字节：r + s
*返回值：0————成功；其他————错误号。
*说明：
       暂时只支持软件算法。
*/
__attribute__((visibility("default"))) int IWALL_SignDataWithIDA(unsigned int nMode, unsigned int nZAFlag, unsigned char *pbIDA, int nIDALen, unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbPrivateKey, unsigned char *pbPublicKey,unsigned char *pbSignature);

/*
*名称： 验签
*描述： 验签 外部传入IDA
*参数：
*       nMobe               [IN]       nMode 模式选择 0：使用软件算法，1: 使用硬件签名算法
*       nZAFlag             [IN]       nZAFlag ZA计算标志 0：内部计算;1:其他情况.
*       pbIDA               [IN]       IDA首地址
*       nIDALen             [IN]       IDA长度
*       pbPlainData		[IN]        签名原文
*       nPlainDataLen       [IN]        签名原文长度
*       pbPublicKey         [IN]        未压缩公钥，64字节
*       pbSignature         [IN]        签名值，64字节：r + s
*返回值：0————成功；其他————错误号。
*说明：公钥为未压缩，64字节；
*/
__attribute__((visibility("default"))) int IWALL_VerifySignatureWithIDA(unsigned int nMode, unsigned int nZAFlag, unsigned char *pbIDA, int nIDALen, unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbPublicKey, unsigned char *pbSignature);

/*
*名称： 验签
*描述： 验签
*参数：
*       pbPlainData			[IN]        签名原文
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
*       AID			                 [IN]       智能交通应用标识
*       pbPlainData			         [IN]       待签名原文
*       nPlainDataLen                [IN]       待签名原文长度
*       pbSecuredMessage             [OUT]      签名后的安全消息
*       nSecuredMessageLen           [IN/OUT]   签名后的安全消息长度
*返回值：0————成功；其他————错误号。
*说明：签名时自动选择之前导入的假名证书进行签名，每五分钟更换一张证书
*/
__attribute__((visibility("default"))) int IWALL_SignSecuredMessage(uint64_t AID, unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbSecuredMessage, int *nSecuredMessageLen);


/*
*名称： 消息签名[指定KeyId]
*描述： 将待签名数据签名组成安全消息
*参数： 
*       nKeyId                       [IN]       指定KeyId
*       AID			                 [IN]       智能交通应用标识
*       pbPlainData			         [IN]       待签名原文
*       nPlainDataLen                [IN]       待签名原文长度
*       pbSecuredMessage             [OUT]      签名后的安全消息
*       nSecuredMessageLen           [IN/OUT]   签名后的安全消息长度
*返回值：0————成功；其他————错误号。
*说明：使用指定KeyId 进行签名， keyId 范围 1~20,内部使用完整证书
*      内部不自动切换证书
*      安全消息附带完整证书
*/
__attribute__((visibility("default"))) int IWALL_SignSecuredMessageWithKeyId(int nKeyId, uint64_t AID, unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbSecuredMessage, int *nSecuredMessageLen);

/*
*名称： 消息签名[支持假名证书摘要]
*描述： 将待签名数据签名组成安全消息
*参数： 
*       AID			                 [IN]       智能交通应用标识
*       pbPlainData			         [IN]       待签名原文
*       nPlainDataLen                [IN]       待签名原文长度
*       pbSecuredMessage             [OUT]      签名后的安全消息
*       nSecuredMessageLen           [IN/OUT]   签名后的安全消息长度
*返回值：0————成功；其他————错误号。
*说明：签名时自动选择之前导入的假名证书进行签名，每五分钟更换一张证书
*    450ms 以内 除第一次使用 完整证书,其余时间使用 带摘要的证书信息。
*/

__attribute__((visibility("default"))) int IWALL_SignSecuredMessageWithCertificateDigest(uint64_t AID, unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbSecuredMessage, int *nSecuredMessageLen);


/*
*名称： 消息签名[使用假名证书摘要][指定KeyId]
*描述： 将待签名数据签名组成安全消息
*参数： 
*       nKeyId                       [IN]       指定keyId
*       AID			                 [IN]       智能交通应用标识
*       pbPlainData			         [IN]       待签名原文
*       nPlainDataLen                [IN]       待签名原文长度
*       pbSecuredMessage             [OUT]      签名后的安全消息
*       nSecuredMessageLen           [IN/OUT]   签名后的安全消息长度
*返回值：0————成功；其他————错误号。
*说明：内部不自动切换
*    
*/
__attribute__((visibility("default"))) int IWALL_SignSecuredMessageWithCertificateDigestWithKeyId(int nKeyId,uint64_t AID, unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbSecuredMessage, int *nSecuredMessageLen);

/*
*名称： RSU消息签名
*描述： 将待签名数据签名组成安全消息
*参数： 
*       AID			                 [IN]       智能交通应用标识
*       pbPlainData			         [IN]       待签名原文
*       nPlainDataLen                [IN]       待签名原文长度
*       pbSecuredMessage             [OUT]      签名后的安全消息
*       nSecuredMessageLen           [IN/OUT]   签名后的安全消息长度
*返回值：0————成功；其他————错误号。
*说明：
*  nPlainDataLen长度最大2048.
*/
__attribute__((visibility("default"))) int IWALL_SignSecuredMessage_RSU(uint64_t AID, unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbSecuredMessage, int *nSecuredMessageLen);
/*
*名称： RSU消息签名[支持应用证书摘要]
*描述： 将待签名数据签名组成安全消息
*参数： 
*       AID			                 [IN]       智能交通应用标识
*       pbPlainData			         [IN]       待签名原文
*       nPlainDataLen                [IN]       待签名原文长度
*       pbSecuredMessage             [OUT]      签名后的安全消息
*       nSecuredMessageLen           [IN/OUT]   签名后的安全消息长度
*返回值：0————成功；其他————错误号。
*说明：
*  nPlainDataLen长度最大2048.
*  450ms 以内 除第一次使用 完整证书,其余时间使用 带摘要的证书信息。
*/
__attribute__((visibility("default"))) int IWALL_SignSecuredMessageWithCertificateDigest_RSU(uint64_t AID, unsigned char *pbPlainData, int nPlainDataLen, unsigned char *pbSecuredMessage, int *nSecuredMessageLen);

/*
*名称： 消息验签
*描述： 验证消息签名
*参数：
*       pbSecuredMsg		[IN]        安全消息
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
*       pbSecuredMsg		[IN]        安全消息
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
*名称： 批量安全消息验签[支持带假名证书摘要]
*描述： 验证消息签名
*参数：
*       pbSecuredMsg		[IN]        安全消息
*       nSecuredMsgLen      [IN]        安全消息长度
*       pbBSMData           [OUT]       UPER编码的BSM消息
*       nBSMDataLen         [IN/OUT]    UPER编码的BSM消息长度
*       AID                 [OUT]       智能交通应用标识
*返回值：0————成功；其他————错误号。
*说明：
*   如果验签不同CA供应商的安全消息，需导入不同CA供应商的PCA证书用作验证证书链对带完整假名证书
*   期望可以支持多线程处理
*/
__attribute__((visibility("default"))) int IWALL_MultiVerifySecuredMessageWithCertificateDigest(unsigned char *pbSecuredMsg, int nSecuredMsgLen, unsigned char *pbBSMData, int *nBSMDataLen, uint64_t *AID);

/*
*名称： 生成密钥对
*描述： 生成密钥对用来申请假名证书和注册证书
*参数：
*       nKeyId           			[IN]  密钥对标识
*		pbPublicVerifyKey			[OUT] 签名公钥
*		nPublicVerifyKeyLen			[IN/OUT] 签名公钥长度
*		pbPublicEncryptionKey		[OUT] 加密公钥
*		nPublicEncryptionKeyLen		[IN/OUT] 加密公钥长度
*返回值：0————成功；其他————错误号。
*说明：  公钥采用uncompressed,长度为64，前32字节为X，后32字节为Y；传入的KeyId对应两对密钥对，私钥存储在安全芯片中，密钥对用于注册证书和假名证书的生成，其中假名证书使用的KeyId为：1～20；
*/
__attribute__((visibility("default"))) int IWALL_GenKeyPair(int nKeyId, unsigned char *pbPublicVerifyKey, int *nPublicVerifyKeyLen, unsigned char *pbPublicEncryptionKey, int *nPublicEncryptionKeyLen);


/*
*名称： 解析应用证书响应数据 
*描述： 解码应用证书响应数据
*参数：
*       nKeyId           			[IN]  密钥对标识
*		pbPublicVerifyKey			[OUT] 签名公钥
*		nPublicVerifyKeyLen			[IN/OUT] 签名公钥长度
*		pbPublicEncryptionKey		[OUT] 加密公钥
*		nPublicEncryptionKeyLen		[IN/OUT] 加密公钥长度
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

/*
*名称： 获取上一次使用的假名PC证书标识  
*描述： 用于 获取上一次使用的PC 证书的标识 
*参数： 
*       keyID                      [OUT] 上次使用的假名证书标识ID。  
*返回值：0————成功；其他————错误。
*说明：
*  只有自动切换证书的签名接口，使用此接口才有效
*/
 __attribute__((visibility("default")))  int IWALL_GetPCKeyId(int *keyID);

/*
*名称： 获取假名证书有效期 
*描述： 获取假名证书有效期
*参数： 
*       nPeriod                      [OUT] 证书有效期(单位 ：秒）。  
*返回值：0————成功；其他————错误。
*说明：
* 时间从 2004年1月1日00:00:00 UTC以来的秒数  
*/
 __attribute__((visibility("default"))) int IWALL_GetPCValidityPeriod(unsigned int *nPeriod);

/*
功能：根据用户ID及公钥，求Z值
[输入] userid： 用户ID
[输入] userid_len： userid的字节数
[输入] xa： 公钥的X坐标
[输入] xa_len: xa的字节数
[输入] ya： 公钥的Y坐标
[输入] ya_len: ya的字节数
[输出] z：32字节

返回值：
－1：内存不足
0：成功
*/
 __attribute__((visibility("default"))) int IWALL_sm3_z( unsigned char *userid, int userid_len, unsigned char  *xa, int xa_len, unsigned char *ya, int ya_len, unsigned char *z);
/*
*名称： 根据私钥生成公钥 
*描述： 根据指定私钥生成公钥
*参数： 
*       callback                       [IN] 回调通知函数。  
*返回值：0————成功；其他————错误。
*说明：
*/
 __attribute__((visibility("default"))) int IWALL_sm2_cal_publickey(const unsigned char *privatekey, int len, unsigned char *publickey, int *publickey_len);

/*
*名称： 解压文件 
*描述： 解压指定文件
*参数： 
*      srcZipFile                      [IN] 压缩文件名
*       callback                       [IN] 解压地址  
*返回值：0————成功；其他————错误。
*说明：
*/
__attribute__((visibility("default"))) int IWALL_unzip(const char *srcZipFile, const char *outputPath);


/*
*名称： 删除文件夹中内容
*描述： 删除指定文件夹中内容 
*参数： 
*      path                             [IN] 文件路径
*返回值：0————成功；其他————错误。
*说明：最终会把目录文件也删除
*/
__attribute__((visibility("default"))) int IWALL_delete_file(const char *path);


/*
*名称： 获取周数
*描述： 获取当前的周数
*参数： 
*       
*返回值：周数。
*说明：
*/
__attribute__((visibility("default"))) uint32_t IWALL_GetWeekNum(void);

/*
*名称： 密钥衍生及导入对用证书
*描述： 从解压的文件中衍生密钥及导入对应证书
*参数： 
*       i                       [IN] i 值
*       j                       [IN] j 值
*       file_buffer             [IN] 输入文件缓冲区起始地址
*       file_len                [IN] 输入文件长度
*       keyID                   [IN] 指定keyID值
*返回值：0————成功；其他————错误。
*说明：
*/
__attribute__((visibility("default"))) int IWALL_ConstructKeypairAndImport(int i, int j, unsigned char *file_buffer, int file_len, int keyID);
/*
*名称： 密钥衍生及只生成证书文件及对应的私钥
*描述： 从解压的文件中衍生密钥及导入对应证书
*参数： 
*       store_path              [IN] 生成证书文件后对应的
*       i                       [IN] i 值
*       j                       [IN] j 值
*       file_buffer             [IN] 输入文件缓冲区起始地址
*       file_len                [IN] 输入文件长度
*       keyID                   [IN] 指定keyID值
*返回值：0————成功；其他————错误。
*说明：需要导入根证书 和 注册证书。
*/
__attribute__((visibility("default"))) int IWALL_ConstructKeypairAndGenCertFile(char *store_path, int i, int j ,unsigned char *file_buffer, int file_len, int keyID);

/*
*名称： 解析可信根证书列表中信息
*描述： 
*参数： 
*       file_buffer             [IN] 输入文件缓冲区起始地址
*       file_len                [IN] 输入文件长度
*       url_array               [OUT] 返回的可信CA证书列表信息地址
*       url_count               [OUT] 地址数量
*返回值：0————成功；其他————错误。
*说明：
*/

__attribute__((visibility("default"))) int IWALL_ParseRootCtlInfo(unsigned char *file_buffer, int file_len,  char url_array[][256], int *url_count);

/*
*名称： 解析可信CA证书列表中信息
*描述： 
*参数： 
*       file_buffer             [IN] 输入文件缓冲区起始地址
*       file_len                [IN] 输入文件长度
*       url_array               [OUT] 返回的证书地址
*       url_count               [OUT] 地址数量
*返回值：0————成功；其他————错误。
*说明：
*
*/

__attribute__((visibility("default"))) int IWALL_ParsePkiCtlInfo(unsigned char *file_buffer, int file_len,  char *url_array, int *url_count);

/*
*名称：生成应用证书按对应的文件指定格式 和生成 假名证书格式相同
*描述： 
*参数： 
*       file_num                [IN] 生成的文件名后缀
*       path                    [IN] 生成的应用证书文件相关信息路径 
*       pbCert                  [IN] 应用证书
*       nCertLen                [IN] 应用证书长度
*返回值：0————成功；其他————错误。
*说明：
* 需要放在 应用证书申请完以后。
*/
__attribute__((visibility("default"))) int IWALL_GenAplicationCertificate(int file_num, char *path, unsigned char *pbCert, int nCertLen);

/*
*名称：获取SDK 版本信息
*描述： 
*参数： 
*       str               [OUT] SDK 版本信息
*返回值：0————成功；其他————错误。
*说明：
*
*/
__attribute__((visibility("default"))) int IWALL_GetSDKVersionString(char *str);

/*
*名称：检查设备状态
*描述： 
*参数： 
*       status              [IN] 默认0
*返回值：0————正常；其他————错误。
*说明：
*
*/
__attribute__((visibility("default"))) int IWALL_CheckDevicestatus(int status);


/*
*名称：关闭设备
*描述： 
*参数： 
*      无
*返回值：0————正常；其他————错误。
*说明：
*
*/
__attribute__((visibility("default"))) int IWALL_CloseDevice(void);


#ifdef  __cplusplus
}
#endif

#endif
