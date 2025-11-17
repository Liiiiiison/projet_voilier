#include "stm32f10x.h"
#include "MyGirouette.h"
#include "MyTimer.h"
int alpha = 0;

// La Girouette est sur le channel 1
void Init_Girouette(TIM_TypeDef *Timer){
	MyTimer_Base_Init(Timer , 360 , 2);
}


int lire_angle(void) {
	/*
	int angle = 0;
	Tant que (Changement de Phase_A / Front montant){
		if (Phase_B){
			angle = angle + 1;
		} else {
			angle = angle - 1;
		}
	if (I){
		angle = 0;
	}
	}
	return angle;
	*/
	return 0;
}	

int convertir_angle(int a){
	int result = a/2;
	if (result > 180){
		result = result - 360;
	} else if (result < -180) { 
		result = 360 + result;
	}
	return result;
}

void ajuster_voile(TIM_TypeDef * Timer, int alpha){
	// Calcul pour theta et envoyer theta.
	int theta = 0;
	if (alpha > 0) {
		if (alpha < 45){
			theta = 0;
		} else {
			theta = (90/135)*(alpha - 45);
		}
	} else {
		if (alpha > -45) {
			theta = 0;
		} else {
			theta = (90/135)*(alpha + 45);
		}
	}
	my_PWM_set_cycle(Timer, 1, ((1.5 + (theta* 1/180))*20));
}