#ifndef _FREDRIC_STACK4_HPP_
#define _FREDRIC_STACK4_HPP_
#include <stdexcept> 

// 非类型模板参数
template <typename T, int MAXSIZE>
class Stack {
    private:
        T elems[MAXSIZE];
        int num_elems;

    public:
        Stack();
        void push(T const&);
        void pop();
        T top() const;
        bool empty() const {
            return num_elems == 0;
        }

        bool full() const {
            return num_elems == MAXSIZE;
        }
};
template <typename T, int MAXSIZE>
Stack<T, MAXSIZE>::Stack(): num_elems(0) {

}

template <typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::push(T const& elem) {
    if(num_elems == MAXSIZE) {
        throw std::out_of_range("Stack<>::push(): stack is full");
    }
    elems[num_elems] = elem;
    ++num_elems;
}

template <typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::pop() {
    if(num_elems <= 0) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    --num_elems;
}

template <typename T, int MAXSIZE>
T Stack<T, MAXSIZE>::top() const {
    if(num_elems <= 0) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return elems[num_elems-1];
}
#endif