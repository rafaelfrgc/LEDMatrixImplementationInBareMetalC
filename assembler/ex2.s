@ .......................................................................................... @

.bss                // .bss is a directive that tells the assembler to allocate space for uninitialized data.

.align 2            // .align is a directive that tells the assembler to align the next instruction on a 4-byte boundary.   

// .global is a directive that tells the assembler to make the symbol a visible global symbol.
.global a           
.global b
.global c

// Variable declaration
a:
    .space 4
b:
    .space 4
c:  
    .space 4

.text               // .text is a directive that tells the assembler to switch to the text section.
.align 2  

@ .......................................................................................... @

ldr r0, =a          // Load the address of a into r0.
ldr r1, =c          // Load the address of c into r1.

ldr r3, [r0]        // Load the value of a into r3.
ldr r4, [r1]        // Load the value of c into r4.

add r3, r3, r4      // Add the value of c to the value of a and store the result in r3.
str r3, [r0]        // Store the result back in a.
ldr r4, [r1]        // Load the value of c into r4.

ldr r2, =b          // Load the address of b into r2.
ldr r5, [r2]        // Load the value of b into r5.

add r5, r5, r4      // Add the value of c to the value of b and store the result in r5.
str r5, [r2]        // Store the result back in b.
ldr r4, [r1]        // Load the value of c into r4.

/* Obs: note that the operation ldr r4, [r1] is done twice in the code. This is because, supposing that for example that a and c 
point to the same memory address, the value of a would be changed in the first operation, but on the second operation, the value
of c would be needed again, but it would be the same as before the operation that changed the value of a. So, c needs to be
updated with the value of a and c after the first operation, considering that a and c point to the same memory address
*/
