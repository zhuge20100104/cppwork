#include <iostream>
#include <cstring>  // for std::size_t

template <typename T>
concept small = (T::size < 4);

template <typename T>
concept can_meow = requires (T value) {
    value.meow();
};

template <typename T>
concept cat_type = small<T> and can_meow<T>;

namespace ns {
    template <small T>
    constexpr auto func() {return 1;}

    template <can_meow T>
    constexpr auto func() {return 2;}

    template <cat_type T>
    constexpr auto func() {return 3;}
};

// kitty_cat 符合cat_type概念
struct kitty_cat {
    constexpr static std::size_t size = 2;
    void meow();
};

template <typename T>
concept magic_cat_type = cat_type<T> and requires (T value) {
    value.do_magic();
};

struct magic_kitty_cat {
    constexpr static std::size_t size = 3;
    void meow();
    void do_magic();
};

namespace ns {
    template <magic_cat_type T>
    constexpr auto func() {return 42; }
};

auto main(int argc, char** argv) -> int {
    static_assert(cat_type<kitty_cat>);
    auto kitty_func_res = ns::func<kitty_cat>();
    std::cout << "Kitty func res: " << kitty_func_res << "\n";

    static_assert(magic_cat_type<magic_kitty_cat>);
    auto magic_func_res = ns::func<magic_kitty_cat>();
    std::cout << "Magic func res: " << magic_func_res << "\n";
    return EXIT_SUCCESS;
}
