#include "led.h"

/*
Sets up the GPIOB and GPIOC pins and clocks for the LEDs
Observation: I decided in this function to not set the GPIOC pin 9 as output, because if it is set as output, the LED will start on as soon the led_init() function is called, which
makes the idea of controlling the order of the LEDs to be turned on/off in the main function unnecessarily complicated and redundant. So, I decided to leave the GPIOC pin 9 in the 
reset state (default state) and only enable port C clock. With this, I can set the GPIOC pin 9 as output in the led_state() function, which is the one responsible for turning on/off 
the yellow and blue LEDs. Also, I decided to do the operations as bit manipulation instead of just assigning the values to the registers, as I think this provides more control of the operations
not needing to overwrite the entire register value.
 */
void led_init(void){
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN;    // For GPIOB and C
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE14_Msk) | (GPIO_MODER_MODE14_0); // Set GPIOB pin 14 as output
}

// Turns on the LED by setting the 14th bit of the GPIOB_BSRR register to 1 
void led_g_on(void){
    GPIOB->BSRR = GPIO_BSRR_BS14; 
}


// Turns off the LED by setting the 30th bit of the GPIOB_BSRR to 1 (reset value)
void led_g_off(void){                                       
    GPIOB->BSRR = GPIO_BSRR_BR14;  
}

void led_state(state s){
    switch(s){
        case LED_OFF:
            GPIOC->MODER = (GPIOC->MODER | GPIO_MODER_MODE9_Msk);  // Set GPIOC pin 9 to reset state (default state)
            break;
        case LED_YELLOW:
            GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODE9_0; // Set GPIOC pin 9 as output
            GPIOC->BSRR = GPIO_BSRR_BS9;
            break;
        case LED_BLUE:
            GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODE9_0; // Set GPIOC pin 9 as output
            GPIOC->BSRR = GPIO_BSRR_BR9;
            break;
    }
}
