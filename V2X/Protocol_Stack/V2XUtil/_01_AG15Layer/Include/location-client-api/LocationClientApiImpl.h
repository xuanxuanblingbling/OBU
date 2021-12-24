/* Copyright (c) 2018 The Linux Foundation. All rights reserved.
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
 *     * Neither the name of The Linux Foundation nor the names of its
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

#ifndef LOCATIONCLIENTAPIIMPL_H
#define LOCATIONCLIENTAPIIMPL_H

#include <mutex>

#ifdef FEATURE_EXTERNAL_AP
#include <LocSocket.h>
#else  // FEATURE_EXTERNAL_AP
#include "../../../_01_AG15Layer/Include/gps-utils/LocIpc.h"
#endif // FEATURE_EXTERNAL_AP
#include "../../../_01_AG15Layer/Include/LocationDataTypes.h"
#include "../../../_01_AG15Layer/Include/ILocationAPI.h"
#include "../../../_01_AG15Layer/Include/location-client-api/LocationClientApi.h"
#include "../../../_01_AG15Layer/Include/gps-utils/MsgTask.h"
#include "../../../_01_AG15Layer/Include/LocationApiMsg.h"
#ifndef FEATURE_EXTERNAL_AP
#include <LocDiagIface.h>
#include <LocationClientApiLog.h>
#endif

using namespace std;

#ifdef FEATURE_EXTERNAL_AP
using loc_util::LocSocket;
using loc_util::LocSocketSender;
#else  // FEATURE_EXTERNAL_AP
using loc_util::LocIpc;
using loc_util::LocIpcSender;
#endif // FEATURE_EXTERNAL_AP

/** @fn
    @brief
    Structure of all client callbacks
*/
struct ClientCallbacks {
    location_client::CapabilitiesCb capabilitycb;
    location_client::ResponseCb responsecb;
    location_client::LocationCb locationcb;
    location_client::GnssReportCbs gnssreportcbs;
    // used for rare system event
    location_client::LocationSystemInfoCb systemInfoCb;
};

#ifndef FEATURE_EXTERNAL_AP
typedef LocDiagIface* (getLocDiagIface_t)();
#endif

namespace location_client
{
#ifndef FEATURE_EXTERNAL_AP
void translateDiagGnssLocationPositionDynamics(clientDiagGnssLocationPositionDynamics& out,
        const GnssLocationPositionDynamics& in);
static clientDiagGnssSystemTimeStructType parseDiagGnssTime(
        const GnssSystemTimeStructType &halGnssTime);
static clientDiagGnssGloTimeStructType parseDiagGloTime(const GnssGloTimeStructType &halGloTime);
static void translateDiagSystemTime(clientDiagGnssSystemTime& out,
        const GnssSystemTime& in);
static clientDiagGnssLocationSvUsedInPosition parseDiagLocationSvUsedInPosition(
        const GnssLocationSvUsedInPosition &halSv);
static void translateDiagGnssMeasUsageInfo(clientDiagGnssMeasUsageInfo& out,
        const GnssMeasUsageInfo& in);
void populateClientDiagLocation(clientDiagGnssLocationStructType* diagGnssLocPtr,
        const GnssLocation& gnssLocation);
static void translateDiagGnssSv(clientDiagGnssSv& out, const GnssSv& in);
void populateClientDiagGnssSv(clientDiagGnssSvStructType* diagGnssSvPtr,
        std::vector<GnssSv>& gnssSvs);
#endif // FEATURE_EXTERNAL_AP

typedef std::function<void(
    uint32_t response
)> PingTestCb;

class LocationClientApiImpl :
#ifdef FEATURE_EXTERNAL_AP
    public LocSocket,
#else // FEATURE_EXTERNAL_AP
    public LocIpc,
#endif // FEATURE_EXTERNAL_AP
    public ILocationAPI,
                              public ILocationControlAPI {
public:
    LocationClientApiImpl(CapabilitiesCb capabitiescb);
    void destroy();

    // Tracking
    virtual void updateCallbacks(LocationCallbacks&) override;

    virtual uint32_t startTracking(LocationOptions&) override;

    virtual void stopTracking(uint32_t id) override;

    virtual void updateTrackingOptions(uint32_t id, LocationOptions&) override;

    //Batching
    virtual uint32_t startBatching(LocationOptions&, BatchingOptions&) override;

    virtual void stopBatching(uint32_t id) override;

    virtual void updateBatchingOptions(uint32_t id, LocationOptions&,
                                       BatchingOptions&) override;

    virtual void getBatchedLocations(uint32_t id, size_t count) override;

    //Geofence
    virtual uint32_t* addGeofences(size_t count, GeofenceOption*,
                                   GeofenceInfo*) override;

    virtual void removeGeofences(size_t count, uint32_t* ids) override;

    virtual void modifyGeofences(size_t count, uint32_t* ids,
                                 GeofenceOption* options) override;

    virtual void pauseGeofences(size_t count, uint32_t* ids) override;

    virtual void resumeGeofences(size_t count, uint32_t* ids) override;

    //GNSS
    virtual void gnssNiResponse(uint32_t id, GnssNiResponse response) override;

    // other
    virtual uint32_t* gnssUpdateConfig(GnssConfig config) override;
    virtual uint32_t gnssDeleteAidingData(GnssAidingData& data) override;

    // override from LocIpc
    virtual void onListenerReady() override;
    virtual void onReceive(const string& data) override;

    // other interface
    void updateNetworkAvailability(bool available);
    void updateCallbackFunctions(const ClientCallbacks&);
    void getGnssEnergyConsumed(GnssEnergyConsumedCb gnssEnergyConsumedCallback,
                               ResponseCb responseCallback);
    void updateLocationSystemInfoListener(LocationSystemInfoCb locSystemInfoCallback,
                                          ResponseCb responseCallback);

    void pingTest(PingTestCb pingTestCallback);

private:
    ~LocationClientApiImpl();
    void capabilitesCallback(ELocMsgID  msgId, const void* msgData);
    void updateTrackingOptionsSync(LocationClientApiImpl* pImpl, LocationOptions& option);

    // internal session parameter
    static uint32_t         mClientIdGenerator;
    static mutex            mMutex;
    uint32_t                mClientId;
    uint32_t                mSessionId;
    bool                    mHalRegistered;
    // For client on different processor, socket name will start with
    // defined constant of SOCKET_TO_EXTERANL_AP_LOCATION_CLIENT_BASE.
    // For client on same processor, socket name will start with
    // SOCKET_TO_LOCATION_CLIENT_BASE.
    char                    mSocketName[MAX_SOCKET_PATHNAME_LENGTH];
    // for client on a different processor, 0 is invalid
    uint32_t                mInstanceId;

    // callbacks
    CapabilitiesCb          mCapabilitiesCb;
    ResponseCb              mResponseCb;
    LocationCb              mLocationCb;
    GnssReportCbs           mGnssReportCbs;
    PingTestCb              mPingTestCb;

    LocationCallbacksMask   mCallbacksMask;
    LocationOptions         mLocationOptions;

    GnssEnergyConsumedCb    mGnssEnergyConsumedInfoCb;
    ResponseCb              mGnssEnergyConsumedResponseCb;

    LocationSystemInfoCb    mLocationSysInfoCb;
    ResponseCb              mLocationSysInfoResponseCb;

    MsgTask*                mMsgTask;

#ifdef FEATURE_EXTERNAL_AP
    LocSocketSender*       mIpcSender;
#else  // FEATURE_EXTERNAL_AP
    // wrapper around diag interface to handle case when diag service starts late
    LocDiagIface*          mDiagIface;
    LocIpcSender*          mIpcSender;
#endif // FEATURE_EXTERNAL_AP
};

} // namespace location_client

#endif /* LOCATIONCLIENTAPIIMPL_H */
