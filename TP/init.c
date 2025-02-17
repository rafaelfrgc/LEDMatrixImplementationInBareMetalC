extern int _sbss;
extern int _ebss;

void init_bss(){
    int* start_bss = &_sbss;
    int* end_bss = &_ebss;

    while(start_bss < end_bss){
        *start_bss++ = 0;
    }
}