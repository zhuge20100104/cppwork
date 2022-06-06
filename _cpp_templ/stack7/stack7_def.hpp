#include "stack7.hpp"

#include <stdexcept>

template <typename T, 
          template <typename> class CONT>
inline bool Stack<T, CONT>::empty() const {
    return elems.empty();
}

template <typename T, 
          template <typename> class CONT>
void Stack<T, CONT>::push(T const& elem) {
    elems.push_back(elem);
}

template <typename T, 
          template <typename> class CONT>
void Stack<T, CONT>::pop() {
    if(elems.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    elems.pop_back();
}

template <typename T, 
          template <typename> class CONT>
T Stack<T, CONT>::top() const {
    if(elems.empty()) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return elems.back();
}