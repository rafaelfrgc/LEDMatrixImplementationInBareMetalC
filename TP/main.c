#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"

int main(){
    clocks_init();
    led_init();
    uart_init();
    matrix_init();
    irq_init();
    button_init();

    while(1){
        test_image();
    }
}