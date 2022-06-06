#include <iostream>
#include <memory>
#include <cstdlib>

using std::cout;
using std::endl;

template <typename T>
using TPtr = typename std::shared_ptr<T>;

template <typename T>
TPtr<T> Instance() {
    return TPtr<T>(new T);
}

template <typename T, typename T0>
TPtr<T> Instance(T0 t0) {
    return TPtr<T>(new T(t0));
}

template <typename T, typename T0, typename T1> 
TPtr<T> Instance(T0 t0, T1 t1) {
    return TPtr<T>(new T(t0, t1));
}

template <typename T, typename T0, typename T1, typename T2> 
TPtr<T> Instance(T0 t0, T1 t1, T2 t2) {
    return TPtr<T>(new T(t0, t1, t2));
}

template <typename T, typename T0, typename T1, typename T2, typename T3> 
TPtr<T> Instance(T0 t0, T1 t1, T2 t2, T3 t3) {
    return TPtr<T>(new T(t0, t1, t2, t3));
}

template <typename T, typename T0, typename T1, typename T2, typename T3, typename T4> 
TPtr<T> Instance(T0 t0, T1 t1, T2 t2, T3 t3, T4 t4) {
    return TPtr<T>(new T(t0, t1, t2, t3, t4));
}

struct A {
    A(int) {}
    ~A() {
        cout << "A的析构函数被调用" << endl;
    }
};

struct B {
    B(int, double) {}
    ~B() {
        cout << "B的析构函数被调用" << endl;
    }
};

int main(void) {
    TPtr<A> aPtr = Instance<A>(1);
    TPtr<B> bPtr = Instance<B>(1, 3);

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}