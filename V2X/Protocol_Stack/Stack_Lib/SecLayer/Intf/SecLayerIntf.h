
#ifndef _SECLAYERINTF_H_
#define _SECLAYERINTF_H_
#include "SecDataInfo.h"

/**
 * @brief SetSecuredMessageCallback 设置消息签名、验签的回调函数
 *
 * @param[in] pSignfunc -- 签名回调函数
 * @param[in] pVerifyfunc -- 验签回调函数
 * 
 */
void SetSecuredMessageCallback(SECSIGNCALL_BACK pSignfunc, SECVERICALL_BACK pVerifyfunc);

#endif