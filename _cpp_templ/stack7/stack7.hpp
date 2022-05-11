#ifndef _FREDIRC_STACK7_HPP_
#define _FREDIRC_STACK7_HPP_

#include <deque>

template <typename T, 
          template <typename> class CONT = std::deque>
class Stack {
    private:
        CONT<T> elems;
    
    public:
        void push(T const&);
        void pop();
        T top() const;
        bool empty() const;
};

#endif