# Copyright (c) 2025 Intel Corporation.
#
# SPDX-License-Identifier: BSD-3-Clause

if(CONFIG_PM)
  if(CONFIG_INTEL_HAL)
    zephyr_library_sources(${BSP_SEDI_SOC_DIR}/pm/sedi_pm.c)
  endif()

  add_subdirectory(aon)
endif()
