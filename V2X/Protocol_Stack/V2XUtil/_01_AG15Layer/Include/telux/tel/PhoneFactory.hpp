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
 * @file       PhoneFactory.hpp
 * @brief      PhoneFactory is the central factory to create all Telephony SDK
 *             classes and services.
 */

#ifndef PHONEFACTORY_HPP
#define PHONEFACTORY_HPP

#include <map>
#include <memory>

#include "../../../../_01_AG15Layer/Include/telux/tel/CallManager.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/CardManager.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/NetworkSelectionManager.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/Phone.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/SapCardManager.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/ServingSystemManager.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/SmsManager.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/SubscriptionManager.hpp"
#include "../../../Include/telux/tel/PhoneManager.hpp"

namespace telux {

namespace tel {

/** @addtogroup telematics_phone_factory
 * @{ */

/**
 * @brief PhoneFactory is the central factory to create all Telephony SDK Classes
 *        and services
 */
class PhoneFactory {
public:
   /**
    * Get Phone Factory instance.
    */
   static PhoneFactory &getInstance();

   /**
    * Get Phone Manager instance. Phone Manager is the main entry point into the
    * telephony subsystem.
    *
    * @returns Pointer of IPhoneManager object.
    */
   std::shared_ptr<IPhoneManager> getPhoneManager();

   /**
    * Get SMS Manager instance for Phone ID. SMSManager used to send and receive
    * SMS messages.
    *
    * @param [in] phoneId   Unique identifier for the phone
    *
    * @returns Pointer of ISmsManager object or nullptr in case of failure.
    */
   std::shared_ptr<ISmsManager> getSmsManager(int phoneId = DEFAULT_PHONE_ID);

   /**
    * Get Call Manager instance to determine state of active calls and perform
    * other functions like dial, conference, swap call.
    *
    * @returns Pointer of ICallManager object.
    */
   std::shared_ptr<ICallManager> getCallManager();

   /**
    * Get Card Manager instance to handle services such as transmitting APDU,
    * SIM IO and more.
    *
    * @returns Pointer of ICardManager object.
    */
   std::shared_ptr<ICardManager> getCardManager();

   /**
    * Get Sap Card Manager instance associated with the provided slot id. This
    * object will handle services in SAP mode such as APDU, SIM Power On/Off
    * and SIM reset.
    *
    * @param [in] slotId    Unique identifier for the SIM slot
    *
    * @returns Pointer of ISapCardManager object.
    */
   std::shared_ptr<ISapCardManager> getSapCardManager(int slotId = DEFAULT_SLOT_ID);

   /**
    * Get Subscription Manager instance to get device subscription details
    *
    * @returns Pointer of ISubscriptionManager object.
    */
   std::shared_ptr<ISubscriptionManager> getSubscriptionManager();

   /**
    * Get Serving System Manager instance to get and set preferred network type.
    *
    * @param [in] slotId    Unique identifier for the SIM slot
    *
    * @returns Pointer of IServingSystemManager object.
    */
   std::shared_ptr<IServingSystemManager> getServingSystemManager(int slotId = DEFAULT_SLOT_ID);

   /**
    * Get Network Selection Manager instance to get and set selection mode, get
    * and set preferred networks and scan available networks.
    *
    * @param [in] slotId    Unique identifier for the SIM slot
    *
    * @returns Pointer of INetworkSelectionManager object.
    */
   std::shared_ptr<INetworkSelectionManager> getNetworkSelectionManager(int slotId
                                                                        = DEFAULT_SLOT_ID);

private:
   std::shared_ptr<IPhoneManager> phoneManager_;
   std::shared_ptr<ICallManager> callManager_;
   std::shared_ptr<ICardManager> cardManager_;
   std::shared_ptr<ISapCardManager> sapCardManager_;
   std::shared_ptr<ISubscriptionManager> subscriptionManager_;
   std::map<int, std::shared_ptr<ISmsManager>> smsMap_;
   std::map<int, std::shared_ptr<IServingSystemManager>> servingSystemManagerMap_;
   std::map<int, std::shared_ptr<INetworkSelectionManager>> networkSelectionManagerMap_;
   std::map<int, std::shared_ptr<ISapCardManager>> sapCardManagerMap_;

   PhoneFactory();
   ~PhoneFactory();
   PhoneFactory(const PhoneFactory &) = delete;
   PhoneFactory &operator=(const PhoneFactory &) = delete;
   std::recursive_mutex mutex_;
};

/** @} */ /* end_addtogroup telematics_phone_factory */

}  // End of namespace tel

}  // End of namespace telux

#endif  // PHONEFACTORY_HPP
