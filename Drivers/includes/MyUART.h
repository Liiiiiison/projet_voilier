#ifndef MYUART_H
#define MYUART_H
#include "stm32f10x.h"
void Init_UART(USART_TypeDef * UART, int Bdrate);
void Print_UART(USART_TypeDef * UART, int data);
void Active_IT_Read_UART(USART_TypeDef * UART, char prio, void (*IT_Function) (void));
	
#endif