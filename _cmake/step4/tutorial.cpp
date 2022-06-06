#include "tutorial_config.h"

#ifdef USE_MYMATH
    #include "math_functions.h"
#endif

#include <cmath>
#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << argv[0] <<  " Version " << Tutorial_VERSION_MAJOR << "."
            << Tutorial_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return EXIT_FAILURE;
    }

    double const input_val = std::stod(argv[1]);

#ifdef USE_MYMATH
    double const ouput_val = mysqrt(input_val);
#else
    double const ouput_val = sqrt(input_val);
#endif
    
    std::cout << "The sqrt root of " << input_val << " is: " << ouput_val << std::endl;
    return EXIT_SUCCESS;
}