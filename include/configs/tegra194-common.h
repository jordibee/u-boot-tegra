#ifndef _TEGRA194_COMMON_H_
#define _TEGRA194_COMMON_H_

#include "tegra-common.h"

/* Cortex-A57 uses a cache line size of 64 bytes */
#define CONFIG_SYS_CACHELINE_SIZE	64

/*
 * NS16550 Configuration
 */
#define V_NS16550_CLK		408000000	/* 408MHz (pllp_out0) */

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */

#define CONFIG_SYS_TEXT_BASE	0x80080000

/* Generic Interrupt Controller */
#define CONFIG_GICV2

/*
 * Memory layout for where various images get loaded by boot scripts:
 *
 * scriptaddr can be pretty much anywhere that doesn't conflict with something
 *   else. Put it above BOOTMAPSZ to eliminate conflicts.
 *
 * pxefile_addr_r can be pretty much anywhere that doesn't conflict with
 *   something else. Put it above BOOTMAPSZ to eliminate conflicts.
 *
 * kernel_addr_r must be within the first 128M of RAM in order for the
 *   kernel's CONFIG_AUTO_ZRELADDR option to work. Since the kernel will
 *   decompress itself to 0x8000 after the start of RAM, kernel_addr_r
 *   should not overlap that area, or the kernel will have to copy itself
 *   somewhere else before decompression. Similarly, the address of any other
 *   data passed to the kernel shouldn't overlap the start of RAM. Pushing
 *   this up to 16M allows for a sizable kernel to be decompressed below the
 *   compressed load address.
 *
 * fdt_addr_r simply shouldn't overlap anything else. Choosing 32M allows for
 *   the compressed kernel to be up to 16M too.
 *
 * ramdisk_addr_r simply shouldn't overlap anything else. Choosing 33M allows
 *   for the FDT/DTB to be up to 1M, which is hopefully plenty.
 */
#define CONFIG_LOADADDR 0x80080000
#define MEM_LAYOUT_ENV_SETTINGS \
	"scriptaddr=0x90000000\0" \
	"pxefile_addr_r=0x90100000\0" \
	"kernel_addr_r=" __stringify(CONFIG_LOADADDR) "\0" \
	"fdt_addr_r=0x82000000\0" \
	"ramdisk_addr_r=0x82100000\0" \
	"fdt_copy_node_paths=" \
		"/chosen/plugin-manager:" \
		"/chosen/reset:" \
		"/memory@80000000\0" \
	"fdt_copy_prop_paths=" \
		"/bpmp/carveout-start:" \
		"/bpmp/carveout-size:" \
		"/chosen/nvidia,bluetooth-mac:" \
		"/chosen/nvidia,ether-mac:" \
		"/chosen/nvidia,wifi-mac:" \
		"/chosen/ecid:" \
		"/chosen/linux,initrd-start:" \
		"/chosen/linux,initrd-end:" \
		"/serial-number\0"

#endif
