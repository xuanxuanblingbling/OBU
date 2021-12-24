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
 * @file       SubscriptionListener.hpp
 *
 * @brief      SubscriptionListener provides callback methods for listening to
 *             notifications about Subscriptions. Client needs to implement this
 *             interface to get access to notifications. The methods in listener can be
 *             invoked from multiple different threads. The implementation should be
 *             thread-safe.
 */

#ifndef SUBSCRIPTIONLISTENER_HPP
#define SUBSCRIPTIONLISTENER_HPP

#include <memory>

#include <telux/tel/Subscription.hpp>

namespace telux {
namespace tel {

/** @addtogroup telematics_subscription
 * @{ */

/**
 * @brief     A listener class for receiving device subscription information.
 *            The methods in listener can be invoked from multiple different
 *            threads. The implementation should be thread safe.
 */
class ISubscriptionListener {

public:
   /**
    * This function is called whenever there is a change in Subscription details.
    *
    * @param [in] subscription    Pointer to ISubscription Object.
    */
   virtual void onSubscriptionInfoChanged(std::shared_ptr<ISubscription> subscription) {
   }

   /**
    * This function called whenever there is a change in the subscription count.
    * for example when a new subscription is discovered or an existing subscription
    * goes away when SIM is inserted or removed respectively.
    *
    * @param [in] count    count of subscription
    */
   virtual void onNumberOfSubscriptionsChanged(int count) {
   }

   virtual ~ISubscriptionListener() {
   }
};

/** @} */ /* end_addtogroup telematics_subscription */

}  // end of namespace tel
}  // end of namespace telux

#endif
