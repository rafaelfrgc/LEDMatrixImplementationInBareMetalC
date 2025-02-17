#include "memfuncs.h"

// Obs: We use char to guarantee the alignment, as a byte is the smallest unit of memory that can be accessed.
// External symbols defined by the linker script
extern char _sisr_vector;
extern char _eisr_vector;
extern char _stext;
extern char _etext;
extern char _sdata;
extern char _edata;
extern char _sbss;
extern char _ebss;

// Load address symbols (in FLASH)
extern char _isr_vector_load;
extern char _text_load;
extern char _data_load;          

// Place these functions in the .text_copy section
__attribute__((section(".bootloader")))
void copy_isr() {
    my_memcpy(&_sisr_vector, &_isr_vector_load, &_eisr_vector - &_sisr_vector);
}

__attribute__((section(".bootloader")))
void copy_text() {
    my_memcpy(&_stext, &_text_load, &_etext - &_stext);
}

__attribute__((section(".bootloader")))
void copy_data() {
    my_memcpy(&_sdata, &_data_load, &_edata - &_sdata);
}

__attribute__((section(".bootloader")))
void init_bss(){
    my_memset(&_sbss, 0, &_ebss - &_sbss);
}