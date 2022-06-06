#ifndef _FREDRIC_FUNC_DECORATOR_HPP_
#define _FREDRIC_FUNC_DECORATOR_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <functional>

struct Logger {
    std::function<void()> func;
    std::string name;

    Logger(std::function<void()> const& func_, std::string const& name_): func{func_}, name{name_} {

    }

    void operator()() const {
        std::cout << "Entering " << name << std::endl;
        func();
        std::cout << "Exiting " << name << std::endl;
    }
};

template <typename Func>
struct Logger2 {
    Func func;
    std::string name;

    Logger2(Func const& func_, std::string const& name_): func{func_}, name{name_} {

    }

    void operator()() const {
        std::cout << "Entering " << name << std::endl;
        func();
        std::cout << "Exiting " << name << std::endl;
    }
};

template <typename Func>
auto make_logger2(Func func, std::string const& name) {
    return Logger2<Func>(func, name);
}

template <typename> 
struct Logger3;

template <typename R, typename ...Args>
struct Logger3<R(Args...)> {
    std::function<R(Args...)> func;
    std::string name;

    Logger3(std::function<R(Args...)> const& func_, std::string const& name_): func{func_}, name{name_} {

    }

    R operator()(Args ...args) {
        std::cout << "Entering " << name << std::endl;
        R result = func(args...);
        std::cout << "Exiting " << name << std::endl;
        return result;
    }
};

template <typename R, typename ... Args>
auto make_logger3(R (*func) (Args...), std::string const& name) {
    return Logger3<R(Args...)>(
        std::function<R(Args...)>(func), name);
}
#endif