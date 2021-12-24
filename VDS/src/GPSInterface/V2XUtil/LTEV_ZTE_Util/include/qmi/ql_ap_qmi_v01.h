#ifndef QL_AP_QMI_SERVICE_01_H
#define QL_AP_QMI_SERVICE_01_H
/**
  @file ql_ap_qmi_v01.h

  @brief This is the public header file which defines the ql_ap_qmi service Data structures.

  This header file defines the types and structures that were defined in
  ql_ap_qmi. It contains the constant values defined, enums, structures,
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
  

  
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
 *THIS IS AN AUTO GENERATED FILE. DO NOT ALTER IN ANY WAY
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/* This file was generated with Tool version 6.14.7 
   It was generated on: Tue Jan 15 2019 (Spin 0)
   From IDL File: ql_ap_qmi_v01.idl */

/** @defgroup ql_ap_qmi_qmi_consts Constant values defined in the IDL */
/** @defgroup ql_ap_qmi_qmi_msg_ids Constant values for QMI message IDs */
/** @defgroup ql_ap_qmi_qmi_enums Enumerated types used in QMI messages */
/** @defgroup ql_ap_qmi_qmi_messages Structures sent as QMI messages */
/** @defgroup ql_ap_qmi_qmi_aggregates Aggregate types used in QMI messages */
/** @defgroup ql_ap_qmi_qmi_accessor Accessor for QMI service object */
/** @defgroup ql_ap_qmi_qmi_version Constant values for versioning information */

#include <stdint.h>
#include "qmi_idl_lib.h"


#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup ql_ap_qmi_qmi_version
    @{
  */
/** Major Version Number of the IDL used to generate this file */
#define QL_AP_QMI_V01_IDL_MAJOR_VERS 0x01
/** Revision Number of the IDL used to generate this file */
#define QL_AP_QMI_V01_IDL_MINOR_VERS 0x01
/** Major Version Number of the qmi_idl_compiler used to generate this file */
#define QL_AP_QMI_V01_IDL_TOOL_VERS 0x06
/** Maximum Defined Message ID */
#define QL_AP_QMI_V01_MAX_MESSAGE_ID 0x0001
/**
    @}
  */


/** @addtogroup ql_ap_qmi_qmi_consts
    @{
  */

/**     */
#define QL_AP_QMI_SERVICE_V01 228
/**
    @}
  */

/** @addtogroup ql_ap_qmi_qmi_enums
    @{
  */
typedef enum {
  QL_AP_QMI_RESULT_TYPE_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  QL_AP_QMI_SUCCESS_V01 = 0, 
  QL_AP_QMI_FAILUTE_V01 = 1, 
  QL_AP_QMI_RESULT_TYPE_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}ql_ap_qmi_result_type_v01;
/**
    @}
  */

/** @addtogroup ql_ap_qmi_qmi_enums
    @{
  */
typedef enum {
  QL_AP_QMI_ERROR_TYPE_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  QL_AP_QMI_ERR_NONE_V01 = 0x0000, 
  QL_AP_QMI_ERROR_TYPE_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}ql_ap_qmi_error_type_v01;
/**
    @}
  */

/** @addtogroup ql_ap_qmi_qmi_aggregates
    @{
  */
typedef struct {

  ql_ap_qmi_result_type_v01 result_t;

  ql_ap_qmi_error_type_v01 err_t;
}ql_ap_qmi_response_type_v01;  /* Type */
/**
    @}
  */

/** @addtogroup ql_ap_qmi_qmi_messages
    @{
  */
/**  Message;  */
typedef struct {

  /* Mandatory */
  char key[256];

  /* Mandatory */
  int32_t len;
}ql_ap_qmi_auth_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup ql_ap_qmi_qmi_messages
    @{
  */
/**  Message;  */
typedef struct {

  /* Mandatory */
  char auth[256];

  /* Mandatory */
  int32_t len;
}ql_ap_qmi_auth_resp_msg_v01;  /* Message */
/**
    @}
  */

/* Conditional compilation tags for message removal */ 

/*Service Message Definition*/
/** @addtogroup ql_ap_qmi_qmi_msg_ids
    @{
  */
#define QMI_AP_AUTH_REQ_V01 0x0001
#define QMI_AP_AUTH_RSP_V01 0x0001
/**
    @}
  */

/* Service Object Accessor */
/** @addtogroup wms_qmi_accessor
    @{
  */
/** This function is used internally by the autogenerated code.  Clients should use the
   macro ql_ap_qmi_get_service_object_v01( ) that takes in no arguments. */
qmi_idl_service_object_type ql_ap_qmi_get_service_object_internal_v01
 ( int32_t idl_maj_version, int32_t idl_min_version, int32_t library_version );

/** This macro should be used to get the service object */
#define ql_ap_qmi_get_service_object_v01( ) \
          ql_ap_qmi_get_service_object_internal_v01( \
            QL_AP_QMI_V01_IDL_MAJOR_VERS, QL_AP_QMI_V01_IDL_MINOR_VERS, \
            QL_AP_QMI_V01_IDL_TOOL_VERS )
/**
    @}
  */


#ifdef __cplusplus
}
#endif
#endif

