#include <iostream>
using std::cout;
using std::endl;
#include <memory>
#include <type_traits>
#include <cstdlib>

template <typename T> 
struct Construct {
    using U = typename std::remove_reference<T>::type;
    using LU = typename std::add_lvalue_reference<U>::type;
    
    Construct():ptr(new U) {
    }
    
    LU get() const {

        *ptr = 100;
        return *ptr.get();
    }

    private:
        std::unique_ptr<U> ptr;
};


int main(void) {
    Construct<int> c;
    int a = c.get();

    cout << a << endl;
    cout << a << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
