#ifndef IRQ_H
#define IRQ_H

#include "CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include "CMSIS/Include/core_cm4.h" // For VTOR

// Defines the extern variables to reference the start and stack addresses
extern uint32_t _start;
extern uint32_t _stack;

// Define the default handler for each IRQ
#define MAKE_DEFAULT_HANDLER(IRQ_Handler) \
    void __attribute__((weak)) IRQ_Handler(void) { \
        __disable_irq(); /*Disable all interruptions*/ \
        while(1); /*Enters infinite loop*/ \
}

void irq_init(void);

#endif