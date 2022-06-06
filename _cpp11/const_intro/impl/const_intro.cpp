#include "const_intro/const_intro.h"

namespace ConstIntro {
    double area(double radius) {
        return PI * radius * radius; 
    }

    double circumference(double radius) {
        return 2.0 * PI * radius;
    }
}; // namespace name
