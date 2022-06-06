#ifndef _FREDRIC_PROPERTY_PROXY_HPP_
#define _FREDRIC_PROPERTY_PROXY_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <functional>

template <typename T>
struct Property {
    T value;

    Property(T value) {
        *this = value;
    }

    operator T() {
        return value;
    }

    T operator=(T new_value) {
        std::cout << "Assignment\n";
        return value = new_value;
    }
};



template <typename T>
struct Property2 {
    T value;
    std::function<bool(T)> func;

    Property2(T value, std::function<bool(T)> func_=nullptr): func{func_} {
        *this = value;
    }

    operator T() {
        return value;
    }

    T operator=(T new_value) {
        std::cout << "Assignment\n";
        if(nullptr == func || func(new_value)) {
            value = new_value;
        } else {
            std::cout << "validation failed, return source value\n";
        }
        return value;
    }
};

struct Creature {
    Property2<int> strength{10, [](int ele){
        return ele > 10 && ele <20;
    }};

    Property2<int> agility {5};
};

#endif