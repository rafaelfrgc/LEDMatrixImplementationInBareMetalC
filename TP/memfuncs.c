#include "memfuncs.h"

// my_memcpy: copies size bytes from src to dest
void* my_memcpy (void* dest, void* src, size_t size){
    if (size == 0) return dest; // If size is 0, there is nothing to copy

    unsigned char* char_dest = (unsigned char*) dest; // Cast to unsigned char* to copy byte by byte, as per the function definition
    unsigned char* char_src = (unsigned char*) src;

    for (size_t i = 0; i < size; i++){     // Copy byte by byte
        char_dest[i] = char_src[i];
    }
    return dest;
}

// my_memset: sets size bytes in dest to val
void* my_memset (void* dest, size_t val, size_t size){
    if (size == 0) return dest;

    unsigned char* char_dest = (unsigned char*) dest;

    for (size_t i = 0; i < size; i++){
        char_dest[i] = val;
    }
    return dest;
}

// my_memcmp: compares size bytes of dest and src
int my_memcmp (void* dest, void* src, size_t size){
    if(size == 0) return 0; 

    unsigned char* char_dest = (unsigned char*) dest;
    unsigned char* char_src = (unsigned char*) src;

    for (size_t i = 0; i < size; i++){     
        if (char_dest[i] != char_src[i]) return char_dest[i] - char_src[i]; //If different, return difference
    }
    return 0; //If all bytes are the same, return 0
}

// my_memmove: copies size bytes from src to dest, even if they overlap
void* my_memmove(void* dest, void* src, size_t size){
    if (size == 0 || dest == src) return dest; // If size is 0 or dest and src are the same, there is nothing to copy

    unsigned char* char_dest = (unsigned char*) dest;
    unsigned char* char_src = (unsigned char*) src;

    if (char_dest < char_src || char_dest >= (char_src + size)){ // If dest is before src, or they don't overlap, copy from the beginning to the end
        for (size_t i = 0; i < size; i++){   
            char_dest[i] = char_src[i];
        }
    } 
    else { //If dest is after src, copy from the end to the beginning, to avoid memory corruption
        for (size_t i = size; i > 0; i--){     
            char_dest[i-1] = char_src[i-1];
        }
    }
    return dest;
}
