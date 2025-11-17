#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"

void ADC_Init(void);
short ADC_Read(char channel);
	
#endif
