/*
 * (C) Copyright 2011 Linaro
 * Ryan Harkin, <ryan.harkin@linaro.org>
 *
 * Configuration for Versatile Express. Parts were derived from other ARM
 *   configurations.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __VEXPRESS_CA9X4_H
#define __VEXPRESS_CA9X4_H

#define CONFIG_VEXPRESS_ORIGINAL_MEMORY_MAP
#include "vexpress_common.h"

#define CONFIG_RBTREE
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_MTD_CONCAT
#define CONFIG_FLASH_CFI_MTD
#define CONFIG_LZO

#ifdef CONFIG_SYS_MALLOC_LEN
#undef CONFIG_SYS_MALLOC_LEN
#define CONFIG_SYS_MALLOC_LEN (8 * 1024 * 1024)
#endif

#define MTDIDS_DEFAULT		"nor2=40000000.flash"
#define MTDPARTS_DEFAULT	"mtdparts=40000000.flash:"					\
  "1m(u-boot)ro," \
  "1m(u-boot-env)," \
  "-(ubi)"

#undef CONFIG_ENV_ADDR
#undef CONFIG_ENV_OFFSET
#define CONFIG_ENV_ADDR	(CONFIG_SYS_FLASH_BASE0 + CONFIG_ENV_OFFSET)
#define CONFIG_ENV_OFFSET 0x100000

#define CONFIG_ENV_ADDR_REDUND (CONFIG_SYS_FLASH_BASE0 + CONFIG_ENV_OFFSET_REDUND)
#define CONFIG_ENV_OFFSET_REDUND (CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)

/*
 * UpdateHub configuration
 */

#define CONFIG_BOOTCOUNT_ENV

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
