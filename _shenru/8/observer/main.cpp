#include "observer.hpp"

using ObserverFunc = std::function<int(int, int)>;

class Observer {
    public:
        int operator() (int a, int b) {
            cout << "Observer函数对象的事件2被调用" << endl;
            int res = a + b;
            return res;
        }
};

class Observer2 {
    public:
        int observerFunc(int a, int b) {
            cout << "Observer2成员函数事件3被调用" << endl;
            int res = a + b;
            return res;
        }
};

int gobserverFunc(int a, int b) {
    cout << "全局的gobserverFunc事件4被调用" << endl;
    int res = a + b;
    return res; 
}

int main(void) {
    Events<ObserverFunc> e;
    // 调用基于lambda表达式的观察者函数
    int lambdaID = e.Connect([](int a, int b){
        int res = a+b;
        cout << "lambda函数的事件1被调用" << endl;
        return res;
    });

    // 调用仿函数的观察者函数
    int obsID = e.Connect(Observer());
    
    // 调用成员函数的观察者函数
    Observer2 o2;
    int obsID1 = e.Connect(std::bind(&Observer2::observerFunc, o2, std::placeholders::_1, std::placeholders::_2));
    
    // 调用全局观察者函数
    int gID4 = e.Connect(gobserverFunc);

    e.Notify(1, 2);

    return 0;
}