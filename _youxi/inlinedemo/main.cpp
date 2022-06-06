#include <iostream>

inline int add(int a, int b) {
    return a + b;
}

int main() {
    auto c = add(1.0, 3);
    std::cout << "c = " << c << std::endl;
}
