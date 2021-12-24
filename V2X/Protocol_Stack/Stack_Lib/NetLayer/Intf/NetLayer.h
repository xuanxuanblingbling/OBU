/*
 * NetLayer.h
 *
 *  Created on: Apr 7, 2020
 *      Author: wanijv2x
 */

#ifndef NETLAYER_NETLAYER_H_
#define NETLAYER_NETLAYER_H_

#include "DataSet.h"

#define ADAPT_LAYER_IPV6 0
#define ADAPT_LAYER_DSMP 4
#define ADAPT_LAYER_IPV4 5

#define DSMP_VERSION 0

/**
 * @brief 填充适配层结构体；
 * @param[in] tDSMEncReq            待打包的网络层数据结构体
 * @param[out] ag15SendDataInfo     打包后的适配层结构体
 * @return 0--成功;非0--错误号。
 */
int32_t Adapter_Encode(TDSMEncReq tDSMEncReq, SendDataInfo *ag15SendDataInfo);
/**
 * @brief 解析反馈的结构体；
 * @param[in] ag15CallbackReturnInfo    底层推送过来的适配层结构体
 * @param[out] pDsmpHdr                 底层数据解析成的网络层结构体格式
 * @return 0--成功;非0--错误号。
 */
int32_t Adapter_Decode(RecvCallbackReturnInfo ag15CallbackReturnInfo, TDSMEncReq *pDsmpHdr);

#endif /* NETLAYER_NETLAYER_H_ */
