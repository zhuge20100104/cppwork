#include <iostream>

using std::cout;
using std::endl;
#include <cstdlib>

template <typename T> 
void print(T a) {
    cout << a << endl;
}

template <typename T1, typename T2> 
void print(T1 a, T2 b) {
    cout << a << " " << b << endl;
}

template <typename T1, typename T2, typename T3> 
void print(T1 a, T2 b, T3 c) {
    cout << a << " " << b << " " << c << endl;
}

template <typename T1, typename T2, typename T3, typename T4> 
void print(T1 a, T2 b, T3 c, T4 d) {
    cout << a << " " << b << " " << c << " " << d << endl;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5> 
void print(T1 a, T2 b, T3 c, T4 d, T5 e) {
    cout << a  << " " << b << " " << c << " " << d << " " << e << endl;
}

int main(void) {
    print(1);
    print(1, 2);
    print(1, 2, 3);
    print(1, 2, 3, 4);
    print(1, 2, 3, 4, 5);

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}