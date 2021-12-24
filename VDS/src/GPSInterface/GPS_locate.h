#ifndef __APPLYLAYER_GPS_H_
#define __APPLYLAYER_GPS_H_
//#include "../../Include/BaseInterface_Include.h"
#include "GPS.h"

extern int RtcmFlag;
#define RTK_Model 1
#define AG15_Model 0

int InitGPS();
int CloseGPS();
extern int GPS_Ag15_GetData(GpsLocation * fix) ; //GpsLocation
extern int GPS_RTK_GetData(GpsLocation * fix);
extern int GetGnssData(GpsLocation * fix); //GpsLocation

#endif
