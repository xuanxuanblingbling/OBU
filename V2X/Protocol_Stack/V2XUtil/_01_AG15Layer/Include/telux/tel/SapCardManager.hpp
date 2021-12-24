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
 * @file       SapCardManager.hpp
 * @brief      SIM Access Profile (SAP) Manager is a primary interface for card operations in SAP
 *             mode. Unlike CardManager, each SapCardManager instance is associated with a
 *             particular slot ID. It allows operations like open, close, transmission of APDU,
 *             SIM power on/off/reset, card reader status, etc.
 */

#ifndef SAPCARDMANAGER_HPP
#define SAPCARDMANAGER_HPP

#include <vector>

#include "../../../../_01_AG15Layer/Include/telux/common/CommonDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/CardDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/PhoneDefines.hpp"

namespace telux {

namespace tel {

/** @addtogroup telematics_card
 * @{ */

// Forward declarations
class IAtrResponseCallback;
class ICardReaderCallback;
class ISapCardCommandCallback;

/**
 * Defines all SIM access profile (SAP) connection states.
 */
enum class SapState {
   SAP_STATE_NOT_ENABLED = 0x00,               /**< SAP connection not enabled */
   SAP_STATE_CONNECTING = 0x01,                /**< SAP State is connecting  */
   SAP_STATE_CONNECTED_SUCCESSFULLY = 0x02,    /**< SAP connection is successful */
   SAP_STATE_CONNECTION_ERROR = 0x03,          /**< SAP connection error  */
   SAP_STATE_DISCONNECTING = 0x04,             /**< SAP state is disconnecting */
   SAP_STATE_DISCONNECTED_SUCCESSFULLY = 0x05, /**< SAP state disconnection is successful */
};

/**
 * Indicates type of connection required, default behavior is to block a SAP connection
 * when a voice or data call is active.
 */
enum class SapCondition {
   SAP_CONDITION_BLOCK_VOICE_OR_DATA = 0x00, /**< Block a SAP connection when a voice or
                                                  data call is active (Default) */
   SAP_CONDITION_BLOCK_DATA = 0x01,          /**< Block a SAP connection
                                                  when a data call is active */
   SAP_CONDITION_BLOCK_VOICE = 0x02,         /**< Block a SAP connection when a voice
                                                  call is active */
   SAP_CONDITION_BLOCK_NONE = 0x03,          /**< Allow Sap connection in all cases */
};

/**
 * Structure contains identity of card reader status
 */
struct CardReaderStatus {
   int id;               /**< Card Reader ID */
   bool isRemovable;     /**< Card reader is removable */
   bool isPresent;       /**< Card reader is present */
   bool isID1size;       /**< Card reader present is ID-1 size*/
   bool isCardPresent;   /**<Card is present in reader */
   bool isCardPoweredOn; /**< Card in reader is powered*/
};

/** @} */ /* end_addtogroup telematics_card */

/**
 * This function is called with the response to requestSapState API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] sapState        @ref SapState of SIM access profile (SAP) connection
 * @param [in] error           Return code for whether the operation
 *                             succeeded or failed
 *
 */

using SapStateResponseCallback
   = std::function<void(SapState sapState, telux::common::ErrorCode error)>;

/** @addtogroup telematics_card
 * @{ */

/**
 * @brief ISapCardManager provide APIs for SAP related operations.
 */
class ISapCardManager {
public:
   /**
    * Get SIM access profile (SAP) client connection state.
    *
    * @param [out] sapState   @ref SapState of the SIM Card
    *
    * @returns Status of getState i.e. success or suitable status code.
    *
    * @deprecated Use requestSapState() API below to get SAP state
    */
   virtual telux::common::Status getState(SapState &sapState) = 0;

   /**
    * Get SIM access profile(SAP) client connection state.
    *
    * @param [out] callback   Callback function pointer to get the response of requestSapState.
    *
    * @returns Status of requestSapState i.e. success or suitable status code.
    */
   virtual telux::common::Status requestSapState(SapStateResponseCallback callback) = 0;

   /**
    * Establishes SIM access profile (SAP) client connection with SIM Card.
    *
    * @param [in] sapCondition    Condition to enable sap connection.
    * @param [in] callback        Optional callback to get the response of open sap connection
    *                             request or possible error codes i.e.
    *                             - @ref SUCCESS
    *                             - @ref INTERNAL
    *                             - @ref NO_MEMORY
    *                             - @ref INVALID_ARG
    *                             - @ref MISSING_ARG
    *
    * @returns Status of openConnection i.e. success or suitable status code.
    */
   virtual telux::common::Status
      openConnection(SapCondition sapCondition = SapCondition::SAP_CONDITION_BLOCK_VOICE_OR_DATA,
                     std::shared_ptr<telux::common::ICommandResponseCallback> callback = nullptr)
      = 0;

   /**
    * Releases a SAP connection to SIM Card.
    *
    * @param [in] callback    Optional callback to get the response of close sap connection
    *                         request or possible error codes i.e.
    *                         - @ref SUCCESS
    *                         - @ref INTERNAL
    *                         - @ref NO_MEMORY
    *                         - @ref INVALID_ARG
    *                         - @ref MISSING_ARG

    * @returns Status of closeConnection i.e. success or suitable status code
    */
   virtual telux::common::Status
      closeConnection(std::shared_ptr<telux::common::ICommandResponseCallback> callback = nullptr)
      = 0;

   /**
    * Request for SAP Answer To Reset command.
    *
    * @param [in] callback    Optional callback to get the response of requestAtr.
    *
    * @returns Status of requestAtr i.e. success or suitable status code.
    */
   virtual telux::common::Status requestAtr(std::shared_ptr<IAtrResponseCallback> callback
                                            = nullptr)
      = 0;

   /**
    * Send the Apdu on SAP mode.
    *
    * @param [in] cla           Class of the APDU command.
    * @param [in] instruction   Instruction of the APDU command.
    * @param [in] p1            Instruction Parameter 1 value of the APDU command.
    * @param [in] p2            Instruction Parameter 1  value of the APDU command.
    * @param [in] lc            Number of bytes present in the data field of the APDU command.
    *                           If lc is negative, a 4 byte APDU is sent to the SIM.
    * @param [in] data          List of data to be sent with the APDU.
    * @param [in] le            Maximum number of bytes expected in the data field of the
    *                           response to the command.
    * @param [in] callback      Optional callback to send APDU in SAP mode.
    *
    * @returns Status of transmitApdu i.e. success or suitable status code.
    */
   virtual telux::common::Status transmitApdu(uint8_t cla, uint8_t instruction, uint8_t p1,
                                              uint8_t p2, uint8_t lc, std::vector<uint8_t> data,
                                              uint8_t le = 0,
                                              std::shared_ptr<ISapCardCommandCallback> callback
                                              = nullptr)
      = 0;

   /**
    * Send the SAP SIM power off request.
    *
    * @param [in] callback    Optional callback to get the response for SIM power off.
    *
    * @returns Status of requestSimPowerOff i.e. success or suitable status code.
    */
   virtual telux::common::Status requestSimPowerOff(
      std::shared_ptr<telux::common::ICommandResponseCallback> callback = nullptr)
      = 0;

   /**
    * Send the SAP SIM power on request.
    *
    * @param [in] callback    Optional callback to get the response for SIM power on.
    *
    * @returns Status of requestSimPowerOn i.e. success or suitable status code.
    */
   virtual telux::common::Status
      requestSimPowerOn(std::shared_ptr<telux::common::ICommandResponseCallback> callback = nullptr)
      = 0;

   /**
    * Send the SAP SIM reset request.
    *
    * @param [in] callback    Optional callback to get the response for SIM reset
    *
    * @returns Status of requestSimReset i.e. success or suitable status code.
    */
   virtual telux::common::Status
      requestSimReset(std::shared_ptr<telux::common::ICommandResponseCallback> callback = nullptr)
      = 0;

   /**
    * Send the SAP Card Reader Status request command.
    *
    * @param [in] callback    Optional callback to get the response for card reader status
    *
    * @returns Status of requestCardReaderStatus i.e. success or suitable status code.
    */
   virtual telux::common::Status
      requestCardReaderStatus(std::shared_ptr<ICardReaderCallback> callback = nullptr)
      = 0;

   /**
    * Get associated slot id for the SapCardManager.
    *
    * @returns SlotId
    */
   virtual int getSlotId() = 0;

   virtual ~ISapCardManager(){};

};  // end of ISapCardManager

class IAtrResponseCallback : public telux::common::ICommandCallback {
public:
   /**
    * This function is called in response to requestAtr() request.
    *
    * @param [in] responseAtr    response ATR values
    * @param [in] error          @ref ErrorCode of the request
    *                            possible error codes are
    *                            - @ref SUCCESS
    *                            - @ref INTERNAL
    *                            - @ref NO_MEMORY
    *                            - @ref INVALID_ARG
    *                            - @ref MISSING_ARG
   */
   virtual void atrResponse(std::vector<int> responseAtr, telux::common::ErrorCode error) = 0;
};

class ISapCardCommandCallback : public telux::common::ICommandCallback {
public:
   /**
    * This function is called when SIM Card transmit APDU on SAP mode.
    *
    * @param [in] result   @ref IccResult of transmit APDU command
    * @param [in] error    @ref ErrorCode of the request,
    *                      possible error codes are
    *                      - @ref SUCCESS
    *                      - @ref INTERNAL
    *                      - @ref NO_MEMORY
    *                      - @ref INVALID_ARG
    *                      - @ref MISSING_ARG
    */
   virtual void onResponse(IccResult result, telux::common::ErrorCode error) = 0;
};

class ICardReaderCallback : public telux::common::ICommandCallback {
public:
   /**
    * This function is called in response to requestCardReaderStatus() method.
    *
    * @param [in] cardReaderStatus   Structure contains the identity of the card reader
    * @param [in] error              @ref ErrorCode of the request
    *
    */
   virtual void cardReaderResponse(CardReaderStatus cardReaderStatus,
                                   telux::common::ErrorCode error)
      = 0;
};

/** @} */ /* end_addtogroup telematics_card */

}  // End of namespace tel

}  // End of namespace telux

#endif
