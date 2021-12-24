/*
 *  Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
  @file v2x_kinematics_api.h

  @addtogroup v2x_api_kinematics
  Abstraction of the system GNSS + DR solution for returning precision fixes
  with low latency via callbacks. This solution is used each time a fix is
  available, and it supports multiple callbacks to a short list of clients.
 */

#ifndef __V2X_KINEMATICS_APIS_H__
#define __V2X_KINEMATICS_APIS_H__ 1

#include "v2x_common.pb.h"
#include "v2x_kinematics_data_types.pb.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup v2x_api_kinematics
@{ */

/** Kinematics data handle to the interface. */
typedef int v2x_kinematics_handle_t;

/** Invalid handle returned by v2x_kinematics_init() upon an error. */
#define V2X_KINEMATICS_HANDLE_BAD (-1)

/**
    User-defined callback function called upon completion of a
    v2x_kinematics_init() operation.

    @datatypes
    #v2x_status_enum_type

    @param[in] status   Status of the %v2x_kinematics_init() call.
    @param[in] context  Pointer to the application context from which
                        %v2x_kinematics_init() was called.

    @newpage
 */
typedef void (*v2x_kinematics_init_callback_t)(v2x_status_enum_type  status, void *context);

/**
    User-defined listener function called when a data rate is updated.

    @datatypes
    #v2x_status_enum_type \n
    #v2x_rates_t

    @param[in] status  Status of the rate change request.
    @param[in] rate    Pointer to the rate.
    @param[in] ctx     Pointer to the application context from which this
                       listener was registered.
 */
typedef void (*v2x_kinematics_rate_notification_listener_t)(v2x_status_enum_type  status, v2x_rates_t *rate,
        void *ctx);

/**
    User-defined callback function called upon completion of a
    v2x_kinematics_set_rate() operation.

    @datatypes
    #v2x_status_enum_type

    @param[in] status   Status of the %v2x_kinematics_set_rate() call.
    @param[in] context  Pointer to the application context from which
                        %v2x_kinematics_set_rate() was called.

    @newpage
 */
typedef void (*v2x_kinematics_set_rate_callback_t)(v2x_status_enum_type status, void *context);

/**
    User-defined callback function called upon completion of a
    v2x_kinematics_get_capabilities() operation.

    @datatypes
    #v2x_kinematics_capabilities_t

    @param[in] cap      Pointer to the capabilities supported by the API.
    @param[in] context  Pointer to the application context from which
                        %v2x_kinematics_get_capabilities() was called.
 */
typedef void (*v2x_kinematics_get_capability_callback_t)(v2x_kinematics_capabilities_t *cap, void *context);

/**
    User-defined listener function for kinematics data.

    @datatypes
    #v2x_location_fix_t

    @param[in] new_fix  Pointer to the data.
    @param[in] context  Pointer to the application context from which this
                        listener was registered.

    @newpage
 */
typedef void (*v2x_kinematics_newfix_listener_t)(v2x_location_fix_t *new_fix, void *context);

/**
    User-defined callback function called upon completion of a
    v2x_kinematics_deregister_listener() operation.

    @datatypes
    #v2x_status_enum_type

    @param[in] status   Status of the %v2x_kinematics_deregister_listener()
                        call.
    @param[in] context  Pointer to the application context from which
                        %v2x_kinematics_deregister_listener() was called.
 */
typedef void (*v2x_kinematics_deregister_callback_t)(v2x_status_enum_type status, void *context);

/**
    User-defined callback function called upon completion of a
    v2x_kinematics_final() operation.

    @datatypes
    #v2x_status_enum_type

    @param[in] status   Status of the %v2x_kinematics_final() call.
    @param[in] context  Pointer to the application context from which
                        %v2x_kinematics_final() was called.

    @newpage
 */
typedef void (*v2x_kinematics_final_callback_t)(v2x_status_enum_type status, void *context);

/**
    Gets the compiled API version interface (as an integer number).

    @return
    v2x_api_ver_t -- Filled with the version number, build date, and
    detailed build information.

    @newpage
 */
extern v2x_api_ver_t v2x_kinematics_api_version(void);

/**
    Initializes the Kinematics library.

    @datatypes
    #v2x_init_t \n
    #v2x_kinematics_init_callback_t

    @param[in] param    Pointer to the structure that contains parameters for
                        the IP address of the server, logging level, and so on.
    @param[in] cb       Callback function called when initialization is
                        complete.
    @param[in] context  Pointer to the application context for use with the
                        callbacks, which can help the caller code.

    @return
    Handle number to use with subsequent calls.
    @par
    #V2X_KINEMATICS_HANDLE_BAD -- Upon an error. @newpage
 */
extern v2x_kinematics_handle_t  v2x_kinematics_init(v2x_init_t *param, v2x_kinematics_init_callback_t cb,
        void *context);

/**
    Gets the current rate and offset from the Kinematics library.

    @datatypes
    #v2x_kinematics_handle_t \n
    #v2x_kinematics_rate_notification_listener_t

    @param[in] handle   Handle number to use with subsequent calls.
                        If there is an error in initialization, the value is -1.
    @param[in] cb       Callback function used to report rate notification
                        changes.
    @param[in] context  Pointer to the application context for use with the
                        callbacks, which can help the caller code.

    @return
    Indication of success or failure from #v2x_status_enum_type. @newpage
 */
extern v2x_status_enum_type v2x_kinematics_start_rate_notification(v2x_kinematics_handle_t handle,
        v2x_kinematics_rate_notification_listener_t cb,
        void *context);

/**
    Sets the current rate and offset from the Kinematics library.

    @datatypes
    #v2x_kinematics_handle_t \n
    #v2x_rates_t \n
    #v2x_kinematics_set_rate_callback_t

    @param[in] handle   Handle number to use with subsequent calls.
                        If there is an error in initialization, the value is -1.
    @param[in] rate     Pointer to the rate structure filled with the fix timing
                        parameters.
    @param[in] cb       Callback function called when rates and offsets are
                        successfully set. This parameter can be NULL.
    @param[in] context  Pointer to the application context for use with the
                        callbacks, which can help the caller code.

    @return
    Indication of success or failure from #v2x_status_enum_type. @newpage
 */
v2x_status_enum_type v2x_kinematics_set_rate(v2x_kinematics_handle_t handle, v2x_rates_t *rate,
        v2x_kinematics_set_rate_callback_t cb,
        void *context);
/** @} *//* end_addtogroup v2x_api_kinematics */

/** @ingroup v2x_deprecated_kinematics
    Obsolete. This function is not supported and will be removed in the future.

    Request from the API for the current capabilities. If DR is in use, the
    request includes supported rates, and so on.

    @datatypes
    #v2x_kinematics_handle_t \n
    #v2x_kinematics_get_capability_callback_t

    @param[in] handle   Handle number to use with subsequent calls.
                        If there is an error in initialization, the value is -1.
    @param[in] cb       Callback function called upon completion of the
                        request.
    @param[in] context  Pointer to the application context for use with the
                        callbacks, which can help the caller code.

    @return
    Indication of success or failure from #v2x_status_enum_type. @newpage
 */
v2x_status_enum_type v2x_kinematics_get_capabilities(v2x_kinematics_handle_t handle,
        v2x_kinematics_get_capability_callback_t cb,
        void *context);

/** @addtogroup v2x_api_kinematics
@{ */
/**
    Registers for a Kinematics result listener callback at the requested rate.

    @datatypes
    #v2x_kinematics_handle_t \n
    #v2x_kinematics_newfix_listener_t

    @param[in] handle    Handle number to use with subsequent calls.
                         If there is an error in initialization, the value
                         is -1.
    @param[in] listener  Callback function to use for this listener.
    @param[in] context   Pointer to the application context for use with the
                         callbacks, which can help the caller code.

    @detdesc
    This function requests GNSS fix/motion callbacks at a specified rate (Hz)
    with a specified offset.
    @par
    Only certain rates are supported (such as 1 Hz, 2 Hz, 5 Hz, 10 Hz), which 
    are obtained from v2x_kinematics_get_capabilities().
    @par
    Currently, a request cannot be made for a rate slower than 1 Hz.

    @return
    Indication of success or failure from #v2x_status_enum_type. @newpage
 */
v2x_status_enum_type v2x_kinematics_register_listener(v2x_kinematics_handle_t handle,
        v2x_kinematics_newfix_listener_t listener, void *context);

/**
    Deregisters a previously registered GNSS fix that the listener established
    earlier via v2x_kinematics_register_listener().

    @datatypes
    #v2x_kinematics_handle_t \n
    #v2x_kinematics_deregister_callback_t

    @param[in] handle   Handle number of the registered fix.
    @param[in] cb       Callback function to use for this listener.
                        This parameter can be NULL.
    @param[in] context  Pointer to the application context for use with the
                        callbacks, which can help the caller code.

    @return
    Indication of success or failure from #v2x_status_enum_type. @newpage
 */
v2x_status_enum_type v2x_kinematics_deregister_listener(v2x_kinematics_handle_t handle, v2x_kinematics_deregister_callback_t cb,
        void *context);

/**
    Terminates the Kinematics library.

    @datatypes
    #v2x_kinematics_handle_t \n
    #v2x_kinematics_final_callback_t

    @param[in] handle   Handle number of the library.
    @param[in] cb       Callback function called when termination is complete.
                        This parameter can be NULL.
    @param[in] context  Pointer to the application context for use with the
                        callbacks, which can help the caller code.

    @return
    Indication of success or failure from #v2x_status_enum_type. @newpage
 */
v2x_status_enum_type v2x_kinematics_final(v2x_kinematics_handle_t handle, v2x_kinematics_final_callback_t cb,
        void *context);

/**
    Enables the Kinematics fixes from GNSS.

    @datatypes
    #v2x_kinematics_handle_t

    @param[in] handle  Unique identifier for the library.

    @return
    None.
 */
void v2x_kinematics_enable_fixes(v2x_kinematics_handle_t handle);

/**
    Disables the Kinematics fixes from GNSS.

    @datatypes
    #v2x_kinematics_handle_t

    @param[in] handle  Unique identifier for the library.

    @return
    None. @newpage
 */
void v2x_kinematics_disable_fixes(v2x_kinematics_handle_t handle);

/** @} *//* end_addtogroup v2x_api_kinematics */

#ifdef __cplusplus
}
#endif

#endif // __V2X_KINEMATICS_APIS_H__
