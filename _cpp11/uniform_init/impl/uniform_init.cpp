#include "uniform_init/uniform_init.h"

Initializer init() {
    Initializer initializer;
    return std::move(initializer);
}