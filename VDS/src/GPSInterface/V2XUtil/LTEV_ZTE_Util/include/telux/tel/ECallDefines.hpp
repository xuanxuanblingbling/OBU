/*
 *  Copyright (c) 2017-2019, The Linux Foundation. All rights reserved.
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
 * @file      ECallDefines.hpp
 * @brief     ECallDefines contains enumerations and variables used for
 *            telephony subsystems.
 */
#ifndef ECALLDEFINES_HPP
#define ECALLDEFINES_HPP

#include <string>

namespace telux {

namespace tel {

/** @addtogroup telematics_phone
 * @{ */

/**
 * ECall Variant
 */
enum class ECallVariant {
   ECALL_TEST = 1,      /**< Initiate a test voice eCall with a configured telephone number stored
                           in the USIM. */
   ECALL_EMERGENCY = 2, /**< Initiate an emergency eCall. The trigger can be a manually initiated
                           eCall or automatically initiated eCall. */
   ECALL_VOICE = 4,     /**< Initiate a regular voice call with capability to transfer an MSD. */
};

/**
 * Emergency Call Type
 */
enum class EmergencyCallType {
   CALL_TYPE_ECALL = 12, /**<  eCall (0x0C) */
};

/**
 * MSD Transmission Status
 */
enum class ECallMsdTransmissionStatus {
   SUCCESS = 0,                  /**< Success */
   FAILURE = 1,                  /**< Generic failure */
   MSD_TRANSMISSION_STARTED = 2, /**< MSD Transmission Started */
   NACK_OUT_OF_ORDER = 3,        /**< Out of order NACK message
                                 detected */
   ACK_OUT_OF_ORDER = 4,         /**< Out of order ACK message
                                 detected */
};

/**
 * ECall category
 */
enum class ECallCategory {
   VOICE_EMER_CAT_AUTO_ECALL = 64, /**< Automatic emergency call */
   VOICE_EMER_CAT_MANUAL = 32,     /**< Manual emergency call */
};

/**
 * Represents a vehicle class as per European eCall MSD standard. i.e. EN 15722.
 */
enum ECallVehicleType {
   PASSENGER_VEHICLE_CLASS_M1,
   BUSES_AND_COACHES_CLASS_M2,
   BUSES_AND_COACHES_CLASS_M3,
   LIGHT_COMMERCIAL_VEHICLES_CLASS_N1,
   HEAVY_DUTY_VEHICLES_CLASS_N2,
   HEAVY_DUTY_VEHICLES_CLASS_N3,
   MOTOR_CYCLES_CLASS_L1E,
   MOTOR_CYCLES_CLASS_L2E,
   MOTOR_CYCLES_CLASS_L3E,
   MOTOR_CYCLES_CLASS_L4E,
   MOTOR_CYCLES_CLASS_L5E,
   MOTOR_CYCLES_CLASS_L6E,
   MOTOR_CYCLES_CLASS_L7E,
};

/**
 * Represents OptionalDataType class as per European eCall MSD standard. i.e. EN 15722.
 */
enum class ECallOptionalDataType {
   ECALL_DEFAULT,
};

/**
 * Represents MsdOptionals class as per European eCall MSD standard. i.e. EN 15722.
 */
struct ECallMsdOptionals {

   ECallOptionalDataType optionalDataType; /**< Type of optional data */
   bool optionalDataPresent;               /**< Availability of Optional data:
                                                  true - Present or false - Absent */
   bool recentVehicleLocationN1Present;    /**< Availability of Recent Vehicle Location N1 data:
                                                  true - Present or false - Absent*/
   bool recentVehicleLocationN2Present;    /**< Availability of Recent Vehicle Location N2 data:
                                                  true - Present or false - Absent */
   bool numberOfPassengersPresent;         /**< Availability of number of seat belts fastened data:
                                                  true - Present or false - Absent*/
};

/**
 * Represents ECallMsdControlBits structure as per European eCall MSD standard. i.e. EN 15722.
 */
struct ECallMsdControlBits {
   bool automaticActivation;  /**< auto / manual activation */
   bool testCall;             /**< test / emergency call */
   bool positionCanBeTrusted; /**< false if coincidence < 95% of reported pos within +/- 150m */
   ECallVehicleType vehicleType : 5; /**< Represents a vehicle class as per EN 15722 */
};

/**
 * Represents VehicleIdentificationNumber structure as per European eCall MSD standard.
 * i.e. EN 15722. Vehicle Identification Number confirming ISO3779.
 */
struct ECallVehicleIdentificationNumber {
   std::string isowmi;          /**< World Manufacturer Index (WMI) */
   std::string isovds;          /**< Vehicle Type Descriptor (VDS) */
   std::string isovisModelyear; /**< Model year from Vehicle Identifier Section (VIS) */
   std::string isovisSeqPlant;  /**< Plant code + sequential number from VIS */
};

/**
 * Represents VehiclePropulsionStorageType structure as per European eCall MSD standard.
 * i.e. EN 15722. Vehicle Propulsion type (energy storage):  True- Present, False - Absent
 */
struct ECallVehiclePropulsionStorageType {
   bool gasolineTankPresent;  /**< Represents the presence of Gasoline Tank in the vehicle. */
   bool dieselTankPresent;    /**< Represents the presence of Diesel Tank in the vehicle   */
   bool compressedNaturalGas; /**< Represents the presence of CNG in the vehicle   */
   bool liquidPropaneGas;     /**< Represents the presence of Liquid Propane Gas in the vehicle   */
   bool electricEnergyStorage; /**< Represents the presence of Electronic Storage in the vehicle */
   bool hydrogenStorage;       /**< Represents the presence of Hydrogen Storage in the vehicle   */
   bool otherStorage; /**< Represents the presence of Other types of storage in the vehicle   */
};

/**
 * Represents VehicleLocation structure as per European eCall MSD standard. i.e. EN 15722.
 */
struct ECallVehicleLocation {
   int32_t positionLatitude; /**< latitude in value range (-2147483648 to 2147483647) */
   int32_t positionLongitude;
};

/**
 * Represents VehicleLocationDelta structure as per European eCall MSD standard. i.e. EN 15722.
 * Delta with respect to Current Vehicle location.
 */
struct ECallVehicleLocationDelta {
   int16_t latitudeDelta;  /**<  ( 1 Unit = 100 milliarcseconds, range: -512 to 511) */
   int16_t longitudeDelta; /**<  ( 1 Unit = 100 milliarcseconds, range: -512 to 511) */
};

///@cond DEV
struct ECallObjectId {
   uint8_t id1 : 4;
   uint8_t id2 : 4;
   uint16_t id3 : 14;
   uint16_t id4 : 14;
   uint16_t id5 : 14;
   uint16_t id6 : 14;
   uint16_t id7 : 14;
   uint16_t id8 : 14;
   uint16_t id9 : 14;
};

struct ECallDefaultOptions {
   ECallObjectId objId;      /**< OBJECT IDENTIFIER data type according to ASN.1 specification */
   std::string optionalData; /**< Optional Data */
};
/// @endcond

/**
 * Optional information for the emergency rescue service.
 */
struct ECallOptionalPdu {
   ECallDefaultOptions eCallDefaultOptions; /**< Optional information */
};

/**
 * Data structure to hold all details required to construct an MSD
 */
struct ECallMsdData {
   ECallMsdOptionals optionals; /**< Indicates presence of optionals in ECall MSD */
   uint8_t messageIdentifier;   /**< Starts with 1 for each new , increment on retransmission */
   ECallMsdControlBits control; /**< ECallMsdControlBits structure as per European standard i.e. EN
                                   15722 */
   ECallVehicleIdentificationNumber vehicleIdentificationNumber; /**< VIN (vehicle identification
                                                                    number) according to ISO3779 */
   ECallVehiclePropulsionStorageType vehiclePropulsionStorage;   /**< VehiclePropulsionStorageType
                                                                    structure as per European standard
                                                                    i.e. EN 15722 */
   uint32_t timestamp;                   /**< Seconds elapsed since midnight 01.01.1970 UTC */
   ECallVehicleLocation vehicleLocation; /**< VehicleLocation structure as per European standard.
                                            i.e. EN 15722 */
   uint8_t vehicleDirection; /**< Direction of travel in 2 degrees steps from magnetic north */

   // The following fields are optional
   ECallVehicleLocationDelta recentVehicleLocationN1; /**< Change in latitude and longitude compared
                                                         to the last MSD transmission */
   ECallVehicleLocationDelta recentVehicleLocationN2; /**< Change in latitude and longitude compared
                                                         to the last but one MSD transmission */
   uint8_t numberOfPassengers;                        /**< Number of occupants in the vehicle */
   /** Optional information for the emergency rescue service
    * (103 bytes, ASN.1 encoded); may also point to an address, where this information is located
    */
   ECallOptionalPdu optionalPdu; /**< Optional information for the emergency rescue service */
};

/**
 * Represents eCall operating mode
 */
enum class ECallMode {
   NORMAL = 0,     /**< eCall and normal voice calls are allowed */
   ECALL_ONLY = 1, /**< Only eCall is allowed */
   NONE = 2,       /**< Invalid mode */
};

/**
 * Represents eCall operating mode change reason
 */
enum class ECallModeReason {
   NORMAL = 0,      /**< eCall operating mode changed due to normal operation like
                        setting of eCall mode */
   ERA_GLONASS = 1, /**< eCall operating mode changed due to ERA-GLONASS operation */
};

/**
 *  Represents eCall operating mode information
 */
struct ECallModeInfo {
   ECallMode mode;         /**< Represents eCall operating mode */
   ECallModeReason reason; /**< Represents eCall operating mode change reason */
};
/** @} */ /* end_addtogroup telematics_phone */

}  // End of namespace tel

}  // End of namespace telux

#endif  // ECALLDEFINES_HPP
