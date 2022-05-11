// 静态多态
#include <iostream>
#include <tuple>

// 希望模板类型 s 有个 draw方法
template <typename T>
concept Drawable = requires(T s) {
    s.draw();
};

class Rectangle {
    public:
        auto draw() const {
            std::cout << "Draw an rectangle\n";
        }
};

class Circle {
    public:
        auto draw() const {
            std::cout << "Draw a circle\n";
        }
};

class Square {
    public:
        auto draw() const {
            std::cout << "Draw a square\n";
        }
};

template <size_t Index=0, Drawable... Ts>
constexpr auto drawAll(std::tuple<Ts ...> const& shapes) {
    if constexpr(Index != sizeof...(Ts)) {
        std::get<Index>(shapes).draw();
        drawAll<Index+1>(shapes);
    }
}


int main(int argc, char* argv[]) {
    drawAll(std::make_tuple(Rectangle{}, Circle{}, Square{}));
    return EXIT_SUCCESS;
}
