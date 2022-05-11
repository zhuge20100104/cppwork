#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>


void myPrint(int a, int b) {
    cout << "调用普通函数" << endl;
    cout << "a=" << a << " b=" << b << endl;
}

template <typename T>
void myPrint(T a, T b) {
    cout << "调用模板函数" << endl;
    cout << "a=" << a << " b=" << b << endl;
}

int main(void) {

    // 默认调用普通函数
    myPrint(10, 8);

    // 强制调用模板函数
    myPrint<>(10, 8);

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}