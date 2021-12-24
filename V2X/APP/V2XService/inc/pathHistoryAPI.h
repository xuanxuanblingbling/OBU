#ifndef PATHHISTORYAPI_H
#define PATHHISTORYAPI_H

#include "wjv4_uper_De.h"
#include "wjv4_uper_Df.h"
#include "V2xBasicTypes.h"

V2X_BEGIN_HEADER

typedef struct _MSG_bsmPHused
{
    WJV4_STRU_Position3D bsm_pos;
    WJV4_INT_Speed bsm_speed;     /* Driving speed. Unit m/s. */
    WJV4_INT_Heading bsm_heading; /* Driving direction. Unit degree. */
    WJV4_INT_DSecond bsm_secMark; /* DSRC second. Unit: millisecond. */
} MSG_bsmPHused_st, *MSG_bsmPHused_st_ptr;

extern int nHistoryCount;
extern MSG_bsmPHused_st a_PHConciseDataBuffer[15];
int calcuPathHistoryApiC(MSG_bsmPHused_st pt);

V2X_END_HEADER

#endif // PATHHISTORYAPI_H
