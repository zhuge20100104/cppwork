#include <iostream>
#include <memory>

class NoVirtual {};

class Virtual {
    public:
        virtual void foo() = 0;
};

template <typename VBase>
class Base: public VBase {
    public:
        void foo() {
            std::cout << "Base::foo()\n";  
        }
};

template <typename V>
class Derived: public Base<V> {
    public:
        void foo() {
            std::cout << "Derived::foo()\n";
        }
};

int main(int argc, char* argv[]) {

    std::unique_ptr<Base<NoVirtual>> base = std::make_unique<Derived<NoVirtual>>(); 
    base->foo();

    std::unique_ptr<Base<Virtual>> derived = std::make_unique<Derived<Virtual>>();
    derived->foo();
    return EXIT_SUCCESS;
}