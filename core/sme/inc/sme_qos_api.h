/*
 * Copyright (c) 2014-2016 The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
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
 * This file was originally distributed by Qualcomm Atheros, Inc.
 * under proprietary terms before Copyright ownership was assigned
 * to the Linux Foundation.
 */

#if !defined(__SME_QOSAPI_H)
#define __SME_QOSAPI_H

/**
 * \file  sme_qos_api.h
 *
 * \brief prototype for SME QoS APIs
 */

/*--------------------------------------------------------------------------
  Include Files
  ------------------------------------------------------------------------*/
#include "qdf_lock.h"
#include "qdf_trace.h"
#include "qdf_mem.h"
#include "qdf_types.h"
#include "ani_global.h"
#include "sir_api.h"

/*--------------------------------------------------------------------------
  Pre-processor Definitions
  ------------------------------------------------------------------------*/
#define SME_QOS_UAPSD_VO      0x01
#define SME_QOS_UAPSD_VI      0x02
#define SME_QOS_UAPSD_BE      0x08
#define SME_QOS_UAPSD_BK      0x04

/*---------------------------------------------------------------------------
  Enumeration of the various QoS status types that would be reported to HDD
  ---------------------------------------------------------------------------*/
typedef enum {
	/*
	 * async: once PE notifies successful TSPEC negotiation, or CSR notifies
	 * for successful reassoc, notifies HDD with current QoS Params
	 */
	SME_QOS_STATUS_SETUP_SUCCESS_IND = 0,
	/* sync: only when App asked for APSD & it's already set with ACM = 0 */
	SME_QOS_STATUS_SETUP_SUCCESS_APSD_SET_ALREADY,
	/* sync or async: in case of async notify HDD with current QoS Params */
	SME_QOS_STATUS_SETUP_FAILURE_RSP,
	/* sync */
	SME_QOS_STATUS_SETUP_INVALID_PARAMS_RSP,
	/* sync: AP doesn't support QoS (WMM) */
	SME_QOS_STATUS_SETUP_NOT_QOS_AP_RSP,
	/* sync: either req has been sent down to PE or just buffered in SME */
	SME_QOS_STATUS_SETUP_REQ_PENDING_RSP,
	/*
	 * async: in case of flow aggregation, if the new TSPEC negotiation
	 * is successful, OR, notify existing flows that TSPEC is modified with
	 * current QoS Params
	 */
	SME_QOS_STATUS_SETUP_MODIFIED_IND,
	/* sync: no APSD asked for & ACM = 0 */
	SME_QOS_STATUS_SETUP_SUCCESS_NO_ACM_NO_APSD_RSP,
	/*
	 * async: In case of UAPSD, once PE notifies successful TSPEC
	 * negotiation, or CSR notifies for successful reassoc to SME-QoS,
	 * notify HDD if PMC can't put the module in UAPSD mode right away
	 * (QDF_STATUS_PMC_PENDING)
	 */
	SME_QOS_STATUS_SETUP_SUCCESS_IND_APSD_PENDING,
	/*
	 * async: In case of UAPSD, once PE notifies successful TSPEC
	 * negotiation, or CSR notifies for successful reassoc to SME-QoS,
	 * notify HDD if PMC can't put the module in UAPSD mode at all
	 * (QDF_STATUS_E_FAILURE)
	 */
	SME_QOS_STATUS_SETUP_SUCCESS_IND_APSD_SET_FAILED,
	/*
	 * sync: req has been sent down to PE in case of delts or addts
	 * for remain flows, OR if the AC doesn't have APSD or ACM
	 * async: once the downgrade req for QoS params is successful
	 */
	SME_QOS_STATUS_RELEASE_SUCCESS_RSP = 100,
	/* sync or async: in case of async notify HDD with current QoS Param */
	SME_QOS_STATUS_RELEASE_FAILURE_RSP,
	/* async: AP sent DELTS indication */
	SME_QOS_STATUS_RELEASE_QOS_LOST_IND,
	/*
	 * sync: an addts req has been sent down to PE to downgrade the
	 * QoS params or just buffered in SME
	 */
	SME_QOS_STATUS_RELEASE_REQ_PENDING_RSP,
	/* sync */
	SME_QOS_STATUS_RELEASE_INVALID_PARAMS_RSP,
	/*
	 * async: for QoS modify request if modification is successful,
	 * notifies HDD with current QoS Params
	 */
	SME_QOS_STATUS_MODIFY_SETUP_SUCCESS_IND = 200,
	/* sync: only when App asked for APSD & it's already set with ACM = 0 */
	SME_QOS_STATUS_MODIFY_SETUP_SUCCESS_APSD_SET_ALREADY,
	/* sync or async: in case of async notify HDD with current QoS Param */
	SME_QOS_STATUS_MODIFY_SETUP_FAILURE_RSP,
	/* sync: either req has been sent down to PE or just buffered in SME */
	SME_QOS_STATUS_MODIFY_SETUP_PENDING_RSP,
	/* sync: no APSD asked for & ACM = 0 */
	SME_QOS_STATUS_MODIFY_SETUP_SUCCESS_NO_ACM_NO_APSD_RSP,
	/* sync */
	SME_QOS_STATUS_MODIFY_SETUP_INVALID_PARAMS_RSP,
	/*
	 * async: In case of UAPSD, once PE notifies successful TSPEC
	 * negotiation or CSR notifies for successful reassoc to SME-QoS,
	 * notify HDD if PMC can't put the module in UAPSD mode right away
	 * (QDF_STATUS_PMC_PENDING)
	 */
	SME_QOS_STATUS_MODIFY_SETUP_SUCCESS_IND_APSD_PENDING,
	/*
	 * async: In case of UAPSD, once PE notifies successful TSPEC
	 * negotiation, or CSR notifies for successful reassoc to SME-QoS,
	 * notify HDD if PMC can't put the module in UAPSD mode at all
	 * (QDF_STATUS_E_FAILURE)
	 */
	SME_QOS_STATUS_MODIFY_SETUP_SUCCESS_IND_APSD_SET_FAILED,
	/* sync: STA is handing off to a new AP */
	SME_QOS_STATUS_HANDING_OFF = 300,
	/* async:powersave mode changed by PMC from UAPSD to Full power */
	SME_QOS_STATUS_OUT_OF_APSD_POWER_MODE_IND = 400,
	/* async:powersave mode changed by PMC from Full power to UAPSD */
	SME_QOS_STATUS_INTO_APSD_POWER_MODE_IND,

} sme_QosStatusType;

/*---------------------------------------------------------------------------
  Enumeration of the various User priority (UP) types

  From 802.1D/802.11e/WMM specifications (all refer to same table)
  ---------------------------------------------------------------------------*/
typedef enum {
	SME_QOS_WMM_UP_BE = 0,
	SME_QOS_WMM_UP_BK = 1,
	SME_QOS_WMM_UP_RESV = 2,        /* Reserved */
	SME_QOS_WMM_UP_EE = 3,
	SME_QOS_WMM_UP_CL = 4,
	SME_QOS_WMM_UP_VI = 5,
	SME_QOS_WMM_UP_VO = 6,
	SME_QOS_WMM_UP_NC = 7,
	SME_QOS_WMM_UP_MAX
} sme_QosWmmUpType;

/*---------------------------------------------------------------------------
  Enumeration of the various TSPEC directions

  From 802.11e/WMM specifications
  ---------------------------------------------------------------------------*/

typedef enum {
	SME_QOS_WMM_TS_DIR_UPLINK = 0,
	SME_QOS_WMM_TS_DIR_DOWNLINK = 1,
	SME_QOS_WMM_TS_DIR_RESV = 2,    /* Reserved */
	SME_QOS_WMM_TS_DIR_BOTH = 3,
} sme_QosWmmDirType;

/*---------------------------------------------------------------------------
  Enumeration of the various TSPEC ack policies.

  From 802.11 WMM specification
  ---------------------------------------------------------------------------*/

typedef enum {
	SME_QOS_WMM_TS_ACK_POLICY_NORMAL_ACK = 0,
	SME_QOS_WMM_TS_ACK_POLICY_RESV1 = 1,
	SME_QOS_WMM_TS_ACK_POLICY_RESV2 = 2,    /* Reserved */
	SME_QOS_WMM_TS_ACK_POLICY_HT_IMMEDIATE_BLOCK_ACK = 3,

} sme_QosWmmAckPolicyType;

/*---------------------------------------------------------------------------
  TS Info field in the WMM TSPEC

  See suggestive values above
  ---------------------------------------------------------------------------*/
typedef struct {
	uint8_t burst_size_defn;
	sme_QosWmmAckPolicyType ack_policy;
	sme_QosWmmUpType up;    /* User priority */
	uint8_t psb;            /* power-save bit */
	sme_QosWmmDirType direction;    /* Direction */
	uint8_t tid;            /* TID : To be filled up by SME-QoS */
} sme_QosWmmTsInfoType;

/*---------------------------------------------------------------------------
  The WMM TSPEC Element (from the WMM spec)
  ---------------------------------------------------------------------------*/
typedef struct {
	sme_QosWmmTsInfoType ts_info;
	uint16_t nominal_msdu_size;
	uint16_t maximum_msdu_size;
	uint32_t min_service_interval;
	uint32_t max_service_interval;
	uint32_t inactivity_interval;
	uint32_t suspension_interval;
	uint32_t svc_start_time;
	uint32_t min_data_rate;
	uint32_t mean_data_rate;
	uint32_t peak_data_rate;
	uint32_t max_burst_size;
	uint32_t delay_bound;
	uint32_t min_phy_rate;
	uint16_t surplus_bw_allowance;
	uint16_t medium_time;
} sme_QosWmmTspecInfo;

/*--------------------------------------------------------------------------
  External APIs
  ------------------------------------------------------------------------*/
typedef QDF_STATUS (*sme_QosCallback)(tHalHandle hHal, void *HDDcontext,
		sme_QosWmmTspecInfo *pCurrentQoSInfo,
		sme_QosStatusType status, uint32_t QosFlowID);
sme_QosStatusType sme_qos_setup_req(tHalHandle hHal, uint32_t sessionId,
		sme_QosWmmTspecInfo *pQoSInfo,
		sme_QosCallback QoSCallback, void *HDDcontext,
		sme_QosWmmUpType UPType, uint32_t *pQosFlowID);
sme_QosStatusType sme_qos_modify_req(tHalHandle hHal,
		sme_QosWmmTspecInfo *pQoSInfo, uint32_t QosFlowID);
sme_QosStatusType sme_qos_release_req(tHalHandle hHal, uint8_t session_id,
				      uint32_t QosFlowID);
bool sme_qos_is_ts_info_ack_policy_valid(tpAniSirGlobal pMac,
		sme_QosWmmTspecInfo *pQoSInfo, uint8_t sessionId);
void sme_qos_update_hand_off(uint8_t sessionId, bool updateHandOff);
QDF_STATUS sme_update_dsc_pto_up_mapping(tHalHandle hHal,
		sme_QosWmmUpType *dscpmapping, uint8_t sessionId);

QDF_STATUS sme_offload_qos_process_out_of_uapsd_mode(tpAniSirGlobal mac_ctx,
		uint32_t session_id);
QDF_STATUS sme_offload_qos_process_into_uapsd_mode(tpAniSirGlobal mac_ctx,
		uint32_t session_id);


#endif /* #if !defined( __SME_QOSAPI_H ) */
