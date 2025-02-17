MEMORY
{
    SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
}

SECTIONS
{
    .text :
    {
        *(.text*) /* Includes all .text subsections */
    } > SRAM1

    .rodata :
    {
        *(.rodata*)
    } > SRAM1

    .data :
    {
        *(.data*)
    } > SRAM1

    .bss :
    {
        _sbss = .; /* Define a global symbol at bss section start */
        *(.bss*)
        *(COMMON)
        _ebss = .; /* Define a global symbol at bss section end */
    } > SRAM1
}

ENTRY(_start)
