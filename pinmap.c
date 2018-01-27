#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include "pinmap.h"

void pinmap_initialize(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	{	// 1 pin(s) on PORTB with mode Out_PP, otype PP, speed 2 MHz and pullup NOPULL
		GPIOB->BRR = (DebugLED_Pin);
		GPIO_InitTypeDef GPIO_InitStructure = {
			.GPIO_Pin = DebugLED_Pin,
			.GPIO_Mode = GPIO_Mode_Out_PP,
			.GPIO_Speed = GPIO_Speed_2MHz,
		};
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
}
