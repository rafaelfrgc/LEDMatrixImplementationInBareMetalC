#include "CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include "uart.h" 

void uart_init(){

    // Gurantees that  USART1 is disabled before configuration
    USART1->CR1 &= ~USART_CR1_UE;

    // Enables clock for GPIOB and USART1
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; 
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;   

    // Resets the bits for GPIOB pins 6 and 7 and sets them to alternate function mode
    GPIOB->MODER &= ~(GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE7_Msk);
    GPIOB->MODER |= (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);

    // To select which alternate function we desire, we need to set the correct bits in the AFR register (AF7)
    GPIOB->AFR[0] |= (GPIO_AFRL_AFSEL6_Msk | GPIO_AFRL_AFSEL7_Msk);
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6_3 | GPIO_AFRL_AFSEL7_3); 

    // Select the clock source as PCLK
    RCC->CCIPR &= ~(RCC_CCIPR_USART1SEL); 

    // Reset trough the APB2RSTR register
    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
    RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST);

    // Baud rate set to 115200
    USART1->BRR = 694; // This value is obtained by dividing the clock frequency (PCLK) by the desired baud rate as described in the datasheet

    // Set 16x oversampling (OVER8 bit to 0)
    USART1->CR1 &= ~(USART_CR1_OVER8);

    // Set data length to 8 bits (M[1:0] bits to 00)
    USART1->CR1 &= ~(USART_CR1_M | USART_CR1_M0);

    // Set 1 stop bit (STOP[1:0] bits to 00)
    USART1->CR2 &= ~(USART_CR2_STOP);

    // Enable the transmitter and receiver
    USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);

}

// Sends a char to the serial port
void uart_putchar(uint8_t c){
    // Wait until the TXE flag is set to 1
    while ((USART1->ISR & USART_ISR_TXE) == 0);
    USART1->TDR = c; // Write data
}

// Gets a char from the serial port
uint8_t uart_getchar(){
    // Wait until the RXNE flag is set to 1
    while ((USART1->ISR & USART_ISR_RXNE) == 0);
    return (uint8_t)USART1->RDR; // Read data
}

// Sends a string to the serial port
void uart_puts(const char *s){
    while((uint8_t)*s != '\0'){
        uart_putchar((uint8_t)*s++);
    }
    uart_putchar((uint8_t)'\r');
    uart_putchar((uint8_t)'\n');
}

// Gets a string from the serial port
void uart_gets(char *s, size_t size){
    // While the null terminator hasn't been reached, keep reading characters
    while(size > 1){                
        *s = uart_getchar();
        if(*s == '\n' || *s == '\r'){ // If the character is a newline or carriage return, break the loop
            break;
        }
        s++;
        size--;
    }
    *s = '\0';
}
