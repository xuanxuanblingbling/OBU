#ifndef __IWALL_V2X_ChIP_H__
#define __IWALL_V2X_CHIP_H__

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//



#define IWALL_DEBUG                      1
//ECC Curve 值
#define ECC_Curve_SM2                    0
#define ECC_Curve_NistP256               1
#define ECC_Curve_BrainpoolP256r1        2
//哈希算法 
#define HashAlg_SM3                 1
#define HashAlg_SHA256              4

//椭圆曲线 type 值
#define ECCPointType_x_only                   0
#define ECCPointType_y_0                      1
#define ECCPointType_y_1                      2
#define ECCPointType_uncompressed             4

//对称加密算法
#define SGD_SM4_ECB                 0x401
#define SGD_SM4_CBC                 0x402
#define SGD_SM4_CFB                 0x404
#define SGD_SM4_OFB                 0x408
#define AES_CCM                     0x2016

/*
*签名结构
*说明：
*curve取值如下：
*#define ECC_Curve_SM2                   0
*#define ECC_Cure_NistP256               1
*#define ECC_Cure_BrainpoolP256r1        2
*/
typedef struct st_signature_hw{
    unsigned int curve;
    unsigned char r[32];
    unsigned char s[32];
}Signature_hw;
/*
*椭圆曲线坐标格式
*说明：
*type 取值如下：
*#define ECCPointType_x_only                   0
*#define ECCPointType_y_0                      1
*#define ECCPointType_y_1                      2
*#define ECCPointType_uncompressed             4
*/
typedef struct st_eccPoint{
    unsigned int type;
    unsigned char x[32];
    unsigned char y[32];
}ECCPoint_hw;
/*
*公钥结构
*说明：
*curve取值如下：
*#define ECC_Curve_SM2                   0
*#define ECC_Cure_NistP256               1
*#define ECC_Cure_BrainpoolP256r1        2
*/
typedef struct st_publickey{
    unsigned int curve;
    ECCPoint_hw key;
}PublicKey_hw;

/*
*对称加密结构
*说明：
*param 为对称密码运算参数;
*当分组模式为ECB时,param 不使用;
*当分组模式为CBC/CFB/OFB时,param 存放iv;
*当分组模式为CCM时，param 存放nonce;
*当param 实际数据少于16字节时，后面补0;
*/
typedef struct st_cipherTxt{
    unsigned char param[16];
    int cipherLen;
    unsigned char cipher[1024];//GNU C support 0
}CipherText_hw;
/*
*非对称加密结构s
*说明：
*curve取值如下：
*#define ECC_Curve_SM2                   0
*#define ECC_Cure_NistP256               1
*#define ECC_Cure_BrainpoolP256r1        2
*/
typedef struct st_eciesEncryptedKey{
    unsigned int curve;
    ECCPoint_hw p;
    unsigned char c[16];
    unsigned char t[32];
}EciesEncryptedKey_hw;

#ifdef  __cplusplus
extern "C" {
#endif
/*
*名称： 消息签名接口定义[有证书]
*描述： 对消息进行数字签名
*参数： 
*       plain                   [IN] 待签名的数据缓冲区指针。
*       plainLen                [IN] 待签名数据长度。
*       keyId                   [IN] 签名密钥标识；当有多个签名密钥时，用来指定使用某个特
*                               定的签名密钥。
*       sign                    [OUT] 签名结果。
*返回值：0————成功；其他————错误号。
*说明：
*私钥签名的原文为：Hash(plain) || Hash(signCer);
*signCer 为指定的密钥对应的证书，获取证书的过程由函数内部处理。
*/ 
int ITS_SignData(unsigned char *plain,int plainLen,int keyId,Signature_hw* sign);



/*
*名称： 消息签名接口定义[使用IDA]
*描述： 对消息进行数字签名
*参数： 
*       plain                   [IN] 待签名的数据缓冲区指针。
*       plainLen                [IN] 待签名数据长度。
*       IDA                     [IN] 传入IDA
*       IDA_len                 [IN] IDA 长度
*       keyId                   [IN] 签名密钥标识；当有多个签名密钥时，用来指定使用某个特
*                               定的签名密钥。
*       sign                    [OUT] 签名结果。
*返回值：0————成功；其他————错误号。
*说明：
*
*/ 
int ITS_SignDataWithIDA(unsigned char *plain,int plainLen, unsigned char *IDA, int IDA_len, int keyId,unsigned char *sign, int *sign_len);
/*
*名称： 消息签名接口定义[无证书]
*描述： 对消息进行数字签名
*参数： 
*       plain                   [IN] 待签名的数据缓冲区指针。
*       plainLen                [IN] 待签名数据长度。
*       keyId                   [IN] 签名密钥标识；当有多个签名密钥时，用来指定使用某个特
*                               定的签名密钥。
*       sign                    [OUT] 签名结果。
*返回值：0————成功；其他————错误号。
*说明：
*此接口内部只是对传入的plain 进行签名。内部会计算e 值。
* 使用固定AID "China"
*/ 
int ITS_SignData_without_certificate(unsigned char *plain,unsigned int plainLen,int keyId,Signature_hw* sign);

/*
*名称： 签名验证接口定义[普通]
*描述： 验证数字签名
*参数： 
*       keyId                   [IN] 签名密钥标识；当有多个签名密钥时，用来指定使用某个特
*                               定的签名密钥。
*       plain                   [IN] 签名原文数据缓冲区指针。
*       plainLen                [IN] 签名原文数据长度,小于1024。
*       sign                    [IN] 签名值。
*返回值：0————验签成功；其他————验签失败。
*说明：  无
*/ 
int IWALL_sm2_verify(int keyID,unsigned char* plain,unsigned int plainLen,Signature_hw sign);

/*
*名称： 签名验证接口定义[使用外部公钥]
*描述： 验证数字签名，使用外部公钥
*参数： 
*       plain                   [IN] 签名原文数据缓冲区指针。
*       plainLen                [IN] 签名原文数据长度,小于1024。
*       sign                    [IN] 签名值。
*       pk                      [IN] 外部公钥。
*返回值：0————验签成功；其他————验签失败。
*说明：  无
*/ 
int IWALL_sm2_verify_with_external_pubkey(unsigned char* plain,unsigned int plainLen,Signature_hw sign,PublicKey_hw pk);

/*
*名称： 消息签名验证接口定义[带证书]
*描述： 验证消息数字签名
*参数： 
*       plain                   [IN] 签名原文数据缓冲区指针。
*       plainLen                [IN] 签名原文数据长度。
*       signer                  [IN] 签名者证书的编码字节数据缓冲区指针。 
*       signerLen               [IN] 签名者证书数据长度。
*       pk                      [IN] 签名证书中的验签公钥。
*       sign                    [IN] 签名值。
*返回值：0————验签成功；其他————验签失败。
*说明：  无
*/ 
int ITS_VerifySignedData(unsigned char *plain,int plainLen,unsigned char *signer,int signerLen,PublicKey_hw pk,Signature_hw sign);

/*
*名称： 消息签名验证接口定义[传e值]
*描述： 验证消息数字签名,使用e值
*参数： 
*       e                       [IN] 签名原文数据缓冲区指针。
*       eLen                    [IN] 签名原文数据长度,32字节。
*       pk                      [IN] 签名证书中的验签公钥。
*       sign                    [IN] 签名值。
*返回值：0————验签成功；其他————验签失败。
*说明：  无
*/ 
int IWALL_VerifySignedData_With_e(unsigned char *e,int eLen,PublicKey_hw pk,Signature_hw sign);

/*
*名称： 消息签名验证接口定义[传e值]
*描述： 验证消息数字签名,使用e值
*参数： 
*       e                       [IN] 签名原文数据缓冲区指针。
*       eLen                    [IN] 签名原文数据长度,32字节。
*       pk                      [IN] 签名证书中的验签公钥。
*       sign                    [IN] 签名值。
*返回值：0————验签成功；其他————验签失败。
*说明：  主要是减少传入参数的类型转换
*/ 
int IWALL_VerifySignedData_With_ee(unsigned char *e,int eLen, unsigned char *pk, unsigned char *sign);
/*
*名称： 消息非对称加密
*描述： 对消息进行数据加密
*参数： 
*       plain                   [IN] 要加密的原文。
*       plainLen                [IN] 原文长度。
*       symAlg                  [IN] 对称加密算法,定义如下：
*               #define SGD_SM4_ECB                 0x401 [支持]
*               #define SGD_SM4_CBC                 0x402
*               #define SGD_SM4_CFB                 0x404
*               #define SGD_SM4_OFB                 0x408
*               #define AES_CCM                     0x2016
*       pk                      [IN]来自于证书或者签名消息中的加密公钥。                
*       kek                     [OUT]对随机产生的对称密钥使用加密公钥加密的结果。
*       cipherText              [OUT]对称加密结果。
*返回值：0————加密成功；其他————错误。
*说明：mode = 0x57
*首先随机产生一个符合对称加密算法的对称密钥，使用对称密钥对原文加密，
*依次用公钥加密对称密钥，产生对应的kek。
*/ 
int ITS_AsymEncrypt(unsigned char *plain,int plainLen,int symAlg,PublicKey_hw pk,EciesEncryptedKey_hw* kek,CipherText_hw *cipherText);

/*
*名称： 消息非对称解密
*描述： 对消息进行数据解密
*参数： 
*       cipherText              [IN] 原始消息的对称加密密文。
*       symAlg                  [IN] 对称加密算法,定义如下：
*               #define SGD_SM4_ECB                 0x401[支持]
*               #define SGD_SM4_CBC                 0x402
*               #define SGD_SM4_CFB                 0x404
*               #define SGD_SM4_OFB                 0x408
*               #define AES_CCM                     0x2016
*       kek                     [IN]对随机产生的对称密钥使用加密公钥加密的结果。
*       plain                   [OUT]解密出的原始消息缓冲区指针。                   
*       plainLen                [OUT]原始消息长度。
*返回值：0————解密成功；其他————错误。
*说明：
*通过本方的非对称私钥解密kek的内容，得到对称密钥，再依指定的对称算法对
*cipherText中的消息密文解密，得到消息原文。
*/ 
int ITS_AsymDecrypt(CipherText_hw cipherText,int symAlg,EciesEncryptedKey_hw kek,unsigned char *plain,int *plainLen);



/*
*名称： 消息对称加密
*描述： 对消息进行数据加密
*参数： 
*       plain                   [IN] 要加密的原文。
*       plainLen                [IN] 原文长度。
*       symAlg                  [IN] 对称加密算法,定义如下：
*               #define SGD_SM4_ECB                 0x401
*               #define SGD_SM4_CBC                 0x402
*               #define SGD_SM4_CFB                 0x404
*               #define SGD_SM4_OFB                 0x408
*               #define AES_CCM                     0x2016
*       symmKey                 [IN]用于加密消息原文的对称密钥，明文。                   
*       symmKeyLen              [IN]明文对称密钥的长度。
*       encryptedSymmKey        [OUT]被内部对称密钥加密的symmKey的密文。
*       cipherText              [OUT]消息密文
*返回值：0————加密成功；其他————错误。
*说明：
*如果加密成功，通过输出参数返回密文
*/ 
int ITS_SymEncrypt(unsigned char *plain,int plainLen,int symAlg,unsigned char *symmKey,int symmKeyLen,CipherText_hw *encryptedSymmKey,CipherText_hw *cipherText);
/*
*名称： 消息对称解密
*描述： 对消息进行数据解密
*参数： 
*       cipherText              [IN] 消息密文。
*       symAlg                  [IN] 对称加密算法,定义如下：
*               #define SGD_SM4_ECB                 0x401
*               #define SGD_SM4_CBC                 0x402
*               #define SGD_SM4_CFB                 0x404
*               #define SGD_SM4_OFB                 0x408
*               #define AES_CCM                     0x2016
*       encryptedSymmKey        [IN]加密消息的对称密钥的密文，可被内部特定对称密钥解密。
*       plain                   [OUT]原文。                   
*       plainLen                [OUT]原文长度。
*返回值：0————解密成功；其他————错误。
*说明：
*如果解密成功，通过参数返回原文
*/ 
int ITS_SymDecrypt(CipherText_hw cipherText,int symAlg,CipherText_hw encryptedSymmkey,unsigned char *plain,int *plainLen);

/*
*名称： 摘要计算
*描述： 对消息进行摘要
*参数： 
*       plain                   [IN] 要计算摘要的内容的数据缓冲区指针。
*       plainLen                [IN] 内容长度。
*       hashAlg                 [IN] 摘要算法,定义如下：
*               #define HashAlg_SM3                 1
*               #define HashAlg_SHA256              4
*       hash                    [OUT]摘要数据，32字节长。                   
*返回值：0————加密成功；其他————错误。
*说明：
*用于计算证书,外部签名数据等内容的摘要。
*/ 
int ITS_digest(unsigned char *plain,int plainLen,int hashAlg,unsigned char *hash);
/*
*名称： 计算公钥 Y 值
*描述： 根据传入的压缩公钥X值,得出Y值.
*参数： 
*       pk_x                    [IN]公钥X。
*       pk_x_len                [IN] 公钥X长度 32字节。
*       ECCPointType            [IN] 压缩公钥类型 。
*       pk_y                    [OUT] 公钥Y 首地址。
*       pk_y_len                [OUT] 公钥Y 长度 32 字节 。
*返回值：0————成功；其他————错误。
*说明：
*用于计算压缩公钥Y值
*/ 
int IWALL_cal_y_base_x(unsigned char *pk_x,int pk_x_len,unsigned char *pk_y,int *pk_y_len,unsigned char ECCPointType);
/*
*名称： 摘要计算[软件实现]
*描述： 对消息进行摘要
*参数： 
*       plain                   [IN] 要计算摘要的内容的数据缓冲区指针。
*       plainLen                [IN] 内容长度。
*       hashAlg                 [IN] 摘要算法,定义如下：
*               #define HashAlg_SM3                 1
*             
*       hash                    [OUT]摘要数据，32字节长。                   
*返回值：0————加密成功；其他————错误。
*说明：
*用于计算证书,外部签名数据等内容的摘要。
*/ 
int ITS_digest_soft(unsigned char *plain,int plainLen,int hashAlg,unsigned char *hash);

/*
*名称： 设备初始化认证
*描述： 设备初始化
*参数： 
*       fd                      [IN] SPI 设备句柄。
*       AuthPassword            [IN] 认证密码。              
*返回值：0————初始化成功；其他————错误。
*说明：
*首次启动，必须调用
*/ 
int IWALL_deviceAuth_init(int fd,char *AuthPassword);

/*
*名称： 设备初始化
*描述： 设备初始化
*参数： 
*       speed              [IN] SPI 速率,默认1M(10000000)。
*       devname            [IN] 设备名称,默认"/dev/spidev1.0"。              
*返回值：0————初始化成功；其他————错误。
*说明：
*首次启动，必须调用
*/ 
int IWALL_device_init(unsigned int speed,unsigned char *devname);

/*
*名称： 设备状态init
*描述： 获取设备状态
*参数： 
*       status                     [IN] 状态标识 默认 0。          
*返回值：0————设备运行正常成功；其他————错误。
*说明：
*/ 
int IWALL_device_status(int status);
/*
*名称： 写证书文件
*描述： 写证书文件，主要是根证书,EA AA  初始化阶段的安全环境的证书
*参数： 
*       filename                    [IN] 证书的哈希值HashedId8 默认 8字节。 
*       file_name_len               [IN] 文件名字长度
*       input                       [IN] 证书文件首地址
*       input_len                   [IN] 证书文件长度        
*返回值：0————写入文件成功；其他————错误。
*说明：
*/ 
int IWALL_write_certificate(unsigned char *filename,unsigned int file_name_len,unsigned char *input,unsigned int input_len);
/*
*名称： 读取文件
*描述： 根据文件名读取文件
*参数： 
*       filename                     [IN] 文件名即证书的哈希值HashedId8 默认 8 字节。    
*       output                       [OUT] 输出文件首地址
*       output_len                   [OUT] 输出文件长度    
*返回值：0————设备运行正常成功；其他————错误。
*说明：
*/ 
int IWALL_read_certificate(unsigned char *filename,unsigned char *output,unsigned int *output_len);
/*
*名称： 生成密钥对
*描述： 生成签名密钥对，生成加密密钥对
*参数： 
*       keyId                        [IN] 两对密钥对对应的keyId。    
*       publicVerifyKey              [OUT] 签名公钥首地址
*       publicVerifykey_len          [OUT] 签名公钥长度,第一个字节固定为0x04,代表非压缩编码
*       publicEncryptionKey          [OUT] 加密公钥首地址    
*       publicEncryptinonKey_len     [OUT] 加密公钥长度,第一个字节固定为0x04,代表非压缩编码
*返回值：0————生成密钥对成功；其他————错误。
*说明：
*/ 
int IWALL_sm2_gen_keypair(int keyId,unsigned char *PublicVerifyKey,unsigned int *publicVerfiyKey_len,unsigned char *PublicEncryptionKey,unsigned int *publicEncryptionKey_len);

/*
*名称： 写证书文件
*描述： 写证书文件,主要是EA签发的公钥证书 或者 AA 签发的公钥证书
*参数： 
*       keyID                       [IN] 注册请求或 授权请求时 使用的keyID
*       filename                    [IN] 证书的哈希值HashedId8 默认 8字节。 
*       file_name_len               [IN] 文件名字长度
*       input                       [IN] 证书文件首地址
*       input_len                   [IN] 证书文件长度        
*返回值：0————写入文件成功；其他————错误。
*说明：
*/ 
int IWALL_write_certificate_with_keyID(int keyID,unsigned char *filename,unsigned int file_name_len,unsigned char *input,unsigned int input_len);

/*
*名称： 删除证书文件
*描述： 根据keyID,删除证书文件,主要是EA签发的公钥证书 或者 AA 签发的公钥证书
*参数： 
*       keyID                       [IN] 注册请求或 授权请求时 使用的keyID   
*返回值：0————写入文件成功；其他————错误。
*说明：
*/ 
int IWALL_del_certificate_with_keyID(int keyID);
/*
*名称： 删除证书文件
*描述： 根据file,删除证书文件,主要是EA签发的公钥证书 或者 AA 签发的公钥证书
*参数： 
*      filename                     [IN] 文件名即证书的哈希值HashedId8 默认 8 字节。    
*返回值：0————写入文件成功；其他————错误。
*说明：
*/ 
int IWALL_del_certificate_with_filename(unsigned char *filename);
/*
*名称： 删除所有证书文件
*描述： 删除所有根证书及其他证书,恢复到初始状态
*参数： 
*返回值：0————写入文件成功；其他————错误。
*说明：
*/ 
int IWALL_del_all_certificate(void);

/*
*名称： 读取文件
*描述： 根据keyID读取文件
*参数： 
*       keyID                        [IN] 注册请求或授权请求时，使用的keyID。
*       filename                     [IN] 文件名即证书的哈希值HashedId8 默认 8 字节。    
*       output                       [OUT] 输出文件首地址。
*       output_len                   [OUT] 输出文件长度。
*返回值：0————读取文件成功；其他————错误。
*说明：
*/
int IWALL_read_certificate_with_keyID(int keyID,unsigned char *filename,unsigned char *output,unsigned int *output_len);

/*
*名称： 关闭spi设备
*描述： 关闭spi设备
*参数： 无
*返回值：0————成功关闭；其他————错误。
*说明：
*/
int IWALL_se_close(void);

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
int IWALL_write_keypair_with_keyID(unsigned int keyID, unsigned int keyType, unsigned char *keyprivate, unsigned int key_private_len, unsigned char *keypubkey, unsigned int key_pubkey_len);

/*
*名称： 读取签名私钥文件
*描述： 根据keyID读取签名的私钥文件
*参数： 
*       keyID                        [IN] 注册请求或授权请求时，使用的keyID。  
*       filename                     [IN] 文件名即证书的哈希值HashedId8 默认 8 字节。  
*       output                       [OUT] 输出文件首地址。
*       output_len                   [OUT] 输出文件长度。
*返回值：0————读取文件成功；其他————错误。
*说明：
*/
int IWALL_read_privatekey_with_keyID(int keyID, unsigned char *filename, unsigned char *output, unsigned int *output_len);

#ifdef  __cplusplus
}
#endif

#endif
