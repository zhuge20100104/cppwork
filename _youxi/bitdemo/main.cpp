#include <iostream>

struct Bit {
    unsigned bit: 1;
};  

int main() {

    Bit b;
    b.bit = 0;
    std::cout << b.bit << std::endl;
}
