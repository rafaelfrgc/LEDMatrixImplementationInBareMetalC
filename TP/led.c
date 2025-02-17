#include "led.h"

unsigned int* const GPIO_CLOCK_ENABLE = (unsigned int*) (0x40021000 + 0x4C); // (0x40021000 is the base address of the RCC peripheral, 0x4C is the offset of the RCC_AHB2ENR)

unsigned int* const GPIOB_MODER = (unsigned int*) 0x48000400;
unsigned int* const GPIOB_BSRR  = (unsigned int*) 0x48000418; // Offset of the GPIOx_BSRR register is 0x18 by default

unsigned int* const GPIOC_MODER = (unsigned int*) 0x48000800;
unsigned int* const GPIOC_BSRR  = (unsigned int*) 0x48000818;

/*
Sets up the GPIOB and GPIOC pins and clocks for the LEDs
Observation: I decided in this function to not set the GPIOC pin 9 as output, because if it is set as output, the LED will start on as soon the led_init() function is called, which
makes the idea of controlling the order of the LEDs to be turned on/off in the main function unnecessarily complicated and redundant. So, I decided to leave the GPIOC pin 9 in the 
reset state (default state) and only enable port C clock. With this, I can set the GPIOC pin 9 as output in the led_state() function, which is the one responsible for turning on/off 
the yellow and blue LEDs. Also, I decided to do the operations as bit manipulation instead of just assigning the values to the registers, as I think this provides more control of the operations
not needing to overwrite the entire register value.
 */
void led_init(void){
    *GPIO_CLOCK_ENABLE |= (1U << 1);    // For GPIOB
    *GPIO_CLOCK_ENABLE |= (1U << 2);    // For GPIOC
    *GPIOB_MODER       &= ~(1U << 29);  // Set GPIOB pin 14 as output
}

// Turns on the LED by setting the 14th bit of the GPIOB_BSRR register to 1 
void led_g_on(void){
    *GPIOB_BSRR |= (1U << 14); 
}

// Turns off the LED by setting the 30th bit of the GPIOB_BSRR to 1 (reset value)
void led_g_off(void){
    *GPIOB_BSRR |= (1U << 30); 
}

void led_state(state s){
    switch(s){
        case LED_OFF:
            *GPIOC_MODER |= (1U << 19);  // Set GPIOC pin 9 to reset state (default state)
            break;
        case LED_YELLOW:
            *GPIOC_MODER &= ~(1U << 19); // Set GPIOC pin 9 as output
            *GPIOC_BSRR  |= (1U << 9);
            break;
        case LED_BLUE:
            *GPIOC_MODER &= ~(1U << 19);
            *GPIOC_BSRR  |= (1U << 25);
            break;
    }
}
