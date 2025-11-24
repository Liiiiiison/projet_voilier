#include "stm32f10x.h"
#include "MyUART.h"
#include "MyTimer.h"
#include "GPIO.h"

int value;

void getValue(){
	value = USART2->DR;
	my_PWM_set_cycle(TIM1,1,value);
}



int main ( void )
{
	//Récupérer la valeur de la télécommande
	Init_UART(USART2, 9600);
	
	//Initialisation PWM : On veut 20kHz, T = 50µs, FClock = 72MHz donc on prend arr = FClock/FTimer -1 = 3600-1 et psc = 0 (donc 1 - 1)
	// Pas besoin du PSC car 3600 < 65535
	MyTimer_Base_Init(TIM1, 3600 , 1 );
	MyTimer_PWM_init(TIM1, 1);
	
	//on configure l'output de la pwm 
	configureOutputGPIO(GPIOB,ALTERNATIVE_PUSH_PULL,13,_2_MHZ);
	Active_IT_Read_UART(USART2, 15, getValue);
	
	
	// AREFAIRRE
	while (1)
	{
		
	}
}
