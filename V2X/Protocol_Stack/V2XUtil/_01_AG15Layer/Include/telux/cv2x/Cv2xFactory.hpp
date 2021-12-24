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
* @file       Cv2xFactory.hpp
*
* @brief      Cv2xFactory is the factory that creates the Cv2x Radio.
*/

#ifndef CV2XFACTORY_HPP
#define CV2XFACTORY_HPP

#include <memory>
#include <mutex>

#include "../../../Include/telux/common/CommonDefines.hpp"

namespace telux {

namespace cv2x {

/** @addtogroup telematics_cv2x
 * @{ */

class ICv2xRadio;
class ICv2xRadioManager;

/**
 *@brief Cv2xFactory is the factory that creates the Cv2x Radio.
 */
class Cv2xFactory {
public:
    /**
     * Get Cv2xFactory instance
     *
     * @returns Reference to Cv2xFactory singleton.
     */
    static Cv2xFactory & getInstance();

    /**
     * Get Cv2xRadioManager instance.
     *
     * @returns shared pointer to Radio upon success.
     *          nullptr otherwise.
     */
    std::shared_ptr<ICv2xRadioManager> getCv2xRadioManager();

private:

    std::mutex mutex_;
    std::shared_ptr<ICv2xRadioManager> radioManager_;

    Cv2xFactory();
};

/** @} */ /* end_addtogroup telematics_cv2x */

} // namespace cv2x

} // namespace telux

#endif // #ifndef CV2XFACTORY_HPP
