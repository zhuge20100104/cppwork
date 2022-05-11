#include "integer.h"
#include <iostream>

class IntPtr {
    Integer* m_ptr;

    public:
        IntPtr(Integer* a): m_ptr(a)  {}
        
        ~IntPtr() {
            delete m_ptr;
        }

        Integer* operator->() {
            return m_ptr;
        }

        Integer& operator*() {
            return *m_ptr;
        }
};

void create_integer() {
    IntPtr ptr {new Integer{}};
    ptr->set_value(10);
    std::cout << ptr->get_value() << std::endl;
}

auto main(int argc, char* argv[]) -> int {
    create_integer();
    return EXIT_SUCCESS;
}