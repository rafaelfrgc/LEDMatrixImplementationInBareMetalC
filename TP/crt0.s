.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

// This is needed to tell the linker to put the code in the bootloader section in the flash, otherwise it would
// not be able to load the rest of the code;
.section .bootloader, "ax", %progbits

.thumb_func
_start:
    ldr sp, =_stack // Loads the stack pointer with the address of the top of the stack
    bl copy_isr
    bl copy_text
    bl copy_data
    bl init_bss
    bl main 
    
_exit:
    b _exit             // Infinite loop
    