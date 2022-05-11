#ifndef _FREDRIC_ACCUM2_HPP_
#define _FREDRIC_ACCUM2_HPP_
#include "accum_traits2.hpp"

template <typename T>
inline typename accumulation_traits<T>::AccT accum(T const* begin, T const* end) {
    using AccT = typename accumulation_traits<T>::AccT;
    AccT total = AccT();

    while(begin != end) {
        total += *begin;
        ++begin;
    }
    return total;
}

#endif