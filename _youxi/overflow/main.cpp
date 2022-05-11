#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>

int main() {

    int a = 0xFF;
    int b = a << 33;
    cout << "b is: " << b << endl;
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}