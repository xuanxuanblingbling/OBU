/**
 * @defgroup NetInterface NetInterface API
 * @ingroup WJ_Message_Com API
 * @{
 *
 * 本模块提供V2X网络层扩展域的数据结构API接口.
 *
 * @}
 *
 */
/**
 * @defgroup NetLayer NetLayer API
 * @ingroup NetInterface API
 * @{
 *
 * 本模块提供V2X网络层扩展域的数据结构API接口.
 *
 * @file ExtensionData.h
 * @brief API file.
 *
 */
#ifndef __EXTENSIONDATA_H_
#define __EXTENSIONDATA_H_
#include <stdint.h>
#define WJ_MAX_EXTENSIONINFO_LEN 32
#define WJ_MAX_EXTEN_NUM 10
/**
 * @brief DSM数据中拓展域数据结构.
 */
typedef struct ExtenSionCommn
{
    uint8_t ElementID;                               //扩展域信息标识
    uint8_t ByteLength;                              //扩展域信息长度
    uint8_t ExtensionInfo[WJ_MAX_EXTENSIONINFO_LEN]; //扩展域信息内容
} __attribute__((packed)) tExtenSionCommn;

typedef struct _ExtenSionCommn_st
{
    //有些模组可能需要上层协议栈提供源层2ID才能正常发送，是否修改ID由应用层控制（若模组不需要，可预留）
    uint8_t layerIDChanged;                           //适配层是否修改源层2ID标志位(0:不修改，1：修改；程序启动后适配层源层2ID会默认为初始随机值)
    uint8_t u8ExtenNum;                               //网络层扩展域信息个数，若不存在扩展域，则为0
    tExtenSionCommn extenSionCommn[WJ_MAX_EXTEN_NUM]; //网络层扩展域信息
} __attribute__((packed)) tExtenSionCommn_st;

/**
 * @brief 高层请求发送的DSM数据信息.
 */
typedef struct _TDSMEncReq
{
    uint16_t AID;                   //应用标识
    int32_t Priority;               //优先级
    int16_t Length;                 //DSM数据实体字节长度
    int8_t *Data;                   //DSM数据实体部分
    tExtenSionCommn_st *pExtension; //指定帧头扩展域
} __attribute__((packed)) TDSMEncReq;

/**
 * @brief 将待打包的网络层数据结构体按照网络层数据码流格式打包；如打包失败，则返回错误代码。
 * @param[in] tDSMEncReq  		待打包的网络层数据结构体
 * @param[out] pn8DstBuf  		打包后的网络层数据码流
 * @param[out] pn32DstBufSize   打包后的网络层数据码流长度
 * @return 0--成功;非0--错误号。
 *
 * Example Usage:
 * @code
 * {
 *      TDSMEncReq tDSMEncReq;
 *      int8_t n8DstBuf[1000] = {0};
 *      int32_t n32DstBufSize = 0;
 *      memset(&tDSMEncReq,0x00,sizeof(tDSMEncReq));
 *      tDSMEncReq.AID = 3617;
 *      tDSMEncReq.Length = 5;
 *      tDSMEncReq.pExtension = NULL;
 *      tDSMEncReq.Data = (int8_t *)calloc(1, tDSMEncReq.Length);
 *      memcpy(tDSMEncReq.Data, "\x01\x02\x03\x04\x05", tDSMEncReq.Length);
 *      NetLay_Encode(tDSMEncReq, n8DstBuf, &n32DstBufSize);
 *      free(tDSMEncReq.Data);
 * }
 * @endcode
 */
__attribute__((visibility("default"))) int32_t NetLay_Encode(TDSMEncReq tDSMEncReq, int8_t *pn8DstBuf, int32_t *pn32DstBufSize);

/**
 * @brief 将底层的的数据按照网络层头的格式解析；如解析失败，则返回错误代码。
 * @param[in] pn8SrcBuf  		底层推送过来的数据码流
 * @param[in] pn32SrcBufSize  	底层推送过来的数据码流长度
 * @param[out] pDsmpHdr   		底层数据解析成的网络层结构体格式
 * @return 0--成功;非0--错误号。
 *
 * Example Usage:
 * @code
 * {
 *      TDSMEncReq pDsmpHdr;
 *      int8_t n8DstBuf[1000] = {0x01,0x02,0x03,0x04,0x05};
 *      int32_t n32DstBufSize = 5;
 *      memset(&pDsmpHdr,0x00,sizeof(pDsmpHdr));
 *      NetLay_Decode(n8DstBuf, &n32DstBufSize, &pDsmpHdr);
 *      free(pDsmpHdr.Data);
 * }
 * @endcode
 */
__attribute__((visibility("default"))) int32_t NetLay_Decode(int8_t *pn8SrcBuf, int32_t *pn32SrcBufSize, TDSMEncReq *pDsmpHdr);

#endif