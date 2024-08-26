#include "cpucycles.h"

unsigned long long cpucycles(void) {
    unsigned long long result;
    __asm__ __volatile__(".byte 15;.byte 49;shlq $32,%%rdx;orq %%rdx,%%rax" : "=a" (result) : : "%rdx");
    return result;
}
