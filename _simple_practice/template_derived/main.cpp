#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>

template <class T>
class Base {
    public:
        Base() {}
        T m;
};

template <class T1, class T2> 
class Son: public Base<T2> {
    public:
        T1 obj;
        Son() {
            cout << "T1的类型为: " << typeid(T1).name() << endl;
            cout << "T2的类型为: " << typeid(T2).name() << endl;
        }
};

int main(void) {

    Son<int, char> s;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}