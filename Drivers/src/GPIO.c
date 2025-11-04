#include "stm32f10x.h"
#include "GPIO.h"

void setupClock(GPIO_TypeDef * GPIO){
	if (GPIO==GPIOA) {
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	if (GPIO==GPIOB) {
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	if (GPIO==GPIOC) {
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	if (GPIO==GPIOD) {
			RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	}
}

void configureInputGPIO(GPIO_TypeDef * GPIO, enum GPIO_INPUT_MOD mod, char pin){
	
	// à changer suivant le GPIO

setupClock(GPIO);
	
	if (pin<8){
		if (mod==0x10) {
				GPIO->CRL&=~(0xF<<(pin*4));	
				GPIO->CRL|=0x8<<(pin*4);
				GPIO->ODR&=~(0x1<<pin);
		}
		else {
				GPIO->CRL&=~(0xF<<(pin*4));	
				GPIO->CRL|=mod<<(pin*4);
				GPIO->ODR|=(0x1<<pin);
		}						
	} else if (pin<16)  {
				if (mod==0x10) {
				GPIO->CRH&=~(0xF<<((pin-8)*4));	
				GPIO->CRH|=0x8<<((pin-8)*4);
				GPIO->ODR&=~(0x1<<(pin-8));
		}
		else {
				GPIO->CRH&=~(0xF<<((pin-8)*4));	
				GPIO->CRH|=mod<<((pin-8)*4);
				GPIO->ODR|=(0x1<<(pin-8));
		}						
	}
}



void configureOutputGPIO(GPIO_TypeDef * GPIO, enum GPIO_OUTPUT_MOD mod, char pin, enum SPEED speed){
	setupClock(GPIO);
	if (pin<8){		
				GPIO->CRL&=~(0xF<<(pin*4));	
				GPIO->CRL|=((mod<<2)+speed)<<(pin*4);	
	} else if (pin<16) {
				GPIO->CRH&=~(0xF<<((pin-8)*4));	
				GPIO->CRH|=((mod<<2)+speed)<<((pin-8)*4);	
	}
}



int GPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	int value = GPIO->IDR;
	value = value>>(GPIO_Pin - 1);
	return value &= 0x1;
}

void GPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	GPIO->ODR |= (0x1<<GPIO_Pin);
}

void GPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR &=~(0x1<<GPIO_Pin);
}

void GPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	int value = GPIO->ODR;
	value = value>>GPIO_Pin;
	value &= 0x1;
	if(value){
		GPIO->ODR &=~(1 << GPIO_Pin);
	} else {
		GPIO->ODR |= (1 << GPIO_Pin);
	}
}
