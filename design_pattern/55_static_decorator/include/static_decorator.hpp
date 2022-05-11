#ifndef _FREDRIC_STATIC_DECORATOR_HPP_
#define _FREDRIC_STATIC_DECORATOR_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <cstdint>


struct Shape {
    virtual std::string str() const = 0;
};

// concept约束，T的基类型必须是Shape
template <typename T>
concept IsShape = std::is_base_of<Shape, T>::value;


struct Circle: Shape {
    float redius;
    Circle() {

    }

    Circle(float redius_): redius{redius_} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << "A circle of redius " << redius;
        return oss.str();
    }

    // resize方法在子类中无法被调用
    void resize(float factor) {
        redius *= factor;
    }
};


struct Square: Shape {
    float side;
    Square() {

    }

    Square(float side_): side{side_} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << "A square with side " << side;
        return oss.str();
    }
};

template <IsShape T>
struct ColoredShape: T {
    std::string color;
    ColoredShape() {

    }

    template <typename ... Args>
    ColoredShape(std::string const& color_, Args&& ... args): T(std::forward<Args>(args)...), color{color_} {

    }

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

template <IsShape T>
struct TransparentShape: T {
    uint8_t transparency;

    template <typename ... Args>
    TransparentShape(uint8_t const transparency_, Args&& ... args): T(std::forward<Args>(args)...), transparency{transparency_} {

    }

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has a "
            << transparency/(float)255.0f * 100.0f
            << "% transparency";
        return oss.str();
    }
};

#endif