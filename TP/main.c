#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"

volatile rgb_color frame[192];

int main(){
    led_init();
    clocks_init();
    uart_init(38400);
    matrix_init();
    irq_init();
    button_init();

    while(1){
        display_frame((rgb_color*)frame);
    }
    
    return 0; 
}