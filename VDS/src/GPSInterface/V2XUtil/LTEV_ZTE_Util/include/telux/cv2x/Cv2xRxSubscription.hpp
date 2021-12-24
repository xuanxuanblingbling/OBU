/*
 *  Copyright (c) 2018, The Linux Foundation. All rights reserved.
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
* @file       Cv2xRxSubscription.hpp
*
* @brief      Represents a Cv2x Rx subscription. Encapsulates the Rx socket
*             and associated Socket address.
*/

#ifndef CV2XRXSUBSCRIPTION_HPP
#define CV2XRXSUBSCRIPTION_HPP

#include <netinet/in.h>

#include <telux/cv2x/Cv2xRadioTypes.hpp>


namespace telux {

namespace cv2x {

/** @addtogroup telematics_cv2x
 * @{ */

/**
 * This class encapsulates a Cv2xRadio Rx Subscription. It contains the Rx socket
 * associated with the subscription from which client applications can read data. This
 * class is referenced in @ref Cv2xRadio::createRxSubscription and
 * Cv2xRadio::closeRxSubscription.
 */
class ICv2xRxSubscription {
public:

    /**
     * Accessor for Rx subscription ID
     *
     * @returns subscription ID
     */
    virtual uint32_t getSubscriptionId() const = 0;

    /**
     * Accessor for IP traffic type
     *
     * @returns The Rx subscriptions's IP traffic type (IP or NON-IP)
     */
    virtual TrafficIpType getIpType() const = 0;

    /**
     * Accessor for the socket file descriptor
     *
     * @returns The Rx subscriptions's socket fd.
     */
    virtual int getSock() const = 0;

    /**
     * Accessor for the socket address description
     *
     * @returns The Rx subscriptions's socket address
     */
    virtual struct sockaddr_in6 getSockAddr() const = 0;

    /**
     * Accessor for the subscriptions's port number
     *
     * @returns The Rx subscriptions's port num
     */
    virtual uint16_t getPortNum() const = 0;

    virtual ~ICv2xRxSubscription() {}
};

/** @} */ /* end_addtogroup telematics_cv2x */

} // namespace cv2x

} // namespace telux

#endif // #ifndef CV2XRXSUBSCRIPTION_HPP
