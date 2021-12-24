#ifndef SDPF_API_H
#define SDPF_API_H
/*
typedef enum _ErrCode
{
    Err_ok =                                 (0),       //正确.
    Err_incorrectSecureMessageVersion =      (1),       //安全消息版本号信息非法.
    Err_incorrectSignerType =                (2),       //签名者信息中签名方式非法.
    Err_incorrectCertVersion =               (3),       //数字证书版本号信息非法..
    Err_incorrectCertIssueDigest =           (4),       //数字证书签发者信息非法.
    Err_incorrectCertSubjectInfo =           (5),       //数字证书中待签主题信息非法.
    Err_incorrectCertSubjectAttribute =      (6),       //数字证书中待签主题属性信息非法.
    Err_incorrectCertValidityPeriod =        (7),       //数字证书中有效限定信息非法.
    Err_incorrectCertTimeStartAndEnd =       (8),       //数字证书中有效时间信息非法.
    Err_incorrectSubcertAuthority =          (9),       //数字证书父子关系非法.
    Err_incorrectCertChain =                 (10),      //证书链非法.
    Err_incorrectCertSignature =             (11),      //数字证书签名信息非法.
    Err_incorrectTbsDataGenTime =            (12),      //待签数据中数据产生时间信息非法.
    Err_incorrectTbsDataHashAlg =            (13),      //待签数据中杂凑算法信息非法.
    Err_incorrectTbsDataItsAid =             (14),      //待签数据中AID信息非法.
    Err_incorrectSignedMessageSignature =    (15),      //安全消息中签名信息非法.
    Err_incorrectCertType,                              //证书类型错误(显性|隐性)
    Err_incorrectCertLinkvalue,                         //linkvalue
    Err_incorrectCertPubkey,                            //公钥信息错误
    Err_craCaId,                                        //CRA ID错误
    Err_signedMessageSignWay,                           //签名方式非法
    Err_incorrectCertHash,                              //数字证书的hash算法非法
    Err_incorrectCertSignatureType,                     //数字证书的签名类型非法

    Err_initFailed,                                     //库初始化失败
    Err_noInitialized,                                  //库未初始化
    Err_incorrectParam,                                 //无效参数
    Err_CertType,                                       //签发SecData时，参数中的证书类型错误
    Err_oerEncodeFailed,                //OER编码失败
    Err_oerDecodeFailed,                //OER解码失败
    Err_computeDigestFailed,            //计算摘要失败
    Err_invalidSignPc,                  //无有效的签名PC证书
    Err_signedFailed,                   //签名失败
    Err_RepeatedMsg,                    //重复消息
    Err_pcHasBeenRevoked,               //签名证书已被撤销
    Err_notFoundCorrespondPc,           //未发现小模式对应的PC证书【小模式】
    Err_notFoundSpecifyCert,            //签名时未找到对应j值的证书【签发时】
    Err_signedMessageExpired,           //安全消息过期
    Err_bufOverflow,                    //解出的数据长度大于缓存长度

}SDPF_ErrCode;
*/
#define OPEN_API __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif

/**
    * @brief 初始化
    *
    * @return 错误码
    * @retval 0-成功 其他-错误
    */
OPEN_API int ITS_SDPF_Init();

/***
    * @brief 注销服务
    *
    * @return 错误码
    * @retval 0为正确，其他为错误
    */
OPEN_API int ITS_SDPF_Destroy();

/**
    * @brief 获取版本号
    *
    * @param[out] version             版本信息
    * @param[in/out] versionLen      版本信息长度
    * @return 错误码
    * @retval 0为正确，其他为错误
    */
OPEN_API int ITS_SDPF_Version(char* version, int* versionLen);


/**
    * @brief 基于安全消息的数据签名
    * @param[in]  certType           输入证书类型:1 PC
    * @param[in]  keyId              证书索引，目前取值范围：PC为0~19
    * @param[in]  mode               模式：0 小模式,1 大模式
    * @param[in]  aid                应用ID
    * @param[in]  pdu              待签明文数据
    * @param[in]  pduLen           待签明文数据长度
    * @param[out] spdu      签名后安全消息数据
    * @param[out] spduLen   签名后安全消息数据长度
    *
    * @return 错误码
    * @retval 0-成功 其他-错误
    */
OPEN_API int ITS_SDPF_GenSignedSPDU(
    int certType,
    int keyId,
    int mode,
    long aid,
    unsigned char *pdu,
    int pduLen,
    unsigned char *spdu,
    int *spduLen
);

/**
    * @brief 验证数据签名
    *
    * @param[in] aid            应用ID
    * @param[in] spdu      签名安全消息数据
    * @param[in] spduLen   签名安全消息数据长度
    * @param[out] pdu      明文数据
    * @param[out] pduLen   明文数据长度
    * @return 错误码
    * @retval 0-成功其他-错误
    */
OPEN_API int ITS_SDPF_VerifySignedSPDU(
    long aid,
    unsigned char *spdu,
    int spduLen,
    unsigned char *pdu,
    int *pduLen
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
OPEN_API int ITS_SDPF_CreatePcRequest(int withEncrypted, unsigned char* request, int* requestLen);

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
OPEN_API int ITS_SDPF_CreateDownloadRequest(int withEncrypted, const char* filename, unsigned char* request, int* requestLen);

#ifdef __cplusplus
}
#endif

#endif
