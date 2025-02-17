#include "uart.h" 

// This variable is used to allow the reading of the frame only when a 0xFF byte is received, impeding the reading of "noise"
static char allowReading = 0;

void uart_init(int baudrate){

    // Gurantees that  USART1 is disabled before configuration
    USART1->CR1 &= ~USART_CR1_UE;

    // Enables clock for GPIOB and USART1
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // Resets the bits for GPIOB pins 6 and 7 and sets them to alternate function mode
    GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODE6_Msk)) | (GPIO_MODER_MODE6_1);
    GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODE7_Msk)) | (GPIO_MODER_MODE7_1);

    // To select which alternate function we desire, we need to set the correct bits in the AFR register (AF7)
    GPIOB->AFR[0] = (GPIOB->AFR[0] | (GPIO_AFRL_AFSEL6_Msk)) & ~(GPIO_AFRL_AFSEL6_3);
    GPIOB->AFR[0] = (GPIOB->AFR[0] | (GPIO_AFRL_AFSEL7_Msk)) & ~(GPIO_AFRL_AFSEL7_3);

    // Select the clock source as PCLK
    RCC->CCIPR &= ~(RCC_CCIPR_USART1SEL); 

    // Reset trough the APB2RSTR register
    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
    RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST);

    // Baud rate set to the value wished
    USART1->BRR = 80000000/baudrate; // This value is obtained by dividing the clock frequency (PCLK) by the desired baud rate as described in the datasheet

    USART1->CR1 = 0; // Reset the CR1 register

    // Set 1 stop bit (STOP[1:0] bits to 00)
    USART1->CR2 &= ~(USART_CR2_STOP);

    // Enable the transmitter, receiver and RXNEIE, which enables USART to generate an interrupt whenever (RDR) contains unread data
    USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE | USART_CR1_RXNEIE);

    NVIC_EnableIRQ(USART1_IRQn);    
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

extern volatile uint8_t frame[192]; // 64 LEDs with 3 bytes of data for each

// Is called every time data is received in the USART1 to handle the byte received
void USART1_IRQHandler(void){
    static int index = 0;
    uint8_t byte = uart_getchar();

    if(USART1->ISR & USART_ISR_ORE || USART1->ISR & USART_ISR_FE){ // Checks if there was an overrun or framing error
        USART1->ICR |= (USART_ICR_ORECF | USART_ICR_FECF); // Clears the error flags
        allowReading = 0;
        return; // Returns if there was an error, so the byte is not processed
    }
    
    if (byte == 0xFF){ // Marks the start of a new frame
        index = 0;
        allowReading = 1; // Allows the reading of the frame
        return;
    } 

    if (allowReading == 1){
        frame[index] = byte;
        index++;
        if(index == 192) allowReading = 0; // If the frame is complete, stop reading, and wait for the next 0xFF byte
    }
}