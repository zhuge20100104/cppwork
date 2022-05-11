#ifndef _FREDRIC_STACK5_HPP_
#define _FREDRIC_STACK5_HPP_

#include <deque>

template <typename T>
class Stack {
    private:
        std::deque<T> elems;
    public:
        void push(T const&);
        void pop();
        T top() const;
        bool empty() const;

        template <typename T2>
        Stack<T>& operator= (Stack<T2> const&);
};
#endif