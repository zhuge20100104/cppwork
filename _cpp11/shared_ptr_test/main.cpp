#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    std::shared_ptr<int> i{new int{10}};
    i.reset(new int{20});
    std::cout << *i << std::endl;
}