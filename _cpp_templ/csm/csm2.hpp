#ifndef _FREDRIC_CSM2_HPP_
#define _FREDRIC_CSM2_HPP_

#include "csm1.hpp"

#include <cstddef>
#include <cassert>
#include <cstring>

// 对于非对象类型，按位拷贝
template <typename T>
class BitOrClassCSM<T, true>: public BitOrClassCSM<T, false>  {
    static void copy_n (T const* src, T* dst, size_t n) {
        // copy n items onto n other ones
        std::memcpy((void*)dst, (void*)src, n*sizeof(T));
    }

    static void copy_init_n (T const* src, void* dst, size_t n) {
        // copy n items onto uninitialized storage
        std::memcpy(dst, (void*)src, n*sizeof(T));
    }

    static void move_n (T* src, T* dst, size_t n) {
        // move n items onto n other ones
        assert(src != dst);
        std::memcpy((void*)dst, (void*)src, n*sizeof(T));
    }

    static void move_init_n (T const* src, void* dst, size_t n) {
        // move n items onto uninitialized storage
        assert(src != dst);
        std::memcpy(dst, (void*)src, n*sizeof(T));
    }  
};

#endif