#ifndef _FREDRIC_SQRT2_HPP_
#define _FREDRIC_SQRT2_HPP_

#include "promote1/ifthenelse.hpp"

template <int N, int LO=1, int HI=N>
class Sqrt {
    public:
        static int constexpr MID = (LO+HI+1) / 2;

        using SubT = typename IfThenElse<(N<MID*MID), Sqrt<N, LO, MID-1>, Sqrt<N, MID, HI>>::ResultT;
        
        static int constexpr result = SubT::result;
};

template <int N, int M>
class Sqrt<N, M, M> {
    public:
        static int constexpr result = M;
};

#endif