/*
 *  Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
  @file v2x_kinematics_data_types.pb.h

  @addtogroup v2x_api_kinematics
  Common types are used for the motion and location reporting system of the
  platform. These types include the structures that are used to both configure
  the Kinematics subsystem and to report periodic fixes. The fixes are
  combinations of inertial/motion data and GNSS solutions determined (possibly
  directly) from satellite processing or dead-reckoning in degraded SV
  reception.
 */

#ifndef PB_V2X_KINEMATICS_DATA_TYPES_PB_H_INCLUDED
#define PB_V2X_KINEMATICS_DATA_TYPES_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup v2x_api_kinematics
@{ */

/* Enum definitions */
/**
  Valid GNSS fix modes.
 */
typedef enum /** @cond */_v2x_fix_mode_t/** @endcond */ {
    V2X_GNSS_MODE_NOT_SEEN = 0,  /**< SV is unavailable or not in view. */
    V2X_GNSS_MODE_NO_FIX = 1,    /**< No SV fix. */
    V2X_GNSS_MODE_2D = 2,        /**< 2D fix with latitude and longitude
                                      information. */
    V2X_GNSS_MODE_3D = 3         /**< 3D fix with latitude, longitude, and
                                      altitude information. */
} v2x_fix_mode_t;


/** @cond *//* Not to be published in PDF */
#define _v2x_fix_mode_t_MIN V2X_GNSS_MODE_NOT_SEEN
#define _v2x_fix_mode_t_MAX V2X_GNSS_MODE_3D
#define _v2x_fix_mode_t_ARRAYSIZE ((v2x_fix_mode_t)(V2X_GNSS_MODE_3D+1))
#define v2x_fix_mode_t_V2X_GNSS_MODE_NOT_SEEN V2X_GNSS_MODE_NOT_SEEN
#define v2x_fix_mode_t_V2X_GNSS_MODE_NO_FIX V2X_GNSS_MODE_NO_FIX
#define v2x_fix_mode_t_V2X_GNSS_MODE_2D V2X_GNSS_MODE_2D
#define v2x_fix_mode_t_V2X_GNSS_MODE_3D V2X_GNSS_MODE_3D

/* Struct definitions */
typedef struct _v2x_msg_t_disable_fixes_tag {
    char dummy_field;
/* @@protoc_insertion_point(struct:v2x_msg_t_disable_fixes_tag) */
} v2x_msg_t_disable_fixes_tag;

typedef struct _v2x_msg_t_enable_fixes_tag {
    char dummy_field;
/* @@protoc_insertion_point(struct:v2x_msg_t_enable_fixes_tag) */
} v2x_msg_t_enable_fixes_tag;
/** @endcond *//* Not to be published in PDF */


/**
  Contains status information for the GNSS satellite.

  This structure is used for each reported fix to indicate the quality of the
  available constellation (or whether the constellation is not available).
 */
typedef struct /** @cond */_v2x_GNSSstatus_t/** @endcond */ {
    bool unavailable;
    /**< Specifies whether a constellation is not equipped or is unavailable.

         @values
         - 0 -- GNSS is available
         - 1 -- GNSS is unavailable @tablebulletend */

    bool aPDOPofUnder5;
    /**< Specifies whether dilution of precision is greater than 5.

         @values
         - 0 -- Not greater than 5
         - 1 -- Greater than 5 @tablebulletend */

    bool inViewOfUnder5;
    /**< Specifies whether fewer than five satellites are in view.

         @values
         - 0 -- Five or more satellites are in view
         - 1 -- Fewer than five satellites are in view @tablebulletend */

    bool localCorrectionsPresent;
    /**< Specifies whether DGPS type corrections are used.

         @values
         - 0 -- Not used
         - 1 -- Used @tablebulletend */

    bool networkCorrectionsPresent;
    /**< Specifies whether RTK type corrections are used.

         @values
         - 0 -- Not used
         - 1 -- Used @tablebulletend */

/* @@protoc_insertion_point(struct:v2x_GNSSstatus_t) */
} v2x_GNSSstatus_t;

/**
  Defines supported GNSS fix generation rates (such as 1 Hz, 5 Hz, 10 Hz).
 */
typedef struct /** @cond */_v2x_gnss_fix_rates_supported_list_t/** @endcond */ {
    uint32_t qty_rates_supported;
    /**< Specify whether the listing or discovery of the supported rates is
         supported.

         @values
         - 0 -- Not supported
         - 1 -- Supported @tablebulletend */

    pb_size_t rates_supported_hz_array_count;
    /**< Number of supported rates. */

    uint32_t rates_supported_hz_array[32];
    /**< Array of data rates supported by the API. */

/* @@protoc_insertion_point(struct:v2x_gnss_fix_rates_supported_list_t) */
} v2x_gnss_fix_rates_supported_list_t;

/**
  Defines client initialization.
 */
typedef struct /** @cond */_v2x_init_t/** @endcond */ {
    uint32_t log_level_mask;
    /**< Log levels as defined in syslog.h. */

    char server_ip_addr[32];
       /**< IP address of the server. @newpagetable */

/* @@protoc_insertion_point(struct:v2x_init_t) */
} v2x_init_t;

/**
  Defines Kinematics features supported by the hardware.
 */
typedef struct /** @cond */_v2x_kinematics_capabilities_t_feature_flags_t/** @endcond */ {
    bool has_3_axis_gyro;
    /**< Specifies whether the hardware supports 3-axis gyro.

         @values
         - 0 -- Not supported
         - 1 -- Supported @tablebulletend */

    bool has_3_axis_accelerometer;
    /**< Specifies whether the hardware supports the 3-axis accelerometer.

         @values
         - 0 -- Not supported
         - 1 -- Supported @tablebulletend */

    bool has_imu_supplemented_dead_reckoning;
    /**< Specifies whether a dead reckoning (DR) solution is available and
         enabled or only GNSS is the result.

         @values
         - 0 -- GNSS is available
         - 1 -- DR is available @tablebulletend */

    bool has_yaw_rate_sensor;
    /**< Specifies whether the IMU includes a yaw rate sensor.

         @values
         - 0 -- Does not include sensor
         - 1 -- Includes sensor @tablebulletend */

    bool used_vehicle_speed;
    /**< Specifies whether the DR algorithm uses the vehicle speed sensor.

         @values
         - 0 -- Does not use sensor
         - 1 -- Uses sensor @tablebulletend */

    bool used_single_wheel_ticks;
    /**< Specifies whether the DR algorithm uses the single wheel ticks.

         @values
         - 0 -- Does not use ticks
         - 1 -- Uses ticks @tablebulletend */

    bool used_front_differential_wheel_ticks;
    /**< Specifies whether the DR algorithm uses two front differential wheel
         ticks.

         @values
         - 0 -- Does not use ticks
         - 1 -- Uses ticks @tablebulletend */

    bool used_rear_differential_wheel_ticks;
    /**< Specifies whether the DR algorithm uses two rear differential wheel
         ticks.

         @values
         - 0 -- Does not use ticks
         - 1 -- Uses ticks @tablebulletend */

    bool used_vehicle_dynamic_model;
    /**< Specifies whether the DR algorithm uses vehicle dynamic model
         factoring in differential ticks, steering, and so on.

         @values
         - 0 -- Does not use factoring
         - 1 -- Uses factoring @tablebulletend */

/* @@protoc_insertion_point(struct:v2x_kinematics_capabilities_t_feature_flags_t) */
} v2x_kinematics_capabilities_t_feature_flags_t;

/**
  Defines the rate type.
 */
typedef struct /** @cond */_v2x_rates_t/** @endcond */ {
    uint32_t rate_report_hz;
    /**< Requested or reported current number of fixes per second. */

    uint32_t offset_nanoseconds;
    /**< Currently unsupported. */

/* @@protoc_insertion_point(struct:v2x_rates_t) */
} v2x_rates_t;

/**
  Returned via v2x_kinematics_get_capabilities() for the client to discover the
  lower level function that this system supports.
 */
typedef struct /** @cond */_v2x_kinematics_capabilities_t/** @endcond */ {
    v2x_kinematics_capabilities_t_feature_flags_t feature_flags;
    /**< Features supported by the API. */

    uint32_t max_fix_rate_supported_hz;
    /**< Highest rate platform that supports GNSS fix generation (in Hz). */

    v2x_gnss_fix_rates_supported_list_t rates_list;
    /**< Supported fix rates. @newpagetable */

/* @@protoc_insertion_point(struct:v2x_kinematics_capabilities_t) */
} v2x_kinematics_capabilities_t;

/**
  Contains a standardized set of parameters that are used for ITS applications.

  The contents of this structure do not include every possible GNSS element
  (for example, raw range data is not included). These fields are via low
  latency for safety applications, both to use locally and to load into a
  J2945/1 or ETSI G5 EN302.637-2 CAM. For example, the fields are used for
  CAM-type and BSM-type safety beacons.

  This structure is populated for each location or dead-reckoning fix, and it
  is supplied on the fix available callback.

  @note1hang Predefined J2735s can be used to communicate raw SV observations
             and RTK correction data. Currently, however, they are not supplied
             from this structure.
 */
typedef struct /** @cond */_v2x_location_fix_t/** @endcond */ {
    double utc_fix_time;
    /**< UTC time in seconds. */

    v2x_fix_mode_t fix_mode;
    /**< Location engine used to produce this record.

         @values No fix, 2D, 3D, RTCM */

    double latitude;
    /**< Latitude in degrees. */

    double longitude;
    /**< Longitude in degrees. */

    double altitude;
    /**< Altitude in meters above the geoid (mean sea level). */

    uint32_t qty_SV_in_view;
    /**< Number of usable space vehicles (SV) that should be in view. */

    uint32_t qty_SV_used;
    /**< Actual number of SVs used in this fix calculation. */

    v2x_GNSSstatus_t gnss_status;
    /**< Status of the GNSS data. */

    bool has_SemiMajorAxisAccuracy;
    /**< Specifies whether the value of the SemiMajorAxisAccuracy field is
         valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double SemiMajorAxisAccuracy;
    /**< Accuracy of the major axis, in meters. */

    bool has_SemiMinorAxisAccuracy;
    /**< Specifies whether the value of the SemiMinorAxisAccuracy field is
         valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double SemiMinorAxisAccuracy;
    /**< Accuracy of the minor axis, in meters. */

    bool has_SemiMajorAxisOrientation;
    /**< Specifies whether the value of the SemiMajorAxisOrientation field is
         valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double SemiMajorAxisOrientation;
    /**< Orientation of the major axis, in meters. */

    bool has_heading;
    /**< Specifies whether the value of the heading field is valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double heading;
    /**< Track degrees relative to true north. */

    bool has_velocity;
    /**< Specifies whether the value of the velocity field is valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double velocity;
    /**< Speed over ground in meters/second. */

    bool has_climb;
    /**< Specifies whether the value of the climb field is valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double climb;
    /**< Vertical speed in meters/second. */

    bool has_lateral_acceleration;
    /**< Specifies whether the value of the lateral_acceleration field is
         valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double lateral_acceleration;
    /**< Acceleration in a latitudinal direction, in meters/second^2. */

    bool has_longitudinal_acceleration;
    /**< Specifies whether the value of the longitudinal acceleration field is
         valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double longitudinal_acceleration;
    /**< Acceleration in a longitudinal direction, in meters/second^2. */

    bool has_vehicle_vertical_acceleration;
    /**< Specifies whether the value of the vehicle_vertical_acceleration field
         is valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double vehicle_vertical_acceleration;
    /**< Vertical acceleration of the vehicle in G force. */ 

    bool has_yaw_rate_degrees_per_second;
    /**< Specifies whether the value of the yaw_rate_degrees_per_second field
         is valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double yaw_rate_degrees_per_second;
    /**< Yaw rate in degrees/second, per SAE J2735. */

    bool has_yaw_rate_95pct_confidence;
    /**< Specifies whether the value of the yaw_rate_95pct_confidence field is
         valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double yaw_rate_95pct_confidence;
    /**< 95% confidence (2 sigma) on the yaw rate in degrees/second. */

    bool has_lane_position_number;
    /**< Specifies whether the value of the lane_position_number field is
         valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double lane_position_number;
    /**< Current lane number, where 0 is either the outer-most edge of the hard
         shoulder or off-road. */

    bool has_lane_position_95pct_confidence;
    /**< Specifies whether the value of the lane_position_95pct_confidence
         field is valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    double lane_position_95pct_confidence;
    /**< 95% confidence range on the lane position. */

    bool has_time_confidence;
    /**< Specifies whether the value of the time_confidence field is valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    float time_confidence;
    /**< 95% (2 sigma) confidence in number of seconds. */

    bool has_heading_confidence;
    /**< Specifies whether the value of the heading_confidence field is valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    float heading_confidence;
    /**< 95% heading confidence in degrees. */

    bool has_velocity_confidence;
    /**< Specifies whether the value of the velocity_confidence field is valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    float velocity_confidence;
    /**< 95% velocity confidence in meters/second. */

    bool has_elevation_confidence;
    /**< Specifies whether the value of the elevation_confidence field is
         valid.

         @values
         - 0 -- Not valid
         - 1 -- Valid @tablebulletend */

    float elevation_confidence;
    /**< 95% uncertainty range (2 sigma) confidence in meters. */

    uint32_t leap_seconds;
    /**< Indicates that both UTC and GPS are required because IEEE 1609.2
         security requires operations to be performed in raw GPS time. */

/* @@protoc_insertion_point(struct:v2x_location_fix_t) */
} v2x_location_fix_t;

/** @} *//* end_addtogroup v2x_api_kinematics */


/** @cond *//* Not to be published in PDF */
/* Default values for struct fields */

/* Initializer values for message structs */
#define v2x_gnss_fix_rates_supported_list_t_init_default {0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define v2x_kinematics_capabilities_t_init_default {v2x_kinematics_capabilities_t_feature_flags_t_init_default, 0, v2x_gnss_fix_rates_supported_list_t_init_default}
#define v2x_kinematics_capabilities_t_feature_flags_t_init_default {0, 0, 0, 0, 0, 0, 0, 0, 0}
#define v2x_GNSSstatus_t_init_default            {0, 0, 0, 0, 0}
#define v2x_location_fix_t_init_default          {0, (v2x_fix_mode_t)0, 0, 0, 0, 0, 0, v2x_GNSSstatus_t_init_default, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, 0}
#define v2x_rates_t_init_default                 {0, 0}
#define v2x_init_t_init_default                  {0, ""}
#define v2x_msg_t_enable_fixes_tag_init_default  {0}
#define v2x_msg_t_disable_fixes_tag_init_default {0}
#define v2x_gnss_fix_rates_supported_list_t_init_zero {0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define v2x_kinematics_capabilities_t_init_zero  {v2x_kinematics_capabilities_t_feature_flags_t_init_zero, 0, v2x_gnss_fix_rates_supported_list_t_init_zero}
#define v2x_kinematics_capabilities_t_feature_flags_t_init_zero {0, 0, 0, 0, 0, 0, 0, 0, 0}
#define v2x_GNSSstatus_t_init_zero               {0, 0, 0, 0, 0}
#define v2x_location_fix_t_init_zero             {0, (v2x_fix_mode_t)0, 0, 0, 0, 0, 0, v2x_GNSSstatus_t_init_zero, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, false, 0, 0}
#define v2x_rates_t_init_zero                    {0, 0}
#define v2x_init_t_init_zero                     {0, ""}
#define v2x_msg_t_enable_fixes_tag_init_zero     {0}
#define v2x_msg_t_disable_fixes_tag_init_zero    {0}

/* Field tags (for use in manual encoding/decoding) */
#define v2x_GNSSstatus_t_unavailable_tag         1
#define v2x_GNSSstatus_t_aPDOPofUnder5_tag       2
#define v2x_GNSSstatus_t_inViewOfUnder5_tag      3
#define v2x_GNSSstatus_t_localCorrectionsPresent_tag 4
#define v2x_GNSSstatus_t_networkCorrectionsPresent_tag 5
#define v2x_gnss_fix_rates_supported_list_t_qty_rates_supported_tag 1
#define v2x_gnss_fix_rates_supported_list_t_rates_supported_hz_array_tag 2
#define v2x_init_t_log_level_mask_tag            1
#define v2x_init_t_server_ip_addr_tag            2
#define v2x_kinematics_capabilities_t_feature_flags_t_has_3_axis_gyro_tag 1
#define v2x_kinematics_capabilities_t_feature_flags_t_has_3_axis_accelerometer_tag 2
#define v2x_kinematics_capabilities_t_feature_flags_t_has_imu_supplemented_dead_reckoning_tag 3
#define v2x_kinematics_capabilities_t_feature_flags_t_has_yaw_rate_sensor_tag 4
#define v2x_kinematics_capabilities_t_feature_flags_t_used_vehicle_speed_tag 5
#define v2x_kinematics_capabilities_t_feature_flags_t_used_single_wheel_ticks_tag 6
#define v2x_kinematics_capabilities_t_feature_flags_t_used_front_differential_wheel_ticks_tag 7
#define v2x_kinematics_capabilities_t_feature_flags_t_used_rear_differential_wheel_ticks_tag 8
#define v2x_kinematics_capabilities_t_feature_flags_t_used_vehicle_dynamic_model_tag 9
#define v2x_rates_t_rate_report_hz_tag           1
#define v2x_rates_t_offset_nanoseconds_tag       2
#define v2x_kinematics_capabilities_t_feature_flags_tag 1
#define v2x_kinematics_capabilities_t_max_fix_rate_supported_hz_tag 2
#define v2x_kinematics_capabilities_t_rates_list_tag 3
#define v2x_location_fix_t_utc_fix_time_tag      1
#define v2x_location_fix_t_fix_mode_tag          2
#define v2x_location_fix_t_latitude_tag          3
#define v2x_location_fix_t_longitude_tag         4
#define v2x_location_fix_t_altitude_tag          5
#define v2x_location_fix_t_qty_SV_in_view_tag    6
#define v2x_location_fix_t_qty_SV_used_tag       7
#define v2x_location_fix_t_gnss_status_tag       8
#define v2x_location_fix_t_SemiMajorAxisAccuracy_tag 9
#define v2x_location_fix_t_SemiMinorAxisAccuracy_tag 10
#define v2x_location_fix_t_SemiMajorAxisOrientation_tag 11
#define v2x_location_fix_t_heading_tag           12
#define v2x_location_fix_t_velocity_tag          13
#define v2x_location_fix_t_climb_tag             14
#define v2x_location_fix_t_lateral_acceleration_tag 15
#define v2x_location_fix_t_longitudinal_acceleration_tag 16
#define v2x_location_fix_t_vehicle_vertical_acceleration_tag 17
#define v2x_location_fix_t_yaw_rate_degrees_per_second_tag 18
#define v2x_location_fix_t_yaw_rate_95pct_confidence_tag 19
#define v2x_location_fix_t_lane_position_number_tag 20
#define v2x_location_fix_t_lane_position_95pct_confidence_tag 21
#define v2x_location_fix_t_time_confidence_tag   22
#define v2x_location_fix_t_heading_confidence_tag 23
#define v2x_location_fix_t_velocity_confidence_tag 24
#define v2x_location_fix_t_elevation_confidence_tag 25
#define v2x_location_fix_t_leap_seconds_tag      26

/* Struct field encoding specification for nanopb */
extern const pb_field_t v2x_gnss_fix_rates_supported_list_t_fields[3];
extern const pb_field_t v2x_kinematics_capabilities_t_fields[4];
extern const pb_field_t v2x_kinematics_capabilities_t_feature_flags_t_fields[10];
extern const pb_field_t v2x_GNSSstatus_t_fields[6];
extern const pb_field_t v2x_location_fix_t_fields[27];
extern const pb_field_t v2x_rates_t_fields[3];
extern const pb_field_t v2x_init_t_fields[3];
extern const pb_field_t v2x_msg_t_enable_fixes_tag_fields[1];
extern const pb_field_t v2x_msg_t_disable_fixes_tag_fields[1];

/* Maximum encoded size of messages (where known) */
#define v2x_gnss_fix_rates_supported_list_t_size 198
#define v2x_kinematics_capabilities_t_size       227
#define v2x_kinematics_capabilities_t_feature_flags_t_size 18
#define v2x_GNSSstatus_t_size                    10
#define v2x_location_fix_t_size                  216
#define v2x_rates_t_size                         12
#define v2x_init_t_size                          40
#define v2x_msg_t_enable_fixes_tag_size          0
#define v2x_msg_t_disable_fixes_tag_size         0

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define V2X_KINEMATICS_DATA_TYPES_MESSAGES \

#endif
/** @endcond *//* Not to be published in PDF */

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
