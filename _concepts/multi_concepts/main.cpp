#include <iostream>

template <typename T>
concept has_member_content = requires (T value) {
    value.content;
};

template <typename T>
concept has_member_func = requires (T value) {
    value.func();
};

template <typename T>
concept has_element_type = requires (T) {
    typename T::element_type;
};

template <typename T>
concept small = (bool(T::size < 4));

template <typename T>
concept my_object_type =    
    has_member_content<T> and
    has_member_func<T> and
    has_element_type<T> and
    small<T>;

struct my_object_impl {
    int content {1};
    void func() {   std::cout << "Hello\n"; }
    using element_type = unsigned long;

    // 注意这里，必须要是constexpr才可以
    constexpr static auto size {3};
};

template <my_object_type T> 
void my_func(T&& obj){
    obj.func();
}

template <my_object_type T> 
void my_func(T& obj){
    obj.func();
}

int main(int argc, char* argv[]) {
    static_assert(my_object_type<my_object_impl>);
    auto obj = my_object_impl();
    my_func(my_object_impl());
    return EXIT_SUCCESS;
}