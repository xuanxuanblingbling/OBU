#ifndef PARAM_PARSE_H
#define PARAM_PARSE_H

#include <stdint.h>
#include "cv_msg_bsm_frame.h"

#define PARAM_PARSE_FAILED      (-1)
#define PARAM_PARSE_SUCCESS     (0)

#define HIGH_Accuracy      0
#define LOW_Accuracy      1


#define VEH_ID_SIZE       34
#define VEH_LWH_MAX_LEN   5//车辆长宽高，配置文件中最大长度

#define QXWZ_AK_SIZE      12
#define QXWZ_AS_SIZE      16
/*
 *@brief：车辆数据结构体 
 */
typedef struct VehParam 
{
    BasicVehicleClass_en VehType;///<定义车辆基本类型。数值范围[0，255]
	float    vehicleLength;//车辆长度，保留小数点后一位，单位：mm
	float    vehicleWidth;//车辆宽度，保留小数点后一位，单位：mm
	float    vehicleHeight;//车辆高度，保留小数点后一位，单位：mm
    uint8_t  VehId [17];//车辆ID,８字节字符串
}__attribute__ ((packed))TVehParam_st;
/*
 *@brief：GNSS定位类型结构体 
 */
typedef struct GnssParam 
{
    uint8_t locationtype;//定位类型：1.移远AG520-GNSS定位，2.千寻服务高精度定位
}__attribute__ ((packed))TGnssParam_st;
/*
 *@brief：QXWZ配置文件消息体 
 */
typedef struct param_qxwz_struct
{
    int8_t  QxwzAk[QXWZ_AK_SIZE];//
    int8_t  QxwzAs[QXWZ_AS_SIZE];//
}__attribute__ ((packed)) Tparam_qxwz_struct_st;
/*
 *@brief：车辆静态配置文件消息体 
 */
typedef struct param_veh_struct
{
    TVehParam_st veh;
    TGnssParam_st gnss;
    Tparam_qxwz_struct_st qxwz;
}__attribute__ ((packed))Tparam_veh_struct;
/*
 *@brief：车辆静态配置文件消息体 
 */
typedef struct param_mcu_struct
{
    uint16_t  PwrUpDlyTime;//上电延时时间
    uint8_t   PwrUpDlyTimeStorFlag;
    uint16_t  DiagDlyTime;//诊断延时时间
    uint8_t   DiagDlyTimeStorFlag;
    uint16_t  DiagVoltRangeL;//诊断电压低限
    uint8_t   DiagVoltRangeLStorFlag;
    uint16_t  DiagVoltRangeH;//诊断电压高限
    uint8_t   DiagVoltRangeHStorFlag;
    uint16_t  DiagHystsVoltH;//诊断迟滞电压高限  
    uint8_t   DiagHystsVoltHStorFlag;
    uint16_t  DiagHystsVoltL;//诊断迟滞电压低限  
    uint8_t   DiagHystsVoltLStorFlag;
}__attribute__ ((packed))Tparam_mcu_struct;


/*********variable definition******/
extern Tparam_veh_struct  g_param_veh_info;
extern Tparam_mcu_struct  g_param_mcu_info;

/*********function definition******/
extern  int32_t param_veh_parse(const int8_t *config_file, Tparam_veh_struct *config);
extern  int32_t param_mcu_parse(const int8_t *config_file, Tparam_mcu_struct *config);

#endif
