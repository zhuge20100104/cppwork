#ifndef _FREDRIC_A_TRAITS_HPP_
#define _FREDRIC_A_TRAITS_HPP_

template <typename T>
class A_Scalar;

// 主模版
template <typename T>
class A_Traits {
    public:
        using ExprRef = T const&;
};

// 针对标量类型的特化
template <typename T>
class A_Traits<A_Scalar<T>> {
    public:
        using ExprRef = A_Scalar<T>;
};

#endif