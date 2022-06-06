#ifndef _FREDRIC_MULTI_METHOD_HPP_
#define _FREDRIC_MULTI_METHOD_HPP_


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <typeindex>
#include <functional>
#include <map>

using type_index = std::type_index;

struct GameObject;
// 全局函数，两种类型的对象相遇
void collide(GameObject& first, GameObject& second);

struct GameObject {
    virtual ~GameObject() = default;
    virtual type_index type() const = 0;

    virtual void collide(GameObject& other) {
        // 调用全局的撞击函数
        ::collide(*this, other);
    }
};

// 以下使用CRTP来获取对象的类型
template <typename T>
struct GameObjectImpl: GameObject {
    type_index type() const override {
        return typeid(T);
    }
};

struct Planet: GameObjectImpl<Planet> {};
struct Asteroid: GameObjectImpl<Asteroid> {};
struct Spaceship: GameObjectImpl<Spaceship> {};
struct ArmedSpaceship: Spaceship {
    type_index type() const override {
        return typeid(ArmedSpaceship);
    }
};

// 宇宙飞船在行星上着陆
void spaceship_planet() {
    std::cout << "Spaceship lands on planet\n";
}

// 小行星在大气中燃烧
void asteroid_planet() {
    std::cout << "Asteroid burns up in atmosphere\n";
}

// 小行星撞上宇宙飞船
void asteroid_spaceship() {
    std::cout << "Asteroid hits and destroys spaceship\n";
}

// 宇宙飞船射击小行星
void asteroid_armed_spaceship() {
    std::cout << "Spaceship shoots asteroid\n";
}

std::map<std::pair<type_index, type_index>, void(*)(void)> outcomes = {
    {{typeid(Spaceship), typeid(Planet)}, spaceship_planet},
    {{typeid(Asteroid), typeid(Planet)}, asteroid_planet},
    {{typeid(Asteroid), typeid(Spaceship)}, asteroid_spaceship},
    {{typeid(Asteroid), typeid(ArmedSpaceship)},asteroid_armed_spaceship}
};

void collide(GameObject& first, GameObject& second) {
    auto it = outcomes.find({first.type(), second.type()});
    if(it == outcomes.end()) {
        it = outcomes.find({second.type(), first.type()});
        if(it == outcomes.end()) {
            std::cout << "Objects pass each other harmlessly\n";
            return;
        }
    }
    it->second();
}

#endif