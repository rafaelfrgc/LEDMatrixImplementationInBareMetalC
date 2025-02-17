#ifndef TIMER_H
#define TIMER_H

#include "CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include "led.h"
#include "matrix.h"

void timer_init(int);
void TIM2_IRQHandler(void);

#endif