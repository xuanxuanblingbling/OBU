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
* @file       Cv2xRxTypes.hpp
*
* @brief      Contains common data types used in Cv2x Radio API
*/

#ifndef CV2XRADIOTYPES_HPP
#define CV2XRADIOTYPES_HPP

#include <bitset>
#include <vector>

namespace telux {

namespace cv2x {

/** @addtogroup telematics_cv2x
 * @{ */

/**
 * Defines CV2X Traffic Types.
 *
 * Used in @ref Cv2xRadioManager::getCv2xRadio
 */
enum class TrafficCategory {
    SAFETY_TYPE,      /**< Safety message traffic category */
    NON_SAFETY_TYPE,  /**< Non-safety message traffic category */
};

/**
 * Defines possible values for CV2X radio RX/TX status.
 *
 * Used in @ref Cv2xStatus
 */
enum class Cv2xStatusType {
    INACTIVE,    /**< RX/TX is inactive */
    ACTIVE,      /**< RX/TX is active */
    SUSPENDED,   /**< RX/TX is suspended */
    UNKNOWN,     /**< RX/TX status unknown */
};

/**
 * Defines possible values for cause of CV2X radio failure.
 *
 * Used in @ref Cv2xStatus
 */
enum class Cv2xCauseType {
    TIMING,     /**< Timing is invalid */
    CONFIG,     /**< Config is invalid */
    UE_MODE,    /**< UE Mode is invalid */
    GEOPOLYGON, /**< V2x is not supported in current geopolygon */
    UNKNOWN,    /**< Cause is unknown */
};

/**
 * Encapsulates status of CV2X radio.
 *
 * Used in @ref Cv2xRadioManager:requestV2xStatus and Cv2xRadioListener.
 */
struct Cv2xStatus {
    Cv2xStatusType rxStatus = Cv2xStatusType::UNKNOWN;  /**< RX status */
    Cv2xStatusType txStatus = Cv2xStatusType::UNKNOWN;  /**< TX status */
    Cv2xCauseType rxCause = Cv2xCauseType::UNKNOWN;     /**< RX cause of failure */
    Cv2xCauseType txCause = Cv2xCauseType::UNKNOWN;     /**< TX cause of failure */
    uint8_t cbrValue = 255;                             /**< Channel Busy Ratio */
    bool cbrValueValid = false;                         /**< CBR value is valid */
};

/**
 * Encapsulates status for single pool.
 *
 * Used in @ref Cv2xStatusEx.
 */
struct Cv2xPoolStatus {
    uint8_t poolId = 0u; /**< pool ID*/
    Cv2xStatus status;   /**< status */
};

/**
 * Encapsulates status of CV2X radio and per pool status.
 *
 * Used in @ref Cv2xRadioManager:requestV2xStatus and
 * Cv2xRadioListener.
 */
struct Cv2xStatusEx {
    Cv2xStatus status;                      /**< Overall Cv2x status */
    std::vector<Cv2xPoolStatus> poolStatus; /**< Multi pool status vector */
    bool timeUncertaintyValid = false;      /**< Time uncertainty value is valid */
    float timeUncertainty;                  /**< Time uncertainty value in milleseconds */
};

/**
 * Defines CV2X traffic type in terms of IP or NON-IP.
 *
 * Used in @ref createRxSock, @ref createTxSpsSock, and @ref createTxEventSock
 */
enum class TrafficIpType {
   TRAFFIC_IP,     /**< IP message traffic */
   TRAFFIC_NON_IP, /**< NON-IP message traffic */
};

/**
 * Defines CV2X modes of concurrency with cellular WWAN.
 *
 * Used in @ref Cv2xRadioCapabilities
 */
enum class RadioConcurrencyMode {
    WWAN_NONCONCURRENT, /**< No simultaneous WWAN + CV2X on this interface  */
    WWAN_CONCURRENT,    /**< Interface supports requests for concurrent WWAN +
                             CV2X connections. */
};

/**
 * Defines CV2X status change events. The state can change in response to the
 * loss of timing precision or a geofencing change.
 *
 * Used in @ref onStatusChanged in ICv2xRadioListener
 */
enum class Cv2xEvent {
    CV2X_INACTIVE,  /**<  */
    CV2X_ACTIVE,    /**<  */
    TX_SUSPENDED,   /**<  */
    TXRX_SUSPENDED, /**<  */
};

/**
 * Range of supported priority levels, where a lower number means a higher
 * priority. For example, 8 is the current 3GPP standard.
 *
 * Used in @ref Cv2xRadioCapabilities and @ref SpsFlowInfo
 */
enum class Priority {
    MOST_URGENT,
    PRIORITY_1,
    PRIORITY_2,
    PRIORITY_3,
    PRIORITY_4,
    PRIORITY_5,
    PRIORITY_6,
    PRIORITY_BACKGROUND,
    PRIORITY_UNKNOWN,
};

/**
 * Range of supported periodicities in milliseconds.
 *
 * Used in @ref Cv2xRadioCapabilities and @ref SpsFlowInfo
 *
 * @Deprecated: enum class not going to be supported in future releases. Clients should stop using
 * this. Once a class has been marked as Deprecated, the class could be removed in future releases.
 *
 */
enum class Periodicity {
    PERIODICITY_10MS,
    PERIODICITY_20MS,
    PERIODICITY_50MS,
    PERIODICITY_100MS,
    PERIODICITY_UNKNOWN,
};

/**
 * Contains minimum and maximum frequency for a given TX pool ID. Multiple TX
 * Pools allow the same radio and overall frequency range to be shared for
 * multiple types of traffic like V2V and V2X. Each pool ID and frequency range
 * corresponds to a certain type of traffic.
 *
 * Used in @ref Cv2xRadioCapabilities
 */
struct TxPoolIdInfo {
    uint8_t poolId;
    /**< TX pool ID. */
    uint16_t minFreq;
    /**< Minimum frequency in MHz. */
    uint16_t maxFreq;
    /**< Maximum frequency in MHz. */
};

/**
 * Contains event flow configuration parameters.
 *
 * Used in @ref createTxEventFlow
 */
struct EventFlowInfo {
    bool autoRetransEnabledValid = true;
    /**< Set to true if autoRetransEnabled field is specified. If false, the
         system will use the default setting. */
    bool autoRetransEnabled = true;
    /**< Used to enable automatic-retransmissions. */
    bool peakTxPowerValid = false;
    /**< Set to true if peakTxPower is used. If false, the system will
         use the default setting. */
    int32_t peakTxPower;
    /**< Max Tx power setting in dBm. */
    bool mcsIndexValid = false;
    /**< Set to true if mcsIndex is used. If false, the system will use its
         default setting. */
    uint8_t mcsIndex;
    /**< Modulation and Coding Scheme Index to use. */
    bool txPoolIdValid = false;
    /**< Set to true if txPoolId is used.  If false, the system will use its
         default setting. */
    uint8_t txPoolId = 0u;
    /**< Transmission Pool ID. */
};

/**
 * Used to request the QoS bandwidth contract, implemented in PC5 3GPP V2X
 * radio as a <i>Semi Persistent Flow</i> (SPS).
 *
 * The underlying radio providing the interface might support periodicities of
 * various granularity in 100ms integer multiples (e.g. 200ms, 300ms).
 *
 * Used in @ref txSpsCreateAndBindSock and @ref changeSpsFlowInfo
 */
struct SpsFlowInfo {
    Priority priority = Priority::PRIORITY_2;
    /**< Specifies one of the 3GPP levels of Priority for the traffic that is
         pre-reserved on the SPS flow. Default is PRIORITY_2.

         Use getCapabilities() to discover the supported priority levels.
         @Deprecated: periodicity, Use new periodicityMs instead */
    Periodicity periodicity = Periodicity::PERIODICITY_100MS;
    /**This is the new interface to specify periodicity in milliseconds for
       SpsFlowInfo. Enum Periodicity is deprecated and will be removed in future
       release.
    */
    uint64_t periodicityMs = 100;
    /**< Bandwidth-reserved periodicity interval in interval in milliseconds.

         There are limits on which intervals the underlying radio supports.
         Use getCapabilities() to discover minPeriodicityMultiplierMs and
         maximumPeriodicityMs. */
    uint32_t nbytesReserved = 0u;
    /**< Number of bytes of TX bandwidth that are sent every periodicity
         interval. */
    bool autoRetransEnabledValid = true;
    /**< Set to true if autoRetransEnabled field is specified. If false, the
         system will use the default setting. */
    bool autoRetransEnabled = true;
    /**< Used to enable automatic-retransmissions. */
    bool peakTxPowerValid = false;
    /**< Set to true if peakTxPower is used. If false, the system will
         use the default setting. */
    int32_t peakTxPower;
    /**< Max Tx power setting in dBm. */
    bool mcsIndexValid = false;
    /**< Set to true if mcsIndex is used. If false, the system will use its
         default setting. */
    uint8_t mcsIndex;
    /**< Modulation and Coding Scheme Index to use.  */
    bool txPoolIdValid = false;
    /**< Set to true if txPoolId is used.  If false, the system will use its
         default setting. */
    uint8_t txPoolId = 0u;
    /**< Transmission Pool ID. */
};

/**
 * Contains capabilities of the Cv2xRadio.
 *
 * Used in @ref requestCapabilities and @ref onCapabilitiesChanged
 */
struct Cv2xRadioCapabilities {
    uint32_t linkIpMtuBytes;
    /**< Maximum data payload length (in bytes) of a packet supported by the
         IP Radio interface. */
    uint32_t linkNonIpMtuBytes;
    /**< Maximum data payload length (in bytes) of a packet supported by the
         non-IP Radio interface. */
    RadioConcurrencyMode maxSupportedConcurrency;
    /**< Indicates whether this interface supports concurrent WWAN with
         V2X (PC5). */
    uint16_t nonIpTxPayloadOffsetBytes;
    /**< Byte offset in a non-IP Tx packet before the actual payload begins. */
    uint16_t nonIpRxPayloadOffsetBytes;
    /**< Byte offset in a non-IP Rx packet before the actual payload begins.
         @Deprecated: periodicitiesSupported, Use new periodicities instead */
    std::bitset<8> periodicitiesSupported;
    std::vector<uint64_t> periodicities;
    /**< Specifies the periodicities supported */
    uint8_t maxNumAutoRetransmissions;
    /**< Least frequent bandwidth periodicity that is supported. Above this
         value, use event-driven periodic messages of a period larger than
         this value. */
    uint8_t layer2MacAddressSize;
    /**< Size of the L2 MAC address.

         Different Radio Access Technologies have different-sized L2 MAC
         addresses: 802.11 has 6 bytes, whereas 3GPP PC5 has only 3 bytes.

         Because a randomized MAC address comes from an HSM with good pseudo
         random entropy, higher layers must know how many bytes of the MAC
         address to generate. */
    std::bitset<8> prioritiesSupported;
    /**< Bit set of different priority levels supported by this Cv2xRadio.
         Refer to @ref: Priority */
    uint16_t maxNumSpsFlows;
    /**< Maximum number of supported SPS reservations. */
    uint16_t maxNumNonSpsFlows;
    /**< Maximum number of supported event flows (non-SPS ports). */
    int32_t maxTxPower;
    /**< Maximum supported transmission power. */
    int32_t minTxPower;
    /**< Minimum supported transmission power. */
    std::vector<TxPoolIdInfo> txPoolIdsSupported;
    /**< Vector of supported transmission pool IDs. */
};

/**
 * Contains MAC information that is reported from the actual MAC SPS in the
 * radio. The offsets can periodically change on any given transmission report.
 */
struct MacDetails {
    uint32_t periodicityInUseNs;
    /**< Actual transmission interval period (in nanoseconds) scheduled
         relative to 1PP 0:00.00 time */
    uint16_t currentlyReservedPeriodicBytes;
    /**< Actual number of bytes currently reserved at the MAC layer. This number
         can be slightly larger than original request. */
    uint32_t txReservationOffsetNs;
    /**< Actual offset, from a 1PPS pulse and TX flow periodicity, that the
         MAC selected and is using for the transmit reservation. If the data
         goes to the radio with enough time, it can be transmitted on the
         medium in the next immediately scheduled slot. */
};

/**
 * Contains SPS packet scheduling information that is reported from the radio.
 *
 * Used in @ref onSpsSchedulingChanged
 */
struct SpsSchedulingInfo {
    uint8_t spsId;
    /**< SPS ID */
    uint64_t utcTime;
    /**< Absolute UTC start time of next selected grant in nanoseconds. */
    uint32_t periodicity;
    /**< Periodicity of the grant in milliseconds. */
};

/**
 * Contains time confidence, position confidence, and propogation delay for a
 * trusted UE.
 *
 * Used in @ref TrustedUEInfo
 */
struct TrustedUEInfo {
    uint32_t sourceL2Id;
    /**< Trusted Source L2 ID */
    float timeUncertainty;
    /**< Time uncertainty value in milliseconds. */
    uint16_t timeConfidenceLevel;
    /**< @deprecated Use timeUncertainty
         Time confidence level.
         Range from 0 to 127 with 0 being invalid/unavailable
         and 127 being the most confident. */
    uint16_t positionConfidenceLevel;
    /**< Position confidence level.
         Range from 0 to 127 with 0 being invalid/unavailable
         and 127 being the most confident. */
    uint32_t propagationDelay;
    /**< Propagation delay in microseconds. */
};

/**
 * Contains list of malicious UE source L2 IDs.
 * Contains list of trusted UE source L2 IDs and associated confidence values.
 *
 * Used in @ref updateTrustedUEList
 */
struct TrustedUEInfoList {
    bool maliciousIdsValid = false;
    /**< Malicious remote UE sources are valid. */
    std::vector<uint32_t> maliciousIds;
    /**< Malicious remote UE source L2 IDs. */
    bool trustedUEsValid = false;
    /**< Trusted remote UE sources are valid. */
    std::vector<TrustedUEInfo> trustedUEs;
    /**< Trusted remote UE sources. */
};

/**
 * Contains IPv6 address.
 *
 * Used in @ref DataSessionSettings
 */
struct IPv6Address {
    uint8_t addr[16];
};

/**
 * Contains packet data session settings.
 *
 * Used in @ref requestDataSessionSettings
 */
struct DataSessionSettings {
    bool mtuValid = false;
    /**< Set to true if mtu is valid. */
    uint32_t mtu;
    /**< MTU size. */
    bool ipv6AddrValid = false;
    /**< Set to true if ipv6 address is valid. */
    IPv6Address ipv6Addr;
    /**< IPv6 address. */
};

/** @} */ /* end_addtogroup telematics_cv2x */

} // namespace cv2x

} // namespace telux

#endif // #ifndef CV2XRADIOTYPES_HPP
