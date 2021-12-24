#ifndef _FRAME_MESSAGE_SENDING_H_
#define _FRAME_MESSAGE_SENDING_H_
#include "TBlockingQueue.h"
#include "InterfaceFrameMsgSending.h"
#include "MemoryBlock.h"
#include <thread>
#include <semaphore.h>
#include "Timer.h"
#include <string.h>

class FrameMessageSending
{
public:
    FrameMessageSending()
    {
        block = std::make_shared<MemoryBlock>(MAX_DUMMY_PACKET_LEN);
        pstruUperDataV2 = (WJV2_UperData *)calloc(1, sizeof(WJV2_UperData));
        pstruUperDataV3 = (WJV3_UperData *)calloc(1, sizeof(WJV3_UperData));
        pstruUperDataV4 = (WJV4_UperData *)calloc(1, sizeof(WJV4_UperData));
        pstruUperDataVN4 = (WJVN4_UperData *)calloc(1, sizeof(WJVN4_UperData));
    }
    ~FrameMessageSending()
    {
        if (pstruUperDataV2)
        {
            free(pstruUperDataV2);
            pstruUperDataV2 = nullptr;
        }
        if (pstruUperDataV3)
        {
            free(pstruUperDataV3);
            pstruUperDataV3 = nullptr;
        }
        if (pstruUperDataV4)
        {
            free(pstruUperDataV4);
            pstruUperDataV4 = nullptr;
        }
        if (pstruUperDataVN4)
        {
            free(pstruUperDataVN4);
            pstruUperDataVN4 = nullptr;
        }
    }
    int DataPushInQueue(MSG_MessageType_st *data);
    void ThreadProcFrameMsg();
    void SetMsgCallback(SENDCALL_BACK pfunc)
    {
        pOnSendingComplete = pfunc;
    }

private:
    int MessageSending(WJV2_STRU_MessageFrame *data, tExtenSionCommn_st *extension, int nEmergencyEventFlag, SendDataInfo *sendDataInfo);
    int MessageSending(WJV4_STRU_MessageFrame *data, tExtenSionCommn_st *extension, int nEmergencyEventFlag, SendDataInfo *sendDataInfo);
    int MessageSending(WJVN4_STRU_MessageFrame *data, tExtenSionCommn_st *extension, int nEmergencyEventFlag, SendDataInfo *sendDataInfo);
    int MessageSending(WJV3_STRU_MessageFrame *data, tExtenSionCommn_st *extension, SendDataInfo *sendDataInfo);

    TBlockingQueue<MSG_MessageType_st *> queue;
    SENDCALL_BACK pOnSendingComplete;
    std::shared_ptr<MemoryBlock> block;
    WJV2_UperData *pstruUperDataV2;
    WJV3_UperData *pstruUperDataV3;
    WJV4_UperData *pstruUperDataV4;
    WJVN4_UperData *pstruUperDataVN4;
};

class FrameMessageSendingblock
{
public:
    FrameMessageSendingblock()
    {
        block = std::make_shared<MemoryBlock>(MAX_DUMMY_PACKET_LEN);
        pstruUperData = (WJ_UperData *)calloc(1, sizeof(WJ_UperData));
        pstruUperDataV2 = (WJV2_UperData *)calloc(1, sizeof(WJV2_UperData));
        pstruUperDataV3 = (WJV3_UperData *)calloc(1, sizeof(WJV3_UperData));
        pstruUperDataV4 = (WJV4_UperData *)calloc(1, sizeof(WJV4_UperData));
        pstruUperDataVN4 = (WJVN4_UperData *)calloc(1, sizeof(WJVN4_UperData));
        index = 0;
    }
    ~FrameMessageSendingblock()
    {
        if (pstruUperData)
        {
            free(pstruUperData);
            pstruUperData = nullptr;
        }

        if (pstruUperDataV2)
        {
            free(pstruUperDataV2);
            pstruUperDataV2 = nullptr;
        }
        if (pstruUperDataV3)
        {
            free(pstruUperDataV3);
            pstruUperDataV3 = nullptr;
        }
        if (pstruUperDataV4)
        {
            free(pstruUperDataV4);
            pstruUperDataV4 = nullptr;
        }
        if (pstruUperDataVN4)
        {
            free(pstruUperDataVN4);
            pstruUperDataVN4 = nullptr;
        }
    }
    void SetMsgCallback(SENDCALL_BACK pfunc)
    {
        pOnSendingComplete = pfunc;
    }
    void SetIndex(int Index)
    {
        index = Index;
    }
    int MessageSending(WJ_UperData *pstruUperData, int MsgAid, SendDataInfo *sendDataInfo);
    int index;
    WJ_UperData *pstruUperData; /* 消息层码流buf */
    std::shared_ptr<MemoryBlock> block;
    WJV2_UperData *pstruUperDataV2;
    WJV3_UperData *pstruUperDataV3;
    WJV4_UperData *pstruUperDataV4;
    WJVN4_UperData *pstruUperDataVN4;
    SENDCALL_BACK pOnSendingComplete;
};

class FrameMessageSendingFromFile
{
public:
    FrameMessageSendingFromFile()
    {
        memset(&Hndl, 0x00, sizeof(ST_OSA_TimerHndl));
        memset(&sevVal, 0x00, sizeof(sevVal));
        m_hz = 0;
        block = new (FrameMessageSendingblock);
    }
    ~FrameMessageSendingFromFile()
    {
        if (Hndl.timerid != NULL)
        {
            ST_OSA_timerStop(&Hndl);
            ST_OSA_timerDelete(&Hndl);
        }
        if (block != NULL)
        {
            delete (block);
            block = NULL;
        }
        memset(&Hndl, 0x00, sizeof(ST_OSA_TimerHndl));
        memset(&sevVal, 0x00, sizeof(sevVal));
        m_hz = 0;
    }
    int m_hz;
    ST_OSA_TimerHndl Hndl;
    union sigval sevVal;
    FrameMessageSendingblock *block;
};

void MessageSendingFromFile(union sigval value);

class FrameMessageSendingSerial
{
public:
    FrameMessageSendingSerial()
    {
        block = std::make_shared<MemoryBlock>(MAX_DUMMY_PACKET_LEN);
        pstruUperDataV2 = (WJV2_UperData *)calloc(1, sizeof(WJV2_UperData));
        pstruUperDataV3 = (WJV3_UperData *)calloc(1, sizeof(WJV3_UperData));
        pstruUperDataV4 = (WJV4_UperData *)calloc(1, sizeof(WJV4_UperData));
        pstruUperDataVN4 = (WJVN4_UperData *)calloc(1, sizeof(WJVN4_UperData));
    }
    ~FrameMessageSendingSerial()
    {
        if (pstruUperDataV2)
        {
            free(pstruUperDataV2);
            pstruUperDataV2 = nullptr;
        }
        if (pstruUperDataV3)
        {
            free(pstruUperDataV3);
            pstruUperDataV3 = nullptr;
        }
        if (pstruUperDataV4)
        {
            free(pstruUperDataV4);
            pstruUperDataV4 = nullptr;
        }
        if (pstruUperDataVN4)
        {
            free(pstruUperDataVN4);
            pstruUperDataVN4 = nullptr;
        }
    }
    void SetMsgCallback(SENDCALL_BACK pfunc)
    {
        pOnSendingComplete = pfunc;
    }
    int MessageSending(MSG_MessageType_st *data);

private:
    SENDCALL_BACK pOnSendingComplete;
    std::shared_ptr<MemoryBlock> block;
    WJV2_UperData *pstruUperDataV2;
    WJV3_UperData *pstruUperDataV3;
    WJV4_UperData *pstruUperDataV4;
    WJVN4_UperData *pstruUperDataVN4;
};

#endif
