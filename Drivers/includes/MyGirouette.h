#include "stm32f10x.h"

#ifndef MYGIROUETTE_H
#define MYGIROUETTES_H
void Init_Girouette(TIM_TypeDef *Timer);
int lire_angle(void);
int convertir_angle(int a);
void ajuster_voile(TIM_TypeDef * Timer, int angle);

#endif