#include <cstring>
#include <iostream>

struct kitty_cat {
    constexpr static std::size_t size = 2;
    void meow() {}
};

template <typename T>
concept small = (T::size < 4);

template <typename T>
concept can_meow = requires (T value) {
    value.meow();
};

template <typename T>
concept cat_type = small<T> and can_meow<T>;

template <small T> 
int func() {
    return 1;
}

template <can_meow T>
int func() {
    return 2;
}

template <cat_type T>
int func() {
    return 3;
}


auto main() -> int {
    static_assert(cat_type<kitty_cat>);
    auto func_res = func<kitty_cat>();
    std::cout << "Func result: " << func_res << "\n";
    return EXIT_SUCCESS;
}