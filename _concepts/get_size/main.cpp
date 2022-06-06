#include <iostream>
#include <cstring>

template <typename T>
requires requires {T::size;}
auto get_size() {
    return T::size;
}


struct small_type {
    constexpr static std::size_t size = 3;
};

struct big_type {
    constexpr static std::size_t size = 5; 
};

int main(int argc, char* argv[]) {
    auto small_size = get_size<small_type>();
    auto big_size = get_size<big_type>();

    std::cout << "Small size: " << small_size << "\n";
    std::cout << "Big size: " << big_size << "\n";
    
    return EXIT_SUCCESS;
}