#include "memfuncs.h"

// Variables declared in .bss to see if init_bss() worked.
int global_var1;
int global_var2;

void test_my_memcmp(){
    unsigned char src[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned char dest[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    global_var1 = 50;

    global_var1 = my_memcmp(dest, src, 0); // Should return 0

    global_var1 = 24;    

    global_var1 = my_memcmp(dest, src, 10); // Should return 0
        

    unsigned char src2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned char dest2[10] = {0, 1, 2, 3, 2, 5, 6, 7, 8, 8};

    global_var1 =  my_memcmp(dest2, src2, 10); // Should return dest2[9] - src2[9]
}


void test_my_memcpy(){
    unsigned char src_buffer[50];
    unsigned char dest_buffer[50];
    unsigned int n = 50;

    for (unsigned int i = 0; i < n; i++) {
        src_buffer[i] = 0x00;
    }

    my_memcpy(dest_buffer, src_buffer, n);
}

void test_my_memset() {
    unsigned char buffer[50];
    unsigned char value = 0xAA;
    unsigned int n = 50;

    for (unsigned int i = 0; i < n; i++) {
        buffer[i] = 0x00;
    }
    my_memset(buffer, value, n);

}

void test_my_memmove() {

    // Test 1: Non-Overlapping Copy
    {
        char src1[] = "abcdefghij";
        char dest1[10];

        // Initialize dest1
        for (int i = 0; i < 10; i++) {
            dest1[i] = 0x00;
        }

        my_memmove(dest1, src1, 10); 

        // Compare dest1 with src1
        if (my_memcmp(dest1, src1, 10) == 0) global_var1++; // Test 1 passed
    }

    // Test 2: Overlapping Copy (dest > src)
    {
        char buffer2[20] = "abcdefghij";        // Larger buffer to allow overlap

        my_memmove(buffer2 + 2, buffer2, 6);    // Move 6 bytes from buffer2 to buffer2 + 2

        char expected2[] = "ababcdefij";        // Expected outcome: "ababcdefij"

        // Compare the first 10 bytes of buffer2 with expected2
        if (my_memcmp(buffer2, expected2, 10) == 0) global_var1++; // Test 2 passed
    }

    // Test 3: Overlapping Copy (dest < src)
    {
        char buffer3[20] = "abcdefghij";        // Initialize buffer3 with "abcdefghij"

        // Perform my_memmove: move 6 bytes from buffer3 + 2 to buffer3
        my_memmove(buffer3, buffer3 + 2, 6);    // Moves 'c','d','e','f','g','h' to buffer3[0..5]

        char expected3[] = "cdefghghij";        // Corrected expected outcome: "cdefghghij"

        // Compare the first 10 bytes of buffer3 with expected3
        if (my_memcmp(buffer3, expected3, 10) == 0) {
            global_var1++;                       // Test 3 passed
        }
    }
}

int fibo(int n){
    if (n <= 0) return n;
    return fibo(n-1) + fibo(n-2);
}

void main(){


    test_my_memcpy();
    test_my_memset();
    test_my_memcmp();
    test_my_memmove();
    
    while(1){}
}
