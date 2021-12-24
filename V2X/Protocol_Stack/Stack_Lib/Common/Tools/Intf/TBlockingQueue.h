#ifndef _T_BLOCKING_QUEUE_H_
#define _T_BLOCKING_QUEUE_H_
#include <list>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <functional>
#include <thread>

#define QUEUE_SIZE 32

template <typename T>
class TBlockingQueue
{
public:
    TBlockingQueue() : deleter(nullptr) {}
    int DataPushInQueue(T data);
    int DataPushInSharePtrQueue(T data);
    T DataGetFromQueue();
    T DataGetFromQueueWaitTimeOut();
    T DataGetFromQueueWait();
    int GetQueueStatus(int &IsFull, int &UsedCnt);
    void SetElementDeleter(void (*pfunc)(void *));

private:
    std::list<T> m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::function<void(void *)> deleter;
};

template <typename T>
T TBlockingQueue<T>::DataGetFromQueue()
{
    std::unique_lock<std::mutex> lk(m_mtx);
    //m_cv.wait(lk, [this]() { return !m_queue.empty(); });
    if (!m_queue.empty())
    {
        T ele = m_queue.front();
        m_queue.pop_front();
        return ele;
    }
    else
    {
        m_cv.wait(lk, [this]() { return !m_queue.empty(); });
    }
    return NULL;
}

template <typename T>
int TBlockingQueue<T>::DataPushInQueue(T data)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    if (m_queue.size() > QUEUE_SIZE)
    {
        T ele = m_queue.front();
        free(ele);
        m_queue.pop_front();
        //采用头插法
        m_queue.push_front(data);
    }
    else
    {
        m_queue.push_back(data);
    }
    m_cv.notify_all();
    return 0;
}

template <typename T>
int TBlockingQueue<T>::DataPushInSharePtrQueue(T data)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    if (m_queue.size() > QUEUE_SIZE)
    {
        //采用Share_Ptr 无需取出释放内存，直接插入即可
        //T ele = m_queue.front();
        //free(ele);
        m_queue.pop_front();
        //采用头插法
        m_queue.push_front(data);
    }
    else
    {
        m_queue.push_back(data);
    }
    m_cv.notify_all();
    return 0;
}
template <typename T>
void TBlockingQueue<T>::SetElementDeleter(void (*pfunc)(void *))
{
    deleter = pfunc;
}

template <typename T>
T TBlockingQueue<T>::DataGetFromQueueWaitTimeOut()
{
    std::unique_lock<std::mutex> lk(m_mtx);
    //2020.07.03 WM add:时间修改为100ms
    //if (m_cv.wait_for(lk, std::chrono::milliseconds(500), [this]() { return !m_queue.empty(); }))
    if (!m_queue.empty())
    {
        T ele = m_queue.front();
        m_queue.pop_front();
        return ele;
    }
    else
    {
        m_cv.wait_for(lk, std::chrono::milliseconds(500), [this]() { return !m_queue.empty(); });
    }
    return NULL;
}
template <typename T>
int TBlockingQueue<T>::GetQueueStatus(int &IsFull, int &UsedCnt)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    UsedCnt = m_queue.size();
    IsFull = UsedCnt >= QUEUE_SIZE ? 1 : 0;

    return 0;
}

template <typename T>
T TBlockingQueue<T>::DataGetFromQueueWait()
{
    std::unique_lock<std::mutex> lk(m_mtx);
    //if (m_cv.wait_for(lk, std::chrono::milliseconds(2), [this]() { return !m_queue.empty(); }))
    if (!m_queue.empty())
    {
        T ele = m_queue.front();
        m_queue.pop_front();
        return ele;
    }
    else
    {
        m_cv.wait_for(lk, std::chrono::milliseconds(2), [this]() { return !m_queue.empty(); });
    }
    return NULL;
}

#endif