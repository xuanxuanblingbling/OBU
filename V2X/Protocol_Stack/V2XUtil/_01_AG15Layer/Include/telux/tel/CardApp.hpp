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
 * @file       CardApp.hpp
 * @brief      CardApp class is used to represent a single card Application on a SIM card.
 *
 */

#ifndef CARDAPP_HPP
#define CARDAPP_HPP

#include <string>

#include "../../../../_01_AG15Layer/Include/telux/common/CommonDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/CardDefines.hpp"

namespace telux {

namespace tel {

/**
 * This function is called with the response to pin operations like change pin password,
 * unlock card and set card lock.
 *
 * @param [in] retryCount         No of retry attempts left
 * @param [in] error              Return code for whether the operation
 *                                succeeded or failed
 *
 * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
 *         break backwards compatibility.
 */

using PinOperationResponseCb = std::function<void(int retryCount, telux::common::ErrorCode error)>;

/**
 * This function is called with the response to queryFdnLockState API.
 *
 * @param [in] isAvailable     Determine FDN lock state availability
 * @param [in] isEnabled       Determine FDN lock state i.e enable or disable
 * @param [in] error           Return code for whether the operation
 *                             succeeded or failed
 *
 * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
 *         break backwards compatibility.
 */

using QueryFdnLockResponseCb
   = std::function<void(bool isAvailable, bool isEnabled, telux::common::ErrorCode error)>;

/**
 * This function is called with the response to queryPin1LockState API.
 *
 * @param [in] state  Determine state whether enabled or disabled
 * @param [in] error  Return code for whether the operation
 *                    succeeded or failed
 *
 * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
 *         break backwards compatibility.
 */

using QueryPin1LockResponseCb = std::function<void(bool state, telux::common::ErrorCode error)>;

/** @addtogroup telematics_card
 * @{ */

/**
 * @brief Represents a single card application.
 */

class ICardApp {
public:
   /**
    * Get Application type like SIM, USIM, RUIM, CSIM or ISIM.
    *
    * @returns @ref AppType.
    */
   virtual AppType getAppType() = 0;

   /**
    * Get Application state like PIN1, PUK required and others.
    *
    * @returns @ref AppState.
    */
   virtual AppState getAppState() = 0;

   /**
    * Get application identifier.
    *
    * @returns Application Id.
    */
   virtual std::string getAppId() = 0;

   /**
    * Change the password used in PIN1/PIN2 lock.
    *
    * @param [in] lockType  @Ref  CardLockType. Applicable lock types are PIN1 and PIN2.
    * @param [in] oldPwd    Old password
    * @param [in] newPwd    New password
    * @param [in] callback  Callback function to get the response of change pin password.
    *
    * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
    *         break backwards compatibility.
    *
    */
   virtual telux::common::Status changeCardPassword(CardLockType lockType, std::string oldPwd,
                                               std::string newPwd, PinOperationResponseCb callback)
      = 0;

   /**
    * Unlock the Sim card for an app by entering PUK and new pin.
    *
    * @param [in] lockType  @Ref  CardLockType. Applicable lock types are PUK1 and PUK2
    * @param [in] puk       PUK1/PUK2
    * @param [in] pin       New PIN1/PIN2
    * @param [in] callback  Callback function to get the response of unlock card lock.
    *
    * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
    *         break backwards compatibility.
    *
    */
   virtual telux::common::Status unlockCardByPuk(CardLockType lockType, std::string puk,
                                                 std::string newPin,
                                                 PinOperationResponseCb callback)
      = 0;

   /**
    * Unlock the Sim card for an app by entering PIN.
    *
    * @param [in] lockType  @Ref  CardLockType. Applicable lock types are PIN1 and PIN2.
    * @param [in] pin       New PIN1/PIN2
    * @param [in] callback  Callback function to get the response of unlock card lock.
    *
    * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
    *         break backwards compatibility.
    *
    */
   virtual telux::common::Status unlockCardByPin(CardLockType lockType, std::string pin,
                                                 PinOperationResponseCb callback)
      = 0;

   /**
    * Query Pin1 lock state.
    *
    * @param [in] callback  Callback function to get the response of query pin1 lock state.
    *
    * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
    *         break backwards compatibility.
    */
   virtual telux::common::Status queryPin1LockState(QueryPin1LockResponseCb callback) = 0;

   /**
    * Query FDN lock state.
    *
    * @param [in] callback  Callback function to get the response of query fdn lock state.
    *
    * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
    *         break backwards compatibility.
    */
   virtual telux::common::Status queryFdnLockState(QueryFdnLockResponseCb callback) = 0;

   /**
    * Enable or disable FDN or Pin1 lock.
    *
    * @param [in] lockType   @Ref CardLockType. Applicable lock type such as PIN1 and FDN
    * @param [in] password   Password of PIN1 and FDN
    * @param [in] isEnabled  If true then enable else disable.
    * @param [in] callback   Callback function to get the response of set card lock.
    *
    * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
    *         break backwards compatibility.
    */
   virtual telux::common::Status setCardLock(CardLockType lockType, std::string password,
                                             bool isEnabled, PinOperationResponseCb callback)
      = 0;

   virtual ~ICardApp(){};
};
/** @} */ /* end_addtogroup telematics_card */

}  // End of namespace tel

}  // End of namespace telux

#endif  // CARDAPP_HPP
