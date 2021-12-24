/*
 *  Copyright (c) 2017-2019, The Linux Foundation. All rights reserved.
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
 * @file       CardDefines.hpp
 * @brief      CardDefines provides the enumerations required for Card Services
 */

#ifndef CARDDEFINES_HPP
#define CARDDEFINES_HPP

#include <string>
#include <sstream>
#include <vector>

#include <telux/common/CommonDefines.hpp>

namespace telux {

namespace tel {

/** @addtogroup telematics_card
 * @{ */

/**
 * Defines all state of Card like absent, present etc
 */
enum class CardState {
   CARDSTATE_UNKNOWN = -1,   /**< Unknown card state */
   CARDSTATE_ABSENT = 0,     /**< Card is absent */
   CARDSTATE_PRESENT = 1,    /**< Card is present */
   CARDSTATE_ERROR = 2,      /**< Card is having error, either card is removed and not readable */
   CARDSTATE_RESTRICTED = 3, /**< Card is present but not usable due to carrier restrictions.*/
};

/**
 * Defines all types of card locks which uses in PIN management APIs
 */
enum class CardLockType {
   PIN1 = 0, /**<Lock type is PIN1 */
   PIN2 = 1, /**<Lock type is PIN2 */
   PUK1 = 2, /**<Lock type is Pin Unblocking Key1 */
   PUK2 = 3, /**<Lock type is Pin Unblocking Key2 */
   FDN  = 4   /**<Lock type is Fixed Dialing Number */
};

/**
 * Defines all type of UICC application such as SIM, RUIM, USIM, CSIM and ISIM.
 */
enum AppType {
   APPTYPE_UNKNOWN = 0, /**< Unknown application type */
   APPTYPE_SIM = 1,     /**< UICC application type is SIM */
   APPTYPE_USIM = 2,    /**< UICC application type is USIM */
   APPTYPE_RUIM = 3,    /**< UICC application type is RSIM */
   APPTYPE_CSIM = 4,    /**< UICC application type is CSIM */
   APPTYPE_ISIM = 5,    /**< UICC application type is ISIM */
};

/**
 * Defines all application states.
 */
enum AppState {
   APPSTATE_UNKNOWN = 0,            /**< Unknown application state */
   APPSTATE_DETECTED = 1,           /**< application state detected */
   APPSTATE_PIN = 2,                /**< If PIN1 or UPin is required */
   APPSTATE_PUK = 3,                /**< If PUK1 or Puk for UPin is required */
   APPSTATE_SUBSCRIPTION_PERSO = 4, /**< PersoSubstate should be look at
                                         when application state is assigned to this value */
   APPSTATE_READY = 5,              /**< application State is ready */
};

/**
 * The APDU response with status for transmit APDU operation.
 */
struct IccResult {
   int sw1;               /**< Status word 1 for command processing status */
   int sw2;               /**< Status word 2 for command processing qualifier */
   std::string payload;   /**< response as a hex string */
   std::vector<int> data; /**< vector of raw data received as part of response
                               to the card services request */
   const std::string toString() const {
      std::stringstream ss;
      ss << "sw1: " << sw1 << ", sw2: " << sw2 << ", payload: " << payload << ", data:";
      for(auto &i : data) {
         ss << i << " ";
      }
      return ss.str();
   };
};
/** @} */ /* end_addtogroup telematics_card */

}  // End of namespace tel

}  // End of namespace telux

#endif  // CARDDEFINES_HPP
