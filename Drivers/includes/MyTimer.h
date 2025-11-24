#ifndef MY_TIMER
#define MY_TIMER
#include "stm32f10x.h"

#define MyTimer_Base_Start(Timer) (Timer->CR1 |= TIM_CR1_CEN)
#define MyTimer_Base_Stop(Timer) (Timer->CR1 &= ~TIM_CR1_CEN)

/**
*****************************************************************************************
* @brief
* @param -> Paramè t r e sous forme d ’ une s t r u c t u r e ( son a d re s se ) con ten an t l e s
i n f o rm a ti o n s de base
* @Note -> F onc ti on à l a n c e r s y s t ématiquement avan t d ’ a l l e r pl u s en dé t a i l dans l e s
con f pl u s f i n e s (PWM, codeur i n c . . . )
*************************************************************************************************
*/

void MyTimer_Base_Init (TIM_TypeDef *Timer , unsigned short ValARR , unsigned short ValPSC );

/**
**************************************************************************************************
* @brief
* @param : - TIM_TypeDef * Timer : Timer conce rne
- cha r P ri o : de 0 a 15
* @Note : La f o n c ti o n MyTime r_Base_ Init doit avoir ete lancee au prealable
**************************************************************************************************
*/

void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void (*IT_function) (void));

/**
* @brief
* @param ....
* @Note Active le channel spécifié suTimerr le timer sécifié
* la gestion de la configuration I/O n’est pas faite dans cette fonction
* ni le réglage de la période de la PWM (ARR, PSC)
*/
void MyTimer_PWM_init(TIM_TypeDef * Timer , char Channel) ;


void my_PWM_set_cycle(TIM_TypeDef * Timer , char Channel, int percent) ;



#endif