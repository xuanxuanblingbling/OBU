# if 0
#include "BlockingQueue.h"
extern "C"
{
#include "wj_log.h"
}

int BlockingQueue::DataPushInQueue(MSG_MessageFrame_st *pelement)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    if (m_queue.size() > QUEUE_SIZE)
    {
        LogPrint(LOG_LEVEL_DEBUG, "Stack_TX", "queue size overflow ");
        MSG_MessageFrame_st *ele = m_queue.front();
        free(ele);
        m_queue.pop_front();
    }
    m_queue.push_back(pelement);
    m_cv.notify_all();
    return 0;
}

MSG_MessageFrame_st *BlockingQueue::DataGetFromQueue()
{
    std::unique_lock<std::mutex> lk(m_mtx);
    m_cv.wait(lk, [this]() { return !m_queue.empty(); });
    MSG_MessageFrame_st *ret = m_queue.front();
    m_queue.pop_front();
    return ret;
}
#endif
