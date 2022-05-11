#ifndef _FREDRIC_PRODUCT_HPP_
#define _FREDRIC_PRODUCT_HPP_

#include <string>
#include <iostream>
#include <concepts>
#include <utility>
#include <vector>

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product {
    std::string name;
    Color color;
    Size size;
};

template <typename T>
concept SpecType = requires (T value){
    {value.is_satisfied(std::declval<Product*>())} -> std::convertible_to<bool>;
};

struct BetterFilter {
    template <SpecType Specification>
    std::vector<Product*> filter(std::vector<Product*> const& items,Specification& spec) {
        std::vector<Product*> result;
        for(auto& item: items) {
            if(spec.is_satisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

struct ColorSpec {
    Color color;
    ColorSpec(Color color_): color{color_} {}

    bool is_satisfied(Product* item) {
        return item->color == color;
    }
};

struct SizeSpec {
    Size size;
    SizeSpec(Size size_): size{size_} {}

    bool is_satisfied(Product* item) {
        return item->size == size;
    }
};

template <SpecType Spec1, SpecType Spec2>
struct AndSpec {
    Spec1 first;
    Spec2 second;

    AndSpec(Spec1 first_, Spec2 second_): first{first_}, second{second_} {}

    bool is_satisfied(Product* item) {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

template <SpecType Spec1, SpecType Spec2>
AndSpec<Spec1, Spec2> operator&&(Spec1 const& spec1, Spec2 const& spec2) {
    return AndSpec<Spec1, Spec2>(spec1, spec2);
}
#endif