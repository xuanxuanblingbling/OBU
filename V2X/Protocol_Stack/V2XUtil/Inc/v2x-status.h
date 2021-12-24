#ifndef __V2X_STATUS_H__
#define __V2X_STATUS_H__

#ifdef __cplusplus
extern "C"{
#endif

//return val: 
//0: normal; 
//-1, -2: can not get correct cmd result
//1: tx or rx not available  
int CheckV2xState();



#ifdef __cplusplus
}
#endif
#endif