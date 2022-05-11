#include "holder.hpp"
#include <iostream>

class Something {
    public:
        void perform() const {
            std::cout << "Perform..." << std::endl;
        }
};

void do_two_things() {
    Holder<Something> first{new Something};
    first->perform();

    Holder<Something> second{new Something};
    second->perform();
}

int main(int argc, char* argv[]) {
    do_two_things();

    return EXIT_SUCCESS;
}