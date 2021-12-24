/******************************************************************************
 * 文 件 名 称 ： Msgque.h
 * 功 能 描 述 ： 消息队列封装
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#ifndef __MSGQUE_H
#define __MSGQUE_H

#ifdef __cplusplus
extern "C" {
#endif

void create_msg(int *m_qid, int msg_key);
void msg_destroy(int m_qid);
int msg_snd(int m_qid, void *msg ,int size);
int msg_rcv_block(int m_qid, void *msg, int size, long type);
int msg_rcv_unblock(int m_qid, void *msg, int size, long type);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif