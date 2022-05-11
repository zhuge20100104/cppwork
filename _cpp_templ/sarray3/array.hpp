#ifndef _FREDRIC_ARRAY_HPP_
#define _FREDRIC_ARRAY_HPP_

#include "sarray1/sarray1.hpp"
#include <cstddef>
#include <cassert>

template <typename T, typename Rep = SArray<T>>
class Array {
    private:
        Rep expr_rep;
    
    public:
        explicit Array(std::size_t s): expr_rep(s) {}

        // 从可能的Representation做拷贝构造
        Array(Rep const& b): expr_rep(b) {
        }

        Array<T>& operator=(Array<T> const& b) {
            assert(size() == b.size());
            if(&b == this) {
                return *this;
            }

            for(std::size_t idx=0; idx<size(); ++idx) {
                expr_rep[idx] = b[idx];
            } 

            return *this;
        }

        // 不同类型的赋值操作符重载
        template <typename T2, typename Rep2> 
        Array<T>& operator=(Array<T2, Rep2> const& b) {
            assert(size() == b.size());

            for(std::size_t idx=0; idx<size(); ++idx) {
                expr_rep[idx] = b[idx];
            } 

            return *this;
        }

        T operator[](std::size_t idx) const {
             assert(idx < size());
             return expr_rep[idx];
        }

        T& operator[](std::size_t idx){
             assert(idx < size());
             return expr_rep[idx];
        }

        Rep const& rep() const {
            return expr_rep;
        }

        Rep& rep() {
            return expr_rep;
        }

        std::size_t size() const {
            return expr_rep.size();
        }
};

#endif 