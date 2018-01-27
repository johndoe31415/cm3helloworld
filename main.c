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

#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "pinmap.h"

static void delay(uint32_t counts) {
	while (counts--) {
		__asm__ __volatile__("nop");
	}
}

int main(void) {
	while (true) {
		DebugLED_set_ACTIVE();
		delay(1500000);
		DebugLED_set_INACTIVE();
		delay(1500000);
	}

	return 0;
}
