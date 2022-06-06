#ifndef _FREDRIC_SARRAY1_OPS_HPP_
#define _FREDRIC_SARRAY1_OPS_HPP_

#include "sarray1.hpp"

template <typename T>
SArray<T> operator+(SArray<T> const& a, SArray<T> const& b) {
    SArray<T> result(a.size());
    for(std::size_t k=0; k<a.size(); ++k) {
        result[k] = a[k] + b[k];
    }
    return result;
}

template <typename T>
SArray<T> operator*(SArray<T> const& a, SArray<T> const& b) {
    SArray<T> result(a.size());
    for(std::size_t k=0; k<a.size(); ++k) {
        result[k] = a[k] * b[k];
    }
    return result;
}


// 标量左乘
template <typename T>
SArray<T> operator*(T const& s, SArray<T> const& b) {
    SArray<T> result(b.size());
    for(std::size_t k=0; k<b.size(); ++k) {
        result[k] = s * b[k];
    }
    return result;
}

// 标量右乘
template <typename T>
SArray<T> operator*(SArray<T> const& a, T const& s) {
    SArray<T> result(a.size());
    for(std::size_t k=0; k<a.size(); ++k) {
        result[k] = a[k] * s;
    }
    return result;
}


// 标量左加
template <typename T>
SArray<T> operator+(T const& s, SArray<T> const& b) {
    SArray<T> result(b.size());
    for(std::size_t k=0; k<b.size(); ++k) {
        result[k] = s + b[k];
    }
    return result;
}

// 标量右加
template <typename T>
SArray<T> operator+(SArray<T> const& a, T const& s) {
    SArray<T> result(a.size());
    for(std::size_t k=0; k<a.size(); ++k) {
        result[k] = a[k] + s;
    }
    return result;
}

#endif