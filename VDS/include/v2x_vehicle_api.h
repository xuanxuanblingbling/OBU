/*
 *  Copyright (c) 2017, 2019 Qualcomm Technologies, Inc.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
  @file v2x_vehicle_api.h

  @addtogroup v2x_api_vehicle
  Abstraction of the vehicle system parameters required for CAM/BSM ITS
  beacons.
 */

#ifndef __V2X_VEHICLE_APIS_H__
#define __V2X_VEHICLE_APIS_H__

#include "v2x_common.pb.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup v2x_api_vehicle
@{ */

/** Vehicle data handle to the interface */
typedef int v2x_vehicle_handle_t;

/** Vehicle high-resolution motion handle to the interface */
typedef int v2x_motion_data_handle_t;

/** Invalid handle returned when there is an error. */
#define V2X_VDATA_HANDLE_BAD (-1)

/**
    Valid types for main transmission drive states.
 */
typedef enum {
    V2X_TRANSMISSION_NEUTRAL = 0,
    V2X_TRANSMISSION_PARK = 1,
    V2X_TRANSMISSION_FORWARD_GEARS = 2,  /**< One of the gears:
                                              D, 1, 2, 3, ... . */
    V2X_TRANSMISSION_REVERSE_GEARS = 3,
    V2X_TRANSMISSION_RESERVED1 = 4,
    V2X_TRANSMISSION_RESERVED2 = 5,
    V2X_TRANSMISSION_RESERVED3 = 6,
    V2X_TRANSMISSION_UNAVAILABLE = 7,    /**< Status is unknown. */
    V2X_TRANSMISSION_MAX                 /**< Sentry variable that must not be
                                              exceeded.*/
} v2x_transmission_state_enum_type;

/** Guard check value on #v2x_transmission_state_enum_type for
    #V2X_TRANSMISSION_MAX. This value is used in a 3-bit bitfield in J2735.
 */
#define V2X_J2735_TRACTION_CONTROL_MAX (4)

/**
    Valid types for brake boosting states.
 */
typedef enum {
    V2X_BRAKEBOOST_UNAVAIL = 0,  /**< Status is unknown. */
    V2X_BRAKEBOOST_OFF = 1,
    V2X_BRAKEBOOST_ON = 2,
    V2X_BRAKEBOOST_MAX           /**< Sentry variable that must not be
                                      exceeded.*/
} v2x_BrakeBoostApplied_enum_type;

/**
    Valid types for traction control states.

    This enumeration currently matches the J2735 2016 version for the Traction
    Control System (TCS).
 */
typedef enum {
    V2X_TRACTION_CTRL_UNAVAIL = 0,  /**< Status is unknown. */
    V2X_TRACTION_CTRL_OFF = 1,
    V2X_TRACTION_CTRL_ON = 2,       /**< On but currently not engaged. */
    V2X_TRACTION_CTRL_ENGAGED = 3   /**< Actively being engaged. @newpage */
} v2x_TractionControlStatus_enum_type;

/** Guard check value on #v2x_TractionControlStatus_enum_type for
    #V2X_TRACTION_CTRL_MAX. This value is used in a 2-bit bitfield in J2735.
 */
#define V2X_TRACTION_CTRL_MAX (4)

/**
    Valid types for antilock-braking states.

    This enumeration matches the J2735 2016 version for the Antilock Braking
    System (ABS) to help BSM packing and unpacking.
 */
typedef enum {
    V2X_ABS_Unavailable = 0,  /**< ABS is not equipped, or the status is
                                   unknown. */
    V2X_ABS_Off = 1,
    V2X_ABS_On = 2,           /**< On but currently not active. */
    V2X_ABS_Engaged = 3       /**< Actively being engaged on one or more
                                   wheels. */
} v2x_AntiLockBrakeStatus_enum_type;

/** Guard check value on #v2x_AntiLockBrakeStatus_enum_type.

    This value cannot be part of the enumeration because the value eventually
    ends up in 2-bit bitfield over the air.
 */
#define J2735_ABS_MAX (4)

/**
    Valid types for the stability control status. This enumeration should be
    equivalent to the J2735 BSM version you are working with.
 */
typedef enum {
    V2X_STABILITY_CONTROL_UNAVAILBLE = 0, /**< Stability Control status is
                                               unknown. */
    V2X_STABILITY_CONTROL_OFF = 1,        /**< Stability Control is not
                                               applied. */
    V2X_STABILITY_CONTROL_ON = 2,         /**< Stability Control is on, but
                                               currently it is not engaged. */
    V2X_STABILITY_CONTROL_ENGAGED = 3     /**< Stability Control is actively
                                               being engaged. */
} v2x_StabilityControlStatus_enum_type;

/** Guard check value on #v2x_StabilityControlStatus_enum_type.

    This value is eventually used over the air in a 2-bit bitfield. The
    enumeration value must never be larger than 4.
 */
#define V2X_STABILITY_CONTROL_MAX (4)

/**
    Valid types for the auxiliary brake status.

    This enumeration should match the J2735 2016 version or any other version
    you are working with.
 */
typedef enum {
    V2X_AUX_BRAKE_UNAVAILBLE = 0,  /**< Vehicle has no auxiliary brake
                                        equipment or the status is unknown. */
    V2X_AUX_BRAKE_OFF = 1,
    V2X_AUX_BRAKE_ON = 2,
    V2X_AUX_BRAKE_RESERVED = 3     /**< @newpage */
} v2x_AuxBrakeStatus_enum_type;

/** Guard check value on #v2x_AuxBrakeStatus_enum_type. This value must
    never be set this high. @newpage
 */
#define V2X_AUX_BRAKE_MAX (4)

/**
    Contains information related to ABS, TCS, stability control state, and
    other vehicle output controls that might occur and be ongoing.
    This structure mirrors the J2735 bit frames.
 */
typedef union {
    /** Bit values for control status information.
    */
    struct {
        unsigned unused_padding                                 : 1;
        /**< Reserved for 16-bit alignment.

             This field is critical because of 16-bit word access to the packed
             v2x_control_status_ut union structure. */

        v2x_AuxBrakeStatus_enum_type aux_brake_status                   : 2;
        /**< Indicates whether the auxiliary braking system is on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        v2x_BrakeBoostApplied_enum_type brake_boost_applied             : 2;
        /**< Indicates whether the brakes are actively being boosted.

             @values
             - 0 -- Not boosted
             - 1 -- Boosted @tablebulletend */

        v2x_StabilityControlStatus_enum_type stability_control_status   : 2;
        /**< Indicates whether stability control is on and engaged.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        v2x_AntiLockBrakeStatus_enum_type antilock_brake_status         : 2;
        /**< Indicates the status of the ABS. */

        v2x_TractionControlStatus_enum_type traction_control_status     : 2;
        /**< Indicates whether status of the TCS. */

        unsigned rightRear                                      : 1;
        /**< Indicates whether the right rear brakes are actively being
             applied.

             @values
             - 0 -- Not applied
             - 1 -- Applied @tablebulletend */

        unsigned rightFront                                     : 1;
        /**< Indicates whether the right front brakes are actively being
             applied.

             @values
             - 0 -- Not applied
             - 1 -- Applied @tablebulletend */

        unsigned leftRear                                       : 1;
        /**< Indicates whether the left rear brakes are actively being
             applied

             @values
             - 0 -- Not applied
             - 1 -- Applied @tablebulletend */

        unsigned leftFront                                      : 1;
        /**< Indicates whether the front left brakes are actively being
             applied.

             @values
             - 0 -- Not applied
             - 1 -- Applied @tablebulletend */

        unsigned unavailable                                    : 1;
        /**< No information is available. */

    } bits; /**< Bit values for control status information. */

    unsigned short word;
    /**< Byte data access to the packed v2x_control_status union structure. */

} v2x_control_status_ut;

/**
    Contains critical events and communication of ongoing events. Also is used
    for combinations of critical and not critical (wipers) events

    This typedef can match the J2735 2016 version or another version you are
    working with.
 */
typedef union {

    /** Bit values for vehicle event flags. A flag indicates the state
        of the event.
    */
    struct {
        unsigned unused                         : 3;
        /**< Reserved for 16-bit alignment in the union access. */

        unsigned eventAirBagDeployment          : 1;
        /**< Indicates whether the airbag is deployed.

             @values
             - 0 -- Not deployed
             - 1 -- Deployed @tablebulletend */

        unsigned eventDisabledVehicle           : 1;
        /**< Indicates whether the vehicle is disabled.

             @values
             - 0 -- Not disabled
             - 1 -- Disabled @tablebulletend */

        unsigned eventFlatTire                  : 1;
        /**< Indicates whether the tire is flat.

             @values
             - 0 -- Not flat
             - 1 -- Flat @tablebulletend */

        unsigned eventWipersChanged             : 1;
        /**< Indicates the status of the windshield wipers. For more
             information, See the wiper state variables in
             current_dynamic_vehicle_state_t. */

        unsigned eventLightsChanged             : 1;
        /**< Indicates the status of one or more lights (such as blinkers and
             fog). */

        unsigned eventHardBraking              : 1;
        /**< Indicates whether hard braking is activated.

             @values
             - 0 -- Not activated
             - 1 -- Activated @tablebulletend */

        unsigned eventReserved1                 : 1;
        /**< Event bit reserved for future use. Do not use. */

        unsigned eventHazardousMaterials        : 1;
        /**< Indicates whether a hazmat load is present.

             @values
             - 0 -- Not present
             - 1 -- Present @tablebulletend */

        unsigned eventStabilityControlactivated : 1;
        /**< Indicates whether stability control is on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        unsigned eventTractionControlLoss       : 1;
        /**< Indicates whether traction control is activated (1) or not (0).

             @values
             - 0 -- Not applied
             - 1 -- Applied @tablebulletend */

        unsigned eventABSactivated              : 1;
        /**< Indicates whether ABS is activated.

             @values
             - 0 -- Not activated
             - 1 -- Activated @tablebulletend */

        unsigned eventStopLineViolation         : 1;
        /**< Indicates whether the vehicle has detected that a violation of the
             Stop Line is imminent.

             @values
             - 0 -- Not imminent
             - 1 -- Imminent @tablebulletend */

        unsigned eventHazardLights              : 1;
        /**< Indicates whether the hazard lights are on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

    }  bits; /**< Bit values for vehicle event flags. */

    unsigned short  data;
    /**< Sixteen-bit word access to the packed vehicleEventFlags union
         structure. @newpagetable */

} vehicleEventFlags_ut;

/**
    Contains information about the state of the exterior lights.
 */
typedef union {

    /** Bit values for exterior light flags.
    */
    struct {
        //-- All lights off is indicated by no bits set

        unsigned parkingLightsOn           : 1;
        /**< Indicates whether the parking lights are on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        unsigned fogLightOn                : 1;
        /**< Indicates whether the fog lights are on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        unsigned daytimeRunningLightsOn    : 1;
        /**< Indicates whether the running lights are on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        unsigned automaticLightControlOn   : 1;
        /**< Indicates whether the automatic light control is on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        unsigned hazardSignalOn            : 1;
        /**< Indicates whether the hazard lights are on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        unsigned rightTurnSignalOn         : 1;
        /**< Indicates whether the right turn light is on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        unsigned leftTurnSignalOn          : 1;
        /**< Indicates whether the left turn light is on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        unsigned highBeamHeadlightsOn      : 1;
        /**< Indicates whether the high beam headlights are on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        unsigned lowBeamHeadlightsOn       : 1;
        /**< Indicates whether the low beam headlights are on.

             @values
             - 0 -- Off
             - 1 -- On @tablebulletend */

        unsigned unused                    : 7;
        /**< Unused padding bits. */

    }  bits; /**< Bit values for exterior light flags. */

    unsigned  short data;
    /**< 16-bit short word access to the packed ExteriorLights union structure. */

    /*Useful as a union, since structure matches J2735 encoding */
} ExteriorLights_ut;

/**
    Contains high-resolution motion parameters.
 */
typedef struct {
    double vehicle_speed;
    /**< Vehicle speed in meters/second. */

    double longitudinal_acceleration;
    /**< Acceleration in a longitudinal direction, in meters/second^2. */

    double yaw_rate;
    /**< Yaw rate in degrees/second, per SAE J2735. */

} high_resolution_motion_t;

/**
    Contains information about the dynamic state of the vehicle.
 */
typedef struct {
    v2x_transmission_state_enum_type prndl;
    /**< Specifies the current state of the transmission gear: forward,
         reverse, and so on. */

    vehicleEventFlags_ut events;
    /**< Flags all critical events and combinations of critical events. */

    double throttle_position;
    /**< Per the J2735 definition, indicates the throttle position from 0% to
         100%. However, this value is in double precision between 0 and 1. */

    double throttle_confidence;
    /**< Per the J2735 definition, double precision degrees of confidence. */

    double steering_wheel_angle;
    /**< Per the J2735 definition, double precision degrees of the wheel
         angle.

         @values -192.0 through 189.0 degrees, with positive being turned to
                 the right */

    v2x_control_status_ut brake_status;
    /**< Indicates whether brakes or emergency brakes (ABS) are activated.

         @values
         - 0 -- Not activated
         - 1 -- Activated @tablebulletend */

    ExteriorLights_ut exterior_lights;
    /**< Conglomeration of bits that indicate the status of the exterior
         lights, such as blinkers. */

    unsigned char front_wiper_status;
    /**< Status of the front windshield wipers. */

    unsigned char rear_wiper_status;
    /**< Status of the rear windshield wipers. */

} current_dynamic_vehicle_state_t;

/**
    Contains static vehicle parameters.
 */
typedef struct {
    double vehicle_height_cm;
    /**< Vehicle height in centimeters.

         This parameter is 0 if the value is not yet available from the
         vehicle network. */

    double vehicle_width_cm;
    /**< Vehicle width in centimeters.

         This parameter is 0 if the value is not yet available from the
         vehicle network. */

    double vehicle_length_cm;
    /**< Vehicle length in centimeters.

         This parameter is 0 if the value is not yet available from the
         vehicle network. */

    double front_bumper_height_cm;
    /**< Height of the front bumper, in centimeters.

         This parameter is 0 if the value is not yet available from the
         vehicle network. */

    double rear_bumper_height_cm;
    /**< Height of the rear bumper, in centimeters.

         This parameter is 0 if the value is not yet available from the
         vehicle network. */

    double vehicle_mass_kg;
    /**< Mass of the vehicle, in kilograms.

         This parameter is 0 if the value is not yet available from the
         vehicle network. */

    double trailer_weight_kg;
    /**< Weight of a trailer connected to the vehicle, in kilograms.

         This parameter is 0 if the value is not yet available from the
         vehicle network. */

    char *make;
    /**< Pointer to the NULL-terminated string with the vehicle manufacturer
         that this software build supports (such as Ford and GM). */

    char *model;
    /**< Pointer to the NULL-terminated string with the vehicle model name that
         this software build supports (such as Prius, Mustang, Rogue). */

    unsigned short begin_model_year;
    /**< Beginning of the model years that this software build supports. */

    unsigned short end_model_year;
    /**< End of model year that this software build supports. This year might
         be the same as begin_model_year. @newpagetable */

} static_vehicle_parameters_t;

/**
    Gets the compiled API version interface (as an integer number).

    @return
    v2x_api_ver_t -- Filled with the version number, build date, and
    detailed build information.
 */
extern v2x_api_ver_t v2x_vehicle_api_version(void);

/**
    Returns (via a reference pointer) the static_vehicle_parameters_t structure
    that enumerates static (unchanging) data items used by ITS stacks.

    @datatypes
    #static_vehicle_parameters_t

    @param[out] parameters  Pointer to the static vehicle parameters, including
                            vehicle dimensions, make, model, and so on.

    @detdesc
    This call is a nonblocking call. If the values are not yet available from
    the vehicle, the data element is 0 (NULL).
    @par
    Because this function is sometimes populated with data from an in-vehicle
    network, it might be incomplete and only partially populated early in a
    system start-up. However, all values can be statically compiled in or
    loaded from an initialization file. In this case, the data is fully
    provided on the first call.

    @return
    #V2X_STATUS_SUCCESS -- This function is successfully populated with the
    results.
    @par
    Error code -- If there is a problem (see #v2x_status_enum_type). @newpage
 */
v2x_status_enum_type v2x_vehicle_get_static_params(static_vehicle_parameters_t *parameters);

/**
    Callback used for high resolution motion data.

    @datatypes
    #high_resolution_motion_t

    @param[in] motion_data  Pointer to the dynamic state of the vehicle.
 */
typedef void (* v2x_high_res_motion_listener_t)(high_resolution_motion_t *motion_data);

/**
    Registers for high-resolution motion callbacks from the vehicle data
    network (CAN bus) when the data changes.

    @datatypes
    #v2x_high_res_motion_listener_t

    @param[in] cb  Callback function to use for this listener.

    @return
    Handle number to use with subsequent deregister calls.
    @par
    -1 -- If there is an error in registering a callback.
 */
v2x_motion_data_handle_t v2x_high_res_motion_register_listener(v2x_high_res_motion_listener_t cb);

/**
    Deregisters a previously registered high-resolution motion data callback
    that was requested via v2x_high_res_motion_register_listener().

    @datatypes
    #v2x_motion_data_handle_t

    @param[in] handle  Handle of the listener callback previously set up.

    @return
    #V2X_STATUS_SUCCESS.

    @dependencies
    The callback must have been previously registered with
    v2x_high_res_motion_register_listener(). @newpage
 */
v2x_status_enum_type v2x_high_res_motion_deregister_listener(v2x_motion_data_handle_t handle);

/**
    Callback used for critical event notification and other less critical
    events.

    @datatypes
    #current_dynamic_vehicle_state_t

    @param[in] current_state  Pointer to the dynamic state of the vehicle.
    @param[in] context        Pointer to the application context used with the
                              callbacks to help the caller code.

    @newpage
 */
typedef void (* v2x_vehicle_event_listener_t)(current_dynamic_vehicle_state_t *current_state, void *context);

/**
    Registers for a callback for state updates from the vehicle data network
    (CAN bus). This function requests vehicle data callbacks when data changes
    or events occur.

    @datatypes
    #v2x_vehicle_event_listener_t

    @param[in] cb       Callback function to use for this listener.
    @param[in] context  Pointer to the application context for use with the
                        callbacks, which can help the caller code.

    @return
    Handle number to use with subsequent deregister calls.
    @par
    -1 -- If there is an error in registering a callback.
 */
v2x_vehicle_handle_t v2x_vehicle_register_listener(v2x_vehicle_event_listener_t cb, void *context);

/**
    Deregisters a previously registered dynamic event callback that was
    requested via v2x_vehicle_register_listener().

    @datatypes
    #v2x_vehicle_handle_t

    @param[in] handle  Handle of the listener callback previously set up.

    @return
    #V2X_STATUS_SUCCESS -- If the callback is successfully deregistered.

    @dependencies
    The callback must have been previously registered. @newpage
 */
v2x_status_enum_type v2x_vehicle_deregister_for_callback(v2x_vehicle_handle_t handle);

/** @} *//* end_addtogroup v2x_api_vehicle */

#ifdef __cplusplus
}
#endif

#endif // __V2X_VEHICLE_APIS_H__
