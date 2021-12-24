/*
 *  Copyright (c) 2019 The Linux Foundation. All rights reserved.
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
 * @file       ThermalManager.hpp
 *
 * @brief      Thermal Manager is a primary interface for thermal zones (sensors) and
 *             thermal cooling devices to get list of sensor temperature readings,
 *             trip point information.
 *
 * @note       Eval: This is a new API and is being evaluated. It is subject to
 *             change and could break backwards compatibility.
 */

#ifndef THERMALMANAGER_HPP
#define THERMALMANAGER_HPP

#include <vector>
#include <string>
#include <memory>

namespace telux {
namespace therm {

/** @addtogroup telematics_therm
 * @{ */

class IThermalZone;
class ICoolingDevice;
class ITripPoint;

/**
 * Defines the type of trip points, it can be one of the values for
 * ACPI (Advanced Configuration and Power Interface) thermal zone
 */
enum class TripType {
   UNKNOWN,           /**< Trip type is unknown */
   CRITICAL,          /**< Trip point at which system shuts down */
   HOT,               /**< Trip point to notify emergency */
   PASSIVE,           /**< Trip point at which kernel lowers the CPU's frequency and throttle
                           the processor down */
   ACTIVE,            /**< Trip point at which processor fan turns on */
   CONFIGURABLE_HIGH, /**< Triggering threshold at which mitigation starts.
                           This type is added to support legacy targets*/
   CONFIGURABLE_LOW   /**< Clearing threshold at which mitigation stops.
                           This type is added to support legacy targets*/
};

/**
 * Defines the trip points to which cooling device is bound.
 */
struct BoundCoolingDevice {
   int coolingDeviceId; /**< Cooling device Id associated with trip points */
   std::vector<std::shared_ptr<ITripPoint>> bindingInfo; /**< List of trippoints bound to the
                                                               cooling device */
};

/**
 * @brief   IThermalManager provides interface to get thermal zone and cooling device information.
 *
 * @note    Eval: This is a new API and is being evaluated. It is subject to change and could break
 *          backwards compatibility.
 */
class IThermalManager {
public:
   /**
    * Retrieves the list of thermal zone info like type, temperature and trip points.
    *
    * @returns List of thermal zones.
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual std::vector<std::shared_ptr<IThermalZone>> getThermalZones() = 0;

   /**
    * Retrieves the list of thermal cooling device info like type, maximum throttle state and
    * currently requested throttle state.
    *
    * @returns List of cooling devices.
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual std::vector<std::shared_ptr<ICoolingDevice>> getCoolingDevices() = 0;

   /**
    * Retrieves the thermal zone details like temperature, type and trip point info
    * for the given thermal zone identifier.
    *
    * @param [in] thermalZoneId     Thermal zone identifier
    *
    * @returns Pointer to thermal zone.
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual std::shared_ptr<IThermalZone> getThermalZone(int thermalZoneId) = 0;

   /**
    * Retrieves the cooling device details like type of the device, maximum cooling level and
    * current cooling level for the given cooling device identifier.
    *
    * @param [in] coolingDeviceId     Cooling device identifier
    *
    * @returns Pointer to cooling device.
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual std::shared_ptr<ICoolingDevice> getCoolingDevice(int coolingDeviceId) = 0;

   /**
    * Destructor of IThermalManager
    */
   virtual ~IThermalManager(){};
};

/**
 * @brief   ITripPoint provides interface to get trip point type, trip point temperature
 *          and hysteresis value for that trip point.
 *
 * @note    Eval: This is a new API and is being evaluated. It is subject to change and could break
 *          backwards compatibility.
 */
class ITripPoint {
public:
   /**
    * Retrieves trip point type.
    *
    * @returns Type of trip point if available else return UNKNOWN.
    *          - @ref TripType
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual TripType getType() = 0;

   /**
    * Retrieves the temperature above which certain trip point will be fired.
    *        - Units: MilliDegree Celsius
    *
    * @returns Threshold temperature
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual int getThresholdTemp() = 0;

   /**
    * Retrieves hysteresis value that is the difference between current temperature of the device
    * and the temperature above which certain trip point will be fired. Units: MilliDegree Celsius
    *
    * @returns Hysteresis value
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual int getHysteresis() = 0;

   /**
    * Destructor of ITripPoint
    */
   virtual ~ITripPoint(){};
};

/**
 * @brief   IThermalZone provides interface to get type of the sensor, the current temperature
 *          reading, trip points and the cooling devices binded etc.
 *
 * @note    Eval: This is a new API and is being evaluated. It is subject to change and could break
 *          backwards compatibility.
 */
class IThermalZone {
public:
   /**
    * Retrieves the identifier for thermal zone.
    *
    * @returns Identifier for thermal zone
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual int getId() = 0;

   /**
    * Retrieves the type of sensor.
    *
    * @returns Sensor type
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual std::string getDescription() = 0;

   /**
    * Retrieves the current temperature of the device. Units: MilliDegree Celsius
    *
    * @returns Current temperature
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual int getCurrentTemp() = 0;

   /**
    * Retrieves the temperature of passive trip point for the zone. Default value is 0.
    *  Valid values: 0 (disabled) or greater than 1000 (enabled), Units: MilliDegree Celsius
    *
    * @returns Temperature of passive trip point
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual int getPassiveTemp() = 0;

   /**
    * Retrieves trip point information like trip type, trip temperature and hysteresis.
    *
    * @returns Trip point info list
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual std::vector<std::shared_ptr<ITripPoint>> getTripPoints() = 0;

   /**
    * Retrieves the list of cooling device and the associated trip points bound to cooling device
    * in given thermal zone.
    *
    * @returns  List of bound cooling device for the given thermal zone.
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual std::vector<BoundCoolingDevice> getBoundCoolingDevices() = 0;

   /**
    * Destructor of IThermalZone
    */
   virtual ~IThermalZone(){};
};

/**
 * @brief   ICoolingDevice provides interface to get type of the cooling device, the maximum
 *          throttle state and the currently requested throttle state of the cooling device.
 *
 * @note    Eval: This is a new API and is being evaluated. It is subject to change and could break
 *          backwards compatibility.
 */
class ICoolingDevice {
public:
   /**
    * Retrieves the identifier of the thermal cooling device.
    *
    * @returns Cooling device identifier
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual int getId() = 0;

   /**
    * Retrieves the type of the cooling device.
    *
    * @returns Cooling device type
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual std::string getDescription() = 0;

   /**
    * Retrieves the maximum cooling level of the cooling device.
    *
    * @returns Maximum cooling level of the thermal cooling device
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual int getMaxCoolingLevel() = 0;

   /**
    * Retrieves the current cooling level of the cooling device.
    * This value can be between 0 and max cooling level.
    * Max cooling level is different for different cooling devices
    * like fan, processor etc.
    *
    * @returns Current cooling level of the thermal cooling device
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change and could
    *          break backwards compatibility.
    */
   virtual int getCurrentCoolingLevel() = 0;

   /**
    * Destructor of ICoolingDevice
    */
   virtual ~ICoolingDevice(){};
};

/** @} */  // end_addtogroup telematics_therm

}  // end of namespace therm
}  // end of namespace telux

#endif  // THERMALMANAGER_HPP