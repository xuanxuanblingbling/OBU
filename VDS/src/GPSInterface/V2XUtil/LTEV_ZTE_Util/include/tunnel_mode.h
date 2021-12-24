/*
 *  Copyright (c) 2019 Qualcomm Technologies, Inc.
 *  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef TUNNEL_MODE_H
#define TUNNEL_MODE_H

#include <pthread.h>
#include <telux/cv2x/legacy/v2x_radio_api.h>

#define SPEED_OF_LIGHT (299792458) /* (m/s) */

typedef struct _tunnel_mode_data_t {
    bool trusted; /* True is truested UE, false is malicious */
    uint32_t source_l2_id;
    uint16_t time_confidence_level;
    float time_uncertainty;
    uint16_t position_confidence_level;
    uint32_t propagation_delay;
} tunnel_mode_data_t;

typedef struct _tunnel_mode_options_t {
    bool alternate_trusted;
    uint16_t alternate_trusted_time;
    uint64_t previous_alternate_timestamp;
    uint64_t entry_timeout_us;
    uint64_t update_period_ns;
} tunnel_mode_options_t;

/* RV map structures */
#define RV_MAP_SIZE (10u)

typedef struct _rv_map_entry_t {
    uint32_t l2_id; /* L2 ID is map key */
    bool valid;
    tunnel_mode_data_t tunnel;
    bool has_rx_timestamp;
    uint64_t rx_timestamp;
} rv_map_entry_t;

typedef struct _rv_map_t {
    rv_map_entry_t entries[RV_MAP_SIZE];
    size_t max_size;
    size_t current_size;
    uint64_t entry_timeout; /* (us) Time after RX that entry will be purged */
    pthread_mutex_t mutex;
} rv_map_t;

#define TIME_CONFIDENCE_SIZE (40)
#define V2X_TIME_UNCERTAINTY_UNAVAILABLE       (-1.0f) /**<  time confidence is invalid  */
#define V2X_TIME_UNCERTAINTY_100_SECONDS       (100.0f * 1000.0f) /**<  1:  better than 100 seconds  */
#define V2X_TIME_UNCERTAINTY_50_SECONDS        (50.0f * 1000.0f) /**<  2:  better than 50 seconds  */
#define V2X_TIME_UNCERTAINTY_20_SECONDS        (20.0f  * 1000.0f) /**<  3:  better than 20 seconds  */
#define V2X_TIME_UNCERTAINTY_10_SECONDS        (10.0f  * 1000.0f) /**<  4:  better than 10 seconds  */
#define V2X_TIME_UNCERTAINTY_2_SECONDS         (2.0f   * 1000.0f) /**<  5:  better than 2 seconds  */
#define V2X_TIME_UNCERTAINTY_1_SECONDS         (1.0f   * 1000.0f) /**<  6:  better than 1 seconds  */
#define V2X_TIME_UNCERTAINTY_500_MILI_SECONDS  (500.0f)  /**<  7:  better than 500 mili-seconds  */
#define V2X_TIME_UNCERTAINTY_200_MILI_SECONDS  (200.0f)  /**<  8:  better than 200 mili-seconds  */
#define V2X_TIME_UNCERTAINTY_100_MILI_SECONDS  (100.0f)  /**<  9:  better than 100 mili-seconds  */
#define V2X_TIME_UNCERTAINTY_50_MILI_SECONDS   (50.0f)  /**<  10: better than 50 mili-seconds  */
#define V2X_TIME_UNCERTAINTY_20_MILI_SECONDS   (20.0f)  /**<  11: better than 20 mili-seconds  */
#define V2X_TIME_UNCERTAINTY_10_MILI_SECONDS   (10.0f)  /**<  12: better than 10 mili-seconds  */
#define V2X_TIME_UNCERTAINTY_5_MILI_SECONDS    (5.0f)  /**<  13: better than 50 mili-seconds  */
#define V2X_TIME_UNCERTAINTY_2_MILI_SECONDS    (2.0f)  /**<  14: better than 20 mili-seconds  */
#define V2X_TIME_UNCERTAINTY_1_MILI_SECONDS    (1.0f)  /**<  15: better than 1 mili-seconds  */
#define V2X_TIME_UNCERTAINTY_500_MICRO_SECONDS (500.0f / 1000.0f)  /**<  16: better than 500 micro-seconds  */
#define V2X_TIME_UNCERTAINTY_200_MICRO_SECONDS (200.0f / 1000.0f)  /**<  17: better than 100 micro-seconds  */
#define V2X_TIME_UNCERTAINTY_100_MICRO_SECONDS (100.0f / 1000.0f)  /**<  18: better than 100 micro-seconds  */
#define V2X_TIME_UNCERTAINTY_50_MICRO_SECONDS  (50.0f  / 1000.0f)  /**<  19: better than 50 micro-seconds  */
#define V2X_TIME_UNCERTAINTY_20_MICRO_SECONDS  (20.0f  / 1000.0f)  /**<  20: better than 20 micro-seconds  */
#define V2X_TIME_UNCERTAINTY_10_MICRO_SECONDS  (10.0f  / 1000.0f)  /**<  21: better than 10 micro-seconds  */
#define V2X_TIME_UNCERTAINTY_5_MICRO_SECONDS   (5.0f   / 1000.0f)  /**<  22: better than 5 micro-seconds  */
#define V2X_TIME_UNCERTAINTY_2_MICRO_SECONDS   (2.0f   / 1000.0f)  /**<  23: better than 2 micro-seconds  */
#define V2X_TIME_UNCERTAINTY_1_MICRO_SECONDS   (1.0f   / 1000.0f)  /**<  24: better than 1 micro-seconds  */
#define V2X_TIME_UNCERTAINTY_500_NANO_SECONDS  (500.0f  / 1000000.0f)  /**<  25: better than 500 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_200_NANO_SECONDS  (200.0f  / 1000000.0f)  /**<  26: better than 200 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_100_NANO_SECONDS  (100.0f  / 1000000.0f)  /**<  27: better than 100 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_50_NANO_SECONDS   (50.0f   / 1000000.0f)  /**<  28: better than 50 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_20_NANO_SECONDS   (20.0f   / 1000000.0f)  /**<  29: better than 20 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_10_NANO_SECONDS   (10.0f   / 1000000.0f)  /**<  30: better than 10 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_5_NANO_SECONDS    (5.0f    / 1000000.0f)  /**<  31: better than 5 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_2_NANO_SECONDS    (2.0f    / 1000000.0f)  /**<  32: better than 2 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_1_NANO_SECONDS    (1.0f    / 1000000.0f)  /**<  33: better than 1 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_0_5_NANO_SECONDS  (0.5f    / 1000000.0f)  /**<  34: better than 0.5 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_0_2_NANO_SECONDS  (0.2f    / 1000000.0f)  /**<  35: better than 0.2 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_0_1_NANO_SECONDS  (0.1f    / 1000000.0f)  /**<  36: better than 0.1 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_0_05_NANO_SECONDS (0.05f   / 1000000.0f)  /**<  37: better than 0.05 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_0_02_NANO_SECONDS (0.02f   / 1000000.0f)  /**<  38: better than 0.02 nano-seconds  */
#define V2X_TIME_UNCERTAINTY_0_01_NANO_SECONDS (0.01f   / 1000000.0f)  /**<  39: better than 0.01 nano-seconds  */

static float time_confidence_to_uncertainty_map[TIME_CONFIDENCE_SIZE] = {
    V2X_TIME_UNCERTAINTY_UNAVAILABLE,
    V2X_TIME_UNCERTAINTY_100_SECONDS,
    V2X_TIME_UNCERTAINTY_50_SECONDS,
    V2X_TIME_UNCERTAINTY_20_SECONDS,
    V2X_TIME_UNCERTAINTY_10_SECONDS,
    V2X_TIME_UNCERTAINTY_2_SECONDS,
    V2X_TIME_UNCERTAINTY_1_SECONDS,
    V2X_TIME_UNCERTAINTY_500_MILI_SECONDS,
    V2X_TIME_UNCERTAINTY_200_MILI_SECONDS,
    V2X_TIME_UNCERTAINTY_100_MILI_SECONDS,
    V2X_TIME_UNCERTAINTY_50_MILI_SECONDS,
    V2X_TIME_UNCERTAINTY_20_MILI_SECONDS,
    V2X_TIME_UNCERTAINTY_10_MILI_SECONDS,
    V2X_TIME_UNCERTAINTY_5_MILI_SECONDS,
    V2X_TIME_UNCERTAINTY_2_MILI_SECONDS,
    V2X_TIME_UNCERTAINTY_1_MILI_SECONDS,
    V2X_TIME_UNCERTAINTY_500_MICRO_SECONDS,
    V2X_TIME_UNCERTAINTY_200_MICRO_SECONDS,
    V2X_TIME_UNCERTAINTY_100_MICRO_SECONDS,
    V2X_TIME_UNCERTAINTY_50_MICRO_SECONDS,
    V2X_TIME_UNCERTAINTY_20_MICRO_SECONDS,
    V2X_TIME_UNCERTAINTY_10_MICRO_SECONDS,
    V2X_TIME_UNCERTAINTY_5_MICRO_SECONDS,
    V2X_TIME_UNCERTAINTY_2_MICRO_SECONDS,
    V2X_TIME_UNCERTAINTY_1_MICRO_SECONDS,
    V2X_TIME_UNCERTAINTY_500_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_200_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_100_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_50_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_20_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_10_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_5_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_2_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_1_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_0_5_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_0_2_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_0_1_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_0_05_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_0_02_NANO_SECONDS,
    V2X_TIME_UNCERTAINTY_0_01_NANO_SECONDS,
};

// SAE Positional Confidence Enum
#define V2X_POSITION_CONFIDENCE_SIZE (13)
#define V2X_POSITION_UNCERTAINTY_UNAVAILABLE (0.0)  /**< Not Equipped or unavailable */
#define V2X_POSITION_UNCERTAINTY_100_00_M    (100.0)  /**< Better than  100 m  */
#define V2X_POSITION_UNCERTAINTY_050_00_M    (50.0)  /**< Better than  50 m   */
#define V2X_POSITION_UNCERTAINTY_020_00_M    (20.0)  /**< Better than  20 m   */
#define V2X_POSITION_UNCERTAINTY_010_00_M    (10.0)  /**< Better than  10 m   */
#define V2X_POSITION_UNCERTAINTY_002_00_M    (2.0)  /**< Better than  2 m    */
#define V2X_POSITION_UNCERTAINTY_001_00_M    (1.0)  /**< Better than  1 m    */
#define V2X_POSITION_UNCERTAINTY_000_50_M    (0.5)  /**< Better than  0.5 m  */
#define V2X_POSITION_UNCERTAINTY_000_20_M    (0.2)  /**< Better than  0.2 m  */
#define V2X_POSITION_UNCERTAINTY_000_10_M    (0.1)  /**< Better than  0.1 m  */
#define V2X_POSITION_UNCERTAINTY_000_05_M    (0.05) /**< Better than  0.05 m */
#define V2X_POSITION_UNCERTAINTY_000_02_M    (0.02) /**< Better than  0.02 m */
#define V2X_POSITION_UNCERTAINTY_000_01_M    (0.01) /**< Better than  0.01 m */

static float position_confidence_to_uncertainty_map[V2X_POSITION_CONFIDENCE_SIZE] = {
    V2X_POSITION_UNCERTAINTY_UNAVAILABLE,
    V2X_POSITION_UNCERTAINTY_100_00_M,
    V2X_POSITION_UNCERTAINTY_050_00_M,
    V2X_POSITION_UNCERTAINTY_020_00_M,
    V2X_POSITION_UNCERTAINTY_010_00_M,
    V2X_POSITION_UNCERTAINTY_002_00_M,
    V2X_POSITION_UNCERTAINTY_001_00_M,
    V2X_POSITION_UNCERTAINTY_000_50_M,
    V2X_POSITION_UNCERTAINTY_000_20_M,
    V2X_POSITION_UNCERTAINTY_000_10_M,
    V2X_POSITION_UNCERTAINTY_000_05_M,
    V2X_POSITION_UNCERTAINTY_000_02_M,
    V2X_POSITION_UNCERTAINTY_000_01_M,
};

float convert_time_confidence_to_uncertainty(uint8_t time_confidence);

uint8_t convert_time_uncertainty_to_confidence(float time_uncertainty);

uint16_t calculate_position_confidence(double semi_major_axis_uncertainty,
                                       double semi_minor_axis_uncertainty,
                                       float elevation_uncertainty);

bool parse_trusted_ue_info(tunnel_mode_data_t *result,
                           tunnel_mode_options_t *options,
                           char *param);

void parse_tunnel_mode_update_params(tunnel_mode_options_t *options, char *param);

/*
 * Calculate the propogation delay in Ts
 * @param distance (in m)
 */
uint32_t calculate_propagation_delay_Ts(double distance);

void rv_map_insert(rv_map_t *rv_map, rv_map_entry_t insert);

uint16_t rv_map_get_trusted(rv_map_t *rv_map, trusted_ue_info_t *trusted, uint16_t trusted_len);

uint16_t rv_map_get_malicious(rv_map_t *rv_map, uint32_t *malicious, uint16_t malicious_len);

int update_tunnel_mode_info(rv_map_t *rv_map);

void *tunnel_mode_thread_fn(void *period_nsec_ptr);

#endif /* TUNNEL_MODE_H */
