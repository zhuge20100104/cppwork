#include <concepts>
#include <iostream>

template <typename T>
concept can_behave = requires (T value) {
    value.behave();
};

template <typename T>
concept has_hp_getter = requires (const T value) {
    {value.get_hp()} -> std::convertible_to<unsigned int>;
};

template <typename T>
concept entity = can_behave<T> and has_hp_getter<T>;

template <entity entity_type>
void use_entity(entity_type&& entity_) {
    auto hp = entity_.get_hp();
    std::cout << "Entity hp is: " << hp << "\n";
}

struct entity_impl {
    void behave() {}
    int get_hp() const {
        return 42;
    }
};


auto main(int argc, char** argv) -> int {
    static_assert(entity<entity_impl>);
    use_entity(entity_impl{});
    return EXIT_SUCCESS;
}