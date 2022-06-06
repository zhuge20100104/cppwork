#ifndef _FREDRIC_STACK6_HPP_
#define _FREDRIC_STACK6_HPP_
#include <deque>

template <typename T, typename CONT = std::deque<T>>
class Stack {
    private:
        CONT elems;
    public:
        void push(T const&);
        void pop();
        T top() const;
        bool empty() const;

        template <typename T2, typename CONT2>
        Stack<T, CONT>& operator=(Stack<T2, CONT2> const&);
};
#endif