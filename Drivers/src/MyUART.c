#include "stm32f10x.h"
#include "stdio.h"
#include "MyUART.h"
#include "GPIO.h"

void (* callbackUART1)(void);
void (* callbackUART2)(void);
void (* callbackUART3)(void);

void Init_UART(USART_TypeDef * UART, int Bdrate){
	// Régler le Baudrate. => BRR -> dépend du périphérique utilisé ici 9600 
	// BdRate = F_Clk/BRR
	// BRR = F_Clk/ BdRate
	if (UART == USART1) {
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 
		UART->BRR = (72e6)/ Bdrate;
		configureOutputGPIO(GPIOA, ALTERNATIVE_PUSH_PULL, 9, _2_MHZ);
	}
	else if (UART == USART2) {
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		UART->BRR = (36e6)/ Bdrate;
		configureOutputGPIO(GPIOA, ALTERNATIVE_PUSH_PULL, 2, _2_MHZ);

	}
	else if (UART == USART3) {
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		UART->BRR = (36e6)/ Bdrate;
		configureOutputGPIO(GPIOB, ALTERNATIVE_PUSH_PULL, 10, _2_MHZ);
	}
	
	UART->CR1 &= ~USART_CR1_M;
	UART->CR2 &= ~USART_CR2_STOP;
	UART->CR1 |= USART_CR1_TE;
	UART->CR1 |= USART_CR1_RE;
	UART->CR1 |= USART_CR1_UE;
}
	
	
void Print_UART(USART_TypeDef * UART, int data){
	while ((UART->SR & USART_SR_TXE) == 0){
		// On peut envoyer (écrire dans DR)
		UART->DR |= data;
	}
}


void Active_IT_Read_UART(USART_TypeDef * UART, char prio, void (*IT_Function) (void)){
		// ACTIVER Les interruptions. 
		UART->CR1 |= USART_CR1_RXNEIE;
		if (UART == USART1) {
			NVIC_EnableIRQ(USART1_IRQn);
			NVIC_SetPriority(USART1_IRQn, prio);
			callbackUART1 = IT_Function;
		}
		else if (UART == USART2) {
			NVIC_EnableIRQ(USART2_IRQn);
			NVIC_SetPriority(USART2_IRQn, prio);
			callbackUART2 = IT_Function;
		}
		else if (UART == USART3) {
			NVIC_EnableIRQ(USART3_IRQn);
			NVIC_SetPriority(USART3_IRQn, prio);
			callbackUART3 = IT_Function;
		}
}

void USART1_IRQHandler(){
	if (USART1->SR & USART_SR_RXNE){
		USART1->SR = 0;
		callbackUART1();
	}
}

void USART2_IRQHandler(){
	if (USART2->SR & USART_SR_RXNE){
		USART2->SR = 0;
		callbackUART2();
	}
}

void USART3_IRQHandler(){
	if (USART3->SR & USART_SR_RXNE){
		USART3->SR = 0;
		callbackUART3();
	}
}
