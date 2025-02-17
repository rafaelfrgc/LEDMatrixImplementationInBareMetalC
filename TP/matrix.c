#include "matrix.h"

// This functions is reponsible for initializing the driver to the LED Matrix.
void matrix_init(){

    // Enable clock for GPIOA, GPIOB and GPIOC
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN;

    // Set the required pins as output
    // For GPIOA: PA2, PA3, PA4, PA5, PA6, PA7, PA15
    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE2_Msk)) | (GPIO_MODER_MODE2_0);
    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE3_Msk)) | (GPIO_MODER_MODE3_0);
    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE4_Msk)) | (GPIO_MODER_MODE4_0);
    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE5_Msk)) | (GPIO_MODER_MODE5_0);
    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE6_Msk)) | (GPIO_MODER_MODE6_0);
    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE7_Msk)) | (GPIO_MODER_MODE7_0);
    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE15_Msk)) | (GPIO_MODER_MODE15_0);

    // For GPIOB: PB0, PB1, PB2
    GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODE0_Msk)) | (GPIO_MODER_MODE0_0);
    GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODE1_Msk)) | (GPIO_MODER_MODE1_0);
    GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODE2_Msk)) | (GPIO_MODER_MODE2_0);

    // For GPIOC: PC3, PC4, PC5
    GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODE3_Msk)) | (GPIO_MODER_MODE3_0);
    GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODE4_Msk)) | (GPIO_MODER_MODE4_0);
    GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODE5_Msk)) | (GPIO_MODER_MODE5_0);

    // Set the output pins as high speed
    // For GPIOA: PA2, PA3, PA4, PA5, PA6, PA7, PA15
    GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED2_Msk | GPIO_OSPEEDR_OSPEED3_Msk | GPIO_OSPEEDR_OSPEED4_Msk | GPIO_OSPEEDR_OSPEED5_Msk | GPIO_OSPEEDR_OSPEED6_Msk | GPIO_OSPEEDR_OSPEED7_Msk | GPIO_OSPEEDR_OSPEED15_Msk);

    // For GPIOB: PB0, PB1, PB2
    GPIOB->OSPEEDR |= (GPIO_OSPEEDR_OSPEED0_Msk | GPIO_OSPEEDR_OSPEED1_Msk | GPIO_OSPEEDR_OSPEED2_Msk);

    // For GPIOC: PC3, PC4, PC5
    GPIOC->OSPEEDR |= (GPIO_OSPEEDR_OSPEED3_Msk | GPIO_OSPEEDR_OSPEED4_Msk | GPIO_OSPEEDR_OSPEED5_Msk);

    // Set up initial values for RST (PC3), LAT(PC4), SB(PC5), SCK(PB1), SDA(PA4), C0(PB2), C1(PA15), C2(PA2), C3(PA7), C4(PA6), C5(PA5), C6(PB0), C7(PA3)
    RST(0);
    LAT(1);
    SB(1);
    SCK(0);
    SDA(0);

    deactivate_rows();

    for (int i = 0; i < 8000000; i++) asm volatile ("nop"); // Wait for 100ms

    RST(1);
    init_bank0();
    SB(1); // Select BANK1 as the default bank  
}

void pulse_SCK(){
    SCK(0);
    for (int i = 0; i < 2; i++) asm volatile ("nop"); // Wait for 2 cycles (aprox 25ns)
    SCK(1);
    for (int i = 0; i < 2; i++) asm volatile ("nop");
    SCK(0);
    for (int i = 0; i < 2; i++) asm volatile ("nop");
}

void pulse_LAT(){
    LAT(1);
    asm volatile ("nop"); // Aprox 12.5ns
    LAT(0);
    asm volatile ("nop");
    LAT(1);
    asm volatile ("nop");
}

void deactivate_rows(){
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

void activate_row(int row){
    switch(row){
        case 0:
            ROW0(1);
            break;
        case 1:
            ROW1(1);
            break;
        case 2:
            ROW2(1);
            break;
        case 3:
            ROW3(1);
            break;
        case 4:
            ROW4(1);
            break;
        case 5:
            ROW5(1);
            break;
        case 6:
            ROW6(1);
            break;
        case 7:
            ROW7(1);
            break;
    }
}

// This function is responsible for sending a byte that represents the instensiy of a color (2^8 = 256 levels of intensity (0-255)) 
void send_byte(uint8_t val){
    for(int i = 0; i < 8; i++){
        SDA(val & 0x80); // Extract the most significant bit from val and send it to the data line
        pulse_SCK();     // Pulse the SCK to shift the bit into the shift register
        val <<= 1;       // Shift the value to the left so the next bit can be sent
    }
}

// This function is responsible for setting the RGB values for a given row 
void mat_set_row(int row, const rgb_color* val){
    for(int i = 7; i >= 0; i--){     // Send the RGB values for each LED in the row in the correct order 
        send_byte(val[i].b);
        send_byte(val[i].g);
        send_byte(val[i].r);   
    }
    activate_row(row);              // Activate the row to display the values
    pulse_LAT();                    // Pulse the LAT pin to latch the values into the output registers
}

// This function sets all the bits for BANK0 to 1
void init_bank0(){
    SB(0);
    for(int i = 0; i < 24; i++){   // Send 144 bits to set all the bits in BANK0 to 1
        send_byte(0xFF);
    }
    pulse_LAT();
}

// This function is responsible for testing the LED Matrix by displaying a pattern of colors as shown by the schematic
void test_pixels() {
//   0 32 64 96 128 160 192 224   + 31 // Intensity
    /*  *  *  *  *  *  *  */ //R
    /*  *  *  *  *  *  *  */ //G
    /*  *  *  *  *  *  *  */ //B
    /*  *  *  *  *  *  *  */ //R
    /*  *  *  *  *  *  *  */ //G
    /*  *  *  *  *  *  *  */ //B
    /*  *  *  *  *  *  *  */ //R
    /*  *  *  *  *  *  *  */ //G

    rgb_color led_rows[8][8];

    /* Observation: row % 3 == 0 -> R, row % 3 == 1 -> G, row % 3 == 2 -> B. Also, +31 is added to the value to make the color more visible, and the first led of each row not being completely off.
    This is the max value without exceding the value of 255 (255 - (7*32)). */
    for (int row = 0; row < 8; row++) {
        for (int led = 0; led < 8; led++) {
            led_rows[row][led].r = (row % 3 == 0) ? (led * 32) + 31 : 0;
            led_rows[row][led].g = (row % 3 == 1) ? (led * 32) + 31 : 0;
            led_rows[row][led].b = (row % 3 == 2) ? (led * 32) + 31 : 0;
        }
    }

    for (int row = 0; row < 8; row++) {
        mat_set_row(row, led_rows[row]);
        for (int i = 0; i < 8000000; i++) asm volatile ("nop");
        deactivate_rows();
    }
}

// Obs: I didn't call this function in the main function because i already called the test_pixels() function, but I tried different methods to test it, and found it interesting to leave it here.
// This function is responsible for testing the LED Matrix by displaying it entireyl in one color at a time, by increasing the intensity of the color from 0 to 255
void test_pixels2(){
    rgb_color led_row[8];

    // color 0 = red, color 1 = green, color 2 = blue
    for (int color = 0; color < 3; color++) {
        for (int luminosity = 0; luminosity < 256; luminosity++) {
            switch(color){
                case 0:
                    for(int i = 0; i < 8; i++){
                        led_row[i].r = luminosity;
                        led_row[i].g = 0;
                        led_row[i].b = 0;
                    }
                    break;
                case 1:
                    for(int i = 0; i < 8; i++){
                        led_row[i].r = 0;
                        led_row[i].g = luminosity;
                        led_row[i].b = 0;
                    }
                    break;
                case 2:
                    for(int i = 0; i < 8; i++){
                        led_row[i].r = 0;
                        led_row[i].g = 0;
                        led_row[i].b = luminosity;
                    }
                    break;
            }
            for (int row = 0; row < 8; row++) {
                mat_set_row(row, led_row);
                for (int i = 0; i < 100000; i++) asm volatile ("nop"); // Wait for 100ms
            }
        }
    }
}
