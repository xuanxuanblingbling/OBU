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
 * @file       SmsManager.hpp
 * @brief      SMS Manager class is the primary interface to send and receive
 *             SMS messages. It allows to send an SMS in several formats
 *             and sizes.
 *
 */

#ifndef SMSMANAGER_HPP
#define SMSMANAGER_HPP

#include <memory>
#include <string>

#include <telux/common/CommonDefines.hpp>

namespace telux {
namespace tel {

/** @addtogroup telematics_sms
 * @{ */

class ISmsListener;
class ISmscAddressCallback;

/**
 * @brief Specifies the encoding of the SMS message
 */
enum class SmsEncoding {
   GSM7,    /**< Message is made up of GSM7 septets */
   GSM8,    /**< Message is made up of GSM8 septets */
   UCS2,    /**< Message is made up of UCS2 septets */
   UNKNOWN, /**< Message encoding is unknown */
};

/**
 * @brief   Contains structure of message attributes like encoding type, number
 * of segments, characters left in last segment
 */
struct MessageAttributes {
   SmsEncoding encoding;               /**< Data encoding type */
   int numberOfSegments;               /**< Number of segments */
   int segmentSize;                    /**< Max size of each segment */
   int numberOfCharsLeftInLastSegment; /**< characters left in last segment */
};

/**
 * @brief A Short Message Service message.
 */
class SmsMessage {
public:
   SmsMessage(std::string text, std::string sender, std::string receiver, SmsEncoding encoding,
              std::string pdu);

   /**
    * Get the message body.
    *
    * @returns String containing SMS message.
    */
   const std::string &getText() const;

   /**
    * Get the originating address (sender) of this SMS message.
    *
    * @returns String containing sender address.
    */
   const std::string &getSender() const;

   /**
    * Get the destination address (receiver) of this SMS message.
    *
    * @returns String containing receiver address
    */
   const std::string &getReceiver() const;

   /**
    * Get encoding used for this SMS message.
    *
    * @returns SMS message encoding used.
    */
   SmsEncoding getEncoding() const;

   /**
    * Get the raw PDU for the message.
    *
    * @returns String containing raw pdu data.
    */
   const std::string &getPdu() const;

   /**
    * Get the text related informative representation of this object.
    *
    * @returns String containing informative string.
    */
   const std::string toString() const;

private:
   std::string text_;     /**< Message body */
   std::string sender_;   /**< Originating address (sender) */
   std::string receiver_; /**< Destination address (receiver) */
   SmsEncoding encoding_; /**< Encoding of the SMS message */
   std::string pdu_;      /**< Raw PDU received from Telephony */
};

/**
 * @brief SMS Manager class is the primary interface to send and receive SMS
 * messages.
 *        It allows to send an SMS in several formats and sizes.
 */
class ISmsManager {
public:
   /**
    * Send Sms to destination address.
    *
    * @param [in] message           Message or payload text to be sent
    * @param [in] receiverAddress   Receiver or destination address
    * @param [in] sentCallback      Optional callback pointer to get the response
    *                               of send SMS request, This callback gives
    *                               possible error codes.
    * @param [in] deliveryCallback  Optional callback pointer to get message
    * delivery status
    *
    * @returns Status of sendSms i.e. success or suitable error code.
    *
    */
   virtual telux::common::Status
      sendSms(const std::string &message, const std::string &receiverAddress,
              std::shared_ptr<telux::common::ICommandResponseCallback> callback = nullptr,
              std::shared_ptr<telux::common::ICommandResponseCallback> deliveryCallback = nullptr)
      = 0;

   /**
    * Request for Short Messaging Service Center (SMSC) Address.
    * Purpose of SMSC is to store, forward, convert and
    * deliver Short Message Service (SMS) messages.
    *
    * @param [in] callback        Optional callback pointer to get the response
    *                             of Smsc address request
    *
    * @returns Status of getSmscAddress i.e. success or suitable error code.
    */
   virtual telux::common::Status requestSmscAddress(std::shared_ptr<ISmscAddressCallback> callback
                                                    = nullptr)
      = 0;

   /**
    * Sets the Short Message Service Center(SMSC) address on the device.
    *
    * This will change the SMSC address for all the SMS messages sent from any
    * app.
    *
    * @param [in] smscAddress    SMSC address
    * @param [in] callback       Optional callback pointer to get the response
    *                            of set SMSC address
    *
    * @returns Status of setSmscAddress i.e. success or suitable error code.
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to
    *          change and could break backwards compatibility.
    */
   virtual telux::common::Status setSmscAddress(const std::string &smscAddress,
                                                telux::common::ResponseCallback callback = nullptr)
      = 0;

   /**
    * Calculate message attributes for the given message.
    *
    * @param [in] message         Message to send
    *
    * @returns MessageAttributes structure containing encoding type, number of
    * segments, max size of segment and characters left in last segment.
    */
   virtual MessageAttributes calculateMessageAttributes(const std::string &message) = 0;

   /**
    * Get associated phone id for this SMSManager.
    *
    * @returns PhoneId.
    */
   virtual int getPhoneId() = 0;

   /**
    * Register a listener for Sms events
    *
    * @param [in] listener    Pointer to ISmsListener object which receives event
    *                         corresponding to SMS
    *
    * @returns Status of registerListener i.e. success or suitable error code.
    */
   virtual telux::common::Status registerListener(std::weak_ptr<ISmsListener> listener) = 0;

   /**
    * Remove a previously added listener.
    *
    * @param [in] listener    Pointer to ISmsListener object
    *
    * @returns Status of removeListener i.e. success or suitable error code.
    */
   virtual telux::common::Status removeListener(std::weak_ptr<ISmsListener> listener) = 0;

   virtual ~ISmsManager(){};
};

/**
 * @brief A listener class for monitoring  incoming SMS.
 * Override the methods for the state that you wish to receive updates for.
 *
 * The methods in listener can be invoked from multiple different threads. The
 * implementation should be thread safe.
 */
class ISmsListener {
public:
   /**
    * This function is called when device receives an incoming message
    *
    * @param [in] phoneId      Unique identifier per phone
    * @param [in] SmsMessage   Pointer to SmsMessage object
    */
   virtual void onIncomingSms(int phoneId, std::shared_ptr<SmsMessage> message) {
   }
   virtual ~ISmsListener() {
   }
};

/**
 * Interface for SMS callback object. Client needs to implement this interface
 * to get single shot responses for send SMS.
 *
 * The methods in callback can be invoked from multiple different threads. The
 * implementation should be thread safe.
 */
class ISmscAddressCallback : public telux::common::ICommandCallback {
public:
   /**
    * This function is called with the response to the Smsc address request.
    *
    * @param [in] address    Smsc address
    * @param [in] error      @ref ErrorCode
    */
   virtual void smscAddressResponse(const std::string &address, telux::common::ErrorCode error) = 0;
};
/** @} */ /* end_addtogroup telematics_sms */
}
}

#endif
