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
 * @file       CardManager.hpp
 * @brief      Card Manager is a primary interface that is aware of all the UICC cards on a device.
 *             It provide APIs to enumerate cards, retrieve number of slots, get card state.
 */

#ifndef CARDMANAGER_HPP
#define CARDMANAGER_HPP

#include <future>
#include <memory>
#include <string>
#include <vector>

#include "../../../../_01_AG15Layer/Include/telux/common/CommonDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/CardApp.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/CardDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/tel/PhoneDefines.hpp"

namespace telux {

namespace tel {

/** @addtogroup telematics_card
 * @{ */

// Forward declarations
class ICardChannelCallback;
class ICardCommandCallback;
class ICardListener;
class ICard;

/**
 * ICardManager provide APIs for slot count, retrieve slot ids, get card state and get card.
 */
class ICardManager {
public:
   /**
    * Checks the status of telephony subsystems and returns the result.
    *
    * @returns If true then CardManager is ready for service.
    */
   virtual bool isSubsystemReady() = 0;

   /**
    * Wait for telephony subsystem to be ready.
    *
    * @returns A future that caller can wait on to be notified
    * when card manager is ready.
    */
   virtual std::future<bool> onSubsystemReady() = 0;

   /**
    * Get SIM slot count.
    *
    * @param [out] count  SIM slot count.
    *
    * @returns Status of getSlotCount i.e. success or suitable status code.
    */
   virtual telux::common::Status getSlotCount(int &count) = 0;

   /**
    * Get list of SIM slots.
    *
    * @param [out] slotIds  List of SIM slot ids.
    *
    * @returns Status of getSlotIds i.e. success or suitable status code.
    */
   virtual telux::common::Status getSlotIds(std::vector<int> &slotIds) = 0;

   /**
    * Get the Card corresponding to SIM slot.
    *
    * @param [in] slotId    Slot id corresponding to the card.
    * @param [out] status   Status of getCard i.e. success or suitable status code.
    *
    * @returns Pointer to ICard object.
    */
   virtual std::shared_ptr<ICard> getCard(int slotId = DEFAULT_SLOT_ID,
                                          telux::common::Status *status = nullptr)
      = 0;

   /**
    * Register a listener for card events.
    *
    * @param [in] listener    Pointer to ICardListener object that processes the notification.
    *
    * @returns Status of registerListener i.e. success or suitable status code.
    */
   virtual telux::common::Status registerListener(std::shared_ptr<ICardListener> listener) = 0;

   /**
    * Remove a previously added listener.
    *
    * @param [in] listener    Pointer to ICardListener object that needs to be removed.
    *
    * @returns Status of removeListener i.e. success or suitable status code.
    */
   virtual telux::common::Status removeListener(std::shared_ptr<ICardListener> listener) = 0;

   virtual ~ICardManager(){};

};  // end of ICardManager

class ICard {
public:
   /**
    * Get the card state for the slot id.
    *
    * @param [out] cardState  @ref CardState - state of the card.
    *
    * @returns Status of getCardState i.e. success or suitable status code.
    */
   virtual telux::common::Status getState(CardState &cardState) = 0;
   /**
    * Get card applications.
    *
    * @param [out] status   Status of getApplications i.e. success or suitable status code.
    *
    * @returns List of card applications.
    */
   virtual std::vector<std::shared_ptr<ICardApp>> getApplications(telux::common::Status *status
                                                                  = nullptr)
      = 0;

   /**
    * Open a logical channel to the SIM.
    *
    * @param [in] applicationId   Application Id.
    * @param [in] callback        Optional callback pointer to get the response of open logical
    *                             channel request.
    *
    * @returns Status of openLogicalChannel i.e. success or suitable status code.
    */
   virtual telux::common::Status openLogicalChannel(std::string applicationId,
                                                    std::shared_ptr<ICardChannelCallback> callback
                                                    = nullptr)
      = 0;

   /**
    * Close a previously opened logical channel to the SIM.
    *
    * @param [in] channelId   The channel ID to be closed.
    * @param [in] callback    Optional callback pointer to get the response of close logical
    *                         channel request.
    *
    * @returns Status of closeLogicalChannel i.e. success or suitable status code.
    */
   virtual telux::common::Status closeLogicalChannel(
      int channelId, std::shared_ptr<telux::common::ICommandResponseCallback> callback = nullptr)
      = 0;

   /**
    * Transmit an APDU to the ICC card over a logical channel.
    *
    * @param [in] channel       Channel Id of the channel to use for communication.
    *                           Has to be greater than zero.
    * @param [in] cla           Class of the APDU command.
    * @param [in] instruction   Instruction of the APDU command.
    * @param [in] p1            Instruction Parameter 1 value of the APDU command.
    * @param [in] p2            Instruction Parameter 2  value of the APDU command.
    * @param [in] p3            Number of bytes present in the data field of the APDU command.
    *                           If p3 is negative, a 4 byte APDU is sent to the SIM.
    * @param [in] data          Data to be sent with the APDU.
    * @param [in] callback      Optional callback pointer to get the response of
    *                           transmit APDU request.
    *
    * @returns Status of transmitApduLogicalChannel i.e. success or suitable status code.
    */
   virtual telux::common::Status transmitApduLogicalChannel(
      int channel, uint8_t cla, uint8_t instruction, uint8_t p1, uint8_t p2, uint8_t p3,
      std::vector<uint8_t> data, std::shared_ptr<ICardCommandCallback> callback = nullptr)
      = 0;

   /**
    * Exchange APDUs with the SIM on a basic channel.
    *
    * @param [in] cla           Class of the APDU command.
    * @param [in] instruction   Instruction of the APDU command.
    * @param [in] p1            Instruction Param1 value of the APDU command.
    * @param [in] p2            Instruction Param1  value of the APDU command.
    * @param [in] p3            Number of bytes present in the data field of the APDU command.
    *                           If p3 is negative, a 4 byte APDU is sent to the SIM.
    * @param [in] data          Data to be sent with the APDU.
    * @param [in] callback      Optional callback pointer to get the response of
    *                           transmit APDU request.
    *
    * @returns Status of transmitApduBasicChannel i.e. success or suitable status code.
    */
   virtual telux::common::Status transmitApduBasicChannel(
      uint8_t cla, uint8_t instruction, uint8_t p1, uint8_t p2, uint8_t p3,
      std::vector<uint8_t> data, std::shared_ptr<ICardCommandCallback> callback = nullptr)
      = 0;

   /**
    * Performs SIM IO operation, This is similar to the TS 27.007 "restricted SIM" operation
    * where it assumes all of the EF selection will be done by the callee
    *
    * @param [in] fileId    Elementary File Identifier
    * @param [in] command   APDU Command for SIM IO operation
    * @param [in] p1        Instruction Param1 value of the APDU command
    * @param [in] p2        Instruction Param2 value of the APDU command
    * @param [in] p3        Number of bytes present in the data field of APDU command.
    *                       If p3 is negative, a 4 byte APDU is sent to the SIM.
    * @param [in] filePath  Path of the file
    * @param [in] data      Data to be sent with the APDU,
    *                       send empty or null string in case no data
    * @param [in] pin2      Pin value of the SIM. Invalid attempt of PIN2 value will lock the SIM.
    *                       send empty or null string in case of no Pin2 value
    * @param [in] aid       Application identifier, send empty or null string in case of no aid
    * @param [in] callback  Optional callback pointer to get the response of SIM IO request
    *
    * @returns - Status of exchangeSimIO i.e. success or suitable status code
    */
   virtual telux::common::Status
      exchangeSimIO(uint16_t fileId, uint8_t command, uint8_t p1, uint8_t p2, uint8_t p3,
                    std::string filePath, std::vector<uint8_t> data, std::string pin2,
                    std::string aid, std::shared_ptr<ICardCommandCallback> callback = nullptr)
      = 0;
};

/**
 * Interface for Card callback object. Client needs to implement this interface to get
 * single shot responses for commands like open logical channel and close logical channel.
 *
 * The methods in callback can be invoked from multiple different threads. The implementation
 * should be thread safe.
 */
class ICardChannelCallback : public telux::common::ICommandCallback {
public:
   /**
    * This function is called with the response to the open logical channel operation.
    *
    * @param [in] channel  Channel Id for the logical channel.
    * @param [in] result   @ref IccResult of open logical channel.
    * @param [in] error    @ref ErrorCode of the request.
    *
    */
   virtual void onChannelResponse(int channel, IccResult result, telux::common::ErrorCode error)
      = 0;
};

class ICardCommandCallback : public telux::common::ICommandCallback {
public:
   /**
    * This function is called when SIM Card transmit APDU over Logical, Basic Channel and
    * Exchange Sim IO.
    *
    * @param [in] result   @ref IccResult of transmit APDU command
    * @param [in] error    @ref ErrorCode of the request,
    *                      Possible error codes are
    *                      - @ref SUCCESS
    *                      - @ref INTERNAL
    *                      - @ref NO_MEMORY
    *                      - @ref INVALID_ARG
    *                      - @ref MISSING_ARG
    */
   virtual void onResponse(IccResult result, telux::common::ErrorCode error) = 0;
};

/**
 * Interface for SIM Card Listener object. Client needs to implement this interface to get
 * access to card services notifications on card state change.
 *
 * The methods in listener can be invoked from multiple different threads. The implementation
 * should be thread safe.
 */
class ICardListener {
public:
   /**
    * This function is called when info of card gets updated.
    *
    * @param [in] slotId   Slot identifier.
    */
   virtual void onCardInfoChanged(int slotId) {
   }

   virtual ~ICardListener() {
   }
};

/** @} */ /* end_addtogroup telematics_card */

}  // End of namespace tel

}  // End of namespace telux

#endif  // CARDMANAGER_HPP
