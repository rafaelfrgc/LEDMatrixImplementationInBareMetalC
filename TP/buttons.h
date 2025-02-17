#ifndef  BUTTONS_H
#define  BUTTONS_H

#include "CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"

void button_init(void);
void EXTI15_10_IRQHandler(void);

#endif