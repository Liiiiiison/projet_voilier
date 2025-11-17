#include "stm32f10x.h"
#include "MyADC.h"


// Initialise l'ADC
void ADC_Init(void){
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->CFGR |= (0x2 << 14); // Pour avoir 12 MHz car la T(ADCCLK) est initialement à 72 MHz, on la divise par 6 car c'est trop grand 
	ADC1->CR2 |= ADC_CR2_ADON; 
	ADC1->SQR1 &= ~(0xF << 20);
	//ADC1->CR2 |= ADC_CR2_EXTTRIG; 
	ADC1->CR2 &= ~ADC_CR2_EXTSEL ;
	ADC1->CR2 |=0x7<<17; /* trig by swstart*/
}	

// Lit la valeur de sortie
short ADC_Read(char channel){
	ADC1->SQR3 = channel;
	ADC1->CR2 |= ADC_CR2_ADON; 
	//ADC1->CR2 |= ADC_CR2_SWSTART  ; // Registre ADC_CR2 champ EXTSEL et EXTTRIG (sert à lancer l'ADC pour qu'il lise la valeur dans la channel)
	
	while ((ADC1->SR&ADC_SR_EOC)==0)
	//while (!(ADC1->SR | ~ADC_SR_EOC))
  { // Alternative :  ADC1->SR ^ (1<<1)
	}
	return (ADC1->DR);
}
