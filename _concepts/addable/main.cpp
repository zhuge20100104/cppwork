#include <iostream>
#include <cassert>

template <typename T>
concept addable = requires (T value) {
    {value + value};
};

template <addable T>
T add(T a, T b) {
    return a + b;
}

int main(int argc, char* argv[]) {
    auto value = add(3, 4);
    assert(7 == value);
    return EXIT_SUCCESS;
}