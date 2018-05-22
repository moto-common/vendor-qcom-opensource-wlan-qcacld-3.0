/*
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
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
 * DOC : wlan_hdd_twt.h
 *
 * WLAN Host Device Driver file for TWT (Target Wake Time) support.
 *
 */

#if !defined(WLAN_HDD_TWT_H)
#define WLAN_HDD_TWT_H

struct hdd_context;
struct wma_tgt_cfg;

#ifdef WLAN_FEATURE_TWT
/**
 * hdd_twt_print_ini_config() - Print TWT INI config items
 * @hdd_ctx: HDD Context
 *
 * Return: None
 */
void hdd_twt_print_ini_config(struct hdd_context *hdd_ctx);

/**
 * hdd_update_tgt_twt_cap() - Update TWT target capabilities
 * @hdd_ctx: HDD Context
 * @cfg: Pointer to target configuration
 *
 * Return: None
 */
void hdd_update_tgt_twt_cap(struct hdd_context *hdd_ctx,
			    struct wma_tgt_cfg *cfg);

#else
static inline void hdd_twt_print_ini_config(struct hdd_context *hdd_ctx)
{
}

static inline void hdd_update_tgt_twt_cap(struct hdd_context *hdd_ctx,
					  struct wma_tgt_cfg *cfg)
{
}

#endif
#endif /* if !defined(WLAN_HDD_TWT_H)*/
