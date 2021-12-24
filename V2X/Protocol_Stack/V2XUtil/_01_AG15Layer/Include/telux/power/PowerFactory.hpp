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
 * @file       PowerFactory.hpp
 *
 * @brief      PowerFactory allows creation of TCU-activity manager class
 *
 * @note       Eval: This is a new API and is being evaluated.It is subject to change and could
 *             break backwards compatibility.
 */

#ifndef POWERFACTORY_HPP
#define POWERFACTORY_HPP

#include <memory>
#include <mutex>

#include "../../../../_01_AG15Layer/Include/telux/power/TcuActivityManager.hpp"

namespace telux {
namespace power {

/** @addtogroup telematics_power
 * @{ */

/**
 * @brief   PowerFactory allows creation of TCU-activity manager instance.
 *
 * @note    Eval: This is a new API and is being evaluated.It is subject to change and could break
 *          backwards compatibility.
 */
class PowerFactory {
public:
    /**
     * API to get the factory instance for TCU-activity management
     */
    static PowerFactory &getInstance();

    /**
     * API to get the TCU-activity Manager instance
     *
     * @returns Pointer of ITcuActivityManager object.
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to change and could
     *          break backwards compatibility.
     */
    std::shared_ptr<ITcuActivityManager> getTcuActivityManager();

    ~PowerFactory();

private:
    std::shared_ptr<ITcuActivityManager> tcuActivityManager_;
    std::mutex tcuActivityFactoryMutex_;
    PowerFactory();
    PowerFactory(const PowerFactory &) = delete;
    PowerFactory &operator=(const PowerFactory &) = delete;
};

/** @} */ /* end_addtogroup telematics_power */

}  // end of namespace power
}  // end of namespace telux

#endif  // POWERFACTORY_HPP
