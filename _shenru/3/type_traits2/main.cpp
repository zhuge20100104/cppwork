#include <iostream>
#include <type_traits>
#include <cstdlib>

using std::cout;
using std::endl;

int fn(int) {
    return int();
}

using fn_ref = int(&)(int);
using fn_ptr = int(*)(int);

struct fn_class {
    int operator()(int i) {
        return i;
    }
};

int main(void) {
    using A = typename std::result_of<decltype(fn)&(int)>::type;
    using B = typename std::result_of<fn_ref(int)>::type;
    using C = typename std::result_of<fn_ptr(int)>::type;
    using D = typename std::result_of<fn_class(int)>::type; 

    cout << std::boolalpha;
    cout << "typedefs of int" << endl;

    cout << "A: " << std::is_same<int, A>::value << endl;
    cout << "B: " << std::is_same<int, B>::value << endl;
    cout << "C: " << std::is_same<int, C>::value << endl;
    cout << "D: " << std::is_same<int, D>::value << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}   