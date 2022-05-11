#include <iostream>

using std::cout;
using std::endl;

struct Foo {
    static const auto var2_ = 0;
};


template <typename T> 
struct Bar{};


int main() {
    int arr[10] = {0};
    auto aa = arr;
    
    for(int i=0; i<10; i++) {
        cout << *aa << endl;
        ++aa;
    }
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
