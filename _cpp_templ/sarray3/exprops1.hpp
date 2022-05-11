#ifndef _FREDRIC_EXPR_OPS1_HPP_
#define _FREDRIC_EXPR_OPS1_HPP_

#include "a_traits.hpp"

#include <cstddef>
#include <cassert>


// 加法运算, OP1 应该是一个Array<T> 或者 AScalar<T>类型的对象
template <typename T, typename OP1, typename OP2>
class A_Add {
    private:
        typename A_Traits<OP1>::ExprRef op1;
        typename A_Traits<OP2>::ExprRef op2;

    public:
        A_Add(OP1 const& a, OP2 const& b): op1(a), op2(b) {}

        T operator[](std::size_t idx) const {
            return op1[idx] + op2[idx];
        }

        // size是两个集合中较大的size，标量的size为0
        std::size_t size() const {
            assert(op1.size() == 0 || op2.size() == 0 || op1.size() == op2.size());
            return op1.size() != 0 ? op1.size() : op2.size();
        }
};


// 乘法运算
template <typename T, typename OP1, typename OP2>
class A_Mult {
    private:
        typename A_Traits<OP1>::ExprRef op1;
        typename A_Traits<OP2>::ExprRef op2;

    public:
        A_Mult(OP1 const& a, OP2 const& b): op1(a), op2(b) {}

        T operator[](std::size_t idx) const {
            return op1[idx] * op2[idx];
        }

        // size是两个集合中较大的size，标量的size为0
        std::size_t size() const {
            assert(op1.size() == 0 || op2.size() == 0 || op1.size() == op2.size());
            return op1.size() != 0 ? op1.size() : op2.size();
        }
};



#endif