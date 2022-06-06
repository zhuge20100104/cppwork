#ifndef _FREDRIC_ACCUM5_HPP_
#define _FREDRIC_ACCUM5_HPP_

#include "accumtraits.hpp"

template <typename T>
inline typename accumulation_traits<T>::AccT accum(T const* beg, T const* end) {
    using AccT = typename accumulation_traits<T>::AccT;
    AccT total = accumulation_traits<T>::zero();

    while(beg != end) {
        total += *beg;
        ++beg;
    }
    return total;
}
#endif