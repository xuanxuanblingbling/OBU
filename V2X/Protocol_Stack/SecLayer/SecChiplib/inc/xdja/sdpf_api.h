#ifndef SDPF_API_H
#define SDPF_API_H

typedef enum _ErrCode
{
    Err_ok = (0),                               //正确.
    Err_incorrectSecureMessageVersion = (1),    //安全消息版本号信息非法.
    Err_incorrectSignerType = (2),              //签名者信息中签名方式非法.
    Err_incorrectCertVersion = (3),             //数字证书版本号信息非法.
    Err_incorrectCertIssueDigest = (4),         //数字证书签发者信息非法.
    Err_incorrectCertSubjectInfo = (5),         //数字证书中待签主题信息非法.
    Err_incorrectCertSubjectAttribute = (6),    //数字证书中待签主题属性信息非法.
    Err_incorrectCertValidityPeriod = (7),      //数字证书中有效限定信息非法. （根据CA时间）
    Err_incorrectCertTimeStartAndEnd = (8),     //数字证书中有效时间信息非法.
    Err_incorrectSubcertAuthority = (9),        //数字证书父子关系非法.
    Err_incorrectCertChain = (10),              //证书链非法.
    Err_incorrectCertSignature = (11),          //数字证书签名信息非法.
    Err_incorrectTbsDataGenTime = (12),         //待签数据中数据产生时间信息非法.
    Err_incorrectTbsDataHashAlg = (13),         //待签数据中杂凑算法信息非法.
    Err_incorrectTbsDataItsAid = (14),          //待签数据中AID信息非法.
    Err_incorrectSignedMessageSignature = (15), //安全消息中签名信息非法.
    Err_incorrectCertType = (16),               //证书类型错误(显性|隐性)
    Err_incorrectCertLinkvalue = (17),          //linkvalue
    Err_incorrectCertPubkey = (18),             //公钥信息错误
    Err_craCaId = (19),                         //CRA ID错误
    Err_signedMessageSignWay = (20),            //签名方式非法
    Err_incorrectCertHash = (21),               //数字证书的hash算法非法
    Err_incorrectCertSignatureType = (22),      //数字证书的签名类型非法

    Err_initFailed = (50),           //库初始化失败
    Err_noInitialized = (51),        //库未初始化
    Err_incorrectParam = (52),       //无效参数
    Err_certType = (53),             //签发SecData时，参数中的证书类型错误
    Err_oerEncodeFailed = (54),      //OER编码失败
    Err_oerDecodeFailed = (55),      //OER解码失败
    Err_computeDigestFailed = (56),  //计算摘要失败
    Err_invalidSignPc = (57),        //无有效的签名PC证书
    Err_signedFailed = (58),         //签名失败
    Err_repeatedMsg = (59),          //重复消息
    Err_pcHasBeenRevoked = (60),     //签名证书已被撤销
    Err_notFoundCorrespondPc = (61), //未发现小模式对应的PC证书【小模式】
    Err_notFoundSpecifyCert = (62),  //签名时未找到对应j值的证书【签发时】
    Err_signedMessageExpired = (63), //安全消息过期
    Err_bufOverflow = (64),          //解出的数据长度大于缓存长度
} SDPF_ErrCode;

#define OPEN_API __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    * @brief      初始化
    * @param[in]  scmfDataRootPath SCMF数据根目录（同I-APP-SCMF-03，SCMF初始化时填入的路径，因为SDPF依赖SCMF中的TDCL）
    * @return     错误码
    * @retval     0为正确，其他为错误
    */
    int ITS_SDPF_Init(const char *scmfDataRootPath);

    /***
    * @brief 回收资源
    *
    * @return 错误码
    * @retval 0为正确，其他为错误
    */
    int ITS_SDPF_Destroy();

    /**
    * @brief 查看版本信息
    * @param[out]       version         版本信息
    * @param[in/out]    versionLen      版本信息长度
    * @return 错误码
    * @retval 0为正确，其他为错误
    */

    int ITS_SDPF_Version(char *version, int *versionLen);

    /**
    * @brief 设置芯片GPIO参数,在初始化前调用
    *
    * @param[in]  Int0  3276 INT1引脚，3275 INT4引脚
    * @param[in]  Int1  3276 INT4引脚，3275 INT5引脚
    * @param[in]  Por   POR复位引脚【可选，不使用保持-1】
    * @param[in]  Power GPIO供电引脚【可选，不使用保持-1】
    * @param[in]  Qwk   低功耗唤醒引脚【可选，不使用保持-1】
    * @param[in]  Speed SPI频率配置,默认20/MHz
    *
    * @return 错误码
    * @retval 0-成功 其他-错误
    */
    int ITS_SDPF_SetSafeChipGpio(int Int0, int Int1, int Por, int Power, int Qwk, int Speed);

    /**
    * @brief设置日志文件存储位置和大小,在初始化前调用, 若不设置，默认在/tmp路径下，大小10MB.
	* 
    *日志路径下包含scmf、ssf、xdjakey三个日志文件,容量至少4MB，3个类型日志容量分别为2M、1M、1M
    *
    *
    * @param[in]    logFilePath    日志文件存储路径
    * @param[in]    capacity_mb    日志文件大小，单位：MB
    *
    */
    void ITS_SDPF_SetLogConf(const char *logFilePath, int capacity_mb);

    /**
    * @brief 基于安全消息的数据签名
    * @param[in]  certType           输入证书类型:1 假名证书PC，2 应用证书AC, OBU使用PC签名，RSU使用AC签名
    * @param[in]  keyId              当OBU使用假名证书PC时，取值范围（0~19）；当RSU使用应用证书AC时，取值固定为0
    * @param[in]  mode               模式：0 小模式,1 大模式
    * @param[in]  aid                应用ID
    * @param[in]  pdu               待签明文数据
    * @param[in]  pduLen            待签明文数据长度
    * @param[out] spdu              签名后安全消息数据
    * @param[in/out] spduLen        签名后安全消息数据长度
    *
    * @return 错误码
    * @retval 0-成功 其他-错误
    */
    int ITS_SDPF_GenSignedSPDU(
        int certType,
        int keyId,
        int mode,
        long aid,
        unsigned char *pdu,
        int pduLen,
        unsigned char *spdu,
        int *spduLen);

    /**
    * @brief 验证数据签名
    *
    * @param[in] aid            应用ID
    * @param[in] spdu           签名安全消息数据
    * @param[in] spduLen        签名安全消息数据长度
    * @param[out] pdu           明文数据
    * @param[in/out] pduLen     明文数据长度指针
    * @return 错误码
    * @retval 0-成功其他-错误
    */
    int ITS_SDPF_VerifySignedSPDU(
        long aid,
        unsigned char *spdu,
        int spduLen,
        unsigned char *pdu,
        int *pduLen);

#ifdef __cplusplus
}
#endif

#endif
