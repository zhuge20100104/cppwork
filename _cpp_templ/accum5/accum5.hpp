#ifndef _FREDRIC_ACCUM5_HPP_
#define _FREDRIC_ACCUM5_HPP_

#include "accumtraits.hpp"

template <typename T, typename AT = accumulation_traits<T>>
class Accum {
    public:
        static typename AT::AccT accum(T const* beg, T const* end) {
            typename AT::AccT total = AT::zero();
            while(beg != end) {
                total += *beg;
                ++beg;
            }
            return total;
        }
};

#endif