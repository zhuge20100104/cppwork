#include "stdobjpolicy.hpp"
#include "stdarraypolicy.hpp"
#include "simplerefcount.hpp"
#include "memberrefcount.hpp"
#include "countptr.hpp"

#include <iostream>
#include <vector>

class MyObject {
    int count{0};
    
    public:
        using Ptr = CountingPtr<MyObject, MemberReferenceCount<MyObject, int, &MyObject::count>>;

        void do_something() {
            std::cout << "Do something ..." << std::endl;
        }
};

void test1();
void test2();

int main(int argc, char* argv[]) {
    test1();
    test2();

    return EXIT_SUCCESS;
}

void test1() {
    std::cout << "\ntest1()\n";
    CountingPtr<int> p0;

    {
        CountingPtr<int> p1 {new int(42)};
        std::cout << "*p1 = " << *p1 << std::endl;

        *p1 = 17;
        std::cout << "*p1 = " << *p1 << std::endl;

        CountingPtr<int> p2 = p1;
        std::cout << "*p2 = " << *p2 << std::endl;

        *p1 = 33;
        std::cout << "*p2 = " << *p2 << std::endl;

        p0 = p2;
        std::cout << "*p0 = " << *p0 << std::endl;

        ++*p0;
        ++*p1;
        ++*p2;

        std::cout << "*p0 = " << *p0 << std::endl;
        std::cout << "*p1 = " << *p1 << std::endl;
        std::cout << "*p2 = " << *p2 << std::endl;
    }

    std::cout << "After block: *p0 = " << *p0 << std::endl;
}

void test2() {
    std::cout << "\ntest2()\n";
    
    MyObject::Ptr obj_ptr {new MyObject};
    obj_ptr->do_something();

    CountingPtr<int,SimpleReferenceCount, StandardArrayPolicy> int_arr {
        new int[10]
    };

    auto arr = int_arr.get();
    for(int i=0; i<10; ++i) {
        arr[i] = i + 1;
    }

    for(int i=0; i<10; ++i) {
       std::cout << arr[i] << " ";
    }

    std::cout << "\n";
}

