#ifndef _FREDRIC_RPARAM_HPP_
#define _FREDRIC_RPARAM_HPP_

#include "promote1/ifthenelse.hpp"
#include "is_class_t/is_class_t.hpp"

template <typename T>
struct RParam {
    using Type = typename IfThenElse<
        IsClassT<T>::NO, 
        T,
        T const&
    >::ResultT;
};


#endif