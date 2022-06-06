#ifndef _FREDRIC_ABS_FACT_H_
#define _FREDRIC_ABS_FACT_H_
#include <cmath>
#include <iostream>
#include <concepts>
#include <memory>
#include <functional>

struct HotDrink{
    virtual void prepare(int volume) = 0;
};
struct Tea: HotDrink {
    void prepare(int volume) {
        std::cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon" << std::endl;
    }
};

struct Coffee: HotDrink{
    void prepare(int volume) {
        std::cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!" << std::endl;
    }
};

template <typename HotDrinkFact>
class DrinkFactory {
    HotDrinkFact factory;
public:
    DrinkFactory(HotDrinkFact fact_): factory{fact_}  {}
    std::unique_ptr<HotDrink> make_drink(){
        return factory();
    }
};

auto tea_func = []() -> std::unique_ptr<HotDrink> {
    auto tea = std::make_unique<Tea>();
    tea->prepare(200);
    return tea;
};

auto coffee_func = []() -> std::unique_ptr<HotDrink> {
    auto coffee = std::make_unique<Coffee>();
    coffee->prepare(50);
    return coffee;
};

using FactType = std::function<std::unique_ptr<HotDrink>()>;
using DrinkFactType = DrinkFactory<FactType>;
#endif