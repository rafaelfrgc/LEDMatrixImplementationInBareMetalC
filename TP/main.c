#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"
#include "timer.h"

volatile rgb_color frame[192];

int main(){
    led_init();
    clocks_init();
    uart_init(38400);
    matrix_init();
    irq_init();
    button_init();
    timer_init(1000000/60);

    while(1){
    }
    
    return 0; 
}