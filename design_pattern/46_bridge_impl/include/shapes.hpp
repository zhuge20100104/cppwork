#ifndef _FREDRIC_SHAPES_HPP_
#define _FREDRIC_SHAPES_HPP_

#include <concepts>
#include <utility>
#include <iostream>

template <typename T>
concept RendererType = requires (T value) {
    value.render_circle(std::declval<float>(), std::declval<float>(), std::declval<float>());
};

struct VectorRenderer {
    void render_circle(float x, float y, float redius) {
        std::cout << "Drawing a vector circle of redius: " << redius << "\n";
    }
};

struct RasterRenderer {
    void render_circle(float x, float y, float redius) {
        std::cout << "Rasterizing a circle of redius: " << redius << "\n";
    }
};

template <RendererType RendererT>
struct Circle {
    RendererT& renderer;
    Circle(RendererT& renderer_, float x_, float y_, float redius_): renderer(renderer_), x{x_}, y{y_}, redius{redius_} {

    }
    void draw() {
        renderer.render_circle(x, y, redius);
    }
    void resize(float factor) {
        redius *= factor;
    }

private:
    float x, y, redius;
};
#endif