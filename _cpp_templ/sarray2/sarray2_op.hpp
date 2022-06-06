#ifndef _FREDRIC_SARRAY2_OP_HPP_
#define _FREDRIC_SARRAY2_OP_HPP_

#include "sarray2.hpp"

template <typename T>
inline SArray<T>& SArray<T>::operator+=(SArray<T> const& a) {
    for(std::size_t k=0; k<size(); ++k) {
        (*this)[k] += a[k];
    }
    return *this;
}

template <typename T>
SArray<T>& SArray<T>::operator*=(SArray<T> const& a) {
    for(std::size_t k=0; k<size(); ++k) {
        (*this)[k] *= a[k];
    }
    return *this;
}

template <typename T>
SArray<T>& SArray<T>::operator*=(T const& s) {
    for(std::size_t k=0; k<size(); ++k) {
        (*this)[k] *= s;
    }
    return *this;
}

#endif