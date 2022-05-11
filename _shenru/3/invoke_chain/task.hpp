#ifndef _TASK_HPP_
#define _TASK_HPP_
#include <functional>
#include <type_traits>

template <typename T>
class Task;

template <typename R, typename ... Args>
class Task<R(Args...)> {
public:
    Task(std::function<R(Args...)>&& f): m_func(std::move(f)) {}
    Task(std::function<R(Args...)>& f): m_func(f) {}

    R Run(Args && ... args) {
        return m_func(std::forward<Args>(args)...);
    }

    template <typename F> 
    auto Then(const F& f) -> Task<typename std::result_of<F(R)>::type(Args...)> {
        using return_type = typename std::result_of<F(R)>::type;
        auto func = std::move(m_func);

        return Task<return_type(Args...)>(
            [func, f](Args&& ... args) {
                return f(func(std::forward<Args>(args)...)); 
            }
        );
    }
private:
    std::function<R(Args...)> m_func;

};
#endif