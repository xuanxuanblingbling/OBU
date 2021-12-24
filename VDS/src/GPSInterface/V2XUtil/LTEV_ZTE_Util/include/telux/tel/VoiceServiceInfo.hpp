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
 * @file       VoiceServiceInfo.hpp
 *
 * @brief      VoiceServiceInfo is a container class for obtaining serving state
 *             details like phone is registered to home network, roaming,
 *             in service, out of service or only emergency calls allowed.
 */
#ifndef VOICESERVICEINFO_HPP
#define VOICESERVICEINFO_HPP

#include <memory>

namespace telux {
namespace tel {

/** @addtogroup telematics_phone
 * @{ */

/**
 * Defines the voice service states
 */
enum class VoiceServiceState {
   NOT_REG_AND_NOT_SEARCHING = 0, /**< Not registered, MT is not currently
                                       searching a new operator to
                                       register */
   REG_HOME = 1,                  /**< Registered, home network */
   NOT_REG_AND_SEARCHING = 2,     /**< Not registered, but MT is currently searching
                                       a new operator to register */
   REG_DENIED = 3,                /**< Registration denied */
   UNKNOWN = 4,                   /**< Unknown */
   REG_ROAMING = 5,               /**< Registered, roaming */
   NOT_REG_AND_EMERGENCY_AVAILABLE_AND_NOT_SEARCHING = 10, /**<  Same as NOT_REG_AND_NOT_SEARCHING
                                                                 but indicates that emergency
                                                                 calls are enabled */
   NOT_REG_AND_EMERGENCY_AVAILABLE_AND_SEARCHING = 12,     /**< Same as NOT_REG_AND_SEARCHING
                                                                but indicates that emergency
                                                                calls are enabled */
   REG_DENIED_AND_EMERGENCY_AVAILABLE = 13,                /**< Same as REG_DENIED but indicates
                                                                that emergency calls are
                                                                enabled */
   UNKNOWN_AND_EMERGENCY_AVAILABLE = 14,                   /**< Same as UNKNOWN but indicates that
                                                                emergency calls are enabled */
};

/**
 * Defines the voice service denial cause why voice service state registration
 * was denied
 * See 3GPP TS 24.008, 10.5.3.6 and Annex G.
 */
enum class VoiceServiceDenialCause {
   UNDEFINED = -1,   /**< Undefined */
   GENERAL = 0,      /**< General */
   AUTH_FAILURE = 1, /**< Authentication Failure */

   // Cause codes related to MS identification
   IMSI_UNKNOWN = 2,      /**< IMSI unknown in HLR */
   ILLEGAL_MS = 3,        /**< Illegal Mobile Station (MS), network
                                refuses service to the MS either because an
                                identity of the MS is not acceptable to the network
                                or because the MS does not pass the authentication
                                check */
   IMSI_UNKNOWN_VLR = 4,  /**< IMSI unknown in Visitors Location Register (VLR) */
   IMEI_NOT_ACCEPTED = 5, /**< Network does not accept emergency call
                               establishment using an IMEI or not accept attach
                               procedure for emergency services using an IMEI */
   ILLEGAL_ME = 6,        /**< ME used is not acceptable to the network */

   // Cause codes related non-GPRS and GPRS services (GMM)
   GPRS_SERVICES_NOT_ALLOWED = 7,      /**< Not allowed to operate GPRS services. */
   GPRS_NON_GPRS_NOT_ALLOWED = 8,      /**< Not allowed to operate either GPRS or
                                             non-GPRS services */
   MS_IDENTITY_FAILED = 9,             /**< the network cannot derive the MS's identity
                                             from the P-TMSI/GUTI. */
   IMPLICITLY_DETACHED = 10,           /**< network has implicitly detached the MS */
   GPRS_NOT_ALLOWED_IN_PLMN = 14,      /**< GPRS services not allowed in this PLMN */
   MSC_TEMPORARILY_NOT_REACHABLE = 16, /**< MSC temporarily not reachable */
   SMS_PROVIDED_VIA_GPRS = 28,         /**< SMS provided via GPRS in this routing area */
   NO_PDP_CONTEXT_ACTIVATED = 40,      /**< No PDP context activated */

   // Cause codes related to subscription options
   PLMN_NOT_ALLOWED = 11,          /**<  if the network initiates a detach request or UE
                                         requests a services, in a PLMN where
                                         the MS, by subscription or due to operator
                                         determined barring is not allowed to operate. */
   LOCATION_AREA_NOT_ALLOWED = 12, /**<  network initiates a detach request, in a
                                         location area where the HPLMN determines that
                                         the MS, by subscription, is not allowed to
                                         operate  or roaming subscriber the subscriber is
                                         denied service even if other PLMNs are available
                                         on which registration was possible*/
   ROAMING_NOT_ALLOWED = 13,       /**< Roaming not allowed in this Location Area */
   NO_SUITABLE_CELLS = 15,         /**< No Suitable Cells in this Location Area */
   NOT_AUTHORIZED = 25,            /**< Not Authorized for this CSG */

   // Causes related to PLMN specific network failures and
   // congestion/Authentication Failures
   NETWORK_FAILURE = 17,                 /**< Network Failure */
   MAC_FAILURE = 20,                     /**< MAC failure */
   SYNC_FAILURE = 21,                    /**< USIM detects that the SQN in the
                                               AUTHENTICATION REQUEST or
                                               AUTHENTICATION_AND_CIPHERING REQUEST
                                               message is out of range */
   CONGESTION = 22,                      /**< network cannot serve a request from the MS
                                              because of congestion */
   GSM_AUTHENTICATION_UNACCEPTABLE = 23, /**< GSM Authentication unacceptable */

   // Causes related to nature of request
   SERVICE_OPTION_NOT_SUPPORTED = 32, /**< Service option not supported */
   SERVICE_OPTION_NOT_SUBCRIBED = 33, /**< Requested service option not subscribed */
   SERVICE_OPTION_OUT_OF_ORDER = 34,  /**< Service option temporarily out of order */
   CALL_NOT_IDENTIFIED = 38,          /**< Call cannot be identified */
   RETRY_FOR_NEW_CELL = 48,           /**< Retry upon entry into a new cell */

   // Causes related to invalid messages
   INCORRECT_MESSAGE = 95,           /**< Semantically incorrect message */
   INVALID_INFO = 96,                /**< Invalid mandatory information */
   MSG_TYPE_NOT_IMPLEMENTED = 97,    /**< Message type non-existent or not implemented */
   MSG_NOT_COMPATIBLE = 98,          /**< Message not compatible with protocol state */
   INFO_NOT_IMPLEMENTED = 99,        /**< Information element non-existent or not implemented */
   CONDITIONAL_IE_ERROR = 100,       /**< Conditional IE error */
   PROTOCOL_ERROR_UNSPECIFIED = 111, /**< Protocol error, unspecified */
};

/**
 * VoiceServiceInfo is a container class for obtaining serving state details
 * like phone is registered to home network, roaming, in service, out of
 * service or only emergency calls allowed.
 */
class VoiceServiceInfo {
public:
   VoiceServiceInfo(VoiceServiceState voiceServiceState, VoiceServiceDenialCause denialCause);

   /**
    * Get voice service state.
    *
    * @returns @ref VoiceServiceState
    */
   VoiceServiceState getVoiceServiceState();

   /**
    * Get Voice service denial cause
    *
    * @returns @ref VoiceServiceDenialCause
    */
   VoiceServiceDenialCause getVoiceServiceDenialCause();

   /**
    * Check if phone service is in emergency mode (i.e Only emergency numbers are
    * allowed)
    */
   bool isEmergency();

   /**
    * Check if phone is registered to home network or roaming network, phone is
    * in service mode
    */
   bool isInService();

   /**
    * check if phone not registered, phone is in out of service mode
    */
   bool isOutOfService();

private:
   VoiceServiceState voiceServiceState_;
   VoiceServiceDenialCause denialCause_;
};

/** @} */ /* end_addtogroup telematics_phone */

}  // End of namespace tel
}  // End of namespace telux

#endif
