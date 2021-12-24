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
 * @file       DataConnectionManager.hpp
 *
 * @brief      DataConnectionManager is a primary interface for cellular connectivity. This
 *             interface provides APIs for start and stop data call connections, get data
 *             call information and add or remove listeners for monitoring data calls
 *             status.
 *
 */

#ifndef DATACONNECTIONMANAGER_HPP
#define DATACONNECTIONMANAGER_HPP

#include <future>
#include <vector>
#include <list>
#include <memory>

#include <telux/data/DataDefines.hpp>
#include <telux/data/DataProfile.hpp>

#include <telux/common/CommonDefines.hpp>

namespace telux {
namespace data {

// Forward declarations
class IDataConnectionListener;
class IDataCall;

/**
 * This function is called with the response to requestDataCallStatistics API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] dataCall        Pointer to IDataCall
 * @param [in] error           Return code for whether the operation
 *                             succeeded or failed
 *
 */
using DataCallResponseCb
   = std::function<void(const std::shared_ptr<IDataCall> &dataCall, telux::common::ErrorCode error)>;

/**
 * This function is called with the response to requestDataCallStatistics API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] dataStats       Data Call statistics
 * @param [in] error           Return code for whether the operation
 *                             succeeded or failed
 */
using StatisticsResponseCb
   = std::function<void(const DataCallStats dataStats, telux::common::ErrorCode error)>;

/** @addtogroup telematics_data
 * @{ */

/**
 *@brief IDataConnectionManager is a primary interface for cellular connectivity
 *       This interface provides APIs for start and stop data call connections,
 *       get data call information and listener for monitoring data calls.
 */
class IDataConnectionManager {
public:
   /**
    * Checks if the data subsystem is ready.
    *
    * @returns True if Data Connection Manager is ready for service, otherwise
    * returns false.
    *
    */
   virtual bool isSubsystemReady() = 0;

   /**
    * Wait for data subsystem to be ready.
    *
    * @returns A future that caller can wait on to be notified
    * when card manager is ready.
    *
    */
   virtual std::future<bool> onSubsystemReady() = 0;

   /**
    * Starts a data call corresponding to default or specified profile identifier.
    *
    * This will bring up data call connection based on specified profile identifier. This is an
    * asynchronous API, client receives notification indicating the data call establishment
    * or failure in callback.
    *
    * @note       if application starts data call on IPV4V6 then it's expected to stop the
    *             data call on same ip family type (i.e IPV4V6).
    *
    * @param [in] profileId     Profile identifier corresponding to which data call bring up
    *                           will be done. Use IDataProfileManager::requestProfileList to get
    *                           list of available profiles.
    * @param [in] ipFamilyType  Identifies IP family type
    * @param [out] callback     Optional callback to get the response of start data call.
    *
    * @returns Immediate status of startDataCall() request sent
    *                   i.e. success or suitable status code.
    *
    *
    */
   virtual telux::common::Status startDataCall(int profileId,
                                               IpFamilyType ipFamilyType = IpFamilyType::IPV4V6,
                                               DataCallResponseCb callback = nullptr)
      = 0;

   /**
    * Stops a data call corresponding to default or specified profile identifier.
    *
    * This will tear down specific data call connection based on profile identifier.
    *
    * @note       if application starts data call on IPV4V6 then it's expected to stop the
    *             data call on same ip family type (i.e IPV4V6).
    *
    * @param [in] profileId     Profile identifier corresponding to which data call tear down
    *                           will be done. Use data profile manager to get the list of
    *                           available profiles.
    * @param [in] ipFamilyType  Identifies IP family type
    * @param [out] callback     Optional callback to get the response of stop data call
    *
    * @returns Immediate status of stopDataCall() request sent i.e. success or
    *          suitable status code. The client receives asynchronous notifications
    *          indicating the data call tear-down.
    *
    */
   virtual telux::common::Status stopDataCall(int profileId,
                                              IpFamilyType ipFamilyType = IpFamilyType::IPV4V6,
                                              DataCallResponseCb callback = nullptr)
      = 0;

   /**
    * Register a listener for specific events in the Connection Manager like establishment of new
    * data call, data call info change and call failure.
    *
    * @param [in] listener    pointer of IDataConnectionListener object that processes the
    * notification
    *
    * @returns Status of registerListener success or suitable status code
    *
    */
   virtual telux::common::Status registerListener(std::weak_ptr<IDataConnectionListener> listener)
      = 0;

   /**
    * Removes a previously added listener.
    *
    * @param [in] listener    pointer of IDataConnectionListener object that needs to be removed
    *
    * @returns Status of deregisterListener success or suitable status code
    *
    */
   virtual telux::common::Status deregisterListener(std::weak_ptr<IDataConnectionListener> listener)
      = 0;

   /**
    * Get associated slot id for the Data Connection Manager.
    *
    * @returns SlotId
    *
    */
   virtual int getSlotId() = 0;

   /**
    * Destructor for IDataConnectionManager
    */
   virtual ~IDataConnectionManager(){};
};  // end of IDataConnectionManager

/**
 * @brief Represents single established data call on the device.
 *
 */
class IDataCall {
public:
   /**
    * Get interface name for the data call associated.
    *
    * @returns Interface Name.
    *
    */
   virtual const std::string &getInterfaceName() = 0;

   /**
    * Get the bearer technology on which earlier data call was brought up like LTE, WCDMA and etc.
    * This is synchronous API called by client to get bearer technology corresponding to data call.
    *
    * @returns @ref DataBearerTechnology
    *
    */
   virtual DataBearerTechnology getCurrentBearerTech() = 0;

   /**
    * Get failure reason for the data call.
    *
    * @returns @ref DataCallFailReason.
    *
    */
   virtual DataCallEndReason getDataCallEndReason() = 0;

   /**
    * Get data call status like connected, disconnected and IP address changes.
    *
    * @returns @ref DataCallStatus.
    *
    */
   virtual DataCallStatus getDataCallStatus() = 0;

   /**
    * Get the technology on which the call was brought up.
    *
    * @returns @ref TechPreference.
    *
    */
   virtual TechPreference getTechPreference() = 0;

   /**
    * Get list of IP address information.
    *
    * @returns List of IP address details.
    *
    */
   virtual std::list<IpAddrInfo> getIpAddressInfo() = 0;

   /**
    * Get IP Family Type i.e. IPv4, IPv6 or Both
    *
    * @returns @ref IpFamilyType.
    *
    */
   virtual IpFamilyType getIpFamilyType() = 0;

   /**
    * Get Profile Id
    *
    * @returns Profile Identifier.
    *
    */
   virtual int getProfileId() = 0;

   /**
    * Request the data transfer statistics for data call corresponding
    * to specified profile identifier.
    *
    * @param [in] callback    Optional callback to get the response of request Data Call
    *                         Statistics
    *
    * @returns Status of getDataCallStatistics i.e. success or suitable status code.
    */
   virtual telux::common::Status requestDataCallStatistics(StatisticsResponseCb callback = nullptr)
      = 0;

   /**
    * Reset data transfer statistics for data call corresponding to specified profile identifier.
    *
    * @param [in] callback   optional callback to get the response of reset Data call statistics
    *
    * @returns Status of resetDataCallStatistics i.e. success or suitable status code.
    */
   virtual telux::common::Status resetDataCallStatistics(telux::common::ResponseCallback callback
                                                         = nullptr)
      = 0;

   /**
    * Destructor for IDataCall
    */
   virtual ~IDataCall(){};
};

/**
 * Interface for Data call listener object. Client needs to implement this interface to get
 * access to data services notifications like onNewDataCall, onDataCallStatusChanged and
 * onDataCallFailure.
 *
 * The methods in listener can be invoked from multiple different threads. The implementation
 * should be thread safe.
 *
 */
class IDataConnectionListener : public telux::common::IServiceStatusListener {
public:
   /**
    * This function is called when there is a change in the data call.
    *
    * @param [in] status     Data Call Status
    * @param [in] dataCall   Pointer to IDataCall
    *
    */
   virtual void onDataCallInfoChanged(const std::shared_ptr<IDataCall> &dataCall){};

   /**
    * Destructor for IDataConnectionListener
    */
   virtual ~IDataConnectionListener(){};
};

/** @} */ /* end_addtogroup telematics_data */
}
}

#endif
