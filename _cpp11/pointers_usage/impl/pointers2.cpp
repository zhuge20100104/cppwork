#include "pointers2/pointers2.h"

int add(int* a, int* b) {
    return *a + *b;
}

void add_val(int* a, int* b, int* result) {
    *result = *a + *b;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void factorial(int* a, int* result) {
    for(int i=1; i<=*a; ++i) {
        *result *= i;
    }
}