#include <iostream>

using namespace std;

void test2() {
    int a[10] = {0};
    int c[2] = {0};
    a[0] = 10;
    a[1] = 20;
}


void test() {
    int b[2] = {0};
    b[0] = 0;
    b[1] = 1;
    int a[10] = {0};
    a[0] = 10;
    a[11] = 20;    
}

int main(int argc, char* argv[]) {
    test2();
    test();
    return EXIT_SUCCESS;
}