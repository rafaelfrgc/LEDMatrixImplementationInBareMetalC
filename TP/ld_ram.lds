MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1M
    SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
    SRAM2 (rwx) : ORIGIN = 0x10000000, LENGTH = 32K
}

_stack = ORIGIN(SRAM1) + LENGTH(SRAM1);

SECTIONS
{
    /* Interrupt service routine table. This must be explicitly initialized here as the program expects to find the interrupt handlers table
    in the beggining of the RAM */
    .isr_vector : 
    {
        KEEP(*(.isr_vector)) /* KEEP tells the linker to keep the section even if it seems unused */
    } > FLASH

    .text :
    {
        *(.text*) /* Includes all .text subsections */
    } > FLASH

    .rodata :
    {
        *(.rodata*)
    } > FLASH

    .data :
    {
        *(.data*)
    } > FLASH

    .bss :
    {
        _sbss = .; /* Define a global symbol at bss section start */
        *(.bss*)
        *(COMMON)
        _ebss = .; /* Define a global symbol at bss section end */
    } > SRAM1
}

ENTRY(_start)
