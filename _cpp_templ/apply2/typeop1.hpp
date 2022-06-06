#ifndef _FREDRIC_TYPEOP_HPP_
#define _FREDRIC_TYPEOP_HPP_

// 主模板
template <typename T>
class TypeOp {
    public:
        using ArgT = T;
        using BareT = T;
        using ConstT = T const;
        using RefT = T&;
        using RefBareT = T&;
        using RefConstT = T const&; 
};

// T const 特化
template <typename T>
class TypeOp<T const> {
    public:
        using ArgT = T const;
        using BareT = T;
        using ConstT = T const;
        using RefT = T const&;
        using RefBareT = T&;
        using RefConstT = T const&; 
};

// T& 特化
template <typename T>
class TypeOp<T&> {
    public:
        using ArgT = T&;
        using BareT = typename TypeOp<T>::BareT;
        using ConstT = T const;
        using RefT = T&;
        using RefBareT = typename TypeOp<T>::BareT & ;
        using RefConstT = T const&; 
};


// void 特化
template <>
class TypeOp<void> {
    public:
        using ArgT = void;
        using BareT = void;
        using ConstT = void const;
        using RefT = void;
        using RefBareT = void;
        using RefConstT = void;
};
#endif