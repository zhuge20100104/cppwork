#include "car.h"

#include <iostream>

int Car::total_count = 0;

Car::Car() {
    ++ total_count;
}

Car::Car(float amount) {
    ++ total_count;
    fuel = amount;
}


void Car::fill_fuel(float amount) {
    fuel += amount;
}

void Car::accelerate() {
    ++ speed;
    fuel -= 0.5f;
}

void Car::brake() {
    speed = 0;
}

void Car::add_passengers(int count) {
    passengers += count;
}

void Car::dashboard() const {
    std::cout << "Fuel level: " << fuel << std::endl;
    std::cout << "Speed: " << speed << std::endl;
    std::cout << "Passengers: " << passengers << std::endl;
}

void Car::show_count() {
    std::cout << "Total car count: " << total_count << std::endl;
}

Car::~Car() {
    -- total_count;
}