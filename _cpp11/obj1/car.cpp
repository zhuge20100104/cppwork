#include <iostream>
#include "car.h"

car::car(): fuel{0.0f}, speed{0.0f}, passengers{0} {}

car::car(float fuel_): fuel{fuel_}, speed{0.0f}, passengers{0} {}

void car::fill_fuel(float amount) {
    fuel += amount;
}

void car::accelerate() {
    ++speed;
    fuel -= 0.5f;
}

void car::brake() {
    speed = 0;
}

void car::add_passengers(int count) {
    passengers += count;
}

void car::dashboard() {
    std::cout << "Fuel: " << fuel << std::endl;
    std::cout << "Speed: " << speed << std::endl;
    std::cout << "Passengers: " << passengers << std::endl;
}
