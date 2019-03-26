/*
 * 
 *
 * Reading C25 Board type
 *
 * marco.sandrelli@seco.com
 *
 *
 *
 */

#include <common.h>
#include <malloc.h>
#include <errno.h>
#include <asm/io.h>
#include <miiphy.h>
#include <netdev.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm-generic/gpio.h>
#include <fsl_esdhc.h>
#include <mmc.h>
#include <asm/arch/imx8mq_pins.h>
#include <asm/arch/sys_proto.h>
#include <asm/mach-imx/gpio.h>
#include <c25_ram_setup.h>

#define PULLUP_PAD_CTRL  (PAD_CTL_PUE)

/* ____________________________________________________________________________
  |                                                                            |
  |                                  C25 REVISION                              |
  |____________________________________________________________________________|
*/


#define C25_IOMUX_REG(x)        ((x))
#define C25_PADCTRL_REG(x)      ((x))
#define C25_GDIR_REG_IN(x,n)    writel((readl(x + 0x4)) & ~(1<<n), x + 0x4 )
#define C25_DR_REG(x,n)         (readl(x) & (1<<n))

#define cfg_0			0
#define cfg_1			1
#define cfg_2			2
#define cfg_3			3

#define GPIO3_PAD_BASE		0x30220000
#define GPIO_CFG_0		16
#define GPIO_CFG_1              18
#define GPIO_CFG_2              17
#define GPIO_CFG_3		15

struct sizes {
	u32 s0;
	u32 s1;
};

DECLARE_GLOBAL_DATA_PTR;

iomux_v3_cfg_t const board_conf_pads[] = {

        /* RAM CONFIG */
        IMX8MQ_PAD_NAND_READY_B__GPIO3_IO16 | MUX_PAD_CTRL(PULLUP_PAD_CTRL),   /* cfg_0 */
        IMX8MQ_PAD_NAND_WP_B__GPIO3_IO18 | MUX_PAD_CTRL(PULLUP_PAD_CTRL),      /* cfg_1 */
        /* Undefined */
        IMX8MQ_PAD_NAND_WE_B__GPIO3_IO17 | MUX_PAD_CTRL(PULLUP_PAD_CTRL),      /* cfg_2 */
	IMX8MQ_PAD_NAND_RE_B__GPIO3_IO15 | MUX_PAD_CTRL(PULLUP_PAD_CTRL),      /* cfg_3 */	

};

int c25_get_board_configuration ( void ) {

        ulong value = 0;

	/* 
         *
         * CFG code is composed in this way:
         * cfg_0 -> first bit   X 
         * cfg_1 -> second bit  X
         * cfg_2 -> third bit   X
         *  
         */
	
	imx_iomux_v3_setup_multiple_pads(board_conf_pads, ARRAY_SIZE(board_conf_pads));

	/* Mux as Input */
	C25_GDIR_REG_IN(GPIO3_PAD_BASE,GPIO_CFG_0);
	C25_GDIR_REG_IN(GPIO3_PAD_BASE,GPIO_CFG_1);
	C25_GDIR_REG_IN(GPIO3_PAD_BASE,GPIO_CFG_2);
	C25_GDIR_REG_IN(GPIO3_PAD_BASE,GPIO_CFG_3);

	/* Read Conf value */
	value = (C25_DR_REG(GPIO3_PAD_BASE,GPIO_CFG_0) >> abs(GPIO_CFG_0 - cfg_0)) | 
		(C25_DR_REG(GPIO3_PAD_BASE,GPIO_CFG_1) >> abs(GPIO_CFG_1 - cfg_1)) | 
		(C25_DR_REG(GPIO3_PAD_BASE,GPIO_CFG_2) >> abs(GPIO_CFG_2 - cfg_2)) |
		(C25_DR_REG(GPIO3_PAD_BASE,GPIO_CFG_3) >> abs(GPIO_CFG_3 - cfg_3));

        return value;

}

/* Substitute in the fdt kernel file the right dram setup */
void c25_fdt_ram_setup(void *blob, bd_t *bdev) { 

	int offset, ret;
	struct sizes ssize;
	

	printf("Overlay dts /reserved-memory/linux,cma/: size = ");
	offset = fdt_path_offset(blob, "/reserved-memory/linux,cma/");
        if (offset < 0) {
                printf("ERROR: find node /: %s.\n", fdt_strerror(offset));
                return;
        }
        if(C25_IS_1GB) {
		ssize.s0 = cpu_to_fdt32(0x0);
		ssize.s1 = cpu_to_fdt32(0x1e000000);
		printf("<0x0 0x1e000000>\n");
	}
        if(C25_IS_2GB) {
		ssize.s0 = cpu_to_fdt32(0x0);
                ssize.s1 = cpu_to_fdt32(0x2c000000);
		printf("<0x0 0x2c000000>\n");
	}

        ret = fdt_setprop(blob, offset, "size", &ssize, sizeof(ssize));
        if (ret < 0)
                printf("ERROR: could not update revision property %s.\n",
                        fdt_strerror(ret));

	return;
}

void c25_fdt_vpu_setup(void *blob, bd_t *bdev) {


	int offset, ret;
	char status[10];	

	printf("Overlay dts: cpu is Quadlite, disabling vpu support\n");
	offset = fdt_path_offset(blob, "/vpu@38300000/");
	if (offset < 0) {
                printf("ERROR: find node /: %s.\n", fdt_strerror(offset));
                return;
        }

	sprintf(status, "%s","disabled" );
	ret = fdt_setprop(blob, offset, "status", status, sizeof(status));
        if (ret < 0)
                printf("ERROR: could not update revision property %s.\n",
                        fdt_strerror(ret));

	return;
}
