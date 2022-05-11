#ifndef _FREDRIC_IS_CLASS_T_HPP_
#define _FREDRIC_IS_CLASS_T_HPP_

template <typename T>
class IsClassT {
        using One = char;
        using Two = struct {char a[2];};
        template <typename C>
        static One test(int C::*);
        template <typename C>
        static Two test(...);
    public:
        enum {YES = sizeof(IsClassT<T>::test<T>(0)) == 1};
        enum {NO = !YES};
};

#endif