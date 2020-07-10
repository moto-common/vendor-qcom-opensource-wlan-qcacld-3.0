/*
 * Copyright (c) 2011-2020 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * DOC: wlan_hdd_sysfs_get_stats.c
 *
 * implementation for creating sysfs file stats
 */

#include <wlan_hdd_includes.h>
#include <wlan_hdd_sysfs.h>
#include "osif_vdev_sync.h"
#include "sme_api.h"
#include "cdp_txrx_stats.h"
#include <wlan_hdd_sysfs_get_stats.h>

static void hdd_sysfs_get_stats(struct hdd_adapter *adapter, ssize_t *length,
				char *buffer, size_t buf_len)
{
	struct hdd_tx_rx_stats *stats = &adapter->hdd_stats.tx_rx_stats;
	uint32_t len = 0;
	uint32_t total_rx_pkt = 0, total_rx_dropped = 0;
	uint32_t total_rx_delv = 0, total_rx_refused = 0;
	int i = 0;
	struct hdd_context *hdd_ctx = adapter->hdd_ctx;

	for (; i < NUM_CPUS; i++) {
		total_rx_pkt += stats->rx_packets[i];
		total_rx_dropped += stats->rx_dropped[i];
		total_rx_delv += stats->rx_delivered[i];
		total_rx_refused += stats->rx_refused[i];
	}

	len = scnprintf(buffer, buf_len,
			"\nTransmit[%lu] - "
			"called %u, dropped %u orphan %u,"
			"\n[dropped]    BK %u, BE %u, VI %u, VO %u"
			"\n[classified] BK %u, BE %u, VI %u, VO %u"
			"\n\nReceive[%lu] - "
			"packets %u, dropped %u, unsolict_arp_n_mcast_drp %u, delivered %u, refused %u\n"
			"GRO - agg %u non-agg %u flush_skip %u low_tput_flush %u disabled(conc %u low-tput %u)\n",
			qdf_system_ticks(),
			stats->tx_called,
			stats->tx_dropped,
			stats->tx_orphaned,
			stats->tx_dropped_ac[SME_AC_BK],
			stats->tx_dropped_ac[SME_AC_BE],
			stats->tx_dropped_ac[SME_AC_VI],
			stats->tx_dropped_ac[SME_AC_VO],
			stats->tx_classified_ac[SME_AC_BK],
			stats->tx_classified_ac[SME_AC_BE],
			stats->tx_classified_ac[SME_AC_VI],
			stats->tx_classified_ac[SME_AC_VO],
			qdf_system_ticks(),
			total_rx_pkt, total_rx_dropped,
			qdf_atomic_read(&stats->rx_usolict_arp_n_mcast_drp),
			total_rx_delv,
			total_rx_refused,
			stats->rx_aggregated, stats->rx_non_aggregated,
			stats->rx_gro_flush_skip,
			stats->rx_gro_low_tput_flush,
			qdf_atomic_read(&hdd_ctx->disable_rx_ol_in_concurrency),
			qdf_atomic_read(&hdd_ctx->disable_rx_ol_in_low_tput));

	for (i = 0; i < NUM_CPUS; i++) {
		if (stats->rx_packets[i] == 0)
			continue;
		len += scnprintf(buffer + len, buf_len - len,
				 "Rx CPU[%d]:"
				 "packets %u, dropped %u, delivered %u, refused %u\n",
				 i, stats->rx_packets[i], stats->rx_dropped[i],
				 stats->rx_delivered[i], stats->rx_refused[i]);
	}

	len += scnprintf(buffer + len, buf_len - len,
		"\nTX_FLOW"
		"\nCurrent status: %s"
		"\ntx-flow timer start count %u"
		"\npause count %u, unpause count %u",
		(stats->is_txflow_paused == true ? "PAUSED" : "UNPAUSED"),
		stats->txflow_timer_cnt,
		stats->txflow_pause_cnt,
		stats->txflow_unpause_cnt);

	len += cdp_stats(cds_get_context(QDF_MODULE_ID_SOC),
			 adapter->vdev_id, &buffer[len], (buf_len - len));
	*length = len + 1;
}

static ssize_t
__hdd_sysfs_get_stats_show(struct net_device *net_dev, char *buf)
{
	struct hdd_adapter *adapter = netdev_priv(net_dev);
	struct hdd_context *hdd_ctx;
	int ret;
	ssize_t length = 0;

	if (hdd_validate_adapter(adapter)) {
		hdd_err_rl("adapter validate fail");
		return -EINVAL;
	}

	hdd_ctx = WLAN_HDD_GET_CTX(adapter);
	ret = wlan_hdd_validate_context(hdd_ctx);
	if (ret)
		return ret;

	if (!wlan_hdd_validate_modules_state(hdd_ctx))
		return -EINVAL;

	hdd_sysfs_get_stats(adapter, &length, buf, PAGE_SIZE);

	return length;
}

static ssize_t
hdd_sysfs_get_stats_show(struct device *dev,
			 struct device_attribute *attr,
			 char *buf)
{
	struct net_device *net_dev = container_of(dev, struct net_device, dev);
	struct osif_vdev_sync *vdev_sync;
	ssize_t err_size;

	err_size = osif_vdev_sync_op_start(net_dev, &vdev_sync);
	if (err_size)
		return err_size;

	err_size = __hdd_sysfs_get_stats_show(net_dev, buf);

	osif_vdev_sync_op_stop(vdev_sync);

	return err_size;
}

static DEVICE_ATTR(stats, 0440,
		   hdd_sysfs_get_stats_show, NULL);

int hdd_sysfs_get_stats_create(struct hdd_adapter *adapter)
{
	int error;

	error = device_create_file(&adapter->dev->dev,
				   &dev_attr_stats);
	if (error)
		hdd_err("could not create stats sysfs file");

	return error;
}

void hdd_sysfs_get_stats_destroy(struct hdd_adapter *adapter)
{
	device_remove_file(&adapter->dev->dev, &dev_attr_stats);
}