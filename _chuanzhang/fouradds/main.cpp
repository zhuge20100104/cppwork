#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>

int addFunc(int a, int b) {
    return a + b;
}

class AddCls {
    public:
        int operator() (int a, int b) {
            return a + b;
        }
};

template <class T, class U>
auto addTemp(T a, U b) -> decltype(a+b) {
    return a + b;
}

auto AddLam = [](int a, int b) -> int {
    return a + b;
};


int main(void) {
    cout << "addFunc(1, 2): " << addFunc(1, 2) << endl;
    cout << "AddCls()(1, 2): " << AddCls()(1, 2) << endl;
    cout << "AddTemp(1, 2): " << addTemp(1, 2) << endl;
    cout << "AddLam(1, 2): " << AddLam(1, 2) << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}