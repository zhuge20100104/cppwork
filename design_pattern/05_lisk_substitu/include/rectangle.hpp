#ifndef _FREDRIC_RECTANGLE_HPP_
#define _FREDRIC_RECTANGLE_HPP_

#include <concepts>
#include <utility>
#include <iostream>

template <typename T>
concept RectGetType = requires (const T value) {
    {value.get_width()} -> std::convertible_to<int>;
    {value.get_height()} -> std::convertible_to<int>;
    {value.area()} -> std::convertible_to<int>;
};

template <typename T>
concept RectSetType = requires (T value) {
    value.set_width(std::declval<int>());
    value.set_height(std::declval<int>());
};

template <typename T>
concept RectType = RectGetType<T> && RectSetType<T>;

struct Rect {
    class Factory {
        public:
            static Rect create_rect(int width, int height) {
                return Rect{width, height};
            }
            static Rect create_square(int size) {
                return Rect{size, size};
            }
    };
    private:
        Rect(int width_, int height_): width{width_}, height{height_} {}
    protected:
        int width, height;
    public:
       
        int get_width() const {
            return width;
        }

        void set_width(int width) {
            this->width = width;
        } 

        int get_height() const {
            return height;
        }

        void set_height(int height) {
            this->height = height;
        } 

        int area() const {
            return width * height;
        }
};



template <RectType RectT>
void process(RectT& r) {
    // 子类不能替换父类，违背了 里氏替换原则
    int width = r.get_width();
    r.set_height(10);
    std::cout << "Expect area = " << (width * 10) 
     << " got " << r.area() << "\n";
}

#endif