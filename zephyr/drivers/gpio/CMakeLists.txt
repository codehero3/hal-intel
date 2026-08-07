# Copyright (c) 2025 Intel Corporation.
#
# SPDX-License-Identifier: BSD-3-Clause

zephyr_library_ootree_sources(${BSP_SEDI_DIR}/drivers/gpio/sedi_gpio.c)
if(NOT CONFIG_INTEL_HAL)
zephyr_library_ootree_sources(${BSP_SEDI_DIR}/drivers/gpio/sedi_timed_gpio.c)
endif()
