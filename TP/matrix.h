#ifndef  MATRIX_H
#define  MATRIX_H

#include "CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include "CMSIS/Include/cmsis_gcc.h"

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;

#define RST(state) GPIOC->BSRR |= (state ? GPIO_BSRR_BS3 : GPIO_BSRR_BR3)
#define LAT(state) GPIOC->BSRR |= (state ? GPIO_BSRR_BS4 : GPIO_BSRR_BR4)
#define SB(state)  GPIOC->BSRR |= (state ? GPIO_BSRR_BS5 : GPIO_BSRR_BR5)
#define SCK(state) GPIOB->BSRR |= (state ? GPIO_BSRR_BS1 : GPIO_BSRR_BR1)
#define SDA(state) GPIOA->BSRR |= (state ? GPIO_BSRR_BS4 : GPIO_BSRR_BR4)

#define ROW0(state) GPIOB->BSRR |= (state ? GPIO_BSRR_BS2 : GPIO_BSRR_BR2)
#define ROW1(state) GPIOA->BSRR |= (state ? GPIO_BSRR_BS15 : GPIO_BSRR_BR15)
#define ROW2(state) GPIOA->BSRR |= (state ? GPIO_BSRR_BS2 : GPIO_BSRR_BR2)
#define ROW3(state) GPIOA->BSRR |= (state ? GPIO_BSRR_BS7 : GPIO_BSRR_BR7)
#define ROW4(state) GPIOA->BSRR |= (state ? GPIO_BSRR_BS6 : GPIO_BSRR_BR6)
#define ROW5(state) GPIOA->BSRR |= (state ? GPIO_BSRR_BS5 : GPIO_BSRR_BR5)
#define ROW6(state) GPIOB->BSRR |= (state ? GPIO_BSRR_BS0 : GPIO_BSRR_BR0)
#define ROW7(state) GPIOA->BSRR |= (state ? GPIO_BSRR_BS3 : GPIO_BSRR_BR3)

// This symbol is a reference to the start of the image data that will be linked to form the final executable. Using -nm to list symbols in the image.o file,
// with this, we can define this variable as extern, and then use it's address to access the image data and parse it into the format we are using. 
extern const uint8_t _binary_image_raw_start;  

void matrix_init(void);
void deactivate_rows();
void activate_row(int row);
void send_byte(uint8_t val);
void mat_set_row(int row, const rgb_color* val);
void init_bank0();
void test_pixels();
void test_pixels2();
void test_image();

#endif