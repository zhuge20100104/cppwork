#ifndef _FREDRIC_TYPE_T_HPP_
#define _FREDRIC_TYPE_T_HPP_

// 是否基础类型，主模板
template <typename T>
class IsFundaT {
    public:
        enum {Yes=0, No=1};
};

// 基础类型的模板偏特化
#define MK_FUNDA_TYPE(T) \
 template <> \
 class IsFundaT<T> { \
     public: \
        enum {Yes=1, No=0}; \
 }; \

MK_FUNDA_TYPE(void)
MK_FUNDA_TYPE(bool)
MK_FUNDA_TYPE(char)
MK_FUNDA_TYPE(signed char)
MK_FUNDA_TYPE(unsigned char)
MK_FUNDA_TYPE(wchar_t)

MK_FUNDA_TYPE(signed short)
MK_FUNDA_TYPE(unsigned short)
MK_FUNDA_TYPE(signed int)
MK_FUNDA_TYPE(unsigned int)
MK_FUNDA_TYPE(signed long)
MK_FUNDA_TYPE(unsigned long)

#if LONGLONG_EXITS
    MK_FUNDA_TYPE(signed long long)
    MK_FUNDA_TYPE(unsigned long long)
#endif

MK_FUNDA_TYPE(float)
MK_FUNDA_TYPE(double)
MK_FUNDA_TYPE(long double)

#undef MK_FUNDA_TYPE

// CompondT 主模板
template <typename T>
class CompondT {
    public: 
        enum {
            IsPtrT=0, 
            IsRefT=0,
            IsArrayT=0,
            IsFuncT=0,
            IsPtrMemT=0
        };

        using BaseT = T;
        using BottomT = T;
        using ClassT = CompondT<void>;
};

// 成员函数指针定义
template <typename T>
class IsFunctionT {
    private:
        using One = char;
        using Two = struct {char a[2];};
        // 泛化不能匹配的任意类型
        template <typename U> static One test(...);
        // 除了函数，其他类型都能转换成 U类型的数组指针
        template <typename U> static Two test(U (*) [1]);
    
    public:
        enum {Yes = sizeof(IsFunctionT<T>::test<T>(0)) == 1};
        enum {No = !Yes};
};

template <typename T>
class IsFunctionT<T&> {
    public:
        enum {Yes=0};
        enum {No=!Yes};
};

template <>
class IsFunctionT<void> {
    public:
        enum {Yes=0};
        enum {No=!Yes};
};

template <>
class IsFunctionT<void const> {
    public:
        enum {Yes=0};
        enum {No=!Yes};
};

template <>
class IsFunctionT<void volatile> {
    public:
        enum {Yes=0};
        enum {No=!Yes};
};

template <>
class IsFunctionT<void const volatile> {
    public:
        enum {Yes=0};
        enum {No=!Yes};
};


// 针对引用类型的偏特化
template <typename T>
class CompondT<T&> {
    public: 
        enum {
            IsPtrT=0, 
            IsRefT=1,
            IsArrayT=0,
            IsFuncT=0,
            IsPtrMemT=0
        };

        using BaseT = T;
        using BottomT = typename CompondT<T>::BottomT;
        using ClassT = CompondT<void>;
};

// 针对指针类型的偏特化
template <typename T>
class CompondT<T*> {
    public: 
        enum {
            IsPtrT=1, 
            IsRefT=0,
            IsArrayT=0,
            IsFuncT=0,
            IsPtrMemT=0
        };

        using BaseT = T;
        using BottomT = typename CompondT<T>::BottomT;
        using ClassT = CompondT<void>;
};

#include <cstddef>
// 针对数组类型的偏特化
template <typename T, std::size_t N>
class CompondT<T[N]> {
    public: 
        enum {
            IsPtrT=0, 
            IsRefT=0,
            IsArrayT=1,
            IsFuncT=0,
            IsPtrMemT=0
        };

        using BaseT = T;
        using BottomT = typename CompondT<T>::BottomT;
        using ClassT = CompondT<void>;
};


// 针对空数组的偏特化
template <typename T>
class CompondT<T[]> {
    public: 
        enum {
            IsPtrT=0, 
            IsRefT=0,
            IsArrayT=1,
            IsFuncT=0,
            IsPtrMemT=0
        };

        using BaseT = T;
        using BottomT = typename CompondT<T>::BottomT;
        using ClassT = CompondT<void>;
};


// 针对成员指针的偏特化
template <typename T, typename C>
class CompondT<T C::*> {
    public: 
        enum {
            IsPtrT=0, 
            IsRefT=0,
            IsArrayT=0,
            IsFuncT=0,
            IsPtrMemT=1
        };

        using BaseT = T;
        using BottomT = typename CompondT<T>::BottomT;
        using ClassT = C;
};

// 针对0参 普通函数的特化
template <typename R>
class CompondT<R()> {
    public: 
        enum {
            IsPtrT=0, 
            IsRefT=0,
            IsArrayT=0,
            IsFuncT=1,
            IsPtrMemT=0
        };

        using BaseT = R();
        using BottomT = R();
        using ClassT = CompondT<void>;
};

// 针对1参 普通函数的特化
template <typename R, typename P1>
class CompondT<R(P1)> {
    public: 
        enum {
            IsPtrT=0, 
            IsRefT=0,
            IsArrayT=0,
            IsFuncT=1,
            IsPtrMemT=0
        };

        using BaseT = R(P1);
        using BottomT = R(P1);
        using ClassT = CompondT<void>;
};

// 针对多参 普通函数的特化
template <typename R, typename P1>
class CompondT<R(P1, ...)> {
    public: 
        enum {
            IsPtrT=0, 
            IsRefT=0,
            IsArrayT=0,
            IsFuncT=1,
            IsPtrMemT=0
        };

        using BaseT = R(P1);
        using BottomT = R(P1);
        using ClassT = CompondT<void>;
};


// 枚举类型处理
struct SizeOverOne { char c[2]; };

// 枚举不能转换成 Function和Array
template <typename T, bool convert_possible = !CompondT<T>::IsFuncT && !CompondT<T>::IsArrayT>
class ConsumeUDC {
    public:
        operator T() const;
};

// 不能转换的类型的偏特化，啥都不做
template <typename T>
class ConsumeUDC<T, false> {
};

// 枚举类型也不能转换为void类型
template <bool convert_possible>
class ConsumeUDC<void, convert_possible> {
};


char enum_check(bool);
char enum_check(char);
char enum_check(signed char);
char enum_check(unsigned char);
char enum_check(wchar_t);

char enum_check(signed short);
char enum_check(unsigned short);
char enum_check(signed int);
char enum_check(unsigned int);
char enum_check(signed long);
char enum_check(unsigned long);

#if LONGLONG_EXITS
    char enum_check(signed long long);
    char enum_check(unsigned long long); 
#endif

char enum_check(float);
char enum_check(double);
char enum_check(long double);

// 所有其他类型，都返回2
SizeOverOne enum_check(...);

template <typename T>
class IsEnumT {
    public:
        enum {Yes= IsFundaT<T>::No &&
            !CompondT<T>::IsRefT &&
            !CompondT<T>::IsPtrT &&
            !CompondT<T>::IsPtrMemT &&
            sizeof(enum_check(ConsumeUDC<T>()))==1};
        enum {No=!Yes};
};


// 类类型处理
template <typename T>
class IsClassT {
    public:
        enum {Yes=IsFundaT<T>::No &&
            IsEnumT<T>::No &&
            !CompondT<T>::IsPtrT &&
            !CompondT<T>::IsRefT &&
            !CompondT<T>::IsArrayT &&
            !CompondT<T>::IsPtrMemT &&
            !CompondT<T>::IsFuncT};
        enum {No=!Yes};
};

// 处理所有类型的模板类
template <typename T>
class TypeT {
    public:
        enum {
            IsFundaT = IsFundaT<T>::Yes,
            IsPtrT = CompondT<T>::IsPtrT,
            IsRefT = CompondT<T>::IsRefT,
            IsArrayT = CompondT<T>::IsArrayT,
            IsFuncT = CompondT<T>::IsFuncT,
            IsPtrMemT = CompondT<T>::IsPtrMemT,
            IsEnumT = IsEnumT<T>::Yes,
            IsClassT = IsClassT<T>::Yes
        };
};

#endif