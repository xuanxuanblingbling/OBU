/******************************************************************************
 * 文 件 名 称 ： Msgque.c
 * 功 能 描 述 ： 消息队列封装
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

/*
** ===================================================================
**     Include files.
** ===================================================================
*/
#include "LinuxCommonHeader.h"

#define MODULE_NAME "MSG_QUEUE"
#include "Debug.h"

/*
** ===================================================================
**     create
** ===================================================================
*/
void create_msg(int *m_qid, int msg_key)
{
    key_t key = (key_t)msg_key;
    *m_qid = msgget(key, 0);
    if (*m_qid < 0)
    {
        *m_qid = msgget(key, IPC_CREAT | 0666);
    }
}

/*
** ===================================================================
**     destroy
** ===================================================================
*/
void msg_destroy(int m_qid)
{
    msgctl(m_qid, IPC_RMID, 0);
}

/*
** ===================================================================
**     snd
** ===================================================================
*/
int msg_snd(int m_qid, void *msg, int size)
{
    int ret = msgsnd(m_qid, msg, size - sizeof(long), IPC_NOWAIT);
    if (ret < 0)
    {
        ERR_MSG("msgsnd error");
    }
    return ret;
}

/*
** ===================================================================
**     rcv
** ===================================================================
*/
int msg_rcv_block(int m_qid, void *msg, int size, long type)
{
    int ret = msgrcv(m_qid, msg, size - sizeof(long), type, 0U | MSG_NOERROR);
    if (ret < 0)
    {
        ERR_MSG("msgrcv error");
    }
    return ret;
}

int msg_rcv_unblock(int m_qid, void *msg, int size, long type)
{
    int ret = msgrcv(m_qid, msg, size - sizeof(long), type, MSG_NOERROR | IPC_NOWAIT);
    if (ret < 0)
    {
        if (errno != ENOMSG)
        {
            ERR_MSG("msgrcv error");
        }
        else
        {
            return ENOMSG;
        }
    }
    return ret;
}
