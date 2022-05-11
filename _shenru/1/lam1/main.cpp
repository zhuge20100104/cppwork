#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>

class A {
    public:
        int i = 0;
        void func(int x, int y) {
            auto x1 = [=] {return i;};
            auto x2 = [&] {return i+x+y; };
            auto x3 = [this, x, y] {return i+x+y; };
            auto x4 = [this] {return i++; };

            x4();
            cout << i << endl;
        }
};

int main() {

    A a;
    a.func(1, 2);
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}

