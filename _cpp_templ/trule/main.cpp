#include "holder.hpp"

#include <iostream>

class Something {};

void read_something(Something* x) {

}

Trule<Something> load_something() {
    Holder<Something> result {new Something};
    read_something(result.get());
    return result;
}

int main(int argc, char* argv[]) {

    Holder<Something> ptr {load_something()};
    return EXIT_SUCCESS;
}