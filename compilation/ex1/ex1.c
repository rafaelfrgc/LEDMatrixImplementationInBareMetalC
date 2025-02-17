#include <stdio.h>
#include <stdlib.h>

int global_uninitialized;           // Global uninitialized variables (.bss)
int global_initialized = 15;        // Global initialized variables (.data)
const int global_const = 10;        // Global constants (.rodata)

//Function code (.text)
void test_fuction(const int* local_variable1){
    int local_variable2 = 3;
    printf("Local variable 1:    %p\n", (void*) &local_variable1);
    printf("Local variable 2:    %p\n", (void*) &local_variable2);

    // To check if the stacks grows upwards or downwards, we can compare the addresses of the local variables
    if (local_variable1 < &local_variable2) printf("The stack grows upwards\n");
    else printf("The stack grows downwards\n");
}

int main(){

    // Local variables (stack)
    int local_variable1 = 1;
    test_fuction(&local_variable1);

    // Dynamic memory (heap)
    int* heap_variable1 = (int*)malloc(sizeof(int));
    int* heap_variable2 = (int*)malloc(sizeof(int));
    int* heap_variable3 = (int*)malloc(sizeof(int));

    printf("Global uninitialized variable (.bss):   %p\n", (void*) &global_uninitialized);
    printf("Global initialized variable (.data):    %p\n", (void*) &global_initialized);
    printf("Global constant (.rodata):              %p\n", (void*) &global_const);
    printf("Function code (.text):                  %p\n", (void*) &test_fuction);
    printf("Heap variable 1:                        %p\n", (void*) heap_variable1);
    printf("Heap variable 2:                        %p\n", (void*) heap_variable2);

    free(heap_variable1);
    free(heap_variable2);

    return 0;
}