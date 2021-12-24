/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       MsgRcvSd.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : MsgRcvSd.h
*   Author:         : wensheng.zhang       2020
********************************************************************************
*   Limitations:      None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version       Date       Initials        CR#        Descriptions
*   -------   ----------  --------------    ------    -------------------
*   01.00.00  07/07/2020  wensheng.zhang      N/A         Original
********************************************************************************
*END_FILE_HDR*/
#ifndef MSGRCVSD_H
#define MSGRCVSD_H

#define MSGM_RCVSD_MAIN    					MsgM_RcvSd_Main
#define MSGM_SEND_SIGNAL   					MsgM_Send_Fun

#ifdef __cplusplus   
extern "C" {
#endif
extern void MsgM_RcvSd_Main();

extern void MsgM_Send_Fun(uint8_t *DataStruct, int StructLen, int index);

#ifdef __cplusplus   
}
#endif

#define SYS_CONFIG_RQ_ID  0x4001
#define SYS_MCU_PD_RS_ID  0x4002



typedef struct _SysConfigRq
{ 
    uint8_t appcfgUpdaeNotify;
    uint8_t v2xcfgUpdaeNotify;
    uint8_t vdscfgUpdaeNotify;
    uint8_t netcfgUpdaeNotify;
}__attribute__ ((packed))SysConfigRq;
#define SYSCONFIGRQ_LEN    (sizeof(SysConfigRq))
typedef struct _SysConfigRq_all
{
    uint16_t    id;
    uint16_t    length;
    SysConfigRq rqdata;
    uint8_t     bcc;
}__attribute__ ((packed))SysConfigRq_all;

typedef struct _SysMcuConfigRs
{ 
    uint8_t PowerDownResp;
}__attribute__ ((packed))SysMcuConfigRs;
#define SYSMCUCONFIGRS_LEN    (sizeof(SysMcuConfigRs))

typedef struct _SysMcuConfigRs_all
{   uint16_t        id;
    uint16_t        length;
    SysMcuConfigRs  mcursdata;
    uint8_t         bcc;

}__attribute__ ((packed))SysMcuConfigRs_all;


enum
{
    SYS_CONFIG,
    SYS_MCU_PD,
    LAST_SIGNAL
};

#define EVENT_REPEAT_PUSH_NUM   5
#define EVENT_REPEAT_CYCLE_TIME 100

#endif
