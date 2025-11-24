#include "stm32f10x.h"
#include "MyGirouette.h"
#include "MyTimer.h"
#include "GPIO.h"
int alpha = 0;
int last_phase_a = 0;
int last_phase_b = 0;

extern int lire_phase_A;
extern int lire_phase_B;
extern int lire_I;

// La Girouette est sur le channel 1
void Init_Girouette(TIM_TypeDef * Timer,TIM_TypeDef *TimerA,TIM_TypeDef *TimerB){
	
	configureInputGPIO(GPIOA,0x2,1); // En alternate push-pull
	configureInputGPIO(GPIOA,0x2,4); 
	MyTimer_Base_Init(Timer , 360 , 2);
	MyTimer_Base_Init(TimerA , 360 , 2);
	MyTimer_Base_Init(TimerB , 360 , 2);
	Conf_capture_phaseAB(TimerA,TimerB);
}

int lire_angle(void) {
	int angle = 0;
	int phase_a = lire_phase_A;
	int phase_b = lire_phase_B;
	int I = lire_I;
	if (phase_a && !last_phase_a){
		if (phase_b){
			angle = angle + 1;
		} else {
			angle = angle - 1;
		}
		if (I){
			angle = 0;
		} 
	}
	last_phase_a = phase_a;
	last_phase_b = phase_b;
	
	return (angle/2); // Renvoie une valeur entre [-360;360]
}	

int convertir_angle(int a){ // Plage de valeurs [0;180]
	int result = a;
	if (result < 0) { 
		result = (-result);	
	} 
	if (result > 180){
		result = 360 - result;
	}
	
	return result;
}

void ajuster_voile(TIM_TypeDef * Timer, int alpha){ // alpha entre [0;180]
	// Calcul pour theta et envoyer theta.
	int theta = 0;
	if (alpha < 45){
		theta = 0;
	} else {
		theta = (90/135)*(alpha - 45);
	}
	my_PWM_set_cycle(Timer, 1, ((1 + (theta* 1/90))*20));
}