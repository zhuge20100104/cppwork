#include <iostream>
using std::cout;
using std::endl;
#include <cstdio>

class Foo {
    public:
        Foo(int a):mA(a) {
            cout << "Foo(int a)被调用 a=" << a << endl;
        }

    private:
        Foo(const Foo& f):mA(f.mA) {
            cout << "Foo(const Foo&)被调用 a=" << mA << endl;
        }

        int mA;
};

int main() {
    
    Foo a(123);
    Foo b = {123};
    Foo c{123};

    int d = {1};
    int e {2};

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
