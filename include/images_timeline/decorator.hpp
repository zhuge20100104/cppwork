#ifndef _FREDRIC_DECORATOR_HPP_
#define _FREDRIC_DECORATOR_HPP_

#include <iostream>
#include <functional>

//-------------------------------
// BEGIN decorator implementation
//-------------------------------

template <class> struct decorator;

const int RetryCount = 3;

template <class R, class... Args>
struct decorator<R(Args ...)>
{
   decorator(std::function<R(Args ...)> f) : f_(f) {}

   R operator()(Args ... args)
   {
      R res;
      for(int i=0; i<RetryCount; ++i) {
        res = f_(args...);
        if(res) {
            return res;
        } else  {
            std::cout <<"Failed, retry..." << std::endl;
        }
      }
      return res;
   }

   std::function<R(Args ...)> f_;
};

template<class R, class... Args>
decorator<R(Args...)> make_decorator(R (*f)(Args ...))
{
   return decorator<R(Args...)>(std::function<R(Args...)>(f));
}

#endif