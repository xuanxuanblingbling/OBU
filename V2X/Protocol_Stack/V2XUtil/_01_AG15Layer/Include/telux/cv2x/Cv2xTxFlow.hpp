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
* @file       Cv2xTxFlow.hpp
*
* @brief      Cv2xRadio class encapsulates a CV2X radio (channel) resource.
* @brief      Represents both Cv2x SPS and Event flows. Encapsulates the Tx
*             socket and associated socket address.
*/



#ifndef CV2XTXFLOW_HPP
#define CV2XTXFLOW_HPP

#include <netinet/in.h>

#include "../../../Include/telux/cv2x/Cv2xRadioTypes.hpp"


namespace telux {

namespace cv2x {

/** @addtogroup telematics_cv2x
 * @{ */

/**
 * This is class encapsulates a Cv2xRadio Tx flows. It contains the Tx socket
 * associated with the flow through which client applications can send data. This
 * class is referenced in @ref Cv2xRadio::createTxSpsFlow, Cv2xRadio::createTxEventFlow,
 * and Cv2xRadio::closeTxFlow
 */
class ICv2xTxFlow {
public:

    /**
     * Accessor for flow ID. The flow ID should be unique within a process but will
     * not be unique between processes.
     *
     * @returns flow ID
     */
    virtual uint32_t getFlowId() const = 0;

    /**
     * Accessor for IP traffic type
     *
     * @returns The flow's IP traffic type (IP or NON-IP)
     */
    virtual TrafficIpType getIpType() const = 0;

    /**
     * Accessor for service ID
     *
     * @returns The flow's Service ID.
     */
    virtual uint32_t getServiceId() const = 0;

    /**
     * Accessor for the socket file descriptor
     *
     * @returns The flow's socket fd.
     */
    virtual int getSock() const = 0;

    /**
     * Accessor for the socket address description
     *
     * @returns The flow's socket address
     */
    virtual struct sockaddr_in6 getSockAddr() const = 0;

    /**
     * Accessor for the flow's source port number
     *
     * @returns The flow's source port num
     */
    virtual uint16_t getPortNum() const = 0;

    virtual ~ICv2xTxFlow() {}
};

/** @} */ /* end_addtogroup telematics_cv2x */

} // namespace cv2x

} // namespace telux

#endif // #ifndef CV2XTXFLOW_HPP
