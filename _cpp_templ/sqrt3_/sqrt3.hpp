#ifndef _FREDRIC_SQRT3_HPP_
#define _FREDRIC_SQRT3_HPP_

template <int N, int I=1>
class Sqrt {
    public:
        static int constexpr result = (I*I<N)?Sqrt<N, I+1>::result : I;
};

// 退出条件
template <int N>
class Sqrt<N, N> {
    public:
        static int constexpr result = N;
};


#endif