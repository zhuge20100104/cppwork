#include <iostream>
#include <cstring>

void test_int_arr() {
    int* p = new int[5];
    for(int i=0; i<5; ++i) {
        p[i] = i;
    }

    for(int i=0; i<5; ++i) {
        std::cout << p[i] << std::endl;
    }

    delete []p;
}

void test_strings() {
    char* s = new char[4];
    ::strcpy(s, "C++");
    std::cout << s << std::endl;
    delete []s;
}


int main(int argc, char* argv[]) {
    test_int_arr();
    test_strings();
    return EXIT_SUCCESS;
}