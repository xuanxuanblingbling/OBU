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
 * @file       PhoneListener.hpp
 * @brief      Interface for Phone listener object. Client needs to implement
 *             this interface to get access to Telephony subsystem notifications
 *             like service state and signal strength.
 *
 *             The methods in listener can be invoked from multiple different
 *             threads. The implementation should be thread-safe.
 */

#ifndef PHONELISTENER_HPP
#define PHONELISTENER_HPP

#include <memory>
#include <vector>

#include <telux/tel/Call.hpp>
#include <telux/tel/CellInfo.hpp>
#include <telux/tel/PhoneDefines.hpp>
#include <telux/tel/ECallDefines.hpp>
#include <telux/tel/SignalStrength.hpp>
#include <telux/tel/VoiceServiceInfo.hpp>

namespace telux {
namespace tel {

/** @addtogroup telematics_phone
 * @{ */

/**
 * @brief A listener class for monitoring changes in specific telephony states
 * on the device, including service state and signal strength.
 * Override the methods for the state that you wish to receive updates for.
 *
 * The methods in listener can be invoked from multiple different threads. The
 * implementation should be thread safe.
 */
class IPhoneListener {
public:
   /**
    * This function is called when device service state changes.
    *
    * @param [in] phoneId   Unique id of the phone on which service state
    *                       changed.
    * @param [in] state     Service state of the phone @ref ServiceState
    *
    * @deprecated Use onVoiceServiceStateChanged() listener
    */
   virtual void onServiceStateChanged(int phoneId, ServiceState state) {
   }

   /**
    * This function is called when network signal strength changes.
    *
    * @param [in] phoneId          Unique id of the phone on which signal
    *                              strength state changed.
    * @param [in] signalStrength   Pointer to signal strength object
    */
   virtual void onSignalStrengthChanged(int phoneId,
                                        std::shared_ptr<SignalStrength> signalStrength) {
   }

   /**
    * This function is called when info pertaining to current or neighboring
    * cells change.
    *
    * @param [in] phoneId        Unique id of the phone on which cell info
    *                            changed.
    * @param [in] cellInfoList   vector of shared pointers to cell info object
    *
    */
   virtual void onCellInfoListChanged(int phoneId,
                                      std::vector<std::shared_ptr<CellInfo>> cellInfoList) {
   }

   /**
    * This function is called when radio state changes on phone
    *
    * @param [in] phone       Unique id of the phone on which radio state
    *                         changed
    *
    * @param [in] radioState  Radio state of the phone @ref RadioState
    */
   virtual void onRadioStateChanged(int phoneId, RadioState radioState) {
   }

   /**
    * This function is called when the radio technology for voice service changes
    *
    * @param [in] phone       Unique id of the phone on which radio technology
    *                         changed
    *
    * @param [in] radioTech   Radio state of the phone
    *                         @ref telux::tel::RadioTechnology
    */
   virtual void onVoiceRadioTechnologyChanged(int phoneId, RadioTechnology radioTech) {
   }

   /**
    * This function is called when the service state for voice service changes
    *
    * @param [in] phone       Unique id of the phone on which radio technology
    *                         changed
    *
    * @param [in] serviceInfo pointer of voice service state info object
    *                         @ref telux::tel::VoiceServiceInfo
    */
   virtual void onVoiceServiceStateChanged(int phoneId,
                                           const std::shared_ptr<VoiceServiceInfo> &serviceInfo) {
   }

   /**
    * This function is called when the operating mode changes
    *
    * @param [in] mode   Operating mode @ref OperatingMode.
    *
    */
   virtual void onOperatingModeChanged(OperatingMode mode) {
   }

   /**
    * This function is called when eCall operating mode changes.
    *
    * @param [in] phoneId - Unique Id of phone for which eCall operating mode changed
    * @param [in] info - Indicates eCall operating mode change reason
    * @Ref ECallModeInfo
    *
    * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
    *         break backwards compatibility.
    */
   virtual void onECallOperatingModeChange(int phoneId, telux::tel::ECallModeInfo info) {
   }

   virtual ~IPhoneListener() {
   }
};
/** @} */ /* end_addtogroup telematics_phone */

}  // End of namespace tel
}  // End namespace telux

#endif  // PHONELISTENER_HPP
