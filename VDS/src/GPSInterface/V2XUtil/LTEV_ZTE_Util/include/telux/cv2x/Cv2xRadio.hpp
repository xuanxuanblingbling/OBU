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
* @file       Cv2xRadio.hpp
*
* @brief      Cv2xRadio class encapsulates a CV2X radio (channel) resource.
*/

#ifndef CV2XRADIO_HPP
#define CV2XRADIO_HPP


#include <telux/cv2x/Cv2xFactory.hpp>
#include <telux/cv2x/Cv2xRadioManager.hpp>
#include <telux/cv2x/Cv2xRadioListener.hpp>
#include <telux/cv2x/Cv2xRxSubscription.hpp>
#include <telux/cv2x/Cv2xTxFlow.hpp>

#include <future>
#include <memory>

#include <telux/common/CommonDefines.hpp>

namespace telux {
namespace cv2x {

class ICv2xRadioListener;
class ICv2xRxSubscription;
class ICv2xTxFlow;


/**
 * This function is called as a response to @ref createRxSubscription.
 *
 * @param [in] rxSub       - Rx Subscription
 * @param [in] error       - Indicates whether socket creation succeeded
 *                         - @ref SUCCESS
 *                         - @ref GENERIC_FAILURE
 */
using CreateRxSubscriptionCallback =
    std::function<void (std::shared_ptr<ICv2xRxSubscription> rxSub,
                        telux::common::ErrorCode error)>;

/**
 * This function is called as a  response to @ref createTxSpsFlow
 *
 * @param [in] spsFlow        - Sps flow
 * @param [in] eventFlow      - Optional event flow. Will be nullptr if event flow was
 *                              not specified in the request
 * @param [in] error          - Indicates whether Tx SPS flow creation succeeded
 *                            - @ref SUCCESS
 *                            - @ref GENERIC_FAILURE
 * @param [in] error          - Indicates whether optional Tx Event flow creation succeeded
 *                            - @ref SUCCESS
 *
 */
using CreateTxSpsFlowCallback = std::function<void (std::shared_ptr<ICv2xTxFlow> txSpsFlow,
                                                    std::shared_ptr<ICv2xTxFlow> txEventFlow,
                                                    telux::common::ErrorCode spsError,
                                                    telux::common::ErrorCode eventError)>;

/**
 * This function is called with the response to @ref createTxEventFlow
 *
 * @param [in] txEventFlow    - Event flow
 * @param [in] error          - Indicates whether Tx event flow creation succeeded
 *                            - @ref SUCCESS
 *                            - @ref GENERIC_FAILURE
 */
using CreateTxEventFlowCallback = std::function<void (std::shared_ptr<ICv2xTxFlow> txEventFlow,
                                                      telux::common::ErrorCode error)>;

/**
 * This function is called with the response to @ref closeTxFlow.
 *
 * @param [in] txFlow    - Closed tx flow
 * @param [in] error     - Indicates whether close operation succeeded
 *                       - @ref SUCCESS
 *                       - @ref GENERIC_FAILURE
 */
using CloseTxFlowCallback = std::function<void (std::shared_ptr<ICv2xTxFlow> txFlow,
                                                telux::common::ErrorCode error)>;

/**
 * This function is called with the response to @ref closeRxSubscription.
 *
 * @param [in] rxSub     - Closed rx subscription
 * @param [in] error     - Indicates whether Rx subscription close succeeded
 *                       - @ref SUCCESS
 *                       - @ref GENERIC_FAILURE
 */
using CloseRxSubscriptionCallback =
    std::function<void (std::shared_ptr<ICv2xRxSubscription> rxSub,
                        telux::common::ErrorCode error)>;


/**
 * This function is called with the response to @ref changeSpsFlowInfo.
 *
 * @param [in] txFlow    - Sps flow that requested reservation change
 * @param [in] error     - SUCCESS if Tx reservation change succeeded
 *                       - @ref SUCCESS
 *                       - @ref GENERIC_FAILURE
 */
using ChangeSpsFlowInfoCallback =
    std::function<void (std::shared_ptr<ICv2xTxFlow> txFlow, telux::common::ErrorCode error)>;

/**
 * This function is called with the response to @ref requestSpsFlowInfo.
 *
 * @param [in] txFlow      - SPS flow that requested info
 * @param [in] spsInfo     - SPS flow reservation info
 * @param [in] error       - SUCCESS if Tx reservation change succeeded
 *                         - @ref SUCCESS
 *                         - @ref GENERIC_FAILURE
 */
using RequestSpsFlowInfoCallback =
    std::function<void (std::shared_ptr<ICv2xTxFlow> txFlow,
                        const SpsFlowInfo & spsInfo,
                        telux::common::ErrorCode error)>;
/**
 * This function is called with the response to @ref changeEventFlowInfo.
 *
 * @param [in] txFlow    - Event flow that requested reservation change
 * @param [in] error     - SUCCESS if Tx parameter change succeeded
 *                       - @ref SUCCESS
 *                       - @ref GENERIC_FAILURE
 */
using ChangeEventFlowInfoCallback =
    std::function<void (std::shared_ptr<ICv2xTxFlow> txFlow, telux::common::ErrorCode error)>;

/**
 * This function is called with the response to @ref requestCapabilities.
 *
 * @param [in] capabilities     - Capability info
 * @param [in] error       - SUCCESS if capabilities request succeeded
 *                         - @ref SUCCESS
 *                         - @ref GENERIC_FAILURE
 *
 * @note   Eval: This is a new API and is being evaluated.It is subject to change and could
 *         break backwards compatibility.
 */
using RequestCapabilitiesCallback =
    std::function<void(const Cv2xRadioCapabilities & capabilities,
                       telux::common::ErrorCode error)>;

/**
 * This function is called with the response to @ref requestDataSessionSettings.
 *
 * @param [in] settings     - Data session settings
 * @param [in] error       - SUCCESS if data session settings request succeeded
 *                         - @ref SUCCESS
 *                         - @ref GENERIC_FAILURE
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to change and could
 *         break backwards compatibility.
 */
using RequestDataSessionSettingsCallback =
    std::function<void (const DataSessionSettings & settings,
                        telux::common::ErrorCode error)>;
/**
 * This function is called with the response to @ref updateTrustedUEList.
 *
 * @param [in] error       - SUCCESS if update succeeded
 *                         - INVALID_ARGUMENTS if trustedUEs or maliciousIds
 *                           length greater than maximum value
 *                         - @ref SUCCESS
 *                         - @ref GENERIC_FAILURE
 *                         - @ref INVALID_ARGUMENTS
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to change and could
 *         break backwards compatibility.
 */
using UpdateTrustedUEListCallback =
    std::function<void(telux::common::ErrorCode error)>;

/**
 * This function is called with the response to updateSrcL2Info.
 *
 * @param [in] error       - SUCCESS if Tx reservation change succeeded
 *                         - @ref SUCCESS
 *                         - @ref GENERIC_FAILURE
 */
using UpdateSrcL2InfoCallback =
    std::function<void (telux::common::ErrorCode error)>;

/** @addtogroup telematics_cv2x
 * @{ */

/**
 * This is class encapsulates a Cv2xRadio interface.
 *
 * Returned from @ref getCv2xRadio in Cv2xFactory
 */
class ICv2xRadio {
public:

    /**
     * Get the capabilities of this Cv2xRadio.
     *
     * @returns Cv2xRadioCapabilities - Contains capabilities of this Cv2xRadio.
     *
     * @deprecated Use requestCapabilities() API
     */
    virtual Cv2xRadioCapabilities getCapabilities() const = 0;

    /**
     * Returns true if the radio interface has completed initialization.
     *
     * @returns True if ready. False otherwise.
     */
    virtual bool isReady() const = 0;

    /**
     * Returns a future that indicated if the radio interface is ready or if
     * radio failed to initialize.
     *
     * @returns SUCCESS if Cv2xRadio initialization was successful. Otherwise it
     *          returns an Error Code.
     */
    virtual std::future<telux::common::Status> onReady() = 0;

    /**
     * Registers a listener for this Cv2xRadio.
     *
     * @param [in] listener - Listener that implements Cv2xRadioListener
     *                        interface.
     */
    virtual telux::common::Status registerListener(
        std::weak_ptr<ICv2xRadioListener> listener) = 0;

    /**
     * Deregisters a listener from this Cv2xRadio.
     *
     * @param [in] listener - Previously registered Cv2xRadioListener that is
     *                        to be deregistered.
     */
    virtual telux::common::Status deregisterListener(
        std::weak_ptr<ICv2xRadioListener> listener) = 0;

    /**
     * Creates and initializes a new Rx subscription which will be returned
     * in the user-supplied callback.
     *
     * @param [in] ipType  - IP traffic type (IP or NON-IP)
     * @param [in] port    - Rx port number
     * @param [in] cb      - Callback function that is invoked when socket
     *                       creation is complete.
     *
     * @returns SUCCESS on success. Error status otherwise.
     *
     * @dependencies The interface must be pre-initialized with init().
     *
     */
    virtual telux::common::Status createRxSubscription(
        TrafficIpType ipType,
        uint16_t port,
        CreateRxSubscriptionCallback cb) = 0;

    /**
     * Creates a Tx SPS flow with the specified IP type, serviceId, and other
     * parameters specified in reservation. Additionally, an option event flow
     * will be created with the same IP type and serviceId. A Tx socket will
     * be created and initialized for the SPS flow. A Tx socket will be created
     * and initialized for the event flow if the optional event flow is specified.
     *
     * @param [in] ipType            - IP traffic type (IP or NON-IP)
     * @param [in] serviceId         - ID used for transmissions that will be
     *                                 mapped to an L2 destination address.
     *                                 Variable length 4-byte PSID or ITS_AID, or
     *                                 another service ID.
     * @param [in] spsInfo           - SPS reservation parameters.
     * @param [in] spsPort           - Requested source port number for the
     *                                 bandwidth reserved SPS transmissions.
     * @param [in] eventSrcPortValid - True if an optional event flow is desired. If
     *                                 this field is left false, the event flow will
     *                                 not be created.
     * @param [in] eventSrcPort      - Requested source port number for the optional
     *                                 event flow.
     * @param [in] cb                - Callback function that is invoked when socket
     *                                 creation is complete. This must not be null.
     *
     * @par This caller is expected to identify two unused local port numbers
     * to use for binding: one for the event-driven flow and one for the SPS
     * flow.
     *
     * @returns SUCCESS upon success. Error status otherwise.
     */
    virtual telux::common::Status createTxSpsFlow(
        TrafficIpType ipType,
        uint32_t serviceId,
        const SpsFlowInfo & spsInfo,
        uint16_t spsSrcPort,
        bool eventSrcPortValid,
        uint16_t eventSrcPort,
        CreateTxSpsFlowCallback cb) = 0;

    /**
     * Creates an event flow. An associated Tx socket will be created and
     * initialized.
     *
     * @param [in] ipType         - IP traffic type (IP or NON-IP)
     * @param [in] serviceId      - ID used for transmissions that will be
     *                              mapped to an L2 destination address.
     *                              Variable length 4-byte PSID or ITS_AID, or
     *                              another service ID.
     * @param [in] eventSrcPort   - Local port number to which the socket is
     *                              bound. Used for transmissions of this ID.
     * @param [in] cb             - Callback function that is invoked when socket
     *                              creation is complete. This must not be null.
     *
     * @detdesc This function is used only for TX when no periodicity is
     *          available for the application type. If your transmit data
     *          periodicity is known, use createTxSpsFlow() instead.
     *
     * @par These even-driven sockets pay attention to the QoS parameters in
     *      the IP socket.
     *
     * @returns SUCCESS upon success. Error status otherwise.
     */
    virtual telux::common::Status createTxEventFlow(
        TrafficIpType ipType,
        uint32_t serviceId,
        uint16_t eventSrcPort,
        CreateTxEventFlowCallback cb) = 0;

    /**
     * Creates an event flow. An associated Tx socket will be created and
     * initialized.
     *
     * @param [in] ipType         - IP traffic type (IP or NON-IP)
     * @param [in] serviceId      - ID used for transmissions that will be
     *                              mapped to an L2 destination address.
     *                              Variable length 4-byte PSID or ITS_AID, or
     *                              another service ID.
     * @param [in] flowInfo       - Flow configuration parameters
     * @param [in] eventSrcPort   - Local port number to which the socket is
     *                              bound. Used for transmissions of this ID.
     * @param [in] cb             - Callback function that is invoked when socket
     *                              creation is complete. This must not be null.
     *
     * @detdesc This function is used only for TX when no periodicity is
     *          available for the application type. If your transmit data
     *          periodicity is known, use createTxSpsFlow() instead.
     *
     * @par These even-driven sockets pay attention to the QoS parameters in
     *      the IP socket.
     *
     * @returns SUCCESS upon success. Error status otherwise.
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to
     *          change and could break backwards compatibility.
     */
    virtual telux::common::Status createTxEventFlow(
        TrafficIpType ipType,
        uint32_t serviceId,
        const EventFlowInfo & flowInfo,
        uint16_t eventSrcPort,
        CreateTxEventFlowCallback cb) = 0;

    /**
     * Closes the RxSubscription and frees resources (such as the Rx socket) associated
     * with it.
     *
     * @param [in] rxSub - RxSubscription to close
     * @param [in] cb    - Callback that is invoked when socket close is complete.
     *                     This may be null.
     *
     * @returns SUCCESS if no error occurred.
     */
    virtual telux::common::Status closeRxSubscription(std::shared_ptr<ICv2xRxSubscription> rxSub,
                                                      CloseRxSubscriptionCallback cb) = 0;

    /**
     * Closes the TxFlow and frees resources associated with it (such as reserved
     * SPS bandwidth contracts and sockets). This function works on both SPS and event
     * flows.
     *
     * @param [in] txFlow  - Tx (SPS or event) flow to close.
     * @param [in] cb      - Callback that is invoked when Tx flow close is complete.
     *                       This may be null.
     *
     * @returns SUCCESS if no error occurred.
     */
    virtual telux::common::Status closeTxFlow(std::shared_ptr<ICv2xTxFlow> txFlow,
                                              CloseTxFlowCallback cb) = 0;

    /**
     * Request to change TX SPS Flow reservation parameters.
     *
     * @param [in] txFlow       - Tx SPS flow
     * @param [in] spsInfo      - Desired SPS reservation parameters
     * @param [in] cb           - Callback that is invoked upon reservation change. This
     *                            may be null.
     *
     * @returns SUCCESS if no error occurred.
     */
    virtual telux::common::Status changeSpsFlowInfo(
        std::shared_ptr<ICv2xTxFlow> txFlow,
        const SpsFlowInfo & spsInfo,
        ChangeSpsFlowInfoCallback cb) = 0;

    /**
     * Request SPS flow info.
     *
     * @param [in] sock         - Tx SPS flow
     * @param [in] cb           - Callback that will be invoked and returns the SPS info.
     *                            Must not be null.
     *
     * @returns SUCCESS if no error occurred.
     */
    virtual telux::common::Status requestSpsFlowInfo(
        std::shared_ptr<ICv2xTxFlow> txFlow,
        RequestSpsFlowInfoCallback cb) = 0;

    /**
     * Request to change TX Event Flow reservation parameters.
     *
     * @param [in] txFlow       - Tx Event flow
     * @param [in] flowInfo     - Desired Event flow parameters
     * @param [in] cb           - Callback that is invoked upon parameter
     *                            change. This may be null.
     *
     * @returns SUCCESS if no error occurred.
     */
    virtual telux::common::Status changeEventFlowInfo(
        std::shared_ptr<ICv2xTxFlow> txFlow,
        const EventFlowInfo & flowInfo,
        ChangeEventFlowInfoCallback cb) = 0;

    /**
     * Request modem Cv2x capability information.
     *
     * @param [in] cb           - Callback that will be invoked and returns the
     *                            capability info. Must not be null.
     *
     * @returns SUCCESS if no error occurred.
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to
     *          change and could break backwards compatibility.
     */
    virtual telux::common::Status requestCapabilities(
        RequestCapabilitiesCallback cb) = 0;

    /**
     * Request data session settings currently in use.
     *
     * @param [in] cb           - Callback that will be invoked and returns the
     *                            data session settings. Must not be null.
     *
     * @returns SUCCESS if no error occurred.
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to
     *          change and could break backwards compatibility.
     */
    virtual telux::common::Status requestDataSessionSettings(
        RequestDataSessionSettingsCallback cb) = 0;

    /**
     * Requests modem to change L2 info.
     *
     * @param  [in] cb          - Callback that will be invoked and returns status.
     *                            Must not be null.
     *
     * @returns SUCCESS if no error occurred.
     */
    virtual telux::common::Status updateSrcL2Info(UpdateSrcL2InfoCallback cb) = 0;

    /**
     * Send request to modem to update the list of malicious UE source IDs and
     * trusted UE source IDs with corresponding confidence information.
     *
     * @param  [in] infoList    - Trusted and malicious UE information list
     * @param  [in] cb          - Callback that will be invoked and returns status.
     *                            Must not be null.
     *
     * @returns SUCCESS if no error occurred.
     *
     * @note    Eval: This is a new API and is being evaluated.It is subject to
     *          change and could break backwards compatibility.
     */
    virtual telux::common::Status updateTrustedUEList(
        const TrustedUEInfoList & infoList,
        UpdateTrustedUEListCallback cb) = 0;

    /**
     * Destructor for ICv2xRadio
     */
    virtual ~ICv2xRadio(){}
};

/** @} */ /* end_addtogroup telematics_cv2x */

} // namespace cv2x

} // namespace telux

#endif // #ifndef CV2XRADIO_HPP
