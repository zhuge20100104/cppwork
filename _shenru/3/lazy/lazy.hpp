#ifndef _LAZY_HPP_
#define _LAZY_HPP_
#include <boost/optional.hpp>
#include <functional>
using boost::optional;

template <typename T>
struct Lazy {
    Lazy() {}

    template <typename Func, typename ... Args>
    Lazy(Func&& f, Args && ... args) {
        m_func = [&f, &args...] {return f(args...);};
    }

    T& Value() {
        if(!m_value.is_initialized()) {
            m_value = m_func();
        }
        return *m_value;
    }

    bool IsValueCreated() const {
        return m_value.is_initialized();
    }

    private:
        std::function<T()> m_func;
        optional<T> m_value;        
};

// 提供一个可以直接调用的lazy函数，生成一个Lazy对象
template <typename T>
using RetLazy = Lazy<typename std::result_of<T>::type>;

template <typename Func, typename ... Args>
RetLazy<Func(Args...)> lazy(Func && func, Args&& ... args) {
    return RetLazy<Func(Args...)>(std::forward<Func>(func), std::forward<Args>(args)...);
}

#endif