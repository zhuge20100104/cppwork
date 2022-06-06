#ifndef _FREDRIC_PROMOTION2_HPP_
#define _FREDRIC_PROMOTION2_HPP_
#include "promotion1.hpp"

// 针对相同类型的特化
template <typename T>
class Promotion <T, T> {
    public:
        using ResultT = T;
};

#endif