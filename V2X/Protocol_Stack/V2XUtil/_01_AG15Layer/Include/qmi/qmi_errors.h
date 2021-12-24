//=============================================================================
// FILE: qmi_errors.h
//
// SERVICES: QMI
//
// DESCRIPTION: defines QMI errors codes and related functions
//   
// AUTHORS:
//
// Copyright (c) 2012-2013 Qualcomm Technologies, Inc. All Rights Reserved.
// Qualcomm Technologies Proprietary and Confidential.
//=============================================================================

//=============================================================================
// CONSTANTS
//=============================================================================

#include "../../../_01_AG15Layer/Include/qmi/common_v01.h"
#include "../../../_01_AG15Layer/Include/qmi/qmi.h"
#include "../../../_01_AG15Layer/Include/qmi-framework/qmi_idl_lib.h"

//=============================================================================
// FUNCTION PROTOTYPES
//=============================================================================
#ifdef __cplusplus
extern "C" {
#endif

/// Converts qmi lib errors to a debug string
const char* qmi_errstr(int qmi_error); 

/// Converts qmi service errors to a debug string
const char* qmisvc_errstr(int qmi_error);

#ifdef __cplusplus
}
#endif
