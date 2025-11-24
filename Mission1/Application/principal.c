#include "stm32f10x.h"
#include "MyGirouette.h"

int main ( void )
{
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
	
	//GPIOA.4 en sortie output push pull 0100
	// mask = ~(0xF<<(6*4))  logique : 11111110000111111111 --> 00000000111100000000
	GPIOA->CRL&=~(0xF<<(4*4));	
	GPIOA->CRL|= 0x02<<(4*4);
	
	GPIOC->CRL&=~(0xF<<(4*4));	
	GPIOC->CRL|= 0x04<<(4*4);
	
	// Codeur incrémental
	// Faire une fonction lire_angle / convertir_angle / 
	
	
	Init_Girouette(TIM4,TIM2,TIM3);
	// AREFAIRRE
	while (1)
	{
		int ang = lire_angle();
		int new_ang = convertir_angle(ang);
		ajuster_voile(TIM4, new_ang);
	}
}
