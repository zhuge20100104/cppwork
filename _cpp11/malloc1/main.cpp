#include <iostream>

void test_malloc() {
    int* p = static_cast<int*>(malloc(sizeof(int)));
    *p = 5;
    std::cout << *p << std::endl;
    free(p);
    p = nullptr;
}

void test_alloc() {
    int* p = static_cast<int*>(calloc(1, sizeof(int)));
    if(p == nullptr) {
        std::cout << "Memory alloc failure" << std::endl;
        return;
    }
    *p = 10;
    std::cout << *p << std::endl;
    free(p);
    p = nullptr;
}

void test_malloc_array() {
    int* p = static_cast<int*>(malloc(5 * sizeof(int)));
    for(int i=0; i<5; ++i) {
        p[i] = i;
    }

    for(int i=0; i<5; ++i) {
        std::cout << p[i] << std::endl;
    }

    free(p);
    p = nullptr;
}

int main(int argc, char* argv[]) {
    test_malloc();
    test_alloc();
    test_malloc_array();
    return EXIT_SUCCESS;
}