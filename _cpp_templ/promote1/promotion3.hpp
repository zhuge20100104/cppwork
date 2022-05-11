#ifndef _FREDRIC_PROMOTION3_HPP_
#define _FREDRIC_PROMOTION3_HPP_
#include "promotion1.hpp"

#define MK_PROMOTION(T1, T2, Tr)    \
    template <> \
    class Promotion<T1, T2> {   \
        public: \
            using ResultT = Tr; \
    };  \
    template <> \
    class Promotion<T2, T1> {   \
        public: \
            using ResultT = Tr; \
    };  \


MK_PROMOTION(bool, char, int)
MK_PROMOTION(bool, unsigned char, int)
MK_PROMOTION(bool, signed char, int)

#undef MK_PROMOTION

#endif