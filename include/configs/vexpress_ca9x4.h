/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2011 Linaro
 * Ryan Harkin, <ryan.harkin@linaro.org>
 *
 * Configuration for Versatile Express. Parts were derived from other ARM
 *   configurations.
 */

#ifndef __VEXPRESS_CA9X4_H
#define __VEXPRESS_CA9X4_H

#define CONFIG_VEXPRESS_ORIGINAL_MEMORY_MAP
#include "vexpress_common.h"

#define CONFIG_MTD_CONCAT

#ifdef CONFIG_SYS_MALLOC_LEN
#undef CONFIG_SYS_MALLOC_LEN
#define CONFIG_SYS_MALLOC_LEN (8 * 1024 * 1024)
#endif

/*
 * UpdateHub configuration
 */

#define UPDATEHUB_LOAD_OS_A     "ubifsload ${kernel_addr_r} /boot/zImage; ubifsload ${fdt_addr_r} /boot/vexpress-v2p-ca9.dtb"
#define UPDATEHUB_FIND_ROOT_A   "ubi part ubi; ubifsmount ubi0:rootfsa; setenv ubiroot ubi0:rootfsa"

#define UPDATEHUB_LOAD_OS_B     UPDATEHUB_LOAD_OS_A
#define UPDATEHUB_FIND_ROOT_B   "ubi part ubi; ubifsmount ubi0:rootfsb; setenv ubiroot ubi0:rootfsb"

#define UPDATEHUB_BOOTARGS      "${mtdparts} ubi.mtd=2 root=${ubiroot} rootfstype=ubifs ubi.fm_autoconvert=1 rootwait ro console=${console}"
#define UPDATEHUB_BOOTCMD       "bootz ${kernel_addr_r} - ${fdt_addr_r}"

#include <configs/updatehub-common.h>

#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS			\
	CONFIG_PLATFORM_ENV_SETTINGS \
            BOOTENV \
	"kernel_addr_r=0x60100000\0" \
	"fdt_addr_r=0x60000000\0" \
	"console=ttyAMA0,38400n8\0" \
	UPDATEHUB_ENV

#endif /* VEXPRESS_CA9X4_H */
