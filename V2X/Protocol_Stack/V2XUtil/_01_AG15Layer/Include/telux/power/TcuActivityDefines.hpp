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
 * @file       TcuActivityDefines.hpp
 *
 * @brief      This file contains types related to TCU activity.
 *
 * @note       Eval: These are new APIs and are being evaluated. They are subject to change and
 *             could break backwards compatibility.
 */

#include "../../../../_01_AG15Layer/Include/telux/common/CommonDefines.hpp"

#ifndef TCUACTIVITYDEFINES_HPP
#define TCUACTIVITYDEFINES_HPP

namespace telux {
namespace power {

/** @addtogroup telematics_power
 * @{ */

/**
 * Defines the supported TCU-activity states that the listeners will be notified about.
 */
enum class TcuActivityState {
    UNKNOWN,    /**< To indicate that system state information is not available */
    SUSPEND,    /**< System is going to SUSPEND state */
    RESUME,     /**< System is going to RESUME state */
    SHUTDOWN    /**< System is going to SHUTDOWN */
};

/**
 * Defines the acknowledgements to TCU-activity states.The client process sends this after
 * processing the TcuActivityState notification, indicating that it is prepared for state transition
 *
 * Acknowledgement for TcuActivityState::RESUME is not required, as the state transition has already
 * happened.
 */
enum class TcuActivityStateAck {
    SUSPEND_ACK,    /**< processed TcuActivityState::SUSPEND notification */
    SHUTDOWN_ACK,   /**< processed TcuActivityState::SHUTDOWN notification */
};

/** @} */ /* end_addtogroup telematics_power */

}  // end of namespace power
}  // end of namespace telux

#endif  // TCUACTIVITYDEFINES_HPP
