#ifndef _FREDRIC_PIMPL_HPP_
#define _FREDRIC_PIMPL_HPP_

#include <memory>

template <typename T>
class PImpl {
private:
    std::unique_ptr<T> p_impl;
public:
    template <typename ... Args>
    PImpl(Args&& ... args): p_impl{new T(std::forward<Args>(args)...)} {

    }

    PImpl(): p_impl(new T()) {

    }

    ~PImpl() {
    }
   
    T* operator->() {
        return p_impl.get();
    }

    T& operator*() {
        return *p_impl;
    }
};
#endif