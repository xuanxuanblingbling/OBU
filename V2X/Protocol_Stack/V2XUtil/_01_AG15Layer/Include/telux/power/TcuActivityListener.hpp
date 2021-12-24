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
 * @file       TcuActivityListener.hpp
 *
 * @brief      TcuActivityListener provides callback methods for listening to TCU-activity service
 *             notifications, like TCU-activity state change.Client need to implement these methods.
 *             The methods in listener can be invoked from multiple threads.So the client needs to
 *             make sure that the implementation is thread-safe.
 *
 * @note       Eval: This is a new API and is being evaluated.It is subject to change and could
 *             break backwards compatibility.
 */

#ifndef TCUACTIVITYLISTENER_HPP
#define TCUACTIVITYLISTENER_HPP

#include <memory>

#include "../../../../_01_AG15Layer/Include/telux/power/TcuActivityDefines.hpp"

namespace telux {
namespace power {

/** @addtogroup telematics_power
 * @{ */

/**
 * @brief Listener class for getting notifications related to TCU-activity state and also the
 *        updates related to TCU-activity service status. The client needs to implement these
 *        methods as briefly as possible and avoid blocking calls in it.
 *        The methods in this class can be invoked from multiple different threads. Client
 *        needs to make sure that the implementation is thread-safe.
 *
 * @note  Eval: This is a new API and is being evaluated.It is subject to change
 *        and could break backwards compatibility.
 */
class ITcuActivityListener : public common::IServiceStatusListener {
public:
    /**
     * This function is called when the TCU-activity state is going to change.
     *
     * @param [in] state TCU-activity state that system is about to enter
     *
     * @note     Eval: This is a new API and is being evaluated.It is subject to change and could
     *           break backwards compatibility.
     */
    virtual void onTcuActivityStateUpdate(TcuActivityState state) {
    }

    /**
     * Destructor of ITcuActivityListener
     */
    virtual ~ITcuActivityListener() {
    }
};

/** @} */ /* end_addtogroup telematics_power */

}  // end of namespace power
}  // end of namespace telux

#endif  // TCUACTIVITYLISTENER_HPP
