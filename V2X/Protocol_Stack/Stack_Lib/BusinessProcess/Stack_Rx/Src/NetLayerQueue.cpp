#include <iostream>
#include <stdint.h>
#include <list>
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <algorithm>
#include "NetLayerQueue.h"
extern "C"
{
#include "wj_log.h"
#include "ConfigModuleRW.h"
}

typedef int PRIORITY; //0 is highest level
typedef std::vector<std::shared_ptr<tRcvInfo>> MSG_QUEUE;

static std::mutex mtx;
static std::condition_variable cv;

static std::map<PRIORITY, MSG_QUEUE> PriorityQueue{
    {255, std::vector<std::shared_ptr<tRcvInfo>>{}},
    {223, std::vector<std::shared_ptr<tRcvInfo>>{}},
    {191, std::vector<std::shared_ptr<tRcvInfo>>{}},
    {159, std::vector<std::shared_ptr<tRcvInfo>>{}},
    {127, std::vector<std::shared_ptr<tRcvInfo>>{}},
    {95, std::vector<std::shared_ptr<tRcvInfo>>{}},
    {63, std::vector<std::shared_ptr<tRcvInfo>>{}},
    {31, std::vector<std::shared_ptr<tRcvInfo>>{}}};

static int indexArray[] = {255, 223, 191, 159, 127, 95, 63, 31};

static int ArraySize = sizeof(indexArray) / sizeof(indexArray[0]);

int PushDataIntoNetLayerPriorityQueue2(std::shared_ptr<tRcvInfo> pdata)
{
    {
        std::unique_lock<std::mutex> lk(mtx);
        //pdata->priority = 255;
        if (PriorityQueue.find(pdata->priority) != PriorityQueue.end())
        {
            if (PriorityQueue.at(pdata->priority).size() < QUEUE_SIZE)
            {
                PriorityQueue.at(pdata->priority).push_back(pdata);
            }
            else
            {
                //采用Share_Ptr 无需取出释放内存，直接插入即可
                //std::shared_ptr<tRcvInfo> p = PriorityQueue.at(pdata->priority).front();
                //free(p);
                PriorityQueue.at(pdata->priority).erase(PriorityQueue.at(pdata->priority).begin());
                PriorityQueue.at(pdata->priority).insert(PriorityQueue.at(pdata->priority).begin(), pdata);
            }

            int nSta, nSize;
            nSize = PriorityQueue.at(pdata->priority).size();
            nSta = nSize >= QUEUE_SIZE ? 1 : 0;
            if (nSta == 1)
            {
                LogPrint(LOG_LEVEL_DEBUG, "Stack_Rx_Debug", "NetLayerPriorityQueue2 priority = %d nSta = %d  nSize = %d ", pdata->priority, nSta, nSize);
            }
        }
    }
    cv.notify_all();
    return 0;
}

__attribute__((visibility("default"))) std::shared_ptr<tRcvInfo> GetDataFromNetLayerPriorityQueue2()
{
    std::unique_lock<std::mutex> lk(mtx);
    //判断是否接收
    if ((ProtocolStackParamConfig.messageParamConfig.recvParamConfig.RecvSwitch != 1) ||
        (SecDiscardedRate < SEC_MAX_DiscardedRate))
    {
        //信号阻塞
        cv.wait(lk, []() {
            for (auto &it : PriorityQueue)
            {
                if (!it.second.empty())
                {
                    return true;
                }
            }
            return false;
        });
    }
    else
    {
        //信号阻塞+时间轮转
        cv.wait_for(lk, std::chrono::milliseconds(1), []() {
            for (auto &it : PriorityQueue)
            {
                if (!it.second.empty())
                {
                    return true;
                }
            }
            return false;
        });
    }

    std::shared_ptr<tRcvInfo> pdata = NULL;
    int i = 0;
    for (i = 0; i < ArraySize; i++)
    {
        if (PriorityQueue.find(indexArray[i]) != PriorityQueue.end())
        {
            if (!PriorityQueue.at(indexArray[i]).empty())
            {
                pdata = PriorityQueue.at(indexArray[i]).front();
                PriorityQueue.at(indexArray[i]).erase(PriorityQueue.at(indexArray[i]).begin());
                break;
            }
        }
    }

    return pdata;

    // if (cv.wait_for(lk, std::chrono::milliseconds(1), []() {
    //         for (auto &it : PriorityQueue)
    //         {
    //             if (!it.second.empty())
    //             {
    //                 return true;
    //             }
    //         }
    //         return false;
    //     }))
    // {
    //     std::shared_ptr<tRcvInfo>pdata = NULL;
    // int i = 0;
    //     for ( i = 0; i < ArraySize; i++)
    //     {
    //         if (!PriorityQueue.at(indexArray[i]).empty())
    //         {
    //             pdata = PriorityQueue.at(indexArray[i]).front();
    //             PriorityQueue.at(indexArray[i]).erase(PriorityQueue.at(indexArray[i]).begin());
    //             break;
    //         }
    //     }

    //     return pdata;
    // }
    // else
    // {
    //     return NULL;
    // }
}
