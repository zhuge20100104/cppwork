#ifndef _FREDRIC_STACK1_HPP_
#define _FREDRIC_STACK1_HPP_
#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
    private:
        std::vector<T> elems;
    
    public:
        void push(T const&);
        void pop();
        T top() const;
        bool empty() const {
            return elems.empty();
        }
};

template <typename T>
void Stack<T>::push(T const& elem) {
     elems.push_back(elem);
}

template <typename T>
void Stack<T>::pop() {
    if(elems.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    elems.pop_back();  // Remove last element
}

template <typename T>
T Stack<T>::top() const {
    if(elems.empty()) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return elems.back(); // return copy of last element
}
#endif