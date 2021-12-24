/*
 *  Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
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
* @file       Cv2xRadioManager.hpp
*
* @brief      Cv2xRadioManager manages instances of Cv2xRadio
*
*/

#ifndef CV2XRADIOMANAGER_HPP
#define CV2XRADIOMANAGER_HPP

#include <memory>
#include <future>

#include "../../../../_01_AG15Layer/Include/telux/common/CommonDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/cv2x/Cv2xRadioListener.hpp"
#include "../../../../_01_AG15Layer/Include/telux/cv2x/Cv2xRadioTypes.hpp"


namespace telux {

namespace cv2x {

class ICv2xRadio;

/**
 *@brief Cv2x Radio Manager listeners implement this interface.
 */
class ICv2xListener : public common::IServiceStatusListener {
public:
    /**
     * Called when the status of the CV2X radio has changed.
     *
     * @param [in] status - CV2X radio status.
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to
     *          change and could break backwards compatibility.
     *
     * @deprecated use onStatusChanged(Cv2xStatusEx status)
     */
    virtual void onStatusChanged(Cv2xStatus status) {}

    /**
     * Called when the status of the CV2X radio has changed.
     *
     * @param [in] status - CV2X radio status.
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to
     *          change and could break backwards compatibility.
     */
    virtual void onStatusChanged(Cv2xStatusEx status) {}

    /**
     * Destructor for ICv2xListener
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to
     *          change and could break backwards compatibility.
     */
    virtual ~ICv2xListener() {}
};

/**
 * This function is called as a response to @ref startCv2x
 *
 * @param [in] error     - SUCCESS if Cv2x mode successfully started
 *                       - @ref SUCCESS
 *                       - @ref GENERIC_FAILURE
 *
 */
using StartCv2xCallback = std::function<void (telux::common::ErrorCode error)>;


/**
 * This function is called as a response to @ref stopCv2x
 *
 * @param [in] error     - SUCCESS if Cv2x mode successfully stopped
 *                       - @ref SUCCESS
 *                       - @ref GENERIC_FAILURE
 *
 */
using StopCv2xCallback = std::function<void (telux::common::ErrorCode error)>;


/**
 * This function is called as a response to @ref requestCv2xStatus
 *
 * @param [in] status    - Cv2x status
 * @param [in] error     - SUCCESS if Cv2x status was successully retrieved
 *                       - @ref SUCCESS
 *                       - @ref GENERIC_FAILURE
 *
 *
 * @deprecated use RequestCv2xStatusCallbackEx
 */
using RequestCv2xStatusCallback = std::function<void (Cv2xStatus status,
                                                      telux::common::ErrorCode error)>;

/**
 * This function is called as a response to @ref requestCv2xStatus
 *
 * @param [in] status    - Cv2x status
 * @param [in] error     - SUCCESS if Cv2x status was successully retrieved
 *                       - @ref SUCCESS
 *                       - @ref GENERIC_FAILURE
 *
 * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
 *         break backwards compatibility.
 */
using RequestCv2xStatusCallbackEx = std::function<void (Cv2xStatusEx status,
                                                        telux::common::ErrorCode error)>;


/**
 * This function is called with the response to @ref updateConfiguration
 *
 * @param [in] error     - SUCCESS if configuration was updated successfully
 *                       - @ref SUCCESS
 *                       - @ref GENERIC_FAILURE
 *
 */
using UpdateConfigurationCallback =
    std::function<void (telux::common::ErrorCode error)>;


/** @addtogroup telematics_cv2x
 * @{ */

/**
 * @brief      Cv2xRadioManager manages instances of Cv2xRadio
 */
class ICv2xRadioManager {
public:
    /**
     * Checks if the Cv2x Radio Manager is ready.
     *
     * @returns True if Cv2x Radio Manager is ready for service, otherwise
     * returns false.
     *
     */
    virtual bool isReady() = 0;

    /**
     * Wait for Cv2x Radio Manager to be ready.
     *
     * @returns A future that caller can wait on to be notified
     * when Cv2x Radio Manager is ready.
     *
     */
    virtual std::future<bool> onReady() = 0;

    /**
     * Get Cv2xRadio instance
     *
     * @param [in] category - Specifies the category of the client application.
     *                        This field is currently unused.
     *
     * @returns Reference to Cv2xRadio interface that corresponds to the Cv2x Traffic
     *          Category specified.
     */
    virtual std::shared_ptr<ICv2xRadio> getCv2xRadio(TrafficCategory category) = 0;

    /**
     * Put modem into CV2X mode.
     *
     * @param [in] cb      - Callback that is invoked when Cv2x mode is started
     *
     * @returns SUCCESS on success. Error status otherwise.
     */
    virtual telux::common::Status startCv2x(StartCv2xCallback cb) = 0;

    /**
     * Take modem outo of CV2X mode
     *
     * @param [in] cb      - Callback that is invoked when Cv2x mode is stopped
     *
     * @returns SUCCESS on success. Error status otherwise.
     */
    virtual telux::common::Status stopCv2x(StopCv2xCallback cb) = 0;

    /**
     * request CV2X status from modem
     *
     * @param [in] cb      - Callback that is invoked when Cv2x status is retrieved
     *
     * @returns SUCCESS on success. Error status otherwise.
     *
     * @deprecated use requestCv2xStatus(RequestCv2xCalbackEx)
     */
    virtual telux::common::Status requestCv2xStatus(RequestCv2xStatusCallback cb) = 0;

    /**
     * request CV2X status from modem
     *
     * @param [in] cb      - Callback that is invoked when Cv2x status is retrieved
     *
     * @returns SUCCESS on success. Error status otherwise.
     */
    virtual telux::common::Status requestCv2xStatus(RequestCv2xStatusCallbackEx cb) = 0;

    /**
     * Registers a listener for this manager.
     *
     * @param [in] listener - Listener that implements Cv2xListener interface.
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to
     *          change and could break backwards compatibility.
     */
    virtual telux::common::Status registerListener(std::weak_ptr<ICv2xListener> listener) = 0;

    /**
     * Deregisters a Cv2xListener for this manager.
     *
     * @param [in] listener - Previously registered CvListener that is to be
     *        deregistered.
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to
     *          change and could break backwards compatibility.
     */
    virtual telux::common::Status deregisterListener(std::weak_ptr<ICv2xListener> listener) = 0;

    /**
     * Updates CV2X configuration
     *
     * @param [in] configFilePath - Path to config file.
     * @param [in] cb             - Callback that is invoked when the send is complete.
     *                              This may be null.
     */
    virtual telux::common::Status updateConfiguration(const std::string & configFilePath,
                                                      UpdateConfigurationCallback cb) = 0;

    virtual ~ICv2xRadioManager() {}
};

/** @} */ /* end_addtogroup telematics_cv2x */

} // namespace cv2x

} // namespace telux

#endif // #ifndef CV2XRADIOMANAGER_HPP
