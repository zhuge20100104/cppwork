#ifndef _FREDRIC_POW3B_HPP_
#define _FREDRIC_POW3B_HPP_

template <int N>
class Pow3 {
    public:
        static int const result = 3 * Pow3<N-1>::result;
};


template <>
class Pow3<0> {
    public:
        static int const result = 1;
};

#endif