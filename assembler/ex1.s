@ .......................................................................................... @

// Variable declaration
.bss                // .bss is a directive that tells the assembler to allocate space for uninitialized data.
.align 2            // .align is a directive that tells the assembler to align the next instruction on a 4-byte boundary.
.global a           // .global is a directive that tells the assembler to make the symbol a visible global symbol.

a:              
    .space 4        // .space is a directive that tells the assembler to allocate space for 4 bytes of data.


// Code to be executed declaration

.text               // .text is a directive that tells the assembler to switch to the text section.
.align 2            // .align tells the assembler to align the next instruction on a 4-byte boundary to ensure no erros occur.

.global loop

loop_begin:
    mov r0, #0      // Move the value 0 into r0 to serve as the loop counter.
    ldr r1, =a      // Load the address of a into r0.
    ldr r2, [r0]    // Load the value of a into r2 for checking.

loop_check:
    cmp r0, r2      // Compare the loop counter with the value of a.
    bgt loop_end    // Branch to loop_end if the loop counter is greater than a.,

    bl g            // Call the function g.

    add r0, r0, #1  // Increment the loop counter by 1.
    b loop_check    // Branch back to loop_check to continue the loop.

loop_end:

    bx lr           // Return from the function.

@ .......................................................................................... @
