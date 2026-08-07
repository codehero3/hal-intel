# Copyright (c) 2023-2025 Intel Corporation.
#
# SPDX-License-Identifier: BSD-3-Clause

SET(INTEL_HAL_LIB_NAME intel_hal_bsp_sedi)

zephyr_interface_library_named(intel_hal_interface)
zephyr_library_named(${INTEL_HAL_LIB_NAME})
zephyr_library_link_libraries(intel_hal_interface)
target_link_libraries(zephyr_interface INTERFACE intel_hal_interface)
target_include_directories(intel_hal_interface INTERFACE ${BSP_SEDI_DIR}/include)
target_include_directories(intel_hal_interface INTERFACE ${BSP_SEDI_DIR}/include/driver)
target_include_directories(intel_hal_interface INTERFACE ${BSP_SEDI_SOC_DIR}/include)
target_include_directories(intel_hal_interface INTERFACE ${BSP_SEDI_SOC_DIR}/../common/include)
target_include_directories(intel_hal_interface INTERFACE ${BSP_SEDI_PM_DIR}/include)

if(EXISTS ${BSP_SEDI_SOC_DIR}/sedi_soc.c)
  zephyr_library_sources(${BSP_SEDI_SOC_DIR}/sedi_soc.c)
endif()

if(NOT CONFIG_INTEL_HAL)
zephyr_library_sources(${BSP_SEDI_SOC_DIR}/ish_fwst.c)
if(DEFINED CONFIG_ISH_PAGING)
  zephyr_linker_pinned(lib${INTEL_HAL_LIB_NAME}.a:ish_fwst.c.obj)
endif()
endif()

zephyr_library_sources(${BSP_SEDI_DIR}/drivers/rtc/sedi_rtc.c)
zephyr_library_sources(${BSP_SEDI_DIR}/drivers/hpet/sedi_hpet.c)

if(CONFIG_INTEL_HAL)
zephyr_sources(bsp_sedi_rtos_utils.c)
else()
zephyr_sources(bsp_sedi_rtos_utils_ish.c)
endif()

if(NOT CONFIG_INTEL_HAL)
if(CONFIG_SOC_SERIES_INTEL_ISH5)
  zephyr_library_sources(${BSP_SEDI_DIR}/drivers/sideband/sideband_sedi.c)
  zephyr_library_sources(${BSP_SEDI_DIR}/drivers/tsync/tsync.c)
else()
  zephyr_library_sources(${BSP_SEDI_DIR}/drivers/sideband/sideband_msgif.c)
endif()
endif()

add_subdirectory(pm)
