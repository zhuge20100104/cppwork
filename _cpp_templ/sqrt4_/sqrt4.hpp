#ifndef _FREDRIC_SQRT4_HPP_
#define _FREDRIC_SQRT4_HPP_

#include "promote1/ifthenelse.hpp"

template <int N>
class Value {
    public:
        static int constexpr result = N;
};


template <int N, int I=1>
class Sqrt {
    public:
        using SubT = typename IfThenElse<
            (I*I < N),
            Sqrt<N, I+1>,
            Value<I>
        >::ResultT;

        static int constexpr result = SubT::result;
};
#endif