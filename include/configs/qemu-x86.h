/*
 * Copyright (C) 2015, Bin Meng <bmeng.cn@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 * board/config.h - configuration options, board specific
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <configs/x86-common.h>

#define CONFIG_SYS_MONITOR_LEN		(1 << 20)

#define CONFIG_STD_DEVICES_SETTINGS	"stdin=serial,i8042-kbd\0" \
					"stdout=serial,vidconsole\0" \
					"stderr=serial,vidconsole\0"

/*
 * ATA/SATA support for QEMU x86 targets
 *   - Only legacy IDE controller is supported for QEMU '-M pc' target
 *   - AHCI controller is supported for QEMU '-M q35' target
 *
 * Default configuraion is to support the QEMU default x86 target
 * Undefine CONFIG_IDE to support q35 target
 */
#ifdef CONFIG_IDE
#define CONFIG_SYS_IDE_MAXBUS		2
#define CONFIG_SYS_IDE_MAXDEVICE	4
#define CONFIG_SYS_ATA_BASE_ADDR	0
#define CONFIG_SYS_ATA_DATA_OFFSET	0
#define CONFIG_SYS_ATA_REG_OFFSET	0
#define CONFIG_SYS_ATA_ALT_OFFSET	0
#define CONFIG_SYS_ATA_IDE0_OFFSET	0x1f0
#define CONFIG_SYS_ATA_IDE1_OFFSET	0x170
#define CONFIG_ATAPI

#undef CONFIG_SCSI_AHCI
#undef CONFIG_SCSI
#else
#define CONFIG_SCSI_DEV_LIST		\
	{PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH9_AHCI}
#endif

/* GPIO is not supported */
#undef CONFIG_INTEL_ICH6_GPIO

/* SPI is not supported */
#undef CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_IS_NOWHERE

#define CONFIG_SPL_FRAMEWORK

#define CONFIG_SPL_TEXT_BASE		0xfffd0000

#define BOOT_DEVICE_SPI			10

#define CONFIG_SPL_BOARD_LOAD_IMAGE
#define BOOT_DEVICE_BOARD		11

/*
 * UpdateHub configuration
 */

#define CONFIG_BOOTCOUNT_ENV

/* Environment */
#undef CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_IS_IN_FAT
#define FAT_ENV_INTERFACE       "ide"
#define FAT_ENV_DEVICE_AND_PART "0:1"
#define FAT_ENV_FILE            "u-boot.env"
#define CONFIG_FAT_WRITE

#define UPDATEHUB_LOAD_OS_A     "load ide 0:2 ${loadaddr} /boot/bzImage"
#define UPDATEHUB_FIND_ROOT_A   "part uuid ide 0:2 uuid"

#define UPDATEHUB_LOAD_OS_B     "load ide 0:3 ${loadaddr} /boot/bzImage"
#define UPDATEHUB_FIND_ROOT_B   "part uuid ide 0:3 uuid"

#define UPDATEHUB_BOOTARGS      "root=PARTUUID=${uuid} rootwait ro console=${consoledev}"
#define UPDATEHUB_BOOTCMD       "zboot ${loadaddr}"

#include <configs/updatehub-common.h>

#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS			\
	CONFIG_STD_DEVICES_SETTINGS			\
	"pciconfighost=1\0"				\
	"consoledev=ttyS0\0"				\
	CONFIG_OTHBOOTARGS				\
	UPDATEHUB_ENV

#endif	/* __CONFIG_H */
