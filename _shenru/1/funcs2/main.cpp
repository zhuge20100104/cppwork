#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;
#include <cstdlib>

// 普通函数打印函数名
void func(void) {
    cout << __FUNCTION__ << endl;
}

// 静态成员函数打印函数名
class Foo {
    public:
        static int foo_func(int a) {
            cout << __FUNCTION__ << "(" << a << ")--->";
            return a;
        }
};

// 仿函数打印函数名
class Bar {
    public:
        int operator()(int a) {
            cout << __FUNCTION__ << "(" << a << ")--->";
            return a;
        }
};


int main(void) {
    // 使用std::function调用普通函数
    function<void(void)> fr1 = func;
    fr1();

    // 使用std::function调用静态成员函数
    function<int(int)> fr2 = Foo::foo_func;
    fr2(123);  
    cout << endl;

    // 使用std::function调用仿函数
    Bar bar;
    fr2 = bar;
    cout << fr2(456) << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
