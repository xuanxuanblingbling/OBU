/*
 * BaseInterface_Include.h
 *
 *  Created on: May 15, 2018
 *      Author: root
 */

#ifndef BASEINTERFACE_INCLUDE_H_
#define BASEINTERFACE_INCLUDE_H_

#include "../BaseInterface/DataSet.h"

#include "../BaseInterface/MsgQueue/MsgQueue.h"

#include "../BaseInterface/DataSet.h"

#include "../BaseInterface/ConfUtil/Config.h"

#include "../BaseInterface/GPSUtil/GPS.h"





enum Station
{
    State_Set_OK = 0,
    State_Set_None = 1,
    State_Set_Error = 2
};


typedef struct _OperateState
{
    uint8_t Init;
    uint8_t Start_Dsm_Tx;
    uint8_t Stop_Dsm_Tx;
    uint8_t Start_Dsm_Rx;
    uint8_t Stop_Dsm_Rx;
    uint8_t Start_Dsa_Tx;
    uint8_t Stop_Dsa_Tx;
    uint8_t Add_User;
    uint8_t Del_User;
} tOperateState;

extern tOperateState g_sOperateState;

#endif /* BASEINTERFACE_INCLUDE_H_ */
