#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include <functional>
#include <type_traits>

template <typename Ret = void>
struct CommonCommand {
    private:
        // Wrap之后的成员函数，参数为空，返回Ret
        std::function<Ret()> m_f;
    
    public:
        // 接收普通函数的函数包装器
        template <class F, class ... Args, class = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type >
        void Wrap(F && f, Args && ... args) {
            m_f = [&] {return f(args...);};
        }

        // 接收常量成员函数的包装器
        // R函数声明中的返回值
        // C实际调用函数的子类类型
        // DArgs 形参类型
        // P子类的基类类型
        // Args实参类型
        // 因为存在使用父类的指针调用子类的虚函数的情况
        // 大部分情况下，P和C是同类型的
        template<class R, class C, class ... DArgs, class P, class ... Args>
        void Wrap(R(C::*f)(DArgs...) const, P && p, Args && ... args) {
            m_f = [&, f] { return (*p.*f)(args...); };
        }

        // 接收非常量成员函数的包装器
         template<class R, class C, class ... DArgs, class P, class ... Args>
        void Wrap(R(C::*f)(DArgs...), P && p, Args && ... args) {
            m_f = [&, f] { return (*p.*f)(args...); };
        }

        Ret Execute() {
            return m_f();
        }
};

#endif