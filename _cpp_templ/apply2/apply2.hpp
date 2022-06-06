#ifndef _FREDRIC_APPLY_2_HPP_
#define _FREDRIC_APPLY_2_HPP_

#include "typeop1.hpp"
#include <iostream>


template <typename T>
using RefArg = typename TypeOp<T>::RefT;

template <typename T>
void apply(RefArg<T> arg, void (*func)(T&)) {
    func(arg);
}

#endif