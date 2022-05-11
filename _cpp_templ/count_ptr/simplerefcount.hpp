#ifndef _FREDRIC_SIMPLE_REF_COUNT_HPP_
#define _FREDRIC_SIMPLE_REF_COUNT_HPP_

#include "allocator.hpp"

#include <cstddef>

// 简单引用计数策略类
class SimpleReferenceCount {
    private:
        std::size_t* counter;
    
    public:
        SimpleReferenceCount() {
            counter = nullptr;
        }

        template <typename T>
        void init(T*) {
            counter = alloc_counter();
            *counter = 1;
        }

        template <typename T>
        void dispose(T*) {
            dealloc_counter(counter);
        }

        template <typename T>
        void increment(T*) {
            ++*counter;
        }

        template <typename T>
        void decrement(T*) {
            --*counter;
        }

        template <typename T>
        bool is_zero(T*) {
            return *counter == 0;
        }
};

#endif