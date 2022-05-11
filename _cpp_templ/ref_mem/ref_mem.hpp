#ifndef _FREDRIC_REF_MEM_HPP_
#define _FREDRIC_REF_MEM_HPP_
#include "holder.hpp"

class MemberType {};

class RefMembers {
    private:
        Holder<MemberType> ptr1;
        Holder<MemberType> ptr2;

    public:
        // 默认构造，不会存在内存泄漏
        RefMembers(): ptr1{new MemberType}, ptr2{new MemberType} {}

        // 拷贝构造函数，不存在内存泄漏
        RefMembers(RefMembers const& x): ptr1 {new MemberType(*x.ptr1)}, ptr2 {new MemberType(*x.ptr2)} {}

        // 赋值操作符重载
        RefMembers const& operator=(RefMembers const& x) {
            *ptr1 = *x.ptr1;
            *ptr2 = *x.ptr2;
            return *this;
        }
};
#endif