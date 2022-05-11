#include <iostream>

using std::cout;
using std::endl;
#include <cstdlib>

template <typename T> 
void MySwap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

int main() {

    int a = 10, b = 8;
    cout << "交换前: ";
    cout << "a=" << a << " b=" << b << endl;

    MySwap(a, b);

    cout << "交换后: ";
    cout << "a=" << a << " b=" << b << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}