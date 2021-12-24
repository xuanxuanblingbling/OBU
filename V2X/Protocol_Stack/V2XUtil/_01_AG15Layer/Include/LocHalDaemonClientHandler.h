/* Copyright (c) 2018, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation, nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LOCHAL_CLIENT_HANDLER_H
#define LOCHAL_CLIENT_HANDLER_H

#include <queue>
#include <mutex>
#include "../../_01_AG15Layer/Include/gps-utils/log_util.h"
#include "../../_01_AG15Layer/Include/gps-utils/LocIpc.h"
#include "../../_01_AG15Layer/Include/LocationAPI.h"
#include "../../_01_AG15Layer/Include/LocationAPI.h"
#include "../../_01_AG15Layer/Include/LocHalDaemonIPCSender.h"

// forward declaration
class LocationApiService;

/******************************************************************************
LocHalDaemonClientHandler
******************************************************************************/
class LocHalDaemonClientHandler
{
public:
    inline LocHalDaemonClientHandler(LocationApiService* service, const std::string& clientname) :
                mService(service),
                mName(clientname),
                mCapabilityMask(0),
                mTracking(false),
                mSessionId(0),
                mLocationApi(nullptr),
                mPendingMessages(),
                mSubscriptionMask(0),
                mIpcSender(nullptr){
        if (mName != "default") {
            mIpcSender = new LocHalDaemonIPCSender(mName.c_str());

            // Create a file name with instanceId. The file handle
            // will be used by hal daemon when it crashes to figure out
            // the running clients.
            if (strncmp(mName.c_str(), SOCKET_DIR_TO_CLIENT,
                sizeof(SOCKET_DIR_TO_CLIENT)-1) != 0 ) {

                char fileName[MAX_SOCKET_PATHNAME_LENGTH];
                snprintf (fileName, sizeof(fileName), "%s%s",
                          SOCKET_TO_EXTERANL_AP_LOCATION_CLIENT_BASE, mName.c_str());
                LOC_LOGv("<-- attempt to open file %s", fileName);
                if (nullptr == fopen (fileName, "w")) {
                    LOC_LOGe("<-- failed to open file %s", fileName);
                }
            }
        }
        updateSubscription(0);
        mLocationApi = LocationAPI::createInstance(mCallbacks);
    }

    void cleanup();

    // public APIs
    void updateSubscription(uint32_t mask);
    // when client stops the location session, then all callbacks
    // related to location session need to be unsubscribed
    void unsubscribeLocationSessionCb();
    uint32_t startTracking();
    uint32_t startTracking(uint32_t minDistance, uint32_t minInterval);
    void stopTracking();
    void updateTrackingOptions(uint32_t minDistance, uint32_t minInterval);
    void onGnssEnergyConsumedInfoAvailable(LocAPIGnssEnergyConsumedIndMsg &msg);
    bool hasPendingEngineInfoRequest(uint32_t mask);
    void addEngineInfoRequst(uint32_t mask);
    void pingTest();

    bool mTracking;
    std::queue<ELocMsgID> mPendingMessages;

private:
    inline ~LocHalDaemonClientHandler() {}

    // Location API callback functions
    void onCapabilitiesCallback(LocationCapabilitiesMask capabilitiesMask);
    void onResponseCb(LocationError err, uint32_t id);
    void onCollectiveResponseCallback(size_t count, LocationError *errs, uint32_t *ids);

    void onTrackingCb(Location location);
    void onGnssLocationInfoCb(GnssLocationInfoNotification gnssLocationInfoNotification);

    void onGnssNiCb(uint32_t id, GnssNiNotification gnssNiNotification);
    void onGnssSvCb(GnssSvNotification gnssSvNotification);
    void onGnssNmeaCb(GnssNmeaNotification);
    void onGnssDataCb(GnssDataNotification gnssDataNotification);
    void onGnssMeasurementsCb(GnssMeasurementsNotification);
    void onLocationSystemInfoCb(LocationSystemInfo);
    void onLocationApiDestroyCompleteCb();

    // send ipc message to this client for general use
    template <typename MESSAGE>
    bool sendMessage(const MESSAGE& msg) {
        return sendMessage(reinterpret_cast<const uint8_t*>(&msg), sizeof(msg));
    }

    // send ipc message to this client for serialized payload
    bool sendMessage(const uint8_t* pmsg, size_t msglen) {
        bool ret = false;
        if (mIpcSender) {
            ret = mIpcSender->send(pmsg, msglen);
            if (!ret) {
                LOC_LOGe("Failed to send message. Disconnected client.");
                delete mIpcSender;
                mIpcSender = nullptr;
            }
        } else {
            ret = true;
        }
        return ret;
    }

    // pointer to parent service
    LocationApiService* mService;

    // name of this client
    const std::string mName;

    // LocationAPI interface
    LocationCapabilitiesMask mCapabilityMask;
    uint32_t mSessionId;
    LocationAPI* mLocationApi;
    LocationCallbacks mCallbacks;
    LocationOptions mOptions;

    // bitmask to hold this client's subscription
    uint32_t mSubscriptionMask;
    // bitmask to hold this client's request to engine info related subscription
    uint32_t mEngineInfoRequestMask;

    LocHalDaemonIPCSender* mIpcSender;
};

#endif //LOCHAL_CLIENT_HANDLER_H

