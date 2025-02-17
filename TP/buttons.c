#include "buttons.h"
#include "led.h"

/* To configure a line as an interrupt source (the case of a GPIO pin), the following steps are required:
1. Configure the corresponding mask bit in the EXTI_IMR register.
2. Configure the Trigger Selection bits of the Interrupt line (EXTI_RTSR and EXTI_FTSR).
3. Configure the enable and mask bits that control the NVIC IRQ channel mapped to the
EXTI so that an interrupt coming from one of the EXTI lines can be correctly
acknowledged.
*/
void button_init(void){
    // Enable GPIOC clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // Configure PC13 as input
    GPIOC->MODER &= ~(GPIO_MODER_MODE13);

    // Map EXTI13 to PC13
    SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] & ~(SYSCFG_EXTICR4_EXTI13)) | SYSCFG_EXTICR4_EXTI13_PC;

    // 1 - Unmask EXTI13
    EXTI->IMR1 |= EXTI_IMR1_IM13;

    // 2 - Set EXTI13 to rising edge trigger
    EXTI->RTSR1 &= ~(EXTI_RTSR1_RT13);   // Disable rising edge
    EXTI->FTSR1 |= EXTI_FTSR1_FT13;      // Enable falling edge

    // 3 - Enable the processor to receive the interrupt
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

// Overwrite the default EXTI15_10_IRQHandler function
void EXTI15_10_IRQHandler(void){
    if(EXTI->PR1 & EXTI_PR1_PIF13){ // Check if an interrupt was generated on line 13
        EXTI->PR1 |= EXTI_PR1_PIF13; // If yes, we clear the bit, otherwise the interrupt would trigger continuously
        led_g_toggle();
    }
}