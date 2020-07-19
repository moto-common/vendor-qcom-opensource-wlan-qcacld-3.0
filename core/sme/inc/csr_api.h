/*
 * Copyright (c) 2011-2020 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/**
 *   \file csr_api.h
 *
 *   Exports and types for the Common Scan and Roaming Module interfaces.
 */

#ifndef CSRAPI_H__
#define CSRAPI_H__

#include "sir_api.h"
#include "sir_mac_prot_def.h"
#include "csr_link_list.h"
#include "wlan_scan_public_structs.h"

#define CSR_INVALID_SCANRESULT_HANDLE       (NULL)
#define CSR_NUM_WLM_LATENCY_LEVEL   4

#define CFG_PMKID_MODES_OKC                        (0x1)
#define CFG_PMKID_MODES_PMKSA_CACHING              (0x2)

typedef enum {
	/* never used */
	eCSR_AUTH_TYPE_NONE,
	/* MAC layer authentication types */
	eCSR_AUTH_TYPE_OPEN_SYSTEM,
	eCSR_AUTH_TYPE_SHARED_KEY,
	eCSR_AUTH_TYPE_SAE,
	eCSR_AUTH_TYPE_AUTOSWITCH,

	/* Upper layer authentication types */
	eCSR_AUTH_TYPE_WPA,
	eCSR_AUTH_TYPE_WPA_PSK,
	eCSR_AUTH_TYPE_WPA_NONE,

	eCSR_AUTH_TYPE_RSN,
	eCSR_AUTH_TYPE_RSN_PSK,
	eCSR_AUTH_TYPE_FT_RSN,
	eCSR_AUTH_TYPE_FT_RSN_PSK,
#ifdef FEATURE_WLAN_WAPI
	eCSR_AUTH_TYPE_WAPI_WAI_CERTIFICATE,
	eCSR_AUTH_TYPE_WAPI_WAI_PSK,
#endif /* FEATURE_WLAN_WAPI */
	eCSR_AUTH_TYPE_CCKM_WPA,
	eCSR_AUTH_TYPE_CCKM_RSN,
	eCSR_AUTH_TYPE_RSN_PSK_SHA256,
	eCSR_AUTH_TYPE_RSN_8021X_SHA256,
	eCSR_AUTH_TYPE_FILS_SHA256,
	eCSR_AUTH_TYPE_FILS_SHA384,
	eCSR_AUTH_TYPE_FT_FILS_SHA256,
	eCSR_AUTH_TYPE_FT_FILS_SHA384,
	eCSR_AUTH_TYPE_DPP_RSN,
	eCSR_AUTH_TYPE_OWE,
	eCSR_AUTH_TYPE_SUITEB_EAP_SHA256,
	eCSR_AUTH_TYPE_SUITEB_EAP_SHA384,
	eCSR_AUTH_TYPE_FT_SAE,
	eCSR_AUTH_TYPE_FT_SUITEB_EAP_SHA384,
	eCSR_NUM_OF_SUPPORT_AUTH_TYPE,
	eCSR_AUTH_TYPE_FAILED = 0xff,
	eCSR_AUTH_TYPE_UNKNOWN = eCSR_AUTH_TYPE_FAILED,

} eCsrAuthType;

typedef enum {
	eCSR_ENCRYPT_TYPE_NONE,
	eCSR_ENCRYPT_TYPE_WEP40_STATICKEY,
	eCSR_ENCRYPT_TYPE_WEP104_STATICKEY,
	eCSR_ENCRYPT_TYPE_WEP40,
	eCSR_ENCRYPT_TYPE_WEP104,
	eCSR_ENCRYPT_TYPE_TKIP,
	eCSR_ENCRYPT_TYPE_AES,/* CCMP */
#ifdef FEATURE_WLAN_WAPI
	/* WAPI */
	eCSR_ENCRYPT_TYPE_WPI,
#endif  /* FEATURE_WLAN_WAPI */
	eCSR_ENCRYPT_TYPE_KRK,
	eCSR_ENCRYPT_TYPE_BTK,
	eCSR_ENCRYPT_TYPE_AES_CMAC,
	eCSR_ENCRYPT_TYPE_AES_GMAC_128,
	eCSR_ENCRYPT_TYPE_AES_GMAC_256,
	eCSR_ENCRYPT_TYPE_AES_GCMP,
	eCSR_ENCRYPT_TYPE_AES_GCMP_256,
	eCSR_ENCRYPT_TYPE_ANY,
	eCSR_NUM_OF_ENCRYPT_TYPE = eCSR_ENCRYPT_TYPE_ANY,

	eCSR_ENCRYPT_TYPE_FAILED = 0xff,
	eCSR_ENCRYPT_TYPE_UNKNOWN = eCSR_ENCRYPT_TYPE_FAILED,

} eCsrEncryptionType;

/*---------------------------------------------------------------------------
   Enumeration of the various Security types
   ---------------------------------------------------------------------------*/
typedef enum {
	eCSR_SECURITY_TYPE_WPA,
	eCSR_SECURITY_TYPE_RSN,
#ifdef FEATURE_WLAN_WAPI
	eCSR_SECURITY_TYPE_WAPI,
#endif /* FEATURE_WLAN_WAPI */
	eCSR_SECURITY_TYPE_UNKNOWN,

} eCsrSecurityType;

typedef enum {
	/* 11a/b/g only, no HT, no proprietary */
	eCSR_DOT11_MODE_abg = 0x0001,
	eCSR_DOT11_MODE_11a = 0x0002,
	eCSR_DOT11_MODE_11b = 0x0004,
	eCSR_DOT11_MODE_11g = 0x0008,
	eCSR_DOT11_MODE_11n = 0x0010,
	eCSR_DOT11_MODE_11g_ONLY = 0x0020,
	eCSR_DOT11_MODE_11n_ONLY = 0x0040,
	eCSR_DOT11_MODE_11b_ONLY = 0x0080,
	eCSR_DOT11_MODE_11ac = 0x0100,
	eCSR_DOT11_MODE_11ac_ONLY = 0x0200,
	/*
	 * This is for WIFI test. It is same as eWNIAPI_MAC_PROTOCOL_ALL
	 * except when it starts IBSS in 11B of 2.4GHz
	 * It is for CSR internal use
	 */
	eCSR_DOT11_MODE_AUTO = 0x0400,
	eCSR_DOT11_MODE_11ax = 0x0800,
	eCSR_DOT11_MODE_11ax_ONLY = 0x1000,

	/* specify the number of maximum bits for phyMode */
	eCSR_NUM_PHY_MODE = 16,
} eCsrPhyMode;

/**
 * enum eCsrRoamBssType - BSS type in CSR operations
 * @eCSR_BSS_TYPE_INFRASTRUCTURE: Infrastructure station
 * @eCSR_BSS_TYPE_INFRA_AP: SoftAP
 * @eCSR_BSS_TYPE_IBSS: IBSS network we'll not start
 * @eCSR_BSS_TYPE_START_IBSS: IBSS network we'll start if no partners found
 * @eCSR_BSS_TYPE_NDI: NAN datapath interface
 * @eCSR_BSS_TYPE_ANY: any BSS type (IBSS or Infrastructure)
 */
typedef enum {
	eCSR_BSS_TYPE_INFRASTRUCTURE,
	eCSR_BSS_TYPE_INFRA_AP,
	eCSR_BSS_TYPE_IBSS,
	eCSR_BSS_TYPE_START_IBSS,
	eCSR_BSS_TYPE_NDI,
	eCSR_BSS_TYPE_ANY,
} eCsrRoamBssType;

typedef enum {
	eCSR_SCAN_SUCCESS,
	eCSR_SCAN_FAILURE,
	eCSR_SCAN_ABORT,
	eCSR_SCAN_FOUND_PEER,
} eCsrScanStatus;

typedef enum {
	eCSR_BW_20MHz_VAL = 20,
	eCSR_BW_40MHz_VAL = 40,
	eCSR_BW_80MHz_VAL = 80,
	eCSR_BW_160MHz_VAL = 160
} eCSR_BW_Val;

typedef enum {
	eCSR_INI_SINGLE_CHANNEL_CENTERED = 0,
	eCSR_INI_DOUBLE_CHANNEL_HIGH_PRIMARY,
	eCSR_INI_DOUBLE_CHANNEL_LOW_PRIMARY,
	eCSR_INI_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_CENTERED,
	eCSR_INI_QUADRUPLE_CHANNEL_20MHZ_CENTERED_40MHZ_CENTERED,
	eCSR_INI_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_CENTERED,
	eCSR_INI_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_LOW,
	eCSR_INI_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_LOW,
	eCSR_INI_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_HIGH,
	eCSR_INI_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_HIGH,
	eCSR_INI_CHANNEL_BONDING_STATE_MAX
} eIniChanBondState;

#define CSR_RSN_PMKID_SIZE          16
#define CSR_RSN_MAX_PMK_LEN         48
#define CSR_MAX_PMKID_ALLOWED       32
#define CSR_WEP40_KEY_LEN           5
#define CSR_WEP104_KEY_LEN          13
#define CSR_TKIP_KEY_LEN            32
#define CSR_AES_KEY_LEN             16
#define CSR_AES_GCMP_KEY_LEN        16
#define CSR_AES_GCMP_256_KEY_LEN    32
#define CSR_AES_GMAC_128_KEY_LEN    16
#define CSR_AES_GMAC_256_KEY_LEN    32
#define CSR_MAX_TX_POWER        (WNI_CFG_CURRENT_TX_POWER_LEVEL_STAMAX)
#define CSR_MAX_RSC_LEN             16
#ifdef FEATURE_WLAN_WAPI
#define CSR_WAPI_BKID_SIZE          16
#define CSR_MAX_BKID_ALLOWED        16
#define CSR_WAPI_KEY_LEN            32
#define CSR_MAX_KEY_LEN         (CSR_WAPI_KEY_LEN) /* longest one is for WAPI */
#else
#define CSR_MAX_KEY_LEN         (CSR_TKIP_KEY_LEN) /* longest one is for TKIP */
#endif /* FEATURE_WLAN_WAPI */
#ifdef FEATURE_WLAN_ESE
#define CSR_KRK_KEY_LEN             16
#endif

typedef struct tagCsrChannelInfo {
	uint8_t numOfChannels;
	uint8_t *ChannelList;   /* it will be an array of channels */
} tCsrChannelInfo, *tpCsrChannelInfo;

typedef enum {
	eHIDDEN_SSID_NOT_IN_USE,
	eHIDDEN_SSID_ZERO_LEN,
	eHIDDEN_SSID_ZERO_CONTENTS
} tHiddenssId;

typedef struct tagCsrSSIDInfo {
	tSirMacSSid SSID;
	bool handoffPermitted;
	tHiddenssId ssidHidden;
} tCsrSSIDInfo;

typedef struct tagCsrSSIDs {
	uint32_t numOfSSIDs;
	tCsrSSIDInfo *SSIDList; /* To be allocated for array of SSIDs */
} tCsrSSIDs;

typedef struct tagCsrBSSIDs {
	uint32_t numOfBSSIDs;
	struct qdf_mac_addr *bssid;
} tCsrBSSIDs;

typedef struct tagCsrStaParams {
	uint16_t capability;
	uint8_t extn_capability[SIR_MAC_MAX_EXTN_CAP];
	uint8_t supported_rates_len;
	uint8_t supported_rates[SIR_MAC_MAX_SUPP_RATES];
	uint8_t htcap_present;
	tSirHTCap HTCap;
	uint8_t vhtcap_present;
	tSirVHTCap VHTCap;
	uint8_t uapsd_queues;
	uint8_t max_sp;
	uint8_t supported_channels_len;
	uint8_t supported_channels[SIR_MAC_MAX_SUPP_CHANNELS];
	uint8_t supported_oper_classes_len;
	uint8_t supported_oper_classes[REG_MAX_SUPP_OPER_CLASSES];
} tCsrStaParams;

typedef struct tagCsrScanResultInfo {
	/*
	 * Carry the IEs for the current BSSDescription.
	 * A pointer to tDot11fBeaconIEs. Maybe NULL for start BSS.
	 */
	void *pvIes;
	tAniSSID ssId;
	unsigned long timer;           /* timer is variable for hidden SSID timer */
	/*
	 * This member must be the last in the structure because the
	 * end of tSirBssDescription is an
	 * array with nonknown size at this time */
	tSirBssDescription BssDescriptor;
} tCsrScanResultInfo;

typedef struct tagCsrEncryptionList {

	uint32_t numEntries;
	eCsrEncryptionType encryptionType[eCSR_NUM_OF_ENCRYPT_TYPE];

} tCsrEncryptionList, *tpCsrEncryptionList;

typedef struct tagCsrAuthList {
	uint32_t numEntries;
	eCsrAuthType authType[eCSR_NUM_OF_SUPPORT_AUTH_TYPE];
} tCsrAuthList, *tpCsrAuthList;

typedef struct tagCsrMobilityDomainInfo {
	uint8_t mdiePresent;
	uint16_t mobilityDomain;
} tCsrMobilityDomainInfo;

#ifdef FEATURE_WLAN_ESE
typedef struct tagCsrEseCckmInfo {
	uint32_t reassoc_req_num;
	bool krk_plumbed;
	uint8_t krk[SIR_KRK_KEY_LEN];
#ifdef WLAN_FEATURE_ROAM_OFFLOAD
	uint8_t btk[SIR_BTK_KEY_LEN];
#endif
} tCsrEseCckmInfo;

typedef struct tagCsrEseCckmIe {
	uint8_t cckmIe[DOT11F_IE_RSN_MAX_LEN];
	uint8_t cckmIeLen;
} tCsrEseCckmIe;
#endif /* FEATURE_WLAN_ESE */

typedef struct sCsrChannel_ {
	uint8_t numChannels;
	uint8_t channelList[WNI_CFG_VALID_CHANNEL_LIST_LEN];
} sCsrChannel;

typedef struct tagCsrScanResultFilter {
	tCsrBSSIDs BSSIDs;
	tCsrSSIDs SSIDs;
	tCsrChannelInfo ChannelInfo;
	tCsrAuthList authType;
	tCsrEncryptionList EncryptionType;
	/*
	 * eCSR_ENCRYPT_TYPE_ANY cannot be set in multicast encryption type.
	 * If caller doesn't case, put all supported encryption types in here
	 */
	tCsrEncryptionList mcEncryptionType;
	eCsrRoamBssType BSSType;
	/* its a bit mask of all the needed phy mode defined in eCsrPhyMode */
	eCsrPhyMode phyMode;
	/*
	 * If countryCode[0] is not 0, countryCode is checked
	 * independent of fCheckUnknownCountryCode
	 */
	uint8_t countryCode[WNI_CFG_COUNTRY_CODE_LEN];
	uint8_t uapsd_mask;
	/* For WPS filtering if true => auth and ecryption should be ignored */
	bool bWPSAssociation;
	bool bOSENAssociation;
	/*
	 * For measurement reports --> if set, only SSID,
	 * BSSID and channel is considered for filtering.
	 */
	bool fMeasurement;
	tCsrMobilityDomainInfo MDID;
	bool p2pResult;
#ifdef WLAN_FEATURE_11W
	/* Management Frame Protection */
	bool MFPEnabled;
	uint8_t MFPRequired;
	uint8_t MFPCapable;
#endif
	/* The following flag is used to distinguish the
	 * roaming case while building the scan filter and
	 * applying it on to the scan results. This is mainly
	 * used to support whitelist ssid feature.
	 */
	uint8_t scan_filter_for_roam;
	struct sCsrChannel_ pcl_channels;
	struct qdf_mac_addr bssid_hint;
	enum QDF_OPMODE csrPersona;
	bool realm_check;
	uint8_t fils_realm[2];
	bool force_rsne_override;
} tCsrScanResultFilter;

typedef struct sCsrChnPower_ {
	uint8_t firstChannel;
	uint8_t numChannels;
	uint8_t maxtxPower;
} sCsrChnPower;

typedef struct tagCsr11dinfo {
	sCsrChannel Channels;
	uint8_t countryCode[WNI_CFG_COUNTRY_CODE_LEN + 1];
	/* max power channel list */
	sCsrChnPower ChnPower[WNI_CFG_VALID_CHANNEL_LIST_LEN];
} tCsr11dinfo;

typedef enum {
	eCSR_ROAM_CANCELLED = 1,
	/* it means error happens before assoc_start/roaming_start is called. */
	eCSR_ROAM_FAILED,
	/*
	 * a CSR trigger roaming operation starts,
	 * callback may get a pointer to tCsrConnectedProfile
	 */
	eCSR_ROAM_ROAMING_START,
	/* a CSR trigger roaming operation is completed */
	eCSR_ROAM_ROAMING_COMPLETION,
	/* Connection completed status. */
	eCSR_ROAM_CONNECT_COMPLETION,
	/*
	 * an association or start_IBSS operation starts,
	 * callback may get a pointer to struct csr_roam_profile and
	 * a pointer to tSirBssDescription
	 */
	eCSR_ROAM_ASSOCIATION_START,
	/*
	 * a roaming operation is finish, see eCsrRoamResult for
	 * possible data passed back
	 */
	eCSR_ROAM_ASSOCIATION_COMPLETION,
	eCSR_ROAM_DISASSOCIATED,
	eCSR_ROAM_ASSOCIATION_FAILURE,
	/* when callback with this flag. it gets a pointer to the BSS desc. */
	eCSR_ROAM_SHOULD_ROAM,
	/* A new candidate for PMKID is found */
	eCSR_ROAM_SCAN_FOUND_NEW_BSS,
	/* CSR is done lostlink roaming and still cannot reconnect */
	eCSR_ROAM_LOSTLINK,
	/* a link lost is detected. CSR starts roaming. */
	eCSR_ROAM_LOSTLINK_DETECTED,
	/*
	 * TKIP MIC error detected, callback gets a pointer
	 * to tpSirSmeMicFailureInd
	 */
	eCSR_ROAM_MIC_ERROR_IND,
	/* IBSS indications. */
	eCSR_ROAM_IBSS_IND,
	/*
	 * Update the connection status, useful for IBSS: new peer added,
	 * network is active etc.
	 */
	eCSR_ROAM_CONNECT_STATUS_UPDATE,
	eCSR_ROAM_GEN_INFO,
	eCSR_ROAM_SET_KEY_COMPLETE,
	eCSR_ROAM_IBSS_LEAVE,   /* IBSS indications. */
	/* BSS in SoftAP mode status indication */
	eCSR_ROAM_INFRA_IND,
	eCSR_ROAM_WPS_PBC_PROBE_REQ_IND,
	eCSR_ROAM_FT_RESPONSE,
	eCSR_ROAM_FT_START,
	/* this mean error happens before assoc_start/roam_start is called. */
	eCSR_ROAM_SESSION_OPENED,
	eCSR_ROAM_FT_REASSOC_FAILED,
	eCSR_ROAM_PMK_NOTIFY,
	/*
	 * Following 4 enums are used by FEATURE_WLAN_LFR_METRICS
	 * but they are needed for compilation even when
	 * FEATURE_WLAN_LFR_METRICS is not defined.
	 */
	eCSR_ROAM_PREAUTH_INIT_NOTIFY,
	eCSR_ROAM_PREAUTH_STATUS_SUCCESS,
	eCSR_ROAM_PREAUTH_STATUS_FAILURE,
	eCSR_ROAM_HANDOVER_SUCCESS,
	/*
	 * TDLS callback events
	 */
	eCSR_ROAM_TDLS_STATUS_UPDATE,
	eCSR_ROAM_RESULT_MGMT_TX_COMPLETE_IND,

	/* Disaconnect all the clients */
	eCSR_ROAM_DISCONNECT_ALL_P2P_CLIENTS,
	/* Stopbss triggered from SME due to different */
	eCSR_ROAM_SEND_P2P_STOP_BSS,
	/* beacon interval */
#ifdef WLAN_FEATURE_11W
	eCSR_ROAM_UNPROT_MGMT_FRAME_IND,
#endif

	eCSR_ROAM_IBSS_PEER_INFO_COMPLETE,

#ifdef FEATURE_WLAN_ESE
	eCSR_ROAM_TSM_IE_IND,
	eCSR_ROAM_CCKM_PREAUTH_NOTIFY,
	eCSR_ROAM_ESE_ADJ_AP_REPORT_IND,
	eCSR_ROAM_ESE_BCN_REPORT_IND,
#endif /* FEATURE_WLAN_ESE */

	/* Radar indication from lower layers */
	eCSR_ROAM_DFS_RADAR_IND,
	eCSR_ROAM_SET_CHANNEL_RSP,

	/* Channel sw update notification */
	eCSR_ROAM_DFS_CHAN_SW_NOTIFY,
	eCSR_ROAM_EXT_CHG_CHNL_IND,
	eCSR_ROAM_STA_CHANNEL_SWITCH,
	eCSR_ROAM_NDP_STATUS_UPDATE,
	eCSR_ROAM_UPDATE_SCAN_RESULT,
	eCSR_ROAM_START,
	eCSR_ROAM_ABORT,
	eCSR_ROAM_NAPI_OFF,
	eCSR_ROAM_CHANNEL_COMPLETE_IND,
	eCSR_ROAM_CAC_COMPLETE_IND,
	eCSR_ROAM_SAE_COMPUTE,
	/* LFR3 Roam sync complete */
	eCSR_ROAM_SYNCH_COMPLETE,
	eCSR_ROAM_FIPS_PMK_REQUEST,
} eRoamCmdStatus;

/* comment inside indicates what roaming callback gets */
typedef enum {
	eCSR_ROAM_RESULT_NONE,
	eCSR_ROAM_RESULT_SUCCESS = eCSR_ROAM_RESULT_NONE,
	/*
	 * If roamStatus is eCSR_ROAM_ASSOCIATION_COMPLETION,
	 * struct csr_roam_info's pBssDesc may pass back
	 */
	eCSR_ROAM_RESULT_FAILURE,
	/* Pass back pointer to struct csr_roam_info */
	eCSR_ROAM_RESULT_ASSOCIATED,
	eCSR_ROAM_RESULT_NOT_ASSOCIATED,
	eCSR_ROAM_RESULT_MIC_FAILURE,
	eCSR_ROAM_RESULT_FORCED,
	eCSR_ROAM_RESULT_DISASSOC_IND,
	eCSR_ROAM_RESULT_DEAUTH_IND,
	eCSR_ROAM_RESULT_CAP_CHANGED,
	/*
	 * This means we starts an IBSS struct csr_roam_info's
	 * pBssDesc may pass back
	 */
	eCSR_ROAM_RESULT_IBSS_STARTED,
	eCSR_ROAM_RESULT_IBSS_START_FAILED,
	eCSR_ROAM_RESULT_IBSS_JOIN_SUCCESS,
	eCSR_ROAM_RESULT_IBSS_JOIN_FAILED,
	eCSR_ROAM_RESULT_IBSS_CONNECT,
	eCSR_ROAM_RESULT_IBSS_INACTIVE,
	/*
	 * If roamStatus is eCSR_ROAM_ASSOCIATION_COMPLETION struct
	 * csr_roam_info's pBssDesc may pass back and the peer's MAC
	 * address in peerMacOrBssid. If roamStatus is
	 * eCSR_ROAM_IBSS_IND, the peer's MAC address in
	 * peerMacOrBssid and a beacon frame of the IBSS in pbFrames
	 */
	eCSR_ROAM_RESULT_IBSS_NEW_PEER,
	/*
	 * Peer departed from IBSS, Callback may get a pointer tSmeIbssPeerInd
	 * in pIbssPeerInd
	 */
	eCSR_ROAM_RESULT_IBSS_PEER_DEPARTED,
	/*
	 * Coalescing in the IBSS network (joined an IBSS network)
	 * Callback pass a BSSID in peerMacOrBssid
	 */
	eCSR_ROAM_RESULT_IBSS_COALESCED,
	/*
	 * If roamStatus is eCSR_ROAM_ROAMING_START, callback may get a pointer
	 * to tCsrConnectedProfile used to connect.
	 */
	eCSR_ROAM_RESULT_IBSS_STOP,
	eCSR_ROAM_RESULT_LOSTLINK,
	eCSR_ROAM_RESULT_MIC_ERROR_UNICAST,
	eCSR_ROAM_RESULT_MIC_ERROR_GROUP,
	eCSR_ROAM_RESULT_AUTHENTICATED,
	eCSR_ROAM_RESULT_NEW_RSN_BSS,
#ifdef FEATURE_WLAN_WAPI
	eCSR_ROAM_RESULT_NEW_WAPI_BSS,
#endif /* FEATURE_WLAN_WAPI */
	/* INFRA started successfully */
	eCSR_ROAM_RESULT_INFRA_STARTED,
	/* INFRA start failed */
	eCSR_ROAM_RESULT_INFRA_START_FAILED,
	/* INFRA stopped */
	eCSR_ROAM_RESULT_INFRA_STOPPED,
	/* A station joining INFRA AP */
	eCSR_ROAM_RESULT_INFRA_ASSOCIATION_IND,
	/* A station joined INFRA AP */
	eCSR_ROAM_RESULT_INFRA_ASSOCIATION_CNF,
	/* INFRA disassociated */
	eCSR_ROAM_RESULT_INFRA_DISASSOCIATED,
	eCSR_ROAM_RESULT_WPS_PBC_PROBE_REQ_IND,
	eCSR_ROAM_RESULT_SEND_ACTION_FAIL,
	/* peer rejected assoc because max assoc limit reached */
	eCSR_ROAM_RESULT_MAX_ASSOC_EXCEEDED,
	/* Assoc rejected due to concurrent session running on a diff channel */
	eCSR_ROAM_RESULT_ASSOC_FAIL_CON_CHANNEL,
	/* TDLS events */
	eCSR_ROAM_RESULT_ADD_TDLS_PEER,
	eCSR_ROAM_RESULT_UPDATE_TDLS_PEER,
	eCSR_ROAM_RESULT_DELETE_TDLS_PEER,
	eCSR_ROAM_RESULT_TEARDOWN_TDLS_PEER_IND,
	eCSR_ROAM_RESULT_DELETE_ALL_TDLS_PEER_IND,
	eCSR_ROAM_RESULT_LINK_ESTABLISH_REQ_RSP,
	eCSR_ROAM_RESULT_TDLS_SHOULD_DISCOVER,
	eCSR_ROAM_RESULT_TDLS_SHOULD_TEARDOWN,
	eCSR_ROAM_RESULT_TDLS_SHOULD_PEER_DISCONNECTED,
	eCSR_ROAM_RESULT_TDLS_CONNECTION_TRACKER_NOTIFICATION,

	eCSR_ROAM_RESULT_IBSS_PEER_INFO_SUCCESS,
	eCSR_ROAM_RESULT_IBSS_PEER_INFO_FAILED,
	eCSR_ROAM_RESULT_DFS_RADAR_FOUND_IND,
	eCSR_ROAM_RESULT_CHANNEL_CHANGE_SUCCESS,
	eCSR_ROAM_RESULT_CHANNEL_CHANGE_FAILURE,
	eCSR_ROAM_RESULT_DFS_CHANSW_UPDATE_SUCCESS,
	eCSR_ROAM_EXT_CHG_CHNL_UPDATE_IND,

	eCSR_ROAM_RESULT_NDI_CREATE_RSP,
	eCSR_ROAM_RESULT_NDI_DELETE_RSP,
	eCSR_ROAM_RESULT_NDP_INITIATOR_RSP,
	eCSR_ROAM_RESULT_NDP_NEW_PEER_IND,
	eCSR_ROAM_RESULT_NDP_CONFIRM_IND,
	eCSR_ROAM_RESULT_NDP_INDICATION,
	eCSR_ROAM_RESULT_NDP_SCHED_UPDATE_RSP,
	eCSR_ROAM_RESULT_NDP_RESPONDER_RSP,
	eCSR_ROAM_RESULT_NDP_END_RSP,
	eCSR_ROAM_RESULT_NDP_PEER_DEPARTED_IND,
	eCSR_ROAM_RESULT_NDP_END_IND,
	eCSR_ROAM_RESULT_CAC_END_IND,
	/* If Scan for SSID failed to found proper BSS */
	eCSR_ROAM_RESULT_SCAN_FOR_SSID_FAILURE,
	eCSR_ROAM_RESULT_INVOKE_FAILED,
} eCsrRoamResult;

typedef enum {
	eCSR_DISCONNECT_REASON_UNSPECIFIED = 0,
	eCSR_DISCONNECT_REASON_MIC_ERROR,
	eCSR_DISCONNECT_REASON_DISASSOC,
	eCSR_DISCONNECT_REASON_DEAUTH,
	eCSR_DISCONNECT_REASON_HANDOFF,
	eCSR_DISCONNECT_REASON_IBSS_LEAVE,
	eCSR_DISCONNECT_REASON_STA_HAS_LEFT,
	eCSR_DISCONNECT_REASON_NDI_DELETE,
	eCSR_DISCONNECT_REASON_ROAM_HO_FAIL,
} eCsrRoamDisconnectReason;

typedef enum {
	/* Not associated in Infra or participating in an IBSS/Ad-hoc */
	eCSR_ASSOC_STATE_TYPE_NOT_CONNECTED,
	/* Associated in an Infrastructure network. */
	eCSR_ASSOC_STATE_TYPE_INFRA_ASSOCIATED,
	/* Participating in IBSS network though disconnection */
	eCSR_ASSOC_STATE_TYPE_IBSS_DISCONNECTED,
	/* Participating in IBSS network with partner stations also present */
	eCSR_ASSOC_STATE_TYPE_IBSS_CONNECTED,
	/* Participating in WDS network in AP/STA mode but not connected yet */
	eCSR_ASSOC_STATE_TYPE_WDS_DISCONNECTED,
	/* Participating in a WDS network and connected peer to peer */
	eCSR_ASSOC_STATE_TYPE_WDS_CONNECTED,
	/* Participating in a Infra network in AP not yet in connected state */
	eCSR_ASSOC_STATE_TYPE_INFRA_DISCONNECTED,
	/* Participating in a Infra network and connected to a peer */
	eCSR_ASSOC_STATE_TYPE_INFRA_CONNECTED,
	/* Disconnecting with AP or stop connecting process */
	eCSR_ASSOC_STATE_TYPE_INFRA_DISCONNECTING,
	/* NAN Data interface not started */
	eCSR_CONNECT_STATE_TYPE_NDI_NOT_STARTED,
	/* NAN Data interface started */
	eCSR_CONNECT_STATE_TYPE_NDI_STARTED,

} eCsrConnectState;

/*
 * This parameter is no longer supported in the Profile.
 * Need to set this in the global properties for the adapter.
 */
typedef enum eCSR_MEDIUM_ACCESS {
	eCSR_MEDIUM_ACCESS_AUTO = 0,
	eCSR_MEDIUM_ACCESS_DCF,
	eCSR_MEDIUM_ACCESS_eDCF,
	eCSR_MEDIUM_ACCESS_HCF,

	eCSR_MEDIUM_ACCESS_WMM_eDCF_802dot1p,
	eCSR_MEDIUM_ACCESS_WMM_eDCF_DSCP,
	eCSR_MEDIUM_ACCESS_WMM_eDCF_NoClassify,
	eCSR_MEDIUM_ACCESS_11e_eDCF = eCSR_MEDIUM_ACCESS_eDCF,
	eCSR_MEDIUM_ACCESS_11e_HCF = eCSR_MEDIUM_ACCESS_HCF,
} eCsrMediaAccessType;

typedef enum {
	eCSR_OPERATING_CHANNEL_ALL = 0,
	eCSR_OPERATING_CHANNEL_AUTO = eCSR_OPERATING_CHANNEL_ALL,
	eCSR_OPERATING_CHANNEL_ANY = eCSR_OPERATING_CHANNEL_ALL,
} eOperationChannel;

typedef enum {
	eCSR_DOT11_FRAG_THRESH_AUTO = -1,
	eCSR_DOT11_FRAG_THRESH_MIN = 256,
	eCSR_DOT11_FRAG_THRESH_MAX = 2346,
	eCSR_DOT11_FRAG_THRESH_DEFAULT = 2000
} eCsrDot11FragThresh;

/*
 * For channel bonding, the channel number gap is 4, either up or down.
 * For both 11a and 11g mode.
 */
#define CSR_CB_CHANNEL_GAP 4
#define CSR_CB_CENTER_CHANNEL_OFFSET    2
#define CSR_SEC_CHANNEL_OFFSET    4


/* WEP keysize (in bits) */
typedef enum {
	/* 40 bit key + 24bit IV = 64bit WEP */
	eCSR_SECURITY_WEP_KEYSIZE_40 = 40,
	/* 104bit key + 24bit IV = 128bit WEP */
	eCSR_SECURITY_WEP_KEYSIZE_104 = 104,
	eCSR_SECURITY_WEP_KEYSIZE_MIN = eCSR_SECURITY_WEP_KEYSIZE_40,
	eCSR_SECURITY_WEP_KEYSIZE_MAX = eCSR_SECURITY_WEP_KEYSIZE_104,
	eCSR_SECURITY_WEP_KEYSIZE_MAX_BYTES =
		(eCSR_SECURITY_WEP_KEYSIZE_MAX / 8),
} eCsrWEPKeySize;

/* Possible values for the WEP static key ID */
typedef enum {

	eCSR_SECURITY_WEP_STATIC_KEY_ID_MIN = 0,
	eCSR_SECURITY_WEP_STATIC_KEY_ID_MAX = 3,
	eCSR_SECURITY_WEP_STATIC_KEY_ID_DEFAULT = 0,

	eCSR_SECURITY_WEP_STATIC_KEY_ID_INVALID = -1,

} eCsrWEPStaticKeyID;

/* Two extra key indicies are used for the IGTK (which is used by BIP) */
#define CSR_MAX_NUM_KEY     (eCSR_SECURITY_WEP_STATIC_KEY_ID_MAX + 2 + 1)

typedef enum {
	eCSR_SECURITY_SET_KEY_ACTION_NO_CHANGE,
	eCSR_SECURITY_SET_KEY_ACTION_SET_KEY,
	eCSR_SECURITY_SET_KEY_ACTION_DELETE_KEY,
} eCsrSetKeyAction;

typedef enum {
	/*
	 * Roaming because HDD requested for reassoc by changing one of the
	 * fields in tCsrRoamModifyProfileFields. OR Roaming because SME
	 * requested for reassoc by changing one of the fields in
	 * tCsrRoamModifyProfileFields.
	 */
	eCsrRoamReasonStaCapabilityChanged,
	/*
	 * Roaming because SME requested for reassoc to a different AP,
	 * as part of inter AP handoff.
	 */
	eCsrRoamReasonBetterAP,
	/*
	 * Roaming because SME requested it as the link is lost - placeholder,
	 * will clean it up once handoff code gets in
	 */
	eCsrRoamReasonSmeIssuedForLostLink,

} eCsrRoamReasonCodes;

typedef enum {
	eCsrRoamWmmAuto = 0,
	eCsrRoamWmmQbssOnly = 1,
	eCsrRoamWmmNoQos = 2,

} eCsrRoamWmmUserModeType;

typedef enum {
	eCSR_REQUESTER_MIN = 0,
	eCSR_DIAG,
	eCSR_UMA_GAN,
	eCSR_HDD
} eCsrStatsRequesterType;

/**
 * enum csr_hi_rssi_scan_id - Parameter ids for hi rssi scan feature
 *
 * @eCSR_HI_RSSI_SCAN_MAXCOUNT_ID: how many times scan can be performed
 * @eCSR_HI_RSSI_SCAN_RSSI_DELTA_ID: rssi difference to trigger scan
 * @eCSR_HI_RSSI_SCAN_DELAY_ID: delay in millseconds between scans
 * @eCSR_HI_RSSI_SCAN_RSSI_UB_ID: rssi upper bound for scan trigger
 */
enum csr_hi_rssi_scan_id {
	eCSR_HI_RSSI_SCAN_MAXCOUNT_ID,
	eCSR_HI_RSSI_SCAN_RSSI_DELTA_ID,
	eCSR_HI_RSSI_SCAN_DELAY_ID,
	eCSR_HI_RSSI_SCAN_RSSI_UB_ID
};

typedef struct tagPmkidCandidateInfo {
	struct qdf_mac_addr BSSID;
	bool preAuthSupported;
} tPmkidCandidateInfo;

typedef struct tagPmkidCacheInfo {
	struct qdf_mac_addr BSSID;
	uint8_t PMKID[CSR_RSN_PMKID_SIZE];
	uint8_t pmk[CSR_RSN_MAX_PMK_LEN];
	uint8_t pmk_len;
	uint8_t ssid_len;
	uint8_t ssid[SIR_MAC_MAX_SSID_LENGTH];
	uint8_t cache_id[CACHE_ID_LEN];
} tPmkidCacheInfo;

#ifdef FEATURE_WLAN_WAPI
typedef struct tagBkidCandidateInfo {
	struct qdf_mac_addr BSSID;
	bool preAuthSupported;
} tBkidCandidateInfo;

typedef struct tagBkidCacheInfo {
	struct qdf_mac_addr BSSID;
	uint8_t BKID[CSR_WAPI_BKID_SIZE];
} tBkidCacheInfo;
#endif /* FEATURE_WLAN_WAPI */

typedef struct tagCsrKeys {
	/* Also use to indicate whether the key index is set */
	uint8_t KeyLength[CSR_MAX_NUM_KEY];
	uint8_t KeyMaterial[CSR_MAX_NUM_KEY][CSR_MAX_KEY_LEN];
	uint8_t defaultIndex;
} tCsrKeys;

/*
 * Following fields which're part of tCsrRoamConnectedProfile might need
 * modification dynamically once STA is up & running & this'd trigger reassoc
 */
typedef struct tagCsrRoamModifyProfileFields {
	/*
	 * during connect this specifies ACs U-APSD is to be setup
	 * for (Bit0:VO; Bit1:VI; Bit2:BK; Bit3:BE all other bits are ignored).
	 * During assoc response this COULD carry confirmation of what
	 * ACs U-APSD got setup for. Later if an APP looking for APSD,
	 * SME-QoS might need to modify this field
	 */
	uint8_t uapsd_mask;
	/* HDD might ask to modify this field */
	uint16_t listen_interval;
} tCsrRoamModifyProfileFields;

struct csr_roam_profile {
	tCsrSSIDs SSIDs;
	tCsrBSSIDs BSSIDs;
	/* this is bit mask of all the needed phy mode defined in eCsrPhyMode */
	uint32_t phyMode;
	eCsrRoamBssType BSSType;
	tCsrAuthList AuthType;
	eCsrAuthType negotiatedAuthType;
	tCsrEncryptionList EncryptionType;
	/* This field is for output only, not for input */
	eCsrEncryptionType negotiatedUCEncryptionType;
	/*
	 * eCSR_ENCRYPT_TYPE_ANY cannot be set in multicast encryption type.
	 * If caller doesn't case, put all supported encryption types in here
	 */
	tCsrEncryptionList mcEncryptionType;
	/* This field is for output only, not for input */
	eCsrEncryptionType negotiatedMCEncryptionType;
#ifdef WLAN_FEATURE_11W
	/* Management Frame Protection */
	bool MFPEnabled;
	uint8_t MFPRequired;
	uint8_t MFPCapable;
#endif
	tAniEdType mgmt_encryption_type;
	tCsrKeys Keys;
	tCsrChannelInfo ChannelInfo;
	uint8_t operationChannel;
	struct ch_params ch_params;
	/* If this is 0, SME will fill in for caller. */
	uint16_t beaconInterval;
	/*
	 * during connect this specifies ACs U-APSD is to be setup
	 * for (Bit0:VO; Bit1:VI; Bit2:BK; Bit3:BE all other bits are ignored).
	 * During assoc resp this'd carry cnf of what ACs U-APSD got setup for
	 */
	uint8_t uapsd_mask;
	uint32_t nWPAReqIELength; /* The byte count in the pWPAReqIE */
	uint8_t *pWPAReqIE;       /* If not null,it's IE byte stream for WPA */
	uint32_t nRSNReqIELength; /* The byte count in the pRSNReqIE */
	uint8_t *pRSNReqIE;       /* If not null,it's IE byte stream for RSN */
#ifdef FEATURE_WLAN_WAPI
	uint32_t nWAPIReqIELength;/* The byte count in the pWAPIReqIE */
	uint8_t *pWAPIReqIE;      /* If not null,it's IE byte stream for WAPI */
#endif /* FEATURE_WLAN_WAPI */

	uint32_t nAddIEScanLength;/* pAddIE for scan (at the time of join) */
	/*
	 * If not null,it's the IE byte stream for additional IE,
	 * which can be WSC IE and/or P2P IE
	 */
	uint8_t *pAddIEScan;
	uint32_t nAddIEAssocLength; /* The byte count in the pAddIE for assoc */
	/*
	 * If not null, it has the IE byte stream for additional IE,
	 * which can be WSC IE and/or P2P IE
	 */
	uint8_t *pAddIEAssoc;
	/* it is ignored if [0] is 0. */
	uint8_t countryCode[WNI_CFG_COUNTRY_CODE_LEN];
	/* WPS Association if true => auth and ecryption should be ignored */
	bool bWPSAssociation;
	bool bOSENAssociation;
	uint32_t nWSCReqIELength; /* The byte count in the pWSCReqIE */
	uint8_t *pWSCReqIE;       /* If not null,it's IE byte stream for WSC */
	uint8_t ieee80211d;
	uint8_t privacy;
	bool fwdWPSPBCProbeReq;
	tAniAuthType csr80211AuthType;
	uint32_t dtimPeriod;
	bool ApUapsdEnable;
	bool protEnabled;
	bool obssProtEnabled;
	bool chan_switch_hostapd_rate_enabled;
	uint16_t cfg_protection;
	uint8_t wps_state;
	tCsrMobilityDomainInfo MDID;
	enum QDF_OPMODE csrPersona;
	uint8_t disableDFSChSwitch;
	/* addIe params */
	tSirAddIeParams addIeParams;
	uint8_t sap_dot11mc;
	uint16_t beacon_tx_rate;
	tSirMacRateSet  supported_rates;
	tSirMacRateSet  extended_rates;
	struct qdf_mac_addr bssid_hint;
	bool force_24ghz_in_ht20;
	uint32_t cac_duration_ms;
	uint32_t dfs_regdomain;
	bool supplicant_disabled_roaming;
	bool driver_disabled_roaming;
#ifdef WLAN_FEATURE_FILS_SK
	bool fils_connection;
	uint8_t *hlp_ie;
	uint32_t hlp_ie_len;
	struct cds_fils_connection_info *fils_con_info;
#endif
	bool force_rsne_override;
};

#ifdef FEATURE_WLAN_MCC_TO_SCC_SWITCH
typedef struct tagCsrRoamHTProfile {
	uint8_t phymode;
	uint8_t htCapability;
	uint8_t htSupportedChannelWidthSet;
	uint8_t htRecommendedTxWidthSet;
	ePhyChanBondState htSecondaryChannelOffset;
	uint8_t vhtCapability;
	uint8_t apCenterChan;
	uint8_t apChanWidth;
} tCsrRoamHTProfile;
#endif

typedef struct tagCsrRoamConnectedProfile {
	tSirMacSSid SSID;
	bool handoffPermitted;
	bool ssidHidden;
	uint8_t operationChannel;
	struct qdf_mac_addr bssid;
	uint16_t beaconInterval;
	eCsrRoamBssType BSSType;
	eCsrAuthType AuthType;
	tCsrAuthList AuthInfo;
	eCsrEncryptionType EncryptionType;
	tCsrEncryptionList EncryptionInfo;
	eCsrEncryptionType mcEncryptionType;
	tCsrEncryptionList mcEncryptionInfo;
	/* group management cipher suite used for 11w */
	tAniEdType mgmt_encryption_type;
	uint8_t country_code[WNI_CFG_COUNTRY_CODE_LEN];
	uint32_t vht_channel_width;
	tCsrKeys Keys;
	/*
	 * meaningless on connect. It's an OUT param from CSR's point of view
	 * During assoc response carries the ACM bit-mask i.e. what
	 * ACs have ACM=1 (if any),(Bit0:VO; Bit1:VI; Bit2:BK; Bit3:BE
	 * all other bits are ignored)
	 */
	uint8_t acm_mask;
	tCsrRoamModifyProfileFields modifyProfileFields;
	bool qosConnection;     /* A connection is QoS enabled */
	uint32_t nAddIEAssocLength;
	/*
	 * If not null,it's IE byte stream for additional IE,
	 * which can be WSC IE and/or P2P IE
	 */
	uint8_t *pAddIEAssoc;
	tSirBssDescription *pBssDesc;
	bool qap;               /* AP supports QoS */
	tCsrMobilityDomainInfo MDID;
#ifdef FEATURE_WLAN_ESE
	tCsrEseCckmInfo eseCckmInfo;
	bool isESEAssoc;
#endif
	uint32_t dot11Mode;
	uint8_t proxyARPService;
#ifdef FEATURE_WLAN_MCC_TO_SCC_SWITCH
	tCsrRoamHTProfile HTProfile;
#endif
#ifdef WLAN_FEATURE_11W
	/* Management Frame Protection */
	bool MFPEnabled;
	uint8_t MFPRequired;
	uint8_t MFPCapable;
#endif
} tCsrRoamConnectedProfile;

typedef struct tagCsrNeighborRoamConfigParams {

	uint32_t nNeighborScanTimerPeriod;
	uint32_t neighbor_scan_min_timer_period;
	uint8_t nNeighborLookupRssiThreshold;
	int8_t rssi_thresh_offset_5g;
	uint16_t nNeighborScanMinChanTime;
	uint16_t nNeighborScanMaxChanTime;
	sCsrChannel neighborScanChanList;
	uint8_t nMaxNeighborRetries;
	uint16_t nNeighborResultsRefreshPeriod;
	uint16_t nEmptyScanRefreshPeriod;
	uint8_t nOpportunisticThresholdDiff;
	uint8_t nRoamRescanRssiDiff;
	uint8_t nRoamBmissFirstBcnt;
	uint8_t nRoamBmissFinalBcnt;
	uint8_t nRoamBeaconRssiWeight;
	uint8_t delay_before_vdev_stop;
	uint32_t nhi_rssi_scan_max_count;
	uint32_t nhi_rssi_scan_rssi_delta;
	uint32_t nhi_rssi_scan_delay;
	int32_t nhi_rssi_scan_rssi_ub;
} tCsrNeighborRoamConfigParams;

/**
 * enum sta_roam_policy_dfs_mode - state of DFS mode for STA ROME policy
 * @CSR_STA_ROAM_POLICY_NONE: DFS mode attribute is not valid
 * @CSR_STA_ROAM_POLICY_DFS_ENABLED:  DFS mode is enabled
 * @CSR_STA_ROAM_POLICY_DFS_DISABLED: DFS mode is disabled
 * @CSR_STA_ROAM_POLICY_DFS_DEPRIORITIZE: Deprioritize DFS channels in scanning
 */
enum sta_roam_policy_dfs_mode {
	CSR_STA_ROAM_POLICY_NONE,
	CSR_STA_ROAM_POLICY_DFS_ENABLED,
	CSR_STA_ROAM_POLICY_DFS_DISABLED,
	CSR_STA_ROAM_POLICY_DFS_DEPRIORITIZE
};

/**
 * struct csr_sta_roam_policy_params - sta roam policy params for station
 * @dfs_mode: tell is DFS channels needs to be skipped while scanning
 * @skip_unsafe_channels: tells if unsafe channels needs to be skip in scanning
 * @sap_operating_band: Opearting band for SAP
 */
struct csr_sta_roam_policy_params {
	enum sta_roam_policy_dfs_mode dfs_mode;
	bool skip_unsafe_channels;
	uint8_t sap_operating_band;
};

/**
 * struct csr_mbo_thresholds - mbo related thresholds
 * @mbo_candidate_rssi_thres - Candidate RSSI threshold
 * @mbo_current_rssi_thres - Current RSSI threshold
 * @mbo_current_rssi_mcc_thres - Current RSSI MCC threshold
 * mbo_candidate_rssi_btc_thres - Candidate RSSI BTC threshold
 */
struct csr_mbo_thresholds {
	int8_t mbo_candidate_rssi_thres;
	int8_t mbo_current_rssi_thres;
	int8_t mbo_current_rssi_mcc_thres;
	int8_t mbo_candidate_rssi_btc_thres;
};

/**
 * struct csr_neighbor_report_offload_params - neighbor report offload params
 * @params_bitmask: bitmask to specify which of the below are enabled
 * @time_offset: time offset after 11k offload command to trigger a neighbor
 *		report request (in seconds)
 * @low_rssi_offset: Offset from rssi threshold to trigger neighbor
 *	report request (in dBm)
 * @bmiss_count_trigger: Number of beacon miss events to trigger neighbor
 *		report request
 * @per_threshold_offset: offset from PER threshold to trigger neighbor
 *		report request (in %)
 * @neighbor_report_cache_timeout: timeout after which new trigger can enable
 *		sending of a neighbor report request (in seconds)
 * @max_neighbor_report_req_cap: max number of neighbor report requests that
 *		can be sent to the peer in the current session
 */
struct csr_neighbor_report_offload_params {
	uint8_t params_bitmask;
	uint32_t time_offset;
	uint32_t low_rssi_offset;
	uint32_t bmiss_count_trigger;
	uint32_t per_threshold_offset;
	uint32_t neighbor_report_cache_timeout;
	uint32_t max_neighbor_report_req_cap;
};

typedef struct tagCsrConfigParam {
	uint32_t FragmentationThreshold;
	/* keep this uint32_t. This gets converted to ePhyChannelBondState */
	uint32_t channelBondingMode24GHz;
	uint32_t channelBondingMode5GHz;
	eCsrPhyMode phyMode;
	enum band_info eBand;
	uint32_t RTSThreshold;
	uint32_t HeartbeatThresh50;
	uint32_t HeartbeatThresh24;
	enum band_info bandCapability;     /* indicate hw capability */
	eCsrRoamWmmUserModeType WMMSupportMode;
	bool Is11eSupportEnabled;
	bool Is11dSupportEnabled;
	bool Is11hSupportEnabled;
	bool shortSlotTime;
	bool ProprietaryRatesEnabled;
	uint8_t AdHocChannel24;
	uint8_t AdHocChannel5G;
	/*
	 * this number minus one is the number of times a scan doesn't find it
	 * before it is removed
	 */
	uint32_t nScanResultAgeCount;
	/* to set the RSSI difference for each category */
	uint8_t bCatRssiOffset;
	/* to set MCC Enable/Disable mode */
	uint8_t fEnableMCCMode;
	bool mcc_rts_cts_prot_enable;
	bool mcc_bcast_prob_resp_enable;
	/*
	 * To allow MCC GO different B.I than STA's.
	 * NOTE: make sure if RIVA firmware can handle this combination before
	 * enabling this at the moment, this flag is provided only to pass
	 * Wi-Fi Cert. 5.1.12
	 */
	uint8_t fAllowMCCGODiffBI;
	tCsr11dinfo Csr11dinfo;

	/* Country Code Priority */
	bool fSupplicantCountryCodeHasPriority;
	uint16_t vccRssiThreshold;
	uint32_t vccUlMacLossThreshold;
	uint32_t nPassiveMinChnTime;        /* in units of milliseconds */
	uint32_t nPassiveMaxChnTime;        /* in units of milliseconds */
	uint32_t nActiveMinChnTime;         /* in units of milliseconds */
	uint32_t nActiveMaxChnTime;         /* in units of milliseconds */
	uint32_t nInitialDwellTime;         /* in units of milliseconds */
	bool initial_scan_no_dfs_chnl;
	uint32_t nPassiveMinChnTimeConc;    /* in units of milliseconds */
	uint32_t nPassiveMaxChnTimeConc;    /* in units of milliseconds */
	uint32_t nActiveMinChnTimeConc;     /* in units of milliseconds */
	uint32_t nActiveMaxChnTimeConc;     /* in units of milliseconds */
	uint32_t nRestTimeConc;             /* in units of milliseconds */
	/*In units of milliseconds*/
	uint32_t       min_rest_time_conc;
	/*In units of milliseconds*/
	uint32_t       idle_time_conc;

	/*
	 * in dBm, the maximum TX power The actual TX power is the lesser of
	 * this value and 11d. If 11d is disable, the lesser of this and
	 * default setting.
	 */
	uint8_t nTxPowerCap;
	bool allow_tpc_from_ap;
	/* stats request frequency from PE while in full power */
	uint32_t statsReqPeriodicity;
	/* stats request frequency from PE while in power save */
	uint32_t statsReqPeriodicityInPS;
#ifdef FEATURE_WLAN_ESE
	uint8_t isEseIniFeatureEnabled;
#endif
	uint8_t isFastRoamIniFeatureEnabled;
	struct mawc_params csr_mawc_config;
	uint8_t isFastTransitionEnabled;
	uint8_t RoamRssiDiff;
	int32_t rssi_abs_thresh;
	bool isWESModeEnabled;
	tCsrNeighborRoamConfigParams neighborRoamConfig;
	/*
	 * Instead of Reassoc, send ADDTS/DELTS even when ACM is off for that AC
	 * This is mandated by WMM-AC certification
	 */
	bool addTSWhenACMIsOff;
	/*
	 * Customer wants to start with an active scan based on the default
	 * country code. This optimization will minimize the driver load to
	 * association time. Based on this flag we will bypass the initial
	 * passive scan needed for 11d to determine the country code & domain
	 */
	bool fEnableBypass11d;
	/*
	 * Customer wants to optimize the scan time. Avoiding scans(passive)
	 * on DFS channels while swipping through both bands can save some time
	 * (apprx 1.3 sec)
	 */
	uint8_t fEnableDFSChnlScan;
	/*
	 * To enable/disable scanning 2.4Ghz channels twice on a single scan
	 * request from HDD
	 */
	bool fScanTwice;
	uint32_t nVhtChannelWidth;
	uint8_t enableTxBF;
	bool enable_subfee_vendor_vhtie;
	uint8_t enable_txbf_sap_mode;
	uint8_t enable2x2;
	bool enableVhtFor24GHz;
	bool vendor_vht_sap;
	uint8_t enableMuBformee;
	uint8_t enableVhtpAid;
	uint8_t enableVhtGid;
	uint8_t enableAmpduPs;
	uint8_t enableHtSmps;
	uint8_t htSmps;
	bool send_smps_action;
	bool ignore_peer_erp_info;
	/*
	 * To enable/disable scanning only 2.4Ghz channels on first scan
	 */
	bool fFirstScanOnly2GChnl;
	bool nRoamPrefer5GHz;
	bool nRoamIntraBand;
	uint8_t nProbes;
	uint16_t nRoamScanHomeAwayTime;

	bool isRoamOffloadScanEnabled;
	bool bFastRoamInConIniFeatureEnabled;
	uint8_t scanCfgAgingTime;
	uint8_t enable_tx_ldpc;
	uint8_t enable_rx_ldpc;
	uint8_t disable_high_ht_mcs_2x2;
	bool enable_vht20_mcs9;
	uint8_t max_amsdu_num;
	uint8_t nSelect5GHzMargin;
	uint32_t ho_delay_for_rx;
	uint32_t min_delay_btw_roam_scans;
	uint32_t roam_trigger_reason_bitmask;
	bool roaming_scan_policy;
	uint8_t isCoalesingInIBSSAllowed;
#ifdef FEATURE_WLAN_MCC_TO_SCC_SWITCH
	uint8_t cc_switch_mode;
#endif
	uint8_t allowDFSChannelRoam;
#ifdef WLAN_FEATURE_ROAM_OFFLOAD
	uint32_t roam_preauth_retry_count;
	uint32_t roam_preauth_no_ack_timeout;
	bool isRoamOffloadEnabled;
	bool enable_disconnect_roam_offload;
	bool enable_idle_roam;
	uint32_t idle_roam_rssi_delta;
	uint32_t idle_roam_inactive_time;
	uint32_t idle_data_packet_count;
	uint32_t idle_roam_band;
	int32_t idle_roam_min_rssi;
#endif
	bool obssEnabled;
	uint8_t conc_custom_rule1;
	uint8_t conc_custom_rule2;
	uint8_t is_sta_connection_in_5gz_enabled;
	bool send_deauth_before_con;

	/* 802.11p enable */
	bool enable_dot11p;
	uint8_t max_scan_count;
	bool early_stop_scan_enable;
	int8_t early_stop_scan_min_threshold;
	int8_t early_stop_scan_max_threshold;
	int8_t first_scan_bucket_threshold;
	uint8_t fEnableDebugLog;
	uint8_t max_intf_count;
	bool enable5gEBT;
	bool enableSelfRecovery;
	uint32_t f_sta_miracast_mcc_rest_time_val;
#ifdef FEATURE_AP_MCC_CH_AVOIDANCE
	bool sap_channel_avoidance;
#endif /* FEATURE_AP_MCC_CH_AVOIDANCE */
	bool acs_with_more_param;
	uint8_t f_prefer_non_dfs_on_radar;
	bool is_ps_enabled;
	uint32_t auto_bmps_timer_val;
	uint32_t dual_mac_feature_disable;
	uint32_t sta_sap_scc_on_dfs_chan;
	uint32_t roam_dense_traffic_thresh;
	uint32_t roam_dense_rssi_thresh_offset;
	uint32_t roam_dense_min_aps;
	int8_t roam_bg_scan_bad_rssi_thresh;
	uint8_t roam_bad_rssi_thresh_offset_2g;
	uint32_t roam_bg_scan_client_bitmap;
	uint32_t obss_width_interval;
	uint32_t obss_active_dwelltime;
	uint32_t obss_passive_dwelltime;
	bool ignore_peer_ht_opmode;
	bool enable_edca_params;
	uint32_t edca_vo_cwmin;
	uint32_t edca_vi_cwmin;
	uint32_t edca_bk_cwmin;
	uint32_t edca_be_cwmin;
	uint32_t edca_vo_cwmax;
	uint32_t edca_vi_cwmax;
	uint32_t edca_bk_cwmax;
	uint32_t edca_be_cwmax;
	uint32_t edca_vo_aifs;
	uint32_t edca_vi_aifs;
	uint32_t edca_bk_aifs;
	uint32_t edca_be_aifs;
	bool enable_fatal_event;
	enum scan_dwelltime_adaptive_mode scan_adaptive_dwell_mode;
	enum scan_dwelltime_adaptive_mode scan_adaptive_dwell_mode_nc;
	enum scan_dwelltime_adaptive_mode roamscan_adaptive_dwell_mode;
	struct csr_sta_roam_policy_params sta_roam_policy_params;
	uint32_t tx_aggregation_size;
	uint32_t tx_aggregation_size_be;
	uint32_t tx_aggregation_size_bk;
	uint32_t tx_aggregation_size_vi;
	uint32_t tx_aggregation_size_vo;
	uint32_t rx_aggregation_size;
	uint32_t tx_aggr_sw_retry_threshold_be;
	uint32_t tx_aggr_sw_retry_threshold_bk;
	uint32_t tx_aggr_sw_retry_threshold_vi;
	uint32_t tx_aggr_sw_retry_threshold_vo;
	uint32_t tx_aggr_sw_retry_threshold;
	uint32_t tx_non_aggr_sw_retry_threshold_be;
	uint32_t tx_non_aggr_sw_retry_threshold_bk;
	uint32_t tx_non_aggr_sw_retry_threshold_vi;
	uint32_t tx_non_aggr_sw_retry_threshold_vo;
	uint32_t tx_non_aggr_sw_retry_threshold;
	struct wmi_per_roam_config per_roam_config;
	bool enable_bcast_probe_rsp;
	bool is_fils_enabled;
#ifdef WLAN_FEATURE_11AX
	bool enable_ul_ofdma;
	bool enable_ul_mimo;
#endif
	uint16_t wlm_latency_enable;
	uint16_t wlm_latency_level;
	uint32_t wlm_latency_flags[CSR_NUM_WLM_LATENCY_LEVEL];
	bool qcn_ie_support;
	uint8_t fils_max_chan_guard_time;
	uint16_t pkt_err_disconn_th;
	enum force_1x1_type is_force_1x1_enable;
	uint16_t num_11b_tx_chains;
	uint16_t num_11ag_tx_chains;
	uint32_t disallow_duration;
	uint32_t rssi_channel_penalization;
	uint32_t num_disallowed_aps;
	struct sir_score_config bss_score_params;
	uint8_t oce_feature_bitmap;
	struct csr_mbo_thresholds mbo_thresholds;
	uint32_t btm_offload_config;
	uint32_t pmkid_modes;
	uint32_t btm_solicited_timeout;
	uint32_t btm_max_attempt_cnt;
	uint32_t btm_sticky_time;
	uint32_t btm_query_bitmask;
	uint32_t btm_trig_min_candidate_score;
	uint32_t offload_11k_enable_bitmask;
	bool wep_tkip_in_he;
	struct csr_neighbor_report_offload_params neighbor_report_offload;
	bool enable_ftopen;
	bool roam_force_rssi_trigger;
	uint32_t btm_validity_timer;
	uint32_t btm_disassoc_timer_threshold;
	bool enable_bss_load_roam_trigger;
	uint32_t bss_load_threshold;
	uint32_t bss_load_sample_time;
	int32_t bss_load_trigger_rssi_threshold_5ghz;
	int32_t bss_load_trigger_rssi_threshold_24ghz;
	uint32_t roam_scan_inactivity_time;
	uint32_t roam_inactive_data_packet_count;
	uint32_t roam_scan_period_after_inactivity;
	int32_t disconnect_roam_min_rssi;
	int32_t bmiss_roam_min_rssi;
	uint32_t btm_roam_score_delta;
	uint32_t idle_roam_score_delta;
#ifdef WLAN_ADAPTIVE_11R
	bool enable_adaptive_11r;
#endif
	bool enable_pending_list_req;
	bool disable_4way_hs_offload;
} tCsrConfigParam;

/* Tush */
typedef struct tagCsrUpdateConfigParam {
	tCsr11dinfo Csr11dinfo;
} tCsrUpdateConfigParam;
#ifdef WLAN_FEATURE_ROAM_OFFLOAD
typedef void (*sme_get_raom_scan_ch_Callback)(
				hdd_handle_t hdd_handle,
				struct roam_scan_ch_resp *roam_ch,
				void *context);

#define csr_roamIsRoamOffloadEnabled(pMac) \
	(pMac->roam.configParam.isRoamOffloadEnabled)
#define DEFAULT_REASSOC_FAILURE_TIMEOUT 1000
#else
#define csr_roamIsRoamOffloadEnabled(pMac)  false
#endif

#ifdef WLAN_FEATURE_ROAM_OFFLOAD
/* connected but not authenticated */
#define CSR_ROAM_AUTH_STATUS_CONNECTED      0x1
/* connected and authenticated */
#define CSR_ROAM_AUTH_STATUS_AUTHENTICATED  0x2
#endif

struct csr_roam_info {
	struct csr_roam_profile *pProfile;
	tSirBssDescription *pBssDesc;
	uint32_t nBeaconLength;
	uint32_t nAssocReqLength;
	uint32_t nAssocRspLength;
	uint32_t nFrameLength;
	uint8_t frameType;
	/*
	 * Point to a buffer contain the beacon, assoc req, assoc rsp frame,
	 * in that order user needs to use nBeaconLength, nAssocReqLength,
	 * nAssocRspLength to desice where each frame starts and ends.
	 */
	uint8_t *pbFrames;
	bool fReassocReq;       /* set to true if for re-association */
	bool fReassocRsp;       /* set to true if for re-association */
	struct qdf_mac_addr bssid;
	/*
	 * Only valid in IBSS. this is the peers MAC address for
	 * eCSR_ROAM_RESULT_IBSS_NEW_PEER or PEER_DEPARTED
	 */
	struct qdf_mac_addr peerMac;
	tSirResultCodes statusCode;
	/* this'd be our own defined or sent from otherBSS(per 802.11spec) */
	uint32_t reasonCode;

	uint8_t disassoc_reason;

	uint8_t staId;         /* Peer stationId when connected */
	/* false means auth needed from supplicant. true means authenticated */
	bool fAuthRequired;
	uint8_t sessionId;
	uint8_t rsnIELen;
	uint8_t *prsnIE;
	uint8_t wapiIELen;
	uint8_t *pwapiIE;
	uint8_t addIELen;
	uint8_t *paddIE;
	union {
		tSirMicFailureInfo *pMICFailureInfo;
		tCsrRoamConnectedProfile *pConnectedProfile;
		tSirWPSPBCProbeReq *pWPSPBCProbeReq;
	} u;
	bool wmmEnabledSta;  /* set to true if WMM enabled STA */
	uint32_t dtimPeriod;
#ifdef FEATURE_WLAN_ESE
	bool isESEAssoc;
	tSirTsmIE tsmIe;
	uint32_t timestamp[2];
	uint16_t tsmRoamDelay;
	tSirEseBcnReportRsp *pEseBcnReportRsp;
#endif
	void *pRemainCtx;
	uint32_t roc_scan_id;
	uint32_t rxChan;
#ifdef FEATURE_WLAN_TDLS
	/*
	 * TDLS parameters to check whether TDLS
	 * and TDLS channel switch is allowed in the
	 * AP network
	 */
	uint8_t staType;
	bool tdls_prohibited;           /* per ExtCap in Assoc/Reassoc resp */
	bool tdls_chan_swit_prohibited; /* per ExtCap in Assoc/Reassoc resp */
#endif
	/* Required for indicating the frames to upper layer */
	uint32_t beaconLength;
	uint8_t *beaconPtr;
	uint32_t assocReqLength;
	uint8_t *assocReqPtr;
	int8_t rxRssi;
	tSirSmeDfsEventInd dfs_event;
	tSirChanChangeResponse *channelChangeRespEvent;
	/* Timing and fine Timing measurement capability clubbed together */
	uint8_t timingMeasCap;
#ifdef WLAN_FEATURE_ROAM_OFFLOAD
	uint8_t roamSynchInProgress;
	uint8_t synchAuthStatus;
	uint8_t kck[KCK_256BIT_KEY_LEN];
	uint8_t kck_len;
	uint8_t kek[SIR_KEK_KEY_LEN_FILS];
	uint8_t kek_len;
	uint32_t pmk_len;
	uint8_t pmk[SIR_PMK_LEN];
	uint8_t pmkid[SIR_PMKID_LEN];
	bool update_erp_next_seq_num;
	uint16_t next_erp_seq_num;
	uint8_t replay_ctr[SIR_REPLAY_CTR_LEN];
	uint8_t subnet_change_status;
#endif
	tSirSmeChanInfo chan_info;
	uint8_t target_channel;

#ifdef WLAN_FEATURE_NAN_DATAPATH
	union {
		struct ndi_create_rsp ndi_create_params;
		struct ndi_delete_rsp ndi_delete_params;
	} ndp;
#endif
	tDot11fIEHTCaps ht_caps;
	tDot11fIEVHTCaps vht_caps;
	bool he_caps_present;
	tDot11fIEhs20vendor_ie hs20vendor_ie;
	tDot11fIEVHTOperation vht_operation;
	tDot11fIEHTInfo ht_operation;
	bool reassoc;
	bool ampdu;
	bool sgi_enable;
	bool tx_stbc;
	bool rx_stbc;
	tSirMacHTChannelWidth ch_width;
	enum sir_sme_phy_mode mode;
	uint8_t max_supp_idx;
	uint8_t max_ext_idx;
	uint8_t max_mcs_idx;
	uint8_t rx_mcs_map;
	uint8_t tx_mcs_map;
	/* Extended capabilities of STA */
	uint8_t ecsa_capable;
	bool is_fils_connection;
#ifdef WLAN_FEATURE_FILS_SK
	uint16_t fils_seq_num;
	struct fils_join_rsp_params *fils_join_rsp;
#endif
	int rssi;
	int tx_rate;
	int rx_rate;
	tSirMacCapabilityInfo capability_info;
#ifdef WLAN_FEATURE_SAE
	struct sir_sae_info *sae_info;
#endif
	uint16_t roam_reason;
	struct wlan_ies *disconnect_ies;
};

typedef struct tagCsrFreqScanInfo {
	uint32_t nStartFreq;    /* in unit of MHz */
	uint32_t nEndFreq;      /* in unit of MHz */
	tSirScanType scanType;
} tCsrFreqScanInfo;

typedef struct sSirSmeAssocIndToUpperLayerCnf {
	uint16_t messageType;   /* eWNI_SME_ASSOC_CNF */
	uint16_t length;
	uint8_t sessionId;
	tSirResultCodes statusCode;
	tSirMacAddr bssId;      /* Self BSSID */
	tSirMacAddr peerMacAddr;
	uint16_t aid;
	tSirMacAddr alternateBssId;
	uint8_t alternateChannelId;
	uint8_t wmmEnabledSta;  /* set to true if WMM enabled STA */
	tSirRSNie rsnIE;        /* RSN IE received from peer */
	tSirWAPIie wapiIE;      /* WAPI IE received from peer */
	tSirAddie addIE;        /* this can be WSC and/or P2P IE */
	uint8_t reassocReq;     /* set to true if reassoc */
	/* Timing and fine Timing measurement capability clubbed together */
	uint8_t timingMeasCap;
	tSirSmeChanInfo chan_info;
	uint8_t target_channel;
	bool ampdu;
	bool sgi_enable;
	bool tx_stbc;
	tSirMacHTChannelWidth ch_width;
	enum sir_sme_phy_mode mode;
	bool rx_stbc;
	uint8_t max_supp_idx;
	uint8_t max_ext_idx;
	uint8_t max_mcs_idx;
	uint8_t rx_mcs_map;
	uint8_t tx_mcs_map;
	/* Extended capabilities of STA */
	uint8_t              ecsa_capable;

	uint32_t ies_len;
	uint8_t *ies;
	tDot11fIEHTCaps ht_caps;
	tDot11fIEVHTCaps vht_caps;
	tSirMacCapabilityInfo capability_info;
	bool he_caps_present;
} tSirSmeAssocIndToUpperLayerCnf, *tpSirSmeAssocIndToUpperLayerCnf;

typedef struct tagCsrSummaryStatsInfo {
	uint32_t snr;
	uint32_t rssi;
	uint32_t retry_cnt[4];
	uint32_t multiple_retry_cnt[4];
	uint32_t tx_frm_cnt[4];
	/* uint32_t num_rx_frm_crc_err; same as rx_error_cnt */
	/* uint32_t num_rx_frm_crc_ok; same as rx_frm_cnt */
	uint32_t rx_frm_cnt;
	uint32_t frm_dup_cnt;
	uint32_t fail_cnt[4];
	uint32_t rts_fail_cnt;
	uint32_t ack_fail_cnt;
	uint32_t rts_succ_cnt;
	uint32_t rx_discard_cnt;
	uint32_t rx_error_cnt;
	uint32_t tx_byte_cnt;

} tCsrSummaryStatsInfo;

typedef struct tagCsrGlobalClassAStatsInfo {
	uint8_t tx_nss;
	uint8_t rx_nss;
	uint32_t max_pwr;
	uint32_t tx_rate;
	uint32_t rx_rate;
	/* mcs index for HT20 and HT40 rates */
	uint32_t tx_mcs_index;
	uint32_t rx_mcs_index;
	uint32_t tx_mcs_rate_flags;
	uint32_t rx_mcs_rate_flags;
	/* to diff between HT20 & HT40 rates;short & long guard interval */
	uint32_t tx_rx_rate_flags;

} tCsrGlobalClassAStatsInfo;

typedef struct tagCsrGlobalClassDStatsInfo {
	uint32_t tx_uc_frm_cnt;
	uint32_t tx_mc_frm_cnt;
	uint32_t tx_bc_frm_cnt;
	uint32_t rx_uc_frm_cnt;
	uint32_t rx_mc_frm_cnt;
	uint32_t rx_bc_frm_cnt;
	uint32_t tx_uc_byte_cnt[4];
	uint32_t tx_mc_byte_cnt;
	uint32_t tx_bc_byte_cnt;
	uint32_t rx_uc_byte_cnt[4];
	uint32_t rx_mc_byte_cnt;
	uint32_t rx_bc_byte_cnt;
	uint32_t rx_byte_cnt;
	uint32_t num_rx_bytes_crc_ok;
	uint32_t rx_rate;

} tCsrGlobalClassDStatsInfo;

/**
 * struct csr_per_chain_rssi_stats_info - stores chain rssi
 * @rssi: array containing rssi for all chains
 * @peer_mac_addr: peer mac address
 */
struct csr_per_chain_rssi_stats_info {
	int8_t rssi[NUM_CHAINS_MAX];
	tSirMacAddr peer_mac_addr;
};

typedef struct tagCsrRoamSetKey {
	eCsrEncryptionType encType;
	tAniKeyDirection keyDirection;  /* Tx, Rx or Tx-and-Rx */
	struct qdf_mac_addr peerMac;    /* Peer MAC. ALL 1's for group key */
	uint8_t paeRole;        /* 0 for supplicant */
	uint8_t keyId;          /* Key index */
	uint16_t keyLength;     /* Number of bytes containing the key in pKey */
	uint8_t Key[CSR_MAX_KEY_LEN];
	uint8_t keyRsc[CSR_MAX_RSC_LEN];
} tCsrRoamSetKey;

typedef struct tagCsrRoamRemoveKey {
	eCsrEncryptionType encType;
	struct qdf_mac_addr peerMac; /* Peer MAC. ALL 1's for group key */
	uint8_t keyId;          /* key index */
} tCsrRoamRemoveKey;

#ifdef FEATURE_WLAN_TDLS

typedef struct tagCsrLinkEstablishParams {
	tSirMacAddr peerMac;
	uint8_t uapsdQueues;
	uint8_t maxSp;
	uint8_t isBufSta;
	uint8_t isOffChannelSupported;
	uint8_t isResponder;
	uint8_t supportedChannelsLen;
	uint8_t supportedChannels[SIR_MAC_MAX_SUPP_CHANNELS];
	uint8_t supportedOperClassesLen;
	uint8_t supportedOperClasses[REG_MAX_SUPP_OPER_CLASSES];
	uint8_t qos;
} tCsrTdlsLinkEstablishParams;

typedef struct tagCsrTdlsSendMgmt {
	tSirMacAddr peerMac;
	uint8_t frameType;
	uint8_t dialog;
	uint16_t statusCode;
	uint8_t responder;
	uint32_t peerCapability;
	uint8_t *buf;
	uint8_t len;
	enum wifi_traffic_ac ac;
} tCsrTdlsSendMgmt;
#endif

typedef void *tScanResultHandle;

typedef enum {
	REASSOC = 0,
	FASTREASSOC = 1,
	CONNECT_CMD_USERSPACE = 2,
} handoff_src;

typedef struct tagCsrHandoffRequest {
	struct qdf_mac_addr bssid;
	uint8_t channel;
	uint8_t src;   /* To check if its a REASSOC or a FASTREASSOC IOCTL */
} tCsrHandoffRequest;

#ifdef FEATURE_WLAN_ESE
typedef struct tagCsrEseBeaconReqParams {
	uint16_t measurementToken;
	uint8_t channel;
	uint8_t scanMode;
	uint16_t measurementDuration;
} tCsrEseBeaconReqParams, *tpCsrEseBeaconReqParams;

typedef struct tagCsrEseBeaconReq {
	uint8_t numBcnReqIe;
	tCsrEseBeaconReqParams bcnReq[SIR_ESE_MAX_MEAS_IE_REQS];
} tCsrEseBeaconReq, *tpCsrEseBeaconReq;
#endif /* FEATURE_WLAN_ESE */

struct csr_del_sta_params {
	struct qdf_mac_addr peerMacAddr;
	uint16_t reason_code;
	uint8_t subtype;
};

/**
 * struct wep_update_default_key_idx: wep default key index structure
 * @session_id: session ID for the connection session
 * @default_idx: default key index for wep
 *
 * structure includes sesssion id for connection and default key
 * index used for wep
 */
struct wep_update_default_key_idx {
	uint8_t session_id;
	uint8_t default_idx;
};

typedef QDF_STATUS (*csr_roam_complete_cb)(void *context,
					   struct csr_roam_info *param,
					   uint32_t roam_id,
					   eRoamCmdStatus roam_status,
					   eCsrRoamResult roam_result);
typedef QDF_STATUS (*csr_session_open_cb)(uint8_t session_id,
					  QDF_STATUS qdf_status);
typedef QDF_STATUS (*csr_session_close_cb)(uint8_t session_id);

#define CSR_IS_START_IBSS(pProfile) (eCSR_BSS_TYPE_START_IBSS == \
				     (pProfile)->BSSType)
#define CSR_IS_JOIN_TO_IBSS(pProfile) (eCSR_BSS_TYPE_IBSS == \
				       (pProfile)->BSSType)
#define CSR_IS_IBSS(pProfile) (CSR_IS_START_IBSS(pProfile) || \
			       CSR_IS_JOIN_TO_IBSS(pProfile))
#define CSR_IS_INFRASTRUCTURE(pProfile) (eCSR_BSS_TYPE_INFRASTRUCTURE == \
					 (pProfile)->BSSType)
#define CSR_IS_ANY_BSS_TYPE(pProfile) (eCSR_BSS_TYPE_ANY == \
				       (pProfile)->BSSType)
#define CSR_IS_INFRA_AP(pProfile) (eCSR_BSS_TYPE_INFRA_AP ==  \
				   (pProfile)->BSSType)
#ifdef WLAN_FEATURE_NAN_DATAPATH
#define CSR_IS_NDI(profile)  (eCSR_BSS_TYPE_NDI == (profile)->BSSType)
#else
#define CSR_IS_NDI(profile)  (false)
#endif
#define CSR_IS_CONN_INFRA_AP(pProfile)  (eCSR_BSS_TYPE_INFRA_AP == \
					 (pProfile)->BSSType)
#ifdef WLAN_FEATURE_NAN_DATAPATH
#define CSR_IS_CONN_NDI(profile)  (eCSR_BSS_TYPE_NDI == (profile)->BSSType)
#else
#define CSR_IS_CONN_NDI(profile)  (false)
#endif

#ifdef WLAN_FEATURE_SAE
#define CSR_IS_AUTH_TYPE_SAE(auth_type) \
	(eCSR_AUTH_TYPE_SAE == auth_type)

#define CSR_IS_AKM_FT_SAE(auth_type) \
	(eCSR_AUTH_TYPE_FT_SAE == (auth_type))

#define CSR_IS_FW_FT_SAE_SUPPORTED(fw_akm_bitmap) \
	(((fw_akm_bitmap) & (1 << AKM_FT_SAE)) ? true : false)

#define CSR_IS_FW_SAE_ROAM_SUPPORTED(fw_akm_bitmap) \
	(((fw_akm_bitmap) & (1 << AKM_SAE)) ? true : false)

#else
#define CSR_IS_AUTH_TYPE_SAE(auth_type) (false)

#define CSR_IS_AKM_FT_SAE(auth_type) (false)

#define CSR_IS_FW_FT_SAE_SUPPORTED(fw_akm_bitmap) (false)
#define CSR_IS_FW_SAE_ROAM_SUPPORTED(fw_akm_bitmap) (false)
#endif

#define CSR_IS_FW_OWE_ROAM_SUPPORTED(fw_akm_bitmap) \
	(((fw_akm_bitmap) & (1 << AKM_OWE)) ? true : false)

#define CSR_IS_AKM_FT_SUITEB_SHA384(auth_type) \
	(eCSR_AUTH_TYPE_FT_SUITEB_EAP_SHA384 == (auth_type))

#define CSR_IS_AKM_FILS(auth_type) \
	((eCSR_AUTH_TYPE_FILS_SHA256 == auth_type) || \
	 (eCSR_AUTH_TYPE_FILS_SHA384 == auth_type))

#define CSR_IS_AKM_FT_FILS(auth_type) \
	((eCSR_AUTH_TYPE_FT_FILS_SHA256 == (auth_type)) || \
	 (eCSR_AUTH_TYPE_FT_FILS_SHA384 == (auth_type)))

#define CSR_IS_FW_FT_SUITEB_SUPPORTED(fw_akm_bitmap) \
	(((fw_akm_bitmap) & (1 << AKM_FT_SUITEB_SHA384))  ? true : false)

#define CSR_IS_FW_FT_FILS_SUPPORTED(fw_akm_bitmap) \
	(((fw_akm_bitmap) & (1 << AKM_FT_FILS))  ? true : false)

QDF_STATUS csr_set_channels(tpAniSirGlobal pMac, tCsrConfigParam *pParam);

/* enum to string conversion for debug output */
const char *get_e_roam_cmd_status_str(eRoamCmdStatus val);
const char *get_e_csr_roam_result_str(eCsrRoamResult val);
const char *csr_phy_mode_str(eCsrPhyMode phy_mode);
QDF_STATUS csr_set_phy_mode(tHalHandle hHal, uint32_t phyMode,
			    enum band_info eBand, bool *pfRestartNeeded);
typedef void (*tCsrStatsCallback)(void *stats, void *pContext);
typedef void (*tCsrRssiCallback)(int8_t rssi, uint32_t staId, void *pContext);

#ifdef FEATURE_WLAN_ESE
typedef void (*tCsrTsmStatsCallback)(tAniTrafStrmMetrics tsmMetrics,
				     uint32_t staId, void *pContext);
#endif /* FEATURE_WLAN_ESE */
typedef void (*tCsrSnrCallback)(int8_t snr, uint32_t staId, void *pContext);

void csr_assoc_rej_free_rssi_disallow_list(struct sAniSirGlobal *mac);
/**
 * csr_roam_issue_ft_preauth_req() - Initiate Preauthentication request
 * @max_ctx: Global MAC context
 * @session_id: SME Session ID
 * @bss_desc: BSS descriptor
 *
 * Return: Success or Failure
 */
#ifdef WLAN_FEATURE_HOST_ROAM
QDF_STATUS csr_roam_issue_ft_preauth_req(tpAniSirGlobal mac_ctx,
					 uint32_t session_id,
					 tpSirBssDescription bss_desc);
#else
static inline
QDF_STATUS csr_roam_issue_ft_preauth_req(tpAniSirGlobal mac_ctx,
					 uint32_t session_id,
					 tpSirBssDescription bss_desc)
{
	return QDF_STATUS_E_NOSUPPORT;
}
#endif
QDF_STATUS csr_set_band(tHalHandle hHal, uint8_t sessionId,
			enum band_info eBand);
enum band_info csr_get_current_band(tHalHandle hHal);
typedef void (*csr_readyToSuspendCallback)(void *pContext, bool suspended);
#ifdef WLAN_FEATURE_EXTWOW_SUPPORT
typedef void (*csr_readyToExtWoWCallback)(void *pContext, bool status);
#endif
typedef void (*csr_link_status_callback)(uint8_t status, void *context);
#ifdef FEATURE_WLAN_TDLS
void csr_roam_fill_tdls_info(tpAniSirGlobal mac_ctx,
			     struct csr_roam_info *roam_info,
			     tpSirSmeJoinRsp join_rsp);
#else
static inline void csr_roam_fill_tdls_info(tpAniSirGlobal mac_ctx,
					   struct csr_roam_info *roam_info,
					   tpSirSmeJoinRsp join_rsp)
{}
#endif
void csr_packetdump_timer_stop(void);

/**
 * csr_get_channel_status() - get chan info via channel number
 * @mac: Pointer to Global MAC structure
 * @channel_id: channel id
 *
 * Return: chan status info
 */
struct lim_channel_status *
csr_get_channel_status(tpAniSirGlobal mac, uint32_t channel_id);

/**
 * csr_clear_channel_status() - clear chan info
 * @mac: Pointer to Global MAC structure
 *
 * Return: none
 */
void csr_clear_channel_status(tpAniSirGlobal mac);

typedef void (*csr_ani_callback)(int8_t *ani, void *context);

#ifdef WLAN_FEATURE_11W
/**
 * csr_update_pmf_cap_from_connected_profile() - Update pmf cap from profile
 * @profile: connected profile
 * @filter: scan filter
 *
 * Return: None
 */
void
csr_update_pmf_cap_from_connected_profile(tCsrRoamConnectedProfile *profile,
					  struct scan_filter *filter);
#else
static inline void
csr_update_pmf_cap_from_connected_profile(tCsrRoamConnectedProfile *profile,
					  struct scan_filter *filter)
{}
#endif
#endif
