#ifndef _FREDRIC_ACCUM6_HPP_
#define _FREDRIC_ACCUM6_HPP_

#include "accum_traits6.hpp"
#include "sum_policy.hpp"

template <typename T,
    typename Policy = sum_policy,
    typename Traits = accumulation_traits<T>>
class Accum {
    public:
        using AccT = typename Traits::AccT;

        static AccT accum(T const* beg, T const* end) {
            AccT total = Traits::zero();
            while(beg != end) {
                total += *beg;
                ++beg;
            }

            return total;
        }
};
#endif