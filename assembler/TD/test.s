/* Assembler directives */

.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

/* ................................................ */

/* Label declarations */ 

.EQU word, 0xdeadbeef
.EQU start_address, 0x10000000
.EQU copy_address, 0x10000300
.EQU counter, 64
.EQU string_copy_address, 0x10000A00

/* ................................................ */

/* Beginning of the program */
_start:
    ldr sp, =0x20018000             @ loads the stack pointer with the address of the top of the stack
    ldr r0, =start_address          @ r0 will store the address where the memory will be filled
    ldr r1, =word                   @ r1 will store the value that will be written to memory
    ldr r3, =copy_address           @ r3 will store the address where the memory will be copied
    mov r2, #counter                @ r2 will store the number of words to be written/copied and act as a counter

    bl init_memory                  @ jumps to init_memory
    bl copy_memory                  @ jumps to copy_memory

    ldr r0, =myString               @ loads the address of the string to be copied in r0
    ldr r1, =string_copy_address    @ loads the address where the string will be copied in r1

    bl copy_string                  @ jumps to copy_string    

    end:
        b end                       @ infinite loop


/* Data declaration section */
.data
    myString:
        .string "Bonjour le monde!"  @ Declaration of the string to be copied

/* ................................................ */

/* Procedure declaration */

@ Procedure: init_memory
@ Parameters:
@ r0: starting_address
@ r1: value
@ r2: size in words

    init_memory:
        push {r0, r2}           @ Saves the states of registers before modification

    init_memory_loop:      
        str r1, [r0], #4        @ Writes the value to memory and increments the address
        subs r2, r2, #1         @ Decrements the counter
        bne init_memory_loop    @ Continues the loop until the counter reaches 0
        pop {r0, r2}            @ Returns the states of registers after modification
        bx lr

@ Function: copy_memory
@ Parameters:
@ r0: starting_address
@ r3: copy_address
@ r1: value
@ r2: size in words

    copy_memory:
    push {r0, r1, r2, r3}
    
    copy_memory_loop:
        ldr r1, [r0], #4            @ Loads the value from the source address and increments the address
        str r1, [r3], #4            @ Writes the value to the destination address and increments the address
        subs r2, r2, #1             @ Decrements the counter
        bne copy_memory_loop        @ Continues the loop until the counter reaches 0
        pop {r0, r2, r3} 
        bx lr

@ Function: copy_string
@ Parameters:
@ string: label representing the string address
@ r0: string address
@ r1: address to copy string to
@ r2: used to compare if the string is finished or not
  
    copy_string:
        PUSH {r0, r1, r2}

    copy_string_loop:
        ldrb r2, [r0], #1              @ Loads the byte from the source address and increments r0
        strb r2, [r1], #1              @ Stores the byte to the destination address and increments r1
        cmp r2, #0                     @ Verifies if the byte is null
        bne copy_string_loop           @ Continues the loop until the byte is null
        POP {r0, r1, r2}
        bx lr                       

/* ................................................ */
