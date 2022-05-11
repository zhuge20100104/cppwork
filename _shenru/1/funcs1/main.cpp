#include <iostream>
using std::cout;
using std::endl;
#include <cstdio>


void func(void) {
    cout << "这是一个普通函数" << endl;
}


struct Foo {
    void operator()(void) {
        cout << "这是一个仿函数" << endl;
    }
};


struct Bar {
    
    using fr_t = void(*)(void);

    static void func(void) {
        cout << "使用可转换成函数指针的对象调用函数" << endl;
    }

    operator fr_t(void) {
        return func;
    }
};


struct A {
    int a_;

    void mem_func(void) {
        cout << "A类的成员函数被调用" << endl;
    }
};


int main(void) {
    // 调用普通函数指针
    void(*func_ptr)(void) = &func;
    func_ptr();
    
    // 仿函数调用
    Foo foo;
    foo();
    
    // 可转换成函数指针的类对象调用
    Bar bar;
    bar();

    // 定义两个指针，成员函数指针和成员变量指针
    void (A::*mem_func_ptr)(void) = &A::mem_func;
    int A::*mem_obj_ptr = &A::a_;
    
    // 构造一个aa对象，调用成员函数和 给成员变量赋值
    A aa;
    (aa.*mem_func_ptr)();
    aa.*mem_obj_ptr = 123;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}

