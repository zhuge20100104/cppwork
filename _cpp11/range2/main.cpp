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

    for(const auto& x: {1, 2, 3, 4}) {
        std::cout << x << " ";
    }

    std::cout << std::endl;

    int* beg = &arr[0];
    int* end = &arr[5];
    
    std::cout << "第一次打印" << std::endl;
    while(beg != end) {
        std::cout << *beg << " ";
        ++beg;
    }

    std::cout << std::endl;

    std::cout << "第二次打印" << std::endl;

    beg = std::begin(arr);
    end = std::end(arr);
    while(beg != end) {
        std::cout << *beg << " ";
        ++beg;
    }

    std::cout << std::endl;

    return EXIT_SUCCESS;
}