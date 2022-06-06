#ifndef _FREDRIC_CSM1_HPP_
#define _FREDRIC_CSM1_HPP_

#include <new>
#include <cassert>
#include <cstddef>
#include "rparam/rparam.hpp"

template <typename T>
using RParamT = typename RParam<T>::Type;

// 公用主模板
template <typename T, bool Bitwise>
class BitOrClassCSM;

// 对象类型拷贝的偏特化
template <typename T>
class BitOrClassCSM<T, false> {
    public:
        static void copy(RParamT<T> src, T* dst) {
            *dst = src;
        }

        static void copy_n(T const* src, T* dst, std::size_t n) {
            for(std::size_t k=0; k<n; ++k) {
                dst[k] = src[k];
            }
        }

        // 拷贝元素到未初始化的存储段
        static void copy_init(RParamT<T> src, void* dst) {
            ::new(dst) T(*src);
        }

        // 拷贝n个元素到未初始化的存储段
        static void copy_init_n(T const* src, void* dst, std::size_t n) {
            for(std::size_t k=0; k<n; ++k) {
                ::new((void*)((T*)dst+k)) T(src[k]);
            }
        }

        // 交换两个元素
        static void swap(T* a, T* b) {
            T tmp(*a);
            *a=*b;
            *b=tmp;
        }

        // 交换n个元素
        static void swap_n(T* a, T* b, std::size_t n) {
            for(std::size_t k=0; k<n; ++k) {
                T tmp(a[k]);
                a[k] = b[k];
                b[k] = tmp;
            }
        }

        static void move(T* src, T* dst) {
            assert(src != dst);
            *dst = *src;
            src->~T();
        }

        static void move_n(T* src, T* dst, std::size_t n) {
            assert(src != dst);

            for(std::size_t k=0; k<n; ++k) {
                dst[k] = src[k];
                src[k].~T();
            }
        }

        // 移动一个元素到未初始化的内存
        static void move_init(T* src, void* dst) {
            assert(src != dst);
            ::new(dst) T(*src);
            src->~T();
        }

        // 移动n个元素到未初始化的内存
        static void move_init_n(T const* src, void* dst, std::size_t n) {
            assert(src != dst);
            for(std::size_t k=0; k<n; ++k) {
                ::new((void*)((T*)dst+k))  T(src[k]);
                src[k].~T();
            }
        }
};




#endif