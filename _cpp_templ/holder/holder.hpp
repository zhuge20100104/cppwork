#ifndef _FREDRIC_HOLDER_HPP_
#define _FREDRIC_HOLDER_HPP_

#include <algorithm>

template <typename T>
class Holder {
    private:
        T* ptr;
    
    public:
        // 默认构造函数，将 ptr初始化为nullptr
        Holder(): ptr(nullptr) {}

        // 带指针的构造函数，将ptr初始化为一个指针
        Holder(T* p): ptr(p) {}
        
        // 析构函数，删除持有的指针
        ~Holder() {
            delete ptr;
            ptr = nullptr;
        }

        // 赋值为一个新的指针
        Holder<T>& operator=(T* p) {
            delete ptr;
            ptr = p;
            return *this;
        } 

        // 指针操作符重载
        T& operator*() const {
            return *ptr;
        }

        // 指向操作符重载
        T* operator->() const {
            return ptr;
        }

        // 获取引用的对象
        T* get() const {
            return ptr;
        }

        // 释放引用对象的所有权
        void release() {
            delete ptr;
            ptr = nullptr;
        }

        // 和其他Holder对象交换所有权
        void exchange_with(Holder<T>& h) {
            std::swap(ptr, h.ptr);
        }

        void exchange_with(T* & p) {
            std::swap(ptr, p);
        }

        //不允许拷贝和拷贝赋值
        Holder(Holder<T> const& other) = delete;
        Holder<T>& operator=(Holder<T> const& other) = delete;

};
#endif