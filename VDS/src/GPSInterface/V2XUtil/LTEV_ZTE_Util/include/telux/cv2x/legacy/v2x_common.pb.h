/*
 *  Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *    * Neither the name of The Linux Foundation nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 *  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 *  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file       v2x_common.pb.h
 *
 * @brief      Contains common data types used in v2x API
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

/* Enum definitions */
typedef enum _v2x_status_enum_type {
    V2X_STATUS_SUCCESS = 0,
    V2X_STATUS_FAIL = 1,
    V2X_STATUS_ENO_MEMORY = 3,
    V2X_STATUS_EBADPARM = 4,
    V2X_STATUS_EALREADY = 5,
    V2X_STATUS_KINETICS_PLACEHOLDER = 1000,
    V2X_STATUS_RADIO_PLACEHOLDER = 2000,
    V2X_STATUS_ECHANNEL_UNAVAILABLE = 2001,
    V2X_STATUS_VEHICLE_PLACEHOLDER = 3000
} v2x_status_enum_type;

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

/* Struct definitions */
typedef struct _v2x_api_ver_t {
    uint32_t version_num;
    char build_date_str[128];
    char build_time_str[128];
    char build_details_str[128];
    /* @@protoc_insertion_point(struct:v2x_api_ver_t) */
} v2x_api_ver_t;

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

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
