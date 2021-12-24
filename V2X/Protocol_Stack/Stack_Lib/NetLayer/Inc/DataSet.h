/*
 * DataSet.h
 *
 *  Created on: Jun 7, 2018
 *      Author: root
 */

#ifndef __NETLAYER_DATASET_H_
#define __NETLAYER_DATASET_H_

#include <semaphore.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Port.h"
#include "PublicMsg.h"
#include "ExtensionData.h"
#include "SendDataInfo.h"
#define NETLAYER_PRINTLOG 0

/*协议一致性测试使用*/
typedef struct _TDSMEncReqTci
{
    uint8_t ProtocalType; //协议类型
    uint16_t AID;         //应用标识
    int m_nSendSwitch;    //发送开关
    int m_nSendFrequency; //发送频率
    int8_t outStringData[RECVINFORel_MAXSIZE];
    int outStringDataLen;

} __attribute__((packed)) TDSMEncReqTci;

#endif /* __NETLAYER_DATASET_H_ */
