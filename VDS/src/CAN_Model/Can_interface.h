#ifndef __INFCE_H_
#define __INFCE_H_

typedef unsigned char  uint8;       /* 无符号8位整型变量  */
typedef unsigned long long  uint64;    /* 无符号64位整型变量  */

typedef struct VehLampData_Type 
{
    uint8    RecVehLampMessage;
    uint64   VehGNSS_timestamp;
} VehLampType;

typedef struct BrakeSystenStatus_Type
{
    uint8    BrakeSystemStatusData;
    uint64   BrakeSystenStatus_timestamp;
} BrakeSystenStatus;

typedef struct VehicleEventFlags_Type
{
    uint8    VehicleEventFlagsData;
    uint64   VehicleEventFlagsData_timestamp;
} VehicleEventFlags;

typedef struct TransmissionState_Type
{
    uint8    TransmissionStateData;
    uint64   TransmissionStateData_timestamp;
} TransmissionState;

typedef struct SteeringWheelAngle_Type
{
    double    SteeringWheelAngleData;
    uint64   SteeringWheelAngle_timestamp;
} SteeringWheelAngle;

typedef struct Speed_Type
{
    double   SpeedData;
    uint64   SpeedData_timestamp;
} Speed;
typedef struct VehCANData_Type 
{
    VehLampType          LeftTurnLampSt;
    VehLampType          RightTurnLampSt;
    VehLampType          LowBeamSt;
    VehLampType          HighBeamSt;
    VehLampType          FrontFogLampSt;
    VehLampType          RearFogLampSt;
    VehLampType          ParkingLampSt;
    VehLampType          HazardLampSt;
    BrakeSystenStatus    DF_BrakeSystemStatus;
    VehicleEventFlags    DE_VehicleEventFlags;
    TransmissionState    DE_TransmissionState;
    SteeringWheelAngle   DE_SteeringWheelAngle;
    Speed                DE_Speed;
} VehCANData;
int CAN_GetData(VehCANData * fix);
int CAN_Init(void);

#endif