#ifndef _FREDIRC_STACK8_HPP_
#define _FREDIRC_STACK8_HPP_
#include <deque>
#include <stdexcept>
#include <memory>

template <typename T,
          template <typename ELEM, typename Alloc = std::allocator<ELEM>>
          class CONT = std::deque>
class Stack {
    private:
        CONT<T> elems;
    
    public:
        void push(T const&);
        void pop();
        T top() const;
        bool empty() const;

        template <typename T2, 
                  template <typename ELEM2, typename Alloc2 = std::allocator<ELEM2>>
                  class CONT2>
        Stack<T, CONT>& operator=(Stack<T2, CONT2> const&); 
};
#endif