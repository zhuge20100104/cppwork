// 静态多态
#include <iostream>
#include <type_traits>
#include <tuple>

// 希望模板类型 s 有个 draw方法
template <typename T>
concept drawable_single = requires(T s) {
    s.draw(1);
};

template <typename T>
concept drawable_double = requires(T s) {
    s.draw(1, 1);
};

template <typename T>
concept drawable = drawable_single<T> || drawable_double<T>;

class Rectangle {
    public:
        auto draw(int width, int height) const {
            std::cout << "Draw an rectangle, Width: "<< width << " height: " << height << "\n";
        }
};

class Circle {
    public:
        auto draw(int radius) const {
            std::cout << "Draw a circle, radius: "<< radius << "\n";
        }
};

class Square {
    public:
        auto draw(int width) const {
            std::cout << "Draw a square, width: " << width << "\n";
        }
};

template <size_t Index=0, drawable... Ts>
constexpr auto drawAll(std::tuple<Ts ...> const& shapes) {
    if constexpr(Index != sizeof...(Ts)) {
        auto shape = std::get<Index>(shapes);
        // 如果是 Rectangle类型，直接draw rectangle
        if constexpr(std::is_same<decltype(shape), Rectangle>::value) {
            shape.draw(4, 3);
        // 否则是 Square 或者 Circle类型， draw square或者circle
        } else {
            shape.draw(3);
        }
        // Recursively draw all shapes
        drawAll<Index+1>(shapes);
    }
}


int main(int argc, char* argv[]) {
    drawAll(std::make_tuple(Rectangle{}, Circle{}, Square{}));
    return EXIT_SUCCESS;
}
