#ifndef UART_H
#define UART_H

typedef unsigned int size_t;
typedef unsigned char uint8_t;

void uart_init();
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
void uart_puts(const char *s);
void uart_gets(char *s, size_t size);

#endif