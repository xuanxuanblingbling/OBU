/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       PowerM.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : PowerM.h
*   Author:         : chengwu.wang       2020
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
*   01.00.00  07/07/2020  chengwu.wang      N/A         Original
********************************************************************************
*END_FILE_HDR*/

#ifndef POWERM_H
#define POWERM_H


typedef struct _PowerM_PwrRq{
	int					PowerRqValue;
} PowerM_PwrRq;
	
#define POWERM_MAIN          PowerM_Main

#ifdef __cplusplus   
extern "C" {
#endif

extern void PowerM_Main();
#ifdef __cplusplus   
}
#endif


#endif
