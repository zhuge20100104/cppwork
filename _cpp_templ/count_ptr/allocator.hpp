#ifndef _FREDRIC_ALLOCATOR_HPP_
#define _FREDRIC_ALLOCATOR_HPP_

#include <cstddef>

std::size_t* alloc_counter() {
    return ::new std::size_t;
}

void dealloc_counter(std::size_t* ptr) {
    ::delete ptr;
}

#endif