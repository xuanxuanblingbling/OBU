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
 * @file       Phone.hpp
 * @brief      Phone class is the primary interface to get phone informations
 *             like radio state, signal strength, turn on/off radio power,
 *             voice radio tech and voice service state.
 */

#ifndef PHONE_HPP
#define PHONE_HPP

#include <memory>
#include <string>

#include <telux/common/CommonDefines.hpp>
#include <telux/tel/Call.hpp>
#include <telux/tel/CellInfo.hpp>
#include <telux/tel/ECallDefines.hpp>
#include <telux/tel/PhoneDefines.hpp>
#include <telux/tel/PhoneManager.hpp>
#include <telux/tel/VoiceServiceInfo.hpp>

namespace telux {
namespace tel {

class ISignalStrengthCallback;
class IVoiceServiceStateCallback;

/**
 * This function is called with the response to requestVoiceRadioTechnology API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] radioTech  Pointer to radio technology
 * @param [in] error      Return code for whether the operation
 *                        succeeded or failed
 *                        - @ref telux::common::ErrorCode::SUCCESS
 *                        - @ref telux::common::ErrorCode::RADIO_NOT_AVAILABLE
 *                        - @ref telux::common::ErrorCode::GENERIC_FAILURE
 */
using VoiceRadioTechResponseCb
   = std::function<void(telux::tel::RadioTechnology radioTech, telux::common::ErrorCode error)>;

/**
 * This function is called with the response to requestCellInfo API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [out] cellInfoList  vector of shared pointers to cell info object
 * @param [out] error         Return code for whether the operation
 *                            succeeded or failed
 */
using CellInfoCallback = std::function<void(std::vector<std::shared_ptr<CellInfo>> cellInfoList,
                                            telux::common::ErrorCode error)>;

/**
 * This function is called with the response to requestECallOperatingMode API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [out] eCallMode    @ref ECallMode
 * @param [out] error        Return code for whether the operation succeeded or failed
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to change and could
 *         break backwards compatibility.
 */
using ECallGetOperatingModeCallback
   = std::function<void(ECallMode eCallMode, telux::common::ErrorCode error)>;

/** @addtogroup telematics_phone
 * @{ */

/**
 * @brief This class allows getting system information and registering for system events.
 * Each Phone instance is associated with a single SIM. So on a dual SIM device you
 * would have 2 Phone instances.
 */
class IPhone {
public:
   /**
    * Get the Phone ID corresponding to phone.
    *
    * @param [out] phoneId   Unique identifier for the phone
    *
    * @returns Status of getPhoneId i.e. success or suitable error code.
    */
   virtual telux::common::Status getPhoneId(int &phId) = 0;

   /**
    * Get Radio state of device.
    *
    * @returns @ref RadioState
    *
    */
   virtual RadioState getRadioState() = 0;

   /**
    * Request for Radio technology type (3GPP/3GPP2) used for voice.
    *
    * @param [in] callback  callback pointer to get the response of radio power
    *                       request @ref telux::tel::VoiceRadioTechResponseCb
    *
    * @returns Status of requestVoiceRadioTechnology i.e. success or suitable
    * error code @ref telux::common::Status.
    */
   virtual telux::common::Status requestVoiceRadioTechnology(VoiceRadioTechResponseCb callback) = 0;

   /**
    * Get service state of the phone.
    *
    * @returns    @ref ServiceState
    *
    * @deprecated Use requestVoiceServiceState() API
    */
   virtual ServiceState getServiceState() = 0;

   /**
    * Request for voice service state to get the information of phone serving
    * states
    *
    * @param [in] callback  callback pointer to get the response of voice
    *                       service state @ref telux::tel::IVoiceServiceStateCallback.
    *
    * @returns Status of requestVoiceServiceState i.e. success or suitable error
    * code @ref telux::common::Status.
    */
   virtual telux::common::Status
      requestVoiceServiceState(std::weak_ptr<IVoiceServiceStateCallback> callback)
      = 0;

   /**
    * Set the radio power on or off.
    *
    * @param [in] enable    Flag that determines whether to turn radio on or off
    * @param [in] callback  Optional callback pointer to get the response of set
    *                       radio power request
    *
    * @returns Status of setRadioPower i.e. success or suitable error code.
    */
   virtual telux::common::Status setRadioPower(
      bool enable, std::shared_ptr<telux::common::ICommandResponseCallback> callback = nullptr)
      = 0;

   /**
    * Get the cell information about current serving cell and neighboring cells.
    *
    * @param [in] callback    Callback to get the response of cell info request
    *                         @telux::tel::CellInfoCallback
    *
    * @returns Status of requestCellInfo i.e. success or suitable error
    *
    */
   virtual telux::common::Status requestCellInfo(CellInfoCallback callback) = 0;

   /**
    * Set the minimum time in milliseconds between when the cell info list should
    * be received.
    *
    * @param [in] timeInterval  Value of 0 means receive cell info list when any
    *                           info changes. Value of INT_MAX means never
    *                           receive cell info list even on change.
    *                           Default value is 0
    * @param [in] callback      Callback to get the response for set cell info
    *                           list rate.
    *
    * @returns Status of setCellInfoListRate i.e. success or suitable error
    *
    */
   virtual telux::common::Status setCellInfoListRate(uint32_t timeInterval,
                                                     common::ResponseCallback callback)
      = 0;

   /**
    * Get current signal strength of the associated network.
    *
    * @param [in] callback   Optional callback pointer to get the response of
    *                        signal strength request
    *
    * @returns Status of requestSignalStrength i.e. success or suitable error
    * code.
    */
   virtual telux::common::Status
      requestSignalStrength(std::shared_ptr<ISignalStrengthCallback> callback = nullptr)
      = 0;

   /**
    * Sets the eCall operating mode
    *
    * @param [in] eCallMode - @ref ECallMode
    * @param [in] callback - Callback function to get the response for set eCall operating mode
    * request.
    *
    * @returns Status of setECallOperatingMode i.e. success or suitable error
    *
    * @note Eval: This is a new API and is being evaluated. It is subject to
    *             change and could break backwards compatibility.
    */
   virtual telux::common::Status setECallOperatingMode(ECallMode eCallMode,
                                                       telux::common::ResponseCallback callback)
      = 0;

   /**
    * Get the eCall operating mode
    *
    * @param [in] callback - Callback function to get the response of eCall operating mode request
    *
    * @returns Status of requestECallOperatingMode i.e. success or suitable error
    *
    * @note Eval: This is a new API and is being evaluated. It is subject to
    *             change and could break backwards compatibility.
    */
   virtual telux::common::Status requestECallOperatingMode(ECallGetOperatingModeCallback callback)
      = 0;

   virtual ~IPhone(){};
};

/**
 * @brief Interface for Signal strength callback object.
 * Client needs to implement this interface to get single shot responses for
 * commands like get signal strength.
 *
 * The methods in callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 */
class ISignalStrengthCallback : public telux::common::ICommandCallback {
public:
   /**
    * This function is called with the response to requestSignalStrength API.
    *
    * @param [in] signalStrength   Pointer to signal strength object
    * @param [in] error            Return code for whether the operation
    *                              succeeded or failed
    *                              @ref SUCCESS
    *                              @ref RADIO_NOT_AVAILABLE
    */
   virtual void signalStrengthResponse(std::shared_ptr<SignalStrength> signalStrength,
                                       telux::common::ErrorCode error) {
   }

   virtual ~ISignalStrengthCallback() {
   }
};

/**
 * @brief Interface for voice service state callback object.
 * Client needs to implement this interface to get single shot responses for
 * commands like request voice radio technology.
 *
 * The methods in callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 */
class IVoiceServiceStateCallback : public telux::common::ICommandCallback {
public:
   /**
    * This function is called with the response to requestVoiceServiceState API.
    *
    * @param [in] serviceInfo   Pointer to voice service info object
    *                           @ref telux::tel::VoiceServiceInfo
    * @param [in] error         Return code for whether the operation
    *                           succeeded or failed
    *                           - @ref telux::common::ErrorCode::SUCCESS
    *                           - @ref telux::common::ErrorCode::RADIO_NOT_AVAILABLE
    *                           - @ref telux::common::ErrorCode::GENERIC_FAILURE
    */
   virtual void voiceServiceStateResponse(const std::shared_ptr<VoiceServiceInfo> &serviceInfo,
                                          telux::common::ErrorCode error) {
   }

   virtual ~IVoiceServiceStateCallback() {
   }
};

/** @} */ /* end_addtogroup telematics_phone */
}
}

#endif
