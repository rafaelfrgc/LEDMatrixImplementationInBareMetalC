#include "led.h"
#include "clocks.h"
#include "uart.h"

#define BUFFER_SIZE 100

void test_uart(){
    uint8_t c;
    char buffer[BUFFER_SIZE];

    uart_puts("Type something to see it echoed back: ");
    c = uart_getchar();
    uart_puts("You typed: ");
    uart_putchar(c);
    uart_puts("");
    
    uart_puts("Now type a string and press Enter:");
    uart_gets(buffer, BUFFER_SIZE);
    uart_puts("You typed:");
    uart_puts(buffer);
}

void sum(){
    unsigned int total = 0;
    unsigned int counter = 0;

    uart_puts("Starting to receive bytes and calculate sum...");

    // Receive 1000 bytes (default set by checksum.py) and calculate the sum
    while(counter < 1000){
        total += uart_getchar();
        counter++;
    }

    /* This line is here just to facilitate the printing of the total variable in GDB. As in the guide there were no explicit instructions
    saying that we should send back the sum value, and as I searched it a bit, it seemed quite complicated to convert the types accordingly
    (int to char) and so i let this line so I could set a break point in gdb and check if the value of total matched the one sent by checksum.py
    */
    uart_puts("Finished summing! You can check the total!"); 
}

int main(){
    clocks_init();
    uart_init();
    uart_puts("Hello World! This is USART1 sending you a message.");
    
    sum();

    while(1){
        test_uart();
    }
}