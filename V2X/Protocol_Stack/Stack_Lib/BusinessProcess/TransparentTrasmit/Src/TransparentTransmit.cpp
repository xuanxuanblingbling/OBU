#include <list>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <iostream>
#include <map>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include "TransparentTransmit.h"
#include "InterfaceFrameMsgSending.h"
#include "crc.h"
#include "MemoryBlock.h"

#include "MyTimer.h"
#include "StackCodec.h"
#include "ConfigModuleRW.h"
#include "StateMonitor.h"

extern "C"
{
#include "wj_log.h"
#include "PublicMsg.h"
#include "TimerProc.h"
}
#define SUB_PKG_SIZE 1000
#define MSG_TYPE_TRANSPARENT_TRANSMIT 100001
//device id to tell msg source
#define DEVICE_ID 1001

#define DATA_SENDING_AID 3001
#define DATA_TRANSPORT_AID 3002
typedef struct TransparentTransmit_
{
    int type;          //与MsgFrame类型做区分;
    int dev_id;        //区分数据的设备来源，
    int pkg_seq;       //大包的序号，区分不同的包
    int pkg_len;       //大包总长
    short crc;         //对大包的校验
    short sub_pkg_seq; //小包的序号
    int offset;        //小包起始位置到基地址的偏移
    int sub_pkg_len;   //小包的长度
    char buf[SUB_PKG_SIZE];
} TransparentTransmit, *PTransparentTransmit;

static int g_PackageSequenceNum = 0;

//used to store transparent transmit data block
static std::list<std::shared_ptr<MemoryBlock>> DataBlock;
static std::mutex mtx;
static std::condition_variable cv;

//used for recv  data from
//map for memory blocks
typedef std::map<int, std::shared_ptr<MemoryBlock>> MAP_SUB_PACKAGE;

typedef struct SUB_PACKAGE_
{
    int pkg_count; //total sub-pkg num of the full data package
    MyTimer tmr;
    MAP_SUB_PACKAGE sub_pkg_map;
} SUB_PACKAGE, *PSUB_PACKAGE;

//map of package
typedef std::map<int, std::shared_ptr<SUB_PACKAGE>> MAP_PACKAGE;

static MAP_PACKAGE package;
static std::mutex mtx_pkg;
static std::condition_variable cv_pkg;

static bool RecvFlag = true;
#if 0
/**
 * @brief TransparentTransmitDataTransport 开始发送透传消息(不使用)
 *
 * @param[in] data -- 发送数据
 * @param[in] data_len -- 发送数据的长度
 *
 * @return true/false             成功/失败
 *
 */
static int TransparentTransmitDataTransport(unsigned char *data, int data_len)
{
    if (nullptr == data || 0 == data_len)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "TransparentTransmitDataTransport Param is NULL");
        return Para_Error;
    }

    TransparentTransmit *pData = (PTransparentTransmit)data;

    //change dev_id to the host device
    pData->dev_id = DEVICE_ID;

    //call interface to send data
    //DataSend(pData, sizeof(TransparentTransmit), DATA_TRANSPORT_AID, &CBR);
    return 0;
}
#endif
__attribute__((visibility("default"))) int TransparentTransmitDataSend(unsigned char *data, int data_len, SendTransInfo *callbackReturnInfo)
{
    if (nullptr == data || 0 == data_len)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "TransparentTransmitDataSend Param is NULL");
        return Para_Error;
    }
    if (ProtocolStackParamConfig.v2xStatusFlag.v2xStatus != 1)
    {
        callbackReturnInfo->error_type = -1;
        return -1;
    }
    SendDataInfo sendDataInfo;
    TransparentTransmit *pTransmitData = new TransparentTransmit;

    pTransmitData->type = MSG_TYPE_TRANSPARENT_TRANSMIT;
    pTransmitData->dev_id = DEVICE_ID;
    {
        std::unique_lock<std::mutex> lk(mtx);
        pTransmitData->pkg_seq = g_PackageSequenceNum++;
    }
    pTransmitData->pkg_len = data_len;
    pTransmitData->crc = do_crc(0xffff, data, data_len);

    short sub_pkg_seq = 1;
    int offset = 0;
    int sub_pkg_len = 0;
    int ret = 0;
    int i = 0;
    while (data_len > 0)
    {
        sub_pkg_len = data_len > SUB_PKG_SIZE ? SUB_PKG_SIZE : data_len;

        memcpy(pTransmitData->buf, data, sub_pkg_len);

        pTransmitData->sub_pkg_seq = sub_pkg_seq;
        pTransmitData->offset = offset;
        pTransmitData->sub_pkg_len = sub_pkg_len;

        memset(&sendDataInfo, 0x00, sizeof(sendDataInfo));

        UpdateTxQueDataNum();
        UpdateMsglayerTxDataNum();
        UpdateMsglayerTxData(5);

        //call interface to send pTransmitData
        ret = DataSend(pTransmitData, sizeof(TransparentTransmit),
                       ProtocolStackParamConfig.DSMPParamConfig.PassMessageAID, &(sendDataInfo));
        if (ret != 0)
        {
            LogPrint(LOG_LEVEL_ERR, "Stack_Tx_Err", "DataSend() Error ,ret = %d ", ret);
            break;
        }

        sub_pkg_seq++;
        data += sub_pkg_len;
        offset += sub_pkg_len;
        data_len -= sub_pkg_len;
        //need a sleep here
        callbackReturnInfo->sendDataNum++;
        memcpy(&callbackReturnInfo->sendDataInfo[i++], &(sendDataInfo), sizeof(sendDataInfo));
    }

    callbackReturnInfo->data_type = ProtocolStackParamConfig.DSMPParamConfig.PassMessageAID;
    callbackReturnInfo->error_type = ret;

    delete pTransmitData;
    return ret;
}

//get data from protocol stack and store data into a queue
int TransparentTransmitDataPushInQueue(unsigned char *data, int data_len)
{
    if (nullptr == data || 0 == data_len)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "TransparentTransmitDataPushInQueue Param is NULL");
        return Para_Error;
    }

    {
        std::unique_lock<std::mutex> lk(mtx);
        if (DataBlock.size() > 50)
        {
            //discard front or back
            LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "queue size over flow ");
        }
        else
        {
            std::shared_ptr<MemoryBlock> block = std::make_shared<MemoryBlock>(data_len);
            memcpy(block->buf, data, data_len);
            DataBlock.push_back(block);
            LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "DataBlock size: %d", DataBlock.size());
        }
    }
    cv.notify_all();

    return 0;
}

static int PackageAssemble(std::shared_ptr<SUB_PACKAGE> sub_pkg, unsigned char **data, int *data_len)
{
    if (data_len == nullptr || data == nullptr)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "PackageAssemble Param is NULL");
        return Para_Error;
    }

    MAP_SUB_PACKAGE::iterator it = sub_pkg->sub_pkg_map.begin();

    TransparentTransmit *pTransmitData = (PTransparentTransmit)it->second->buf;
    unsigned char *pdata = (unsigned char *)calloc(1, pTransmitData->pkg_len);
    if (NULL == pdata)
    {
        LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "pdata is NULL");
        return Calloc_Error;
    }

    for (it = sub_pkg->sub_pkg_map.begin(); it != sub_pkg->sub_pkg_map.end(); it++)
    {
        pTransmitData = (PTransparentTransmit)it->second->buf;
        memcpy(pdata + pTransmitData->offset, pTransmitData->buf, pTransmitData->sub_pkg_len);
    }

    *data = pdata;
    *data_len = pTransmitData->pkg_len;
    return 0;
}

//check elements of sub pkg
static void TimerCallback(int arg)
{
    std::unique_lock<std::mutex> lk(mtx_pkg);
    RecvFlag = false;
}

// called by upper user to get full package data
__attribute__((visibility("default"))) int TransparentTransmitDataRecv(int devid, unsigned char **data, int *data_len)
{
    std::shared_ptr<MemoryBlock> sp_chunk;
    // int PackageLen = 0;
    // int PkgSeq = 0;
    // int SubPkgSeq = 0;

    //maintain the MAP_PACKAGE package in timer callback until recv a full package
    StartTimer(0, 1000, TimerCallback);
    {
        std::unique_lock<std::mutex> lk(mtx_pkg);
        RecvFlag = true;
    }

    while (1)
    {
        //recv chunk form queue
        {
            std::unique_lock<std::mutex> lk(mtx);
            bool res = cv.wait_for(lk, std::chrono::milliseconds(1000), []() {
                return !DataBlock.empty();
            });

            if (true == res)
            {
                LogPrint(LOG_LEVEL_INFO, "Stack_Rx_Debug", "get data from DataBlock");
                sp_chunk = DataBlock.front();
                DataBlock.pop_front();
            }
            else
            {
                //return or continue ?
                LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "time out");
                return Other_Error;
            }
        }
        //dev_id check
        TransparentTransmit *pTransmitData = (TransparentTransmit *)sp_chunk->buf;
        if (pTransmitData->dev_id != DEVICE_ID)
        {
            LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "DEVICE_ID check not pass");
            sp_chunk = nullptr;
            continue;
        }

        //recv data
        auto it_pkg = package.find(pTransmitData->pkg_seq);
        if (it_pkg != package.end())
        {
            //pkg_seq exist
            std::shared_ptr<SUB_PACKAGE> sub_pkg = it_pkg->second;

            auto it_sub_pkg = sub_pkg->sub_pkg_map.find(pTransmitData->sub_pkg_seq);
            if (it_sub_pkg == sub_pkg->sub_pkg_map.end())
            {
                //sub pkg not exist, add in
                sub_pkg->sub_pkg_map.insert(std::pair<int, std::shared_ptr<MemoryBlock>>(
                    pTransmitData->sub_pkg_seq, sp_chunk));

                if (pTransmitData->offset + pTransmitData->sub_pkg_len == pTransmitData->pkg_len)
                {
                    sub_pkg->pkg_count = pTransmitData->sub_pkg_seq;
                }
                sub_pkg->tmr.Reset();
            }
        }
        else
        {
            //pkg_seq not exist, add sub pkg in
            std::shared_ptr<SUB_PACKAGE> sub_pkg = std::make_shared<SUB_PACKAGE>();
            sub_pkg->pkg_count = 0;
            sub_pkg->sub_pkg_map.insert(std::pair<int, std::shared_ptr<MemoryBlock>>(
                pTransmitData->sub_pkg_seq, sp_chunk));

            if (pTransmitData->offset + pTransmitData->sub_pkg_len == pTransmitData->pkg_len)
            {
                sub_pkg->pkg_count = pTransmitData->sub_pkg_seq;
            }
            sub_pkg->tmr.Start();
            //sub_pkg->insert(std::pair<int, SP_MEM_BLOCK>(pTransmitData->sub_pkg_seq, sp_chunk));
            package.insert(std::pair<int, std::shared_ptr<SUB_PACKAGE>>(pTransmitData->pkg_seq, sub_pkg));
        }

        unsigned char *pdata = nullptr;
        int len = 0;
        //judge if there is full pkg recved everytime add sub pkg in package
        for (auto &pkg : package)
        {
            std::shared_ptr<SUB_PACKAGE> sub_pkg = pkg.second;
            if (sub_pkg->tmr.IsTimeout())
            {
                package.erase(pkg.first);
                LogPrint(LOG_LEVEL_ERR, "Stack_Rx_Err", "time out");
                continue;
            }

            if (sub_pkg->pkg_count != 0 && (int)sub_pkg->sub_pkg_map.size() == sub_pkg->pkg_count)
            {
                //full package recved
                //assemble data
                PackageAssemble(sub_pkg, &pdata, &len);
                //crc check
                short crc = do_crc(0xffff, pdata, len);
                TransparentTransmit *pTrans = (TransparentTransmit *)(sub_pkg->sub_pkg_map.begin()->second->buf);
                if (crc == pTrans->crc)
                {
                    *data = pdata;
                    *data_len = len;
                    UpdateMsglayerRxData(5);
                    UpdateMsglayerRxDataNum();
                }
                else
                {
                    free(pdata);
                    pdata = NULL;
                }

                package.erase(pkg.first);
                //package.clear();
                return 0;
            }
        }

        //time out to recv a full pkg
        if (RecvFlag == false)
        {
            break;
        }
    }
    package.clear();
    return -1;
}
