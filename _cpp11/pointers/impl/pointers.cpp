#include "pointers/pointers.h"

std::shared_ptr<int> create_pointer(const int val) {
    return std::shared_ptr<int>(new int(val));
}