/*
 *  Copyright (c) 2019, The Linux Foundation. All rights reserved.
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
 * @file       TcuActivityManager.hpp
 *
 * @brief      TcuActivityManager class provides interface to register and receive notifications
 *             related to TCU-activity states, initiate TCU-activity state transition.
 *
 * @note       Eval: This is a new API and is being evaluated.It is subject to change and could
 *             break backwards compatibility.
 */

#ifndef TCUACTIVITYMANAGER_HPP
#define TCUACTIVITYMANAGER_HPP

#include <future>
#include <memory>

#include "../../../../_01_AG15Layer/Include/telux/common/CommonDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/power/TcuActivityListener.hpp"

namespace telux {
namespace power {

/** @addtogroup telematics_power
 * @{ */

/**
 * @brief   ITcuActivityManager provides interface to register and de-register listeners (to get
 *          TCU-activity state updates). And also API to initiate TCU-activity state transition.
 *
 * @note    Eval: This is a new API and is being evaluated.It is subject to change and could break
 *          backwards compatibility.
 */
class ITcuActivityManager {
public:
    /**
     * Checks the status of TCU-activity services and if the other APIs are ready for use,
     * and returns the result.
     *
     * @returns  True if the services are ready otherwise false.
     *
     * @note     Eval: This is a new API and is being evaluated.It is subject to change and could
     *           break backwards compatibility.
     */
    virtual bool isReady() = 0;

    /**
     * Wait for TCU-activity services to be ready.
     *
     * @returns  A future that caller can wait on to be notified when TCU-activity services
     *           are ready.
     *
     * @note     Eval: This is a new API and is being evaluated.It is subject to change and could
     *           break backwards compatibility.
     */
    virtual std::future<bool> onReady() = 0;

    /**
     * Register a listener for updates on TCU-activity state changes.
     *
     * @param [in] listener Pointer of ITcuActivityListener object that processes the notification
     *
     * @returns Status of registerListener i.e success or suitable status code.
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to change
     *          and could break backwards compatibility.
     */
    virtual telux::common::Status registerListener(std::weak_ptr<ITcuActivityListener> listener) =0;

    /**
     * Remove a previously registered listener.
     *
     * @param [in] listener Previously registered ITcuActivityListener that needs to be removed
     *
     * @returns Status of deregisterListener, success or suitable status code
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to change
     *          and could break backwards compatibility.
     */
    virtual telux::common::Status deregisterListener(std::weak_ptr<ITcuActivityListener> listener)
                        = 0;

    /**
     * Initiate a TCU-activity state transition.
     *
     * This API needs to be used cautiously, as it could change the power-state of the system and
     * may affect other processes.
     *
     * @param [in] state    TCU-activity state that the System is intended to enter
     * @param [in] callback Optional callback to get the response for the TCU-activity state
     *                      transition command
     *
     * @returns Status of setActivityState i.e. success or suitable status code.
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to change
     *          and could break backwards compatibility.
     */
    virtual telux::common::Status setActivityState( TcuActivityState state,
                        telux::common::ResponseCallback callback = nullptr) = 0;

    /**
     * Get the current TCU-activity state.
     *
     * @returns TcuActivityState
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to change
     *          and could break backwards compatibility.
     */
    virtual TcuActivityState getActivityState() = 0;

    /**
     * API to send the acknowledgement, after processing a TCU-activity state notification.
     * This indicates that the client is prepared for state transition.Only one acknowledgement is
     * expected from a single client process(may have multiple listeners).
     *
     * @param [in] ack Acknowledgement for a TCU-activity state notification.
     *
     * @returns Status of sendActivityStateAck i.e. success or suitable status code.
     *
     * @note     Eval: This is a new API and is being evaluated.It is subject to change and could
     *           break backwards compatibility.
     */
    virtual telux::common::Status sendActivityStateAck(TcuActivityStateAck ack) = 0;

    /**
     * Destructor of ITcuActivityManager
     */
    virtual ~ITcuActivityManager(){};
};
/** @} */ /* end_addtogroup telematics_power */

}  // end of namespace power
}  // end of namespace telux

#endif  // TCUACTIVITYMANAGER_HPP
