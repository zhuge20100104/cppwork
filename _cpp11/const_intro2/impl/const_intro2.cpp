#include "const_intro2/const_intro2.h"

#include <iostream>


void print(const int* ptr) {
    std::cout << *ptr << std::endl;
}

void print(const int& ref) {
    std::cout << ref << std::endl;
}


const std::shared_ptr<int> get_const_ele() {
    const int CHUNK_SIZE = 512;
    const std::shared_ptr<int>  ptr {new int(CHUNK_SIZE)};
    return ptr;
}