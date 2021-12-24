#ifndef DS_API_H
#define DS_API_H

typedef enum _ErrCode
{
    Err_ok =                                (0),  //正确.
    Err_incorrectSecureMessageVersion =     (1),  //安全消息版本号信息非法.  1.1
    Err_incorrectSignerType =               (2),  //签名者信息中签名方式非法.
    Err_incorrectCertVersion =              (3),  //数字证书版本号信息非法.. 1.3
    Err_incorrectCertIssueDigest =          (4),  //数字证书签发者信息非法. 1.5
    Err_incorrectCertSubjectInfo =          (5),  //数字证书中待签主题信息非法.
    Err_incorrectCertSubjectAttribute =     (6),  //数字证书中待签主题属性信息非法.
    Err_incorrectCertValidityPeriod =       (7),  //数字证书中有效限定信息非法. （根据CA时间）1.8
    Err_incorrectCertTimeStartAndEnd =      (8),  //数字证书中有效时间信息非法. (未生效) 1.14 1.15
    Err_incorrectSubcertAuthority =         (9),  //数字证书父子关系非法. 1.2
    Err_incorrectCertChain =                (10), //证书链非法.
    Err_incorrectCertSignature =            (11), //数字证书签名信息非法. 1.10
    Err_incorrectTbsDataGenTime =           (12), //待签数据中数据产生时间信息非法. 1.11
    Err_incorrectTbsDataHashAlg =           (13), //待签数据中杂凑算法信息非法. 1.11
    Err_incorrectTbsDataItsAid =            (14), //待签数据中AID信息非法. 1.11
    Err_incorrectSignedMessageSignature =   (15), //安全消息中签名信息非法. 1.13
    Err_incorrectCertType =                 (16), //证书类型错误(显性|隐性)  1.4
    Err_incorrectCertLinkvalue =            (17), //linkvalue 1.6
    Err_incorrectCertPubkey =               (18), //公钥信息错误 1.9
    Err_craCaId =                           (19), //CRA ID错误              1.7
    Err_signedMessageSignWay =              (20), //签名方式非法             1.12
    Err_incorrectCertHash =                 (21), //数字证书的hash算法非法
    Err_incorrectCertSignatureType =        (22), //数字证书的签名类型非法

    Err_initFailed =                        (50), //库初始化失败
    Err_noInitialized =                     (51), //库未初始化
    Err_incorrectParam =                    (52), //无效参数
    Err_certType =                          (53), //签发SecData时，参数中的证书类型错误
    Err_oerEncodeFailed =                   (54),  //OER编码失败
    Err_oerDecodeFailed =                   (55),  //OER解码失败
    Err_computeDigestFailed =               (56),  //计算摘要失败
    Err_invalidSignPc =                     (57),  //无有效的签名PC证书
    Err_signedFailed =                      (58),  //签名失败
    Err_repeatedMsg =                       (59),  //重复消息
    Err_pcHasBeenRevoked =                  (60),  //签名证书已被撤销
    Err_notFoundCorrespondPc =              (61),  //未发现小模式对应的PC证书【小模式】
    Err_notFoundSpecifyCert =               (62),  //签名时未找到对应j值的证书【签发时】
    Err_signedMessageExpired =              (63),  //安全消息过期
    Err_bufOverflow =                       (64),  //解出的数据长度大于缓存长度
}DS_ErrCode;

#ifdef __cplusplus
extern "C" {
#endif

/**
    * @brief 初始化安全服务
    *
    * @param[in]  vassRootPath         该离线版本指定为当前目录 "./"
    *
    * @return 错误码
    * @retval 0-成功 其他-错误
    */
int DS_InitSecurityService(
    const char *vassRootPath
);


/**
    * @brief 基于安全消息的数据签名
    *
    * @param[in]  certnum,           签发证书的序号(0-19)最多20张证书
    * @param[in]  signerType         签名者类型：0 证书hashId8，1 证书
    * @param[in]  itsAid             应用ID
    * @param[in]  plain              待签明文数据
    * @param[in]  plainLen           待签明文数据长度
    * @param[out] secureMessage      签名后安全消息数据
    * @param[out] secureMessageLen   签名后安全消息数据长度
    *
    * @return 错误码
    * @retval 0-成功 其他-错误
    */
int DS_Sign(
    int certType,
    int certnum,
    int signerType,
    long itsAid,
    unsigned char *plain,
    int plainLen,
    unsigned char *securedMessage,
    int *securedMessageLen
);

/**
    * @brief 验证数据签名
    *
    * @param[in]  itsAid            应用ID
    * @param[in] securedMessage      签名安全消息数据
    * @param[in] securedMessageLen   签名安全消息数据长度
    * @param[out] plain      明文数据
    * @param[out] plainLen   明文数据长度指针
    * @return 错误码
    * @retval 0-成功其他-错误
    */
int DS_VerifySigned(
    long itsAid,
    unsigned char *securedMessage,
    int securedMessageLen,
    unsigned char *plain,
    int *plainLen
);

/**
    * @brief 创建PC申请请求数据
    *
    * @param[in] withEncrypted          是否加密，0-不加密，1-加密
    * @param[out] request               申请请求数据
    * @param[in/out] requestLen         申请请求数据长度
    * @return 错误码
    * @retval 0-成功其他-错误
    */
int DS_CreatePcRequest(
    int withEncrypted,
    unsigned char* request,
    int* requestLen);

/**
    * @brief 创建PC下载请求数据
    *
    * @param[in] withEncrypted          是否加密，0-不加密，1-加密
    * @param[in] filename               待下载的文件名
    * @param[out] request                下载请求数据
    * @param[in/out] requestLen         下载请求数据长度
    * @return 错误码
    * @retval 0-成功其他-错误
    */
int DS_CreateDownloadRequest(
    int withEncrypted,
    const char* filename,
    unsigned char* request,
    int* requestLen);


/**
    * @brief 导入离线证书
    *
    * @param[in] caCertPath        CA证书路径，如（RCA，ICA，ECA，PCA等）
    * @param[in] ecPath            EC证书路径（包含1套：私钥，证书）
    * @param[in] pcPath            PC证书路径（包含多套：私钥，证书）
    * @return 错误码
    * @retval 0-成功其他-错误
    */
int DS_LoadOfflineCert(
    const char *caCertPath,
    const char *ecPath,
    const char *pcPath,
    const char *acPath);

#ifdef __cplusplus
}
#endif

#endif
