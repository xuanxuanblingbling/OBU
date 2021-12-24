
#include "SecLayerIntfCom.h"
#include <stdio.h>

SECSIGNCALL_BACK pSignSecuredComplete = NULL;
SECVERICALL_BACK pVerifySecureComplete = NULL;
/**
 * @brief SetSecuredMessageCallback 设置消息签名、验签的回调函数
 *
 * @param[in] pSignfunc -- 签名回调函数
 * @param[in] pVerifyfunc -- 验签回调函数
 *
 */
void SetSecuredMessageCallback(SECSIGNCALL_BACK pSignfunc, SECVERICALL_BACK pVerifyfunc)
{
    pSignSecuredComplete = pSignfunc;
    pVerifySecureComplete = pVerifyfunc;
}