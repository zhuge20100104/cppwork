#include <iostream>

#include <cstdlib>

int main(int argc, char* argv[]) {

    int arr[] = {1, 2, 3, 4, 5};
    for(int i=0; i<5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    for(const auto& x: arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // range based for loop 也可以循环初始化列表，初始化列表也是一个range
    for(const auto& x: {1, 2, 3, 4}) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}