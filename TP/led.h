#ifndef LED_H
#define LED_H

#include "CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"

typedef enum { 
    LED_OFF,
    LED_YELLOW,
    LED_BLUE,
} state;

void led_init(void);
void led_g_on(void);
void led_g_off(void);
void led_state(state s);

#endif