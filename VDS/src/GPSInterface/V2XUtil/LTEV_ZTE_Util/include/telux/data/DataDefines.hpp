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
 * @file       DataDefines.hpp
 * @brief      DataDefines provides the enumerations required for Connection Manager
 *
 */

#ifndef DATADEFINES_HPP
#define DATADEFINES_HPP

#include <string>
#include <vector>

namespace telux {
namespace data {

/** @addtogroup telematics_data
 * @{ */

/**
 * Preferred IP family for the call
 */
enum class IpFamilyType {
   UNKNOWN = -1,
   IPV4 = 0x04,    // IPv4 call
   IPV6 = 0x06,    // IPv6 call
   IPV4V6 = 0x0A,  // IPv4 and IPv6 call
};

/**
 * Technology Preference
 */
enum class TechPreference {
   UNKNOWN = -1,
   TP_3GPP,  /**< UMTS, LTE */
   TP_3GPP2, /**< CDMA */
   TP_ANY,   /**< ANY (3GPP or 3GPP2)  */
};

/**
 * Authentication protocol preference type to be used for PDP context.
 */
enum class AuthProtocolType {
   AUTH_NONE = 0,
   AUTH_PAP = 1,  /**< Password Authentication Protocol */
   AUTH_CHAP = 2, /**< Challenge Handshake Authentication Protocol */
   AUTH_PAP_CHAP = 3,
};

/**
 * Profile Parameters used for profile creation, query and modify
 */
struct ProfileParams {
   std::string profileName;                                 /**< Profile Name */
   std::string apn;                                         /**< APN name */
   std::string userName;                                    /**< APN user name (if any) */
   std::string password;                                    /**< APN password (if any) */
   TechPreference techPref = TechPreference::UNKNOWN;       /**< Technology preference,
                                           default is TechPreference::UNKNOWN */
   AuthProtocolType authType = AuthProtocolType::AUTH_NONE; /**< Authentication protocol type,
                                     default is AuthProtocolType::AUTH_NONE */
   IpFamilyType ipFamilyType = IpFamilyType::UNKNOWN;       /**< Preferred IP family for the call,
                                                                 default is
                                                                 IpFamilyType::UNKNOWN */
};

/**
 * Data transfer statistics structure.
 */
struct DataCallStats {
   unsigned long packetsTx = 0;        /**< Number of packets transmitted */
   unsigned long packetsRx = 0;        /**< Number of packets received */
   long long bytesTx = 0;              /**< Number of bytes transmitted */
   long long bytesRx = 0;              /**< Number of bytes received */
   unsigned long packetsDroppedTx = 0; /**< Number of transmit packets dropped */
   unsigned long packetsDroppedRx = 0; /**< Number of receive packets dropped */
};

/**
 * Data call event status
 */
enum class DataCallStatus {
   INVALID = 0x00,    /**<  Invalid  */
   NET_CONNECTED,     /**< Call is connected */
   NET_NO_NET,        /**< Call is disconnected */
   NET_IDLE,          /**< Call is in idle state */
   NET_CONNECTING,    /**< Call is in connecting state */
   NET_DISCONNECTING, /**< Call is in disconnecting state */
   NET_RECONFIGURED,  /**< Interface is reconfigured, IP Address got changed */
   NET_NEWADDR,       /**< A new IP address was added on an existing call */
   NET_DELADDR,       /**< An IP address was removed from the existing interface */
};

/**
 * IP address information structure
 */
struct IpAddrInfo {
   std::string ifAddress;           /**< Interface IP address. */
   unsigned int ifMask = 0;         /**< Subnet mask.          */
   std::string gwAddress;           /**< Gateway IP address.   */
   unsigned int gwMask = 0;         /**< Subnet mask.          */
   std::string primaryDnsAddress;   /**< Primary DNS address.  */
   std::string secondaryDnsAddress; /**< Secondary DNS address.*/
};

/**
 * Bearer technology types (returned with getCurrentBearerTech).
 */
enum class DataBearerTechnology {
   UNKNOWN, /**< Unknown bearer. */
   // CDMA related data bearer technologies
   CDMA_1X,                /**< 1X technology. */
   EVDO_REV0,              /**< CDMA Rev 0. */
   EVDO_REVA,              /**< CDMA Rev A. */
   EVDO_REVB,              /**< CDMA Rev B. */
   EHRPD,                  /**< EHRPD. */
   FMC,                    /**< Fixed mobile convergence. */
   HRPD,                   /**< HRPD */
   BEARER_TECH_3GPP2_WLAN, /**< IWLAN */

   // UMTS related data bearer technologies
   WCDMA,                 /**< WCDMA. */
   GPRS,                  /**< GPRS. */
   HSDPA,                 /**< HSDPA. */
   HSUPA,                 /**< HSUPA. */
   EDGE,                  /**< EDGE. */
   LTE,                   /**< LTE. */
   HSDPA_PLUS,            /**< HSDPA+. */
   DC_HSDPA_PLUS,         /**< DC HSDPA+. */
   HSPA,                  /**< HSPA */
   BEARER_TECH_64_QAM,    /**< 64 QAM. */
   TDSCDMA,               /**< TD-SCDMA. */
   GSM,                   /**< GSM */
   BEARER_TECH_3GPP_WLAN, /**< IWLAN */
};

/**
 * Data call end/termination due to reason type.
 */
enum class EndReasonType {
   CE_UNKNOWN = 0xFF,
   CE_MOBILE_IP = 0x01,
   CE_INTERNAL = 0x02,
   CE_CALL_MANAGER_DEFINED = 0x03,
   CE_3GPP_SPEC_DEFINED = 0x06,
   CE_PPP = 0x07,
   CE_EHRPD = 0x08,
   CE_IPV6 = 0x09,
   CE_HANDOFF = 0x0C,
};

/**
 * Data call end/termination reason code for EndReasonType::CE_MOBILE_IP
 */
enum class MobileIpReasonCode {
   /*Mobile IP Call End reasons*/
   CE_MIP_FA_ERR_REASON_UNSPECIFIED = 64,
   CE_MIP_FA_ERR_ADMINISTRATIVELY_PROHIBITED = 65,
   CE_MIP_FA_ERR_INSUFFICIENT_RESOURCES = 66,
   CE_MIP_FA_ERR_MOBILE_NODE_AUTHENTICATION_FAILURE = 67,
   CE_MIP_FA_ERR_HA_AUTHENTICATION_FAILURE = 68,
   CE_MIP_FA_ERR_REQUESTED_LIFETIME_TOO_LONG = 69,
   CE_MIP_FA_ERR_MALFORMED_REQUEST = 70,
   CE_MIP_FA_ERR_MALFORMED_REPLY = 71,
   CE_MIP_FA_ERR_ENCAPSULATION_UNAVAILABLE = 72,
   CE_MIP_FA_ERR_VJHC_UNAVAILABLE = 73,
   CE_MIP_FA_ERR_REVERSE_TUNNEL_UNAVAILABLE = 74,
   CE_MIP_FA_ERR_REVERSE_TUNNEL_IS_MANDATORY_AND_T_BIT_NOT_SET = 75,
   CE_MIP_FA_ERR_DELIVERY_STYLE_NOT_SUPPORTED = 79,
   CE_MIP_FA_ERR_MISSING_NAI = 97,
   CE_MIP_FA_ERR_MISSING_HA = 98,
   CE_MIP_FA_ERR_MISSING_HOME_ADDR = 99,
   CE_MIP_FA_ERR_UNKNOWN_CHALLENGE = 104,
   CE_MIP_FA_ERR_MISSING_CHALLENGE = 105,
   CE_MIP_FA_ERR_STALE_CHALLENGE = 106,
   CE_MIP_HA_ERR_REASON_UNSPECIFIED = 128,
   CE_MIP_HA_ERR_ADMINISTRATIVELY_PROHIBITED = 129,
   CE_MIP_HA_ERR_INSUFFICIENT_RESOURCES = 130,
   CE_MIP_HA_ERR_MOBILE_NODE_AUTHENTICATION_FAILURE = 131,
   CE_MIP_HA_ERR_FA_AUTHENTICATION_FAILURE = 132,
   CE_MIP_HA_ERR_REGISTRATION_ID_MISMATCH = 133,
   CE_MIP_HA_ERR_MALFORMED_REQUEST = 134,
   CE_MIP_HA_ERR_UNKNOWN_HA_ADDR = 136,
   CE_MIP_HA_ERR_REVERSE_TUNNEL_UNAVAILABLE = 137,
   CE_MIP_HA_ERR_REVERSE_TUNNEL_IS_MANDATORY_AND_T_BIT_NOT_SET = 138,
   CE_MIP_HA_ERR_ENCAPSULATION_UNAVAILABLE = 139,
   CE_MIP_ERR_REASON_UNKNOWN = -1,
};

/**
 * Data call end/termination reason code for EndReasonType::CE_INTERNAL
 */
enum class InternalReasonCode {
   /*Internal Error Call End reasons*/
   CE_INTERNAL_ERROR = 201,
   CE_CALL_ENDED = 202,
   CE_INTERNAL_UNKNOWN_CAUSE_CODE = 203,
   CE_UNKNOWN_CAUSE_CODE = 204,
   CE_CLOSE_IN_PROGRESS = 205,
   CE_NW_INITIATED_TERMINATION = 206,
   CE_APP_PREEMPTED = 207,
   CE_ERR_PDN_IPV4_CALL_DISALLOWED = 208,
   CE_ERR_PDN_IPV4_CALL_THROTTLED = 209,
   CE_ERR_PDN_IPV6_CALL_DISALLOWED = 210,
   CE_ERR_PDN_IPV6_CALL_THROTTLED = 211,
   CE_MODEM_RESTART = 212,
   CE_PDP_PPP_NOT_SUPPORTED = 213,
   CE_UNPREFERRED_RAT = 214,
   CE_PHYS_LINK_CLOSE_IN_PROGRESS = 215,
   CE_APN_PENDING_HANDOVER = 216,
   CE_PROFILE_BEARER_INCOMPATIBLE = 217,
   CE_MMGSDI_CARD_EVT = 218,
   CE_LPM_OR_PWR_DOWN = 219,
   CE_APN_DISABLED = 220,
   CE_MPIT_EXPIRED = 221,
   CE_IPV6_ADDR_TRANSFER_FAILED = 222,
   CE_TRAT_SWAP_FAILED = 223,
   CE_EHRPD_TO_HRPD_FALLBACK = 224,
   CE_MANDATORY_APN_DISABLED = 225,
   CE_MIP_CONFIG_FAILURE = 226,
   CE_INTERNAL_PDN_INACTIVITY_TIMER_EXPIRED = 227,
   CE_MAX_V4_CONNECTIONS = 228,
   CE_MAX_V6_CONNECTIONS = 229,
   CE_APN_MISMATCH = 230,
   CE_IP_VERSION_MISMATCH = 231,
   CE_DUN_CALL_DISALLOWED = 232,
   CE_INVALID_PROFILE = 233,
   CE_INTERNAL_EPC_NONEPC_TRANSITION = 234,
   CE_INVALID_PROFILE_ID = 235,
   CE_INTERNAL_CALL_ALREADY_PRESENT = 236,
   CE_IFACE_IN_USE = 237,
   CE_IP_PDP_MISMATCH = 238,
   CE_APN_DISALLOWED_ON_ROAMING = 239,
   CE_APN_PARAM_CHANGE = 240,
   CE_IFACE_IN_USE_CFG_MATCH = 241,
   CE_NULL_APN_DISALLOWED = 242,
   CE_THERMAL_MITIGATION = 243,
   CE_SUBS_ID_MISMATCH = 244,
   CE_DATA_SETTINGS_DISABLED = 245,
   CE_DATA_ROAMING_SETTINGS_DISABLED = 246,
   CE_APN_FORMAT_INVALID = 247,
   CE_DDS_CALL_ABORT = 248,
   CE_VALIDATION_FAILURE = 249,
   CE_PROFILES_NOT_COMPATIBLE = 251,
   CE_NULL_RESOLVED_APN_NO_MATCH = 252,
   CE_INVALID_APN_NAME = 253,
};

/**
 * Data call end/termination reason code for EndReasonType::CE_CALL_MANAGER_DEFINED
 */
enum class CallManagerReasonCode {
   /*CM defined Call End reasons*/
   CE_CDMA_LOCK = 500,
   CE_INTERCEPT = 501,
   CE_REORDER = 502,
   CE_REL_SO_REJ = 503,
   CE_INCOM_CALL = 504,
   CE_ALERT_STOP = 505,
   CE_ACTIVATION = 506,
   CE_MAX_ACCESS_PROBE = 507,
   CE_CCS_NOT_SUPPORTED_BY_BS = 508,
   CE_NO_RESPONSE_FROM_BS = 509,
   CE_REJECTED_BY_BS = 510,
   CE_INCOMPATIBLE = 511,
   CE_ALREADY_IN_TC = 512,
   CE_USER_CALL_ORIG_DURING_GPS = 513,
   CE_USER_CALL_ORIG_DURING_SMS = 514,
   CE_NO_CDMA_SRV = 515,
   CE_MC_ABORT = 516,
   CE_PSIST_NG = 517,
   CE_UIM_NOT_PRESENT = 518,
   CE_RETRY_ORDER = 519,
   CE_ACCESS_BLOCK = 520,
   CEACCESS_BLOCK_ALL = 521,
   CE_IS707B_MAX_ACC = 522,
   CE_THERMAL_EMERGENCY = 523,
   CE_CALL_ORIG_THROTTLED = 524,
   CE_USER_CALL_ORIG_DURING_VOICE_CALL = 535,
   CE_CONF_FAILED = 1000,
   CE_INCOM_REJ = 1001,
   CE_NEW_NO_GW_SRV = 1002,
   CE_NEW_NO_GPRS_CONTEXT = 1003,
   CE_NEW_ILLEGAL_MS = 1004,
   CE_NEW_ILLEGAL_ME = 1005,
   CE_NEW_GPRS_SERVICES_AND_NON_GPRS_SERVICES_NOT_ALLOWED = 1006,
   CE_NEW_GPRS_SERVICES_NOT_ALLOWED = 1007,
   CE_NEW_MS_IDENTITY_CANNOT_BE_DERIVED_BY_THE_NETWORK = 1008,
   CE_NEW_IMPLICITLY_DETACHED = 1009,
   CE_NEW_PLMN_NOT_ALLOWED = 1010,
   CE_NEW_LA_NOT_ALLOWED = 1011,
   CE_NEW_GPRS_SERVICES_NOT_ALLOWED_IN_THIS_PLMN = 1012,
   CE_NEW_PDP_DUPLICATE = 1013,
   CE_NEW_UE_RAT_CHANGE = 1014,
   CE_NEW_CONGESTION = 1015,
   CE_NEW_NO_PDP_CONTEXT_ACTIVATED = 1016,
   CE_NEW_ACCESS_CLASS_DSAC_REJECTION = 1017,
   CE_PDP_ACTIVATE_MAX_RETRY_FAILED = 1018,
   CE_RAB_FAILURE = 1019,
   CE_ESM_UNKNOWN_EPS_BEARER_CONTEXT = 1025,
   CE_DRB_RELEASED_AT_RRC = 1026,
   CE_NAS_SIG_CONN_RELEASED = 1027,
   CE_REASON_EMM_DETACHED = 1028,
   CE_EMM_ATTACH_FAILED = 1029,
   CE_EMM_ATTACH_STARTED = 1030,
   CE_LTE_NAS_SERVICE_REQ_FAILED = 1031,
   CE_ESM_ACTIVE_DEDICATED_BEARER_REACTIVATED_BY_NW = 1032,
   CE_ESM_LOWER_LAYER_FAILURE = 1033,
   CE_ESM_SYNC_UP_WITH_NW = 1034,
   CE_ESM_NW_ACTIVATED_DED_BEARER_WITH_ID_OF_DEF_BEARER = 1035,
   CE_ESM_BAD_OTA_MESSAGE = 1036,
   CE_ESM_DS_REJECTED_THE_CALL = 1037,
   CE_ESM_CONTEXT_TRANSFERED_DUE_TO_IRAT = 1038,
   CE_DS_EXPLICIT_DEACT = 1039,
   CE_ESM_LOCAL_CAUSE_NONE = 1040,
   CE_LTE_NAS_SERVICE_REQ_FAILED_NO_THROTTLE = 1041,
   CE_ACL_FAILURE = 1042,
   CE_LTE_NAS_SERVICE_REQ_FAILED_DS_DISALLOW = 1043,
   CE_EMM_T3417_EXPIRED = 1044,
   CE_EMM_T3417_EXT_EXPIRED = 1045,
   CE_LRRC_UL_DATA_CNF_FAILURE_TXN = 1046,
   CE_LRRC_UL_DATA_CNF_FAILURE_HO = 1047,
   CE_LRRC_UL_DATA_CNF_FAILURE_CONN_REL = 1048,
   CE_LRRC_UL_DATA_CNF_FAILURE_RLF = 1049,
   CE_LRRC_UL_DATA_CNF_FAILURE_CTRL_NOT_CONN = 1050,
   CE_LRRC_CONN_EST_FAILURE = 1051,
   CE_LRRC_CONN_EST_FAILURE_ABORTED = 1052,
   CE_LRRC_CONN_EST_FAILURE_ACCESS_BARRED = 1053,
   CE_LRRC_CONN_EST_FAILURE_CELL_RESEL = 1054,
   CE_LRRC_CONN_EST_FAILURE_CONFIG_FAILURE = 1055,
   CE_LRRC_CONN_EST_FAILURE_TIMER_EXPIRED = 1056,
   CE_LRRC_CONN_EST_FAILURE_LINK_FAILURE = 1057,
   CE_LRRC_CONN_EST_FAILURE_NOT_CAMPED = 1058,
   CE_LRRC_CONN_EST_FAILURE_SI_FAILURE = 1059,
   CE_LRRC_CONN_EST_FAILURE_CONN_REJECT = 1060,
   CE_LRRC_CONN_REL_NORMAL = 1061,
   CE_LRRC_CONN_REL_RLF = 1062,
   CE_LRRC_CONN_REL_CRE_FAILURE = 1063,
   CE_LRRC_CONN_REL_OOS_DURING_CRE = 1064,
   CE_LRRC_CONN_REL_ABORTED = 1065,
   CE_LRRC_CONN_REL_SIB_READ_ERROR = 1066,
   CE_DETACH_WITH_REATTACH_LTE_NW_DETACH = 1067,
   CE_DETACH_WITH_OUT_REATTACH_LTE_NW_DETACH = 1068,
   CE_ESM_PROC_TIME_OUT = 1069,
   CE_INVALID_CONNECTION_ID = 1070,
   CE_INVALID_NSAPI = 1071,
   CE_INVALID_PRI_NSAPI = 1072,
   CE_INVALID_FIELD = 1073,
   CE_RAB_SETUP_FAILURE = 1074,
   CE_PDP_ESTABLISH_MAX_TIMEOUT = 1075,
   CE_PDP_MODIFY_MAX_TIMEOUT = 1076,
   CE_PDP_INACTIVE_MAX_TIMEOUT = 1077,
   CE_PDP_LOWERLAYER_ERROR = 1078,
   CE_PPD_UNKNOWN_REASON = 1079,
   CE_PDP_MODIFY_COLLISION = 1080,
   CE_PDP_MBMS_REQUEST_COLLISION = 1081,
   CE_MBMS_DUPLICATE = 1082,
   CE_SM_PS_DETACHED = 1083,
   CE_SM_NO_RADIO_AVAILABLE = 1084,
   CE_SM_ABORT_SERVICE_NOT_AVAILABLE = 1085,
   CE_MESSAGE_EXCEED_MAX_L2_LIMIT = 1086,
   CE_SM_NAS_SRV_REQ_FAILURE = 1087,
   CE_RRC_CONN_EST_FAILURE_REQ_ERROR = 1088,
   CE_RRC_CONN_EST_FAILURE_TAI_CHANGE = 1089,
   CE_RRC_CONN_EST_FAILURE_RF_UNAVAILABLE = 1090,
   CE_RRC_CONN_REL_ABORTED_IRAT_SUCCESS = 1091,
   CE_RRC_CONN_REL_RLF_SEC_NOT_ACTIVE = 1092,
   CE_RRC_CONN_REL_IRAT_TO_LTE_ABORTED = 1093,
   CE_RRC_CONN_REL_IRAT_FROM_LTE_TO_G_CCO_SUCCESS = 1094,
   CE_RRC_CONN_REL_IRAT_FROM_LTE_TO_G_CCO_ABORTED = 1095,
   CE_IMSI_UNKNOWN_IN_HSS = 1096,
   CE_IMEI_NOT_ACCEPTED = 1097,
   CE_EPS_SERVICES_AND_NON_EPS_SERVICES_NOT_ALLOWED = 1098,
   CE_EPS_SERVICES_NOT_ALLOWED_IN_PLMN = 1099,
   CE_MSC_TEMPORARILY_NOT_REACHABLE = 1100,
   CE_CS_DOMAIN_NOT_AVAILABLE = 1101,
   CE_ESM_FAILURE = 1102,
   CE_MAC_FAILURE = 1103,
   CE_SYNCH_FAILURE = 1104,
   CE_UE_SECURITY_CAPABILITIES_MISMATCH = 1105,
   CE_SECURITY_MODE_REJ_UNSPECIFIED = 1106,
   CE_NON_EPS_AUTH_UNACCEPTABLE = 1107,
   CE_CS_FALLBACK_CALL_EST_NOT_ALLOWED = 1108,
   CE_NO_EPS_BEARER_CONTEXT_ACTIVATED = 1109,
   CE_EMM_INVALID_STATE = 1110,
   CE_NAS_LAYER_FAILURE = 1111,
   CE_MULTI_PDN_NOT_ALLOWED = 1112,
   CE_EMBMS_NOT_ENABLED = 1113,
   CE_PENDING_REDIAL_CALL_CLEANUP = 1114,
   CE_EMBMS_REGULAR_DEACTIVATION = 1115,
   CE_TLB_REGULAR_DEACTIVATION = 1116,
   CE_LOWER_LAYER_REGISTRATION_FAILURE = 1117,
   CE_DETACH_EPS_SERVICES_NOT_ALLOWED = 1118,
   CE_SM_INTERNAL_PDP_DEACTIVATION = 1119,
   CE_UNSUPPORTED_1X_PREV = 1515,
   CE_CD_GEN_OR_BUSY = 1500,
   CE_CD_BILL_OR_AUTH = 1501,
   CE_CHG_HDR = 1502,
   CE_EXIT_HDR = 1503,
   CE_HDR_NO_SESSION = 1504,
   CE_HDR_ORIG_DURING_GPS_FIX = 1505,
   CE_HDR_CS_TIMEOUT = 1506,
   CE_HDR_RELEASED_BY_CM = 1507,
   CE_COLLOC_ACQ_FAIL = 1508,
   CE_OTASP_COMMIT_IN_PROG = 1509,
   CE_NO_HYBR_HDR_SRV = 1510,
   CE_HDR_NO_LOCK_GRANTED = 1511,
   CE_HOLD_OTHER_IN_PROG = 1512,
   CE_HDR_FADE = 1513,
   CE_HDR_ACC_FAIL = 1514,
   CE_CLIENT_END = 2000,
   CE_NO_SRV = 2001,
   CE_FADE = 2002,
   CE_REL_NORMAL = 2003,
   CE_ACC_IN_PROG = 2004,
   CE_ACC_FAIL = 2005,
   CE_REDIR_OR_HANDOFF = 2006,
   CE_CM_UNKNOWN_ERROR = 2007,
   CE_OFFLINE = 2500,
   CE_EMERGENCY_MODE = 2501,
   CE_PHONE_IN_USE = 2502,
   CE_INVALID_MODE = 2503,
   CE_INVALID_SIM_STATE = 2504,
   CE_NO_COLLOC_HDR = 2505,
   CE_CALL_CONTROL_REJECTED = 2506,
   CE_UNKNOWN = -1,
};

/**
 * Data call end/termination reason code for EndReasonType::CE_3GPP_SPEC_DEFINED
 */
enum class SpecReasonCode {
   /*3GPP spec defined Call End reasons*/
   CE_OPERATOR_DETERMINED_BARRING = 8,
   CE_NAS_SIGNALLING_ERROR = 14,
   CE_LLC_SNDCP_FAILURE = 25,
   CE_INSUFFICIENT_RESOURCES = 26,
   CE_UNKNOWN_APN = 27,
   CE_UNKNOWN_PDP = 28,
   CE_AUTH_FAILED = 29,
   CE_GGSN_REJECT = 30,
   CE_ACTIVATION_REJECT = 31,
   CE_OPTION_NOT_SUPPORTED = 32,
   CE_OPTION_UNSUBSCRIBED = 33,
   CE_OPTION_TEMP_OOO = 34,
   CE_NSAPI_ALREADY_USED = 35,
   CE_REGULAR_DEACTIVATION = 36,
   CE_QOS_NOT_ACCEPTED = 37,
   CE_NETWORK_FAILURE = 38,
   CE_UMTS_REACTIVATION_REQ = 39,
   CE_FEATURE_NOT_SUPPORTED = 40,
   CE_TFT_SEMANTIC_ERROR = 41,
   CE_TFT_SYNTAX_ERROR = 42,
   CE_UNKNOWN_PDP_CONTEXT = 43,
   CE_FILTER_SEMANTIC_ERROR = 44,
   CE_FILTER_SYNTAX_ERROR = 45,
   CE_PDP_WITHOUT_ACTIVE_TFT = 46,
   CE_IP_V4_ONLY_ALLOWED = 50,
   CE_IP_V6_ONLY_ALLOWED = 51,
   CE_SINGLE_ADDR_BEARER_ONLY = 52,
   CE_ESM_INFO_NOT_RECEIVED = 53,
   CE_PDN_CONN_DOES_NOT_EXIST = 54,
   CE_MULTI_CONN_TO_SAME_PDN_NOT_ALLOWED = 55,
   CE_MAX_ACTIVE_PDP_CONTEXT_REACHED = 65,
   CE_UNSUPPORTED_APN_IN_CURRENT_PLMN = 66,
   CE_INVALID_TRANSACTION_ID = 81,
   CE_MESSAGE_INCORRECT_SEMANTIC = 95,
   CE_INVALID_MANDATORY_INFO = 96,
   CE_MESSAGE_TYPE_UNSUPPORTED = 97,
   CE_MSG_TYPE_NONCOMPATIBLE_STATE = 98,
   CE_UNKNOWN_INFO_ELEMENT = 99,
   CE_CONDITIONAL_IE_ERROR = 100,
   CE_MSG_AND_PROTOCOL_STATE_UNCOMPATIBLE = 101,
   CE_PROTOCOL_ERROR = 111,
   CE_APN_TYPE_CONFLICT = 112,
   CE_INVALID_PCSCF_ADDRESS = 113,
   CE_INTERNAL_CALL_PREEMPT_BY_HIGH_PRIO_APN = 114,
   CE_EMM_ACCESS_BARRED = 115,
   CE_EMERGENCY_IFACE_ONLY = 116,
   CE_IFACE_MISMATCH = 117,
   CE_COMPANION_IFACE_IN_USE = 118,
   CE_IP_ADDRESS_MISMATCH = 119,
   CE_IFACE_AND_POL_FAMILY_MISMATCH = 120,
   CE_EMM_ACCESS_BARRED_INFINITE_RETRY = 121,
   CE_AUTH_FAILURE_ON_EMERGENCY_CALL = 122,
   CE_INVALID_DNS_ADDR = 123,
   CE_INVALID_PCSCF_DNS_ADDR = 124,
   CE_TEST_LOOPBACK_MODE_A_OR_B_ENABLED = 125,
   CE_UNKNOWN = -1,
};

/**
 * Data call end/termination reason code for EndReasonType::CE_PPP
 */
enum class PPPReasonCode {
   /*Enumeration for the PPP verbose call end reason*/
   CE_PPP_TIMEOUT = 1,
   CE_PPP_AUTH_FAILURE = 2,
   CE_PPP_OPTION_MISMATCH = 3,
   CE_PPP_PAP_FAILURE = 31,
   CE_PPP_CHAP_FAILURE = 32,
   CE_PPP_CLOSE_IN_PROGRESS = 33,
   CE_PPP_NV_REFRESH_IN_PROGRESS = 34,
   CE_PPP_UNKNOWN = -1,
};

/**
 * Data call end/termination reason code for EndReasonType::CE_EHRPD
 */
enum class EHRPDReasonCode {
   /* Enumeration for the EHRPD verbose call end reason */
   CE_EHRPD_SUBS_LIMITED_TO_V4 = 1,
   CE_EHRPD_SUBS_LIMITED_TO_V6 = 2,
   CE_EHRPD_VSNCP_TIMEOUT = 4,
   CE_EHRPD_VSNCP_FAILURE = 5,
   CE_EHRPD_VSNCP_3GPP2I_GEN_ERROR = 6,
   CE_EHRPD_VSNCP_3GPP2I_UNAUTH_APN = 7,
   CE_EHRPD_VSNCP_3GPP2I_PDN_LIMIT_EXCEED = 8,
   CE_EHRPD_VSNCP_3GPP2I_NO_PDN_GW = 9,
   CE_EHRPD_VSNCP_3GPP2I_PDN_GW_UNREACH = 10,
   CE_EHRPD_VSNCP_3GPP2I_PDN_GW_REJ = 11,
   CE_EHRPD_VSNCP_3GPP2I_INSUFF_PARAM = 12,
   CE_EHRPD_VSNCP_3GPP2I_RESOURCE_UNAVAIL = 13,
   CE_EHRPD_VSNCP_3GPP2I_ADMIN_PROHIBIT = 14,
   CE_EHRPD_VSNCP_3GPP2I_PDN_ID_IN_USE = 15,
   CE_EHRPD_VSNCP_3GPP2I_SUBSCR_LIMITATION = 16,
   CE_EHRPD_VSNCP_3GPP2I_PDN_EXISTS_FOR_THIS_APN = 17,
   CE_EHRPD_VSNCP_3GPP2I_RECONNECT_NOT_ALLOWED = 19,
   CE_EHRPD_UNKNOWN = -1,
};

/**
 * Data call end/termination reason code for EndReasonType::CE_IPV6
 */
enum class Ipv6ReasonCode {
   /*IPV6 defined Call End reasons*/
   CE_PREFIX_UNAVAILABLE = 1,
   CE_IPV6_ERR_HRPD_IPV6_DISABLED = 2,
   CE_IPV6_DISABLED = 3,
};

/**
 * Data call end/termination reason code for EndReasonType::CE_HANDOFF
 */
enum class HandoffReasonCode {
   /*Hand off Call End reasons*/
   CE_VCER_HANDOFF_PREF_SYS_BACK_TO_SRAT = 1,
};

/**
 * Structure represents data call failure reason type and code.
 */
struct DataCallEndReason {
   EndReasonType type = EndReasonType::CE_UNKNOWN;
   /**< Data call terminated due to reason type, default is CE_UNKNOWN */
   union {
      MobileIpReasonCode IpCode;
      InternalReasonCode internalCode;
      CallManagerReasonCode cmCode;
      SpecReasonCode specCode;
      PPPReasonCode pppCode;
      EHRPDReasonCode ehrpdCode;
      Ipv6ReasonCode ipv6Code;
      HandoffReasonCode handOffCode;
   };
};

/**
 * Event due to which change in profile happened.
 */
enum class ProfileChangeEvent {
   CREATE_PROFILE_EVENT = 1, /**< Profile was created */
   DELETE_PROFILE_EVENT,     /**< Profile was deleted */
   MODIFY_PROFILE_EVENT,     /**< Profile was modified */
};

/** @} */ /* end_addtogroup telematics_data */
}
}

#endif  // DATADEFINES_HPP
