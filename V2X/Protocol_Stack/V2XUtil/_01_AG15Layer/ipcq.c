#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "ipcq.h"
typedef struct _LEDCtalgrcv
{
	long mtype;
    int m_u8BlockIndex;  
    int LEDState;  
}LEDCtalgrcv;

static int IpcQueueConnect()
{
    key_t key = ftok("/tmp",50);
    int id = msgget(key,0666|IPC_CREAT);
    return id;
}

int IpcQueueSendingActiveMsg()
{
    int msgid = IpcQueueConnect();
    if (msgid != -1)
    {
        LEDCtalgrcv data;
        data.mtype = 2;
        data.LEDState = 0; //green light flash
        data.m_u8BlockIndex = 2;//module v2x
        return msgsnd(msgid, &data, sizeof(data) - sizeof(long), IPC_NOWAIT);
    }
    return -1;
    
}

int IpcQueueSendingAbnormalMsg()
{
    int msgid = IpcQueueConnect();
    if (msgid != -1)
    {
        LEDCtalgrcv data;
        data.mtype = 2;
        data.LEDState = 2; //red light
        data.m_u8BlockIndex = 2; //module v2x
        return msgsnd(msgid, &data, sizeof(data) - sizeof(long), IPC_NOWAIT);
    }
    return -1;
}