#ifndef _FREDRIC_MY_CLASS_HPP_
#define _FREDRIC_MY_CLASS_HPP_

#include <iostream>

class my_class {
    private:
        int value;
    
    public:
        my_class(int v_): value{v_} {}
        
        friend bool operator < (my_class const& x, my_class const& y) {
            return x.value < y.value;
        }

        friend std::ostream& operator << (std::ostream& os, my_class const& x) {
            os << x.value;
            return os;
        }
};
#endif