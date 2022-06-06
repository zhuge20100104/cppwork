#include "car.h"

#include <iostream>

Car::Car() {

}

Car::Car(float amount) {
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

void Car::dashboard() {
    std::cout << "Fuel level: " << fuel << std::endl;
    std::cout << "Speed: " << speed << std::endl;
    std::cout << "Passengers: " << passengers << std::endl;
}

Car::~Car() {
    
}