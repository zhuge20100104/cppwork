#include "ref_demo2/ref_demo2.h"

void add(int a, int b, int& result) {
    result = a + b;
}

void factorial(int a, int& result) {
    for(int i=1; i<=a; ++i) {
        result *= i;
    }
}


void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}
