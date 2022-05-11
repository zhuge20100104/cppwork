#include "factor/factor.h"

size_t factorial(size_t n) {
    size_t result = 1;
    for(size_t i=1; i<=n; ++i) {
        result *= i;
    }
    return result;
}