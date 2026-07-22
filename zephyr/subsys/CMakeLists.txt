# Copyright (c) 2019-2024 Intel Corporation.
#
# SPDX-License-Identifier: BSD-3-Clause

if(CONFIG_INTEL_HAL)
  add_subdirectory_ifdef(CONFIG_LOG logging/backends)
else()
  add_subdirectory_ifdef(CONFIG_LOG logging)
  add_subdirectory_ifdef(CONFIG_SPI_SEDI spi_extension)
  add_subdirectory_ifdef(CONFIG_I2C_SEDI i2c_extension)
  add_subdirectory_ifdef(CONFIG_HOST_SERVICE host_service)
  add_subdirectory_ifdef(CONFIG_PM_SERVICE pm)
  add_subdirectory_ifdef(CONFIG_DEMAND_PAGING demand_paging)
endif()
