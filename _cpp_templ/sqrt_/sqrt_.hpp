#ifndef _FREDRIC_SQRT__HPP_
#define _FREDRIC_SQRT__HPP_

template <int N, int LO=1, int HI=N>
class Sqrt {
    public:
        static int constexpr  MID = (LO + HI + 1)/ 2;

        static int constexpr result = (N < MID * MID) ? Sqrt<N, LO, MID-1>::result : Sqrt<N, MID, HI>::result;
};


// Low=High的特化
// 特化名要写完整
template <int N, int M>
class Sqrt<N, M, M> {
    public:
        static int constexpr result = M;
};
#endif 