MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1M
    SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
    SRAM2 (rwx) : ORIGIN = 0x10000000, LENGTH = 32K
}

_stack = ORIGIN(SRAM2) + LENGTH(SRAM2);

SECTIONS
{
    /* Interrupt service routine table. This must be explicitly initialized here as the program expects to find the interrupt handlers table
    in the beggining of the RAM */
    .isr_vector : 
    {
        _sisr_vector = .;
        KEEP(*(.isr_vector)) /* KEEP tells the linker to keep the section even if it seems unused */
        _eisr_vector = .;
    } > SRAM1 AT> FLASH /* AT> FLASH tells the linker to place the section in the FLASH memory and copy it to the SRAM */

    .text :
    {
        _stext = .;
        *(.text*) /* Includes all .text subsections */
        _etext = .;
    } > SRAM1 AT> FLASH

    .rodata :
    {
        *(.rodata*)
    } > FLASH

    .data :
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > SRAM1 AT> FLASH

    .bss :
    {
        _sbss = .; /* Define a global symbol at bss section start */
        *(.bss*)
        *(COMMON)
        _ebss = .; /* Define a global symbol at bss section end */
    } > SRAM1

    /* Code responsible for copying sections, must stay in flash, as this guarantees that the code will not be overwritten */
    .bootloader :
    {
        *(.bootloader*)
    } > FLASH

    /* These symbols mark the load addresses in FLASH for copying */
    _isr_vector_load = LOADADDR(.isr_vector);
    _text_load = LOADADDR(.text);
    _data_load = LOADADDR(.data);
}

ENTRY(_start)
