#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <stdint.h>
#include "NetLayerPriorityQueue.h"
#include "PublicMsg.h"
extern "C"
{
#include "wj_log.h"
#include "ConfigModuleRW.h"
}
#define QUEUE_SIZE 48
struct cmp
{
    //bool operator()(std::shared_ptr<tRcvInfo> a, std::shared_ptr<tRcvInfo> b)
    bool operator()(tRcvInfo *a, tRcvInfo *b)
    {
        // if (a->priority < b->priority)
        // {
        //     return true; //优先处理b
        // }
        // else if (a->priority == b->priority && a->u64InTime > b->u64InTime)
        // {
        //     return true; //优先处理b
        // }
        // return false;
        if (a->u64InTime > b->u64InTime)
        {
            return true;
        }
        else if (a->u64InTime == b->u64InTime && a->priority < b->priority)
        {
            return true;
        }
        return false;
    }
};

//static std::priority_queue<std::shared_ptr<tRcvInfo>, std::vector<std::shared_ptr<tRcvInfo>>, cmp> NetLayerPriorityQueue;
static std::priority_queue<tRcvInfo *, std::vector<tRcvInfo *>, cmp> NetLayerPriorityQueue;
static std::mutex mtx;
static std::condition_variable cv;

//int PushDataInNetLayerPriorityQueue(std::shared_ptr<tRcvInfo> pdata)
int PushDataInNetLayerPriorityQueue(tRcvInfo *pdata)
{

    {
        std::unique_lock<std::mutex> lk(mtx);
        if (NetLayerPriorityQueue.size() > QUEUE_SIZE)
        {
            //std::shared_ptr<tRcvInfo> pdata = NetLayerPriorityQueue.top();
            tRcvInfo *pdata = NetLayerPriorityQueue.top();
            free(pdata);
            NetLayerPriorityQueue.pop();
            ++SecRecvDis;
        }
        NetLayerPriorityQueue.push(pdata);
    }

    cv.notify_all();
    return 0;
}

//__attribute__((visibility("default"))) std::shared_ptr<tRcvInfo> GetDataFromNetLayerPriorityQueue()
__attribute__((visibility("default"))) tRcvInfo *GetDataFromNetLayerPriorityQueue()
{
    std::unique_lock<std::mutex> lk(mtx);
    //std::shared_ptr<tRcvInfo> pdata = NULL;
    tRcvInfo *pdata = NULL;

    if (!NetLayerPriorityQueue.empty())
    {
        pdata = NetLayerPriorityQueue.top();
        NetLayerPriorityQueue.pop();
        return pdata;
    }
    else
    {
        cv.wait(lk, []() { return !NetLayerPriorityQueue.empty(); });
    }
    //判断是否接收
    // if ((ProtocolStackParamConfig.messageParamConfig.recvParamConfig.RecvSwitch != 1) ||
    //     (SecDiscardedRate < SEC_MAX_DiscardedRate))
    // {
    //     //信号阻塞
    //     //cv.wait(lk, []() { return !NetLayerPriorityQueue.empty(); });
    //     if (!NetLayerPriorityQueue.empty())
    //     {
    //         pdata = NetLayerPriorityQueue.top();
    //         NetLayerPriorityQueue.pop();
    //         return pdata;
    //     }
    //     else
    //     {
    //         cv.wait(lk, []() { return !NetLayerPriorityQueue.empty(); });
    //     }
    // }
    // else
    // {
    //     //信号阻塞+时间轮转
    //     if (!NetLayerPriorityQueue.empty())
    //     {
    //         pdata = NetLayerPriorityQueue.top();
    //         NetLayerPriorityQueue.pop();
    //         return pdata;
    //     }
    //     else
    //     {
    //         cv.wait_for(lk, std::chrono::milliseconds(1), []() { return !NetLayerPriorityQueue.empty(); });
    //     }
    // }

    return NULL;
}
