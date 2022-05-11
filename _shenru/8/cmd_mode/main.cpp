#include "command.hpp"
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;

class Parent {
    public:
        virtual void doSth() {
            cout << "Parent doSth" << endl;
        }
        virtual ~Parent() {
            cout << "父类析构函数被调用" << endl;
        }
};

class Child: public Parent {
    public:
        virtual void doSth() {
            cout << "Child doSth" << endl;
        }

        virtual ~Child() {
            cout << "子类析构函数被调用" << endl;
        }
};

// 调用仿函数
class FuncObj {
    public:
        void operator() () {
            cout << "Func Obj被调用" << endl;
        } 
};

void f() {
    cout << "普通函数f被调用" << endl;
}

int main(void) {
    // 使用多态调用子类doSth
    shared_ptr<Parent> p(new Child);
    CommonCommand<void> cmd;
    cmd.Wrap(&Parent::doSth, p);
    cmd.Execute();

    // 调用常量仿函数
    CommonCommand<void> cmd1;
    FuncObj obj;
    cmd1.Wrap(&FuncObj::operator(), &obj);
    cmd1.Execute();

    // 调用普通函数
    CommonCommand<void> cmd2;
    cmd2.Wrap(f);
    cmd2.Execute();
} 