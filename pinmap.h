#ifndef __PINMAP_H__
#define __PINMAP_H__

#ifdef __ARM_ARCH
#include <stm32f10x_gpio.h>
#else
typedef struct {
} GPIO_TypeDef;
#endif

struct gpio_definition_t {
	const char *pin_name;
	const char *name;
	GPIO_TypeDef *gpio;
	int pin_source;
	const char *comment;
	const char *connect;
};

// PB1: DebugLED (OUT) -- ['init']
#define DebugLED_GPIO							GPIOB
#define DebugLED_PinSource						GPIO_PinSource1
#define DebugLED_Pin							GPIO_Pin_1
#define DebugLED_set_HIGH()						DebugLED_GPIO->BSRR = DebugLED_Pin
#define DebugLED_set_LOW()						DebugLED_GPIO->BRR = DebugLED_Pin
#define DebugLED_set_ACTIVE()					DebugLED_set_HIGH()
#define DebugLED_set_INACTIVE()					DebugLED_set_LOW()
#define DebugLED_get()							(DebugLED_GPIO->IDR & DebugLED_Pin)
#define DebugLED_set(value)						if (value) { DebugLED_set_ACTIVE(); } else { DebugLED_set_INACTIVE(); }
#define DebugLED_toggle()						DebugLED_GPIO->ODR ^= DebugLED_Pin
#define DebugLED_pulse()						do { DebugLED_set_ACTIVE(); delay_loopcnt(LOOPCOUNT_50NS); DebugLED_set_INACTIVE(); } while (0)
#define DebugLED_npulse()						do { DebugLED_set_INACTIVE(); delay_loopcnt(LOOPCOUNT_50NS); DebugLED_set_ACTIVE(); } while (0)
#define DebugLED_GPIO_Definition				{ .gpio = DebugLED_GPIO, .name = "DebugLED", .pin_name = "B1", .pin_source = DebugLED_PinSource }

void pinmap_initialize(void);

#endif
