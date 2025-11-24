#include "stm32f10x.h"
#include "MyUART.h"
#include "MyTimer.h"
#include "GPIO.h"

int value;

void getValue(){
	value = USART1->DR;
	if (value > 100) {
		value = 256 - value;
		GPIO_Set(GPIOA, 0);
	} else { 
		GPIO_Reset(GPIOA,0);
	}
	my_PWM_set_cycle(TIM1,1,value);
}



int main ( void )
{
	//Récupérer la valeur de la télécommande
	Init_UART(USART1, 9600);
	
	//Initialisation PWM : On veut 20kHz, T = 50µs, FClock = 72MHz donc on prend arr = FClock/FTimer -1 = 3600-1 et psc = 0 (donc 1 - 1)
	// Pas besoin du PSC car 3600 < 65535
	MyTimer_Base_Init(TIM1, 3600 , 1 );
	
	//Start après le init
	MyTimer_Base_Start(TIM1);
	MyTimer_PWM_init(TIM1, 1);
	
	//on configure l'output de la pwm 
	configureOutputGPIO(GPIOA,ALTERNATIVE_PUSH_PULL,8,_2_MHZ);
	//on configure l'output du bit de sens
	configureOutputGPIO(GPIOA, PUSH_PULL, 0, _2_MHZ);
	Active_IT_Read_UART(USART1, 15, getValue);
	
	
	// AREFAIRRE
	while (1)
	{
		
	}
}
