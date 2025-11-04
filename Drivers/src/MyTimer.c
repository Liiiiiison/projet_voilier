#include "stm32f10x.h"
#include "MyTimer.h"

void (*TIM1_func) (void);
void (*TIM2_func) (void);
void (*TIM3_func) (void);
void (*TIM4_func) (void);

void MyTimer_Base_Init ( TIM_TypeDef *Timer , unsigned short ValARR , unsigned short ValPSC ){

	if(Timer == TIM1) {
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}
	
	if (Timer == TIM2) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}
	
	if (Timer == TIM3){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}
	
	if (Timer == TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	
	Timer->PSC = (ValPSC - 1);
	Timer->ARR = (ValARR - 1);
	
}

void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void (*IT_function) (void)) {

		if(Timer == TIM1) {
			//code 25 = TIM1_UP_IRQn
			NVIC_EnableIRQ(TIM1_UP_IRQn);
			NVIC_SetPriority(TIM1_UP_IRQn,Prio);
			TIM1_func = IT_function;
		}
		
		if (Timer == TIM2) {
			//code 28 = TIM2_IRQn
			NVIC_EnableIRQ(TIM2_IRQn);
			NVIC_SetPriority(TIM2_IRQn,Prio);
			TIM2_func = IT_function;
		}
		
		if (Timer == TIM3){
			//code 29 = TIM3_IRQn
			NVIC_EnableIRQ(TIM3_IRQn);
			NVIC_SetPriority(TIM3_IRQn,Prio);
			TIM3_func = IT_function;
		}
		
		if (Timer == TIM4){
			//code 30 = TIM4_IRQn
			NVIC_EnableIRQ(TIM4_IRQn);
			NVIC_SetPriority(TIM4_IRQn,Prio);
			TIM4_func = IT_function;
		}
		Timer->DIER |= TIM_DIER_UIE;
		
}
;

void MyTimer_PWM_init(TIM_TypeDef * Timer , char Channel) {
		if(Timer == TIM1) {
			TIM1->BDTR |= TIM_BDTR_MOE;
		}
		if (Channel==1){
			Timer->CCMR1 &= ~TIM_CCMR1_OC1M ;
			Timer->CCMR1 |= TIM_CCMR1_OC1M_1 ;
			Timer->CCMR1 |= TIM_CCMR1_OC1M_2 ;
			Timer->CCMR1 |= TIM_CCMR1_OC1PE ;
			Timer->CCMR1 &=~TIM_CCMR1_CC1S ;
			Timer->CCER |= TIM_CCER_CC1E ;
		}
		if (Channel==2){
			Timer->CCMR1  &= ~TIM_CCMR1_OC2M ;
			Timer->CCMR1 |= TIM_CCMR1_OC2M_1 ;
			Timer->CCMR1 |= TIM_CCMR1_OC2M_2 ;
			Timer->CCMR1 |= TIM_CCMR1_OC2PE ;
			Timer->CCMR1 &=~TIM_CCMR1_CC2S ;
			Timer->CCER |= TIM_CCER_CC2E ;
		}
		if (Channel==3){
			Timer->CCMR2  &= ~ TIM_CCMR2_OC3M ;
			Timer->CCMR2 |= TIM_CCMR2_OC3M_1 ;
			Timer->CCMR2 |= TIM_CCMR2_OC3M_2 ;
			Timer->CCMR2 |= TIM_CCMR2_OC3PE ;
			Timer->CCMR2 &=~TIM_CCMR2_CC3S ;
			Timer->CCER |= TIM_CCER_CC3E ;
		}
		if (Channel==4){
			Timer->CCMR2  &= ~TIM_CCMR2_OC4M ;
			Timer->CCMR2 |= TIM_CCMR2_OC4M_1 ;			
			Timer->CCMR2 |= TIM_CCMR2_OC4M_2 ;
			Timer->CCMR2 &=~TIM_CCMR2_CC4S ;
			Timer->CCMR2 |= TIM_CCMR2_OC4PE ;
			Timer->CCER |= TIM_CCER_CC4E ;
		}
	};


void my_PWM_set_cycle(TIM_TypeDef * Timer , char Channel, int percent){
	int arr = Timer->ARR ;
	int ccr = (arr*percent)/100 ;
	if (Channel==1){
		Timer->CCR1=ccr;
	}
	if (Channel==2){
		Timer->CCR2=ccr;
	}
	if (Channel==3){
		Timer->CCR3=ccr;
	}
	if (Channel==4){
		Timer->CCR4=ccr;
	}
}


void TIM1_UP_IRQHandler(void){
	TIM1->DIER &= ~TIM_DIER_UIE;
	TIM1_func();
}

void TIM2_IRQHandler(void) {
	TIM2->DIER &= ~TIM_DIER_UIE;
	TIM2_func();
}

void TIM3_IRQHandler(void) {
	TIM3->DIER &= ~TIM_DIER_UIE;
	TIM3_func();
}

void TIM4_IRQHandler(void) {
	TIM4->DIER &= ~TIM_DIER_UIE;
	TIM4_func();
}



