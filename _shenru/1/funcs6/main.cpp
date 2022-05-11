#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::bind;
using std::function;
#include <cstdlib>


// 绑定类成员函数和类成员变量
class A {
    public:
        int i = 0;
        void output(int x, int y) {
            cout << x << " " << y << endl; 
        }
};

int main(void) {
    A a;

    function<void(int,int)> fr = bind(&A::output, &a, std::placeholders::_1, std::placeholders::_2);
    fr(1, 2);

    function<int&(void)> ir = bind(&A::i, &a);
    ir() = 123;
    cout << a.i << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
