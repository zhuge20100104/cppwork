#include "ref_vs_pointer/ref_vs_pointer.h"

#include <iostream>

void swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void swap(int& x, int& y) {
    int tmp = x;
    x = y;
    y = tmp;
}

void print(int* ptr) {
    if(nullptr != ptr) {
        std::cout << *ptr << std::endl;
    }
}

void print(int& ref) {
    std::cout << ref << std::endl;
}