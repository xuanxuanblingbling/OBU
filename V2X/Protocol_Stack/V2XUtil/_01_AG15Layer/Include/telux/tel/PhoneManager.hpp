/*
 *  Copyright (c) 2017-2018 The Linux Foundation. All rights reserved.
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
 * @file       PhoneManager.hpp
 * @brief      PhoneManager enumerates one or more phones. It also allows
 *             clients to register for notification of system events.
 *             clients should check if the subsystem is ready before
 *             invoking any of the APIs as follows
 *
 *             bool isReady = phoneManager->isSubsystemReady();
 *
 */

#ifndef PHONEMANAGER_HPP
#define PHONEMANAGER_HPP

#include <future>
#include <memory>
#include <string>
#include <vector>

#include "../../../../_01_AG15Layer/Include/telux/common/CommonDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/PhoneDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/PhoneListener.hpp"

namespace telux {
namespace tel {

class ICellularCapabilityCallback;
class IOperatingModeCallback;

/** @addtogroup telematics_phone
 * @{ */

/**
 *@brief       Phone Manager creates one or more phones based on SIM slot count,
 *             it allows clients to register for notification of system events.
 *             Clients should check if the subsystem is ready before invoking
 *             any of the APIs.
 *
 */
class IPhoneManager {
public:
   /**
    * Checks the status of telephony subsystems and returns the result.
    *
    * @returns If true PhoneManager is ready for service (i.e Phone, Sms and
    * Card).
    */
   virtual bool isSubsystemReady() = 0;

   /**
    * Wait for telephony subsystem to be ready.
    *
    * @returns A future that caller can wait on to be notified when telephony
    * subsystem is ready.
    */
   virtual std::future<bool> onSubsystemReady() = 0;

   /**
    * Retrieves a list of Phone Ids. Each id is unique per phone.
    * For example: on a dual SIM device, there would be 2 Phones.
    *
    * @param [out] phoneIds   List of phone ids
    *
    * @returns Status of getPhoneIds i.e. success or suitable error code.
    */
   virtual telux::common::Status getPhoneIds(std::vector<int> &phoneIds) = 0;

   /**
    * Get the Phone Id for a given Slot Id.
    *
    * @param [in] slotId    SIM Card Slot Id
    *
    * @returns Phone Id corresponding to the Slot Id.
    */
   virtual int getPhoneIdFromSlotId(int slotId) = 0;

   /**
    * Get the SIM Slot Id for a given Phone Id.
    *
    * @param [in] phoneId    Phone Id of the phone
    *
    * @returns Slot Id corresponding to the Phone Id.
    */
   virtual int getSlotIdFromPhoneId(int phoneId) = 0;

   /**
    * Get the phone instance for a given phone identifier.
    *
    * @param [in] phoneId   Identifier for phone instance, retrieved from
    *                       getPhoneIds API
    *
    * @returns Pointer to Phone object corresponding to phoneId.
    */
   virtual std::shared_ptr<IPhone> getPhone(int phoneId = DEFAULT_PHONE_ID) = 0;

   /**
    * Get the information about cellular capability.
    *
    * @param [in] callback   Optional callback pointer to get the response of
    *                        cellular capability.
    *
    * @returns Status of requestCellularCapabilityInfo i.e. success or suitable
    * error code.
    *
    *
    */
   virtual telux::common::Status
      requestCellularCapabilityInfo(std::shared_ptr<ICellularCapabilityCallback> callback = nullptr)
      = 0;

   /**
    * Get current operating mode of the device.
    *
    * @param [in] callback   Optional callback pointer to get the response of
    *                        operating mode request
    *
    * @returns Status of requestOperatingMode i.e. success or suitable error
    * code.
    *
    */
   virtual telux::common::Status
      requestOperatingMode(std::shared_ptr<IOperatingModeCallback> callback = nullptr)
      = 0;

   /**
    * Set the operating mode of the device. Only valid transitions allowed from
    * one mode to another.
    *
    * @param [in] operatingMode Operating Mode to be set
    * @param [in] callback      Optional callback pointer to get the response
    *                           of set operatingmode request.
    *                           In callback following error is returned.
    *                           - @ref
    *                             telux::common::ErrorCode::INVALID_TRANSITION
    *                           - @ref
    *                             telux::common::ErrorCode::INVALID_ARGUMENTS
    *                           - @ref telux::common::ErrorCode::DEVICE_IN_USE
    *                           - @ref telux::common::ErrorCode::NO_MEMORY
    *
    * @returns Status of setOperatingMode i.e. success or suitable error code.
    */
   virtual telux::common::Status setOperatingMode(OperatingMode operatingMode,
                                                  telux::common::ResponseCallback callback
                                                  = nullptr)
      = 0;

   /**
    * Register a listener for specific events in the telephony subsystem.
    *
    * @param [in] listener  Pointer to Phone Listener object that processes the
    *                       notification
    *
    * @returns Status of registerListener i.e. success or suitable error code.
    */
   virtual telux::common::Status registerListener(std::weak_ptr<IPhoneListener> listener) = 0;

   /**
    * Remove a previously added listener.
    *
    * @param [in] listener    Pointer to Phone Listener object that needs to be
    *                         removed
    *
    * @returns Status of removeListener i.e. success or suitable error code.
    */
   virtual telux::common::Status removeListener(std::weak_ptr<IPhoneListener> listener) = 0;

   virtual ~IPhoneManager(){};
};

/**
 * Interface for callback corresponding to cellular capability request.
 * Client needs to implement this interface to get single shot responses for
 * commands like get cellular capability.
 *
 * The methods in callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 */

class ICellularCapabilityCallback : public telux::common::ICommandCallback {
public:
   /**
    * This function is called with the response to requestCellularCapabilityInfo
    * API.
    *
    * @param [in] capabilityInfo  Cellular capability information.
    * @param [in] error           Return code for whether the operation
    *                             succeeded or failed
    *                             - @ref telux::common::ErrorCode::SUCCESS
    *                             - @ref telux::common::ErrorCode::INTERNAL
    *                             - @ref telux::common::ErrorCode::NO_MEMORY
    *
    */
   virtual void cellularCapabilityResponse(CellularCapabilityInfo capabilityInfo,
                                           telux::common::ErrorCode error) {
   }
   virtual ~ICellularCapabilityCallback(){};
};

/**
 * Interface for operating mode callback object.
 * Client needs to implement this interface to get single shot responses for
 * commands like request current operating mode.
 *
 * The methods in callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 */

class IOperatingModeCallback : public telux::common::ICommandCallback {
public:
   /**
    * This function is called with the response to requestOperatingMode API.
    *
    * @param [in] operatingMode   @ref OperatingMode
    * @param [in] error           Return code for whether the operation succeeded
    *                             or failed
    *                             - @ref telux::common::ErrorCode::SUCCESS
    *                             - @ref telux::common::ErrorCode::INTERNAL_ERR
    *                             - @ref telux::common::ErrorCode::NO_MEMORY
    */
   virtual void operatingModeResponse(OperatingMode operatingMode, telux::common::ErrorCode error) {
   }
   virtual ~IOperatingModeCallback(){};
};

/** @} */ /* end_addtogroup telematics_phone */
}
}

#endif
