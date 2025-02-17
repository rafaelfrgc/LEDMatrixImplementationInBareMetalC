.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start
_start:
    ldr sp, =0x20018000 // loads the stack pointer with the address of the top of the stack which is 0x20000000 + 96 * 1024 (96kB)
    bl init_bss
    bl main 
    bl _exit
_exit:
    b _exit             // infinite loop
    