#ifndef _FREDRIC_PROMOTION1_HPP_
#define _FREDRIC_PROMOTION1_HPP_

#include "ifthenelse.hpp"

// Promotion 对象逻辑，
// 如果 T1占用内存大 取 T1，否则取T2,
// 如果 T1 == T2， 取void
template <typename T1, typename T2>
class Promotion {
    public:
        using ResultT = typename IfThenElse<(sizeof(T1) > sizeof(T2)), 
                                            T1,
                            typename IfThenElse<(sizeof(T1) < sizeof(T2)),
                                            T2,
                                            void
                            >::ResultT>::ResultT;
};

#endif