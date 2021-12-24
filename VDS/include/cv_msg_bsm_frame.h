/***************************************************************//**
 * @defgroup Message Message Define
 * @{
 *
 *  此模块关于消息层消息体定义.
 *
 * @}
 *
 *******************************************************************/
/***************************************************************//**
 * @defgroup BasicSafetyMessage BasicSafetyMessage Define
 * @ingroup Message
 * @{
 *
 *  此模块参照“数据发送最小准则”提供ＢＳＭ消息体的各帧和元素的定义.
 *
 * @file cv_msg_frame.h
 * @brief BasicSafetyMessage Define file.
 * @author zhangliyang 任何问题请发送邮件至zhangliyang@wanji.net.cn
 * @version　V1.0
 * @copyright VanJee Technology Co., Ltd.
 *
 * 
 *******************************************************************/

#ifndef _CV_MSG_FRAME_H_
#define _CV_MSG_FRAME_H_

/**
 * @brief 历史轨迹点的数量。
 */
#define PH_POINT_NUM_MAX 15

//------------------------------------------------------------------------------
// 消息体帧和元素的定义
//------------------------------------------------------------------------------

/**
 * @brief 定义车辆档位状态。(4)-(6)为保留位
 */
typedef enum TransmissionState_en
{
    trans_state_neutral      = 0,///<空档
    trans_state_park         = 1,///<停止档
    trans_state_forwardGears = 2,///<前进档
    trans_state_reverseGears = 3,///<倒档
    trans_state_reserved1    = 4,///<保留
    trans_state_reserved2    = 5,///<保留
    trans_state_reserved3    = 6,///<保留
    trans_state_unavailable  = 7///<无效值
    
}TransmissionState_en;

/**
 * @brief 指示刹车踏板状态是否处在被踩下状态。
 */
typedef enum BrakePedalStatus_en
{
    brakepedal_status_unavailable      = 0, 
    brakepedal_status_off              = 1, 
    brakepedal_status_on               = 2  
}BrakePedalStatus_en;

/**
 * @brief 定义四轮分别的刹车状态。这里将车辆的轮胎分为左前、右前、左后、右后四组。当车辆进行刹车时，
 * 该数值分别指示了四组轮胎的刹车情况。当车辆为单排轮胎（摩托车等）时，分别以左前和左后表示其前、后轮
 * ，后侧轮胎对应数值置为0。当车辆某一组轮胎由多个组成时，其状态将等效为一个数值来表示。
 */
typedef struct BrakeAppliedStatus_st
{
 
    uint8_t brake_status_unavailable :1;
    uint8_t brake_status_leftFront   :1;
    uint8_t brake_status_leftRear    :1;
    uint8_t brake_status_rightFront  :1;
    uint8_t brake_status_rightRear   :1;

    uint8_t reserved                 :3;
    
}BrakeAppliedStatus_st;

/**
 * @brief 定义牵引力控制系统实时状态。
 */
typedef enum TractionControlStatus_en
{
    traction_status_unavailable = 0,
    traction_status_off         = 1,
    traction_status_on          = 2,
    traction_status_engaged     = 3

}TractionControlStatus_en;

/**
 * @brief 定义车辆基本类型。数值范围[0，255]其中“0”表示未装备/未知/不可用。
 */
typedef enum
{
    Vehicle_unknown                     = 0,///<未知

    /*Passenger car*/ 
    Passenger_car_saloon                = 1,///<普通乘用车
    Passenger_car_convertible_saloon    = 2,///<活顶乘用车
    Passenger_car_pullman_saloon        = 3,///<高级乘用车
    Passenger_car_coupe                 = 4,///<小型乘用车
    Passenger_car_convertible           = 5,///<敞篷车
    Passenger_car_hatchback             = 6,///<仓背乘用车
    Passenger_car_station_wagon         = 7,///<旅行车
    Passenger_car_multipurpose          = 8,///<多用途乘用车
    Passenger_car_forward_control       = 9,///<短头乘用车
    Passenger_car_off_road              = 10,///<越野乘用车

    /*truck*/
    truck_semi_trailer_towing           = 20,///<半挂牵引车
    truck_goods_vehicle                 = 21,///<货车
    truck_tri_wheelvehicle              = 22,///<三轮汽车

    /*Passenger bus*/
    Passenger_bus_minibus               = 30,///<小型客车
    Passenger_bus_city_bus              = 31,///<城市客车
    Passenger_bus_interurban_coach      = 32,///<长途客车
    Passenger_bus_touring_coach         = 33,///<旅游客车
    Passenger_bus_articulated_bus       = 34,///<铰接客车
    Passenger_bus_trolley_bus           = 35,///<无轨电车
    Passenger_busoff_road_bus           = 36,///<越野客车

    /*special purpose*/
    special_purpose_bus                 = 40,///<专用客车
    special_purpose_passenger_car       = 41,///<专用乘用车
    special_purpose_motor_caravan       = 42,///<旅居车
    special_purpose_armoured            = 43,///<防弹车
    special_purpose_hearse              = 44,///<殡仪车
    special_purpose_goods_vehicle       = 45,///<专用作业车
    special_purpose_specialized_goods   = 46,///<专用货车

    /*motorcycle*/
    motorcycle_Ordinary                 = 50,///<普通摩托车
    motorcycle_withtwowheel             = 51,///<两轮普通摩托车
    motorcycle_clewithsidecar           = 52,///<边三轮摩托车
    motorcycle_ightthree_wheeled        = 53,///<正三轮摩托车
    motorcycle_moped                    = 54,///<轻便摩托车
    motorcycle_mopedwithtwowheel        = 55,///<两轮轻便摩托车
    motorcycle_rightthree_wheeledmoped  = 56,///<正三轮轻便摩托车

    /*special Vehicle*/
    special_emergency_Fire_Light        = 62,///<消防轻型车
    special_emergency_Fire_Heavy        = 63,///<消防重型车
  
    special_emergency_Fire_Ambulance    = 65,///<急救车
    special_emergency_Police_Light      = 66,///<公安轻型车
    special_emergency_Police_Heavy      = 67,///<公安重型车
    special_emergency_Engineering       = 68,///<工程抢险车

    /*trailer*/
    trailer_draw_dar                    = 90,///<牵引杆挂车
    trailer_goods_draw_bar              = 91,///<牵引杆货车挂车
    trailer_general_purpose_draw_bar    = 92,///<通用牵引杆挂车
    trailer_special_draw_bar            = 93,///<专用牵引杆挂车
    trailer_semi                        = 94,///<半挂车
    trailer_general_goods_semi          = 95,///<通用货车 半挂车
    trailer_special_semi                = 96,///<专用半挂车
    trailer_caravan_semi                = 97,///<旅居半挂车
    trailer_centre_axle                 = 98,///<中置挂车
    trailer_caravan                     = 99///<旅居挂车

}BasicVehicleClass_en;

/**
 * @brief 定义了一系列车辆的特殊状态。如果数据某一位被置1，表示车辆处于该位对应的状态。
 * 当至少有一种对应状态被激活或者从激活状态恢复，该标志数值才应该被设置和交互。(1),(5)
 * ,(6),(8),(9)可以不发送。
 */
struct VehicleEventFlags_st
{
        uint16_t VehicleEventFlags_eventHazardLights              :1;///<车辆警示灯亮起
        uint16_t VehicleEventFlags_eventStopLineViolation         :1;///<车辆在到达路口前预测自己可能会来不及刹车而越过停止线；(可不发送)
        uint16_t VehicleEventFlags_eventABSactivated              :1;///<ABS系统被触发并超过100ms
        uint16_t VehicleEventFlags_eventTractionControlLoss       :1;///<电子系统控制牵引力被触发并超过100ms。
        uint16_t VehicleEventFlags_eventStabilityControlactivated :1;///<车身稳定控制被触发并超过100ms
        uint16_t VehicleEventFlags_eventHazardousMaterials        :1;///<危险品运输车(可不发送)；
        uint16_t VehicleEventFlags_eventReserved1                 :1;///<保留位
        uint16_t VehicleEventFlags_eventHardBraking               :1;///<车辆急刹车，并且减速度大于4m/s2。
        uint16_t VehicleEventFlags_eventLightsChanged             :1;///<过去2s内，车灯状态改变(可不发)；
        uint16_t VehicleEventFlags_eventWipersChanged             :1;///<过去2s内，车辆雨刷（前窗或后窗）状态改变 (可不发)；
        uint16_t VehicleEventFlags_eventFlatTire                  :1;///<车辆发现至少1个轮胎爆胎了
        uint16_t VehicleEventFlags_eventDisabledVehicle           :1;///<由上述之外的行车安全故障导致的无法正常行驶。
        uint16_t VehicleEventFlags_eventAirBagDeployment          :1;///<触发条件：至少1个安全气囊从正常状态变为弹出状态。截至条件： 系统掉电。
        uint16_t VehicleEventFlags_reserved                       :3;///<保留
};

/**
 * @brief 定义车身周围的车灯状态。用9位字符串表示车灯状态，车身周围车灯关闭时不置位，仅5置位可不发送，全0不发送：
 */
typedef struct ExteriorLights_st
{
        uint16_t lowBeamHeadlightsOn     :1;///<近光灯
        uint16_t highBeamHeadlightsOn    :1;///<远光灯
        uint16_t leftTurnSignalOn        :1;///<左转信号灯
        uint16_t rightTurnSignalOn       :1;///<右转信号灯
        uint16_t hazardSignalOn          :1;///<危险信号灯
        uint16_t automaticLightControlOn :1;///<自动大灯功能
        uint16_t daytimeRunningLightsOn  :1;///<日间行车灯
        uint16_t fogLightOn              :1;///<雾灯
    
        uint16_t parkingLightsOn         :1;///<停车灯
        uint16_t reserved                :7;///<保留
}ExteriorLights_st;

/**
 * @brief 紧急车辆或特殊车辆当前的行驶状态或驾驶行为。
 */
enum ResponseType_en
{
	ResponseType_EN_notInUseOrNotEquipped	= 0,///<表示未装备/不可用
	ResponseType_EN_emergency           	= 1,///<紧急状态——紧急情况服务中
	ResponseType_EN_nonEmergency        	= 2,///<非紧急状态——可用于紧急情况结束后
	ResponseType_EN_pursuit             	= 3,///<追逐——不稳定的驾驶行为
	ResponseType_EN_stationary          	= 4,///<静止——不移动，停止在路边
};

/**
 * @brief 紧急车辆或特殊车辆的警笛或任何专用发声装置的状态.
 */
enum SirenInUse_en 
{
	SirenInUse_EN_unavailable	= 0,
	SirenInUse_EN_notInUse     	= 1,
	SirenInUse_EN_inUse     	= 2,
	SirenInUse_EN_reserved  	= 3
};

/**
 * @brief 紧急车辆或特殊车辆的警示灯或外置专用显示设备的工作状态.
 */
enum LightbarInUse_en 
{
	LightbarInUse_EN_unavailable         	= 0,///<不可用
	LightbarInUse_EN_notInUse              	= 1,///<未使用
	LightbarInUse_EN_inUse                	= 2,///<正在使用
	LightbarInUse_EN_yellowCautionLights	= 3,///<黄色警示灯
	LightbarInUse_EN_undefined            	= 4,///<未定义    
	LightbarInUse_EN_arrowSignsActive   	= 5,///<箭头指示方向运动
	LightbarInUse_EN_slowMovingVehicle  	= 6,///<慢行车辆
	LightbarInUse_EN_freqStops          	= 7///<频繁停止
};

/**
 * @brief 车辆位置.
 */
struct PositionOffset_st
{
	double	pos_lon;
	double	pos_lat;
	float	pos_ele;
};

/**
 * @brief 数值描述了95%置信水平的车辆位置精度。
 */
enum PositionCon_pos
{
    PositionConf_unavailable = 0,///<未装备/未知/不可用；
    PositionConf_a500m       = 1,///<500m
    PositionConf_a200m       = 2,///<200m
    PositionConf_a100m       = 3,///<100m
    PositionConf_a50m        = 4,///<50m
    PositionConf_a20m        = 5,///<20m
    PositionConf_a10m        = 6,///<10m
    PositionConf_a5m         = 7,///<5m
    PositionConf_a2m         = 8,///<2m
    PositionConf_a1m         = 9,///<1m
    PositionConf_a50cm       = 10,///<0.5m
    PositionConf_a20cm       = 11,///<0.2m
    PositionConf_a10cm       = 12,///<0.1m
    PositionConf_a5cm        = 13,///<0.05m
    PositionConf_a2cm        = 14,///<0.02m
    PositionConf_a1cm        = 15///<0.01m
    
};

/**
 * @brief 数值描述了95%置信水平的车辆高程精度。
 */
enum PositionCon_ele_en
{
    ElevationConf_unavailable    = 0,///<装备/未知/不可用
    ElevationConf_elev_500_00    = 1,///<500m   
    ElevationConf_elev_200_00    = 2,///<200m
    ElevationConf_elev_100_00    = 3,///<100m
    ElevationConf_elev_050_00    = 4,///<50m
    ElevationConf_elev_020_00    = 5,///<20m
    ElevationConf_elev_010_00    = 6,///<10m
    ElevationConf_elev_005_00    = 7,///<5m
    ElevationConf_elev_002_00    = 8,///<2m
    ElevationConf_elev_001_00    = 9,///<1m
    ElevationConf_elev_000_50    = 10,///<0.5m
    ElevationConf_elev_000_20    = 11,///<0.2m
    ElevationConf_elev_000_10    = 12,///<0.1m
    ElevationConf_elev_000_05    = 13,///<0.05m
    ElevationConf_elev_000_02    = 14,///<0.02m
    ElevationConf_elev_000_01    = 15///<0.01m
};

/**
 * @brief 车辆的位置精度。
 */
struct PositionConfidence_st
{
	/* Data */
	enum PositionCon_pos	posCon_pos; /* position confidence */
	enum PositionCon_ele_en	posCon_ele; /* elevation confidence */

};

/**
 * @brief PH点的集合。包括位置、时间戳，以及轨迹点处的车速、位置精度以及航向。
 */
struct PathHistoryPoint_st
{
	struct PositionOffset_st		PosOffset;
	struct PositionConfidence_st	posConfidence;
	float 							timeoffset;
	float 							speed; /* Speed over the reported period */
	float 							heading;	
};


/**
 * @brief 根据“数据发送最小准则”中的条件必选元素。
 */
typedef struct _MSG_BasicSafety_opt_st
{
    uint8_t     BrakeSystemStatus_opt    :1;
	uint8_t     ResponseType_opt         :1;
    uint8_t     SirenInUse_opt           :1;
    uint8_t     LightBarInUse_opt        :1;
    uint8_t     VehicleEventFlags_opt    :1;
    uint8_t     PathHistory_opt          :1;
    uint8_t     ExteriorLights           :1;  
    uint8_t     reserved                 :1;

}MSG_BasicSafety_opt_st, *MSG_BasicSafety_opt_st_ptr;

/**
 * @brief ＢＳＭ最小消息体。
 */
typedef struct _BasicSafetyMessage_st
{ 
    /*DF_Position3D */
    double                          pos_lat;///<定义纬度数值，北纬为正，南纬为负。分辨率为1e-7°。提供正负90°范围。数值范围：[-900000000, 900000001]。
	double                          pos_lon;///<定义经度数值。东经为正，西经为负。分辨率为1e-7°。提供正负180°范围。数值范围：[-1799999999, 1800000001]。
	float                           pos_ele;///<定义车辆海拔高程量化指标。以3m为一阶，分辨率为1阶。海拔高程(m)除以3，保留整数位。数值-4096表示无效数值。范围-4096到61439阶。数值范围：[-4096, 61439]。
    /*DF_PositionalAccuracyac */
    float                           semi_major_accu;///<定位系统精度，数值范围[0，255]。255为无效值。
    enum TransmissionState_en       bsm_trans;///<定义车辆档位状态。
    float                           bsm_speed;///<车速大小。分辨率为0.02m/s。数值范围[0, 8191]
    float                         	bsm_heading;///<车辆航向角，即为车头方向与正北方向的顺时针夹角。分辨率为0.0125°。范围 0 到 359.9875°，数值范围为[0，28800）
    /*DF_AccelerationSet4Way */
    float                           bsm_acceSet_longitudinal;///<定义车辆纵向加速度。分辨率为0.01m/s2，数值2001为无效数值。加速度范围为[-2000， 2001]。超过2000的值置为2000，小于-2000的值置为-2000，2001表示不可用/无效数值。
	float                           bsm_acceSet_yawrate;///<车辆横摆角速度，指汽车绕垂直轴的偏转，顺时针旋转为正，逆时针为负。数据分辨率为0.01°/s。数值范围(-32767,32767)。
    /*DF_BrakeSystemStatus */
    enum BrakePedalStatus_en        brakepedal;///<指示刹车踏板状态是否处在被踩下状态。
	struct BrakeAppliedStatus_st    wheelBrakes;///<定义四轮分别的刹车状态。
	enum TractionControlStatus_en   traction;///<定义牵引力控制系统实时状态。
    /*DF_VehicleSize */
    float                           bsm_size_width;///<定义车辆车身宽度。分辨率为1cm。
	float                           bsm_size_length;///<定义车辆车身长度。分辨率为1cm。
    /*DF_VehicleClassification */
    BasicVehicleClass_en            classification;///<定义车辆基本类型。数值范围[0，255]
    /*DF_VehicleSafetyExtensions */
    struct VehicleEventFlags_st     events;///<定义了一系列车辆的特殊状态。//---
    struct PathHistoryPoint_st      ph_point[PH_POINT_NUM_MAX];///<PH点的集合。//---
	/*DF_PathPrediction */
    float                           radiusOfCurve;///<定义车辆的预测线路，主要是预测线路的曲率半径。//---
	float                           confidence;///<定义置信度。数值范围[0，200]，分辨率为0.5。//---
	struct ExteriorLights_st        lights;///<定义车身周围的车灯状态。    
    /*DF_VehicleEmergencyExtensions */
    enum ResponseType_en	        responseType;///<紧急车辆或特殊车辆当前的行驶状态或驾驶行为。
	enum SirenInUse_en	            sirenUse;///<紧急车辆或特殊车辆的警笛或任何专用发声装置的状态。
	enum LightbarInUse_en	        lightsUse;///<紧急车辆或特殊车辆的警示灯或外置专用显示设备的工作状态。
    
}BasicSafetyMessage_st, * BasicSafetyMessage_st_ptr;

#define MSG_BSM_ST_LEN    (sizeof(BasicSafetyMessage_st))

#endif /* _CV_MSG_FRAME_H_ */

