/*
 *  Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
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
 * @file       CallListener.hpp
 * @brief      Interface for Call listener object. Client needs to implement this interface
 *             to get access to Call related notifications like call state changes and ecall
 *             state change.
 *
 *             The methods in listener can be invoked from multiple different threads. The
 *             implementation should be thread safe.
 */

#ifndef CALLLISTENER_HPP
#define CALLLISTENER_HPP

#include <vector>
#include <memory>

#include "../../../../_01_AG15Layer/Include/telux/common/CommonDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/Call.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/ECallDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/Phone.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/PhoneDefines.hpp"

namespace telux {

namespace tel {

/** @addtogroup telematics_call
 * @{ */

class ICall;

/**
 * @brief A listener class for monitoring changes in call,
 * including call state change and ECall state change.
 * Override the methods for the state that you wish to receive updates for.
 *
 * The methods in listener can be invoked from multiple different threads. The implementation
 * should be thread safe.
 */
class ICallListener {
public:
   /**
    * This function is called when device receives an incoming call.
    *
    * @param [in] call -  Pointer to ICall instance
    */
   virtual void onIncomingCall(std::shared_ptr<ICall> call) {
   }

   /**
    * This function is called when there is a change in call attributes
    *
    * @param [in] call -  Pointer to ICall instance
    */
   virtual void onCallInfoChange(std::shared_ptr<ICall> call) {
   }

   /**
    * This function is called when device completes MSD Transmission.
    *
    * @param [in] phoneId - Unique Id of phone on which MSD Transmission Status is being reported
    * @param [in] status - Indicates MSD Transmission status i.e. success or failure
    *
    * @deprecated Use another onECallMsdTransmissionStatus() API with argument
    * @Ref ECallMsdTransmissionStatus
    */
   virtual void onECallMsdTransmissionStatus(int phoneId, telux::common::ErrorCode errorCode) {
   }

   /**
    * This function is called when device completes MSD Transmission.
    *
    * @param [in] phoneId - Unique Id of phone on which MSD Transmission Status is being reported
    * @param [in] msdTransmissionStatus - Indicates MSD Transmission status
    * @Ref ECallMsdTransmissionStatus
    */
   virtual void onECallMsdTransmissionStatus(
      int phoneId, telux::tel::ECallMsdTransmissionStatus msdTransmissionStatus) {
   }

   virtual ~ICallListener() {
   }
};
/** @} */ /* end_addtogroup telematics_call */

}  // End of namespace tel

}  // End of namespace telux

#endif  // CALLLISTENER_HPP
