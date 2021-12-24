/*
 *  Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef CV2X_QMI_H
#define CV2X_QMI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <data/dsi_netctrl.h>
#include <qmi-framework/qmi_client.h>

#define CV2X_QMI_TIMEOUT_MS 12000
#define CV2X_COND_TIMEOUT_MS 2000
#define MAX_DSI_RETRIES 20
#define APN_NAME_V2X_IP "v2x_ip"
#define APN_NAME_V2X_NON_IP "v2x_non_ip"
#define MAX_INTERFACE_NAME (DSI_CALL_INFO_DEVICE_NAME_MAX_LEN + 1)
#define MAX_V2X_SUB QMI_WDS_V2X_MAX_SUB_V01
#define CV2X_MAX_RX_POOL_LIST 4
#define CV2X_MAX_TX_POOL_LIST 2

typedef enum {
    CV2X_STATUS_INACTIVE = 0,
    CV2X_STATUS_ACTIVE,
    CV2X_STATUS_SUSPENDED,
} cv2x_status_enum_t;

typedef enum {
    CV2X_STATUS_CAUSE_TIMING_INVALID = 0,
    CV2X_STATUS_CAUSE_CONFIG_INVALID,
    CV2X_STATUS_CAUSE_UE_MODE_INVALID,
    CV2X_STATUS_CAUSE_OUT_OF_ALLOWED_GEOPOLYGON,
} cv2x_status_cause_enum_t;

typedef struct {
    cv2x_status_enum_t status;
    cv2x_status_cause_enum_t cause;
} cv2x_multi_pool_status_t;

typedef struct {
    uint8_t tx_status_valid;
    cv2x_status_enum_t tx_status;
    uint8_t rx_status_valid;
    cv2x_status_enum_t rx_status;
    uint8_t cbr_value_valid;
    uint8_t cbr_value;
    uint8_t tx_cause_valid;
    cv2x_status_cause_enum_t tx_cause;
    uint8_t rx_cause_valid;
    cv2x_status_cause_enum_t rx_cause;
    uint8_t rx_multi_pool_status_valid;
    uint32_t rx_multi_pool_status_len;
    cv2x_multi_pool_status_t rx_multi_pool_status[CV2X_MAX_RX_POOL_LIST];
    uint8_t tx_multi_pool_status_valid;
    uint32_t tx_multi_pool_status_len;
    cv2x_multi_pool_status_t tx_multi_pool_status[CV2X_MAX_TX_POOL_LIST];
    uint8_t cbr_multi_pool_value_valid;
    uint32_t cbr_multi_pool_value_len;
    uint8_t cbr_multi_pool_value[CV2X_MAX_RX_POOL_LIST];
    float time_uncertainty;
    uint8_t time_uncertainty_valid;
} cv2x_status_t;

/* Callback function to a single listener of this process, no context pointer
 * provided, since only one listener total per library instance */
typedef void (*cv2x_status_cb_t)(cv2x_status_t status);

/* Callback function to a single listener of this process, no context pointer
 * provided, since only one listener total per library instance */
typedef void (*cv2x_l2addr_cb_t)(uint32_t new_l2addr);

typedef enum {
    CV2X_DATA_CALL_IP = 0,
    CV2X_DATA_CALL_NON_IP,
} data_call_type_t;

typedef enum {
    CV2X_DATA_CALL_OFFLINE = 0,
    CV2X_DATA_CALL_ONLINE,
} data_call_status_t;

typedef struct {
    data_call_type_t type;
    char interface_name[MAX_INTERFACE_NAME];
    uint8_t profile_valid;
    uint8_t profile_index;
    dsi_hndl_t dsi_client;
    qmi_client_type wds_client;
    qmi_cci_os_signal_type wds_os_params;
    /* Protects shared objects */
    pthread_mutex_t lock;
    /* Shared objects */
    data_call_status_t status;
} data_call_info_t;

typedef enum {
    CV2X_RETX_AUTO = 0,
    CV2X_RETX_ON,
    CV2X_RETX_OFF,
} retx_enum_t;

typedef struct {
    uint32_t service_id;
    uint8_t priority;
    uint32_t periodicity;
    uint32_t msg_size;
    uint16_t sps_port;
    uint8_t non_sps_port_valid;
    uint16_t non_sps_port;
    uint8_t tx_pool_id_valid;
    uint8_t tx_pool_id;
    uint8_t peak_tx_power_valid;
    int32_t peak_tx_power;
    uint8_t mcs_index_valid;
    uint8_t mcs_index;
    uint8_t retx_setting_valid;
    retx_enum_t retx_setting;
} sps_flow_t;

typedef struct {
    uint32_t service_id;
    uint16_t port;
    uint8_t tx_pool_id_valid;
    uint8_t tx_pool_id;
    uint8_t peak_tx_power_valid;
    int32_t peak_tx_power;
    uint8_t mcs_index_valid;
    uint8_t mcs_index;
    uint8_t retx_setting_valid;
    retx_enum_t retx_setting;
} non_sps_flow_t;

typedef struct {
    uint8_t wildcard_enabled;
    uint32_t service_id_len;
    uint32_t service_id[MAX_V2X_SUB];
    uint16_t dest_port;
} service_sub_info_t;

typedef struct {
    uint32_t src_l2_id;
    uint16_t time_confidence_level;
    uint16_t position_confidence_level;
    uint32_t propagation_delay;
} trusted_ue_info_t;

typedef struct cv2x_state {
    /* QMI services */
    qmi_client_type nas_client;
    qmi_client_os_params nas_os_params;
    qmi_client_ind_cb nas_callback;
    qmi_client_type wds_client;
    qmi_client_os_params wds_os_params;
    qmi_client_ind_cb wds_callback;

    /* Protects shared objects */
    pthread_mutex_t lock;
    /* Shared objects */
    cv2x_status_t cv2x_status;
    /* Non-shared objects */
    data_call_info_t data_call_ip;
    data_call_info_t data_call_non_ip;

    /* Optional callbacks to listeners */
    cv2x_status_cb_t v2x_status_cb;
    cv2x_l2addr_cb_t l2_addr_cb;
} cv2x_state_t;

/* Initialize the library, allocate state variables */
cv2x_state_t *init_v2x_library();

/* De-initializes the library, de-allocates memory */
void deinit_v2x_library(cv2x_state_t *state);

/* Initialize all QMI services into the library state */
int init_qmi_services(cv2x_state_t *state);

/* Deinit all QMI services */
void deinit_qmi_services(cv2x_state_t *state);

/* Register to receive network access service notifications */
int register_nas_callback(qmi_client_type client);

/* Register to receive wireless data service notifications */
int register_wds_callback(qmi_client_type client);

/* Read the V2X radio status for TX and RX into the status variable.
 * The CBR value is not valid and has to be obtained via RRC indication */
int get_v2x_radio_status(qmi_client_type client, cv2x_status_t *status,
                         cv2x_state_t *state);

/* Start the V2X radio operation */
int start_v2x_radio(qmi_client_type client);

/* Stop the V2X radio operation */
int stop_v2x_radio(qmi_client_type client);

/* Setup the dummy APN profiles needed for V2X, create the profiles
 * if they do not exist yet
 */
int setup_v2x_profiles(qmi_client_type client, cv2x_state_t *state);

/* Bind a WDS client to IPv6, this client has to be associated with
 * a data connection */
int set_ip_preference_ipv6(qmi_client_type client);

/* Bind a WDS client to a MUX data port, this client has to be associated
 * with a data connection */
int bind_mux_data_port(qmi_client_type client, uint8_t link_id);

/* Bind a WDS client to a subscription, this client has to be associated
 * with a data connection */
int bind_mux_subscription(qmi_client_type client);

/* Initialize the DSI library state */
int start_dsi_library(cv2x_state_t *state);

/* Clean up the DSI library */
int stop_dsi_library();

/* Start the DSI service for a V2X connection */
int start_dsi_service(data_call_info_t *data_call);

/* Releases all resources associated with the DSI service, ends any
 * related data calls that are in place */
void stop_dsi_service(data_call_info_t *data_call);

/* Start a data connection in V2X mode, there are two options, IP and NON_IP.
 * This API is not thread-safe */
int start_v2x_data_call(data_call_info_t *data_call);

/* Tear-down a V2X data connection. This API is not thread-safe */
int stop_v2x_data_call(data_call_info_t *data_call);

/* Obtain reference to the WDS client related to a specific data call */
qmi_client_type get_wds_client_by_interface(data_call_type_t type, cv2x_state_t *state);

/* Subscribe to receive all V2X messages */
int subscribe_v2x_service_wildcard(qmi_client_type client, uint32_t req_id, uint16_t port);

/* Unsubscribe from all V2X messages, specific messages can still be received */
int unsubscribe_v2x_service_wildcard(qmi_client_type client, uint32_t req_id);

/* Subscribe to a list of V2X messages by service ID, the port number
 * is determined by the TX flow registered port */
int subscribe_v2x_service_list(qmi_client_type client, uint32_t req_id,
                               uint32_t id_list_len, uint32_t *id_list);

/* Unsubscribe from a list of V2X messages by service ID */
int unsubscribe_v2x_service_list(qmi_client_type client, uint32_t req_id,
                                 uint32_t id_list_len, uint32_t *id_list);

/* Obtain information about service subscription */
int get_v2x_subscribe_list(qmi_client_type client, uint32_t req_id,
                           service_sub_info_t *service_info);

/* Register for a semi persistent schedule flow for transmitting V2X messages, the port number
 * for RX is the same as the SPS source TX port if wildcard is disabled. SPS flow APIs are not
 * thread-safe. Result is returned in sps_id if the call is successful */
int register_v2x_sps_flow(qmi_client_type client, uint32_t req_id, sps_flow_t flow, uint8_t *sps_id);

/* De-register to stop transmitting a semi persistent schedule flow of V2X messages.
 * SPS flow APIs are not thread-safe */
int deregister_v2x_sps_flow(qmi_client_type client, uint32_t req_id, uint8_t sps_id);

/* Update parameters of a semi persistent schedule flow. SPS flow APIs are not thread-safe */
int update_v2x_sps_flow(qmi_client_type client, uint32_t req_id, uint8_t sps_id,
                        uint32_t periodicity, uint32_t msg_size);

/* Update parameters of a semi persistent schedule flow. SPS flow APIs are not thread-safe.
 * Added new parameters for AT_CS */
int update_v2x_sps_flow_v02(qmi_client_type client, uint32_t req_id, uint8_t sps_id,
                            uint32_t periodicity, uint32_t msg_size, uint8_t tx_pool_id_valid,
                            uint8_t tx_pool_id, uint8_t peak_tx_power_valid,
                            uint32_t peak_tx_power, uint8_t mcs_index_valid, uint8_t mcs_index,
                            uint8_t retx_setting_valid, uint8_t retx_setting);

/* Obtain information about a semi persistent schedule flow */
int get_v2x_sps_flow_info(qmi_client_type client, uint32_t req_id, uint8_t sps_id,
                          sps_flow_t *flow);

/* Register for a non-SPS flow or event driven flow to transmit V2X messages,
 * the port number for RX is the same as the non-SPS source TX port if wildcard
 * is disabled */
int register_v2x_non_sps_flow_list(qmi_client_type client, uint32_t req_id,
                                   uint32_t flow_len, non_sps_flow_t *flow);

/* Register for a non-SPS flow or event driven flow to transmit V2X messages,
 * the port number for RX is the same as the non-SPS source TX port if wildcard
 * is disabled. This is the new version of the API for AT-CS. It supports a single
 * flow and additional options */
int register_v2x_non_sps_flow(qmi_client_type client, uint32_t req_id,
                              non_sps_flow_t flow);

/* De-register to stop transmitting a non-SPS flow of V2X messages */
int deregister_v2x_non_sps_flow_list(qmi_client_type client, uint32_t req_id,
                                     uint32_t flow_len, non_sps_flow_t *flow);

/* Register the status callback used to deliver changes in TX/RX ready/suspend,
 * and periodic CBR/measurements */
void subscribe_v2x_status_callback(cv2x_state_t *state, cv2x_status_cb_t callback);

/* Register the status callback used to deliver changes in TX/RX ready/suspend,
 * and periodic CBR/measurements */
void subscribe_l2addr_change_callback(cv2x_state_t *state, cv2x_l2addr_cb_t callback);

/* Request an update of the L2 SRC address */
int update_v2x_l2_address(qmi_client_type client);

/* Update the V2X XML config file. Reads the file from the disk in file_path
 * and sends it to the modem */
int update_v2x_config_file(qmi_client_type client, char *file_path);

/* Send a list of malicious L2 addresses and a list of trusted nodes with
 * additional information on each one */
int set_tunnel_mode_info(qmi_client_type client,
                         uint32_t malicious_list_len,
                         uint32_t *malicious_list,
                         uint32_t trusted_list_len,
                         trusted_ue_info_t *trusted_ue_info_list);

#ifdef __cplusplus
}
#endif

#endif /* CV2X_QMI_H */
