#include <iostream>
using std::cout;
using std::endl;
#include <typeinfo>
#include <cstdio>

class Foo {
    public:
        static int Get() {
            return 10;
        }
};


class Bar {
    public:
        static const char* Get() {
            return "10";
        }
};

template <typename T> 
decltype(T::Get()) func() {
    auto var = T::Get();
    return var;
}

int main() {

    auto res0 =  func<Foo>();
    cout << "res0=" << res0 << endl;
    cout << typeid(res0).name() << endl;


    auto res1 = func<Bar>();
    cout << "res1=" << res1 << endl;
    cout << typeid(res1).name() << endl;
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
