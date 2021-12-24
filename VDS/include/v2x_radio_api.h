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
  @file v2x_radio_api.h

  @addtogroup v2x_api_radio
  Abstraction of the radio driver parameters for a V2X broadcast socket
  interface, including 3GPP CV2X QoS bandwidth contracts.
 */

#ifndef __V2X_RADIO_APIS_H__
#define __V2X_RADIO_APIS_H__

#include <net/ethernet.h> /* the L2 protocols */
#include <netinet/in.h>
#include <netpacket/packet.h>
#include <stdint.h>
#include <sys/socket.h>
#include <unistd.h>

#include "v2x_common.pb.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup v2x_api_radio
@{ */

/** Radio data handle to the interface. */
typedef int v2x_radio_handle_t;

/** Invalid handle returned by v2x_radio_init() and v2x_radio_init_v2() upon an error. */
#define V2X_RADIO_HANDLE_BAD (-1)

/** Limit on the number of simultaneous RmNet Radio interfaces this library can
    have open at once.

    Typically, there are only a few actual radios. On the same radio however,
    one interface can be for IP traffic, and another interface can be for
    non-IP traffic.
 */
#define V2X_MAX_RADIO_SESSIONS (10)

/** Wildcard value for a port number. When the wildcard is used, all V2X
    received traffic is routed.
 */
#define V2X_RX_WILDCARD_PORTNUM (9000)

/** Maximum length of the pool ID list that is returned in
    #v2x_iface_capabilities_t.
 */
#define MAX_POOL_IDS_LIST_LEN (20)

/** Maximum length of the malicious ID list that can be passed in
    v2x_radio_update_trusted_ue_list().
 */
#define MAX_MALICIOUS_IDS_LIST_LEN (50)

/** Maximum length of the trusted ID list that can be passed in
    v2x_radio_update_trusted_ue_list().
 */
#define MAX_TRUSTED_IDS_LIST_LEN   (50)

 /** Maximum length for the subscribed service ID list that can
     be passed in v2x_radio_rx_sock_create_and_bind_v2(). @newpage
  */
#define MAX_SUBSCRIBE_SIDS_LIST_LEN (10)

/**
    Describes whether the radio chip modem should attempt or support concurrent
    3GPP CV2X operation with a WWAN 4G/5G data call.

    Some chips are only capable of operating on CV2X. In this case:
    - The callers can only request V2X_WWAN_NONCONCURRENT.
    - The interface parameters that are returned list v2x_concurrency_sel_t as
      the value for V2X_WAN_NONCONCURRENT.
 */
typedef enum {
    V2X_WWAN_NONCONCURRENT = 0,  /**< No simultaneous WWAN + CV2X on this
                                      interface. */
    V2X_WWAN_CONCURRENT = 1      /**< Interface allows requests for concurrent
                                      support of WWAN + CV2X connections. */
} v2x_concurrency_sel_t;

/**
    Event indications sent asynchronously from the radio via callbacks that
    indicate the state of the radio. The state can change in response to the
    loss of timing precision or a geofencing change.
 */
typedef enum {
    V2X_INACTIVE = 0,    /**< V2X communication is disabled. */
    V2X_ACTIVE,          /**< V2X communication is enabled. Transmit and
                              receive are possible. */
    V2X_TX_SUSPENDED,    /**< Small loss of timing precision occurred.
                              Transmit is no longer supported. */
    V2X_RX_SUSPENDED,    /**< Radio can no longer receive any messages. */
    V2X_TXRX_SUSPENDED,  /**< Radio can no longer transmit or receive for
                              some reason. @newpage */
} v2x_event_t;

/**
    Range of supported priority levels, where a lower number means a higher
    priority. For example, 8 is the current 3GPP standard.
 */
typedef enum {
    V2X_PRIO_MOST_URGENT = 0,  /**< Highest priority. */
    V2X_PRIO_1 = 1,
    V2X_PRIO_2 = 2,
    V2X_PRIO_3 = 3,
    V2X_PRIO_4 = 4,
    V2X_PRIO_5 = 5,
    V2X_PRIO_6 = 6,
    V2X_PRIO_BACKGROUND = 7    /**< Lowest priority. */
} v2x_priority_et;

/**
    Valid service availability states.
 */
typedef enum  {
    SERVICE_UNAVAILABLE = 0,
    SERVICE_AVAILABLE = 1,
} v2x_service_status_t;

/**
    Contains time confidence, position confidence, and propagation delay for a
    trusted UE.
*/
typedef struct {
    uint32_t source_l2_id;
    /**< L2 ID of the trusted source */

    float time_uncertainty;
    /**< Time uncertainty in milliseconds. */

    uint16_t time_confidence_level;
    /**< Deprecated. Use time_uncertainty instead.

         Confidence level of the time period.

         @values 0 through 127, where 0 is invalid or unavailable and 127 is
                 the most confident */

    uint16_t position_confidence_level;
    /**< Confidence level of the position.

         @values 0 through 127, where 0 is invalid or unavailable and 127 is
                 the most confident */

    uint32_t propagation_delay;
    /**< Propagation delay in microseconds. */
} trusted_ue_info_t;

/**
    Contains minimum and maximum frequencies for a Tx pool ID.
    This struct is used in #v2x_iface_capabilities_t.
 */
typedef struct {
    uint8_t pool_id;      /**< ID of the Tx pool. */
    uint16_t min_freq;    /**< Minimum frequency in MHz. */
    uint16_t max_freq;    /**< Maximum frequency in MHz. @newpagetable */
} tx_pool_id_info_t;

/**
    Contains information on the capabilities of a Radio interface.
 */
typedef struct {
    int link_ip_MTU_bytes;
    /**< Maximum data payload length (in bytes) of a packet supported by the
         IP Radio interface. */

    int link_non_ip_MTU_bytes;
    /**< Maximum data payload length (in bytes) of a packet supported by the
         non-IP Radio interface. */

    v2x_concurrency_sel_t max_supported_concurrency;
    /**< Indicates whether this interface supports concurrent WWAN with
         V2X (PC5). */

    uint16_t non_ip_tx_payload_offset_bytes;
    /**< Byte offset in a non-IP Tx packet before the actual payload begins.
         In 3GPP CV2X, the first byte after the offset is the 1-byte V2X
         Family ID.

         This offset is to the left for a per-packet Tx header that includes
         Tx information that might be inserted in front of the packet
         payload (in subsequent releases).

         An example of Tx information is MAC/Phy parameters (power, rate,
         retransmissions policy, and so on).

         Currently, this value is expected to be 0. But it is reserved to
         support possible per-packet Tx/Rx headers that might be added in
         future releases of this API. */

    uint16_t non_ip_rx_payload_offset_bytes;
    /**< Byte offset in a non-IP Rx packet before the actual payload begins.

         Initially, this value is zero. But it allows for later insertion of
         per-packet Rx information (sometimes called metadata) to be
         added to the front of the data payload. An example of Rx
         information is MAC/Phy measurements (receive signal strength,
         timestamps, and so on).

         The V2X Family ID is considered as part of the payload in the 3GPP
         CV2X. Higher layers (applications that are clients to this API) must
         remove or advance past that 1 byte to get to the more familiar
         actual WSMP/Geonetworking payload. */

    uint16_t int_min_periodicity_multiplier_ms;
    /**< Lowest number of milliseconds requested for a bandwidth.

         This value is also the basis for all possible bandwidth reservation
         periods. For example, if this multiplier=100 ms, applications can only
         reserve bandwidths of 100 ms, 200 ms, up to 1000 ms. */

    uint16_t int_maximum_periodicity_ms;
    /**< Least frequent bandwidth periodicity that is supported. Above this
         value, use event-driven periodic messages of a period larger than
         this value. */

    unsigned supports_10ms_periodicity : 1;
    /**< Indicates whether n*10 ms periodicities are supported.

         @values
         - 0 -- Not supported
         - 1 -- Supported @tablebulletend */

    unsigned supports_20ms_periodicity : 1;
    /**< Indicates whether an n*20 ms bandwidth reservation is supported.

         @values
         - 0 -- Not supported
         - 1 -- Supported @tablebulletend */

    unsigned supports_50ms_periodicity : 1;
    /**< Indicates whether 50 ms periodicity is supported.

         @values
         - 0 -- Not supported
         - 1 -- Supported @tablebulletend */

    unsigned supports_100ms_periodicity : 1;
    /**< Indicates whether the basic minimum periodicity of 100 ms is
         supported.

         @values
         - 0 -- Not supported
         - 1 -- Supported @tablebulletend */

    unsigned max_quantity_of_auto_retrans : 4;
    /**< Maximum number automatic retransmissions.

         @values 0 through 15 */

    unsigned size_of_layer2_mac_address : 4;
    /**< Size of the L2 MAC address.

         Different Radio Access Technologies have different-sized L2 MAC
         addresses: 802.11 has 6 bytes, whereas 3GPP PC5 has only 3 bytes.

         Because a randomized MAC address comes from an HSM with good pseudo
         random entropy, higher layers must know how many bytes of the MAC
         address to generate. */

    uint16_t v2x_number_of_priority_levels;
    /**< Number of different priority levels supported. For example, 8 is
         the current 3GPP standard (where a lower number means a higher
         priority). */

    uint16_t highest_priority_value;
    /**< Least urgent priority number supported by this radio.

         Higher numbers are lower priority, so if the full range is supported,
         this value is #V2X_PRIO_BACKGROUND. */

    uint16_t lowest_priority_value;
    /**< Highest priority value (most urgent traffic).

         Lower numbers are higher priority, so if the highest level supported
         this value is #V2X_PRIO_MOST_URGENT. */

    uint16_t max_qty_SPS_flows;
    /**< Maximum number of supported SPS reservations. */

    uint16_t max_qty_non_SPS_flows;
    /**< Maximum number of supported event flows (non-SPS ports). */

    int32_t max_tx_pwr;
    /**< Maximum supported transmission power in dBm. */

    int32_t min_tx_pwr;
    /**< Minimum supported transmission power in dBm. */

    uint32_t tx_pool_ids_supported_len;
    /**< Length of the tx_pool_ids_supported array. */

    tx_pool_id_info_t tx_pool_ids_supported[MAX_POOL_IDS_LIST_LEN];
    /**< Array of Tx pool IDs and their associated minimum and maximum
         frequencies. @newpagetable */

} v2x_iface_capabilities_t;

/**
    Converts a traffic priority to one of the 255 IPv6 traffic class bytes that
    are used in the data plane to indicate per-packet priority on non-SPS
    (event driven) data ports.

    @datatypes
    #v2x_priority_et

    @param[in] priority  Packet priority that is to be converted to an IPv6
                         traffic class. \n
                         @vertspace{3}
                         This priority is between the lowest and highest
                         priority values returned in #v2x_iface_capabilities_t.

    @detdesc
    This function is symmetric and is a reverse operation.
    @par
    The traffic priority is one of the values between min_priority_value and
    max_priority_value returned in the #v2x_iface_capabilities_t query.

    @return
    IPv6 traffic class for achieving the calling input parameter priority
    level. @newpage
 */
uint16_t v2x_convert_priority_to_traffic_class(v2x_priority_et priority);

/**
    Maps an IPv6 traffic class to a V2X priority value.

    @param[in] traffic_class  IPv6 traffic classification that came in a packet
                              from the radio.

    @detdesc
    This function is the inverse of the v2x_convert_priority_to_traffic_class()
    function. It is symmetric and is a reverse operation.

    @return
    Priority level (between highest and lowest priority values) equivalent to
    the input IPv6 traffic class parameter.
 */
v2x_priority_et v2x_convert_traffic_class_to_priority(uint16_t traffic_class);
/** @} *//* end_addtogroup v2x_api_radio */

/** @ingroup v2x_deprecated_radio
    Deprecated. Use #v2x_tx_flow_info_t.

    Contains parameters used to convey MAC/Phy settings (such as transmit power
    limits) channel/bandwidth from the application.

    Applications might need to set these parameters in response to a WSA/WRA or
    other application-level reconfiguration (such as power reduction).
    Currently, these parameters are all transmission-profile types of
    parameters.
 */
typedef struct {
    int channel_center_khz;
    /**< Channel center frequency in kHz. */

    int channel_bandwidth_mhz;
    /**< Channel bandwidth in MHz, such as 5 MHz, 10 MHz, and 20 MHz. */

    int tx_power_limit_decidbm;
    /**< Limit on the transmit power in tenths of a dBm.

         Examples of how this field is used:
         - To reduce a range that is possible as the output of an
           application-layer congestion management scheme.
         - In cases when a small communication range is needed, such as
           indoors and electronic fare collection.
         - In ETSI use cases where the power might need to be temporarily
           restricted to accommodate a nearby mobile 5.8 CEN enforcement toll
           (EFC) reader. @tablebulletend */

    int qty_auto_retrans;
    /**< Used to request the number of automatic-retransmissions. The maximum
         supported number is defined in v2x_iface_capabilities_t. */

    uint8_t l2_source_addr_length_bytes;
    /**< Length of the L2 MAC address that is supplied to the radio. */

    uint8_t *l2_source_addr_p;
    /**< Pointer to l2_source_addr_length_bytes, which contains the L2 SRC
         address that the application layer selected for the radio. */

} v2x_radio_macphy_params_t;

/** @addtogroup v2x_api_radio
@{ */
/**
    Used when requesting a QoS bandwidth contract, which is implemented in
    PC5 3GPP V2-X radio as a <i>Semi Persistent Flow</i> (SPS).

    The underlying radio providing the interface might support periodicities of
    various granularity in 100 ms integer multiples (such as 200 ms, 300 ms,
    and 400 ms).

    The reservation is also used internally as a handle.
 */
typedef struct {
    int v2xid;
    /**< Variable length 4-byte PSID or ITS_AID, or another application ID. */

    v2x_priority_et priority;
    /**< Specifies one of the 3GPP levels of priority for the traffic that is
         pre-reserved on the SPS flow.

         Use v2x_radio_query_parameters() to get the exact number of
         supported priority levels. */

    int period_interval_ms;
    /**< Bandwidth-reserved periodicity interval in milliseconds.

         There are limits on which intervals the underlying radio supports.
         Use the capabilities query method to discover the
         int_min_periodicity_multiplier_ms and int_maximum_periodicity_ms
         supported intervals. */

    int tx_reservation_size_bytes;
    /**< Number of Tx bandwidth bytes that are sent every periodicity
         interval. @newpagetable */

} v2x_tx_bandwidth_reservation_t;

/**
    Contains the measurement parameters for configuring the MAC/Phy radio
    channel measurements (such as CBR utilization).

    The radio chip contains requests on radio measurement parameters that API
    clients can use to specify the following:
    - How their higher-level application requires the CBR/CBP to be measured
    - Over which time window
    - When to send a report
 */
typedef struct {
    int channel_measurement_interval_us;
    /**< Duration in microseconds of the sliding window size. */

    int rs_threshold_decidbm;
    /**< Parameter to the radio CBR measurement that is used for determining
         how busy the channel is.

         Signals weaker than the specified receive strength (RSRP, or RSSI) are
         not considered to be in use (busy). */
} v2x_chan_meas_params_t;

/**
    Periodically returned by the radio with all measurements about the radio
    channel, such as the amount of noise and bandwidth saturation
    (channel_busy_percentage, or CBR).
 */
typedef struct {
    float channel_busy_percentage;
    /**< No measurement parameters are supplied. */

    float noise_floor;
    /**< Measurement of the background noise for a quiet channel. */

    float time_uncertainty;
    /**< V2X time uncertainty in milliseconds. @newpagetable */
} v2x_chan_measurements_t;

/**
    Contains callback functions used in a v2x_radio_init() and v2x_radio_init_v2 call.

    The radio interface uses these callback functions for events such as
    completion of initialization, a Layer-02 MAC address change, or a status
    event (loss of sufficient GPS time precision to transmit).

    These callbacks are related to a specific radio interface, and its
    MAC/Phy parameters, such as transmit power, bandwidth utilization, and
    changes in radio status.
 */
typedef struct {
    /**
    Callback that indicates initialization is complete.

    @datatypes
    #v2x_status_enum_type

    @param[in] status   Updated current radio status that indicates whether
                        transmit and receive are ready.
    @param[in] context  Pointer to the context that was supplied during initial
                        registration.

    @newpage
    */
    void (*v2x_radio_init_complete)(v2x_status_enum_type status,
                                    void *context);

    /**
    Callback made when the status in the radio changes. For example, in
    response to a fault when there is a loss of GPS timing accuracy.

    @datatypes
    #v2x_event_t

    @param[in] event    Delivery of the event that just occurred, such losing
                        the ability to transmit.
    @param[in] context  Pointer to the context of the caller who originally
                        registered for this callback.
    */
    void (*v2x_radio_status_listener)(v2x_event_t event,
                                      void *context);

    /**
    Callback made from lower layers when periodic radio measurements are
    prepared.

    @datatypes
    #v2x_chan_measurements_t

    @param[in] measurements  Pointer to the periodic measurements.
    @param[in] context       Pointer to the context of the caller who
                             originally registered for this callback.
    */
    void (*v2x_radio_chan_meas_listener)(v2x_chan_measurements_t *measurements, void *context);

    /**
    Callback made by the platform SDK when the MAC address (L2 SRC address)
    changes.

    @param[in] new_l2_address  New L2 source address as an integer
                               (because the L2 address is 3 bytes).
    @param[in] context         Pointer to the context of the caller who
                               originally registered for this callback.

    @newpage
    */
    void (*v2x_radio_l2_addr_changed_listener)(int new_l2_address, void *context);

    /**
    Callback made to indicate that the requested radio MAC/Phy change (such
    as channel/frequency and power) has completed.

    @param[in] context  Pointer to the context of the caller who originally
                        registered for this callback.
    */
    void (*v2x_radio_macphy_change_complete_cb)(void *context);

    /**
    Callback made when V2X capabilities change.

    @datatypes
    #v2x_iface_capabilities_t

    @param[in] caps     Pointer to the capabilities of this interface.
    @param[in] context  Pointer to the context of the caller who originally
                        registered for this callback.
    */
    void (*v2x_radio_capabilities_listener)(v2x_iface_capabilities_t *caps,
                                            void *context);

    /**
    Callback made when the service status changes.

    @datatypes
    #v2x_service_status_t

    @param[in] status   Service status.
    @param[in] context  Pointer to the context of the caller who originally
                        registered for this callback.

    @newpage
    */
    void (*v2x_service_status_listener)(v2x_service_status_t status,
                                        void *context);

} v2x_radio_calls_t;

/**
    Contains MAC information that is reported from the actual MAC SPS in the
    radio. The offsets can periodically change on any given transmission
    report.
 */
typedef struct {
    uint32_t periodicity_in_use_ns;
    /**< Actual transmission interval period (in nanoseconds) scheduled
         relative to 1PP 0:00.00 time. */

    uint16_t currently_reserved_periodic_bytes;
    /**< Actual number of bytes currently reserved at the MAC layer. This
         number can be slightly larger than original request. */

    uint32_t tx_reservation_offset_ns;
    /**< Actual offset, from a 1PPS pulse and Tx flow periodicity, that the MAC
         selected and is using for the transmit reservation.

         If data goes to the radio with enough time, it can be transmitted on
         the medium in the next immediately scheduled slot. @newpagetable */

    uint64_t utc_time_ns;
    /**< Absolute UTC start time of next selected grant, in nanoseconds. */

} v2x_sps_mac_details_t;

/**
    Callback functions used in v2x_radio_tx_sps_sock_create_and_bind() calls.
 */
typedef struct {
    /**
    Callback made upon completion of a reservation change that a
    v2x_radio_tx_reservation_change() call initiated for a MAC/Phy contention.

    The current SPS offset and reservation parameter are passed in the details
    structure returned by the pointer details.

    @datatypes
    #v2x_sps_mac_details_t

    @param[in] context  Pointer to the application context.
    @param[in] details  Pointer to the MAC information.

    @newpage
    */
    void (*v2x_radio_l2_reservation_change_complete_cb)(void *context,
                                                        v2x_sps_mac_details_t *details);

    /**
    Callback periodically made when the MAC SPS timeslot changes. The new
    reservation offset is in the details structure returned by pointer details.

    @datatypes
    #v2x_sps_mac_details_t

    @param[in] measurements  Pointer to the channel measurements.
    @param[in] context       Pointer to the context.

    @detdesc
    This callback can occur when a MAC contention triggers a new reservation
    time slot to be selected. It is relevant only to connections opened with
    v2x_radio_tx_sps_sock_create_and_bind().

    @newpage
    */
    void (*v2x_radio_sps_offset_changed)(void *context,
                                         v2x_sps_mac_details_t *details);

} v2x_per_sps_reservation_calls_t;

/**
    V2X Tx retransmission policies supported by the modem.
 */
typedef enum {
    V2X_AUTO_RETRANSMIT_DISABLED = 0,  /**< Retransmit mode is disabled. */
    V2X_AUTO_RETRANSMIT_ENABLED = 1,   /**< Retransmit mode is enabled. */
    V2X_AUTO_RETRANSMIT_DONT_CARE = 2, /**< Modem falls back to its default
                                            behavior. @newpage */
} v2x_auto_retransmit_policy_t;

/**
    Advanced parameters that can be specified for Tx SPS and event-driven
    flows.
 */
typedef struct {
    v2x_auto_retransmit_policy_t retransmit_policy;
    /**< V2X retransmit policy. */

    uint8_t default_tx_power_valid;
    /**< Indicates whether the default Tx power is specified.

         @values
         - 0 -- Default power is not specified
         - 1 -- Default power is specified and is valid @tablebulletend */

    int32_t default_tx_power;
    /**< Default power used for transmission. */

    uint8_t mcs_index_valid;
    /**< Indicates whether the MCS index is specified.

         @values
         - 0 -- Index is not specified
         - 1 -- Index is specified and is valid @tablebulletend */

    uint8_t mcs_index;
    /**< MCS index number */

    uint8_t tx_pool_id_valid;
    /**< Indicates whether the Tx pool ID is valid.

         @values
         - 0 -- ID is not specified
         - 1 -- ID is specified and is valid @tablebulletend */

    uint8_t tx_pool_id;
    /**< ID of the Tx pool. */

} v2x_tx_flow_info_t;

/**
    Advanced parameters that can be specified for Tx SPS flows.
 */
typedef struct {
    v2x_tx_bandwidth_reservation_t reservation;
    /**< Transmit reservation information. */

    v2x_tx_flow_info_t flow_info;
    /**< Transmit resource information about the SPS Tx flow.
         @newpagetable */

} v2x_tx_sps_flow_info_t;

/**
    V2X Ip Types
 */
typedef enum {
    TRAFFIC_IP = 0,     /**< Use Ip type traffic. */
    TRAFFIC_NON_IP = 1  /**< Use Non-Ip type traffic. */
} traffic_ip_type_t;

typedef traffic_ip_type_t traffic_ip_type;

/**
    Method used to query the platform SDK for its version number, build
    information, and build date.

    @return
    v2x_api_ver_t -- Contains the build date and API version number. @newpage
 */
extern v2x_api_ver_t v2x_radio_api_version();

/**
    Gets the capabilities of a specific Radio interface attached to the system.

    @datatypes
    #v2x_iface_capabilities_t

    @param[in] iface_name  Pointer to the Radio interface name. \n
                           @vertspace{3}
                           The Radio interface is one of the following:
                           - An RmNet interface (HLOS)
                           - The interface supplied for IP communication
                           - The interface for non-IP communication (such as
                             WSMP and Geonetworking). @vertspace{-13}
    @param[out] caps       Pointer to the v2x_iface_capabilities_t structure,
                           which contains the capabilities of this specific
                           interface.

    @return
    #V2X_STATUS_SUCCESS -- The radio is ready for data-plane sockets to be
    created and bound.
    @par
    Error code -- If there is a problem (see #v2x_status_enum_type).

    @dependencies
    An SPS flow must have been successfully initialized. @newpage
 */
extern v2x_status_enum_type v2x_radio_query_parameters(const char *iface_name, v2x_iface_capabilities_t *caps);
/** @} *//* end_addtogroup v2x_api_radio */

/** @ingroup v2x_deprecated_radio
    Deprecated. Pass #traffic_ip_type_t on radio init.

    Initializes the Radio interface and sets the callback that will be used
    when events in the radio change (including when radio initialization is
    complete).

    @datatypes
    #v2x_concurrency_sel_t \n
    #v2x_radio_calls_t

    @param[in] interface_name  Pointer to the NULL-terminated parameter that
                               specifies which Radio interface name caller is
                               to be initialized (the IP or non-IP interface of
                               a specific name). \n
                               @vertspace{3}
                               The Radio interface is one of the following:
                               - An RmNet interface (HLOS)
                               - The interface supplied for IP communication
                               - The interface for non-IP communication (such
                                 as WSMP and Geonetworking). @vertspace{-13}
    @param[in] mode            WAN concurrency mode, although the radio might
                               not support concurrency. Errors can be generated.
    @param[in] callbacks       Pointer to the v2x_radio_calls_t structure that
                               is prepopulated with function pointers used
                               during radio events (such as loss of time
                               synchronization or accuracy) for subscribers. \n
                               @vertspace{3}
                               This parameter also points to a callback for
                               this initialization function.
    @param[in] context         Voluntary pointer to the first parameter on the
                               callback.

    @detdesc
    This function call is a nonblocking, and it is a control plane action.
    @par
    Use v2x_radio_deinit() when radio operations are complete.
    @par
    @note1hang Currently, the channel and transmit power are not specified.
               They are specified with a subsequent call to
               #v2x_radio_calls_t::v2x_radio_init_complete() when 
               initialization is complete.

    @return
    Handle to the specified initialized radio. The handle is used for
    reconfiguring, opening or changing, and closing reservations.
    @par
    #V2X_RADIO_HANDLE_BAD -- If there is an error. No initialization callback
    is made. @newpage
 */
v2x_radio_handle_t v2x_radio_init(char *interface_name,
                                  v2x_concurrency_sel_t mode,
                                  v2x_radio_calls_t *callbacks,
                                  void *context);

/** @ingroup v2x_deprecated_radio
    Deprecated. Pass #v2x_tx_flow_info_t on flow creation.

    Configures the MAC/Phy parameters on an initialized radio handle to
    either an IP or non-IP radio. Parameters include the source L2 address,
    channel, bandwidth, and transmit power.

    After the radio has been configured or changed, a callback to
    #v2x_radio_calls_t::v2x_radio_macphy_change_complete_cb() is made with the
    supplied context.

    @datatypes
    #v2x_radio_handle_t \n
    #v2x_radio_macphy_params_t

    @param[in] handle   Identifies the initialized Radio interface.
    @param[in] macphy   Pointer to the MAC/Phy parameters to be configured.
    @param[in] context  Voluntary pointer to the context that will be supplied
                        as the first parameter in the callback.

    @return
    #V2X_STATUS_SUCCESS -- The radio is now ready for data-plane sockets to be
    open and bound.
    @par
    Error code -- If there is a problem (see #v2x_status_enum_type).

    @dependencies
    The interface must be pre-initialized with v2x_radio_init() or v2x_radio_init_v2(). The handle
    from that function must be used as the parameter in this function. @newpage
 */
extern v2x_status_enum_type v2x_radio_set_macphy(v2x_radio_handle_t handle, v2x_radio_macphy_params_t *macphy,
        void *context);

/** @addtogroup v2x_api_radio
@{ */
/**
    De-initializes a specific Radio interface.

    @datatypes
    #v2x_radio_handle_t

    @param[in] handle  Handle to the Radio that was initialized.

    @return
    Indication of success or failure (see #v2x_status_enum_type).

    @dependencies
    The interface must be pre-initialized with v2x_radio_init() or v2x_radio_init_v2(). The handle
    from that function must be used as the parameter in this function. @newpage
 */
extern v2x_status_enum_type v2x_radio_deinit(v2x_radio_handle_t handle);

/**
    Opens a new V2X radio receive socket, and initializes the given sockaddr
    buffer. The socket is also bound as an AF_INET6 UDP type socket.

    @datatypes
    #v2x_radio_handle_t

    @param[in] handle        Identifies the initialized Radio interface.
    @param[out] sock         Pointer to the socket that, on success, returns
                             the socket descriptor. The caller must release 
                             this socket with v2x_radio_sock_close().
    @param[out] rx_sockaddr  Pointer to the IPv6 UDP socket. The sockaddr_in6
                             buffer is initialized with the IPv6 source address
                             and source port that are used for the bind.

    @detdesc
    You can execute any sockopts that are appropriate for this type of socket
    (AF_INET6).
    @par
    @note1hang The port number for the receive path is not exposed, but it is
               in the sockaddr_ll structure (if the caller is interested).

    @return
    0 -- On success.
    @par
    Otherwise:
     - EPERM -- Socket creation failed; for more details, check errno.h.
     - EAFNOSUPPORT -- On failure to find the interface.
     - EACCES -- On failure to get the MAC address of the device.

    @dependencies
    The interface must be pre-initialized with v2x_radio_init() or v2x_radio_init_v2(). The handle
    from that function must be used as the parameter in this function. @newpage
 */
extern int v2x_radio_rx_sock_create_and_bind(v2x_radio_handle_t handle, int *sock, struct sockaddr_in6 *rx_sockaddr);

/**
    Opens a new V2X radio receive socket with specified service IDs for subscription,
    and initializes the given sockaddr buffer. The socket is also bound as an
    AF_INET6 UDP type socket.

    @datatypes
    #v2x_radio_handle_t

    @param[in] handle        Identifies the initialized Radio interface.
    @param[in] id_ist_len    Identifies the length of service ID list.
    @param[in] id_list       Pointer to the service ID list for subscription,
                             subscribe wildcard if input nullptr.
    @param[out] sock         Pointer to the socket that, on success, returns
                             the socket descriptor. The caller must release
                             this socket with v2x_radio_sock_close().
    @param[out] rx_sockaddr  Pointer to the IPv6 UDP socket. The sockaddr_in6
                             buffer is initialized with the IPv6 source address
                             and source port that are used for the bind.

    @detdesc
    You can execute any sockopts that are appropriate for this type of socket
    (AF_INET6).
    @par
    @note1hang The port number for the receive path is not exposed, but it is
               in the sockaddr_ll structure (if the caller is interested).

    @return
    0 -- On success.
    @par
    Otherwise:
     - EPERM -- Socket creation failed; for more details, check errno.h.
     - EAFNOSUPPORT -- On failure to find the interface.
     - EACCES -- On failure to get the MAC address of the device.

    @dependencies
    The interface must be pre-initialized with v2x_radio_init(). The handle from
    that function must be used as the parameter in this function. @newpage
 */
extern int v2x_radio_rx_sock_create_and_bind_v2(v2x_radio_handle_t handle,
    int id_ist_len,
    uint32_t *id_list,
    int *sock,
    struct sockaddr_in6 *rx_sockaddr);

/**
    Creates and binds a socket with a bandwidth-reserved (SPS) Tx flow with the
    requested ID, priority, periodicity, and size on a specified source port
    number. The socket is created as an IPv6 UDP socket.

    @datatypes
    #v2x_radio_handle_t \n
    v2x_tx_bandwidth_reservation_t \n
    v2x_per_sps_reservation_calls_t

    @param[in]  handle          Identifies the initialized Radio interface on
                                which this data connection is made.
    @param[in]  res             Pointer to the parameter structure (how often
                                the structure is sent, how many bytes are
                                reserved, and so on).
    @param[in]  calls           Pointer to reservation callbacks or listeners.
                                \n @vertspace{3}
                                This parameter is called when underlying radio
                                MAC parameters change related to the SPS
                                bandwidth contract.
                                For example, the callback after a
                                reservation change, or if the timing offset of
                                the SPS adjusts itself in response to
                                traffic. \n
                                @vertspace{3}
                                This parameter passes NULL if no callbacks are
                                required.
    @param[in]  sps_portnum     Requested source port number for the bandwidth
                                reserved SPS transmissions.
    @param[in]  event_portnum   Requested source port number for the bandwidth
                                reserved event transmissions, or  -1 for no
                                event port.
    @param[out] sps_sock        Pointer to the socket that is bound to the
                                requested port for Tx with reserved bandwidth.
    @param[out] sps_sockaddr    Pointer to the IPv6 UDP socket. \n
                                @vertspace{3}
                                The sockaddr_in6 buffer is initialized with the
                                IPv6 source address and source port that are
                                used for the bind() function.
                                The caller can then use the buffer for
                                subsequent sendto() function calls.
    @param[out] event_sock      Pointer to the socket that is bound to the
                                event-driven transmission port.
    @param[out] event_sockaddr  Pointer to the IPV6 UDP socket. \n
                                @vertspace{3}
                                The sockaddr_in6 buffer is initialized with the
                                IPv6 source address and source port that are
                                used for the bind() function.
                                The caller can then use the buffer for
                                subsequent sendto() function calls.

    @newpage
    @detdesc
    The radio attempts to reserve the flow with the specified size and rate
    passed in the request parameters.
    @par
    This function is used only for Tx. It sets up two UDP sockets on the
    requested two HLOS port numbers.
    @par
    For only a single SPS flow, indicate the event port number by using a
    negative number or NULL for the event_sockaddr. For a single event-driven
    port, use v2x_radio_tx_event_sock_create_and_bind() instead.
    @par
    Because the modem endpoint requires a specific global address, all data
    sent on these sockets must have a configurable IPv6 destination address for
    the non-IP traffic.
    @par
    @note1hang The Priority parameter of the SPS reservation is used only for
               the reserved Tx bandwidth (SPS) flow. The non-SPS/event-driven
               data sent to the event_portnum parameter is prioritized on the
               air, based on the IPv67 Traffic Class of the packet.
    @par
    The caller is expected to identify two unused local port numbers to use for
    binding: one for the event-driven flow and one for the SPS flow.
    @par
    This call is a blocking call. When it returns, the sockets are ready to
    use, assuming there is no error.

    @return
    0 -- On success.
    @par
    Otherwise:
     - EPERM -- Socket creation failed; for more details, check errno.h.
     - EAFNOSUPPORT -- On failure to find the interface.
     - EACCES -- On failure to get the MAC address of the device.

    @dependencies
    The interface must be pre-initialized with v2x_radio_init() or v2x_radio_init_v2(). The handle
    from that function must be used as the parameter in this function. @newpage
*/
extern int v2x_radio_tx_sps_sock_create_and_bind(v2x_radio_handle_t handle,
        v2x_tx_bandwidth_reservation_t *res,
        v2x_per_sps_reservation_calls_t *calls,
        int sps_portnum,
        int event_portnum,
        int *sps_sock,
        struct sockaddr_in6 *sps_sockaddr,
        int *event_sock,
        struct sockaddr_in6 *event_sockaddr);

/**
    Creates a socket with a bandwidth-reserved (SPS) Tx flow.

    @note1hang Only SPS transmissions are to be implemented for the socket,
               which is created as an IPv6 UDP socket.

    @datatypes
    #v2x_radio_handle_t \n
    #v2x_tx_bandwidth_reservation_t \n
    #v2x_per_sps_reservation_calls_t

    @param[in]  handle          Identifies the initialized Radio interface on
                                which this data connection is made.
    @param[in]  res             Pointer to the parameter structure (how often
                                the structure is sent, how many bytes are
                                reserved, and so on).
    @param[in]  calls           Pointer to reservation callbacks or listeners.
                                \n @vertspace{3}
                                This parameter is called when underlying radio
                                MAC parameters change related to the SPS
                                bandwidth contract.
                                For example, the callback after a
                                reservation change, or if the timing offset of
                                the SPS adjusts itself in response to
                                traffic. \n
                                @vertspace{3}
                                This parameter passes NULL if no callbacks are
                                required.
    @param[in]  sps_portnum     Requested source port number for the bandwidth
                                reserved SPS transmissions.
    @param[out] sps_sock        Pointer to the socket that is bound to the
                                requested port for Tx with reserved bandwidth.
    @param[out] sps_sockaddr    Pointer to the IPv6 UDP socket. \n
                                @vertspace{3}
                                The sockaddr_in6 buffer is initialized with the
                                IPv6 source address and source port that are
                                used for the bind() function.
                                The caller can then use the buffer for
                                subsequent sendto() function calls.

    @detdesc
    The radio attempts to reserve the flow with the specified size and rate
    passed in the request parameters.
    @par
    This function is used only for Tx. It sets up a UDP socket on the
    requested HLOS port number.
    Because the modem endpoint requires a specific global address, all data
    sent on the socket must have a configurable IPv6 destination address for
    the non-IP traffic.
    @par
    @note1hang The Priority parameter of the SPS reservation is used only for
               the reserved Tx bandwidth (SPS) flow.
    @par
    The caller is expected to identify an unused local port number for the SPS
    flow.
    @par
    This call is a blocking call. When it returns, the socket is ready to
    use, assuming there is no error.

    @return
    0 -- On success.
    @par
    Otherwise:
     - EPERM -- Socket creation failed; for more details, check errno.h.
     - EINVAL -- On failure to find the interface or get bad parameters.

    @dependencies
    The interface must be pre-initialized with v2x_radio_init() or v2x_radio_init_v2(). The handle
    from that function must be used as the parameter in this function. @newpage
*/
extern int v2x_radio_tx_sps_only_create(v2x_radio_handle_t handle,
    v2x_tx_bandwidth_reservation_t *res,
    v2x_per_sps_reservation_calls_t *calls,
    int sps_portnum,
    int *sps_sock,
    struct sockaddr_in6 *sps_sockaddr);

/**
    Adjusts the reservation for transmit bandwidth.

    @datatypes
    v2x_tx_bandwidth_reservation_t

    @param[out] sps_sock             Pointer to the socket bound to the
                                     requested port.
    @param[in]  updated_reservation  Pointer to a bandwidth reservation with
                                     new reservation information.

    @detdesc
    This function will not update reservation priority.
    Can be used as follows:
    - When the bandwidth requirement changes in periodicity (for example, due
      to an application layer DCC algorithm)
    - Because the packet size is increasing (for example, due to a growing path
        history size in a BSM).
    @par
    When the reservation change is complete, a callback to the structure is passed
    in a v2x_radio_init() or v2x_radio_init_v2() call.

    @return
    #V2X_STATUS_SUCCESS.
    @par
    Error code -- If there is a problem (see #v2x_status_enum_type).

    @dependencies
    An SPS flow must have been successfully initialized with the
    v2x_radio_tx_sps_sock_create_and_bind() method. @newpage
 */
extern v2x_status_enum_type v2x_radio_tx_reservation_change(int *sps_sock,
        v2x_tx_bandwidth_reservation_t *updated_reservation);
/** @} *//* end_addtogroup v2x_api_radio */

/** @ingroup v2x_deprecated_radio
    Obsolete. This API is not supported and will be removed in the future.

    Flushes the radio transmitter queue.

    This function is used for all packets on the specified interface that have
    not been sent yet. This action is necessary when a radio MAC address change
    is coordinated for anonymity.

    @param[in] interface  Name of the Radio interface operating system.

    @return
    None.
 */
extern void v2x_radio_tx_flush(char *interface);

/** @addtogroup v2x_api_radio
@{ */
/**
    Opens and binds an event-driven socket (one with no bandwidth reservation).

    @param[in]  interface        Pointer to the operating system name to use.
                                 This interface is an RmNet interface (HLOS).
    @param[in]  v2x_id           Used for transmissions that are ultimately
                                 mapped to an L2 destination address.
    @param[in]  event_portnum    Local port number to which the socket is
                                 bound. Used for transmissions of this ID.
    @param[out] event_sock_addr  Pointer to the sockaddr_ll structure buffer
                                 to be initialized.
    @param[out] sock             Pointer to the file descriptor. Loaded when
                                 the function is successful.

    @detdesc
    This function is used only for Tx when no periodicity is available for the
    application type. If you know your transmit data periodicity, use
    v2x_radio_tx_sps_sock_create_and_bind() instead.
    @par
    These event-driven sockets pay attention to QoS parameters in the IP
    socket.

    @return
    0 -- On success.
    @par
    Otherwise:
     - EPERM -- Socket creation failed; for more details, check errno.h.
     - EAFNOSUPPORT -- On failure to find the interface.
     - EACCES -- On failure to get the MAC address of the device. @newpage
 */
extern int v2x_radio_tx_event_sock_create_and_bind(const char *interface,
        int v2x_id,
        int event_portnum,
        struct sockaddr_in6 *event_sock_addr,
        int *sock);

/**
    Requests a channel utilization (CBP/CBR) measurement result on a
    channel.

    @datatypes
    #v2x_radio_handle_t \n
    #v2x_chan_meas_params_t

    @param[in] handle            Handle to the port.
    @param[in] measure_this_way  Indicates how and what to measure, and how
                                 often to send results. \n
                                 @vertspace{3}
                                 Some higher-level
                                 standards (like J2945/1 and ETSI TS102687 DCC)
                                 have specific time windows and items to
                                 measure.

    @detdesc
    This function uses the callbacks passed in during initialization to
    deliver the measurements. Measurement callbacks continue until the Radio
    interface is closed.

    @return
    #V2X_STATUS_SUCCESS -- The radio is now ready for data-plane sockets to be
    created and bound.
    @par
    #V2X_STATUS_FAIL -- CBR measurement is not supported yet.

    @dependencies
    The interface must be pre-initialized with v2x_radio_init() or v2x_radio_init_v2(). The handle
    from that function must be used as the parameter in this function. @newpage
 */
extern v2x_status_enum_type v2x_radio_start_measurements(v2x_radio_handle_t handle,
        v2x_chan_meas_params_t *measure_this_way);

/**
    Discontinues any periodic MAC/Phy channel measurements and the reporting of
    them via listener calls.

    @datatypes
    #v2x_radio_handle_t

    @param[in] handle  Handle to the radio measurements to be stopped.

    @return
    #V2X_STATUS_SUCCESS.

    @dependencies
    The measurements must have been started with
    v2x_radio_start_measurements(). @newpage
 */
extern v2x_status_enum_type v2x_radio_stop_measurements(v2x_radio_handle_t handle);
/** @} *//* end_addtogroup v2x_api_radio */

/** @ingroup v2x_deprecated_radio
    Obsolete. This API is not supported and will be removed in the future.

    Queries for the current V2X Rx or Tx status.

    @return
    Indication of success or failure (see #v2x_status_enum_type).
 */
v2x_event_t v2x_radio_get_status(void);

/** @addtogroup v2x_api_radio
@{ */
/**
    Closes a specified socket file descriptor and deregisters any modem
    resources associated with it (such as reserved SPS bandwidth contracts).

    @param[in] sock_fd  Socket file descriptor.

    @detdesc
    This function works on receive, SPS, or event-driven sockets.
    @par
    The socket file descriptor must be closed when the client exits. We
    recommend using a trap to catch controlled shutdowns.

    @return
    Integer value of the close(sock) operation.

    @dependencies
    The socket must have been opened with one of the following methods:
    - v2x_radio_rx_sock_create_and_bind()
    - v2x_radio_tx_sps_sock_create_and_bind()
    - v2x_radio_tx_sps_sock_create_and_bind_v2()
    - v2x_radio_tx_sps_only_create()
    - v2x_radio_tx_sps_only_create_v2()
    - v2x_radio_tx_event_sock_create_and_bind()
    - v2x_radio_tx_event_sock_create_and_bind_v2()
    - v2x_radio_tx_event_sock_create_and_bind_v3() @newpage
 */
extern int v2x_radio_sock_close(int *sock_fd);

/**
    Configures the V2X log level and destination for SDK and lower layers.

    @param[in] new_level   Log level to set to one of the standard syslog
                           levels (LOG_ERR, LOG_INFO, and so on).
    @param[in] use_syslog  Destination: send to stdout (0) or syslog
                           (otherwise).

    @return
    None.
 */
extern void v2x_radio_set_log_level(int new_level, int use_syslog);

/**
    Polls for the recent V2X status.

    @param[out] status_age_useconds  Pointer to the age in microseconds of the
                                     last event (radio status) that is being
                                     reported.

    @detdesc
    This function does not generate any modem control traffic. For efficiency,
    it simply returns the most recently cached value that was reported from the
    modem (often reported at a high rate or frequent rate from the modem).

    @return
    Indication of success or failure (see #v2x_status_enum_type). @newpage
 */
extern v2x_event_t cv2x_status_poll(uint64_t *status_age_useconds);

/**
    Triggers the modem to change its source L2 address by randomly generating
    a new address.

    @datatypes
    #v2x_radio_handle_t

    @param[in] handle  Initialized Radio interface on which this data
                       connection is made.

    @detdesc
    When the change is complete, clients are notified of the new L2 address
    via the #v2x_radio_calls_t::v2x_radio_l2_addr_changed_listener() callback
    function.

    @return
    0 -- On success.
    @par
    Otherwise:
     - EPERM -- Socket creation failed; for more details, check errno.h.
     - EAFNOSUPPORT -- On failure to find the interface.
     - EACCES -- On failure to get the MAC address of the device. @newpage
 */
extern int v2x_radio_trigger_l2_update(
    v2x_radio_handle_t handle);

/**
    Updates the list of malicious and trusted IDs tracked by the modem.

    @datatypes
    #trusted_ue_info_t

    @param[in] malicious_list_len  Number of malicious IDs in malicious_list.
    @param[in] malicious_list      List of malicious IDs.
    @param[in] trusted_list_len    Number of trusted IDs in trusted_list.
    @param[in] trusted_list        List of trusted IDs.

    @return
    0 -- On success.
    @par
    Otherwise:
     - EPERM -- Socket creation failed; for more details, check errno.h.
     - EAFNOSUPPORT -- On failure to find the interface.
     - EACCES -- On failure to get the MAC address of the device. @newpage
 */
int v2x_radio_update_trusted_ue_list(unsigned int malicious_list_len,
                                     unsigned int malicious_list[MAX_MALICIOUS_IDS_LIST_LEN],
                                     unsigned int trusted_list_len,
                                     trusted_ue_info_t trusted_list[MAX_TRUSTED_IDS_LIST_LEN]);

/**
    Creates and binds a socket with a bandwidth-reserved (SPS) Tx flow with the
    requested ID, priority, periodicity, and size on a specified source port
    number. The socket is created as an IPv6 UDP socket.

    This %v2x_radio_tx_sps_sock_create_and_bind_v2() method differs from
    v2x_radio_tx_sps_sock_create_and_bind() in that you can use the
    sps_flow_info parameter to specify transmission resource information about
    the Tx flow.

    @datatypes
    #v2x_radio_handle_t \n
    #v2x_tx_sps_flow_info_t \n
    #v2x_per_sps_reservation_calls_t

    @param[in]  handle          Identifies the initialized Radio interface on
                                which this data connection is made.
    @param[in]  sps_flow_info   Pointer to the flow information in the
                                v2x_tx_sps_flow_info_t structure.
    @param[in]  calls           Pointer to reservation callbacks or listeners.
                                \n @vertspace{3}
                                This parameter is called when underlying radio
                                MAC parameters change related to the SPS
                                bandwidth contract.
                                For example, the callback after a
                                reservation change, or if the timing offset of
                                the SPS adjusts itself in response to
                                traffic. \n @vertspace{3}
                                This parameter passes NULL if no callbacks are
                                required.
    @param[in]  sps_portnum     Requested source port number for the bandwidth
                                reserved SPS transmissions.
    @param[in]  event_portnum   Requested source port number for the bandwidth
                                reserved event transmissions, or  -1 for no
                                event port.
    @param[out] sps_sock        Pointer to the socket that is bound to the
                                requested port for Tx with reserved bandwidth.
    @param[out] sps_sockaddr    Pointer to the IPv6 UDP socket. \n
                                @vertspace{3}
                                The sockaddr_in6 buffer is initialized with the
                                IPv6 source address and source port that are
                                used for the bind() function.
                                The caller can then use the buffer for
                                subsequent sendto() function calls.
    @param[out] event_sock      Pointer to the socket that is bound to the
                                event-driven transmission port.
    @param[out] event_sockaddr  Pointer to the IPV6 UDP socket. \n
                                @vertspace{3}
                                The sockaddr_in6 buffer is initialized with the
                                IPv6 source address and source port that are
                                used for the bind() function.
                                The caller can then use the buffer for
                                subsequent sendto() function calls.

    @newpage
    @detdesc
    The radio attempts to reserve the flow with the specified size and rate
    passed in the request parameters.
    @par
    This function is used only for Tx. It sets up two UDP sockets on the
    requested two HLOS port numbers.
    @par
    For only a single SPS flow, indicate the event port number by using a
    negative number or NULL for the event_sockaddr. For a single event-driven
    port, use v2x_radio_tx_event_sock_create_and_bind() or
    v2x_radio_tx_event_sock_create_and_bind_v2() or
    v2x_radio_tx_event_sock_create_and_bind_v3() instead.
    @par
    Because the modem endpoint requires a specific global address, all data
    sent on these sockets must have a configurable IPv6 destination address for
    the non-IP traffic.
    @par
    @note1hang The Priority parameter of the SPS reservation is used only for
               the reserved Tx bandwidth (SPS) flow. The non-SPS/event-driven
               data sent to the event_portnum parameter is prioritized on the
               air, based on the IPv67 Traffic Class of the packet.
    @par
    The caller is expected to identify two unused local port numbers to use for
    binding: one for the event-driven flow and one for the SPS flow.
    @par
    This call is a blocking call. When it returns, the sockets are ready to
    use, assuming there is no error.

    @return
    0 -- On success.
    @par
    Otherwise:
     - EPERM -- Socket creation failed; for more details, check errno.h.
     - EAFNOSUPPORT -- On failure to find the interface.
     - EACCES -- On failure to get the MAC address of the device.

    @dependencies
    The interface must be pre-initialized with v2x_radio_init() or v2x_radio_init_v2(). The handle
    from that function must be used as the parameter in this function. @newpage
*/
extern int v2x_radio_tx_sps_sock_create_and_bind_v2(
    v2x_radio_handle_t handle,
    v2x_tx_sps_flow_info_t *sps_flow_info,
    v2x_per_sps_reservation_calls_t *calls,
    int sps_portnum,
    int event_portnum,
    int *sps_sock,
    struct sockaddr_in6 *sps_sockaddr,
    int *event_sock,
    struct sockaddr_in6 *event_sockaddr);

/**
    Creates a socket with a bandwidth-reserved (SPS) Tx flow.

    @note1hang Only SPS transmissions are to be implemented for the socket,
               which is created as an IPv6 UDP socket.

    This %v2x_radio_tx_sps_only_create_v2() method differs from
    v2x_radio_tx_sps_only_create() in that you can use the sps_flow_info
    parameter to specify transmission resource information about the Tx flow.

    @datatypes
    #v2x_radio_handle_t \n
    #v2x_tx_sps_flow_info_t \n
    #v2x_per_sps_reservation_calls_t

    @param[in]  handle          Identifies the initialized Radio interface on
                                which this data connection is made.
    @param[in]  sps_flow_info   Pointer to the flow information in the
                                v2x_tx_sps_flow_info_t structure.
    @param[in]  calls           Pointer to reservation callbacks or listeners.
                                \n @vertspace{3}
                                This parameter is called when underlying radio
                                MAC parameters change related to the SPS
                                bandwidth contract.
                                For example, the callback after a
                                reservation change, or if the timing offset of
                                the SPS adjusts itself in response to
                                traffic. \n @vertspace{3}
                                This parameter passes NULL if no callbacks are
                                required.
    @param[in]  sps_portnum     Requested source port number for the bandwidth
                                reserved SPS transmissions.
    @param[out] sps_sock        Pointer to the socket that is bound to the
                                requested port for Tx with reserved bandwidth.
    @param[out] sps_sockaddr    Pointer to the IPv6 UDP socket. \n
                                @vertspace{3}
                                The sockaddr_in6 buffer is initialized with the
                                IPv6 source address and source port that are
                                used for the bind() function.
                                The caller can then use the buffer for
                                subsequent sendto() function calls.

    @detdesc
    The radio attempts to reserve the flow with the specified size and rate
    passed in the request parameters.
    @par
    This function is used only for Tx. It sets up a UDP socket on the
    requested HLOS port number.
    Because the modem endpoint requires a specific global address, all data
    sent on the socket must have a configurable IPv6 destination address for
    the non-IP traffic.
    @par
    The caller is expected to identify an unused local port number to use for
    binding the SPS flow.
    @par
    This call is a blocking call. When it returns, the socket is ready to
    use, assuming there is no error. @newpage

    @return
    0 -- On success.
    @par
    Otherwise:
     - EPERM -- Socket creation failed; for more details, check errno.h.
     - EINVAL -- On failure to find the interface or get bad parameters.

    @dependencies
    The interface must be pre-initialized with v2x_radio_init() or v2x_radio_init_v2(). The handle
    from that function must be used as the parameter in this function. @newpage
*/
int v2x_radio_tx_sps_only_create_v2(v2x_radio_handle_t handle,
    v2x_tx_sps_flow_info_t *sps_flow_info,
    v2x_per_sps_reservation_calls_t *calls,
    int sps_portnum,
    int *sps_sock,
    struct sockaddr_in6 *sps_sockaddr);

/**
    Adjusts the reservation for transmit bandwidth.

    This %v2x_radio_tx_reservation_change_v2() method differs from
    v2x_radio_tx_reservation_change() in that you can use the updated_flow_info
    parameter to specify transmission resource information about the Tx flow.

    @datatypes
    v2x_tx_sps_flow_info_t

    @param[out] sps_sock           Pointer to the socket bound to the requested
                                   port.
    @param[in]  updated_flow_info  Pointer to the new reservation information.

    @detdesc
    This function will not update reservation priority.
    Can be used as follows:
    - When the bandwidth requirement changes in periodicity (for example, due
      to an application layer DCC algorithm)
    - Because the packet size is increasing (for example, due to a growing path
      history size in a BSM).
    @par
    When the reservation change is complete, a callback to the structure is
    passed in a v2x_radio_init() or v2x_radio_init_v2() call.

    @return
    #V2X_STATUS_SUCCESS.
    @par
    Error code -- On failure (see #v2x_status_enum_type).

    @dependencies
    An SPS flow must have been successfully initialized with
    v2x_radio_tx_sps_sock_create_and_bind() or
    v2x_radio_tx_sps_sock_create_and_bind_v2(). @newpage
 */
extern v2x_status_enum_type v2x_radio_tx_reservation_change_v2(
    int *sps_sock,
    v2x_tx_sps_flow_info_t *updated_flow_info);
/** @} *//* end_addtogroup v2x_api_radio */


/** @ingroup v2x_deprecated_radio
    Deprecated. Pass #traffic_ip_type_t on flow creation.

    Opens and binds an event-driven socket (one with no bandwidth reservation).

    This %v2x_radio_tx_event_sock_create_and_bind_v2() method differs from
    v2x_radio_tx_event_sock_create_and_bind() in that you can use the
    event_flow_info parameter to specify transmission resource information
    about the Tx flow.

    @datatypes
    v2x_tx_flow_info_t

    @param[in]  interface        Pointer to the operating system name to use.
                                 This interface is an RmNet interface (HLOS).
    @param[in]  v2x_id           Used for transmissions that are ultimately
                                 mapped to an L2 destination address.
    @param[in]  event_portnum    Local port number to which the socket is
                                 bound. Used for transmissions of this ID.
    @param[in]  event_flow_info  Pointer to the event flow parameters.
    @param[out] event_sock_addr  Pointer to the sockaddr_ll structure buffer
                                 to be initialized.
    @param[out] sock             Pointer to the file descriptor. Loaded when
                                 the function is successful.

    @detdesc
    This function is used only for Tx when no periodicity is available for the
    application type. If you know your transmit data periodicity, use
    v2x_radio_tx_sps_sock_create_and_bind() or
    v2x_radio_tx_sps_sock_create_and_bind_v2() instead.
    @par
    These event-driven sockets pay attention to QoS parameters in the IP
    socket.

    @return
    0 -- On success.
    @par
    Otherwise:
     - EPERM -- Socket creation failed; for more details, check errno.h.
     - EAFNOSUPPORT -- On failure to find the interface.
     - EACCES -- On failure to get the MAC address of the device. @newpage
 */
extern int v2x_radio_tx_event_sock_create_and_bind_v2(
    const char *interface,
    int v2x_id,
    int event_portnum,
    v2x_tx_flow_info_t *event_flow_info,
    struct sockaddr_in6 *event_sock_addr,
    int *sock);

/** @addtogroup v2x_api_radio
@{ */
/**
    Adjusts the flow parameters for an existing Tx event socket.

    @datatypes
    #v2x_tx_flow_info_t

    @param[out] sock               Pointer to the socket bound to the
                                   requested port.
    @param[in]  updated_flow_info  Pointer to the new flow parameters.

    @detdesc
    When the reservation change is complete, a callback to the structure is
    passed in a v2x_radio_init() or v2x_radio_init_v2() call.
    @par
    This call is a blocking call. When it returns, the socket is ready to be
    use, assuming there is no error.

    @return
    #V2X_STATUS_SUCCESS.
    @par
    Error code -- On failure (see #v2x_status_enum_type).

    @dependencies
    An event flow must have been successfully initialized with
    v2x_radio_tx_event_sock_create_and_bind() or
    v2x_radio_tx_event_sock_create_and_bind_v2()
    v2x_radio_tx_event_sock_create_and_bind_v3(). @newpage
 */
extern v2x_status_enum_type v2x_radio_tx_event_flow_info_change(
    int *sock,
    v2x_tx_flow_info_t *updated_flow_info);

/**
    Updates the V2X radio configuration file.

    @param[in] config_file_path  Pointer to the path of the configuration file.

    @detdesc
    The V2X radio status must be INACTIVE. If the V2X status is
    ACTIVE or SUSPENDED (see #v2x_event_t), call stop_v2x_mode() first.
    @par
    This call is a blocking call. When it returns the configuration has
    been updated, assuming no error.

    @return
    #V2X_STATUS_SUCCESS.
    @par
    Otherwise:
    - #V2X_STATUS_EALREADY -- Failure because V2X status is not #V2X_INACTIVE.
    - #V2X_STATUS_FAIL -- Other failure.

    @dependencies
    V2X radio status must be #V2X_INACTIVE (#v2x_event_t). @newpage
 */
extern v2x_status_enum_type v2x_update_configuration(const char *config_file_path);

/**
    Starts V2X mode.

    The V2X radio status must be INACTIVE. If the status is ACTIVE or
    SUSPENDED (see #v2x_event_t), call stop_v2x_mode() first.

    This call is a blocking call. When it returns, V2X mode has been started,
    assuming there is no error.

    @return
    #V2X_STATUS_SUCCESS.
    @par
    Otherwise:
    - #V2X_STATUS_EALREADY -- Failure because V2X mode is already started.
    - #V2X_STATUS_FAIL -- Other failure.

    @dependencies
    V2X radio status must be #V2X_INACTIVE (#v2x_event_t).
 */
extern v2x_status_enum_type start_v2x_mode();

/**
    Stops V2X mode.

    The V2X radio status must be ACTIVE or SUSPENDED (see #v2x_event_t).
    If the status is INACTIVE, call start_v2x_mode() first.

    This call is a blocking call. When it returns, V2X mode has been stopped,
    assuming there is no error.

    @return
    #V2X_STATUS_SUCCESS.
    @par
    Otherwise:
    - #V2X_STATUS_EALREADY -- Failure because V2X mode is already stopped.
    - #V2X_STATUS_FAIL -- Other failure.

    @dependencies
    V2X radio status must be #V2X_ACTIVE, #V2X_TX_SUSPENDED, #V2X_RX_SUSPENDED,
    or #V2X_TXRX_SUSPENDED. @newpage
 */
extern v2x_status_enum_type stop_v2x_mode();

/**
    Initializes the Radio interface and sets the callback that will be used
    when events in the radio change (including when radio initialization is
    complete).

    @datatypes
    #traffic_ip_type_t \n
    #v2x_concurrency_sel_t \n
    #v2x_radio_calls_t

    @param[in] ip_type         The Ip or non-Ip interface.
    @param[in] mode            WAN concurrency mode, although the radio might
                               not support concurrency. Errors can be generated.
    @param[in] callbacks       Pointer to the v2x_radio_calls_t structure that
                               is prepopulated with function pointers used
                               during radio events (such as loss of time
                               synchronization or accuracy) for subscribers. \n
                               @vertspace{3}
                               This parameter also points to a callback for
                               this initialization function.
    @param[in] context         Voluntary pointer to the first parameter on the
                               callback.

    @detdesc
    This function call is a nonblocking, and it is a control plane action.
    @par
    Use v2x_radio_deinit() when radio operations are complete.
    @par
    @note1hang Currently, the channel and transmit power are not specified.
               They are specified with a subsequent call to
               #v2x_radio_calls_t::v2x_radio_init_complete() when
               initialization is complete.

    @return
    Handle to the specified initialized radio. The handle is used for
    reconfiguring, opening or changing, and closing reservations.
    @par
    #V2X_RADIO_HANDLE_BAD -- If there is an error. No initialization callback
    is made. @newpage
 */
v2x_radio_handle_t v2x_radio_init_v2(traffic_ip_type_t ip_type,
                                     v2x_concurrency_sel_t mode,
                                     v2x_radio_calls_t *callbacks_p,
                                     void *ctx_p);
/**
    Opens and binds an event-driven socket (one with no bandwidth reservation).

    This %v2x_radio_tx_event_sock_create_and_bind_v3() method differs from
    v2x_radio_tx_event_sock_create_and_bind_v2() in that you can use the traffic_ip_type_t
    parameter to specify traffic ip type instead of requiring the interface name.

    @datatypes
    v2x_tx_flow_info_t
    traffic_ip_type_t

    @param[in]  ip_type          traffice_ip_type.
    @param[in]  v2x_id           Used for transmissions that are ultimately
                                 mapped to an L2 destination address.
    @param[in]  event_portnum    Local port number to which the socket is
                                 bound. Used for transmissions of this ID.
    @param[in]  event_flow_info  Pointer to the event flow parameters.
    @param[out] event_sock_addr  Pointer to the sockaddr_ll structure buffer
                                 to be initialized.
    @param[out] sock             Pointer to the file descriptor. Loaded when
                                 the function is successful.

    @detdesc
    This function is used only for Tx when no periodicity is available for the
    application type. If you know your transmit data periodicity, use
    v2x_radio_tx_sps_sock_create_and_bind() or
    v2x_radio_tx_sps_sock_create_and_bind_v2() instead.
    @par
    These event-driven sockets pay attention to QoS parameters in the IP
    socket.

    @return
    0 -- On success.
    @par
    Otherwise:
     - EPERM -- Socket creation failed; for more details, check errno.h.
     - EAFNOSUPPORT -- On failure to find the interface.
     - EACCES -- On failure to get the MAC address of the device.
 */
int v2x_radio_tx_event_sock_create_and_bind_v3(
        traffic_ip_type_t ip_type,
        int v2x_id,
        int event_portnum,
        v2x_tx_flow_info_t *event_flow_info,
        struct sockaddr_in6 *event_sockaddr,
        int *sock);

/**
    Returns interface name set during radio initialization.

    @datatypes
    traffic_ip_type_t

    @param[in]  ip_type     traffic_ip_type_t
    @param[out] iface_name  pointer to buffer for interface name
    @param[in]  buffer_len  length of the buffer passed for interface name.
 *                          Must be at least the max buffer size for an interface name (IFNAMSIZE).
    @detdesc
    This function should only be called after successfully initializing a radio.

    @return
    #V2X_STATUS_SUCCESS.
    @par
    #V2X_STATUS_FAIL -- If there is an error. Interface name will be an
    empty string. @newpage
 */
v2x_status_enum_type get_iface_name(traffic_ip_type_t ip_type, char * iface_name, size_t buffer_len);

/** @} *//* end_addtogroup v2x_api_radio */

/*
 * Testing functions mainly for sim environment
 * but also useful for IPV6 testing
 */
extern void v2x_set_dest_ipv6_addr(char *new_addr);
extern void v2x_set_dest_port(uint16_t portnum);
extern void v2x_set_rx_port(uint16_t portnum);
void v2x_disable_socket_connect();


#ifdef __cplusplus
}
#endif

#endif // __V2X_RADIO_APIS_H__
