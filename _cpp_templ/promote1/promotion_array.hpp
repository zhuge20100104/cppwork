#ifndef _FREDRIC_PROMOTION_ARRAY_HPP_
#define _FREDRIC_PROMOTION_ARRAY_HPP_

#include "promotion1.hpp"
#include "promotion2.hpp"
#include "promotion3.hpp"

template <typename T>
class Array {};

// 针对Array的特化
template <typename T1, typename T2>
class Promotion<Array<T1>, Array<T2>> {
    public:
        using ResultT = Array<typename Promotion<T1, T2>::ResultT>;
};

// 针对同类型 Array的特化
template <typename T>
class Promotion<Array<T>, Array<T>> {
    public:
        using ResultT = Array<typename Promotion<T, T>::ResultT>;
};

#endif