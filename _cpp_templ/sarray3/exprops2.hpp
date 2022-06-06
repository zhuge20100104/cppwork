#ifndef _FREDRIC_EXPR_OPS2_HPP_
#define _FREDRIC_EXPR_OPS2_HPP_

#include "exprops1.hpp"
#include "array.hpp"
#include "a_scalar.hpp"

template <typename T, typename R1, typename R2>
Array<T, A_Add<T, R1, R2>> operator+ (Array<T, R1> const& a, Array<T, R2> const& b) {
    return Array<T, A_Add<T, R1, R2>>(A_Add<T, R1, R2>(a.rep(), b.rep()));
}



template <typename T, typename R1, typename R2>
Array<T, A_Mult<T, R1, R2>> operator* (Array<T, R1> const& a, Array<T, R2> const& b) {
    return Array<T, A_Mult<T, R1, R2>>(A_Mult<T, R1, R2>(a.rep(), b.rep()));
}

// 标量左加
template <typename T, typename R2>
Array<T, A_Add<T, A_Scalar<T>, R2>> operator+ (T const& s, Array<T, R2> const& b) {
    return Array<T, A_Add<T, A_Scalar<T>, R2>>(A_Add<T, A_Scalar<T>, R2>(A_Scalar<T>(s), b.rep()));
}


// 标量右加
template <typename T, typename R1>
Array<T, A_Add<T, R1, A_Scalar<T>>> operator+ (Array<T, R1> const& b, T const& s) {
    return Array<T, A_Add<T, R1, A_Scalar<T>>>(A_Add<T, R1, A_Scalar<T>>(b.rep(), A_Scalar<T>(s)));
}


// 标量左乘
template <typename T, typename R2>
Array<T, A_Mult<T, A_Scalar<T>, R2>> operator* (T const& s, Array<T, R2> const& b) {
    return Array<T, A_Mult<T, A_Scalar<T>, R2>>(A_Mult<T, A_Scalar<T>, R2>(A_Scalar<T>(s), b.rep()));
}


// 标量右乘
template <typename T, typename R1>
Array<T, A_Mult<T, R1, A_Scalar<T>>> operator* (Array<T, R1> const& b, T const& s) {
    return Array<T, A_Mult<T, R1, A_Scalar<T>>>(A_Mult<T, R1, A_Scalar<T>>(b.rep(), A_Scalar<T>(s)));
}

#endif