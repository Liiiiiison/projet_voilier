#include "stm32f10x.h"
#include "MyUART.h"

int value;

void setValue(){
	value = USART2->DR;
}

int main ( void )
{

	Init_UART(USART2, 9600);
	Active_IT_Read_UART(USART2, setValue);
	
	// AREFAIRRE
	while (1)
	{
		
	}
}
