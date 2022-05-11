#include "car.h"
#include <cstdlib>

int main(int argc, char* argv[]) {

    car c;
    c.fill_fuel(6);
    c.accelerate();
    c.accelerate();
    c.accelerate();
    c.accelerate();
    c.dashboard();
    
    return EXIT_SUCCESS;
}