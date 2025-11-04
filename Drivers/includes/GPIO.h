#include "stm32f10x.h"

#ifndef GPIO_H
#define GPIO_H

enum GPIO_INPUT_MOD{
	ANALOG = 0x0,
	FLOATING = 0x4,
	PULL_UP = 0x8,
	PULL_DOWN = 0x10
};

enum GPIO_OUTPUT_MOD {
	PUSH_PULL = 0x0,
	OPEN_DRAIN = 0x1,
	ALTERNATIVE_PUSH_PULL = 0x2,
	ALTERNATIVE_OPEN_DRAIN = 0x3
};

enum GPIO_MOD {
	INPUT,
	OUTPUT
};

enum SPEED {
	_RESERVED,
	_2_MHZ,
	_5_MHZ,
	_10_MHZ
};


void configureInputGPIO(GPIO_TypeDef * GPIO, enum GPIO_INPUT_MOD mod, char pin);

void configureOutputGPIO(GPIO_TypeDef * GPIO, enum GPIO_OUTPUT_MOD mod, char pin, enum SPEED speed);

int GPIO_Read (GPIO_TypeDef * GPIO, char GPIO_Pin );

void GPIO_Set (GPIO_TypeDef * GPIO, char GPIO_Pin );

void GPIO_Reset (GPIO_TypeDef * GPIO, char GPIO_Pin);

void GPIO_Toggle (GPIO_TypeDef * GPIO, char GPIO_Pin);


#endif