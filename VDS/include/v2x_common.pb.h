/*
 *  Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
  @file v2x_common.pb.h

  @addtogroup v2x_api_common
  The following common typedefs and macros are used across all parts of this
  platform.
 */

#ifndef PB_V2X_COMMON_PB_H_INCLUDED
#define PB_V2X_COMMON_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup v2x_api_common
@{ */

/* Enum definitions */
/**
  Valid types for subsystem status, and return status codes for API function
  calls and callbacks.
 */
typedef enum /** @cond */_v2x_status_enum_type/** @endcond */ {
    V2X_STATUS_SUCCESS = 0,     /**< Operation is successful. */
    V2X_STATUS_FAIL = 1,        /**< Operation is unsuccessful. This is a
                                     generic error failure status that can be
                                     due to radio hardware resource
                                     limitations, geofencing, and so on. */
    V2X_STATUS_ENO_MEMORY = 3,  /**< Failure due to a memory allocation
                                     issue. */
    V2X_STATUS_EBADPARM = 4,    /**< One of the supplied parameters is bad. */
    V2X_STATUS_EALREADY = 5,    /**< Attempted step was already issued, and
                                    this call is not required. */
    V2X_STATUS_KINETICS_PLACEHOLDER = 1000,
                                /**< Begin the return codes associated with the
                                     Kinematics interface. */
    V2X_STATUS_RADIO_PLACEHOLDER = 2000,
                                /**< Begin the return codes associated with the
                                     Radio interface. */
    V2X_STATUS_ECHANNEL_UNAVAILABLE = 2001,
                                /**< Requested radio frequency cannot be used
                                     at this time. */
    V2X_STATUS_VEHICLE_PLACEHOLDER = 3000
                                /**< Begin the return codes associated with the
                                     Vehicle Data interface. */
} v2x_status_enum_type;


/** @cond *//* Not to be published in PDF */
#define _v2x_status_enum_type_MIN V2X_STATUS_SUCCESS
#define _v2x_status_enum_type_MAX V2X_STATUS_VEHICLE_PLACEHOLDER
#define _v2x_status_enum_type_ARRAYSIZE ((v2x_status_enum_type)(V2X_STATUS_VEHICLE_PLACEHOLDER+1))
#define v2x_status_enum_type_V2X_STATUS_SUCCESS V2X_STATUS_SUCCESS
#define v2x_status_enum_type_V2X_STATUS_FAIL V2X_STATUS_FAIL
#define v2x_status_enum_type_V2X_STATUS_ENO_MEMORY V2X_STATUS_ENO_MEMORY
#define v2x_status_enum_type_V2X_STATUS_EBADPARM V2X_STATUS_EBADPARM
#define v2x_status_enum_type_V2X_STATUS_EALREADY V2X_STATUS_EALREADY
#define v2x_status_enum_type_V2X_STATUS_KINETICS_PLACEHOLDER V2X_STATUS_KINETICS_PLACEHOLDER
#define v2x_status_enum_type_V2X_STATUS_RADIO_PLACEHOLDER V2X_STATUS_RADIO_PLACEHOLDER
#define v2x_status_enum_type_V2X_STATUS_ECHANNEL_UNAVAILABLE V2X_STATUS_ECHANNEL_UNAVAILABLE
#define v2x_status_enum_type_V2X_STATUS_VEHICLE_PLACEHOLDER V2X_STATUS_VEHICLE_PLACEHOLDER
/** @endcond *//* Not to be published in PDF */

/**
  Contains retrieved information about the SDK API library that is called.
  Each SDK component (Kinematics, Radio, Vehicle Data) implements a method to
  return this structure.
 */
typedef struct /** @cond */_v2x_api_ver_t/** @endcond */ {
    uint32_t version_num;
    /**< Version number of the interface. */

    char build_date_str[128];
    /**< Date of the build (part of the data string). */

    char build_time_str[128];
    /**< Time of the build (part of the data string). */

    char build_details_str[128];
    /**< Build details (part of the data string). */

/* @@protoc_insertion_point(struct:v2x_api_ver_t) */
} v2x_api_ver_t;

/** @} *//* end_addtogroup v2x_api_common */


/** @cond *//* Not to be published in PDF */
/* Default values for struct fields */

/* Initializer values for message structs */
#define v2x_api_ver_t_init_default               {0, "", "", ""}
#define v2x_api_ver_t_init_zero                  {0, "", "", ""}

/* Field tags (for use in manual encoding/decoding) */
#define v2x_api_ver_t_version_num_tag            1
#define v2x_api_ver_t_build_date_str_tag         2
#define v2x_api_ver_t_build_time_str_tag         3
#define v2x_api_ver_t_build_details_str_tag      4

/* Struct field encoding specification for nanopb */
extern const pb_field_t v2x_api_ver_t_fields[5];

/* Maximum encoded size of messages (where known) */
#define v2x_api_ver_t_size                       399

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define V2X_COMMON_MESSAGES \

#endif
/** @endcond *//* Not to be published in PDF */

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
