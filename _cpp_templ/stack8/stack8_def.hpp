#ifndef _FREDIRC_STACK8_DEF_HPP_
#define _FREDIRC_STACK8_DEF_HPP_

#include "stack8.hpp"

template <typename T, template <typename, typename> class CONT>
void Stack<T, CONT>::push(T const& elem) {
    elems.push_back(elem);
}

template <typename T, template <typename, typename> class CONT>
void Stack<T, CONT>::pop() {
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    elems.pop_back();
}

template <typename T, template <typename, typename> class CONT>
T Stack<T, CONT>::top() const {
    if (elems.empty()) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return elems.back();
}

template <typename T, template <typename, typename> class CONT>
inline bool Stack<T, CONT>::empty() const {
    return elems.empty();
}

template <typename T, template <typename, typename> class CONT>
template <typename T2, template <typename, typename> class CONT2>
Stack<T, CONT>& Stack<T, CONT>::operator=(Stack<T2, CONT2> const& op2) {
    if((void*)this == (void*)&op2) {
        return *this;
    }

    Stack<T2, CONT2> tmp(op2);
    elems.clear();

    while(!tmp.empty()) {
        elems.push_front(tmp.top());
        tmp.pop();
    }

    return *this;
}

#endif