/*
 * Copyright (c) 2019 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 */
#ifndef POWER_MANAGER_QMI_SERVICE_SERVICE_01_H
#define POWER_MANAGER_QMI_SERVICE_SERVICE_01_H
/**
  @file power_manager_service_v01.h

  @brief This is the public header file which defines the power_manager_qmi_service service Data structures.

  This header file defines the types and structures that were defined in
  power_manager_qmi_service. It contains the constant values defined, enums, structures,
  messages, and service message IDs (in that order) Structures that were
  defined in the IDL as messages contain mandatory elements, optional
  elements, a combination of mandatory and optional elements (mandatory
  always come before optionals in the structure), or nothing (null message)

  An optional element in a message is preceded by a uint8_t value that must be
  set to true if the element is going to be included. When decoding a received
  message, the uint8_t values will be set to true or false by the decode
  routine, and should be checked before accessing the values that they
  correspond to.

  Variable sized arrays are defined as static sized arrays with an unsigned
  integer (32 bit) preceding it that must be set to the number of elements
  in the array that are valid. For Example:

  uint32_t test_opaque_len;
  uint8_t test_opaque[16];

  If only 4 elements are added to test_opaque[] then test_opaque_len must be
  set to 4 before sending the message.  When decoding, the _len value is set
  by the decode routine and should be checked so that the correct number of
  elements in the array will be accessed.

*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
 *THIS IS AN AUTO GENERATED FILE. DO NOT ALTER IN ANY WAY
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/* This file was generated with Tool version 6.14.7
   It was generated on: Fri Mar  8 2019 (Spin 0)
   From IDL File: power_manager_service_v01.idl */

/** @defgroup power_manager_qmi_service_qmi_consts Constant values defined in the IDL */
/** @defgroup power_manager_qmi_service_qmi_msg_ids Constant values for QMI message IDs */
/** @defgroup power_manager_qmi_service_qmi_enums Enumerated types used in QMI messages */
/** @defgroup power_manager_qmi_service_qmi_messages Structures sent as QMI messages */
/** @defgroup power_manager_qmi_service_qmi_aggregates Aggregate types used in QMI messages */
/** @defgroup power_manager_qmi_service_qmi_accessor Accessor for QMI service object */
/** @defgroup power_manager_qmi_service_qmi_version Constant values for versioning information */

#include <stdint.h>
#include "qmi_idl_lib.h"
#include "common_v01.h"


#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup power_manager_qmi_service_qmi_version
    @{
  */
/** Major Version Number of the IDL used to generate this file */
#define POWER_MANAGER_QMI_SERVICE_V01_IDL_MAJOR_VERS 0x01
/** Revision Number of the IDL used to generate this file */
#define POWER_MANAGER_QMI_SERVICE_V01_IDL_MINOR_VERS 0x01
/** Major Version Number of the qmi_idl_compiler used to generate this file */
#define POWER_MANAGER_QMI_SERVICE_V01_IDL_TOOL_VERS 0x06
/** Maximum Defined Message ID */
#define POWER_MANAGER_QMI_SERVICE_V01_MAX_MESSAGE_ID 0x0004
/**
    @}
  */


/** @addtogroup power_manager_qmi_service_qmi_consts
    @{
  */
/**
    @}
  */

/** @addtogroup power_manager_qmi_service_qmi_enums
    @{
  */
typedef enum {
  PWR_STATE_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  UNKNOWN_STATE_V01 = 0,
  SUSPEND_STATE_V01 = 1,
  RESUME_STATE_V01 = 2,
  SHUTDOWN_STATE_V01 = 3,
  PWR_STATE_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}pwr_state_v01;
/**
    @}
  */

/** @addtogroup power_manager_qmi_service_qmi_enums
    @{
  */
typedef enum {
  PWR_STATE_ACK_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  ACK_SUSPEND_V01 = 0,
  ACK_SHUTDOWN_V01 = 1,
  PWR_STATE_ACK_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}pwr_state_ack_v01;
/**
    @}
  */

/** @addtogroup power_manager_qmi_service_qmi_messages
    @{
  */
/** Request Message; This command just registers the qmi client to server. */
typedef struct {

  /* Mandatory */
  uint32_t value;
}pwr_mgr_register_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup power_manager_qmi_service_qmi_messages
    @{
  */
/** Response Message; This command just registers the qmi client to server. */
typedef struct {

  /* Mandatory */
  pwr_state_v01 curr_state;
  /**<   Standard response type.*/
}pwr_mgr_register_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup power_manager_qmi_service_qmi_messages
    @{
  */
/** Request Message; This command will be used by clients to take device in any desired state. */
typedef struct {

  /* Mandatory */
  pwr_state_v01 qmi_reqstate;
}pwr_mgr_cmd_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup power_manager_qmi_service_qmi_messages
    @{
  */
/** Response Message; This command will be used by clients to take device in any desired state. */
typedef struct {

  /* Mandatory */
  qmi_response_type_v01 qmi_resp;
  /**<   Standard response type.*/
}pwr_mgr_cmd_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup power_manager_qmi_service_qmi_messages
    @{
  */
/** Request Message; This is acknowledgement for the notifications received. */
typedef struct {

  /* Mandatory */
  pwr_state_ack_v01 acknowledgement;
}pwr_mgr_ack_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup power_manager_qmi_service_qmi_messages
    @{
  */
/** Response Message; This is acknowledgement for the notifications received. */
typedef struct {

  /* Mandatory */
  qmi_response_type_v01 ackresp;
  /**<   Standard response type.*/
}pwr_mgr_ack_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup power_manager_qmi_service_qmi_messages
    @{
  */
/** Indication Message; This is acknowledgement for the notifications received. */
typedef struct {

  /* Mandatory */
  pwr_state_v01 notify_state;
}pwr_mgr_broadcast_indication_msg_v01;  /* Message */
/**
    @}
  */

/* Conditional compilation tags for message removal */
//#define REMOVE_ACKNOWLEDGEMENT FOR POWER STATES_V01
//#define REMOVE_POWER_MANAGER_COMMAND_V01
//#define REMOVE_POWER_MANAGER_REGISTRATION_V01

/*Service Message Definition*/
/** @addtogroup power_manager_qmi_service_qmi_msg_ids
    @{
  */
#define PWR_MGR_REGISTER_REQ_V01 0x0001
#define PWR_MGR_REGISTER_RESP_V01 0x0001
#define PWR_MGR_CMD_REQ_V01 0x0002
#define PWR_MGR_CMD_RESP_V01 0x0002
#define PWR_MGR_ACK_REQ_V01 0x0003
#define PWR_MGR_ACK_RESP_V01 0x0003
#define PWR_MGR_BROADCAST_IND_V01 0x0004
/**
    @}
  */

/* Service Object Accessor */
/** @addtogroup wms_qmi_accessor
    @{
  */
/** This function is used internally by the autogenerated code.  Clients should use the
   macro power_manager_qmi_service_get_service_object_v01( ) that takes in no arguments. */
qmi_idl_service_object_type power_manager_qmi_service_get_service_object_internal_v01
 ( int32_t idl_maj_version, int32_t idl_min_version, int32_t library_version );

/** This macro should be used to get the service object */
#define power_manager_qmi_service_get_service_object_v01( ) \
          power_manager_qmi_service_get_service_object_internal_v01( \
            POWER_MANAGER_QMI_SERVICE_V01_IDL_MAJOR_VERS, POWER_MANAGER_QMI_SERVICE_V01_IDL_MINOR_VERS, \
            POWER_MANAGER_QMI_SERVICE_V01_IDL_TOOL_VERS )
/**
    @}
  */


#ifdef __cplusplus
}
#endif
#endif
