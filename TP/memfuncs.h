#ifndef MEMFUNCS_H
#define MEMFUNCS_H

// Obs: We use unsigned to guarantee the expected full byte value range.
typedef unsigned int size_t; 

__attribute__((section(".bootloader"))) void* my_memcpy(void* dest, void* src, size_t size);
__attribute__((section(".bootloader"))) void* my_memset(void* dest, size_t val, size_t size);
__attribute__((section(".bootloader"))) int my_memcmp(void* dest, void* src, size_t size);
__attribute__((section(".bootloader"))) void* my_memmove(void* dest, void* src, size_t size);

#endif
