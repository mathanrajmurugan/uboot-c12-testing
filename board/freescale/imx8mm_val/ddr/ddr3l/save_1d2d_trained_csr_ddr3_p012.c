/*
 * Copyright 2018 NXP
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#include <common.h>
#include <errno.h>
#include <asm/io.h>
#include <asm/arch/ddr.h>
#include <asm/arch/clock.h>
#include "../ddr.h"
#include "ddr3_define.h"

static const unsigned int save_csr[] = {
	0x200b2,
	0x1200b2,
	0x2200b2,
	0x200cb,
#ifdef RUN_ON_SILICON
	0x10043,
	0x110043,
	0x210043,
	0x10143,
	0x110143,
	0x210143,
	0x11043,
	0x111043,
	0x211043,
	0x11143,
	0x111143,
	0x211143,
	0x12043,
	0x112043,
	0x212043,
	0x12143,
	0x112143,
	0x212143,
	0x13043,
	0x113043,
	0x213043,
	0x13143,
	0x113143,
	0x213143,
	0x80,
	0x100080,
	0x200080,
	0x1080,
	0x101080,
	0x201080,
	0x2080,
	0x102080,
	0x202080,
	0x3080,
	0x103080,
	0x203080,
	0x4080,
	0x104080,
	0x204080,
	0x5080,
	0x105080,
	0x205080,
	0x6080,
	0x106080,
	0x206080,
	0x7080,
	0x107080,
	0x207080,
	0x8080,
	0x108080,
	0x208080,
	0x9080,
	0x109080,
	0x209080,
	0x10080,
	0x110080,
	0x210080,
	0x10180,
	0x110180,
	0x210180,
	0x10081,
	0x110081,
	0x210081,
	0x10181,
	0x110181,
	0x210181,
	0x10082,
	0x110082,
	0x210082,
	0x10182,
	0x110182,
	0x210182,
	0x10083,
	0x110083,
	0x210083,
	0x10183,
	0x110183,
	0x210183,
	0x11080,
	0x111080,
	0x211080,
	0x11180,
	0x111180,
	0x211180,
	0x11081,
	0x111081,
	0x211081,
	0x11181,
	0x111181,
	0x211181,
	0x11082,
	0x111082,
	0x211082,
	0x11182,
	0x111182,
	0x211182,
	0x11083,
	0x111083,
	0x211083,
	0x11183,
	0x111183,
	0x211183,
	0x12080,
	0x112080,
	0x212080,
	0x12180,
	0x112180,
	0x212180,
	0x12081,
	0x112081,
	0x212081,
	0x12181,
	0x112181,
	0x212181,
	0x12082,
	0x112082,
	0x212082,
	0x12182,
	0x112182,
	0x212182,
	0x12083,
	0x112083,
	0x212083,
	0x12183,
	0x112183,
	0x212183,
	0x13080,
	0x113080,
	0x213080,
	0x13180,
	0x113180,
	0x213180,
	0x13081,
	0x113081,
	0x213081,
	0x13181,
	0x113181,
	0x213181,
	0x13082,
	0x113082,
	0x213082,
	0x13182,
	0x113182,
	0x213182,
	0x13083,
	0x113083,
	0x213083,
	0x13183,
	0x113183,
	0x213183,
	0x100d0,
	0x1100d0,
	0x2100d0,
	0x101d0,
	0x1101d0,
	0x2101d0,
	0x100d1,
	0x1100d1,
	0x2100d1,
	0x101d1,
	0x1101d1,
	0x2101d1,
	0x100d2,
	0x1100d2,
	0x2100d2,
	0x101d2,
	0x1101d2,
	0x2101d2,
	0x100d3,
	0x1100d3,
	0x2100d3,
	0x101d3,
	0x1101d3,
	0x2101d3,
	0x110d0,
	0x1110d0,
	0x2110d0,
	0x111d0,
	0x1111d0,
	0x2111d0,
	0x110d1,
	0x1110d1,
	0x2110d1,
	0x111d1,
	0x1111d1,
	0x2111d1,
	0x110d2,
	0x1110d2,
	0x2110d2,
	0x111d2,
	0x1111d2,
	0x2111d2,
	0x110d3,
	0x1110d3,
	0x2110d3,
	0x111d3,
	0x1111d3,
	0x2111d3,
	0x120d0,
	0x1120d0,
	0x2120d0,
	0x121d0,
	0x1121d0,
	0x2121d0,
	0x120d1,
	0x1120d1,
	0x2120d1,
	0x121d1,
	0x1121d1,
	0x2121d1,
	0x120d2,
	0x1120d2,
	0x2120d2,
	0x121d2,
	0x1121d2,
	0x2121d2,
	0x120d3,
	0x1120d3,
	0x2120d3,
	0x121d3,
	0x1121d3,
	0x2121d3,
	0x130d0,
	0x1130d0,
	0x2130d0,
	0x131d0,
	0x1131d0,
	0x2131d0,
	0x130d1,
	0x1130d1,
	0x2130d1,
	0x131d1,
	0x1131d1,
	0x2131d1,
	0x130d2,
	0x1130d2,
	0x2130d2,
	0x131d2,
	0x1131d2,
	0x2131d2,
	0x130d3,
	0x1130d3,
	0x2130d3,
	0x131d3,
	0x1131d3,
	0x2131d3,
	0x10068,
	0x10168,
	0x10268,
	0x10368,
	0x10468,
	0x10568,
	0x10668,
	0x10768,
	0x10868,
	0x10069,
	0x10169,
	0x10269,
	0x10369,
	0x10469,
	0x10569,
	0x10669,
	0x10769,
	0x10869,
	0x1006a,
	0x1016a,
	0x1026a,
	0x1036a,
	0x1046a,
	0x1056a,
	0x1066a,
	0x1076a,
	0x1086a,
	0x1006b,
	0x1016b,
	0x1026b,
	0x1036b,
	0x1046b,
	0x1056b,
	0x1066b,
	0x1076b,
	0x1086b,
	0x11068,
	0x11168,
	0x11268,
	0x11368,
	0x11468,
	0x11568,
	0x11668,
	0x11768,
	0x11868,
	0x11069,
	0x11169,
	0x11269,
	0x11369,
	0x11469,
	0x11569,
	0x11669,
	0x11769,
	0x11869,
	0x1106a,
	0x1116a,
	0x1126a,
	0x1136a,
	0x1146a,
	0x1156a,
	0x1166a,
	0x1176a,
	0x1186a,
	0x1106b,
	0x1116b,
	0x1126b,
	0x1136b,
	0x1146b,
	0x1156b,
	0x1166b,
	0x1176b,
	0x1186b,
	0x12068,
	0x12168,
	0x12268,
	0x12368,
	0x12468,
	0x12568,
	0x12668,
	0x12768,
	0x12868,
	0x12069,
	0x12169,
	0x12269,
	0x12369,
	0x12469,
	0x12569,
	0x12669,
	0x12769,
	0x12869,
	0x1206a,
	0x1216a,
	0x1226a,
	0x1236a,
	0x1246a,
	0x1256a,
	0x1266a,
	0x1276a,
	0x1286a,
	0x1206b,
	0x1216b,
	0x1226b,
	0x1236b,
	0x1246b,
	0x1256b,
	0x1266b,
	0x1276b,
	0x1286b,
	0x13068,
	0x13168,
	0x13268,
	0x13368,
	0x13468,
	0x13568,
	0x13668,
	0x13768,
	0x13868,
	0x13069,
	0x13169,
	0x13269,
	0x13369,
	0x13469,
	0x13569,
	0x13669,
	0x13769,
	0x13869,
	0x1306a,
	0x1316a,
	0x1326a,
	0x1336a,
	0x1346a,
	0x1356a,
	0x1366a,
	0x1376a,
	0x1386a,
	0x1306b,
	0x1316b,
	0x1326b,
	0x1336b,
	0x1346b,
	0x1356b,
	0x1366b,
	0x1376b,
	0x1386b,
	0x1008c,
	0x11008c,
	0x21008c,
	0x1018c,
	0x11018c,
	0x21018c,
	0x1008d,
	0x11008d,
	0x21008d,
	0x1018d,
	0x11018d,
	0x21018d,
	0x1008e,
	0x11008e,
	0x21008e,
	0x1018e,
	0x11018e,
	0x21018e,
	0x1008f,
	0x11008f,
	0x21008f,
	0x1018f,
	0x11018f,
	0x21018f,
	0x1108c,
	0x11108c,
	0x21108c,
	0x1118c,
	0x11118c,
	0x21118c,
	0x1108d,
	0x11108d,
	0x21108d,
	0x1118d,
	0x11118d,
	0x21118d,
	0x1108e,
	0x11108e,
	0x21108e,
	0x1118e,
	0x11118e,
	0x21118e,
	0x1108f,
	0x11108f,
	0x21108f,
	0x1118f,
	0x11118f,
	0x21118f,
	0x1208c,
	0x11208c,
	0x21208c,
	0x1218c,
	0x11218c,
	0x21218c,
	0x1208d,
	0x11208d,
	0x21208d,
	0x1218d,
	0x11218d,
	0x21218d,
	0x1208e,
	0x11208e,
	0x21208e,
	0x1218e,
	0x11218e,
	0x21218e,
	0x1208f,
	0x11208f,
	0x21208f,
	0x1218f,
	0x11218f,
	0x21218f,
	0x1308c,
	0x11308c,
	0x21308c,
	0x1318c,
	0x11318c,
	0x21318c,
	0x1308d,
	0x11308d,
	0x21308d,
	0x1318d,
	0x11318d,
	0x21318d,
	0x1308e,
	0x11308e,
	0x21308e,
	0x1318e,
	0x11318e,
	0x21318e,
	0x1308f,
	0x11308f,
	0x21308f,
	0x1318f,
	0x11318f,
	0x21318f,
	0x100c0,
	0x1100c0,
	0x2100c0,
	0x101c0,
	0x1101c0,
	0x2101c0,
	0x102c0,
	0x1102c0,
	0x2102c0,
	0x103c0,
	0x1103c0,
	0x2103c0,
	0x104c0,
	0x1104c0,
	0x2104c0,
	0x105c0,
	0x1105c0,
	0x2105c0,
	0x106c0,
	0x1106c0,
	0x2106c0,
	0x107c0,
	0x1107c0,
	0x2107c0,
	0x108c0,
	0x1108c0,
	0x2108c0,
	0x100c1,
	0x1100c1,
	0x2100c1,
	0x101c1,
	0x1101c1,
	0x2101c1,
	0x102c1,
	0x1102c1,
	0x2102c1,
	0x103c1,
	0x1103c1,
	0x2103c1,
	0x104c1,
	0x1104c1,
	0x2104c1,
	0x105c1,
	0x1105c1,
	0x2105c1,
	0x106c1,
	0x1106c1,
	0x2106c1,
	0x107c1,
	0x1107c1,
	0x2107c1,
	0x108c1,
	0x1108c1,
	0x2108c1,
	0x100c2,
	0x1100c2,
	0x2100c2,
	0x101c2,
	0x1101c2,
	0x2101c2,
	0x102c2,
	0x1102c2,
	0x2102c2,
	0x103c2,
	0x1103c2,
	0x2103c2,
	0x104c2,
	0x1104c2,
	0x2104c2,
	0x105c2,
	0x1105c2,
	0x2105c2,
	0x106c2,
	0x1106c2,
	0x2106c2,
	0x107c2,
	0x1107c2,
	0x2107c2,
	0x108c2,
	0x1108c2,
	0x2108c2,
	0x100c3,
	0x1100c3,
	0x2100c3,
	0x101c3,
	0x1101c3,
	0x2101c3,
	0x102c3,
	0x1102c3,
	0x2102c3,
	0x103c3,
	0x1103c3,
	0x2103c3,
	0x104c3,
	0x1104c3,
	0x2104c3,
	0x105c3,
	0x1105c3,
	0x2105c3,
	0x106c3,
	0x1106c3,
	0x2106c3,
	0x107c3,
	0x1107c3,
	0x2107c3,
	0x108c3,
	0x1108c3,
	0x2108c3,
	0x110c0,
	0x1110c0,
	0x2110c0,
	0x111c0,
	0x1111c0,
	0x2111c0,
	0x112c0,
	0x1112c0,
	0x2112c0,
	0x113c0,
	0x1113c0,
	0x2113c0,
	0x114c0,
	0x1114c0,
	0x2114c0,
	0x115c0,
	0x1115c0,
	0x2115c0,
	0x116c0,
	0x1116c0,
	0x2116c0,
	0x117c0,
	0x1117c0,
	0x2117c0,
	0x118c0,
	0x1118c0,
	0x2118c0,
	0x110c1,
	0x1110c1,
	0x2110c1,
	0x111c1,
	0x1111c1,
	0x2111c1,
	0x112c1,
	0x1112c1,
	0x2112c1,
	0x113c1,
	0x1113c1,
	0x2113c1,
	0x114c1,
	0x1114c1,
	0x2114c1,
	0x115c1,
	0x1115c1,
	0x2115c1,
	0x116c1,
	0x1116c1,
	0x2116c1,
	0x117c1,
	0x1117c1,
	0x2117c1,
	0x118c1,
	0x1118c1,
	0x2118c1,
	0x110c2,
	0x1110c2,
	0x2110c2,
	0x111c2,
	0x1111c2,
	0x2111c2,
	0x112c2,
	0x1112c2,
	0x2112c2,
	0x113c2,
	0x1113c2,
	0x2113c2,
	0x114c2,
	0x1114c2,
	0x2114c2,
	0x115c2,
	0x1115c2,
	0x2115c2,
	0x116c2,
	0x1116c2,
	0x2116c2,
	0x117c2,
	0x1117c2,
	0x2117c2,
	0x118c2,
	0x1118c2,
	0x2118c2,
	0x110c3,
	0x1110c3,
	0x2110c3,
	0x111c3,
	0x1111c3,
	0x2111c3,
	0x112c3,
	0x1112c3,
	0x2112c3,
	0x113c3,
	0x1113c3,
	0x2113c3,
	0x114c3,
	0x1114c3,
	0x2114c3,
	0x115c3,
	0x1115c3,
	0x2115c3,
	0x116c3,
	0x1116c3,
	0x2116c3,
	0x117c3,
	0x1117c3,
	0x2117c3,
	0x118c3,
	0x1118c3,
	0x2118c3,
	0x120c0,
	0x1120c0,
	0x2120c0,
	0x121c0,
	0x1121c0,
	0x2121c0,
	0x122c0,
	0x1122c0,
	0x2122c0,
	0x123c0,
	0x1123c0,
	0x2123c0,
	0x124c0,
	0x1124c0,
	0x2124c0,
	0x125c0,
	0x1125c0,
	0x2125c0,
	0x126c0,
	0x1126c0,
	0x2126c0,
	0x127c0,
	0x1127c0,
	0x2127c0,
	0x128c0,
	0x1128c0,
	0x2128c0,
	0x120c1,
	0x1120c1,
	0x2120c1,
	0x121c1,
	0x1121c1,
	0x2121c1,
	0x122c1,
	0x1122c1,
	0x2122c1,
	0x123c1,
	0x1123c1,
	0x2123c1,
	0x124c1,
	0x1124c1,
	0x2124c1,
	0x125c1,
	0x1125c1,
	0x2125c1,
	0x126c1,
	0x1126c1,
	0x2126c1,
	0x127c1,
	0x1127c1,
	0x2127c1,
	0x128c1,
	0x1128c1,
	0x2128c1,
	0x120c2,
	0x1120c2,
	0x2120c2,
	0x121c2,
	0x1121c2,
	0x2121c2,
	0x122c2,
	0x1122c2,
	0x2122c2,
	0x123c2,
	0x1123c2,
	0x2123c2,
	0x124c2,
	0x1124c2,
	0x2124c2,
	0x125c2,
	0x1125c2,
	0x2125c2,
	0x126c2,
	0x1126c2,
	0x2126c2,
	0x127c2,
	0x1127c2,
	0x2127c2,
	0x128c2,
	0x1128c2,
	0x2128c2,
	0x120c3,
	0x1120c3,
	0x2120c3,
	0x121c3,
	0x1121c3,
	0x2121c3,
	0x122c3,
	0x1122c3,
	0x2122c3,
	0x123c3,
	0x1123c3,
	0x2123c3,
	0x124c3,
	0x1124c3,
	0x2124c3,
	0x125c3,
	0x1125c3,
	0x2125c3,
	0x126c3,
	0x1126c3,
	0x2126c3,
	0x127c3,
	0x1127c3,
	0x2127c3,
	0x128c3,
	0x1128c3,
	0x2128c3,
	0x130c0,
	0x1130c0,
	0x2130c0,
	0x131c0,
	0x1131c0,
	0x2131c0,
	0x132c0,
	0x1132c0,
	0x2132c0,
	0x133c0,
	0x1133c0,
	0x2133c0,
	0x134c0,
	0x1134c0,
	0x2134c0,
	0x135c0,
	0x1135c0,
	0x2135c0,
	0x136c0,
	0x1136c0,
	0x2136c0,
	0x137c0,
	0x1137c0,
	0x2137c0,
	0x138c0,
	0x1138c0,
	0x2138c0,
	0x130c1,
	0x1130c1,
	0x2130c1,
	0x131c1,
	0x1131c1,
	0x2131c1,
	0x132c1,
	0x1132c1,
	0x2132c1,
	0x133c1,
	0x1133c1,
	0x2133c1,
	0x134c1,
	0x1134c1,
	0x2134c1,
	0x135c1,
	0x1135c1,
	0x2135c1,
	0x136c1,
	0x1136c1,
	0x2136c1,
	0x137c1,
	0x1137c1,
	0x2137c1,
	0x138c1,
	0x1138c1,
	0x2138c1,
	0x130c2,
	0x1130c2,
	0x2130c2,
	0x131c2,
	0x1131c2,
	0x2131c2,
	0x132c2,
	0x1132c2,
	0x2132c2,
	0x133c2,
	0x1133c2,
	0x2133c2,
	0x134c2,
	0x1134c2,
	0x2134c2,
	0x135c2,
	0x1135c2,
	0x2135c2,
	0x136c2,
	0x1136c2,
	0x2136c2,
	0x137c2,
	0x1137c2,
	0x2137c2,
	0x138c2,
	0x1138c2,
	0x2138c2,
	0x130c3,
	0x1130c3,
	0x2130c3,
	0x131c3,
	0x1131c3,
	0x2131c3,
	0x132c3,
	0x1132c3,
	0x2132c3,
	0x133c3,
	0x1133c3,
	0x2133c3,
	0x134c3,
	0x1134c3,
	0x2134c3,
	0x135c3,
	0x1135c3,
	0x2135c3,
	0x136c3,
	0x1136c3,
	0x2136c3,
	0x137c3,
	0x1137c3,
	0x2137c3,
	0x138c3,
	0x1138c3,
	0x2138c3,
	0x10020,
	0x110020,
	0x210020,
	0x11020,
	0x111020,
	0x211020,
	0x12020,
	0x112020,
	0x212020,
	0x13020,
	0x113020,
#endif
	0x213020,
	0x2007d,
	0x12007d,
	0x22007d,
	0
};

void save_1d2d_trained_csr_ddr3_p012(unsigned int addr)
{
	unsigned int i;

	dwc_ddrphy_apb_wr(0xd0000, 0x0); /* DWC_DDRPHYA_APBONLY0_MicroContMuxSel */
	dwc_ddrphy_apb_wr(0xc0080, 0x3); /* DWC_DDRPHYA_DRTUB0_UcclkHclkEnables */
	for (i = 0; save_csr[i] != 0; i++) {
		reg32_write(addr + (i << 2), dwc_ddrphy_apb_rd(save_csr[i]));
	}
	dwc_ddrphy_apb_wr(0xc0080, 0x0); /* DWC_DDRPHYA_DRTUB0_UcclkHclkEnables */
	dwc_ddrphy_apb_wr(0xd0000, 0x1); /* DWC_DDRPHYA_APBONLY0_MicroContMuxSel */

	ddr_dbg("save 1d2d training registers done \n");
}
