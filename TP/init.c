// Obs: We use char to guarantee the alignment, as a byte is the smallest unit of memory that can be accessed.
extern char _sbss;
extern char _ebss;

void init_bss(){
    char* start_bss = &_sbss;
    char* end_bss = &_ebss;

    while(start_bss < end_bss){
        *start_bss++ = 0;
    }
}