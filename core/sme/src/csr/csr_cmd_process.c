/*
 * Copyright (c) 2011-2017 The Linux Foundation. All rights reserved.
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

/*
 * DOC: csr_cmd_process.c
 *
 * Implementation for processing various commands.
 */
#include "ani_global.h"
#include "csr_inside_api.h"
#include "sme_inside.h"
#include "mac_trace.h"

/**
 * csr_msg_processor() - To process all csr msg
 * @mac_ctx: mac context
 * @msg_buf: message buffer
 *
 * This routine will handle all the message for csr to process
 *
 * Return: QDF_STATUS
 */
QDF_STATUS csr_msg_processor(tpAniSirGlobal mac_ctx, void *msg_buf)
{
	QDF_STATUS status = QDF_STATUS_SUCCESS;
	tSirSmeRsp *sme_rsp = (tSirSmeRsp *) msg_buf;
	uint8_t session_id = sme_rsp->sessionId;
	eCsrRoamState cur_state = mac_ctx->roam.curState[session_id];

	sme_debug("msg %d[0x%04X] recvd in curstate %s & substate %s id(%d)",
		sme_rsp->messageType, sme_rsp->messageType,
		mac_trace_getcsr_roam_state(cur_state),
		mac_trace_getcsr_roam_sub_state(
			mac_ctx->roam.curSubState[session_id]),
		session_id);

	/* Process the message based on the state of the roaming states... */
	switch (cur_state) {
	case eCSR_ROAMING_STATE_JOINED:
		/* are we in joined state */
		csr_roam_joined_state_msg_processor(mac_ctx, msg_buf);
		break;
	case eCSR_ROAMING_STATE_JOINING:
		/* are we in roaming states */
		csr_roaming_state_msg_processor(mac_ctx, msg_buf);
		break;

	default:
		if (sme_rsp->messageType ==
		    eWNI_SME_GET_STATISTICS_RSP) {
			csr_roam_joined_state_msg_processor(mac_ctx,
							    msg_buf);
			break;
		}

		/*
		 * For all other messages, we ignore it
		 * To work-around an issue where checking for set/remove
		 * key base on connection state is no longer workable
		 * due to failure or finding the condition meets both
		 * SAP and infra/IBSS requirement.
		 */
		if (eWNI_SME_SETCONTEXT_RSP == sme_rsp->messageType) {
			sme_warn("handling msg 0x%X CSR state is %d",
				sme_rsp->messageType, cur_state);
			csr_roam_check_for_link_status_change(mac_ctx,
					sme_rsp);
		} else if (eWNI_SME_GET_RSSI_REQ ==
				sme_rsp->messageType) {
			tAniGetRssiReq *pGetRssiReq =
				(tAniGetRssiReq *) msg_buf;
			if (NULL == pGetRssiReq->rssiCallback) {
				sme_err("rssiCallback is NULL");
				return status;
			}
			((tCsrRssiCallback)(pGetRssiReq->rssiCallback))(
					pGetRssiReq->lastRSSI,
					pGetRssiReq->staId,
					pGetRssiReq->pDevContext);
		} else {
			sme_err("Message 0x%04X is not handled by CSR state is %d session Id %d",
				sme_rsp->messageType, cur_state,
				session_id);

			if (eWNI_SME_FT_PRE_AUTH_RSP ==
					sme_rsp->messageType) {
				sme_err("Dequeue eSmeCommandRoam command with reason eCsrPerformPreauth");
				csr_dequeue_roam_command(mac_ctx,
					eCsrPerformPreauth, session_id);
			} else if (eWNI_SME_REASSOC_RSP ==
					sme_rsp->messageType) {
				sme_err("Dequeue eSmeCommandRoam command with reason eCsrSmeIssuedFTReassoc");
				csr_dequeue_roam_command(mac_ctx,
					eCsrSmeIssuedFTReassoc,
					session_id);
			}
		}
		break;
	} /* switch */
	return status;
}

bool csr_check_ps_ready(void *pv)
{
	tpAniSirGlobal pMac = PMAC_STRUCT(pv);

	if (pMac->roam.sPendingCommands < 0) {
		QDF_ASSERT(pMac->roam.sPendingCommands >= 0);
		return 0;
	}
	return pMac->roam.sPendingCommands == 0;
}

bool csr_check_ps_offload_ready(void *pv, uint32_t sessionId)
{
	tpAniSirGlobal pMac = PMAC_STRUCT(pv);

	QDF_ASSERT(pMac->roam.sPendingCommands >= 0);
	return pMac->roam.sPendingCommands == 0;
}

