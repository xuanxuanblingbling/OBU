/*
 *  Copyright (c) 2017, The Linux Foundation. All rights reserved.
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
 * @file       SubscriptionManager.hpp
 *
 * @brief      Subscription Manager class provides the interface to register
 *             listener and receive notifications related to SIM card subscription
 *             information and to fetch the current subscription on client's
 *             request by SIM SlotId.
 */

#ifndef SUBSCRIPTIONMANAGER_HPP
#define SUBSCRIPTIONMANAGER_HPP

#include <future>
#include <vector>

#include "../../../../_01_AG15Layer/Include/telux/common/CommonDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/Subscription.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/SubscriptionListener.hpp"

namespace telux {
namespace tel {

/** @addtogroup telematics_subscription
* @{ */

/*
 * @brief   Subscription Manager class provides APIs to register
 *          and receive notifications related to SIM card subscription
 *          information and to fetch the current subscription on client's
 *          request by SIM SlotId.
 */
class ISubscriptionManager {
public:
   /**
    * Checks the status of SubscriptionManager and returns the result.
    *
    * @returns If true then SubscriptionManager is ready for service.
    */
   virtual bool isSubsystemReady() = 0;

   /**
    * Wait for Subscription subsystem to be ready.
    *
    * @returns A future that caller can wait on to be notified when
    *          SubscriptionManager is ready.
    */
   virtual std::future<bool> onSubsystemReady() = 0;

   /**
    * Get Subscription details of the SIM in the given SIM slot.
    *
    * @param [in] slotId   Slot id corresponding to the subscription.
    * @param [out] status  Status of getSubscription i.e. success or suitable status code.
    *
    * @returns Pointer to ISubscription object.
    */
   virtual std::shared_ptr<ISubscription> getSubscription(int slotId = DEFAULT_SLOT_ID,
                                                          telux::common::Status *status = nullptr)
      = 0;

   /**
    * Get all the subscription details of the device.
    *
    * @param [out] status  Status of getAllSubscriptions i.e. success or suitable status code.
    *
    * @returns list of ISubscription objects.
    */
   virtual std::vector<std::shared_ptr<ISubscription>>
      getAllSubscriptions(telux::common::Status *status = nullptr) = 0;

   /**
    * Register a listener for Subscription events.
    *
    * @param [in] listener   Pointer to ISubscriptionListener object that
    *                        processes the notification.
    *
    * @returns Status of registerListener i.e. success or suitable status code.
    */
   virtual telux::common::Status registerListener(std::weak_ptr<ISubscriptionListener> listener)
      = 0;

   /**
    * Remove a previously added listener.
    *
    * @param [in] listener   Pointer to ISubscriptionListener object that needs
    *                        to be removed.
    *
    * @returns Status of removeListener i.e. success or suitable status code.
    */
   virtual telux::common::Status removeListener(std::weak_ptr<ISubscriptionListener> listener) = 0;

   virtual ~ISubscriptionManager(){};
};

/** @} */ /* end_addtogroup telematics_subscription */

}  // end of namespace tel
}  // end namespace telux

#endif
