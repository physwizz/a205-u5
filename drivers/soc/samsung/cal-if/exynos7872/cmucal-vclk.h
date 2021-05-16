#ifndef __CMUCAL_VCLK_H__
#define __CMUCAL_VCLK_H__

#include "../cmucal.h"

/*=================CMUCAL version: S5E7872================================*/

enum vclk_id {
/* DVFS TYPE */
	VCLK_VDD_CPUCL0 = DFS_VCLK_TYPE,
	VCLK_VDD_CPUCL1,
	VCLK_VDD_G3D,
	VCLK_VDD_INT,
	VCLK_DFS_ABOX,
	end_of_dfs_vclk,
	num_of_dfs_vclk = end_of_dfs_vclk - DFS_VCLK_TYPE,

/* SPECIAL TYPE */
	VCLK_SPL_CLK_FSYS_MMC_CARD_BLK_CMU = (MASK_OF_ID & end_of_dfs_vclk) | VCLK_TYPE,
	VCLK_MUX_CLKCMU_IS_ISP_USER_BLK_CMU,
	VCLK_SPL_CLK_PERI_SPI_1_BLK_CMU,
	VCLK_SPL_CLK_PERI_UART_2_BLK_CMU,
	VCLK_SPL_CLK_PERI_USI2_BLK_CMU,
	VCLK_CLKCMU_CIS_CLK0_BLK_CMU,
	VCLK_CLKCMU_CIS_CLK2_BLK_CMU,
	VCLK_SPL_CLK_FSYS_MMC_EMBD_BLK_CMU,
	VCLK_SPL_CLK_FSYS_MMC_SDIO_BLK_CMU,
	VCLK_SPL_CLK_IS_TPU_BLK_CMU,
	VCLK_SPL_CLK_PERI_SPI_0_BLK_CMU,
	VCLK_SPL_CLK_PERI_UART_0_BLK_CMU,
	VCLK_SPL_CLK_PERI_USI1_BLK_CMU,
	VCLK_OCC_MIF_CMUREF_BLK_CMU,
	VCLK_OCC_CMU_CMUREF_BLK_CMU,
	VCLK_CLKCMU_CIS_CLK1_BLK_CMU,
	VCLK_SPL_CLK_PERI_USI0_BLK_CMU,
	VCLK_SPL_CLK_PERI_UART_1_BLK_CMU,
	VCLK_SPL_CLK_IS_3AA_HALF_BLK_CMU,
	VCLK_SPL_CLK_CPUCL0_CNTCLK_BLK_CPUCL0,
	VCLK_SPL_CLK_CPUCL0_ATCLK_BLK_CPUCL0,
	VCLK_SPL_CLK_CPUCL0_CMUREF_BLK_CPUCL0,
	VCLK_SPL_CLK_CPUCL1_CNTCLK_BLK_CPUCL1,
	VCLK_DIV_CLK_CPUCL1_CMUREF_BLK_CPUCL1,
	VCLK_SPL_CLK_CPUCL1_ATCLK_BLK_CPUCL1,
	VCLK_SPL_CLK_AUD_UAIF2_BLK_DISPAUD,
	VCLK_SPL_CLK_AUD_CPU_ACLK_BLK_DISPAUD,
	VCLK_SPL_CLK_AUD_UAIF0_BLK_DISPAUD,
	VCLK_SPL_CLK_AUD_UAIF3_BLK_DISPAUD,
	VCLK_SPL_CLK_AUD_CPU_PCLKDBG_BLK_DISPAUD,
	VCLK_CLK_AUD_FM_BLK_DISPAUD,
	VCLK_SPL_CLK_IS_3AA_HALF_BLK_IS,
	VCLK_OCC_MIF_CMUREF_BLK_MIF,
	VCLK_WPLL_USBPLL,
	end_of_vclk,
	num_of_vclk = end_of_vclk - ((MASK_OF_ID & end_of_dfs_vclk) | VCLK_TYPE),

/* COMMON TYPE */
	VCLK_BLK_APM = (MASK_OF_ID & end_of_vclk) | COMMON_VCLK_TYPE,
	VCLK_BLK_CMU,
	VCLK_BLK_CPUCL0,
	VCLK_BLK_CPUCL1,
	VCLK_BLK_DISPAUD,
	VCLK_BLK_G3D,
	VCLK_BLK_MFCMSCL,
	VCLK_BLK_MIF,
	end_of_common_vclk,
	num_of_common_vclk = end_of_common_vclk - ((MASK_OF_ID & end_of_vclk) | COMMON_VCLK_TYPE),

/* GATING TYPE */
	VCLK_APBIF_GPIO_ALIVE = (MASK_OF_ID & end_of_common_vclk) | GATE_VCLK_TYPE,
	VCLK_APBIF_PMU_ALIVE,
	VCLK_APM,
	VCLK_APM_CMU_APM,
	VCLK_ASYNCAPB_APM,
	VCLK_I2C_APM,
	VCLK_IP_BATCHER_AP,
	VCLK_IP_BATCHER_CP,
	VCLK_LHM_AXI_P_ALIVE,
	VCLK_LHS_AXI_D_ALIVE,
	VCLK_MAILBOX_APM2AP,
	VCLK_MAILBOX_APM2CP,
	VCLK_MAILBOX_APM2GNSS,
	VCLK_MAILBOX_APM2WLBT,
	VCLK_MP_APBSEMA_HWACG_2CH,
	VCLK_SPEEDY,
	VCLK_SYSREG_APM,
	VCLK_WDT_APM,
	VCLK_ADM_APB_P_CSSYS_DBG,
	VCLK_ADS_AHB_G_SSS,
	VCLK_ADS_APB_G_CSSYS_DBG,
	VCLK_AD_APB_P_DUMP_PC_CPUCL0,
	VCLK_AD_APB_P_SECJTAG_CPUCL0,
	VCLK_AXI2APB_CPUCL0,
	VCLK_CPUCL0_CMU_CPUCL0,
	VCLK_CSSYS_DBG,
	VCLK_DUMP_PC_CPUCL0,
	VCLK_LHM_AXI_P_CPUCL0,
	VCLK_LHS_ACE_D_CPUCL0,
	VCLK_LHS_AXI_T_CSSYS_DBG,
	VCLK_SECJTAG,
	VCLK_SYSREG_CPUCL0,
	VCLK_ADM_APB_G_CPUCL1,
	VCLK_AD_APB_P_DUMP_PC_CPUCL1,
	VCLK_AXI2APB_CPUCL1,
	VCLK_CPUCL1_CMU_CPUCL1,
	VCLK_DUMP_PC_CPUCL1,
	VCLK_LHM_AXI_P_CPUCL1,
	VCLK_LHS_ACE_D_CPUCL1,
	VCLK_SYSREG_CPUCL1,
	VCLK_ABOX,
	VCLK_ABOX_DAP,
	VCLK_AD_APB_DECON0,
	VCLK_AD_APB_DECON0_SECURE,
	VCLK_AD_APB_DPP,
	VCLK_AD_APB_DPU_DMA,
	VCLK_AD_APB_DPU_DMA_SECURE,
	VCLK_AD_APB_DSIM0,
	VCLK_AD_APB_SMMU_DPU,
	VCLK_AD_APB_SMMU_DPU_SECURE,
	VCLK_AXI2APB_DISPAUD,
	VCLK_AXI_US_32to128,
	VCLK_DFTMUX_DISPAUD,
	VCLK_DISPAUD_CMU_DISPAUD,
	VCLK_DPU,
	VCLK_GPIO_DISPAUD,
	VCLK_LHM_AXI_P_DISPAUD,
	VCLK_LHS_AXI_D_ABOX,
	VCLK_LHS_AXI_D_DPU,
	VCLK_PERI_AXI_ASB,
	VCLK_BCM_ABOX,
	VCLK_BCM_DPU,
	VCLK_SMMU_ABOX,
	VCLK_SMMU_DPU,
	VCLK_SYSREG_DISPAUD,
	VCLK_WDT_ABOXCPU,
	VCLK_XIU_P_DISPAUD,
	VCLK_ADM_AHB_SSS,
	VCLK_AHB2APB_FSYS,
	VCLK_AHBBR_FSYS,
	VCLK_AHBBR_FSYS_1x4,
	VCLK_AXI2AHB_FSYS,
	VCLK_FSYS_CMU_FSYS,
	VCLK_GPIO_FSYS,
	VCLK_LHM_AXI_P_FSYS,
	VCLK_LHS_AXI_D_FSYS,
	VCLK_MMC_CARD,
	VCLK_MMC_EMBD,
	VCLK_MMC_SDIO,
	VCLK_BCM_FSYS,
	VCLK_RTIC,
	VCLK_SSS,
	VCLK_SYSREG_FSYS,
	VCLK_USB20DRD,
	VCLK_XIU_D_FSYS,
	VCLK_AXI2APB_G3D,
	VCLK_G3D_CMU_G3D,
	VCLK_LHM_AXI_G3DSFR,
	VCLK_LHM_AXI_P_G3D,
	VCLK_LHS_AXI_D_G3D,
	VCLK_LHS_AXI_G3DSFR,
	VCLK_SYSREG_G3D,
	VCLK_XIU_P_G3D,
	VCLK_ASYNCM_P_IS,
	VCLK_ASYNCS_D0_IS,
	VCLK_ASYNCS_D1_IS,
	VCLK_IS_CMU_IS,
	VCLK_BCM_NRT,
	VCLK_BCM_RT,
	VCLK_SMMU_IS,
	VCLK_SYSREG_IS,
	VCLK_is5p15p0_IS,
	VCLK_ASYNC_AXI,
	VCLK_ASYNC_G2D_P,
	VCLK_ASYNC_JPEG_P,
	VCLK_ASYNC_MFC_P,
	VCLK_ASYNC_MSCL_P,
	VCLK_ASYNC_SMMU_NS_P,
	VCLK_ASYNC_SMMU_S_P,
	VCLK_AXI2APB_MFCMSCL,
	VCLK_G2D,
	VCLK_JPEG,
	VCLK_LHM_AXI_P_MFCMSCL,
	VCLK_LHS_AXI_D_MFCMSCL,
	VCLK_MFC,
	VCLK_MFCMSCL_CMU_MFCMSCL,
	VCLK_MSCL,
	VCLK_BCM_MFCMSCL,
	VCLK_SMMU_MFCMSCL,
	VCLK_SYSREG_MFCMSCL,
	VCLK_XIU_D_MFCMSCL,
	VCLK_ADS_APB_G_CSSYS,
	VCLK_AD_APB_PDMA0,
	VCLK_AD_APB_SPDMA,
	VCLK_AD_AXI_GIC,
	VCLK_AHB2APB_COREP0,
	VCLK_AHB2APB_CSSYS_DBG,
	VCLK_AHB_BRIDGE,
	VCLK_AXI2AHB_COREP,
	VCLK_AXI2AHB_CORE_CSSYS,
	VCLK_AXI2APB_2MB_BUSCP,
	VCLK_AXI_ASYNC_DMC_CPU,
	VCLK_AXI_US_A40_32to128_PDMA,
	VCLK_AXI_US_A40_32to128_SDMA,
	VCLK_AXI_US_A40_64to128_CSSYS,
	VCLK_CCI_400,
	VCLK_GIC400_AIHWACG,
	VCLK_LBLK_MIF,
	VCLK_LHM_ACE_D_CPUCL0,
	VCLK_LHM_ACE_D_CPUCL1,
	VCLK_LHM_AXI_D_ABOX,
	VCLK_LHM_AXI_D_APM,
	VCLK_LHM_AXI_D_CP,
	VCLK_LHM_AXI_D_CSSYS,
	VCLK_LHM_AXI_D_DPU,
	VCLK_LHM_AXI_D_FSYS,
	VCLK_LHM_AXI_D_G3D,
	VCLK_LHM_AXI_D_GNSS,
	VCLK_LHM_AXI_D_ISPNRT,
	VCLK_LHM_AXI_D_ISPRT,
	VCLK_LHM_AXI_D_MFCMSCL,
	VCLK_LHM_AXI_D_WLBT,
	VCLK_LHM_AXI_P_CP,
	VCLK_LHS_AXI_P_APM,
	VCLK_LHS_AXI_P_CPUCL0,
	VCLK_LHS_AXI_P_CPUCL1,
	VCLK_LHS_AXI_P_DISPAUD,
	VCLK_LHS_AXI_P_FSYS,
	VCLK_LHS_AXI_P_G3D,
	VCLK_LHS_AXI_P_IS,
	VCLK_LHS_AXI_P_MFCMSCL,
	VCLK_LHS_AXI_P_PERI,
	VCLK_MAILBOX,
	VCLK_MAILBOX_ABOX,
	VCLK_MAILBOX_GNSSS,
	VCLK_MAILBOX_SECURE,
	VCLK_MAILBOX_WLBT0,
	VCLK_MAILBOX_WLBT1,
	VCLK_MIF_CMU_MIF,
	VCLK_PDMA_CORE,
	VCLK_PPCFW_G3D,
	VCLK_BCM_ACE_CPUCL0,
	VCLK_BCM_ACE_CPUCL1,
	VCLK_QE,
	VCLK_SFR_APBIF_CMU_CMU,
	VCLK_SPDMA_CORE,
	VCLK_SYSREG_MIF,
	VCLK_TREX_D_CORE,
	VCLK_TREX_P_CORE,
	VCLK_WRAP_ADC_IF,
	VCLK_XIU_D_PDMA_3x1,
	VCLK_MODEM_CMU,
	VCLK_AXI2AHB_PERI,
	VCLK_BUSIF_TMU,
	VCLK_BUSP1_PERIS0,
	VCLK_BUSP_BR_PERI,
	VCLK_LBLK_PERIC,
	VCLK_LHM_AXI_P_PERI,
	VCLK_MCT,
	VCLK_OTP_CON_TOP,
	VCLK_PERI_CMU_PERI,
	VCLK_SECUCON,
	VCLK_SYSREG_PERI,
	VCLK_WDT_CLUSTER0,
	VCLK_WDT_CLUSTER1,
	end_of_gating_vclk,
	num_of_gating_vclk = end_of_gating_vclk - ((MASK_OF_ID & end_of_common_vclk) | GATE_VCLK_TYPE),

};
#endif
