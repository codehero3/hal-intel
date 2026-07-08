/*
 * Copyright (c) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log_ctrl.h>
#include <zephyr/logging/log.h>

#include "sedi_soc_regs.h"
#include "sedi_misc_regs.h"

LOG_MODULE_REGISTER(bsp_sedi, CONFIG_BSP_SEDI_LOG_LEVEL);

void sedi_log(int level, const char *fmt, ...)
{
	va_list vargs;

	va_start(vargs, fmt);

#ifndef CONFIG_LOG
	/* No support, do nothing */
	ARG_UNUSED(level);
#elif CONFIG_LOG_MODE_MINIMAL
	vprintk(fmt, vargs);
#else
	log_generic(level, fmt, vargs);
#endif

	va_end(vargs);
}

#ifdef CONFIG_DEBUG
void sedi_assert_halt(void)
{
	while (1) {
		if (k_is_in_isr()) {
			LOG_PANIC();
		} else {
			k_msleep(1);
		}
	}
}
#endif

#define SOFT_STRAP_SRAM_SIZE_MASK ((uint32_t)BIT(6))

bool sedi_high_sram_is_ready(void)
{
	if (SEDI_REG_GET(MISC, ISH_SOFT_STRAP1) & SOFT_STRAP_SRAM_SIZE_MASK) {
		return true;
	} else {
		return false;
	}
}

#ifdef CONFIG_ISH_PAGING
#include <x86_mmu.h>
#include <mmu.h>
#include "sedi_soc_regs.h"
#include "sedi_misc_regs.h"

uintptr_t sedi_core_virt_to_phys(uintptr_t virt)
{
	pentry_t entry = (pentry_t)NULL;

	z_x86_pentry_get(NULL, &entry, z_x86_page_tables_get(), (void *)virt);
	if (!entry) {
		return 0xdead0001;
	}

	return ((uintptr_t)(entry & ~(CONFIG_MMU_PAGE_SIZE - 1))
			| (virt & (CONFIG_MMU_PAGE_SIZE - 1)));
}

uintptr_t sedi_core_phys_to_virt(uintptr_t phys)
{
	struct k_mem_page_frame *pf = NULL;

	pf = k_mem_phys_to_page_frame(phys);
	if (!pf) {
		return 0xdead0002;
	}

	return (((uintptr_t)k_mem_page_frame_to_virt(pf) & ~(CONFIG_MMU_PAGE_SIZE - 1))
			| (phys & (CONFIG_MMU_PAGE_SIZE - 1)));
}

#define SOFT_STRAP_SRAM_SIZE_MASK ((uint32_t)BIT(6))
#define SEDI_SRAM_SIZE_960KB_BYTES (960U * 1024U)
#define SEDI_SRAM_SIZE_640KB_BYTES (640U * 1024U)

uint32_t sedi_get_sram_size(void)
{
	if (SEDI_REG_GET(MISC, ISH_SOFT_STRAP1) & SOFT_STRAP_SRAM_SIZE_MASK) {
		return SEDI_SRAM_SIZE_960KB_BYTES;
	} else {
		return SEDI_SRAM_SIZE_640KB_BYTES;
	}
}
#endif
