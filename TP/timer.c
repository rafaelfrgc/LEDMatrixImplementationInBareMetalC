#include "timer.h"

void timer_init(int max_us){

    // Disables TIM2 to configure it
    TIM2->CR1 &= TIM_CR1_CEN;

    // Enables TIM2 clock on the APB1 bus
    RCC->APB1ENR1 |= RCC_APB1SMENR1_TIM2SMEN;

    TIM2->SR = 0; // Clear the status register
    TIM2->CNT = 0; // Reset the counter

    // Sets counting up, edge-aligned mode, clock division and one pulse mode
    TIM2->CR1 &=  ~(TIM_CR1_DIR | TIM_CR1_CMS | TIM_CR1_CKD | TIM_CR1_OPM); 

    // Prescaler value for 1 MHz -> PSC[15:0] + 1 = fCK_PSC / fCK_CNT -> PSC[15:0] = 80 Mhz / 1 Mhz - 1 = 79
    TIM2->PSC = 79;

    TIM2->ARR = max_us; // Sets the maximum value for the counter

    TIM2->DIER |= TIM_DIER_UIE; // Enables the update interrupt

    NVIC_SetPriority(TIM2_IRQn, 1); // Sets the priority of the TIM2 interrupt to 1, so that the matrix refresh works correctly

    NVIC_EnableIRQ(TIM2_IRQn); // Enables the TIM2 interrupt

    TIM2->CR1 |= TIM_CR1_CEN; // Enables TIM2
}

extern volatile uint8_t frame[192]; // 64 LEDs with 3 bytes of data for each

void TIM2_IRQHandler(void){
    TIM2->SR &= ~TIM_SR_UIF; // Clears the update interrupt flag to allow new interrupts
    display_frame((rgb_color*)frame);
    led_g_toggle(); // Toggles the green led
}