#include "car.h"

#include <cstdlib>

int main(int argc, char* argv[]) {
    Car::show_count();
    Car car(4);
    car.accelerate();
    car.accelerate();
    car.accelerate();
    car.accelerate();
    car.dashboard();

    Car c1, c2;
    Car::show_count();

    return EXIT_SUCCESS;
}