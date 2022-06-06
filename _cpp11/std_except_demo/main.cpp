#include <iostream>
#include <memory>
#include <vector>

class A {
    public:
    A() {
        std::cout << "A()" << std::endl;
    }

    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

class B {
    public:
    B() {
        std::cout << "B()" << std::endl;
    }

    ~B() {
        std::cout << "~B()" << std::endl;
    }
};

class Test {
    std::unique_ptr<A> pA {};
    B b {};
    std::unique_ptr<int> pInt {};
    std::string pStr {};
    std::vector<int> pArr {};

    public:
    Test() {
        std::cout << "Test():Acquire Resources" << std::endl;
        pA.reset(new A);
        pInt.reset(new int);
    }

    ~Test() {
        std::cout << "~Test: Release Resources" << std::endl;
        throw std::runtime_error("Failed to de-allocate");
    }
};

int main(int argc, char* argv[]) {
    try {
        Test t;
    } catch(const std::runtime_error& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}