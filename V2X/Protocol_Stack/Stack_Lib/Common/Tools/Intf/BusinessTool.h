#ifndef _BUSINESSTOOL_H_
#define _BUSINESSTOOL_H_

#include "PublicMsg.h"
#include "Port.h"

void getMsgNameFromAID(char *MsgType, int AID);

int getAIDFromID(int messageid);

int getMessageidFromAID(int MessageAID, int Messageid);

int getMessageidFromAIDBak(int MessageAID);

int getPriorityFromID(int messageid);

void setDestinationLayer2ID(int AID, unsigned char DestinationLayer2ID[3]);

unsigned char setPPPP(int Priority);

int setPriority(unsigned char pppp);

int setPriorityFromNetAid(int AID);
/**
 * @brief 计算min-max之间的随机数,并转换成16进制
 */
int setSrandSourceLayer2ID(int max, int min, unsigned char returnNum[], int size);

int32_t NetLay_AIDCheck(uint64_t aid);
int32_t SendFrameIDCheck(int id);

#endif