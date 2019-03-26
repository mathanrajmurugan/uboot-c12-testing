#ifndef _C12_REVISION_H_
#define _C12_REVISION_H_

#include <asm/arch/imx-regs.h>
#include <asm/arch/crm_regs.h>
#include <asm/gpio.h>
#include <common.h>
#include <malloc.h>
#include <errno.h>
#include <asm/io.h>
#include <miiphy.h>
#include <netdev.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm-generic/gpio.h>

#include <linux/libfdt.h>

void c12_fdt_ram_setup(void *blob, bd_t *bdev);
void c12_fdt_vpu_setup(void *blob, bd_t *bdev);
void c12_fdt_pcie_setup(void *blob, bd_t *bdev);
int c12_get_board_configuration (void);
int c12_get_hw_revision ( void );
int c12_get_q_ql ( void );
int c12_get_spi_canrtc ( void );
int c12_get_pcie ( void );


#define C12_IS_1GB	(!(c12_get_board_configuration() & 0x1) & !(c12_get_board_configuration() & 0x2))
#define C12_IS_2GB	(c12_get_board_configuration() & 0x1)
#define C12_IS_4GB      (c12_get_board_configuration() & 0x2)
#define C12_HAS_HDMI	(~(c12_get_board_configuration()) & 0x4)
#define C12_IS_QLITE	(~(c12_get_q_ql()) & 0x1)
#define C12_HAS_WILINK	((c12_get_board_configuration()) & 0x8)
#define C12_HAS_CANRTC  (~(c12_get_spi_canrtc()) & 0x1)
#define C12_FW_03	((gd->fwrev & 0xf) >= 0x3) ? 1 : 0
#define C12_HAS_PCIE	(~(c12_get_pcie()) & 0x1)

#endif
