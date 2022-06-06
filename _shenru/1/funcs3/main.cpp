#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;
#include <cstdlib>

// 可以将函数指针当作std::function传递，会自动做隐式类型转换
void call_when_even(int x, const function<void(int)>& f) {
    if(!(x&1)) {  // x%2==0 偶数打印
        f(x);
    }
}


void output(int x) {
    cout << x << " ";
}


int main(void) {
    for(int i=0; i<10; i++) {
        call_when_even(i, output);
    }

    cout << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
