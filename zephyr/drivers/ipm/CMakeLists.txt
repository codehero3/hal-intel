# Copyright (c) 2019-2023 Intel Corporation.
#
# SPDX-License-Identifier: BSD-3-Clause

if(NOT CONFIG_INTEL_HAL)
zephyr_library_ootree_sources(ipm_sedi.c)
endif()

zephyr_library_ootree_sources(${BSP_SEDI_DIR}/drivers/ipc/sedi_ipc.c)
