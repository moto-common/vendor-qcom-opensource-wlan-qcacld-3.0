/*
 * Copyright (c) 2012-2021 The Linux Foundation. All rights reserved.
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

/*
 * This file wni_api.h contains message definitions exported by
 * Sirius software modules.
 * NOTE: See projects/sirius/include/sir_api.h for structure
 * definitions of the host/FW messages.
 *
 * Author:        Chandra Modumudi
 * Date:          04/11/2002
 * History:-
 * Date           Modified by    Modification Information
 * --------------------------------------------------------------------
 */

#ifndef __WNI_API_H
#define __WNI_API_H

#include "sir_api.h"

#define SIR_SME_MSG_TYPES_BEGIN        (SIR_SME_MODULE_ID << 8)

enum eWniMsgTypes {
	eWNI_SME_MSG_TYPES_BEGIN = SIR_SME_MSG_TYPES_BEGIN,
	eWNI_SME_SYS_READY_IND = SIR_SME_MSG_TYPES_BEGIN + 1,
	eWNI_SME_JOIN_REQ = SIR_SME_MSG_TYPES_BEGIN + 2,
	eWNI_SME_JOIN_RSP = SIR_SME_MSG_TYPES_BEGIN + 3,
	eWNI_SME_SETCONTEXT_RSP = SIR_SME_MSG_TYPES_BEGIN + 5,
	eWNI_SME_REASSOC_REQ = SIR_SME_MSG_TYPES_BEGIN + 6,
	eWNI_SME_REASSOC_RSP = SIR_SME_MSG_TYPES_BEGIN + 7,
	eWNI_SME_DISASSOC_REQ = SIR_SME_MSG_TYPES_BEGIN + 8,
	eWNI_SME_DISASSOC_RSP = SIR_SME_MSG_TYPES_BEGIN + 9,
	eWNI_SME_DISASSOC_IND = SIR_SME_MSG_TYPES_BEGIN + 10,
	eWNI_SME_DISASSOC_CNF = SIR_SME_MSG_TYPES_BEGIN + 11,
	eWNI_SME_DEAUTH_REQ = SIR_SME_MSG_TYPES_BEGIN + 12,
	eWNI_SME_DEAUTH_RSP = SIR_SME_MSG_TYPES_BEGIN + 13,
	eWNI_SME_DEAUTH_IND = SIR_SME_MSG_TYPES_BEGIN + 14,
	eWNI_SME_DISCONNECT_DONE_IND = SIR_SME_MSG_TYPES_BEGIN + 15,
	eWNI_SME_WM_STATUS_CHANGE_NTF = SIR_SME_MSG_TYPES_BEGIN + 16,
	eWNI_SME_START_BSS_REQ = SIR_SME_MSG_TYPES_BEGIN + 19,
	eWNI_SME_START_BSS_RSP = SIR_SME_MSG_TYPES_BEGIN + 20,
	eWNI_SME_ASSOC_IND = SIR_SME_MSG_TYPES_BEGIN + 21,
	eWNI_SME_ASSOC_CNF = SIR_SME_MSG_TYPES_BEGIN + 22,
	eWNI_SME_SWITCH_CHL_IND = SIR_SME_MSG_TYPES_BEGIN + 23,
	eWNI_SME_STOP_BSS_REQ = SIR_SME_MSG_TYPES_BEGIN + 24,
	eWNI_SME_STOP_BSS_RSP = SIR_SME_MSG_TYPES_BEGIN + 25,
	eWNI_SME_DEAUTH_CNF = SIR_SME_MSG_TYPES_BEGIN + 26,
	eWNI_SME_MIC_FAILURE_IND = SIR_SME_MSG_TYPES_BEGIN + 27,
	eWNI_SME_ADDTS_REQ = SIR_SME_MSG_TYPES_BEGIN + 28,
	eWNI_SME_ADDTS_RSP = SIR_SME_MSG_TYPES_BEGIN + 29,
	eWNI_SME_DELTS_REQ = SIR_SME_MSG_TYPES_BEGIN + 30,
	eWNI_SME_DELTS_RSP = SIR_SME_MSG_TYPES_BEGIN + 31,
	eWNI_SME_DELTS_IND = SIR_SME_MSG_TYPES_BEGIN + 32,
	eWNI_SME_MSCS_REQ = SIR_SME_MSG_TYPES_BEGIN + 33,
	/*
	 * unused SIR_SME_MSG_TYPES_BEGIN + 34 to
	 * to SIR_SME_MSG_TYPES_BEGIN + 35
	 */
	eWNI_SME_ASSOC_IND_UPPER_LAYER = SIR_SME_MSG_TYPES_BEGIN + 36,
	eWNI_SME_WPS_PBC_PROBE_REQ_IND = SIR_SME_MSG_TYPES_BEGIN + 37,
	eWNI_SME_UPPER_LAYER_ASSOC_CNF = SIR_SME_MSG_TYPES_BEGIN + 38,
	eWNI_SME_SESSION_UPDATE_PARAM = SIR_SME_MSG_TYPES_BEGIN + 39,
	eWNI_SME_CHNG_MCC_BEACON_INTERVAL = SIR_SME_MSG_TYPES_BEGIN + 40,
	eWNI_SME_GET_SNR_REQ = SIR_SME_MSG_TYPES_BEGIN + 41,

	eWNI_SME_RRM_MSG_TYPE_BEGIN = SIR_SME_MSG_TYPES_BEGIN + 42,

	eWNI_SME_NEIGHBOR_REPORT_REQ_IND = SIR_SME_MSG_TYPES_BEGIN + 43,
	eWNI_SME_NEIGHBOR_REPORT_IND = SIR_SME_MSG_TYPES_BEGIN + 44,
	eWNI_SME_BEACON_REPORT_REQ_IND = SIR_SME_MSG_TYPES_BEGIN + 45,
	eWNI_SME_BEACON_REPORT_RESP_XMIT_IND = SIR_SME_MSG_TYPES_BEGIN + 46,

	/* unused SIR_SME_MSG_TYPES_BEGIN + 47, */
	/* unused SIR_SME_MSG_TYPES_BEGIN + 48, */

	eWNI_SME_FT_PRE_AUTH_REQ = SIR_SME_MSG_TYPES_BEGIN + 49,
	eWNI_SME_FT_PRE_AUTH_RSP = SIR_SME_MSG_TYPES_BEGIN + 50,
	eWNI_SME_FT_AGGR_QOS_REQ = SIR_SME_MSG_TYPES_BEGIN + 52,
	eWNI_SME_FT_AGGR_QOS_RSP = SIR_SME_MSG_TYPES_BEGIN + 53,

#if defined FEATURE_WLAN_ESE
	eWNI_SME_ESE_ADJACENT_AP_REPORT = SIR_SME_MSG_TYPES_BEGIN + 54,
#endif

	eWNI_SME_REGISTER_MGMT_FRAME_REQ = SIR_SME_MSG_TYPES_BEGIN + 55,
	eWNI_SME_GENERIC_CHANGE_COUNTRY_CODE = SIR_SME_MSG_TYPES_BEGIN + 56,
	eWNI_SME_MAX_ASSOC_EXCEEDED = SIR_SME_MSG_TYPES_BEGIN + 57,
#ifdef FEATURE_WLAN_TDLS
	eWNI_SME_TDLS_SEND_MGMT_REQ = SIR_SME_MSG_TYPES_BEGIN + 58,
	eWNI_SME_TDLS_SEND_MGMT_RSP = SIR_SME_MSG_TYPES_BEGIN + 59,
	eWNI_SME_TDLS_ADD_STA_REQ = SIR_SME_MSG_TYPES_BEGIN + 60,
	eWNI_SME_TDLS_ADD_STA_RSP = SIR_SME_MSG_TYPES_BEGIN + 61,
	eWNI_SME_TDLS_DEL_STA_REQ = SIR_SME_MSG_TYPES_BEGIN + 62,
	eWNI_SME_TDLS_DEL_STA_RSP = SIR_SME_MSG_TYPES_BEGIN + 63,
	eWNI_SME_TDLS_DEL_STA_IND = SIR_SME_MSG_TYPES_BEGIN + 64,
	eWNI_SME_TDLS_DEL_ALL_PEER_IND = SIR_SME_MSG_TYPES_BEGIN + 65,
	eWNI_SME_MGMT_FRM_TX_COMPLETION_IND = SIR_SME_MSG_TYPES_BEGIN + 66,
	eWNI_SME_TDLS_LINK_ESTABLISH_REQ = SIR_SME_MSG_TYPES_BEGIN + 67,
	eWNI_SME_TDLS_LINK_ESTABLISH_RSP = SIR_SME_MSG_TYPES_BEGIN + 68,
	eWNI_SME_TDLS_SHOULD_DISCOVER = SIR_SME_MSG_TYPES_BEGIN + 69,
	eWNI_SME_TDLS_SHOULD_TEARDOWN = SIR_SME_MSG_TYPES_BEGIN + 70,
	eWNI_SME_TDLS_PEER_DISCONNECTED = SIR_SME_MSG_TYPES_BEGIN + 71,
#endif
	/* NOTE: If you are planning to add more mesages, please make sure that */
	/* SIR_LIM_ITC_MSG_TYPES_BEGIN is moved appropriately. It is set as */
	/* SIR_LIM_MSG_TYPES_BEGIN+0xB0 = 12B0 (which means max of 176 messages and */
	/* eWNI_SME_TDLS_DEL_STA_RSP = 175. */
	/* Should fix above issue to enable TDLS_INTERNAL */
	eWNI_SME_RESET_AP_CAPS_CHANGED = SIR_SME_MSG_TYPES_BEGIN + 73,
#ifdef WLAN_FEATURE_11W
	eWNI_SME_UNPROT_MGMT_FRM_IND = SIR_SME_MSG_TYPES_BEGIN + 74,
#endif
#ifdef WLAN_FEATURE_GTK_OFFLOAD
	eWNI_PMC_GTK_OFFLOAD_GETINFO_RSP = SIR_SME_MSG_TYPES_BEGIN + 75,
#endif /* WLAN_FEATURE_GTK_OFFLOAD */
	/*ROAM candidate indication from FW */
	eWNI_SME_CANDIDATE_FOUND_IND = SIR_SME_MSG_TYPES_BEGIN + 76,
	/*upper layer requested handoff to driver in STA mode */
	eWNI_SME_HANDOFF_REQ = SIR_SME_MSG_TYPES_BEGIN + 77,
	/*Fwd the LFR scan offload rsp from FW to SME */
	eWNI_SME_ROAM_SCAN_OFFLOAD_RSP = SIR_SME_MSG_TYPES_BEGIN + 78,
	eWNI_SME_GET_TSM_STATS_REQ = SIR_SME_MSG_TYPES_BEGIN + 80,
	eWNI_SME_GET_TSM_STATS_RSP = SIR_SME_MSG_TYPES_BEGIN + 81,
	eWNI_SME_TSM_IE_IND = SIR_SME_MSG_TYPES_BEGIN + 82,

	/* DFS EVENTS */
	/* RADAR found indication from DFS */
	eWNI_SME_DFS_RADAR_FOUND = SIR_SME_MSG_TYPES_BEGIN + 83,
	/* Channel Change Request from SAP */
	eWNI_SME_CHANNEL_CHANGE_REQ = SIR_SME_MSG_TYPES_BEGIN + 84,
	/* Channel Change Response from WMA */
	eWNI_SME_CHANNEL_CHANGE_RSP = SIR_SME_MSG_TYPES_BEGIN + 85,
	/* Start Beacon Transmission. */
	eWNI_SME_START_BEACON_REQ = SIR_SME_MSG_TYPES_BEGIN + 86,
	/* Transmit CSA IE in beacons */
	eWNI_SME_DFS_BEACON_CHAN_SW_IE_REQ = SIR_SME_MSG_TYPES_BEGIN + 87,
	/* To indicate completion of CSA IE */
	eWNI_SME_DFS_CSAIE_TX_COMPLETE_IND = SIR_SME_MSG_TYPES_BEGIN + 88,
	/* update in beacons/probe rsp */
	eWNI_SME_STATS_EXT_EVENT = SIR_SME_MSG_TYPES_BEGIN + 89,
	/* Unused SIR_SME_MSG_TYPES_BEGIN + 90 */
	eWNI_SME_GET_PEER_INFO_EXT_IND = SIR_SME_MSG_TYPES_BEGIN + 91,
	/* indicates Additional IE from hdd to PE */
	eWNI_SME_UPDATE_ADDITIONAL_IES = SIR_SME_MSG_TYPES_BEGIN + 93,
	/* To indicate IE modify from hdd to PE */
	eWNI_SME_MODIFY_ADDITIONAL_IES = SIR_SME_MSG_TYPES_BEGIN + 94,
#ifdef FEATURE_WLAN_AUTO_SHUTDOWN
	eWNI_SME_AUTO_SHUTDOWN_IND = SIR_SME_MSG_TYPES_BEGIN + 95,
#endif
#ifdef QCA_HT_2040_COEX
	eWNI_SME_SET_HT_2040_MODE = SIR_SME_MSG_TYPES_BEGIN + 96,
#endif
#ifdef WLAN_FEATURE_ROAM_OFFLOAD
	/* Hand Off Failure Ind from WMA to SME */
	eWNI_SME_HO_FAIL_IND = SIR_SME_MSG_TYPES_BEGIN + 97,
#endif
#ifdef WLAN_FEATURE_NAN
	eWNI_SME_NAN_EVENT = SIR_SME_MSG_TYPES_BEGIN + 98,
#endif
	eWNI_SME_LINK_STATUS_IND = SIR_SME_MSG_TYPES_BEGIN + 99,
#ifdef WLAN_FEATURE_EXTWOW_SUPPORT
	eWNI_SME_READY_TO_EXTWOW_IND = SIR_SME_MSG_TYPES_BEGIN + 100,
#endif
	eWNI_SME_MSG_GET_TEMPERATURE_IND = SIR_SME_MSG_TYPES_BEGIN + 101,
	eWNI_SME_SNR_IND = SIR_SME_MSG_TYPES_BEGIN + 102,
#ifdef FEATURE_WLAN_EXTSCAN
	eWNI_SME_EXTSCAN_FULL_SCAN_RESULT_IND = SIR_SME_MSG_TYPES_BEGIN + 103,
	eWNI_SME_EPNO_NETWORK_FOUND_IND = SIR_SME_MSG_TYPES_BEGIN + 104,
#endif
	eWNI_SME_SET_HW_MODE_REQ = SIR_SME_MSG_TYPES_BEGIN + 105,
	eWNI_SME_SET_HW_MODE_RESP = SIR_SME_MSG_TYPES_BEGIN + 106,
	eWNI_SME_HW_MODE_TRANS_IND = SIR_SME_MSG_TYPES_BEGIN + 107,
	eWNI_SME_NSS_UPDATE_REQ = SIR_SME_MSG_TYPES_BEGIN + 108,
	eWNI_SME_NSS_UPDATE_RSP = SIR_SME_MSG_TYPES_BEGIN + 109,
	eWNI_SME_OCB_SET_CONFIG_RSP = SIR_SME_MSG_TYPES_BEGIN + 110,
	eWNI_SME_OCB_GET_TSF_TIMER_RSP = SIR_SME_MSG_TYPES_BEGIN + 111,
	eWNI_SME_DCC_GET_STATS_RSP = SIR_SME_MSG_TYPES_BEGIN + 112,
	eWNI_SME_DCC_UPDATE_NDL_RSP = SIR_SME_MSG_TYPES_BEGIN + 113,
	eWNI_SME_DCC_STATS_EVENT = SIR_SME_MSG_TYPES_BEGIN + 114,
	eWNI_SME_SET_DUAL_MAC_CFG_REQ = SIR_SME_MSG_TYPES_BEGIN + 115,
	eWNI_SME_SET_DUAL_MAC_CFG_RESP = SIR_SME_MSG_TYPES_BEGIN + 116,
	eWNI_SME_SET_THERMAL_LEVEL_IND = SIR_SME_MSG_TYPES_BEGIN + 117,
	eWNI_SME_SET_IE_REQ = SIR_SME_MSG_TYPES_BEGIN + 118,
	eWNI_SME_EXT_CHANGE_CHANNEL = SIR_SME_MSG_TYPES_BEGIN + 119,
	eWNI_SME_EXT_CHANGE_CHANNEL_IND = SIR_SME_MSG_TYPES_BEGIN + 120,
	eWNI_SME_REGISTER_MGMT_FRAME_CB = SIR_SME_MSG_TYPES_BEGIN + 121,
	/* START and UPDATE OBSS SCAN Indication*/
	eWNI_SME_HT40_OBSS_SCAN_IND = SIR_SME_MSG_TYPES_BEGIN + 122,
	eWNI_SME_SET_ANTENNA_MODE_REQ = SIR_SME_MSG_TYPES_BEGIN + 123,
	eWNI_SME_SET_ANTENNA_MODE_RESP = SIR_SME_MSG_TYPES_BEGIN + 124,
	eWNI_SME_TSF_EVENT = SIR_SME_MSG_TYPES_BEGIN + 125,
	eWNI_SME_MON_INIT_SESSION = SIR_SME_MSG_TYPES_BEGIN + 126,
	eWNI_SME_PDEV_SET_HT_VHT_IE = SIR_SME_MSG_TYPES_BEGIN + 127,
	eWNI_SME_SET_VDEV_IES_PER_BAND = SIR_SME_MSG_TYPES_BEGIN + 128,
	eWNI_SME_SEND_DISASSOC_FRAME = SIR_SME_MSG_TYPES_BEGIN + 129,
	eWNI_SME_UPDATE_ACCESS_POLICY_VENDOR_IE = SIR_SME_MSG_TYPES_BEGIN + 130,
	eWNI_SME_DEFAULT_SCAN_IE = SIR_SME_MSG_TYPES_BEGIN + 131,
	eWNI_SME_ROAM_INVOKE = SIR_SME_MSG_TYPES_BEGIN + 132,
#ifndef ROAM_OFFLOAD_V1
	eWNI_SME_ROAM_SCAN_OFFLOAD_REQ = SIR_SME_MSG_TYPES_BEGIN + 133,
#endif
	eWNI_SME_LOST_LINK_INFO_IND = SIR_SME_MSG_TYPES_BEGIN + 134,
	eWNI_SME_DEL_ALL_TDLS_PEERS = SIR_SME_MSG_TYPES_BEGIN + 135,
	eWNI_SME_RSO_CMD_STATUS_IND = SIR_SME_MSG_TYPES_BEGIN + 136,
	eWMI_SME_LL_STATS_IND = SIR_SME_MSG_TYPES_BEGIN + 137,
	eWNI_SME_DFS_CAC_COMPLETE = SIR_SME_MSG_TYPES_BEGIN + 138,
	eWNI_SME_UPDATE_CONFIG = SIR_SME_MSG_TYPES_BEGIN + 139,
	eWNI_SME_BT_ACTIVITY_INFO_IND = SIR_SME_MSG_TYPES_BEGIN + 140,
	eWNI_SME_SET_HE_BSS_COLOR = SIR_SME_MSG_TYPES_BEGIN + 141,
	eWNI_SME_TRIGGER_SAE = SIR_SME_MSG_TYPES_BEGIN + 142,
	eWNI_SME_SEND_MGMT_FRAME_TX = SIR_SME_MSG_TYPES_BEGIN + 143,
	eWNI_SME_SEND_SAE_MSG = SIR_SME_MSG_TYPES_BEGIN + 144,
	eWNI_SME_SET_ADDBA_ACCEPT = SIR_SME_MSG_TYPES_BEGIN + 145,
	eWNI_SME_UPDATE_EDCA_PROFILE = SIR_SME_MSG_TYPES_BEGIN + 146,
	WNI_SME_UPDATE_MU_EDCA_PARAMS = SIR_SME_MSG_TYPES_BEGIN + 147,
	eWNI_SME_CSA_RESTART_REQ = SIR_SME_MSG_TYPES_BEGIN + 148,
	eWNI_SME_CSA_RESTART_RSP = SIR_SME_MSG_TYPES_BEGIN + 149,
	WNI_SME_CFG_ACTION_FRM_HE_TB_PPDU = SIR_SME_MSG_TYPES_BEGIN + 150,
	/* To indicate Hidden ssid start complition to upper layer */
	eWNI_SME_HIDDEN_SSID_RESTART_RSP = SIR_SME_MSG_TYPES_BEGIN + 151,
	eWNI_SME_FW_STATUS_IND = SIR_SME_MSG_TYPES_BEGIN + 152,
	eWNI_SME_STA_CSA_CONTINUE_REQ = SIR_SME_MSG_TYPES_BEGIN + 153,
	/* 154 unused */
	eWNI_SME_ANTENNA_ISOLATION_RSP = SIR_SME_MSG_TYPES_BEGIN + 155,
	eWNI_SME_MON_DEINIT_SESSION = SIR_SME_MSG_TYPES_BEGIN + 156,
	eWNI_SME_VDEV_DELETE_RSP = SIR_SME_MSG_TYPES_BEGIN + 157,
#ifndef ROAM_OFFLOAD_V1
	eWNI_SME_ROAM_INIT_PARAM = SIR_SME_MSG_TYPES_BEGIN + 158,
	eWNI_SME_ROAM_SEND_PER_REQ = SIR_SME_MSG_TYPES_BEGIN + 159,
#endif
	eWNI_SME_GET_ROAM_SCAN_CH_LIST_EVENT =
				SIR_SME_MSG_TYPES_BEGIN + 160,
	eWNI_SME_MONITOR_MODE_VDEV_UP = SIR_SME_MSG_TYPES_BEGIN + 161,
	eWNI_SME_UPDATE_SESSION_EDCA_TXQ_PARAMS = SIR_SME_MSG_TYPES_BEGIN + 162,
	eWNI_SME_ROAM_SEND_SET_PCL_REQ = SIR_SME_MSG_TYPES_BEGIN + 163,
#ifndef ROAM_OFFLOAD_V1
	eWNI_SME_ROAM_DISABLE_CFG = SIR_SME_MSG_TYPES_BEGIN + 164,
#endif
	eWNI_SME_TWT_ADD_DIALOG_EVENT = SIR_SME_MSG_TYPES_BEGIN + 165,
	eWNI_SME_TWT_DEL_DIALOG_EVENT = SIR_SME_MSG_TYPES_BEGIN + 166,
	eWNI_SME_TWT_PAUSE_DIALOG_EVENT = SIR_SME_MSG_TYPES_BEGIN + 167,
	eWNI_SME_TWT_RESUME_DIALOG_EVENT = SIR_SME_MSG_TYPES_BEGIN + 168,
	eWNI_SME_TWT_NUDGE_DIALOG_EVENT = SIR_SME_MSG_TYPES_BEGIN + 169,
	eWNI_SME_TWT_NOTIFY_EVENT = SIR_SME_MSG_TYPES_BEGIN + 170,
	eWNI_SME_MSG_TYPES_END = SIR_SME_MSG_TYPES_BEGIN + 171
};

typedef struct sAniCfgTxRateCtrs {
/* add the rate counters here */
	unsigned long TxFrames_1Mbps;
	unsigned long TxFrames_2Mbps;
	unsigned long TxFrames_5_5Mbps;
	unsigned long TxFrames_6Mbps;
	unsigned long TxFrames_9Mbps;
	unsigned long TxFrames_11Mbps;
	unsigned long TxFrames_12Mbps;
	unsigned long TxFrames_18Mbps;
	unsigned long TxFrames_24Mbps;
	unsigned long TxFrames_36Mbps;
	unsigned long TxFrames_48Mbps;
	unsigned long TxFrames_54Mbps;
	unsigned long TxFrames_72Mbps;
	unsigned long TxFrames_96Mbps;
	unsigned long TxFrames_108Mbps;

} tAniCfgTxRateCtrs, *tpAniCfgTxRateCtrs;
#endif /* __WNI_API_H */
