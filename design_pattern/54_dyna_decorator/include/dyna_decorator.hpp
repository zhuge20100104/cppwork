#ifndef _FREDRIC_DYNA_DECORATOR_HPP_
#define _FREDRIC_DYNA_DECORATOR_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <cstdint>

struct Shape {
    virtual std::string str() const = 0;
};

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

struct ColoredShape: Shape {
    Shape& shape;
    std::string color;

    ColoredShape(Shape& shape_, std::string const& color_): shape{shape_}, color{color_} {

    }

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

struct TransparentShape: Shape {
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape_, uint8_t transparency_): shape{shape_}, transparency{transparency_} {

    }

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has " << 
            static_cast<float>(transparency)/255.0f * 100.0f
            << "% transparency";
        return oss.str();
    }
};
#endif