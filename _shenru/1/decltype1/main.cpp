#include <iostream>

using std::cout;
using std::endl;

#include <cstdio>
#include <typeinfo>

class Foo {
    public:
        static const int num = 0;
        int x;
};

int main() {

    int n = 0;
    const volatile int& x = n;

    decltype(n) a = n;
    decltype(x) b = n;
    
    decltype(Foo::num) c = 0;
    cout << "type of a " << typeid(a).name() << endl;
    cout << "type of b " << typeid(b).name() << endl;
    cout << "type of c " << typeid(c).name() << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}

