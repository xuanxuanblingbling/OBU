#if 0
#ifndef _BLOCKING_QUEUE_H_
#define _BLOCKING_QUEUE_H_
#include <list>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <functional>

#define QUEUE_SIZE 10

extern "C"{
#include "wj_Message_com.h"
}

class BlockingQueue
{
public:
    int DataPushInQueue(MSG_MessageFrame_st *pdata);
    MSG_MessageFrame_st* DataGetFromQueue();
private:
    std::list<MSG_MessageFrame_st*> m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
};


#endif
#endif
