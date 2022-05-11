#ifndef _FREDRIC_ACCUM6_HPP_
#define _FREDRIC_ACCUM6_HPP_

#include "accum_traits7.hpp"
#include "sum_policy.hpp"
#include "mul_policy.hpp"

template <typename T,
    typename Policy = sum_policy,
    typename Traits = accumulation_traits<T>>
class Accum {
    public:
        using AccT = typename Traits::AccT;

        static AccT accum(T const* beg, T const* end) {
            // 有问题，这个zero是0，加法可以，乘法乘出来是错误的
            AccT total = Traits::init();
            while(beg != end) {
                Policy::accumulate(total, *beg);
                ++beg;
            }

            return total;
        }
};

template <typename T, int initial_val=1>
using MulAccum = Accum<T, mul_policy, accumulation_traits<T, initial_val>>;

template <typename T, int initial_val=0>
using SumAccum = Accum<T, sum_policy, accumulation_traits<T, initial_val>>;

#endif