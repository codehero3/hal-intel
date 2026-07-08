# Copyright (c) 2025 Intel Corporation.
#
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory_ifdef(CONFIG_UART_SEDI serial)
add_subdirectory_ifdef(CONFIG_GPIO_SEDI gpio)
add_subdirectory_ifdef(CONFIG_IPM_SEDI ipm)
add_subdirectory_ifdef(CONFIG_DMA_SEDI dma)
if(CONFIG_I3C_SEDI OR CONFIG_I3C_SLAVE_SEDI OR CONFIG_I3C_SEDI_V111)
  add_subdirectory(i3c)
endif()
add_subdirectory_ifdef(CONFIG_WDT_SEDI watchdog)
add_subdirectory_ifdef(CONFIG_I2C_SEDI i2c)
add_subdirectory_ifdef(CONFIG_SPI_SEDI spi)
