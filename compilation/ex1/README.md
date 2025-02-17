# EX1.C README

## Idea of the code

The idea of this code is to determine the order in which each section of data is stored in memory, and determine if the stack grows up or down in a Linux x86_64 system. For that, we can write a C program with all types of variables in terms of their sections, and print the address of each variable. Then, we can analyze the order of the addresses and determine the order of the sections in memory.

## Stack growth direction

For the stack growth direction, we can declare two variables, one inside a function and another outside of it, in this way, we can assure that the second local variable (declared inside the function) will be placed in an address after the first local variable, declared before the function call. This way, by printing their addresses inside the function, and comparing their values, we can determine if the stack grows up or down.

## Conclusion

By running the code, we can see that the order of the sections in memory is: text, rodata, data, bss, heap, stack by simply comparing the addresses of the printed variables. Also, following the same ideia, we were able to verify that the stack grows down.
