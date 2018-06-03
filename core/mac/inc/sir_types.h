/*
 * Copyright (c) 2011-2016,2018 The Linux Foundation. All rights reserved.
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
 *
 * This file sir_types.h contains the common types
 *
 * Author:    V. K. Kandarpa
 * Date:      04/12/2002
 */

#ifndef __SIR_TYPES_H
#define __SIR_TYPES_H

#include <qdf_types.h>


/** ------------------------------------------------------------------------ *

    \typedef tHalHandle

    \brief Handle to the HAL.  The HAL handle is returned by the HAL after it
    is opened (by calling halOpen).

    ------------------------------------------------------------------------- */
typedef void *tHalHandle;

/**
 * typedef hdd_handle_t - HDD Handle
 *
 * Handle to the HDD.  The HDD handle is given to the UMAC from the
 * HDD on Open.  The HDD handle is an input to all HDD/PAL function
 * calls and represents an opaque handle to the HDD instance that is
 * tied to the UMAC instance
 *
 * The HDD must be able to derive it's internal instance structure
 * pointer through this handle.
 */
/*
 * NOTE WELL: struct opaque_hdd_handle is not defined anywhere. This
 * reference is used to help ensure that a hdd_handle_t is never used
 * where a different handle type is expected
 */
struct opaque_hdd_handle;
typedef struct opaque_hdd_handle *hdd_handle_t;

/* ********************************************** *
*                                                *
*     SIRIUS ERROR Codes / Return Codes          *
*                                                *
* ********************************************** */

/* / Return status type */
typedef enum eSirRetStatus {
	eSIR_SUCCESS,
	eSIR_FAILURE,
	eSIR_MEM_ALLOC_FAILED,
	eSIR_HAL_STA_DOES_NOT_EXIST,
	eSIR_HAL_INPUT_INVALID,
	eSIR_LIM_IGNORE_BEACON,
	eSIR_LIM_INVALID_STA,
	eSIR_LIM_MAX_STA_REACHED_ERROR,
	eSIR_CFG_INVALID_ID,
	eSIR_CFG_INVALID_LEN,
	eSIR_IGNORE_IE,
} tSirRetStatus;

#define IS_SIR_STATUS_SUCCESS(status) (eSIR_SUCCESS == status)
typedef enum {
	HAL_STOP_TYPE_SYS_RESET,
	HAL_STOP_TYPE_SYS_DEEP_SLEEP,
	HAL_STOP_TYPE_RF_KILL,
} tHalStopType;

#define HAL_NUM_ASSOC_STA           32
#define HAL_NUM_STA                 41

#define STACFG_MAX_TC               8

#endif /* __SIR_TYPES_H */
