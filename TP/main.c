#include "led.h"
#include "clocks.h"

void main(){

    clocks_init();
    led_init();

    while(1){

        led_g_on();

        for(int i = 0; i < 100000; i++){
            asm volatile("nop");
        }

        led_g_off();
        led_state(LED_YELLOW);

        for(int i = 0; i < 100000; i++){
            asm volatile("nop");
        }

        led_state(LED_BLUE);

        for(int i = 0; i < 100000; i++){
            asm volatile("nop");
        }

        led_state(LED_OFF);
    }
}
