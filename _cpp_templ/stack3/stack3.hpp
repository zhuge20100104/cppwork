#ifndef _FREDRIC_STACK3_HPP_
#define _FREDRIC_STACK3_HPP_
#include <vector>
#include <stdexcept>

// Container泛化为类型参数
template <typename T, typename CONT = std::vector<T>>
class Stack {
    private:
        CONT elems;
    public:
        void push(T const&);
        void pop();
        T top() const;
        bool empty() const {
            return elems.empty();
        }
};

template <typename T, typename CONT>
void Stack<T, CONT>::push(T const& elem) {
    elems.push_back(elem);
}

template <typename T, typename CONT>
void Stack<T, CONT>::pop() {
    if(elems.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    elems.pop_back();
}

template <typename T, typename CONT>
T Stack<T, CONT>::top() const {
    if(elems.empty()) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return elems.back();
}
#endif