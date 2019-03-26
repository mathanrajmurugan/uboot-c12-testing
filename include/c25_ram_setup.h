#ifndef _C25_REVISION_H_
#define _C25_REVISION_H_

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

void c25_fdt_ram_setup(void *blob, bd_t *bdev);
void c25_fdt_vpu_setup(void *blob, bd_t *bdev);
int c25_get_board_configuration (void);


#define C25_IS_1GB	(!(c25_get_board_configuration() & 0x1) & !(c25_get_board_configuration() & 0x2))
#define C25_IS_2GB	(c25_get_board_configuration() & 0x1)
#define C25_IS_4GB      (c25_get_board_configuration() & 0x2)
#define C25_IS_8GB      ((c25_get_board_configuration() & 0x1) & (c25_get_board_configuration() & 0x2)) 
#define C25_HAS_HDMI	!(c25_get_board_configuration() & 0x4)
#define C25_IS_QLITE	C25_IS_1GB
#define C25_HAS_WILINK	!(c25_get_board_configuration() & 0x10)

#endif
