/*
 * Copyright (c) 2023-2026 Intel Corporation
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _SEDI_SOC_DEFS_H_
#define _SEDI_SOC_DEFS_H_

#include <stdbool.h>

/*!
 * \defgroup sedi_soc_defs_ish Intel ISH SoC Definitions
 */

#define SEDI_CONFIG_ARCH_X86	(1)

#if defined(CONFIG_ISH_PLATFORM_FPGA)
/* ISH SoC clock is lower on FPGA than Silicon */
#if defined(CONFIG_BOARD_ISH_5_9_RVP)
#define SEDI_SOC_CLK_DIVISOR (8)
#define SEDI_RTC_CLK_DIVISOR (1)
#else
#define SEDI_SOC_CLK_DIVISOR (5)
#define SEDI_RTC_CLK_DIVISOR (5)
#endif
#endif

#ifndef SEDI_SOC_CLK_DIVISOR
#define SEDI_SOC_CLK_DIVISOR (1)
#endif

#ifndef SEDI_RTC_CLK_DIVISOR
#define SEDI_RTC_CLK_DIVISOR (1)
#endif

#ifndef ISH_CONFIG_HBW_CLK_DIVIDER
#define ISH_CONFIG_HBW_CLK_DIVIDER (1)
#endif

#define SEDI_RTC_BASE_FREQ (32768)
#define SEDI_RTC_TICKS_PER_SECOND (SEDI_RTC_BASE_FREQ / SEDI_RTC_CLK_DIVISOR)
#define SEDI_RTC_TICKS2US(ticks) ((uint64_t)(ticks) * 1000000 * SEDI_RTC_CLK_DIVISOR \
		/ SEDI_RTC_BASE_FREQ)
#define SEDI_RTC_TICKS2MS(ticks) (SEDI_RTC_TICKS2US(ticks) / 1000)

#define SEDI_MHZ_TO_HZ(mhz) ((mhz) * 1000000)

#ifndef ISH_CONFIG_CLK_FREQUENCY_MHZ
#define ISH_CONFIG_CLK_FREQUENCY_MHZ (100 / SEDI_SOC_CLK_DIVISOR)
#endif

/*!
 * \enum sedi_hw_rev_t
 * \brief HW Revision ID
 */
typedef enum {
	SEDI_HW_REV_INVALID = 0
} sedi_hw_rev_t;

/*!
 * \enum sedi_uart_t
 * \brief  uart device bus ID
 */
typedef enum {
	SEDI_UART_0 = 0,
	SEDI_UART_1,
	SEDI_UART_2,
	SEDI_UART_NUM
} sedi_uart_t;

/*!
 * \enum sedi_dma_t
 * \brief  DMA device bus ID
 */
typedef enum {
	SEDI_DMA_0 = 0,
	SEDI_DMA_NUM
} sedi_dma_t;

/**DMA block TS**/
#define SEDI_DMA_PERIPH_MAX_SIZE 4096
#define SEDI_DMA_PERIPH_MAX_SIZE_SHIFT 12

/*!
 * \enum sedi_i2c_t
 * \brief  I2C device bus ID
 */
typedef enum {
	SEDI_I2C_0 = 0,
	SEDI_I2C_1,
	SEDI_I2C_2,
	SEDI_I2C_NUM
} sedi_i2c_t;

#define I2C_FIFO_DEPTH (64)

/*
 * \enum sedi_ipc_t
 * \brief IPC interface ID
 */
typedef enum {
	SEDI_IPC_HOST = 0,
	SEDI_IPC_CSME,
	SEDI_IPC_PMC,
	SEDI_IPC_CNVI,
	SEDI_IPC_BT,
	SEDI_IPC_NUM
} sedi_ipc_t;

/*!
 * \enum sedi_i3c_t
 * \brief  I3C device bus ID
 */
typedef enum {
	SEDI_I3C_0 = 0,
	SEDI_I3C_1,
	SEDI_I3C_NUM
} sedi_i3c_t;

/*!
 * \enum sedi_gpio_t
 * \brief  GPIO device bus ID
 */
typedef enum {
	SEDI_GPIO_0 = 0,
	SEDI_GPIO_NUM
} sedi_gpio_t;

#define ISH_PIN_NUM 36
#define SEDI_GPIO_SOC_PORT_NUM (2U)

#define SEDI_GPIO_TIMESTAMP_SLOTS_NUM 4
#define SEDI_GPIO_TIMESTAMP_INTERVAL 0x10

/*!
 * \enum sedi_watchdog_t
 * \brief  WATCHDOG device bus ID
 */
typedef enum {
	SEDI_WATCHDOG_0 = 0,
	SEDI_WATCHDOG_NUM
} sedi_watchdog_t;

#define SEDI_HPET_SOC_TIMER_NUM (3)

/*!
 * \enum sedi_spi_t
 * \brief  SPI device bus ID
 */
typedef enum {
	SEDI_SPI_0 = 0,
	SEDI_SPI_1,
	SEDI_SPI_NUM
} sedi_spi_t;

#define SPI_FIFO_DEPTH (64)

/****** TSYNC *****/
#define TSYNC_DEFAULT_FREQ 38400000
#define TSYNC_PMC_LOCAL_MULTI (1)

/*!
 * \enum vnn_id_t
 * \brief VNN ID bit for different drivers
 * \ingroup sedi_soc_defs_ish
 */
typedef enum {
	VNN_ID_FIRST = 0,
	VNN_ID_AON_TASK = VNN_ID_FIRST,
	VNN_ID_DMA0,
	VNN_ID_SIDEBAND,
	VNN_ID_CLK_CHANGE,
	VNN_ID_BRIDGE,
	VNN_ID_IPC_HOST_LONG_UP, /* 5, used by BUP */

	VNN_ID_IPC_START,
	VNN_ID_TOP = VNN_ID_IPC_START + SEDI_IPC_NUM * 2,
} vnn_id_t;

#define VNN_ID_IPC_R(_instance) (VNN_ID_IPC_START + (_instance) * 2)
#define VNN_ID_IPC_W(_instance) (VNN_ID_IPC_START + (_instance) * 2 + 1)

/*!
 * \enum sedi_devid_t
 * \brief SEDI device ID table
 * \ingroup sedi_soc_defs_ish
 */
typedef enum {
	SEDI_DEVID_FIRST = 0,
	SEDI_DEVID_I2C0 = SEDI_DEVID_FIRST,
	SEDI_DEVID_I2C1,
	SEDI_DEVID_I2C2,
	SEDI_DEVID_UART0,
	SEDI_DEVID_UART1,
	SEDI_DEVID_UART2,
	SEDI_DEVID_GPIO0,
	SEDI_DEVID_DMA0,
	SEDI_DEVID_SPI0,
	SEDI_DEVID_SPI1,
#if !defined(BSP_adl)
	SEDI_DEVID_I3C0,
#if !(defined(BSP_mtl) || defined(BSP_mtls))
	SEDI_DEVID_I3C1,
#endif
#endif
	SEDI_DEVID_TOP
} sedi_devid_t;

/*!
 * peripheral device id for dma handshake
 */
typedef enum {
	DMA_HWID_I2C0_RX = 0,
	DMA_HWID_I2C0_TX = 1,
	DMA_HWID_I2C1_RX = 2,
	DMA_HWID_I2C1_TX = 3,
	DMA_HWID_I2C2_RX = 4,
	DMA_HWID_I2C2_TX = 5,
	DMA_HWID_UART0_RX = 6,
	DMA_HWID_UART0_TX = 7,
	DMA_HWID_UART1_RX = 8,
	DMA_HWID_UART1_TX = 9,
	DMA_HWID_UART2_RX = 10,
	DMA_HWID_UART2_TX = 11,
	DMA_HWID_SPI0_RX = 12,
	DMA_HWID_SPI0_TX = 13,
	DMA_HWID_SPI1_RX = 14,
	DMA_HWID_SPI1_TX = 15,
	DMA_HWID_I3C0_RX = 16,
	DMA_HWID_I3C0_TX = 17,
	DMA_HWID_I3C0_CMDQ = 18,
	DMA_HWID_I3C0_RESPQ = 19,
	DMA_HWID_I3C0_IBIQ = 20,
	DMA_HWID_I3C1_RX = 21,
	DMA_HWID_I3C1_TX = 22,
	DMA_HWID_I3C1_CMDQ = 23,
	DMA_HWID_I3C1_RESPQ = 24,
	DMA_HWID_I3C1_IBQ = 25,

	/* below is dummy ones */
	DMA_HWID_I3C2_TX = 0xff,
	DMA_HWID_I3C2_RX = 0xff,
} dma_hs_per_dev_id_t;

/* The step number of hardware IDs per device */
#define SEDI_HWID_PER_DEVICE 2

/*!
 * \enum sedi_pm_pci_inst_t
 * \brief Type of PCI device/function
 * \ingroup sedi_driver_pm
 */
typedef enum {
	SEDI_PCI_INST_FUNC_0 = 0,
	SEDI_PCI_INST_FUNC_TOP,
} sedi_pci_inst_t;

/*!
 * \brief check if a device is owned by SoC itself
 * \param[in] dev: device id to check
 * \return true/false
 * \ingroup sedi_soc_defs_ish
 */
static inline bool sedi_dev_is_self_owned(sedi_devid_t dev)
{
	(void)dev;

	return true;
}

#endif /* _SEDI_SOC_DEFS_H_ */
