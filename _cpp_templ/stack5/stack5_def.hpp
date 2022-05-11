#ifndef _FREDRIC_STACK5_DEF_HPP_
#define _FREDRIC_STACK5_DEF_HPP_
#include "stack5.hpp"
#include <stdexcept>

template<typename T>
void Stack<T>::push(T const& elem) {
    elems.push_back(elem);
}

template <typename T>
void Stack<T>::pop() {
    if(elems.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    elems.pop_back();
}

template <typename T>
inline bool Stack<T>::empty() const {   // return whether the stack is empty
    return elems.empty();
}

template <typename T>
T Stack<T>::top() const {
    if(elems.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    return elems.back();
}

template <typename T>
template <typename T2>
Stack<T>& Stack<T>::operator= (Stack<T2> const& op2) {
    if((void*)this == (void*)&op2){
        return *this;
    }

    Stack<T2> tmp(op2);
    elems.clear();

    while(!tmp.empty()) {
        elems.push_front(tmp.top());
        tmp.pop();
    }
    return *this;
}

#endif