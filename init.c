/**
 *	cm3helloworld - STM32F101 "Hello World" blinky.
 *	Copyright (C) 2018-2018 Johannes Bauer
 *
 *	This file is part of cm3helloworld.
 *
 *	cm3helloworld is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; this program is ONLY licensed under
 *	version 3 of the License, later versions are explicitly excluded.
 *
 *	cm3helloworld is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with cm3helloworld; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	Johannes Bauer <JohannesBauer@gmx.de>
**/

#include <stm32f10x_rcc.h>
#include <misc.h>
#include "init.h"
#include "pinmap.h"

static void init_clock(void) {
	/* Enable HSE */
	RCC->CR |= RCC_CR_HSEON;

	/* Wait until HSE ready */
	while (!(RCC->CR & RCC_CR_HSERDY));

	/* Configure PLL for 8 MHz HSE -> 36 MHz PLL */
	/* HSE / 2 (PLLXTPRE) = 4 MHz */
	/* PLLMUL = 9 */
	RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_PLLMULL)) | RCC_CFGR_PLLMULL9 | RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE;

	/* Activate PLL */
	RCC->CR |= RCC_CR_PLLON;

	/* Wait until the main PLL is ready */
	while (!(RCC->CR & RCC_CR_PLLRDY));

	/* Select the main PLL as system clock source */
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	/* Wait until the main PLL is used as system clock source */
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);

	/* Output at PA8 (Pin29, MCO) for debugging */
//	RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);
}

void SystemInit(void) {
	__disable_irq();
	init_clock();
	pinmap_initialize();
	__enable_irq();
}
